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
#include "windows.h"
#include "MMinMaxInfo.h"
#include "packet/Properties.h"
#include "MItem.h"

#include "Packet\types\PacketItemDef.h"
#include "MathTable.h"
#include <math.h>

#define SAVE_TO_FILE

HRESULT InitFail(LPCTSTR szError,...);
bool 
FileOpenBinary(const char* filename, ivfstream& file);
//---------------------------------------------------------------------------
// Open File
//---------------------------------------------------------------------------
bool 
FileCheck(const char* filename);

BOOL	InitActionInfoTableVampire(CCreatureFramePack		&CreatureFPK ,int *FrameSize, int *VampireActionDelay)
{
	//-------------------------------------------------------------
	//
	//                       Vampire 마법
	//
	//-------------------------------------------------------------

	// 뱀프기술,
	// SKILL_BLOOD_DRAIN,			// 흡혈
	

#ifdef __EXPO_CLIENT__
	(*g_pActionInfoTable)[SKILL_BLOOD_DRAIN].SetExpoSkill();
#endif
	(*g_pActionInfoTable)[SKILL_BLOOD_DRAIN].Set("SKILL_BLOOD_DRAIN", ACTION_VAMPIRE_DRAIN, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_BLOOD_DRAIN].SetPacketType( ACTIONINFO_PACKET_BLOOD_DRAIN );	
	(*g_pActionInfoTable)[SKILL_BLOOD_DRAIN].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_BLOOD_DRAIN].SetStartWithCasting();

	// MAGIC_DARKNESS,		// Darkness
	(*g_pActionInfoTable)[MAGIC_DARKNESS].Set("MAGIC_DARKNESS", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_DARKNESS].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_DARKNESS].SetSoundID( SOUNDID_NULL );	

	// MAGIC_DARKNESS,		// Darkness
	(*g_pActionInfoTable)[MAGIC_DARKNESS_WIDE].Set("MAGIC_DARKNESS_WIDE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_DARKNESS_WIDE].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_DARKNESS_WIDE].SetSoundID( SOUNDID_NULL );	

	// MAGIC_POISONOUS_HANDS,		// Poisonous Hands
	(*g_pActionInfoTable)[MAGIC_POISONOUS_HANDS].Set("MAGIC_POISONOUS_HANDS", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[MAGIC_POISONOUS_HANDS].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[MAGIC_POISONOUS_HANDS].SetStartFrameAll( 6 );
	(*g_pActionInfoTable)[MAGIC_POISONOUS_HANDS].SetSoundID( SOUNDID_NULL );	
	(*g_pActionInfoTable)[MAGIC_POISONOUS_HANDS].Init( 1 );		
	(*g_pActionInfoTable)[MAGIC_POISONOUS_HANDS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[MAGIC_POISONOUS_HANDS][0].EffectSpriteType	= EFFECTSPRITETYPE_POISONOUS_HAND;
	(*g_pActionInfoTable)[MAGIC_POISONOUS_HANDS][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_POISONOUS_HANDS][0].Count				= FrameSize[EFFECTSPRITETYPE_POISONOUS_HAND];
	(*g_pActionInfoTable)[MAGIC_POISONOUS_HANDS][0].SoundID			= SOUND_VAMPIRE_POISON_PH;
	(*g_pActionInfoTable)[MAGIC_POISONOUS_HANDS][0].SetResultTime();
	
	// MAGIC_GREEN_POISON,			// Green Poison
	(*g_pActionInfoTable)[MAGIC_GREEN_POISON].Set("MAGIC_GREEN_POISON", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_GREEN_POISON].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_GREEN_POISON].SetSoundID( SOUNDID_NULL );	
	(*g_pActionInfoTable)[MAGIC_GREEN_POISON].SetEffectStatus(EFFECTSTATUS_GREEN_POISON);
	

	// MAGIC_GREEN_STALKER,		// Green Stalker
	(*g_pActionInfoTable)[MAGIC_GREEN_STALKER].Set("MAGIC_GREEN_STALKER", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_GREEN_STALKER_1, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	//(*g_pActionInfoTable)[RESULT_VAMPIRE_DIE].SetCastingStartFrameAll( 0 );
	(*g_pActionInfoTable)[MAGIC_GREEN_STALKER].SetCastingFramesAll( 16 );
	(*g_pActionInfoTable)[MAGIC_GREEN_STALKER].SetStartFrameAll( 16 );
	(*g_pActionInfoTable)[MAGIC_GREEN_STALKER].SetSoundID( SOUND_VAMPIRE_GREENSTALKER1 );
	(*g_pActionInfoTable)[MAGIC_GREEN_STALKER].Init( 1 );		
	(*g_pActionInfoTable)[MAGIC_GREEN_STALKER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[MAGIC_GREEN_STALKER][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_FLY_GREEN_STALKER;//EFFECTSPRITETYPE_GREEN_STALKER_2;
	(*g_pActionInfoTable)[MAGIC_GREEN_STALKER][0].Step				= 20;
	(*g_pActionInfoTable)[MAGIC_GREEN_STALKER][0].Count				= 32;//FrameSize[EFFECTSPRITETYPE_ACID_BOLT_1];
	(*g_pActionInfoTable)[MAGIC_GREEN_STALKER][0].SoundID			= SOUND_VAMPIRE_GREENSTALKER2;
	//(*g_pActionInfoTable)[MAGIC_GREEN_STALKER][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	//(*g_pActionInfoTable)[MAGIC_GREEN_STALKER][1].EffectSpriteType	= EFFECTSPRITETYPE_GREEN_STALKER_2;
	//(*g_pActionInfoTable)[MAGIC_GREEN_STALKER][1].Step				= 15;
	//(*g_pActionInfoTable)[MAGIC_GREEN_STALKER][1].Count				= 2;//FrameSize[EFFECTSPRITETYPE_ACID_BOLT_1];

	// MAGIC_PARALYZE,			// Purple Wall
	(*g_pActionInfoTable)[MAGIC_PARALYZE].Set("MAGIC_PARALYZE", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_PARALYZE].SetStartFrameAll( 10 );
	//(*g_pActionInfoTable)[MAGIC_PARALYZE].SetPacketType( ACTIONINFO_PACKET_ZONE );
	(*g_pActionInfoTable)[MAGIC_PARALYZE].SetSoundID( SOUNDID_NULL );	
	//(*g_pActionInfoTable)[MAGIC_PARALYZE].SetOptionRangeToDirection();	// range값을 direction 값으로 사용한다.
	//(*g_pActionInfoTable)[MAGIC_PARALYZE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_ATTACK_MELEE );	// 맞는 결과를 표현한다.	
	(*g_pActionInfoTable)[MAGIC_PARALYZE].SetEffectStatus( EFFECTSTATUS_CURSE_PARALYSIS );
	(*g_pActionInfoTable)[MAGIC_PARALYZE].SetSkillFailDelay(); // 스킬실패해도 딜레이는 남아 있다..

	
	// MAGIC_DOOM,			// Purple Wall
	(*g_pActionInfoTable)[MAGIC_DOOM].Set("MAGIC_DOOM", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_DOOM].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_DOOM].SetSoundID( SOUNDID_NULL );	
	(*g_pActionInfoTable)[MAGIC_DOOM].SetEffectStatus( EFFECTSTATUS_CURSE_DOOM );

	// MAGIC_HALLUCINATION,			// Purple Wall
	(*g_pActionInfoTable)[MAGIC_HALLUCINATION].Set("MAGIC_HALLUCINATION", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_HALLUCINATION].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_HALLUCINATION].SetSoundID( SOUNDID_NULL );	
	(*g_pActionInfoTable)[MAGIC_HALLUCINATION].SetEffectStatus( EFFECTSTATUS_HALLUCINATION );

	// MAGIC_DEATH,			// Purple Wall
	(*g_pActionInfoTable)[MAGIC_DEATH].Set("MAGIC_DEATH", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_DEATH].SetUser(FLAG_ACTIONINFO_USER_ALL & ~FLAG_ACTIONINFO_USER_VAMPIRE);
	(*g_pActionInfoTable)[MAGIC_DEATH].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_DEATH].SetSoundID( SOUNDID_NULL );	
	(*g_pActionInfoTable)[MAGIC_DEATH].SetEffectStatus( EFFECTSTATUS_DEATH );	// [새기술8]
	
	
	/*
	(*g_pActionInfoTable)[MAGIC_PARALYZE].Init( 6 );		
	(*g_pActionInfoTable)[MAGIC_PARALYZE].SetMainNode( 4 );
	(*g_pActionInfoTable)[MAGIC_PARALYZE][0].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE;
	(*g_pActionInfoTable)[MAGIC_PARALYZE][0].EffectSpriteType	= EFFECTSPRITETYPE_PURPLE_WALL_1;
	(*g_pActionInfoTable)[MAGIC_PARALYZE][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_PARALYZE][0].Count				= FrameSize[EFFECTSPRITETYPE_PURPLE_WALL_1];
	(*g_pActionInfoTable)[MAGIC_PARALYZE][0].LinkCount			= 1;
	(*g_pActionInfoTable)[MAGIC_PARALYZE][0].SetDelayNode();
	(*g_pActionInfoTable)[MAGIC_PARALYZE][1].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE;
	(*g_pActionInfoTable)[MAGIC_PARALYZE][1].EffectSpriteType	= EFFECTSPRITETYPE_PURPLE_WALL_1;
	(*g_pActionInfoTable)[MAGIC_PARALYZE][1].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_PARALYZE][1].Count				= FrameSize[EFFECTSPRITETYPE_PURPLE_WALL_1];
	(*g_pActionInfoTable)[MAGIC_PARALYZE][1].LinkCount			= 1;
	(*g_pActionInfoTable)[MAGIC_PARALYZE][1].SetDelayNode();
	(*g_pActionInfoTable)[MAGIC_PARALYZE][2].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE;
	(*g_pActionInfoTable)[MAGIC_PARALYZE][2].EffectSpriteType	= EFFECTSPRITETYPE_PURPLE_WALL_1;
	(*g_pActionInfoTable)[MAGIC_PARALYZE][2].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_PARALYZE][2].Count				= FrameSize[EFFECTSPRITETYPE_PURPLE_WALL_1];
	(*g_pActionInfoTable)[MAGIC_PARALYZE][2].LinkCount			= 1;
	(*g_pActionInfoTable)[MAGIC_PARALYZE][2].SetDelayNode();
	(*g_pActionInfoTable)[MAGIC_PARALYZE][3].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE;
	(*g_pActionInfoTable)[MAGIC_PARALYZE][3].EffectSpriteType	= EFFECTSPRITETYPE_PURPLE_WALL_1;
	(*g_pActionInfoTable)[MAGIC_PARALYZE][3].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_PARALYZE][3].Count				= FrameSize[EFFECTSPRITETYPE_PURPLE_WALL_1];
	(*g_pActionInfoTable)[MAGIC_PARALYZE][3].LinkCount			= 1;
	(*g_pActionInfoTable)[MAGIC_PARALYZE][3].SetDelayNode();
	(*g_pActionInfoTable)[MAGIC_PARALYZE][4].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE;
	(*g_pActionInfoTable)[MAGIC_PARALYZE][4].EffectSpriteType	= EFFECTSPRITETYPE_PURPLE_WALL_2;
	(*g_pActionInfoTable)[MAGIC_PARALYZE][4].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_PARALYZE][4].Count				= FrameSize[EFFECTSPRITETYPE_PURPLE_WALL_2];
	(*g_pActionInfoTable)[MAGIC_PARALYZE][4].LinkCount			= 1;
	(*g_pActionInfoTable)[MAGIC_PARALYZE][4].SetDelayNode();
	(*g_pActionInfoTable)[MAGIC_PARALYZE][5].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[MAGIC_PARALYZE][5].EffectSpriteType	= EFFECTSPRITETYPE_PURPLE_WALL_3;
	(*g_pActionInfoTable)[MAGIC_PARALYZE][5].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_PARALYZE][5].Count				= FrameSize[EFFECTSPRITETYPE_PURPLE_WALL_3];
	(*g_pActionInfoTable)[MAGIC_PARALYZE][5].LinkCount			= 1;
	(*g_pActionInfoTable)[MAGIC_PARALYZE][5].SetDelayNode();
	*/
	

	// MAGIC_DARKBLUE_POISON,		// DarkBlue Poison
	(*g_pActionInfoTable)[MAGIC_DARKBLUE_POISON].Set("MAGIC_DARKBLUE_POISON", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_DARKBLUE_POISON].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_DARKBLUE_POISON].SetSoundID( SOUNDID_NULL );	
	(*g_pActionInfoTable)[MAGIC_DARKBLUE_POISON].SetEffectStatus(EFFECTSTATUS_DARKBLUE_POISON);

	// MAGIC_YELLOW_POISON,		// Yellow Poison
	(*g_pActionInfoTable)[MAGIC_YELLOW_POISON].Set("MAGIC_YELLOW_POISON", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_YELLOW_POISON].SetUser(FLAG_ACTIONINFO_USER_ALL & ~FLAG_ACTIONINFO_USER_VAMPIRE);
	(*g_pActionInfoTable)[MAGIC_YELLOW_POISON].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_YELLOW_POISON].SetSoundID( SOUNDID_NULL );	
	(*g_pActionInfoTable)[MAGIC_YELLOW_POISON].SetEffectStatus( EFFECTSTATUS_YELLOW_POISON );	

	// MAGIC_SUMMON_MONSTERS,
	(*g_pActionInfoTable)[MAGIC_SUMMON_MONSTERS].Set("MAGIC_SUMMON_MONSTERS", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_SUMMON_MONSTERS].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_SUMMON_MONSTERS].SetSoundID( SOUNDID_NULL );	

	// MAGIC_DUPLICATE_SELF,
	(*g_pActionInfoTable)[MAGIC_DUPLICATE_SELF].Set("MAGIC_DUPLICATE_SELF", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_DUPLICATE_SELF].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_DUPLICATE_SELF].SetSoundID( SOUNDID_NULL );	

	// MAGIC_CURSE_LEVEL1,			// Curse Level1
	//(*g_pActionInfoTable)[MAGIC_CURSE_LEVEL1].Set("MAGIC_CURSE_LEVEL1", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	////(*g_pActionInfoTable)[MAGIC_CURSE_LEVEL1].SetStartFrameAll( 5 );
	////(*g_pActionInfoTable)[MAGIC_CURSE_LEVEL1].SetSoundID( SOUND_VAMPIRE_POISON_PH );
	
	// MAGIC_CURSE_LEVEL2,			// Curse Level2
	/*
	(*g_pActionInfoTable)[MAGIC_CURSE_LEVEL2].Set("MAGIC_CURSE_LEVEL2", ACTION_MAGIC, EFFECTSPRITETYPE_DARKNESS_1, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_CURSE_LEVEL2].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAGIC_CURSE_LEVEL2].Init( 1 );		
	(*g_pActionInfoTable)[MAGIC_CURSE_LEVEL2][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[MAGIC_CURSE_LEVEL2][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[MAGIC_CURSE_LEVEL2][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_CURSE_LEVEL2][0].Count				= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[MAGIC_CURSE_LEVEL2][0].SoundID					= 4;
	*/

	// MAGIC_CURSE_LEVEL3,			// Curse Level3
	/*
	(*g_pActionInfoTable)[MAGIC_CURSE_LEVEL3].Set("MAGIC_CURSE_LEVEL3", ACTION_MAGIC, EFFECTSPRITETYPE_DARKNESS_1, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_CURSE_LEVEL3].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAGIC_CURSE_LEVEL3].Init( 1 );		
	(*g_pActionInfoTable)[MAGIC_CURSE_LEVEL3][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[MAGIC_CURSE_LEVEL3][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[MAGIC_CURSE_LEVEL3][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_CURSE_LEVEL3][0].Count				= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[MAGIC_CURSE_LEVEL3][0].SoundID					= 4;
	*/

	// MAGIC_ACID_TOUCH,			// Acid Touch
	(*g_pActionInfoTable)[MAGIC_ACID_TOUCH].Set("MAGIC_ACID_TOUCH", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
//	(*g_pActionInfoTable)[MAGIC_ACID_TOUCH].Set("MAGIC_ACID_TOUCH", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_ATTACK]);
//	(*g_pActionInfoTable)[MAGIC_ACID_TOUCH].SetStartFrameAll( 6 );
	(*g_pActionInfoTable)[MAGIC_ACID_TOUCH].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[MAGIC_ACID_TOUCH].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[MAGIC_ACID_TOUCH].SetSoundID( SOUNDID_NULL );	
	(*g_pActionInfoTable)[MAGIC_ACID_TOUCH].SetAttachSelf();
	(*g_pActionInfoTable)[MAGIC_ACID_TOUCH].Init( 1 );		
	(*g_pActionInfoTable)[MAGIC_ACID_TOUCH][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[MAGIC_ACID_TOUCH][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_ACID_TOUCH_MALE_NORMAL;//EFFECTSPRITETYPE_ACID_TOUCH;
	(*g_pActionInfoTable)[MAGIC_ACID_TOUCH][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_ACID_TOUCH][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_ACID_TOUCH_MALE_NORMAL];
	(*g_pActionInfoTable)[MAGIC_ACID_TOUCH][0].SoundID			= SOUND_VAMPIRE_ACID_AT;
	(*g_pActionInfoTable)[MAGIC_ACID_TOUCH][0].SetResultTime();

	// SKILL_HANDS_OF_WISDOM,			// Acid Touch
	(*g_pActionInfoTable)[SKILL_HANDS_OF_WISDOM].Set("SKILL_HANDS_OF_WISDOM", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_HANDS_OF_WISDOM].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_HANDS_OF_WISDOM].SetStartFrameAll( 6 );
	(*g_pActionInfoTable)[SKILL_HANDS_OF_WISDOM].SetSoundID( SOUNDID_NULL );	
	(*g_pActionInfoTable)[SKILL_HANDS_OF_WISDOM].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_HANDS_OF_WISDOM][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_HANDS_OF_WISDOM][0].EffectSpriteType	= EFFECTSPRITETYPE_HANDS_OF_WISDOM;
	(*g_pActionInfoTable)[SKILL_HANDS_OF_WISDOM][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_HANDS_OF_WISDOM][0].Count				= FrameSize[EFFECTSPRITETYPE_HANDS_OF_WISDOM];
	(*g_pActionInfoTable)[SKILL_HANDS_OF_WISDOM][0].SoundID			= SOUND_VAMPIRE_HALLUCINATION;
	(*g_pActionInfoTable)[SKILL_HANDS_OF_WISDOM][0].SetResultTime();

	// MAGIC_ACID_BOLT,			// Acid Bolt
	(*g_pActionInfoTable)[MAGIC_ACID_BOLT].Set("MAGIC_ACID_BOLT", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_ACID_BOLT].SetStartFrameAll( 14 );
	(*g_pActionInfoTable)[MAGIC_ACID_BOLT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAGIC_ACID_BOLT].Init( 1 );		
	(*g_pActionInfoTable)[MAGIC_ACID_BOLT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[MAGIC_ACID_BOLT][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_ACID_BOLT_1;
	(*g_pActionInfoTable)[MAGIC_ACID_BOLT][0].Step				= 20;
	(*g_pActionInfoTable)[MAGIC_ACID_BOLT][0].Count				= 32;//FrameSize[EFFECTSPRITETYPE_ACID_BOLT_1];
	(*g_pActionInfoTable)[MAGIC_ACID_BOLT][0].SoundID			= SOUND_VAMPIRE_ACID_ABOLT1;
	//(*g_pActionInfoTable)[MAGIC_ACID_BOLT][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	//(*g_pActionInfoTable)[MAGIC_ACID_BOLT][1].EffectSpriteType	= EFFECTSPRITETYPE_ACID_BOLT_1;
	//(*g_pActionInfoTable)[MAGIC_ACID_BOLT][1].Step				= 15;
	//(*g_pActionInfoTable)[MAGIC_ACID_BOLT][1].Count				= 2;//FrameSize[EFFECTSPRITETYPE_ACID_BOLT_1];

	// MAGIC_ACID_BALL,			// Acid Ball
	(*g_pActionInfoTable)[MAGIC_ACID_BALL].Set("MAGIC_ACID_BALL", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_ACID_BALL].SetStartFrameAll( 14 );
	(*g_pActionInfoTable)[MAGIC_ACID_BALL].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAGIC_ACID_BALL].Init( 1 );		
	(*g_pActionInfoTable)[MAGIC_ACID_BALL][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[MAGIC_ACID_BALL][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_ACID_BALL_1;
	(*g_pActionInfoTable)[MAGIC_ACID_BALL][0].Step				= 20;
	(*g_pActionInfoTable)[MAGIC_ACID_BALL][0].Count				= 32;//FrameSize[EFFECTSPRITETYPE_DARKNESS_2];
	(*g_pActionInfoTable)[MAGIC_ACID_BALL][0].SoundID			= SOUND_VAMPIRE_ACIDBALL1;
	//(*g_pActionInfoTable)[MAGIC_ACID_BALL][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	//(*g_pActionInfoTable)[MAGIC_ACID_BALL][1].EffectSpriteType	= EFFECTSPRITETYPE_ACID_BALL_1;
	//(*g_pActionInfoTable)[MAGIC_ACID_BALL][1].Step				= 15;
	//(*g_pActionInfoTable)[MAGIC_ACID_BALL][1].Count				= 2;//FrameSize[EFFECTSPRITETYPE_DARKNESS_2];

	// MAGIC_ACID_SWAMP,			// Acid Swamp
	(*g_pActionInfoTable)[MAGIC_ACID_SWAMP].Set("MAGIC_ACID_SWAMP", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_ACID_SWAMP].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_ACID_SWAMP].SetSoundID( SOUNDID_NULL );	

	// MAGIC_REGENERATION,			// Acid Swamp
	(*g_pActionInfoTable)[MAGIC_REGENERATION].Set("MAGIC_REGENERATION", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
//	(*g_pActionInfoTable)[MAGIC_REGENERATION].Set("MAGIC_REGENERATION", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_REGENERATION].SetStartFrameAll( 10 );
//	(*g_pActionInfoTable)[MAGIC_REGENERATION].SetCastingActionInfo( CASTING_HEALING );
	(*g_pActionInfoTable)[MAGIC_REGENERATION].SetSoundID( SOUND_SLAYER_ENCHANT_CL );	

	// MAGIC_GROUND_ATTACK,			// 불기둥
	(*g_pActionInfoTable)[MAGIC_GROUND_ATTACK].Set("MAGIC_GROUND_ATTACK", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_GROUND_ATTACK].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_GROUND_ATTACK].SetSoundID( SOUNDID_NULL );	
	(*g_pActionInfoTable)[MAGIC_GROUND_ATTACK].SetActionResult( SKILL_ATTACK_MELEE );

	// MAGIC_METEOR,			// 메테오
	(*g_pActionInfoTable)[MAGIC_METEOR].Set("MAGIC_METEOR", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_SKY, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_METEOR].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_METEOR].SetSoundID( SOUNDID_NULL );	
//	(*g_pActionInfoTable)[MAGIC_METEOR].SetActionResult( SKILL_ATTACK_MELEE );

	// MAGIC_BLOODY_NAIL,			// Bloody Nail
	(*g_pActionInfoTable)[MAGIC_BLOODY_NAIL].Set("MAGIC_BLOODY_NAIL", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 1,FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
//	(*g_pActionInfoTable)[MAGIC_BLOODY_NAIL].SetStartFrameAll( 6 );
	(*g_pActionInfoTable)[MAGIC_BLOODY_NAIL].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[MAGIC_BLOODY_NAIL].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[MAGIC_BLOODY_NAIL].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAGIC_BLOODY_NAIL].SetAttachSelf();
	(*g_pActionInfoTable)[MAGIC_BLOODY_NAIL].Init( 1 );		
	(*g_pActionInfoTable)[MAGIC_BLOODY_NAIL][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[MAGIC_BLOODY_NAIL][0].EffectSpriteType	= EFFECTSPRITETYPE_RENEWAL_BLOODY_NAIL_MALE_ACTION_1_NORMAL;
	(*g_pActionInfoTable)[MAGIC_BLOODY_NAIL][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_BLOODY_NAIL][0].Count				= FrameSize[EFFECTSPRITETYPE_RENEWAL_BLOODY_NAIL_MALE_ACTION_1_NORMAL];
	(*g_pActionInfoTable)[MAGIC_BLOODY_NAIL][0].SetResultTime();
	//(*g_pActionInfoTable)[MAGIC_BLOODY_NAIL][0].SoundID					= 4;

	// MAGIC_BLOODY_KNIFE,			// Bloody Knife
	(*g_pActionInfoTable)[MAGIC_BLOODY_KNIFE].Set("MAGIC_BLOODY_KNIFE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_BLOODY_KNIFE].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_BLOODY_KNIFE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAGIC_BLOODY_KNIFE].Init( 1 );		
	(*g_pActionInfoTable)[MAGIC_BLOODY_KNIFE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[MAGIC_BLOODY_KNIFE][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_KNIFE_1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_KNIFE][0].Step				= 20;
	(*g_pActionInfoTable)[MAGIC_BLOODY_KNIFE][0].Count				= 32;//FrameSize[EFFECTSPRITETYPE_BLOODY_KNIFE_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_KNIFE][0].SoundID			= SOUND_VAMPIRE_BLOODYKNIFE;	


	// MAGIC_BLOODY_BALL,			// Bloody Ball
	(*g_pActionInfoTable)[MAGIC_BLOODY_BALL].Set("MAGIC_BLOODY_BALL", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_BLOODY_BALL].SetCastingStartFrameAll( 1 );
	(*g_pActionInfoTable)[MAGIC_BLOODY_BALL].SetStartFrameAll( 16 );
	(*g_pActionInfoTable)[MAGIC_BLOODY_BALL].SetSoundID( SOUND_VAMPIRE_BLOODYBALL );
	(*g_pActionInfoTable)[MAGIC_BLOODY_BALL].Init( 2 );		
	(*g_pActionInfoTable)[MAGIC_BLOODY_BALL][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BALL][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_BALL_2_MALE;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BALL][0].Step				= 30;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BALL][0].Count				= 32;//FrameSize[EFFECTSPRITETYPE_BLOODY_KNIFE_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_BALL][1].EffectGeneratorID	= EFFECTGENERATORID_SPREAD_OUT;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BALL][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_KNIFE_1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BALL][1].Step				= 20;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BALL][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_KNIFE_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_BALL].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, MAGIC_BLOODY_BALL );	// 맞는 결과를 표현한다.	

	// MAGIC_BLOODY_WALL,			// Bloody Wall
	(*g_pActionInfoTable)[MAGIC_BLOODY_WALL].Set("MAGIC_BLOODY_WALL", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_BLOODY_WALL].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_BLOODY_WALL].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAGIC_BLOODY_WALL].SetOptionRangeToDirection();

	// MAGIC_BLOODY_SPEAR,			// Bloody Spear
	(*g_pActionInfoTable)[MAGIC_BLOODY_SPEAR].Set("MAGIC_BLOODY_SPEAR", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_BLOODY_SPEAR].SetStartFrameAll( 12 );
	(*g_pActionInfoTable)[MAGIC_BLOODY_SPEAR].SetSoundID( SOUNDID_NULL );
	//(*g_pActionInfoTable)[MAGIC_BLOODY_SPEAR].Init( 1 );		
	//(*g_pActionInfoTable)[MAGIC_BLOODY_SPEAR][0].EffectGeneratorID	= EFFECTGENERATORID_RISING;
	//(*g_pActionInfoTable)[MAGIC_BLOODY_SPEAR][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_SPEAR_1_1;
	//(*g_pActionInfoTable)[MAGIC_BLOODY_SPEAR][0].Step				= 50;
	//(*g_pActionInfoTable)[MAGIC_BLOODY_SPEAR][0].Count				= 9;//FrameSize[EFFECTSPRITETYPE_ACID_BOLT_1];
	//(*g_pActionInfoTable)[MAGIC_BLOODY_SPEAR][0].SoundID			= SOUND_VAMPIRE_BLOODYBALL;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SPEAR].Init( 2 );
	(*g_pActionInfoTable)[MAGIC_BLOODY_SPEAR][0].EffectGeneratorID	= EFFECTGENERATORID_FALLING;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SPEAR][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_SPEAR_1_2;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SPEAR][0].Step				= 60;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SPEAR][0].Count				= 6;//FrameSize[EFFECTSPRITETYPE_BLOODY_KNIFE_2];
	(*g_pActionInfoTable)[MAGIC_BLOODY_SPEAR][0].SoundID			= SOUND_VAMPIRE_BLOODYBALL;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SPEAR][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SPEAR][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_SPEAR_3_3;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SPEAR][1].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SPEAR][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_SPEAR_1_3];
	(*g_pActionInfoTable)[MAGIC_BLOODY_SPEAR][1].SoundID				= SOUND_VAMPIRE_MISC_D;	
	
	
	
	// MAGIC_HIDE,					// Hide
	(*g_pActionInfoTable)[MAGIC_HIDE].Set("MAGIC_HIDE", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);	
	(*g_pActionInfoTable)[MAGIC_HIDE].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_HIDE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAGIC_HIDE].SetActionResult( ACTIONRESULTNODE_CREATURE_BURROW );	// 사용한 캐릭터를 숨게 한다.


	// MAGIC_INVISIBILITY,			// Invisibility
	(*g_pActionInfoTable)[MAGIC_INVISIBILITY].Set("MAGIC_INVISIBILITY", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);	
	(*g_pActionInfoTable)[MAGIC_INVISIBILITY].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAGIC_INVISIBILITY].SetStartFrameAll( 15 );
	(*g_pActionInfoTable)[MAGIC_INVISIBILITY].SetActionResult( ACTIONRESULTNODE_CREATURE_INVISIBLE );	// 사용한 캐릭터를 안 보이게 한다.
	(*g_pActionInfoTable)[MAGIC_INVISIBILITY].SetEffectStatus( EFFECTSTATUS_INVISIBILITY );
	
	// MAGIC_SUMMON_CASKET,				// Summon
	(*g_pActionInfoTable)[MAGIC_SUMMON_CASKET].Set("MAGIC_SUMMON_CASKET", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_ITEM, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);	
	(*g_pActionInfoTable)[MAGIC_SUMMON_CASKET].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_SUMMON_CASKET].SetSoundID( SOUND_VAMPIRE_SUMMONCASKET );
	(*g_pActionInfoTable)[MAGIC_SUMMON_CASKET].SetActionResult( ACTIONRESULTNODE_SUMMON_CASKET );	// 관 소환

	// MAGIC_OPEN_CASKET,				// Summon
	(*g_pActionInfoTable)[MAGIC_OPEN_CASKET].Set("MAGIC_OPEN_CASKET", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_ITEM, FLAG_ACTIONINFO_START_USER, 10);	
	(*g_pActionInfoTable)[MAGIC_OPEN_CASKET].SetStartWithCasting();
	(*g_pActionInfoTable)[MAGIC_OPEN_CASKET].SetSoundID( SOUND_VAMPIRE_SUMMONCASKET );
	(*g_pActionInfoTable)[MAGIC_OPEN_CASKET].SetActionResult( ACTIONRESULTNODE_OPEN_CASKET );	// 관에서 나가기
	
	// MAGIC_SUMMON_WOLF,				// Summon
	(*g_pActionInfoTable)[MAGIC_SUMMON_WOLF].Set("MAGIC_SUMMON_WOLF", ACTION_MAGIC, EFFECTSPRITETYPE_DARKNESS_1, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);	
	(*g_pActionInfoTable)[MAGIC_SUMMON_WOLF].SetSoundID( SOUNDID_NULL );

	// MAGIC_SUMMON_SERVANT,				// Summon
	(*g_pActionInfoTable)[MAGIC_SUMMON_SERVANT].Set("MAGIC_SUMMON_SERVANT", ACTION_MAGIC, EFFECTSPRITETYPE_DARKNESS_1, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);	
	(*g_pActionInfoTable)[MAGIC_SUMMON_SERVANT].SetSoundID( SOUNDID_NULL );
	
	// MAGIC_RAISING_DEAD,				// Summon
	(*g_pActionInfoTable)[MAGIC_RAISING_DEAD].Set("MAGIC_RAISING_DEAD", ACTION_MAGIC, EFFECTSPRITETYPE_DARKNESS_1, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);	
	(*g_pActionInfoTable)[MAGIC_RAISING_DEAD].SetSoundID( SOUNDID_NULL );
	
		// MAGIC_TRANSFORM_TO_BAT,						//	Transform To Bat 		 110
	(*g_pActionInfoTable)[MAGIC_TRANSFORM_TO_BAT].Set("MAGIC_TRANSFORM_TO_BAT", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_ITEM, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);	
	(*g_pActionInfoTable)[MAGIC_TRANSFORM_TO_BAT].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_TRANSFORM_TO_BAT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAGIC_TRANSFORM_TO_BAT].SetEffectStatus( EFFECTSTATUS_TRANSFORM_TO_BAT );
	(*g_pActionInfoTable)[MAGIC_TRANSFORM_TO_BAT].SetActionResult( ACTIONRESULTNODE_CHANGE_CREATURE_TYPE );	// 변신

	// MAGIC_TRANSFORM_TO_WOLF,					//	Transform To Wolf		 111
	(*g_pActionInfoTable)[MAGIC_TRANSFORM_TO_WOLF].Set("MAGIC_TRANSFORM_TO_WOLF", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_ITEM, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);	
	(*g_pActionInfoTable)[MAGIC_TRANSFORM_TO_WOLF].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_TRANSFORM_TO_WOLF].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAGIC_TRANSFORM_TO_WOLF].SetEffectStatus( EFFECTSTATUS_TRANSFORM_TO_WOLF );
	(*g_pActionInfoTable)[MAGIC_TRANSFORM_TO_WOLF].SetActionResult( ACTIONRESULTNODE_CHANGE_CREATURE_TYPE );	// 변신

	
	// MAGIC_UN_TRANSFORM,					// UN_TRANSFORM
	(*g_pActionInfoTable)[MAGIC_UN_TRANSFORM].Set("MAGIC_UN_TRANSFORM", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);	
	(*g_pActionInfoTable)[MAGIC_UN_TRANSFORM].SetStartWithCasting();	
	(*g_pActionInfoTable)[MAGIC_UN_TRANSFORM].SetSoundID( SOUNDID_NULL );
	//(*g_pActionInfoTable)[MAGIC_UN_TRANSFORM].SetActionResult( ACTIONRESULTNODE_CREATURE_BURROW );	// 사용한 캐릭터를 숨게 한다.

	// MAGIC_UN_BURROW,					// UN_BURROW
	(*g_pActionInfoTable)[MAGIC_UN_BURROW].Set("MAGIC_UN_BURROW", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);	
	(*g_pActionInfoTable)[MAGIC_UN_BURROW].SetStartWithCasting();	
	(*g_pActionInfoTable)[MAGIC_UN_BURROW].SetSoundID( SOUNDID_NULL );
	//(*g_pActionInfoTable)[MAGIC_UN_BURROW].SetActionResult( ACTIONRESULTNODE_CREATURE_BURROW );	// 사용한 캐릭터를 숨게 한다.

	// MAGIC_UN_INVISIBILITY,					// UN_INVISIBILITY
	(*g_pActionInfoTable)[MAGIC_UN_INVISIBILITY].Set("MAGIC_UN_INVISIBILITY", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);	
	(*g_pActionInfoTable)[MAGIC_UN_INVISIBILITY].SetStartWithCasting();	
	(*g_pActionInfoTable)[MAGIC_UN_INVISIBILITY].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAGIC_UN_INVISIBILITY].SetActionResult( ACTIONRESULTNODE_CREATURE_VISIBLE );	// 사용한 캐릭터를 보이게 한다.

	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_DRAIN].Set("RESULT_SKILL_BLOOD_DRAIN", ACTION_DRAINED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_DRAIN].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_DRAIN].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_DRAIN].Init( 3 );
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_DRAIN].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_DRAIN][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_DRAIN][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_DRAIN_1;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_DRAIN][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_DRAIN][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_DRAIN_1];
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_DRAIN][0].SoundID				= SOUND_VAMPIRE_MISC_BD;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_DRAIN][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_DRAIN][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_DRAIN_2;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_DRAIN][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_DRAIN][1].Count				= 10 * FrameSize[EFFECTSPRITETYPE_BLOOD_DRAIN_2];
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_DRAIN][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_DRAIN][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_DRAIN_3;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_DRAIN][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_DRAIN][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_DRAIN_3];

	// MAGIC_DARKNESS,		// Darkness
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS_WIDE].Set("RESULT_MAGIC_DARKNESS_WIDE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS_WIDE].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS_WIDE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS_WIDE].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS_WIDE].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS_WIDE][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_RECT;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS_WIDE][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS_WIDE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS_WIDE][0].Count				= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS_WIDE][0].SoundID				= SOUND_VAMPIRE_MISC_D;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS_WIDE][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS_WIDE][1].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS_WIDE][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS_WIDE][1].Count				= FrameSize[EFFECTSPRITETYPE_DARKNESS_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS_WIDE][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS_WIDE][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS_WIDE][2].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS_WIDE][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS_WIDE][2].Count				= FrameSize[EFFECTSPRITETYPE_DARKNESS_3];

	// MAGIC_DARKNESS,		// Darkness
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS].Set("RESULT_MAGIC_DARKNESS", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_RECT;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS][0].Count				= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS][0].SoundID				= SOUND_VAMPIRE_MISC_D;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS][1].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS][1].Count				= FrameSize[EFFECTSPRITETYPE_DARKNESS_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS][2].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKNESS][2].Count				= FrameSize[EFFECTSPRITETYPE_DARKNESS_3];

	// MAGIC_POISONOUS_HANDS,		// Poisonous Hands
	(*g_pActionInfoTable)[RESULT_MAGIC_POISONOUS_HANDS].Set("RESULT_MAGIC_POISONOUS_HANDS", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_POISONOUS_HANDS].SetSoundID( SOUNDID_NULL );
	
	// MAGIC_GREEN_POISON,			// Green Poison
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON].Set("RESULT_MAGIC_GREEN_POISON", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON].Init( 6 );		
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][0].EffectSpriteType	= EFFECTSPRITETYPE_GREEN_POISON_FLOOR_START;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][0].Count				= FrameSize[EFFECTSPRITETYPE_GREEN_POISON_FLOOR_START];
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][0].SoundID				= SOUND_VAMPIRE_POISON_GP;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][0].LinkCount				= 0;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][1].EffectSpriteType	= EFFECTSPRITETYPE_GREEN_POISON_SMOKE_START;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][1].Count				= FrameSize[EFFECTSPRITETYPE_GREEN_POISON_SMOKE_START];
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][2].EffectSpriteType	= EFFECTSPRITETYPE_GREEN_POISON_FLOOR_LOOP;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][2].Count				= FrameSize[EFFECTSPRITETYPE_GREEN_POISON_FLOOR_LOOP];
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][2].SetResultTime();
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][2].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][2].LinkCount				= 0;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][3].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][3].EffectSpriteType	= EFFECTSPRITETYPE_GREEN_POISON_SMOKE_LOOP;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][3].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][3].Count				= FrameSize[EFFECTSPRITETYPE_GREEN_POISON_SMOKE_LOOP];
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][3].SetResultTime();
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][3].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][4].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][4].EffectSpriteType	= EFFECTSPRITETYPE_GREEN_POISON_FLOOR_END;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][4].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][4].Count				= FrameSize[EFFECTSPRITETYPE_GREEN_POISON_FLOOR_END];
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][4].LinkCount				= 0;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][5].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][5].EffectSpriteType	= EFFECTSPRITETYPE_GREEN_POISON_SMOKE_END;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][5].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_POISON][5].Count				= FrameSize[EFFECTSPRITETYPE_GREEN_POISON_SMOKE_END];
	
	
	// MAGIC_GREEN_STALKER,		// Green Stalker
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_STALKER].Set("RESULT_MAGIC_GREEN_STALKER", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_STALKER].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_STALKER].Init( 3 );
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_STALKER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_STALKER][0].EffectSpriteType	= EFFECTSPRITETYPE_GREEN_STALKER_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_STALKER][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_STALKER][0].Count				= FrameSize[EFFECTSPRITETYPE_GREEN_STALKER_3];
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_STALKER][0].SoundID			= SOUND_VAMPIRE_ACIDBURN;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_STALKER][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_STALKER][1].EffectSpriteType	= EFFECTSPRITETYPE_GREEN_STALKER_4;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_STALKER][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_STALKER][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_STALKER][1].SetResultTime();
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_STALKER][1].Count				= FrameSize[EFFECTSPRITETYPE_GREEN_STALKER_4];
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_STALKER][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_STALKER][2].EffectSpriteType	= EFFECTSPRITETYPE_GREEN_STALKER_5;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_STALKER][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_GREEN_STALKER][2].Count				= FrameSize[EFFECTSPRITETYPE_GREEN_STALKER_5];
	
	// MAGIC_PARALYZE,			// Purple Wall
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE].Set("RESULT_MAGIC_PARALYZE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][0].EffectSpriteType	= EFFECTSPRITETYPE_PURPLE_WALL_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][0].Count				= FrameSize[EFFECTSPRITETYPE_PURPLE_WALL_1];
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][0].SoundID				= SOUND_VAMPIRE_PARALYSIS;
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][1].EffectSpriteType	= EFFECTSPRITETYPE_PURPLE_WALL_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][1].SetResultTime();
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][1].Count				= FrameSize[EFFECTSPRITETYPE_PURPLE_WALL_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][2].EffectSpriteType	= EFFECTSPRITETYPE_PURPLE_WALL_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][2].Count				= FrameSize[EFFECTSPRITETYPE_PURPLE_WALL_3];
	/*
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_WALL;
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][0].EffectSpriteType	= EFFECTSPRITETYPE_PURPLE_WALL_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][0].Count				= FrameSize[EFFECTSPRITETYPE_PURPLE_WALL_1];
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][0].SoundID				= SOUND_VAMPIRE_POISON_PW;
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][1].EffectSpriteType	= EFFECTSPRITETYPE_PURPLE_WALL_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][1].SetResultTime();
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][1].Count				= FrameSize[EFFECTSPRITETYPE_PURPLE_WALL_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][2].EffectSpriteType	= EFFECTSPRITETYPE_PURPLE_WALL_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_PARALYZE][2].Count				= FrameSize[EFFECTSPRITETYPE_PURPLE_WALL_3];
	*/

	// MAGIC_HALLUCINATION,			// Purple Wall
	(*g_pActionInfoTable)[RESULT_MAGIC_HALLUCINATION].Set("RESULT_MAGIC_HALLUCINATION", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_HALLUCINATION].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_HALLUCINATION].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_MAGIC_HALLUCINATION][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_HALLUCINATION][0].EffectSpriteType	= EFFECTSPRITETYPE_CURSE_BLIND;
	(*g_pActionInfoTable)[RESULT_MAGIC_HALLUCINATION][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_HALLUCINATION][0].Count				= FrameSize[EFFECTSPRITETYPE_CURSE_BLIND];
	(*g_pActionInfoTable)[RESULT_MAGIC_HALLUCINATION][0].SoundID				= SOUND_VAMPIRE_POISON_PW;
	(*g_pActionInfoTable)[RESULT_MAGIC_HALLUCINATION][0].SetDelayNode();
	
	// MAGIC_DEATH,			// Purple Wall
	(*g_pActionInfoTable)[RESULT_MAGIC_DEATH].Set("RESULT_MAGIC_DEATH", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_DEATH].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_DEATH].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_MAGIC_DEATH].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_DEATH][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_DEATH][0].EffectSpriteType	= EFFECTSPRITETYPE_CURSE_DEATH;
	(*g_pActionInfoTable)[RESULT_MAGIC_DEATH][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_DEATH][0].Count				= FrameSize[EFFECTSPRITETYPE_CURSE_DEATH];
	(*g_pActionInfoTable)[RESULT_MAGIC_DEATH][0].SoundID			= SOUND_VAMPIRE_DEATH;
	
	// MAGIC_DARKBLUE_POISON,		// DarkBlue Poison	
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKBLUE_POISON].Set("RESULT_MAGIC_DARKBLUE_POISON", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKBLUE_POISON].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKBLUE_POISON].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKBLUE_POISON].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKBLUE_POISON][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKBLUE_POISON][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKBLUE_POISON_BACK_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKBLUE_POISON][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKBLUE_POISON][0].Count				= FrameSize[EFFECTSPRITETYPE_DARKBLUE_POISON_BACK_1];
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKBLUE_POISON][0].SoundID				= SOUND_VAMPIRE_POISON_GP;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKBLUE_POISON][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKBLUE_POISON][1].EffectSpriteType	= EFFECTSPRITETYPE_DARKBLUE_POISON_BACK_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKBLUE_POISON][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKBLUE_POISON][1].Count				= FrameSize[EFFECTSPRITETYPE_DARKBLUE_POISON_BACK_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKBLUE_POISON][1].SetResultTime();
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKBLUE_POISON][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKBLUE_POISON][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKBLUE_POISON][2].EffectSpriteType	= EFFECTSPRITETYPE_DARKBLUE_POISON_BACK_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKBLUE_POISON][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_DARKBLUE_POISON][2].Count				= FrameSize[EFFECTSPRITETYPE_DARKBLUE_POISON_BACK_3];
	

	// MAGIC_YELLOW_POISON,		// Yellow Poison
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON].Set("RESULT_MAGIC_YELLOW_POISON", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON].Init( 6 );		
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][0].EffectSpriteType	= EFFECTSPRITETYPE_YELLOW_POISON_FLOOR_START;
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][0].Count				= FrameSize[EFFECTSPRITETYPE_YELLOW_POISON_FLOOR_START];
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][0].SoundID				= SOUND_VAMPIRE_POISON_YP;
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][0].LinkCount				= 0;
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][1].EffectSpriteType	= EFFECTSPRITETYPE_YELLOW_POISON_SMOKE_START;
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][1].Count				= FrameSize[EFFECTSPRITETYPE_YELLOW_POISON_SMOKE_START];
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][2].EffectSpriteType	= EFFECTSPRITETYPE_YELLOW_POISON_FLOOR_LOOP;
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][2].Count				= FrameSize[EFFECTSPRITETYPE_YELLOW_POISON_FLOOR_LOOP];
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][2].SetResultTime();
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][2].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][2].LinkCount				= 0;
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][3].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][3].EffectSpriteType	= EFFECTSPRITETYPE_YELLOW_POISON_SMOKE_LOOP;
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][3].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][3].Count				= FrameSize[EFFECTSPRITETYPE_YELLOW_POISON_SMOKE_LOOP];
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][3].SetResultTime();
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][3].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][4].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][4].EffectSpriteType	= EFFECTSPRITETYPE_YELLOW_POISON_FLOOR_END;
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][4].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][4].Count				= FrameSize[EFFECTSPRITETYPE_YELLOW_POISON_FLOOR_END];
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][4].LinkCount				= 0;
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][5].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][5].EffectSpriteType	= EFFECTSPRITETYPE_YELLOW_POISON_SMOKE_END;
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][5].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_YELLOW_POISON][5].Count				= FrameSize[EFFECTSPRITETYPE_YELLOW_POISON_SMOKE_END];
	// MAGIC_CURSE_LEVEL1,			// Curse Level1
	/*
	(*g_pActionInfoTable)[RESULT_MAGIC_CURSE_LEVEL1].Set("RESULT_MAGIC_CURSE_LEVEL1", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_CURSE_LEVEL1].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_CURSE_LEVEL1].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_MAGIC_CURSE_LEVEL1].Init( 3 );
	(*g_pActionInfoTable)[RESULT_MAGIC_CURSE_LEVEL1].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_CURSE_LEVEL1][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURSE_LEVEL1][0].EffectSpriteType	= EFFECTSPRITETYPE_CURSE_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURSE_LEVEL1][0].Step				= 12;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURSE_LEVEL1][0].Count				= FrameSize[EFFECTSPRITETYPE_CURSE_1];
	//(*g_pActionInfoTable)[RESULT_MAGIC_CURSE_LEVEL1][0].SoundID				= SOUND_VAMPIRE_MISC_BD;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURSE_LEVEL1][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURSE_LEVEL1][1].EffectSpriteType	= EFFECTSPRITETYPE_CURSE_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURSE_LEVEL1][1].Step				= 10;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURSE_LEVEL1][1].Count				= 2 * FrameSize[EFFECTSPRITETYPE_CURSE_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_CURSE_LEVEL1][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURSE_LEVEL1][2].EffectSpriteType	= EFFECTSPRITETYPE_CURSE_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURSE_LEVEL1][2].Step				= 6;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURSE_LEVEL1][2].Count				= FrameSize[EFFECTSPRITETYPE_CURSE_3];
	*/

	// MAGIC_CURSE_LEVEL2,			// Curse Level2
	/*
	(*g_pActionInfoTable)[RESULT_MAGIC_CURSE_LEVEL2].Set("RESULT_MAGIC_CURSE_LEVEL2", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, 1000);
	(*g_pActionInfoTable)[RESULT_MAGIC_CURSE_LEVEL2].SetSoundID( SOUNDID_NULL );
	*/

	// MAGIC_CURSE_LEVEL3,			// Curse Level3
	/*
	(*g_pActionInfoTable)[RESULT_MAGIC_CURSE_LEVEL3].Set("RESULT_MAGIC_CURSE_LEVEL3", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, 1500);
	(*g_pActionInfoTable)[RESULT_MAGIC_CURSE_LEVEL3].SetSoundID( SOUNDID_NULL );
	*/

	// MAGIC_ACID_TOUCH,			// Acid Touch
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_TOUCH].Set("RESULT_MAGIC_ACID_TOUCH", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_TOUCH].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_TOUCH].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_TOUCH][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_TOUCH][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_TOUCH][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_TOUCH][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_TOUCH][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_TOUCH][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_TOUCH][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_TOUCH][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_TOUCH][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_TOUCH][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_TOUCH][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_TOUCH][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];

	// RESULT_SKILL_HANDS_OF_WISDOM,			// Acid Touch
	(*g_pActionInfoTable)[RESULT_SKILL_HANDS_OF_WISDOM].Set("RESULT_SKILL_HANDS_OF_WISDOM", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_HANDS_OF_WISDOM].SetSoundID( SOUNDID_NULL );

	// MAGIC_ACID_BOLT,			// Acid Bolt
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BOLT].Set("RESULT_MAGIC_ACID_BOLT", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BOLT].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BOLT].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BOLT].Init( 2 );
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BOLT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BOLT][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_ACID_BOLT_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BOLT][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BOLT][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_ACID_BOLT_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BOLT][0].SoundID			= SOUND_VAMPIRE_ACID_ABOLT2;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BOLT][0].LinkCount			= 1;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BOLT][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BOLT][1].EffectSpriteType	= EFFECTSPRITETYPE_SMOKE;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BOLT][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BOLT][1].Count				= FrameSize[EFFECTSPRITETYPE_SMOKE];
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BOLT][1].SoundID			= SOUND_VAMPIRE_ACIDBURN;	
	
	// MAGIC_ACID_BALL,			// Acid Ball
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BALL].Set("RESULT_MAGIC_ACID_BALL", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BALL].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BALL].Init( 2 );
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BALL][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BALL][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_ACID_BALL_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BALL][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BALL][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_ACID_BALL_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BALL][0].SoundID			= SOUND_VAMPIRE_ACIDBALL2;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BALL][0].LinkCount			= 1;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BALL][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BALL][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE_AROUND;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BALL][1].EffectSpriteType	= EFFECTSPRITETYPE_SMOKE;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BALL][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BALL][1].Count				= FrameSize[EFFECTSPRITETYPE_SMOKE];
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BALL][1].SoundID			= SOUND_VAMPIRE_ACIDBURN;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_BALL][1].SetResultTime();

	// MAGIC_ACID_SWAMP,			// Acid Swamp
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_SWAMP].Set("RESULT_MAGIC_ACID_SWAMP", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_SWAMP].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_SWAMP].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_SWAMP].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_SWAMP].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_SWAMP][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_SWAMP][0].EffectSpriteType	= EFFECTSPRITETYPE_ACID_SWAMP_NEW_START;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_SWAMP][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_SWAMP][0].Count				= FrameSize[EFFECTSPRITETYPE_ACID_SWAMP_NEW_START];
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_SWAMP][0].SoundID				= SOUND_VAMPIRE_ACIDSWAMP;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_SWAMP][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_SWAMP][1].EffectSpriteType	= EFFECTSPRITETYPE_ACID_SWAMP_NEW_LOOP;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_SWAMP][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_SWAMP][1].Count				= FrameSize[EFFECTSPRITETYPE_ACID_SWAMP_NEW_LOOP];
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_SWAMP][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_SWAMP][1].SetResultTime();
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_SWAMP][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_SWAMP][2].EffectSpriteType	= EFFECTSPRITETYPE_ACID_SWAMP_NEW_END;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_SWAMP][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_ACID_SWAMP][2].Count				= FrameSize[EFFECTSPRITETYPE_ACID_SWAMP_NEW_END];

	// RESULT_MAGIC_REGENERATION,			// Acid Swamp
	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION].Set("RESULT_MAGIC_REGENERATION", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION][0].EffectSpriteType	= EFFECTSPRITETYPE_REGENERATION;
	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION][0].Count				= FrameSize[EFFECTSPRITETYPE_REGENERATION];
