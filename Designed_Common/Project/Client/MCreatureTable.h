//----------------------------------------------------------------------
// MCreatureTable.h
//----------------------------------------------------------------------
// CreatureÀÇ Á¾·ù¿¡ µû¸¥ Á¤º¸¸¦ ÀúÀåÇÏ´Â class
//----------------------------------------------------------------------
//
// [ Á¾·ùº°·Î ÀÖ´Â Á¤º¸ ] 
//
// - µ¿ÀÛ FrameID
// - Sprite FilePosition
// - First SpriteID
// - ÀÌ¸§... µîµî...
// 
//----------------------------------------------------------------------

#ifndef	__MCREATURETABLE_H__
#define	__MCREATURETABLE_H__

#pragma warning(disable:4786)

#include "MObject.h"
#include "SpriteLib\DrawTypeDef.h"
#include "CTypeTable.h"
#include "MString.h"
#include <list>
#include <vector>
std::ifstream;
std::ofstream;

//----------------------------------------------------------------------
// CreatureÀÇ Á¾Á·
//----------------------------------------------------------------------
enum CREATURETRIBE
{	
	CREATURETRIBE_SLAYER,			// ½½·¹ÀÌ¾î
	CREATURETRIBE_VAMPIRE,			// ¹ìÆÄÀÌ¾î
	CREATURETRIBE_NPC,				// NPC
	CREATURETRIBE_SLAYER_NPC,		// ½½·¹ÀÌ¾î ½ºÇÁ¶óÀÌÆ®¸¦ »ç¿ëÇÏ´Â NPC
	CREATURETRIBE_OUSTERS,
	CREATURETRIBE_OUSTERS_NPC,		// ¾Æ¿ì½ºÅÍÁî ½ºÇÁ¶óÀÌÆ®¸¦ »ç¿ëÇÏ´Â NPC
	CREATURETRIBE_UNKNOW1,	
	CREATURETRIBE_UNKNOW2,	
	CREATURETRIBE_UNKNOW3,
	CREATURETRIBE_UNKNOW4,
	CREATURETRIBE_UNKNOW5,
	MAX_CREATURETRIBE
};

//----------------------------------------------------------------------
// CreatureType
//----------------------------------------------------------------------
#define	CREATURETYPE_SLAYER_MALE		0
#define	CREATURETYPE_SLAYER_FEMALE		1
#define	CREATURETYPE_VAMPIRE_MALE1		2
#define	CREATURETYPE_VAMPIRE_FEMALE1	3
#define	CREATURETYPE_VAMPIRE_MALE2		514
#define	CREATURETYPE_VAMPIRE_FEMALE2	515
#define	CREATURETYPE_VAMPIRE_MALE3		558
#define	CREATURETYPE_VAMPIRE_FEMALE3	559
#define	CREATURETYPE_BAT				185
#define	CREATURETYPE_WOLF				186
#define	CREATURETYPE_SLAYER_OPERATOR	367
#define	CREATURETYPE_VAMPIRE_OPERATOR	369
#define	CREATURETYPE_OUSTERS_OPERATOR	652
#define CREATURETYPE_OUSTERS			651
#define CREATURETYPE_WER_WOLF			671//671
#define CREATURETYPE_GHOST				716
#define CREATURETYPE_INSTALL_TURRET		742
#define CREATURETYPE_ROCKET_LUNCHER		767
#define CREATURETYPE_WILD_WOLF			787//787
#define	CREATURETYPE_VAMPIRE_MALE4		804
#define	CREATURETYPE_VAMPIRE_FEMALE4	805
#define	CREATURETYPE_VAMPIRE_GHOST		813
#define CREATURETYPE_BAT_STORM_1		924
#define CREATURETYPE_BAT_STORM_2		925
#define CREATURETYPE_XRL_ROCKET_LUNCHER	1027
#define CREATURETYPE_FLITTERMOUSE		1028
#define CREATURETYPE_SHAPE_OF_DEMON		1042
#define CREATURETYPE_INSTALL_MK1		1357
//#define CREATURETYPE_CML		        1362
#define CREATURETYPE_NEDE		        1208//¹í×å±äÉíËÀÍöÄÚµÂ
#define CREATURETYPE_KLTL		        1712//¹í×å±äÉíËÀÍöÄÚµÂ
#define CREATURETYPE_DARK_WOLF			1730//787


