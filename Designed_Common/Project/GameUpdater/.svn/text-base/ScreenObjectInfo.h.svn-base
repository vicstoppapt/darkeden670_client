// ScreenObjectInfo.h: interface for the ScreenObjectInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCREENOBJECTINFO_H__E0C712F9_7C30_48E2_B45B_1EBE6651A335__INCLUDED_)
#define AFX_SCREENOBJECTINFO_H__E0C712F9_7C30_48E2_B45B_1EBE6651A335__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct ScreenObjectInfo
{
private:
	ScreenObjectInfo();

public:
	~ScreenObjectInfo();

	static ScreenObjectInfo* Instance()
	{ 
		static ScreenObjectInfo instance;
		return &instance;
	}

	enum BUTTON_INDEX {
		BTN_CUSTOMERS,	BTN_ACCOUNT,
		BTN_START,		BTN_EXIT,
		BTN_MAX
	};

	enum VERSION_NUMBER_IMAGE {
		VERNUM_0,	VERNUM_1,	VERNUM_2,	VERNUM_3,	VERNUM_4,
		VERNUM_5,	VERNUM_6,	VERNUM_7,	VERNUM_8,	VERNUM_9,
		VERNUM_DOT,	VERNUM_VER,
		VERNUM_MAX
	};

	enum SELECT_RESOLUTION {
		SELRES_800x600,
		SELRES_1024x768,
		SELRES_1280x720,
		SELRES_1280x768,
		SELRES_1280x960,
		SELRES_1280x1024,
		SELRES_MAX
	};
	
	void InitNormal();
	void InitWebLogin();

public:
	CRect	rcWebBrowser;

	CRect	rcOnButton[BTN_MAX];
	//071004 zzi
	bool	bButtonEnable[BTN_MAX];
	//-
	int		nButtonResourceIdx[BTN_MAX];

	int		nVerNumResourceIdx[VERNUM_MAX];

	CPoint	ptVersionPosition;

	CRect	rcProgressFiles;
	CRect	rcProgressTotal;

	CRect	rcOnFullScreen;

	CRect	rcStatusString;
	CRect	rcStatusProgessString;

	CRect	rcDragWindow;

	CString strSelectResolution[SELRES_MAX];
};

#endif // !defined(AFX_SCREENOBJECTINFO_H__E0C712F9_7C30_48E2_B45B_1EBE6651A335__INCLUDED_)