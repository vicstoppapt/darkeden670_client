#include "stdafx.h"
#include "UpdateManager.h"
#include "ScreenObjectInfo.h"

//zzi
#include "UpdaterVersionControl.h"
#include "GameUpdaterStringInfo.h"
//-

extern HWND		g_hWnd;
extern CString	g_StatusString;
extern RECT		g_statusRect;
//zzi
extern bool		g_bNeedPatch;

void SetStatusText(LPCTSTR text)
{
	g_StatusString = text;

	ScreenObjectInfo* pObjInfo = ScreenObjectInfo::Instance();
	CRect& rStatusRect = pObjInfo->rcStatusString;

	InvalidateRect(g_hWnd, &rStatusRect, FALSE);
}

//Nowcom
unsigned int WINAPI Update_Thread_GuildMark(void *arg)
{
	UpdateManager* pUpdateManager = static_cast<UpdateManager*>(arg);

	if (g_bNeedPatch)
	{
	/*	if(!pUpdateManager->LoadUpdateInfo())
		{
			SetStatusText("알수 없는 형식의 업데이트 정보파일입니다.");
			return -1;
		}
	*/
	//	SetStatusText("제거된 파일을 삭제하고 있습니다.");
		SetStatusText(_STR_INFO_DELETEFILES_);
		
		if(!pUpdateManager->ApplyDeletedFiles())
		{
	//		SetStatusText("업데이트가 실패하였습니다.");
			SetStatusText(_STR_FAILTOPATCH_);
			return -1;
		}
		
	// 	SetStatusText("업데이트를 적용하고 있습니다.");
 		SetStatusText(_STR_INFO_APPLYFILES_);
 		
 		if(!pUpdateManager->ApplyUpdatedFiles())
 		{
 			SetStatusText(_STR_FAILTOPATCH_);
	// 		SetStatusText("업데이트가 실패하였습니다.");
 			return -1;
 		}
		
	//	SetStatusText("패키지를 업데이트하고 있습니다.");
		SetStatusText(_STR_INFO_APPLYPACKAGE_);
		
		if(!pUpdateManager->ApplyPackingTypeChangedFiles())
		{
	//		SetStatusText("업데이트가 실패하였습니다.");
			SetStatusText(_STR_FAILTOPATCH_);
			return -1;
		}
		
		if(!pUpdateManager->ApplyFileList())
		{
	//		SetStatusText("업데이트가 실패하였습니다.");
			SetStatusText(_STR_FAILTOPATCH_);
			return -1;
		}
	}

//	SetStatusText("길드마크 버전을 확인하고 있습니다.");
	SetStatusText(_STR_CHECKGUILDMARKVERSION_);
	// 길드 버전을 체크해서 업데이트를 받아야한다면 업데이트를 받는다.
	// 길드 마크는 특성상 받지 않아도 게임하는데 큰 지장이 없기 때문에
	// 에러가 나면 그냥 무시하고 지나간다.
	bool bGuildMarkApply = false;

	if(!pUpdateManager->CheckGuildVersion())
	{
		//*
		// 길드 버전을 다운 받는다.
		if(pUpdateManager->GenerateRecentGuildID())
		{
//			SetStatusText("길드마크를 다운로드 받고 있습니다.");
			SetStatusText(_STR_DOWNLOADGUILDMARK_);

			// 길드 이미지 파일을 다운 받는다.
			bGuildMarkApply = pUpdateManager->DownloadRecentGuildMark();
		}
		//*/
	}

	// 길드마크라도 패치를 할때 에러가 나면 안된다.
	if(bGuildMarkApply)
	{
//		SetStatusText("길드마크를 업데이트하고 있습니다.");
		SetStatusText(_STR_APPLYGUILDMARK_);

		if(!pUpdateManager->ApplyGuildMark())
		{
//			SetStatusText("업데이트가 실패하였습니다.");
			SetStatusText(_STR_FAILTOPATCH_);
			return -1;
		}
	}

	// 임시 파일 삭제
//	SetStatusText("임시 파일을 삭제하고 있습니다.");
	SetStatusText(_STR_DELETETEMPFILES_);
	pUpdateManager->ClearTemporaryFile();

//	SetStatusText("업데이트가 완료되었습니다.");
	SetStatusText(_STR_INFO_COMPLETEPATCH_);

	return 0;
}

unsigned int WINAPI Update_Thread(void *arg)
{
	UpdateManager* pUpdateManager = static_cast<UpdateManager*>(arg);

	SetStatusText("攣瞳쇱꿴뫘劤륩蛟포角뤠옵痰.");

	if(!pUpdateManager->LoadUpdateInfo())
	{
		SetStatusText(_STR_UNKNOWNINFOFILE_);
		return -1;
	}

	SetStatusText(_STR_CHECKSERVERSTATUS_);

	if(!pUpdateManager->CheckUpdateStatus())
	{
		SetStatusText(_STR_FAILTOCONNECTSERVER_);
		return -1;
	}
	SetStatusText(_STR_CHECKINGVERSION_);

	if(!pUpdateManager->CheckFileListVersion())
	{
		SetStatusText(_STR_DOWNLOADINGFILEINFO_);

		if(!pUpdateManager->DownloadRecentFileList())
		{
			SetStatusText(_STR_FAILTODOWNLOADINGFILEINFO_);
			return -1;
		}

		SetStatusText(_STR_CHECKINGUPDATERPATCH_);
		
		if(!pUpdateManager->CheckUpdaterPatch())
		{
			SetStatusText(_STR_FAILTOUPDATERPATCH_);
			return -1;
		}

		SetStatusText(_STR_CHECKINGUPDATEINFO_);

		if(!pUpdateManager->GenerateUpdateFile())
		{
			SetStatusText(_STR_FAILTOCHECKINGUPDATEINFO_);
			return -1;
		}

		SetStatusText(_STR_CHECKFREEDISK_);

		if(!pUpdateManager->CheckDiskFreeSpace())
		{
			SetStatusText(_STR_NOTENOUGHFREEDIST_);
			return -1;
		}

		SetStatusText(_STR_DOWNLOADINGPATCHFILES_);

		if(!pUpdateManager->DownloadUpdatedFiles())
		{
			SetStatusText(_STR_CANNOTDOWNLOADPATCHFILES_);
			return -1;
		}
		
		SetStatusText(_STR_INFO_DELETEFILES_);
		
		if(!pUpdateManager->ApplyDeletedFiles())
		{
			SetStatusText(_STR_FAILTOPATCH_);
			return -1;
		}
		
 		SetStatusText(_STR_INFO_APPLYFILES_);
 	
 	if(!pUpdateManager->ApplyUpdatedFiles())
 	{
 		SetStatusText(_STR_FAILTOPATCH_);
 			return -1;
 		}
		
		SetStatusText(_STR_INFO_APPLYPACKAGE_);
		
		if(!pUpdateManager->ApplyPackingTypeChangedFiles())
		{
			SetStatusText(_STR_FAILTOPATCH_);
			return -1;
		}
		
		if(!pUpdateManager->ApplyFileList())
		{
			SetStatusText(_STR_FAILTOPATCH_);
			return -1;
		}
	}

	SetStatusText(_STR_DELETETEMPFILES_);
	pUpdateManager->ClearTemporaryFile();

	SetStatusText(_STR_INFO_COMPLETEPATCH_);

	return 0;
}
