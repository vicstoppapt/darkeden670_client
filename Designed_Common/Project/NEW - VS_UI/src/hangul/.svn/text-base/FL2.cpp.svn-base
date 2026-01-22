// FL2.cpp

#include "client_PCH.h"

#include "FL2.h"
#include "VS_UI_Base.h"

//-----------------------------------------------------------------------------
// Utilities for IO.
//-----------------------------------------------------------------------------

//
// FL2ñÕ?? DCÜË ???ÍéøË surface? ???õµ. ?÷é? ÖÕ?××?øË ?Øó? 
// surface??×»Ý«, offscreen surfaceøË? ó¦ ? ??õµ.
//
// Unicorn edit line widgetñÕ? FL2ÜË ???ÍéøË øÉ?ñÕ? ? surfaceÜË Øº?ó¦
// ÷é?õµ.
//
LPDIRECTDRAWSURFACE7	gpC_fl2_surface = NULL;
HDC gh_FL2_DC = NULL;

//-----------------------------------------------------------------------------
// g_SetFL2Surface
//
// 
//-----------------------------------------------------------------------------
void g_SetFL2Surface(LPDIRECTDRAWSURFACE7 surface)
{
	gpC_fl2_surface = surface;
}

//-----------------------------------------------------------------------------
// g_PossibleStringCut
//
// sz_strÕÉ position(byte)? cut? ? ??? ?ù¼ÜË ?ÏçÊµõµ.
// sz_str? ÊµÞ¢ 2byte, Ë¬? 1byte?õµ.
//-----------------------------------------------------------------------------
bool g_PossibleStringCut(const char * sz_str, int position)
{
	if (sz_str != NULL)
	{
		if ((int)strlen(sz_str) <= position)
			return true;

		//
		// positionñÕ? Ðü?×» ÷úöáÕÉ data? ?? ? ?õµ.
		//
		// (1) ASCII
		// (2) ÊµÞ¢ 1 byte
		// (3) ÊµÞ¢ 2 byte
		//
		// øÉ?óÝ (3)ÕÉ ÷úöá øÉ ?? ASCII? ñÐ?äù? ×Ø?ó¦ ? ?õµ.
		// øÉ?? ??ù¼Úñ position?×» ø¢?ÜË òÚÎý Êµõµ.
		//
		enum _CODE
		{
			_ENG,
			_HAN,
		};

		_CODE code = _ENG;
		int i;
		for (i=0; i <= position; i++)
		{
			if ((BYTE)sz_str[i] > 128) // no ASCII?
			{
				i++;
				code = _HAN;
			}
			else
				code = _ENG;
		}

		if (code == _HAN)
			if (i <= position+1)
				return false;

		return true;
	}

	return false;
}

int g_GetStringWidth2(const char * sz_str, int Index, HFONT hfont)
{
	int iStrLen = strlen (sz_str);
	if(Index >= iStrLen)
		Index = iStrLen-1;

	assert(!gpC_base->m_p_DDSurface_back->IsLock());
	if (gpC_fl2_surface == NULL)
		_Error(NULL_REF);

	if (sz_str == NULL)
		return 0;

	HDC hdc;

	bool bGetDC = g_FL2_GetDC();

	hdc = gh_FL2_DC;
	
	if (hfont != NULL)
		SelectObject(hdc, hfont);

	SIZE size;
	GetTextExtentPoint32(hdc, sz_str, Index, &size);

	if(bGetDC)
		g_FL2_ReleaseDC();

	return size.cx;
}

// sz_str?Öð?×ð, Width?ñÕ Ðï?? ? ?? ?Öð?ÕÉ Index (base 0)ÜË ÏÀÛª×ýõµ. 
int g_GetStringIndexByWidth (const char *sz_str, int Width, HFONT hfont)
{
	int iStrWidth = g_GetStringWidth (sz_str, hfont);
	int resIndex;
	int Len = strlen(sz_str);

	if (iStrWidth <= Width)	//ÊçîÙ Ðï?Ôõõµ.
		resIndex = Len - 1;
	else
	{
		int Index = Len -1;
		while (--Index)
		{
			if (!g_PossibleStringCut (sz_str, Index))
				Index --;

			iStrWidth = g_GetStringWidth2 (sz_str, Index+1, hfont);
			if(iStrWidth <= Width)
				break;
		}
		//?Õô Index??.. Width?? ÖÁ×» Ï¿? ?Öð?ÕÉ Üõ×»Ý½ Ù»Ý¯ÚñÕÉ ÍÝÙ¹.
		resIndex = Index;
	}

	return resIndex;
}

