#include "StdAfx.h"
#include <fstream>

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

HRESULT InitFail(LPCTSTR szError,...);
bool 
FileOpenBinary(const char* filename, ivfstream& file);
//---------------------------------------------------------------------------
// Open File
//---------------------------------------------------------------------------
bool 
FileCheck(const char* filename);

#define SAVE_TO_FILE

BOOL	InitSoundTable()
{
	///*
#ifdef SAVE_TO_FILE
	(*g_pSoundTable).Init( MAX_SOUND );

	//for (i=0; i<MAX_SOUND; i++)
	//{		
		//(*g_pSoundTable)[i].Filename.Format("Data\\Sound\\Sound#%d.wav", i);		 
	//}
	char PATH_SOUND[256];
	strcpy(PATH_SOUND, g_pFileDef->getProperty("PATH_SOUND").c_str());

	//-------------------------------------------------------
	// slayer 행동	
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_SLAYER_ATTACK_BARE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ATTACK_BARE.wav");
	(*g_pSoundTable)[SOUND_SLAYER_ATTACK_KICK].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ATTACK_KICK.wav");
	(*g_pSoundTable)[SOUND_SLAYER_ATTACK_MELEE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ATTACK_MELEE.wav");
	(*g_pSoundTable)[SOUND_SLAYER_ATTACK_AR].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ATTACK_AR.wav");
	(*g_pSoundTable)[SOUND_SLAYER_ATTACK_SMG].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ATTACK_SMG.wav");
	(*g_pSoundTable)[SOUND_SLAYER_ATTACK_BOMB].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ATTACK_BOMB.wav");
	(*g_pSoundTable)[SOUND_SLAYER_ATTACK_BOTTLE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ATTACK_BOTTLE.wav");
	(*g_pSoundTable)[SOUND_SLAYER_DIE_MALE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_DIE_MALE.wav");
	(*g_pSoundTable)[SOUND_SLAYER_DIE_FEMALE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_DIE_FEMALE.wav");
	(*g_pSoundTable)[SOUND_SLAYER_DAMAGE_MALE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_DAMAGE_MALE.wav");
	(*g_pSoundTable)[SOUND_SLAYER_DAMAGE_FEMALE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_DAMAGE_FEMALE.wav");
	(*g_pSoundTable)[SOUND_SLAYER_DRAINED_MALE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_DRAINED_MALE.wav");
	(*g_pSoundTable)[SOUND_SLAYER_DRAINED_FEMALE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_DRAINED_FEMALE.wav");
	(*g_pSoundTable)[SOUND_SLAYER_SWORD_MALE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_SWORD_MALE.wav");
	(*g_pSoundTable)[SOUND_SLAYER_SWORD_FEMALE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_SWORD_FEMALE.wav");
	(*g_pSoundTable)[SOUND_SLAYER_MAGIC_MALE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_MAGIC_MALE.wav");
	(*g_pSoundTable)[SOUND_SLAYER_MAGIC_FEMALE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_MAGIC_FEMALE.wav");

	//-------------------------------------------------------
	// Item
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_ITEM_MOVE_CLOTH].Filename.Format("%s%s", PATH_SOUND, "ITEM_MOVE_CLOTH.wav");
	(*g_pSoundTable)[SOUND_ITEM_MOVE_SWORD].Filename.Format("%s%s", PATH_SOUND, "ITEM_MOVE_SWORD.wav");
	(*g_pSoundTable)[SOUND_ITEM_MOVE_GUN].Filename.Format("%s%s", PATH_SOUND, "ITEM_MOVE_GUN.wav");
	(*g_pSoundTable)[SOUND_ITEM_MOVE_SHIELD].Filename.Format("%s%s", PATH_SOUND, "ITEM_MOVE_SHIELD.wav");
	(*g_pSoundTable)[SOUND_ITEM_MOVE_BRACELET].Filename.Format("%s%s", PATH_SOUND, "ITEM_MOVE_BRACELET.wav");
	(*g_pSoundTable)[SOUND_ITEM_MOVE_SHOES].Filename.Format("%s%s", PATH_SOUND, "ITEM_MOVE_SHOES.wav");
	(*g_pSoundTable)[SOUND_ITEM_MOVE_GLOVE].Filename.Format("%s%s", PATH_SOUND, "ITEM_MOVE_GLOVE.wav");
	(*g_pSoundTable)[SOUND_ITEM_MOVE_HELM].Filename.Format("%s%s", PATH_SOUND, "ITEM_MOVE_HELM.wav");
	(*g_pSoundTable)[SOUND_ITEM_MOVE_BELT].Filename.Format("%s%s", PATH_SOUND, "ITEM_MOVE_BELT.wav");
	(*g_pSoundTable)[SOUND_ITEM_MOVE_MAGAZINE].Filename.Format("%s%s", PATH_SOUND, "ITEM_MOVE_MAGAZINE.wav");
	(*g_pSoundTable)[SOUND_ITEM_MOVE_SCROLL].Filename.Format("%s%s", PATH_SOUND, "ITEM_MOVE_SCROLL.wav");
	(*g_pSoundTable)[SOUND_ITEM_MOVE_KEY].Filename.Format("%s%s", PATH_SOUND, "ITEM_MOVE_KEY.wav");
	(*g_pSoundTable)[SOUND_ITEM_MOVE_BOMB].Filename.Format("%s%s", PATH_SOUND, "ITEM_MOVE_BOMB.wav");
	(*g_pSoundTable)[SOUND_ITEM_MOVE_BOTTLE].Filename.Format("%s%s", PATH_SOUND, "ITEM_MOVE_BOTTLE.wav");
	(*g_pSoundTable)[SOUND_ITEM_MOVE_C4].Filename.Format("%s%s", PATH_SOUND, "ITEM_MOVE_C4.wav");
	(*g_pSoundTable)[SOUND_ITEM_MOVE_SKULL].Filename.Format("%s%s", PATH_SOUND, "ITEM_MOVE_SKULL.wav");
	(*g_pSoundTable)[SOUND_ITEM_MOVE_MONEY].Filename.Format("%s%s", PATH_SOUND, "ITEM_MOVE_MONEY.wav");
	(*g_pSoundTable)[SOUND_ITEM_MOVE_POTION].Filename.Format("%s%s", PATH_SOUND, "ITEM_MOVE_POTION.wav");
	(*g_pSoundTable)[SOUND_ITEM_USE_MPOTION].Filename.Format("%s%s", PATH_SOUND, "ITEM_USE_MPOTION.wav");
	(*g_pSoundTable)[SOUND_ITEM_USE_HPOTION].Filename.Format("%s%s", PATH_SOUND, "ITEM_USE_HPOTION.wav");
	(*g_pSoundTable)[SOUND_ITEM_USE_SCROLL].Filename.Format("%s%s", PATH_SOUND, "ITEM_USE_SCROLL.wav");
	(*g_pSoundTable)[SOUND_ITEM_USE_C4].Filename.Format("%s%s", PATH_SOUND, "ITEM_USE_C4.wav");
	(*g_pSoundTable)[SOUND_ITEM_USE_MAGAZINE].Filename.Format("%s%s", PATH_SOUND, "ITEM_USE_MAGAZINE.wav");
	(*g_pSoundTable)[SOUND_ITEM_NO_MAGAZINE].Filename.Format("%s%s", PATH_SOUND, "ITEM_NO_MAGAZINE.wav");
	(*g_pSoundTable)[SOUND_ITEM_FLYING_BOMB].Filename.Format("%s%s", PATH_SOUND, "ITEM_FLYING_BOMB.wav");
	(*g_pSoundTable)[SOUND_ITEM_FLYING_BOTTLE].Filename.Format("%s%s", PATH_SOUND, "ITEM_FLYING_BOTTLE.wav");
	(*g_pSoundTable)[SOUND_DAMAGE_BOMB].Filename.Format("%s%s", PATH_SOUND, "DAMAGE_BOMB.wav");
	(*g_pSoundTable)[SOUND_DAMAGE_BOTTLE].Filename.Format("%s%s", PATH_SOUND, "DAMAGE_BOTTLE.wav");
	(*g_pSoundTable)[SOUND_DAMAGE_GUN].Filename.Format("%s%s", PATH_SOUND, "DAMAGE_GUN.wav");
	(*g_pSoundTable)[SOUND_WORLD_BIKE_GO].Filename.Format("%s%s", PATH_SOUND, "WORLD_BIKE_GO.wav");
	(*g_pSoundTable)[SOUND_WORLD_BIKE_RUN].Filename.Format("%s%s", PATH_SOUND, "WORLD_BIKE_RUN.wav");
	(*g_pSoundTable)[SOUND_WORLD_BIKE_STOP].Filename.Format("%s%s", PATH_SOUND, "WORLD_BIKE_STOP.wav");
	(*g_pSoundTable)[SOUND_WORLD_BIKE_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "WORLD_BIKE_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_WORLD_BIKE_EXPLODE].Filename.Format("%s%s", PATH_SOUND, "WORLD_BIKE_EXPLODE.wav");

	// 2006.09.18 New Sound 
	(*g_pSoundTable)[SOUND_THROW_HOLY_WATER].Filename.Format("%s%s", PATH_SOUND, "THROW_HOLY_WATER.wav") ;
	(*g_pSoundTable)[SOUND_SPIT_STREAM].Filename.Format("%s%s", PATH_SOUND, "SPIT_STREAM.wav") ;

	//-------------------------------------------------------
	// Interface
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_PDS_MENU].Filename.Format("%s%s", PATH_SOUND, "PDS_MENU.wav");
	(*g_pSoundTable)[SOUND_PCS_1].Filename.Format("%s%s", PATH_SOUND, "PCS_1.wav");
	(*g_pSoundTable)[SOUND_PCS_2].Filename.Format("%s%s", PATH_SOUND, "PCS_2.wav");
	(*g_pSoundTable)[SOUND_PCS_3].Filename.Format("%s%s", PATH_SOUND, "PCS_3.wav");
	(*g_pSoundTable)[SOUND_PCS_4].Filename.Format("%s%s", PATH_SOUND, "PCS_4.wav");
	(*g_pSoundTable)[SOUND_PCS_5].Filename.Format("%s%s", PATH_SOUND, "PCS_5.wav");
	(*g_pSoundTable)[SOUND_PCS_6].Filename.Format("%s%s", PATH_SOUND, "PCS_6.wav");
	(*g_pSoundTable)[SOUND_PCS_7].Filename.Format("%s%s", PATH_SOUND, "PCS_7.wav");
	(*g_pSoundTable)[SOUND_PCS_8].Filename.Format("%s%s", PATH_SOUND, "PCS_8.wav");
	(*g_pSoundTable)[SOUND_PCS_9].Filename.Format("%s%s", PATH_SOUND, "PCS_9.wav");
	(*g_pSoundTable)[SOUND_PCS_0].Filename.Format("%s%s", PATH_SOUND, "PCS_0.wav");
	(*g_pSoundTable)[SOUND_PCS_STAR].Filename.Format("%s%s", PATH_SOUND, "PCS_STAR.wav");
	(*g_pSoundTable)[SOUND_PCS_SHARP].Filename.Format("%s%s", PATH_SOUND, "PCS_SHARP.wav");
	(*g_pSoundTable)[SOUND_PDS_ETC].Filename.Format("%s%s", PATH_SOUND, "PDS_ETC.wav");
	(*g_pSoundTable)[SOUND_SLAYER_BELT].Filename.Format("%s%s", PATH_SOUND, "SLAYER_BELT.wav");
	(*g_pSoundTable)[SOUND_SLAYER_SKILL].Filename.Format("%s%s", PATH_SOUND, "SLAYER_SKILL.wav");
	(*g_pSoundTable)[SOUND_SLAYER_BUTTON].Filename.Format("%s%s", PATH_SOUND, "SLAYER_BUTTON.wav");
	(*g_pSoundTable)[SOUND_SLAYER_MENU].Filename.Format("%s%s", PATH_SOUND, "SLAYER_MENU.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_ICON].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_ICON.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_BUTTON].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_BUTTON.wav");


	//-------------------------------------------------------
	// PC Vampire행동
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_VAMPIRE_ATTACK].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_ATTACK.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_CHANGE_MALE].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_CHANGE_MALE.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_CHANGE_FEMALE].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_CHANGE_FEMALE.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_DAMAGE_MALE].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_DAMAGE_MALE.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_DAMAGE_FEMALE].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_DAMAGE_FEMALE.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_DIE_MALE].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_DIE_MALE.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_DIE_FEMALE].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_DIE_FEMALE.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_DRAINED_MALE].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_DRAINED_MALE.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_DRAINED_FEMALE].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_DRAINED_FEMALE.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_DRAIN_MALE].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_DRAIN_MALE.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_DRAIN_FEMALE].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_DRAIN_FEMALE.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_MAGIC].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_MAGIC.wav");
	
	//-------------------------------------------------------
	// 데드 바디
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_DB_ATTACK].Filename.Format("%s%s", PATH_SOUND, "DB_ATTACK.wav");
	(*g_pSoundTable)[SOUND_DB_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "DB_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_DB_DIE].Filename.Format("%s%s", PATH_SOUND, "DB_DIE.wav");
	(*g_pSoundTable)[SOUND_DB_DRAINED].Filename.Format("%s%s", PATH_SOUND, "DB_DRAINED.wav");
	(*g_pSoundTable)[SOUND_DB_DRAIN].Filename.Format("%s%s", PATH_SOUND, "DB_DRAIN.wav");

	//-------------------------------------------------------
	// 터닝 데드
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_TD_ATTACK].Filename.Format("%s%s", PATH_SOUND, "TD_ATTACK.wav");
	(*g_pSoundTable)[SOUND_TD_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "TD_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_TD_DIE].Filename.Format("%s%s", PATH_SOUND, "TD_DIE.wav");
	(*g_pSoundTable)[SOUND_TD_DRAINED].Filename.Format("%s%s", PATH_SOUND, "TD_DRAINED.wav");
	(*g_pSoundTable)[SOUND_TD_DRAIN].Filename.Format("%s%s", PATH_SOUND, "TD_DRAIN.wav");

	//-------------------------------------------------------
	// 터닝 소울
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_TS_ATTACK].Filename.Format("%s%s", PATH_SOUND, "TS_ATTACK.wav");
	(*g_pSoundTable)[SOUND_TS_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "TS_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_TS_DIE].Filename.Format("%s%s", PATH_SOUND, "TS_DIE.wav");
	(*g_pSoundTable)[SOUND_TS_DRAINED].Filename.Format("%s%s", PATH_SOUND, "TS_DRAINED.wav");
	(*g_pSoundTable)[SOUND_TS_DRAIN].Filename.Format("%s%s", PATH_SOUND, "TS_DRAIN.wav");

	//-------------------------------------------------------
	// 키드
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_K_ATTACK].Filename.Format("%s%s", PATH_SOUND, "K_ATTACK.wav");
	(*g_pSoundTable)[SOUND_K_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "K_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_K_DIE].Filename.Format("%s%s", PATH_SOUND, "K_DIE.wav");
	(*g_pSoundTable)[SOUND_K_DRAINED].Filename.Format("%s%s", PATH_SOUND, "K_DRAINED.wav");
	(*g_pSoundTable)[SOUND_K_DRAIN].Filename.Format("%s%s", PATH_SOUND, "K_DRAIN.wav");

	//-------------------------------------------------------
	// 솔져 
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_S_ATTACK].Filename.Format("%s%s", PATH_SOUND, "S_ATTACK.wav");
	(*g_pSoundTable)[SOUND_S_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "S_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_S_DIE].Filename.Format("%s%s", PATH_SOUND, "S_DIE.wav");
	(*g_pSoundTable)[SOUND_S_DRAINED].Filename.Format("%s%s", PATH_SOUND, "S_DRAINED.wav");
	(*g_pSoundTable)[SOUND_S_DRAIN].Filename.Format("%s%s", PATH_SOUND, "S_DRAIN.wav");

	//-------------------------------------------------------
	// 캡틴
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_C_ATTACK].Filename.Format("%s%s", PATH_SOUND, "C_ATTACK.wav");
	(*g_pSoundTable)[SOUND_C_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "C_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_C_DIE].Filename.Format("%s%s", PATH_SOUND, "C_DIE.wav");
	(*g_pSoundTable)[SOUND_C_DRAINED].Filename.Format("%s%s", PATH_SOUND, "C_DRAINED.wav");
	(*g_pSoundTable)[SOUND_C_DRAIN].Filename.Format("%s%s", PATH_SOUND, "C_DRAIN.wav");

	//-------------------------------------------------------
	// 섀도우 윙
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_SW_ATTACK].Filename.Format("%s%s", PATH_SOUND, "SW_ATTACK.wav");
	(*g_pSoundTable)[SOUND_SW_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "SW_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_SW_DIE].Filename.Format("%s%s", PATH_SOUND, "SW_DIE.wav");
	(*g_pSoundTable)[SOUND_SW_DRAINED].Filename.Format("%s%s", PATH_SOUND, "SW_DRAINED.wav");
	(*g_pSoundTable)[SOUND_SW_DRAIN].Filename.Format("%s%s", PATH_SOUND, "SW_DRAIN.wav");
	(*g_pSoundTable)[SOUND_SW_MAGIC].Filename.Format("%s%s", PATH_SOUND, "SW_MAGIC.wav");

	//-------------------------------------------------------
	// 더티 스트라이더
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_DS_ATTACK].Filename.Format("%s%s", PATH_SOUND, "DS_ATTACK.wav");
	(*g_pSoundTable)[SOUND_DS_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "DS_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_DS_DIE].Filename.Format("%s%s", PATH_SOUND, "DS_DIE.wav");
	(*g_pSoundTable)[SOUND_DS_DRAINED].Filename.Format("%s%s", PATH_SOUND, "DS_DRAINED.wav");
	(*g_pSoundTable)[SOUND_DS_DRAIN].Filename.Format("%s%s", PATH_SOUND, "DS_DRAIN.wav");
	(*g_pSoundTable)[SOUND_DS_MAGIC].Filename.Format("%s%s", PATH_SOUND, "DS_MAGIC.wav");

	//-------------------------------------------------------
	// 블러드 워록
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_BW_ATTACK].Filename.Format("%s%s", PATH_SOUND, "BW_ATTACK.wav");
	(*g_pSoundTable)[SOUND_BW_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "BW_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_BW_DIE].Filename.Format("%s%s", PATH_SOUND, "BW_DIE.wav");
	(*g_pSoundTable)[SOUND_BW_DRAINED].Filename.Format("%s%s", PATH_SOUND, "BW_DRAINED.wav");
	(*g_pSoundTable)[SOUND_BW_DRAIN].Filename.Format("%s%s", PATH_SOUND, "BW_DRAIN.wav");
	(*g_pSoundTable)[SOUND_BW_MAGIC].Filename.Format("%s%s", PATH_SOUND, "BW_MAGIC.wav");

	//-------------------------------------------------------
	// 골레머
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_GO_MOVE].Filename.Format("%s%s", PATH_SOUND, "GO_MOVE.wav");
	(*g_pSoundTable)[SOUND_GO_ATTACK].Filename.Format("%s%s", PATH_SOUND, "GO_ATTACK.wav");
	(*g_pSoundTable)[SOUND_GO_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "GO_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_GO_DIE].Filename.Format("%s%s", PATH_SOUND, "GO_DIE.wav");
	(*g_pSoundTable)[SOUND_GO_DRAINED].Filename.Format("%s%s", PATH_SOUND, "GO_DRAINED.wav");
	(*g_pSoundTable)[SOUND_GO_DRAIN].Filename.Format("%s%s", PATH_SOUND, "GO_DRAIN.wav");

	//-------------------------------------------------------
	// 레드 아이
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_RE_ATTACK].Filename.Format("%s%s", PATH_SOUND, "RE_ATTACK.wav");
	(*g_pSoundTable)[SOUND_RE_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "RE_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_RE_DIE].Filename.Format("%s%s", PATH_SOUND, "RE_DIE.wav");
	(*g_pSoundTable)[SOUND_RE_DRAINED].Filename.Format("%s%s", PATH_SOUND, "RE_DRAINED.wav");
	(*g_pSoundTable)[SOUND_RE_DRAIN].Filename.Format("%s%s", PATH_SOUND, "RE_DRAIN.wav");
	(*g_pSoundTable)[SOUND_RE_MAGIC].Filename.Format("%s%s", PATH_SOUND, "RE_MAGIC.wav");

	//-------------------------------------------------------
	// 알칸
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_AL_ATTACK].Filename.Format("%s%s", PATH_SOUND, "AL_ATTACK.wav");
	(*g_pSoundTable)[SOUND_AL_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "AL_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_AL_DIE].Filename.Format("%s%s", PATH_SOUND, "AL_DIE.wav");
	(*g_pSoundTable)[SOUND_AL_DRAINED].Filename.Format("%s%s", PATH_SOUND, "AL_DRAINED.wav");
	(*g_pSoundTable)[SOUND_AL_DRAIN].Filename.Format("%s%s", PATH_SOUND, "AL_DRAIN.wav");
	(*g_pSoundTable)[SOUND_AL_MAGIC].Filename.Format("%s%s", PATH_SOUND, "AL_MAGIC.wav");

	//-------------------------------------------------------
	// 카오스 가디언
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_CG_ATTACK].Filename.Format("%s%s", PATH_SOUND, "CG_ATTACK.wav");
	(*g_pSoundTable)[SOUND_CG_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "CG_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_CG_DIE].Filename.Format("%s%s", PATH_SOUND, "CG_DIE.wav");
	(*g_pSoundTable)[SOUND_CG_DRAINED].Filename.Format("%s%s", PATH_SOUND, "CG_DRAINED.wav");
	(*g_pSoundTable)[SOUND_CG_DRAIN].Filename.Format("%s%s", PATH_SOUND, "CG_DRAIN.wav");

	//-------------------------------------------------------
	// 호블
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_HB_ATTACK].Filename.Format("%s%s", PATH_SOUND, "HB_ATTACK.wav");
	(*g_pSoundTable)[SOUND_HB_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "HB_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_HB_DIE].Filename.Format("%s%s", PATH_SOUND, "HB_DIE.wav");
	(*g_pSoundTable)[SOUND_HB_DRAINED].Filename.Format("%s%s", PATH_SOUND, "HB_DRAINED.wav");
	(*g_pSoundTable)[SOUND_HB_DRAIN].Filename.Format("%s%s", PATH_SOUND, "HB_DRAIN.wav");
	(*g_pSoundTable)[SOUND_HB_MAGIC].Filename.Format("%s%s", PATH_SOUND, "HB_MAGIC.wav");

	//-------------------------------------------------------
	// 환경
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_WORLD_DOG_BARK].Filename.Format("%s%s", PATH_SOUND, "WORLD_DOG_BARK.wav");
	(*g_pSoundTable)[SOUND_WORLD_DOG_GRRR].Filename.Format("%s%s", PATH_SOUND, "WORLD_DOG_GRRR.wav");
	(*g_pSoundTable)[SOUND_WORLD_DOG_KICKED].Filename.Format("%s%s", PATH_SOUND, "WORLD_DOG_KICKED.wav");
	(*g_pSoundTable)[SOUND_WORLD_WOLF_CRY].Filename.Format("%s%s", PATH_SOUND, "WORLD_WOLF_CRY.wav");
	(*g_pSoundTable)[SOUND_WORLD_CROW].Filename.Format("%s%s", PATH_SOUND, "WORLD_CROW.wav");
	(*g_pSoundTable)[SOUND_WORLD_BIRD].Filename.Format("%s%s", PATH_SOUND, "WORLD_BIRD.wav");
	(*g_pSoundTable)[SOUND_WORLD_WEATHER_RAIN_1].Filename.Format("%s%s", PATH_SOUND, "WORLD_WEATHER_RAIN_1.wav");
	(*g_pSoundTable)[SOUND_WORLD_WEATHER_RAIN_2].Filename.Format("%s%s", PATH_SOUND, "WORLD_WEATHER_RAIN_2.wav");
	(*g_pSoundTable)[SOUND_WORLD_WEATHER_THUNDER_1].Filename.Format("%s%s", PATH_SOUND, "WORLD_WEATHER_THUNDER_1.wav");
	(*g_pSoundTable)[SOUND_WORLD_WEATHER_THUNDER_2].Filename.Format("%s%s", PATH_SOUND, "WORLD_WEATHER_THUNDER_2.wav");
	(*g_pSoundTable)[SOUND_WORLD_WEATHER_WIND].Filename.Format("%s%s", PATH_SOUND, "WORLD_WEATHER_WIND.wav");
	(*g_pSoundTable)[SOUND_WORLD_DOOR_WOOD].Filename.Format("%s%s", PATH_SOUND, "WORLD_DOOR_WOOD.wav");
	(*g_pSoundTable)[SOUND_WORLD_DOOR_IRON].Filename.Format("%s%s", PATH_SOUND, "WORLD_DOOR_IRON.wav");
	(*g_pSoundTable)[SOUND_WORLD_WATER_DROP].Filename.Format("%s%s", PATH_SOUND, "WORLD_WATER_DROP.wav");
	
	//2004,04,27 sobeit 2nd pet sound add start
	(*g_pSoundTable)[SOUND_WORLD_CENTAURO_ATTACK].Filename.Format("%s%s", PATH_SOUND, "World_Centauro_attack.wav");
	(*g_pSoundTable)[SOUND_WORLD_CENTAURO_MOVE].Filename.Format("%s%s", PATH_SOUND, "World_Centauro_move.wav");
	(*g_pSoundTable)[SOUND_WORLD_CENTAURO_PICKUP].Filename.Format("%s%s", PATH_SOUND, "World_Centauro_pick.wav");
	(*g_pSoundTable)[SOUND_WORLD_STIRGE_ATTACK].Filename.Format("%s%s", PATH_SOUND, "World_Stirge_attack.wav");
	(*g_pSoundTable)[SOUND_WORLD_STIRGE_MOVE].Filename.Format("%s%s", PATH_SOUND, "World_Stirge_move.wav");
	(*g_pSoundTable)[SOUND_WORLD_PIXIE_ABSORB].Filename.Format("%s%s", PATH_SOUND, "World_Pixie_absorb.wav");
	(*g_pSoundTable)[SOUND_WORLD_PIXIE_MOVE].Filename.Format("%s%s", PATH_SOUND, "World_Pixie_move.wav");
	//2004,04,27 sobeit 2nd pet sound add end
	//-------------------------------------------------------
	// Slayer 검 기술
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_SLAYER_SWORD_DI].Filename.Format("%s%s", PATH_SOUND, "SLAYER_SWORD_DI.wav");
	(*g_pSoundTable)[SOUND_SLAYER_SWORD_TS].Filename.Format("%s%s", PATH_SOUND, "SLAYER_SWORD_TS.wav");
	(*g_pSoundTable)[SOUND_SLAYER_SWORD_SS].Filename.Format("%s%s", PATH_SOUND, "SLAYER_SWORD_SS.wav");
	(*g_pSoundTable)[SOUND_SLAYER_SWORD_RS].Filename.Format("%s%s", PATH_SOUND, "SLAYER_SWORD_RS.wav");
	(*g_pSoundTable)[SOUND_SLAYER_SWORD_THS].Filename.Format("%s%s", PATH_SOUND, "SLAYER_SWORD_THS.wav");

	// 2006.09.18  New Sound 
	(*g_pSoundTable)[SOUND_HURRICANE_COMBO].Filename.Format("%s%s", PATH_SOUND, "HURRICANE_COMBO.wav");
	(*g_pSoundTable)[SOUND_SLAYER_SWORD_DOUBLE_IMPACT].Filename.Format("%s%s", PATH_SOUND, "SLAYER_SWORD_DOUBLE_IMPACT.wav");
	(*g_pSoundTable)[SOUND_SLAYER_SWORD_THUNDER_SPARK].Filename.Format("%s%s", PATH_SOUND, "SLAYER_SWORD_THUNDER_SPARK.wav");
	(*g_pSoundTable)[SOUND_SLAYER_SWORD_MENTAL_SWORD].Filename.Format("%s%s", PATH_SOUND, "SLAYER_SWORD_MENTAL_SWORD.wav");


	//-------------------------------------------------------
	// Slayer 도 기술
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_SLAYER_BLADE_SB].Filename.Format("%s%s", PATH_SOUND, "SLAYER_BLADE_SB.wav");
	(*g_pSoundTable)[SOUND_SLAYER_BLADE_TB].Filename.Format("%s%s", PATH_SOUND, "SLAYER_BLADE_TB.wav");
	(*g_pSoundTable)[SOUND_SLAYER_BLADE_SS].Filename.Format("%s%s", PATH_SOUND, "SLAYER_BLADE_SS.wav");
	(*g_pSoundTable)[SOUND_SLAYER_BLADE_TRB].Filename.Format("%s%s", PATH_SOUND, "SLAYER_BLADE_TRB.wav");
	(*g_pSoundTable)[SOUND_SLAYER_BLADE_WS].Filename.Format("%s%s", PATH_SOUND, "SLAYER_BLADE_WS.wav");

	// 2006.09.18 New Sound 
	(*g_pSoundTable)[SOUND_SLAYER_REBUKE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_REBUKE.wav");

	//-------------------------------------------------------
	// Slayer Enchant 기술
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_SLAYER_ENCHANT_B1].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ENCHANT_B1.wav");	// bless시작
	(*g_pSoundTable)[SOUND_SLAYER_ENCHANT_B2].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ENCHANT_B2.wav");	// bless바닥에서
	(*g_pSoundTable)[SOUND_SLAYER_ENCHANT_CHW1].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ENCHANT_CHW1.wav");	// create holy water시작
	(*g_pSoundTable)[SOUND_SLAYER_ENCHANT_CHW2].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ENCHANT_CHW2.wav");	// 완성
	(*g_pSoundTable)[SOUND_SLAYER_ENCHANT_CL].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ENCHANT_CL.wav");	// continual light
	(*g_pSoundTable)[SOUND_SLAYER_ENCHANT_DH].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ENCHANT_DH.wav");	// detect hidden
	(*g_pSoundTable)[SOUND_SLAYER_ENCHANT_L].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ENCHANT_L.wav");		// light
	(*g_pSoundTable)[SOUND_SLAYER_ENCHANT_S1].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ENCHANT_S1.wav");	// striking 시작
	(*g_pSoundTable)[SOUND_SLAYER_ENCHANT_S2].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ENCHANT_S2.wav");	// striking 끝?

	// 2006.09.18 New Sound 
	(*g_pSoundTable)[SOUND_SLAYER_CREATE_HOLY_WATER].Filename.Format("%s%s", PATH_SOUND, "SLAYER_CREATE_HOLY_WATER.wav");	// 홀리 워터
	(*g_pSoundTable)[SOUND_SLAYER_CONTINUAL_LIGHT].Filename.Format("%s%s", PATH_SOUND, "SLAYER_CONTINUAL_LIGHT.wav");	// 컨트뉴얼 라이트 
	(*g_pSoundTable)[SOUND_SLAYER_STRIKING].Filename.Format("%s%s", PATH_SOUND, "SLAYER_STRIKING.wav");	// 컨트뉴얼 라이트 

	//-------------------------------------------------------
	// Slayer Healing 기술
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_SLAYER_HEALING_CCW].Filename.Format("%s%s", PATH_SOUND, "SLAYER_HEALING_CCW.wav");	// cure critical wounds
	(*g_pSoundTable)[SOUND_SLAYER_HEALING_CLW].Filename.Format("%s%s", PATH_SOUND, "SLAYER_HEALING_CLW.wav");	// cure light wounds
	(*g_pSoundTable)[SOUND_SLAYER_HEALING_CP].Filename.Format("%s%s", PATH_SOUND, "SLAYER_HEALING_CP.wav");	// cure poison
	(*g_pSoundTable)[SOUND_SLAYER_HEALING_CPA].Filename.Format("%s%s", PATH_SOUND, "SLAYER_HEALING_CPA.wav");	// cure paralysis
	(*g_pSoundTable)[SOUND_SLAYER_HEALING_PFC].Filename.Format("%s%s", PATH_SOUND, "SLAYER_HEALING_PFC.wav");	// protection from curse
	(*g_pSoundTable)[SOUND_SLAYER_HEALING_PFP].Filename.Format("%s%s", PATH_SOUND, "SLAYER_HEALING_PFP.wav");	// protection from poison
	(*g_pSoundTable)[SOUND_SLAYER_HEALING_PFPA].Filename.Format("%s%s", PATH_SOUND, "SLAYER_HEALING_PFPA.wav");	// protection from paralysis
	(*g_pSoundTable)[SOUND_SLAYER_HEALING_R1].Filename.Format("%s%s", PATH_SOUND, "SLAYER_HEALING_R1.wav");	// restore 시작
	(*g_pSoundTable)[SOUND_SLAYER_HEALING_R2].Filename.Format("%s%s", PATH_SOUND, "SLAYER_HEALING_R2.wav");	// restore 끝
	(*g_pSoundTable)[SOUND_SLAYER_HEALING_RC].Filename.Format("%s%s", PATH_SOUND, "SLAYER_HEALING_RC.wav");	// remove curse
	
	// 2006.09.18 New Sound 
	(*g_pSoundTable)[SOUND_SLAYER_WILD_TYPHOON].Filename.Format("%s%s", PATH_SOUND, "SLAYER_WILD_TYPHOON.wav") ;
	(*g_pSoundTable)[SOUND_SLAYER_CURE_LIGHT_WOUNDS].Filename.Format("%s%s", PATH_SOUND, "SLAYER_CURE_LIGHT_WOUNDS.wav") ;
	(*g_pSoundTable)[SOUND_SLAYER_RESURRECT].Filename.Format("%s%s", PATH_SOUND, "SLAYER_RESURRECT.wav") ;
	(*g_pSoundTable)[SOUND_SLAYER_CAUSE_SERIOUS_WOUNDS].Filename.Format("%s%s", PATH_SOUND, "SLAYER_CAUSE_SERIOUS_WOUNDS.wav") ;
	(*g_pSoundTable)[SOUND_SLAYER_CAUSE_CRITICAL_WOUNDS].Filename.Format("%s%s", PATH_SOUND, "SLAYER_CAUSE_CRITICAL_WOUNDS.wav") ;
	(*g_pSoundTable)[SOUND_SLAYER_ETERNITY].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ETERNITY.wav") ;
	

	(*g_pSoundTable)[SOUND_SLAYER_CURE_CRITICAL_WOUNDS].Filename.Format("%s%s", PATH_SOUND, "SLAYER_CURE_CRITICAL_WOUNDS.wav") ;
	(*g_pSoundTable)[SOUND_SLAYER_HEART_CATALYST].Filename.Format("%s%s", PATH_SOUND, "SLAYER_HEART_CATALYST.wav") ;
	(*g_pSoundTable)[SOUND_SLAYER_PEACE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_PEACE.wav") ;
	(*g_pSoundTable)[SOUND_SLAYER_INSTALL_TRAP].Filename.Format("%s%s", PATH_SOUND, "SLAYER_INSTALL_TRAP.wav") ;
	(*g_pSoundTable)[SOUND_SLAYER_SPIRIT_GUARD].Filename.Format("%s%s", PATH_SOUND, "SLAYER_SPIRIT_GUARD.wav") ;
	(*g_pSoundTable)[SOUND_SLAYER_MERCY_GROUND].Filename.Format("%s%s", PATH_SOUND, "SLAYER_MERCY_GROUND.wav") ;
	(*g_pSoundTable)[SOUND_SLAYER_DRAGON_TORNADO].Filename.Format("%s%s", PATH_SOUND, "SLAYER_DRAGON_TORNADO.wav") ;
	


	//-------------------------------------------------------
	// Vampire 기술
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_VAMPIRE_ACID_ABOLT1].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_ACID_ABOLT1.wav");		// acid bolt날아가기
	(*g_pSoundTable)[SOUND_VAMPIRE_ACID_ABOLT2].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_ACID_ABOLT2.wav");		// acid bolt터질때
	(*g_pSoundTable)[SOUND_VAMPIRE_MISC_BD].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_MISC_BD.wav");			// blood drain
	(*g_pSoundTable)[SOUND_VAMPIRE_MISC_H].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_MISC_H.wav");			// hide
	(*g_pSoundTable)[SOUND_VAMPIRE_POISON_GP].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_POISON_GP.wav");		// green poison
	(*g_pSoundTable)[SOUND_VAMPIRE_POISON_PW].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_POISON_PW.wav");		// purple wall
	(*g_pSoundTable)[SOUND_VAMPIRE_POISON_YP].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_POISON_YP.wav");		// yellow poison
	(*g_pSoundTable)[SOUND_VAMPIRE_ACID_AT].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_ACID_AT.wav");			// acid touch
	(*g_pSoundTable)[SOUND_VAMPIRE_MISC_D].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_MISC_D.wav");			// darkness
	(*g_pSoundTable)[SOUND_VAMPIRE_POISON_PH].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_POISON_PH.wav");		// poisonous hand

	//-------------------------------------------------------
	// 폭주 공격 사운드 
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_BLOODBURST_ATTACK].Filename.Format("%s%s", PATH_SOUND, "BLOODBURSTATTACK.wav");		// poisonous hand	
	//-------------------------------------------------------

	//-------------------------------------------------------
	// 박쥐
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_BAT_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "BAT_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_BAT_DIE].Filename.Format("%s%s", PATH_SOUND, "BAT_DIE.wav");
	(*g_pSoundTable)[SOUND_BAT_WING].Filename.Format("%s%s", PATH_SOUND, "BAT_WING.wav");

	//-------------------------------------------------------
	// ITEM
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_ITEM_MOVE_HEAD].Filename.Format("%s%s", PATH_SOUND, "ITEM_MOVE_HEAD.wav");
	(*g_pSoundTable)[SOUND_ITEM_MOVE_NECKLACE].Filename.Format("%s%s", PATH_SOUND, "ITEM_MOVE_NECKLACE.wav");
	(*g_pSoundTable)[SOUND_ITEM_MOVE_RING].Filename.Format("%s%s", PATH_SOUND, "ITEM_MOVE_RING.wav");

	//-------------------------------------------------------
	// slayer
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_SLAYER_ATTACK_SG].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ATTACK_SG.wav");
	(*g_pSoundTable)[SOUND_SLAYER_ATTACK_SILENCER].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ATTACK_SILENCER.wav");
	(*g_pSoundTable)[SOUND_SLAYER_ATTACK_SR].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ATTACK_TR.wav");
	(*g_pSoundTable)[SOUND_SLAYER_CHARGE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_CHARGE.wav");

	(*g_pSoundTable)[SOUND_SLAYER_ENCHANT_AURABALL1].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ENCHANT_AURABALL1.wav");
	(*g_pSoundTable)[SOUND_SLAYER_ENCHANT_AURABALL2].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ENCHANT_AURABALL2.wav");
	(*g_pSoundTable)[SOUND_SLAYER_ENCHANT_AURARING1].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ENCHANT_AURARING1.wav");
	(*g_pSoundTable)[SOUND_SLAYER_ENCHANT_AURARING2].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ENCHANT_AURARING2.wav");
	(*g_pSoundTable)[SOUND_SLAYER_ENCHANT_AURASHIELD1].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ENCHANT_AURASHIELD1.wav");
	(*g_pSoundTable)[SOUND_SLAYER_ENCHANT_AURASHIELD2].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ENCHANT_AURASHIELD2.wav");
	(*g_pSoundTable)[SOUND_SLAYER_ENCHANT_BLESSGROUND].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ENCHANT_BLESSGROUND.wav");

	(*g_pSoundTable)[SOUND_SLAYER_HEALING_CSW].Filename.Format("%s%s", PATH_SOUND, "SLAYER_HEALING_CSW.wav");
	(*g_pSoundTable)[SOUND_SLAYER_HEALING_REMOVECURSE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_HEALING_REMOVECURSE.wav");

	// 2006.09.18 New Sound 
	(*g_pSoundTable)[SOUND_SLAYER_HOLY_ARROW].Filename.Format("%s%s", PATH_SOUND, "SLAYER_HOLY_ARROW.wav");
	(*g_pSoundTable)[SOUND_SLAYER_CAUSE_LIGHT_WOUNDS].Filename.Format("%s%s", PATH_SOUND, "SLAYER_CAUSE_LIGHT_WOUNDS.wav");
	(*g_pSoundTable)[SOUND_SLAYER_PASSING_HEAL].Filename.Format("%s%s", PATH_SOUND, "SLAYER_PASSING_HEAL.wav");
	(*g_pSoundTable)[SOUND_SLAYER_LIGHT_BALL].Filename.Format("%s%s", PATH_SOUND, "SLAYER_LIGHT_BALL.wav");
	(*g_pSoundTable)[SOUND_SLAYER_AURA_BALL].Filename.Format("%s%s", PATH_SOUND, "SLAYER_AURA_BALL.wav");
	(*g_pSoundTable)[SOUND_SLAYER_VISIBLE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_VISIBLE.wav");

	(*g_pSoundTable)[SOUND_SLAYER_AURA_RING].Filename.Format("%s%s", PATH_SOUND, "SLAYER_AURA_RING.wav");	

	(*g_pSoundTable)[SOUND_SLAYER_HOLY_ARMOR].Filename.Format("%s%s", PATH_SOUND, "SLAYER_HOLY_ARMOR.wav");	
	(*g_pSoundTable)[SOUND_SLAYER_HARPOON_BOMB].Filename.Format("%s%s", PATH_SOUND, "SLAYER_HARPOON_BOMB.wav");	
	(*g_pSoundTable)[SOUND_SLAYER_FLARE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_FLARE.wav");	

	(*g_pSoundTable)[SOUND_SLAYER_FLASH_SLIDING].Filename.Format("%s%s", PATH_SOUND, "SLAYER_FLASH_SLIDING.wav");		
	(*g_pSoundTable)[SOUND_SLAYER_POWER_OF_LAND].Filename.Format("%s%s", PATH_SOUND, "SLAYER_POWER_OF_LAND.wav");			
	(*g_pSoundTable)[SOUND_SLAYER_CREATE_HOLY_POTION].Filename.Format("%s%s", PATH_SOUND, "SLAYER_CREATE_HOLY_POTION.wav");								
		
	(*g_pSoundTable)[SOUND_SLAYER_JABBING_VEIN_NEW].Filename.Format("%s%s", PATH_SOUND, "SLAYER_JABBING_VEIN_NEW.wav");
	(*g_pSoundTable)[SOUND_SLAYER_INSTALL_MINE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_INSTALL_MINE.wav");

	(*g_pSoundTable)[SOUND_SLAYER_ENERGY_DROP].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ENERGY_DROP.wav");
	(*g_pSoundTable)[SOUND_SLAYER_AURA_SHIELD].Filename.Format("%s%s", PATH_SOUND, "SLAYER_AURA_SHIELD.wav");

	(*g_pSoundTable)[SOUND_SLAYER_SHADOW_WALK].Filename.Format("%s%s", PATH_SOUND, "SLAYER_SHADOW_WALK.wav");
	(*g_pSoundTable)[SOUND_SLAYER_SANCTUARY].Filename.Format("%s%s", PATH_SOUND, "SLAYER_SANCTUARY.wav");
	(*g_pSoundTable)[SOUND_SLAYER_BIKE_CRASH].Filename.Format("%s%s", PATH_SOUND, "SLAYER_BIKE_CRASH.wav");

	(*g_pSoundTable)[SOUND_SLAYER_REFLECTION].Filename.Format("%s%s", PATH_SOUND, "SLAYER_REFLECTION.wav");
	(*g_pSoundTable)[SOUND_SLAYER_ROTTEN_APPLE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ROTTEN_APPLE.wav");
		
	
	//-------------------------------------------------------
	// Vampire
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_VAMPIRE_ACIDBALL1].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_ACIDBALL1.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_ACIDBALL2].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_ACIDBALL2.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_ACIDBURN].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_ACIDBURN.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_DOOM].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_DOOM.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_GREENSTALKER1].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_GREENSTALKER1.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_GREENSTALKER2].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_GREENSTALKER2.wav");

	(*g_pSoundTable)[SOUND_VAMPIRE_PARALYSIS].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_PARALYSIS.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_POISON_DB].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_POISON_DB.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_TRANSFORM].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_TRANSFORM.wav");
	
	//-------------------------------------------------------
	// 늑대
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_WOLF_ATTACK].Filename.Format("%s%s", PATH_SOUND, "WOLF_ATTACK.wav");
	(*g_pSoundTable)[SOUND_WOLF_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "WOLF_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_WOLF_DIE].Filename.Format("%s%s", PATH_SOUND, "WOLF_DIE.wav");
	(*g_pSoundTable)[SOUND_WOLF_DRAINED].Filename.Format("%s%s", PATH_SOUND, "WOLF_DRAINED.wav");
	(*g_pSoundTable)[SOUND_WOLF_EAT].Filename.Format("%s%s", PATH_SOUND, "WOLF_EAT.wav");
	(*g_pSoundTable)[SOUND_WOLF_GROWL].Filename.Format("%s%s", PATH_SOUND, "WOLF_GROWL.wav");
	(*g_pSoundTable)[SOUND_WOLF_HOWL].Filename.Format("%s%s", PATH_SOUND, "WOLF_HOWL.wav");

	//-------------------------------------------------------
	// World
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_WORLD_COCK].Filename.Format("%s%s", PATH_SOUND, "WORLD_COCK.wav");
	(*g_pSoundTable)[SOUND_WORLD_CRICKET].Filename.Format("%s%s", PATH_SOUND, "WORLD_CRICKET.wav");
	(*g_pSoundTable)[SOUND_WORLD_FROG].Filename.Format("%s%s", PATH_SOUND, "WORLD_FROG.wav");
	(*g_pSoundTable)[SOUND_WORLD_GRASS].Filename.Format("%s%s", PATH_SOUND, "WORLD_GRASS.wav");
	(*g_pSoundTable)[SOUND_WORLD_OWL].Filename.Format("%s%s", PATH_SOUND, "WORLD_OWL.wav");
	(*g_pSoundTable)[SOUND_WORLD_PROPELLER].Filename.Format("%s%s", PATH_SOUND, "WORLD_PROPELLER.wav");
	(*g_pSoundTable)[SOUND_WORLD_RATS].Filename.Format("%s%s", PATH_SOUND, "WORLD_RATS.wav");
	(*g_pSoundTable)[SOUND_WORLD_RIVER].Filename.Format("%s%s", PATH_SOUND, "WORLD_RIVER.wav");
	(*g_pSoundTable)[SOUND_WORLD_SEWER].Filename.Format("%s%s", PATH_SOUND, "WORLD_SEWER.wav");
	(*g_pSoundTable)[SOUND_WORLD_TREE].Filename.Format("%s%s", PATH_SOUND, "WORLD_TREE.wav");
	(*g_pSoundTable)[SOUND_WORLD_WIND].Filename.Format("%s%s", PATH_SOUND, "WORLD_WIND.wav");
	
	//-------------------------------------------------------
	// 으흠?
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_BLOOD_SWORD].Filename.Format("%s%s", PATH_SOUND, "BLOOD_SWORD.wav");
	

	//-------------------------------------------------------
	// 에스트로이더
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_ES_ATTACK].Filename.Format("%s%s", PATH_SOUND, "ES_ATTACK.wav");
	(*g_pSoundTable)[SOUND_ES_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "ES_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_ES_DIE].Filename.Format("%s%s", PATH_SOUND, "ES_DIE.wav");
	(*g_pSoundTable)[SOUND_ES_DRAIN].Filename.Format("%s%s", PATH_SOUND, "ES_DRAIN.wav");
	(*g_pSoundTable)[SOUND_ES_DRAINED].Filename.Format("%s%s", PATH_SOUND, "ES_DRAINED.wav");

	//-------------------------------------------------------
	// 모데라스
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_MD_ATTACK].Filename.Format("%s%s", PATH_SOUND, "MD_ATTACK.wav");
	(*g_pSoundTable)[SOUND_MD_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "MD_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_MD_DIE].Filename.Format("%s%s", PATH_SOUND, "MD_DIE.wav");
	(*g_pSoundTable)[SOUND_MD_DRAIN].Filename.Format("%s%s", PATH_SOUND, "MD_DRAIN.wav");
	(*g_pSoundTable)[SOUND_MD_DRAINED].Filename.Format("%s%s", PATH_SOUND, "MD_DRAINED.wav");

	//-------------------------------------------------------
	// 뮤턴트
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_MT_ATTACK].Filename.Format("%s%s", PATH_SOUND, "MT_ATTACK.wav");
	(*g_pSoundTable)[SOUND_MT_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "MT_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_MT_DIE].Filename.Format("%s%s", PATH_SOUND, "MT_DIE.wav");
	(*g_pSoundTable)[SOUND_MT_DRAIN].Filename.Format("%s%s", PATH_SOUND, "MT_DRAIN.wav");
	(*g_pSoundTable)[SOUND_MT_DRAINED].Filename.Format("%s%s", PATH_SOUND, "MT_DRAINED.wav");

	//-------------------------------------------------------
	// 위도우즈
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_WD_ATTACK].Filename.Format("%s%s", PATH_SOUND, "WD_ATTACK.wav");
	(*g_pSoundTable)[SOUND_WD_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "WD_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_WD_DIE].Filename.Format("%s%s", PATH_SOUND, "WD_DIE.wav");
	(*g_pSoundTable)[SOUND_WD_DRAIN].Filename.Format("%s%s", PATH_SOUND, "WD_DRAIN.wav");
	(*g_pSoundTable)[SOUND_WD_DRAINED].Filename.Format("%s%s", PATH_SOUND, "WD_DRAINED.wav");

	//-------------------------------------------------------
	// 이벤트
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_EVENT_FANFARE].Filename.Format("%s%s", PATH_SOUND, "EVENT_FANFARE.wav");

	//-------------------------------------------------------
	// 빅팽
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_BF_ATTACK].Filename.Format("%s%s", PATH_SOUND, "BF_ATTACK.wav");
	(*g_pSoundTable)[SOUND_BF_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "BF_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_BF_DIE].Filename.Format("%s%s", PATH_SOUND, "BF_DIE.wav");
	(*g_pSoundTable)[SOUND_BF_DRAIN].Filename.Format("%s%s", PATH_SOUND, "BF_DRAIN.wav");
	(*g_pSoundTable)[SOUND_BF_DRAINED].Filename.Format("%s%s", PATH_SOUND, "BF_DRAINED.wav");

	//-------------------------------------------------------
	// 반델라이저
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_VD_ATTACK].Filename.Format("%s%s", PATH_SOUND, "VD_ATTACK.wav");
	(*g_pSoundTable)[SOUND_VD_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "VD_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_VD_DIE].Filename.Format("%s%s", PATH_SOUND, "VD_DIE.wav");
	(*g_pSoundTable)[SOUND_VD_DRAIN].Filename.Format("%s%s", PATH_SOUND, "VD_DRAIN.wav");
	(*g_pSoundTable)[SOUND_VD_DRAINED].Filename.Format("%s%s", PATH_SOUND, "VD_DRAINED.wav");

	//-------------------------------------------------------
	// 슬레이어 기술
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_SLAYER_BLADE_TS].Filename.Format("%s%s", PATH_SOUND, "SLAYER_BLADE_TS.wav");
	(*g_pSoundTable)[SOUND_SLAYER_ENCHANT_DETECTINVISIBILITY].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ENCHANT_DETECTINVISIBILITY.wav");
	(*g_pSoundTable)[SOUND_SLAYER_ENCHANT_IDENTIFY].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ENCHANT_IDENTIFY.wav");
	(*g_pSoundTable)[SOUND_SLAYER_ENCHANT_PFA].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ENCHANT_PFA.wav");
	(*g_pSoundTable)[SOUND_SLAYER_HEAL_SACRIFICE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_HEAL_SACRIFICE.wav");
	(*g_pSoundTable)[SOUND_SLAYER_SWORD_LH].Filename.Format("%s%s", PATH_SOUND, "SLAYER_SWORD_LH.wav");
	(*g_pSoundTable)[SOUND_SLAYER_SWORD_SC].Filename.Format("%s%s", PATH_SOUND, "SLAYER_SWORD_SC.wav");
	(*g_pSoundTable)[SOUND_SLAYER_SWORD_SW].Filename.Format("%s%s", PATH_SOUND, "SLAYER_SWORD_SW.wav");

	// 2006.09.18 New Sound 
	(*g_pSoundTable)[SOUND_SLAYER_SWORD_LIGHTNING_HAND].Filename.Format("%s%s", PATH_SOUND, "SLAYER_SWORD_LIGHTNING_HAND.wav");
	(*g_pSoundTable)[SOUND_SLAYER_SWORD_LARSLASH].Filename.Format("%s%s", PATH_SOUND, "SLAYER_SWORD_LARSLASH.wav");

	//-------------------------------------------------------
	// 뱀파이어 기술
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_VAMPIRE_ACIDSWAMP].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_ACIDSWAMP.wav");

	//-------------------------------------------------------
	// 카오스 나이트
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_CK_ATTACK].Filename.Format("%s%s", PATH_SOUND, "CK_ATTACK.wav");
	(*g_pSoundTable)[SOUND_CK_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "CK_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_CK_DIE].Filename.Format("%s%s", PATH_SOUND, "CK_DIE.wav");
	(*g_pSoundTable)[SOUND_CK_DRAIN].Filename.Format("%s%s", PATH_SOUND, "CK_DRAIN.wav");
	(*g_pSoundTable)[SOUND_CK_DRAINED].Filename.Format("%s%s", PATH_SOUND, "CK_DRAINED.wav");
	(*g_pSoundTable)[SOUND_CK_MAGIC].Filename.Format("%s%s", PATH_SOUND, "CK_MAGIC.wav");

	//-------------------------------------------------------
	// 크림슨 슬로터
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_CS_ATTACK].Filename.Format("%s%s", PATH_SOUND, "CS_ATTACK.wav");
	(*g_pSoundTable)[SOUND_CS_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "CS_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_CS_DIE].Filename.Format("%s%s", PATH_SOUND, "CS_DIE.wav");
	(*g_pSoundTable)[SOUND_CS_DRAIN].Filename.Format("%s%s", PATH_SOUND, "CS_DRAIN.wav");
	(*g_pSoundTable)[SOUND_CS_DRAINED].Filename.Format("%s%s", PATH_SOUND, "CS_DRAINED.wav");

	//-------------------------------------------------------
	// 다크스크리머
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_DSC_ATTACK].Filename.Format("%s%s", PATH_SOUND, "DSC_ATTACK.wav");
	(*g_pSoundTable)[SOUND_DSC_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "DSC_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_DSC_DIE].Filename.Format("%s%s", PATH_SOUND, "DSC_DIE.wav");
	(*g_pSoundTable)[SOUND_DSC_DRAIN].Filename.Format("%s%s", PATH_SOUND, "DSC_DRAIN.wav");
	(*g_pSoundTable)[SOUND_DSC_DRAINED].Filename.Format("%s%s", PATH_SOUND, "DSC_DRAINED.wav");
	(*g_pSoundTable)[SOUND_DSC_MAGIC].Filename.Format("%s%s", PATH_SOUND, "DSC_MAGIC.wav");

	//-------------------------------------------------------
	// 아이언티쓰
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_IT_ATTACK].Filename.Format("%s%s", PATH_SOUND, "IT_ATTACK.wav");
	(*g_pSoundTable)[SOUND_IT_DAMAGE].Filename.Format("%s%s", PATH_SOUND, "IT_DAMAGE.wav");
	(*g_pSoundTable)[SOUND_IT_DIE].Filename.Format("%s%s", PATH_SOUND, "IT_DIE.wav");
	(*g_pSoundTable)[SOUND_IT_DRAIN].Filename.Format("%s%s", PATH_SOUND, "IT_DRAIN.wav");
	(*g_pSoundTable)[SOUND_IT_DRAINED].Filename.Format("%s%s", PATH_SOUND, "IT_DRAINED.wav");

	//-------------------------------------------------------
	// item
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_ITEM_MOVE_JEWEL].Filename.Format("%s%s", PATH_SOUND, "ITEM_MOVE_JEWEL.wav");

	//-------------------------------------------------------
	// world
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_WORLD_MAP].Filename.Format("%s%s", PATH_SOUND, "WORLD_MAP.wav");
	(*g_pSoundTable)[SOUND_WORLD_WALKIETALKIE].Filename.Format("%s%s", PATH_SOUND, "WORLD_WALKIETALKIE.wav");

	//-------------------------------------------------------
	// 2001.12.17 추가
	//-------------------------------------------------------
	//-------------------------------------------------------
	// 폭탄 소리
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_ITEM_BOOM1].Filename.Format("%s%s", PATH_SOUND, "ITEM_BOOM1.wav");
	(*g_pSoundTable)[SOUND_ITEM_BOOM2].Filename.Format("%s%s", PATH_SOUND, "ITEM_BOOM2.wav");
	(*g_pSoundTable)[SOUND_ITEM_BOOM3].Filename.Format("%s%s", PATH_SOUND, "ITEM_BOOM3.wav");
	(*g_pSoundTable)[SOUND_ITEM_BOOM4].Filename.Format("%s%s", PATH_SOUND, "ITEM_BOOM4.wav");

	//-------------------------------------------------------
	// 슬레이어 기술
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_SLAYER_BLADE_BERSERKER].Filename.Format("%s%s", PATH_SOUND, "SLAYER_BLADE_BERSERKER.wav");
	(*g_pSoundTable)[SOUND_SLAYER_BLADE_EARTHQUAKE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_BLADE_EARTHQUAKE.wav");
	(*g_pSoundTable)[SOUND_SLAYER_ENCHANT_ENCHANT].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ENCHANT_ENCHANT.wav");
	(*g_pSoundTable)[SOUND_SLAYER_ENCHANT_VISIBLEA].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ENCHANT_VISIBLEA.wav");
	(*g_pSoundTable)[SOUND_SLAYER_ENCHANT_VISIBLEB].Filename.Format("%s%s", PATH_SOUND, "SLAYER_ENCHANT_VISIBLEB.wav");
	(*g_pSoundTable)[SOUND_SLAYER_HEAL_ACTIVATION].Filename.Format("%s%s", PATH_SOUND, "SLAYER_HEAL_ACTIVATION.wav");
	(*g_pSoundTable)[SOUND_SLAYER_HEAL_CUREALL].Filename.Format("%s%s", PATH_SOUND, "SLAYER_HEAL_CUREALL.wav");
	(*g_pSoundTable)[SOUND_SLAYER_SWORD_EXPANSION].Filename.Format("%s%s", PATH_SOUND, "SLAYER_SWORD_EXPANSION.wav");
	(*g_pSoundTable)[SOUND_SLAYER_SWORD_THUNDERBOLTA].Filename.Format("%s%s", PATH_SOUND, "SLAYER_SWORD_THUNDERBOLTA.wav");
	(*g_pSoundTable)[SOUND_SLAYER_SWORD_THUNDERBOLTB].Filename.Format("%s%s", PATH_SOUND, "SLAYER_SWORD_THUNDERBOLTB.wav");
	(*g_pSoundTable)[SOUND_SLAYER_SWORD_WINDDIVIDER].Filename.Format("%s%s", PATH_SOUND, "SLAYER_SWORD_WINDDIVIDER.wav");

	(*g_pSoundTable)[SOUND_SLAYER_BLOODBURST_ATTATCK_MAIL].Filename.Format("%s%s", PATH_SOUND, "SLAYER_BLOODBURST_ATTACK_COMMON.wav");
	(*g_pSoundTable)[SOUND_SLAYER_BLOODBURST_ATTATCK_FEMALE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_BLOODBURST_ATTACK_COMMON.wav");
	(*g_pSoundTable)[SOUND_SLAYER_BLOODBURST_DEFENSE_MAIL].Filename.Format("%s%s", PATH_SOUND, "SLAYER_BLOODBURST_DEFENSE_COMMON.wav");

	// 2006.09.18 New Sound 
	(*g_pSoundTable)[SOUND_SLAYER_EARTHQUAKE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_EARTHQUAKE.wav") ;	
	(*g_pSoundTable)[SOUND_SLAYER_GUN_SHOT_GUIDANCE].Filename.Format("%s%s", PATH_SOUND, "SLAYER_GUN_SHOT_GUIDANCE.wav") ;

	//-------------------------------------------------------
	// 뱀파이어 기술
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_VAMPIRE_BLOODYBALL].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_BLOODYBALL.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_BLOODYKNIFE].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_BLOODYKNIFE.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_BLOODYWALL].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_BLOODYWALL.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_DEATH].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_DEATH.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_HALLUCINATION].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_HALLUCINATION.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_SEDUCTION].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_SEDUCTION.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_SUMMONCASKET].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_SUMMONCASKET.wav");


	(*g_pSoundTable)[SOUND_VAMPIRE_BLOODBURST_ATTATCK_MAIL].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_BLOODBURST_ATTACK_COMMON.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_BLOODBURST_ATTATCK_FEMALE].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_BLOODBURST_ATTACK_COMMON.wav");

	(*g_pSoundTable)[SOUND_VAMPIRE_BLOODBURST_DEFENSE_MAIL].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_BLOODBURST_DEFENSE_MALE.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_BLOODBURST_DEFENSE_FEMALE].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_BLOODBURST_DEFENSE_FEMALE.wav");

	(*g_pSoundTable)[SOUND_VAMPIRE_ABERRATION].Filename.Format("%s%s", PATH_SOUND, "VAMPIRE_ABERRATION.wav");


	//-------------------------------------------------------
	// 크리스마스 이벤트 사운드
	//-------------------------------------------------------
	(*g_pSoundTable)[SOUND_XMAS_GIFTBOX].Filename.Format("%s%s", PATH_SOUND, "XMAS_GIFTBOX.wav");
	(*g_pSoundTable)[SOUND_XMAS_STAR].Filename.Format("%s%s", PATH_SOUND, "XMAS_STAR.wav");
	
	//----------------------------------------------------------
	// 신종 몬스터 3종 딤가고일,볼바메두사,애쉬발록 - 2003.4.23
	//----------------------------------------------------------
	(*g_pSoundTable)[SOUND_VOL_MAGIC].Filename.Format("%s%s",PATH_SOUND, "VOL_MAGIC.WAV");
	(*g_pSoundTable)[SOUND_VOL_DIE].Filename.Format("%s%s",PATH_SOUND, "VOL_DIE.WAV");
	(*g_pSoundTable)[SOUND_VOL_DAMAGE].Filename.Format("%s%s",PATH_SOUND, "VOL_DAMAGE.WAV");
	(*g_pSoundTable)[SOUND_VOL_ATTACK].Filename.Format("%s%s",PATH_SOUND, "VOL_ATTACK.WAV");

	(*g_pSoundTable)[SOUND_ASH_DIE].Filename.Format("%s%s",PATH_SOUND, "ASH_DIE.WAV");
	(*g_pSoundTable)[SOUND_ASH_DAMAGE].Filename.Format("%s%s",PATH_SOUND, "ASH_DAMAGE.WAV");
	(*g_pSoundTable)[SOUND_ASH_ATTACK].Filename.Format("%s%s",PATH_SOUND, "aSH_ATTACK.WAV");
	
	(*g_pSoundTable)[SOUND_DIM_DIE].Filename.Format("%s%s",PATH_SOUND, "DIM_DIE.WAV");
	(*g_pSoundTable)[SOUND_DIM_DAMAGE].Filename.Format("%s%s",PATH_SOUND, "DIM_DAMAGE.WAV");
	(*g_pSoundTable)[SOUND_DIM_ATTACK].Filename.Format("%s%s",PATH_SOUND, "DIM_ATTACK.WAV");
	(*g_pSoundTable)[SOUND_DIM_MAGIC].Filename.Format("%s%s",PATH_SOUND, "DIM_MAGIC.WAV");
	
	(*g_pSoundTable)[SOUND_DRAGON_FIRE_CRACKER].Filename.Format("%s%s",PATH_SOUND, "DRAGON_FIRECRACKER.WAV");
	(*g_pSoundTable)[SOUND_AMPUTATE].Filename.Format("%s%s",PATH_SOUND, "SLAYER_SWORD_AMPUTATE.WAV");
	(*g_pSoundTable)[SOUND_CONCEALMENT].Filename.Format("%s%s",PATH_SOUND, "SLAYER_GUN_CONCEALMENT.WAV");
	(*g_pSoundTable)[SOUND_DENIAL_MAGIC_DAMAGED].Filename.Format("%s%s",PATH_SOUND, "SLAYER_HEAL_DENIAL_1.WAV");
	(*g_pSoundTable)[SOUND_DENIAL_MAGIC_START].Filename.Format("%s%s",PATH_SOUND, "SLAYER_HEAL_DENIAL_2.WAV");
	(*g_pSoundTable)[SOUND_REQUITAL].Filename.Format("%s%s",PATH_SOUND, "SLAYER_ENCHANT_REQUITAL.WAV");

	(*g_pSoundTable)[SOUND_OUSTERS_ARMSBAND].Filename.Format("%s%s",PATH_SOUND,"OUSTERS_ARMSBAND.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_BOOTS].Filename.Format("%s%s",PATH_SOUND,"OUSTERS_BOOTS.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_CHAKRAM].Filename.Format("%s%s",PATH_SOUND,"OUSTERS_CHAKRAM.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_CIRCLET].Filename.Format("%s%s",PATH_SOUND,"OUSTERS_CIRCLET.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_COAT].Filename.Format("%s%s",PATH_SOUND,"OUSTERS_COAT.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_ELEMENTAL_STONE].Filename.Format("%s%s",PATH_SOUND,"OUSTERS_ELEMENTAL_STONE.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_INTERFACE].Filename.Format("%s%s",PATH_SOUND,"OUSTERS_INTERFACE.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_PENDANT].Filename.Format("%s%s",PATH_SOUND,"OUSTERS_PENDANT.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_RING].Filename.Format("%s%s",PATH_SOUND,"OUSTERS_RING.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_SKILL_INFO].Filename.Format("%s%s",PATH_SOUND,"OUSTERS_SKILLINF.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_WRISTLET].Filename.Format("%s%s",PATH_SOUND,"OUSTERS_WRISTLET.WAV");

	(*g_pSoundTable)[SOUND_OUSTERS_ATTACK_1].Filename.Format("%s%s",PATH_SOUND,"OUSTERS_ATTACK_1.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_ATTACK_2].Filename.Format("%s%s",PATH_SOUND,"OUSTERS_ATTACK_2.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_MAGIC_1].Filename.Format("%s%s",PATH_SOUND,"OUSTERS_MAGIC_1.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_MAGIC_2].Filename.Format("%s%s",PATH_SOUND,"OUSTERS_MAGIC_2.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_DAMAGED].Filename.Format("%s%s",PATH_SOUND,"OUSTERS_DAMAGED.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_FAST_MOVE_1].Filename.Format("%s%s",PATH_SOUND,"OUSTERS_FAST_MOVE_1.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_FAST_MOVE_2].Filename.Format("%s%s",PATH_SOUND,"OUSTERS_FAST_MOVE_2.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_DIE].Filename.Format("%s%s",PATH_SOUND,"OUSTERS_DIE.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_ABSORB_SOUL].Filename.Format("%s%s",PATH_SOUND,"OUSTERS_ABSORB_SOUL.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_DRAIN].Filename.Format("%s%s",PATH_SOUND,"OUSTERS_DRAIN.WAV");


	//------------------------------------------------------------
	// 아우스터즈 스킬
	//------------------------------------------------------------
	(*g_pSoundTable)[SOUND_OUSTERS_PROMINENCE].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_PROMINENCE.WAV");
	
	(*g_pSoundTable)[SOUND_OUSTERS_BACK_STAB].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_BACK_STAB.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_BLAZE_BOLT].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_BLAZE_BOLT.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_BLUNTING].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_BLUNTING.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_CROSS_GUARD].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_CROSS_GUARD.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_EVADE].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_EVADE.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_FLOURISH].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_FLOURISH.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_GAMMA_CHOP].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_GAMMA_CHOP.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_LIBERTY].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_LIBERTY.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_SHARP_ROUND].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_SHARP_ROUND.WAV");

	(*g_pSoundTable)[SOUND_OUSTERS_BLOCK_HEAD].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_BLOCK_HEAD.WAV");				// STATUS
	(*g_pSoundTable)[SOUND_OUSTERS_GNOME_WHISPER].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_GNOME_WHISPER.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_EARTH_TEETH].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_EARTH_TEETH.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_SAND_OF_SOUL_STONE].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_SAND_OF_SOUL_STONE.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_ICE_OF_SOUL_STONE].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_ICE_OF_SOUL_STONE.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_FIRE_OF_SOUL_STONE].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_FIRE_OF_SOUL_STONE.WAV");	// STATUS
	(*g_pSoundTable)[SOUND_OUSTERS_REFUSAL_ETHER].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_REFUSAL_ETHER.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_TENDRIL].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_TENDRIL.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_HANDS_OF_FIRE].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_HANDS_OF_FIRE.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_ICE_FIELD].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_ICE_FIELD.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_RING_OF_FLARE].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_RING_OF_FLARE.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_PROMINENCE_2].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_PROMINENCE_2.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_HANDS_OF_NIZIE].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_HANDS_OF_NIZIE.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_STONE_AUGER].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_STONE_AUGER.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_NYMPH_RECOVERY].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_NYMPH_RECORVERY.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_WATER_BARRIER].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_WATER_BARRIER.WAV");

	(*g_pSoundTable)[SOUND_OUSTERS_BLOODBURST_ATTACK].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_BLOODBURST_ATTACK_COMMON.wav");
	(*g_pSoundTable)[SOUND_OUSTERS_BLOODBURST_DEFENSE].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_BLOODBURST_DEFENSE_COMMON.wav");

	// 2006.09.21 by chyaya
	(*g_pSoundTable)[SOUND_OUSTERS_BACK_STAB_NEW].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_BACK_STAB_NEW.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_SHARP_CHAKRAM].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_SHARP_CHAKRAM.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_BLESS_FIRE].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_BLESS_FIRE.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_CHARGING_ATTACK].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_CHARGING_ATTACK.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_DISTANCE_BLITZ].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_DISTANCE_BLITZ.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_KASA_S_ARROW].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_KASA_S_ARROW.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_FIRE_PIERCING].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_FIRE_PIERCING.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_FIERCE_FLAME].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_FIERCE_FLAME.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_EMISSION_WATER].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_EMISSION_WATER.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_SUMMON_OF_WATER_ELEMENTAL].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_SUMMON_OF_WATER_ELEMENTAL.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_EXPLOSION_WATER].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_EXPLOSION_WATER.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_SHADOW_OF_STORM].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_SHADOW_OF_STORM.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_BEAT_HEAD].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_BEAT_HEAD.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_SUMMON_OF_GROUND_ELEMENTAL].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_SUMMON_OF_GROUND_ELEMENTAL.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_METEOR_STORM].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_METEOR_STORM.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_DESTINIES].Filename.Format("%s%s",PATH_SOUND, "OUSTERS_DESTINIES.WAV");
	

	(*g_pSoundTable)[SOUND_OUSTERS_PUPA].Filename.Format("%s%s",PATH_SOUND, "ITEM_USE_HPOTION1.WAV");
	(*g_pSoundTable)[SOUND_OUSTERS_MEI].Filename.Format("%s%s",PATH_SOUND, "ITEM_USE_MPOTION1.WAV");

	
	//---------------------------------------------------------------------------------------------------
	// 110 레벨 스킬 사운드
	//---------------------------------------------------------------------------------------------------
	(*g_pSoundTable)[SOUND_SLAYER_BLITZ_SLIDING].Filename.Format("%s%s",PATH_SOUND, "SLAYER_BLITZ_SLIDING.WAV");
	(*g_pSoundTable)[SOUND_SLAYER_BLAZE_WALK].Filename.Format("%s%s",PATH_SOUND, "SLAYER_BLAZE_WALK.WAV");
	(*g_pSoundTable)[SOUND_SLAYER_JABBING_VEIN].Filename.Format("%s%s",PATH_SOUND, "SLAYER_JABBING_VEIN.WAV");
	(*g_pSoundTable)[SOUND_SLAYER_GREAT_HEAL].Filename.Format("%s%s",PATH_SOUND, "SLAYER_GREAT_HEAL.WAV");
	(*g_pSoundTable)[SOUND_SLAYER_DIVINE_GUIDANCE].Filename.Format("%s%s",PATH_SOUND, "SLAYER_DIVINE_GUIDANCE.WAV");
	(*g_pSoundTable)[SOUND_VAMPIRE_BLOODY_ZENITH].Filename.Format("%s%s",PATH_SOUND, "VAMPIRE_BLOODY_ZENITH.WAV");
	
	(*g_pSoundTable)[SOUND_REGEN_TOWER_REPEAT].Filename.Format("%s%s",PATH_SOUND, "RegenTowerRepeat.wav");
	(*g_pSoundTable)[SOUND_REGEN_TOWER_START].Filename.Format("%s%s",PATH_SOUND, "RegenTowerStart.wav");
	(*g_pSoundTable)[SOUND_REGEN_TOWER_FLASH].Filename.Format("%s%s",PATH_SOUND, "RegenTowerFlash.wav");
	(*g_pSoundTable)[SOUND_REGEN_TOWER_OWNER_CHANGED].Filename.Format("%s%s",PATH_SOUND, "RegenTowerOwnerChanged.wav");
	(*g_pSoundTable)[SOUND_SWEEPER_START].Filename.Format("%s%s",PATH_SOUND, "SweeperStart.wav");
	(*g_pSoundTable)[SOUND_SWEEPER_REPEAT].Filename.Format("%s%s",PATH_SOUND, "SweeperRepeat.wav");
	(*g_pSoundTable)[SOUND_SWEEPER_END].Filename.Format("%s%s",PATH_SOUND, "SweeperEnd.wav");

	//---------------------------------------------------------------------------------------------------
	// 아우 스킬 사운드
	//---------------------------------------------------------------------------------------------------
	(*g_pSoundTable)[SOUND_DESTRUCTION_SPEAR].Filename.Format("%s%s",PATH_SOUND, "Destruction_Spear.wav");
	(*g_pSoundTable)[SOUND_DUCKING_WALLOP].Filename.Format("%s%s",PATH_SOUND, "Ducking_Wallop.wav");
	(*g_pSoundTable)[SOUND_FATAL_SNICK].Filename.Format("%s%s",PATH_SOUND, "Fatal_Snick.wav");
	(*g_pSoundTable)[SOUND_FROZEN_ARMOR].Filename.Format("%s%s",PATH_SOUND, "Frozen_Armor.wav");
	(*g_pSoundTable)[SOUND_GROUND_BLESS].Filename.Format("%s%s",PATH_SOUND, "Ground_Bless.wav");
	(*g_pSoundTable)[SOUND_HELLFIRE].Filename.Format("%s%s",PATH_SOUND, "Hellfire.wav");
	(*g_pSoundTable)[SOUND_ICE_LANCE].Filename.Format("%s%s",PATH_SOUND, "Ice_Lance.wav");
	(*g_pSoundTable)[SOUND_MAGNUM_SPEAR_1].Filename.Format("%s%s",PATH_SOUND, "Magnum_Spear_1.wav");
	(*g_pSoundTable)[SOUND_MAGNUM_SPEAR_2].Filename.Format("%s%s",PATH_SOUND, "Magnum_Spear_2.wav");
	(*g_pSoundTable)[SOUND_MAGNUM_SPEAR_3].Filename.Format("%s%s",PATH_SOUND, "Magnum_Spear_3.wav");
	(*g_pSoundTable)[SOUND_REACTIVE_ARMOR].Filename.Format("%s%s",PATH_SOUND, "Reactive_Armor.wav");
	(*g_pSoundTable)[SOUND_SAND_CROSS].Filename.Format("%s%s",PATH_SOUND, "Sand_Cross.wav");
	(*g_pSoundTable)[SOUND_SHIFT_BREAK].Filename.Format("%s%s",PATH_SOUND, "Shift_Break.wav");
	(*g_pSoundTable)[SOUND_SOUL_REBIRTH].Filename.Format("%s%s",PATH_SOUND, "Soul_Rebirth.wav");
	(*g_pSoundTable)[SOUND_TELEPORT].Filename.Format("%s%s",PATH_SOUND, "Teleport.wav");

	
	//---------------------------------------------------------------------------------------------------
	// 질드레 레어 관련 이펙트 사운드 - 2004, 7, 7 sobeit add start
	//---------------------------------------------------------------------------------------------------
	(*g_pSoundTable)[SOUND_BLIND_SUMMON].Filename.Format("%s%s",PATH_SOUND, "Blind_summon.wav");	// 질드레 얼음 석상 소환 시
	(*g_pSoundTable)[SOUND_BLIND_DESTORY].Filename.Format("%s%s",PATH_SOUND, "Blind_destroy.wav");	// 질드레 얼음 석상 파괴 시

	(*g_pSoundTable)[SOUND_PIPE_ROUTING].Filename.Format("%s%s",PATH_SOUND, "Pipe_routing.wav");	// 맹인의 피리 루팅 시
	(*g_pSoundTable)[SOUND_PIPE_DROP].Filename.Format("%s%s",PATH_SOUND, "Pipe_drop.wav");			// 맹인의 피리 드롭 시

	(*g_pSoundTable)[SOUND_BLINDNESS].Filename.Format("%s%s",PATH_SOUND, "Blindness.wav");			// 블라인드니스 스킬 걸릴 시

	(*g_pSoundTable)[SOUND_TRAP_A].Filename.Format("%s%s",PATH_SOUND, "Trap_A.wav");				// TRAP_ICICLE_AUGER 시전 시
	(*g_pSoundTable)[SOUND_TRAP_B].Filename.Format("%s%s",PATH_SOUND, "Trap_B.wav");				// TRAP_ICICLE_LARGE_AUGER 시전 시
	(*g_pSoundTable)[SOUND_DROP_A].Filename.Format("%s%s",PATH_SOUND, "Drop_A.wav");				// ICICLE_DROP 시전 시
	(*g_pSoundTable)[SOUND_SIDE_SUMMON].Filename.Format("%s%s",PATH_SOUND, "Side_summon.wav");		// ICE_STICK 시전 시
	(*g_pSoundTable)[SOUND_SIDE_DESTORY].Filename.Format("%s%s",PATH_SOUND, "Side_summon_destroy.wav");	// ICE_STICK 종료 시
	(*g_pSoundTable)[SOUND_GLACIER_START].Filename.Format("%s%s",PATH_SOUND, "Glacier_start.wav");	// 글래셔 시전 시 - 질드레 스킬
	(*g_pSoundTable)[SOUND_GLACIER_END].Filename.Format("%s%s",PATH_SOUND, "Glacier_end.wav");		// 글래셔 종료 시 - 질드레 스킬

	(*g_pSoundTable)[SOUND_ICEAUGER].Filename.Format("%s%s",PATH_SOUND, "Iceauger.wav");			// 아이스 오거 시전 시 - 질드레 스킬
	
	(*g_pSoundTable)[SOUND_ICEHAIL].Filename.Format("%s%s",PATH_SOUND, "Icehail.wav");				// 아이스 헤일 시전 시 - 질드레 스킬
	(*g_pSoundTable)[SOUND_ICEWAVE].Filename.Format("%s%s",PATH_SOUND, "Icewave.wav");				// 아이스 웨이브 시전 시 - 질드레 스킬

	(*g_pSoundTable)[SOUND_GDR_GHOST1].Filename.Format("%s%s",PATH_SOUND, "ghost_1.wav");				// 질드레 레어 유령
	(*g_pSoundTable)[SOUND_GDR_GHOST2].Filename.Format("%s%s",PATH_SOUND, "ghost_2.wav");				// 질드레 레어 유령
	(*g_pSoundTable)[SOUND_GDR_GHOST3].Filename.Format("%s%s",PATH_SOUND, "ghost_3.wav");				// 질드레 레어 유령
	(*g_pSoundTable)[SOUND_GDR_GHOST4].Filename.Format("%s%s",PATH_SOUND, "ghost_4.wav");				// 질드레 레어 유령

	// 2004, 10, 6, sobeit add start - 130 스킬 사운드
	(*g_pSoundTable)[SOUND_SLAYER_TURRET_FIRE].Filename.Format("%s%s",PATH_SOUND, "Slayer_TurretFire.wav");
	(*g_pSoundTable)[SOUND_SLAYER_TURRET_FIRE_START].Filename.Format("%s%s",PATH_SOUND, "Slayer_TurretFire_Ready.wav");
	(*g_pSoundTable)[SOUND_SLAYER_TURRET_FIRE_END].Filename.Format("%s%s",PATH_SOUND, "Slayer_TurretFire_End.wav");
	(*g_pSoundTable)[SOUND_SLAYER_SWORDOFTHOR].Filename.Format("%s%s",PATH_SOUND, "Slayer_SwordOfThor.wav");
	(*g_pSoundTable)[SOUND_SLAYER_WITHSUNTIDE].Filename.Format("%s%s",PATH_SOUND, "Slayer_WithSunTide.wav");
	(*g_pSoundTable)[SOUND_SLAYER_SWEEPVICE_HIT].Filename.Format("%s%s",PATH_SOUND, "Slayer_SweepViceHit.wav");
	(*g_pSoundTable)[SOUND_SLAYER_SWEEPVICE_RESIZE].Filename.Format("%s%s",PATH_SOUND, "Slayer_SweepViceReSize.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_SUMMONGOREGRAND].Filename.Format("%s%s",PATH_SOUND, "Vampire_SummonGoreGrand.wav");
	// 2004, 10, 6, sobeit add end - 130 스킬 사운드
	
	// 2004, 11, 8, sobeit add start - 그레이트 러피언 도끼
	(*g_pSoundTable)[SOUND_GREAT_RUFFIAN_AXE].Filename.Format("%s%s",PATH_SOUND, "GreateRuffian_Axe.wav");
	// 2004, 11, 8, sobeit add end
	
	// 2004, 12, 15, sobeit add start - 140 skill sound
	(*g_pSoundTable)[SOUND_SLAYER_PLASMA_ROCKET_LAUNCHER].Filename.Format("%s%s",PATH_SOUND, "PlasmaRocketLauncher.wav");
	(*g_pSoundTable)[SOUND_SLAYER_BOMBING_STAR].Filename.Format("%s%s",PATH_SOUND, "BombingStar.wav");
	(*g_pSoundTable)[SOUND_SLAYER_INTIMATE_GRAIL].Filename.Format("%s%s",PATH_SOUND, "IntimateGrail.wav");
	(*g_pSoundTable)[SOUND_OUSTERS_FURY_OF_GNOME].Filename.Format("%s%s",PATH_SOUND, "FuryOfGnome.wav");
	(*g_pSoundTable)[SOUND_OUSTERS_SUMMON_MIGA].Filename.Format("%s%s",PATH_SOUND, "SummonMiga.wav");
	// 2004, 12, 15, sobeit add end

	// 2005, 1, 11, sobeit add start - 새로운 몬스터들
	//---------------------------------------------
	// 플리거 - 자폭병
	//---------------------------------------------
	(*g_pSoundTable)[SOUND_FLIEGER_BOMB].Filename.Format("%s%s",PATH_SOUND, "Flieger_Bomb.wav");
	//---------------------------------------------
	// 기프레이터 - 박격포
	//---------------------------------------------
	(*g_pSoundTable)[SOUND_GEFREITER_ATTACK].Filename.Format("%s%s",PATH_SOUND, "Gefreiter_Attack.wav");
	(*g_pSoundTable)[SOUND_GEFREITER_DAMAGE].Filename.Format("%s%s",PATH_SOUND, "Gefreiter_Damage.wav");
	(*g_pSoundTable)[SOUND_GEFREITER_DEAD].Filename.Format("%s%s",PATH_SOUND, "Gefreiter_Dead.wav");
	(*g_pSoundTable)[SOUND_GEFREITER_DRAINED].Filename.Format("%s%s",PATH_SOUND, "Gefreiter_Drained.wav");
	//---------------------------------------------
	// 하우트만 - 장교
	//---------------------------------------------
	(*g_pSoundTable)[SOUND_HAUPTMANN_DAMAGE].Filename.Format("%s%s",PATH_SOUND, "Hauptmann_Damage.wav");
	(*g_pSoundTable)[SOUND_HAUPTMANN_DEAD].Filename.Format("%s%s",PATH_SOUND, "Hauptmann_Dead.wav");
	(*g_pSoundTable)[SOUND_HAUPTMANN_DRAINED].Filename.Format("%s%s",PATH_SOUND, "Hauptmann_Drained.wav");
	(*g_pSoundTable)[SOUND_HAUPTMANN_MAGIC].Filename.Format("%s%s",PATH_SOUND, "Hauptmann_Magic.wav");
	//---------------------------------------------
	// 룽가테스타 - 신체변이
	//---------------------------------------------
	(*g_pSoundTable)[SOUND_LUNGA_TESTA_ATTACK].Filename.Format("%s%s",PATH_SOUND, "lungatesta_Attack.wav");
	(*g_pSoundTable)[SOUND_LUNGA_TESTA_DAMAGE].Filename.Format("%s%s",PATH_SOUND, "lungatesta_Damage.wav");
	(*g_pSoundTable)[SOUND_LUNGA_TESTA_DEAD].Filename.Format("%s%s",PATH_SOUND, "lungatesta_Dead.wav");
	(*g_pSoundTable)[SOUND_LUNGA_TESTA_DRAINED].Filename.Format("%s%s",PATH_SOUND, "lungatesta_Drained.wav");
	(*g_pSoundTable)[SOUND_LUNGA_TESTA_VAMPIRE_DRAIN].Filename.Format("%s%s",PATH_SOUND, "lungatesta_VampireDrain.wav");
	//---------------------------------------------
	// 오베르슈츠 - SR
	//---------------------------------------------
	(*g_pSoundTable)[SOUND_OBERSCHUTZE_SR_ATTACK].Filename.Format("%s%s",PATH_SOUND, "Oberschutze_SR_Attack.wav");
	(*g_pSoundTable)[SOUND_OBERSCHUTZE_SR_DAMAGE].Filename.Format("%s%s",PATH_SOUND, "Oberschutze_SR_Damage.wav");
	(*g_pSoundTable)[SOUND_OBERSCHUTZE_SR_DEAD].Filename.Format("%s%s",PATH_SOUND, "Oberschutze_SR_Dead.wav");
	(*g_pSoundTable)[SOUND_OBERSCHUTZE_SR_DRAINED].Filename.Format("%s%s",PATH_SOUND, "Oberschutze_SR_Drained.wav");
	(*g_pSoundTable)[SOUND_OBERSCHUTZE_SR_MELEE].Filename.Format("%s%s",PATH_SOUND, "Oberschutze_SR_Melee.wav");
	//---------------------------------------------
	// 로이카다브루 - 철퇴인간
	//---------------------------------------------
	(*g_pSoundTable)[SOUND_ROI_CADAVRU_ATTACK].Filename.Format("%s%s",PATH_SOUND, "RoiCadavru_Attack.wav");
	(*g_pSoundTable)[SOUND_ROI_CADAVRU_DAMAGE].Filename.Format("%s%s",PATH_SOUND, "RoiCadavru_Damage.wav");
	(*g_pSoundTable)[SOUND_ROI_CADAVRU_DEAD].Filename.Format("%s%s",PATH_SOUND, "RoiCadavru_Dead.wav");
	(*g_pSoundTable)[SOUND_ROI_CADAVRU_DRAINED].Filename.Format("%s%s",PATH_SOUND, "RoiCadavru_Drained.wav");
	(*g_pSoundTable)[SOUND_ROI_CADAVRU_VAMPIRE_DRAIN].Filename.Format("%s%s",PATH_SOUND, "RoiCadavru_VampireDrain.wav");
	//---------------------------------------------
	// 시아메스 - 쌍둥이
	//---------------------------------------------
	(*g_pSoundTable)[SOUND_SIAMESE_ATTACK].Filename.Format("%s%s",PATH_SOUND, "Siamese_Attack.wav");
	(*g_pSoundTable)[SOUND_SIAMESE_DAMAGE].Filename.Format("%s%s",PATH_SOUND, "Siamese_Damage.wav");
	(*g_pSoundTable)[SOUND_SIAMESE_DEAD].Filename.Format("%s%s",PATH_SOUND, "Siamese_Dead.wav");
	(*g_pSoundTable)[SOUND_SIAMESE_DRAINED].Filename.Format("%s%s",PATH_SOUND, "Siamese_Drained.wav");
	(*g_pSoundTable)[SOUND_SIAMESE_VAMPIRE_DRAIN].Filename.Format("%s%s",PATH_SOUND, "Siamese_VampireDrain.wav");
	//---------------------------------------------
	// 스터르만 - SMG
	//---------------------------------------------
	(*g_pSoundTable)[SOUND_STURMMANN_SMG_ATTACK].Filename.Format("%s%s",PATH_SOUND, "Sturmmann_SMG_Attack.wav");
	(*g_pSoundTable)[SOUND_STURMMANN_SMG_DAMAGE].Filename.Format("%s%s",PATH_SOUND, "Sturmmann_SMG_Damage.wav");
	(*g_pSoundTable)[SOUND_STURMMANN_SMG_DEAD].Filename.Format("%s%s",PATH_SOUND, "Sturmmann_SMG_Dead.wav");
	(*g_pSoundTable)[SOUND_STURMMANN_SMG_DRAINED].Filename.Format("%s%s",PATH_SOUND, "Sturmmann_SMG_Drained.wav");
	//---------------------------------------------
	// 터그레그 - 골룸
	//---------------------------------------------
	(*g_pSoundTable)[SOUND_TUGLEG_ATTACK].Filename.Format("%s%s",PATH_SOUND, "Tugleg_Attack.wav");
	(*g_pSoundTable)[SOUND_TUGLEG_DAMAGE].Filename.Format("%s%s",PATH_SOUND, "Tugleg_Damage.wav");
	(*g_pSoundTable)[SOUND_TUGLEG_DEAD].Filename.Format("%s%s",PATH_SOUND, "Tugleg_Dead.wav");
	(*g_pSoundTable)[SOUND_TUGLEG_DRAINED].Filename.Format("%s%s",PATH_SOUND, "Tugleg_Drained.wav");
	(*g_pSoundTable)[SOUND_TUGLEG_MOVE].Filename.Format("%s%s",PATH_SOUND, "Tugleg_Move.wav");
	(*g_pSoundTable)[SOUND_TUGLEG_VAMPIRE_DRAIN].Filename.Format("%s%s",PATH_SOUND, "Tugleg_VampireDrain.wav");
	// 2005, 1, 11, sobeit add end - 새로운 몬스터들
	//---------------------------------------------
	// 레어 스킬
	//---------------------------------------------
	(*g_pSoundTable)[SOUND_SLAYER_EAGLES_EYE].Filename.Format("%s%s",PATH_SOUND, "RareSkill_EaglesEye.wav");
	(*g_pSoundTable)[SOUND_SLAYER_FREEZE_RING].Filename.Format("%s%s",PATH_SOUND, "RareSkill_FreezeRing.wav");
	(*g_pSoundTable)[SOUND_SLAYER_MAGIC_SHIELD].Filename.Format("%s%s",PATH_SOUND, "RareSkill_MagicShield.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_CURSE_OF_BLOOD].Filename.Format("%s%s",PATH_SOUND, "RareSkill_CurseOfBlood.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_BLOODY_WING].Filename.Format("%s%s",PATH_SOUND, "RareSkill_BloodyWing.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_BLOODY_SHOUT_1].Filename.Format("%s%s",PATH_SOUND, "RareSkill_BloodyShout1.wav");
	(*g_pSoundTable)[SOUND_VAMPIRE_BLOODY_SHOUT_2].Filename.Format("%s%s",PATH_SOUND, "RareSkill_BloodyShout2.wav");
	(*g_pSoundTable)[SOUND_OUSTERS_MIST_OF_SOUL].Filename.Format("%s%s",PATH_SOUND, "RareSkill_MistOfSoul.wav");
	
	(*g_pSoundTable)[SOUND_CABERUS_ATTACK].Filename.Format("%s%s",PATH_SOUND, "caberus_attack.wav");
	(*g_pSoundTable)[SOUND_CABERUS_SKILL].Filename.Format("%s%s",PATH_SOUND, "caberus_skill.wav");
	(*g_pSoundTable)[SOUND_CABERUS_DIE].Filename.Format("%s%s",PATH_SOUND, "caberus_die.wav");

	(*g_pSoundTable)[SOUND_MANTICORET_ATTACK].Filename.Format("%s%s",PATH_SOUND, "manticoret_attack.wav");
	(*g_pSoundTable)[SOUND_MANTICORET_SKILL].Filename.Format("%s%s",PATH_SOUND, "manticoret_skill.wav");
	(*g_pSoundTable)[SOUND_MANTICORET_DIE].Filename.Format("%s%s",PATH_SOUND, "manticoret_die.wav");

	(*g_pSoundTable)[SOUND_BOGLET_B_ATTACK].Filename.Format("%s%s",PATH_SOUND, "boglet_b_attack.wav");
	(*g_pSoundTable)[SOUND_BOGLET_B_SKILL].Filename.Format("%s%s",PATH_SOUND, "boglet_b_skill.wav");
	(*g_pSoundTable)[SOUND_BOGLET_B_DIE].Filename.Format("%s%s",PATH_SOUND, "boglet_b_die.wav");

	(*g_pSoundTable)[SOUND_BOGLET_H_ATTACK].Filename.Format("%s%s",PATH_SOUND, "boglet_h_attack.wav");
	(*g_pSoundTable)[SOUND_BOGLET_H_SKILL].Filename.Format("%s%s",PATH_SOUND, "boglet_h_skill.wav");
	(*g_pSoundTable)[SOUND_BOGLET_H_DIE].Filename.Format("%s%s",PATH_SOUND, "boglet_h_die.wav");

	(*g_pSoundTable)[SOUND_MASSACRE_ATTACK].Filename.Format("%s%s",PATH_SOUND, "massacre_attack.wav");
	(*g_pSoundTable)[SOUND_MASSACRE_SKILL].Filename.Format("%s%s",PATH_SOUND, "massacre_skill.wav");
	(*g_pSoundTable)[SOUND_MASSACRE_DIE].Filename.Format("%s%s",PATH_SOUND, "massacre_die.wav");

	(*g_pSoundTable)[SOUND_PLUMYBOAR_ATTACK].Filename.Format("%s%s",PATH_SOUND, "plumyboar_attack.wav");
	(*g_pSoundTable)[SOUND_PLUMYBOAR_SKILL].Filename.Format("%s%s",PATH_SOUND, "plumyboar_skill.wav");
	(*g_pSoundTable)[SOUND_PLUMYBOAR_DIE].Filename.Format("%s%s",PATH_SOUND, "plumyboar_die.wav");

	(*g_pSoundTable)[SOUND_CABRACAM_ATTACK].Filename.Format("%s%s",PATH_SOUND, "cabracam_attack.wav");
	(*g_pSoundTable)[SOUND_CABRACAM_SKILL].Filename.Format("%s%s",PATH_SOUND, "cabracam_skill.wav");

	(*g_pSoundTable)[SOUND_BOOM_TRAP].Filename.Format("%s%s",PATH_SOUND, "boom_trap.wav");

	
	(*g_pSoundTable)[SOUND_FROZEN_GLACIER].Filename.Format("%s%s",PATH_SOUND, "frozen_glacier.wav");
	(*g_pSoundTable)[SOUND_HEAVENLY_SPARK].Filename.Format("%s%s",PATH_SOUND, "heavenly_spark.wav");
	(*g_pSoundTable)[SOUND_VENOM_CIRCLE].Filename.Format("%s%s",PATH_SOUND, "venom_circle.wav");

	(*g_pSoundTable)[SOUND_HOVER_VEHICLE].Filename.Format("%s%s",PATH_SOUND, "Hover Vehicle.wav");
	(*g_pSoundTable)[SOUND_SHAPE_OF_DEMON].Filename.Format("%s%s",PATH_SOUND, "Shape Of Demon.wav");
	(*g_pSoundTable)[SOUND_UNICORN].Filename.Format("%s%s",PATH_SOUND, "Unicorn.wav");


//#if __CONTENTS(__TIPOJYU_CASTLE) //사운드 추가
	(*g_pSoundTable)[SOUND_BBR_ATT1].Filename.Format("%s%s",PATH_SOUND, "Balberith_att_1.wav");
	(*g_pSoundTable)[SOUND_BBR_ATT2].Filename.Format("%s%s",PATH_SOUND, "Balberith_att_2.wav");
	(*g_pSoundTable)[SOUND_BBR_DAM].Filename.Format("%s%s",PATH_SOUND, "Balberith_dam.wav");
	(*g_pSoundTable)[SOUND_BBR_DIE].Filename.Format("%s%s",PATH_SOUND, "Balberith_die.wav");

	(*g_pSoundTable)[SOUND_BR_ATT1].Filename.Format("%s%s",PATH_SOUND, "Berith_att_1.wav");
	(*g_pSoundTable)[SOUND_BR_ATT2].Filename.Format("%s%s",PATH_SOUND, "Berith_att_2.wav");
	(*g_pSoundTable)[SOUND_BR_DAM].Filename.Format("%s%s",PATH_SOUND, "Berith_dam.wav");
	(*g_pSoundTable)[SOUND_BR_DIE].Filename.Format("%s%s",PATH_SOUND, "Berith_die.wav");

	(*g_pSoundTable)[SOUND_GMR_ATT1].Filename.Format("%s%s",PATH_SOUND, "Gomory_att_1.wav");
	(*g_pSoundTable)[SOUND_GMR_ATT2].Filename.Format("%s%s",PATH_SOUND, "Gomory_att_2.wav");
	(*g_pSoundTable)[SOUND_GMR_DAM].Filename.Format("%s%s",PATH_SOUND, "Gomory_dam.wav");
	(*g_pSoundTable)[SOUND_GMR_DIE].Filename.Format("%s%s",PATH_SOUND, "Gomory_die.wav");

	(*g_pSoundTable)[SOUND_GSO_ATT1].Filename.Format("%s%s",PATH_SOUND, "Krsnik_att_1.wav");
	(*g_pSoundTable)[SOUND_GSO_ATT2].Filename.Format("%s%s",PATH_SOUND, "Krsnik_att_2.wav");
	(*g_pSoundTable)[SOUND_GSO_ATT3].Filename.Format("%s%s",PATH_SOUND, "Gusion_att_3.wav");
	(*g_pSoundTable)[SOUND_GSO_DAM].Filename.Format("%s%s",PATH_SOUND, "Krsnik_dam.wav");
	(*g_pSoundTable)[SOUND_GSO_DIE].Filename.Format("%s%s",PATH_SOUND, "Krsnik_die.wav");

	(*g_pSoundTable)[SOUND_KRS_ATT1].Filename.Format("%s%s",PATH_SOUND, "Krsnik_att_1.wav");
	(*g_pSoundTable)[SOUND_KRS_ATT2].Filename.Format("%s%s",PATH_SOUND, "Krsnik_att_2.wav");
	(*g_pSoundTable)[SOUND_KRS_DAM].Filename.Format("%s%s",PATH_SOUND, "Krsnik_dam.wav");
	(*g_pSoundTable)[SOUND_KRS_DIE].Filename.Format("%s%s",PATH_SOUND, "Krsnik_die.wav");

	(*g_pSoundTable)[SOUND_MRG_ATT1].Filename.Format("%s%s",PATH_SOUND, "Morgoth_att_1.wav");
	(*g_pSoundTable)[SOUND_MRG_ATT2].Filename.Format("%s%s",PATH_SOUND, "Morgoth_att_2.wav");
	(*g_pSoundTable)[SOUND_MRG_ATT3].Filename.Format("%s%s",PATH_SOUND, "Morgoth_att_3.wav");
	(*g_pSoundTable)[SOUND_MRG_DAM].Filename.Format("%s%s",PATH_SOUND, "Morgoth_dam.wav");
	(*g_pSoundTable)[SOUND_MRG_DIE].Filename.Format("%s%s",PATH_SOUND, "Morgoth_die.wav");

	(*g_pSoundTable)[SOUND_KRS_ATT1].Filename.Format("%s%s",PATH_SOUND, "Krsnik_att_1.wav");
	(*g_pSoundTable)[SOUND_KRS_ATT2].Filename.Format("%s%s",PATH_SOUND, "Krsnik_att_2.wav");
	(*g_pSoundTable)[SOUND_KRS_DAM].Filename.Format("%s%s",PATH_SOUND, "Krsnik_dam.wav");
	(*g_pSoundTable)[SOUND_KRS_DIE].Filename.Format("%s%s",PATH_SOUND, "Krsnik_die.wav");

	(*g_pSoundTable)[SOUND_PM_ATT1].Filename.Format("%s%s",PATH_SOUND, "Paimon_att_1.wav");
	(*g_pSoundTable)[SOUND_PM_ATT2].Filename.Format("%s%s",PATH_SOUND, "Paimon_att_2.wav");
	(*g_pSoundTable)[SOUND_PM_DAM].Filename.Format("%s%s",PATH_SOUND, "Paimon_dam.wav");
	(*g_pSoundTable)[SOUND_PM_DIE].Filename.Format("%s%s",PATH_SOUND, "Paimon_die.wav");

	(*g_pSoundTable)[SOUND_VKR_ATT1].Filename.Format("%s%s",PATH_SOUND, "Valkyrja_att_1.wav");
	(*g_pSoundTable)[SOUND_VKR_ATT2].Filename.Format("%s%s",PATH_SOUND, "Valkyrja_att_2.wav");
	(*g_pSoundTable)[SOUND_VKR_DAM].Filename.Format("%s%s",PATH_SOUND, "Valkyrja_dam.wav");
	(*g_pSoundTable)[SOUND_VKR_DIE].Filename.Format("%s%s",PATH_SOUND, "Valkyrja_die.wav");

	(*g_pSoundTable)[SOUND_TIPOJYU_TRAP_A].Filename.Format("%s%s",PATH_SOUND, "Tiff_trap.wav");
	(*g_pSoundTable)[SOUND_TIPOJYU_TRAP_B].Filename.Format("%s%s",PATH_SOUND, "Tiff_trap.wav");
//#endif // __TIPOJYU_CASTLE
	//------------------------------------------------
	// Save
	//------------------------------------------------
	std::ofstream soundTable(g_pFileDef->getProperty("FILE_INFO_SOUND").c_str(), std::ios::binary);
	(*g_pSoundTable).SaveToFile(soundTable);
	soundTable.close();
#endif
	//*/

	//------------------------------------------------
	// Load
	//------------------------------------------------
	ivfstream soundTable2;//(FILE_INFO_SOUND, ios::binary);
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_INFO_SOUND").c_str(), soundTable2))
		return FALSE;
	(*g_pSoundTable).LoadFromFile(soundTable2);
	soundTable2.close();

	//------------------------------------------------
	// sound file 체크
	//------------------------------------------------
	for (int i=0; i<g_pSoundTable->GetSize(); i++)
	{
		if (!FileCheck( (*g_pSoundTable)[i].Filename.GetString() ))
		{
			return FALSE;
		}
	}
	return TRUE;
}
