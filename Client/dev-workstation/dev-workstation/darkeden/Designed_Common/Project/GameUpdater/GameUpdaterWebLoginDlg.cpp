 // NewUpdater2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "GameUpdater.h"
#include "GameUpdaterWebLoginDlg.h"

#include "ProgressST.h"
#include "CMessageArray.h"
#include "Properties.h"
#include "Updater.h"

#include "UpdateManagerThread.h"

//zzi
#include "UpdaterVersionControl.h"
#include "GameUpdaterStringInfo.h"
//-

#ifdef __TEST_CODE__
	#include "UCUpdateList.h"
#endif 


// WebServer를 통해서 다운을 받는다.
extern HRESULT InitFail(HWND hWnd, LPCTSTR szError,...);
extern std::string GetSeperator(int num);

extern HWND				g_hWnd;

extern BOOL				g_bHttpPatch;
extern CProgressST		g_Progress;
extern CProgressST		g_ProgressTotal;
extern CString			g_StatusString, g_VersionString;
extern BOOL				g_bWinNT;
extern char				g_CWD[_MAX_PATH];	
extern HANDLE			g_hSocketCheck;
extern bool				g_bNoFreeDisk;
extern std::string		g_FutecString;						//char g_FutecString[128] = {0, };
extern BYTE				g_Key[10];
extern RECT				g_statusRect;
RECT					g_TotaldownRect = {250, 166, 390, 178};

// [Futec수정]

//#define HTTP_PATCH_VERSION_PLUS				1000
//-----------------------------------------------------------------------------
// 긴급 updater.exe 패치를 위한 버전 수정..
// 2000이하이면 updater.exe를 무조건 받는다.
//-----------------------------------------------------------------------------
//#define HTTP_PATCH_VERSION_PLUS				2000

// 상용화 하면서 새버전으로 나가기 위해서!!
#define HTTP_PATCH_VERSION_PLUS				3000


#ifdef	OUTPUT_DEBUG
	CMessageArray*		g_pDebugMessage = NULL;
#endif
 
//-----------------------------------------------------------------------------
// Global
//-----------------------------------------------------------------------------
extern bool					g_bActiveApp;
extern bool					g_bActiveUpdate;
extern DWORD				g_CurrentTime;

extern CMessageArray		g_Message;

extern HANDLE				g_hMutex;

extern bool					g_bHasUpdate;
extern bool					g_bUpdateOK;

//void				Release();

extern DWORD				g_UpdateStartTime;

//bool				g_bFake = false;
extern bool					g_bPatcher;

extern HANDLE				g_hMessageThread;

extern HANDLE				g_hConnectThread;
extern HANDLE				g_hConnectCheck;

//extern bool		CheckDarkEdenFile();
extern bool		MovePIMFile(class PatchInfoManager &pim, int version);
extern class	PatchInfoManager g_pim;

extern int					g_version;
int							g_guildversion = -1;


//#ifdef _DEBUG
//#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#endif
/**********************************************************
		Mode Setting by 2004, 7, 29 sobeit added
**********************************************************/
extern bool g_bNetmarble;
extern bool g_bTestServer;

extern bool	g_bWebLoginMode;
extern bool	g_bOpenWeppage;
extern BYTE	g_Dimention;
/**********************************************************
		Mode Setting
**********************************************************/


/////////////////////////////////////////////////////////////////////////////
// CGameUpdaterWebLoginDlg dialog

CGameUpdaterWebLoginDlg::CGameUpdaterWebLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGameUpdaterWebLoginDlg::IDD, pParent)
	, m_bUpdateRunning(false)
	, m_hWorkThread(NULL)
	, m_dwWorkThreadID(0)
	, m_hThreadCheckTimer(NULL)
{
	//{{AFX_DATA_INIT(CGameUpdaterWebLoginDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CGameUpdaterWebLoginDlg::~CGameUpdaterWebLoginDlg()
{
	if(m_hWorkThread)
		CloseHandle(m_hWorkThread);

//	if(m_hThreadCheckTimer)
//		KillTimer(0);
	
	m_hWorkThread		= 0;
	m_dwWorkThreadID	= 0;
	m_bUpdateRunning	= false;
}

void CGameUpdaterWebLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGameUpdaterWebLoginDlg)
//	DDX_Control(pDX, IDC_EXPLORER1, m_Explorer);
	DDX_Control(pDX, IDC_PROGRESS1, g_Progress);
	DDX_Control(pDX, IDC_PROGRESS2, g_ProgressTotal);
//	DDX_Control(pDX, IDC_EXPLORER2, m_ExplorerBanner);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGameUpdaterWebLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CGameUpdaterWebLoginDlg)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGameUpdaterWebLoginDlg message handlers
bool
CGameUpdaterWebLoginDlg::ParsingRealServer(const char* pCommandLine)
{
	if( pCommandLine == NULL )
		return false;
	
//	AfxMessageBox(pCommandLine);
	char szTemp[1024];
	if(strlen(pCommandLine) < 16)
		return false;

	const char *pString = strchr(pCommandLine, ' ');
//	AfxMessageBox(pString);
	if(pString == NULL)
	{
		strcpy(szTemp, pCommandLine);
	}
	else
		strcpy(szTemp, pString+1);

	g_FutecString = szTemp;

	int argcnt = 0;
	char* token = NULL;
	char arg2[4][32];
	argcnt = 0;

	token = strtok(szTemp, "|");
	if(NULL == token)
		return false;
	while(token && argcnt < 4)
	{
		strcpy(arg2[argcnt], token);
		argcnt++;
		token = strtok(NULL, "|");
	}
	// mode|world|ID|key
	g_bWebLoginMode = atoi(arg2[0])?1:0;
	m_nDimention = atoi(arg2[1]);
	
	return true;
} 


BOOL CGameUpdaterWebLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ScreenObjectInfo::Instance()->InitWebLogin();
	
	SetRect(&g_statusRect, 27, 108, 390, 120);

	m_nDimention = 0;


