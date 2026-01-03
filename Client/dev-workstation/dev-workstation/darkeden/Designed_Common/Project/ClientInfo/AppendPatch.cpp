#include "StdAfx.h"
#include <fstream>
#include <io.h>

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

#define FILE_INFO_NETMARBLE_APPENDPATCH			"Data\\Info\\AppendPatch.inf"

HRESULT InitFail(LPCTSTR szError,...)
{
	// 프로그램 중단..
//	g_bActiveApp = FALSE;

	//ShowCursor( TRUE );
	//ShowWindow(g_hWnd, SW_HIDE);

    char		szBuff[1024];
    va_list		vl;

    va_start(vl, szError);
    vsprintf(szBuff, szError, vl);

    //ReleaseAllObjects();
	#ifdef OUTPUT_DEBUG
		if (g_pDebugMessage!=NULL)
				g_pDebugMessage->Add( szBuff );
	#endif

    AfxMessageBox(szBuff);
    //DestroyWindow();
    va_end(vl);
	
    return 0;
}


//---------------------------------------------------------------------------
// Open File
//---------------------------------------------------------------------------
bool 
FileOpenBinary(const char* filename, ivfstream& file)
{
	if(access(filename, 0))
	{
		InitFail("[Error] File Open Error : [%s]", filename);
		return false;
	}

	file.open(filename, std::ios::binary);
	
	if (!file.is_open())
	{
		#ifdef OUTPUT_DEBUG
			if (g_pDebugMessage!=NULL)
					g_pDebugMessage->AddFormat("[Error] File Open Error : [%s]", filename);
		#endif
		InitFail("[Error] File Open Error : [%s]", filename);
		return false;
	}

	#ifdef OUTPUT_DEBUG
		if (g_pDebugMessage!=NULL)
				g_pDebugMessage->AddFormat("File Open OK : [%s]", filename);
	#endif
	return true;
}

//---------------------------------------------------------------------------
// Open File
//---------------------------------------------------------------------------
bool 
FileCheck(const char* filename)
{
	if(access(filename, 0))
	{
		InitFail("[Error] File Open Error : [%s]", filename);
		return false;
	}

	std::ifstream file;
		
	file.open(filename, std::ios::binary);
	
	if (!file)
	{
		#ifdef OUTPUT_DEBUG
			if (g_pDebugMessage!=NULL)
					g_pDebugMessage->AddFormat("[Error] File Open Error : [%s]", filename);
		#endif
		
		InitFail("[Error] File Open Error : [%s]", filename);
		return false;
	}

	file.close();

	return true;
}


//-----------------------------------------------------------------------------
// Init AppendPatchInfo
//-----------------------------------------------------------------------------
#define CHECK_FINAL_FILE													\
																			\
		sprintf(str, "%s\\%s", FINAL_DIR, pPatch->GetOriginalFilename() );	\
																			\
		if (!pPatch->SetFinalInfo( str ))									\
		{																	\
			InitFail("[Error] Check Final AppendPatchInfo : %s", pPatch->GetOriginalFilename());	\
			return FALSE;													\
		}																	\
																			\
		if (!pPatch->CalculateFinalInfo())									\
		{																	\
			InitFail("[Error] Calculate Final AppendPatchInfo : %s", pPatch->GetOriginalFilename());	\
			return FALSE;													\
		}

#define APPEND_PATCH( filename )									\
																	\
		if (!pPatch->AddAppendInfo( filename ))						\
		{															\
			InitFail("[Error] Add AppendPatchInfo : %s", filename);	\
			return FALSE;											\
		}

void SET_ORIGINAL_INFO( AppendPatch *pPatch, const char *filename, const char* originalDir)
{
	char sz_temp_filename[512];
	sprintf(sz_temp_filename, "%s\\%s", originalDir, filename);

	std::ifstream orgFile(sz_temp_filename, std::ios::binary);
	
	if (orgFile.is_open())
	{
		WORD orgSpkSize;
		orgFile.read((char*)&orgSpkSize, 2);	// Sprite의 개수
		
		orgFile.seekg(0, std::ios::end);
		int orgFilesize = orgFile.tellg();

		pPatch->SetOriginalInfo(filename, orgFilesize, orgSpkSize);
	}
	else
	{
		char sz_error_string[512];
		sprintf(sz_error_string, "Error Open : %s", sz_temp_filename);
		AfxMessageBox(sz_error_string);
	}
}

//#define	FILE_INFO_NETMARBLE_APPENDPATCH				"Data\\Info\\NetmarbleAppendPatch.inf"

//#define __MAKE_CHINA_INFO__


//////////////////////////////////////////////////////////////////////////
// 본서버인가 테스트서버인가.
// __MAKE_REAL_SERVER__ 를 하면 본서버/넷마블용 패치 인포를 만든다.

//*
#define __MAKE_REAL_SERVER__
/*/
#define __MAKE_TEST_INFO__
//*/

//////////////////////////////////////////////////////////////////////////
// __MAKE_REAL_SERVER__를 define 했을경우 넷마블인가 본서버 인가

//*
#define __MAKE_NETMARBLE_INFO__
/*/
#define __MAKE_MAIN_INFO__
//*/


