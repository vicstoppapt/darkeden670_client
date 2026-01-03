#include "StdAfx.h"
#include <fstream>
#include <mmsystem.h>

// def
#include "MTypeDef.h"
#include "MFileDef.h"
#include "AddonDef.h"
#include "SoundDef.h"
#include "EffectSpriteTypeDef.h"

// table
#include "ClientConfig.h"
#include "UserOption.h"
#include "MSoundTable.h"
#include "MMusicTable.h"
#include "MZoneTable.h"
#include "MItemTable.h"
#include "MItemOptionTable.h"
#include "MInteractionObjectTable.h"
#include "CFileIndexTable.h"
#include "MCreatureTable.h"
#include "MCreatureSpriteTable.h"
#include "CFramePack.h"
#include "MShopTemplateTable.h"
#include "MNPCTable.h"
#include "MEffectSpriteTypeTable.h"
#include "MEffectStatusTable.h"
#include "MActionInfoTable.h"
#include "MGameStringTable.h"
#include "MServerItemTable.h"
#include "MSkillManager.h"
#include "MEffectGeneratorDef.h"
#include "MusicDef.h"
#include "MChatManager.h"
#include "MLevelNameTable.h"
#include "AppendPatchInfo.h"
#include "AddonDef.h"
#include "RankBonusTable.h"
#include "ServerRankBonusTable.h"
#include "packet/Properties.h"

#include "MMinMaxInfo.h"

#include "MItem.h"

#include "Packet\types\PacketItemDef.h"
#include "MathTable.h"

#define SAVE_TO_FILE

HRESULT InitFail(LPCTSTR szError,...);
bool 
FileOpenBinary(const char* filename, ivfstream& file);
//---------------------------------------------------------------------------
// Open File
//---------------------------------------------------------------------------
bool 
FileCheck(const char* filename);


BOOL	InitEffectStatusTable()
{
#ifdef SAVE_TO_FILE
	(*g_pEffectStatusTable).Init( EFFECTSTATUS_MAX );	
	
	//---------------------------------------------------------------------
	// 성직자
	//---------------------------------------------------------------------
	(*g_pEffectStatusTable)[EFFECTSTATUS_LIGHT].EffectSpriteType		= EFFECTSPRITETYPE_LIGHT_2;		// Light 를 걸었을 때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_LIGHT].ActionInfo				= RESULT_MAGIC_LIGHT;					// Light 를 걸었을 때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_LIGHT].OriginalActionInfo		= MAGIC_LIGHT;

	(*g_pEffectStatusTable)[EFFECTSTATUS_DETECT_HIDDEN].EffectSpriteType				= EFFECTSPRITETYPE_NULL;		// DetectHidden 을 걸었을 때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_DETECT_HIDDEN].OriginalActionInfo		= MAGIC_DETECT_HIDDEN;

	(*g_pEffectStatusTable)[EFFECTSTATUS_PROTECTION_FROM_POISON].EffectSpriteType		= EFFECTSPRITETYPE_PROTECTION_FROM_POISON_ING; // ProtecitonFromPoison 을 걸었을때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_PROTECTION_FROM_POISON].OriginalActionInfo		= MAGIC_PROTECTION_FROM_POISON;

	(*g_pEffectStatusTable)[EFFECTSTATUS_PROTECTION_FROM_CURSE].EffectSpriteType		= EFFECTSPRITETYPE_PROTECTION_FROM_CURSE_ING;// ProtectionFromParalysis 을 걸었을때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_PROTECTION_FROM_CURSE].OriginalActionInfo		= MAGIC_PROTECTION_FROM_CURSE;

	(*g_pEffectStatusTable)[EFFECTSTATUS_PROTECTION_FROM_ACID].EffectSpriteType			= EFFECTSPRITETYPE_PROTECTION_FROM_ACID_ING; // ProtecitonFromPoison 을 걸었을때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_PROTECTION_FROM_ACID].OriginalActionInfo		= MAGIC_PROTECTION_FROM_ACID;

	(*g_pEffectStatusTable)[EFFECTSTATUS_PROTECTION_FROM_BLOOD].EffectSpriteType		= EFFECTSPRITETYPE_PROTECTION_FROM_BLOOD_ING;
	(*g_pEffectStatusTable)[EFFECTSTATUS_PROTECTION_FROM_BLOOD].OriginalActionInfo		= SKILL_PROTECTION_FROM_BLOOD;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLESS].EffectSpriteType				= EFFECTSPRITETYPE_BLESS_ING_NEW;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLESS].OriginalActionInfo				= MAGIC_BLESS;

	//(*g_pEffectStatusTable)[EFFECTSTATUS_STRIKING].EffectSpriteType				= EFFECTSPRITETYPE_STRIKING_ING_2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_STRIKING].bUseEffectSprite		= false;
	(*g_pEffectStatusTable)[EFFECTSTATUS_STRIKING].EffectColor				= 215;
	(*g_pEffectStatusTable)[EFFECTSTATUS_STRIKING].EffectColorPart			= ADDON_RIGHTHAND;
	(*g_pEffectStatusTable)[EFFECTSTATUS_STRIKING].OriginalActionInfo			= MAGIC_STRIKING;

	(*g_pEffectStatusTable)[EFFECTSTATUS_CONTINUAL_LIGHT].EffectSpriteType				= EFFECTSPRITETYPE_NULL;		// Continual Light를 걸었을때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_CONTINUAL_LIGHT].OriginalActionInfo			= MAGIC_CONTINUAL_LIGHT;

	(*g_pEffectStatusTable)[EFFECTSTATUS_DETECT_INVISIBILITY].EffectSpriteType		= EFFECTSPRITETYPE_NULL;		// DetectInvisibility 을 걸었을 때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_DETECT_INVISIBILITY].OriginalActionInfo		= MAGIC_DETECT_INVISIBILITY;
	
//	(*g_pEffectStatusTable)[EFFECTSTATUS_REGENERATION].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_REGENERATION].OriginalActionInfo	= MAGIC_REGENERATION;

	(*g_pEffectStatusTable)[EFFECTSTATUS_AURA_SHIELD].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_AURA_SHIELD].OriginalActionInfo		= MAGIC_AURA_SHIELD;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SAINT_AURA].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SAINT_AURA].OriginalActionInfo		= MAGIC_SAINT_AURA;

	(*g_pEffectStatusTable)[EFFECTSTATUS_FLARE].EffectSpriteType			= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FLARE].OriginalActionInfo			= MAGIC_FLARE;

	//---------------------------------------------------------------------
	// 무사
	//---------------------------------------------------------------------	
	(*g_pEffectStatusTable)[EFFECTSTATUS_CROSS_COUNTER].EffectSpriteType		= EFFECTSPRITETYPE_NULL;			// final blow & cross counter
	(*g_pEffectStatusTable)[EFFECTSTATUS_CROSS_COUNTER].OriginalActionInfo		= SKILL_CROSS_COUNTER;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_CHARGING_POWER].EffectSpriteType		= EFFECTSPRITETYPE_NULL;			//  
	(*g_pEffectStatusTable)[EFFECTSTATUS_CHARGING_POWER].OriginalActionInfo		= SKILL_CHARGING_POWER;

	(*g_pEffectStatusTable)[EFFECTSTATUS_LIGHTNING_HAND].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_LIGHTNING_HAND].OriginalActionInfo		= SKILL_LIGHTNING_HAND;

	(*g_pEffectStatusTable)[EFFECTSTATUS_POTENTIAL_EXPLOSION].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_POTENTIAL_EXPLOSION].OriginalActionInfo	= SKILL_POTENTIAL_EXPLOSION;

	(*g_pEffectStatusTable)[EFFECTSTATUS_DANCING_SWORD].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DANCING_SWORD].OriginalActionInfo		= SKILL_DANCING_SWORD;

	(*g_pEffectStatusTable)[EFFECTSTATUS_GHOST_BLADE].EffectSpriteType			= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_GHOST_BLADE].OriginalActionInfo			= SKILL_GHOST_BLADE;


	//---------------------------------------------------------------------	
	// 뱀파이어
	//---------------------------------------------------------------------	
	(*g_pEffectStatusTable)[EFFECTSTATUS_HIDE ].EffectSpriteType				= EFFECTSPRITETYPE_NULL;					// Hide 를 걸었을때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_HIDE ].OriginalActionInfo				= MAGIC_HIDE;

	// Vampire Magics
	(*g_pEffectStatusTable)[EFFECTSTATUS_ACID_TOUCH].bUseEffectSprite				= false;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ACID_TOUCH].EffectColor					= 176;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ACID_TOUCH].OriginalActionInfo					= MAGIC_ACID_TOUCH;

	(*g_pEffectStatusTable)[EFFECTSTATUS_POISON].bUseEffectSprite				= false;
	(*g_pEffectStatusTable)[EFFECTSTATUS_POISON].EffectColor					= 110;
	(*g_pEffectStatusTable)[EFFECTSTATUS_POISON].OriginalActionInfo					= MAGIC_GREEN_POISON;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_POISONOUS_HANDS].bUseEffectSprite				= false;
	(*g_pEffectStatusTable)[EFFECTSTATUS_POISONOUS_HANDS].EffectColor					= 110;
	(*g_pEffectStatusTable)[EFFECTSTATUS_POISONOUS_HANDS].OriginalActionInfo					= MAGIC_POISONOUS_HANDS;

	(*g_pEffectStatusTable)[EFFECTSTATUS_BLOOD_DRAIN].EffectSpriteType				= EFFECTSPRITETYPE_NULL;			// 흡혈 당했을때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLOOD_DRAIN].OriginalActionInfo				= SKILL_BLOOD_DRAIN;

	(*g_pEffectStatusTable)[EFFECTSTATUS_CURSE_PARALYSIS].bUseEffectSprite			= false;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CURSE_PARALYSIS].EffectColor			= 393;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CURSE_PARALYSIS].ActionInfo				= RESULT_MAGIC_PARALYZE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CURSE_PARALYSIS].OriginalActionInfo				= MAGIC_PARALYZE;
	
//	(*g_pEffectStatusTable)[EFFECTSTATUS_EXPLOSION_WATER].bUseEffectSprite			= false;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_EXPLOSION_WATER].EffectColor			= 393;
	(*g_pEffectStatusTable)[EFFECTSTATUS_EXPLOSION_WATER].ActionInfo				= RESULT_SKILL_EXPLOSION_WATER;
	(*g_pEffectStatusTable)[EFFECTSTATUS_EXPLOSION_WATER].OriginalActionInfo				= SKILL_EXPLOSION_WATER;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_CURSE_DOOM].EffectSpriteType		= EFFECTSPRITETYPE_CURSE_2;		// Light 를 걸었을 때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_CURSE_DOOM].ActionInfo				= RESULT_MAGIC_DOOM;					// Light 를 걸었을 때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_CURSE_DOOM].OriginalActionInfo		= MAGIC_DOOM;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_GREEN_POISON].bUseEffectSprite			= false;
	(*g_pEffectStatusTable)[EFFECTSTATUS_GREEN_POISON].EffectColor				= 110;
	(*g_pEffectStatusTable)[EFFECTSTATUS_GREEN_POISON].ActionInfo				= RESULT_MAGIC_GREEN_POISON;
	(*g_pEffectStatusTable)[EFFECTSTATUS_GREEN_POISON].OriginalActionInfo				= MAGIC_GREEN_POISON;

	(*g_pEffectStatusTable)[EFFECTSTATUS_YELLOW_POISON].bUseEffectSprite		= false;
	(*g_pEffectStatusTable)[EFFECTSTATUS_YELLOW_POISON].EffectColor		= 170;
	(*g_pEffectStatusTable)[EFFECTSTATUS_YELLOW_POISON].ActionInfo				= RESULT_MAGIC_YELLOW_POISON;
	(*g_pEffectStatusTable)[EFFECTSTATUS_YELLOW_POISON].OriginalActionInfo				= MAGIC_YELLOW_POISON;

	(*g_pEffectStatusTable)[EFFECTSTATUS_YELLOW_POISON_TO_CREATURE].bUseEffectSprite		= false;
	(*g_pEffectStatusTable)[EFFECTSTATUS_YELLOW_POISON_TO_CREATURE].EffectColor		= 170;
	(*g_pEffectStatusTable)[EFFECTSTATUS_YELLOW_POISON_TO_CREATURE].OriginalActionInfo		= MAGIC_YELLOW_POISON;
		
	(*g_pEffectStatusTable)[EFFECTSTATUS_DARKNESS].EffectSpriteType				= EFFECTSPRITETYPE_DARKNESS_2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DARKNESS].ActionInfo					= RESULT_MAGIC_DARKNESS;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DARKNESS].OriginalActionInfo			= MAGIC_DARKNESS;
		
	(*g_pEffectStatusTable)[EFFECTSTATUS_INVISIBILITY].EffectSpriteType		= EFFECTSPRITETYPE_NULL;			// Invisibility 를 걸었을때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_INVISIBILITY].ActionInfo			= MAGIC_INVISIBILITY;
	(*g_pEffectStatusTable)[EFFECTSTATUS_INVISIBILITY].OriginalActionInfo	= MAGIC_INVISIBILITY;

	(*g_pEffectStatusTable)[EFFECTSTATUS_ACID_SWAMP].EffectSpriteType		= EFFECTSPRITETYPE_ACID_SWAP_2;				// AcidBall이 바닥에 .
	(*g_pEffectStatusTable)[EFFECTSTATUS_ACID_SWAMP].ActionInfo					= RESULT_MAGIC_ACID_SWAMP;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ACID_SWAMP].OriginalActionInfo		= MAGIC_ACID_SWAMP;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_REGENERATION].EffectSpriteType		= EFFECTSPRITETYPE_REGENERATION_ING;				// AcidBall이 바닥에 .
	(*g_pEffectStatusTable)[EFFECTSTATUS_REGENERATION].ActionInfo					= RESULT_MAGIC_REGENERATION;
	(*g_pEffectStatusTable)[EFFECTSTATUS_REGENERATION].OriginalActionInfo		= MAGIC_REGENERATION;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_GROUND_ATTACK].EffectSpriteType		= EFFECTSPRITETYPE_NULL;//ACID_SWAP_2;				// AcidBall이 바닥에 .
	(*g_pEffectStatusTable)[EFFECTSTATUS_GROUND_ATTACK].ActionInfo					= RESULT_MAGIC_GROUND_ATTACK;
	(*g_pEffectStatusTable)[EFFECTSTATUS_GROUND_ATTACK].OriginalActionInfo		= MAGIC_GROUND_ATTACK;
	
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_ACID_BALL].EffectSpriteType		= EFFECTSPRITETYPE_NULL;				// AcidBall이 바닥에 .
	(*g_pEffectStatusTable)[EFFECTSTATUS_ACID_BALL].OriginalActionInfo		= MAGIC_ACID_BALL;
		
	(*g_pEffectStatusTable)[EFFECTSTATUS_GREEN_STALKER].EffectSpriteType		= EFFECTSPRITETYPE_GREEN_STALKER_4;
	(*g_pEffectStatusTable)[EFFECTSTATUS_GREEN_STALKER].ActionInfo				= RESULT_MAGIC_GREEN_STALKER;
	(*g_pEffectStatusTable)[EFFECTSTATUS_GREEN_STALKER].OriginalActionInfo		= MAGIC_GREEN_STALKER;
	
	/*
	(*g_pEffectStatusTable)[EFFECTSTATUS_DARKBLUE_POISON].bUseEffectSprite			= false;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DARKBLUE_POISON].EffectColor			= 163;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DARKBLUE_POISON].ActionInfo				= RESULT_MAGIC_DARKBLUE_POISON;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DARKBLUE_POISON].OriginalActionInfo				= MAGIC_DARKBLUE_POISON;

	(*g_pEffectStatusTable)[EFFECTSTATUS_DARKBLUE_POISON_TO_CREATURE].bUseEffectSprite			= false;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DARKBLUE_POISON_TO_CREATURE].EffectColor			= 163;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DARKBLUE_POISON_TO_CREATURE].ActionInfo				= RESULT_MAGIC_DARKBLUE_POISON;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DARKBLUE_POISON_TO_CREATURE].OriginalActionInfo	= MAGIC_DARKBLUE_POISON;
	*/
	(*g_pEffectStatusTable)[EFFECTSTATUS_DARKBLUE_POISON].EffectSpriteType		= EFFECTSPRITETYPE_DARKBLUE_POISON_BACK_2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DARKBLUE_POISON].ActionInfo				= RESULT_MAGIC_DARKBLUE_POISON;					// Light 를 걸었을 때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_DARKBLUE_POISON].OriginalActionInfo		= MAGIC_DARKBLUE_POISON;

	(*g_pEffectStatusTable)[EFFECTSTATUS_DARKBLUE_POISON_TO_CREATURE].EffectSpriteType		= EFFECTSPRITETYPE_DARKBLUE_POISON_BACK_2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DARKBLUE_POISON_TO_CREATURE].ActionInfo				= RESULT_MAGIC_DARKBLUE_POISON;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DARKBLUE_POISON_TO_CREATURE].OriginalActionInfo		= MAGIC_DARKBLUE_POISON;

	(*g_pEffectStatusTable)[EFFECTSTATUS_TRANSFORM_TO_WOLF].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_TRANSFORM_TO_WOLF].OriginalActionInfo		= MAGIC_TRANSFORM_TO_WOLF;

	(*g_pEffectStatusTable)[EFFECTSTATUS_TRANSFORM_TO_BAT].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_TRANSFORM_TO_BAT].OriginalActionInfo		= MAGIC_TRANSFORM_TO_BAT;

#if __CONTENTS(__FAST_TRANSFORTER)
	(*g_pEffectStatusTable)[EFFECTSTATUS_CLIENT_WING_SYLPH].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CLIENT_WING_SYLPH].OriginalActionInfo		= SKILL_CLIENT_OUSTERS_WING;

	(*g_pEffectStatusTable)[EFFECTSTATUS_CLIENT_WING_HELLBIKE].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CLIENT_WING_HELLBIKE].OriginalActionInfo	= SKILL_CLIENT_SLAYER_WING;

