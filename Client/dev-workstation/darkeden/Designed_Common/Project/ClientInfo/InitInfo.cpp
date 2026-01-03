//---------------------------------------------------------------------------
// GameInitInfo.cpp
//---------------------------------------------------------------------------
// Information Table에 대한 초기화를 한다.
//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Include files
//-----------------------------------------------------------------------------
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
#include "MMinMaxInfo.h"
#include "packet/Properties.h"
#include "MItem.h"

#include "Packet\types\PacketItemDef.h"
#include "MathTable.h"

#include "MGpsTable.h"

//#ifdef OUTPUT_DEBUG
	#define SAVE_TO_FILE
	//#define SAVE_POWER_JJANG_INFO // 자주 바뀌지 않는다
//#endif

//#ifdef OUTPUT_DEBUG
	#define SAVE_TO_CSV_FILE
//#endif

#if __CONTENTS(__ITEMINFO_TABLEATION_PROJECT)
	#define LOAD_TO_CSV_FILE
#endif //__ITEMINFO_TABLEATION_PROJECT

DWORD		g_CurrentFrame;
#if __CONTENTS(__GPS_ADD)
	MGPS_INFO	*g_pGpsInfoTable = NULL;
#endif //__GPS_ADD

#define		FILE_INFO_SERVER_RANK_BONUS	"Data\\ServerRankBonus.inf"
#define		FILE_INFO_SERVER_ITEM		"Data\\ServerItemInfo.inf"
#define		FILE_INFO_SERVER_NPC		"Data\\ServerNPC.inf"

#define		FILE_INFO_CHAT_CURSE		"Data\\yok.txt"
#define		FILE_INFO_CHAT_CURSE_2		"Data\\yok2.txt"// 캐릭터 이름에서만 필터링 될 것들

#define		FILE_INFO_CHAT_CURSE_NET		"Data\\yok_net.txt"
#define		FILE_INFO_CHAT_CURSE_NET_2		"Data\\yok2_net.txt"

#define		COLOR_CHIEF_MAGE			44
#define		COLOR_CHIEF_FIGHT			120
#define		COLOR_CHIEF_MAGE_FIGHT		485


HRESULT InitFail(LPCTSTR szError,...);
bool 
FileOpenBinary(const char* filename, ivfstream& file);
//---------------------------------------------------------------------------
// Open File
//---------------------------------------------------------------------------
bool 
FileCheck(const char* filename);
BOOL	InitActionInfoTable(
	CCreatureFramePack	&AddonManFPK,	CCreatureFramePack	&AddonWomanFPK,
	CCreatureFramePack	&CreatureFPK,	CCreatureFramePack	&OustersFPK,
	int *FrameSize);
BOOL	InitEffectStatusTable();
BOOL	InitZoneInfo();
BOOL	InitSoundTable();
BOOL	InitCreatureSpriteTable();
BOOL	InitCreatureTable();
void	InitEffectLight(CEffectFramePack& ScreenEFPK,CEffectFramePack& EFPK);


//-----------------------------------------------------------------------------
// Limit Light
//-----------------------------------------------------------------------------
// 일부 effect는 밝기 filter 크기가 너무 커서 제한한다.
//-----------------------------------------------------------------------------
void
LimitLight( CEffectFramePack& EFPK, int limit )
{
	for (int e=0; e<EFPK.GetSize(); e++)
	{
		DIRECTION_EFFECTFRAME_ARRAY& DEA = EFPK[e];

		for (int d=0; d<DEA.GetSize(); d++)
		{
			EFFECTFRAME_ARRAY& EA = DEA[d];

			for (int f=0; f<EA.GetSize(); f++)
			{
				CEffectFrame& frame = EA[f];

				TYPE_SPRITEID spriteID = frame.GetSpriteID();
				short cx = frame.GetCX();
				short cy = frame.GetCY();
				int newLight = min( frame.GetLight(), limit );	// limit 제한
				bool back = frame.IsBackground();

				frame.Set( spriteID, cx, cy, newLight, back );
			}
		}
	}
}

//-----------------------------------------------------------------------------
// Init Object
//-----------------------------------------------------------------------------
void
InitObject()
{
	if(g_pFileDef == NULL)
	{
		g_pFileDef = new Properties;
		g_pFileDef->load(FILE_INFO_FILEDEF);
	}

	if (g_pClientConfig==NULL)
	{
		g_pClientConfig = new ClientConfig;
	}

//	if (g_pUserOption==NULL)
//	{
//		g_pUserOption = new UserOption;
//	}

	if (g_pGameStringTable==NULL)
	{
		g_pGameStringTable = new MStringArray;
	}

	if (g_pSoundTable==NULL)
	{
		g_pSoundTable = new SOUND_TABLE;
	}

	if (g_pMusicTable==NULL)
	{
		g_pMusicTable = new MUSIC_TABLE;
	}

	if (g_pZoneTable==NULL)
	{
		g_pZoneTable = new CZoneTable;
	}

	if (g_pItemTable==NULL)
	{
		g_pItemTable = new ITEMCLASS_TABLE;
	}	

	if (g_pRankBonusTable==NULL)
	{
		g_pRankBonusTable = new RankBonusTable;
	}	

	if (g_pItemOptionTable==NULL)
	{
		g_pItemOptionTable = new ITEMOPTION_TABLE;
	}

	if (g_pInteractionObjectTable==NULL)
	{
		g_pInteractionObjectTable = new INTERACTIONOBJECT_TABLE;
	}

	if (g_pCreatureSpriteTable==NULL)
	{
		g_pCreatureSpriteTable = new CREATURESPRITE_TABLE;
	}

//	if (g_pCreatureActionSpriteTable==NULL)
//	{
//		g_pCreatureActionSpriteTable = new CREATURESPRITE_TABLE;
//	}

//	if (g_pAddonSpriteTable==NULL)
//	{
//		g_pAddonSpriteTable = new CREATURESPRITE_TABLE;
//	}
//
	if (g_pCreatureTable==NULL)
	{
		g_pCreatureTable = new CREATURE_TABLE;
	}

	if (g_pCreatureSpriteTypeMapper==NULL)
	{
		g_pCreatureSpriteTypeMapper = new CreatureSpriteTypeMapper;
	}

	if (g_pShopTemplateTable==NULL)
	{
		g_pShopTemplateTable = new MShopTemplateTable;
	}

	if (g_pNPCTable==NULL)
	{
		g_pNPCTable = new MNPCTable;
	}

	if (g_pEffectSpriteTypeTable==NULL)
	{
		g_pEffectSpriteTypeTable = new EFFECTSPRITETYPE_TABLE;
	}

	if (g_pActionEffectSpriteTypeTable==NULL)
	{
		g_pActionEffectSpriteTypeTable = new MActionEffectSpriteTypeTable;
	}

	if (g_pEffectStatusTable==NULL)
	{
		g_pEffectStatusTable = new EFFECTSTATUS_TABLE;
	}

	
	if (g_pActionInfoTable==NULL)
	{
		g_pActionInfoTable = new MActionInfoTable;
	}

	if (g_pChatManager==NULL)
	{
		g_pChatManager = new MChatManager;
	}

	if (g_pLevelNameTable==NULL)
	{
		g_pLevelNameTable = new MLevelNameTable;
	}
}


//-----------------------------------------------------------------------------
// Release Object
//-----------------------------------------------------------------------------
void
ReleaseObject()
{
	if (g_pActionInfoTable!=NULL)
	{
		delete g_pActionInfoTable;
		g_pActionInfoTable = NULL;
	}

	if(g_pFileDef != NULL)
	{
		delete g_pFileDef;
		g_pFileDef = NULL;
	}
	
	if (g_pClientConfig!=NULL)
	{
		delete g_pClientConfig;
		g_pClientConfig = NULL;
	}

//	if (g_pUserOption!=NULL)
//	{
//		delete g_pUserOption;
//		g_pUserOption = NULL;
//	}

	if (g_pGameStringTable!=NULL)
	{
		delete g_pGameStringTable;
		g_pGameStringTable = NULL;
	}

	if (g_pSoundTable!=NULL)
	{
		delete g_pSoundTable;
		g_pSoundTable = NULL;
	}

	if (g_pMusicTable!=NULL)
	{
		delete g_pMusicTable;
		g_pMusicTable = NULL;
	}

	if (g_pZoneTable!=NULL)
	{
		delete g_pZoneTable;
		g_pZoneTable = NULL;
	}

	if (g_pRankBonusTable!=NULL)
	{
		delete g_pRankBonusTable;
		g_pRankBonusTable = NULL;
	}	

	if (g_pItemTable!=NULL)
	{
		delete g_pItemTable;
		g_pItemTable = NULL;
	}	

	if (g_pItemOptionTable!=NULL)
	{
		delete g_pItemOptionTable;
		g_pItemOptionTable = NULL;
	}

	if (g_pInteractionObjectTable!=NULL)
	{
		delete g_pInteractionObjectTable;
		g_pInteractionObjectTable = NULL;
	}

	if (g_pCreatureSpriteTable!=NULL)
	{
		delete g_pCreatureSpriteTable;
		g_pCreatureSpriteTable = NULL;
	}

//	if (g_pCreatureActionSpriteTable!=NULL)
//	{
//		delete g_pCreatureActionSpriteTable;
//		g_pCreatureActionSpriteTable = NULL;
//	}

//	if (g_pAddonSpriteTable!=NULL)
//	{
//		delete g_pAddonSpriteTable;
//		g_pAddonSpriteTable = NULL;
//	}
//
	if (g_pCreatureTable!=NULL)
	{
		delete g_pCreatureTable;
		g_pCreatureTable = NULL;
	}

	if (g_pCreatureSpriteTypeMapper!=NULL)
	{
		delete g_pCreatureSpriteTypeMapper;
		g_pCreatureSpriteTypeMapper = NULL;
	}	

	if (g_pShopTemplateTable!=NULL)
	{
		delete g_pShopTemplateTable;
		g_pShopTemplateTable = NULL;
	}

	if (g_pNPCTable!=NULL)
	{
		delete g_pNPCTable;
		g_pNPCTable = NULL;
	}

	if (g_pEffectSpriteTypeTable!=NULL)
	{
		delete g_pEffectSpriteTypeTable;
		g_pEffectSpriteTypeTable = NULL;
	}

	if (g_pActionEffectSpriteTypeTable)
	{
		delete g_pActionEffectSpriteTypeTable;
		g_pActionEffectSpriteTypeTable = NULL;
	}

	if (g_pEffectStatusTable!=NULL)
	{
		delete g_pEffectStatusTable;
		g_pEffectStatusTable = NULL;
	}

	if (g_pSkillInfoTable!=NULL)
	{
		delete g_pSkillInfoTable;
		g_pSkillInfoTable = NULL;
	}

#if __CONTENTS(__GPS_ADD)	// MGPS_INFO
	if (g_pGpsInfoTable!=NULL)
	{
		delete g_pGpsInfoTable;
		g_pGpsInfoTable = NULL;
	}
#endif	// MGPS_INFO
	
	if (g_pChatManager!=NULL)
	{
		delete g_pChatManager;
		g_pChatManager = NULL;
	}

	if (g_pLevelNameTable!=NULL)
	{
		delete g_pLevelNameTable;
		g_pLevelNameTable = NULL;
	}
}

//-----------------------------------------------------------------------------
// Init Config
//-----------------------------------------------------------------------------
BOOL
InitClientConfig()
{
	// Debug Message
	#ifdef	OUTPUT_DEBUG
		if (g_pDebugMessage!=NULL)
			g_pDebugMessage->Add("[ InitGame ]  ClientConfig");
	#endif

	//---------------------------------------------------------------------
	//
	//			Client Config 설정
	//
	//---------------------------------------------------------------------
	///*
	#ifdef SAVE_TO_FILE
		//--------------------------------------------------------------
		// FPS - 적용은 안된다.
		//--------------------------------------------------------------
		g_pClientConfig->FPS						= 16;

		// ScreenShot의 개수
		g_pClientConfig->MAX_SCREENSHOT			= 100;

		// 죽고 나서 다시 살아나는데까지의 delay시간 10초
		g_pClientConfig->DELAY_PLAYER_DEAD		= 10 * 1000;	
		
		// client에서 움직일 수 있는 sector수
		g_pClientConfig->MAX_CLIENT_MOVE			= 6;//3;

		// client에서 움직일 수 있는 sector수
		g_pClientConfig->MAX_CREATURE_MOVE_BUFFER	= 2;
		
		// 화면의 최대 Light개수
		g_pClientConfig->MAX_LIGHT_DRAW			= 50;

		// Load하는 Sound 개수
		g_pClientConfig->MAX_SOUNDPART			= 100;

		//--------------------------------------------------------------
		// 한번에 udpate하는 최대 회수
		//--------------------------------------------------------------
		// 한번에 최대 6 Frame의 의미는
		// 6 Frame마다 적어도 한번은 그려준다는 의미가 된다.
		//--------------------------------------------------------------
		g_pClientConfig->MAX_UPDATE_ONETIME		= 6;

		//--------------------------------------------------------------
		// '한번에 update하는 최대 회수'를 수행하는 회수.. - -;;
		//--------------------------------------------------------------
		// 이렇게 하면..
		// 한번에 최대 6 Frame씩, 최대 "10"회니까..
		// 60 Frame동안 표현될 것이.. 순간적~~으로 표현되게 된다.
		// 10 Frame만 보이겠찌.. 
		//--------------------------------------------------------------
		g_pClientConfig->MAX_UPDATE_ONETIME_COUNT		= 10;		

		g_pClientConfig->DELAY_GLOBAL_SAY				= 12*1000;	// 12초

		//--------------------------------------------------------------
		// message scroll delay시간
		//--------------------------------------------------------------
		g_pClientConfig->DELAY_SYSTEMMESSAGE		= 5000;
		g_pClientConfig->DELAY_GAMEMESSAGE		= 5000;

		//--------------------------------------------------------------
		// 화면에 출력되는 item이름 개수
		//--------------------------------------------------------------
		g_pClientConfig->MAX_DRAWITEMNAME			= 20;

		//--------------------------------------------------------------
		// packet기다리는 시간
		//--------------------------------------------------------------
		g_pClientConfig->MAX_WAIT_PACKET			= 15000;	// 15초

		//--------------------------------------------------------------
		// 한 loop에 처리되는 packet의 최대 수
		//--------------------------------------------------------------
		g_pClientConfig->MAX_PROCESS_PACKET			= 11;		// 11개 처리

		//--------------------------------------------------------------
		// 초기화면의 음악
		//--------------------------------------------------------------
		g_pClientConfig->MUSIC_THEME				= MUSIC_ADVANCE ; //MUSIC_PAY_BACK;

		//--------------------------------------------------------------
		// 채팅 String 줄 수
		//--------------------------------------------------------------
		g_pClientConfig->MAX_CHATSTRING				= 5;
		g_pClientConfig->MAX_CHATSTRING_MINUS_1		= 4;
		g_pClientConfig->MAX_CHATSTRING_LENGTH		= 20;
		g_pClientConfig->MAX_CHATSTRINGLENGTH_PLUS1	= 21;

		//--------------------------------------------------------------
		// 채팅 유지 시간
		//--------------------------------------------------------------
		g_pClientConfig->DELAY_CHATSTRING_KEEP		= 1500;		// 흰색의 지속 시간
		g_pClientConfig->DELAY_CHATSTRING_FADE		= 250;		// 어두워지는 단계의 시간
		g_pClientConfig->VALUE_CHATSTRING_FADE		= 8;		// 어두워지는 값
		g_pClientConfig->MIN_CHATSTRING_COLOR256		= 96;		// 가장 어두운 채팅 String색
		
		//--------------------------------------------------------
		// TexturePart Manager의 Part 개수
		//--------------------------------------------------------
		g_pClientConfig->MAX_TEXTUREPART_EFFECT				= 25;
		g_pClientConfig->MAX_TEXTUREPART_CREATURESHADOW		= 100;
		g_pClientConfig->MAX_TEXTUREPART_IMAGEOBJECTSHADOW	= 100;
		g_pClientConfig->MAX_TEXTUREPART_ADDON_SHADOW			= 200;
		g_pClientConfig->MAX_TEXTUREPART_IMAGEOBJECTSPK		= 20;

		//--------------------------------------------------------
		// Font 크기
		//--------------------------------------------------------
		g_pClientConfig->FONT_HEIGHT				= 20;
		g_pClientConfig->FONT_ITEM_HEIGHT			= 15;

		//--------------------------------------------------------
		// HP Bar
		//--------------------------------------------------------
		g_pClientConfig->MAX_HP_BAR_PIXEL			= 120;		// hp bar의 크기
		g_pClientConfig->POSITION_HP_BAR			= -10;		// 이름의 위치(hp bar 위치)

		//--------------------------------------------------------
		// 아이템 부서지는거에 따른 색깔 표시
		//--------------------------------------------------------
		g_pClientConfig->PERCENTAGE_ITEM_SOMEWHAT_BROKEN	= 25;		// 25%남았을때 오렌지색
		g_pClientConfig->PERCENTAGE_ITEM_ALMOST_BROKEN		= 10;		// 10%남았을때 빨간색

		//--------------------------------------------------------------
		// Effect붙어서 캐릭터 색깔 바뀔때 가끔씩 원래 모습 보여주는 frame
		//--------------------------------------------------------------
		g_pClientConfig->FRAME_DRAW_ORIGINAL_SPRITE			= 8;		// 4frame마다 한번씩

		//--------------------------------------------------------
		// 색깔 - 5:6:5를 저장해야 한다.
		//--------------------------------------------------------
		g_pClientConfig->COLOR_OUTLINE_INTERACTIONOBJECT	= (0 << 11) | (31 << 6) | 0;	// GREEN

		// item
		g_pClientConfig->COLOR_NAME_ITEM					= RGB(31<<3, 31<<3, 31<<3);	// WHITE
		g_pClientConfig->COLOR_NAME_ITEM_OPTION			= RGB(31<<3, 31<<3, 5<<3);	// 거의 blue
		g_pClientConfig->COLOR_NAME_ITEM_RARE_OPTION	= RGB(19<<3, 19<<3, 31<<3);	// 거의 blue
		g_pClientConfig->COLOR_OUTLINE_ITEM				= (23 << 11) | (23 << 6) | 23;

		// 종족별
		g_pClientConfig->COLOR_NAME_VAMPIRE				= RGB(31<<3, 10<<3, 10<<3);	// RED
		g_pClientConfig->COLOR_NAME_SLAYER				= RGB(23<<3, 23<<3, 31<<3);	// BLUE
		g_pClientConfig->COLOR_NAME_NPC					= RGB(5<<3, 27<<3, 5<<3);	// GREEN

		// 공격 가능?
		g_pClientConfig->COLOR_OUTLINE_NPC				= (5 << 11) | (23 << 6) | 5;
		g_pClientConfig->COLOR_OUTLINE_ATTACK_POSSIBLE	= (23 << 11) | (5 << 6) | 5;
		g_pClientConfig->COLOR_OUTLINE_ATTACK_IMPOSSIBLE	= (5 << 11) | (5 << 6) | 18;

		// hp bar
		g_pClientConfig->COLOR_HP_BAR_R					= 15;
		g_pClientConfig->COLOR_HP_BAR_G					= 16;
		g_pClientConfig->COLOR_HP_BAR_B					= 15;

		//---------------------------------------------------------------------
		// 새 사용자 등록 모드
		//---------------------------------------------------------------------
		//	NUR_CLIENT,				// 새 사용자 등록 가능
		//	NUR_HOMEPAGE,			// 홈페이지를 띄워주면서 등록
		//	NUR_MESSAGE_HOMEPAGE,	// 홈페이지에서 등록하라는 message
		//	NUR_DENY				// 새 사용자 등록 불가			
//		g_pClientConfig->NEW_USER_REGISTERATION_MODE	= ClientConfig::NUR_HOMEPAGE;

//		g_pClientConfig->URL_HOMEPAGE					= "http://www.t2cn.com";				// 홈페이지 main
//		g_pClientConfig->URL_HOMEPAGE_NEW_USER			= "http://member.t2cn.com/reg";		// 새 사용자 등록 URL
//		g_pClientConfig->URL_HOMEPAGE_BILING				= "http://pay.t2cn.com";
		g_pClientConfig->URL_HOMEPAGE					= "http://kr.darkeden.com";				// 홈페이지 main
		//g_pClientConfig->URL_HOMEPAGE_NEW_USER			= "http://www.darkeden.com/htdocs2/homepage/Registration/html/new_reg.html";		// 새 사용자 등록 URL
		g_pClientConfig->URL_HOMEPAGE_NEW_USER			= "http://www.darkeden.com/pg/new_reg.html";		// 새 사용자 등록 URL
		g_pClientConfig->URL_HOMEPAGE_BILING				= "http://www.darkeden.com/pg/buy_index.html";
#if __CONTENTS(__ID_PASSWORD)
		g_pClientConfig->URL_HOMEPAGE_NEW_USER = "http://www.joymax.com/darkeden/Darkeden_Front.jmx?workURL=http://darkedencp.joymax.com/notarget/agreement/agreement.asp";
#endif	//__ID_PASSWORD
#if __CONTENTS(__JAPAN_UI)
		g_pClientConfig->URL_HOMEPAGE_NEW_USER_NETMARBLE	= "http://www.netmarble.jp/";
#endif //__JAPAN_UI
#if __CONTENTS(__IMI_INTERFACE)
		g_pClientConfig->URL_HOMEPAGE_NEW_USER = "http://dark.gamemania.co.kr";
#endif //__IMI_INTERFACE
		//--------------------------------------------------------
		// 피 흘리기
		//--------------------------------------------------------
		g_pClientConfig->BLOOD_DROP_HP_PERCENT		= 30;		// 피 흘리기 시작하는 HP %
		g_pClientConfig->BLOOD_DROP_GAP_TIME			= 3000;		// 다음에 피 흘리기 시작하는 시간 gap
		g_pClientConfig->BLOOD_DROP_RANDOM_TIME		= 3000;		// 피 흘리는 시간 = GAP + RANDOM

		g_pClientConfig->REPEAT_TIME				= 10*60*1000;				// 자동공격 제한시간 10분
		g_pClientConfig->LOCK_TIME				= 10*60*1000;				// Caps Lock자동공격 제한시간 10분

		//---------------------------------------------------------------------
		// Save
		//---------------------------------------------------------------------
		g_pClientConfig->SaveToFile(g_pFileDef->getProperty("FILE_INFO_CLIENTCONFIG").c_str());
	#endif
	//*/
	//---------------------------------------------------------------------
	// Load
	//---------------------------------------------------------------------
	if (!g_pClientConfig->LoadFromFile(g_pFileDef->getProperty("FILE_INFO_CLIENTCONFIG").c_str()))
	{
		#ifdef OUTPUT_DEBUG
			if (g_pDebugMessage!=NULL)
					g_pDebugMessage->AddFormat("[Error] File Open Error : [%s]", FILE_INFO_CLIENTCONFIG);
		#endif
		InitFail("[Error] File Open Error : [%s]", g_pFileDef->getProperty("FILE_INFO_CLIENTCONFIG").c_str());
		
		return FALSE;
	}

	return TRUE;
}

//-----------------------------------------------------------------------------
// Init Infomation
//-----------------------------------------------------------------------------
BOOL		
InitInformation()
{
	// Debug Message
	#ifdef	OUTPUT_DEBUG
		if (g_pDebugMessage!=NULL)
				g_pDebugMessage->Add("[ InitGame ]  Information");
	#endif

	//---------------------------------------------------------------------
	//
	//			Chat Manager
	//
	//---------------------------------------------------------------------
	// 욕 읽기..
	// 욕읽기를 위해서 userinformation을 추가한다.
	if (g_pUserInformation==NULL)
		g_pUserInformation = new UserInformation;	

	Properties NetmarbleConfig;
	
	try
	{
		NetmarbleConfig.load(g_pFileDef->getProperty("FILE_INFO_NETMARBLE").c_str());			
		g_pUserInformation->IsNetmarble = NetmarbleConfig.getPropertyInt("Netmarble") != 0;
	}
	catch (...)	// 파일이 없거나 뭔가 이상이 있다.
	{
		g_pUserInformation->IsNetmarble = false;
	}

	if(g_pUserInformation->IsNetmarble)
	{
		g_pChatManager->LoadFromFileCurse( FILE_INFO_CHAT_CURSE_NET );
		g_pChatManager->SaveToFile( g_pFileDef->getProperty("FILE_INFO_CHAT").c_str());
		
		g_pChatManager->LoadFromFileCurse( FILE_INFO_CHAT_CURSE_NET_2 );
		g_pChatManager->SaveToFile( g_pFileDef->getProperty("FILE_INFO_CHAT_2").c_str());
	}
	else
	{
		g_pChatManager->LoadFromFileCurse( FILE_INFO_CHAT_CURSE );
		g_pChatManager->SaveToFile( g_pFileDef->getProperty("FILE_INFO_CHAT").c_str());
		
		g_pChatManager->LoadFromFileCurse( FILE_INFO_CHAT_CURSE_2 );
		g_pChatManager->SaveToFile( g_pFileDef->getProperty("FILE_INFO_CHAT_2").c_str());
	}


	//---------------------------------------------------------------------
	//
	//				Effect FramePack
	//
	//---------------------------------------------------------------------
	// Darkness는 빛을 0으로.
	// Light는 빛을 더 크게..
	ivfstream efpkFile;//(FILE_CFRAME_ADDON_MALE, ios::binary);
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_EFRAME_ALPHAEFFECT").c_str(), efpkFile))
		return false;

	CEffectFramePack		EFPK;
	EFPK.LoadFromFile(efpkFile);
	efpkFile.close();

	CEffectFramePack NormalEFPK;
	ivfstream efpkFile2(g_pFileDef->getProperty("FILE_EFRAME_NORMALEFFECT").c_str(), std::ios::binary);
	NormalEFPK.LoadFromFile( efpkFile2 );
	efpkFile2.close();

	CEffectFramePack ScreenEFPK;
	ivfstream efpkFile3(g_pFileDef->getProperty("FILE_EFRAME_SCREENEFFECT").c_str(), std::ios::binary);
	ScreenEFPK.LoadFromFile( efpkFile3 );
	efpkFile3.close();

	CEffectFramePack ShadowEFPK;
	ivfstream efpkFile4(g_pFileDef->getProperty("FILE_EFRAME_SHADOWEFFECT").c_str(), std::ios::binary);
	ShadowEFPK.LoadFromFile( efpkFile4 );
	efpkFile4.close();

	//---------------------------------------------------------------------
	// Effect 밝기 제한
	//---------------------------------------------------------------------
	LimitLight( EFPK, 5 );
	LimitLight( NormalEFPK, 5 );
	LimitLight( ScreenEFPK, 5 );
	LimitLight( ShadowEFPK, 5 );


	//---------------------------------------------------------------------
	//
	//      EffectSpriteTypeTable 정보 생성
	//
	//---------------------------------------------------------------------
	//*
#ifdef SAVE_TO_FILE
	(*g_pEffectSpriteTypeTable).Init( MAX_EFFECTSPRITETYPE );
	

	int sid = 0;


	int FrameSize[MAX_EFFECTSPRITETYPE];

	//------------------------------------------------
	// Alpha Effect
	//------------------------------------------------
	for (int st=0; st<MAX_EFFECTSPRITETYPE_ALPHAEFFECT; st++)
	{
		(*g_pEffectSpriteTypeTable)[st].BltType		= BLT_EFFECT;
		(*g_pEffectSpriteTypeTable)[st].FrameID		= sid;
		(*g_pEffectSpriteTypeTable)[st].RepeatFrame	= false;
		(*g_pEffectSpriteTypeTable)[st].ActionEffectFrameID = FRAMEID_NULL;
		//(*g_pEffectSpriteTypeTable)[st].PairFrameID = FRAMEID_NULL;
		(*g_pEffectSpriteTypeTable)[st].FemaleEffectSpriteType = EFFECTSPRITETYPE_NULL;		

		FrameSize[st] = EFPK[sid][DIRECTION_LEFT].GetSize();

		/*
		if (st==EFFECTSPRITETYPE_SWORD_WAVE_1 ||
			st==EFFECTSPRITETYPE_SWORD_WAVE_2)
		{
			// frame이 따로 없는 것들..
			int a =0;
		}
		else
		{
		*/
			sid++;
		//}

	}

	sid = 0;

	//------------------------------------------------
	// Screen Effect
	//------------------------------------------------
	for (st=MAX_EFFECTSPRITETYPE_ALPHAEFFECT; st<MAX_EFFECTSPRITETYPE_SCREENEFFECT; st++)
	{
		(*g_pEffectSpriteTypeTable)[st].BltType		= BLT_SCREEN;
		(*g_pEffectSpriteTypeTable)[st].FrameID		= sid;
		(*g_pEffectSpriteTypeTable)[st].RepeatFrame	= false;
		(*g_pEffectSpriteTypeTable)[st].ActionEffectFrameID = FRAMEID_NULL;
		//(*g_pEffectSpriteTypeTable)[st].PairFrameID = FRAMEID_NULL;
		(*g_pEffectSpriteTypeTable)[st].FemaleEffectSpriteType = EFFECTSPRITETYPE_NULL;		

		FrameSize[st] = ScreenEFPK[sid][DIRECTION_DOWN].GetSize();

		sid ++;
	}

	sid = 0;

	//------------------------------------------------
	// Normal Effect
	//------------------------------------------------
	for (st=MAX_EFFECTSPRITETYPE_SCREENEFFECT; st<MAX_EFFECTSPRITETYPE_NORMALEFFECT; st++)
	{
		(*g_pEffectSpriteTypeTable)[st].BltType		= BLT_NORMAL;
		(*g_pEffectSpriteTypeTable)[st].FrameID		= sid;
		(*g_pEffectSpriteTypeTable)[st].RepeatFrame	= false;
		(*g_pEffectSpriteTypeTable)[st].ActionEffectFrameID = FRAMEID_NULL;
		//(*g_pEffectSpriteTypeTable)[st].PairFrameID = FRAMEID_NULL;
		(*g_pEffectSpriteTypeTable)[st].FemaleEffectSpriteType = EFFECTSPRITETYPE_NULL;		

		FrameSize[st] = NormalEFPK[sid][DIRECTION_DOWN].GetSize();

		sid ++;
	}

	sid = 0;

	//------------------------------------------------
	// Shadow Effect
	//------------------------------------------------
	for (st=MAX_EFFECTSPRITETYPE_NORMALEFFECT; st<MAX_EFFECTSPRITETYPE; st++)
	{
		(*g_pEffectSpriteTypeTable)[st].BltType		= BLT_SHADOW;
		(*g_pEffectSpriteTypeTable)[st].FrameID		= sid;
		(*g_pEffectSpriteTypeTable)[st].RepeatFrame	= false;
		(*g_pEffectSpriteTypeTable)[st].ActionEffectFrameID = FRAMEID_NULL;
		//(*g_pEffectSpriteTypeTable)[st].PairFrameID = FRAMEID_NULL;	
		(*g_pEffectSpriteTypeTable)[st].FemaleEffectSpriteType = EFFECTSPRITETYPE_NULL;

		FrameSize[st] = ShadowEFPK[sid][DIRECTION_DOWN].GetSize();

		sid ++;
	}

	//------------------------------------------------
	// 반복되는 것 설정
	//------------------------------------------------
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_GREEN_POISON_2].RepeatFrame = true;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_PURPLE_WALL_2].RepeatFrame = true;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_YELLOW_POISON_2].RepeatFrame = true;
//	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_DARKBLUE_POISON_FRONT_2].RepeatFrame = true;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_DARKBLUE_POISON_BACK_2].RepeatFrame = true;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_DARKNESS_2].RepeatFrame = true;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_CURSE_BLIND].RepeatFrame = true;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_CURSE_WEAKNESS_2].RepeatFrame = true;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BLOODY_WALL_1].RepeatFrame = true;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BLOODY_WALL_2].RepeatFrame = true;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BLOODY_WALL_3].RepeatFrame = true;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_PEACE_UP].RepeatFrame = true;
//	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BLESS_ING].RepeatFrame = true;	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BLESS_ING_NEW].RepeatFrame = true;
	// 2004, 6, 5 sobeit add start
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BLINDNESS_BACK_2].RepeatFrame = true;

	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BURNING_SOL_CHARGE_1].RepeatFrame = true;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BURNING_SOL_CHARGE_2].RepeatFrame = true;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BURNING_SOL_CHARGE_3].RepeatFrame = true;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BURNING_SOL_CHARGE_4].RepeatFrame = true;
//
//	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SWORD_OF_THOR_LOOP_GROUND].RepeatFrame = true;
//	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BLINDNESS_BACK_2].RepeatFrame = true;
//	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SWORD_OF_THOR_LOOP_ELECTIRIC_1].RepeatFrame = true;
//	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SWORD_OF_THOR_LOOP_ELECTIRIC_2].RepeatFrame = true;
//
	
	// 2004, 6, 5 sobeit add end

	//------------------------------------------------------------
	//
	//				PairFrame 설정
	//
	//------------------------------------------------------------
	// 뱀파 150 에버레이션
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_ABERRATION_BACK].PairFrameIDList.push_back( EFFECTSPRITETYPE_ABERRATION_FRONT );	
	// 터렛 파이어
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_INSTALL_TURRET_FIRE1].PairFrameIDList.push_back( EFFECTSPRITETYPE_INSTALL_TURRET_FIRE2 );	
	// 버닝 솔
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BURNING_SOL_CHARGE_1].PairFrameIDList.push_back( EFFECTSPRITETYPE_BURNING_SOL_CHARGING_NEW );	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BURNING_SOL_CHARGE_2].PairFrameIDList.push_back( EFFECTSPRITETYPE_BURNING_SOL_CHARGING_NEW );	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BURNING_SOL_CHARGE_3].PairFrameIDList.push_back( EFFECTSPRITETYPE_BURNING_SOL_CHARGING_NEW );	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BURNING_SOL_CHARGE_4].PairFrameIDList.push_back( EFFECTSPRITETYPE_BURNING_SOL_CHARGING_NEW );	
	// 질드레 소환 이펙트
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_GDR_SUMMON_BACK].PairFrameIDList.push_back( EFFECTSPRITETYPE_GDR_SUMMON_FRONT );	
	//------------------------------------------------------------
	// 질드레 위성 EFFECT
	//------------------------------------------------------------
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_GDR_SATELLITE_BACK].PairFrameIDList.push_back( EFFECTSPRITETYPE_GDR_SATELLITE_FRONT );	
	
	//------------------------------------------------------------
	// MASTER EFFECT
	//------------------------------------------------------------
//	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_GRAND_MASTER_SLAYER_130].PairFrameIDList.push_back( EFFECTSPRITETYPE_GRAND_MASTER_SLAYER_100 - MAX_EFFECTSPRITETYPE_ALPHAEFFECT);	
//	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_GRAND_MASTER_SLAYER_150].PairFrameIDList.push_back( EFFECTSPRITETYPE_GRAND_MASTER_SLAYER_100 - MAX_EFFECTSPRITETYPE_ALPHAEFFECT);	
//	
//	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_GRAND_MASTER_VAMPIRE_130].PairFrameIDList.push_back( EFFECTSPRITETYPE_GRAND_MASTER_VAMPIRE_100  - MAX_EFFECTSPRITETYPE_ALPHAEFFECT);	
//	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_GRAND_MASTER_VAMPIRE_150_FRONT].PairFrameIDList.push_back( EFFECTSPRITETYPE_GRAND_MASTER_VAMPIRE_150_BACK - MAX_EFFECTSPRITETYPE_ALPHAEFFECT);	
//	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_GRAND_MASTER_VAMPIRE_150_FRONT].PairFrameIDList.push_back( EFFECTSPRITETYPE_GRAND_MASTER_VAMPIRE_100  - MAX_EFFECTSPRITETYPE_ALPHAEFFECT);	
//	
//	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_GRAND_MASTER_OUSTERS_130].PairFrameIDList.push_back( EFFECTSPRITETYPE_GRAND_MASTER_OUSTERS_100  - MAX_EFFECTSPRITETYPE_ALPHAEFFECT);	
//	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_GRAND_MASTER_OUSTERS_150].PairFrameIDList.push_back( EFFECTSPRITETYPE_GRAND_MASTER_OUSTERS_100  - MAX_EFFECTSPRITETYPE_ALPHAEFFECT);	

	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_SLAYER_130_NEW].PairFrameIDList.push_back( EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_SLAYER_100_NEW);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_SLAYER_150_NEW].PairFrameIDList.push_back( EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_SLAYER_130_NEW);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_SLAYER_150_NEW].PairFrameIDList.push_back( EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_SLAYER_100_NEW);	
	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_VAMPIRE_130_NEW].PairFrameIDList.push_back( EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_VAMPIRE_100_NEW);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_VAMPIRE_150_FRONT_NEW].PairFrameIDList.push_back( EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_VAMPIRE_150_BACK_NEW);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_VAMPIRE_150_FRONT_NEW].PairFrameIDList.push_back( EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_VAMPIRE_100_NEW);	
	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_OUSTERS_130_NEW].PairFrameIDList.push_back( EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_OUSTERS_100_NEW);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_OUSTERS_150_NEW].PairFrameIDList.push_back( EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_OUSTERS_100_NEW);	

	// 승직 마스터 이펙트
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_ADVANCEMENT_MASTER_SLAYER].PairFrameIDList.push_back( EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_SLAYER_130_NEW);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_ADVANCEMENT_MASTER_SLAYER].PairFrameIDList.push_back( EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_SLAYER_100_NEW);	
	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_ADVANCEMENT_MASTER_VAMPIRE_BACK].PairFrameIDList.push_back( EFFECTSPRITETYPE_ADVANCEMENT_MASTER_VAMPIRE_FRONT );	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_ADVANCEMENT_MASTER_VAMPIRE_BACK].PairFrameIDList.push_back( EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_VAMPIRE_100_NEW);	

	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_ADVANCEMENT_MASTER_OUSTER].PairFrameIDList.push_back( EFFECTSPRITETYPE_GRAND_MASTER_ALPHA_OUSTERS_100_NEW);	


	// 추가 이펙트  Sjheon 2005.05.18 Add 
	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_130_COLOR5].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_100_COLOR5);
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_150_BACK_COLOR5].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_150_FRONT_COLOR5);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_150_BACK_COLOR5].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_100_COLOR5);	


	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_ADVANCE_BACK_COLOR5].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_ADVANCE_FRONT_COLOR5);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_ADVANCE_BACK_COLOR5].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_100_COLOR5);	



	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_130_COLOR5].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_100_COLOR5);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_150_COLOR5].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_100_COLOR5);	
	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_150_COLOR5].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_130_COLOR5);	

	//(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_150_COLOR5].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_150_COLOR5);	

	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_ADVANCE_COLOR5].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_130_COLOR5);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_ADVANCE_COLOR5].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_100_COLOR5);	


	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_OUSTERS_130_COLOR5].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_OUSTERS_100_COLOR5);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_OUSTERS_150_COLOR5].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_OUSTERS_100_COLOR5);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_OUSTERS_ADVANCE_COLOR5].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_OUSTERS_100_COLOR5);
	

    
	//(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_ADVANCEMENT_AURA_CRYSTAL_SLAYER].PairFrameIDList.push_back( EFFECTSPRITETYPE_ADVANCEMENT_AURA_CRYSTAL_SLAYER);	
	//(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_ADVANCEMENT_AURA_CRYSTAL_VAMPIRE].PairFrameIDList.push_back( EFFECTSPRITETYPE_ADVANCEMENT_AURA_CRYSTAL_VAMPIRE);	
	//(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_ADVANCEMENT_AURA_CRYSTAL_OUSTER].PairFrameIDList.push_back( EFFECTSPRITETYPE_ADVANCEMENT_AURA_CRYSTAL_OUSTER);
	// 추가 이펙트  Sjheon 2005.05.18 End 


	// sjheon	2005.05.17 Add
	//(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_ADVANCEMENT_AURA_CRYSTAL_SLAYER].PairFrameIDList.push_back( EFFECTSPRITETYPE_ADVANCEMENT_AURA_CRYSTAL_SLAYER);	
	//(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_ADVANCEMENT_AURA_CRYSTAL_VAMPIRE].PairFrameIDList.push_back( EFFECTSPRITETYPE_ADVANCEMENT_AURA_CRYSTAL_VAMPIRE);	
	//(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_ADVANCEMENT_AURA_CRYSTAL_OUSTER].PairFrameIDList.push_back( EFFECTSPRITETYPE_ADVANCEMENT_AURA_CRYSTAL_OUSTER);	
	// sjheon	2005.05.17 End

