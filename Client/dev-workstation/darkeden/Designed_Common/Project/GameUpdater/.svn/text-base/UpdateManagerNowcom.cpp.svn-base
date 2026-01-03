#include "stdafx.h"
#include "resource.h"
#include "GameUpdaterDlg.h"

#include "ProgressST.h"
#include "ScreenObjectInfo.h"

extern CProgressST	g_Progress;
extern CProgressST	g_ProgressTotal;
extern CString		g_StatusString;
extern RECT			g_statusRect;
extern HWND			g_hWnd;

CNowCDNUpdater::CNowCDNUpdater ()
{
	m_bRunningUpdate = false;
	m_pDlg = NULL;
	m_pfnUpdateComplete = NULL;
}

CNowCDNUpdater::~CNowCDNUpdater ()
{
	m_DownEngine.Close ();
}

void CNowCDNUpdater::SetNotifyUpdateCompleteCallBack (void (*pfnUpdateComplete)(IN void*))
{
	m_pfnUpdateComplete = pfnUpdateComplete;
//	(*m_pfnUpdateComplete) = pfnUpdateComplete;
}

void CNowCDNUpdater::ReadyToDownload ()
{
	m_DownEngine.Create (m_strDllPath);
	m_DownEngine.SetParentWindow((void*)m_pDlg);

	// DownEngineSDK로 다운로드 시작 알림을 받을 함수 포인터 전달
	m_DownEngine.SetNotifyDownStartCallBack(CGameUpdaterDlg::CallBack_Common_OnDownloadStart);
	// DownEngineSDK로 다운로드 완료 알림을 받을 함수 포인터 전달
	m_DownEngine.SetNotifyDownCompleteCallBack(CGameUpdaterDlg::CallBack_Common_OnDownloadComplete);
	// DownEngineSDK로 다운로드 대상 파일들의 정보를 받을 함수 포인터 전달
	m_DownEngine.SetDrawFileInfoCallback(CGameUpdaterDlg::CallBack_Common_OnFileInfo);
}

bool CNowCDNUpdater::RunUpdate (void* pDlg, UpdateManager *pUpdateManager, CString strWorkPath)
{
//	if (m_pfnUpdateComplete)
//		m_pfnUpdateComplete (pDlg);
//	return true;
	
	if (!pDlg || !pUpdateManager) return false;
	m_pDlg = pDlg;
	m_pUpdateManager = pUpdateManager;

	m_strDllPath = strWorkPath;
	m_strDllPath += _T("DownEngineSDK.dll");

	SetStatus ("연결중..");

	ReadyToDownload ();

	// 다운로드 할 파일들의 정보 입력( 로컬 저장 절대 경로, 다운로드 URL)
	// 버전 검사를 마친 실제 다운로드 받아야 할 게임 구성 파일들 정보 입력
	m_DownEngine.SetDownloadFileInfo("C:\\Download\\Install_MSN_Messenger_kor.exe", "nowcdn://Softon/Darkeden/Patch/PatchTest/Install_MSN_Messenger_kor.EXE");

	m_DownEngine.AutoPatchStart();

	m_bRunningUpdate = true;
	return true;
}

void CNowCDNUpdater::UpdateStepTest ()
{
	ReadyToDownload ();

	m_DownEngine.SetDownloadFileInfo("C:\\Download\\Install_MSN_Messenger_kor.exe", "nowcdn://Softon/Darkeden/Patch/PatchTest/Install_MSN_Messenger_kor.EXE");

	SetStatus ("나우콤 테스트2 중..");

	m_DownEngine.AutoPatchStart();
}

void CNowCDNUpdater::UpdateUI ()
{
	ULONG		ulDownCompleteCount = 0;
	ULONG		ulDownloadSpeed = 0;
	ULONGLONG	ullDownloadSize = 0;
	ULONG		ulExtraTime = 0;
	ULONG		ulLapseTime = 0;
	m_DownEngine.GetDownloadInfo(&ulDownCompleteCount, &ulDownloadSpeed, &ullDownloadSize, &ulExtraTime, &ulLapseTime);
	
	//ullDownloadSize 만..사용하자.
	UpdateProgress ((int)(ullDownloadSize));///1024));
}

void CNowCDNUpdater::Noti_FileInfo (IN ULONGLONG ullFileSize)
{
	m_ullFileSize = ullFileSize;
	g_Progress.SetRange32 (0, (int)(ullFileSize));///1024));
	UpdateProgress (0);		
}

void CNowCDNUpdater::Noti_Start ()
{
	SetStatus ("나우콤 테스트중..");
}

void CNowCDNUpdater::Noti_Complete (unsigned int uMsgID)
{
	//Progress바를 .. 완료버전으로..
//	UpdateProgress ((int)m_ullFileSize);
//	UpdateStepTest ();
	m_DownEngine.Close ();

	::SendMessage (g_hWnd, uMsgID, (LPARAM)m_pDlg, 0);
//	((CGameUpdaterDlg*)m_pDlg)->Start_GuildMarkUpdate ();

//	((CDialog*)m_pDlg)->SendMessage (uMsgID, 0, 0);
//	if (m_pfnUpdateComplete)
//		m_pfnUpdateComplete (m_pDlg);
	m_bRunningUpdate = false;
}

void CNowCDNUpdater::UpdateProgress (int pos)
{
	const CRect& rInvalidateRect = ScreenObjectInfo::Instance()->rcStatusString;
	g_Progress.SetPos (pos);
	InvalidateRect(g_hWnd, &rInvalidateRect, FALSE);
}

void CNowCDNUpdater::UpdateTotalProgress (int pos)
{
}

void CNowCDNUpdater::SetStatus (LPCTSTR text)
{
	g_StatusString = text;

	ScreenObjectInfo* pObjInfo = ScreenObjectInfo::Instance();
	CRect& rStatusRect = pObjInfo->rcStatusString;

	InvalidateRect(g_hWnd, &rStatusRect, FALSE);
}
