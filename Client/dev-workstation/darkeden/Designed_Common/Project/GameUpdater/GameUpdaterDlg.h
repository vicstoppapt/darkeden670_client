// NewUpdater2Dlg.h : header file
//
//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES

#if !defined(AFX_NEWUPDATER2DLG_H__1A5AA50F_EB7A_4E75_809E_9EAB4E225EBB__INCLUDED_)
#define AFX_NEWUPDATER2DLG_H__1A5AA50F_EB7A_4E75_809E_9EAB4E225EBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyComboBox.h"
#include "ScreenObjectInfo.h"
#include "UpdateManager.h"

//#include "UpdateManagerNowcom.h"
//#include "NowCom_DownEngineSDK.h"

//#include "BMMTimer.h"

class UpdateManager;

struct DibBitmap
{
	CBitmap		bitmap;
	CPalette	palette;
	SIZE		size;
};

#define UM_UPDATE_COMPLETE	(WM_USER + 1)

/////////////////////////////////////////////////////////////////////////////
// CGameUpdaterDlg dialog

class CGameUpdaterDlg : public CDialog
{
// Construction
public:
	CGameUpdaterDlg(CWnd* pParent = NULL);	// standard constructor
	~CGameUpdaterDlg();

	bool		Init();
	void		Release();

	void		Connect();

//Now CDN 
	bool			CheckNowDN_DllFile ();		//Now Dll이 로컬에 존재하는 지 체크. 없으면.. 효성에서 다운로딩한다.

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
	void			UpdatePatchStatus (LPCTSTR text);

	static void		mmTimerCallback ();
	void			Start_Timer ();
	void			End_Timer ();
	void			Start_GuildMarkUpdate ();
//-

	// 배경 이미지
	DibBitmap	m_dibBackground;

	// 버튼 이미지
	DibBitmap	m_dibFocusButton[ScreenObjectInfo::BTN_MAX];
	bool		m_bFocus[ScreenObjectInfo::BTN_MAX];

	// 버전 숫자 이미지
	DibBitmap	m_dibVersionNum[ScreenObjectInfo::VERNUM_MAX];

	DibBitmap	m_dibRadioSelected;
	DibBitmap	m_dibWindowSelected;

	CFont		m_hStatusFont, m_hStatusFont2, m_hVersionFont;

	bool		m_bDragWindow;		// 드래그 중인가?
	CPoint		m_ptPickPostion;	// 드래그 할때 마우스를 클릭한 위치

	UpdateManager	m_UpdateManager;

	//Nowcom			-- NowCDNUpdate를 사용하는 방법은.. 추후, 시간이 허용할 때.. 다시 시도해 보자.
	//					-- 일단, (시간이 읍다ㅠㅠ) 여기서, 처리하는 방법으로.. ㅡ.,ㅡ;;
//	CNowCDNUpdater	m_UpdateManagerNowcom;
	CDownEngineSDK	m_DownEngine;
//	int				m_NowCDN_NextStep;
	CString			m_NowDllPath;

//	CMMTimer		m_mmTimer;
	
//--

	bool		m_bUpdateRunning;

	bool		m_bFullScreen;
	int		m_nResolutionX, m_nResolutionY;

	HANDLE		m_hWorkThread;
	DWORD		m_dwWorkThreadID;

	HANDLE		m_hThreadCheckTimer;

// Dialog Data
	//{{AFX_DATA(CGameUpdaterDlg)
	enum { IDD = IDD_NEWUPDATER2_DIALOG };
	CWebBrowser2	m_Explorer;
	//}}AFX_DATA

	// by svi
	CComboBox m_cmbProxyList;
	CComboBox m_cmbResoulvList;

	std::vector<std::string> m_strTunnelList;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGameUpdaterDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	//----------------------------------------------------------
	// 해상도 정보를 로드/세이브한다.
	//----------------------------------------------------------
	void InitResolutionConfig();
	void SaveResolutionConfig();

	void SetStatusString(const char* message);


	// Generated message map functions
	//{{AFX_MSG(CGameUpdaterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHomepage();
	afx_msg void OnNewUser();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDocumentCompleteExplorer(LPDISPATCH pDisp, VARIANT FAR* URL);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LRESULT OnUpdateComplete(WPARAM wParam,LPARAM lParam);
	afx_msg void OnCheckFull();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWUPDATER2DLG_H__1A5AA50F_EB7A_4E75_809E_9EAB4E225EBB__INCLUDED_)