//----------------------------------------------------------------------
// ½½·¹ÀÌ¾î NPCÀÇ º¹Àå¿¡ ´ëÇÑ Á¤º¸
//----------------------------------------------------------------------
class ITEM_WEARINFO
{
	public :
		WORD		skinColor;
		WORD		hairColor;		
		WORD		jacketColor;
		WORD		pantsColor;
		WORD		helmetColor;
		WORD		weaponColor;
		WORD		shieldColor;
		WORD		motorcycleColor;
		
		BYTE		hair;		
		BYTE		jacket;
		BYTE		pants;
		BYTE		helmet;
		BYTE		weapon;
		BYTE		shield;
		BYTE		motorcycle;

	public :
		ITEM_WEARINFO();

		void		operator = (const ITEM_WEARINFO& info);
		void		SaveToFile(std::ofstream& file);
		void		LoadFromFile(ivfstream& file);
};


//----------------------------------------------------------------------
//
// ÇÑ Á¾·ùÀÇ Creature¿¡ ´ëÇÑ Á¤º¸
//
//----------------------------------------------------------------------
class CREATURETABLE_INFO {
	public :
//¾Æ·¡ csvº¯¼ö´Â Å©¸®Ã³ ÀÌ¸§À» csvÆÄÀÏ·Î »Ì¾Æ ³»±â À§ÇÑ º¯¼öÀÌ´Ù. °ÔÀÓ ½ÇÇà¿¡´Â ¿¬°üÀÌ ¾øÀ¸¹Ç·Î °æ¿ì¿¡ µû¶ó¼­ Á¦°Å ÇØµµ ±¦Âù´Ù.
//¿ª½Ã ÇÔ¼öµµ ¸¶Âù°¡ÁöÀÌ´Ù.
		const char*				CSV_NULL_VALUE;
      	const char*				CSV_TOKEN;

		MString					Name;					// Ä³¸¯ÅÍ ÀÌ¸§
		CTypeTable<int>			SpriteTypes;			// SpriteTable¿¡¼­ÀÇ ID
		bool					bMale;					// ³²ÀÚÀÎ°¡?		
		BYTE					MoveTimes;				// ÀÌµ¿ È¸¼ö
		BYTE					MoveRatio;				// Frame¼ö/ÀÌµ¿ È¸¼ö... ±×¸²Àº 12frameÀÌ¶óµµ 6¹ø¸¸ ÀÌµ¿ÇÒ ¼öµµ ÀÖ´Ù.
		BYTE					MoveTimesMotor;			// ¿ÀÅä¹ÙÀÌ ÅÀÀ» ¶§ ÀÌµ¿ È¸¼ö
		int						Height;					// Å° (Ã¤ÆÃ Ãâ·Â À§Ä¡¸¦ À§ÇØ¼­)
		int						Width;					// ³Êºñ 
		int						DeadHeight;				// Á×¾úÀ»¶§ÀÇ Å°
		TYPE_ACTIONINFO			DeadActionInfo;			// Á×À»¶§ÀÇ actionInfo
		int						ColorSet;				// ¹Ù²î´Â »ö±ò ¹øÈ£
		bool					bFlyingCreature;		// ³¯¾Æ´Ù´Ï´Â Ä³¸¯ÀÎ°¡?
		int						FlyingHeight;			// ³¯¾Æ´Ù´Ï´Â ³ôÀÌ
		bool					bHeadCut;				// ¸Ó¸® Àß¸®´Â°¡? -_-;
		int						HPBarWidth;				// HP bar Å©±â
		ITEM_WEARINFO*			pItemWearInfo;			// ½½·¹ÀÌ¾î NPCÀÎ °æ¿ì
		WORD					ChangeColorSet;			// Ä³¸¯ÅÍ ÀüÃ¼°¡ ¹Ù²î´Â °æ¿ì
		int						ShadowCount;			// ´Ã µû¶ó´Ù´Ï´Â ¸öÀÇ ÀÜ»ó °³¼ö
		int						EffectStatus;			// ¸ó½ºÅÍ ¸ö¿¡ ºÙ´Â ÀÌÆÑÆ® »óÅÂ
		int						Level;					// ¸ó½ºÅÍ ·¹º§
		bool					bFade;					// ¾îµÓ°Ô ³ª¿À´Â ¸ó½ºÅÍ
		bool					bFadeShadow;			// ±×¸²ÀÚ°¡ ¾îµÓ°Ô ³ª¿À´Â ¸ó½ºÅÍ
		int					tmp;		// ¸ó½ºÅÍ ¸ö¿¡ ºÙ´Â ÀÌÆÑÆ® ½ºÇÁ¶óÀÌÆ®
        int                     EffectSpriteType;

