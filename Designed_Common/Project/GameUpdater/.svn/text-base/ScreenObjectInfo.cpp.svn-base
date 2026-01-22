// ScreenObjectInfo.cpp: implementation of the ScreenObjectInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gameupdater.h"
#include "ScreenObjectInfo.h"

//zzi
#include "UpdaterVersionControl.h"
//-

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ScreenObjectInfo::ScreenObjectInfo()
{

}

ScreenObjectInfo::~ScreenObjectInfo()
{

}


void ScreenObjectInfo::InitNormal()
{
	// WebBrowser Size
	rcWebBrowser		= CRect(CPoint(2, 30), CSize(596, 360));

	// Common Button SIze
	CSize sizeButton(77, 43 );
	CSize sizeButton1(68, 43 );
	CSize sizeButton2(155, 44 );
	CSize sizeButtonexit(52, 18 );

	//071004 zzi - Init bButtonEnable
#ifdef _INTERNATIONAL_VERSION_
	bButtonEnable[BTN_CUSTOMERS] = true;
	bButtonEnable[BTN_ACCOUNT] = true;
#else
	bButtonEnable[BTN_CUSTOMERS] = true;
	bButtonEnable[BTN_ACCOUNT] = true;
#endif
	bButtonEnable[BTN_START] = true;
	bButtonEnable[BTN_EXIT] = true;
	bButtonEnable[BTN_MAX] = false;
//-

	// Customers Button
	rcOnButton[BTN_CUSTOMERS]			= CRect(CPoint(30, 412), sizeButton);
	nButtonResourceIdx[BTN_CUSTOMERS]	= IDB_CUSTOMERS_FOCUS;

	// Account Button
	rcOnButton[BTN_ACCOUNT]				= CRect(CPoint(107, 412), sizeButton1);
	nButtonResourceIdx[BTN_ACCOUNT]		= IDB_ACCOUNT_FOCUS;

	// Start Button
	rcOnButton[BTN_START]				= CRect(CPoint(418, 418), sizeButton2);
	nButtonResourceIdx[BTN_START]		= IDB_START_FOCUS;

	// Exit Button
	rcOnButton[BTN_EXIT]				= CRect(CPoint(543, 6), sizeButtonexit);
	nButtonResourceIdx[BTN_EXIT]		= IDB_EXIT_FOCUS;

	// Common Progress Size
	CSize sizeProgress(173, 4);

	// Files Progress Bar
	rcProgressFiles		= CRect(CPoint(241, 389 ), sizeProgress);

	// Total Progress Bar
	rcProgressTotal		= CRect(CPoint(241, 429), sizeProgress);

	// Version Number
	nVerNumResourceIdx[VERNUM_0]	= IDB_VERSION_0;
	nVerNumResourceIdx[VERNUM_1]	= IDB_VERSION_1;
	nVerNumResourceIdx[VERNUM_2]	= IDB_VERSION_2;
	nVerNumResourceIdx[VERNUM_3]	= IDB_VERSION_3;
	nVerNumResourceIdx[VERNUM_4]	= IDB_VERSION_4;
	nVerNumResourceIdx[VERNUM_5]	= IDB_VERSION_5;
	nVerNumResourceIdx[VERNUM_6]	= IDB_VERSION_6;
	nVerNumResourceIdx[VERNUM_7]	= IDB_VERSION_7;
	nVerNumResourceIdx[VERNUM_8]	= IDB_VERSION_8;
	nVerNumResourceIdx[VERNUM_9]	= IDB_VERSION_9;
	nVerNumResourceIdx[VERNUM_DOT]	= IDB_VERSION_DOT;
	nVerNumResourceIdx[VERNUM_VER]	= IDB_VERSION_VER;

	// 버전은 오른쪽에 정렬된다는 사실
	ptVersionPosition				= CPoint(489, 11);

	// 해상도 선택
	CSize sizeResolution(70, 13);

	//rcOnResolution[SELRES_1024x768]	= CRect(CPoint(205, 441), sizeResolution);
	//rcOnResolution[SELRES_800x600]	= CRect(CPoint(277, 441), sizeResolution);

	// rcOnFullScreen 
	CSize sizeFullScreen(60, 13);
	rcOnFullScreen	=   CRect(CPoint(343, 441), sizeFullScreen);

	// 상태 글씨 출력
	rcStatusString			= CRect(0, 392, 621, 438);
	rcStatusProgessString	= CRect(203, 396, 410, 418);

	rcDragWindow			= CRect(0, 0, 600, 30);

	// 놓迦뺏롸길쪽죗깊
	strSelectResolution[SELRES_800x600] =   " 800 * 600";
	strSelectResolution[SELRES_1024x768] =  "1024 * 768";
	strSelectResolution[SELRES_1280x720] =  "1280 * 720";
	strSelectResolution[SELRES_1280x768] =  "1280 * 768";
	strSelectResolution[SELRES_1280x960] =  "1280 * 960";
	strSelectResolution[SELRES_1280x1024] = "1280 * 1024";

}

void ScreenObjectInfo::InitWebLogin()
{
	rcStatusString			= CRect(0, 0, 413, 219);
	rcStatusProgessString	= rcStatusString;
	
	// Files Progress Bar
	rcProgressFiles			= rcStatusString;

	// Total Progress Bar
	rcProgressTotal			= rcStatusString;
}