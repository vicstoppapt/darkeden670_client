// ProgressST.cpp : implementation file
//

#include "stdafx.h"
#include "ProgressST.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#undef THIS_FILE
//static char THIS_FILE[] = __FILE__;
//#endif

#include <string>

extern std::string GetSeperator(int num);

/////////////////////////////////////////////////////////////////////////////
// CProgressST

CProgressST::CProgressST()
{
	// Default range of the control
	m_nLower = 0;
	m_nUpper = 100;
	m_RangeUnit = __KBYTE__;
	CalcRange();

	// Default position
	m_nPos = 0;

	// Default step
	m_nStep = 10;

	LOGFONT lf;

	lf.lfHeight = 12; // 0 = default
	lf.lfWidth = 0; // 0 = 높이에 기준하여 자동으로 설정됨.
	lf.lfEscapement = 0; // 방향설정 (900, 2700)
	lf.lfOrientation = 0;
	lf.lfWeight = FW_BOLD;
	lf.lfItalic = 0; // 0 아닌 값이면 italic이다.
	lf.lfUnderline = 0;
	lf.lfStrikeOut = 0;
	lf.lfCharSet = HANGUL_CHARSET;//*/JOHAB_CHARSET;
	lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf.lfQuality = DEFAULT_QUALITY;
	lf.lfPitchAndFamily = DEFAULT_PITCH|FF_DONTCARE;
	strcpy(lf.lfFaceName, "돋움체");
	
	m_hfont.CreateFontIndirect(&lf);

	m_bDrawText = true;
} // End of CProgressST


CProgressST::~CProgressST()
{
} // End of ~CProgressST


BEGIN_MESSAGE_MAP(CProgressST, CProgressCtrl)
	//{{AFX_MSG_MAP(CProgressST)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressST message handlers

void CProgressST::OnPaint() 
{
	PAINTSTRUCT lpPaint;

	// If there is NO bitmap loaded
//	if (m_bmPattern.m_hObject == NULL) 
//	{
//		CProgressCtrl::OnPaint();
//		return;
//	}

	BeginPaint(&lpPaint);

	CWindowDC dc(this);
	
	RECT clientRect;
	GetClientRect(&clientRect);
	
	CDC bufferDC;
	bufferDC.CreateCompatibleDC(&dc);
	
	CBitmap bmpBuffer;
	bmpBuffer.CreateCompatibleBitmap(&dc, clientRect.right - clientRect.left+2, clientRect.bottom - clientRect.top+2);
	
	CBitmap* pOldBufferBitmap = bufferDC.SelectObject(&bmpBuffer);

	DrawProgress(&bufferDC);

	dc.BitBlt(0, 0, clientRect.right-clientRect.left+2, clientRect.bottom-clientRect.top+2, &bufferDC, 0, 0, SRCCOPY);
	
	bufferDC.SelectObject(pOldBufferBitmap);

	EndPaint(&lpPaint);
} // End of OnPaint


//BOOL CProgressST::SetBitmap(UINT nBitmapId, BOOL bRepaint)
//{
//	BITMAP bm;
//	BOOL bRet;
//
//	// Detach any previuos bitmap
//	m_bmPattern.Detach();
//
//	// Default return value
//	bRet = TRUE;
//
//	// Load new bitmap
//	if (nBitmapId != NULL)
//	{
//		bRet = GetBitmapAndPalette(nBitmapId, m_bmPattern, m_Palette);
//		// If all ok
//		if (bRet == TRUE)
//		{
//			// Get dimension
//			m_bmPattern.GetBitmap(&bm);
//			// Width of the bitmap
//			m_nWidth = bm.bmWidth;
//			// Height of the bitmap
//			m_nHeight = bm.bmHeight;
//		}
//	}
//
//	// Repaint control
//	if (bRepaint == TRUE) Invalidate();
//
//	return bRet;
//} // End of SetBitmap
//
//BOOL CProgressST::SetBackgroundBitmap(UINT nBitmapId, BOOL bRepaint)
//{
//	BITMAP bm;
//	BOOL bRet;
//
//	// Detach any previuos bitmap
//	m_bmBackground.Detach();
//
//	// Default return value
//	bRet = TRUE;
//
//	// Load new bitmap
//	if (nBitmapId != NULL)
//	{
//		bRet = GetBitmapAndPalette(nBitmapId, m_bmBackground, m_BackgroundPalette);
//		// If all ok
//		if (bRet == TRUE)
//		{
//			// Get dimension
//			m_bmBackground.GetBitmap(&bm);
//			// Width of the bitmap
//			m_nBackgroundWidth = bm.bmWidth;
//			// Height of the bitmap
//			m_nBackgroundHeight = bm.bmHeight;
//		}
//	}
//
//	// Repaint control
//	if (bRepaint == TRUE) Invalidate();
//
//	return bRet;
//} // End of SetBitmap


