//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAuthXTrap.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_AUTH_XTRAP_H__
#define __GC_AUTH_XTRAP_H__

#include "Packet.h"
#include "PacketFactory.h"

#ifdef __GAME_CLIENT__ 
#include "XTrap4Client.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// class GCAuthXTrap;
// 
//////////////////////////////////////////////////////////////////////////////

class GCAuthXTrap : public Packet 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_AUTH_XTRAP; }
	
	PacketSize_t getPacketSize() const throw() { return szshort + szBYTE + szAuth ; }
	string getPacketName() const throw() { return "GCAuthXTrap"; }
	string toString() const throw();
	
	BYTE * getAuthData() const throw() { return (BYTE *)m_AuthData; };
	
	BYTE * getKey() const throw() { return (BYTE *)m_AuthData; }
	void setKey(BYTE * key) throw() { memcpy(m_AuthData , key, szAuth); }
	
	short m_shCmdFlag;
private:
	
	
	BYTE m_AuthData[128];
	
};


//////////////////////////////////////////////////////////////////////////////
// class GCAuthKeyFactory;
//////////////////////////////////////////////////////////////////////////////


class GCAuthXTrapFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCAuthXTrap(); }
	string getPacketName() const throw() { return "GCAuthXTrap"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_AUTH_XTRAP; }
	PacketSize_t getPacketMaxSize() const throw() { return szshort + szBYTE + szAuth ; }

};


//////////////////////////////////////////////////////////////////////////////
// class GCAuthKeyHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAuthXTrapHandler 
{
public:
	static void execute(GCAuthXTrap* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
