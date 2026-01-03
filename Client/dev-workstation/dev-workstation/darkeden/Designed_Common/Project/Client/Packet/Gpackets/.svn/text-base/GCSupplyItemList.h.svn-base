//////////////////////////////////////////////////////////////////////////////
// Filename    : GCSupplyItemList.h 
// Written By  : rappi76
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_SUPPLYITEM_LIST_H__
#define __GC_SUPPLYITEM_LIST_H__

#include "Packet.h"
#include "PacketFactory.h"
#include <list>

using namespace std;


#define MAX_SUPPLYITEM_LIST 20

typedef struct _SupplyItemInfo
{
	int getPacketSize() const
	{ 
		return szObjectID + 
				szBYTE + 
				szItemType + 
				szGrade +
				szBYTE + optionType.size() +
				szItemNum +
				szDWORD;
	}

	static int getPacketMaxSize() 
	{ 
		return szObjectID + 
				szBYTE + 
				szItemType + 
				szGrade +
				szBYTE + 255 +
				szItemNum +
				szDWORD;
	}

	string toString() const
	{
		StringStream msg;
		msg << "SupplyItem( "
			<< "ID : " << ID
			<< ", ItemClass : " << (int)itemClass
			<< ", ItemType : " << itemType
			<< ", Grade : " << grade
			<< ", Options : (";

		list<OptionType_t>::const_iterator itr = optionType.begin();
		list<OptionType_t>::const_iterator endItr = optionType.end();

		for ( ; itr != endItr ; ++itr )
		{
			msg << *itr << ", ";
		}

		msg << "), Num : " << num
			<< ", TimeLimit : " << timeLimit;

		return msg.toString();
	}

	ObjectID_t     		ID;
	BYTE           		itemClass;
	ItemType_t     		itemType;
	Grade_t				grade;
	list<OptionType_t>  optionType;
	ItemNum_t      		num;
	DWORD				timeLimit;
} SupplyItemInfo;

//////////////////////////////////////////////////////////////////////////////
// class GCSupplyItemList;
//////////////////////////////////////////////////////////////////////////////

class GCSupplyItemList : public Packet 
{
public:
	GCSupplyItemList() throw();
	virtual ~GCSupplyItemList() throw();

	void read(SocketInputStream & iStream) throw(ProtocolException, Error);
	void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_SUPPLYITEM_LIST; }
	PacketSize_t getPacketSize() const throw();
#ifdef __DEBUG_OUTPUT__	
	string getPacketName() const throw() { return "GCSupplyItemList"; }
	string toString() const throw();
#endif
public:
	void		addSupplyItemInfo( SupplyItemInfo* pSI ) { m_SupplyItemList.push_back( pSI ); }
	SupplyItemInfo*	popSupplyItemInfo( ) { SupplyItemInfo* pRet = m_SupplyItemList.front(); if ( pRet ) m_SupplyItemList.pop_front(); return pRet; }

private:
	list<SupplyItemInfo*> m_SupplyItemList;
};


//////////////////////////////////////////////////////////////////////////////
// class GCSupplyItemListFactory;
//////////////////////////////////////////////////////////////////////////////

class GCSupplyItemListFactory : public PacketFactory 
{
public :
	Packet* createPacket() throw() { return new GCSupplyItemList(); }
	string getPacketName() const throw() { return "GCSupplyItemList"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_SUPPLYITEM_LIST; }
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		PacketSize_t size = szBYTE;
		size += SupplyItemInfo::getPacketMaxSize() * MAX_SUPPLYITEM_LIST;

		return size;
	}
};


//////////////////////////////////////////////////////////////////////////////
// class GCSupplyItemListHandler;
//////////////////////////////////////////////////////////////////////////////

class GCSupplyItemListHandler 
{
public :
	static void execute(GCSupplyItemList* pPacket, Player* pPlayer) throw(ProtocolException, Error);

};

#endif
