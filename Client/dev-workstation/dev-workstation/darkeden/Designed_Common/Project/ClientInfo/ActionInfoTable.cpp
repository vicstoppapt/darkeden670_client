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

#define SAVE_TO_FILE

#define SLAYER_MAGIC_SELF_START_FRAME 7

HRESULT InitFail(LPCTSTR szError,...);
bool 
FileOpenBinary(const char* filename, ivfstream& file);
//---------------------------------------------------------------------------
// Open File
//---------------------------------------------------------------------------
bool 
FileCheck(const char* filename);
BOOL	InitActionInfoTableOusters(CCreatureFramePack &OustersFPK ,int *FrameSize, int *OustersActionDelay);
BOOL	InitActionInfoTableFireCracker(int *FrameSize);
BOOL	InitActionInfoTableVampire(CCreatureFramePack &CreatureFPK ,int *FrameSize, int *VampireActionDelay);

BOOL	InitActionInfoTable(
	CCreatureFramePack	&AddonManFPK,
	CCreatureFramePack	&AddonWomanFPK,
	CCreatureFramePack	&CreatureFPK,
	CCreatureFramePack	&OustersFPK,
	int *FrameSize)
{
	//---------------------------------------------------------------------
	//
	//         ActionInfoTable 정보 생성
	//
	//---------------------------------------------------------------------	
	///*
#ifdef SAVE_TO_FILE

	//---------------------------------------------------------------------	
	// 필요한 정보 --> EffectFramePack
	//---------------------------------------------------------------------	
	//CEffectFramePack EFPK;
	//std::ifstream efpkFile(FILE_EFRAME_ALPHAEFFECT, ios::binary);
	//EFPK.LoadFromFile( efpkFile );
	//efpkFile.close();

	//---------------------------------------------------------------------	
	// ActionInfoTable 초기화
	//---------------------------------------------------------------------	
	(*g_pActionInfoTable).Init( MAX_ACTIONINFO );

	// action / result 의 경계 값 설정
	(*g_pActionInfoTable).SetMinResultActionInfo( MIN_RESULT_ACTIONINFO );
	(*g_pActionInfoTable).SetMaxResultActionInfo( MAX_RESULT_ACTIONINFO );

	for (int i=0; i<MAX_ACTIONINFO; i++)
	{
		(*g_pActionInfoTable)[i].Set("...Not Defined...", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, 500);
		(*g_pActionInfoTable)[i].SetSoundID( SOUNDID_NULL );
		
		(*g_pActionInfoTable)[i].SetMaleSoundID( SOUNDID_NULL );
		(*g_pActionInfoTable)[i].SetFemaleSoundID( SOUNDID_NULL );
	}

	//---------------------------------------------------------------------	
	// delay시간 계산
	//---------------------------------------------------------------------	
	int ActionDelay[ACTION_MAX_SLAYER];
	int VampireActionDelay[ACTION_MAX_VAMPIRE];
	int OustersActionDelay[ACTION_MAX_OUSTERS];

	int frameNum;
	for (int ad=0; ad<ACTION_MAX_SLAYER; ad++)
	{	
		if (ad < AddonManFPK[0].GetSize())
		{
			frameNum = AddonManFPK[ADDONID_COAT1][ad][0].GetSize()-1;

			if (frameNum < 0) frameNum = 0;

			ActionDelay[ad] = frameNum * 1000 / 16;
		}
	}

	for (ad=0; ad<ACTION_MAX_VAMPIRE; ad++)
	{
		if (ad < CreatureFPK[0].GetSize())
		{
			frameNum = CreatureFPK[0][ad][0].GetSize()-1;

			if (frameNum < 0) frameNum = 0;

			VampireActionDelay[ad] = frameNum * 1000 / 16;
		}
	}

	for (ad=0; ad<ACTION_MAX_OUSTERS; ad++)
	{
		if( ad < OustersFPK[1].GetSize() )
		{
			frameNum = OustersFPK[1][ad][0].GetSize() - 1;

			if( frameNum < 0 ) frameNum =0;

			OustersActionDelay[ad] = frameNum * 1000 / 16;
		}
	}

// -_-;;;
#ifdef ACTION_DAMAGED
	//#undef ACTION_DAMAGED
	//#define ACTION_DAMAGED		ACTION_STAND
#endif

	//-------------------------------------------------------------
	//
	//                         기본 기술
	//
	//-------------------------------------------------------------
	// SKILL_ATTACK_MELEE,	// 기본 공격
	(*g_pActionInfoTable)[SKILL_ATTACK_MELEE].Set("SKILL_ATTACK_MELEE", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_VAMPIRE_ATTACK_FAST]);
	(*g_pActionInfoTable)[SKILL_ATTACK_MELEE].SetStartFrameAll( 8 );
	(*g_pActionInfoTable)[SKILL_ATTACK_MELEE].SetActionStepCnt(1) ; 
	(*g_pActionInfoTable)[SKILL_ATTACK_MELEE].SetSoundID( SOUNDID_NULL );

	// SKILL_ATTACK_ARMS,	// 기본 공격
	(*g_pActionInfoTable)[SKILL_ATTACK_ARMS].Set("SKILL_ATTACK_ARMS", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_ATTACK_ARMS].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_ATTACK_ARMS].SetSoundID( SOUNDID_NULL );

	// SKILL_ATTACK_GUN_SR - 저격용총(TR)
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SR].Set("SKILL_ATTACK_GUN_SR", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_GUN_SR_MALE, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_GUN_SR_FAST]);
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SR].SetStartFrame( 0, 12 );			// slow
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SR].SetStartFrame( 1, 10 );			// normal
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SR].SetStartFrame( 2, 8 );			// fast
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SR].SetActionEffectSpriteTypeFemale( EFFECTSPRITETYPE_GUN_SR_FEMALE );
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SR].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_SR );
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SR].SetAffectCurrentWeaponRange();	// 들고 있는 무기의 range적용
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SR].SetSoundID( SOUND_SLAYER_ATTACK_SR );
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SR].SetCastingStartFrame( 0, 12 );	// slow
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SR].SetCastingStartFrame( 1, 10 );	// normal
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SR].SetCastingStartFrame( 2, 8 );	// fast
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SR].SetCastingFrames( 0, 3 );		// slow
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SR].SetCastingFrames( 1, 3 );		// normal
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SR].SetCastingFrames( 2, 3 );		// fast
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SR].SetRepeatFrame( 0, 6, 10);		// slow
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SR].SetRepeatFrame( 1, 4, 10);		// normal
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SR].SetRepeatFrame( 2, 2, 10);		// fast
	
	// SKILL_ATTACK_GUN_SG - 샷건(SG)
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SG].Set("SKILL_ATTACK_GUN_SG", ACTION_SLAYER_GUN_SG, EFFECTSPRITETYPE_GUN_SG_MALE, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_GUN_SG_FAST]);
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SG].SetStartFrame( 0, 7 );			// slow
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SG].SetStartFrame( 1, 7 );			// normal
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SG].SetStartFrame( 2, 5 );			// fast
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SG].SetActionEffectSpriteTypeFemale( EFFECTSPRITETYPE_GUN_SG_FEMALE );
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SG].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_SG );
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SG].SetAffectCurrentWeaponRange();	// 들고 있는 무기의 range적용
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SG].SetSoundID( SOUND_SLAYER_ATTACK_SG );
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SG].SetCastingStartFrame( 0, 7 );	// slow
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SG].SetCastingStartFrame( 1, 7 );	// normal
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SG].SetCastingStartFrame( 2, 5 );	// fast
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SG].SetCastingFrames( 0, 3 );		// slow
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SG].SetCastingFrames( 1, 3 );		// normal
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SG].SetCastingFrames( 2, 3 );		// fast
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SG].SetRepeatFrame( 0, 7, 10);		// slow
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SG].SetRepeatFrame( 1, 5, 10);		// normal
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SG].SetRepeatFrame( 2, 3, 10);		// fast
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SG].Init( 1 );
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SG][0].EffectGeneratorID	= EFFECTGENERATORID_AROUND_ZONE;
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SG][0].EffectSpriteType	= EFFECTSPRITETYPE_GUN_DUST_1;
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SG][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SG][0].Count				= FrameSize[EFFECTSPRITETYPE_GUN_DUST_1];

	// SKILL_ATTACK_GUN_AR - 소총(AR)
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_AR].Set("SKILL_ATTACK_GUN_AR", ACTION_SLAYER_GUN_AR, EFFECTSPRITETYPE_GUN_AR_MALE, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_GUN_AR_FAST]);
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_AR].SetStartFrame( 0, 8 );			// slow
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_AR].SetStartFrame( 1, 7 );			// normal
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_AR].SetStartFrame( 2, 6 );			// fast
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_AR].SetActionEffectSpriteTypeFemale( EFFECTSPRITETYPE_GUN_AR_FEMALE );
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_AR].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_AR );
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_AR].SetAffectCurrentWeaponRange();	// 들고 있는 무기의 range적용
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_AR].SetSoundID( SOUND_SLAYER_ATTACK_AR );
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_AR].SetCastingStartFrame( 0, 8 );	// slow
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_AR].SetCastingStartFrame( 1, 7 );	// normal
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_AR].SetCastingStartFrame( 2, 6 );	// fast
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_AR].SetCastingFrames( 0, 2 );		// slow
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_AR].SetCastingFrames( 1, 2 );		// normal
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_AR].SetCastingFrames( 2, 2 );		// fast
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_AR].SetRepeatFrame( 0, 7, 6);		// slow
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_AR].SetRepeatFrame( 1, 5, 6);		// normal
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_AR].SetRepeatFrame( 2, 4, 6);		// fast

	// SKILL_ATTACK_GUN_SMG - 자동소총(SMG)
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SMG].Set("SKILL_ATTACK_GUN_SMG", ACTION_SLAYER_GUN_SMG, EFFECTSPRITETYPE_GUN_SMG_MALE, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_GUN_SMG_FAST]);
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SMG].SetStartFrame( 0, 8 );			// slow
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SMG].SetStartFrame( 1, 7 );			// normal
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SMG].SetStartFrame( 2, 6 );			// fast
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SMG].SetActionEffectSpriteTypeFemale( EFFECTSPRITETYPE_GUN_SMG_FEMALE );
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SMG].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_SMG );
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SMG].SetAffectCurrentWeaponRange();	// 들고 있는 무기의 range적용
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SMG].SetSoundID( SOUND_SLAYER_ATTACK_SMG );
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SMG].SetCastingStartFrame( 0, 8 );	// slow
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SMG].SetCastingStartFrame( 1, 7 );	// normal
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SMG].SetCastingStartFrame( 2, 6 );	// fast
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SMG].SetCastingFrames( 0, 2 );		// slow
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SMG].SetCastingFrames( 1, 2 );		// normal
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SMG].SetCastingFrames( 2, 2 );		// fast
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SMG].SetRepeatFrame( 0, 8, 5);		// slow
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SMG].SetRepeatFrame( 1, 6, 5);		// normal
	(*g_pActionInfoTable)[SKILL_ATTACK_GUN_SMG].SetRepeatFrame( 2, 4, 5);		// fast
	
	// SKILL_ATTACK_SWORD,	// 기본 공격
	(*g_pActionInfoTable)[SKILL_ATTACK_SWORD].Set("SKILL_ATTACK_SWORD", ACTION_SLAYER_SWORD, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_SWORD]);
	(*g_pActionInfoTable)[SKILL_ATTACK_SWORD].SetStartFrame( 0, 10 );
	(*g_pActionInfoTable)[SKILL_ATTACK_SWORD].SetStartFrame( 1, 8 );
	(*g_pActionInfoTable)[SKILL_ATTACK_SWORD].SetStartFrame( 2, 6 );
	(*g_pActionInfoTable)[SKILL_ATTACK_SWORD].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_ATTACK_SWORD].SetActionStepCnt(1) ; 
	(*g_pActionInfoTable)[SKILL_ATTACK_SWORD].SetAffectCurrentWeaponRange();	// 들고 있는 무기의 range적용
	(*g_pActionInfoTable)[SKILL_ATTACK_SWORD].SetSoundID( SOUNDID_NULL );

	// SKILL_ATTACK_BLADE,	// 기본 공격
	(*g_pActionInfoTable)[SKILL_ATTACK_BLADE].Set("SKILL_ATTACK_BLADE", ACTION_SLAYER_BLADE, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_BLADE]);
	(*g_pActionInfoTable)[SKILL_ATTACK_BLADE].SetStartFrame( 0, 12 );
	(*g_pActionInfoTable)[SKILL_ATTACK_BLADE].SetStartFrame( 1, 10 );
	(*g_pActionInfoTable)[SKILL_ATTACK_BLADE].SetStartFrame( 2, 8 );
	(*g_pActionInfoTable)[SKILL_ATTACK_BLADE].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_ATTACK_BLADE].SetActionStepCnt(1) ; 
	(*g_pActionInfoTable)[SKILL_ATTACK_BLADE].SetAffectCurrentWeaponRange();	// 들고 있는 무기의 range적용
	(*g_pActionInfoTable)[SKILL_ATTACK_BLADE].SetSoundID( SOUNDID_NULL );


	// SKILL_HOLY_SHOOTING_TR - 저격용총(TR)
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_TR].Set("SKILL_HOLY_SHOOTING_TR", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_HOLY_SHOOTING_TR_MALE, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_GUN_SR_FAST]);
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_TR].SetStartFrame( 0, 12 );			// slow
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_TR].SetStartFrame( 1, 10 );			// normal
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_TR].SetStartFrame( 2, 8 );			// fast	
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_TR].SetActionEffectSpriteTypeFemale( EFFECTSPRITETYPE_HOLY_SHOOTING_TR_FEMALE );
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_TR].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_SR );	// 총알 사용 안 한다.
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_TR].SetAffectCurrentWeaponRange();	// 들고 있는 무기의 range적용
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_TR].SetSoundID( SOUND_SLAYER_ATTACK_TR );
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_TR].SetCastingStartFrame( 0, 12 );	// slow
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_TR].SetCastingStartFrame( 1, 10 );	// normal
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_TR].SetCastingStartFrame( 2, 8 );	// fast
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_TR].SetCastingFrames( 0, 3 );		// slow
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_TR].SetCastingFrames( 1, 3 );		// normal
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_TR].SetCastingFrames( 2, 3 );		// fast
	

	// SKILL_HOLY_SHOOTING_SG - 샷건(SG)
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SG].Set("SKILL_HOLY_SHOOTING_SG", ACTION_SLAYER_GUN_SG, EFFECTSPRITETYPE_HOLY_SHOOTING_SG_MALE, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_GUN_SG_FAST]);
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SG].SetStartFrame( 0, 7 );			// slow
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SG].SetStartFrame( 1, 7 );			// normal
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SG].SetStartFrame( 2, 5 );			// fast	
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SG].SetActionEffectSpriteTypeFemale( EFFECTSPRITETYPE_HOLY_SHOOTING_SG_FEMALE );
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SG].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_SG );
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SG].SetAffectCurrentWeaponRange();	// 들고 있는 무기의 range적용
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SG].SetSoundID( SOUND_SLAYER_ATTACK_SG );	
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SG].SetCastingStartFrame( 0, 7 );	// slow
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SG].SetCastingStartFrame( 1, 7 );	// normal
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SG].SetCastingStartFrame( 2, 5 );	// fast
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SG].SetCastingFrames( 0, 2 );		// slow
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SG].SetCastingFrames( 1, 2 );		// normal
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SG].SetCastingFrames( 2, 2 );		// fast
	
	// SKILL_HOLY_SHOOTING_AR - 소총(AR)
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_AR].Set("SKILL_HOLY_SHOOTING_AR", ACTION_SLAYER_GUN_AR, EFFECTSPRITETYPE_HOLY_SHOOTING_AR_MALE, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_GUN_AR_FAST]);
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_AR].SetStartFrame( 0, 9 );			// slow
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_AR].SetStartFrame( 1, 7 );			// normal
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_AR].SetStartFrame( 2, 6 );			// fast
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_AR].SetActionEffectSpriteTypeFemale( EFFECTSPRITETYPE_HOLY_SHOOTING_AR_FEMALE );
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_AR].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_AR );
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_AR].SetAffectCurrentWeaponRange();	// 들고 있는 무기의 range적용
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_AR].SetSoundID( SOUND_SLAYER_ATTACK_AR );
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_AR].SetCastingStartFrame( 0, 9 );	// slow
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_AR].SetCastingStartFrame( 1, 7 );	// normal
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_AR].SetCastingStartFrame( 2, 6 );	// fast
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_AR].SetCastingFrames( 0, 3 );		// slow
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_AR].SetCastingFrames( 1, 3 );		// normal
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_AR].SetCastingFrames( 2, 3 );		// fast
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_AR].SetRepeatFrame( 0, 9, 6 );		// slow
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_AR].SetRepeatFrame( 1, 7, 6 );		// normal
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_AR].SetRepeatFrame( 2, 6, 6 );		// fast

	// SKILL_HOLY_SHOOTING_SMG - 자동소총(SMG)
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SMG].Set("SKILL_HOLY_SHOOTING_SMG", ACTION_SLAYER_GUN_SMG, EFFECTSPRITETYPE_HOLY_SHOOTING_SMG_MALE, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_GUN_SMG_FAST]);
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SMG].SetStartFrame( 0, 9 );			// slow
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SMG].SetStartFrame( 1, 7 );			// normal
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SMG].SetStartFrame( 2, 6 );			// fast
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SMG].SetActionEffectSpriteTypeFemale( EFFECTSPRITETYPE_HOLY_SHOOTING_SMG_FEMALE );
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SMG].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_SMG );
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SMG].SetAffectCurrentWeaponRange();	// 들고 있는 무기의 range적용
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SMG].SetSoundID( SOUND_SLAYER_ATTACK_SMG );	
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SMG].SetCastingStartFrame( 0, 9 );	// slow
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SMG].SetCastingStartFrame( 1, 7 );	// normal
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SMG].SetCastingStartFrame( 2, 6 );	// fast
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SMG].SetCastingFrames( 0, 2 );		// slow
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SMG].SetCastingFrames( 1, 2 );		// normal
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SMG].SetCastingFrames( 2, 2 );		// fast
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SMG].SetRepeatFrame( 0, 9, 6 );		// slow
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SMG].SetRepeatFrame( 1, 7, 6 );		// normal
//	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING_SMG].SetRepeatFrame( 2, 6, 6 );		// fast
	

	//-------------------------------------------------------------
	//
	//                         테스트용
	//
	//-------------------------------------------------------------
	// SKILL_SELF
	(*g_pActionInfoTable)[SKILL_SELF].Set("SKILL_SELF", ACTION_MAGIC, EFFECTSPRITETYPE_LIGHT_2, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[SKILL_SELF].SetSoundID( SOUNDID_NULL );

	// SKILL_TILE
	(*g_pActionInfoTable)[SKILL_TILE].Set("SKILL_TILE", ACTION_MAGIC, EFFECTSPRITETYPE_LIGHT_2, 5, FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[SKILL_TILE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TILE].SetActionResult(SKILL_TILE);


	// SKILL_OBJECT
	(*g_pActionInfoTable)[SKILL_OBJECT].Set("SKILL_OBJECT", ACTION_MAGIC, EFFECTSPRITETYPE_LIGHT_2, 5, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[SKILL_OBJECT].SetSoundID( SOUNDID_NULL );	

	//-------------------------------------------------------------
	//
	//                         검 계열
	//
	//-------------------------------------------------------------
	// SKILL_DOUBLE_IMPACT
	(*g_pActionInfoTable)[SKILL_DOUBLE_IMPACT].Set("SKILL_DOUBLE_IMPACT", ACTION_SLAYER_SWORD, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD]);
	(*g_pActionInfoTable)[SKILL_DOUBLE_IMPACT].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_DOUBLE_IMPACT].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_DOUBLE_IMPACT].SetStartFrame( 0, 10 );
	(*g_pActionInfoTable)[SKILL_DOUBLE_IMPACT].SetStartFrame( 1, 8 );
	(*g_pActionInfoTable)[SKILL_DOUBLE_IMPACT].SetStartFrame( 2, 6 );
	(*g_pActionInfoTable)[SKILL_DOUBLE_IMPACT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_DOUBLE_IMPACT].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_DOUBLE_IMPACT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_DOUBLE_IMPACT][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_DOUBLE_IMPACT ; // chyaya 2006.02.17 EFFECTSPRITETYPE_DOUBLE_IMPACT;
	(*g_pActionInfoTable)[SKILL_DOUBLE_IMPACT][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_DOUBLE_IMPACT][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_DOUBLE_IMPACT] ; // EFFECTSPRITETYPE_DOUBLE_IMPACT];
	(*g_pActionInfoTable)[SKILL_DOUBLE_IMPACT][0].SoundID			= SOUND_SLAYER_SWORD_DOUBLE_IMPACT ; //SOUND_SLAYER_SWORD_DI;
	(*g_pActionInfoTable)[SKILL_DOUBLE_IMPACT][0].SetResultTime();
	
    // SKILL_TRIPLE_SLASHER
	(*g_pActionInfoTable)[SKILL_TRIPLE_SLASHER].Set("SKILL_TRIPLE_SLASHER", ACTION_SLAYER_SWORD_2, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD_2]);
	(*g_pActionInfoTable)[SKILL_TRIPLE_SLASHER].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_TRIPLE_SLASHER].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_TRIPLE_SLASHER].SetStartFrameAll( 9 );	// 기술 effect가 시작되는 frame
	(*g_pActionInfoTable)[SKILL_TRIPLE_SLASHER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TRIPLE_SLASHER].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_TRIPLE_SLASHER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_TRIPLE_SLASHER][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_TRIPLE_SlASHER ; // chyaya 2006.02.17 EFFECTSPRITETYPE_TRIPLE_SLASHER;
	(*g_pActionInfoTable)[SKILL_TRIPLE_SLASHER][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TRIPLE_SLASHER][0].Count			= FrameSize[EFFECTSPRITETYPE_NEW_TRIPLE_SlASHER] ; //EFFECTSPRITETYPE_TRIPLE_SLASHER];
	(*g_pActionInfoTable)[SKILL_TRIPLE_SLASHER][0].SoundID			= SOUND_SLAYER_SWORD_TS;
	(*g_pActionInfoTable)[SKILL_TRIPLE_SLASHER][0].SetResultTime();
	

	// SKILL_SCREW_SLASHER,       
	/*
	(*g_pActionInfoTable)[SKILL_SCREW_SLASHER].Set("SKILL_SCREW_SLASHER", ACTION_SLAYER_SWORD, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD]);
	(*g_pActionInfoTable)[SKILL_SCREW_SLASHER].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_SCREW_SLASHER].SetStartFrameAll( 1 );	// 기술 effect가 시작되는 frame
	(*g_pActionInfoTable)[SKILL_SCREW_SLASHER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_SCREW_SLASHER].Init( 1 );	
	(*g_pActionInfoTable)[SKILL_SCREW_SLASHER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_SCREW_SLASHER][0].EffectSpriteType	= EFFECTSPRITETYPE_SCREW_SLASHER;
	(*g_pActionInfoTable)[SKILL_SCREW_SLASHER][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SCREW_SLASHER][0].Count				= FrameSize[EFFECTSPRITETYPE_SCREW_SLASHER];
	(*g_pActionInfoTable)[SKILL_SCREW_SLASHER][0].SoundID			= SOUND_SLAYER_SWORD_SS;
	*/

    // SKILL_RAINBOW_SLASHER
#ifdef __EXPO_CLIENT__
	(*g_pActionInfoTable)[SKILL_RAINBOW_SLASHER].SetExpoSkill();
#endif
	(*g_pActionInfoTable)[SKILL_RAINBOW_SLASHER].Set("SKILL_RAINBOW_SLASHER", ACTION_SLAYER_SWORD_2, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD_2]);
	(*g_pActionInfoTable)[SKILL_RAINBOW_SLASHER].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_RAINBOW_SLASHER].SetStartFrameAll( 9 );	// 기술 effect가 시작되는 frame
	(*g_pActionInfoTable)[SKILL_RAINBOW_SLASHER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_RAINBOW_SLASHER].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_RAINBOW_SLASHER].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_RAINBOW_SLASHER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_RAINBOW_SLASHER][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_RAINDOW_SLASHER ; // chyaya 2006.02.17 EFFECTSPRITETYPE_RAINBOW_SLASHER;
	(*g_pActionInfoTable)[SKILL_RAINBOW_SLASHER][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_RAINBOW_SLASHER][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_RAINDOW_SLASHER] ; //EFFECTSPRITETYPE_RAINBOW_SLASHER];
	(*g_pActionInfoTable)[SKILL_RAINBOW_SLASHER][0].SoundID			= SOUND_SLAYER_SWORD_RS;
	(*g_pActionInfoTable)[SKILL_RAINBOW_SLASHER][0].SetResultTime();

    // SKILL_THUNDER_SPARK
#ifdef __EXPO_CLIENT__
	(*g_pActionInfoTable)[SKILL_THUNDER_SPARK].SetExpoSkill();
#endif
	(*g_pActionInfoTable)[SKILL_THUNDER_SPARK].Set("SKILL_THUNDER_SPARK", ACTION_SLAYER_SWORD_2, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD_2]);
	(*g_pActionInfoTable)[SKILL_THUNDER_SPARK].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_THUNDER_SPARK].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_THUNDER_SPARK].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_THUNDER_SPARK].SetStartFrameAll( 9 );	// 기술 effect가 시작되는 frame
	(*g_pActionInfoTable)[SKILL_THUNDER_SPARK].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_THUNDER_SPARK][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_THUNDER_SPARK][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_THUNDER_SPARK ; // chyaya 2006.02.17 EFFECTSPRITETYPE_THUNDER_SPARK;
	(*g_pActionInfoTable)[SKILL_THUNDER_SPARK][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_THUNDER_SPARK][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_THUNDER_SPARK] ; // EFFECTSPRITETYPE_THUNDER_SPARK];
	(*g_pActionInfoTable)[SKILL_THUNDER_SPARK][0].SoundID			= SOUND_SLAYER_SWORD_THUNDER_SPARK ; //SOUND_SLAYER_SWORD_THS;
	(*g_pActionInfoTable)[SKILL_THUNDER_SPARK][0].SetResultTime();

	(*g_pActionInfoTable)[SKILL_DANCING_SWORD].Set("SKILL_DANCING_SWORD", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_DANCING_SWORD].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_DANCING_SWORD].SetSoundID( SOUNDID_NULL );
//	(*g_pActionInfoTable)[SKILL_DANCING_SWORD].SetStartFrameAll( 9 );	// 기술 effect가 시작되는 frame	

	// SKILL_CRUSH_COMBO
	/*
	(*g_pActionInfoTable)[SKILL_CRUSH_COMBO].Set("SKILL_CRUSH_COMBO", ACTION_SLAYER_SWORD, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD]);
	(*g_pActionInfoTable)[SKILL_CRUSH_COMBO].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_CRUSH_COMBO].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_CRUSH_COMBO].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CRUSH_COMBO].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CRUSH_COMBO][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CRUSH_COMBO][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[SKILL_CRUSH_COMBO][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CRUSH_COMBO][0].Count				= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[SKILL_CRUSH_COMBO][0].SoundID			= 0;
	*/

    // SKILL_HURRICANE_COMBO
	(*g_pActionInfoTable)[SKILL_HURRICANE_COMBO].Set("SKILL_HURRICANE_COMBO", ACTION_SLAYER_BLADE_2, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD_2]);
	(*g_pActionInfoTable)[SKILL_HURRICANE_COMBO].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_HURRICANE_COMBO].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_HURRICANE_COMBO].SetStartFrameAll( 13 );	// 기술 effect가 시작되는 frame
	(*g_pActionInfoTable)[SKILL_HURRICANE_COMBO].SetActionStepCnt(2) ;
	(*g_pActionInfoTable)[SKILL_HURRICANE_COMBO].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_HURRICANE_COMBO][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_HURRICANE_COMBO][0].EffectSpriteType	= EFFECTSPRITETYPE_HURRICANE_COMBO;
	(*g_pActionInfoTable)[SKILL_HURRICANE_COMBO][0].Step				= 19;
	(*g_pActionInfoTable)[SKILL_HURRICANE_COMBO][0].Count				= FrameSize[EFFECTSPRITETYPE_HURRICANE_COMBO];
	(*g_pActionInfoTable)[SKILL_HURRICANE_COMBO][0].SoundID			= SOUND_SLAYER_SWORD_THS ; //SOUND_SLAYER_SWORD_THS;
	(*g_pActionInfoTable)[SKILL_HURRICANE_COMBO][0].SetResultTime();

    // SKILL_CHAOS_COMBO
	/*
	(*g_pActionInfoTable)[SKILL_CHAOS_COMBO].Set("SKILL_CHAOS_COMBO", ACTION_SLAYER_SWORD_2, EFFECTSPRITETYPE_CHAOS_COMBO, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD_2]);
	(*g_pActionInfoTable)[SKILL_CHAOS_COMBO].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_CHAOS_COMBO].SetCastingStartFrameAll( 4 );	// 기술 effect가 시작되는 frame
	(*g_pActionInfoTable)[SKILL_CHAOS_COMBO].SetCastingFramesAll( 27 );
	*/
	
    // SKILL_SNAKE_COMBO
	(*g_pActionInfoTable)[SKILL_SNAKE_COMBO].Set("SKILL_SNAKE_COMBO", ACTION_SLAYER_SWORD_2, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD_2]);
	(*g_pActionInfoTable)[SKILL_SNAKE_COMBO].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_SNAKE_COMBO].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_SNAKE_COMBO].SetStartFrameAll( 8 );	// 기술 effect가 시작되는 frame
	(*g_pActionInfoTable)[SKILL_SNAKE_COMBO].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_SNAKE_COMBO].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_SNAKE_COMBO][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_SNAKE_COMBO][0].EffectSpriteType	= EFFECTSPRITETYPE_SNAKE_COMBO;
	(*g_pActionInfoTable)[SKILL_SNAKE_COMBO][0].Step				= 20;
	(*g_pActionInfoTable)[SKILL_SNAKE_COMBO][0].Count				= FrameSize[EFFECTSPRITETYPE_SNAKE_COMBO];
	(*g_pActionInfoTable)[SKILL_SNAKE_COMBO][0].SoundID			= SOUND_SLAYER_SWORD_SC;
	(*g_pActionInfoTable)[SKILL_SNAKE_COMBO][0].SetResultTime();

    // SKILL_SHIELD_STRIKE
	/*
	(*g_pActionInfoTable)[SKILL_SHIELD_STRIKE].Set("SKILL_SHIELD_STRIKE", ACTION_SLAYER_SWORD, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_SWORD]);
	(*g_pActionInfoTable)[SKILL_SHIELD_STRIKE].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_SHIELD_STRIKE].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_SHIELD_STRIKE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_SHIELD_STRIKE].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_SHIELD_STRIKE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_SHIELD_STRIKE][0].EffectSpriteType	= EFFECTSPRITETYPE_TRIPLE_SLASHER;
	(*g_pActionInfoTable)[SKILL_SHIELD_STRIKE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SHIELD_STRIKE][0].Count				= FrameSize[EFFECTSPRITETYPE_TRIPLE_SLASHER];
	(*g_pActionInfoTable)[SKILL_SHIELD_STRIKE][0].SoundID			= 0;
	*/

	// SKILL_CROSS_COUNTER
	(*g_pActionInfoTable)[SKILL_CROSS_COUNTER].Set("SKILL_CROSS_COUNTER", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_CROSS_COUNTER].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_CROSS_COUNTER].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_CROSS_COUNTER].SetSoundID( SOUND_SLAYER_CHARGE );
	/*
	(*g_pActionInfoTable)[SKILL_CROSS_COUNTER].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CROSS_COUNTER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CROSS_COUNTER][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[SKILL_CROSS_COUNTER][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CROSS_COUNTER][0].Count			= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[SKILL_CROSS_COUNTER][0].SoundID			= 0;
	*/

	// SKILL_PROTECTION_FIELD
	/*
	(*g_pActionInfoTable)[SKILL_PROTECTION_FIELD].Set("SKILL_PROTECTION_FIELD", ACTION_SLAYER_SWORD, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD]);
	(*g_pActionInfoTable)[SKILL_PROTECTION_FIELD].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_PROTECTION_FIELD].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_PROTECTION_FIELD].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_PROTECTION_FIELD].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_PROTECTION_FIELD][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_PROTECTION_FIELD][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[SKILL_PROTECTION_FIELD][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_PROTECTION_FIELD][0].Count			= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[SKILL_PROTECTION_FIELD][0].SoundID			= 0;
	*/

	// SKILL_FLASH_SLIDING
	(*g_pActionInfoTable)[SKILL_FLASH_SLIDING].Set("SKILL_FLASH_SLIDING", ACTION_STAND, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, 10);//ActionDelay[ACTION_SLAYER_SWORD]);
	(*g_pActionInfoTable)[SKILL_FLASH_SLIDING].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_FLASH_SLIDING].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_FLASH_SLIDING].SetSoundID( SOUNDID_NULL );
	/*
	(*g_pActionInfoTable)[SKILL_FLASH_SLIDING].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_FLASH_SLIDING][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_FLASH_SLIDING][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[SKILL_FLASH_SLIDING][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_FLASH_SLIDING][0].Count			= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	*/

	// SKILL_RAGE
	/*
	(*g_pActionInfoTable)[SKILL_RAGE].Set("SKILL_RAGE", ACTION_SLAYER_SWORD, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD]);
	(*g_pActionInfoTable)[SKILL_RAGE].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_RAGE].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_RAGE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_RAGE].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_RAGE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_RAGE][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[SKILL_RAGE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_RAGE][0].Count			= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[SKILL_RAGE][0].SoundID			= 0;
	*/

	// SKILL_LIGHTNING_HAND
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND].Set("SKILL_LIGHTNING_HAND", ACTION_SLAYER_SWORD_2_REPEAT, EFFECTSPRITETYPE_LIGHTNING_HANDS_2, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD_2]);
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND].SetCastingEffectToOther();	// casting effect를 다른 사람에게 붙인다.
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND].SetSoundID( SOUND_SLAYER_SWORD_LIGHTNING_HAND) ; //SOUND_SLAYER_SWORD_LH );
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND].SetCastingStartFrameAll( 5 );	// 불꽃이 붙는 frame
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND].UseRepeatFrame();	
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND].SetStartFrame( 0, 18 );			// slow
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND].SetStartFrame( 1, 18 );			// normal
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND].SetStartFrame( 2, 18 );			// fast
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND].SetCastingStartFrame( 0, 7 );	// slow
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND].SetCastingStartFrame( 1, 7 );	// normal
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND].SetCastingStartFrame( 2, 7 );	// fast
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND].SetCastingFrames( 0, 10 );		// slow
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND].SetCastingFrames( 1, 10 );		// normal
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND].SetCastingFrames( 2, 10 );		// fast
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND].SetRepeatFrame( 0, 7, 11 );		// slow
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND].SetRepeatFrame( 1, 7, 11 );		// normal
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND].SetRepeatFrame( 2, 7, 11 );		// fast
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND][0].EffectSpriteType		= EFFECTSPRITETYPE_LIGHTNING_HANDS_3;
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND][0].Count				= FrameSize[EFFECTSPRITETYPE_LIGHTNING_HANDS_3];
	(*g_pActionInfoTable)[SKILL_LIGHTNING_HAND][0].SetResultTime();
	

	// SKILL_SWORD_WAVE
	(*g_pActionInfoTable)[SKILL_SWORD_WAVE].Set("SKILL_SWORD_WAVE", ACTION_SLAYER_SWORD_2, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_SWORD_2]);
	(*g_pActionInfoTable)[SKILL_SWORD_WAVE].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_SWORD_WAVE].SetStartFrameAll( 2 );
	(*g_pActionInfoTable)[SKILL_SWORD_WAVE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_SWORD_WAVE].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_SWORD_WAVE].Init( 3 );		
	(*g_pActionInfoTable)[SKILL_SWORD_WAVE][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_SWORD_WAVE][0].EffectSpriteType		= EFFECTSPRITETYPE_SWORD_WAVE_1;
	(*g_pActionInfoTable)[SKILL_SWORD_WAVE][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_SWORD_WAVE][0].Count				= FrameSize[EFFECTSPRITETYPE_SWORD_WAVE_1];
	(*g_pActionInfoTable)[SKILL_SWORD_WAVE][0].SoundID				= SOUND_SLAYER_SWORD_SW;
	(*g_pActionInfoTable)[SKILL_SWORD_WAVE][0].LinkCount			= 6;
	(*g_pActionInfoTable)[SKILL_SWORD_WAVE][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_SWORD_WAVE][1].EffectSpriteType		= EFFECTSPRITETYPE_SWORD_WAVE_2;
	(*g_pActionInfoTable)[SKILL_SWORD_WAVE][1].Step					= 25;
	(*g_pActionInfoTable)[SKILL_SWORD_WAVE][1].Count				= FrameSize[EFFECTSPRITETYPE_SWORD_WAVE_2];
	(*g_pActionInfoTable)[SKILL_SWORD_WAVE][1].LinkCount			= 6;
	(*g_pActionInfoTable)[SKILL_SWORD_WAVE][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_SWORD_WAVE][2].EffectSpriteType		= EFFECTSPRITETYPE_SWORD_WAVE_3;
	(*g_pActionInfoTable)[SKILL_SWORD_WAVE][2].Step					= 25;
	(*g_pActionInfoTable)[SKILL_SWORD_WAVE][2].Count				= FrameSize[EFFECTSPRITETYPE_SWORD_WAVE_3];
	(*g_pActionInfoTable)[SKILL_SWORD_WAVE][2].SetResultTime();
	
	// SKILL_FIVE_STORM_CRASH
	(*g_pActionInfoTable)[SKILL_FIVE_STORM_CRASH].Set("SKILL_FIVE_STORM_CRASH", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_FIVE_STORM_CRASH].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_FIVE_STORM_CRASH].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_FIVE_STORM_CRASH].SetSoundID( SOUND_SLAYER_CHARGE );

	// SKILL_CRITICAL_THRUST
	/*
	(*g_pActionInfoTable)[SKILL_CRITICAL_THRUST].Set("SKILL_CRITICAL_THRUST", ACTION_SLAYER_SWORD, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD]);
	(*g_pActionInfoTable)[SKILL_CRITICAL_THRUST].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_CRITICAL_THRUST].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_CRITICAL_THRUST].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CRITICAL_THRUST].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CRITICAL_THRUST][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CRITICAL_THRUST][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[SKILL_CRITICAL_THRUST][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CRITICAL_THRUST][0].Count			= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[SKILL_CRITICAL_THRUST][0].SoundID			= 0;
	*/

	// SKILL_DRAGON_RISING
	(*g_pActionInfoTable)[SKILL_DRAGON_RISING].Set("SKILL_DRAGON_RISING", ACTION_SLAYER_SWORD, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_SWORD]);
	(*g_pActionInfoTable)[SKILL_DRAGON_RISING].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_DRAGON_RISING].SetStartFrameAll( 5 );
	(*g_pActionInfoTable)[SKILL_DRAGON_RISING].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_DRAGON_RISING].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_DRAGON_RISING].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_DRAGON_RISING][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_DRAGON_RISING][0].EffectSpriteType	= EFFECTSPRITETYPE_LIGHTNING_1;
	(*g_pActionInfoTable)[SKILL_DRAGON_RISING][0].Step				= 20;
	(*g_pActionInfoTable)[SKILL_DRAGON_RISING][0].Count				= FrameSize[EFFECTSPRITETYPE_LIGHTNING_1];
	(*g_pActionInfoTable)[SKILL_DRAGON_RISING][0].LinkCount			= 3;
	(*g_pActionInfoTable)[SKILL_DRAGON_RISING][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_DRAGON_RISING][1].EffectSpriteType	= EFFECTSPRITETYPE_LIGHTNING_2;
	(*g_pActionInfoTable)[SKILL_DRAGON_RISING][1].Step				= 20;
	(*g_pActionInfoTable)[SKILL_DRAGON_RISING][1].Count			= FrameSize[EFFECTSPRITETYPE_LIGHTNING_2];
	(*g_pActionInfoTable)[SKILL_DRAGON_RISING][1].SetResultTime();
	
	
	// SKILL_HEAVENS_POWER
	/*
	(*g_pActionInfoTable)[SKILL_HEAVENS_POWER].Set("SKILL_HEAVENS_POWER", ACTION_SLAYER_SWORD, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD]);
	(*g_pActionInfoTable)[SKILL_HEAVENS_POWER].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_HEAVENS_POWER].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_HEAVENS_POWER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_HEAVENS_POWER].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_HEAVENS_POWER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_HEAVENS_POWER][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[SKILL_HEAVENS_POWER][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_HEAVENS_POWER][0].Count			= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[SKILL_HEAVENS_POWER][0].SoundID			= 0;
	*/

	// SKILL_HEAVENS_SWORD
	(*g_pActionInfoTable)[SKILL_HEAVENS_SWORD].Set("SKILL_HEAVENS_SWORD", ACTION_MAGIC, EFFECTSPRITETYPE_HPBOOST_CASTING, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_HEAVENS_SWORD].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_HEAVENS_SWORD].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_HEAVENS_SWORD].SetSoundID( SOUND_SLAYER_CHARGE );

	
	//-------------------------------------------------------------
	//
	//                          도 계열
	//
	//-------------------------------------------------------------
	
    // SKILL_SINGLE_BLOW
	(*g_pActionInfoTable)[SKILL_SINGLE_BLOW].Set("SKILL_SINGLE_BLOW", ACTION_SLAYER_BLADE, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_BLADE]);
	(*g_pActionInfoTable)[SKILL_SINGLE_BLOW].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_SINGLE_BLOW].SetStartFrameAll( 9 );	// 기술 effect가 시작되는 frame
	(*g_pActionInfoTable)[SKILL_SINGLE_BLOW].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_SINGLE_BLOW].SetActionStepCnt(2) ;
	(*g_pActionInfoTable)[SKILL_SINGLE_BLOW].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_SINGLE_BLOW][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_SINGLE_BLOW][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_SINGLE_BLOW ; // chyaya 2006.02.17 EFFECTSPRITETYPE_SINGLE_BLOW;
	(*g_pActionInfoTable)[SKILL_SINGLE_BLOW][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SINGLE_BLOW][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_SINGLE_BLOW] ; //EFFECTSPRITETYPE_SINGLE_BLOW];
	(*g_pActionInfoTable)[SKILL_SINGLE_BLOW][0].SoundID				= SOUND_SLAYER_BLADE_SB;
	(*g_pActionInfoTable)[SKILL_SINGLE_BLOW][0].SetResultTime();

    // SKILL_TWIN_BREAK
	/*
	(*g_pActionInfoTable)[SKILL_TWIN_BREAK].Set("SKILL_TWIN_BREAK", ACTION_SLAYER_BLADE_2, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_BLADE_2]);
	(*g_pActionInfoTable)[SKILL_TWIN_BREAK].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_TWIN_BREAK].SetStartFrameAll( 9 );	// 기술 effect가 시작되는 frame
	(*g_pActionInfoTable)[SKILL_TWIN_BREAK].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TWIN_BREAK].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_TWIN_BREAK].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_TWIN_BREAK][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_TWIN_BREAK][0].EffectSpriteType	= EFFECTSPRITETYPE_TWIN_BREAK;
	(*g_pActionInfoTable)[SKILL_TWIN_BREAK][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TWIN_BREAK][0].Count			= FrameSize[EFFECTSPRITETYPE_TWIN_BREAK];
	(*g_pActionInfoTable)[SKILL_TWIN_BREAK][0].SoundID			= SOUND_SLAYER_BLADE_TB;
	*/

    // SKILL_TRIPLE_BREAK
	(*g_pActionInfoTable)[SKILL_TRIPLE_BREAK].Set("SKILL_TRIPLE_BREAK", ACTION_SLAYER_BLADE_2, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_BLADE_2]);
	(*g_pActionInfoTable)[SKILL_TRIPLE_BREAK].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_TRIPLE_BREAK].SetStartFrameAll( 9 );	// 기술 effect가 시작되는 frame
	(*g_pActionInfoTable)[SKILL_TRIPLE_BREAK].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TRIPLE_BREAK].SetActionStepCnt(2) ;
	(*g_pActionInfoTable)[SKILL_TRIPLE_BREAK].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_TRIPLE_BREAK][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_TRIPLE_BREAK][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_TRIPLE_BREAK  ; // chyaya 2006.02.17 EFFECTSPRITETYPE_TRIPLE_BREAK;
	(*g_pActionInfoTable)[SKILL_TRIPLE_BREAK][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TRIPLE_BREAK][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_TRIPLE_BREAK ] ; // EFFECTSPRITETYPE_TRIPLE_BREAK];
	(*g_pActionInfoTable)[SKILL_TRIPLE_BREAK][0].SoundID			= SOUND_SLAYER_BLADE_TRB;
	(*g_pActionInfoTable)[SKILL_TRIPLE_BREAK][0].SetResultTime();
	
    // SKILL_SPIRAL_SLAY
	(*g_pActionInfoTable)[SKILL_SPIRAL_SLAY].Set("SKILL_SPIRAL_SLAY", ACTION_SLAYER_BLADE_2, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_BLADE_2]);
	(*g_pActionInfoTable)[SKILL_SPIRAL_SLAY].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_SPIRAL_SLAY].SetStartFrameAll( 7 );	// 기술 effect가 시작되는 frame
	(*g_pActionInfoTable)[SKILL_SPIRAL_SLAY].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_SPIRAL_SLAY].SetActionStepCnt(2) ;
	(*g_pActionInfoTable)[SKILL_SPIRAL_SLAY].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_SPIRAL_SLAY][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_SPIRAL_SLAY][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_SPIRAL_SLAY ; // 2006.02.17 chyaya EFFECTSPRITETYPE_SPIRAL_SLAY;
	(*g_pActionInfoTable)[SKILL_SPIRAL_SLAY][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SPIRAL_SLAY][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_SPIRAL_SLAY] ; // EFFECTSPRITETYPE_SPIRAL_SLAY];
	(*g_pActionInfoTable)[SKILL_SPIRAL_SLAY][0].SoundID				= SOUND_SLAYER_BLADE_SS;
	(*g_pActionInfoTable)[SKILL_SPIRAL_SLAY][0].SetResultTime();

    // SKILL_WILD_SMASH
#ifdef __EXPO_CLIENT__
	(*g_pActionInfoTable)[SKILL_WILD_SMASH].SetExpoSkill();
#endif
	(*g_pActionInfoTable)[SKILL_WILD_SMASH].Set("SKILL_WILD_SMASH", ACTION_SLAYER_BLADE_2, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_BLADE_2]);
	(*g_pActionInfoTable)[SKILL_WILD_SMASH].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_WILD_SMASH].SetStartFrameAll( 9 );	// 기술 effect가 시작되는 frame
	(*g_pActionInfoTable)[SKILL_WILD_SMASH].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_WILD_SMASH].SetActionStepCnt(2) ;
	(*g_pActionInfoTable)[SKILL_WILD_SMASH].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_WILD_SMASH][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_WILD_SMASH][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_WILD_SMASH ; // 2006.02.17 chyayaEFFECTSPRITETYPE_WILD_SMASH;
	(*g_pActionInfoTable)[SKILL_WILD_SMASH][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_WILD_SMASH][0].Count			= FrameSize[EFFECTSPRITETYPE_NEW_WILD_SMASH] ; //EFFECTSPRITETYPE_WILD_SMASH];
	(*g_pActionInfoTable)[SKILL_WILD_SMASH][0].SoundID			= SOUND_SLAYER_BLADE_WS;
	(*g_pActionInfoTable)[SKILL_WILD_SMASH][0].SetResultTime();

	(*g_pActionInfoTable)[SKILL_GHOST_BLADE].Set("SKILL_GHOST_BLADE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_GHOST_BLADE].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_GHOST_BLADE].SetSoundID( SOUNDID_NULL );
//	(*g_pActionInfoTable)[SKILL_GHOST_BLADE].SetStartFrameAll( 9 );	// 기술 effect가 시작되는 frame	

	
	// SKILL_CHARGING_POWER
	(*g_pActionInfoTable)[SKILL_CHARGING_POWER].Set("SKILL_CHARGING_POWER", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_CHARGING_POWER].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_CHARGING_POWER].SetStartWithCasting();	
	(*g_pActionInfoTable)[SKILL_CHARGING_POWER].SetSoundID( SOUND_SLAYER_CHARGE );
	(*g_pActionInfoTable)[SKILL_CHARGING_POWER].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CHARGING_POWER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CHARGING_POWER][0].EffectSpriteType	= EFFECTSPRITETYPE_POTENTIAL;
	(*g_pActionInfoTable)[SKILL_CHARGING_POWER][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CHARGING_POWER][0].Count				= FrameSize[EFFECTSPRITETYPE_POTENTIAL];
	(*g_pActionInfoTable)[SKILL_CHARGING_POWER][0].SoundID				= 1;
	(*g_pActionInfoTable)[SKILL_CHARGING_POWER][0].SetResultTime();
	
	
    // SKILL_ARMOR_CRASH
	/*
	(*g_pActionInfoTable)[SKILL_ARMOR_CRASH].Set("SKILL_ARMOR_CRASH", ACTION_SLAYER_BLADE, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_BLADE]);
	(*g_pActionInfoTable)[SKILL_ARMOR_CRASH].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_ARMOR_CRASH].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_ARMOR_CRASH].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_ARMOR_CRASH].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_ARMOR_CRASH].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_ARMOR_CRASH][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_ARMOR_CRASH][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[SKILL_ARMOR_CRASH][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_ARMOR_CRASH][0].Count				= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[SKILL_ARMOR_CRASH][0].SoundID			= 1;
	*/

	// SKILL_REQUIEM
	/*
	(*g_pActionInfoTable)[SKILL_REQUIEM].Set("SKILL_REQUIEM", ACTION_SLAYER_BLADE, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_BLADE]);
	(*g_pActionInfoTable)[SKILL_REQUIEM].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_REQUIEM].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_REQUIEM].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_REQUIEM].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_REQUIEM].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_REQUIEM][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[SKILL_REQUIEM][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[SKILL_REQUIEM][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_REQUIEM][0].Count			= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[SKILL_REQUIEM][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_REQUIEM][1].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[SKILL_REQUIEM][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_REQUIEM][1].Count			= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[SKILL_REQUIEM][1].SoundID			= 1;
	*/

    // SKILL_FINAL_BLOW,        // 심도	
	/*
	(*g_pActionInfoTable)[SKILL_FINAL_BLOW].Set("SKILL_FINAL_BLOW", ACTION_SLAYER_BLADE, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_BLADE]);
	(*g_pActionInfoTable)[SKILL_FINAL_BLOW].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_FINAL_BLOW].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_FINAL_BLOW].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_FINAL_BLOW].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_FINAL_BLOW].Init( 3 );
	(*g_pActionInfoTable)[SKILL_FINAL_BLOW][0].EffectGeneratorID	= EFFECTGENERATORID_RISING;
	(*g_pActionInfoTable)[SKILL_FINAL_BLOW][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[SKILL_FINAL_BLOW][0].Step				= 50;
	(*g_pActionInfoTable)[SKILL_FINAL_BLOW][0].Count				= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[SKILL_FINAL_BLOW][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[SKILL_FINAL_BLOW][1].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[SKILL_FINAL_BLOW][1].Step				= 80;
	(*g_pActionInfoTable)[SKILL_FINAL_BLOW][1].Count				= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[SKILL_FINAL_BLOW][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_FINAL_BLOW][2].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[SKILL_FINAL_BLOW][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_FINAL_BLOW][2].Count				= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[SKILL_FINAL_BLOW][2].SoundID			= 1;
	*/

	// SKILL_ENORMOUS_POWER
	/*
	(*g_pActionInfoTable)[SKILL_ENORMOUS_POWER].Set("SKILL_ENORMOUS_POWER", ACTION_SLAYER_BLADE, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_BLADE]);
	(*g_pActionInfoTable)[SKILL_ENORMOUS_POWER].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_ENORMOUS_POWER].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_ENORMOUS_POWER].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_ENORMOUS_POWER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_ENORMOUS_POWER].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_ENORMOUS_POWER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_ENORMOUS_POWER][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[SKILL_ENORMOUS_POWER][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_ENORMOUS_POWER][0].Count				= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[SKILL_ENORMOUS_POWER][0].SoundID				= 1;
	*/

	// SKILL_POTENTIAL_EXPLOSION
	(*g_pActionInfoTable)[SKILL_POTENTIAL_EXPLOSION].Set("SKILL_POTENTIAL_EXPLOSION", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_POTENTIAL_EXPLOSION].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_POTENTIAL_EXPLOSION].SetStartWithCasting();	
	(*g_pActionInfoTable)[SKILL_POTENTIAL_EXPLOSION].SetSoundID( SOUND_SLAYER_CHARGE );
	(*g_pActionInfoTable)[SKILL_POTENTIAL_EXPLOSION].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_POTENTIAL_EXPLOSION][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_POTENTIAL_EXPLOSION][0].EffectSpriteType	= EFFECTSPRITETYPE_POTENTIAL;
	(*g_pActionInfoTable)[SKILL_POTENTIAL_EXPLOSION][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_POTENTIAL_EXPLOSION][0].Count				= FrameSize[EFFECTSPRITETYPE_POTENTIAL];
	(*g_pActionInfoTable)[SKILL_POTENTIAL_EXPLOSION][0].SoundID				= 1;
	(*g_pActionInfoTable)[SKILL_POTENTIAL_EXPLOSION][0].SetResultTime();

	// SKILL_SHADOW_WALK
	(*g_pActionInfoTable)[SKILL_SHADOW_WALK].Set("SKILL_SHADOW_WALK", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, 10);//ActionDelay[ACTION_SLAYER_SWORD]);
	(*g_pActionInfoTable)[SKILL_SHADOW_WALK].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_SHADOW_WALK].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_SHADOW_WALK].SetSoundID( SOUNDID_NULL );
	/*
	(*g_pActionInfoTable)[SKILL_SHADOW_WALK].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_SHADOW_WALK][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_SHADOW_WALK][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[SKILL_SHADOW_WALK][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SHADOW_WALK][0].Count			= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	*/
	
	// SKILL_MULTI_HANDS
	/*
	(*g_pActionInfoTable)[SKILL_MULTI_HANDS].Set("SKILL_MULTI_HANDS", ACTION_SLAYER_BLADE, EFFECTSPRITETYPE_LIGHT_2, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_BLADE]);
	(*g_pActionInfoTable)[SKILL_MULTI_HANDS].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_MULTI_HANDS].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_MULTI_HANDS].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_MULTI_HANDS].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_MULTI_HANDS].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_MULTI_HANDS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_MULTI_HANDS][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[SKILL_MULTI_HANDS][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_MULTI_HANDS][0].Count				= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[SKILL_MULTI_HANDS][0].SoundID				= 1;
	*/

	// SKILL_TORNADO_SEVER
	(*g_pActionInfoTable)[SKILL_TORNADO_SEVER].Set("SKILL_TORNADO_SEVER", ACTION_SLAYER_BLADE, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_BLADE]);
	(*g_pActionInfoTable)[SKILL_TORNADO_SEVER].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_TORNADO_SEVER].SetActionStepCnt(2) ;
	(*g_pActionInfoTable)[SKILL_TORNADO_SEVER].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_TORNADO_SEVER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TORNADO_SEVER].SetActionStepCnt(2) ;
	(*g_pActionInfoTable)[SKILL_TORNADO_SEVER].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_TORNADO_SEVER][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_TORNADO_SEVER][0].EffectSpriteType	= EFFECTSPRITETYPE_TORNADO_SEVER_2;
	(*g_pActionInfoTable)[SKILL_TORNADO_SEVER][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TORNADO_SEVER][0].SoundID			= SOUND_SLAYER_BLADE_TS;
	(*g_pActionInfoTable)[SKILL_TORNADO_SEVER][0].Count				= FrameSize[EFFECTSPRITETYPE_TORNADO_SEVER_2];
	(*g_pActionInfoTable)[SKILL_TORNADO_SEVER][0].LinkCount			= 5;
	(*g_pActionInfoTable)[SKILL_TORNADO_SEVER][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_TORNADO_SEVER][1].EffectSpriteType	= EFFECTSPRITETYPE_TORNADO_SEVER_1;
	(*g_pActionInfoTable)[SKILL_TORNADO_SEVER][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TORNADO_SEVER][1].Count				= FrameSize[EFFECTSPRITETYPE_TORNADO_SEVER_1];	
	(*g_pActionInfoTable)[SKILL_TORNADO_SEVER][1].SetResultTime();
	(*g_pActionInfoTable)[SKILL_TORNADO_SEVER].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_TORNADO_SEVER );	// 맞는 결과를 표현한다.	

	// SKILL_SOUL_SHOCK
	(*g_pActionInfoTable)[SKILL_SOUL_SHOCK].Set("SKILL_SOUL_SHOCK", ACTION_MAGIC, EFFECTSPRITETYPE_POTENTIAL, 8, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_SOUL_SHOCK].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_SOUL_SHOCK].SetStartFrameAll( 14 );
	(*g_pActionInfoTable)[SKILL_SOUL_SHOCK].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_SOUL_SHOCK].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_SOUL_SHOCK][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_SOUL_SHOCK][0].EffectSpriteType	= EFFECTSPRITETYPE_TORNADO_SEVER_1;
	(*g_pActionInfoTable)[SKILL_SOUL_SHOCK][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SOUL_SHOCK][0].Count				= FrameSize[EFFECTSPRITETYPE_TORNADO_SEVER_1];
	(*g_pActionInfoTable)[SKILL_SOUL_SHOCK][0].SoundID				= 1;
	(*g_pActionInfoTable)[SKILL_SOUL_SHOCK][0].SetResultTime();

	// SKILL_BLADE_WAVE
	/*
	(*g_pActionInfoTable)[SKILL_BLADE_WAVE].Set("SKILL_BLADE_WAVE", ACTION_SLAYER_BLADE, EFFECTSPRITETYPE_LIGHT_2, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_BLADE]);
	(*g_pActionInfoTable)[SKILL_BLADE_WAVE].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_BLADE_WAVE].SetActionStepCnt(2) ;
	(*g_pActionInfoTable)[SKILL_BLADE_WAVE].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_BLADE_WAVE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_BLADE_WAVE].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_BLADE_WAVE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_BLADE_WAVE][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[SKILL_BLADE_WAVE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_BLADE_WAVE][0].Count				= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[SKILL_BLADE_WAVE][0].SoundID				= 1;
	*/

	// SKILL_ARMAGEDDON_SLASHER
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER].Set("SKILL_ARMAGEDDON_SLASHER", ACTION_SLAYER_BLADE, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_BLADE]);
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER].SetActionStepCnt(2) ;
	//(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER].SetActionStepCnt(2) ;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER].Init( 10 );		
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][0].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][0].EffectSpriteType	= EFFECTSPRITETYPE_EARTHQUAKE_1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][0].Step				= 28;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][0].Count				= FrameSize[EFFECTSPRITETYPE_EARTHQUAKE_1];
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][0].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][0].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][1].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][1].EffectSpriteType	= EFFECTSPRITETYPE_EARTHQUAKE_1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][1].Step				= 28;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][1].Count				= FrameSize[EFFECTSPRITETYPE_EARTHQUAKE_1];
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][1].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][2].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][2].EffectSpriteType	= EFFECTSPRITETYPE_EARTHQUAKE_1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][2].Step				= 28;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][2].Count				= FrameSize[EFFECTSPRITETYPE_EARTHQUAKE_1];
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][2].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][2].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][3].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][3].EffectSpriteType	= EFFECTSPRITETYPE_EARTHQUAKE_1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][3].Step				= 28;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][3].Count				= FrameSize[EFFECTSPRITETYPE_EARTHQUAKE_1];
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][3].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][3].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][4].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][4].EffectSpriteType	= EFFECTSPRITETYPE_EARTHQUAKE_1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][4].Step				= 28;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][4].Count				= FrameSize[EFFECTSPRITETYPE_EARTHQUAKE_1];
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][4].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][4].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][5].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][5].EffectSpriteType	= EFFECTSPRITETYPE_EARTHQUAKE_1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][5].Step				= 28;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][5].Count				= FrameSize[EFFECTSPRITETYPE_EARTHQUAKE_1];
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][5].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][5].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][6].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][6].EffectSpriteType	= EFFECTSPRITETYPE_EARTHQUAKE_1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][6].Step				= 28;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][6].Count				= FrameSize[EFFECTSPRITETYPE_EARTHQUAKE_1];
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][6].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][6].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][7].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][7].EffectSpriteType	= EFFECTSPRITETYPE_EARTHQUAKE_1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][7].Step				= 28;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][7].Count				= FrameSize[EFFECTSPRITETYPE_EARTHQUAKE_1];
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][7].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][7].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][8].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][8].EffectSpriteType	= EFFECTSPRITETYPE_EARTHQUAKE_1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][8].Step				= 28;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][8].Count				= FrameSize[EFFECTSPRITETYPE_EARTHQUAKE_1];
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][8].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][8].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][9].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][9].EffectSpriteType	= EFFECTSPRITETYPE_EARTHQUAKE_1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][9].Step				= 28;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][9].Count				= FrameSize[EFFECTSPRITETYPE_EARTHQUAKE_1];
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][9].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][9].SetDelayNode();
	/*
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][10].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][10].EffectSpriteType	= EFFECTSPRITETYPE_ARMAGEDDON_SLASHER_1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][10].Step				= 28;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][10].Count				= FrameSize[EFFECTSPRITETYPE_ARMAGEDDON_SLASHER_1];
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][10].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][10].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][11].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][11].EffectSpriteType	= EFFECTSPRITETYPE_ARMAGEDDON_SLASHER_1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][11].Step				= 28;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][11].Count				= FrameSize[EFFECTSPRITETYPE_ARMAGEDDON_SLASHER_1];
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][11].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][11].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][12].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][12].EffectSpriteType	= EFFECTSPRITETYPE_ARMAGEDDON_SLASHER_1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][12].Step				= 28;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][12].Count				= FrameSize[EFFECTSPRITETYPE_ARMAGEDDON_SLASHER_1];
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][12].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][12].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][13].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][13].EffectSpriteType	= EFFECTSPRITETYPE_ARMAGEDDON_SLASHER_1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][13].Step				= 28;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][13].Count				= FrameSize[EFFECTSPRITETYPE_ARMAGEDDON_SLASHER_1];
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][13].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_ARMAGEDDON_SLASHER][13].SetDelayNode();
	*/

	// SKILL_IMMORTAL_POWER
	/*
	(*g_pActionInfoTable)[SKILL_IMMORTAL_POWER].Set("SKILL_IMMORTAL_POWER", ACTION_SLAYER_BLADE, EFFECTSPRITETYPE_LIGHT_2, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_BLADE]);
	(*g_pActionInfoTable)[SKILL_IMMORTAL_POWER].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_IMMORTAL_POWER].SetActionStepCnt(2) ;
	(*g_pActionInfoTable)[SKILL_IMMORTAL_POWER].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_IMMORTAL_POWER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_IMMORTAL_POWER].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_IMMORTAL_POWER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_IMMORTAL_POWER][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[SKILL_IMMORTAL_POWER][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_IMMORTAL_POWER][0].Count				= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[SKILL_IMMORTAL_POWER][0].SoundID				= 1;
	*/

	// SKILL_SAINT_BLADE
	(*g_pActionInfoTable)[SKILL_SAINT_BLADE].Set("SKILL_SAINT_BLADE", ACTION_SLAYER_BLADE, EFFECTSPRITETYPE_LIGHT_2, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_BLADE]);
	(*g_pActionInfoTable)[SKILL_SAINT_BLADE].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_SAINT_BLADE].SetActionStepCnt(2) ;
	(*g_pActionInfoTable)[SKILL_SAINT_BLADE].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_SAINT_BLADE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_SAINT_BLADE].SetActionStepCnt(2) ;
	(*g_pActionInfoTable)[SKILL_SAINT_BLADE].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_SAINT_BLADE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_SAINT_BLADE][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[SKILL_SAINT_BLADE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SAINT_BLADE][0].Count				= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[SKILL_SAINT_BLADE][0].SoundID				= 1;
	(*g_pActionInfoTable)[SKILL_SAINT_BLADE][0].SetResultTime();
	
	
	//-------------------------------------------------------------
	//
	//                      Gun계열
	//
	//-------------------------------------------------------------
	// SKILL_SNIPPING
	/*
	(*g_pActionInfoTable)[SKILL_SNIPPING].Set("SKILL_SNIPPING", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[SKILL_SNIPPING].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_SNIPPING].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_SNIPPING].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_SNIPPING].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_SNIPPING].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_SNIPPING].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_SNIPPING].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_SNIPPING].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용
	(*g_pActionInfoTable)[SKILL_SNIPPING].SetSoundID( SOUNDID_NULL );		// 의미 없다.
	*/

	// SKILL_SHARP_SHOOTING
	/*
	(*g_pActionInfoTable)[SKILL_SHARP_SHOOTING].Set("SKILL_SHARP_SHOOTING", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[SKILL_SHARP_SHOOTING].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_SHARP_SHOOTING].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_SHARP_SHOOTING].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_SHARP_SHOOTING].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_SHARP_SHOOTING].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_SHARP_SHOOTING].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_SHARP_SHOOTING].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_SHARP_SHOOTING].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용
	(*g_pActionInfoTable)[SKILL_SHARP_SHOOTING].SetSoundID( SOUNDID_NULL );
	*/

	// SKILL_FAST_RELOAD
	(*g_pActionInfoTable)[SKILL_FAST_RELOAD].Set("SKILL_FAST_RELOAD", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[SKILL_FAST_RELOAD].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_FAST_RELOAD].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_FAST_RELOAD].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_FAST_RELOAD].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_FAST_RELOAD].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_FAST_RELOAD].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_FAST_RELOAD].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_FAST_RELOAD].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용
	(*g_pActionInfoTable)[SKILL_FAST_RELOAD].SetSoundID( SOUNDID_NULL );

	// SKILL_SMG_MASTERY
	(*g_pActionInfoTable)[SKILL_SMG_MASTERY].Set("SKILL_SMG_MASTERY", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[SKILL_SMG_MASTERY].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_SMG_MASTERY].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_SMG_MASTERY].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_SMG_MASTERY].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_SMG_MASTERY].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_SMG_MASTERY].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_SMG_MASTERY].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_SMG_MASTERY].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용
	(*g_pActionInfoTable)[SKILL_SMG_MASTERY].SetSoundID( SOUNDID_NULL );

	// SKILL_AR_MASTERY
	(*g_pActionInfoTable)[SKILL_AR_MASTERY].Set("SKILL_AR_MASTERY", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[SKILL_AR_MASTERY].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_AR_MASTERY].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_AR_MASTERY].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_AR_MASTERY].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_AR_MASTERY].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_AR_MASTERY].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_AR_MASTERY].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_AR_MASTERY].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용
	(*g_pActionInfoTable)[SKILL_AR_MASTERY].SetSoundID( SOUNDID_NULL );

	// SKILL_SR_MASTERY
	(*g_pActionInfoTable)[SKILL_SR_MASTERY].Set("SKILL_SR_MASTERY", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[SKILL_SR_MASTERY].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_SR_MASTERY].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_SR_MASTERY].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_SR_MASTERY].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_SR_MASTERY].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_SR_MASTERY].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_SR_MASTERY].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_SR_MASTERY].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용
	(*g_pActionInfoTable)[SKILL_SR_MASTERY].SetSoundID( SOUNDID_NULL );

	// SKILL_SG_MASTERY
	(*g_pActionInfoTable)[SKILL_SG_MASTERY].Set("SKILL_SG_MASTERY", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[SKILL_SG_MASTERY].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_SG_MASTERY].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_SG_MASTERY].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_SG_MASTERY].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_SG_MASTERY].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_SG_MASTERY].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_SG_MASTERY].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_SG_MASTERY].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용
	(*g_pActionInfoTable)[SKILL_SG_MASTERY].SetSoundID( SOUNDID_NULL );

	// SKILL_QUICK_FIRE
	(*g_pActionInfoTable)[SKILL_QUICK_FIRE].Set("SKILL_QUICK_FIRE", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_GUN_SR_MALE, 5, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[SKILL_QUICK_FIRE].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_QUICK_FIRE].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_QUICK_FIRE].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_QUICK_FIRE].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_QUICK_FIRE].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_QUICK_FIRE].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_QUICK_FIRE].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_QUICK_FIRE].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용	
	(*g_pActionInfoTable)[SKILL_QUICK_FIRE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_QUICK_FIRE].SetCastingStartFrameAll( 14 );	// 불꽃이 붙는 frame
	(*g_pActionInfoTable)[SKILL_QUICK_FIRE].SetCastingFramesAll( 2 );
	(*g_pActionInfoTable)[SKILL_QUICK_FIRE].UseRepeatFrame();	
	//(*g_pActionInfoTable)[SKILL_QUICK_FIRE].SetRepeatLimit( 2 );

	// SKILL_DOUBLE_SHOT
	(*g_pActionInfoTable)[SKILL_DOUBLE_SHOT].Set("SKILL_DOUBLE_SHOT", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_GUN_SR_MALE, 5, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[SKILL_DOUBLE_SHOT].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_DOUBLE_SHOT].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_DOUBLE_SHOT].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_DOUBLE_SHOT].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_DOUBLE_SHOT].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_DOUBLE_SHOT].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_DOUBLE_SHOT].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_DOUBLE_SHOT].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용	
	(*g_pActionInfoTable)[SKILL_DOUBLE_SHOT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_DOUBLE_SHOT].SetCastingStartFrameAll( 14 );	// 불꽃이 붙는 frame
	(*g_pActionInfoTable)[SKILL_DOUBLE_SHOT].SetCastingFramesAll( 2 );
	(*g_pActionInfoTable)[SKILL_DOUBLE_SHOT].UseRepeatFrame();	
	(*g_pActionInfoTable)[SKILL_DOUBLE_SHOT].SetRepeatLimit( 2 );

	// SKILL_TRIPLE_SHOT
	(*g_pActionInfoTable)[SKILL_TRIPLE_SHOT].Set("SKILL_TRIPLE_FIRE", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_GUN_SR_MALE, 5, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[SKILL_TRIPLE_SHOT].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_TRIPLE_SHOT].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_TRIPLE_SHOT].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_TRIPLE_SHOT].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_TRIPLE_SHOT].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_TRIPLE_SHOT].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_TRIPLE_SHOT].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_TRIPLE_SHOT].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용	
	(*g_pActionInfoTable)[SKILL_TRIPLE_SHOT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TRIPLE_SHOT].SetCastingStartFrameAll( 14 );	// 불꽃이 붙는 frame
	(*g_pActionInfoTable)[SKILL_TRIPLE_SHOT].SetCastingFramesAll( 2 );
	(*g_pActionInfoTable)[SKILL_TRIPLE_SHOT].UseRepeatFrame();	
	(*g_pActionInfoTable)[SKILL_TRIPLE_SHOT].SetRepeatLimit( 3 );

	// SKILL_MULTI_SHOT
	(*g_pActionInfoTable)[SKILL_MULTI_SHOT].Set("SKILL_MULTI_SHOT", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_GUN_SR_MALE, 5, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_MULTI_SHOT].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_MULTI_SHOT].SetStartFrame( 0, 7 );			// slow
	(*g_pActionInfoTable)[SKILL_MULTI_SHOT].SetStartFrame( 1, 7 );			// normal
	(*g_pActionInfoTable)[SKILL_MULTI_SHOT].SetStartFrame( 2, 5 );			// fast
	(*g_pActionInfoTable)[SKILL_MULTI_SHOT].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_MULTI_SHOT].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_MULTI_SHOT].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_MULTI_SHOT].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_MULTI_SHOT].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_MULTI_SHOT].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_MULTI_SHOT].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용
	(*g_pActionInfoTable)[SKILL_MULTI_SHOT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_MULTI_SHOT].SetCastingStartFrameAll( 14 );	// 불꽃이 붙는 frame
	(*g_pActionInfoTable)[SKILL_MULTI_SHOT].SetCastingFramesAll( 2 );
	(*g_pActionInfoTable)[SKILL_MULTI_SHOT].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_MULTI_SHOT );	// 맞는 결과를 표현한다.	
	(*g_pActionInfoTable)[SKILL_MULTI_SHOT].Init( 1 );
	(*g_pActionInfoTable)[SKILL_MULTI_SHOT][0].EffectGeneratorID	= EFFECTGENERATORID_AROUND_ZONE;
	(*g_pActionInfoTable)[SKILL_MULTI_SHOT][0].EffectSpriteType		= EFFECTSPRITETYPE_GUN_DUST_1;
	(*g_pActionInfoTable)[SKILL_MULTI_SHOT][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_MULTI_SHOT][0].Count				= FrameSize[EFFECTSPRITETYPE_GUN_DUST_1];
	
	// SKILL_BULLET_OF_LIGHT
	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].Set("SKILL_BULLET_OF_LIGHT", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_GUN_SR_MALE, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetStartFrame( 0, 7 );			// slow
	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetStartFrame( 1, 7 );			// normal
	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetStartFrame( 2, 5 );			// fast
	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
 	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용
//	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetCastingStartFrame( 0, 8 );	// slow
//	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetCastingStartFrame( 1, 7 );	// normal
//	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetCastingStartFrame( 2, 6 );	// fast
//	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetCastingFrames( 0, 2 );		// slow
//	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetCastingFrames( 1, 2 );		// normal
//	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetCastingFrames( 2, 2 );		// fast
//	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetRepeatFrame( 0, 10, 6 );		// slow
//	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetRepeatFrame( 1, 8, 6 );		// normal
//	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetRepeatFrame( 2, 6, 6 );		// fast
	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetCastingStartFrameAll( 14 );	// 불꽃이 붙는 frame
	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetCastingFramesAll( 2 );
	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_BULLET_OF_LIGHT );	// 맞는 결과를 표현한다.	
	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].UseRepeatFrame();	
	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].SetRepeatLimit( 4 );
	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT].Init( 1 );
	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT][0].EffectSpriteType		= EFFECTSPRITETYPE_BULLET_OF_LIGHT_START_1;
	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT][0].Count				= FrameSize[EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_1];
//	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT][0].LinkCount				= 0;
//	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT][1].EffectSpriteType		= EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_1;
//	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT][1].Step					= 25;
//	(*g_pActionInfoTable)[SKILL_BULLET_OF_LIGHT][1].Count				= FrameSize[EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_1];
	
	// RESULT_SKILL_BULLET_OF_LIGHT
	(*g_pActionInfoTable)[RESULT_SKILL_BULLET_OF_LIGHT].Set("RESULT_SKILL_BULLET_OF_LIGHT", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_BULLET_OF_LIGHT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_BULLET_OF_LIGHT].Init(1);
	(*g_pActionInfoTable)[RESULT_SKILL_BULLET_OF_LIGHT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_BULLET_OF_LIGHT][0].EffectSpriteType		= EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_1;
	(*g_pActionInfoTable)[RESULT_SKILL_BULLET_OF_LIGHT][0].Step					= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_BULLET_OF_LIGHT][0].Count				= FrameSize[EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_1];
	
	// SKILL_HEAD_SHOT
	(*g_pActionInfoTable)[SKILL_HEAD_SHOT].Set("SKILL_HEAD_SHOT", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_GUN_SR_MALE, 5, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[SKILL_HEAD_SHOT].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_HEAD_SHOT].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_HEAD_SHOT].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_HEAD_SHOT].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_HEAD_SHOT].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_HEAD_SHOT].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_HEAD_SHOT].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_HEAD_SHOT].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용
	(*g_pActionInfoTable)[SKILL_HEAD_SHOT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_HEAD_SHOT].SetCastingStartFrameAll( 14 );	// 불꽃이 붙는 frame
	(*g_pActionInfoTable)[SKILL_HEAD_SHOT].SetCastingFramesAll( 2 );
	(*g_pActionInfoTable)[SKILL_HEAD_SHOT].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_BULLET_OF_LIGHT );	// 맞는 결과를 표현한다.	
	(*g_pActionInfoTable)[SKILL_HEAD_SHOT].Init ( 1 );
	(*g_pActionInfoTable)[SKILL_HEAD_SHOT][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_HEAD_SHOT][0].EffectSpriteType  = EFFECTSPRITETYPE_HEAD_SHOT;
	(*g_pActionInfoTable)[SKILL_HEAD_SHOT][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_HEAD_SHOT][0].Count				= FrameSize[EFFECTSPRITETYPE_HEAD_SHOT];	
	
	// SKILL_PIERCING

	(*g_pActionInfoTable)[SKILL_PIERCING].Set("SKILL_PIERCING", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_GUN_SR_MALE, 5, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[SKILL_PIERCING].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_PIERCING].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_PIERCING].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_PIERCING].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_PIERCING].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_PIERCING].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_PIERCING].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_PIERCING].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용
	(*g_pActionInfoTable)[SKILL_PIERCING].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_PIERCING].SetCastingStartFrameAll( 14 );	// 불꽃이 붙는 frame
	(*g_pActionInfoTable)[SKILL_PIERCING].SetCastingFramesAll( 2 );
	(*g_pActionInfoTable)[SKILL_PIERCING].SetActionResult( ACTIONRESULTNODE_ACTIONINFO );
//	(*g_pActionInfoTable)[SKILL_PIERCING].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_PIERCING );	// 맞는 결과를 표현한다.
//	(*g_pActionInfoTable)[SKILL_PIERCING].Init( 2 );	
//	(*g_pActionInfoTable)[SKILL_PIERCING][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[SKILL_PIERCING][0].EffectSpriteType = EFFECTSPRITETYPE_PIERCING_BACK;	
//	(*g_pActionInfoTable)[SKILL_PIERCING][0].Count				= FrameSize[EFFECTSPRITETYPE_PIERCING_BACK];
//	(*g_pActionInfoTable)[SKILL_PIERCING][0].Step = 25;
//	(*g_pActionInfoTable)[SKILL_PIERCING][0].LinkCount = 2;
//	(*g_pActionInfoTable)[SKILL_PIERCING][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[SKILL_PIERCING][1].EffectSpriteType = EFFECTSPRITETYPE_PIERCING_FRONT;
//	(*g_pActionInfoTable)[SKILL_PIERCING][1].Count				= FrameSize[EFFECTSPRITETYPE_PIERCING_FRONT];
//	(*g_pActionInfoTable)[SKILL_PIERCING][1].Step = 25;

	// SKILL_SNIPPING
	(*g_pActionInfoTable)[SKILL_SNIPPING].Set("SKILL_SNIPPING", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[SKILL_SNIPPING].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_SNIPPING].SetActionResult( ACTIONRESULTNODE_CREATURE_SNIPPING );	// 사용한 캐릭터를 숨게 한다.
	(*g_pActionInfoTable)[SKILL_SNIPPING].SetEffectStatus( EFFECTSTATUS_SNIPPING_MODE );
	/*
	(*g_pActionInfoTable)[SKILL_SNIPPING].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_SNIPPING].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_SNIPPING].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_SNIPPING].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_SNIPPING].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_SNIPPING].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_SNIPPING].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용
	(*g_pActionInfoTable)[SKILL_SNIPPING].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_SNIPPING].SetCastingStartFrameAll( 14 );	// 불꽃이 붙는 frame
	(*g_pActionInfoTable)[SKILL_SNIPPING].SetCastingFramesAll( 2 );
	*/

	// SKILL_KNOCKS_TARGET_BACK
	/*
	(*g_pActionInfoTable)[SKILL_KNOCKS_TARGET_BACK].Set("SKILL_KNOCKS_TARGET_BACK", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[SKILL_KNOCKS_TARGET_BACK].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_KNOCKS_TARGET_BACK].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_KNOCKS_TARGET_BACK].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_KNOCKS_TARGET_BACK].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_KNOCKS_TARGET_BACK].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_KNOCKS_TARGET_BACK].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_KNOCKS_TARGET_BACK].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_KNOCKS_TARGET_BACK].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용
	(*g_pActionInfoTable)[SKILL_KNOCKS_TARGET_BACK].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_KNOCKS_TARGET_BACK].SetCastingStartFrameAll( 14 );	// 불꽃이 붙는 frame
	(*g_pActionInfoTable)[SKILL_KNOCKS_TARGET_BACK].SetCastingFramesAll( 2 );
	*/

	// SKILL_CRITICAL_SHOOTING
	/*
	(*g_pActionInfoTable)[SKILL_CRITICAL_SHOOTING].Set("SKILL_CRITICAL_SHOOTING", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[SKILL_CRITICAL_SHOOTING].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_CRITICAL_SHOOTING].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_CRITICAL_SHOOTING].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_CRITICAL_SHOOTING].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_CRITICAL_SHOOTING].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_CRITICAL_SHOOTING].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_CRITICAL_SHOOTING].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_CRITICAL_SHOOTING].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용
	(*g_pActionInfoTable)[SKILL_CRITICAL_SHOOTING].SetSoundID( SOUNDID_NULL );
	*/

	// SKILL_SCOPE_SHOOTING
	/*
	(*g_pActionInfoTable)[SKILL_SCOPE_SHOOTING].Set("SKILL_SCOPE_SHOOTING", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[SKILL_SCOPE_SHOOTING].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_SCOPE_SHOOTING].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_SCOPE_SHOOTING].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_SCOPE_SHOOTING].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_SCOPE_SHOOTING].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_SCOPE_SHOOTING].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_SCOPE_SHOOTING].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_SCOPE_SHOOTING].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용
	(*g_pActionInfoTable)[SKILL_SCOPE_SHOOTING].SetSoundID( SOUNDID_NULL );
	*/

	// SKILL_DETECT_MINE
	(*g_pActionInfoTable)[SKILL_DETECT_MINE].Set("SKILL_DETECT_MINE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_DETECT_MINE].SetSoundID( SOUNDID_NULL );		

	
	// SKILL_INSTALL_MINE
	(*g_pActionInfoTable)[SKILL_INSTALL_MINE].Set("SKILL_INSTALL_MINE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ITEM | FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[SKILL_INSTALL_MINE].SetSoundID( SOUND_SLAYER_INSTALL_MINE) ;//SOUNDID_NULL );


	// SKILL_INSTALL_DISARM_MINE
	/*
	(*g_pActionInfoTable)[SKILL_INSTALL_DISARM_MINE].Set("SKILL_INSTALL_DISARM_MINE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_INSTALL_DISARM_MINE].SetSoundID( SOUNDID_NULL );
	*/

	// SKILL_DISARM_MINE
	/*
	(*g_pActionInfoTable)[SKILL_DISARM_MINE].Set("SKILL_DISARM_MINE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_DISARM_MINE].SetSoundID( SOUNDID_NULL );
	*/

	// SKILL_MAKE_BOMB
	(*g_pActionInfoTable)[SKILL_MAKE_BOMB].Set("SKILL_MAKE_BOMB", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ITEM | FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_MAKE_BOMB].SetSoundID( SOUNDID_NULL );

	// SKILL_MAKE_MINE
	(*g_pActionInfoTable)[SKILL_MAKE_MINE].Set("SKILL_MAKE_MINE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ITEM | FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_MAKE_MINE].SetSoundID( SOUNDID_NULL );

	// SKILL_HOLY_SHOOTING
	/*
	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING].Set("SKILL_HOLY_SHOOTING", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_HOLY_SHOOTING_TR_MALE, 5, FLAG_ACTIONINFO_TARGET_OTHER);
	//(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL ); // 총알 사용 안 한다.
	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용
	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING].SetAffectCurrentWeaponActionInfoPlus(SKILL_HOLY_SHOOTING_TR - SKILL_ATTACK_GUN_SR);	// 총마다 다른 effect를 사용하므로.. plus만큼 더해서..
	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING].SetCastingStartFrameAll( 14 );	// 불꽃이 붙는 frame
	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING].SetCastingFramesAll( 2 );
	(*g_pActionInfoTable)[SKILL_HOLY_SHOOTING].SetOptionUseWithBless(); // bless걸린 상태에서 쓸 수 있는 기술
	*/

	//-------------------------------------------------------------
	//
	//                      Priest 마법
	//
	//-------------------------------------------------------------

	// MAGIC_LIGHT,				// Light
#ifdef __EXPO_CLIENT__
	(*g_pActionInfoTable)[MAGIC_LIGHT].SetExpoSkill();
#endif
	(*g_pActionInfoTable)[MAGIC_LIGHT].Set("MAGIC_LIGHT", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_LIGHT].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[MAGIC_LIGHT].UnSetAttack();	// 공격 기술이 아니다
	(*g_pActionInfoTable)[MAGIC_LIGHT].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_LIGHT].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_LIGHT].SetSoundID( SOUNDID_NULL );		
	



	// MAGIC_DETECT_HIDDEN,		// Detect Hidden
#ifdef __EXPO_CLIENT__
	(*g_pActionInfoTable)[MAGIC_DETECT_HIDDEN].SetExpoSkill();
#endif
	(*g_pActionInfoTable)[MAGIC_DETECT_HIDDEN].Set("MAGIC_DETECT_HIDDEN", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_DETECT_HIDDEN].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[MAGIC_DETECT_HIDDEN].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_DETECT_HIDDEN].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_DETECT_HIDDEN].SetSoundID( SOUNDID_NULL );		
	

	/*
	(*g_pActionInfoTable)[MAGIC_DETECT_HIDDEN].Init( 1 );
	(*g_pActionInfoTable)[MAGIC_DETECT_HIDDEN][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[MAGIC_DETECT_HIDDEN][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[MAGIC_DETECT_HIDDEN][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_DETECT_HIDDEN][0].Count				= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	*/

	// MAGIC_CONTINUAL_LIGHT,		// Continual Light
#ifdef __EXPO_CLIENT__
	(*g_pActionInfoTable)[MAGIC_CONTINUAL_LIGHT].SetExpoSkill();
#endif
	(*g_pActionInfoTable)[MAGIC_CONTINUAL_LIGHT].Set("MAGIC_CONTINUAL_LIGHT", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_CONTINUAL_LIGHT].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[MAGIC_CONTINUAL_LIGHT].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_CONTINUAL_LIGHT].SetStartFrameAll( 10 );	
	(*g_pActionInfoTable)[MAGIC_CONTINUAL_LIGHT].SetSoundID( SOUNDID_NULL );	
	
	
	// MAGIC_DETECT_INVISIBILITY,	// Detect Invisibility
#ifdef __EXPO_CLIENT__
	(*g_pActionInfoTable)[MAGIC_DETECT_INVISIBILITY].SetExpoSkill();
#endif
	(*g_pActionInfoTable)[MAGIC_DETECT_INVISIBILITY].Set("MAGIC_DETECT_INVISIBILITY", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_DETECT_INVISIBILITY].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[MAGIC_DETECT_INVISIBILITY].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_DETECT_INVISIBILITY].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_DETECT_INVISIBILITY].SetSoundID( SOUNDID_NULL );		

	// MAGIC_VISIBLE,				// Visible
	(*g_pActionInfoTable)[MAGIC_VISIBLE].Set("MAGIC_VISIBLE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_VISIBLE].SetUser(FLAG_ACTIONINFO_USER_VAMPIRE);
	(*g_pActionInfoTable)[MAGIC_VISIBLE].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[MAGIC_VISIBLE].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_VISIBLE].SetStartFrameAll( 10 );	
	(*g_pActionInfoTable)[MAGIC_VISIBLE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAGIC_VISIBLE].Init( 4 );		
	(*g_pActionInfoTable)[MAGIC_VISIBLE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE;
	(*g_pActionInfoTable)[MAGIC_VISIBLE][0].EffectSpriteType	= EFFECTSPRITETYPE_VISIBLE_1;
	(*g_pActionInfoTable)[MAGIC_VISIBLE][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_VISIBLE][0].LinkCount			= 1;
	(*g_pActionInfoTable)[MAGIC_VISIBLE][0].Count				= 2*16;	//FrameSize[EFFECTSPRITETYPE_VISIBLE_1];
	(*g_pActionInfoTable)[MAGIC_VISIBLE][0].SoundID				= SOUND_SLAYER_VISIBLE;//SOUND_SLAYER_ENCHANT_AURABALL1;
	(*g_pActionInfoTable)[MAGIC_VISIBLE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE;
	(*g_pActionInfoTable)[MAGIC_VISIBLE][1].EffectSpriteType	= EFFECTSPRITETYPE_VISIBLE_2;
	(*g_pActionInfoTable)[MAGIC_VISIBLE][1].Step				= 24;
	(*g_pActionInfoTable)[MAGIC_VISIBLE][1].LinkCount			= 1;
	(*g_pActionInfoTable)[MAGIC_VISIBLE][1].Count				= 2*16;	//FrameSize[EFFECTSPRITETYPE_VISIBLE_2];
	(*g_pActionInfoTable)[MAGIC_VISIBLE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE;
	(*g_pActionInfoTable)[MAGIC_VISIBLE][2].EffectSpriteType	= EFFECTSPRITETYPE_VISIBLE_3;
	(*g_pActionInfoTable)[MAGIC_VISIBLE][2].Step				= 20;
	(*g_pActionInfoTable)[MAGIC_VISIBLE][2].Count				= 2*16;	//FrameSize[EFFECTSPRITETYPE_VISIBLE_3];
	(*g_pActionInfoTable)[MAGIC_VISIBLE][3].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[MAGIC_VISIBLE][3].EffectSpriteType	= EFFECTSPRITETYPE_VISIBLE_4;
	(*g_pActionInfoTable)[MAGIC_VISIBLE][3].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_VISIBLE][3].Count				= FrameSize[EFFECTSPRITETYPE_VISIBLE_4];
	(*g_pActionInfoTable)[MAGIC_VISIBLE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, MAGIC_VISIBLE );	// 맞는 결과를 표현한다.	

	// MAGIC_DETECT_EVIL,			// Detect Evil
	/*
#ifdef __EXPO_CLIENT__
	(*g_pActionInfoTable)[MAGIC_DETECT_EVIL].SetExpoSkill();
#endif
	(*g_pActionInfoTable)[MAGIC_DETECT_EVIL].Set("MAGIC_DETECT_EVIL", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_DETECT_EVIL].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAGIC_DETECT_EVIL].Init( 1 );	
	(*g_pActionInfoTable)[MAGIC_DETECT_EVIL][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_RANDOM;
	(*g_pActionInfoTable)[MAGIC_DETECT_EVIL][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[MAGIC_DETECT_EVIL][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_DETECT_EVIL][0].Count				= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	*/
	
	// MAGIC_AURA_SHIELD,			// Aura Shield
	(*g_pActionInfoTable)[MAGIC_AURA_SHIELD].Set("MAGIC_AURA_SHIELD", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	//(*g_pActionInfoTable)[MAGIC_AURA_SHIELD].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[MAGIC_AURA_SHIELD].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_AURA_SHIELD].SetSoundID( SOUND_SLAYER_AURA_SHIELD) ; //SOUNDID_NULL);
	(*g_pActionInfoTable)[MAGIC_AURA_SHIELD].Init( 1 );		
	(*g_pActionInfoTable)[MAGIC_AURA_SHIELD][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[MAGIC_AURA_SHIELD][0].EffectSpriteType	= EFFECTSPRITETYPE_AURA_PRISM_1;
	(*g_pActionInfoTable)[MAGIC_AURA_SHIELD][0].Step				= 40;
	(*g_pActionInfoTable)[MAGIC_AURA_SHIELD][0].Count				= FrameSize[EFFECTSPRITETYPE_AURA_PRISM_1];	
	/*
	(*g_pActionInfoTable)[MAGIC_AURA_SHIELD].Set("MAGIC_AURA_SHIELD", ACTION_MAGIC, EFFECTSPRITETYPE_AURA_SHIELD_1, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_AURA_SHIELD].SetCastingFramesAll( 25 );
	(*g_pActionInfoTable)[MAGIC_AURA_SHIELD].SetSoundID( SOUNDID_NULL );
	*/
	
	// MAGIC_FLARE,			// Flare
	(*g_pActionInfoTable)[MAGIC_FLARE].Set("MAGIC_FLARE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_FLARE].SetUser(FLAG_ACTIONINFO_USER_ALL & ~FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[MAGIC_FLARE].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[MAGIC_FLARE].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_FLARE].SetStartFrameAll( 10 );	
	(*g_pActionInfoTable)[MAGIC_FLARE].SetSoundID( SOUND_SLAYER_FLARE) ; //SOUNDID_NULL );
	(*g_pActionInfoTable)[MAGIC_FLARE].Init( 2 );		
	(*g_pActionInfoTable)[MAGIC_FLARE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[MAGIC_FLARE][0].EffectSpriteType	= EFFECTSPRITETYPE_CONTINUAL_LIGHT_2;
	(*g_pActionInfoTable)[MAGIC_FLARE][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_FLARE][0].Count				= 32;//FrameSize[EFFECTSPRITETYPE_AURA_BALL_2];
	(*g_pActionInfoTable)[MAGIC_FLARE][0].SoundID			= SOUND_SLAYER_ENCHANT_AURABALL1;
	(*g_pActionInfoTable)[MAGIC_FLARE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[MAGIC_FLARE][1].EffectSpriteType	= EFFECTSPRITETYPE_CONTINUAL_LIGHT_2;
	(*g_pActionInfoTable)[MAGIC_FLARE][1].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_FLARE][1].Count				= 2;//FrameSize[EFFECTSPRITETYPE_AURA_BALL_2];
	(*g_pActionInfoTable)[MAGIC_FLARE][1].SetResultTime();

	// MAGIC_AURA_BALL,			// Aura Ball
	(*g_pActionInfoTable)[MAGIC_AURA_BALL].Set("MAGIC_AURA_BALL", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_AURA_BALL].SetUser(FLAG_ACTIONINFO_USER_ALL & ~FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[MAGIC_AURA_BALL].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[MAGIC_AURA_BALL].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_AURA_BALL].SetStartFrameAll( 10 );	
	(*g_pActionInfoTable)[MAGIC_AURA_BALL].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAGIC_AURA_BALL].Init( 1 );		
	(*g_pActionInfoTable)[MAGIC_AURA_BALL][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[MAGIC_AURA_BALL][0].EffectSpriteType	= EFFECTSPRITETYPE_AURA_BALL_2;
	(*g_pActionInfoTable)[MAGIC_AURA_BALL][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_AURA_BALL][0].Count				= 32;//FrameSize[EFFECTSPRITETYPE_AURA_BALL_2];
	(*g_pActionInfoTable)[MAGIC_AURA_BALL][0].SoundID			= SOUND_SLAYER_AURA_BALL ; //SOUND_SLAYER_ENCHANT_AURABALL1;
	//(*g_pActionInfoTable)[MAGIC_AURA_BALL][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	//(*g_pActionInfoTable)[MAGIC_AURA_BALL][1].EffectSpriteType	= EFFECTSPRITETYPE_AURA_BALL_2;
	//(*g_pActionInfoTable)[MAGIC_AURA_BALL][1].Step				= 25;
	//(*g_pActionInfoTable)[MAGIC_AURA_BALL][1].Count				= 2;//FrameSize[EFFECTSPRITETYPE_AURA_BALL_2];

	// SKILL_LIGHT_BALL,			// Aura Ball
	(*g_pActionInfoTable)[SKILL_LIGHT_BALL].Set("SKILL_LIGHT_BALL", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_LIGHT_BALL].SetUser(FLAG_ACTIONINFO_USER_ALL & ~FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[SKILL_LIGHT_BALL].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[SKILL_LIGHT_BALL].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[SKILL_LIGHT_BALL].SetStartFrameAll( 10 );	
	(*g_pActionInfoTable)[SKILL_LIGHT_BALL].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_LIGHT_BALL].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_LIGHT_BALL][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[SKILL_LIGHT_BALL][0].EffectSpriteType	= EFFECTSPRITETYPE_LIGHT_BALL;
	(*g_pActionInfoTable)[SKILL_LIGHT_BALL][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_LIGHT_BALL][0].Count				= 32;//FrameSize[EFFECTSPRITETYPE_AURA_BALL_2];
	(*g_pActionInfoTable)[SKILL_LIGHT_BALL][0].SoundID			= SOUND_SLAYER_ENCHANT_AURABALL1;

	// SKILL_HOLY_ARROW,			// Aura Ball
	(*g_pActionInfoTable)[SKILL_HOLY_ARROW].Set("SKILL_HOLY_ARROW", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_HOLY_ARROW].SetUser(FLAG_ACTIONINFO_USER_ALL & ~FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[SKILL_HOLY_ARROW].SetCastingActionInfo( CASTING_HEALING );
	(*g_pActionInfoTable)[SKILL_HOLY_ARROW].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[SKILL_HOLY_ARROW].SetStartFrameAll( 10 );	
	(*g_pActionInfoTable)[SKILL_HOLY_ARROW].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_HOLY_ARROW].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_HOLY_ARROW][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[SKILL_HOLY_ARROW][0].EffectSpriteType	= EFFECTSPRITETYPE_HOLY_ARROW;
	(*g_pActionInfoTable)[SKILL_HOLY_ARROW][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_HOLY_ARROW][0].Count				= 32;//FrameSize[EFFECTSPRITETYPE_AURA_BALL_2];
	(*g_pActionInfoTable)[SKILL_HOLY_ARROW][0].SoundID			= SOUND_SLAYER_HOLY_ARROW; //SOUND_SLAYER_ENCHANT_AURABALL1;

	// MAGIC_AURA_CROSS,			// Aura Cross
	/*
	(*g_pActionInfoTable)[MAGIC_AURA_CROSS].Set("MAGIC_AURA_CROSS", ACTION_MAGIC, EFFECTSPRITETYPE_CREATE_HOLY_WATER_1, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_AURA_CROSS].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAGIC_AURA_CROSS].Init( 2 );		
	(*g_pActionInfoTable)[MAGIC_AURA_CROSS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[MAGIC_AURA_CROSS][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[MAGIC_AURA_CROSS][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_AURA_CROSS][0].Count			= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[MAGIC_AURA_CROSS][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[MAGIC_AURA_CROSS][1].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[MAGIC_AURA_CROSS][1].Step				= 25; 
	(*g_pActionInfoTable)[MAGIC_AURA_CROSS][1].Count			= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[MAGIC_AURA_CROSS][1].SoundID			= 3;
	*/

	// MAGIC_AURA_RING,			// Aura Ring
	(*g_pActionInfoTable)[MAGIC_AURA_RING].Set("MAGIC_AURA_RING", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_AURA_RING].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[MAGIC_AURA_RING].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_AURA_RING].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_AURA_RING].SetSoundID( SOUNDID_NULL );		

	// SKILL_REBUKE,			// Aura Ring
	(*g_pActionInfoTable)[SKILL_REBUKE].Set("SKILL_REBUKE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_REBUKE].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[SKILL_REBUKE].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[SKILL_REBUKE].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_REBUKE].SetSoundID( SOUND_SLAYER_REBUKE) ; //SOUND_SLAYER_BLADE_SS );		
	(*g_pActionInfoTable)[SKILL_REBUKE].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_REBUKE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_REBUKE][0].EffectSpriteType	= EFFECTSPRITETYPE_REBUKE;
	(*g_pActionInfoTable)[SKILL_REBUKE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_REBUKE][0].Count			= FrameSize[EFFECTSPRITETYPE_REBUKE];
//	(*g_pActionInfoTable)[SKILL_REBUKE][0].SoundID				= 3;
	(*g_pActionInfoTable)[SKILL_REBUKE][0].SetResultTime();

	// SKILL_TURN_UNDEAD,			// Aura Ring
	(*g_pActionInfoTable)[SKILL_TURN_UNDEAD].Set("SKILL_TURN_UNDEAD", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_MAGIC]);
//	(*g_pActionInfoTable)[SKILL_TURN_UNDEAD].SetCastingActionInfo( CASTING_HEALING );
	(*g_pActionInfoTable)[SKILL_TURN_UNDEAD].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[SKILL_TURN_UNDEAD].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_TURN_UNDEAD].SetSoundID( SOUND_SLAYER_BLADE_BERSERKER );		
	(*g_pActionInfoTable)[SKILL_TURN_UNDEAD].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_TURN_UNDEAD][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_TURN_UNDEAD][0].EffectSpriteType	= EFFECTSPRITETYPE_TURN_UNDEAD_ARRAY;
	(*g_pActionInfoTable)[SKILL_TURN_UNDEAD][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TURN_UNDEAD][0].Count			= FrameSize[EFFECTSPRITETYPE_TURN_UNDEAD_ARRAY];
//	(*g_pActionInfoTable)[SKILL_TURN_UNDEAD][0].SoundID				= 3;
	(*g_pActionInfoTable)[SKILL_TURN_UNDEAD][0].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_TURN_UNDEAD][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_TURN_UNDEAD][1].EffectSpriteType	= EFFECTSPRITETYPE_TURN_UNDEAD_FIRE;
	(*g_pActionInfoTable)[SKILL_TURN_UNDEAD][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TURN_UNDEAD][1].Count			= FrameSize[EFFECTSPRITETYPE_TURN_UNDEAD_FIRE];
//	(*g_pActionInfoTable)[SKILL_TURN_UNDEAD][1].SoundID				= 3;
	(*g_pActionInfoTable)[SKILL_TURN_UNDEAD][1].SetResultTime();

	// MAGIC_SAINT_AURA,			// Saint Aura
	(*g_pActionInfoTable)[MAGIC_SAINT_AURA].Set("MAGIC_SAINT_AURA", ACTION_MAGIC, EFFECTSPRITETYPE_LIGHT_2, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_SAINT_AURA].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAGIC_SAINT_AURA].Init( 1 );		
	(*g_pActionInfoTable)[MAGIC_SAINT_AURA][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[MAGIC_SAINT_AURA][0].EffectSpriteType	= EFFECTSPRITETYPE_DARKNESS_1;
	(*g_pActionInfoTable)[MAGIC_SAINT_AURA][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_SAINT_AURA][0].Count			= FrameSize[EFFECTSPRITETYPE_DARKNESS_1];
	(*g_pActionInfoTable)[MAGIC_SAINT_AURA][0].SoundID				= 3;
	(*g_pActionInfoTable)[MAGIC_SAINT_AURA][0].SetResultTime();

	// MAGIC_CREATE_HOLY_WATER,	// Create Holy Water
	(*g_pActionInfoTable)[MAGIC_CREATE_HOLY_WATER].Set("MAGIC_CREATE_HOLY_WATER", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_ITEM, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_CREATE_HOLY_WATER].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[MAGIC_CREATE_HOLY_WATER].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_CREATE_HOLY_WATER].SetStartWithCasting();
	//(*g_pActionInfoTable)[MAGIC_CREATE_HOLY_WATER].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_CREATE_HOLY_WATER].SetSoundID( SOUNDID_NULL );		
	(*g_pActionInfoTable)[MAGIC_CREATE_HOLY_WATER].Init( 2 );
	(*g_pActionInfoTable)[MAGIC_CREATE_HOLY_WATER][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_INVENTORY;
	(*g_pActionInfoTable)[MAGIC_CREATE_HOLY_WATER][0].EffectSpriteType	= EFFECTSPRITETYPE_CREATE_HOLY_WATER_1;
	(*g_pActionInfoTable)[MAGIC_CREATE_HOLY_WATER][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_CREATE_HOLY_WATER][0].Count				= FrameSize[EFFECTSPRITETYPE_CREATE_HOLY_WATER_1];
	(*g_pActionInfoTable)[MAGIC_CREATE_HOLY_WATER][0].SoundID			= SOUND_SLAYER_CREATE_HOLY_WATER ; //SOUND_SLAYER_ENCHANT_CHW1;
	(*g_pActionInfoTable)[MAGIC_CREATE_HOLY_WATER][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_INVENTORY;	// 반복
	(*g_pActionInfoTable)[MAGIC_CREATE_HOLY_WATER][1].EffectSpriteType	= EFFECTSPRITETYPE_CREATE_HOLY_WATER_2;
	(*g_pActionInfoTable)[MAGIC_CREATE_HOLY_WATER][1].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_CREATE_HOLY_WATER][1].Count				= FrameSize[EFFECTSPRITETYPE_CREATE_HOLY_WATER_2];
//	(*g_pActionInfoTable)[MAGIC_CREATE_HOLY_WATER][1].SetDelayNode();
	
	// MAGIC_BLESS,				// Bless
	(*g_pActionInfoTable)[MAGIC_BLESS].Set("MAGIC_BLESS", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_BLESS].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[MAGIC_BLESS].SetCastingActionInfo( CASTING_ENCHANT );	
	(*g_pActionInfoTable)[MAGIC_BLESS].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_BLESS].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_BLESS].SetEffectStatus( EFFECTSTATUS_BLESS );
	(*g_pActionInfoTable)[MAGIC_BLESS].SetSoundID( SOUNDID_NULL );		


	// MAGIC_PURIFY,			// Bless Ground
	(*g_pActionInfoTable)[MAGIC_PURIFY].Set("MAGIC_PURIFY", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_PURIFY].SetUser(FLAG_ACTIONINFO_USER_ALL & ~FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[MAGIC_PURIFY].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[MAGIC_PURIFY].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_PURIFY].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_PURIFY].SetSoundID( SOUND_SLAYER_ENCHANT_BLESSGROUND );		
	
	// MAGIC_STRIKING,				// Striking
	(*g_pActionInfoTable)[MAGIC_STRIKING].Set("MAGIC_STRIKING", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_STRIKING].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[MAGIC_STRIKING].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[MAGIC_STRIKING].SetCastingActionInfo( CASTING_ENCHANT );	
	(*g_pActionInfoTable)[MAGIC_STRIKING].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_STRIKING].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_STRIKING].SetEffectStatus( EFFECTSTATUS_STRIKING );
	(*g_pActionInfoTable)[MAGIC_STRIKING].SetSoundID( SOUNDID_NULL );		

	// MAGIC_ENCHANT_OPTION_NULL,	// Create Holy Water
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_NULL].Set("MAGIC_ENCHANT_OPTION_NULL", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ITEM, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_NULL].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_NULL].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_NULL].SetStartWithCasting();
	//(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_NULL].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_NULL].SetSoundID( SOUNDID_NULL );		
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_NULL].Init( 2 );
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_NULL][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_INVENTORY;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_NULL][0].EffectSpriteType	= EFFECTSPRITETYPE_ENCHANT_START;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_NULL][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_NULL][0].Count				= FrameSize[EFFECTSPRITETYPE_ENCHANT_START];
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_NULL][0].SoundID			= SOUND_SLAYER_ENCHANT_CHW1;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_NULL][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_INVENTORY;	// 반복
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_NULL][1].EffectSpriteType	= EFFECTSPRITETYPE_ENCHANT_OPTION_NULL;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_NULL][1].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_NULL][1].Count				= FrameSize[EFFECTSPRITETYPE_ENCHANT_OPTION_NULL];
//	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_NULL][1].SetDelayNode();

	// MAGIC_ENCHANT_OPTION_PLUS,	// Create Holy Water
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_PLUS].Set("MAGIC_ENCHANT_OPTION_PLUS", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ITEM, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_PLUS].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_PLUS].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_PLUS].SetStartWithCasting();
	//(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_PLUS].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_PLUS].SetSoundID( SOUNDID_NULL );		
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_PLUS].Init( 2 );
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_PLUS][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_INVENTORY;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_PLUS][0].EffectSpriteType	= EFFECTSPRITETYPE_ENCHANT_START;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_PLUS][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_PLUS][0].Count				= FrameSize[EFFECTSPRITETYPE_ENCHANT_START];
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_PLUS][0].SoundID			= SOUND_SLAYER_ENCHANT_CHW1;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_PLUS][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_INVENTORY;	// 반복
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_PLUS][1].EffectSpriteType	= EFFECTSPRITETYPE_ENCHANT_OPTION_PLUS;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_PLUS][1].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_PLUS][1].Count				= FrameSize[EFFECTSPRITETYPE_ENCHANT_OPTION_PLUS];
//	(*g_pActionInfoTable)[MAGIC_ENCHANT_OPTION_PLUS][1].SetDelayNode();

	//서드 인첸트	
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_NULL].Set("MAGIC_ENCHANT_OPTION_NULL", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ITEM, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_NULL].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_NULL].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_NULL].SetStartWithCasting();
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_NULL].SetSoundID( SOUNDID_NULL );		
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_NULL].Init( 2 );
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_NULL][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_INVENTORY;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_NULL][0].EffectSpriteType	= EFFECTSPRITETYPE_ENCHANT_START;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_NULL][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_NULL][0].Count				= FrameSize[EFFECTSPRITETYPE_ENCHANT_START];
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_NULL][0].SoundID			= SOUND_SLAYER_ENCHANT_CHW1;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_NULL][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_INVENTORY;	// 반복
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_NULL][1].EffectSpriteType	= EFFECTSPRITETYPE_ENCHANT_OPTION_NULL;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_NULL][1].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_NULL][1].Count				= FrameSize[EFFECTSPRITETYPE_ENCHANT_OPTION_NULL];
	
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_PLUS].Set("MAGIC_ENCHANT_OPTION_PLUS", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ITEM, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_PLUS].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_PLUS].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_PLUS].SetStartWithCasting();
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_PLUS].SetSoundID( SOUNDID_NULL );		
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_PLUS].Init( 2 );
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_PLUS][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_INVENTORY;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_PLUS][0].EffectSpriteType	= EFFECTSPRITETYPE_ENCHANT_START;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_PLUS][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_PLUS][0].Count				= FrameSize[EFFECTSPRITETYPE_ENCHANT_START];
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_PLUS][0].SoundID			= SOUND_SLAYER_ENCHANT_CHW1;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_PLUS][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_INVENTORY;	// 반복
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_PLUS][1].EffectSpriteType	= EFFECTSPRITETYPE_ENCHANT_OPTION_PLUS;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_PLUS][1].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_THIRD_OPTION_PLUS][1].Count				= FrameSize[EFFECTSPRITETYPE_ENCHANT_OPTION_PLUS];


	// MAGIC_ENCHANT_REMOVE_ITEM,	// Create Holy Water
	(*g_pActionInfoTable)[MAGIC_ENCHANT_REMOVE_ITEM].Set("MAGIC_ENCHANT_REMOVE_ITEM", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ITEM, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_ENCHANT_REMOVE_ITEM].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[MAGIC_ENCHANT_REMOVE_ITEM].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_ENCHANT_REMOVE_ITEM].SetStartWithCasting();
	//(*g_pActionInfoTable)[MAGIC_ENCHANT_REMOVE_ITEM].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_ENCHANT_REMOVE_ITEM].SetSoundID( SOUNDID_NULL );		
	(*g_pActionInfoTable)[MAGIC_ENCHANT_REMOVE_ITEM].Init( 2 );
	(*g_pActionInfoTable)[MAGIC_ENCHANT_REMOVE_ITEM][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_INVENTORY;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_REMOVE_ITEM][0].EffectSpriteType	= EFFECTSPRITETYPE_ENCHANT_START;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_REMOVE_ITEM][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_REMOVE_ITEM][0].Count				= FrameSize[EFFECTSPRITETYPE_ENCHANT_START];
	(*g_pActionInfoTable)[MAGIC_ENCHANT_REMOVE_ITEM][0].SoundID			= SOUND_SLAYER_ENCHANT_CHW1;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_REMOVE_ITEM][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_INVENTORY;	// 반복
	(*g_pActionInfoTable)[MAGIC_ENCHANT_REMOVE_ITEM][1].EffectSpriteType	= EFFECTSPRITETYPE_ENCHANT_REMOVE_ITEM;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_REMOVE_ITEM][1].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_ENCHANT_REMOVE_ITEM][1].Count				= FrameSize[EFFECTSPRITETYPE_ENCHANT_REMOVE_ITEM];
//	(*g_pActionInfoTable)[MAGIC_ENCHANT_REMOVE_ITEM][1].SetDelayNode();

	// MAGIC_ENCHANT,				// Enchant
//	(*g_pActionInfoTable)[MAGIC_ENCHANT].Set("MAGIC_ENCHANT", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ITEM, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
//	(*g_pActionInfoTable)[MAGIC_ENCHANT].SetCastingActionInfo( CASTING_ENCHANT );
//	(*g_pActionInfoTable)[MAGIC_ENCHANT].SetCastingFramesAll( 24 );
//	(*g_pActionInfoTable)[MAGIC_ENCHANT].SetStartFrameAll( 10 );
//	(*g_pActionInfoTable)[MAGIC_ENCHANT].SetSoundID( SOUNDID_NULL );


	// MAGIC_IDENTIFY,				// Identify
//	(*g_pActionInfoTable)[MAGIC_IDENTIFY].Set("MAGIC_IDENTIFY", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ITEM, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
//	(*g_pActionInfoTable)[MAGIC_IDENTIFY].SetCastingActionInfo( CASTING_ENCHANT );
//	(*g_pActionInfoTable)[MAGIC_IDENTIFY].SetCastingFramesAll( 24 );
//	(*g_pActionInfoTable)[MAGIC_IDENTIFY].SetStartFrameAll( 10 );
//	(*g_pActionInfoTable)[MAGIC_IDENTIFY].SetSoundID( SOUNDID_NULL );
	
	
	// MAGIC_REMOVE_CURSE,			// Remove Curse
	(*g_pActionInfoTable)[MAGIC_REMOVE_CURSE].Set("MAGIC_REMOVE_CURSE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_REMOVE_CURSE].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[MAGIC_REMOVE_CURSE].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[MAGIC_REMOVE_CURSE].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_REMOVE_CURSE].SetStartFrameAll( 7 );
	(*g_pActionInfoTable)[MAGIC_REMOVE_CURSE].SetSoundID( SOUNDID_NULL );		
	
	// MAGIC_PROTECTION_FROM_CURSE,	// Protection From Curse
	(*g_pActionInfoTable)[MAGIC_PROTECTION_FROM_CURSE].Set("MAGIC_PROTECTION_FROM_CURSE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_PROTECTION_FROM_CURSE].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[MAGIC_PROTECTION_FROM_CURSE].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[MAGIC_PROTECTION_FROM_CURSE].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_PROTECTION_FROM_CURSE].SetStartFrameAll( 7 );
	(*g_pActionInfoTable)[MAGIC_PROTECTION_FROM_CURSE].SetSoundID( SOUNDID_NULL );		


	// MAGIC_CURE_LIGHT_WOUNDS,	// Cure Light Wounds
	(*g_pActionInfoTable)[MAGIC_CURE_LIGHT_WOUNDS].Set("MAGIC_CURE_LIGHT_WOUNDS", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_CURE_LIGHT_WOUNDS].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[MAGIC_CURE_LIGHT_WOUNDS].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[MAGIC_CURE_LIGHT_WOUNDS].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_CURE_LIGHT_WOUNDS].SetStartFrameAll( 8 );
	(*g_pActionInfoTable)[MAGIC_CURE_LIGHT_WOUNDS].SetSoundID( SOUNDID_NULL );		

	// MAGIC_CURE_SERIOUS_WOUNDS,	// Cure SERIOUS Wounds
	(*g_pActionInfoTable)[MAGIC_CURE_SERIOUS_WOUNDS].Set("MAGIC_CURE_SERIOUS_WOUNDS", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_CURE_SERIOUS_WOUNDS].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[MAGIC_CURE_SERIOUS_WOUNDS].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[MAGIC_CURE_SERIOUS_WOUNDS].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_CURE_SERIOUS_WOUNDS].SetStartFrameAll( 8 );
	(*g_pActionInfoTable)[MAGIC_CURE_SERIOUS_WOUNDS].SetSoundID( SOUNDID_NULL );		
	(*g_pActionInfoTable)[MAGIC_CURE_SERIOUS_WOUNDS].SetEffectStatus( EFFECTSTATUS_WHITE_BLESS );		
	

	// MAGIC_CAUSE_LIGHT_WOUNDS,
	(*g_pActionInfoTable)[MAGIC_CAUSE_LIGHT_WOUNDS].Set("MAGIC_CAUSE_LIGHT_WOUNDS", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_CAUSE_LIGHT_WOUNDS].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[MAGIC_CAUSE_LIGHT_WOUNDS].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_CAUSE_LIGHT_WOUNDS].SetStartFrameAll( 8 );
	(*g_pActionInfoTable)[MAGIC_CAUSE_LIGHT_WOUNDS].SetSoundID( SOUNDID_NULL );		
	(*g_pActionInfoTable)[MAGIC_CAUSE_LIGHT_WOUNDS].Init( 1 );		
	(*g_pActionInfoTable)[MAGIC_CAUSE_LIGHT_WOUNDS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	// 2004, 5, 20 sobeit modify start
	//(*g_pActionInfoTable)[MAGIC_CAUSE_LIGHT_WOUNDS][0].EffectSpriteType	= EFFECTSPRITETYPE_CURE_LIGHT_WOUND_NEW_1;
	(*g_pActionInfoTable)[MAGIC_CAUSE_LIGHT_WOUNDS][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_CAUSE_LIGHT_WOUNDS_FLY;
	// 2004, 5, 20 sobeit modify end
	(*g_pActionInfoTable)[MAGIC_CAUSE_LIGHT_WOUNDS][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_CAUSE_LIGHT_WOUNDS][0].Count				= 32;//FrameSize[EFFECTSPRITETYPE_CURE_LIGHT_WOUND_GO];	

	// MAGIC_CAUSE_SERIOUS_WOUNDS,	// CAUSE SERIOUS Wounds
	(*g_pActionInfoTable)[MAGIC_CAUSE_SERIOUS_WOUNDS].Set("MAGIC_CAUSE_SERIOUS_WOUNDS", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_CAUSE_SERIOUS_WOUNDS].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[MAGIC_CAUSE_SERIOUS_WOUNDS].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_CAUSE_SERIOUS_WOUNDS].SetStartFrameAll( 8 );
	(*g_pActionInfoTable)[MAGIC_CAUSE_SERIOUS_WOUNDS].SetSoundID( SOUNDID_NULL );		
	(*g_pActionInfoTable)[MAGIC_CAUSE_SERIOUS_WOUNDS].Init( 1 );		
	(*g_pActionInfoTable)[MAGIC_CAUSE_SERIOUS_WOUNDS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	// 2004, 5, 20 sobeit modify start
	//(*g_pActionInfoTable)[MAGIC_CAUSE_SERIOUS_WOUNDS][0].EffectSpriteType	= EFFECTSPRITETYPE_CURE_LIGHT_WOUND_NEW_1;
	(*g_pActionInfoTable)[MAGIC_CAUSE_SERIOUS_WOUNDS][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_CAUSE_SERIOUS_WOUNDS_FLY;
	// 2004, 5, 20 sobeit modify end
	(*g_pActionInfoTable)[MAGIC_CAUSE_SERIOUS_WOUNDS][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_CAUSE_SERIOUS_WOUNDS][0].Count				= 32;//FrameSize[EFFECTSPRITETYPE_CURE_LIGHT_WOUND_GO];	

	// MAGIC_CAUSE_CRITICAL_	WOUNDS,
	(*g_pActionInfoTable)[MAGIC_CAUSE_CRITICAL_WOUNDS].Set("MAGIC_CAUSE_CRITICAL_WOUNDS", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_CAUSE_CRITICAL_WOUNDS].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[MAGIC_CAUSE_CRITICAL_WOUNDS].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_CAUSE_CRITICAL_WOUNDS].SetStartFrameAll( 8 );
	(*g_pActionInfoTable)[MAGIC_CAUSE_CRITICAL_WOUNDS].SetEffectStatus( EFFECTSTATUS_CAUSE_CRITICAL_WOUNDS );
	(*g_pActionInfoTable)[MAGIC_CAUSE_CRITICAL_WOUNDS].SetSoundID( SOUNDID_NULL );		
	(*g_pActionInfoTable)[MAGIC_CAUSE_CRITICAL_WOUNDS].SetSkillFailDelay(); // 스킬실패해도 딜레이는 남아 있다..

	// MAGIC_PRAYER
	(*g_pActionInfoTable)[MAGIC_PRAYER].Set("MAGIC_PRAYER", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[MAGIC_PRAYER].SetSoundID( SOUNDID_NULL );

	// MAGIC_MEDITATION
	(*g_pActionInfoTable)[MAGIC_MEDITATION].Set("MAGIC_MEDITATION", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[MAGIC_MEDITATION].SetSoundID( SOUNDID_NULL );

	// MAGIC_SACRIFICE,	// Cure Light Wounds
	(*g_pActionInfoTable)[MAGIC_SACRIFICE].Set("MAGIC_SACRIFICE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_SACRIFICE].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[MAGIC_SACRIFICE].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_SACRIFICE].SetStartFrameAll( 8 );
	(*g_pActionInfoTable)[MAGIC_SACRIFICE].SetSoundID( SOUNDID_NULL );		
	(*g_pActionInfoTable)[MAGIC_SACRIFICE].Init( 1 );
	(*g_pActionInfoTable)[MAGIC_SACRIFICE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[MAGIC_SACRIFICE][0].EffectSpriteType	= EFFECTSPRITETYPE_SACRIFICE_1;
	(*g_pActionInfoTable)[MAGIC_SACRIFICE][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_SACRIFICE][0].Count				= FrameSize[EFFECTSPRITETYPE_SACRIFICE_1];
	(*g_pActionInfoTable)[MAGIC_SACRIFICE][0].SoundID			= SOUND_SLAYER_ENCHANT_CHW1;

	// MAGIC_CURE_LIGHT_WOUNDS,	// Cure Light Wounds
	(*g_pActionInfoTable)[MAGIC_CURE_LIGHT_WOUNDS].Set("MAGIC_CURE_LIGHT_WOUNDS", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_CURE_LIGHT_WOUNDS].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[MAGIC_CURE_LIGHT_WOUNDS].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[MAGIC_CURE_LIGHT_WOUNDS].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_CURE_LIGHT_WOUNDS].SetStartFrameAll( 8 );
	(*g_pActionInfoTable)[MAGIC_CURE_LIGHT_WOUNDS].SetSoundID( SOUNDID_NULL );		
	(*g_pActionInfoTable)[MAGIC_CURE_LIGHT_WOUNDS].Init( 1 );		
	(*g_pActionInfoTable)[MAGIC_CURE_LIGHT_WOUNDS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[MAGIC_CURE_LIGHT_WOUNDS][0].EffectSpriteType	= EFFECTSPRITETYPE_CURE_LIGHT_WOUND_NEW_1;
	(*g_pActionInfoTable)[MAGIC_CURE_LIGHT_WOUNDS][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_CURE_LIGHT_WOUNDS][0].Count				= 32;//FrameSize[EFFECTSPRITETYPE_CURE_LIGHT_WOUND_GO];	

	// MAGIC_CURE_POISON,			// Cure Poison
	(*g_pActionInfoTable)[MAGIC_CURE_POISON].Set("MAGIC_CURE_POISON", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_CURE_POISON].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[MAGIC_CURE_POISON].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[MAGIC_CURE_POISON].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_CURE_POISON].SetStartFrameAll( 7 );
	(*g_pActionInfoTable)[MAGIC_CURE_POISON].SetSoundID( SOUNDID_NULL );		

	// MAGIC_PROTECTION_FROM_POISON,	// Protection From Poison
	(*g_pActionInfoTable)[MAGIC_PROTECTION_FROM_POISON].Set("MAGIC_PROTECTION_FROM_POISON", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_PROTECTION_FROM_POISON].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[MAGIC_PROTECTION_FROM_POISON].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[MAGIC_PROTECTION_FROM_POISON].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_PROTECTION_FROM_POISON].SetStartFrameAll( 7 );
	(*g_pActionInfoTable)[MAGIC_PROTECTION_FROM_POISON].SetSoundID( SOUNDID_NULL );		

	// MAGIC_PROTECTION_FROM_ACID,	// Protection From Poison
	(*g_pActionInfoTable)[MAGIC_PROTECTION_FROM_ACID].Set("MAGIC_PROTECTION_FROM_ACID", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_PROTECTION_FROM_ACID].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[MAGIC_PROTECTION_FROM_ACID].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[MAGIC_PROTECTION_FROM_ACID].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_PROTECTION_FROM_ACID].SetStartFrameAll( 7 );
	(*g_pActionInfoTable)[MAGIC_PROTECTION_FROM_ACID].SetSoundID( SOUNDID_NULL );	
	
	// MAGIC_CURE_PARALYSIS,		// Cure Paralysis
	/*
	(*g_pActionInfoTable)[MAGIC_CURE_PARALYSIS].Set("MAGIC_CURE_PARALYSIS", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_CURE_PARALYSIS].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[MAGIC_CURE_PARALYSIS].SetCastingFramesAll( 8 );
	(*g_pActionInfoTable)[MAGIC_CURE_PARALYSIS].SetStartFrameAll( 7 );
	(*g_pActionInfoTable)[MAGIC_CURE_PARALYSIS].SetSoundID( SOUNDID_NULL );		
	*/

	// MAGIC_CURE_CRITICAL_WOUNDS,	// Cure Critical Wounds
	(*g_pActionInfoTable)[MAGIC_CURE_CRITICAL_WOUNDS].Set("MAGIC_CURE_CRITICAL_WOUNDS", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_CURE_CRITICAL_WOUNDS].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[MAGIC_CURE_CRITICAL_WOUNDS].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[MAGIC_CURE_CRITICAL_WOUNDS].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_CURE_CRITICAL_WOUNDS].SetStartFrameAll( 7 );
	(*g_pActionInfoTable)[MAGIC_CURE_CRITICAL_WOUNDS].SetSoundID( SOUNDID_NULL );		
	(*g_pActionInfoTable)[MAGIC_CURE_CRITICAL_WOUNDS].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, MAGIC_CURE_SERIOUS_WOUNDS );	// 맞는 결과를 표현한다.	
	
	// SKILL_SPIRIT_GUARD,	// Cure Critical Wounds  2005.12.06 Sjheo  FLAG_ACTIONINFO_TARGET_SELF  -> FLAG_ACTIONINFO_TARGET_OTHER 으로 수정 
	(*g_pActionInfoTable)[SKILL_SPIRIT_GUARD].Set("SKILL_SPIRIT_GUARD", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_SPIRIT_GUARD].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[SKILL_SPIRIT_GUARD].SetCastingActionInfo( CASTING_ENCHANT );	
	(*g_pActionInfoTable)[SKILL_SPIRIT_GUARD].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[SKILL_SPIRIT_GUARD].SetStartFrameAll( 7 );
	(*g_pActionInfoTable)[SKILL_SPIRIT_GUARD].SetSoundID( SOUNDID_NULL );		
	(*g_pActionInfoTable)[SKILL_SPIRIT_GUARD].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, MAGIC_CAUSE_SERIOUS_WOUNDS );	// 맞는 결과를 표현한다.	
	
	// MAGIC_PROTECTION_FROM_PARALYSIS,// Protection From Paralysis
	/*
	(*g_pActionInfoTable)[MAGIC_PROTECTION_FROM_PARALYSIS].Set("MAGIC_PROTECTION_FROM_PARALYSIS", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_PROTECTION_FROM_PARALYSIS].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[MAGIC_PROTECTION_FROM_PARALYSIS].SetCastingFramesAll( 8 );
	(*g_pActionInfoTable)[MAGIC_PROTECTION_FROM_PARALYSIS].SetStartFrameAll( 7 );
	(*g_pActionInfoTable)[MAGIC_PROTECTION_FROM_PARALYSIS].SetSoundID( SOUNDID_NULL );		
	*/

	// MAGIC_RESTORE,				// Restore
	(*g_pActionInfoTable)[MAGIC_RESTORE].Set("MAGIC_RESTORE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_RESTORE].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[MAGIC_RESTORE].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_RESTORE].SetStartFrameAll( 7 );
	(*g_pActionInfoTable)[MAGIC_RESTORE].SetSoundID( SOUNDID_NULL );		

//	// MAGIC_REGENERATION,			// Regeneration
//	(*g_pActionInfoTable)[MAGIC_REGENERATION].Set("MAGIC_REGENERATION", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
//	(*g_pActionInfoTable)[MAGIC_REGENERATION].SetCastingActionInfo( CASTING_HEALING );	
//	(*g_pActionInfoTable)[MAGIC_REGENERATION].SetCastingFramesAll( 24 );
//	(*g_pActionInfoTable)[MAGIC_REGENERATION].SetStartFrameAll( 7 );
//	(*g_pActionInfoTable)[MAGIC_REGENERATION].SetSoundID( SOUNDID_NULL );		
	
	// MAGIC_CURE_ALL,				// Cure All
	(*g_pActionInfoTable)[MAGIC_CURE_ALL].Set("MAGIC_CURE_ALL", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_CURE_ALL].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[MAGIC_CURE_ALL].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[MAGIC_CURE_ALL].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_CURE_ALL].SetStartFrameAll( 7 );
	(*g_pActionInfoTable)[MAGIC_CURE_ALL].SetSoundID( SOUND_SLAYER_HEAL_CUREALL );		

	// MAGIC_MASS_CURE,				// Cure All
//	(*g_pActionInfoTable)[MAGIC_MASS_CURE].Set("MAGIC_MASS_CURE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
//	(*g_pActionInfoTable)[MAGIC_MASS_CURE].SetCastingActionInfo( CASTING_HEALING );	
//	(*g_pActionInfoTable)[MAGIC_MASS_CURE].SetCastingFramesAll( 24 );
//	(*g_pActionInfoTable)[MAGIC_MASS_CURE].SetStartFrameAll( 7 );
//	(*g_pActionInfoTable)[MAGIC_MASS_CURE].SetSoundID( SOUNDID_NULL );		

	// MAGIC_MASS_HEAL,				// Cure All
//	(*g_pActionInfoTable)[MAGIC_MASS_HEAL].Set("MAGIC_MASS_HEAL", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
//	(*g_pActionInfoTable)[MAGIC_MASS_HEAL].SetCastingActionInfo( CASTING_HEALING );	
//	(*g_pActionInfoTable)[MAGIC_MASS_HEAL].SetCastingFramesAll( 24 );
//	(*g_pActionInfoTable)[MAGIC_MASS_HEAL].SetStartFrameAll( 7 );
//	(*g_pActionInfoTable)[MAGIC_MASS_HEAL].SetSoundID( SOUNDID_NULL );	
	
	// MAGIC_RESURRECT
	(*g_pActionInfoTable)[MAGIC_RESURRECT].Set("MAGIC_RESURRECT", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_RESURRECT].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[MAGIC_RESURRECT].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[MAGIC_RESURRECT].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_RESURRECT].SetStartWithCasting();//FrameAll( 7 );
	(*g_pActionInfoTable)[MAGIC_RESURRECT].SetSoundID( SOUNDID_NULL );		
	
	// MAGIC_AURA_STORM,				// MAGIC_AURA_STORM
	/*
	(*g_pActionInfoTable)[MAGIC_AURA_STORM].Set("MAGIC_AURA_STORM", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_AURA_STORM].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[MAGIC_AURA_STORM].SetCastingFramesAll( 8 );
	(*g_pActionInfoTable)[MAGIC_AURA_STORM].SetStartFrameAll( 7 );
	(*g_pActionInfoTable)[MAGIC_AURA_STORM].SetSoundID( SOUNDID_NULL );		
	*/
	

	//-------------------------------------------------------------
	//
	//                       Vampire 마법
	//
	//-------------------------------------------------------------

	// 뱀프기술,
	// SKILL_BLOOD_DRAIN,			// 흡혈


	// MAGIC_AURA_PRISM,							//	Aura Prism				 106
	/*
	(*g_pActionInfoTable)[MAGIC_AURA_PRISM].Set("MAGIC_AURA_PRISM", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	//(*g_pActionInfoTable)[MAGIC_AURA_PRISM].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[MAGIC_AURA_PRISM].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[MAGIC_AURA_PRISM].Init( 2 );		
	(*g_pActionInfoTable)[MAGIC_AURA_PRISM][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[MAGIC_AURA_PRISM][0].EffectSpriteType	= EFFECTSPRITETYPE_AURA_PRISM_1;
	(*g_pActionInfoTable)[MAGIC_AURA_PRISM][0].Step				= 40;
	(*g_pActionInfoTable)[MAGIC_AURA_PRISM][0].Count				= FrameSize[EFFECTSPRITETYPE_AURA_PRISM_1];
	(*g_pActionInfoTable)[MAGIC_AURA_PRISM][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[MAGIC_AURA_PRISM][1].EffectSpriteType	= EFFECTSPRITETYPE_AURA_PRISM_2;
	(*g_pActionInfoTable)[MAGIC_AURA_PRISM][1].Step				= 40;
	(*g_pActionInfoTable)[MAGIC_AURA_PRISM][1].Count				= FrameSize[EFFECTSPRITETYPE_AURA_PRISM_2];
	*/	

	// MAGIC_CHAIN_AURA,							//	Chain Aura 				 107
	(*g_pActionInfoTable)[MAGIC_CHAIN_AURA].Set("MAGIC_CHAIN_AURA", ACTION_MAGIC, EFFECTSPRITETYPE_DARKNESS_1, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_CHAIN_AURA].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[MAGIC_CHAIN_AURA].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[MAGIC_CHAIN_AURA].Init( 1 );		
	(*g_pActionInfoTable)[MAGIC_CHAIN_AURA][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[MAGIC_CHAIN_AURA][0].EffectSpriteType	= EFFECTSPRITETYPE_AURA_BALL_2;
	(*g_pActionInfoTable)[MAGIC_CHAIN_AURA][0].Step				= 40;
	(*g_pActionInfoTable)[MAGIC_CHAIN_AURA][0].Count				= FrameSize[EFFECTSPRITETYPE_AURA_BALL_2];

	// MAGIC_CHRIST_AURA,							//	Christ Aura 			 108
	/*
	(*g_pActionInfoTable)[MAGIC_CHRIST_AURA].Set("MAGIC_CHRIST_AURA", ACTION_MAGIC, EFFECTSPRITETYPE_DARKNESS_1, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_CHRIST_AURA].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[MAGIC_CHRIST_AURA].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[MAGIC_CHRIST_AURA].Init( 1 );		
	(*g_pActionInfoTable)[MAGIC_CHRIST_AURA][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[MAGIC_CHRIST_AURA][0].EffectSpriteType	= EFFECTSPRITETYPE_AURA_BALL_2;
	(*g_pActionInfoTable)[MAGIC_CHRIST_AURA][0].Step				= 40;
	(*g_pActionInfoTable)[MAGIC_CHRIST_AURA][0].Count				= FrameSize[EFFECTSPRITETYPE_AURA_BALL_2];
	*/




	// SKILL_SOUL_CHAIN
	(*g_pActionInfoTable)[SKILL_SOUL_CHAIN].Set("SKILL_SOUL_CHAIN", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 3000);	
	(*g_pActionInfoTable)[SKILL_SOUL_CHAIN].SetSoundID( SOUNDID_NULL );
	
	// SKILL_SHARP_SHIELD
	(*g_pActionInfoTable)[SKILL_SHARP_SHIELD].Set("SKILL_SHARP_SHIELD", ACTION_SLAYER_SWORD_2, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 50);	
	(*g_pActionInfoTable)[SKILL_SHARP_SHIELD].SetSoundID( SOUND_SLAYER_SWORD_SC );
//	(*g_pActionInfoTable)[SKILL_SHARP_SHIELD].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD ); // item을 사용하는 기술이다.
	
	// SKILL_AIR_SHIELD
	(*g_pActionInfoTable)[SKILL_AIR_SHIELD].Set("SKILL_AIR_SHIELD", ACTION_SLAYER_BLADE_2, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 50);	
	(*g_pActionInfoTable)[SKILL_AIR_SHIELD].SetSoundID( SOUND_SLAYER_BLADE_SB );
	
	// SKILL_GUN_SHOT_GUIDANCE
	(*g_pActionInfoTable)[SKILL_GUN_SHOT_GUIDANCE].Set("SKILL_GUN_SHOT_GUIDANCE", ACTION_STAND, EFFECTSPRITETYPE_GUN_SR_MALE, 3, FLAG_ACTIONINFO_TARGET_ZONE | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, 50);	
	(*g_pActionInfoTable)[SKILL_GUN_SHOT_GUIDANCE].SetSoundID( SOUNDID_NULL );
//	(*g_pActionInfoTable)[SKILL_GUN_SHOT_GUIDANCE].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_GUN_SHOT_GUIDANCE].SetStartFrame( 0, 7 );			// slow
	(*g_pActionInfoTable)[SKILL_GUN_SHOT_GUIDANCE].SetStartFrame( 1, 7 );			// normal
	(*g_pActionInfoTable)[SKILL_GUN_SHOT_GUIDANCE].SetStartFrame( 2, 5 );			// fast
//	(*g_pActionInfoTable)[SKILL_GUN_SHOT_GUIDANCE].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_GUN_SHOT_GUIDANCE].SetAffectCurrentWeaponRange();
//	(*g_pActionInfoTable)[SKILL_GUN_SHOT_GUIDANCE].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_GUN_SHOT_GUIDANCE].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_GUN_SHOT_GUIDANCE].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
//	(*g_pActionInfoTable)[SKILL_GUN_SHOT_GUIDANCE].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_GUN_SHOT_GUIDANCE].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용
//	(*g_pActionInfoTable)[SKILL_GUN_SHOT_GUIDANCE].SetSoundID( SOUNDID_NULL );
	

	//-------------------------------------------------------------
	// 늑대 기술
	//-------------------------------------------------------------
	// MAGIC_EAT_CORPSE
	(*g_pActionInfoTable)[MAGIC_EAT_CORPSE].Set("MAGIC_EAT_CORPSE", ACTION_VAMPIRE_DRAIN, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[MAGIC_EAT_CORPSE].SetStartFrameAll( 20 );
	(*g_pActionInfoTable)[MAGIC_EAT_CORPSE].SetSoundID( SOUNDID_NULL );	
	(*g_pActionInfoTable)[MAGIC_EAT_CORPSE].SetSelectCreature(FLAG_ACTIONINFO_SELECT_CORPSE);

	// MAGIC_HOWL
	(*g_pActionInfoTable)[MAGIC_HOWL].Set("MAGIC_HOWL", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_HOWL].SetSoundID( SOUNDID_NULL );


	//-------------------------------------------------------------
	//
	//                          BOMB
	//
	//-------------------------------------------------------------

	// BOMB_ACER
//	(*g_pActionInfoTable)[BOMB_ACER].Set("BOMB_ACER", ACTION_SLAYER_THROW_WEAPON, EFFECTSPRITETYPE_NULL, 7, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_THROW_WEAPON]);
	(*g_pActionInfoTable)[BOMB_ACER].Set("BOMB_ACER", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 7, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[BOMB_ACER].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BOMB ); // item을 사용하는 기술이다.
	(*g_pActionInfoTable)[BOMB_ACER].SetPacketType( ACTIONINFO_PACKET_OTHER );
	(*g_pActionInfoTable)[BOMB_ACER].SetStartFrameAll( 14 );		// 날아가기 시작하는 frame
	//(*g_pActionInfoTable)[BOMB_ACER].SetSoundID( SOUND_ITEM_FLYING_BOMB );
	(*g_pActionInfoTable)[BOMB_ACER].Init( 2 );		
	(*g_pActionInfoTable)[BOMB_ACER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE_BOMB;
	(*g_pActionInfoTable)[BOMB_ACER][0].EffectSpriteType	= EFFECTSPRITETYPE_FLYING_BOMB;
	(*g_pActionInfoTable)[BOMB_ACER][0].Step				= 30;
	(*g_pActionInfoTable)[BOMB_ACER][0].Count				= 1000;//NormalEFPK[(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_FLYING_BOMB].FrameID-MAX_EFFECTSPRITETYPE_ALPHAEFFECT][DIRECTION_DOWN].GetSize();
	(*g_pActionInfoTable)[BOMB_ACER][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[BOMB_ACER][1].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION;
	(*g_pActionInfoTable)[BOMB_ACER][1].Step				= 30;
	(*g_pActionInfoTable)[BOMB_ACER][1].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION];
	(*g_pActionInfoTable)[BOMB_ACER][1].SoundID				= SOUND_SLAYER_ATTACK_BOMB;
	(*g_pActionInfoTable)[BOMB_ACER][1].SetResultTime();
	(*g_pActionInfoTable)[BOMB_ACER].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, BOMB_ACER );	// 맞는 결과를 표현한다.	
	

	// BOMB_BULLS	
//	(*g_pActionInfoTable)[BOMB_BULLS].Set("BOMB_BULLS", ACTION_SLAYER_THROW_WEAPON, EFFECTSPRITETYPE_NULL, 7, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_THROW_WEAPON]);
	(*g_pActionInfoTable)[BOMB_BULLS].Set("BOMB_BULLS", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 7, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[BOMB_BULLS].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BOMB ); // item을 사용하는 기술이다.
	(*g_pActionInfoTable)[BOMB_BULLS].SetPacketType( ACTIONINFO_PACKET_OTHER );
	(*g_pActionInfoTable)[BOMB_BULLS].SetStartFrameAll( 14 );
	//(*g_pActionInfoTable)[BOMB_BULLS].SetSoundID( SOUND_ITEM_FLYING_BOMB );
	(*g_pActionInfoTable)[BOMB_BULLS].Init( 2 );	
	(*g_pActionInfoTable)[BOMB_BULLS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE_BOMB;
	(*g_pActionInfoTable)[BOMB_BULLS][0].EffectSpriteType	= EFFECTSPRITETYPE_FLYING_BOMB;
	(*g_pActionInfoTable)[BOMB_BULLS][0].Step				= 30;
	(*g_pActionInfoTable)[BOMB_BULLS][0].Count				= 1000;//NormalEFPK[(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_FLYING_BOMB].FrameID-MAX_EFFECTSPRITETYPE_ALPHAEFFECT][DIRECTION_DOWN].GetSize();
	(*g_pActionInfoTable)[BOMB_BULLS][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[BOMB_BULLS][1].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION;
	(*g_pActionInfoTable)[BOMB_BULLS][1].Step				= 30;
	(*g_pActionInfoTable)[BOMB_BULLS][1].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION];
	(*g_pActionInfoTable)[BOMB_BULLS][1].SoundID			= SOUND_SLAYER_ATTACK_BOMB;
	(*g_pActionInfoTable)[BOMB_BULLS][1].SetResultTime();	
	(*g_pActionInfoTable)[BOMB_BULLS].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, BOMB_BULLS );	// 맞는 결과를 표현한다.	
	
	// BOMB_SPLINTER(스플린터)
//	(*g_pActionInfoTable)[BOMB_SPLINTER].Set("BOMB_SPLINTER", ACTION_SLAYER_THROW_WEAPON, EFFECTSPRITETYPE_NULL, 7, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_THROW_WEAPON]);	
	(*g_pActionInfoTable)[BOMB_SPLINTER].Set("BOMB_SPLINTER", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 7, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_ATTACK]);	
	(*g_pActionInfoTable)[BOMB_SPLINTER].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BOMB ); // item을 사용하는 기술이다.
	(*g_pActionInfoTable)[BOMB_SPLINTER].SetPacketType( ACTIONINFO_PACKET_OTHER );
	(*g_pActionInfoTable)[BOMB_SPLINTER].SetStartFrameAll( 14 );
	//(*g_pActionInfoTable)[BOMB_SPLINTER].SetSoundID( SOUND_ITEM_FLYING_BOMB );
	(*g_pActionInfoTable)[BOMB_SPLINTER].Init( 2 );	
	(*g_pActionInfoTable)[BOMB_SPLINTER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE_BOMB;
	(*g_pActionInfoTable)[BOMB_SPLINTER][0].EffectSpriteType	= EFFECTSPRITETYPE_FLYING_BOMB;
	(*g_pActionInfoTable)[BOMB_SPLINTER][0].Step				= 30;
	(*g_pActionInfoTable)[BOMB_SPLINTER][0].Count				= 1000;//NormalEFPK[(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_FLYING_BOMB].FrameID-MAX_EFFECTSPRITETYPE_ALPHAEFFECT][DIRECTION_DOWN].GetSize();
	(*g_pActionInfoTable)[BOMB_SPLINTER][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[BOMB_SPLINTER][1].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION_3;
	(*g_pActionInfoTable)[BOMB_SPLINTER][1].Step				= 20;
	(*g_pActionInfoTable)[BOMB_SPLINTER][1].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_3];
	(*g_pActionInfoTable)[BOMB_SPLINTER][1].SoundID				= SOUND_SLAYER_ATTACK_BOMB;
	(*g_pActionInfoTable)[BOMB_SPLINTER].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, BOMB_SPLINTER );	// 맞는 결과를 표현한다.	

	// BOMB_STUN(스턴)
//	(*g_pActionInfoTable)[BOMB_STUN].Set("BOMB_STUN", ACTION_SLAYER_THROW_WEAPON, EFFECTSPRITETYPE_NULL, 7, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_THROW_WEAPON]);
	(*g_pActionInfoTable)[BOMB_STUN].Set("BOMB_STUN", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 7, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[BOMB_STUN].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BOMB ); // item을 사용하는 기술이다.
	(*g_pActionInfoTable)[BOMB_STUN].SetPacketType( ACTIONINFO_PACKET_OTHER );
	(*g_pActionInfoTable)[BOMB_STUN].SetStartFrameAll( 14 );
	//(*g_pActionInfoTable)[BOMB_STUN].SetSoundID( SOUND_ITEM_FLYING_BOMB );
	(*g_pActionInfoTable)[BOMB_STUN].Init( 3 );	
	(*g_pActionInfoTable)[BOMB_STUN][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE_BOMB;
	(*g_pActionInfoTable)[BOMB_STUN][0].EffectSpriteType	= EFFECTSPRITETYPE_FLYING_BOMB;
	(*g_pActionInfoTable)[BOMB_STUN][0].Step				= 30;
	(*g_pActionInfoTable)[BOMB_STUN][0].Count				= 1000;//NormalEFPK[(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_FLYING_BOMB].FrameID-MAX_EFFECTSPRITETYPE_ALPHAEFFECT][DIRECTION_DOWN].GetSize();
	(*g_pActionInfoTable)[BOMB_STUN][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[BOMB_STUN][1].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION_3;
	(*g_pActionInfoTable)[BOMB_STUN][1].Step				= 20;
	(*g_pActionInfoTable)[BOMB_STUN][1].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_3];
	(*g_pActionInfoTable)[BOMB_STUN][1].SoundID				= SOUND_SLAYER_ATTACK_BOMB;	
	(*g_pActionInfoTable)[BOMB_STUN][1].LinkCount			= 4;
	(*g_pActionInfoTable)[BOMB_STUN][1].SetResultTime();
	(*g_pActionInfoTable)[BOMB_STUN][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_EMPTY_HORIZONTAL_WALL;
	(*g_pActionInfoTable)[BOMB_STUN][2].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION_3;
	(*g_pActionInfoTable)[BOMB_STUN][2].Step				= 3;
	(*g_pActionInfoTable)[BOMB_STUN][2].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_3];
	//(*g_pActionInfoTable)[BOMB_STUN][2].SoundID				= SOUND_SLAYER_ATTACK_BOMB;
	(*g_pActionInfoTable)[BOMB_STUN].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, BOMB_STUN);	// 맞는 결과를 표현한다.	

	// BOMB_CROSSBOW
//	(*g_pActionInfoTable)[BOMB_CROSSBOW].Set("BOMB_CROSSBOW", ACTION_SLAYER_THROW_WEAPON, EFFECTSPRITETYPE_NULL, 7, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_THROW_WEAPON]);
	(*g_pActionInfoTable)[BOMB_CROSSBOW].Set("BOMB_CROSSBOW", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 7, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[BOMB_CROSSBOW].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BOMB ); // item을 사용하는 기술이다.
	(*g_pActionInfoTable)[BOMB_CROSSBOW].SetPacketType( ACTIONINFO_PACKET_OTHER );
	(*g_pActionInfoTable)[BOMB_CROSSBOW].SetStartFrameAll( 14 );
	//(*g_pActionInfoTable)[BOMB_CROSSBOW].SetSoundID( SOUND_ITEM_FLYING_BOMB );
	(*g_pActionInfoTable)[BOMB_CROSSBOW].Init( 3 );	
	(*g_pActionInfoTable)[BOMB_CROSSBOW][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE_BOMB;
	(*g_pActionInfoTable)[BOMB_CROSSBOW][0].EffectSpriteType	= EFFECTSPRITETYPE_FLYING_BOMB;
	(*g_pActionInfoTable)[BOMB_CROSSBOW][0].Step				= 30;
	(*g_pActionInfoTable)[BOMB_CROSSBOW][0].Count				= 1000;//NormalEFPK[(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_FLYING_BOMB].FrameID-MAX_EFFECTSPRITETYPE_ALPHAEFFECT][DIRECTION_DOWN].GetSize();
	(*g_pActionInfoTable)[BOMB_CROSSBOW][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[BOMB_CROSSBOW][1].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION_3;
	(*g_pActionInfoTable)[BOMB_CROSSBOW][1].Step				= 20;
	(*g_pActionInfoTable)[BOMB_CROSSBOW][1].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_3];
	(*g_pActionInfoTable)[BOMB_CROSSBOW][1].SoundID				= SOUND_SLAYER_ATTACK_BOMB;	
	(*g_pActionInfoTable)[BOMB_CROSSBOW][1].LinkCount			= 4;;
	(*g_pActionInfoTable)[BOMB_CROSSBOW][1].SetResultTime();
	(*g_pActionInfoTable)[BOMB_CROSSBOW][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_EMPTY_CROSS;
	(*g_pActionInfoTable)[BOMB_CROSSBOW][2].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION_3;
	(*g_pActionInfoTable)[BOMB_CROSSBOW][2].Step				= 20;
	(*g_pActionInfoTable)[BOMB_CROSSBOW][2].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_3];
	//(*g_pActionInfoTable)[BOMB_CROSSBOW][2].SoundID					= 5;
	(*g_pActionInfoTable)[BOMB_CROSSBOW].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, BOMB_CROSSBOW );	// 맞는 결과를 표현한다.	

	// BOMB_TWISTER
#ifdef __EXPO_CLIENT__
	(*g_pActionInfoTable)[BOMB_TWISTER].SetExpoSkill();
#endif
//	(*g_pActionInfoTable)[BOMB_TWISTER].Set("BOMB_TWISTER", ACTION_SLAYER_THROW_WEAPON, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_THROW_WEAPON]);	
	(*g_pActionInfoTable)[BOMB_TWISTER].Set("BOMB_TWISTER", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_ATTACK]);	
	(*g_pActionInfoTable)[BOMB_TWISTER].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BOMB ); // item을 사용하는 기술이다.
	(*g_pActionInfoTable)[BOMB_TWISTER].SetPacketType( ACTIONINFO_PACKET_OTHER );
	(*g_pActionInfoTable)[BOMB_TWISTER].SetStartFrameAll( 14 );
	//(*g_pActionInfoTable)[BOMB_TWISTER].SetSoundID( SOUND_ITEM_FLYING_BOMB );
	(*g_pActionInfoTable)[BOMB_TWISTER].Init( 2 );	
	(*g_pActionInfoTable)[BOMB_TWISTER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE_BOMB;
	(*g_pActionInfoTable)[BOMB_TWISTER][0].EffectSpriteType		= EFFECTSPRITETYPE_FLYING_BOMB;
	(*g_pActionInfoTable)[BOMB_TWISTER][0].Step					= 30;
	(*g_pActionInfoTable)[BOMB_TWISTER][0].Count				= 1000;//NormalEFPK[(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_FLYING_BOMB].FrameID-MAX_EFFECTSPRITETYPE_ALPHAEFFECT][DIRECTION_DOWN].GetSize();
	(*g_pActionInfoTable)[BOMB_TWISTER][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_RECT;
	(*g_pActionInfoTable)[BOMB_TWISTER][1].EffectSpriteType		= EFFECTSPRITETYPE_EXPLOSION_3;
	(*g_pActionInfoTable)[BOMB_TWISTER][1].Step					= 20;
	(*g_pActionInfoTable)[BOMB_TWISTER][1].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_3];
	(*g_pActionInfoTable)[BOMB_TWISTER].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, BOMB_TWISTER );	// 맞는 결과를 표현한다.	
	

	//-------------------------------------------------------------
	//
	//                          MINE
	//
	//-------------------------------------------------------------

	// MINE_ANKLE_KILLER
	(*g_pActionInfoTable)[MINE_ANKLE_KILLER].Set("MINE_ANKLE_KILLER", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MINE_ANKLE_KILLER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MINE_ANKLE_KILLER].Init( 2 );	
	(*g_pActionInfoTable)[MINE_ANKLE_KILLER][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[MINE_ANKLE_KILLER][0].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION_2;
	(*g_pActionInfoTable)[MINE_ANKLE_KILLER][0].Step				= 15;
	(*g_pActionInfoTable)[MINE_ANKLE_KILLER][0].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_2];
	(*g_pActionInfoTable)[MINE_ANKLE_KILLER][0].SoundID				= SOUND_SLAYER_ATTACK_BOMB;
	(*g_pActionInfoTable)[MINE_ANKLE_KILLER][0].LinkCount			= 4;
	(*g_pActionInfoTable)[MINE_ANKLE_KILLER][0].SetResultTime();
	(*g_pActionInfoTable)[MINE_ANKLE_KILLER][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_EMPTY_VERTICAL_WALL;
	(*g_pActionInfoTable)[MINE_ANKLE_KILLER][1].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION_2;
	(*g_pActionInfoTable)[MINE_ANKLE_KILLER][1].Step				= 3;
	(*g_pActionInfoTable)[MINE_ANKLE_KILLER][1].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_2];
	//(*g_pActionInfoTable)[MINE_ANKLE_KILLER][1].SoundID					= 5;
	(*g_pActionInfoTable)[MINE_ANKLE_KILLER].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, MINE_ANKLE_KILLER );	// 맞는 결과를 표현한다.	

	// MINE_POMZ
	(*g_pActionInfoTable)[MINE_POMZ].Set("MINE_POMZ", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MINE_POMZ].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MINE_POMZ].Init( 2 );	
	(*g_pActionInfoTable)[MINE_POMZ][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[MINE_POMZ][0].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION_2;
	(*g_pActionInfoTable)[MINE_POMZ][0].Step				= 15;
	(*g_pActionInfoTable)[MINE_POMZ][0].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_2];
	(*g_pActionInfoTable)[MINE_POMZ][0].SoundID				= SOUND_SLAYER_ATTACK_BOMB;
	(*g_pActionInfoTable)[MINE_POMZ][0].LinkCount			= 4;
	(*g_pActionInfoTable)[MINE_POMZ][0].SetResultTime();
	(*g_pActionInfoTable)[MINE_POMZ][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_EMPTY_HORIZONTAL_WALL;
	(*g_pActionInfoTable)[MINE_POMZ][1].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION_2;
	(*g_pActionInfoTable)[MINE_POMZ][1].Step				= 3;
	(*g_pActionInfoTable)[MINE_POMZ][1].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_2];
	//(*g_pActionInfoTable)[MINE_POMZ][1].SoundID					= 5;
	(*g_pActionInfoTable)[MINE_POMZ].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, MINE_POMZ );	// 맞는 결과를 표현한다.	

	// MINE_AP_C1
	(*g_pActionInfoTable)[MINE_AP_C1].Set("MINE_AP_C1", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MINE_AP_C1].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MINE_AP_C1].Init( 3 );	
	(*g_pActionInfoTable)[MINE_AP_C1][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[MINE_AP_C1][0].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION_2;
	(*g_pActionInfoTable)[MINE_AP_C1][0].Step				= 15;
	(*g_pActionInfoTable)[MINE_AP_C1][0].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_2];
	(*g_pActionInfoTable)[MINE_AP_C1][0].SoundID			= SOUND_SLAYER_ATTACK_BOMB;
	(*g_pActionInfoTable)[MINE_AP_C1][0].LinkCount			= 4;
	(*g_pActionInfoTable)[MINE_AP_C1][1].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_WIDE;
	(*g_pActionInfoTable)[MINE_AP_C1][1].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION_2;
	(*g_pActionInfoTable)[MINE_AP_C1][1].Step				= 15;
	(*g_pActionInfoTable)[MINE_AP_C1][1].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_2];
	(*g_pActionInfoTable)[MINE_AP_C1][1].LinkCount			= 2;
	(*g_pActionInfoTable)[MINE_AP_C1][1].SetResultTime();
	(*g_pActionInfoTable)[MINE_AP_C1][2].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_WIDE;
	(*g_pActionInfoTable)[MINE_AP_C1][2].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION_2;
	(*g_pActionInfoTable)[MINE_AP_C1][2].Step				= 15;
	(*g_pActionInfoTable)[MINE_AP_C1][2].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_2];
	(*g_pActionInfoTable)[MINE_AP_C1].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, MINE_AP_C1 );	// 맞는 결과를 표현한다.	
	/*
	(*g_pActionInfoTable)[MINE_AP_C1][1].LinkCount			= 3;
	(*g_pActionInfoTable)[MINE_AP_C1][2].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_WIDE;
	(*g_pActionInfoTable)[MINE_AP_C1][2].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION;
	(*g_pActionInfoTable)[MINE_AP_C1][2].Step				= 15;
	(*g_pActionInfoTable)[MINE_AP_C1][2].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION];
	(*g_pActionInfoTable)[MINE_AP_C1][2].SoundID					= 6;
	*/

		// MINE_DIAMONDBACK	
	(*g_pActionInfoTable)[MINE_DIAMONDBACK].Set("MINE_DIAMONDBACK", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MINE_DIAMONDBACK].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MINE_DIAMONDBACK].Init( 2 );	
	(*g_pActionInfoTable)[MINE_DIAMONDBACK][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[MINE_DIAMONDBACK][0].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION_2;
	(*g_pActionInfoTable)[MINE_DIAMONDBACK][0].Step				= 15;
	(*g_pActionInfoTable)[MINE_DIAMONDBACK][0].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_2];
	(*g_pActionInfoTable)[MINE_DIAMONDBACK][0].SoundID					= SOUND_SLAYER_ATTACK_BOMB;
	(*g_pActionInfoTable)[MINE_DIAMONDBACK][0].SetResultTime();
	(*g_pActionInfoTable)[MINE_DIAMONDBACK][0].LinkCount			= 4;
	(*g_pActionInfoTable)[MINE_DIAMONDBACK][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_EMPTY_CROSS;
	(*g_pActionInfoTable)[MINE_DIAMONDBACK][1].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION_2;
	(*g_pActionInfoTable)[MINE_DIAMONDBACK][1].Step				= 15;
	(*g_pActionInfoTable)[MINE_DIAMONDBACK][1].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_2];	
	(*g_pActionInfoTable)[MINE_DIAMONDBACK].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, MINE_DIAMONDBACK );	// 맞는 결과를 표현한다.	

	// MINE_SWIFT_EX
	(*g_pActionInfoTable)[MINE_SWIFT_EX].Set("MINE_SWIFT_EX", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MINE_SWIFT_EX].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MINE_SWIFT_EX].Init( 2 );	
	(*g_pActionInfoTable)[MINE_SWIFT_EX][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[MINE_SWIFT_EX][0].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION_2;
	(*g_pActionInfoTable)[MINE_SWIFT_EX][0].Step				= 15;
	(*g_pActionInfoTable)[MINE_SWIFT_EX][0].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_2];
	(*g_pActionInfoTable)[MINE_SWIFT_EX][0].SoundID					= SOUND_SLAYER_ATTACK_BOMB;
	(*g_pActionInfoTable)[MINE_SWIFT_EX][0].LinkCount			= 4;
	(*g_pActionInfoTable)[MINE_SWIFT_EX][0].SetResultTime();
	(*g_pActionInfoTable)[MINE_SWIFT_EX][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_EMPTY_RECT;
	(*g_pActionInfoTable)[MINE_SWIFT_EX][1].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION_2;
	(*g_pActionInfoTable)[MINE_SWIFT_EX][1].Step				= 15;
	(*g_pActionInfoTable)[MINE_SWIFT_EX][1].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_2];
	(*g_pActionInfoTable)[MINE_SWIFT_EX].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, MINE_SWIFT_EX );	// 맞는 결과를 표현한다.			
	


	// MINE_SIDEWINDER	
	(*g_pActionInfoTable)[MINE_SIDEWINDER].Set("MINE_SIDEWINDER", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MINE_SIDEWINDER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MINE_SIDEWINDER].Init( 5 );	
	(*g_pActionInfoTable)[MINE_SIDEWINDER][0].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE;
	(*g_pActionInfoTable)[MINE_SIDEWINDER][0].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION_2;
	(*g_pActionInfoTable)[MINE_SIDEWINDER][0].Step				= 15;
	(*g_pActionInfoTable)[MINE_SIDEWINDER][0].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_2];
	(*g_pActionInfoTable)[MINE_SIDEWINDER][0].LinkCount			= 4;
	(*g_pActionInfoTable)[MINE_SIDEWINDER][0].SetResultTime();
	(*g_pActionInfoTable)[MINE_SIDEWINDER][0].SoundID					= SOUND_SLAYER_ATTACK_BOMB;
	(*g_pActionInfoTable)[MINE_SIDEWINDER][1].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE;
	(*g_pActionInfoTable)[MINE_SIDEWINDER][1].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION_2;
	(*g_pActionInfoTable)[MINE_SIDEWINDER][1].Step				= 15;
	(*g_pActionInfoTable)[MINE_SIDEWINDER][1].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_2];
	(*g_pActionInfoTable)[MINE_SIDEWINDER][1].LinkCount			= 4;
	(*g_pActionInfoTable)[MINE_SIDEWINDER][1].SoundID					= SOUND_SLAYER_ATTACK_BOMB;
	(*g_pActionInfoTable)[MINE_SIDEWINDER][2].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE;
	(*g_pActionInfoTable)[MINE_SIDEWINDER][2].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION_2;
	(*g_pActionInfoTable)[MINE_SIDEWINDER][2].Step				= 15;
	(*g_pActionInfoTable)[MINE_SIDEWINDER][2].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_2];
	(*g_pActionInfoTable)[MINE_SIDEWINDER][2].LinkCount			= 4;
	(*g_pActionInfoTable)[MINE_SIDEWINDER][2].SoundID					= SOUND_SLAYER_ATTACK_BOMB;
	(*g_pActionInfoTable)[MINE_SIDEWINDER][3].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE;
	(*g_pActionInfoTable)[MINE_SIDEWINDER][3].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION_2;
	(*g_pActionInfoTable)[MINE_SIDEWINDER][3].Step				= 15;
	(*g_pActionInfoTable)[MINE_SIDEWINDER][3].LinkCount			= 4;
	(*g_pActionInfoTable)[MINE_SIDEWINDER][3].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_2];
	(*g_pActionInfoTable)[MINE_SIDEWINDER][3].SoundID					= SOUND_SLAYER_ATTACK_BOMB;
	(*g_pActionInfoTable)[MINE_SIDEWINDER][4].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE;
	(*g_pActionInfoTable)[MINE_SIDEWINDER][4].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION_2;
	(*g_pActionInfoTable)[MINE_SIDEWINDER][4].Step				= 15;
	(*g_pActionInfoTable)[MINE_SIDEWINDER][4].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_2];
	(*g_pActionInfoTable)[MINE_SIDEWINDER][4].SoundID					= SOUND_SLAYER_ATTACK_BOMB;
	(*g_pActionInfoTable)[MINE_SIDEWINDER].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, MINE_SIDEWINDER );	// 맞는 결과를 표현한다.	

	// MINE_COBRA
	(*g_pActionInfoTable)[MINE_COBRA].Set("MINE_COBRA", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MINE_COBRA].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MINE_COBRA].Init( 3 );	
	(*g_pActionInfoTable)[MINE_COBRA][0].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_WIDE;
	(*g_pActionInfoTable)[MINE_COBRA][0].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION_2;
	(*g_pActionInfoTable)[MINE_COBRA][0].Step				= 15;
	(*g_pActionInfoTable)[MINE_COBRA][0].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_2];
	(*g_pActionInfoTable)[MINE_COBRA][0].SetResultTime();
	(*g_pActionInfoTable)[MINE_COBRA][0].LinkCount			= 4;
	(*g_pActionInfoTable)[MINE_COBRA][1].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_WIDE;
	(*g_pActionInfoTable)[MINE_COBRA][1].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION_2;
	(*g_pActionInfoTable)[MINE_COBRA][1].Step				= 15;
	(*g_pActionInfoTable)[MINE_COBRA][1].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_2];
	(*g_pActionInfoTable)[MINE_COBRA][1].LinkCount			= 4;
	(*g_pActionInfoTable)[MINE_COBRA][2].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_WIDE;
	(*g_pActionInfoTable)[MINE_COBRA][2].EffectSpriteType	= EFFECTSPRITETYPE_EXPLOSION_2;
	(*g_pActionInfoTable)[MINE_COBRA][2].Step				= 15;
	(*g_pActionInfoTable)[MINE_COBRA][2].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION_2];
	(*g_pActionInfoTable)[MINE_COBRA][2].SoundID					= SOUND_SLAYER_ATTACK_BOMB;
	(*g_pActionInfoTable)[MINE_COBRA].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, MINE_COBRA );	// 맞는 결과를 표현한다.	

	//-------------------------------------------------------------
	//
	//                          ETC
	//
	//-------------------------------------------------------------	

	/*
	// SKILL_THROW_HOLY_WATER
	(*g_pActionInfoTable)[SKILL_THROW_HOLY_WATER].Set("SKILL_THROW_HOLY_WATER", ACTION_SLAYER_THROW_POTION, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_THROW_POTION]);
	(*g_pActionInfoTable)[SKILL_THROW_HOLY_WATER].SetWeaponType( FLAG_ACTIONINFO_WEAPON_HOLY_WATER ); // item을 사용하는 기술이다.
	(*g_pActionInfoTable)[SKILL_THROW_HOLY_WATER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_THROW_HOLY_WATER].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_THROW_HOLY_WATER].Init( 1 );
	(*g_pActionInfoTable)[SKILL_THROW_HOLY_WATER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE_PARABOLA;
	(*g_pActionInfoTable)[SKILL_THROW_HOLY_WATER][0].EffectSpriteType	= EFFECTSPRITETYPE_FLYING_HOLY_WATER;
	(*g_pActionInfoTable)[SKILL_THROW_HOLY_WATER][0].Step				= 30;
	(*g_pActionInfoTable)[SKILL_THROW_HOLY_WATER][0].Count				= 48;//NormalEFPK[(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_FLYING_HOLY_WATER].FrameID-MAX_EFFECTSPRITETYPE_ALPHAEFFECT][DIRECTION_DOWN].GetSize();	
	(*g_pActionInfoTable)[SKILL_THROW_HOLY_WATER][0].SoundID			= SOUND_ITEM_FLYING_BOTTLE;
	*/
	// MAGIC_THROW_HOLY_WATER
//	(*g_pActionInfoTable)[MAGIC_THROW_HOLY_WATER].Set("MAGIC_THROW_HOLY_WATER", ACTION_SLAYER_THROW_POTION, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_THROW_POTION]);
	(*g_pActionInfoTable)[MAGIC_THROW_HOLY_WATER].Set("MAGIC_THROW_HOLY_WATER", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[MAGIC_THROW_HOLY_WATER].SetWeaponType( FLAG_ACTIONINFO_WEAPON_HOLY_WATER ); // item을 사용하는 기술이다.
	(*g_pActionInfoTable)[MAGIC_THROW_HOLY_WATER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAGIC_THROW_HOLY_WATER].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[MAGIC_THROW_HOLY_WATER].Init( 1 );
	(*g_pActionInfoTable)[MAGIC_THROW_HOLY_WATER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE_PARABOLA;
	(*g_pActionInfoTable)[MAGIC_THROW_HOLY_WATER][0].EffectSpriteType	= EFFECTSPRITETYPE_FLYING_HOLY_WATER;
	(*g_pActionInfoTable)[MAGIC_THROW_HOLY_WATER][0].Step				= 30;
	(*g_pActionInfoTable)[MAGIC_THROW_HOLY_WATER][0].Count				= 48;//NormalEFPK[(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_FLYING_HOLY_WATER].FrameID-MAX_EFFECTSPRITETYPE_ALPHAEFFECT][DIRECTION_DOWN].GetSize();	
	(*g_pActionInfoTable)[MAGIC_THROW_HOLY_WATER][0].SoundID			= SOUND_THROW_HOLY_WATER ; //SOUND_ITEM_FLYING_BOTTLE;
	

	// GUIDANCE_FIRE
	(*g_pActionInfoTable)[GUIDANCE_FIRE].Set("GUIDANCE_FIRE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET | FLAG_ACTIONINFO_START_SKY, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[GUIDANCE_FIRE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[GUIDANCE_FIRE].Init( 2 );
	(*g_pActionInfoTable)[GUIDANCE_FIRE][0].EffectGeneratorID	= EFFECTGENERATORID_MULTIPLE_FALLING;
	(*g_pActionInfoTable)[GUIDANCE_FIRE][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_BALL_2_MALE;
	(*g_pActionInfoTable)[GUIDANCE_FIRE][0].Step				= 30;
	(*g_pActionInfoTable)[GUIDANCE_FIRE][0].Count				= 17;//FrameSize[EFFECTSPRITETYPE_AURA_BALL_2];
	(*g_pActionInfoTable)[GUIDANCE_FIRE][1].EffectGeneratorID	= EFFECTGENERATORID_SPREAD_OUT;
	(*g_pActionInfoTable)[GUIDANCE_FIRE][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_KNIFE_1;
	(*g_pActionInfoTable)[GUIDANCE_FIRE][1].Step				= 30;
	(*g_pActionInfoTable)[GUIDANCE_FIRE][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_KNIFE_1];
	
	/*
	(*g_pActionInfoTable)[GUIDANCE_FIRE].Set("GUIDANCE_FIRE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET | FLAG_ACTIONINFO_START_SKY, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[GUIDANCE_FIRE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[GUIDANCE_FIRE].Init( 5 );
	(*g_pActionInfoTable)[GUIDANCE_FIRE][0].EffectGeneratorID	= EFFECTGENERATORID_MULTIPLE_FALLING;
	(*g_pActionInfoTable)[GUIDANCE_FIRE][0].EffectSpriteType	= EFFECTSPRITETYPE_ACID_BALL_1;
	(*g_pActionInfoTable)[GUIDANCE_FIRE][0].Step				= 30;
	(*g_pActionInfoTable)[GUIDANCE_FIRE][0].Count				= 17;//FrameSize[EFFECTSPRITETYPE_AURA_BALL_2];
	(*g_pActionInfoTable)[GUIDANCE_FIRE][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[GUIDANCE_FIRE][1].EffectSpriteType	= EFFECTSPRITETYPE_ACID_BALL_2;
	(*g_pActionInfoTable)[GUIDANCE_FIRE][1].Step				= 30;
	(*g_pActionInfoTable)[GUIDANCE_FIRE][1].Count				= FrameSize[EFFECTSPRITETYPE_ACID_BALL_2];
	(*g_pActionInfoTable)[GUIDANCE_FIRE][1].LinkCount			= 1;
	(*g_pActionInfoTable)[GUIDANCE_FIRE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[GUIDANCE_FIRE][2].EffectSpriteType	= EFFECTSPRITETYPE_ACID_SWAP_1;
	(*g_pActionInfoTable)[GUIDANCE_FIRE][2].Step				= 15;
	(*g_pActionInfoTable)[GUIDANCE_FIRE][2].Count				= FrameSize[EFFECTSPRITETYPE_ACID_SWAP_1];	
	(*g_pActionInfoTable)[GUIDANCE_FIRE][3].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[GUIDANCE_FIRE][3].EffectSpriteType	= EFFECTSPRITETYPE_ACID_SWAP_2;
	(*g_pActionInfoTable)[GUIDANCE_FIRE][3].Step				= 15;
	(*g_pActionInfoTable)[GUIDANCE_FIRE][3].Count				= FrameSize[EFFECTSPRITETYPE_ACID_SWAP_2];	
	(*g_pActionInfoTable)[GUIDANCE_FIRE][3].SetDelayNode();
	(*g_pActionInfoTable)[GUIDANCE_FIRE][4].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[GUIDANCE_FIRE][4].EffectSpriteType	= EFFECTSPRITETYPE_ACID_SWAP_3;
	(*g_pActionInfoTable)[GUIDANCE_FIRE][4].Step				= 15;
	(*g_pActionInfoTable)[GUIDANCE_FIRE][4].Count				= FrameSize[EFFECTSPRITETYPE_ACID_SWAP_3];	
	*/

	// FALLING_LIGHTNING
	(*g_pActionInfoTable)[FALLING_LIGHTNING].Set("FALLING_LIGHTNING", ACTION_MAGIC, EFFECTSPRITETYPE_GREEN_STALKER_1, 8, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET | FLAG_ACTIONINFO_START_SKY, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[FALLING_LIGHTNING].SetCastingFramesAll( 16 );
	(*g_pActionInfoTable)[FALLING_LIGHTNING].SetStartFrameAll( 16 );
	(*g_pActionInfoTable)[FALLING_LIGHTNING].SetSoundID( SOUND_VAMPIRE_GREENSTALKER1 );
	(*g_pActionInfoTable)[FALLING_LIGHTNING].Init( 2 );
	(*g_pActionInfoTable)[FALLING_LIGHTNING][0].EffectGeneratorID	= EFFECTGENERATORID_MULTIPLE_FALLING;
	(*g_pActionInfoTable)[FALLING_LIGHTNING][0].EffectSpriteType	= EFFECTSPRITETYPE_ACID_BOLT_1;
	(*g_pActionInfoTable)[FALLING_LIGHTNING][0].Step				= 30;
	(*g_pActionInfoTable)[FALLING_LIGHTNING][0].Count				= 17;//FrameSize[EFFECTSPRITETYPE_AURA_BALL_2];
	(*g_pActionInfoTable)[FALLING_LIGHTNING][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[FALLING_LIGHTNING][1].EffectSpriteType	= EFFECTSPRITETYPE_SMOKE;
	(*g_pActionInfoTable)[FALLING_LIGHTNING][1].Step				= 25;
	(*g_pActionInfoTable)[FALLING_LIGHTNING][1].Count				= FrameSize[EFFECTSPRITETYPE_SMOKE];
	(*g_pActionInfoTable)[FALLING_LIGHTNING][1].SoundID				= SOUND_VAMPIRE_ACIDBURN;
	/*
	(*g_pActionInfoTable)[FALLING_LIGHTNING].Set("FALLING_LIGHTNING", ACTION_MAGIC, EFFECTSPRITETYPE_AURA_BALL_1, 8, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET | FLAG_ACTIONINFO_START_SKY, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[FALLING_LIGHTNING].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[FALLING_LIGHTNING].Init( 2 );
	(*g_pActionInfoTable)[FALLING_LIGHTNING][0].EffectGeneratorID	= EFFECTGENERATORID_MULTIPLE_FALLING;
	(*g_pActionInfoTable)[FALLING_LIGHTNING][0].EffectSpriteType	= EFFECTSPRITETYPE_AURA_BALL_2;
	(*g_pActionInfoTable)[FALLING_LIGHTNING][0].Step				= 30;
	(*g_pActionInfoTable)[FALLING_LIGHTNING][0].Count				= 17;//FrameSize[EFFECTSPRITETYPE_AURA_BALL_2];
	(*g_pActionInfoTable)[FALLING_LIGHTNING][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[FALLING_LIGHTNING][1].EffectSpriteType	= EFFECTSPRITETYPE_AURA_BALL_3;
	(*g_pActionInfoTable)[FALLING_LIGHTNING][1].Step				= 15;
	(*g_pActionInfoTable)[FALLING_LIGHTNING][1].Count				= FrameSize[EFFECTSPRITETYPE_AURA_BALL_3];	
	*/
	
	// ATTACH_FIRE
	(*g_pActionInfoTable)[ATTACH_FIRE].Set("ATTACH_FIRE", ACTION_MAGIC, EFFECTSPRITETYPE_BLOOD_DRAIN_2, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[ATTACH_FIRE].SetCastingFramesAll( 16 );
	(*g_pActionInfoTable)[ATTACH_FIRE].SetStartFrameAll( 16 );
	(*g_pActionInfoTable)[ATTACH_FIRE].SetSoundID( SOUND_VAMPIRE_GREENSTALKER1 );
	(*g_pActionInfoTable)[ATTACH_FIRE].Init( 2 );		
	(*g_pActionInfoTable)[ATTACH_FIRE][0].EffectGeneratorID	= EFFECTGENERATORID_SPREAD_OUT;
	(*g_pActionInfoTable)[ATTACH_FIRE][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_KNIFE_1;
	(*g_pActionInfoTable)[ATTACH_FIRE][0].Step				= 15;
	(*g_pActionInfoTable)[ATTACH_FIRE][0].Count				= 10;//FrameSize[EFFECTSPRITETYPE_ACID_BOLT_1];
	(*g_pActionInfoTable)[ATTACH_FIRE][0].SoundID			= SOUND_VAMPIRE_GREENSTALKER2;
	(*g_pActionInfoTable)[ATTACH_FIRE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[ATTACH_FIRE][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_KNIFE_1;
	(*g_pActionInfoTable)[ATTACH_FIRE][1].Step				= 25;
	(*g_pActionInfoTable)[ATTACH_FIRE][1].Count				= 2*16;//FrameSize[EFFECTSPRITETYPE_ACID_BOLT_1];	

	// ATTACH_AURA
	(*g_pActionInfoTable)[ATTACH_AURA].Set("ATTACH_AURA", ACTION_MAGIC, EFFECTSPRITETYPE_GREEN_STALKER_1, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[ATTACH_AURA].SetCastingFramesAll( 16 );
	(*g_pActionInfoTable)[ATTACH_AURA].SetStartFrameAll( 16 );
	(*g_pActionInfoTable)[ATTACH_AURA].SetSoundID( SOUND_VAMPIRE_GREENSTALKER1 );
	(*g_pActionInfoTable)[ATTACH_AURA].Init( 2 );		
	(*g_pActionInfoTable)[ATTACH_AURA][0].EffectGeneratorID	= EFFECTGENERATORID_SPREAD_OUT;
	(*g_pActionInfoTable)[ATTACH_AURA][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_FLY_GREEN_STALKER;//EFFECTSPRITETYPE_GREEN_STALKER_2;
	(*g_pActionInfoTable)[ATTACH_AURA][0].Step				= 15;
	(*g_pActionInfoTable)[ATTACH_AURA][0].Count				= 10;//FrameSize[EFFECTSPRITETYPE_ACID_BOLT_1];
	(*g_pActionInfoTable)[ATTACH_AURA][0].SoundID			= SOUND_VAMPIRE_GREENSTALKER2;
	(*g_pActionInfoTable)[ATTACH_AURA][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[ATTACH_AURA][1].EffectSpriteType	= EFFECTSPRITETYPE_NEW_FLY_GREEN_STALKER;//EFFECTSPRITETYPE_GREEN_STALKER_2;
	(*g_pActionInfoTable)[ATTACH_AURA][1].Step				= 25;
	(*g_pActionInfoTable)[ATTACH_AURA][1].Count				= 2*16;//FrameSize[EFFECTSPRITETYPE_ACID_BOLT_1];	
	/*
	(*g_pActionInfoTable)[ATTACH_AURA].Set("ATTACH_AURA", ACTION_MAGIC, EFFECTSPRITETYPE_GREEN_STALKER_1, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[ATTACH_AURA].SetCastingFramesAll( 16 );
	(*g_pActionInfoTable)[ATTACH_AURA].SetStartFrameAll( 16 );
	(*g_pActionInfoTable)[ATTACH_AURA].SetSoundID( SOUND_VAMPIRE_GREENSTALKER1 );
	(*g_pActionInfoTable)[ATTACH_AURA].Init( 2 );		
	(*g_pActionInfoTable)[ATTACH_AURA][0].EffectGeneratorID	= EFFECTGENERATORID_SPREAD_OUT;
	(*g_pActionInfoTable)[ATTACH_AURA][0].EffectSpriteType	= EFFECTSPRITETYPE_ACID_BOLT_1;
	(*g_pActionInfoTable)[ATTACH_AURA][0].Step				= 15;
	(*g_pActionInfoTable)[ATTACH_AURA][0].Count				= 10;//FrameSize[EFFECTSPRITETYPE_ACID_BOLT_1];
	(*g_pActionInfoTable)[ATTACH_AURA][0].SoundID			= SOUND_VAMPIRE_GREENSTALKER2;
	(*g_pActionInfoTable)[ATTACH_AURA][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[ATTACH_AURA][1].EffectSpriteType	= EFFECTSPRITETYPE_ACID_BOLT_1;
	(*g_pActionInfoTable)[ATTACH_AURA][1].Step				= 25;
	(*g_pActionInfoTable)[ATTACH_AURA][1].Count				= 2*16;//FrameSize[EFFECTSPRITETYPE_ACID_BOLT_1];	
	*/

	//--------------------------------------------------------------------
	//
	//         RESULT ActionInfoTable 정보 생성
	//
	//--------------------------------------------------------------------
		
	//-------------------------------------------------------------
	//
	//                         기본 기술
	//
	//-------------------------------------------------------------
	// SKILL_ATTACK_MELEE,	// 기본 공격
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_MELEE].Set("RESULT_SKILL_ATTACK_MELEE", ACTION_DAMAGED, EFFECTSPRITETYPE_BLOOD, 0, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 80);
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_MELEE].SetSoundID( SOUND_DAMAGE_GUN );
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_MELEE].SetCastingFramesAll( 6 );

	// RESULT_SKILL_ATTACK_ARMS,	// 기본 공격
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_ARMS].Set("RESULT_SKILL_ATTACK_ARMS", ACTION_ATTACK, EFFECTSPRITETYPE_BLOOD, 5, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 80);
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_ARMS].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_ARMS].SetCastingFramesAll( 6 );

	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_GUN_SR].Set("RESULT_SKILL_ATTACK_GUN_SR", ACTION_DAMAGED, EFFECTSPRITETYPE_BLOOD_GUN_1_1, 0, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 80);
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_GUN_SR].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_GUN_SR].SetCastingFramesAll( 6 );
	
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_GUN_SG].Set("RESULT_SKILL_ATTACK_GUN_SG", ACTION_DAMAGED, EFFECTSPRITETYPE_BLOOD_GUN_3_1, 0, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 80);
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_GUN_SG].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_GUN_SG].SetCastingFramesAll( 6 );

	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_GUN_AR].Set("RESULT_SKILL_ATTACK_GUN_AR", ACTION_DAMAGED, EFFECTSPRITETYPE_BLOOD_GUN_2_1, 0, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 80);
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_GUN_AR].SetSoundID( SOUND_DAMAGE_GUN );
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_GUN_AR].SetCastingFramesAll( 6 );
	
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_GUN_SMG].Set("RESULT_SKILL_ATTACK_GUN_SMG", ACTION_DAMAGED, EFFECTSPRITETYPE_BLOOD_GUN_2_1, 0, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 80);
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_GUN_SMG].SetSoundID( SOUND_DAMAGE_GUN );
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_GUN_SMG].SetCastingFramesAll( 6 );
	
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_SWORD].Set("RESULT_SKILL_ATTACK_SWORD", ACTION_DAMAGED, EFFECTSPRITETYPE_BLOOD_VERTICAL_1, 0, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 80);
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_SWORD].SetSoundID( SOUND_DAMAGE_GUN );
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_SWORD].SetCastingFramesAll( 6 );

	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_BLADE].Set("RESULT_SKILL_ATTACK_BLADE", ACTION_DAMAGED, EFFECTSPRITETYPE_BLOOD_VERTICAL_1, 0, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 80);
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_BLADE].SetSoundID( SOUND_DAMAGE_GUN );
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_BLADE].SetCastingFramesAll( 6 );

	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_ARMS].Set("RESULT_SKILL_ATTACK_ARMS", ACTION_ATTACK, EFFECTSPRITETYPE_BLOOD, 5, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 80);
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_ARMS].SetSoundID( SOUNDID_NULL );	
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_ARMS].SetCastingFramesAll( 6 );

//	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SHOOTING_TR].Set("RESULT_SKILL_HOLY_SHOOTING_TR", ACTION_DAMAGED, EFFECTSPRITETYPE_HOLY_SHOOTING_HIT, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
//	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SHOOTING_TR].SetCastingFramesAll( 8 );
//	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SHOOTING_TR].SetSoundID( SOUND_DAMAGE_GUN );
	
//	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SHOOTING_SG].Set("RESULT_SKILL_HOLY_SHOOTING_SG", ACTION_DAMAGED, EFFECTSPRITETYPE_HOLY_SHOOTING_HIT, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
//	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SHOOTING_SG].SetCastingFramesAll( 8 );
//	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SHOOTING_SG].SetSoundID( SOUND_DAMAGE_GUN );
	
//	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SHOOTING_AR].Set("RESULT_SKILL_HOLY_SHOOTING_AR", ACTION_DAMAGED, EFFECTSPRITETYPE_HOLY_SHOOTING_HIT, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
//	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SHOOTING_AR].SetCastingFramesAll( 8 );
//	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SHOOTING_AR].SetSoundID( SOUND_DAMAGE_GUN );
	
//	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SHOOTING_SMG].Set("RESULT_SKILL_HOLY_SHOOTING_SMG", ACTION_DAMAGED, EFFECTSPRITETYPE_HOLY_SHOOTING_HIT, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
//	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SHOOTING_SMG].SetCastingFramesAll( 8 );
//	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SHOOTING_SMG].SetSoundID( SOUND_DAMAGE_GUN );
	
	//-------------------------------------------------------------
	//
	//                         테스트 용
	//
	//-------------------------------------------------------------
	// RESULT_SKILL_SELF
	(*g_pActionInfoTable)[RESULT_SKILL_SELF].Set("RESULT_SKILL_SELF", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_SELF].SetSoundID( SOUNDID_NULL );

	// RESULT_SKILL_TILE
	(*g_pActionInfoTable)[RESULT_SKILL_TILE].Set("RESULT_SKILL_TILE", ACTION_DAMAGED, EFFECTSPRITETYPE_BLOOD, 0, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 80);
	(*g_pActionInfoTable)[RESULT_SKILL_TILE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_TILE].SetCastingFramesAll( 6 );

	// RESULT_SKILL_OBJECT
	(*g_pActionInfoTable)[RESULT_SKILL_OBJECT].Set("RESULT_SKILL_OBJECT", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_SKILL_OBJECT].SetSoundID( SOUNDID_NULL );
	
	//-------------------------------------------------------------
	//
	//                         검 계열
	//
	//-------------------------------------------------------------
	// SKILL_DOUBLE_IMPACT
	(*g_pActionInfoTable)[RESULT_SKILL_DOUBLE_IMPACT].Set("RESULT_SKILL_DOUBLE_IMPACT", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 100);	
	(*g_pActionInfoTable)[RESULT_SKILL_DOUBLE_IMPACT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_DOUBLE_IMPACT].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_DOUBLE_IMPACT].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SKILL_DOUBLE_IMPACT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_DOUBLE_IMPACT][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_DOUBLE_IMPACT][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_DOUBLE_IMPACT][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	
	
    // SKILL_TRIPLE_SLASHER
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_SLASHER].Set("RESULT_SKILL_TRIPLE_SLASHER", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 100);	
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_SLASHER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_SLASHER].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_SLASHER].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_SLASHER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_SLASHER][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_SLASHER][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_SLASHER][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_SLASHER][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_SLASHER][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_SLASHER][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_SLASHER][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_SLASHER][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_SLASHER][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_SLASHER][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_SLASHER][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	// SKILL_SCREW_SLASHER
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_SCREW_SLASHER].Set("RESULT_SKILL_SCREW_SLASHER", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 100);
	(*g_pActionInfoTable)[RESULT_SKILL_SCREW_SLASHER].SetSoundID( SOUNDID_NULL );
	*/

    // SKILL_RAINBOW_SLASHER
	(*g_pActionInfoTable)[RESULT_SKILL_RAINBOW_SLASHER].Set("RESULT_SKILL_RAINBOW_SLASHER", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 100);
	(*g_pActionInfoTable)[RESULT_SKILL_RAINBOW_SLASHER].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_SKILL_RAINBOW_SLASHER].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_RAINBOW_SLASHER].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_SKILL_RAINBOW_SLASHER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_RAINBOW_SLASHER][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_RAINBOW_SLASHER][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_RAINBOW_SLASHER][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_SKILL_RAINBOW_SLASHER][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_RAINBOW_SLASHER][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_RAINBOW_SLASHER][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_RAINBOW_SLASHER][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_SKILL_RAINBOW_SLASHER][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_RAINBOW_SLASHER][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_RAINBOW_SLASHER][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_RAINBOW_SLASHER][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];

    // SKILL_THUNDER_SPARK
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_SPARK].Set("RESULT_SKILL_THUNDER_SPARK", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 100);
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_SPARK].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_SPARK].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_SPARK].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_SPARK][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_SPARK][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_SPARK][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_SPARK][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_SPARK][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_SPARK][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_SPARK][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_SPARK][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_SPARK][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_SPARK][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_SPARK][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_SPARK][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];

	// SKILL_DANCING_SWORD
	(*g_pActionInfoTable)[RESULT_SKILL_DANCING_SWORD].Set("RESULT_SKILL_DANCING_SWORD", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 100);
	(*g_pActionInfoTable)[RESULT_SKILL_DANCING_SWORD].SetSoundID( SOUNDID_NULL );
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_DANCING_SWORD].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_DANCING_SWORD].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_SKILL_DANCING_SWORD][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_DANCING_SWORD][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_DANCING_SWORD][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_DANCING_SWORD][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_SKILL_DANCING_SWORD][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_DANCING_SWORD][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_DANCING_SWORD][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_DANCING_SWORD][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_SKILL_DANCING_SWORD][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_DANCING_SWORD][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_DANCING_SWORD][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_DANCING_SWORD][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	*/

	// SKILL_CRUSH_COMBO
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_CRUSH_COMBO].Set("SKILL_CRUSH_COMBO", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 100);
	(*g_pActionInfoTable)[RESULT_SKILL_CRUSH_COMBO].SetSoundID( SOUNDID_NULL );
	*/

    // SKILL_HURRICANE_COMBO
	(*g_pActionInfoTable)[RESULT_SKILL_HURRICANE_COMBO].Set("RESULT_SKILL_HURRICANE_COMBO", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 100);
	(*g_pActionInfoTable)[RESULT_SKILL_HURRICANE_COMBO].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_HURRICANE_COMBO].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_HURRICANE_COMBO].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_SKILL_HURRICANE_COMBO][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_HURRICANE_COMBO][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_HURRICANE_COMBO][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_HURRICANE_COMBO][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_SKILL_HURRICANE_COMBO][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_HURRICANE_COMBO][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_HURRICANE_COMBO][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_HURRICANE_COMBO][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_SKILL_HURRICANE_COMBO][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_HURRICANE_COMBO][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_HURRICANE_COMBO][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_HURRICANE_COMBO][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];

    // SKILL_CHAOS_COMBO
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_CHAOS_COMBO].Set("RESULT_SKILL_CHAOS_COMBO", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 100);
	(*g_pActionInfoTable)[RESULT_SKILL_CHAOS_COMBO].SetSoundID( SOUNDID_NULL );
	*/

    // SKILL_SNAKE_COMBO
	(*g_pActionInfoTable)[RESULT_SKILL_SNAKE_COMBO].Set("RESULT_SKILL_SNAKE_COMBO", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 100);
	(*g_pActionInfoTable)[RESULT_SKILL_SNAKE_COMBO].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_SNAKE_COMBO].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_SNAKE_COMBO].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_SKILL_SNAKE_COMBO][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_SNAKE_COMBO][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_SNAKE_COMBO][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_SNAKE_COMBO][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_SKILL_SNAKE_COMBO][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_SNAKE_COMBO][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_SNAKE_COMBO][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_SNAKE_COMBO][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_SKILL_SNAKE_COMBO][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_SNAKE_COMBO][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_SNAKE_COMBO][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_SNAKE_COMBO][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];

    // SKILL_SHIELD_STRIKE
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_SHIELD_STRIKE].Set("RESULT_SKILL_SHIELD_STRIKE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_SHIELD_STRIKE].SetSoundID( SOUNDID_NULL );
	*/

	// SKILL_CROSS_COUNTER
	(*g_pActionInfoTable)[RESULT_SKILL_CROSS_COUNTER].Set("RESULT_SKILL_CROSS_COUNTER", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_CROSS_COUNTER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_CROSS_COUNTER].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_CROSS_COUNTER].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SKILL_CROSS_COUNTER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_CROSS_COUNTER][0].EffectSpriteType	= EFFECTSPRITETYPE_POTENTIAL;
	(*g_pActionInfoTable)[RESULT_SKILL_CROSS_COUNTER][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_CROSS_COUNTER][0].Count				= FrameSize[EFFECTSPRITETYPE_POTENTIAL];

	// SKILL_PROTECTION_FIELD
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_PROTECTION_FIELD].Set("RESULT_SKILL_PROTECTION_FIELD", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_PROTECTION_FIELD].SetSoundID( SOUNDID_NULL );
	*/

	
	// SKILL_FLASH_SLIDING
	(*g_pActionInfoTable)[RESULT_SKILL_FLASH_SLIDING].Set("RESULT_SKILL_FLASH_SLIDING", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_FLASH_SLIDING].SetSoundID( SOUND_SLAYER_FLASH_SLIDING) ; //SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_FLASH_SLIDING].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_FLASH_SLIDING].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SKILL_FLASH_SLIDING][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_FLASH_SLIDING][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_FLASH_SLIDING][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_FLASH_SLIDING][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];

	// SKILL_RAGE
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_RAGE].Set("RESULT_SKILL_RAGE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_RAGE].SetSoundID( SOUNDID_NULL );
	*/

	// SKILL_LIGHTNING_HAND
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNING_HAND].Set("RESULT_SKILL_LIGHTNING_HAND", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNING_HAND].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNING_HAND].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNING_HAND].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNING_HAND][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNING_HAND][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNING_HAND][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNING_HAND][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNING_HAND][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNING_HAND][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNING_HAND][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNING_HAND][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNING_HAND][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNING_HAND][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNING_HAND][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNING_HAND][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];


	// SKILL_SWORD_WAVE
	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_WAVE].Set("RESULT_SKILL_SWORD_WAVE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_WAVE].SetSoundID( SOUNDID_NULL );

	// SKILL_FIVE_STORM_CRASH
	(*g_pActionInfoTable)[RESULT_SKILL_FIVE_STORM_CRASH].Set("RESULT_SKILL_FIVE_STORM_CRASH", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_FIVE_STORM_CRASH].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_FIVE_STORM_CRASH].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_FIVE_STORM_CRASH].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SKILL_FIVE_STORM_CRASH][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_FIVE_STORM_CRASH][0].EffectSpriteType	= EFFECTSPRITETYPE_REGENERATION_1_STAND_MALE;
	(*g_pActionInfoTable)[RESULT_SKILL_FIVE_STORM_CRASH][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_FIVE_STORM_CRASH][0].Count				= FrameSize[EFFECTSPRITETYPE_REGENERATION_1_STAND_MALE];
	(*g_pActionInfoTable)[RESULT_SKILL_FIVE_STORM_CRASH][0].SetDelayNode();

	// SKILL_CRITICAL_THRUST
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_THRUST].Set("RESULT_SKILL_CRITICAL_THRUST", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_THRUST].SetSoundID( SOUNDID_NULL );
	*/

	// SKILL_DRAGON_RISING
	(*g_pActionInfoTable)[RESULT_SKILL_DRAGON_RISING].Set("RESULT_SKILL_DRAGON_RISING", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_DRAGON_RISING].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_DRAGON_RISING].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_DRAGON_RISING].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SKILL_DRAGON_RISING][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_DRAGON_RISING][0].EffectSpriteType	= EFFECTSPRITETYPE_LIGHTNING_3;
	(*g_pActionInfoTable)[RESULT_SKILL_DRAGON_RISING][0].Step				= 20;
	(*g_pActionInfoTable)[RESULT_SKILL_DRAGON_RISING][0].Count			= FrameSize[EFFECTSPRITETYPE_LIGHTNING_3];

	// SKILL_HEAVENS_POWER
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVENS_POWER].Set("RESULT_SKILL_HEAVENS_POWER", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVENS_POWER].SetSoundID( SOUNDID_NULL );
	*/

	// SKILL_HEAVENS_SWORD
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVENS_SWORD].Set("RESULT_SKILL_HEAVENS_SWORD", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVENS_SWORD].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVENS_SWORD].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVENS_SWORD].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVENS_SWORD][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVENS_SWORD][0].EffectSpriteType	= EFFECTSPRITETYPE_HPBOOST_STAND_MALE;
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVENS_SWORD][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVENS_SWORD][0].Count				= FrameSize[EFFECTSPRITETYPE_HPBOOST_STAND_MALE];
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVENS_SWORD][0].SetDelayNode();


	//-------------------------------------------------------------
	//
	//                          도 계열
	//
	//-------------------------------------------------------------
	
    // SKILL_SINGLE_BLOW
	(*g_pActionInfoTable)[RESULT_SKILL_SINGLE_BLOW].Set("RESULT_SKILL_SINGLE_BLOW", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 100);
	(*g_pActionInfoTable)[RESULT_SKILL_SINGLE_BLOW].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_SKILL_SINGLE_BLOW].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_SINGLE_BLOW].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SKILL_SINGLE_BLOW][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_SINGLE_BLOW][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_SINGLE_BLOW][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_SINGLE_BLOW][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	
    // SKILL_TWIN_BREAK
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_TWIN_BREAK].Set("RESULT_SKILL_TWIN_BREAK", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 200);
	(*g_pActionInfoTable)[RESULT_SKILL_TWIN_BREAK].SetSoundID( SOUNDID_NULL );
	*/

    // SKILL_TRIPLE_BREAK
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_BREAK].Set("RESULT_SKILL_TRIPLE_BREAK", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_BREAK].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_BREAK].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_BREAK].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_BREAK][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_BREAK][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_BREAK][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_BREAK][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_BREAK][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_BREAK][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_BREAK][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_BREAK][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_BREAK][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_BREAK][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_BREAK][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_BREAK][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];

    // SKILL_SPIRAL_SLAY
	(*g_pActionInfoTable)[RESULT_SKILL_SPIRAL_SLAY].Set("RESULT_SKILL_SPIRAL_SLAY", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_SPIRAL_SLAY].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_SPIRAL_SLAY].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_SPIRAL_SLAY].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_SKILL_SPIRAL_SLAY][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_SPIRAL_SLAY][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_SPIRAL_SLAY][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_SPIRAL_SLAY][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_SKILL_SPIRAL_SLAY][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_SPIRAL_SLAY][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_SPIRAL_SLAY][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_SPIRAL_SLAY][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_SKILL_SPIRAL_SLAY][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_SPIRAL_SLAY][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_SPIRAL_SLAY][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_SPIRAL_SLAY][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];

    // SKILL_WILD_SMASH
	(*g_pActionInfoTable)[RESULT_SKILL_WILD_SMASH].Set("RESULT_SKILL_WILD_SMASH", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 500);
	(*g_pActionInfoTable)[RESULT_SKILL_WILD_SMASH].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_WILD_SMASH].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_WILD_SMASH].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_SKILL_WILD_SMASH][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_WILD_SMASH][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_WILD_SMASH][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_WILD_SMASH][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_SKILL_WILD_SMASH][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_WILD_SMASH][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_WILD_SMASH][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_WILD_SMASH][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_SKILL_WILD_SMASH][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_WILD_SMASH][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_WILD_SMASH][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_WILD_SMASH][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];

	// SKILL_GHOST_BLADE
	(*g_pActionInfoTable)[RESULT_SKILL_GHOST_BLADE].Set("RESULT_SKILL_GHOST_BLADE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 100);
	(*g_pActionInfoTable)[RESULT_SKILL_GHOST_BLADE].SetSoundID( SOUNDID_NULL );	
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_GHOST_BLADE].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_GHOST_BLADE].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_SKILL_GHOST_BLADE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_GHOST_BLADE][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_GHOST_BLADE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_GHOST_BLADE][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_SKILL_GHOST_BLADE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_GHOST_BLADE][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_GHOST_BLADE][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_GHOST_BLADE][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_SKILL_GHOST_BLADE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_GHOST_BLADE][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_GHOST_BLADE][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_GHOST_BLADE][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	*/


	// SKILL_CHARGING_POWER
	(*g_pActionInfoTable)[RESULT_SKILL_CHARGING_POWER].Set("RESULT_SKILL_CHARGING_POWER", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_CHARGING_POWER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_CHARGING_POWER].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[RESULT_SKILL_CHARGING_POWER].Init( 1 );
 	(*g_pActionInfoTable)[RESULT_SKILL_CHARGING_POWER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
 	(*g_pActionInfoTable)[RESULT_SKILL_CHARGING_POWER][0].EffectSpriteType	= EFFECTSPRITETYPE_CHARGING_POWER_MALE_STOP_1;			//EFFECTSPRITETYPE_CHARGING_POWER_MALE_STOP_1
 	(*g_pActionInfoTable)[RESULT_SKILL_CHARGING_POWER][0].Step				= 25;
 	(*g_pActionInfoTable)[RESULT_SKILL_CHARGING_POWER][0].Count				= FrameSize[EFFECTSPRITETYPE_CHARGING_POWER_MALE_STOP_1];	//EFFECTSPRITETYPE_CHARGING_POWER_MALE_STOP_1
 	(*g_pActionInfoTable)[RESULT_SKILL_CHARGING_POWER][0].SetDelayNode();
	
    // SKILL_ARMOR_CRASH
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_ARMOR_CRASH].Set("RESULT_SKILL_ARMOR_CRASH", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 600);
	(*g_pActionInfoTable)[RESULT_SKILL_ARMOR_CRASH].SetSoundID( SOUNDID_NULL );
	*/

	// SKILL_REQUIEM
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_REQUIEM].Set("RESULT_SKILL_REQUIEM", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 300);
	(*g_pActionInfoTable)[RESULT_SKILL_REQUIEM].SetSoundID( SOUNDID_NULL );
	*/

    // SKILL_FINAL_BLOW
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_FINAL_BLOW].Set("RESULT_SKILL_FINAL_BLOW", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_FINAL_BLOW].SetSoundID( SOUNDID_NULL );
	*/

	// SKILL_ENORMOUS_POWER
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_ENORMOUS_POWER].Set("RESULT_SKILL_ENORMOUS_POWER", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_ENORMOUS_POWER].SetSoundID( SOUNDID_NULL );
	*/

	// SKILL_POTENTIAL_EXPLOSION
	(*g_pActionInfoTable)[RESULT_SKILL_POTENTIAL_EXPLOSION].Set("RESULT_SKILL_POTENTIAL_EXPLOSION", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_POTENTIAL_EXPLOSION].SetSoundID( SOUNDID_NULL );

	// SKILL_SHADOW_WALK
	(*g_pActionInfoTable)[RESULT_SKILL_SHADOW_WALK].Set("RESULT_SKILL_SHADOW_WALK", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 100);
	(*g_pActionInfoTable)[RESULT_SKILL_SHADOW_WALK].SetSoundID(SOUND_SLAYER_SHADOW_WALK) ;// SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_SKILL_SHADOW_WALK].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_SHADOW_WALK].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SKILL_SHADOW_WALK][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_SHADOW_WALK][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_SHADOW_WALK][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_SHADOW_WALK][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	

	// SKILL_MULTI_HANDS
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_HANDS].Set("RESULT_SKILL_MULTI_HANDS", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_HANDS].SetSoundID( SOUNDID_NULL );
	*/

	// SKILL_TORNADO_SEVER
	(*g_pActionInfoTable)[RESULT_SKILL_TORNADO_SEVER].Set("RESULT_SKILL_TORNADO_SEVER", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_TORNADO_SEVER].SetSoundID( SOUNDID_NULL );

	// SKILL_SOUL_SHOCK
	(*g_pActionInfoTable)[RESULT_SKILL_SOUL_SHOCK].Set("RESULT_SKILL_SOUL_SHOCK", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_SOUL_SHOCK].SetSoundID( SOUNDID_NULL );

	// SKILL_BLADE_WAVE
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_BLADE_WAVE].Set("RESULT_SKILL_BLADE_WAVE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_BLADE_WAVE].SetSoundID( SOUNDID_NULL );
	*/

	// SKILL_ARMAGEDDON_SLASHER
	(*g_pActionInfoTable)[RESULT_SKILL_ARMAGEDDON_SLASHER].Set("RESULT_SKILL_ARMAGEDDON_SLASHER", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_ARMAGEDDON_SLASHER].SetSoundID( SOUNDID_NULL );

	// SKILL_IMMORTAL_POWER
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_IMMORTAL_POWER].Set("RESULT_SKILL_IMMORTAL_POWER", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_IMMORTAL_POWER].SetSoundID( SOUNDID_NULL );
	*/

	// SKILL_SAINT_BLADE
	(*g_pActionInfoTable)[RESULT_SKILL_SAINT_BLADE].Set("RESULT_SKILL_SAINT_BLADE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_SAINT_BLADE].SetSoundID( SOUNDID_NULL );
	

	//-------------------------------------------------------------
	//
	//                      Gun계열
	//
	//-------------------------------------------------------------
	// RESULT_SKILL_SNIPPING
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_SNIPPING].Set("RESULT_SKILL_SNIPPING", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_SNIPPING].SetSoundID( SOUNDID_NULL );
	*/

	// RESULT_SKILL_SHARP_SHOOTING
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_SHARP_SHOOTING].Set("RESULT_SKILL_SHARP_SHOOTING", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_SHARP_SHOOTING].SetSoundID( SOUNDID_NULL );
	*/

	// RESULT_SKILL_FAST_RELOAD
	(*g_pActionInfoTable)[RESULT_SKILL_FAST_RELOAD].Set("RESULT_SKILL_FAST_RELOAD", ACTION_STAND, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_FAST_RELOAD].SetSoundID( SOUNDID_NULL );

	// RESULT_SKILL_SMG_MASTERY
	(*g_pActionInfoTable)[RESULT_SKILL_SMG_MASTERY].Set("RESULT_SKILL_SMG_MASTERY", ACTION_STAND, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_SMG_MASTERY].SetSoundID( SOUNDID_NULL );

	// RESULT_SKILL_SG_MASTERY
	(*g_pActionInfoTable)[RESULT_SKILL_SG_MASTERY].Set("RESULT_SKILL_SG_MASTERY", ACTION_STAND, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_SG_MASTERY].SetSoundID( SOUNDID_NULL );

	// RESULT_SKILL_AR_MASTERY
	(*g_pActionInfoTable)[RESULT_SKILL_AR_MASTERY].Set("RESULT_SKILL_AR_MASTERY", ACTION_STAND, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_AR_MASTERY].SetSoundID( SOUNDID_NULL );

	// RESULT_SKILL_SR_MASTERY
	(*g_pActionInfoTable)[RESULT_SKILL_SR_MASTERY].Set("RESULT_SKILL_SR_MASTERY", ACTION_STAND, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_SR_MASTERY].SetSoundID( SOUNDID_NULL );

	// RESULT_SKILL_QUICK_FIRE
	(*g_pActionInfoTable)[RESULT_SKILL_QUICK_FIRE].Set("RESULT_SKILL_QUICK_FIRE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_QUICK_FIRE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_QUICK_FIRE].Init( 2);
	(*g_pActionInfoTable)[RESULT_SKILL_QUICK_FIRE][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_QUICK_FIRE][0].EffectSpriteType = EFFECTSPRITETYPE_QUICK_FIRE_BOMB_1;
	(*g_pActionInfoTable)[RESULT_SKILL_QUICK_FIRE][0].Step = 25;
	(*g_pActionInfoTable)[RESULT_SKILL_QUICK_FIRE][0].Count = FrameSize[EFFECTSPRITETYPE_QUICK_FIRE_BOMB_1];
	(*g_pActionInfoTable)[RESULT_SKILL_QUICK_FIRE][0].LinkCount = 1;
	(*g_pActionInfoTable)[RESULT_SKILL_QUICK_FIRE][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_QUICK_FIRE][1].EffectSpriteType = EFFECTSPRITETYPE_QUICK_FIRE_BOMB_1;
	(*g_pActionInfoTable)[RESULT_SKILL_QUICK_FIRE][1].Step = 25;
	(*g_pActionInfoTable)[RESULT_SKILL_QUICK_FIRE][1].Count = FrameSize[EFFECTSPRITETYPE_QUICK_FIRE_BOMB_1];
	

	// RESULT_SKILL_DOUBLE_SHOT
	(*g_pActionInfoTable)[RESULT_SKILL_DOUBLE_SHOT].Set("RESULT_SKILL_DOUBLE_FIRE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_DOUBLE_SHOT].SetSoundID( SOUNDID_NULL );	

	// RESULT_SKILL_TRIPLE_SHOT
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_SHOT].Set("RESULT_SKILL_TRIPLE_FIRE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_TRIPLE_SHOT].SetSoundID( SOUNDID_NULL );
	
	
	// RESULT_SKILL_MULTI_SHOT
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_SHOT].Set("RESULT_SKILL_MULTI_SHOT", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_SHOT].SetSoundID( SOUNDID_NULL );
	
	// RESULT_SKILL_HEAD_SHOT
	(*g_pActionInfoTable)[RESULT_SKILL_HEAD_SHOT].Set("RESULT_SKILL_HEAD_SHOT", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_HEAD_SHOT].SetSoundID( SOUNDID_NULL );

	// RESULT_SKILL_PIERCING
	(*g_pActionInfoTable)[RESULT_SKILL_PIERCING].Set("RESULT_SKILL_PIERCING", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[RESULT_SKILL_PIERCING].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_PIERCING].Init( 2 );
	(*g_pActionInfoTable)[RESULT_SKILL_PIERCING][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_PIERCING][0].EffectSpriteType = EFFECTSPRITETYPE_PIERCING_FRONT;
	(*g_pActionInfoTable)[RESULT_SKILL_PIERCING][0].Step = 25;
	(*g_pActionInfoTable)[RESULT_SKILL_PIERCING][0].Count = FrameSize[EFFECTSPRITETYPE_PIERCING_FRONT];
	(*g_pActionInfoTable)[RESULT_SKILL_PIERCING][0].LinkCount = 2;
	(*g_pActionInfoTable)[RESULT_SKILL_PIERCING][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_PIERCING][1].EffectSpriteType = EFFECTSPRITETYPE_PIERCING_BACK;
	(*g_pActionInfoTable)[RESULT_SKILL_PIERCING][1].Step = 25;
	(*g_pActionInfoTable)[RESULT_SKILL_PIERCING][1].Count = FrameSize[EFFECTSPRITETYPE_PIERCING_BACK];

	// RESULT_SKILL_SNIPPING
	(*g_pActionInfoTable)[RESULT_SKILL_SNIPPING].Set("RESULT_SKILL_SNIPPING", ACTION_STAND, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_SNIPPING].SetSoundID( SOUNDID_NULL );

	// RESULT_SKILL_KNOCKS_TARGET_BACK
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_KNOCKS_TARGET_BACK].Set("RESULT_SKILL_KNOCKS_TARGET_BACK", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_KNOCKS_TARGET_BACK].SetSoundID( SOUNDID_NULL );
	*/
	

	// RESULT_SKILL_CRITICAL_SHOOTING
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_SHOOTING].Set("RESULT_SKILL_CRITICAL_SHOOTING", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_SHOOTING].SetSoundID( SOUNDID_NULL );
	*/

	// RESULT_SKILL_SCOPE_SHOOTING
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_SCOPE_SHOOTING].Set("RESULT_SKILL_SCOPE_SHOOTING", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_SCOPE_SHOOTING].SetSoundID( SOUNDID_NULL );
	*/

	// SKILL_DETECT_MINE
	(*g_pActionInfoTable)[RESULT_SKILL_DETECT_MINE].Set("RESULT_SKILL_DETECT_MINE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);	
	(*g_pActionInfoTable)[RESULT_SKILL_DETECT_MINE].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_DETECT_MINE].SetSoundID( SOUNDID_NULL );	
	(*g_pActionInfoTable)[RESULT_SKILL_DETECT_MINE].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_DETECT_MINE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_DETECT_MINE][0].EffectSpriteType	= EFFECTSPRITETYPE_DETECT_HIDDEN;
	(*g_pActionInfoTable)[RESULT_SKILL_DETECT_MINE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_DETECT_MINE][0].Count			= FrameSize[EFFECTSPRITETYPE_DETECT_HIDDEN];
	(*g_pActionInfoTable)[RESULT_SKILL_DETECT_MINE][0].SoundID			= SOUND_SLAYER_ENCHANT_DH;

	// SKILL_INSTALL_MINE
	(*g_pActionInfoTable)[RESULT_SKILL_INSTALL_MINE].Set("RESULT_SKILL_INSTALL_MINE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_INSTALL_MINE].SetSoundID( SOUNDID_NULL );
	

	// SKILL_INSTALL_DISARM_MINE
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_INSTALL_DISARM_MINE].Set("RESULT_SKILL_INSTALL_DISARM_MINE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_INSTALL_DISARM_MINE].SetSoundID( SOUNDID_NULL );
	*/

	// RESULT_SKILL_DISARM_MINE
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_DISARM_MINE].Set("RESULT_SKILL_DISARM_MINE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_DISARM_MINE].SetSoundID( SOUNDID_NULL );
	*/

	// RESULT_SKILL_MAKE_BOMB
	(*g_pActionInfoTable)[RESULT_SKILL_MAKE_BOMB].Set("RESULT_SKILL_MAKE_BOMB", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ITEM);
	(*g_pActionInfoTable)[RESULT_SKILL_MAKE_BOMB].SetSoundID( SOUNDID_NULL );
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_MAKE_BOMB].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_MAKE_BOMB].SetMainNode( 1 );	
	(*g_pActionInfoTable)[RESULT_SKILL_MAKE_BOMB].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_MAKE_BOMB][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_INVENTORY;
	(*g_pActionInfoTable)[RESULT_SKILL_MAKE_BOMB][0].EffectSpriteType	= EFFECTSPRITETYPE_ENCHANT_1x1;
	(*g_pActionInfoTable)[RESULT_SKILL_MAKE_BOMB][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_MAKE_BOMB][0].Count				= FrameSize[EFFECTSPRITETYPE_ENCHANT_1x1];
	(*g_pActionInfoTable)[RESULT_SKILL_MAKE_BOMB][0].SoundID			= SOUND_SLAYER_ENCHANT_IDENTIFY;
	*/

	// RESULT_SKILL_MAKE_MINE
	(*g_pActionInfoTable)[RESULT_SKILL_MAKE_MINE].Set("RESULT_SKILL_MAKE_MINE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ITEM);
	(*g_pActionInfoTable)[RESULT_SKILL_MAKE_MINE].SetSoundID( SOUNDID_NULL );
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_MAKE_MINE].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_MAKE_MINE].SetMainNode( 1 );	
	(*g_pActionInfoTable)[RESULT_SKILL_MAKE_MINE].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_MAKE_MINE][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_INVENTORY;
	(*g_pActionInfoTable)[RESULT_SKILL_MAKE_MINE][0].EffectSpriteType	= EFFECTSPRITETYPE_IDENTIFY_1x1;
	(*g_pActionInfoTable)[RESULT_SKILL_MAKE_MINE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_MAKE_MINE][0].Count				= FrameSize[EFFECTSPRITETYPE_IDENTIFY_1x1];
	(*g_pActionInfoTable)[RESULT_SKILL_MAKE_MINE][0].SoundID			= SOUND_SLAYER_ENCHANT_IDENTIFY;
	*/

	// RESULT_SKILL_HOLY_SHOOTING
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SHOOTING].Set("RESULT_SKILL_HOLY_SHOOTING", ACTION_DAMAGED, EFFECTSPRITETYPE_HOLY_SHOOTING_HIT, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SHOOTING].SetCastingFramesAll( 8 );
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SHOOTING].SetSoundID( SOUND_DAMAGE_GUN );
	*/

	//-------------------------------------------------------------
	//
	//                      Priest 마법
	//
	//-------------------------------------------------------------

	// MAGIC_LIGHT,				// Light
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT].Set("RESULT_MAGIC_LIGHT", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);	
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT].Init( 3 );	
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][0].EffectSpriteType	= EFFECTSPRITETYPE_LIGHT_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][0].Count				= FrameSize[EFFECTSPRITETYPE_LIGHT_1];
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][0].SoundID			= SOUND_SLAYER_ENCHANT_L;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][1].EffectSpriteType	= EFFECTSPRITETYPE_LIGHT_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][1].Count				= FrameSize[EFFECTSPRITETYPE_LIGHT_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][1].SetResultTime();
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][2].EffectSpriteType	= EFFECTSPRITETYPE_LIGHT_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][2].Count				= FrameSize[EFFECTSPRITETYPE_LIGHT_3];
		
	//*/
	/*
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][0].EffectGeneratorID	= EFFECTGENERATORID_MULTIPLE_FALLING;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][0].EffectSpriteType	= EFFECTSPRITETYPE_HEAL_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][0].Count				= FrameSize[EFFECTSPRITETYPE_HEAL_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][1].EffectSpriteType	= EFFECTSPRITETYPE_LIGHT;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][1].Count				= FrameSize[EFFECTSPRITETYPE_LIGHT];
	*/
	/*
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][0].EffectSpriteType	= EFFECTSPRITETYPE_LIGHT_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][0].Count				= FrameSize[EFFECTSPRITETYPE_LIGHT_1];
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][1].EffectSpriteType	= EFFECTSPRITETYPE_LIGHT_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][1].Count				= FrameSize[EFFECTSPRITETYPE_LIGHT_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][2].EffectSpriteType	= EFFECTSPRITETYPE_LIGHT_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_LIGHT][2].Count				= FrameSize[EFFECTSPRITETYPE_LIGHT_3];
	*/
	
	// MAGIC_DETECT_HIDDEN,		// Detect Hidden
	//FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_MAGIC_DETECT_HIDDEN].Set("RESULT_RESULT_MAGIC_DETECT_HIDDEN", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);	
	(*g_pActionInfoTable)[RESULT_MAGIC_DETECT_HIDDEN].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_MAGIC_DETECT_HIDDEN].SetSoundID( SOUNDID_NULL );	
	(*g_pActionInfoTable)[RESULT_MAGIC_DETECT_HIDDEN].Init( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_DETECT_HIDDEN][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_DETECT_HIDDEN][0].EffectSpriteType	= EFFECTSPRITETYPE_DETECT_HIDDEN;
	(*g_pActionInfoTable)[RESULT_MAGIC_DETECT_HIDDEN][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_DETECT_HIDDEN][0].Count			= FrameSize[EFFECTSPRITETYPE_DETECT_HIDDEN];
	(*g_pActionInfoTable)[RESULT_MAGIC_DETECT_HIDDEN][0].SoundID			= SOUND_SLAYER_ENCHANT_DH;
	

	// MAGIC_CONTINUAL_LIGHT,		// Continual Light
	(*g_pActionInfoTable)[RESULT_MAGIC_CONTINUAL_LIGHT].Set("RESULT_MAGIC_CONTINUAL_LIGHT", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);	
	(*g_pActionInfoTable)[RESULT_MAGIC_CONTINUAL_LIGHT].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_MAGIC_CONTINUAL_LIGHT].SetSoundID( SOUNDID_NULL);	
	(*g_pActionInfoTable)[RESULT_MAGIC_CONTINUAL_LIGHT].Init( 3 );
	(*g_pActionInfoTable)[RESULT_MAGIC_CONTINUAL_LIGHT].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_CONTINUAL_LIGHT][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_CONTINUAL_LIGHT][0].EffectSpriteType	= EFFECTSPRITETYPE_CONTINUAL_LIGHT_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_CONTINUAL_LIGHT][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CONTINUAL_LIGHT][0].Count				= FrameSize[EFFECTSPRITETYPE_CONTINUAL_LIGHT_1];
	(*g_pActionInfoTable)[RESULT_MAGIC_CONTINUAL_LIGHT][0].SoundID			= SOUND_SLAYER_CONTINUAL_LIGHT ; //SOUND_SLAYER_ENCHANT_CL;
	(*g_pActionInfoTable)[RESULT_MAGIC_CONTINUAL_LIGHT][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;	// 반복
	(*g_pActionInfoTable)[RESULT_MAGIC_CONTINUAL_LIGHT][1].EffectSpriteType	= EFFECTSPRITETYPE_CONTINUAL_LIGHT_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_CONTINUAL_LIGHT][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CONTINUAL_LIGHT][1].Count				= FrameSize[EFFECTSPRITETYPE_CONTINUAL_LIGHT_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_CONTINUAL_LIGHT][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_CONTINUAL_LIGHT][1].SetResultTime();
	(*g_pActionInfoTable)[RESULT_MAGIC_CONTINUAL_LIGHT][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_CONTINUAL_LIGHT][2].EffectSpriteType	= EFFECTSPRITETYPE_CONTINUAL_LIGHT_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_CONTINUAL_LIGHT][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CONTINUAL_LIGHT][2].Count				= FrameSize[EFFECTSPRITETYPE_CONTINUAL_LIGHT_3];

	// MAGIC_DETECT_INVISIBILITY,	// Detect Invisibility
	(*g_pActionInfoTable)[RESULT_MAGIC_DETECT_INVISIBILITY].Set("RESULT_MAGIC_DETECT_INVISIBILITY", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);	
	(*g_pActionInfoTable)[RESULT_MAGIC_DETECT_INVISIBILITY].SetSoundID( SOUNDID_NULL );		
	(*g_pActionInfoTable)[RESULT_MAGIC_DETECT_INVISIBILITY].Init( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_DETECT_INVISIBILITY][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_DETECT_INVISIBILITY][0].EffectSpriteType	= EFFECTSPRITETYPE_DETECT_INVISIBILITY;
	(*g_pActionInfoTable)[RESULT_MAGIC_DETECT_INVISIBILITY][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_DETECT_INVISIBILITY][0].Count				= FrameSize[EFFECTSPRITETYPE_DETECT_INVISIBILITY];
	(*g_pActionInfoTable)[RESULT_MAGIC_DETECT_INVISIBILITY][0].SoundID			= SOUND_SLAYER_ENCHANT_DETECTINVISIBILITY;

	// MAGIC_VISIBLE,				// Visible
	(*g_pActionInfoTable)[RESULT_MAGIC_VISIBLE].Set("RESULT_MAGIC_VISIBLE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_MAGIC_VISIBLE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_VISIBLE].Init( 2 );
	(*g_pActionInfoTable)[RESULT_MAGIC_VISIBLE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_VISIBLE][0].EffectSpriteType	= EFFECTSPRITETYPE_VISIBLE_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_VISIBLE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_VISIBLE][0].Count				= 2*16;//FrameSize[EFFECTSPRITETYPE_VISIBLE_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_VISIBLE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_VISIBLE][1].EffectSpriteType	= EFFECTSPRITETYPE_VISIBLE_5;
	(*g_pActionInfoTable)[RESULT_MAGIC_VISIBLE][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_VISIBLE][1].Count			= FrameSize[EFFECTSPRITETYPE_VISIBLE_5];
	
	
	// MAGIC_DETECT_EVIL,			// Detect Evil
	/*
	(*g_pActionInfoTable)[RESULT_MAGIC_DETECT_EVIL].Set("RESULT_MAGIC_DETECT_EVIL", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[RESULT_MAGIC_DETECT_EVIL].SetSoundID( SOUNDID_NULL );
	*/

	// MAGIC_AURA_SHIELD,			// Aura Shield
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD].Set("RESULT_MAGIC_AURA_SHIELD", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD][0].EffectSpriteType	= EFFECTSPRITETYPE_AURA_PRISM_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD][0].Step				= 40;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD][0].Count				= FrameSize[EFFECTSPRITETYPE_AURA_PRISM_2];
	/*
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE_GROUND;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD][0].EffectSpriteType	= EFFECTSPRITETYPE_AURA_PRISM_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD][0].Count				= FrameSize[EFFECTSPRITETYPE_AURA_PRISM_3];
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD][0].SoundID				= SOUND_VAMPIRE_MISC_D;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE_GROUND;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD][1].EffectSpriteType	= EFFECTSPRITETYPE_AURA_PRISM_4;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD][1].Count				= FrameSize[EFFECTSPRITETYPE_AURA_PRISM_4];
	//(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE_GROUND;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD][2].EffectSpriteType	= EFFECTSPRITETYPE_AURA_PRISM_5;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD][2].Count				= FrameSize[EFFECTSPRITETYPE_AURA_PRISM_5];
	*/
	/*
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD].Set("RESULT_MAGIC_AURA_SHIELD", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD].Init( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD][0].EffectSpriteType	= EFFECTSPRITETYPE_AURA_SHIELD_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD][0].Count				= FrameSize[EFFECTSPRITETYPE_AURA_SHIELD_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_SHIELD][0].SoundID			= SOUND_SLAYER_ENCHANT_AURASHIELD1;
	*/
	

	// MAGIC_FLARE,			// flare
	(*g_pActionInfoTable)[RESULT_MAGIC_FLARE].Set("RESULT_MAGIC_FLARE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_FLARE].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_MAGIC_FLARE].Init( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_FLARE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_FLARE][0].EffectSpriteType	= EFFECTSPRITETYPE_CONTINUAL_LIGHT_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_FLARE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_FLARE][0].Count				= FrameSize[EFFECTSPRITETYPE_CONTINUAL_LIGHT_3];
	(*g_pActionInfoTable)[RESULT_MAGIC_FLARE][0].SoundID			= SOUND_SLAYER_ENCHANT_AURABALL2;

	// MAGIC_AURA_BALL,			// Aura Ball
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_BALL].Set("RESULT_MAGIC_AURA_BALL", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_BALL].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_BALL].Init( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_BALL][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_BALL][0].EffectSpriteType	= EFFECTSPRITETYPE_AURA_BALL_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_BALL][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_BALL][0].Count				= FrameSize[EFFECTSPRITETYPE_AURA_BALL_3];
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_BALL][0].SoundID			= SOUND_SLAYER_ENCHANT_AURABALL2;

	// RESUL_SKILL_LIGHT_BALL,			// Aura Ball
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHT_BALL].Set("RESULT_SKILL_LIGHT_BALL", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHT_BALL].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHT_BALL].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHT_BALL][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHT_BALL][0].EffectSpriteType	= EFFECTSPRITETYPE_LIGHT_BALL_END;
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHT_BALL][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHT_BALL][0].Count				= FrameSize[EFFECTSPRITETYPE_LIGHT_BALL_END];
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHT_BALL][0].SoundID			= SOUND_SLAYER_LIGHT_BALL ; //SOUND_SLAYER_ENCHANT_AURABALL2;

	// RESUL_SKILL_HOLY_ARROW,			// Aura Ball
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARROW].Set("RESULT_SKILL_HOLY_ARROW", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARROW].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARROW].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARROW][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARROW][0].EffectSpriteType	= EFFECTSPRITETYPE_HOLY_ARROW_END;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARROW][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARROW][0].Count				= FrameSize[EFFECTSPRITETYPE_HOLY_ARROW_END];
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARROW][0].SoundID			= SOUND_SLAYER_ENCHANT_AURABALL2;

	// MAGIC_AURA_CROSS,			// Aura Cross
	/*
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_CROSS].Set("RESULT_MAGIC_AURA_CROSS", ACTION_DAMAGED, EFFECTSPRITETYPE_DARKNESS_2, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_CROSS].SetSoundID( SOUNDID_NULL );
	*/

	// MAGIC_AURA_RING,			// Aura Ring
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_RING].Set("RESULT_MAGIC_AURA_RING", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_RING].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_RING].SetSoundID( SOUND_SLAYER_AURA_RING) ; //SOUND_SLAYER_ENCHANT_AURARING1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_RING].Init( 1 );	
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_RING][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_RING][0].EffectSpriteType	= EFFECTSPRITETYPE_AURA_RING;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_RING][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_RING][0].Count				= FrameSize[EFFECTSPRITETYPE_AURA_RING];
	//(*g_pActionInfoTable)[RESULT_MAGIC_AURA_RING][0].SoundID			= SOUND_SLAYER_ENCHANT_AURARING2;
	//(*g_pActionInfoTable)[RESULT_MAGIC_AURA_RING][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	//(*g_pActionInfoTable)[RESULT_MAGIC_AURA_RING][1].EffectSpriteType	= EFFECTSPRITETYPE_AURA_RING;
	//(*g_pActionInfoTable)[RESULT_MAGIC_AURA_RING][1].Step				= 25;
	//(*g_pActionInfoTable)[RESULT_MAGIC_AURA_RING][1].Count				= 2;
	//(*g_pActionInfoTable)[RESULT_MAGIC_AURA_RING][1].SoundID			= SOUND_SLAYER_ENCHANT_AURARING2;
	

	// MAGIC_SAINT_AURA,			// Saint Aura
	(*g_pActionInfoTable)[RESULT_MAGIC_SAINT_AURA].Set("RESULT_MAGIC_SAINT_AURA", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_SAINT_AURA].SetSoundID( SOUNDID_NULL );

	// RESULT_SKILL_REBUKE,			// Saint Aura
	(*g_pActionInfoTable)[RESULT_SKILL_REBUKE].Set("RESULT_SKILL_REBUKE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_REBUKE].SetSoundID( SOUNDID_NULL );

	// RESULT_SKILL_GUN_SHOT_GUIDANCE,			// Saint Aura
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE].Set("RESULT_SKILL_GUN_SHOT_GUIDANCE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE].SetSoundID( SOUND_SLAYER_GUN_SHOT_GUIDANCE) ;//SOUNDID_NULL );

	// RESULT_SKILL_GUN_SHOT_GUIDANCE,			// Saint Aura
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_BOMB].Set("RESULT_SKILL_GUN_SHOT_GUIDANCE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
//	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_BOMB].SetSoundID( SOUND_ITEM_BOOM4 );
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_BOMB].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_BOMB].Init( 3 );
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_BOMB][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_BOMB][0].EffectSpriteType	= EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_WAVE;
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_BOMB][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_BOMB][0].Count				= FrameSize[EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_WAVE];
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_BOMB][0].SoundID			= SOUND_ITEM_BOOM4;
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_BOMB][0].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_BOMB][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_BOMB][1].EffectSpriteType	= EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_BOOM;
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_BOMB][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_BOMB][1].Count				= FrameSize[EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_BOOM];
//	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_BOMB][1].SoundID			= SOUND_SLAYER_ENCHANT_CHW2;
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_BOMB][1].LinkCount			= 2;
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_BOMB][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_BOMB][2].EffectSpriteType	= EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_PIT;
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_BOMB][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_BOMB][2].Count				= FrameSize[EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_PIT];
//	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_BOMB][2].SoundID			= SOUND_SLAYER_ENCHANT_CHW2;

	// RESULT_SKILL_GUN_SHOT_POINT,			// Saint Aura
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_POINT].Set("RESULT_SKILL_GUN_SHOT_GUIDANCE_POINT", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
//	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_POINT].SetSoundID( SOUND_ITEM_USE_SCROLL );
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_POINT].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_POINT].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_POINT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_POINT][0].EffectSpriteType	= EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_POINT;
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_POINT][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_POINT][0].Count				= FrameSize[EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_POINT];
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_POINT][0].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_GUIDANCE_POINT][0].SoundID			= SOUND_ITEM_USE_SCROLL;
//	(*g_pActionInfoTable)[RESULT_SKILL_GUN_SHOT_POINT][0].LinkCount			= 0;

	// RESULT_TURN_UNDEAD,			// Saint Aura
	(*g_pActionInfoTable)[RESULT_SKILL_TURN_UNDEAD].Set("RESULT_SKILL_TURN_UNDEAD", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_TURN_UNDEAD].SetSoundID( SOUNDID_NULL );

	// MAGIC_CREATE_HOLY_WATER,	// Create Holy Water
	(*g_pActionInfoTable)[RESULT_MAGIC_CREATE_HOLY_WATER].Set("RESULT_MAGIC_CREATE_HOLY_WATER", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ITEM);
	(*g_pActionInfoTable)[RESULT_MAGIC_CREATE_HOLY_WATER].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_MAGIC_CREATE_HOLY_WATER].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_CREATE_HOLY_WATER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_CREATE_HOLY_WATER].Init( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_CREATE_HOLY_WATER][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_INVENTORY;
	(*g_pActionInfoTable)[RESULT_MAGIC_CREATE_HOLY_WATER][0].EffectSpriteType	= EFFECTSPRITETYPE_CREATE_HOLY_WATER_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_CREATE_HOLY_WATER][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CREATE_HOLY_WATER][0].Count				= FrameSize[EFFECTSPRITETYPE_CREATE_HOLY_WATER_3];
	(*g_pActionInfoTable)[RESULT_MAGIC_CREATE_HOLY_WATER][0].SoundID			= SOUND_SLAYER_ENCHANT_CHW2;

	// MAGIC_BLESS,				// Bless
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS].Set("RESULT_MAGIC_BLESS", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS].Init( 2 );
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][0].EffectSpriteType	= EFFECTSPRITETYPE_BLESS;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][0].Count				= FrameSize[EFFECTSPRITETYPE_BLESS];
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][0].SoundID			= SOUND_SLAYER_ENCHANT_B1;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][1].EffectSpriteType	= EFFECTSPRITETYPE_BLESS_ING_NEW;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][1].Count				= FrameSize[EFFECTSPRITETYPE_BLESS_ING_NEW];
	/*
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS].Init( 7 );
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][0].EffectSpriteType	= EFFECTSPRITETYPE_BLESS_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][0].Count				= FrameSize[EFFECTSPRITETYPE_BLESS_1];
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][0].SoundID			= SOUND_SLAYER_ENCHANT_B1;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;	// 반복
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][1].EffectSpriteType	= EFFECTSPRITETYPE_BLESS_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][1].Count				= FrameSize[EFFECTSPRITETYPE_BLESS_2];
	//(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][2].EffectSpriteType	= EFFECTSPRITETYPE_BLESS_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][2].Count				= FrameSize[EFFECTSPRITETYPE_BLESS_3];
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][3].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][3].EffectSpriteType	= EFFECTSPRITETYPE_BLESS_4;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][3].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][3].Count				= FrameSize[EFFECTSPRITETYPE_BLESS_4];
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][4].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;		// 바닥..
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][4].EffectSpriteType	= EFFECTSPRITETYPE_BLESS_5;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][4].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][4].SoundID			= SOUND_SLAYER_ENCHANT_B2;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][4].Count				= FrameSize[EFFECTSPRITETYPE_BLESS_5];
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][5].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;		// 솟아오름
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][5].EffectSpriteType	= EFFECTSPRITETYPE_BLESS_6;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][5].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][5].Count				= FrameSize[EFFECTSPRITETYPE_BLESS_6];
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][6].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;		// - -;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][6].EffectSpriteType	= EFFECTSPRITETYPE_BLESS_7;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][6].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_BLESS][6].Count				= FrameSize[EFFECTSPRITETYPE_BLESS_7];
	*/

	// MAGIC_PURIFY,			// Bless Ground
	(*g_pActionInfoTable)[RESULT_MAGIC_PURIFY].Set("RESULT_MAGIC_PURIFY", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);	
	(*g_pActionInfoTable)[RESULT_MAGIC_PURIFY].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_MAGIC_PURIFY].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_PURIFY].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_PURIFY].Init( 4 );
	(*g_pActionInfoTable)[RESULT_MAGIC_PURIFY][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_PURIFY][0].EffectSpriteType	= EFFECTSPRITETYPE_BLESS_GROUND_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_PURIFY][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_PURIFY][0].Count				= FrameSize[EFFECTSPRITETYPE_BLESS_GROUND_1];
	(*g_pActionInfoTable)[RESULT_MAGIC_PURIFY][0].SoundID				= SOUND_SLAYER_ENCHANT_B1;
	(*g_pActionInfoTable)[RESULT_MAGIC_PURIFY][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_PURIFY][1].EffectSpriteType	= EFFECTSPRITETYPE_BLESS_GROUND_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_PURIFY][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_PURIFY][1].Count				= FrameSize[EFFECTSPRITETYPE_BLESS_GROUND_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_PURIFY][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_PURIFY][2].EffectSpriteType	= EFFECTSPRITETYPE_BLESS_GROUND_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_PURIFY][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_PURIFY][2].Count				= FrameSize[EFFECTSPRITETYPE_BLESS_GROUND_3];
	(*g_pActionInfoTable)[RESULT_MAGIC_PURIFY][3].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_MAGIC_PURIFY][3].EffectSpriteType	= EFFECTSPRITETYPE_BLESS_GROUND_4;
	(*g_pActionInfoTable)[RESULT_MAGIC_PURIFY][3].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_PURIFY][3].Count				= FrameSize[EFFECTSPRITETYPE_BLESS_GROUND_4];
	

	// MAGIC_STRIKING,				// Striking
	(*g_pActionInfoTable)[RESULT_MAGIC_STRIKING].Set("RESULT_MAGIC_STRIKING", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_STRIKING].SetSoundID(SOUND_SLAYER_STRIKING) ;// SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_STRIKING].Init( 3 );
	(*g_pActionInfoTable)[RESULT_MAGIC_STRIKING].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_STRIKING][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_STRIKING][0].EffectSpriteType	= EFFECTSPRITETYPE_STRIKING_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_STRIKING][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_STRIKING][0].Count				= FrameSize[EFFECTSPRITETYPE_STRIKING_1];
	//(*g_pActionInfoTable)[RESULT_MAGIC_STRIKING][0].SoundID				= SOUND_SLAYER_ENCHANT_S1;
	(*g_pActionInfoTable)[RESULT_MAGIC_STRIKING][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_STRIKING][1].EffectSpriteType	= EFFECTSPRITETYPE_STRIKING_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_STRIKING][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_STRIKING][1].Count				= FrameSize[EFFECTSPRITETYPE_STRIKING_2];
	//(*g_pActionInfoTable)[RESULT_MAGIC_STRIKING][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_STRIKING][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_STRIKING][2].EffectSpriteType	= EFFECTSPRITETYPE_STRIKING_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_STRIKING][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_STRIKING][2].Count				= FrameSize[EFFECTSPRITETYPE_STRIKING_3];
	//(*g_pActionInfoTable)[RESULT_MAGIC_STRIKING][2].SoundID				= SOUND_SLAYER_ENCHANT_S2;

	// MAGIC_ENCHANT,				// Enchant
//	(*g_pActionInfoTable)[RESULT_MAGIC_ENCHANT].Set("RESULT_MAGIC_ENCHANT", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ITEM);
//	(*g_pActionInfoTable)[RESULT_MAGIC_ENCHANT].SetStartWithCasting();
//	(*g_pActionInfoTable)[RESULT_MAGIC_ENCHANT].SetMainNode( 1 );
//	(*g_pActionInfoTable)[RESULT_MAGIC_ENCHANT].SetSoundID( SOUNDID_NULL );
//	(*g_pActionInfoTable)[RESULT_MAGIC_ENCHANT].Init( 1 );
//	(*g_pActionInfoTable)[RESULT_MAGIC_ENCHANT][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_INVENTORY;
//	(*g_pActionInfoTable)[RESULT_MAGIC_ENCHANT][0].EffectSpriteType	= EFFECTSPRITETYPE_ENCHANT_1x1;
//	(*g_pActionInfoTable)[RESULT_MAGIC_ENCHANT][0].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_ENCHANT][0].Count				= FrameSize[EFFECTSPRITETYPE_ENCHANT_1x1];
//	(*g_pActionInfoTable)[RESULT_MAGIC_ENCHANT][0].SoundID			= SOUND_SLAYER_ENCHANT_IDENTIFY;

	// MAGIC_IDENTIFY,				// Identify
//	(*g_pActionInfoTable)[RESULT_MAGIC_IDENTIFY].Set("RESULT_MAGIC_IDENTIFY", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ITEM);
//	(*g_pActionInfoTable)[RESULT_MAGIC_IDENTIFY].SetStartWithCasting();
//	(*g_pActionInfoTable)[RESULT_MAGIC_IDENTIFY].SetMainNode( 1 );
//	(*g_pActionInfoTable)[RESULT_MAGIC_IDENTIFY].SetSoundID( SOUNDID_NULL );
//	(*g_pActionInfoTable)[RESULT_MAGIC_IDENTIFY].Init( 1 );
//	(*g_pActionInfoTable)[RESULT_MAGIC_IDENTIFY][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_INVENTORY;
////	(*g_pActionInfoTable)[RESULT_MAGIC_IDENTIFY][0].EffectSpriteType	= EFFECTSPRITETYPE_IDENTIFY_1x1;
//	(*g_pActionInfoTable)[RESULT_MAGIC_IDENTIFY][0].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_IDENTIFY][0].Count				= FrameSize[EFFECTSPRITETYPE_IDENTIFY_1x1];
//	(*g_pActionInfoTable)[RESULT_MAGIC_IDENTIFY][0].SoundID			= SOUND_SLAYER_ENCHANT_IDENTIFY;
	
	// MAGIC_REMOVE_CURSE,			// Remove Curse
	(*g_pActionInfoTable)[RESULT_MAGIC_REMOVE_CURSE].Set("RESULT_MAGIC_REMOVE_CURSE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[RESULT_MAGIC_REMOVE_CURSE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_REMOVE_CURSE].Init( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_REMOVE_CURSE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_REMOVE_CURSE][0].EffectSpriteType	= EFFECTSPRITETYPE_REMOVE_CURSE;
	(*g_pActionInfoTable)[RESULT_MAGIC_REMOVE_CURSE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_REMOVE_CURSE][0].Count				= FrameSize[EFFECTSPRITETYPE_REMOVE_CURSE];
	(*g_pActionInfoTable)[RESULT_MAGIC_REMOVE_CURSE][0].SoundID			= SOUND_SLAYER_HEALING_REMOVECURSE;	

	// MAGIC_PROTECTION_FROM_CURSE,	// Protection From Curse
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_CURSE].Set("RESULT_MAGIC_PROTECTION_FROM_CURSE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_CURSE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_CURSE].Init( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_CURSE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_CURSE][0].EffectSpriteType	= EFFECTSPRITETYPE_PROTECTION_FROM_CURSE;
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_CURSE][0].Step				= 26;
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_CURSE][0].Count				= FrameSize[EFFECTSPRITETYPE_PROTECTION_FROM_CURSE];
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_CURSE][0].SoundID			= SOUND_SLAYER_HEALING_PFP;

	// MAGIC_PROTECTION_FROM_ACID,	// Protection From Curse
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_ACID].Set("RESULT_MAGIC_PROTECTION_FROM_ACID", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_ACID].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_ACID].Init( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_ACID][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_ACID][0].EffectSpriteType	= EFFECTSPRITETYPE_PROTECTION_FROM_ACID_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_ACID][0].Step				= 26;
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_ACID][0].Count				= FrameSize[EFFECTSPRITETYPE_PROTECTION_FROM_ACID_1];
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_ACID][0].SoundID			= SOUND_SLAYER_ENCHANT_PFA;

	// MAGIC_CURE_LIGHT_WOUNDS,	// Cure Light Wounds
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_LIGHT_WOUNDS].Set("RESULT_MAGIC_CURE_LIGHT_WOUNDS", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_LIGHT_WOUNDS].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_LIGHT_WOUNDS].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_LIGHT_WOUNDS].Init( 3 );
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_LIGHT_WOUNDS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_LIGHT_WOUNDS][0].EffectSpriteType	= EFFECTSPRITETYPE_CURE_LIGHT_WOUND_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_LIGHT_WOUNDS][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_LIGHT_WOUNDS][0].Count				= FrameSize[EFFECTSPRITETYPE_CURE_LIGHT_WOUND_1];
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_LIGHT_WOUNDS][0].SoundID			= SOUND_SLAYER_CURE_LIGHT_WOUNDS; //SOUND_SLAYER_HEALING_CLW;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_LIGHT_WOUNDS][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_LIGHT_WOUNDS][1].EffectSpriteType	= EFFECTSPRITETYPE_CURE_LIGHT_WOUND_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_LIGHT_WOUNDS][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_LIGHT_WOUNDS][1].Count				= FrameSize[EFFECTSPRITETYPE_CURE_LIGHT_WOUND_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_LIGHT_WOUNDS][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_LIGHT_WOUNDS][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_LIGHT_WOUNDS][2].EffectSpriteType	= EFFECTSPRITETYPE_CURE_LIGHT_WOUND_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_LIGHT_WOUNDS][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_LIGHT_WOUNDS][2].Count				= FrameSize[EFFECTSPRITETYPE_CURE_LIGHT_WOUND_3];
	
	// MAGIC_CURE_SERIOUS_WOUNDS,	// Cure SERIOUS Wounds
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_SERIOUS_WOUNDS].Set("RESULT_MAGIC_CURE_SERIOUS_WOUNDS", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_SERIOUS_WOUNDS].SetSoundID( SOUNDID_NULL );
	//(*g_pActionInfoTable)[RESULT_MAGIC_CURE_SERIOUS_WOUNDS].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_SERIOUS_WOUNDS].Init( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_SERIOUS_WOUNDS].SetMainNode( 1 );	
	//2004, 5, 20 sobeit modify start
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_SERIOUS_WOUNDS][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_RECT;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_SERIOUS_WOUNDS][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_CURE_SERIOUS_WOUNDS_GROUND;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_SERIOUS_WOUNDS][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_SERIOUS_WOUNDS][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_CURE_SERIOUS_WOUNDS_GROUND];
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_SERIOUS_WOUNDS][0].SoundID			= SOUND_SLAYER_HEALING_CSW;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_SERIOUS_WOUNDS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_SERIOUS_WOUNDS][0].EffectSpriteType	= EFFECTSPRITETYPE_CURE_SERIOUS_WOUND_1;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_SERIOUS_WOUNDS][0].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_SERIOUS_WOUNDS][0].Count				= FrameSize[EFFECTSPRITETYPE_CURE_SERIOUS_WOUND_1];
//	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_SERIOUS_WOUNDS][0].SoundID			= SOUND_SLAYER_HEALING_CSW;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_SERIOUS_WOUNDS][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_SERIOUS_WOUNDS][1].EffectSpriteType	= EFFECTSPRITETYPE_CURE_SERIOUS_WOUND_2;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_SERIOUS_WOUNDS][1].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_SERIOUS_WOUNDS][1].Count				= FrameSize[EFFECTSPRITETYPE_CURE_SERIOUS_WOUND_2];
//	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_SERIOUS_WOUNDS][1].SetDelayNode();
//	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_SERIOUS_WOUNDS][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_SERIOUS_WOUNDS][2].EffectSpriteType	= EFFECTSPRITETYPE_CURE_SERIOUS_WOUND_3;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_SERIOUS_WOUNDS][2].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_SERIOUS_WOUNDS][2].Count				= FrameSize[EFFECTSPRITETYPE_CURE_SERIOUS_WOUND_3];
	// 2004, 5, 20 sobeit modify end
		
	// MAGIC_CAUSE_LIGHT_WOUNDS,	// CAUSE Light Wounds
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS].Set("RESULT_MAGIC_CAUSE_LIGHT_WOUNDS", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS].Init( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS].SetMainNode( 1 );	
	// 2004, 5, 20 sobeit modify start
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_CAUSE_LIGHT_WOUNDS_BLOW;
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_CAUSE_LIGHT_WOUNDS_BLOW];
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS][0].SoundID			= SOUND_SLAYER_HEALING_CSW;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS][0].EffectSpriteType	= EFFECTSPRITETYPE_CURE_LIGHT_WOUND_1;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS][0].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS][0].Count				= FrameSize[EFFECTSPRITETYPE_CURE_LIGHT_WOUND_1];
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS][0].SoundID			= SOUND_SLAYER_CAUSE_LIGHT_WOUNDS ; //SOUND_SLAYER_HEALING_CSW;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS][1].EffectSpriteType	= EFFECTSPRITETYPE_CURE_LIGHT_WOUND_2;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS][1].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS][1].Count				= FrameSize[EFFECTSPRITETYPE_CURE_LIGHT_WOUND_2];
//	//(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS][1].SetDelayNode();
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS][1].SetResultTime();
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS][2].EffectSpriteType	= EFFECTSPRITETYPE_CURE_LIGHT_WOUND_3;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS][2].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_LIGHT_WOUNDS][2].Count				= FrameSize[EFFECTSPRITETYPE_CURE_LIGHT_WOUND_3];
	// 2004, 5, 20 sobeit modify end

	// MAGIC_CAUSE_SERIOUS_WOUNDS,	// CAUSE SERIOUS Wounds
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS].Set("RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS].Init( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS].SetMainNode( 1 );	
	//2004, 5, 20 sobeit modify start
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_CAUSE_SERIOUS_WOUNDS_BLOW;
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_CAUSE_SERIOUS_WOUNDS_BLOW];
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS][0].SoundID			= SOUND_SLAYER_CAUSE_SERIOUS_WOUNDS ; //SOUND_SLAYER_HEALING_CLW;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS][0].EffectSpriteType	= EFFECTSPRITETYPE_CURE_SERIOUS_WOUND_1;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS][0].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS][0].Count				= FrameSize[EFFECTSPRITETYPE_CURE_SERIOUS_WOUND_1];
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS][0].SoundID			= SOUND_SLAYER_CAUSE_SERIOUS_WOUNDS; //SOUND_SLAYER_HEALING_CLW;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS][1].EffectSpriteType	= EFFECTSPRITETYPE_CURE_SERIOUS_WOUND_2;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS][1].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS][1].Count				= FrameSize[EFFECTSPRITETYPE_CURE_SERIOUS_WOUND_2];
//	//(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS][1].SetDelayNode();
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS][1].SetResultTime();
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS][2].EffectSpriteType	= EFFECTSPRITETYPE_CURE_SERIOUS_WOUND_3;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS][2].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_SERIOUS_WOUNDS][2].Count				= FrameSize[EFFECTSPRITETYPE_CURE_SERIOUS_WOUND_3];
	//2004, 5, 20 sobeit modify end


	// MAGIC_CURE_POISON,			// Cure Poison
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_POISON].Set("RESULT_MAGIC_CURE_POISON", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_POISON].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_POISON].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_POISON].Init( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_POISON][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_POISON][0].EffectSpriteType	= EFFECTSPRITETYPE_CURE_POISON;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_POISON][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_POISON][0].Count				= FrameSize[EFFECTSPRITETYPE_CURE_POISON];
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_POISON][0].SoundID			= SOUND_SLAYER_HEALING_CP;

	// MAGIC_PROTECTION_FROM_POISON,	// Protection From Poison
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_POISON].Set("RESULT_MAGIC_PROTECTION_FROM_POISON", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_POISON].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_POISON].Init( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_POISON][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_POISON][0].EffectSpriteType	= EFFECTSPRITETYPE_PROTECTION_FROM_POISON;
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_POISON][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_POISON][0].Count				= FrameSize[EFFECTSPRITETYPE_PROTECTION_FROM_POISON];
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_POISON][0].SoundID			= SOUND_SLAYER_HEALING_PFP;

	// MAGIC_CURE_PARALYSIS,		// Cure Paralysis
	/*
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_PARALYSIS].Set("RESULT_MAGIC_CURE_PARALYSIS", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_PARALYSIS].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_PARALYSIS].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_PARALYSIS].Init( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_PARALYSIS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_PARALYSIS][0].EffectSpriteType	= EFFECTSPRITETYPE_CURE_PARALYSIS;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_PARALYSIS][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_PARALYSIS][0].Count				= FrameSize[EFFECTSPRITETYPE_CURE_PARALYSIS];
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_PARALYSIS][0].SoundID			= SOUND_SLAYER_HEALING_CPA;
	*/

	// MAGIC_SACRIFICE,	// Protection From Poison
	(*g_pActionInfoTable)[RESULT_MAGIC_SACRIFICE].Set("RESULT_MAGIC_SACRIFICE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_SACRIFICE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_SACRIFICE].Init( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_SACRIFICE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_SACRIFICE][0].EffectSpriteType	= EFFECTSPRITETYPE_SACRIFICE_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_SACRIFICE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_SACRIFICE][0].Count				= FrameSize[EFFECTSPRITETYPE_SACRIFICE_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_SACRIFICE][0].SoundID			= SOUND_SLAYER_HEAL_SACRIFICE;
	
	// MAGIC_CURE_CRITICAL_WOUNDS,	// Cure Critical Wounds
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS].Set("RESULT_MAGIC_CURE_CRITICAL_WOUNDS", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS].Init( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE_ORBIT;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS][0].EffectSpriteType	= EFFECTSPRITETYPE_CURE_1_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS][0].Count				= FrameSize[EFFECTSPRITETYPE_CURE_1_1];
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS][0].SoundID				= SOUND_SLAYER_CURE_CRITICAL_WOUNDS; //SOUND_SLAYER_HEALING_CCW;	
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS][0].SetDelayNode();

	// RESULT_SKILL_SPIRIT_GUARD,	// Cure Critical Wounds
	(*g_pActionInfoTable)[RESULT_SKILL_SPIRIT_GUARD].Set("RESULT_SKILL_SPIRIT_GUARD", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_SPIRIT_GUARD].SetSoundID(SOUND_SLAYER_SPIRIT_GUARD) ; // SOUND_SLAYER_HEALING_CSW );
	/*
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS].SetMainNode( 1 );	
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS][0].EffectSpriteType	= EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS][0].Count				= FrameSize[EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_1];
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS][0].SoundID				= SLAYER_CURE_CRITICAL_WOUNDS ;//SOUND_SLAYER_HEALING_CCW;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS][1].EffectSpriteType	= EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS][1].Count				= FrameSize[EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS][2].EffectSpriteType	= EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_CRITICAL_WOUNDS][2].Count				= FrameSize[EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_3];
	*/

	// MAGIC_CAUSE_CRITICAL_WOUNDS,	// CAUSE Critical Wounds
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS].Set("RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS].Init( 5 );
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS].SetMainNode( 1 );	
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS][0].EffectSpriteType	= EFFECTSPRITETYPE_CAUSE_CRITICAL_WOUND_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS][0].Count				= FrameSize[EFFECTSPRITETYPE_CAUSE_CRITICAL_WOUND_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS][0].LinkCount				= 4;
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS][0].SoundID				=SOUND_SLAYER_CAUSE_CRITICAL_WOUNDS ; // SOUND_SLAYER_HEALING_CCW;
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE_GROUND;
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS][1].EffectSpriteType	= EFFECTSPRITETYPE_CAUSE_CRITICAL_WOUND_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS][1].Count				= FrameSize[EFFECTSPRITETYPE_CAUSE_CRITICAL_WOUND_1];
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS][1].LinkCount				= 0;
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS][1].SetResultTime();
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE_GROUND;
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS][2].EffectSpriteType	= EFFECTSPRITETYPE_CAUSE_CRITICAL_WOUND_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS][2].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS][2].Count				= FrameSize[EFFECTSPRITETYPE_CAUSE_CRITICAL_WOUND_3];
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS][2].LinkCount				= 0;
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS][3].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS][3].EffectSpriteType	= EFFECTSPRITETYPE_CAUSE_CRITICAL_WOUND_4;
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS][3].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS][3].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS][3].Count				= FrameSize[EFFECTSPRITETYPE_CAUSE_CRITICAL_WOUND_4];

	// MAGIC_PRAYER
	(*g_pActionInfoTable)[RESULT_MAGIC_PRAYER].Set("RESULT_MAGIC_PRAYER", ACTION_STAND, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_PRAYER].SetSoundID( SOUNDID_NULL );

	// MAGIC_MEDITATION
	(*g_pActionInfoTable)[RESULT_MAGIC_MEDITATION].Set("RESULT_MAGIC_MEDITATION", ACTION_STAND, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_MEDITATION].SetSoundID( SOUNDID_NULL );

	// MAGIC_MASS_CURE,	// Cure Critical Wounds
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_CURE].Set("RESULT_MAGIC_MASS_CURE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_CURE].SetSoundID( SOUNDID_NULL );
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_CURE].SetStartWithCasting();
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_CURE].Init( 3 );
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_CURE].SetMainNode( 1 );	
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_CURE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_CURE][0].EffectSpriteType	= EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_1;
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_CURE][0].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_CURE][0].Count				= FrameSize[EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_1];
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_CURE][0].SoundID				= SOUND_SLAYER_HEALING_CCW;
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_CURE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_CURE][1].EffectSpriteType	= EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_2;
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_CURE][1].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_CURE][1].Count				= FrameSize[EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_2];
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_CURE][1].SetDelayNode();
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_CURE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_CURE][2].EffectSpriteType	= EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_3;
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_CURE][2].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_CURE][2].Count				= FrameSize[EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_3];

	// MAGIC_MASS_HEAL,	// Cure Critical Wounds
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_HEAL].Set("RESULT_MAGIC_MASS_HEAL", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_HEAL].SetSoundID( SOUNDID_NULL );
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_HEAL].SetStartWithCasting();
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_HEAL].Init( 3 );
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_HEAL].SetMainNode( 1 );	
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_HEAL][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_HEAL][0].EffectSpriteType	= EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_1;
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_HEAL][0].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_HEAL][0].Count				= FrameSize[EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_1];
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_HEAL][0].SoundID				= SOUND_SLAYER_HEALING_CCW;
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_HEAL][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_HEAL][1].EffectSpriteType	= EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_2;
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_HEAL][1].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_HEAL][1].Count				= FrameSize[EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_2];
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_HEAL][1].SetDelayNode();
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_HEAL][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_HEAL][2].EffectSpriteType	= EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_3;
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_HEAL][2].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_MASS_HEAL][2].Count				= FrameSize[EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_3];


	// MAGIC_PROTECTION_FROM_PARALYSIS,// Protection From Paralysis
	/*
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_PARALYSIS].Set("RESULT_MAGIC_PROTECTION_FROM_PARALYSIS", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_PARALYSIS].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_PARALYSIS].Init( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_PARALYSIS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_PARALYSIS][0].EffectSpriteType	= EFFECTSPRITETYPE_PROTECTION_FROM_PARALYSIS;
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_PARALYSIS][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_PARALYSIS][0].Count				= FrameSize[EFFECTSPRITETYPE_PROTECTION_FROM_PARALYSIS];
	(*g_pActionInfoTable)[RESULT_MAGIC_PROTECTION_FROM_PARALYSIS][0].SoundID			= SOUND_SLAYER_HEALING_PFPA;
	*/

	// MAGIC_RESTORE,				// Restore
	(*g_pActionInfoTable)[RESULT_MAGIC_RESTORE].Set("RESULT_MAGIC_RESTORE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_RESTORE].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_MAGIC_RESTORE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_RESTORE].Init( 3 );
	(*g_pActionInfoTable)[RESULT_MAGIC_RESTORE].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_RESTORE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_RESTORE][0].EffectSpriteType	= EFFECTSPRITETYPE_RESTORE_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_RESTORE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_RESTORE][0].Count				= FrameSize[EFFECTSPRITETYPE_RESTORE_1];
	(*g_pActionInfoTable)[RESULT_MAGIC_RESTORE][0].SoundID			= SOUND_SLAYER_HEALING_R1;
	(*g_pActionInfoTable)[RESULT_MAGIC_RESTORE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_RESTORE][1].EffectSpriteType	= EFFECTSPRITETYPE_RESTORE_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_RESTORE][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_RESTORE][1].Count				= FrameSize[EFFECTSPRITETYPE_RESTORE_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_RESTORE][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_RESTORE][1].SetResultTime();
	(*g_pActionInfoTable)[RESULT_MAGIC_RESTORE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_RESTORE][2].EffectSpriteType	= EFFECTSPRITETYPE_RESTORE_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_RESTORE][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_RESTORE][2].Count				= FrameSize[EFFECTSPRITETYPE_RESTORE_3];
	(*g_pActionInfoTable)[RESULT_MAGIC_RESTORE][2].SoundID			= SOUND_SLAYER_HEALING_R2;


//	// MAGIC_REGENERATION,			// Regeneration
//	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION].Set("RESULT_MAGIC_REGENERATION", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
//	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION].SetSoundID( SOUNDID_NULL );
//	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION].SetStartWithCasting();
//	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION].Init( 1 );
//	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION][0].EffectSpriteType	= EFFECTSPRITETYPE_REGENERATION_1_STAND_MALE;
//	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION][0].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION][0].Count				= FrameSize[EFFECTSPRITETYPE_REGENERATION_1_STAND_MALE];
//	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION][0].SoundID				= SOUND_SLAYER_HEALING_R1;	
//	(*g_pActionInfoTable)[RESULT_MAGIC_REGENERATION][0].SetDelayNode();

	// MAGIC_CURE_ALL,				// Cure All
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_ALL].Set("RESULT_MAGIC_CURE_ALL", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_ALL].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_ALL].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_ALL].Init( 2 );
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_ALL][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_ALL][0].EffectSpriteType	= EFFECTSPRITETYPE_CURE_ALL_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_ALL][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_ALL][0].Count				= FrameSize[EFFECTSPRITETYPE_CURE_ALL_1];
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_ALL][0].SoundID			= SOUND_SLAYER_HEALING_R1;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_ALL][0].LinkCount			= 15;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_ALL][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_ALL][1].EffectSpriteType	= EFFECTSPRITETYPE_CURE_ALL_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_ALL][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_CURE_ALL][1].Count				= FrameSize[EFFECTSPRITETYPE_CURE_ALL_2];
	

	// MAGIC_RESURRECT
	(*g_pActionInfoTable)[RESULT_MAGIC_RESURRECT].Set("RESULT_MAGIC_RESURRECT", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_RESURRECT].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_MAGIC_RESURRECT].SetSoundID( SOUND_SLAYER_RESURRECT) ; //SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MAGIC_RESURRECT].Init( 3 );
	(*g_pActionInfoTable)[RESULT_MAGIC_RESURRECT].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_MAGIC_RESURRECT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_RESURRECT][0].EffectSpriteType	= EFFECTSPRITETYPE_RESTORE_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_RESURRECT][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_RESURRECT][0].Count				= FrameSize[EFFECTSPRITETYPE_RESTORE_1];
	//(*g_pActionInfoTable)[RESULT_MAGIC_RESURRECT][0].SoundID			= SOUND_SLAYER_HEALING_R1;
	(*g_pActionInfoTable)[RESULT_MAGIC_RESURRECT][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_RESURRECT][1].EffectSpriteType	= EFFECTSPRITETYPE_RESTORE_2;
	(*g_pActionInfoTable)[RESULT_MAGIC_RESURRECT][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_RESURRECT][1].Count				= FrameSize[EFFECTSPRITETYPE_RESTORE_2];
	(*g_pActionInfoTable)[RESULT_MAGIC_RESURRECT][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_MAGIC_RESURRECT][1].SetResultTime();
	(*g_pActionInfoTable)[RESULT_MAGIC_RESURRECT][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_RESURRECT][2].EffectSpriteType	= EFFECTSPRITETYPE_RESTORE_3;
	(*g_pActionInfoTable)[RESULT_MAGIC_RESURRECT][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MAGIC_RESURRECT][2].Count				= FrameSize[EFFECTSPRITETYPE_RESTORE_3];
	//(*g_pActionInfoTable)[RESULT_MAGIC_RESURRECT][2].SoundID			= SOUND_SLAYER_HEALING_R2;


	// MAGIC_AURA_STORM,				// Aura Storm
	/*
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_STORM].Set("RESULT_MAGIC_AURA_STORM", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_AURA_STORM].SetSoundID( SOUNDID_NULL );
	*/
	

	//-------------------------------------------------------------
	//
	//                          BOMB
	//
	//-------------------------------------------------------------

	// BOMB_ACER
	(*g_pActionInfoTable)[RESULT_BOMB_ACER].Set("RESULT_BOMB_ACER", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_BOMB_ACER].SetSoundID( SOUND_DAMAGE_BOMB );

	// BOMB_BULLS	
	(*g_pActionInfoTable)[RESULT_BOMB_BULLS].Set("RESULT_BOMB_BULLS", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);	
	(*g_pActionInfoTable)[RESULT_BOMB_BULLS].SetSoundID( SOUND_DAMAGE_BOMB );

	// BOMB_SPLINTER
	(*g_pActionInfoTable)[RESULT_BOMB_SPLINTER].Set("RESULT_BOMB_SPLINTER", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);	
	(*g_pActionInfoTable)[RESULT_BOMB_SPLINTER].SetSoundID( SOUND_DAMAGE_BOMB );

	// BOMB_STUN
	(*g_pActionInfoTable)[RESULT_BOMB_STUN].Set("RESULT_BOMB_STUN", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_BOMB_STUN].SetSoundID( SOUND_DAMAGE_BOMB );

	// BOMB_CROSSBOW
	(*g_pActionInfoTable)[RESULT_BOMB_CROSSBOW].Set("RESULT_BOMB_CROSSBOW", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_BOMB_CROSSBOW].SetSoundID( SOUND_DAMAGE_BOMB );

	// BOMB_TWISTER
	(*g_pActionInfoTable)[RESULT_BOMB_TWISTER].Set("RESULT_BOMB_TWISTER", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_BOMB_TWISTER].SetSoundID( SOUND_DAMAGE_BOMB );
	

	//-------------------------------------------------------------
	//
	//                          MINE
	//
	//-------------------------------------------------------------

	// MINE_VIPER
	(*g_pActionInfoTable)[RESULT_MINE_ANKLE_KILLER].Set("RESULT_MINE_ANKLE_KILLER", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MINE_ANKLE_KILLER].SetSoundID( SOUND_DAMAGE_BOMB );

	// MINE_VIPER
	(*g_pActionInfoTable)[RESULT_MINE_POMZ].Set("RESULT_MINE_POMZ", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MINE_POMZ].SetSoundID( SOUND_DAMAGE_BOMB );

	// MINE_VIPER
	(*g_pActionInfoTable)[RESULT_MINE_AP_C1].Set("RESULT_MINE_AP_C1", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MINE_AP_C1].SetSoundID( SOUND_DAMAGE_BOMB );

	// MINE_VIPER
	(*g_pActionInfoTable)[RESULT_MINE_SWIFT_EX].Set("RESULT_MINE_SWIFT_EX", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MINE_SWIFT_EX].SetSoundID( SOUND_DAMAGE_BOMB );

	// MINE_DIAMONDBACK	
	(*g_pActionInfoTable)[RESULT_MINE_DIAMONDBACK].Set("RESULT_MINE_DIAMONDBACK", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MINE_DIAMONDBACK].SetSoundID( SOUND_DAMAGE_BOMB );

	// MINE_SIDEWINDER	
	(*g_pActionInfoTable)[RESULT_MINE_SIDEWINDER].Set("RESULT_MINE_SIDEWINDER", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MINE_SIDEWINDER].SetSoundID( SOUND_DAMAGE_BOMB );

	// MINE_COBRA
	(*g_pActionInfoTable)[RESULT_MINE_COBRA].Set("RESULT_MINE_COBRA", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MINE_COBRA].SetSoundID( SOUND_DAMAGE_BOMB );

	// Soul Chain
	(*g_pActionInfoTable)[RESULT_SKILL_SOUL_CHAIN].Set("RESULT_SKILL_SOUL_CHAIN", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_SOUL_CHAIN].SetSoundID( SOUNDID_NULL );

	//-------------------------------------------------------------
	//
	//                          ETC
	//
	//-------------------------------------------------------------

	/*
	// SKILL_THROW_HOLY_WATER
	(*g_pActionInfoTable)[RESULT_SKILL_THROW_HOLY_WATER].Set("RESULT_SKILL_THROW_HOLY_WATER", ACTION_DAMAGED, EFFECTSPRITETYPE_BLOOD, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_THROW_HOLY_WATER].Init( 1 );	
	(*g_pActionInfoTable)[RESULT_SKILL_THROW_HOLY_WATER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_THROW_HOLY_WATER][0].EffectSpriteType	= EFFECTSPRITETYPE_HOLY_WATER_1;
	(*g_pActionInfoTable)[RESULT_SKILL_THROW_HOLY_WATER][0].Step				= 30;
	(*g_pActionInfoTable)[RESULT_SKILL_THROW_HOLY_WATER][0].Count				= FrameSize[EFFECTSPRITETYPE_HOLY_WATER_1];
	(*g_pActionInfoTable)[RESULT_SKILL_THROW_HOLY_WATER][0].SoundID				= SOUND_DAMAGE_BOTTLE;
	*/

	// MAGIC_THROW_HOLY_WATER
	(*g_pActionInfoTable)[RESULT_MAGIC_THROW_HOLY_WATER].Set("RESULT_MAGIC_THROW_HOLY_WATER", ACTION_DAMAGED, EFFECTSPRITETYPE_BLOOD, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_MAGIC_THROW_HOLY_WATER].Init( 1 );	
	(*g_pActionInfoTable)[RESULT_MAGIC_THROW_HOLY_WATER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_MAGIC_THROW_HOLY_WATER][0].EffectSpriteType	= EFFECTSPRITETYPE_HOLY_WATER_1;
	(*g_pActionInfoTable)[RESULT_MAGIC_THROW_HOLY_WATER][0].Step				= 30;
	(*g_pActionInfoTable)[RESULT_MAGIC_THROW_HOLY_WATER][0].Count				= FrameSize[EFFECTSPRITETYPE_HOLY_WATER_1];
	(*g_pActionInfoTable)[RESULT_MAGIC_THROW_HOLY_WATER][0].SoundID				= SOUND_DAMAGE_BOTTLE;
	(*g_pActionInfoTable)[RESULT_MAGIC_THROW_HOLY_WATER][0].SetResultTime();
	
	
	// GUIDANCE_FIRE
	(*g_pActionInfoTable)[RESULT_GUIDANCE_FIRE].Set("RESULT_GUIDANCE_FIRE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[RESULT_GUIDANCE_FIRE].SetSoundID( SOUNDID_NULL );

	// FALLING_LIGHTNING
	(*g_pActionInfoTable)[RESULT_FALLING_LIGHTNING].Set("RESULT_FALLING_LIGHTNING", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET | FLAG_ACTIONINFO_START_SKY, 300);
	(*g_pActionInfoTable)[RESULT_FALLING_LIGHTNING].SetSoundID( SOUNDID_NULL );
	
	// ATTACH_FIRE
	(*g_pActionInfoTable)[RESULT_ATTACH_FIRE].Set("RESULT_ATTACH_FIRE", ACTION_DAMAGED, EFFECTSPRITETYPE_BLOOD_GUN_3_1, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_ATTACH_FIRE].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_ATTACH_FIRE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_ATTACH_FIRE].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_ATTACH_FIRE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_ATTACH_FIRE][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_KNIFE_2;
	(*g_pActionInfoTable)[RESULT_ATTACH_FIRE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_ATTACH_FIRE][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_KNIFE_2];
	(*g_pActionInfoTable)[RESULT_ATTACH_FIRE][0].SoundID				= SOUND_VAMPIRE_MISC_D;	
	(*g_pActionInfoTable)[RESULT_ATTACH_FIRE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_ATTACH_FIRE][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_KNIFE_2;
	(*g_pActionInfoTable)[RESULT_ATTACH_FIRE][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_ATTACH_FIRE][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_KNIFE_2];
	(*g_pActionInfoTable)[RESULT_ATTACH_FIRE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_ATTACH_FIRE][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_KNIFE_2;
	(*g_pActionInfoTable)[RESULT_ATTACH_FIRE][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_ATTACH_FIRE][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_KNIFE_2];

	// ATTACH_AURA
	(*g_pActionInfoTable)[RESULT_ATTACH_AURA].Set("RESULT_ATTACH_AURA", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_ATTACH_AURA].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_ATTACH_AURA].Init( 1 );
	(*g_pActionInfoTable)[RESULT_ATTACH_AURA][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_ATTACH_AURA][0].EffectSpriteType	= EFFECTSPRITETYPE_GREEN_STALKER_3;
	(*g_pActionInfoTable)[RESULT_ATTACH_AURA][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_ATTACH_AURA][0].Count				= FrameSize[EFFECTSPRITETYPE_ACID_BOLT_2];
	(*g_pActionInfoTable)[RESULT_ATTACH_AURA][0].SoundID			= SOUND_VAMPIRE_ACID_ABOLT2;	
	

	// RESULT_SLAYER_DIE
	(*g_pActionInfoTable)[RESULT_SLAYER_DIE].Set("RESULT_SLAYER_DIE", ACTION_DIE, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 500);
	(*g_pActionInfoTable)[RESULT_SLAYER_DIE].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SLAYER_DIE].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_SLAYER_DIE].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_SLAYER_DIE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SLAYER_DIE][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_SLAYER_1;
	(*g_pActionInfoTable)[RESULT_SLAYER_DIE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SLAYER_DIE][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_SLAYER_1];
	(*g_pActionInfoTable)[RESULT_SLAYER_DIE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SLAYER_DIE][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_SLAYER_2;
	(*g_pActionInfoTable)[RESULT_SLAYER_DIE][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SLAYER_DIE][1].Count				= 16*10;	//FrameSize[EFFECTSPRITETYPE_BLOOD_SLAYER_2];
	(*g_pActionInfoTable)[RESULT_SLAYER_DIE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SLAYER_DIE][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_SLAYER_3;
	(*g_pActionInfoTable)[RESULT_SLAYER_DIE][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SLAYER_DIE][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_SLAYER_3];

	// RESULT_FAKE_DIE
	(*g_pActionInfoTable)[RESULT_FAKE_DIE].Set("RESULT_FAKE_DIE", ACTION_DIE, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 500);
	(*g_pActionInfoTable)[RESULT_FAKE_DIE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_FAKE_DIE].SetStartFrameAll( 15 );
	(*g_pActionInfoTable)[RESULT_FAKE_DIE].SetActionResult( ACTIONRESULTNODE_FAKE_DIE );

	// CASTING_ENCHANT
	(*g_pActionInfoTable)[CASTING_ENCHANT].Set("CASTING_ENCHANT", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 500);
	(*g_pActionInfoTable)[CASTING_ENCHANT].SetCastingAction();
	(*g_pActionInfoTable)[CASTING_ENCHANT].SetStartWithCasting();
	(*g_pActionInfoTable)[CASTING_ENCHANT].Init( 2 );		
	(*g_pActionInfoTable)[CASTING_ENCHANT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[CASTING_ENCHANT][0].EffectSpriteType	= EFFECTSPRITETYPE_ENCHANT_CASTING_GROUND;
	(*g_pActionInfoTable)[CASTING_ENCHANT][0].Step				= 25;
	(*g_pActionInfoTable)[CASTING_ENCHANT][0].Count				= FrameSize[EFFECTSPRITETYPE_ENCHANT_CASTING_GROUND];
	(*g_pActionInfoTable)[CASTING_ENCHANT][0].LinkCount			= 0;
	(*g_pActionInfoTable)[CASTING_ENCHANT][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[CASTING_ENCHANT][1].EffectSpriteType	= EFFECTSPRITETYPE_ENCHANT_CASTING;
	(*g_pActionInfoTable)[CASTING_ENCHANT][1].Step				= 25;
	(*g_pActionInfoTable)[CASTING_ENCHANT][1].Count				= FrameSize[EFFECTSPRITETYPE_ENCHANT_CASTING];	
		
	/*
	(*g_pActionInfoTable)[CASTING_ENCHANT].SetMainNode( 1 );
	(*g_pActionInfoTable)[CASTING_ENCHANT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[CASTING_ENCHANT][0].EffectSpriteType	= EFFECTSPRITETYPE_ENCHANT_CASTING1_1;
	(*g_pActionInfoTable)[CASTING_ENCHANT][0].Step				= 25;
	(*g_pActionInfoTable)[CASTING_ENCHANT][0].Count				= FrameSize[EFFECTSPRITETYPE_ENCHANT_CASTING1_1];
	(*g_pActionInfoTable)[CASTING_ENCHANT][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[CASTING_ENCHANT][1].EffectSpriteType	= EFFECTSPRITETYPE_ENCHANT_CASTING1_2;
	(*g_pActionInfoTable)[CASTING_ENCHANT][1].Step				= 25;
	(*g_pActionInfoTable)[CASTING_ENCHANT][1].Count				= FrameSize[EFFECTSPRITETYPE_ENCHANT_CASTING1_2];
	(*g_pActionInfoTable)[CASTING_ENCHANT][1].LinkCount			= 0;
	//(*g_pActionInfoTable)[CASTING_ENCHANT][1].SetDelayNode();
	(*g_pActionInfoTable)[CASTING_ENCHANT][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[CASTING_ENCHANT][2].EffectSpriteType	= EFFECTSPRITETYPE_ENCHANT_CASTING2_2;
	(*g_pActionInfoTable)[CASTING_ENCHANT][2].Step				= 25;
	(*g_pActionInfoTable)[CASTING_ENCHANT][2].Count				= FrameSize[EFFECTSPRITETYPE_ENCHANT_CASTING2_2];
	//(*g_pActionInfoTable)[CASTING_ENCHANT][2].SetDelayNode();
	(*g_pActionInfoTable)[CASTING_ENCHANT][3].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[CASTING_ENCHANT][3].EffectSpriteType	= EFFECTSPRITETYPE_ENCHANT_CASTING1_3;
	(*g_pActionInfoTable)[CASTING_ENCHANT][3].Step				= 25;
	(*g_pActionInfoTable)[CASTING_ENCHANT][3].Count				= FrameSize[EFFECTSPRITETYPE_ENCHANT_CASTING1_3];
	*/

	// CASTING_HEALING
	(*g_pActionInfoTable)[CASTING_HEALING].Set("CASTING_HEALING", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 500);
	(*g_pActionInfoTable)[CASTING_HEALING].SetCastingAction();
	(*g_pActionInfoTable)[CASTING_HEALING].SetStartWithCasting();
	(*g_pActionInfoTable)[CASTING_HEALING].Init( 1 );
	(*g_pActionInfoTable)[CASTING_HEALING][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[CASTING_HEALING][0].EffectSpriteType	= EFFECTSPRITETYPE_HEAL_CASTING;
	(*g_pActionInfoTable)[CASTING_HEALING][0].Step				= 25;
	(*g_pActionInfoTable)[CASTING_HEALING][0].Count				= FrameSize[EFFECTSPRITETYPE_HEAL_CASTING];	
	/*
	(*g_pActionInfoTable)[CASTING_HEALING].SetMainNode( 1 );
	(*g_pActionInfoTable)[CASTING_HEALING][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[CASTING_HEALING][0].EffectSpriteType	= EFFECTSPRITETYPE_HEALING_CASTING_1;
	(*g_pActionInfoTable)[CASTING_HEALING][0].Step				= 25;
	(*g_pActionInfoTable)[CASTING_HEALING][0].Count				= FrameSize[EFFECTSPRITETYPE_HEALING_CASTING_1];
	(*g_pActionInfoTable)[CASTING_HEALING][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[CASTING_HEALING][1].EffectSpriteType	= EFFECTSPRITETYPE_HEALING_CASTING_2;
	(*g_pActionInfoTable)[CASTING_HEALING][1].Step				= 25;
	(*g_pActionInfoTable)[CASTING_HEALING][1].Count				= FrameSize[EFFECTSPRITETYPE_HEALING_CASTING_2];
	//(*g_pActionInfoTable)[CASTING_HEALING][1].SetDelayNode();
	(*g_pActionInfoTable)[CASTING_HEALING][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[CASTING_HEALING][2].EffectSpriteType	= EFFECTSPRITETYPE_HEALING_CASTING_3;
	(*g_pActionInfoTable)[CASTING_HEALING][2].Step				= 25;
	(*g_pActionInfoTable)[CASTING_HEALING][2].Count				= FrameSize[EFFECTSPRITETYPE_HEALING_CASTING_3];
	*/

	// REFLECT_AURA_PRISM,	// aura prism 방어막
	(*g_pActionInfoTable)[REFLECT_AURA_PRISM].Set("REFLECT_AURA_PRISM", ACTION_STAND, EFFECTSPRITETYPE_AURA_PRISM_SHIELD, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[REFLECT_AURA_PRISM].SetCastingFramesAll( 8 );
	(*g_pActionInfoTable)[REFLECT_AURA_PRISM].SetSoundID( SOUNDID_NULL );
	
	// REFLECT_AURA_SHIELD,	// aura shield 방어막
	(*g_pActionInfoTable)[REFLECT_AURA_SHIELD].Set("REFLECT_AURA_SHIELD", ACTION_STAND, EFFECTSPRITETYPE_AURA_SHIELD_3, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[REFLECT_AURA_SHIELD].SetCastingFramesAll( 5 );
	(*g_pActionInfoTable)[REFLECT_AURA_SHIELD].SetSoundID( SOUND_SLAYER_ENCHANT_AURASHIELD2 );

	// PROTECTION_FROM_ACID,	// aura shield 방어막
	(*g_pActionInfoTable)[PROTECTION_FROM_ACID].Set("PROTECTION_FROM_ACID", ACTION_STAND, EFFECTSPRITETYPE_PROTECTION_FROM_ACID_2, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[PROTECTION_FROM_ACID].SetCastingFramesAll( 5 );
	(*g_pActionInfoTable)[PROTECTION_FROM_ACID].SetSoundID( SOUND_SLAYER_ENCHANT_AURASHIELD2 );

	
	// BLOOD_DROP_GROUND
	(*g_pActionInfoTable)[BLOOD_DROP_GROUND].Set("BLOOD_DROP_GROUND", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[BLOOD_DROP_GROUND].SetStartWithCasting();
	(*g_pActionInfoTable)[BLOOD_DROP_GROUND].Init( 1 );		
	(*g_pActionInfoTable)[BLOOD_DROP_GROUND].SetMainNode( 1 );
	(*g_pActionInfoTable)[BLOOD_DROP_GROUND][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[BLOOD_DROP_GROUND][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_GROUND_2_1;
	(*g_pActionInfoTable)[BLOOD_DROP_GROUND][0].Step				= 25;
	(*g_pActionInfoTable)[BLOOD_DROP_GROUND][0].Count				= 5*16; //FrameSize[EFFECTSPRITETYPE_BLOOD_GROUND_2_1];
	(*g_pActionInfoTable)[BLOOD_DROP_GROUND][0].SetDelayNode();

	// BLOOD_CRITICAL_HIT
	(*g_pActionInfoTable)[BLOOD_CRITICAL_HIT].Set("BLOOD_CRITICAL_HIT", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[BLOOD_CRITICAL_HIT].SetStartWithCasting();
	(*g_pActionInfoTable)[BLOOD_CRITICAL_HIT].Init( 1 );		
	(*g_pActionInfoTable)[BLOOD_CRITICAL_HIT].SetMainNode( 1 );
	(*g_pActionInfoTable)[BLOOD_CRITICAL_HIT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[BLOOD_CRITICAL_HIT][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_GROUND_1_1;
	(*g_pActionInfoTable)[BLOOD_CRITICAL_HIT][0].Step				= 25;
	(*g_pActionInfoTable)[BLOOD_CRITICAL_HIT][0].Count				= 5*16;	//FrameSize[EFFECTSPRITETYPE_BLOOD_GROUND_1_1];
	(*g_pActionInfoTable)[BLOOD_CRITICAL_HIT][0].SetDelayNode();

	// BLOOD_RESURRECT
	(*g_pActionInfoTable)[BLOOD_RESURRECT].Set("BLOOD_RESURRECT", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[BLOOD_RESURRECT].SetStartWithCasting();
	(*g_pActionInfoTable)[BLOOD_RESURRECT].Init( 3 );
	(*g_pActionInfoTable)[BLOOD_RESURRECT].SetMainNode( 1 );
	(*g_pActionInfoTable)[BLOOD_RESURRECT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[BLOOD_RESURRECT][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_DRAIN_1;
	(*g_pActionInfoTable)[BLOOD_RESURRECT][0].Step				= 25;
	(*g_pActionInfoTable)[BLOOD_RESURRECT][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_DRAIN_1];
	(*g_pActionInfoTable)[BLOOD_RESURRECT][0].SoundID				= SOUND_VAMPIRE_MISC_BD;
	(*g_pActionInfoTable)[BLOOD_RESURRECT][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[BLOOD_RESURRECT][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_DRAIN_2;
	(*g_pActionInfoTable)[BLOOD_RESURRECT][1].Step				= 25;
	(*g_pActionInfoTable)[BLOOD_RESURRECT][1].Count				= 2* FrameSize[EFFECTSPRITETYPE_BLOOD_DRAIN_2];
	(*g_pActionInfoTable)[BLOOD_RESURRECT][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[BLOOD_RESURRECT][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_DRAIN_3;
	(*g_pActionInfoTable)[BLOOD_RESURRECT][1].Step				= 25;
	(*g_pActionInfoTable)[BLOOD_RESURRECT][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_DRAIN_3];
	

	// SUMMON_HELICOPTER
	(*g_pActionInfoTable)[SUMMON_HELICOPTER].Set("SUMMON_HELICOPTER", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_ITEM, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_STAND]);	
	(*g_pActionInfoTable)[SUMMON_HELICOPTER].SetStartFrameAll( 6 );
	(*g_pActionInfoTable)[SUMMON_HELICOPTER].SetSoundID( SOUNDID_NULL );	

	// SUMMON_HELICOPTER
	(*g_pActionInfoTable)[RESULT_SUMMON_HELICOPTER].Set("RESULT_SUMMON_HELICOPTER", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_ITEM, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_STAND]);	
	(*g_pActionInfoTable)[RESULT_SUMMON_HELICOPTER].SetStartFrameAll( 6 );
	(*g_pActionInfoTable)[RESULT_SUMMON_HELICOPTER].SetSoundID( SOUNDID_NULL );	

	// SKILL_EARTHQUAKE
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE].Set("SKILL_EARTHQUAKE", ACTION_SLAYER_BLADE_2, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_BLADE]);
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE].SetActionStepCnt(2) ;
	//(*g_pActionInfoTable)[SKILL_EARTHQUAKE].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE].SetActionStepCnt(2) ;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE].Init( 10 );		
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][0].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][0].EffectSpriteType	= EFFECTSPRITETYPE_EARTHQUAKE_1;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][0].Step				= 28;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][0].Count				= FrameSize[EFFECTSPRITETYPE_EARTHQUAKE_1];
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][0].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][0].SoundID				= SOUND_SLAYER_EARTHQUAKE; //SOUND_SLAYER_BLADE_EARTHQUAKE;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][0].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][1].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][1].EffectSpriteType	= EFFECTSPRITETYPE_EARTHQUAKE_1;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][1].Step				= 28;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][1].Count				= FrameSize[EFFECTSPRITETYPE_EARTHQUAKE_1];
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][1].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][2].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][2].EffectSpriteType	= EFFECTSPRITETYPE_EARTHQUAKE_1;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][2].Step				= 28;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][2].Count				= FrameSize[EFFECTSPRITETYPE_EARTHQUAKE_1];
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][2].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][2].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][3].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][3].EffectSpriteType	= EFFECTSPRITETYPE_EARTHQUAKE_1;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][3].Step				= 28;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][3].Count				= FrameSize[EFFECTSPRITETYPE_EARTHQUAKE_1];
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][3].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][3].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][4].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][4].EffectSpriteType	= EFFECTSPRITETYPE_EARTHQUAKE_1;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][4].Step				= 28;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][4].Count				= FrameSize[EFFECTSPRITETYPE_EARTHQUAKE_1];
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][4].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][4].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][5].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][5].EffectSpriteType	= EFFECTSPRITETYPE_EARTHQUAKE_1;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][5].Step				= 28;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][5].Count				= FrameSize[EFFECTSPRITETYPE_EARTHQUAKE_1];
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][5].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][5].SetDelayNode();	
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][5].SetResultTime();
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][6].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][6].EffectSpriteType	= EFFECTSPRITETYPE_EARTHQUAKE_1;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][6].Step				= 28;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][6].Count				= FrameSize[EFFECTSPRITETYPE_EARTHQUAKE_1];
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][6].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][6].SetDelayNode();	
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][7].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][7].EffectSpriteType	= EFFECTSPRITETYPE_EARTHQUAKE_1;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][7].Step				= 28;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][7].Count				= FrameSize[EFFECTSPRITETYPE_EARTHQUAKE_1];
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][7].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][7].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][8].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][8].EffectSpriteType	= EFFECTSPRITETYPE_EARTHQUAKE_1;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][8].Step				= 28;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][8].Count				= FrameSize[EFFECTSPRITETYPE_EARTHQUAKE_1];
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][8].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][8].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][9].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][9].EffectSpriteType	= EFFECTSPRITETYPE_EARTHQUAKE_1;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][9].Step				= 28;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][9].Count				= FrameSize[EFFECTSPRITETYPE_EARTHQUAKE_1];
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][9].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE][9].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_EARTHQUAKE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_EARTHQUAKE );	// 맞는 결과를 표현한다.	

	// SKILL_EARTHQUAKE
	(*g_pActionInfoTable)[RESULT_SKILL_EARTHQUAKE].Set("RESULT_SKILL_EARTHQUAKE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_EARTHQUAKE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_EARTHQUAKE].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_EARTHQUAKE].Init( 3 );
	(*g_pActionInfoTable)[RESULT_SKILL_EARTHQUAKE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_EARTHQUAKE][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_GROUND_2_1;
	(*g_pActionInfoTable)[RESULT_SKILL_EARTHQUAKE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_EARTHQUAKE][0].Count				= 4*16; //FrameSize[EFFECTSPRITETYPE_BLOOD_GROUND_2_1];
	(*g_pActionInfoTable)[RESULT_SKILL_EARTHQUAKE][0].LinkCount			= 1;
	(*g_pActionInfoTable)[RESULT_SKILL_EARTHQUAKE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_EARTHQUAKE][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_GROUND_2_1;
	(*g_pActionInfoTable)[RESULT_SKILL_EARTHQUAKE][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_EARTHQUAKE][1].Count				= 4*16; //FrameSize[EFFECTSPRITETYPE_BLOOD_GROUND_2_1];
	(*g_pActionInfoTable)[RESULT_SKILL_EARTHQUAKE][1].LinkCount			= 1;
	(*g_pActionInfoTable)[RESULT_SKILL_EARTHQUAKE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_EARTHQUAKE][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_GROUND_2_1;
	(*g_pActionInfoTable)[RESULT_SKILL_EARTHQUAKE][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_EARTHQUAKE][2].Count				= 4*16; //FrameSize[EFFECTSPRITETYPE_BLOOD_GROUND_2_1];
	(*g_pActionInfoTable)[RESULT_SKILL_EARTHQUAKE][2].SetResultTime();
	
	// SKILL_POWER_OF_LAND
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND].Set("SKILL_POWER_OF_LAND", ACTION_SLAYER_BLADE_2, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_BLADE]);
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND].SetActionStepCnt(2) ;
	//(*g_pActionInfoTable)[SKILL_POWER_OF_LAND].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND].SetSoundID( SOUND_SLAYER_POWER_OF_LAND) ; //SOUND_SLAYER_BLADE_EARTHQUAKE );
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND].Init( 10 );		
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][0].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][0].EffectSpriteType	= EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][0].Step				= 28;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][0].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1];
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][0].LinkCount			= 1;
//	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][0].SoundID				= SOUND_SLAYER_BLADE_EARTHQUAKE;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][0].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][1].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][1].EffectSpriteType	= EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][1].Step				= 28;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][1].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1];
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][1].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][2].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][2].EffectSpriteType	= EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][2].Step				= 28;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][2].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1];
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][2].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][2].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][3].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][3].EffectSpriteType	= EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][3].Step				= 28;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][3].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1];
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][3].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][3].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][4].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][4].EffectSpriteType	= EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][4].Step				= 28;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][4].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1];
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][4].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][4].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][5].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][5].EffectSpriteType	= EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][5].Step				= 28;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][5].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1];
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][5].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][5].SetDelayNode();	
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][6].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][6].EffectSpriteType	= EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][6].Step				= 28;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][6].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1];
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][6].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][6].SetDelayNode();	
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][7].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][7].EffectSpriteType	= EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][7].Step				= 28;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][7].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1];
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][7].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][7].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][8].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][8].EffectSpriteType	= EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][8].Step				= 28;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][8].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1];
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][8].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][8].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][9].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][9].EffectSpriteType	= EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][9].Step				= 28;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][9].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1];
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][9].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][9].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND][9].SetResultTime();
//	(*g_pActionInfoTable)[SKILL_POWER_OF_LAND].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_POWER_OF_LAND );	// 맞는 결과를 표현한다.	

	// SKILL_POWER_OF_LAND
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND].Set("RESULT_SKILL_POWER_OF_LAND", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND].SetSoundID( SOUNDID_NULL);///SOUND_ITEM_BOOM3 );
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND].Init( 9 );
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][0].EffectSpriteType	= EFFECTSPRITETYPE_POWER_OF_LAND_FIRE_1;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][0].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_FIRE_1];
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][0].LinkCount			= 2;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][0].SoundID			= SOUND_SLAYER_SWORD_EXPANSION;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][0].SetResultTime();
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][1].EffectGeneratorID	= EFFECTGENERATORID_AROUND_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][1].EffectSpriteType	= EFFECTSPRITETYPE_POWER_OF_LAND_FIRE_2;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][1].Step				= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][1].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_FIRE_2];
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][1].LinkCount			= 1;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][2].EffectGeneratorID	= EFFECTGENERATORID_AROUND_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][2].EffectSpriteType	= EFFECTSPRITETYPE_POWER_OF_LAND_FIRE_2;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][2].Step				= 1;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][2].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_FIRE_2];
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][2].LinkCount			= 1;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][3].EffectGeneratorID	= EFFECTGENERATORID_AROUND_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][3].EffectSpriteType	= EFFECTSPRITETYPE_POWER_OF_LAND_FIRE_2;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][3].Step				= 2;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][3].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_FIRE_2];
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][3].LinkCount			= 1;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][4].EffectGeneratorID	= EFFECTGENERATORID_AROUND_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][4].EffectSpriteType	= EFFECTSPRITETYPE_POWER_OF_LAND_FIRE_2;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][4].Step				= 3;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][4].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_FIRE_2];
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][4].LinkCount			= 1;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][5].EffectGeneratorID	= EFFECTGENERATORID_AROUND_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][5].EffectSpriteType	= EFFECTSPRITETYPE_POWER_OF_LAND_FIRE_2;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][5].Step				= 4;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][5].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_FIRE_2];
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][5].LinkCount			= 1;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][6].EffectGeneratorID	= EFFECTGENERATORID_AROUND_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][6].EffectSpriteType	= EFFECTSPRITETYPE_POWER_OF_LAND_FIRE_2;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][6].Step				= 5;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][6].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_FIRE_2];
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][6].LinkCount			= 1;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][7].EffectGeneratorID	= EFFECTGENERATORID_AROUND_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][7].EffectSpriteType	= EFFECTSPRITETYPE_POWER_OF_LAND_FIRE_2;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][7].Step				= 6;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][7].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_FIRE_2];
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][7].LinkCount			= 1;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][8].EffectGeneratorID	= EFFECTGENERATORID_AROUND_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][8].EffectSpriteType	= EFFECTSPRITETYPE_POWER_OF_LAND_FIRE_2;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][8].Step				= 7;
	(*g_pActionInfoTable)[RESULT_SKILL_POWER_OF_LAND][8].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_FIRE_2];
	

	// SKILL_WIND_DIVIDER
	(*g_pActionInfoTable)[SKILL_WIND_DIVIDER].Set("SKILL_WIND_DIVIDER", ACTION_SLAYER_SWORD_2, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_SWORD_2]);
	(*g_pActionInfoTable)[SKILL_WIND_DIVIDER].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_WIND_DIVIDER].SetActionStepCnt(2) ; 
	//(*g_pActionInfoTable)[SKILL_WIND_DIVIDER].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_WIND_DIVIDER].SetStartFrameAll( 7 );
	(*g_pActionInfoTable)[SKILL_WIND_DIVIDER].SetSoundID( SOUND_SLAYER_SWORD_WINDDIVIDER );
	(*g_pActionInfoTable)[SKILL_WIND_DIVIDER].Init( 3 );		
	(*g_pActionInfoTable)[SKILL_WIND_DIVIDER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE;
	(*g_pActionInfoTable)[SKILL_WIND_DIVIDER][0].EffectSpriteType	= EFFECTSPRITETYPE_WIND_DIVIDER_1;
	(*g_pActionInfoTable)[SKILL_WIND_DIVIDER][0].Step				= 20;
	(*g_pActionInfoTable)[SKILL_WIND_DIVIDER][0].Count			= FrameSize[EFFECTSPRITETYPE_WIND_DIVIDER_1];
	(*g_pActionInfoTable)[SKILL_WIND_DIVIDER][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE;
	(*g_pActionInfoTable)[SKILL_WIND_DIVIDER][1].EffectSpriteType	= EFFECTSPRITETYPE_WIND_DIVIDER_2;
	(*g_pActionInfoTable)[SKILL_WIND_DIVIDER][1].Step				= 20;
	(*g_pActionInfoTable)[SKILL_WIND_DIVIDER][1].Count			= 16;//FrameSize[EFFECTSPRITETYPE_WIND_DIVIDER_2];
	(*g_pActionInfoTable)[SKILL_WIND_DIVIDER][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE;
	(*g_pActionInfoTable)[SKILL_WIND_DIVIDER][2].EffectSpriteType	= EFFECTSPRITETYPE_WIND_DIVIDER_3;
	(*g_pActionInfoTable)[SKILL_WIND_DIVIDER][2].Step				= 20;
	(*g_pActionInfoTable)[SKILL_WIND_DIVIDER][2].Count			= FrameSize[EFFECTSPRITETYPE_WIND_DIVIDER_3];
	(*g_pActionInfoTable)[SKILL_WIND_DIVIDER][2].SetResultTime();
	(*g_pActionInfoTable)[SKILL_WIND_DIVIDER].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_WIND_DIVIDER );	// 맞는 결과를 표현한다.	

	// SKILL_WIND_DIVIDER
	(*g_pActionInfoTable)[RESULT_SKILL_WIND_DIVIDER].Set("RESULT_SKILL_WIND_DIVIDER", ACTION_DAMAGED, EFFECTSPRITETYPE_BLOOD_VERTICAL_1, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_WIND_DIVIDER].SetSoundID( SOUNDID_NULL );
	
	// SKILL_THUNDER_BOLT
	(*g_pActionInfoTable)[SKILL_THUNDER_BOLT].Set("SKILL_THUNDER_BOLT", ACTION_SLAYER_SWORD_2, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD_2]);
	(*g_pActionInfoTable)[SKILL_THUNDER_BOLT].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_THUNDER_BOLT].SetStartFrameAll( 5 );
	(*g_pActionInfoTable)[SKILL_THUNDER_BOLT].SetSoundID( SOUND_SLAYER_SWORD_THUNDERBOLTB );
	(*g_pActionInfoTable)[SKILL_THUNDER_BOLT].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_THUNDER_BOLT].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_THUNDER_BOLT][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;//EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_THUNDER_BOLT][0].EffectSpriteType	= EFFECTSPRITETYPE_LIGHTNING_1;
	(*g_pActionInfoTable)[SKILL_THUNDER_BOLT][0].Step				= 20;
	(*g_pActionInfoTable)[SKILL_THUNDER_BOLT][0].Count				= FrameSize[EFFECTSPRITETYPE_LIGHTNING_1];
	(*g_pActionInfoTable)[SKILL_THUNDER_BOLT][0].LinkCount			= 3;
	(*g_pActionInfoTable)[SKILL_THUNDER_BOLT][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;//EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_THUNDER_BOLT][1].EffectSpriteType	= EFFECTSPRITETYPE_LIGHTNING_2;
	(*g_pActionInfoTable)[SKILL_THUNDER_BOLT][1].Step				= 20;
	(*g_pActionInfoTable)[SKILL_THUNDER_BOLT][1].Count			= FrameSize[EFFECTSPRITETYPE_LIGHTNING_2];
	(*g_pActionInfoTable)[SKILL_THUNDER_BOLT][1].SetResultTime();
	(*g_pActionInfoTable)[SKILL_THUNDER_BOLT].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_THUNDER_BOLT );	// 맞는 결과를 표현한다.	

	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_BOLT].Set("RESULT_SKILL_THUNDER_BOLT", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_BOLT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_BOLT].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_BOLT].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_BOLT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_BOLT][0].EffectSpriteType	= EFFECTSPRITETYPE_LIGHTNING_3;
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_BOLT][0].Step				= 20;
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_BOLT][0].Count			= FrameSize[EFFECTSPRITETYPE_LIGHTNING_3];
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_BOLT][0].SetResultTime();

	// SKILL_WIDE_LIGHTNING
	(*g_pActionInfoTable)[SKILL_WIDE_LIGHTNING].Set("SKILL_WIDE_LIGHTNING", ACTION_SLAYER_SWORD_2, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD_2]);
	(*g_pActionInfoTable)[SKILL_WIDE_LIGHTNING].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_WIDE_LIGHTNING].SetStartFrameAll( 5 );
	(*g_pActionInfoTable)[SKILL_WIDE_LIGHTNING].SetSoundID( SOUND_SLAYER_SWORD_THS );
	(*g_pActionInfoTable)[SKILL_WIDE_LIGHTNING].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_WIDE_LIGHTNING].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_WIDE_LIGHTNING][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;//EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_WIDE_LIGHTNING][0].EffectSpriteType	= EFFECTSPRITETYPE_WIDE_LIGHTNING_LIGHT;
	(*g_pActionInfoTable)[SKILL_WIDE_LIGHTNING][0].Step				= 20;
	(*g_pActionInfoTable)[SKILL_WIDE_LIGHTNING][0].Count				= FrameSize[EFFECTSPRITETYPE_WIDE_LIGHTNING_LIGHT];
	(*g_pActionInfoTable)[SKILL_WIDE_LIGHTNING][0].LinkCount			= 6;
	(*g_pActionInfoTable)[SKILL_WIDE_LIGHTNING][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;//EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_WIDE_LIGHTNING][1].EffectSpriteType	= EFFECTSPRITETYPE_NULL;
	(*g_pActionInfoTable)[SKILL_WIDE_LIGHTNING][1].Step				= 20;
	(*g_pActionInfoTable)[SKILL_WIDE_LIGHTNING][1].Count				= 6;
	(*g_pActionInfoTable)[SKILL_WIDE_LIGHTNING][1].SetResultTime();
//	(*g_pActionInfoTable)[SKILL_WIDE_LIGHTNING].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, MAGIC_BLOODY_SNAKE );	// 맞는 결과를 표현한다.	

	(*g_pActionInfoTable)[RESULT_SKILL_WIDE_LIGHTNING].Set("RESULT_SKILL_WIDE_LIGHTNING", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_WIDE_LIGHTNING].SetSoundID( SOUND_ITEM_BOOM1 );
	(*g_pActionInfoTable)[RESULT_SKILL_WIDE_LIGHTNING].SetStartFrameAll( 11 );
	(*g_pActionInfoTable)[RESULT_SKILL_WIDE_LIGHTNING].Init( 2 );		
	(*g_pActionInfoTable)[RESULT_SKILL_WIDE_LIGHTNING][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_WIDE_LIGHTNING][0].EffectSpriteType	= EFFECTSPRITETYPE_WIDE_LIGHTNING_WAVE;
	(*g_pActionInfoTable)[RESULT_SKILL_WIDE_LIGHTNING][0].Step				= 20;
	(*g_pActionInfoTable)[RESULT_SKILL_WIDE_LIGHTNING][0].Count			= FrameSize[EFFECTSPRITETYPE_WIDE_LIGHTNING_WAVE];
	(*g_pActionInfoTable)[RESULT_SKILL_WIDE_LIGHTNING][0].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_WIDE_LIGHTNING][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_WIDE_LIGHTNING][1].EffectSpriteType	= EFFECTSPRITETYPE_WIDE_LIGHTNING_WAVE_2;
	(*g_pActionInfoTable)[RESULT_SKILL_WIDE_LIGHTNING][1].Step				= 20;
	(*g_pActionInfoTable)[RESULT_SKILL_WIDE_LIGHTNING][1].Count			= FrameSize[EFFECTSPRITETYPE_WIDE_LIGHTNING_WAVE_2];
	(*g_pActionInfoTable)[RESULT_SKILL_WIDE_LIGHTNING][1].SetResultTime();


	// SKILL_EXPANSION
	(*g_pActionInfoTable)[SKILL_EXPANSION].Set("SKILL_EXPANSION", ACTION_MAGIC, EFFECTSPRITETYPE_HPBOOST_CASTING, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_EXPANSION].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_EXPANSION].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_EXPANSION].SetSoundID( SOUND_SLAYER_SWORD_EXPANSION );

	(*g_pActionInfoTable)[RESULT_SKILL_EXPANSION].Set("RESULT_SKILL_EXPANSION", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_EXPANSION].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_EXPANSION].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_EXPANSION].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SKILL_EXPANSION][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_EXPANSION][0].EffectSpriteType	= EFFECTSPRITETYPE_HPBOOST_STAND_MALE;
	(*g_pActionInfoTable)[RESULT_SKILL_EXPANSION][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_EXPANSION][0].Count				= FrameSize[EFFECTSPRITETYPE_HPBOOST_STAND_MALE];
	(*g_pActionInfoTable)[RESULT_SKILL_EXPANSION][0].SetDelayNode();

	// SKILL_MIRACLE_SHIELD
	(*g_pActionInfoTable)[SKILL_MIRACLE_SHIELD].Set("SKILL_MIRACLE_SHIELD", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_MIRACLE_SHIELD].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_MIRACLE_SHIELD].Set("RESULT_SKILL_MIRACLE_SHIELD", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_MIRACLE_SHIELD].SetSoundID( SOUNDID_NULL );

	// SKILL_THUNDER_FLASH
	(*g_pActionInfoTable)[SKILL_THUNDER_FLASH].Set("SKILL_THUNDER_FLASH", ACTION_SLAYER_SWORD_2, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD]);
	(*g_pActionInfoTable)[SKILL_THUNDER_FLASH].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_THUNDER_FLASH].SetStartFrameAll( 5 );
	(*g_pActionInfoTable)[SKILL_THUNDER_FLASH].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_THUNDER_FLASH].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_THUNDER_FLASH].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_THUNDER_FLASH][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_THUNDER_FLASH][0].EffectSpriteType	= EFFECTSPRITETYPE_LIGHTNING_1;
	(*g_pActionInfoTable)[SKILL_THUNDER_FLASH][0].Step				= 20;
	(*g_pActionInfoTable)[SKILL_THUNDER_FLASH][0].Count				= FrameSize[EFFECTSPRITETYPE_LIGHTNING_1];
	(*g_pActionInfoTable)[SKILL_THUNDER_FLASH][0].LinkCount			= 3;
	(*g_pActionInfoTable)[SKILL_THUNDER_FLASH][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_THUNDER_FLASH][1].EffectSpriteType	= EFFECTSPRITETYPE_LIGHTNING_2;
	(*g_pActionInfoTable)[SKILL_THUNDER_FLASH][1].Step				= 20;
	(*g_pActionInfoTable)[SKILL_THUNDER_FLASH][1].Count			= FrameSize[EFFECTSPRITETYPE_LIGHTNING_2];
	(*g_pActionInfoTable)[SKILL_THUNDER_FLASH][1].SetResultTime();
	(*g_pActionInfoTable)[SKILL_THUNDER_FLASH].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_THUNDER_FLASH );	// 맞는 결과를 표현한다.	

	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_FLASH].Set("RESULT_SKILL_THUNDER_FLASH", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_FLASH].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_FLASH].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_FLASH].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_FLASH][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_FLASH][0].EffectSpriteType	= EFFECTSPRITETYPE_LIGHTNING_3;
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_FLASH][0].Step				= 20;
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_FLASH][0].Count			= FrameSize[EFFECTSPRITETYPE_LIGHTNING_3];
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_FLASH][0].SetResultTime();


	// SKILL_MASSACRE
	(*g_pActionInfoTable)[SKILL_MASSACRE].Set("SKILL_MASSACRE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_MASSACRE].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_MASSACRE].Set("RESULT_SKILL_MASSACRE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_MASSACRE].SetSoundID( SOUNDID_NULL );

	// SKILL_INVINCIBLE
	(*g_pActionInfoTable)[SKILL_INVINCIBLE].Set("SKILL_INVINCIBLE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_INVINCIBLE].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_INVINCIBLE].Set("RESULT_SKILL_INVINCIBLE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_INVINCIBLE].SetSoundID( SOUNDID_NULL );


	// SKILL_BERSERKER
	(*g_pActionInfoTable)[SKILL_BERSERKER].Set("SKILL_BERSERKER", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_BERSERKER].SetSoundID( SOUNDID_NULL );		

	(*g_pActionInfoTable)[RESULT_SKILL_BERSERKER].Set("RESULT_SKILL_BERSERKER", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_BERSERKER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_BERSERKER].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[RESULT_SKILL_BERSERKER].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_BERSERKER].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_BERSERKER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_BERSERKER][0].EffectSpriteType	= EFFECTSPRITETYPE_BERSERKER_1_STAND_MALE;
	(*g_pActionInfoTable)[RESULT_SKILL_BERSERKER][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_BERSERKER][0].Count				= FrameSize[EFFECTSPRITETYPE_BERSERKER_1_STAND_MALE];
	(*g_pActionInfoTable)[RESULT_SKILL_BERSERKER][0].SoundID				= SOUND_SLAYER_HEALING_R1;	
	(*g_pActionInfoTable)[RESULT_SKILL_BERSERKER][0].SetDelayNode();


	// SKILL_MOONLIGHT_SEVER
	(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER].Set("SKILL_MOONLIGHT_SEVER", ACTION_SLAYER_BLADE_2, EFFECTSPRITETYPE_TRIPLE_SLASHER, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD_2]);
	(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER].SetCastingEffectToOther();	// casting effect를 다른 사람에게 붙인다.
	(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER].SetActionStepCnt(2) ;
	// 이 SOUND_ITEM_FLYING_BOMB가 아니지만.. 들어있는데 wav가 어울린다. -_-;;
	(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER].SetSoundID( SOUND_ITEM_FLYING_BOMB );
	(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER].UseRepeatFrame();	
	(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER].SetStartFrame( 0, 9 );			// slow
	(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER].SetStartFrame( 1, 9 );			// normal
	(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER].SetStartFrame( 2, 9 );			// fast
	(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER].SetCastingStartFrame( 0, 9 );	// slow
	(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER].SetCastingStartFrame( 1, 9 );	// normal
	(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER].SetCastingStartFrame( 2, 9 );	// fast
	//(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER].SetCastingFrames( 0, 10 );		// slow
	//(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER].SetCastingFrames( 1, 10 );		// normal
	//(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER].SetCastingFrames( 2, 10 );		// fast
	(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER].SetRepeatFrame( 0, 9, 13 );		// slow
	(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER].SetRepeatFrame( 1, 9, 13 );		// normal
	(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER].SetRepeatFrame( 2, 9, 13 );		// fast
	(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER].SetRepeatLimit( 3 );
	(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER][0].EffectSpriteType		= EFFECTSPRITETYPE_TRIPLE_SLASHER;
	(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER][0].Count				= FrameSize[EFFECTSPRITETYPE_TRIPLE_SLASHER];
	(*g_pActionInfoTable)[SKILL_MOONLIGHT_SEVER][0].SetResultTime();

	(*g_pActionInfoTable)[RESULT_SKILL_MOONLIGHT_SEVER].Set("RESULT_SKILL_MOONLIGHT_SEVER", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_MOONLIGHT_SEVER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_MOONLIGHT_SEVER].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_MOONLIGHT_SEVER].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_SKILL_MOONLIGHT_SEVER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_MOONLIGHT_SEVER][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_MOONLIGHT_SEVER][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_MOONLIGHT_SEVER][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_SKILL_MOONLIGHT_SEVER][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_MOONLIGHT_SEVER][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_MOONLIGHT_SEVER][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_MOONLIGHT_SEVER][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];
	(*g_pActionInfoTable)[RESULT_SKILL_MOONLIGHT_SEVER][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_MOONLIGHT_SEVER][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_VERTICAL_1;
	(*g_pActionInfoTable)[RESULT_SKILL_MOONLIGHT_SEVER][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_MOONLIGHT_SEVER][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_VERTICAL_1];

	// SKILL_SHADOW_DANCING
	(*g_pActionInfoTable)[SKILL_SHADOW_DANCING].Set("SKILL_SHADOW_DANCING", ACTION_SLAYER_BLADE_2, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_BLADE_2_FAST]);
	(*g_pActionInfoTable)[SKILL_SHADOW_DANCING].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_SHADOW_DANCING].SetActionStepCnt(2) ;
	//(*g_pActionInfoTable)[SKILL_SHADOW_DANCING].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_SHADOW_DANCING].SetStartFrameAll( 7 );
	(*g_pActionInfoTable)[SKILL_SHADOW_DANCING].SetSoundID( SOUND_SLAYER_SWORD_WINDDIVIDER );

	(*g_pActionInfoTable)[RESULT_SKILL_SHADOW_DANCING].Set("RESULT_SKILL_SHADOW_DANCING", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_SHADOW_DANCING].SetSoundID( SOUNDID_NULL );

	// SKILL_TYPHOON
	(*g_pActionInfoTable)[SKILL_TYPHOON].Set("SKILL_TYPHOON", ACTION_SLAYER_BLADE_2, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_BLADE_2_FAST]);
	(*g_pActionInfoTable)[SKILL_TYPHOON].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_TYPHOON].SetActionStepCnt(2) ;
	(*g_pActionInfoTable)[SKILL_TYPHOON].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TYPHOON].SetStartFrameAll( 13 );	// 기술 effect가 시작되는 frame
	(*g_pActionInfoTable)[SKILL_TYPHOON].Init( 1 );
	(*g_pActionInfoTable)[SKILL_TYPHOON][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_TYPHOON][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_TYPHOON;		// TYPHOON_BACK
	(*g_pActionInfoTable)[SKILL_TYPHOON][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TYPHOON][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_TYPHOON]*2;
	(*g_pActionInfoTable)[SKILL_TYPHOON][0].SoundID				= SOUND_SLAYER_HEALING_R1;		
	(*g_pActionInfoTable)[SKILL_TYPHOON][0].SetResultTime();
	(*g_pActionInfoTable)[SKILL_TYPHOON].SetActionResult( ACTIONRESULTNODE_CREATURE_TURNING );		// 빙빙 돈다.

	(*g_pActionInfoTable)[RESULT_SKILL_TYPHOON].Set("RESULT_SKILL_TYPHOON", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_TYPHOON].SetSoundID( SOUNDID_NULL );

	// SKILL_PSYCHOKINESIS
	(*g_pActionInfoTable)[SKILL_PSYCHOKINESIS].Set("SKILL_PSYCHOKINESIS", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_PSYCHOKINESIS].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_PSYCHOKINESIS].Set("RESULT_SKILL_PSYCHOKINESIS", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_PSYCHOKINESIS].SetSoundID( SOUNDID_NULL );

	// SKILL_EXTERMINATION
	(*g_pActionInfoTable)[SKILL_EXTERMINATION].Set("SKILL_EXTERMINATION", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_EXTERMINATION].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_EXTERMINATION].Set("RESULT_SKILL_EXTERMINATION", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_EXTERMINATION].SetSoundID( SOUNDID_NULL );

	// SKILL_MIND_CONTROL
	(*g_pActionInfoTable)[SKILL_MIND_CONTROL].Set("SKILL_MIND_CONTROL", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_MIND_CONTROL].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_MIND_CONTROL].Set("RESULT_SKILL_MIND_CONTROL", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_MIND_CONTROL].SetSoundID( SOUNDID_NULL );

	// SKILL_REVOLVING
	(*g_pActionInfoTable)[SKILL_REVOLVING].Set("SKILL_REVOLVING", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_REVOLVING].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_REVOLVING].Set("RESULT_SKILL_REVOLVING", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_REVOLVING].SetSoundID( SOUNDID_NULL );

	// SKILL_FATALITY
	(*g_pActionInfoTable)[SKILL_FATALITY].Set("SKILL_FATALITY", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_FATALITY].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_FATALITY].Set("RESULT_SKILL_FATALITY", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_FATALITY].SetSoundID( SOUNDID_NULL );

	// SKILL_BLITZ
	(*g_pActionInfoTable)[SKILL_BLITZ].Set("SKILL_BLITZ", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_BLITZ].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_BLITZ].Set("RESULT_SKILL_BLITZ", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_BLITZ].SetSoundID( SOUNDID_NULL );

	// SKILL_PEACE (BLOODY_WAVE 임시로..)
	(*g_pActionInfoTable)[SKILL_PEACE].Set("SKILL_PEACE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_PEACE].SetUser(FLAG_ACTIONINFO_USER_MONSTER);
	(*g_pActionInfoTable)[SKILL_PEACE].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[SKILL_PEACE].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[SKILL_PEACE].SetStartFrameAll( 7 );	
	(*g_pActionInfoTable)[SKILL_PEACE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_PEACE );	// [새기술8]

	(*g_pActionInfoTable)[RESULT_SKILL_PEACE].Set("RESULT_SKILL_PEACE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_PEACE].SetSoundID(SOUND_SLAYER_PEACE) ; //SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_PEACE].Init( 2 );
	(*g_pActionInfoTable)[RESULT_SKILL_PEACE].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_PEACE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_PEACE][0].EffectSpriteType	= EFFECTSPRITETYPE_PEACE_BACK;
	(*g_pActionInfoTable)[RESULT_SKILL_PEACE][0].Step				= 20;
	(*g_pActionInfoTable)[RESULT_SKILL_PEACE][0].Count				= FrameSize[EFFECTSPRITETYPE_PEACE_BACK];
	(*g_pActionInfoTable)[RESULT_SKILL_PEACE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_PEACE][1].EffectSpriteType	= EFFECTSPRITETYPE_PEACE_UP;
	(*g_pActionInfoTable)[RESULT_SKILL_PEACE][1].Step				= 20;
	(*g_pActionInfoTable)[RESULT_SKILL_PEACE][1].Count				= FrameSize[EFFECTSPRITETYPE_PEACE_UP];
	(*g_pActionInfoTable)[RESULT_SKILL_PEACE][1].SetDelayNode();

	// SKILL_ENERGY_DROP
	(*g_pActionInfoTable)[SKILL_ENERGY_DROP].Set("SKILL_ENERGY_DROP", ACTION_MAGIC, EFFECTSPRITETYPE_AURA_BALL_1, 8, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET | FLAG_ACTIONINFO_START_SKY, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_ENERGY_DROP].SetSoundID(SOUND_SLAYER_ENERGY_DROP) ; // SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_ENERGY_DROP].SetStartFrameAll( 5 );
	(*g_pActionInfoTable)[SKILL_ENERGY_DROP].Init( 2 );
	(*g_pActionInfoTable)[SKILL_ENERGY_DROP][0].EffectGeneratorID	= EFFECTGENERATORID_MULTIPLE_FALLING;
	(*g_pActionInfoTable)[SKILL_ENERGY_DROP][0].EffectSpriteType	= EFFECTSPRITETYPE_AURA_BALL_2;
	(*g_pActionInfoTable)[SKILL_ENERGY_DROP][0].Step				= 30;
	(*g_pActionInfoTable)[SKILL_ENERGY_DROP][0].Count				= 17;//FrameSize[EFFECTSPRITETYPE_AURA_BALL_2];
	(*g_pActionInfoTable)[SKILL_ENERGY_DROP][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_ENERGY_DROP][1].EffectSpriteType	= EFFECTSPRITETYPE_AURA_BALL_3;
	(*g_pActionInfoTable)[SKILL_ENERGY_DROP][1].Step				= 15;
	(*g_pActionInfoTable)[SKILL_ENERGY_DROP][1].Count				= FrameSize[EFFECTSPRITETYPE_AURA_BALL_3];	
	(*g_pActionInfoTable)[SKILL_ENERGY_DROP][1].SoundID				= SOUND_SLAYER_ENCHANT_AURABALL2;
	(*g_pActionInfoTable)[SKILL_ENERGY_DROP].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_ENERGY_DROP );	// 맞는 결과를 표현한다.	
	(*g_pActionInfoTable)[SKILL_ENERGY_DROP].SetSkillFailDelay(); // 스킬실패해도 딜레이는 남아 있다..

	(*g_pActionInfoTable)[RESULT_SKILL_ENERGY_DROP].Set("RESULT_SKILL_ENERGY_DROP", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_ENERGY_DROP].SetSoundID( SOUNDID_NULL );

	// SKILL_SANCTUARY
	(*g_pActionInfoTable)[SKILL_SANCTUARY].Set("SKILL_SANCTUARY", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_SANCTUARY].SetSoundID( SOUNDID_NULL );	

	(*g_pActionInfoTable)[RESULT_SKILL_SANCTUARY].Set("RESULT_SKILL_SANCTUARY", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_SANCTUARY].SetSoundID( SOUND_SLAYER_SANCTUARY) ;//SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_SANCTUARY].Init( 3 );
	(*g_pActionInfoTable)[RESULT_SKILL_SANCTUARY].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_SANCTUARY][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_SANCTUARY][0].EffectSpriteType	= EFFECTSPRITETYPE_SANCTUARY_1;
	(*g_pActionInfoTable)[RESULT_SKILL_SANCTUARY][0].Step				= 30;
	(*g_pActionInfoTable)[RESULT_SKILL_SANCTUARY][0].Count				= FrameSize[EFFECTSPRITETYPE_SANCTUARY_1];
	(*g_pActionInfoTable)[RESULT_SKILL_SANCTUARY][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_SANCTUARY][1].EffectSpriteType	= EFFECTSPRITETYPE_SANCTUARY_2;
	(*g_pActionInfoTable)[RESULT_SKILL_SANCTUARY][1].Step				= 30;
	(*g_pActionInfoTable)[RESULT_SKILL_SANCTUARY][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_SKILL_SANCTUARY][1].Count				= FrameSize[EFFECTSPRITETYPE_SANCTUARY_2];
	(*g_pActionInfoTable)[RESULT_SKILL_SANCTUARY][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_SANCTUARY][2].EffectSpriteType	= EFFECTSPRITETYPE_SANCTUARY_3;
	(*g_pActionInfoTable)[RESULT_SKILL_SANCTUARY][2].Step				= 30;
	(*g_pActionInfoTable)[RESULT_SKILL_SANCTUARY][2].Count				= FrameSize[EFFECTSPRITETYPE_SANCTUARY_3];

	// SKILL_REFLECTION
	(*g_pActionInfoTable)[SKILL_REFLECTION].Set("SKILL_REFLECTION", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_REFLECTION].SetSoundID( SOUND_SLAYER_REFLECTION) ;// SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_REFLECTION].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_REFLECTION].SetEffectStatus( EFFECTSTATUS_REFLECTION );	// [새기술9]

	(*g_pActionInfoTable)[RESULT_SKILL_REFLECTION].Set("RESULT_SKILL_REFLECTION", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_REFLECTION].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_REFLECTION].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_REFLECTION][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_REFLECTION][0].EffectSpriteType	= EFFECTSPRITETYPE_REFLECTION_1;
	(*g_pActionInfoTable)[RESULT_SKILL_REFLECTION][0].Step				= 15;
	(*g_pActionInfoTable)[RESULT_SKILL_REFLECTION][0].Count				= FrameSize[EFFECTSPRITETYPE_REFLECTION_1];
	
	// REFLECT_REFLECTION,	// SKILL_REFLECTION 방어막
	(*g_pActionInfoTable)[REFLECT_REFLECTION].Set("REFLECT_REFLECTION", ACTION_STAND, EFFECTSPRITETYPE_REFLECTION_2, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[REFLECT_REFLECTION].SetCastingFramesAll( 5 );
	(*g_pActionInfoTable)[REFLECT_REFLECTION].SetSoundID( SOUND_SLAYER_ENCHANT_AURASHIELD2 );

	// SKILL_ARMAGEDDON
//	(*g_pActionInfoTable)[SKILL_ARMAGEDDON].Set("SKILL_ARMAGEDDON", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_MAGIC]);
//	(*g_pActionInfoTable)[SKILL_ARMAGEDDON].SetStartFrameAll( 10 );
//	(*g_pActionInfoTable)[SKILL_ARMAGEDDON].SetSoundID( SOUNDID_NULL );		
//	
//
//	(*g_pActionInfoTable)[RESULT_SKILL_ARMAGEDDON].Set("RESULT_SKILL_ARMAGEDDON", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
//	(*g_pActionInfoTable)[RESULT_SKILL_ARMAGEDDON].SetSoundID( SOUNDID_NULL );
//	(*g_pActionInfoTable)[RESULT_SKILL_ARMAGEDDON].Init( 2 );
//	(*g_pActionInfoTable)[RESULT_SKILL_ARMAGEDDON][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[RESULT_SKILL_ARMAGEDDON][0].EffectSpriteType	= EFFECTSPRITETYPE_ARMAGEDDON_START_BACK;
//	(*g_pActionInfoTable)[RESULT_SKILL_ARMAGEDDON][0].Step				= 15;
//	(*g_pActionInfoTable)[RESULT_SKILL_ARMAGEDDON][0].Count				= FrameSize[EFFECTSPRITETYPE_ARMAGEDDON_START_BACK];
//	(*g_pActionInfoTable)[RESULT_SKILL_ARMAGEDDON][0].SoundID			= SOUND_VAMPIRE_GREENSTALKER2;	
//	(*g_pActionInfoTable)[RESULT_SKILL_ARMAGEDDON][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[RESULT_SKILL_ARMAGEDDON][1].EffectSpriteType	= EFFECTSPRITETYPE_ARMAGEDDON_BACK_0_2;
//	(*g_pActionInfoTable)[RESULT_SKILL_ARMAGEDDON][1].Step				= 15;
//	(*g_pActionInfoTable)[RESULT_SKILL_ARMAGEDDON][1].Count				= FrameSize[EFFECTSPRITETYPE_ARMAGEDDON_BACK_0_2];
//	(*g_pActionInfoTable)[RESULT_SKILL_ARMAGEDDON][1].SoundID			= SOUND_VAMPIRE_GREENSTALKER2;



	// SKILL_EXORCISM
	(*g_pActionInfoTable)[SKILL_EXORCISM].Set("SKILL_EXORCISM", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_EXORCISM].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[SKILL_EXORCISM].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[SKILL_EXORCISM].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_EXORCISM].SetSoundID( SOUNDID_NULL );		

	(*g_pActionInfoTable)[RESULT_SKILL_EXORCISM].Set("RESULT_SKILL_EXORCISM", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_EXORCISM].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_EXORCISM].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[RESULT_SKILL_EXORCISM].Init( 2 );		
	(*g_pActionInfoTable)[RESULT_SKILL_EXORCISM][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_EXORCISM][0].EffectSpriteType	= EFFECTSPRITETYPE_EXORCISM_GROUND;
	(*g_pActionInfoTable)[RESULT_SKILL_EXORCISM][0].Step				= 30;
	(*g_pActionInfoTable)[RESULT_SKILL_EXORCISM][0].Count				= FrameSize[EFFECTSPRITETYPE_EXORCISM_GROUND];
	(*g_pActionInfoTable)[RESULT_SKILL_EXORCISM][0].LinkCount			= 7;
	(*g_pActionInfoTable)[RESULT_SKILL_EXORCISM][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_EXORCISM][1].EffectSpriteType	= EFFECTSPRITETYPE_EXORCISM_BACK;
	(*g_pActionInfoTable)[RESULT_SKILL_EXORCISM][1].Step				= 30;
	(*g_pActionInfoTable)[RESULT_SKILL_EXORCISM][1].Count				= FrameSize[EFFECTSPRITETYPE_EXORCISM_BACK];

	// SKILL_SUMMON_BAT
//	(*g_pActionInfoTable)[SKILL_SUMMON_BAT].Set("SKILL_SUMMON_BAT", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
//	(*g_pActionInfoTable)[SKILL_SUMMON_BAT].SetSoundID( SOUNDID_NULL);
//	(*g_pActionInfoTable)[SKILL_SUMMON_BAT].SetStartFrameAll( 10 );
//
//	(*g_pActionInfoTable)[RESULT_SKILL_SUMMON_BAT].Set("RESULT_SKILL_SUMMON_BAT", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
//	(*g_pActionInfoTable)[RESULT_SKILL_SUMMON_BAT].SetSoundID( SOUNDID_NULL);
//	(*g_pActionInfoTable)[RESULT_SKILL_SUMMON_BAT].Init( 2 );		
//	(*g_pActionInfoTable)[RESULT_SKILL_SUMMON_BAT].SetMainNode( 1 );
//	(*g_pActionInfoTable)[RESULT_SKILL_SUMMON_BAT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[RESULT_SKILL_SUMMON_BAT][0].EffectSpriteType		= EFFECTSPRITETYPE_SUMMON_BAT_1;
//	(*g_pActionInfoTable)[RESULT_SKILL_SUMMON_BAT][0].Step					= 30;
//	(*g_pActionInfoTable)[RESULT_SKILL_SUMMON_BAT][0].Count				= FrameSize[EFFECTSPRITETYPE_SUMMON_BAT_1];
//	(*g_pActionInfoTable)[RESULT_SKILL_SUMMON_BAT][0].SetDelayNode();
//	(*g_pActionInfoTable)[RESULT_SKILL_SUMMON_BAT][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[RESULT_SKILL_SUMMON_BAT][1].EffectSpriteType		= EFFECTSPRITETYPE_SUMMON_BAT_2;
//	(*g_pActionInfoTable)[RESULT_SKILL_SUMMON_BAT][1].Step					= 30;
//	(*g_pActionInfoTable)[RESULT_SKILL_SUMMON_BAT][1].Count				= FrameSize[EFFECTSPRITETYPE_SUMMON_BAT_2];

	// SKILL_CHARM
	(*g_pActionInfoTable)[SKILL_CHARM].Set("SKILL_CHARM", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_CHARM].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_CHARM].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[SKILL_CHARM].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CHARM][0].EffectGeneratorID		= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CHARM][0].EffectSpriteType		= EFFECTSPRITETYPE_CHARM_1;
	(*g_pActionInfoTable)[SKILL_CHARM][0].Step					= 30;
	(*g_pActionInfoTable)[SKILL_CHARM][0].Count					= FrameSize[EFFECTSPRITETYPE_CHARM_1];
	(*g_pActionInfoTable)[SKILL_CHARM][0].SetResultTime();

	(*g_pActionInfoTable)[RESULT_SKILL_CHARM].Set("RESULT_SKILL_CHARM", ACTION_DRAINED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_CHARM].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_SKILL_CHARM].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SKILL_CHARM][0].EffectGeneratorID		= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_CHARM][0].EffectSpriteType		= EFFECTSPRITETYPE_CHARM_2;
	(*g_pActionInfoTable)[RESULT_SKILL_CHARM][0].Step					= 30;
	(*g_pActionInfoTable)[RESULT_SKILL_CHARM][0].Count					= FrameSize[EFFECTSPRITETYPE_CHARM_2];
	(*g_pActionInfoTable)[RESULT_SKILL_CHARM][0].SetDelayNode();

	// SKILL_POLYMORPH
	(*g_pActionInfoTable)[SKILL_POLYMORPH].Set("SKILL_POLYMORPH", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);	
	(*g_pActionInfoTable)[SKILL_POLYMORPH].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[SKILL_POLYMORPH].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_POLYMORPH].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_POLYMORPH][0].EffectGeneratorID		= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_POLYMORPH][0].EffectSpriteType		= EFFECTSPRITETYPE_POLYMORPH_BACK;
	(*g_pActionInfoTable)[SKILL_POLYMORPH][0].Step					= 30;
	(*g_pActionInfoTable)[SKILL_POLYMORPH][0].Count					= FrameSize[EFFECTSPRITETYPE_POLYMORPH_BACK];
	(*g_pActionInfoTable)[SKILL_POLYMORPH][0].SetResultTime();

	(*g_pActionInfoTable)[RESULT_SKILL_POLYMORPH].Set("RESULT_SKILL_POLYMORPH", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_POLYMORPH].SetSoundID( SOUNDID_NULL);


	// SKILL_HYPNOSIS
//	(*g_pActionInfoTable)[SKILL_HYPNOSIS].Set("SKILL_HYPNOSIS", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
//	(*g_pActionInfoTable)[SKILL_HYPNOSIS].SetSoundID( SOUNDID_NULL);
//	(*g_pActionInfoTable)[SKILL_HYPNOSIS].SetStartFrameAll( 10 );
//	(*g_pActionInfoTable)[SKILL_HYPNOSIS].Init( 1 );		
//	(*g_pActionInfoTable)[SKILL_HYPNOSIS][0].EffectGeneratorID		= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[SKILL_HYPNOSIS][0].EffectSpriteType		= EFFECTSPRITETYPE_HYPNOSIS_START_MALE;
//	(*g_pActionInfoTable)[SKILL_HYPNOSIS][0].Step					= 30;
//	(*g_pActionInfoTable)[SKILL_HYPNOSIS][0].Count					= FrameSize[EFFECTSPRITETYPE_HYPNOSIS_START_MALE];
//	(*g_pActionInfoTable)[SKILL_HYPNOSIS][0].SetResultTime();

//	(*g_pActionInfoTable)[RESULT_SKILL_HYPNOSIS].Set("RESULT_SKILL_HYPNOSIS", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
//	(*g_pActionInfoTable)[RESULT_SKILL_HYPNOSIS].SetSoundID( SOUNDID_NULL);
//	(*g_pActionInfoTable)[RESULT_SKILL_HYPNOSIS].SetStartFrameAll( 10 );
//	(*g_pActionInfoTable)[RESULT_SKILL_HYPNOSIS].Init( 1 );		
//	(*g_pActionInfoTable)[RESULT_SKILL_HYPNOSIS][0].EffectGeneratorID		= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[RESULT_SKILL_HYPNOSIS][0].EffectSpriteType		= EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE;
//	(*g_pActionInfoTable)[RESULT_SKILL_HYPNOSIS][0].Step					= 30;
//	(*g_pActionInfoTable)[RESULT_SKILL_HYPNOSIS][0].Count					= FrameSize[EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE];
//	(*g_pActionInfoTable)[RESULT_SKILL_HYPNOSIS][0].SetDelayNode();




//	// ARMAGEDDON_CRASH_1
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_1].Set("ARMAGEDDON_CRASH_1", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_1].SetStartWithCasting();
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_1].Init( 1 );		
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_1][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_1][0].EffectSpriteType	= EFFECTSPRITETYPE_ARMAGEDDON_BACK_1_1;
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_1][0].Step				= 25;
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_1][0].Count				= FrameSize[EFFECTSPRITETYPE_ARMAGEDDON_BACK_1_1];
//	
//	// ARMAGEDDON_CRASH_2
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_2].Set("ARMAGEDDON_CRASH_2", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_2].SetStartWithCasting();
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_2].Init( 1 );		
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_2][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_2][0].EffectSpriteType	= EFFECTSPRITETYPE_ARMAGEDDON_BACK_2_1;
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_2][0].Step				= 25;
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_2][0].Count				= FrameSize[EFFECTSPRITETYPE_ARMAGEDDON_BACK_2_1];
//	
//	// ARMAGEDDON_CRASH_3
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_3].Set("ARMAGEDDON_CRASH_3", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_3].SetStartWithCasting();
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_3].Init( 1 );		
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_3][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_3][0].EffectSpriteType	= EFFECTSPRITETYPE_ARMAGEDDON_BACK_3_1;
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_3][0].Step				= 25;
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_3][0].Count				= FrameSize[EFFECTSPRITETYPE_ARMAGEDDON_BACK_3_1];
//	
//	// ARMAGEDDON_CRASH_4
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_4].Set("ARMAGEDDON_CRASH_4", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_4].SetStartWithCasting();
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_4].Init( 1 );		
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_4][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_4][0].EffectSpriteType	= EFFECTSPRITETYPE_ARMAGEDDON_BACK_4_1;
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_4][0].Step				= 25;
//	(*g_pActionInfoTable)[ARMAGEDDON_CRASH_4][0].Count				= FrameSize[EFFECTSPRITETYPE_ARMAGEDDON_BACK_4_1];	
	

	// SKILL_THROW_BOMB
//	(*g_pActionInfoTable)[SKILL_THROW_BOMB].Set("SKILL_THROW_BOMB", ACTION_SLAYER_THROW_WEAPON, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_THROW_POTION]);
	(*g_pActionInfoTable)[SKILL_THROW_BOMB].Set("SKILL_THROW_BOMB", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_THROW_BOMB].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BOMB ); // item을 사용하는 기술이다.
	(*g_pActionInfoTable)[SKILL_THROW_BOMB].SetPacketType( ACTIONINFO_PACKET_OTHER );
	(*g_pActionInfoTable)[SKILL_THROW_BOMB].SetStartFrameAll( 14 );		// 날아가기 시작하는 frame
	(*g_pActionInfoTable)[SKILL_THROW_BOMB].SetSoundID( SOUND_ITEM_FLYING_BOMB );
	(*g_pActionInfoTable)[SKILL_THROW_BOMB].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_THROW_BOMB][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE_BOMB;
	(*g_pActionInfoTable)[SKILL_THROW_BOMB][0].EffectSpriteType	= EFFECTSPRITETYPE_FLYING_BOMB;
	(*g_pActionInfoTable)[SKILL_THROW_BOMB][0].Step				= 30;
	(*g_pActionInfoTable)[SKILL_THROW_BOMB][0].Count				= 32;//NormalEFPK[(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_FLYING_BOMB].FrameID-MAX_EFFECTSPRITETYPE_ALPHAEFFECT][DIRECTION_DOWN].GetSize();

	// SKILL_THROW_BOMB
	(*g_pActionInfoTable)[RESULT_SKILL_THROW_BOMB].Set("RESULT_SKILL_THROW_BOMB", ACTION_DAMAGED, EFFECTSPRITETYPE_BLOOD, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_THROW_BOMB].SetSoundID( SOUNDID_NULL );	
	
	// SKILL_CURE_EFFECT,	// Cure Critical Wounds
	(*g_pActionInfoTable)[SKILL_CURE_EFFECT].Set("SKILL_CURE_EFFECT", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[SKILL_CURE_EFFECT].SetSoundID( SOUNDID_NULL );//SOUND_SLAYER_HEALING_CCW );
	//(*g_pActionInfoTable)[SKILL_CURE_EFFECT].SetStartWithCasting();
	//(*g_pActionInfoTable)[SKILL_CURE_EFFECT].SetCastingFramesAll( FrameSize[EFFECTSPRITETYPE_CURE_2_2] );	

	// SKILL_CURE_EFFECT,	// Cure Critical Wounds
	(*g_pActionInfoTable)[RESULT_SKILL_CURE_EFFECT].Set("RESULT_SKILL_CURE_EFFECT", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_CURE_EFFECT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_CURE_EFFECT].SetStartWithCasting();
	//(*g_pActionInfoTable)[RESULT_SKILL_CURE_EFFECT].SetCastingFramesAll( FrameSize[EFFECTSPRITETYPE_CURE_2_2] );
	//(*g_pActionInfoTable)[RESULT_SKILL_CURE_EFFECT].SetMainNode( 1 );	
	(*g_pActionInfoTable)[RESULT_SKILL_CURE_EFFECT].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_CURE_EFFECT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_CURE_EFFECT][0].EffectSpriteType	= EFFECTSPRITETYPE_CURE_ALL_2;
	(*g_pActionInfoTable)[RESULT_SKILL_CURE_EFFECT][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_CURE_EFFECT][0].Count				= FrameSize[EFFECTSPRITETYPE_CURE_ALL_2];
	(*g_pActionInfoTable)[RESULT_SKILL_CURE_EFFECT][0].SoundID				= SOUND_SLAYER_HEALING_CCW;
	/*
	(*g_pActionInfoTable)[RESULT_SKILL_CURE_EFFECT][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_CURE_EFFECT][1].EffectSpriteType	= EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_2;
	(*g_pActionInfoTable)[RESULT_SKILL_CURE_EFFECT][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_CURE_EFFECT][1].Count				= FrameSize[EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_2];
	(*g_pActionInfoTable)[RESULT_SKILL_CURE_EFFECT][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_SKILL_CURE_EFFECT][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_CURE_EFFECT][2].EffectSpriteType	= EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_3;
	(*g_pActionInfoTable)[RESULT_SKILL_CURE_EFFECT][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_CURE_EFFECT][2].Count				= FrameSize[EFFECTSPRITETYPE_CURE_CRITICAL_WOUND_3];
	*/

	// SKILL_CRITICAL_GROUND :기술을 쓰는 경우
	(*g_pActionInfoTable)[SKILL_CRITICAL_GROUND].Set("SKILL_CRITICAL_GROUND", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_CRITICAL_GROUND].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CRITICAL_GROUND].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_CRITICAL_GROUND].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CRITICAL_GROUND][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_CRITICAL_GROUND][0].EffectSpriteType	= EFFECTSPRITETYPE_CRITICAL;
	(*g_pActionInfoTable)[SKILL_CRITICAL_GROUND][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CRITICAL_GROUND][0].Count			= FrameSize[EFFECTSPRITETYPE_CRITICAL];	
	(*g_pActionInfoTable)[SKILL_CRITICAL_GROUND].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_CRITICAL_GROUND );	// 맞는 결과를 표현한다.	
	
	// SKILL_CRITICAL_GROUND
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_GROUND].Set("RESULT_SKILL_CRITICAL_GROUND", ACTION_DAMAGED, EFFECTSPRITETYPE_BLOOD, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_GROUND].SetSoundID( SOUNDID_NULL );	
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_GROUND].Init( 3 );
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_GROUND][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_GROUND][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_GROUND_1_1;
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_GROUND][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_GROUND][0].Count				= 5*16;	//FrameSize[EFFECTSPRITETYPE_BLOOD_GROUND_1_1];
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_GROUND][0].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_GROUND][0].LinkCount		= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_GROUND][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_GROUND][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_GROUND_1_1;
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_GROUND][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_GROUND][1].Count				= 5*16;	//FrameSize[EFFECTSPRITETYPE_BLOOD_GROUND_1_1];
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_GROUND][1].LinkCount		= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_GROUND][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_GROUND][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_GROUND][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_GROUND_1_1;
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_GROUND][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_GROUND][2].Count				= 5*16;	//FrameSize[EFFECTSPRITETYPE_BLOOD_GROUND_1_1];
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_GROUND][2].SetDelayNode();
	

	// SKILL_CRITICAL_EFFECT : 그냥 땅에 생길때
	(*g_pActionInfoTable)[SKILL_CRITICAL_EFFECT].Set("SKILL_CRITICAL_EFFECT", ACTION_STAND, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_CRITICAL_EFFECT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CRITICAL_EFFECT].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_CRITICAL_EFFECT].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CRITICAL_EFFECT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_CRITICAL_EFFECT][0].EffectSpriteType	= EFFECTSPRITETYPE_CRITICAL;
	(*g_pActionInfoTable)[SKILL_CRITICAL_EFFECT][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CRITICAL_EFFECT][0].Count			= FrameSize[EFFECTSPRITETYPE_CRITICAL];		

	// SKILL_CRITICAL_EFFECT : 그냥 땅에 생길때
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_EFFECT].Set("RESULT_SKILL_CRITICAL_EFFECT", ACTION_STAND, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_EFFECT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_EFFECT].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_EFFECT].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_EFFECT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_EFFECT][0].EffectSpriteType	= EFFECTSPRITETYPE_CRITICAL;
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_EFFECT][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_CRITICAL_EFFECT][0].Count			= FrameSize[EFFECTSPRITETYPE_CRITICAL];		


	// SKILL_VIGOR_DROP
	(*g_pActionInfoTable)[SKILL_VIGOR_DROP].Set("SKILL_VIGOR_DROP", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET | FLAG_ACTIONINFO_START_SKY, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_VIGOR_DROP].SetCastingActionInfo( CASTING_HEALING );
	(*g_pActionInfoTable)[SKILL_VIGOR_DROP].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[SKILL_VIGOR_DROP].SetStartFrameAll( 5 );	
	(*g_pActionInfoTable)[SKILL_VIGOR_DROP].SetSoundID( SOUND_SLAYER_HEAL_ACTIVATION );
	(*g_pActionInfoTable)[SKILL_VIGOR_DROP].Init( 2 );
	(*g_pActionInfoTable)[SKILL_VIGOR_DROP][0].EffectGeneratorID	= EFFECTGENERATORID_MULTIPLE_FALLING;
	(*g_pActionInfoTable)[SKILL_VIGOR_DROP][0].EffectSpriteType	= EFFECTSPRITETYPE_VISIBLE_1;
	(*g_pActionInfoTable)[SKILL_VIGOR_DROP][0].Step				= 30;
	(*g_pActionInfoTable)[SKILL_VIGOR_DROP][0].Count				= 17;//FrameSize[EFFECTSPRITETYPE_AURA_BALL_2];
	(*g_pActionInfoTable)[SKILL_VIGOR_DROP][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_VIGOR_DROP][1].EffectSpriteType	= EFFECTSPRITETYPE_VISIBLE_4;
	(*g_pActionInfoTable)[SKILL_VIGOR_DROP][1].Step				= 15;
	(*g_pActionInfoTable)[SKILL_VIGOR_DROP][1].Count				= FrameSize[EFFECTSPRITETYPE_VISIBLE_4];	
	(*g_pActionInfoTable)[SKILL_VIGOR_DROP].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_VIGOR_DROP );	// 맞는 결과를 표현한다.	
	(*g_pActionInfoTable)[SKILL_VIGOR_DROP].SetSkillFailDelay(); // 스킬실패해도 딜레이는 남아 있다..

	(*g_pActionInfoTable)[RESULT_SKILL_VIGOR_DROP].Set("RESULT_SKILL_VIGOR_DROP", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_VIGOR_DROP].SetSoundID( SOUNDID_NULL );

	// [새기술]
	// SKILL_SWORD_MASTERY
	(*g_pActionInfoTable)[SKILL_SWORD_MASTERY].Set("SKILL_SWORD_MASTERY", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_SWORD_MASTERY].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_SWORD_MASTERY].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_MASTERY].Set("RESULT_SKILL_SWORD_MASTERY", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_MASTERY].SetSoundID( SOUNDID_NULL );

	// SKILL_SHIELD_MASTERY
    (*g_pActionInfoTable)[SKILL_SHIELD_MASTERY].Set("SKILL_SHIELD_MASTERY", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_SHIELD_MASTERY].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SHIELD );
	(*g_pActionInfoTable)[SKILL_SHIELD_MASTERY].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_SHIELD_MASTERY].Set("RESULT_SKILL_SHIELD_MASTERY", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[RESULT_SKILL_SHIELD_MASTERY].SetSoundID( SOUNDID_NULL );

	// SKILL_THUNDER_STORM
    (*g_pActionInfoTable)[SKILL_THUNDER_STORM].Set("SKILL_THUNDER_STORM", ACTION_SLAYER_SWORD_2, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD_2]);
	(*g_pActionInfoTable)[SKILL_THUNDER_STORM].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_THUNDER_STORM].SetStartFrameAll( 5 );
	(*g_pActionInfoTable)[SKILL_THUNDER_STORM].SetSoundID( SOUND_SLAYER_SWORD_THUNDERBOLTA );
	(*g_pActionInfoTable)[SKILL_THUNDER_STORM].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_THUNDER_STORM].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_THUNDER_STORM][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_CROSS;//EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_THUNDER_STORM][0].EffectSpriteType	= EFFECTSPRITETYPE_LIGHTNING_1;
	(*g_pActionInfoTable)[SKILL_THUNDER_STORM][0].Step				= 20;
	(*g_pActionInfoTable)[SKILL_THUNDER_STORM][0].Count				= FrameSize[EFFECTSPRITETYPE_LIGHTNING_1];
	(*g_pActionInfoTable)[SKILL_THUNDER_STORM][0].LinkCount			= 3;
	(*g_pActionInfoTable)[SKILL_THUNDER_STORM][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;//EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_THUNDER_STORM][1].EffectSpriteType	= EFFECTSPRITETYPE_LIGHTNING_2;
	(*g_pActionInfoTable)[SKILL_THUNDER_STORM][1].Step				= 20;
	(*g_pActionInfoTable)[SKILL_THUNDER_STORM][1].Count			= FrameSize[EFFECTSPRITETYPE_LIGHTNING_2];
	(*g_pActionInfoTable)[SKILL_THUNDER_STORM][1].SetResultTime();
	(*g_pActionInfoTable)[SKILL_THUNDER_STORM].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_THUNDER_STORM );	// 맞는 결과를 표현한다.	

	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_STORM].Set("RESULT_SKILL_THUNDER_STORM", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_STORM].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_STORM].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_STORM].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_STORM][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_STORM][0].EffectSpriteType	= EFFECTSPRITETYPE_LIGHTNING_3;
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_STORM][0].Step				= 20;
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_STORM][0].Count			= FrameSize[EFFECTSPRITETYPE_LIGHTNING_3];
	(*g_pActionInfoTable)[RESULT_SKILL_THUNDER_STORM][0].SetResultTime();

	// SKILL_CONCENTRATION
    (*g_pActionInfoTable)[SKILL_CONCENTRATION].Set("SKILL_CONCENTRATION", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_CONCENTRATION].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_CONCENTRATION].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_CONCENTRATION].Set("RESULT_SKILL_CONCENTRATION", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[RESULT_SKILL_CONCENTRATION].SetSoundID( SOUNDID_NULL );

	// SKILL_EVASION
    (*g_pActionInfoTable)[SKILL_EVASION].Set("SKILL_EVASION", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_EVASION].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_EVASION].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_EVASION].Set("RESULT_SKILL_EVASION", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[RESULT_SKILL_EVASION].SetSoundID( SOUNDID_NULL );

	// SKILL_HOLY_BLAST
    (*g_pActionInfoTable)[SKILL_HOLY_BLAST].Set("SKILL_HOLY_BLAST", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_HOLY_BLAST].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[SKILL_HOLY_BLAST].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[SKILL_HOLY_BLAST].SetStartFrameAll( 7 );
	(*g_pActionInfoTable)[SKILL_HOLY_BLAST].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_HOLY_BLAST].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_HOLY_BLAST][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_HOLY_BLAST][0].EffectSpriteType	= EFFECTSPRITETYPE_VISIBLE_1;
	(*g_pActionInfoTable)[SKILL_HOLY_BLAST][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_HOLY_BLAST][0].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_HOLY_BLAST][0].Count				= FrameSize[EFFECTSPRITETYPE_VISIBLE_1];
	(*g_pActionInfoTable)[SKILL_HOLY_BLAST][0].SoundID				= SOUND_SLAYER_ENCHANT_AURABALL1;	
	(*g_pActionInfoTable)[SKILL_HOLY_BLAST].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_HOLY_BLAST );	// 맞는 결과를 표현한다.	

	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_BLAST].Set("RESULT_SKILL_HOLY_BLAST", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_BLAST].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_BLAST].Init( 2 );
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_BLAST][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_BLAST][0].EffectSpriteType	= EFFECTSPRITETYPE_VISIBLE_2;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_BLAST][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_BLAST][0].Count				= 2*16;//FrameSize[EFFECTSPRITETYPE_VISIBLE_2];
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_BLAST][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_BLAST][1].EffectSpriteType	= EFFECTSPRITETYPE_VISIBLE_5;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_BLAST][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_BLAST][1].Count			= FrameSize[EFFECTSPRITETYPE_VISIBLE_5];

	// SKILL_HYMN
    (*g_pActionInfoTable)[SKILL_HYMN].Set("SKILL_HYMN", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_HYMN].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_HYMN].Set("RESULT_SKILL_HYMN", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_HYMN].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_HYMN].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_HYMN].Init( 3 );
	(*g_pActionInfoTable)[RESULT_SKILL_HYMN].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_HYMN][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_HYMN][0].EffectSpriteType	= EFFECTSPRITETYPE_CURSE_1;
	(*g_pActionInfoTable)[RESULT_SKILL_HYMN][0].Step				= 12;
	(*g_pActionInfoTable)[RESULT_SKILL_HYMN][0].Count				= FrameSize[EFFECTSPRITETYPE_CURSE_1];
	(*g_pActionInfoTable)[RESULT_SKILL_HYMN][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_HYMN][1].EffectSpriteType	= EFFECTSPRITETYPE_CURSE_2;
	(*g_pActionInfoTable)[RESULT_SKILL_HYMN][1].Step				= 10;
	(*g_pActionInfoTable)[RESULT_SKILL_HYMN][1].Count				= 2 * FrameSize[EFFECTSPRITETYPE_CURSE_2];
	(*g_pActionInfoTable)[RESULT_SKILL_HYMN][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_SKILL_HYMN][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_HYMN][2].EffectSpriteType	= EFFECTSPRITETYPE_CURSE_3;
	(*g_pActionInfoTable)[RESULT_SKILL_HYMN][2].Step				= 6;
	(*g_pActionInfoTable)[RESULT_SKILL_HYMN][2].Count				= FrameSize[EFFECTSPRITETYPE_CURSE_3];


	// SKILL_ACTIVATION,			// Regeneration
	(*g_pActionInfoTable)[SKILL_ACTIVATION].Set("SKILL_ACTIVATION", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_ACTIVATION].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[SKILL_ACTIVATION].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[SKILL_ACTIVATION].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[SKILL_ACTIVATION].SetStartFrameAll( 7 );
	(*g_pActionInfoTable)[SKILL_ACTIVATION].SetSoundID( SOUNDID_NULL );		
	(*g_pActionInfoTable)[SKILL_ACTIVATION].SetEffectStatus( EFFECTSTATUS_ACTIVATION );	// [새기술8]

	// SKILL_ACTIVATION,			// Regeneration
	(*g_pActionInfoTable)[RESULT_SKILL_ACTIVATION].Set("RESULT_SKILL_ACTIVATION", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_ACTIVATION].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_ACTIVATION].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_ACTIVATION].Init( 1 );
 	(*g_pActionInfoTable)[RESULT_SKILL_ACTIVATION][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
 	(*g_pActionInfoTable)[RESULT_SKILL_ACTIVATION][0].EffectSpriteType	= EFFECTSPRITETYPE_REGENERATION_1_STAND_MALE;
 	(*g_pActionInfoTable)[RESULT_SKILL_ACTIVATION][0].Step				= 25;
 	(*g_pActionInfoTable)[RESULT_SKILL_ACTIVATION][0].Count				= FrameSize[EFFECTSPRITETYPE_REGENERATION_1_STAND_MALE];
 	(*g_pActionInfoTable)[RESULT_SKILL_ACTIVATION][0].SoundID				= SOUND_SLAYER_HEALING_R1;	
 	(*g_pActionInfoTable)[RESULT_SKILL_ACTIVATION][0].SetDelayNode();



//	// SKILL_ACTIVATION
//	(*g_pActionInfoTable)[SKILL_ACTIVATION].Set("SKILL_ACTIVATION", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
//	(*g_pActionInfoTable)[SKILL_ACTIVATION].SetSoundID( SOUNDID_NULL );
//	
//	(*g_pActionInfoTable)[RESULT_SKILL_ACTIVATION].Set("RESULT_SKILL_ACTIVATION", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
//	(*g_pActionInfoTable)[RESULT_SKILL_ACTIVATION].SetSoundID( SOUNDID_NULL );


	// [새기술2]
	// SKILL_MENTAL_SWORD,
	(*g_pActionInfoTable)[SKILL_MENTAL_SWORD].Set("SKILL_MENTAL_SWORD", ACTION_SLAYER_SWORD_2, EFFECTSPRITETYPE_NULL, 6, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_SWORD]);
	(*g_pActionInfoTable)[SKILL_MENTAL_SWORD].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_MENTAL_SWORD].SetStartFrame( 0, 10 );
	(*g_pActionInfoTable)[SKILL_MENTAL_SWORD].SetStartFrame( 1, 8 );
	(*g_pActionInfoTable)[SKILL_MENTAL_SWORD].SetStartFrame( 2, 6 );
	(*g_pActionInfoTable)[SKILL_MENTAL_SWORD].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_MENTAL_SWORD].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_MENTAL_SWORD].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_MENTAL_SWORD][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[SKILL_MENTAL_SWORD][0].EffectSpriteType	= EFFECTSPRITETYPE_MENTALSWORD_THUNDER;
	(*g_pActionInfoTable)[SKILL_MENTAL_SWORD][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_MENTAL_SWORD][0].Count				= 32;//FrameSize[EFFECTSPRITETYPE_ACID_BOLT_1];
	(*g_pActionInfoTable)[SKILL_MENTAL_SWORD][0].SoundID			= SOUND_SLAYER_SWORD_MENTAL_SWORD;//SOUND_SLAYER_SWORD_DI;	

	// SKILL_MENTAL_SWORD
	(*g_pActionInfoTable)[RESULT_SKILL_MENTAL_SWORD].Set("RESULT_SKILL_MENTAL_SWORD", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 100);	
	(*g_pActionInfoTable)[RESULT_SKILL_MENTAL_SWORD].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_MENTAL_SWORD].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_MENTAL_SWORD].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SKILL_MENTAL_SWORD][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_MENTAL_SWORD][0].EffectSpriteType	= EFFECTSPRITETYPE_MENTALSWORD_DAMAGE;
	(*g_pActionInfoTable)[RESULT_SKILL_MENTAL_SWORD][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_MENTAL_SWORD][0].Count				= FrameSize[EFFECTSPRITETYPE_MENTALSWORD_DAMAGE];
	
	// SKILL_OBSERVING_EYE,				// Bless
	(*g_pActionInfoTable)[SKILL_OBSERVING_EYE].Set("SKILL_OBSERVING_EYE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_OBSERVING_EYE].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_OBSERVING_EYE].SetEffectStatus( EFFECTSTATUS_OBSERVING_EYE );
	(*g_pActionInfoTable)[SKILL_OBSERVING_EYE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_OBSERVING_EYE].Init( 1 );
	(*g_pActionInfoTable)[SKILL_OBSERVING_EYE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_OBSERVING_EYE][0].EffectSpriteType	= EFFECTSPRITETYPE_OBSERVINGEYE_RADER;
	(*g_pActionInfoTable)[SKILL_OBSERVING_EYE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_OBSERVING_EYE][0].Count				= FrameSize[EFFECTSPRITETYPE_OBSERVINGEYE_RADER];
	(*g_pActionInfoTable)[SKILL_OBSERVING_EYE][0].SoundID			= SOUND_SLAYER_ENCHANT_B1;
	
	
	// SKILL_OBSERVING_EYE,				// Bless
	(*g_pActionInfoTable)[RESULT_SKILL_OBSERVING_EYE].Set("RESULT_SKILL_OBSERVING_EYE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_OBSERVING_EYE].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_OBSERVING_EYE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_OBSERVING_EYE].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_OBSERVING_EYE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_OBSERVING_EYE][0].EffectSpriteType	= EFFECTSPRITETYPE_OBSERVINGEYE_REDEYE;
	(*g_pActionInfoTable)[RESULT_SKILL_OBSERVING_EYE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_OBSERVING_EYE][0].Count				= FrameSize[EFFECTSPRITETYPE_OBSERVINGEYE_REDEYE];
	(*g_pActionInfoTable)[RESULT_SKILL_OBSERVING_EYE][0].SetDelayNode();

	// REFLECT_REFLECTION,	// SKILL_REFLECTION 방어막
	(*g_pActionInfoTable)[SKILL_REFLECTION_EFFECT].Set("SKILL_REFLECTION_EFFECT", ACTION_STAND, EFFECTSPRITETYPE_REFLECTION_2, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_REFLECTION_EFFECT].SetCastingFramesAll( 5 );
	(*g_pActionInfoTable)[SKILL_REFLECTION_EFFECT].SetSoundID( SOUND_SLAYER_ENCHANT_AURASHIELD2 );
	// SKILL_CURE_EFFECT,	// Cure Critical Wounds
	(*g_pActionInfoTable)[SKILL_REFLECTION_EFFECT].Set("SKILL_CURE_EFFECT", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[SKILL_REFLECTION_EFFECT].SetSoundID( SOUNDID_NULL );//SOUND_SLAYER_HEALING_CCW );
	//(*g_pActionInfoTable)[SKILL_CURE_EFFECT].SetStartWithCasting();
	//(*g_pActionInfoTable)[SKILL_CURE_EFFECT].SetCastingFramesAll( FrameSize[EFFECTSPRITETYPE_CURE_2_2] );	

	// SKILL_REFLECTION_EFFECT,	// Cure Critical Wounds
	(*g_pActionInfoTable)[RESULT_SKILL_REFLECTION_EFFECT].Set("RESULT_SKILL_REFLECTION_EFFECT", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_REFLECTION_EFFECT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_REFLECTION_EFFECT].SetStartWithCasting();
	//(*g_pActionInfoTable)[RESULT_SKILL_REFLECTION_EFFECT].SetCastingFramesAll( FrameSize[EFFECTSPRITETYPE_CURE_2_2] );
	//(*g_pActionInfoTable)[RESULT_SKILL_REFLECTION_EFFECT].SetMainNode( 1 );	
	(*g_pActionInfoTable)[RESULT_SKILL_REFLECTION_EFFECT].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_REFLECTION_EFFECT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_REFLECTION_EFFECT][0].EffectSpriteType	= EFFECTSPRITETYPE_CURE_ALL_2;
	(*g_pActionInfoTable)[RESULT_SKILL_REFLECTION_EFFECT][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_REFLECTION_EFFECT][0].Count				= FrameSize[EFFECTSPRITETYPE_CURE_ALL_2];
	(*g_pActionInfoTable)[RESULT_SKILL_REFLECTION_EFFECT][0].SoundID				= SOUND_SLAYER_HEALING_CCW;

	
	// SHRINE_SHIELD, 성단 보호박
	(*g_pActionInfoTable)[SHRINE_SHIELD].Set("SHRINE_SHIELD", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[SHRINE_SHIELD].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SHRINE_SHIELD].SetStartWithCasting();
	(*g_pActionInfoTable)[SHRINE_SHIELD].Init( 3 );
	(*g_pActionInfoTable)[SHRINE_SHIELD].SetMainNode(1);
	(*g_pActionInfoTable)[SHRINE_SHIELD][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SHRINE_SHIELD][0].EffectSpriteType	= EFFECTSPRITETYPE_SHRINE_SHIELD_START;
	(*g_pActionInfoTable)[SHRINE_SHIELD][0].Step				= 30;
	(*g_pActionInfoTable)[SHRINE_SHIELD][0].Count				= FrameSize[EFFECTSPRITETYPE_SHRINE_SHIELD_START];
	(*g_pActionInfoTable)[SHRINE_SHIELD][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SHRINE_SHIELD][1].EffectSpriteType	= EFFECTSPRITETYPE_SHRINE_SHIELD_ING;
	(*g_pActionInfoTable)[SHRINE_SHIELD][1].Step				= 30;
	(*g_pActionInfoTable)[SHRINE_SHIELD][1].Count				= FrameSize[EFFECTSPRITETYPE_SHRINE_SHIELD_ING];
	(*g_pActionInfoTable)[SHRINE_SHIELD][1].SetDelayNode();
	(*g_pActionInfoTable)[SHRINE_SHIELD][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SHRINE_SHIELD][2].EffectSpriteType	= EFFECTSPRITETYPE_SHRINE_SHIELD_END;
	(*g_pActionInfoTable)[SHRINE_SHIELD][2].Step				= 30;
	(*g_pActionInfoTable)[SHRINE_SHIELD][2].Count				= FrameSize[EFFECTSPRITETYPE_SHRINE_SHIELD_END];

	(*g_pActionInfoTable)[DROP_BLOOD_BIBLE].Set("DROP_BLOOD_BIBLE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE);
	//(*g_pActionInfoTable)[DROP_BLOOD_BIBLE].SetStartWithCasting();	
	(*g_pActionInfoTable)[DROP_BLOOD_BIBLE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[DROP_BLOOD_BIBLE].Init( 1 );
	(*g_pActionInfoTable)[DROP_BLOOD_BIBLE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[DROP_BLOOD_BIBLE][0].EffectSpriteType = EFFECTSPRITETYPE_DROP_BLOOD_BIBLE;
	(*g_pActionInfoTable)[DROP_BLOOD_BIBLE][0].Step				= 30;
	(*g_pActionInfoTable)[DROP_BLOOD_BIBLE][0].Count			= FrameSize[EFFECTSPRITETYPE_DROP_BLOOD_BIBLE];
	(*g_pActionInfoTable)[DROP_BLOOD_BIBLE][0].SetDelayNode();

	(*g_pActionInfoTable)[GREGORI_TILE].Set("GREGORI_TILE",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[GREGORI_TILE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[GREGORI_TILE].Init( 1 );
	(*g_pActionInfoTable)[GREGORI_TILE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[GREGORI_TILE][0].EffectSpriteType = EFFECTSPRITETYPE_GREGORI_TILE;
	(*g_pActionInfoTable)[GREGORI_TILE][0].Step						= 30;
	(*g_pActionInfoTable)[GREGORI_TILE][0].Count					= FrameSize[EFFECTSPRITETYPE_GREGORI_TILE];
	(*g_pActionInfoTable)[GREGORI_TILE][0].SetDelayNode();

	(*g_pActionInfoTable)[NEMA_TILE].Set("NEMA_TILE",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[NEMA_TILE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[NEMA_TILE].Init( 1 );
	(*g_pActionInfoTable)[NEMA_TILE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[NEMA_TILE][0].EffectSpriteType = EFFECTSPRITETYPE_NEMA_TILE;
	(*g_pActionInfoTable)[NEMA_TILE][0].Step						= 30;
	(*g_pActionInfoTable)[NEMA_TILE][0].Count					= FrameSize[EFFECTSPRITETYPE_NEMA_TILE];
	(*g_pActionInfoTable)[NEMA_TILE][0].SetDelayNode();

	(*g_pActionInfoTable)[LEGIOS_TILE].Set("LEGIOS_TILE",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[LEGIOS_TILE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[LEGIOS_TILE].Init( 1 );
	(*g_pActionInfoTable)[LEGIOS_TILE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[LEGIOS_TILE][0].EffectSpriteType = EFFECTSPRITETYPE_LEGIOS_TILE;
	(*g_pActionInfoTable)[LEGIOS_TILE][0].Step						= 30;
	(*g_pActionInfoTable)[LEGIOS_TILE][0].Count					= FrameSize[EFFECTSPRITETYPE_LEGIOS_TILE];
	(*g_pActionInfoTable)[LEGIOS_TILE][0].SetDelayNode();

	(*g_pActionInfoTable)[MIHOLE_TILE].Set("MIHOLE_TILE",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[MIHOLE_TILE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MIHOLE_TILE].Init( 1 );
	(*g_pActionInfoTable)[MIHOLE_TILE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[MIHOLE_TILE][0].EffectSpriteType = EFFECTSPRITETYPE_MIHOLE_TILE;
	(*g_pActionInfoTable)[MIHOLE_TILE][0].Step						= 30;
	(*g_pActionInfoTable)[MIHOLE_TILE][0].Count					= FrameSize[EFFECTSPRITETYPE_MIHOLE_TILE];
	(*g_pActionInfoTable)[MIHOLE_TILE][0].SetDelayNode();

	(*g_pActionInfoTable)[AROSA_TILE].Set("AROSA_TILE",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[AROSA_TILE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[AROSA_TILE].Init( 1 );
	(*g_pActionInfoTable)[AROSA_TILE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[AROSA_TILE][0].EffectSpriteType = EFFECTSPRITETYPE_AROSA_TILE;
	(*g_pActionInfoTable)[AROSA_TILE][0].Step						= 30;
	(*g_pActionInfoTable)[AROSA_TILE][0].Count					= FrameSize[EFFECTSPRITETYPE_AROSA_TILE];
	(*g_pActionInfoTable)[AROSA_TILE][0].SetDelayNode();

	(*g_pActionInfoTable)[ARMEGA_TILE].Set("ARMEGA_TILE",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[ARMEGA_TILE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[ARMEGA_TILE].Init( 1 );
	(*g_pActionInfoTable)[ARMEGA_TILE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[ARMEGA_TILE][0].EffectSpriteType = EFFECTSPRITETYPE_ARMEGA_TILE;
	(*g_pActionInfoTable)[ARMEGA_TILE][0].Step						= 30;
	(*g_pActionInfoTable)[ARMEGA_TILE][0].Count					= FrameSize[EFFECTSPRITETYPE_ARMEGA_TILE];
	(*g_pActionInfoTable)[ARMEGA_TILE][0].SetDelayNode();

	(*g_pActionInfoTable)[INI_TILE].Set("INI_TILE",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[INI_TILE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[INI_TILE].Init( 1 );
	(*g_pActionInfoTable)[INI_TILE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[INI_TILE][0].EffectSpriteType = EFFECTSPRITETYPE_INI_TILE;
	(*g_pActionInfoTable)[INI_TILE][0].Step						= 30;
	(*g_pActionInfoTable)[INI_TILE][0].Count					= FrameSize[EFFECTSPRITETYPE_INI_TILE];
	(*g_pActionInfoTable)[INI_TILE][0].SetDelayNode();

	(*g_pActionInfoTable)[JAVE_TILE].Set("JAVE_TILE",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[JAVE_TILE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[JAVE_TILE].Init( 1 );
	(*g_pActionInfoTable)[JAVE_TILE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[JAVE_TILE][0].EffectSpriteType = EFFECTSPRITETYPE_JAVE_TILE;
	(*g_pActionInfoTable)[JAVE_TILE][0].Step						= 30;
	(*g_pActionInfoTable)[JAVE_TILE][0].Count					= FrameSize[EFFECTSPRITETYPE_JAVE_TILE];
	(*g_pActionInfoTable)[JAVE_TILE][0].SetDelayNode();

	(*g_pActionInfoTable)[CHASPA_TILE].Set("CHASPA_TILE",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[CHASPA_TILE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[CHASPA_TILE].Init( 1 );
	(*g_pActionInfoTable)[CHASPA_TILE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[CHASPA_TILE][0].EffectSpriteType = EFFECTSPRITETYPE_CHASPA_TILE;
	(*g_pActionInfoTable)[CHASPA_TILE][0].Step						= 30;
	(*g_pActionInfoTable)[CHASPA_TILE][0].Count					= FrameSize[EFFECTSPRITETYPE_CHASPA_TILE];
	(*g_pActionInfoTable)[CHASPA_TILE][0].SetDelayNode();

	(*g_pActionInfoTable)[CONCILIA_TILE].Set("CONCILIA_TILE",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[CONCILIA_TILE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[CONCILIA_TILE].Init( 1 );
	(*g_pActionInfoTable)[CONCILIA_TILE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[CONCILIA_TILE][0].EffectSpriteType = EFFECTSPRITETYPE_CONCILIA_TILE;
	(*g_pActionInfoTable)[CONCILIA_TILE][0].Step						= 30;
	(*g_pActionInfoTable)[CONCILIA_TILE][0].Count					= FrameSize[EFFECTSPRITETYPE_CONCILIA_TILE];
	(*g_pActionInfoTable)[CONCILIA_TILE][0].SetDelayNode();

	(*g_pActionInfoTable)[KIRO_TILE].Set("KIRO_TILE",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[KIRO_TILE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[KIRO_TILE].Init( 1 );
	(*g_pActionInfoTable)[KIRO_TILE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[KIRO_TILE][0].EffectSpriteType = EFFECTSPRITETYPE_KIRO_TILE;
	(*g_pActionInfoTable)[KIRO_TILE][0].Step						= 30;
	(*g_pActionInfoTable)[KIRO_TILE][0].Count					= FrameSize[EFFECTSPRITETYPE_KIRO_TILE];
	(*g_pActionInfoTable)[KIRO_TILE][0].SetDelayNode();

	(*g_pActionInfoTable)[HILLEL_TILE].Set("HILLEL_TILE",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[HILLEL_TILE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[HILLEL_TILE].Init( 1 );
	(*g_pActionInfoTable)[HILLEL_TILE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[HILLEL_TILE][0].EffectSpriteType = EFFECTSPRITETYPE_HILLEL_TILE;
	(*g_pActionInfoTable)[HILLEL_TILE][0].Step						= 30;
	(*g_pActionInfoTable)[HILLEL_TILE][0].Count					= FrameSize[EFFECTSPRITETYPE_HILLEL_TILE];
	(*g_pActionInfoTable)[HILLEL_TILE][0].SetDelayNode();

	(*g_pActionInfoTable)[HOLY_LAND_WARP_VAMPIRE].Set("HOLY_LAND_WARP_VAMPIRE",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[HOLY_LAND_WARP_VAMPIRE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[HOLY_LAND_WARP_VAMPIRE].Init( 1 );
	(*g_pActionInfoTable)[HOLY_LAND_WARP_VAMPIRE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[HOLY_LAND_WARP_VAMPIRE][0].EffectSpriteType = EFFECTSPRITETYPE_WARP_HOLY_LAND_VAMPIRE_START;
	(*g_pActionInfoTable)[HOLY_LAND_WARP_VAMPIRE][0].Step						= 30;
	(*g_pActionInfoTable)[HOLY_LAND_WARP_VAMPIRE][0].Count					= FrameSize[EFFECTSPRITETYPE_WARP_HOLY_LAND_VAMPIRE_START];
//	(*g_pActionInfoTable)[HOLY_LAND_WARP_VAMPIRE][0].SetDelayNode();

	(*g_pActionInfoTable)[HOLY_LAND_WARP_SLAYER].Set("HOLY_LAND_WARP_SLAYER",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[HOLY_LAND_WARP_SLAYER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[HOLY_LAND_WARP_SLAYER].Init( 1 );
	(*g_pActionInfoTable)[HOLY_LAND_WARP_SLAYER][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[HOLY_LAND_WARP_SLAYER][0].EffectSpriteType = EFFECTSPRITETYPE_WARP_HOLY_LAND_SLAYER_START;
	(*g_pActionInfoTable)[HOLY_LAND_WARP_SLAYER][0].Step						= 30;
	(*g_pActionInfoTable)[HOLY_LAND_WARP_SLAYER][0].Count					= FrameSize[EFFECTSPRITETYPE_WARP_HOLY_LAND_SLAYER_START];
//	(*g_pActionInfoTable)[HOLY_LAND_WARP_SLAYER][0].SetDelayNode();

	(*g_pActionInfoTable)[WARP_BLOOD_BIBLE_TILE].Set("WARP_BLOOD_BIBLE_TILE",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[WARP_BLOOD_BIBLE_TILE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[WARP_BLOOD_BIBLE_TILE].Init( 1 );
	(*g_pActionInfoTable)[WARP_BLOOD_BIBLE_TILE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[WARP_BLOOD_BIBLE_TILE][0].EffectSpriteType = EFFECTSPRITETYPE_WARP_BLOOD_BIBLE_TILE;
	(*g_pActionInfoTable)[WARP_BLOOD_BIBLE_TILE][0].Step						= 30;
	(*g_pActionInfoTable)[WARP_BLOOD_BIBLE_TILE][0].Count					= FrameSize[EFFECTSPRITETYPE_WARP_BLOOD_BIBLE_TILE];

	(*g_pActionInfoTable)[AMBER_OF_GUARD_TILE].Set("AMBER_OF_GUARD_TILE",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[AMBER_OF_GUARD_TILE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[AMBER_OF_GUARD_TILE].Init( 1 );
	(*g_pActionInfoTable)[AMBER_OF_GUARD_TILE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[AMBER_OF_GUARD_TILE][0].EffectSpriteType = EFFECTSPRITETYPE_AMBER_OF_GUARD_TILE;
	(*g_pActionInfoTable)[AMBER_OF_GUARD_TILE][0].Step						= 30;
	(*g_pActionInfoTable)[AMBER_OF_GUARD_TILE][0].Count					= FrameSize[EFFECTSPRITETYPE_AMBER_OF_GUARD_TILE];
	(*g_pActionInfoTable)[AMBER_OF_GUARD_TILE][0].SetDelayNode();

	(*g_pActionInfoTable)[AMBER_OF_AVENGER_TILE].Set("AMBER_OF_AVENGER_TILE",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[AMBER_OF_AVENGER_TILE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[AMBER_OF_AVENGER_TILE].Init( 1 );
	(*g_pActionInfoTable)[AMBER_OF_AVENGER_TILE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[AMBER_OF_AVENGER_TILE][0].EffectSpriteType = EFFECTSPRITETYPE_AMBER_OF_AVENGER_TILE;
	(*g_pActionInfoTable)[AMBER_OF_AVENGER_TILE][0].Step						= 30;
	(*g_pActionInfoTable)[AMBER_OF_AVENGER_TILE][0].Count					= FrameSize[EFFECTSPRITETYPE_AMBER_OF_AVENGER_TILE];
	(*g_pActionInfoTable)[AMBER_OF_AVENGER_TILE][0].SetDelayNode();

	(*g_pActionInfoTable)[AMBER_OF_IMMORTAL_TILE].Set("AMBER_OF_IMMORTAL_TILE",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[AMBER_OF_IMMORTAL_TILE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[AMBER_OF_IMMORTAL_TILE].Init( 1 );
	(*g_pActionInfoTable)[AMBER_OF_IMMORTAL_TILE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[AMBER_OF_IMMORTAL_TILE][0].EffectSpriteType = EFFECTSPRITETYPE_AMBER_OF_IMMORTAL_TILE;
	(*g_pActionInfoTable)[AMBER_OF_IMMORTAL_TILE][0].Step						= 30;
	(*g_pActionInfoTable)[AMBER_OF_IMMORTAL_TILE][0].Count					= FrameSize[EFFECTSPRITETYPE_AMBER_OF_IMMORTAL_TILE];
	(*g_pActionInfoTable)[AMBER_OF_IMMORTAL_TILE][0].SetDelayNode();

	(*g_pActionInfoTable)[AMBER_OF_CURSE_TILE].Set("AMBER_OF_CURSE_TILE",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[AMBER_OF_CURSE_TILE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[AMBER_OF_CURSE_TILE].Init( 1 );
	(*g_pActionInfoTable)[AMBER_OF_CURSE_TILE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[AMBER_OF_CURSE_TILE][0].EffectSpriteType = EFFECTSPRITETYPE_AMBER_OF_CURSE_TILE;
	(*g_pActionInfoTable)[AMBER_OF_CURSE_TILE][0].Step						= 30;
	(*g_pActionInfoTable)[AMBER_OF_CURSE_TILE][0].Count					= FrameSize[EFFECTSPRITETYPE_AMBER_OF_CURSE_TILE];
	(*g_pActionInfoTable)[AMBER_OF_CURSE_TILE][0].SetDelayNode();

//	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER].Set("MAGIC_BLOODY_BREAKER", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
//	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER].SetStartFrameAll( 10 );
//	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER].SetSoundID( SOUNDID_NULL );
//	(*g_pActionInfoTable)[MAGIC_BLOODY_BREAKER].SetOptionRangeToDirection();

	(*g_pActionInfoTable)[SKILL_LOVE_CHAIN].Set("SKILL_LOVE_CHAIN", ACTION_STAND, EFFECTSPRITETYPE_NULL, 6, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER );
	(*g_pActionInfoTable)[SKILL_LOVE_CHAIN].SetSoundID( SOUNDID_NULL );
	

	(*g_pActionInfoTable)[SKILL_MAGIC_ELUSION].Set("SKILL_MAGIC_ELUSION", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_MAGIC_ELUSION].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_MAGIC_ELUSION].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_MAGIC_ELUSION].SetSkillFailDelay(); // 스킬실패해도 딜레이는 남아 있다..

	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_ELUSION].Set("RESULT_SKILL_MAGIC_ELUSION", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_ELUSION].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_ELUSION].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_ELUSION].Init( 3 );
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_ELUSION].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_ELUSION][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_ZONE; //EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_ELUSION][0].EffectSpriteType = EFFECTSPRITETYPE_MAGIC_ELUSION_START;
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_ELUSION][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_ELUSION][0].Count				= FrameSize[EFFECTSPRITETYPE_MAGIC_ELUSION_START];
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_ELUSION][0].SoundID			= SOUND_SLAYER_ENCHANT_B1;
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_ELUSION][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_ELUSION][1].EffectSpriteType = EFFECTSPRITETYPE_MAGIC_ELUSION_ING;
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_ELUSION][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_ELUSION][1].Count				= FrameSize[EFFECTSPRITETYPE_MAGIC_ELUSION_ING];
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_ELUSION][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_ELUSION][1].SetResultTime();
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_ELUSION][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_ELUSION][2].EffectSpriteType	= EFFECTSPRITETYPE_MAGIC_ELUSION_END;
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_ELUSION][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_ELUSION][2].Count				= FrameSize[EFFECTSPRITETYPE_MAGIC_ELUSION_END];
		

	(*g_pActionInfoTable)[SKILL_ILLUSION_OF_AVENGE].Set("SKILL_ILLUSION_OF_AVENGE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_ILLUSION_OF_AVENGE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_ILLUSION_OF_AVENGE].SetSkillFailDelay(); // 스킬실패해도 딜레이는 남아 있다..

	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_OF_AVENGE].Set("RESULT_SKILL_ILLUSION_OF_AVENGE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, 3);
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_OF_AVENGE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_OF_AVENGE].SetStartFrameAll( 5 );	
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_OF_AVENGE].Init( 2 );
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_OF_AVENGE][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_OF_AVENGE][0].EffectSpriteType = EFFECTSPRITETYPE_ILLUSION_OF_AVENGE;
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_OF_AVENGE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_OF_AVENGE][0].Count				= FrameSize[EFFECTSPRITETYPE_ILLUSION_OF_AVENGE];
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_OF_AVENGE][0].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_OF_AVENGE][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_OF_AVENGE][1].EffectSpriteType = EFFECTSPRITETYPE_ILLUSION_OF_AVENGE_TILE;
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_OF_AVENGE][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_OF_AVENGE][1].Count				= FrameSize[EFFECTSPRITETYPE_ILLUSION_OF_AVENGE_TILE];	
	
	(*g_pActionInfoTable)[SKILL_DENIAL_MAGIC].Set("SKILL_DENIAL_MAGIC", ACTION_MAGIC,EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_DENIAL_MAGIC].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_DENIAL_MAGIC].Set("RESULT_SKILL_WILL_OF_LIFE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[RESULT_SKILL_DENIAL_MAGIC].SetSoundID( SOUND_DENIAL_MAGIC_START );
	(*g_pActionInfoTable)[RESULT_SKILL_DENIAL_MAGIC].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_DENIAL_MAGIC].SetCastingActionInfo( CASTING_HEALING );
	(*g_pActionInfoTable)[RESULT_SKILL_DENIAL_MAGIC].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_DENIAL_MAGIC][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_DENIAL_MAGIC][0].EffectSpriteType = EFFECTSPRITETYPE_DENIAL_MAGIC_START;
	(*g_pActionInfoTable)[RESULT_SKILL_DENIAL_MAGIC][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_DENIAL_MAGIC][0].Count				= FrameSize[EFFECTSPRITETYPE_DENIAL_MAGIC_START];

	(*g_pActionInfoTable)[SKILL_DENIAL_MAGIC_DAMAGED].Set("SKILL_DENIAL_MAGIC_DAMAGED", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL,8,FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER );
	(*g_pActionInfoTable)[SKILL_DENIAL_MAGIC_DAMAGED].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_DENIAL_MAGIC_DAMAGED].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_DENIAL_MAGIC_DAMAGED].Init( 1 );
	(*g_pActionInfoTable)[SKILL_DENIAL_MAGIC_DAMAGED][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_DENIAL_MAGIC_DAMAGED][0].EffectSpriteType = EFFECTSPRITETYPE_DENIAL_MAGIC_DAMAGE;
	(*g_pActionInfoTable)[SKILL_DENIAL_MAGIC_DAMAGED][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_DENIAL_MAGIC_DAMAGED][0].Count				= FrameSize[EFFECTSPRITETYPE_DENIAL_MAGIC_DAMAGE];

	(*g_pActionInfoTable)[SKILL_REQUITAL].Set("SKILL_REQUITAL", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_REQUITAL].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_REQUITAL].SetCastingActionInfo( CASTING_ENCHANT );	

	(*g_pActionInfoTable)[RESULT_SKILL_REQUITAL].Set("RESULT_SKILL_REQUITAL", ACTION_STAND, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER );
	(*g_pActionInfoTable)[RESULT_SKILL_REQUITAL].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_REQUITAL].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_REQUITAL].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_REQUITAL][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_REQUITAL][0].EffectSpriteType =  EFFECTSPRITETYPE_REQUITAL;
	(*g_pActionInfoTable)[RESULT_SKILL_REQUITAL][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_REQUITAL][0].Count				= FrameSize[EFFECTSPRITETYPE_REQUITAL];
	(*g_pActionInfoTable)[RESULT_SKILL_REQUITAL][0].SoundID				= SOUND_REQUITAL;
	(*g_pActionInfoTable)[RESULT_SKILL_REQUITAL][0].LinkCount			= 0;
//	(*g_pActionInfoTable)[RESULT_SKILL_REQUITAL][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_ZONE;
//	(*g_pActionInfoTable)[RESULT_SKILL_REQUITAL][1].EffectSpriteType = EFFECTSPRITETYPE_REQUITAL_GROUND;
//	(*g_pActionInfoTable)[RESULT_SKILL_REQUITAL][1].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_SKILL_REQUITAL][1].Count				= FrameSize[EFFECTSPRITETYPE_REQUITAL_GROUND];
	
	(*g_pActionInfoTable)[SKILL_CONCEALMENT].Set("SKILL_CONCEALMENT", ACTION_MAGIC , EFFECTSPRITETYPE_NULL, 8 , FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER );
	(*g_pActionInfoTable)[SKILL_CONCEALMENT].SetSoundID( SOUNDID_NULL );	
	(*g_pActionInfoTable)[SKILL_CONCEALMENT].SetEffectStatus( EFFECTSTATUS_CONCEALMENT );
	
	(*g_pActionInfoTable)[RESULT_SKILL_CONCEALMENT].Set("RESULT_SKILL_CONCEALMENT", ACTION_STAND, EFFECTSPRITETYPE_NULL, 8 , FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_CONCEALMENT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_CONCEALMENT].Init( 3 );
	(*g_pActionInfoTable)[RESULT_SKILL_CONCEALMENT].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_CONCEALMENT][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE; 
	(*g_pActionInfoTable)[RESULT_SKILL_CONCEALMENT][0].EffectSpriteType = EFFECTSPRITETYPE_CONCEALMENT_START;
	(*g_pActionInfoTable)[RESULT_SKILL_CONCEALMENT][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_CONCEALMENT][0].Count			= FrameSize[EFFECTSPRITETYPE_CONCEALMENT_START];
	(*g_pActionInfoTable)[RESULT_SKILL_CONCEALMENT][0].LinkCount		= FrameSize[EFFECTSPRITETYPE_CONCEALMENT_START];
	(*g_pActionInfoTable)[RESULT_SKILL_CONCEALMENT][0].SoundID			= SOUND_CONCEALMENT;
	(*g_pActionInfoTable)[RESULT_SKILL_CONCEALMENT][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_CONCEALMENT][1].EffectSpriteType = EFFECTSPRITETYPE_CONCEALMENT_ING;
	(*g_pActionInfoTable)[RESULT_SKILL_CONCEALMENT][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_CONCEALMENT][1].Count			= FrameSize[EFFECTSPRITETYPE_CONCEALMENT_ING];
	(*g_pActionInfoTable)[RESULT_SKILL_CONCEALMENT][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_SKILL_CONCEALMENT][2].EffectGeneratorID= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_CONCEALMENT][2].EffectSpriteType = EFFECTSPRITETYPE_CONCEALMENT_END;
	(*g_pActionInfoTable)[RESULT_SKILL_CONCEALMENT][2].Step				=25;
	(*g_pActionInfoTable)[RESULT_SKILL_CONCEALMENT][2].Count			= FrameSize[EFFECTSPRITETYPE_CONCEALMENT_END];

	(*g_pActionInfoTable)[SKILL_SWORD_RAY].Set("SKILL_SWORD_RAY", ACTION_SLAYER_SWORD_2, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_SWORD_2]);
	(*g_pActionInfoTable)[SKILL_SWORD_RAY].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_SWORD_RAY].SetStartFrameAll( 2 );
	(*g_pActionInfoTable)[SKILL_SWORD_RAY].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_SWORD_RAY].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_SWORD_RAY].Init( 3 );
	(*g_pActionInfoTable)[SKILL_SWORD_RAY][0].EffectGeneratorID = EFFECTGENERATORID_ATTACK_ZONE ;//EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[SKILL_SWORD_RAY][0].EffectSpriteType	= EFFECTSPRITETYPE_SWORD_RAY_1;
	(*g_pActionInfoTable)[SKILL_SWORD_RAY][0].Step				= 20;
	(*g_pActionInfoTable)[SKILL_SWORD_RAY][0].Count				= 32;
	(*g_pActionInfoTable)[SKILL_SWORD_RAY][1].EffectGeneratorID = EFFECTGENERATORID_ATTACK_ZONE_RECT;
	(*g_pActionInfoTable)[SKILL_SWORD_RAY][1].EffectSpriteType	= EFFECTSPRITETYPE_SWORD_RAY_3;
	(*g_pActionInfoTable)[SKILL_SWORD_RAY][1].Step				= 15;
	(*g_pActionInfoTable)[SKILL_SWORD_RAY][1].Count				= FrameSize[EFFECTSPRITETYPE_SWORD_RAY_3];
	(*g_pActionInfoTable)[SKILL_SWORD_RAY][1].SoundID			= SOUND_ITEM_BOOM3;
	(*g_pActionInfoTable)[SKILL_SWORD_RAY][2].EffectGeneratorID = EFFECTGENERATORID_ATTACH_ZONE_AROUND;
	(*g_pActionInfoTable)[SKILL_SWORD_RAY][2].EffectSpriteType	= EFFECTSPRITETYPE_SWORD_RAY_2;
	(*g_pActionInfoTable)[SKILL_SWORD_RAY][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SWORD_RAY][2].Count				= FrameSize[EFFECTSPRITETYPE_SWORD_RAY_2];	
	(*g_pActionInfoTable)[SKILL_SWORD_RAY][2].SetResultTime();

	
	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_RAY].Set("RESULT_SKILL_SWORD_RAY", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF );
	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_RAY].SetSoundID( SOUNDID_NULL );
//	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_RAY].Init( 2 );
//	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_RAY][0].EffectGeneratorID = EFFECTGENERATORID_ATTACK_ZONE_RECT;
//	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_RAY][0].EffectSpriteType	= EFFECTSPRITETYPE_SWORD_RAY_3;
//	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_RAY][0].Step				 =8;
//	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_RAY][0].Count				= FrameSize[EFFECTSPRITETYPE_SWORD_RAY_3];
//	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_RAY][0].SoundID			= SOUND_ITEM_BOOM3;
//	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_RAY][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_ZONE_AROUND;
//	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_RAY][1].EffectSpriteType	= EFFECTSPRITETYPE_SWORD_RAY_2;
//	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_RAY][1].Step				 =25;
//	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_RAY][1].Count				= FrameSize[EFFECTSPRITETYPE_SWORD_RAY_2];	
//	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_RAY][1].SetResultTime();

	(*g_pActionInfoTable)[SKILL_MULTI_AMPUTATE].Set("SKILL_MULTI_AMPUTATE", ACTION_SLAYER_BLADE_2, EFFECTSPRITETYPE_NULL, 6, FLAG_ACTIONINFO_TARGET_OTHER , FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_BLADE_2] );
	(*g_pActionInfoTable)[SKILL_MULTI_AMPUTATE].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_MULTI_AMPUTATE].SetActionStepCnt(2) ;
	(*g_pActionInfoTable)[SKILL_MULTI_AMPUTATE].SetStartFrameAll( 8 );
	(*g_pActionInfoTable)[SKILL_MULTI_AMPUTATE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_MULTI_AMPUTATE].Init( 1 );
	(*g_pActionInfoTable)[SKILL_MULTI_AMPUTATE][0].EffectGeneratorID = EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[SKILL_MULTI_AMPUTATE][0].EffectSpriteType		= EFFECTSPRITETYPE_MULTI_AMPUTATE_1;
	(*g_pActionInfoTable)[SKILL_MULTI_AMPUTATE][0].Step					= 20;
	(*g_pActionInfoTable)[SKILL_MULTI_AMPUTATE][0].Count				= 32;
	(*g_pActionInfoTable)[SKILL_MULTI_AMPUTATE][0].SoundID				= SOUND_AMPUTATE;
	
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_AMPUTATE].Set("RESULT_SKILL_MULTI_AMPUTATE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF );
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_AMPUTATE].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_AMPUTATE].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_AMPUTATE][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_AMPUTATE][0].EffectSpriteType	= EFFECTSPRITETYPE_MULTI_AMPUTATE_2;
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_AMPUTATE][0].Step				 =25;
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_AMPUTATE][0].Count				= FrameSize[EFFECTSPRITETYPE_MULTI_AMPUTATE_2];
	(*g_pActionInfoTable)[RESULT_SKILL_MULTI_AMPUTATE][0].SoundID			= SOUND_SLAYER_ENCHANT_AURARING2;

	(*g_pActionInfoTable)[MAGIC_TRANS_ITEM_OK].Set("MAGIC_TRANS_ITEM_OK", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ITEM, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[MAGIC_TRANS_ITEM_OK].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[MAGIC_TRANS_ITEM_OK].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[MAGIC_TRANS_ITEM_OK].SetStartWithCasting();
	(*g_pActionInfoTable)[MAGIC_TRANS_ITEM_OK].SetSoundID( SOUNDID_NULL );		
	(*g_pActionInfoTable)[MAGIC_TRANS_ITEM_OK].Init( 2 );
	(*g_pActionInfoTable)[MAGIC_TRANS_ITEM_OK][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_INVENTORY;
	(*g_pActionInfoTable)[MAGIC_TRANS_ITEM_OK][0].EffectSpriteType	= EFFECTSPRITETYPE_ENCHANT_START;
	(*g_pActionInfoTable)[MAGIC_TRANS_ITEM_OK][0].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_TRANS_ITEM_OK][0].Count				= FrameSize[EFFECTSPRITETYPE_ENCHANT_START];
	(*g_pActionInfoTable)[MAGIC_TRANS_ITEM_OK][0].SoundID			= SOUND_SLAYER_ENCHANT_CHW1;
	(*g_pActionInfoTable)[MAGIC_TRANS_ITEM_OK][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_INVENTORY;	// 반복
	(*g_pActionInfoTable)[MAGIC_TRANS_ITEM_OK][1].EffectSpriteType	= EFFECTSPRITETYPE_ENCHANT_OPTION_PLUS;
	(*g_pActionInfoTable)[MAGIC_TRANS_ITEM_OK][1].Step				= 25;
	(*g_pActionInfoTable)[MAGIC_TRANS_ITEM_OK][1].Count				= FrameSize[EFFECTSPRITETYPE_ENCHANT_OPTION_PLUS];

	(*g_pActionInfoTable)[SKILL_ILLENDUE].Set("SKILL_ILLENDUE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_ILLENDUE].SetStartFrameAll( 7 );	
	(*g_pActionInfoTable)[SKILL_ILLENDUE].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_ILLENDUE].Set("RESULT_SKILL_ILLENDUE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_ILLENDUE].SetSoundID( SOUNDID_NULL);

	(*g_pActionInfoTable)[SKILL_HIT_CONVERT].Set("SKILL_HIT_CONVERT", ACTION_SLAYER_SWORD_2, EFFECTSPRITETYPE_NULL, 6, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_SWORD]);
	(*g_pActionInfoTable)[SKILL_HIT_CONVERT].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_HIT_CONVERT].SetStartFrame( 0, 10 );
	(*g_pActionInfoTable)[SKILL_HIT_CONVERT].SetStartFrame( 1, 8 );
	(*g_pActionInfoTable)[SKILL_HIT_CONVERT].SetStartFrame( 2, 6 );
	(*g_pActionInfoTable)[SKILL_HIT_CONVERT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_HIT_CONVERT].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_HIT_CONVERT].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_HIT_CONVERT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[SKILL_HIT_CONVERT][0].EffectSpriteType	= EFFECTSPRITETYPE_HIT_CONVERT;
	(*g_pActionInfoTable)[SKILL_HIT_CONVERT][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_HIT_CONVERT][0].Count				= 32;//FrameSize[EFFECTSPRITETYPE_ACID_BOLT_1];
	(*g_pActionInfoTable)[SKILL_HIT_CONVERT][0].SoundID			= SOUND_SLAYER_SWORD_DI;	

	// SKILL_HIT_CONVERT
	(*g_pActionInfoTable)[RESULT_SKILL_HIT_CONVERT].Set("RESULT_SKILL_HIT_CONVERT", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 100);	
	(*g_pActionInfoTable)[RESULT_SKILL_HIT_CONVERT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_HIT_CONVERT].SetStartWithCasting();	
	(*g_pActionInfoTable)[RESULT_SKILL_HIT_CONVERT].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_SKILL_HIT_CONVERT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_HIT_CONVERT][0].EffectSpriteType	= EFFECTSPRITETYPE_HIT_CONVERT_DAMAGED;
	(*g_pActionInfoTable)[RESULT_SKILL_HIT_CONVERT][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_HIT_CONVERT][0].Count				= FrameSize[EFFECTGENERATORID_ATTACH_CREATURE];
	(*g_pActionInfoTable)[RESULT_SKILL_HIT_CONVERT][0].LinkCount			= 4;
	(*g_pActionInfoTable)[RESULT_SKILL_HIT_CONVERT][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_HIT_CONVERT][1].EffectSpriteType	= EFFECTSPRITETYPE_HIT_CONVERT_DAMAGED;
	(*g_pActionInfoTable)[RESULT_SKILL_HIT_CONVERT][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_HIT_CONVERT][1].Count				= FrameSize[EFFECTGENERATORID_ATTACH_CREATURE];
	(*g_pActionInfoTable)[RESULT_SKILL_HIT_CONVERT][1].LinkCount			= 4;
	(*g_pActionInfoTable)[RESULT_SKILL_HIT_CONVERT][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_HIT_CONVERT][2].EffectSpriteType	= EFFECTSPRITETYPE_HIT_CONVERT_DAMAGED;
	(*g_pActionInfoTable)[RESULT_SKILL_HIT_CONVERT][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_HIT_CONVERT][2].Count				= FrameSize[EFFECTGENERATORID_ATTACH_CREATURE];
	
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON].Set("SKILL_WILD_TYPHOON", ACTION_SLAYER_BLADE_2, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER| FLAG_ACTIONINFO_TARGET_ZONE , FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_BLADE_2_FAST]);
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON].SetActionStepCnt(2) ;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON].SetStartFrameAll( 13 );	// 기술 effect가 시작되는 frame
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON].Init( 9 );
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON].SetActionResult( ACTIONRESULTNODE_CREATURE_TURNING );		// 빙빙 돈다.
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON].SetOptionRangeToDirection();
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_TYPHOON;		// TYPHOON_BACK
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][0].Step				=8;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_TYPHOON]*2;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][0].SoundID				= SOUND_SLAYER_WILD_TYPHOON; //SOUND_SLAYER_HEALING_R1;	
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][1].EffectGeneratorID	= EFFECTGENERATORID_FOLLOW_PATH;//EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][1].EffectSpriteType	= EFFECTSPRITETYPE_NEW_TYPHOON;		// TYPHOON_BACK
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][1].Step				=8;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][1].Count				= FrameSize[EFFECTSPRITETYPE_NEW_TYPHOON]*2;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][1].SoundID				= SOUND_SLAYER_WILD_TYPHOON; //SOUND_SLAYER_HEALING_R1;	
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][1].SetResultTime();
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][2].EffectGeneratorID	= EFFECTGENERATORID_FOLLOW_PATH;//EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][2].EffectSpriteType	= EFFECTSPRITETYPE_NEW_TYPHOON;		// TYPHOON_BACK
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][2].Step				=8;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][2].Count				= FrameSize[EFFECTSPRITETYPE_NEW_TYPHOON]*2;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][2].SoundID				= SOUND_SLAYER_WILD_TYPHOON; //SOUND_SLAYER_HEALING_R1;	
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][3].EffectGeneratorID	= EFFECTGENERATORID_FOLLOW_PATH;//EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][3].EffectSpriteType	= EFFECTSPRITETYPE_NEW_TYPHOON;		// TYPHOON_BACK
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][3].Step				=8;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][3].Count				= FrameSize[EFFECTSPRITETYPE_NEW_TYPHOON]*2;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][3].SoundID				= SOUND_SLAYER_WILD_TYPHOON; //SOUND_SLAYER_HEALING_R1;	
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][4].EffectGeneratorID	= EFFECTGENERATORID_FOLLOW_PATH;//EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][4].EffectSpriteType	= EFFECTSPRITETYPE_NEW_TYPHOON;		// TYPHOON_BACK
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][4].Step				=8;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][4].Count				= FrameSize[EFFECTSPRITETYPE_NEW_TYPHOON]*2;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][4].SoundID				= SOUND_SLAYER_WILD_TYPHOON; //SOUND_SLAYER_HEALING_R1;	
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][5].EffectGeneratorID	= EFFECTGENERATORID_FOLLOW_PATH;//EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][5].EffectSpriteType	= EFFECTSPRITETYPE_NEW_TYPHOON;		// TYPHOON_BACK
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][5].Step				=8;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][5].Count				= FrameSize[EFFECTSPRITETYPE_NEW_TYPHOON]*2;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][5].SoundID				= SOUND_SLAYER_WILD_TYPHOON; //SOUND_SLAYER_HEALING_R1;	
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][6].EffectGeneratorID	= EFFECTGENERATORID_FOLLOW_PATH;//EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][6].EffectSpriteType	= EFFECTSPRITETYPE_NEW_TYPHOON;		// TYPHOON_BACK
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][6].Step				=8;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][6].Count				= FrameSize[EFFECTSPRITETYPE_NEW_TYPHOON]*2;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][6].SoundID				= SOUND_SLAYER_WILD_TYPHOON; //SOUND_SLAYER_HEALING_R1;	
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][7].EffectGeneratorID	= EFFECTGENERATORID_FOLLOW_PATH;//EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][7].EffectSpriteType	= EFFECTSPRITETYPE_NEW_TYPHOON;		// TYPHOON_BACK
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][7].Step				=8;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][7].Count				= FrameSize[EFFECTSPRITETYPE_NEW_TYPHOON]*2;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][7].SoundID				= SOUND_SLAYER_WILD_TYPHOON; //SOUND_SLAYER_HEALING_R1;	
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][8].EffectGeneratorID	= EFFECTGENERATORID_FOLLOW_PATH;//EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][8].EffectSpriteType	= EFFECTSPRITETYPE_NEW_TYPHOON;		// TYPHOON_BACK
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][8].Step				=8;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][8].Count				= FrameSize[EFFECTSPRITETYPE_NEW_TYPHOON]*2;
	(*g_pActionInfoTable)[SKILL_WILD_TYPHOON][8].SoundID				= SOUND_SLAYER_WILD_TYPHOON; //SOUND_SLAYER_HEALING_R1;		

	(*g_pActionInfoTable)[RESULT_SKILL_WILD_TYPHOON].Set("RESULT_SKILL_TYPHOON", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_WILD_TYPHOON].SetSoundID( SOUNDID_NULL );	

	(*g_pActionInfoTable)[SKILL_ULTIMATE_BLOW].Set("SKILL_ULTIMATE_BLOW", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_GUN_SR_MALE, 3, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[SKILL_ULTIMATE_BLOW].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_ULTIMATE_BLOW].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_ULTIMATE_BLOW].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_ULTIMATE_BLOW].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_ULTIMATE_BLOW].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_ULTIMATE_BLOW].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_ULTIMATE_BLOW].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_ULTIMATE_BLOW].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용
	(*g_pActionInfoTable)[SKILL_ULTIMATE_BLOW].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_ULTIMATE_BLOW].SetCastingStartFrameAll( 14 );	// 불꽃이 붙는 frame
	(*g_pActionInfoTable)[SKILL_ULTIMATE_BLOW].SetCastingFramesAll( 2 );
	(*g_pActionInfoTable)[SKILL_ULTIMATE_BLOW].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_BULLET_OF_LIGHT );	// 맞는 결과를 표현한다.	
	(*g_pActionInfoTable)[SKILL_ULTIMATE_BLOW].Init( 1 );
	(*g_pActionInfoTable)[SKILL_ULTIMATE_BLOW].SetStartFrame( 0, 7 );			// slow
	(*g_pActionInfoTable)[SKILL_ULTIMATE_BLOW].SetStartFrame( 1, 7 );			// normal
	(*g_pActionInfoTable)[SKILL_ULTIMATE_BLOW].SetStartFrame( 2, 5 );			// fast
	(*g_pActionInfoTable)[SKILL_ULTIMATE_BLOW][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_ULTIMATE_BLOW][0].EffectSpriteType		= EFFECTSPRITETYPE_RESULT_ULTIMATE_BLOW;
	(*g_pActionInfoTable)[SKILL_ULTIMATE_BLOW][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_ULTIMATE_BLOW][0].Count				= FrameSize[EFFECTSPRITETYPE_RESULT_ULTIMATE_BLOW];

//	// 2004, 08, 02, sobeit add start
//	(*g_pActionInfoTable)[RESULT_SKILL_ULTIMATE_BLOW].Set("RESULT_SKILL_ULTIMATE_BLOW", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
//	(*g_pActionInfoTable)[RESULT_SKILL_ULTIMATE_BLOW].SetSoundID( SOUNDID_NULL );
//	(*g_pActionInfoTable)[RESULT_SKILL_ULTIMATE_BLOW].Init( 1 );
//	(*g_pActionInfoTable)[RESULT_SKILL_ULTIMATE_BLOW][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
//	(*g_pActionInfoTable)[RESULT_SKILL_ULTIMATE_BLOW][0].EffectSpriteType = EFFECTSPRITETYPE_RESULT_ULTIMATE_BLOW;
//	(*g_pActionInfoTable)[RESULT_SKILL_ULTIMATE_BLOW][0].Step			 = 25;
//	(*g_pActionInfoTable)[RESULT_SKILL_ULTIMATE_BLOW][0].Count			= FrameSize[EFFECTSPRITETYPE_RESULT_ULTIMATE_BLOW];
//	(*g_pActionInfoTable)[RESULT_SKILL_ULTIMATE_BLOW][0].SoundID			= SOUNDID_NULL;
//	// 2004, 08, 02, sobeit add end
//	
	(*g_pActionInfoTable)[SKILL_LIGHTNESS].Set("SKILL_LIGHTNESS", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_LIGHTNESS].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[SKILL_LIGHTNESS].SetCastingActionInfo( CASTING_ENCHANT );	
	(*g_pActionInfoTable)[SKILL_LIGHTNESS].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[SKILL_LIGHTNESS].SetStartFrameAll( 7 );
	(*g_pActionInfoTable)[SKILL_LIGHTNESS].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNESS].Set("RESULT_MAGIC_LIGHT", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);	
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNESS].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNESS].Init( 3 );	
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNESS].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNESS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNESS][0].EffectSpriteType	= EFFECTSPRITETYPE_LIGHTNESS_1;
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNESS][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNESS][0].Count				= FrameSize[EFFECTSPRITETYPE_LIGHTNESS_1];
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNESS][0].SoundID			= SOUND_SLAYER_ENCHANT_L;
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNESS][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNESS][1].EffectSpriteType	= EFFECTSPRITETYPE_LIGHTNESS_2;
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNESS][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNESS][1].Count				= FrameSize[EFFECTSPRITETYPE_LIGHTNESS_2];
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNESS][1].SetResultTime();
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNESS][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNESS][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNESS][2].EffectSpriteType	= EFFECTSPRITETYPE_LIGHTNESS_3;
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNESS][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_LIGHTNESS][2].Count				= FrameSize[EFFECTSPRITETYPE_LIGHTNESS_3];

	(*g_pActionInfoTable)[SKILL_BLITZ_SLIDING].Set("SKILL_BLITZ_SLIDING", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[SKILL_BLITZ_SLIDING].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_BLITZ_SLIDING].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_BLITZ_SLIDING_ATTACK );
	
	(*g_pActionInfoTable)[RESULT_SKILL_BLITZ_SLIDING].Set("RESULT_SKILL_BLITZ_SLIDING", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[RESULT_SKILL_BLITZ_SLIDING].SetSoundID( SOUNDID_NULL);
 	(*g_pActionInfoTable)[RESULT_SKILL_BLITZ_SLIDING].Init( 2 );
 	(*g_pActionInfoTable)[RESULT_SKILL_BLITZ_SLIDING][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
 	(*g_pActionInfoTable)[RESULT_SKILL_BLITZ_SLIDING][0].EffectSpriteType = EFFECTSPRITETYPE_BLITZ_SLIDING_DROP;
 	(*g_pActionInfoTable)[RESULT_SKILL_BLITZ_SLIDING][0].Step				= 25;
 	(*g_pActionInfoTable)[RESULT_SKILL_BLITZ_SLIDING][0].Count				= FrameSize[EFFECTSPRITETYPE_BLITZ_SLIDING_DROP];
 	(*g_pActionInfoTable)[RESULT_SKILL_BLITZ_SLIDING][0].SoundID			= SOUND_SLAYER_BLITZ_SLIDING;
 	(*g_pActionInfoTable)[RESULT_SKILL_BLITZ_SLIDING][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
 	(*g_pActionInfoTable)[RESULT_SKILL_BLITZ_SLIDING][1].EffectSpriteType = EFFECTSPRITETYPE_BLITZ_SLIDING_BOMB;
 	(*g_pActionInfoTable)[RESULT_SKILL_BLITZ_SLIDING][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_BLITZ_SLIDING][1].Count				= FrameSize[EFFECTSPRITETYPE_BLITZ_SLIDING_BOMB];
 	(*g_pActionInfoTable)[RESULT_SKILL_BLITZ_SLIDING][1].SoundID			= SOUNDID_NULL;

	(*g_pActionInfoTable)[SKILL_BLAZE_WALK].Set("SKILL_BLAZE_WALK", ACTION_SLAYER_BLADE_2_FAST, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER );
	(*g_pActionInfoTable)[SKILL_BLAZE_WALK].SetSoundID( SOUNDID_NULL );
	
	(*g_pActionInfoTable)[RESULT_SKILL_BLAZE_WALK].Set("RESULT_SKILL_BLAZE_WALK", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER );
	(*g_pActionInfoTable)[RESULT_SKILL_BLAZE_WALK].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[SKILL_JABBING_VEIN].Set("SKILL_JABBING_VEIN", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_GUN_SR_MALE, 5, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[SKILL_JABBING_VEIN].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_JABBING_VEIN].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_JABBING_VEIN].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_JABBING_VEIN].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_JABBING_VEIN].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_JABBING_VEIN].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_JABBING_VEIN].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_JABBING_VEIN].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용	
	(*g_pActionInfoTable)[SKILL_JABBING_VEIN].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_JABBING_VEIN].SetCastingStartFrameAll( 14 );	// 불꽃이 붙는 frame
	(*g_pActionInfoTable)[SKILL_JABBING_VEIN].SetCastingFramesAll( 2 );
	(*g_pActionInfoTable)[SKILL_JABBING_VEIN].UseRepeatFrame();	

	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN].Set("RESULT_SKILL_JABBING_VEIN", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN].SetSoundID(SOUND_SLAYER_JABBING_VEIN_NEW)  ;// SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN].Init( 8 );
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][0].EffectSpriteType = EFFECTSPRITETYPE_JABBING_VEIN_FRONT_1;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][0].Step			 = 25;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][0].LinkCount		 = 3;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][0].Count			= FrameSize[EFFECTSPRITETYPE_JABBING_VEIN_FRONT_1];
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][0].SoundID			= SOUNDID_NULL;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][1].EffectSpriteType = EFFECTSPRITETYPE_JABBING_VEIN_REAR_1;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][1].Step			 =25;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][1].Count			= FrameSize[EFFECTSPRITETYPE_JABBING_VEIN_REAR_1];
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][1].SoundID			= SOUNDID_NULL;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][1].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][2].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][2].EffectSpriteType = EFFECTSPRITETYPE_JABBING_VEIN_FRONT_2;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][2].Step			 = 1;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][2].Count			= FrameSize[EFFECTSPRITETYPE_JABBING_VEIN_FRONT_2];
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][2].SoundID			= SOUNDID_NULL;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][2].LinkCount		= 3;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][3].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][3].EffectSpriteType = EFFECTSPRITETYPE_JABBING_VEIN_REAR_2;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][3].Step			 =25;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][3].Count			= FrameSize[EFFECTSPRITETYPE_JABBING_VEIN_REAR_2];
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][3].SoundID			= SOUNDID_NULL;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][3].LinkCount		= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][4].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][4].EffectSpriteType = EFFECTSPRITETYPE_JABBING_VEIN_FRONT_3;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][4].Step			 = 1;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][4].Count			= FrameSize[EFFECTSPRITETYPE_JABBING_VEIN_FRONT_3];
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][4].SoundID			= SOUNDID_NULL;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][4].LinkCount		= 3;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][5].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][5].EffectSpriteType = EFFECTSPRITETYPE_JABBING_VEIN_REAR_3;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][5].Step			 =25;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][5].Count			= FrameSize[EFFECTSPRITETYPE_JABBING_VEIN_REAR_3];
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][5].SoundID			= SOUNDID_NULL;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][5].LinkCount		= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][6].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][6].EffectSpriteType = EFFECTSPRITETYPE_JABBING_VEIN_FRONT_4;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][6].Step			 = 1;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][6].Count			= FrameSize[EFFECTSPRITETYPE_JABBING_VEIN_FRONT_4];
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][6].SoundID			= SOUNDID_NULL;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][6].LinkCount		= 3;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][7].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][7].EffectSpriteType = EFFECTSPRITETYPE_JABBING_VEIN_REAR_4;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][7].Step			 =25;
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][7].Count			= FrameSize[EFFECTSPRITETYPE_JABBING_VEIN_REAR_4];
	(*g_pActionInfoTable)[RESULT_SKILL_JABBING_VEIN][7].SoundID			= SOUNDID_NULL;
	
	(*g_pActionInfoTable)[SKILL_GREAT_HEAL].Set("SKILL_GREAT_HEAL", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_GREAT_HEAL].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[SKILL_GREAT_HEAL].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[SKILL_GREAT_HEAL].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[SKILL_GREAT_HEAL].SetStartFrameAll( 8 );
	(*g_pActionInfoTable)[SKILL_GREAT_HEAL].SetSoundID( SOUNDID_NULL );		
	
	(*g_pActionInfoTable)[RESULT_SKILL_GREAT_HEAL].Set("RESULT_SKILL_GREAT_HEAL", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_GREAT_HEAL].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_GREAT_HEAL].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SKILL_GREAT_HEAL][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_GREAT_HEAL][0].EffectSpriteType	= EFFECTSPRITETYPE_GREAT_HEAL;
	(*g_pActionInfoTable)[RESULT_SKILL_GREAT_HEAL][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_GREAT_HEAL][0].Count				= FrameSize[EFFECTSPRITETYPE_GREAT_HEAL];	
	(*g_pActionInfoTable)[RESULT_SKILL_GREAT_HEAL][0].SoundID			= SOUND_SLAYER_GREAT_HEAL;;
	
	(*g_pActionInfoTable)[SKILL_DIVINE_GUIDANCE].Set("SKILL_DIVINE_GUIDANCE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER );
	(*g_pActionInfoTable)[SKILL_DIVINE_GUIDANCE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_DIVINE_GUIDANCE].SetEffectStatus( EFFECTSTATUS_DIVINE_GUIDANCE );

	(*g_pActionInfoTable)[RESULT_SKILL_DIVINE_GUIDANCE].Set("RESULT_SKILL_DIVINE_GUIDANCE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER );
	(*g_pActionInfoTable)[RESULT_SKILL_DIVINE_GUIDANCE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_DIVINE_GUIDANCE].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_DIVINE_GUIDANCE].Init( 3 );
	(*g_pActionInfoTable)[RESULT_SKILL_DIVINE_GUIDANCE][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_DIVINE_GUIDANCE][0].EffectSpriteType = EFFECTSPRITETYPE_DIVINE_GUIDANCE_START;
	(*g_pActionInfoTable)[RESULT_SKILL_DIVINE_GUIDANCE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_DIVINE_GUIDANCE][0].Count			= FrameSize[ EFFECTSPRITETYPE_DIVINE_GUIDANCE_START];
	(*g_pActionInfoTable)[RESULT_SKILL_DIVINE_GUIDANCE][0].SoundID			= SOUND_SLAYER_DIVINE_GUIDANCE;
	(*g_pActionInfoTable)[RESULT_SKILL_DIVINE_GUIDANCE][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_DIVINE_GUIDANCE][1].EffectSpriteType = EFFECTSPRITETYPE_DIVINE_GUIDANCE_ING;
	(*g_pActionInfoTable)[RESULT_SKILL_DIVINE_GUIDANCE][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_DIVINE_GUIDANCE][1].Count			= FrameSize [EFFECTSPRITETYPE_DIVINE_GUIDANCE_ING];
	(*g_pActionInfoTable)[RESULT_SKILL_DIVINE_GUIDANCE][1].SoundID			= SOUNDID_NULL;
	(*g_pActionInfoTable)[RESULT_SKILL_DIVINE_GUIDANCE][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_SKILL_DIVINE_GUIDANCE][2].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_DIVINE_GUIDANCE][2].EffectSpriteType = EFFECTSPRITETYPE_DIVINE_GUIDANCE_END;
	(*g_pActionInfoTable)[RESULT_SKILL_DIVINE_GUIDANCE][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_DIVINE_GUIDANCE][2].Count			= FrameSize[ EFFECTSPRITETYPE_DIVINE_GUIDANCE_END];
	(*g_pActionInfoTable)[RESULT_SKILL_DIVINE_GUIDANCE][2].SoundID			= SOUNDID_NULL;
	
	(*g_pActionInfoTable)[SKILL_BLITZ_SLIDING_ATTACK].Set("SKILL_BLITZ_SLIDING", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER );
	(*g_pActionInfoTable)[SKILL_BLITZ_SLIDING_ATTACK].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_BLITZ_SLIDING_ATTACK].SetStartFrameAll( 0 );	// 기술 effect가 시작되는 frame
	(*g_pActionInfoTable)[SKILL_BLITZ_SLIDING_ATTACK].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_BLITZ_SLIDING_ATTACK].Init( 1 );
	(*g_pActionInfoTable)[SKILL_BLITZ_SLIDING_ATTACK][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_BLITZ_SLIDING_ATTACK][0].EffectSpriteType = EFFECTSPRITETYPE_NEW_BLITZ_SLIDING_SWORD_MALE;
	(*g_pActionInfoTable)[SKILL_BLITZ_SLIDING_ATTACK][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_BLITZ_SLIDING_ATTACK][0].Count			= FrameSize[EFFECTSPRITETYPE_NEW_BLITZ_SLIDING_SWORD_MALE];
	(*g_pActionInfoTable)[SKILL_BLITZ_SLIDING_ATTACK][0].SoundID			= SOUND_SLAYER_SWORD_THUNDERBOLTA;

	(*g_pActionInfoTable)[RESULT_SKILL_BLITZ_SLIDING_ATTACK].Set("RESULT_SKILL_BLITZ_SLIDING_ATTACK", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER );
	(*g_pActionInfoTable)[RESULT_SKILL_BLITZ_SLIDING_ATTACK].SetSoundID( SOUNDID_NULL );
	
	(*g_pActionInfoTable)[SKILL_BLAZE_WALK_ATTACK].Set("SKILL_BLAZE_WALK", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER );
	(*g_pActionInfoTable)[SKILL_BLAZE_WALK_ATTACK].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_BLAZE_WALK_ATTACK].SetStartFrameAll( 0 );	// 기술 effect가 시작되는 frame
	(*g_pActionInfoTable)[SKILL_BLAZE_WALK_ATTACK].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_BLAZE_WALK_ATTACK].Init( 1 );
	(*g_pActionInfoTable)[SKILL_BLAZE_WALK_ATTACK][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_BLAZE_WALK_ATTACK][0].EffectSpriteType = EFFECTSPRITETYPE_NEW_BLAZE_WALK_MALE;
	(*g_pActionInfoTable)[SKILL_BLAZE_WALK_ATTACK][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_BLAZE_WALK_ATTACK][0].Count			= FrameSize[EFFECTSPRITETYPE_NEW_BLAZE_WALK_MALE];
	(*g_pActionInfoTable)[SKILL_BLAZE_WALK_ATTACK][0].SoundID			= SOUND_SLAYER_BLAZE_WALK;

	(*g_pActionInfoTable)[RESULT_SKILL_BLAZE_WALK_ATTACK].Set("RESULT_SKILL_BLAZE_WALK_ATTACK", ACTION_SLAYER_BLADE_2_FAST, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER );
	(*g_pActionInfoTable)[RESULT_SKILL_BLAZE_WALK_ATTACK].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[SKILL_REDIANCE].Set("SKILL_REDIANCE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF );	
	(*g_pActionInfoTable)[SKILL_REDIANCE].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_REDIANCE].Set("RESULT_SKILL_REDIANCE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER );		
	(*g_pActionInfoTable)[RESULT_SKILL_REDIANCE].SetSoundID( SOUNDID_NULL );
	
	(*g_pActionInfoTable)[SKILL_HEART_CATALYST].Set("SKILL_HEART_CATALYST", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF );	
	(*g_pActionInfoTable)[SKILL_HEART_CATALYST].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_HEART_CATALYST].Set("RESULT_SKILL_HEART_CATALYST", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER );	
	(*g_pActionInfoTable)[RESULT_SKILL_HEART_CATALYST].SetSoundID( SOUND_SLAYER_HEART_CATALYST) ; //SOUNDID_NULL );
	
	(*g_pActionInfoTable)[SKILL_ATTACK_MELEE_REDIANCE].Set("SKILL_ATTACK_MELEE_RELIDANCE", ACTION_SLAYER_SWORD, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_VAMPIRE_ATTACK_FAST]);
	(*g_pActionInfoTable)[SKILL_ATTACK_MELEE_REDIANCE].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[SKILL_ATTACK_MELEE_REDIANCE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_ATTACK_MELEE_REDIANCE].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_ATTACK_MELEE_REDIANCE].Init( 1 );
	(*g_pActionInfoTable)[SKILL_ATTACK_MELEE_REDIANCE][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_ATTACK_MELEE_REDIANCE][0].EffectSpriteType = EFFECTSPRITETYPE_NEW_REDIANCE_MALE_NORMAL_ATTACK_NORMAL;
	(*g_pActionInfoTable)[SKILL_ATTACK_MELEE_REDIANCE][0].Step = 25;
	(*g_pActionInfoTable)[SKILL_ATTACK_MELEE_REDIANCE][0].Count = FrameSize[EFFECTSPRITETYPE_NEW_REDIANCE_MALE_NORMAL_ATTACK_NORMAL];
	(*g_pActionInfoTable)[SKILL_ATTACK_MELEE_REDIANCE][0].SoundID = SOUNDID_NULL;	

	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_MELEE_REDIANCE].Set("RESULT_SKILL_ATTACK_MELEE_RELIDANCE", ACTION_DAMAGED, EFFECTSPRITETYPE_BLOOD, 0, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 80);
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_MELEE_REDIANCE].SetSoundID( SOUND_DAMAGE_GUN );
	(*g_pActionInfoTable)[RESULT_SKILL_ATTACK_MELEE_REDIANCE].SetCastingFramesAll( 6 );	

	(*g_pActionInfoTable)[SKILL_LARSLASH].Set("SKILL_LARSLASH", ACTION_SLAYER_SWORD_2_REPEAT, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD_2]);
	(*g_pActionInfoTable)[SKILL_LARSLASH].SetCastingEffectToOther();	// casting effect를 다른 사람에게 붙인다.
	(*g_pActionInfoTable)[SKILL_LARSLASH].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_LARSLASH].SetSoundID( SOUND_SLAYER_SWORD_LARSLASH) ; //SOUND_SLAYER_SWORD_LH );
	(*g_pActionInfoTable)[SKILL_LARSLASH].SetCastingStartFrameAll( 5 );	// 불꽃이 붙는 frame
	(*g_pActionInfoTable)[SKILL_LARSLASH].UseRepeatFrame();	
	(*g_pActionInfoTable)[SKILL_LARSLASH].SetStartFrame( 0, 18 );			// slow
	(*g_pActionInfoTable)[SKILL_LARSLASH].SetStartFrame( 1, 18 );			// normal
	(*g_pActionInfoTable)[SKILL_LARSLASH].SetStartFrame( 2, 18 );			// fast
	(*g_pActionInfoTable)[SKILL_LARSLASH].SetCastingStartFrame( 0, 7 );		// slow
	(*g_pActionInfoTable)[SKILL_LARSLASH].SetCastingStartFrame( 1, 7 );		// normal
	(*g_pActionInfoTable)[SKILL_LARSLASH].SetCastingStartFrame( 2, 7 );		// fast
	(*g_pActionInfoTable)[SKILL_LARSLASH].SetCastingFrames( 0, 10 );		// slow
	(*g_pActionInfoTable)[SKILL_LARSLASH].SetCastingFrames( 1, 10 );		// normal
	(*g_pActionInfoTable)[SKILL_LARSLASH].SetCastingFrames( 2, 10 );		// fast
	(*g_pActionInfoTable)[SKILL_LARSLASH].SetRepeatFrame( 0, 7, 11 );		// slow
	(*g_pActionInfoTable)[SKILL_LARSLASH].SetRepeatFrame( 1, 7, 11 );		// normal
	(*g_pActionInfoTable)[SKILL_LARSLASH].SetRepeatFrame( 2, 7, 11 );		// fast
	(*g_pActionInfoTable)[SKILL_LARSLASH].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_LARSLASH].SetActionStepCnt(2) ; 
  	(*g_pActionInfoTable)[SKILL_LARSLASH].Init( 1 );		
  	(*g_pActionInfoTable)[SKILL_LARSLASH][0].EffectGeneratorID		= EFFECTGENERATORID_ATTACH_CREATURE;
  	(*g_pActionInfoTable)[SKILL_LARSLASH][0].EffectSpriteType		= EFFECTSPRITETYPE_NEW_LAR_SLASH_MALE_NORMAL;
  	(*g_pActionInfoTable)[SKILL_LARSLASH][0].Step					= 25;
  	(*g_pActionInfoTable)[SKILL_LARSLASH][0].Count					= FrameSize[EFFECTSPRITETYPE_NEW_LAR_SLASH_MALE_NORMAL];
  	(*g_pActionInfoTable)[SKILL_LARSLASH][0].SetResultTime();

	/*
	(*g_pActionInfoTable)[SKILL_LARSLASH].Set("SKILL_LARSLASH", ACTION_SLAYER_SWORD_2, EFFECTSPRITETYPE_LAR_SLASH_MALE_NORMAL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD_2]);
		(*g_pActionInfoTable)[SKILL_LARSLASH].SetCastingEffectToOther();	// casting effect를 다른 사람에게 붙인다.
		(*g_pActionInfoTable)[SKILL_LARSLASH].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );	
		(*g_pActionInfoTable)[SKILL_LARSLASH].SetSoundID( SOUND_SLAYER_SWORD_LARSLASH) ; //SOUND_SLAYER_SWORD_LH );
		(*g_pActionInfoTable)[SKILL_LARSLASH].UseRepeatFrame();		
		(*g_pActionInfoTable)[SKILL_LARSLASH].SetStartFrame( 0, 18 );			// slow
		(*g_pActionInfoTable)[SKILL_LARSLASH].SetStartFrame( 1, 18 );			// normal
		(*g_pActionInfoTable)[SKILL_LARSLASH].SetStartFrame( 2, 18 );			// fast
		(*g_pActionInfoTable)[SKILL_LARSLASH].SetCastingStartFrame( 0, 7 );	// slow
		(*g_pActionInfoTable)[SKILL_LARSLASH].SetCastingStartFrame( 1, 7 );	// normal
		(*g_pActionInfoTable)[SKILL_LARSLASH].SetCastingStartFrame( 2, 7 );	// fast
		(*g_pActionInfoTable)[SKILL_LARSLASH].SetCastingFrames( 0, 10 );		// slow
		(*g_pActionInfoTable)[SKILL_LARSLASH].SetCastingFrames( 1, 10 );		// normal
		(*g_pActionInfoTable)[SKILL_LARSLASH].SetCastingFrames( 2, 10 );		// fast
		(*g_pActionInfoTable)[SKILL_LARSLASH].SetRepeatFrame( 0, 7, 11 );		// slow
		(*g_pActionInfoTable)[SKILL_LARSLASH].SetRepeatFrame( 1, 7, 11 );		// normal
		(*g_pActionInfoTable)[SKILL_LARSLASH].SetRepeatFrame( 2, 7, 11 );		// fast
	//	(*g_pActionInfoTable)[SKILL_LARSLASH].SetStartFrame( 0, 0 );			// slow
	//	(*g_pActionInfoTable)[SKILL_LARSLASH].SetStartFrame( 1, 0 );			// normal
	//	(*g_pActionInfoTable)[SKILL_LARSLASH].SetStartFrame( 2, 0 );			// fast
	//	(*g_pActionInfoTable)[SKILL_LARSLASH].SetCastingStartFrame( 0, 7 );	// slow
	//	(*g_pActionInfoTable)[SKILL_LARSLASH].SetCastingStartFrame( 1, 7 );	// normal
	//	(*g_pActionInfoTable)[SKILL_LARSLASH].SetCastingStartFrame( 2, 7 );	// fast
	//	(*g_pActionInfoTable)[SKILL_LARSLASH].SetCastingFrames( 0, 10 );		// slow
	//	(*g_pActionInfoTable)[SKILL_LARSLASH].SetCastingFrames( 1, 10 );		// normal
	//	(*g_pActionInfoTable)[SKILL_LARSLASH].SetCastingFrames( 2, 10 );		// fast
	//	(*g_pActionInfoTable)[SKILL_LARSLASH].SetRepeatFrame( 0, 7, 11 );		// slow
	//	(*g_pActionInfoTable)[SKILL_LARSLASH].SetRepeatFrame( 1, 7, 11 );		// normal
	//	(*g_pActionInfoTable)[SKILL_LARSLASH].SetRepeatFrame( 2, 7, 11 );		// fast	
		(*g_pActionInfoTable)[SKILL_LARSLASH].SetAttachSelf();
		(*g_pActionInfoTable)[SKILL_LARSLASH].SetCastingStartFrameAll( 0 );	// 불꽃이 붙는 frame
		(*g_pActionInfoTable)[SKILL_LARSLASH].Init( 1 );
		(*g_pActionInfoTable)[SKILL_LARSLASH][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
		(*g_pActionInfoTable)[SKILL_LARSLASH][0].EffectSpriteType	= EFFECTSPRITETYPE_LAR_SLASH_MALE_NORMAL;
		(*g_pActionInfoTable)[SKILL_LARSLASH][0].Step				= 25;
		//(*g_pActionInfoTable)[SKILL_LARSLASH][0].Count				= FrameSize[EFFECTSPRITETYPE_LAR_SLASH_MALE_NORMAL]+10;	
		(*g_pActionInfoTable)[SKILL_LARSLASH][0].Count				= FrameSize[EFFECTSPRITETYPE_LIGHTNING_HANDS_3];
		(*g_pActionInfoTable)[SKILL_LARSLASH][0].SetResultTime();	*/
	

	(*g_pActionInfoTable)[RESULT_SKILL_LARSLASH].Set("RESULT_SKILL_LARSLASH", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_LARSLASH].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_LARSLASH].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_LARSLASH][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_LARSLASH][0].EffectSpriteType = EFFECTSPRITETYPE_EARTHS_TEETH_DAMAGED;
	(*g_pActionInfoTable)[RESULT_SKILL_LARSLASH][0].Step			= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_LARSLASH][0].Count			= FrameSize[ EFFECTSPRITETYPE_EARTHS_TEETH_DAMAGED ];

	
	// SKILL_QUICK_FIRE
	(*g_pActionInfoTable)[SKILL_TRIDENT].Set("SKILL_TRIDENT", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_GUN_SR_MALE, 5, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[SKILL_TRIDENT].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_TRIDENT].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_TRIDENT].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_TRIDENT].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_TRIDENT].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_TRIDENT].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_TRIDENT].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_TRIDENT].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용	
	(*g_pActionInfoTable)[SKILL_TRIDENT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_TRIDENT].SetCastingStartFrameAll( 14 );	// 불꽃이 붙는 frame
	(*g_pActionInfoTable)[SKILL_TRIDENT].SetCastingFramesAll( 2 );
	(*g_pActionInfoTable)[SKILL_TRIDENT].UseRepeatFrame();	
	
	(*g_pActionInfoTable)[RESULT_SKILL_TRIDENT].Set("RESULT_SKILL_TRIDENT", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_TRIDENT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_TRIDENT].Init( 2);
	(*g_pActionInfoTable)[RESULT_SKILL_TRIDENT][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIDENT][0].EffectSpriteType = EFFECTSPRITETYPE_TRIDENT_BOMB_1;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIDENT][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIDENT][0].Count				= FrameSize[EFFECTSPRITETYPE_TRIDENT_BOMB_1];
	(*g_pActionInfoTable)[RESULT_SKILL_TRIDENT][0].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIDENT][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIDENT][1].EffectSpriteType = EFFECTSPRITETYPE_TRIDENT_BOMB_1;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIDENT][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_TRIDENT][1].Count				= FrameSize[EFFECTSPRITETYPE_TRIDENT_BOMB_1];
	(*g_pActionInfoTable)[RESULT_SKILL_TRIDENT][1].LinkCount			= 1;
	
	// SKILL_MOLE_SHOT
	(*g_pActionInfoTable)[SKILL_MOLE_SHOT].Set("SKILL_MOLE_SHOT", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_GUN_SR_MALE, 5, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_MOLE_SHOT].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_MOLE_SHOT].SetStartFrame( 0, 7 );			// slow
	(*g_pActionInfoTable)[SKILL_MOLE_SHOT].SetStartFrame( 1, 7 );			// normal
	(*g_pActionInfoTable)[SKILL_MOLE_SHOT].SetStartFrame( 2, 5 );			// fast
	(*g_pActionInfoTable)[SKILL_MOLE_SHOT].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_MOLE_SHOT].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_MOLE_SHOT].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_MOLE_SHOT].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_MOLE_SHOT].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_MOLE_SHOT].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_MOLE_SHOT].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용	
	(*g_pActionInfoTable)[SKILL_MOLE_SHOT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_MOLE_SHOT].SetCastingStartFrameAll( 14 );	// 불꽃이 붙는 frame
	(*g_pActionInfoTable)[SKILL_MOLE_SHOT].SetCastingFramesAll( 2 );
	(*g_pActionInfoTable)[SKILL_MOLE_SHOT].UseRepeatFrame();	
	//(*g_pActionInfoTable)[SKILL_MOLE_SHOT].SetRepeatLimit( 4 );
	(*g_pActionInfoTable)[SKILL_MOLE_SHOT].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_MOLE_SHOT );	// 맞는 결과를 표현한다.	
	(*g_pActionInfoTable)[SKILL_MOLE_SHOT].Init( 1 );
	(*g_pActionInfoTable)[SKILL_MOLE_SHOT][0].EffectGeneratorID	= EFFECTGENERATORID_AROUND_ZONE;
	(*g_pActionInfoTable)[SKILL_MOLE_SHOT][0].EffectSpriteType		= EFFECTSPRITETYPE_MOLE_SHOT_1;
	(*g_pActionInfoTable)[SKILL_MOLE_SHOT][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_MOLE_SHOT][0].Count				= FrameSize[EFFECTSPRITETYPE_MOLE_SHOT_1];

	(*g_pActionInfoTable)[RESULT_SKILL_MOLE_SHOT].Set("RESULT_SKILL_MOLE_SHOT", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_MOLE_SHOT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_MOLE_SHOT].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_MOLE_SHOT][0].EffectGeneratorID	= EFFECTGENERATORID_AROUND_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_MOLE_SHOT][0].EffectSpriteType		= EFFECTSPRITETYPE_MOLE_SHOT_1;
	(*g_pActionInfoTable)[RESULT_SKILL_MOLE_SHOT][0].Step					= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_MOLE_SHOT][0].Count				= FrameSize[EFFECTSPRITETYPE_MOLE_SHOT_1];

	(*g_pActionInfoTable)[HOLY_LAND_WARP_OUSTERS].Set("HOLY_LAND_WARP_OUSTERS",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[HOLY_LAND_WARP_OUSTERS].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[HOLY_LAND_WARP_OUSTERS].Init( 1 );
	(*g_pActionInfoTable)[HOLY_LAND_WARP_OUSTERS][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[HOLY_LAND_WARP_OUSTERS][0].EffectSpriteType = EFFECTSPRITETYPE_OUSTERS_PORTAL_HOLY_LAND;
	(*g_pActionInfoTable)[HOLY_LAND_WARP_OUSTERS][0].Step						= 30;
	(*g_pActionInfoTable)[HOLY_LAND_WARP_OUSTERS][0].Count					= FrameSize[EFFECTSPRITETYPE_OUSTERS_PORTAL_HOLY_LAND];

	(*g_pActionInfoTable)[SKILL_PROTECTION_FROM_BLOOD].Set("SKILL_PROTECTION_FROM_BLOOD", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_PROTECTION_FROM_BLOOD].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[SKILL_PROTECTION_FROM_BLOOD].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[SKILL_PROTECTION_FROM_BLOOD].SetStartFrameAll( 7 );
	(*g_pActionInfoTable)[SKILL_PROTECTION_FROM_BLOOD].SetSoundID( SOUNDID_NULL );		

	(*g_pActionInfoTable)[RESULT_SKILL_PROTECTION_FROM_BLOOD].Set("RESULT_SKILL_PROTECTION_FROM_BLOOD", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_PROTECTION_FROM_BLOOD].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_PROTECTION_FROM_BLOOD].Init( 2 );
	(*g_pActionInfoTable)[RESULT_SKILL_PROTECTION_FROM_BLOOD][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_PROTECTION_FROM_BLOOD][0].EffectSpriteType	= EFFECTSPRITETYPE_PROTECTION_FROM_BLOOD_BACK;
	(*g_pActionInfoTable)[RESULT_SKILL_PROTECTION_FROM_BLOOD][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_PROTECTION_FROM_BLOOD][0].Count				= FrameSize[EFFECTSPRITETYPE_PROTECTION_FROM_BLOOD_BACK];
	(*g_pActionInfoTable)[RESULT_SKILL_PROTECTION_FROM_BLOOD][0].SoundID			= SOUND_SLAYER_HEALING_PFP;
	(*g_pActionInfoTable)[RESULT_SKILL_PROTECTION_FROM_BLOOD][0].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_PROTECTION_FROM_BLOOD][1].EffectGeneratorID  = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_PROTECTION_FROM_BLOOD][1].EffectSpriteType   = EFFECTSPRITETYPE_PROTECTION_FROM_BLOOD_FRONT;
	(*g_pActionInfoTable)[RESULT_SKILL_PROTECTION_FROM_BLOOD][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_PROTECTION_FROM_BLOOD][1].Count				= FrameSize[EFFECTSPRITETYPE_PROTECTION_FROM_BLOOD_FRONT];

	(*g_pActionInfoTable)[SKILL_ETERNITY].Set("SKILL_ETERNITY", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF );
	(*g_pActionInfoTable)[SKILL_ETERNITY].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[SKILL_ETERNITY].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_ETERNITY].Set("RESULT_SKILL_ETERNITY", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_ETERNITY].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_ETERNITY].SetSoundID( SOUND_SLAYER_ETERNITY) ; //SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_ETERNITY].Init( 3 );
	(*g_pActionInfoTable)[RESULT_SKILL_ETERNITY].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_ETERNITY][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_ETERNITY][0].EffectSpriteType	= EFFECTSPRITETYPE_RESTORE_1;
	(*g_pActionInfoTable)[RESULT_SKILL_ETERNITY][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ETERNITY][0].Count				= FrameSize[EFFECTSPRITETYPE_RESTORE_1];
//  (*g_pActionInfoTable)[RESULT_SKILL_ETERNITY][0].SoundID			= SOUND_SLAYER_HEALING_R1;
	(*g_pActionInfoTable)[RESULT_SKILL_ETERNITY][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_ETERNITY][1].EffectSpriteType	= EFFECTSPRITETYPE_RESTORE_2;
	(*g_pActionInfoTable)[RESULT_SKILL_ETERNITY][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ETERNITY][1].Count				= FrameSize[EFFECTSPRITETYPE_RESTORE_2];
	(*g_pActionInfoTable)[RESULT_SKILL_ETERNITY][1].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_SKILL_ETERNITY][1].SetResultTime();
	(*g_pActionInfoTable)[RESULT_SKILL_ETERNITY][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_ETERNITY][2].EffectSpriteType	= EFFECTSPRITETYPE_RESTORE_3;
	(*g_pActionInfoTable)[RESULT_SKILL_ETERNITY][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ETERNITY][2].Count				= FrameSize[EFFECTSPRITETYPE_RESTORE_3];
//(*g_pActionInfoTable)[RESULT_SKILL_ETERNITY][2].SoundID			= SOUND_SLAYER_HEALING_R2;

	(*g_pActionInfoTable)[ETERNITY].Set("ETERNITY",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[ETERNITY].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[ETERNITY].Init( 2 );
	(*g_pActionInfoTable)[ETERNITY][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[ETERNITY][0].EffectSpriteType = EFFECTSPRITETYPE_ETERNITY;
	(*g_pActionInfoTable)[ETERNITY][0].Step						= 30;
	(*g_pActionInfoTable)[ETERNITY][0].Count					= FrameSize[EFFECTSPRITETYPE_ETERNITY];
	(*g_pActionInfoTable)[ETERNITY][0].LinkCount				= 0;
	(*g_pActionInfoTable)[ETERNITY][1].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[ETERNITY][1].EffectSpriteType = EFFECTSPRITETYPE_ETERNITY_GROUND;
	(*g_pActionInfoTable)[ETERNITY][1].Step						= 30;
	(*g_pActionInfoTable)[ETERNITY][1].Count					= FrameSize[EFFECTSPRITETYPE_ETERNITY_GROUND];
	(*g_pActionInfoTable)[ETERNITY][1].SetDelayNode();

	(*g_pActionInfoTable)[SKILL_INSTALL_TRAP].Set("SKILL_INSTALL_TRAP", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC] );
	(*g_pActionInfoTable)[SKILL_INSTALL_TRAP].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_INSTALL_TRAP].Set("RESULT_SKILL_INSTALL_TRAP", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC] );
	(*g_pActionInfoTable)[RESULT_SKILL_INSTALL_TRAP].SetSoundID( SOUND_SLAYER_INSTALL_TRAP) ; //SOUNDID_NULL );

	(*g_pActionInfoTable)[SKILL_CREATE_HOLY_POTION].Set("SKILL_CREATE_HOLY_POTION", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ITEM | FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_CREATE_HOLY_POTION].SetSoundID( SOUND_SLAYER_CREATE_HOLY_POTION) ;//SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CREATE_HOLY_POTION].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[SKILL_CREATE_HOLY_POTION].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[SKILL_CREATE_HOLY_POTION].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_CREATE_HOLY_POTION].SetSoundID( SOUNDID_NULL );		
	(*g_pActionInfoTable)[SKILL_CREATE_HOLY_POTION].Init( 2 );
	(*g_pActionInfoTable)[SKILL_CREATE_HOLY_POTION][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_INVENTORY;
	(*g_pActionInfoTable)[SKILL_CREATE_HOLY_POTION][0].EffectSpriteType	= EFFECTSPRITETYPE_HOLY_POTION_START;
	(*g_pActionInfoTable)[SKILL_CREATE_HOLY_POTION][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CREATE_HOLY_POTION][0].Count				= FrameSize[EFFECTSPRITETYPE_HOLY_POTION_START];
	(*g_pActionInfoTable)[SKILL_CREATE_HOLY_POTION][0].SoundID			= SOUND_SLAYER_ENCHANT_CHW1;
	(*g_pActionInfoTable)[SKILL_CREATE_HOLY_POTION][1].EffectGeneratorID	= EFFECTSPRITETYPE_HOLY_POTION_ING;	// 반복
	(*g_pActionInfoTable)[SKILL_CREATE_HOLY_POTION][1].EffectSpriteType	= EFFECTSPRITETYPE_CREATE_HOLY_WATER_2;
	(*g_pActionInfoTable)[SKILL_CREATE_HOLY_POTION][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CREATE_HOLY_POTION][1].Count				= FrameSize[EFFECTSPRITETYPE_HOLY_POTION_ING];

	(*g_pActionInfoTable)[RESULT_SKILL_CREATE_HOLY_POTION].Set("RESULT_SKILL_CREATE_HOLY_POTION", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ITEM | FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[RESULT_SKILL_CREATE_HOLY_POTION].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_CREATE_HOLY_POTION].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_CREATE_HOLY_POTION].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_CREATE_HOLY_POTION].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_CREATE_HOLY_POTION][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_INVENTORY;
	(*g_pActionInfoTable)[RESULT_SKILL_CREATE_HOLY_POTION][0].EffectSpriteType	= EFFECTSPRITETYPE_HOLY_POTION_END;
	(*g_pActionInfoTable)[RESULT_SKILL_CREATE_HOLY_POTION][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_CREATE_HOLY_POTION][0].Count				= FrameSize[EFFECTSPRITETYPE_HOLY_POTION_END];
	(*g_pActionInfoTable)[RESULT_SKILL_CREATE_HOLY_POTION][0].SoundID			= SOUND_SLAYER_ENCHANT_CHW2;

	(*g_pActionInfoTable)[SKILL_MERCY_GROUND].Set("SKILL_MERCY_GROUND", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_MERCY_GROUND].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_MERCY_GROUND].SetSoundID( SOUNDID_NULL );	

	(*g_pActionInfoTable)[RESULT_SKILL_MERCY_GROUND].Set("RESULT_SKILL_MERCY_GROUND", ACTION_STAND, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[RESULT_SKILL_MERCY_GROUND].SetSoundID(SOUND_SLAYER_MERCY_GROUND) ;// SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_MERCY_GROUND].Init( 2 );
	(*g_pActionInfoTable)[RESULT_SKILL_MERCY_GROUND].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_MERCY_GROUND][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_MERCY_GROUND][0].EffectSpriteType = EFFECTSPRITETYPE_MERCY_GROUND_START;
	(*g_pActionInfoTable)[RESULT_SKILL_MERCY_GROUND][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_MERCY_GROUND][0].Count				= FrameSize[EFFECTSPRITETYPE_MERCY_GROUND_START];
	(*g_pActionInfoTable)[RESULT_SKILL_MERCY_GROUND][0].LinkCount			= 5;
	(*g_pActionInfoTable)[RESULT_SKILL_MERCY_GROUND][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_MERCY_GROUND][1].EffectSpriteType = EFFECTSPRITETYPE_MERCY_GROUND_1;
	(*g_pActionInfoTable)[RESULT_SKILL_MERCY_GROUND][1].Step			= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_MERCY_GROUND][1].Count				= FrameSize[EFFECTSPRITETYPE_MERCY_GROUND_1];
	(*g_pActionInfoTable)[RESULT_SKILL_MERCY_GROUND][1].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_MERCY_GROUND][1].SetDelayNode();	
    
	(*g_pActionInfoTable)[SKILL_HOLY_ARMOR].Set("SKILL_INSTALL_TRAP", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC] );
	(*g_pActionInfoTable)[SKILL_HOLY_ARMOR].SetSoundID( SOUNDID_NULL );
	
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARMOR].Set("RESULT_SKILL_INSTALL_TRAP", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC] );
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARMOR].SetSoundID( SOUND_SLAYER_HOLY_ARMOR) ; // SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARMOR].Init( 3 );
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARMOR][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARMOR][0].EffectSpriteType = EFFECTSPRITETYPE_HOLY_ARMOR_A;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARMOR][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARMOR][0].Count				= FrameSize[EFFECTSPRITETYPE_HOLY_ARMOR_A];
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARMOR][0].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARMOR][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARMOR][1].EffectSpriteType = EFFECTSPRITETYPE_HOLY_ARMOR_B;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARMOR][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARMOR][1].Count				= FrameSize[EFFECTSPRITETYPE_HOLY_ARMOR_B];
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARMOR][1].LinkCount			= FrameSize[EFFECTSPRITETYPE_HOLY_ARMOR_B];
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARMOR][2].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARMOR][2].EffectSpriteType = EFFECTSPRITETYPE_HOLY_ARMOR_C;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARMOR][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_ARMOR][2].Count				= FrameSize[EFFECTSPRITETYPE_HOLY_ARMOR_C];	

	(*g_pActionInfoTable)[TRAP_INSTALLED].Set("TRAP_INSTALL", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[TRAP_INSTALLED].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[TRAP_INSTALLED].Init( 1 );
	(*g_pActionInfoTable)[TRAP_INSTALLED][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[TRAP_INSTALLED][0].EffectSpriteType = EFFECTSPRITETYPE_INSTALL_TRAP;
	(*g_pActionInfoTable)[TRAP_INSTALLED][0].Step				= 25;
	(*g_pActionInfoTable)[TRAP_INSTALLED][0].Count				= FrameSize[EFFECTSPRITETYPE_INSTALL_TRAP];
	(*g_pActionInfoTable)[TRAP_INSTALLED][0].SetDelayNode();

	(*g_pActionInfoTable)[TRAP_TRIGGERED].Set("TRAP_TRIGGERED", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC] );
	(*g_pActionInfoTable)[TRAP_TRIGGERED].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[TRAP_TRIGGERED].Init( 7 );
	(*g_pActionInfoTable)[TRAP_TRIGGERED][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[TRAP_TRIGGERED][0].EffectSpriteType = EFFECTSPRITETYPE_INSTALL_TRAP_DUST;
	(*g_pActionInfoTable)[TRAP_TRIGGERED][0].Step			= 25;
	(*g_pActionInfoTable)[TRAP_TRIGGERED][0].Count				= FrameSize[EFFECTSPRITETYPE_INSTALL_TRAP_DUST];
	(*g_pActionInfoTable)[TRAP_TRIGGERED][0].LinkCount = 0;	
	(*g_pActionInfoTable)[TRAP_TRIGGERED][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[TRAP_TRIGGERED][1].EffectSpriteType = EFFECTSPRITETYPE_INSTALL_TRAP_START_BACK;
	(*g_pActionInfoTable)[TRAP_TRIGGERED][1].Step				= 25;
	(*g_pActionInfoTable)[TRAP_TRIGGERED][1].Count				= FrameSize[EFFECTSPRITETYPE_INSTALL_TRAP_START_BACK];
	(*g_pActionInfoTable)[TRAP_TRIGGERED][1].LinkCount			= 0;
	(*g_pActionInfoTable)[TRAP_TRIGGERED][2].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[TRAP_TRIGGERED][2].EffectSpriteType = EFFECTSPRITETYPE_INSTALL_TRAP_START_FRONT;
	(*g_pActionInfoTable)[TRAP_TRIGGERED][2].Step				= 25;
	(*g_pActionInfoTable)[TRAP_TRIGGERED][2].Count				= FrameSize[EFFECTSPRITETYPE_INSTALL_TRAP_START_FRONT];
	(*g_pActionInfoTable)[TRAP_TRIGGERED][2].LinkCount			= FrameSize[EFFECTSPRITETYPE_INSTALL_TRAP_START_FRONT];
	(*g_pActionInfoTable)[TRAP_TRIGGERED][3].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[TRAP_TRIGGERED][3].EffectSpriteType = EFFECTSPRITETYPE_INSTALL_TRAP_ING_BACK;
	(*g_pActionInfoTable)[TRAP_TRIGGERED][3].Step				= 25;
	(*g_pActionInfoTable)[TRAP_TRIGGERED][3].Count				= FrameSize[EFFECTSPRITETYPE_INSTALL_TRAP_ING_BACK];
	(*g_pActionInfoTable)[TRAP_TRIGGERED][3].LinkCount			= 0;
	(*g_pActionInfoTable)[TRAP_TRIGGERED][4].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[TRAP_TRIGGERED][4].EffectSpriteType = EFFECTSPRITETYPE_INSTALL_TRAP_ING_FRONT;
	(*g_pActionInfoTable)[TRAP_TRIGGERED][4].Step				= 25;
	(*g_pActionInfoTable)[TRAP_TRIGGERED][4].Count				= FrameSize[EFFECTSPRITETYPE_INSTALL_TRAP_ING_FRONT];
	(*g_pActionInfoTable)[TRAP_TRIGGERED][4].SetDelayNode();
	(*g_pActionInfoTable)[TRAP_TRIGGERED][5].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[TRAP_TRIGGERED][5].EffectSpriteType = EFFECTSPRITETYPE_INSTALL_TRAP_END_BACK;
	(*g_pActionInfoTable)[TRAP_TRIGGERED][5].Step				= 25;
	(*g_pActionInfoTable)[TRAP_TRIGGERED][5].Count				= FrameSize[EFFECTSPRITETYPE_INSTALL_TRAP_END_BACK];
	(*g_pActionInfoTable)[TRAP_TRIGGERED][5].LinkCount			= 0;
	(*g_pActionInfoTable)[TRAP_TRIGGERED][6].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[TRAP_TRIGGERED][6].EffectSpriteType = EFFECTSPRITETYPE_INSTALL_TRAP_END_FRONT;
	(*g_pActionInfoTable)[TRAP_TRIGGERED][6].Step				= 25;
	(*g_pActionInfoTable)[TRAP_TRIGGERED][6].Count				= FrameSize[EFFECTSPRITETYPE_INSTALL_TRAP_END_FRONT];

	(*g_pActionInfoTable)[TRAPPED].Set("TRAPPED", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC] );
	(*g_pActionInfoTable)[TRAPPED].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[TRAPPED].Init( 4 );
	(*g_pActionInfoTable)[TRAPPED][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[TRAPPED][0].EffectSpriteType = EFFECTSPRITETYPE_INSTALL_TRAP_ING_BACK;
	(*g_pActionInfoTable)[TRAPPED][0].Step				= 25;
	(*g_pActionInfoTable)[TRAPPED][0].Count				= FrameSize[EFFECTSPRITETYPE_INSTALL_TRAP_ING_BACK];
	(*g_pActionInfoTable)[TRAPPED][0].LinkCount			= 0;
	(*g_pActionInfoTable)[TRAPPED][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[TRAPPED][1].EffectSpriteType = EFFECTSPRITETYPE_INSTALL_TRAP_ING_FRONT;
	(*g_pActionInfoTable)[TRAPPED][1].Step				= 25;
	(*g_pActionInfoTable)[TRAPPED][1].Count				= FrameSize[EFFECTSPRITETYPE_INSTALL_TRAP_ING_FRONT];
	(*g_pActionInfoTable)[TRAPPED][1].SetDelayNode();
	(*g_pActionInfoTable)[TRAPPED][2].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[TRAPPED][2].EffectSpriteType = EFFECTSPRITETYPE_INSTALL_TRAP_END_BACK;
	(*g_pActionInfoTable)[TRAPPED][2].Step				= 25;
	(*g_pActionInfoTable)[TRAPPED][2].Count				= FrameSize[EFFECTSPRITETYPE_INSTALL_TRAP_END_BACK];
	(*g_pActionInfoTable)[TRAPPED][2].LinkCount			= 0;
	(*g_pActionInfoTable)[TRAPPED][3].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[TRAPPED][3].EffectSpriteType = EFFECTSPRITETYPE_INSTALL_TRAP_END_FRONT;
	(*g_pActionInfoTable)[TRAPPED][3].Step				= 25;
	(*g_pActionInfoTable)[TRAPPED][3].Count				= FrameSize[EFFECTSPRITETYPE_INSTALL_TRAP_END_FRONT];

	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_SMOKE].Set("SKILL_CLIENT_TANK_SMOKE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC] );
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_SMOKE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_SMOKE].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_SMOKE][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_SMOKE][0].EffectSpriteType = EFFECTSPRITETYPE_PET_SLAYER_SMOKE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_SMOKE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_SMOKE][0].Count				= FrameSize[EFFECTSPRITETYPE_PET_SLAYER_SMOKE];
	
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_3].Set("SKILL_CLIENT_TANK_ATTACK_3", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_ATTACK] );
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_3].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_3].Init( 2 );
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_3][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_3][0].EffectSpriteType = EFFECTSPRITETYPE_PET_SLAYER_3TH_ATTACK_1;
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_3][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_3][0].Count				= FrameSize[EFFECTSPRITETYPE_PET_SLAYER_3TH_ATTACK_1];
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_3][0].LinkCount = 0;
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_3][1].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_3][1].EffectSpriteType = EFFECTSPRITETYPE_PET_SLAYER_3TH_ATTACK_2;
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_3][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_3][1].Count				= FrameSize[EFFECTSPRITETYPE_PET_SLAYER_3TH_ATTACK_2];
	
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_4].Set("SKILL_CLIENT_TANK_ATTACK_4", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_ATTACK] );
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_4].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_4].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_4][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_4][0].EffectSpriteType = EFFECTSPRITETYPE_PET_SLAYER_4TH_ATTACK;
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_4][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_4][0].Count				= FrameSize[EFFECTSPRITETYPE_PET_SLAYER_4TH_ATTACK];
	
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_5].Set("SKILL_CLIENT_TANK_ATTACK_5", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_ATTACK] );
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_5].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_5].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_5][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_5][0].EffectSpriteType = EFFECTSPRITETYPE_PET_SLAYER_5TH_ATTACK;
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_5][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACK_5][0].Count				= FrameSize[EFFECTSPRITETYPE_PET_SLAYER_5TH_ATTACK];
	
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACKED].Set("SKILL_CLIENT_TANK_ATTACKED", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_DAMAGED] );
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACKED].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACKED].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACKED][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACKED][0].EffectSpriteType = EFFECTSPRITETYPE_EXPLOSION;
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACKED][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TANK_ATTACKED][0].Count				= FrameSize[EFFECTSPRITETYPE_EXPLOSION];
	
	// 2004,3,22 sobeit add start - 검은 기운 , 전기 기둥 , 유령
	(*g_pActionInfoTable)[MAP_BLACK_LARGE_SMOKE].Set("MAP_BLACK_LARGE_SMOKE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET );
	(*g_pActionInfoTable)[MAP_BLACK_LARGE_SMOKE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAP_BLACK_LARGE_SMOKE].Init( 1 );
	(*g_pActionInfoTable)[MAP_BLACK_LARGE_SMOKE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[MAP_BLACK_LARGE_SMOKE][0].EffectSpriteType = EFFECTSPRITETYPE_MAP_BLACK_LARGE_SMOKE;
	(*g_pActionInfoTable)[MAP_BLACK_LARGE_SMOKE][0].Step				= 25;
	(*g_pActionInfoTable)[MAP_BLACK_LARGE_SMOKE][0].Count				= 0xFFFF/*FrameSize[EFFECTSPRITETYPE_MAP_BLACK_LARGE_SMOKE]*/;

	(*g_pActionInfoTable)[MAP_BLACK_HALL].Set("MAP_BLACK_HALL", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET );
	(*g_pActionInfoTable)[MAP_BLACK_HALL].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAP_BLACK_HALL].Init( 1 );
	(*g_pActionInfoTable)[MAP_BLACK_HALL][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[MAP_BLACK_HALL][0].EffectSpriteType = EFFECTSPRITETYPE_MAP_BLACK_HALL;
	(*g_pActionInfoTable)[MAP_BLACK_HALL][0].Step				= 25;
	(*g_pActionInfoTable)[MAP_BLACK_HALL][0].Count				= FrameSize[EFFECTSPRITETYPE_MAP_BLACK_HALL];

	(*g_pActionInfoTable)[MAP_BLACK_SMALL_SMOKE_1].Set("MAP_BLACK_SMALL_SMOKE_1", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET );
	(*g_pActionInfoTable)[MAP_BLACK_SMALL_SMOKE_1].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAP_BLACK_SMALL_SMOKE_1].Init( 1 );
	(*g_pActionInfoTable)[MAP_BLACK_SMALL_SMOKE_1][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[MAP_BLACK_SMALL_SMOKE_1][0].EffectSpriteType = EFFECTSPRITETYPE_MAP_BLACK_SMALL_SMOKE_1;
	(*g_pActionInfoTable)[MAP_BLACK_SMALL_SMOKE_1][0].Step				= 25;
	(*g_pActionInfoTable)[MAP_BLACK_SMALL_SMOKE_1][0].Count				= 0xFFFF/*FrameSize[EFFECTSPRITETYPE_MAP_BLACK_SMALL_SMOKE_1]*/;

	(*g_pActionInfoTable)[MAP_BLACK_SMALL_SMOKE_2].Set("MAP_BLACK_SMALL_SMOKE_2", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET );
	(*g_pActionInfoTable)[MAP_BLACK_SMALL_SMOKE_2].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAP_BLACK_SMALL_SMOKE_2].Init( 1 );
	(*g_pActionInfoTable)[MAP_BLACK_SMALL_SMOKE_2][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[MAP_BLACK_SMALL_SMOKE_2][0].EffectSpriteType = EFFECTSPRITETYPE_MAP_BLACK_SMALL_SMOKE_2;
	(*g_pActionInfoTable)[MAP_BLACK_SMALL_SMOKE_2][0].Step				= 25;
	(*g_pActionInfoTable)[MAP_BLACK_SMALL_SMOKE_2][0].Count				= 0xFFFF/*FrameSize[EFFECTSPRITETYPE_MAP_BLACK_SMALL_SMOKE_2]*/;

	(*g_pActionInfoTable)[MAP_BLACK_SMALL_SMOKE_3].Set("MAP_BLACK_SMALL_SMOKE_3", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET );
	(*g_pActionInfoTable)[MAP_BLACK_SMALL_SMOKE_3].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAP_BLACK_SMALL_SMOKE_3].Init( 1 );
	(*g_pActionInfoTable)[MAP_BLACK_SMALL_SMOKE_3][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[MAP_BLACK_SMALL_SMOKE_3][0].EffectSpriteType = EFFECTSPRITETYPE_MAP_BLACK_SMALL_SMOKE_3;
	(*g_pActionInfoTable)[MAP_BLACK_SMALL_SMOKE_3][0].Step				= 25;
	(*g_pActionInfoTable)[MAP_BLACK_SMALL_SMOKE_3][0].Count				= 0xFFFF/*FrameSize[EFFECTSPRITETYPE_MAP_BLACK_SMALL_SMOKE_3]*/;

	(*g_pActionInfoTable)[MAP_ELECTRIC_POST].Set("MAP_ELECTRIC_POST", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET );
	(*g_pActionInfoTable)[MAP_ELECTRIC_POST].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAP_ELECTRIC_POST].Init( 1 );
	(*g_pActionInfoTable)[MAP_ELECTRIC_POST][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[MAP_ELECTRIC_POST][0].EffectSpriteType = EFFECTSPRITETYPE_MAP_ELECTRIC_POST;
	(*g_pActionInfoTable)[MAP_ELECTRIC_POST][0].Step				= 25;
	(*g_pActionInfoTable)[MAP_ELECTRIC_POST][0].Count				= FrameSize[EFFECTSPRITETYPE_MAP_BLACK_HALL]/*FrameSize[EFFECTSPRITETYPE_MAP_ELECTRIC_POST]*/;

	(*g_pActionInfoTable)[MAP_GHOST_1].Set("MAP_GHOST_1", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET );
	(*g_pActionInfoTable)[MAP_GHOST_1].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAP_GHOST_1].Init( 1 );
	(*g_pActionInfoTable)[MAP_GHOST_1][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[MAP_GHOST_1][0].EffectSpriteType = EFFECTSPRITETYPE_MAP_GHOST_1;
	(*g_pActionInfoTable)[MAP_GHOST_1][0].Step				= 25;
	(*g_pActionInfoTable)[MAP_GHOST_1][0].Count				= FrameSize[EFFECTSPRITETYPE_MAP_GHOST_1];

	(*g_pActionInfoTable)[MAP_GHOST_2].Set("MAP_GHOST_2", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET );
	(*g_pActionInfoTable)[MAP_GHOST_2].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAP_GHOST_2].Init( 1 );
	(*g_pActionInfoTable)[MAP_GHOST_2][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[MAP_GHOST_2][0].EffectSpriteType = EFFECTSPRITETYPE_MAP_GHOST_2;
	(*g_pActionInfoTable)[MAP_GHOST_2][0].Step				= 25;
	(*g_pActionInfoTable)[MAP_GHOST_2][0].Count				= FrameSize[EFFECTSPRITETYPE_MAP_GHOST_2];
	// 2004,3,6 sobeit add end - 검은 기운, 전기 기둥 , 유령

	// 2004, 3, 30 sobeit add start - 울버린 나올때 이펙트
	(*g_pActionInfoTable)[RESULT_SUMMON_ULBERINE].Set("RESULT_SUMMON_ULBERINE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[RESULT_SUMMON_ULBERINE].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SUMMON_ULBERINE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SUMMON_ULBERINE].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SUMMON_ULBERINE][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SUMMON_ULBERINE][0].EffectSpriteType	= EFFECTSPRITETYPE_SUMMON_ULBERINE;
	(*g_pActionInfoTable)[RESULT_SUMMON_ULBERINE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SUMMON_ULBERINE][0].Count				= FrameSize[EFFECTSPRITETYPE_SUMMON_ULBERINE];
	// 2004, 3, 30 sobeit add end - 울버린 나올때 이펙트

	// 2004, 4, 2 sobeit add start - 행운의 오로라(네잎 클로바)
	(*g_pActionInfoTable)[RESULT_LUCKY_AURA].Set("RESULT_LUCKY_AURA", ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[RESULT_LUCKY_AURA].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_LUCKY_AURA].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_LUCKY_AURA].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_LUCKY_AURA][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_LUCKY_AURA][0].EffectSpriteType	= EFFECTSPRITETYPE_LUCKY_AURA;
	(*g_pActionInfoTable)[RESULT_LUCKY_AURA][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_LUCKY_AURA][0].Count				= FrameSize[EFFECTSPRITETYPE_LUCKY_AURA];

	(*g_pActionInfoTable)[RESULT_MISFORTUNE_AURA].Set("RESULT_MISFORTUNE_AURA", ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[RESULT_MISFORTUNE_AURA].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_MISFORTUNE_AURA].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_MISFORTUNE_AURA].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_MISFORTUNE_AURA][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_MISFORTUNE_AURA][0].EffectSpriteType	= EFFECTSPRITETYPE_MISFORTUNE_AURA;
	(*g_pActionInfoTable)[RESULT_MISFORTUNE_AURA][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_MISFORTUNE_AURA][0].Count				= FrameSize[EFFECTSPRITETYPE_MISFORTUNE_AURA];
	// 2004, 4, 2 sobeit add end - 행운의 오로라(네잎 클로바)

	(*g_pActionInfoTable)[AMBER_OF_LIFE_TILE].Set("AMBER_OF_LIFE_TILE",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[AMBER_OF_LIFE_TILE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[AMBER_OF_LIFE_TILE].Init( 1 );
	(*g_pActionInfoTable)[AMBER_OF_LIFE_TILE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[AMBER_OF_LIFE_TILE][0].EffectSpriteType = EFFECTSPRITETYPE_AMBER_OF_LIFE;
	(*g_pActionInfoTable)[AMBER_OF_LIFE_TILE][0].Step						= 30;
	(*g_pActionInfoTable)[AMBER_OF_LIFE_TILE][0].Count					= FrameSize[EFFECTSPRITETYPE_AMBER_OF_GUARD_TILE];
	(*g_pActionInfoTable)[AMBER_OF_LIFE_TILE][0].SetDelayNode();

	(*g_pActionInfoTable)[AMBER_OF_LIGHT_TILE].Set("AMBER_OF_LIGHT_TILE",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[AMBER_OF_LIGHT_TILE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[AMBER_OF_LIGHT_TILE].Init( 1 );
	(*g_pActionInfoTable)[AMBER_OF_LIGHT_TILE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[AMBER_OF_LIGHT_TILE][0].EffectSpriteType = EFFECTSPRITETYPE_AMBER_OF_LIGHT;
	(*g_pActionInfoTable)[AMBER_OF_LIGHT_TILE][0].Step						= 30;
	(*g_pActionInfoTable)[AMBER_OF_LIGHT_TILE][0].Count					= FrameSize[EFFECTSPRITETYPE_AMBER_OF_AVENGER_TILE];
	(*g_pActionInfoTable)[AMBER_OF_LIGHT_TILE][0].SetDelayNode();


	// 2004, 5, 20 sobeit add start
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_AUGER].Set("SKILL_CLIENT_TRAP_ICICLE_AUGER", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_AUGER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_AUGER].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_AUGER][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_AUGER][0].EffectSpriteType = EFFECTSPRITETYPE_ICICLE_AUGER;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_AUGER][0].SoundID		 = SOUND_TRAP_A;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_AUGER][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_AUGER][0].Count				= FrameSize[EFFECTSPRITETYPE_ICICLE_AUGER];

	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_AUGER_SIGN].Set("SKILL_CLIENT_TRAP_ICICLE_AUGER_SIGN", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 100);	
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_AUGER_SIGN].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_AUGER_SIGN].Init( 3 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_AUGER_SIGN][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_AUGER_SIGN][0].EffectSpriteType	= EFFECTSPRITETYPE_ICICLE_AUGER_SIGN_START;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_AUGER_SIGN][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_AUGER_SIGN][0].Count				= FrameSize[EFFECTSPRITETYPE_ICICLE_AUGER_SIGN_START];
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_AUGER_SIGN][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_AUGER_SIGN][1].EffectSpriteType	= EFFECTSPRITETYPE_ICICLE_AUGER_SIGN_LOOP;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_AUGER_SIGN][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_AUGER_SIGN][1].Count				= FrameSize[EFFECTSPRITETYPE_ICICLE_AUGER_SIGN_LOOP];
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_AUGER_SIGN][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_AUGER_SIGN][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_AUGER_SIGN][2].EffectSpriteType	= EFFECTSPRITETYPE_ICICLE_AUGER_SIGN_END;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_AUGER_SIGN][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_AUGER_SIGN][2].Count				= FrameSize[EFFECTSPRITETYPE_ICICLE_AUGER_SIGN_END];

	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER].Set("SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER][0].EffectSpriteType = EFFECTSPRITETYPE_ICICLE_LARGE_AUGER;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER][0].SoundID			 = SOUND_TRAP_B;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER][0].Count				= FrameSize[EFFECTSPRITETYPE_ICICLE_LARGE_AUGER];

	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER_SIGN].Set("SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER_SIGN", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 100);	
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER_SIGN].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER_SIGN].Init( 3 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER_SIGN][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER_SIGN][0].EffectSpriteType	= EFFECTSPRITETYPE_ICICLE_LARGE_AUGER_SIGN_START;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER_SIGN][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER_SIGN][0].Count				= FrameSize[EFFECTSPRITETYPE_ICICLE_LARGE_AUGER_SIGN_START];
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER_SIGN][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER_SIGN][1].EffectSpriteType	= EFFECTSPRITETYPE_ICICLE_LARGE_AUGER_SIGN_LOOP;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER_SIGN][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER_SIGN][1].Count				= FrameSize[EFFECTSPRITETYPE_ICICLE_LARGE_AUGER_SIGN_LOOP];
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER_SIGN][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER_SIGN][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER_SIGN][2].EffectSpriteType	= EFFECTSPRITETYPE_ICICLE_LARGE_AUGER_SIGN_END;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER_SIGN][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_LARGE_AUGER_SIGN][2].Count				= FrameSize[EFFECTSPRITETYPE_ICICLE_LARGE_AUGER_SIGN_END];

	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_DROP].Set("SKILL_CLIENT_TRAP_ICICLE_DROP", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET | FLAG_ACTIONINFO_START_SKY, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_DROP].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_DROP].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_DROP][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_DROP][0].EffectSpriteType = EFFECTSPRITETYPE_ICICLE_DROP;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_DROP][0].SoundID			 = SOUND_DROP_A;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_DROP][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_DROP][0].Count				= FrameSize[EFFECTSPRITETYPE_ICICLE_DROP];
	
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_DROP_SIGN].Set("SKILL_CLIENT_TRAP_ICICLE_DROP_SIGN", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 100);	
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_DROP_SIGN].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_DROP_SIGN].Init( 3 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_DROP_SIGN][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_DROP_SIGN][0].EffectSpriteType	= EFFECTSPRITETYPE_ICICLE_DROP_SIGN_START;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_DROP_SIGN][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_DROP_SIGN][0].Count				= FrameSize[EFFECTSPRITETYPE_ICICLE_DROP_SIGN_START];
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_DROP_SIGN][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_DROP_SIGN][1].EffectSpriteType	= EFFECTSPRITETYPE_ICICLE_DROP_SIGN_LOOP;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_DROP_SIGN][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_DROP_SIGN][1].Count				= FrameSize[EFFECTSPRITETYPE_ICICLE_DROP_SIGN_LOOP];
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_DROP_SIGN][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_DROP_SIGN][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_DROP_SIGN][2].EffectSpriteType	= EFFECTSPRITETYPE_ICICLE_DROP_SIGN_END;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_DROP_SIGN][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICICLE_DROP_SIGN][2].Count				= FrameSize[EFFECTSPRITETYPE_ICICLE_DROP_SIGN_END];

	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW].Set("SKILL_CLIENT_TRAP_ICE_STICK_SW", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW].Init( 3 );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW][0].EffectSpriteType = EFFECTSPRITETYPE_ICE_STICK_SW_START;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW][0].SoundID			= SOUND_SIDE_SUMMON ;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW][0].Count				= FrameSize[EFFECTSPRITETYPE_ICE_STICK_SW_START];
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW][1].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW][1].EffectSpriteType = EFFECTSPRITETYPE_ICE_STICK_SW_LOOP;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW][1].Count				= FrameSize[EFFECTSPRITETYPE_ICE_STICK_SW_LOOP];
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW][2].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW][2].EffectSpriteType = EFFECTSPRITETYPE_ICE_STICK_SW_END;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW][2].SoundID			= SOUND_SIDE_DESTORY ;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW][2].Count				= FrameSize[EFFECTSPRITETYPE_ICE_STICK_SW_END];

	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW_SIGN].Set("SKILL_CLIENT_TRAP_ICE_STICK_SW_SIGN", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 100);	
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW_SIGN].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW_SIGN].Init( 3 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW_SIGN][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW_SIGN][0].EffectSpriteType	= EFFECTSPRITETYPE_ICE_STICK_SW_SIGN_START;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW_SIGN][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW_SIGN][0].Count				= FrameSize[EFFECTSPRITETYPE_ICE_STICK_SW_SIGN_START];
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW_SIGN][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW_SIGN][1].EffectSpriteType	= EFFECTSPRITETYPE_ICE_STICK_SW_SIGN_LOOP;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW_SIGN][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW_SIGN][1].Count				= FrameSize[EFFECTSPRITETYPE_ICE_STICK_SW_SIGN_LOOP];
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW_SIGN][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW_SIGN][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW_SIGN][2].EffectSpriteType	= EFFECTSPRITETYPE_ICE_STICK_SW_SIGN_END;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW_SIGN][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SW_SIGN][2].Count				= FrameSize[EFFECTSPRITETYPE_ICE_STICK_SW_SIGN_END];


	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE].Set("SKILL_CLIENT_TRAP_ICE_STICK_SE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE].Init( 3 );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE][0].EffectSpriteType = EFFECTSPRITETYPE_ICE_STICK_SE_START;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE][0].SoundID			= SOUND_SIDE_SUMMON ;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE][0].Count				= FrameSize[EFFECTSPRITETYPE_ICE_STICK_SE_START];
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE][1].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE][1].EffectSpriteType = EFFECTSPRITETYPE_ICE_STICK_SE_LOOP;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE][1].Count				= FrameSize[EFFECTSPRITETYPE_ICE_STICK_SE_LOOP];
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE][2].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE][2].EffectSpriteType = EFFECTSPRITETYPE_ICE_STICK_SE_END;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE][2].SoundID			= SOUND_SIDE_DESTORY ;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE][2].Count				= FrameSize[EFFECTSPRITETYPE_ICE_STICK_SE_END];


	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE_SIGN].Set("SKILL_CLIENT_TRAP_ICE_STICK_SE_SIGN", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 100);	
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE_SIGN].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE_SIGN].Init( 3 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE_SIGN][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE_SIGN][0].EffectSpriteType	= EFFECTSPRITETYPE_ICE_STICK_SE_SIGN_START;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE_SIGN][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE_SIGN][0].Count				= FrameSize[EFFECTSPRITETYPE_ICE_STICK_SE_SIGN_START];
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE_SIGN][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE_SIGN][1].EffectSpriteType	= EFFECTSPRITETYPE_ICE_STICK_SE_SIGN_LOOP;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE_SIGN][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE_SIGN][1].Count				= FrameSize[EFFECTSPRITETYPE_ICE_STICK_SE_SIGN_LOOP];
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE_SIGN][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE_SIGN][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE_SIGN][2].EffectSpriteType	= EFFECTSPRITETYPE_ICE_STICK_SE_SIGN_END;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE_SIGN][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_SE_SIGN][2].Count				= FrameSize[EFFECTSPRITETYPE_ICE_STICK_SE_SIGN_END];


	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE].Set("SKILL_CLIENT_TRAP_ICE_STICK_NE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE].Init( 3 );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE][0].EffectSpriteType = EFFECTSPRITETYPE_ICE_STICK_NE_START;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE][0].SoundID			= SOUND_SIDE_SUMMON ;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE][0].Count				= FrameSize[EFFECTSPRITETYPE_ICE_STICK_NE_START];
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE][1].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE][1].EffectSpriteType = EFFECTSPRITETYPE_ICE_STICK_NE_LOOP;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE][1].Count				= FrameSize[EFFECTSPRITETYPE_ICE_STICK_NE_LOOP];
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE][2].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE][2].EffectSpriteType = EFFECTSPRITETYPE_ICE_STICK_NE_END;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE][2].SoundID			= SOUND_SIDE_DESTORY ;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE][2].Count				= FrameSize[EFFECTSPRITETYPE_ICE_STICK_NE_END];

	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE_SIGN].Set("SKILL_CLIENT_TRAP_ICE_STICK_NE_SIGN", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 100);	
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE_SIGN].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE_SIGN].Init( 3 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE_SIGN][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE_SIGN][0].EffectSpriteType	= EFFECTSPRITETYPE_ICE_STICK_NE_SIGN_START;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE_SIGN][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE_SIGN][0].Count				= FrameSize[EFFECTSPRITETYPE_ICE_STICK_NE_SIGN_START];
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE_SIGN][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE_SIGN][1].EffectSpriteType	= EFFECTSPRITETYPE_ICE_STICK_NE_SIGN_LOOP;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE_SIGN][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE_SIGN][1].Count				= FrameSize[EFFECTSPRITETYPE_ICE_STICK_NE_SIGN_LOOP];
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE_SIGN][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE_SIGN][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE_SIGN][2].EffectSpriteType	= EFFECTSPRITETYPE_ICE_STICK_NE_SIGN_END;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE_SIGN][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NE_SIGN][2].Count				= FrameSize[EFFECTSPRITETYPE_ICE_STICK_NE_SIGN_END];


	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW].Set("SKILL_CLIENT_TRAP_ICE_STICK_NW", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW].Init( 3 );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW][0].EffectSpriteType = EFFECTSPRITETYPE_ICE_STICK_NW_START;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW][0].Count				= FrameSize[EFFECTSPRITETYPE_ICE_STICK_NW_START];
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW][0].SoundID			= SOUND_SIDE_SUMMON ;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW][1].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW][1].EffectSpriteType = EFFECTSPRITETYPE_ICE_STICK_NW_LOOP;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW][1].Count				= FrameSize[EFFECTSPRITETYPE_ICE_STICK_NW_LOOP];
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW][2].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW][2].EffectSpriteType = EFFECTSPRITETYPE_ICE_STICK_NW_END;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW][2].SoundID			= SOUND_SIDE_DESTORY ;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW][2].Count				= FrameSize[EFFECTSPRITETYPE_ICE_STICK_NW_END];
	

	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW_SIGN].Set("SKILL_CLIENT_TRAP_ICE_STICK_NW_SIGN", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 100);	
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW_SIGN].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW_SIGN].Init( 3 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW_SIGN][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW_SIGN][0].EffectSpriteType	= EFFECTSPRITETYPE_ICE_STICK_NW_SIGN_START;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW_SIGN][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW_SIGN][0].Count				= FrameSize[EFFECTSPRITETYPE_ICE_STICK_NW_SIGN_START];
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW_SIGN][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW_SIGN][1].EffectSpriteType	= EFFECTSPRITETYPE_ICE_STICK_NW_SIGN_LOOP;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW_SIGN][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW_SIGN][1].Count				= FrameSize[EFFECTSPRITETYPE_ICE_STICK_NW_SIGN_LOOP];
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW_SIGN][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW_SIGN][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW_SIGN][2].EffectSpriteType	= EFFECTSPRITETYPE_ICE_STICK_NW_SIGN_END;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW_SIGN][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TRAP_ICE_STICK_NW_SIGN][2].Count				= FrameSize[EFFECTSPRITETYPE_ICE_STICK_NW_SIGN_END];
	// 2004, 5, 19 sobeit add end

	// 2004, 6, 5 sobeit add start - BLINDNESS
	(*g_pActionInfoTable)[SKILL_CLIENT_BLINDNESS].Set("SKILL_CLIENT_BLINDNESS", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_CLIENT_BLINDNESS].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_BLINDNESS].SetMainNode( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_BLINDNESS].Init( 3 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_BLINDNESS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE_GROUND;
	(*g_pActionInfoTable)[SKILL_CLIENT_BLINDNESS][0].EffectSpriteType	= EFFECTSPRITETYPE_BLINDNESS_BACK_1;
	(*g_pActionInfoTable)[SKILL_CLIENT_BLINDNESS][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_BLINDNESS][0].Count				= FrameSize[EFFECTSPRITETYPE_BLINDNESS_BACK_1];
	(*g_pActionInfoTable)[SKILL_CLIENT_BLINDNESS][0].SoundID			= SOUND_BLINDNESS;
	(*g_pActionInfoTable)[SKILL_CLIENT_BLINDNESS][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE_GROUND;
	(*g_pActionInfoTable)[SKILL_CLIENT_BLINDNESS][1].EffectSpriteType	= EFFECTSPRITETYPE_BLINDNESS_BACK_2;
	(*g_pActionInfoTable)[SKILL_CLIENT_BLINDNESS][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_BLINDNESS][1].Count				= FrameSize[EFFECTSPRITETYPE_BLINDNESS_BACK_2];
//	(*g_pActionInfoTable)[SKILL_CLIENT_BLINDNESS][1].SetResultTime();
	(*g_pActionInfoTable)[SKILL_CLIENT_BLINDNESS][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_BLINDNESS][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE_GROUND;
	(*g_pActionInfoTable)[SKILL_CLIENT_BLINDNESS][2].EffectSpriteType	= EFFECTSPRITETYPE_BLINDNESS_BACK_3;
	(*g_pActionInfoTable)[SKILL_CLIENT_BLINDNESS][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_BLINDNESS][2].Count				= FrameSize[EFFECTSPRITETYPE_BLINDNESS_BACK_3];
	// 2004, 6, 5 sobeit add end - BLINDNESS


	// 2004, 6, 15 sobeit add start - gdr skill - glacier
	(*g_pActionInfoTable)[SKILL_GLACIER_1].Set("SKILL_GLACIER_1", ACTION_OUSTERS_DRAIN, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, OustersActionDelay[ACTION_OUSTERS_DRAIN]);
	(*g_pActionInfoTable)[SKILL_GLACIER_1].SetPacketType( ACTIONINFO_PACKET_BLOOD_DRAIN );	
	(*g_pActionInfoTable)[SKILL_GLACIER_1].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_GLACIER_1].SetStartWithCasting();

	(*g_pActionInfoTable)[RESULT_SKILL_GLACIER_1].Set("RESULT_SKILL_GLACIER_1", ACTION_OUSTERS_DRAIN, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_GLACIER_1].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[SKILL_GLACIER_2].Set("SKILL_GLACIER_2", ACTION_OUSTERS_DRAIN, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, OustersActionDelay[ACTION_OUSTERS_DRAIN]);
	(*g_pActionInfoTable)[SKILL_GLACIER_2].SetPacketType( ACTIONINFO_PACKET_BLOOD_DRAIN );	
	(*g_pActionInfoTable)[SKILL_GLACIER_2].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_GLACIER_2].SetStartWithCasting();

	(*g_pActionInfoTable)[RESULT_SKILL_GLACIER_2].Set("RESULT_SKILL_GLACIER_2", ACTION_OUSTERS_DRAIN, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_GLACIER_2].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_SLAYER].Set("SKILL_CLIENT_GDR_GLACIER_SLAYER", ACTION_DRAINED, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_SLAYER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_SLAYER].SetMainNode( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_SLAYER].Init( 3 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_SLAYER][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_SLAYER][0].EffectSpriteType	= EFFECTSPRITETYPE_GDR_GLACIER_SLAYER_START;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_SLAYER][0].SoundID			= SOUND_GLACIER_START ;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_SLAYER][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_SLAYER][0].Count				= FrameSize[EFFECTSPRITETYPE_GDR_GLACIER_SLAYER_START];
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_SLAYER][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_SLAYER][1].EffectSpriteType	= EFFECTSPRITETYPE_GDR_GLACIER_SLAYER_LOOP;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_SLAYER][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_SLAYER][1].Count				= FrameSize[EFFECTSPRITETYPE_GDR_GLACIER_SLAYER_LOOP];
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_SLAYER][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_SLAYER][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_SLAYER][2].EffectSpriteType	= EFFECTSPRITETYPE_GDR_GLACIER_SLAYER_END;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_SLAYER][2].SoundID			= SOUND_GLACIER_END ;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_SLAYER][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_SLAYER][2].Count				= FrameSize[EFFECTSPRITETYPE_GDR_GLACIER_SLAYER_END];

	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_VAMPIRE].Set("SKILL_CLIENT_GDR_GLACIER_VAMPIRE", ACTION_DRAINED, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_VAMPIRE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_VAMPIRE].SetMainNode( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_VAMPIRE].Init( 3 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_VAMPIRE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_VAMPIRE][0].EffectSpriteType	= EFFECTSPRITETYPE_GDR_GLACIER_VAMPIRE_START;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_VAMPIRE][0].SoundID			= SOUND_GLACIER_START ;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_VAMPIRE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_VAMPIRE][0].Count				= FrameSize[EFFECTSPRITETYPE_GDR_GLACIER_VAMPIRE_START];
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_VAMPIRE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_VAMPIRE][1].EffectSpriteType	= EFFECTSPRITETYPE_GDR_GLACIER_VAMPIRE_LOOP;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_VAMPIRE][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_VAMPIRE][1].Count				= FrameSize[EFFECTSPRITETYPE_GDR_GLACIER_VAMPIRE_LOOP];
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_VAMPIRE][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_VAMPIRE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_VAMPIRE][2].EffectSpriteType	= EFFECTSPRITETYPE_GDR_GLACIER_VAMPIRE_END;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_VAMPIRE][2].SoundID			= SOUND_GLACIER_END ;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_VAMPIRE][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_VAMPIRE][2].Count				= FrameSize[EFFECTSPRITETYPE_GDR_GLACIER_VAMPIRE_END];

	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_OUSTERS].Set("SKILL_CLIENT_GDR_GLACIER_OUSTERS", ACTION_DRAINED, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_OUSTERS].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_OUSTERS].SetMainNode( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_OUSTERS].Init( 3 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_OUSTERS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_OUSTERS][0].EffectSpriteType	= EFFECTSPRITETYPE_GDR_GLACIER_OUSTERS_START;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_OUSTERS][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_OUSTERS][0].Count				= FrameSize[EFFECTSPRITETYPE_GDR_GLACIER_OUSTERS_START];
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_OUSTERS][0].SoundID			= SOUND_GLACIER_START;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_OUSTERS][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_OUSTERS][1].EffectSpriteType	= EFFECTSPRITETYPE_GDR_GLACIER_OUSTERS_LOOP;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_OUSTERS][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_OUSTERS][1].Count				= FrameSize[EFFECTSPRITETYPE_GDR_GLACIER_OUSTERS_LOOP];
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_OUSTERS][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_OUSTERS][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_OUSTERS][2].EffectSpriteType	= EFFECTSPRITETYPE_GDR_GLACIER_OUSTERS_END;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_OUSTERS][2].SoundID			= SOUND_GLACIER_END ;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_OUSTERS][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_GLACIER_OUSTERS][2].Count				= FrameSize[EFFECTSPRITETYPE_GDR_GLACIER_OUSTERS_END];
	// 2004, 6, 15 sobeit add end - gdr skill - glacier

	// 2004, 6, 21 sobeit add start - 질드레 스킬들..^^;
//	(*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD].Set("SKILL_WIDE_ICE_FIELD", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
//	(*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD].SetSoundID( SOUNDID_NULL );
//	(*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD].SetCastingActionInfo( CASTING_WATER );
//	(*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD].SetUseActionGrade();
	
    (*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD].Set("SKILL_WIDE_ICE_FIELD", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD].SetSoundID( SOUND_OUSTERS_ICE_FIELD );
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD].Init( 3 );
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD].SetMainNode( 1 );
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE_RECT;
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD][0].EffectSpriteType = EFFECTSPRITETYPE_ICE_FIELD_1;
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD][0].Count				= FrameSize[EFFECTSPRITETYPE_ICE_FIELD_1];
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD][0].SoundID			= SOUNDID_NULL;
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD][1].EffectSpriteType = EFFECTSPRITETYPE_ICE_FIELD_2;
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD][1].Count				= FrameSize[EFFECTSPRITETYPE_ICE_FIELD_2];
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD][1].SoundID			= SOUNDID_NULL;
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD][1].SetResultTime();
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD][2].EffectGeneratorID = EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD][2].EffectSpriteType = EFFECTSPRITETYPE_ICE_FIELD_3;
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD][2].Count				= FrameSize[EFFECTSPRITETYPE_ICE_FIELD_3];
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_FIELD][2].SoundID			= SOUNDID_NULL;


//	(*g_pActionInfoTable)[RESULT_SKILL_ICE_AUGER].Set("RESULT_SKILL_ICE_AUGER", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET );
//	(*g_pActionInfoTable)[RESULT_SKILL_ICE_AUGER].SetSoundID( SOUNDID_NULL );
//	(*g_pActionInfoTable)[RESULT_SKILL_ICE_AUGER].Init( 1 );
//	(*g_pActionInfoTable)[RESULT_SKILL_ICE_AUGER][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[RESULT_SKILL_ICE_AUGER][0].EffectSpriteType = EFFECTSPRITETYPE_ICICLE_DROP;
//	(*g_pActionInfoTable)[RESULT_SKILL_ICE_AUGER][0].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_SKILL_ICE_AUGER][0].Count				= FrameSize[EFFECTSPRITETYPE_ICICLE_DROP];


	(*g_pActionInfoTable)[SKILL_ICE_AUGER].Set("SKILL_ICE_AUGER", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
//	(*g_pActionInfoTable)[SKILL_ICE_AUGER].SetPacketType( ACTIONINFO_PACKET_OTHER );	
	(*g_pActionInfoTable)[SKILL_ICE_AUGER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_ICE_AUGER].SetStartWithCasting();

	(*g_pActionInfoTable)[RESULT_SKILL_ICE_AUGER].Set("RESULT_SKILL_ICE_AUGER", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_ICE_AUGER].SetSoundID( SOUND_ICEAUGER );
	(*g_pActionInfoTable)[RESULT_SKILL_ICE_AUGER].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_ICE_AUGER][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_ICE_AUGER][0].EffectSpriteType = EFFECTSPRITETYPE_ICICLE_DROP;
	(*g_pActionInfoTable)[RESULT_SKILL_ICE_AUGER][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ICE_AUGER][0].Count				= FrameSize[EFFECTSPRITETYPE_ICICLE_DROP];

	(*g_pActionInfoTable)[SKILL_ICE_HAIL].Set("SKILL_ICE_HAIL", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET | FLAG_ACTIONINFO_START_SKY, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_ICE_HAIL].SetCastingActionInfo( CASTING_HEALING );
	(*g_pActionInfoTable)[SKILL_ICE_HAIL].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[SKILL_ICE_HAIL].SetStartFrameAll( 5 );	
	(*g_pActionInfoTable)[SKILL_ICE_HAIL].SetSoundID( SOUND_ICEHAIL );
	(*g_pActionInfoTable)[SKILL_ICE_HAIL].Init( 2 );
	(*g_pActionInfoTable)[SKILL_ICE_HAIL][0].EffectGeneratorID	= EFFECTGENERATORID_MULTIPLE_FALLING;
	(*g_pActionInfoTable)[SKILL_ICE_HAIL][0].EffectSpriteType	= EFFECTSPRITETYPE_GDR_ICE_HAIL_DROP;
	(*g_pActionInfoTable)[SKILL_ICE_HAIL][0].Step				= 30;
	(*g_pActionInfoTable)[SKILL_ICE_HAIL][0].Count				= FrameSize[EFFECTSPRITETYPE_GDR_ICE_HAIL_DROP];
	(*g_pActionInfoTable)[SKILL_ICE_HAIL][0].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_ICE_HAIL][0].SetResultTime();
	(*g_pActionInfoTable)[SKILL_ICE_HAIL][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_ICE_HAIL][1].EffectSpriteType	= EFFECTSPRITETYPE_GDR_ICE_HAIL_WAVE;
	(*g_pActionInfoTable)[SKILL_ICE_HAIL][1].Step				= 15;
	(*g_pActionInfoTable)[SKILL_ICE_HAIL][1].Count				= FrameSize[EFFECTSPRITETYPE_GDR_ICE_HAIL_WAVE];	
	(*g_pActionInfoTable)[SKILL_ICE_HAIL].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_WIDE_ICE_HAIL );	// 맞는 결과를 표현한다.	

	(*g_pActionInfoTable)[RESULT_SKILL_ICE_HAIL].Set("RESULT_SKILL_ICE_HAIL", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_ICE_HAIL].SetSoundID( SOUNDID_NULL );


	(*g_pActionInfoTable)[SKILL_WIDE_ICE_HAIL].Set("SKILL_WIDE_ICE_HAIL", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET | FLAG_ACTIONINFO_START_SKY, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_HAIL].SetCastingActionInfo( CASTING_HEALING );
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_HAIL].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_HAIL].SetStartFrameAll( 5 );	
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_HAIL].SetSoundID( SOUND_ICEHAIL );
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_HAIL].Init( 2 );
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_HAIL][0].EffectGeneratorID	= EFFECTGENERATORID_MULTIPLE_FALLING;
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_HAIL][0].EffectSpriteType	= EFFECTSPRITETYPE_GDR_ICE_HAIL_DROP;
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_HAIL][0].Step				= 30;
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_HAIL][0].Count				= FrameSize[EFFECTSPRITETYPE_GDR_ICE_HAIL_DROP];
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_HAIL][0].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_HAIL][0].SetResultTime();
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_HAIL][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_HAIL][1].EffectSpriteType	= EFFECTSPRITETYPE_GDR_ICE_HAIL_WAVE;
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_HAIL][1].Step				= 15;
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_HAIL][1].Count				= FrameSize[EFFECTSPRITETYPE_GDR_ICE_HAIL_WAVE];	
	(*g_pActionInfoTable)[SKILL_WIDE_ICE_HAIL].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_WIDE_ICE_HAIL );	// 맞는 결과를 표현한다.	

	(*g_pActionInfoTable)[RESULT_SKILL_WIDE_ICE_HAIL].Set("RESULT_SKILL_WIDE_ICE_HAIL", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_WIDE_ICE_HAIL].SetSoundID( SOUNDID_NULL );
	
	(*g_pActionInfoTable)[SKILL_ICE_WAVE].Set("SKILL_ICE_WAVE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET );
	(*g_pActionInfoTable)[SKILL_ICE_WAVE].SetSoundID( SOUND_ICEWAVE );
	(*g_pActionInfoTable)[SKILL_ICE_WAVE].Init( 1 );
	(*g_pActionInfoTable)[SKILL_ICE_WAVE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_ICE_WAVE][0].EffectSpriteType = EFFECTSPRITETYPE_ICICLE_LARGE_AUGER;
	(*g_pActionInfoTable)[SKILL_ICE_WAVE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_ICE_WAVE][0].Count				= FrameSize[EFFECTSPRITETYPE_ICICLE_LARGE_AUGER];

	(*g_pActionInfoTable)[RESULT_SKILL_ICE_WAVE].Set("RESULT_SKILL_ICE_WAVE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_ICE_WAVE].SetSoundID( SOUNDID_NULL );
	// 2004, 6, 21 sobeit add end - 질드레 스킬들..^^;

	// 2004, 6, 26 sobeit add start
	(*g_pActionInfoTable)[MAP_GDR_LAIR_POTAL].Set("MAP_GDR_LAIR_POTAL", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET );
	(*g_pActionInfoTable)[MAP_GDR_LAIR_POTAL].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[MAP_GDR_LAIR_POTAL].Init( 1 );
	(*g_pActionInfoTable)[MAP_GDR_LAIR_POTAL][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[MAP_GDR_LAIR_POTAL][0].EffectSpriteType = EFFECTSPRITETYPE_GDR_LAIR_POTAL;
	(*g_pActionInfoTable)[MAP_GDR_LAIR_POTAL][0].Step				= 25;
	(*g_pActionInfoTable)[MAP_GDR_LAIR_POTAL][0].Count				= 0xFFFF/*FrameSize[EFFECTSPRITETYPE_GDR_LAIR_POTAL]*/;
	// 2004, 6, 26 sobeit add end

	// 2004, 8, 5 sobeit add start
	(*g_pActionInfoTable)[SKILL_CLIENT_CASTLE_GATE_DEAD].Set("SKILL_CLIENT_CASTLE_GATE_DEAD", ACTION_DIE, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_CLIENT_CASTLE_GATE_DEAD].Init( 1 );	
	(*g_pActionInfoTable)[SKILL_CLIENT_CASTLE_GATE_DEAD][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_CASTLE_GATE_DEAD][0].EffectSpriteType	= EFFECTSPRITETYPE_CASTLE_GATE_LARGE_DUST;
	(*g_pActionInfoTable)[SKILL_CLIENT_CASTLE_GATE_DEAD][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_CASTLE_GATE_DEAD][0].Count				= FrameSize[EFFECTSPRITETYPE_CASTLE_GATE_LARGE_DUST];

	(*g_pActionInfoTable)[SKILL_CLIENT_CASTLE_GATE_DAMAGED].Set("SKILL_CLIENT_CASTLE_GATE_DAMAGED", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_CLIENT_CASTLE_GATE_DAMAGED].Init( 1 );	
	(*g_pActionInfoTable)[SKILL_CLIENT_CASTLE_GATE_DAMAGED][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_CASTLE_GATE_DAMAGED][0].EffectSpriteType	= EFFECTSPRITETYPE_CASTLE_GATE_DAMAGED;
	(*g_pActionInfoTable)[SKILL_CLIENT_CASTLE_GATE_DAMAGED][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_CASTLE_GATE_DAMAGED][0].Count				= FrameSize[EFFECTSPRITETYPE_CASTLE_GATE_DAMAGED];

		
	(*g_pActionInfoTable)[SKILL_CLIENT_GUILD_TOWER_DEAD].Set("SKILL_CLIENT_GUILD_TOWER_DEAD", ACTION_DIE, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_CLIENT_GUILD_TOWER_DEAD].Init( 1 );	
	(*g_pActionInfoTable)[SKILL_CLIENT_GUILD_TOWER_DEAD][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_GUILD_TOWER_DEAD][0].EffectSpriteType	= EFFECTSPRITETYPE_GUILD_TOWER_DESTROY;
	(*g_pActionInfoTable)[SKILL_CLIENT_GUILD_TOWER_DEAD][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_GUILD_TOWER_DEAD][0].Count				= FrameSize[EFFECTSPRITETYPE_GUILD_TOWER_DESTROY];

	(*g_pActionInfoTable)[SKILL_CLIENT_GUILD_TOWER_PROTECT].Set("SKILL_CLIENT_GUILD_TOWER_PROTECT", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_CLIENT_GUILD_TOWER_PROTECT].Init( 1 );	
	(*g_pActionInfoTable)[SKILL_CLIENT_GUILD_TOWER_PROTECT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_GUILD_TOWER_PROTECT][0].EffectSpriteType	= EFFECTSPRITETYPE_GUILD_TOWER_PROTECT;
	(*g_pActionInfoTable)[SKILL_CLIENT_GUILD_TOWER_PROTECT][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_GUILD_TOWER_PROTECT][0].Count				= FrameSize[EFFECTSPRITETYPE_GUILD_TOWER_PROTECT];
	// 2004, 8, 5 sobeit add end

	// 2004, 8, 31, sobeit add start - 트랩 관련
	(*g_pActionInfoTable)[SKILL_CLIENT_LAND_MINE_LIGHT].Set("SKILL_CLIENT_LAND_MINE_LIGHT", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_CLIENT_LAND_MINE_LIGHT].Init( 1 );	
	(*g_pActionInfoTable)[SKILL_CLIENT_LAND_MINE_LIGHT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_LAND_MINE_LIGHT][0].EffectSpriteType	= EFFECTSPRITETYPE_LAND_MINE_LIGHT;
	(*g_pActionInfoTable)[SKILL_CLIENT_LAND_MINE_LIGHT][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_LAND_MINE_LIGHT][0].Count			= 0xffff; //FrameSize[EFFECTSPRITETYPE_LAND_MINE_LIGHT];

	(*g_pActionInfoTable)[SKILL_CLIENT_PLEASUER_STATION_LIGHT].Set("SKILL_CLIENT_PLEASUER_STATION_LIGHT", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_CLIENT_PLEASUER_STATION_LIGHT].Init( 1 );	
	(*g_pActionInfoTable)[SKILL_CLIENT_PLEASUER_STATION_LIGHT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_PLEASUER_STATION_LIGHT][0].EffectSpriteType	= EFFECTSPRITETYPE_PLEASUER_STATION_LIGHT_START;
	(*g_pActionInfoTable)[SKILL_CLIENT_PLEASUER_STATION_LIGHT][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_PLEASUER_STATION_LIGHT][0].Count			= 0xffff; //FrameSize[EFFECTSPRITETYPE_PLEASUER_STATION_LIGHT_START];


	// RESULT_SKILL_GUN_SHOT_GUIDANCE,			// Saint Aura
	(*g_pActionInfoTable)[SKILL_LAND_MINE_EXPLOSION].Set("SKILL_LAND_MINE_EXPLOSION", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_LAND_MINE_EXPLOSION].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_LAND_MINE_EXPLOSION].Init( 3 );
	(*g_pActionInfoTable)[SKILL_LAND_MINE_EXPLOSION][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE_RECT;
	(*g_pActionInfoTable)[SKILL_LAND_MINE_EXPLOSION][0].EffectSpriteType	= EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_WAVE;
	(*g_pActionInfoTable)[SKILL_LAND_MINE_EXPLOSION][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_LAND_MINE_EXPLOSION][0].Count				= FrameSize[EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_WAVE];
	(*g_pActionInfoTable)[SKILL_LAND_MINE_EXPLOSION][0].SoundID			= SOUND_ITEM_BOOM4;
	(*g_pActionInfoTable)[SKILL_LAND_MINE_EXPLOSION][0].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_LAND_MINE_EXPLOSION][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_LAND_MINE_EXPLOSION][1].EffectSpriteType	= EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_BOOM;
	(*g_pActionInfoTable)[SKILL_LAND_MINE_EXPLOSION][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_LAND_MINE_EXPLOSION][1].Count				= FrameSize[EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_BOOM];
	(*g_pActionInfoTable)[SKILL_LAND_MINE_EXPLOSION][1].LinkCount			= 2;
	(*g_pActionInfoTable)[SKILL_LAND_MINE_EXPLOSION][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_LAND_MINE_EXPLOSION][2].EffectSpriteType	= EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_PIT;
	(*g_pActionInfoTable)[SKILL_LAND_MINE_EXPLOSION][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_LAND_MINE_EXPLOSION][2].Count				= FrameSize[EFFECTSPRITETYPE_GUN_SHOT_GUIDANCE_PIT];

	(*g_pActionInfoTable)[RESULT_SKILL_LAND_MINE_EXPLOSION].Set("RESULT_SKILL_LAND_MINE_EXPLOSION", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_LAND_MINE_EXPLOSION].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[SKILL_CLAYMORE_EXPLOSION].Set("SKILL_CLAYMORE_EXPLOSION", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_CLAYMORE_EXPLOSION].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLAYMORE_EXPLOSION].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_CLAYMORE_EXPLOSION].SetMainNode( 1 );
	(*g_pActionInfoTable)[SKILL_CLAYMORE_EXPLOSION][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLAYMORE_EXPLOSION][0].EffectSpriteType	= EFFECTSPRITETYPE_CLAYMORE_BODY_EXPLOSION;
	(*g_pActionInfoTable)[SKILL_CLAYMORE_EXPLOSION][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLAYMORE_EXPLOSION][0].Count				= FrameSize[EFFECTSPRITETYPE_CLAYMORE_BODY_EXPLOSION];
	(*g_pActionInfoTable)[SKILL_CLAYMORE_EXPLOSION][0].LinkCount			= 4;
	(*g_pActionInfoTable)[SKILL_CLAYMORE_EXPLOSION][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLAYMORE_EXPLOSION][1].EffectSpriteType	= EFFECTSPRITETYPE_CLAYMORE_SPREAD_EXPLOSION;
	(*g_pActionInfoTable)[SKILL_CLAYMORE_EXPLOSION][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLAYMORE_EXPLOSION][1].Count				= FrameSize[EFFECTSPRITETYPE_CLAYMORE_SPREAD_EXPLOSION];
	(*g_pActionInfoTable)[SKILL_CLAYMORE_EXPLOSION][1].SoundID			= SOUND_ITEM_BOOM4;

	(*g_pActionInfoTable)[RESULT_SKILL_CLAYMORE_EXPLOSION].Set("RESULT_SKILL_CLAYMORE_EXPLOSION", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_CLAYMORE_EXPLOSION].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[SKILL_PLEASURE_EXPLOSION].Set("SKILL_PLEASURE_EXPLOSION", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_PLEASURE_EXPLOSION].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_PLEASURE_EXPLOSION].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_PLEASURE_EXPLOSION].SetMainNode( 1 );
	(*g_pActionInfoTable)[SKILL_PLEASURE_EXPLOSION][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_PLEASURE_EXPLOSION][0].EffectSpriteType	= EFFECTSPRITETYPE_PLEASUER_STATION_LIGHT_END;
	(*g_pActionInfoTable)[SKILL_PLEASURE_EXPLOSION][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_PLEASURE_EXPLOSION][0].Count				= FrameSize[EFFECTSPRITETYPE_PLEASUER_STATION_LIGHT_END];
	(*g_pActionInfoTable)[SKILL_PLEASURE_EXPLOSION][0].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_PLEASURE_EXPLOSION][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_PLEASURE_EXPLOSION][1].EffectSpriteType	= EFFECTSPRITETYPE_PLEASUER_STATION_LIGHT_SPREAD;
	(*g_pActionInfoTable)[SKILL_PLEASURE_EXPLOSION][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_PLEASURE_EXPLOSION][1].Count				= FrameSize[EFFECTSPRITETYPE_PLEASUER_STATION_LIGHT_SPREAD];
	

	(*g_pActionInfoTable)[RESULT_SKILL_PLEASURE_EXPLOSION].Set("RESULT_SKILL_PLEASURE_EXPLOSION", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_PLEASURE_EXPLOSION].SetSoundID( SOUNDID_NULL );
	
	// 2004, 8, 31, sobeit add end

	// 2004, 9, 2, sobeit add start
	(*g_pActionInfoTable)[SKILL_CLIENT_TURRET_LASER].Set("SKILL_CLIENT_TURRET_LASER", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[SKILL_CLIENT_TURRET_LASER].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[SKILL_CLIENT_TURRET_LASER].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_TURRET_LASER][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TURRET_LASER][0].EffectSpriteType = EFFECTSPRITETYPE_AUTO_TURRET_BEAM;
	(*g_pActionInfoTable)[SKILL_CLIENT_TURRET_LASER][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TURRET_LASER][0].Count				= FrameSize[EFFECTSPRITETYPE_AUTO_TURRET_BEAM];
	(*g_pActionInfoTable)[SKILL_CLIENT_TURRET_LASER][0].SetDelayNode();

	(*g_pActionInfoTable)[SKILL_CLIENT_TURRET_LASER_ATTACK].Set("SKILL_CLIENT_TURRET_LASER_ATTACK", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[SKILL_CLIENT_TURRET_LASER_ATTACK].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[SKILL_CLIENT_TURRET_LASER_ATTACK].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_TURRET_LASER_ATTACK][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_TURRET_LASER_ATTACK][0].EffectSpriteType = EFFECTSPRITETYPE_AUTO_TURRET_BEAM;
	(*g_pActionInfoTable)[SKILL_CLIENT_TURRET_LASER_ATTACK][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_TURRET_LASER_ATTACK][0].Count				= FrameSize[EFFECTSPRITETYPE_AUTO_TURRET_BEAM];
	(*g_pActionInfoTable)[SKILL_CLIENT_TURRET_LASER_ATTACK][0].SetDelayNode();
	// 2004, 9, 2, sobeit add end

	// 2004, 9, 6, sobeit add start - 질드레 죽기 이펙트
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_DEAD].Set("SKILL_CLIENT_GDR_DEAD", ACTION_DIE, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_DEAD].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_DEAD].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_DEAD][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_DEAD][0].EffectSpriteType	= EFFECTSPRITETYPE_GDR_DEAD;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_DEAD][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_GDR_DEAD][0].Count				= FrameSize[EFFECTSPRITETYPE_GDR_DEAD];
	// 2004, 9, 6, sobeit add end - 질드레 죽기 이펙트

	// 2004, 9, 8, sobeit add start - 130 스킬들
	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR].Set("SKILL_SWORD_OF_THOR", ACTION_SLAYER_SWORD_2, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD_2]);
	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR].SetStartFrameAll( 5 );
	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR].SetSoundID( SOUND_SLAYER_SWORDOFTHOR );
	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR].SetMainNode( 1 );
	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, RESULT_SKILL_SWORD_OF_THOR );	// 맞는 결과를 표현한다.	
	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][0].EffectSpriteType	= EFFECTSPRITETYPE_SWORD_OF_THOR_DROP;
	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][0].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][0].Count				= FrameSize[EFFECTSPRITETYPE_SWORD_OF_THOR_DROP];
	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][1].EffectSpriteType	= EFFECTSPRITETYPE_SWORD_OF_THOR_EXPLODE;
	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][1].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][1].Count				= FrameSize[EFFECTSPRITETYPE_SWORD_OF_THOR_EXPLODE];
//	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
//	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][2].EffectSpriteType	= EFFECTSPRITETYPE_SWORD_OF_THOR_LOOP_ELECTIRIC_1;
//	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][2].Step				= 25;
//	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][2].SetDelayNode();
//	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][2].LinkCount			= 0;
//	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][2].Count				= FrameSize[EFFECTSPRITETYPE_SWORD_OF_THOR_LOOP_ELECTIRIC_1];
////	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_OF_THOR][3].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
////	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_OF_THOR][3].EffectSpriteType	= EFFECTSPRITETYPE_SWORD_OF_THOR_LOOP_ELECTIRIC_2;
////	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_OF_THOR][3].Step				= 25;
////	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_OF_THOR][3].SetDelayNode();
////	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_OF_THOR][3].LinkCount			= 0;
////	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_OF_THOR][3].Count				= FrameSize[EFFECTSPRITETYPE_SWORD_OF_THOR_LOOP_ELECTIRIC_2];
//	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][3].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][3].EffectSpriteType	= EFFECTSPRITETYPE_SWORD_OF_THOR_LOOP_SWORD;
//	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][3].Step				= 25;
//	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][3].SetDelayNode();
//	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][3].LinkCount			= 0;
//	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][3].Count				= FrameSize[EFFECTSPRITETYPE_SWORD_OF_THOR_LOOP_SWORD];
//	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][4].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
//	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][4].EffectSpriteType	= EFFECTSPRITETYPE_SWORD_OF_THOR_LOOP_GROUND;
//	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][4].Step				= 25;
//	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][4].SetDelayNode();
//	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][4].LinkCount			= 0;
//	(*g_pActionInfoTable)[SKILL_SWORD_OF_THOR][4].Count				= FrameSize[EFFECTSPRITETYPE_SWORD_OF_THOR_LOOP_GROUND];

	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_OF_THOR].Set("RESULT_SKILL_SWORD_OF_THOR", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_OF_THOR].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR].Set("SKILL_CLIENT_SWORD_OF_THOR", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR].Init( 3 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR][0].EffectSpriteType	= EFFECTSPRITETYPE_SWORD_OF_THOR_LOOP_SWORD;
	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR][0].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR][0].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR][0].Count				= FrameSize[EFFECTSPRITETYPE_SWORD_OF_THOR_LOOP_SWORD];
	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR][1].EffectSpriteType	= EFFECTSPRITETYPE_SWORD_OF_THOR_LOOP_GROUND;
	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR][1].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR][1].Count				= FrameSize[EFFECTSPRITETYPE_SWORD_OF_THOR_LOOP_GROUND];
	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR][2].EffectGeneratorID	= EFFECTGENERATORID_SKIP_DRAW;
	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR][2].EffectSpriteType	= EFFECTSPRITETYPE_SWORD_OF_THOR_LOOP_ELECTIRIC_1;
	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR][2].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR][2].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR][2].Count				= FrameSize[EFFECTSPRITETYPE_SWORD_OF_THOR_LOOP_ELECTIRIC_1];
//	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR][3].EffectGeneratorID	= EFFECTGENERATORID_SKIP_DRAW;
//	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR][3].EffectSpriteType	= EFFECTSPRITETYPE_SWORD_OF_THOR_LOOP_ELECTIRIC_2;
//	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR][3].Step				= 25;
//	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR][3].SetDelayNode();
//	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR][3].LinkCount			= 0;
//	(*g_pActionInfoTable)[SKILL_CLIENT_SWORD_OF_THOR][3].Count				= FrameSize[EFFECTSPRITETYPE_SWORD_OF_THOR_LOOP_ELECTIRIC_2];
//	

	(*g_pActionInfoTable)[SKILL_WHITSUNTIDE].Set("SKILL_WHITSUNTIDE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_WHITSUNTIDE].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[SKILL_WHITSUNTIDE].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[SKILL_WHITSUNTIDE].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[SKILL_WHITSUNTIDE].SetStartFrameAll( 8 );
	(*g_pActionInfoTable)[SKILL_WHITSUNTIDE].SetSoundID( SOUNDID_NULL );		
	(*g_pActionInfoTable)[SKILL_WHITSUNTIDE].Init( 3 );		
	(*g_pActionInfoTable)[SKILL_WHITSUNTIDE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_WHITSUNTIDE][0].EffectSpriteType	= EFFECTSPRITETYPE_WHITSUNTIDE;
	(*g_pActionInfoTable)[SKILL_WHITSUNTIDE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_WHITSUNTIDE][0].Count				= FrameSize[EFFECTSPRITETYPE_WHITSUNTIDE];	
	(*g_pActionInfoTable)[SKILL_WHITSUNTIDE][0].SoundID			= SOUND_SLAYER_WITHSUNTIDE;
	(*g_pActionInfoTable)[SKILL_WHITSUNTIDE][0].LinkCount				= 0;
	(*g_pActionInfoTable)[SKILL_WHITSUNTIDE][1].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_WHITSUNTIDE][1].EffectSpriteType = EFFECTSPRITETYPE_ETERNITY;
	(*g_pActionInfoTable)[SKILL_WHITSUNTIDE][1].Step						= 30;
	(*g_pActionInfoTable)[SKILL_WHITSUNTIDE][1].Count					= FrameSize[EFFECTSPRITETYPE_ETERNITY];
	(*g_pActionInfoTable)[SKILL_WHITSUNTIDE][1].LinkCount				= 0;
	(*g_pActionInfoTable)[SKILL_WHITSUNTIDE][2].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_WHITSUNTIDE][2].EffectSpriteType = EFFECTSPRITETYPE_ETERNITY_GROUND;
	(*g_pActionInfoTable)[SKILL_WHITSUNTIDE][2].Step						= 30;
	(*g_pActionInfoTable)[SKILL_WHITSUNTIDE][2].Count					= FrameSize[EFFECTSPRITETYPE_ETERNITY_GROUND];
	

	(*g_pActionInfoTable)[SKILL_WHITSUNTIDE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, RESULT_SKILL_WHITSUNTIDE );	// 맞는 결과를 표현한다.	
	
	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE].Set("RESULT_SKILL_WHITSUNTIDE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE].Init( 3 );
	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE][0].EffectSpriteType	= EFFECTSPRITETYPE_RESTORE_1;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE][0].Count				= FrameSize[EFFECTSPRITETYPE_RESTORE_1];
	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE][0].SoundID			= SOUND_SLAYER_HEALING_R1;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE][1].EffectSpriteType	= EFFECTSPRITETYPE_RESTORE_2;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE][1].Count				= FrameSize[EFFECTSPRITETYPE_RESTORE_2];
	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE][2].EffectSpriteType	= EFFECTSPRITETYPE_RESTORE_3;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE][2].Count				= FrameSize[EFFECTSPRITETYPE_RESTORE_3];
//	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE][2].SoundID			= SOUND_SLAYER_HEALING_R2;

//	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE].Set("RESULT_SKILL_WHITSUNTIDE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
//	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE].SetSoundID( SOUNDID_NULL );
//	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE].Init( 1 );		
	
//	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
//	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE][0].EffectSpriteType	= EFFECTSPRITETYPE_WHITSUNTIDE;
//	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE][0].Step				= 25;
//	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE][0].Count				= FrameSize[EFFECTSPRITETYPE_WHITSUNTIDE];	
//	(*g_pActionInfoTable)[RESULT_SKILL_WHITSUNTIDE][0].SoundID			= SOUND_SLAYER_GREAT_HEAL;;


	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_1].Set("SKILL_SWEEP_VICE_1", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_1].SetCastingActionInfo( CASTING_ENCHANT );
	//(*g_pActionInfoTable)[SKILL_SWEEP_VICE_1].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_1].SetStartFrameAll( 0 );	
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_1].SetSoundID( SOUND_SLAYER_SWEEPVICE_HIT );
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_1].Init( 2 );
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_1][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_1][0].EffectSpriteType	= EFFECTSPRITETYPE_SWEEP_VICE_START_1;
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_1][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_1][0].Count				= FrameSize[EFFECTSPRITETYPE_SWEEP_VICE_START_1];
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_1][0].LinkCount			= 5;
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_1][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_1][1].EffectSpriteType	= EFFECTSPRITETYPE_SWEEP_VICE_END_1;
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_1][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_1][1].Count				= FrameSize[EFFECTSPRITETYPE_SWEEP_VICE_END_1];	
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_1].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, RESULT_SKILL_SWEEP_VICE_1 );	// 맞는 결과를 표현한다.	

	(*g_pActionInfoTable)[RESULT_SKILL_SWEEP_VICE_1].Set("RESULT_SKILL_SWEEP_VICE_1", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_SWEEP_VICE_1].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_SWEEP_VICE_1].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_SWEEP_VICE_1][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_SWEEP_VICE_1][0].EffectSpriteType	= EFFECTSPRITETYPE_SWEEP_VICE_DAMAGED;
	(*g_pActionInfoTable)[RESULT_SKILL_SWEEP_VICE_1][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_SWEEP_VICE_1][0].Count				= FrameSize[EFFECTSPRITETYPE_SWEEP_VICE_DAMAGED];

	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_3].Set("SKILL_SWEEP_VICE_3", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET , ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_3].SetCastingActionInfo( CASTING_ENCHANT );
//	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_3].SetCastingFramesAll( 24 );
//	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_3].SetStartFrameAll( 5 );	
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_3].SetSoundID( SOUND_SLAYER_SWEEPVICE_HIT );
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_3].Init( 2 );
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_3][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_3][0].EffectSpriteType	= EFFECTSPRITETYPE_SWEEP_VICE_START_2;
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_3][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_3][0].Count				= FrameSize[EFFECTSPRITETYPE_SWEEP_VICE_START_2];
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_3][0].LinkCount			= 5;
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_3][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_3][1].EffectSpriteType	= EFFECTSPRITETYPE_SWEEP_VICE_END_2;
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_3][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_3][1].Count				= FrameSize[EFFECTSPRITETYPE_SWEEP_VICE_END_2];	
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_3].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, RESULT_SKILL_SWEEP_VICE_3 );	// 맞는 결과를 표현한다.	

	(*g_pActionInfoTable)[RESULT_SKILL_SWEEP_VICE_3].Set("RESULT_SKILL_SWEEP_VICE_3", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_SWEEP_VICE_3].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_SWEEP_VICE_3].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_SWEEP_VICE_3][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_SWEEP_VICE_3][0].EffectSpriteType	= EFFECTSPRITETYPE_SWEEP_VICE_DAMAGED;
	(*g_pActionInfoTable)[RESULT_SKILL_SWEEP_VICE_3][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_SWEEP_VICE_3][0].Count				= FrameSize[EFFECTSPRITETYPE_SWEEP_VICE_DAMAGED];

	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_5].Set("SKILL_SWEEP_VICE_5", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_5].SetCastingActionInfo( CASTING_ENCHANT );
//	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_5].SetCastingFramesAll( 24 );
//	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_5].SetStartFrameAll( 5 );	
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_5].SetSoundID( SOUND_SLAYER_SWEEPVICE_HIT );
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_5].Init( 2 );
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_5][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_5][0].EffectSpriteType	= EFFECTSPRITETYPE_SWEEP_VICE_START_3;
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_5][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_5][0].Count				= FrameSize[EFFECTSPRITETYPE_SWEEP_VICE_START_3];
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_5][0].LinkCount			= 5;
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_5][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_5][1].EffectSpriteType	= EFFECTSPRITETYPE_SWEEP_VICE_END_3;
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_5][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_5][1].Count				= FrameSize[EFFECTSPRITETYPE_SWEEP_VICE_END_3];	
	(*g_pActionInfoTable)[SKILL_SWEEP_VICE_5].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, RESULT_SKILL_SWEEP_VICE_5 );	// 맞는 결과를 표현한다.	

	(*g_pActionInfoTable)[RESULT_SKILL_SWEEP_VICE_5].Set("RESULT_SKILL_SWEEP_VICE_5", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_SWEEP_VICE_5].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_SWEEP_VICE_5].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_SWEEP_VICE_5][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_SWEEP_VICE_5][0].EffectSpriteType	= EFFECTSPRITETYPE_SWEEP_VICE_DAMAGED;
	(*g_pActionInfoTable)[RESULT_SKILL_SWEEP_VICE_5][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_SWEEP_VICE_5][0].Count				= FrameSize[EFFECTSPRITETYPE_SWEEP_VICE_DAMAGED];


	(*g_pActionInfoTable)[SKILL_INSTALL_TURRET].Set("SKILL_INSTALL_TURRET", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);	
	(*g_pActionInfoTable)[SKILL_INSTALL_TURRET].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_INSTALL_TURRET].SetSoundID( SOUNDID_NULL );
//	(*g_pActionInfoTable)[SKILL_INSTALL_TURRET].SetEffectStatus( EFFECTSTATUS_INSTALL_TURRET );
//	(*g_pActionInfoTable)[SKILL_INSTALL_TURRET].SetActionResult( ACTIONRESULTNODE_CHANGE_CREATURE_TYPE );	// 변신
	
	(*g_pActionInfoTable)[RESULT_SKILL_INSTALL_TURRET].Set("RESULT_SKILL_INSTALL_TURRET", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);	
	(*g_pActionInfoTable)[RESULT_SKILL_INSTALL_TURRET].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_INSTALL_TURRET].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_INSTALL_TURRET][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_INSTALL_TURRET][0].EffectSpriteType	= EFFECTSPRITETYPE_SUMMON_INSTALL_TURRET;
	(*g_pActionInfoTable)[RESULT_SKILL_INSTALL_TURRET][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_INSTALL_TURRET][0].Count				= FrameSize[EFFECTSPRITETYPE_SUMMON_INSTALL_TURRET];

	// SKILL_TURRET_FIRE
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE].Set("SKILL_TURRET_FIRE", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 2, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_ATTACK]);
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
//	(*g_pActionInfoTable)[SKILL_TURRET_FIRE].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE].SetSoundID( SOUNDID_NULL );	
//	(*g_pActionInfoTable)[SKILL_TURRET_FIRE].SetAffectCurrentWeaponSound();
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE].SetCastingStartFrameAll( 14 );	// 불꽃이 붙는 frame
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE].SetCastingFramesAll( 14 );
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE].SetStartFrame( 0, 14);		// slow
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE].SetStartFrame( 1, 14);		// slow
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE].SetStartFrame( 2, 14);		// slow
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE].SetRepeatFrame( 0, 14, 6);		// slow
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE].SetRepeatFrame( 1, 14, 6);		// normal
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE].SetRepeatFrame( 2, 14, 6);		// fast
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE].UseRepeatFrame();	
//	(*g_pActionInfoTable)[SKILL_TURRET_FIRE].SetRepeatLimit( 2 );
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE].Init( 3 );
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE][0].EffectSpriteType		= EFFECTSPRITETYPE_INSTALL_TURRET_FIRE1;
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE][0].Count				= FrameSize[EFFECTSPRITETYPE_INSTALL_TURRET_FIRE1];
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE][0].SoundID				= 	SOUND_SLAYER_TURRET_FIRE;
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE][0].LinkCount				= 0;

	(*g_pActionInfoTable)[SKILL_TURRET_FIRE][1].EffectGeneratorID	= EFFECTGENERATORID_AROUND_ZONE;
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE][1].EffectSpriteType		= EFFECTSPRITETYPE_INSTALL_TURRET_SCRAP1;
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE][1].Step					= 25;
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE][1].Count				= FrameSize[EFFECTSPRITETYPE_INSTALL_TURRET_SCRAP1];
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE][1].LinkCount				= 0;

	(*g_pActionInfoTable)[SKILL_TURRET_FIRE][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE][2].EffectSpriteType		= EFFECTSPRITETYPE_INSTALL_TURRET_BULLET;
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE][2].Step					= 25;
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE][2].Count				= FrameSize[EFFECTSPRITETYPE_INSTALL_TURRET_BULLET];
	(*g_pActionInfoTable)[SKILL_TURRET_FIRE][2].LinkCount				= 0;

	(*g_pActionInfoTable)[SKILL_TURRET_FIRE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, RESULT_SKILL_TURRET_FIRE );	// 맞는 결과를 표현한다.	

	(*g_pActionInfoTable)[RESULT_SKILL_TURRET_FIRE].Set("RESULT_SKILL_TURRET_FIRE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[RESULT_SKILL_TURRET_FIRE].SetSoundID( SOUNDID_NULL );


	// 2004, 9, 8, sobeit add end - 130 스킬들

	(*g_pActionInfoTable)[SKILL_CLIENT_SWEEP_VICE].Set("SKILL_CLIENT_SWEEP_VICE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_CLIENT_SWEEP_VICE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_SWEEP_VICE].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_SWEEP_VICE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_SWEEP_VICE][0].EffectSpriteType	= EFFECTSPRITETYPE_SWEEP_VICE_PRECASTING_1;
	(*g_pActionInfoTable)[SKILL_CLIENT_SWEEP_VICE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_SWEEP_VICE][0].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_SWEEP_VICE][0].Count				= 0xffff;//FrameSize[EFFECTSPRITETYPE_SWEEP_VICE_END_1];

	(*g_pActionInfoTable)[SKILL_BURNING_SOUL_CHARGING].Set("SKILL_BURNING_SOUL_CHARGING", ACTION_SLAYER_BLADE, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_BLADE_2]);
	(*g_pActionInfoTable)[SKILL_BURNING_SOUL_CHARGING].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_BURNING_SOUL_CHARGING].SetActionStepCnt(2) ;
	(*g_pActionInfoTable)[SKILL_BURNING_SOUL_CHARGING].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_BURNING_SOUL_CHARGING].Set("RESULT_SKILL_BURNING_SOUL_CHARGING", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[RESULT_SKILL_BURNING_SOUL_CHARGING].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[SKILL_BURNING_SOUL_LAUNCH].Set("SKILL_BURNING_SOUL_LAUNCH", ACTION_SLAYER_BLADE, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_BLADE]);
	(*g_pActionInfoTable)[SKILL_BURNING_SOUL_LAUNCH].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_BURNING_SOUL_LAUNCH].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, RESULT_SKILL_BURNING_SOUL_LAUNCH );	// 맞는 결과를 표현한다.	

	(*g_pActionInfoTable)[RESULT_SKILL_BURNING_SOUL_LAUNCH].Set("RESULT_SKILL_BURNING_SOUL_LAUNCH", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_BLADE]);
	(*g_pActionInfoTable)[RESULT_SKILL_BURNING_SOUL_LAUNCH].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_1].Set("SKILL_CLIENT_BURNING_SOL_1", ACTION_SLAYER_BLADE, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_1].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_1].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_1][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_1][0].EffectSpriteType	= EFFECTSPRITETYPE_BURNING_SOL_THROW_1;
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_1][0].Step				= 40;
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_1][0].Count				= FrameSize[EFFECTSPRITETYPE_BURNING_SOL_THROW_1];
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_1][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_1][1].EffectSpriteType	= EFFECTSPRITETYPE_BURNING_SOL_BLOW_3;
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_1][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_1][1].Count				= FrameSize[EFFECTSPRITETYPE_BURNING_SOL_BLOW_3];
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_1][1].SoundID			= SOUND_ITEM_BOOM3;

	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_2].Set("SKILL_CLIENT_BURNING_SOL_2", ACTION_SLAYER_BLADE, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_2].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_2].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_2][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_2][0].EffectSpriteType	= EFFECTSPRITETYPE_BURNING_SOL_THROW_2;
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_2][0].Step				= 40;
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_2][0].Count				= FrameSize[EFFECTSPRITETYPE_BURNING_SOL_THROW_2];
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_2][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_2][1].EffectSpriteType	= EFFECTSPRITETYPE_BURNING_SOL_BLOW_3;
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_2][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_2][1].Count				= FrameSize[EFFECTSPRITETYPE_BURNING_SOL_BLOW_3];
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_2][1].SoundID			= SOUND_ITEM_BOOM3;

	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_3].Set("SKILL_CLIENT_BURNING_SOL_3", ACTION_SLAYER_BLADE, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_3].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_3].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_3][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_3][0].EffectSpriteType	= EFFECTSPRITETYPE_BURNING_SOL_THROW_3;
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_3][0].Step				= 40;
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_3][0].Count				= FrameSize[EFFECTSPRITETYPE_BURNING_SOL_THROW_3];
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_3][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_3][1].EffectSpriteType	= EFFECTSPRITETYPE_BURNING_SOL_BLOW_4;
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_3][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_3][1].Count				= FrameSize[EFFECTSPRITETYPE_BURNING_SOL_BLOW_4];
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_3][1].SoundID			= SOUND_ITEM_BOOM4;

	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_4].Set("SKILL_CLIENT_BURNING_SOL_4", ACTION_SLAYER_BLADE, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_4].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_4].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_4][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_4][0].EffectSpriteType	= EFFECTSPRITETYPE_BURNING_SOL_THROW_4;
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_4][0].Step				= 40;
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_4][0].Count				= FrameSize[EFFECTSPRITETYPE_BURNING_SOL_THROW_4];
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_4][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_4][1].EffectSpriteType	= EFFECTSPRITETYPE_BURNING_SOL_BLOW_4;
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_4][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_4][1].Count				= FrameSize[EFFECTSPRITETYPE_BURNING_SOL_BLOW_4];
	(*g_pActionInfoTable)[SKILL_CLIENT_BURNING_SOL_4][1].SoundID			= SOUND_ITEM_BOOM4;

	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_1].Set("RESULT_CLIENT_BURNING_SOL_1", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_1].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_1].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_1][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_1][0].EffectSpriteType	= EFFECTSPRITETYPE_BURNING_SOL_BLOW_3;
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_1][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_1][0].Count				= FrameSize[EFFECTSPRITETYPE_BURNING_SOL_BLOW_3];
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_1][0].SoundID			= SOUND_ITEM_BOOM3;

	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_2].Set("RESULT_CLIENT_BURNING_SOL_2", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_2].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_2].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_2][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_2][0].EffectSpriteType	= EFFECTSPRITETYPE_BURNING_SOL_BLOW_3;
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_2][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_2][0].Count				= FrameSize[EFFECTSPRITETYPE_BURNING_SOL_BLOW_3];
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_2][0].SoundID			= SOUND_ITEM_BOOM3;

	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_3].Set("RESULT_CLIENT_BURNING_SOL_3", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_3].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_3].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_3][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_3][0].EffectSpriteType	= EFFECTSPRITETYPE_BURNING_SOL_BLOW_4;
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_3][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_3][0].Count				= FrameSize[EFFECTSPRITETYPE_BURNING_SOL_BLOW_4];
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_3][0].SoundID			= SOUND_ITEM_BOOM4;

	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_4].Set("RESULT_CLIENT_BURNING_SOL_4", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_4].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_4].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_4][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_4][0].EffectSpriteType	= EFFECTSPRITETYPE_BURNING_SOL_BLOW_4;
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_4][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_4][0].Count				= FrameSize[EFFECTSPRITETYPE_BURNING_SOL_BLOW_4];
	(*g_pActionInfoTable)[RESULT_CLIENT_BURNING_SOL_4][0].SoundID			= SOUND_ITEM_BOOM4;
//	// 2004, 8, 13 sobeit add end

	// 2004, 10, 25, sobeit add start
	(*g_pActionInfoTable)[SKILL_CLIENT_DRAGON_EYES].Set("SKILL_CLIENT_DRAGON_EYES",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[SKILL_CLIENT_DRAGON_EYES].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_DRAGON_EYES].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_DRAGON_EYES][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_DRAGON_EYES][0].EffectSpriteType = EFFECTSPRITETYPE_DRAGON_EYE;
	(*g_pActionInfoTable)[SKILL_CLIENT_DRAGON_EYES][0].Step						= 30;
	(*g_pActionInfoTable)[SKILL_CLIENT_DRAGON_EYES][0].Count					= FrameSize[EFFECTSPRITETYPE_DRAGON_EYE];
	(*g_pActionInfoTable)[SKILL_CLIENT_DRAGON_EYES][0].SetDelayNode();
	// 2004, 10, 25, sobeit add end

#if __CONTENTS(__HERO_SYSTEM)

	(*g_pActionInfoTable)[SKILL_CLIENT_SLAYER_HERO].Set("SKILL_CLIENT_HERO_ITEM",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[SKILL_CLIENT_SLAYER_HERO].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_SLAYER_HERO].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_SLAYER_HERO][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_SLAYER_HERO][0].EffectSpriteType = EFFECTSPRITETYPE_SLAYER_HERO;
	(*g_pActionInfoTable)[SKILL_CLIENT_SLAYER_HERO][0].Step						= 30;
	(*g_pActionInfoTable)[SKILL_CLIENT_SLAYER_HERO][0].Count					= FrameSize[EFFECTSPRITETYPE_SLAYER_HERO];
	(*g_pActionInfoTable)[SKILL_CLIENT_SLAYER_HERO][0].SetDelayNode();

	(*g_pActionInfoTable)[SKILL_CLIENT_OUSTERS_HERO].Set("SKILL_CLIENT_HERO_ITEM",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[SKILL_CLIENT_OUSTERS_HERO].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_OUSTERS_HERO].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_OUSTERS_HERO][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_OUSTERS_HERO][0].EffectSpriteType = EFFECTSPRITETYPE_OUSTERS_HERO;
	(*g_pActionInfoTable)[SKILL_CLIENT_OUSTERS_HERO][0].Step						= 30;
	(*g_pActionInfoTable)[SKILL_CLIENT_OUSTERS_HERO][0].Count					= FrameSize[EFFECTSPRITETYPE_OUSTERS_HERO];
	(*g_pActionInfoTable)[SKILL_CLIENT_OUSTERS_HERO][0].SetDelayNode();

	(*g_pActionInfoTable)[SKILL_CLIENT_VAMPIRE_HERO].Set("SKILL_CLIENT_HERO_ITEM",ACTION_STAND,EFFECTSPRITETYPE_NULL,10,FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[SKILL_CLIENT_VAMPIRE_HERO].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_VAMPIRE_HERO].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_VAMPIRE_HERO][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_VAMPIRE_HERO][0].EffectSpriteType = EFFECTSPRITETYPE_VAMPIRE_HERO;
	(*g_pActionInfoTable)[SKILL_CLIENT_VAMPIRE_HERO][0].Step						= 30;
	(*g_pActionInfoTable)[SKILL_CLIENT_VAMPIRE_HERO][0].Count					= FrameSize[EFFECTSPRITETYPE_VAMPIRE_HERO];
	(*g_pActionInfoTable)[SKILL_CLIENT_VAMPIRE_HERO][0].SetDelayNode();

#endif //__HERO_SYSTEM

#if __CONTENTS(__FAST_TRANSFORTER)
	(*g_pActionInfoTable)[SKILL_CLIENT_SLAYER_WING].Set("SKILL_CLIENT_SLAYER_WING", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[SKILL_CLIENT_SLAYER_WING].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_SLAYER_WING].SetEffectStatus(EFFECTSTATUS_CLIENT_WING_HELLBIKE);
#endif //__FAST_TRANSFORTER

#if __CONTENTS(__SECOND_TRANSFORTER)
	(*g_pActionInfoTable)[SKILL_CLIENT_SLAYER_HOVER_VEHICLE].Set("SKILL_CLIENT_SLAYER_HOVER_VEHICLE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[SKILL_CLIENT_SLAYER_HOVER_VEHICLE].SetSoundID( SOUND_HOVER_VEHICLE );
	(*g_pActionInfoTable)[SKILL_CLIENT_SLAYER_HOVER_VEHICLE].SetEffectStatus(EFFECTSTATUS_CLIENT_HOVER_VEHICLE);
#endif //__SECOND_TRANSFORTER

	// 2004, 11, 8, sobeit add start
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT].Set("SKILL_INFINITY_THUNDERBOLT", ACTION_SLAYER_SWORD_2, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD_2]);
	//(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT].SetCastingEffectToOther();	// casting effect를 다른 사람에게 붙인다.
	//(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT].SetUser(FLAG_ACTIONINFO_USER_ALL & ~FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT].SetSoundID( SOUND_SLAYER_SWORDOFTHOR );
//	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT].SetCastingStartFrameAll( 1 );	// 불꽃이 붙는 frame
//	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT].UseRepeatFrame();	
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT].SetStartFrame( 0, 7 );			// slow
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT].SetStartFrame( 1, 7 );			// normal
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT].SetStartFrame( 2, 7 );			// fast
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT].SetCastingStartFrame( 0, 7 );	// slow
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT].SetCastingStartFrame( 1, 7 );	// normal
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT].SetCastingStartFrame( 2, 7 );	// fast
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT].SetCastingFrames( 0, 10 );		// slow
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT].SetCastingFrames( 1, 10 );		// normal
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT].SetCastingFrames( 2, 10 );		// fast
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT].SetRepeatFrame( 0, 7, 11 );		// slow
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT].SetRepeatFrame( 1, 7, 11 );		// normal
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT].SetRepeatFrame( 2, 7, 11 );		// fast
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, RESULT_SKILL_INFINITY_THUNDERBOLT );	// 맞는 결과를 표현한다.	
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT].Init( 2 );		


	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_INFINITY_THUNDERBOLT ; //FFECTSPRITETYPE_INFINITY_THUNDERBOLT_GROUND;
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_INFINITY_THUNDERBOLT] ; // EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_GROUND];
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT][0].LinkCount			= 5;


	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT][1].EffectSpriteType	= EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_CENTER;
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT][1].Count				= FrameSize[EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_CENTER] ;
	//(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT][0].LinkCount			= 5;
	

//	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT][0].EffectSpriteType	= EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_CENTER;
//	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT][0].Step				= 25;
//	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT][0].Count				= FrameSize[EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_CENTER] ;
//	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT][0].LinkCount			= 5;
//	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
//	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT][1].EffectSpriteType	= EFFECTSPRITETYPE_NEW_INFINITY_THUNDERBOLT ; //FFECTSPRITETYPE_INFINITY_THUNDERBOLT_GROUND;
//	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT][1].Step				= 25;
//	(*g_pActionInfoTable)[SKILL_INFINITY_THUNDERBOLT][1].Count				= FrameSize[EFFECTSPRITETYPE_NEW_INFINITY_THUNDERBOLT] ; // EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_GROUND];




	(*g_pActionInfoTable)[RESULT_SKILL_INFINITY_THUNDERBOLT].Set("RESULT_SKILL_INFINITY_THUNDERBOLT", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_INFINITY_THUNDERBOLT].SetSoundID( SOUNDID_NULL );
	
#if __CONTENTS(__SECOND_RARE_SKILL)
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK].Set("SKILL_HEAVENLY_SPARK", ACTION_SLAYER_SWORD_2, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD_2]);
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK].SetUser(FLAG_ACTIONINFO_USER_ALL & ~FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK].SetSoundID( SOUND_HEAVENLY_SPARK );
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK].UseRepeatFrame();	
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK].SetStartFrame( 0, 7 );			// slow
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK].SetStartFrame( 1, 7 );			// normal
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK].SetStartFrame( 2, 7 );			// fast
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK].SetCastingStartFrame( 0, 7 );	// slow
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK].SetCastingStartFrame( 1, 7 );	// normal
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK].SetCastingStartFrame( 2, 7 );	// fast
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK].SetCastingFrames( 0, 10 );		// slow
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK].SetCastingFrames( 1, 10 );		// normal
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK].SetCastingFrames( 2, 10 );		// fast
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK].SetRepeatFrame( 0, 7, 11 );		// slow
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK].SetRepeatFrame( 1, 7, 11 );		// normal
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK].SetRepeatFrame( 2, 7, 11 );		// fast
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, RESULT_SKILL_HEAVENLY_SPARK );	// 맞는 결과를 표현한다.	
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK][0].EffectSpriteType	= EFFECTSPRITETYPE_HEAVENLY_SPARK_GROUND; //FFECTSPRITETYPE_INFINITY_THUNDERBOLT_GROUND;
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK][0].Count				= FrameSize[EFFECTSPRITETYPE_HEAVENLY_SPARK_GROUND] ; // EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_GROUND];
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK][0].LinkCount			= 5;
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK][1].EffectSpriteType	= EFFECTSPRITETYPE_HEAVENLY_SPARK_CENTER;
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_HEAVENLY_SPARK][1].Count				= FrameSize[EFFECTSPRITETYPE_HEAVENLY_SPARK_CENTER] ;

	(*g_pActionInfoTable)[RESULT_SKILL_HEAVENLY_SPARK].Set("RESULT_SKILL_HEAVENLY_SPARK", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVENLY_SPARK].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[SKILL_BLADE_STORM].Set("SKILL_BLADE_STORM", ACTION_SLAYER_BLADE_2, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_SWORD_2]);
	(*g_pActionInfoTable)[SKILL_BLADE_STORM].SetCastingEffectToOther();	// casting effect를 다른 사람에게 붙인다.
	(*g_pActionInfoTable)[SKILL_BLADE_STORM].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_BLADE_STORM].SetActionStepCnt(2) ;
	(*g_pActionInfoTable)[SKILL_BLADE_STORM].SetSoundID( SOUND_SPIT_STREAM) ; //SOUND_ITEM_FLYING_BOMB );
	(*g_pActionInfoTable)[SKILL_BLADE_STORM].UseRepeatFrame();	
	(*g_pActionInfoTable)[SKILL_BLADE_STORM].SetStartFrame( 0, 9 );			// slow
	(*g_pActionInfoTable)[SKILL_BLADE_STORM].SetStartFrame( 1, 9 );			// normal
	(*g_pActionInfoTable)[SKILL_BLADE_STORM].SetStartFrame( 2, 9 );			// fast
	(*g_pActionInfoTable)[SKILL_BLADE_STORM].SetCastingStartFrame( 0, 9 );	// slow
	(*g_pActionInfoTable)[SKILL_BLADE_STORM].SetCastingStartFrame( 1, 9 );	// normal
	(*g_pActionInfoTable)[SKILL_BLADE_STORM].SetCastingStartFrame( 2, 9 );	// fast
	(*g_pActionInfoTable)[SKILL_BLADE_STORM].SetRepeatFrame( 0, 9, 13 );		// slow
	(*g_pActionInfoTable)[SKILL_BLADE_STORM].SetRepeatFrame( 1, 9, 13 );		// normal
	(*g_pActionInfoTable)[SKILL_BLADE_STORM].SetRepeatFrame( 2, 9, 13 );		// fast
	(*g_pActionInfoTable)[SKILL_BLADE_STORM].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_BLADE_STORM][0].EffectGeneratorID	= EFFECTGENERATORID_AROUND_ZONE  ;
	(*g_pActionInfoTable)[SKILL_BLADE_STORM][0].EffectSpriteType	= EFFECTSPRITETYPE_BLADE_STORM;
	(*g_pActionInfoTable)[SKILL_BLADE_STORM][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_BLADE_STORM][0].Count				= FrameSize[EFFECTSPRITETYPE_BLADE_STORM];
	(*g_pActionInfoTable)[SKILL_BLADE_STORM][0].SetResultTime();

	(*g_pActionInfoTable)[RESULT_SKILL_BLADE_STORM].Set("RESULT_SKILL_BLADE_STORM", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_BLADE_STORM].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[SKILL_XRL].Set("SKILL_XRL", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_NEW_PLASMA_ROCKET_LAUNCHER_FIRE, 3, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[SKILL_XRL].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_XRL].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_XRL].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_XRL].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_XRL].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_XRL].SetCastingStartFrameAll( 7 );	// 불꽃이 붙는 frame
	(*g_pActionInfoTable)[SKILL_XRL].SetCastingFramesAll( 7 );
	(*g_pActionInfoTable)[SKILL_XRL].SetStartFrame( 0, 5 );			// slow
	(*g_pActionInfoTable)[SKILL_XRL].SetStartFrame( 1, 5 );			// normal
	(*g_pActionInfoTable)[SKILL_XRL].SetStartFrame( 2, 5 );			// fast
	(*g_pActionInfoTable)[SKILL_XRL].UseRepeatFrame();	
	(*g_pActionInfoTable)[SKILL_XRL].SetRepeatFrame( 0, 5, 10);		// slow
	(*g_pActionInfoTable)[SKILL_XRL].SetRepeatFrame( 1, 5, 10);		// normal
	(*g_pActionInfoTable)[SKILL_XRL].SetRepeatFrame( 2, 5, 10);		// fast
	
	(*g_pActionInfoTable)[RESULT_SKILL_XRL].Set("RESULT_SKILL_XRL", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_XRL].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[SKILL_CLIENT_XRL_BLOW].Set("SKILL_CLIENT_XRL_BLOW", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER , FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_DAMAGED]);
	(*g_pActionInfoTable)[SKILL_CLIENT_XRL_BLOW].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_XRL_BLOW].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_XRL_BLOW][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_XRL_BLOW][0].EffectSpriteType	= EFFECTSPRITETYPE_XRL_EXPLOSION;
	(*g_pActionInfoTable)[SKILL_CLIENT_XRL_BLOW][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_XRL_BLOW][0].Count				= FrameSize[EFFECTSPRITETYPE_XRL_EXPLOSION];
	(*g_pActionInfoTable)[SKILL_CLIENT_XRL_BLOW][0].SoundID			= SOUND_SLAYER_PLASMA_ROCKET_LAUNCHER;

	(*g_pActionInfoTable)[SKILL_GENESIS].Set("SKILL_GENESIS", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_GENESIS].SetCastingActionInfo( CASTING_HEALING );
	(*g_pActionInfoTable)[SKILL_GENESIS].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_GENESIS].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_GENESIS].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, RESULT_SKILL_GENESIS );	// 맞는 결과를 표현한다.	
	(*g_pActionInfoTable)[SKILL_GENESIS].Init( 2 );
	(*g_pActionInfoTable)[SKILL_GENESIS][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_GENESIS][0].EffectSpriteType	= EFFECTSPRITETYPE_GENESIS_DROP;
	(*g_pActionInfoTable)[SKILL_GENESIS][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_GENESIS][0].Count				= 8; //FrameSize[EFFECTSPRITETYPE_GENESIS_DROP];
	(*g_pActionInfoTable)[SKILL_GENESIS][0].SoundID				= SOUND_SLAYER_BOMBING_STAR;
	(*g_pActionInfoTable)[SKILL_GENESIS][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_GENESIS][1].EffectSpriteType	= EFFECTSPRITETYPE_GENESIS_BLOW;
	(*g_pActionInfoTable)[SKILL_GENESIS][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_GENESIS][1].Count				= FrameSize[EFFECTSPRITETYPE_GENESIS_BLOW];
	
	(*g_pActionInfoTable)[RESULT_SKILL_GENESIS].Set("RESULT_SKILL_GENESIS", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_GENESIS].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[SKILL_THORNS].Set("SKILL_THORNS", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_THORNS].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[SKILL_THORNS].SetCastingActionInfo( CASTING_ENCHANT );
	(*g_pActionInfoTable)[SKILL_THORNS].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[SKILL_THORNS].SetStartFrameAll( 7 );
	(*g_pActionInfoTable)[SKILL_THORNS].SetSoundID( SOUNDID_NULL );	
	(*g_pActionInfoTable)[SKILL_THORNS].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, RESULT_SKILL_THORNS );
	(*g_pActionInfoTable)[SKILL_THORNS].Init( 1 );
	(*g_pActionInfoTable)[SKILL_THORNS][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE; //벰스킬 나오는 것때문에 잠시 추가.
	(*g_pActionInfoTable)[SKILL_THORNS][0].EffectSpriteType		= EFFECTSPRITETYPE_NULL;
	(*g_pActionInfoTable)[SKILL_THORNS][0].Step					= 0;
	(*g_pActionInfoTable)[SKILL_THORNS][0].Count				= 25;
	(*g_pActionInfoTable)[SKILL_THORNS][0].SoundID				= SOUND_SLAYER_BOMBING_STAR;
	
	(*g_pActionInfoTable)[RESULT_SKILL_THORNS].Set("RESULT_SKILL_THORNS", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_THORNS].SetSoundID(SOUND_SLAYER_SPIRIT_GUARD) ;
#endif //__SECOND_RARE_SKILL
	
#if __CONTENTS(__TIPOJYU_CASTLE)	//스킬 추가

	//현세 문지기 스킬
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_BLUE].Set("SKILL_SPIT_STREAM", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_SWORD_2]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_BLUE].SetCastingEffectToOther();	// casting effect를 다른 사람에게 붙인다.
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_BLUE].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_BLUE].SetActionStepCnt(2) ;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_BLUE].SetSoundID( SOUND_SPIT_STREAM) ; //SOUND_ITEM_FLYING_BOMB );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_BLUE].UseRepeatFrame();	
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_BLUE].SetStartFrame( 0, 9 );			// slow
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_BLUE].SetStartFrame( 1, 9 );			// normal
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_BLUE].SetStartFrame( 2, 9 );			// fast
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_BLUE].SetCastingStartFrame( 0, 9 );	// slow
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_BLUE].SetCastingStartFrame( 1, 9 );	// normal
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_BLUE].SetCastingStartFrame( 2, 9 );	// fast
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_BLUE].SetRepeatFrame( 0, 9, 13 );		// slow
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_BLUE].SetRepeatFrame( 1, 9, 13 );		// normal
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_BLUE].SetRepeatFrame( 2, 9, 13 );		// fast
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_BLUE].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_BLUE][0].EffectGeneratorID	= EFFECTGENERATORID_AROUND_ZONE  ;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_BLUE][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_LIFE_GATEKEEPER_ATTACK_A;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_BLUE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_BLUE][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_LIFE_GATEKEEPER_ATTACK_A];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_BLUE][0].SetResultTime();

	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_BALBERITH_BLUE].Set("RESULT_SKILL_TIFFAUGES_BALBERITH_BLUE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_BALBERITH_BLUE].SetSoundID( SOUNDID_NULL );

	//이계 문지기 스킬
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_RED].Set("SKILL_TIFFAUGES_BALBERITH_RED", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_SWORD_2]);
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_RED].SetCastingEffectToOther();	// casting effect를 다른 사람에게 붙인다.
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_RED].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_RED].SetActionStepCnt(2) ;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_RED].SetSoundID( SOUND_SPIT_STREAM) ; //SOUND_ITEM_FLYING_BOMB );
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_RED].UseRepeatFrame();	
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_RED].SetStartFrame( 0, 9 );			// slow
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_RED].SetStartFrame( 1, 9 );			// normal
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_RED].SetStartFrame( 2, 9 );			// fast
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_RED].SetCastingStartFrame( 0, 9 );	// slow
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_RED].SetCastingStartFrame( 1, 9 );	// normal
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_RED].SetCastingStartFrame( 2, 9 );	// fast
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_RED].SetRepeatFrame( 0, 9, 13 );		// slow
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_RED].SetRepeatFrame( 1, 9, 13 );		// normal
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_RED].SetRepeatFrame( 2, 9, 13 );		// fast
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_RED].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_RED][0].EffectGeneratorID	= EFFECTGENERATORID_AROUND_ZONE  ;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_RED][0].EffectSpriteType	= EFFECTSPRITETYPE_TIPOJYU_HADES_GATEKEEPER_ATTACK_A;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_RED][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_RED][0].Count				= FrameSize[EFFECTSPRITETYPE_TIPOJYU_HADES_GATEKEEPER_ATTACK_A];
	(*g_pActionInfoTable)[SKILL_TIFFAUGES_BALBERITH_RED][0].SetResultTime();

	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_BALBERITH_RED].Set("RESULT_SKILL_TIFFAUGES_BALBERITH_RED", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_TIFFAUGES_BALBERITH_RED].SetSoundID( SOUNDID_NULL );

#endif // __TIPOJYU_CASTLE

	(*g_pActionInfoTable)[SKILL_SPIT_STREAM].Set("SKILL_SPIT_STREAM", ACTION_SLAYER_BLADE_2, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_SWORD_2]);
	(*g_pActionInfoTable)[SKILL_SPIT_STREAM].SetCastingEffectToOther();	// casting effect를 다른 사람에게 붙인다.
	(*g_pActionInfoTable)[SKILL_SPIT_STREAM].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_SPIT_STREAM].SetActionStepCnt(2) ;
	(*g_pActionInfoTable)[SKILL_SPIT_STREAM].SetSoundID( SOUND_SPIT_STREAM) ; //SOUND_ITEM_FLYING_BOMB );
	(*g_pActionInfoTable)[SKILL_SPIT_STREAM].UseRepeatFrame();	
	(*g_pActionInfoTable)[SKILL_SPIT_STREAM].SetStartFrame( 0, 9 );			// slow
	(*g_pActionInfoTable)[SKILL_SPIT_STREAM].SetStartFrame( 1, 9 );			// normal
	(*g_pActionInfoTable)[SKILL_SPIT_STREAM].SetStartFrame( 2, 9 );			// fast
	(*g_pActionInfoTable)[SKILL_SPIT_STREAM].SetCastingStartFrame( 0, 9 );	// slow
	(*g_pActionInfoTable)[SKILL_SPIT_STREAM].SetCastingStartFrame( 1, 9 );	// normal
	(*g_pActionInfoTable)[SKILL_SPIT_STREAM].SetCastingStartFrame( 2, 9 );	// fast
	(*g_pActionInfoTable)[SKILL_SPIT_STREAM].SetRepeatFrame( 0, 9, 13 );		// slow
	(*g_pActionInfoTable)[SKILL_SPIT_STREAM].SetRepeatFrame( 1, 9, 13 );		// normal
	(*g_pActionInfoTable)[SKILL_SPIT_STREAM].SetRepeatFrame( 2, 9, 13 );		// fast
	(*g_pActionInfoTable)[SKILL_SPIT_STREAM].Init( 1 );	
	(*g_pActionInfoTable)[SKILL_SPIT_STREAM][0].EffectGeneratorID	= EFFECTGENERATORID_AROUND_ZONE  ;
	(*g_pActionInfoTable)[SKILL_SPIT_STREAM][0].EffectSpriteType	= EFFECTSPRITETYPE_SPIT_STREAM;
	(*g_pActionInfoTable)[SKILL_SPIT_STREAM][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SPIT_STREAM][0].Count				= FrameSize[EFFECTSPRITETYPE_SPIT_STREAM];
	(*g_pActionInfoTable)[SKILL_SPIT_STREAM][0].SetResultTime();

	(*g_pActionInfoTable)[RESULT_SKILL_SPIT_STREAM].Set("RESULT_SKILL_SPIT_STREAM", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_SPIT_STREAM].SetSoundID( SOUNDID_NULL );


	(*g_pActionInfoTable)[SKILL_INTIMATE_GRAIL].Set("SKILL_INTIMATE_GRAIL", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_INTIMATE_GRAIL].SetSoundID( SOUNDID_NULL );		
	(*g_pActionInfoTable)[SKILL_INTIMATE_GRAIL].SetStartWithCasting();
	//(*g_pActionInfoTable)[SKILL_INTIMATE_GRAIL].SetUser(FLAG_ACTIONINFO_USER_SLAYER | FLAG_ACTIONINFO_USER_VAMPIRE | FLAG_ACTIONINFO_USER_OUSTERS);
	
	(*g_pActionInfoTable)[RESULT_SKILL_INTIMATE_GRAIL].Set("RESULT_SKILL_INTIMATE_GRAIL", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_INTIMATE_GRAIL].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_INTIMATE_GRAIL].Init( 3 );		
	(*g_pActionInfoTable)[RESULT_SKILL_INTIMATE_GRAIL][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE  ;
	(*g_pActionInfoTable)[RESULT_SKILL_INTIMATE_GRAIL][0].EffectSpriteType	= EFFECTSPRITETYPE_INTIMATE_GRAIL_LIGHT;
	(*g_pActionInfoTable)[RESULT_SKILL_INTIMATE_GRAIL][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_INTIMATE_GRAIL][0].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_INTIMATE_GRAIL][0].SoundID			= SOUND_SLAYER_INTIMATE_GRAIL;
	(*g_pActionInfoTable)[RESULT_SKILL_INTIMATE_GRAIL][0].Count				= FrameSize[EFFECTSPRITETYPE_INTIMATE_GRAIL_LIGHT];
	(*g_pActionInfoTable)[RESULT_SKILL_INTIMATE_GRAIL][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE  ;
	(*g_pActionInfoTable)[RESULT_SKILL_INTIMATE_GRAIL][1].EffectSpriteType	= EFFECTSPRITETYPE_INTIMATE_GRAIL_DROP_1;
	(*g_pActionInfoTable)[RESULT_SKILL_INTIMATE_GRAIL][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_INTIMATE_GRAIL][1].Count				= FrameSize[EFFECTSPRITETYPE_INTIMATE_GRAIL_DROP_1];
	(*g_pActionInfoTable)[RESULT_SKILL_INTIMATE_GRAIL][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE  ;
	(*g_pActionInfoTable)[RESULT_SKILL_INTIMATE_GRAIL][2].EffectSpriteType	= EFFECTSPRITETYPE_INTIMATE_GRAIL_DROP_2;
	(*g_pActionInfoTable)[RESULT_SKILL_INTIMATE_GRAIL][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_INTIMATE_GRAIL][2].Count				= FrameSize[EFFECTSPRITETYPE_INTIMATE_GRAIL_DROP_2];


	(*g_pActionInfoTable)[SKILL_BOMBING_STAR].Set("SKILL_BOMBING_STAR", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_BOMBING_STAR].SetCastingActionInfo( CASTING_HEALING );
	(*g_pActionInfoTable)[SKILL_BOMBING_STAR].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_BOMBING_STAR].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_BOMBING_STAR].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, RESULT_SKILL_BOMBING_STAR );	// 맞는 결과를 표현한다.	
	(*g_pActionInfoTable)[SKILL_BOMBING_STAR].Init( 2 );
	(*g_pActionInfoTable)[SKILL_BOMBING_STAR][0].EffectGeneratorID	= EFFECTGENERATORID_FALLING;
	(*g_pActionInfoTable)[SKILL_BOMBING_STAR][0].EffectSpriteType		= EFFECTSPRITETYPE_BOMBING_STAR_DROP;
	(*g_pActionInfoTable)[SKILL_BOMBING_STAR][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_BOMBING_STAR][0].Count				= FrameSize[EFFECTSPRITETYPE_BOMBING_STAR_DROP]*2;
	(*g_pActionInfoTable)[SKILL_BOMBING_STAR][0].SoundID				= SOUND_SLAYER_BOMBING_STAR;
	(*g_pActionInfoTable)[SKILL_BOMBING_STAR][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_BOMBING_STAR][1].EffectSpriteType		= EFFECTSPRITETYPE_BOMBING_STAR_BLOW;
	(*g_pActionInfoTable)[SKILL_BOMBING_STAR][1].Step					= 25;
	(*g_pActionInfoTable)[SKILL_BOMBING_STAR][1].Count				= FrameSize[EFFECTSPRITETYPE_BOMBING_STAR_BLOW];


	(*g_pActionInfoTable)[RESULT_SKILL_BOMBING_STAR].Set("RESULT_SKILL_BOMBING_STAR", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_BOMBING_STAR].SetSoundID( SOUNDID_NULL );
	

	(*g_pActionInfoTable)[SKILL_PLASMA_ROCKET_LAUNCHER].Set("SKILL_PLASMA_ROCKET_LAUNCHER", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_NEW_PLASMA_ROCKET_LAUNCHER_FIRE, 3, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[SKILL_PLASMA_ROCKET_LAUNCHER].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_PLASMA_ROCKET_LAUNCHER].SetAffectCurrentWeaponAction();
//	(*g_pActionInfoTable)[SKILL_PLASMA_ROCKET_LAUNCHER].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_PLASMA_ROCKET_LAUNCHER].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
//	(*g_pActionInfoTable)[SKILL_PLASMA_ROCKET_LAUNCHER].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
//	(*g_pActionInfoTable)[SKILL_PLASMA_ROCKET_LAUNCHER].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_PLASMA_ROCKET_LAUNCHER].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
//	//(*g_pActionInfoTable)[SKILL_PLASMA_ROCKET_LAUNCHER].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용
	(*g_pActionInfoTable)[SKILL_PLASMA_ROCKET_LAUNCHER].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_PLASMA_ROCKET_LAUNCHER].SetCastingStartFrameAll( 7 );	// 불꽃이 붙는 frame
	(*g_pActionInfoTable)[SKILL_PLASMA_ROCKET_LAUNCHER].SetCastingFramesAll( 7 );
//	(*g_pActionInfoTable)[SKILL_PLASMA_ROCKET_LAUNCHER].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_BULLET_OF_LIGHT );	// 맞는 결과를 표현한다.	
	(*g_pActionInfoTable)[SKILL_PLASMA_ROCKET_LAUNCHER].SetStartFrame( 0, 5 );			// slow
	(*g_pActionInfoTable)[SKILL_PLASMA_ROCKET_LAUNCHER].SetStartFrame( 1, 5 );			// normal
	(*g_pActionInfoTable)[SKILL_PLASMA_ROCKET_LAUNCHER].SetStartFrame( 2, 5 );			// fast
	(*g_pActionInfoTable)[SKILL_PLASMA_ROCKET_LAUNCHER].UseRepeatFrame();	
	(*g_pActionInfoTable)[SKILL_PLASMA_ROCKET_LAUNCHER].SetRepeatFrame( 0, 5, 10);		// slow
	(*g_pActionInfoTable)[SKILL_PLASMA_ROCKET_LAUNCHER].SetRepeatFrame( 1, 5, 10);		// normal
	(*g_pActionInfoTable)[SKILL_PLASMA_ROCKET_LAUNCHER].SetRepeatFrame( 2, 5, 10);		// fast
	
	(*g_pActionInfoTable)[RESULT_SKILL_PLASMA_ROCKET_LAUNCHER].Set("RESULT_SKILL_PLASMA_ROCKET_LAUNCHER", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_PLASMA_ROCKET_LAUNCHER].SetSoundID( SOUNDID_NULL );
	
	// 2004, 11, 8, sobeit add end

//	// 2004, 11, 22, sobeit add start
//	(*g_pActionInfoTable)[SKILL_CLIENT_BLOOD_BIBLE_IN_GEAR_WINDOW].Set("SKILL_CLIENT_BLOOD_BIBLE_IN_GEAR_WINDOW", ACTION_STAND, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ITEM , FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_STAND]);
//	(*g_pActionInfoTable)[SKILL_CLIENT_BLOOD_BIBLE_IN_GEAR_WINDOW].SetStartWithCasting();
//	(*g_pActionInfoTable)[SKILL_CLIENT_BLOOD_BIBLE_IN_GEAR_WINDOW].SetMainNode( 1 );
//	(*g_pActionInfoTable)[SKILL_CLIENT_BLOOD_BIBLE_IN_GEAR_WINDOW].SetSoundID( SOUNDID_NULL );
//	(*g_pActionInfoTable)[SKILL_CLIENT_BLOOD_BIBLE_IN_GEAR_WINDOW].Init( 1 );
//	(*g_pActionInfoTable)[SKILL_CLIENT_BLOOD_BIBLE_IN_GEAR_WINDOW][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_GEAR;
//	(*g_pActionInfoTable)[SKILL_CLIENT_BLOOD_BIBLE_IN_GEAR_WINDOW][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_BIBLE_IN_GEAR;
//	(*g_pActionInfoTable)[SKILL_CLIENT_BLOOD_BIBLE_IN_GEAR_WINDOW][0].Step				= 25;
//	(*g_pActionInfoTable)[SKILL_CLIENT_BLOOD_BIBLE_IN_GEAR_WINDOW][0].Count				= 0xffff/* FrameSize[EFFECTSPRITETYPE_BLOODY_BIBLE_IN_GEAR]*/;
//	// 2004, 11, 22, sobeit add end
	
	
	(*g_pActionInfoTable)[SKILL_CLIENT_PLASMA_ROCKET_LAUNCHER_BLOW].Set("SKILL_CLIENT_PLASMA_ROCKET_LAUNCHER_BLOW", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER , FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_DAMAGED]);
	(*g_pActionInfoTable)[SKILL_CLIENT_PLASMA_ROCKET_LAUNCHER_BLOW].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_PLASMA_ROCKET_LAUNCHER_BLOW].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_PLASMA_ROCKET_LAUNCHER_BLOW][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_PLASMA_ROCKET_LAUNCHER_BLOW][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_PLASMA_ROCKET_LAUNCHER_BLOW;
	(*g_pActionInfoTable)[SKILL_CLIENT_PLASMA_ROCKET_LAUNCHER_BLOW][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_PLASMA_ROCKET_LAUNCHER_BLOW][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_PLASMA_ROCKET_LAUNCHER_BLOW];
	(*g_pActionInfoTable)[SKILL_CLIENT_PLASMA_ROCKET_LAUNCHER_BLOW][0].SoundID			= SOUND_SLAYER_PLASMA_ROCKET_LAUNCHER;
	
	// 2005, 1, 3, sobeit add start - 승직 스킬들
	(*g_pActionInfoTable)[SKILL_ROTTEN_APPLE].Set("SKILL_ROTTEN_APPLE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_ROTTEN_APPLE].SetSoundID( SOUNDID_NULL );		
	(*g_pActionInfoTable)[SKILL_ROTTEN_APPLE].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_ROTTEN_APPLE].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, RESULT_SKILL_ROTTEN_APPLE );	// 맞는 결과를 표현한다.	
	
	(*g_pActionInfoTable)[SKILL_CLIENT_ROTTEN_APPLE].Set("RESULT_SKILL_INTIMATE_GRAIL", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[SKILL_CLIENT_ROTTEN_APPLE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_ROTTEN_APPLE].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_ROTTEN_APPLE][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE  ;
	(*g_pActionInfoTable)[SKILL_CLIENT_ROTTEN_APPLE][0].EffectSpriteType	= EFFECTSPRITETYPE_ROTTEN_APPLE;
	(*g_pActionInfoTable)[SKILL_CLIENT_ROTTEN_APPLE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_ROTTEN_APPLE][0].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_CLIENT_ROTTEN_APPLE][0].Count				= FrameSize[EFFECTSPRITETYPE_ROTTEN_APPLE];

	(*g_pActionInfoTable)[RESULT_SKILL_ROTTEN_APPLE].Set("RESULT_SKILL_ROTTEN_APPLE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_ROTTEN_APPLE].SetSoundID( SOUND_SLAYER_ROTTEN_APPLE) ;//SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_ROTTEN_APPLE].Init( 4 );
	(*g_pActionInfoTable)[RESULT_SKILL_ROTTEN_APPLE][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_ROTTEN_APPLE][0].EffectSpriteType = EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_1;
	(*g_pActionInfoTable)[RESULT_SKILL_ROTTEN_APPLE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ROTTEN_APPLE][0].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_1]*2;
	(*g_pActionInfoTable)[RESULT_SKILL_ROTTEN_APPLE][0].LinkCount			= 2;
	(*g_pActionInfoTable)[RESULT_SKILL_ROTTEN_APPLE][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_ROTTEN_APPLE][1].EffectSpriteType = EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_2;
	(*g_pActionInfoTable)[RESULT_SKILL_ROTTEN_APPLE][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ROTTEN_APPLE][1].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_2]*2;
	(*g_pActionInfoTable)[RESULT_SKILL_ROTTEN_APPLE][1].LinkCount			= 2;
	(*g_pActionInfoTable)[RESULT_SKILL_ROTTEN_APPLE][2].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_ROTTEN_APPLE][2].EffectSpriteType = EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_3;
	(*g_pActionInfoTable)[RESULT_SKILL_ROTTEN_APPLE][2].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ROTTEN_APPLE][2].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_3]*2;
	(*g_pActionInfoTable)[RESULT_SKILL_ROTTEN_APPLE][2].LinkCount			= 4;
	(*g_pActionInfoTable)[RESULT_SKILL_ROTTEN_APPLE][3].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_ROTTEN_APPLE][3].EffectSpriteType = EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_4;
	(*g_pActionInfoTable)[RESULT_SKILL_ROTTEN_APPLE][3].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ROTTEN_APPLE][3].Count				= FrameSize[EFFECTSPRITETYPE_VIOLENT_PHANTOM_BLOOD_4]*2;
	(*g_pActionInfoTable)[RESULT_SKILL_ROTTEN_APPLE][3].LinkCount			= 4;

	(*g_pActionInfoTable)[SKILL_PASSING_HEAL].Set("SKILL_PASSING_HEAL", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_PASSING_HEAL].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[SKILL_PASSING_HEAL].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[SKILL_PASSING_HEAL].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_PASSING_HEAL].SetSoundID( SOUNDID_NULL );		
	(*g_pActionInfoTable)[SKILL_PASSING_HEAL].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[SKILL_PASSING_HEAL].Init( 3 );		
	(*g_pActionInfoTable)[SKILL_PASSING_HEAL][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE;
	(*g_pActionInfoTable)[SKILL_PASSING_HEAL][0].EffectSpriteType	= EFFECTSPRITETYPE_VISIBLE_1;
	(*g_pActionInfoTable)[SKILL_PASSING_HEAL][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_PASSING_HEAL][0].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_PASSING_HEAL][0].Count				= 2*16;	//FrameSize[EFFECTSPRITETYPE_VISIBLE_1];
	(*g_pActionInfoTable)[SKILL_PASSING_HEAL][0].SoundID				= SOUND_SLAYER_PASSING_HEAL ; //SOUND_SLAYER_ENCHANT_AURABALL1;
	(*g_pActionInfoTable)[SKILL_PASSING_HEAL][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE;
	(*g_pActionInfoTable)[SKILL_PASSING_HEAL][1].EffectSpriteType	= EFFECTSPRITETYPE_VISIBLE_2;
	(*g_pActionInfoTable)[SKILL_PASSING_HEAL][1].Step				= 24;
	(*g_pActionInfoTable)[SKILL_PASSING_HEAL][1].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_PASSING_HEAL][1].Count				= 2*16;	//FrameSize[EFFECTSPRITETYPE_VISIBLE_2];
	(*g_pActionInfoTable)[SKILL_PASSING_HEAL][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE;
	(*g_pActionInfoTable)[SKILL_PASSING_HEAL][2].EffectSpriteType	= EFFECTSPRITETYPE_VISIBLE_3;
	(*g_pActionInfoTable)[SKILL_PASSING_HEAL][2].Step				= 20;
	(*g_pActionInfoTable)[SKILL_PASSING_HEAL][2].Count				= 2*16;	//FrameSize[EFFECTSPRITETYPE_VISIBLE_3];
	

	(*g_pActionInfoTable)[RESULT_SKILL_PASSING_HEAL].Set("RESULT_SKILL_PASSING_HEAL", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_PASSING_HEAL].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_PASSING_HEAL].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SKILL_PASSING_HEAL][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_PASSING_HEAL][0].EffectSpriteType	= EFFECTSPRITETYPE_PASSING_HEAL;
	(*g_pActionInfoTable)[RESULT_SKILL_PASSING_HEAL][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_PASSING_HEAL][0].Count				= FrameSize[EFFECTSPRITETYPE_PASSING_HEAL];
		
	(*g_pActionInfoTable)[SKILL_HEAL_PASS].Set("SKILL_HEAL_PASS", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_HEAL_PASS].SetSoundID( SOUNDID_NULL );		
	(*g_pActionInfoTable)[SKILL_HEAL_PASS].Init( 3 );		
	(*g_pActionInfoTable)[SKILL_HEAL_PASS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE;
	(*g_pActionInfoTable)[SKILL_HEAL_PASS][0].EffectSpriteType	= EFFECTSPRITETYPE_VISIBLE_1;
	(*g_pActionInfoTable)[SKILL_HEAL_PASS][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_HEAL_PASS][0].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_HEAL_PASS][0].Count				= 2*16;	//FrameSize[EFFECTSPRITETYPE_VISIBLE_1];
	(*g_pActionInfoTable)[SKILL_HEAL_PASS][0].SoundID				= SOUND_SLAYER_ENCHANT_AURABALL1;
	(*g_pActionInfoTable)[SKILL_HEAL_PASS][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE;
	(*g_pActionInfoTable)[SKILL_HEAL_PASS][1].EffectSpriteType	= EFFECTSPRITETYPE_VISIBLE_2;
	(*g_pActionInfoTable)[SKILL_HEAL_PASS][1].Step				= 24;
	(*g_pActionInfoTable)[SKILL_HEAL_PASS][1].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_HEAL_PASS][1].Count				= 2*16;	//FrameSize[EFFECTSPRITETYPE_VISIBLE_2];
	(*g_pActionInfoTable)[SKILL_HEAL_PASS][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_ZONE;
	(*g_pActionInfoTable)[SKILL_HEAL_PASS][2].EffectSpriteType	= EFFECTSPRITETYPE_VISIBLE_3;
	(*g_pActionInfoTable)[SKILL_HEAL_PASS][2].Step				= 20;
	(*g_pActionInfoTable)[SKILL_HEAL_PASS][2].Count				= 2*16;	//FrameSize[EFFECTSPRITETYPE_VISIBLE_3];
	
	(*g_pActionInfoTable)[RESULT_SKILL_HEAL_PASS].Set("RESULT_SKILL_PASSING_HEAL", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_HEAL_PASS].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_HEAL_PASS].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SKILL_HEAL_PASS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_HEAL_PASS][0].EffectSpriteType	= EFFECTSPRITETYPE_PASSING_HEAL;
	(*g_pActionInfoTable)[RESULT_SKILL_HEAL_PASS][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_HEAL_PASS][0].Count				= FrameSize[EFFECTSPRITETYPE_PASSING_HEAL];
	

	(*g_pActionInfoTable)[SKILL_CLIENT_HARPOON_BOMB].Set("SKILL_CLIENT_HARPOON_BOMB", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_CLIENT_HARPOON_BOMB].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_HARPOON_BOMB].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_HARPOON_BOMB][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_HARPOON_BOMB][0].EffectSpriteType	= EFFECTSPRITETYPE_HARPOON_BOMB_BLOW;
	(*g_pActionInfoTable)[SKILL_CLIENT_HARPOON_BOMB][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_HARPOON_BOMB][0].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_CLIENT_HARPOON_BOMB][0].Count				= FrameSize[EFFECTSPRITETYPE_HARPOON_BOMB_BLOW];
	(*g_pActionInfoTable)[SKILL_CLIENT_HARPOON_BOMB][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_HARPOON_BOMB][1].EffectSpriteType	= EFFECTSPRITETYPE_HARPOON_BOMB_GROUND;
	(*g_pActionInfoTable)[SKILL_CLIENT_HARPOON_BOMB][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_HARPOON_BOMB][1].Count				= FrameSize[EFFECTSPRITETYPE_HARPOON_BOMB_GROUND];

		// SKILL_QUICK_FIRE
	(*g_pActionInfoTable)[SKILL_HARPOON_BOMB].Set("SKILL_HARPOON_BOMB", ACTION_SLAYER_GUN_SR, EFFECTSPRITETYPE_GUN_SR_MALE, 5, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[SKILL_HARPOON_BOMB].SetWeaponType( FLAG_ACTIONINFO_WEAPON_GUN_ALL );
	(*g_pActionInfoTable)[SKILL_HARPOON_BOMB].SetAffectCurrentWeaponAction();
	(*g_pActionInfoTable)[SKILL_HARPOON_BOMB].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_HARPOON_BOMB].SetAffectCurrentWeaponSound();	// 들고 있는 무기의 sound적용
	(*g_pActionInfoTable)[SKILL_HARPOON_BOMB].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_HARPOON_BOMB].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_HARPOON_BOMB].SetAffectCurrentWeaponDelay();	// 들고 있는 무기의 Delay적용
	(*g_pActionInfoTable)[SKILL_HARPOON_BOMB].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용	
	(*g_pActionInfoTable)[SKILL_HARPOON_BOMB].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_HARPOON_BOMB].SetCastingStartFrameAll( 14 );	// 불꽃이 붙는 frame
	(*g_pActionInfoTable)[SKILL_HARPOON_BOMB].SetCastingFramesAll( 2 );
	(*g_pActionInfoTable)[SKILL_HARPOON_BOMB].UseRepeatFrame();	
	//(*g_pActionInfoTable)[SKILL_QUICK_FIRE].SetRepeatLimit( 2 );

	
	(*g_pActionInfoTable)[RESULT_SKILL_HARPOON_BOMB].Set("RESULT_SKILL_HARPOON_BOMB", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_HARPOON_BOMB].SetSoundID(SOUND_SLAYER_HARPOON_BOMB) ; // SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_HARPOON_BOMB].Init(1);
	(*g_pActionInfoTable)[RESULT_SKILL_HARPOON_BOMB][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_HARPOON_BOMB][0].EffectSpriteType = EFFECTSPRITETYPE_HARPOON_BOMB_DAMAGE;
	(*g_pActionInfoTable)[RESULT_SKILL_HARPOON_BOMB][0].Step = 25;
	(*g_pActionInfoTable)[RESULT_SKILL_HARPOON_BOMB][0].Count = FrameSize[EFFECTSPRITETYPE_HARPOON_BOMB_DAMAGE];

	/*
	(*g_pActionInfoTable)[RESULT_SKILL_HARPOON_BOMB][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_HARPOON_BOMB][0].EffectSpriteType = EFFECTSPRITETYPE_QUICK_FIRE_BOMB_1;
	(*g_pActionInfoTable)[RESULT_SKILL_HARPOON_BOMB][0].Step = 25;
	(*g_pActionInfoTable)[RESULT_SKILL_HARPOON_BOMB][0].Count = FrameSize[EFFECTSPRITETYPE_QUICK_FIRE_BOMB_1];
	(*g_pActionInfoTable)[RESULT_SKILL_HARPOON_BOMB][0].LinkCount = 1;
	(*g_pActionInfoTable)[RESULT_SKILL_HARPOON_BOMB][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_HARPOON_BOMB][1].EffectSpriteType = EFFECTSPRITETYPE_QUICK_FIRE_BOMB_1;
	(*g_pActionInfoTable)[RESULT_SKILL_HARPOON_BOMB][1].Step = 25;
	(*g_pActionInfoTable)[RESULT_SKILL_HARPOON_BOMB][1].Count = FrameSize[EFFECTSPRITETYPE_QUICK_FIRE_BOMB_1];
	*/
	

	(*g_pActionInfoTable)[SKILL_BIKE_CRASH].Set("SKILL_BIKE_CRASH", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_BIKE_CRASH].SetSoundID( SOUND_SLAYER_BIKE_CRASH) ; //SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_BIKE_CRASH].Set("RESULT_SKILL_BIKE_CRASH", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_BIKE_CRASH].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[SKILL_CLIENT_BIKE_CRASH].Set("SKILL_CLIENT_BIKE_CRASH", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_STAND]);
	(*g_pActionInfoTable)[SKILL_CLIENT_BIKE_CRASH].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_BIKE_CRASH].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_BIKE_CRASH][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_BIKE_CRASH][0].EffectSpriteType	= EFFECTSPRITETYPE_BIKE_CRASH;
	(*g_pActionInfoTable)[SKILL_CLIENT_BIKE_CRASH][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_BIKE_CRASH][0].Count				= FrameSize[EFFECTSPRITETYPE_BIKE_CRASH];

	(*g_pActionInfoTable)[SKILL_DRAGON_TORNADO].Set("SKILL_DRAGON_TORNADO", ACTION_SLAYER_BLADE_2, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_BLADE_2_FAST]);
	(*g_pActionInfoTable)[SKILL_DRAGON_TORNADO].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_DRAGON_TORNADO].SetActionStepCnt(2) ;
	(*g_pActionInfoTable)[SKILL_DRAGON_TORNADO].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_DRAGON_TORNADO].SetStartFrameAll( 13 );	// 기술 effect가 시작되는 frame
	(*g_pActionInfoTable)[SKILL_DRAGON_TORNADO].SetActionResult( ACTIONRESULTNODE_CREATURE_TURNING );		// 빙빙 돈다.

	(*g_pActionInfoTable)[RESULT_SKILL_DRAGON_TORNADO].Set("RESULT_SKILL_DRAGON_TORNADO", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_DRAGON_TORNADO].SetSoundID( SOUND_SLAYER_DRAGON_TORNADO) ; //SOUNDID_NULL );
	//(*g_pActionInfoTable)[RESULT_SKILL_DRAGON_TORNADO].SetActionResult( ACTIONRESULTNODE_CREATURE_TURNING );		// 빙빙 돈다.
	
	// 이벤트 촛불
	(*g_pActionInfoTable)[SKILL_CLIENT_CANDLE].Set("SKILL_CLIENT_CANDLE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_STAND]);
	(*g_pActionInfoTable)[SKILL_CLIENT_CANDLE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_CANDLE].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_CANDLE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_CANDLE][0].EffectSpriteType	= EFFECTSPRITETYPE_CANDLE_START;
	(*g_pActionInfoTable)[SKILL_CLIENT_CANDLE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_CANDLE][0].Count				= FrameSize[EFFECTSPRITETYPE_CANDLE_START];
	(*g_pActionInfoTable)[SKILL_CLIENT_CANDLE][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_CANDLE][1].EffectSpriteType	= EFFECTSPRITETYPE_CANDLE_END;
	(*g_pActionInfoTable)[SKILL_CLIENT_CANDLE][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_CANDLE][1].Count				= FrameSize[EFFECTSPRITETYPE_CANDLE_END];
	
	
	(*g_pActionInfoTable)[SKILL_CLIENT_QUEST_MAGIC_ZONE].Set("SKILL_CLIENT_QUEST_MAGIC_ZONE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_STAND]);
	(*g_pActionInfoTable)[SKILL_CLIENT_QUEST_MAGIC_ZONE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_QUEST_MAGIC_ZONE].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_QUEST_MAGIC_ZONE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_QUEST_MAGIC_ZONE][0].EffectSpriteType	= EFFECTSPRITETYPE_QUEST_MAGIC_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_QUEST_MAGIC_ZONE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_QUEST_MAGIC_ZONE][0].Count				= /*FrameSize[EFFECTSPRITETYPE_QUEST_MAGIC_ZONE]*/0xffff;
	//(*g_pActionInfoTable)[SKILL_CLIENT_QUEST_MAGIC_ZONE][0].SetDelayNode();

	(*g_pActionInfoTable)[SKILL_CLIENT_QUEST_MAGIC_ZONE_POTAL].Set("SKILL_CLIENT_QUEST_MAGIC_ZONE_POTAL", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_STAND]);
	(*g_pActionInfoTable)[SKILL_CLIENT_QUEST_MAGIC_ZONE_POTAL].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_QUEST_MAGIC_ZONE_POTAL].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_QUEST_MAGIC_ZONE_POTAL][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_QUEST_MAGIC_ZONE_POTAL][0].EffectSpriteType	= EFFECTSPRITETYPE_QUEST_MAGIC_ZONE_POTAL;
	(*g_pActionInfoTable)[SKILL_CLIENT_QUEST_MAGIC_ZONE_POTAL][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_QUEST_MAGIC_ZONE_POTAL][0].Count				= 0xffff/*FrameSize[EFFECTSPRITETYPE_QUEST_MAGIC_ZONE]*/;
	
	//2004, 10, 15, sobeit add start - test
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT].Set("TEMP_SKILL_INFINITY_THUNDERBLOT", ACTION_SLAYER_SWORD_2, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD_2]);
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT].SetStartFrameAll( 5 );
//	//(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT].SetSoundID( SOUND_SLAYER_SWORDOFTHOR );
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT].Init( 2 );		
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT].SetMainNode( 1 );
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][0].EffectSpriteType	= EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_CENTER;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][0].Step				= 25;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][0].Count				= FrameSize[EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_CENTER];
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][1].EffectSpriteType	= EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_GROUND;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][1].Step				= 25;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][1].Count				= FrameSize[EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_GROUND];

//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, RESULT_SKILL_SWORD_OF_THOR );	// 맞는 결과를 표현한다.	
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][0].EffectSpriteType	= EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_CENTER;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][0].Step				= 25;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][0].LinkCount			= 5;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][0].Count				= FrameSize[EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_CENTER];
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][1].EffectSpriteType	= EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_LEFT;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][1].Step				= 25;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][1].LinkCount			= 0;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][1].Count				= FrameSize[EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_LEFT];
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][2].EffectSpriteType	= EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_GROUND;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][2].Step				= 25;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][2].LinkCount			= 5;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][2].Count				= FrameSize[EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_GROUND];
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][3].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][3].EffectSpriteType	= EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_RIGHT;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][3].Step				= 25;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][3].LinkCount			= 0;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][3].Count				= FrameSize[EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_RIGHT];
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][4].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][4].EffectSpriteType	= EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_GROUND;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][4].Step				= 25;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][4].LinkCount			= 5;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][4].Count				= FrameSize[EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_GROUND];
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][5].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][5].EffectSpriteType	= EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_GROUND;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][5].Step				= 25;
//	(*g_pActionInfoTable)[TEMP_SKILL_INFINITY_THUNDERBLOT][5].Count				= FrameSize[EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_GROUND];
//

//	(*g_pActionInfoTable)[TEMP_SKILL_SPIT_STREAM].Set("TEMP_SKILL_SPIT_STREAM", ACTION_SLAYER_BLADE, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER);
//	(*g_pActionInfoTable)[TEMP_SKILL_SPIT_STREAM].SetSoundID( SOUNDID_NULL );
//	(*g_pActionInfoTable)[TEMP_SKILL_SPIT_STREAM].SetMainNode( 1 );
//	(*g_pActionInfoTable)[TEMP_SKILL_SPIT_STREAM].Init( 1 );		
//	(*g_pActionInfoTable)[TEMP_SKILL_SPIT_STREAM][0].EffectGeneratorID	= EFFECTGENERATORID_AROUND_ZONE  ;
//	(*g_pActionInfoTable)[TEMP_SKILL_SPIT_STREAM][0].EffectSpriteType	= EFFECTSPRITETYPE_SPIT_STREAM;
//	(*g_pActionInfoTable)[TEMP_SKILL_SPIT_STREAM][0].Step				= 25;
//	(*g_pActionInfoTable)[TEMP_SKILL_SPIT_STREAM][0].Count				= FrameSize[EFFECTSPRITETYPE_SPIT_STREAM];


//	(*g_pActionInfoTable)[TEMP_SKILL_BOMBING_STAR].Set("TEMP_SKILL_BOMBING_STAR", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_MAGIC]);
////	(*g_pActionInfoTable)[TEMP_SKILL_BOMBING_STAR].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
////	(*g_pActionInfoTable)[TEMP_SKILL_BOMBING_STAR].SetCastingActionInfo( CASTING_ENCHANT );	
////	(*g_pActionInfoTable)[TEMP_SKILL_BOMBING_STAR].SetCastingFramesAll( 24 );
////	(*g_pActionInfoTable)[TEMP_SKILL_BOMBING_STAR].SetStartFrameAll( 10 );
////	(*g_pActionInfoTable)[TEMP_SKILL_BOMBING_STAR].SetEffectStatus( EFFECTSTATUS_BLESS );
//	(*g_pActionInfoTable)[TEMP_SKILL_BOMBING_STAR].SetSoundID( SOUNDID_NULL );		
//	(*g_pActionInfoTable)[TEMP_SKILL_BOMBING_STAR].Init(2 );		
//	(*g_pActionInfoTable)[TEMP_SKILL_BOMBING_STAR][0].EffectGeneratorID	= EFFECTGENERATORID_FALLING  ;
//	(*g_pActionInfoTable)[TEMP_SKILL_BOMBING_STAR][0].EffectSpriteType	= EFFECTSPRITETYPE_BOMBING_STAR_DROP;
//	(*g_pActionInfoTable)[TEMP_SKILL_BOMBING_STAR][0].Step				= 25;
//	(*g_pActionInfoTable)[TEMP_SKILL_BOMBING_STAR][0].Count				= FrameSize[EFFECTSPRITETYPE_BOMBING_STAR_DROP];
//	(*g_pActionInfoTable)[TEMP_SKILL_BOMBING_STAR][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE  ;
//	(*g_pActionInfoTable)[TEMP_SKILL_BOMBING_STAR][1].EffectSpriteType	= EFFECTSPRITETYPE_BOMBING_STAR_BLOW;
//	(*g_pActionInfoTable)[TEMP_SKILL_BOMBING_STAR][1].Step				= 25;
//	(*g_pActionInfoTable)[TEMP_SKILL_BOMBING_STAR][1].Count				= FrameSize[EFFECTSPRITETYPE_BOMBING_STAR_BLOW];
//	

	//2004, 10, 15, sobeit add end - test

	//2005.08.04, Sjheon  폭주 스킬 설정 Add

/*	(*g_pActionInfoTable)[SKILL_HOLY_SWORD].Set("SKILL_HOLY_SWORD",ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_HOLY_SWORD].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_HOLY_SWORD].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_HOLY_SWORD].SetAttachSelf();
	(*g_pActionInfoTable)[SKILL_HOLY_SWORD].Init( 1 );
	(*g_pActionInfoTable)[SKILL_HOLY_SWORD][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_HOLY_SWORD][0].EffectSpriteType		= EFFECTSPRITETYPE_BLOOD_BURST_START ;
	(*g_pActionInfoTable)[SKILL_HOLY_SWORD][0].Step					= 0;
	(*g_pActionInfoTable)[SKILL_HOLY_SWORD][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_BURST_START];
	(*g_pActionInfoTable)[SKILL_HOLY_SWORD][0].LinkCount			= 0;

*/
	(*g_pActionInfoTable)[SKILL_HOLY_SWORD].Set("SKILL_HOLY_SWORD",ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_HOLY_SWORD].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SWORD].Set("RESULT_SKILL_HOLY_SWORD",ACTION_STAND, EFFECTSPRITETYPE_BLOOD_BURST_START, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	//(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SWORD].SetSoundID( SOUNDID_NULL );
	//(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SWORD].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SWORD].SetMaleSoundID(SOUND_SLAYER_BLOODBURST_ATTATCK_MAIL);
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SWORD].SetFemaleSoundID(SOUND_SLAYER_BLOODBURST_ATTATCK_FEMALE);

	//(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SWORD].SetAttachSelf();
	//(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SWORD].Init( 1 );
	//(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SWORD][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	//(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SWORD][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_BURST_START ;
	//(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SWORD][0].Step				= 0;
	//(*g_pActionInfoTable)[RESULT_SKILL_HOLY_SWORD][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_BURST_START] * 20;
	



	(*g_pActionInfoTable)[SKILL_HOLY_BLADE].Set("SKILL_HOLY_BLADE",ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_HOLY_BLADE].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_BLADE].Set("RESULT_SKILL_HOLY_BLADE",ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_BLADE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_BLADE].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_BLADE].SetMaleSoundID(SOUND_SLAYER_BLOODBURST_ATTATCK_MAIL);
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_BLADE].SetFemaleSoundID(SOUND_SLAYER_BLOODBURST_ATTATCK_FEMALE);
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_BLADE].SetAttachSelf();

	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_BLADE].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_BLADE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_BLADE][0].EffectSpriteType		= EFFECTSPRITETYPE_BLOOD_BURST_START ;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_BLADE][0].Step					= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_BLADE][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_BURST_START];

	
	(*g_pActionInfoTable)[SKILL_BURST_GUN].Set("SKILL_BURST_GUN",ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_BURST_GUN].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_BURST_GUN].Set("RESULT_SKILL_BURST_GUN",ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[RESULT_SKILL_BURST_GUN].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_BURST_GUN].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_BURST_GUN].SetMaleSoundID(SOUND_SLAYER_BLOODBURST_ATTATCK_MAIL);
	(*g_pActionInfoTable)[RESULT_SKILL_BURST_GUN].SetFemaleSoundID(SOUND_SLAYER_BLOODBURST_ATTATCK_FEMALE);
	(*g_pActionInfoTable)[RESULT_SKILL_BURST_GUN].SetAttachSelf();
	(*g_pActionInfoTable)[RESULT_SKILL_BURST_GUN].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_BURST_GUN][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_BURST_GUN][0].EffectSpriteType		= EFFECTSPRITETYPE_BLOOD_BURST_START ;
	(*g_pActionInfoTable)[RESULT_SKILL_BURST_GUN][0].Step					= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_BURST_GUN][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_BURST_START];
	
	(*g_pActionInfoTable)[SKILL_HOLY_MACE].Set("SKILL_HOLY_MACE",ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_HOLY_MACE].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_MACE].Set("RESULT_SKILL_HOLY_MACE",ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_MACE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_MACE].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_MACE].SetMaleSoundID(SOUND_SLAYER_BLOODBURST_ATTATCK_MAIL);
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_MACE].SetFemaleSoundID(SOUND_SLAYER_BLOODBURST_ATTATCK_FEMALE);
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_MACE].SetAttachSelf();
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_MACE].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_MACE][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_MACE][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOOD_BURST_START ;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_MACE][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_MACE][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_BURST_START];
	
	
	(*g_pActionInfoTable)[SKILL_HOLY_CROSS].Set("SKILL_HOLY_CROSS",ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_HOLY_CROSS].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_CROSS].Set("RESULT_SKILL_HOLY_CROSS",ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_CROSS].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_CROSS].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_CROSS].SetMaleSoundID(SOUND_SLAYER_BLOODBURST_ATTATCK_MAIL);
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_CROSS].SetFemaleSoundID(SOUND_SLAYER_BLOODBURST_ATTATCK_FEMALE);
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_CROSS].SetAttachSelf();
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_CROSS].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_CROSS][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_CROSS][0].EffectSpriteType		= EFFECTSPRITETYPE_BLOOD_BURST_START ;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_CROSS][0].Step					= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_HOLY_CROSS][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_BURST_START];
	

	(*g_pActionInfoTable)[SKILL_LOSE_SIGHT].Set("SKILL_LOSE_SIGHT",ACTION_STAND, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_LOSE_SIGHT].SetSoundID( SOUNDID_NULL );


	(*g_pActionInfoTable)[RESULT_SKILL_LOSE_SIGHT].Set("RESULT_SKILL_LOSE_SIGHT",ACTION_STAND, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[RESULT_SKILL_LOSE_SIGHT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_LOSE_SIGHT].SetAttachSelf();
	(*g_pActionInfoTable)[RESULT_SKILL_LOSE_SIGHT].SetMaleSoundID(SOUND_SLAYER_BLOODBURST_DEFENSE_MAIL);
	(*g_pActionInfoTable)[RESULT_SKILL_LOSE_SIGHT].SetFemaleSoundID(SOUND_SLAYER_BLOODBURST_DEFENSE_MAIL);
	(*g_pActionInfoTable)[RESULT_SKILL_LOSE_SIGHT].SetUseActionGrade();
	(*g_pActionInfoTable)[RESULT_SKILL_LOSE_SIGHT].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_LOSE_SIGHT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_LOSE_SIGHT][0].EffectSpriteType		= EFFECTSPRITETYPE_BLOOD_BURST_DEFENSE_START_GOLD ;
	(*g_pActionInfoTable)[RESULT_SKILL_LOSE_SIGHT][0].Step					= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_LOSE_SIGHT][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOOD_BURST_DEFENSE_START_GOLD];
	
	


	(*g_pActionInfoTable)[SKILL_PARTY_AURA].Set("SKILL_PARTY_AURA",ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_PARTY_AURA].SetSoundID( SOUNDID_NULL );
	
	(*g_pActionInfoTable)[RESULT_SKILL_PARTY_AURA].Set("SKILL_PARTY_AURA",ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[RESULT_SKILL_PARTY_AURA].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_PARTY_AURA].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_PARTY_AURA].SetAttachSelf();
	(*g_pActionInfoTable)[RESULT_SKILL_PARTY_AURA].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_PARTY_AURA][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_PARTY_AURA][0].EffectSpriteType	= EFFECTSPRITETYPE_PARTY_ROTATION_WHITE ;
	(*g_pActionInfoTable)[RESULT_SKILL_PARTY_AURA][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_PARTY_AURA][0].Count				= FrameSize[EFFECTSPRITETYPE_PARTY_ROTATION_WHITE];


	//2005.08.04, Sjheon  폭주 스킬 설정 End
	
	
	
	//2006.02.14, Sjheon ComboSkill add 
	(*g_pActionInfoTable)[SKILL_SWORD_COMBO].Set("SKILL_SWORD_COMBO", ACTION_SLAYER_SWORD_2, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_SWORD_2]);
	(*g_pActionInfoTable)[SKILL_SWORD_COMBO].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_SWORD_COMBO].SetComboAttackSkill(TRUE);
	(*g_pActionInfoTable)[SKILL_SWORD_COMBO].SetSoundID( SOUNDID_NULL );
	//(*g_pActionInfoTable)[SKILL_SWORD_COMBO].SetComboActionResultEffect(SKILL_SWORD_COMBO_EFFECT) ; 
	(*g_pActionInfoTable)[SKILL_SWORD_COMBO].SetComboSkillActionStep(ACTIONINFO_NULL , ACTIONINFO_NULL , ACTIONINFO_NULL ,  SKILL_SWORD_COMBO_EFFECT) ;

	
	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_COMBO].Set("RESULT_SKILL_SWORD_COMBO", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[RESULT_SKILL_SWORD_COMBO].SetSoundID( SOUNDID_NULL );
	//(*g_pActionInfoTable)[RESULT_SKILL_SWORD_COMBO].Init( 1 );
	//(*g_pActionInfoTable)[RESULT_SKILL_SWORD_COMBO][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	//(*g_pActionInfoTable)[RESULT_SKILL_SWORD_COMBO][0].EffectSpriteType  = EFFECTSPRITETYPE_SHARP_ROUND_1_3;
	//(*g_pActionInfoTable)[RESULT_SKILL_SWORD_COMBO][0].Step			     = 0;
	//(*g_pActionInfoTable)[RESULT_SKILL_SWORD_COMBO][0].Count			 = FrameSize[EFFECTSPRITETYPE_SHARP_ROUND_1_3];
	//(*g_pActionInfoTable)[RESULT_SKILL_SWORD_COMBO][0].SetResultTime();
	
	(*g_pActionInfoTable)[SKILL_SWORD_COMBO_EFFECT].Set("SKILL_SWORD_COMBO_EFFECT", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_SWORD_COMBO_EFFECT].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[SKILL_SWORD_COMBO_EFFECT].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_SWORD_COMBO_EFFECT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_SWORD_COMBO_EFFECT][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_INFINITY_THUNDERBOLT ; //FFECTSPRITETYPE_INFINITY_THUNDERBOLT_GROUND;
	(*g_pActionInfoTable)[SKILL_SWORD_COMBO_EFFECT][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SWORD_COMBO_EFFECT][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_INFINITY_THUNDERBOLT] ; // EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_GROUND];
	(*g_pActionInfoTable)[SKILL_SWORD_COMBO_EFFECT][0].LinkCount			= 5;
	(*g_pActionInfoTable)[SKILL_SWORD_COMBO_EFFECT][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_SWORD_COMBO_EFFECT][1].EffectSpriteType	= EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_CENTER;
	(*g_pActionInfoTable)[SKILL_SWORD_COMBO_EFFECT][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SWORD_COMBO_EFFECT][1].Count				= FrameSize[EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_CENTER] ;


	/*(*g_pActionInfoTable)[SKILL_SWORD_COMBO_EFFECT].Init( 1 );
	(*g_pActionInfoTable)[SKILL_SWORD_COMBO_EFFECT][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_SWORD_COMBO_EFFECT][0].EffectSpriteType  = EFFECTSPRITETYPE_SHARP_ROUND_1_3;
	(*g_pActionInfoTable)[SKILL_SWORD_COMBO_EFFECT][0].Step			     = 0;
	(*g_pActionInfoTable)[SKILL_SWORD_COMBO_EFFECT][0].Count			 = FrameSize[EFFECTSPRITETYPE_SHARP_ROUND_1_3];
	(*g_pActionInfoTable)[SKILL_SWORD_COMBO_EFFECT][0].SetResultTime();
	*/
		
	(*g_pActionInfoTable)[SKILL_BLADE_COMBO].Set("SKILL_BLADE_COMBO", ACTION_SLAYER_BLADE_2, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_BLADE_2]);
	(*g_pActionInfoTable)[SKILL_BLADE_COMBO].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	//(*g_pActionInfoTable)[SKILL_BLADE_COMBO].SetStartFrameAll( 4 );
	(*g_pActionInfoTable)[SKILL_BLADE_COMBO].SetComboAttackSkill(TRUE);
	(*g_pActionInfoTable)[SKILL_BLADE_COMBO].SetSoundID( SOUNDID_NULL );
	//(*g_pActionInfoTable)[SKILL_BLADE_COMBO].SetComboActionResultEffect(SKILL_BLADE_COMBO_EFFECT) ; 

	(*g_pActionInfoTable)[SKILL_BLADE_COMBO].SetComboSkillActionStep(ACTIONINFO_NULL , ACTIONINFO_NULL , ACTIONINFO_NULL ,  SKILL_BLADE_COMBO_EFFECT) ; 

	
	(*g_pActionInfoTable)[RESULT_SKILL_BLADE_COMBO].Set("RESULT_SKILL_BLADE_COMBO", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	//(*g_pActionInfoTable)[RESULT_SKILL_BLADE_COMBO].SetStartFrameAll( 4 );
	(*g_pActionInfoTable)[RESULT_SKILL_BLADE_COMBO].SetSoundID( SOUNDID_NULL );
	//(*g_pActionInfoTable)[RESULT_SKILL_BLADE_COMBO].Init( 1 );
	//(*g_pActionInfoTable)[RESULT_SKILL_BLADE_COMBO][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	//(*g_pActionInfoTable)[RESULT_SKILL_BLADE_COMBO][0].EffectSpriteType  = EFFECTSPRITETYPE_SHARP_ROUND_1_3;
	//(*g_pActionInfoTable)[RESULT_SKILL_BLADE_COMBO][0].Step			     = 0;
	//(*g_pActionInfoTable)[RESULT_SKILL_BLADE_COMBO][0].Count			 = FrameSize[EFFECTSPRITETYPE_SHARP_ROUND_1_3];


	(*g_pActionInfoTable)[SKILL_BLADE_COMBO_EFFECT].Set("SKILL_BLADE_COMBO_EFFECT", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER);
	///(*g_pActionInfoTable)[SKILL_BLADE_COMBO_EFFECT].SetStartFrameAll( 4 );
	(*g_pActionInfoTable)[SKILL_BLADE_COMBO_EFFECT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_BLADE_COMBO_EFFECT].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_BLADE_COMBO_EFFECT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_BLADE_COMBO_EFFECT][0].EffectSpriteType	= EFFECTSPRITETYPE_NEW_INFINITY_THUNDERBOLT ; //FFECTSPRITETYPE_INFINITY_THUNDERBOLT_GROUND;
	(*g_pActionInfoTable)[SKILL_BLADE_COMBO_EFFECT][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_BLADE_COMBO_EFFECT][0].Count				= FrameSize[EFFECTSPRITETYPE_NEW_INFINITY_THUNDERBOLT] ; // EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_GROUND];
	(*g_pActionInfoTable)[SKILL_BLADE_COMBO_EFFECT][0].LinkCount			= 5;
	(*g_pActionInfoTable)[SKILL_BLADE_COMBO_EFFECT][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_BLADE_COMBO_EFFECT][1].EffectSpriteType	= EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_CENTER;
	(*g_pActionInfoTable)[SKILL_BLADE_COMBO_EFFECT][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_BLADE_COMBO_EFFECT][1].Count				= FrameSize[EFFECTSPRITETYPE_INFINITY_THUNDERBOLT_CENTER] ;


	//2006.02.14  Sjheon ComboSkill End	

	
	// 2006.10.20 sjheo Add
	// 2008.02.28 경진 	VampireActionDelay[ACTION_SLAYER_SWORD_2]를 ActionDelay[ACTION_SLAYER_SWORD_2]로 수정
	(*g_pActionInfoTable)[SKILL_SHINE_SWORD].Set("SKILL_SHINE_SWORD", ACTION_SLAYER_SWORD_2, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_SWORD_2]);
	(*g_pActionInfoTable)[SKILL_SHINE_SWORD].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_SHINE_SWORD].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SWORD );
	(*g_pActionInfoTable)[SKILL_SHINE_SWORD].SetStartFrameAll( 2 );
	(*g_pActionInfoTable)[SKILL_SHINE_SWORD].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_SHINE_SWORD].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_SHINE_SWORD].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_SHINE_SWORD][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[SKILL_SHINE_SWORD][0].EffectSpriteType	= EFFECTSPRITETYPE_SHINE_SWORD_THROW;
	(*g_pActionInfoTable)[SKILL_SHINE_SWORD][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_SHINE_SWORD][0].Count				= FrameSize[EFFECTSPRITETYPE_SHINE_SWORD_THROW];	
	
	
	(*g_pActionInfoTable)[RESULT_SKILL_SHINE_SWORD].Set("RESULT_SKILL_SHINE_SWORD", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_SHINE_SWORD].SetSoundID( SOUNDID_NULL);
	(*g_pActionInfoTable)[RESULT_SKILL_SHINE_SWORD].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_SHINE_SWORD][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_SHINE_SWORD][0].EffectSpriteType		= EFFECTSPRITETYPE_SHINE_SWORD_FLASH_LIGHT;
	(*g_pActionInfoTable)[RESULT_SKILL_SHINE_SWORD][0].Step					= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_SHINE_SWORD][0].Count				= FrameSize[EFFECTSPRITETYPE_SHINE_SWORD_FLASH_LIGHT];	
		
	
	(*g_pActionInfoTable)[SKILL_CLIENT_SHINE_SWORD].Set("SKILL_CLIENT_SKILL_SHINE_SWORD", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_CLIENT_SHINE_SWORD].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_SHINE_SWORD].Init( 4 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_SHINE_SWORD][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_SHINE_SWORD][0].EffectSpriteType		= EFFECTSPRITETYPE_SHINE_SWORD_FALL_DOWN_A;
	(*g_pActionInfoTable)[SKILL_CLIENT_SHINE_SWORD][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_SHINE_SWORD][0].Count				= FrameSize[EFFECTSPRITETYPE_SHINE_SWORD_FALL_DOWN_A];
	
	(*g_pActionInfoTable)[SKILL_CLIENT_SHINE_SWORD][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_SHINE_SWORD][1].EffectSpriteType		= EFFECTSPRITETYPE_SHINE_SWORD_FALL_DOWN_B;
	(*g_pActionInfoTable)[SKILL_CLIENT_SHINE_SWORD][1].Step					= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_SHINE_SWORD][1].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_CLIENT_SHINE_SWORD][1].Count				= FrameSize[EFFECTSPRITETYPE_SHINE_SWORD_FALL_DOWN_B];
	(*g_pActionInfoTable)[SKILL_CLIENT_SHINE_SWORD][1].SetDelayNode();
	
	(*g_pActionInfoTable)[SKILL_CLIENT_SHINE_SWORD][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_SHINE_SWORD][2].EffectSpriteType		= EFFECTSPRITETYPE_SHINE_SWORD_GROUND_ELECTRIC;
	(*g_pActionInfoTable)[SKILL_CLIENT_SHINE_SWORD][2].Step					= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_SHINE_SWORD][2].Count				= FrameSize[EFFECTSPRITETYPE_SHINE_SWORD_GROUND_ELECTRIC];
	(*g_pActionInfoTable)[SKILL_CLIENT_SHINE_SWORD][2].SetDelayNode();

	(*g_pActionInfoTable)[SKILL_CLIENT_SHINE_SWORD][3].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_SHINE_SWORD][3].EffectSpriteType		= EFFECTSPRITETYPE_SHINE_SWORD_GROUND_BROKEN_PIECE;
	(*g_pActionInfoTable)[SKILL_CLIENT_SHINE_SWORD][3].Step					= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_SHINE_SWORD][3].Count				= FrameSize[EFFECTSPRITETYPE_SHINE_SWORD_GROUND_BROKEN_PIECE];
	(*g_pActionInfoTable)[SKILL_CLIENT_SHINE_SWORD][3].SetResultTime();
	
	
	(*g_pActionInfoTable)[SKILL_BOMB_CRASH_WALK].Set("SKILL_BOMB_CRASH_WALK", ACTION_SLAYER_BLADE_2, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER);
	(*g_pActionInfoTable)[SKILL_BOMB_CRASH_WALK].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_BOMB_CRASH_WALK].SetSoundID( SOUNDID_NULL );
	
	
	(*g_pActionInfoTable)[RESULT_SKILL_BOMB_CRASH_WALK].Set("RESULT_SKILL_BOMB_CRASH_WALK", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_BOMB_CRASH_WALK].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_BOMB_CRASH_WALK].Init( 1 );
	
	(*g_pActionInfoTable)[RESULT_SKILL_BOMB_CRASH_WALK][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE_X;
	(*g_pActionInfoTable)[RESULT_SKILL_BOMB_CRASH_WALK][0].EffectSpriteType  = EFFECTSPRITETYPE_BOMB_CRASH_WALK_PILLAR_OF_FIRE;
	(*g_pActionInfoTable)[RESULT_SKILL_BOMB_CRASH_WALK][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_BOMB_CRASH_WALK][0].Count				= FrameSize[EFFECTSPRITETYPE_BOMB_CRASH_WALK_PILLAR_OF_FIRE];
	(*g_pActionInfoTable)[RESULT_SKILL_BOMB_CRASH_WALK][0].SoundID			= SOUNDID_NULL;

	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK].Set("SKILL_CLIENT_BOMB_CRASH_WALK", ACTION_SLAYER_BLADE_2, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_SLAYER_BLADE]);
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK].SetActionStepCnt(2) ;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK].Init( 11 );	
	
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][0].EffectSpriteType		= EFFECTSPRITETYPE_BOMB_CRASH_WALK_DASH;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][0].Count				= FrameSize[EFFECTSPRITETYPE_BOMB_CRASH_WALK_DASH];
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][0].SoundID				= SOUNDID_NULL;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][0].LinkCount			= 0;
		
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][1].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][1].EffectSpriteType		= EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][1].Step					= 42;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][1].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1];
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][1].LinkCount			= 1;
	
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][2].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][2].EffectSpriteType		= EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][2].Step					= 42;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][2].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1];
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][2].LinkCount			= 1;
	
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][3].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][3].EffectSpriteType		= EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][3].Step					= 42;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][3].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1];
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][3].LinkCount			= 1;
	
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][4].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][4].EffectSpriteType		= EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][4].Step					= 42;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][4].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1];
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][4].LinkCount			= 1;
	
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][5].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][5].EffectSpriteType		= EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][5].Step					= 42;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][5].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1];
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][5].LinkCount			= 1;
	
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][6].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][6].EffectSpriteType		= EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][6].Step					= 42;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][6].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1];
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][6].LinkCount			= 1;
		
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][7].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][7].EffectSpriteType		= EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][7].Step					= 42;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][7].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1];
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][7].LinkCount			= 1;
	
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][8].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][8].EffectSpriteType		= EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][8].Step					= 42;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][8].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1];
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][8].LinkCount			= 1;
	
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][9].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][9].EffectSpriteType		= EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][9].Step					= 42;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][9].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1];
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][9].LinkCount			= 1;
	
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][10].EffectGeneratorID	= EFFECTGENERATORID_RIPPLE_ZONE_PIXEL;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][10].EffectSpriteType	= EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][10].Step				= 42;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][10].Count				= FrameSize[EFFECTSPRITETYPE_POWER_OF_LAND_STONE_1];
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK][10].LinkCount			= 1;
	

	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK_SPARK].Set("SKILL_CLIENT_BOMB_CRASH_WALK_SPARK", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK_SPARK].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK_SPARK].Init(3);

	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK_SPARK][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK_SPARK][0].EffectSpriteType	= EFFECTSPRITETYPE_BOMB_CRASH_WALK_SPARK_1;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK_SPARK][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK_SPARK][0].Count				= FrameSize[EFFECTSPRITETYPE_BOMB_CRASH_WALK_SPARK_1];
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK_SPARK][0].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK_SPARK][0].SetDelayNode();

	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK_SPARK][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK_SPARK][1].EffectSpriteType	= EFFECTSPRITETYPE_BOMB_CRASH_WALK_SPARK_2;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK_SPARK][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK_SPARK][1].Count				= FrameSize[EFFECTSPRITETYPE_BOMB_CRASH_WALK_SPARK_2];
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK_SPARK][1].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK_SPARK][1].SetDelayNode();

	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK_SPARK][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK_SPARK][2].EffectSpriteType	= EFFECTSPRITETYPE_BOMB_CRASH_WALK_SPARK_3;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK_SPARK][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK_SPARK][2].Count				= FrameSize[EFFECTSPRITETYPE_BOMB_CRASH_WALK_SPARK_3];
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK_SPARK][2].LinkCount			= 1;
	(*g_pActionInfoTable)[SKILL_CLIENT_BOMB_CRASH_WALK_SPARK][2].SetDelayNode();

	
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_POINT].Set("RESULT_SKILL_SATELLITE_BOMB_POINT", ACTION_STAND, EFFECTSPRITETYPE_SATELLITE_BOMB_TARGET, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_POINT].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_POINT].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_POINT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_POINT][0].EffectSpriteType	= EFFECTSPRITETYPE_SATELLITE_BOMB_TARGET;
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_POINT][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_POINT][0].Count				= FrameSize[EFFECTSPRITETYPE_SATELLITE_BOMB_TARGET];
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_POINT][0].SoundID				= SOUNDID_NULL;
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_POINT][0].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_POINT][0].SetDelayNode();
	
	
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_FIRE].Set("RESULT_SKILL_SATELLITE_BOMB_BOMB", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_FIRE].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_FIRE].Init( 3 );
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_FIRE][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_FIRE][0].EffectSpriteType		= EFFECTSPRITETYPE_SATELLITE_BOMB_LASER_REPEAT;
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_FIRE][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_FIRE][0].Count				= FrameSize[EFFECTSPRITETYPE_SATELLITE_BOMB_LASER_REPEAT];
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_FIRE][0].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_FIRE][0].SetResultTime();
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_FIRE][0].SoundID				= SOUNDID_NULL;
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_FIRE][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_FIRE][1].EffectSpriteType		= EFFECTSPRITETYPE_SATELLITE_BOMB_LASER_END;
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_FIRE][1].Step					= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_FIRE][1].Count				= FrameSize[EFFECTSPRITETYPE_SATELLITE_BOMB_LASER_END];
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_FIRE][1].SoundID				= SOUNDID_NULL;
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_FIRE][1].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_FIRE][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_FIRE][2].EffectSpriteType		= EFFECTSPRITETYPE_SATELLITE_BOMB_BIG_EXPLOSION;
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_FIRE][2].Step					= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_FIRE][2].Count				= FrameSize[EFFECTSPRITETYPE_SATELLITE_BOMB_BIG_EXPLOSION];
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_FIRE][2].SoundID				= SOUNDID_NULL;
	(*g_pActionInfoTable)[SKILL_CLIENT_SATELLITE_BOMB_FIRE][2].LinkCount			= 0;
	
	
	
	(*g_pActionInfoTable)[SKILL_SATELLITE_BOMB].Set("SKILL_SATELLITE_BOMB", ACTION_STAND, EFFECTSPRITETYPE_GUN_SR_MALE, 3, FLAG_ACTIONINFO_TARGET_ZONE | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, 50);	
	(*g_pActionInfoTable)[SKILL_SATELLITE_BOMB].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_SATELLITE_BOMB].SetStartFrame( 0, 7 );			// slow
	(*g_pActionInfoTable)[SKILL_SATELLITE_BOMB].SetStartFrame( 1, 7 );			// normal
	(*g_pActionInfoTable)[SKILL_SATELLITE_BOMB].SetStartFrame( 2, 5 );			// fast
	(*g_pActionInfoTable)[SKILL_SATELLITE_BOMB].SetAffectCurrentWeaponRange();
	(*g_pActionInfoTable)[SKILL_SATELLITE_BOMB].SetAffectCurrentWeaponCastingStartFrame();	// 들고 있는 무기의 CastingStartFrame적용
	(*g_pActionInfoTable)[SKILL_SATELLITE_BOMB].SetAffectCurrentWeaponCastingFrames();	// 들고 있는 무기의 Casting Frames적용
	(*g_pActionInfoTable)[SKILL_SATELLITE_BOMB].SetAffectCurrentWeaponActionEffectSpriteType();	// 들고 있는 무기의 ActionEffectSpriteType적용
	
	(*g_pActionInfoTable)[RESULT_SKILL_SATELLITE_BOMB].Set("RESULT_SKILL_SATELLITE_BOMB", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[RESULT_SKILL_SATELLITE_BOMB].SetSoundID( SOUND_SLAYER_GUN_SHOT_GUIDANCE) ;//SOUNDID_NULL );
	
	
	(*g_pActionInfoTable)[SKILL_ILLUSION_INVERSION].Set("MAGIC_CAUSE_SERIOUS_WOUNDS", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER) ; //, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_ILLUSION_INVERSION].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_ILLUSION_INVERSION].SetSoundID( SOUNDID_NULL );		

	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_INVERSION].Set("RESULT_SKILL_ILLUSION_INVERSION", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_INVERSION].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_INVERSION].Init( 2 );
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_INVERSION][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_INVERSION][0].EffectSpriteType	= EFFECTSPRITETYPE_ILLUSION_INVERSION_IMBIBITION_FRONT;
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_INVERSION][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_INVERSION][0].Count				= FrameSize[EFFECTSPRITETYPE_ILLUSION_INVERSION_IMBIBITION_FRONT];
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_INVERSION][0].LinkCount			= FrameSize[EFFECTSPRITETYPE_ILLUSION_INVERSION_IMBIBITION_FRONT]/2;
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_INVERSION][0].SoundID			= SOUNDID_NULL;
	
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_INVERSION][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_INVERSION][1].EffectSpriteType	= EFFECTSPRITETYPE_ILLUSION_INVERSION_EXPLOSION_1;
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_INVERSION][1].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_INVERSION][1].Count				= FrameSize[EFFECTSPRITETYPE_ILLUSION_INVERSION_EXPLOSION_1];
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_INVERSION][1].SoundID			= SOUNDID_NULL;
	(*g_pActionInfoTable)[RESULT_SKILL_ILLUSION_INVERSION][1].LinkCount			= 0;
	
	(*g_pActionInfoTable)[SKILL_HEAVEN_GROUND].Set("SKILL_HEAVEN_GROUND", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_HEAVEN_GROUND].SetStartFrameAll( 10 );
	(*g_pActionInfoTable)[SKILL_HEAVEN_GROUND].SetSoundID( SOUNDID_NULL );	

	(*g_pActionInfoTable)[RESULT_SKILL_HEAVEN_GROUND].Set("RESULT_SKILL_HEAVEN_GROUND", ACTION_STAND, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVEN_GROUND].SetSoundID(SOUND_SLAYER_MERCY_GROUND) ;
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVEN_GROUND].Init( 2 );
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVEN_GROUND].SetMainNode( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVEN_GROUND][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVEN_GROUND][0].EffectSpriteType = EFFECTSPRITETYPE_HEAVEN_GROUND_START;
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVEN_GROUND][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVEN_GROUND][0].Count				= FrameSize[EFFECTSPRITETYPE_HEAVEN_GROUND_START];
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVEN_GROUND][0].LinkCount			= 5;
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVEN_GROUND][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVEN_GROUND][1].EffectSpriteType = EFFECTSPRITETYPE_HEAVEN_GROUND_REPEAT;
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVEN_GROUND][1].Step			= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVEN_GROUND][1].Count				= FrameSize[EFFECTSPRITETYPE_HEAVEN_GROUND_REPEAT];
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVEN_GROUND][1].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_HEAVEN_GROUND][1].SetDelayNode();	
	
	// 2006.10.20 sjheo end


	// 2006.11.10 chyaya begin - Dummy Action Skill add

	// SKILL_DUMMY_ACTION_MAGIC,			// Dummy Action Magic
	(*g_pActionInfoTable)[SKILL_DUMMY_ACTION_MAGIC].Set("SKILL_DUMMY_ACTION_MAGIC", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_DUMMY_ACTION_MAGIC].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[SKILL_DUMMY_ACTION_MAGIC].SetCastingActionInfo( CASTING_HEALING );	
	(*g_pActionInfoTable)[SKILL_DUMMY_ACTION_MAGIC].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[SKILL_DUMMY_ACTION_MAGIC].SetStartFrameAll( 7 );
	(*g_pActionInfoTable)[SKILL_DUMMY_ACTION_MAGIC].SetSoundID( SOUNDID_NULL );	

	// SKILL_DUMMY_ACTION_MAGIC,			// Dummy Action Magic
	(*g_pActionInfoTable)[RESULT_SKILL_DUMMY_ACTION_MAGIC].Set("RESULT_SKILL_DUMMY_ACTION_MAGIC", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[RESULT_SKILL_DUMMY_ACTION_MAGIC].SetSoundID( SOUNDID_NULL );

	// 2006.11.10 chyaya end - Dummy Action Skill add 
	

	// 2007.01.22 chyaya begin - Tanning Skill Add
	// MAGIC_EAT_CORPSE
	(*g_pActionInfoTable)[SKILL_TANNING].Set("SKILL_TANNING", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_USER);
//	(*g_pActionInfoTable)[SKILL_TANNING].SetStartFrameAll(20);
	(*g_pActionInfoTable)[SKILL_TANNING].SetSoundID(SOUNDID_NULL);	
	(*g_pActionInfoTable)[SKILL_TANNING].SetSelectCreature(FLAG_ACTIONINFO_SELECT_CORPSE);
//	(*g_pActionInfoTable)[SKILL_TANNING].UseRepeatFrame();
	(*g_pActionInfoTable)[SKILL_TANNING].SetCastingTime(40);

//	(*g_pActionInfoTable)[RESULT_SKILL_TANNING].Set("RESULT_SKILL_TANNING", ACTION_ATTACK, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER);
//	(*g_pActionInfoTable)[RESULT_SKILL_TANNING].SetSoundID( SOUNDID_NULL );
	// 2007.01.22 chyaya end - Tanning Skill Add

	// 2007.02.12 chyaya begin - Request Resurrect
 	(*g_pActionInfoTable)[SKILL_REQUEST_RESURRECT].Set("SKILL_GREAT_HEAL", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
 	(*g_pActionInfoTable)[SKILL_REQUEST_RESURRECT].SetSoundID( SOUNDID_NULL );
	
	(*g_pActionInfoTable)[RESULT_SKILL_REQUEST_RESURRECT].Set("RESULT_SKILL_REQUEST_RESURRECT", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_REQUEST_RESURRECT].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_REQUEST_RESURRECT].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SKILL_REQUEST_RESURRECT][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_REQUEST_RESURRECT][0].EffectSpriteType	= EFFECTSPRITETYPE_REQUEST_RESURRECT_LIGHT_FRONT;
	(*g_pActionInfoTable)[RESULT_SKILL_REQUEST_RESURRECT][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_REQUEST_RESURRECT][0].Count				= FrameSize[EFFECTSPRITETYPE_REQUEST_RESURRECT_LIGHT_FRONT];	
	(*g_pActionInfoTable)[RESULT_SKILL_REQUEST_RESURRECT][0].SoundID			= SOUND_SLAYER_GREAT_HEAL;

	(*g_pActionInfoTable)[SKILL_CLIENT_REQUEST_RESURRECT_WAITING].Set("RESULT_SKILL_REQUEST_RESURRECT", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[SKILL_CLIENT_REQUEST_RESURRECT_WAITING].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_REQUEST_RESURRECT_WAITING].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_REQUEST_RESURRECT_WAITING][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_REQUEST_RESURRECT_WAITING][0].EffectSpriteType	= EFFECTSPRITETYPE_REQUEST_RESURRECT_WAITING;
	(*g_pActionInfoTable)[SKILL_CLIENT_REQUEST_RESURRECT_WAITING][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_REQUEST_RESURRECT_WAITING][0].Count				= FrameSize[EFFECTSPRITETYPE_REQUEST_RESURRECT_WAITING];
	(*g_pActionInfoTable)[SKILL_CLIENT_REQUEST_RESURRECT_WAITING][0].SetDelayNode();
	// 2007.02.12 chyaya end - Request Resurrect


	// 2007.07.30 chyaya begin - Summon Lupeng
	(*g_pActionInfoTable)[RESULT_SUMMON_LUPENG].Set("RESULT_SUMMON_LUPENG", ACTION_STAND, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[RESULT_SUMMON_LUPENG].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SUMMON_LUPENG].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SUMMON_LUPENG].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SUMMON_LUPENG][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SUMMON_LUPENG][0].EffectSpriteType		= EFFECTSPRITETYPE_SUMMON_LUPENG;
	(*g_pActionInfoTable)[RESULT_SUMMON_LUPENG][0].Step					= 25;
	(*g_pActionInfoTable)[RESULT_SUMMON_LUPENG][0].Count				= FrameSize[EFFECTSPRITETYPE_SUMMON_LUPENG];
	// 2007.07.30 chyaya end - Summon Lupeng
	


	// 2007.08.30 chyaya begin - Rare Skill
	(*g_pActionInfoTable)[SKILL_MAGIC_SHIELD1].Set("SKILL_MAGIC_SHIELD1", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[SKILL_MAGIC_SHIELD1].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[SKILL_MAGIC_SHIELD1].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SHIELD );
	(*g_pActionInfoTable)[SKILL_MAGIC_SHIELD1].SetStartFrameAll( SLAYER_MAGIC_SELF_START_FRAME );
	(*g_pActionInfoTable)[SKILL_MAGIC_SHIELD1].SetSoundID(SOUNDID_NULL);

	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_SHIELD1].Set("RESULT_SKILL_MAGIC_SHIELD1", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_SHIELD1].SetSoundID(SOUND_SLAYER_MAGIC_SHIELD);
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_SHIELD1].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_SHIELD1][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_SHIELD1][0].EffectSpriteType	= EFFECTSPRITETYPE_MAGIC_SHEILD_SILVER;
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_SHIELD1][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_SHIELD1][0].Count				= FrameSize[EFFECTSPRITETYPE_MAGIC_SHEILD_SILVER];
	
	(*g_pActionInfoTable)[SKILL_MAGIC_SHIELD2].Set("SKILL_MAGIC_SHIELD2", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 1, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[SKILL_MAGIC_SHIELD2].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[SKILL_MAGIC_SHIELD2].SetWeaponType( FLAG_ACTIONINFO_WEAPON_SHIELD );
	(*g_pActionInfoTable)[SKILL_MAGIC_SHIELD2].SetStartFrameAll( SLAYER_MAGIC_SELF_START_FRAME );
	(*g_pActionInfoTable)[SKILL_MAGIC_SHIELD2].SetSoundID(SOUNDID_NULL);

	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_SHIELD2].Set("RESULT_SKILL_MAGIC_SHIELD2", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_SHIELD2].SetSoundID(SOUND_SLAYER_MAGIC_SHIELD);
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_SHIELD2].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_SHIELD2][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_SHIELD2][0].EffectSpriteType	= EFFECTSPRITETYPE_MAGIC_SHEILD_GOLD;
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_SHIELD2][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_MAGIC_SHIELD2][0].Count				= FrameSize[EFFECTSPRITETYPE_MAGIC_SHEILD_GOLD];
	
	(*g_pActionInfoTable)[SKILL_EAGLES_EYE1].Set("SKILL_EAGLES_EYE1", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_EAGLES_EYE1].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[SKILL_EAGLES_EYE1].SetStartFrameAll( SLAYER_MAGIC_SELF_START_FRAME );
	(*g_pActionInfoTable)[SKILL_EAGLES_EYE1].SetSoundID( SOUNDID_NULL );
	
	(*g_pActionInfoTable)[RESULT_SKILL_EAGLES_EYE1].Set("RESULT_SKILL_EAGLES_EYE1", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_EAGLES_EYE1].SetSoundID(SOUND_SLAYER_EAGLES_EYE);
	(*g_pActionInfoTable)[RESULT_SKILL_EAGLES_EYE1].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SKILL_EAGLES_EYE1][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_EAGLES_EYE1][0].EffectSpriteType		= EFFECTSPRITETYPE_EAGLES_EYE_SILVER;
	(*g_pActionInfoTable)[RESULT_SKILL_EAGLES_EYE1][0].Step					= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_EAGLES_EYE1][0].Count				= FrameSize[EFFECTSPRITETYPE_EAGLES_EYE_SILVER];
	
	(*g_pActionInfoTable)[SKILL_EAGLES_EYE2].Set("SKILL_EAGLES_EYE2", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_SELF | FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_EAGLES_EYE2].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[SKILL_EAGLES_EYE2].SetStartFrameAll( SLAYER_MAGIC_SELF_START_FRAME );
	(*g_pActionInfoTable)[SKILL_EAGLES_EYE2].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_EAGLES_EYE2].Set("RESULT_SKILL_EAGLES_EYE2", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_EAGLES_EYE2].SetSoundID(SOUND_SLAYER_EAGLES_EYE);
	(*g_pActionInfoTable)[RESULT_SKILL_EAGLES_EYE2].Init( 1 );		
	(*g_pActionInfoTable)[RESULT_SKILL_EAGLES_EYE2][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_EAGLES_EYE2][0].EffectSpriteType		= EFFECTSPRITETYPE_EAGLES_EYE_GOLD;
	(*g_pActionInfoTable)[RESULT_SKILL_EAGLES_EYE2][0].Step					= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_EAGLES_EYE2][0].Count				= FrameSize[EFFECTSPRITETYPE_EAGLES_EYE_GOLD];

	(*g_pActionInfoTable)[SKILL_FREEZE_RING1].Set("SKILL_FREEZE_RING1", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_FREEZE_RING1].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
 	(*g_pActionInfoTable)[SKILL_FREEZE_RING1].SetStartFrameAll( SLAYER_MAGIC_SELF_START_FRAME );
	(*g_pActionInfoTable)[SKILL_FREEZE_RING1].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_FREEZE_RING1].Set("RESULT_SKILL_FREEZE_RING1", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_FREEZE_RING1].SetSoundID(SOUND_SLAYER_FREEZE_RING);
	(*g_pActionInfoTable)[RESULT_SKILL_FREEZE_RING1].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_FREEZE_RING1][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_FREEZE_RING1][0].EffectSpriteType	= EFFECTSPRITETYPE_FREEZE_RING_5X5;
	(*g_pActionInfoTable)[RESULT_SKILL_FREEZE_RING1][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_FREEZE_RING1][0].Count				= FrameSize[EFFECTSPRITETYPE_FREEZE_RING_5X5];

	(*g_pActionInfoTable)[SKILL_FREEZE_RING2].Set("SKILL_FREEZE_RING2", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_FREEZE_RING2].SetUser(FLAG_ACTIONINFO_USER_SLAYER);
	(*g_pActionInfoTable)[SKILL_FREEZE_RING2].SetStartFrameAll( SLAYER_MAGIC_SELF_START_FRAME );
	(*g_pActionInfoTable)[SKILL_FREEZE_RING2].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[RESULT_SKILL_FREEZE_RING2].Set("RESULT_SKILL_FREEZE_RING2", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_FREEZE_RING2].SetSoundID(SOUND_SLAYER_FREEZE_RING);
	(*g_pActionInfoTable)[RESULT_SKILL_FREEZE_RING2].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_FREEZE_RING2][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_FREEZE_RING2][0].EffectSpriteType	= EFFECTSPRITETYPE_FREEZE_RING_7X7;
	(*g_pActionInfoTable)[RESULT_SKILL_FREEZE_RING2][0].Step				= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_FREEZE_RING2][0].Count				= FrameSize[EFFECTSPRITETYPE_FREEZE_RING_7X7];
	
	(*g_pActionInfoTable)[SKILL_CLIENT_FREEZE].Set("SKILL_CLIENT_FREEZE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[SKILL_CLIENT_FREEZE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_FREEZE].Init( 3 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_FREEZE].SetMainNode( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_FREEZE][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_FREEZE][0].EffectSpriteType	= EFFECTSPRITETYPE_FREEZE_ICE_START;
	(*g_pActionInfoTable)[SKILL_CLIENT_FREEZE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_FREEZE][0].Count				= FrameSize[EFFECTSPRITETYPE_FREEZE_ICE_START];
	(*g_pActionInfoTable)[SKILL_CLIENT_FREEZE][0].SoundID			= SOUND_VAMPIRE_PARALYSIS;
	(*g_pActionInfoTable)[SKILL_CLIENT_FREEZE][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_FREEZE][1].EffectSpriteType	= EFFECTSPRITETYPE_FREEZE_ICE_REPEAT;
	(*g_pActionInfoTable)[SKILL_CLIENT_FREEZE][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_FREEZE][1].Count				= FrameSize[EFFECTSPRITETYPE_FREEZE_ICE_REPEAT];
	(*g_pActionInfoTable)[SKILL_CLIENT_FREEZE][1].SetResultTime();
	(*g_pActionInfoTable)[SKILL_CLIENT_FREEZE][1].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_CLIENT_FREEZE][2].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_FREEZE][2].EffectSpriteType	= EFFECTSPRITETYPE_FREEZE_ICE_END;
	(*g_pActionInfoTable)[SKILL_CLIENT_FREEZE][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_FREEZE][2].Count				= FrameSize[EFFECTSPRITETYPE_FREEZE_ICE_END];
	
	// 2007.08.30 chyaya begin - Rare Skill

#if __CONTENTS(__NEW_PET_INCUBUS)
	(*g_pActionInfoTable)[SKILL_CLIENT_INCUBUS_ATTACK].Set("SKILL_CLIENT_INCUBUS_ATTACK", ACTION_DAMAGED, EFFECTSPRITETYPE_CURSE_BLIND, 25, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[SKILL_CLIENT_INCUBUS_ATTACK].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_CLIENT_INCUBUS_ATTACK].SetSoundID( SOUND_BOGLET_B_ATTACK );
	(*g_pActionInfoTable)[SKILL_CLIENT_INCUBUS_ATTACK].Init( 3 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_INCUBUS_ATTACK][0].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_INCUBUS_ATTACK][0].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_NAIL;
	(*g_pActionInfoTable)[SKILL_CLIENT_INCUBUS_ATTACK][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_INCUBUS_ATTACK][0].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_KNIFE_2];
	(*g_pActionInfoTable)[SKILL_CLIENT_INCUBUS_ATTACK][0].SoundID				= SOUND_VAMPIRE_MISC_D;	
	(*g_pActionInfoTable)[SKILL_CLIENT_INCUBUS_ATTACK][1].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_INCUBUS_ATTACK][1].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_NAIL;
	(*g_pActionInfoTable)[SKILL_CLIENT_INCUBUS_ATTACK][1].Step				= 30;
	(*g_pActionInfoTable)[SKILL_CLIENT_INCUBUS_ATTACK][1].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_KNIFE_2];
	(*g_pActionInfoTable)[SKILL_CLIENT_INCUBUS_ATTACK][2].EffectGeneratorID	= EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[SKILL_CLIENT_INCUBUS_ATTACK][2].EffectSpriteType	= EFFECTSPRITETYPE_BLOODY_NAIL;
	(*g_pActionInfoTable)[SKILL_CLIENT_INCUBUS_ATTACK][2].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_INCUBUS_ATTACK][2].Count				= FrameSize[EFFECTSPRITETYPE_BLOODY_KNIFE_2];
#endif //__NEW_PET_INCUBUS

#if __CONTENTS(__ONIBLA)	
	(*g_pActionInfoTable)[SKILL_ONIBLA_DROP_SKULL].Set("SKILL_ONIBLA_DROP_SKULL", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET | FLAG_ACTIONINFO_START_SKY, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_ONIBLA_DROP_SKULL].SetCastingActionInfo( CASTING_HEALING );
	(*g_pActionInfoTable)[SKILL_ONIBLA_DROP_SKULL].SetCastingFramesAll( 24 );
	(*g_pActionInfoTable)[SKILL_ONIBLA_DROP_SKULL].SetStartFrameAll( 5 );	
	(*g_pActionInfoTable)[SKILL_ONIBLA_DROP_SKULL].SetSoundID( SOUND_SLAYER_VISIBLE );
	(*g_pActionInfoTable)[SKILL_ONIBLA_DROP_SKULL].Init( 2 );
	(*g_pActionInfoTable)[SKILL_ONIBLA_DROP_SKULL][0].EffectGeneratorID	= EFFECTGENERATORID_MULTIPLE_FALLING;
	(*g_pActionInfoTable)[SKILL_ONIBLA_DROP_SKULL][0].EffectSpriteType	= EFFECTSPRITETYPE_DROPSKULL_FALLING;
	(*g_pActionInfoTable)[SKILL_ONIBLA_DROP_SKULL][0].Step				= 30;
	(*g_pActionInfoTable)[SKILL_ONIBLA_DROP_SKULL][0].Count				= FrameSize[EFFECTSPRITETYPE_DROPSKULL_FALLING];
	(*g_pActionInfoTable)[SKILL_ONIBLA_DROP_SKULL][0].SetDelayNode();
	(*g_pActionInfoTable)[SKILL_ONIBLA_DROP_SKULL][0].SetResultTime();
	(*g_pActionInfoTable)[SKILL_ONIBLA_DROP_SKULL][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_ONIBLA_DROP_SKULL][1].EffectSpriteType	= EFFECTSPRITETYPE_DROPSKULL_BROKEN;
	(*g_pActionInfoTable)[SKILL_ONIBLA_DROP_SKULL][1].Step				= 15;
	(*g_pActionInfoTable)[SKILL_ONIBLA_DROP_SKULL][1].Count				= FrameSize[EFFECTSPRITETYPE_DROPSKULL_BROKEN];	
	(*g_pActionInfoTable)[SKILL_ONIBLA_DROP_SKULL].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, SKILL_ONIBLA_DROP_SKULL );	// 맞는 결과를 표현한다.	

	(*g_pActionInfoTable)[RESULT_SKILL_ONIBLA_DROP_SKULL].Set("RESULT_SKILL_ONIBLA_DROP_SKULL", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_ONIBLA_DROP_SKULL].SetSoundID( SOUNDID_NULL );

	(*g_pActionInfoTable)[SKILL_ONIBLA_RAISE_BONE].Set("SKILL_ONIBLA_RAISE_BONE", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET );
	(*g_pActionInfoTable)[SKILL_ONIBLA_RAISE_BONE].SetSoundID( SOUND_ICEWAVE );
	(*g_pActionInfoTable)[SKILL_ONIBLA_RAISE_BONE].Init( 1 );
	(*g_pActionInfoTable)[SKILL_ONIBLA_RAISE_BONE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_ONIBLA_RAISE_BONE][0].EffectSpriteType = EFFECTSPRITETYPE_RAISEBONE;
	(*g_pActionInfoTable)[SKILL_ONIBLA_RAISE_BONE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_ONIBLA_RAISE_BONE][0].Count				= FrameSize[EFFECTSPRITETYPE_RAISEBONE];

	(*g_pActionInfoTable)[RESULT_SKILL_ONIBLA_RAISE_BONE].Set("RESULT_SKILL_ONIBLA_RAISE_BONE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[RESULT_SKILL_ONIBLA_RAISE_BONE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[RESULT_SKILL_ONIBLA_RAISE_BONE].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_ONIBLA_RAISE_BONE][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_ONIBLA_RAISE_BONE][0].EffectSpriteType = EFFECTSPRITETYPE_EARTHS_TEETH_DAMAGED;
	(*g_pActionInfoTable)[RESULT_SKILL_ONIBLA_RAISE_BONE][0].Step			= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_ONIBLA_RAISE_BONE][0].Count			= FrameSize[ EFFECTSPRITETYPE_EARTHS_TEETH_DAMAGED ];

	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_RAISE_BONE].Set("SKILL_CLIENT_ONIBLA_RAISE_BONE", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET );
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_RAISE_BONE].SetSoundID( SOUND_SLAYER_SWORD_THUNDER_SPARK );
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_RAISE_BONE].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_RAISE_BONE][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_RAISE_BONE][0].EffectSpriteType = EFFECTSPRITETYPE_RAISEBONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_RAISE_BONE][0].SoundID			 = SOUND_TRAP_B;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_RAISE_BONE][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_RAISE_BONE][0].Count				= FrameSize[EFFECTSPRITETYPE_RAISEBONE];

	(*g_pActionInfoTable)[SKILL_AGONY_CHILD_DROP_HEAD].Set("SKILL_AGONY_CHILD_DROP_HEAD", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_SKY, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_AGONY_CHILD_DROP_HEAD].SetStartWithCasting();
	(*g_pActionInfoTable)[SKILL_AGONY_CHILD_DROP_HEAD].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_AGONY_CHILD_DROP_HEAD].Init( 2 );		
	(*g_pActionInfoTable)[SKILL_AGONY_CHILD_DROP_HEAD][0].EffectGeneratorID	= EFFECTGENERATORID_METEOR_DROP;
	(*g_pActionInfoTable)[SKILL_AGONY_CHILD_DROP_HEAD][0].EffectSpriteType	= EFFECTSPRITETYPE_DROPHEAD_FALLING;
	(*g_pActionInfoTable)[SKILL_AGONY_CHILD_DROP_HEAD][0].Step				= 30;
	(*g_pActionInfoTable)[SKILL_AGONY_CHILD_DROP_HEAD][0].Count				= FrameSize[EFFECTSPRITETYPE_DROPHEAD_FALLING]*2;
	(*g_pActionInfoTable)[SKILL_AGONY_CHILD_DROP_HEAD][0].SoundID			= SOUND_ITEM_FLYING_BOTTLE;
	(*g_pActionInfoTable)[SKILL_AGONY_CHILD_DROP_HEAD][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_AGONY_CHILD_DROP_HEAD][1].EffectSpriteType	= EFFECTSPRITETYPE_DROPHEAD_BROKEN;
	(*g_pActionInfoTable)[SKILL_AGONY_CHILD_DROP_HEAD][1].Step				= 25;
	(*g_pActionInfoTable)[SKILL_AGONY_CHILD_DROP_HEAD][1].Count				= FrameSize[EFFECTSPRITETYPE_DROPHEAD_BROKEN];
	(*g_pActionInfoTable)[SKILL_AGONY_CHILD_DROP_HEAD][1].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_AGONY_CHILD_DROP_HEAD][1].SoundID			= SOUND_SLAYER_ATTACK_BOMB;


	(*g_pActionInfoTable)[RESULT_SKILL_AGONY_CHILD_DROP_HEAD].Set("RESULT_SKILL_AGONY_CHILD_DROP_HEAD", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_SKY);
	(*g_pActionInfoTable)[RESULT_SKILL_AGONY_CHILD_DROP_HEAD].SetStartWithCasting();
	(*g_pActionInfoTable)[RESULT_SKILL_AGONY_CHILD_DROP_HEAD].SetSoundID( SOUND_DIM_DIE );
	


	(*g_pActionInfoTable)[SKILL_SPANIEL_THROWING_AXE].Set("SKILL_SPANIEL_THROWING_AXE", ACTION_OUSTERS_MAGIC_ATTACK, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, OustersActionDelay[ACTION_OUSTERS_MAGIC_ATTACK]);
	(*g_pActionInfoTable)[SKILL_SPANIEL_THROWING_AXE].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_SPANIEL_THROWING_AXE].SetUseActionStep();
	(*g_pActionInfoTable)[SKILL_SPANIEL_THROWING_AXE].SetStartFrameAll( 8 );
	(*g_pActionInfoTable)[SKILL_SPANIEL_THROWING_AXE].Init( 2 );
	(*g_pActionInfoTable)[SKILL_SPANIEL_THROWING_AXE][0].EffectGeneratorID = EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[SKILL_SPANIEL_THROWING_AXE][0].EffectSpriteType = EFFECTSPRITETYPE_THROWINGAXE_UP;
	(*g_pActionInfoTable)[SKILL_SPANIEL_THROWING_AXE][0].Step				= 20;
	(*g_pActionInfoTable)[SKILL_SPANIEL_THROWING_AXE][0].Count				= FrameSize[EFFECTSPRITETYPE_THROWINGAXE_UP]*5;
	(*g_pActionInfoTable)[SKILL_SPANIEL_THROWING_AXE][0].LinkCount			= 0;
	(*g_pActionInfoTable)[SKILL_SPANIEL_THROWING_AXE][0].SoundID			= SOUNDID_NULL;
	(*g_pActionInfoTable)[SKILL_SPANIEL_THROWING_AXE][1].EffectGeneratorID = EFFECTGENERATORID_ATTACK_CREATURE;
	(*g_pActionInfoTable)[SKILL_SPANIEL_THROWING_AXE][1].EffectSpriteType = EFFECTSPRITETYPE_THROWINGAXE_DOWN;
	(*g_pActionInfoTable)[SKILL_SPANIEL_THROWING_AXE][1].Step				= 20;
	(*g_pActionInfoTable)[SKILL_SPANIEL_THROWING_AXE][1].Count				= FrameSize[EFFECTSPRITETYPE_THROWINGAXE_DOWN]*5;
	(*g_pActionInfoTable)[SKILL_SPANIEL_THROWING_AXE][1].SoundID			= SOUNDID_NULL;

    (*g_pActionInfoTable)[RESULT_SKILL_SPANIEL_THROWING_AXE].Set("RESULT_SKILL_SPANIEL_THROWING_AXE", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER);
	(*g_pActionInfoTable)[RESULT_SKILL_SPANIEL_THROWING_AXE].SetSoundID( SOUND_BBR_ATT2 );
	(*g_pActionInfoTable)[RESULT_SKILL_SPANIEL_THROWING_AXE].Init( 1 );
	(*g_pActionInfoTable)[RESULT_SKILL_SPANIEL_THROWING_AXE][0].EffectGeneratorID = EFFECTGENERATORID_ATTACH_CREATURE;
	(*g_pActionInfoTable)[RESULT_SKILL_SPANIEL_THROWING_AXE][0].EffectSpriteType = EFFECTSPRITETYPE_EARTHS_TEETH_DAMAGED;
	(*g_pActionInfoTable)[RESULT_SKILL_SPANIEL_THROWING_AXE][0].Step			= 25;
	(*g_pActionInfoTable)[RESULT_SKILL_SPANIEL_THROWING_AXE][0].Count			= FrameSize[ EFFECTSPRITETYPE_EARTHS_TEETH_DAMAGED ];

	(*g_pActionInfoTable)[SKILL_BLACKASTRAL_MAGIC_CRYSTAL].Set("SKILL_BLACKASTRAL_MAGIC_CRYSTAL", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_START_SKY | FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[SKILL_BLACKASTRAL_MAGIC_CRYSTAL].SetSoundID( SOUNDID_NULL );
	

	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL].Set("RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL].SetSoundID( SOUND_OUSTERS_FURY_OF_GNOME );
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL].Init( 6 );
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][0].EffectSpriteType = EFFECTSPRITETYPE_MAGIC_CRYSTAL_FALLING;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][0].Step				= 30;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][0].Count				= FrameSize[EFFECTSPRITETYPE_MAGIC_CRYSTAL_FALLING];
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][0].SoundID			= SOUND_OUSTERS_FURY_OF_GNOME;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][0].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][1].EffectSpriteType = EFFECTSPRITETYPE_MAGIC_CRYSTAL_GROUND;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][1].Step				= 30;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][1].Count				= FrameSize[EFFECTSPRITETYPE_MAGIC_CRYSTAL_GROUND];
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][1].SoundID			= SOUNDID_NULL;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][2].EffectGeneratorID = EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][2].EffectSpriteType = EFFECTSPRITETYPE_MAGIC_CRYSTAL_GROUND_STOP;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][2].Step				= 30;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][2].Count				= FrameSize[EFFECTSPRITETYPE_MAGIC_CRYSTAL_GROUND_STOP];
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][2].SoundID			= SOUNDID_NULL;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][2].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][2].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][3].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][3].EffectSpriteType = EFFECTSPRITETYPE_MAGIC_CRYSTAL_STOP;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][3].Step				= 30;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][3].Count				= FrameSize[EFFECTSPRITETYPE_MAGIC_CRYSTAL_GROUND_STOP];
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][3].SoundID			= SOUNDID_NULL;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][3].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][4].EffectGeneratorID = EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][4].EffectSpriteType = EFFECTSPRITETYPE_MAGIC_CRYSTAL_GROUND_ERASE;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][4].Step				= 30;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][4].Count				= FrameSize[EFFECTSPRITETYPE_MAGIC_CRYSTAL_GROUND_ERASE];
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][4].SoundID			= SOUNDID_NULL;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][4].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][5].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][5].EffectSpriteType = EFFECTSPRITETYPE_MAGIC_CRYSTAL_BROKEN;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][5].Step				= 30;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][5].Count				= FrameSize[EFFECTSPRITETYPE_MAGIC_CRYSTAL_BROKEN];
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][5].SoundID			= SOUNDID_NULL;
	(*g_pActionInfoTable)[RESULT_SKILL_BLACKASTRAL_MAGIC_CRYSTAL][5].SetResultTime();

	(*g_pActionInfoTable)[SKILL_WHITEASTRAL_SPELL_CRYSTAL].Set("SKILL_WHITEASTRAL_SPELL_CRYSTAL", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_START_SKY | FLAG_ACTIONINFO_TARGET_ZONE);
	(*g_pActionInfoTable)[SKILL_WHITEASTRAL_SPELL_CRYSTAL].SetSoundID( SOUNDID_NULL );


	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL].Set("RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, 400);
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL].SetSoundID( SOUND_OUSTERS_FURY_OF_GNOME );
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL].SetStartFrameAll( 0 );
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL].Init( 6 );
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][0].EffectSpriteType = EFFECTSPRITETYPE_SPELL_CRYSTAL_FALLING;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][0].Step				= 30;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][0].Count				= FrameSize[EFFECTSPRITETYPE_SPELL_CRYSTAL_FALLING];
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][0].SoundID			= SOUND_OUSTERS_FURY_OF_GNOME;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][0].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][1].EffectGeneratorID = EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][1].EffectSpriteType = EFFECTSPRITETYPE_SPELL_CRYSTAL_GROUND;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][1].Step				= 30;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][1].Count				= FrameSize[EFFECTSPRITETYPE_SPELL_CRYSTAL_GROUND];
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][1].SoundID			= SOUNDID_NULL;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][2].EffectGeneratorID = EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][2].EffectSpriteType = EFFECTSPRITETYPE_SPELL_CRYSTAL_GROUND_STOP;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][2].Step				= 30;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][2].Count				= FrameSize[EFFECTSPRITETYPE_SPELL_CRYSTAL_GROUND_STOP];
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][2].SoundID			= SOUNDID_NULL;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][2].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][2].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][3].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][3].EffectSpriteType = EFFECTSPRITETYPE_SPELL_CRYSTAL_STOP;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][3].Step				= 30;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][3].Count				= FrameSize[EFFECTSPRITETYPE_SPELL_CRYSTAL_GROUND_STOP];
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][3].SoundID			= SOUNDID_NULL;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][3].SetDelayNode();
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][4].EffectGeneratorID = EFFECTGENERATORID_ATTACH_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][4].EffectSpriteType	= EFFECTSPRITETYPE_SPELL_CRYSTAL_GROUND_ERASE;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][4].Step				= 30;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][4].Count				= FrameSize[EFFECTSPRITETYPE_SPELL_CRYSTAL_GROUND_ERASE];
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][4].SoundID			= SOUNDID_NULL;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][4].LinkCount			= 0;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][5].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][5].EffectSpriteType = EFFECTSPRITETYPE_SPELL_CRYSTAL_BROKEN;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][5].Step				= 30;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][5].Count				= FrameSize[EFFECTSPRITETYPE_SPELL_CRYSTAL_BROKEN];
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][5].SoundID			= SOUNDID_NULL;
	(*g_pActionInfoTable)[RESULT_SKILL_WHITEASTRAL_SPELL_CRYSTAL][5].SetResultTime();

	
	(*g_pActionInfoTable)[SKILL_AGONY_CHILD_SHADOW_FOUR].Set("SKILL_AGONY_CHILD_SHADOW_FOUR", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_AGONY_CHILD_SHADOW_FOUR].SetStartFrameAll( 7 );	
	(*g_pActionInfoTable)[SKILL_AGONY_CHILD_SHADOW_FOUR].SetSoundID( SOUND_DESTRUCTION_SPEAR );

	(*g_pActionInfoTable)[RESULT_SKILL_AGONY_CHILD_SHADOW_FOUR].Set("RESULT_SKILL_AGONY_CHILD_SHADOW_FOUR", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_AGONY_CHILD_SHADOW_FOUR].SetSoundID( SOUNDID_NULL);


	(*g_pActionInfoTable)[SKILL_VILLAIN_LADY_GHOST_SHADOW].Set("SKILL_VILLAIN_LADY_GHOST_SHADOW", ACTION_MAGIC, EFFECTSPRITETYPE_NULL, 5, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, ActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_VILLAIN_LADY_GHOST_SHADOW].SetStartFrameAll( 7 );	
	(*g_pActionInfoTable)[SKILL_VILLAIN_LADY_GHOST_SHADOW].SetSoundID( SOUND_SIAMESE_VAMPIRE_DRAIN );

	(*g_pActionInfoTable)[RESULT_SKILL_VILLAIN_LADY_GHOST_SHADOW].Set("RESULT_SKILL_VILLAIN_LADY_GHOST_SHADOW", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_SELF);
	(*g_pActionInfoTable)[RESULT_SKILL_VILLAIN_LADY_GHOST_SHADOW].SetSoundID( SOUNDID_NULL);


	(*g_pActionInfoTable)[SKILL_VILLAIN_LADY_SELF_DESTRUCTION].Set("SKILL_VILLAIN_LADY_SELF_DESTRUCTION", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET , VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[SKILL_VILLAIN_LADY_SELF_DESTRUCTION].SetSoundID( SOUND_HB_DAMAGE );
	(*g_pActionInfoTable)[SKILL_VILLAIN_LADY_SELF_DESTRUCTION].Init( 1 );
	(*g_pActionInfoTable)[SKILL_VILLAIN_LADY_SELF_DESTRUCTION][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_VILLAIN_LADY_SELF_DESTRUCTION][0].EffectSpriteType = EFFECTSPRITETYPE_ONIBLA_VILLAINLADY_SELFDESTRUCTION;
	(*g_pActionInfoTable)[SKILL_VILLAIN_LADY_SELF_DESTRUCTION][0].SoundID			 = SOUND_ITEM_BOOM4;
	(*g_pActionInfoTable)[SKILL_VILLAIN_LADY_SELF_DESTRUCTION][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_VILLAIN_LADY_SELF_DESTRUCTION][0].Count				= FrameSize[EFFECTSPRITETYPE_ONIBLA_VILLAINLADY_SELFDESTRUCTION];

	(*g_pActionInfoTable)[RESULT_SKILL_VILLAIN_LADY_SELF_DESTRUCTION].Set("RESULT_SKILL_VILLAIN_LADY_SELF_DESTRUCTION", ACTION_DAMAGED, EFFECTSPRITETYPE_NULL, 8, FLAG_ACTIONINFO_TARGET_OTHER, FLAG_ACTIONINFO_START_USER, VampireActionDelay[ACTION_MAGIC]);
	(*g_pActionInfoTable)[RESULT_SKILL_VILLAIN_LADY_SELF_DESTRUCTION].SetSoundID( SOUNDID_NULL );


	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_LEFT_UP].Set("SKILL_CLIENT_ONIBLA_BLOCK_DOOR_LEFT_UP", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET );
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_LEFT_UP].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_LEFT_UP].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_LEFT_UP][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_LEFT_UP][0].EffectSpriteType = EFFECTSPRITETYPE_ONIBLA_BLOCK_DOOR_LEFT_UP;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_LEFT_UP][0].SoundID			 = SOUND_TRAP_B;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_LEFT_UP][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_LEFT_UP][0].Count				= FrameSize[EFFECTSPRITETYPE_ONIBLA_BLOCK_DOOR_LEFT_UP];

	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_LEFT_UP_OPEN].Set("SKILL_CLIENT_ONIBLA_BLOCK_DOOR_LEFT_UP_OPEN", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET );
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_LEFT_UP_OPEN].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_LEFT_UP_OPEN].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_LEFT_UP_OPEN][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_LEFT_UP_OPEN][0].EffectSpriteType = EFFECTSPRITETYPE_ONIBLA_BLOCK_DOOR_LEFT_UP_OPEN;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_LEFT_UP_OPEN][0].SoundID			 = SOUND_TRAP_B;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_LEFT_UP_OPEN][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_LEFT_UP_OPEN][0].Count				= FrameSize[EFFECTSPRITETYPE_ONIBLA_BLOCK_DOOR_LEFT_UP_OPEN];

	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_RIGHT_UP].Set("SKILL_CLIENT_ONIBLA_BLOCK_DOOR_RIGHT_UP", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET );
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_RIGHT_UP].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_RIGHT_UP].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_RIGHT_UP][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_RIGHT_UP][0].EffectSpriteType = EFFECTSPRITETYPE_ONIBLA_BLOCK_DOOR_RIGHT_UP;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_RIGHT_UP][0].SoundID			 = SOUND_TRAP_B;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_RIGHT_UP][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_RIGHT_UP][0].Count				= FrameSize[EFFECTSPRITETYPE_ONIBLA_BLOCK_DOOR_RIGHT_UP];

	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_RIGHT_UP_OPEN].Set("SKILL_CLIENT_ONIBLA_BLOCK_DOOR_LEFT_UP_OPEN", ACTION_STAND, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET );
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_RIGHT_UP_OPEN].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_RIGHT_UP_OPEN].Init( 1 );
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_RIGHT_UP_OPEN][0].EffectGeneratorID = EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_RIGHT_UP_OPEN][0].EffectSpriteType = EFFECTSPRITETYPE_ONIBLA_BLOCK_DOOR_RIGHT_UP_OPEN;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_RIGHT_UP_OPEN][0].SoundID			 = SOUND_TRAP_B;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_RIGHT_UP_OPEN][0].Step				= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BLOCK_DOOR_RIGHT_UP_OPEN][0].Count				= FrameSize[EFFECTSPRITETYPE_ONIBLA_BLOCK_DOOR_RIGHT_UP_OPEN];

	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BARRIER_RIGHT_UP].Set("SKILL_CLIENT_ONIBLA_BARRIER_RIGHT_UP", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BARRIER_RIGHT_UP].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BARRIER_RIGHT_UP].SetStartFrameAll(0);
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BARRIER_RIGHT_UP].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BARRIER_RIGHT_UP][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BARRIER_RIGHT_UP][0].EffectSpriteType		= EFFECTSPRITETYPE_ONIBLA_BARRIER_RIGHT_UP;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BARRIER_RIGHT_UP][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BARRIER_RIGHT_UP][0].Count				= FrameSize[EFFECTSPRITETYPE_ONIBLA_BARRIER_RIGHT_UP];

	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BARRIER_LEFT_UP].Set("SKILL_CLIENT_ONIBLA_BARRIER_LEFT_UP", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BARRIER_LEFT_UP].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BARRIER_LEFT_UP].SetStartFrameAll(0);
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BARRIER_LEFT_UP].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BARRIER_LEFT_UP][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BARRIER_LEFT_UP][0].EffectSpriteType		= EFFECTSPRITETYPE_ONIBLA_BARRIER_LEFT_UP;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BARRIER_LEFT_UP][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_BARRIER_LEFT_UP][0].Count				= FrameSize[EFFECTSPRITETYPE_ONIBLA_BARRIER_LEFT_UP];

	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_EXIT_RIGHT_UP].Set("SKILL_CLIENT_ONIBLA_BARRIER_LEFT_UP", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_EXIT_RIGHT_UP].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_EXIT_RIGHT_UP].SetStartFrameAll(0);
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_EXIT_RIGHT_UP].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_EXIT_RIGHT_UP][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_EXIT_RIGHT_UP][0].EffectSpriteType		= EFFECTSPRITETYPE_ONIBLA_EXIT_RIGHT_UP;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_EXIT_RIGHT_UP][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_EXIT_RIGHT_UP][0].Count				= FrameSize[EFFECTSPRITETYPE_ONIBLA_EXIT_RIGHT_UP];

	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_EXIT_LEFT_UP].Set("SKILL_CLIENT_ONIBLA_EXIT_LEFT_UP", ACTION_STAND, EFFECTSPRITETYPE_NULL, 10, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_EXIT_LEFT_UP].SetSoundID( SOUNDID_NULL );
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_EXIT_LEFT_UP].SetStartFrameAll(0);
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_EXIT_LEFT_UP].Init( 1 );		
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_EXIT_LEFT_UP][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_EXIT_LEFT_UP][0].EffectSpriteType		= EFFECTSPRITETYPE_ONIBLA_EXIT_LEFT_UP;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_EXIT_LEFT_UP][0].Step					= 25;
	(*g_pActionInfoTable)[SKILL_CLIENT_ONIBLA_EXIT_LEFT_UP][0].Count				= FrameSize[EFFECTSPRITETYPE_ONIBLA_EXIT_LEFT_UP];

#endif //__ONIBLA

#if __CONTENTS(__20091116_ADD_RARE_SKILL)
	// 마그마 데토네이션 1
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_1].Set("SKILL_BLADE_MAGMA_DETONATION_1", ACTION_SLAYER_BLADE_2, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_BLADE_2]);
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_1].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_1].SetStartFrameAll(5);
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_1].SetSoundID( SOUND_SLAYER_SWORDOFTHOR );
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_1].Init(2);		
	//(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_1].SetMainNode(1);
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_1].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_1].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, RESULT_SKILL_BLADE_MAGMA_DETONATION_1 );	// 맞는 결과를 표현한다.	
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_1][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_1][0].EffectSpriteType	= EFFECTSPRITETYPE_BLADE_MAGMA_DETONATION_1_RARE_SKILL_DROP;
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_1][0].Step				= 20;
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_1][0].LinkCount			= FrameSize[EFFECTSPRITETYPE_BLADE_MAGMA_DETONATION_1_RARE_SKILL_DROP];
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_1][0].Count				= FrameSize[EFFECTSPRITETYPE_BLADE_MAGMA_DETONATION_1_RARE_SKILL_DROP];
// 	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_1][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
// 	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_1][1].EffectSpriteType	= EFFECTSPRITETYPE_BLADE_MAGMA_DETONATION_1_RARE_SKILL_REPEAT;
// 	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_1][1].Step				= 20;
// 	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_1][1].LinkCount			= FrameSize[EFFECTSPRITETYPE_BLADE_MAGMA_DETONATION_1_RARE_SKILL_REPEAT] + 1;
// 	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_1][1].Count				= FrameSize[EFFECTSPRITETYPE_BLADE_MAGMA_DETONATION_1_RARE_SKILL_REPEAT] + 1;
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_1][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_1][1].EffectSpriteType	= EFFECTSPRITETYPE_BLADE_MAGMA_DETONATION_1_RARE_SKILL_END;
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_1][1].Step				= 20;
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_1][1].LinkCount			= FrameSize[EFFECTSPRITETYPE_BLADE_MAGMA_DETONATION_1_RARE_SKILL_END] + 1;
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_1][1].Count				= FrameSize[EFFECTSPRITETYPE_BLADE_MAGMA_DETONATION_1_RARE_SKILL_END] + 1;

	(*g_pActionInfoTable)[RESULT_SKILL_BLADE_MAGMA_DETONATION_1].Set("RESULT_SKILL_BLADE_MAGMA_DETONATION_1", ACTION_STAND, EFFECTSPRITETYPE_NULL, 7, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
 	(*g_pActionInfoTable)[RESULT_SKILL_BLADE_MAGMA_DETONATION_1].SetSoundID( SOUNDID_NULL );

	// 마그마 데토네이션 2
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_2].Set("SKILL_BLADE_MAGMA_DETONATION_2", ACTION_SLAYER_BLADE_2, EFFECTSPRITETYPE_NULL, 3, FLAG_ACTIONINFO_TARGET_OTHER | FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET, ActionDelay[ACTION_SLAYER_BLADE_2]);
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_2].SetWeaponType( FLAG_ACTIONINFO_WEAPON_BLADE );
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_2].SetStartFrameAll(5);
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_2].SetSoundID( SOUND_SLAYER_SWORDOFTHOR );
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_2].Init(2);		
	//(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_2].SetMainNode(1);
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_2].SetActionStepCnt(2) ; 
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_2].SetActionResult( ACTIONRESULTNODE_ACTIONINFO, RESULT_SKILL_BLADE_MAGMA_DETONATION_2 );	// 맞는 결과를 표현한다.	
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_2][0].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_2][0].EffectSpriteType	= EFFECTSPRITETYPE_BLADE_MAGMA_DETONATION_2_RARE_SKILL_DROP;
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_2][0].Step				= 20;
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_2][0].LinkCount			= FrameSize[EFFECTSPRITETYPE_BLADE_MAGMA_DETONATION_2_RARE_SKILL_DROP];
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_2][0].Count				= FrameSize[EFFECTSPRITETYPE_BLADE_MAGMA_DETONATION_2_RARE_SKILL_DROP];
// 	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_2][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
// 	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_2][1].EffectSpriteType	= EFFECTSPRITETYPE_BLADE_MAGMA_DETONATION_2_RARE_SKILL_REPEAT;
// 	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_2][1].Step				= 20;
// 	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_2][1].LinkCount			= FrameSize[EFFECTSPRITETYPE_BLADE_MAGMA_DETONATION_2_RARE_SKILL_REPEAT] + 1;
// 	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_2][1].Count				= FrameSize[EFFECTSPRITETYPE_BLADE_MAGMA_DETONATION_2_RARE_SKILL_REPEAT] + 1;
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_2][1].EffectGeneratorID	= EFFECTGENERATORID_STOP_ZONE;
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_2][1].EffectSpriteType	= EFFECTSPRITETYPE_BLADE_MAGMA_DETONATION_2_RARE_SKILL_END;
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_2][1].Step				= 20;
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_2][1].LinkCount			= FrameSize[EFFECTSPRITETYPE_BLADE_MAGMA_DETONATION_2_RARE_SKILL_END] + 1;
	(*g_pActionInfoTable)[SKILL_BLADE_MAGMA_DETONATION_2][1].Count				= FrameSize[EFFECTSPRITETYPE_BLADE_MAGMA_DETONATION_2_RARE_SKILL_END] + 1;

	(*g_pActionInfoTable)[RESULT_SKILL_BLADE_MAGMA_DETONATION_2].Set("RESULT_SKILL_BLADE_MAGMA_DETONATION_2", ACTION_STAND, EFFECTSPRITETYPE_NULL, 7, FLAG_ACTIONINFO_TARGET_ZONE, FLAG_ACTIONINFO_START_TARGET);
 	(*g_pActionInfoTable)[RESULT_SKILL_BLADE_MAGMA_DETONATION_2].SetSoundID( SOUNDID_NULL );
#endif //__20091116_ADD_RARE_SKILL


		
	InitActionInfoTableVampire(CreatureFPK, FrameSize, VampireActionDelay);
	InitActionInfoTableOusters(OustersFPK, FrameSize, OustersActionDelay);
	InitActionInfoTableFireCracker(FrameSize);
	
	//-----------------------------------
	// Save To File
	//-----------------------------------
	std::ofstream actionInfoFile(g_pFileDef->getProperty("FILE_INFO_ACTION").c_str(), std::ios::binary);	
	(*g_pActionInfoTable).SaveToFile(actionInfoFile);
	actionInfoFile.close();
#endif

	return TRUE;
}
