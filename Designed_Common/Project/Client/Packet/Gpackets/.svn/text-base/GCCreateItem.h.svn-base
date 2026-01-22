//////////////////////////////////////////////////////////////////////////////
// Filename    : GCCreateItem.h 
// Written By  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __GC_CREATE_ITEM_H__
#define __GC_CREATE_ITEM_H__

#include "Packet.h"
#include "PacketFactory.h"
#include "PCItemInfo.h"




#if __CONTENTS(__PCITEMINFO)
//////////////////////////////////////////////////////////////////////////////
// class GCCreateItem;
//////////////////////////////////////////////////////////////////////////////

class GCCreateItem : public Packet 
{
public:
	GCCreateItem() throw();
	virtual ~GCCreateItem() throw() {}
public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_CREATE_ITEM; }
	PacketSize_t getPacketSize() const throw() 
	{ 
		PacketSize_t packetSize;
		
		packetSize = szCoordInven * 2 +		// 아이템 X, Y 좌표
			m_PCItemInfo.getSize() +		// 아이템 정보
			szObjectID;    					// 인벤토리 오브젝트 아이디
		
		return packetSize;
	}
	string getPacketName() const throw() { return "GCCreateItem"; }
	string toString() const throw();

public:
	CoordInven_t getInvenX() const throw() { return m_InvenX; }
	void setInvenX(CoordInven_t InvenX) throw() { m_InvenX = InvenX; }

	CoordInven_t getInvenY() const throw() { return m_InvenY; }
	void setInvenY(CoordInven_t InvenY) throw() { m_InvenY = InvenY; }
	
	void SetPCItemInfo(PCItemInfo& pcItemInfo) { m_PCItemInfo = pcItemInfo; }
	PCItemInfo* GetPCItemInfo() { return &m_PCItemInfo; }

	// 2007 03 29 Add
	ObjectID_t getInventoryItemObjectID() const throw() { return m_InventoryItemObjectID; }
	void setInventoryItemObjectID(ObjectID_t InventoryItemObjectID) throw() { m_InventoryItemObjectID = InventoryItemObjectID; }

private:
	CoordInven_t   		m_InvenX;       // 인벤토리 X 좌표
	CoordInven_t   		m_InvenY;       // 인벤토리 Y 좌표
	
	PCItemInfo m_PCItemInfo;
	
	// 2007.03.29 Add
	ObjectID_t			m_InventoryItemObjectID;		// 보조 인벤토리인지 확인하기 위하여 추가
};


//////////////////////////////////////////////////////////////////////////////
// class GCCreateItemFactory;
//////////////////////////////////////////////////////////////////////////////

class GCCreateItemFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCCreateItem(); }
	string getPacketName() const throw() { return "GCCreateItem"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_CREATE_ITEM; }
	PacketSize_t getPacketMaxSize() const throw() 
	{
 		PacketSize_t packetSize = 0;
		
		packetSize = szCoordInven +		// 아이템 X 좌표
					szCoordInven +				// 아이템 Y 좌표
					szObjectID;					// 인벤토리 오브젝트 아이디
		packetSize +=	PCItemInfo::getMaxSize();
		return packetSize;

	}
};


//////////////////////////////////////////////////////////////////////////////
// class GCCreateItemHandler;
//////////////////////////////////////////////////////////////////////////////

class GCCreateItemHandler 
{
public:
	static void execute(GCCreateItem* pPacket, Player* pPlayer) throw(Error);

};
#else //__PCITEMINFO
//////////////////////////////////////////////////////////////////////////////
// class GCCreateItem;
//////////////////////////////////////////////////////////////////////////////

