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

#define SAVE_TO_FILE

HRESULT InitFail(LPCTSTR szError,...);
bool 
FileOpenBinary(const char* filename, ivfstream& file);
//---------------------------------------------------------------------------
// Open File
//---------------------------------------------------------------------------
bool 
FileCheck(const char* filename);
void MakeEventInfo();

BOOL InitZoneInfo()
{
	//---------------------------------------------------------------------
	//
	//         Zone 정보 생성
	//
	//---------------------------------------------------------------------
	///*
#ifdef SAVE_TO_FILE
	///*
	ZONETABLE_INFO* pZoneInfo;
	// test1

	// 필드맵
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 11;
	pZoneInfo->Name				= "에슬라니안 NE";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Eslania_NE.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Eslania_NE.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->HolyLand			= false;
// 	pZoneInfo->MusicIDSlayer	= MUSIC_WHISPER;
// 	pZoneInfo->MusicIDVampire	= MUSIC_WINDMILL;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_CROW );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_WOLF_CRY );
	pZoneInfo->MinimapSpriteID	= 138 ; //86;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(304, 0, 404, 50);
// 	pZoneInfo->WorldMapInfo.EncourageSlayerLevelMin		= 0;
// 	pZoneInfo->WorldMapInfo.EncourageSlayerLevelMax		= 0;
// 	pZoneInfo->WorldMapInfo.EncourageVampireLevelMin	= 0;
// 	pZoneInfo->WorldMapInfo.EncourageVampireLevelMax	= 0;
// 	pZoneInfo->WorldMapInfo.EncourageOustersLevelMin	= 0;
// 	pZoneInfo->WorldMapInfo.EncourageOustersLevelMax	= 0;
// 	pZoneInfo->WorldMapInfo.MiscDescription				= "간단 설명이 없으면 이 줄을 지운다.";
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 12;
	pZoneInfo->Name				= "에슬라니안 NW";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Eslania_NW.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Eslania_NW.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_GEHENNA;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_CROW );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_GRRR );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_WOLF_CRY );
	pZoneInfo->MinimapSpriteID	= 139 ; // 87;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(203, 0, 303, 50);
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 13;
	pZoneInfo->Name				= "에슬라니안 SE";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Eslania_SE.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Eslania_SE.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_WHISPER;
// 	pZoneInfo->MusicIDVampire	= MUSIC_WINDMILL;
	//pZoneInfo->SoundIDList.push_back( SOUND_WORLD_CROW );
	//pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	//pZoneInfo->SoundIDList.push_back( SOUND_WORLD_WOLF_CRY );
	//pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->MinimapSpriteID	= 88;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(304, 51, 404, 101);
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 14;
	pZoneInfo->Name				= "에슬라니안 SW";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Eslania_SW.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Eslania_SW.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 140 ; // 89;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(203, 51, 303, 101);
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 21;
	pZoneInfo->Name				= "림보성 NE";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Limbo_Lair_NE.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Limbo_Lair_NE.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HIDE_AWAY;
// 	pZoneInfo->MusicIDVampire	= MUSIC_HIDE_AWAY;
	pZoneInfo->MusicID			= MUSIC_SCHWARZWALD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_CROW );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_WOLF_CRY );
	pZoneInfo->MinimapSpriteID	= 4;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(101, 0, 202, 50);
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 22;
	pZoneInfo->Name				= "림보성 NW";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Limbo_Lair_NW.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Limbo_Lair_NW.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HIDE_AWAY;
// 	pZoneInfo->MusicIDVampire	= MUSIC_HIDE_AWAY;
	pZoneInfo->MusicID			= MUSIC_SCHWARZWALD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_CROW );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_WOLF_CRY );
	pZoneInfo->MinimapSpriteID	= 5;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(0, 0, 101, 50);
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 23;
	pZoneInfo->Name				= "림보성 SE";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Limbo_Lair_SE.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Limbo_Lair_SE.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HIDE_AWAY;
// 	pZoneInfo->MusicIDVampire	= MUSIC_HIDE_AWAY;
	pZoneInfo->MusicID			= MUSIC_SCHWARZWALD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_CROW );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_WOLF_CRY );
	pZoneInfo->MinimapSpriteID	= 6;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(101, 51, 202, 101);
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 24;
	pZoneInfo->Name				= "림보성 SW";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Limbo_Lair_SW.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Limbo_Lair_SW.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HIDE_AWAY;
// 	pZoneInfo->MusicIDVampire	= MUSIC_HIDE_AWAY;
	pZoneInfo->MusicID			= MUSIC_SCHWARZWALD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_CROW );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_WOLF_CRY );
	pZoneInfo->MinimapSpriteID	= 7;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(0, 51, 101, 101);
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 31;
	pZoneInfo->Name				= "드로베타 NE";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Drobeta_NE.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Drobeta_NE.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HIDE_AWAY;
// 	pZoneInfo->MusicIDVampire	= MUSIC_HIDE_AWAY;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_CROW );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_WOLF_CRY );
	pZoneInfo->MinimapSpriteID	= 8;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(304, 102, 404, 151);
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 32;
	pZoneInfo->Name				= "드로베타 NW";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Drobeta_NW.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Drobeta_NW.mip";
	pZoneInfo->TeenFilename		= "" ; // "Data\\Map\\Drobeta_NW_Teen.map";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HIDE_AWAY;
// 	pZoneInfo->MusicIDVampire	= MUSIC_HIDE_AWAY;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_CROW );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_WOLF_CRY );
	pZoneInfo->MinimapSpriteID	= 9;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(203, 102, 303, 151);
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 33;
	pZoneInfo->Name				= "드로베타 SE";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Drobeta_SE.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Drobeta_SE.mip";
	pZoneInfo->TeenFilename		= "Data\\Map\\Drobeta_SE_Teen.map";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HIDE_AWAY;
// 	pZoneInfo->MusicIDVampire	= MUSIC_HIDE_AWAY;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_CROW );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_WOLF_CRY );
	pZoneInfo->MinimapSpriteID	= 10;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(304, 152, 404, 201);
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 34;
	pZoneInfo->Name				= "드로베타 SW";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Drobeta_SW.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Drobeta_SW.mip";
	pZoneInfo->TeenFilename		= "Data\\Map\\Drobeta_SW_Teen.map";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HIDE_AWAY;
