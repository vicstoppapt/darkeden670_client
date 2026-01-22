//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectSupplyItem.h 
// Written By  : rappi76
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CG_SELECT_SUPPLYITEM_H__
#define __CG_SELECT_SUPPLYITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Packet.h"
#include "PacketFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class CGSelectSupplyItem;
//////////////////////////////////////////////////////////////////////////////

class CGSelectSupplyItem : public Packet 
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_CG_SELECT_SUPPLYITEM; }
	PacketSize_t getPacketSize() const throw() { return szObjectID; }
	string getPacketName() const throw() { return "CGSelectSupplyItem"; }
	string toString() const throw();

public:
	ZoneID_t getSelectID() const throw()  { return m_SelectID; }
	void setSelectID(ObjectID_t SelectID) throw() { m_SelectID = SelectID; }

private:
	ObjectID_t   m_SelectID;

};

//////////////////////////////////////////////////////////////////////////////
// class CGSelectSupplyItemFactory;
//////////////////////////////////////////////////////////////////////////////

class CGSelectSupplyItemFactory : public PacketFactory 
{
	Packet* createPacket() throw() { return new CGSelectSupplyItem(); }
	string getPacketName() const throw() { return "CGSelectSupplyItem"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_CG_SELECT_SUPPLYITEM; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID; }
};

//////////////////////////////////////////////////////////////////////////////
// class CGSelectSupplyItemHandler;
//////////////////////////////////////////////////////////////////////////////

class CGSelectSupplyItemHandler 
{
public:
	static void execute(CGSelectSupplyItem* pCGSelectSupplyItem, Player* pPlayer) throw(Error);
};

#endif