int g_PrintColorStr2 (int x, int y, const char * sz_str, PrintInfo &pi, COLORREF str_rgb, int LimitWidth)
{
	int iStrWidth = g_GetStringWidth ((const char*)sz_str, pi.hfont);
	if (iStrWidth <= LimitWidth)
		return g_PrintColorStr (x, y, sz_str, pi, str_rgb);
	else
	{
		// Øó?ó¦ ?Öð?ÕÉ ?Ðë Ü©??, ÕôÊµ Ü©??õµ Ü©õµ. ÕôÊµ Ü©?ÜË ÖÁ×» Ï¿??.. ?Öð?? ÖðÝ×õµ..
		int Len = strlen (sz_str);
		char *strTemp = new char [Len + 1];

		int Index = Len - 1;
		while (--Index)
		{
			if (!g_PossibleStringCut (sz_str, Index))
			{
				//ÖðÜË ? ?? Index (ÊµÞ¢îü 2Î¯?? ?Öð??ñÕ?Ý« .. ?í¶)ÖÕ ÷úöá.. Êµ? ? --
				Index--;
			}
			//?Öð? Ü©? ý§ÛÎ..
			iStrWidth = g_GetStringWidth2 ((const char*)sz_str, Index-1, pi.hfont);
			if (iStrWidth <= LimitWidth)
				break;
		}
		// ?Öð?ÕÉ ???×» ?õµ?.. øÉÛíÝ¤? ÷ôÕÉ ??×»Ý«.. Ú¶?
		if (Index==0)
			return g_PrintColorStr (x, y, sz_str, pi, str_rgb);
		// ñÐ?äù?.. Index Ý«ÒÁÝ«.. øÉÝ¹õµ. ÖÕ?.. ÕÜ? ÖðÝ× õµ?ñÕ.. '..'? ??×ùÖð.
		strncpy (strTemp, sz_str, Index-2);
		strTemp [Index-2] = '.';
		strTemp [Index-1] = '.';
		strTemp [Index] = '\0';
		int res = g_PrintColorStr (x, y, (const char*)strTemp, pi, str_rgb);
		delete strTemp;
		return res;
	}
}

//-----------------------------------------------------------------------------
// g_GetStringWidth
//
// p_str? null terminated string?õµ.
// hfontÜË ?Î¯ÜØ? settingòÚÎý ?Ì³Êµ ?? óÝÊ¯õµ.
//
// ! Ï¨ù¼ñÕ? lock?? Ï­Ôõõµ.
//-----------------------------------------------------------------------------
int g_GetStringWidth(const char * sz_str, HFONT hfont)
{
	assert(!gpC_base->m_p_DDSurface_back->IsLock());
	if (gpC_fl2_surface == NULL)
		_Error(NULL_REF);

	if (sz_str == NULL)
		return 0;

	HDC hdc;

	bool bGetDC = g_FL2_GetDC();

	hdc = gh_FL2_DC;
	
	if (hfont != NULL)
		SelectObject(hdc, hfont);

	SIZE size;
	GetTextExtentPoint32(hdc, sz_str, strlen(sz_str), &size);

	if(bGetDC)
		g_FL2_ReleaseDC();

	return size.cx;
}

//-----------------------------------------------------------------------------
// g_GetStringHeight
//
// p_str? null terminated string?õµ.
// hfontÜË ?Î¯ÜØ? settingòÚÎý ?Ì³Êµ ?? óÝÊ¯õµ.
//
// !Ï¨ù¼ñÕ? lock?? Ï­Ôõõµ.
//-----------------------------------------------------------------------------
int g_GetStringHeight(const char * sz_str, HFONT hfont)
{
	assert(!gpC_base->m_p_DDSurface_back->IsLock());
	if (gpC_fl2_surface == NULL)
		_Error(NULL_REF);

	if (sz_str == NULL)
		return 0;
	
	HDC hdc;

	bool bGetDC = g_FL2_GetDC();

	hdc = gh_FL2_DC;
	
	
	if (hfont != NULL)
		SelectObject(hdc, hfont);

	SIZE size;
	GetTextExtentPoint32(hdc, sz_str, strlen(sz_str), &size);

	if(bGetDC)
		g_FL2_ReleaseDC();

	return size.cy;
}

