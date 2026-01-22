// AutoPatchManagerDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "AutoPatchManager.h"
#include "AutoPatchManagerDlg.h"

#include "APM_Define.h"

#include "VFS_Macro.h"

//#include "vfstream.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


char CAutoPatchManagerDlg::s_szPackingString[][6]	= { "None", "Pack", "CPack" };


unsigned int WINAPI UpdateListCtrl_Thread(void *arg)
{
	CAutoPatchManagerDlg *pAPM = static_cast<CAutoPatchManagerDlg *>(arg);
	pAPM->UpdateListCtrl();
	pAPM->MessageBox("Patch List를 성공적으로 업데이트하였습니다.", NULL, MB_ICONINFORMATION | MB_OK);
	return 0;
}

unsigned int WINAPI MakePatch_Thread(void *arg)
{
	CAutoPatchManagerDlg *pAPM = static_cast<CAutoPatchManagerDlg *>(arg);
	pAPM->MakePatch();
	pAPM->SetNewFileMode();
	pAPM->UpdateListCtrl();
	return 0;
}

unsigned int WINAPI Preload_Thread(void *arg)
{
	CAutoPatchManagerDlg *pAPM = static_cast<CAutoPatchManagerDlg *>(arg);

	//////////////////////////////////////////////////////////////////////////
	// Load Recent List
	pAPM->LoadPatchListFile();

	//////////////////////////////////////////////////////////////////////////
	// Load New List
	pAPM->SetNewFileMode();
	pAPM->BuildPatchFileListTable(UPDATE_PATH);
	pAPM->UpdateListCtrl();

	//////////////////////////////////////////////////////////////////////////
	// Init Progress
	pAPM->SetProgress("Ready");

	return 0;
}


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원

// 구현
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CAutoPatchManagerDlg 대화 상자


CAutoPatchManagerDlg::CAutoPatchManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAutoPatchManagerDlg::IDD, pParent)
	, m_hWorkThread(NULL)
	, m_dwWorkThreadID(0)
	, m_pSelectedFileCheckInfoTable(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	InitColumnSort();
}

void CAutoPatchManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_WORKING, m_progressWorking);
	DDX_Control(pDX, IDC_LIST_FILES, m_listFiles);
	DDX_Control(pDX, IDC_COMBO_PACKING_TYPE, m_comboPackingType);
	DDX_Control(pDX, IDC_EDIT_PROGRESS, m_editWorking);
	DDX_Control(pDX, IDC_CHECK_COPY_IDENTICAL_FILE, m_checkCopyIdenticalFile);
	DDX_Control(pDX, IDC_FILE_COUNT, m_staticFileCount);
}

BEGIN_MESSAGE_MAP(CAutoPatchManagerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_SET_PACKING_TYPE, OnBnClickedSetPackingType)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_FILES, OnLvnColumnclickListFiles)
	ON_BN_CLICKED(IDC_BTN_RECENT_LIST, OnBnClickedRecentList)
	ON_BN_CLICKED(IDC_BTN_NEW_LIST, OnBnClickedNewList)
	ON_BN_CLICKED(IDC_BTN_MAKE, OnBnClickedMake)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBnClickedDelete)
END_MESSAGE_MAP()


// CAutoPatchManagerDlg 메시지 처리기