// 	pZoneInfo->MusicIDVampire	= MUSIC_HIDE_AWAY;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_CROW );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_WOLF_CRY );
	pZoneInfo->MinimapSpriteID	= 11;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(203, 152, 303, 201);
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 41;
	pZoneInfo->Name				= "로딘산 NE";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Rodin_NE.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Rodin_NE.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 12;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(506, 0, 606, 50);
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 42;
	pZoneInfo->Name				= "로딘산 NW";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Rodin_NW.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Rodin_NW.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 13;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(405, 0, 505, 50);
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 43;
	pZoneInfo->Name				= "로딘산 SE";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Rodin_SE.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Rodin_SE.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 14;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(506, 51, 606, 101);
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 44;
	pZoneInfo->Name				= "로딘산 SW";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Rodin_SW.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Rodin_SW.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 15;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(405, 51, 505, 101);
	g_pZoneTable->Add( pZoneInfo );

	//------------------------------------------------
	// 2002.3.23일 추가
	//------------------------------------------------
	const WORD COLOR_TIMORE_CREATURE_WHITE = 379;	// 375는 흰색 colorSet이다.

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 51;
	pZoneInfo->Name				= "티모르 호수 NE";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Timore_NE.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Timore_NE.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->CreatureColorSet = COLOR_TIMORE_CREATURE_WHITE;	// 375는 완전 흰색이다.
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 16;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(304, 302, 404, 352);
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 52;
	pZoneInfo->Name				= "티모르 호수 NW";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Timore_NW.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Timore_NW.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->CreatureColorSet = COLOR_TIMORE_CREATURE_WHITE;	// 375는 완전 흰색이다.
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 17;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(203, 302, 303, 352);
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 53;
	pZoneInfo->Name				= "티모르 호수 SE";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Timore_SE.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Timore_SE.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->CreatureColorSet = COLOR_TIMORE_CREATURE_WHITE;	// 375는 완전 흰색이다.
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 18;			// 18은 아담의성지 연결 안된것.
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(304, 353, 404, 403);
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 54;
	pZoneInfo->Name				= "티모르 호수 SW";
	pZoneInfo->Property			= 0;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Timore_SW.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Timore_SW.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->CreatureColorSet = COLOR_TIMORE_CREATURE_WHITE;	// 375는 완전 흰색이다.
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 19;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(203, 353, 303, 403);
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 61;
	pZoneInfo->Name				= "페로나 NE";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\perona_NE.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\perona_NE.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 20;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(253, 202, 303, 251);
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 62;
	pZoneInfo->Name				= "페로나 NW";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\perona_NW.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\perona_NW.mip";
	pZoneInfo->TeenFilename		= "Data\\Map\\perona_NW_teen.map";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_ADVANCE;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 141; //21;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(203, 202, 252, 251);
	g_pZoneTable->Add( pZoneInfo );
	
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 63;
	pZoneInfo->Name				= "페로나 SE";
	pZoneInfo->Property			= 0;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\perona_SE.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\perona_SE.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 22;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(253, 252, 303, 301);
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 64;
	pZoneInfo->Name				= "페로나 SW";
	pZoneInfo->Property			= 0;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\perona_SW.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\perona_SW.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_GEHENNA;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 23;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(203, 252, 252, 301);
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 71;
	pZoneInfo->Name				= "아담의 성지 E";
	pZoneInfo->Property			= 0;
	pZoneInfo->HolyLand			= true;
	pZoneInfo->Safety			= false;
	pZoneInfo->CannotAttackInSafe = true;
	pZoneInfo->Filename			= "Data\\Map\\adam_new_e.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\adam_new_e.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_HOLYLAND;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 103;
	pZoneInfo->PKType			= PK_TYPE_USER_PK;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 72;
	pZoneInfo->Name				= "아담의 성지 C";
	pZoneInfo->Property			= 0;
	pZoneInfo->HolyLand			= true;
	pZoneInfo->Safety			= false;
	pZoneInfo->CannotAttackInSafe = true;\
	pZoneInfo->Filename			= "Data\\Map\\adam_new_c.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\adam_new_c.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_HOLYLAND;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 102;
	pZoneInfo->PKType			= PK_TYPE_USER_PK;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 73;
	pZoneInfo->Name				= "아담의 성지 W";
	pZoneInfo->Property			= 0;
	pZoneInfo->HolyLand			= true;
	pZoneInfo->Safety			= false;
	pZoneInfo->CannotAttackInSafe = true;
	pZoneInfo->Filename			= "Data\\Map\\adam_new_w.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\adam_new_w.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_HOLYLAND;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 101;
	pZoneInfo->PKType			= PK_TYPE_USER_PK;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	g_pZoneTable->Add( pZoneInfo );	
	
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 74;
	pZoneInfo->Name				= "아담의 성지 N";
	pZoneInfo->Property			= 0;
	pZoneInfo->HolyLand			= true;
	pZoneInfo->Safety			= false;
	pZoneInfo->CannotAttackInSafe = true;
	pZoneInfo->Filename			= "Data\\Map\\adam_new_c_n.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\adam_new_c_n.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_HOLYLAND;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 117;
	pZoneInfo->PKType			= PK_TYPE_USER_PK;
	g_pZoneTable->Add( pZoneInfo );	

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 75;
	pZoneInfo->Name				= "아담의 성지 S";
	pZoneInfo->Property			= 0;
	pZoneInfo->HolyLand			= true;
	pZoneInfo->Safety			= false;
	pZoneInfo->CannotAttackInSafe = true;
	pZoneInfo->Filename			= "Data\\Map\\adam_new_c_s.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\adam_new_c_s.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_HOLYLAND;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 118;
	pZoneInfo->PKType			= PK_TYPE_USER_PK;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	g_pZoneTable->Add( pZoneInfo );	


	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 81;
	pZoneInfo->Name				= "카스탈로 NE";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\castalo_ne.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\castalo_ne.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_ADVANCE;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 93;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(120, 102, 202, 151);
	g_pZoneTable->Add( pZoneInfo );	

	// 2004, 12, 24, sobeit add start - 신규맵 브랑코
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 91;
	pZoneInfo->Name				= "브랑코 NE";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Vranco_NE.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Vranco_NE.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 127;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(506, 102, 606, 151);
	g_pZoneTable->Add( pZoneInfo );	
	
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 92;
	pZoneInfo->Name				= "브랑코 NW";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Vranco_NW.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Vranco_NW.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 128;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(405, 102, 505, 151);
	g_pZoneTable->Add( pZoneInfo );	

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 93;
	pZoneInfo->Name				= "브랑코 SE";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Vranco_SE.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Vranco_SE.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 129;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(506, 152, 606, 201);
	g_pZoneTable->Add( pZoneInfo );	

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 94;
	pZoneInfo->Name				= "브랑코 SW";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Vranco_SW.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Vranco_SW.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 130;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	pZoneInfo->WorldMapInfo.WorldMapPosition	= CRect(405, 152, 505, 201);
	g_pZoneTable->Add( pZoneInfo );	

	// 2004, 12, 24, sobeit add end - 신규맵 브랑코
	

	// 던전 맵
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1001;
	pZoneInfo->Name				= "지하 수로";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Slayers_Training.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Slayers_Training.mip";
	pZoneInfo->TeenFilename		= "Data\\Map\\Slayers_Training_Teen.map";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HIDE_AWAY;
// 	pZoneInfo->MusicIDVampire	= MUSIC_HIDE_AWAY;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_WATER_DROP );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_IRON );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_SEWER );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 24;
	pZoneInfo->CannotAttackInSafe = true;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1002;
	pZoneInfo->Name				= "에슬라니안 던전";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Eslania_Dungeon.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Eslania_Dungeon.mip";
	pZoneInfo->TeenFilename		= "";	// bg00x
// 	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
// 	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_WATER_DROP );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_SEWER );
	pZoneInfo->MinimapSpriteID	= 25;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1003;
	pZoneInfo->Name				= "림보성 내부";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= true;
	pZoneInfo->Filename			= "Data\\Map\\Vampire_Village.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Vampire_Village.mip";
	pZoneInfo->TeenFilename		= "Data\\Map\\Vampire_Village_Teen.map";
// 	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
// 	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->MusicID			= MUSIC_OVERTURE;
	pZoneInfo->MinimapSpriteID	= 26;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1004;
	pZoneInfo->Name				= "림보성 던전";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Limbo_Dungeon.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Limbo_Dungeon.mip";
	pZoneInfo->TeenFilename		= "Data\\Map\\Limbo_Dungeon_Teen.map";	// bg00x
// 	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
// 	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_WATER_DROP );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_SEWER );
	pZoneInfo->MinimapSpriteID	= 27;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1005;
	pZoneInfo->Name				= "이벤트 OX";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= true;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Drobeta_OX.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Drobeta_OX.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
// 	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->MinimapSpriteID	= 28;
	pZoneInfo->CompetenceZone	= true;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->ID				= 1006;
	pZoneInfo->Name				= "이벤트 경기장";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Drobeta_Stadium.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Drobeta_Stadium.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
// 	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->MinimapSpriteID	= 29;
	pZoneInfo->CompetenceZone	= true;
	pZoneInfo->ChatMaskByRace	= false;
	pZoneInfo->PKType			= PK_TYPE_GUILD;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1007;
	pZoneInfo->Name				= "라센성 내부";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= true;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Rasen_yard.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Rasen_yard.mip";
	pZoneInfo->TeenFilename		= "Data\\Map\\Rasen_yard_Teen.map";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_OVERTURE;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->MinimapSpriteID	= 30;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1008;
	pZoneInfo->Name				= "칼리 석굴";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Kali_cave.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Kali_cave.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 31;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1009;
	pZoneInfo->Name				= "라센 에이나몬";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\rasen_training.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\rasen_training.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 32;
	g_pZoneTable->Add( pZoneInfo );


	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1010;
	pZoneInfo->Name				= "페이악 터널";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\tunnel_peiac.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\tunnel_peiac.mip";
	pZoneInfo->TeenFilename		= "Data\\Map\\tunnel_peiac_Teen.map";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 33;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1011;
	pZoneInfo->Name				= "로스트 타이얀 B1";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\losttaiyan_b1f.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\losttaiyan_b1f.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 67;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1012;
	pZoneInfo->Name				= "로스트 타이얀 B2";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\losttaiyan_b2f.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\losttaiyan_b2f.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 68;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1013;
	pZoneInfo->Name				= "아실리온 던전";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\asylion_dungeon.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\asylion_dungeon.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 69;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->ID				= 1020;
	pZoneInfo->Name				= "이벤트 경기장2";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Drobeta_Stadium.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Drobeta_Stadium.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