BOOL
InitAppendPatchInfo()
{
	//-----------------------------------------------------------------------------
	// ImageObject Patch
	//-----------------------------------------------------------------------------
	AppendPatchTable apt, netmarbleApt;
	
	//-----------------------------------------------------------------------------
	// 추가되는거 있으면 이거 바꿔줘야 한다.
	//-----------------------------------------------------------------------------
	apt.Init( 30 );	
	
	AppendPatch* pPatch = NULL;

	int index = 0;

//	BOOL bOK = TRUE;

	const char* FINAL_DIR = "\\Darkeden_Data\\Korea_DarkedenTest\\";

	//const char* FINAL_DIR = "\\DarkedenTest\\";
	
	const char* REAL_SERVER_DIR = "Original_data";
	const char* TEST_ORIGINAL_DIR = "Test_Original_data";
	const char* NETMARBLE_ORIGINAL_DIR = "Netmarble_Original_data";
	const char* CHINA_ORIGINAL_DIR = "China_Original_data";
	const char* ORIGINAL_DIR;

	char str[256];

#ifdef __MAKE_CHINA_INFO__
	ORIGINAL_DIR = CHINA_ORIGINAL_DIR;
#endif

#ifdef __MAKE_TEST_INFO__
	ORIGINAL_DIR = TEST_ORIGINAL_DIR;
#endif

#ifdef __MAKE_NETMARBLE_INFO__
	ORIGINAL_DIR = NETMARBLE_ORIGINAL_DIR;
#endif

#ifdef __MAKE_REAL_SERVER__
	
#ifdef __MAKE_MAIN_INFO__
	ORIGINAL_DIR = REAL_SERVER_DIR;
#endif
	//-----------------------------------------------------------------------------
	// 0 ImageObject.spk
	//-----------------------------------------------------------------------------	
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_IMAGEOBJECT").c_str(), ORIGINAL_DIR );
	//pPatch->SetOriginalInfo( FILE_SPRITE_IMAGEOBJECT, 47564158, 0x04CA );
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7ImageObject.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New9ImageObject.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15ImageObject.spk" );
#endif
#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New16ImageObject.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New43ImageObject.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New45ImageObject.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New49ImageObject.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New55ImageObject.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New59ImageObject.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New83ImageObject.spk" );
#endif
	APPEND_PATCH( "Data\\AppendPatch\\New117ImageObject.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New133ImageObject.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New154ImageObject.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New173ImageObject.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New189ImageObject.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New195ImageObject.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New229ImageObject.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New230ImageObject.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New233ImageObject.spk" );

	APPEND_PATCH( "Data\\AppendPatch\\New289ImageObject.spk" );

#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New302ImageObject.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New305ImageObject.spk" );	
#endif
	
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New303ImageObject.spk" );	
	APPEND_PATCH( "Data\\AppendPatch\\New306ImageObject.spk" );	
#endif

	APPEND_PATCH( "Data\\AppendPatch\\New329ImageObject.spk" ); //20070417 by diesirace


	//APPEND_PATCH( "Data\\AppendPatch\\New305ImageObject.spk" );	
	
	
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 1 ImageObject.spk
	//-----------------------------------------------------------------------------	
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_IMAGEOBJECT").c_str(), ORIGINAL_DIR );
	//pPatch->SetOriginalInfo( FILE_SPRITE_IMAGEOBJECT, 47564158, 0x04CA );
//#ifdef __MAKE_NETMARBLE_INFO__
//	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7ImageObject.sspk" );
//	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New9ImageObject.sspk" );
//	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15ImageObject.sspk" );
//#endif
//
//#ifdef __MAKE_MAIN_INFO__
//	APPEND_PATCH( "Data\\AppendPatch\\New43ImageObject.sspk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New45ImageObject.sspk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New49ImageObject.sspk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New55ImageObject.sspk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New59ImageObject.sspk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New83ImageObject.sspk" );
//#endif
//	APPEND_PATCH( "Data\\AppendPatch\\New117ImageObject.sspk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New133ImageObject.sspk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New154ImageObject.sspk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New173ImageObject.sspk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New189ImageObject.sspk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New195ImageObject.sspk" );
	CHECK_FINAL_FILE;
	
	//-----------------------------------------------------------------------------
	// 2 Tile.spk
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_TILE").c_str(), ORIGINAL_DIR );
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7Tile.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15Tile.spk" );
#endif
#ifdef __MAKE_MAIN_INFO__
//	APPEND_PATCH( "Data\\AppendPatch\\New16Tile.spk" );

	APPEND_PATCH( "Data\\AppendPatch\\New43Tile.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New45Tile.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New55Tile.spk" );	
	APPEND_PATCH( "Data\\AppendPatch\\New83Tile.spk" );	
#endif
	APPEND_PATCH( "Data\\AppendPatch\\New117Tile.spk" );	
	APPEND_PATCH( "Data\\AppendPatch\\New133Tile.spk" );	
	APPEND_PATCH( "Data\\AppendPatch\\New154Tile.spk" );	
	APPEND_PATCH( "Data\\AppendPatch\\New189Tile.spk" );	
	APPEND_PATCH( "Data\\AppendPatch\\New229Tile.spk" );	
	APPEND_PATCH( "Data\\AppendPatch\\New233Tile.spk" );	
	APPEND_PATCH( "Data\\AppendPatch\\New234Tile.spk" );	

	APPEND_PATCH( "Data\\AppendPatch\\New289Tile.spk" );	


#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New305Tile.spk" );
#endif
	
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New306Tile.spk" );
#endif



	CHECK_FINAL_FILE;


	//-----------------------------------------------------------------------------
	// 3 Creature.ispk
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_CREATURE").c_str(), ORIGINAL_DIR );
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New5Creature.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New6Creature.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7Creature.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New9Creature.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New10Creature.ispk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New13Creature.ispk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15Creature.ispk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New17Creature.ispk" );	
#endif
#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New16Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New19Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New33Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New38Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New43Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New45Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New50Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New59Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New61Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New69Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New80Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New83Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New94Creature.ispk" );
#endif
	APPEND_PATCH( "Data\\AppendPatch\\New104Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New117Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New126Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New140Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New147Creature.ispk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New170Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New172Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New173Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New178Creature.ispk" ); // 웨이포인트 3종
	APPEND_PATCH( "Data\\AppendPatch\\New184Creature.ispk" ); // 수정 질드레
	APPEND_PATCH( "Data\\AppendPatch\\New189Creature.ispk" ); // 길드타워, 다크베리트 디펜더
	APPEND_PATCH( "Data\\AppendPatch\\New190Creature.ispk" ); // 트랩4종, 총슬 130
	APPEND_PATCH( "Data\\AppendPatch\\New191Creature.ispk" ); // 클레이모어 수정, 장애물
	APPEND_PATCH( "Data\\AppendPatch\\New194Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New199Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New200Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New205Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New211Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New216Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New229Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New233Creature.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New246Creature.ispk" );


	APPEND_PATCH( "Data\\AppendPatch\\New289Creature.ispk" );

#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New302Creature.ispk" );
#endif
	
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New303Creature.ispk" );
#endif

	APPEND_PATCH( "Data\\AppendPatch\\New314Creature.ispk" );
	
	CHECK_FINAL_FILE;


	//-----------------------------------------------------------------------------
	// 4 Creature.sspk
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_CREATURE").c_str(), ORIGINAL_DIR );
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New9Creature.sspk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New10Creature.sspk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New13Creature.sspk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15Creature.sspk" );	
#endif
#ifdef __MAKE_MAIN_INFO__
//	APPEND_PATCH( "Data\\AppendPatch\\New16Creature.sspk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New19Creature.sspk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New33Creature.sspk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New38Creature.sspk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New43Creature.sspk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New45Creature.sspk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New50Cr종eature.sspk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New57Creature.sspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New59Creature.sspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New61Creature.sspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New69Creature.sspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New80Creature.sspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New83Creature.sspk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New94Creature.sspk" );
#endif
	APPEND_PATCH( "Data\\AppendPatch\\New104Creature.sspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New117Creature.sspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New126Creature.sspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New147Creature.sspk" );
	//APPEND_PATCH( "Data\\AppendPatch\\New170Creature.sspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New172Creature.sspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New173Creature.sspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New178Creature.sspk" ); // 웨이포인트 3종
	APPEND_PATCH( "Data\\AppendPatch\\New184Creature.sspk" ); // 수정 질드레
	APPEND_PATCH( "Data\\AppendPatch\\New189Creature.sspk" ); // 길드타워, 다크베리트 디펜더
	APPEND_PATCH( "Data\\AppendPatch\\New190Creature.sspk" ); // 트랩4종, 총슬 130
	APPEND_PATCH( "Data\\AppendPatch\\New191Creature.sspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New194Creature.sspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New199Creature.sspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New200Creature.sspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New205Creature.sspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New211Creature.sspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New216Creature.sspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New229Creature.sspk" );
	//APPEND_PATCH( "Data\\AppendPatch\\New233Creature.sspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New246Creature.sspk" );

	//APPEND_PATCH( "Data\\AppendPatch\\New280Creature.sspk" );

	APPEND_PATCH( "Data\\AppendPatch\\New289Creature.sspk" );

#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New302Creature.sspk" );
#endif
	
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New303Creature.sspk" );
#endif


	APPEND_PATCH( "Data\\AppendPatch\\New314Creature.sspk" );
	
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 5 Effect.aspk
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ASPRITE_ALPHAEFFECT").c_str(), ORIGINAL_DIR );
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15Effect.aspk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New17Effect.aspk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New19Effect.aspk" );
#endif
#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New80Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New83Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New94Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New97Effect.aspk" );
#endif
	APPEND_PATCH( "Data\\AppendPatch\\New104Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New117Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New135Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New138Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New140Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New142Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New145Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New147Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New153Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New156Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New170Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New173Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New175Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New177Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New188Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New189Effect.aspk" ); // 공성전 이펙트
	APPEND_PATCH( "Data\\AppendPatch\\New190Effect.aspk" ); // 트랩 이펙트 등등
	APPEND_PATCH( "Data\\AppendPatch\\New191Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New194Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New195Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New199Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New205Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New206Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New207Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New216Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New217Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New229Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New230Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New231Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New233Effect.aspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New246Effect.aspk" );

	APPEND_PATCH( "Data\\AppendPatch\\New249Effect.aspk" );

	APPEND_PATCH( "Data\\AppendPatch\\New256Effect.aspk" );
	
	APPEND_PATCH( "Data\\AppendPatch\\New272Effect.aspk" );

	APPEND_PATCH( "Data\\AppendPatch\\New289Effect.aspk" );

#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New302Effect.aspk" );
#endif
	
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New303Effect.aspk" );
#endif

	APPEND_PATCH( "Data\\AppendPatch\\New314Effect.aspk" );

	APPEND_PATCH( "Data\\AppendPatch\\New318Effect.aspk" ); // 승직 스킬 이팩트 2007.01.02 by chyaya
	APPEND_PATCH( "Data\\AppendPatch\\New322Effect.aspk" ); // 부활 이팩트 by chyaya

	CHECK_FINAL_FILE;


	//-----------------------------------------------------------------------------
	// 6 EffectScreen.spk
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_SCREENEFFECT").c_str(), ORIGINAL_DIR );
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15EffectScreen.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New17EffectScreen.spk" );
#endif
#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New80EffectScreen.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New83EffectScreen.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New94EffectScreen.spk" );
#endif
//	APPEND_PATCH( "Data\\AppendPatch\\New97EffectScreen.spk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New16EffectScreen.spk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New25EffectScreen.spk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New33EffectScreen.spk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New36EffectScreen.spk" );	
//	APPEND_PATCH( "Data\\AppendPatch\\New43EffectScreen.spk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New45EffectScreen.spk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New55EffectScreen.spk" );	
//	APPEND_PATCH( "Data\\AppendPatch\\New59EffectScreen.spk" );	
//	APPEND_PATCH( "Data\\AppendPatch\\New61EffectScreen.spk" );	
//	APPEND_PATCH( "Data\\AppendPatch\\New69EffectScreen.spk" );	
	APPEND_PATCH( "Data\\AppendPatch\\New126EffectScreen.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New130EffectScreen.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New135EffectScreen.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New138EffectScreen.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New140EffectScreen.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New142EffectScreen.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New153EffectScreen.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New170EffectScreen.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New173EffectScreen.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New190EffectScreen.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New192EffectScreen.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New193EffectScreen.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New199EffectScreen.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New205EffectScreen.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New217EffectScreen.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New230EffectScreen.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New233EffectScreen.spk" );

	APPEND_PATCH( "Data\\AppendPatch\\New289EffectScreen.spk" );
	
	CHECK_FINAL_FILE;
//
	//-----------------------------------------------------------------------------
	// 7 Effect.spk
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_NORMALEFFECT").c_str(), ORIGINAL_DIR );
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New6Effect.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7Effect.spk" );
#endif
#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New16Effect.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New36Effect.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New43Effect.spk" );
#endif

	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 8 Item Patch
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
//	pPatch->SetOriginalInfo( "Data\\UI\\Spk\\Item.ispk", 441166, 0x00F7 );
	SET_ORIGINAL_INFO( pPatch, "Data\\UI\\Spk\\Item.ispk", ORIGINAL_DIR );
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New5Item.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New6Item.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7Item.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New10Item.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New13Item.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15Item.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New17Item.ispk" );
#endif
#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New7Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New9Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New12Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New16Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New19Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New33Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New38Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New42Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New43Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New45Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New48Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New55Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New61Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New69Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New73Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New80Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New83Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New94Item.ispk" );
#endif
	APPEND_PATCH( "Data\\AppendPatch\\New104Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New108Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New117Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New126Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New135Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New138Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New142Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New143Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New145Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New147Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New156Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New162Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New170Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New172Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New174Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New178Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New188Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New190Item.ispk" );	// 사탕2종
	APPEND_PATCH( "Data\\AppendPatch\\New193Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New194Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New195Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New199Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New205Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New206Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New217Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New229Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New231Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New233Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New236Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New240Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New247Item.ispk" );

	APPEND_PATCH( "Data\\AppendPatch\\New249Item.ispk" );
	

#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New255Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New274Item.ispk" );
#endif

#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New256Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New275Item.ispk" );
#endif

	APPEND_PATCH( "Data\\AppendPatch\\New277Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New289Item.ispk" );

#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New296Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New298Item.ispk" );
#endif

#ifdef __MAKE_NETMARBLE_INFO__	
	APPEND_PATCH( "Data\\AppendPatch\\New297Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New300Item.ispk" );
#endif


#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New302Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New305Item.ispk" );
#endif
	
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New303Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New306Item.ispk" );
#endif

	APPEND_PATCH( "Data\\AppendPatch\\New309Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New310Item.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New314Item.ispk" );

	APPEND_PATCH( "Data\\AppendPatch\\New322Item.ispk" ); // 가죽 벗기기 의문의 물약 by chyaya	
	APPEND_PATCH( "Data\\AppendPatch\\New325Item.ispk" ); // by diesirace 20070327 마켓 아이템 추가
	APPEND_PATCH( "Data\\AppendPatch\\New333Item.ispk" ); // by diesirace 20070508 장미 이벤트
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 9 ItemTile Patch
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
//	pPatch->SetOriginalInfo( FILE_ISPRITE_ITEMTILE, 142224, 0x00F3 );
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_ITEMTILE").c_str(), ORIGINAL_DIR );
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New5ItemTile.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New6ItemTile.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7ItemTile.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New10ItemTile.ispk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New13ItemTile.ispk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15ItemTile.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New17ItemTile.ispk" );
#endif
#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New7ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New9ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New12ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New16ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New19ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New33ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New38ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New42ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New43ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New45ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New48ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New55ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New61ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New69ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New73ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New80ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New83ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New94ItemTile.ispk" );
#endif
	APPEND_PATCH( "Data\\AppendPatch\\New104ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New108ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New117ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New126ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New135ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New138ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New142ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New143ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New145ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New147ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New156ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New162ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New170ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New172ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New174ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New178ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New188ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New190ItemTile.ispk" ); // 사탕 2종
	APPEND_PATCH( "Data\\AppendPatch\\New193ItemTile.ispk" ); 
	APPEND_PATCH( "Data\\AppendPatch\\New194ItemTile.ispk" ); 
	APPEND_PATCH( "Data\\AppendPatch\\New195ItemTile.ispk" ); 
	APPEND_PATCH( "Data\\AppendPatch\\New206ItemTile.ispk" ); 
	APPEND_PATCH( "Data\\AppendPatch\\New217ItemTile.ispk" ); 
	APPEND_PATCH( "Data\\AppendPatch\\New229ItemTile.ispk" ); 
	APPEND_PATCH( "Data\\AppendPatch\\New230ItemTile.ispk" ); 
	APPEND_PATCH( "Data\\AppendPatch\\New231ItemTile.ispk" ); 
	APPEND_PATCH( "Data\\AppendPatch\\New233ItemTile.ispk" ); 
	APPEND_PATCH( "Data\\AppendPatch\\New236ItemTile.ispk" ); 
	APPEND_PATCH( "Data\\AppendPatch\\New240ItemTile.ispk" ); 
	APPEND_PATCH( "Data\\AppendPatch\\New247ItemTile.ispk" ); 

	APPEND_PATCH( "Data\\AppendPatch\\New249ItemTile.ispk" ); 
	
	
#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New255ItemTile.ispk" ); 
	APPEND_PATCH( "Data\\AppendPatch\\New274ItemTile.ispk" ); 
#endif

#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New256ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New275ItemTile.ispk" );
#endif
	
	APPEND_PATCH( "Data\\AppendPatch\\New277ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New289ItemTile.ispk" );
	
	
#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New296ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New298ItemTile.ispk" );
#endif

#ifdef __MAKE_NETMARBLE_INFO__	
	APPEND_PATCH( "Data\\AppendPatch\\New297ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New300ItemTile.ispk" );
#endif

#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New302ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New305ItemTile.ispk" );
#endif
	
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New303ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New306ItemTile.ispk" );
#endif
	
	APPEND_PATCH( "Data\\AppendPatch\\New309ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New310ItemTile.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New314ItemTile.ispk" );
	
	APPEND_PATCH( "Data\\AppendPatch\\New318ItemTile.ispk" ); // 드롭 이미지 수정 2007.01.02 by chyaya
	APPEND_PATCH( "Data\\AppendPatch\\New322ItemTile.ispk" ); // 가죽 벗기기 의문의 물약 by chyaya
	APPEND_PATCH( "Data\\AppendPatch\\New325ItemTile.ispk" ); // by diesirace 20070320 마켓 아이템 추가
	APPEND_PATCH( "Data\\AppendPatch\\New333ItemTile.ispk" ); // by diesirace 20070508 장미 이벤트

	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 10 ItemDrop Patch
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
//	pPatch->SetOriginalInfo( FILE_ISPRITE_ITEMDROP, 579872, 0x03CC );
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_ITEMDROP").c_str(), ORIGINAL_DIR );
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New5ItemDrop.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New6ItemDrop.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7ItemDrop.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New10ItemDrop.ispk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New13ItemDrop.ispk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15ItemDrop.ispk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New17ItemDrop.ispk" );	
#endif
#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New7ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New9ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New12ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New16ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New19ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New33ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New38ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New42ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New43ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New45ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New48ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New55ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New61ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New69ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New73ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New80ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New83ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New94ItemDrop.ispk" );	
#endif
	APPEND_PATCH( "Data\\AppendPatch\\New104ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New108ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New117ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New126ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New135ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New138ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New142ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New143ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New145ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New147ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New156ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New162ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New170ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New172ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New174ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New178ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New188ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New190ItemDrop.ispk" );	// 사탕 2종
	APPEND_PATCH( "Data\\AppendPatch\\New193ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New194ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New195ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New206ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New217ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New229ItemDrop.ispk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New231ItemDrop.ispk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New233ItemDrop.ispk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New236ItemDrop.ispk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New240ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New241ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New247ItemDrop.ispk" );

	APPEND_PATCH( "Data\\AppendPatch\\New249ItemDrop.ispk" );
	

#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New255ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New274ItemDrop.ispk" );
#endif

#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New256ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New275ItemDrop.ispk" );
#endif
	
	APPEND_PATCH( "Data\\AppendPatch\\New277ItemDrop.ispk" );

	APPEND_PATCH( "Data\\AppendPatch\\New289ItemDrop.ispk" );
	
#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New296ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New298ItemDrop.ispk" );
#endif

#ifdef __MAKE_NETMARBLE_INFO__	
	APPEND_PATCH( "Data\\AppendPatch\\New297ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New300ItemDrop.ispk" );
#endif
	

#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New302ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New305ItemDrop.ispk" );
#endif
	
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New303ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New306ItemDrop.ispk" );
#endif

	APPEND_PATCH( "Data\\AppendPatch\\New309ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New310ItemDrop.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New314ItemDrop.ispk" );

	APPEND_PATCH( "Data\\AppendPatch\\New318ItemDrop.ispk" ); // 드롭 이미지 수정 2007.01.02 by chyaya
	APPEND_PATCH( "Data\\AppendPatch\\New322ItemDrop.ispk" ); // 가죽 벗기기 의문의 물약 by chyaya
	APPEND_PATCH( "Data\\AppendPatch\\New325ItemDrop.ispk" ); // by diesirace 20070320 마켓아이템 추가
	APPEND_PATCH( "Data\\AppendPatch\\New333ItemDrop.ispk" ); // by diesirace 20070508 장미 이벤트

	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 11 ItemDescription Patch
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
//	pPatch->SetOriginalInfo( FILE_SPRITE_ITEM_DESCRIPTION, 6521842, 0x0104 );
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_ITEM_DESCRIPTION").c_str(), ORIGINAL_DIR );
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New5ItemDescription.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New6ItemDescription.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7ItemDescription.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New10ItemDescription.spk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New13ItemDescription.spk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15ItemDescription.spk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New17ItemDescription.spk" );	
#endif
#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New7ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New9ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New12ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New16ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New33ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New38ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New42ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New43ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New45ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New48ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New55ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New61ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New69ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New73ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New80ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New83ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New94ItemDescription.spk" );
#endif
	APPEND_PATCH( "Data\\AppendPatch\\New104ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New108ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New117ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New126ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New135ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New138ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New142ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New143ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New145ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New147ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New156ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New162ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New170ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New172ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New174ItemDescription.spk" ); // 질드레 보상아이템 잘못된거 + 수정한거 같이 ..
	APPEND_PATCH( "Data\\AppendPatch\\New178ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New188ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New190ItemDescription.spk" ); // 사탕 2종
	APPEND_PATCH( "Data\\AppendPatch\\New193ItemDescription.spk" ); 
	APPEND_PATCH( "Data\\AppendPatch\\New194ItemDescription.spk" ); 
	APPEND_PATCH( "Data\\AppendPatch\\New195ItemDescription.spk" ); 
	APPEND_PATCH( "Data\\AppendPatch\\New206ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New217ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New229ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New231ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New233ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New236ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New240ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New247ItemDescription.spk" );

	APPEND_PATCH( "Data\\AppendPatch\\New249ItemDescription.spk" );
	
#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New255ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New274ItemDescription.spk" );
#endif

#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New256ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New275ItemDescription.spk" );
#endif
	
	APPEND_PATCH( "Data\\AppendPatch\\New277ItemDescription.spk" );

	APPEND_PATCH( "Data\\AppendPatch\\New289ItemDescription.spk" );
	
#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New296ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New298ItemDescription.spk" );
#endif

#ifdef __MAKE_NETMARBLE_INFO__	
	APPEND_PATCH( "Data\\AppendPatch\\New297ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New300ItemDescription.spk" );
#endif

#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New302ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New305ItemDescription.spk" );
#endif
	
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New303ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New306ItemDescription.spk" );
#endif

	APPEND_PATCH( "Data\\AppendPatch\\New309ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New310ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New314ItemDescription.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New322ItemDescription.spk" ); // 가죽 벗기기 의문의 물약 by chyaya
	APPEND_PATCH( "Data\\AppendPatch\\New325ItemDescription.spk" ); // by diesirace 20070320 마켓아이템 추가
	APPEND_PATCH( "Data\\AppendPatch\\New333ItemDescription.spk" ); // by diesirace 20070508 장미 이벤트


	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 12 Minimap Patch
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
//	pPatch->SetOriginalInfo( FILE_SPRITE_MINIMAP, 6521842, 0x0104 );
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_MINIMAP").c_str(), ORIGINAL_DIR );
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New5Minimap.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New6Minimap.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7Minimap.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New9Minimap.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New13Minimap.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15Minimap.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New19Minimap.spk" );
#endif
#ifdef __MAKE_MAIN_INFO__
//	APPEND_PATCH( "Data\\AppendPatch\\New7Minimap.spk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New9Minimap.spk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New33Minimap.spk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New38Minimap.spk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New43Minimap.spk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New45Minimap.spk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New49Minimap.spk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New50Minimap.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New55MiniMap.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New59MiniMap.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New80MiniMap.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New83MiniMap.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New97MiniMap.spk" );	
#endif
	APPEND_PATCH( "Data\\AppendPatch\\New112MiniMap.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New117MiniMap.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New133MiniMap.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New164MiniMap.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New173MiniMap.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New195MiniMap.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New199MiniMap.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New229MiniMap.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New230MiniMap.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New231MiniMap.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New233MiniMap.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New234MiniMap.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New246MiniMap.spk" );

	APPEND_PATCH( "Data\\AppendPatch\\New289Minimap.spk" );



#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New296Minimap.spk" );
#endif

#ifdef __MAKE_NETMARBLE_INFO__	
	APPEND_PATCH( "Data\\AppendPatch\\New297Minimap.spk" );
#endif


#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New302Minimap.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New305Minimap.spk" );
#endif
	
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New303Minimap.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New306Minimap.spk" );
#endif

	//APPEND_PATCH( "Data\\AppendPatch\\New305Minimap.spk" );
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 13 SkillIcon Patch
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_SKILLICON").c_str(), ORIGINAL_DIR );
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New3SkillIcon.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New6SkillIcon.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7SkillIcon.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New13SkillIcon.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15SkillIcon.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New17SkillIcon.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New19SkillIcon.spk" );
#endif
#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New19SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New22SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New30SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New36SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New43SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New45SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New49SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New50SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New69SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New73SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New80SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New83SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New94SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New97SkillIcon.spk" );
#endif
	APPEND_PATCH( "Data\\AppendPatch\\New104SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New117SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New123SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New133SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New161SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New193SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New194SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New195SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New217SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New229SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New232SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New249SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New272SkillIcon.spk" );
#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New274SkillIcon.spk" );
#endif 
	
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New275SkillIcon.spk" );
#endif

	APPEND_PATCH( "Data\\AppendPatch\\New289SkillIcon.spk" );


#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New302SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New305SkillIcon.spk" );
#endif
	
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New303SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New306SkillIcon.spk" );
#endif

	APPEND_PATCH( "Data\\AppendPatch\\New314SkillIcon.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New322SkillIcon.spk" );	// 가죽 벗기기 by chyaya


	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 14 SkillMini Patch
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_SKILLMINI").c_str(), ORIGINAL_DIR );
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New3SkillMini.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New6SkillMini.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7SkillMini.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New13SkillMini.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15SkillMini.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New17SkillMini.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New19SkillMini.spk");
#endif
#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New19SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New22SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New30SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New36SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New43SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New45SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New49SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New50SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New69SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New73SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New80SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New83SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New94SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New97SkillMini.spk" );
#endif
	APPEND_PATCH( "Data\\AppendPatch\\New104SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New117SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New123SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New133SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New161SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New173SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New193SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New194SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New195SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New217SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New229SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New232SkillMini.spk" );

	APPEND_PATCH( "Data\\AppendPatch\\New249SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New272SkillMini.spk" );

#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New274SkillMini.spk" );
#endif

#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New275SkillMini.spk" );
#endif
	
	APPEND_PATCH( "Data\\AppendPatch\\New289SkillMini.spk" );


#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New302SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New305SkillMini.spk" );
#endif
	
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New303SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New306SkillMini.spk" );
#endif

	APPEND_PATCH( "Data\\AppendPatch\\New314SkillMini.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New322SkillMini.spk" );	// 가죽 벗기기 by chyaya


	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 15 Addon Patch
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_ADDON").c_str(), ORIGINAL_DIR );
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New9Addon.ispk" );
#endif

#ifdef __MAKE_MAIN_INFO__
//	APPEND_PATCH( "Data\\AppendPatch\\New55Addon.ispk" );
	APPEND_PATCH( "Data\\AppendPatch\\New59Addon.ispk" );
#endif
	APPEND_PATCH( "Data\\AppendPatch\\New104Addon.ispk" );

	APPEND_PATCH( "Data\\AppendPatch\\New289Addon.ispk" );
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 16 Addon Shadow Patch
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_ADDON").c_str(), ORIGINAL_DIR );
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New9Addon.sspk" );
#endif

#ifdef __MAKE_MAIN_INFO__
//	APPEND_PATCH( "Data\\AppendPatch\\New55Addon.sspk" );
	APPEND_PATCH( "Data\\AppendPatch\\New59Addon.sspk" );
#endif
	APPEND_PATCH( "Data\\AppendPatch\\New104Addon.sspk" );
	
	APPEND_PATCH( "Data\\AppendPatch\\New289Addon.sspk" );
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 17 Ousters ispk
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_OUSTERS").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\AppendPatch\\New289Ousters.ispk");
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 18 Ousters sspk
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_OUSTERS").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\AppendPatch\\New289Ousters.sspk");
	CHECK_FINAL_FILE;


	//-----------------------------------------------------------------------------
	// 19 NPCFACE Patch
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_NPCFACE").c_str(), ORIGINAL_DIR );
#ifdef __MAKE_NETMARBLE_INFO__
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7NpcFace.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New10NpcFace.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New13NpcFace.spk" );
#endif
#ifdef __MAKE_MAIN_INFO__
	APPEND_PATCH( "Data\\AppendPatch\\New43NpcFace.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New61NpcFace.spk" );