void CProgressST::DrawProgress(CDC * pDC)
{
	CRect ctrlRect;

	GetClientRect(ctrlRect);
	ctrlRect.right += 3;
	ctrlRect.bottom += 3;
//
//
//    CDC backDC;
//	backDC.CreateCompatibleDC(pDC);
//
//	// Select bitmap
//	CBitmap* pOldBackBitmap = backDC.SelectObject(&m_bmBackground);
//
//    CDC memDC;
//	memDC.CreateCompatibleDC(pDC);
//
//	// Select bitmap
//	CBitmap* pOldBitmap = memDC.SelectObject(&m_bmPattern);
//
//	// Create temporary DC & bitmap
//	CDC tempDC;
//	tempDC.CreateCompatibleDC(pDC);
//
//	CBitmap bitmapTemp;
//	bitmapTemp.CreateCompatibleBitmap(&memDC, ctrlRect.Width()+2, ctrlRect.Height()+2);
//	CBitmap* pOldTempBitmap = tempDC.SelectObject(&bitmapTemp);
//
//	TileBitmap(&tempDC, &backDC, 0, 0, m_nBackgroundWidth, m_nBackgroundHeight);
	{
		CBrush brush(m_BackColor);
		CBrush* pOldBrush = pDC->SelectObject(&brush);
		CPen pen;
		pen.CreatePen(PS_NULL, 0, RGB(0, 0, 0));
		CPen* pOldPen = pDC->SelectObject(&pen);
		pDC->Rectangle(0, 0, ctrlRect.Width()+3, ctrlRect.Height()+3);
		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);
	}


	// Calculate control's percentage to draw
//	int nPercentage;
//	nPercentage = (int)((100.0/m_nRange)*(abs(m_nLower)+m_nPos));

	// Adjust rectangle to draw on screen
	int Lower, Upper;
	GetRange(Lower, Upper);

//	double f = (double)(ctrlRect.Width())/abs(Upper-Lower)*GetPos();
	
//	if ((ctrlRect.left + f) > ctrlRect.right)
//	{
//		ctrlRect.right -= 1;
//	}
//	else
//	{
//		ctrlRect.left = ctrlRect.left + (int)f;
//	}
	// Leave space for border
//	ctrlRect.DeflateRect(1, 1);

	// Tile the bitmap into the temporary rectangle