	protected :
		CREATURETRIBE			m_CreatureTribe;		// Á¾Á·
		TYPE_SOUNDID*			m_pActionSound;			// Sound ID
		int*					m_pActionCount;			// Action Count
		
	public :
		CREATURETABLE_INFO();
		~CREATURETABLE_INFO();

		//-------------------------------------------------------
		// Set / Get
		//-------------------------------------------------------
		void				SetCreatureTribe(enum CREATURETRIBE ct, int nMaxAction = 0);
		bool				IsSlayer() const						{ return m_CreatureTribe==CREATURETRIBE_SLAYER || m_CreatureTribe==CREATURETRIBE_SLAYER_NPC; }
		bool				IsVampire() const						{ return m_CreatureTribe==CREATURETRIBE_VAMPIRE || m_CreatureTribe==CREATURETRIBE_UNKNOW1 || m_CreatureTribe==CREATURETRIBE_UNKNOW2 || m_CreatureTribe==CREATURETRIBE_UNKNOW3 || m_CreatureTribe==CREATURETRIBE_UNKNOW4; }
		bool				IsOusters() const						{ return m_CreatureTribe==CREATURETRIBE_OUSTERS || m_CreatureTribe==CREATURETRIBE_OUSTERS_NPC; }
		bool				IsNPC() const							{ return m_CreatureTribe==CREATURETRIBE_NPC || m_CreatureTribe==CREATURETRIBE_SLAYER_NPC|| m_CreatureTribe==CREATURETRIBE_OUSTERS_NPC; }
		void				SetActionSound(int n, int count, TYPE_SOUNDID sid)	{ m_pActionCount[n] = count;  m_pActionSound[n] = sid; }
		void				SetActionSound(int n, TYPE_SOUNDID sid)	{ m_pActionSound[n] = sid; }
		void				SetActionCount(int n, int count)		{ m_pActionCount[n] = count; }

		enum CREATURETRIBE	GetCreatureTribe() const				{ return m_CreatureTribe; }
		int					GetActionCount(int n)					{ return m_pActionCount[n]; }		
		TYPE_SOUNDID		GetActionSound(int n)					{ return m_pActionSound[n]; }		
		int					GetActionMax() const;
		
		bool				IsFlyingCreature() const				{ return bFlyingCreature; }

		//-------------------------------------------------------
		// assign
		//-------------------------------------------------------
		void				operator = (const CREATURETABLE_INFO& creatureInfo);

		//-------------------------------------------------------
		// File I/O
		//-------------------------------------------------------
		void				SaveToFile(std::ofstream& file);
		void				LoadFromFile(ivfstream& file);	

		void				SaveToCSVFile(std::ofstream& file, unsigned int CreatureID);
		void				SaveNumberToCSVFile(std::ofstream& file, int value, int null = 65536);
		void				SaveStringToCSVFile(std::ofstream& file, const MString& value);

		
	protected :
		void				InitActionType(int nMaxAction = 0);				
};

//----------------------------------------------------------------------
// CreatureSpriteTypeMapper
//----------------------------------------------------------------------
// SpriteID·Î CreatureTypeÀ» Ã£´Â °æ¿ì¿¡ »ç¿ë
//----------------------------------------------------------------------
class CreatureSpriteTypeMapper {
	public :
		typedef std::vector<WORD>				CREATURE_TYPES;		// WORD.. ±ÍÂ÷³ª..
		typedef std::vector<CREATURE_TYPES*>	CREATURE_SPRITE_TYPES;

	public :
		CreatureSpriteTypeMapper();
		~CreatureSpriteTypeMapper();

		void	Init(int num);
		void	Release();

		void	AddCreatureType(TYPE_SPRITEID spriteID, WORD creatureType);
		int		GetRandomCreatureType(TYPE_SPRITEID spriteID) const;

		//-------------------------------------------------------
		// File I/O
		//-------------------------------------------------------
		void				SaveToFile(std::ofstream& file);
		void				LoadFromFile(ivfstream& file);	

	protected :
		CREATURE_SPRITE_TYPES	m_CreatureSpriteTypes;
};


typedef CTypeTable<CREATURETABLE_INFO>	CREATURE_TABLE;
extern CREATURE_TABLE* g_pCreatureTable;

extern CreatureSpriteTypeMapper* g_pCreatureSpriteTypeMapper;

#endif


