//////////////////////////////////////////////////////////////////////////////
// Filename    : GCAddSlyph.h 
// Written By  : rappi76
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_ADD_SYLPH_H__
#define __GC_ADD_SYLPH_H__

#include "Packet.h"
#include "PacketFactory.h"


//////////////////////////////////////////////////////////////////////////////
// class GCAddSlyph;
//
// 시야 안에 고속 Slyph 가 들어왔을 경우, 이 패킷에 Slyph 정보를 담아서 전송받는다.
//////////////////////////////////////////////////////////////////////////////

class GCAddSylph : public Packet 
{
public:
	virtual ~GCAddSylph() throw() {}
	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
	PacketID_t getPacketID() const throw() { return PACKET_GC_ADD_SYLPH; }
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
	PacketSize_t getPacketSize() const throw();

	string getPacketName() const throw() { return "GCAddSylph"; }
	string toString() const throw();

public:
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t creatureID) throw() { m_ObjectID = creatureID; }

	uchar getSylphType() { return m_SylphType; }
	void setSylphType(uchar Type) { m_SylphType = Type; }

#if __CONTENTS(__SECOND_TRANSFORTER)
	ItemType_t getWingItemType() { return m_WingItemType; }
	void setWingItemType(ItemType_t ItemType) { m_WingItemType = ItemType; }
#endif //__SECOND_TRANSFORTER

	Color_t getWingBodyColor() { return m_WingBodyColor; }
	void setWingBodyColor(Color_t Color) { m_WingBodyColor = Color; }
	
	Color_t getWingEffectColor() { return m_WingEffectColor; }
	void setWingEffectColor(Color_t Color) { m_WingEffectColor = Color; }

private:
	ObjectID_t   m_ObjectID;

#if __CONTENTS(__SECOND_TRANSFORTER)
	ItemType_t m_WingItemType;
#endif //__SECOND_TRANSFORTER

	uchar m_SylphType;
	Color_t m_WingBodyColor;
	Color_t m_WingEffectColor;
};


//////////////////////////////////////////////////////////////////////////////
// class GCAddSlyphFactory;
//////////////////////////////////////////////////////////////////////////////

class GCAddSylphFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCAddSylph(); }
	string getPacketName() const throw() { return "GCAddSlyph"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_ADD_SYLPH; }
	PacketSize_t getPacketMaxSize() const throw();

};

//////////////////////////////////////////////////////////////////////////////
// class GCAddSlyphHandler;
//////////////////////////////////////////////////////////////////////////////

class GCAddSylphHandler 
{
public:
	static void execute(GCAddSylph* pPacket, Player* pPlayer) throw(Error);

};

#endif