//	const skull_max = 14;
//
//	int skull_count = skull_max - (int)((double)(skull_max)/abs(Upper-Lower)*GetPos());
//
//	TileBitmap(&tempDC, &memDC, 20 + (skull_max - skull_count)*m_nWidth, 26, m_nWidth, m_nHeight, skull_count);
//	TileBitmap(&tempDC, &memDC, 0, 0, GetPos()*m_nWidth/abs(Upper-Lower), m_nHeight);
//	memDC.Rectangle(-1, -1, GetPos()*m_nWidth/abs(Upper-Lower), m_nHeight+10);
	RECT LeftRect = ctrlRect, RightRect = ctrlRect;

	int pos = GetPos();
	int size = abs(Upper-Lower);

	/*
	if(size >= 1024)
	{
		pos /= 1024;
		size /= 1024;
	}
	*/

	if(size)
	{
		RightRect.left = LeftRect.right = pos*(ctrlRect.Width())/size;

		CBrush brush(m_Color);
		CBrush* pOldBrush = pDC->SelectObject(&brush);
		CPen pen;
		pen.CreatePen(PS_NULL, 0, RGB(0, 0, 0));
		CPen* pOldPen = pDC->SelectObject(&pen);
		pDC->Rectangle(0, 0, LeftRect.right, ctrlRect.Height());
		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);

		pDC->SetBkMode(TRANSPARENT);

		CString printString;
		if(m_string.IsEmpty())
		{
			if(Upper > 0)
			printString.Format("%d%%", pos*100/size);
		}
		else
		{
			printString = m_string;
		}

		if(m_bDrawText)
		{
			CFont *oldFont = pDC->SelectObject(&m_hfont);

			CRgn rgn;
			rgn.CreateRectRgn(LeftRect.left, LeftRect.top, LeftRect.right, LeftRect.bottom);
			pDC->SelectClipRgn(&rgn);
			pDC->SetTextColor(m_BackColor);

			pDC->DrawText(printString.GetBuffer(0), ctrlRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			rgn.DeleteObject();
			rgn.CreateRectRgn(RightRect.left, RightRect.top, RightRect.right, RightRect.bottom);
			pDC->SelectClipRgn(&rgn);
			pDC->SetTextColor(m_Color);

			pDC->DrawText(printString.GetBuffer(0), ctrlRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			pDC->SelectObject(oldFont);
		}
	}
	
	// Select and realize the palette
//	if(pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE && m_Palette.m_hObject != NULL)
//	{
//		pDC->SelectPalette(&m_Palette, FALSE);
//		pDC->RealizePalette();
//	}
//
//	// Copy from temporary DC to screen (only the percentage rectangle)
//	GetClientRect(ctrlRect);
//	ctrlRect.right += 2;
//	ctrlRect.bottom += 2;
//
//	tempDC.SetTextColor(RGB(255, 255, 255));
//	CString str;
//
//	if (m_string.IsEmpty())
//		str.Format("화일을 전송받고 있습니다. (%d%%)", (int)((double)(GetPos())/abs(Upper-Lower)*100));
//	else
//		str = m_string;
//	
//    tempDC.SetBkMode(TRANSPARENT);
//
//	CFont *oldFont = tempDC.SelectObject(&m_hfont);
//	tempDC.DrawText(str, &ctrlRect, DT_CENTER |DT_SINGLELINE);
//	tempDC.SelectObject(oldFont);
	
//	if (ctrlRect.IsRectEmpty() == FALSE)
//		pDC->BitBlt(0, 0, ctrlRect.Width(), ctrlRect.Height(), &tempDC, 0, 0, SRCCOPY);

	/* RFU
	CRect R;
	GetClientRect(R);
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText("Title", -1, R, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	*/

	// Restore old selected bitmaps
//	tempDC.SelectObject(pOldTempBitmap);
//	memDC.SelectObject(pOldBitmap);
//	backDC.SelectObject(pOldBackBitmap);
} // End of DrawProgress
//        CRgn rgn;
//        rgn.CreateRectRgn(LeftRect.left, LeftRect.top, LeftRect.right, LeftRect.bottom);
//        dc.SelectClipRgn(&rgn);
//        dc.SetTextColor(m_colTextBk);
//
//        dc.DrawText(str, ClientRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
//
//        rgn.DeleteObject();
//        rgn.CreateRectRgn(RightRect.left, RightRect.top, RightRect.right, RightRect.bottom);
//        dc.SelectClipRgn(&rgn);
//        dc.SetTextColor(m_colTextFore);
//
//        dc.DrawText(str, ClientRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


//void CProgressST::TileBitmap(CDC * pDestDC, CDC* pSrcDC, int x, int y, int srcWidth, int srcHeight, int count)
//{
//
//	for(int i = 0; i < count; i++)
//	{
//		pDestDC->BitBlt(x+i*srcWidth, y, srcWidth, srcHeight, pSrcDC, 0, 0, SRCCOPY);
//	}
//
////	int nHLoop;
////	int nVLoop;
////	int nHTiles;
////	int nVTiles;
////
////	// Calc number of horizontal tiles
////	nHTiles = (rect.Width() / nWidth);
////	if (rect.Width() % nWidth != 0) nHTiles++;
////	// Calc number of vertical tiles
////	nVTiles = (rect.Height() / nHeight);
////	if (rect.Height() % nHeight != 0) nVTiles++;
////
////	// Tile bitmap horizontally
////	for (nHLoop = 0; nHLoop < nHTiles; nHLoop++)
////	{
////		int width = nWidth;
////		if(nHLoop == nHTiles-1 && rect.Width() % width > 0)
////			width = rect.Width() % width;
////		
////		// Tile bitmap vertically
////		nVLoop = 0;
//////		for (nVLoop = 0; nVLoop < nVTiles; nVLoop++)
////		{
////			pDestDC->BitBlt((nHLoop*nWidth), (nVLoop*nHeight), width, nHeight, pSrcDC, 0, 0, SRCCOPY);
////		}
////	}
//} // End of TileBitmap


