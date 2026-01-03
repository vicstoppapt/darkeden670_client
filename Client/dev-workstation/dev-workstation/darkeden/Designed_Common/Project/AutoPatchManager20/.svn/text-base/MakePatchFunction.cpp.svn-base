#include "stdafx.h"
#include "AutoPatchManager.h"
#include "AutoPatchManagerDlg.h"

#include "APM_Macro.h"
#include "APM_Define.h"

#include "VFS_Macro.h"

#include "PatchDataHeader.h"

#include "MZLib/zlib.h"

#include <list>
#include <map>

bool CAutoPatchManagerDlg::AutoSplitSpk(bool copySameFile)
{
	std::list<std::string> splitSpkList;

	char szSplitBuf[_MAX_PATH + _MAX_FNAME + _MAX_EXT];

	// 파일을 나눠야 하는 Spk를 찾는다.
	FileCheckInfoTable::iterator newPos		= m_NewFileCheckInfoTable.begin();

	for(; newPos != m_NewFileCheckInfoTable.end(); ++newPos)
	{
		const std::string&		newFileName = newPos->first;
		const FileCheckInfo&	newFileCheckInfo = newPos->second;

		sprintf(szSplitBuf, "%s/header.inf", newFileName.c_str());

		FileCheckInfoTable::iterator recentPos = m_RecentFileCheckInfoTable.find(szSplitBuf);

		// 뭔가 찾았다면
		if(recentPos != m_RecentFileCheckInfoTable.end())
			splitSpkList.push_back(newFileName);
	}

	// 나눌 SPK가 하나도 없다면 끝
	if(splitSpkList.empty())
		return true;

	
	// 찾은 Spk를 확인 시킨다.
	//std::string strAutoSplitFiles = "One or more files are need to split\n\n";
	std::string strAutoSplitFiles = "한개 이상의 파일을 분리해야만 계속 할 수 있습니다.\n\n";

	std::list<std::string>::iterator pos = splitSpkList.begin();
	
	for(; pos != splitSpkList.end(); ++pos)
		strAutoSplitFiles += *pos + '\n';

	//strAutoSplitFiles += "\nWould you like to split them?";
	strAutoSplitFiles += "\n해당 파일들을 분리하시겠습니까?";

	// Split 시킬 것인지 물어본다.
	// 분리 안 시키면 뻐팅긴다.
	if(IDNO == MessageBox(strAutoSplitFiles.c_str(), "Auto Split Confirm", MB_YESNO | MB_ICONQUESTION))
		return false;

	// 예전 분리되있던 놈들을 테이블에 저장해둔다.
	FileCheckInfoTable splitSpkOldMap;

	pos = splitSpkList.begin();

	for(; pos != splitSpkList.end(); ++pos)
	{
		sprintf(szSplitBuf, "%s/", pos->c_str());

		FileCheckInfoTable::iterator recentPos	= m_RecentFileCheckInfoTable.begin();

		for(; recentPos != m_RecentFileCheckInfoTable.end(); ++recentPos)
		{
			const std::string&		recentFileName = recentPos->first;
			const FileCheckInfo&	recentFileCheckInfo = recentPos->second;

			if(!strnicmp(recentFileName.c_str(), szSplitBuf, pos->size()))
			{
				splitSpkOldMap.insert(std::make_pair(
					recentFileName, recentFileCheckInfo));
			}
		}
	}

	// 파일을 나눈다.
	char splitFName[_MAX_FNAME], splitExt[_MAX_EXT];
	
	pos = splitSpkList.begin();

	for(; pos != splitSpkList.end(); ++pos)
	{
		// 확장자를 얻는다.
		_splitpath(pos->c_str(), NULL, NULL, NULL, splitExt);

		sprintf(szSplitBuf, "%s/00000%s", pos->c_str(), splitExt);

		FileCheckInfoTable::iterator findPos
			= splitSpkOldMap.find(szSplitBuf);

		bool bSplitOK = false;

		// 00000을 찾았다면 바로 다음 숫자가 Split Unit Size이다.
		// 만약 찾을 수 없다면 Auto Split를 사용할 수 없다.
		if(findPos != splitSpkOldMap.end() &&
			++findPos != splitSpkOldMap.end())
		{
			const std::string& findFileName = findPos->first;

			// 파일 이름을 얻는다.
			_splitpath(findFileName.c_str(), NULL, NULL, splitFName, NULL);

			int splitUnit = atoi(splitFName);

			if(splitUnit > 0)
			{
				std::string updateFilePath = UPDATE_PATH;
				updateFilePath += "/";
				updateFilePath += *pos;

				bSplitOK = SplitSpk(updateFilePath.c_str(), splitUnit);
			}
		}

		if(!bSplitOK)
		{
			MessageBox(pos->c_str(), "Auto Split Error", MB_OK | MB_ICONERROR);
			return false;
		}
	}

	// 이 시점에서 분리된 파일을 다시 읽어와준다.
	BuildPatchFileListTable(UPDATE_PATH);

	// 기존에 분리 되어있던 놈들과 방금 분리한 놈들과
	// MD5 비교를 해서 필요 없는 놈은 삭제한다.

	newPos = m_NewFileCheckInfoTable.begin();

	for(; newPos != m_NewFileCheckInfoTable.end(); ++newPos)
	{
		const std::string& newFileName = newPos->first;
		
		FileCheckInfoTable::iterator findPos
			= splitSpkOldMap.find(newFileName);

		if(findPos == splitSpkOldMap.end()) continue;

		const FileCheckInfo &newCheck = newPos->second;
		const FileCheckInfo &oldCheck = findPos->second;

		bool bSame = !copySameFile && oldCheck.GetFileSize() == newCheck.GetFileSize() &&
			!memcmp(oldCheck.GetMD5CheckSum(), newCheck.GetMD5CheckSum(), FileCheckInfo::CHECKSUM_SIZE);

		// 똑같은 놈은 필요 없음
		if(bSame)
		{
			std::string deleteFilePath = UPDATE_PATH;
			deleteFilePath += "/";
			deleteFilePath += newFileName;
			DeleteFile(deleteFilePath.c_str());
		}
	}

	// 다 정리했으면 다시 로드
	BuildPatchFileListTable(UPDATE_PATH);

	// 헥헥
	return true;
}