//-----------------------------------------------------------------------------
// g_PrintLen
//
// gpC_fl2_surfaceñÕ Øó?Êµõµ.
// p_str? null terminated string?õµ.
//
// !Ï¨ù¼ñÕ? lock?? Ï­Ôõõµ.
//-----------------------------------------------------------------------------
void g_PrintLen(int x, int y, const char * sz_str, int str_length, PrintInfo * p_print_info)
{
	assert(!gpC_base->m_p_DDSurface_back->IsLock());
	if (sz_str!=NULL)
	{
		//assert(sz_str != NULL);
		assert(gpC_fl2_surface != NULL);

		// no Release exception handling code for speed.

		HDC hdc;

		bool bGetDC = g_FL2_GetDC();

		hdc = gh_FL2_DC;

		if (p_print_info != NULL)
		{
			SetTextAlign(hdc, p_print_info->text_align);
			SetBkMode(hdc, p_print_info->bk_mode);
			SetBkColor(hdc, p_print_info->back_color);
			SetTextColor(hdc, p_print_info->text_color);
			SelectObject(hdc, p_print_info->hfont);
		}

		TextOut(hdc, x, y, sz_str, str_length);

		if(bGetDC)
			g_FL2_ReleaseDC();

	}
}

std::string g_MakeLinefeedString(char* sz_src, int linewidth, HFONT hfont)
{
	assert (sz_src != NULL);

	std::string resultString = sz_src;

	int strWidth = g_GetStringWidth(sz_src, hfont);
	int LinefeedCount = strWidth/linewidth;

	int srcIndex = 0;
	int destIndex = 0;
	int LinefeedIndex = 0;
	for (int i=0; i<LinefeedCount; i++)
	{
		LinefeedIndex = g_GetStringIndexByWidth (&sz_src[srcIndex], linewidth, hfont);
		destIndex += LinefeedIndex;
		resultString.insert(destIndex, "\n");
		destIndex ++;
		srcIndex += LinefeedIndex;
	}
	return resultString;
}

void g_DrawText(RECT *pRt, const char* sz_str, PrintInfo * p_print_info)
{
	if(!pRt || !sz_str) return;

	assert(!gpC_base->m_p_DDSurface_back->IsLock());
	if (sz_str!=NULL)
	{
		//assert(sz_str != NULL);
		assert(gpC_fl2_surface != NULL);

		//sz_strÕÉ ?øË?Ðë ?ø·ËÔ pRtÕÉ ?? ý§ÛÎ??, ?Öð?? äùÖï??? ? ??? Ðá ?Ý¤Êµõµ.

		int str_length = strlen(sz_str);
		int destWidth = pRt->right - pRt->left;
		int strWidth = g_GetStringWidth(sz_str, p_print_info->hfont);
		int LinefeedCount = strWidth / destWidth;
		HFONT hfont = NULL;
		if (p_print_info)
			hfont = p_print_info->hfont;
		
		std::string srcStr = g_MakeLinefeedString ((char*)sz_str, destWidth, hfont);//sz_str;

	
/*		int srcIndex = 0;
		int destIndex = 0;
		int LinefeedIndex = 0;
		for (int i=0; i<LinefeedCount; i++)
		{
			LinefeedIndex = g_GetStringIndexByWidth (&sz_str[srcIndex], destWidth, hfont);
			destIndex += LinefeedIndex;
			srcStr.insert(destIndex, "\n");
			destIndex ++;
			srcIndex += LinefeedIndex;
		}*/

		int strHeight = g_GetStringHeight(sz_str, hfont);
		int destHeight = pRt->bottom - pRt->top;
		if (strWidth%destWidth) LinefeedCount++;
		pRt->bottom = pRt->top + strHeight * LinefeedCount;

		// no Release exception handling code for speed.

		HDC hdc;

		bool bGetDC = g_FL2_GetDC();

		hdc = gh_FL2_DC;

		if (p_print_info != NULL)
		{
			SetTextAlign(hdc, p_print_info->text_align);
			SetBkMode(hdc, p_print_info->bk_mode);
			SetBkColor(hdc, p_print_info->back_color);
			SelectObject(hdc, p_print_info->hfont);
//øÉÜÝÖð Øó?
			SetTextColor(hdc, 0);
			RECT sRt = {pRt->left+1, pRt->top+1, pRt->right+1, pRt->bottom+1};
			DrawText(hdc, srcStr.c_str(), srcStr.length(), &sRt, p_print_info->text_align);
//?Öð? Øó?
			SetTextColor(hdc, p_print_info->text_color);
			DrawText(hdc, srcStr.c_str(), srcStr.length(), pRt, p_print_info->text_align);

		}
		else
			DrawText(hdc, srcStr.c_str(), srcStr.length(), pRt, DT_LEFT);

		if(bGetDC)
			g_FL2_ReleaseDC();

	}
}