// 마켓용 마스터 이펙트 start
	
	// 뱀파이어 130 - 3종
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_130_FEAR].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_100_FEAR);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_130_CRULE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_100_CRULE);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_130_HOPE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_100_HOPE);	

	// 뱀파이어 150 - 3종
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_150_FRONT_FEAR].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_150_BACK_FEAR);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_150_FRONT_FEAR].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_100_FEAR);	

	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_150_FRONT_CRULE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_150_BACK_CRULE);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_150_FRONT_CRULE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_100_CRULE);	

	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_150_FRONT_HOPE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_150_BACK_HOPE);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_150_FRONT_HOPE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_100_HOPE);	

	// 뱀파이어 승직 - 3종
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_150_FRONT_ADVANCE_FEAR].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_150_BACK_ADVANCE_FEAR);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_150_FRONT_ADVANCE_FEAR].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_100_FEAR);	

	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_150_FRONT_ADVANCE_CRULE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_150_BACK_ADVANCE_CRULE);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_150_FRONT_ADVANCE_CRULE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_100_CRULE);	

	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_150_FRONT_ADVANCE_HOPE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_150_BACK_ADVANCE_HOPE);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_150_FRONT_ADVANCE_HOPE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_VAMPIRE_100_HOPE);	

	// 슬레이어 130 - 3종
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_130_FEAR].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_100_FEAR);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_130_CRULE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_100_CRULE);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_130_HOPE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_100_HOPE);	

	// 슬레이어 150 - 3종
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_150_FEAR].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_100_FEAR);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_150_FEAR].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_130_FEAR);	

	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_150_CRULE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_100_CRULE);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_150_CRULE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_130_CRULE);	

	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_150_HOPE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_100_HOPE);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_150_HOPE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_130_HOPE);	

	// 슬레이어 승직 - 3종
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_150_ADVANCE_FEAR].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_100_FEAR);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_150_ADVANCE_FEAR].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_130_FEAR);	

	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_150_ADVANCE_CRULE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_100_CRULE);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_150_ADVANCE_CRULE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_130_CRULE);	

	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_150_ADVANCE_HOPE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_100_HOPE);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_150_ADVANCE_HOPE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_SLAYER_130_HOPE);	

	// 아우스터즈 130 - 3종
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_OUSTERS_130_FEAR].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_OUSTERS_100_FEAR);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_OUSTERS_130_CRULE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_OUSTERS_100_CRULE);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_OUSTERS_130_HOPE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_OUSTERS_100_HOPE);	

	// 아우스터즈 150 - 3종
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_OUSTERS_150_FEAR].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_OUSTERS_100_FEAR);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_OUSTERS_150_CRULE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_OUSTERS_100_CRULE);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_OUSTERS_150_HOPE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_OUSTERS_100_HOPE);	

	// 아우스터즈 승직 - 3종
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_OUSTERS_150_ADVANCE_FEAR].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_OUSTERS_100_FEAR);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_OUSTERS_150_ADVANCE_CRULE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_OUSTERS_100_CRULE);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MARKET_MASTER_OUSTERS_150_ADVANCE_HOPE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MARKET_MASTER_OUSTERS_100_HOPE);	
	
	// 마켓용 마스터 이펙트 end

	// 피블 바이러스  Start
	// 피블 바이러스  처음 
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_FEEBLEVIRUS_LINE_BACK].PairFrameIDList.push_back( EFFECTSPRITETYPE_FEEBLEVIRUS_LINE_FRONT);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_FEEBLEVIRUS_LINE_BACK].PairFrameIDList.push_back( EFFECTSPRITETYPE_FEEBLEVIRUS_SMOKE_START_BACK);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_FEEBLEVIRUS_LINE_BACK].PairFrameIDList.push_back( EFFECTSPRITETYPE_FEEBLEVIRUS_SMOKE_START_FRONT);	

	// 피블 바이러스  반복
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_FEEBLEVIRUS_SMOKE_END_BACK].PairFrameIDList.push_back( EFFECTSPRITETYPE_FEEBLEVIRUS_SMOKE_END_FAONT);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_FEEBLEVIRUS_SMOKE_END_BACK].PairFrameIDList.push_back( EFFECTSPRITETYPE_FEEBLEVIRUS_LINE_BACK);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_FEEBLEVIRUS_SMOKE_END_BACK].PairFrameIDList.push_back( EFFECTSPRITETYPE_FEEBLEVIRUS_LINE_FRONT);	
	
	// 피블 바이러스  종료
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_FEEBLEVIRUS_SMOKE_RELEASE_BACK].PairFrameIDList.push_back( EFFECTSPRITETYPE_FEEBLEVIRUS_SMOKE_RELEASE_FRONT);	
	// 피블 바이러스 End
	
	// 폭주 시스템 이펙트 Add
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BLOOD_BURST_ATTACK_ORANGE_LIGHT].PairFrameIDList.push_back( EFFECTSPRITETYPE_BLOOD_BURST_ATTACK_ORANGE_SMOKE);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BLOOD_BURST_ATTACK_GREEN_LIGHT].PairFrameIDList.push_back( EFFECTSPRITETYPE_MIKLLIZZ_FEELER_WRIGGLE_START);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BLOOD_BURST_ATTACK_WHITE_LIGHT].PairFrameIDList.push_back( EFFECTSPRITETYPE_MIKLLIZZ_FEELER_WRIGGLE_REPEAT);	


	// 폭주 시스템 이펙트 End
	
	// 미클리스 촉수 박힘 
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MIKLLIZZ_FEELER_STUCK_FRONT].PairFrameIDList.push_back( EFFECTSPRITETYPE_MIKLLIZZ_FEELER_STUCK_BEHIND);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MIKLLIZZ_FEELER_STUCK_FRONT].PairFrameIDList.push_back( EFFECTSPRITETYPE_MIKLLIZZ_FEELER_WRIGGLE_START);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MIKLLIZZ_FEELER_STUCK_FRONT].PairFrameIDList.push_back( EFFECTSPRITETYPE_MIKLLIZZ_FEELER_WRIGGLE_REPEAT);	


	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MIKLLIZZ_SOUND_WAVE_ATTACK_TYPE_A_FRONT].PairFrameIDList.push_back( EFFECTSPRITETYPE_MIKLLIZZ_SOUND_WAVE_ATTACK_TYPE_A_BEHIND);	
	
	//(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MIKLLIZZ_PILLAR_OF_FIRE_TYPE_A_START].PairFrameIDList.push_back( EFFECTSPRITETYPE_MIKLLIZZ_PILLAR_OF_FIRE_TYPE_B_START);	
	//(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MIKLLIZZ_PILLAR_OF_FIRE_TYPE_A_START].PairFrameIDList.push_back( EFFECTSPRITETYPE_MIKLLIZZ_PILLAR_OF_FIRE_TYPE_C_START);	

	//(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MIKLLIZZ_PILLAR_OF_FIRE_TYPE_A_REPEAT].PairFrameIDList.push_back( EFFECTSPRITETYPE_MIKLLIZZ_PILLAR_OF_FIRE_TYPE_B_REPEAT);	
	//(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MIKLLIZZ_PILLAR_OF_FIRE_TYPE_A_REPEAT].PairFrameIDList.push_back( EFFECTSPRITETYPE_MIKLLIZZ_PILLAR_OF_FIRE_TYPE_C_REPEAT);	

	//(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MIKLLIZZ_PILLAR_OF_FIRE_TYPE_A_END].PairFrameIDList.push_back( EFFECTSPRITETYPE_MIKLLIZZ_PILLAR_OF_FIRE_TYPE_B_END);	
	//(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MIKLLIZZ_PILLAR_OF_FIRE_TYPE_A_END].PairFrameIDList.push_back( EFFECTSPRITETYPE_MIKLLIZZ_PILLAR_OF_FIRE_TYPE_C_END);	

	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MIKLLIZZ_SOUND_WAVE_ATTACK_TYPE_B_FRONT].PairFrameIDList.push_back( EFFECTSPRITETYPE_MIKLLIZZ_SOUND_WAVE_ATTACK_TYPE_B_BEHIND);	

	// 2006.10 20 sjheon
	//(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SHINE_SWORD_FALL_DOWN_A].PairFrameIDList.push_back( EFFECTSPRITETYPE_SHINE_SWORD_FALL_DOWN_B);	

	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_ILLUSION_INVERSION_IMBIBITION_FRONT].PairFrameIDList.push_back( EFFECTSPRITETYPE_ILLUSION_INVERSION_IMBIBITION_BEHIND);	


	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_DUMMY_DRAKE_FIRE_BALL_BEHIND].PairFrameIDList.push_back( EFFECTSPRITETYPE_DUMMY_DRAKE_FIRE_BALL_FRONT);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_DUMMY_DRAKE_FIRE_BALL_BEHIND].PairFrameIDList.push_back( EFFECTSPRITETYPE_DUMMY_DRAKE_FIRE_BALL_LIGHT);	


	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_HYDRO_CONVERGENCE_PILLAR_OF_WATER_START].PairFrameIDList.push_back( EFFECTSPRITETYPE_HYDRO_CONVERGENCE_WATER_GROUND_START);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_HYDRO_CONVERGENCE_PILLAR_OF_WATER_REPEAT].PairFrameIDList.push_back( EFFECTSPRITETYPE_HYDRO_CONVERGENCE_WATER_GROUND_REPEAT);	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_HYDRO_CONVERGENCE_PILLAR_OF_WATER_END].PairFrameIDList.push_back( EFFECTSPRITETYPE_HYDRO_CONVERGENCE_WATER_GROUND_END);	

	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_REQUEST_RESURRECT_LIGHT_FRONT].PairFrameIDList.push_back( EFFECTSPRITETYPE_REQUEST_RESURRECT_LIGHT_BEHIND);
#if __CONTENTS(__DSG_EFFECT)	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_DSG_FRONT].PairFrameIDList.push_back( EFFECTSPRITETYPE_DSG_BACK);
#endif //__DSG_EFFECT

#if __CONTENTS(__SECOND_RARE_SKILL)	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_THORNS_FRONT].PairFrameIDList.push_back( EFFECTSPRITETYPE_THORNS_BACK);
#endif //__SECOND_RARE_SKILL

#if __CONTENTS(__TIPOJYU_CASTLE)	//현세 진입 NPC 이펙트 추가(스킬이 2개로 나쥐어져 따로 보이는 것을 하나로 보이게)
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_TIPOJYU_LIFE_CASTLE_ADDMISION_NPC1].PairFrameIDList.push_back( EFFECTSPRITETYPE_TIPOJYU_LIFE_CASTLE_ADDMISION_NPC2);
#endif // __TIPOJYU_CASTLE
#if __CONTENTS(__2008_OCTOBER_MAKETITEM)
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BEARBOX_FRONT].PairFrameIDList.push_back(EFFECTSPRITETYPE_BEARBOX_BACK);
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SUCCUBUS_SUMMON_FRONT].PairFrameIDList.push_back(EFFECTSPRITETYPE_SUCCUBUS_SUMMON_BACK);
	
#endif //__2008_OCTOBER_MAKETITEM
#if __CONTENTS(__PET_MASHIMARO)
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MASHIMARO_SUMMON_FRONT].PairFrameIDList.push_back(EFFECTSPRITETYPE_MASHIMARO_SUMMON_BACK);
#endif //__PET_MASHIMARO

#if __CONTENTS(__PET_CATS)
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_CATS_SUMMON_FRONT].PairFrameIDList.push_back(EFFECTSPRITETYPE_CATS_SUMMON_BACK);
#endif //__PET_CATS

#if __CONTENTS(__PET_CATS_UPGRADED)
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_CATS_SUMMON_FRONT].PairFrameIDList.push_back(EFFECTSPRITETYPE_CATS_SUMMON_BACK);
#endif //__PET_CATS_UPGRADED

#if __CONTENTS(__PET_CATS_UPGRADED)
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_UPGRADED_CARA_CATS_EFFECT_FRONT].PairFrameIDList.push_back(EFFECTSPRITETYPE_UPGRADED_CARA_CATS_EFFECT_BACK);
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_UPGRADED_DELLA_CATS_EFFECT_FRONT].PairFrameIDList.push_back(EFFECTSPRITETYPE_UPGRADED_DELLA_CATS_EFFECT_BACK);
#endif //__PET_CATS_UPGRADED

#if __CONTENTS(__20091116_ADD_RARE_SKILL)
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_OUSTERS_SQUALLY_BARRIER_1_RARE_SKILL_FRONT].PairFrameIDList.push_back(EFFECTSPRITETYPE_OUSTERS_SQUALLY_BARRIER_1_RARE_SKILL_BACK);
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_OUSTERS_SQUALLY_BARRIER_2_RARE_SKILL_FRONT].PairFrameIDList.push_back(EFFECTSPRITETYPE_OUSTERS_SQUALLY_BARRIER_2_RARE_SKILL_BACK);
#endif //__20091116_ADD_RARE_SKILL

	//------------------------------------------------------------
	// BERSERKER
	//------------------------------------------------------------
#if __CONTENTS(__EFFECT_RENEWAL)
	const int berserkerNumPairs = 136;
#else
	const int berserkerNumPairs = 80;
#endif //__EFFECT_RENEWAL
	const int berserkerPairFrames[berserkerNumPairs] = 
	{
		EFFECTSPRITETYPE_BERSERKER_1_STAND_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_STAND_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_STAND_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_STAND_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_STAND_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_STAND_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_STAND_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_STAND_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_MOVE_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_MOVE_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_MOVE_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_MOVE_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_MOVE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_MOVE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_MOVE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_MOVE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_MAGIC_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_MAGIC_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_MAGIC_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_MAGIC_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_MAGIC_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_MAGIC_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_MAGIC_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_MAGIC_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_DAMAGE_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_DAMAGE_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_DAMAGE_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_DAMAGE_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_DAMAGE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_DAMAGE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_DAMAGE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_DAMAGE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE2_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE2_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE2_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE2_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE2_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE2_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE2_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE2_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE2_FAST_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE2_FAST_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE2_FAST_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE2_FAST_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE2_FAST_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE2_FAST_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE2_FAST_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE2_FAST_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE2_SLOW_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE2_SLOW_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE2_SLOW_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE2_SLOW_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE2_SLOW_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE2_SLOW_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE2_SLOW_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE2_SLOW_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE_FAST_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE_FAST_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE_FAST_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE_FAST_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE_FAST_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE_FAST_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE_FAST_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE_FAST_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE_SLOW_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE_SLOW_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE_SLOW_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE_SLOW_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE_SLOW_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE_SLOW_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE_SLOW_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE_SLOW_FEMALE,
#if __CONTENTS(__EFFECT_RENEWAL)
		EFFECTSPRITETYPE_BERSERKER_1_DRAIN_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_DRAIN_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_DRAIN_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_DRAIN_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_DIE_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_DIE_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_DIE_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_DIE_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_MOTOR_MOVE_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_MOTOR_MOVE_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_MOTOR_MOVE_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_MOTOR_MOVE_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_MOTOR_STAND_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_MOTOR_STAND_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_MOTOR_STAND_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_MOTOR_STAND_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_BATTLE_STAND_BLADE_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_BATTLE_STAND_BLADE_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_BATTLE_STAND_BLADE_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_BATTLE_STAND_BLADE_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_MAGIC_CASTING_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_MAGIC_CASTING_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_MAGIC_CASTING_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_MAGIC_CASTING_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE_2_REPEAT_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE_2_REPEAT_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE_2_REPEAT_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE_2_REPEAT_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_DRAIN_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_DRAIN_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_DRAIN_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_DRAIN_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_DIE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_DIE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_DIE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_DIE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_MOTOR_MOVE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_MOTOR_MOVE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_MOTOR_MOVE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_MOTOR_MOVE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_MOTOR_STAND_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_MOTOR_STAND_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_MOTOR_STAND_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_MOTOR_STAND_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_BATTLE_STAND_BLADE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_BATTLE_STAND_BLADE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_BATTLE_STAND_BLADE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_BATTLE_STAND_BLADE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_MAGIC_CASTING_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_MAGIC_CASTING_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_MAGIC_CASTING_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_MAGIC_CASTING_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE_2_REPEAT_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE_2_REPEAT_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE_2_REPEAT_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE_2_REPEAT_FEMALE,
#endif //__EFFECT_RENEWAL
	};
// EFFECTSPRITETYPE 선언된것을 보면 알겠지만 기존에는 좌우 3개씩 6개로 이루어졌던 이팩트가 4개로 줄었다.따라서 4개에 걸맞도록 수정
// enum값은 걍 지워 버리고 아래 코드만 살짝 남겨둠
	for (int pf=0; pf<berserkerNumPairs; pf+=4)
	{
		int current = berserkerPairFrames[pf];
		int p1 = berserkerPairFrames[pf+1];
		int p2 = berserkerPairFrames[pf+2];
		int p3 = berserkerPairFrames[pf+3];
		//int p4 = berserkerPairFrames[pf+4];
		//int p5 = berserkerPairFrames[pf+5];

		(*g_pEffectSpriteTypeTable)[current].PairFrameIDList.push_back( p1 );
		(*g_pEffectSpriteTypeTable)[current].PairFrameIDList.push_back( p2 );
		(*g_pEffectSpriteTypeTable)[current].PairFrameIDList.push_back( p3 );
		//(*g_pEffectSpriteTypeTable)[current].PairFrameIDList.push_back( p4 );
		//(*g_pEffectSpriteTypeTable)[current].PairFrameIDList.push_back( p5 );
	}


	//------------------------------------------------------------
	// REGENERATION
	//------------------------------------------------------------
#if __CONTENTS(__EFFECT_RENEWAL)
	const int regenNumPairs = 176;
#else
	const int regenNumPairs = 64;
#endif
	const int regenPairFrames[regenNumPairs] = 
	{
		EFFECTSPRITETYPE_REGENERATION_1_STAND_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_STAND_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_STAND_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_STAND_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_MOVE_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_MOVE_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_MOVE_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_MOVE_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_ATTACK_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_ATTACK_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_ATTACK_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_ATTACK_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_MAGIC_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_MAGIC_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_MAGIC_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_MAGIC_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_DAMAGE_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_DAMAGE_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_DAMAGE_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_DAMAGE_FEMALE ,
		EFFECTSPRITETYPE_REGENERATION_1_AR_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_AR_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_AR_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_AR_FEMALE ,
		EFFECTSPRITETYPE_REGENERATION_1_SR_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SR_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SR_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SR_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD_MALE ,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_THROW_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_THROW_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_THROW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_THROW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_MOTOR_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_MOTOR_MALE ,
		EFFECTSPRITETYPE_REGENERATION_1_MOTOR_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_MOTOR_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SG_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SG_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SG_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SG_FEMALE ,
		EFFECTSPRITETYPE_REGENERATION_1_SMG_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SMG_MALE ,
		EFFECTSPRITETYPE_REGENERATION_1_SMG_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SMG_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD2_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD2_MALE ,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD2_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD2_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE2_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE2_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE2_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE2_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_THROW2_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_THROW2_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_THROW2_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_THROW2_FEMALE,
#if __CONTENTS(__EFFECT_RENEWAL)
		EFFECTSPRITETYPE_REGENERATION_1_MAGIC_ATTACK_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_MAGIC_ATTACK_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_DRAIN_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_DRAIN_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_DIE_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_DIE_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_BIKE_MOVE_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_BIKE_MOVE_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_BIKE_STOP_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_BIKE_STOP_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SR_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SR_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SR_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SR_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_AR_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_AR_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_AR_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_AR_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SG_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SG_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SG_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SG_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SMG_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SMG_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SMG_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SMG_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD2_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD2_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD2_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD2_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE2_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE2_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE2_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE2_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_BATTLE_STAND_GUN_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_BATTLE_STAND_GUN_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_BATTLE_STAND_SWORD_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_BATTLE_STAND_SWORD_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_BATTLE_STAND_BLADE_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_BATTLE_STAND_BLADE_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_MOVE_GUN_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_MOVE_GUN_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_MAGIC_CASTING_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_MAGIC_CASTING_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD_2_REPEAT_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD_2_REPEAT_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE_2_REPEAT_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE_2_REPEAT_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_MAGIC_ATTACK_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_MAGIC_ATTACK_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_DRAIN_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_DRAIN_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_DIE_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_DIE_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_BIKE_MOVE_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_BIKE_MOVE_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_BIKE_STOP_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_BIKE_STOP_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SR_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SR_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SR_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SR_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_AR_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_AR_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_AR_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_AR_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SG_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SG_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SG_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SG_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SMG_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SMG_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SMG_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SMG_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD2_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD2_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD2_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD2_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE2_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE2_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE2_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE2_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_BATTLE_STAND_GUN_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_BATTLE_STAND_GUN_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_BATTLE_STAND_SWORD_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_BATTLE_STAND_SWORD_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_BATTLE_STAND_BLADE_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_BATTLE_STAND_BLADE_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_MOVE_GUN_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_MOVE_GUN_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_MAGIC_CASTING_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_MAGIC_CASTING_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD_2_REPEAT_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD_2_REPEAT_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE_2_REPEAT_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE_2_REPEAT_FEMALE,
#endif //__EFFECT_RENEWAL
	};

	for (int rpf=0; rpf<regenNumPairs; rpf+=2)
	{
		(*g_pEffectSpriteTypeTable)[regenPairFrames[rpf]].PairFrameIDList.push_back( regenPairFrames[rpf+1] );
	}

	//------------------------------------------------------------
	// Extreme
	//------------------------------------------------------------
#if __CONTENTS(__EFFECT_RENEWAL)
	const int extremeNumPairs = 68;
#else
	const int extremeNumPairs = 24;
#endif //__EFFECT_RENEWAL
	const int extremePairFrames[extremeNumPairs] = 
	{
		EFFECTSPRITETYPE_EXTREME_L_1_STAND_MALE,	// 뱀파 어깨에 붙는 검은 기운.
		EFFECTSPRITETYPE_EXTREME_R_1_STAND_MALE,
		EFFECTSPRITETYPE_EXTREME_L_1_MOVE_MALE,
		EFFECTSPRITETYPE_EXTREME_R_1_MOVE_MALE,
		EFFECTSPRITETYPE_EXTREME_L_1_ATTACK_MALE,
		EFFECTSPRITETYPE_EXTREME_R_1_ATTACK_MALE,
		EFFECTSPRITETYPE_EXTREME_L_1_ATTACK_SLOW_MALE,
		EFFECTSPRITETYPE_EXTREME_R_1_ATTACK_SLOW_MALE,
		EFFECTSPRITETYPE_EXTREME_L_1_ATTACK_FAST_MALE,
		EFFECTSPRITETYPE_EXTREME_R_1_ATTACK_FAST_MALE,
		EFFECTSPRITETYPE_EXTREME_L_1_DAMAGE_MALE,
		EFFECTSPRITETYPE_EXTREME_R_1_DAMAGE_MALE,
		EFFECTSPRITETYPE_EXTREME_L_1_STAND_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_1_STAND_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_1_MOVE_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_1_MOVE_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_1_ATTACK_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_1_ATTACK_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_1_ATTACK_SLOW_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_1_ATTACK_SLOW_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_1_ATTACK_FAST_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_1_ATTACK_FAST_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_1_DAMAGE_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_1_DAMAGE_FEMALE,
#if __CONTENTS(__EFFECT_RENEWAL)
		EFFECTSPRITETYPE_EXTREME_L_MAGIC_ATTACK_MALE,
		EFFECTSPRITETYPE_EXTREME_R_MAGIC_ATTACK_MALE,
		EFFECTSPRITETYPE_EXTREME_L_DRIN_MALE,
		EFFECTSPRITETYPE_EXTREME_R_DRIN_MALE,
		EFFECTSPRITETYPE_EXTREME_L_DIE_MALE,
		EFFECTSPRITETYPE_EXTREME_R_DIE_MALE,
		EFFECTSPRITETYPE_EXTREME_L_DRIN_ATTACK_MALE,
		EFFECTSPRITETYPE_EXTREME_R_DRIN_ATTACK_MALE,
		EFFECTSPRITETYPE_EXTREME_L_ATTACK_2_MALE,
		EFFECTSPRITETYPE_EXTREME_R_ATTACK_2_MALE,
		EFFECTSPRITETYPE_EXTREME_L_ATTACK_2_SLOW_MALE,
		EFFECTSPRITETYPE_EXTREME_R_ATTACK_2_SLOW_MALE,
		EFFECTSPRITETYPE_EXTREME_L_ATTACK_2_FAST_MALE,
		EFFECTSPRITETYPE_EXTREME_R_ATTACK_2_FAST_MALE,
		EFFECTSPRITETYPE_EXTREME_L_ATTACK_3_MALE,
		EFFECTSPRITETYPE_EXTREME_R_ATTACK_3_MALE,
		EFFECTSPRITETYPE_EXTREME_L_ATTACK_3_SLOW_MALE,
		EFFECTSPRITETYPE_EXTREME_R_ATTACK_3_SLOW_MALE,
		EFFECTSPRITETYPE_EXTREME_L_ATTACK_3_FAST_MALE,
		EFFECTSPRITETYPE_EXTREME_R_ATTACK_3_FAST_MALE,
		EFFECTSPRITETYPE_EXTREME_L_MAGIC_CASTING_MALE,
		EFFECTSPRITETYPE_EXTREME_R_MAGIC_CASTING_MALE,
		EFFECTSPRITETYPE_EXTREME_L_MAGIC_ATTACK_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_MAGIC_ATTACK_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_DRIN_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_DRIN_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_DIE_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_DIE_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_DRIN_ATTACK_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_DRIN_ATTACK_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_ATTACK_2_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_ATTACK_2_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_ATTACK_2_SLOW_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_ATTACK_2_SLOW_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_ATTACK_2_FAST_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_ATTACK_2_FAST_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_ATTACK_3_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_ATTACK_3_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_ATTACK_3_SLOW_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_ATTACK_3_SLOW_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_ATTACK_3_FAST_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_ATTACK_3_FAST_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_MAGIC_CASTING_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_MAGIC_CASTING_FEMALE,
#endif //__EFFECT_RENEWAL
	};

	for (pf=0; pf<extremeNumPairs; pf+=2)
	{
		int current = extremePairFrames[pf];
		int p1 = extremePairFrames[pf+1];
		
		(*g_pEffectSpriteTypeTable)[current].PairFrameIDList.push_back( p1 );
	}


//	//------------------------------------------------------------
//	// ARMAGEDDON
//	//------------------------------------------------------------
//	const int armageddonNumPairs = 18;
//	const int armageddonPairFrames[armageddonNumPairs] = 
//	{
//		EFFECTSPRITETYPE_ARMAGEDDON_BACK_1_1,
//		EFFECTSPRITETYPE_ARMAGEDDON_FRONT_1_1,
//		EFFECTSPRITETYPE_ARMAGEDDON_BACK_1_2,		
//		EFFECTSPRITETYPE_ARMAGEDDON_FRONT_1_2,
//		EFFECTSPRITETYPE_ARMAGEDDON_BACK_2_1,
//		EFFECTSPRITETYPE_ARMAGEDDON_FRONT_2_1,
//		EFFECTSPRITETYPE_ARMAGEDDON_BACK_2_2,		
//		EFFECTSPRITETYPE_ARMAGEDDON_FRONT_2_2,
//		EFFECTSPRITETYPE_ARMAGEDDON_BACK_3_1,
//		EFFECTSPRITETYPE_ARMAGEDDON_FRONT_3_1,
//		EFFECTSPRITETYPE_ARMAGEDDON_BACK_3_2,		
//		EFFECTSPRITETYPE_ARMAGEDDON_FRONT_3_2,
//		EFFECTSPRITETYPE_ARMAGEDDON_BACK_4_1,
//		EFFECTSPRITETYPE_ARMAGEDDON_FRONT_4_1,
//		EFFECTSPRITETYPE_ARMAGEDDON_END_BACK,
//		EFFECTSPRITETYPE_ARMAGEDDON_END_FRONT,	
//		EFFECTSPRITETYPE_ARMAGEDDON_BACK_0_2,
//		EFFECTSPRITETYPE_ARMAGEDDON_FRONT_0_2,	
//	};
//
//	for (pf=0; pf<armageddonNumPairs; pf+=2)
//	{
//		int current = armageddonPairFrames[pf];
//		int p1 = armageddonPairFrames[pf+1];
//		
//		(*g_pEffectSpriteTypeTable)[current].PairFrameIDList.push_back( p1 );
//	}

