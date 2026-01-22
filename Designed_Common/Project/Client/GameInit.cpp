//---------------------------------------------------------------------------
// GameInit.cpp
//---------------------------------------------------------------------------
// 게임 관련 부분(주로 시스템 쪽)의 초기화 / Release
//---------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Include files
//-----------------------------------------------------------------------------
#include "Client_PCH.h"
#include <MMSystem.h>
#include "Client.h"
#include "GameObject.h"
#include "AddonDef.h"
#include "ServerInfo.h"
#include "PacketDef.h"
#include "VS_UI.h"
#include "COpeningUpdate.h"
#include "CGameUpdate.h"
#include "CWaitPacketUpdate.h"
#include "UserInformation.h"
#include "TempInformation.h"
#include "CWaitUIUpdate.h"
#include "UIDialog.h"
#include "MMusic.h"
#include "MGameStringTable.h"
#include "MMoneyManager.h"
#include "MPriceManager.h"
#include "MChatManager.h"
#include "MTradeManager.h"
#include "UIMessageManager.h"
#include "MStorage.h"
#include "MHelpManager.h"
#include "MHelpStringTable.h"
#include "MCompareManager.h"
#include "MHelpDisplayer.h"
#include "MObjectSelector.h"
#include "MLevelNameTable.h"
#include "MonsterNameTable.h"
#include "ExperienceTable.h"
#include "ServerInformation.h"
#include "GameObject.h"
#include "MZoneSoundManager.h"
#include "MNPCScriptTable.h"
#include "MParty.h"
#include "SpriteIDDef.h"
#include "MathTable.h"
#include "ModifyStatusManager.h"
#include "RequestServerPlayerManager.h"
#include "RequestClientPlayerManager.h"
#include "ClientCommunicationManager.h"
#include "KeyAccelerator.h"
#include "AcceleratorManager.h"
#include "WhisperManager.h"
#include "ProfileManager.h"
#include "MGuildMarkManager.h"
#include "MEventManager.h"
#include "RequestFileManager.h"
#include "RequestUserManager.h"
#include "MJusticeAttackManager.h"
#include "Profiler.h"
#include "WavePackFileManager.h"
//#include "MFileDef.h"
#include "MGuildInfoMapper.h"
#include "PCConfigTable.h"
#include "MAttachOrbitEffect.h"
#include "DebugInfo.h"
#include "MTestDef.h"
#include "CMP3.h"
#include "RankBonusTable.h"
#include "MMonsterKillQuestInfo.h"
#include "MTimeItemManager.h"
#include "FameInfo.h"
#include "MWarManager.H"
#include "CSprite555.h"
#include "CSprite565.h"
#include "Properties.h"
#include "UIFunction.h"
#include "SoundSetting.h"
#include "SystemAvailabilities.h"
#include "ShrineInfoManager.h"
#include "ServerInfoFileParser.h"
#include "MWorkThreadGlobal.h"
#include "BGMManager.h"
#include "MilitarySlot.h"

#if __CONTENTS(__PREMIUM_GIVE_ITEM_UI)
#include "MPremiumGiveItemInfo.h"
#endif //__PREMIUM_GIVE_ITEM_UI

extern BYTE g_macAddress[6];
extern BOOL GetMacAddressFromSock();

//#include "CJpeg.h"
//#define	new			DEBUG_NEW

// ToT SafeDelete 도 없고..ToT 2003.5.11 by sonee

extern int					g_Dimension ;

BOOL g_bEnable3DHAL = TRUE;

//----------------------------------------------------------------------
// Title Loading - 2001.8.20 우헤헤 자꾸 늘어나는 global - -;;
//----------------------------------------------------------------------
//CSpritePack		g_TitleSPK;
//CSpritePack		g_TitleAniSPK;
//int				g_TitleSpriteID = 0;
//int				g_TitleSpriteDarkness = 4;
bool			g_bTitleLoading = false;
//CSprite*		g_pTitleLoadingSprite = NULL;

CSpritePack*	g_pTitleLoadingSPK = NULL;

int				g_TitleSpriteAlpha = 32;
//CDirectDrawSurface	g_TitleSurface;


// [Futec수정]
extern char g_FutecIP[20];
extern unsigned int g_FutecPort;

#ifdef OUTPUT_DEBUG
	extern CRITICAL_SECTION		g_Lock;
#endif

//----------------------------------------------------------------------
// AddonSPK 분할 로딩 - 2001.8.20
//----------------------------------------------------------------------
TYPE_SPRITEID		g_AddonSPKNum = 0;
const int			g_AddonSPKLoadingTimes = 20;	// 20등분으로 나눠서 loading한다.
bool				g_AddonSPKLoaded[g_AddonSPKLoadingTimes] = { false, };
int					g_AddonSPKIndexFirst[g_AddonSPKLoadingTimes] = { 0, };
int					g_AddonSPKIndexLast[g_AddonSPKLoadingTimes] = { 0, };
long				g_AddonSPKIndexFP[g_AddonSPKLoadingTimes] = { 0, };
bool				g_AddonSPKAllLoaded = false;

bool				g_bHALAvailable = false;
extern bool				g_bHALAvailable;


void	StartTitleLoading();
void	DrawTitleLoading();
void	EndTitleLoading(bool SendLogin = false);
bool	PrepareLoadingAddonSPK();
bool	LoadingAddonSPK(bool bLoadingAll);

//#define	CLIENT_VERSION		"[TestVersion] : 2000.12.05.09"
//---------------------------------------------------------------------------
// Start TitleLoading
//---------------------------------------------------------------------------
// 2001.8.20
//---------------------------------------------------------------------------
void
StartTitleLoading()
{
//	std::ifstream	titleFile;//(FILE_SSPRITE_IMAGEOBJECT, ios::binary);
//	if (!FileOpenBinary("data\\ui\\spk\\Title.spk", titleFile))
//		return;
//
//	g_TitleSPK.LoadFromFile(titleFile);
//	titleFile.close();
//
//	std::ifstream	titleAniFile;//(FILE_SSPRITE_IMAGEOBJECT, ios::binary);
//	if (!FileOpenBinary("data\\ui\\spk\\TitleAni.spk", titleAniFile))
//		return;
//
//	g_TitleAniSPK.LoadFromFile(titleAniFile);
//	titleAniFile.close();
//	
//
//	g_TitleSpriteID = 0;
//	g_TitleSpriteDarkness = 4;
	g_bTitleLoading = true;

//	CJpeg jpg;
//	bool bOpen = jpg.Open(g_pFileDef->getProperty("FILE_JPG_SOFTON_CI").c_str());
//	if(bOpen == true && jpg.GetWidth() > 0 && jpg.GetHeight() > 0 && jpg.GetHeight() > 0)
//	{
//		g_bTitleLoading = true;
//		CDirectDrawSurface &surface = g_TitleSurface;
//		const int bpp = jpg.GetBpp(), width = jpg.GetWidth(), height = jpg.GetHeight(), pitch = width*bpp;
//
//		if (surface.InitOffsurface(width, height, DDSCAPS_SYSTEMMEMORY))
//		{
//			if (surface.Lock())
//			{
//				WORD *pSurface = (WORD *)surface.GetSurfacePointer();
//				unsigned char *pData = jpg.GetImage(), *pDataTemp;
//				WORD *pSurfaceTemp;
//				
//				int surfacePitch = surface.GetSurfacePitch();
//				
//				if (pSurface)
//				{
//					if (bpp == 1)
//					{
//						for (int y = 0; y < height; y++)
//						{
//							pDataTemp = pData;
//							pSurfaceTemp = pSurface;								
//							
//							for (int x = 0; x < width; x++)
//							{
//								BYTE temp_data = *pDataTemp++;	//p_data[y*(pitch)+x];
//								BYTE r = temp_data>>3;
//								BYTE g = r;
//								BYTE b = r;
//								
//								*pSurfaceTemp++ = CDirectDraw::Color(r, g, b);
//							}
//							
//							pData = pData + pitch;
//							pSurface = (WORD*)((BYTE*)pSurface + surfacePitch);
//						}
//					}
//					else if (bpp == 3)
//					{
//						for (int y = 0; y < height; y++)
//						{
//							pDataTemp = pData;
//							pSurfaceTemp = pSurface;	
//							
//							for (int x = 0; x < width; x++)
//							{
//								//char *temp_data = &p_data[y*pitch+x*bpp];
//								BYTE r = *(pDataTemp+2) >> 3;		//temp_data[2]>>3;
//								BYTE g = *(pDataTemp+1) >> 3;	//temp_data[1]>>3;
//								BYTE b = *pDataTemp >> 3;	//temp_data[0]>>3;
//								
//								pDataTemp += bpp;
//								
//								*pSurfaceTemp++ = CDirectDraw::Color(r, g, b);
//							}
//							
//							pData = pData + pitch;
//							pSurface = (WORD*)((BYTE*)pSurface + surfacePitch);
//						}
//					}
//					
//				}
//				
//				surface.Unlock();
//			}
//		}
//	}
	
	/*
	if (g_pTitleLoadingSprite==NULL)
	{
		if (CDirectDraw::Is565())
		{
			g_pTitleLoadingSprite = new CSprite565;
		}
		else
		{
			g_pTitleLoadingSprite = new CSprite555;
		}

		CFileIndexTable	FIT;
		ivfstream indexFile(g_pFileDef->getProperty("FILE_SPRITEINDEX_UI").c_str(), std::ios::binary);
		FIT.LoadFromFile( indexFile );
		indexFile.close();

		ivfstream spkFile(g_pFileDef->getProperty("FILE_SPRITE_UI").c_str(), std::ios::binary);
		spkFile.seekg( FIT[SPRITEID_CI] );

		g_pTitleLoadingSprite->LoadFromFile( spkFile );
		spkFile.close();
	}
	*/

	if(g_pTitleLoadingSPK == NULL)
	{
		g_pTitleLoadingSPK = new CSpritePack;
		g_pTitleLoadingSPK->LoadFromFile(g_pFileDef->getProperty("FILE_SPRITE_UI").c_str());
	}
}
	
//---------------------------------------------------------------------------
// Draw TitleLoading
//---------------------------------------------------------------------------
// 2001.8.20
//---------------------------------------------------------------------------
void
DrawTitleLoading()
{
	int iSpriteID_CI = 0;
	bool bHighResolution = g_pUserInformation->iResolution_x > 800;
	int ConvX = 0;	int ConvY = 0;
	if(bHighResolution)	// 1024*768, 1280*960, 1280*1024
	{
		if(g_pUserInformation->iResolution_x <=1024)
			iSpriteID_CI = SPRITEID_CI_1024_768;
		else
		{
			if(g_pUserInformation->iResolution_y < 960)
			{	
				iSpriteID_CI = SPRITEID_CI_1280_720;
			}
			else if(g_pUserInformation->iResolution_y < 1024)
			{	
				iSpriteID_CI = SPRITEID_CI_1280_960;
			}
			else
			{	
				iSpriteID_CI = SPRITEID_CI_1280_1024;
			}
		}
	}
	else
		iSpriteID_CI = SPRITEID_CI_800_600;
	if (g_bTitleLoading)
	{
		//--------------------------------------------------------
		// 2001.8.20
		//--------------------------------------------------------
		POINT pointZero = {
			(SURFACE_WIDTH-(*g_pTitleLoadingSPK)[iSpriteID_CI].GetWidth())/2,
			(SURFACE_HEIGHT-(*g_pTitleLoadingSPK)[iSpriteID_CI].GetHeight())/2
		};


		//POINT point = { 263, 93 };

//		g_pBack->FillSurface( CDirectDraw::Color(0,0,0) );
		
//		g_pBack->Lock();

//		g_pBack->Blt(&pointZero, &g_TitleSurface, &rect);
//		g_pBack->BltSprite( &pointZero, &g_TitleSPK[ 0 ] );

//		if (g_TitleSpriteDarkness==0)
//		{
//			g_pBack->BltSprite( &point, &g_TitleAniSPK[g_TitleSpriteID] );
//		}
//		else
//		{
//			g_pBack->BltSpriteDarkness( &point, &g_TitleAniSPK[g_TitleSpriteID], g_TitleSpriteDarkness );
//		}

//		g_pBack->Unlock();

		// Loading 출력
		/*
		if (gpC_base!=NULL)
		{
			if (!CDirect3D::IsHAL())
			{
				g_SetFL2Surface( g_pBack->GetSurface() );
			}

			PrintInfo* pPrintInfo = &gpC_base->m_info_pi;
			const COLORREF txColor = RGB(100,250,100);				
			const COLORREF txColor2 = RGB(20,50,20);

			pPrintInfo->text_color	= txColor2;
			g_Print(331, 451, "잠시 기다려주세요.", pPrintInfo);
			pPrintInfo->text_color	= txColor;
			g_Print(330, 450, "잠시 기다려주세요.", pPrintInfo);
			
			//char str[80];
			//sprintf(str, "[%d]", g_TitleSpriteID);
			//g_Print(330, 480, str, pPrintInfo);	
			
			if (!CDirect3D::IsHAL())
			{
				g_SetFL2Surface( g_pLast->GetSurface() );
			}
		}
		*/
		
		if(g_pTitleLoadingSPK)
		{
//			point.x = 400 - (g_pTitleLoadingSprite->GetWidth()>>1);
//			point.y = 460 - (g_pTitleLoadingSprite->GetHeight()>>1);
//			
			CSpriteSurface *pSurface = NULL;
//			if (!CDirect3D::IsHAL())
			if(g_TitleSpriteAlpha != 32)
			{
				pSurface = g_pLast;
			}
			else
			{
				pSurface = g_pBack;
			}

			//pSurface->FillSurface(0);
			POINT deliberationPoint = {SURFACE_WIDTH-(*g_pTitleLoadingSPK)[SPRITEID_CI_DELIBERATION].GetWidth() - 6, 
				6};

			pSurface->Lock();

			if(g_TitleSpriteAlpha == 32)
			{
				pSurface->BltSprite(&pointZero, &(*g_pTitleLoadingSPK)[iSpriteID_CI]);
#if __CONTENTS(__USER_GRADE)
				pSurface->BltSprite(&deliberationPoint, 
					&(*g_pTitleLoadingSPK)[SPRITEID_CI_DELIBERATION]);
#endif	//__USER_GRADE
			}
			else
			{
				pSurface->BltSpriteAlpha( &pointZero, &(*g_pTitleLoadingSPK)[iSpriteID_CI], g_TitleSpriteAlpha);
			}
			pSurface->Unlock();
		}

		if(g_TitleSpriteAlpha == 32)
			CDirectDraw::Flip();

		
		// frame 바꿈
//		if (++g_TitleSpriteID>=g_TitleAniSPK.GetSize())
//		{
//			g_TitleSpriteID = 0;			
//		}
//			
//		// 밝기 조절
//		if (g_TitleSpriteID%3==2)
//		{
//			if (--g_TitleSpriteDarkness < 0)
//			{
//				g_TitleSpriteDarkness = 0;
//			}
//		}			
	}
}

//---------------------------------------------------------------------------
// End TitleLoading
//---------------------------------------------------------------------------
void
EndTitleLoading(bool SendLogin)
{
//	g_TitleAniSPK.Release();
//	g_TitleSPK.Release();
//	g_TitleSpriteID = 0;
//	g_TitleSpriteDarkness = 4;
	g_bTitleLoading = false;

	if (g_pTitleLoadingSPK!=NULL)
	{
		delete g_pTitleLoadingSPK;
		g_pTitleLoadingSPK = NULL;
	}
	// 2004, 7, 15, sobeit modify start
	
	if(SendLogin && true == g_pUserInformation->IsAutoLogIn) // 자동 로그인
	{
		static LOGIN	login;
		login.sz_id = new char[  g_pUserInformation->UserID.GetLength() + 1 ];
		//해당 문자열을 32바이트로 늘리면서 NULL문자 누락이 생기지 않도록 +1 해준다.
		login.sz_password = new char[ 32 + 1 ];

		strcpy( login.sz_id, g_pUserInformation->UserID.GetString() );		
		strcpy( login.sz_password, g_pUserInformation->AutoLogInKeyValue.GetString() );
		
		gpC_base->SendMessage(UI_LOGIN, 0, 0, (void *)&login);
	}
	// 2004, 7, 15, sobeit modify end
}

//---------------------------------------------------------------------------
// PrepareLoadingAddonSPK
//---------------------------------------------------------------------------
bool
PrepareLoadingAddonSPK()
{
	return true;

	/*
	#ifdef OUTPUT_DEBUG
		if (g_pDebugMessage)
		{
			DEBUG_ADD("Prepare LoadingAddonSPK");
		}
	#endif

	g_AddonSPKAllLoaded = false;

	if (g_pTopView==NULL)
	{
		#ifdef OUTPUT_DEBUG
			if (g_pDebugMessage)
			{
				DEBUG_ADD("[Error] g_pTopView is NULL");
			}
		#endif

		return false;
	}

	//------------------------------------------------------------
	// 나눠서 로딩하기 위한 준비.. 2001.8.20 추가
	//------------------------------------------------------------
	if (g_AddonSPKNum==0)
	{
		ivfstream	AddonFileIndex2;//(FILE_ISPRITE_ADDON, ios::binary);
		if (!FileOpenBinary(g_pFileDef->getProperty("FILE_ISPRITEINDEX_ADDON").c_str(), AddonFileIndex2))
			return false;

		AddonFileIndex2.read((char*)&g_AddonSPKNum, SIZE_SPRITEID);

		// 개수를 잡아둔다.
		g_pTopView->m_AddonSPK.Init(g_AddonSPKNum);		

		//bool				g_AddonSPKLoaded[g_AddonSPKLoadingTimes] = { false, };
		//bool				g_AddonSPKIndex[g_AddonSPKLoadingTimes] = { 0 };

		// loading하는 회수에 맞게 file index를 구한다.
		int first = 0;
		for (int i=0; i<g_AddonSPKLoadingTimes; i++)
		{
			// 1/3
			int last = (int)g_AddonSPKNum * (i+1) / g_AddonSPKLoadingTimes;
			
			// 더 클 일은 없겠지만.. 혹시.. - -;;
			if (last >= g_AddonSPKNum)
			{
				last = g_AddonSPKNum - 1;
			}

			long fp;
			// 개수(2 bytes) + ID * (4 bytes)
			AddonFileIndex2.seekg( 2 + first*4 , std::ios::beg );
			AddonFileIndex2.read((char*)&fp, 4);

			// loading해야된다고 표시
			g_AddonSPKLoaded[i] = false;

			// file index설정			
			g_AddonSPKIndexFirst[i] = first;
			g_AddonSPKIndexLast[i] = last;
			g_AddonSPKIndexFP[i] = fp;
			

			// 다음 꺼.
			first = last+1;
		}

		AddonFileIndex2.close();
	}
	*/

	return true;
}

//---------------------------------------------------------------------------
// LoadingAddonSPK
//---------------------------------------------------------------------------
bool
LoadingAddonSPK(bool bLoadingAll)
{
	return true;

	/*
	#ifdef OUTPUT_DEBUG
		if (g_pDebugMessage)
		{
			if (bLoadingAll)
			{
				DEBUG_ADD("LoadingAddonSPK - LoadingAll");
			}
			else
			{
				DEBUG_ADD("LoadingAddonSPK - LoadingPart");
			}
		}
	#endif

	if (g_pTopView==NULL)
	{
		#ifdef OUTPUT_DEBUG
			if (g_pDebugMessage)
			{
				DEBUG_ADD("[Error] g_pTopView is NULL");
			}
		#endif

		return false;
	}

	for (int i=0; i<g_AddonSPKLoadingTimes; i++)
	{
		// loading 안 된 부분이 있으면 loading한다.
		if (!g_AddonSPKLoaded[i])
		{
//			std::ifstream	addonFile;
//
//			if (!FileOpenBinary(FILE_ISPRITE_ADDON, addonFile))
//				return false;	

			TYPE_SPRITEID first = g_AddonSPKIndexFirst[i];
			TYPE_SPRITEID last	= g_AddonSPKIndexLast[i];
			long			fp	= g_AddonSPKIndexFP[i];

			#ifdef OUTPUT_DEBUG
				if (g_pDebugMessage)
				{
					DEBUG_ADD_FORMAT("LoadingAddonSPK: [%d ~ %d](fp=%d). num=%d", first, last, fp, g_AddonSPKNum);
				}
			#endif

			g_pTopView->m_AddonSPK.LoadFromFilePart(first, last);
		
			g_AddonSPKLoaded[i] = true;

			// 전부 loading해야하는 경우가 아니면 한부분만 loading한다.
			if (!bLoadingAll)
			{
				#ifdef OUTPUT_DEBUG
					if (g_pDebugMessage)
					{
						DEBUG_ADD("LoadingAddonSPK Part OK");
					}
				#endif

				return true;
			}
		}
	}

	g_AddonSPKAllLoaded = true;

	#ifdef OUTPUT_DEBUG
		if (g_pDebugMessage)
		{
			DEBUG_ADD("All AddonSPK is Loaded");
		}
	#endif
	*/

	return true;
}

//---------------------------------------------------------------------------
// Init Volume
//---------------------------------------------------------------------------
BOOL
InitVolume()
{
	// Debug Message
	DEBUG_ADD("[ InitGame ]  Volume");

	//--------------------------------------------------------
	// Master volume
	//--------------------------------------------------------
	//g_pMasterVolume = (IVolume*)new CVolumeOutMaster;
	if (!g_pMasterVolume || !g_pMasterVolume->IsAvailable() )
	{
 		//InitFail("Master Volume 조절이 안됨");
		// Debug Message
		DEBUG_ADD("[Error] Volume : MasterVolume Failed!");
	}

	//--------------------------------------------------------
	// Wave volume
	//--------------------------------------------------------
	//g_pWaveVolume = (IVolume*)new CVolumeOutWave;
	if (!g_pWaveVolume || !g_pWaveVolume->IsAvailable() )
	{
 		//InitFail("Wave Volume 조절이 안됨");
		// Debug Message
		DEBUG_ADD("[Error] Volume : WaveVolume Failed!");
	}

	if (g_pMasterVolume!=NULL)
	{
		g_MasterVolumeOriginal = g_pMasterVolume->GetCurrentVolume();
	}

	if (g_pWaveVolume!=NULL)
	{
		g_WaveVolumeOriginal = g_pWaveVolume->GetCurrentVolume();
	}
	
	return TRUE;
}

//---------------------------------------------------------------------------
// Init Input
//---------------------------------------------------------------------------
BOOL
InitInput()
{
	// Debug Message
	DEBUG_ADD("[ InitGame ]  Input");

	if (g_pDXInput==NULL)
	{
		g_pDXInput = new CDirectInput;
	}

	//----------------------------
	// DirectInput
	//----------------------------
	//g_pDXInput->Init(g_hInstance);
	//g_pDXInput->InitKeyDevice(g_hWnd);
//	g_pDXInput->InitJoyDevice(g_hWnd);
	//g_pDXInput->InitMouseDevice(g_hWnd);

	if (!g_pDXInput->Init( g_hWnd, g_hInstance, CDirectInput::NONEXCLUSIVE ))
	{
		InitFail("DirectInput Error!");
		return false;
	}

	//g_pDXInput->SetMouseMoveLimit(SURFACE_WIDTH, SURFACE_HEIGHT);

	g_pDXInput->SetAcquire(true);

	return TRUE;
}


//---------------------------------------------------------------------------
// Surface의 정보를 생성한다.
//---------------------------------------------------------------------------
BOOL
InitSurface()
{
	DEBUG_ADD("[ InitGame ]  Surface");

	//--------------------------------------------------------
	// Back Surface
	//--------------------------------------------------------
	if (g_pBack!=NULL) 
	{
		delete g_pBack;
	}
	g_pBack = new CSpriteSurface;
	g_pBack->InitBacksurface();	

	//--------------------------------------------------------
	// 임시로 로딩화면 구성..
	// 2001.8.20
	//--------------------------------------------------------

	StartTitleLoading();
	DrawTitleLoading();


	g_pBack->SetTransparency( 0 );
	g_pBack->FillSurface( CDirectDraw::Color(31,31,31) );

	//--------------------------------------------------------
	// Buffer로 사용할 Surface
	//--------------------------------------------------------
	DEBUG_ADD("[ InitGame ]  Surface - new g_pTopView");

		
	if (g_pTopView==NULL)
	{		
		g_pTopView = new MTopView;

		// addonSPK 분할 로딩 준비 - 2001.8.20
		if (!PrepareLoadingAddonSPK())
		{
			return FALSE;
		}
	}


	// H/W가속 되는 경우
//	if (CDirect3D::IsHAL())
//	{
//		g_pTopView->SetSurface( g_pBack );
//	}
//	// H/W가속 안 되는 경우
//	else
	{		
		if (g_pLast!=NULL) 
		{
			delete g_pLast;
		}
		g_pLast = new CSpriteSurface;	
		g_pLast->InitOffsurface(
			SURFACE_WIDTH, SURFACE_HEIGHT, DDSCAPS_SYSTEMMEMORY);
		g_pLast->SetTransparency( 0 );
		g_pLast->FillSurface( CDirectDraw::Color(31,31,31) );

		g_pTopView->SetSurface( g_pLast );
	}

	//--------------------------------------------------------
	// 감마값 설정
	//--------------------------------------------------------
	if (g_pUserOption->UseGammaControl
		&& g_pUserOption->GammaValue!=100)
	{
		CDirectDraw::SetGammaRamp( g_pUserOption->GammaValue );
	}

	//--------------------------------------------------------
	//                UI
	//--------------------------------------------------------	
	DEBUG_ADD("[ InitGame ]  Surface - InitializeGL");


	InitializeGL(CDirectDraw::Get_BPP(), 
					 CDirectDraw::Get_Count_Rbit(), 
					 CDirectDraw::Get_Count_Gbit(), 
					 CDirectDraw::Get_Count_Bbit());

	DEBUG_ADD("[ InitGame ]  Surface - Initialize Font");
	DEBUG_ADD("[ InitGame ]  Surface - UI");

	// 슬레이어 그림 약간 loading
	LoadingAddonSPK( false );
	DrawTitleLoading();


	// 일단 제거.. - -;
	gC_vs_ui.Release();

	DEBUG_ADD("[ InitGame ]  Surface - InitD3D");
//	if (CDirect3D::IsHAL())
//	{
//		gC_vs_ui.Init(g_pBack, UI_ResultReceiver);		
//	} 
//	else
	{
		gC_vs_ui.Init(g_pLast, UI_ResultReceiver);
	}

#if __CONTENTS(__MOVE_ZONE)
	#ifdef __MOVE_ZONE_UI__
		gC_vs_ui.MoveZoneUi_On();
	#else
		gC_vs_ui.MoveZoneUi_Off();
	#endif //__MOVE_ZONE_UI__
#endif //__MOVE_ZONE

	//--------------------------------------------------------
	// 2001.8.20
	//--------------------------------------------------------	
	DrawTitleLoading();	

//	gC_vs_ui.SetVersion(CLIENT_VERSION);




	///*
	//--------------------------------------------------------
	// 새로운 IndexSprite 생성 방법 TEST
	//--------------------------------------------------------
	// indexTable은 555와 565가 다르기 때문에...
	// 잘~~골라서 해야한다. = =;
	CIndexSprite::SetColorSet();

	//#ifdef OUTPUT_DEBUG
	//	std::ofstream indexTable(FILE_INDEXTABLE, ios::binary);
	//	CIndexSprite::SaveIndexTableToFile( indexTable );
	///	indexTable.close();
	//#endif
	
	//std::ifstream indexTable2;//(FILE_INFO_USINGCOLORSET, ios::binary);
	//if (!FileOpenBinary(FILE_INDEXTABLE, indexTable2))
	//	return FALSE;
	//CIndexSprite::LoadIndexTableFromFile( indexTable2 );
	//indexTable2.close();

	/*
	CSpriteSurface imageSurface;
	CSpriteSurface indexSurface1;
	//CSpriteSurface indexSurface2;
	
	WORD *lpImage, imagePitch;
	WORD *lpIndex1, indexPitch1;
	//WORD *lpIndex2, indexPitch2;

	imageSurface.InitFromBMP("test\\0.bmp", DDSCAPS_SYSTEMMEMORY);	
	indexSurface1.InitFromBMP("test\\0i.bmp", DDSCAPS_SYSTEMMEMORY);	
	//indexSurface2.InitFromBMP("Gauntlet2.bmp", DDSCAPS_SYSTEMMEMORY);	

	imageSurface.LockW(lpImage, imagePitch);
	indexSurface1.LockW(lpIndex1, indexPitch1);
	//indexSurface2.LockW(lpIndex2, indexPitch2);

	CIndexSprite565 is;

	RECT rect;

	CSprite::GetTightColorRect(lpImage, imagePitch, 
								imageSurface.GetWidth(), imageSurface.GetHeight(),
								0x001F, 
								rect);


	lpImage = (WORD*)((BYTE*)lpImage + imagePitch*rect.top + (rect.left << 1));
	lpIndex1 = (WORD*)((BYTE*)lpIndex1 + indexPitch1*rect.top + (rect.left << 1));
	//lpIndex2 = (WORD*)((BYTE*)lpIndex2 + indexPitch2*rect.top + (rect.left << 1));

	CIndexSprite::SetColorkey( 0x001F );
	//CIndexSprite::SetColorkey( ((32>>3) << 11) | ((32>>3) << 6) | (32>>3) );
	is.SetPixel(lpImage, imagePitch,
				lpIndex1, indexPitch1,
				NULL, 0, //lpIndex2, indexPitch2,
				rect.right-rect.left, rect.bottom-rect.top);
	
	imageSurface.Unlock();
	indexSurface1.Unlock();
	//indexSurface2.Unlock();

	std::ofstream file("test.ispr", ios::binary);
	is.SaveToFile( file );
	file.close();

	POINT point;
	point.x = 100;
	point.y = 100;
	WORD a=40, b=150;
	while (1)
	{
		UpdateInput();

		if (g_pDXInput->KeyDown(DIK_ESCAPE))
			break;

		if (g_pDXInput->KeyDown(DIK_SPACE))
		{
			a = rand()%MAX_COLORSET;
			b = rand()%MAX_COLORSET;
		}

		g_pBack->FillSurface( 0 );	

		g_pBack->Lock();
		CIndexSprite::SetUsingColorSet( a, b );
		g_pBack->BltIndexSprite( &point, &is );
		g_pBack->Unlock();

		CDirectDraw::Flip();
	}

	return FALSE;
	*/	

	//--------------------------------------------------------
	// View의 정보를 초기화 시킨다.
	//--------------------------------------------------------
	//g_pTopView->SetSurface(g_pLast);	
	if (g_Mode==MODE_CHANGE_OPTION	// 옵션 바꿀때는 g_pTopView->Init()는 안 한다.
		&& !g_pTopView->Init())
	{
		return FALSE;
	}			

	DrawTitleLoading();	
//	EndTitleLoading();
	
	//g_pTopView->SetDarkBits(5);
		

	// ColorSet을 초기화시킨다.
	CIndexSprite::SetColorSet();
	
	//--------------------------------------------------------
	// Cursor Surface 초기화
	//--------------------------------------------------------
	// 2개의 Flip Surface, (32*32)
	if (CDirectDraw::IsFullscreen())
	{
		if (g_pCursorSurface!=NULL)
		{
			delete g_pCursorSurface;
			g_pCursorSurface = NULL;
		}

		//g_pCursorSurface = new CStorageSurface;
	}
	//g_pCursorSurface.Init(2, CURSOR_SURFACE_WIDTH, CURSOR_SURFACE_HEIGHT);
	DrawTitleLoading();	

	return TRUE;
}

//---------------------------------------------------------------------------
// Init Sound
//---------------------------------------------------------------------------
BOOL
InitSound()
{
	// Debug Message
	DEBUG_ADD("[ InitGame ]  InitSound");

	//--------------------------------------------------------
	//
	//                 DirectSound
	//
	//--------------------------------------------------------
	/*
	if (g_pWavePackFileManager==NULL)
	{
		g_pWavePackFileManager = new WavePackFileManager;

		g_pWavePackFileManager->LoadFromFileInfo(FILE_WAVE_PACK_SOUND_INDEX);
		g_pWavePackFileManager->SetDataFilename(FILE_WAVE_PACK_SOUND);
	}
	*/

	if (g_DXSound.IsInit())
	{
		DEBUG_ADD("[ InitGame ]  Already Init");

		return TRUE;
	}
	else
	{
		if (g_DXSound.Init(g_hWnd))
		{	
			// filename에 따라서.. Wav file을 Load한다.
			//for (int i=0; i<(*g_pSoundTable).GetSize(); i++)
			//{			
			//	(*g_pSoundTable)[i].pDSBuffer = g_Sound.LoadWav( (*g_pSoundTable)[i].Filename );
			//}
			int value = g_pUserOption->VolumeSound;	

			LONG volume = value*SOUND_DEGREE + SOUND_MIN;

			g_DXSound.SetVolumeLimit( volume );	

			BGMManager::Instance()->Init(g_DXSound.GetDS());
		}
		else
		{
			DEBUG_ADD("[Error] Init Sound Error");

			return FALSE;
		}

		//-----------------------------------------------------------
		// RAM 체크해서.. 적당하게 잡아준다.
		//-----------------------------------------------------------
		MEMORYSTATUS ms;
		ZeroMemory(&ms, sizeof(MEMORYSTATUS));
		ms.dwLength = sizeof(MEMORYSTATUS);

		GlobalMemoryStatus( &ms );

		// dwAvailPhys는 왠지 이상하다. -_-;
		// 100메가 이상인 경우..
		// 사운드에 10메가를 투자한다.
		if (ms.dwTotalPhys >= 100*1024*1024)
		{
			// 이것도 임시코드지만.. - -;
			g_pClientConfig->MAX_SOUNDPART = 100;
		}

		// ( 전체 개수, 메모리 허용 개수 )
		g_pSoundManager->Init( g_pSoundTable->GetSize(), g_pClientConfig->MAX_SOUNDPART );

		/*
		for (int i=0; i<2; i++)
		for (int soundID=0; soundID<(*g_pClientConfig).MAX_SOUNDPART; soundID++)
		{
			//-----------------------------------------------------------
			// 없으면 --> Load & Play
			//-----------------------------------------------------------
			if (g_pSoundManager.IsDataNULL(soundID))
			{
				// 다시 load						
 				LPDIRECTSOUNDBUFFER pBuffer = g_DXSound.LoadWav( (*g_pSoundTable)[soundID].Filename );

				// Load에 성공 했으면...
				if (pBuffer!=NULL)
				{
					// Replace됐으면 원래것을 메모리에서 지운다.
					LPDIRECTSOUNDBUFFER pOld;
					if (g_pSoundManager.SetData( soundID, pBuffer, pOld ))
					{
						pOld->Release();
					}				
				}
			}
			//-----------------------------------------------------------
			// 있는 경우 --> Play
			//-----------------------------------------------------------
			else
			{
				LPDIRECTSOUNDBUFFER pBuffer;
				if (g_pSoundManager.GetData(soundID, pBuffer))
				{
				
				}		
			}
		}

		return FALSE;
		*/

		return TRUE;
	}
	
}

//---------------------------------------------------------------------------
// Init Music
//---------------------------------------------------------------------------
BOOL
InitMusic()
{
	// Debug Message
	DEBUG_ADD("[ InitGame ]  Music");
	
	//--------------------------------------------------------
	//
	//                 Music
	//
	//--------------------------------------------------------
	//g_Music.Init(g_hWnd);	
		/*
	if (g_bMusicSW)
	{
		g_DXMusic.Init(g_hWnd, DIRECTMUSIC_TYPE_SW);
	}
	else
	{
		g_DXMusic.Init(g_hWnd, DIRECTMUSIC_TYPE_HW);
	}
	*/
	g_Music.Init( g_hWnd );

	//int volume = g_Music.GetVolume();
	//			DEBUG_ADD_FORMAT("[MIDI] Volume in Init = %x", volume);

	int value = g_pUserOption->VolumeMusic;
				
	WORD volume = value*0x1000 + 0x0FFF;

	g_Music.SetVolume( volume );

	
//	if (g_pDXSoundStream==NULL)
//	{
//		g_pDXSoundStream = new CDirectSoundStream;
//
//		int value = g_pUserOption->VolumeMusic;	
//
//		LONG volume = value*SOUND_DEGREE + SOUND_MIN;
//
//		g_pDXSoundStream->SetVolumeLimit( volume );	
//	}

	DEBUG_ADD("MP3 new");
#ifdef __USE_MP3__
	if (g_pMP3 == NULL)
	{
		g_pMP3 = new CMP3;

	DEBUG_ADD("MP3 new OK");
		int value = g_pUserOption->VolumeMusic;	

		LONG volume = value*16*257;// value*SOUND_DEGREE + SOUND_MIN;

	DEBUG_ADD("MP3 SetVolume1");
		g_pMP3->SetVolume( volume );	
	DEBUG_ADD("MP3 SetVolume1 OK");
	}
#else
	if( g_DXSound.IsInit() )
	{
// 		if( g_pSoundBufferForOGG == NULL )
// 		{
// 			g_pSoundBufferForOGG = new CDirectSoundBuffer(g_hWnd, SOUND_STEREO, SOUND_44K, SOUND_16BIT);
// 		}
// 		if( g_pOGG == NULL )
// 		{
// #ifdef _MT
// 			g_pOGG = new COGGSTREAM(g_hWnd, g_pSoundBufferForOGG, 44100, 11025, 8800);
// #else
// 			g_pOGG = new COGGSTREAM(g_hWnd, g_pSoundBufferForOGG, 44100, 11025, 8800,1);
// #endif
// 			int volume = (g_pUserOption->VolumeMusic - 15) * 250;
// 
// 			g_pOGG->streamVolume( max( -10000, min( -1, volume ) ) );
// 		}

		BGMManager::Instance()->SetVolume(max( -10000, min( -1, volume ) ));
	}
#endif

	return TRUE;
}

//---------------------------------------------------------------------------
// Init Draw
//---------------------------------------------------------------------------
BOOL
InitDraw()
{
	// Debug Message
	DEBUG_ADD("[ InitGame ]  Draw");

	//--------------------------------------------------------
	// 3D가속 여부를 ClientConfig에서 읽어온다.
	//--------------------------------------------------------
	g_bHAL = (g_pUserOption->Use3DHAL)? true : false;

//	bool g_bUseIMEWindow = (g_pUserOption->Chinese) ? true : false;

	//bool g_bUseIMEWindow = gC_ci->IsChinese() == true;
	bool g_bUseIMEWindow = true;

	//--------------------------------------------------------
	//
	//                 DirectDraw
	//
	//--------------------------------------------------------
	//if (g_bHAL)
	if( g_bHAL )
	{
		if (g_bFullScreen)
		{
			CDirectDraw::Init(g_hWnd, SURFACE_WIDTH, SURFACE_HEIGHT, CDirectDraw::FULLSCREEN, true, g_bUseIMEWindow);
		}
		else
		{
			CDirectDraw::Init(g_hWnd, SURFACE_WIDTH, SURFACE_HEIGHT, CDirectDraw::WINDOWMODE, true, g_bUseIMEWindow);
		}	
		
		//--------------------------------------------------------
		// Video Memory 얼마인가?
		//--------------------------------------------------------
		DDSCAPS2 ddsCaps2;
		DWORD dwTotal;
		DWORD dwFree;
		ZeroMemory(&ddsCaps2, sizeof(ddsCaps2)); 
		ddsCaps2.dwCaps = DDSCAPS_VIDEOMEMORY;//DDSCAPS_TEXTURE; 
		HRESULT hr = CDirectDraw::GetDD()->GetAvailableVidMem(&ddsCaps2, &dwTotal, &dwFree);

		DEBUG_ADD_FORMAT("[VidemoMemory from GetAvailableVidMem()] Before Init Draw = %d/%d", dwFree, dwTotal);


		//--------------------------------------------------------
		// 이게 진짜다.. - -;
		//--------------------------------------------------------
		// 근데 .. 과연 이거라고 될려나..
		// i740에서 memory 60M쯤 나오는건 뭘까.. - -;;
		DDCAPS	driverCaps;
		ZeroMemory( &driverCaps, sizeof(driverCaps) );
		driverCaps.dwSize = sizeof(driverCaps);
		
		hr = CDirectDraw::GetDD()->GetCaps( &driverCaps, NULL );
		if (hr!=DD_OK)
		{	
			InitFail("[Error] GetCaps to Get VidMem");
			return FALSE;
		}
		
		#ifdef	OUTPUT_DEBUG
			if (driverCaps.dwCaps2 & DDCAPS2_NONLOCALVIDMEMCAPS)
			{			
				DEBUG_ADD_FORMAT("DDCAPS2_NONLOCALVIDMEMCAPS Enable");		
			}
			else
			{
				DEBUG_ADD_FORMAT("DDCAPS2_NONLOCALVIDMEMCAPS Disable");
			}
		#endif	

		dwTotal = driverCaps.dwVidMemTotal;
		dwFree = driverCaps.dwVidMemFree;

		DEBUG_ADD_FORMAT("[VidemoMemory from GetDDCaps()] Before Init Draw = %d/%d", dwFree, dwTotal);

		DEBUG_ADD("[ InitGame ]  Init Draw OK");

		BOOL enoughMemory = TRUE;

		//--------------------------------------------------------
		// 8M 이상 남아있는 경우만 3D 가속한다.. 흠.. - -;;
		//--------------------------------------------------------
		if (dwFree < 8388608)
		{
			enoughMemory = FALSE;
		}

		//--------------------------------------------------------
		// 하드웨어 가속 사용 가능
		//--------------------------------------------------------
		bool bUse3D = ( enoughMemory && g_bHAL && ( CDirect3D::CheckHAL() ));
		
		if (bUse3D)
		{		
			DEBUG_ADD("[ InitGame ]  Init 3D");

			if (CDirect3D::Init())
			{			
				g_bEnable3DHAL = TRUE;


				D3DDEVICEDESC7 devDesc;
				
				CDirect3D::GetDevice()->GetCaps( &devDesc );

				#ifdef	OUTPUT_DEBUG
					if (devDesc.dwDevCaps & D3DDEVCAPS_TEXTURENONLOCALVIDMEM)
					{				
						DEBUG_ADD_FORMAT("D3DDEVCAPS_TEXTURENONLOCALVIDMEM Enable");
					}
					else
					{
						DEBUG_ADD_FORMAT("D3DDEVCAPS_TEXTURENONLOCALVIDMEM Disable");
					}
				#endif
			}
			else
			{
				bUse3D = false;
			}
			g_bHALAvailable = true;
		}
		
		//--------------------------------------------------------
		// 하드웨어 가속 사용 불가능
		//--------------------------------------------------------
		if (!bUse3D)
		{
			DEBUG_ADD("[ InitGame ]  3D Failed. Release Draw and Re-Init 2D");

			CDirectDraw::ReleaseAll();

			if (g_bFullScreen)
			{
				CDirectDraw::Init(g_hWnd, SURFACE_WIDTH, SURFACE_HEIGHT, CDirectDraw::FULLSCREEN, false, g_bUseIMEWindow);
			}
			else
			{
				CDirectDraw::Init(g_hWnd, SURFACE_WIDTH, SURFACE_HEIGHT, CDirectDraw::WINDOWMODE, false, g_bUseIMEWindow);
			}

			g_bEnable3DHAL = FALSE;
		}	
	}
	//--------------------------------------------------------
	//
	// 무조건 3D가속 안 할때
	//
	//--------------------------------------------------------
	else
	{
		DEBUG_ADD("[ InitGame ]  Init 2D");
		
		if (g_bFullScreen)
		{
			CDirectDraw::Init(g_hWnd, SURFACE_WIDTH, SURFACE_HEIGHT, CDirectDraw::FULLSCREEN, false, g_bUseIMEWindow);
		}
		else
		{
			CDirectDraw::Init(g_hWnd, SURFACE_WIDTH, SURFACE_HEIGHT, CDirectDraw::WINDOWMODE, false, g_bUseIMEWindow);
		}		
	}

	CSpriteSurface::InitEffectTable();

	CDirectDrawSurface::SetGammaFunction();

	return TRUE;
}

// -----------------------------------------------------------------------------
// LoadingThreadProc
// -----------------------------------------------------------------------------
// LONG
// LoadingThreadProc(LPVOID lpParameter)
// {
// 	if (g_pLoadingThread!=NULL)
// 	{
// 		g_pLoadingThread->Execute();
// 	}
// 
// 	return 0L;
// }

//-----------------------------------------------------------------------------
// Init Thread
//-----------------------------------------------------------------------------
BOOL
InitThread()
{
	// Debug Message
	DEBUG_ADD("[ InitGame ]  Thread");

	/*
	DWORD	dwChildThreadID;

	// init event for nonsignaled
	g_hFileEvent = CreateEvent(NULL, TRUE, FALSE, NULL);	

	g_hFileThread = CreateThread(NULL, 
								0,	// default stack size
								(LPTHREAD_START_ROUTINE)FileThreadProc,
								NULL,
								NULL,
								&dwChildThreadID);

	SetThreadPriority(g_hFileThread, 
						//THREAD_PRIORITY_NORMAL
						THREAD_PRIORITY_BELOW_NORMAL
						);
	*/

// 	if (g_pLoadingThread!=NULL)
// 	{
// 		delete g_pLoadingThread;
// 	}
// 
// 	g_pLoadingThread = new MWorkThread;
// 	g_pLoadingThread->Init(THREAD_PRIORITY_LOWEST);

	// Work Thread 초기화
	//MWorkThreadGlobal::Instance()->InitThread();

	return TRUE;
}

//---------------------------------------------------------------------------
// Stop LoadingThread
//---------------------------------------------------------------------------
// void
// StopLoadingThread()
// {
// 	//-------------------------------------------------------------
// 	// Loading 중이던것 모두 제거
// 	//-------------------------------------------------------------
// 	if (g_pLoadingThread!=NULL)
// 	{
// 		DEBUG_ADD_FORMAT("Thread-ReleaseWork: size=%d, working=%d, finish=%d, stop=%d", 
// 									g_pLoadingThread->GetSize(),
// 									(int)g_pLoadingThread->IsWorking(),
// 									(int)g_pLoadingThread->IsFinishCurrentWork(),
// 									(int)g_pLoadingThread->IsStopWork());
// 		
// 		g_pLoadingThread->SetPriority( THREAD_PRIORITY_HIGHEST );
// 		g_pLoadingThread->ReleaseWork();
// 		g_pLoadingThread->SetPriority( THREAD_PRIORITY_LOWEST );
// 
// 		//-------------------------------------------------------------
// 		// 작업 중지가 끝날때까지 기다림
// 		//-------------------------------------------------------------
// 		DEBUG_ADD_FORMAT("Thread-WaitingForStop: size=%d, working=%d, finish=%d, stop=%d", 
// 									g_pLoadingThread->GetSize(),
// 									(int)g_pLoadingThread->IsWorking(),
// 									(int)g_pLoadingThread->IsFinishCurrentWork(),
// 									(int)g_pLoadingThread->IsStopWork());
// 		
// 		while (g_pLoadingThread->IsStopWork());
// 
// 		DEBUG_ADD("Thread-End Waiting");
// 	}
// }

//---------------------------------------------------------------------------
// update loop의 정보를 설정한다.
//---------------------------------------------------------------------------
BOOL
InitGameUpdate()
{
	if (g_pCOpeningUpdate!=NULL)
	{
		delete	g_pCOpeningUpdate;
	}

	if (g_pCGameUpdate!=NULL)
	{
		delete	g_pCGameUpdate;
	}

	if (g_pCWaitPacketUpdate!=NULL)
	{
		delete	g_pCWaitPacketUpdate;
	}

	if (g_pCWaitUIUpdate!=NULL)
	{
		delete	g_pCWaitUIUpdate;
	}

	g_pCOpeningUpdate		= new COpeningUpdate;
	g_pCGameUpdate			= new CGameUpdate;
	g_pCWaitPacketUpdate	= new CWaitPacketUpdate;
	g_pCWaitUIUpdate		= new CWaitUIUpdate;

	return TRUE;
}

//---------------------------------------------------------------------------
// Surface의 정보를 생성한다.
//---------------------------------------------------------------------------
BOOL
InitGame()
{	

	//---------------------------------------------------------------------
	// Profiler
	//---------------------------------------------------------------------
	#ifdef OUTPUT_DEBUG
		if (g_pProfiler!=NULL) 
		{ 
			g_pProfiler->Release(); 
		} 
		else 
		{ 
			g_pProfiler = new Profiler; 
		}
	#endif

	//---------------------------------------------------------------------
	// MathTable
	//---------------------------------------------------------------------
	MathTable::FCreateSines();

	//---------------------------------------------------------------------
	// Effect Orbit Table
	//---------------------------------------------------------------------
	MAttachOrbitEffect::InitOrbitPosition();

	//---------------------------------------------------------------------
	// Init 
	//---------------------------------------------------------------------
	if (g_pGameStringTable==NULL)
	{
		g_pGameStringTable = new MStringArray;
	}

	if (g_pSystemMessage==NULL)
	{
		g_pSystemMessage = new CMessageArray;
	}

	if (g_pGameMessage==NULL)
	{
		g_pGameMessage = new CMessageArray;
	}

	if (g_pHelpMessage==NULL)
	{
		g_pHelpMessage = new CMessageArray;
	}
	
	if (g_pNoticeMessage == NULL )
	{
		g_pNoticeMessage = new CMessageArray;
	}
// 2008.07.17 zzi
	if (g_pGMMessage == NULL )
	{
		g_pGMMessage = new CMessageArray;
	}
#if __CONTENTS(__WORLDCHATING)
	if(g_pWorldChatingMessage == NULL)
	{
		g_pWorldChatingMessage = new CMessageArray;
	}

#endif //g_pWorldChatingMessage
	if (g_pEventMessage == NULL )
	{
		g_pEventMessage  = new CMessageArray;
	}

	if ( g_pInfomationBord == NULL )
	{
		g_pInfomationBord = new CInfomationBord;
	}
//-
	// 2004, 6, 18 sobeit add start - nick name table 
	if (g_pNickNameStringTable==NULL)
	{
		g_pNickNameStringTable = new MStringArray;
	}
	//---------------------------------------------------------------------
	// nick name string table Loading
	//---------------------------------------------------------------------
	ivfstream gameStringTableTable;//(FILE_INFO_gameStringTable, ios::binary);
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_INFO_NICKNAME_STRING").c_str(), gameStringTableTable))
		return FALSE;
	(*g_pNickNameStringTable).LoadFromFile_NickNameString(gameStringTableTable);
	gameStringTableTable.close();


	// 2004, 6, 18 sobeit add end - nick name table 
	//---------------------------------------------------------------------
	// GameStringTable Loading
	//---------------------------------------------------------------------
	ivfstream gameStringTableTable2;//(FILE_INFO_gameStringTable, ios::binary);
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_INFO_STRING").c_str(), gameStringTableTable2))
		return FALSE;
	(*g_pGameStringTable).LoadFromFile(gameStringTableTable2);
	gameStringTableTable2.close();


	//---------------------------------------------------
	// System Message
	//---------------------------------------------------
	g_pSystemMessage->Init(MAX_SYSTEMMESSAGE, 256);

	g_pNoticeMessage->Init(7, 256);

	//---------------------------------------------------
	// Game Message
	//---------------------------------------------------
	g_pGameMessage->Init(MAX_GAMEMESSAGE, 256);

	//---------------------------------------------------
	// Help Message
	//---------------------------------------------------
	g_pHelpMessage->Init(MAX_HELPMESSAGE, 256);
	
	//---------------------------------------------------
	// GM & Special Message - 2008.07.17 zzi
	//---------------------------------------------------
	g_pGMMessage->Init(MAX_GMMESSAGE, 256);
	g_pEventMessage->Init(MAX_EVENTMESSAGE, 256);
	g_pEventMessage->BeginUpdateTimer(5000);
//	g_pPlayerMessage->Init(MAX_PLAYERMESSAGE, 256);
#if __CONTENTS(__WORLDCHATING)
	g_pWorldChatingMessage->Init(MAX_GMMESSAGE, 256);
#endif //__WORLDCHATING

	// Debug Message
	DEBUG_ADD("---------------[   InitGame   ]---------------");

	//----------------------------------------------------------------------
	// WSA Startup
	//----------------------------------------------------------------------
	DEBUG_ADD("[ InitGame ]  Socket - Before WSAStartup");

	WORD wVersionRequested;
	WSADATA wsaData;	
  
	wVersionRequested = MAKEWORD( 2, 0 );
 
	if (WSAStartup( wVersionRequested, &wsaData ) != 0)	
	{
	    // Tell the user that we couldn't find a useable
	    // WinSock DLL.                                 
	    MessageBox( g_hWnd, "couldn't find a useable WinSock DLL.", NULL, MB_OK);
		return FALSE;
	}

//	#ifdef _DEBUG
//		bool bMerge = false;
//
//		if (bMerge)
//		{
//			MGuildMarkManager::MergeGuildMark( FILE_SPRITE_GUILD_MARK, 
//												FILE_INFO_GUILD_INFO_MAPPER,
//												"data\\GuildMark.spk",
//												"data\\GuildMark.inf");
//		}
//	#endif

	//--------------------------------------------------------
	//
	//                 Init...
	//
	//--------------------------------------------------------
	if (InitClientConfig() &&
		InitInfomation() &&
		InitUserOption() &&

		InitVolume() &&
		InitInput() &&	
		//InitSound()  &&
		InitDraw() &&
		
		InitThread() &&		// 2001.8.20 주석처리 - 로딩 Thread사용 안함 // 2007.06.09 다시 사용함
		InitSurface() &&
		
		InitGameObject() &&

		InitGameUpdate()
		)		
	{	
		UI_AffectUserOption();
		//----------------------------------------
		// guild 마크 생성부분
		//----------------------------------------
		/*
		#ifdef _DEBUG
			g_pGuildMarkManager->CreateGuildMark( 1, "Data\\Guild\\Guild1.bmp" );
			g_pGuildMarkManager->CreateGuildMark( 2, "Data\\Guild\\Guild2.bmp" );
			g_pGuildMarkManager->CreateGuildMark( 3, "Data\\Guild\\Guild3.bmp" );
			g_pGuildMarkManager->CreateGuildMark( 4, "Data\\Guild\\Guild4.bmp" );
			g_pGuildMarkManager->CreateGuildMark( 5, "Data\\Guild\\Guild5.bmp" );
			g_pGuildMarkManager->CreateGuildMark( 6, "Data\\Guild\\Guild6.bmp" );
			g_pGuildMarkManager->CreateGuildMark( 7, "Data\\Guild\\Guild7.bmp" );
		#endif
		*/
		
		/*
		#if defined(_DEBUG) && defined(OUTPUT_DEBUG)
			std::ifstream guildInfoFile2(FILE_INFO_GUILD_INFO_MAPPER, ios::binary | ios::nocreate);	

			if (!guildInfoFile2.is_open())
			{
				struct MAKE_GUILD_INFO
				{
					WORD	guildID;
					char	guildName[80];
				};

				const int numGuild = 20;
				MAKE_GUILD_INFO guildInfo[numGuild] =
				{
					{ 1, "테페즈" },
					{ 2, "바토리" },
					{ 100, "E.V.E" },
					{ 101, "귀천검" },
					{ 102, "다덴마스터" },
					{ 103, "레드블러드" },
					{ 104, "바이러스" },
					{ 105, "뱀파이어키퍼즈" },
					{ 106, "버피즈" },
					{ 107, "블러드레인" },
					{ 108, "소년미소녀" },
					{ 109, "십자군" },
					{ 110, "엘카" },
					{ 111, "지존" },
					{ 112, "키퍼즈" },
					{ 113, "태극" },
					{ 114, "특전사" },
					{ 115, "패밀리" },
					{ 116, "퍼펙트" },
					{ 117, "데카" }
				};


				char guildMarkFilename[256];

				for (int g=0; g<numGuild; g++)
				{
					WORD		guildID		= guildInfo[g].guildID;
					const char* guildName	= guildInfo[g].guildName;

					GUILD_INFO* pInfo = new GUILD_INFO;
					pInfo->SetGuildName( guildName );
					
					g_pGuildInfoMapper->Set( guildID, pInfo );

					// 길드 마크 생성. "길드이름.bmp"
					sprintf(guildMarkFilename, "Data\\Guild\\%s.bmp", guildName);
					g_pGuildMarkManager->CreateGuildMark( guildID, guildMarkFilename );
				}

				// g_pGuildInfoMapper 저장
				std::ofstream guildInfoFile(FILE_INFO_GUILD_INFO_MAPPER, ios::binary);	
				g_pGuildInfoMapper->SaveToFile(guildInfoFile);
				guildInfoFile.close();
				
				g_pGuildInfoMapper->SaveInfoToFile("GuildList.txt");
			}
			else
			{
				guildInfoFile2.close();
			}
		#endif
		*/

		//----------------------------------------
		// 내 profile 초기화
		//----------------------------------------
		ProfileManager::DeleteProfiles();		// 기존에거 모두 제거
		ProfileManager::InitProfiles();			// profile 생성


			//----------------------------------------
			// Player 캐릭터 그림 Load
			//----------------------------------------
			//UI_DrawProgress(70);

			//LoadCreature( 0 );
			//UI_DrawProgress(80);

			//LoadCreature( 1 );
			//UI_DrawProgress(90);

			//LoadCreature( 2 );
			//UI_DrawProgress(95);

			//LoadCreature( 3 );
			//UI_DrawProgress(100);
		
			//gC_vs_ui.EndProgress();

			// Login Mode로 시작한다.
			//SetMode( MODE_OPENING );		
			SetMode( MODE_MAINMENU );	
			//SetMode( MODE_WAIT_POSITION );
		///*
		// Server에 접속이 안될 때 사용하는 code
		//*/

		// Debug Message
		#ifdef	OUTPUT_DEBUG			
			// Fullscreen?
			if (CDirectDraw::IsFullscreen())	
			{
				DEBUG_ADD("# Fullscreen.");
			}
			else
			{
				DEBUG_ADD("# Windowed Mode.");
			}

			// 565?
			if (CDirectDraw::Is565())	
			{
				DEBUG_ADD("# 5:6:5 mode");
			}
			else
			{
				DEBUG_ADD("# 5:5:5 mode or ???.");
			}

			// 3D HAL?
			if (CDirect3D::IsHAL())	
			{
				DEBUG_ADD("# 3D Hardware Accel.");
			}
			
			DEBUG_ADD("---------------[  InitGame OK  ]---------------");
		#endif
	
		return TRUE;
	}

	// Init가 실패한 경우
	return FALSE;	
}

//-----------------------------------------------------------------------------
// Init Socket
//-----------------------------------------------------------------------------
BOOL
InitSocket()
{
 

	// 일단 release
	ReleaseSocket();

	// Debug Message
	DEBUG_ADD("[ InitGame ]  Socket");


	//----------------------------------------------------------------------
	// 환경 파일을 읽어들인다.
	// 실행 파일은 $VSHOME/bin에, 환경 파일은 $VSHOME/conf 에 존재해야 한다.?	// command line 에서 환경 파일을 지정할 수 있도록 한다.
	//----------------------------------------------------------------------

	try {
		DEBUG_ADD("[ InitGame ]  Socket - Before new Properties");

		std::string configFilename;

		if( !g_pUserInformation->bKorean )
		{
			configFilename = g_pFileDef->getProperty("FILE_INFO_GAMECLIENT").c_str();
			//g_pConfigForeign = new ServerInfoFileParser( configFilename );
			g_pConfigForeign = new Properties();
			g_pConfigForeign->load(configFilename);
		}
		else
		{
			switch(g_Dimension)
			{
				//		case 0:
				//			configFilename = FILE_INFO_GAMECLIENT;
				//			break;
				
			case 1:
				configFilename = g_pFileDef->getProperty("FILE_INFO_GAMECLIENT2").c_str();
				break;
				
			default:
				configFilename = g_pFileDef->getProperty("FILE_INFO_GAMECLIENT").c_str();
				break;
			}
			
			g_pConfigKorean = new Properties();
			g_pConfigKorean->load(configFilename);			
		}

	} catch ( Throwable& t ) 	
	{
		//InitFail(t.toString().c_str());				

		DEBUG_ADD_ERR(t.toString().c_str());

		SetMode( MODE_MAINMENU );
		UpdateDisconnected();


		return FALSE;
	}	

	//----------------------------------------------------------------------
	// Create Socket 
	//----------------------------------------------------------------------
	Socket * pSocket = NULL;
	try {		
		DEBUG_ADD("[ InitGame ]  Socket - Before new PacketFactoryManager");

		// 패킷 팩토리 매니저를 생성, 초기화한다. 
		g_pPacketFactoryManager = new PacketFactoryManager();

		DEBUG_ADD("[ InitGame ]  Socket - Before new PacketValidator");

		g_pPacketValidator = new PacketValidator();

		DEBUG_ADD("[ InitGame ]  Socket - Before Init...");

		g_pPacketFactoryManager->init();
		g_pPacketValidator->init();
		
		DEBUG_ADD("[ InitGame ]  Socket - Before new Socket...");

		//---------------------------------------------------------
		// Address 골라서 접속하기
		//---------------------------------------------------------
		int maxAddress = 1;

		try {
			if( g_pUserInformation->bKorean )
				maxAddress = atoi(g_pConfigKorean->getProperty("MaxLoginServerAddress").c_str());
			else
				maxAddress = atoi( g_pConfigForeign->getProperty("MaxLoginServerAddress").c_str() );
		} catch (NoSuchElementException) {
			//maxAddress = 1;
		}

		// 최근에 접속시도를 했던 서버 주소 번호..
		static int previousTryServer = 0;
		
			
		//for (int i=0; i<maxAddress; i++)
		{
			// 여러 login 서버 중의 한 군데로 접속한다.
			// 순서대로..
			int i = previousTryServer % maxAddress;

			try {				
				std::string serverAddressString;
				serverAddressString = "LoginServerAddress";
				
				// [Futec수정]
				uint port;
				if( g_pUserInformation->bKorean )
					port = g_pConfigKorean->getPropertyInt("LoginServerPort");
				else
					port = g_pConfigForeign->getPropertyInt("LoginServerPort");


				// 소켓을 생성하고 업데이트 서버에 연결한다.
				std::string ServerAddress;				
				if (g_FutecPort==0)
				{				
					if (i!=0)
					{
						char str[10];
						sprintf(str, "%d", i);
						serverAddressString += str;
					}
					
					if( g_pUserInformation->bKorean )
						ServerAddress = g_pConfigKorean->getProperty(serverAddressString);
					else
						ServerAddress = g_pConfigForeign->getProperty(serverAddressString);

					// LoginServer의 port를 임의로 선택한다.
					try {
						int portNum;
						if( g_pUserInformation->bKorean )
							portNum = g_pConfigKorean->getPropertyInt("LoginServerPortNum");
						else
							portNum = g_pConfigForeign->getPropertyInt("LoginServerPortNum");
						
						// port 고르기
						if (portNum>1)
						{
							if( g_pUserInformation->bKorean )
								port = g_pConfigKorean->getPropertyInt("LoginServerBasePort") + rand()%portNum;
							else
								port = g_pConfigForeign->getPropertyInt("LoginServerBasePort") + rand()%portNum;
						}
					} catch (NoSuchElementException&) {
					}
				}
				// Futec으로 접속
				else
				{
					ServerAddress = g_FutecIP;
					port = g_FutecPort;
				}

				// domain으로 된 주소인 경우..
				if (ServerAddress[0] < '0' || ServerAddress[0] > '9')
				{
					struct hostent* h;

					if ((h=gethostbyname(ServerAddress.c_str()))==NULL)
					{
						// -_-;
						throw ConnectException("LoginServer의 주소를 찾을 수 없습니다.");
					}

					char* pIP = (char*)inet_ntoa(*((struct in_addr*)h->h_addr));

					ServerAddress = pIP;
				}
				
				DEBUG_ADD_FORMAT("Conneting( %s : %d )", ServerAddress.c_str() , port);
				pSocket = new Socket( ServerAddress , port );

				DEBUG_ADD("[ InitGame ]  Socket - Before connect");

				// try to connect to server
				pSocket->connect();

//				SOCKADDR_IN sa;
//				int lenSA = sizeof(sa);
//				getsockname( pSocket->getSOCKET(), (sockaddr*)&sa, &lenSA );
//				char str[128];
//				sprintf(str, inet_ntoa(sa.sin_addr));	// str : 내IP

				// connect가 된 경우..
				//break;

			} catch ( ConnectException ) {

				if (pSocket!=NULL)
				{
					delete pSocket;
					pSocket = NULL;
				}

				// 실패했으니까 다음 주소로..
				previousTryServer ++;

				// 마지막 주소인 경우에만 끝이다.
				//if (i==maxAddress-1)
				throw;
			}
		}


		// make nonblocking socket
	    pSocket->setNonBlocking();

		// make no-linger socket
		pSocket->setLinger(0);

		DEBUG_ADD("[ InitGame ]  Socket - new ClientPlayer");

	    // create player
		g_pSocket = new ClientPlayer(pSocket);
		pSocket = NULL;
	 
	} catch ( Throwable & t ) {	
		//MessageBox( g_hWnd, t.toString().c_str(), NULL, MB_OK );
		//InitFail(t.toString().c_str());
		DEBUG_ADD(t.toString().c_str());

		if (pSocket!=NULL)
		{
			delete pSocket;
		}

		SetMode( MODE_MAINMENU );		
		UpdateDisconnected();


		return FALSE;
	}

	//----------------------------------------------------------------------
	// RequestServerPlayerManager
	//----------------------------------------------------------------------
	if (g_pProfileManager!=NULL)
	{
		g_pProfileManager->ReleaseRequire();
	}

	if (g_pRequestServerPlayerManager!=NULL)
	{
		DEBUG_ADD("[ InitGame ]  delete RequestServerPlayerManager");
		delete g_pRequestServerPlayerManager;
	}

	if (g_pRequestClientPlayerManager!=NULL)
	{
		DEBUG_ADD("[ InitGame ]  delete RequestClientPlayerManager");
		delete g_pRequestClientPlayerManager;
	}

	if (g_pClientCommunicationManager!=NULL)
	{
		DEBUG_ADD("[ InitGame ]  delete ClientCommunicationManager");
		delete g_pClientCommunicationManager;
	}

	if (g_pRequestUserManager!=NULL)
	{
		DEBUG_ADD("[ InitGame ]  delete g_pRequestUserManager");
		delete g_pRequestUserManager;		
	}

	if (g_pWhisperManager!=NULL)
	{
		DEBUG_ADD("[ InitGame ]  delete g_pWhisperManager");
		delete g_pWhisperManager;		
	}

	if (g_pRequestFileManager!=NULL)
	{
		DEBUG_ADD("[ InitGame ]  delete g_pRequestFileManager");
		delete g_pRequestFileManager;		
	}
	

	DEBUG_ADD("[ InitGame ] new ClientCommunicationManager");
	g_pClientCommunicationManager = new ClientCommunicationManager;

	#ifdef __METROTECH_TEST__
		g_UDPTest.Init();
	#endif
	
	if (g_pClientConfig->MAX_REQUEST_SERVICE > 0)
	{
		DEBUG_ADD("[ InitGame ] new RequestServerPlayerManager");
		g_pRequestServerPlayerManager = new RequestServerPlayerManager;

		DEBUG_ADD("[ InitGame ] new RequestClientPlayerManager");
		g_pRequestClientPlayerManager = new RequestClientPlayerManager;

		DEBUG_ADD("[ InitGame ] RequestServerPlayerManager Init");
		g_pRequestServerPlayerManager->Init();
	}


	DEBUG_ADD("[ InitGame ] new g_pRequestUserManager");
	g_pRequestUserManager = new RequestUserManager;

	DEBUG_ADD("[ InitGame ] new g_pWhisperManager");
	g_pWhisperManager = new WhisperManager;

	DEBUG_ADD("[ InitGame ] new g_pRequestFileManager");
	g_pRequestFileManager = new RequestFileManager;



	DEBUG_ADD("[ InitGame ]  Socket OK");

	return TRUE;
}


//-----------------------------------------------------------------------------
// ReleaseGameUpdate()
//-----------------------------------------------------------------------------
void
ReleaseGameUpdate()
{
	if (g_pCOpeningUpdate!=NULL)
	{
		delete	g_pCOpeningUpdate;
		g_pCOpeningUpdate = NULL;
	}

	if (g_pCGameUpdate!=NULL)
	{
		delete	g_pCGameUpdate;
		g_pCGameUpdate = NULL;
	}

	if (g_pCWaitPacketUpdate!=NULL)
	{
		delete	g_pCWaitPacketUpdate;
		g_pCWaitPacketUpdate = NULL;
	}

	if (g_pCWaitUIUpdate!=NULL)
	{
		delete	g_pCWaitUIUpdate;
		g_pCWaitUIUpdate = NULL;
	}

}

void ReleaseAllObjects()
{

	g_bActiveGame = false;

	EndTitleLoading();

	//ReleaseGameUpdate();


	//if (g_pUIDialog!=NULL)
	//{
	//	DEBUG_ADD("[Release] UI Dialog");
	//	g_pUIDialog->Release();
	//}

	DEBUG_ADD("[Release] UI");
	gC_vs_ui.Release();

	TerminateProcess( GetCurrentProcess(), 0 );
}
//-----------------------------------------------------------------------------
// Name: ReleaseAllObjects()
// Desc: Finished with all objects we use; release them
//-----------------------------------------------------------------------------
/*void ReleaseAllObjects()
{
	DEBUG_ADD("---------------[ Start ReleaseAllObjects ]---------------");

	DEBUG_ADD("[Release] Work Thread");



	g_bActiveGame = false;

	EndTitleLoading();
	
	ReleaseGameUpdate();


#ifndef __USE_MP3__
	BGMManager::Instance()->Destory();
#endif
	ReleasePacketItemTable();

	if (g_pUIDialog!=NULL)
	{
		DEBUG_ADD("[Release] UI Dialog");
		g_pUIDialog->Release();
	}

	DEBUG_ADD("[Release] UI");
	gC_vs_ui.Release();

	DEBUG_ADD("[Release] Weather");
	if (g_pWeather!=NULL)
	{
		delete g_pWeather;
		g_pWeather = NULL;
	}
	DEBUG_ADD("[Release] Inventory Effect Manager");
	if (g_pInventoryEffectManager != NULL)
	{
		delete g_pInventoryEffectManager;
		g_pInventoryEffectManager = NULL;
	}
	DEBUG_ADD("[Release] g_pPlayer");
	if (g_pPlayer!=NULL)
	{
		if (g_pZone!=NULL)
		{
			g_pZone->RemoveCreature( g_pPlayer->GetID() );
		}
		SAFE_DELETE( g_pPlayer );		
	}

	DEBUG_ADD("[Release] Zone");
	SAFE_DELETE( g_pZoneSmall );
	SAFE_DELETE( g_pZoneLarge );
	g_pZone = NULL;
	
	DEBUG_ADD("[Release] MCreature::MoveTable");
	MCreature::ReleaseMoveTable();

	
	DEBUG_ADD("[Release] DirectInput");

	SAFE_DELETE( g_pDXInput );

	DEBUG_ADD("[Release] Music");
	g_Music.Stop();
	g_Music.UnInit();

	DEBUG_ADD("[Release] MP3");
	SAFE_DELETE( g_pMP3 );	
	DEBUG_ADD("[Release] ZoneSound");


	SAFE_DELETE( g_pZoneSoundTable );
	SAFE_DELETE( g_pZoneSoundManager );
	SAFE_DELETE( g_pWavePackFileManager );
	
	DEBUG_ADD("[Release] Sound");

	UnInitSound();

	DEBUG_ADD("[Release] AVI");

	if (g_pAvi!=NULL)
	{
		g_pAvi->Close();
		delete g_pAvi;
		g_pAvi = NULL;
	}

	DEBUG_ADD("[Release] MTopView");
	
	if (g_pTopView!=NULL)
	{
		{
			g_pTopView->Release();
			delete g_pTopView;
		}

		g_pTopView = NULL;
	}
	DEBUG_ADD("[Release] g_pCursorSurface");
	SAFE_DELETE(g_pCursorSurface );

	DEBUG_ADD("[Release] Back Surface");
	SAFE_DELETE( g_pBack );
	
	DEBUG_ADD("[Release] Last Surface");
	SAFE_DELETE( g_pLast );
	
	DEBUG_ADD("[Release] Socket");
	ReleaseSocket();

	WSACleanup();	

	DEBUG_ADD("[Release] Volume");
	if (g_pWaveVolume!=NULL)
	{
		g_pWaveVolume->SetCurrentVolume( g_WaveVolumeOriginal );
		g_pWaveVolume->Done();

		delete g_pWaveVolume;
		g_pWaveVolume = NULL;
	}

	if (g_pMasterVolume!=NULL)
	{
		g_pMasterVolume->SetCurrentVolume( g_MasterVolumeOriginal );
		g_pMasterVolume->Done();

		delete g_pMasterVolume;
		g_pMasterVolume = NULL;
	}

	{
		if (g_pActionInfoTable) g_pActionInfoTable->Release();	
		if (g_pCreatureSpriteTable!=NULL) g_pCreatureSpriteTable->Release();
		if (g_pCreatureTable) g_pCreatureTable->Release();
		if (g_pCreatureSpriteTypeMapper) g_pCreatureSpriteTypeMapper->Release();
		if (g_pEffectSpriteTypeTable) g_pEffectSpriteTypeTable->Release();
		if (g_pActionEffectSpriteTypeTable) g_pActionEffectSpriteTypeTable->Release();
		if (g_pEffectStatusTable) g_pEffectStatusTable->Release();
		if (g_pGameMessage!=NULL) g_pGameMessage->Release();
		if (g_pGameStringTable) g_pGameStringTable->Release();
		if (g_pInteractionObjectTable) g_pInteractionObjectTable->Release();
		if (g_pItemOptionTable) g_pItemOptionTable->Release();
		if (g_pNPCTable) g_pNPCTable->Release();
		if (g_pNPCTalkBox) g_pNPCTalkBox->Release();
		if (g_pPCTalkBox) g_pPCTalkBox->Release();
		if (g_pShopTemplateTable) g_pShopTemplateTable->Release();
		if (g_pSkillAvailable) g_pSkillAvailable->clear();
		if (g_pSkillInfoTable) g_pSkillInfoTable->Release();
		if (g_pSkillManager) g_pSkillManager->Release();
		if (g_pSlayerGear) g_pSlayerGear->Release();
		if (g_pVampireGear) g_pVampireGear->Release();
		if (g_pOustersGear) g_pOustersGear->Release();
		if (g_pInventory) g_pInventory->Release();
		if (g_pSoundManager) g_pSoundManager->Release();
		if (g_pSoundTable) g_pSoundTable->Release();
		if (g_pSystemMessage) g_pSystemMessage->Release();	
		if (g_pUsingColorSetTable) g_pUsingColorSetTable->Release();
		if (g_pZoneTable) g_pZoneTable->Release();
		if (g_pZoneSoundManager) g_pZoneSoundManager->Release();
		if (g_pNPCScriptTable) g_pNPCScriptTable->Release();
		if (g_pNickNameStringTable!=NULL) g_pNickNameStringTable->Release();
		if (g_pGMMessage) g_pGMMessage->Release ();
		if (g_pEventMessage) g_pEventMessage->Release ();
#if __CONTENTS(__WORLDCHATING)
		if (g_pWorldChatingMessage) g_pWorldChatingMessage->Release();
#endif
	}
	TerminateProcess( GetCurrentProcess(), 0 );
	SAFE_DELETE( g_pRegenTowerInfoManager );
	SAFE_DELETE( g_pSystemAvailableManager );
	SAFE_DELETE( g_pWorldPlayerConfigTable );
	SAFE_DELETE( g_pServerInformation );
	SAFE_DELETE( g_pUserInformation );
	SAFE_DELETE( g_pTempInformation );
	SAFE_DELETE( g_pGameMessage );
	SAFE_DELETE( g_pHelpMessage );
	SAFE_DELETE( g_pNoticeMessage );
	SAFE_DELETE( g_pSystemMessage );
	SAFE_DELETE( g_pGameStringTable );
	SAFE_DELETE( g_pClientConfig );
	SAFE_DELETE( g_pUserOption );
	SAFE_DELETE( g_pOperatorOption );
	SAFE_DELETE( g_pUIDialog );
	SAFE_DELETE( g_pProfileManager );
	SAFE_DELETE( g_pGuildMarkManager );
	SAFE_DELETE( g_pGuildInfoMapper );
	SAFE_DELETE( g_pEventManager );
	SAFE_DELETE( g_pEffectSpriteTypeTable );
	SAFE_DELETE( g_pActionEffectSpriteTypeTable );
	SAFE_DELETE( g_pCreatureTable );
	SAFE_DELETE( g_pCreatureSpriteTypeMapper );
	SAFE_DELETE( g_pItemTable );
	SAFE_DELETE( g_pCreatureSpriteTable );
	SAFE_DELETE( g_pEffectStatusTable );
	SAFE_DELETE( g_pInteractionObjectTable );
	SAFE_DELETE( g_pItemOptionTable );
	SAFE_DELETE( g_pNPCTable );
	SAFE_DELETE( g_pJusticeAttackManager );
	SAFE_DELETE( g_pNPCScriptTable );	
	SAFE_DELETE( g_pShopTemplateTable );
#if __CONTENTS(__GPS_ADD)
	SAFE_DELETE( g_pGpsInfoTable );
#endif
	SAFE_DELETE( g_pSkillInfoTable );
	SAFE_DELETE( g_pRankBonusTable );
	SAFE_DELETE( g_pExperienceTable );
	SAFE_DELETE( g_pSoundTable );
	SAFE_DELETE( g_pMusicTable );
	SAFE_DELETE( g_pZoneTable );
	SAFE_DELETE( g_pLevelNameTable );
	SAFE_DELETE( g_pQuestInfoManager );
	SAFE_DELETE( g_pSoundManager );
	SAFE_DELETE( g_pSkillAvailable );
	SAFE_DELETE( g_pSkillManager );
	SAFE_DELETE( g_pSlayerGear );
	SAFE_DELETE( g_pVampireGear );
	SAFE_DELETE( g_pOustersGear );

	SAFE_DELETE( g_pSlayerGearOther );
	SAFE_DELETE( g_pVampireGearOther );
	SAFE_DELETE( g_pOustersGearOther );

	SAFE_DELETE( g_pMilitarySlot );
 
	SAFE_DELETE( g_pInventory );
	SAFE_DELETE( g_pParty );
	SAFE_DELETE( g_pTradeManager );	
	SAFE_DELETE( g_pStorage );
	SAFE_DELETE( g_pStorage2 );
	SAFE_DELETE( g_pGameTime );
	SAFE_DELETE( g_pKeyAccelerator );
	SAFE_DELETE( g_pAcceleratorManager );
	SAFE_DELETE( g_pModifyStatusManager );
	SAFE_DELETE( g_pEffectGeneratorTable );
	SAFE_DELETE( g_pUsingColorSetTable );
	SAFE_DELETE( g_pActionInfoTable );
	SAFE_DELETE( g_pPriceManager );
	SAFE_DELETE( g_pMoneyManager );
	SAFE_DELETE( g_pPCTalkBox );
	SAFE_DELETE( g_pNPCTalkBox );
	SAFE_DELETE( g_pChatManager );	
	SAFE_DELETE( g_pHelpManager );
	SAFE_DELETE( g_pHelpStringTable );	

	SAFE_DELETE( g_pCompareManager );

	SAFE_DELETE( g_pHelpDisplayer );
	SAFE_DELETE( g_pObjectSelector );	
	SAFE_DELETE( g_pUIMessageManager );	
	SAFE_DELETE( g_pMonsterNameTable  );
	SAFE_DELETE( g_pQuestInfoManager  );
	SAFE_DELETE( g_pTimeItemManager  );	
	SAFE_DELETE( g_pFameInfoTable );
	SAFE_DELETE( g_pWarManager );

	SAFE_DELETE( g_pNickNameStringTable );

	SAFE_DELETE(g_pGMMessage);
	SAFE_DELETE(g_pInfomationBord);
	SAFE_DELETE(g_pEventMessage);

#if __CONTENTS(__PREMIUM_GIVE_ITEM_UI)	
	SAFE_DELETE(g_pPremiumGiveItemInfoList);
#endif
#if __CONTENTS(__WORLDCHATING)
	SAFE_DELETE(g_pWorldChatingMessage);
#endif

	DEBUG_ADD("[Release] CDirect3D");

	CDirect3D::Release();

	DEBUG_ADD("[Release] CDirectDraw");
	
	CDirectDraw::ReleaseAll();

	DEBUG_ADD("[Release] Profiler");
	SAFE_DELETE( g_pProfiler );	
	DEBUG_ADD("[Release] All OK");		

	SAFE_DELETE(g_pFileDef);
}	*/