// 	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->MinimapSpriteID	= 29;
	pZoneInfo->CompetenceZone	= true;
	pZoneInfo->ChatMaskByRace	= false;
	pZoneInfo->PKType			= PK_TYPE_ALL;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1100;
	pZoneInfo->Name				= "바토리 던전 B1";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\bathory_dungeon_B1F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\bathory_dungeon_B1F.mip";
	pZoneInfo->TeenFilename		= "Data\\Map\\bathory_dungeon_B1F_Teen.map";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HIDE_AWAY;
// 	pZoneInfo->MusicIDVampire	= MUSIC_HIDE_AWAY;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_SEWER );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 34;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1101;
	pZoneInfo->Name				= "바토리 던전 B2";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\bathory_dungeon_B2F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\bathory_dungeon_B2F.mip";
	pZoneInfo->TeenFilename		= "Data\\Map\\bathory_dungeon_B2F_Teen.map";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HIDE_AWAY;
// 	pZoneInfo->MusicIDVampire	= MUSIC_HIDE_AWAY;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_SEWER );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 35;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1102;
	pZoneInfo->Name				= "바토리 던전 B3";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\bathory_dungeon_B3F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\bathory_dungeon_B3F.mip";
	pZoneInfo->TeenFilename		= "Data\\Map\\bathory_dungeon_B3F_Teen.map";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HIDE_AWAY;
// 	pZoneInfo->MusicIDVampire	= MUSIC_HIDE_AWAY;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_SEWER );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 36;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1103;
	pZoneInfo->Name				= "바토리 던전 B4";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\bathory_dungeon_B4F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\bathory_dungeon_B4F.mip";
	pZoneInfo->TeenFilename		= "Data\\Map\\bathory_dungeon_B4F_Teen.map";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HIDE_AWAY;
// 	pZoneInfo->MusicIDVampire	= MUSIC_HIDE_AWAY;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_SEWER );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 37;
	pZoneInfo->PKType			= PK_TYPE_USER_PK;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1104;
	pZoneInfo->Name				= "바토리 레어";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\bathory_lair.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\bathory_lair.mip";
	pZoneInfo->TeenFilename		= "Data\\Map\\bathory_lair_Teen.map";	
// 	pZoneInfo->MusicIDSlayer	= MUSIC_ADVANCE;
// 	pZoneInfo->MusicIDVampire	= MUSIC_ADVANCE;
	pZoneInfo->MusicID			= MUSIC_ADVANCE;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 70;
	g_pZoneTable->Add( pZoneInfo );


	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1105;
	pZoneInfo->Name				= "고르고바 터널";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Tunnel_Ghorgova.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Tunnel_Ghorgova.mip";
	pZoneInfo->TeenFilename		= "Data\\Map\\Tunnel_Ghorgova_Teen.map";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->HolyLand			= false;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 39;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1106;
	pZoneInfo->Name				= "클론 바토리 레어";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\bathory_lair_clon.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\bathory_lair_clon.mip";
	pZoneInfo->TeenFilename		= "Data\\Map\\bathory_lair_clon_Teen.map";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_ADVANCE;
// 	pZoneInfo->MusicIDVampire	= MUSIC_ADVANCE;
	pZoneInfo->MusicID			= MUSIC_ADVANCE;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 70;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1111;
	pZoneInfo->Name				= "라센 외성 1F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Castle_rasen_1_1.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Castle_rasen_1_1.mip";
	pZoneInfo->TeenFilename		= "Data\\Map\\Castle_rasen_1_1_Teen.map";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 40;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1112;
	pZoneInfo->Name				= "라센 내성 1F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Castle_rasen_1_2.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Castle_rasen_1_2.mip";
	pZoneInfo->TeenFilename		= "Data\\Map\\Castle_rasen_1_2_Teen.map";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 41;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1113;
	pZoneInfo->Name				= "라센 내성 2F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Castle_rasen_2_2.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Castle_rasen_2_2.mip";
	pZoneInfo->TeenFilename		= "Data\\Map\\Castle_rasen_2_2_Teen.map";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 42;
	pZoneInfo->PKType			= PK_TYPE_USER_PK;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1114;
	pZoneInfo->Name				= "테페즈 레어";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Tepes_lair.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Tepes_lair.mip";
	pZoneInfo->TeenFilename		= "Data\\Map\\Tepes_lair_Teen.map";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_ADVANCE;
// 	pZoneInfo->MusicIDVampire	= MUSIC_ADVANCE;
	pZoneInfo->MusicID			= MUSIC_ADVANCE;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 43;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1115;
	pZoneInfo->Name				= "클론 테페즈 레어";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Tepes_lair_clon.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Tepes_lair_clon.mip";
	pZoneInfo->TeenFilename		= "Data\\Map\\Tepes_lair_clon_Teen.map";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_ADVANCE;
