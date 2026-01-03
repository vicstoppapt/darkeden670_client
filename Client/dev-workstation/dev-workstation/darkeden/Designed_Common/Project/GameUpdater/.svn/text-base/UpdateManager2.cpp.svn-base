//2007 - Nowcom 관련 함수들을 따로 묶기 위해, cpp파일을 새로 만든다.

#include "stdafx.h"

#include "Updater.h"
#include "UpdateManager.h"
#include "Properties.h"

#include "APM_Macro.h"
#include "FileCheckInfoTable.h"

#include "MInternetConnection.h"

#include "PatchDataHeader.h"

#include "PatchDataHeader.h"

#include "zlib.h"

#include "vfstream.h"

// Guild Mark Dependencies
#include "MGuildMarkManager.h"
#include "MGuildInfoMapper.h"
#include "CDirectDraw.h"

#include "MD5/MD5Checksum.h"

#include "VFS_Macro.h"

#include "UpdateManagerThread.h"

//zzi
#include "UpdaterVersionControl.h"
#include "GameUpdaterStringInfo.h"
//-

#define USE_PROGRESS
#define RETRY_MAX	5

#ifdef USE_PROGRESS
	#include "ProgressST.h"
	#include "ScreenObjectInfo.h"

	extern HWND				g_hWnd;
	extern CProgressST		g_Progress;
	extern CProgressST		g_ProgressTotal;
#endif


void UpdateManager::SetRootPath (TCHAR *strPath)
{
	m_strRootPath = strPath;
}

//NowDN_DownEngineSDK Dll은 효성CDN에서 받는다.
//	임시적인 처리방법이다. 효성CDN이 닫히기 전까지만 사용될 예정이다.
//	효성CDN이 닫힌 후에는.. 수동패치를 할 수 밖에 없다.
bool UpdateManager::DownloadFile_NowDN_Dll (CString dllFileName)
{
	/*
	std::string strWebFilePath = m_strHyosungDownloadPath + '/' + (LPCTSTR)dllFileName;
	std::string strDownFilePath = m_strRootPath + '/' + (LPCTSTR)dllFileName;

	for(int i = 0; i < RETRY_MAX; ++i)
	{
		MInternetFile internetFile (strWebFilePath.c_str(), strDownFilePath.c_str ());

		if (internetFile.IsOpen())
		{		
			while (internetFile.Update ())
			{
			}
			internetFile.Flush();
				
			// 파일을 끝까지 잘 받았는지 확인
			if(internetFile.GetFileSize() != internetFile.GetReceivedSize())
			{
				// 파일 크기가 틀리다면 지우고 다시 시도
				Assert("internetFile.GetFileSize() != internetFile.GetReceivedSize()" && FALSE);
				DeleteFile(strDownFilePath.c_str ());
				continue;
			}

			return true;
		}
		//retry
	}
	return false;*/
	return true;
}