//	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION][0].SoundID				= SOUND_VAMPIRE_ACIDSWAMP;
	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION][1].EffectSpriteType	= EFFECTSPRITETYPE_REGENERATION_ING;
	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION][1].Count				= FrameSize[EFFECTSPRITETYPE_REGENERATION_ING];
	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION][1].SetResultTime();

	// MAGIC_GROUND_ATTACK,			// 불기둥
	(*g_pActionInfoTable)[RESULT_MAGIC_GROUND_ATTACK].Set("RESULT_MAGIC_GROUND_ATTACK", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_MAGIC_GROUND_ATTACK].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_MAGIC_GROUND_ATTACK].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_GROUND_ATTACK].Init( 2 );		
//	(*g_pActionInfoTable)[RESULT_MAGIC_GROUND_ATTACK].SetMainNode( 0 );
	(*g_pActionInfoTable)[RESULT_MAGIC_GROUND_ATTACK][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_GROUND_ATTACK][0].EffectSpriteType	= EFFECTSPRITETYPE_GROUND_ATTACK_READY;
	(*g_pActionInfoTable)[RESULT_MAGIC_GROUND_ATTACK][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_GROUND_ATTACK][0].Count				= FrameSize[EFFECTSPRITETYPE_GROUND_ATTACK_READY]+10;
	(*g_pActionInfoTable)[RESULT_MAGIC_GROUND_ATTACK][0].SoundID			= SOUND_SLAYER_SWORD_EXPANSION;
	(*g_pActionInfoTable)[RESULT_MAGIC_GROUND_ATTACK][0].LinkCount			= FrameSize[EFFECTSPRITETYPE_GROUND_ATTACK_READY];
	(*g_pActionInfoTable)[RESULT_MAGIC_GROUND_ATTACK][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_GROUND_ATTACK][1].EffectSpriteType	= EFFECTSPRITETYPE_GROUND_ATTACK_FIRE;
	(*g_pActionInfoTable)[RESULT_MAGIC_GROUND_ATTACK][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_GROUND_ATTACK][1].Count				= FrameSize[EFFECTSPRITETYPE_GROUND_ATTACK_FIRE];
	(*g_pActionInfoTable)[RESULT_MAGIC_GROUND_ATTACK][1].SoundID			= SOUND_SLAYER_ENCHANT_AURARING2;
	(*g_pActionInfoTable)[RESULT_MAGIC_GROUND_ATTACK][1].SetResultTime();

	// MAGIC_METEOR					// 메테오
	(*g_pActionInfoTable)[RESULT_MAGIC_METEOR].Set("RESULT_MAGIC_METEOR", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_SKY);
	(*g_pActionInfoTable)[RESULT_MAGIC_METEOR].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_MAGIC_METEOR].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_METEOR].Init( 3 );		
//	(*g_pActionInfoTable)[RESULT_MAGIC_METEOR].SetMainNode( 0 );
	(*g_pActionInfoTable)[RESULT_MAGIC_METEOR][0].EffectGeneratorID	= EFFECTGENERATORID_METEOR_DROP;
	(*g_pActionInfoTable)[RESULT_MAGIC_METEOR][0].EffectSpriteType	= EFFECTSPRITETYPE_METEOR_DROP;
	(*g_pActionInfoTable)[RESULT_MAGIC_METEOR][0].Step				= 30;
	(*g_pActionInfoTable)[RESULT_MAGIC_METEOR][0].Count				= 19;//FrameSize[EFFECTSPRITETYPE_METEOR_DROP];
	(*g_pActionInfoTable)[RESULT_MAGIC_METEOR][0].SoundID			= SOUND_ITEM_FLYING_BOTTLE;
	(*g_pActionInfoTable)[RESULT_MAGIC_METEOR][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_METEOR][1].EffectSpriteType	= EFFECTSPRITETYPE_METEOR_WAVE;
	(*g_pActionInfoTable)[RESULT_MAGIC_METEOR][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_METEOR][1].Count				= FrameSize[EFFECTSPRITETYPE_METEOR_WAVE];
	(*g_pActionInfoTable)[RESULT_MAGIC_METEOR][1].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_MAGIC_METEOR][1].SoundID			= SOUND_SLAYER_ATTACK_BOMB;
	(*g_pActionInfoTable)[RESULT_MAGIC_METEOR][1].SetResultTime();
	(*g_pActionInfoTable)[RESULT_MAGIC_METEOR][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_METEOR][2].EffectSpriteType	= EFFECTSPRITETYPE_METEOR_ROCK;
	(*g_pActionInfoTable)[RESULT_MAGIC_METEOR][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_METEOR][2].Count				= FrameSize[EFFECTSPRITETYPE_METEOR_ROCK];

	// MAGIC_BLOODY_WALL_SINGLE,			// Bloody Block
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL_SINGLE].Set("RESULT_MAGIC_BLOODY_WALL_SINGLE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL_SINGLE].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL_SINGLE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL_SINGLE].Init( 1 );		
//	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL_SINGLE].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL_SINGLE][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL_SINGLE][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL_SINGLE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL_SINGLE][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
//	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL_SINGLE][0].SoundID				= SOUND_VAMPIRE_MISC_D;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL_SINGLE][0].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL_SINGLE][0].SetResultTime();

	// MAGIC_BLOODY_NAIL,			// Bloody Nail
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_NAIL].Set("RESULT_MAGIC_BLOODY_NAIL", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_NAIL].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_NAIL].Init( 4 );
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_NAIL][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_NAIL][0].EffectSpriteType = EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_NAIL][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_NAIL][0].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_1];
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_NAIL][0].LinkCount			= 2;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_NAIL][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_NAIL][1].EffectSpriteType = EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_NAIL][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_NAIL][1].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_NAIL][1].LinkCount			= 2;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_NAIL][2].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_NAIL][2].EffectSpriteType = EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_NAIL][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_NAIL][2].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_3];
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_NAIL][2].LinkCount			= 4;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_NAIL][3].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_NAIL][3].EffectSpriteType = EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_4;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_NAIL][3].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_NAIL][3].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_4];
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_NAIL][3].LinkCount			= 4;


	// MAGIC_BLOODY_KNIFE,			// Bloody Knife
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_KNIFE].Set("RESULT_MAGIC_BLOODY_KNIFE", ACTION_DAMAGED, EFFECTSPRITETYPE_BLOOD_GUN_3_1, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_KNIFE].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_KNIFE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_KNIFE].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_KNIFE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_KNIFE][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_KNIFE_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_KNIFE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_KNIFE][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_KNIFE_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_KNIFE][0].SoundID				= SOUND_VAMPIRE_MISC_D;	
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_KNIFE][0].SetResultTime();
	

	// MAGIC_BLOODY_BALL,			// Bloody Ball
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_BALL].Set("RESULT_MAGIC_BLOODY_BALL", ACTION_DAMAGED, EFFECTSPRITETYPE_BLOOD_GUN_3_1, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_BALL].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_BALL].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_BALL].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_BALL][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_BALL][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_KNIFE_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_BALL][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_BALL][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_KNIFE_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_BALL][0].SoundID				= SOUND_VAMPIRE_MISC_D;	
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_BALL][0].SetResultTime();

	// MAGIC_BLOODY_WALL,			// Bloody Wall
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL].Set("RESULT_MAGIC_BLOODY_WALL", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL].SetSoundID( SOUND_VAMPIRE_BLOODYWALL );
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL].Init( 1 );		
	//(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL][0].EffectGeneratorID	= EFFECTGENERATORID_BLOODY_WALL;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
//	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL][0].SoundID				= SOUND_VAMPIRE_MISC_D;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL][0].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL][0].SetResultTime();
	/*
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WALL][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_3];
	*/


	// MAGIC_BLOODY_SPEAR,			// Bloody Spear
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_SPEAR].Set("RESULT_MAGIC_BLOODY_SPEAR", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_SPEAR].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_SPEAR].SetSoundID( SOUNDID_NULL );
	
	

	// MAGIC_HIDE,					// Hide
	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE].Set("RESULT_MAGIC_HIDE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);	
	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE].SetSoundID( SOUNDID_NULL );
	//(*g_pActionInfoTable)[RESULT_MAGIC_HIDE].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE].Init( 2 );
	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_HIDE;
	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_HIDE];
	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE][0].SoundID				= SOUND_VAMPIRE_MISC_H;
	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE][0].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE][1].EffectSpriteType	= EFFECTSPRITETYPE_NEW_HIDE_GROUND;
	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE][1].Count				= FrameSize[EFFECTSPRITETYPE_NEW_HIDE_GROUND];	
//	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE].Init( 3 );		
//	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE][0].EffectSpriteType	= EFFECTSPRITETYPE_HIDE_1;
//	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE][0].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE][0].Count				= FrameSize[EFFECTSPRITETYPE_HIDE_1];
//	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE][0].SoundID				= SOUND_VAMPIRE_MISC_H;
//	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE][1].EffectSpriteType	= EFFECTSPRITETYPE_HIDE_2;
//	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE][1].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE][1].Count				= FrameSize[EFFECTSPRITETYPE_HIDE_2];
//	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE][1].SetDelayNode();
//	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE][2].EffectSpriteType	= EFFECTSPRITETYPE_HIDE_3;
//	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE][2].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_HIDE][2].Count				= FrameSize[EFFECTSPRITETYPE_HIDE_3];

	// MAGIC_UN_BURROW,					// UN_BURROW
	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW].Set("RESULT_MAGIC_UN_BURROW", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);	
	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW].SetSoundID( SOUNDID_NULL );
	//(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW].Init( 2 );
	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_HIDE;
	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_HIDE];
	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW][0].SoundID				= SOUND_VAMPIRE_MISC_H;
	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW][0].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW][1].EffectSpriteType	= EFFECTSPRITETYPE_NEW_HIDE_GROUND;
	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW][1].Count				= FrameSize[EFFECTSPRITETYPE_NEW_HIDE_GROUND];
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW].Init( 3 );		
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW][0].EffectSpriteType	= EFFECTSPRITETYPE_HIDE_1;
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW][0].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW][0].Count				= FrameSize[EFFECTSPRITETYPE_HIDE_1];
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW][0].SoundID				= SOUND_VAMPIRE_MISC_H;
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW][1].EffectSpriteType	= EFFECTSPRITETYPE_HIDE_2;
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW][1].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW][1].Count				= FrameSize[EFFECTSPRITETYPE_HIDE_2];
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW][1].SetDelayNode();
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW][2].EffectSpriteType	= EFFECTSPRITETYPE_HIDE_3;
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW][2].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_BURROW][2].Count				= FrameSize[EFFECTSPRITETYPE_HIDE_3];

	// MAGIC_UN_TRANSFORM,					// UN_TRANSFORM
	(*g_pActionInfoTable)[RESULT_MAGIC_UN_TRANSFORM].Set("RESULT_MAGIC_UN_TRANSFORM", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);	
	(*g_pActionInfoTable)[RESULT_MAGIC_UN_TRANSFORM].SetSoundID( SOUNDID_NULL );
	//(*g_pActionInfoTable)[RESULT_MAGIC_UN_TRANSFORM].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_UN_TRANSFORM].Init( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_UN_TRANSFORM][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_UN_TRANSFORM][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_HIDE;
	(*g_pActionInfoTable)[RESULT_MAGIC_UN_TRANSFORM][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_UN_TRANSFORM][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_HIDE];
	(*g_pActionInfoTable)[RESULT_MAGIC_UN_TRANSFORM][0].SoundID				= SOUND_VAMPIRE_TRANSFORM;
	
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_TRANSFORM].Init( 3 );		
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_TRANSFORM][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_TRANSFORM][0].EffectSpriteType	= EFFECTSPRITETYPE_HIDE_1;
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_TRANSFORM][0].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_TRANSFORM][0].Count				= FrameSize[EFFECTSPRITETYPE_HIDE_1];
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_TRANSFORM][0].SoundID				= SOUND_VAMPIRE_TRANSFORM;
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_TRANSFORM][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_TRANSFORM][1].EffectSpriteType	= EFFECTSPRITETYPE_HIDE_2;
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_TRANSFORM][1].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_TRANSFORM][1].Count				= FrameSize[EFFECTSPRITETYPE_HIDE_2];
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_TRANSFORM][1].SetDelayNode();
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_TRANSFORM][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_TRANSFORM][2].EffectSpriteType	= EFFECTSPRITETYPE_HIDE_3;
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_TRANSFORM][2].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_UN_TRANSFORM][2].Count				= FrameSize[EFFECTSPRITETYPE_HIDE_3];

	// RESULT_MAGIC_UN_INVISIBILITY,			// Invisibility
	(*g_pActionInfoTable)[RESULT_MAGIC_UN_INVISIBILITY].Set("RESULT_MAGIC_UN_INVISIBILITY", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);	
	(*g_pActionInfoTable)[RESULT_MAGIC_UN_INVISIBILITY].SetSoundID( SOUNDID_NULL );

	// MAGIC_INVISIBILITY,			// Invisibility
	(*g_pActionInfoTable)[RESULT_MAGIC_INVISIBILITY].Set("RESULT_MAGIC_INVISIBILITY", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);	
	(*g_pActionInfoTable)[RESULT_MAGIC_INVISIBILITY].SetSoundID( SOUNDID_NULL );
	
	// MAGIC_SUMMON_CASKET,				// Summon
	(*g_pActionInfoTable)[RESULT_MAGIC_SUMMON_CASKET].Set("RESULT_MAGIC_SUMMON_CASKET", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);	
	(*g_pActionInfoTable)[RESULT_MAGIC_SUMMON_CASKET].SetSoundID( SOUNDID_NULL );

	// MAGIC_SUMMON_CASKET,				// Summon
	(*g_pActionInfoTable)[RESULT_MAGIC_OPEN_CASKET].Set("RESULT_MAGIC_OPEN_CASKET", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);	
	(*g_pActionInfoTable)[RESULT_MAGIC_OPEN_CASKET].SetSoundID( SOUNDID_NULL );

	// MAGIC_SUMMON_WOLF,				// Summon
	(*g_pActionInfoTable)[RESULT_MAGIC_SUMMON_WOLF].Set("RESULT_MAGIC_SUMMON_WOLF", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_ZONE);	
	(*g_pActionInfoTable)[RESULT_MAGIC_SUMMON_WOLF].SetSoundID( SOUNDID_NULL );

	// MAGIC_SUMMON_SERVANT,				// Summon
	(*g_pActionInfoTable)[RESULT_MAGIC_SUMMON_SERVANT].Set("RESULT_MAGIC_SUMMON_SERVANT", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_ZONE);	
	(*g_pActionInfoTable)[RESULT_MAGIC_SUMMON_SERVANT].SetSoundID( SOUNDID_NULL );

	// MAGIC_RAISING_DEAD,				// Summon
	(*g_pActionInfoTable)[RESULT_MAGIC_RAISING_DEAD].Set("RESULT_MAGIC_RAISING_DEAD", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_ZONE);	
	(*g_pActionInfoTable)[RESULT_MAGIC_RAISING_DEAD].SetSoundID( SOUNDID_NULL );

	// MAGIC_AURA_PRISM,							//	Aura Prism				 106
	/*
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_PRISM].Set("RESULT_MAGIC_AURA_PRISM", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_PRISM].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_PRISM].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_PRISM].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_PRISM].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_PRISM][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE_GROUND;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_PRISM][0].EffectSpriteType	= EFFECTSPRITETYPE_AURA_PRISM_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_PRISM][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_PRISM][0].Count				= FrameSize[EFFECTSPRITETYPE_AURA_PRISM_3];
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_PRISM][0].SoundID				= SOUND_VAMPIRE_MISC_D;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_PRISM][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE_GROUND;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_PRISM][1].EffectSpriteType	= EFFECTSPRITETYPE_AURA_PRISM_4;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_PRISM][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_PRISM][1].Count				= FrameSize[EFFECTSPRITETYPE_AURA_PRISM_4];
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_PRISM][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_PRISM][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE_GROUND;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_PRISM][2].EffectSpriteType	= EFFECTSPRITETYPE_AURA_PRISM_5;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_PRISM][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_PRISM][2].Count				= FrameSize[EFFECTSPRITETYPE_AURA_PRISM_5];
	*/

	// MAGIC_CHAIN_AURA,							//	Chain Aura 				 107
	(*g_pActionInfoTable)[RESULT_MAGIC_CHAIN_AURA].Set("RESULT_MAGIC_CHAIN_AURA", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_MAGIC_CHAIN_AURA].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_MAGIC_CHAIN_AURA].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_CHAIN_AURA].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_MAGIC_CHAIN_AURA].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_CHAIN_AURA][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_RECT;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHAIN_AURA][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHAIN_AURA][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHAIN_AURA][0].Count				= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[RESULT_MAGIC_CHAIN_AURA][0].SoundID				= SOUND_VAMPIRE_MISC_D;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHAIN_AURA][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHAIN_AURA][1].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHAIN_AURA][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHAIN_AURA][1].Count				= FrameSize[EFFECTSPRITETYPE_DARKNESS_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_CHAIN_AURA][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_CHAIN_AURA][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHAIN_AURA][2].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHAIN_AURA][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHAIN_AURA][2].Count				= FrameSize[EFFECTSPRITETYPE_DARKNESS_3];

	// MAGIC_CHRIST_AURA,							//	Christ Aura 			 108
	/*
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA].Set("RESULT_MAGIC_CHRIST_AURA", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA].Init( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][0].EffectSpriteType	= EFFECTSPRITETYPE_BLESS;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][0].Count				= FrameSize[EFFECTSPRITETYPE_BLESS];
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][0].SoundID			= SOUND_SLAYER_ENCHANT_B1;
	*/
	/*
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;	// 반복
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][1].EffectSpriteType	= EFFECTSPRITETYPE_BLESS_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][1].Count				= FrameSize[EFFECTSPRITETYPE_BLESS_2];
	//(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][2].EffectSpriteType	= EFFECTSPRITETYPE_BLESS_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][2].Count				= FrameSize[EFFECTSPRITETYPE_BLESS_3];
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][3].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][3].EffectSpriteType	= EFFECTSPRITETYPE_BLESS_4;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][3].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][3].Count				= FrameSize[EFFECTSPRITETYPE_BLESS_4];
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][4].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;		// 바닥..
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][4].EffectSpriteType	= EFFECTSPRITETYPE_BLESS_5;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][4].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][4].SoundID			= SOUND_SLAYER_ENCHANT_B2;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][4].Count				= FrameSize[EFFECTSPRITETYPE_BLESS_5];
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][5].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;		// 솟아오름
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][5].EffectSpriteType	= EFFECTSPRITETYPE_BLESS_6;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][5].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][5].Count				= FrameSize[EFFECTSPRITETYPE_BLESS_6];
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][6].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;		// - -;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][6].EffectSpriteType	= EFFECTSPRITETYPE_BLESS_7;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][6].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CHRIST_AURA][6].Count				= FrameSize[EFFECTSPRITETYPE_BLESS_7];
*/
	// MAGIC_DOOM,			// Curse
	(*g_pActionInfoTable)[RESULT_MAGIC_DOOM].Set("RESULT_MAGIC_DOOM", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_DOOM].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_DOOM].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_MAGIC_DOOM].Init( 3 );
	(*g_pActionInfoTable)[RESULT_MAGIC_DOOM].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_DOOM][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_DOOM][0].EffectSpriteType	= EFFECTSPRITETYPE_CURSE_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_DOOM][0].Step				= 12;
	(*g_pActionInfoTable)[RESULT_MAGIC_DOOM][0].Count				= FrameSize[EFFECTSPRITETYPE_CURSE_1];
	//(*g_pActionInfoTable)[RESULT_MAGIC_DOOM][0].SoundID				= SOUND_VAMPIRE_MISC_BD;
	(*g_pActionInfoTable)[RESULT_MAGIC_DOOM][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_DOOM][1].EffectSpriteType	= EFFECTSPRITETYPE_CURSE_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_DOOM][1].Step				= 10;
	(*g_pActionInfoTable)[RESULT_MAGIC_DOOM][1].Count				= 2 * FrameSize[EFFECTSPRITETYPE_CURSE_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_DOOM][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_DOOM][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_DOOM][2].EffectSpriteType	= EFFECTSPRITETYPE_CURSE_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_DOOM][2].Step				= 6;
	(*g_pActionInfoTable)[RESULT_MAGIC_DOOM][2].Count				= FrameSize[EFFECTSPRITETYPE_CURSE_3];

#if __CONTENTS(__FAST_TRANSFORTER)
	(*g_pActionInfoTable)[SKILL_CLIENT_FLITTERMOUSE].Set("SKILL_CLIENT_FLITTERMOUSE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[SKILL_CLIENT_FLITTERMOUSE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_FLITTERMOUSE].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_FLITTERMOUSE][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_FLITTERMOUSE][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_HIDE;
	(*g_pActionInfoTable)[SKILL_CLIENT_FLITTERMOUSE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_FLITTERMOUSE][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_HIDE];
	(*g_pActionInfoTable)[SKILL_CLIENT_FLITTERMOUSE][0].SoundID				= SOUND_VAMPIRE_TRANSFORM;
#endif //__FAST_TRANSFORTER

#if __CONTENTS(__SECOND_TRANSFORTER)
	(*g_pActionInfoTable)[SKILL_CLIENT_SHAPE_OF_DEMON].Set("SKILL_CLIENT_SHAPE_OF_DEMON", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[SKILL_CLIENT_SHAPE_OF_DEMON].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_SHAPE_OF_DEMON].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_SHAPE_OF_DEMON][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_SHAPE_OF_DEMON][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_HIDE;
	(*g_pActionInfoTable)[SKILL_CLIENT_SHAPE_OF_DEMON][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_SHAPE_OF_DEMON][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_HIDE];
	(*g_pActionInfoTable)[SKILL_CLIENT_SHAPE_OF_DEMON][0].SoundID				= SOUND_VAMPIRE_TRANSFORM;
#endif //__SECOND_TRANSFORTER

	// MAGIC_TRANSFORM_TO_BAT,						//	Transform To Bat 		 110
	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_BAT].Set("RESULT_MAGIC_TRANSFORM_TO_BAT", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);	
	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_BAT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_BAT].Init( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_BAT][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_BAT][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_HIDE;
	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_BAT][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_BAT][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_HIDE];
	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_BAT][0].SoundID				= SOUND_VAMPIRE_TRANSFORM;
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_BAT].Init( 3 );		
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_BAT][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_BAT][0].EffectSpriteType	= EFFECTSPRITETYPE_HIDE_1;
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_BAT][0].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_BAT][0].Count				= FrameSize[EFFECTSPRITETYPE_HIDE_1];
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_BAT][0].SoundID				= SOUND_VAMPIRE_TRANSFORM;
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_BAT][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_BAT][1].EffectSpriteType	= EFFECTSPRITETYPE_HIDE_2;
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_BAT][1].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_BAT][1].Count				= FrameSize[EFFECTSPRITETYPE_HIDE_2];
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_BAT][1].SetDelayNode();
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_BAT][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_BAT][2].EffectSpriteType	= EFFECTSPRITETYPE_HIDE_3;
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_BAT][2].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_BAT][2].Count				= FrameSize[EFFECTSPRITETYPE_HIDE_3];

	// MAGIC_TRANSFORM_TO_WOLF,					//	Transform To Wolf		 111
	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_WOLF].Set("RESULT_MAGIC_TRANSFORM_TO_WOLF", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);	
	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_WOLF].SetSoundID( SOUNDID_NULL );
	//(*g_pActionInfoTable)[RESULT_MAGIC_HIDE].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_WOLF].Init( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_WOLF][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_WOLF][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_HIDE;
	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_WOLF][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_WOLF][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_HIDE];
	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_WOLF][0].SoundID				= SOUND_VAMPIRE_TRANSFORM;
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_WOLF].Init( 3 );		
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_WOLF][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_WOLF][0].EffectSpriteType	= EFFECTSPRITETYPE_HIDE_1;
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_WOLF][0].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_WOLF][0].Count				= FrameSize[EFFECTSPRITETYPE_HIDE_1];
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_WOLF][0].SoundID				= SOUND_VAMPIRE_TRANSFORM;
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_WOLF][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_WOLF][1].EffectSpriteType	= EFFECTSPRITETYPE_HIDE_2;
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_WOLF][1].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_WOLF][1].Count				= FrameSize[EFFECTSPRITETYPE_HIDE_2];
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_WOLF][1].SetDelayNode();
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_WOLF][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_WOLF][2].EffectSpriteType	= EFFECTSPRITETYPE_HIDE_3;
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_WOLF][2].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_TRANSFORM_TO_WOLF][2].Count				= FrameSize[EFFECTSPRITETYPE_HIDE_3];
//
	//-------------------------------------------------------------
	// 늑대 기술
	//-------------------------------------------------------------
	// MAGIC_EAT_CORPSE
	(*g_pActionInfoTable)[RESULT_MAGIC_EAT_CORPSE].Set("RESULT_MAGIC_EAT_CORPSE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[RESULT_MAGIC_EAT_CORPSE].SetSoundID( SOUNDID_NULL );

	// MAGIC_HOWL
	(*g_pActionInfoTable)[RESULT_MAGIC_HOWL].Set("RESULT_MAGIC_HOWL", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_HOWL].SetSoundID( SOUND_WOLF_HOWL );

	// MAGIC_SEDUCTION
	(*g_pActionInfoTable)[MAGIC_SEDUCTION].Set("MAGIC_SEDUCTION", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_SEDUCTION].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_SEDUCTION].SetSoundID( SOUNDID_NULL );	

	// MAGIC_SEDUCTION	
	(*g_pActionInfoTable)[RESULT_MAGIC_SEDUCTION].Set("RESULT_MAGIC_SEDUCTION", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_SEDUCTION].SetSoundID( SOUND_VAMPIRE_SEDUCTION );
	(*g_pActionInfoTable)[RESULT_MAGIC_SEDUCTION].Init( 2 );		
	(*g_pActionInfoTable)[RESULT_MAGIC_SEDUCTION].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_SEDUCTION][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_SEDUCTION][0].EffectSpriteType	= EFFECTSPRITETYPE_CURSE_WEAKNESS_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_SEDUCTION][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_SEDUCTION][0].Count				= FrameSize[EFFECTSPRITETYPE_CURSE_WEAKNESS_1];
	(*g_pActionInfoTable)[RESULT_MAGIC_SEDUCTION][0].SoundID				= SOUND_VAMPIRE_POISON_PW;
	(*g_pActionInfoTable)[RESULT_MAGIC_SEDUCTION][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_SEDUCTION][1].EffectSpriteType	= EFFECTSPRITETYPE_CURSE_WEAKNESS_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_SEDUCTION][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_SEDUCTION][1].Count				= FrameSize[EFFECTSPRITETYPE_CURSE_WEAKNESS_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_SEDUCTION][1].SetDelayNode();

	(*g_pActionInfoTable)[HOLY_LAND_WARP_VAMPIRE].Set("HOLY_LAND_WARP_VAMPIRE",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[HOLY_LAND_WARP_VAMPIRE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[HOLY_LAND_WARP_VAMPIRE].Init( 1 );
	(*g_pActionInfoTable)[HOLY_LAND_WARP_VAMPIRE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[HOLY_LAND_WARP_VAMPIRE][0].EffectSpriteType = EFFECTSPRITETYPE_WARP_HOLY_LAND_VAMPIRE_START;
	(*g_pActionInfoTable)[HOLY_LAND_WARP_VAMPIRE][0].Step						= 30;
	(*g_pActionInfoTable)[HOLY_LAND_WARP_VAMPIRE][0].Count					= FrameSize[EFFECTSPRITETYPE_WARP_HOLY_LAND_VAMPIRE_START];
//	(*g_pActionInfoTable)[HOLY_LAND_WARP_VAMPIRE][0].SetDelayNode();
	
	// RESULT_VAMPIRE_DIE
	(*g_pActionInfoTable)[RESULT_VAMPIRE_DIE].Set("RESULT_VAMPIRE_DIE", ACTION_DIE, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 500);
	(*g_pActionInfoTable)[RESULT_VAMPIRE_DIE].SetStartFrameAll( 10 );	
	(*g_pActionInfoTable)[RESULT_VAMPIRE_DIE].SetCastingStartFrameAll( 8 );
	(*g_pActionInfoTable)[RESULT_VAMPIRE_DIE].SetCastingFramesAll( 16 );
	(*g_pActionInfoTable)[RESULT_VAMPIRE_DIE].Init( 1 );	
	(*g_pActionInfoTable)[RESULT_VAMPIRE_DIE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_VAMPIRE_DIE][0].EffectSpriteType	= EFFECTSPRITETYPE_VAMPIRE_DEATH;
	(*g_pActionInfoTable)[RESULT_VAMPIRE_DIE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_VAMPIRE_DIE][0].Count				= FrameSize[EFFECTSPRITETYPE_VAMPIRE_DEATH];
	
	// RESULT_MASTER_DIE
	(*g_pActionInfoTable)[RESULT_MASTER_DIE].Set("RESULT_MASTER_DIE", ACTION_DIE, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 500);
	//(*g_pActionInfoTable)[RESULT_MASTER_DIE].SetStartFrameAll( 10 );	
	(*g_pActionInfoTable)[RESULT_MASTER_DIE].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_MASTER_DIE].Init( 3 );	
	(*g_pActionInfoTable)[RESULT_MASTER_DIE][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MASTER_DIE][0].EffectSpriteType	= EFFECTSPRITETYPE_MASTER_DIE_FIRE;
	(*g_pActionInfoTable)[RESULT_MASTER_DIE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MASTER_DIE][0].Count				= FrameSize[EFFECTSPRITETYPE_MASTER_DIE_FIRE];
	(*g_pActionInfoTable)[RESULT_MASTER_DIE][0].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_MASTER_DIE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_MASTER_DIE][1].EffectSpriteType	= EFFECTSPRITETYPE_MASTER_DIE_ROCK_BACK;
	(*g_pActionInfoTable)[RESULT_MASTER_DIE][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MASTER_DIE][1].Count				= FrameSize[EFFECTSPRITETYPE_MASTER_DIE_ROCK_BACK];
	(*g_pActionInfoTable)[RESULT_MASTER_DIE][1].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_MASTER_DIE][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MASTER_DIE][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MASTER_DIE][2].EffectSpriteType	= EFFECTSPRITETYPE_MASTER_DIE_ROCK_FRONT;
	(*g_pActionInfoTable)[RESULT_MASTER_DIE][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MASTER_DIE][2].Count				= FrameSize[EFFECTSPRITETYPE_MASTER_DIE_ROCK_FRONT];
	(*g_pActionInfoTable)[RESULT_MASTER_DIE][2].SetDelayNode();

	
	// RESULT_VAMPIRE_DIE_NO_EFFECT
	(*g_pActionInfoTable)[RESULT_VAMPIRE_DIE_NO_EFFECT].Set("RESULT_VAMPIRE_DIE_NO_EFFECT", ACTION_DIE, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 500);
	//(*g_pActionInfoTable)[RESULT_VAMPIRE_DIE_NO_EFFECT].SetStartFrameAll( 10 );	
	
	// MAGIC_BLOODY_MARK,			// Bloody Nail
	(*g_pActionInfoTable)[MAGIC_BLOODY_MARK].Set("MAGIC_BLOODY_MARK", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_ITEM, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);	
	(*g_pActionInfoTable)[MAGIC_BLOODY_MARK].SetStartFrameAll( 6 );
	(*g_pActionInfoTable)[MAGIC_BLOODY_MARK].SetSoundID( SOUNDID_NULL );		

	// MAGIC_BLOODY_MARK,				// Summon
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_MARK].Set("RESULT_MAGIC_BLOODY_MARK", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_ITEM);
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_MARK].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_MARK].Init( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_MARK][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_INVENTORY;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_MARK][0].EffectSpriteType	= EFFECTSPRITETYPE_VAMPIRE_PORTAL_ITEM;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_MARK][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_MARK][0].Count				= FrameSize[EFFECTSPRITETYPE_VAMPIRE_PORTAL_ITEM];
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_MARK][0].SoundID				= SOUND_SLAYER_ENCHANT_CHW1;

	// MAGIC_BLOODY_TUNNEL,			// Bloody Nail
	(*g_pActionInfoTable)[MAGIC_BLOODY_TUNNEL].Set("MAGIC_BLOODY_TUNNEL", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_ITEM, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);	
	(*g_pActionInfoTable)[MAGIC_BLOODY_TUNNEL].SetStartFrameAll( 6 );
	(*g_pActionInfoTable)[MAGIC_BLOODY_TUNNEL].SetSoundID( SOUNDID_NULL );	

	
	// MAGIC_BLOODY_TUNNEL,			// Bloody Nail
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL].Set("RESULT_MAGIC_BLOODY_TUNNEL", ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_STAND]);
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE_SELECTABLE;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_TUNNEL_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_TUNNEL_1];
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE_SELECTABLE;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_TUNNEL_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_TUNNEL_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE_SELECTABLE;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_TUNNEL_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_TUNNEL_3];
	

	// MAGIC_BLOODY_TUNNEL,			// Bloody Nail
	(*g_pActionInfoTable)[MAGIC_BLOODY_TUNNEL_INTO].Set("MAGIC_BLOODY_TUNNEL_INTO", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_ITEM, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);	
	(*g_pActionInfoTable)[MAGIC_BLOODY_TUNNEL_INTO].SetStartFrameAll( 6 );
	(*g_pActionInfoTable)[MAGIC_BLOODY_TUNNEL_INTO].SetSoundID( SOUNDID_NULL );	

	// MAGIC_BLOODY_TUNNEL,			// Bloody Nail
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL_INTO].Set("RESULT_MAGIC_BLOODY_TUNNEL_INTO", ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL_INTO].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL_INTO].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL_INTO].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL_INTO][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL_INTO][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_TUNNEL_4;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL_INTO][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_TUNNEL_INTO][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_TUNNEL_4];
	// SKILL_POISON_STRIKE

	(*g_pActionInfoTable)[SKILL_POISON_STRIKE].Set("SKILL_POISON_STRIKE", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_GREEN_STALKER_1, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_POISON_STRIKE].SetCastingFramesAll( 16 );
	(*g_pActionInfoTable)[SKILL_POISON_STRIKE].SetStartFrameAll( 16 );
	(*g_pActionInfoTable)[SKILL_POISON_STRIKE].SetSoundID( SOUND_VAMPIRE_GREENSTALKER1 );
	(*g_pActionInfoTable)[SKILL_POISON_STRIKE].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_POISON_STRIKE][0].EffectGeneratorID	= EFFECTGENERATORID_SPREAD_OUT;
	(*g_pActionInfoTable)[SKILL_POISON_STRIKE][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_FLY_GREEN_STALKER;//EFFECTSPRITETYPE_GREEN_STALKER_2;
	(*g_pActionInfoTable)[SKILL_POISON_STRIKE][0].Step				= 15;
	(*g_pActionInfoTable)[SKILL_POISON_STRIKE][0].Count				= 10;//FrameSize[EFFECTSPRITETYPE_ACID_BOLT_1];
	(*g_pActionInfoTable)[SKILL_POISON_STRIKE][0].SoundID			= SOUND_VAMPIRE_GREENSTALKER2;
	(*g_pActionInfoTable)[SKILL_POISON_STRIKE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[SKILL_POISON_STRIKE][1].EffectSpriteType	= EFFECTSPRITETYPE_NEW_FLY_GREEN_STALKER;//EFFECTSPRITETYPE_GREEN_STALKER_2;
	(*g_pActionInfoTable)[SKILL_POISON_STRIKE][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_POISON_STRIKE][1].Count				= 2*16;//FrameSize[EFFECTSPRITETYPE_ACID_BOLT_1];	

	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STRIKE].Set("RESULT_SKILL_POISON_STRIKE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STRIKE].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STRIKE].Init( 3 );
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STRIKE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STRIKE][0].EffectSpriteType	= EFFECTSPRITETYPE_GREEN_STALKER_3;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STRIKE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STRIKE][0].Count				= FrameSize[EFFECTSPRITETYPE_GREEN_STALKER_3];
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STRIKE][0].SoundID			= SOUND_VAMPIRE_ACIDBURN;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STRIKE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STRIKE][1].EffectSpriteType	= EFFECTSPRITETYPE_GREEN_STALKER_4;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STRIKE][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STRIKE][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STRIKE][1].SetResultTime();
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STRIKE][1].Count				= FrameSize[EFFECTSPRITETYPE_GREEN_STALKER_4];
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STRIKE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STRIKE][2].EffectSpriteType	= EFFECTSPRITETYPE_GREEN_STALKER_5;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STRIKE][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STRIKE][2].Count				= FrameSize[EFFECTSPRITETYPE_GREEN_STALKER_5];
	

	// SKILL_POISON_STORM
	(*g_pActionInfoTable)[SKILL_POISON_STORM].Set("SKILL_POISON_STORM", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_GREEN_STALKER_1, 8, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET | FLAG_ACTIONINFO_START_SKY, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_POISON_STORM].SetCastingFramesAll( 16 );
	(*g_pActionInfoTable)[SKILL_POISON_STORM].SetStartFrameAll( 6 );
	(*g_pActionInfoTable)[SKILL_POISON_STORM].SetSoundID( SOUND_VAMPIRE_GREENSTALKER1 );
	(*g_pActionInfoTable)[SKILL_POISON_STORM].Init( 2 );
	(*g_pActionInfoTable)[SKILL_POISON_STORM][0].EffectGeneratorID	= EFFECTGENERATORID_MULTIPLE_FALLING;
	(*g_pActionInfoTable)[SKILL_POISON_STORM][0].EffectSpriteType	= EFFECTSPRITETYPE_ACID_BOLT_1;
	(*g_pActionInfoTable)[SKILL_POISON_STORM][0].Step				= 30;
	(*g_pActionInfoTable)[SKILL_POISON_STORM][0].Count				= 17;//FrameSize[EFFECTSPRITETYPE_ACID_BOLT_1];
	(*g_pActionInfoTable)[SKILL_POISON_STORM][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_POISON_STORM][1].EffectSpriteType	= EFFECTSPRITETYPE_SMOKE;
	(*g_pActionInfoTable)[SKILL_POISON_STORM][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_POISON_STORM][1].Count				= FrameSize[EFFECTSPRITETYPE_SMOKE];
	(*g_pActionInfoTable)[SKILL_POISON_STORM][1].SoundID			= SOUND_VAMPIRE_ACIDBURN;
	(*g_pActionInfoTable)[SKILL_POISON_STORM].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_POISON_STORM );	// 맞는 결과를 표현한다.	
	(*g_pActionInfoTable)[SKILL_POISON_STORM].SetSkillFailDelay(); // 스킬실패해도 딜레이는 남아 있다..

	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM].Set("RESULT_SKILL_POISON_STORM", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM].Init( 2 );
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM][0].EffectSpriteType	= EFFECTSPRITETYPE_ACID_BOLT_2;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM][0].Count				= FrameSize[EFFECTSPRITETYPE_ACID_BOLT_2];
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM][0].SoundID			= SOUND_VAMPIRE_ACID_ABOLT2;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM][0].LinkCount			= 1;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM][1].EffectSpriteType	= EFFECTSPRITETYPE_SMOKE;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM][1].Count				= FrameSize[EFFECTSPRITETYPE_SMOKE];
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM][1].SoundID			= SOUND_VAMPIRE_ACIDBURN;

	// SKILL_POISON_STORM_WIDE
	(*g_pActionInfoTable)[SKILL_POISON_STORM_WIDE].Set("SKILL_POISON_STORM_WIDE", ACTION_MAGIC, EFFECTSPRITETYPE_GREEN_STALKER_1, 8, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET | FLAG_ACTIONINFO_START_SKY, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_POISON_STORM_WIDE].SetCastingFramesAll( 16 );
	(*g_pActionInfoTable)[SKILL_POISON_STORM_WIDE].SetStartFrameAll( 6 );
	(*g_pActionInfoTable)[SKILL_POISON_STORM_WIDE].SetSoundID( SOUND_VAMPIRE_GREENSTALKER1 );
	(*g_pActionInfoTable)[SKILL_POISON_STORM_WIDE].Init( 2 );
	(*g_pActionInfoTable)[SKILL_POISON_STORM_WIDE][0].EffectGeneratorID	= EFFECTGENERATORID_MULTIPLE_FALLING;
	(*g_pActionInfoTable)[SKILL_POISON_STORM_WIDE][0].EffectSpriteType	= EFFECTSPRITETYPE_ACID_BOLT_1;
	(*g_pActionInfoTable)[SKILL_POISON_STORM_WIDE][0].Step				= 30;
	(*g_pActionInfoTable)[SKILL_POISON_STORM_WIDE][0].Count				= 17;//FrameSize[EFFECTSPRITETYPE_ACID_BOLT_1];
	(*g_pActionInfoTable)[SKILL_POISON_STORM_WIDE][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_POISON_STORM_WIDE][1].EffectSpriteType	= EFFECTSPRITETYPE_SMOKE;
	(*g_pActionInfoTable)[SKILL_POISON_STORM_WIDE][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_POISON_STORM_WIDE][1].Count				= FrameSize[EFFECTSPRITETYPE_SMOKE];
	(*g_pActionInfoTable)[SKILL_POISON_STORM_WIDE][1].SoundID			= SOUND_VAMPIRE_ACIDBURN;
	(*g_pActionInfoTable)[SKILL_POISON_STORM_WIDE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_POISON_STORM_WIDE );	// 맞는 결과를 표현한다.	

	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM_WIDE].Set("RESULT_SKILL_POISON_STORM_WIDE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM_WIDE].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM_WIDE].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM_WIDE].Init( 2 );
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM_WIDE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM_WIDE][0].EffectSpriteType	= EFFECTSPRITETYPE_ACID_BOLT_2;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM_WIDE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM_WIDE][0].Count				= FrameSize[EFFECTSPRITETYPE_ACID_BOLT_2];
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM_WIDE][0].SoundID			= SOUND_VAMPIRE_ACID_ABOLT2;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM_WIDE][0].LinkCount			= 1;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM_WIDE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM_WIDE][1].EffectSpriteType	= EFFECTSPRITETYPE_SMOKE;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM_WIDE][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM_WIDE][1].Count				= FrameSize[EFFECTSPRITETYPE_SMOKE];
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_STORM_WIDE][1].SoundID			= SOUND_VAMPIRE_ACIDBURN;

	// SKILL_ACID_STRIKE
	(*g_pActionInfoTable)[SKILL_ACID_STRIKE].Set("SKILL_ACID_STRIKE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_ACID_STRIKE].SetCastingFramesAll( 16 );
	(*g_pActionInfoTable)[SKILL_ACID_STRIKE].SetStartFrameAll( 16 );
	(*g_pActionInfoTable)[SKILL_ACID_STRIKE].SetSoundID( SOUND_VAMPIRE_GREENSTALKER1 );
	(*g_pActionInfoTable)[SKILL_ACID_STRIKE].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_ACID_STRIKE][0].EffectGeneratorID	= EFFECTGENERATORID_SPREAD_OUT;
	(*g_pActionInfoTable)[SKILL_ACID_STRIKE][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_ACID_BOLT_1;//EFFECTSPRITETYPE_ACID_BOLT_1;
	(*g_pActionInfoTable)[SKILL_ACID_STRIKE][0].Step				= 15;
	(*g_pActionInfoTable)[SKILL_ACID_STRIKE][0].Count				= 10;//FrameSize[EFFECTSPRITETYPE_ACID_BOLT_1];
	(*g_pActionInfoTable)[SKILL_ACID_STRIKE][0].SoundID			= SOUND_VAMPIRE_GREENSTALKER2;
	(*g_pActionInfoTable)[SKILL_ACID_STRIKE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[SKILL_ACID_STRIKE][1].EffectSpriteType	= EFFECTSPRITETYPE_NEW_ACID_BOLT_1;
	(*g_pActionInfoTable)[SKILL_ACID_STRIKE][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_ACID_STRIKE][1].Count				= 2*16;//FrameSize[EFFECTSPRITETYPE_ACID_BOLT_1];	

	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STRIKE].Set("RESULT_SKILL_ACID_STRIKE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STRIKE].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STRIKE].Init( 4 );		
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STRIKE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STRIKE][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_ACID_BOLT_2;//EFFECTSPRITETYPE_ACID_BOLT_2;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STRIKE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STRIKE][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_ACID_BOLT_2];
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STRIKE][0].SoundID				= SOUND_VAMPIRE_ACID_ABOLT2;	
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STRIKE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STRIKE][1].EffectSpriteType	= EFFECTSPRITETYPE_NEW_ACID_BOLT_2;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STRIKE][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STRIKE][1].Count				= FrameSize[EFFECTSPRITETYPE_NEW_ACID_BOLT_2];
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STRIKE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STRIKE][2].EffectSpriteType	= EFFECTSPRITETYPE_NEW_ACID_BOLT_2;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STRIKE][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STRIKE][2].Count				= FrameSize[EFFECTSPRITETYPE_NEW_ACID_BOLT_2];
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STRIKE][2].LinkCount			= 1;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STRIKE][3].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STRIKE][3].EffectSpriteType	= EFFECTSPRITETYPE_SMOKE;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STRIKE][3].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STRIKE][3].Count				= FrameSize[EFFECTSPRITETYPE_SMOKE];
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STRIKE][3].SoundID			= SOUND_VAMPIRE_ACIDBURN;	


	// SKILL_ACID_STORM
	(*g_pActionInfoTable)[SKILL_ACID_STORM].Set("SKILL_ACID_STORM", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET | FLAG_ACTIONINFO_START_SKY, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_ACID_STORM].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_ACID_STORM].SetStartFrameAll( 5 );
	(*g_pActionInfoTable)[SKILL_ACID_STORM].Init( 2 );
	(*g_pActionInfoTable)[SKILL_ACID_STORM][0].EffectGeneratorID	= EFFECTGENERATORID_MULTIPLE_FALLING;
	(*g_pActionInfoTable)[SKILL_ACID_STORM][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_ACID_BOLT_1;//EFFECTSPRITETYPE_ACID_BALL_1;
	(*g_pActionInfoTable)[SKILL_ACID_STORM][0].Step				= 30;
	(*g_pActionInfoTable)[SKILL_ACID_STORM][0].Count				= 17;//FrameSize[EFFECTSPRITETYPE_AURA_BALL_2];
	(*g_pActionInfoTable)[SKILL_ACID_STORM][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_ACID_STORM][1].EffectSpriteType	= EFFECTSPRITETYPE_SMOKE;
	(*g_pActionInfoTable)[SKILL_ACID_STORM][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_ACID_STORM][1].Count				= FrameSize[EFFECTSPRITETYPE_SMOKE];
	(*g_pActionInfoTable)[SKILL_ACID_STORM][1].SoundID			= SOUND_VAMPIRE_ACIDBURN;
	(*g_pActionInfoTable)[SKILL_ACID_STORM].SetSkillFailDelay(); // 스킬실패해도 딜레이는 남아 있다..
	/*
	(*g_pActionInfoTable)[SKILL_ACID_STORM][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_ACID_STORM][1].EffectSpriteType	= EFFECTSPRITETYPE_ACID_BALL_2;
	(*g_pActionInfoTable)[SKILL_ACID_STORM][1].Step				= 30;
	(*g_pActionInfoTable)[SKILL_ACID_STORM][1].Count				= FrameSize[EFFECTSPRITETYPE_ACID_BALL_2];
	(*g_pActionInfoTable)[SKILL_ACID_STORM][1].LinkCount			= 1;
	*/
	/*
	(*g_pActionInfoTable)[SKILL_ACID_STORM][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_ACID_STORM][2].EffectSpriteType	= EFFECTSPRITETYPE_ACID_SWAP_1;
	(*g_pActionInfoTable)[SKILL_ACID_STORM][2].Step				= 15;
	(*g_pActionInfoTable)[SKILL_ACID_STORM][2].Count				= FrameSize[EFFECTSPRITETYPE_ACID_SWAP_1];	
	(*g_pActionInfoTable)[SKILL_ACID_STORM][3].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_ACID_STORM][3].EffectSpriteType	= EFFECTSPRITETYPE_ACID_SWAP_2;
	(*g_pActionInfoTable)[SKILL_ACID_STORM][3].Step				= 15;
	(*g_pActionInfoTable)[SKILL_ACID_STORM][3].Count				= FrameSize[EFFECTSPRITETYPE_ACID_SWAP_2];	
	(*g_pActionInfoTable)[SKILL_ACID_STORM][3].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_ACID_STORM][4].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_ACID_STORM][4].EffectSpriteType	= EFFECTSPRITETYPE_ACID_SWAP_3;
	(*g_pActionInfoTable)[SKILL_ACID_STORM][4].Step				= 15;
	(*g_pActionInfoTable)[SKILL_ACID_STORM][4].Count				= FrameSize[EFFECTSPRITETYPE_ACID_SWAP_3];	
	*/
	(*g_pActionInfoTable)[SKILL_ACID_STORM].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_ACID_STORM );	// 맞는 결과를 표현한다.	

	// SKILL_ACID_STORM_WIDE
	(*g_pActionInfoTable)[SKILL_ACID_STORM_WIDE].Set("SKILL_ACID_STORM_WIDE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET | FLAG_ACTIONINFO_START_SKY, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_ACID_STORM_WIDE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_ACID_STORM_WIDE].SetStartFrameAll( 5 );
	(*g_pActionInfoTable)[SKILL_ACID_STORM_WIDE].Init( 2 );
	(*g_pActionInfoTable)[SKILL_ACID_STORM_WIDE][0].EffectGeneratorID	= EFFECTGENERATORID_MULTIPLE_FALLING;
	(*g_pActionInfoTable)[SKILL_ACID_STORM_WIDE][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_ACID_BOLT_1;
	(*g_pActionInfoTable)[SKILL_ACID_STORM_WIDE][0].Step				= 30;
	(*g_pActionInfoTable)[SKILL_ACID_STORM_WIDE][0].Count				= 17;//FrameSize[EFFECTSPRITETYPE_AURA_BALL_2];
	(*g_pActionInfoTable)[SKILL_ACID_STORM_WIDE][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_ACID_STORM_WIDE][1].EffectSpriteType	= EFFECTSPRITETYPE_SMOKE;
	(*g_pActionInfoTable)[SKILL_ACID_STORM_WIDE][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_ACID_STORM_WIDE][1].Count				= FrameSize[EFFECTSPRITETYPE_SMOKE];
	(*g_pActionInfoTable)[SKILL_ACID_STORM_WIDE][1].SoundID			= SOUND_VAMPIRE_ACIDBURN;
	(*g_pActionInfoTable)[SKILL_ACID_STORM_WIDE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_ACID_STORM_WIDE );	// 맞는 결과를 표현한다.	

	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM].Set("RESULT_SKILL_ACID_STORM", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM].Init( 3 );
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_ACID_BALL_2;//EFFECTSPRITETYPE_ACID_BOLT_2;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM][0].Count				= FrameSize[EFFECTSPRITETYPE_ACID_BOLT_2];
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM][0].SoundID			= SOUND_VAMPIRE_ACID_ABOLT2;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM][0].LinkCount			= 1;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM][1].EffectSpriteType	= EFFECTSPRITETYPE_SMOKE;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM][1].Count				= FrameSize[EFFECTSPRITETYPE_SMOKE];
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM][1].SoundID			= SOUND_VAMPIRE_ACIDBURN;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM][1].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM][2].EffectSpriteType	= EFFECTSPRITETYPE_SMOKE;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM][2].Count				= FrameSize[EFFECTSPRITETYPE_SMOKE];
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM][2].SoundID			= SOUND_VAMPIRE_ACIDBURN;

	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM_WIDE].Set("RESULT_SKILL_ACID_STORM_WIDE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM_WIDE].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM_WIDE].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM_WIDE].Init( 2 );
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM_WIDE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM_WIDE][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_ACID_BOLT_2;//EFFECTSPRITETYPE_ACID_BOLT_2;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM_WIDE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM_WIDE][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_ACID_BOLT_2];
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM_WIDE][0].SoundID			= SOUND_VAMPIRE_ACID_ABOLT2;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM_WIDE][0].LinkCount			= 1;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM_WIDE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM_WIDE][1].EffectSpriteType	= EFFECTSPRITETYPE_SMOKE;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM_WIDE][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM_WIDE][1].Count				= FrameSize[EFFECTSPRITETYPE_SMOKE];
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_STORM_WIDE][1].SoundID			= SOUND_VAMPIRE_ACIDBURN;


	// SKILL_BLOODY_STRIKE
	(*g_pActionInfoTable)[SKILL_BLOODY_STRIKE].Set("SKILL_BLOODY_STRIKE", ACTION_MAGIC, EFFECTSPRITETYPE_BLOOD_DRAIN_2, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_BLOODY_STRIKE].SetCastingFramesAll( 16 );
	(*g_pActionInfoTable)[SKILL_BLOODY_STRIKE].SetStartFrameAll( 16 );
	(*g_pActionInfoTable)[SKILL_BLOODY_STRIKE].SetSoundID( SOUND_VAMPIRE_GREENSTALKER1 );
	(*g_pActionInfoTable)[SKILL_BLOODY_STRIKE].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_BLOODY_STRIKE][0].EffectGeneratorID	= EFFECTGENERATORID_SPREAD_OUT;
	(*g_pActionInfoTable)[SKILL_BLOODY_STRIKE][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_KNIFE_1;
	(*g_pActionInfoTable)[SKILL_BLOODY_STRIKE][0].Step				= 15;
	(*g_pActionInfoTable)[SKILL_BLOODY_STRIKE][0].Count				= 10;//FrameSize[EFFECTSPRITETYPE_ACID_BOLT_1];
	(*g_pActionInfoTable)[SKILL_BLOODY_STRIKE][0].SoundID			= SOUND_VAMPIRE_GREENSTALKER2;
	(*g_pActionInfoTable)[SKILL_BLOODY_STRIKE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[SKILL_BLOODY_STRIKE][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_KNIFE_1;
	(*g_pActionInfoTable)[SKILL_BLOODY_STRIKE][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_BLOODY_STRIKE][1].Count				= 2*16;//FrameSize[EFFECTSPRITETYPE_ACID_BOLT_1];	
	
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_STRIKE].Set("RESULT_SKILL_BLOODY_STRIKE", ACTION_DAMAGED, EFFECTSPRITETYPE_BLOOD_GUN_3_1, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_STRIKE].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_STRIKE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_STRIKE].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_STRIKE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_STRIKE][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_KNIFE_2;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_STRIKE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_STRIKE][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_KNIFE_2];
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_STRIKE][0].SoundID				= SOUND_VAMPIRE_MISC_D;	
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_STRIKE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_STRIKE][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_KNIFE_2;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_STRIKE][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_STRIKE][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_KNIFE_2];
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_STRIKE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_STRIKE][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_KNIFE_2;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_STRIKE][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_STRIKE][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_KNIFE_2];

	// SKILL_BLOODY_STORM
	(*g_pActionInfoTable)[SKILL_BLOODY_STORM].Set("SKILL_BLOODY_STORM", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_BLOODY_STORM].SetCastingFramesAll( 16 );
	(*g_pActionInfoTable)[SKILL_BLOODY_STORM].SetStartFrameAll( 6 );
	(*g_pActionInfoTable)[SKILL_BLOODY_STORM].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_BLOODY_STORM][0].EffectGeneratorID	= EFFECTGENERATORID_MULTIPLE_FALLING;
	(*g_pActionInfoTable)[SKILL_BLOODY_STORM][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_BALL_2_MALE;
	(*g_pActionInfoTable)[SKILL_BLOODY_STORM][0].Step				= 30;
	(*g_pActionInfoTable)[SKILL_BLOODY_STORM][0].Count				= 17;//FrameSize[EFFECTSPRITETYPE_AURA_BALL_2];
	(*g_pActionInfoTable)[SKILL_BLOODY_STORM][1].EffectGeneratorID	= EFFECTGENERATORID_SPREAD_OUT;
	(*g_pActionInfoTable)[SKILL_BLOODY_STORM][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_KNIFE_1;
	(*g_pActionInfoTable)[SKILL_BLOODY_STORM][1].Step				= 30;
	(*g_pActionInfoTable)[SKILL_BLOODY_STORM][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_KNIFE_1];	
	(*g_pActionInfoTable)[SKILL_BLOODY_STORM].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_BLOODY_STORM );	// 맞는 결과를 표현한다.	
	(*g_pActionInfoTable)[SKILL_BLOODY_STORM].SetSkillFailDelay(); // 스킬실패해도 딜레이는 남아 있다..

	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_STORM].Set("RESULT_SKILL_BLOODY_STORM", ACTION_DAMAGED, EFFECTSPRITETYPE_BLOOD_GUN_3_1, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_STORM].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_STORM].SetSoundID( SOUNDID_NULL );	

	// SKILL_MEPHISTO
	(*g_pActionInfoTable)[SKILL_MEPHISTO].Set("SKILL_MEPHISTO", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_MEPHISTO].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[SKILL_MEPHISTO].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_MEPHISTO].SetEffectStatus( EFFECTSTATUS_MEPHISTO );	// [새기술8]

	(*g_pActionInfoTable)[RESULT_SKILL_MEPHISTO].Set("RESULT_SKILL_MEPHISTO", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_MEPHISTO].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_SKILL_MEPHISTO].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[RESULT_SKILL_MEPHISTO].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SKILL_MEPHISTO][0].EffectGeneratorID		= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_MEPHISTO][0].EffectSpriteType		= EFFECTSPRITETYPE_MEPHISTO;
	(*g_pActionInfoTable)[RESULT_SKILL_MEPHISTO][0].Step					= 30;
	(*g_pActionInfoTable)[RESULT_SKILL_MEPHISTO][0].Count					= FrameSize[EFFECTSPRITETYPE_MEPHISTO];
	(*g_pActionInfoTable)[RESULT_SKILL_MEPHISTO][0].SetResultTime();

	// SKILL_TRANSFUSION
	(*g_pActionInfoTable)[SKILL_TRANSFUSION].Set("SKILL_TRANSFUSION", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_TRANSFUSION].SetUser(FLAG_ACTIONINFO_USER_VAMPIRE);
	//(*g_pActionInfoTable)[SKILL_TRANSFUSION].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_TRANSFUSION].SetStartFrameAll( 15 );
	(*g_pActionInfoTable)[SKILL_TRANSFUSION].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TRANSFUSION].Init( 11 );		
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][0].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][0].EffectSpriteType	= EFFECTSPRITETYPE_TRANSFUSION_1;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][0].Step				= 20;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][0].Count				= FrameSize[EFFECTSPRITETYPE_TRANSFUSION_1];
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][0].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][0].SoundID				= SOUND_SLAYER_BLADE_EARTHQUAKE;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][0].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][1].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][1].EffectSpriteType	= EFFECTSPRITETYPE_TRANSFUSION_1;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][1].Step				= 20;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][1].Count				= FrameSize[EFFECTSPRITETYPE_TRANSFUSION_1];
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][1].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][2].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][2].EffectSpriteType	= EFFECTSPRITETYPE_TRANSFUSION_1;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][2].Step				= 20;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][2].Count				= FrameSize[EFFECTSPRITETYPE_TRANSFUSION_1];
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][2].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][2].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][3].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][3].EffectSpriteType	= EFFECTSPRITETYPE_TRANSFUSION_1;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][3].Step				= 20;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][3].Count				= FrameSize[EFFECTSPRITETYPE_TRANSFUSION_1];
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][3].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][3].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][4].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][4].EffectSpriteType	= EFFECTSPRITETYPE_TRANSFUSION_1;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][4].Step				= 20;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][4].Count				= FrameSize[EFFECTSPRITETYPE_TRANSFUSION_1];
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][4].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][4].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][5].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][5].EffectSpriteType	= EFFECTSPRITETYPE_TRANSFUSION_1;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][5].Step				= 20;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][5].Count				= FrameSize[EFFECTSPRITETYPE_TRANSFUSION_1];
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][5].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][5].SetDelayNode();	
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][5].SetResultTime();
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][6].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][6].EffectSpriteType	= EFFECTSPRITETYPE_TRANSFUSION_1;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][6].Step				= 20;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][6].Count				= FrameSize[EFFECTSPRITETYPE_TRANSFUSION_1];
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][6].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][6].SetDelayNode();	
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][7].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][7].EffectSpriteType	= EFFECTSPRITETYPE_TRANSFUSION_1;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][7].Step				= 20;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][7].Count				= FrameSize[EFFECTSPRITETYPE_TRANSFUSION_1];
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][7].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][7].SetDelayNode();	
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][8].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][8].EffectSpriteType	= EFFECTSPRITETYPE_TRANSFUSION_1;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][8].Step				= 20;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][8].Count				= FrameSize[EFFECTSPRITETYPE_TRANSFUSION_1];
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][8].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][8].SetDelayNode();	
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][9].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][9].EffectSpriteType	= EFFECTSPRITETYPE_TRANSFUSION_1;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][9].Step				= 20;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][9].Count				= FrameSize[EFFECTSPRITETYPE_TRANSFUSION_1];
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][9].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][9].SetDelayNode();	
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][10].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][10].EffectSpriteType	= EFFECTSPRITETYPE_TRANSFUSION_1;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][10].Step				= 20;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][10].Count				= FrameSize[EFFECTSPRITETYPE_TRANSFUSION_1];
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][10].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_TRANSFUSION][10].SetDelayNode();	
	(*g_pActionInfoTable)[SKILL_TRANSFUSION].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TRANSFUSION );	// 맞는 결과를 표현한다.	

	// SKILL_EARTHQUAKE
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFUSION].Set("RESULT_SKILL_TRANSFUSION", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFUSION].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFUSION].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFUSION].Init( 3 );
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFUSION][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFUSION][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_GROUND_2_1;
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFUSION][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFUSION][0].Count				= 4*16; //FrameSize[EFFECTSPRITETYPE_BLOOD_GROUND_2_1];
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFUSION][0].LinkCount			= 1;
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFUSION][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFUSION][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_GROUND_2_1;
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFUSION][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFUSION][1].Count				= 4*16; //FrameSize[EFFECTSPRITETYPE_BLOOD_GROUND_2_1];
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFUSION][1].LinkCount			= 1;
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFUSION][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFUSION][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_GROUND_2_1;
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFUSION][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFUSION][2].Count				= 4*16; //FrameSize[EFFECTSPRITETYPE_BLOOD_GROUND_2_1];
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFUSION][2].SetResultTime();
	
		// SKILL_EXTREME
	(*g_pActionInfoTable)[SKILL_EXTREME].Set("SKILL_EXTREME", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_EXTREME].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[SKILL_EXTREME].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_EXTREME].SetEffectStatus( EFFECTSTATUS_EXTREME );

	(*g_pActionInfoTable)[RESULT_SKILL_EXTREME].Set("RESULT_SKILL_EXTREME", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_EXTREME].SetSoundID( SOUNDID_NULL);	
	(*g_pActionInfoTable)[RESULT_SKILL_EXTREME].SetStartAfterCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_EXTREME].SetStartFrameAll( 16 );
	(*g_pActionInfoTable)[RESULT_SKILL_EXTREME].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SKILL_EXTREME][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_EXTREME][0].EffectSpriteType		= EFFECTSPRITETYPE_EXTREME_L_1_STAND_MALE;
	(*g_pActionInfoTable)[RESULT_SKILL_EXTREME][0].Step					= 30;
	(*g_pActionInfoTable)[RESULT_SKILL_EXTREME][0].Count				= FrameSize[EFFECTSPRITETYPE_EXTREME_L_1_STAND_MALE];
	(*g_pActionInfoTable)[RESULT_SKILL_EXTREME][0].SetDelayNode();

	// SKILL_BLOODY_WAVE
	(*g_pActionInfoTable)[SKILL_BLOODY_WAVE].Set("SKILL_BLOODY_WAVE", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_BLOODY_WAVE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_BLOODY_WAVE].SetStartFrameAll( 15 );
	(*g_pActionInfoTable)[SKILL_BLOODY_WAVE].Init( 3 );
	(*g_pActionInfoTable)[SKILL_BLOODY_WAVE][0].EffectGeneratorID	= EFFECTGENERATORID_BLOODY_WAVE;
	(*g_pActionInfoTable)[SKILL_BLOODY_WAVE][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[SKILL_BLOODY_WAVE][0].Step				= 30;
	(*g_pActionInfoTable)[SKILL_BLOODY_WAVE][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[SKILL_BLOODY_WAVE][0].LinkCount			= 2;
	(*g_pActionInfoTable)[SKILL_BLOODY_WAVE][0].SoundID				= SOUND_VAMPIRE_BLOODYWALL;
	(*g_pActionInfoTable)[SKILL_BLOODY_WAVE][1].EffectGeneratorID	= EFFECTGENERATORID_BLOODY_WAVE;
	(*g_pActionInfoTable)[SKILL_BLOODY_WAVE][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[SKILL_BLOODY_WAVE][1].Step				= 30;
	(*g_pActionInfoTable)[SKILL_BLOODY_WAVE][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[SKILL_BLOODY_WAVE][1].LinkCount			= 2;
	(*g_pActionInfoTable)[SKILL_BLOODY_WAVE][1].SoundID				= SOUND_VAMPIRE_BLOODYWALL;
	(*g_pActionInfoTable)[SKILL_BLOODY_WAVE][2].EffectGeneratorID	= EFFECTGENERATORID_BLOODY_WAVE;
	(*g_pActionInfoTable)[SKILL_BLOODY_WAVE][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[SKILL_BLOODY_WAVE][2].Step				= 30;
	(*g_pActionInfoTable)[SKILL_BLOODY_WAVE][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[SKILL_BLOODY_WAVE][2].SoundID				= SOUND_VAMPIRE_BLOODYWALL;
	(*g_pActionInfoTable)[SKILL_BLOODY_WAVE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_BLOODY_WAVE );	// 맞는 결과를 표현한다.	

	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_WAVE].Set("RESULT_SKILL_BLOODY_WAVE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_WAVE].SetSoundID( SOUNDID_NULL);

	// MAGIC_BLOODY_MASTER_WAVE
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE].Set("MAGIC_BLOODY_MASTER_WAVE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE].SetStartFrameAll( 15 );
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE].Init( 5 );
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE][0].EffectGeneratorID	= EFFECTGENERATORID_BLOODY_WAVE;
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE][0].Step				= 30;
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE][0].LinkCount			= 2;
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE][1].EffectGeneratorID	= EFFECTGENERATORID_BLOODY_WAVE;
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE][1].Step				= 30;
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE][1].LinkCount			= 2;
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE][2].EffectGeneratorID	= EFFECTGENERATORID_BLOODY_WAVE;
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE][2].Step				= 30;
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE][2].LinkCount			= 2;
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE][3].EffectGeneratorID	= EFFECTGENERATORID_BLOODY_WAVE;
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE][3].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE][3].Step				= 30;
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE][3].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE][3].LinkCount			= 2;
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE][4].EffectGeneratorID	= EFFECTGENERATORID_BLOODY_WAVE;
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE][4].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE][4].Step				= 30;
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE][4].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_MASTER_WAVE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, MAGIC_BLOODY_MASTER_WAVE );	// 맞는 결과를 표현한다.	

	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_MASTER_WAVE].Set("RESULT_MAGIC_BLOODY_MASTER_WAVE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_MASTER_WAVE].SetSoundID( SOUNDID_NULL);

	// MAGIC_BLOODY_WARP
	(*g_pActionInfoTable)[MAGIC_BLOODY_WARP].Set("MAGIC_BLOODY_WARP", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_BLOODY_WARP].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[MAGIC_BLOODY_WARP].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_BLOODY_WARP].SetEffectStatus( EFFECTSTATUS_EXTREME );
	(*g_pActionInfoTable)[MAGIC_BLOODY_WARP].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, MAGIC_BLOODY_WARP );	// 맞는 결과를 표현한다.	

	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WARP].Set("RESULT_MAGIC_BLOODY_WARP", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_WARP].SetSoundID( SOUNDID_NULL);

	// MAGIC_BLOODY_SNAKE
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE].Set("MAGIC_BLOODY_SNAKE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	//(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE].SetStartWithCasting();
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE].Init( 10 );		
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][0].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][0].Step				= 28;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][0].LinkCount			= 1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][0].SoundID				= SOUND_SLAYER_BLADE_EARTHQUAKE;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][0].SetDelayNode();
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][1].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][1].Step				= 28;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][1].LinkCount			= 1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][1].SetDelayNode();
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][2].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][2].Step				= 28;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][2].LinkCount			= 1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][2].SetDelayNode();
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][3].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][3].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][3].Step				= 28;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][3].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][3].LinkCount			= 1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][3].SetDelayNode();
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][4].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][4].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][4].Step				= 28;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][4].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][4].LinkCount			= 1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][4].SetDelayNode();
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][5].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][5].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][5].Step				= 28;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][5].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][5].LinkCount			= 1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][5].SetDelayNode();	
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][5].SetResultTime();
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][6].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][6].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][6].Step				= 28;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][6].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][6].LinkCount			= 1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][6].SetDelayNode();	
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][7].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][7].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][7].Step				= 28;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][7].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][7].LinkCount			= 1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][7].SetDelayNode();
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][8].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][8].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][8].Step				= 28;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][8].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][8].LinkCount			= 1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][8].SetDelayNode();
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][9].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][9].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][9].Step				= 28;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][9].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][9].LinkCount			= 1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE][9].SetDelayNode();
	(*g_pActionInfoTable)[MAGIC_BLOODY_SNAKE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, MAGIC_BLOODY_SNAKE );	// 맞는 결과를 표현한다.	

	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_SNAKE].Set("RESULT_MAGIC_BLOODY_SNAKE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_SNAKE].SetSoundID( SOUNDID_NULL);

		// SKILL_EARTHQUAKE		
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER].Set("MAGIC_BLOODY_BREAKER", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, 3);
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER].SetStartFrameAll( 15 );
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER].Init( 7 );		
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][0].EffectGeneratorID	= EFFECTGENERATORID_BLOODY_BREAKER;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][0].LinkCount		= 2;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][1].EffectGeneratorID	= EFFECTGENERATORID_BLOODY_BREAKER;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][1].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][1].LinkCount		= 2;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][2].EffectGeneratorID	= EFFECTGENERATORID_BLOODY_BREAKER;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][2].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][2].LinkCount		= 2;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][3].EffectGeneratorID	= EFFECTGENERATORID_BLOODY_BREAKER;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][3].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][3].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][3].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][3].LinkCount		= 2;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][4].EffectGeneratorID	= EFFECTGENERATORID_BLOODY_BREAKER;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][4].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][4].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][4].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][4].LinkCount		= 2;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][5].EffectGeneratorID	= EFFECTGENERATORID_BLOODY_BREAKER;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][5].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][5].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][5].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][6].LinkCount		= 2;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][6].EffectGeneratorID	= EFFECTGENERATORID_BLOODY_BREAKER;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][6].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WALL_1;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][6].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][6].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WALL_1];
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER][6].LinkCount		= 2;
	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, MAGIC_BLOODY_BREAKER);	// 맞는 결과를 표현한다.	

	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_BREAKER].Set("RESULT_MAGIC_BLOODY_BREAKER", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_BREAKER].SetStartWithCasting();		
	
	(*g_pActionInfoTable)[MAGIC_RAPID_GLIDING].Set("MAGIC_RAPID_GLIDING", ACTION_STAND, EFFECTSPRITETYPE_NULL, 6, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, 10);//ActionDelay[ACTION_SLAYER_SWORD]);	
	(*g_pActionInfoTable)[MAGIC_RAPID_GLIDING].SetSoundID( SOUNDID_NULL );
	
	(*g_pActionInfoTable)[RESULT_MAGIC_RAPID_GLIDING].Set("RESULT_MAGIC_RAPID_GLIDING", ACTION_STAND, EFFECTSPRITETYPE_NULL, 6, FLAG_ACTIONINFO_TARGET_NONE, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[RESULT_MAGIC_RAPID_GLIDING].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[SKILL_POISON_MESH].Set("SKILL_POISON_MESH", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_POISON_MESH].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_POISON_MESH].SetSoundID( SOUNDID_NULL );	
	(*g_pActionInfoTable)[SKILL_POISON_MESH].SetSkillFailDelay(); // 스킬실패해도 딜레이는 남아 있다..
	
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_MESH].Set("SKILL_POISON_MESH", ACTION_STAND, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, 3);
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_MESH].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_MESH].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_MESH].Init( 3 );
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_MESH].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_MESH][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_MESH][0].EffectSpriteType	= EFFECTSPRITETYPE_POISON_MESH_START;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_MESH][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_MESH][0].Count				= FrameSize[EFFECTSPRITETYPE_POISON_MESH_START];
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_MESH][0].SoundID				= SOUND_VAMPIRE_ACIDBURN;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_MESH][0].LinkCount			= FrameSize[EFFECTSPRITETYPE_POISON_MESH_START];
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_MESH][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_MESH][1].EffectSpriteType	= EFFECTSPRITETYPE_POISON_MESH_ING;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_MESH][1].Step				= 25;	
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_MESH][1].Count				= FrameSize[EFFECTSPRITETYPE_POISON_MESH_ING];
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_MESH][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_MESH][1].SetResultTime();
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_MESH][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_MESH][2].EffectSpriteType	= EFFECTSPRITETYPE_POISON_MESH_END;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_MESH][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_POISON_MESH][2].Count				= FrameSize[EFFECTSPRITETYPE_POISON_MESH_END];
	
	(*g_pActionInfoTable)[SKILL_WILL_OF_LIFE].Set("SKILL_WILL_OF_LIFE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_WILL_OF_LIFE].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_WILL_OF_LIFE].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_WILL_OF_LIFE].Set("RESULT_SKILL_WILL_OF_LIFE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
//	(*g_pActionInfoTable)[RESULT_SKILL_WILL_OF_LIFE].SetStartFrameAll( 15 );
	(*g_pActionInfoTable)[RESULT_SKILL_WILL_OF_LIFE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_WILL_OF_LIFE].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_WILL_OF_LIFE].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_WILL_OF_LIFE].Init( 2 );
	(*g_pActionInfoTable)[RESULT_SKILL_WILL_OF_LIFE][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_WILL_OF_LIFE][0].EffectSpriteType = EFFECTSPRITETYPE_WILL_OF_LIFE;
	(*g_pActionInfoTable)[RESULT_SKILL_WILL_OF_LIFE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_WILL_OF_LIFE][0].Count				= FrameSize[EFFECTSPRITETYPE_WILL_OF_LIFE];
	
	(*g_pActionInfoTable)[MAGIC_BLOODY_ZENITH].Set("MAGIC_BLOODY_ZENITH", ACTION_STAND, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_BLOODY_ZENITH].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_ZENITH].Set("RESULT_MAGIC_BLOODY_ZENITH", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[RESULT_MAGIC_BLOODY_ZENITH].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[SKILL_BITE_OF_DEATH].Set("SKILL_BITE_OF_DEATH", ACTION_VAMPIRE_DRAIN, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_VAMPIRE_DRAIN]);
	(*g_pActionInfoTable)[SKILL_BITE_OF_DEATH].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_BITE_OF_DEATH].SetStartWithCasting();

	(*g_pActionInfoTable)[RESULT_SKILL_BITE_OF_DEATH].Set("RESULT_SKILL_BITE_OF_DEATH", ACTION_DRAINED, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[RESULT_SKILL_BITE_OF_DEATH].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_BITE_OF_DEATH].SetStartWithCasting();

	(*g_pActionInfoTable)[SKILL_TALON_OF_CROW].Set("SKILL_TALON_OF_CROW", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 2, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_TALON_OF_CROW].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_TALON_OF_CROW].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TALON_OF_CROW].SetSoundID( SOUNDID_NULL );	
	(*g_pActionInfoTable)[SKILL_TALON_OF_CROW].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_TALON_OF_CROW].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_TALON_OF_CROW][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_TALON_OF_CROW][0].EffectSpriteType	= EFFECTSPRITETYPE_RENEWAL_TALON_OF_CROW_MALE_ACTION_1_NORMAL;
	(*g_pActionInfoTable)[SKILL_TALON_OF_CROW][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TALON_OF_CROW][0].Count				= FrameSize[EFFECTSPRITETYPE_RENEWAL_TALON_OF_CROW_MALE_ACTION_1_NORMAL];
	(*g_pActionInfoTable)[SKILL_TALON_OF_CROW][0].SoundID			= SOUND_VAMPIRE_ACID_AT;
	(*g_pActionInfoTable)[SKILL_TALON_OF_CROW][0].SetResultTime();

	(*g_pActionInfoTable)[RESULT_SKILL_TALON_OF_CROW].Set("RESULT_SKILL_TALON_OF_CROW", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_TALON_OF_CROW].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_TALON_OF_CROW].Init( 4 );
	(*g_pActionInfoTable)[RESULT_SKILL_TALON_OF_CROW][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_TALON_OF_CROW][0].EffectSpriteType = EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_1;
	(*g_pActionInfoTable)[RESULT_SKILL_TALON_OF_CROW][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_TALON_OF_CROW][0].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_1];
	(*g_pActionInfoTable)[RESULT_SKILL_TALON_OF_CROW][0].LinkCount			= 2;
	(*g_pActionInfoTable)[RESULT_SKILL_TALON_OF_CROW][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_TALON_OF_CROW][1].EffectSpriteType = EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_2;
	(*g_pActionInfoTable)[RESULT_SKILL_TALON_OF_CROW][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_TALON_OF_CROW][1].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_2];
	(*g_pActionInfoTable)[RESULT_SKILL_TALON_OF_CROW][1].LinkCount			= 2;
	(*g_pActionInfoTable)[RESULT_SKILL_TALON_OF_CROW][2].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_TALON_OF_CROW][2].EffectSpriteType = EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_3;
	(*g_pActionInfoTable)[RESULT_SKILL_TALON_OF_CROW][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_TALON_OF_CROW][2].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_3];
	(*g_pActionInfoTable)[RESULT_SKILL_TALON_OF_CROW][2].LinkCount			= 4;
	(*g_pActionInfoTable)[RESULT_SKILL_TALON_OF_CROW][3].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_TALON_OF_CROW][3].EffectSpriteType = EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_4;
	(*g_pActionInfoTable)[RESULT_SKILL_TALON_OF_CROW][3].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_TALON_OF_CROW][3].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_4];
	(*g_pActionInfoTable)[RESULT_SKILL_TALON_OF_CROW][3].LinkCount			= 4;

	(*g_pActionInfoTable)[SKILL_TRANSFORM_TO_WERWOLF].Set("SKILL_TRANSFORM_TO_WERWOLF", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_ITEM, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);	
	(*g_pActionInfoTable)[SKILL_TRANSFORM_TO_WERWOLF].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_TRANSFORM_TO_WERWOLF].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TRANSFORM_TO_WERWOLF].SetEffectStatus( EFFECTSTATUS_TRANSFORM_TO_WERWOLF );
	(*g_pActionInfoTable)[SKILL_TRANSFORM_TO_WERWOLF].SetActionResult( ACTIONRESULTNODE_CHANGE_CREATURE_TYPE );	// 변신

	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFORM_TO_WERWOLF].Set("RESULT_SKILL_TRANSFORM_TO_WERWOLF", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFORM_TO_WERWOLF].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFORM_TO_WERWOLF].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFORM_TO_WERWOLF][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFORM_TO_WERWOLF][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_HIDE;
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFORM_TO_WERWOLF][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFORM_TO_WERWOLF][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_HIDE];
	(*g_pActionInfoTable)[RESULT_SKILL_TRANSFORM_TO_WERWOLF][0].SoundID				= SOUND_VAMPIRE_TRANSFORM;

	(*g_pActionInfoTable)[SKILL_STONE_SKIN].Set("SKILL_STONE_SKIN", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF );
	(*g_pActionInfoTable)[SKILL_STONE_SKIN].SetSoundID( SOUNDID_NULL );
	
	(*g_pActionInfoTable)[RESULT_SKILL_STONE_SKIN].Set("RESULT_SKILL_STONE_SKIN", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF );
	(*g_pActionInfoTable)[RESULT_SKILL_STONE_SKIN].SetSoundID( SOUNDID_NULL );	
	(*g_pActionInfoTable)[RESULT_SKILL_STONE_SKIN].Init( 2 );
	(*g_pActionInfoTable)[RESULT_SKILL_STONE_SKIN][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_STONE_SKIN][0].EffectSpriteType = EFFECTSPRITETYPE_STONE_SKIN_ING_FRONT;
	(*g_pActionInfoTable)[RESULT_SKILL_STONE_SKIN][0].Step			= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_STONE_SKIN][0].Count		= FrameSize[EFFECTSPRITETYPE_STONE_SKIN_ING_FRONT];
	(*g_pActionInfoTable)[RESULT_SKILL_STONE_SKIN][0].SoundID		= SOUNDID_NULL;
	(*g_pActionInfoTable)[RESULT_SKILL_STONE_SKIN][0].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_SKILL_STONE_SKIN][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_STONE_SKIN][1].EffectSpriteType = EFFECTSPRITETYPE_STONE_SKIN_END_FRONT;
	(*g_pActionInfoTable)[RESULT_SKILL_STONE_SKIN][1].Step			= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_STONE_SKIN][1].Count		= FrameSize[EFFECTSPRITETYPE_STONE_SKIN_END_FRONT];
	(*g_pActionInfoTable)[RESULT_SKILL_STONE_SKIN][1].SoundID		= SOUNDID_NULL;

	(*g_pActionInfoTable)[SKILL_GRAY_DARKNESS].Set("SKILL_GRAY_DARKNESS", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_GRAY_DARKNESS].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_GRAY_DARKNESS].SetSoundID( SOUNDID_NULL );	

	(*g_pActionInfoTable)[RESULT_SKILL_GRAY_DARKNESS].Set("RESULT_SKILL_GRAY_DARKNESS", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_SKILL_GRAY_DARKNESS].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_GRAY_DARKNESS].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_GRAY_DARKNESS].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_SKILL_GRAY_DARKNESS].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_GRAY_DARKNESS][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_RECT;
	(*g_pActionInfoTable)[RESULT_SKILL_GRAY_DARKNESS][0].EffectSpriteType	= EFFECTSPRITETYPE_GRAY_DARKNESS_1_1;
	(*g_pActionInfoTable)[RESULT_SKILL_GRAY_DARKNESS][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_GRAY_DARKNESS][0].Count				= FrameSize[EFFECTSPRITETYPE_GRAY_DARKNESS_1_1];
	(*g_pActionInfoTable)[RESULT_SKILL_GRAY_DARKNESS][0].SoundID				= SOUND_VAMPIRE_MISC_D;
	(*g_pActionInfoTable)[RESULT_SKILL_GRAY_DARKNESS][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_GRAY_DARKNESS][1].EffectSpriteType	= EFFECTSPRITETYPE_GRAY_DARKNESS_2_1;
	(*g_pActionInfoTable)[RESULT_SKILL_GRAY_DARKNESS][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_GRAY_DARKNESS][1].Count				= FrameSize[EFFECTSPRITETYPE_GRAY_DARKNESS_2_1];
	(*g_pActionInfoTable)[RESULT_SKILL_GRAY_DARKNESS][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_SKILL_GRAY_DARKNESS][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_GRAY_DARKNESS][2].EffectSpriteType	= EFFECTSPRITETYPE_GRAY_DARKNESS_3_1;
	(*g_pActionInfoTable)[RESULT_SKILL_GRAY_DARKNESS][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_GRAY_DARKNESS][2].Count				= FrameSize[EFFECTSPRITETYPE_GRAY_DARKNESS_3_1];

	(*g_pActionInfoTable)[SKILL_ACID_ERUPTION].Set("SKILL_ERUPTION", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_SKY, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_ACID_ERUPTION].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_ACID_ERUPTION].SetSoundID( SOUNDID_NULL );	

	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION].Set("RESULT_SKILL_ACID_ERUPTION", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION].Init( 5 );		
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][0].EffectSpriteType	= EFFECTSPRITETYPE_ACID_ERUPTION_1;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][0].Step				= 30;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][0].Count				= FrameSize[EFFECTSPRITETYPE_ACID_ERUPTION_1];
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][0].LinkCount			= 5;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][1].EffectSpriteType	= EFFECTSPRITETYPE_ACID_ERUPTION_2;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][1].Count				= FrameSize[EFFECTSPRITETYPE_ACID_ERUPTION_2];
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][1].LinkCount			= 5;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][1].SoundID			= SOUND_VAMPIRE_ACID_ABOLT1;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][2].EffectSpriteType	= EFFECTSPRITETYPE_ACID_ERUPTION_3;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][2].Count				= FrameSize[EFFECTSPRITETYPE_ACID_ERUPTION_3];
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][2].LinkCount			= 5;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][2].SoundID			= SOUND_VAMPIRE_ACID_ABOLT2;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][3].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][3].EffectSpriteType	= EFFECTSPRITETYPE_ACID_ERUPTION_4;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][3].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][3].Count				= FrameSize[EFFECTSPRITETYPE_ACID_ERUPTION_4];
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][3].SoundID			= SOUND_VAMPIRE_ACID_ABOLT1;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][3].LinkCount			= 5;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][4].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][4].EffectSpriteType	= EFFECTSPRITETYPE_ACID_ERUPTION_5;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][4].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][4].Count				= FrameSize[EFFECTSPRITETYPE_ACID_ERUPTION_5];
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][4].LinkCount			= 5;
	(*g_pActionInfoTable)[RESULT_SKILL_ACID_ERUPTION][4].SoundID			= SOUND_VAMPIRE_ACID_ABOLT2;

	// 2004,3,6 sobeit add start - 스터지 흡혈
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_1].Set("SKILL_CLIENT_STIRGE_BLOOD_DRAIN_1", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK] );
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_1].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_1].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_1].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_1][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_1][0].EffectSpriteType = EFFECTSPRITETYPE_PET_VAMPIRE_BLOOD_DRAIN_1;
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_1][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_1][0].Count				= FrameSize[EFFECTSPRITETYPE_PET_VAMPIRE_BLOOD_DRAIN_1];

	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_2].Set("SKILL_CLIENT_STIRGE_BLOOD_DRAIN_2", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK] );
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_2].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_2].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_2].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_2][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_2][0].EffectSpriteType = EFFECTSPRITETYPE_PET_VAMPIRE_BLOOD_DRAIN_2;
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_2][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_2][0].Count				= FrameSize[EFFECTSPRITETYPE_PET_VAMPIRE_BLOOD_DRAIN_2];

	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_3].Set("SKILL_CLIENT_STIRGE_BLOOD_DRAIN_3", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK] );
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_3].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_3].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_3].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_3][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_3][0].EffectSpriteType = EFFECTSPRITETYPE_PET_VAMPIRE_BLOOD_DRAIN_3;
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_3][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_3][0].Count				= FrameSize[EFFECTSPRITETYPE_PET_VAMPIRE_BLOOD_DRAIN_3];

	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_4].Set("SKILL_CLIENT_STIRGE_BLOOD_DRAIN_4", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK] );
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_4].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_4].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_4].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_4][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_4][0].EffectSpriteType = EFFECTSPRITETYPE_PET_VAMPIRE_BLOOD_DRAIN_4;
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_4][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_4][0].Count				= FrameSize[EFFECTSPRITETYPE_PET_VAMPIRE_BLOOD_DRAIN_4];

	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_5].Set("SKILL_CLIENT_STIRGE_BLOOD_DRAIN_5", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK] );
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_5].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_5].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_5].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_5][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_5][0].EffectSpriteType = EFFECTSPRITETYPE_PET_VAMPIRE_BLOOD_DRAIN_5;
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_5][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_STIRGE_BLOOD_DRAIN_5][0].Count				= FrameSize[EFFECTSPRITETYPE_PET_VAMPIRE_BLOOD_DRAIN_5];
	// 2004,3,6 sobeit add end - 스터지 흡혈