//	APPEND_PATCH( "Data\\AppendPatch\\New69NpcFace.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New80NpcFace.spk" );
#endif
	APPEND_PATCH( "Data\\AppendPatch\\New117NpcFace.spk" );
	APPEND_PATCH( "Data\\AppendPatch\\New322NpcFace.spk" );		// 카를코흐 얼굴 by chyaya
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 20 Advancement Slayer male
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_ADVANCEMENT_CLASS_SLAYER_MAN").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\AppendPatch\\New325ACSlayerMan.ispk" ); // by diesirace 20070327 마켓아이템 추가
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 21 Advancement Slayer male Shadow
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_ADVANCEMENT_CLASS_SLAYER_MAN").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\AppendPatch\\New325ACSlayerManShadow.sspk" ); // by diesirace 20070327 마켓아이템 추가
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 22 Advancement Slayer female
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_ADVANCEMENT_CLASS_SLAYER_WOMAN").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\AppendPatch\\New325ACSlayerWoman.ispk" ); // by diesirace 20070327 마켓아이템 추가
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 23 Advancement Slayer female Shadow
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_ADVANCEMENT_CLASS_SLAYER_WOMAN").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\AppendPatch\\New325ACSlayerWomanShadow.sspk" ); // by diesirace 20070327 마켓아이템 추가
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 24 Advancement Vampire male
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_ADVANCEMENT_CLASS_VAMPIRE_MAN").c_str(), ORIGINAL_DIR );
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 25 Advancement Vampire male Shadow
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_ADVANCEMENT_CLASS_VAMPIRE_MAN").c_str(), ORIGINAL_DIR );
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 26 Advancement Vampire female
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_ADVANCEMENT_CLASS_VAMPIRE_WOMAN").c_str(), ORIGINAL_DIR );
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 27 Advancement Vampire female Shadow
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_ADVANCEMENT_CLASS_VAMPIRE_WOMAN").c_str(), ORIGINAL_DIR );
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 28 Advancement Ousters
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_ADVANCEMENT_CLASS_OUSTERS").c_str(), ORIGINAL_DIR );
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 29 Advancement Ousters Shadow
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_ADVANCEMENT_CLASS_OUSTERS").c_str(), ORIGINAL_DIR );
	CHECK_FINAL_FILE;
	