// -- HttpUrl를 임시적으로 나우콤 Url로 하드코딩한다.
// -- 나우콤CDN 적용의 안정기에는 다시 Url를 inf파일에서 로딩하는 것으로 회귀할 수 있을 것이다.
// -- Url이 테섭, 개발섭, 본섭등 각각에 따른 Url로 빌드되어야 한다.
bool UpdateManager::LoadUpdateInfo_NowCom ()
{
	iovfs_base::start_vfs(FILE_DATA_PACKAGE, FS_READ);

	bool bOK = true;

	//나우콤CDN
	std::string strNowDN_Url				= "nowcdn://Softon/Darkeden/";				//URL

//	std::string strNowDN_DataDir			= "Patch/DevServer";						//개발섭용
//	std::string strNowDN_GuildMarkDataDir	= "Patch/guildMark/TestServer";				//개발섭용

//	std::string strNowDN_DataDir			= "Patch/TestServer";						//테섭용
//	std::string strNowDN_GuildMarkDataDir	= "Patch/guildMark/TestServer";				//테섭용

	std::string strNowDN_DataDir			= "Patch/RealServer";						//본섭용
//	std::string strNowDN_GuildMarkDataDir	= "Patch/guildMark/RealServer";				//본섭용

//Mirror Real Server
//	std::string strNowDN_DataDir			= "Patch/RealServer_Mirror";						//본섭용_Mirror
//	std::string strNowDN_GuildMarkDataDir	= "Patch/guildMark/RealServer";				//본섭용_Mirror

	try
	{
		Properties UpdateInfo(FILE_INFO_UPDATECLIENT);
		UpdateInfo.load();

		std::string strHttpUrl		= UpdateInfo.getProperty("HttpUrl");
		std::string strDataDir		= UpdateInfo.getProperty("DataDir");
		std::string strGuildDataDir = UpdateInfo.getProperty("GuildDataDir");
//		m_strDownloadPath			= "http://" + strHttpUrl + "/" + URL_RECENT_PATCH_DATA_ROOT + "/" + strDataDir;
		m_strGuildDownloadPath		= "http://" + strHttpUrl + "/" + URL_RECENT_GUILDMARK_DATA_ROOT + "/" + strGuildDataDir;

		//NowCon용...으로 재설정. 길드마크는 종전처럼 효성cdn에서 받는다.
		m_strDownloadPath			= strNowDN_Url + strNowDN_DataDir;

		//TempDir 와 UpdateStatus 는 inf의 것을 그대로 사용.
		m_strUpdateTempDir			= UpdateInfo.getProperty("UpdateTempDir");
		m_strUpdateStatus			= UpdateInfo.getProperty("UpdateStatusFile");

		//Temp - Hyosung CDN Path
//		m_strHyosungDownloadPath	= "http://" + strHttpUrl + "/" + URL_RECENT_PATCH_DATA_ROOT + "/" + strDataDir;
//		m_strHyosungDownloadPath	= "http://darkeden/RecentPatchData/DevServer";
	}
	catch (...)
	{
		ShowErrorMessage("업데이트 정보를 읽던 중 오류가 발생하였습니다.");
		bOK = false;
	}

	iovfs_base::end_vfs();

	return bOK;
}

//DownLoad Test
bool UpdateManager::ReadyTestDownload (CDownEngineSDK* pDownEngine)
{
	if (!pDownEngine) return false;

	std::string strTestFileName = "NowCDN_TestFile.dat";

	std::string strWebFilePath = m_strDownloadPath + "/" + strTestFileName;
	std::string strDownFilePath = m_strRootPath + '/' + m_strUpdateTempDir + "/" + strTestFileName;

	CString strWebFilePath_ = strWebFilePath.c_str ();
	CString strDownFilePath_ = strDownFilePath.c_str ();

	pDownEngine->SetDownloadFileInfo (strDownFilePath_, strWebFilePath_);
	return true;
}

bool UpdateManager::CheckTestDownload ()
{
	return true;
}

//CheckUpdateStatus
bool UpdateManager::ReadyCheckUpdateStauts_NowCom (CDownEngineSDK *pDownEngine)
{
	if (!pDownEngine) return false;

	std::string strWebFilePath = m_strDownloadPath + "/" + m_strUpdateStatus;
	std::string strDownFilePath = m_strRootPath + '/' + m_strUpdateTempDir + "/" + m_strUpdateStatus;

	CString strWebFilePath_ = strWebFilePath.c_str ();
	CString strDownFilePath_ = strDownFilePath.c_str ();

	pDownEngine->SetDownloadFileInfo (strDownFilePath_, strWebFilePath_);
	return true;
}

bool UpdateManager::CheckUPdateStatus_NowCom ()
{
	std::string strDownFilePath = m_strRootPath + '/' + m_strUpdateTempDir + "/" + m_strUpdateStatus;
	BOOL bOpen = FALSE;

	Properties UpdateStatusInfo(strDownFilePath);
	UpdateStatusInfo.load();

	try
	{
		bOpen = UpdateStatusInfo.getPropertyInt("UpdateStatus");
	}
	catch (...)
	{
		bOpen = FALSE;
	}

//	bOpen = TRUE;

	// 체크가 끝났다면 삭제
	DeleteFile(strDownFilePath.c_str());
	return bOpen != FALSE;
}

