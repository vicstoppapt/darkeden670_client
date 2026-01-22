//----------------------------------------------------------------------
// MServerItemTable.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MServerItemTable.h"
#include "MItem.h"
#include "MItemTable.h"
#include <fstream>

//----------------------------------------------------------------------
//
// SERVER_ITEMTABLE_INFO
//
//----------------------------------------------------------------------
SERVER_ITEMTABLE_INFO::SERVER_ITEMTABLE_INFO()
{
}

SERVER_ITEMTABLE_INFO::~SERVER_ITEMTABLE_INFO()
{
}

//----------------------------------------------------------------------
// Save To File
//----------------------------------------------------------------------
void			
SERVER_ITEMTABLE_INFO::SaveToFile(std::ofstream& file)
{
	HName.SaveToFile( file );
	EName.SaveToFile( file );
	Description.SaveToFile( file );
	file.write((const char*)&Weight, 4);
	file.write((const char*)&Price, 4);
	file.write((const char*)&Durability, 4);
	file.write((const char*)&GridWidth, 4);
	file.write((const char*)&GridHeight, 4);
	file.write((const char*)&Defense, 4);
	file.write((const char*)&MinDamage, 4);
	file.write((const char*)&MaxDamage, 4);
	file.write((const char*)&MPPlus, 4);
	file.write((const char*)&Range, 4);			// 총 길이
	file.write((const char*)&Bullet, 4);			// 총알 개수
	file.write((const char*)&ToHit, 4);			// tohit bonus
	file.write((const char*)&MotorCarry, 4);		// 오토바이 운반 가능무게
	file.write((const char*)&HPRecover, 4);		// HP 회복 수치
	file.write((const char*)&MPRecover, 4);		// MP 회복 수치
	file.write((const char*)&Pocket, 4);			// 벨트 크기
	file.write((const char*)&RequireSTR, 4);	
	file.write((const char*)&RequireDEX, 4);
	file.write((const char*)&RequireINT, 4);
	file.write((const char*)&RequireSUM, 4);
	file.write((const char*)&RequireLevel, 4);
	file.write((const char*)&RequireGender, 4);
	file.write((const char*)&RequirAdvancementLevel, 4);
	file.write((const char*)&MaxSilver, 4);
	file.write((const char*)&Speed, 4);
	file.write((const char*)&Protection, 4);
	file.write((const char*)&Charge, 4);
	file.write((const char*)&CriticalHit, 4);

	file.write((const char*)&UpgradeCrashPercent, 4);

	int DefaultOptionListSize = DefaultOptionList.size();
	file.write((const char*)&DefaultOptionListSize, 4);
	std::list<int>::iterator itr = DefaultOptionList.begin();

	while(itr != DefaultOptionList.end())
	{
		int Option = *itr;
		file.write((const char*)&Option, 4);

		itr++;
	}

	file.write((const char*)&ItemStyle, 4);
	file.write((const char*)&Race, 4);

#if __CONTENTS(__TUNING_ITEM)
	file.write((const char*)&TuningItmeClass, 4);
	file.write((const char*)&TuningItmeType, 4);
#endif //__TUNING_ITEM
#if __CONTENTS(__ADD_MAGICPROTECTION)
	file.write((const char*)&MagicProtection, 4);
#endif
}

//----------------------------------------------------------------------
// Load To File
//----------------------------------------------------------------------
void			
SERVER_ITEMTABLE_INFO::LoadFromFile(ivfstream& file)
{
	HName.LoadFromFile( file );
	EName.LoadFromFile( file );
	Description.LoadFromFile( file );
	file.read((char*)&Weight, 4);
	file.read((char*)&Price, 4);
	file.read((char*)&Durability, 4);
	file.read((char*)&GridWidth, 4);
	file.read((char*)&GridHeight, 4);
	file.read((char*)&Defense, 4);
	file.read((char*)&MinDamage, 4);
	file.read((char*)&MaxDamage, 4);
	file.read((char*)&MPPlus, 4);
	file.read((char*)&Range, 4);			// 총 길이
	file.read((char*)&Bullet, 4);			// 총알 개수
	file.read((char*)&ToHit, 4);			// tohit bonus
	file.read((char*)&MotorCarry, 4);		// 오토바이 운반 가능무게
	file.read((char*)&HPRecover, 4);		// HP 회복 수치
	file.read((char*)&MPRecover, 4);		// MP 회복 수치
	file.read((char*)&Pocket, 4);			// 벨트 크기
	file.read((char*)&RequireSTR, 4);	
	file.read((char*)&RequireDEX, 4);
	file.read((char*)&RequireINT, 4);
	file.read((char*)&RequireSUM, 4);
	file.read((char*)&RequireLevel, 4);
	file.read((char*)&RequireGender, 4);
	file.read((char*)&RequirAdvancementLevel, 4);
	file.read((char*)&MaxSilver, 4);
	file.read((char*)&Speed, 4);
	file.read((char*)&Protection, 4);
	file.read((char*)&Charge, 4);
	file.read((char*)&CriticalHit, 4);

	file.read((char*)&UpgradeCrashPercent, 4);

	int DefaultOptionListSize = 0;
	file.read((char*)&DefaultOptionListSize, 4);
	
	for(int i = 0; i < DefaultOptionListSize; i++)
	{
		DWORD TempOptionType = 0;
		file.read((char*)&TempOptionType, 4);
		DefaultOptionList.push_back(BYTE(TempOptionType));
	}
	
	file.read((char*)&ItemStyle, 4);

	file.read((char*)&ElementalType, 4);
	file.read((char*)&Elemental, 4);
	file.read((char*)&Race, 4);

#if __CONTENTS(__TUNING_ITEM)
	file.read((char*)&TuningItmeClass, 4);
	file.read((char*)&TuningItmeType, 4);
#endif //__TUNING_ITEM
#if __CONTENTS(__ADD_MAGICPROTECTION)
	file.read((char*)&MagicProtection, 4);
#endif
}