//	// 2004, 08, 07 sobeit add start-SKILL_CLIENT_TEST_VIOLENT_PHANTOM
	(*g_pActionInfoTable)[SKILL_VIOLENT_PHANTOM].Set("SKILL_VIOLENT_PHANTOM", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 2, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_VIOLENT_PHANTOM].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_VIOLENT_PHANTOM].SetSoundID( SOUNDID_NULL );	
	(*g_pActionInfoTable)[SKILL_VIOLENT_PHANTOM].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_VIOLENT_PHANTOM].SetStartFrame( 0, 4);		// slow
	(*g_pActionInfoTable)[SKILL_VIOLENT_PHANTOM].SetStartFrame( 1, 3);		// slow
	(*g_pActionInfoTable)[SKILL_VIOLENT_PHANTOM].SetStartFrame( 2, 3);		// slow
	(*g_pActionInfoTable)[SKILL_VIOLENT_PHANTOM].SetRepeatFrame( 0, 4, 8);		// slow
	(*g_pActionInfoTable)[SKILL_VIOLENT_PHANTOM].SetRepeatFrame( 1, 3, 7);		// normal
	(*g_pActionInfoTable)[SKILL_VIOLENT_PHANTOM].SetRepeatFrame( 2, 3, 6);		// fast
	(*g_pActionInfoTable)[SKILL_VIOLENT_PHANTOM].UseRepeatFrame();	
	(*g_pActionInfoTable)[SKILL_VIOLENT_PHANTOM].SetRepeatLimit( 2 );
	(*g_pActionInfoTable)[SKILL_VIOLENT_PHANTOM].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_VIOLENT_PHANTOM][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_VIOLENT_PHANTOM][0].EffectSpriteType	= EFFECTSPRITETYPE_VIOLENT_PHANTOM;//EFFECTSPRITETYPE_ACID_TOUCH;
	(*g_pActionInfoTable)[SKILL_VIOLENT_PHANTOM][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_VIOLENT_PHANTOM][0].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM];
	(*g_pActionInfoTable)[SKILL_VIOLENT_PHANTOM][0].SetResultTime();
	(*g_pActionInfoTable)[SKILL_VIOLENT_PHANTOM].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, RESULT_SKILL_VIOLENT_PHANTOM );	// 맞는 결과를 표현한다.	

	(*g_pActionInfoTable)[RESULT_SKILL_VIOLENT_PHANTOM].Set("RESULT_SKILL_VIOLENT_PHANTOM", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[RESULT_SKILL_VIOLENT_PHANTOM].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_VIOLENT_PHANTOM].Init( 4 );
	(*g_pActionInfoTable)[RESULT_SKILL_VIOLENT_PHANTOM][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_VIOLENT_PHANTOM][0].EffectSpriteType = EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_1;
	(*g_pActionInfoTable)[RESULT_SKILL_VIOLENT_PHANTOM][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_VIOLENT_PHANTOM][0].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_1];
	(*g_pActionInfoTable)[RESULT_SKILL_VIOLENT_PHANTOM][0].LinkCount			= 2;
	(*g_pActionInfoTable)[RESULT_SKILL_VIOLENT_PHANTOM][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_VIOLENT_PHANTOM][1].EffectSpriteType = EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_2;
	(*g_pActionInfoTable)[RESULT_SKILL_VIOLENT_PHANTOM][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_VIOLENT_PHANTOM][1].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_2];
	(*g_pActionInfoTable)[RESULT_SKILL_VIOLENT_PHANTOM][1].LinkCount			= 2;
	(*g_pActionInfoTable)[RESULT_SKILL_VIOLENT_PHANTOM][2].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_VIOLENT_PHANTOM][2].EffectSpriteType = EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_3;
	(*g_pActionInfoTable)[RESULT_SKILL_VIOLENT_PHANTOM][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_VIOLENT_PHANTOM][2].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_3];
	(*g_pActionInfoTable)[RESULT_SKILL_VIOLENT_PHANTOM][2].LinkCount			= 4;
	(*g_pActionInfoTable)[RESULT_SKILL_VIOLENT_PHANTOM][3].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_VIOLENT_PHANTOM][3].EffectSpriteType = EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_4;
	(*g_pActionInfoTable)[RESULT_SKILL_VIOLENT_PHANTOM][3].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_VIOLENT_PHANTOM][3].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_4];
	(*g_pActionInfoTable)[RESULT_SKILL_VIOLENT_PHANTOM][3].LinkCount			= 4;

