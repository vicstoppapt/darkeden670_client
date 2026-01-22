#include "StdAfx.h"
#include ".\NowCom_downenginesdk.h"



CDownEngineSDK::CDownEngineSDK(void) : m_hDownEngineAPI(NULL)
{
}

CDownEngineSDK::~CDownEngineSDK(void)
{
	if( m_hDownEngineAPI )
	{
		LPFNCLOSE			lpfnClose;
		if( lpfnClose = (LPFNCLOSE)GetProcAddress(m_hDownEngineAPI, "NOWCDN_Close") )
		{
			lpfnClose();
		}

		FreeLibrary(m_hDownEngineAPI);
	}
}

int CDownEngineSDK::Create(IN const CString& strDllPath)
{
	int nRet = 0;

	CString szLog;
	szLog.Format(_T("strDllPath = [%s] 읽기 전용 해제1\n"), strDllPath);
	OutputDebugString(szLog);

	CFileStatus fs;
	if( CFile::GetStatus(strDllPath, fs) ) 
	{
		DWORD dwAttr = GetFileAttributes((LPCTSTR)strDllPath);
		dwAttr &= ~ FILE_ATTRIBUTE_READONLY;
		SetFileAttributes((LPCTSTR)strDllPath, dwAttr);

		szLog.Format(_T("strDllPath = [%s] 읽기 전용 해제2\n"), strDllPath);
		OutputDebugString(szLog);
	}
	szLog.Format(_T("strDllPath = [%s] 읽기 전용 해제3\n"), strDllPath);
	OutputDebugString(szLog);


	if( m_hDownEngineAPI = LoadLibrary(strDllPath.operator LPCTSTR()) )
	{
		LPFNCREATE		lpfnCreate;
		if( lpfnCreate = (LPFNCREATE)GetProcAddress(m_hDownEngineAPI, "NOWCDN_Create") )
		{
			nRet = lpfnCreate(StringConvert_T2A(strDllPath));
			if( nRet == 1 ) // Update
			{
				LPFNUPDATEDLL	lpfnUpdateDll;
				if( lpfnUpdateDll = (LPFNUPDATEDLL)GetProcAddress(m_hDownEngineAPI, "NOWCDN_UpdateDLL") )
				{
					CString strZipPath = _T("[*TMP]\\downenginesdk.zip");
					CString strNewDllPath = strDllPath + _T("_NOWCDN");
					CString szLog;
					szLog.Format(_T("strZipPath = [%s] strNewDllPath = [%s]\n"), strZipPath, strNewDllPath);
					OutputDebugString(szLog);

					lpfnUpdateDll(StringConvert_T2A(strZipPath), StringConvert_T2A(strNewDllPath));

					FreeLibrary(m_hDownEngineAPI);
					m_hDownEngineAPI = NULL;
					BOOL bRet = ::DeleteFile(strDllPath);

					szLog.Format(_T("bRet[%d] = ::DeleteFile [%s]\n"), bRet, strDllPath);
					OutputDebugString(szLog);

					bRet = ::MoveFile(strNewDllPath,strDllPath);

					szLog.Format(_T("bRet[%d] = ::MoveFile [strNewDllPath:%s  strDllPath:%s]\n"), bRet, strNewDllPath,strDllPath);
					OutputDebugString(szLog);

					m_hDownEngineAPI = LoadLibrary(strDllPath.operator LPCTSTR());
	
					if( m_hDownEngineAPI == NULL )
						return -1;
					else
					{
						LPFNCREATE		lpfnCreate;
						if( lpfnCreate = (LPFNCREATE)GetProcAddress(m_hDownEngineAPI, "NOWCDN_Create") )
						{
							nRet = lpfnCreate(StringConvert_T2A(strDllPath));
							if( nRet == 1 ) // Update
							{
								return 0;
							}
						}
					}
				}
			}
		}
	}
	
	return 0;
}

int CDownEngineSDK::AutoPatchStart()
{
	int nRet = 0;
	if( m_hDownEngineAPI )
	{
		LPFNAUTOPATCHSTART lpfnAutoPatchStart;
		lpfnAutoPatchStart = (LPFNAUTOPATCHSTART)GetProcAddress(m_hDownEngineAPI, "NOWCDN_AutoPatchStart");
		if( lpfnAutoPatchStart )
		{
			nRet = lpfnAutoPatchStart();
		}
	}

	return nRet;
}

int CDownEngineSDK::SetDownloadFileInfo(IN const CString& strDownloadFullPath, IN const CString& strDownloadURL)
{
	int nRet = 0;
	if( m_hDownEngineAPI )
	{
		LPFNSETDOWNLOADFILEINFO lpfnSetDownloadInfo;
		lpfnSetDownloadInfo = (LPFNSETDOWNLOADFILEINFO)GetProcAddress(m_hDownEngineAPI, "NOWCDN_SetDownloadFileInfo");
		if( lpfnSetDownloadInfo )
		{
			nRet = lpfnSetDownloadInfo(StringConvert_T2A(strDownloadFullPath), StringConvert_T2A(strDownloadURL));
		}
	}

	return nRet;
}

