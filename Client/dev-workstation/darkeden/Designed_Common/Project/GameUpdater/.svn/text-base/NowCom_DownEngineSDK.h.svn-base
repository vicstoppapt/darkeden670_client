#pragma once

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
// FILE			:	DownEngineSDK.h
// AUTHOR		:	pco96
// DATE			:	2007.04.25
// COPYRIGHT	:	NOWCOM Co., LTD. 2006-
// DESCRIPTIONS	:	Interface of the CDownEngineSDK class.
// REMARKS		:	파일 다운로드 수행 SDK (MFC 사용 프로젝트)
// MODIFY		:	
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

#ifndef IN
# define IN
#endif

#ifndef OUT
# define OUT
#endif

#if _MFC_VER < 0x0700
typedef CString CStringA;
#endif

class CDownEngineSDK
{
public:
	CDownEngineSDK(void);
	~CDownEngineSDK(void);

public:

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// DownEngineSDK 초기화 및 종료
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	int		Create(IN const CString& strDllPath);
	void	Close();

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// DownEngineSDK 다운로드 준비를 위한 설정
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	
	int		SetDownloadFileInfo(IN const CString& strDownloadFullPath, IN const CString& strDownloadURL);
	int		SetDownloadFolderInfo(IN const CString& strDownloadFolderPath, IN const CString& strDownloadURL);

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// DownEngineSDK 다운로드 시작 및 진행 상황 체크
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	int		AutoPatchStart();
	void	GetDownloadInfo(OUT ULONG* pulDownCompleteCount, OUT ULONG* pulDownloadSpeed, OUT ULONGLONG* pullDownloadSize, OUT ULONG* pulExtraTime, OUT ULONG* pulLapseTime);

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// DownEngineSDK로부터 정보를 받는 Callback 함수 설정
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	void SetParentWindow(IN void* pParentWindow);
	void SetDrawFileInfoCallback(IN void* pfnDraw);
	void SetNotifyDownStartCallBack(IN void* pfnDraw);
	void SetNotifyDownCompleteCallBack(IN void* pfnDraw);



	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// 유니코드와 ANSI코드간의 변환 함수
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef _UNICODE
	static CStringA StringConvert_T2A(LPCTSTR psString)
	{
		CStringA strAnsiString;
		int nLen = ::WideCharToMultiByte(CP_ACP, NULL, psString, -1, NULL, 0, NULL, FALSE);
		CHAR* psAnsiString = new CHAR[nLen+1];
		::WideCharToMultiByte(CP_ACP, NULL, psString, -1, psAnsiString, nLen, NULL, FALSE);
		strAnsiString = psAnsiString;
		delete[] psAnsiString;

		return strAnsiString;
	}
	static CString StringConvert_A2T(LPCSTR psString)
	{
		CString strStringT;
		int nLen = ::MultiByteToWideChar(CP_ACP, NULL, psString, -1, NULL, NULL);
		TCHAR* psStringT = new TCHAR[nLen+1];
		::MultiByteToWideChar(CP_ACP, NULL, psString, -1, psStringT, nLen);
		strStringT = psStringT;
		delete[] psStringT;

		return strStringT;
	}
#else
	inline static CStringA	StringConvert_T2A(LPCTSTR psStringT)	{return CStringA(psStringT);}
	inline static CString	StringConvert_A2T(LPCSTR psStringA)		{return CString(psStringA);}
#endif

protected:
	// DLL 핸들
	HINSTANCE				m_hDownEngineAPI;


	// DLL 내의 함수원형 정의
	typedef int (*LPFNCREATE)(LPCSTR pszDllPath);
	typedef void (*LPFNCLOSE)();

	typedef int (*LPFNSETDOWNLOADFILEINFO)(LPCSTR pszDownloadFullPath, LPCSTR pszDownloadURL);
	typedef int (*LPFNSETDOWNLOADFOLDERINFO)(LPCSTR pszDownloadFolderPath, LPCSTR pszDownloadURL);

	typedef int (*LPFNAUTOPATCHSTART)();
	typedef void (*LPFNGETDOWNLOADINFO)(OUT ULONG* pulDownCompleteCount, OUT ULONG* pulDownloadSpeed, OUT ULONGLONG* pullDownloadSize, OUT ULONG* pulExtraTime, OUT ULONG* pulLapseTime);

	// 콜백함수 설정용
	typedef void (*LPFNSETPARENTWINDOW)(void* pParentWnd);
	typedef void (*LPFNSETDRAWFILEINFO)(void* pfnDraw);
	typedef void (*LPFNUPDATESTARTBUTTON)(void* pfnDraw);
	typedef void (*LPFNNOTIFYDOWNCOMPLETE)(void* pfnDraw);

	typedef void (*LPFNUPDATEDLL)(LPCSTR pszZipPath, LPCSTR pszDllPath);
};
