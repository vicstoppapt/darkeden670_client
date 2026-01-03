//////////////////////////////////////////////////////////////////////////////
// Filename    : GCOtherModifyInfo.h 
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_OTHER_GEAR_INFO_H__
#define __GC_OTHER_GEAR_INFO_H__

#include "ModifyInfo.h"
#include "PacketFactory.h"
#include "GearInfo.h"

//////////////////////////////////////////////////////////////////////////////
// class GCOtherModifyInfo;
//////////////////////////////////////////////////////////////////////////////

class GCOtherGearInfo : public Packet
{
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_OTHER_GEAR_INFO; }
	PacketSize_t getPacketSize() const throw() { return szObjectID + m_pGearInfo->getSize(); }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName() const throw() { return "GCOtherGearInfo"; }
		std::string toString() const throw();
	#endif

public:
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	GearInfo* getGearInfo() const throw() { return m_pGearInfo; } 	
	void setGearInfo(GearInfo* pGearInfo) throw(Error) { m_pGearInfo = pGearInfo; }

private:
	ObjectID_t m_ObjectID;
	GearInfo* m_pGearInfo;
};


//////////////////////////////////////////////////////////////////////////////
// class GCOtherModifyInfoFactory;
//////////////////////////////////////////////////////////////////////////////

class GCOtherGearInfoFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCOtherGearInfo(); }

	#ifdef __DEBUG_OUTPUT__
		std::string getPacketName() const throw() { return "GCOtherGearInfo"; }
	#endif

	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_OTHER_GEAR_INFO; }
	PacketSize_t getPacketMaxSize() const throw() { return szObjectID + GearInfo::getMaxSize(); }
};


//////////////////////////////////////////////////////////////////////////////
// class GCOtherModifyInfoHandler;
//////////////////////////////////////////////////////////////////////////////

class GCOtherGearInfoHandler 
{
public:
	static void execute(GCOtherGearInfo* pGCOtherGearInfo, Player* pPlayer) throw(Error);
};

#endif