bool CAutoPatchManagerDlg::SplitSpk(LPCTSTR fileName, int UnitCount)
{
	const int SPLITED_NUMBER_SIZE = 5;
	
	assert("분리단위가 2의 승수가 아닙니다." && IsTwoMultiplier(UnitCount));

	if(access(fileName, 0))
	{
		return false;
	}

    char fileIndexName[MAX_PATH];
	strcpy(fileIndexName, fileName);
	strcat(fileIndexName, "i");

	if(access(fileIndexName, 0))
	{
		return false;
	}

	// Origin Name
	char splitDrive[_MAX_DRIVE], splitPath[MAX_PATH], splitFName[_MAX_FNAME], splitExt[_MAX_EXT];
	_splitpath(fileName, splitDrive, splitPath, splitFName, splitExt);

	char originName[MAX_PATH];
	sprintf(originName, "%s%s~original~%s%s", splitDrive, splitPath, splitFName, splitExt);

	char originIndexName[MAX_PATH];
	sprintf(originIndexName, "%s%s~original~%s%si", splitDrive, splitPath, splitFName, splitExt);

	MoveFile(fileName, originName);
	MoveFile(fileIndexName, originIndexName);

	int* pIndex		= NULL;
	int* pDataSize	= NULL;
	char* pBuffer	= NULL;

	try
	{
		// Open TypePack
		std::ifstream TypePackFile;
		TypePackFile.open(originName, std::ios_base::in | std::ios_base::binary);

		// Get TypePack File Size
		TypePackFile.seekg(0, std::ios_base::end);
		int FileSize = static_cast<int>(TypePackFile.tellg());

		TypePackFile.seekg(0, std::ios_base::beg);

		// Get TypePack Data Count
		WORD DataCount = 0;
		TypePackFile.read((char *)&DataCount, 2);

		// TypePack Index Load
		bool bIndexLoad = false;

		WORD IndexCount = 0;
		std::ifstream TypePackIndexFile;
		TypePackIndexFile.open(originIndexName, std::ios_base::in | std::ios_base::binary);
		TypePackIndexFile.read((char *)&IndexCount, 2);

		if(DataCount != IndexCount)
		{
			throw std::exception("해당 파일과 인덱스 파일의 데이터 갯수가 다릅니다.");
		}

		if(TypePackIndexFile.is_open() && IndexCount == DataCount)
		{
			bool readError = false;

			pIndex = new int[DataCount + 1];
			for (int i = 0; i < DataCount; ++i)
			{
				TypePackIndexFile.read((char *)&pIndex[i], 4);
				if(TypePackIndexFile.gcount() < 4) { readError = true; break; }
			}

			TypePackIndexFile.close();

			if(!readError)
			{
				pIndex[DataCount] = FileSize;
				bIndexLoad = true;
			}
		}

		// Index Load에 실패했다.
		if(!bIndexLoad)
		{
			throw std::exception("인덱스 파일을 읽어 들어던 중 오류가 발생하였습니다.");
		}

		// Generate Data Size
		pDataSize = new int[DataCount];

		int DataSizeMax = 0;
		int DataSizeSum = 0;

		// Set Progress Bar
		char szBuf[256];
		sprintf(szBuf, "Split %s (UnitCount=%d)", fileName, UnitCount);
		
		SetProgress(szBuf, DataCount * 2);

		for (int i = 0; i < DataCount; ++i)
		{
			int size = pIndex[i + 1] - pIndex[i];
			if(size > DataSizeMax) DataSizeMax = size;
			pDataSize[i] = size;
			DataSizeSum += size;

			m_progressWorking.OffsetPos(1);
		}

		// Index Load에 실패했다.
		if(DataSizeSum != FileSize - 2)
		{
			throw std::exception("인덱스 파일을 읽어 들어던 중 오류가 발생하였습니다.");
		}

		delete [] pIndex;

		CreateDirectory(fileName, NULL);

		char fileFormat[MAX_PATH];
		sprintf(fileFormat, "%s\\%%0%dd%s", fileName, SPLITED_NUMBER_SIZE, splitExt);

		char fileOutputName[MAX_PATH];

		pBuffer = new char[DataSizeMax];

		int dataIdx = 0;

		while(dataIdx < DataCount)
		{
			sprintf(fileOutputName, fileFormat, dataIdx);

			std::ofstream OutputFile(fileOutputName, std::ios_base::out | std::ios_base::binary);

			int		leftCount	= DataCount - dataIdx;
			WORD	outputCount = min(leftCount, UnitCount);

			OutputFile.write((char *)&outputCount, 2);

			for(int j = 0; j < outputCount; ++j, ++dataIdx)
			{
				TypePackFile.read(pBuffer, pDataSize[dataIdx]);
				OutputFile.write(pBuffer, pDataSize[dataIdx]);
			}

			OutputFile.close();

			m_progressWorking.OffsetPos(outputCount);
		}

		TypePackFile.close();

		char headerName[MAX_PATH];
		sprintf(headerName, "%s\\header.inf", fileName);

		std::ofstream TypePackHeader(headerName);

		TypePackHeader << DataCount << '\n';
		TypePackHeader << UnitCount << '\n';

		TypePackHeader.close();


		delete [] pBuffer;
		delete [] pDataSize;
	}
	catch(const std::exception& error)
	{
		RemoveDirectory(fileName);
		MoveFile(originName, fileName);
		MoveFile(originIndexName, fileIndexName);

		delete [] pIndex;
		delete [] pBuffer;
		delete [] pDataSize;

//		std::ofstream errLog("SpkSpliter.log", std::ios_base::app);
//		errLog << "(ERROR!) FILENAME = " << fileName << ", WHAT = " << error.what() << std::endl;

		char szBuf[256];
		sprintf(szBuf, "%s\n\n%s", fileName, error.what());

		MessageBox(szBuf, "split spk error", MB_OK | MB_ICONERROR);

		return false;
	}

//	std::ofstream log("SpkSpliter.log", std::ios_base::app);
//	log << "(COMPLETE) FILENAME = " << fileName << std::endl;

	DeleteFile(originName);

//	DeleteFile(originIndexName);
	MoveFile(originIndexName, fileIndexName);

	return true;
}