#endif
	
#ifdef __MAKE_TEST_INFO__
	//-----------------------------------------------------------------------------
	// 0 ImageObject.spk
	//-----------------------------------------------------------------------------	
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_IMAGEOBJECT").c_str(), ORIGINAL_DIR );
	//pPatch->SetOriginalInfo( FILE_SPRITE_IMAGEOBJECT, 47564158, 0x04CA );
	APPEND_PATCH( "Data\\TestAppendPatch\\New16ImageObject.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New43ImageObject.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New45ImageObject.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New53ImageObject.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New55ImageObject.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New57ImageObject.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New75ImageObject.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New89ImageObject.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New107ImageObject.spk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New69ImageObject.spk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New73ImageObject.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New124ImageObject.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New150ImageObject.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New161ImageObject.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New167ImageObject.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New191ImageObject.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New195ImageObject.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New197ImageObject.spk" );

	APPEND_PATCH( "Data\\TestAppendPatch\\New225ImageObject.spk" );

	APPEND_PATCH( "Data\\TestAppendPatch\\New237ImageObject.spk" );


	APPEND_PATCH( "Data\\TestAppendPatch\\New241ImageObject.spk" );

	
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 1 ImageObject.sspk
	//-----------------------------------------------------------------------------	
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_IMAGEOBJECT").c_str(), ORIGINAL_DIR );
	//pPatch->SetOriginalInfo( FILE_SPRITE_IMAGEOBJECT, 47564158, 0x04CA );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New43ImageObject.sspk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New45ImageObject.sspk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New53ImageObject.sspk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New55ImageObject.sspk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New57ImageObject.sspk" );	