#endif //__FAST_TRANSFORTER
	
	//---------------------------------------------------------------------	
	// 군인
	//---------------------------------------------------------------------	
	(*g_pEffectStatusTable)[EFFECTSTATUS_RELOAD_TIMER].EffectSpriteType		= EFFECTSPRITETYPE_NULL;			// passive skill "FAST RELOAD"를 위해서..
	//(*g_pEffectStatusTable)[EFFECTSTATUS_RELOAD_TIMER].OriginalActionInfo		= ACTIONINFO_NULL;

	(*g_pEffectStatusTable)[EFFECTSTATUS_DETECT_MINE].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DETECT_MINE].OriginalActionInfo		= SKILL_DETECT_MINE;

	(*g_pEffectStatusTable)[EFFECTSTATUS_INSTALL].EffectSpriteType		= EFFECTSPRITETYPE_NULL;                // mine install( install되면 안보인다)
	//(*g_pEffectStatusTable)[EFFECTSTATUS_INSTALL].OriginalActionInfo		= MAGIC_

	(*g_pEffectStatusTable)[EFFECTSTATUS_FADE_OUT].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	//(*g_pEffectStatusTable)[EFFECTSTATUS_FADE_OUT].OriginalActionInfo		= MAGIC_

	(*g_pEffectStatusTable)[EFFECTSTATUS_SNIPPING_MODE].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	//(*g_pEffectStatusTable)[EFFECTSTATUS_SNIPPING_MODE].OriginalActionInfo		= MAGIC_

	(*g_pEffectStatusTable)[EFFECTSTATUS_GHOST].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	//(*g_pEffectStatusTable)[EFFECTSTATUS_SNIPPING_MODE].OriginalActionInfo		= MAGIC_

	//---------------------------------------------------------------------	
	// 기타
	//---------------------------------------------------------------------	
	(*g_pEffectStatusTable)[EFFECTSTATUS_HP_RECOVERY].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_MP_RECOVERY].EffectSpriteType		= EFFECTSPRITETYPE_NULL;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SACRIFICE].EffectSpriteType		= EFFECTSPRITETYPE_SACRIFICE_2;		// Light 를 걸었을 때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_SACRIFICE].ActionInfo				= RESULT_MAGIC_SACRIFICE;					// Light 를 걸었을 때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_SACRIFICE].OriginalActionInfo		= MAGIC_SACRIFICE;


	// 서버 전용
	(*g_pEffectStatusTable)[EFFECTSTATUS_AFTER_MATH].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ALIGNMENT_RECOVERY].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ENEMY_ERASE].EffectSpriteType		= EFFECTSPRITETYPE_NULL;

	(*g_pEffectStatusTable)[EFFECTSTATUS_VAMPIRE_PORTAL].EffectSpriteType			= EFFECTSPRITETYPE_BLOODY_TUNNEL_2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_VAMPIRE_PORTAL].ActionInfo					= RESULT_MAGIC_BLOODY_TUNNEL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_VAMPIRE_PORTAL].OriginalActionInfo			= MAGIC_BLOODY_TUNNEL;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SLAYER_PORTAL].EffectSpriteType			= EFFECTSPRITETYPE_NULL;

	(*g_pEffectStatusTable)[EFFECTSTATUS_COMA].EffectSpriteType			= EFFECTSPRITETYPE_NULL;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SEDUCTION].EffectSpriteType	= EFFECTSPRITETYPE_CURSE_WEAKNESS_2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SEDUCTION].ActionInfo					= RESULT_MAGIC_SEDUCTION;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SEDUCTION].OriginalActionInfo			= MAGIC_SEDUCTION;

	(*g_pEffectStatusTable)[EFFECTSTATUS_EXPANSION].EffectSpriteType	= EFFECTSPRITETYPE_HPBOOST_STAND_MALE;
// <슬레이어 리뉴얼 이팩트 삭제>
//	(*g_pEffectStatusTable)[EFFECTSTATUS_EXPANSION].ActionInfo				= RESULT_SKILL_EXPANSION;
	(*g_pEffectStatusTable)[EFFECTSTATUS_EXPANSION].OriginalActionInfo		= SKILL_EXPANSION;

	(*g_pEffectStatusTable)[EFFECTSTATUS_MIRACLE_SHIELD].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	
//	(*g_pEffectStatusTable)[EFFECTSTATUS_BERSERKER].EffectSpriteType		= EFFECTSPRITETYPE_BERSERKER_1_STAND_MALE;		// Light 를 걸었을 때.
//	(*g_pEffectStatusTable)[EFFECTSTATUS_BERSERKER].ActionInfo				= RESULT_SKILL_BERSERKER;					// Light 를 걸었을 때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_BERSERKER].OriginalActionInfo		= SKILL_BERSERKER;
	

	(*g_pEffectStatusTable)[EFFECTSTATUS_TYPHOON].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_MIND_CONTROL].EffectSpriteType	= EFFECTSPRITETYPE_NULL;


	// [새기술]
	//(*g_pEffectStatusTable)[EFFECTSTATUS_ACTIVATION].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_ACTIVATION].EffectSpriteType		= EFFECTSPRITETYPE_REGENERATION_1_STAND_MALE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ACTIVATION].OriginalActionInfo		= SKILL_ACTIVATION;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_ACTIVATION].ActionInfo				= RESULT_SKILL_ACTIVATION;

	(*g_pEffectStatusTable)[EFFECTSTATUS_PEACE].EffectSpriteType		= EFFECTSPRITETYPE_PEACE_UP;		// Light 를 걸었을 때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_PEACE].ActionInfo				= RESULT_SKILL_PEACE;					// Light 를 걸었을 때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_PEACE].OriginalActionInfo		= SKILL_PEACE;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SANCTUARY].EffectSpriteType			= EFFECTSPRITETYPE_SANCTUARY_2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SANCTUARY].ActionInfo					= RESULT_SKILL_SANCTUARY;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SANCTUARY].OriginalActionInfo			= SKILL_SANCTUARY;
	
	// [새기술8]
	(*g_pEffectStatusTable)[EFFECTSTATUS_REFLECTION].EffectSpriteType		= EFFECTSPRITETYPE_NULL;//EFFECTSPRITETYPE_REFLECTION_2;		// Light 를 걸었을 때.
	//(*g_pEffectStatusTable)[EFFECTSTATUS_REFLECTION].ActionInfo				= RESULT_SKILL_REFLECTION;					// Light 를 걸었을 때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_REFLECTION].OriginalActionInfo		= SKILL_REFLECTION;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_HALLUCINATION].EffectSpriteType		= EFFECTSPRITETYPE_CURSE_BLIND;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HALLUCINATION].ActionInfo				= RESULT_MAGIC_HALLUCINATION;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HALLUCINATION].OriginalActionInfo		= MAGIC_HALLUCINATION;
	

	(*g_pEffectStatusTable)[EFFECTSTATUS_CASKET].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DEATH].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DEATH].OriginalActionInfo		= MAGIC_DEATH;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_DEATH].ActionInfo				= RESULT_MAGIC_DEATH;

	// 2002.3.23 추가	
	(*g_pEffectStatusTable)[EFFECTSTATUS_CURE_CRITICAL_WOUNDS].EffectSpriteType		= EFFECTSPRITETYPE_CURE_1_1;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CURE_CRITICAL_WOUNDS].ActionInfo				= RESULT_MAGIC_CURE_CRITICAL_WOUNDS;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CURE_CRITICAL_WOUNDS].OriginalActionInfo		= MAGIC_CURE_CRITICAL_WOUNDS;

	// 2002.12.30 추가	
	(*g_pEffectStatusTable)[EFFECTSTATUS_SPIRIT_GUARD_1].EffectSpriteType		= EFFECTSPRITETYPE_SPIRIT_GUARD;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SPIRIT_GUARD_1].OriginalActionInfo		= SKILL_SPIRIT_GUARD;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SPIRIT_GUARD_2].EffectSpriteType		= EFFECTSPRITETYPE_SPIRIT_GUARD;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SPIRIT_GUARD_2].OriginalActionInfo		= SKILL_SPIRIT_GUARD;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SPIRIT_GUARD_3].EffectSpriteType		= EFFECTSPRITETYPE_SPIRIT_GUARD;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SPIRIT_GUARD_3].OriginalActionInfo		= SKILL_SPIRIT_GUARD;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SPIRIT_GUARD_4].EffectSpriteType		= EFFECTSPRITETYPE_SPIRIT_GUARD;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SPIRIT_GUARD_4].OriginalActionInfo		= SKILL_SPIRIT_GUARD;

	// 2002.2.23 추가
	(*g_pEffectStatusTable)[EFFECTSTATUS_EXTREME].EffectSpriteType		= EFFECTSPRITETYPE_EXTREME_L_1_STAND_MALE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_EXTREME].ActionInfo				= RESULT_SKILL_EXTREME;
	(*g_pEffectStatusTable)[EFFECTSTATUS_EXTREME].OriginalActionInfo		= SKILL_EXTREME;

//	(*g_pEffectStatusTable)[EFFECTSTATUS_HYPNOSIS].EffectSpriteType		= EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_HYPNOSIS].ActionInfo				= RESULT_SKILL_HYPNOSIS;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_HYPNOSIS].OriginalActionInfo		= SKILL_HYPNOSIS;
	
//	(*g_pEffectStatusTable)[EFFECTSTATUS_ARMAGEDDON].EffectSpriteType		= EFFECTSPRITETYPE_ARMAGEDDON_BACK_1_2;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_ARMAGEDDON].ActionInfo				= RESULT_SKILL_ARMAGEDDON;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_ARMAGEDDON].OriginalActionInfo		= SKILL_ARMAGEDDON;	

	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_BAT].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_CHARM].EffectSpriteType		= EFFECTSPRITETYPE_CHARM_2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CHARM].ActionInfo				= RESULT_SKILL_CHARM;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CHARM].OriginalActionInfo		= SKILL_CHARM;


	(*g_pEffectStatusTable)[EFFECTSTATUS_MEPHISTO].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_MEPHISTO].OriginalActionInfo = SKILL_MEPHISTO;

	(*g_pEffectStatusTable)[EFFECTSTATUS_ACID_STORM].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_POISON_STORM].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLOODY_STORM].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ACID_STORM_TO_CREATURE].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_POISON_STORM_TO_CREATURE].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLOODY_STORM_TO_CREATURE].EffectSpriteType	= EFFECTSPRITETYPE_NULL;

	(*g_pEffectStatusTable)[EFFECTSTATUS_ENERGY_DROP].EffectSpriteType	= EFFECTSPRITETYPE_NULL;	
	(*g_pEffectStatusTable)[EFFECTSTATUS_ENERGY_DROP_TO_CREATURE].EffectSpriteType	= EFFECTSPRITETYPE_NULL;	
	(*g_pEffectStatusTable)[EFFECTSTATUS_VIGOR_DROP].EffectSpriteType	= EFFECTSPRITETYPE_NULL;	
	(*g_pEffectStatusTable)[EFFECTSTATUS_VIGOR_DROP_TO_CREATURE].EffectSpriteType	= EFFECTSPRITETYPE_NULL;	
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_CAUSE_CRITICAL_WOUNDS].bUseEffectSprite			= true;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_CAUSE_CRITICAL_WOUNDS].EffectSpriteType			= EFFECTSPRITETYPE_NULL;	
	(*g_pEffectStatusTable)[EFFECTSTATUS_CAUSE_CRITICAL_WOUNDS].ActionInfo				= RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CAUSE_CRITICAL_WOUNDS].OriginalActionInfo			= MAGIC_CAUSE_CRITICAL_WOUNDS;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_CAUSE_CRITICAL_WOUNDS].EffectColor				= 0;

    (*g_pEffectStatusTable)[EFFECTSTATUS_TRANSPORT_ITEM].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
    (*g_pEffectStatusTable)[EFFECTSTATUS_ADD_ITEM].EffectSpriteType	= EFFECTSPRITETYPE_NULL;

//    (*g_pEffectStatusTable)[EFFECTSTATUS_RELIC].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
//    (*g_pEffectStatusTable)[EFFECTSTATUS_HAS_RELIC].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
    (*g_pEffectStatusTable)[EFFECTSTATUS_INCRASE_ATTR].EffectSpriteType	= EFFECTSPRITETYPE_NULL;

    (*g_pEffectStatusTable)[EFFECTSTATUS_HYMN].EffectSpriteType	= EFFECTSPRITETYPE_NULL;

	// [새기술2]
	(*g_pEffectStatusTable)[EFFECTSTATUS_OBSERVING_EYE].EffectSpriteType				= EFFECTSPRITETYPE_OBSERVINGEYE_REDEYE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_OBSERVING_EYE].OriginalActionInfo				= SKILL_OBSERVING_EYE;


    (*g_pEffectStatusTable)[EFFECTSTATUS_METEOR_STRIKE].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
    (*g_pEffectStatusTable)[EFFECTSTATUS_METEOR_STRIKE].OriginalActionInfo	= MAGIC_METEOR;
    (*g_pEffectStatusTable)[EFFECTSTATUS_METEOR_STRIKE].ActionInfo			= RESULT_MAGIC_METEOR;

	(*g_pEffectStatusTable)[EFFECTSTATUS_IMMUNE_TO_BLOOD_DRAIN].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_IMMUNE_TO_PARALYZE].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_IMMUNE_TO_POISON].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_IMMUNE_TO_ACID].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_IMMUNE_TO_CURSE].EffectSpriteType	= EFFECTSPRITETYPE_NULL;

	(*g_pEffectStatusTable)[EFFECTSTATUS_DECREASE_HP].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_INCREASE_HP].EffectSpriteType	= EFFECTSPRITETYPE_NULL;

	(*g_pEffectStatusTable)[EFFECTSTATUS_BLOODY_WALL].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLOODY_WALL].ActionInfo	= RESULT_MAGIC_BLOODY_WALL_SINGLE;

	(*g_pEffectStatusTable)[EFFECTSTATUS_BLOODY_WALL_BLOCKED].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLOODY_WALL_BLOCKED].ActionInfo	= RESULT_MAGIC_BLOODY_WALL_SINGLE;

	(*g_pEffectStatusTable)[EFFECTSTATUS_BLOODY_WALL_SNAKE].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLOODY_WALL_SNAKE].ActionInfo	= RESULT_MAGIC_BLOODY_WALL_SINGLE;

	/*
	(*g_pEffectStatusTable)[EFFECTSTATUS_PROTECTION_FROM_PARALYSIS].EffectSpriteType	= EFFECTSPRITETYPE_NULL;// ProtecitonFromPoison 을 걸었을때.
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_PARALYSIS].bUseEffectSprite			= false;
	(*g_pEffectStatusTable)[EFFECTSTATUS_PARALYSIS].EffectColor					= 393;//156;
	(*g_pEffectStatusTable)[EFFECTSTATUS_PARALYSIS].ActionInfo				= RESULT_MAGIC_PARALYZE;

	(*g_pEffectStatusTable)[EFFECTSTATUS_CURSE_PARALYSIS].bUseEffectSprite			= false;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CURSE_PARALYSIS].EffectColor			= 156;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CURSE_PARALYSIS].ActionInfo				= RESULT_MAGIC_PARALYZE;
	

	// 2001/04/04 - 새로 추가된 것들 	
	(*g_pEffectStatusTable)[EFFECTSTATUS_DECAY_CORPSE].EffectSpriteType		= EFFECTSPRITETYPE_NULL;			// 일정 시간이 지나면 시체가 사라짐
	(*g_pEffectStatusTable)[EFFECTSTATUS_DEAD_CREATURE].EffectSpriteType		= EFFECTSPRITETYPE_NULL; 		// 일정 시간이 지나면 죽음 처리를 해줌.
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHUT_DOWN].EffectSpriteType		= EFFECTSPRITETYPE_NULL; 			// 일정 시간이 지나면 서버를 종료한다.
	(*g_pEffectStatusTable)[EFFECTSTATUS_HP_RECOVERY].EffectSpriteType		= EFFECTSPRITETYPE_NULL; 			// 포션등에 의한 hp 회복
	(*g_pEffectStatusTable)[EFFECTSTATUS_DECAY_ITEM].EffectSpriteType		= EFFECTSPRITETYPE_NULL; 			// 
	(*g_pEffectStatusTable)[EFFECTSTATUS_ARMOR_CRASH].EffectSpriteType		= EFFECTSPRITETYPE_NULL;			// 일정시간 방어력 하강.
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_PROTECTION_FIELD].EffectSpriteType		= EFFECTSPRITETYPE_NULL;			//  

	(*g_pEffectStatusTable)[EFFECTSTATUS_RAGE].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_REQUIEM].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ENORMOUSE_POWER].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_CONTINUAL_LIGHT ].EffectSpriteType		= EFFECTSPRITETYPE_NULL;		// Continual Light를 걸었을때.

	(*g_pEffectStatusTable)[EFFECTSTATUS_ACID_SWAMP].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DETECT_MINE].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_INSTALL].EffectSpriteType		= EFFECTSPRITETYPE_NULL;				// mine install( install되면 안보인다)
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_AURA_PRISM].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_AURA_PRISM].bAttachGround		= true;

	
	(*g_pEffectStatusTable)[EFFECTSTATUS_FADE_OUT].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CHRIST_AURA].EffectSpriteType		= EFFECTSPRITETYPE_NULL;

	(*g_pEffectStatusTable)[EFFECTSTATUS_CURSE].EffectSpriteType		= EFFECTSPRITETYPE_CURSE_2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CURSE].ActionInfo				= RESULT_MAGIC_DOOM;
	*/

	// 2002.6.12 전쟁관련 이펙트들
	(*g_pEffectStatusTable)[EFFECTSTATUS_SLAYER_RELIC].EffectSpriteType		= EFFECTSPRITETYPE_RELIC_SLAYER;
	(*g_pEffectStatusTable)[EFFECTSTATUS_VAMPIRE_RELIC].EffectSpriteType		= EFFECTSPRITETYPE_RELIC_VAMPIRE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SLAYER_RELIC].EffectSpriteType		= EFFECTSPRITETYPE_RELIC_CHARACTER_SLAYER;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_VAMPIRE_RELIC].EffectSpriteType		= EFFECTSPRITETYPE_RELIC_CHARACTER_VAMPIRE_SKULL;


	(*g_pEffectStatusTable)[EFFECTSTATUS_SOUL_CHAIN].EffectSpriteType			= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SOUL_CHAIN].ActionInfo					= RESULT_SKILL_SOUL_CHAIN;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SOUL_CHAIN].OriginalActionInfo			= SKILL_SOUL_CHAIN;

	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_1].EffectSpriteType			= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_1].ActionInfo					= SKILL_FIRE_CRACKER_1;

	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_2].EffectSpriteType			= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_2].ActionInfo					= SKILL_FIRE_CRACKER_2;

	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_3].EffectSpriteType			= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_3].ActionInfo					= SKILL_FIRE_CRACKER_3;

	(*g_pEffectStatusTable)[EFFECTSTATUS_TRANSPORT_CREATURE].EffectSpriteType			= EFFECTSPRITETYPE_NULL;

	(*g_pEffectStatusTable)[EFFECTSTATUS_LEVELUP_SLAYER].EffectSpriteType			= EFFECTSPRITETYPE_SLAYER_LEVELUP_FRONT;
	(*g_pEffectStatusTable)[EFFECTSTATUS_LEVELUP_VAMPIRE].EffectSpriteType			= EFFECTSPRITETYPE_VAMPIRE_LEVELUP_FRONT;

	(*g_pEffectStatusTable)[EFFECTSTATUS_CLIENTONLY_XMAS_TREE].EffectSpriteType			= EFFECTSPRITETYPE_XMAS_TREE;

	// 2002.12.27
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHARP_SHIELD_1].EffectSpriteType		= EFFECTSPRITETYPE_SHARP_SHIELD_TOP;		// Light 를 걸었을 때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHARP_SHIELD_1].OriginalActionInfo		= SKILL_SHARP_SHIELD;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SHARP_SHIELD_2].EffectSpriteType		= EFFECTSPRITETYPE_SHARP_SHIELD_2;		// Light 를 걸었을 때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHARP_SHIELD_2].OriginalActionInfo		= SKILL_SHARP_SHIELD;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SHARP_SHIELD_3].EffectSpriteType		= EFFECTSPRITETYPE_SHARP_SHIELD_BOTTOM;		// Light 를 걸었을 때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHARP_SHIELD_3].OriginalActionInfo		= SKILL_SHARP_SHIELD;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SHARP_SHIELD_4].EffectSpriteType		= EFFECTSPRITETYPE_SHARP_SHIELD_BOTTOM_2;		// Light 를 걸었을 때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHARP_SHIELD_4].OriginalActionInfo		= SKILL_SHARP_SHIELD;

	// 2002.12.27
	(*g_pEffectStatusTable)[EFFECTSTATUS_AIR_SHIELD_1].EffectSpriteType		= EFFECTSPRITETYPE_AIR_SHIELD_LEFT;		// Light 를 걸었을 때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_AIR_SHIELD_1].OriginalActionInfo		= SKILL_AIR_SHIELD;

	(*g_pEffectStatusTable)[EFFECTSTATUS_AIR_SHIELD_2].EffectSpriteType		= EFFECTSPRITETYPE_AIR_SHIELD_2;		// Light 를 걸었을 때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_AIR_SHIELD_2].OriginalActionInfo		= SKILL_AIR_SHIELD;

	(*g_pEffectStatusTable)[EFFECTSTATUS_AIR_SHIELD_3].EffectSpriteType		= EFFECTSPRITETYPE_AIR_SHIELD_RIGHT;		// Light 를 걸었을 때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_AIR_SHIELD_3].OriginalActionInfo		= SKILL_AIR_SHIELD;

	(*g_pEffectStatusTable)[EFFECTSTATUS_AIR_SHIELD_4].EffectSpriteType		= EFFECTSPRITETYPE_AIR_SHIELD_LEFT_2;		// Light 를 걸었을 때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_AIR_SHIELD_4].OriginalActionInfo		= SKILL_AIR_SHIELD;

	// 2002.12.30
	(*g_pEffectStatusTable)[EFFECTSTATUS_SLEEP].EffectSpriteType		= EFFECTSPRITETYPE_SLEEP;		// Light 를 걸었을 때.
	(*g_pEffectStatusTable)[EFFECTSTATUS_SLEEP].ActionInfo		= RESULT_SKILL_REBUKE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SLEEP].OriginalActionInfo		= SKILL_REBUKE;

	// 2002.12.31
	(*g_pEffectStatusTable)[EFFECTSTATUS_GUN_SHOT_GUIDANCE_AIM].OriginalActionInfo		= SKILL_GUN_SHOT_GUIDANCE;

	(*g_pEffectStatusTable)[EFFECTSTATUS_GUN_SHOT_GUIDANCE_POINT].EffectSpriteType		= EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_POINT;
	(*g_pEffectStatusTable)[EFFECTSTATUS_GUN_SHOT_GUIDANCE_POINT].ActionInfo		= RESULT_SKILL_GUN_SHOT_GUIDANCE_POINT;

