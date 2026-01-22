// MainFrm.cpp : implementation of the CMainFrame class
//

#pragma warning(disable:4786)

#include "stdafx.h"
#include "ClientInfo.h"
#include "MainFrm.h"
#include <list>
#include <string>
#include "vfstream.h"
#include <fstream>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern void		InitObject();
extern BOOL		InitClientConfig();
extern BOOL		InitAppendPatchInfo();
//extern BOOL		InitUserOption();
extern BOOL		InitInformation();
extern BOOL		InitHelpManager();
extern BOOL		InitHelpString();
extern BOOL		InitOustersPortal();
extern void		ReleaseObject();

extern bool		FileOpenBinary(const char* filename, ivfstream& file);

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	InitInfo();
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	// forward focus to the view window
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void
CMainFrame::InitInfo()
{
	InitObject();

	BOOL bResult =  InitInformation();

	if (InitClientConfig() && bResult
	//	&& InitUserOption()		
		&& InitHelpManager()
		&& InitHelpString()
		&& InitOustersPortal()
//		&& InitAppendPatchInfo()	// 이제 이 패치 방식은 사용하지 않음. AutoPatchManager20 확인 바람
		)
	{
//		AfxMessageBox("Init OK");
		CopyFiles();		
	}
	else
	{
		AfxMessageBox("Init Failed!");
	}

	ReleaseObject();
	PostQuitMessage(0);
}


static int CALLBACK BrowseForFolder_CallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
    if(uMsg == BFFM_INITIALIZED)
        SendMessage(hwnd, BFFM_SETSELECTION, (WPARAM)TRUE, (LPARAM)lpData);
    return 0;
}


void CMainFrame::CopyFiles()
{
	const char* FILE_COPY_DIRECTORY = "FileCopyDirectory.inf";

	// 예전에 선택했던 디렉토리를 불러온다.
	char defaultDirectory[MAX_PATH];
	memset(defaultDirectory, 0, MAX_PATH);

	std::ifstream fileCopyDirectoryInput(FILE_COPY_DIRECTORY);
	if(fileCopyDirectoryInput.is_open())
	{
		fileCopyDirectoryInput.getline(defaultDirectory, MAX_PATH);
		fileCopyDirectoryInput.close();
	}

	// 디렉토리 선택 창을 띄운다.
	ITEMIDLIST *pildBrowse;

	char pszPathname[MAX_PATH];

	BROWSEINFO bInfo;

	memset( &bInfo, 0, sizeof(bInfo));

	bInfo.hwndOwner = GetSafeHwnd();
	bInfo.pidlRoot = NULL;
	bInfo.pszDisplayName = pszPathname;
	bInfo.lpszTitle = "완성된 Info 파일을 복사할 디렉토리를 선택하세요.";
	bInfo.ulFlags = BIF_RETURNONLYFSDIRS;

	if(strlen(defaultDirectory) != 0)
	{
		bInfo.lpfn = BrowseForFolder_CallbackProc;
		bInfo.lParam = (LPARAM)(LPCSTR)defaultDirectory;
	}

	pildBrowse = ::SHBrowseForFolder(&bInfo);

	if(pildBrowse == NULL) return;

	SHGetPathFromIDList(pildBrowse, pszPathname);
	
	// 방금 선택한 디렉토리를 다시 저장
	std::ofstream fileCopyDirectoryOut(FILE_COPY_DIRECTORY);
	
	if(fileCopyDirectoryOut.is_open())
	{
		fileCopyDirectoryOut << pszPathname;
		fileCopyDirectoryOut.close();
	}


//	SetCurrentDirectory(pszPathname);

	std::list<std::string> CopyList;
	
	std::string filename;

	filename = "Data\\Info\\Skill.inf";
	CopyList.push_back( filename );
	filename = "Data\\Info\\levelname.inf";
	CopyList.push_back( filename );
	filename = "Data\\Info\\horn.inf";
	CopyList.push_back( filename );
	filename = "Data\\Info\\effectstatus.inf";
	CopyList.push_back( filename );
	filename = "Data\\Info\\Action.inf";
	CopyList.push_back( filename );
	filename = "Data\\Info\\NPC.inf";
	CopyList.push_back( filename );
	filename = "Data\\Info\\CreatureSpriteManager.inf";
	CopyList.push_back( filename );
	filename = "Data\\Info\\CreatureSprite.inf";
	CopyList.push_back( filename );
	filename = "Data\\Info\\Gps.inf";
	CopyList.push_back( filename );
	filename = "Data\\Info\\Creature.inf";
	CopyList.push_back( filename );
	filename = "Data\\Info\\Zone.inf";
	CopyList.push_back( filename );
	filename = "Data\\Info\\String.inf";
	CopyList.push_back( filename );
	filename = "Data\\Info\\Sound.inf";
	CopyList.push_back( filename );
	filename = "Data\\Info\\RankBonus.inf";
	CopyList.push_back( filename );
	filename = "Data\\Info\\Music.inf";
	CopyList.push_back( filename );
	filename = "Data\\Info\\Item.inf";
	CopyList.push_back( filename );
	filename = "Data\\Info\\EffectSpriteType.inf";
	CopyList.push_back( filename );
	filename = "Data\\Info\\ActionEffectSpriteType.inf";
	CopyList.push_back( filename );
	filename = "Data\\Info\\SHelpString.inf";
	CopyList.push_back( filename );
	filename = "Data\\Info\\SHelp.inf";
	CopyList.push_back( filename );
	filename = "Data\\Info\\ClientConfig.inf";
	CopyList.push_back( filename );

//	filename = "Data\\Info\\Chat.inf";
//	CopyList.push_back( filename );
//	filename = "Data\\Info\\chat2.inf";
//	CopyList.push_back( filename );

//	filename = "Data\\Info\\AppendPatch.inf";
//	CopyList.push_back( filename );

// 	filename = "Data\\Image\\Effect.efpk";
// 	CopyList.push_back( filename );
// 	filename = "Data\\Image\\EffectScreen.efpk";
// 	CopyList.push_back( filename );
	

	std::list<std::string>::const_iterator Itr = CopyList.begin();
	std::list<std::string>::const_iterator endItr = CopyList.end();
	
	while( Itr != endItr )
	{
		std::string SourceFiles = *Itr;
		std::string TargetPath = pszPathname;
		//std::string TargetPath = "C:\\Program Files\\DarkEdenTest\\";
		
		TargetPath += "\\";
		TargetPath += *Itr;

		CopyFile( SourceFiles.c_str(), TargetPath.c_str(), FALSE );
		Itr++;
	}
}