//	APPEND_PATCH( "Data\\TestAppendPatch\\New75ImageObject.sspk" );	
//	APPEND_PATCH( "Data\\TestAppendPatch\\New89ImageObject.sspk" );	
//	APPEND_PATCH( "Data\\TestAppendPatch\\New107ImageObject.sspk" );	
////	APPEND_PATCH( "Data\\TestAppendPatch\\New69ImageObject.sspk" );	
////	APPEND_PATCH( "Data\\TestAppendPatch\\New73ImageObject.sspk" );	
//	APPEND_PATCH( "Data\\TestAppendPatch\\New124ImageObject.sspk" );	
//	APPEND_PATCH( "Data\\TestAppendPatch\\New150ImageObject.sspk" );	
//	APPEND_PATCH( "Data\\TestAppendPatch\\New161ImageObject.sspk" );	
//	APPEND_PATCH( "Data\\TestAppendPatch\\New167ImageObject.sspk" );	
//	APPEND_PATCH( "Data\\TestAppendPatch\\New191ImageObject.sspk" );	
	// 버전 195에서 sspk 풀버전이 나간다..1.84M 정도..이미 패치된 부분 수정 때문에
	// 용량이 적어 걍 풀버전 내보냄..-_-;
	CHECK_FINAL_FILE;
	
	//-----------------------------------------------------------------------------
	// 2 Tile.spk
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_TILE").c_str(), ORIGINAL_DIR );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New16Tile.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New43Tile.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New45Tile.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New55Tile.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New69Tile.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New73Tile.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New75Tile.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New89Tile.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New107Tile.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New124Tile.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New161Tile.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New191Tile.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New197Tile.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New199Tile.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New200Tile.spk" );

	APPEND_PATCH( "Data\\TestAppendPatch\\New225Tile.spk" );

	APPEND_PATCH( "Data\\TestAppendPatch\\New241Tile.spk" );

	CHECK_FINAL_FILE;


	//-----------------------------------------------------------------------------
	// 3 Creature.ispk
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_CREATURE").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\TestAppendPatch\\New16Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New19Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New33Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New38Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New43Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New45Creature.ispk" );
	//APPEND_PATCH( "Data\\TestAppendPatch\\New50Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New55Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New57Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New61Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New66Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New69Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New71Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New75Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New78Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New82Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New89Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New91Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New93Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New104Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New115Creature.ispk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New119Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New121Creature.ispk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New142Creature.ispk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New144Creature.ispk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New146Creature.ispk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New150Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New151Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New156Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New157Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New160Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New161Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New162Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New164Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New169Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New171Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New172Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New176Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New180Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New191Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New197Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New204Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New225Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New237Creature.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New256Creature.ispk" );
	
	CHECK_FINAL_FILE;


	//-----------------------------------------------------------------------------
	// 4 Creature.sspk
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_CREATURE").c_str(), ORIGINAL_DIR );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New16Creature.sspk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New19Creature.sspk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New33Creature.sspk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New38Creature.sspk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New43Creature.sspk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New45Creature.sspk" );
//	//APPEND_PATCH( "Data\\TestAppendPatch\\New50Creature.sspk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New55Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New57Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New61Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New66Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New69Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New71Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New75Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New82Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New89Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New91Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New93Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New104Creature.sspk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New115Creature.sspk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New119Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New121Creature.sspk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New142Creature.sspk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New144Creature.sspk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New146Creature.sspk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New150Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New151Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New156Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New157Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New160Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New161Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New162Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New164Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New169Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New171Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New172Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New176Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New180Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New191Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New204Creature.sspk" );	
	APPEND_PATCH( "Data\\TestAppendPatch\\New225Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New237Creature.sspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New256Creature.sspk" );
	
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 5 EffectScreen.spk
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, "Data\\Image\\EffectScreen.spk", ORIGINAL_DIR );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New69EffectScreen.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New70EffectScreen.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New71EffectScreen.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New75EffectScreen.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New106EffectScreen.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New107EffectScreen.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New110EffectScreen.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New114EffectScreen.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New118EffectScreen.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New119EffectScreen.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New124EffectScreen.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New139EffectScreen.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New144EffectScreen.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New161EffectScreen.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New162EffectScreen.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New171EffectScreen.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New172EffectScreen.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New183EffectScreen.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New192EffectScreen.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New197EffectScreen.spk" );

	APPEND_PATCH( "Data\\TestAppendPatch\\New225EffectScreen.spk" );
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 6 Effect.aspk
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, "Data\\Image\\Effect.aspk", ORIGINAL_DIR );
	APPEND_PATCH( "Data\\TestAppendPatch\\New69Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New71Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New73Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New75Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New78Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New79Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New81Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New82Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New89Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New112Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New114Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New115Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New118Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New119Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New121Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New122Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New124Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New125Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New139Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New144Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New145Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New146Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New148Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New150Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New155Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New156Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New159Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New160Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New161Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New162Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New164Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New167Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New169Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New172Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New173Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New175Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New180Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New183Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New191Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New192Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New197Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New198Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New204Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New206Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New208Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New210Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New225Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New237Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New239Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New254Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New256Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New262Effect.aspk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New267Effect.aspk" );

	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 7 Effect.spk
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_NORMALEFFECT").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\TestAppendPatch\\New16Effect.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New36Effect.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New43Effect.spk" );

	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 8 Item Patch
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
//	pPatch->SetOriginalInfo( "Data\\UI\\Spk\\Item.ispk", 441166, 0x00F7 );
	SET_ORIGINAL_INFO( pPatch, "Data\\UI\\Spk\\Item.ispk", ORIGINAL_DIR );
	APPEND_PATCH( "Data\\TestAppendPatch\\New61Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New66Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New69Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New71Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New73Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New75Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New78Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New81Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New85Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New89Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New92Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New93Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New104Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New111Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New112Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New115Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New119Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New120Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New121Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New124Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New130Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New133Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New142Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New146Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New151Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New156Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New159Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New161Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New162Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New164Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New169Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New171Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New173Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New175Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New183Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New192Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New197Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New198Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New200Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New201Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New206Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New208Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New212Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New215Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New228Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New234Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New236Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New237Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New241Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New246Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New249Item.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New256Item.ispk" ); // 터프한 눈사람 2006.11.30 by chyaya
	APPEND_PATCH( "Data\\TestAppendPatch\\New265Item.ispk" ); // 일자코흐 입장권 2007.01.15 by diesirace
	APPEND_PATCH( "Data\\TestAppendPatch\\New272Item.ispk" ); // by diesirace 20070320 마켓 아이템 추가

	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 9 ItemTile Patch
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
///	pPatch->SetOriginalInfo( FILE_ISPRITE_ITEMTILE, 142224, 0x00F3 );
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_ITEMTILE").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\TestAppendPatch\\New71ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New73ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New75ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New78ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New81ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New85ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New89ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New92ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New93ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New104ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New111ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New112ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New115ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New119ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New120ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New121ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New124ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New130ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New133ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New142ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New146ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New151ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New156ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New159ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New161ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New162ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New164ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New169ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New175ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New183ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New192ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New194ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New197ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New198ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New200ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New201ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New206ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New208ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New212ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New215ItemTile.ispk" );
	//APPEND_PATCH( "Data\\TestAppendPatch\\New228ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New232ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New234ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New236ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New237ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New241ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New246ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New249ItemTile.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New256ItemTile.ispk" ); // 터프한 눈사람 2006.11.30 by chyaya
	APPEND_PATCH( "Data\\TestAppendPatch\\New262ItemTile.ispk" ); // 아이템 타일 이미지 수정 2006.12.21 by diesirace
	APPEND_PATCH( "Data\\TestAppendPatch\\New265ItemTile.ispk" ); // 일자코흐 입장권 아이템 2007.01.15 by diesirace
	APPEND_PATCH( "Data\\TestAppendPatch\\New272ItemTile.ispk" ); // by diesirace 20070320 마켓 아이템 추가

	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 10 ItemDrop Patch
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
//	pPatch->SetOriginalInfo( FILE_ISPRITE_ITEMDROP, 579872, 0x03CC );
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_ITEMDROP").c_str(), ORIGINAL_DIR );
	
	APPEND_PATCH( "Data\\TestAppendPatch\\New61ItemDrop.ispk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New64ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New66ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New69ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New71ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New73ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New75ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New78ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New81ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New85ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New89ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New92ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New93ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New104ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New111ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New112ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New115ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New119ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New120ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New121ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New124ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New130ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New133ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New142ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New146ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New151ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New156ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New159ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New161ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New162ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New164ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New169ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New175ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New183ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New192ItemDrop.ispk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New197ItemDrop.ispk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New198ItemDrop.ispk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New200ItemDrop.ispk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New201ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New202ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New206ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New208ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New212ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New215ItemDrop.ispk" );
	//APPEND_PATCH( "Data\\TestAppendPatch\\New228ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New232ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New234ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New236ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New237ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New241ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New246ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New249ItemDrop.ispk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New256ItemDrop.ispk" ); // 터프한 눈사람 2006.11.30 by chyaya
	APPEND_PATCH( "Data\\TestAppendPatch\\New262ItemDrop.ispk" ); // 아이템 타일 이미지 수정 2006.12.21 by diesirace
	APPEND_PATCH( "Data\\TestAppendPatch\\New265ItemDrop.ispk" ); // 일자코흐 입장권 아이템  2007.01.15 by diesirace
	APPEND_PATCH( "Data\\TestAppendPatch\\New272ItemDrop.ispk" ); // by diesirace 20070320 마켓아이템 추가

	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 11 ItemDescription Patch
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
//	pPatch->SetOriginalInfo( FILE_SPRITE_ITEM_DESCRIPTION, 6521842, 0x0104 );
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_ITEM_DESCRIPTION").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\TestAppendPatch\\New7ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New9ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New12ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New16ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New33ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New38ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New42ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New43ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New45ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New50ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New55ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New61ItemDescription.spk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New64ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New66ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New69ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New71ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New73ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New75ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New78ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New81ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New85ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New89ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New92ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New93ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New104ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New111ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New112ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New115ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New119ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New120ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New121ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New124ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New130ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New133ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New142ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New146ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New151ItemDescription.spk" ); // 질드레 보상아이템 잘못된거 - 담에 수정?
	APPEND_PATCH( "Data\\TestAppendPatch\\New152ItemDescription.spk" ); // 질드레 보상아이템 수정된거
	APPEND_PATCH( "Data\\TestAppendPatch\\New156ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New159ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New161ItemDescription.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New162ItemDescription.spk" ); 
	APPEND_PATCH( "Data\\TestAppendPatch\\New164ItemDescription.spk" ); 
	APPEND_PATCH( "Data\\TestAppendPatch\\New169ItemDescription.spk" ); 
	APPEND_PATCH( "Data\\TestAppendPatch\\New175ItemDescription.spk" ); 
	APPEND_PATCH( "Data\\TestAppendPatch\\New183ItemDescription.spk" ); 
	APPEND_PATCH( "Data\\TestAppendPatch\\New192ItemDescription.spk" ); 
	APPEND_PATCH( "Data\\TestAppendPatch\\New197ItemDescription.spk" ); 
	APPEND_PATCH( "Data\\TestAppendPatch\\New198ItemDescription.spk" ); 
	APPEND_PATCH( "Data\\TestAppendPatch\\New200ItemDescription.spk" ); 
	APPEND_PATCH( "Data\\TestAppendPatch\\New201ItemDescription.spk" ); 
	APPEND_PATCH( "Data\\TestAppendPatch\\New206ItemDescription.spk" ); 
	APPEND_PATCH( "Data\\TestAppendPatch\\New208ItemDescription.spk" ); 
	APPEND_PATCH( "Data\\TestAppendPatch\\New212ItemDescription.spk" ); 
	APPEND_PATCH( "Data\\TestAppendPatch\\New215ItemDescription.spk" ); 
	APPEND_PATCH( "Data\\TestAppendPatch\\New228ItemDescription.spk" ); 
	APPEND_PATCH( "Data\\TestAppendPatch\\New234ItemDescription.spk" ); 
	APPEND_PATCH( "Data\\TestAppendPatch\\New236ItemDescription.spk" ); 
	APPEND_PATCH( "Data\\TestAppendPatch\\New237ItemDescription.spk" ); 
	APPEND_PATCH( "Data\\TestAppendPatch\\New241ItemDescription.spk" ); 
	APPEND_PATCH( "Data\\TestAppendPatch\\New246ItemDescription.spk" ); 
	APPEND_PATCH( "Data\\TestAppendPatch\\New249ItemDescription.spk" ); 
	APPEND_PATCH( "Data\\TestAppendPatch\\New256ItemDescription.spk" ); // 터프한 눈사람 2006.11.30 by chyaya
	APPEND_PATCH( "Data\\TestAppendPatch\\New265ItemDescription.spk" ); // 일자코흐 입장권 아이템 2007.01.15 by diesirace
	APPEND_PATCH( "Data\\TestAppendPatch\\New272ItemDescription.spk" ); // by diesirace 20070320 마켓아이템 추가
	
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 12 Minimap Patch
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++]; 
//	pPatch->SetOriginalInfo( FILE_SPRITE_MINIMAP, 6521842, 0x0104 );
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_MINIMAP").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\TestAppendPatch\\New7Minimap.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New9Minimap.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New33Minimap.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New38Minimap.spk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New43Minimap.spk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New45Minimap.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New53Minimap.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New55Minimap.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New57Minimap.spk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New69Minimap.spk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New71Minimap.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New73Minimap.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New75Minimap.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New78Minimap.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New89Minimap.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New107Minimap.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New134Minimap.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New151Minimap.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New168Minimap.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New171Minimap.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New191Minimap.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New195Minimap.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New197Minimap.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New199Minimap.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New200Minimap.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New204Minimap.spk" );


	APPEND_PATCH( "Data\\TestAppendPatch\\New225Minimap.spk" );

	APPEND_PATCH( "Data\\TestAppendPatch\\New234Minimap.spk" );

	APPEND_PATCH( "Data\\TestAppendPatch\\New237Minimap.spk" );

	APPEND_PATCH( "Data\\TestAppendPatch\\New241Minimap.spk" );
	
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 13 SkillIcon Patch
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_SKILLICON").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\TestAppendPatch\\New19SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New22SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New30SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New36SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New43SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New45SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New51SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New53SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New64SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New66SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New69SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New73SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New75SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New78SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New79SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New83SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New84SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New89SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New92SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New108SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New132SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New162SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New163SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New167SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New180SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New192SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New197SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New208SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New210SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New212SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New228SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New237SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New242SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New254SkillIcon.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New265SkillIcon.spk" );	// 일자코흐 입장권 2007.01.25 by chyaya

	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 14 SkillMini Patch
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_SKILLMINI").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\TestAppendPatch\\New19SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New22SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New30SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New36SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New43SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New45SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New51SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New53SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New64SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New66SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New69SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New73SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New75SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New78SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New79SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New83SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New84SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New89SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New92SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New108SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New132SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New148SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New162SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New163SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New167SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New180SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New192SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New197SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New208SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New210SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New212SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New228SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New237SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New242SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New254SkillMini.spk" );
	APPEND_PATCH( "Data\\TestAppendPatch\\New265SkillMini.spk" );	// 일자코흐 입장권 2007.01.25 by chyaya

	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 15 Addon ispk
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_ADDON").c_str(), ORIGINAL_DIR );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New53Addon.ispk");
//	APPEND_PATCH( "Data\\TestAppendPatch\\New55Addon.ispk");
//	APPEND_PATCH( "Data\\TestAppendPatch\\New57Addon.ispk");
//	APPEND_PATCH( "Data\\TestAppendPatch\\New79Addon.ispk");

	//APPEND_PATCH( "Data\\TestAppendPatch\\New225Addon.ispk");