//	(*g_pEffectStatusTable)[EFFECTSTATUS_GUN_SHOT_GUIDANCE_FIRE].EffectSpriteType		= EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_POINT;
	(*g_pEffectStatusTable)[EFFECTSTATUS_GUN_SHOT_GUIDANCE_FIRE].ActionInfo		= RESULT_SKILL_GUN_SHOT_GUIDANCE_BOMB;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_GUN_SHOT_GUIDANCE_POINT].OriginalActionInfo		= SKILL_REBUKE;

	// 2003.1.29

	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_BLOOD_BIBLE_GREGORI].EffectSpriteType = EFFECTSPRITETYPE_GREGORI;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_BLOOD_BIBLE_NEMA].EffectSpriteType = EFFECTSPRITETYPE_NEMA;	// 네마
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_BLOOD_BIBLE_LEGIOS].EffectSpriteType = EFFECTSPRITETYPE_LEGIOS;		// 레지오스
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_BLOOD_BIBLE_MIHOLE].EffectSpriteType = EFFECTSPRITETYPE_MIHOLE;		// 미호레
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_BLOOD_BIBLE_AROSA].EffectSpriteType = EFFECTSPRITETYPE_AROSA;			// 아로사
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_BLOOD_BIBLE_ARMEGA].EffectSpriteType = EFFECTSPRITETYPE_ARMEGA;		// 아르메가
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_BLOOD_BIBLE_INI].EffectSpriteType = EFFECTSPRITETYPE_INI;			// 아이니
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_BLOOD_BIBLE_JAVE].EffectSpriteType = EFFECTSPRITETYPE_JAVE;			// 쟈브
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_BLOOD_BIBLE_CHASPA].EffectSpriteType = EFFECTSPRITETYPE_CHASPA;		// 차스파
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_BLOOD_BIBLE_CONCILIA].EffectSpriteType = EFFECTSPRITETYPE_CONCILIA;		// 콘칠리아
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_BLOOD_BIBLE_KIRO].EffectSpriteType = EFFECTSPRITETYPE_KIRO;			// 키로
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_BLOOD_BIBLE_HILLEL].EffectSpriteType = EFFECTSPRITETYPE_HILLEL;		// 힐릴

	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_GUARD_GREGORI].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_GUARD_GREGORI;				// 163
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_GUARD_NEMA].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_GUARD_NEMA;				// 164
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_GUARD_LEGIOS].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_GUARD_LEGIOS;				// 165
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_GUARD_MIHOLE].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_GUARD_MIHOLE;				// 166
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_GUARD_AROSA].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_GUARD_AROSA;				// 167
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_GUARD_ARMEGA].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_GUARD_ARMEGA;				// 168
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_GUARD_INI].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_GUARD_INI;				// 169
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_GUARD_JAVE].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_GUARD_JAVE;				// 170
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_GUARD_CHASPA].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_GUARD_CHASPA;				// 171
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_GUARD_CONCILIA].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_GUARD_CONCILIA;				// 172
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_GUARD_KIRO].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_GUARD_KIRO;				// 173
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_GUARD_HILLEL].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_GUARD_HILLEL;				// 174

	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_HOLY_GREGORI].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_HOLY_GREGORI;				// 175
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_HOLY_NEMA].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_HOLY_NEMA;				// 176
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_HOLY_LEGIOS].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_HOLY_LEGIOS;				// 177
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_HOLY_MIHOLE].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_HOLY_MIHOLE;				// 178
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_HOLY_AROSA].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_HOLY_AROSA;				// 179
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_HOLY_ARMEGA].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_HOLY_ARMEGA;				// 180
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_HOLY_INI].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_HOLY_INI;				// 181
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_HOLY_JAVE].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_HOLY_JAVE;				// 182
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_HOLY_CHASPA].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_HOLY_CHASPA;				// 183
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_HOLY_CONCILIA].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_HOLY_CONCILIA;			// 184
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_HOLY_KIRO].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_HOLY_KIRO;			// 185
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_HOLY_HILLEL].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_HOLY_HILLEL;			// 186

	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_GUARD_WARP].EffectSpriteType = EFFECTSPRITETYPE_WARP_BLOOD_BIBLE_CASTLE;			// 187
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_HOLY_WARP].EffectSpriteType = EFFECTSPRITETYPE_WARP_BLOOD_BIBLE_HOLY;			// 188
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_CHANGE_CASTLE_CHANGED].EffectSpriteType = EFFECTSPRITETYPE_NULL;		// 189

	(*g_pEffectStatusTable)[EFFECTSTATUS_SHRINE_SHIELD].EffectSpriteType = EFFECTSPRITETYPE_SHRINE_SHIELD_ING;	
	(*g_pEffectStatusTable)[EFFECTSTATUS_TOWER_SHIELD].EffectSpriteType = EFFECTSPRITETYPE_NULL;		// 191
