//----------------------------------------------------------------------
// MServerItemTable.h
//----------------------------------------------------------------------

#ifndef __SERVER_ITEMTABLE_H__
#define __SERVER_ITEMTABLE_H__

#pragma warning(disable:4786)

#include "MString.h"
#include "CTypeTable.h"
#include <list>

class ITEMCLASS_TABLE;
std::ifstream;
std::ofstream;


class SERVER_ITEMTABLE_INFO {
	public :
		SERVER_ITEMTABLE_INFO();
		~SERVER_ITEMTABLE_INFO();

		void			SaveToFile(std::ofstream& file);
		void			LoadFromFile(ivfstream& file);

	public :
		MString			HName;
		MString			EName;
		MString			Description;
		int				Weight;
		int				Price;
		int				Durability;
		int				GridWidth;
		int				GridHeight;
		int				Defense;
		int				MinDamage;
		int				MaxDamage;
		int				MPPlus;
		int				Range;			// 총 길이
		int				Bullet;			// 총알 개수
		int				ToHit;			// to hit 보너스 (총에만)
		int				MotorCarry;		// 오토바이 운반 가능무게
		int				HPRecover;		// HP 회복 수치
		int				MPRecover;		// MP 회복 수치
		int				Pocket;			// 벨트 크기
		int				RequireSTR;	
		int				RequireDEX;
		int				RequireINT;
		int				RequireSUM;
		int				RequireLevel;
		int				RequireGender;
		int				RequirAdvancementLevel;	// 승직 필요 레벨
		int				MaxSilver;
		int				Speed;
		int				Protection;
		int				Charge;
		int				CriticalHit;

		std::list<int>	DefaultOptionList;
		int				UpgradeCrashPercent;

		int				ItemStyle;
		
		int				ElementalType;
		int				Elemental;
		int				Race;

#if __CONTENTS(__TUNING_ITEM)
		int				TuningItmeClass;
		int				TuningItmeType;
#endif //__TUNING_ITEM

#if __CONTENTS(__ADD_MAGICPROTECTION)
		int				MagicProtection;
#endif	//__
};

typedef CTypeTable<SERVER_ITEMTABLE_INFO>				SERVER_ITEMTYPE_TABLE;

//----------------------------------------------------------------------
// MServerItemTableInfo
//----------------------------------------------------------------------
class SERVER_ITEMCLASS_TABLE : public CTypeTable<SERVER_ITEMTYPE_TABLE> {
	public :
		SERVER_ITEMCLASS_TABLE();
		~SERVER_ITEMCLASS_TABLE();

		int			AffectToItemTable( ITEMCLASS_TABLE& itemTable );
};

#endif

