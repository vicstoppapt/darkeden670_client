//////////////////////////////////////////////////////////////////////////////
// Filename    : GCOtherModifyInfo.cpp 
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "Client_PCH.h"
#include "GCOtherGearInfo.h"

void GCOtherGearInfo::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read( m_ObjectID );
	m_pGearInfo = new GearInfo();
	m_pGearInfo->read( iStream );

	__END_CATCH
}
		    
void GCOtherGearInfo::write ( SocketOutputStream & oStream ) 
     const throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	oStream.write( m_ObjectID );
	m_pGearInfo->write( oStream );
	
	__END_CATCH
}

void GCOtherGearInfo::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCOtherGearInfoHandler::execute( this , pPlayer );
		
	__END_CATCH
}

#ifdef __DEBUG_OUTPUT__
std::string GCOtherGearInfo::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "GCOtherGearInfo("
		<< "ObjectID::" << (int)m_ObjectID << ","
		<< ")";
	return msg.toString();

	__END_CATCH
}
#endif