//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAuthKey.cpp 
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////
#include "Client_PCH.h"
#include "GCAuthXTrap.h"

void GCAuthXTrap::read ( SocketInputStream & iStream ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	iStream.read(m_shCmdFlag);
	BYTE sizeAuth =0;
	iStream.read(sizeAuth);
	
	if ( sizeAuth == 0 )
		throw InvalidProtocolException("sizeAuth == 0");

	if ( sizeAuth > szAuth )
		throw InvalidProtocolException("sizeAuth too long name length");
	
	iStream.read((char *) m_AuthData , sizeAuth);

	__END_CATCH
}
		    
void GCAuthXTrap::write ( SocketOutputStream & oStream ) const 
     throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	
	
	oStream.write(m_shCmdFlag);
	oStream.write(szAuth);
	oStream.write( (char *)m_AuthData, szAuth );

	__END_CATCH
}

void GCAuthXTrap::execute ( Player * pPlayer ) 
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
		
	GCAuthXTrapHandler::execute( this , pPlayer );

	__END_CATCH
}

string GCAuthXTrap::toString () const
       throw ()
{
	__BEGIN_TRY
		
	StringStream msg;
	msg << "GCAuthXTrap("
		<< "Key:" << m_AuthData 
		<< ")" ;
	return msg.toString();
		
	__END_CATCH
}