//CheckFileListVersion
bool UpdateManager::ReadyCheckFileListVersion (CDownEngineSDK *pDownEngine)
{
	if (!pDownEngine) return false;

	std::string strWebFilePath = m_strDownloadPath + "/" + FILE_INFO_RECENT_FILE_LIST_VERSION;
	std::string strDownFilePath = m_strRootPath + '/' + m_strUpdateTempDir + "/" + FILE_INFO_RECENT_FILE_LIST_VERSION;

	CString strWebFilePath_ = strWebFilePath.c_str ();
	CString strDownFilePath_ = strDownFilePath.c_str ();

	pDownEngine->SetDownloadFileInfo (strDownFilePath_, strWebFilePath_);
	return true;
}

bool UpdateManager::CheckFileListVersion_NowCom (bool *bNeedPatch)
{
	*bNeedPatch = false;

	std::string strDownFilePath = m_strRootPath + '/' + m_strUpdateTempDir + "/" + FILE_INFO_RECENT_FILE_LIST_VERSION;

	// 최신 버전 파일을 잘 다운 받았는지 확인한다.
	if(access(strDownFilePath.c_str(), 0))
		return false;
	
	// 최신 버전 파일을 읽어온다.
	FileCheckInfo recentVersion;

	std::ifstream fileRecentVersion(strDownFilePath.c_str(), std::ios_base::binary);

	if(!fileRecentVersion.is_open())
	{
		return false;
	}

	recentVersion.LoadFromFile(fileRecentVersion);
	fileRecentVersion.close();

	// 현재 클라이언트의 버전을 읽어온다.

	FileCheckInfo myVersion;

	std::ifstream fileMyVersion(FILE_INFO_FILE_LIST_VERSION, std::ios_base::binary);

	if(!fileMyVersion.is_open())
	{
		return false;
	}

	myVersion.LoadFromFile(fileMyVersion);
	fileMyVersion.close();
	
	if (!recentVersion.IsFileDataIdentical(myVersion))
		*bNeedPatch = true;
	return true;
//	return recentVersion.IsFileDataIdentical(myVersion);
}

//DownLoadRecentFileList
bool UpdateManager::ReadyDownloadRecentFileList (CDownEngineSDK *pDownEngine)
{
	if (!pDownEngine) return false;

	std::string strWebFilePath = m_strDownloadPath + "/" + FILE_INFO_RECENT_FILE_LIST;
	std::string strDownFilePath = m_strRootPath + '/' + m_strUpdateTempDir + "/" + FILE_INFO_RECENT_FILE_LIST;

	CString strWebFilePath_ = strWebFilePath.c_str ();
	CString strDownFilePath_ = strDownFilePath.c_str ();

	pDownEngine->SetDownloadFileInfo (strDownFilePath_, strWebFilePath_);
	return true;
}

bool UpdateManager::DownloadRecentFileList_NowCom ()
{
	std::string strDownFilePath = m_strRootPath + '/' + m_strUpdateTempDir + "/" + FILE_INFO_RECENT_FILE_LIST;

	m_RecentFiles.clear();
	m_LocalFiles.clear();

	if(!access(strDownFilePath.c_str(), 0) && !access(FILE_INFO_FILE_LIST, 0))
	{
		LoadCompressFileCheckInfoTable(m_RecentFiles, strDownFilePath.c_str());
		LoadCompressFileCheckInfoTable(m_LocalFiles, FILE_INFO_FILE_LIST);
	}

	return true;
}

//Check Updater Patch --
bool UpdateManager::CheckUpdaterPatch_NowCom (CDownEngineSDK *pDownEngine)
{
	if (!pDownEngine) return false;

	// 각각의 FileCheckInfoTable에서 Updater를 찾는다.
	FileCheckInfoTable::const_iterator findRecentIter = m_RecentFiles.find(UPDATER_FILENAME);
	FileCheckInfoTable::const_iterator findLocalIter = m_LocalFiles.find(UPDATER_FILENAME);

	if(findRecentIter != m_RecentFiles.end() &&
	   findLocalIter != m_LocalFiles.end())
	{
		const FileCheckInfo& findRecentFileCheckInfo = findRecentIter->second;
		const FileCheckInfo& findLocalFileCheckInfo = findLocalIter->second;

		// Updater가 바뀌었는지 확인
		if(!findLocalFileCheckInfo.IsFileDataIdentical(findRecentFileCheckInfo))
		{
			//여기서, 다운로드 할 파일을 설정한다.
			// 새로운 Updater를 다운로드 받는다.
			std::string strUpdateFilePath	= UPDATER_FILENAME;
			strUpdateFilePath += PATCH_DATA_EXT;
			
			std::string strWebFilePath		= m_strDownloadPath + "/" + strUpdateFilePath;
			std::string strDownFilePath		= m_strRootPath + '/' + m_strUpdateTempDir + "/" + strUpdateFilePath;

			CString strWebFilePath_ = strWebFilePath.c_str ();
			CString strDownFilePath_ = strDownFilePath.c_str ();
			
			pDownEngine->SetDownloadFileInfo (strDownFilePath_, strWebFilePath_);
			return true;
		}
	}
	return false;
}

// Download 받아 놓은.. Updater파일을 RealData로 생성한 후에, Updater2.exe로 저장한다.
// 이후, 새로운 Updater의 FileCheckInfo를 Local상의 FileList에 복사 한 후에, 저장한다.
// 새로운 FileList (위에서 갱신한)의 version를 갱신 한 후에 저장한다.
// 이제, Updater자체를 다시 실행 해야 한다. return true로... 처리한다.
bool UpdateManager::DoUpdaterPatch ()
{
	//다운로드 받은 Updater파일의 경로를 다시 잡는다. -_-;;
	std::string strUpdateFilePath	= UPDATER_FILENAME;
	strUpdateFilePath += PATCH_DATA_EXT;
	std::string strDownFilePath		= m_strRootPath + '/' + m_strUpdateTempDir + "/" + strUpdateFilePath;

	//이제, 다운받은 파일을 RealData로 생성한다. 
	RealData newUpdater;

	if(!newUpdater.Create(strDownFilePath.c_str(),
		(int)hash_func_path_string_stlport()(UPDATER_FILENAME)))
	{
		return false;			//생성 실패!! --> 이 함수를 호출한 쪽에서.. 에러처리.
	}

	//다운받은 파일을 Updater2.exe로 저장한다.
	std::ofstream fileNewUpdater(UPDATER_NEW_FILENAME, std::ios_base::binary);
	fileNewUpdater.write((const char *)newUpdater.m_pData, newUpdater.m_nSize);
	fileNewUpdater.close();

	newUpdater.Destory();

	// 파일이 생성됐는지 확인			
	if(access(UPDATER_NEW_FILENAME, 0))
	{
//		ShowErrorMessage("업데이트 패치를 하던중 오류가 발생하였습니다.", UPDATER_NEW_FILENAME);
		ShowErrorMessage(_STR_ERROR_DOWNLOADINGUPDATER_, UPDATER_NEW_FILENAME);
		return false;
	}

	// 각각의 FileCheckInfoTable에서 Updater를 찾는다.
	FileCheckInfoTable::const_iterator findRecentIter = m_RecentFiles.find(UPDATER_FILENAME);
	FileCheckInfoTable::const_iterator findLocalIter = m_LocalFiles.find(UPDATER_FILENAME);

	// 새로운 Updater FileCheckInfo를 복사후 저장
	m_LocalFiles[UPDATER_FILENAME] = findRecentIter->second;
	SaveCompressFileCheckInfoTable(m_LocalFiles, FILE_INFO_FILE_LIST);

	// 새로운 Version 저장
	FileCheckInfo FileListVersion(FILE_INFO_FILE_LIST);

	std::ofstream fileVersion(FILE_INFO_FILE_LIST_VERSION, std::ios_base::binary);

	// 파일이름은 안 넣어도 되는데 과거 Updater와의 호환성을 위해 ㅠ _ㅠ
	int nameLength = static_cast<int>(strlen(FILE_INFO_FILE_LIST_VERSION));
	fileVersion.write((const char *)&nameLength, sizeof(int));
	fileVersion.write((const char *)FILE_INFO_FILE_LIST_VERSION, nameLength);

	FileListVersion.SaveToFile(fileVersion);
	fileVersion.close();

	// thread를 종료한다. == NowDN 모드? 에서는 아직 쓰레드를 실행시키지 않았다.
//	_endthreadex(EXITCODE_UPDATER_PATCH);

	return true;		//성공을 리턴한다.
}