//	(*g_pEffectStatusTable)[EFFECTSTATUS_DROP_BLOOD_BIBLE].EffectSpriteType = EFFECTSPRITETYPE_DROP_BLOOD_BIBLE;			// 192 피의성서가 떨어졌을때
//	(*g_pEffectStatusTable)[EFFECTSTATUS_DROP_BLOOD_BIBLE].ActionInfo					= DROP_BLOOD_BIBLE;	

	(*g_pEffectStatusTable)[EFFECTSTATUS_TRANSPORT_ITEM_TO_CORPSE].EffectSpriteType = EFFECTSPRITETYPE_NULL;          // 193
    (*g_pEffectStatusTable)[EFFECTSTATUS_ADD_ITEM_TO_CORPSE].EffectSpriteType = EFFECTSPRITETYPE_NULL;                // 194

	(*g_pEffectStatusTable)[EFFECTSTATUS_WARP_BLOOD_BIBLE_FROM_ME].EffectSpriteType = EFFECTSPRITETYPE_WARP_BLOOD_BIBLE_HEAD;	// 195
	(*g_pEffectStatusTable)[EFFECTSTATUS_WARP_BLOOD_BIBLE_FROM_TILE].EffectSpriteType = EFFECTSPRITETYPE_WARP_BLOOD_BIBLE_TILE;			// 196
	(*g_pEffectStatusTable)[EFFECTSTATUS_WARP_BLOOD_BIBLE_FROM_TILE].ActionInfo = WARP_BLOOD_BIBLE_TILE;

	(*g_pEffectStatusTable)[EFFECTSTATUS_WARP_HOLY_LAND_VAMPIRE].EffectSpriteType = EFFECTSPRITETYPE_WARP_HOLY_LAND_VAMPIRE_START;			// 197 뱀파이어가 포탈로 이동할때
	(*g_pEffectStatusTable)[EFFECTSTATUS_WARP_HOLY_LAND_VAMPIRE].ActionInfo		= HOLY_LAND_WARP_VAMPIRE;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_WARP_HOLY_LAND_SLAYER].EffectSpriteType = EFFECTSPRITETYPE_WARP_HOLY_LAND_SLAYER_START;				// 198 슬레이어가 포탈로 이동할때
	(*g_pEffectStatusTable)[EFFECTSTATUS_WARP_HOLY_LAND_SLAYER].ActionInfo	= HOLY_LAND_WARP_SLAYER;

	(*g_pEffectStatusTable)[EFFECTSTATUS_AMBER_OF_GUARD].EffectSpriteType = EFFECTSPRITETYPE_AMBER_OF_GUARD;
	(*g_pEffectStatusTable)[EFFECTSTATUS_AMBER_OF_AVENGER].EffectSpriteType = EFFECTSPRITETYPE_AMBER_OF_AVENGER;
	(*g_pEffectStatusTable)[EFFECTSTATUS_AMBER_OF_IMMORTAL].EffectSpriteType = EFFECTSPRITETYPE_AMBER_OF_IMMORTAL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_AMBER_OF_CURSE].EffectSpriteType = EFFECTSPRITETYPE_AMBER_OF_CURSE;

	(*g_pEffectStatusTable)[EFFECTSTATUS_WARP_BLOOD_BIBLE_SLAYER].EffectSpriteType = EFFECTSPRITETYPE_WARP_BLOOD_BIBLE_SLAYER;
	(*g_pEffectStatusTable)[EFFECTSTATUS_WARP_BLOOD_BIBLE_VAMPIRE].EffectSpriteType = EFFECTSPRITETYPE_WARP_BLOOD_BIBLE_VAMPIRE;

	(*g_pEffectStatusTable)[EFFECTSTATUS_LOVE_CHAIN].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_LOVE_CHAIN].ActionInfo	= SKILL_LOVE_CHAIN;
	(*g_pEffectStatusTable)[EFFECTSTATUS_LOVE_CHAIN].OriginalActionInfo		= SKILL_LOVE_CHAIN;

	(*g_pEffectStatusTable)[EFFECTSTATUS_PK_ZONE_RESURRECTION].EffectSpriteType = EFFECTSPRITETYPE_PK_ZONE_RESURRECTION;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_MAGIC_ELUSION].EffectSpriteType = EFFECTSPRITETYPE_MAGIC_ELUSION_ING;
	(*g_pEffectStatusTable)[EFFECTSTATUS_MAGIC_ELUSION].ActionInfo = RESULT_SKILL_MAGIC_ELUSION;
	(*g_pEffectStatusTable)[EFFECTSTATUS_MAGIC_ELUSION].OriginalActionInfo = SKILL_MAGIC_ELUSION;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_POISON_MESH].EffectSpriteType = EFFECTSPRITETYPE_POISON_MESH_ING;
	(*g_pEffectStatusTable)[EFFECTSTATUS_POISON_MESH].ActionInfo = RESULT_SKILL_POISON_MESH;
	(*g_pEffectStatusTable)[EFFECTSTATUS_POISON_MESH].OriginalActionInfo = SKILL_POISON_MESH;

	(*g_pEffectStatusTable)[EFFECTSTATUS_ILLUSION_OF_AVENGE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ILLUSION_OF_AVENGE].ActionInfo = RESULT_SKILL_ILLUSION_OF_AVENGE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ILLUSION_OF_AVENGE].OriginalActionInfo = SKILL_ILLUSION_OF_AVENGE;

	(*g_pEffectStatusTable)[EFFECTSTATUS_WILL_OF_LIFE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_WILL_OF_LIFE].ActionInfo = RESULT_SKILL_WILL_OF_LIFE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_WILL_OF_LIFE].OriginalActionInfo = SKILL_WILL_OF_LIFE;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_DENIAL_MAGIC].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DENIAL_MAGIC].ActionInfo = RESULT_SKILL_DENIAL_MAGIC;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DENIAL_MAGIC].OriginalActionInfo = SKILL_DENIAL_MAGIC;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_DENIAL_MAGIC_DAMAGED].EffectSpriteType = EFFECTSPRITETYPE_DENIAL_MAGIC_DAMAGE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DENIAL_MAGIC_DAMAGED].ActionInfo = SKILL_DENIAL_MAGIC_DAMAGED;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_REQUITAL].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_REQUITAL].ActionInfo = RESULT_SKILL_REQUITAL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_REQUITAL].OriginalActionInfo = SKILL_REQUITAL;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_CONCEALMENT].EffectSpriteType = EFFECTSPRITETYPE_CONCEALMENT_ING;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CONCEALMENT].ActionInfo = RESULT_SKILL_CONCEALMENT;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CONCEALMENT].OriginalActionInfo = SKILL_CONCEALMENT;

	(*g_pEffectStatusTable)[EFFECTSTATUS_DRAGON_FIRE_CRACKER].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DRAGON_FIRE_CRACKER].ActionInfo = SKILL_DRAGON_FIRE_CRACKER;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_4].EffectSpriteType			= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_4].ActionInfo					= SKILL_FIRE_CRACKER_4;

	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_VOLLEY_1].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_VOLLEY_1].ActionInfo			= SKILL_FIRE_CRACKER_VOLLEY_1;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_VOLLEY_2].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_VOLLEY_2].ActionInfo			= SKILL_FIRE_CRACKER_VOLLEY_2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_VOLLEY_3].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_VOLLEY_3].ActionInfo			= SKILL_FIRE_CRACKER_VOLLEY_3;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_VOLLEY_4].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_VOLLEY_4].ActionInfo			= SKILL_FIRE_CRACKER_VOLLEY_4;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_WIDE_VOLLEY_1].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_WIDE_VOLLEY_1].ActionInfo			= SKILL_FIRE_CRACKER_WIDE_VOLLEY_1;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_WIDE_VOLLEY_2].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_WIDE_VOLLEY_2].ActionInfo			= SKILL_FIRE_CRACKER_WIDE_VOLLEY_2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_WIDE_VOLLEY_3].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_WIDE_VOLLEY_3].ActionInfo			= SKILL_FIRE_CRACKER_WIDE_VOLLEY_3;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_WIDE_VOLLEY_4].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_WIDE_VOLLEY_4].ActionInfo			= SKILL_FIRE_CRACKER_WIDE_VOLLEY_4;

	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_STORM].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_CRACKER_STORM].ActionInfo		= SKILL_FIRE_CRACKER_STORM;	

	(*g_pEffectStatusTable)[EFFECTSTATUS_TRANSLATION].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_TRANSLATION].ActionInfo = SKILL_TRANSLATION;
	(*g_pEffectStatusTable)[EFFECTSTATUS_TRANSLATION].OriginalActionInfo = SKILL_TRANSLATION;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_LIGHTNESS].EffectSpriteType = EFFECTSPRITETYPE_LIGHTNESS_2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_LIGHTNESS].ActionInfo = RESULT_SKILL_LIGHTNESS;
	(*g_pEffectStatusTable)[EFFECTSTATUS_LIGHTNESS].OriginalActionInfo = SKILL_LIGHTNESS;

	(*g_pEffectStatusTable)[EFFECTSTATUS_EVADE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_EVADE].OriginalActionInfo = SKILL_EVADE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_EVADE].ActionInfo = RESULT_SKILL_EVADE;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLUNTING].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLUNTING].OriginalActionInfo = SKILL_BLUNTING;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLUNTING].ActionInfo = RESULT_SKILL_EVADE;

	(*g_pEffectStatusTable)[EFFECTSTATUS_CROSS_GUARD].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CROSS_GUARD].OriginalActionInfo = SKILL_CROSS_GUARD;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_CROSS_GUARD].ActionInfo = RESULT_SKILL_CROSS_GUARD;

	(*g_pEffectStatusTable)[EFFECTSTATUS_HANDS_OF_FIRE].EffectSpriteType = EFFECTSPRITETYPE_HANDS_OF_FIRE_1; // 빨간게 지속이라는데..
	(*g_pEffectStatusTable)[EFFECTSTATUS_HANDS_OF_FIRE].OriginalActionInfo = SKILL_HANDS_OF_FIRE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HANDS_OF_FIRE].ActionInfo = RESULT_SKILL_HANDS_OF_FIRE;

	(*g_pEffectStatusTable)[EFFECTSTATUS_PROMINENCE].EffectSpriteType = EFFECTSPRITETYPE_PROMINENCE_ING;
	(*g_pEffectStatusTable)[EFFECTSTATUS_PROMINENCE].OriginalActionInfo = SKILL_PROMINENCE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_PROMINENCE].ActionInfo = RESULT_SKILL_PROMINENCE;

	(*g_pEffectStatusTable)[EFFECTSTATUS_RING_OF_FLARE].EffectSpriteType = EFFECTSPRITETYPE_RING_OF_FLARE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_RING_OF_FLARE].OriginalActionInfo = SKILL_RING_OF_FLARE;

	(*g_pEffectStatusTable)[EFFECTSTATUS_WATER_BARRIER].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_WATER_BARRIER].OriginalActionInfo = SKILL_WATER_BARRIER;
	(*g_pEffectStatusTable)[EFFECTSTATUS_WATER_BARRIER].ActionInfo = RESULT_SKILL_WATER_BARRIER;

	(*g_pEffectStatusTable)[EFFECTSTATUS_TENDRIL].EffectSpriteType = EFFECTSPRITETYPE_TENDRIL_ING;
	(*g_pEffectStatusTable)[EFFECTSTATUS_TENDRIL].OriginalActionInfo = SKILL_TENDRIL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_TENDRIL].ActionInfo = RESULT_SKILL_TENDRIL;

	(*g_pEffectStatusTable)[EFFECTSTATUS_GNOME_WHISPER].EffectSpriteType = EFFECTSPRITETYPE_GNOMES_WHISPER;
	(*g_pEffectStatusTable)[EFFECTSTATUS_GNOME_WHISPER].OriginalActionInfo = SKILL_GNOMES_WHISPER;

	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_FIELD].EffectSpriteType = EFFECTSPRITETYPE_ICE_FIELD_2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_FIELD].ActionInfo = RESULT_SKILL_ICE_FIELD;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_FIELD].OriginalActionInfo = SKILL_ICE_FIELD;

	(*g_pEffectStatusTable)[EFFECTSTATUS_HELLFIRE].EffectSpriteType = EFFECTSPRITETYPE_HELLFIRE_ING;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HELLFIRE].ActionInfo = RESULT_SKILL_HELLFIRE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HELLFIRE].OriginalActionInfo = SKILL_HELLFIRE;

	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_FIELD_TO_CREATURE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_FIELD_TO_CREATURE].OriginalActionInfo = SKILL_ICE_FIELD;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_FIELD_TO_CREATURE].bUseEffectSprite		= false;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_FIELD_TO_CREATURE].EffectColor		= 225;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_FIELD_TO_CREATURE].SoundID = SOUND_SLAYER_JABBING_VEIN;

	(*g_pEffectStatusTable)[EFFECTSTATUS_HELLFIRE_TO_ENEMY].EffectSpriteType = EFFECTSPRITETYPE_HELLFIRE_BODY;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_HELLFIRE_TO_ENEMY].ActionInfo = RESULT_SKILL_HELLFIRE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HELLFIRE_TO_ENEMY].OriginalActionInfo = SKILL_HELLFIRE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HELLFIRE_TO_ENEMY].bUseEffectSprite		= true;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_HELLFIRE_TO_ENEMY].EffectColor		= 225;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_HELLFIRE_TO_ENEMY].SoundID = SOUND_SLAYER_JABBING_VEIN;

	(*g_pEffectStatusTable)[EFFECTSTATUS_FROZEN_ARMOR].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FROZEN_ARMOR].ActionInfo = RESULT_SKILL_FROZEN_ARMOR;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FROZEN_ARMOR].OriginalActionInfo = SKILL_FROZEN_ARMOR;

	(*g_pEffectStatusTable)[EFFECTSTATUS_FROZEN_ARMOR_TO_ENEMY].EffectSpriteType = EFFECTSPRITETYPE_FROZEN_ARMOR_GROUND;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FROZEN_ARMOR_TO_ENEMY].OriginalActionInfo = SKILL_FROZEN_ARMOR;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FROZEN_ARMOR_TO_ENEMY].bUseEffectSprite		= true;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FROZEN_ARMOR_TO_ENEMY].EffectColor		= 225;

	(*g_pEffectStatusTable)[EFFECTSTATUS_REACTIVE_ARMOR].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_REACTIVE_ARMOR].OriginalActionInfo = SKILL_REACTIVE_ARMOR;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_SYLPH].EffectSpriteType = EFFECTSPRITETYPE_FAST_MOVE_STOP;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_SYLPH].OriginalActionInfo = SKILL_SUMMON_SYLPH;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_GROUND_BLESS].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_GROUND_BLESS].OriginalActionInfo = SKILL_GROUND_BLESS;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_LEVELUP_OUSTERS].EffectSpriteType = EFFECTSPRITETYPE_OUSTERS_LEVELUP_GROUND;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_BACK_STAB].EffectSpriteType = EFFECTSPRITETYPE_BACK_STAB_1;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_OF_SOUL_STONE].EffectSpriteType = EFFECTSPRITETYPE_FIRE_OF_SOUL_STONE;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_OF_SOUL_STONE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_OF_SOUL_STONE].ActionInfo = ICE_OF_SOUL_STONE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_OF_SOUL_STONE].OriginalActionInfo = SKILL_ICE_OF_SOUL_STONE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_OF_SOUL_STONE].bUseEffectSprite		= false;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_OF_SOUL_STONE].EffectColor		= 0;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_OF_SOUL_STONE].SoundID = SOUND_SLAYER_JABBING_VEIN;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_SAND_OF_SOUL_STONE].EffectSpriteType = EFFECTSPRITETYPE_SAND_OF_SOUL_STONE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SAND_OF_SOUL_STONE].ActionInfo = SAND_OF_SOUL_STONE;

	(*g_pEffectStatusTable)[EFFECTSTATUS_WATER_SHIELD].EffectSpriteType = EFFECTSPRITETYPE_WATER_SHIELD_WATER;

//    (*g_pEffectStatusTable)[EFFECTSTATUS_SHARP_CHAKRAM].ActionInfo = SAND_OF_SOUL_STONE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHARP_CHAKRAM].OriginalActionInfo = SKILL_SHARP_CHAKRAM;

//    (*g_pEffectStatusTable)[EFFECTSTATUS_DESTRUCTION_SPEAR].ActionInfo = SAND_OF_SOUL_STONE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DESTRUCTION_SPEAR].OriginalActionInfo = SKILL_DESTRUCTION_SPEAR;
    
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLESS_FIRE].ActionInfo = BLESS_FIRE;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_BLESS_FIRE].EffectSpriteType = EFFECTSPRITETYPE_BLESS_FIRE_GROUND;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_BLESS_FIRE].OriginalActionInfo = SKILL_BLESS_FIRE;

    (*g_pEffectStatusTable)[EFFECTSTATUS_WATER_SHIELD].ActionInfo = WATER_SHIELD;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_WATER_SHIELD].OriginalActionInfo = SKILL_WATER_SHIELD;
    
	(*g_pEffectStatusTable)[EFFECTSTATUS_SAND_CROSS].ActionInfo = SAND_CROSS;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_SAND_CROSS].OriginalActionInfo = SKILL_SAND_CROSS;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLOCK_HEAD].EffectSpriteType = EFFECTSPRITETYPE_BLOCK_HEAD;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLOCK_HEAD].OriginalActionInfo = SKILL_BLOCK_HEAD;	
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_BACK_STAB_2].EffectSpriteType = EFFECTSPRITETYPE_BACK_STAB_2;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_BACK_STAB_3].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BACK_STAB_3].ActionInfo = BACK_STAB_GRADE_3;

	(*g_pEffectStatusTable)[EFFECTSTATUS_PROMINENCE_2].EffectSpriteType = EFFECTSPRITETYPE_PROMINENCE_ING;
	(*g_pEffectStatusTable)[EFFECTSTATUS_PROMINENCE_2].OriginalActionInfo = STEP_SKILL_PROMINENCE_2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_PROMINENCE_2].ActionInfo = RESULT_STEP_SKILL_PROMINENCE_2;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_PROMINENCE_3].EffectSpriteType = EFFECTSPRITETYPE_PROMINENCE_ING;
	(*g_pEffectStatusTable)[EFFECTSTATUS_PROMINENCE_3].OriginalActionInfo = STEP_SKILL_PROMINENCE_3;
	(*g_pEffectStatusTable)[EFFECTSTATUS_PROMINENCE_3].ActionInfo = RESULT_STEP_SKILL_PROMINENCE_3;


	(*g_pEffectStatusTable)[EFFECTSTATUS_RING_OF_FLARE_2].EffectSpriteType = EFFECTSPRITETYPE_RING_OF_FLARE2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_RING_OF_FLARE_2].OriginalActionInfo = SKILL_RING_OF_FLARE;

	(*g_pEffectStatusTable)[EFFECTSTATUS_RING_OF_FLARE_3].EffectSpriteType = EFFECTSPRITETYPE_RING_OF_FLARE3;
	(*g_pEffectStatusTable)[EFFECTSTATUS_RING_OF_FLARE_3].OriginalActionInfo = SKILL_RING_OF_FLARE;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_DIVINE_SPIRITS].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DIVINE_SPIRITS].OriginalActionInfo = SKILL_DIVINE_SPIRITS;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_LOUD].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_LOUD].OriginalActionInfo = SKILL_MEGAPHONE;

	(*g_pEffectStatusTable)[EFFECTSTATUS_DIVINE_GUIDANCE].EffectSpriteType = EFFECTSPRITETYPE_DIVINE_GUIDANCE_ING;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DIVINE_GUIDANCE].OriginalActionInfo = SKILL_DIVINE_GUIDANCE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DIVINE_GUIDANCE].ActionInfo = RESULT_SKILL_DIVINE_GUIDANCE;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_JABBING_VEIN].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_JABBING_VEIN].OriginalActionInfo = SKILL_JABBING_VEIN;
	(*g_pEffectStatusTable)[EFFECTSTATUS_JABBING_VEIN].bUseEffectSprite		= false;
	(*g_pEffectStatusTable)[EFFECTSTATUS_JABBING_VEIN].EffectColor		= 225;	
	(*g_pEffectStatusTable)[EFFECTSTATUS_JABBING_VEIN].SoundID = SOUND_SLAYER_JABBING_VEIN;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_FLAG].EffectSpriteType = EFFECTSPRITETYPE_FLAG_HEAD;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FLAG_INSERT].EffectSpriteType = EFFECTSPRITETYPE_FLAG_GROUND;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_MUTE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_MUTE].OriginalActionInfo = SKILL_MUTE;

	(*g_pEffectStatusTable)[EFFECTSTATUS_REDIANCE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_REDIANCE].OriginalActionInfo = SKILL_REDIANCE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_REDIANCE].bUseEffectSprite		= false;
	(*g_pEffectStatusTable)[EFFECTSTATUS_REDIANCE].EffectColor				= 376;
	(*g_pEffectStatusTable)[EFFECTSTATUS_REDIANCE].EffectColorPart			= ADDON_RIGHTHAND;

	(*g_pEffectStatusTable)[EFFECTSTATUS_FAMILY_BONUS].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FAMILY_BONUS].OriginalActionInfo = FAMILY_BONUS;

	(*g_pEffectStatusTable)[EFFECTSTATUS_ETERNITY].EffectSpriteType = EFFECTSPRITETYPE_ETERNITY;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ETERNITY].ActionInfo		= ETERNITY;

	(*g_pEffectStatusTable)[EFFECTSTATUS_HEART_CATALYST].EffectSpriteType = EFFECTSPRITETYPE_HEART_CATALYST;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HEART_CATALYST].OriginalActionInfo = SKILL_HEART_CATALYST;

	(*g_pEffectStatusTable)[EFFECTSTATUS_ETERNITY_PAUSE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ETERNITY_PAUSE].OriginalActionInfo = SKILL_ETERNITY;