#if __CONTENTS(__SECOND_RARE_SKILL)
	(*g_pActionInfoTable)[SKILL_LETHAL_CLAW].Set("SKILL_LETHAL_CLAW", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 2, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_LETHAL_CLAW].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_LETHAL_CLAW].SetSoundID( SOUNDID_NULL );	
	(*g_pActionInfoTable)[SKILL_LETHAL_CLAW].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_LETHAL_CLAW].SetStartFrame( 0, 4);		// slow
	(*g_pActionInfoTable)[SKILL_LETHAL_CLAW].SetStartFrame( 1, 3);		// slow
	(*g_pActionInfoTable)[SKILL_LETHAL_CLAW].SetStartFrame( 2, 3);		// slow
	(*g_pActionInfoTable)[SKILL_LETHAL_CLAW].SetRepeatFrame( 0, 4, 8);		// slow
	(*g_pActionInfoTable)[SKILL_LETHAL_CLAW].SetRepeatFrame( 1, 3, 7);		// normal
	(*g_pActionInfoTable)[SKILL_LETHAL_CLAW].SetRepeatFrame( 2, 3, 6);		// fast
	(*g_pActionInfoTable)[SKILL_LETHAL_CLAW].UseRepeatFrame();	
	(*g_pActionInfoTable)[SKILL_LETHAL_CLAW].SetRepeatLimit( 2 );
	(*g_pActionInfoTable)[SKILL_LETHAL_CLAW].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_LETHAL_CLAW][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_LETHAL_CLAW][0].EffectSpriteType	= EFFECTSPRITETYPE_LETHAL_CLAW;//EFFECTSPRITETYPE_ACID_TOUCH;
	(*g_pActionInfoTable)[SKILL_LETHAL_CLAW][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_LETHAL_CLAW][0].Count				= FrameSize[EFFECTSPRITETYPE_LETHAL_CLAW];
	(*g_pActionInfoTable)[SKILL_LETHAL_CLAW][0].SetResultTime();
	(*g_pActionInfoTable)[SKILL_LETHAL_CLAW].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, RESULT_SKILL_LETHAL_CLAW );	// 맞는 결과를 표현한다.	

	(*g_pActionInfoTable)[RESULT_SKILL_LETHAL_CLAW].Set("RESULT_SKILL_LETHAL_CLAW", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[RESULT_SKILL_LETHAL_CLAW].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_LETHAL_CLAW].Init( 4 );
	(*g_pActionInfoTable)[RESULT_SKILL_LETHAL_CLAW][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_LETHAL_CLAW][0].EffectSpriteType = EFFECTSPRITETYPE_LETHAL_CLAW_BLOOD_1;
	(*g_pActionInfoTable)[RESULT_SKILL_LETHAL_CLAW][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_LETHAL_CLAW][0].Count				= FrameSize[EFFECTSPRITETYPE_LETHAL_CLAW_BLOOD_1];
	(*g_pActionInfoTable)[RESULT_SKILL_LETHAL_CLAW][0].LinkCount			= 2;
	(*g_pActionInfoTable)[RESULT_SKILL_LETHAL_CLAW][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_LETHAL_CLAW][1].EffectSpriteType = EFFECTSPRITETYPE_LETHAL_CLAW_BLOOD_2;
	(*g_pActionInfoTable)[RESULT_SKILL_LETHAL_CLAW][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_LETHAL_CLAW][1].Count				= FrameSize[EFFECTSPRITETYPE_LETHAL_CLAW_BLOOD_2];
	(*g_pActionInfoTable)[RESULT_SKILL_LETHAL_CLAW][1].LinkCount			= 2;
	(*g_pActionInfoTable)[RESULT_SKILL_LETHAL_CLAW][2].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_LETHAL_CLAW][2].EffectSpriteType = EFFECTSPRITETYPE_LETHAL_CLAW_BLOOD_3;
	(*g_pActionInfoTable)[RESULT_SKILL_LETHAL_CLAW][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_LETHAL_CLAW][2].Count				= FrameSize[EFFECTSPRITETYPE_LETHAL_CLAW_BLOOD_3];
	(*g_pActionInfoTable)[RESULT_SKILL_LETHAL_CLAW][2].LinkCount			= 4;
	(*g_pActionInfoTable)[RESULT_SKILL_LETHAL_CLAW][3].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_LETHAL_CLAW][3].EffectSpriteType = EFFECTSPRITETYPE_LETHAL_CLAW_BLOOD_4;
	(*g_pActionInfoTable)[RESULT_SKILL_LETHAL_CLAW][3].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_LETHAL_CLAW][3].Count				= FrameSize[EFFECTSPRITETYPE_LETHAL_CLAW_BLOOD_4];
	(*g_pActionInfoTable)[RESULT_SKILL_LETHAL_CLAW][3].LinkCount			= 4;

	(*g_pActionInfoTable)[SKILL_VENOM_CIRCLE].Set("SKILL_VENOM_CIRCLE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_VENOM_CIRCLE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_VENOM_CIRCLE].SetStartFrameAll(7);
	(*g_pActionInfoTable)[SKILL_VENOM_CIRCLE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, RESULT_SKILL_VENOM_CIRCLE );	// 맞는 결과를 표현한다.
	(*g_pActionInfoTable)[SKILL_VENOM_CIRCLE].Init( 2 );
	(*g_pActionInfoTable)[SKILL_VENOM_CIRCLE][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_VENOM_CIRCLE][0].EffectSpriteType	= EFFECTSPRITETYPE_VENOM_CIRCLE;
	(*g_pActionInfoTable)[SKILL_VENOM_CIRCLE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_VENOM_CIRCLE][0].Count				= FrameSize[EFFECTSPRITETYPE_VENOM_CIRCLE]*2;
	(*g_pActionInfoTable)[SKILL_VENOM_CIRCLE][0].SoundID			= SOUNDID_NULL;
	(*g_pActionInfoTable)[SKILL_VENOM_CIRCLE][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_VENOM_CIRCLE][1].EffectSpriteType	= EFFECTSPRITETYPE_VENOM_CIRCLE;
	(*g_pActionInfoTable)[SKILL_VENOM_CIRCLE][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_VENOM_CIRCLE][1].Count				= FrameSize[EFFECTSPRITETYPE_VENOM_CIRCLE];
	(*g_pActionInfoTable)[SKILL_VENOM_CIRCLE][1].SoundID			= SOUNDID_NULL;

	(*g_pActionInfoTable)[RESULT_SKILL_VENOM_CIRCLE].Set("RESULT_SKILL_VENOM_CIRCLE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_VENOM_CIRCLE].SetSoundID(SOUND_VENOM_CIRCLE);
	(*g_pActionInfoTable)[RESULT_SKILL_VENOM_CIRCLE].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_VENOM_CIRCLE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_VENOM_CIRCLE][0].EffectSpriteType	= EFFECTSPRITETYPE_VENOM_CIRCLE;
	(*g_pActionInfoTable)[RESULT_SKILL_VENOM_CIRCLE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_VENOM_CIRCLE][0].Count				= FrameSize[EFFECTSPRITETYPE_VENOM_CIRCLE];
	(*g_pActionInfoTable)[RESULT_SKILL_VENOM_CIRCLE][0].SoundID				= SOUNDID_NULL;
/*
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE].Set("SKILL_CLIENT_VENOM_CIRCLE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE].Init( 5 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE].SetMainNode( 3 );
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][0].EffectSpriteType	= EFFECTSPRITETYPE_CURSE_OF_BLOOD_TARGET_HANDS_START;
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][0].Count				= FrameSize[EFFECTSPRITETYPE_CURSE_OF_BLOOD_TARGET_HANDS_START];
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][0].SoundID				= SOUND_VAMPIRE_PARALYSIS;
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][0].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][1].EffectSpriteType	= EFFECTSPRITETYPE_CURSE_OF_BLOOD_TARGET_GROUND_START;
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][1].Count				= FrameSize[EFFECTSPRITETYPE_CURSE_OF_BLOOD_TARGET_GROUND_START];
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][2].EffectSpriteType	= EFFECTSPRITETYPE_CURSE_OF_BLOOD_TARGET_GROUND_REPEAT;
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][2].Count				= FrameSize[EFFECTSPRITETYPE_CURSE_OF_BLOOD_TARGET_GROUND_REPEAT];
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][2].SetResultTime();
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][2].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][3].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][3].EffectSpriteType	= EFFECTSPRITETYPE_CURSE_OF_BLOOD_TARGET_HANDS_END;
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][3].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][3].Count				= FrameSize[EFFECTSPRITETYPE_CURSE_OF_BLOOD_TARGET_HANDS_END];
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][3].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][4].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][4].EffectSpriteType	= EFFECTSPRITETYPE_CURSE_OF_BLOOD_TARGET_GROUND_END;
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][4].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_VENOM_CIRCLE][4].Count				= FrameSize[EFFECTSPRITETYPE_CURSE_OF_BLOOD_TARGET_GROUND_END];
//*/
#endif //__SECOND_RARE_SKILL

	// MAGIC_SUMMON_MONSTERS,
	(*g_pActionInfoTable)[SKILL_SUMMON_GORE_GLAND].Set("SKILL_SUMMON_GORE_GLAND", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_SUMMON_GORE_GLAND].SetSoundID( SOUND_VAMPIRE_SUMMONGOREGRAND );	

	// 2004.9.16 서먼 고어 파이어 
//	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE].Set("SKILL_GORE_GLAND_FIRE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER);
//	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE].SetSoundID( SOUNDID_NULL );
//	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE].Init( 4 );		
//	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE;
//	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE][0].EffectSpriteType	= EFFECTSPRITETYPE_SUMMON_GORE_GRAND_THROW_BLOOD;
//	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE][0].Step				= 25;
//	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE][0].Count				= FrameSize[EFFECTSPRITETYPE_SUMMON_GORE_GRAND_THROW_BLOOD];
//	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
//	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE][1].EffectSpriteType	= EFFECTSPRITETYPE_SUMMON_GORE_GRAND_GROUND_START;
//	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE][1].Step				= 25;
//	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE][1].Count				= FrameSize[EFFECTSPRITETYPE_SUMMON_GORE_GRAND_GROUND_START];
//	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE][2].EffectSpriteType	= EFFECTSPRITETYPE_SUMMON_GORE_GRAND_GROUND_LOOP;
//	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE][2].Step				= 25;
//	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE][2].Count				= FrameSize[EFFECTSPRITETYPE_SUMMON_GORE_GRAND_GROUND_LOOP];
////	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE][2].SetDelayNode();
//	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE][3].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
//	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE][3].EffectSpriteType	= EFFECTSPRITETYPE_SUMMON_GORE_GRAND_GROUND_END;
//	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE][3].Step				= 25;
//	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE][3].Count				= FrameSize[EFFECTSPRITETYPE_SUMMON_GORE_GRAND_GROUND_END];
//	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, RESULT_SKILL_GORE_GLAND_FIRE );	// 맞는 결과를 표현한다.	
	
	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE].Set("SKILL_GORE_GLAND_FIRE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE;
	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE][0].EffectSpriteType	= EFFECTSPRITETYPE_SUMMON_GORE_GRAND_THROW_BLOOD;
	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE][0].Count				= FrameSize[EFFECTSPRITETYPE_SUMMON_GORE_GRAND_THROW_BLOOD];
	(*g_pActionInfoTable)[SKILL_GORE_GLAND_FIRE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, RESULT_SKILL_GORE_GLAND_FIRE );	// 맞는 결과를 표현한다.	


	(*g_pActionInfoTable)[RESULT_SKILL_GORE_GLAND_FIRE].Set("RESULT_SKILL_GORE_GLAND_FIRE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE,FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_SKILL_GORE_GLAND_FIRE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_GORE_GLAND_FIRE].Init( 3 );		//	EFFECTSPRITETYPE_SUMMON_GORE_GRAND_GROUND_LOOP, // 서먼 고어 그랜드 땅에 핏물 
	(*g_pActionInfoTable)[RESULT_SKILL_GORE_GLAND_FIRE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_GORE_GLAND_FIRE][0].EffectSpriteType	= EFFECTSPRITETYPE_SUMMON_GORE_GRAND_GROUND_START;
	(*g_pActionInfoTable)[RESULT_SKILL_GORE_GLAND_FIRE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_GORE_GLAND_FIRE][0].Count				= FrameSize[EFFECTSPRITETYPE_SUMMON_GORE_GRAND_GROUND_START];
	(*g_pActionInfoTable)[RESULT_SKILL_GORE_GLAND_FIRE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_GORE_GLAND_FIRE][1].EffectSpriteType	= EFFECTSPRITETYPE_SUMMON_GORE_GRAND_GROUND_LOOP;
	(*g_pActionInfoTable)[RESULT_SKILL_GORE_GLAND_FIRE][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_GORE_GLAND_FIRE][1].Count				= FrameSize[EFFECTSPRITETYPE_SUMMON_GORE_GRAND_GROUND_LOOP];
	(*g_pActionInfoTable)[RESULT_SKILL_GORE_GLAND_FIRE][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_SKILL_GORE_GLAND_FIRE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_GORE_GLAND_FIRE][2].EffectSpriteType	= EFFECTSPRITETYPE_SUMMON_GORE_GRAND_GROUND_END;
	(*g_pActionInfoTable)[RESULT_SKILL_GORE_GLAND_FIRE][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_GORE_GLAND_FIRE][2].Count				= FrameSize[EFFECTSPRITETYPE_SUMMON_GORE_GRAND_GROUND_END];
//	// 2004, 08, 07 sobeit add end
//	

	// 2004, 10, 27, sobeit add start - 그레이트 러피언 관련 스킬
	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_BODY].Set("SKILL_CLIENT_GREAT_RUFFIAN_BODY",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_STAND]);
	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_BODY].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_BODY].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_BODY][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_BODY][0].EffectSpriteType = EFFECTSPRITETYPE_GREAT_RUFFIAN_2_BODY;
	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_BODY][0].Step						= 30;
	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_BODY][0].Count					= 0xffff/*FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_2_BODY]*/;

	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_DIE].Set("SKILL_CLIENT_GREAT_RUFFIAN_DIE",ACTION_DIE,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_DIE]);
	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_DIE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_DIE].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_DIE][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_DIE][0].EffectSpriteType = EFFECTSPRITETYPE_GREAT_RUFFIAN_2_DIE;
	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_DIE][0].Step						= 30;
	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_DIE][0].Count					=FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_2_DIE];

	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_ALIVE].Set("SKILL_CLIENT_GREAT_RUFFIAN_ALIVE",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_STAND]);
	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_ALIVE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_ALIVE].Init( 2 );
	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_ALIVE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_ALIVE][0].EffectSpriteType = EFFECTSPRITETYPE_GREAT_RUFFIAN_2_ALIVE_BACK;
	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_ALIVE][0].Step						= 30;
	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_ALIVE][0].Count					=FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_2_ALIVE_BACK];
	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_ALIVE][0].LinkCount		= 0;
	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_ALIVE][1].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_ALIVE][1].EffectSpriteType = EFFECTSPRITETYPE_GREAT_RUFFIAN_2_ALIVE_FRONT;
	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_ALIVE][1].Step						= 30;
	(*g_pActionInfoTable)[SKILL_CLIENT_GREAT_RUFFIAN_ALIVE][1].Count					=FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_2_ALIVE_FRONT];

	
	(*g_pActionInfoTable)[SKILL_CHOPPING_FIREWOOD].Set("SKILL_CHOPPING_FIREWOOD", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_ATTACK]);	
	(*g_pActionInfoTable)[SKILL_CHOPPING_FIREWOOD].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_CHOPPING_FIREWOOD].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CHOPPING_FIREWOOD].SetStartFrameAll( 14 );
	(*g_pActionInfoTable)[SKILL_CHOPPING_FIREWOOD].SetCastingStartFrameAll( 14 );	// 불꽃이 붙는 frame
	(*g_pActionInfoTable)[SKILL_CHOPPING_FIREWOOD].Init( 2 );
	(*g_pActionInfoTable)[SKILL_CHOPPING_FIREWOOD][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_CHOPPING_FIREWOOD][0].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_1_AXE_GROUND;
	(*g_pActionInfoTable)[SKILL_CHOPPING_FIREWOOD][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CHOPPING_FIREWOOD][0].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_1_AXE_GROUND];
	(*g_pActionInfoTable)[SKILL_CHOPPING_FIREWOOD][0].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_CHOPPING_FIREWOOD][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_CHOPPING_FIREWOOD][1].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_1_AXE_WAVE;
	(*g_pActionInfoTable)[SKILL_CHOPPING_FIREWOOD][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CHOPPING_FIREWOOD][1].SoundID			= SOUND_GREAT_RUFFIAN_AXE;
	(*g_pActionInfoTable)[SKILL_CHOPPING_FIREWOOD][1].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_1_AXE_WAVE];


	(*g_pActionInfoTable)[RESULT_SKILL_CHOPPING_FIREWOOD].Set("RESULT_SKILL_CHOPPING_FIREWOOD", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[RESULT_SKILL_CHOPPING_FIREWOOD].SetSoundID( SOUNDID_NULL );
	
	(*g_pActionInfoTable)[SKILL_THROWING_AXE].Set("SKILL_THROWING_AXE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);	
	(*g_pActionInfoTable)[SKILL_THROWING_AXE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_THROWING_AXE].Init( 3 );
	(*g_pActionInfoTable)[SKILL_THROWING_AXE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_THROWING_AXE][0].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_2_AXE_THROW;
	(*g_pActionInfoTable)[SKILL_THROWING_AXE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_THROWING_AXE][0].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_2_AXE_THROW];
	(*g_pActionInfoTable)[SKILL_THROWING_AXE][0].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_THROWING_AXE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_THROWING_AXE][1].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_2_AXE_THROW_SHADOW;
	(*g_pActionInfoTable)[SKILL_THROWING_AXE][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_THROWING_AXE][1].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_2_AXE_THROW_SHADOW];
	(*g_pActionInfoTable)[SKILL_THROWING_AXE][1].LinkCount			= 31;
	(*g_pActionInfoTable)[SKILL_THROWING_AXE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_THROWING_AXE][2].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_AXE_CREATE;
	(*g_pActionInfoTable)[SKILL_THROWING_AXE][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_THROWING_AXE][2].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_AXE_CREATE];
	
	(*g_pActionInfoTable)[RESULT_SKILL_THROWING_AXE].Set("RESULT_SKILL_THROWING_AXE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[RESULT_SKILL_THROWING_AXE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_THROWING_AXE].Init( 3 );
	(*g_pActionInfoTable)[RESULT_SKILL_THROWING_AXE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_THROWING_AXE][0].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_1_AXE_GROUND;
	(*g_pActionInfoTable)[RESULT_SKILL_THROWING_AXE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_THROWING_AXE][0].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_1_AXE_GROUND];
	(*g_pActionInfoTable)[RESULT_SKILL_THROWING_AXE][0].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_THROWING_AXE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_THROWING_AXE][1].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_1_AXE_WAVE;
	(*g_pActionInfoTable)[RESULT_SKILL_THROWING_AXE][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_THROWING_AXE][1].SoundID			= SOUND_GREAT_RUFFIAN_AXE;
	(*g_pActionInfoTable)[RESULT_SKILL_THROWING_AXE][1].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_1_AXE_WAVE];
	(*g_pActionInfoTable)[RESULT_SKILL_THROWING_AXE][1].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_THROWING_AXE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_THROWING_AXE][2].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_AXE_CREATE;
	(*g_pActionInfoTable)[RESULT_SKILL_THROWING_AXE][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_THROWING_AXE][2].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_AXE_CREATE];

// 2004, 10, 27, sobeit add end - 그레이트 러피언 관련 스킬

	// 2004, 11, 2, sobeit add start - 그레이트 러피언 관련 스킬

	(*g_pActionInfoTable)[SKILL_MULTI_THROWING_AXE].Set("SKILL_MULTI_THROWING_AXE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);	
	(*g_pActionInfoTable)[SKILL_MULTI_THROWING_AXE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_MULTI_THROWING_AXE].Init( 3 );
	(*g_pActionInfoTable)[SKILL_MULTI_THROWING_AXE][0].EffectGeneratorID	= EFFECTGENERATORID_AROUND_ZONE;
	(*g_pActionInfoTable)[SKILL_MULTI_THROWING_AXE][0].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_2_AXE_THROW;
	(*g_pActionInfoTable)[SKILL_MULTI_THROWING_AXE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_MULTI_THROWING_AXE][0].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_2_AXE_THROW];
	(*g_pActionInfoTable)[SKILL_MULTI_THROWING_AXE][0].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_MULTI_THROWING_AXE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_MULTI_THROWING_AXE][1].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_2_AXE_THROW_SHADOW;
	(*g_pActionInfoTable)[SKILL_MULTI_THROWING_AXE][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_MULTI_THROWING_AXE][1].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_2_AXE_THROW_SHADOW];
	(*g_pActionInfoTable)[SKILL_MULTI_THROWING_AXE][1].LinkCount			= 31;
	(*g_pActionInfoTable)[SKILL_MULTI_THROWING_AXE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_MULTI_THROWING_AXE][2].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_AXE_CREATE;
	(*g_pActionInfoTable)[SKILL_MULTI_THROWING_AXE][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_MULTI_THROWING_AXE][2].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_AXE_CREATE];
	
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_THROWING_AXE].Set("RESULT_SKILL_MULTI_THROWING_AXE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_THROWING_AXE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_THROWING_AXE].Init( 2 );
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_THROWING_AXE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE_AROUND;
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_THROWING_AXE][0].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_1_AXE_GROUND;
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_THROWING_AXE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_THROWING_AXE][0].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_1_AXE_GROUND];
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_THROWING_AXE][0].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_THROWING_AXE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_THROWING_AXE][1].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_1_AXE_WAVE;
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_THROWING_AXE][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_THROWING_AXE][1].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_1_AXE_WAVE];
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_THROWING_AXE][1].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_THROWING_AXE][1].SoundID			= SOUND_GREAT_RUFFIAN_AXE;
//	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_THROWING_AXE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_THROWING_AXE][2].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_AXE_CREATE;
//	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_THROWING_AXE][2].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_THROWING_AXE][2].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_AXE_CREATE];
//


	(*g_pActionInfoTable)[SKILL_PLAYING_WITH_FIRE].Set("SKILL_PLAYING_WITH_FIRE", ACTION_DRAINED, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_DRAINED]);
	(*g_pActionInfoTable)[SKILL_PLAYING_WITH_FIRE].SetStartFrameAll( 13 );
	(*g_pActionInfoTable)[SKILL_PLAYING_WITH_FIRE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_PLAYING_WITH_FIRE].Init( 16 );		
	(*g_pActionInfoTable)[SKILL_PLAYING_WITH_FIRE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_FIRE_PIERCING );	// 맞는 결과를 표현한다.	
	for( int i = 0; i < 16; i++)
	{
		(*g_pActionInfoTable)[SKILL_PLAYING_WITH_FIRE][i].EffectGeneratorID	= EFFECTGENERATORID_PLAYING_WITH_FIRE;
		(*g_pActionInfoTable)[SKILL_PLAYING_WITH_FIRE][i].EffectSpriteType		= EFFECTSPRITETYPE_FIRE_1;
		(*g_pActionInfoTable)[SKILL_PLAYING_WITH_FIRE][i].Step					= 25;
		(*g_pActionInfoTable)[SKILL_PLAYING_WITH_FIRE][i].Count				= FrameSize[EFFECTSPRITETYPE_FIRE_1];
		(*g_pActionInfoTable)[SKILL_PLAYING_WITH_FIRE][i].LinkCount = 2;
	}

	(*g_pActionInfoTable)[RESULT_SKILL_PLAYING_WITH_FIRE].Set("RESULT_SKILL_PLAYING_WITH_FIRE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[RESULT_SKILL_PLAYING_WITH_FIRE].SetSoundID( SOUNDID_NULL );

	
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE].Set("SKILL_CHAIN_THROWING_AXE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);	
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE].Init( 7 );

	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][0].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_2_AXE_THROW;
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][0].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_2_AXE_THROW];
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][0].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][1].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_2_AXE_THROW_SHADOW;
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][1].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_2_AXE_THROW_SHADOW];
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][1].LinkCount			= 3;

	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][2].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_2_AXE_THROW;
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][2].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_2_AXE_THROW];
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][2].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][3].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][3].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_2_AXE_THROW_SHADOW;
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][3].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][3].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_2_AXE_THROW_SHADOW];
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][3].LinkCount			= 3;

	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][4].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][4].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_2_AXE_THROW;
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][4].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][4].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_2_AXE_THROW];
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][4].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][5].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][5].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_2_AXE_THROW_SHADOW;
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][5].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][5].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_2_AXE_THROW_SHADOW];
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][5].LinkCount			= 28;

	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][6].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][6].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_AXE_CREATE;
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][6].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CHAIN_THROWING_AXE][6].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_AXE_CREATE];

	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE].Set("RESULT_SKILL_CHAIN_THROWING_AXE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE].Init( 4 );
	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE][0].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_1_AXE_GROUND;
	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE][0].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_1_AXE_GROUND];
	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE][0].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE][1].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_1_AXE_WAVE;
	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE][1].SoundID			= SOUND_GREAT_RUFFIAN_AXE;
	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE][1].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_1_AXE_WAVE];
	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE][1].LinkCount			= 4;
	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE][2].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_1_AXE_WAVE;
	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE][2].SoundID			= SOUND_GREAT_RUFFIAN_AXE;
	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE][2].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_1_AXE_WAVE];
	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE][2].LinkCount			= 4;
	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE][3].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE][3].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_1_AXE_WAVE;
	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE][3].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE][3].SoundID			= SOUND_GREAT_RUFFIAN_AXE;
	(*g_pActionInfoTable)[RESULT_SKILL_CHAIN_THROWING_AXE][3].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_1_AXE_WAVE];



	// 2004, 11, 2, sobeit add end - 그레이트 러피언 관련 스킬

	
	(*g_pActionInfoTable)[SKILL_NOOSE_OF_WRAITH].Set("SKILL_NOOSE_OF_WRAITH", ACTION_MAGIC/*ACTION_VAMPIRE_MAGIC_CASTING*/, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_NOOSE_OF_WRAITH].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_NOOSE_OF_WRAITH].SetStartWithCasting();

	(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH].Set("RESULT_SKILL_NOOSE_OF_WRAITH", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH][0].EffectSpriteType	= EFFECTSPRITETYPE_NOOSE_OF_WRAITH_RISE;
	(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH][0].Count				= FrameSize[EFFECTSPRITETYPE_NOOSE_OF_WRAITH_RISE];
	(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH][0].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH][1].EffectSpriteType	= EFFECTSPRITETYPE_NOOSE_OF_WRAITH_GROUND_SHAPE;
	(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH][1].Count				= FrameSize[EFFECTSPRITETYPE_NOOSE_OF_WRAITH_GROUND_SHAPE];
	(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH][1].LinkCount			=  8;
	(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH][2].EffectSpriteType	= EFFECTSPRITETYPE_NEW_NOOSE_OF_WRAITH ; //EFFECTSPRITETYPE_NOOSE_OF_WRAITH_BLOW;
	(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH][2].Count				= FrameSize[EFFECTSPRITETYPE_NEW_NOOSE_OF_WRAITH] ; //EFFECTSPRITETYPE_NOOSE_OF_WRAITH_BLOW];
	(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH][2].LinkCount			= 0;

	
	//(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	//(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH][2].EffectSpriteType	= EFFECTSPRITETYPE_NOOSE_OF_WRAITH_GROUND_SPREAD;
	//(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH][2].Step				= 25;
//	/(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH][2].Count				= FrameSize[EFFECTSPRITETYPE_NOOSE_OF_WRAITH_GROUND_SPREAD];

//	(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH][3].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH][3].EffectSpriteType		= EFFECTSPRITETYPE_NOOSE_OF_WRAITH_GROUND_SPREAD;
//	(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH][3].Step					= 25;
//	(*g_pActionInfoTable)[RESULT_SKILL_NOOSE_OF_WRAITH][3].Count				= FrameSize[EFFECTSPRITETYPE_NOOSE_OF_WRAITH_GROUND_SPREAD];

	(*g_pActionInfoTable)[SKILL_SET_AFIRE].Set("SKILL_SET_AFIRE", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_SET_AFIRE].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_SET_AFIRE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_SET_AFIRE].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_SET_AFIRE].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_SET_AFIRE].Init( 3 );		
	(*g_pActionInfoTable)[SKILL_SET_AFIRE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_SET_AFIRE][0].EffectSpriteType	= EFFECTSPRITETYPE_SET_AFIRE_START_SCREEN;
	(*g_pActionInfoTable)[SKILL_SET_AFIRE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SET_AFIRE][0].Count				= FrameSize[EFFECTSPRITETYPE_SET_AFIRE_START];
	(*g_pActionInfoTable)[SKILL_SET_AFIRE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_SET_AFIRE][1].EffectSpriteType	= EFFECTSPRITETYPE_SET_AFIRE_LOOP_SCREEN;
	(*g_pActionInfoTable)[SKILL_SET_AFIRE][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SET_AFIRE][1].Count				= FrameSize[EFFECTSPRITETYPE_SET_AFIRE_LOOP];
	(*g_pActionInfoTable)[SKILL_SET_AFIRE][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_SET_AFIRE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_SET_AFIRE][2].EffectSpriteType	= EFFECTSPRITETYPE_SET_AFIRE_END_SCREEN;
	(*g_pActionInfoTable)[SKILL_SET_AFIRE][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SET_AFIRE][2].Count				= FrameSize[EFFECTSPRITETYPE_SET_AFIRE_END];
	
	(*g_pActionInfoTable)[RESULT_SKILL_SET_AFIRE].Set("RESULT_SKILL_SET_AFIRE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[RESULT_SKILL_SET_AFIRE].SetSoundID( SOUNDID_NULL );


	// 2004, 12, 23, sobeit add start  - 자폭병
	(*g_pActionInfoTable)[SKILL_SELF_DESTRUCTION].Set("SKILL_SELF_DESTRUCTION", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET , VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_SELF_DESTRUCTION].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_SELF_DESTRUCTION].Init( 1 );
	(*g_pActionInfoTable)[SKILL_SELF_DESTRUCTION][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_SELF_DESTRUCTION][0].EffectSpriteType = EFFECTSPRITETYPE_SELF_DESTRUCTION_BLOW;
	(*g_pActionInfoTable)[SKILL_SELF_DESTRUCTION][0].SoundID			 = SOUND_ITEM_BOOM4;
	(*g_pActionInfoTable)[SKILL_SELF_DESTRUCTION][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SELF_DESTRUCTION][0].Count				= FrameSize[EFFECTSPRITETYPE_SELF_DESTRUCTION_BLOW];

	(*g_pActionInfoTable)[RESULT_SKILL_SELF_DESTRUCTION].Set("RESULT_SKILL_SELF_DESTRUCTION", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[RESULT_SKILL_SELF_DESTRUCTION].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[SKILL_CANNONADE].Set("SKILL_CANNONADE", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_CANNONADE].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_CANNONADE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CANNONADE].SetStartFrameAll( 18 );	
	(*g_pActionInfoTable)[SKILL_CANNONADE].SetCastingStartFrameAll( 18 );	
	(*g_pActionInfoTable)[SKILL_CANNONADE].SetAttachSelf();
	//(*g_pActionInfoTable)[SKILL_CANNONADE].SetCastingAction();
	(*g_pActionInfoTable)[SKILL_CANNONADE].Init( 3 );
	(*g_pActionInfoTable)[SKILL_CANNONADE][2].EffectGeneratorID = EFFECTGENERATORID_ATTACK_ZONE_PARABOLA;
	(*g_pActionInfoTable)[SKILL_CANNONADE][2].EffectSpriteType = EFFECTSPRITETYPE_CANNONADE_BALL;
	(*g_pActionInfoTable)[SKILL_CANNONADE][2].SoundID			 = SOUND_GEFREITER_ATTACK;
	(*g_pActionInfoTable)[SKILL_CANNONADE][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CANNONADE][2].Count				= 18/*FrameSize[EFFECTSPRITETYPE_CANNONADE_BALL]*/;
	(*g_pActionInfoTable)[SKILL_CANNONADE][2].SetResultTime();
	(*g_pActionInfoTable)[SKILL_CANNONADE][2].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_CANNONADE][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CANNONADE][1].EffectSpriteType = EFFECTSPRITETYPE_CANNONADE_DUST;
	(*g_pActionInfoTable)[SKILL_CANNONADE][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CANNONADE][1].Count				= FrameSize[EFFECTSPRITETYPE_CANNONADE_DUST];
	(*g_pActionInfoTable)[SKILL_CANNONADE][1].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_CANNONADE][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CANNONADE][0].EffectSpriteType = EFFECTSPRITETYPE_CANNONADE_SPARK;
	(*g_pActionInfoTable)[SKILL_CANNONADE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CANNONADE][0].Count				= FrameSize[EFFECTSPRITETYPE_CANNONADE_SPARK];
	(*g_pActionInfoTable)[SKILL_CANNONADE][0].LinkCount			= 0;
	