//Download Updated Files
//	- FileCount : 기존에 받아놓은 파일들에 의해, 실재 다운로드할 파일 수는 0일 수도 있다.
//				Now Dll은 다운받을 파일 수가 0일 경우, ㅡㅡ; 미궁에 빠진다.
//				때문에, 인자로.. 실재 다운로드 받을 파일 수를 넘겨주도록 하여, 이 함수의 호출부에서 참조하도록 한다.
bool UpdateManager::ReadyDownloadUpdatedFiles (CDownEngineSDK *pDownEngine, int *FileCount)
{
	if (!pDownEngine) return false;

	//FileCheckInfoTable failedCheckInfoTable;
#ifdef USE_PROGRESS
#endif

	// 순차적인 다운로드에 생기는 부하를 줄이기위해 랜덤으로 다운로드 순서를 정해준다.
//	FILECHECKINFO_VEC RandomUpdatedFiles(m_UpdatedFiles.begin(), m_UpdatedFiles.end());
//	std::random_shuffle(RandomUpdatedFiles.begin(), RandomUpdatedFiles.end());

	//////////////////////////////////////////////////////////////////////////
	// 파일 다운로드

//** NowDN Dll에서 알아서.. 섞어 준단다.
	
//	FILECHECKINFO_VEC::iterator updatedFilesIter = RandomUpdatedFiles.begin();
	FileCheckInfoTable::iterator updatedFilesIter = m_UpdatedFiles.begin ();
	
//	for(; updatedFilesIter != RandomUpdatedFiles.end(); ++updatedFilesIter)
	for(; updatedFilesIter != m_UpdatedFiles.end(); ++updatedFilesIter)
	{
		const std::string& updateFileName = updatedFilesIter->first;
		const FileCheckInfo& updateFileCheckInfo = updatedFilesIter->second;

		std::string strUpdateFilePath	= updateFileName;
		strUpdateFilePath += PATCH_DATA_EXT;
		
		std::string strWebFilePath		= m_strDownloadPath + "/" + strUpdateFilePath;
		std::string strDownFilePath		= m_strRootPath + '/' + m_strUpdateTempDir + "/" + strUpdateFilePath;

		bool bNeedDownload = true;

		// 파일이 있다면 맞는 파일인지 확인
		if(!access(strDownFilePath.c_str(), 0))
		{
			RealData realData;

			if(realData.Create(strDownFilePath.c_str(),
				(int)hash_func_path_string_stlport()(updateFileName.c_str())))
			{
				// 일단 파일 크기가 같아야 한다.
				if(realData.m_nSize == updateFileCheckInfo.GetFileSize())
				{
					// md5를 체크해본다.
					std::string md5 = CMD5Checksum::GetMD5((BYTE*)realData.m_pData, realData.m_nSize);
			
					if(!memcmp(md5.c_str(), updateFileCheckInfo.GetMD5CheckSum(), FileCheckInfo::CHECKSUM_SIZE))
					{
						bNeedDownload = false;
					}
				}
			}
		}
		
		// 파일이 없다면 인자로 넘어온 DonwEngine에 .. 다운받을 파일 설정.
		if(bNeedDownload)
		{
			CString strWebFilePath_ = strWebFilePath.c_str ();
			CString strDownFilePath_ = strDownFilePath.c_str ();
			
			pDownEngine->SetDownloadFileInfo(strDownFilePath_, strWebFilePath_);
			*FileCount += 1;
		}
/*
		if(bNeedDownload &&
		   !DownloadFile(strWebFilePath.c_str(), strDownFilePath.c_str()))
		{
			ShowErrorMessage("패치를 다운로드하던 중 오류가 발생하였습니다.",
#ifdef _DEBUG	
				strWebFilePath.c_str(),
#endif	
				strDownFilePath.c_str());
			return false;
		}
*/
		
#ifdef USE_PROGRESS
//		g_ProgressTotal.OffsetPos(1);
//		InvalidateRect(g_hWnd, &rInvalidateRect, FALSE);
#endif
	}
	
	return true;
}