// 	pZoneInfo->MusicIDVampire	= MUSIC_ADVANCE;
	pZoneInfo->MusicID			= MUSIC_ADVANCE;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 43;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1121;
	pZoneInfo->Name				= "라옴 던전 B2F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\slayer_battlezone1.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\slayer_battlezone1.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 148;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1122;
	pZoneInfo->Name				= "테메리에 성지";
	pZoneInfo->Property			= 0;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\slayer_battlezone2.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\slayer_battlezone2.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 100;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1123;
	pZoneInfo->Name				= "힐라놈 성지";
	pZoneInfo->Property			= 0;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\bathory_battlezone.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\bathory_battlezone.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 46;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1124;
	pZoneInfo->Name				= "아이센 던전 B2F";
	pZoneInfo->Property			= 0;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\rasen_battlezone.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\rasen_battlezone.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 147;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1125;
	pZoneInfo->Name				= "라옴 던전 B1F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\drobeta_dungeon_s1f.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\drobeta_dungeon_s1f.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 143;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1126;
	pZoneInfo->Name				= "아이센 던전 B1F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;	
	pZoneInfo->Filename			= "Data\\Map\\drobeta_dungeon_v1f.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\drobeta_dungeon_v1f.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 144;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	g_pZoneTable->Add( pZoneInfo );
	
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1127;
	pZoneInfo->Name				= "아이센 던전 B3F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;	
	pZoneInfo->Filename			= "Data\\Map\\icen_Dungeon3F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\icen_dungeon3f.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 111;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1622;
	pZoneInfo->Name				= "아이센 던전 B4F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;	
	pZoneInfo->Filename			= "Data\\Map\\icen_Dungeon4F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\icen_dungeon4f.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 145;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1128;
	pZoneInfo->Name				= "라옴 던전 B3F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;	
	pZoneInfo->Filename			= "Data\\Map\\laom_Dungeon3F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\laom_dungeon3f.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 151;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1129;
	pZoneInfo->Name				= "라옴 던전 B4F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;	
	pZoneInfo->Filename			= "Data\\Map\\laom_Dungeon4F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\laom_dungeon4f.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 146;
	g_pZoneTable->Add( pZoneInfo );


	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1130;
	pZoneInfo->Name				= "라옴 던전 B5F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;	
	pZoneInfo->Filename			= "Data\\Map\\laom_Dungeon5F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\laom_dungeon5f.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 150;
	//pZoneInfo->PKType = PK_TYPE_DISABLE ;
	g_pZoneTable->Add( pZoneInfo );
	
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1131;
	pZoneInfo->Name				= "칼리고 던전 1레벨";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Caligo_Dungeon.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Caligo_Dungeon.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID = 104;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1132;
	pZoneInfo->Name				= "칼리고 던전 2레벨";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Caligo_Dungeon.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Caligo_Dungeon.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID = 104;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1133;
	pZoneInfo->Name				= "칼리고 던전 3레벨";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Caligo_Dungeon.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Caligo_Dungeon.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	pZoneInfo->MinimapSpriteID = 104;

	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1134;
	pZoneInfo->Name				= "칼리고 던전 4레벨";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->Filename			= "Data\\Map\\Caligo_Dungeon.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Caligo_Dungeon.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID = 104;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1201;
	pZoneInfo->Name				= "옥타부스 성";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= true;
	pZoneInfo->HolyLand			= true;
	pZoneInfo->CannotAttackInSafe = true;	
	pZoneInfo->Filename			= "Data\\Map\\castle_octavus.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\castle_octavus.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_OCTAVUS;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 76;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1202;
	pZoneInfo->Name				= "테르티우스 성";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= true;
	pZoneInfo->HolyLand			= true;
	pZoneInfo->CannotAttackInSafe = true;
	pZoneInfo->Filename			= "Data\\Map\\castle_tertius.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\castle_tertius.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_TERTIUS;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 77;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1203;
	pZoneInfo->Name				= "셉티무스";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= true;
	pZoneInfo->HolyLand			= true;
	pZoneInfo->CannotAttackInSafe = true;
	pZoneInfo->Filename			= "Data\\Map\\castle_septimus.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\castle_septimus.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_SEPTIMUS;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 78;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1204;
	pZoneInfo->Name				= "쿠아르투스 성";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= true;
	pZoneInfo->HolyLand			= true;
	pZoneInfo->CannotAttackInSafe = true;	
	pZoneInfo->Filename			= "Data\\Map\\castle_quartus.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\castle_quartus.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_QUARTUS;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 79;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1205;
	pZoneInfo->Name				= "펜타누스 성";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= true;
	pZoneInfo->HolyLand			= true;
	pZoneInfo->CannotAttackInSafe = true;	
	pZoneInfo->Filename			= "Data\\Map\\castle_pentanus.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\castle_pentanus.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_OCTAVUS;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 79;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1206;
	pZoneInfo->Name				= "헥시리우스 성";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= true;
	pZoneInfo->HolyLand			= true;
	pZoneInfo->CannotAttackInSafe = true;	
	pZoneInfo->Filename			= "Data\\Map\\castle_hexserius.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\castle_hexserius.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_TERTIUS;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 77;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1211;
	pZoneInfo->Name				= "옥타부스 던전 B1F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= true;
	pZoneInfo->CannotAttackInSafe = true;	
	pZoneInfo->Filename			= "Data\\Map\\octavus_dungeon1f.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\octavus_dungeon1f.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_OCTAVUS;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 149;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1212;
	pZoneInfo->Name				= "옥타부스 던전 B2F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= true;
	pZoneInfo->CannotAttackInSafe = true;	
	pZoneInfo->Filename			= "Data\\Map\\octavus_dungeon2f.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\octavus_dungeon2f.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_OCTAVUS;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 91;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1221;
	pZoneInfo->Name				= "테르티우스 던전 B1F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= true;
	pZoneInfo->CannotAttackInSafe = true;	
	pZoneInfo->Filename			= "Data\\Map\\tertius_dungeon1f.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\tertius_dungeon1f.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_TERTIUS;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 149;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1222;
	pZoneInfo->Name				= "테르티우스 던전 B2F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= true;
	pZoneInfo->CannotAttackInSafe = true;	
	pZoneInfo->Filename			= "Data\\Map\\tertius_dungeon2f.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\tertius_dungeon2f.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_TERTIUS;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 91;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1231;
	pZoneInfo->Name				= "셉티무스 던전 B1F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= true;
	pZoneInfo->CannotAttackInSafe = true;
	pZoneInfo->Filename			= "Data\\Map\\septimus_dungeon1f.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\septimus_dungeon1f.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_SEPTIMUS;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 149;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1232;
	pZoneInfo->Name				= "셉티무스 던전 B2F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= true;
	pZoneInfo->CannotAttackInSafe = true;	
	pZoneInfo->Filename			= "Data\\Map\\septimus_dungeon2f.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\septimus_dungeon2f.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_SEPTIMUS;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 91;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1241;
	pZoneInfo->Name				= "쿠아르투스 던전 B1F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= true;
	pZoneInfo->CannotAttackInSafe = true;
	pZoneInfo->Filename			= "Data\\Map\\quartus_dungeon1f.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\quartus_dungeon1f.mip";
	pZoneInfo->TeenFilename		= "";
// 	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
// 	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_QUARTUS;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 149;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1242;
	pZoneInfo->Name				= "쿠아르투스 던전 B2F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= true;
	pZoneInfo->CannotAttackInSafe = true;
	pZoneInfo->Filename			= "Data\\Map\\quartus_dungeon2f.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\quartus_dungeon2f.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_QUARTUS;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 91;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1251;
	pZoneInfo->Name				= "펜타누스 던전 B1F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= true;
	pZoneInfo->CannotAttackInSafe = true;
	pZoneInfo->Filename			= "Data\\Map\\pentanus_dungeon1f.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\pentanus_dungeon1f.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_OCTAVUS;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 149;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1252;
	pZoneInfo->Name				= "펜타누스 던전 B2F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= true;
	pZoneInfo->CannotAttackInSafe = true;
	pZoneInfo->Filename			= "Data\\Map\\pentanus_dungeon2f.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\pentanus_dungeon2f.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_OCTAVUS;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 91;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1261;
	pZoneInfo->Name				= "헥시리우스 던전 B1F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= true;
	pZoneInfo->CannotAttackInSafe = true;
	pZoneInfo->Filename			= "Data\\Map\\hexserius_dungeon1f.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hexserius_dungeon1f.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_TERTIUS;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 149;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1262;
	pZoneInfo->Name				= "헥시리우스 던전 B2F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= true;
	pZoneInfo->CannotAttackInSafe = true;
	pZoneInfo->Filename			= "Data\\Map\\hexserius_dungeon2f.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hexserius_dungeon2f.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_TERTIUS;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 91;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1301;
	pZoneInfo->Name				= "올트";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = true;
	pZoneInfo->ChatMaskByRace	= false;
	pZoneInfo->Filename			= "Data\\Map\\SlayerPK.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\SlayerPK.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 82;
	pZoneInfo->CannotUseSpecialItem = true;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1302;
	pZoneInfo->Name				= "올테니아";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->ChatMaskByRace	= false;
	pZoneInfo->Filename			= "Data\\Map\\VampirePK.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\VampirePK.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 82;
	pZoneInfo->CannotUseSpecialItem = true;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1303;
	pZoneInfo->Name				= "바나툴";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->ChatMaskByRace	= false;
	pZoneInfo->Filename			= "Data\\Map\\FreePK.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Freepk.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 83;
	pZoneInfo->CannotUseSpecialItem = true;
	pZoneInfo->PKType			= PK_TYPE_ALL;
	g_pZoneTable->Add( pZoneInfo );
	
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1311;
	pZoneInfo->Name				= "아우스터즈 마을";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= true;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->Filename			= "Data\\Map\\ousters_village.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\ousters_village.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_CONCORDIA;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 142 ; //90;
	pZoneInfo->CannotUseSpecialItem = true;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	g_pZoneTable->Add( pZoneInfo );


	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1321;
	pZoneInfo->Name				= "하니알 던전 B1";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->Filename			= "Data\\Map\\ousters_dungeon01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\ousters_dungeon01.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 92;
	pZoneInfo->CannotUseSpecialItem = false;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1322;
	pZoneInfo->Name				= "하니알 던전 B2";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->Filename			= "Data\\Map\\ousters_dungeon02.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\ousters_dungeon02.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 91;
	pZoneInfo->CannotUseSpecialItem = false;
	g_pZoneTable->Add( pZoneInfo );
	
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1323;
	pZoneInfo->Name				= "하니알 던전 B3";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->Filename			= "Data\\Map\\ousters_dungeon03.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\ousters_dungeon03.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 97;
	pZoneInfo->CannotUseSpecialItem = false;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1324;
	pZoneInfo->Name				= "하니알 던전 B4";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->Filename			= "Data\\Map\\ousters_dungeon04.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\ousters_dungeon04.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 98;
	pZoneInfo->CannotUseSpecialItem = false;
	g_pZoneTable->Add( pZoneInfo );

	// 로스트 타워
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1401;
	pZoneInfo->Name				= "러스트 타워 1F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->Filename			= "Data\\Map\\LustTower_1F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\LustTower_1F.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 105;
	pZoneInfo->CannotUseSpecialItem = false;
	pZoneInfo->PKType			= PK_TYPE_USER_PK;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	g_pZoneTable->Add( pZoneInfo );

	// 로스트 타워
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1402;
	pZoneInfo->Name				= "러스트 타워 2F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->Filename			= "Data\\Map\\LustTower_2F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\LustTower_2F.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 106;
	pZoneInfo->CannotUseSpecialItem = false;
	pZoneInfo->PKType			= PK_TYPE_USER_PK;
	g_pZoneTable->Add( pZoneInfo );

	// 질드레 레어
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1410;
	pZoneInfo->Name				= "일루젼스 웨이1";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->Filename			= "Data\\Map\\Gdr_illusion_01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Gdr_illusion_01.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_ADVANCE;