//	//------------------------------------------------------------
//	// Bullet Of Light
//	//------------------------------------------------------------
//	const int bolNumPairs = 14;
//	const int bolPairFrames[bolNumPairs] = 
//	{
//		EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_1,
//		EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_1-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,
//		EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_2,
//		EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_2-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,
//		EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_3,
//		EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_3-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,
//		EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_4,
//		EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_4-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,
//		EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_5,
//		EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_5-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,
//		EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_6,
//		EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_6-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,
//		EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_7,
//		EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_7-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,
//	};
//
//	for (pf=0; pf<bolNumPairs; pf+=2)
//	{
//		int current = bolPairFrames[pf];
//		int p1 = bolPairFrames[pf+1];
//		
//		(*g_pEffectSpriteTypeTable)[current].PairFrameIDList.push_back( p1 );
//	}

	//------------------------------------------------------------
	// ARMAGEDDON
	//------------------------------------------------------------
	const int vampireGrandmasterNumPairs = 16*2;
	const int vampireGrandmasterPairFrames[vampireGrandmasterNumPairs] = 
	{
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK,			// 뱀파이어-남자정지뒤
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_FRONT-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,			// 뱀파이어-남자정지앞
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_MAGIC_BACK,			// 뱀파이어-남자마법뒤
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_MAGIC_FRONT-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,			// 뱀파이어-남자마법앞
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_DAMAGED_BACK,			// 뱀파이어-남자맞기뒤
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_DAMAGED_FRONT-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자맞기앞
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_DRAINED_BACK,			// 뱀파이어-남자흡혈당하기뒤
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_DRAINED_FRONT-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자흡혈당하기앞
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_DRAIN_BACK,			// 뱀파이어-남자흡혈하기뒤
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_DRAIN_FRONT-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,			// 뱀파이어-남자흡혈하기앞
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_ATTACK_SLOW_BACK,		// 뱀파이어-남자공격뒤s
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_ATTACK_SLOW_FRONT-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,	// 뱀파이어-남자공격앞s
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_ATTACK_BACK,			// 뱀파이어-남자공격뒤n
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_ATTACK_FRONT-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,			// 뱀파이어-남자공격앞n
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_ATTACK_FAST_BACK,		// 뱀파이어-남자공격뒤f
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_ATTACK_FAST_FRONT-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,	// 뱀파이어-남자공격앞f
			
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK,			// 뱀파이어-여자정지뒤
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_FRONT-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지앞
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_MAGIC_BACK,			// 뱀파이어-여자마법뒤
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_MAGIC_FRONT-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자마법앞
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_DAMAGED_BACK,		// 뱀파이어-여자맞기뒤
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_DAMAGED_FRONT-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자맞기앞
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_DRAINED_BACK,		// 뱀파이어-여자흡혈당하기뒤
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_DRAINED_FRONT-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자흡혈당하기앞
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_DRAIN_BACK,			// 뱀파이어-여자흡혈하기뒤
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_DRAIN_FRONT-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자흡혈하기앞
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_ATTACK_SLOW_BACK,	// 뱀파이어-여자공격뒤s
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_ATTACK_SLOW_FRONT-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,	// 뱀파이어-여자공격앞s
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_ATTACK_BACK,		// 뱀파이어-여자공격뒤n
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_ATTACK_FRONT-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자공격앞n
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_ATTACK_FAST_BACK,	// 뱀파이어-여자공격뒤f
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_ATTACK_FAST_FRONT-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,	// 뱀파이어-여자공격앞f
	};

	for (pf=0; pf<vampireGrandmasterNumPairs; pf+=2)
	{
		int current = vampireGrandmasterPairFrames[pf];
		int p1 = vampireGrandmasterPairFrames[pf+1];
		
		(*g_pEffectSpriteTypeTable)[current].PairFrameIDList.push_back( p1 );
	}

	//------------------------------------------------------------
	// BULLET_OF_LIGHT
	//------------------------------------------------------------
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_1].PairFrameIDList.push_back( EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_1 - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_2].PairFrameIDList.push_back( EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_2 - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_3].PairFrameIDList.push_back( EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_3 - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_4].PairFrameIDList.push_back( EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_4 - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_5].PairFrameIDList.push_back( EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_5 - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_6].PairFrameIDList.push_back( EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_6 - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_7].PairFrameIDList.push_back( EFFECTSPRITETYPE_BULLET_OF_LIGHT_END_7 - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );	

	//------------------------------------------------------------
	// POLYMORPH
	//------------------------------------------------------------
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_POLYMORPH_BACK].PairFrameIDList.push_back( EFFECTSPRITETYPE_POLYMORPH_FRONT );	

	//------------------------------------------------------------
	// TYPHOON
	//------------------------------------------------------------
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_TYPHOON_BACK].PairFrameIDList.push_back( EFFECTSPRITETYPE_TYPHOON_FRONT );		

	//------------------------------------------------------------
	// EXORCISM
	//------------------------------------------------------------
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_EXORCISM_BACK].PairFrameIDList.push_back( 
								EFFECTSPRITETYPE_EXORCISM_FRONT - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );
	
	//------------------------------------------------------------
	// PEACE
	//------------------------------------------------------------
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_PEACE_BACK].PairFrameIDList.push_back( 
								EFFECTSPRITETYPE_PEACE_FRONT - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );		

	//------------------------------------------------------------
	// HYMN
	//------------------------------------------------------------
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_HYMN_BACK].PairFrameIDList.push_back( EFFECTSPRITETYPE_HYMN_FRONT );	

	//------------------------------------------------------------
	// VAMPIRE_HAS_RELIC
	//------------------------------------------------------------
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_RELIC_CHARACTER_VAMPIRE_SKULL].PairFrameIDList.push_back( EFFECTSPRITETYPE_RELIC_CHARACTER_VAMPIRE_FIRE - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );	

	// LEVEL_UP_SLAYER
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SLAYER_LEVELUP_FRONT].PairFrameIDList.push_back( EFFECTSPRITETYPE_SLAYER_LEVELUP_GROUND - MAX_EFFECTSPRITETYPE_ALPHAEFFECT);
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SLAYER_LEVELUP_FRONT].PairFrameIDList.push_back( EFFECTSPRITETYPE_SLAYER_LEVELUP_BACK - MAX_EFFECTSPRITETYPE_ALPHAEFFECT);

	// LEVEL_UP_VAMPIRE
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_VAMPIRE_LEVELUP_FRONT].PairFrameIDList.push_back( EFFECTSPRITETYPE_VAMPIRE_LEVELUP_GROUND - MAX_EFFECTSPRITETYPE_ALPHAEFFECT);
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_VAMPIRE_LEVELUP_FRONT].PairFrameIDList.push_back( EFFECTSPRITETYPE_VAMPIRE_LEVELUP_BACK - MAX_EFFECTSPRITETYPE_ALPHAEFFECT);

	// SHARP_SHIELD_3
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SHARP_SHIELD_BOTTOM].PairFrameIDList.push_back( EFFECTSPRITETYPE_SHARP_SHIELD_TOP - MAX_EFFECTSPRITETYPE_ALPHAEFFECT);

	// SHARP_SHIELD_4
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SHARP_SHIELD_BOTTOM_2].PairFrameIDList.push_back( EFFECTSPRITETYPE_SHARP_SHIELD_TOP - MAX_EFFECTSPRITETYPE_ALPHAEFFECT);

	// AIR_SHIELD_3
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_AIR_SHIELD_RIGHT].PairFrameIDList.push_back( EFFECTSPRITETYPE_AIR_SHIELD_LEFT - MAX_EFFECTSPRITETYPE_ALPHAEFFECT);

	// AIR_SHIELD_4
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_AIR_SHIELD_LEFT_2].PairFrameIDList.push_back( EFFECTSPRITETYPE_AIR_SHIELD_LEFT - MAX_EFFECTSPRITETYPE_ALPHAEFFECT);

	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_AMBER_OF_GUARD].PairFrameIDList.push_back( EFFECTSPRITETYPE_AMBER - MAX_EFFECTSPRITETYPE_ALPHAEFFECT);
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_AMBER_OF_AVENGER].PairFrameIDList.push_back( EFFECTSPRITETYPE_AMBER - MAX_EFFECTSPRITETYPE_ALPHAEFFECT);
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_AMBER_OF_IMMORTAL].PairFrameIDList.push_back( EFFECTSPRITETYPE_AMBER - MAX_EFFECTSPRITETYPE_ALPHAEFFECT);
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_AMBER_OF_CURSE].PairFrameIDList.push_back( EFFECTSPRITETYPE_AMBER - MAX_EFFECTSPRITETYPE_ALPHAEFFECT);
	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_AMBER_OF_GUARD_TILE].PairFrameIDList.push_back( EFFECTSPRITETYPE_AMBER_TILE - MAX_EFFECTSPRITETYPE_ALPHAEFFECT);
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_AMBER_OF_AVENGER_TILE].PairFrameIDList.push_back( EFFECTSPRITETYPE_AMBER_TILE - MAX_EFFECTSPRITETYPE_ALPHAEFFECT);
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_AMBER_OF_IMMORTAL_TILE].PairFrameIDList.push_back( EFFECTSPRITETYPE_AMBER_TILE - MAX_EFFECTSPRITETYPE_ALPHAEFFECT);
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_AMBER_OF_CURSE_TILE].PairFrameIDList.push_back( EFFECTSPRITETYPE_AMBER_TILE - MAX_EFFECTSPRITETYPE_ALPHAEFFECT);
	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_POISON_MESH_END].PairFrameIDList.push_back( EFFECTSPRITETYPE_POISON_MESH_END_BACK - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_POISON_MESH_ING].PairFrameIDList.push_back( EFFECTSPRITETYPE_POISON_MESH_ING_BACK - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_POISON_MESH_END].PairFrameIDList.push_back( EFFECTSPRITETYPE_POISON_MESH_END_BACK - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );

	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_DRAGON_FIRE_CRACKER_FRONT].PairFrameIDList.push_back( EFFECTSPRITETYPE_DRAGON_FIRE_CRACKER_BACK - MAX_EFFECTSPRITETYPE_ALPHAEFFECT);
	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_TENDRIL_END].PairFrameIDList.push_back( EFFECTSPRITETYPE_TENDRIL_GRASS_END );
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_TENDRIL_ING].PairFrameIDList.push_back( EFFECTSPRITETYPE_TENDRIL_GRASS_ING );
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_TENDRIL_END].PairFrameIDList.push_back( EFFECTSPRITETYPE_TENDRIL_GRASS_END );
	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_OUSTERS_LEVELUP_GROUND].PairFrameIDList.push_back( EFFECTSPRITETYPE_OUSTERS_LEVELUP_BACK - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BACK_STAB_1].PairFrameIDList.push_back( EFFECTSPRITETYPE_BACK_STAB_2 - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BACK_STAB2].PairFrameIDList.push_back( EFFECTSPRITETYPE_BACK_STAB2_2 - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );
	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BLITZ_SLIDING_DROP].PairFrameIDList.push_back( EFFECTSPRITETYPE_BLITZ_SLIDING_SPARK );

	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_INSTALL_TRAP_ING_FRONT].PairFrameIDList.push_back( EFFECTSPRITETYPE_INSTALL_TRAP_ING_BACK );

	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_STONE_SKIN_ING_FRONT].PairFrameIDList.push_back( EFFECTSPRITETYPE_STONE_SKIN_ING_BACK );
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_STONE_SKIN_END_FRONT].PairFrameIDList.push_back( EFFECTSPRITETYPE_STONE_SKIN_END_BACK );

	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_EXPLOSION_WATER_START].PairFrameIDList.push_back( EFFECTSPRITETYPE_EXPLOSION_WATER_GROUND_START - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_EXPLOSION_WATER_START].PairFrameIDList.push_back( EFFECTSPRITETYPE_EXPLOSION_WATER_BACK_START - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_EXPLOSION_WATER_ING].PairFrameIDList.push_back( EFFECTSPRITETYPE_EXPLOSION_WATER_GROUND_ING - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_EXPLOSION_WATER_ING].PairFrameIDList.push_back( EFFECTSPRITETYPE_EXPLOSION_WATER_BACK_ING - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_EXPLOSION_WATER_END].PairFrameIDList.push_back( EFFECTSPRITETYPE_EXPLOSION_WATER_GROUND_END - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_EXPLOSION_WATER_END].PairFrameIDList.push_back( EFFECTSPRITETYPE_EXPLOSION_WATER_BACK_END - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );

	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_HELLFIRE_BODY].PairFrameIDList.push_back( EFFECTSPRITETYPE_HELLFIRE_BODY_GROUND - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );
	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_WATER_SHIELD_WATER].PairFrameIDList.push_back( EFFECTSPRITETYPE_WATER_SHIELD_SHIELD - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );

	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SWEEPER_NUMBER_1].PairFrameIDList.push_back( EFFECTSPRITETYPE_SWEEPER_1 );
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SWEEPER_NUMBER_2].PairFrameIDList.push_back( EFFECTSPRITETYPE_SWEEPER_2 );
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SWEEPER_NUMBER_3].PairFrameIDList.push_back( EFFECTSPRITETYPE_SWEEPER_3 );
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SWEEPER_NUMBER_4].PairFrameIDList.push_back( EFFECTSPRITETYPE_SWEEPER_4 );
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SWEEPER_NUMBER_5].PairFrameIDList.push_back( EFFECTSPRITETYPE_SWEEPER_5 );
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SWEEPER_NUMBER_6].PairFrameIDList.push_back( EFFECTSPRITETYPE_SWEEPER_6 );
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SWEEPER_NUMBER_7].PairFrameIDList.push_back( EFFECTSPRITETYPE_SWEEPER_7 );
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SWEEPER_NUMBER_8].PairFrameIDList.push_back( EFFECTSPRITETYPE_SWEEPER_8 );
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SWEEPER_NUMBER_9].PairFrameIDList.push_back( EFFECTSPRITETYPE_SWEEPER_9 );
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SWEEPER_NUMBER_10].PairFrameIDList.push_back( EFFECTSPRITETYPE_SWEEPER_10 );
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SWEEPER_NUMBER_11].PairFrameIDList.push_back( EFFECTSPRITETYPE_SWEEPER_11 );
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SWEEPER_NUMBER_12].PairFrameIDList.push_back( EFFECTSPRITETYPE_SWEEPER_12 );

	for(int cp=EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_STOP_1;cp<=EFFECTSPRITETYPE_CHARGING_POWER_MALE_SKILL_SLOW_5;)
	{
		(*g_pEffectSpriteTypeTable)[cp].PairFrameIDList.push_back(cp+1);
		(*g_pEffectSpriteTypeTable)[cp].PairFrameIDList.push_back(cp+2);
		(*g_pEffectSpriteTypeTable)[cp].PairFrameIDList.push_back(cp+3);
		(*g_pEffectSpriteTypeTable)[cp].PairFrameIDList.push_back(cp+4);
		cp+=5;
	}
#if __CONTENTS(__EFFECT_RENEWAL)
	//기존에 차징 파워 배열을 만들지 않고 처리 해서 별수 없다. 후인이 나타나 본디 방식으로 배열 만들어서 정리해주길 게다가 징그러운 6.0버그까지...
	for (int dp = EFFECTSPRITETYPE_CHARGING_POWER_MALE_DRIN_1; dp <=EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_BLADE_2_REPEAT_5;)
	{
		(*g_pEffectSpriteTypeTable)[dp].PairFrameIDList.push_back(dp+1);
		(*g_pEffectSpriteTypeTable)[dp].PairFrameIDList.push_back(dp+2);
		(*g_pEffectSpriteTypeTable)[dp].PairFrameIDList.push_back(dp+3);
		(*g_pEffectSpriteTypeTable)[dp].PairFrameIDList.push_back(dp+4);
		dp += 5;
	}
#endif //__EFFECT_RENEWAL
	for(cp = EFFECTSPRITETYPE_HAS_SWEEPER_1;cp <= EFFECTSPRITETYPE_HAS_SWEEPER_12; cp+=3 )
	{
		(*g_pEffectSpriteTypeTable)[cp].PairFrameIDList.push_back( EFFECTSPRITETYPE_HAS_SWEEPER_WHITE );
		(*g_pEffectSpriteTypeTable)[cp].bPairFrameBack = true;
		(*g_pEffectSpriteTypeTable)[cp+1].PairFrameIDList.push_back( EFFECTSPRITETYPE_HAS_SWEEPER_ORANGE );
		(*g_pEffectSpriteTypeTable)[cp+1].bPairFrameBack = true;
		(*g_pEffectSpriteTypeTable)[cp+2].PairFrameIDList.push_back( EFFECTSPRITETYPE_HAS_SWEEPER_GREEN );		
		(*g_pEffectSpriteTypeTable)[cp+2].bPairFrameBack = true;
	}
//	for(cp = EFFECTSPRITETYPE_SWEEPER_NUMBER_1;cp <= EFFECTSPRITETYPE_SWEEPER_NUMBER_12; cp+=3 )
//	{
//		(*g_pEffectSpriteTypeTable)[cp].PairFrameIDList.push_back( EFFECTSPRITETYPE_SWEEPER_WHITE - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );
//		(*g_pEffectSpriteTypeTable)[cp+1].PairFrameIDList.push_back( EFFECTSPRITETYPE_SWEEPER_ORANGE - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );
//		(*g_pEffectSpriteTypeTable)[cp+2].PairFrameIDList.push_back( EFFECTSPRITETYPE_SWEEPER_GREEN - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );		
//	}


//	EFFECTSPRITETYPE_JABBING_VEIN_FRONT_GOLEMER,
//	EFFECTSPRITETYPE_JABBING_VEIN_FRONT_ALCAN,
//	EFFECTSPRITETYPE_JABBING_VEIN_FRONT_BAT,

//	EFFECTSPRITETYPE_JABBING_VEIN_REAR_GOLEMER,
//	EFFECTSPRITETYPE_JABBING_VEIN_REAR_ALCAN,
//	EFFECTSPRITETYPE_JABBING_VEIN_REAR_BAT,

	
//	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_ILLUSION_OF_AVENGE].PairFrameIDList.push_back( EFFECTSPRITETYPE_ILLUSION_OF_AVENGE_TILE - MAX_EFFECTSPRITETYPE_ALPHAEFFECT );
	
	

	//------------------------------------------------------------
	// MASTER_DIE
	//------------------------------------------------------------
//	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MASTER_DIE_FIRE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MASTER_DIE_ROCK_BACK - MAX_EFFECTSPRITETYPE_SCREENEFFECT );	
//	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MASTER_DIE_FIRE].PairFrameIDList.push_back( EFFECTSPRITETYPE_MASTER_DIE_ROCK_FRONT - MAX_EFFECTSPRITETYPE_SCREENEFFECT );	

	//------------------------------------------------------------
	// MENTAL_SWORD
	//------------------------------------------------------------
//	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_MENTALSWORD_DAMAGE_BACK].PairFrameIDList.push_back( EFFECTSPRITETYPE_MENTALSWORD_DAMAGE_FRONT );		

	//------------------------------------------------------------
	// DARKBLUE_POISON 바뀐거
	//------------------------------------------------------------
	const int darkbluePoisonNumPairs = 6;
	const int darkbluePoisonPairFrames[darkbluePoisonNumPairs] = 
	{
		EFFECTSPRITETYPE_DARKBLUE_POISON_BACK_3,
		EFFECTSPRITETYPE_DARKBLUE_POISON_FRONT_3,
		EFFECTSPRITETYPE_DARKBLUE_POISON_BACK_1,
		EFFECTSPRITETYPE_DARKBLUE_POISON_FRONT_1,
		EFFECTSPRITETYPE_DARKBLUE_POISON_BACK_2,
		EFFECTSPRITETYPE_DARKBLUE_POISON_FRONT_2
	};

	for (pf=0; pf<darkbluePoisonNumPairs; pf+=2)
	{
		int back = darkbluePoisonPairFrames[pf];
		int front = darkbluePoisonPairFrames[pf+1];
		
		(*g_pEffectSpriteTypeTable)[back].PairFrameIDList.push_back( front );
	}

	//------------------------------------------------------------
	// BLINDNESS
	//------------------------------------------------------------
	const int blindnessNumPairs = 6;
	const int blindnessPairFrames[blindnessNumPairs] = 
	{
		EFFECTSPRITETYPE_BLINDNESS_BACK_3,
		EFFECTSPRITETYPE_BLINDNESS_FRONT_3,
		EFFECTSPRITETYPE_BLINDNESS_BACK_1,
		EFFECTSPRITETYPE_BLINDNESS_FRONT_1,
		EFFECTSPRITETYPE_BLINDNESS_BACK_2,
		EFFECTSPRITETYPE_BLINDNESS_FRONT_2,	
	};

	for (pf=0; pf<blindnessNumPairs; pf+=2)
	{
		int back = blindnessPairFrames[pf];
		int front = blindnessPairFrames[pf+1];
		
		(*g_pEffectSpriteTypeTable)[back].PairFrameIDList.push_back( front );
	}

//	//------------------------------------------------------------
//	// SWORD_OF_THOR
//	//------------------------------------------------------------
//	const int SWORD_OF_THORNumPairs = 5;
//	const int SWORD_OF_THORPairFrames[SWORD_OF_THORNumPairs] = 
//	{
//		EFFECTSPRITETYPE_SWORD_OF_THOR_LOOP_SWORD,
//		EFFECTSPRITETYPE_SWORD_OF_THOR_EXPLODE,
//		EFFECTSPRITETYPE_SWORD_OF_THOR_LOOP_GROUND,
//		EFFECTSPRITETYPE_SWORD_OF_THOR_LOOP_ELECTIRIC_1,
//		EFFECTSPRITETYPE_SWORD_OF_THOR_LOOP_ELECTIRIC_2,
//	};
//
//	for (pf=0; pf<blindnessNumPairs-1; pf++)
//	{
//		(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SWORD_OF_THOR_LOOP_SWORD].PairFrameIDList.push_back( pf + 1 );
//	}
	
	//------------------------------------------------------------
	// Pet Effects
	//------------------------------------------------------------
	int petEffectNumPairs = 12;
	int petEffectIndex = EFFECTSPRITETYPE_PET_EFFECT_WOLF_LIGHT_SKYBLUE_BEHIND;
	for(pf = 0; pf < petEffectNumPairs; ++pf)
	{
		(*g_pEffectSpriteTypeTable)[petEffectIndex].PairFrameIDList.push_back(petEffectIndex + 1);
		petEffectIndex += 2;
	}

	//------------------------------------------------------------
	// Rare Skill
	//------------------------------------------------------------
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_CURSE_OF_BLOOD_TARGET_GROUND_REPEAT].PairFrameIDList.push_back(EFFECTSPRITETYPE_CURSE_OF_BLOOD_TARGET_HANDS_REPEAT);
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BLOODY_SHOUT_RED_LIGHT_BACK].PairFrameIDList.push_back(EFFECTSPRITETYPE_BLOODY_SHOUT_RED_LIGHT_FRONT);
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BLOODY_SHOUT_ROTATE_LIGHT_BACK].PairFrameIDList.push_back(EFFECTSPRITETYPE_BLOODY_SHOUT_ROTATE_LIGHT_FRONT);

	//------------------------------------------------------------
	//
	//				ColorGroupMap 설정
	//
	//	같은 모양에 색상만 다른 이팩트들을 추가해준다.
	//
	//------------------------------------------------------------

	EFFECTSPRITETYPETABLE_INFO::COLORGROUP_MAP *pColorGroupMap = NULL;
	
	pColorGroupMap = &(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_MOVE_BLACK].ColorGroupMap;
	(*pColorGroupMap)[36]	= EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_MOVE_RED;
	(*pColorGroupMap)[6]	= EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_MOVE_BLUE;
	(*pColorGroupMap)[0]	= EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_MOVE_BLACK;
	(*pColorGroupMap)[262]	= EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_MOVE_GREEN;

	
	pColorGroupMap = &(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_STAND_BLACK].ColorGroupMap;
	(*pColorGroupMap)[36]	= EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_STAND_RED;
	(*pColorGroupMap)[6]	= EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_STAND_BLUE;
	(*pColorGroupMap)[0]	= EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_STAND_BLACK;
	(*pColorGroupMap)[262]	= EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_STAND_GREEN;

#if __CONTENTS(__FAST_TRANSFORTER)	
	pColorGroupMap = &(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_VAMPIRE_WING_MOVE_GRAY].ColorGroupMap;
	(*pColorGroupMap)[0]	= EFFECTSPRITETYPE_VAMPIRE_WING_MOVE_GRAY;
	(*pColorGroupMap)[1]	= EFFECTSPRITETYPE_VAMPIRE_WING_MOVE_RED;
	(*pColorGroupMap)[2]	= EFFECTSPRITETYPE_VAMPIRE_WING_MOVE_BLUE;
	(*pColorGroupMap)[3]	= EFFECTSPRITETYPE_VAMPIRE_WING_MOVE_GREEN;
	(*pColorGroupMap)[4]	= EFFECTSPRITETYPE_VAMPIRE_WING_MOVE_ORANGE;
	
	pColorGroupMap = &(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_VAMPIRE_WING_STOP_GRAY].ColorGroupMap;
	(*pColorGroupMap)[0]	= EFFECTSPRITETYPE_VAMPIRE_WING_STOP_GRAY;
	(*pColorGroupMap)[1]	= EFFECTSPRITETYPE_VAMPIRE_WING_STOP_RED;
	(*pColorGroupMap)[2]	= EFFECTSPRITETYPE_VAMPIRE_WING_STOP_BLUE;
	(*pColorGroupMap)[3]	= EFFECTSPRITETYPE_VAMPIRE_WING_STOP_GREEN;
	(*pColorGroupMap)[4]	= EFFECTSPRITETYPE_VAMPIRE_WING_STOP_ORANGE;

	pColorGroupMap = &(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_BLUE_MOVE].ColorGroupMap;
	(*pColorGroupMap)[0]	= EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_WHITE_MOVE;
	(*pColorGroupMap)[1]	= EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_ORANGE_MOVE;
	(*pColorGroupMap)[2]	= EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_YELLOW_MOVE;
	(*pColorGroupMap)[3]	= EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_RED_MOVE;
	(*pColorGroupMap)[4]	= EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_YELLOWGREEN_MOVE;
	(*pColorGroupMap)[5]	= EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_BLUEGREEN_MOVE;
	(*pColorGroupMap)[6]	= EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_VIOLET_MOVE;
	(*pColorGroupMap)[7]	= EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_BLUE_MOVE;

	pColorGroupMap = &(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_BLUE_STOP].ColorGroupMap;
	(*pColorGroupMap)[0]	= EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_WHITE_STOP;
	(*pColorGroupMap)[1]	= EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_ORANGE_STOP;
	(*pColorGroupMap)[2]	= EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_YELLOW_STOP;
	(*pColorGroupMap)[3]	= EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_RED_STOP;
	(*pColorGroupMap)[4]	= EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_YELLOWGREEN_STOP;
	(*pColorGroupMap)[5]	= EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_BLUEGREEN_STOP;
	(*pColorGroupMap)[6]	= EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_VIOLET_STOP;
	(*pColorGroupMap)[7]	= EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_BLUE_STOP;

	pColorGroupMap = &(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SLAYER_WING_BIKE_MOVE].ColorGroupMap;
	(*pColorGroupMap)[0]	= EFFECTSPRITETYPE_SLAYER_WING_BIKE_MOVE;
	pColorGroupMap = &(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SLAYER_WING_BIKE_STOP].ColorGroupMap;
	(*pColorGroupMap)[0]	= EFFECTSPRITETYPE_SLAYER_WING_BIKE_STOP;
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
	pColorGroupMap = &(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_WHITE].ColorGroupMap;
	(*pColorGroupMap)[0]	= EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_WHITE;
	(*pColorGroupMap)[1]	= EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_RED;
	(*pColorGroupMap)[2]	= EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_YELLOW;
	(*pColorGroupMap)[3]	= EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_BLUEGREEN;
	(*pColorGroupMap)[4]	= EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_BLUE;
	(*pColorGroupMap)[5]	= EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_MAZANTA;
	(*pColorGroupMap)[6]	= EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_VIOLET;
	(*pColorGroupMap)[7]	= EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_BLACK;

	pColorGroupMap = &(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_WHITE].ColorGroupMap;
	(*pColorGroupMap)[0]	= EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_WHITE;
	(*pColorGroupMap)[1]	= EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_RED;
	(*pColorGroupMap)[2]	= EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_YELLOW;
	(*pColorGroupMap)[3]	= EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_BLUEGREEN;
	(*pColorGroupMap)[4]	= EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_BLUE;
	(*pColorGroupMap)[5]	= EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_MAZANTA;
	(*pColorGroupMap)[6]	= EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_VIOLET;
	(*pColorGroupMap)[7]	= EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_BLACK;

	pColorGroupMap = &(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_OUSTERS_UNICORN_MOVE_WHITE].ColorGroupMap;
	(*pColorGroupMap)[0]	= EFFECTSPRITETYPE_OUSTERS_UNICORN_MOVE_WHITE;
	(*pColorGroupMap)[1]	= EFFECTSPRITETYPE_OUSTERS_UNICORN_MOVE_RED;
	(*pColorGroupMap)[2]	= EFFECTSPRITETYPE_OUSTERS_UNICORN_MOVE_YELLOW;
	(*pColorGroupMap)[3]	= EFFECTSPRITETYPE_OUSTERS_UNICORN_MOVE_YELLOWGREEN;
	(*pColorGroupMap)[4]	= EFFECTSPRITETYPE_OUSTERS_UNICORN_MOVE_BLUE;
	(*pColorGroupMap)[5]	= EFFECTSPRITETYPE_OUSTERS_UNICORN_MOVE_MAZANTA;

	pColorGroupMap = &(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_OUSTERS_UNICORN_STOP_WHITE].ColorGroupMap;
	(*pColorGroupMap)[0]	= EFFECTSPRITETYPE_OUSTERS_UNICORN_STOP_WHITE;
	(*pColorGroupMap)[1]	= EFFECTSPRITETYPE_OUSTERS_UNICORN_STOP_RED;
	(*pColorGroupMap)[2]	= EFFECTSPRITETYPE_OUSTERS_UNICORN_STOP_YELLOW;
	(*pColorGroupMap)[3]	= EFFECTSPRITETYPE_OUSTERS_UNICORN_STOP_YELLOWGREEN;
	(*pColorGroupMap)[4]	= EFFECTSPRITETYPE_OUSTERS_UNICORN_STOP_BLUE;
	(*pColorGroupMap)[5]	= EFFECTSPRITETYPE_OUSTERS_UNICORN_STOP_MAZANTA;

//	pColorGroupMap = &(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SLAYER_HOVER_VEHICLE_MOVE].ColorGroupMap;
//	(*pColorGroupMap)[0]	= EFFECTSPRITETYPE_SLAYER_HOVER_VEHICLE_MOVE;
//	pColorGroupMap = &(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SLAYER_HOVER_VEHICLE_STOP].ColorGroupMap;
//	(*pColorGroupMap)[0]	= EFFECTSPRITETYPE_SLAYER_HOVER_VEHICLE_STOP;
#endif //__SECOND_TRANSFORTER
	
	//------------------------------------------------------------
	//
	//				ActionEffectFrame설정
	//
	//------------------------------------------------------------
	const int numHPBOOSTESTMale = 12;
	const int HPBOOSTESTMale[numHPBOOSTESTMale] = 
	{
		EFFECTSPRITETYPE_HPBOOST_STAND_MALE,
		EFFECTSPRITETYPE_HPBOOST_MOVE_MALE,
		EFFECTSPRITETYPE_HPBOOST_ATTACK_MALE,
		EFFECTSPRITETYPE_HPBOOST_MAGIC_MALE,
		EFFECTSPRITETYPE_HPBOOST_DAMAGE_MALE,
		EFFECTSPRITETYPE_HPBOOST_SWORD_FAST_MALE,
		EFFECTSPRITETYPE_HPBOOST_SWORD2_FAST_MALE,
		EFFECTSPRITETYPE_HPBOOST_SWORD_MALE,
		EFFECTSPRITETYPE_HPBOOST_SWORD_SLOW_MALE,
		EFFECTSPRITETYPE_HPBOOST_SWORD2_SLOW_MALE,
		EFFECTSPRITETYPE_HPBOOST_SWORD2_MALE,
		EFFECTSPRITETYPE_HPBOOST_THROW_MALE,
	};

	const int numHPBOOSTESTFemale = 12;
	const int HPBOOSTESTFemale[numHPBOOSTESTFemale] =
	{
		EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE,
		EFFECTSPRITETYPE_HPBOOST_MOVE_FEMALE,
		EFFECTSPRITETYPE_HPBOOST_ATTACK_FEMALE,
		EFFECTSPRITETYPE_HPBOOST_MAGIC_FEMALE,
		EFFECTSPRITETYPE_HPBOOST_DAMAGE_FEMALE,
		EFFECTSPRITETYPE_HPBOOST_SWORD_FAST_FEMALE,
		EFFECTSPRITETYPE_HPBOOST_SWORD2_SLOW_FEMALE,
		EFFECTSPRITETYPE_HPBOOST_SWORD_FEMALE,
		EFFECTSPRITETYPE_HPBOOST_SWORD_SLOW_FEMALE,
		EFFECTSPRITETYPE_HPBOOST_SWORD2_FAST_FEMALE,
		EFFECTSPRITETYPE_HPBOOST_SWORD2_FEMALE,
		EFFECTSPRITETYPE_HPBOOST_THROW_FEMALE,
	};

#if __CONTENTS(__EFFECT_RENEWAL)
	const int numRegenESTMale = 88;
#else
	const int numRegenESTMale = 32;
#endif //__EFFECT_RENEWAL
	const int regenESTMale[numRegenESTMale] =
	{
		EFFECTSPRITETYPE_REGENERATION_1_STAND_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_STAND_MALE ,
		EFFECTSPRITETYPE_REGENERATION_1_MOVE_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_MOVE_MALE ,
		EFFECTSPRITETYPE_REGENERATION_1_ATTACK_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_ATTACK_MALE ,
		EFFECTSPRITETYPE_REGENERATION_1_MAGIC_MALE	,
		EFFECTSPRITETYPE_REGENERATION_2_MAGIC_MALE ,
		EFFECTSPRITETYPE_REGENERATION_1_DAMAGE_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_DAMAGE_MALE ,
		EFFECTSPRITETYPE_REGENERATION_1_AR_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_AR_MALE ,
		EFFECTSPRITETYPE_REGENERATION_1_SR_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SR_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD_MALE ,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE_MALE ,
		EFFECTSPRITETYPE_REGENERATION_1_THROW_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_THROW_MALE ,
		EFFECTSPRITETYPE_REGENERATION_1_MOTOR_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_MOTOR_MALE ,
		EFFECTSPRITETYPE_REGENERATION_1_SG_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SG_MALE ,
		EFFECTSPRITETYPE_REGENERATION_1_SMG_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SMG_MALE ,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD2_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD2_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE2_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE2_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_THROW2_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_THROW2_MALE,
#if __CONTENTS(__EFFECT_RENEWAL)
		EFFECTSPRITETYPE_REGENERATION_1_MAGIC_ATTACK_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_MAGIC_ATTACK_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_DRAIN_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_DRAIN_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_DIE_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_DIE_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_BIKE_MOVE_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_BIKE_MOVE_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_BIKE_STOP_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_BIKE_STOP_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SR_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SR_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SR_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SR_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_AR_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_AR_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_AR_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_AR_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SG_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SG_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SG_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SG_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SMG_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SMG_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SMG_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SMG_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD2_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD2_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD2_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD2_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE2_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE2_SLOW_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE2_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE2_FAST_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_BATTLE_STAND_GUN_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_BATTLE_STAND_GUN_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_BATTLE_STAND_SWORD_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_BATTLE_STAND_SWORD_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_BATTLE_STAND_BLADE_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_BATTLE_STAND_BLADE_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_MOVE_GUN_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_MOVE_GUN_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_MAGIC_CASTING_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_MAGIC_CASTING_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD_2_REPEAT_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD_2_REPEAT_MALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE_2_REPEAT_MALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE_2_REPEAT_MALE
#endif//__EFFECT_RENEWAL
	};
#if __CONTENTS(__EFFECT_RENEWAL)
	const int numRegenESTFemale = 88;
#else
	const int numRegenESTFemale = 32;
#endif //__EFFECT_RENEWAL

	const int regenESTFemale[numRegenESTFemale] =
	{
		EFFECTSPRITETYPE_REGENERATION_1_STAND_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_STAND_FEMALE ,
		EFFECTSPRITETYPE_REGENERATION_1_MOVE_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_MOVE_FEMALE ,
		EFFECTSPRITETYPE_REGENERATION_1_ATTACK_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_ATTACK_FEMALE ,
		EFFECTSPRITETYPE_REGENERATION_1_MAGIC_FEMALE	,
		EFFECTSPRITETYPE_REGENERATION_2_MAGIC_FEMALE ,
		EFFECTSPRITETYPE_REGENERATION_1_DAMAGE_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_DAMAGE_FEMALE ,
		EFFECTSPRITETYPE_REGENERATION_1_AR_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_AR_FEMALE ,
		EFFECTSPRITETYPE_REGENERATION_1_SR_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SR_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD_FEMALE ,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE_FEMALE ,
		EFFECTSPRITETYPE_REGENERATION_1_THROW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_THROW_FEMALE ,
		EFFECTSPRITETYPE_REGENERATION_1_MOTOR_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_MOTOR_FEMALE ,
		EFFECTSPRITETYPE_REGENERATION_1_SG_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SG_FEMALE ,
		EFFECTSPRITETYPE_REGENERATION_1_SMG_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SMG_FEMALE ,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD2_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD2_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE2_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE2_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_THROW2_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_THROW2_FEMALE,
#if __CONTENTS(__EFFECT_RENEWAL)
		EFFECTSPRITETYPE_REGENERATION_1_MAGIC_ATTACK_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_MAGIC_ATTACK_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_DRAIN_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_DRAIN_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_DIE_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_DIE_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_BIKE_MOVE_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_BIKE_MOVE_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_BIKE_STOP_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_BIKE_STOP_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SR_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SR_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SR_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SR_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_AR_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_AR_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_AR_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_AR_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SG_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SG_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SG_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SG_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SMG_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SMG_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SMG_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SMG_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD2_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD2_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD2_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD2_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE2_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE2_SLOW_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE2_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE2_FAST_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_BATTLE_STAND_GUN_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_BATTLE_STAND_GUN_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_BATTLE_STAND_SWORD_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_BATTLE_STAND_SWORD_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_BATTLE_STAND_BLADE_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_BATTLE_STAND_BLADE_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_MOVE_GUN_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_MOVE_GUN_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_MAGIC_CASTING_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_MAGIC_CASTING_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_SWORD_2_REPEAT_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_SWORD_2_REPEAT_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_1_BLADE_2_REPEAT_FEMALE,
		EFFECTSPRITETYPE_REGENERATION_2_BLADE_2_REPEAT_FEMALE
#endif //__EFFECT_RENEWAL
	};

#if __CONTENTS(__FAST_TRANSFORTER)
	const int numOUSTERSWINGBLUE = 2;
	const int OUSTERSWINGBLUE[numOUSTERSWINGBLUE] = 
	{
		EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_BLUE_MOVE,
		EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_BLUE_STOP,
	};

	const int numOUSTERSWINGYELLOW = 2;
	const int OUSTERSWINGYELLOW[numOUSTERSWINGYELLOW] = 
	{
		EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_YELLOW_MOVE,
		EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_YELLOW_STOP,
	};

	const int numOUSTERSWINGRED = 2;
	const int OUSTERSWINGRED[numOUSTERSWINGRED] = 
	{
		EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_RED_MOVE,
		EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_RED_STOP,
	};

	const int numOUSTERSWINGORANGE = 2;
	const int OUSTERSWINGORANGE[numOUSTERSWINGORANGE] = 
	{
		EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_ORANGE_MOVE,
		EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_ORANGE_STOP,
	};

	const int numOUSTERSWINGYELLOWGREEN = 2;
	const int OUSTERSWINGYELLOWGREEN[numOUSTERSWINGYELLOWGREEN] = 
	{
		EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_YELLOWGREEN_MOVE,
		EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_YELLOWGREEN_STOP,
	};

	const int numOUSTERSWINGBLUEGREEN = 2;
	const int OUSTERSWINGBLUEGREEN[numOUSTERSWINGBLUEGREEN] = 
	{
		EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_BLUEGREEN_MOVE,
		EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_BLUEGREEN_STOP,
	};

	const int numOUSTERSWINGVIOLET = 2;
	const int OUSTERSWINGVIOLET[numOUSTERSWINGVIOLET] = 
	{
		EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_VIOLET_MOVE,
		EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_VIOLET_STOP,
	};

	const int numOUSTERSWINGWHITE = 2;
	const int OUSTERSWINGWHITE[numOUSTERSWINGWHITE] = 
	{
		EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_WHITE_MOVE,
		EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_WHITE_STOP,
	};

	const int numSLAYERWING = 2;
	const int SLAYERWING[numSLAYERWING] = 
	{
		EFFECTSPRITETYPE_SLAYER_WING_BIKE_MOVE,
		EFFECTSPRITETYPE_SLAYER_WING_BIKE_STOP,
	};

#endif //__FAST_TRANSFORTER

#if __CONTENTS(__SECOND_TRANSFORTER)
	const int numOUSTERSUNICORN_WHITE = 2;
	const int OUSTERSUNICORN_WHITE[numOUSTERSUNICORN_WHITE] = 
	{
		EFFECTSPRITETYPE_OUSTERS_UNICORN_MOVE_WHITE,
		EFFECTSPRITETYPE_OUSTERS_UNICORN_STOP_WHITE,
	};

	const int numOUSTERSUNICORN_RED = 2;
	const int OUSTERSUNICORN_RED[numOUSTERSUNICORN_RED] = 
	{
		EFFECTSPRITETYPE_OUSTERS_UNICORN_MOVE_RED,
		EFFECTSPRITETYPE_OUSTERS_UNICORN_STOP_RED,
	};

	const int numOUSTERSUNICORN_YELLOW = 2;
	const int OUSTERSUNICORN_YELLOW[numOUSTERSUNICORN_YELLOW] = 
	{
		EFFECTSPRITETYPE_OUSTERS_UNICORN_MOVE_YELLOW,
		EFFECTSPRITETYPE_OUSTERS_UNICORN_STOP_YELLOW,
	};

	const int numOUSTERSUNICORN_YELLOWGREEN = 2;
	const int OUSTERSUNICORN_YELLOWGREEN[numOUSTERSUNICORN_YELLOWGREEN] = 
	{
		EFFECTSPRITETYPE_OUSTERS_UNICORN_MOVE_YELLOWGREEN,
		EFFECTSPRITETYPE_OUSTERS_UNICORN_STOP_YELLOWGREEN,
	};

	const int numOUSTERSUNICORN_BLUE = 2;
	const int OUSTERSUNICORN_BLUE[numOUSTERSUNICORN_BLUE] = 
	{
		EFFECTSPRITETYPE_OUSTERS_UNICORN_MOVE_BLUE,
		EFFECTSPRITETYPE_OUSTERS_UNICORN_STOP_BLUE,
	};

	const int numOUSTERSUNICORN_MAZANTA = 2;
	const int OUSTERSUNICORN_MAZANTA[numOUSTERSUNICORN_MAZANTA] = 
	{
		EFFECTSPRITETYPE_OUSTERS_UNICORN_MOVE_MAZANTA,
		EFFECTSPRITETYPE_OUSTERS_UNICORN_STOP_MAZANTA,
	};

	const int numSLAYERHOVERVEHICLE = 2;
	const int SLAYERHOVERVEHICLE[numSLAYERHOVERVEHICLE] = 
	{
		EFFECTSPRITETYPE_SLAYER_WING_BIKE_MOVE,
		EFFECTSPRITETYPE_SLAYER_WING_BIKE_STOP,
	};
#endif //__SECOND_TRANSFORTER

#if __CONTENTS(__EFFECT_RENEWAL)
	const int numBERSERKERESTMale = 68;
#else
	const int numBERSERKERESTMale = 40;
#endif //__EFFECT_RENEWAL

	const int BERSERKERESTMale[numBERSERKERESTMale] = 
	{
		EFFECTSPRITETYPE_BERSERKER_1_STAND_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_STAND_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_STAND_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_STAND_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_MOVE_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_MOVE_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_MOVE_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_MOVE_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_MAGIC_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_MAGIC_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_MAGIC_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_MAGIC_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_DAMAGE_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_DAMAGE_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_DAMAGE_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_DAMAGE_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE2_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE2_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE2_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE2_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE2_FAST_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE2_FAST_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE2_FAST_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE2_FAST_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE2_SLOW_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE2_SLOW_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE2_SLOW_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE2_SLOW_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE_FAST_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE_FAST_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE_FAST_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE_FAST_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE_SLOW_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE_SLOW_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE_SLOW_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE_SLOW_MALE,
#if __CONTENTS(__EFFECT_RENEWAL)
		EFFECTSPRITETYPE_BERSERKER_1_DRAIN_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_DRAIN_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_DRAIN_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_DRAIN_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_DIE_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_DIE_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_DIE_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_DIE_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_MOTOR_MOVE_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_MOTOR_MOVE_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_MOTOR_MOVE_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_MOTOR_MOVE_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_MOTOR_STAND_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_MOTOR_STAND_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_MOTOR_STAND_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_MOTOR_STAND_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_BATTLE_STAND_BLADE_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_BATTLE_STAND_BLADE_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_BATTLE_STAND_BLADE_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_BATTLE_STAND_BLADE_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_MAGIC_CASTING_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_MAGIC_CASTING_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_MAGIC_CASTING_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_MAGIC_CASTING_MALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE_2_REPEAT_MALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE_2_REPEAT_MALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE_2_REPEAT_MALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE_2_REPEAT_MALE,
#endif //__EFFECT_RENEWAL
	};