bool UpdateManager::ApplyDownloadUpdatedFiles ()
{
	//특별히 할 일이 없다... 있다면... 다운받을 파일을 모두 성공적으로 받았는가 검사하는 정도가 될 것이다.
	//이러한 처리는.. 다른 처리를 다 완료한 후에~ 추가하도록 하자.
	return true;
}

bool UpdateManager::ApplyDeletedFiles_NowCom()
{
	iovfs_base::start_vfs(FILE_DATA_PACKAGE, FS_WRITE);

	LPVFSYSTEM pVFSystem = iovfs_base::get_vfs();

#ifdef USE_PROGRESS
	const CRect& rInvalidateRect = ScreenObjectInfo::Instance()->rcStatusString;

	g_Progress.SetRangeUnitC ();
	g_Progress.SetPos(0);
	g_Progress.SetRange(0, m_DeletedFiles.size());
#endif

	FileCheckInfoTable::iterator pos = m_DeletedFiles.begin();

	for(; pos != m_DeletedFiles.end(); ++pos)
	{
		const std::string& deleteFileName = pos->first;
		const FileCheckInfo& deleteFileCheckInfo = pos->second;

		LPCTSTR fileName = deleteFileName.c_str();

		// Packing Type에 따라 삭제 방법이 다르다
		if(deleteFileCheckInfo.GetPackingType() == PT_NO_PACKING)
		{
			DeleteFile(fileName);
		}
		else
		{
			pVFSystem->DeleteFile(fileName);
		}

#ifdef USE_PROGRESS
		g_Progress.OffsetPos(1);
		InvalidateRect(g_hWnd, &rInvalidateRect, FALSE);
#endif
	}

	iovfs_base::end_vfs();

	return true;
}


