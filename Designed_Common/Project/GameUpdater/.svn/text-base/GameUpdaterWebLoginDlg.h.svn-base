// NewUpdater2Dlg.h : header file
//
//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES

#if !defined(_AFX_NEWUPDATER2DLG_H__1A5AA50F_EB7A_4E75_809E_9EAB4E225EBB__INCLUDED_)
#define _AFX_NEWUPDATER2DLG_H__1A5AA50F_EB7A_4E75_809E_9EAB4E225EBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma warning(disable:4006)

#include "GameUpdaterDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CGameUpdaterDlg dialog

class CGameUpdaterWebLoginDlg : public CDialog
{
// Construction
public:
	bool ParsingRealServer(const char* pCommandLine);
	CGameUpdaterWebLoginDlg(CWnd* pParent = NULL);	// standard constructor
	~CGameUpdaterWebLoginDlg();

	void		Release();
	bool		Init();
	void		Connect();
	int			m_nDimention;
	
	DibBitmap	m_dibBackground;
	DibBitmap	m_dibExitHilight;

	bool		m_bFocusExit;
	bool		m_bPushExit;
	
	RECT		m_rtFocusExit;

	UpdateManager	m_UpdateManager;

//Nowcom
	CDownEngineSDK	m_DownEngine;
	CString			m_NowDllPath;
//--
	
	bool		m_bUpdateRunning;
	
	HANDLE		m_hWorkThread;
	DWORD		m_dwWorkThreadID;
	
	HANDLE		m_hThreadCheckTimer;

	CFont m_hStatusFont, m_hStatusFont2, m_hVersionFont;

// Dialog Data
	//{{AFX_DATA(CGameUpdaterDlg)
	enum { IDD = IDD_NEW_UPDATER3_DLG };
//	CWebBrowser2	m_Explorer;
//	CWebBrowser2	m_ExplorerBanner;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGameUpdaterDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

//Now CDN 
	bool			NowDN_Start ();
	bool			NowDN_Init ();
	void			NowDN_Error (LPCTSTR text);
	void			NowDN_Complete ();			//Now Dll을 이용한 다운로드 완료후의 처리... 

	void			Complete_Patch ();			//완료!! 패치할 필요가 없다. --> darkeden.exe 실행
	void			Complete_UpdaterPatch ();	//완료!! Updater 패치 완료처리. --> exeswaper.exe 실행.

	void			NowDN_Step1 ();		//Status
	static void		CallBack_Status_OnFileInfo(IN void* pThisPointer, IN CHAR* pszFileNameA, IN WCHAR* pszFileNameW, IN ULONG ulFileTotalCount, IN ULONGLONG ullFileSize, IN ULONG ulCPCode, IN ULONG ulGameCode, IN ULONG ulFileID, IN ULONG ulFileType);
	static void		CallBack_Status_OnDownloadStart(IN void* pThisPointer);
	static void		CallBack_Status_OnDownloadComplete(IN void* pThisPointer);

	void			NowDN_Step2 ();		//FileListVersion
	static void		CallBack_FileListVersion_OnFileInfo(IN void* pThisPointer, IN CHAR* pszFileNameA, IN WCHAR* pszFileNameW, IN ULONG ulFileTotalCount, IN ULONGLONG ullFileSize, IN ULONG ulCPCode, IN ULONG ulGameCode, IN ULONG ulFileID, IN ULONG ulFileType);
	static void		CallBack_FileListVersion_OnDownloadStart(IN void* pThisPointer);
	static void		CallBack_FileListVersion_OnDownloadComplete(IN void* pThisPointer);

	void			NowDN_Step3 ();		//FileList Down
	static void		CallBack_FileList_OnFileInfo(IN void* pThisPointer, IN CHAR* pszFileNameA, IN WCHAR* pszFileNameW, IN ULONG ulFileTotalCount, IN ULONGLONG ullFileSize, IN ULONG ulCPCode, IN ULONG ulGameCode, IN ULONG ulFileID, IN ULONG ulFileType);
	static void		CallBack_FileList_OnDownloadStart(IN void* pThisPointer);
	static void		CallBack_FileList_OnDownloadComplete(IN void* pThisPointer);

	void			NowDN_Step4 ();		//Updater Patch
	static void		CallBack_UpdaterPatch_OnFileInfo(IN void* pThisPointer, IN CHAR* pszFileNameA, IN WCHAR* pszFileNameW, IN ULONG ulFileTotalCount, IN ULONGLONG ullFileSize, IN ULONG ulCPCode, IN ULONG ulGameCode, IN ULONG ulFileID, IN ULONG ulFileType);
	static void		CallBack_UpdaterPatch_OnDownloadStart(IN void* pThisPointer);
	static void		CallBack_UpdaterPatch_OnDownloadComplete(IN void* pThisPointer);

	void			NowDN_Step5 ();		//Updated Files Down
	static void		CallBack_UpdatedFileDown_OnFileInfo(IN void* pThisPointer, IN CHAR* pszFileNameA, IN WCHAR* pszFileNameW, IN ULONG ulFileTotalCount, IN ULONGLONG ullFileSize, IN ULONG ulCPCode, IN ULONG ulGameCode, IN ULONG ulFileID, IN ULONG ulFileType);
	static void		CallBack_UpdatedFileDown_OnDownloadStart(IN void* pThisPointer);
	static void		CallBack_UpdatedFileDown_OnDownloadComplete(IN void* pThisPointer);

	void			NowDN_UpdateUI ();
	void			UpdateProgress ();//(int pos);
	void			UpdateTotalProgress ();//(int pos);

	static void		mmTimerCallback ();
	void			Start_Timer ();
	void			End_Timer ();
	void			Start_GuildMarkUpdate ();
//-

protected:
	HICON m_hIcon;

	//NowCDN
	void SetStatusString(const char* message);
	//--

	// Generated message map functions
	//{{AFX_MSG(CGameUpdaterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_AFX_NEWUPDATER2DLG_H__1A5AA50F_EB7A_4E75_809E_9EAB4E225EBB__INCLUDED_)