#if __CONTENTS(__EFFECT_RENEWAL)
	const int numBERSERKERESTFemale = 68;
#else
	const int numBERSERKERESTFemale = 40;
#endif //__EFFECT_RENEWAL
	const int BERSERKERESTFemale[numBERSERKERESTFemale] =
	{
		EFFECTSPRITETYPE_BERSERKER_1_STAND_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_STAND_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_STAND_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_STAND_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_MOVE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_MOVE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_MOVE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_MOVE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_MAGIC_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_MAGIC_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_MAGIC_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_MAGIC_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_DAMAGE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_DAMAGE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_DAMAGE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_DAMAGE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE2_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE2_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE2_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE2_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE2_FAST_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE2_FAST_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE2_FAST_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE2_FAST_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE2_SLOW_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE2_SLOW_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE2_SLOW_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE2_SLOW_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE_FAST_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE_FAST_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE_FAST_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE_FAST_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE_SLOW_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE_SLOW_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE_SLOW_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE_SLOW_FEMALE,
#if __CONTENTS(__EFFECT_RENEWAL)
		EFFECTSPRITETYPE_BERSERKER_1_DRAIN_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_DRAIN_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_DRAIN_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_DRAIN_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_DIE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_DIE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_DIE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_DIE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_MOTOR_MOVE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_MOTOR_MOVE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_MOTOR_MOVE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_MOTOR_MOVE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_MOTOR_STAND_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_MOTOR_STAND_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_MOTOR_STAND_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_MOTOR_STAND_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_BATTLE_STAND_BLADE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_BATTLE_STAND_BLADE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_BATTLE_STAND_BLADE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_BATTLE_STAND_BLADE_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_MAGIC_CASTING_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_MAGIC_CASTING_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_MAGIC_CASTING_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_MAGIC_CASTING_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_1_BLADE_2_REPEAT_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_2_BLADE_2_REPEAT_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_3_BLADE_2_REPEAT_FEMALE,
		EFFECTSPRITETYPE_BERSERKER_4_BLADE_2_REPEAT_FEMALE,
#endif //__EFFECT_RENEWAL
	};

//	const int numHypnosisESTMale = 7;
//	const int HypnosisESTMale[numHypnosisESTMale] = 
//	{
//		EFFECTSPRITETYPE_HYPNOSIS_ATTACK_SLOW_MALE,
//		EFFECTSPRITETYPE_HYPNOSIS_MALE_MAGIC,
//		EFFECTSPRITETYPE_HYPNOSIS_ATTACK_MALE,
//		EFFECTSPRITETYPE_HYPNOSIS_MOVE_MALE,
//		EFFECTSPRITETYPE_HYPNOSIS_DAMAGE_MALE,
//		EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,
//		EFFECTSPRITETYPE_HYPNOSIS_ATTACK_FAST_MALE
//	};
//
//	const int numHypnosisESTFemale = 7;
//	const int HypnosisESTFemale[numHypnosisESTFemale] = 
//	{
//		EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,
//		EFFECTSPRITETYPE_HYPNOSIS_ATTACK_FAST_FEMALE,
//		EFFECTSPRITETYPE_HYPNOSIS_ATTACK_SLOW_FEMALE,
//		EFFECTSPRITETYPE_HYPNOSIS_ATTACK_FEMALE,
//		EFFECTSPRITETYPE_HYPNOSIS_MAGIC_FEMALE,
//		EFFECTSPRITETYPE_HYPNOSIS_DAMAGE_FEMALE,
//		EFFECTSPRITETYPE_HYPNOSIS_MOVE_FEMALE		
//	};
#if __CONTENTS(__EFFECT_RENEWAL)
	const int numExtremeESTMale = 34;
#else
	const int numExtremeESTMale = 12;
#endif //__EFFECT_RENEWAL

	const int ExtremeESTMale[numExtremeESTMale] = 
	{
		EFFECTSPRITETYPE_EXTREME_L_1_STAND_MALE,	// 뱀파 어깨에 붙는 검은 기운.
		EFFECTSPRITETYPE_EXTREME_R_1_STAND_MALE,
		EFFECTSPRITETYPE_EXTREME_L_1_MOVE_MALE,
		EFFECTSPRITETYPE_EXTREME_R_1_MOVE_MALE,
		EFFECTSPRITETYPE_EXTREME_L_1_ATTACK_MALE,
		EFFECTSPRITETYPE_EXTREME_R_1_ATTACK_MALE,
		EFFECTSPRITETYPE_EXTREME_L_1_ATTACK_SLOW_MALE,
		EFFECTSPRITETYPE_EXTREME_R_1_ATTACK_SLOW_MALE,
		EFFECTSPRITETYPE_EXTREME_L_1_ATTACK_FAST_MALE,
		EFFECTSPRITETYPE_EXTREME_R_1_ATTACK_FAST_MALE,
		EFFECTSPRITETYPE_EXTREME_L_1_DAMAGE_MALE,
		EFFECTSPRITETYPE_EXTREME_R_1_DAMAGE_MALE,
#if __CONTENTS(__EFFECT_RENEWAL)
		EFFECTSPRITETYPE_EXTREME_L_MAGIC_ATTACK_MALE,
		EFFECTSPRITETYPE_EXTREME_R_MAGIC_ATTACK_MALE,
		EFFECTSPRITETYPE_EXTREME_L_DRIN_MALE,
		EFFECTSPRITETYPE_EXTREME_R_DRIN_MALE,
		EFFECTSPRITETYPE_EXTREME_L_DIE_MALE,
		EFFECTSPRITETYPE_EXTREME_R_DIE_MALE,
		EFFECTSPRITETYPE_EXTREME_L_DRIN_ATTACK_MALE,
		EFFECTSPRITETYPE_EXTREME_R_DRIN_ATTACK_MALE,
		EFFECTSPRITETYPE_EXTREME_L_ATTACK_2_MALE,
		EFFECTSPRITETYPE_EXTREME_R_ATTACK_2_MALE,
		EFFECTSPRITETYPE_EXTREME_L_ATTACK_2_SLOW_MALE,
		EFFECTSPRITETYPE_EXTREME_R_ATTACK_2_SLOW_MALE,
		EFFECTSPRITETYPE_EXTREME_L_ATTACK_2_FAST_MALE,
		EFFECTSPRITETYPE_EXTREME_R_ATTACK_2_FAST_MALE,
		EFFECTSPRITETYPE_EXTREME_L_ATTACK_3_MALE,
		EFFECTSPRITETYPE_EXTREME_R_ATTACK_3_MALE,
		EFFECTSPRITETYPE_EXTREME_L_ATTACK_3_SLOW_MALE,
		EFFECTSPRITETYPE_EXTREME_R_ATTACK_3_SLOW_MALE,
		EFFECTSPRITETYPE_EXTREME_L_ATTACK_3_FAST_MALE,
		EFFECTSPRITETYPE_EXTREME_R_ATTACK_3_FAST_MALE,
		EFFECTSPRITETYPE_EXTREME_L_MAGIC_CASTING_MALE,
		EFFECTSPRITETYPE_EXTREME_R_MAGIC_CASTING_MALE,
#endif //__EFFECT_RENEWAL
	};
#if __CONTENTS(__EFFECT_RENEWAL)
	const int numExtremeESTFemale = 34;
#else
	const int numExtremeESTFemale = 12;
#endif //__EFFECT_RENEWAL
	const int ExtremeESTFemale[numExtremeESTFemale] = 
	{		
		EFFECTSPRITETYPE_EXTREME_L_1_STAND_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_1_STAND_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_1_MOVE_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_1_MOVE_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_1_ATTACK_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_1_ATTACK_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_1_ATTACK_SLOW_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_1_ATTACK_SLOW_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_1_ATTACK_FAST_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_1_ATTACK_FAST_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_1_DAMAGE_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_1_DAMAGE_FEMALE,
#if __CONTENTS(__EFFECT_RENEWAL)
		EFFECTSPRITETYPE_EXTREME_L_MAGIC_ATTACK_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_MAGIC_ATTACK_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_DRIN_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_DRIN_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_DIE_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_DIE_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_DRIN_ATTACK_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_DRIN_ATTACK_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_ATTACK_2_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_ATTACK_2_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_ATTACK_2_SLOW_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_ATTACK_2_SLOW_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_ATTACK_2_FAST_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_ATTACK_2_FAST_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_ATTACK_3_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_ATTACK_3_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_ATTACK_3_SLOW_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_ATTACK_3_SLOW_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_ATTACK_3_FAST_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_ATTACK_3_FAST_FEMALE,
		EFFECTSPRITETYPE_EXTREME_L_MAGIC_CASTING_FEMALE,
		EFFECTSPRITETYPE_EXTREME_R_MAGIC_CASTING_FEMALE,
#endif //__EFFECT_RENEWAL
	};

	const int numSlayerGrandmasterESTMale = 31;
	const int SlayerGrandmasterESTMale[numSlayerGrandmasterESTMale] = 
	{		
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_STAND,			// 슬레-그랜드마스터-정지-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_MOVE,			// 슬레-그랜드마스터-걷기-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_ATTACK,		// 슬레-그랜드마스터-공격-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_MAGIC,			// 슬레-그랜드마스터-마법-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_DAMAGED,		// 슬레-그랜드마스터-맞기-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_THROW_WEAPON,	// 슬레-그랜드마스터-던지기-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_THROW_POTION,	// 슬레-그랜드마스터-던지기2-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SWORD_SLOW,	// 슬레-그랜드마스터-검S-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SWORD,			// 슬레-그랜드마스터-검-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SWORD_FAST,	// 슬레-그랜드마스터-검F-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_BLADE_SLOW,	// 슬레-그랜드마스터-도S-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_BLADE,			// 슬레-그랜드마스터-도-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_BLADE_FAST,	// 슬레-그랜드마스터-도F-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_AR_SLOW,		// 슬레-그랜드마스터-ARS-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_AR,			// 슬레-그랜드마스터-AR-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_AR_FAST,		// 슬레-그랜드마스터-ARF-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SR_SLOW,		// 슬레-그랜드마스터-SRS-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SR,			// 슬레-그랜드마스터-SR-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SR_FAST,		// 슬레-그랜드마스터-SRF-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SMG_SLOW,		// 슬레-그랜드마스터-SMGS-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SMG,			// 슬레-그랜드마스터-SMG-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SMG_FAST,		// 슬레-그랜드마스터-SMGF-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SG_SLOW,		// 슬레-그랜드마스터-SGS-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SG,			// 슬레-그랜드마스터-SG-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SG_FAST,		// 슬레-그랜드마스터-SGF-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SWORD_2_SLOW,	// 슬레-그랜드마스터-검기술S-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SWORD_2,		// 슬레-그랜드마스터-검기술-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SWORD_2_FAST,	// 슬레-그랜드마스터-검기술F-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_BLADE_2_SLOW,	// 슬레-그랜드마스터-도기술S-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_BLADE_2,		// 슬레-그랜드마스터-도기술-남자
		EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_BLADE_2_FAST,	// 슬레-그랜드마스터-도기술F-남자
	};

	const int numSlayerGrandmasterESTFemale = 31;
	const int SlayerGrandmasterESTFemale[numSlayerGrandmasterESTFemale] = 
	{		
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_STAND,			// 슬레-그랜드마스터-정지-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_MOVE,			// 슬레-그랜드마스터-걷기-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_ATTACK,			// 슬레-그랜드마스터-공격-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_MAGIC,			// 슬레-그랜드마스터-마법-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_DAMAGED,			// 슬레-그랜드마스터-맞기-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_THROW_WEAPON,	// 슬레-그랜드마스터-던지기-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_THROW_POTION,	// 슬레-그랜드마스터-던지기2-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SWORD_SLOW,		// 슬레-그랜드마스터-검S-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SWORD,			// 슬레-그랜드마스터-검-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SWORD_FAST,		// 슬레-그랜드마스터-검F-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_BLADE_SLOW,		// 슬레-그랜드마스터-도S-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_BLADE,			// 슬레-그랜드마스터-도-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_BLADE_FAST,		// 슬레-그랜드마스터-도F-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_AR_SLOW,			// 슬레-그랜드마스터-ARS-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_AR,				// 슬레-그랜드마스터-AR-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_AR_FAST,			// 슬레-그랜드마스터-ARF-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SR_SLOW,			// 슬레-그랜드마스터-SRS-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SR,				// 슬레-그랜드마스터-SR-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SR_FAST,			// 슬레-그랜드마스터-SRF-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SMG_SLOW,		// 슬레-그랜드마스터-SMGS-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SMG,				// 슬레-그랜드마스터-SMG-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SMG_FAST,		// 슬레-그랜드마스터-SMGF-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SG_SLOW,			// 슬레-그랜드마스터-SGS-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SG,				// 슬레-그랜드마스터-SG-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SG_FAST,			// 슬레-그랜드마스터-SGF-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SWORD_2_SLOW,	// 슬레-그랜드마스터-검기술S-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SWORD_2,			// 슬레-그랜드마스터-검기술-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SWORD_2_FAST,	// 슬레-그랜드마스터-검기술F-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_BLADE_2_SLOW,	// 슬레-그랜드마스터-도기술S-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_BLADE_2,			// 슬레-그랜드마스터-도기술-여자
		EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_BLADE_2_FAST,	// 슬레-그랜드마스터-도기술F-여자
	};

	const int numVampireGrandmasterESTMale = 16;
	const int VampireGrandmasterESTMale[numVampireGrandmasterESTMale] = 
	{		
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK,			// 뱀파이어-남자정지뒤
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_FRONT,			// 뱀파이어-남자정지앞
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_MAGIC_BACK,			// 뱀파이어-남자마법뒤
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_MAGIC_FRONT,			// 뱀파이어-남자마법앞
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_DAMAGED_BACK,			// 뱀파이어-남자맞기뒤
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_DAMAGED_FRONT,		// 뱀파이어-남자맞기앞
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_DRAINED_BACK,			// 뱀파이어-남자흡혈당하기뒤
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_DRAINED_FRONT,		// 뱀파이어-남자흡혈당하기앞
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_DRAIN_BACK,			// 뱀파이어-남자흡혈하기뒤
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_DRAIN_FRONT,			// 뱀파이어-남자흡혈하기앞
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_ATTACK_SLOW_BACK,		// 뱀파이어-남자공격뒤s
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_ATTACK_SLOW_FRONT,	// 뱀파이어-남자공격앞s
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_ATTACK_BACK,			// 뱀파이어-남자공격뒤n
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_ATTACK_FRONT,			// 뱀파이어-남자공격앞n
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_ATTACK_FAST_BACK,		// 뱀파이어-남자공격뒤f
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_ATTACK_FAST_FRONT,	// 뱀파이어-남자공격앞f
	};

	const int numVampireGrandmasterESTFemale = 16;
	const int VampireGrandmasterESTFemale[numVampireGrandmasterESTFemale] = 
	{		
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK,			// 뱀파이어-여자정지뒤
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_FRONT,		// 뱀파이어-여자정지앞
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_MAGIC_BACK,			// 뱀파이어-여자마법뒤
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_MAGIC_FRONT,		// 뱀파이어-여자마법앞
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_DAMAGED_BACK,		// 뱀파이어-여자맞기뒤
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_DAMAGED_FRONT,		// 뱀파이어-여자맞기앞
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_DRAINED_BACK,		// 뱀파이어-여자흡혈당하기뒤
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_DRAINED_FRONT,		// 뱀파이어-여자흡혈당하기앞
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_DRAIN_BACK,			// 뱀파이어-여자흡혈하기뒤
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_DRAIN_FRONT,		// 뱀파이어-여자흡혈하기앞
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_ATTACK_SLOW_BACK,	// 뱀파이어-여자공격뒤s
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_ATTACK_SLOW_FRONT,	// 뱀파이어-여자공격앞s
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_ATTACK_BACK,		// 뱀파이어-여자공격뒤n
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_ATTACK_FRONT,		// 뱀파이어-여자공격앞n
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_ATTACK_FAST_BACK,	// 뱀파이어-여자공격뒤f
		EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_ATTACK_FAST_FRONT,	// 뱀파이어-여자공격앞f
	};
	

	


	const int numBloodBibleEST = 12;

	const int BloodBibleEst[numBloodBibleEST] = 
	{
		EFFECTSPRITETYPE_GREGORI,					// 그리고리 이펙트(머리위에)
		EFFECTSPRITETYPE_NEMA,						// 네마
		EFFECTSPRITETYPE_LEGIOS,					// 레지오스
		EFFECTSPRITETYPE_MIHOLE,					// 미호레
		EFFECTSPRITETYPE_AROSA,						// 아로사
		EFFECTSPRITETYPE_ARMEGA,					// 아르메가
		EFFECTSPRITETYPE_INI,						// 아이니
		EFFECTSPRITETYPE_JAVE,						// 쟈브
		EFFECTSPRITETYPE_CHASPA,					// 차스파
		EFFECTSPRITETYPE_CONCILIA,					// 콘칠리아
		EFFECTSPRITETYPE_KIRO,						// 키로
		EFFECTSPRITETYPE_HILLEL,					// 힐릴
	};
	
	const int SlayerChargingPowerMaleEst[] = {		
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_STOP_1,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_STOP_2,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_STOP_3,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_STOP_4,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_STOP_5,	
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_MOTOR_STOP_1,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_MOTOR_STOP_2,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_MOTOR_STOP_3,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_MOTOR_STOP_4,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_MOTOR_STOP_5,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_MOTOR_MOVE_1,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_MOTOR_MOVE_2,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_MOTOR_MOVE_3,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_MOTOR_MOVE_4,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_MOTOR_MOVE_5,		
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_WALK_1,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_WALK_2,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_WALK_3,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_WALK_4,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_WALK_5,		
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_MAGIC_1,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_MAGIC_2,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_MAGIC_3,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_MAGIC_4,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_MAGIC_5,		
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_DAMAGED_1,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_DAMAGED_2,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_DAMAGED_3,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_DAMAGED_4,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_DAMAGED_5,		
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_ATTACK_FAST_1,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_ATTACK_FAST_2,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_ATTACK_FAST_3,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_ATTACK_FAST_4,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_ATTACK_FAST_5,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_ATTACK_NORMAL_1,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_ATTACK_NORMAL_2,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_ATTACK_NORMAL_3,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_ATTACK_NORMAL_4,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_ATTACK_NORMAL_5,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_ATTACK_SLOW_1,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_ATTACK_SLOW_2,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_ATTACK_SLOW_3,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_ATTACK_SLOW_4,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_ATTACK_SLOW_5,		
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_SKILL_FAST_1,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_SKILL_FAST_2,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_SKILL_FAST_3,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_SKILL_FAST_4,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_SKILL_FAST_5,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_SKILL_NORMAL_1,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_SKILL_NORMAL_2,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_SKILL_NORMAL_3,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_SKILL_NORMAL_4,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_SKILL_NORMAL_5,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_SKILL_SLOW_1,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_SKILL_SLOW_2,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_SKILL_SLOW_3,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_SKILL_SLOW_4,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_SKILL_SLOW_5,
#if __CONTENTS(__EFFECT_RENEWAL)
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_DRIN_1,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_DRIN_2,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_DRIN_3,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_DRIN_4,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_DRIN_5,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_DIE_1,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_DIE_2,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_DIE_3,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_DIE_4,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_DIE_5,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_BATTLE_STAND_1,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_BATTLE_STAND_2,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_BATTLE_STAND_3,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_BATTLE_STAND_4,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_BATTLE_STAND_5,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_MAGIC_CASTING_1,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_MAGIC_CASTING_2,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_MAGIC_CASTING_3,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_MAGIC_CASTING_4,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_MAGIC_CASTING_5,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_BLADE_2_REPEAT_1,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_BLADE_2_REPEAT_2,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_BLADE_2_REPEAT_3,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_BLADE_2_REPEAT_4,
		EFFECTSPRITETYPE_CHARGING_POWER_MALE_BLADE_2_REPEAT_5,
#endif //__EFFECT_RENEWAL
	};

	const int SlayerChargingPowerFeMaleEst[] =
	{
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_STOP_1,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_STOP_2,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_STOP_3,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_STOP_4,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_STOP_5,	
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_MOTOR_STOP_1,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_MOTOR_STOP_2,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_MOTOR_STOP_3,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_MOTOR_STOP_4,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_MOTOR_STOP_5,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_MOTOR_MOVE_1,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_MOTOR_MOVE_2,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_MOTOR_MOVE_3,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_MOTOR_MOVE_4,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_MOTOR_MOVE_5,	
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_WALK_1,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_WALK_2,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_WALK_3,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_WALK_4,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_WALK_5,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_MAGIC_1,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_MAGIC_2,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_MAGIC_3,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_MAGIC_4,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_MAGIC_5,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_DAMAGED_1,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_DAMAGED_2,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_DAMAGED_3,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_DAMAGED_4,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_DAMAGED_5,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_ATTACK_FAST_1,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_ATTACK_FAST_2,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_ATTACK_FAST_3,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_ATTACK_FAST_4,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_ATTACK_FAST_5,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_ATTACK_NORMAL_1,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_ATTACK_NORMAL_2,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_ATTACK_NORMAL_3,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_ATTACK_NORMAL_4,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_ATTACK_NORMAL_5,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_ATTACK_SLOW_1,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_ATTACK_SLOW_2,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_ATTACK_SLOW_3,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_ATTACK_SLOW_4,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_ATTACK_SLOW_5,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_SKILL_FAST_1,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_SKILL_FAST_2,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_SKILL_FAST_3,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_SKILL_FAST_4,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_SKILL_FAST_5,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_SKILL_NORMAL_1,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_SKILL_NORMAL_2,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_SKILL_NORMAL_3,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_SKILL_NORMAL_4,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_SKILL_NORMAL_5,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_SKILL_SLOW_1,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_SKILL_SLOW_2,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_SKILL_SLOW_3,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_SKILL_SLOW_4,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_SKILL_SLOW_5,
#if __CONTENTS(__EFFECT_RENEWAL)
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_DRIN_1,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_DRIN_2,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_DRIN_3,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_DRIN_4,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_DRIN_5,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_DIE_1,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_DIE_2,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_DIE_3,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_DIE_4,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_DIE_5,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_BATTLE_STAND_1,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_BATTLE_STAND_2,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_BATTLE_STAND_3,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_BATTLE_STAND_4,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_BATTLE_STAND_5,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_MAGIC_CASTING_1,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_MAGIC_CASTING_2,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_MAGIC_CASTING_3,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_MAGIC_CASTING_4,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_MAGIC_CASTING_5,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_BLADE_2_REPEAT_1,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_BLADE_2_REPEAT_2,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_BLADE_2_REPEAT_3,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_BLADE_2_REPEAT_4,
		EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_BLADE_2_REPEAT_5,
#endif //__EFFECT_RENEWAL
	};

	const int numACVampireGhostColorGroup = 6;
	const int numACVampireGhost = 2;
	const int ACVampireGhost[numACVampireGhostColorGroup][numACVampireGhost] = 
	{	
//		{ EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_STAND,			EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_MOVE,			},
		{ EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_STAND_BLACK,	EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_MOVE_BLACK,	},
		{ EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_STAND_RED,		EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_MOVE_RED,		},
		{ EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_STAND_BLUE,		EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_MOVE_BLUE,	},
		{ EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_STAND_YELLOW,	EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_MOVE_YELLOW,	},
		{ EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_STAND_GREEN,	EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_MOVE_GREEN,	},
		{ EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_STAND_WHITE,	EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_MOVE_WHITE,	},
	};

#if __CONTENTS(__FAST_TRANSFORTER)
	const int numVampireWingColorGroup = 5;
	const int numVampireWing = 2;
	const int VampireWing[numVampireWingColorGroup][numVampireWing] = 
	{	
		{ EFFECTSPRITETYPE_VAMPIRE_WING_STOP_GRAY,	EFFECTSPRITETYPE_VAMPIRE_WING_MOVE_GRAY,	},
		{ EFFECTSPRITETYPE_VAMPIRE_WING_STOP_RED,	EFFECTSPRITETYPE_VAMPIRE_WING_MOVE_RED,		},
		{ EFFECTSPRITETYPE_VAMPIRE_WING_STOP_BLUE,	EFFECTSPRITETYPE_VAMPIRE_WING_MOVE_BLUE,	},
		{ EFFECTSPRITETYPE_VAMPIRE_WING_STOP_ORANGE,EFFECTSPRITETYPE_VAMPIRE_WING_MOVE_ORANGE,	},
		{ EFFECTSPRITETYPE_VAMPIRE_WING_STOP_GREEN,	EFFECTSPRITETYPE_VAMPIRE_WING_MOVE_GREEN,	},
	};
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
	const int numVampireShapeOfDemonColorGroup = 8;
	const int numVampireShapeOfDemon = 2;
	const int VampireShapeOfDemon[numVampireShapeOfDemonColorGroup][numVampireShapeOfDemon] = 
	{	
		{ EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_WHITE,		EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_WHITE,		},
		{ EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_RED,			EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_RED,		},
		{ EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_YELLOW,		EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_YELLOW,	},
		{ EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_BLUEGREEN,	EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_BLUEGREEN, },
		{ EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_BLUE,		EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_BLUE,		},
		{ EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_MAZANTA,		EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_MAZANTA,	},
		{ EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_VIOLET,		EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_VIOLET,	},
		{ EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_BLACK,		EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_BLACK,		},
	};