bool UpdateManager::ApplyUpdatedFiles_NowCom()
{
#ifdef USE_PROGRESS
	const CRect& rInvalidateRect = ScreenObjectInfo::Instance()->rcStatusString;

	g_Progress.SetRangeUnitC ();
	g_Progress.SetPos(0);
	g_Progress.SetRange(0, m_UpdatedFiles.size());
#endif

	// VFS ㄱㄱ
	iovfs_base::start_vfs(FILE_DATA_PACKAGE, FS_WRITE);
	
	LPVFSYSTEM pVFSystem = iovfs_base::get_vfs();

	FileCheckInfoTable::const_iterator pos = m_UpdatedFiles.begin();

	for(; pos != m_UpdatedFiles.end(); ++pos)
	{
		const std::string& updateFileName = pos->first;
		const FileCheckInfo& updateFileCheckInfo = pos->second;

		LPCTSTR fileName = updateFileName.c_str();

		std::string strUpdateFileName = m_strUpdateTempDir + "/";
		strUpdateFileName += fileName;
		strUpdateFileName += PATCH_DATA_EXT;

		RealData updateFileData;

		if(!updateFileData.Create(strUpdateFileName.c_str(),
			(int)hash_func_path_string_stlport()(fileName)))
		{
//			ShowErrorMessage("패치 파일의 압축을 해제할 수 없습니다.",
			ShowErrorMessage(_STR_ERROR_UNCOMPRESSFILE_,
				fileName, strUpdateFileName.c_str());
			return false;
		}

		bool bFileCheckOK = false;

		// 패치에 앞서 맞는 파일인지 체크해본다.
		if(updateFileData.m_nSize == updateFileCheckInfo.GetFileSize())
		{
			// md5를 체크해본다.
			std::string md5 = CMD5Checksum::GetMD5((BYTE*)updateFileData.m_pData, updateFileData.m_nSize);
			
			if(!memcmp(md5.c_str(), updateFileCheckInfo.GetMD5CheckSum(), FileCheckInfo::CHECKSUM_SIZE))
			{
				bFileCheckOK = true;
			}
		}

		if(!bFileCheckOK)
		{
//			ShowErrorMessage("패치 파일이 손상되었습니다.",
			ShowErrorMessage(_STR_ERROR_DAMAGEDPATCHFILE_,
				fileName, strUpdateFileName.c_str());
			DeleteFile(strUpdateFileName.c_str());
			return false;
		}
		
		int fileOption = std::ios_base::binary;

		// Packing Type에 따라 처리해준다.
		BYTE packingType = updateFileCheckInfo.GetPackingType();

		if(packingType == PT_NO_PACKING)
		{
			FullPathBuild(fileName);
		}	
		else
		{
			fileOption |= iovs_ex::virtualfile;

			if(packingType == PT_COMPRESS_PACKING)
			{
				fileOption |= iovs_ex::compress;
			}
		}

		// 기존에 파일이 있다면 삭제한다.
		if(pVFSystem->IsFileExist(fileName))
		{
			// 실제 파일을 삭제
			DeleteFile(fileName);
			
			// 패키지 파일을 삭제
			pVFSystem->DeleteFile(fileName);
		}

		// 압축 풀린 파일을 기록한다.
		ovfstream fileUpdate(fileName, fileOption);

		if(!fileUpdate.is_open())
		{
//			ShowErrorMessage("패치 파일을 복사할 수 없습니다.",
			ShowErrorMessage(_STR_ERROR_CANNOTCOPYPATCHFILE_,
				fileName, strUpdateFileName.c_str());
			return false;
		}

		fileUpdate.write((const char *)updateFileData.m_pData, updateFileData.m_nSize);
		fileUpdate.close();

		updateFileData.Destory();

#ifdef USE_PROGRESS
		g_Progress.OffsetPos(1);
		InvalidateRect(g_hWnd, &rInvalidateRect, FALSE);
#endif	
	}

	iovfs_base::end_vfs();

	return true;
}