//	(*g_pActionInfoTable)[SKILL_CANNONADE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, RESULT_SKILL_CANNONADE );	// 맞는 결과를 표현한다.	
//
	(*g_pActionInfoTable)[RESULT_SKILL_CANNONADE].Set("RESULT_SKILL_CANNONADE", /*ACTION_DAMAGED*/ACTION_STAND, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_DAMAGED]);
	(*g_pActionInfoTable)[RESULT_SKILL_CANNONADE].SetSoundID( SOUNDID_NULL );
//	(*g_pActionInfoTable)[RESULT_SKILL_CANNONADE].Set("RESULT_SKILL_GUN_SHOT_GUIDANCE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
//	(*g_pActionInfoTable)[RESULT_SKILL_CANNONADE].SetStartWithCasting();
//	(*g_pActionInfoTable)[RESULT_SKILL_CANNONADE].Init( 3 );
//	(*g_pActionInfoTable)[RESULT_SKILL_CANNONADE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
//	(*g_pActionInfoTable)[RESULT_SKILL_CANNONADE][0].EffectSpriteType	= EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_WAVE;
//	(*g_pActionInfoTable)[RESULT_SKILL_CANNONADE][0].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_SKILL_CANNONADE][0].Count				= FrameSize[EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_WAVE];
//	(*g_pActionInfoTable)[RESULT_SKILL_CANNONADE][0].SoundID			= SOUND_ITEM_BOOM4;
//	(*g_pActionInfoTable)[RESULT_SKILL_CANNONADE][0].LinkCount			= 0;
//	(*g_pActionInfoTable)[RESULT_SKILL_CANNONADE][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[RESULT_SKILL_CANNONADE][1].EffectSpriteType	= EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_BOOM;
//	(*g_pActionInfoTable)[RESULT_SKILL_CANNONADE][1].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_SKILL_CANNONADE][1].Count				= FrameSize[EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_BOOM];
//	(*g_pActionInfoTable)[RESULT_SKILL_CANNONADE][1].LinkCount			= 2;
//	(*g_pActionInfoTable)[RESULT_SKILL_CANNONADE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
//	(*g_pActionInfoTable)[RESULT_SKILL_CANNONADE][2].EffectSpriteType	= EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_PIT;
//	(*g_pActionInfoTable)[RESULT_SKILL_CANNONADE][2].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_SKILL_CANNONADE][2].Count				= FrameSize[EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_PIT];


	// 783 ar monster fire
	(*g_pActionInfoTable)[SKILL_AR_ATTACK].Set("SKILL_AR_ATTACK", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER , VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_AR_ATTACK].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_AR_ATTACK].SetStartFrameAll( 6 );	
	(*g_pActionInfoTable)[SKILL_AR_ATTACK].SetCastingStartFrameAll( 6 );
	(*g_pActionInfoTable)[SKILL_AR_ATTACK].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_AR_ATTACK].Init( 1 );
	(*g_pActionInfoTable)[SKILL_AR_ATTACK][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_AR_ATTACK][0].EffectSpriteType = EFFECTSPRITETYPE_AR_FIRE;
	(*g_pActionInfoTable)[SKILL_AR_ATTACK][0].SoundID			 = SOUND_SLAYER_ATTACK_AR;
	(*g_pActionInfoTable)[SKILL_AR_ATTACK][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_AR_ATTACK][0].Count				= FrameSize[EFFECTSPRITETYPE_AR_FIRE];

	(*g_pActionInfoTable)[RESULT_SKILL_AR_ATTACK].Set("RESULT_SKILL_AR_ATTACK", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_DAMAGED]);
	(*g_pActionInfoTable)[RESULT_SKILL_AR_ATTACK].SetSoundID( SOUNDID_NULL );

	// 784 smg monster fire
	(*g_pActionInfoTable)[SKILL_SMG_ATTACK].Set("SKILL_SMG_ATTACK", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER , VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_SMG_ATTACK].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_SMG_ATTACK].SetStartFrameAll( 5 );	
	(*g_pActionInfoTable)[SKILL_SMG_ATTACK].SetCastingStartFrameAll( 5 );
	(*g_pActionInfoTable)[SKILL_SMG_ATTACK].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_SMG_ATTACK].Init( 1 );
	(*g_pActionInfoTable)[SKILL_SMG_ATTACK][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_SMG_ATTACK][0].EffectSpriteType = EFFECTSPRITETYPE_SMG_FIRE;
	(*g_pActionInfoTable)[SKILL_SMG_ATTACK][0].SoundID			 = SOUND_STURMMANN_SMG_ATTACK;
	(*g_pActionInfoTable)[SKILL_SMG_ATTACK][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SMG_ATTACK][0].Count				= FrameSize[EFFECTSPRITETYPE_SMG_FIRE]*3;

	(*g_pActionInfoTable)[RESULT_SKILL_SMG_ATTACK].Set("RESULT_SKILL_SMG_ATTACK", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_DAMAGED]);
	(*g_pActionInfoTable)[RESULT_SKILL_SMG_ATTACK].SetSoundID( SOUNDID_NULL );

	// 783 몬스터 수류탄 던지기
	(*g_pActionInfoTable)[SKILL_GRENADE_ATTACK].Set("SKILL_GRENADE_ATTACK", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER , VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_GRENADE_ATTACK].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_GRENADE_ATTACK].SetStartFrameAll( 12 );	
	(*g_pActionInfoTable)[SKILL_GRENADE_ATTACK].SetCastingStartFrameAll( 12 );
	(*g_pActionInfoTable)[SKILL_GRENADE_ATTACK].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_GRENADE_ATTACK].Init( 1 );
	(*g_pActionInfoTable)[SKILL_GRENADE_ATTACK][0].EffectGeneratorID = EFFECTGENERATORID_ATTACK_ZONE_PARABOLA;
	(*g_pActionInfoTable)[SKILL_GRENADE_ATTACK][0].EffectSpriteType = EFFECTSPRITETYPE_CANNONADE_BALL;
	(*g_pActionInfoTable)[SKILL_GRENADE_ATTACK][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_GRENADE_ATTACK][0].Count				= 18/*FrameSize[EFFECTSPRITETYPE_CANNONADE_BALL]*/;
	
//
//	(*g_pActionInfoTable)[RESULT_SKILL_GRENADE_ATTACK].Set("RESULT_SKILL_GRENADE_ATTACK", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_DAMAGED]);
//	(*g_pActionInfoTable)[RESULT_SKILL_GRENADE_ATTACK].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_GRENADE_ATTACK].Set("RESULT_SKILL_GUN_SHOT_GUIDANCE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_SKILL_GRENADE_ATTACK].SetStartWithCasting();
//	(*g_pActionInfoTable)[RESULT_SKILL_GRENADE_ATTACK].Init( 3 );
//	(*g_pActionInfoTable)[RESULT_SKILL_GRENADE_ATTACK][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
//	(*g_pActionInfoTable)[RESULT_SKILL_GRENADE_ATTACK][0].EffectSpriteType	= EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_WAVE;
//	(*g_pActionInfoTable)[RESULT_SKILL_GRENADE_ATTACK][0].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_SKILL_GRENADE_ATTACK][0].Count				= FrameSize[EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_WAVE];
//	(*g_pActionInfoTable)[RESULT_SKILL_GRENADE_ATTACK][0].SoundID			= SOUND_ITEM_BOOM4;
//	(*g_pActionInfoTable)[RESULT_SKILL_GRENADE_ATTACK][0].LinkCount			= 0;
//	(*g_pActionInfoTable)[RESULT_SKILL_GRENADE_ATTACK][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[RESULT_SKILL_GRENADE_ATTACK][1].EffectSpriteType	= EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_BOOM;
//	(*g_pActionInfoTable)[RESULT_SKILL_GRENADE_ATTACK][1].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_SKILL_GRENADE_ATTACK][1].Count				= FrameSize[EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_BOOM];
//	(*g_pActionInfoTable)[RESULT_SKILL_GRENADE_ATTACK][1].LinkCount			= 2;
//	(*g_pActionInfoTable)[RESULT_SKILL_GRENADE_ATTACK][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
//	(*g_pActionInfoTable)[RESULT_SKILL_GRENADE_ATTACK][2].EffectSpriteType	= EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_PIT;
//	(*g_pActionInfoTable)[RESULT_SKILL_GRENADE_ATTACK][2].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_SKILL_GRENADE_ATTACK][2].Count				= FrameSize[EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_PIT];

	// 2004, 12, 23, sobeit add end

	(*g_pActionInfoTable)[SKILL_ABERRATION].Set("SKILL_ABERRATION", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_ABERRATION].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_ABERRATION].SetStartWithCasting();

	(*g_pActionInfoTable)[RESULT_SKILL_ABERRATION].Set("RESULT_SKILL_ABERRATION", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_ABERRATION].SetSoundID( SOUND_VAMPIRE_ABERRATION );

	(*g_pActionInfoTable)[SKILL_WILD_WOLF].Set("SKILL_WILD_WOLF", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_WILD_WOLF].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_WILD_WOLF].SetStartWithCasting();

	(*g_pActionInfoTable)[RESULT_SKILL_WILD_WOLF].Set("RESULT_SKILL_WILD_WOLF", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_WILD_WOLF].SetSoundID( SOUNDID_NULL );
	
	(*g_pActionInfoTable)[SKILL_TRASLA_ATTACK].Set("SKILL_TRASLA_ATTACK", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[SKILL_TRASLA_ATTACK].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_TRASLA_ATTACK].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TRASLA_ATTACK].SetStartFrameAll( 9 );	
	(*g_pActionInfoTable)[SKILL_TRASLA_ATTACK].SetCastingStartFrameAll( 9 );
	(*g_pActionInfoTable)[SKILL_TRASLA_ATTACK].SetAttachSelf();
//	(*g_pActionInfoTable)[SKILL_TRASLA_ATTACK].Init( 1 );
//	(*g_pActionInfoTable)[SKILL_TRASLA_ATTACK][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[SKILL_TRASLA_ATTACK][0].EffectSpriteType = EFFECTSPRITETYPE_PLASMA_ROCKET_LAUNCHER_FIRE;
//	(*g_pActionInfoTable)[SKILL_TRASLA_ATTACK][0].Step				= 25;
//	(*g_pActionInfoTable)[SKILL_TRASLA_ATTACK][0].Count				= FrameSize[EFFECTSPRITETYPE_PLASMA_ROCKET_LAUNCHER_FIRE];

	(*g_pActionInfoTable)[RESULT_SKILL_TRASLA_ATTACK].Set("RESULT_SKILL_TRASLA_ATTACK", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_TRASLA_ATTACK].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_TRASLA_ATTACK].Init( 3 );
	(*g_pActionInfoTable)[RESULT_SKILL_TRASLA_ATTACK][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_TRASLA_ATTACK][0].EffectSpriteType	= EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_WAVE;
	(*g_pActionInfoTable)[RESULT_SKILL_TRASLA_ATTACK][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_TRASLA_ATTACK][0].Count				= FrameSize[EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_WAVE];
	(*g_pActionInfoTable)[RESULT_SKILL_TRASLA_ATTACK][0].SoundID			= SOUND_ITEM_BOOM4;
	(*g_pActionInfoTable)[RESULT_SKILL_TRASLA_ATTACK][0].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_TRASLA_ATTACK][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_TRASLA_ATTACK][1].EffectSpriteType	= EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_BOOM;
	(*g_pActionInfoTable)[RESULT_SKILL_TRASLA_ATTACK][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_TRASLA_ATTACK][1].Count				= FrameSize[EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_BOOM];
//	(*g_pActionInfoTable)[RESULT_SKILL_TRASLA_ATTACK][1].SoundID			= SOUND_SLAYER_ENCHANT_CHW2;
	(*g_pActionInfoTable)[RESULT_SKILL_TRASLA_ATTACK][1].LinkCount			= 2;
	(*g_pActionInfoTable)[RESULT_SKILL_TRASLA_ATTACK][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_TRASLA_ATTACK][2].EffectSpriteType	= EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_PIT;
	(*g_pActionInfoTable)[RESULT_SKILL_TRASLA_ATTACK][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_TRASLA_ATTACK][2].Count				= FrameSize[EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_PIT];
//	(*g_pActionInfoTable)[RESULT_SKILL_TRASLA_ATTACK][2].SoundID			= SOUND_SLAYER_ENCHANT_CHW2;


	(*g_pActionInfoTable)[SKILL_PUSCA_ATTACK].Set("SKILL_PUSCA_ATTACK", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[SKILL_PUSCA_ATTACK].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_PUSCA_ATTACK].SetStartFrameAll( 15 );	
	(*g_pActionInfoTable)[SKILL_PUSCA_ATTACK].SetCastingStartFrameAll( 15 );
	(*g_pActionInfoTable)[SKILL_PUSCA_ATTACK].SetAttachSelf();
//	(*g_pActionInfoTable)[SKILL_PUSCA_ATTACK].Init( 1 );
//	(*g_pActionInfoTable)[SKILL_PUSCA_ATTACK][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[SKILL_PUSCA_ATTACK][0].EffectSpriteType = EFFECTSPRITETYPE_PLASMA_ROCKET_LAUNCHER_FIRE;
//	(*g_pActionInfoTable)[SKILL_PUSCA_ATTACK][0].Step				= 25;
//	(*g_pActionInfoTable)[SKILL_PUSCA_ATTACK][0].Count				= FrameSize[EFFECTSPRITETYPE_PLASMA_ROCKET_LAUNCHER_FIRE];

	(*g_pActionInfoTable)[RESULT_SKILL_PUSCA_ATTACK].Set("RESULT_SKILL_PUSCA_ATTACK", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_PUSCA_ATTACK].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_PUSCA_ATTACK].Init( 3 );
	(*g_pActionInfoTable)[RESULT_SKILL_PUSCA_ATTACK][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_PUSCA_ATTACK][0].EffectSpriteType	= EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_WAVE;
	(*g_pActionInfoTable)[RESULT_SKILL_PUSCA_ATTACK][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_PUSCA_ATTACK][0].Count				= FrameSize[EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_WAVE];
	(*g_pActionInfoTable)[RESULT_SKILL_PUSCA_ATTACK][0].SoundID			= SOUND_ITEM_BOOM4;
	(*g_pActionInfoTable)[RESULT_SKILL_PUSCA_ATTACK][0].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_PUSCA_ATTACK][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_PUSCA_ATTACK][1].EffectSpriteType	= EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_BOOM;
	(*g_pActionInfoTable)[RESULT_SKILL_PUSCA_ATTACK][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_PUSCA_ATTACK][1].Count				= FrameSize[EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_BOOM];
//	(*g_pActionInfoTable)[RESULT_SKILL_PUSCA_ATTACK][1].SoundID			= SOUND_SLAYER_ENCHANT_CHW2;
	(*g_pActionInfoTable)[RESULT_SKILL_PUSCA_ATTACK][1].LinkCount			= 2;
	(*g_pActionInfoTable)[RESULT_SKILL_PUSCA_ATTACK][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_PUSCA_ATTACK][2].EffectSpriteType	= EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_PIT;
	(*g_pActionInfoTable)[RESULT_SKILL_PUSCA_ATTACK][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_PUSCA_ATTACK][2].Count				= FrameSize[EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_PIT];