void CProgressST::CalcRange()
{
	m_nRange = abs(m_nUpper - m_nLower);
	// Avoid divide by zero
	if (m_nRange == 0) m_nRange = 1;
} // End of CalcRange


void CProgressST::SetRange(int nLower, int nUpper)
{
	m_nLower = nLower;
	m_nUpper = nUpper;
	CalcRange();

	CProgressCtrl::SetRange(nLower, nUpper);
} // End of SetRange

void CProgressST::SetRange32(int nLower, int nUpper)
{
	m_nLower = nLower;
	m_nUpper = nUpper;
	CalcRange();

	CProgressCtrl::SetRange32(nLower, nUpper);
} // End of SetRange

int CProgressST::SetStep(int nStep)
{
	m_nStep = nStep;
	return CProgressCtrl::SetStep(nStep);
} // End Of SetStep


int CProgressST::SetPos(int nPos)
{
	// Bound checking
	if (nPos < m_nLower) nPos = m_nLower;
	if (nPos > m_nUpper) nPos = m_nUpper;

	m_nPos = nPos;

	return CProgressCtrl::SetPos(nPos);
} // End of SetPos


int CProgressST::OffsetPos(int nOffset)
{
	return SetPos(GetPos() + nOffset);
}


int CProgressST::StepIt()
{
	m_nPos += m_nStep;

	// Bound checking
	if (m_nPos > m_nUpper) m_nPos = m_nLower + (m_nPos - m_nUpper);

	return CProgressCtrl::StepIt();
} // End of StepIt


BOOL CProgressST::GetBitmapAndPalette(UINT nIDResource, CBitmap& bitmap, CPalette& pal, SIZE &imageSize)
{
	LPCTSTR lpszResourceName = (LPCTSTR)nIDResource;

	HBITMAP hBmp = (HBITMAP)::LoadImage( AfxGetInstanceHandle(), 
		lpszResourceName, IMAGE_BITMAP, 0,0, LR_CREATEDIBSECTION);

	if (hBmp == NULL) return FALSE;

	bitmap.Attach(hBmp);

	// Create a logical palette for the bitmap
	DIBSECTION ds;
	BITMAPINFOHEADER &bmInfo = ds.dsBmih;
	bitmap.GetObject(sizeof(ds), &ds);

	int nColors = bmInfo.biClrUsed ? bmInfo.biClrUsed : 1 << bmInfo.biBitCount;

	// Create a halftone palette if colors > 256. 
	CClientDC dc(NULL); // Desktop DC

	if(nColors > 256)
		pal.CreateHalftonePalette(&dc);
	else
	{
		// Create the palette
		RGBQUAD *pRGB = new RGBQUAD[nColors];
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);
		memDC.SelectObject( &bitmap );
		::GetDIBColorTable( memDC, 0, nColors, pRGB );
		UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
		LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];
		pLP->palVersion = 0x300;
		pLP->palNumEntries = nColors;
		for (int i=0; i < nColors; i++)
		{
			pLP->palPalEntry[i].peRed = pRGB[i].rgbRed;
			pLP->palPalEntry[i].peGreen = pRGB[i].rgbGreen;
			pLP->palPalEntry[i].peBlue = pRGB[i].rgbBlue;
			pLP->palPalEntry[i].peFlags = 0;
		}
		pal.CreatePalette( pLP );
		delete[] pLP;
		delete[] pRGB;
	}
	
	imageSize.cx = bmInfo.biWidth;
	imageSize.cy = bmInfo.biHeight;

	return TRUE;
} // End of GetBitmapAndPalette


const char* CProgressST::GetVersionC()
{
  return "1.0";
} // End of GetVersionC


const int CProgressST::GetVersionI()
{
  return 10; // Divide by 10 to get actual version
} // End of GetVersionI

void	CProgressST::SetText(const char *str)
{
	if(str == NULL)
		m_string = "";
	else
		m_string = str;

//	Invalidate();
}