#ifdef _DEBUG
	AfxMessageBox(__targv[1]);
#endif


#ifdef _DEBUG
	if(g_bNetmarble)
		AfxMessageBox("넷마블용");
	else
		AfxMessageBox("본섭용");
#endif


	if(false == g_bNetmarble)
	{
		bool ErrorMsg = false;
		if(__argc > 1)
		{
			char szBuf1[256];
			char szBuf2[256];
			strcpy(szBuf1, __targv[1]);
			if(__targv[2])
			{
				//AfxMessageBox("__targv[2]가 있다");
				strcpy(szBuf2, __targv[2]);
				if(strlen(szBuf2)>0)
				{
					strcat(szBuf1, " ");
					strcat(szBuf1,szBuf2);
				}
			}
//			std::string str = __targv[1];
//			str += ' ';
//			str += __targv[2];
			//AfxMessageBox(szBuf1);
			ErrorMsg = ParsingRealServer( szBuf1);
			if(false == ErrorMsg)
			{
#ifdef NDEBUG
//				AfxMessageBox("다크에덴은 홈페이지를 통해서만 실행이 가능합니다.");
				AfxMessageBox(_STR_INFO_WEBLOGIN_);
				
				ShellExecute(NULL, NULL, "www.darkeden.com", NULL, NULL, SW_SHOW);

				OnCancel();
#endif
			}
			if(false == g_bWebLoginMode)
			{
				ShellExecute(NULL, NULL, "Updater2R.exe", NULL, NULL, SW_SHOW);
				OnCancel();
			}

		}
	}
	else	// 넷마블 일때
	{
		if(__argc > 1)
		{
			if (strncmp(__targv[1], "PATCHER", 6)==0)
			{
				g_bPatcher = true;
				//AfxMessageBox("아하하");
			}
			else
			{	
				if(__targv[2])
					g_FutecString = __targv[2];
				else
					g_FutecString = __targv[1];
				//MessageBox(NULL, g_FutecString.c_str(), "", MB_OK);// ??
#ifdef _DEBUG
				AfxMessageBox( g_FutecString.c_str() );
#endif
			}
		}
	}
	
	// Add "About..." menu item to system menu.
	LOGFONT lf;

#ifdef __CHINESE__
	lf.lfHeight			= 16; // 0 = default
#else
	lf.lfHeight			= 12; // 0 = default
#endif
	lf.lfWidth			= 0; // 0 = 높이에 기준하여 자동으로 설정됨.
	lf.lfEscapement		= 0; // 방향설정 (900, 2700)
	lf.lfOrientation	= 0;
	lf.lfWeight			= FW_BOLD;
	lf.lfItalic			= 0; // 0 아닌 값이면 italic이다.
	lf.lfUnderline		= 0;
	lf.lfStrikeOut		= 0;
	lf.lfCharSet		= HANGUL_CHARSET;//*/JOHAB_CHARSET;
	lf.lfOutPrecision	= OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	lf.lfQuality		= DEFAULT_QUALITY;
	lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	strcpy(lf.lfFaceName, "돋움체");
	
	m_hStatusFont.CreateFontIndirect(&lf);
	
	lf.lfWeight = FW_NORMAL;
	m_hStatusFont2.CreateFontIndirect(&lf);

	lf.lfHeight			= 20; // 0 = default
	lf.lfWidth			= 0; // 0 = 높이에 기준하여 자동으로 설정됨.
	lf.lfEscapement		= 0; // 방향설정 (900, 2700)
	lf.lfOrientation	= 0;
	lf.lfWeight			= FW_BOLD;
	lf.lfItalic			= 0; // 0 아닌 값이면 italic이다.
	lf.lfUnderline		= 0;
	lf.lfStrikeOut		= 0;
	lf.lfCharSet		= HANGUL_CHARSET;//*/JOHAB_CHARSET;
	lf.lfOutPrecision	= OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	lf.lfQuality		= DEFAULT_QUALITY;
	lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	strcpy(lf.lfFaceName, "HY견명조");
	
	m_hVersionFont.CreateFontIndirect(&lf);

	m_bFocusExit = false;
	m_bPushExit = false;
	
	SetRect(&m_rtFocusExit, 373, 14, 373+21, 14+22);
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	g_hWnd = GetSafeHwnd();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
		
	#ifdef OUTPUT_DEBUG
		if (g_pDebugMessage)
		{
			g_pDebugMessage->Add("Before Init");
		}
	#endif	

	if (!Init())
	{
		return FALSE;
	}

	#ifdef OUTPUT_DEBUG
		if (g_pDebugMessage)
		{
			g_pDebugMessage->Add("Show Window");
		}
	#endif


	SetWindowText(PROGRAM_TITLE);

	
	OSVERSIONINFO        osVer;

	// First get the windows platform
	osVer.dwOSVersionInfoSize = sizeof(osVer);
	if( !GetVersionEx( &osVer ) )
	{
		// -_-;
		//return 0;
	}
	
	g_bWinNT = (osVer.dwPlatformId == VER_PLATFORM_WIN32_NT);

	g_Progress.SetRange32(0, 0);
//	g_Progress.SetPos(0);
	g_ProgressTotal.SetRange32(0, 0);
//	g_ProgressTotal.SetPos(0);
	
	int version = 0;

	std::ifstream versionFile(FILE_INFO_VERSION, std::ios_base::binary);
	if(versionFile.is_open())
		versionFile.read((char*)&version, 4);
	versionFile.close();

	char szTemp[512];

	if(version > 0)
	{
		sprintf(szTemp, "%1.2f", (float)version/100+3);
	}
	else
	{
		sprintf(szTemp, "0.00");
	}

	g_VersionString = szTemp;


	// 비트맵 로드
