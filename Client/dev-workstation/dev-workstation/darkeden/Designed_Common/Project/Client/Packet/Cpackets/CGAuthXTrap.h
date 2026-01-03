//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAuthXTrap.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_AUTH_XTRAP_H__
#define __CG_AUTH_XTRAP_H__

#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGAuthXTrap;
//
//////////////////////////////////////////////////////////////////////////////

class CGAuthXTrap : public Packet 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_AUTH_XTRAP; }
	string getPacketName() const throw() { return "CGAuthXTrap"; }
	string toString() const throw();

	PacketSize_t getPacketSize() const throw() { return szshort + szBYTE + szAuth ; }
	
	BYTE * getAuthData() const throw() { return (BYTE *)m_AuthData; };
	
	BYTE * getKey() const throw() { return (BYTE *)m_AuthData;; }
	void setKey(BYTE * key) throw() { memcpy(m_AuthData , key, szAuth); }
	short m_shCmdFlag;
private:

	
	BYTE m_AuthData[szAuth];
	
};


//////////////////////////////////////////////////////////////////////////////
// class CGAuthKeyFactory;
//////////////////////////////////////////////////////////////////////////////


class CGAuthXTrapFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new CGAuthXTrap(); }
	string getPacketName() const throw() { return "CGAuthXTrap"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_AUTH_XTRAP; }
	PacketSize_t getPacketMaxSize() const throw() { return szshort + szBYTE + szAuth ; }
	
};


//////////////////////////////////////////////////////////////////////////////
// class CGAuthXTrapHandler;
//////////////////////////////////////////////////////////////////////////////

class CGAuthXTrapHandler 
{
public:
	static void execute(CGAuthXTrap* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