//	pZoneInfo->MusicIDVampire	= MUSIC_ADVANCE;
	pZoneInfo->MusicID			= MUSIC_ADVANCE;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_WIND );
	pZoneInfo->MinimapSpriteID	= 107;
	pZoneInfo->CannotUseSpecialItem = false;
	pZoneInfo->ChatMaskByRace	= false;
	pZoneInfo->PKType			= PK_TYPE_DISABLE;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1411;
	pZoneInfo->Name				= "일루젼스 웨이2";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->Filename			= "Data\\Map\\Gdr_illusion_02.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Gdr_illusion_02.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_ADVANCE;
//	pZoneInfo->MusicIDVampire	= MUSIC_ADVANCE;
	pZoneInfo->MusicID			= MUSIC_ADVANCE;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_WIND );
	pZoneInfo->MinimapSpriteID	= 108;
	pZoneInfo->CannotUseSpecialItem = false;
	pZoneInfo->ChatMaskByRace	= false;
	pZoneInfo->PKType			= PK_TYPE_DISABLE;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1412;
	pZoneInfo->Name				= "질드레 레어";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->Filename			= "Data\\Map\\Gdr_lair_01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Gdr_lair_01.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_ADVANCE;
//	pZoneInfo->MusicIDVampire	= MUSIC_ADVANCE;
	pZoneInfo->MusicID			= MUSIC_ADVANCE;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_WIND );
	pZoneInfo->MinimapSpriteID	= 109;
	pZoneInfo->CannotUseSpecialItem = false;
	pZoneInfo->ChatMaskByRace	= false;
	pZoneInfo->PKType			= PK_TYPE_DISABLE;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1413;
	pZoneInfo->Name				= "질드레 레어 코어";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->Filename			= "Data\\Map\\Gdr_lair_hard.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Gdr_lair_hard.mip";
	pZoneInfo->TeenFilename		= "Data\\Map\\Gdr_lair_hard_teen.map";
//	pZoneInfo->MusicIDSlayer	= MUSIC_ADVANCE;
//	pZoneInfo->MusicIDVampire	= MUSIC_ADVANCE;
	pZoneInfo->MusicID			= MUSIC_ADVANCE;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_WIND );
	pZoneInfo->MinimapSpriteID	= 110;
	pZoneInfo->CannotUseSpecialItem = false;
	pZoneInfo->ChatMaskByRace	= false;
	pZoneInfo->PKType			= PK_TYPE_DISABLE;
	g_pZoneTable->Add( pZoneInfo );


	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1500;
	pZoneInfo->Name				= "공성 지역";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->Filename			= "Data\\Map\\siege_warfare.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\siege_warfare.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 152;
	pZoneInfo->CannotUseSpecialItem = false;
	pZoneInfo->PKType			= PK_TYPE_SIEGE;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1501;
	pZoneInfo->Name				= "옥타부스 공성지역";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->Filename			= "Data\\Map\\siege_warfare.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\siege_warfare.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_GEHENNA;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 152;
	pZoneInfo->CannotUseSpecialItem = false;
	pZoneInfo->PKType			= PK_TYPE_SIEGE;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1502;
	pZoneInfo->Name				= "테르티우스 공성지역";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->Filename			= "Data\\Map\\siege_warfare.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\siege_warfare.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_SCHWARZWALD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 152;
	pZoneInfo->CannotUseSpecialItem = false;
	pZoneInfo->PKType			= PK_TYPE_SIEGE;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1503;
	pZoneInfo->Name				= "셉티무스 공성지역";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->Filename			= "Data\\Map\\siege_warfare.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\siege_warfare.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_GEHENNA;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 152;
	pZoneInfo->CannotUseSpecialItem = false;
	pZoneInfo->PKType			= PK_TYPE_SIEGE;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1504;
	pZoneInfo->Name				= "쿠아르투스 공성지역";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->Filename			= "Data\\Map\\siege_warfare.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\siege_warfare.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_SCHWARZWALD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 152;
	pZoneInfo->CannotUseSpecialItem = false;
	pZoneInfo->PKType			= PK_TYPE_SIEGE;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1505;
	pZoneInfo->Name				= "펜타누스 공성지역";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->Filename			= "Data\\Map\\siege_warfare.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\siege_warfare.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_ADVANCE;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 152;
	pZoneInfo->CannotUseSpecialItem = false;
	pZoneInfo->PKType			= PK_TYPE_SIEGE;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1506;
	pZoneInfo->Name				= "헥시리우스 공성지역";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->Filename			= "Data\\Map\\siege_warfare.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\siege_warfare.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->MusicID			= MUSIC_ADVANCE;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 152;
	pZoneInfo->CannotUseSpecialItem = false;
	pZoneInfo->PKType			= PK_TYPE_SIEGE;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1600;
	pZoneInfo->Name				= "패스 투 피어";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->Filename			= "Data\\Map\\Path_to_Fears.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Path_to_Fears.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 96; // 96:?표시
	pZoneInfo->CannotUseSpecialItem = false;
	g_pZoneTable->Add( pZoneInfo );


	// 2004, 12, 24, sobeit add start - 신규맵 브랑코 던전
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1601;
	pZoneInfo->Name				= "IK Office";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->Filename			= "Data\\Map\\IK_offic.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\IK_offic.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 123; // 96:?표시
	pZoneInfo->CannotUseSpecialItem = false;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1602;
	pZoneInfo->Name				= "IK Lab";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->Filename			= "Data\\Map\\IK_Lab.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\IK_Lab.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 124; // 96:?표시
	pZoneInfo->CannotUseSpecialItem = false;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1603;
	pZoneInfo->Name				= "IK Lab B1F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->Filename			= "Data\\Map\\IK_Lab_B1F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\IK_Lab_B1F.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 125; // 96:?표시
	pZoneInfo->CannotUseSpecialItem = false;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1604;
	pZoneInfo->Name				= "IK Lab B2F";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CannotAttackInSafe = false;
	pZoneInfo->Filename			= "Data\\Map\\IK_Lab_B2F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\IK_Lab_B2F.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 126; // 96:?표시
	pZoneInfo->CannotUseSpecialItem = false;
	g_pZoneTable->Add( pZoneInfo );
	// 2004, 12, 24, sobeit add end - 신규맵 브랑코

	// 2005, 1, 11, sobeit add start - 승직 던전
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1611;
	pZoneInfo->Name				= "준저터널1층";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Under_pass_1F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Under_pass_1F.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 131;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	g_pZoneTable->Add( pZoneInfo );	

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1612;
	pZoneInfo->Name				= "준저터널2층";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Under_pass_2F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Under_pass_2F.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_BIRD );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOG_BARK );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_DOOR_WOOD );
	pZoneInfo->MinimapSpriteID	= 132;
	g_pZoneTable->Add( pZoneInfo );	
	// 2005, 1, 11, sobeit add end
	
	
	// 2005, 4, 19, sjheon  add start 신규맵 게르블 던전 맵 
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1621;
	pZoneInfo->Name				= "게르블던전";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\castellum.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\castellum.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_HOLLOWEEN;
//	pZoneInfo->MusicIDVampire	= MUSIC_LIVE_OR_DEAD;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_RATS );
	pZoneInfo->MinimapSpriteID	= 137;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_PREMIUM;
	g_pZoneTable->Add( pZoneInfo );	
	// 2005, 4, 19, sjheon add start - 신규 던전 맵 

	
	// 건물
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 2000;
	pZoneInfo->Name				= "군인 길드 B1";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= true;
	pZoneInfo->Filename			= "Data\\Map\\Guild_army_B1.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Guild_army_B1.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_LUNATIC;
//	pZoneInfo->MusicIDVampire	= MUSIC_LUNATIC;
	pZoneInfo->MusicID			= MUSIC_ANONCIAD;
	pZoneInfo->MinimapSpriteID	= 48;
	pZoneInfo->HolyLand			= false;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 2001;
	pZoneInfo->Name				= "군인 길드 1F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= true;
	pZoneInfo->Filename			= "Data\\Map\\Guild_Army_1F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Guild_Army_1F.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_LUNATIC;