//	APPEND_PATCH( "Data\\TestAppendPatch\\New232Addon.ispk");

	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 16 Addon sspk
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_ADDON").c_str(), ORIGINAL_DIR );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New53Addon.sspk");
//	APPEND_PATCH( "Data\\TestAppendPatch\\New55Addon.sspk");
//	APPEND_PATCH( "Data\\TestAppendPatch\\New57Addon.sspk");
//	APPEND_PATCH( "Data\\TestAppendPatch\\New79Addon.sspk");

	//APPEND_PATCH( "Data\\TestAppendPatch\\New225Addon.sspk");
//	APPEND_PATCH( "Data\\TestAppendPatch\\New232Addon.sspk");
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 17 Ousters ispk
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_OUSTERS").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\TestAppendPatch\\New71Ousters.ispk");
	APPEND_PATCH( "Data\\TestAppendPatch\\New73Ousters.ispk");

	APPEND_PATCH( "Data\\TestAppendPatch\\New225Ousters.ispk");
	//APPEND_PATCH( "Data\\TestAppendPatch\\New280Ousters.ispk");

	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 18 Ousters sspk
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_OUSTERS").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\TestAppendPatch\\New71Ousters.sspk");
	APPEND_PATCH( "Data\\TestAppendPatch\\New73Ousters.sspk");

	APPEND_PATCH( "Data\\TestAppendPatch\\New225Ousters.sspk");
	//APPEND_PATCH( "Data\\TestAppendPatch\\New280Ousters.sspk");

	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 19 Npc Face
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_NPCFACE").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\TESTAppendPatch\\New43NpcFace.spk" );
	APPEND_PATCH( "Data\\TESTAppendPatch\\New61NpcFace.spk" );
	APPEND_PATCH( "Data\\TESTAppendPatch\\New75NpcFace.spk" );
	APPEND_PATCH( "Data\\TESTAppendPatch\\New92NpcFace.spk" );