bool CAutoPatchManagerDlg::IsTwoMultiplier(int num)
{
	int count = 0;

	for(int i = 0; i < 8; ++i) {

		if(num & 0x00000001) {
			if(count > 0) return false;
			++count;
		}

		num >>= 1;
	}

	return count == 1;
}


void CAutoPatchManagerDlg::MakePatch()
{
	// 	if(m_NewFileCheckInfoTable.empty())
	// 	{
	// 		MessageBox("Update파일이 없습니다.", NULL, MB_ICONWARNING | MB_OK);
	// 		return;
	// 	}

	//////////////////////////////////////////////////////////////////////////
	// 같은 파일도 무조건 복사라면
	// 새로운 파일의 기록 시간을 현재 시간으로 바꿔
	// 기존 파일보다 최신 버전으로 인식하게 한다.
	bool bCopyIdenticalFile = m_checkCopyIdenticalFile.GetCheck() == BST_CHECKED;

	if(bCopyIdenticalFile)
	{
		SetProgress("Set new file write time", 2);

		FILETIME sysFileTime;
		GetSystemTimeAsFileTime(&sysFileTime);
		
		SetFileWriteTimeInDirectory(UPDATE_PATH, sysFileTime);

		m_progressWorking.OffsetPos(1);

		// 기록 시간이 바뀌었음으로 다시 로드
		BuildPatchFileListTable(UPDATE_PATH);

		m_progressWorking.OffsetPos(1);
	}


	//////////////////////////////////////////////////////////////////////////
	// 패치 데이터를 백업한다.
	SYSTEMTIME sysTime; 
	GetLocalTime( &sysTime );

	char szAutoBackupFile[MAX_PATH];
	sprintf(szAutoBackupFile,
		"%s/%04d%02d/Update%04d%02d%02d_%02d%02d%02d.zip",
		AUTOBACKUP_PATH,
		sysTime.wYear, sysTime.wMonth,
		sysTime.wYear, sysTime.wMonth, sysTime.wDay,
		sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

	if(!BackupUpdateToZip(UPDATE_PATH, szAutoBackupFile))
	{
		MessageBox("패치 백업에 실패하였습니다.", NULL, MB_ICONERROR | MB_OK);
	}


	//////////////////////////////////////////////////////////////////////////
	// 분리시켜 압축할 패치 파일이 있나 확인한다.
	if(!AutoSplitSpk(bCopyIdenticalFile))
	{
		MessageBox("패치 생성을 실패하였습니다.", "Make Patch Error", MB_OK | MB_ICONERROR);
		return;
	}



	//////////////////////////////////////////////////////////////////////////
	// 프로그레스바를 초기화한다.
	SetProgress("Make Patch", (int)m_NewFileCheckInfoTable.size());



	//////////////////////////////////////////////////////////////////////////
	// 패치를 생성한다.
	char szPath[_MAX_PATH];
	char szFileName[_MAX_PATH + _MAX_FNAME + _MAX_EXT];
	
	int copyFileCount		= 0;

	FileCheckInfoTable::iterator newPos		= m_NewFileCheckInfoTable.begin();

	for(; newPos != m_NewFileCheckInfoTable.end(); ++newPos)
	{
		const std::string&		newFileName = newPos->first;
		const FileCheckInfo&	newFileCheckInfo = newPos->second;

		int cmpValue = 0;
		
		// 기존에 없던 파일이라면 그냥 카피하고
		// 기존에 있던 파일이라면 새로운 파일과 비교해서 복사할 것인지 결정한다.
		FileCheckInfoTable::iterator findPos = m_RecentFileCheckInfoTable.find(newFileName);
				
		bool findFile = findPos != m_RecentFileCheckInfoTable.end();
		bool copyUpdate = true;
		
		if(findFile)
		{
			FileCheckInfo	&recentFileCheckInfo = findPos->second;
			copyUpdate = !newFileCheckInfo.IsFileDataIdentical(recentFileCheckInfo);
		}

#ifdef _DEBUG
		OutputDebugString("Check File: Name=");
		OutputDebugString(newFileName.c_str());
		OutputDebugString(", Find=");
		OutputDebugString(findFile ? "1" : "0");
		OutputDebugString(", Copy=");
		OutputDebugString(copyUpdate ? "1" : "0");
		OutputDebugString("\n");
#endif

		if(copyUpdate)
		{
			// 새로운 FileCheckInfo를 업데이트 해준다.
			m_RecentFileCheckInfoTable[newFileName] = newFileCheckInfo;

			// 실제 패치 파일을 생성한다.
			_splitpath(newFileName.c_str(), NULL, szPath, NULL, NULL);

			strcpy(szFileName, UPDATE_PATH "/");
			strcat(szFileName, newFileName.c_str());

			std::ifstream newFile(szFileName, std::ios_base::binary);

			newFile.seekg(0, std::ios_base::end);
			DWORD fileSize = static_cast<DWORD>(newFile.tellg());
			newFile.seekg(0, std::ios_base::beg);

			DWORD compressSize = calc_compress_buffer_size(fileSize);

			char *pBuffer		= new char[fileSize];
			char *pCompressBuf	= new char[compressSize];

			char *pRead = pBuffer;

			int readSum = 0, readCount = 0;
			for(;;)
			{
				newFile.read(pBuffer, fileSize);
				readCount = static_cast<int>(newFile.gcount());
				if(readCount == 0) break;

				readSum	+= readCount;
				pRead	+= readCount;
			}

			assert(fileSize == readSum);

			newFile.close();

			PatchDataHeader patchDataHeader;

			int result = compress2(
				(Bytef*)pCompressBuf, &compressSize,
				(Bytef*)pBuffer, fileSize, Z_DEFAULT_COMPRESSION);
			assert(result == Z_OK);

			patchDataHeader.UncompressSize = fileSize;
			patchDataHeader.Incompressible = compressSize >= fileSize;

			strcpy(szFileName, PATCHOUT_PATH "/");
			strcat(szFileName, newFileName.c_str());
			strcat(szFileName, PATCHOUT_EXT);

			result = FullPathBuild(szFileName);
			assert(result == 1);

			std::ofstream uploadFile(szFileName, std::ios_base::binary);

			// 압축 안되는 놈이면 걍 쓴다.
			if(patchDataHeader.Incompressible)
			{
				patchDataHeader.CompressSize = fileSize;
				uploadFile.write((const char *)&patchDataHeader, PATCHDATAHEADER_SIZE);
				uploadFile.write(pBuffer, fileSize);
			}
			// 압축 되는 놈이면 암호화해서 쓴다.
			else
			{
				patchDataHeader.CompressSize = compressSize;

				encrypt_data(pCompressBuf, compressSize,
					(int)hash_func_path_string_stlport()(newFileName.c_str()));

				uploadFile.write((const char *)&patchDataHeader, PATCHDATAHEADER_SIZE);
				uploadFile.write(pCompressBuf, compressSize);
			}

			uploadFile.close();

			delete [] pCompressBuf;
			delete [] pBuffer;

			++copyFileCount;
		}

		m_progressWorking.OffsetPos(1);
	}
	//*/


	//////////////////////////////////////////////////////////////////////////
	// 새로운 파일 리스트는 삭제
	m_NewFileCheckInfoTable.clear();


	//////////////////////////////////////////////////////////////////////////
	// 바뀐 List파일을 저장하고 PatchOut 폴더에 복사한다.
	SavePatchListFile();

	FullPathBuild(PATCHOUT_PATH "/" RECENT_PATCH_LIST_FILE_NAME);
	CopyFile(RECENT_PATCH_LIST_FILE_NAME,			PATCHOUT_PATH "/" RECENT_PATCH_LIST_FILE_NAME, FALSE);
	CopyFile(RECENT_PATCH_LIST_VERSION_FILE_NAME,	PATCHOUT_PATH "/" RECENT_PATCH_LIST_VERSION_FILE_NAME, FALSE);


	//////////////////////////////////////////////////////////////////////////
	// 끝
	if(copyFileCount > 0)
	{
		MessageBox("Patch를 성공적으로 생성하였습니다.", NULL, MB_ICONINFORMATION | MB_OK);
	}
	else
	{
		MessageBox("Update파일이 모두 최신입니다.", NULL, MB_ICONWARNING | MB_OK);
	}
}


bool CAutoPatchManagerDlg::BackupUpdateToZip(const char *dirName, const char *zipName)
{
/*	SetProgress("Auto backup to zip", 3);

	//HZIP hz = CreateZip(zipName, "" );

	const LPCTSTR TEMP_ZIP_NAME = "backup.tmp";

	DeleteFile(TEMP_ZIP_NAME);

	CZipper zipper(TEMP_ZIP_NAME);

	//zRes = ZipAdd(hz, RECENT_PATCH_LIST_FILE_NAME, RECENT_PATCH_LIST_FILE_NAME);

	if(!zipper.AddFileToZip(RECENT_PATCH_LIST_FILE_NAME))
	{
		DeleteFile(TEMP_ZIP_NAME);
		return false;
	}

	m_progressWorking.OffsetPos(1);

	if(!zipper.AddFileToZip(RECENT_PATCH_LIST_VERSION_FILE_NAME))
	{
		DeleteFile(TEMP_ZIP_NAME);
		return false;
	}

	m_progressWorking.OffsetPos(1);

//	if(!BackupDirectoryToZipImpl(dirName, zipper))
//		return false;

	if(!zipper.AddFolderToZip(dirName))
	{
		DeleteFile(TEMP_ZIP_NAME);
		return false;
	}

	m_progressWorking.OffsetPos(1);

	zipper.CloseZip();

	FullPathBuild(zipName);

	MoveFile(TEMP_ZIP_NAME, zipName);
*/
	return true;
}


bool CAutoPatchManagerDlg::SetFileWriteTimeInDirectory(const char* dirName, FILETIME& fileTime)
{
	char	newPath[MAX_PATH];
	char	drive[_MAX_DRIVE];
	char	dir[MAX_PATH];
	char	szWildCard[MAX_PATH];

	HANDLE	hSrch;
	BOOL	bResult = TRUE;
	WIN32_FIND_DATA	wfd;

	if(strlen(dirName))
		wsprintf(szWildCard, "%s/*.*", dirName);
	else
		strcpy(szWildCard, "*.*");

	_splitpath(szWildCard, drive, dir, NULL, NULL);

	hSrch = FindFirstFile(szWildCard, &wfd);

	while(bResult)
	{
		wsprintf(newPath, "%s%s%s", drive, dir, wfd.cFileName);

		if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(wfd.cFileName[0] != '.')
			{
				if(!SetFileWriteTimeInDirectory(newPath, fileTime))
					return false;
			}
		}
		else
		{
			HANDLE hFile = CreateFile(newPath, GENERIC_WRITE, FILE_SHARE_READ,
				NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

			SetFileTime(hFile, NULL, NULL, &fileTime);

			CloseHandle(hFile);
		}

		bResult = FindNextFile(hSrch, &wfd);
	}

	FindClose(hSrch);

	return true;
}