class GCCreateItem : public Packet 
{
public:
	GCCreateItem() throw();

public:
    void read(SocketInputStream & iStream) throw(ProtocolException, Error);
    void write(SocketOutputStream & oStream) const throw(ProtocolException, Error);
	void execute(Player* pPlayer) throw(ProtocolException, Error);
	PacketID_t getPacketID() const throw() { return PACKET_GC_CREATE_ITEM; }
	PacketSize_t getPacketSize() const throw() 
	{ 
		return szObjectID +  // 아이템 오브젝트 ID
			szBYTE +         // 아이템 클래스
			szItemType +     // 아이템 타입
			szBYTE + m_OptionType.size() +   // 아이템 옵션
			szDurability +   // 아이템 내구도
			szSilver +       // 아이템 은 도금량
			szGrade +        // 아이템 등급
			szEnchantLevel + // 아이템 인챈트 레벨
			szItemNum +      // 아이템 숫자
			szCoordInven +   // 아이템 X 좌표
			szCoordInven +   // 아이템 Y 좌표
			szObjectID	// 보조 인벤토리 유무
//20071009 by diesirace 서드아이템옵션 추가 (서드 옵션 달린 아이템은 만들어질리가 절대 없단다...)
//			+ szBYTE + m_ThirdOptionType.size() +	// 서드인첸트 옵션리스트와 리스트 사이즈
//			szBYTE									// 서드인첸트  타입
#if __CONTENTS(__INTERNATIONAL_PREMIUM_SYSTEM)
			 + szBYTE								// 캐쉬아이템
#endif //__INTERNATIONAL_PREMIUM_SYSTEM
			;
	}

#ifdef __DEBUG_OUTPUT__
	std::string getPacketName() const throw() { return "GCCreateItem"; }
	std::string toString() const throw();
#endif

public:
	ObjectID_t getObjectID() const throw() { return m_ObjectID; }
	void setObjectID(ObjectID_t ObjectID) throw() { m_ObjectID = ObjectID; }

	BYTE getItemClass() const throw() { return m_ItemClass; }
	void setItemClass(BYTE ItemClass) throw() { m_ItemClass = ItemClass; }

	ItemType_t getItemType() const throw() { return m_ItemType; }
	void setItemType(ItemType_t ItemType) throw() { m_ItemType = ItemType; }

	int getOptionTypeSize() const throw() { return m_OptionType.size(); }
	const std::list<OptionType_t>& getOptionType() const throw() { return m_OptionType; }
	OptionType_t popOptionType() throw()
	{
		if (m_OptionType.empty()) return 0;
		OptionType_t optionType = m_OptionType.front();
		m_OptionType.pop_front();
		return optionType;
	}
	void addOptionType(OptionType_t OptionType) throw() { m_OptionType.push_back( OptionType ); }
	void setOptionType(const std::list<OptionType_t>& OptionTypes) throw() { m_OptionType = OptionTypes; }

	Durability_t getDurability() const throw() { return m_Durability; }
	void setDurability(Durability_t Durability) throw() { m_Durability = Durability; }

	Silver_t getSilver() const throw() { return m_Silver; }
	void setSilver(Silver_t silver) throw() { m_Silver = silver; }

	Grade_t getGrade() const throw() { return m_Grade; }
	void setGrade(Grade_t grade) throw() { m_Grade = grade; }

	EnchantLevel_t getEnchantLevel() const throw() { return m_EnchantLevel; }
	void setEnchantLevel(EnchantLevel_t level) throw() { m_EnchantLevel = level; }

	ItemNum_t getItemNum() const throw() { return m_ItemNum; }
	void setItemNum(ItemNum_t num) throw() { m_ItemNum = num; }

	CoordInven_t getInvenX() const throw() { return m_InvenX; }
	void setInvenX(CoordInven_t InvenX) throw() { m_InvenX = InvenX; }

	CoordInven_t getInvenY() const throw() { return m_InvenY; }
	void setInvenY(CoordInven_t InvenY) throw() { m_InvenY = InvenY; }

	ObjectID_t getInventoryItemObjectID() const throw() {return m_InventoryItemObjectID;}
	void setInventoryItemObjectID(ObjectID_t InventoryItemObjectID) throw() {m_InventoryItemObjectID = InventoryItemObjectID;}

#if __CONTENTS(__INTERNATIONAL_PREMIUM_SYSTEM)
	void setCashItem(BYTE cashItem) throw()					{m_CashItem = cashItem;}
	BYTE getCashItem()										{return m_CashItem;}
#endif //__INTERNATIONAL_PREMIUM_SYSTEM	
	