//	(*g_pEffectStatusTable)[EFFECTSTATUS_WARP_HOLY_LAND_OUSTERS].EffectSpriteType = EFFECTSPRITETYPE_OUSTERS_PORTAL_HOLY_LAND;				// 198 슬레이어가 포탈로 이동할때
//	(*g_pEffectStatusTable)[EFFECTSTATUS_WARP_HOLY_LAND_OUSTERS].ActionInfo	= HOLY_LAND_WARP_OUSTERS;

	(*g_pEffectStatusTable)[EFFECTSTATUS_TRAP_INSTALLED].EffectSpriteType = EFFECTSPRITETYPE_INSTALL_TRAP;
	(*g_pEffectStatusTable)[EFFECTSTATUS_TRAP_INSTALLED].ActionInfo = TRAP_INSTALLED;

	(*g_pEffectStatusTable)[EFFECTSTATUS_TRAP_TRIGGERED].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_TRAP_TRIGGERED].ActionInfo = TRAP_TRIGGERED;
	(*g_pEffectStatusTable)[EFFECTSTATUS_TRAP_TRIGGERED].OriginalActionInfo = SKILL_INSTALL_TRAP;

	(*g_pEffectStatusTable)[EFFECTSTATUS_TRAPPED].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_TRAPPED].ActionInfo = TRAPPED;
	(*g_pEffectStatusTable)[EFFECTSTATUS_TRAPPED].OriginalActionInfo = SKILL_INSTALL_TRAP;

	(*g_pEffectStatusTable)[EFFECTSTATUS_MERCY_GROUND].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_MERCY_GROUND].ActionInfo = RESULT_SKILL_MERCY_GROUND;

	(*g_pEffectStatusTable)[EFFECTSTATUS_HOLY_ARMOR].EffectSpriteType = EFFECTSPRITETYPE_HOLY_ARMOR_C;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HOLY_ARMOR].OriginalActionInfo = SKILL_HOLY_ARMOR;

	(*g_pEffectStatusTable)[EFFECTSTATUS_TRANSFORM_TO_WERWOLF].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_TRANSFORM_TO_WERWOLF].OriginalActionInfo = SKILL_TRANSFORM_TO_WERWOLF;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_HOWL].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HOWL].OriginalActionInfo = MAGIC_HOWL;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_STONE_SKIN].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_STONE_SKIN].OriginalActionInfo = SKILL_STONE_SKIN;
	(*g_pEffectStatusTable)[EFFECTSTATUS_STONE_SKIN].ActionInfo = RESULT_SKILL_STONE_SKIN;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_GRAY_DARKNESS].EffectSpriteType = EFFECTSPRITETYPE_GRAY_DARKNESS_2_1;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_GRAY_DARKNESS].OriginalActionInfo = SKILL_GRAY_DARKNESS;
	(*g_pEffectStatusTable)[EFFECTSTATUS_GRAY_DARKNESS].ActionInfo = RESULT_SKILL_GRAY_DARKNESS;

	(*g_pEffectStatusTable)[EFFECTSTATUS_STONE_SKIN_DAMAGED].EffectSpriteType = EFFECTSPRITETYPE_STONE_SKIN_DAMAGED_1;	
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SWEEPER].EffectSpriteType = EFFECTSPRITETYPE_HAS_SWEEPER_1;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SWEEPER].OriginalActionInfo = SKILL_SWEEPER_BONUS_1;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SWEEPER_2].EffectSpriteType = EFFECTSPRITETYPE_HAS_SWEEPER_2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SWEEPER_2].OriginalActionInfo = SKILL_SWEEPER_BONUS_2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SWEEPER_3].EffectSpriteType = EFFECTSPRITETYPE_HAS_SWEEPER_3;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SWEEPER_3].OriginalActionInfo = SKILL_SWEEPER_BONUS_3;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SWEEPER_4].EffectSpriteType = EFFECTSPRITETYPE_HAS_SWEEPER_4;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SWEEPER_4].OriginalActionInfo = SKILL_SWEEPER_BONUS_4;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SWEEPER_5].EffectSpriteType = EFFECTSPRITETYPE_HAS_SWEEPER_5;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SWEEPER_5].OriginalActionInfo = SKILL_SWEEPER_BONUS_5;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SWEEPER_6].EffectSpriteType = EFFECTSPRITETYPE_HAS_SWEEPER_6;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SWEEPER_6].OriginalActionInfo = SKILL_SWEEPER_BONUS_6;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SWEEPER_7].EffectSpriteType = EFFECTSPRITETYPE_HAS_SWEEPER_7;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SWEEPER_7].OriginalActionInfo = SKILL_SWEEPER_BONUS_7;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SWEEPER_8].EffectSpriteType = EFFECTSPRITETYPE_HAS_SWEEPER_8;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SWEEPER_8].OriginalActionInfo = SKILL_SWEEPER_BONUS_8;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SWEEPER_9].EffectSpriteType = EFFECTSPRITETYPE_HAS_SWEEPER_9;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SWEEPER_9].OriginalActionInfo = SKILL_SWEEPER_BONUS_9;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SWEEPER_10].EffectSpriteType = EFFECTSPRITETYPE_HAS_SWEEPER_10;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SWEEPER_10].OriginalActionInfo = SKILL_SWEEPER_BONUS_10;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SWEEPER_11].EffectSpriteType = EFFECTSPRITETYPE_HAS_SWEEPER_11;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SWEEPER_11].OriginalActionInfo = SKILL_SWEEPER_BONUS_11;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SWEEPER_12].EffectSpriteType = EFFECTSPRITETYPE_HAS_SWEEPER_12;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_SWEEPER_12].OriginalActionInfo = SKILL_SWEEPER_BONUS_12;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER].EffectSpriteType = EFFECTSPRITETYPE_SWEEPER_NUMBER_1;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER].OriginalActionInfo = SKILL_SWEEPER_BONUS_1;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER].SoundID			=	SOUND_SWEEPER_START;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_2].EffectSpriteType = EFFECTSPRITETYPE_SWEEPER_NUMBER_2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_2].OriginalActionInfo = SKILL_SWEEPER_BONUS_2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_2].SoundID			=	SOUND_SWEEPER_START;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_3].EffectSpriteType = EFFECTSPRITETYPE_SWEEPER_NUMBER_3;	
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_3].OriginalActionInfo = SKILL_SWEEPER_BONUS_3;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_3].SoundID			=	SOUND_SWEEPER_START;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_4].EffectSpriteType = EFFECTSPRITETYPE_SWEEPER_NUMBER_4;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_4].OriginalActionInfo = SKILL_SWEEPER_BONUS_4;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_4].SoundID			=	SOUND_SWEEPER_START;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_5].EffectSpriteType = EFFECTSPRITETYPE_SWEEPER_NUMBER_5;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_5].OriginalActionInfo = SKILL_SWEEPER_BONUS_5;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_5].SoundID			=	SOUND_SWEEPER_START;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_6].EffectSpriteType = EFFECTSPRITETYPE_SWEEPER_NUMBER_6;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_6].OriginalActionInfo = SKILL_SWEEPER_BONUS_6;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_6].SoundID			=	SOUND_SWEEPER_START;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_7].EffectSpriteType = EFFECTSPRITETYPE_SWEEPER_NUMBER_7;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_7].OriginalActionInfo = SKILL_SWEEPER_BONUS_7;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_7].SoundID			=	SOUND_SWEEPER_START;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_8].EffectSpriteType = EFFECTSPRITETYPE_SWEEPER_NUMBER_8;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_8].OriginalActionInfo = SKILL_SWEEPER_BONUS_8;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_8].SoundID			=	SOUND_SWEEPER_START;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_9].EffectSpriteType = EFFECTSPRITETYPE_SWEEPER_NUMBER_9;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_9].OriginalActionInfo = SKILL_SWEEPER_BONUS_9;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_9].SoundID			=	SOUND_SWEEPER_START;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_10].EffectSpriteType = EFFECTSPRITETYPE_SWEEPER_NUMBER_10;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_10].OriginalActionInfo = SKILL_SWEEPER_BONUS_10;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_10].SoundID			=	SOUND_SWEEPER_START;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_11].EffectSpriteType = EFFECTSPRITETYPE_SWEEPER_NUMBER_11;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_11].OriginalActionInfo = SKILL_SWEEPER_BONUS_11;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_11].SoundID			=	SOUND_SWEEPER_START;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_12].EffectSpriteType = EFFECTSPRITETYPE_SWEEPER_NUMBER_12;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_12].OriginalActionInfo = SKILL_SWEEPER_BONUS_12;
	(*g_pEffectStatusTable)[EFFECTSTATUS_KEEP_SWEEPER_12].SoundID			=	SOUND_SWEEPER_START;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SLAYER_REGEN_ZONE].EffectSpriteType = EFFECTSPRITETYPE_BEAD_BLUE_4;
	(*g_pEffectStatusTable)[EFFECTSTATUS_VAMPIRE_REGEN_ZONE].EffectSpriteType = EFFECTSPRITETYPE_BEAD_RED_4;
	(*g_pEffectStatusTable)[EFFECTSTATUS_OUSTERS_REGEN_ZONE].EffectSpriteType = EFFECTSPRITETYPE_BEAD_GREEN_4;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DEFAULT_REGEN_ZONE].EffectSpriteType = EFFECTSPRITETYPE_NULL;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SLAYER_TRYING_1].EffectSpriteType = EFFECTSPRITETYPE_BEAD_BLUE_1;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SLAYER_TRYING_1].SoundID			= SOUND_REGEN_TOWER_FLASH;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SLAYER_TRYING_2].EffectSpriteType = EFFECTSPRITETYPE_BEAD_BLUE_2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SLAYER_TRYING_2].SoundID			= SOUND_REGEN_TOWER_FLASH;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SLAYER_TRYING_3].EffectSpriteType = EFFECTSPRITETYPE_BEAD_BLUE_3;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SLAYER_TRYING_3].SoundID			= SOUND_REGEN_TOWER_FLASH;

	(*g_pEffectStatusTable)[EFFECTSTATUS_VAMPIRE_TRYING_1].EffectSpriteType = EFFECTSPRITETYPE_BEAD_RED_1;
	(*g_pEffectStatusTable)[EFFECTSTATUS_VAMPIRE_TRYING_1].SoundID			= SOUND_REGEN_TOWER_FLASH;
	(*g_pEffectStatusTable)[EFFECTSTATUS_VAMPIRE_TRYING_2].EffectSpriteType = EFFECTSPRITETYPE_BEAD_RED_2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_VAMPIRE_TRYING_2].SoundID			= SOUND_REGEN_TOWER_FLASH;
	(*g_pEffectStatusTable)[EFFECTSTATUS_VAMPIRE_TRYING_3].EffectSpriteType = EFFECTSPRITETYPE_BEAD_RED_3;
	(*g_pEffectStatusTable)[EFFECTSTATUS_VAMPIRE_TRYING_3].SoundID			= SOUND_REGEN_TOWER_FLASH;

	(*g_pEffectStatusTable)[EFFECTSTATUS_OUSTERS_TRYING_1].EffectSpriteType = EFFECTSPRITETYPE_BEAD_GREEN_1;	
	(*g_pEffectStatusTable)[EFFECTSTATUS_OUSTERS_TRYING_1].SoundID			= SOUND_REGEN_TOWER_FLASH;
	(*g_pEffectStatusTable)[EFFECTSTATUS_OUSTERS_TRYING_2].EffectSpriteType = EFFECTSPRITETYPE_BEAD_GREEN_2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_OUSTERS_TRYING_2].SoundID			= SOUND_REGEN_TOWER_FLASH;
	(*g_pEffectStatusTable)[EFFECTSTATUS_OUSTERS_TRYING_3].EffectSpriteType = EFFECTSPRITETYPE_BEAD_GREEN_3;
	(*g_pEffectStatusTable)[EFFECTSTATUS_OUSTERS_TRYING_3].SoundID			= SOUND_REGEN_TOWER_FLASH;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_TRYING_POSITION].EffectSpriteType = EFFECTSPRITETYPE_REGEN_TOWER_GROUND;
	(*g_pEffectStatusTable)[EFFECTSTATUS_TRYING_POSITION].ActionInfo		= REGEN_TOWER_TRING_POSITION;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_TRYING].EffectSpriteType = EFFECTSPRITETYPE_REGEN_TOWER_THROW_LIGHT_ING;
	(*g_pEffectStatusTable)[EFFECTSTATUS_TRYING].ActionInfo			= REGEN_TOWER_THROW_LIGHT;
	(*g_pEffectStatusTable)[EFFECTSTATUS_TRYING].SoundID			= SOUND_REGEN_TOWER_START;
	(*g_pEffectStatusTable)[EFFECTSTATUS_TRYING].bUseEffectSprite = true;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_CAPTURE_REGEN_ZONE].EffectSpriteType = EFFECTSPRITETYPE_REGEN_TOWER_DROP_LIGHT;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CAPTURE_REGEN_ZONE].SoundID			= SOUND_REGEN_TOWER_OWNER_CHANGED;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_SYLPH_GREEN].EffectSpriteType = EFFECTSPRITETYPE_SUMMON_SYLPH_GREEN_STOP;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_SYLPH_GREEN].OriginalActionInfo = SKILL_SUMMON_SYLPH;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_SYLPH_ORANGE].EffectSpriteType = EFFECTSPRITETYPE_SUMMON_SYLPH_ORANGE_STOP;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_SYLPH_ORANGE].OriginalActionInfo = SKILL_SUMMON_SYLPH;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_SYLPH_RED].EffectSpriteType = EFFECTSPRITETYPE_SUMMON_SYLPH_RED_STOP;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_SYLPH_RED].OriginalActionInfo = SKILL_SUMMON_SYLPH;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_SYLPH_YELLOW].EffectSpriteType = EFFECTSPRITETYPE_SUMMON_SYLPH_YELLOW_STOP;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_SYLPH_YELLOW].OriginalActionInfo = SKILL_SUMMON_SYLPH;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_SYLPH_WHITE].EffectSpriteType = EFFECTSPRITETYPE_SUMMON_SYLPH_WHITE_STOP;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_SYLPH_WHITE].OriginalActionInfo = SKILL_SUMMON_SYLPH;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_SYLPH_BROWN].EffectSpriteType = EFFECTSPRITETYPE_SUMMON_SYLPH_BROWN_STOP;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_SYLPH_BROWN].OriginalActionInfo = SKILL_SUMMON_SYLPH;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_SYLPH_LILAC].EffectSpriteType = EFFECTSPRITETYPE_SUMMON_SYLPH_PURPLE_STOP;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_SYLPH_LILAC].OriginalActionInfo = SKILL_SUMMON_SYLPH;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_SYLPH_BLACK].EffectSpriteType = EFFECTSPRITETYPE_SUMMON_SYLPH_BLACK_STOP;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_SYLPH_BLACK].OriginalActionInfo = SKILL_SUMMON_SYLPH;

	
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_ELEMENTAL_DAMAGED].EffectSpriteType = EFFECTSPRITETYPE_FIRE_BURST_MEDIUM;
	(*g_pEffectStatusTable)[EFFECTSTATUS_WATER_ELEMENTAL_HEALED].EffectSpriteType = EFFECTSPRITETYPE_NYMPH_RECOVERY;

	(*g_pEffectStatusTable)[EFFECTSTATUS_DISTANCE_BLITZ].EffectSpriteType = EFFECTSPRITETYPE_DISTANCE_BLITZ_DAMAGED;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_ELEMENTAL].EffectSpriteType = EFFECTSPRITETYPE_SUMMON_FIRE_ELEMENTAL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_ELEMENTAL].OriginalActionInfo = SKILL_SUMMON_OF_FIRE_ELEMENTAL;

	(*g_pEffectStatusTable)[EFFECTSTATUS_WATER_ELEMENTAL].EffectSpriteType = EFFECTSPRITETYPE_SUMMON_WATER_ELEMENTAL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_WATER_ELEMENTAL].OriginalActionInfo = SKILL_SUMMON_OF_WATER_ELEMENTAL;

	(*g_pEffectStatusTable)[EFFECTSTATUS_GROUND_ELEMENTAL_CENTER].ActionInfo = SKILL_CLIENT_SUMMON_GROUND_ELEMENTAL;

	// 2004, 03, 25 sobeit add start
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLACK_LARGE_SMOKE].EffectSpriteType = EFFECTSPRITETYPE_MAP_BLACK_LARGE_SMOKE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLACK_HALL].EffectSpriteType = EFFECTSPRITETYPE_MAP_BLACK_HALL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLACK_SMALL_SMOKE_1].EffectSpriteType = EFFECTSPRITETYPE_MAP_BLACK_SMALL_SMOKE_1;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLACK_SMALL_SMOKE_2].EffectSpriteType = EFFECTSPRITETYPE_MAP_BLACK_SMALL_SMOKE_2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLACK_SMALL_SMOKE_3].EffectSpriteType = EFFECTSPRITETYPE_MAP_BLACK_SMALL_SMOKE_3;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ELECTRIC_POST].EffectSpriteType = EFFECTSPRITETYPE_MAP_ELECTRIC_POST;

	(*g_pEffectStatusTable)[EFFECTSTATUS_GHOST_1].EffectSpriteType = EFFECTSPRITETYPE_MAP_GHOST_1;
	(*g_pEffectStatusTable)[EFFECTSTATUS_GHOST_2].EffectSpriteType = EFFECTSPRITETYPE_MAP_GHOST_2;
	// 2004, 03, 25 sobeit add end
	
	// 2004, 04, 2 sobeit add start
	(*g_pEffectStatusTable)[EFFECTSTATUS_LUCKY].EffectSpriteType = EFFECTSPRITETYPE_LUCKY_AURA;
	(*g_pEffectStatusTable)[EFFECTSTATUS_MISFORTUNE].EffectSpriteType = EFFECTSPRITETYPE_MISFORTUNE_AURA;
	// 2004, 04, 2 sobeit add end

	// 2004, 05, 6, sobeit add start - 엠버 2종 추가
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_CASTLE_SYMBOL_5].EffectSpriteType = EFFECTSPRITETYPE_AMBER_OF_LIFE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HAS_CASTLE_SYMBOL_6].EffectSpriteType = EFFECTSPRITETYPE_AMBER_OF_LIGHT;
	// 2004, 05, 6, sobeit add end - 엠버 2종 추가

	// 2004, 5, 19 sobeit add start - 일루전스 웨이 트랩
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICICLE_DROP].EffectSpriteType  = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICICLE_DROP].ActionInfo		= SKILL_CLIENT_TRAP_ICICLE_DROP;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICICLE_DROP_SIGN].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICICLE_DROP_SIGN].ActionInfo		= SKILL_CLIENT_TRAP_ICICLE_DROP_SIGN;

	(*g_pEffectStatusTable)[EFFECTSTATUS_ICICLE_AUGER].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICICLE_AUGER].ActionInfo		= SKILL_CLIENT_TRAP_ICICLE_AUGER;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICICLE_AUGER_SIGN].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICICLE_AUGER_SIGN].ActionInfo		= SKILL_CLIENT_TRAP_ICICLE_AUGER_SIGN;

	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_STICK_SW].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_STICK_SW].ActionInfo		= SKILL_CLIENT_TRAP_ICE_STICK_SW;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_STICK_SW_SIGN].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_STICK_SW_SIGN].ActionInfo		= SKILL_CLIENT_TRAP_ICE_STICK_SW_SIGN;

	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_STICK_SE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_STICK_SE].ActionInfo		= SKILL_CLIENT_TRAP_ICE_STICK_SE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_STICK_SE_SIGN].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_STICK_SE_SIGN].ActionInfo		= SKILL_CLIENT_TRAP_ICE_STICK_SE_SIGN;

	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_STICK_NE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_STICK_NE].ActionInfo		= SKILL_CLIENT_TRAP_ICE_STICK_NE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_STICK_NE_SIGN].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_STICK_NE_SIGN].ActionInfo		= SKILL_CLIENT_TRAP_ICE_STICK_NE_SIGN;

	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_STICK_NW].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_STICK_NW].ActionInfo		= SKILL_CLIENT_TRAP_ICE_STICK_NW;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_STICK_NW_SIGN].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_STICK_NW_SIGN].ActionInfo		= SKILL_CLIENT_TRAP_ICE_STICK_NW_SIGN;

	(*g_pEffectStatusTable)[EFFECTSTATUS_ICICLE_LARGE_AUGER].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICICLE_LARGE_AUGER].ActionInfo		= SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICICLE_LARGE_AUGER_SIGN].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICICLE_LARGE_AUGER_SIGN].ActionInfo		= SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER_SIGN;
	// 2004, 5, 19 sobeit add end - 일루전스 웨이 트랩

	// 2004, 5, 20, sobeit add start
	(*g_pEffectStatusTable)[EFFECTSTATUS_WHITE_BLESS].EffectSpriteType = EFFECTSPRITETYPE_WHITE_BLESS;
	// 2004, 5, 20, sobeit add end