//-----------------------------------------------------------------------------
// Release Socket
//-----------------------------------------------------------------------------
void
ReleaseSocket()
{
	//----------------------------------------------------------------
	//
	//							socket
	//
	//----------------------------------------------------------------
		DEBUG_ADD("----- Start ReleaseSocket -----");
		
		if (g_pSocket!=NULL) 
		{			
			//g_pSocket->setPlayerStatus( CPS_END_SESSION );

			g_pSocket->disconnect(UNDISCONNECTED);

			//g_pSocket->getSocket()->close();			
			DEBUG_ADD("delete g_pSocket");
			
			delete g_pSocket;
			g_pSocket = NULL;
		}

		SAFE_DELETE( g_pConfigKorean );		
		SAFE_DELETE( g_pConfigForeign );

		if (g_pPacketFactoryManager != NULL)
		{
			DEBUG_ADD("delete g_pPacketFactoryManager");
			
			delete g_pPacketFactoryManager;
			g_pPacketFactoryManager = NULL;
		}			

		if (g_pPacketValidator != NULL)
		{
			DEBUG_ADD("delete g_pPacketValidator");
			
			delete g_pPacketValidator;
			g_pPacketValidator = NULL;
		}		

		if (g_pProfileManager!=NULL)
		{
			g_pProfileManager->ReleaseRequire();
		}
		
		if (g_pRequestServerPlayerManager!=NULL)
		{
			DEBUG_ADD("delete g_pRequestServerPlayerManager");
			delete g_pRequestServerPlayerManager;
			g_pRequestServerPlayerManager = NULL;
		}

		if (g_pRequestClientPlayerManager!=NULL)
		{
			DEBUG_ADD("delete g_pRequestClientPlayerManager");
			delete g_pRequestClientPlayerManager;
			g_pRequestClientPlayerManager = NULL;
		}

		if (g_pClientCommunicationManager!=NULL)
		{
			DEBUG_ADD("delete g_pClientCommunicationManager");
			delete g_pClientCommunicationManager;
			g_pClientCommunicationManager = NULL;
		}

		if (g_pWhisperManager!=NULL)
		{
			DEBUG_ADD("delete g_pWhisperManager");
			delete g_pWhisperManager;
			g_pWhisperManager = NULL;
		}

		if (g_pRequestFileManager!=NULL)
		{
			DEBUG_ADD("delete g_pRequestFileManager");
			delete g_pRequestFileManager;
			g_pRequestFileManager = NULL;
		}

		if (g_pRequestUserManager!=NULL)
		{
			DEBUG_ADD("delete g_pRequestUserManager");
			delete g_pRequestUserManager;
			g_pRequestUserManager = NULL;
		}

		
		DEBUG_ADD("----- End ReleaseSocket -----");
		
}

//-----------------------------------------------------------------------------
// UnInit Sound
//-----------------------------------------------------------------------------
void
UnInitSound()
{
	//-------------------------------------
	// UnInit DirectSound
	//-------------------------------------
	if (g_pSoundManager!=NULL)
	{
		g_pSoundManager->Release();	
	}

	g_DXSound.Release();
}

//-----------------------------------------------------------------------------
// Init GameObject
//-----------------------------------------------------------------------------
BOOL
InitGameObject()
{
	DEBUG_ADD("[ InitGame ]  GameObject");

#if __CONTENTS(__CRYPT)
//	if(g_pCryptManager == NULL)
//	{
//		g_pCryptManager = new CCryptManager;
//		g_pCryptManager->InitCryptManager();
//	}
#endif 
	//----------------------------------------
	// 
	//----------------------------------------
	if (g_pSystemAvailableManager == NULL )
	{
		g_pSystemAvailableManager = new SystemAvailabilitiesManager;
		g_pSystemAvailableManager->LoadFromFile(g_pFileDef->getProperty("FILE_FILTER_INFO").c_str());
	}
	if (g_pServerInformation==NULL)
	{
		g_pServerInformation = new ServerInformation;
		g_pServerInformation->SetServerGroupName( "ServerGroup" );
		g_pServerInformation->SetServerName( "Server" );
	}

	if (g_pUserInformation==NULL)
	{
		g_pUserInformation = new UserInformation;
	}

	if (g_pTempInformation==NULL)
	{
		g_pTempInformation = new TempInformation;
	}

	if (g_pSkillManager==NULL)
	{
		g_pSkillManager = new MSkillManager;		
	}

	if (g_pSkillAvailable==NULL)
	{
		g_pSkillAvailable = new MSkillSet;
	}

	if (g_pSlayerGear==NULL)
	{
		g_pSlayerGear = new MSlayerGear;
	}

	if (g_pVampireGear==NULL)
	{
		g_pVampireGear = new MVampireGear;
	}

	if (g_pOustersGear==NULL)
	{
		g_pOustersGear = new MOustersGear;
	}

	//Add By Hays
	if (g_pSlayerGearOther==NULL)
	{
		g_pSlayerGearOther = new MSlayerGear;
	}

	if (g_pVampireGearOther==NULL)
	{
		g_pVampireGearOther = new MVampireGear;
	}

	if (g_pOustersGearOther==NULL)
	{
		g_pOustersGearOther = new MOustersGear;
	}

	if ( g_pMilitarySlot == NULL )
	{
		g_pMilitarySlot = new MilitarySlot;
	}
	
	if (g_pInventory==NULL)
	{
		g_pInventory = new MInventory;
	}

	if (g_pParty==NULL)
	{
		g_pParty = new MParty;
	}
	else
	{
		g_pParty->Release();
	}


	//if (g_pTradeManager==NULL)
	//{
	//	g_pTradeManager = new MTradeManager;
	//}	

	if (g_pGameTime==NULL)
	{
		g_pGameTime = new MGameTime;
	}

	if (g_pPriceManager==NULL)
	{
		g_pPriceManager = new MPriceManager;
	}

	if (g_pMoneyManager==NULL)
	{
		g_pMoneyManager = new MMoneyManager;
	}

	if (g_pPCTalkBox==NULL)
	{
		g_pPCTalkBox = new PCTalkBox;
	}

	if (g_pNPCTalkBox==NULL)
	{
		g_pNPCTalkBox = new MStringList;
	}

	if (g_pUIMessageManager==NULL)
	{
		g_pUIMessageManager = new UIMessageManager;
		g_pUIMessageManager->Init();
	}
 
	if (g_pObjectSelector==NULL)
	{
		g_pObjectSelector = new MObjectSelector;
	}

#if __CONTENTS(__PREMIUM_GIVE_ITEM_UI)
	if (g_pPremiumGiveItemInfoList==NULL)
	{
		g_pPremiumGiveItemInfoList = new MPremiumGiveItemInfoList;
	}
#endif //__PREMIUM_GIVE_ITEM_UI

	//----------------------------------------
	// Weather
	//----------------------------------------
	if (g_pWeather!=NULL)
	{
		delete g_pWeather;
	}
	g_pWeather = new MWeather;

	//----------------------------------------
	// ScreenEffectManager
	//----------------------------------------
	if (g_pInventoryEffectManager != NULL)
	{
		delete g_pInventoryEffectManager;			
	}
	g_pInventoryEffectManager = new MScreenEffectManager;

	//----------------------------------------
	// Player 생성
	//----------------------------------------
	if (g_pPlayer!=NULL)
	{	
		if (g_pZone!=NULL)
		{
			g_pZone->RemoveCreature( g_pPlayer->GetID() );
		}
	
		delete g_pPlayer;
	}

	// Player 기본값 초기화
	g_pPlayer = new MPlayer;
	DEBUG_ADD_FORMAT("[g_pPlayer] %x", g_pPlayer);

	g_pPlayer->SetCreatureType( CREATURETYPE_SLAYER_MALE );


	//--------------------------------------------------
	//
	// Skill Tree 초기화
	//
	//--------------------------------------------------
	g_pSkillManager->Init();

	return TRUE;
}
