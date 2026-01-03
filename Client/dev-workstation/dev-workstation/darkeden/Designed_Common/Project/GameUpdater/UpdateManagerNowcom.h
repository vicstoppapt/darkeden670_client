#ifndef __UPDATEMANAGERNOWCOM_H__
#define __UPDATEMANAGERNOWCOM_H__

#include "NowCom_DownEngineSDK.h"
#include "UpdateManager.h"

class CNowCDNUpdater
{
public:
	//typedef void (*UPDATECOMPELTE_CALLBACK)(IN void*);

	CNowCDNUpdater ();
	~CNowCDNUpdater ();

	void			SetNotifyUpdateCompleteCallBack (void (*pfnUpdateComplete)(IN void*) );
	bool			RunUpdate (void *pDlg, UpdateManager *pUpdateManager, CString strWorkPath);
	void			ReadyToDownload ();							// Download받을 때마다.. 호출되는 녀석. -_-;; 느리게 하는 원흉이다.

	void			UpdateStepTest ();

	bool			IsRunning () { return m_bRunningUpdate; }
//FrameWork
	void			Noti_FileInfo (IN ULONGLONG ullFileSize);
	void			Noti_Start ();
	void			Noti_Complete (unsigned int uMsgID);
//Update UI
	void			UpdateUI ();
	void			SetStatus (LPCTSTR text);
	void			UpdateProgress (int pos);
	void			UpdateTotalProgress (int pos);

protected:
	CDownEngineSDK	m_DownEngine;
	UpdateManager*	m_pUpdateManager;

	//UPDATECOMPELTE_CALLBACK m_pfnUpdateComplete;
	void (*m_pfnUpdateComplete)(IN void*);

	CString			m_strDllPath;
	void*			m_pDlg;
	bool			m_bRunningUpdate;

//Downloading Infos
	IN ULONGLONG	m_ullFileSize;
};

#endif