/*	CProgressST::GetBitmapAndPalette(IDB_WEBLOGIN_BG,
		m_dibBackground.bitmap, m_dibBackground.palette, m_dibBackground.size);

	CProgressST::GetBitmapAndPalette(IDB_WEBLOGIN_EXIT_HILIGHT,
		m_dibExitHilight.bitmap, m_dibExitHilight.palette, m_dibExitHilight.size);
*/

	SetWindowPos(NULL, 0, 0, m_dibBackground.size.cx, m_dibBackground.size.cy, SWP_NOMOVE);

	
	g_Progress.SetColor(RGB(156, 0, 0));
	g_Progress.SetBackColor(RGB(16, 16, 16));
	
	g_ProgressTotal.SetColor(RGB(156, 0, 0));
	g_ProgressTotal.SetBackColor(RGB(16, 16, 16));
	
	g_Progress.SetWindowPos(NULL, 77, 140, 294, 4, 0);
	g_ProgressTotal.SetWindowPos(NULL, 77, 149, 294, 4, 0);

	g_Progress.SetDrawText(false);
	g_ProgressTotal.SetDrawText(false);


	// 시작
	Connect();
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGameUpdaterWebLoginDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	RECT clientRect;
	GetClientRect(&clientRect);

	CDC bufferDC;
	bufferDC.CreateCompatibleDC(&dc);

	bufferDC.SetBkMode(TRANSPARENT);

	CBitmap bmpBuffer;
	bmpBuffer.CreateCompatibleBitmap(&dc, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);

	CBitmap* pOldBufferBitmap = bufferDC.SelectObject(&bmpBuffer);

	CDC tempDC;
	tempDC.CreateCompatibleDC(&bufferDC);

	CBitmap* pOldTempBitmap = tempDC.SelectObject(&m_dibBackground.bitmap);

	tempDC.SelectObject(m_dibBackground.bitmap);
	bufferDC.BitBlt(0, 0,
		clientRect.right - clientRect.left,
		clientRect.bottom - clientRect.top,
		&tempDC, 0, 0, SRCCOPY);

	// EXIT
	if(m_bFocusExit)
	{
		tempDC.SelectObject(m_dibExitHilight.bitmap);
		bufferDC.BitBlt(m_rtFocusExit.left, m_rtFocusExit.top,
			m_rtFocusExit.right - m_rtFocusExit.left,
			m_rtFocusExit.bottom - m_rtFocusExit.top,
			&tempDC, 0, 0, SRCCOPY);
	}


	bufferDC.SelectObject(&m_hStatusFont);
	bufferDC.SetTextColor(RGB(255, 180, 0));

	bufferDC.DrawText(g_StatusString, 
		CRect(77, 245, 350, 10),
		DT_SINGLELINE | DT_LEFT | DT_VCENTER);

	tempDC.SelectObject(pOldTempBitmap);

	dc.BitBlt(0, 0,
		clientRect.right - clientRect.left,
		clientRect.bottom - clientRect.top,
		&bufferDC, 0, 0, SRCCOPY);

	bufferDC.SelectObject(pOldBufferBitmap);
}


//-----------------------------------------------------------------------------
// Release
//-----------------------------------------------------------------------------
void
CGameUpdaterWebLoginDlg::Release()
{
	g_bActiveUpdate = FALSE;
}

BOOL CGameUpdaterWebLoginDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	#ifdef OUTPUT_DEBUG
		if (g_pDebugMessage)
		{
			g_pDebugMessage->Add("End Loop");

			g_pDebugMessage->Add("--------------- Delete DebugMessageArray --------------");		
			delete g_pDebugMessage;	
			g_pDebugMessage = NULL;
		}
	#endif
		
	Release();

	
	return CDialog::DestroyWindow();
}


//-----------------------------------------------------------------------------
// Init
//-----------------------------------------------------------------------------
bool
CGameUpdaterWebLoginDlg::Init()
{
	//-----------------------------------------------------
	// Message 초기화
	//-----------------------------------------------------
//	g_Message.Init(MAX_TEXT, 80);

	//-----------------------------------------------------
	// test timer
	//-----------------------------------------------------
	SetTimer(100, 1000, NULL);

	return true;
}

void CGameUpdaterWebLoginDlg::Connect()
{
	if(m_bUpdateRunning)
	{
//		MessageBox("이미 패치 작업이 진행중입니다.", NULL, MB_OK | MB_ICONINFORMATION);
		MessageBox(_STR_ALREADY_RUNNING_, NULL, MB_OK | MB_ICONINFORMATION);
		return;
	}


	//여기서, 이전버전과 Nowcom 버전으로 분기한다.
#ifdef __USE_NOWCDN__
	NowDN_Start ();
	return;
#endif
	//

	m_hWorkThread = (HANDLE)_beginthreadex(
		NULL, 0, Update_Thread, &m_UpdateManager, 0, (unsigned int *)&m_dwWorkThreadID);
	
	SetThreadPriority(m_hWorkThread, THREAD_PRIORITY_HIGHEST);	

	m_bUpdateRunning = true;

	m_hThreadCheckTimer = (HANDLE)SetTimer(0, 100, NULL);
}

void CGameUpdaterWebLoginDlg::OnOK() 
{
	// TODO: Add extra validation here
	Release();

	CDialog::OnOK();
}

void CGameUpdaterWebLoginDlg::OnCancel() 
{
	if(m_bUpdateRunning)
	{
		MessageBox(_STR_INFO_EXITONRUNNING_, NULL, MB_OK | MB_ICONERROR);
//		MessageBox(
//			"패치 중에는 업데이터를 종료할 수 없습니다.\n\n"
//			"강제로 종료할 경우 데이터가 손상될 수 있습니다.",
//			NULL, MB_OK | MB_ICONERROR);

		return;
	}

	// TODO: Add extra cleanup here
	Release();
	
	CDialog::OnCancel();
}


void CGameUpdaterWebLoginDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	bool bRefresh = false;
	//RECT refreshRect = { min(EXITBACK_X, STARTBACK_X), min(EXITBACK_Y, STARTBACK_Y), max(EXITBACK_X+m_nExitBack.cx, STARTBACK_X+m_nStartBack.cx), max(EXITBACK_Y+m_nExitBack.cy, STARTBACK_Y+m_nStartBack.cy)};
	

	// TODO: Add your message handler code here and/or call default
	if(PtInRect(&m_rtFocusExit, point))
	{
		if(!m_bFocusExit)
		{
			bRefresh = true;
		}
		m_bFocusExit = true;
	}
	else
	{
		if(m_bFocusExit)
		{
			bRefresh = true;
		}
		m_bFocusExit = false;
		m_bPushExit = false;
	}
	
	if(bRefresh)
	{
		InvalidateRect(&m_rtFocusExit, FALSE);
	}
	
	CDialog::OnMouseMove(nFlags, point);
}

void CGameUpdaterWebLoginDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	bool bRefresh = false;
	// TODO: Add your message handler code here and/or call default
	
	if(m_bFocusExit)
	{
		if(!m_bPushExit)
			bRefresh = true;
		m_bPushExit = true;
	}
		
	if(bRefresh)
	{
		InvalidateRect(&m_rtFocusExit, FALSE);
	}

	CDialog::OnLButtonDown(nFlags, point);
}


void CGameUpdaterWebLoginDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bFocusExit && m_bPushExit)
		OnCancel();

	CDialog::OnLButtonUp(nFlags, point);
}


void CGameUpdaterWebLoginDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == 0)
	{
		// 스레드가 종료되길 기다린다.
		DWORD exitCode = STILL_ACTIVE;
		GetExitCodeThread(m_hWorkThread, &exitCode);
		
		if(exitCode != STILL_ACTIVE)
		{
			KillTimer(nIDEvent);
			
			m_hThreadCheckTimer = NULL;
			m_bUpdateRunning	= false;

			char szParamBuf[256];
			
			switch(exitCode)
			{
			case EXITCODE_PATCH_COMPLETE:
				sprintf(szParamBuf, "NEWSTART %s", g_FutecString);
				_spawnl(_P_OVERLAY, DARKEDEN_FILENAME, DARKEDEN_FILENAME, szParamBuf, NULL);	
				PostQuitMessage(0);
				break;
				
			case EXITCODE_UPDATER_PATCH:
				// 실행중인 Updater를 종료하고 ExeSwaper를 통해 새로운 Updater를 카피한다.
				char szParam[512];
				sprintf(szParam, "%s %s %s", UPDATER_NEW_FILENAME, UPDATER_FILENAME, g_FutecString);
				_spawnl(_P_OVERLAY, EXESWAPER_FILENAME, EXESWAPER_FILENAME, szParam, NULL);	
				PostQuitMessage(0);
				break;
			//20071210 - 서버점검중.. 넷마블은..서버점검중 기능만 추가.
			case EXITCODE_NOWMAINTENANCE:
				MessageBox(_STR_FAILTOPATCH_, NULL, MB_OK | MB_ICONERROR);
				PostQuitMessage(0);
				break;
			//--
			default:
//				MessageBox("패치가 실패하였습니다.", NULL, MB_OK | MB_ICONERROR);
				MessageBox(_STR_FAILTOPATCH_, NULL, MB_OK | MB_ICONERROR);
			}
		}
	}
	//Nowcom - 다운로드 프로그레스바 갱신을 위해..
	else if (nIDEvent == 100)
	{
		NowDN_UpdateUI ();
	}
	//--
	
	CDialog::OnTimer(nIDEvent);
}

void CGameUpdaterWebLoginDlg::SetStatusString(const char* message)
{
	g_StatusString = message;

	const CRect& rStatusRect = ScreenObjectInfo::Instance()->rcStatusString;
	InvalidateRect(&rStatusRect, FALSE);
}



//now Cdn의 경우에만 사용되는.. Guild마크만을 위한 쓰레드를 시작하기 위한 함수.
// 길드마크는.. 효성CDN를 그대로 사용하기 때문 ㅠㅠ
void CGameUpdaterWebLoginDlg::Start_GuildMarkUpdate ()
{
	//여기서, 길드마크를 다운로드할 스레드를 시작한다.
	m_hWorkThread = (HANDLE)_beginthreadex(
		NULL, 0, Update_Thread_GuildMark, &m_UpdateManager, 0, (unsigned int *)&m_dwWorkThreadID);
	
	SetThreadPriority(m_hWorkThread, THREAD_PRIORITY_HIGHEST);	
//	m_bUpdateRunning = true;
	m_hThreadCheckTimer = (HANDLE)SetTimer(0, 100, NULL);
}

void CGameUpdaterWebLoginDlg::Start_Timer ()
{
	SetTimer (100, 50, NULL);
}

void CGameUpdaterWebLoginDlg::End_Timer ()
{
	KillTimer (100);
}

bool CGameUpdaterWebLoginDlg::NowDN_Init ()
{
	//NowDll Path 설정.
	TCHAR	szCurPath[MAX_PATH];
	::GetCurrentDirectory (sizeof(szCurPath), szCurPath);
	m_NowDllPath.Format (_T("%s\\"), szCurPath);

	m_NowDllPath += _T("DownEngineSDK.dll");
	
	//UpdateManager에도 root를 설정해 줘야 한다. -_-;;
	m_UpdateManager.SetRootPath (szCurPath);
	return true;
}

bool CGameUpdaterWebLoginDlg::NowDN_Start ()
{
	//NowDN dll를 사용준비
	if (!NowDN_Init ())
		return false;

	//패치준비
	if(!m_UpdateManager.LoadUpdateInfo_NowCom())
	{
//		SetStatusString ("알수 없는 형식의 업데이트 정보파일입니다.");
		SetStatusString (_STR_UNKNOWNINFOFILE_);
		return false;
	}

	//이제 패치를 시작한다.
	m_bUpdateRunning = true;

	// 먼저, 테스트를 하자.
//	NowDN_Test ();
	
	NowDN_Step1 ();
	return true;
}

