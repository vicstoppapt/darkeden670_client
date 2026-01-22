//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCInstanceDoungeonLobby.cpp 
// Written By  : rappi76
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"

#include "GCInstanceDoungeonLobby.h"


//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
#if __CONTENTS(__TIPOJYU_CASTLE)
GCInstanceDoungeonLobby::GCInstanceDoungeonLobby()
	throw()
{
	m_wButtonSize	= 0;
}

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
GCInstanceDoungeonLobby::~GCInstanceDoungeonLobby()
	throw()
{
	m_wButtonSize	= 0;

	TInstanceDoungeonInfoItr subitr1 = m_DoungeonList.begin();

	while(subitr1 != m_DoungeonList.end())
	{
		InstanceDoungeonInfo *pInstanceDoungeonInfo = (*subitr1);
		subitr1 = m_DoungeonList.erase(subitr1);

		if(pInstanceDoungeonInfo != NULL)
        {
			delete pInstanceDoungeonInfo;
            pInstanceDoungeonInfo = NULL;
		}
	}
}

//////////////////////////////////////////////////////////////////////
// �Է½�Ʈ��(����)���κ��� ����Ÿ�� �о ��Ŷ�� �ʱ�ȭ�Ѵ�.
//////////////////////////////////////////////////////////////////////
void GCInstanceDoungeonLobby::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	
	BYTE szDoungeonTitle;
	BYTE szDoungeonListCount;
	BYTE szDoungeonDesc;
	
	iStream.read( m_ObjectID );
	iStream.read( m_NPCID );

	iStream.read( szDoungeonTitle );
	iStream.read( m_strDoungeonTitle, szDoungeonTitle );

	iStream.read( szDoungeonListCount);
	for(int i = 0 ; i < szDoungeonListCount; ++i)
	{
		InstanceDoungeonInfo *pInstanceDoungeonInfo = new InstanceDoungeonInfo();
		pInstanceDoungeonInfo->read(iStream);
		m_DoungeonList.push_back(pInstanceDoungeonInfo);
	}
	
	iStream.read( szDoungeonDesc );
	iStream.read( m_strDoungeonDesc, szDoungeonDesc );

	m_wButtonSize	= szDoungeonListCount;

	__END_CATCH
}

		    
//////////////////////////////////////////////////////////////////////
// ��½�Ʈ��(����)���� ��Ŷ�� ���̳ʸ� �̹����� ������.
//////////////////////////////////////////////////////////////////////
void GCInstanceDoungeonLobby::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	
	BYTE szDoungeonTitle;
	BYTE szDoungeonDesc;
	BYTE szDoungeonListCount;
	
	oStream.write( m_ObjectID );
	oStream.write( m_NPCID );
	
	szDoungeonTitle = m_strDoungeonTitle.length();
	szDoungeonListCount = m_DoungeonList.size();
	szDoungeonDesc = m_strDoungeonDesc.length();
		
	oStream.write( szDoungeonTitle );
	oStream.write( m_strDoungeonTitle);
	
	oStream.write(szDoungeonListCount);
	TInstanceDoungeonInfoItr itr = m_DoungeonList.begin();
	for ( ; itr != m_DoungeonList.end(); itr++ )
	{
		(*itr)->write( oStream );
	}
	
	oStream.write( szDoungeonDesc );
	oStream.write( m_strDoungeonDesc);


	__END_CATCH
}

//////////////////////////////////////////////////////////////////////
// execute packet's handler
//////////////////////////////////////////////////////////////////////
void GCInstanceDoungeonLobby::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCInstanceDoungeonLobbyHandler::execute( this , pPlayer );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet size
//////////////////////////////////////////////////////////////////////
PacketSize_t GCInstanceDoungeonLobby::getPacketSize() const
	throw()
{
	__BEGIN_TRY

	PacketSize_t size = 0;
	
	size += szObjectID + szNPCID; 
	size += szBYTE + m_strDoungeonTitle.size();
	
	TInstanceDoungeonInfoItr itr = m_DoungeonList.begin();
	for ( ; itr != m_DoungeonList.end(); itr++ )
	{
		size += (*itr)->getSize();
	}
	
	size += szBYTE + m_strDoungeonDesc.size();
	
	return size;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// get packet's debug string
//////////////////////////////////////////////////////////////////////
string GCInstanceDoungeonLobby::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	
	msg << "GCInstanceDoungeonLobby("
		<< "DoungeonTitle:" << m_strDoungeonTitle
		<< "DoungeonDesc:" << m_strDoungeonDesc
		<< ")";
	
	return msg.toString();
		
	__END_CATCH
}

#endif //__TIPOJYU_CASTLE