bool UpdateManager::ApplyPackingTypeChangedFiles_NowCom()
{
	// 두 리스트의 크기는 반드시 같아야한다.
	if(m_PackingTypeChangedLocalFiles.size()
		!= m_PackingTypeChangedRecentFiles.size())
	{
		Assert("UpdateManager::ApplyPackingTypeChangedFiles() : List Error" && FALSE);

		char szChangeLocal[128];
		char szChangeRecent[128];

		sprintf(szChangeLocal, "LocalFiles: %d", m_PackingTypeChangedLocalFiles.size());
		sprintf(szChangeRecent, "RecentFiles: %d", m_PackingTypeChangedRecentFiles.size());

//		ShowErrorMessage("리스트의 크기가 다릅니다.", szChangeLocal, szChangeRecent);
		ShowErrorMessage(_STR_ERROR_DIFFERLISTSIZE_, szChangeLocal, szChangeRecent);
		return false;
	}

#ifdef USE_PROGRESS
	const CRect& rInvalidateRect = ScreenObjectInfo::Instance()->rcStatusString;

	g_Progress.SetRangeUnitC ();
	g_Progress.SetPos(0);
	g_Progress.SetRange(0, m_PackingTypeChangedLocalFiles.size());
#endif

	// VFS ㄱㄱ
	iovfs_base::start_vfs(FILE_DATA_PACKAGE, FS_WRITE);
	
	LPVFSYSTEM pVFSystem = iovfs_base::get_vfs();

	
	FileCheckInfoTable::iterator recentIter	= m_PackingTypeChangedRecentFiles.begin();
	FileCheckInfoTable::iterator localIter	= m_PackingTypeChangedLocalFiles.begin();

	while(recentIter != m_PackingTypeChangedRecentFiles.end() ||
		localIter != m_PackingTypeChangedLocalFiles.end())
	{
		const std::string& recentFileName = recentIter->first;
		const FileCheckInfo& recentFileCheckInfo = recentIter->second;

		const std::string& localFileName = localIter->first;
		const FileCheckInfo& localFileCheckInfo = localIter->second;

		// 두 리스트의 파일 이름은 반드시 같아야한다.
		Assert("localIter->GetFileName() == recentIter->GetFileName()" && localFileName == recentFileName);

		LPCTSTR fileName = localFileName.c_str();

		// 파일이 없다면 뭔가 이상하다.
		if(!pVFSystem->IsFileExist(fileName))
		{
//			ShowErrorMessage("패키지 타입이 다른 파일의 원본 파일이 없습니다.", fileName);
			ShowErrorMessage(_STR_ERROR_PACKAGETYPE1_, fileName);
			return false;
		}

		BYTE recentPackingType	= recentFileCheckInfo.GetPackingType();
		BYTE localPackingType	= localFileCheckInfo.GetPackingType();

		DWORD recentFileSize	= recentFileCheckInfo.GetFileSize();
		DWORD localFileSize		= localFileCheckInfo.GetFileSize();

		// 다른 정보는 다 같고 패킹 타입만 틀려야한다.
		if(recentPackingType != localPackingType &&
			recentFileSize == localFileSize)
		{
			// 내가 가지고 있던 파일을 읽어들인다.
			int localFileOption = std::ios_base::binary;

			if(localPackingType != PT_NO_PACKING)
			{
				localFileOption |= iovs_ex::virtualfile;

				if(localPackingType == PT_COMPRESS_PACKING)
				{
					localFileOption |= iovs_ex::compress;
				}
			}

			char *pBuffer = new char[localFileSize];

			ivfstream localFile(fileName, localFileOption);
			if(!localFile.is_open())
			{
				ShowErrorMessage(
					_STR_ERROR_PACKAGETYPE2_, fileName);
//					"패키지 타입이 다른 파일의 원본 파일을 열 수 없습니다.", fileName);
				delete [] pBuffer;
				return false;
			}

			localFile.read(pBuffer, localFileSize);
			
			if(static_cast<DWORD>(localFile.gcount()) != localFileSize)
			{
				ShowErrorMessage(
					_STR_ERROR_PACKAGETYPE3_, fileName);
//					"패키지 타입이 다른 파일의 원본 파일을 읽던 중 오류가 발생하였습니다.", fileName);
				delete [] pBuffer;
				return false;
			}
			
			localFile.close();

			// 새로운 패킹 타입에 맞게 복사한다.
			int recentFileOption = std::ios_base::binary;

			if(recentPackingType != PT_NO_PACKING)
			{
				recentFileOption |= iovs_ex::virtualfile;

				if(recentPackingType == PT_COMPRESS_PACKING)
				{
					recentFileOption |= iovs_ex::compress;
				}
			}
			

			if(!FullPathBuild(fileName))
			{
//				ShowErrorMessage("패키지 타입이 바뀐 파일을 출력할 디렉토리를 생성할 수 없습니다.", fileName);
				ShowErrorMessage(_STR_ERROR_PACKAGETYPE4_, fileName);
				return false;
			}

			ovfstream recentFile(fileName, recentFileOption);
			
			if(!recentFile.is_open())
			{
//				ShowErrorMessage("패키지 타입이 바뀐 파일을 출력 수 없습니다.", fileName);
				ShowErrorMessage(_STR_ERROR_PACKAGETYPE5_, fileName);
				return false;
			}

			recentFile.write(pBuffer, recentFileSize);
			recentFile.close();

			delete [] pBuffer;

			// 로컬 파일은 삭제한다.
			if(localPackingType == PT_NO_PACKING)
			{
				DeleteFile(fileName);
			}
			else
			{
				pVFSystem->DeleteFile(fileName);
			}
		}
		else
		{
//			ShowErrorMessage("패키지 타입이 다른 파일의 내용이 다릅니다.", fileName);
			ShowErrorMessage(_STR_ERROR_PACKAGETYPE6_, fileName);
			return false;
		}

		++recentIter;
		++localIter;

#ifdef USE_PROGRESS
		g_Progress.OffsetPos(1);
		InvalidateRect(g_hWnd, &rInvalidateRect, FALSE);
#endif	
	}


	iovfs_base::end_vfs();

	return true;
}