//-----------------------------------------------------------------------------
// g_DBCSLen
//
// p_dbcsÕÉ lengthÜË ?ÏçÊµõµ.
//-----------------------------------------------------------------------------
int g_DBCSLen(const char_t * p_dbcs)
{
	if (p_dbcs == NULL)
		return 0;

	int len = 0;
	while (*p_dbcs++ != 0)
		len++;

	return len;
}
int	g_GetByteLenth(const char_t * p_dbcs, int dbcs_len)
{

	if (p_dbcs == NULL || dbcs_len <= 0)
		return 0;
	// convert
	for (int i=0, c=0; i < dbcs_len; i++)
	{
		// check high byte
		if ((p_dbcs[i]&0xFF00) != 0)
		{
			c+=2;
		}
		else
		{
			c++;
		}
	}
	return c;

}
//-----------------------------------------------------------------------------
// g_Convert_DBCS_Ascii2SingleByte
//
// DBCS Ascii codeÜË single byteøË Î¯ðËõµ. õµÝ× ?Öðï¤? øÉðÂøË ?×»??õµ.
// p_new_bufÜË newøË ó¦õ»Êµõµ. ïÊäù? Ï¨ù¼ñÕ? p_new_bufÜË deleteòÚ?Îý Êµõµ.
//
// ?×ØÔõ bufferÕÉ Ü©?(by byte)ÜË ?ÏçÊµõµ.
//-----------------------------------------------------------------------------
int g_Convert_DBCS_Ascii2SingleByte(const char_t * p_dbcs, int dbcs_len, char * &p_new_buf)
{
	//
	// (1) ignore 'p_new_buf'.
	//

	if (p_dbcs == NULL || dbcs_len <= 0)
		return 0;

	int max_size = dbcs_len*2+1;

	char * p_temp = new char[max_size];
	CheckMemAlloc(p_temp);
	memset(p_temp, 0, max_size);

	// convert
	for (int i=0, c=0; i < dbcs_len; i++)
	{
		// check high byte
		if ((p_dbcs[i]&0xFF00) != 0)
		{
			*(char_t *)(p_temp+i+c) = p_dbcs[i];
			c++;
		}
		else
		{
			p_temp[i+c] = (char)(p_dbcs[i]);
		}
	}

	int len = strlen(p_temp);
	p_new_buf = new char[len+1];
	CheckMemAlloc(p_new_buf);

	strcpy(p_new_buf, p_temp);

	DeleteNewArray(p_temp);

	return len;
}

//-----------------------------------------------------------------------------
// g_ConvertAscii2DBCS
//
// ascii code(single byte?×» Ðï?)ÜË DBCSøË ùÞÏç?? p_new_bufñÕ ó¦õ»Êµõµ.
// p_new_buf? Ï¨ù¼ñÕ? deleteòÚÎý Êµõµ.
//
//-----------------------------------------------------------------------------
// p_ascii:		single byte string
// ascii_len:	p_ascii length
// p_new_buf:	converted DBCS buf
//
// return:		p_new_buf length
//					zero is failed.
//-----------------------------------------------------------------------------
int g_ConvertAscii2DBCS(const char * p_ascii, int ascii_len, char_t * &p_new_buf)
{
	if (p_ascii == NULL || ascii_len <= 0)
		return 0;

	int size = ascii_len+1;
	char_t * p_temp = new char_t[size];

	int dbcs = 0;
	for (int i=0; i<ascii_len; i++, dbcs++)
		if (isascii(p_ascii[i]) != 0) // ascii? or not hangul code?
		{
			// ascii

			p_temp[dbcs] = (char_t)p_ascii[i];
		}
		else
		{
			// hangul

			p_temp[dbcs] = *((char_t *)(p_ascii+i));
			i++;
		}

	// ?Ì³Êµ sizeÕÉ bufferÜË p_new_buf? ?Ý¤ùË?? Êµõµ.
	// ÊµÞ¢? Ðï?Ôô? dbcsËÔ ascii_len? õµÜØõµ.
	p_new_buf = new char_t[dbcs+1];

	for (int m=0; m < dbcs; m++)
		p_new_buf[m] = p_temp[m];

	DeleteNewArray(p_temp);
	p_new_buf[dbcs] = 0;

	return dbcs;
}