void CGameUpdaterWebLoginDlg::NowDN_Error (LPCTSTR text)
{
	//에러메시지와 실패대화상자를 출력하고..종료.
	SetStatusString (text);

//	MessageBox("패치가 실패하였습니다.", NULL, MB_OK | MB_ICONERROR);
	MessageBox(_STR_FAILTOPATCH_, NULL, MB_OK | MB_ICONERROR);
	PostQuitMessage(0);
}

void CGameUpdaterWebLoginDlg::Complete_UpdaterPatch ()
{
	m_bUpdateRunning	= false;
//	SaveResolutionConfig();
	// 실행중인 Updater를 종료하고 ExeSwaper를 통해 새로운 Updater를 카피한다.
	// 이후, ExeSwaper에서 Updater를 카피한 후, 다시 실행할 것이다.
	char szParam[256];
	sprintf(szParam, "%s %s", UPDATER_NEW_FILENAME, UPDATER_FILENAME);
	_spawnl(_P_OVERLAY, EXESWAPER_FILENAME, EXESWAPER_FILENAME, szParam, NULL);	
	PostQuitMessage(0);
}

void CGameUpdaterWebLoginDlg::Complete_Patch ()
{
	m_bUpdateRunning	= false;
//	SaveResolutionConfig();

	_spawnl(_P_OVERLAY, DARKEDEN_FILENAME, DARKEDEN_FILENAME, "NEWSTART", NULL);	
	PostQuitMessage(0);
}


//Step1 : Status 확인은 개발단계에서는 빼고..진행한다. < 파일이 없는 경우에 대한 처리가 NowDN에는 현재 없다. ㅠㅠ >
void CGameUpdaterWebLoginDlg::NowDN_Step1 ()
{
	//따라서, 바로.. 다음 단계로..
	NowDN_Step2 ();
}
//Step1 CallBacks
void CGameUpdaterWebLoginDlg::CallBack_Status_OnFileInfo (IN void *pThisPointer, IN CHAR *pszFileNameA, IN WCHAR *pszFileNameW, IN ULONG ulFileTotalCount, IN ULONGLONG ullFileSize, IN ULONG ulCPCode, IN ULONG ulGameCode, IN ULONG ulFileID, IN ULONG ulFileType)
{
}

void CGameUpdaterWebLoginDlg::CallBack_Status_OnDownloadStart (IN void *pThisPointer)
{
}

void CGameUpdaterWebLoginDlg::CallBack_Status_OnDownloadComplete (IN void *pThisPointer)
{
}

//Step2 : FileListVersion 체크!! 
void CGameUpdaterWebLoginDlg::NowDN_Step2 ()
{
	Start_Timer ();
	m_DownEngine.Create (m_NowDllPath);
	m_DownEngine.SetParentWindow((void*)this);

	// DownEngineSDK로 다운로드 시작 알림을 받을 함수 포인터 전달
	m_DownEngine.SetNotifyDownStartCallBack(CGameUpdaterWebLoginDlg::CallBack_FileListVersion_OnDownloadStart);
	// DownEngineSDK로 다운로드 완료 알림을 받을 함수 포인터 전달
	m_DownEngine.SetNotifyDownCompleteCallBack(CGameUpdaterWebLoginDlg::CallBack_FileListVersion_OnDownloadComplete);
	// DownEngineSDK로 다운로드 대상 파일들의 정보를 받을 함수 포인터 전달
	m_DownEngine.SetDrawFileInfoCallback(CGameUpdaterWebLoginDlg::CallBack_FileListVersion_OnFileInfo);


	//다운받을 파일 'FileListVersion'을 NowDll에 설정한다.
	m_UpdateManager.ReadyCheckFileListVersion (&m_DownEngine);

	//다운로드 시작.
	m_DownEngine.AutoPatchStart ();
}

//Step2 - CallBacks
void CGameUpdaterWebLoginDlg::CallBack_FileListVersion_OnFileInfo (IN void *pThisPointer, IN CHAR *pszFileNameA, IN WCHAR *pszFileNameW, IN ULONG ulFileTotalCount, IN ULONGLONG ullFileSize, IN ULONG ulCPCode, IN ULONG ulGameCode, IN ULONG ulFileID, IN ULONG ulFileType)
{
	CGameUpdaterWebLoginDlg *pDlg = (CGameUpdaterWebLoginDlg*)pThisPointer;
	//용량이 작다. -- 경험적인 판단. 별도의 파일크기 체크를 하지않는다. ^^;; 
	g_Progress.SetRangeUnitK ();

	g_Progress.SetRange32 (0, (int)(ullFileSize));///1024));
	g_Progress.SetPos (0);
	pDlg->UpdateProgress ();// (0);		
}

void CGameUpdaterWebLoginDlg::CallBack_FileListVersion_OnDownloadStart (IN void *pThisPointer)
{
	CGameUpdaterWebLoginDlg *pDlg = (CGameUpdaterWebLoginDlg*)pThisPointer;
//	pDlg->Start_Timer ();
//	pDlg->SetStatusString ("버전을 확인하고 있습니다.");
	pDlg->SetStatusString (_STR_CHECKINGVERSION_);
}

void CGameUpdaterWebLoginDlg::CallBack_FileListVersion_OnDownloadComplete (IN void *pThisPointer)
{
	CGameUpdaterWebLoginDlg *pDlg = (CGameUpdaterWebLoginDlg*)pThisPointer;
	pDlg->End_Timer ();
	// 프로그레스바를 Full로 강제!!
	int Lower, Upper;
	g_Progress.GetRange (Lower, Upper);
	g_Progress.SetPos (Upper);
	pDlg->UpdateProgress ();

	bool bNeedPatch = false;
	if (!pDlg->m_UpdateManager.CheckFileListVersion_NowCom (&bNeedPatch))
	{
		//다운로드 실패 혹은, 파일오픈 실패!! 에러 처리
//		pDlg->NowDN_Error ("버전 확인에 실패하였습니다.");
		pDlg->NowDN_Error (_STR_FAILTOCHECINGVERSION_);
		return;
	}

	if (bNeedPatch)
		pDlg->NowDN_Step3 ();
	else
	{
		//버전이 같다. 패치가 필요 없다. 이럴 경우의 처리는 여기서..
		pDlg->Complete_Patch ();
	}
}

//Step3 : FileList 다운로드.
void CGameUpdaterWebLoginDlg::NowDN_Step3 ()
{
	Start_Timer ();
	m_DownEngine.Create (m_NowDllPath);
	m_DownEngine.SetParentWindow((void*)this);

	// DownEngineSDK로 다운로드 시작 알림을 받을 함수 포인터 전달
	m_DownEngine.SetNotifyDownStartCallBack(CGameUpdaterWebLoginDlg::CallBack_FileList_OnDownloadStart);
	// DownEngineSDK로 다운로드 완료 알림을 받을 함수 포인터 전달
	m_DownEngine.SetNotifyDownCompleteCallBack(CGameUpdaterWebLoginDlg::CallBack_FileList_OnDownloadComplete);
	// DownEngineSDK로 다운로드 대상 파일들의 정보를 받을 함수 포인터 전달
	m_DownEngine.SetDrawFileInfoCallback(CGameUpdaterWebLoginDlg::CallBack_FileList_OnFileInfo);


	//다운받을 파일 'FileList'을 NowDll에 설정한다.
	m_UpdateManager.ReadyDownloadRecentFileList (&m_DownEngine);

	//다운로드 시작.
	m_DownEngine.AutoPatchStart ();
}
//
void CGameUpdaterWebLoginDlg::CallBack_FileList_OnFileInfo (IN void *pThisPointer, IN CHAR *pszFileNameA, IN WCHAR *pszFileNameW, IN ULONG ulFileTotalCount, IN ULONGLONG ullFileSize, IN ULONG ulCPCode, IN ULONG ulGameCode, IN ULONG ulFileID, IN ULONG ulFileType)
{
	CGameUpdaterWebLoginDlg *pDlg = (CGameUpdaterWebLoginDlg*)pThisPointer;
	//용량이 작다. -- 경험적인 판단. 별도의 파일크기 체크를 하지않는다. ^^;; 
	g_Progress.SetRangeUnitK ();

	g_Progress.SetRange32 (0, (int)(ullFileSize));
	g_Progress.SetPos (0);
	pDlg->UpdateProgress ();//(0);		
}

void CGameUpdaterWebLoginDlg::CallBack_FileList_OnDownloadStart (IN void *pThisPointer)
{
	CGameUpdaterWebLoginDlg *pDlg = (CGameUpdaterWebLoginDlg*)pThisPointer;
//	pDlg->Start_Timer ();
//	pDlg->SetStatusString ("파일 정보를 다운로드하고 있습니다.");
	pDlg->SetStatusString (_STR_DOWNLOADINGFILEINFO_);
}

void CGameUpdaterWebLoginDlg::CallBack_FileList_OnDownloadComplete (IN void *pThisPointer)
{
	CGameUpdaterWebLoginDlg *pDlg = (CGameUpdaterWebLoginDlg*)pThisPointer;
	pDlg->End_Timer ();
	// 프로그레스바를 Full로 강제!!
	int Lower, Upper;
	g_Progress.GetRange (Lower, Upper);
	g_Progress.SetPos (Upper);
	pDlg->UpdateProgress ();

	//m_RecentFiles와 m_LocalFiles 목록을 생성한다.
	pDlg->m_UpdateManager.DownloadRecentFileList_NowCom ();

	//다음 단계인 -- Updater자체의 패치여부를 진행한다.
	pDlg->NowDN_Step4 ();
}

//Step4 - Updater Patch
// - Step3에서 설정된 FileList들을 이용하여, Updater자체의 패치여부를 판단하고, 필요시 패치한다.
void CGameUpdaterWebLoginDlg::NowDN_Step4 ()
{
	Start_Timer ();
	m_DownEngine.Create (m_NowDllPath);
	m_DownEngine.SetParentWindow((void*)this);

	// DownEngineSDK로 다운로드 시작 알림을 받을 함수 포인터 전달
	m_DownEngine.SetNotifyDownStartCallBack(CGameUpdaterWebLoginDlg::CallBack_UpdaterPatch_OnDownloadStart);
	// DownEngineSDK로 다운로드 완료 알림을 받을 함수 포인터 전달
	m_DownEngine.SetNotifyDownCompleteCallBack(CGameUpdaterWebLoginDlg::CallBack_UpdaterPatch_OnDownloadComplete);
	// DownEngineSDK로 다운로드 대상 파일들의 정보를 받을 함수 포인터 전달
	m_DownEngine.SetDrawFileInfoCallback(CGameUpdaterWebLoginDlg::CallBack_UpdaterPatch_OnFileInfo);

//	SetStatusString ("업데이터 패치를 확인하고 있습니다.");
	SetStatusString (_STR_CHECKINGUPDATERPATCH_);
	//Updater의 패치가 필요한가 확인 -- 확인이 성공했다는 것은.. 파일정보 설정까지 했다는 의미. 그렇지 않다면, 위에서 생성한 DonwEngine를 클로즈 하도록하자.
	if (m_UpdateManager.CheckUpdaterPatch_NowCom (&m_DownEngine))
	{
		//다운로드 시작.
		m_DownEngine.AutoPatchStart ();
		//아래의 콜백 함수에서.. Updater패치처리 후, 종료.
	}
	else
	{
		m_DownEngine.Close ();
		End_Timer ();
		//바로 다음 단계로..
		NowDN_Step5 ();
	}
}


//CallBacks - UpdaterPatch
void CGameUpdaterWebLoginDlg::CallBack_UpdaterPatch_OnFileInfo (IN void *pThisPointer, IN CHAR *pszFileNameA, IN WCHAR *pszFileNameW, IN ULONG ulFileTotalCount, IN ULONGLONG ullFileSize, IN ULONG ulCPCode, IN ULONG ulGameCode, IN ULONG ulFileID, IN ULONG ulFileType)
{
	CGameUpdaterWebLoginDlg *pDlg = (CGameUpdaterWebLoginDlg*)pThisPointer;
	//용량이 작다. -- 경험적인 판단. 별도의 파일크기 체크를 하지않는다. ^^;; 
	g_Progress.SetRangeUnitK ();

	g_Progress.SetRange32 (0, (int)(ullFileSize));
	g_Progress.SetPos (0);
	pDlg->UpdateProgress ();//(0);		
}

void CGameUpdaterWebLoginDlg::CallBack_UpdaterPatch_OnDownloadStart (IN void *pThisPointer)
{
	CGameUpdaterWebLoginDlg *pDlg = (CGameUpdaterWebLoginDlg*)pThisPointer;
//	pDlg->Start_Timer ();
//	pDlg->SetStatusString ("업데이터를 다운로드하고 있습니다.");
	pDlg->SetStatusString (_STR_DOWNLOADINGUPDATER_);
}

void CGameUpdaterWebLoginDlg::CallBack_UpdaterPatch_OnDownloadComplete (IN void *pThisPointer)
{
	CGameUpdaterWebLoginDlg *pDlg = (CGameUpdaterWebLoginDlg*)pThisPointer;
	pDlg->End_Timer ();
	// 프로그레스바를 Full로 강제!!
	int Lower, Upper;
	g_Progress.GetRange (Lower, Upper);
	g_Progress.SetPos (Upper);
	pDlg->UpdateProgress ();

	//여기로 들어온 다는 것은.. Updater파일을 다운로드 했다는 것!! 다운로드 한 Updater를 적용한다.
	if (!pDlg->m_UpdateManager.DoUpdaterPatch ())
	{
		//다운로드는 성공했으나, 이후의 처리에서 실패을 했다.!!!! Error처리를 하고 종료 해야겠지?
//		pDlg->NowDN_Error ("업데이터 패치에 실패하였습니다.");
		pDlg->NowDN_Error (_STR_FAILTOUPDATERPATCH_);
	}
	else
	{
		//성공!! -- 
		pDlg->Complete_UpdaterPatch ();
	}
}

//Step5 - Updated Files Download
//	업데이트될 파일들을 모두 다운로드 한다.
void CGameUpdaterWebLoginDlg::NowDN_Step5 ()
{
	//업데이트될 파일들을 다운로드 하기 전에~~ 해야할 것들이 있다.
	//	1. 업데이트 정보를 생성해야 한다. - GenerateUpdateFile // 업데이트된 파일목록과, 삭제된 파일목록, 팩킹타입변경 파일목록 을 생성한다.
	//	2. 업데이트된 파일목록을 다운로드할 수 있는만큼의 디스크 용량을 확인한다.
//	SetStatusString ("업데이트 정보를 확인하고 있습니다.");
	SetStatusString (_STR_CHECKINGUPDATEINFO_);
	if (!m_UpdateManager.GenerateUpdateFile ())
	{
		//실패!! 실패처리!!
//		NowDN_Error ("업데이트 정보를 확인 할 수 없습니다.");
		NowDN_Error (_STR_FAILTOCHECKINGUPDATEINFO_);
		return;
	}

//	SetStatusString ("디스크의 남은 공간을 확인하고 있습니다.");
	SetStatusString (_STR_CHECKFREEDISK_);
	if (!m_UpdateManager.CheckDiskFreeSpace ())
	{
		//실패!! 실패처리!!
//		NowDN_Error ("디스크의 남은 공간이 부족합니다.");
		NowDN_Error (_STR_NOTENOUGHFREEDIST_);
		return;
	}
	Start_Timer ();

	m_DownEngine.Create (m_NowDllPath);
	m_DownEngine.SetParentWindow((void*)this);

	// DownEngineSDK로 다운로드 시작 알림을 받을 함수 포인터 전달
	m_DownEngine.SetNotifyDownStartCallBack(CGameUpdaterWebLoginDlg::CallBack_UpdatedFileDown_OnDownloadStart);
	// DownEngineSDK로 다운로드 완료 알림을 받을 함수 포인터 전달
	m_DownEngine.SetNotifyDownCompleteCallBack(CGameUpdaterWebLoginDlg::CallBack_UpdatedFileDown_OnDownloadComplete);
	// DownEngineSDK로 다운로드 대상 파일들의 정보를 받을 함수 포인터 전달
	m_DownEngine.SetDrawFileInfoCallback(CGameUpdaterWebLoginDlg::CallBack_UpdatedFileDown_OnFileInfo);

	int FileCount = 0;
	if (!m_UpdateManager.ReadyDownloadUpdatedFiles (&m_DownEngine, &FileCount))
	{
		//업데이트 될 파일들의 다운로드 준비 실패!! 에러처리 후, 종료
//		NowDN_Error ("업데이트를 다운로드 받을 수 없습니다.");
		NowDN_Error (_STR_CANNOTDOWNLOADPATCHFILES_);
	}
	//다운로드 시작
	if (FileCount)
		m_DownEngine.AutoPatchStart ();
	else
	{
		//다운로드 받을 필요는 없다. -- 패치될 파일을 모두 다운 받아 놓은 상태에서~~ 무언가의 문제로.. Updater를 다시 실행 한 것이다.
		// 이럴 경우, 바로.. Complete단계로...
		NowDN_Complete ();
		End_Timer ();
	}
//	SetStatusString ("업데이트를 다운로드 받고 있습니다.");
	SetStatusString (_STR_DOWNLOADINGPATCHFILES_);
}

//CallBacks - Patch
void CGameUpdaterWebLoginDlg::CallBack_UpdatedFileDown_OnFileInfo (IN void *pThisPointer, IN CHAR *pszFileNameA, IN WCHAR *pszFileNameW, IN ULONG ulFileTotalCount, IN ULONGLONG ullFileSize, IN ULONG ulCPCode, IN ULONG ulGameCode, IN ULONG ulFileID, IN ULONG ulFileType)
{
	CGameUpdaterWebLoginDlg *pDlg = (CGameUpdaterWebLoginDlg*)pThisPointer;
	//용량을 체크하자. 현재의 프로그래스바가 Range값이 몇 까지 설정되었을 때, 정상적으로 그려지는 지는 확인하자면 완전 노가다.ㅡㅡ;
	// 대략 다운받을 파일의 전체사이즈가 M단위가 된다면.. M로 설정하자.
	if (ullFileSize / (1024*1024) > 1)
		g_Progress.SetRangeUnitM ();
	else
		g_Progress.SetRangeUnitK ();

	g_Progress.SetRange32 (0, (int)(ullFileSize/1024));	//미리 1024로 나누어 KByte단위의 값으로 설정. OnPaint에서 다시 1024로 나누므로, M단위의 값으로 출력될 것이다.
	g_Progress.SetPos (0);
	pDlg->UpdateProgress ();//(0);		
}

void CGameUpdaterWebLoginDlg::CallBack_UpdatedFileDown_OnDownloadStart (IN void *pThisPointer)
{
	CGameUpdaterWebLoginDlg *pDlg = (CGameUpdaterWebLoginDlg*)pThisPointer;
//	pDlg->Start_Timer ();
}

void CGameUpdaterWebLoginDlg::CallBack_UpdatedFileDown_OnDownloadComplete (IN void *pThisPointer)
{
	CGameUpdaterWebLoginDlg *pDlg = (CGameUpdaterWebLoginDlg*)pThisPointer;
	pDlg->End_Timer ();

	// 업데이트 될 파일들의 다운로드가 완료되었다. 
	pDlg->m_UpdateManager.ApplyDownloadUpdatedFiles ();

	// 프로그레스바를 Full로 강제!!
	int Lower, Upper;
	g_Progress.GetRange (Lower, Upper);
	g_Progress.SetPos (Upper);
	pDlg->UpdateProgress ();

	// 다음단계로 .. 고고싱~~
	pDlg->NowDN_Complete ();
}	

// 다운로드 한 파일들을 패치적용 (실재 로컬 파일들에 카피)하고, 지울 건 지우고, 팩킹 타입이 변경된 것을 처리하고, 길드마크 패치를 시작한다.
void CGameUpdaterWebLoginDlg::NowDN_Complete ()
{
	//각 단계에 적합한.. 상태문자열~~을 추가하자.. ^^

/*	아래 녀석들이.ㅡㅡ; Dlg 쓰레드에서 호출되므로... 정보갱신이 안된다. ==> 길드마크 쓰레드로.. 이전..한다.

	
	// 먼저, 삭제할 파일을 제거한다.
	SetStatusString ("제거된 파일을 삭제하고 있습니다.");
//	OnPaint ();
	if (!m_UpdateManager.ApplyDeletedFiles_NowCom ())
	{
		NowDN_Error ("업데이트가 실패하였습니다.");
	}

	// 다운로드한 파일들을 카피한다.
	SetStatusString ("업데이트를 적용하고 있습니다.");
//	OnPaint ();
	if (!m_UpdateManager.ApplyUpdatedFiles_NowCom ())
	{
		NowDN_Error ("업데이트가 실패하였습니다.");
	}

	// 팩킹타입이 변경된 파일들에 대한 처리
	SetStatusString ("패키지를 업데이트하고 있습니다.");
//	OnPaint ();
	if (!m_UpdateManager.ApplyPackingTypeChangedFiles_NowCom ())
	{
		NowDN_Error ("업데이트가 실패하였습니다.");
	}

	// 로컬상의 파일리스트/파일리스트버전 을 갱신한다
	if (!m_UpdateManager.ApplyFileList ())
	{
		NowDN_Error ("업데이트가 실패하였습니다.");
	}
*/

	//이제 길드마크 패치 시작~~!~
	Start_GuildMarkUpdate ();
}


//UI Update
void CGameUpdaterWebLoginDlg::NowDN_UpdateUI ()
{
	ULONG		ulDownCompleteCount = 0;
	ULONG		ulDownloadSpeed = 0;
	ULONGLONG	ullDownloadSize = 0;
	ULONG		ulExtraTime = 0;
	ULONG		ulLapseTime = 0;

	m_DownEngine.GetDownloadInfo(&ulDownCompleteCount, &ulDownloadSpeed, &ullDownloadSize, &ulExtraTime, &ulLapseTime);
	
	//ullDownloadSize 만..사용하자.
	//여기서도, M단위와 K단위를 구분해 줘야 한다. -_-;; 거참 귀찮군.
	int RangeUnit = g_Progress.GetRangeUnit ();
	if (RangeUnit == __MBYTE__)
	{
		//MByte단위일 때는.. 1024로 나누어 KByte단위로 설정해 줘야한다.
		g_Progress.SetPos (((int)ullDownloadSize/1024));///1024);
	}
	else
	{
		g_Progress.SetPos ((int)ullDownloadSize);
	}

	UpdateProgress ();
	//UpdateProgress ((int)(ullDownloadSize));///1024));
//	static int CheckCheck = 0;
//	char strCheck[256];
//	wsprintf (strCheck, "%d : %d Kb", CheckCheck, ullDownloadSize/1024);
//	UpdatePatchStatus (strCheck);
//	CheckCheck++;
}


//UI - Common
void CGameUpdaterWebLoginDlg::UpdateProgress ()//(int pos)
{
	const CRect& rInvalidateRect = ScreenObjectInfo::Instance()->rcStatusString;
//	g_Progress.SetPos (pos);
	::InvalidateRect(g_hWnd, &rInvalidateRect, FALSE);
}

void CGameUpdaterWebLoginDlg::UpdateTotalProgress ()//(int pos)
{
	const CRect& rInvalidateRect = ScreenObjectInfo::Instance()->rcStatusString;
//	g_ProgressTotal.SetPos (pos);
	::InvalidateRect(g_hWnd, &rInvalidateRect, FALSE);
}

