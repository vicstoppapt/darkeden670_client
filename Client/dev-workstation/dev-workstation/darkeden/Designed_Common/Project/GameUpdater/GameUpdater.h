// NewUpdater2.h : main header file for the NEWUPDATER2 application
//

#if !defined(AFX_NEWUPDATER2_H__624F8840_DA39_4ACE_969E_4C86D2551ABE__INCLUDED_)
#define AFX_NEWUPDATER2_H__624F8840_DA39_4ACE_969E_4C86D2551ABE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


/////////////////////////////////////////////////////////////////////////////
// CGameUpdaterApp:
// See NewUpdater2.cpp for the implementation of this class
//

class CGameUpdaterApp : public CWinApp
{
public:
	CGameUpdaterApp();
	bool	ParsingRealServer(const char* pCommandLine);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGameUpdaterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGameUpdaterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWUPDATER2_H__624F8840_DA39_4ACE_969E_4C86D2551ABE__INCLUDED_)