//	pZoneInfo->MusicIDVampire	= MUSIC_LUNATIC;
	pZoneInfo->MusicID			= MUSIC_ANONCIAD;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 49;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 2002;
	pZoneInfo->Name				= "군인 길드 2F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= true;
	pZoneInfo->Filename			= "Data\\Map\\Guild_Army_2F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Guild_Army_2F.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_LUNATIC;
//	pZoneInfo->MusicIDVampire	= MUSIC_LUNATIC;
	pZoneInfo->MusicID			= MUSIC_ANONCIAD;
	pZoneInfo->MinimapSpriteID	= 50;
	pZoneInfo->HolyLand			= false;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 2003;
	pZoneInfo->Name				= "군인 길드 3F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= true;
	pZoneInfo->Filename			= "Data\\Map\\Guild_Army_3F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Guild_Army_3F.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_LUNATIC;
//	pZoneInfo->MusicIDVampire	= MUSIC_LUNATIC;
	pZoneInfo->MusicID			= MUSIC_ANONCIAD;
	pZoneInfo->MinimapSpriteID	= 51;
	pZoneInfo->HolyLand			= false;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 2004;
	pZoneInfo->Name				= "군인 길드 옥상";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= true;
	pZoneInfo->Filename			= "Data\\Map\\Guild_army_4F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Guild_army_4F.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_PROPELLER );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_WIND );
//	pZoneInfo->MusicIDSlayer	= MUSIC_LUNATIC;
//	pZoneInfo->MusicIDVampire	= MUSIC_LUNATIC;
	pZoneInfo->MusicID			= MUSIC_ANONCIAD;
	pZoneInfo->MinimapSpriteID	= 52;
	pZoneInfo->HolyLand			= false;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 2010;
	pZoneInfo->Name				= "성직자 길드 B1";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= true;
	pZoneInfo->Filename			= "Data\\Map\\Guild_cleric_B1.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Guild_cleric_B1.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_LUNATIC;
//	pZoneInfo->MusicIDVampire	= MUSIC_LUNATIC;
	pZoneInfo->MusicID			= MUSIC_ANONCIAD;
	pZoneInfo->MinimapSpriteID	= 53;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->HolyLand			= false;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 2011;
	pZoneInfo->Name				= "성직자 길드 1F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= true;
	pZoneInfo->Filename			= "Data\\Map\\Guild_Cleric_1F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Guild_Cleric_1F.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_LUNATIC;
//	pZoneInfo->MusicIDVampire	= MUSIC_LUNATIC;
	pZoneInfo->MusicID			= MUSIC_ANONCIAD;
	pZoneInfo->MinimapSpriteID	= 54;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 2012;
	pZoneInfo->Name				= "성직자 길드 2F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= true;
	pZoneInfo->Filename			= "Data\\Map\\Guild_Cleric_2F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Guild_Cleric_2F.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_LUNATIC;
//	pZoneInfo->MusicIDVampire	= MUSIC_LUNATIC;
	pZoneInfo->MusicID			= MUSIC_ANONCIAD;
	pZoneInfo->MinimapSpriteID	= 55;
	pZoneInfo->HolyLand			= false;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 2013;
	pZoneInfo->Name				= "성직자 길드 3F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= true;
	pZoneInfo->Filename			= "Data\\Map\\Guild_Cleric_3F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Guild_Cleric_3F.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_LUNATIC;
//	pZoneInfo->MusicIDVampire	= MUSIC_LUNATIC;
	pZoneInfo->MusicID			= MUSIC_ANONCIAD;
	pZoneInfo->MinimapSpriteID	= 56;
	pZoneInfo->HolyLand			= false;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 2014;
	pZoneInfo->Name				= "성직자 길드 옥상";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= true;
	pZoneInfo->Filename			= "Data\\Map\\Guild_cleric_4F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Guild_cleric_4F.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_PROPELLER );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_WIND );
//	pZoneInfo->MusicIDSlayer	= MUSIC_LUNATIC;
//	pZoneInfo->MusicIDVampire	= MUSIC_LUNATIC;
	pZoneInfo->MusicID			= MUSIC_ANONCIAD;
	pZoneInfo->MinimapSpriteID	= 57;
	pZoneInfo->HolyLand			= false;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 2020;
	pZoneInfo->Name				= "무사 길드 B1";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= true;
	pZoneInfo->Filename			= "Data\\Map\\Guild_knight_B1.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Guild_knight_B1.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_LUNATIC;
//	pZoneInfo->MusicIDVampire	= MUSIC_LUNATIC;
	pZoneInfo->MusicID			= MUSIC_ANONCIAD;
	pZoneInfo->MinimapSpriteID	= 58;
	pZoneInfo->HolyLand			= false;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 2021;
	pZoneInfo->Name				= "무사 길드 1F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= true;
	pZoneInfo->Filename			= "Data\\Map\\Guild_Knight_1F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Guild_Knight_1F.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_LUNATIC;
//	pZoneInfo->MusicIDVampire	= MUSIC_LUNATIC;
	pZoneInfo->MusicID			= MUSIC_ANONCIAD;
	pZoneInfo->MinimapSpriteID	= 59;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 2022;
	pZoneInfo->Name				= "무사 길드 2F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= true;
	pZoneInfo->Filename			= "Data\\Map\\Guild_Knight_2F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Guild_Knight_2F.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_LUNATIC;
//	pZoneInfo->MusicIDVampire	= MUSIC_LUNATIC;
	pZoneInfo->MusicID			= MUSIC_ANONCIAD;
	pZoneInfo->MinimapSpriteID	= 60;
	pZoneInfo->HolyLand			= false;

	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 2023;
	pZoneInfo->Name				= "무사 길드 3F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= true;
	pZoneInfo->Filename			= "Data\\Map\\Guild_Knight_3F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Guild_Knight_3F.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSIC_LUNATIC;
//	pZoneInfo->MusicIDVampire	= MUSIC_LUNATIC;
	pZoneInfo->MusicID			= MUSIC_ANONCIAD;
	pZoneInfo->MinimapSpriteID	= 61;
	pZoneInfo->HolyLand			= false;

	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 2024;
	pZoneInfo->Name				= "무사 길드 옥상";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= true;
	pZoneInfo->Filename			= "Data\\Map\\Guild_Knight_4F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Guild_Knight_4F.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_PROPELLER );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_WIND );