// DCÜË GetÊµõµ.
bool	g_FL2_GetDC()
{
	assert(!gpC_base->m_p_DDSurface_back->IsLock());
	if (gpC_fl2_surface == NULL)
		_Error(NULL_REF);

	if(gh_FL2_DC == NULL)
	{
		gpC_fl2_surface->GetDC(&gh_FL2_DC);

		return true;
	}

	return false;
}

// DCÜË Release Êµõµ.
bool	g_FL2_ReleaseDC()
{
	assert(!gpC_base->m_p_DDSurface_back->IsLock());
	if (gpC_fl2_surface == NULL)
		_Error(NULL_REF);

	if(gh_FL2_DC != NULL)
	{
		gpC_fl2_surface->ReleaseDC(gh_FL2_DC);
		gh_FL2_DC = NULL;

		return true;
	}

	return false;
}


////////////////////////////////////////////////
// ?? ??×ù? Ê«? by sonee
//
// ? ?ÖðÜË 40ÖðøË ??? ý£?? ReduceString(str,40);
// str ÖðÚ¶ÜË ùÞ÷úÊµõµ.
// ùÞ÷ú?×» Ï¿? Ý¤Úí??øË ó¦÷úöá Üõ×»Ý½ ùÒ?ù¼ùì? ?? øÉà÷ Ý¤Úí???
////////////////////////////////////////////////

void ReduceString(char *str,int len)
{
	if(len<15) return;
	char name[100]="",*p_name;
	int lt=strlen(str),passlen,position,size;
	p_name=&name[0];
	//bool g_PossibleStringCut(const char * sz_str, int position)
	if(lt>len)
	{
		if(g_PossibleStringCut(str,5))
			passlen=5;
		else	
			passlen=6;
		memcpy(p_name,str,passlen);
		p_name+=passlen;
		*(p_name++)='.';
		*(p_name++)='.';
		*(p_name++)='.';
		passlen+=3;
		size=passlen;
		position=lt-(len-passlen);
		if(g_PossibleStringCut(str,position))
			{
			position=lt-len+passlen;
			passlen=len-passlen;
		}
		else
			{
			position=lt-len+passlen-1;
			passlen=len-passlen+1;
		}
		size+=passlen;
		memcpy(p_name,str+position,passlen);		
		memcpy(str,name,size);
		str[size]='\0';		
	}		
}

// ?ù¼ùìñÕ ... ? ??×ýõµ.				 by sonee
void ReduceString2(char *str,int len)
{
	if(len<15) return;
	char name[100]="",*p_name;
	int lt=strlen(str),passlen,position,size;
	p_name=&name[0];
	//bool g_PossibleStringCut(const char * sz_str, int position)
	
	int skip_len=len-14;
	if(lt>len)
	{
		if(g_PossibleStringCut(str,skip_len))
			passlen=skip_len;
		else	
			passlen=skip_len+1;
		memcpy(p_name,str,passlen);
		p_name+=passlen;
		*(p_name++)='.';
		*(p_name++)='.';
		*(p_name++)='.';
		passlen+=3;
		size=passlen;
		position=lt-(len-passlen);
		if(g_PossibleStringCut(str,position))
			{
			position=lt-len+passlen;
			passlen=len-passlen;
		}
		else
			{
			position=lt-len+passlen-1;
			passlen=len-passlen+1;
		}
		size+=passlen;
		memcpy(p_name,str+position,passlen);		
		memcpy(str,name,size);
		str[size]='\0';		
	}		
}
// 2004, 10, 26, sobeit add start
void ReduceString3(char *str,int len)
{
	if(str == NULL) return;
	if(len<15) return;
	int CurLen = strlen(str);
	if(CurLen<=len) return;
	
	if(!g_PossibleStringCut(str,len))
		str[len-3] = '.';
	str[len-2] = '.';
	str[len-1] = '.';
	str[len] = '\0';
}
// 2004, 10, 26, sobeit add end

