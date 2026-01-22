//////////////////////////////////////////////////////////////////////
// 
// Filename    : GCInstanceDoungeonResult.h 
// Written By  : 
// 
//////////////////////////////////////////////////////////////////////

#ifndef __GC_INSTANCEDOUNGEON_RESULT_H__
#define __GC_INSTANCEDOUNGEON_RESULT_H__

// include files
#include <list>
#include "Packet.h"
#include "PacketFactory.h"
#include "GuildInfo.h"

typedef std::list<GuildInfo*> GuildInfoList;
typedef std::list<GuildInfo*>::const_iterator GuildInfoListConstItor;


//////////////////////////////////////////////////////////////////////
//
// class GCInstanceDoungeonResult;
//
// 클라이언트에 등록 대기중인 길드 리스트를 보낸다.
//
//////////////////////////////////////////////////////////////////////
#if __CONTENTS(__TIPOJYU_CASTLE)
class GCInstanceDoungeonResult : public Packet {

public :

	// constructor
	GCInstanceDoungeonResult() throw();

	// destructor
	~GCInstanceDoungeonResult() throw();
	
    // 입력스트림(버퍼)으로부터 데이타를 읽어서 패킷을 초기화한다.
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
		    
    // 출력스트림(버퍼)으로 패킷의 바이너리 이미지를 보낸다.
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);

	// execute packet's handler
	void execute(Player* pPlayer) throw(ProtocolException, Error);

	// get packet id
	PacketID_t getPacketID() const throw() { return PACKET_GC_INSTANCEDOUNGEON_RESULT; }
	
	// get packet's body size
	PacketSize_t getPacketSize() const throw();

	// get packet name
	string getPacketName() const throw() { return "GCInstanceDoungeonResult"; }
	
	// get packet's debug string
	string toString() const throw();
	
	DWORD	getExp()		const throw(){ return m_ExpBonus; }
	DWORD	getRankExp()	const throw(){ return m_RankExpBonus; }
	WORD	getRemainTime()	const throw(){ return m_RemainTime; }
	string	getTitleName()	const throw(){ return m_strDoungeonTitle; }

public:


private :
	
	string m_strDoungeonTitle;
	
	Exp_t m_ExpBonus;
	RankExp_t m_RankExpBonus;
	Duration_t m_RemainTime;
};


//////////////////////////////////////////////////////////////////////
//
// class GCInstanceDoungeonResultFactory;
//
// Factory for GCInstanceDoungeonResult
//
//////////////////////////////////////////////////////////////////////

class GCInstanceDoungeonResultFactory : public PacketFactory {

public :
	
	// create packet
	Packet* createPacket() throw() { return new GCInstanceDoungeonResult(); }

	// get packet name
	string getPacketName() const throw() { return "GCInstanceDoungeonResult"; }
	
	// get packet id
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_INSTANCEDOUNGEON_RESULT; }

	// get packet's max body size
	// *OPTIMIZATION HINT*
	// const static GCSystemMessagePacketMaxSize 를 정의, 리턴하라.
	PacketSize_t getPacketMaxSize() const throw() { return szBYTE + 200 + szExp + szRankExp + szDuration; }

};


//////////////////////////////////////////////////////////////////////
//
// class GCInstanceDoungeonResult;
//
//////////////////////////////////////////////////////////////////////

class GCInstanceDoungeonResultHandler {
	
public :
	
	// execute packet's handler
	static void execute(GCInstanceDoungeonResult* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};
#endif // __TIPOJYU_CASTLE
#endif