BOOL CAutoPatchManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	// 프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.


	//////////////////////////////////////////////////////////////////////////
	// File List 초기화
	LVCOLUMN	COL;

	COL.mask		= LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt			= LVCFMT_LEFT;
	COL.iSubItem	= 0;

	COL.pszText		= "Name";
	COL.cx			= 100;
	m_listFiles.InsertColumn(COL.iSubItem, &COL);
	++COL.iSubItem;

	COL.pszText		= "Path";
	COL.cx			= 230;
	m_listFiles.InsertColumn(COL.iSubItem, &COL);
	++COL.iSubItem;

	COL.pszText		= "Ext";
	COL.cx			= 45;
	m_listFiles.InsertColumn(COL.iSubItem, &COL);
	++COL.iSubItem;
	
	COL.pszText		= "Type";
	COL.cx			= 50;
	m_listFiles.InsertColumn(COL.iSubItem, &COL);
	++COL.iSubItem;

	COL.pszText		= "UpdateDate";
	COL.cx			= 115;
	m_listFiles.InsertColumn(COL.iSubItem, &COL);
	++COL.iSubItem;

	COL.pszText		= "FileSize";
	COL.cx			= 75;
	COL.fmt			= LVCFMT_RIGHT;
	m_listFiles.InsertColumn(COL.iSubItem, &COL);
	++COL.iSubItem;

	COL.fmt			= LVCFMT_LEFT;

	COL.pszText		= "MD5";
	COL.cx			= 250;
	m_listFiles.InsertColumn(COL.iSubItem, &COL);
	++COL.iSubItem;


	//////////////////////////////////////////////////////////////////////////
	// Packing Type

	m_comboPackingType.InsertString(0, "No Packing");
	m_comboPackingType.InsertString(1, "Packing");
	m_comboPackingType.InsertString(2, "Compress Packing");
	
	m_comboPackingType.SetWindowPos(NULL, 0, 0, 140, 100, SWP_NOMOVE | SWP_NOZORDER);
	m_comboPackingType.SetCurSel(0);


	//////////////////////////////////////////////////////////////////////////
	// Load New List
	StartWorkThread(Preload_Thread);


	return TRUE;  // 컨트롤에 대한 포커스를 설정하지 않을 경우 TRUE를 반환합니다.
}

void CAutoPatchManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면 
// 아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
// 프레임워크에서 이 작업을 자동으로 수행합니다.

void CAutoPatchManagerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다. 
HCURSOR CAutoPatchManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CAutoPatchManagerDlg::SortTextItems(int nCol, BOOL bAscending, int low, int high)
{
	if( nCol >= ((CHeaderCtrl*)m_listFiles.GetDlgItem(0))->GetItemCount() )
		return FALSE;

	if( high == -1 ) high = m_listFiles.GetItemCount() - 1;

	int lo = low;
	int hi = high;
	CString midItem;

	if( hi <= lo ) return FALSE;

	midItem = m_listFiles.GetItemText( (lo+hi)/2, nCol );

	// loop through the list until indices cross
	while( lo <= hi )
	{
		// rowText will hold all column text for one row
		CStringArray rowText;

		// find the first element that is greater than or equal to
		// the partition element starting from the left Index.
		if( bAscending )
			while( ( lo < high ) && ( m_listFiles.GetItemText(lo, nCol) < midItem ) )
				++lo;
		else
			while( ( lo < high ) && ( m_listFiles.GetItemText(lo, nCol) > midItem ) )
				++lo;

		// find an element that is smaller than or equal to
		// the partition element starting from the right Index.
		if( bAscending )
			while( ( hi > low ) && ( m_listFiles.GetItemText(hi, nCol) > midItem ) )
				--hi;
		else
			while( ( hi > low ) && ( m_listFiles.GetItemText(hi, nCol) < midItem ) )
				--hi;

		// if the indexes have not crossed, swap
		// and if the items are not equal
		if( lo <= hi )
		{
			// swap only if the items are not equal
			if( m_listFiles.GetItemText(lo, nCol) != m_listFiles.GetItemText(hi, nCol))
			{
				// swap the rows
				LV_ITEM lvitemlo, lvitemhi;
				int nColCount =
					((CHeaderCtrl*)m_listFiles.GetDlgItem(0))->GetItemCount();
				rowText.SetSize( nColCount );
				int i;
				for( i=0; i<nColCount; i++)
					rowText[i] = m_listFiles.GetItemText(lo, i);
				lvitemlo.mask = LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
				lvitemlo.iItem = lo;
				lvitemlo.iSubItem = 0;
				lvitemlo.stateMask = LVIS_CUT | LVIS_DROPHILITED |
					LVIS_FOCUSED | LVIS_SELECTED |
					LVIS_OVERLAYMASK | LVIS_STATEIMAGEMASK;

				lvitemhi = lvitemlo;
				lvitemhi.iItem = hi;

				m_listFiles.GetItem( &lvitemlo );
				m_listFiles.GetItem( &lvitemhi );

				for( i=0; i<nColCount; i++)
					m_listFiles.SetItemText(lo, i, m_listFiles.GetItemText(hi, i));

				lvitemhi.iItem = lo;
				m_listFiles.SetItem( &lvitemhi );

				for( i=0; i<nColCount; i++)
					m_listFiles.SetItemText(hi, i, rowText[i]);

				lvitemlo.iItem = hi;
				m_listFiles.SetItem( &lvitemlo );
			}

			++lo;
			--hi;
		}
	}

	// If the right index has not reached the left side of array
	// must now sort the left partition.
	if( low < hi )
		SortTextItems( nCol, bAscending , low, hi);

	// If the left index has not reached the right side of array
	// must now sort the right partition.
	if( lo < high )
		SortTextItems( nCol, bAscending , lo, high );

	return TRUE;
}


void CAutoPatchManagerDlg::InitColumnSort()
{
	for(int i = 0; i < COLUMN_SIZE; ++i)
		m_bColumnSort[i] = TRUE;

	m_nLastClickedColumn = -1;
}

void CAutoPatchManagerDlg::OnBnClickedSetPackingType()
{
	assert(m_pSelectedFileCheckInfoTable);

	if(!CheckWorkTheardRunning()) return;

	int selectPatchType = m_comboPackingType.GetCurSel();

	if(selectPatchType == PT_PACKING)
	{
		MessageBox("이 버전은 No Packing, Compress Packing만 지원합니다.", NULL, MB_ICONINFORMATION | MB_OK);
		return;
	}

	int size = m_listFiles.GetSelectedCount();

	if(size <= 0)
	{
		MessageBox("Packing Type을 변경 할 파일을 선택하지 않았습니다.", NULL, MB_ICONWARNING | MB_OK);
		return;
	}

	POSITION pos = m_listFiles.GetFirstSelectedItemPosition();

	LV_ITEM lvItem;
	lvItem.mask		= LVIF_TEXT;

	for(int i = 0; i < size; ++i)
	{
		int idx = m_listFiles.GetNextSelectedItem(pos);

		lvItem.iSubItem = 3;
		lvItem.iItem	= idx;
		lvItem.pszText	= s_szPackingString[selectPatchType];

		m_listFiles.SetItem(&lvItem);

		CString listFileName = m_listFiles.GetItemText(idx, 0);
		CString listFilePath = m_listFiles.GetItemText(idx, 1);
		CString fileFullName = listFilePath + listFileName;

		FileCheckInfoTable::iterator iter = m_pSelectedFileCheckInfoTable->find((LPCTSTR)fileFullName);

		assert(iter != m_pSelectedFileCheckInfoTable->end());

		if(iter != m_pSelectedFileCheckInfoTable->end())
		{
			FileCheckInfo &findFileCheckInfo = iter->second;

			findFileCheckInfo.SetPackingType(selectPatchType);
		}
	}

	SavePatchListFile();
}


void CAutoPatchManagerDlg::OnBnClickedDelete()
{
	assert(m_pSelectedFileCheckInfoTable);

	if(!CheckWorkTheardRunning()) return;

	int size = m_listFiles.GetSelectedCount();

	if(size <= 0)
	{
		MessageBox("삭제할 파일을 선택하지 않았습니다.", NULL, MB_ICONWARNING | MB_OK);
		return;
	}

	if(MessageBox("선택한 파일들을 삭제하시겠습니까?", NULL, MB_ICONQUESTION | MB_YESNO) == IDNO)
	{
		return;
	}

	POSITION pos = m_listFiles.GetFirstSelectedItemPosition();

	std::vector<int> selectItemVec;
	selectItemVec.reserve(size);

	for(int i = 0; i < size; ++i)
	{
		int idx = m_listFiles.GetNextSelectedItem(pos);
		selectItemVec.push_back(idx);
	}

	std::vector<int>::reverse_iterator iter = selectItemVec.rbegin();

	for(; iter != selectItemVec.rend(); ++iter)
	{
		int idx = *iter;

		CString listFileName = m_listFiles.GetItemText(idx, 0);
		CString listFilePath = m_listFiles.GetItemText(idx, 1);
		CString fileFullName = listFilePath + listFileName;

		FileCheckInfoTable::iterator findPos = m_pSelectedFileCheckInfoTable->find((LPCTSTR)fileFullName);

		assert(findPos != m_pSelectedFileCheckInfoTable->end());

		if(findPos != m_pSelectedFileCheckInfoTable->end())
		{
			m_pSelectedFileCheckInfoTable->erase(findPos);
		}

		m_listFiles.DeleteItem(idx);
	}

	SavePatchListFile();
}


void CAutoPatchManagerDlg::BuildPatchFileListTable(LPCTSTR path)
{
//	assert(m_pSelectedFileCheckInfoTable);

	m_NewFileCheckInfoTable.clear();

	SetProgress("Build Patch File List", (int)USHRT_MAX);

	// 현재 디랙토리를 백업하고 path를 새로운 디랙토리로 설정
	char szCurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, szCurrentDir);
	SetCurrentDirectory(path);

	BuildPatchFileListTableImpl("");

	// 원래 디랙토리로 복구
	SetCurrentDirectory(szCurrentDir);
}

void CAutoPatchManagerDlg::BuildPatchFileListTableImpl(LPCTSTR path)
{
	//assert(m_pSelectedFileCheckInfoTable);

	WIN32_FIND_DATA fd;
	HANDLE			hFD;
	const char		*sName;

	char sPathAccess[MAX_PATH]; 
	char sRunPath[MAX_PATH]; 
	char sWildCard[MAX_PATH];

	int pathLength = (int)strlen(path);

	sprintf(sWildCard, "%s%s*.*", path, pathLength ? "/" : "");

	hFD = FindFirstFile(sWildCard, &fd);

	if (hFD != INVALID_HANDLE_VALUE)
	{
		do	
		{
			ZeroMemory( sPathAccess,	sizeof(sPathAccess	));
			ZeroMemory( sRunPath,		sizeof(sRunPath		));

			sName = fd.cFileName;

			sprintf(sPathAccess, "%s%s%s", path, pathLength ? "/" : "", sName);

//			sName = ::TrimGetRunName(fd.cFileName);

//			::TrimGetRunPath( sWildCard , sRunPath );
//			sprintf( sPathAccess, "%s/%s", sRunPath, sName);

			if((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
			{
				if(sName[0] != '.')
				{
					BuildPatchFileListTableImpl( sPathAccess );
				}
			}
			else
			{
				make_unique_path(sPathAccess);

				FileCheckInfo fileCheckInfo(sPathAccess);

				// 기존에 같은 이름의 파일이 있다면 패킹 타입을 기존 걸로 해주는게 편함
				FileCheckInfoTable::iterator pos = m_RecentFileCheckInfoTable.find(sPathAccess);

				if(pos != m_RecentFileCheckInfoTable.end())
				{
					FileCheckInfo &beforeFileCheckInfo = pos->second;
					fileCheckInfo.SetPackingType(beforeFileCheckInfo.GetPackingType());
				}

				m_NewFileCheckInfoTable.insert(
					FileCheckInfoTable::value_type(sPathAccess, fileCheckInfo));

				m_progressWorking.OffsetPos(1);
			}
		} while(FindNextFile(hFD, &fd));

		FindClose( hFD );
	}
}

void CAutoPatchManagerDlg::UpdateListCtrl()
{
	assert(m_pSelectedFileCheckInfoTable);

	char szPath[MAX_PATH];
	char szFNameExt[_MAX_FNAME + _MAX_EXT];
	char szFName[_MAX_FNAME]; 
	char szExt[_MAX_EXT]; 
	char szItemText[128];

	SetProgress("Update File List", (int)m_pSelectedFileCheckInfoTable->size());

	m_listFiles.DeleteAllItems();

	LV_ITEM lvItem;
	lvItem.mask		= LVIF_TEXT;

	FileCheckInfoTable::iterator pos = m_pSelectedFileCheckInfoTable->begin();

	int cnt = 0;
	for(; pos != m_pSelectedFileCheckInfoTable->end(); ++pos, ++cnt)
	{
		const std::string&		fileName = pos->first;
		const FileCheckInfo&	fileCheckInfo = pos->second;

		_splitpath(fileName.c_str(), NULL, szPath, szFName, szExt);

		strcpy(szFNameExt, szFName);
		strcat(szFNameExt, szExt);
		strupr(szExt);

		lvItem.iSubItem = 0;
		lvItem.iItem	= cnt;

		lvItem.pszText	= szFNameExt;

		m_listFiles.InsertItem(&lvItem);
		++lvItem.iSubItem;

		lvItem.pszText	= szPath;
		m_listFiles.SetItem(&lvItem);
		++lvItem.iSubItem;

		lvItem.pszText	= &szExt[1];
		m_listFiles.SetItem(&lvItem);
		++lvItem.iSubItem;

		assert(fileCheckInfo.GetPackingType() < PT_MAX);
		lvItem.pszText	= s_szPackingString[fileCheckInfo.GetPackingType()];
		m_listFiles.SetItem(&lvItem);
		++lvItem.iSubItem;

		const FILETIME	&lastWriteTime = fileCheckInfo.GetLastWriteTime();

		FILETIME		localTime;
		FileTimeToLocalFileTime(&lastWriteTime, &localTime);

		SYSTEMTIME		systemTime;
		FileTimeToSystemTime(&localTime, &systemTime);

		sprintf(szItemText, "%d-%02d-%02d %02d:%02d",
			systemTime.wYear, systemTime.wMonth, systemTime.wDay,
			systemTime.wHour, systemTime.wMinute);


		lvItem.pszText	= szItemText;
		m_listFiles.SetItem(&lvItem);
		++lvItem.iSubItem;

		sprintf(szItemText, "%10d", fileCheckInfo.GetFileSize());

		lvItem.pszText	= szItemText;
		m_listFiles.SetItem(&lvItem);
		++lvItem.iSubItem;

		memcpy(szItemText, fileCheckInfo.GetMD5CheckSum(), FileCheckInfo::CHECKSUM_SIZE);
		szItemText[FileCheckInfo::CHECKSUM_SIZE] = '\0';

		lvItem.pszText	= szItemText;
		m_listFiles.SetItem(&lvItem);
		++lvItem.iSubItem;
		m_progressWorking.OffsetPos(1);
	}


	int listItemCount = m_listFiles.GetItemCount();

	char buffer[128];
	sprintf(buffer, "File Count: %d", listItemCount);

	m_staticFileCount.SetWindowText(buffer);
}


void CAutoPatchManagerDlg::OnLvnColumnclickListFiles(NMHDR *pNMHDR, LRESULT *pResult)
{
	if(!CheckWorkTheardRunning()) return;

	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	int column = pNMLV->iSubItem;

	if(m_nLastClickedColumn == column)
		m_bColumnSort[column] = !m_bColumnSort[column];
	else
		m_bColumnSort[column] = TRUE;

	SortTextItems(column, m_bColumnSort[column]);

	m_nLastClickedColumn = column;

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


bool CAutoPatchManagerDlg::StartWorkThread(THEAD_FUNCTION theadFunction)
{
	if(!CheckWorkTheardRunning()) return false;

	m_hWorkThread = (HANDLE)_beginthreadex(
		NULL, 0, theadFunction, this, 0, (unsigned int *)&m_dwWorkThreadID);

	SetThreadPriority(m_hWorkThread, THREAD_PRIORITY_ABOVE_NORMAL);

	return true;
}


bool CAutoPatchManagerDlg::CheckWorkTheardRunning()
{
	if(m_hWorkThread)
	{
		DWORD dwExitCode;
		GetExitCodeThread(m_hWorkThread, &dwExitCode);

		if(dwExitCode == STILL_ACTIVE)
		{
			MessageBox("다른 작업이 진행중입니다.", NULL, MB_ICONERROR | MB_OK );
			return false;
		}

		CloseHandle(m_hWorkThread);
		m_hWorkThread		= NULL;
		m_dwWorkThreadID	= 0;
	}

	return true;
}


void CAutoPatchManagerDlg::SetProgress(LPCTSTR text, int range)
{
	m_progressWorking.SetRange32(0, range);
	m_progressWorking.SetPos(0);
	m_editWorking.SetWindowText(text);
}


void CAutoPatchManagerDlg::OnBnClickedRecentList()
{
	if(!CheckWorkTheardRunning()) return;

	SetRecentFileMode();
	StartWorkThread(UpdateListCtrl_Thread);
}

void CAutoPatchManagerDlg::OnBnClickedNewList()
{
	if(!CheckWorkTheardRunning()) return;

	SetNewFileMode();
	StartWorkThread(UpdateListCtrl_Thread);
}


void CAutoPatchManagerDlg::SavePatchListFile()
{
	SaveCompressFileCheckInfoTable(m_RecentFileCheckInfoTable, RECENT_PATCH_LIST_FILE_NAME);
	
	FileCheckInfo FileListVersion(RECENT_PATCH_LIST_FILE_NAME);

	std::ofstream fileVersion(RECENT_PATCH_LIST_VERSION_FILE_NAME, std::ios_base::binary);

	// 파일이름은 안 넣어도 되는데 과거 Updater와의 호환성을 위해 ㅠ _ㅠ
	int nameLength = static_cast<int>(strlen(RECENT_PATCH_LIST_FILE_NAME));
	fileVersion.write((const char *)&nameLength, sizeof(int));
	fileVersion.write((const char *)RECENT_PATCH_LIST_FILE_NAME, nameLength);
	
	FileListVersion.SaveToFile(fileVersion);
	fileVersion.close();
}


void CAutoPatchManagerDlg::LoadPatchListFile()
{
	if(access(RECENT_PATCH_LIST_FILE_NAME, 0))
	{
		/*
		MessageBox(
			"Patch List Data를 찾을 수 없습니다.\n\n"
			"Recent폴더의 파일 정보를 토대로 새로운 Data를 생성합니다.\n\n"
			"이 작업은 수분의 시간이 소요됩니다.", NULL, MB_ICONINFORMATION | MB_OK);

		SetRecentFileMode();
		BuildPatchFileListTable("Recent");
		SavePatchListFile();
		MessageBox("Patch List Data를 성공적으로 생성하였습니다.", NULL, MB_ICONINFORMATION | MB_OK);
		*/
	}
	else
	{
		LoadCompressFileCheckInfoTable(m_RecentFileCheckInfoTable, RECENT_PATCH_LIST_FILE_NAME);
	}
}


void CAutoPatchManagerDlg::SetRecentFileMode()
{
	m_pSelectedFileCheckInfoTable = &m_RecentFileCheckInfoTable;
}


void CAutoPatchManagerDlg::SetNewFileMode()
{
	m_pSelectedFileCheckInfoTable = &m_NewFileCheckInfoTable;
}


void CAutoPatchManagerDlg::OnBnClickedMake()
{
	StartWorkThread(MakePatch_Thread);
}