int CDownEngineSDK::SetDownloadFolderInfo(IN const CString& strDownloadFolderPath, IN const CString& strDownloadURL)
{
	int nRet = 0;
	if( m_hDownEngineAPI )
	{
		LPFNSETDOWNLOADFOLDERINFO lpfnSetDownloadFolderInfo;
		lpfnSetDownloadFolderInfo = (LPFNSETDOWNLOADFOLDERINFO)GetProcAddress(m_hDownEngineAPI, "NOWCDN_SetDownloadFolderInfo");
		if( lpfnSetDownloadFolderInfo )
		{
			nRet = lpfnSetDownloadFolderInfo(StringConvert_T2A(strDownloadFolderPath), StringConvert_T2A(strDownloadURL));
		}
	}

	return nRet;
}

void CDownEngineSDK::Close()
{
	if( m_hDownEngineAPI )
	{
		LPFNCLOSE			lpfnClose;
		if( lpfnClose = (LPFNCLOSE)GetProcAddress(m_hDownEngineAPI, "NOWCDN_Close") )
		{
			lpfnClose();
		}

		FreeLibrary(m_hDownEngineAPI);
	}

}

// void CDownEngineSDK::GetDownloadInfo(OUT ULONG& ulDownCompleteCount, OUT ULONG& ulDownloadSpeed, OUT ULONGLONG& ullDownloadSize, OUT ULONG& ulExtraTime, OUT ULONG& ulLapseTime)
// {
// 	if( m_hDownEngineAPI )
// 	{
// 		LPFNGETDOWNLOADINFO		lpfnGetDownloadInfo;
// 		if( lpfnGetDownloadInfo = (LPFNGETDOWNLOADINFO)GetProcAddress(m_hDownEngineAPI, "NOWCDN_GetDownloadInfo") )
// 		{
// 			lpfnGetDownloadInfo(ulDownCompleteCount, ulDownloadSpeed, ullDownloadSize, ulExtraTime, ulLapseTime);
// 		}
// 	}
// }
//--------------------------------------------------------------------------------------------------//
// FUNCTION		:	GetDownloadInfo
// PARAMETER	:	ulDownCompleteCount		- 다운로드 완료한 파일 개수
//					ulDownloadSpeed			- 다운로드 속도
//					ullDownloadSize			- 다운로드 크기
//					ulExtraTime				- 남은 시간
//					ulLapseTime				- 경과 시간
// RETURN		:	None
// NOTE			:	다운로드 진행상황에 대한 정보를 얻는다.
//--------------------------------------------------------------------------------------------------//
void CDownEngineSDK::GetDownloadInfo(OUT ULONG* pulDownCompleteCount, OUT ULONG* pulDownloadSpeed, OUT ULONGLONG* pullDownloadSize, OUT ULONG* pulExtraTime, OUT ULONG* pulLapseTime)
{
	if( m_hDownEngineAPI )
	{
		LPFNGETDOWNLOADINFO		lpfnGetDownloadInfo;
		if( lpfnGetDownloadInfo = (LPFNGETDOWNLOADINFO)GetProcAddress(m_hDownEngineAPI, "NOWCDN_GetDownloadInfo") )
		{
			lpfnGetDownloadInfo(pulDownCompleteCount, pulDownloadSpeed, pullDownloadSize, pulExtraTime, pulLapseTime);
		}
		else
		{
			// 			OutputDebugString(_T("NOWCDN_GetDownloadInfo() 호출 실패\n"));
		}
	}
}




void CDownEngineSDK::SetParentWindow(IN void* pParentWindow)
{
	if( m_hDownEngineAPI )
	{
		LPFNSETPARENTWINDOW		lpfnSetParentWindow;
		if( lpfnSetParentWindow = (LPFNSETPARENTWINDOW)GetProcAddress(m_hDownEngineAPI, "NOWCDN_SetParentWindow") )
		{
			lpfnSetParentWindow(pParentWindow);
			//typedef void (*LPFNGETDOWNLOADINFO)(ULONG& ulDownCompleteCount, ULONG& ulDownloadSpeed, ULONGLONG& ullDownloadSize, ULONG& ulExtraTime, ULONG& ulLapseTime)
		}
	}
}

void CDownEngineSDK::SetDrawFileInfoCallback(IN void* pfnDraw)
{
	if( m_hDownEngineAPI )
	{
		LPFNSETDRAWFILEINFO		lpfnSetDrawFileInfo;
		if( lpfnSetDrawFileInfo = (LPFNSETDRAWFILEINFO)GetProcAddress(m_hDownEngineAPI, "NOWCDN_SetDrawFileInfoCallback") )
		{
			lpfnSetDrawFileInfo(pfnDraw);
		}
	}
}

void CDownEngineSDK::SetNotifyDownStartCallBack(IN void* pfnDraw)
{
	if( m_hDownEngineAPI )
	{
		LPFNUPDATESTARTBUTTON	lpfnUpdateStartButton;
		if( lpfnUpdateStartButton = (LPFNUPDATESTARTBUTTON)GetProcAddress(m_hDownEngineAPI, "NOWCDN_SetUpdateStartButtonCallBack") )
		{
			lpfnUpdateStartButton(pfnDraw);
		}
	}
}

void CDownEngineSDK::SetNotifyDownCompleteCallBack(IN void* pfnDraw)
{
	if( m_hDownEngineAPI )
	{
		LPFNNOTIFYDOWNCOMPLETE	lpfnNotifyDownComplete;
		if( lpfnNotifyDownComplete = (LPFNNOTIFYDOWNCOMPLETE)GetProcAddress(m_hDownEngineAPI, "NOWCDN_SetNotifyDownCompleteCallBack") )
		{
			lpfnNotifyDownComplete(pfnDraw);
		}
	}
}