//	// 2004, 6, 5 sobeit add start
//	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_STICK_NE].EffectSpriteType = EFFECTSPRITETYPE_ICE_STICK_NE;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_STICK_NE].ActionInfo		= SKILL_CLIENT_TRAP_ICE_STICK_NE;
//	// 2004, 6, 5 sobeit add end

	// 2004, 6, 10 sobeit add & modify start - master effect
	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_GDR].EffectSpriteType			= EFFECTSPRITETYPE_GDR_SUMMON_BACK;
	//(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_GDR].ActionInfo					= SKILL_CLIENT_GDR_SUMMON;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_GDR_SATELLITE].EffectSpriteType		= EFFECTSPRITETYPE_GDR_SATELLITE_BACK;
	
 
	(*g_pEffectStatusTable)[EFFECTSTATUS_GRAND_MASTER_SLAYER].EffectSpriteType			= EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_SLAYER_100_NEW;
	(*g_pEffectStatusTable)[EFFECTSTATUS_GRAND_MASTER_VAMPIRE].EffectSpriteType			= EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_VAMPIRE_100_NEW;
	(*g_pEffectStatusTable)[EFFECTSTATUS_GRAND_MASTER_OUSTERS].EffectSpriteType			= EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_OUSTERS_100_NEW;

	(*g_pEffectStatusTable)[EFFECTSTATUS_GRAND_MASTER_SLAYER_130].EffectSpriteType			= EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_SLAYER_130_NEW;
	(*g_pEffectStatusTable)[EFFECTSTATUS_GRAND_MASTER_SLAYER_150].EffectSpriteType			= EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_SLAYER_150_NEW;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_GRAND_MASTER_VAMPIRE_130].EffectSpriteType			= EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_VAMPIRE_130_NEW;
	(*g_pEffectStatusTable)[EFFECTSTATUS_GRAND_MASTER_VAMPIRE_150].EffectSpriteType			= EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_VAMPIRE_150_FRONT_NEW;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_GRAND_MASTER_OUSTERS_130].EffectSpriteType			= EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_OUSTERS_130_NEW;
	(*g_pEffectStatusTable)[EFFECTSTATUS_GRAND_MASTER_OUSTERS_150].EffectSpriteType			= EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_OUSTERS_150_NEW;
	
		
	// 2004, 6, 10 sobeit add & modify end - master effect SKILL_CLIENT_VAMPIRE_MASTERE_150
	
//	// 2004, 6, 15 sobeit add start - gdr skill - glacier
//	(*g_pEffectStatusTable)[EFFECTSTATUS_GDR_GLACIER_SLAYER].EffectSpriteType = EFFECTSPRITETYPE_GDR_GLACIER_SLAYER_START;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_GDR_GLACIER_SLAYER].ActionInfo		= SKILL_CLIENT_GDR_GLACIER_SLAYER;
//
//	(*g_pEffectStatusTable)[EFFECTSTATUS_GDR_GLACIER_VAMPIRE].EffectSpriteType = EFFECTSPRITETYPE_GDR_GLACIER_VAMPIRE_START;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_GDR_GLACIER_VAMPIRE].ActionInfo		= SKILL_CLIENT_GDR_GLACIER_VAMPIRE;
//
//	(*g_pEffectStatusTable)[EFFECTSTATUS_GDR_GLACIER_OUSTERS].EffectSpriteType = EFFECTSPRITETYPE_GDR_GLACIER_OUSTERS_START;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_GDR_GLACIER_OUSTERS].ActionInfo		= SKILL_CLIENT_GDR_GLACIER_OUSTERS;
//	// 2004, 6, 15 sobeit add end - gdr skill - glacier

	// 2004, 6, 18 sobeit add start
	(*g_pEffectStatusTable)[EFFECTSTATUS_CAN_ENTER_GDR_LAIR].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CAN_ENTER_GDR_LAIR].OriginalActionInfo = SKILL_CLIENT_CAN_ENTER_GDR_LAIR;

	(*g_pEffectStatusTable)[EFFECTSTATUS_BLINDNESS].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLINDNESS].OriginalActionInfo = SKILL_CLIENT_BLINDNESS;
	
	// 2004, 6, 18 sobeit add end

	// 2004, 6, 21 sobeit add start
	(*g_pEffectStatusTable)[EFFECTSTATUS_CAN_MODIFY_NICKNAME_0].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CAN_MODIFY_PET_NICKNAME].EffectSpriteType = EFFECTSPRITETYPE_NULL;

	(*g_pEffectStatusTable)[EFFECTSTATUS_GLACIER].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_HAIL].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	// 2004, 6, 21 sobeit add end

	// 2004, 7, 21 sobeit add start
	(*g_pEffectStatusTable)[EFFECTSTATUS_GOLD_MEDAL].EffectSpriteType = EFFECTSPRITETYPE_NETMARBLE_GOLD_MEDAL;	// 넷마블 금메달 이펙트
	// 2004, 7, 21 sobeit add end
	
	// 2004, 8, 31 sobeit add start
	(*g_pEffectStatusTable)[EFFECTSTATUS_LAND_MINE_EXPLOSION].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_LAND_MINE_EXPLOSION].ActionInfo		= SKILL_LAND_MINE_EXPLOSION;

	(*g_pEffectStatusTable)[EFFECTSTATUS_CLAYMORE_EXPLOTION].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CLAYMORE_EXPLOTION].ActionInfo		= SKILL_CLAYMORE_EXPLOSION;

	(*g_pEffectStatusTable)[EFFECTSTATUS_PLEASURE_EXPLOSION].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_PLEASURE_EXPLOSION].bUseEffectSprite		= false;
	(*g_pEffectStatusTable)[EFFECTSTATUS_PLEASURE_EXPLOSION].EffectColor		= 333;
	(*g_pEffectStatusTable)[EFFECTSTATUS_PLEASURE_EXPLOSION].ActionInfo		= SKILL_PLEASURE_EXPLOSION;
	(*g_pEffectStatusTable)[EFFECTSTATUS_PLEASURE_EXPLOSION].OriginalActionInfo		= SKILL_PLEASURE_EXPLOSION;

	(*g_pEffectStatusTable)[EFFECTSTATUS_TURRET_LASER].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_TURRET_LASER].ActionInfo	= SKILL_CLIENT_TURRET_LASER;

	(*g_pEffectStatusTable)[EFFECTSTATUS_TURRET_LASER_ATTACK].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_TURRET_LASER_ATTACK].ActionInfo	= SKILL_CLIENT_TURRET_LASER_ATTACK;

	(*g_pEffectStatusTable)[EFFECTSTATUS_AUTO_TURRET].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	// 2004, 8, 31 sobeit add end

	// 2004, 9, 4, sobeit add start - 아우스터즈 공성전 스킬
	(*g_pEffectStatusTable)[EFFECTSTATUS_REPUTO_FACTUM].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_REPUTO_FACTUM_LAST].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_REPUTO_FACTUM_LAST].OriginalActionInfo	= SKILL_REPUTO_FACTUM;
	// 2004, 9, 4, sobeit add end - 아우스터즈 공성전 스킬
	
	// 2004, 9, 8, sobeit add start - 130 스킬 관련
	(*g_pEffectStatusTable)[EFFECTSTATUS_SWORD_OF_THOR].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SWORD_OF_THOR].ActionInfo	= SKILL_CLIENT_SWORD_OF_THOR;

	(*g_pEffectStatusTable)[EFFECTSTATUS_BURNING_SOL_CHARGE_1].EffectSpriteType	= EFFECTSPRITETYPE_BURNING_SOL_CHARGE_1;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BURNING_SOL_CHARGE_2].EffectSpriteType	= EFFECTSPRITETYPE_BURNING_SOL_CHARGE_2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BURNING_SOL_CHARGE_3].EffectSpriteType	= EFFECTSPRITETYPE_BURNING_SOL_CHARGE_3;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BURNING_SOL_CHARGE_4].EffectSpriteType	= EFFECTSPRITETYPE_BURNING_SOL_CHARGE_4;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_INSTALL_TURRET].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_DRAGON_EYES].EffectSpriteType	= EFFECTSPRITETYPE_DRAGON_EYE;
	//(*g_pEffectStatusTable)[EFFECTSTATUS_DRAGON_EYES].OriginalActionInfo = SKILL_CLIENT_DRAGON_EYES;

 	// 2004, 9, 8, sobeit add end - 130 스킬 관련

#if __CONTENTS(__HERO_SYSTEM)
	(*g_pEffectStatusTable)[EFFECTSTATUS_SLAYER_HERO].EffectSpriteType	= EFFECTSPRITETYPE_SLAYER_HERO;
	(*g_pEffectStatusTable)[EFFECTSTATUS_VAMPIRE_HERO].EffectSpriteType	= EFFECTSPRITETYPE_VAMPIRE_HERO;
	(*g_pEffectStatusTable)[EFFECTSTATUS_OUSTERS_HERO].EffectSpriteType	= EFFECTSPRITETYPE_OUSTERS_HERO;
	(*g_pEffectStatusTable)[EFFECTSTATUS_LEVELWAR_SLAYER_HERO].EffectSpriteType	= EFFECTSPRITETYPE_SLAYER_HERO;
	(*g_pEffectStatusTable)[EFFECTSTATUS_LEVELWAR_VAMPIRE_HERO].EffectSpriteType	= EFFECTSPRITETYPE_VAMPIRE_HERO;
	(*g_pEffectStatusTable)[EFFECTSTATUS_LEVELWAR_OUSTERS_HERO].EffectSpriteType	= EFFECTSPRITETYPE_OUSTERS_HERO;
#endif //__HERO_SYSTEM

#if __CONTENTS(__MENEGROTH)
	(*g_pEffectStatusTable)[EFFECTSTATUS_MENEGROTH_PERMISSION].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_MENEGROTH_PERMISSION].OriginalActionInfo = SKILL_CLIENT_MENEGROTH_TIME;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_MENEGROTH_TRAP1].EffectSpriteType	= EFFECTSPRITETYPE_NULL;

	(*g_pEffectStatusTable)[EFFECTSTATUS_MENEGROTH_TRAP2].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_MENEGROTH_TRAP2].ActionInfo		= SKILL_CLIENT_MENEGROTH_TRAP;

	(*g_pEffectStatusTable)[EFFECTSTATUS_MENEGROTH_CABRACAM_ALTAR].EffectSpriteType	= EFFECTSPRITETYPE_CABRACAM_ALTAR_LIGHT;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_MENEGROTH_CABRACAM_SUMMON].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_MENEGROTH_CABRACAM_SUMMON].ActionInfo = SKILL_CLIENT_CABRACAM_SUMMON;
	
#endif //__MENEGROTH
	
#if __CONTENTS(__DSG_EFFECT)
	(*g_pEffectStatusTable)[EFFECTSTATUS_DSG].EffectSpriteType = EFFECTSPRITETYPE_DSG_FRONT;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DSG].OriginalActionInfo = SKILL_CLIENT_DSG;
#endif //__DSG_EFFECT

#if __CONTENTS(__080327_ORDINIS_VAPOR)
	(*g_pEffectStatusTable)[EFFECTSTATUS_ORDINIS_VAPOR_RED].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ORDINIS_VAPOR_RED].OriginalActionInfo = SKILL_CLIENT_ORDINIS_VAPOR_RED;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ORDINIS_VAPOR_BLUE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ORDINIS_VAPOR_BLUE].OriginalActionInfo = SKILL_CLIENT_ORDINIS_VAPOR_BLUE;
#endif //__DSG_EFFECT

	// 2004, 11, 8, sobeit add start
	(*g_pEffectStatusTable)[EFFECTSTATUS_ROCKET_LUNCHER].EffectSpriteType	= EFFECTSPRITETYPE_NEW_PLASMA_ROCKET_LAUNCHER_MISSILE_FIRE;

#if __CONTENTS(__SECOND_RARE_SKILL)
	(*g_pEffectStatusTable)[EFFECTSTATUS_XRL].EffectSpriteType	= EFFECTSPRITETYPE_XRL_TAILFIRE;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_THORNS].EffectSpriteType	= EFFECTSPRITETYPE_THORNS_FRONT;
	(*g_pEffectStatusTable)[EFFECTSTATUS_THORNS].OriginalActionInfo	= SKILL_THORNS;

	(*g_pEffectStatusTable)[EFFECTSTATUS_BRIONAC].EffectSpriteType = EFFECTSPRITETYPE_HELLFIRE_ING;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BRIONAC].ActionInfo = RESULT_SKILL_BRIONAC;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BRIONAC].OriginalActionInfo = SKILL_BRIONAC;
#endif //__SECOND_RARE_SKILL
	
#if __CONTENTS(__QUEST_RENEWAL)
	(*g_pEffectStatusTable)[EFFECTSTATUS_CLIENT_QUEST_FINISH_SLAYER].EffectSpriteType			= EFFECTSPRITETYPE_QUEST_FINISH_SLAYER2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CLIENT_QUEST_FINISH_VAMPIRE].EffectSpriteType			= EFFECTSPRITETYPE_QUEST_FINISH_VAMPIRE2;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CLIENT_QUEST_FINISH_OUSTERS].EffectSpriteType			= EFFECTSPRITETYPE_QUEST_FINISH_OUSTERS2;

#endif	

	(*g_pEffectStatusTable)[EFFECTSTATUS_INTIMATE_GRAIL].EffectSpriteType	= EFFECTSPRITETYPE_INTIMATE_GRAIL_LOOP;
	(*g_pEffectStatusTable)[EFFECTSTATUS_INTIMATE_GRAIL].OriginalActionInfo = SKILL_INTIMATE_GRAIL;
	// 2004, 11, 8, sobeit add end

	(*g_pEffectStatusTable)[EFFECTSTATUS_SET_AFIRE_ATTACK].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SET_AFIRE_ATTACK].bUseEffectSprite = false;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SET_AFIRE_ATTACK].EffectColor	= 44;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_HORIZON].EffectSpriteType	= EFFECTSPRITETYPE_ICE_HORIZON_HEAL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ICE_HORIZON].ActionInfo	= RESULT_SKILL_ICE_HORIZON;

	(*g_pEffectStatusTable)[EFFECTSTATUS_FURY_OF_GNOME].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FURY_OF_GNOME_MARK].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FURY_OF_GNOME_MARK].ActionInfo		= SKILL_CLIENT_FURY_OF_GNOME;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_MIGA_FIRE].EffectSpriteType	= EFFECTSPRITETYPE_SUMMON_MIGA_ATTACK;

	(*g_pEffectStatusTable)[EFFECTSTATUS_HALO].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HALO].ActionInfo		= SKILL_CLIENT_HALO_STOP;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIERCE_FLAME].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	//(*g_pEffectStatusTable)[EFFECTSTATUS_FIERCE_FLAME].ActionInfo		= SKILL_CLIENT_FIERCE_FLAME;

	(*g_pEffectStatusTable)[EFFECTSTATUS_ABERRATION].EffectSpriteType = EFFECTSPRITETYPE_ABERRATION_BACK;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ABERRATION].OriginalActionInfo = SKILL_ABERRATION;

	(*g_pEffectStatusTable)[EFFECTSTATUS_DRAGON_TORNADO].EffectSpriteType = EFFECTSPRITETYPE_DRAGON_TORNADO;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DRAGON_TORNADO_CHILD].EffectSpriteType = EFFECTSPRITETYPE_NEW_TYPHOON;

	//(*g_pEffectStatusTable)[EFFECTSTATUS_PASSING_HEAL].EffectSpriteType = EFFECTSPRITETYPE_PASSING_HEAL;

	(*g_pEffectStatusTable)[EFFECTSTATUS_HARPOON_BOMB].EffectSpriteType		= EFFECTSPRITETYPE_HARPOON_BOMB_REPEAT;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HARPOON_BOMB].OriginalActionInfo	= SKILL_CLIENT_HARPOON_BOMB;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HARPOON_BOMB].ActionInfo			= SKILL_CLIENT_HARPOON_BOMB;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_BIKE_CRASH].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DONATION_200501].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BONUS_EXP].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BONUS_EXP].OriginalActionInfo = SKILL_CLIENT_EXP_BONUS_EVENT;
#if __CONTENTS(__JAPAN_REVERSE_DEVELOP)
	(*g_pEffectStatusTable)[EFFECTSTATUS_BONUS_EXP_ACCOUNT].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BONUS_EXP_ACCOUNT].OriginalActionInfo = SKILL_CLIENT_EXP_BONUS_EVENT;