#endif //__SECOND_TRANSFORTER

	int ae, cg;
	for (ae=0; ae<numHPBOOSTESTMale; ae++)
	{
		(*g_pEffectSpriteTypeTable)[HPBOOSTESTMale[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_HPBOOST_MALE;
	}

	for (ae=0; ae<numHPBOOSTESTFemale; ae++)
	{
		(*g_pEffectSpriteTypeTable)[HPBOOSTESTFemale[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_HPBOOST_FEMALE;
	}

	for (ae=0; ae<numRegenESTMale; ae++)
	{
		(*g_pEffectSpriteTypeTable)[regenESTMale[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_REGENERATION_MALE;
	}

	for (ae=0; ae<numRegenESTFemale; ae++)
	{
		(*g_pEffectSpriteTypeTable)[regenESTFemale[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_REGENERATION_FEMALE;
	}

#if __CONTENTS(__FAST_TRANSFORTER)
	for (ae=0; ae<numOUSTERSWINGBLUE; ae++)
	{
		(*g_pEffectSpriteTypeTable)[OUSTERSWINGBLUE[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_OUSTERS_WING_BLUE;
	}
	for (ae=0; ae<numOUSTERSWINGYELLOW; ae++)
	{
		(*g_pEffectSpriteTypeTable)[OUSTERSWINGYELLOW[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_OUSTERS_WING_YELLOW;
	}
	for (ae=0; ae<numOUSTERSWINGRED; ae++)
	{
		(*g_pEffectSpriteTypeTable)[OUSTERSWINGRED[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_OUSTERS_WING_RED;
	}
	for (ae=0; ae<numOUSTERSWINGORANGE; ae++)
	{
		(*g_pEffectSpriteTypeTable)[OUSTERSWINGORANGE[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_OUSTERS_WING_ORANGE;
	}
	for (ae=0; ae<numOUSTERSWINGYELLOWGREEN; ae++)
	{
		(*g_pEffectSpriteTypeTable)[OUSTERSWINGYELLOWGREEN[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_OUSTERS_WING_YELLOWGREEN;
	}
	for (ae=0; ae<numOUSTERSWINGBLUEGREEN; ae++)
	{
		(*g_pEffectSpriteTypeTable)[OUSTERSWINGBLUEGREEN[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_OUSTERS_WING_BLUEGREEN;
	}
	for (ae=0; ae<numOUSTERSWINGVIOLET; ae++)
	{
		(*g_pEffectSpriteTypeTable)[OUSTERSWINGVIOLET[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_OUSTERS_WING_VIOLET;
	}
	for (ae=0; ae<numOUSTERSWINGWHITE; ae++)
	{
		(*g_pEffectSpriteTypeTable)[OUSTERSWINGWHITE[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_OUSTERS_WING_WHITE;
	}
	for (ae=0; ae<numSLAYERWING; ae++)
	{
		(*g_pEffectSpriteTypeTable)[SLAYERWING[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_SLAYER_WING;
	}
#endif //__FAST_TRANSFORTER

#if __CONTENTS(__SECOND_TRANSFORTER)
	for (ae=0; ae<numOUSTERSUNICORN_WHITE; ae++)
	{
		(*g_pEffectSpriteTypeTable)[OUSTERSUNICORN_WHITE[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_OUSTERS_UNICORN_WHITE;
	}
	for (ae=0; ae<numOUSTERSUNICORN_RED; ae++)
	{
		(*g_pEffectSpriteTypeTable)[OUSTERSUNICORN_RED[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_OUSTERS_UNICORN_RED;
	}
	for (ae=0; ae<numOUSTERSUNICORN_YELLOW; ae++)
	{
		(*g_pEffectSpriteTypeTable)[OUSTERSUNICORN_YELLOW[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_OUSTERS_UNICORN_YELLOW;
	}
	for (ae=0; ae<numOUSTERSUNICORN_YELLOWGREEN; ae++)
	{
		(*g_pEffectSpriteTypeTable)[OUSTERSUNICORN_YELLOWGREEN[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_OUSTERS_UNICORN_YELLOWGREEN;
	}
	for (ae=0; ae<numOUSTERSUNICORN_BLUE; ae++)
	{
		(*g_pEffectSpriteTypeTable)[OUSTERSUNICORN_BLUE[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_OUSTERS_UNICORN_BLUE;
	}
	for (ae=0; ae<numOUSTERSUNICORN_MAZANTA; ae++)
	{
		(*g_pEffectSpriteTypeTable)[OUSTERSUNICORN_MAZANTA[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_OUSTERS_UNICORN_MAZANTA;
	}
//	for (ae=0; ae<numSLAYERHOVERVEHICLE; ae++)
//	{
//		(*g_pEffectSpriteTypeTable)[SLAYERHOVERVEHICLE[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_SLAYER_HOVER_VEHICLE;
//	}
#endif //__SECOND_TRANSFORTER

	for (ae=0; ae<numBERSERKERESTMale; ae++)
	{
		(*g_pEffectSpriteTypeTable)[BERSERKERESTMale[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_BERSERKER_MALE;
	}

	for (ae=0; ae<numBERSERKERESTFemale; ae++)
	{
		(*g_pEffectSpriteTypeTable)[BERSERKERESTFemale[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_BERSERKER_FEMALE;
	}

	for (ae=0; ae<numExtremeESTMale; ae++)
	{
		(*g_pEffectSpriteTypeTable)[ExtremeESTMale[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_EXTREME_MALE;
	}

	for (ae=0; ae<numExtremeESTFemale; ae++)
	{
		(*g_pEffectSpriteTypeTable)[ExtremeESTFemale[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_EXTREME_FEMALE;
	}

	for (ae=0; ae<numSlayerGrandmasterESTMale; ae++)
	{
		(*g_pEffectSpriteTypeTable)[SlayerGrandmasterESTMale[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_SLAYER_GRANDMASTER_MALE;
	}

	for (ae=0; ae<numSlayerGrandmasterESTFemale; ae++)
	{
		(*g_pEffectSpriteTypeTable)[SlayerGrandmasterESTFemale[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_SLAYER_GRANDMASTER_FEMALE;
	}

	for (ae=0; ae<numVampireGrandmasterESTMale; ae++)
	{
		(*g_pEffectSpriteTypeTable)[VampireGrandmasterESTMale[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE;
	}

	for (ae=0; ae<numVampireGrandmasterESTFemale; ae++)
	{
		(*g_pEffectSpriteTypeTable)[VampireGrandmasterESTFemale[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE;
	}
	
	for(cg = 0; cg < numACVampireGhostColorGroup; ++cg)
	{
		for (ae = 0; ae < numACVampireGhost; ++ae)
		{
			(*g_pEffectSpriteTypeTable)[ACVampireGhost[cg][ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_VAMPIRE_ACGHOST_BLACK + cg;
		}
	}
#if __CONTENTS(__FAST_TRANSFORTER)
	for(cg = 0; cg < numVampireWingColorGroup; ++cg)
	{
		for (ae = 0; ae < numVampireWing; ++ae)
		{
			(*g_pEffectSpriteTypeTable)[VampireWing[cg][ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_VAMPIRE_WING_GRAY + cg;
		}
	}
#endif //__FAST_TRANSFORTER

#if __CONTENTS(__SECOND_TRANSFORTER)
	for(cg = 0; cg < numVampireShapeOfDemonColorGroup; ++cg)
	{
		for (ae = 0; ae < numVampireShapeOfDemon; ++ae)
		{
			(*g_pEffectSpriteTypeTable)[VampireShapeOfDemon[cg][ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_WHITE + cg;
		}
	}
#endif //__SECOND_TRANSFORTER
	
	for (ae=0; ae<sizeof(SlayerChargingPowerMaleEst)/sizeof(int);ae++)
	{
		(*g_pEffectSpriteTypeTable)[SlayerChargingPowerMaleEst[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_CHARGING_POWER_MALE;
	}

	for (ae=0; ae<sizeof(SlayerChargingPowerFeMaleEst)/sizeof(int);ae++)
	{
		(*g_pEffectSpriteTypeTable)[SlayerChargingPowerFeMaleEst[ae]].ActionEffectFrameID = ACTIONEFFECTSPRITETYPE_CHARGING_POWER_FEMALE;
	}


	//-----------------------------------------------------------------------------------
	//
	// FemaleEffectSpriteType 설정
	//
	//-----------------------------------------------------------------------------------
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_HPBOOST_STAND_MALE].FemaleEffectSpriteType = EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_REGENERATION_1_STAND_MALE].FemaleEffectSpriteType = EFFECTSPRITETYPE_REGENERATION_1_STAND_FEMALE;	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_BERSERKER_1_STAND_MALE].FemaleEffectSpriteType = EFFECTSPRITETYPE_BERSERKER_1_STAND_FEMALE;	
//	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE].FemaleEffectSpriteType = EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE;	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_EXTREME_L_1_STAND_MALE].FemaleEffectSpriteType = EFFECTSPRITETYPE_EXTREME_L_1_STAND_FEMALE;
//	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_HYPNOSIS_END_MALE].FemaleEffectSpriteType = EFFECTSPRITETYPE_HYPNOSIS_END_FEMALE;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_STAND].FemaleEffectSpriteType = EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_STAND;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK].FemaleEffectSpriteType = EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK;

	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_CHARGING_POWER_MALE_STOP_1].FemaleEffectSpriteType = EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_STOP_1;	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_NEW_ACID_TOUCH_MALE_NORMAL].FemaleEffectSpriteType = EFFECTSPRITETYPE_NEW_ACID_TOUCH_FEMALE_NORMAL;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_NEW_BLOODY_NAIL_MALE_NORMAL].FemaleEffectSpriteType = EFFECTSPRITETYPE_NEW_BLOODY_NAIL_FEMALE_NORMAL;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_JABBING_VEIN_GUN_AR_MALE].FemaleEffectSpriteType = EFFECTSPRITETYPE_JABBING_VEIN_GUN_AR_FEMALE;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_JABBING_VEIN_GUN_SMG_MALE].FemaleEffectSpriteType = EFFECTSPRITETYPE_JABBING_VEIN_GUN_SMG_FEMALE;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_JABBING_VEIN_GUN_SR_MALE].FemaleEffectSpriteType = EFFECTSPRITETYPE_JABBING_VEIN_GUN_SR_FEMALE;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_JABBING_VEIN_GUN_SG_MALE].FemaleEffectSpriteType = EFFECTSPRITETYPE_JABBING_VEIN_GUN_SG_FEMALE;
	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_NEW_BLITZ_SLIDING_SWORD_MALE].FemaleEffectSpriteType = EFFECTSPRITETYPE_NEW_BLITZ_SLIDING_SWORD_FEMALE;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_NEW_BLAZE_WALK_MALE].FemaleEffectSpriteType = EFFECTSPRITETYPE_NEW_BLAZE_WALK_FEMALE;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_NEW_LAR_SLASH_MALE_NORMAL].FemaleEffectSpriteType = EFFECTSPRITETYPE_NEW_LAR_SLASH_FEMALE_NORMAL;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_NEW_REDIANCE_MALE_NORMAL].FemaleEffectSpriteType = EFFECTSPRITETYPE_NEW_REDIANCE_FEMALE_NORMAL;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_NEW_REDIANCE_MALE_NORMAL_ATTACK_NORMAL].FemaleEffectSpriteType = EFFECTSPRITETYPE_NEW_REDIANCE_FEMALE_NORMAL_ATTACK_NORMAL;

	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_TALON_OF_CROW_MALE_NORMAL].FemaleEffectSpriteType = EFFECTSPRITETYPE_TALON_OF_CROW_FEMALE_NORMAL;
	
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_RENEWAL_BLOODY_NAIL_MALE_ACTION_1_NORMAL].FemaleEffectSpriteType = EFFECTSPRITETYPE_RENEWAL_BLOODY_NAIL_FEMALE_ACTION_1_NORMAL;
	(*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_RENEWAL_TALON_OF_CROW_MALE_ACTION_1_NORMAL].FemaleEffectSpriteType = EFFECTSPRITETYPE_RENEWAL_TALON_OF_CROW_FEMALE_ACTION_1_NORMAL;

	
	//------------------------------------------------
	// Save
	//------------------------------------------------
	std::ofstream effectSpriteTypeTable(g_pFileDef->getProperty("FILE_INFO_EFFECTSPRITETYPE").c_str(), std::ios::binary);
	(*g_pEffectSpriteTypeTable).SaveToFile(effectSpriteTypeTable);
	effectSpriteTypeTable.close();
#endif
	//*/

	//------------------------------------------------
	// Load
	//------------------------------------------------
	ivfstream effectSpriteTypeTable2;//(FILE_INFO_EFFECTSPRITETYPE, ios::binary);
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_INFO_EFFECTSPRITETYPE").c_str(), effectSpriteTypeTable2))
		return FALSE;
	(*g_pEffectSpriteTypeTable).LoadFromFile(effectSpriteTypeTable2);
	effectSpriteTypeTable2.close();


	//---------------------------------------------------------------------
	//
	//      Action EffectSpriteTypeTable 정보 생성
	//
	//---------------------------------------------------------------------
	///*
#ifdef SAVE_TO_FILE
	(*g_pActionEffectSpriteTypeTable).Init( MAX_ACTIONEFFECTSPRITETYPE );

	//ACTIONEFFECTSPRITETYPE_HPBOOST_MALE
	//ACTIONEFFECTSPRITETYPE_HPBOOST_FEMALE,
	//ACTIONEFFECTSPRITETYPE_REGENERATION_MALE,
	//ACTIONEFFECTSPRITETYPE_REGENERATION_FEMALE,
	int actionEST[MAX_ACTIONEFFECTSPRITETYPE][ACTION_MAX_SLAYER] = 
	{
		// HPBOOST Male												MAX_ACTIONEFFECTSPRITETYPE 0
		{
			EFFECTSPRITETYPE_HPBOOST_STAND_MALE,
			EFFECTSPRITETYPE_HPBOOST_MOVE_MALE,				
			EFFECTSPRITETYPE_HPBOOST_ATTACK_MALE,			
			EFFECTSPRITETYPE_HPBOOST_MAGIC_MALE,			
			EFFECTSPRITETYPE_HPBOOST_DAMAGE_MALE,			
			EFFECTSPRITETYPE_HPBOOST_STAND_MALE,			
			EFFECTSPRITETYPE_HPBOOST_STAND_MALE,				
			EFFECTSPRITETYPE_HPBOOST_STAND_MALE,	
			EFFECTSPRITETYPE_HPBOOST_STAND_MALE,	
			EFFECTSPRITETYPE_HPBOOST_SWORD_MALE,
			EFFECTSPRITETYPE_HPBOOST_STAND_MALE,		
			EFFECTSPRITETYPE_HPBOOST_THROW_MALE,
			EFFECTSPRITETYPE_HPBOOST_STAND_MALE,
			EFFECTSPRITETYPE_HPBOOST_STAND_MALE,	
			EFFECTSPRITETYPE_HPBOOST_STAND_MALE,	
			EFFECTSPRITETYPE_HPBOOST_SWORD2_MALE,	
			EFFECTSPRITETYPE_HPBOOST_STAND_MALE,	
			EFFECTSPRITETYPE_HPBOOST_THROW_MALE,
			EFFECTSPRITETYPE_HPBOOST_STAND_MALE,
			EFFECTSPRITETYPE_HPBOOST_STAND_MALE,	
			EFFECTSPRITETYPE_HPBOOST_STAND_MALE,	
			EFFECTSPRITETYPE_HPBOOST_STAND_MALE,	
			EFFECTSPRITETYPE_HPBOOST_STAND_MALE,	
			EFFECTSPRITETYPE_HPBOOST_STAND_MALE,	
			EFFECTSPRITETYPE_HPBOOST_STAND_MALE,	
			EFFECTSPRITETYPE_HPBOOST_STAND_MALE,	
			EFFECTSPRITETYPE_HPBOOST_STAND_MALE,	
			EFFECTSPRITETYPE_HPBOOST_SWORD_SLOW_MALE,				//ACTION_SWORD_SLOW	
			EFFECTSPRITETYPE_HPBOOST_SWORD_FAST_MALE,				//ACTION_SWORD_FAST	
			EFFECTSPRITETYPE_HPBOOST_STAND_MALE,	
			EFFECTSPRITETYPE_HPBOOST_STAND_MALE,	
			EFFECTSPRITETYPE_HPBOOST_SWORD2_SLOW_MALE,				//ACTION_SWORD_2_SLOW	
			EFFECTSPRITETYPE_HPBOOST_SWORD2_FAST_MALE,				//ACTION_SWORD_2_FAST
			EFFECTSPRITETYPE_HPBOOST_STAND_MALE,	
			EFFECTSPRITETYPE_HPBOOST_STAND_MALE
		},

		// HPBOOST Female											MAX_ACTIONEFFECTSPRITETYPE 1
		{
			EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE,
			EFFECTSPRITETYPE_HPBOOST_MOVE_FEMALE,				
			EFFECTSPRITETYPE_HPBOOST_ATTACK_FEMALE,			
			EFFECTSPRITETYPE_HPBOOST_MAGIC_FEMALE,			
			EFFECTSPRITETYPE_HPBOOST_DAMAGE_FEMALE,			
			EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE,			
			EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE,				
			EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE,	
			EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE,	
			EFFECTSPRITETYPE_HPBOOST_SWORD_FEMALE,		
			EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE,		
			EFFECTSPRITETYPE_HPBOOST_THROW_FEMALE,
			EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE,
			EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE,	
			EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE,	
			EFFECTSPRITETYPE_HPBOOST_SWORD2_FEMALE,	
			EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE,	
			EFFECTSPRITETYPE_HPBOOST_THROW_FEMALE,
			EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE,
			EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE,	
			EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE,	
			EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE,	
			EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE,	
			EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE,	
			EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE,	
			EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE,	
			EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE,	
			EFFECTSPRITETYPE_HPBOOST_SWORD_SLOW_FEMALE,				//ACTION_SWORD_SLOW	
			EFFECTSPRITETYPE_HPBOOST_SWORD_FAST_FEMALE,				//ACTION_SWORD_FAST	
			EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE,	
			EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE,	
			EFFECTSPRITETYPE_HPBOOST_SWORD2_SLOW_FEMALE,			//ACTION_SWORD_2_SLOW	
			EFFECTSPRITETYPE_HPBOOST_SWORD2_FAST_FEMALE,			//ACTION_SWORD_2_FAST
			EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE,	
			EFFECTSPRITETYPE_HPBOOST_STAND_FEMALE
		},
#if __CONTENTS(__EFFECT_RENEWAL)
		// Regeneration Male 										MAX_ACTIONEFFECTSPRITETYPE 2
		{
			EFFECTSPRITETYPE_REGENERATION_1_STAND_MALE,				//ACTION_STAND
			EFFECTSPRITETYPE_REGENERATION_1_MOVE_MALE,				//ACTION_MOVE
			EFFECTSPRITETYPE_REGENERATION_1_ATTACK_MALE,			//ACTION_ATTACK
			EFFECTSPRITETYPE_REGENERATION_1_MAGIC_ATTACK_MALE,		//ACTION_MAGIC
			EFFECTSPRITETYPE_REGENERATION_1_DAMAGE_MALE,			//ACTION_DAMAGED
			EFFECTSPRITETYPE_REGENERATION_1_DRAIN_MALE,				//ACTION_DRAINED
			EFFECTSPRITETYPE_REGENERATION_1_DIE_MALE,				//ACTION_DIE
			
			EFFECTSPRITETYPE_REGENERATION_1_SR_MALE,				//ACTION_SLAYER_GUN_SR
			EFFECTSPRITETYPE_REGENERATION_1_AR_MALE,				//ACTION_SLAYER_GUN_AR
			EFFECTSPRITETYPE_REGENERATION_1_SG_MALE,				//ACTION_SLAYER_GUN_SG
			EFFECTSPRITETYPE_REGENERATION_1_SMG_MALE,				//ACTION_SLAYER_GUN_SMG

			EFFECTSPRITETYPE_REGENERATION_1_SWORD_MALE,				//ACTION_SLAYER_SWORD
			EFFECTSPRITETYPE_REGENERATION_1_BLADE_MALE,				//ACTION_SLAYER_BLADE
			EFFECTSPRITETYPE_REGENERATION_1_SWORD2_MALE,			//ACTION_SLAYER_SWORD_2
			EFFECTSPRITETYPE_REGENERATION_1_BLADE2_MALE,			//ACTION_SLAYER_BLADE_2
			EFFECTSPRITETYPE_REGENERATION_1_MOTOR_MALE,				//ACTION_SLAYER_MOTOR_MOVE
			EFFECTSPRITETYPE_REGENERATION_1_BIKE_STOP_MALE,			//ACTION_SLAYER_MOTOR_STAND

			EFFECTSPRITETYPE_REGENERATION_1_SR_SLOW_MALE,			//ACTION_SLAYER_GUN_SR_SLOW
			EFFECTSPRITETYPE_REGENERATION_1_SR_FAST_MALE,			//ACTION_SLAYER_GUN_SR_FAST
			EFFECTSPRITETYPE_REGENERATION_1_AR_SLOW_MALE,			//ACTION_SLAYER_GUN_AR_SLOW
			EFFECTSPRITETYPE_REGENERATION_1_AR_FAST_MALE,			//ACTION_SLAYER_GUN_AR_FAST
			EFFECTSPRITETYPE_REGENERATION_1_SG_SLOW_MALE,			//ACTION_SLAYER_GUN_SG_SLOW
			EFFECTSPRITETYPE_REGENERATION_1_SG_FAST_MALE,			//ACTION_SLAYER_GUN_SG_FAST
			EFFECTSPRITETYPE_REGENERATION_1_SMG_SLOW_MALE,			//ACTION_SLAYER_GUN_SMG_SLOW
			EFFECTSPRITETYPE_REGENERATION_1_SMG_FAST_MALE,			//ACTION_SLAYER_GUN_SMG_FAST
			EFFECTSPRITETYPE_REGENERATION_1_SWORD_SLOW_MALE,		//ACTION_SLAYER_SWORD_SLOW
			EFFECTSPRITETYPE_REGENERATION_1_SWORD_FAST_MALE,		//ACTION_SLAYER_SWORD_FAST
			EFFECTSPRITETYPE_REGENERATION_1_BLADE_SLOW_MALE,		//ACTION_SLAYER_BLADE_SLOW
			EFFECTSPRITETYPE_REGENERATION_1_BLADE_FAST_MALE,		//ACTION_SLAYER_BLADE_FAST
			EFFECTSPRITETYPE_REGENERATION_1_SWORD2_SLOW_MALE,		//ACTION_SLAYER_SWORD_2_SLOW
			EFFECTSPRITETYPE_REGENERATION_1_SWORD2_FAST_MALE,		//ACTION_SLAYER_SWORD_2_FAST
			EFFECTSPRITETYPE_REGENERATION_1_BLADE2_SLOW_MALE,		//ACTION_SLAYER_BLADE_2_SLOW
			EFFECTSPRITETYPE_REGENERATION_1_BLADE2_FAST_MALE,		//ACTION_SLAYER_BLADE_2_FAST
			
			EFFECTSPRITETYPE_REGENERATION_1_BATTLE_STAND_GUN_MALE,	//ACTION_SLAYER_BATTLE_STAND_GUN
			EFFECTSPRITETYPE_REGENERATION_1_BATTLE_STAND_SWORD_MALE,//ACTION_SLAYER_BATTLE_STAND_SWORD
			EFFECTSPRITETYPE_REGENERATION_1_BATTLE_STAND_BLADE_MALE,//ACTION_SLAYER_BATTLE_STAND_BLADE
			
			EFFECTSPRITETYPE_REGENERATION_1_MOVE_GUN_MALE,			//ACTION_SLAYER_MOVE_GUN,			
			EFFECTSPRITETYPE_REGENERATION_1_MAGIC_CASTING_MALE,		//ACTION_SLAYER_MAGIC_CASTING,	
			EFFECTSPRITETYPE_REGENERATION_1_SWORD_2_REPEAT_MALE,	//ACTION_SLAYER_SWORD_2_REPEAT
			EFFECTSPRITETYPE_REGENERATION_1_BLADE_2_REPEAT_MALE		//ACTION_SLAYER_BLADE_2_REPEAT

		},

		// Regeneration Female 										MAX_ACTIONEFFECTSPRITETYPE 3
		{
			EFFECTSPRITETYPE_REGENERATION_1_STAND_FEMALE,			//ACTION_STAND
			EFFECTSPRITETYPE_REGENERATION_1_MOVE_FEMALE,			//ACTION_MOVE
			EFFECTSPRITETYPE_REGENERATION_1_ATTACK_FEMALE,			//ACTION_ATTACK
			EFFECTSPRITETYPE_REGENERATION_1_MAGIC_ATTACK_FEMALE,	//ACTION_MAGIC
			EFFECTSPRITETYPE_REGENERATION_1_DAMAGE_FEMALE,			//ACTION_DAMAGED
			EFFECTSPRITETYPE_REGENERATION_1_DRAIN_FEMALE,			//ACTION_DRAINED
			EFFECTSPRITETYPE_REGENERATION_1_DIE_FEMALE,				//ACTION_DIE
			
			EFFECTSPRITETYPE_REGENERATION_1_SR_FEMALE,				//ACTION_SLAYER_GUN_SR
			EFFECTSPRITETYPE_REGENERATION_1_AR_FEMALE,				//ACTION_SLAYER_GUN_AR
			EFFECTSPRITETYPE_REGENERATION_1_SG_FEMALE,				//ACTION_SLAYER_GUN_SG
			EFFECTSPRITETYPE_REGENERATION_1_SMG_FEMALE,				//ACTION_SLAYER_GUN_SMG

			EFFECTSPRITETYPE_REGENERATION_1_SWORD_FEMALE,			//ACTION_SLAYER_SWORD
			EFFECTSPRITETYPE_REGENERATION_1_BLADE_FEMALE,			//ACTION_SLAYER_BLADE
			EFFECTSPRITETYPE_REGENERATION_1_SWORD2_FEMALE,			//ACTION_SLAYER_SWORD_2
			EFFECTSPRITETYPE_REGENERATION_1_BLADE2_FEMALE,			//ACTION_SLAYER_BLADE_2
			EFFECTSPRITETYPE_REGENERATION_1_MOTOR_FEMALE,			//ACTION_SLAYER_MOTOR_MOVE
			EFFECTSPRITETYPE_REGENERATION_1_BIKE_STOP_FEMALE,		//ACTION_SLAYER_MOTOR_STAND

			EFFECTSPRITETYPE_REGENERATION_1_SR_SLOW_FEMALE,			//ACTION_SLAYER_GUN_SR_SLOW
			EFFECTSPRITETYPE_REGENERATION_1_SR_FAST_FEMALE,			//ACTION_SLAYER_GUN_SR_FAST
			EFFECTSPRITETYPE_REGENERATION_1_AR_SLOW_FEMALE,			//ACTION_SLAYER_GUN_AR_SLOW
			EFFECTSPRITETYPE_REGENERATION_1_AR_FAST_FEMALE,			//ACTION_SLAYER_GUN_AR_FAST
			EFFECTSPRITETYPE_REGENERATION_1_SG_SLOW_FEMALE,			//ACTION_SLAYER_GUN_SG_SLOW
			EFFECTSPRITETYPE_REGENERATION_1_SG_FAST_FEMALE,			//ACTION_SLAYER_GUN_SG_FAST
			EFFECTSPRITETYPE_REGENERATION_1_SMG_SLOW_FEMALE,		//ACTION_SLAYER_GUN_SMG_SLOW
			EFFECTSPRITETYPE_REGENERATION_1_SMG_FAST_FEMALE,		//ACTION_SLAYER_GUN_SMG_FAST
			EFFECTSPRITETYPE_REGENERATION_1_SWORD_SLOW_FEMALE,		//ACTION_SLAYER_SWORD_SLOW
			EFFECTSPRITETYPE_REGENERATION_1_SWORD_FAST_FEMALE,		//ACTION_SLAYER_SWORD_FAST
			EFFECTSPRITETYPE_REGENERATION_1_BLADE_SLOW_FEMALE,		//ACTION_SLAYER_BLADE_SLOW
			EFFECTSPRITETYPE_REGENERATION_1_BLADE_FAST_FEMALE,		//ACTION_SLAYER_BLADE_FAST
			EFFECTSPRITETYPE_REGENERATION_1_SWORD2_SLOW_FEMALE,		//ACTION_SLAYER_SWORD_2_SLOW
			EFFECTSPRITETYPE_REGENERATION_1_SWORD2_FAST_FEMALE,		//ACTION_SLAYER_SWORD_2_FAST
			EFFECTSPRITETYPE_REGENERATION_1_BLADE2_SLOW_FEMALE,		//ACTION_SLAYER_BLADE_2_SLOW
			EFFECTSPRITETYPE_REGENERATION_1_BLADE2_FAST_FEMALE,		//ACTION_SLAYER_BLADE_2_FAST
			
			EFFECTSPRITETYPE_REGENERATION_1_BATTLE_STAND_GUN_FEMALE,//ACTION_SLAYER_BATTLE_STAND_GUN
			EFFECTSPRITETYPE_REGENERATION_1_BATTLE_STAND_SWORD_FEMALE,//ACTION_SLAYER_BATTLE_STAND_SWORD
			EFFECTSPRITETYPE_REGENERATION_1_BATTLE_STAND_BLADE_FEMALE,//ACTION_SLAYER_BATTLE_STAND_BLADE
			
			EFFECTSPRITETYPE_REGENERATION_1_MOVE_GUN_FEMALE,		//ACTION_SLAYER_MOVE_GUN,			
			EFFECTSPRITETYPE_REGENERATION_1_MAGIC_CASTING_FEMALE,	//ACTION_SLAYER_MAGIC_CASTING,	
			EFFECTSPRITETYPE_REGENERATION_1_SWORD_2_REPEAT_FEMALE,	//ACTION_SLAYER_SWORD_2_REPEAT
			EFFECTSPRITETYPE_REGENERATION_1_BLADE_2_REPEAT_FEMALE	//ACTION_SLAYER_BLADE_2_REPEAT
		},
#else
		// Regeneration Male										MAX_ACTIONEFFECTSPRITETYPE 3
		{
			EFFECTSPRITETYPE_REGENERATION_1_STAND_MALE,				//ACTION_STAND
			EFFECTSPRITETYPE_REGENERATION_1_MOVE_MALE,				//ACTION_MOVE
			EFFECTSPRITETYPE_REGENERATION_1_ATTACK_MALE,			//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_REGENERATION_1_DAMAGE_MALE,			//ACTION_DAMAGED
			EFFECTSPRITETYPE_NULL,									//ACTION_DRAINED
			EFFECTSPRITETYPE_NULL,									//ACTION_DIE
			
			EFFECTSPRITETYPE_REGENERATION_1_SR_MALE,				//ACTION_SLAYER_GUN_SR
			EFFECTSPRITETYPE_REGENERATION_1_AR_MALE,				//ACTION_SLAYER_GUN_AR
			EFFECTSPRITETYPE_REGENERATION_1_SG_MALE,				//ACTION_SLAYER_GUN_SG
			EFFECTSPRITETYPE_REGENERATION_1_SMG_MALE,				//ACTION_SLAYER_GUN_SMG

			EFFECTSPRITETYPE_REGENERATION_1_SWORD_MALE,				//ACTION_SLAYER_SWORD
			EFFECTSPRITETYPE_REGENERATION_1_BLADE_MALE,				//ACTION_SLAYER_BLADE
			EFFECTSPRITETYPE_REGENERATION_1_SWORD2_MALE,			//ACTION_SLAYER_SWORD_2
			EFFECTSPRITETYPE_REGENERATION_1_BLADE2_MALE,			//ACTION_SLAYER_BLADE_2
			EFFECTSPRITETYPE_REGENERATION_1_MOTOR_MALE,				//ACTION_SLAYER_MOTOR_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOTOR_STAND

			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BLADE_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BLADE_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BLADE_2_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BLADE_2_FAST
			
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_GUN
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_SWORD
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_BLADE
			
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOVE_GUN,			
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MAGIC_CASTING,	
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_REPEAT
			EFFECTSPRITETYPE_NULL									//ACTION_SLAYER_BLADE_2_REPEAT

		},

		// Regeneration Female  									MAX_ACTIONEFFECTSPRITETYPE 4
		{
			EFFECTSPRITETYPE_REGENERATION_1_STAND_FEMALE,			//ACTION_STAND
			EFFECTSPRITETYPE_REGENERATION_1_MOVE_FEMALE,			//ACTION_MOVE
			EFFECTSPRITETYPE_REGENERATION_1_ATTACK_FEMALE,			//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_REGENERATION_1_DAMAGE_FEMALE,			//ACTION_DAMAGED
			EFFECTSPRITETYPE_NULL,									//ACTION_DRAINED
			EFFECTSPRITETYPE_NULL,									//ACTION_DIE
			
			EFFECTSPRITETYPE_REGENERATION_1_SR_FEMALE,				//ACTION_SLAYER_GUN_SR
			EFFECTSPRITETYPE_REGENERATION_1_AR_FEMALE,				//ACTION_SLAYER_GUN_AR
			EFFECTSPRITETYPE_REGENERATION_1_SG_FEMALE,				//ACTION_SLAYER_GUN_SG
			EFFECTSPRITETYPE_REGENERATION_1_SMG_FEMALE,				//ACTION_SLAYER_GUN_SMG

			EFFECTSPRITETYPE_REGENERATION_1_SWORD_FEMALE,			//ACTION_SLAYER_SWORD
			EFFECTSPRITETYPE_REGENERATION_1_BLADE_FEMALE,			//ACTION_SLAYER_BLADE
			EFFECTSPRITETYPE_REGENERATION_1_SWORD2_FEMALE,			//ACTION_SLAYER_SWORD_2
			EFFECTSPRITETYPE_REGENERATION_1_BLADE2_FEMALE,			//ACTION_SLAYER_BLADE_2
			EFFECTSPRITETYPE_REGENERATION_1_MOTOR_FEMALE,			//ACTION_SLAYER_MOTOR_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOTOR_STAND

			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BLADE_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BLADE_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BLADE_2_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BLADE_2_FAST
			
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_GUN
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_SWORD
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_BLADE
			
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOVE_GUN,			
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MAGIC_CASTING,	
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_REPEAT
			EFFECTSPRITETYPE_NULL									//ACTION_SLAYER_BLADE_2_REPEAT
		},
#endif //__EFFECT_RENEWAL
#if __CONTENTS(__EFFECT_RENEWAL)
		// BERSERKER Male 											MAX_ACTIONEFFECTSPRITETYPE 4
		{
			EFFECTSPRITETYPE_BERSERKER_1_STAND_MALE,				//ACTION_STAND
			EFFECTSPRITETYPE_BERSERKER_1_MOVE_MALE,					//ACTION_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_BERSERKER_1_DAMAGE_MALE,				//ACTION_DAMAGED
			EFFECTSPRITETYPE_BERSERKER_1_DRAIN_MALE,				//ACTION_DRAINED			
			EFFECTSPRITETYPE_BERSERKER_1_DIE_MALE,					//ACTION_DIE				
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD
			EFFECTSPRITETYPE_BERSERKER_1_BLADE_MALE,				//ACTION_SLAYER_BLADE
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2
			EFFECTSPRITETYPE_BERSERKER_1_BLADE2_MALE,				//ACTION_SLAYER_BLADE_2
			EFFECTSPRITETYPE_BERSERKER_1_MOTOR_MOVE_MALE,			//ACTION_SLAYER_MOTOR_MOVE
			EFFECTSPRITETYPE_BERSERKER_1_MOTOR_STAND_MALE,			//ACTION_SLAYER_MOTOR_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_FAST
			EFFECTSPRITETYPE_BERSERKER_1_BLADE_SLOW_MALE,			//ACTION_SLAYER_BLADE_SLOW
			EFFECTSPRITETYPE_BERSERKER_1_BLADE_FAST_MALE,			//ACTION_SLAYER_BLADE_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_FAST
			EFFECTSPRITETYPE_BERSERKER_1_BLADE2_SLOW_MALE,			//ACTION_SLAYER_BLADE_2_SLOW
			EFFECTSPRITETYPE_BERSERKER_1_BLADE2_FAST_MALE,			//ACTION_SLAYER_BLADE_2_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_GUN
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_SWORD
			EFFECTSPRITETYPE_BERSERKER_1_BATTLE_STAND_BLADE_MALE,	//ACTION_SLAYER_BATTLE_STAND_BLADE
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOVE_GUN,			
			EFFECTSPRITETYPE_BERSERKER_1_MAGIC_CASTING_MALE,		//ACTION_SLAYER_MAGIC_CASTING,	
			EFFECTSPRITETYPE_BERSERKER_1_BLADE_2_REPEAT_MALE,		//ACTION_SLAYER_SWORD_2_REPEAT
			EFFECTSPRITETYPE_NULL									//ACTION_SLAYER_BLADE_2_REPEAT
		},

		// BERSERKER Female 										MAX_ACTIONEFFECTSPRITETYPE 5
		{
			EFFECTSPRITETYPE_BERSERKER_1_STAND_FEMALE,				//ACTION_STAND
			EFFECTSPRITETYPE_BERSERKER_1_MOVE_FEMALE,				//ACTION_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_BERSERKER_1_DAMAGE_FEMALE,				//ACTION_DAMAGED
			EFFECTSPRITETYPE_BERSERKER_1_DRAIN_FEMALE,				//ACTION_DRAINED			
			EFFECTSPRITETYPE_BERSERKER_1_DIE_FEMALE,				//ACTION_DIE				
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD
			EFFECTSPRITETYPE_BERSERKER_1_BLADE_FEMALE,				//ACTION_SLAYER_BLADE
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2
			EFFECTSPRITETYPE_BERSERKER_1_BLADE2_FEMALE,				//ACTION_SLAYER_BLADE_2
			EFFECTSPRITETYPE_BERSERKER_1_MOTOR_MOVE_FEMALE,			//ACTION_SLAYER_MOTOR_MOVE
			EFFECTSPRITETYPE_BERSERKER_1_MOTOR_STAND_FEMALE,		//ACTION_SLAYER_MOTOR_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_FAST
			EFFECTSPRITETYPE_BERSERKER_1_BLADE_SLOW_FEMALE,			//ACTION_SLAYER_BLADE_SLOW
			EFFECTSPRITETYPE_BERSERKER_1_BLADE_FAST_FEMALE,			//ACTION_SLAYER_BLADE_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_FAST
			EFFECTSPRITETYPE_BERSERKER_1_BLADE2_SLOW_FEMALE,		//ACTION_SLAYER_BLADE_2_SLOW
			EFFECTSPRITETYPE_BERSERKER_1_BLADE2_FAST_FEMALE,		//ACTION_SLAYER_BLADE_2_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_GUN
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_SWORD
			EFFECTSPRITETYPE_BERSERKER_1_BATTLE_STAND_BLADE_FEMALE,	//ACTION_SLAYER_BATTLE_STAND_BLADE
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOVE_GUN,			
			EFFECTSPRITETYPE_BERSERKER_1_MAGIC_CASTING_FEMALE,		//ACTION_SLAYER_MAGIC_CASTING,	
			EFFECTSPRITETYPE_BERSERKER_1_BLADE_2_REPEAT_FEMALE,		//ACTION_SLAYER_SWORD_2_REPEAT
			EFFECTSPRITETYPE_NULL									//ACTION_SLAYER_BLADE_2_REPEAT
		},
#else
		// BERSERKER Male 											MAX_ACTIONEFFECTSPRITETYPE 4
		{
			EFFECTSPRITETYPE_BERSERKER_1_STAND_MALE,				//ACTION_STAND
			EFFECTSPRITETYPE_BERSERKER_1_MOVE_MALE,					//ACTION_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_BERSERKER_1_DAMAGE_MALE,				//ACTION_DAMAGED
			EFFECTSPRITETYPE_NULL,									//ACTION_DRAINED			
			EFFECTSPRITETYPE_NULL,									//ACTION_DIE				
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD
			EFFECTSPRITETYPE_BERSERKER_1_BLADE_MALE,				//ACTION_SLAYER_BLADE
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2
			EFFECTSPRITETYPE_BERSERKER_1_BLADE2_MALE,				//ACTION_SLAYER_BLADE_2
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOTOR_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOTOR_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_FAST
			EFFECTSPRITETYPE_BERSERKER_1_BLADE_SLOW_MALE,			//ACTION_SLAYER_BLADE_SLOW
			EFFECTSPRITETYPE_BERSERKER_1_BLADE_FAST_MALE,			//ACTION_SLAYER_BLADE_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_FAST
			EFFECTSPRITETYPE_BERSERKER_1_BLADE2_SLOW_MALE,			//ACTION_SLAYER_BLADE_2_SLOW
			EFFECTSPRITETYPE_BERSERKER_1_BLADE2_FAST_MALE,			//ACTION_SLAYER_BLADE_2_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_GUN
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_SWORD
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_BLADE
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOVE_GUN,			
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MAGIC_CASTING,	
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_REPEAT
			EFFECTSPRITETYPE_NULL									//ACTION_SLAYER_BLADE_2_REPEAT
		},

		// BERSERKER Female 										MAX_ACTIONEFFECTSPRITETYPE 5
		{
			EFFECTSPRITETYPE_BERSERKER_1_STAND_FEMALE,				//ACTION_STAND
			EFFECTSPRITETYPE_BERSERKER_1_MOVE_FEMALE,				//ACTION_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_BERSERKER_1_DAMAGE_FEMALE,				//ACTION_DAMAGED
			EFFECTSPRITETYPE_NULL,									//ACTION_DRAINED			
			EFFECTSPRITETYPE_NULL,									//ACTION_DIE				
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD
			EFFECTSPRITETYPE_BERSERKER_1_BLADE_FEMALE,				//ACTION_SLAYER_BLADE
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2
			EFFECTSPRITETYPE_BERSERKER_1_BLADE2_FEMALE,				//ACTION_SLAYER_BLADE_2
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOTOR_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOTOR_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_FAST
			EFFECTSPRITETYPE_BERSERKER_1_BLADE_SLOW_FEMALE,			//ACTION_SLAYER_BLADE_SLOW
			EFFECTSPRITETYPE_BERSERKER_1_BLADE_FAST_FEMALE,			//ACTION_SLAYER_BLADE_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_FAST
			EFFECTSPRITETYPE_BERSERKER_1_BLADE2_SLOW_FEMALE,		//ACTION_SLAYER_BLADE_2_SLOW
			EFFECTSPRITETYPE_BERSERKER_1_BLADE2_FAST_FEMALE,		//ACTION_SLAYER_BLADE_2_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_GUN
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_SWORD
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_BLADE
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOVE_GUN,			
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MAGIC_CASTING,	
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_REPEAT
			EFFECTSPRITETYPE_NULL									//ACTION_SLAYER_BLADE_2_REPEAT
		},
#endif //__EFFECT_RENEWAL
//		// HYPNOSIS Male
//		{
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,
//			EFFECTSPRITETYPE_HYPNOSIS_MOVE_MALE,				
//			EFFECTSPRITETYPE_HYPNOSIS_ATTACK_MALE,			
//			EFFECTSPRITETYPE_HYPNOSIS_MAGIC_FEMALE,			// 남자꺼 없네
//			EFFECTSPRITETYPE_HYPNOSIS_DAMAGE_MALE,			
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,			
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,				
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,
//			EFFECTSPRITETYPE_HYPNOSIS_ATTACK_MALE,		
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,	//ACTION_SWORD_SLOW	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,	//ACTION_SWORD_FAST	
//			EFFECTSPRITETYPE_HYPNOSIS_ATTACK_SLOW_MALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_ATTACK_FAST_MALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,	//ACTION_SWORD_2_SLOW	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,	//ACTION_SWORD_2_FAST
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_MALE
//		},
//
//		// HYPNOSIS Female
//		{
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,
//			EFFECTSPRITETYPE_HYPNOSIS_MOVE_FEMALE,				
//			EFFECTSPRITETYPE_HYPNOSIS_ATTACK_FEMALE,			
//			EFFECTSPRITETYPE_HYPNOSIS_MAGIC_FEMALE,			
//			EFFECTSPRITETYPE_HYPNOSIS_DAMAGE_FEMALE,			
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,			
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,				
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,
//			EFFECTSPRITETYPE_HYPNOSIS_ATTACK_FEMALE,		
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,	//ACTION_SWORD_SLOW	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,	//ACTION_SWORD_FAST	
//			EFFECTSPRITETYPE_HYPNOSIS_ATTACK_SLOW_FEMALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_ATTACK_FAST_FEMALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,	//ACTION_SWORD_2_SLOW	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,	//ACTION_SWORD_2_FAST
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE,	
//			EFFECTSPRITETYPE_HYPNOSIS_STAND_FEMALE
//		},
#if __CONTENTS(__EFFECT_RENEWAL)
		// Extreme Male 											MAX_ACTIONEFFECTSPRITETYPE 6
		{
			EFFECTSPRITETYPE_EXTREME_L_1_STAND_MALE,				//ACTION_STAND				
			EFFECTSPRITETYPE_EXTREME_L_1_MOVE_MALE,					//ACTION_MOVE		
			EFFECTSPRITETYPE_EXTREME_L_1_ATTACK_MALE,				//ACTION_ATTACK		
			EFFECTSPRITETYPE_EXTREME_L_MAGIC_ATTACK_MALE,			//ACTION_MAGIC
			EFFECTSPRITETYPE_EXTREME_L_1_DAMAGE_MALE,				//ACTION_DAMAGED		
			EFFECTSPRITETYPE_EXTREME_L_DRIN_MALE,					//ACTION_DRAINED			흡혈당하기
			EFFECTSPRITETYPE_EXTREME_L_DIE_MALE,					//ACTION_DIE				죽기
			EFFECTSPRITETYPE_EXTREME_L_DRIN_ATTACK_MALE,			//ACTION_VAMPIRE_DRAIN = ACTIO
			EFFECTSPRITETYPE_EXTREME_L_1_ATTACK_SLOW_MALE,			//ACTION_VAMPIRE_ATTACK_SLOW,	
			EFFECTSPRITETYPE_EXTREME_L_1_ATTACK_FAST_MALE,			//ACTION_VAMPIRE_ATTACK_FAST,	
			EFFECTSPRITETYPE_EXTREME_L_ATTACK_2_MALE,				//ACTION_VAMPIRE_ATTACK_2,		
			EFFECTSPRITETYPE_EXTREME_L_ATTACK_2_SLOW_MALE,			//ACTION_VAMPIRE_ATTACK_2_SLOW
			EFFECTSPRITETYPE_EXTREME_L_ATTACK_2_FAST_MALE,			//ACTION_VAMPIRE_ATTACK_2_FAST
			EFFECTSPRITETYPE_EXTREME_L_ATTACK_3_MALE,				//ACTION_VAMPIRE_ATTACK_3,	
			EFFECTSPRITETYPE_EXTREME_L_ATTACK_3_SLOW_MALE,			//ACTION_VAMPIRE_ATTACK_3_SLOW
			EFFECTSPRITETYPE_EXTREME_L_ATTACK_3_FAST_MALE,			//ACTION_VAMPIRE_ATTACK_3_FAST
			EFFECTSPRITETYPE_EXTREME_L_MAGIC_CASTING_MALE,			//ACTION_VAMPIRE_MAGIC_CASTING
			EFFECTSPRITETYPE_NULL,
			EFFECTSPRITETYPE_NULL,
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,		
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,
		},

		// Extreme FEMALE 											MAX_ACTIONEFFECTSPRITETYPE 7
		{
			EFFECTSPRITETYPE_EXTREME_L_1_STAND_FEMALE,				//ACTION_STAND				
			EFFECTSPRITETYPE_EXTREME_L_1_MOVE_FEMALE,				//ACTION_MOVE		
			EFFECTSPRITETYPE_EXTREME_L_1_ATTACK_FEMALE,				//ACTION_ATTACK		
			EFFECTSPRITETYPE_EXTREME_L_MAGIC_ATTACK_FEMALE,			//ACTION_MAGIC
			EFFECTSPRITETYPE_EXTREME_L_1_DAMAGE_FEMALE,				//ACTION_DAMAGED		
			EFFECTSPRITETYPE_EXTREME_L_DRIN_FEMALE,					//ACTION_DRAINED			흡혈당하기
			EFFECTSPRITETYPE_EXTREME_L_DIE_FEMALE,					//ACTION_DIE				죽기
			EFFECTSPRITETYPE_EXTREME_L_DRIN_ATTACK_FEMALE,			//ACTION_VAMPIRE_DRAIN = ACTIO
			EFFECTSPRITETYPE_EXTREME_L_1_ATTACK_SLOW_FEMALE,		//ACTION_VAMPIRE_ATTACK_SLOW,	
			EFFECTSPRITETYPE_EXTREME_L_1_ATTACK_FAST_FEMALE,		//ACTION_VAMPIRE_ATTACK_FAST,	
			EFFECTSPRITETYPE_EXTREME_L_ATTACK_2_FEMALE,				//ACTION_VAMPIRE_ATTACK_2,		
			EFFECTSPRITETYPE_EXTREME_L_ATTACK_2_SLOW_FEMALE,		//ACTION_VAMPIRE_ATTACK_2_SLOW
			EFFECTSPRITETYPE_EXTREME_L_ATTACK_2_FAST_FEMALE,		//ACTION_VAMPIRE_ATTACK_2_FAST
			EFFECTSPRITETYPE_EXTREME_L_ATTACK_3_FEMALE,				//ACTION_VAMPIRE_ATTACK_3,	
			EFFECTSPRITETYPE_EXTREME_L_ATTACK_3_SLOW_FEMALE,		//ACTION_VAMPIRE_ATTACK_3_SLOW
			EFFECTSPRITETYPE_EXTREME_L_ATTACK_3_FAST_FEMALE,		//ACTION_VAMPIRE_ATTACK_3_FAST
			EFFECTSPRITETYPE_EXTREME_L_MAGIC_CASTING_FEMALE,		//ACTION_VAMPIRE_MAGIC_CASTING
			EFFECTSPRITETYPE_NULL,
			EFFECTSPRITETYPE_NULL,
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,		
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,
		},
#else
		// Extreme Male 											MAX_ACTIONEFFECTSPRITETYPE 6
		{
			EFFECTSPRITETYPE_EXTREME_L_1_STAND_MALE,				//ACTION_STAND				
			EFFECTSPRITETYPE_EXTREME_L_1_MOVE_MALE,					//ACTION_MOVE		
			EFFECTSPRITETYPE_EXTREME_L_1_ATTACK_MALE,				//ACTION_ATTACK		
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_EXTREME_L_1_DAMAGE_MALE,				//ACTION_DAMAGED		
			EFFECTSPRITETYPE_NULL,									//ACTION_DRAINED			흡혈당하기
			EFFECTSPRITETYPE_NULL,									//ACTION_DIE				죽기
			EFFECTSPRITETYPE_NULL,									//ACTION_VAMPIRE_DRAIN = ACTIO
			EFFECTSPRITETYPE_EXTREME_L_1_ATTACK_SLOW_MALE,			//ACTION_VAMPIRE_ATTACK_SLOW,	
			EFFECTSPRITETYPE_EXTREME_L_1_ATTACK_FAST_MALE,			//ACTION_VAMPIRE_ATTACK_FAST,	
			EFFECTSPRITETYPE_NULL,									//ACTION_VAMPIRE_ATTACK_2,		
			EFFECTSPRITETYPE_NULL,									//ACTION_VAMPIRE_ATTACK_2_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_VAMPIRE_ATTACK_2_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_VAMPIRE_ATTACK_3,	
			EFFECTSPRITETYPE_NULL,									//ACTION_VAMPIRE_ATTACK_3_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_VAMPIRE_ATTACK_3_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_VAMPIRE_MAGIC_CASTING
			EFFECTSPRITETYPE_NULL,
			EFFECTSPRITETYPE_NULL,
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,		
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,
		},

		// Extreme FEMALE 											MAX_ACTIONEFFECTSPRITETYPE 7
		{
			EFFECTSPRITETYPE_EXTREME_L_1_STAND_FEMALE,				//ACTION_STAND				
			EFFECTSPRITETYPE_EXTREME_L_1_MOVE_FEMALE,				//ACTION_MOVE		
			EFFECTSPRITETYPE_EXTREME_L_1_ATTACK_FEMALE,				//ACTION_ATTACK		
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_EXTREME_L_1_DAMAGE_FEMALE,				//ACTION_DAMAGED		
			EFFECTSPRITETYPE_NULL,									//ACTION_DRAINED			흡혈당하기
			EFFECTSPRITETYPE_NULL,									//ACTION_DIE				죽기
			EFFECTSPRITETYPE_NULL,									//ACTION_VAMPIRE_DRAIN = ACTIO
			EFFECTSPRITETYPE_EXTREME_L_1_ATTACK_SLOW_FEMALE,		//ACTION_VAMPIRE_ATTACK_SLOW,	
			EFFECTSPRITETYPE_EXTREME_L_1_ATTACK_FAST_FEMALE,		//ACTION_VAMPIRE_ATTACK_FAST,	
			EFFECTSPRITETYPE_NULL,									//ACTION_VAMPIRE_ATTACK_2,		
			EFFECTSPRITETYPE_NULL,									//ACTION_VAMPIRE_ATTACK_2_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_VAMPIRE_ATTACK_2_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_VAMPIRE_ATTACK_3,	
			EFFECTSPRITETYPE_NULL,									//ACTION_VAMPIRE_ATTACK_3_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_VAMPIRE_ATTACK_3_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_VAMPIRE_MAGIC_CASTING
			EFFECTSPRITETYPE_NULL,
			EFFECTSPRITETYPE_NULL,
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,		
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,	
			EFFECTSPRITETYPE_NULL,
		},
#endif //__EFFECT_RENEWAL

		// Slayer GrandMaster Male 									MAX_ACTIONEFFECTSPRITETYPE 8
		{
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_STAND-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-정지-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_MOVE-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,			// 슬레-그랜드마스터-걷기-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_ATTACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-공격-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_MAGIC-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-마법-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_DAMAGED-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-맞기-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_STAND-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-정지-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_STAND-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-정지-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SR-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,			// 슬레-그랜드마스터-SR-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_AR-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,			// 슬레-그랜드마스터-AR-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SWORD-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-검-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_BLADE-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-도-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_THROW_WEAPON-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,	// 슬레-그랜드마스터-던지기-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_STAND-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-정지-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SG-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,			// 슬레-그랜드마스터-SG-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SMG-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,			// 슬레-그랜드마스터-SMG-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SWORD_2-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-검기술-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_BLADE_2-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-도기술-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_THROW_POTION-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,	// 슬레-그랜드마스터-던지기2-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_STAND-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-정지-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SR_SLOW-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-SRS-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SR_FAST-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-SRF-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_AR_SLOW-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-ARS-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_AR_FAST-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-ARF-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SG_SLOW-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-SGS-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SG_FAST-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-SGF-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SMG_SLOW-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-SMGS-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SMG_FAST-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-SMGF-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SWORD_SLOW-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,	// 슬레-그랜드마스터-검S-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SWORD_FAST-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,	// 슬레-그랜드마스터-검F-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_BLADE_SLOW-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,	// 슬레-그랜드마스터-도S-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_BLADE_FAST-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,	// 슬레-그랜드마스터-도F-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SWORD_2_SLOW-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,	// 슬레-그랜드마스터-검기술S-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_SWORD_2_FAST-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,	// 슬레-그랜드마스터-검기술F-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_BLADE_2_SLOW-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,	// 슬레-그랜드마스터-도기술S-남자
			EFFECTSPRITETYPE_SLAYER_MALE_GRANDMASTER_BLADE_2_FAST-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,	// 슬레-그랜드마스터-도기술F-남자
		},

		// Slayer GrandMaster Female 								MAX_ACTIONEFFECTSPRITETYPE 9
		{
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_STAND-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,			// 슬레-그랜드마스터-정지-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_MOVE-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,			// 슬레-그랜드마스터-걷기-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_ATTACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,			// 슬레-그랜드마스터-공격-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_MAGIC-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,			// 슬레-그랜드마스터-마법-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_DAMAGED-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-맞기-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_STAND-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,			// 슬레-그랜드마스터-정지-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_STAND-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,			// 슬레-그랜드마스터-정지-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SR-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,				// 슬레-그랜드마스터-SR-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_AR-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,				// 슬레-그랜드마스터-AR-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SWORD-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,			// 슬레-그랜드마스터-검-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_BLADE-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,			// 슬레-그랜드마스터-도-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_THROW_WEAPON-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,	// 슬레-그랜드마스터-던지기-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_STAND-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,			// 슬레-그랜드마스터-정지-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SG-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,				// 슬레-그랜드마스터-SG-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SMG-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,			// 슬레-그랜드마스터-SMG-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SWORD_2-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-검기술-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_BLADE_2-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-도기술-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_THROW_POTION-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,	// 슬레-그랜드마스터-던지기2-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_STAND-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,			// 슬레-그랜드마스터-정지-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SR_SLOW-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-SRS-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SR_FAST-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-SRF-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_AR_SLOW-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-ARS-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_AR_FAST-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-ARF-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SG_SLOW-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-SGS-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SG_FAST-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-SGF-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SMG_SLOW-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-SMGS-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SMG_FAST-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-SMGF-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SWORD_SLOW-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-검S-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SWORD_FAST-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-검F-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_BLADE_SLOW-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-도S-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_BLADE_FAST-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 슬레-그랜드마스터-도F-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SWORD_2_SLOW-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,	// 슬레-그랜드마스터-검기술S-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_SWORD_2_FAST-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,	// 슬레-그랜드마스터-검기술F-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_BLADE_2_SLOW-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,	// 슬레-그랜드마스터-도기술S-여자
			EFFECTSPRITETYPE_SLAYER_FEMALE_GRANDMASTER_BLADE_2_FAST-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,	// 슬레-그랜드마스터-도기술F-여자
		},

		// Vampire Grandmaster Male 								MAX_ACTIONEFFECTSPRITETYPE 10
		{
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_ATTACK_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자공격뒤n
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_MAGIC_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자마법뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_DAMAGED_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,	// 뱀파이어-남자맞기뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_DRAINED_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,	// 뱀파이어-남자흡혈당하기뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_DRAIN_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자흡혈하기뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_ATTACK_SLOW_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,// 뱀파이어-남자공격뒤s
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_ATTACK_FAST_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,// 뱀파이어-남자공격뒤f
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_MALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-남자정지뒤
		},

		// Vampire Grandmaster Female 								MAX_ACTIONEFFECTSPRITETYPE 11
		{
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_ATTACK_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자공격뒤n
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_MAGIC_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자마법뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_DAMAGED_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자맞기뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_DRAINED_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자흡혈당하기뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_DRAIN_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자흡혈하기뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_ATTACK_SLOW_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,	// 뱀파이어-여자공격뒤s
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_ATTACK_FAST_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,	// 뱀파이어-여자공격뒤f
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
			EFFECTSPRITETYPE_VAMPIRE_GRANDMASTER_FEMALE_STAND_BACK-MAX_EFFECTSPRITETYPE_ALPHAEFFECT,		// 뱀파이어-여자정지뒤
		},

		
#if __CONTENTS(__EFFECT_RENEWAL)
		//ACTIONEFFECTSPRITETYPE_CHARGING_POWER_MALE, 				MAX_ACTIONEFFECTSPRITETYPE 12
		{
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_STOP_1,			//ACTION_STAND				
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_WALK_1,			//ACTION_MOVE
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_ATTACK_NORMAL_1,	//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_DAMAGED_1,			//ACTION_DAMAGED
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_DRIN_1,			//ACTION_DRAINED			흡혈당하기
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_DIE_1,				//ACTION_DIE				죽기
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SRR
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_ARR
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SGWORD
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_ATTACK_NORMAL_1,	//ACTION_SLAYER_BLADE
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_SKILL_NORMAL_1,	//ACTION_SLAYER_BLADE_2
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOTOR_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOTOR_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR_SLOWR SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR_FASTR FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG_SLOWR SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG_FASTR FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG_SLOWG SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG_FASTG FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_SLOWMG SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_FASTMG FAST
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_ATTACK_SLOW_1,		//ACTION_SLAYER_BLADE_SLOWWORD SLOW
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_ATTACK_FAST_1,		//ACTION_SLAYER_BLADE_FASTWORD FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_FAST
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_SKILL_SLOW_1,		//ACTION_SLAYER_BLADE_2_SLOW
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_SKILL_FAST_1,		//ACTION_SLAYER_BLADE_2_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_GUN
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_SWORD
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_BATTLE_STAND_1,	//ACTION_SLAYER_BATTLE_STAND_BLADE

			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOVE_GUN,			
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_MAGIC_CASTING_1,	//ACTION_SLAYER_MAGIC_CASTING,	
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_REPEAT
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_BLADE_2_REPEAT_1,	//ACTION_SLAYER_BLADE_2_REPEAT
		},
		//ACTIONEFFECTSPRITETYPE_CHARGING_POWER_FEMALE, 			MAX_ACTIONEFFECTSPRITETYPE 13
		{
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_STOP_1,			//ACTION_STAND				
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_WALK_1,			//ACTION_MOVE
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_ATTACK_NORMAL_1,	//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_DAMAGED_1,		//ACTION_DAMAGED
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_DRIN_1,			//ACTION_DRAINED			흡혈당하기
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_DIE_1,			//ACTION_DIE				죽기
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SRR
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_ARR
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SGWORD
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_ATTACK_NORMAL_1,	//ACTION_SLAYER_BLADE
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_SKILL_NORMAL_1,	//ACTION_SLAYER_BLADE_2
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOTOR_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOTOR_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR_SLOWR SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR_FASTR FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG_SLOWR SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG_FASTR FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG_SLOWG SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG_FASTG FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_SLOWMG SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_FASTMG FAST
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_ATTACK_SLOW_1,	//ACTION_SLAYER_BLADE_SLOWWORD SLOW
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_ATTACK_FAST_1,	//ACTION_SLAYER_BLADE_FASTWORD FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_FAST
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_SKILL_SLOW_1,	//ACTION_SLAYER_BLADE_2_SLOW
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_SKILL_FAST_1,	//ACTION_SLAYER_BLADE_2_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_GUN
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_SWORD
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_BATTLE_STAND_1,	//ACTION_SLAYER_BATTLE_STAND_BLADE

			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOVE_GUN,			
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_MAGIC_CASTING_1,	//ACTION_SLAYER_MAGIC_CASTING,	
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_REPEAT
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_BLADE_2_REPEAT_1,//ACTION_SLAYER_BLADE_2_REPEAT
		},
#else
				//ACTIONEFFECTSPRITETYPE_CHARGING_POWER_MALE, 		MAX_ACTIONEFFECTSPRITETYPE 12
		{
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_STOP_1,			//ACTION_STAND				
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_WALK_1,			//ACTION_MOVE
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_ATTACK_NORMAL_1,	//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_DAMAGED_1,			//ACTION_DAMAGED
			EFFECTSPRITETYPE_NULL,									//ACTION_DRAINED		흡혈당하기
			EFFECTSPRITETYPE_NULL,									//ACTION_DIE			죽기
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SRR
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_ARR
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SGWORD
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_ATTACK_NORMAL_1,	//ACTION_SLAYER_BLADE
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_SKILL_NORMAL_1,	//ACTION_SLAYER_BLADE_2
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOTOR_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOTOR_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR_SLOWR SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR_FASTR FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG_SLOWR SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG_FASTR FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG_SLOWG SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG_FASTG FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_SLOWMG SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_FASTMG FAST
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_ATTACK_SLOW_1,		//ACTION_SLAYER_BLADE_SLOWWORD SLOW
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_ATTACK_FAST_1,		//ACTION_SLAYER_BLADE_FASTWORD FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_FAST
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_SKILL_SLOW_1,		//ACTION_SLAYER_BLADE_2_SLOW
			EFFECTSPRITETYPE_CHARGING_POWER_MALE_SKILL_FAST_1,		//ACTION_SLAYER_BLADE_2_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_GUN
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_SWORD
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_BLADE

			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOVE_GUN,			
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MAGIC_CASTING,	
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_REPEAT
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BLADE_2_REPEAT
		},
		//ACTIONEFFECTSPRITETYPE_CHARGING_POWER_FEMALE, 			MAX_ACTIONEFFECTSPRITETYPE 13
		{
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_STOP_1,			//ACTION_STAND				
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_WALK_1,			//ACTION_MOVE
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_ATTACK_NORMAL_1,	//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_DAMAGED_1,		//ACTION_DAMAGED
			EFFECTSPRITETYPE_NULL,									//ACTION_DRAINED			흡혈당하기
			EFFECTSPRITETYPE_NULL,									//ACTION_DIE				죽기
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SRR
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_ARR
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SGWORD
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_ATTACK_NORMAL_1,	//ACTION_SLAYER_BLADE
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_SKILL_NORMAL_1,	//ACTION_SLAYER_BLADE_2
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOTOR_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOTOR_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR_SLOWR SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR_FASTR FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG_SLOWR SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG_FASTR FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG_SLOWG SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG_FASTG FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_SLOWMG SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_FASTMG FAST
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_ATTACK_SLOW_1,	//ACTION_SLAYER_BLADE_SLOWWORD SLOW
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_ATTACK_FAST_1,	//ACTION_SLAYER_BLADE_FASTWORD FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_FAST
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_SKILL_SLOW_1,	//ACTION_SLAYER_BLADE_2_SLOW
			EFFECTSPRITETYPE_CHARGING_POWER_FEMALE_SKILL_FAST_1,	//ACTION_SLAYER_BLADE_2_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_GUN
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_SWORD
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_BLADE

			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOVE_GUN,			
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MAGIC_CASTING,	
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_REPEAT
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BLADE_2_REPEAT
		},
#endif //__EFFECT_RENEWAL

		// Vampire Ghost Black 										MAX_ACTIONEFFECTSPRITETYPE 14
		{
			EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_STAND_BLACK,
			EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_MOVE_BLACK,
		},

		// Vampire Ghost Red 										MAX_ACTIONEFFECTSPRITETYPE 15
		{
			EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_STAND_RED,
			EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_MOVE_RED,
		},

		// Vampire Ghost Blue 										MAX_ACTIONEFFECTSPRITETYPE 16
		{
			EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_STAND_BLUE,
			EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_MOVE_BLUE,
		},

		// Vampire Ghost Yellow 									MAX_ACTIONEFFECTSPRITETYPE 17
		{
			EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_STAND_YELLOW,
			EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_MOVE_YELLOW,
		},

		// Vampire Ghost Green 										MAX_ACTIONEFFECTSPRITETYPE 18
		{
			EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_STAND_GREEN,
			EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_MOVE_GREEN,
		},

		// Vampire Ghost White 										MAX_ACTIONEFFECTSPRITETYPE 19
		{
			EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_STAND_WHITE,
			EFFECTSPRITETYPE_AC_VAMPIRE_GHOST_MOVE_WHITE,
		},
#if __CONTENTS(__FAST_TRANSFORTER)
		//ACTIONEFFECTSPRITETYPE_VAMPIRE_WING_GRAY, 				MAX_ACTIONEFFECTSPRITETYPE 20
		{
			EFFECTSPRITETYPE_VAMPIRE_WING_STOP_GRAY,
			EFFECTSPRITETYPE_VAMPIRE_WING_MOVE_GRAY,
		},

		//ACTIONEFFECTSPRITETYPE_VAMPIRE_WING_RED, 					MAX_ACTIONEFFECTSPRITETYPE 21
		{
			EFFECTSPRITETYPE_VAMPIRE_WING_STOP_RED,
			EFFECTSPRITETYPE_VAMPIRE_WING_MOVE_RED,
		},
		//ACTIONEFFECTSPRITETYPE_VAMPIRE_WING_BLUE, 				MAX_ACTIONEFFECTSPRITETYPE 22
		{
			EFFECTSPRITETYPE_VAMPIRE_WING_STOP_BLUE,
			EFFECTSPRITETYPE_VAMPIRE_WING_MOVE_BLUE,
		},
		//ACTIONEFFECTSPRITETYPE_VAMPIRE_WING_ORANGE, 				MAX_ACTIONEFFECTSPRITETYPE 23
		{
			EFFECTSPRITETYPE_VAMPIRE_WING_STOP_ORANGE,
			EFFECTSPRITETYPE_VAMPIRE_WING_MOVE_ORANGE,
		},

		//ACTIONEFFECTSPRITETYPE_VAMPIRE_WING_GREEN 				MAX_ACTIONEFFECTSPRITETYPE 24
		{
			EFFECTSPRITETYPE_VAMPIRE_WING_STOP_GREEN,
			EFFECTSPRITETYPE_VAMPIRE_WING_MOVE_GREEN,
		},
		// 															MAX_ACTIONEFFECTSPRITETYPE 25
		{
			EFFECTSPRITETYPE_NULL,									//ACTION_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_NULL,									//ACTION_DAMAGED
			EFFECTSPRITETYPE_NULL,									//ACTION_DRAINED
			EFFECTSPRITETYPE_NULL,									//ACTION_DIE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MAGIC_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_DRAIN
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_FAST
			EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_BLUE_STOP,			//ACTION_OUSTERS_WING_STAND
			EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_BLUE_MOVE,			//ACTION_OUSTERS_WING_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_UNICORN_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_WING_MOVE
		},
		// 															MAX_ACTIONEFFECTSPRITETYPE 26
		{
			EFFECTSPRITETYPE_NULL,									//ACTION_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_NULL,									//ACTION_DAMAGED
			EFFECTSPRITETYPE_NULL,									//ACTION_DRAINED
			EFFECTSPRITETYPE_NULL,									//ACTION_DIE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MAGIC_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_DRAIN
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_SLOW	
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_FAST
			EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_YELLOW_STOP,		//ACTION_OUSTERS_WING_STAND
			EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_YELLOW_MOVE,		//ACTION_OUSTERS_WING_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_UNICORN_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_WING_MOVE
		},
		// 															MAX_ACTIONEFFECTSPRITETYPE 27
		{
			EFFECTSPRITETYPE_NULL,									//ACTION_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_NULL,									//ACTION_DAMAGED
			EFFECTSPRITETYPE_NULL,									//ACTION_DRAINED
			EFFECTSPRITETYPE_NULL,									//ACTION_DIE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MAGIC_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_DRAIN
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_SLOW	
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_FAST
			EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_RED_STOP,			//ACTION_OUSTERS_WING_STAND
			EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_RED_MOVE,			//ACTION_OUSTERS_WING_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_UNICORN_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_WING_MOVE
		},
		//		 													MAX_ACTIONEFFECTSPRITETYPE 28
		{
			EFFECTSPRITETYPE_NULL,									//ACTION_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_NULL,									//ACTION_DAMAGED
			EFFECTSPRITETYPE_NULL,									//ACTION_DRAINED
			EFFECTSPRITETYPE_NULL,									//ACTION_DIE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MAGIC_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_DRAIN
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_SLOW	
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_FAST
			EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_ORANGE_STOP,		//ACTION_OUSTERS_WING_STAND
			EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_ORANGE_MOVE,		//ACTION_OUSTERS_WING_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_UNICORN_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_WING_MOVE
		},
		// 															MAX_ACTIONEFFECTSPRITETYPE 29
		{
			EFFECTSPRITETYPE_NULL,									//ACTION_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_NULL,									//ACTION_DAMAGED
			EFFECTSPRITETYPE_NULL,									//ACTION_DRAINED
			EFFECTSPRITETYPE_NULL,									//ACTION_DIE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MAGIC_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_DRAIN
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_SLOW	
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_FAST
			EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_YELLOWGREEN_STOP,	//ACTION_OUSTERS_WING_STAND
			EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_YELLOWGREEN_MOVE,	//ACTION_OUSTERS_WING_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_UNICORN_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_WING_MOVE
		},
//		 															MAX_ACTIONEFFECTSPRITETYPE 30
		{
			EFFECTSPRITETYPE_NULL,									//ACTION_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_NULL,									//ACTION_DAMAGED
			EFFECTSPRITETYPE_NULL,									//ACTION_DRAINED
			EFFECTSPRITETYPE_NULL,									//ACTION_DIE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MAGIC_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_DRAIN
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_SLOW	
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_FAST
			EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_BLUEGREEN_STOP,		//ACTION_OUSTERS_WING_STAND
			EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_BLUEGREEN_MOVE,		//ACTION_OUSTERS_WING_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_UNICORN_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_WING_MOVE
		},
		// 															MAX_ACTIONEFFECTSPRITETYPE 31
		{
			EFFECTSPRITETYPE_NULL,									//ACTION_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_NULL,									//ACTION_DAMAGED
			EFFECTSPRITETYPE_NULL,									//ACTION_DRAINED
			EFFECTSPRITETYPE_NULL,									//ACTION_DIE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MAGIC_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_DRAIN
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_SLOW	
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_FAST
			EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_VIOLET_STOP,		//ACTION_OUSTERS_WING_STAND
			EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_VIOLET_MOVE,		//ACTION_OUSTERS_WING_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_UNICORN_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_WING_MOVE
		},
		// 															MAX_ACTIONEFFECTSPRITETYPE 32
		{
			EFFECTSPRITETYPE_NULL,									//ACTION_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_NULL,									//ACTION_DAMAGED
			EFFECTSPRITETYPE_NULL,									//ACTION_DRAINED
			EFFECTSPRITETYPE_NULL,									//ACTION_DIE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MAGIC_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_DRAIN
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_SLOW	
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_FAST
			EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_WHITE_STOP,			//ACTION_OUSTERS_WING_STAND
			EFFECTSPRITETYPE_OUSTERS_WING_FAIRY_WHITE_MOVE,			//ACTION_OUSTERS_WING_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_UNICORN_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_WING_MOVE
		},
		//		 													MAX_ACTIONEFFECTSPRITETYPE 33
		{
			EFFECTSPRITETYPE_NULL,									//ACTION_STAND				
			EFFECTSPRITETYPE_NULL,									//ACTION_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_NULL,									//ACTION_DAMAGED
			EFFECTSPRITETYPE_NULL,									//ACTION_DRAINED			흡혈당하기
			EFFECTSPRITETYPE_NULL,									//ACTION_DIE				죽기
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SRR
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_ARR
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SGWORD
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BLADE
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BLADE_2
			EFFECTSPRITETYPE_SLAYER_WING_BIKE_MOVE,					//ACTION_SLAYER_MOTOR_MOVE
			EFFECTSPRITETYPE_SLAYER_WING_BIKE_STOP,					//ACTION_SLAYER_MOTOR_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR_SLOWR SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR_FASTR FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG_SLOWR SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG_FASTR FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG_SLOWG SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG_FASTG FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_SLOWMG SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_FASTMG FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BLADE_SLOWWORD SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BLADE_FASTWORD FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BLADE_2_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BLADE_2_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_GUN
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_SWORD
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_BLADE

			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOVE_GUN,			
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MAGIC_CASTING,	
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_REPEAT
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BLADE_2_REPEAT
		},
#endif //__FAST_TRANSFORTER

#if __CONTENTS(__SECOND_TRANSFORTER)
		// ACTIONEFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON 			MAX_ACTIONEFFECTSPRITETYPE 34
		{
			EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_WHITE,
			EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_WHITE,
		},
		// 															MAX_ACTIONEFFECTSPRITETYPE 35
		{
			EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_RED,
			EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_RED,
		},
		// 															MAX_ACTIONEFFECTSPRITETYPE 36
		{
			EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_YELLOW,
			EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_YELLOW,
		},
		//		 													MAX_ACTIONEFFECTSPRITETYPE 37
		{
			EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_BLUEGREEN,
			EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_BLUEGREEN,
		},
		// 															MAX_ACTIONEFFECTSPRITETYPE 38
		{
			EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_BLUE,
			EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_BLUE,
		},
		// 															MAX_ACTIONEFFECTSPRITETYPE 39
		{
			EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_MAZANTA,
			EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_MAZANTA,
		},
		// 															MAX_ACTIONEFFECTSPRITETYPE 40
		{
			EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_VIOLET,
			EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_VIOLET,
		},
		// 															MAX_ACTIONEFFECTSPRITETYPE 41
		{
			EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_STOP_BLACK,
			EFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_MOVE_BLACK,
		},
		// ACTIONEFFECTSPRITETYPE_OUSTERS_UNICORN 					MAX_ACTIONEFFECTSPRITETYPE 42
		{
			EFFECTSPRITETYPE_NULL,									//ACTION_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_NULL,									//ACTION_DAMAGED
			EFFECTSPRITETYPE_NULL,									//ACTION_DRAINED
			EFFECTSPRITETYPE_NULL,									//ACTION_DIE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MAGIC_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_DRAIN
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_SLOW		
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_FAST	
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_WING_STAND	
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_WING_MOVE
			EFFECTSPRITETYPE_OUSTERS_UNICORN_STOP_WHITE,			//ACTION_OUSTERS_UNICORN_STAND
			EFFECTSPRITETYPE_OUSTERS_UNICORN_MOVE_WHITE,			//ACTION_OUSTERS_WING_MOVE
		},
		// 															MAX_ACTIONEFFECTSPRITETYPE 43
		{
			EFFECTSPRITETYPE_NULL,									//ACTION_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_NULL,									//ACTION_DAMAGED
			EFFECTSPRITETYPE_NULL,									//ACTION_DRAINED
			EFFECTSPRITETYPE_NULL,									//ACTION_DIE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MAGIC_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_DRAIN
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_SLOW	
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_FAST	
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_WING_STAND	
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_WING_MOVE
			EFFECTSPRITETYPE_OUSTERS_UNICORN_STOP_RED,				//ACTION_OUSTERS_UNICORN_STAND
			EFFECTSPRITETYPE_OUSTERS_UNICORN_MOVE_RED,				//ACTION_OUSTERS_WING_MOVE
		},
		// 															MAX_ACTIONEFFECTSPRITETYPE 44
		{
			EFFECTSPRITETYPE_NULL,									//ACTION_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_NULL,									//ACTION_DAMAGED
			EFFECTSPRITETYPE_NULL,									//ACTION_DRAINED
			EFFECTSPRITETYPE_NULL,									//ACTION_DIE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MAGIC_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_DRAIN
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_SLOW	
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_FAST	
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_WING_STAND	
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_WING_MOVE
			EFFECTSPRITETYPE_OUSTERS_UNICORN_STOP_YELLOW,			//ACTION_OUSTERS_UNICORN_STAND
			EFFECTSPRITETYPE_OUSTERS_UNICORN_MOVE_YELLOW,			//ACTION_OUSTERS_WING_MOVE
		},
		//															MAX_ACTIONEFFECTSPRITETYPE 45
		{
			EFFECTSPRITETYPE_NULL,									//ACTION_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_NULL,									//ACTION_DAMAGED
			EFFECTSPRITETYPE_NULL,									//ACTION_DRAINED
			EFFECTSPRITETYPE_NULL,									//ACTION_DIE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MAGIC_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_DRAIN
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_SLOW	
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_FAST	
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_WING_STAND	
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_WING_MOVE
			EFFECTSPRITETYPE_OUSTERS_UNICORN_STOP_YELLOWGREEN,		//ACTION_OUSTERS_UNICORN_STAND
			EFFECTSPRITETYPE_OUSTERS_UNICORN_MOVE_YELLOWGREEN,		//ACTION_OUSTERS_WING_MOVE
		},
		// 															MAX_ACTIONEFFECTSPRITETYPE 46
		{
			EFFECTSPRITETYPE_NULL,									//ACTION_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_NULL,									//ACTION_DAMAGED
			EFFECTSPRITETYPE_NULL,									//ACTION_DRAINED
			EFFECTSPRITETYPE_NULL,									//ACTION_DIE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MAGIC_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_DRAIN
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_SLOW	
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_FAST	
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_WING_STAND	
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_WING_MOVE
			EFFECTSPRITETYPE_OUSTERS_UNICORN_STOP_BLUE,				//ACTION_OUSTERS_UNICORN_STAND
			EFFECTSPRITETYPE_OUSTERS_UNICORN_MOVE_BLUE,				//ACTION_OUSTERS_WING_MOVE
		},
		// 															MAX_ACTIONEFFECTSPRITETYPE 47
		{
			EFFECTSPRITETYPE_NULL,									//ACTION_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_NULL,									//ACTION_DAMAGED
			EFFECTSPRITETYPE_NULL,									//ACTION_DRAINED
			EFFECTSPRITETYPE_NULL,									//ACTION_DIE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_MAGIC_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_DRAIN
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_FAST_MOVE_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_ATTACK_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_SLOW	
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_CHAKRAM_FAST	
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_WING_STAND	
			EFFECTSPRITETYPE_NULL,									//ACTION_OUSTERS_WING_MOVE
			EFFECTSPRITETYPE_OUSTERS_UNICORN_STOP_MAZANTA,			//ACTION_OUSTERS_UNICORN_STAND
			EFFECTSPRITETYPE_OUSTERS_UNICORN_MOVE_MAZANTA,			//ACTION_OUSTERS_WING_MOVE
		},
		// ACTIONEFFECTSPRITETYPE_SLAYER_HOVER_VEHICLE
/*		{
			EFFECTSPRITETYPE_NULL,									//ACTION_STAND				
			EFFECTSPRITETYPE_NULL,									//ACTION_MOVE
			EFFECTSPRITETYPE_NULL,									//ACTION_ATTACK
			EFFECTSPRITETYPE_NULL,									//ACTION_MAGIC
			EFFECTSPRITETYPE_NULL,									//ACTION_DAMAGED
			EFFECTSPRITETYPE_NULL,									//ACTION_DRAINED			흡혈당하기
			EFFECTSPRITETYPE_NULL,									//ACTION_DIE				죽기
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SRR
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_ARR
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SGWORD
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BLADE
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BLADE_2
			EFFECTSPRITETYPE_SLAYER_HOVER_VEHICLE_MOVE,				//ACTION_SLAYER_MOTOR_MOVE
			EFFECTSPRITETYPE_SLAYER_HOVER_VEHICLE_STOP,				//ACTION_SLAYER_MOTOR_STAND
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SR_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR_SLOWR SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_AR_FASTR FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG_SLOWR SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SG_FASTR FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG_SLOWG SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_GUN_SMG_FASTG FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_SLOWMG SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_FASTMG FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BLADE_SLOWWORD SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BLADE_FASTWORD FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BLADE_2_SLOW
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BLADE_2_FAST
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_GUN
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_SWORD
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BATTLE_STAND_BLADE

			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MOVE_GUN,			
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_MAGIC_CASTING,	
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_SWORD_2_REPEAT
			EFFECTSPRITETYPE_NULL,									//ACTION_SLAYER_BLADE_2_REPEAT
		},*/
#endif //__SECOND_TRANSFORTER
	};

	// Vampire Ghost
	// Vampire Ghost
	for(ae = ACTIONEFFECTSPRITETYPE_VAMPIRE_ACGHOST_BLACK;
		ae <= 
#if __CONTENTS(__FAST_TRANSFORTER)
			ACTIONEFFECTSPRITETYPE_VAMPIRE_WING_GREEN
#else
			ACTIONEFFECTSPRITETYPE_VAMPIRE_ACGHOST_WHITE
#endif //__FAST_TRANSFORTER
			;
		++ae)
	{
		for (int a = 2; a < ACTION_MAX_SLAYER; ++a)
		{
			actionEST[ae][a] = EFFECTSPRITETYPE_NULL;
		}
	}

#if __CONTENTS(__SECOND_TRANSFORTER)
	for(ae = ACTIONEFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_WHITE;
		ae <= ACTIONEFFECTSPRITETYPE_VAMPIRE_SHAPE_OF_DEMON_BLACK;
		++ae)
	{
		for (int a = 2; a < ACTION_MAX_SLAYER; ++a)
		{
			actionEST[ae][a] = EFFECTSPRITETYPE_NULL;
		}
	}
#endif //__SECOND_TRANSFORTER
	// Set Action Effect Sprite Type Table	
	for (ae=0; ae<MAX_ACTIONEFFECTSPRITETYPE; ae++)
	{
		for (int a=0; a<ACTION_MAX_SLAYER; a++)
		{
			int est = actionEST[ae][a];
			int frameID = est;
			(*g_pActionEffectSpriteTypeTable)[ae][a].FrameID = frameID;
		}
	}

	//------------------------------------------------
	// Save
	//------------------------------------------------
	std::ofstream ActionEffectSpriteTypeTable(g_pFileDef->getProperty("FILE_INFO_ACTIONEFFECTSPRITETYPE").c_str(), std::ios::binary);
	(*g_pActionEffectSpriteTypeTable).SaveToFile(ActionEffectSpriteTypeTable);
	ActionEffectSpriteTypeTable.close();
#endif
	//*/

	//------------------------------------------------
	// Load
	//------------------------------------------------
	ivfstream ActionEffectSpriteTypeTable2;//(FILE_INFO_EFFECTSPRITETYPE, ios::binary);
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_INFO_ACTIONEFFECTSPRITETYPE").c_str(), ActionEffectSpriteTypeTable2))
		return FALSE;
	(*g_pActionEffectSpriteTypeTable).LoadFromFile(ActionEffectSpriteTypeTable2);
	ActionEffectSpriteTypeTable2.close();

	
	InitEffectLight(ScreenEFPK,EFPK);



	//---------------------------------------------------------
	//
	// EFPK 정보 변경
	//
	//---------------------------------------------------------
	int etype, s, d;
	int sprite, light;
	int sprite2, light2;
	int effectSpriteType;


	//---------------------------------------------------------
	// SG
	//---------------------------------------------------------
	// cxySG[holyShooting][male][effectFrame][direction]
	POINT cxySG[2][2][2][8] =	
	{
		// Bullet_of_light
		{
			// effectSpriteType = EFFECTSPRITETYPE_BULLET_OF_LIGHT_SG_MALE;
			{			
				//POINT cxySGMaleHoly[8] =	
				{
					{ -50, -49 },
					{ -34, -29 },
					{ 12, -16 },
					{ 47, -21 },
					{ 65, -39 },
					{ 59, -70 },
					{ 28, -88 },
					{ -23, -75 }
				},

				//POINT cxySG2MaleHoly[8] =
				{
					{ -26, -49 },
					{ -18, -25 },
					{ 14, -14 },
					{ 49, -19 },
					{ 67, -37 },
					{ 60, -58 },
					{ 32, -71 },
					{ -6, -64 }	
				}
			},


			// effectSpriteType = EFFECTSPRITETYPE_BULLET_OF_LIGHT_SG_FEMALE;
			{
				//POINT cxySGFemaleHoly[8] =
				{
					{ -48, -53 },
					{ -34, -33 },
					{ 10, -21 },
					{ 45, -24 },
					{ 62, -42 },
					{ 59, -71 },
					{ 30, -90 },
					{ -20, -79 }
				},

				//POINT cxySG2FemaleHoly[8] =
				{		
					{ -23, -50 },
					{ -17, -32 },
					{ 13, -19 },
					{ 45, -23 },
					{ 64, -39 },
					{ 59, -60 },
					{ 33, -73 },
					{ -3, -68 }
				}
			}
		},
		
		// Normal SG
		{
			// effectSpriteType = EFFECTSPRITETYPE_GUN_SG_MALE;
			{
				//POINT cxySGMale[8] =
				{
					{ -53, -49 },
					{ -35, -30 },
					{ 13, -16 },
					{ 48, -21 },
					{ 66, -39 },
					{ 60, -72 },
					{ 29, -89 },
					{ -25, -78 }
				},

				//POINT cxySG2Male[8] =
				{
					{ -27, -49 },
					{ -18, -25 },
					{ 15, -14 },
					{ 49, -19 },
					{ 68, -37 },
					{ 61, -59 },
					{ 33, -71 },
					{ -6, -64 }
				}
			},
			
			// effectSpriteType = EFFECTSPRITETYPE_GUN_SG_FEMALE;
			{
				//POINT cxySGFemale[8] =
				{
					{ -51, -53 },
					{ -35, -34 },
					{ 11, -21 },
					{ 46, -24 },
					{ 63, -42 },
					{ 60, -73 },
					{ 31, -91 },
					{ -22, -82 }
				},

				//POINT cxySG2Female[8] =
				{
					{ -24, -50 },
					{ -17, -32 },
					{ 14, -19 },
					{ 45, -23 },
					{ 65, -39 },
					{ 60, -61 },
					{ 34, -73 },
					{ -3, -68 }
				}
			}
		}
	};

	// effectType[holyShooting][male]
	int etypeSG[2][2] = 
	{
		{ 
			EFFECTSPRITETYPE_BULLET_OF_LIGHT_SG_MALE - MAX_EFFECTSPRITETYPE_ALPHAEFFECT, 
			EFFECTSPRITETYPE_BULLET_OF_LIGHT_SG_FEMALE  - MAX_EFFECTSPRITETYPE_ALPHAEFFECT
		},

		{ 
			EFFECTSPRITETYPE_GUN_SG_MALE - MAX_EFFECTSPRITETYPE_ALPHAEFFECT, 
			EFFECTSPRITETYPE_GUN_SG_FEMALE  - MAX_EFFECTSPRITETYPE_ALPHAEFFECT
		}
	};
	
	for (etype=0; etype<2; etype++)
//	etype = 0;
	{
		for (s=0; s<2; s++)
		{
			DIRECTION_EFFECTFRAME_ARRAY SG;
			SG.Init( 8 );

			effectSpriteType = etypeSG[etype][s];

			for (d=0; d<8; d++)
			{
				SG[d].Init( 3 );	// 3 frame				

				// frame이 두 개 밖에 없는 경우...는 1
				int secondFrame = (ScreenEFPK[effectSpriteType][d].GetSize()==2)? 1 : 2;

				sprite = ScreenEFPK[effectSpriteType][d][0].GetSpriteID();
				light = ScreenEFPK[effectSpriteType][d][0].GetLight();

				sprite2 = ScreenEFPK[effectSpriteType][d][secondFrame].GetSpriteID();
				light2 = ScreenEFPK[effectSpriteType][d][secondFrame].GetLight();
				
				for (int f=0; f<SG[d].GetSize()-1; f++)
				{
					SG[d][f].Set( sprite, cxySG[etype][s][0][d].x, cxySG[etype][s][0][d].y, light, false );
				}

				SG[d][SG[d].GetSize()-1].Set( sprite2, cxySG[etype][s][1][d].x, cxySG[etype][s][1][d].y, light2, false );
			}

			// 바꿈..
			ScreenEFPK[effectSpriteType] = SG;
		}
	}

	


	//---------------------------------------------------------
	// TR
	//---------------------------------------------------------
	// cxyTR[holyShooting][male][effectFrame][direction]
	POINT cxyTR[2][2][2][8] =	
	{
		// Holy
		{
			//effectSpriteType = EFFECTSPRITETYPE_HOLY_SHOOTING_TR_MALE;
			{
				//POINT cxyTR[8] =
				{
					{ -74, -56 },
					{ -50, -25 },
					{ 14, -10 },
					{ 67, -19 },
					{ 89, -48 },
					{ 74, -88 },
					{ 26, -109 },
					{ -41, -91 }
				},
				
				// 희미한 불꽃 frame
				//POINT cxyTR2[8] =
				{
					{ -49, -52 },
					{ -33, -23 },
					{ 17, -7 },
					{ 68, -18 },
					{ 91, -45 },
					{ 75, -76 },
					{ 29, -92 },
					{ -24, -81 }
				}
			},
			
			//effectSpriteType = EFFECTSPRITETYPE_HOLY_SHOOTING_TR_FEMALE;
			{
				//POINT cxyTR[8] =
				{
					{ -74, -60 },
					{ -52, -31 },
					{ 10, -14 },
					{ 63, -22 },
					{ 89, -50 },
					{ 76, -90 },
					{ 30, -112 },
					{ -37, -97 }
				},

				//POINT cxyTR2[8] =
				{
					{ -49, -58 },
					{ -35, -29 },
					{ 13, -13 },
					{ 64, -21 },
					{ 91, -47 },
					{ 77, -78 },
					{ 33, -95 },
					{ -21, -86 }
				}
			}
		},
			
		// normal
		{
			//effectSpriteType = EFFECTSPRITETYPE_GUN_SR_MALE;
			{
				//POINT cxyTR[8] =
				{
					{ -77, -56 },
					{ -51, -26 },
					{ 15, -10 },
					{ 68, -19 },
					{ 90, -48 },
					{ 75, -90 },
					{ 27, -110 },
					{ -43, -94 }
				},

				//POINT cxyTR2[8] =
				{
					{ -50, -52 },
					{ -33, -23 },
					{ 18, -7 },
					{ 68, -18 },
					{ 92, -45 },
					{ 76, -77 },
					{ 30, -92 },
					{ -24, -81 }
				}
			},
			
			// effectSpriteType = EFFECTSPRITETYPE_GUN_SR_FEMALE;
			{
				//POINT cxyTR[8] =
				{
					{ -77, -60 },
					{ -53, -32 },
					{ 11, -14 },
					{ 64, -22 },
					{ 90, -50 },
					{ 77, -92 },
					{ 31, -113 },
					{ -39, -100 }
				},

				//POINT cxyTR2[8] =
				{
					{ -50, -58 },
					{ -35, -29 },
					{ 14, -13 },
					{ 64, -21 },
					{ 92, -47 },
					{ 78, -79 },
					{ 34, -95 },
					{ -21, -86 }
				}
			}
		}
	};

	// etypeTR[holyShooting][male]
	int etypeTR[2][2] = 
	{
		{ 
			EFFECTSPRITETYPE_BULLET_OF_LIGHT_SR_MALE - MAX_EFFECTSPRITETYPE_ALPHAEFFECT, 
			EFFECTSPRITETYPE_BULLET_OF_LIGHT_SR_FEMALE - MAX_EFFECTSPRITETYPE_ALPHAEFFECT 
		},

		{ 
			EFFECTSPRITETYPE_GUN_SR_MALE - MAX_EFFECTSPRITETYPE_ALPHAEFFECT, 
			EFFECTSPRITETYPE_GUN_SR_FEMALE - MAX_EFFECTSPRITETYPE_ALPHAEFFECT
		}
	};

//	etype = 0;
	for (etype=0; etype<2; etype++)
	{
		for (s=0; s<2; s++)
		{
			DIRECTION_EFFECTFRAME_ARRAY TR;
			TR.Init( 8 );

			effectSpriteType = etypeTR[etype][s];

			for (d=0; d<8; d++)
			{
				TR[d].Init( 3 );	// 3 frame

				// frame이 두 개 밖에 없는 경우...는 1
				int secondFrame = (ScreenEFPK[effectSpriteType][d].GetSize()==2)? 1 : 2;

				sprite = ScreenEFPK[effectSpriteType][d][0].GetSpriteID();
				light = ScreenEFPK[effectSpriteType][d][0].GetLight();

				sprite2 = ScreenEFPK[effectSpriteType][d][secondFrame].GetSpriteID();
				light2 = ScreenEFPK[effectSpriteType][d][secondFrame].GetLight();
				
				for (int f=0; f<TR[d].GetSize()-1; f++)
				{
					TR[d][f].Set( sprite, cxyTR[etype][s][0][d].x, cxyTR[etype][s][0][d].y, light, false );
				}
				
				TR[d][TR[d].GetSize()-1].Set( sprite2, cxyTR[etype][s][1][d].x, cxyTR[etype][s][1][d].y, light2, false );
			}
			
			// 바꿈..
			ScreenEFPK[effectSpriteType] = TR;
		}
	}


	//---------------------------------------------------------
	// AR
	//---------------------------------------------------------
	// cxyAR[holyShooting][male][effectFrame][direction]
	POINT cxyAR[2][2][2][8] =
	{
		// Holy
		{
			//effectSpriteType = EFFECTSPRITETYPE_HOLY_SHOOTING_AR_MALE;
			{
				//POINT cxyAR[8] =
				{
					{ -66, -61 },
					{ -44, -45 },
					{ 4, -33 },
					{ 43, -39 },
					{ 76, -59 },
					{ 49, -87 },
					{ 11, -105 },
					{ -37, -97 }	
				},

				// 희미한 frame
				//POINT cxyAR2[8] =
				{
					{ -56, -58 },
					{ -37, -36 },
					{ 7, -20 },
					{ 51, -32 },
					{ 79, -51 },
					{ 60, -81 },
					{ 19, -99 },
					{ -30, -86 }
				}
			},

			//effectSpriteType = EFFECTSPRITETYPE_HOLY_SHOOTING_AR_FEMALE;
			{
				//POINT cxyAR[8] =
				{
					{ -65, -67 },
					{ -54, -64 },
					{ 0, -36 },
					{ 42, -40 },
					{ 71, -61 },
					{ 51, -89 },
					{ 15, -109 },
					{ -34, -101 }
				},

				// 희미한 frame
				//POINT cxyAR2[8] =
				{			
					{ -54, -64 },
					{ -39, -41 },
					{ 3, -26 },
					{ 47, -34 },
					{ 74, -52 },
					{ 60, -82 },
					{ 24, -104 },
					{ -25, -89 }
				}
			}
		},
		
		// Normal
		{
			//effectSpriteType = EFFECTSPRITETYPE_GUN_AR_MALE;
			{
				//POINT cxyAR[8] =
				{
					{ -68, -67 },
					{ -44, -46 },
					{ 5, -33 },
					{ 43, -40 },
					{ 77, -62 },
					{ 49, -87 },
					{ 10, -105 },
					{ -36, -98 }
				},

				// 희미한 frame
				//POINT cxyAR2[8] =
				{
					{ -55, -59 },
					{ -37, -37 },
					{ 7, -21 },
					{ 51, -32 },
					{ 80, -52 },
					{ 60, -81 },
					{ 19, -99 },
					{ -29, -86 }
				},
			},

			
			//effectSpriteType = EFFECTSPRITETYPE_GUN_AR_FEMALE;
			{
				//POINT cxyAR[8] =
				{
					{ -67, -73 },
					{ -45, -52 },
					{ 1, -36 },
					{ 42, -41 },
					{ 72, -64 },
					{ 51, -89 },
					{ 14, -109 },
					{ -33, -102 }
				},

				// 희미한 frame
				//POINT cxyAR2[8] =
				{
					{ -53, -65 },
					{ -39, -42 },
					{ 3, -27 },
					{ 47, -34 },
					{ 75, -53 },
					{ 60, -82 },
					{ 24, -104 },
					{ -24, -89 }
				}
			}
		}
	};

	// etypeAR[holyShooting][male]
	int etypeAR[2][2] = 
	{
		{ 
			EFFECTSPRITETYPE_BULLET_OF_LIGHT_AR_MALE - MAX_EFFECTSPRITETYPE_ALPHAEFFECT, 
			EFFECTSPRITETYPE_BULLET_OF_LIGHT_AR_FEMALE  - MAX_EFFECTSPRITETYPE_ALPHAEFFECT
		},

		{ 
			EFFECTSPRITETYPE_GUN_AR_MALE - MAX_EFFECTSPRITETYPE_ALPHAEFFECT, 
			EFFECTSPRITETYPE_GUN_AR_FEMALE - MAX_EFFECTSPRITETYPE_ALPHAEFFECT 
		}
	};

//	etype = 0;
	for (etype=0; etype<2; etype++)
	{
		for (s=0; s<2; s++)
		{
			DIRECTION_EFFECTFRAME_ARRAY AR;
			AR.Init( 8 );

			effectSpriteType = etypeAR[etype][s];

			for (d=0; d<8; d++)
			{
				AR[d].Init( 2 );	// 6 frame

				sprite = ScreenEFPK[effectSpriteType][d][0].GetSpriteID();
				light = ScreenEFPK[effectSpriteType][d][0].GetLight();
				
				sprite2 = ScreenEFPK[effectSpriteType][d][1].GetSpriteID();
				light2 = ScreenEFPK[effectSpriteType][d][1].GetLight();
				
				for (int f=0; f<AR[d].GetSize(); f+=2)
				{
					AR[d][f].Set( sprite, cxyAR[etype][s][0][d].x, cxyAR[etype][s][0][d].y, light, false );
					AR[d][f+1].Set( sprite2, cxyAR[etype][s][1][d].x, cxyAR[etype][s][1][d].y, light2, false );
				}
			}

			// 바꿈..
			ScreenEFPK[effectSpriteType] = AR;
		}
	}


	//---------------------------------------------------------
	// SMG
	//---------------------------------------------------------
	// cxySMG[holyShooting][male][effectFrame][direction]
	POINT cxySMG[2][2][2][8] =	
	{
		// Holy
		{
			//effectSpriteType = EFFECTSPRITETYPE_HOLY_SHOOTING_SMG_MALE;
			{
				//POINT cxySMG[8] =
				{
					{ -52, -54 },
					{ -39, -43 },
					{ 1, -29 },
					{ 32, -33 },
					{ 64, -49 },
					{ 41, -71 },
					{ 14, -88 },
					{ -25, -83 }
				},
				
				// 희미한 불꽃 frame
				//POINT cxySMG2[8] =
				{				
					{ -43, -52 },
					{ -31, -33 },
					{ 3, -17 },
					{ 38, -27 },
					{ 66, -40 },
					{ 52, -65 },
					{ 23, -83 },
					{ -16, -73 }
				}
			},
			
			//effectSpriteType = EFFECTSPRITETYPE_HOLY_SHOOTING_SMG_FEMALE;
			{
				//POINT cxySMG[8] =
				{
					{ -50, -59 },
					{ -38, -47 },
					{ -2, -33 },
					{ 30, -38 },
					{ 61, -52 },
					{ 40, -73 },
					{ 15, -91 },
					{ -22, -87 }		
				},
				
				// 희미한 불꽃 frame
				//POINT cxySMG2[8] =
				{
					{ -38, -56 },
					{ -29, -39 },
					{ 2, -25 },
					{ 36, -31 },
					{ 62, -43 },
					{ 49, -66 },
					{ 24, -83 },
					{ -14, -75 }
				}
			}
		},

		// Normal
		{
			// effectSpriteType = EFFECTSPRITETYPE_GUN_SMG_MALE;
			{
				// POINT cxySMG[8] =
				{
					{ -54, -60 },
					{ -39, -44 },
					{ 2, -29 },
					{ 32, -34 },
					{ 65, -52 },
					{ 41, -71 },
					{ 13, -88 },
					{ -24, -84 }
				},
				
				// 희미한 불꽃 frame
				//POINT cxySMG2[8] =
				{
					{ -42, -53 },
					{ -31, -34 },
					{ 3, -18 },
					{ 38, -27 },
					{ 67, -41 },
					{ 52, -65 },
					{ 23, -83 },
					{ -15, -73 }
				}
			},
			
			// effectSpriteType = EFFECTSPRITETYPE_GUN_SMG_FEMALE;
			{
				//POINT cxySMG[8] =
				{
					{ -52, -65 },
					{ -38, -48 },
					{ -1, -33 },
					{ 30, -39 },
					{ 62, -55 },
					{ 40, -73 },
					{ 14, -91 },
					{ -21, -88 }
				},
				
				// 희미한 불꽃 frame
				//POINT cxySMG2[8] =
				{
					{ -37, -57 },
					{ -29, -40 },
					{ 2, -26 },
					{ 36, -31 },
					{ 63, -44 },
					{ 49, -66 },
					{ 24, -83 },
					{ -13, -75 }
				}
			}
		}
	};

	// etypeSMG[holyShooting][male]
	int etypeSMG[2][2] = 
	{
		{ 
			EFFECTSPRITETYPE_BULLET_OF_LIGHT_SMG_MALE - MAX_EFFECTSPRITETYPE_ALPHAEFFECT, 
			EFFECTSPRITETYPE_BULLET_OF_LIGHT_SMG_FEMALE - MAX_EFFECTSPRITETYPE_ALPHAEFFECT 
		},

		{ 
			EFFECTSPRITETYPE_GUN_SMG_MALE - MAX_EFFECTSPRITETYPE_ALPHAEFFECT, 
			EFFECTSPRITETYPE_GUN_SMG_FEMALE - MAX_EFFECTSPRITETYPE_ALPHAEFFECT 
		}
	};

//	etype = 0;
	for (etype=0; etype<2; etype++)
	{
		for (s=0; s<2; s++)
		{
			DIRECTION_EFFECTFRAME_ARRAY SMG;
			SMG.Init( 8 );

			effectSpriteType = etypeSMG[etype][s];

			for (d=0; d<8; d++)
			{
				SMG[d].Init( 2 );	// 10 frame

				sprite = ScreenEFPK[effectSpriteType][d][0].GetSpriteID();
				light = ScreenEFPK[effectSpriteType][d][0].GetLight();

				sprite2 = ScreenEFPK[effectSpriteType][d][1].GetSpriteID();
				light2 = ScreenEFPK[effectSpriteType][d][1].GetLight();
				
				for (int f=0; f<SMG[d].GetSize(); f+=2)
				{
					SMG[d][f].Set( sprite, cxySMG[etype][s][0][d].x, cxySMG[etype][s][0][d].y, light, false );
					SMG[d][f+1].Set( sprite2, cxySMG[etype][s][1][d].x, cxySMG[etype][s][1][d].y, light2, false );
				}
			}

			// 바꿈..
			ScreenEFPK[effectSpriteType] = SMG;
		}
	}

//	int etypeSprit[4] = 
//	{
//		EFFECTSPRITETYPE_SPRIT_GUARD,
//		EFFECTSPRITETYPE_SPRIT_GUARD,
//		EFFECTSPRITETYPE_SPRIT_GUARD,
//		EFFECTSPRITETYPE_SPRIT_GUARD,
//	};
//
//	const int pixelOrbitWidthHalf	= 48*2;
//	const int pixelOrbitHeightHalf	= 24*2;
//	bool back;
//
//	for (etype=0; etype<4; etype++)
//	{
//		DIRECTION_EFFECTFRAME_ARRAY Sprit;
//		Sprit.Init( 8 );
//		
//		effectSpriteType = etypeSprit[etype];
//		
//		const int radOrbitStep			= MathTable::MAX_ANGLE/EFPK[effectSpriteType][0].GetSize();
//
//		for (d=0; d<8; d++)
//		{
//			Sprit[d].Init( EFPK[effectSpriteType][d].GetSize() );	// 10 frame
//			
//			for (int f=0; f<Sprit[d].GetSize(); f++)
//			{
//				int rad = radOrbitStep*f;
//
//				sprite = EFPK[effectSpriteType][d][f].GetSpriteID();
//				light = EFPK[effectSpriteType][d][f].GetLight();
//				back = EFPK[effectSpriteType][d][f].IsBackground();
//			
//				Sprit[d][f].Set( sprite, (MathTable::FCos(rad)*pixelOrbitWidthHalf), (MathTable::FSin(rad)*pixelOrbitHeightHalf), light, back );
//			}
//		}
//		
//		// 바꿈..
//		EFPK[effectSpriteType] = Sprit;
//	}

	std::ofstream efpkSaveFile(g_pFileDef->getProperty("FILE_EFRAME_ALPHAEFFECT").c_str(), std::ios::binary);
	std::ofstream efpkFileIndex(g_pFileDef->getProperty("FILE_EFRAMEINDEX_ALPHAEFFECT").c_str(), std::ios::binary);

	EFPK.SaveToFile( efpkSaveFile, efpkFileIndex );

	efpkSaveFile.close();
	efpkFileIndex.close();


	std::ofstream efpk2SaveFile(g_pFileDef->getProperty("FILE_EFRAME_SCREENEFFECT").c_str(), std::ios::binary);
	std::ofstream efpk2FileIndex(g_pFileDef->getProperty("FILE_EFRAMEINDEX_SCREENEFFECT").c_str(), std::ios::binary);

	ScreenEFPK.SaveToFile( efpk2SaveFile, efpk2FileIndex );

	efpk2SaveFile.close();
	efpk2FileIndex.close();

	
	//---------------------------------------------------------------------
	// 성수, 폭탄.. 날아가는거 좌표 위치 높혀주기..
	//---------------------------------------------------------------------
	// 0 - Flying Bomb
	// 1 - Flying HolyWater
	/*
	if (NormalEFPK[0][0][0].GetCY() < -25)
	{
		const int numFlying = 2;
		int nefFlying[numFlying] =
		{
			0,	// EFFECTSPRITETYPE_FLYING_BOMB,
			1	// EFFECTSPRITETYPE_FLYING_HOLY_WATER
		};

		for (int est=0; est<numFlying; est++)
		{
			DIRECTION_EFFECTFRAME_ARRAY& DEA = NormalEFPK[nefFlying[est]];

			for (int d=0; d<8; d++)
			{
				EFFECTFRAME_ARRAY& EFA = DEA[d];

				for (int f=0; f<EFA.GetSize(); f++)
				{
					CEffectFrame& frame = EFA[f];

					frame.Set( frame.GetSpriteID(), frame.GetCX(), frame.GetCY()-30, frame.GetLight() );
				}
			}
		}
	}

	
	std::ofstream normalEfpkSaveFile(FILE_EFRAME_NORMALEFFECT, ios::binary);
	std::ofstream normalEfpkFileIndex(FILE_EFRAMEINDEX_NORMALEFFECT, ios::binary);

	NormalEFPK.SaveToFile( normalEfpkSaveFile, normalEfpkFileIndex );

	normalEfpkSaveFile.close();
	normalEfpkFileIndex.close();
	*/

	//---------------------------------------------------------------------
	//
	//			Game String Table 정보 생성
	//
	//---------------------------------------------------------------------
	//---------------------------------------------------------------------		
	// GameStringTable 초기화
	//---------------------------------------------------------------------
	InitGameStringTable();

	//---------------------------------------------------------------------
	// Save
	//---------------------------------------------------------------------
	std::ofstream gameStringTable(g_pFileDef->getProperty("FILE_INFO_STRING").c_str(), std::ios::binary);
	g_pGameStringTable->SaveToFile(gameStringTable);
	gameStringTable.close();


	//---------------------------------------------------------------------
	//
	//		도움말
	//
	//---------------------------------------------------------------------
	/*
	MStringArray helpMessage;

	const int numStr = 44;

	const char	strMessage[numStr][80] =
	{
		" ",		//0
		"        다크에덴 베타 테스트 도움말",
		" ",
		" ",
		" [ 키보드 단축키 ]",
		" ",		// 5
		"     [ Ctrl + H ]  도움말",
		"     [ ESC ]  메뉴",
		"     [ Tab ] 아이템창 열고 닫기",			
		"     [ Ctrl + Tab ] 장착창 열고 닫기",
		"     [ Ctrl + ~ ] 벨트 열고 닫기",	// 10
		"     [ Ctrl + Space ] 아이템과 장착창 감추기",	
		"     [ Ctrl + S ] 기술 아이콘 선택",				
		"     [ F1~F8 ]  벨트 아이템 사용",
		"     [ F9~F12 ]  기술 단축기",
		"     [ L-Ctrl ]  같은 종족 선택 가능",
		"     [ L-Alt ]  아이템 줍기, 거래하기",
		"     [ CTRL + C ]  캐릭터 정보창 보기",	// 15
		"     [ Ctrl + M ]  지도 보기",	// 15
		"     [ Ctrl + T ]  게임 시간 보기",
		"     [ Ctrl + Z ]  존 이름, 좌표 보기",
		"     [ Ctrl + V ]  그림자 출력방식 바꾸기",
		"     [ Ctrl + B ]  배경 음악 on/off",
		"     [ Ctrl + E ]  효과음 on/off",
		//"     [ Ctrl + W ]  채팅창 크기 바꾸기",
		"     [ Scroll Lock ]  화면 캡쳐(\\ScreenShot)",	//20	
		" ",
		" ",	// 22
		" [ 마우스 사용 방법 ]",
		" ",
		"     [ L-Button ]  이동, 추적, 공격",
		"     [ R-Button ] 마법, 기술, 아이템 사용",	
		"     [ L-Shift + L-Button ]  강제 공격",	// 27		
		" ",
		" ",
		" [ 게임 진행에 필요한 기능 ]",
		" ",	// 32
		"     = 존에 외치기 : !할말",
		"     = 귓속말 :  /아이디 할말",		//34
		"     = 대화 거부 :  @거부 아이디",		//34
		"     = 대화 허용 :  @허용 아이디",		//34
		"     = 대화 전부 거부 :  @거부",		//34
		"     = 대화 전부 허용 :  @허용",		//34
		"     = 좋지 않은 말 제거하기 :  @바른말",		//34
		"     = 모든 말 다 보기 :  @뭐라고?",		//34
	};

	helpMessage.Init( numStr );

	for (int line=0; line<numStr; line++)
	{
		helpMessage[line] = strMessage[line];
	}


	//---------------------------------------------------------------------
	// Save
	//---------------------------------------------------------------------
	std::ofstream helpTable(FILE_INFO_HELP, ios::binary);
	helpMessage.SaveToFile(helpTable);
	helpTable.close();
	*/
	//---------------------------------------------------------------------
	//
	//         Sound 정보 생성
	//
	//---------------------------------------------------------------------

	if(InitSoundTable() == FALSE)
		return FALSE;
	
	//---------------------------------------------------------------------
	//
	//         Music 정보 생성
	//
	//---------------------------------------------------------------------
	///*
#ifdef SAVE_TO_FILE

	(*g_pMusicTable).Init( MAX_MUSIC );

	// Mid file
	(*g_pMusicTable)[MUSIC_TREASURE].Filename		= "Data\\Music\\Treasure.mid";
	(*g_pMusicTable)[MUSIC_WHISPER].Filename		= "Data\\Music\\Whisper.mid";
	(*g_pMusicTable)[MUSIC_SAY_AGAIN].Filename		= "Data\\Music\\SayAgain.mid";
	(*g_pMusicTable)[MUSIC_WINDMILL].Filename		= "Data\\Music\\Windmill.mid";
	(*g_pMusicTable)[MUSIC_HELL_KNIGHT].Filename	= "Data\\Music\\HellKnight.mid";
	(*g_pMusicTable)[MUSIC_HOLLOWEEN].Filename		= "Data\\Music\\Holloween.mid";
	(*g_pMusicTable)[MUSIC_PAY_BACK].Filename		= "Data\\Music\\PayBack.mid";
	(*g_pMusicTable)[MUSIC_HIDE_AWAY].Filename		= "Data\\Music\\HideAway.mid";
	(*g_pMusicTable)[MUSIC_LIVE_OR_DEAD].Filename	= "Data\\Music\\LiveOrDead.mid";
	(*g_pMusicTable)[MUSIC_LUNATIC].Filename		= "Data\\Music\\Lunatic.mid";
	(*g_pMusicTable)[MUSIC_MARCHING].Filename		= "Data\\Music\\Marching.mid";

	(*g_pMusicTable)[MUSIC_XMAS_JINGLEBELL].Filename = "Data\\Music\\XMAS_JINGLEBELL.mid";
	(*g_pMusicTable)[MUSIC_XMAS_SILENTNIGHT].Filename = "Data\\Music\\XMAS_SILENTNIGHT.mid";
	(*g_pMusicTable)[MUSIC_XMAS_SILVERBELL].Filename = "Data\\Music\\XMAS_SILVERBELL.mid";	

//	(*g_pMusicTable)[MUSIC_HOLYLAND].Filename = "Data\\Music\\Adam_Normal.mid";
//	(*g_pMusicTable)[MUSIC_HOLYLAND_WAR].Filename = "Data\\Music\\Adam_War.mid";
//	(*g_pMusicTable)[MUSIC_OCTAVUS].Filename = "Data\\Music\\Castle_Octavus.mid";
//	(*g_pMusicTable)[MUSIC_SEPTIMUS].Filename = "Data\\Music\\Castle_Septimus.mid";
//	(*g_pMusicTable)[MUSIC_TERTIUS].Filename = "Data\\Music\\Castle_Tertius.mid" ;
//	(*g_pMusicTable)[MUSIC_QUARTUS].Filename = "Data\\Music\\Castle_Quartus.mid";

	(*g_pMusicTable)[MUSIC_HOLYLAND].Filename = "Data\\Music\\Marching.mid";
	(*g_pMusicTable)[MUSIC_HOLYLAND_WAR].Filename = "Data\\Music\\Marching.mid";
	(*g_pMusicTable)[MUSIC_OCTAVUS].Filename = "Data\\Music\\Marching.mid";
	(*g_pMusicTable)[MUSIC_SEPTIMUS].Filename = "Data\\Music\\Marching.mid";
	(*g_pMusicTable)[MUSIC_TERTIUS].Filename = "Data\\Music\\Marching.mid" ;
	(*g_pMusicTable)[MUSIC_QUARTUS].Filename = "Data\\Music\\Marching.mid";

	// Wave file
//	(*g_pMusicTable)[MUSIC_TREASURE].FilenameWav	= "Data\\Music\\Treasure.wav";
//	(*g_pMusicTable)[MUSIC_WHISPER].FilenameWav		= "Data\\Music\\Whisper.wav";
//	(*g_pMusicTable)[MUSIC_SAY_AGAIN].FilenameWav	= "Data\\Music\\SayAgain.wav";
//	(*g_pMusicTable)[MUSIC_WINDMILL].FilenameWav	= "Data\\Music\\Windmill.wav";
//	(*g_pMusicTable)[MUSIC_HELL_KNIGHT].FilenameWav	= "Data\\Music\\HellKnight.wav";
//	(*g_pMusicTable)[MUSIC_HOLLOWEEN].FilenameWav	= "Data\\Music\\Holloween.wav";
//	(*g_pMusicTable)[MUSIC_PAY_BACK].FilenameWav	= "Data\\Music\\PayBack.wav";
//	(*g_pMusicTable)[MUSIC_HIDE_AWAY].FilenameWav	= "Data\\Music\\HideAway.wav";
//	(*g_pMusicTable)[MUSIC_LIVE_OR_DEAD].FilenameWav= "Data\\Music\\LiveOrDead.wav";
//	(*g_pMusicTable)[MUSIC_LUNATIC].FilenameWav		= "Data\\Music\\Lunatic.wav";
//	(*g_pMusicTable)[MUSIC_MARCHING].FilenameWav	= "Data\\Music\\Marching.wav";


	(*g_pMusicTable)[MUSIC_XMAS_JINGLEBELL].FilenameWav	= "Data\\Music\\XMAS_JINGLEBELL.wav";
	(*g_pMusicTable)[MUSIC_XMAS_SILENTNIGHT].FilenameWav= "Data\\Music\\XMAS_SILENTNIGHT.wav";
	(*g_pMusicTable)[MUSIC_XMAS_SILVERBELL].FilenameWav	= "Data\\Music\\XMAS_SILVERBELL.wav";	
	
//	(*g_pMusicTable)[MUSIC_HOLYLAND].FilenameWav = "Data\\Music\\Adam_Normal.wav";
//	(*g_pMusicTable)[MUSIC_HOLYLAND_WAR].FilenameWav = "Data\\Music\\Adam_War.wav";
//	(*g_pMusicTable)[MUSIC_OCTAVUS].FilenameWav = "Data\\Music\\Castle_Octavus.wav";
//	(*g_pMusicTable)[MUSIC_SEPTIMUS].FilenameWav = "Data\\Music\\Castle_Septimus.wav";
//	(*g_pMusicTable)[MUSIC_TERTIUS].FilenameWav = "Data\\Music\\Castle_Tertius.wav";
//	(*g_pMusicTable)[MUSIC_QUARTUS].FilenameWav = "Data\\Music\\Castle_Quartus.wav";


	(*g_pMusicTable)[MUSIC_TREASURE].FilenameWav	= "Data\\Music\\blood.ogg";
	(*g_pMusicTable)[MUSIC_WHISPER].FilenameWav		= "Data\\Music\\chaos.ogg";
	(*g_pMusicTable)[MUSIC_SAY_AGAIN].FilenameWav	= "Data\\Music\\rest.ogg";
	(*g_pMusicTable)[MUSIC_WINDMILL].FilenameWav	= "Data\\Music\\ruin.ogg";
	(*g_pMusicTable)[MUSIC_HELL_KNIGHT].FilenameWav	= "Data\\Music\\underworld.ogg";
	(*g_pMusicTable)[MUSIC_HOLLOWEEN].FilenameWav	= "Data\\Music\\silence_of_battlefield.ogg";
	(*g_pMusicTable)[MUSIC_PAY_BACK].FilenameWav	= "Data\\Music\\blood.ogg";
	(*g_pMusicTable)[MUSIC_HIDE_AWAY].FilenameWav	= "Data\\Music\\dominator_of_darkness.ogg";
	(*g_pMusicTable)[MUSIC_LIVE_OR_DEAD].FilenameWav= "Data\\Music\\oblivion.ogg";
	(*g_pMusicTable)[MUSIC_LUNATIC].FilenameWav		= "Data\\Music\\chaos.ogg";
	(*g_pMusicTable)[MUSIC_MARCHING].FilenameWav	= "Data\\Music\\ruin.ogg";


	(*g_pMusicTable)[MUSIC_HOLYLAND].FilenameWav	= "Data\\Music\\Adam_Normal.ogg";
	(*g_pMusicTable)[MUSIC_HOLYLAND_WAR].FilenameWav = "Data\\Music\\Adam_War.ogg";
	(*g_pMusicTable)[MUSIC_OCTAVUS].FilenameWav		= "Data\\Music\\Castle_Octavus.ogg";
	(*g_pMusicTable)[MUSIC_SEPTIMUS].FilenameWav	= "Data\\Music\\Castle_Septimus.ogg";
	(*g_pMusicTable)[MUSIC_TERTIUS].FilenameWav		= "Data\\Music\\Castle_Tertius.ogg";
	(*g_pMusicTable)[MUSIC_QUARTUS].FilenameWav		= "Data\\Music\\Castle_Quartus.ogg";

	(*g_pMusicTable)[MUSIC_ILLUSIONS_WAY].FilenameWav = "Data\\Music\\BGM_illu.ogg";
	(*g_pMusicTable)[MUSIC_ILLUSIONS_WAY].Filename	= "Data\\Music\\BGM_illu.ogg";
	(*g_pMusicTable)[MUSIC_GDR_LAIR].FilenameWav	= "Data\\Music\\BGM_GDRLair.ogg";
	(*g_pMusicTable)[MUSIC_GDR_LAIR].Filename		= "Data\\Music\\BGM_GDRLair.ogg";

	(*g_pMusicTable)[MUSIC_OVERTURE].FilenameWav	= "Data\\Music\\overture.ogg";
	(*g_pMusicTable)[MUSIC_OVERTURE].Filename		= "Data\\Music\\overture.ogg";

	(*g_pMusicTable)[MUSIC_ADVANCE].FilenameWav		= "Data\\Music\\advance.ogg";
	(*g_pMusicTable)[MUSIC_ADVANCE].Filename		= "Data\\Music\\advance.ogg";
	
	(*g_pMusicTable)[MUSIC_GEHENNA].FilenameWav		= "Data\\Music\\Gehenna.ogg";
	(*g_pMusicTable)[MUSIC_GEHENNA].Filename		= "Data\\Music\\Gehenna.ogg";
	
	(*g_pMusicTable)[MUSIC_ANONCIAD].FilenameWav	= "Data\\Music\\Anonciad.ogg";
	(*g_pMusicTable)[MUSIC_ANONCIAD].Filename		= "Data\\Music\\Anonciad.ogg";
	
	(*g_pMusicTable)[MUSIC_SCHWARZWALD].FilenameWav	= "Data\\Music\\Schwarzwald.ogg";
	(*g_pMusicTable)[MUSIC_SCHWARZWALD].Filename	= "Data\\Music\\Schwarzwald.ogg";

	(*g_pMusicTable)[MUSIC_CONCORDIA].FilenameWav	= "Data\\Music\\Concordia.ogg";
	(*g_pMusicTable)[MUSIC_CONCORDIA].Filename		= "Data\\Music\\Concordia.ogg";

	//------------------------------------------------
	// Save
	//------------------------------------------------
	std::ofstream musicTable(g_pFileDef->getProperty("FILE_INFO_MUSIC").c_str(), std::ios::binary);
	(*g_pMusicTable).SaveToFile(musicTable);
	musicTable.close();
#endif
	//*/

	//------------------------------------------------
	// Load
	//------------------------------------------------
	ivfstream musicTable2;//(FILE_INFO_MUSIC, ios::binary);
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_INFO_MUSIC").c_str(), musicTable2))
		return FALSE;
	(*g_pMusicTable).LoadFromFile(musicTable2);
	musicTable2.close();

	//------------------------------------------------
	// music file 체크
	//------------------------------------------------
	for (int i=0; i<g_pMusicTable->GetSize(); i++)
	{
		if (!FileCheck( (*g_pMusicTable)[i].Filename.GetString() ))
		{
			return FALSE;
		}

		if (!FileCheck( (*g_pMusicTable)[i].FilenameWav.GetString() ))
		{
			return FALSE;
		}
	}

	if(InitZoneInfo() == FALSE)
		return FALSE;
	//---------------------------------------------------------------------
	//
	//    RankBonusTable에 대한 정보 설정
	//
	//---------------------------------------------------------------------

	ivfstream serverRankBonusFile;//(FILE_INFO_SERVER_ITEM, ios::binary);
	if (!FileOpenBinary(FILE_INFO_SERVER_RANK_BONUS, serverRankBonusFile))
		return false;

	ServerRankBonusTable serverRankBonusTable;

	serverRankBonusTable.LoadFromFile( serverRankBonusFile );

	serverRankBonusFile.close();


	//------------------------------------------------
	// client의 item table에 적용시킨다.
	//------------------------------------------------
	int result = serverRankBonusTable.AffectToClient( (*g_pRankBonusTable) );

	if (result!=-2)
	{
		char str[80];

		if (result==-2)
		{		
			AfxMessageBox("ServerRankBonusInfo와 ClientRankBonusTable의 class 수가 다릅니다.");

			return false;
		}

		sprintf(str, "RankBonusError");

		AfxMessageBox(str);

		return false;

	}

	//------------------------------------------------
	// Save
	//------------------------------------------------
#ifdef SAVE_TO_FILE
	std::ofstream rankTable(g_pFileDef->getProperty("FILE_INFO_RANK_BONUS").c_str(), std::ios::binary);
	(*g_pRankBonusTable).SaveToFile(rankTable);
	rankTable.close();
#endif

	//---------------------------------------------------------------------
	//
	//    ItemTable에 대한 정보 설정
	//
	//---------------------------------------------------------------------

	ivfstream serverItemFile;//(FILE_INFO_SERVER_ITEM, ios::binary);
	if (!FileOpenBinary(FILE_INFO_SERVER_ITEM, serverItemFile))
		return false;

	SERVER_ITEMCLASS_TABLE	ServerItemTable;

	ServerItemTable.LoadFromFile( serverItemFile );

	serverItemFile.close();


	//------------------------------------------------
	// client의 item table에 적용시킨다.
	//------------------------------------------------
	int rankResult = ServerItemTable.AffectToItemTable( (*g_pItemTable) );

	if (rankResult!=-1)
	{
		char str[128];

		if (rankResult==-2)
		{		
			sprintf(str, "ServerItemInfo(%d)와 ClientItemTable(%d)의 class 수가 다릅니다.", ServerItemTable.GetSize(), g_pItemTable->GetSize());
			AfxMessageBox(str);

			return false;
		}

		sprintf(str, "%d번. %s ItemClass의 Type개수가 다릅니다.(server:%d, client:%d)", rankResult, ITEM_SHOW_NAME[rankResult], ServerItemTable[rankResult].GetSize(), (*g_pItemTable)[rankResult].GetSize());

		AfxMessageBox(str);

		return false;

	}

	//------------------------------------------------
	// Save
	//------------------------------------------------
#ifdef SAVE_TO_FILE
	std::ofstream itemTable(g_pFileDef->getProperty("FILE_INFO_ITEM").c_str(), std::ios::binary);
	(*g_pItemTable).SaveToFile(itemTable);
	itemTable.close();
#endif

#ifdef SAVE_TO_CSV_FILE
	std::ofstream itemTableCSV("ItemInfo.csv", std::ios::out);
	(*g_pItemTable).SaveToCSVFile(itemTableCSV);
	itemTable.close();
#endif
	
	//------------------------------------------------
	// Load
	//------------------------------------------------
	ivfstream itemTable2;//(FILE_INFO_ITEM, ios::binary);
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_INFO_ITEM").c_str(), itemTable2))
		return FALSE;
	(*g_pItemTable).LoadFromFile(itemTable2);
	itemTable2.close();

	// 
	// item size 출력
	/*
	std::ofstream itemfile("itemSize.txt");
	for (int it=0; it<(*g_pItemTable).GetSize(); it++)
	{
		itemfile << "class = " << it << endl;
		itemfile << "----------------------------------------" << endl;
		for (int t=0; t<(*g_pItemTable)[it].GetSize(); t++)
		{
			itemfile << "[" << t << "] "
				<< (*g_pItemTable)[it][t].HName.GetString() << " = (" 
				<< (int)(*g_pItemTable)[it][t].GridWidth
				<< ", " << (int)(*g_pItemTable)[it][t].GridHeight << ")" << endl; 
				
				
		}
		itemfile << "----------------------------------------" << endl;
		itemfile << endl;
	}
	itemfile.close();
	*/

	//---------------------------------------------------------------------
	//
	//	ItemOptionTable
	//
	//---------------------------------------------------------------------
	/*
#ifdef SAVE_TO_FILE
	(*g_pItemOptionTable).Init( 2 );
	(*g_pItemOptionTable)[0].Part = 8;
	(*g_pItemOptionTable)[0].Name = "Lizard";
	(*g_pItemOptionTable)[0].PlusPoint = 1;
	(*g_pItemOptionTable)[0].PlusRequireAbility = 1;
	(*g_pItemOptionTable)[0].Worth = 5000;
	(*g_pItemOptionTable)[0].ColorSet = 30;
	
	(*g_pItemOptionTable)[1].Part = 8;
	(*g_pItemOptionTable)[1].Name = "Tiger";
	(*g_pItemOptionTable)[1].PlusPoint = 2;
	(*g_pItemOptionTable)[1].PlusRequireAbility = 2;
	(*g_pItemOptionTable)[1].Worth = 10000;
	(*g_pItemOptionTable)[1].ColorSet = 32;

	std::ofstream itemOptionTable(FILE_INFO_ITEMOPTION, ios::binary);
	(*g_pItemOptionTable).SaveToFile( itemOptionTable );
	itemOptionTable.close();
#endif
	*/

//	std::ifstream itemOptionTable2(FILE_INFO_ITEMOPTION, ios::binary);
//	(*g_pItemOptionTable).LoadFromFile( itemOptionTable2 );
//	itemOptionTable2.close();
//
//	// 0을 추가한다.
//	///*
//	// 0번 option이 없는 경우는 추가한다.
//	if ((*g_pItemOptionTable)[0].Name != "NONE")
//	{
//		ITEMOPTION_TABLE ItemOptionTable;
//		ItemOptionTable.Init( (*g_pItemOptionTable).GetSize()+1 );
//
//		ItemOptionTable[0].Part = 0;
//		ItemOptionTable[0].Name = "NONE";
//		ItemOptionTable[0].EName = "NONE";
//		ItemOptionTable[0].PlusPoint = 0;
//		//ItemOptionTable[0].PlusRequireAbility = 0;
//		ItemOptionTable[0].PriceMultiplier = 0;
//		ItemOptionTable[0].RequireSTR = 0;
//		ItemOptionTable[0].RequireDEX = 0;
//		ItemOptionTable[0].RequireINT = 0;
//		ItemOptionTable[0].RequireSUM = 0;
//		ItemOptionTable[0].RequireLevel = 0;			
//		ItemOptionTable[0].ColorSet = 388;//368;
//		ItemOptionTable[0].UpgradeOptionType = 0;
//
//		for (int o=0; o<(*g_pItemOptionTable).GetSize(); o++)
//		{
//			ItemOptionTable[o+1] = (*g_pItemOptionTable)[o];
//		}
//
//		std::ofstream itemOptionTable(FILE_INFO_ITEMOPTION, ios::binary);
//		ItemOptionTable.SaveToFile( itemOptionTable );
//		itemOptionTable.close();
//	}
//	//*/

	//---------------------------------------------------------------------
	//
	//    InteractionObjectTable에 대한 정보 설정
	//
	//---------------------------------------------------------------------
	/*
#ifdef SAVE_TO_FILE
	g_pInteractionObjectTable->Init( 2 );

	g_InteractionObjectTable[0].Type	= MInteractionObject::TYPE_DOOR;
	g_InteractionObjectTable[0].FrameID = 0;
	g_InteractionObjectTable[0].SoundID = 10;

	g_InteractionObjectTable[1].Type	= MInteractionObject::TYPE_TRAP;
	g_InteractionObjectTable[1].FrameID = 1;
	g_InteractionObjectTable[1].SoundID = 11;
	
	//------------------------------------------------
	// Save
	//------------------------------------------------
	std::ofstream interactionObjectTable(FILE_INFO_INTERACTIONOBJECT, ios::binary);
	g_pInteractionObjectTable->SaveToFile(interactionObjectTable);
	interactionObjectTable.close();
#endif
	*/

	//------------------------------------------------
	// Load
	//------------------------------------------------
	ivfstream interactionObjectTable2;//(FILE_INFO_INTERACTIONOBJECT, ios::binary);
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_INFO_INTERACTIONOBJECT").c_str(), interactionObjectTable2))
		return FALSE;
	g_pInteractionObjectTable->LoadFromFile(interactionObjectTable2);
	interactionObjectTable2.close();

	//---------------------------------------------------------------------
	//
	//    AddonSpriteTable에 대한 정보 설정
	//
	//---------------------------------------------------------------------	
#ifdef SAVE_TO_FILE

	// 남자 Slayer
	ivfstream addonManIndexFile(g_pFileDef->getProperty("FILE_ISPRITEINDEX_ADDON_MAN").c_str(), std::ios::binary);
	ivfstream addonManShadowIndexFile(g_pFileDef->getProperty("FILE_SSPRITEINDEX_ADDON_MAN").c_str(), std::ios::binary);
	ivfstream addonManMmiFile("Data\\AddonManAction.mmi", std::ios::binary);
	ivfstream addonManMmiFile2("Data\\AddonManActionShadow.mmi", std::ios::binary);
	CFileIndexTable	addonManIndexTable;
	CFileIndexTable	addonManIndexTableShadow;
	MMinMaxInfoTable	addonManMmiTable;
	MMinMaxInfoTable	addonManMmiTable2;	// 그림자 체크용

	// Creature IndexSprite IndexFile
	addonManIndexTable.LoadFromFile(addonManIndexFile);

	// Creature ShadowSprite IndexFile
	addonManIndexTableShadow.LoadFromFile(addonManShadowIndexFile);

	// Creature IndexSprite Min/Max Info
	addonManMmiTable.LoadFromFile(addonManMmiFile);
	addonManMmiTable2.LoadFromFile(addonManMmiFile2);

	addonManIndexFile.close();
	addonManShadowIndexFile.close();
	addonManMmiFile.close();
	addonManMmiFile2.close();

	if (addonManMmiTable.GetSize()!=addonManMmiTable2.GetSize())
	{
		InitFail("Wrong AddonMMI Table Size: %d != %d", addonManMmiTable.GetSize(), addonManMmiTable2.GetSize());

		return FALSE;
	}

	for (int m=0; m<addonManMmiTable.GetSize(); m++)
	{
		if (addonManMmiTable[m]!=addonManMmiTable2[m])
		{
			//InitFail("Wrong MMI Size: [%d] (%d ~ %d) != (%d ~ %d)", m, mmiTable[m].Min, mmiTable[m].Max, mmiTable2[m].Min, mmiTable2[m].Max);

			//return FALSE;
		}
	}


	// 여자 Slayer
	ivfstream addonWomanIndexFile(g_pFileDef->getProperty("FILE_ISPRITEINDEX_ADDON_WOMAN").c_str(), std::ios::binary);
	ivfstream addonWomanShadowIndexFile(g_pFileDef->getProperty("FILE_SSPRITEINDEX_ADDON_WOMAN").c_str(), std::ios::binary);
	ivfstream addonWomanMmiFile("Data\\AddonWomanAction.mmi", std::ios::binary);
	ivfstream addonWomanMmiFile2("Data\\AddonWomanActionShadow.mmi", std::ios::binary);
	CFileIndexTable	addonWomanIndexTable;
	CFileIndexTable	addonWomanIndexTableShadow;
	MMinMaxInfoTable	addonWomanMmiTable;
	MMinMaxInfoTable	addonWomanMmiTable2;	// 그림자 체크용

	// Creature IndexSprite IndexFile
	addonWomanIndexTable.LoadFromFile(addonWomanIndexFile);

	// Creature ShadowSprite IndexFile
	addonWomanIndexTableShadow.LoadFromFile(addonWomanShadowIndexFile);

	// Creature IndexSprite Min/Max Info
	addonWomanMmiTable.LoadFromFile(addonWomanMmiFile);
	addonWomanMmiTable2.LoadFromFile(addonWomanMmiFile2);

	addonWomanIndexFile.close();
	addonWomanShadowIndexFile.close();
	addonWomanMmiFile.close();
	addonWomanMmiFile2.close();

	if (addonWomanMmiTable.GetSize()!=addonWomanMmiTable2.GetSize())
	{
		InitFail("Wrong AddonMMI Table Size: %d != %d", addonWomanMmiTable.GetSize(), addonWomanMmiTable2.GetSize());

		return FALSE;
	}

	for (m=0; m<addonWomanMmiTable.GetSize(); m++)
	{
		if (addonWomanMmiTable[m]!=addonWomanMmiTable2[m])
		{
			//InitFail("Wrong MMI Size: [%d] (%d ~ %d) != (%d ~ %d)", m, mmiTable[m].Min, mmiTable[m].Max, mmiTable2[m].Min, mmiTable2[m].Max);

			//return FALSE;
		}
	}


	int maxAddonSprites = MAX_ADDONID_SLAYER * ACTION_MAX_SLAYER;

//	g_pAddonSpriteTable->Init( maxAddonSprites );
//
//	for (int addonIndex=0; addonIndex<MAX_ADDONID_SLAYER; addonIndex++)
//	{
//		for (int a=0; a<ACTION_MAX_SLAYER; a++)
//		{
//			int i = addonIndex*ACTION_MAX_SLAYER + a;
//
//			(*g_pAddonSpriteTable)[i].FrameID				= addonIndex;
//			(*g_pAddonSpriteTable)[i].FirstSpriteID			= addonMmiTable[i].Min;
//			(*g_pAddonSpriteTable)[i].LastSpriteID			= addonMmiTable[i].Max;
//			(*g_pAddonSpriteTable)[i].FirstShadowSpriteID	= addonMmiTable2[i].Min;
//			(*g_pAddonSpriteTable)[i].LastShadowSpriteID	= addonMmiTable2[i].Max;
//			(*g_pAddonSpriteTable)[i].SpriteFilePosition	= addonIndexTable[(*g_pAddonSpriteTable)[i].FirstSpriteID];
//
//			CREATURESPRITETABLE_INFO &cinfo = (*g_pAddonSpriteTable)[i];
//			int fspID = cinfo.FirstShadowSpriteID;
//			(*g_pAddonSpriteTable)[i].SpriteShadowFilePosition	= addonIndexTableShadow[fspID];
//		}
//	}
//

	//------------------------------------------------
	// Save
	//------------------------------------------------
//	std::ofstream addonSpriteTable(g_pFileDef->getProperty("FILE_INFO_ADDONSPRITE").c_str(), ios::binary);
//	g_pAddonSpriteTable->SaveToFile(addonSpriteTable);
//	addonSpriteTable.close();
#endif

	//------------------------------------------------
	// Load
	//------------------------------------------------
//	std::ifstream addonSpriteTable2;//(FILE_INFO_CREATURE, ios::binary);
//	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_INFO_ADDONSPRITE").c_str(), addonSpriteTable2))
//		return FALSE;
//	g_pAddonSpriteTable->LoadFromFile(addonSpriteTable2);
//	addonSpriteTable2.close();
//

	if( InitCreatureSpriteTable() != TRUE )
	{
		AfxMessageBox("InitCreatureSpriteTable Error");
		return FALSE;	
	}

	if( InitCreatureTable() != TRUE )
	{
		AfxMessageBox("InitCreatureTable Error");
		return FALSE;
	}

	//---------------------------------------------------------------------
	//
	//		CreatureSpriteTypeMapper
	//
	//---------------------------------------------------------------------
#ifdef SAVE_TO_FILE
	
	int numSpriteTypes = g_pCreatureSpriteTable->GetSize();

	g_pCreatureSpriteTypeMapper->Init( numSpriteTypes );

	for (int cs=0; cs<g_pCreatureTable->GetSize(); cs++)
	{
		if((*g_pCreatureTable)[cs].SpriteTypes.GetSize()==0)
			continue;
		int spriteType = (*g_pCreatureTable)[cs].SpriteTypes[0];

		if (spriteType < numSpriteTypes)
		{
			g_pCreatureSpriteTypeMapper->AddCreatureType( spriteType, cs );
		}

		

	}

	//------------------------------------------------
	// Save
	//------------------------------------------------
	std::ofstream CreatureSpriteTypeMapper(g_pFileDef->getProperty("FILE_INFO_CREATURESPRITE_MAPPER").c_str(), std::ios::binary);
	g_pCreatureSpriteTypeMapper->SaveToFile(CreatureSpriteTypeMapper);
	CreatureSpriteTypeMapper.close();
#endif	

	//------------------------------------------------
	// Load
	//------------------------------------------------
	ivfstream CreatureSpriteTypeMapper2;//(FILE_INFO_CREATURE, ios::binary);
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_INFO_CREATURESPRITE_MAPPER").c_str(), CreatureSpriteTypeMapper2))
		return FALSE;
	g_pCreatureSpriteTypeMapper->LoadFromFile(CreatureSpriteTypeMapper2);
	CreatureSpriteTypeMapper2.close();


	//---------------------------------------------------------------------
	//
	//		ShopTemplateTable 정보 설정
	//
	//---------------------------------------------------------------------
#ifdef SAVE_TO_FILE
	/*	
	(*g_pShopTemplateTable).Init( 1 );	

	MShopTemplate* pShopTemplate;

	//------------------------------------------------------
	// 1
	//------------------------------------------------------
	pShopTemplate = new MShopTemplate;
	pShopTemplate->

	(*g_pShopTemplateTable)->AddData( 2, pShopTemplateTableInfo );		// smith의 ShopTemplateTable ID는 2




	//------------------------------------------------
	// Save
	//------------------------------------------------
	std::ofstream ShopTemplateTable(FILE_INFO_SHOPTEMPLATE, ios::binary);
	(*g_pShopTemplateTable).SaveToFile(ShopTemplateTable);
	ShopTemplateTable.close();
	*/
#endif

	//------------------------------------------------
	// Load
	//------------------------------------------------
	ivfstream ShopTemplateTable2;//(FILE_INFO_SHOPTEMPLATE, ios::binary);
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_INFO_SHOPTEMPLATE").c_str(), ShopTemplateTable2))
		return FALSE;
	(*g_pShopTemplateTable).LoadFromFile(ShopTemplateTable2);
	ShopTemplateTable2.close();


	//---------------------------------------------------------------------
	//
	//    NPC에 대한 정보 설정
	//
	//---------------------------------------------------------------------	
#ifdef SAVE_TO_FILE
	
	//(*g_pNPCTable).Release();	// 안해줘도 될건데.. 

	/*
	NPC_INFO* pNPCInfo;

	//------------------------------------------------------
	// Smith
	//------------------------------------------------------
	pNPCInfo = new NPC_INFO;
	pNPCInfo->ListShopTemplateID.push_back( 1 );
	pNPCInfo->ListShopTemplateID.push_back( 2 );
	pNPCInfo->ListShopTemplateID.push_back( 3 );

	(*g_pNPCTable).AddData( 2, pNPCInfo );		// smith의 NPC ID는 2

	//------------------------------------------------------
	// SpeedMania
	//------------------------------------------------------
	pNPCInfo = new NPC_INFO;
	pNPCInfo->ListShopTemplateID.push_back( 10 );	

	(*g_pNPCTable).AddData( 4, pNPCInfo );		// SpeedMania의 NPC ID는 4
	*/

	//------------------------------------------------
	// Save
	//------------------------------------------------
	//std::ofstream NPCTable(FILE_INFO_NPC, ios::binary);
	//(*g_pNPCTable).SaveToFile(NPCTable);
	//NPCTable.close();
#endif


	
	//------------------------------------------------
	// Addon FPK
	//------------------------------------------------
	ivfstream AddonManFile2;//(FILE_CFRAME_ADDON_MALE, ios::binary);
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_CFRAME_ADDON_MAN").c_str(), AddonManFile2))
		return false;

	CCreatureFramePack		AddonManFPK;
	AddonManFPK.LoadFromFile(AddonManFile2);
	AddonManFile2.close();

	ivfstream AddonWomanFile2;//(FILE_CFRAME_ADDON_MALE, ios::binary);
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_CFRAME_ADDON_WOMAN").c_str(), AddonWomanFile2))
		return false;

	CCreatureFramePack		AddonWomanFPK;
	AddonWomanFPK.LoadFromFile(AddonWomanFile2);
	AddonWomanFile2.close();

	//------------------------------------------------
	// Creature FPK
	//------------------------------------------------
	CCreatureFramePack		CreatureFPK;

	ivfstream file;//(FILE_CFRAME_CREATURE, ios::binary);
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_CFRAME_CREATURE").c_str(), file))
		return false;
	CreatureFPK.LoadFromFile(file);
	file.close();
	
	//-----------------------------------------------
	// Ousters FPK
	//-----------------------------------------------

	CCreatureFramePack		OustersFPK;
	ivfstream	OustersFPKFile;
	
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_CFRAME_OUSTERS").c_str(), OustersFPKFile) )
		return false;
	OustersFPK.LoadFromFile( OustersFPKFile );
	OustersFPKFile.close();
	
	//---------------------------------------------------------------------
	//
	//      EffectStatusTable 정보 생성
	//
	//---------------------------------------------------------------------
	///*

	if(InitEffectStatusTable()==FALSE)
		return FALSE;

	InitActionInfoTable(AddonManFPK, AddonWomanFPK, CreatureFPK, OustersFPK, FrameSize);


	//*/

		//---------------------------------------------------------------------
	//
	//         SkillManager 초기화
	//
	//---------------------------------------------------------------------
	/*
#ifdef SAVE_TO_FILE
	g_SkillManager.Init( MAX_SKILLDOMAIN );

	//---------------------------------------------------------------------
	// 기본 기술로부터 skill tree를 초기화한다.
	//---------------------------------------------------------------------
	g_SkillManager[SKILLDOMAIN_BLADE].AddSkill( SKILL_SINGLE_BLOW );
	g_SkillManager[SKILLDOMAIN_SWORD].AddSkill( SKILL_DOUBLE_IMPACT );
	g_SkillManager[SKILLDOMAIN_GUN].AddSkill( SKILL_SNIPPING );
	g_SkillManager[SKILLDOMAIN_ENCHANT].AddSkill( MAGIC_CREATE_HOLY_WATER );
	g_SkillManager[SKILLDOMAIN_HEAL].AddSkill( MAGIC_CURE_POISON );
	//g_SkillManager[SKILLDOMAIN_GUILD]
	g_SkillManager[SKILLDOMAIN_VAMPIRE].AddSkill( MAGIC_HIDE );	
	
	//------------------------------------------------
	// Save
	//------------------------------------------------
	std::ofstream SkillManager(FILE_INFO_SKILLMANAGER, ios::binary);
	g_SkillManager.SaveToFile(SkillManager);
	SkillManager.close();
#endif
	*/

	//------------------------------------------------
	// Load
	//------------------------------------------------
	/*
	std::ifstream SkillManager2;//(FILE_INFO_SKILLMANAGER, ios::binary);
	if (!FileOpenBinary(FILE_INFO_SKILLMANAGER, SkillManager2))
		return FALSE;
	g_SkillManager.LoadFromFile(SkillManager2);
	SkillManager2.close();
	*/

	//---------------------------------------------------------------------
	//
	//    SkillInfoTable에 대한 정보 설정
	//
	//---------------------------------------------------------------------
	if (g_pSkillInfoTable==NULL)
	{
		g_pSkillInfoTable = new MSkillInfoTable;
	}

	ivfstream serverSkillTable2;//(FILE_INFO_skill, ios::binary);
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_INFO_SKILL_INFO").c_str(), serverSkillTable2))
		return FALSE;
	g_pSkillInfoTable->LoadFromFileServerSkillInfo(serverSkillTable2);
	serverSkillTable2.close();
	

	//------------------------------------------------
	// Save
	//------------------------------------------------
#ifdef SAVE_TO_FILE
	std::ofstream skillTable(g_pFileDef->getProperty("FILE_INFO_SKILL").c_str(), std::ios::binary);
	g_pSkillInfoTable->SaveToFile(skillTable);
	skillTable.close();
#endif

	//------------------------------------------------
	// Load
	//------------------------------------------------
	ivfstream skillTable2;//(FILE_INFO_skill, ios::binary);
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_INFO_SKILL").c_str(), skillTable2))
		return FALSE;
	g_pSkillInfoTable->LoadFromFile(skillTable2);
	skillTable2.close();
#if __CONTENTS(__GPS_ADD)	//gps.inf 파일 저장
	if (g_pGpsInfoTable==NULL)
	{
		g_pGpsInfoTable = new MGPS_INFO;
	}
#ifdef SAVE_TO_FILE
	std::ofstream gpsTable1(g_pFileDef->getProperty("FILE_INFO_GPS").c_str(), std::ios::binary);
	g_pGpsInfoTable->SaveToFile(gpsTable1);
	gpsTable1.close();
#endif

	ivfstream gpsTable2;//(FILE_INFO_skill, ios::binary);
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_INFO_GPS").c_str(), gpsTable2))
		return FALSE;
	g_pGpsInfoTable->LoadFromFile(gpsTable2);
	gpsTable2.close();
#endif //__GPS_ADD
/*
	if (g_pSkillManager==NULL)
	{
		g_pSkillManager = new MSkillManager;

		g_pSkillManager->Init();

		MSkillDomain& vampire = (*g_pSkillManager)[SKILLDOMAIN_VAMPIRE];

		const MSkillDomain::SKILL_STEP_LIST* skillStep 
					= vampire.GetSkillStepList(SKILL_STEP_VAMPIRE_CURSE);

		MSkillDomain::SKILL_STEP_LIST::const_iterator iStep = skillStep->begin();

		while (iStep != skillStep->end())
		{
			ACTIONINFO ai = *iStep;

			iStep++;
		}
	}
*/

	//-----------------------------------
	// Load From File
	//-----------------------------------
	ivfstream actionInfoFile2;//(FILE_INFO_ACTION, ios::binary);
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_INFO_ACTION").c_str(), actionInfoFile2))
		return FALSE;
	(*g_pActionInfoTable).LoadFromFile(actionInfoFile2);
	actionInfoFile2.close();

	
	//---------------------------------------------------------------------
	//
	//						LevelName Table
	//
	//---------------------------------------------------------------------
	int levelNameNum = MAX_SKILLDOMAIN * 20;
	
	g_pLevelNameTable->Init( levelNameNum+1 );	// 0번은 NULL이다.

	char strTemp[20];
	for (i=1; i<=levelNameNum; i++)
	{		
		sprintf(strTemp, "LevelName%d", i);
		(*g_pLevelNameTable)[i] = strTemp;		
	}

	//-----------------------------------
	// Save To File
	//-----------------------------------
	std::ofstream LevelNameInfoFile(g_pFileDef->getProperty("FILE_INFO_LEVEL_NAME").c_str(), std::ios::binary);	
	g_pLevelNameTable->SaveToFile(LevelNameInfoFile);
	LevelNameInfoFile.close();



	//---------------------------------------------------------------------
	//
	// Server를 위한 정보 file 생성
	//
	//---------------------------------------------------------------------
	//---------------------------------------------------------------------
	// Creature 정보
	//---------------------------------------------------------------------
	std::ofstream cfile("Creature.txt");
	cfile << "[ ID ]  Name  (spriteType) " << std::endl << std::endl;
	for (int ct=0; ct<g_pCreatureTable->GetSize(); ct++)
	{
		if((*g_pCreatureTable)[ct].SpriteTypes.GetSize()==0)
			continue;
		int spriteType = (*g_pCreatureTable)[ct].SpriteTypes[0];

		cfile << "[ " << ct << " ]  "
				<< (*g_pCreatureTable)[ct].Name.GetString()
				<< " ( " << spriteType << " ) ";
		
		int frameID = (*g_pCreatureSpriteTable)[spriteType].FrameID;
		if (frameID < CreatureFPK.GetSize())
		{
			if (CreatureFPK[frameID][0][1].GetSize()==0)
			{
				if (CreatureFPK[frameID][0][3].GetSize()!=0)
				{
					cfile << ", Dir = 3" << std::endl;
				}
				else if (CreatureFPK[frameID][0][2].GetSize()!=0)
				{
					cfile << ", Dir = 2" << std::endl;
				}
			}
			else if (CreatureFPK[frameID][0][3].GetSize()==0)
			{
				if (CreatureFPK[frameID][0][2].GetSize()!=0)
				{
					cfile << ", Dir = 2" << std::endl;
				}
				else
				{
					cfile << ", Dir = 1" << std::endl;
				}

			}
			else
			{
				cfile << std::endl;
			}
		}
		else
		{
			cfile << std::endl;
		}
	}

	for (ct=0; ct<g_pCreatureTable->GetSize(); ct++)
	{
		if((*g_pCreatureTable)[ct].SpriteTypes.GetSize()==0)
			continue;
		int spriteType = (*g_pCreatureTable)[ct].SpriteTypes[0];
		int frameID = (*g_pCreatureSpriteTable)[spriteType].FrameID;
		BYTE player = (*g_pCreatureSpriteTable)[spriteType].IsPlayerOnlySprite();

		const char* name = (*g_pCreatureTable)[ct].Name.GetString();

		cfile << "(" << ct << ", " << spriteType << ", " << name << ")";
		
		if(!player)
		{
			if (!(*g_pCreatureTable)[ct].IsNPC() 
				&& frameID < CreatureFPK.GetSize())
			{
				int actionSize = CreatureFPK[frameID].GetSize();
				
				if (actionSize > ACTION_MOVE)
				{
					int moveFrame = CreatureFPK[frameID][ACTION_MOVE][0].GetSize();
					cfile << "  move(" << (moveFrame*1000 / 16.0f) << "), ";
				}

				if (actionSize > ACTION_ATTACK)
				{
					int attackFrame = CreatureFPK[frameID][ACTION_ATTACK][0].GetSize();
					cfile << "attack(" << (attackFrame*1000 / 16.0f) << "), ";
				}

				if (actionSize > ACTION_MAGIC)
				{
					int magicFrame = CreatureFPK[frameID][ACTION_MAGIC][0].GetSize();
					cfile << "magic(" << (magicFrame*1000 / 16.0f) << ") ";
				}			 
			}
		}
		else
		{
			cfile << " is Player Only";
		}

		cfile << std::endl;				
	}

	cfile.close();


	//------------------------------------------------------------------
	// Slayer action 속도
	//------------------------------------------------------------------
	int SlayerActionSpeed[ACTION_MAX_SLAYER][3] =
	{
		{ ACTION_STAND, ACTION_STAND, ACTION_STAND },
		{ ACTION_MOVE, ACTION_MOVE, ACTION_MOVE },
		{ ACTION_ATTACK, ACTION_ATTACK, ACTION_ATTACK },
		{ ACTION_MAGIC, ACTION_MAGIC, ACTION_MAGIC },
		{ ACTION_DAMAGED, ACTION_DAMAGED, ACTION_DAMAGED },
		{ ACTION_DRAINED, ACTION_DRAINED, ACTION_DRAINED },
		{ ACTION_DIE, ACTION_DIE, ACTION_DIE },

		{ ACTION_SLAYER_GUN_SR_SLOW, ACTION_SLAYER_GUN_SR, ACTION_SLAYER_GUN_SR_FAST },
		{ ACTION_SLAYER_GUN_AR_SLOW, ACTION_SLAYER_GUN_AR, ACTION_SLAYER_GUN_AR_FAST },
		{ ACTION_SLAYER_GUN_SG_SLOW, ACTION_SLAYER_GUN_SG, ACTION_SLAYER_GUN_SG_FAST },
		{ ACTION_SLAYER_GUN_SMG_SLOW, ACTION_SLAYER_GUN_SMG, ACTION_SLAYER_GUN_SMG_FAST },

		{ ACTION_SLAYER_SWORD_SLOW, ACTION_SLAYER_SWORD, ACTION_SLAYER_SWORD_FAST },
		{ ACTION_SLAYER_BLADE_SLOW, ACTION_SLAYER_BLADE, ACTION_SLAYER_BLADE_FAST },
		{ ACTION_SLAYER_SWORD_2_SLOW, ACTION_SLAYER_SWORD_2, ACTION_SLAYER_SWORD_2_FAST },
		{ ACTION_SLAYER_BLADE_2_SLOW, ACTION_SLAYER_BLADE_2, ACTION_SLAYER_BLADE_2_FAST },

//		{ ACTION_SLAYER_THROW_WEAPON, ACTION_SLAYER_THROW_WEAPON, ACTION_SLAYER_THROW_WEAPON },
//		{ ACTION_SLAYER_THROW_POTION, ACTION_SLAYER_THROW_POTION, ACTION_SLAYER_THROW_POTION },

		{ ACTION_SLAYER_MOTOR_MOVE, ACTION_SLAYER_MOTOR_MOVE, ACTION_SLAYER_MOTOR_MOVE },
		{ ACTION_SLAYER_MOTOR_STAND, ACTION_SLAYER_MOTOR_STAND, ACTION_SLAYER_MOTOR_STAND },
	
	};

	//------------------------------------------------------------------
	// vampire action 속도
	//------------------------------------------------------------------
	int VampireActionSpeed[ACTION_MAX_VAMPIRE][3] =
	{
		{ ACTION_STAND, ACTION_STAND, ACTION_STAND },
		{ ACTION_MOVE, ACTION_MOVE, ACTION_MOVE },
		{ ACTION_VAMPIRE_ATTACK_SLOW, ACTION_ATTACK, ACTION_VAMPIRE_ATTACK_FAST },
		{ ACTION_MAGIC, ACTION_MAGIC, ACTION_MAGIC },
		{ ACTION_DAMAGED, ACTION_DAMAGED, ACTION_DAMAGED },
		{ ACTION_DRAINED, ACTION_DRAINED, ACTION_DRAINED },
		{ ACTION_DIE, ACTION_DIE, ACTION_DIE },
		{ ACTION_VAMPIRE_DRAIN, ACTION_VAMPIRE_DRAIN, ACTION_VAMPIRE_DRAIN },
	};


	//---------------------------------------------------------------------
	// 기술 정보
	//---------------------------------------------------------------------
	std::ofstream sfile("Skill.txt");
	
	sfile << "< Slayer Man Action Delay To Second >" << std::endl;

	int second;
	for (int ad=0; ad<ACTION_MAX_SLAYER; ad++)
	{	
		if (ad < AddonManFPK[0].GetSize())
		{
			int frameNum = AddonManFPK[0][ad][0].GetSize();

			if (frameNum < 0) frameNum = 0;

			second = frameNum * 1000 / 16;

			sfile << "[" << ad << "]  " << second << std::endl;
		}
	}


	sfile << "< Slayer Woman Action Delay To Second >" << std::endl;

	for (ad=0; ad<ACTION_MAX_SLAYER; ad++)
	{	
		if (ad < AddonWomanFPK[0].GetSize())
		{
			int frameNum = AddonWomanFPK[0][ad][0].GetSize();

			if (frameNum < 0) frameNum = 0;

			second = frameNum * 1000 / 16;

			sfile << "[" << ad << "]  " << second << std::endl;
		}
	}


	sfile << std::endl << "< Vampire Action Delay To Second >" << std::endl;

	for (ad=0; ad<ACTION_MAX_VAMPIRE; ad++)
	{
		if (ad < CreatureFPK[0].GetSize())
		{
			int frameNum = CreatureFPK[0][ad][0].GetSize();

			if (frameNum < 0) frameNum = 0;

			second = frameNum * 1000 / 16;

			sfile << "[" << ad << "]  " << second << std::endl;
		}
	}

	cfile << std::endl << std::endl << "[ SkillName ]  DelaySecond" << std::endl;

	for (int ai=0; ai<g_pActionInfoTable->GetMinResultActionInfo(); ai++)
	{
		MActionInfo& actionInfo = (*g_pActionInfoTable)[ai];

		const char* name = actionInfo.GetName();
		int action = actionInfo.GetAction();			

		sfile << "[ " << name << " ]  " << action << "    ( ";

		for (int ws=0; ws<3; ws++)
		{
			int sAction;
			
			if (ai==SKILL_ATTACK_MELEE ||
				ai>=SKILL_BLOOD_DRAIN
				&& ai<=MAGIC_UN_INVISIBILITY)
			{
				sAction = VampireActionSpeed[action][ws];
			}
			else
			{
				sAction = SlayerActionSpeed[action][ws];
			}

			int frameNum = AddonManFPK[0][sAction][0].GetSize();

			if (frameNum < 0) frameNum = 0;

			second = frameNum * 1000 / 16;

			sfile << second << ", ";
		}

		sfile << " )" << std::endl;
	}
	sfile.close();

	//---------------------------------------------------------------------
	//
	//						파워짱 아이템 테이블
	//
	//---------------------------------------------------------------------
#ifdef SAVE_POWER_JJANG_INFO
	BYTE MaxPowerjjangItem = 7; // 아이템 갯수
	WORD AvailablePoint = 300; // 획득 가능 포인트
	BYTE PowerjjangItem[7][3] = 
	{	// 아이템 클래스, 아이템 타입, 이미지 인덱스(GCUsePowerPointResult의 ITEM_CODE의 순서대로 powerjjang_Item.spk에 넣자)
	
		{ITEM_CLASS_EVENT_ETC,			14,		0},	// 노란 사탕
		{ITEM_CLASS_RESURRECT_ITEM,		0,		1},	// 부활 스크롤
		{ITEM_CLASS_RESURRECT_ITEM,		1,		2},	// 엘릭서 스크롤
		{ITEM_CLASS_EFFECT_ITEM,		0,		3},	// 확성기
		{ITEM_CLASS_EVENT_GIFT_BOX,		22,		4},	// 네이밍 펜
		{ITEM_CLASS_EVENT_TREE,			26,		5},	// 푯말 (6시간)
		{ITEM_CLASS_EVENT_STAR,			11,		6},	// 검은 떡국
	
//	enum ITEM_CODE
//	{
//		CANDY = 0,				// 사탕 1개 
//		RESURRECTION_SCROLL,	// 부활 스크롤 1개
//		ELIXIR_SCROLL,			// 엘릭서 스크롤 1개
//		MEGAPHONE,				// 확성기 30분
//		NAMING_PEN,				// 네이밍 펜 1개
//		SIGNPOST,				// 알림판 6시간
//		BLACK_RICE_CAKE_SOUP	// 검은 떡국 1개
//	};
	};
//	//-----------------------------------
//	// Save To File
//	//-----------------------------------
	std::ofstream PowerjjangInfoFile(g_pFileDef->getProperty("FILE_INFO_POWERJJANG_STRING").c_str(), ios::binary);	
	PowerjjangInfoFile.write((const char*)&MaxPowerjjangItem, sizeof(MaxPowerjjangItem));
	PowerjjangInfoFile.write((const char*)&AvailablePoint, sizeof(AvailablePoint));
	PowerjjangInfoFile.write((const char*)PowerjjangItem, sizeof(PowerjjangItem));
	PowerjjangInfoFile.close();
#endif

	return TRUE;
}

