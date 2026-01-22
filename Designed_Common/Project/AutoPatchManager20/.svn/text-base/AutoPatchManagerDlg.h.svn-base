// AutoPatchManagerDlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "FileCheckInfoTable.h"
//#include "Minizip/Zipper.h"


// CAutoPatchManagerDlg 대화 상자
class CAutoPatchManagerDlg : public CDialog
{
// 생성
public:
	CAutoPatchManagerDlg(CWnd* pParent = NULL);	// 표준 생성자

// 대화 상자 데이터
	enum { IDD = IDD_AUTOPATCHMANAGER_DIALOG };
	enum { COLUMN_SIZE = 3 };

	typedef unsigned (__stdcall *THEAD_FUNCTION)(void *);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원

public:
	void InitColumnSort();
	BOOL SortTextItems(int nCol, BOOL bAscending, int low = 0, int high = -1);

	void UpdateListCtrl();

	void BuildPatchFileListTable(LPCTSTR path);

	void SetRecentFileMode();
	void SetNewFileMode();

	void LoadPatchListFile();
	void SavePatchListFile();

	void SetProgress(LPCTSTR text, int range = 0);

	bool AutoSplitSpk(bool copySameFile = false);
	bool SplitSpk(LPCTSTR fileName, int UnitCount);
	bool IsTwoMultiplier(int num);

	void MakePatch();

	bool BackupUpdateToZip(const char *dirName, const char *zipName);

protected:
	bool SetFileWriteTimeInDirectory(const char* dirName, FILETIME& fileTime);


// 구현
protected:
	HICON	m_hIcon;

	BOOL	m_bColumnSort[COLUMN_SIZE];
	int		m_nLastClickedColumn;

	static char s_szPackingString[][6];

	void BuildPatchFileListTableImpl(LPCTSTR path);

	bool StartWorkThread(THEAD_FUNCTION theadFunction);
	bool CheckWorkTheardRunning();
	
	// 메시지 맵 함수를 생성했습니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CProgressCtrl	m_progressWorking;
	CListCtrl		m_listFiles;
	CComboBox		m_comboPackingType;
	CEdit			m_editWorking;
	CButton			m_checkCopyIdenticalFile;
	CStatic			m_staticFileCount;

	FileCheckInfoTable	m_RecentFileCheckInfoTable;
	FileCheckInfoTable	m_NewFileCheckInfoTable;

	FileCheckInfoTable* m_pSelectedFileCheckInfoTable;

	HANDLE			m_hWorkThread;
	DWORD			m_dwWorkThreadID;

	afx_msg void OnBnClickedSetPackingType();
	afx_msg void OnLvnColumnclickListFiles(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRecentList();
	afx_msg void OnBnClickedNewList();
	afx_msg void OnBnClickedMake();
	afx_msg void OnBnClickedDelete();
};