	void addThirdOptionType(OptionType_t ThirdOptionType) throw() { m_OptionType.push_back( ThirdOptionType ); }
	void setThirdOptionType(const std::list<OptionType_t>& ThirdOptionType) throw() { m_ThirdOptionType = ThirdOptionType; }
	int getThirdOptionTypeSize() const throw() { return m_ThirdOptionType.size(); }
	const std::list<OptionType_t>& getThirdOptionType() const throw() { return m_ThirdOptionType; }
	OptionType_t popThirdOptionType() throw() 
	{ 
		if (m_ThirdOptionType.empty()) return 0;
		OptionType_t ThirdoptionType = m_ThirdOptionType.front(); 
		m_ThirdOptionType.pop_front(); 
		return ThirdoptionType; 
	}

	BYTE getThirdEnchantType() const throw()				{ return m_ThirdEnchantType; }
	void setThirdEnchantType(BYTE ThirdEnchantType)throw()	{m_ThirdEnchantType = ThirdEnchantType; }

private:
	ObjectID_t     		m_ObjectID;     // 오브젝트 ID
	BYTE           		m_ItemClass;    // 아이템 클래스
	ItemType_t     		m_ItemType;     // 아이템 타입
	std::list<OptionType_t>  m_OptionType;   // 옵션 타입
	Durability_t   		m_Durability;   // 내구성
	Silver_t       		m_Silver;       // 은 도금량
	Grade_t       		m_Grade;        // 등급
	EnchantLevel_t 		m_EnchantLevel; // 인챈트 레벨
	ItemNum_t      		m_ItemNum;      // 아이템의 숫자
	CoordInven_t   		m_InvenX;       // 인벤토리 X 좌표
	CoordInven_t   		m_InvenY;       // 인벤토리 Y 좌표
	ObjectID_t			m_InventoryItemObjectID;	// 보조 인벤토리 유무
	
#if __CONTENTS(__INTERNATIONAL_PREMIUM_SYSTEM)
	BYTE				m_CashItem;			// this item is cash
#endif //__INTERNATIONAL_PREMIUM_SYSTEM
	std::list<OptionType_t> m_ThirdOptionType;      // item Third option type
	BYTE				m_ThirdEnchantType;			// Third Enchant type
};


//////////////////////////////////////////////////////////////////////////////
// class GCCreateItemFactory;
//////////////////////////////////////////////////////////////////////////////

class GCCreateItemFactory : public PacketFactory 
{
public:
	Packet* createPacket() throw() { return new GCCreateItem(); }
	std::string getPacketName() const throw() { return "GCCreateItem"; }
	PacketID_t getPacketID() const throw() { return Packet::PACKET_GC_CREATE_ITEM; }
	PacketSize_t getPacketMaxSize() const throw() 
	{ 
		return szObjectID +  // 아이템 오브젝트 ID
			szBYTE +         // 아이템 클래스
			szItemType +     // 아이템 타입
			szBYTE + 255 +   // 아이템 옵션
			szDurability +   // 아이템 내구도
			szSilver +       // 아이템 은 도금량
			szGrade +        // 아이템 등급
			szEnchantLevel + // 아이템 인챈트 레벨
			szItemNum +      // 아이템 숫자
			szCoordInven +   // 아이템 X 좌표
			szCoordInven +   // 아이템 Y 좌표
			szObjectID;		 // 보조 인벤토리 유무
//20071009 by diesirace 서드아이템옵션 추가 (서드 옵션 달린 아이템은 만들어질리가 절대 없단다...)
//			+ szBYTE + 255 + // 서드인첸트 옵션리스트와 리스트 사이즈
//			szBYTE			 // 서드인첸트  타입
#if __CONTENTS(__INTERNATIONAL_PREMIUM_SYSTEM)
			 + szBYTE		 //	캐쉬 아이템
#endif
			;
	}
};


//////////////////////////////////////////////////////////////////////////////
// class GCCreateItemHandler;
//////////////////////////////////////////////////////////////////////////////

class GCCreateItemHandler 
{
public:
	static void execute(GCCreateItem* pPacket, Player* pPlayer) throw(Error);

};
#endif //__PCITEMINFO
#endif //__GC_CREATE_ITEM_H__