//-----------------------------------------------------------------------------
// g_PrintColorStrLen
//
// str? Øó?Êµ ?ÕÉ xÜË ?ÏçÊµõµ.
//-----------------------------------------------------------------------------
int g_PrintColorStrLen(int x, int y, const char * sz_str, int str_length, PrintInfo &pi, COLORREF str_rgb)
{
	PrintInfo use_pi = pi;

	use_pi.text_color = str_rgb;

	bool bGetDC = g_FL2_GetDC();

	g_PrintLen(x, y, sz_str, str_length, &use_pi);

	int re = (x+g_GetStringWidth(sz_str, use_pi.hfont));

	if(bGetDC)
		g_FL2_ReleaseDC();

	return re;
}


//-----------------------------------------------------------------------------
// g_PrintColorStrOut
//
// str? Øó?Êµ ?ÕÉ xÜË ?ÏçÊµõµ.
//-----------------------------------------------------------------------------
int g_PrintColorStrOut(int x, int y, const char * sz_str, PrintInfo &pi, COLORREF str_rgb, COLORREF out_rgb)
{
	PrintInfo use_pi = pi;

	use_pi.text_color = out_rgb;
	bool bGetDC = g_FL2_GetDC();
	g_Print(x-1, y, sz_str, &use_pi);
	g_Print(x+1, y, sz_str, &use_pi);
	g_Print(x, y-1, sz_str, &use_pi);
	g_Print(x, y+1, sz_str, &use_pi);

	use_pi.text_color = str_rgb;
	g_Print(x, y, sz_str, &use_pi);
	
	int re = (x+g_GetStringWidth(sz_str, use_pi.hfont));

	if(bGetDC)
		g_FL2_ReleaseDC();

	return re;
}

//-----------------------------------------------------------------------------
// g_PrintColorStrShadow
//
// str? Øó?Êµ ?ÕÉ xÜË ?ÏçÊµõµ.
//-----------------------------------------------------------------------------
int g_PrintColorStrShadow(int x, int y, const char * sz_str, PrintInfo &pi, COLORREF str_rgb, COLORREF shadow_rgb)
{
	assert(!gpC_base->m_p_DDSurface_back->IsLock());
	PrintInfo use_pi = pi;

	if(shadow_rgb == 0xFFFFFFFF)
	{
		int r = (str_rgb&0xFF0000) >> 16;
		int g = (str_rgb&0xFF00) >> 8;
		int b = str_rgb&0xFF;
//		shadow_rgb = RGB(max(0, r-150), max(0, g-150), max(0, b-150));
		shadow_rgb = RGB(r>>2, g>>2, b>>2);
	}

	bool bGetDC = g_FL2_GetDC();

	use_pi.text_color = shadow_rgb;
	g_Print(x+1, y+1, sz_str, &use_pi);

	use_pi.text_color = str_rgb;
	g_Print(x, y, sz_str, &use_pi);
	
	int re = (x+g_GetStringWidth(sz_str, use_pi.hfont));

	if(bGetDC)
		g_FL2_ReleaseDC();

	return re;
}

std::string g_GetNumberString(int number)
{
	char sz_temp[20];
	wsprintf(sz_temp, "%d", number);
	std::string sstr = sz_temp;
	for(int i = 3; i <= 13; i += 4)
		if((int)sstr.size() > i)sstr.insert(sstr.size()-i, ",");

	return sstr;
}


std::string g_GetStringByMoney(DWORD dwMoney)
{
	char TempBuffer[32] = {0,};
	std::string sstr;
	DWORD TempMoney = 0;
	if(dwMoney>=100000000) // ?
	{
		TempMoney = dwMoney / 100000000;
		if(TempMoney)
		{
			wsprintf(TempBuffer, "%d¾ï", TempMoney);
			sstr+= TempBuffer;
		}
	}
	if(dwMoney>=10000) // Ý«
	{
		TempMoney = (dwMoney%100000000) / 10000;
		if(TempMoney)
		{
			wsprintf(TempBuffer, "%d¸¸", TempMoney);
			sstr+= TempBuffer;
		}
	}
	
	TempMoney = (dwMoney%10000);
	if(TempMoney || 0 == dwMoney)
	{
		wsprintf(TempBuffer, "%d", TempMoney);
		sstr+= TempBuffer;
	}

	return sstr;
}















