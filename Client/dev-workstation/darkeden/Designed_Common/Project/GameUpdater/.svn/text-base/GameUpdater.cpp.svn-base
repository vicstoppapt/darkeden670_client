// NewUpdater2.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "GameUpdater.h"

#include "GameUpdaterDlg.h"
#include "GameUpdaterWebLoginDlg.h"
#include <string>
#include "IO.H"
#include "Updater.h"
#include "Packet\\Properties.h"

#include "vfstream.h"

extern HANDLE				g_hMutex;

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#endif

/////////////////////////////////////////////////////////////////////////////
// CGameUpdaterApp

BEGIN_MESSAGE_MAP(CGameUpdaterApp, CWinApp)
	//{{AFX_MSG_MAP(CGameUpdaterApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGameUpdaterApp construction

CGameUpdaterApp::CGameUpdaterApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGameUpdaterApp object

CGameUpdaterApp theApp;

extern bool	g_bWebLoginMode;
extern std::string	g_FutecString;
extern BYTE	g_Dimention;
extern bool g_bNetmarble;
extern bool g_bTestServer;

extern char		g_CWD[_MAX_PATH];	
/////////////////////////////////////////////////////////////////////////////


void TestSaveArgs (char *pFileName, char *Arg);

// CGameUpdaterApp initialization
bool
CGameUpdaterApp::ParsingRealServer(const char* pCommandLine)
{
	if( pCommandLine == NULL )
		return false;
	//zzi
	TestSaveArgs ("Jin2.txt", (char*)pCommandLine);
	//--

//	AfxMessageBox(pCommandLine);
	char szTemp[1024];
//	if(strlen(pCommandLine) < 9)
//		return false;

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
	g_Dimention = atoi(arg2[1]);
	
	return true;
} 

void TestSaveArgs (char *pFileName, char *Arg)
{
	std::ofstream file(pFileName, std::ios::binary);

	if (file.is_open())
	{
		file.write((const char*)Arg, strlen (Arg));
		file.close();
	}
}

BOOL CGameUpdaterApp::InitInstance()
{
	//----------------------------------------------------------
	// 하나의 application만 실행시킨다.
	//----------------------------------------------------------
	// 값 대충 넣기.. --;
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = FALSE;

	g_hMutex = CreateMutex(&sa, FALSE, "<<<Updater>>>");   

	if (GetLastError()==ERROR_ALREADY_EXISTS)
	{
		#ifdef OUTPUT_DEBUG
			if (g_pDebugMessage!=NULL)
			{
				DEBUG_ADD("Updater is Already Running..."); 
				DEBUG_ADD("--------------- Delete DebugMessageArray --------------");		
				delete g_pDebugMessage;	
				g_pDebugMessage = NULL;
			}
		#endif

		ReleaseMutex( g_hMutex );
		
		return FALSE;

//		#ifndef _DEBUG
//			return FALSE;
//			return -1;
//		#endif
	}
 
	// random seed
	srand(time(NULL));


	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	GetModuleFileName(NULL, g_CWD, _MAX_PATH);
	char *tempCut = strrchr(g_CWD, '\\');
	if(tempCut == NULL)
		return FALSE;

	*tempCut = '\0';

	SetCurrentDirectory(g_CWD);

	iovfs_base::start_vfs(FILE_DATA_PACKAGE, FS_READ);
	
	Properties NetmarbleConfig;
		
	NetmarbleConfig.load(FILE_INFO_NETMARBLE);			
	g_bNetmarble = NetmarbleConfig.getPropertyInt("Netmarble") != 0;
	
	Properties TestServerConfig;
		
	TestServerConfig.load(FILE_INFO_TESTSERVER);			
	g_bTestServer = TestServerConfig.getPropertyInt("TestServer") != 0;

	iovfs_base::end_vfs();

	if(__argc > 1)
	{
		if(!g_bNetmarble)
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
			
			//MessageBox( NULL, ::GetCommandLine(), "NewUpdate", 0 );

			ParsingRealServer( szBuf1);
		}
		else
		{
			if(__targv[2])
			{
				//test
				char strArg[256];
				wsprintf (strArg, "targv[2] : %s", __targv[2]);
				TestSaveArgs ("Jin.txt", strArg);
				//--
				g_FutecString = __targv[2];
			}
			else
			{
				//test
				char strArg[256];
				wsprintf (strArg, "__argc : %d \r\n targv[1] : %s\rwntargv[0] : %s", __argc, __targv[1], __targv[0]);
				TestSaveArgs ("Jin.txt", strArg);
				//--
				g_FutecString = __targv[1];
			}

			g_bWebLoginMode = true;
		}
	}
	
	//NowCDN Test
//	g_bWebLoginMode = g_bNetmarble = true;

	if(g_bWebLoginMode == false && g_bNetmarble == false)
	//if(0)
	{
		CGameUpdaterDlg dlg;
		m_pMainWnd = &dlg;
		int nResponse = dlg.DoModal();

		if (nResponse == IDOK)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with OK
		}
		else if (nResponse == IDCANCEL)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with Cancel
		}
	}
	else
	{
		CGameUpdaterWebLoginDlg dlg;
		m_pMainWnd = &dlg;
		int nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with OK
		}
		else if (nResponse == IDCANCEL)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with Cancel
		}
	}

	ReleaseMutex( g_hMutex );

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