//	APPEND_PATCH( "Data\\TESTAppendPatch\\New69NpcFace.spk" );
//	APPEND_PATCH( "Data\\TestAppendPatch\\New74NpcFace.spk" );
	APPEND_PATCH( "Data\\TESTAppendPatch\\New265NpcFace.spk" );		// 일자코흐 입장권 (카를코흐 얼굴) 2007.01.25 by chyaya
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 20 Advancement Slayer male
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_ADVANCEMENT_CLASS_SLAYER_MAN").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\TESTAppendPatch\\New272ACSlayerMan.ispk" ); // by diesirace 20070320 마켓아이템 추가
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 21 Advancement Slayer male Shadow
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_ADVANCEMENT_CLASS_SLAYER_MAN").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\TESTAppendPatch\\New272ACSlayerManShadow.sspk" ); // by diesirace 20070320 마켓아이템 추가
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 22 Advancement Slayer female
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_ADVANCEMENT_CLASS_SLAYER_WOMAN").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\TESTAppendPatch\\New272ACSlayerWoman.ispk" ); // by diesirace 20070320 마켓아이템 추가
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 23 Advancement Slayer female Shadow
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_ADVANCEMENT_CLASS_SLAYER_WOMAN").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\TESTAppendPatch\\New272ACSlayerWomanShadow.sspk" ); // by diesirace 20070320 마켓아이템 추가
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 24 Advancement Vampire male
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_ADVANCEMENT_CLASS_VAMPIRE_MAN").c_str(), ORIGINAL_DIR );
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 25 Advancement Vampire male Shadow
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_ADVANCEMENT_CLASS_VAMPIRE_MAN").c_str(), ORIGINAL_DIR );
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 26 Advancement Vampire female
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_ADVANCEMENT_CLASS_VAMPIRE_WOMAN").c_str(), ORIGINAL_DIR );
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 27 Advancement Vampire female Shadow
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_ADVANCEMENT_CLASS_VAMPIRE_WOMAN").c_str(), ORIGINAL_DIR );
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 28 Advancement Ousters
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_ADVANCEMENT_CLASS_OUSTERS").c_str(), ORIGINAL_DIR );
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 29 Advancement Ousters Shadow
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_ADVANCEMENT_CLASS_OUSTERS").c_str(), ORIGINAL_DIR );
	CHECK_FINAL_FILE;
#endif

#ifdef __MAKE_CHINA_INFO__
	//-----------------------------------------------------------------------------
	// 0 ImageObject.spk
	//-----------------------------------------------------------------------------	
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_IMAGEOBJECT").c_str(), ORIGINAL_DIR );
	//pPatch->SetOriginalInfo( FILE_SPRITE_IMAGEOBJECT, 47564158, 0x04CA );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New31ImageObject.spk" );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New47ImageObject.spk" );
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 1 ImageObject.spk
	//-----------------------------------------------------------------------------	
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_IMAGEOBJECT").c_str(), ORIGINAL_DIR );
	//pPatch->SetOriginalInfo( FILE_SPRITE_IMAGEOBJECT, 47564158, 0x04CA );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New31ImageObject.sspk" );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New47ImageObject.sspk" );
	CHECK_FINAL_FILE;
	
	//-----------------------------------------------------------------------------
	// 2 Tile.spk
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_TILE").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New31Tile.spk" );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New47Tile.spk" );
	CHECK_FINAL_FILE;


	//-----------------------------------------------------------------------------
	// 3 Creature.ispk
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_CREATURE").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New31Creature.ispk" );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New35Creature.ispk" );
	
	CHECK_FINAL_FILE;


	//-----------------------------------------------------------------------------
	// 4 Creature.sspk
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_CREATURE").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New31Creature.sspk" );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New35Creature.sspk" );
	
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 5 EffectScreen.spk
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, "Data\\Image\\EffectScreen.spk", ORIGINAL_DIR );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New31EffectScreen.spk" );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New46EffectScreen.spk" );
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 6 Effect.aspk
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, "Data\\Image\\Effect.aspk", ORIGINAL_DIR );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New31Effect.aspk" );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New35Effect.aspk" );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New46Effect.aspk" );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New50Effect.aspk" );
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 7 Effect.spk
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_NORMALEFFECT").c_str(), ORIGINAL_DIR );
//	APPEND_PATCH( "Data\\ChinaAppendPatch\\New16Effect.spk" );

	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 8 Item Patch
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
//	pPatch->SetOriginalInfo( "Data\\UI\\Spk\\Item.ispk", 441166, 0x00F7 );
	SET_ORIGINAL_INFO( pPatch, "Data\\UI\\Spk\\Item.ispk", ORIGINAL_DIR );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New31Item.ispk" );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New46Item.ispk" );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New50Item.ispk" );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New51Item.ispk" );
	
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 9 ItemTile Patch
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
///	pPatch->SetOriginalInfo( FILE_ISPRITE_ITEMTILE, 142224, 0x00F3 );
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_ITEMTILE").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New31ItemTile.ispk" );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New46ItemTile.ispk" );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New50ItemTile.ispk" );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New51ItemTile.ispk" );
	
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 10 ItemDrop Patch
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
//	pPatch->SetOriginalInfo( FILE_ISPRITE_ITEMDROP, 579872, 0x03CC );
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_ITEMDROP").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New31ItemDrop.ispk" );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New46ItemDrop.ispk" );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New50ItemDrop.ispk" );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New51ItemDrop.ispk" );


	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 11 ItemDescription Patch
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
//	pPatch->SetOriginalInfo( FILE_SPRITE_ITEM_DESCRIPTION, 6521842, 0x0104 );
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_ITEM_DESCRIPTION").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New31ItemDescription.spk" );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New46ItemDescription.spk" );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New50ItemDescription.spk" );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New51ItemDescription.spk" );
	
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 12 Minimap Patch
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
//	pPatch->SetOriginalInfo( FILE_SPRITE_MINIMAP, 6521842, 0x0104 );
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_MINIMAP").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New31Minimap.spk" );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New51Minimap.spk" );
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 13 SkillIcon Patch
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_SKILLICON").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New31SkillIcon.spk" );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New51SkillIcon.spk" );
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 14 SkillMini Patch
	//-----------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_SKILLMINI").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New31SkillMini.spk" );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New51SkillMini.spk" );
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 15 Addon ispk
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_ADDON").c_str(), ORIGINAL_DIR );
//	APPEND_PATCH( "Data\\ChinaAppendPatch\\New79Addon.ispk");
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 16 Addon sspk
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_ADDON").c_str(), ORIGINAL_DIR );
//	APPEND_PATCH( "Data\\ChinaAppendPatch\\New79Addon.sspk");
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 17 Ousters ispk
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_OUSTERS").c_str(), ORIGINAL_DIR );
//	APPEND_PATCH( "Data\\ChinaAppendPatch\\New71Ousters.ispk");
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 18 Ousters sspk
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_OUSTERS").c_str(), ORIGINAL_DIR );
//	APPEND_PATCH( "Data\\ChinaAppendPatch\\New71Ousters.sspk");
	CHECK_FINAL_FILE;

	//------------------------------------------------------------------------------
	// 19 NPC face spk
	//------------------------------------------------------------------------------
	pPatch = &apt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_NPCFACE").c_str(), ORIGINAL_DIR );
	APPEND_PATCH( "Data\\ChinaAppendPatch\\New31NpcFace.spk" );
	CHECK_FINAL_FILE;

#endif