//----------------------------------------------------------------------
//
// SERVER_ITEMCLASS_TABLE
//
//----------------------------------------------------------------------
SERVER_ITEMCLASS_TABLE::SERVER_ITEMCLASS_TABLE()
{
}

SERVER_ITEMCLASS_TABLE::~SERVER_ITEMCLASS_TABLE()
{
}

//----------------------------------------------------------------------
// Affect To ItemTable
//----------------------------------------------------------------------
// client의 item table에 필요한 정보를 저장시킨다.
//
// return값이 -1이면 제대로 된 경우이고
//				-2이면 itemClass의 개수가 틀린 경우
//				아니라면... 오류가 있는 itemClass의 ID이다.
//----------------------------------------------------------------------
int		
SERVER_ITEMCLASS_TABLE::AffectToItemTable( ITEMCLASS_TABLE& itemTable )
{
	//---------------------------------------------------
	// 전체class의 size 체크
	//---------------------------------------------------
	int clientClassSize = itemTable.GetSize();
	int serverClassSize = GetSize();

	if (clientClassSize!=serverClassSize)
	{
		// class의 size가 다르다.
		return -2;
	}

	//---------------------------------------------------
	// 각 class마다의 type개수 체크
	//---------------------------------------------------
	for (int c=0; c<serverClassSize; c++)
	{
		int serverTypeSize = m_pTypeInfo[c].GetSize();
		int clientTypeSize = itemTable[c].GetSize();

		if (serverTypeSize!=clientTypeSize)
		{
			// size가 다른 경우..
			return c;
		}
	}

	//---------------------------------------------------
	// 양쪽 size가 모두 같은 경우에 
	// 필요한 data들 설정한다.
	//---------------------------------------------------
	for (c=0; c<serverClassSize; c++)
	{	

		for (int t=0; t<m_pTypeInfo[c].GetSize(); t++)
		{
			ITEM_CLASS	itemClass = (ITEM_CLASS)c;

			MItem* pItem = MItem::NewItem( itemClass );
			pItem->SetItemType( t );

			SERVER_ITEMTABLE_INFO&	serverInfo = m_pTypeInfo[c][t];
			ITEMTABLE_INFO&			clientInfo = itemTable[c][t];

			clientInfo.HName = serverInfo.HName;
			clientInfo.EName = serverInfo.EName;
//			clientInfo.Description = serverInfo.Description;

			// 오토바이 grid는 설정하면 안된다. default (1,1)로 잡혀있다.
			if (itemClass!=ITEM_CLASS_MOTORCYCLE)
			{
				clientInfo.GridWidth = serverInfo.GridWidth;
				clientInfo.GridHeight = serverInfo.GridHeight;
				if( itemClass == ITEM_CLASS_MIXING_ITEM &&
					pItem->GetItemType() >=9&& pItem->GetItemType() <= 17)
				{
					clientInfo.GridWidth = 1;
					clientInfo.GridHeight = 1;
				}

			}
			else
			{
				int a = 0;
			}

			clientInfo.Weight		= serverInfo.Weight;
			clientInfo.Price		= serverInfo.Price;

			//---------------------------------------------------
			// 성별
			//---------------------------------------------------
			switch (serverInfo.RequireGender)
			{
				// 공용
				case 0 :
					clientInfo.bMaleOnly = false;
					clientInfo.bFemaleOnly = false;
				break;

				// 남
				case 1 :
					clientInfo.bMaleOnly = true;
					clientInfo.bFemaleOnly = false;
				break;

				// 여
				case 2 :
					clientInfo.bMaleOnly = false;
					clientInfo.bFemaleOnly = true;
				break;
			}

			//---------------------------------------------------
			// silver max값
			//---------------------------------------------------
			clientInfo.SilverMax	= serverInfo.MaxSilver;

			//---------------------------------------------------
			// 값이 들어가는 가변적인 위치..
			//---------------------------------------------------
			// MotorCycle				: 내구성(1), 운반가능무게(2)
			// GearItem					: 내구성(1), 방어력(2)
			// Belt						: 내구성(1), 방어력(2), 포켓수(3)
			// HolyWater, 지뢰, 폭탄	: MinDam(1)~MaxDam(2)
			// Potion					: 회복수치(1)
			// 검,도					: 내구성(1), 방어력(?), MinDam(3)~MaxDam(4)
			// 십자가					: 내구성(1), 방어력(?), MinDam(3)~MaxDam(4), MP증가(5)
			// 총						: 내구성(1), 방어력(?), MinDam(3)~MaxDam(4), 사정거리(5)
			// 탄창						:			Max탄창수(2)
			//---------------------------------------------------
			
			//---------------------------------------------------
			// Tohit
			//---------------------------------------------------
			if (pItem->IsGunItem()
#if __CONTENTS(__TUNING_ITEM)
				|| pItem->GetItemClass() == ITEM_CLASS_SWORD
				|| pItem->GetItemClass() == ITEM_CLASS_BLADE
				|| pItem->GetItemClass() == ITEM_CLASS_VAMPIRE_WEAPON
				|| pItem->GetItemClass() == ITEM_CLASS_OUSTERS_CHAKRAM
#endif //__TUNING_ITEM
				)
			{
				clientInfo.ToHit = serverInfo.ToHit;
			}
			else
			{
				clientInfo.ToHit = -1;
			}
			
			// Item Style
			clientInfo.ItemStyle = serverInfo.ItemStyle;

			//---------------------------------------------------
			// Value1에 내구성.
			//---------------------------------------------------
			if (pItem->GetItemClass() == ITEM_CLASS_VAMPIRE_AMULET 
				|| clientInfo.ItemStyle == 1 || pItem->GetItemClass() == ITEM_CLASS_COUPLE_RING ||
				pItem->GetItemClass() == ITEM_CLASS_VAMPIRE_COUPLE_RING)
			{
				clientInfo.Value1 = -1;
			}
			else if(pItem->IsGearItem()
					|| pItem->IsBasicWeapon()
					|| itemClass==ITEM_CLASS_MOTORCYCLE
					|| itemClass==ITEM_CLASS_BELT
					|| itemClass==ITEM_CLASS_OUSTERS_ARMSBAND)
			{
				clientInfo.Value1 = serverInfo.Durability;			
			}

			//---------------------------------------------------
			// Value2에 방어력
			//---------------------------------------------------
			if (pItem->IsGearItem()
				|| pItem->IsBasicWeapon()
				|| itemClass==ITEM_CLASS_BELT
				|| itemClass==ITEM_CLASS_OUSTERS_ARMSBAND)
			{
				// Protection!
				clientInfo.Value2 = serverInfo.Protection;
			}

			//---------------------------------------------------
			// Value6에 Defense
			//---------------------------------------------------
			if (pItem->IsGearItem()
				|| itemClass==ITEM_CLASS_MOTORCYCLE)
			{
				clientInfo.Value6 = serverInfo.Defense;
			}

			//---------------------------------------------------
			// Value7에 속도
			//---------------------------------------------------
			if (pItem->IsBasicWeapon())
			{
				clientInfo.Value7 = serverInfo.Speed;
			}
	
#if __CONTENTS(__ADD_MAGICPROTECTION)
			if (pItem->HasMagicProtection())
			{
				clientInfo.Value7 = serverInfo.MagicProtection;
			}
#endif	//__ADD_MAGICPROTECTION

			//---------------------------------------------------
			// HolyWater, 지뢰, 폭탄	: MinDam(1)~MaxDam(2)
			//---------------------------------------------------
			if (itemClass==ITEM_CLASS_HOLYWATER
				|| itemClass==ITEM_CLASS_BOMB
				|| itemClass==ITEM_CLASS_MINE)
			{
				clientInfo.Value1 = serverInfo.MinDamage;
				clientInfo.Value2 = serverInfo.MaxDamage;
			}

			//---------------------------------------------------
			// 기본무기	: MinDam(3)~MaxDam(4)
			//---------------------------------------------------
			if (pItem->IsBasicWeapon())
			{
				clientInfo.Value3 = serverInfo.MinDamage;
				clientInfo.Value4 = serverInfo.MaxDamage;

				clientInfo.CriticalHit = serverInfo.CriticalHit;
			}

			//---------------------------------------------------
			// 십자가인 경우는 MP Plus
			//---------------------------------------------------
			if (itemClass==ITEM_CLASS_CROSS
				|| itemClass==ITEM_CLASS_MACE)
			{
				clientInfo.Value5 = serverInfo.MPPlus;
			}
			
			//---------------------------------------------------
			// 총은 사정거리
			//---------------------------------------------------
			if (itemClass==ITEM_CLASS_AR
				|| itemClass==ITEM_CLASS_SR
				|| itemClass==ITEM_CLASS_SG
				|| itemClass==ITEM_CLASS_SMG)
			{
				clientInfo.Value5 = serverInfo.Range;			// 총 길이
			}

			//---------------------------------------------------
			// 총알은 총알 개수..
			//---------------------------------------------------
			if (itemClass==ITEM_CLASS_MAGAZINE)
			{
				clientInfo.Value2 = serverInfo.Bullet;			// 총알 개수
			}

			//---------------------------------------------------
			// motor는 운반가능무게
			//---------------------------------------------------
			if (itemClass==ITEM_CLASS_MOTORCYCLE)
			{
				clientInfo.Value2 = serverInfo.MotorCarry;		// 오토바이 운반 가능무게
			}

			//---------------------------------------------------
			// 포션.. 회복수치
			//---------------------------------------------------
			if (itemClass==ITEM_CLASS_POTION || itemClass == ITEM_CLASS_PUPA ||
				itemClass==ITEM_CLASS_COMPOS_MEI)
			{
				// 0~4까지는 힐링, 10은 파란 사탕
				//if (t<=4 || t==10 || t==)
				//{
				//	clientInfo.Value1 = serverInfo.HPRecover;		// HP 회복 수치
				//}
				
				//if (t>=5 && t<=10)
				//{
				//	clientInfo.Value2 = serverInfo.MPRecover;		// MP 회복 수치
				//}

				if(serverInfo.HPRecover > 0)
					clientInfo.Value1 = serverInfo.HPRecover;
				else
					clientInfo.Value1 = -1;
				if(serverInfo.MPRecover > 0)
					clientInfo.Value2 = serverInfo.MPRecover;
				else
					clientInfo.Value2 = -1;
			}

			if (itemClass==ITEM_CLASS_SERUM)
			{
				clientInfo.Value1 = serverInfo.HPRecover;	// HP 회복 수치
			}

			//---------------------------------------------------
			// 벨트 크기
			//---------------------------------------------------
			if (itemClass==ITEM_CLASS_BELT || itemClass == ITEM_CLASS_OUSTERS_ARMSBAND)
			{
				clientInfo.Value3 = serverInfo.Pocket;			// 벨트 크기
			}

#if __CONTENTS(__TUNING_ITEM)
			if (itemClass==ITEM_CLASS_TUNING_SLAYER || itemClass == ITEM_CLASS_TUNING_VAMPIRE || itemClass == ITEM_CLASS_TUNING_OUSTERS)
			{
				clientInfo.Value1 = serverInfo.TuningItmeClass;
				clientInfo.Value2 = serverInfo.TuningItmeType;
			}
#endif //__TUNING_ITEM

			//---------------------------------------------------
			// Charge Item
			//---------------------------------------------------
			if (pItem->IsChargeItem())
			{
				clientInfo.MaxNumber = serverInfo.Charge;
			}

			//---------------------------------------------------
			// 필요능력치
			//---------------------------------------------------
			clientInfo.SetRequireSTR( serverInfo.RequireSTR );
			clientInfo.SetRequireDEX( serverInfo.RequireDEX );
			clientInfo.SetRequireINT( serverInfo.RequireINT );
			clientInfo.SetRequireSUM( serverInfo.RequireSUM );
			clientInfo.SetRequireLevel( serverInfo.RequireLevel );
			clientInfo.SetRequireAdvancementLevel( serverInfo.RequirAdvancementLevel );

			// Default Option
			if(!serverInfo.DefaultOptionList.empty())
			{
				std::list<int>::iterator itr = serverInfo.DefaultOptionList.begin();
				while(itr != serverInfo.DefaultOptionList.end())
				{
					int Option = *itr;

					clientInfo.DefaultOptionList.push_back(Option);

					itr++;
				}
			}

			clientInfo.ElementalType = (ITEMTABLE_INFO::ELEMENTAL_TYPE)serverInfo.ElementalType;
			clientInfo.Elemental = serverInfo.Elemental;

			clientInfo.Race = serverInfo.Race;
			
			delete pItem;
		}
	}


	return -1;
}