//	pZoneInfo->MusicIDSlayer	= MUSIC_LUNATIC;
//	pZoneInfo->MusicIDVampire	= MUSIC_LUNATIC;
	pZoneInfo->MusicID			= MUSIC_ANONCIAD;
	pZoneInfo->MinimapSpriteID	= 62;
	pZoneInfo->HolyLand			= false;
	g_pZoneTable->Add( pZoneInfo );
	
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 3001;
	pZoneInfo->Name				= "리피니움 탄광";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\maze.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\maze.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->MinimapSpriteID	= 96;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 3002;
	pZoneInfo->Name				= "트랩 존";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\trapzone01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\trapzone01.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->MinimapSpriteID	= 96;
	pZoneInfo->HolyLand			= false;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 3003;
	pZoneInfo->Name				= "리피니움 저장실";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\trapzone02.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\trapzone02.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->MinimapSpriteID	= 96;
	pZoneInfo->HolyLand			= false;
	g_pZoneTable->Add( pZoneInfo );

	// 승직 퀘스트 맵
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 4001;
	pZoneInfo->Name				= "제단 입구";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Gate_of_alter.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Gate_of_alter.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->MinimapSpriteID	= 136;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->PKType			= PK_TYPE_ALL;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 4002;
	pZoneInfo->Name				= "피의 제단";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Alter_of_blood.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Alter_of_blood.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->MinimapSpriteID	= 134;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->PKType			= PK_TYPE_ALL;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 4003;
	pZoneInfo->Name				= "심연의 거울";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Gate_of_alter2.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Gate_of_alter2.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->MinimapSpriteID	= 135;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->PKType			= PK_TYPE_ALL;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 4004;
	pZoneInfo->Name				= "심연의 거울";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Gate_of_alter2.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Gate_of_alter2.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->MinimapSpriteID	= 135;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->PKType			= PK_TYPE_ALL;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 4005;
	pZoneInfo->Name				= "심연의 거울";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Gate_of_alter2.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Gate_of_alter2.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->MinimapSpriteID	= 135;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->PKType			= PK_TYPE_ALL;
	g_pZoneTable->Add( pZoneInfo );


	/*
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 2103;
	pZoneInfo->Name				= "튜토리얼-컴퓨터실";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Tutorial_Computer.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Tutorial_Computer.mip";
	pZoneInfo->TeenFilename	= "Data\\Image\\Minimap\\Vampire_Village.spr";
	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 2104;
	pZoneInfo->Name				= "튜토리얼-무기고";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Tutorial_GunShop.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Tutorial_GunShop.mip";
	pZoneInfo->TeenFilename	= "Data\\Image\\Minimap\\Vampire_Village.spr";
	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	g_pZoneTable->Add( pZoneInfo );
	
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 2105;
	pZoneInfo->Name				= "튜토리얼-도서관";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Tutorial_Library.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Tutorial_Library.mip";
	pZoneInfo->TeenFilename	= "Data\\Image\\Minimap\\Vampire_Village.spr";
	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 2106;
	pZoneInfo->Name				= "튜토리얼-헬기장";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Tutorial_Heliport.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Tutorial_Heliport.mip";
	pZoneInfo->TeenFilename	= "Data\\Image\\Minimap\\Tutorial_Heliport.spr";
	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_PROPELLER );
	pZoneInfo->SoundIDList.push_back( SOUND_WORLD_WIND );
	g_pZoneTable->Add( pZoneInfo );
	*/

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 2101;
	pZoneInfo->Name				= "가상훈련장 1";
	pZoneInfo->Property			= 0;//FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Tutorial_N.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Tutorial_N.mip";
	pZoneInfo->TeenFilename		= "";	// bg00x
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->MusicID			= MUSIC_GEHENNA;
	pZoneInfo->MinimapSpriteID	= 84;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 2102;
	pZoneInfo->Name				= "가상훈련장 2";
	pZoneInfo->Property			= 0;//FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Tutorial_S.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Tutorial_S.mip";
	pZoneInfo->TeenFilename		= "";	// bg00x
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->MusicID			= MUSIC_GEHENNA;
	pZoneInfo->MinimapSpriteID	= 85;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	g_pZoneTable->Add( pZoneInfo );
	
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 8000;
	pZoneInfo->Name				= "이벤트 경기장(大)";
	pZoneInfo->Property			= 0;//FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\DEVT.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\DEVT.mip";
	pZoneInfo->TeenFilename		= "";	// bg00x
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->MinimapSpriteID	= 99;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CompetenceZone	= true;
	g_pZoneTable->Add( pZoneInfo );

	
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 8001;
	pZoneInfo->Name				= "서바이벌 경기장";
	pZoneInfo->Property			= 0;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\survival.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\survival.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;
	pZoneInfo->MinimapSpriteID	= 99;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->CompetenceZone	= true;
	pZoneInfo->CannotUseSpecialItem = true;
	pZoneInfo->PKType			= PK_TYPE_SIEGE;
	g_pZoneTable->Add( pZoneInfo );

	// 길드 아지트
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 10001;
	pZoneInfo->Name				= "길드 아지트";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\team_hdqrs.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\team_hdqrs.mip";
	pZoneInfo->TeenFilename		= "";	// bg00x
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->MinimapSpriteID	= 65;
	pZoneInfo->HolyLand			= false;

	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 20001;
	pZoneInfo->Name				= "클랜 아지트";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\clan_hdqrs.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\clan_hdqrs.mip";
	pZoneInfo->TeenFilename		= "Data\\Map\\clan_hdqrs_teen.map";	// bg00x
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->MinimapSpriteID	= 66;
	pZoneInfo->HolyLand			= false;

	g_pZoneTable->Add( pZoneInfo );

	

	//------------------------------------------------
	// 가짜 존 ID
	//------------------------------------------------
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 60000;
	pZoneInfo->Name				= "헬기 탑승";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Tutorial_Bokdo.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Tutorial_Bokdo.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;

	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 60001;
	pZoneInfo->Name				= "엘리베이터";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Tutorial_Bokdo.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Tutorial_Bokdo.mip";
	pZoneInfo->HolyLand			= false;

	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 60002;
	pZoneInfo->Name				= "알 수 없음";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Tutorial_Bokdo.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Tutorial_Bokdo.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 60003;
	pZoneInfo->Name				= "출구";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Tutorial_Bokdo.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Tutorial_Bokdo.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 60004;
	pZoneInfo->Name				= "가상훈련장";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Tutorial_Bokdo.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Tutorial_Bokdo.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 60005;
	pZoneInfo->Name				= "칼리고 던전";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Tutorial_Bokdo.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Tutorial_Bokdo.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->WorldMapInfo.WorldMapType		= WORLDMAP_INFO::WORLDMAP_HELEA;
	pZoneInfo->WorldMapInfo.PaymentType			= WORLDMAP_INFO::PAYMENT_FREE;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 60006;
	pZoneInfo->Name				= "아담동 워프게이트";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Tutorial_Bokdo.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Tutorial_Bokdo.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 60007;
	pZoneInfo->Name				= "아담서 워프게이트";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Tutorial_Bokdo.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Tutorial_Bokdo.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	g_pZoneTable->Add( pZoneInfo );
	


	//////////////////////////////////////////////////////////////////////////
	// 헬가든 시작 - chyaya 2007.05.14

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5000;
	pZoneInfo->Name				= "헬가든 1층";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_1f.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_1f.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 153;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5010;
	pZoneInfo->Name				= "헬가든 2층";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_2f.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_2f.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 153;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5020;
	pZoneInfo->Name				= "헬가든 3층";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_3f.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_3f.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 153;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5030;
	pZoneInfo->Name				= "헬가든 4층";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_4f.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_4f.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 153;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5040;
	pZoneInfo->Name				= "헬가든 5층";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_5f.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_5f.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 153;
	g_pZoneTable->Add( pZoneInfo );


	//////////////////////////////////////////////////////////////////////////
	// Hell Garden Tower

	ZONETABLE_INFO::MAPSHAPE_VEC HellGardenTowerMapShapeList;
	HellGardenTowerMapShapeList.push_back("Data\\Map\\hell_garden_tower01.map");
	HellGardenTowerMapShapeList.push_back("Data\\Map\\hell_garden_tower02.map");
	HellGardenTowerMapShapeList.push_back("Data\\Map\\hell_garden_tower01.map");
	HellGardenTowerMapShapeList.push_back("Data\\Map\\hell_garden_tower02.map");
	HellGardenTowerMapShapeList.push_back("Data\\Map\\hell_garden_tower_b.map");


	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5001;
	pZoneInfo->Name				= "1층 루베도";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_tower01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_tower01.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 154;
	pZoneInfo->MapShapeList		= HellGardenTowerMapShapeList;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5002;
	pZoneInfo->Name				= "1층 니그레도";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_tower01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_tower01.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 154;
	pZoneInfo->MapShapeList		= HellGardenTowerMapShapeList;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5003;
	pZoneInfo->Name				= "1층 알베도";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_tower01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_tower01.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 154;
	pZoneInfo->MapShapeList		= HellGardenTowerMapShapeList;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5004;
	pZoneInfo->Name				= "1층 데스페라도";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_tower01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_tower01.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 154;
	pZoneInfo->MapShapeList		= HellGardenTowerMapShapeList;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5011;
	pZoneInfo->Name				= "2층 루베도";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_tower01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_tower01.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 154;
	pZoneInfo->MapShapeList		= HellGardenTowerMapShapeList;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5012;
	pZoneInfo->Name				= "2층 니그레도";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_tower01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_tower01.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 154;
	pZoneInfo->MapShapeList		= HellGardenTowerMapShapeList;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5013;
	pZoneInfo->Name				= "2층 알베도";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_tower01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_tower01.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 154;
	pZoneInfo->MapShapeList		= HellGardenTowerMapShapeList;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5014;
	pZoneInfo->Name				= "2층 데스페라도";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_tower01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_tower01.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 154;
	pZoneInfo->MapShapeList		= HellGardenTowerMapShapeList;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5021;
	pZoneInfo->Name				= "3층 루베도";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_tower01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_tower01.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 154;
	pZoneInfo->MapShapeList		= HellGardenTowerMapShapeList;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5022;
	pZoneInfo->Name				= "3층 니그레도";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_tower01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_tower01.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 154;
	pZoneInfo->MapShapeList		= HellGardenTowerMapShapeList;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5023;
	pZoneInfo->Name				= "3층 알베도";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_tower01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_tower01.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 154;
	pZoneInfo->MapShapeList		= HellGardenTowerMapShapeList;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5024;
	pZoneInfo->Name				= "3층 데스페라도";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_tower01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_tower01.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 154;
	pZoneInfo->MapShapeList		= HellGardenTowerMapShapeList;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5031;
	pZoneInfo->Name				= "4층 루베도";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_tower01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_tower01.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 154;
	pZoneInfo->MapShapeList		= HellGardenTowerMapShapeList;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5032;
	pZoneInfo->Name				= "4층 니그레도";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_tower01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_tower01.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 154;
	pZoneInfo->MapShapeList		= HellGardenTowerMapShapeList;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5033;
	pZoneInfo->Name				= "4층 알베도";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_tower01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_tower01.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 154;
	pZoneInfo->MapShapeList		= HellGardenTowerMapShapeList;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5034;
	pZoneInfo->Name				= "4층 데스페라도";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_tower01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_tower01.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 154;
	pZoneInfo->MapShapeList		= HellGardenTowerMapShapeList;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5041;
	pZoneInfo->Name				= "5층 루베도";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_tower01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_tower01.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 154;
	pZoneInfo->MapShapeList		= HellGardenTowerMapShapeList;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5042;
	pZoneInfo->Name				= "5층 니그레도";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_tower01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_tower01.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 154;
	pZoneInfo->MapShapeList		= HellGardenTowerMapShapeList;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5043;
	pZoneInfo->Name				= "5층 알베도";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_tower01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_tower01.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 154;
	pZoneInfo->MapShapeList		= HellGardenTowerMapShapeList;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 5044;
	pZoneInfo->Name				= "5층 데스페라도";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\hell_garden_tower01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\hell_garden_tower01.mip";
	pZoneInfo->TeenFilename		= "";