//	(*g_pActionInfoTable)[RESULT_SKILL_PUSCA_ATTACK][2].SoundID			= SOUND_SLAYER_ENCHANT_CHW2;

	(*g_pActionInfoTable)[SKILL_NOD_COPILA_ATTACK].Set("SKILL_NOD_COPILA_ATTACK", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_NOD_COPILA_ATTACK].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_NOD_COPILA_ATTACK].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_NOD_COPILA_ATTACK].SetStartWithCasting();

	(*g_pActionInfoTable)[RESULT_SKILL_NOD_COPILA_ATTACK].Set("RESULT_SKILL_NOD_COPILA_ATTACK", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_NOD_COPILA_ATTACK].SetSoundID( SOUNDID_NULL );
	
	(*g_pActionInfoTable)[SKILL_NOD_COPILA_ATTACK_2].Set("SKILL_NOD_COPILA_ATTACK_2", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_NOD_COPILA_ATTACK_2].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_NOD_COPILA_ATTACK_2].SetStartWithCasting();

	(*g_pActionInfoTable)[RESULT_SKILL_NOD_COPILA_ATTACK_2].Set("RESULT_SKILL_NOD_COPILA_ATTACK_2", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_NOD_COPILA_ATTACK_2].SetSoundID( SOUNDID_NULL );

	// sjheon 2005.04.26 스킬 이펙트 add
	(*g_pActionInfoTable)[SKILL_UNTERFELDWEBEL_FIRE].Set( "SKILL_UNTERFELDWEBEL_FIRE", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[SKILL_UNTERFELDWEBEL_FIRE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_UNTERFELDWEBEL_FIRE].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_UNTERFELDWEBEL_FIRE].SetCastingStartFrameAll(12);
	(*g_pActionInfoTable)[SKILL_UNTERFELDWEBEL_FIRE].SetStartFrameAll(12);
	(*g_pActionInfoTable)[SKILL_UNTERFELDWEBEL_FIRE].Init(2);
	(*g_pActionInfoTable)[SKILL_UNTERFELDWEBEL_FIRE].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_UNTERFELDWEBEL_FIRE][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_UNTERFELDWEBEL_FIRE][0].EffectSpriteType = EFFECTSPRITETYPE_BALKANS_EMPTY_CARTRIDGE;
	(*g_pActionInfoTable)[SKILL_UNTERFELDWEBEL_FIRE][0].Step = 0;
	(*g_pActionInfoTable)[SKILL_UNTERFELDWEBEL_FIRE][0].Count = FrameSize[EFFECTSPRITETYPE_BALKANS_EMPTY_CARTRIDGE];    
	(*g_pActionInfoTable)[SKILL_UNTERFELDWEBEL_FIRE][0].LinkCount			= 5;
		;
	(*g_pActionInfoTable)[SKILL_UNTERFELDWEBEL_FIRE][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_UNTERFELDWEBEL_FIRE][1].EffectSpriteType = EFFECTSPRITETYPE_UNTERFELDWEBEL_BALKANS_FIRE;
	(*g_pActionInfoTable)[SKILL_UNTERFELDWEBEL_FIRE][1].Step = 0;
	(*g_pActionInfoTable)[SKILL_UNTERFELDWEBEL_FIRE][1].Count = 10;
	
	
	(*g_pActionInfoTable)[RESULT_SKILL_UNTERFELDWEBEL_FIRE].Set("RESULT_SKILL_UNTERFELDWEBEL_FIRE", ACTION_DAMAGED /*ACTION_ATTACK*/, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_UNTERFELDWEBEL_FIRE].SetSoundID( SOUNDID_NULL );
	

	(*g_pActionInfoTable)[SKILL_FELDWEBEL_FIRE].Set( "SKILL_FELDWEBEL_FIRE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[SKILL_FELDWEBEL_FIRE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_FELDWEBEL_FIRE].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_FELDWEBEL_FIRE].SetCastingStartFrameAll(5);
	(*g_pActionInfoTable)[SKILL_FELDWEBEL_FIRE].SetStartFrameAll(5);
	(*g_pActionInfoTable)[SKILL_FELDWEBEL_FIRE].Init(1);
	(*g_pActionInfoTable)[SKILL_FELDWEBEL_FIRE].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_FELDWEBEL_FIRE][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_FELDWEBEL_FIRE][0].EffectSpriteType = EFFECTSPRITETYPE_FELDWEBEL_CLAYDOLL_FIRE;
	(*g_pActionInfoTable)[SKILL_FELDWEBEL_FIRE][0].Step = 0;
	(*g_pActionInfoTable)[SKILL_FELDWEBEL_FIRE][0].Count = FrameSize[EFFECTSPRITETYPE_FELDWEBEL_CLAYDOLL_FIRE];    

	(*g_pActionInfoTable)[RESULT_SKILL_FELDWEBEL_FIRE].Set("RESULT_SKILL_FELDWEBEL_FIRE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_FELDWEBEL_FIRE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_FELDWEBEL_FIRE].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_FELDWEBEL_FIRE].SetCastingStartFrameAll(12);
	(*g_pActionInfoTable)[RESULT_SKILL_FELDWEBEL_FIRE].SetStartFrameAll(12);
	(*g_pActionInfoTable)[RESULT_SKILL_FELDWEBEL_FIRE].Init(2);
	(*g_pActionInfoTable)[RESULT_SKILL_FELDWEBEL_FIRE].SetAttachSelf();
	(*g_pActionInfoTable)[RESULT_SKILL_FELDWEBEL_FIRE][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_FELDWEBEL_FIRE][0].EffectSpriteType = EFFECTSPRITETYPE_EXPLOSION_3;
	(*g_pActionInfoTable)[RESULT_SKILL_FELDWEBEL_FIRE][0].Step = 0;
	(*g_pActionInfoTable)[RESULT_SKILL_FELDWEBEL_FIRE][0].Count = FrameSize[EFFECTSPRITETYPE_EXPLOSION_3];    
	

	// sjheon 2005.04.26 스킬 이펙트 End


	// SKILL_FEEBLE_VIRUS Action Add Sjheon 2005.06.02

	(*g_pActionInfoTable)[SKILL_FEEBLE_VIRUS].Set( "SKILL_FEEBLE_VIRUS",ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_FEEBLE_VIRUS].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_FEEBLE_VIRUS].SetStartWithCasting();

	

	(*g_pActionInfoTable)[RESULT_SKILL_FEEBLE_VIRUS].Set("RESULT_SKILL_FEEBLE_VIRUS", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_FEEBLE_VIRUS].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_FEEBLE_VIRUS].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_FEEBLE_VIRUS].SetAttachSelf();
	(*g_pActionInfoTable)[RESULT_SKILL_FEEBLE_VIRUS].Init( 3 );
	//(*g_pActionInfoTable)[RESULT_SKILL_FEEBLE_VIRUS].SetMainNode( 1 );
	
	(*g_pActionInfoTable)[RESULT_SKILL_FEEBLE_VIRUS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_FEEBLE_VIRUS][0].EffectSpriteType	= EFFECTSPRITETYPE_FEEBLEVIRUS_LINE_BACK ;
	(*g_pActionInfoTable)[RESULT_SKILL_FEEBLE_VIRUS][0].Step				= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_FEEBLE_VIRUS][0].Count				= FrameSize[EFFECTSPRITETYPE_FEEBLEVIRUS_LINE_BACK];
	(*g_pActionInfoTable)[RESULT_SKILL_FEEBLE_VIRUS][0].LinkCount			= 16;

	(*g_pActionInfoTable)[RESULT_SKILL_FEEBLE_VIRUS][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_FEEBLE_VIRUS][1].EffectSpriteType	= EFFECTSPRITETYPE_FEEBLEVIRUS_SMOKE_END_BACK;
	(*g_pActionInfoTable)[RESULT_SKILL_FEEBLE_VIRUS][1].Step				= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_FEEBLE_VIRUS][1].Count				= FrameSize[EFFECTSPRITETYPE_FEEBLEVIRUS_SMOKE_END_BACK] * 10 ;
	(*g_pActionInfoTable)[RESULT_SKILL_FEEBLE_VIRUS][1].SetResultTime();
	(*g_pActionInfoTable)[RESULT_SKILL_FEEBLE_VIRUS][1].SetDelayNode();

	//(*g_pActionInfoTable)[RESULT_SKILL_FEEBLE_VIRUS][1].LinkCount			= 21;

	(*g_pActionInfoTable)[RESULT_SKILL_FEEBLE_VIRUS][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_FEEBLE_VIRUS][2].EffectSpriteType	= EFFECTSPRITETYPE_FEEBLEVIRUS_SMOKE_RELEASE_BACK;
	(*g_pActionInfoTable)[RESULT_SKILL_FEEBLE_VIRUS][2].Step				= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_FEEBLE_VIRUS][2].Count				= FrameSize[EFFECTSPRITETYPE_FEEBLEVIRUS_SMOKE_RELEASE_BACK];

		
	//2005.07.13, Sjheon ComboSkill add 


	//2005.08.04, Sjheon  폭주 스킬 설정 Add

	(*g_pActionInfoTable)[SKILL_DARK_FORCE].Set("SKILL_DARK_FORCE",ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_DARK_FORCE].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_DARK_FORCE].Set("SKILL_DARK_FORCE",ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[RESULT_SKILL_DARK_FORCE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_DARK_FORCE].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_DARK_FORCE].SetMaleSoundID(SOUND_VAMPIRE_BLOODBURST_ATTATCK_MAIL);
	(*g_pActionInfoTable)[RESULT_SKILL_DARK_FORCE].SetFemaleSoundID(SOUND_VAMPIRE_BLOODBURST_ATTATCK_FEMALE);
	(*g_pActionInfoTable)[RESULT_SKILL_DARK_FORCE].SetAttachSelf();
	(*g_pActionInfoTable)[RESULT_SKILL_DARK_FORCE].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_DARK_FORCE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_DARK_FORCE][0].EffectSpriteType		= EFFECTSPRITETYPE_BLOOD_BURST_START ;
	(*g_pActionInfoTable)[RESULT_SKILL_DARK_FORCE][0].Step					= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_DARK_FORCE][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_BURST_START];
	

	(*g_pActionInfoTable)[SKILL_WIDE_BLOOD_DRAIN].Set("RESULT_SKILL_WIDE_BLOOD_DRAIN", ACTION_VAMPIRE_DRAIN, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[SKILL_WIDE_BLOOD_DRAIN].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_WIDE_BLOOD_DRAIN].Set("RESULT_SKILL_WIDE_BLOOD_DRAIN", ACTION_VAMPIRE_DRAIN, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_WIDE_BLOOD_DRAIN].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_WIDE_BLOOD_DRAIN].SetMaleSoundID(SOUND_VAMPIRE_BLOODBURST_DEFENSE_MAIL);
	(*g_pActionInfoTable)[RESULT_SKILL_WIDE_BLOOD_DRAIN].SetFemaleSoundID(SOUND_VAMPIRE_BLOODBURST_DEFENSE_FEMALE);

	//2005.08.04, Sjheon  폭주 스킬 설정 End
	
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO].Set("SKILL_VAMPIRE_COMBO", ACTION_ATTACK , EFFECTSPRITETYPE_NULL, 0, FLAG_ACTIONINFO_TARGET_OTHER , FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);	
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO].SetStartFrameAll( 4 );
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO].SetComboAttackSkill(TRUE);
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO].SetSoundID( SOUNDID_NULL );
	
	//(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO].SetComboActionResultEffect(SKILL_VAMPIRE_COMBO_EFFECT) ; 
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO].SetComboSkillActionStep(ACTIONINFO_NULL , ACTIONINFO_NULL , ACTIONINFO_NULL ,  SKILL_VAMPIRE_COMBO_EFFECT) ; 
	


	(*g_pActionInfoTable)[RESULT_SKILL_VAMPIRE_COMBO].Set("RESULT_SKILL_VAMPIRE_COMBO", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[RESULT_SKILL_VAMPIRE_COMBO].SetSoundID( SOUNDID_NULL );
	//(*g_pActionInfoTable)[RESULT_SKILL_VAMPIRE_COMBO].Init( 1 );
	//(*g_pActionInfoTable)[RESULT_SKILL_VAMPIRE_COMBO][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	//(*g_pActionInfoTable)[RESULT_SKILL_VAMPIRE_COMBO][0].EffectSpriteType  = EFFECTSPRITETYPE_SHARP_ROUND_1_3;
	//(*g_pActionInfoTable)[RESULT_SKILL_VAMPIRE_COMBO][0].Step			     = 0;
	//(*g_pActionInfoTable)[RESULT_SKILL_VAMPIRE_COMBO][0].Count			 = FrameSize[EFFECTSPRITETYPE_SHARP_ROUND_1_3];


	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT].Set("SKILL_VAMPIRE_COMBO_EFFECT", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_SKY);
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT].SetStartWithCasting();	
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT].Init( 3 );		
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][0].EffectGeneratorID	= EFFECTGENERATORID_METEOR_DROP;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][0].EffectSpriteType	= EFFECTSPRITETYPE_METEOR_DROP;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][0].Step				= 30;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][0].Count				= 19;//FrameSize[EFFECTSPRITETYPE_METEOR_DROP];
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][0].SoundID			= SOUND_ITEM_FLYING_BOTTLE;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][1].EffectSpriteType	= EFFECTSPRITETYPE_METEOR_WAVE;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][1].Count				= FrameSize[EFFECTSPRITETYPE_METEOR_WAVE];
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][1].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][1].SoundID			= SOUND_SLAYER_ATTACK_BOMB;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][1].SetResultTime();
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][2].EffectSpriteType	= EFFECTSPRITETYPE_METEOR_ROCK;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][2].Count				= FrameSize[EFFECTSPRITETYPE_METEOR_ROCK];

	
	
	(*g_pActionInfoTable)[SKILL_BRANDISH].Set( "SKILL_BRANDISH", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 7, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_BRANDISH].SetSoundID( SOUNDID_NULL );
		
	//(*g_pActionInfoTable)[RESULT_SKILL_BRANDISH].Set("RESULT_SKILL_BRANDISH", ACTION_DAMAGED , EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE) ;//, FLAG_ACTIONINFO_START_TARGET) ; //, 400);
	//(*g_pActionInfoTable)[RESULT_SKILL_BRANDISH].SetSoundID( SOUNDID_NULL );
	//(*g_pActionInfoTable)[RESULT_SKILL_BRANDISH].Init( 1 );
	//(*g_pActionInfoTable)[RESULT_SKILL_BRANDISH][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	//(*g_pActionInfoTable)[RESULT_SKILL_BRANDISH][0].EffectSpriteType	= EFFECTSPRITETYPE_MIKLLIZZ_SOUND_WAVE_ATTACK_TYPE_A_FRONT ;
	//(*g_pActionInfoTable)[RESULT_SKILL_BRANDISH][0].Step					    = 0;
	//(*g_pActionInfoTable)[RESULT_SKILL_BRANDISH][0].Count				      = FrameSize[EFFECTSPRITETYPE_MIKLLIZZ_SOUND_WAVE_ATTACK_TYPE_A_FRONT];
	

	(*g_pActionInfoTable)[SKILL_PARASITE].Set("SKILL_PARASITE", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_PARASITE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_PARASITE].SetCastingFramesAll( 16 );
	(*g_pActionInfoTable)[SKILL_PARASITE].SetStartFrameAll( 16 );
	(*g_pActionInfoTable)[SKILL_PARASITE].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_PARASITE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[SKILL_PARASITE][0].EffectSpriteType	= EFFECTSPRITETYPE_MIKLLIZZ_FEELER_THROW;//EFFECTSPRITETYPE_GREEN_STALKER_2;
	(*g_pActionInfoTable)[SKILL_PARASITE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_PARASITE][0].Count				= 2*16;//FrameSize[EFFECTSPRITETYPE_ACID_BOLT_1];	
	
	
	(*g_pActionInfoTable)[RESULT_SKILL_PARASITE].Set("RESULT_SKILL_PARASITE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_PARASITE].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_SKILL_PARASITE].Init( 2 );
	(*g_pActionInfoTable)[RESULT_SKILL_PARASITE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_PARASITE][0].EffectSpriteType	= EFFECTSPRITETYPE_MIKLLIZZ_FEELER_STUCK_FRONT;
	(*g_pActionInfoTable)[RESULT_SKILL_PARASITE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_PARASITE][0].Count				= FrameSize[EFFECTSPRITETYPE_MIKLLIZZ_FEELER_STUCK_FRONT];
	(*g_pActionInfoTable)[RESULT_SKILL_PARASITE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_PARASITE][1].EffectSpriteType	= EFFECTSPRITETYPE_MIKLLIZZ_FEELER_WRIGGLE_REPEAT;
	(*g_pActionInfoTable)[RESULT_SKILL_PARASITE][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_SKILL_PARASITE][1].SetResultTime();
	

	//(*g_pActionInfoTable)[SKILL_PARASITE].Set( "SKILL_PARASITE", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, 400);
	//(*g_pActionInfoTable)[SKILL_PARASITE].SetSoundID( SOUNDID_NULL );
		
	//(*g_pActionInfoTable)[RESULT_SKILL_PARASITE].Set("RESULT_SKILL_PARASITE", ACTION_DAMAGED , EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, 400);
	//(*g_pActionInfoTable)[RESULT_SKILL_PARASITE].SetSoundID( SOUNDID_NULL );
	
	
	(*g_pActionInfoTable)[SKILL_SOUND_WAVE].Set( "SKILL_SOUND_WAVE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF) ;//, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[SKILL_SOUND_WAVE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_SOUND_WAVE].Init( 1 );
	(*g_pActionInfoTable)[SKILL_SOUND_WAVE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;//EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_SOUND_WAVE][0].EffectSpriteType	= EFFECTSPRITETYPE_MIKLLIZZ_SOUND_WAVE_ATTACK_TYPE_B_FRONT ;
	(*g_pActionInfoTable)[SKILL_SOUND_WAVE][0].Step					    = 0;
	(*g_pActionInfoTable)[SKILL_SOUND_WAVE][0].Count				    = FrameSize[EFFECTSPRITETYPE_MIKLLIZZ_SOUND_WAVE_ATTACK_TYPE_B_FRONT];



	
//	(*g_pActionInfoTable)[SKILL_THRUST].Set( "SKILL_THRUST", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, 400);
//	(*g_pActionInfoTable)[SKILL_THRUST].SetSoundID( SOUNDID_NULL );
	
//	(*g_pActionInfoTable)[RESULT_SKILL_THRUST].Set("RESULT_SKILL_THRUST", ACTION_DAMAGED , EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, 400);
//	(*g_pActionInfoTable)[RESULT_SKILL_THRUST].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[SKILL_FIRE_WAVE].Set( "SKILL_FIRE_WAVE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[SKILL_FIRE_WAVE].SetSoundID( SOUNDID_NULL );
	
	

	(*g_pActionInfoTable)[SKILL_CLIENT_FIRE_BREATH].Set("SKILL_CLIENT_FIRE_BREATH", ACTION_STAND , EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[SKILL_CLIENT_FIRE_BREATH].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_FIRE_BREATH].Init( 3 );
	(*g_pActionInfoTable)[SKILL_CLIENT_FIRE_BREATH][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_RHOMBUS;
	(*g_pActionInfoTable)[SKILL_CLIENT_FIRE_BREATH][0].EffectSpriteType	= EFFECTSPRITETYPE_MIKLLIZZ_PILLAR_OF_FIRE_TYPE_A_START ;
	(*g_pActionInfoTable)[SKILL_CLIENT_FIRE_BREATH][0].Step					    = 0;
	(*g_pActionInfoTable)[SKILL_CLIENT_FIRE_BREATH][0].Count				    = FrameSize[EFFECTSPRITETYPE_MIKLLIZZ_PILLAR_OF_FIRE_TYPE_A_START];
	
	(*g_pActionInfoTable)[SKILL_CLIENT_FIRE_BREATH][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_RHOMBUS;
	(*g_pActionInfoTable)[SKILL_CLIENT_FIRE_BREATH][1].EffectSpriteType	= EFFECTSPRITETYPE_MIKLLIZZ_PILLAR_OF_FIRE_TYPE_A_REPEAT ;
	(*g_pActionInfoTable)[SKILL_CLIENT_FIRE_BREATH][1].Step					    = 0;
	(*g_pActionInfoTable)[SKILL_CLIENT_FIRE_BREATH][1].Count				    = FrameSize[EFFECTSPRITETYPE_MIKLLIZZ_PILLAR_OF_FIRE_TYPE_A_REPEAT];
	(*g_pActionInfoTable)[SKILL_CLIENT_FIRE_BREATH][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_FIRE_BREATH][1].SetResultTime();

	(*g_pActionInfoTable)[SKILL_CLIENT_FIRE_BREATH][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_RHOMBUS	;
	(*g_pActionInfoTable)[SKILL_CLIENT_FIRE_BREATH][2].EffectSpriteType	= EFFECTSPRITETYPE_MIKLLIZZ_PILLAR_OF_FIRE_TYPE_A_END ;
	(*g_pActionInfoTable)[SKILL_CLIENT_FIRE_BREATH][2].Step					    = 0;
	(*g_pActionInfoTable)[SKILL_CLIENT_FIRE_BREATH][2].Count				    = FrameSize[EFFECTSPRITETYPE_MIKLLIZZ_PILLAR_OF_FIRE_TYPE_A_END];
	
	(*g_pActionInfoTable)[SKILL_BLOODY_BURST].Set("SKILL_BLOODY_BURST",ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_BLOODY_BURST].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_BURST].Set("RESULT_SKILL_HOLY_SWORD",ACTION_STAND, EFFECTSPRITETYPE_BLOOD_BURST_START, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_BURST].SetSoundID( SOUNDID_NULL );
	
	// 2006.10.31 sjheon
	
	(*g_pActionInfoTable)[SKILL_BLOOD_CURSE].Set("SKILL_BLOOD_CURSE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF , FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_BLOOD_CURSE].SetSoundID( SOUNDID_NULL );
	
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_CURSE].Set("RESULT_SKILL_BLOOD_CURSE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_CURSE].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_CURSE].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_CURSE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_CURSE][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODS_SYMPOSION_START;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_CURSE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_CURSE][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOODS_SYMPOSION_START];
	
	(*g_pActionInfoTable)[SKILL_BLOODS_SYMPOSION_ATTACK].Set("SKILL_BLOODS_SYMPOSION_ATTACK", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER , FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_BLOODS_SYMPOSION_ATTACK].SetSoundID( SOUNDID_NULL );
	
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODS_SYMPOSION_ATTACK].Set("RESULT_SKILL_BLOODS_SYMPOSION_ATTACK", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE,VampireActionDelay[ACTION_DAMAGED]);
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODS_SYMPOSION_ATTACK].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODS_SYMPOSION_ATTACK].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODS_SYMPOSION_ATTACK][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODS_SYMPOSION_ATTACK][0].EffectSpriteType		= EFFECTSPRITETYPE_BLOODS_SYMPOSION_END;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODS_SYMPOSION_ATTACK][0].Step					= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODS_SYMPOSION_ATTACK][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOODS_SYMPOSION_END];
	
	
	
	
/*	(*g_pActionInfoTable)[SKILL_CLIENT_BLOOD_CURSE].Set("SKILL_CLIENT_BLOOD_CURSE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOOD_CURSE].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOOD_CURSE].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOOD_CURSE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOOD_CURSE][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODS_SYMPOSION_REPEAT;
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOOD_CURSE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOOD_CURSE][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOODS_SYMPOSION_REPEAT];
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOOD_CURSE][0].SetDelayNode();
	*/
		
	(*g_pActionInfoTable)[SKILL_BLOODY_SCARIFY].Set("SKILL_BLOODY_SCARIFY", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER , FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_BLOODY_SCARIFY].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_BLOODY_SCARIFY].SetStartWithCasting();
	
	
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SCARIFY].Set("RESULT_SKILL_BLOODY_SCARIFY", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SCARIFY].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SCARIFY].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SCARIFY].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SCARIFY][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SCARIFY][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_SCARIFY_ATTACK_TYPE_1;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SCARIFY][0].Step				= 30;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SCARIFY][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_SCARIFY_ATTACK_TYPE_1];
	
	
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOODY_SCARIFY_BOMB].Set("SKILL_CLIENT_BLOODY_SCARIFY", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOODY_SCARIFY_BOMB].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOODY_SCARIFY_BOMB].Init( 3 );
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOODY_SCARIFY_BOMB][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_RECT_RANDOM_PIXEL;
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOODY_SCARIFY_BOMB][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_SCARIFY_ATTACK_TYPE_2_A;
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOODY_SCARIFY_BOMB][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOODY_SCARIFY_BOMB][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_SCARIFY_ATTACK_TYPE_2_A];
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOODY_SCARIFY_BOMB][1].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOODY_SCARIFY_BOMB][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOODY_SCARIFY_BOMB][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_RECT_RANDOM_PIXEL;
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOODY_SCARIFY_BOMB][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_SCARIFY_ATTACK_TYPE_2_B;
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOODY_SCARIFY_BOMB][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOODY_SCARIFY_BOMB][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_SCARIFY_ATTACK_TYPE_2_B];
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOODY_SCARIFY_BOMB][1].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOODY_SCARIFY_BOMB][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOODY_SCARIFY_BOMB][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_RECT_RANDOM_PIXEL;
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOODY_SCARIFY_BOMB][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_SCARIFY_ATTACK_TYPE_2_C;
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOODY_SCARIFY_BOMB][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOODY_SCARIFY_BOMB][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_SCARIFY_ATTACK_TYPE_2_C];
	(*g_pActionInfoTable)[SKILL_CLIENT_BLOODY_SCARIFY_BOMB][2].LinkCount			= 1;
	//(*g_pActionInfoTable)[SKILL_CLIENT_BLOODY_SCARIFY_BOMB][2].SetDelayNode();



	// 2007.09.04 chyaya begin - Rare Skill
	(*g_pActionInfoTable)[SKILL_BAT_STORM1].Set("SKILL_BAT_STORM1", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_BAT_STORM1].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_BAT_STORM1].SetStartFrameAll(7);

	(*g_pActionInfoTable)[RESULT_SKILL_BAT_STORM1].Set("RESULT_SKILL_BAT_STORM1", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_BAT_STORM1].SetSoundID(SOUND_VAMPIRE_MAGIC);

	(*g_pActionInfoTable)[SKILL_BAT_STORM2].Set("SKILL_BAT_STORM2", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_BAT_STORM2].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_BAT_STORM2].SetStartFrameAll(7);

	(*g_pActionInfoTable)[RESULT_SKILL_BAT_STORM2].Set("RESULT_SKILL_BAT_STORM2", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_BAT_STORM2].SetSoundID(SOUND_VAMPIRE_MAGIC);

	(*g_pActionInfoTable)[SKILL_CURSE_OF_BLOOD1].Set("SKILL_CURSE_OF_BLOOD1", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_CURSE_OF_BLOOD1].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CURSE_OF_BLOOD1].SetStartFrameAll(7);

	(*g_pActionInfoTable)[RESULT_SKILL_CURSE_OF_BLOOD1].Set("RESULT_SKILL_CURSE_OF_BLOOD1", ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_CURSE_OF_BLOOD1].SetSoundID(SOUND_VAMPIRE_CURSE_OF_BLOOD);
	(*g_pActionInfoTable)[RESULT_SKILL_CURSE_OF_BLOOD1].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_CURSE_OF_BLOOD1][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_CURSE_OF_BLOOD1][0].EffectSpriteType		= EFFECTSPRITETYPE_CURSE_OF_BLOOD_5X5;
	(*g_pActionInfoTable)[RESULT_SKILL_CURSE_OF_BLOOD1][0].Step					= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_CURSE_OF_BLOOD1][0].Count				= FrameSize[EFFECTSPRITETYPE_CURSE_OF_BLOOD_5X5];

	(*g_pActionInfoTable)[SKILL_CURSE_OF_BLOOD2].Set("SKILL_CURSE_OF_BLOOD2", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_CURSE_OF_BLOOD2].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CURSE_OF_BLOOD2].SetStartFrameAll(7);

	(*g_pActionInfoTable)[RESULT_SKILL_CURSE_OF_BLOOD2].Set("RESULT_SKILL_CURSE_OF_BLOOD2", ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_CURSE_OF_BLOOD2].SetSoundID(SOUND_VAMPIRE_CURSE_OF_BLOOD);
	(*g_pActionInfoTable)[RESULT_SKILL_CURSE_OF_BLOOD2].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_CURSE_OF_BLOOD2][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_CURSE_OF_BLOOD2][0].EffectSpriteType		= EFFECTSPRITETYPE_CURSE_OF_BLOOD_7X7;
	(*g_pActionInfoTable)[RESULT_SKILL_CURSE_OF_BLOOD2][0].Step					= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_CURSE_OF_BLOOD2][0].Count				= FrameSize[EFFECTSPRITETYPE_CURSE_OF_BLOOD_7X7];

	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD].Set("SKILL_CLIENT_CURSE_OF_BLOOD", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD].Init( 5 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD].SetMainNode( 3 );
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][0].EffectSpriteType	= EFFECTSPRITETYPE_CURSE_OF_BLOOD_TARGET_HANDS_START;
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][0].Count				= FrameSize[EFFECTSPRITETYPE_CURSE_OF_BLOOD_TARGET_HANDS_START];
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][0].SoundID			= SOUND_VAMPIRE_PARALYSIS;
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][0].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][1].EffectSpriteType	= EFFECTSPRITETYPE_CURSE_OF_BLOOD_TARGET_GROUND_START;
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][1].Count				= FrameSize[EFFECTSPRITETYPE_CURSE_OF_BLOOD_TARGET_GROUND_START];
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][2].EffectSpriteType	= EFFECTSPRITETYPE_CURSE_OF_BLOOD_TARGET_GROUND_REPEAT;
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][2].Count				= FrameSize[EFFECTSPRITETYPE_CURSE_OF_BLOOD_TARGET_GROUND_REPEAT];
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][2].SetResultTime();
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][2].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][3].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][3].EffectSpriteType	= EFFECTSPRITETYPE_CURSE_OF_BLOOD_TARGET_HANDS_END;
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][3].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][3].Count				= FrameSize[EFFECTSPRITETYPE_CURSE_OF_BLOOD_TARGET_HANDS_END];
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][3].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][4].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][4].EffectSpriteType	= EFFECTSPRITETYPE_CURSE_OF_BLOOD_TARGET_GROUND_END;
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][4].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_CURSE_OF_BLOOD][4].Count				= FrameSize[EFFECTSPRITETYPE_CURSE_OF_BLOOD_TARGET_GROUND_END];

	(*g_pActionInfoTable)[SKILL_BLOOD_DRAIN2].Set("SKILL_BLOOD_DRAIN2", ACTION_VAMPIRE_DRAIN, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[SKILL_BLOOD_DRAIN2].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_BLOOD_DRAIN2].SetMaleSoundID( SOUND_VAMPIRE_DRAIN_MALE );
	(*g_pActionInfoTable)[SKILL_BLOOD_DRAIN2].SetFemaleSoundID( SOUND_VAMPIRE_DRAIN_FEMALE );

	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_DRAIN2].Set("RESULT_SKILL_BLOOD_DRAIN2", ACTION_VAMPIRE_DRAIN, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_BLOOD_DRAIN2].SetSoundID( SOUNDID_NULL );
	
	(*g_pActionInfoTable)[SKILL_BLOODY_SHOUT1].Set("SKILL_BLOODY_SHOUT1", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_BLOODY_SHOUT1].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_BLOODY_SHOUT1].Init( 1 );
	(*g_pActionInfoTable)[SKILL_BLOODY_SHOUT1].SetStartFrameAll(7);
	(*g_pActionInfoTable)[SKILL_BLOODY_SHOUT1][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_BLOODY_SHOUT1][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_SHOUT_GROUND;
	(*g_pActionInfoTable)[SKILL_BLOODY_SHOUT1][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_BLOODY_SHOUT1][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_SHOUT_GROUND];

	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT1].Set("RESULT_SKILL_BLOODY_SHOUT1", ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT1].SetSoundID(SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT1].Init( 2 );
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT1][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT1][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_SHOUT_RED_DUST;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT1][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT1][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_SHOUT_RED_DUST];
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT1][0].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT1][0].SoundID			= SOUND_VAMPIRE_BLOODY_SHOUT_1;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT1][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT1][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_SHOUT_RED_LIGHT_BACK;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT1][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT1][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_SHOUT_RED_LIGHT_BACK];
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT1][1].SoundID			= SOUND_VAMPIRE_BLOODY_SHOUT_2;

	(*g_pActionInfoTable)[SKILL_BLOODY_SHOUT2].Set("SKILL_BLOODY_SHOUT2", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_BLOODY_SHOUT2].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_BLOODY_SHOUT2].Init( 1 );
	(*g_pActionInfoTable)[SKILL_BLOODY_SHOUT2].SetStartFrameAll(7);
	(*g_pActionInfoTable)[SKILL_BLOODY_SHOUT2][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_BLOODY_SHOUT2][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_SHOUT_GROUND;
	(*g_pActionInfoTable)[SKILL_BLOODY_SHOUT2][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_BLOODY_SHOUT2][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_SHOUT_GROUND];

	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT2].Set("RESULT_SKILL_BLOODY_SHOUT2", ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT2].SetSoundID(SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT2].Init( 3 );
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT2][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT2][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_SHOUT_RED_DUST;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT2][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT2][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_SHOUT_RED_DUST];
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT2][0].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT2][0].SoundID			= SOUND_VAMPIRE_BLOODY_SHOUT_1;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT2][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT2][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_SHOUT_RED_LIGHT_BACK;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT2][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT2][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_SHOUT_RED_LIGHT_BACK];
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT2][1].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT2][1].SoundID			= SOUND_VAMPIRE_BLOODY_SHOUT_2;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT2][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT2][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_SHOUT_ROTATE_LIGHT_BACK;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT2][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_SHOUT2][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_SHOUT_ROTATE_LIGHT_BACK];

	(*g_pActionInfoTable)[SKILL_BLOODY_WINGS].Set("SKILL_BLOODY_WINGS", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 2, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_BLOODY_WINGS].SetUser(FLAG_ACTIONINFO_USER_VAMPIRE);
	(*g_pActionInfoTable)[SKILL_BLOODY_WINGS].SetStartFrameAll( 15 );
	(*g_pActionInfoTable)[SKILL_BLOODY_WINGS].SetStartWithCasting();//FrameAll( 7 );
	(*g_pActionInfoTable)[SKILL_BLOODY_WINGS].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_BLOODY_WINGS].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, RESULT_SKILL_BLOODY_WINGS );	// 맞는 결과를 표현한다.	

	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_WINGS].Set("RESULT_SKILL_BLOODY_WINGS", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_WINGS].SetSoundID(SOUND_VAMPIRE_BLOODY_WING);
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_WINGS].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_WINGS].SetMainNode( 0 );
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_WINGS].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_WINGS][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_WINGS][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_WINGS;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_WINGS][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_BLOODY_WINGS][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_WINGS];

#if __CONTENTS(__MENEGROTH)

	(*g_pActionInfoTable)[SKILL_CERBERUS].Set("SKILL_CERBERUS", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 2, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_CERBERUS].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_CERBERUS].SetSoundID( SOUND_CABERUS_SKILL );
	(*g_pActionInfoTable)[SKILL_CERBERUS].Init(3);
	(*g_pActionInfoTable)[SKILL_CERBERUS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CERBERUS][0].EffectSpriteType	= EFFECTSPRITETYPE_CERBERUS_1;
	(*g_pActionInfoTable)[SKILL_CERBERUS][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CERBERUS][0].Count				= FrameSize[EFFECTSPRITETYPE_CERBERUS_1];
	(*g_pActionInfoTable)[SKILL_CERBERUS][0].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_CERBERUS][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CERBERUS][1].EffectSpriteType	= EFFECTSPRITETYPE_CERBERUS_2;
	(*g_pActionInfoTable)[SKILL_CERBERUS][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CERBERUS][1].Count				= FrameSize[EFFECTSPRITETYPE_CERBERUS_2];
	(*g_pActionInfoTable)[SKILL_CERBERUS][1].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_CERBERUS][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CERBERUS][2].EffectSpriteType	= EFFECTSPRITETYPE_CERBERUS_3;
	(*g_pActionInfoTable)[SKILL_CERBERUS][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CERBERUS][2].Count				= FrameSize[EFFECTSPRITETYPE_CERBERUS_3];
	(*g_pActionInfoTable)[SKILL_CERBERUS][2].LinkCount			= 0;	


	(*g_pActionInfoTable)[RESULT_SKILL_CERBERUS].Set("SKILL_CERBERUS", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_CERBERUS].SetSoundID( SOUNDID_NULL );



//맨티는 에시드스톰과 동일

	(*g_pActionInfoTable)[SKILL_MANTICORET].Set("SKILL_MANTICORET", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_MANTICORET].SetStartFrameAll( 4 );
	(*g_pActionInfoTable)[SKILL_MANTICORET].SetCastingStartFrameAll(4);
	(*g_pActionInfoTable)[SKILL_MANTICORET].SetSoundID( SOUND_MANTICORET_SKILL );
	(*g_pActionInfoTable)[SKILL_MANTICORET].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_MANTICORET][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[SKILL_MANTICORET][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_ACID_BOLT_1;
	(*g_pActionInfoTable)[SKILL_MANTICORET][0].Step				= 20;
	(*g_pActionInfoTable)[SKILL_MANTICORET][0].Count			= 32;//FrameSize[EFFECTSPRITETYPE_ACID_BOLT_1];
	(*g_pActionInfoTable)[SKILL_MANTICORET][0].SoundID			= SOUND_VAMPIRE_ACID_ABOLT1;

	(*g_pActionInfoTable)[RESULT_SKILL_MANTICORET].Set("RESULT_SKILL_MANTICORET", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_MANTICORET].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_SKILL_MANTICORET].Init( 2 );
	(*g_pActionInfoTable)[RESULT_SKILL_MANTICORET][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_MANTICORET][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_ACID_BALL_2;
	(*g_pActionInfoTable)[RESULT_SKILL_MANTICORET][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_MANTICORET][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_ACID_BALL_2];
	(*g_pActionInfoTable)[RESULT_SKILL_MANTICORET][0].SoundID			= SOUND_VAMPIRE_ACIDBALL2;
	(*g_pActionInfoTable)[RESULT_SKILL_MANTICORET][0].LinkCount			= 1;
	(*g_pActionInfoTable)[RESULT_SKILL_MANTICORET][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_MANTICORET][1].EffectSpriteType	= EFFECTSPRITETYPE_SMOKE;
	(*g_pActionInfoTable)[RESULT_SKILL_MANTICORET][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_MANTICORET][1].Count				= FrameSize[EFFECTSPRITETYPE_SMOKE];
	(*g_pActionInfoTable)[RESULT_SKILL_MANTICORET][1].SoundID			= SOUND_VAMPIRE_ACIDBURN;
	(*g_pActionInfoTable)[RESULT_SKILL_MANTICORET][1].SetResultTime();

	
	(*g_pActionInfoTable)[SKILL_BOGLE_H].Set("SKILL_BOGLE_H", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 2, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_BOGLE_H].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_BOGLE_H].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_BOGLE_H].SetSoundID( SOUND_BOGLET_H_SKILL );

	//보글트 이펙트가 망치질 액션에 마춰서 딜레이 있시 터져 야 하기 때문에 빈 스프라이트 단계를 두어 딜레이를 조정했다. 상수값 11
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_H].Set("RESULT_SKILL_BOGLE_H", ACTION_STAND, EFFECTSPRITETYPE_NULL, 2, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_H].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_H].SetStartFrameAll(11);
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_H].SetCastingStartFrameAll(11);
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_H].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_H][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_H][0].EffectSpriteType		= EFFECTSPRITETYPE_BOGLE_H;
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_H][0].Step					= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_H][0].Count				= FrameSize[EFFECTSPRITETYPE_BOGLE_H];


	(*g_pActionInfoTable)[SKILL_BOGLE_B].Set("SKILL_BOGLE_B", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 2, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_BOGLE_B].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_BOGLE_B].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_BOGLE_B].SetSoundID( SOUND_BOGLET_B_SKILL );
	(*g_pActionInfoTable)[SKILL_BOGLE_B].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_BOGLE_B].Init( 1 );
	(*g_pActionInfoTable)[SKILL_BOGLE_B][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_BOGLE_B][0].EffectSpriteType	= EFFECTSPRITETYPE_BOGLE_B;
	(*g_pActionInfoTable)[SKILL_BOGLE_B][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_BOGLE_B][0].Count				= FrameSize[EFFECTSPRITETYPE_BOGLE_B];
	(*g_pActionInfoTable)[SKILL_BOGLE_B][0].SetResultTime();


	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_B].Set("RESULT_SKILL_BOGLE_B", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_B].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_B].Init( 4 );
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_B][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_B][0].EffectSpriteType = EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_1;
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_B][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_B][0].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_1];
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_B][0].LinkCount			= 2;
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_B][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_B][1].EffectSpriteType = EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_2;
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_B][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_B][1].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_2];
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_B][1].LinkCount			= 2;
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_B][2].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_B][2].EffectSpriteType = EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_3;
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_B][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_B][2].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_3];
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_B][2].LinkCount			= 4;
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_B][3].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_B][3].EffectSpriteType = EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_4;
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_B][3].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_B][3].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_4];
	(*g_pActionInfoTable)[RESULT_SKILL_BOGLE_B][3].LinkCount			= 4;

//매서커 

	(*g_pActionInfoTable)[SKILL_MASSACRE_MENEGROTH].Set("SKILL_MASSACRE_MENEGROTH", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 2, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_MASSACRE_MENEGROTH].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_MASSACRE_MENEGROTH].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_MASSACRE_MENEGROTH].SetSoundID( SOUND_MASSACRE_SKILL );
	
	(*g_pActionInfoTable)[RESULT_SKILL_MASSACRE_MENEGROTH].Set("RESULT_SKILL_MASSACRE_MENEGROTH", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 2, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_ATTACK]);	
	(*g_pActionInfoTable)[RESULT_SKILL_MASSACRE_MENEGROTH].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_MASSACRE_MENEGROTH].SetStartFrameAll( 14 );
	(*g_pActionInfoTable)[RESULT_SKILL_MASSACRE_MENEGROTH].SetCastingStartFrameAll( 14 );	// 불꽃이 붙는 frame
	(*g_pActionInfoTable)[RESULT_SKILL_MASSACRE_MENEGROTH].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_MASSACRE_MENEGROTH][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_MASSACRE_MENEGROTH][0].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_RUFFIAN_1_AXE_GROUND;
	(*g_pActionInfoTable)[RESULT_SKILL_MASSACRE_MENEGROTH][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_MASSACRE_MENEGROTH][0].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_RUFFIAN_1_AXE_GROUND];
	(*g_pActionInfoTable)[RESULT_SKILL_MASSACRE_MENEGROTH][0].LinkCount			= 0;


//플럼피보어

	(*g_pActionInfoTable)[SKILL_PLUMYBOAR].Set("SKILL_PLUMYBOAR", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 4, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_PLUMYBOAR].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_PLUMYBOAR].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_PLUMYBOAR].SetCastingStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_PLUMYBOAR].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_PLUMYBOAR].SetSoundID( SOUND_PLUMYBOAR_SKILL );
	(*g_pActionInfoTable)[SKILL_PLUMYBOAR].Init( 2 );
	(*g_pActionInfoTable)[SKILL_PLUMYBOAR][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_PLUMYBOAR][0].EffectSpriteType	= EFFECTSPRITETYPE_PLUMYBOAR_FRONT;
	(*g_pActionInfoTable)[SKILL_PLUMYBOAR][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_PLUMYBOAR][0].Count				= FrameSize[EFFECTSPRITETYPE_PLUMYBOAR_FRONT];
	(*g_pActionInfoTable)[SKILL_PLUMYBOAR][0].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_PLUMYBOAR][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_PLUMYBOAR][1].EffectSpriteType	= EFFECTSPRITETYPE_PLUMYBOAR_BACK;
	(*g_pActionInfoTable)[SKILL_PLUMYBOAR][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_PLUMYBOAR][1].Count				= FrameSize[EFFECTSPRITETYPE_PLUMYBOAR_BACK];
	(*g_pActionInfoTable)[SKILL_PLUMYBOAR][1].LinkCount			= 0;

	(*g_pActionInfoTable)[RESULT_SKILL_PLUMYBOAR].Set("RESULT_SKILL_PLUMYBOAR", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 4, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_PLUMYBOAR].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_PLUMYBOAR].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_SKILL_PLUMYBOAR][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_PLUMYBOAR][0].EffectSpriteType	= EFFECTSPRITETYPE_NOOSE_OF_WRAITH_RISE;
	(*g_pActionInfoTable)[RESULT_SKILL_PLUMYBOAR][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_PLUMYBOAR][0].Count				= FrameSize[EFFECTSPRITETYPE_NOOSE_OF_WRAITH_RISE];
	(*g_pActionInfoTable)[RESULT_SKILL_PLUMYBOAR][0].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_PLUMYBOAR][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_PLUMYBOAR][1].EffectSpriteType	= EFFECTSPRITETYPE_NOOSE_OF_WRAITH_GROUND_SHAPE;
	(*g_pActionInfoTable)[RESULT_SKILL_PLUMYBOAR][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_PLUMYBOAR][1].Count				= FrameSize[EFFECTSPRITETYPE_NOOSE_OF_WRAITH_GROUND_SHAPE];
	(*g_pActionInfoTable)[RESULT_SKILL_PLUMYBOAR][1].LinkCount			=  8;
	(*g_pActionInfoTable)[RESULT_SKILL_PLUMYBOAR][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_PLUMYBOAR][2].EffectSpriteType	= EFFECTSPRITETYPE_NEW_NOOSE_OF_WRAITH ; //EFFECTSPRITETYPE_NOOSE_OF_WRAITH_BLOW;
	(*g_pActionInfoTable)[RESULT_SKILL_PLUMYBOAR][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_PLUMYBOAR][2].Count				= FrameSize[EFFECTSPRITETYPE_NEW_NOOSE_OF_WRAITH] ; //EFFECTSPRITETYPE_NOOSE_OF_WRAITH_BLOW];

//카브라캄	도끼 질에 마춰서 이펙트가 터져야 하기 땜시 스타트 캐스팅 몽땅 마춰준다.

	(*g_pActionInfoTable)[SKILL_CABRACAM].Set("SKILL_CABRACAM", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER,VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_CABRACAM].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_CABRACAM].SetSoundID( SOUND_CABRACAM_SKILL );
	(*g_pActionInfoTable)[SKILL_CABRACAM].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_CABRACAM].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CABRACAM][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CABRACAM][0].EffectSpriteType	= EFFECTSPRITETYPE_CABRACAM;
	(*g_pActionInfoTable)[SKILL_CABRACAM][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CABRACAM][0].Count				= FrameSize[EFFECTSPRITETYPE_CABRACAM];
	
	(*g_pActionInfoTable)[RESULT_SKILL_CABRACAM].Set("SKILL_CABRACAM", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET,VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[RESULT_SKILL_CABRACAM].SetSoundID( SOUND_CABRACAM_SKILL );
	(*g_pActionInfoTable)[RESULT_SKILL_CABRACAM].SetStartFrameAll(14);
	(*g_pActionInfoTable)[RESULT_SKILL_CABRACAM].SetCastingStartFrameAll(14);
	(*g_pActionInfoTable)[RESULT_SKILL_CABRACAM].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_CABRACAM][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_X;
	(*g_pActionInfoTable)[RESULT_SKILL_CABRACAM][0].EffectSpriteType	= EFFECTSPRITETYPE_BOMB_CRASH_WALK_PILLAR_OF_FIRE;
	(*g_pActionInfoTable)[RESULT_SKILL_CABRACAM][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_CABRACAM][0].Count				= FrameSize[EFFECTSPRITETYPE_BOMB_CRASH_WALK_PILLAR_OF_FIRE];
	(*g_pActionInfoTable)[RESULT_SKILL_CABRACAM][0].SoundID				= SOUNDID_NULL;

	(*g_pActionInfoTable)[SKILL_CLIENT_CABRACAM_SUMMON].Set("SKILL_CLIENT_CABRACAM_SUMMON", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_CLIENT_CABRACAM_SUMMON].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_CABRACAM_SUMMON].SetStartFrameAll(0);
	(*g_pActionInfoTable)[SKILL_CLIENT_CABRACAM_SUMMON].Init(3);
	(*g_pActionInfoTable)[SKILL_CLIENT_CABRACAM_SUMMON][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_CABRACAM_SUMMON][0].EffectSpriteType		= EFFECTSPRITETYPE_CABRACAM_SUMMON_BACK;
	(*g_pActionInfoTable)[SKILL_CLIENT_CABRACAM_SUMMON][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_CABRACAM_SUMMON][0].Count				= FrameSize[EFFECTSPRITETYPE_CABRACAM_SUMMON_BACK];
	(*g_pActionInfoTable)[SKILL_CLIENT_CABRACAM_SUMMON][0].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_CLIENT_CABRACAM_SUMMON][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_CABRACAM_SUMMON][1].EffectSpriteType		= EFFECTSPRITETYPE_CABRACAM_SUMMON_FRONT;
	(*g_pActionInfoTable)[SKILL_CLIENT_CABRACAM_SUMMON][1].Step					= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_CABRACAM_SUMMON][1].Count				= FrameSize[EFFECTSPRITETYPE_CABRACAM_SUMMON_FRONT];
	(*g_pActionInfoTable)[SKILL_CLIENT_CABRACAM_SUMMON][1].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_CLIENT_CABRACAM_SUMMON][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_CABRACAM_SUMMON][2].EffectSpriteType		= EFFECTSPRITETYPE_CABRACAM_SUMMON_BODY;
	(*g_pActionInfoTable)[SKILL_CLIENT_CABRACAM_SUMMON][2].Step					= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_CABRACAM_SUMMON][2].Count				= FrameSize[EFFECTSPRITETYPE_CABRACAM_SUMMON_BODY];
	(*g_pActionInfoTable)[SKILL_CLIENT_CABRACAM_SUMMON][2].LinkCount			= 0;


	(*g_pActionInfoTable)[SKILL_CLIENT_MENEGROTH_TRAP].Set("SKILL_CLIENT_MENEGROTH_TRAP", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_CLIENT_MENEGROTH_TRAP].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_MENEGROTH_TRAP].SetStartFrameAll(0);
	(*g_pActionInfoTable)[SKILL_CLIENT_MENEGROTH_TRAP].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_MENEGROTH_TRAP][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_MENEGROTH_TRAP][0].EffectSpriteType	= EFFECTSPRITETYPE_MENEGROTH_TRAP_MODIFY;
	(*g_pActionInfoTable)[SKILL_CLIENT_MENEGROTH_TRAP][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_MENEGROTH_TRAP][0].Count				= FrameSize[EFFECTSPRITETYPE_MENEGROTH_TRAP_MODIFY];
	(*g_pActionInfoTable)[SKILL_CLIENT_MENEGROTH_TRAP][0].SoundID			= SOUND_BOOM_TRAP;


#endif //__MENEGROTH
	
#if __CONTENTS(__TIPOJYU_CASTLE)	//스킬 추가
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_LIFE_GATEWAY_NE].Set("SKILL_CLIENT_TIPOJYU_LIFE_GATEWAY_NE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_LIFE_GATEWAY_NE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_LIFE_GATEWAY_NE].SetStartFrameAll(0);
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_LIFE_GATEWAY_NE].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_LIFE_GATEWAY_NE][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_LIFE_GATEWAY_NE][0].EffectSpriteType		= EFFECTSPRITETYPE_TIPOJYU_LIFE_GATEWAY_NE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_LIFE_GATEWAY_NE][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_LIFE_GATEWAY_NE][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_GATEWAY_NE];

	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_LIFE_GATEWAY_NW].Set("SKILL_CLIENT_TIPOJYU_LIFE_GATEWAY_NE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_LIFE_GATEWAY_NW].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_LIFE_GATEWAY_NW].SetStartFrameAll(0);
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_LIFE_GATEWAY_NW].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_LIFE_GATEWAY_NW][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_LIFE_GATEWAY_NW][0].EffectSpriteType		= EFFECTSPRITETYPE_TIPOJYU_LIFE_GATEWAY_NW;
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_LIFE_GATEWAY_NW][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_LIFE_GATEWAY_NW][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_GATEWAY_NW];

	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_HADES_GATEWAY_NE].Set("SKILL_CLIENT_TIPOJYU_LIFE_GATEWAY_NE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_HADES_GATEWAY_NE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_HADES_GATEWAY_NE].SetStartFrameAll(0);
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_HADES_GATEWAY_NE].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_HADES_GATEWAY_NE][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_HADES_GATEWAY_NE][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_GATEWAY_NE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_HADES_GATEWAY_NE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_HADES_GATEWAY_NE][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_HADES_GATEWAY_NE];

	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_HADES_GATEWAY_NW].Set("SKILL_CLIENT_TIPOJYU_LIFE_GATEWAY_NE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_HADES_GATEWAY_NW].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_HADES_GATEWAY_NW].SetStartFrameAll(0);
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_HADES_GATEWAY_NW].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_HADES_GATEWAY_NW][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_HADES_GATEWAY_NW][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_HADES_GATEWAY_NW;
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_HADES_GATEWAY_NW][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_HADES_GATEWAY_NW][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_GATEWAY_NW];
	

	//트랩
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_LIFE_TRAP].Set("SKILL_CLIENT_TIPOJYU_LIFE_TRAP", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_LIFE_TRAP].SetSoundID( SOUND_TIPOJYU_TRAP_A );
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_LIFE_TRAP].SetStartFrameAll(0);
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_LIFE_TRAP].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_LIFE_TRAP][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_LIFE_TRAP][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_TRAP;
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_LIFE_TRAP][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_LIFE_TRAP][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_TRAP];

	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_HADES_TRAP].Set("SKILL_CLIENT_TIPOJYU_HADES_TRAP", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_HADES_TRAP].SetSoundID( SOUND_TIPOJYU_TRAP_B );
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_HADES_TRAP].SetStartFrameAll(0);
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_HADES_TRAP].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_HADES_TRAP][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_HADES_TRAP][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_HADES_TRAP;
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_HADES_TRAP][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TIPOJYU_HADES_TRAP][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_HADES_TRAP];

	
	//현세 근위대 스킬
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_BLUE].Set("SKILL_TIFFAUGES_BERITH_BLUE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_BLUE].SetCastingStartFrameAll( 1 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_BLUE].SetStartFrameAll( 16 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_BLUE].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_BLUE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_BLUE][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_ROYALGUARDS_ATTACK_A_1;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_BLUE][0].Step				= 30;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_BLUE][0].Count				= 32; // 발사 스킬의 Count는 32로 되어있다. 소스 분석 필요하다.;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_BLUE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_BLUE][1].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_ROYALGUARDS_ATTACK_A_2;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_BLUE][1].Step				= 20;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_BLUE][1].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_ROYALGUARDS_ATTACK_A_2];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_BLUE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_BERITH_BLUE );	// 맞는 결과를 표현한다.
	// RESULT 스킬은 플레이어의 모션과 관련이 있다. ACTION_DAMAGED을 ACTION_MAGIC 바꾸면 마법 모션으로 바뀐다.
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_BERITH_BLUE].Set("RESULT_SKILL_TIFFAUGES_BERITH_BLUE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_BERITH_BLUE].SetSoundID( SOUNDID_NULL );


	//과거 근위대 스킬
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_RED].Set("SKILL_TIFFAUGES_BERITH_RED", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_RED].SetCastingStartFrameAll( 1 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_RED].SetStartFrameAll( 16 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_RED].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_RED][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_RED][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_HADES_ROYALGUARDS_ATTACK_A_1;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_RED][0].Step				= 30;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_RED][0].Count				= 32;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_RED][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_RED][1].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_HADES_ROYALGUARDS_ATTACK_A_2;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_RED][1].Step				= 20;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_RED][1].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_HADES_ROYALGUARDS_ATTACK_A_2];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BERITH_RED].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_BERITH_BLUE );	// 맞는 결과를 표현한다.	
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_BERITH_RED].Set("RESULT_SKILL_TIFFAUGES_BERITH_RED", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_BERITH_RED].SetSoundID( SOUNDID_NULL );




	//현세 근위대 두목 스킬
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_BLUE].Set("SKILL_TIFFAUGES_VALKYRJA_BLUE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_BLUE].SetCastingStartFrameAll( 1 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_BLUE].SetStartFrameAll( 16 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_BLUE].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_BLUE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_BLUE][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_ROYALGUARDS_BOSS_ATTACK_A;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_BLUE][0].Step				= 30;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_BLUE][0].Count				= 0;//FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_ROYALGUARDS_ATTACK_A_1];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_BLUE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_BLUE][1].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_ROYALGUARDS_BOSS_ATTACK_A;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_BLUE][1].Step				= 20;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_BLUE][1].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_ROYALGUARDS_BOSS_ATTACK_A];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_BLUE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_VALKYRJA_BLUE );	// 맞는 결과를 표현한다.
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_VALKYRJA_BLUE].Set("RESULT_SKILL_TIFFAUGES_VALKYRJA_BLUE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_VALKYRJA_BLUE].SetSoundID( SOUNDID_NULL );

	//과거 근위대 두목 스킬
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_RED].Set("SKILL_TIFFAUGES_VALKYRJA_RED", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_RED].SetCastingStartFrameAll( 1 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_RED].SetStartFrameAll( 16 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_RED].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_RED][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_RED][0].EffectSpriteType		= EFFECTSPRITETYPE_TIPOJYU_HADES_ROYALGUARDS_BOSS_ATTACK_A;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_RED][0].Step					= 30;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_RED][0].Count				= 0;//FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_ROYALGUARDS_ATTACK_A_1];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_RED][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_RED][1].EffectSpriteType		= EFFECTSPRITETYPE_TIPOJYU_HADES_ROYALGUARDS_BOSS_ATTACK_A;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_RED][1].Step					= 20;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_RED][1].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_ROYALGUARDS_BOSS_ATTACK_A];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_VALKYRJA_RED].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_VALKYRJA_RED );	// 맞는 결과를 표현한다.
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_VALKYRJA_RED].Set("RESULT_SKILL_TIFFAUGES_VALKYRJA_RED", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_VALKYRJA_RED].SetSoundID( SOUNDID_NULL );
	
	

	//현세 여자 백작 스킬 A
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_BLUE].Set("SKILL_TIFFAUGES_GOMORY_A_BLUE", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_BLUE].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_BLUE].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_BLUE].SetCastingStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_BLUE].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_BLUE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_BLUE].Init( 1 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_BLUE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_BLUE][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNTESS_ATTACK_A;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_BLUE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_BLUE][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNTESS_ATTACK_A] - 4;	// 노드시간이 살짝 길어서 스킬을 계속 사용하면 이펙트가 어긋난다. 그래서 -4를 해줌.
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_BLUE][0].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_BLUE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_GOMORY_A_BLUE );	// 맞는 결과를 표현한다.
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_GOMORY_A_BLUE].Set("RESULT_SKILL_TIFFAUGES_GOMORY_A_BLUE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_GOMORY_A_BLUE].SetSoundID( SOUNDID_NULL );

	//현세 여자 백작 스킬 B	
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_BLUE].Set("SKILL_TIFFAUGES_GOMORY_B_BLUE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_BLUE].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_BLUE].SetStartFrameAll( 16 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_BLUE].SetCastingStartFrameAll( 16 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_BLUE].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_BLUE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_BLUE].Init( 2 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_BLUE][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_BLUE][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNTESS_ATTACK_B_1;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_BLUE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_BLUE][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNTESS_ATTACK_B_1];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_BLUE][0].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_BLUE][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_EMPTY_RECT;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_BLUE][1].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNTESS_ATTACK_B_2;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_BLUE][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_BLUE][1].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNTESS_ATTACK_B_2];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_BLUE][1].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_BLUE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_GOMORY_B_BLUE );	// 맞는 결과를 표현한다.
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_GOMORY_B_BLUE].Set("RESULT_SKILL_TIFFAUGES_GOMORY_B_BLUE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_GOMORY_B_BLUE].SetSoundID( SOUNDID_NULL );

	//과거 여자 백작 스킬 A
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_RED].Set("SKILL_TIFFAUGES_GOMORY_A_RED", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_RED].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_RED].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_RED].SetCastingStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_RED].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_RED].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_RED].Init( 1 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_RED][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_RED][0].EffectSpriteType		= EFFECTSPRITETYPE_TIPOJYU_HADES_COUNTESS_ATTACK_A;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_RED][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_RED][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_HADES_COUNTESS_ATTACK_A] - 4;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_RED][0].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_A_RED].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_GOMORY_A_RED );	// 맞는 결과를 표현한다.
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_GOMORY_A_RED].Set("RESULT_SKILL_TIFFAUGES_GOMORY_A_RED", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_GOMORY_A_RED].SetSoundID( SOUNDID_NULL );

	//과거 여자 백작 스킬 B	
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_RED].Set("SKILL_TIFFAUGES_GOMORY_B_RED", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_RED].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_RED].SetStartFrameAll( 16 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_RED].SetCastingStartFrameAll( 16 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_RED].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_RED].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_RED].Init( 2 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_RED][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_RED][0].EffectSpriteType		= EFFECTSPRITETYPE_TIPOJYU_HADES_COUNTESS_ATTACK_B_1;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_RED][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_RED][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_HADES_COUNTESS_ATTACK_B_1];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_RED][0].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_RED][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_EMPTY_RECT;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_RED][1].EffectSpriteType		= EFFECTSPRITETYPE_TIPOJYU_HADES_COUNTESS_ATTACK_B_2;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_RED][1].Step					= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_RED][1].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_HADES_COUNTESS_ATTACK_B_2];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_RED][1].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GOMORY_B_RED].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_GOMORY_B_RED );	// 맞는 결과를 표현한다.
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_GOMORY_B_RED].Set("RESULT_SKILL_TIFFAUGES_GOMORY_B_RED", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_GOMORY_B_RED].SetSoundID( SOUNDID_NULL );

	
	//현세 남자 백작 스킬 A
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_BLUE].Set("SKILL_TIFFAUGES_KRSNIK_A_BLUE", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_BLUE].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_BLUE].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_BLUE].SetCastingStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_BLUE].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_BLUE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_BLUE].Init( 1 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_BLUE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_BLUE][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNT_ATTACK_A;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_BLUE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_BLUE][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNT_ATTACK_A] - 4;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_BLUE][0].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_BLUE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_KRSNIK_A_BLUE );	// 맞는 결과를 표현한다.
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_KRSNIK_A_BLUE].Set("RESULT_SKILL_TIFFAUGES_KRSNIK_A_BLUE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_KRSNIK_A_BLUE].SetSoundID( SOUNDID_NULL );

	//현세 남자 백작 스킬 B
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE].Set("SKILL_TIFFAUGES_KRSNIK_B_BLUE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE].SetCastingStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE].Init( 2 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNT_ATTACK_B_1;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNT_ATTACK_B_1];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE][0].LinkCount			= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNT_ATTACK_B_1];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE][1].EffectGeneratorID	= EFFECTGENERATORID_AROUND_ZONE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE][1].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNT_ATTACK_B_2;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE][1].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNT_ATTACK_B_2];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE][1].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_KRSNIK_B_BLUE );	// 맞는 결과를 표현한다.
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_KRSNIK_B_BLUE].Set("RESULT_SKILL_TIFFAUGES_KRSNIK_B_BLUE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_KRSNIK_B_BLUE].SetSoundID( SOUNDID_NULL );


	//과거 남자 백작 스킬 A
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_RED].Set("SKILL_TIFFAUGES_KRSNIK_A_RED", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_RED].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_RED].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_RED].SetCastingStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_RED].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_RED].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_RED].Init( 1 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_RED][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_RED][0].EffectSpriteType		= EFFECTSPRITETYPE_TIPOJYU_HADES_COUNT_ATTACK_A;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_RED][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_RED][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_HADES_COUNT_ATTACK_A] - 4;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_RED][0].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_A_RED].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_KRSNIK_A_RED );	// 맞는 결과를 표현한다.
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_KRSNIK_A_RED].Set("RESULT_SKILL_TIFFAUGES_KRSNIK_A_RED", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_KRSNIK_A_RED].SetSoundID( SOUNDID_NULL );

	//과거 남자 백작 스킬 B
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE].Set("SKILL_TIFFAUGES_KRSNIK_B_BLUE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE].SetCastingStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE].Init( 2 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNT_ATTACK_B_1;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNT_ATTACK_B_1];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE][0].LinkCount			= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNT_ATTACK_B_1];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE][1].EffectGeneratorID	= EFFECTGENERATORID_AROUND_ZONE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE][1].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNT_ATTACK_B_2;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE][1].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNT_ATTACK_B_2];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE][1].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_KRSNIK_B_BLUE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_KRSNIK_B_BLUE );	// 맞는 결과를 표현한다.
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_KRSNIK_B_BLUE].Set("RESULT_SKILL_TIFFAUGES_KRSNIK_B_BLUE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_KRSNIK_B_BLUE].SetSoundID( SOUNDID_NULL );

	//현세 남자 백작 대장 스킬 A
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_BLUE].Set("SKILL_TIFFAUGES_GUSION_A_BLUE", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_BLUE].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_BLUE].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_BLUE].SetCastingStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_BLUE].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_BLUE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_BLUE].Init( 1 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_BLUE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_BLUE][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNT_BOSS_ATTACK_A;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_BLUE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_BLUE][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNT_BOSS_ATTACK_A];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_BLUE][0].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_BLUE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_GUSION_A_BLUE );	// 맞는 결과를 표현한다.
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_GUSION_A_BLUE].Set("RESULT_SKILL_TIFFAUGES_GUSION_A_BLUE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_GUSION_A_BLUE].SetSoundID( SOUNDID_NULL );
	
	//현세 남자 백작 대장 스킬 B
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_BLUE].Set("SKILL_TIFFAUGES_GUSION_B_BLUE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_BLUE].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_BLUE].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_BLUE].SetCastingStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_BLUE].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_BLUE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_BLUE].Init( 2 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_BLUE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_BLUE][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNT_BOSS_ATTACK_B_1;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_BLUE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_BLUE][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNT_BOSS_ATTACK_B_1];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_BLUE][0].LinkCount			= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNT_BOSS_ATTACK_B_1];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_BLUE][1].EffectGeneratorID	= EFFECTGENERATORID_AROUND_ZONE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_BLUE][1].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNT_BOSS_ATTACK_B_2;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_BLUE][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_BLUE][1].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNT_BOSS_ATTACK_B_2];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_BLUE][1].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_BLUE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_GUSION_B_BLUE );	// 맞는 결과를 표현한다.
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_GUSION_B_BLUE].Set("RESULT_SKILL_TIFFAUGES_GUSION_B_BLUE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_GUSION_B_BLUE].SetSoundID( SOUNDID_NULL );

	//현세 남자 백작 대장 스킬 C
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_BLUE].Set("SKILL_TIFFAUGES_GUSION_B_BLUE", ACTION_DRAINED, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_BLUE].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_BLUE].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_BLUE].SetCastingStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_BLUE].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_BLUE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_BLUE].Init( 1 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_BLUE][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_RECT_RANDOM_PIXEL;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_BLUE][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNT_BOSS_ATTACK_C;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_BLUE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_BLUE][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_COUNT_BOSS_ATTACK_C];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_BLUE][0].LinkCount			= 0;
 	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_BLUE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_GUSION_C_BLUE );	// 맞는 결과를 표현한다.
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_GUSION_C_BLUE].Set("RESULT_SKILL_TIFFAUGES_GUSION_C_BLUE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_GUSION_C_BLUE].SetSoundID( SOUNDID_NULL );

	//과거 남자 백작 대장 스킬 A
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_RED].Set("SKILL_TIFFAUGES_GUSION_A_RED", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_RED].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_RED].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_RED].SetCastingStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_RED].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_RED].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_RED].Init( 1 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_RED][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_RED][0].EffectSpriteType		= EFFECTSPRITETYPE_TIPOJYU_HADES_COUNT_BOSS_ATTACK_A;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_RED][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_RED][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_HADES_COUNT_BOSS_ATTACK_A];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_RED][0].LinkCount			= 0;
 	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_A_RED].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_GUSION_A_RED );	// 맞는 결과를 표현한다.
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_GUSION_A_RED].Set("RESULT_SKILL_TIFFAUGES_GUSION_A_RED", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_GUSION_A_RED].SetSoundID( SOUNDID_NULL );
	
	//과거 남자 백작 대장 스킬 B
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_RED].Set("SKILL_TIFFAUGES_GUSION_B_BLUE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_RED].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_RED].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_RED].SetCastingStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_RED].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_RED].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_RED].Init( 2 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_RED][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_RED][0].EffectSpriteType		= EFFECTSPRITETYPE_TIPOJYU_HADES_COUNT_BOSS_ATTACK_B_1;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_RED][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_RED][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_HADES_COUNT_BOSS_ATTACK_B_1];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_RED][0].LinkCount			= FrameSize[EFFECTSPRITETYPE_TIPOJYU_HADES_COUNT_BOSS_ATTACK_B_1];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_RED][1].EffectGeneratorID	= EFFECTGENERATORID_AROUND_ZONE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_RED][1].EffectSpriteType		= EFFECTSPRITETYPE_TIPOJYU_HADES_COUNT_BOSS_ATTACK_B_2;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_RED][1].Step					= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_RED][1].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_HADES_COUNT_BOSS_ATTACK_B_2];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_RED][1].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_B_RED].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_GUSION_B_RED );	// 맞는 결과를 표현한다.
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_GUSION_B_RED].Set("RESULT_SKILL_TIFFAUGES_GUSION_B_RED", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_GUSION_B_RED].SetSoundID( SOUNDID_NULL );

	//과거 남자 백작 대장 스킬 C //흡혈 이미지를 마법 모션으로 대치 했다.(흡혈 당하지 않는다.)
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_RED].Set("SKILL_TIFFAUGES_GUSION_C_RED", ACTION_DRAINED, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_RED].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_RED].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_RED].SetCastingStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_RED].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_RED].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_RED].Init( 1 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_RED][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_RECT_RANDOM_PIXEL;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_RED][0].EffectSpriteType		= EFFECTSPRITETYPE_TIPOJYU_HADES_COUNT_BOSS_ATTACK_C;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_RED][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_RED][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_HADES_COUNT_BOSS_ATTACK_C];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_RED][0].LinkCount			= 0;
 	(*g_pActionInfoTable)[SKILL_TIFFAUGES_GUSION_C_RED].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_GUSION_C_RED );	// 맞는 결과를 표현한다.
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_GUSION_C_RED].Set("RESULT_SKILL_TIFFAUGES_GUSION_C_RED", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_GUSION_C_RED].SetSoundID( SOUNDID_NULL );



	
	
	//현세 경비병 스킬
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_BLUE].Set("SKILL_TIFFAUGES_PAIMON_BLUE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_BLUE].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_BLUE].SetStartFrameAll( 8 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_BLUE].SetCastingStartFrameAll( 8 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_BLUE].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_BLUE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_BLUE].Init( 2 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_BLUE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_BLUE][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_PATROL_ATTACK_A;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_BLUE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_BLUE][0].Count				= 0;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_BLUE][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_RECT_RANDOM_PIXEL;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_BLUE][1].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_PATROL_ATTACK_A;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_BLUE][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_BLUE][1].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_PATROL_ATTACK_A];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_BLUE][1].LinkCount			= 0;
 	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_BLUE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_PAIMON_BLUE );	// 맞는 결과를 표현한다.
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_PAIMON_BLUE].Set("RESULT_SKILL_TIFFAUGES_PAIMON_BLUE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_PAIMON_BLUE].SetSoundID( SOUNDID_NULL );

	//과거 경비병 스킬
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_RED].Set("SKILL_TIFFAUGES_PAIMON_RED", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_RED].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_RED].SetStartFrameAll( 8 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_RED].SetCastingStartFrameAll( 8 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_RED].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_RED].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_RED].Init( 2 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_RED][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_RED][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_HADES_PATROL_ATTACK_A;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_RED][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_RED][0].Count				= 0;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_RED][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_RECT_RANDOM_PIXEL;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_RED][1].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_HADES_PATROL_ATTACK_A;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_RED][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_RED][1].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_HADES_PATROL_ATTACK_A];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_RED][1].LinkCount			= 0;
 	(*g_pActionInfoTable)[SKILL_TIFFAUGES_PAIMON_RED].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_PAIMON_RED );	// 맞는 결과를 표현한다.
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_PAIMON_RED].Set("RESULT_SKILL_TIFFAUGES_PAIMON_RED", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_PAIMON_RED].SetSoundID( SOUNDID_NULL );



	
	//현세 웨버데스 스킬 A
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_BLUE].Set("SKILL_TIFFAUGES_MORGOTH_A_BLUE", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_BLUE].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_BLUE].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_BLUE].SetCastingStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_BLUE].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_BLUE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_BLUE].Init( 1 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_BLUE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_BLUE][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_WARVERDESS_ATTACK_A;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_BLUE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_BLUE][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_WARVERDESS_ATTACK_A] - 4;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_BLUE][0].LinkCount			= 0;
 	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_BLUE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_MORGOTH_A_BLUE );	// 맞는 결과를 표현한다.
 	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_MORGOTH_A_BLUE].Set("RESULT_SKILL_TIFFAUGES_MORGOTH_A_BLUE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_MORGOTH_A_BLUE].SetSoundID( SOUNDID_NULL );	

	//현세 웨버데스 스킬 B //흡혈 이미지를 마법 모션으로 대치 했다.(흡혈 당하지 않는다.)
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_BLUE].Set("SKILL_TIFFAUGES_MORGOTH_B_BLUE", ACTION_DRAINED, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_BLUE].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_BLUE].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_BLUE].SetCastingStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_BLUE].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_BLUE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_BLUE].Init( 2 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_BLUE][0].EffectGeneratorID	= EFFECTGENERATORID_MULTIPLE_FALLING;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_BLUE][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_WARVERDESS_ATTACK_B_1;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_BLUE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_BLUE][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_WARVERDESS_ATTACK_B_1];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_BLUE][0].LinkCount			= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_WARVERDESS_ATTACK_B_1];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_BLUE][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_RECT_RANDOM_PIXEL;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_BLUE][1].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_WARVERDESS_ATTACK_B_2;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_BLUE][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_BLUE][1].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_WARVERDESS_ATTACK_B_2];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_BLUE][1].LinkCount			= 0;
 	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_BLUE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_MORGOTH_B_BLUE );	// 맞는 결과를 표현한다.
 	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_MORGOTH_B_BLUE].Set("RESULT_SKILL_TIFFAUGES_MORGOTH_B_BLUE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_MORGOTH_B_BLUE].SetSoundID( SOUNDID_NULL );	

	//현세 웨버데스 스킬 C
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_BLUE].Set("SKILL_TIFFAUGES_MORGOTH_C_BLUE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_BLUE].SetCastingStartFrameAll( 1 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_BLUE].SetStartFrameAll( 16 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_BLUE].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_BLUE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_BLUE][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_WARVERDESS_ATTACK_C;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_BLUE][0].Step				= 30;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_BLUE][0].Count				= 0;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_BLUE][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_RECT_RANDOM_PIXEL;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_BLUE][1].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_WARVERDESS_ATTACK_C;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_BLUE][1].Step				= 20;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_BLUE][1].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_WARVERDESS_ATTACK_C];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_BLUE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_MORGOTH_C_BLUE );	// 맞는 결과를 표현한다.	
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_MORGOTH_C_BLUE].Set("RESULT_SKILL_TIFFAUGES_MORGOTH_C_BLUE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_MORGOTH_C_BLUE].SetSoundID( SOUNDID_NULL );

	//과거 웨버데스 스킬 A
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_RED].Set("SKILL_TIFFAUGES_MORGOTH_A_RED", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_RED].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_RED].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_RED].SetCastingStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_RED].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_RED].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_RED].Init( 1 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_RED][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_RED][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_HADES_WARVERDESS_ATTACK_A;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_RED][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_RED][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_HADES_WARVERDESS_ATTACK_A] - 4;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_RED][0].LinkCount			= 0;
 	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_A_RED].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_MORGOTH_A_RED );	// 맞는 결과를 표현한다.
 	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_MORGOTH_A_RED].Set("RESULT_SKILL_TIFFAUGES_MORGOTH_A_RED", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_MORGOTH_A_RED].SetSoundID( SOUNDID_NULL );	

	//과거 웨버데스 스킬 B
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_RED].Set("SKILL_TIFFAUGES_MORGOTH_B_RED", ACTION_DRAINED, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_RED].SetUser(FLAG_ACTIONINFO_USER_ALL);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_RED].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_RED].SetCastingStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_RED].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_RED].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_RED].Init( 2 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_RED][0].EffectGeneratorID	= EFFECTGENERATORID_MULTIPLE_FALLING;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_RED][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_HADES_WARVERDESS_ATTACK_B_1;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_RED][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_RED][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_HADES_WARVERDESS_ATTACK_B_1];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_RED][0].LinkCount			= FrameSize[EFFECTSPRITETYPE_TIPOJYU_HADES_WARVERDESS_ATTACK_B_1];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_RED][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_RECT_RANDOM_PIXEL;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_RED][1].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_HADES_WARVERDESS_ATTACK_B_2;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_RED][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_RED][1].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_HADES_WARVERDESS_ATTACK_B_2];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_RED][1].LinkCount			= 0;
 	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_B_RED].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_MORGOTH_B_RED );	// 맞는 결과를 표현한다.
 	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_MORGOTH_B_RED].Set("RESULT_SKILL_TIFFAUGES_MORGOTH_B_RED", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_MORGOTH_B_RED].SetSoundID( SOUNDID_NULL );	

	//과거 웨버데스 스킬 C
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_RED].Set("SKILL_TIFFAUGES_MORGOTH_C_RED", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_RED].SetCastingStartFrameAll( 1 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_RED].SetStartFrameAll( 16 );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_RED].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_RED][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_RED][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_HADES_WARVERDESS_ATTACK_C;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_RED][0].Step				= 30;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_RED][0].Count				= 0;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_RED][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_RECT_RANDOM_PIXEL;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_RED][1].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_HADES_WARVERDESS_ATTACK_C;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_RED][1].Step				= 20;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_RED][1].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_HADES_WARVERDESS_ATTACK_C];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_MORGOTH_C_RED].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TIFFAUGES_MORGOTH_C_RED );	// 맞는 결과를 표현한다.	
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_MORGOTH_C_RED].Set("RESULT_SKILL_TIFFAUGES_MORGOTH_C_RED", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_MORGOTH_C_RED].SetSoundID( SOUNDID_NULL );

#endif // __TIPOJYU_CASTLE
#if __CONTENTS(__2008_OCTOBER_MAKETITEM)	
	(*g_pActionInfoTable)[SKILL_CLIENT_BEARBOX_SUMMON].Set("SKILL_CLIENT_BEARBOX_SUMMON",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_STAND]);
	(*g_pActionInfoTable)[SKILL_CLIENT_BEARBOX_SUMMON].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_BEARBOX_SUMMON].Init( 4 );
	(*g_pActionInfoTable)[SKILL_CLIENT_BEARBOX_SUMMON][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_BEARBOX_SUMMON][0].EffectSpriteType = EFFECTSPRITETYPE_BEARBOX_SUMMON;
	(*g_pActionInfoTable)[SKILL_CLIENT_BEARBOX_SUMMON][0].Step						= 30;
	(*g_pActionInfoTable)[SKILL_CLIENT_BEARBOX_SUMMON][0].Count					=FrameSize[EFFECTSPRITETYPE_BEARBOX_SUMMON];
	(*g_pActionInfoTable)[SKILL_CLIENT_BEARBOX_SUMMON][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_BEARBOX_SUMMON][1].EffectSpriteType = EFFECTSPRITETYPE_BEARBOX_FRONT;
	(*g_pActionInfoTable)[SKILL_CLIENT_BEARBOX_SUMMON][1].Step						= 30;
	(*g_pActionInfoTable)[SKILL_CLIENT_BEARBOX_SUMMON][1].Count					=FrameSize[EFFECTSPRITETYPE_BEARBOX_FRONT];
	(*g_pActionInfoTable)[SKILL_CLIENT_BEARBOX_SUMMON][2].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_BEARBOX_SUMMON][2].EffectSpriteType = EFFECTSPRITETYPE_BEARBOX_BOTTOM;
	(*g_pActionInfoTable)[SKILL_CLIENT_BEARBOX_SUMMON][2].Step						= 30;
	(*g_pActionInfoTable)[SKILL_CLIENT_BEARBOX_SUMMON][2].Count					=16;
	(*g_pActionInfoTable)[SKILL_CLIENT_BEARBOX_SUMMON][3].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_BEARBOX_SUMMON][3].EffectSpriteType = EFFECTSPRITETYPE_BEARBOX_DESTROY;
	(*g_pActionInfoTable)[SKILL_CLIENT_BEARBOX_SUMMON][3].Step						= 30;
	(*g_pActionInfoTable)[SKILL_CLIENT_BEARBOX_SUMMON][3].Count					=FrameSize[EFFECTSPRITETYPE_BEARBOX_DESTROY];

	(*g_pActionInfoTable)[SKILL_CLIENT_SUCCUBUS_SUMMON].Set("SKILL_CLIENT_SUCCUBUS_SUMMON",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_STAND]);
	(*g_pActionInfoTable)[SKILL_CLIENT_SUCCUBUS_SUMMON].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_SUCCUBUS_SUMMON].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_SUCCUBUS_SUMMON][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_SUCCUBUS_SUMMON][0].EffectSpriteType = EFFECTSPRITETYPE_SUCCUBUS_SUMMON_FRONT;
	(*g_pActionInfoTable)[SKILL_CLIENT_SUCCUBUS_SUMMON][0].Step						= 30;
	(*g_pActionInfoTable)[SKILL_CLIENT_SUCCUBUS_SUMMON][0].Count					=FrameSize[EFFECTSPRITETYPE_SUCCUBUS_SUMMON_FRONT];

	(*g_pActionInfoTable)[SKILL_CLIENT_FIREELEMENTAL_SUMMON].Set("SKILL_CLIENT_FIREELEMENTAL_SUMMON",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_STAND]);
	(*g_pActionInfoTable)[SKILL_CLIENT_FIREELEMENTAL_SUMMON].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_FIREELEMENTAL_SUMMON].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_FIREELEMENTAL_SUMMON][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_FIREELEMENTAL_SUMMON][0].EffectSpriteType = EFFECTSPRITETYPE_FIREELEMENTAL_SUMMON;
	(*g_pActionInfoTable)[SKILL_CLIENT_FIREELEMENTAL_SUMMON][0].Step						= 30;
	(*g_pActionInfoTable)[SKILL_CLIENT_FIREELEMENTAL_SUMMON][0].Count					=FrameSize[EFFECTSPRITETYPE_SUCCUBUS_SUMMON_FRONT];
#endif //__2008_OCTOBER_MAKETITEM

#if __CONTENTS(__PET_MASHIMARO)
	(*g_pActionInfoTable)[SKILL_CLIENT_MASHIMARO_SUMMON].Set("SKILL_CLIENT_MASHIMARO_SUMMON",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_STAND]);
	(*g_pActionInfoTable)[SKILL_CLIENT_MASHIMARO_SUMMON].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_MASHIMARO_SUMMON].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_MASHIMARO_SUMMON][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_MASHIMARO_SUMMON][0].EffectSpriteType = EFFECTSPRITETYPE_MASHIMARO_SUMMON_FRONT;
	(*g_pActionInfoTable)[SKILL_CLIENT_MASHIMARO_SUMMON][0].Step						= 30;
	(*g_pActionInfoTable)[SKILL_CLIENT_MASHIMARO_SUMMON][0].Count					=FrameSize[EFFECTSPRITETYPE_MASHIMARO_SUMMON_FRONT];
#endif//__PET_MASHIMARO

#if __CONTENTS(__PET_CATS)
	(*g_pActionInfoTable)[SKILL_CLIENT_CATS_SUMMON].Set("SKILL_CLIENT_CATS_SUMMON",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_STAND]);
	(*g_pActionInfoTable)[SKILL_CLIENT_CATS_SUMMON].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_CATS_SUMMON].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_CATS_SUMMON][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_CATS_SUMMON][0].EffectSpriteType = EFFECTSPRITETYPE_CATS_SUMMON_FRONT;
	(*g_pActionInfoTable)[SKILL_CLIENT_CATS_SUMMON][0].Step						= 30;
	(*g_pActionInfoTable)[SKILL_CLIENT_CATS_SUMMON][0].Count					=FrameSize[EFFECTSPRITETYPE_CATS_SUMMON_FRONT];
#endif//__PET_CATS
#if __CONTENTS(__PET_CATS_UPGRADED)
	(*g_pActionInfoTable)[SKILL_CLIENT_CATS_SUMMON].Set("SKILL_CLIENT_CATS_SUMMON",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_STAND]);
	(*g_pActionInfoTable)[SKILL_CLIENT_CATS_SUMMON].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_CATS_SUMMON].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_CATS_SUMMON][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_CATS_SUMMON][0].EffectSpriteType = EFFECTSPRITETYPE_CATS_SUMMON_FRONT;
	(*g_pActionInfoTable)[SKILL_CLIENT_CATS_SUMMON][0].Step						= 30;
	(*g_pActionInfoTable)[SKILL_CLIENT_CATS_SUMMON][0].Count					=FrameSize[EFFECTSPRITETYPE_CATS_SUMMON_FRONT];
#endif//__PET_CATS_UPGRADED


//	(*g_pActionInfoTable)[RESULT_SKILL_SOUND_WAVE].Set("RESULT_SKILL_SOUND_WAVE", ACTION_STAND , EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, 400);
//	(*g_pActionInfoTable)[RESULT_SKILL_SOUND_WAVE].SetSoundID( SOUNDID_NULL );
				
/*	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT].Set("SKILL_VAMPIRE_COMBO_EFFECT", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT].Init( 1 );
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][0].EffectSpriteType  = EFFECTSPRITETYPE_SHARP_ROUND_1_3;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][0].Step			     = 0;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][0].Count			 = FrameSize[EFFECTSPRITETYPE_SHARP_ROUND_1_3];
*/
	/*
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO].Set("SKILL_VAMPIRE_COMBO", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 2, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO].SetStartFrameAll( 4 );
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO].SetComboAttackSkill(TRUE);
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO].SetComboActionResultEffect(SKILL_VAMPIRE_COMBO_EFFECT) ; 


	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT].Set("SKILL_VAMPIRE_COMBO_EFFECT", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 2, FLAG_ACTIONINFO_TARGET_OTHER);	
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT].SetStartFrameAll( 4 );
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT].SetSoundID( SOUNDID_NULL );
	//(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT].SetComboAttackSkill(TRUE);
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT].Init( 4 );
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][0].EffectSpriteType = EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_1;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][0].Step				= 0;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][0].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_1];
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][0].LinkCount			= 2;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][1].EffectSpriteType = EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_2;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][1].Step				= 0;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][1].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_2];
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][1].LinkCount			= 2;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][2].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][2].EffectSpriteType = EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_3;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][2].Step				= 0;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][2].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_3];
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][2].LinkCount			= 2;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][3].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][3].EffectSpriteType = EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_4;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][3].Step				= 0;
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][3].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_4];
	(*g_pActionInfoTable)[SKILL_VAMPIRE_COMBO_EFFECT][3].LinkCount			= 2;
	//2005.07.13, Sjheon ComboSkill End */

	return TRUE;
}