#endif //__JAPAN_REVERSE_DEVELOP

	(*g_pEffectStatusTable)[EFFECTSTATUS_ADVANCEMENT_MASTSER_EFFECT_SLAYER].EffectSpriteType = EFFECTSPRITETYPE_ADVANCEMENT_MASTER_SLAYER;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ADVANCEMENT_MASTSER_EFFECT_VAMPIRE].EffectSpriteType = EFFECTSPRITETYPE_ADVANCEMENT_MASTER_VAMPIRE_BACK;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ADVANCEMENT_MASTSER_EFFECT_OUSTERS].EffectSpriteType = EFFECTSPRITETYPE_ADVANCEMENT_MASTER_OUSTER;

	(*g_pEffectStatusTable)[EFFECTSTATUS_TILE_PORTAL].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_TILE_PORTAL].ActionInfo		= SKILL_CLIENT_QUEST_MAGIC_ZONE_POTAL;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_BEHEMOTH_FORCE_SCROLL].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BEHEMOTH_FORCE_SCROLL].OriginalActionInfo = SKILL_CLIENT_BEHEMOTH_FORCE_SCROLL;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_SAFE_FORCE_SCROLL].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SAFE_FORCE_SCROLL].OriginalActionInfo = SKILL_CLIENT_SAFE_FORCE_SCROLL;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_CARNELIAN_FORCE_SCROLL].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CARNELIAN_FORCE_SCROLL].OriginalActionInfo = SKILL_CLIENT_CARNELIAN_FORCE_SCROLL;

	// Sjheon 2005.05.30 FEEBLE_VIRUS Action 상태  Add
	(*g_pEffectStatusTable)[EFFECTSTATUS_FEEBLE_VIRUS].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FEEBLE_VIRUS].ActionInfo		= RESULT_SKILL_FEEBLE_VIRUS;
	// Sjheon 2005.05.30 FEEBLE_VIRUS Action 상태  End 


	// Sjheon 2005.08.05 폭주 Add 

	(*g_pEffectStatusTable)[EFFECTSTATUS_COMBO_DAMAGE].EffectSpriteType = EFFECTSPRITETYPE_NULL;

	(*g_pEffectStatusTable)[EFFECTSTATUS_HOLY_SWORD].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HOLY_SWORD].OriginalActionInfo		=  SKILL_HOLY_SWORD ; 

	(*g_pEffectStatusTable)[EFFECTSTATUS_HOLY_BLADE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HOLY_BLADE].OriginalActionInfo		=  SKILL_HOLY_BLADE ; 

	(*g_pEffectStatusTable)[EFFECTSTATUS_BURST_GUN].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BURST_GUN].OriginalActionInfo		=  SKILL_BURST_GUN ; 

	(*g_pEffectStatusTable)[EFFECTSTATUS_HOLY_MACE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HOLY_MACE].OriginalActionInfo		=  SKILL_HOLY_MACE ; 

	(*g_pEffectStatusTable)[EFFECTSTATUS_HOLY_CROSS].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HOLY_CROSS].OriginalActionInfo		=  SKILL_HOLY_CROSS ; 

	(*g_pEffectStatusTable)[EFFECTSTATUS_DARK_FORCE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DARK_FORCE].OriginalActionInfo		=  SKILL_DARK_FORCE ;

	(*g_pEffectStatusTable)[EFFECTSTATUS_NATURAL_FORCE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_NATURAL_FORCE].OriginalActionInfo		=  SKILL_NATURAL_FORCE ; 

	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_FORCE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_FORCE].OriginalActionInfo		=  SKILL_FIRE_FORCE ; 

	(*g_pEffectStatusTable)[EFFECTSTATUS_WATER_FORCE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_WATER_FORCE].OriginalActionInfo		=  SKILL_WATER_FORCE ; 


	(*g_pEffectStatusTable)[EFFECTSTATUS_EARTH_FORCE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_EARTH_FORCE].OriginalActionInfo		=  SKILL_EARTH_FORCE ;
	
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_LOSE_SIGHT].EffectSpriteType = EFFECTSPRITETYPE_BLOOD_BURST_DEFENSE_ATTACK_BLUE;

	(*g_pEffectStatusTable)[EFFECTSTATUS_NATURAL_PEACE].EffectSpriteType = EFFECTSPRITETYPE_BLOOD_BURST_DEFENSE_ATTACK_GOLD;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_PARTY_AURA].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_PARTY_AURA].OriginalActionInfo		=  SKILL_PARTY_AURA ;

   
	(*g_pEffectStatusTable)[EFFECTSTATUS_SLAYER_BLOOD_BURST_HIT].EffectSpriteType  = EFFECTSPRITETYPE_BLOOD_BURST_ATTACK_WHITE_LIGHT;
	(*g_pEffectStatusTable)[EFFECTSTATUS_OUSTERS_BLOOD_BURST_HIT].EffectSpriteType = EFFECTSPRITETYPE_BLOOD_BURST_ATTACK_GREEN_LIGHT;
	(*g_pEffectStatusTable)[EFFECTSTATUS_VAMPIRE_BLOOD_BURST_HIT].EffectSpriteType = EFFECTSPRITETYPE_BLOOD_BURST_ATTACK_ORANGE_LIGHT;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HOLY_CROSS_HEAL].EffectSpriteType = EFFECTSPRITETYPE_BLOOD_BURST_HEAL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_WATER_FORCE_HEAL].EffectSpriteType = EFFECTSPRITETYPE_NYMPH_RECOVERY;
	
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_PARTY_AURA_HP].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_PARTY_AURA_HP].OriginalActionInfo		=  SKILL_CLIENT_PARTY_AURA_HP ;

	(*g_pEffectStatusTable)[EFFECTSTATUS_PARTY_AURA_DEFENSE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_PARTY_AURA_DEFENSE].OriginalActionInfo		=  SKILL_CLIENT_PARTY_AURA_DEFENSE ;

	(*g_pEffectStatusTable)[EFFECTSTATUS_PARTY_AURA_TOHIT].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_PARTY_AURA_TOHIT].OriginalActionInfo		=  SKILL_CLIENT_PARTY_AURA_TOHIT ;

	(*g_pEffectStatusTable)[EFFECTSTATUS_PARTY_AURA_LUCKY].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_PARTY_AURA_LUCKY].OriginalActionInfo		=  SKILL_CLIENT_PARTY_AURA_LUCKY ;

	(*g_pEffectStatusTable)[EFFECTSTATUS_PARTY_AURA_DAMAGE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_PARTY_AURA_DAMAGE].OriginalActionInfo		=  SKILL_CLIENT_PARTY_AURA_DAMAGE ;

	(*g_pEffectStatusTable)[EFFECTSTATUS_PARTY_AURA_RESIST].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_PARTY_AURA_RESIST].OriginalActionInfo		=  SKILL_CLIENT_PARTY_AURA_RESIST ;


	// Sjheon 2005.08.05 폭죽 End
	
	// Sjheon 2005.08.17 Market 아이템 Add
	(*g_pEffectStatusTable)[EFFECTSTATUS_CLIENT_MAGICAL_PET_CHANGER].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CLIENT_MAGICAL_PET_CHANGER].OriginalActionInfo		=  SKILL_CLIENT_MAGICAL_PET_CHANGER ;
#if __CONTENTS(__EXPERT_PET_CHANGER)
	(*g_pEffectStatusTable)[EFFECTSTATUS_CLIENT_EXPERT_PET_CHANGER].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CLIENT_EXPERT_PET_CHANGER].OriginalActionInfo	= SKILL_CLIENT_EXPERT_PET_CHANGER ;
#endif //__EXPERT_PET_CHANGER


#if __CONTENTS(__JAPAN_REVERSE_DEVELOP)
	(*g_pEffectStatusTable)[EFFECTSTATUS_ORIGIN_OF_FURY].EffectSpriteType				= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ORIGIN_OF_FURY].OriginalActionInfo				= SKILL_CLIENT_ORIGIN_OF_FURY ;
#endif //__JAPAN_REVERSE_DEVELOP
	(*g_pEffectStatusTable)[EFFECTSTATUS_HOODLUM_STIGMA].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HOODLUM_STIGMA].OriginalActionInfo		=  SKILL_CLIENT_HOODLUM_STIGMA ;


	(*g_pEffectStatusTable)[EFFECTSTATUS_FURIOUS_INCENSE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FURIOUS_INCENSE].OriginalActionInfo		=  SKILL_CLIENT_FURIOUS_INCENSE ;

	(*g_pEffectStatusTable)[EFFECTSTATUS_STRENGTHEN_INCENSE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_STRENGTHEN_INCENSE].OriginalActionInfo		=  SKILL_CLIENT_STRENGTHEN_INCENSE ;

	(*g_pEffectStatusTable)[EFFECTSTATUS_HYPERACTIVE_INCENSE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HYPERACTIVE_INCENSE].OriginalActionInfo		=  SKILL_CLIENT_HYPERACTIVE_INCENSE ;

	(*g_pEffectStatusTable)[EFFECTSTATUS_IMPREGNABLE_INCENSE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_IMPREGNABLE_INCENSE].OriginalActionInfo		=  SKILL_CLIENT_IMPREGNABLE_INCENSE ;


	(*g_pEffectStatusTable)[EFFECTSTATUS_GREYFELL_FORCE_SCROLL].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_GREYFELL_FORCE_SCROLL].OriginalActionInfo		= SKILL_CLIENT_GREYFELL_FORCE_SCROLL;
		
	(*g_pEffectStatusTable)[EFFECTSTATUS_SOVIUS_FORCE_SCROLL].EffectSpriteType			= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SOVIUS_FORCE_SCROLL].OriginalActionInfo		= SKILL_CLIENT_SOVIUS_FORCE_SCROLL;
		
	(*g_pEffectStatusTable)[EFFECTSTATUS_MIR_FORCE_SCROLL].EffectSpriteType				= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_MIR_FORCE_SCROLL].OriginalActionInfo			= SKILL_CLIENT_MIR_FORCE_SCROLL;


	(*g_pEffectStatusTable)[EFFECTSTATUS_BLEEDING].EffectSpriteType				= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLEEDING].OriginalActionInfo			= SKILL_CLIENT_BLEEDING;


	(*g_pEffectStatusTable)[EFFECTSTATUS_PARASITE].EffectSpriteType				= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_PARASITE].OriginalActionInfo			= SKILL_CLIENT_PARASITE;


//	(*g_pEffectStatusTable)[EFFECTSTATUS_SOUND_WAVE].EffectSpriteType			= EFFECTSPRITETYPE_NULL;
//	(*g_pEffectStatusTable)[EFFECTSTATUS_SOUND_WAVE].OriginalActionInfo			= SKILL_CLIENT_SOUND_WAVE;


	(*g_pEffectStatusTable)[EFFECTSTATUS_SILENCE].EffectSpriteType				= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SILENCE].OriginalActionInfo			= SKILL_CLIENT_SILENCE;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_BREATH].EffectSpriteType				= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FIRE_BREATH].ActionInfo				= SKILL_CLIENT_FIRE_BREATH;	
	
	//(*g_pEffectStatusTable)[EFFECTSTATUS_SLAYER_BLOOD_BURST_HIT].EffectSpriteType  = EFFECTSPRITETYPE_BLOOD_BURST_ATTACK_WHITE_LIGHT;
	//(*g_pEffectStatusTable)[EFFECTSTATUS_OUSTERS_BLOOD_BURST_HIT].EffectSpriteType = EFFECTSPRITETYPE_BLOOD_BURST_ATTACK_GREEN_LIGHT;


	//(*g_pEffectStatusTable)[EFFECTSTATUS_BLOODY_BURST].EffectSpriteType  = EFFECTSPRITETYPE_BLOOD_BURST_START;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLOODY_BURST_HIT].EffectSpriteType = EFFECTSPRITETYPE_MIKLLIZZ_PILLAR_OF_FIRE_TYPE_A_START ; //EFFECTSPRITETYPE_BLOOD_BURST_ATTACK_GREEN_LIGHT;


	(*g_pEffectStatusTable)[EFFECTSTATUS_EDGE_ARCH].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_EDGE_ARCH].OriginalActionInfo		= SKILL_CLIENT_EDGE_ARCH;	

	
	(*g_pEffectStatusTable)[EFFECTSTATUS_BOMB_CRASH_WALK].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BOMB_CRASH_WALK].OriginalActionInfo	= SKILL_CLIENT_BOMB_CRASH_WALK_SPARK;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BOMB_CRASH_WALK].ActionInfo			= SKILL_CLIENT_BOMB_CRASH_WALK_SPARK;
	
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_SATELLITE_BOMB_AIM].OriginalActionInfo		= SKILL_SATELLITE_BOMB;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SATELLITE_BOMB_POINT].EffectSpriteType	= EFFECTSPRITETYPE_NULL ;//EFFECTSPRITETYPE_SATELLITE_BOMB_TARGET;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SATELLITE_BOMB_POINT].ActionInfo		= SKILL_CLIENT_SATELLITE_BOMB_POINT;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SATELLITE_BOMB_FIRE].ActionInfo		= SKILL_CLIENT_SATELLITE_BOMB_FIRE;


	(*g_pEffectStatusTable)[EFFECTSTATUS_ILLUSION_INVERSION].EffectSpriteType	= EFFECTSPRITETYPE_ILLUSION_INVERSION_EXPLOSION_2;

	(*g_pEffectStatusTable)[EFFECTSTATUS_HEAVEN_GROUND].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HEAVEN_GROUND].ActionInfo = RESULT_SKILL_HEAVEN_GROUND;

	(*g_pEffectStatusTable)[EFFECTSTATUS_BLOODY_SCARIFY_BOMB].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLOODY_SCARIFY_BOMB].ActionInfo = SKILL_CLIENT_BLOODY_SCARIFY_BOMB;

	(*g_pEffectStatusTable)[EFFECTSTATUS_BLOOD_CURSE].EffectSpriteType = EFFECTSPRITETYPE_BLOODS_SYMPOSION_REPEAT ; //EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLOOD_CURSE].OriginalActionInfo = SKILL_CLIENT_BLOOD_CURSE;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLOODS_SYMPOSION_ATTACK].EffectSpriteType = EFFECTSPRITETYPE_BLOODS_SYMPOSION_REPEAT;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLOODS_SYMPOSION_ATTACK].OriginalActionInfo = SKILL_CLIENT_BLOOD_CURSE;

	(*g_pEffectStatusTable)[EFFECTSTATUS_DUMMY_DRAKE].EffectSpriteType = EFFECTSPRITETYPE_NULL ; //EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DUMMY_DRAKE].OriginalActionInfo = SKILL_CLIENT_DUMMY_DRAKE;


	(*g_pEffectStatusTable)[EFFECTSTATUS_DUMMY_DRAKE_BOMB].EffectSpriteType = EFFECTSPRITETYPE_NULL ; //EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_DUMMY_DRAKE_BOMB].ActionInfo = SKILL_CLIENT_DUMMY_DRAKE_BOMB;

	
	(*g_pEffectStatusTable)[EFFECTSTATUS_HYDRO_CONVERGENCE].EffectSpriteType = EFFECTSPRITETYPE_NULL ;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HYDRO_CONVERGENCE].ActionInfo = SKILL_CLIENT_HYDRO_CONVERGENCE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HYDRO_CONVERGENCE].OriginalActionInfo = SKILL_CLIENT_HYDRO_CONVERGENCE;


	(*g_pEffectStatusTable)[EFFECTSTATUS_HYDRO_CONVERGENCE_BOMB].EffectSpriteType = EFFECTSPRITETYPE_NULL ;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HYDRO_CONVERGENCE_BOMB].ActionInfo = SKILL_CLIENT_HYDRO_CONVERGENCE_BOMB ;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_CLAY].EffectSpriteType = EFFECTSPRITETYPE_NULL ;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_CLAY].ActionInfo = SKILL_CLIENT_SUMMON_CLAY ;

	(*g_pEffectStatusTable)[EFFECTSTATUS_BLOODY_SCARIFY].EffectSpriteType = EFFECTSPRITETYPE_NULL ;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLOODY_SCARIFY].ActionInfo = SKILL_BLOODY_SCARIFY;

	(*g_pEffectStatusTable)[EFFECTSTATUS_HETER_CHAKRAM_BOMB].EffectSpriteType = EFFECTSPRITETYPE_NULL ;
	(*g_pEffectStatusTable)[EFFECTSTATUS_HETER_CHAKRAM_BOMB].ActionInfo = SKILL_CLIENT_HETER_CHAKRAM_BOMB;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_WISP_RED].EffectSpriteType = EFFECTSPRITETYPE_SUMMON_WISP_RED_LOOP;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_WISP_RED].OriginalActionInfo = SKILL_SUMMON_SYLPH;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_WISP_YELLOW].EffectSpriteType = EFFECTSPRITETYPE_SUMMON_WISP_YELLOW_LOOP;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_WISP_YELLOW].OriginalActionInfo = SKILL_SUMMON_SYLPH;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_WISP_GREEN].EffectSpriteType = EFFECTSPRITETYPE_SUMMON_WISP_GREEN_LOOP;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SUMMON_WISP_GREEN].OriginalActionInfo = SKILL_SUMMON_SYLPH;


	//EFFECTSTATUS_HYDRO_CONVERGENCE,             // 530
	//EFFECTSTATUS_HYDRO_CONVERGENCE_BOMB,        // 531


	// 2006.10.20 sjheon Add
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHINE_SWORD].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_SHINE_SWORD].ActionInfo 			= SKILL_CLIENT_SHINE_SWORD;

	// 2007.05.30 chyaya
	(*g_pEffectStatusTable)[EFFECTSTATUS_STUN].EffectSpriteType = EFFECTSPRITETYPE_BLOOD_BURST_DEFENSE_ATTACK_BLUE;

	// 2006.12.01 chyaya - 터프한 눈사람
	(*g_pEffectStatusTable)[EFFECTSTATUS_CLIENT_TOUGH_SNOWMAN_SWORD].EffectSpriteType	= EFFECTSPRITETYPE_TOUGH_SNOWMAN_SWORD;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CLIENT_TOUGH_SNOWMAN_EYES].EffectSpriteType	= EFFECTSPRITETYPE_TOUGH_SNOWMAN_EYES;

	// 2007.12.16 chyaya - 의문의 물약
	(*g_pEffectStatusTable)[EFFECTSTATUS_MYSTERY_POTION].EffectSpriteType		= EFFECTSPRITETYPE_NULL; 
	(*g_pEffectStatusTable)[EFFECTSTATUS_MYSTERY_POTION].OriginalActionInfo		= SKILL_CLIENT_MYSTERY_POTION;
	
	// 2007.12.16 chyaya - 부활 이팩트
	(*g_pEffectStatusTable)[EFFECTSTATUS_REQUEST_RESURRECT].EffectSpriteType	= EFFECTSPRITETYPE_NULL; 
	(*g_pEffectStatusTable)[EFFECTSTATUS_REQUEST_RESURRECT].ActionInfo			= SKILL_CLIENT_REQUEST_RESURRECT_WAITING;

	// 2007.05.22 chyaya - 헬가든
	(*g_pEffectStatusTable)[EFFECTSTATUS_CLIENT_HELL_GARDEN_CRYSTAL_1F].EffectSpriteType	= EFFECTSPRITETYPE_HELL_GARDEN_CRYSTAL_1F;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CLIENT_HELL_GARDEN_CRYSTAL_2F].EffectSpriteType	= EFFECTSPRITETYPE_HELL_GARDEN_CRYSTAL_2F;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CLIENT_HELL_GARDEN_CRYSTAL_3F].EffectSpriteType	= EFFECTSPRITETYPE_HELL_GARDEN_CRYSTAL_3F;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CLIENT_HELL_GARDEN_CRYSTAL_4F].EffectSpriteType	= EFFECTSPRITETYPE_HELL_GARDEN_CRYSTAL_4F;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CLIENT_HELL_GARDEN_CRYSTAL_5F].EffectSpriteType	= EFFECTSPRITETYPE_HELL_GARDEN_CRYSTAL_5F;

	// 2007.05.23 chyaya - 몬스터 재배치
	(*g_pEffectStatusTable)[EFFECTSTATUS_CLIENT_MONSTER_REPOSITION_BOSS].EffectSpriteType		= EFFECTSPRITETYPE_MONSTER_REPOSITION_BOSS;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CLIENT_MONSTER_REPOSITION_STRENGTHEN].EffectSpriteType	= EFFECTSPRITETYPE_MONSTER_REPOSITION_MONSTER;

	(*g_pEffectStatusTable)[EFFECTSTATUS_CLIENT_GEN_MASTER].EffectSpriteType	= EFFECTSPRITETYPE_GEN_MASTER;

	// 2007.07.31 chyaya - 펫 이팩트

	// Shock, Ice, Diet Capsule
	
	int petEffectIdx = EFFECTSTATUS_CLIENT_PET_EFFECT_WOLF_SHOCK_CAPSULE;
	for(int i = 0; i < 4; ++i)
	{
		(*g_pEffectStatusTable)[petEffectIdx++].EffectSpriteType		= EFFECTSPRITETYPE_PET_EFFECT_WOLF_LIGHT_YELLOW_BEHIND + i * 6;
		(*g_pEffectStatusTable)[petEffectIdx++].EffectSpriteType		= EFFECTSPRITETYPE_PET_EFFECT_WOLF_LIGHT_SKYBLUE_BEHIND + i * 6;
		(*g_pEffectStatusTable)[petEffectIdx++].EffectSpriteType		= EFFECTSPRITETYPE_PET_EFFECT_WOLF_LIGHT_PINK_BEHIND + i * 6;
	}


	// 2007.08.01 chyaya - 신규 포스 스크롤
	(*g_pEffectStatusTable)[EFFECTSTATUS_ODIN_FORCE_SCROLL].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ODIN_FORCE_SCROLL].OriginalActionInfo = SKILL_CLIENT_ODIN_FORCE_SCROLL;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_TITUOS_FORCE_SCROLL].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_TITUOS_FORCE_SCROLL].OriginalActionInfo = SKILL_CLIENT_TITUOS_FORCE_SCROLL;

	

	// 2007.08.30 chyaya - 레어 스킬
	(*g_pEffectStatusTable)[EFFECTSTATUS_MAGIC_SHIELD1].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_MAGIC_SHIELD1].OriginalActionInfo = SKILL_MAGIC_SHIELD1;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_MAGIC_SHIELD2].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_MAGIC_SHIELD2].OriginalActionInfo = SKILL_MAGIC_SHIELD2;

	(*g_pEffectStatusTable)[EFFECTSTATUS_EAGLES_EYE1].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_EAGLES_EYE1].OriginalActionInfo = SKILL_EAGLES_EYE1;
	
	(*g_pEffectStatusTable)[EFFECTSTATUS_EAGLES_EYE2].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_EAGLES_EYE2].OriginalActionInfo = SKILL_EAGLES_EYE2;

	(*g_pEffectStatusTable)[EFFECTSTATUS_FREEZE].bUseEffectSprite = false;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FREEZE].ActionInfo = SKILL_CLIENT_FREEZE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FREEZE].OriginalActionInfo = SKILL_FREEZE_RING1;
	(*g_pEffectStatusTable)[EFFECTSTATUS_FREEZE].EffectColor = 225;

	(*g_pEffectStatusTable)[EFFECTSTATUS_BAT_STORM1].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BAT_STORM1].OriginalActionInfo = SKILL_BAT_STORM1;

	(*g_pEffectStatusTable)[EFFECTSTATUS_BAT_STORM2].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BAT_STORM2].OriginalActionInfo = SKILL_BAT_STORM2;

	(*g_pEffectStatusTable)[EFFECTSTATUS_CURSE_OF_BLOOD].bUseEffectSprite = false;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CURSE_OF_BLOOD].ActionInfo = SKILL_CLIENT_CURSE_OF_BLOOD;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CURSE_OF_BLOOD].OriginalActionInfo = SKILL_CURSE_OF_BLOOD1;

	(*g_pEffectStatusTable)[EFFECTSTATUS_BLOODY_SHOUT].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BLOODY_SHOUT].OriginalActionInfo = SKILL_CLIENT_BLOODY_SHOUT;

	(*g_pEffectStatusTable)[EFFECTSTATUS_MIST_OF_SOUL1].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_MIST_OF_SOUL1].OriginalActionInfo = SKILL_MIST_OF_SOUL1;

	(*g_pEffectStatusTable)[EFFECTSTATUS_MIST_OF_SOUL2].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_MIST_OF_SOUL2].OriginalActionInfo = SKILL_MIST_OF_SOUL2;

	(*g_pEffectStatusTable)[EFFECTSTATUS_MIST_OF_SOUL].EffectSpriteType = EFFECTSPRITETYPE_SLEEP;
	(*g_pEffectStatusTable)[EFFECTSTATUS_MIST_OF_SOUL].OriginalActionInfo = SKILL_MIST_OF_SOUL1;

	(*g_pEffectStatusTable)[EFFECTSTATUS_PET_BONUS_EXP].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_PET_BONUS_EXP].OriginalActionInfo = SKILL_CLIENT_PET_BONUS_EXP;
	

