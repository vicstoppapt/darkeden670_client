//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectAllSupplyItem.h 
// Written By  : rappi76
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_SELECT_ALL_SUPPLYITEM_H__
#define __CG_SELECT_ALL_SUPPLYITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGSelectAllSupplyItem;
//////////////////////////////////////////////////////////////////////////////

class CGSelectAllSupplyItem : public Packet 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_SELECT_ALL_SUPPLYITEM; }
	PacketSize_t getPacketSize() const throw() { return 0; }
	string getPacketName() const throw() { return "CGSelectAllSupplyItem"; }
	string toString() const throw();

public:

private:

};

//////////////////////////////////////////////////////////////////////////////
// class CGSelectAllSupplyItemFactory;
//////////////////////////////////////////////////////////////////////////////

class CGSelectAllSupplyItemFactory : public PacketFactory 
{
	Packet* createPacket() throw() { return new CGSelectAllSupplyItem(); }
	string getPacketName() const throw() { return "CGSelectAllSupplyItem"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_SELECT_ALL_SUPPLYITEM; }
	PacketSize_t getPacketMaxSize() const throw() { return 0; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGSelectAllSupplyItemHandler;
//////////////////////////////////////////////////////////////////////////////

class CGSelectAllSupplyItemHandler 
{
public:
	static void execute(CGSelectAllSupplyItem* pCGSelectAllSupplyItem, Player* pPlayer) throw(Error);
};

#endif