//	pZoneInfo->MusicIDSlayer	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
//	pZoneInfo->MusicIDVampire	= MUSICID_NULL;//MUSIC_HIDE_AWAY;
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 154;
	pZoneInfo->MapShapeList		= HellGardenTowerMapShapeList;
	g_pZoneTable->Add( pZoneInfo );

	// 헬가든 끝 - chyaya 2007.05.14
	//////////////////////////////////////////////////////////////////////////
#if __CONTENTS(__MENEGROTH)	
	//////////////////////////////////////////////////////////////////////////
	//메네그로스 20071214 start
	//////////////////////////////////////////////////////////////////////////
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1701;
	pZoneInfo->Name				= "메네그로스 B1F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Menegroth_1F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Menegroth_1F_Slayer.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 157;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1702;
	pZoneInfo->Name				= "메네그로스 B2F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Menegroth_2F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Menegroth_2F_Slayer.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 158;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1703;
	pZoneInfo->Name				= "메네그로스 B3F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Menegroth_3F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Menegroth_3F_Slayer.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 159;
	g_pZoneTable->Add( pZoneInfo );
	pZoneInfo = new ZONETABLE_INFO;

	pZoneInfo->ID				= 1704;
	pZoneInfo->Name				= "메네그로스 B4F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Menegroth_4F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Menegroth_4F_Slayer.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 160;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1705;
	pZoneInfo->Name				= "메네그로스 B5F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Menegroth_5F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Menegroth_5F_Slayer.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 161;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1706;
	pZoneInfo->Name				= "메네그로스 B6F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Menegroth_6F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Menegroth_6F_Slayer.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 162;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1707;
	pZoneInfo->Name				= "메네그로스 B1F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Menegroth_1F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Menegroth_1F_Vampire.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 157;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1708;
	pZoneInfo->Name				= "메네그로스 B2F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Menegroth_2F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Menegroth_2F_Vampire.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 158;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1709;
	pZoneInfo->Name				= "메네그로스 B3F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Menegroth_3F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Menegroth_3F_Vampire.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 159;
	g_pZoneTable->Add( pZoneInfo );
	pZoneInfo = new ZONETABLE_INFO;

	pZoneInfo->ID				= 1710;
	pZoneInfo->Name				= "메네그로스 B4F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Menegroth_4F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Menegroth_4F_Vampire.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 160;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1711;
	pZoneInfo->Name				= "메네그로스 B5F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Menegroth_5F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Menegroth_5F_Vampire.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 161;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1712;
	pZoneInfo->Name				= "메네그로스 B6F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Menegroth_6F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Menegroth_6F_Vampire.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 162;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1713;
	pZoneInfo->Name				= "메네그로스 B1F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Menegroth_1F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Menegroth_1F_Ousters.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 157;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1714;
	pZoneInfo->Name				= "메네그로스 B2F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Menegroth_2F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Menegroth_2F_Ousters.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 158;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1715;
	pZoneInfo->Name				= "메네그로스 B3F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Menegroth_3F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Menegroth_3F_Ousters.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 159;
	g_pZoneTable->Add( pZoneInfo );
	pZoneInfo = new ZONETABLE_INFO;

	pZoneInfo->ID				= 1716;
	pZoneInfo->Name				= "메네그로스 B4F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Menegroth_4F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Menegroth_4F_Ousters.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 160;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1717;
	pZoneInfo->Name				= "메네그로스 B5F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Menegroth_5F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Menegroth_5F_Ousters.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 161;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1718;
	pZoneInfo->Name				= "메네그로스 B6F";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Menegroth_6F.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Menegroth_6F_Ousters.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 162;
	g_pZoneTable->Add( pZoneInfo );

#endif //__MENEGROTH
#if __CONTENTS(__TIPOJYU_CASTLE)		//티포쥬 맵 추가
	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1801;
	pZoneInfo->Name				= "티포쥬 성1F (현세)";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Tiffauges_castle_1F_01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Tiffauges_castle_1F_01.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 163;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1802;
	pZoneInfo->Name				= "티포쥬 성1F (과거)";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Tiffauges_castle_1F_02.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Tiffauges_castle_1F_02.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 164;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1803;
	pZoneInfo->Name				= "티포쥬 성2F (현세)";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Tiffauges_castle_2F_01.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Tiffauges_castle_2F_01.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 165;
	g_pZoneTable->Add( pZoneInfo );

	pZoneInfo = new ZONETABLE_INFO;
	pZoneInfo->ID				= 1804;
	pZoneInfo->Name				= "티포쥬 성2F (과거)";
	pZoneInfo->Property			= FLAG_ZONESIZE_SMALL;
	pZoneInfo->Safety			= false;
	pZoneInfo->Filename			= "Data\\Map\\Tiffauges_castle_2F_02.map";
	pZoneInfo->InfoFilename		= "Data\\Map\\Tiffauges_castle_2F_02.mip";
	pZoneInfo->TeenFilename		= "";
	pZoneInfo->HolyLand			= false;
	pZoneInfo->MinimapSpriteID	= 166;
	g_pZoneTable->Add( pZoneInfo );
	
#endif	// __TIPOJYU_CASTLE
	//------------------------------------------------
	// Save
	//------------------------------------------------
	std::ofstream zoneTable(g_pFileDef->getProperty("FILE_INFO_ZONE").c_str(), std::ios::binary);
	g_pZoneTable->SaveToFile(zoneTable);
	zoneTable.close();
#endif
	//*/

	//------------------------------------------------
	// Load
	//------------------------------------------------
	ivfstream zoneTable2;//(FILE_INFO_ZONE, ios::binary);
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_INFO_ZONE").c_str(), zoneTable2))
		return FALSE;
	g_pZoneTable->LoadFromFile(zoneTable2);
	zoneTable2.close();


	//------------------------------------------------
	// zone file 체크
	//------------------------------------------------
	const CZoneTable::ZONEINFO_MAP&	mapZone = g_pZoneTable->GetZoneMap();

	CZoneTable::ZONEINFO_MAP::const_iterator iZoneInfo = mapZone.begin();

	while (iZoneInfo != mapZone.end())
	{
		const ZONETABLE_INFO* pZoneInfo = iZoneInfo->second;

		if (!FileCheck( pZoneInfo->Filename.GetString() ))
		{
			return FALSE;
		}

		if (!FileCheck( pZoneInfo->InfoFilename.GetString() ))
		{
			return FALSE;
		}

		//if (!FileCheck( pZoneInfo->TeenFilename.GetString() ))
		{
		//	return FALSE;
		}

		iZoneInfo++;
	}

	MakeEventInfo();
	return TRUE;
}