#if __CONTENTS(__PREMIUM_CARD)
	(*g_pEffectStatusTable)[EFFECTSTATUS_PREMIUM_CARD].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_PREMIUM_CARD].OriginalActionInfo = SKILL_CLIENT_PREMIUM_CARD;
#endif //__PREMIUM_CARD

#if __CONTENTS(__TIPOJYU_CASTLE)
	(*g_pEffectStatusTable)[EFFECTSTATUS_TIFFAUGES_REALWORLD_RIGHT_UP].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_TIFFAUGES_REALWORLD_RIGHT_UP].ActionInfo		= SKILL_CLIENT_TIPOJYU_LIFE_GATEWAY_NE;

	(*g_pEffectStatusTable)[EFFECTSTATUS_TIFFAUGES_REALWORLD_LEFT_UP].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_TIFFAUGES_REALWORLD_LEFT_UP].ActionInfo		= SKILL_CLIENT_TIPOJYU_LIFE_GATEWAY_NW;

	(*g_pEffectStatusTable)[EFFECTSTATUS_TIFFAUGES_OTHERWORLD_RIGHT_UP].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_TIFFAUGES_OTHERWORLD_RIGHT_UP].ActionInfo		= SKILL_CLIENT_TIPOJYU_HADES_GATEWAY_NE;

	(*g_pEffectStatusTable)[EFFECTSTATUS_TIFFAUGES_OTHERWORLD_LEFT_UP].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_TIFFAUGES_OTHERWORLD_LEFT_UP].ActionInfo		= SKILL_CLIENT_TIPOJYU_HADES_GATEWAY_NW;
//
	(*g_pEffectStatusTable)[EFFECT_CLASS_TIFFAUGES_TRAP_BLUE].EffectSpriteType			= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECT_CLASS_TIFFAUGES_TRAP_BLUE].ActionInfo				= SKILL_CLIENT_TIPOJYU_LIFE_TRAP;

	(*g_pEffectStatusTable)[EFFECT_CLASS_TIFFAUGES_TRAP_RED].EffectSpriteType			= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECT_CLASS_TIFFAUGES_TRAP_RED].ActionInfo					= SKILL_CLIENT_TIPOJYU_HADES_TRAP;
	
	(*g_pEffectStatusTable)[EFFECT_CLASS_TRANSLUCENCY].EffectSpriteType					= EFFECTSPRITETYPE_NULL;	//몬스터 투명 효과를 주기 위해
#endif // __TIPOJYU_CASTLE


#if __CONTENTS(__JAPAN_REVERSE_DEVELOP)
	(*g_pEffectStatusTable)[EFFECTSTATUS_BONUS_ITEM_LOOTING_RATIO].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_BONUS_ITEM_LOOTING_RATIO].OriginalActionInfo = SKILL_CLIENT_BONUS_ITEM_LOOTING_RATIO;
#endif //__JAPAN_REVERSE_DEVELOP

#if __CONTENTS(__2008_OCTOBER_MAKETITEM)
	(*g_pEffectStatusTable)[EFFECTSTATUS_CLIENT_SUCCUBUS_MAINTENANCE].EffectSpriteType		= EFFECTSPRITETYPE_SUCCUBUS_MAINTENANCE;
	(*g_pEffectStatusTable)[EFFECTSTATUS_CLIENT_SUCCUBUS_MAINTENANCE].OriginalActionInfo	= SKILL_CLIENT_SUCCUBUS_SUMMON;
#endif //__2008_OCTOBER_MAKETITEM

#if __CONTENTS(__EXTREME_FORCE_SCROLL)
	(*g_pEffectStatusTable)[EFFECTSTATUS_EXTREME_FORCE_SCROLL].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_EXTREME_FORCE_SCROLL].OriginalActionInfo = SKILL_CLIENT_EFFECT_ITEM_EXTREME_FORCE_SCROLL;
#endif //__EXTREME_FORCE_SCROLL

#if __CONTENTS(__ONIBLA)
	(*g_pEffectStatusTable)[EFFECTSTATUS_ONIBLA_BARRIER_RIGHT_UP].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ONIBLA_BARRIER_RIGHT_UP].ActionInfo		= SKILL_CLIENT_ONIBLA_BARRIER_RIGHT_UP;

	(*g_pEffectStatusTable)[EFFECTSTATUS_ONIBLA_BARRIER_LEFT_UP].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ONIBLA_BARRIER_LEFT_UP].ActionInfo			= SKILL_CLIENT_ONIBLA_BARRIER_LEFT_UP;

	(*g_pEffectStatusTable)[EFFECTSTATUS_ONIBLA_RAISE_BONE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ONIBLA_RAISE_BONE].ActionInfo		= SKILL_CLIENT_ONIBLA_RAISE_BONE;

	
	(*g_pEffectStatusTable)[EFFECTSTATUS_ONIBLA_BLOCK_DOOR_LEFT_UP].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ONIBLA_BLOCK_DOOR_LEFT_UP].ActionInfo		= SKILL_CLIENT_ONIBLA_BLOCK_DOOR_LEFT_UP;

	(*g_pEffectStatusTable)[EFFECTSTATUS_ONIBLA_BLOCK_DOOR_LEFT_UP_OPEN].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ONIBLA_BLOCK_DOOR_LEFT_UP_OPEN].ActionInfo		= SKILL_CLIENT_ONIBLA_BLOCK_DOOR_LEFT_UP_OPEN;

	(*g_pEffectStatusTable)[EFFECTSTATUS_ONIBLA_BLOCK_DOOR_RIGHT_UP].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ONIBLA_BLOCK_DOOR_RIGHT_UP].ActionInfo		= SKILL_CLIENT_ONIBLA_BLOCK_DOOR_RIGHT_UP;

	(*g_pEffectStatusTable)[EFFECTSTATUS_ONIBLA_BLOCK_DOOR_RIGHT_UP_OPEN].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ONIBLA_BLOCK_DOOR_RIGHT_UP_OPEN].ActionInfo		= SKILL_CLIENT_ONIBLA_BLOCK_DOOR_RIGHT_UP_OPEN;

	(*g_pEffectStatusTable)[EFFECTSTATUS_ONIBLA_EXIT_RIGHT_UP].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ONIBLA_EXIT_RIGHT_UP].ActionInfo		= SKILL_CLIENT_ONIBLA_EXIT_RIGHT_UP;

	(*g_pEffectStatusTable)[EFFECTSTATUS_ONIBLA_EXIT_LEFT_UP].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_ONIBLA_EXIT_LEFT_UP].ActionInfo		= SKILL_CLIENT_ONIBLA_EXIT_LEFT_UP;

#endif //__ONIBLA

#if __CONTENTS(__MASTER_EFFECTS)
	(*g_pEffectStatusTable)[EFFECTSTATUS_MASTER_EFFECT_ANGEL_FLUTTER].EffectSpriteType = EFFECTSPRITETYPE_MASTER_EFFECT_ANGEL_FLUTTER;
	(*g_pEffectStatusTable)[EFFECTSTATUS_MASTER_EFFECT_ANGEL_FLUTTER].OriginalActionInfo = SKILL_CLIENT_MASTER_EFFECT_ANGEL_FLUTTER;	

	(*g_pEffectStatusTable)[EFFECTSTATUS_MASTER_EFFECT_SHADOW_OF_BLOODY_DARKNESS].EffectSpriteType = EFFECTSPRITETYPE_MASTER_EFFECT_SHADOW_OF_BLOODY_DARKNESS;
	(*g_pEffectStatusTable)[EFFECTSTATUS_MASTER_EFFECT_SHADOW_OF_BLOODY_DARKNESS].OriginalActionInfo = SKILL_CLIENT_MASTER_EFFECT_SHADOW_OF_BLOODY_DARKNESS;

	(*g_pEffectStatusTable)[EFFECTSTATUS_MASTER_EFFECT_ARIEL_BREATHING].EffectSpriteType = EFFECTSPRITETYPE_MASTER_EFFECT_ARIEL_BREATHING;	
	(*g_pEffectStatusTable)[EFFECTSTATUS_MASTER_EFFECT_ARIEL_BREATHING].OriginalActionInfo = SKILL_CLIENT_MASTER_EFFECT_ARIEL_BREATHING;
#endif //__MASTER_EFFECTS

#if __CONTENTS(__NONE_ADVANCEMENT_SANDGLASS)
	(*g_pEffectStatusTable)[EFFECT_CLASS_BONUS_EXP_SECOND].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECT_CLASS_BONUS_EXP_SECOND].OriginalActionInfo = SKILL_CLIENT_EFFECT_ITEM_BONUS_EXP_SECOND;
#endif //__NONE_ADVANCEMENT_SANDGLASS

#if __CONTENTS(__20091028_ADD_ITEM)
	(*g_pEffectStatusTable)[EFFECT_CLASS_BONUS_EXP_ADVANCE].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECT_CLASS_BONUS_EXP_ADVANCE].OriginalActionInfo = SKILL_CLIENT_EFFECT_ITEM_BONUS_EXP_ADVANCE;

	(*g_pEffectStatusTable)[EFFECT_CLASS_ACCURA_FORCE_SCROLL].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECT_CLASS_ACCURA_FORCE_SCROLL].OriginalActionInfo = SKILL_CLIENT_EFFECT_ITEM_ACCURA_FORCE_SCROLL;

	(*g_pEffectStatusTable)[EFFECT_CLASS_LIFE_FORCE_SCROLL].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECT_CLASS_LIFE_FORCE_SCROLL].OriginalActionInfo = SKILL_CLIENT_EFFECT_ITEM_LIFE_FORCE_SCROLL;

	(*g_pEffectStatusTable)[EFFECT_CLASS_CHAOTIC_STONE_EXP].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECT_CLASS_CHAOTIC_STONE_EXP].OriginalActionInfo = SKILL_CLIENT_EFFECT_ITEM_CHAOTIC_EXPERIENCE_STONE;
#endif //__20091028_ADD_ITEM
	
#if __CONTENTS(__20091116_ADD_RARE_SKILL)
	(*g_pEffectStatusTable)[EFFECTSTATUS_MAGMA_DETONATION1].EffectSpriteType = EFFECTSPRITETYPE_NULL;
	(*g_pEffectStatusTable)[EFFECTSTATUS_MAGMA_DETONATION1].OriginalActionInfo = SKILL_BLADE_MAGMA_DETONATION_1;

 	(*g_pEffectStatusTable)[EFFECTSTATUS_MAGMA_DETONATION2].EffectSpriteType = EFFECTSPRITETYPE_NULL;
 	(*g_pEffectStatusTable)[EFFECTSTATUS_MAGMA_DETONATION2].OriginalActionInfo = SKILL_BLADE_MAGMA_DETONATION_2;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SQUALLY_BARRIER1].EffectSpriteType = EFFECTSPRITETYPE_NULL;
 	(*g_pEffectStatusTable)[EFFECTSTATUS_SQUALLY_BARRIER1].OriginalActionInfo = SKILL_CLIENT_EFFECT_OUSTERS_SQUALLY_BARRIER_1;

	(*g_pEffectStatusTable)[EFFECTSTATUS_SQUALLY_BARRIER2].EffectSpriteType = EFFECTSPRITETYPE_NULL;
 	(*g_pEffectStatusTable)[EFFECTSTATUS_SQUALLY_BARRIER2].OriginalActionInfo = SKILL_CLIENT_EFFECT_OUSTERS_SQUALLY_BARRIER_2;
#endif //__20091116_ADD_RARE_SKILL

	//------------------------------------------------
	// Save
	//------------------------------------------------
	std::ofstream EffectStatusTable(g_pFileDef->getProperty("FILE_INFO_EFFECTSTATUS").c_str(), std::ios::binary);
	(*g_pEffectStatusTable).SaveToFile(EffectStatusTable);
	EffectStatusTable.close();
#endif
	//*/

	//------------------------------------------------
	// Load
	//------------------------------------------------
	ivfstream EffectStatusTable2;//(FILE_INFO_EffectStatus, ios::binary);
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_INFO_EFFECTSTATUS").c_str(), EffectStatusTable2))
		return FALSE;
	(*g_pEffectStatusTable).LoadFromFile(EffectStatusTable2);
	EffectStatusTable2.close();
	
	return TRUE;
}
