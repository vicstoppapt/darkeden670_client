//////////////////////////////////////////////////////////////////////////////
// Filename    : GCSupplyItemList.cpp 
// Written By  : rappi76
// Description : 
//////////////////////////////////////////////////////////////////////////////


#include "Assert.h"
#include "Client_PCH.h"
#include "GCSupplyItemList.h"

#ifdef __GAME_SERVER__
	
#endif

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////

GCSupplyItemList::GCSupplyItemList() 
	throw ()
{
	__BEGIN_TRY

	m_SupplyItemList.clear();
 
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
GCSupplyItemList::~GCSupplyItemList() 
	throw ()
{
	__BEGIN_TRY

	list<SupplyItemInfo*>::iterator itr = m_SupplyItemList.begin();
	list<SupplyItemInfo*>::iterator endItr = m_SupplyItemList.end();

	for ( ; itr != endItr ; ++itr )
	{
		if ( *itr != NULL )
		{
			delete *itr; 
			*itr = NULL;
		}
	}

	m_SupplyItemList.clear();
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
//////////////////////////////////////////////////////////////////////////////
void GCSupplyItemList::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY

	BYTE totalNum;
	iStream.read( totalNum );
	if ( totalNum > MAX_SUPPLYITEM_LIST ) throw DisconnectException("GCSupplyItemList : 물건 개수가 제한을 초과했습니다.");

	for ( int i=0; i < totalNum ; ++i )
	{
		SupplyItemInfo* pSI = new SupplyItemInfo;

		iStream.read( pSI->ID );
		iStream.read( pSI->itemClass );
		iStream.read( pSI->itemType );
		iStream.read( pSI->grade );

		BYTE optionNum;
		iStream.read( optionNum );

		pSI->optionType.clear();

		for ( int j=0; j < optionNum ; ++j )
		{
			OptionType_t optionType;
			iStream.read( optionType );
			pSI->optionType.push_back( optionType );
		}
		
		iStream.read( pSI->num );
		iStream.read( pSI->timeLimit );

		addSupplyItemInfo( pSI );
	}

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////////////
// 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
//////////////////////////////////////////////////////////////////////////////
void GCSupplyItemList::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	BYTE totalNum = m_SupplyItemList.size();
	BYTE currentNum = 0;
	
	if ( totalNum > MAX_SUPPLYITEM_LIST ) 
	{
		totalNum = MAX_SUPPLYITEM_LIST;
	}

	oStream.write( totalNum );
	
	list<SupplyItemInfo*>::const_iterator itr = m_SupplyItemList.begin();
	list<SupplyItemInfo*>::const_iterator endItr = m_SupplyItemList.end();

	for ( ; itr != endItr, currentNum < totalNum ; ++itr )
	{
		SupplyItemInfo* pSI = *itr;
		Assert( pSI != NULL );

		oStream.write( pSI->ID );
		oStream.write( pSI->itemClass );
		oStream.write( pSI->itemType );
		oStream.write( pSI->grade );
		
		BYTE optionNum = pSI->optionType.size();
		oStream.write( optionNum );

		list<OptionType_t>::const_iterator oitr = pSI->optionType.begin();
		list<OptionType_t>::const_iterator endoItr = pSI->optionType.end();

		for ( ; oitr != endoItr ; ++oitr )
		{
			oStream.write( *oitr );
		}

		oStream.write( pSI->num );
		oStream.write( pSI->timeLimit );
		
		++currentNum;
	}

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////////////
void GCSupplyItemList::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	__BEGIN_DEBUG
		
	GCSupplyItemListHandler::execute( this , pPlayer );

	__END_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
PacketSize_t GCSupplyItemList::getPacketSize () const 
	throw ()
{ 
	__BEGIN_TRY
	__BEGIN_DEBUG

	PacketSize_t size = szBYTE;

	list<SupplyItemInfo*>::const_iterator itr = m_SupplyItemList.begin();
	list<SupplyItemInfo*>::const_iterator endItr = m_SupplyItemList.end();

	for ( ; itr != endItr ; ++itr )
	{
		size += (*itr)->getPacketSize();
	}

	return size;

	__END_DEBUG
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////////////
#ifdef __DEBUG_OUTPUT__
string GCSupplyItemList::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCSupplyItemList(";

	list<SupplyItemInfo*>::const_iterator itr = m_SupplyItemList.begin();
	list<SupplyItemInfo*>::const_iterator endItr = m_SupplyItemList.end();

	for ( ; itr != endItr ; ++itr )
	{
		msg << (*itr)->toString();
	}

	msg << ")";
	return msg.toString();
		
	__END_CATCH
}
#endif