//	int allSize = apt.GetAllSize();

	
	//-----------------------------------------------------------------------------
	// Save
	//-----------------------------------------------------------------------------
	std::ofstream fileAppendInfo2(g_pFileDef->getProperty("FILE_INFO_APPENDPATCH").c_str(), std::ios::binary);
	apt.SaveToFile( fileAppendInfo2 );
	fileAppendInfo2.close();

	//-----------------------------------------------------------------------------
	// Load
	//-----------------------------------------------------------------------------
	ivfstream	fileAppendInfo;
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_INFO_APPENDPATCH").c_str(), fileAppendInfo))
		return false;
	apt.LoadFromFile( fileAppendInfo );
	fileAppendInfo.close();

/*


// 넷마블용
#ifdef __MAKE_NETMARBLE_INFO__
	index = 0;
	netmarbleApt.Init( 20 );	

	//-----------------------------------------------------------------------------
	// 0 Effect.aspk
	//-----------------------------------------------------------------------------
	pPatch = &netmarbleApt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ASPRITE_ALPHAEFFECT").c_str(), NETMARBLE_ORIGINAL_DIR );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15Effect.aspk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New17Effect.aspk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New19Effect.aspk" );
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 1 EffectScreen.spk
	//-----------------------------------------------------------------------------
	pPatch = &netmarbleApt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_SCREENEFFECT").c_str(), NETMARBLE_ORIGINAL_DIR );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15EffectScreen.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New17EffectScreen.spk" );
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 2 Effect.spk
	//-----------------------------------------------------------------------------
	pPatch = &netmarbleApt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_NORMALEFFECT").c_str(), NETMARBLE_ORIGINAL_DIR );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New6Effect.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7Effect.spk" );
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 3 SkillIcon Patch
	//-----------------------------------------------------------------------------
	pPatch = &netmarbleApt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_SKILLICON").c_str(), NETMARBLE_ORIGINAL_DIR );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New3SkillIcon.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New6SkillIcon.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7SkillIcon.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New13SkillIcon.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15SkillIcon.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New17SkillIcon.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New19SkillIcon.spk" );
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 4 SkillMini Patch
	//-----------------------------------------------------------------------------
	pPatch = &netmarbleApt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_SKILLMINI").c_str(), NETMARBLE_ORIGINAL_DIR );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New3SkillMini.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New6SkillMini.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7SkillMini.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New13SkillMini.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15SkillMini.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New17SkillMini.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New19SkillMini.spk");
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 5 Item Patch
	//-----------------------------------------------------------------------------
	pPatch = &netmarbleApt[index++];
//	pPatch->SetOriginalInfo( "Data\\UI\\Spk\\Item.ispk", 441166, 0x00F7 );
	SET_ORIGINAL_INFO( pPatch, "Data\\UI\\Spk\\Item.ispk", NETMARBLE_ORIGINAL_DIR );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New5Item.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New6Item.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7Item.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New10Item.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New13Item.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15Item.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New17Item.ispk" );
	
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 6 ItemTile Patch
	//-----------------------------------------------------------------------------
	pPatch = &netmarbleApt[index++];
//	pPatch->SetOriginalInfo( g_pFileDef->getProperty("FILE_ISPRITE_ITEMTILE").c_str(), 142224, 0x00F3 );
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_ITEMTILE").c_str(), NETMARBLE_ORIGINAL_DIR );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New5ItemTile.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New6ItemTile.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7ItemTile.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New10ItemTile.ispk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New13ItemTile.ispk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15ItemTile.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New17ItemTile.ispk" );
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 7 ItemDrop Patch
	//-----------------------------------------------------------------------------
	pPatch = &netmarbleApt[index++];
//	pPatch->SetOriginalInfo( g_pFileDef->getProperty("FILE_ISPRITE_ITEMDROP").c_str(), 579872, 0x03CC );
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_ITEMDROP").c_str(), NETMARBLE_ORIGINAL_DIR );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New5ItemDrop.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New6ItemDrop.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7ItemDrop.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New10ItemDrop.ispk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New13ItemDrop.ispk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15ItemDrop.ispk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New17ItemDrop.ispk" );	
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 8 ItemDescription Patch
	//-----------------------------------------------------------------------------
	pPatch = &netmarbleApt[index++];
//	pPatch->SetOriginalInfo( g_pFileDef->getProperty("FILE_SPRITE_ITEM_DESCRIPTION").c_str(), 6521842, 0x0104 );
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_ITEM_DESCRIPTION").c_str(), NETMARBLE_ORIGINAL_DIR );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New5ItemDescription.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New6ItemDescription.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7ItemDescription.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New10ItemDescription.spk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New13ItemDescription.spk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15ItemDescription.spk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New17ItemDescription.spk" );	
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 9 Creature.ispk
	//-----------------------------------------------------------------------------
	pPatch = &netmarbleApt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_CREATURE").c_str(), NETMARBLE_ORIGINAL_DIR );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New5Creature.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New6Creature.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7Creature.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New9Creature.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New10Creature.ispk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New13Creature.ispk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15Creature.ispk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New17Creature.ispk" );	
	CHECK_FINAL_FILE;


	//-----------------------------------------------------------------------------
	// 10 Creature.sspk
	//-----------------------------------------------------------------------------
	pPatch = &netmarbleApt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_CREATURE").c_str(), NETMARBLE_ORIGINAL_DIR );
//	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New5Creature.sspk" );
//	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New6Creature.sspk" );
//	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7Creature.sspk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New9Creature.sspk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New10Creature.sspk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New13Creature.sspk" );	
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15Creature.sspk" );	
	
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 11 Minimap Patch
	//-----------------------------------------------------------------------------
	pPatch = &netmarbleApt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_MINIMAP").c_str(), NETMARBLE_ORIGINAL_DIR );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New5Minimap.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New6Minimap.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7Minimap.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New9Minimap.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New13Minimap.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15Minimap.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New19Minimap.spk" );
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 12 Addon
	//-----------------------------------------------------------------------------
	pPatch = &netmarbleApt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_ISPRITE_ADDON").c_str(), NETMARBLE_ORIGINAL_DIR );
//	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7Addon.ispk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New9Addon.ispk" );
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 13 Addon
	//-----------------------------------------------------------------------------
	pPatch = &netmarbleApt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_ADDON").c_str(), NETMARBLE_ORIGINAL_DIR );
//	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7Addon.sspk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New9Addon.sspk" );
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 14 TeamVampire
	//-----------------------------------------------------------------------------
	pPatch = &netmarbleApt[index++];
	SET_ORIGINAL_INFO( pPatch, "Data\\UI\\SPK\\TeamVampire.spk" , NETMARBLE_ORIGINAL_DIR );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7TeamVampire.spk" );
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 15 InfoVampire
	//-----------------------------------------------------------------------------
	pPatch = &netmarbleApt[index++];
	SET_ORIGINAL_INFO( pPatch, "Data\\ui\\spk\\TeamSlayer.spk", NETMARBLE_ORIGINAL_DIR );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7TeamSlayer.spk" );
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 16 NPCFace
	//-----------------------------------------------------------------------------
	pPatch = &netmarbleApt[index++];
	SET_ORIGINAL_INFO( pPatch, "Data\\ui\\spk\\NPCFACE.spk", NETMARBLE_ORIGINAL_DIR );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7NpcFace.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New10NpcFace.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New13NpcFace.spk" );
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 17 Tile
	//-----------------------------------------------------------------------------
	pPatch = &netmarbleApt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_TILE").c_str(), NETMARBLE_ORIGINAL_DIR );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7Tile.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15Tile.spk" );
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 18 ImageObject
	//-----------------------------------------------------------------------------
	pPatch = &netmarbleApt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SPRITE_IMAGEOBJECT").c_str(), NETMARBLE_ORIGINAL_DIR );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7ImageObject.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New9ImageObject.spk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15ImageObject.spk" );
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// 19 ImageObject
	//-----------------------------------------------------------------------------
	pPatch = &netmarbleApt[index++];
	SET_ORIGINAL_INFO( pPatch, g_pFileDef->getProperty("FILE_SSPRITE_IMAGEOBJECT").c_str(), NETMARBLE_ORIGINAL_DIR );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New7ImageObject.sspk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New9ImageObject.sspk" );
	APPEND_PATCH( "Data\\NetmarbleAppendPatch\\New15ImageObject.sspk" );
	CHECK_FINAL_FILE;

	//-----------------------------------------------------------------------------
	// Save
	//-----------------------------------------------------------------------------
	std::ofstream netmarblefileAppendInfo2(g_pFileDef->getProperty("FILE_INFO_APPENDPATCH").c_str(), ios::binary);
	netmarbleApt.SaveToFile( netmarblefileAppendInfo2 );
	netmarblefileAppendInfo2.close();

	//-----------------------------------------------------------------------------
	// Load
	//-----------------------------------------------------------------------------
	std::ifstream	netmarblefileAppendInfo;
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_INFO_APPENDPATCH").c_str(), netmarblefileAppendInfo))
		return false;
	netmarbleApt.LoadFromFile( netmarblefileAppendInfo );
	netmarblefileAppendInfo.close();
#endif
*/
	return true;
}





















