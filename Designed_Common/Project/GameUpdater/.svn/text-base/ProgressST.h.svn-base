#ifndef _PROGRESSST_H
#define _PROGRESSST_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// ProgressST.h : header file
//

#define __COUNT__	1
#define __KBYTE__	1024
#define __MBYTE__	1024 * 1024

/////////////////////////////////////////////////////////////////////////////
// CProgressST window

class CProgressST : public CProgressCtrl
{
public:
	CProgressST();
	virtual ~CProgressST();
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressST)
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	//	BOOL SetBitmap(UINT nBitmapId = NULL, BOOL bRepaint = TRUE);
	//	BOOL SetBackgroundBitmap(UINT nBitmapId = NULL, BOOL bRepaint = TRUE);
	void	SetColor(COLORREF color)	{ m_Color = color; }
	void	SetBackColor(COLORREF color)	{ m_BackColor = color; }
	
	void SetRange(int nLower, int nUpper);
	void SetRange32(int nLower, int nUpper);
	int SetPos(int nPos);
	int OffsetPos(int nOffset);
	
	int SetStep(int nStep);
	int StepIt( );
	
	void	SetText(const char *str);
	void	SetDrawText(bool drawtext)	{ m_bDrawText = drawtext;	}
	
	static const char* GetVersionC();
	static const int GetVersionI();

	int		GetRangeUnit () { return m_RangeUnit; }
	void	SetRangeUnitK () { m_RangeUnit = __KBYTE__; }
	void	SetRangeUnitM () { m_RangeUnit = __MBYTE__; }
	void	SetRangeUnitC () { m_RangeUnit = __COUNT__; }
	
	static BOOL GetBitmapAndPalette(UINT nIDResource, CBitmap& bitmap, CPalette& pal, SIZE &imageSize);
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CProgressST)
	afx_msg void OnPaint();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
private:
	void CalcRange();
	void DrawProgress(CDC* pDC);
	// 	void TileBitmap(CDC * pDestDC, CDC* pSrcDC, int x, int y, int srcWidth, int srcHeight, int count = 1);
	
	int	m_RangeUnit;
	int m_nLower;
	int m_nUpper;
	int m_nRange;
	
	int m_nStep;
	
	int m_nPos;

	bool	m_bDrawText;
	
	CFont m_hfont;
	COLORREF m_BackColor, m_Color;
	//	CBitmap m_bmPattern;
	//	CBitmap m_bmBackground;
	//	CPalette m_Palette;
	//	CPalette m_BackgroundPalette;
	//	int m_nWidth;
	//	int m_nHeight;
	//	int m_nBackgroundWidth;
	//	int m_nBackgroundHeight;
	CString m_string;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif
