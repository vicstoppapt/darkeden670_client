// VS_UI_Title.cpp

#include "client_PCH.h"
#include "MTopView.h"
#include "VS_UI.h"

#include "VS_UI_filepath.h"
#include "VS_UI_Message.h"
#include "VS_UI_Mouse_pointer.h"
#include "VS_UI_GameCommon.h"
#include "UserOption.h"
#include "ClientConfig.h"

//#include "ExperienceTable.h"	//char_infoÁö¿ï¶§ Áö¿ï°Í
#include "MGuildMarkManager.h"
#include "KeyAccelerator.h"
#include "UserInformation.h"
#include <time.h>

#include "MItemOptionTable.H"
#include "mgamestringtable.H"
#include "SkinManager.h"
#include "ServerInformation.h"

#include "TickTimer.h"

#include <windows.h>

#if __CONTENTS(__TITLE_UI_RENWEAL)
	#include "VS_UI_NewTitle.h"
#else	//__TITLE_UI_RENWEAL
	#include "VS_UI_Title.h"
#endif //__TITLE_UI_RENWEAL

#if __CONTENTS(__TITLE_UI_RENWEAL)

#define LOGIN_ID_X 7 // »ó´ë°ª
#define LOGIN_ID_Y 3
#define LOGIN_PASSWORD_X 7
#define LOGIN_PASSWORD_Y 34

#define	MAX_SOUND_VOLUME		15
#define	MAX_MUSIC_VOLUME		15
#define MIN_GAMMA_VALUE			50
#define	MAX_GAMMA_VALUE			100
#define	MAX_MOUSE_SPEED			100
#define MAX_ALPHA_DEPTH			31
//bool gbl_option_running = false;

#ifdef _LIB
	extern BOOL g_bEnable3DHAL;
#else
	BOOL g_bEnable3DHAL = TRUE;
#endif

extern bool		g_bFamily;
extern DWORD g_CurrentFrame;
extern int		g_LeftPremiumDays;
extern BYTE		g_PayType;

extern MTopView*	g_pTopView;

void ExecF_OptionResetButton(C_VS_UI_DIALOG * p_this_dialog, id_t id)
{
	switch( id )
	{
	case DIALOG_EXECID_OK :
		gpC_base->SendMessage( UI_RESET_BUTTON );
		break;
	case DIALOG_CANCEL:

		break;
		
	}
}
void ExecF_EXITQuestion(C_VS_UI_DIALOG * p_this_dialog, id_t id)
{
	switch( id )
	{
	case DIALOG_EXECID_OK :
		gpC_base->SendMessage(UI_TERMINATION, 0, 0);
		break;
	case DIALOG_CANCEL:

		break;
	}
}


/*
//----------------------------------------------------------------------------
// static
//----------------------------------------------------------------------------
C_VS_UI_OPTION::GAMEMENU_SPK_INDEX			
C_VS_UI_OPTION::m_sprite_id[C_VS_UI_OPTION::MENU_COUNT][4] =
// { normal, focused, checked, focused&checked }
{
	{ SPK_NORMAL_BOX, SPK_FOCUSED_BOX, SPK_CHECKED_BOX, SPK_FOCUSED_CHECKED_BOX }, //USE_3D_HAL,
//	{ SPK_NORMAL_BOX, SPK_FOCUSED_BOX, SPK_CHECKED_BOX, SPK_FOCUSED_CHECKED_BOX }, //DRAW_MINIMAP,
//	{ SPK_NORMAL_BOX, SPK_FOCUSED_BOX, SPK_CHECKED_BOX, SPK_FOCUSED_CHECKED_BOX }, //DRAW_ZONE_NAME,
//	{ SPK_NORMAL_BOX, SPK_FOCUSED_BOX, SPK_CHECKED_BOX, SPK_FOCUSED_CHECKED_BOX }, //DRAW_GAME_TIME,
//	{ SPK_NORMAL_BOX, SPK_FOCUSED_BOX, SPK_CHECKED_BOX, SPK_FOCUSED_CHECKED_BOX }, //DRAW_BLENDING_CHARACTER_SHADOW,
	{ SPK_NORMAL_BOX, SPK_FOCUSED_BOX, SPK_CHECKED_BOX, SPK_FOCUSED_CHECKED_BOX }, //PLAY_SOUND,
	{ SPK_NORMAL_BOX, SPK_FOCUSED_BOX, SPK_CHECKED_BOX, SPK_FOCUSED_CHECKED_BOX }, //PLAY_MUSIC,
	{ SPK_SCROLL_NORMAL_SELECT, SPK_SCROLL_FOCUSED_SELECT, SPK_SCROLL_NORMAL_SELECT, SPK_SCROLL_FOCUSED_SELECT }, //VOLUME_SOUND,
	{ SPK_SCROLL_NORMAL_SELECT, SPK_SCROLL_FOCUSED_SELECT, SPK_SCROLL_NORMAL_SELECT, SPK_SCROLL_FOCUSED_SELECT }, //VOLUME_MUSIC,
	{ SPK_NORMAL_BOX, SPK_FOCUSED_BOX, SPK_CHECKED_BOX, SPK_FOCUSED_CHECKED_BOX }, //PLAY_WAV,
	{ SPK_NORMAL_BOX, SPK_FOCUSED_BOX, SPK_CHECKED_BOX, SPK_FOCUSED_CHECKED_BOX }, //PLAY_MIDI,
	{ SPK_NORMAL_BOX, SPK_FOCUSED_BOX, SPK_CHECKED_BOX, SPK_FOCUSED_CHECKED_BOX }, //FILTERING_CURSE,
	{ SPK_NORMAL_BOX, SPK_FOCUSED_BOX, SPK_CHECKED_BOX, SPK_FOCUSED_CHECKED_BOX }, //VIEW_BLOOD,
	{ SPK_NORMAL_BOX, SPK_FOCUSED_BOX, SPK_CHECKED_BOX, SPK_FOCUSED_CHECKED_BOX }, //PARTY_HPBAR_ALPHA,
	{ SPK_NORMAL_BOX, SPK_FOCUSED_BOX, SPK_CHECKED_BOX, SPK_FOCUSED_CHECKED_BOX }, //IFEEL
	{ SPK_NORMAL_BOX, SPK_FOCUSED_BOX, SPK_CHECKED_BOX, SPK_FOCUSED_CHECKED_BOX }, //USE_GAMMA
	{ SPK_SCROLL_NORMAL_SELECT, SPK_SCROLL_FOCUSED_SELECT, SPK_SCROLL_NORMAL_SELECT, SPK_SCROLL_FOCUSED_SELECT }, //GAMMA_VALUE
	{ SPK_NORMAL_BOX, SPK_FOCUSED_BOX, SPK_CHECKED_BOX, SPK_FOCUSED_CHECKED_BOX }, //CHAT_BOX
};

// by sigi
void ExecF_TitleOption(C_VS_UI_DIALOG * p_this_dialog, id_t id)
{
	switch (id)
	{
		case DIALOG_EXECID_CANCEL:
		case DIALOG_EXECID_EXIT:
		case DIALOG_EXECID_OK:
			gpC_base->SendMessage( UI_CLOSE_TITLE_OPTION );
			gbl_title_option_running = false;
		break;
	}

	gC_vs_ui.AcquireChatting();
}
*/
//----------------------------------------------------------------------------
// Prototype
//----------------------------------------------------------------------------
void _Timer_CharUpdate();
void _Timer_CharUpdate2();
void _Timer_CharUpdate3();

//----------------------------------------------------------------------------
// Globals
//----------------------------------------------------------------------------
timer_id_t					g_char_update_tid = INVALID_TID;

int							g_char_index;

const int TITLE_X = 400, TITLE_Y = 21;
// heart rect	
#define HEART_WIDTH			152
#define HEART_HEIGHT		246
#define HEART_Y				166
int g_heart_rect[] = {254, 441, 628};

namespace					// 2003.9.29		by sonee µýµ¥¼± ¾È¾´´Ù ¤¾¤¾ 
{
	int			g_vs_ui_title_only_premium_x = 517;			// ÇÁ¸®¹Ì¾ö Á¤º¸ ÂïÈ÷´Â À§Ä¡
	int			g_vs_ui_title_only_premium_y = 499;			// ÇÁ¸®¹Ì¾ö Á¤º¸ ÂïÈ÷´Â À§Ä¡
};	

int C_VS_UI_NEWCHAR::m_hair_color_array[COLOR_LIST_X][COLOR_LIST_Y] = {
	
	/*
	{0, 15, 30},
	{90, 165, 240},
	{225, 105, 60},
	{285, 210, 120},
	{180, 195, 150}, 
	{270, 75, 255},
	{45, 135, 300}, 
	{315, 330, 345},
	*/
	// »ö±ò ¹Ù²¼¾î¿ä.. by sigi
	{ 57, 70, 86 },
	{ 101, 115, 130 },
	{ 145, 159, 174 },
	{ 193, 207, 222 },
	{ 237, 252, 267 },
	{ 283, 297, 312 },
	{ 327, 342, 359 },
	{ 369, 381, 400 },
};

int C_VS_UI_NEWCHAR::m_skin_color_array[COLOR_LIST_X][COLOR_LIST_Y] = {
/*	{405, 412, 419}, 
	{420, 428, 434}, 
	{435, 442, 449}, 
	{450, 457, 464}, 
	{465, 472, 479}, 
	{480, 487, 494}, 
	{389, 390, 374}, 
	{359, 375, 403},
	*/	
	{ 494, 487, 480 },
	{ 479, 471, 466 },
	{ 464, 455, 451 },
	{ 449, 440, 435 },
	{ 434, 426, 420 },
	{ 419, 412, 407 },
	{ 371, 364, 381 },
	{ 179, 170, 165 },
};

// Item blink color table
int ga_blink_color_table[INTERFACE_BLINK_VALUE_MAX] = {
	LIGHT_BLUE, LIGHT_BLUE, WHITE, WHITE
};



//-----------------------------------------------------------------------------
// SendCharacterDeleteToClient
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_CHAR_DELETE::SendCharacterDeleteToClient()
{
	// staticÀ¸·Î ÇÏ°í ¿ÜºÎ¿¡¼­ stringÀº deleteÇØÁØ´Ù.

	static DELETE_CHARACTER S_delete_char;

	// ³Ý¸¶ºí¿ë
	if(!(g_pUserInformation->IsNetmarble && g_pUserInformation->IsNetmarbleLogin))
	{
		g_Convert_DBCS_Ascii2SingleByte(m_lev_ssn_part1.GetString(), m_lev_ssn_part1.Size(), S_delete_char.sz_part1);
#if !__CONTENTS(__CHAR_DELETE)
		g_Convert_DBCS_Ascii2SingleByte(m_lev_ssn_part2.GetString(), m_lev_ssn_part2.Size(), S_delete_char.sz_part2);
#endif	//__CHAR_DELETE
	}
	else if(g_pUserInformation->IsNetmarble && g_pUserInformation->IsNetmarbleLogin)
	{
		g_Convert_DBCS_Ascii2SingleByte(m_lev_ssn_part1.GetString(), m_lev_ssn_part1.Size(), S_delete_char.sz_part1);
	}
	S_delete_char.slot = m_selected_slot;

	gpC_base->SendMessage(UI_DELETE_CHARACTER, 0, 0, &S_delete_char);
	
}

//-----------------------------------------------------------------------------
// C_VS_UI_CHAR_DELETE
//
// 
//-----------------------------------------------------------------------------
C_VS_UI_CHAR_DELETE::C_VS_UI_CHAR_DELETE()
{
	g_RegisterWindow(this);

	AttrTopmost(true);
	AttrKeyboardControl(true);

	// ³Ý¸¶ºí¿ë
	int w_h = 207;
	//if((g_pUserInformation->IsNetmarble && g_pUserInformation->IsNetmarbleLogin))
	//	w_h = 127;

	int cancel_offset_x, cancel_offset_y;
	int ok_offset_x, ok_offset_y;
	int ssn_part1_x, ssn_y, ssn_part2_x;

	{
//		m_pC_image_spk = new C_SPRITE_PACK(SPK_CHAR_DELETE);
		ok_offset_x = 189-26;
		ok_offset_y = w_h-60;
		cancel_offset_x = 253-24;
		cancel_offset_y = w_h-60;
		ssn_part1_x = 55;
		ssn_part2_x = 175;
		ssn_y = 108;
	}

	//Set(RESOLUTION_X/2-324/2, RESOLUTION_Y/2-w_h/2, 324, w_h);
	Set(g_pUserInformation->iResolution_x/2-324/2, g_pUserInformation->iResolution_y/2-w_h/2, 324, w_h);

	m_pC_button_group = new ButtonGroup(this);
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(x+ok_offset_x, y+ok_offset_y, gpC_global_resource->m_pC_assemble_box_button_spk->GetWidth(C_GLOBAL_RESOURCE::AB_BUTTON_OK), gpC_global_resource->m_pC_assemble_box_button_spk->GetHeight(C_GLOBAL_RESOURCE::AB_BUTTON_OK), DELETE_OK, this, C_GLOBAL_RESOURCE::BUTTON_OK_TITLE_RENEWAL));
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(x+cancel_offset_x, y+cancel_offset_y, gpC_global_resource->m_pC_assemble_box_button_spk->GetWidth(C_GLOBAL_RESOURCE::AB_BUTTON_OK), gpC_global_resource->m_pC_assemble_box_button_spk->GetHeight(C_GLOBAL_RESOURCE::AB_BUTTON_OK), DELETE_CANCEL, this, C_GLOBAL_RESOURCE::BUTTON_CANCEL_TITLE_RENEWAL));

	if( g_pUserInformation->IsNetmarble) // && g_pUserInformation->IsNetmarbleLogin)
	{
		m_lev_ssn_part1.SetPosition(x+ssn_part1_x, y+ssn_y);
		m_lev_ssn_part1.SetByteLimit(SSN_PART1_CHAR_COUNT + 1);
		Attach(&m_lev_ssn_part1);
	}
	else
	{

		m_lev_ssn_part1.SetPosition(x+ssn_part1_x, y+ssn_y);
		m_lev_ssn_part1.SetByteLimit(SSN_PART1_CHAR_COUNT
#if __CONTENTS(__CHAR_DELETE)
			+1
#endif //__CHAR_DELETE
			);
		Attach(&m_lev_ssn_part1);
#if !__CONTENTS(__CHAR_DELETE)	
		m_lev_ssn_part2.SetPosition(x+ssn_part2_x, y+ssn_y);
		m_lev_ssn_part2.SetByteLimit(SSN_PART2_CHAR_COUNT);
		m_lev_ssn_part2.PasswordMode(true);
		Attach(&m_lev_ssn_part2);
#endif	//__CHAR_DELETE
	}
}

//-----------------------------------------------------------------------------
// ~C_VS_UI_CHAR_DELETE
//
// 
//-----------------------------------------------------------------------------
C_VS_UI_CHAR_DELETE::~C_VS_UI_CHAR_DELETE()
{
	g_UnregisterWindow(this);

//	if( gC_ci->IsChinese() )
//		m_lev_ssn_part1.Unacquire();
// 	else 
	if(g_pUserInformation->IsNetmarble) // && g_pUserInformation->IsNetmarbleLogin)
	{
		m_lev_ssn_part1.Unacquire();
	}
	else
	{
		m_lev_ssn_part1.Unacquire();
#if !__CONTENTS(__CHAR_DELETE)
		m_lev_ssn_part2.Unacquire();
#endif	//__CHAR_DELETE
	}

//	DeleteNew(m_pC_image_spk);
	DeleteNew(m_pC_button_group);
}

void	C_VS_UI_CHAR_DELETE::ShowButtonDescription(C_VS_UI_EVENT_BUTTON * p_button)
{
	static char * m_help_string[2] = {
		(*g_pGameStringTable)[UI_STRING_MESSAGE_CHAR_DELETE].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_CHAR_CANCEL].GetString()
	};

	g_descriptor_manager.Set(DID_INFO, p_button->x, p_button->y, (void *)m_help_string[p_button->GetID()],0,0);
}

//-----------------------------------------------------------------------------
// C_VS_UI_CHAR_DELETE::ShowButtonWidget
//
// 
//-----------------------------------------------------------------------------
void	C_VS_UI_CHAR_DELETE::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{	
	if (p_button->GetFocusState() && p_button->GetPressState())
		gpC_global_resource->m_pC_common_button_spk->BltLocked(p_button->x, p_button->y, p_button->m_image_index+2);
	else
		gpC_global_resource->m_pC_common_button_spk->BltLocked(p_button->x, p_button->y, p_button->m_image_index);
}

//-----------------------------------------------------------------------------
// WindowEventReceiver
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_CHAR_DELETE::WindowEventReceiver(id_t event)
{
}

//-----------------------------------------------------------------------------
// IsPixel
//
// 
//-----------------------------------------------------------------------------
bool C_VS_UI_CHAR_DELETE::IsPixel(int _x, int _y)
{
	return IsInRect(_x, _y);//m_pC_image_spk->IsPixel(SCR2WIN_X(_x), SCR2WIN_Y(_y));
}

//-----------------------------------------------------------------------------
// Start
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_CHAR_DELETE::Start()
{
	PI_Processor::Start();

	if(g_pUserInformation->IsNetmarble) // && g_pUserInformation->IsNetmarbleLogin)
	{
		m_lev_ssn_part1.EraseAll();
		m_lev_ssn_part1.Acquire();
	}
	else
	{
		m_lev_ssn_part1.EraseAll();
		m_lev_ssn_part1.Acquire();
#if !__CONTENTS(__CHAR_DELETE)
		m_lev_ssn_part2.EraseAll();
#endif	//__CHAR_DELETE
	}

	m_bl_ssn_ip_part1 = true;
	m_selected_slot = 0;

	gpC_window_manager->AppearWindow(this);

	m_pC_button_group->Init();
}

void C_VS_UI_CHAR_DELETE::Finish()
{
	PI_Processor::Finish();

	gpC_window_manager->DisappearWindow(this);
}

//-----------------------------------------------------------------------------
// Process
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_CHAR_DELETE::Process()
{
	m_pC_button_group->Process();
}




WORD	C_VS_UI_CHAR_DELETE::Get_RGB_16(BYTE btRGB_R, BYTE btRGB_G, BYTE btRGB_B)
{
	WORD	wRGB		= 0;

	wRGB	+= (BYTE)(((float)((float)btRGB_R / 255)) * 31);

	wRGB	=  wRGB << 6;	
	wRGB	+= (BYTE)(((float)((float)btRGB_G / 255)) * 63);

	wRGB	=  wRGB << 5;	
	wRGB	+= (BYTE)(((float)((float)btRGB_B / 255)) * 31);

	return wRGB;
}


WORD	C_VS_UI_CHAR_DELETE::Get_RGBAlpha_16(BYTE btRGB_Alpha)
{
	WORD	wRGBAlpha	= 0;

	if(btRGB_Alpha > 100)
		btRGB_Alpha = 10;

	wRGBAlpha	= (BYTE)(((float)((float)btRGB_Alpha / 100)) * 31);

	return wRGBAlpha;
}


void	C_VS_UI_CHAR_DELETE::Init_TitleUIInterface_InfInfo()
{
	char arrstrAppName[255]		= {NULL,};
	char arrstrFileName[255]	= {NULL,};

	GetCurrentDirectory(_MAX_PATH, arrstrFileName);	//ÇöÀç ½ÇÇà ÁßÀÎ ÆÄÀÏÀÇ °æ·Î¸¦ ¾ò´Â´Ù.

	strcpy(arrstrAppName,"RGB_16");

	strcat(arrstrFileName, FILE_INFO_TITLE_UI);

	m_btBox_RGB_R				= (BYTE)GetPrivateProfileInt(arrstrAppName, "BOX_RGB_R", 0, arrstrFileName);
	m_btBox_RGB_G				= (BYTE)GetPrivateProfileInt(arrstrAppName, "BOX_RGB_G", 0, arrstrFileName);
	m_btBox_RGB_B				= (BYTE)GetPrivateProfileInt(arrstrAppName, "BOX_RGB_B", 0, arrstrFileName);
	m_btBox_RGB_Alpha			= (BYTE)GetPrivateProfileInt(arrstrAppName, "BOX_RGB_ALPHA", 0, arrstrFileName);

	m_btLine_RGB_R				= (BYTE)GetPrivateProfileInt(arrstrAppName, "LINE_RGB_R", 0, arrstrFileName);
	m_btLine_RGB_G				= (BYTE)GetPrivateProfileInt(arrstrAppName, "LINE_RGB_G", 0, arrstrFileName);
	m_btLine_RGB_B				= (BYTE)GetPrivateProfileInt(arrstrAppName, "LINE_RGB_B", 0, arrstrFileName);
}





//-----------------------------------------------------------------------------
// Show
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_CHAR_DELETE::Show()
{
//	m_pC_image_spk->Blt(x, y, DELETE_WINDOW);
// 20070702 »Ñ¸®´Â ±×¸² º¯°æ ÈÊ³¯ ÀÌÀüÀ¸·Î µ¹¾Æ°¡¸é ¾Æ·¡ ÁÖ¼® ÇØÁ¦
	//	gpC_global_resource->DrawDialog(x, y, w, h, GetAttributes()->alpha);
	
	RECT mssageBox;
	
	mssageBox.left = x;
	mssageBox.top = y;
	mssageBox.right = x + w;
	mssageBox.bottom = y + h;
	
	Init_TitleUIInterface_InfInfo();

	WORD	wBox_RGB		= Get_RGB_16(m_btBox_RGB_R, m_btBox_RGB_G, m_btBox_RGB_B);
	WORD	wLine_RGB		= Get_RGB_16(m_btLine_RGB_R, m_btLine_RGB_G, m_btLine_RGB_B);
	WORD	wBoxRGB_Alpha	= Get_RGBAlpha_16(m_btBox_RGB_Alpha);

	gpC_base->m_p_DDSurface_back->DrawRect(&mssageBox, wLine_RGB);
	gpC_base->m_p_DDSurface_back->BltColorAlpha(&mssageBox, wBox_RGB, wBoxRGB_Alpha);
	
	g_FL2_GetDC();
	g_PrintColorStr(x+w/2-g_GetStringWidth((*g_pGameStringTable)[UI_STRING_MESSAGE_CHAR_DELETE_CONFIRM].GetString(), gpC_base->m_char_name_pi.hfont)/2, 
		y+30, (*g_pGameStringTable)[UI_STRING_MESSAGE_CHAR_DELETE_CONFIRM].GetString(), gpC_base->m_char_name_pi, RGB_WHITE);
	// ³Ý¸¶ºí¿ë
	if(!(g_pUserInformation->IsNetmarble)) // && g_pUserInformation->IsNetmarbleLogin))
	{
		
#if	__CONTENTS(__CHAR_DELETE)
		g_PrintColorStr(x+20+w/2-g_GetStringWidth((*g_pGameStringTable)[UI_STRING_MESSAGE_RE_INPUT_CORRECT_SSN].GetString(), gpC_base->m_char_name_pi.hfont)/2, 
			y+50,(*g_pGameStringTable)[UI_STRING_MESSAGE_RE_INPUT_CORRECT_DELETE].GetString(), gpC_base->m_char_name_pi, RGB_WHITE);
#else
		g_PrintColorStr(x+w/2-g_GetStringWidth((*g_pGameStringTable)[UI_STRING_MESSAGE_RE_INPUT_CORRECT_SSN].GetString(), gpC_base->m_char_name_pi.hfont)/2, 
			y+50,(*g_pGameStringTable)[UI_STRING_MESSAGE_RE_INPUT_CORRECT_SSN].GetString(), gpC_base->m_char_name_pi, RGB_WHITE);
#endif	//__CHAR_DELETE
	}
	else if((g_pUserInformation->IsNetmarble)) // && g_pUserInformation->IsNetmarbleLogin))
	{
		g_PrintColorStr(x+w/2-g_GetStringWidth((*g_pGameStringTable)[UI_STRING_MESSAGE_RE_INPUT_CORRECT_SSN].GetString(), gpC_base->m_char_name_pi.hfont)/2, 
			y+50,(*g_pGameStringTable)[UI_STRING_MESSAGE_RE_INPUT_CORRECT_DELETE].GetString(), gpC_base->m_char_name_pi, RGB_WHITE);
	}

	m_pC_button_group->ShowDescription();
	g_FL2_ReleaseDC();

 	const int chineseSSNBoxSizeX = 165;

	RECT chineseRect = {m_lev_ssn_part1.GetPosition().x-10, m_lev_ssn_part1.GetPosition().y-4,
		m_lev_ssn_part1.GetPosition().x-10+chineseSSNBoxSizeX,m_lev_ssn_part1.GetPosition().y-4+25};	

	if(g_pUserInformation->IsNetmarble) // && g_pUserInformation->IsNetmarbleLogin)
	{
		gpC_base->m_p_DDSurface_back->FillRect(&chineseRect,0);
	}

	if(gpC_base->m_p_DDSurface_back->Lock())
	{
		// ³Ý¸¶ºí¿ë
		if(!(g_pUserInformation->IsNetmarble)) // && g_pUserInformation->IsNetmarbleLogin))
		{
			{
#if __CONTENTS(__CHAR_DELETE)
				gpC_global_resource->m_pC_assemble_box_button_spk->BltLocked(chineseRect.left, chineseRect.top, C_GLOBAL_RESOURCE::AB_NAME_BAR);
#else
				gpC_global_resource->m_pC_assemble_box_button_spk->BltLocked(m_lev_ssn_part1.GetPosition().x-10, m_lev_ssn_part1.GetPosition().y-2, C_GLOBAL_RESOURCE::AB_NAME_BAR);
				gpC_global_resource->m_pC_assemble_box_button_spk->BltLocked(m_lev_ssn_part2.GetPosition().x-10, m_lev_ssn_part2.GetPosition().y-2, C_GLOBAL_RESOURCE::AB_NAME_BAR);
#endif	//__CHAR_DELETE
			}
		}
		else
		{
			Rect rect(chineseRect.left,chineseRect.top,chineseSSNBoxSizeX,25);
			gpC_global_resource->DrawOutBoxLocked(rect);

		}

		m_pC_button_group->Show();
		gpC_base->m_p_DDSurface_back->Unlock();
	}

	// ³Ý¸¶ºí¿ë
	//if(!( g_pUserInformation->IsNetmarble && g_pUserInformation->IsNetmarbleLogin) )
		Window::ShowWidget();

	SHOW_WINDOW_ATTR;
}

//-----------------------------------------------------------------------------
// Run
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_CHAR_DELETE::Run(id_t id)
{
//	switch (id)
//	{
//		case DELETE_OK:
//			// ³Ý¸¶ºí¿ë
//			{
//				// Á¦´ë·Î ÀÔ·ÂÇÏ¿´´Â°¡?
//				if (true
//#if __CONTENTS(__CHAR_DELETE)
//					// ¼­¹ö¿¡¼­ Á¦¾î ÇÑµ¥¿ä.
//					&&	(m_lev_ssn_part1.Size() == SSN_PART1_CHAR_COUNT)
//					&& ( wcscmp( m_lev_ssn_part1.GetString(), _L("delete")) == 0 )
//#else
//					&& ( ( gC_ci->IsKorean()&& (	m_lev_ssn_part1.Size() == SSN_PART1_CHAR_COUNT &&
//					 m_lev_ssn_part2.Size() == SSN_PART2_CHAR_COUNT ) ) 
//					 || ( !gC_ci->IsKorean() && ( wcscmp( m_lev_ssn_part1.GetString(), _L("yes")) == 0 ) )
//					 )
//#endif	//__CHAR_DELETE
//					 )
//					 //|| (g_pUserInformation->IsNetmarble && g_pUserInformation->IsNetmarbleLogin))
//				{
//					SendCharacterDeleteToClient();
//				}
//				else if(
//						//((g_pUserInformation->IsNetmarble && g_pUserInformation->IsNetmarbleLogin) && (	m_lev_ssn_part1.Size() == SSN_PART1_CHAR_COUNT) && 
//						((g_pUserInformation->IsNetmarble) && (	m_lev_ssn_part1.Size() == SSN_PART1_CHAR_COUNT) 
//						&& ( wcscmp( m_lev_ssn_part1.GetString(), _L("delete")) == 0 )
//						)) 
//				{
//					SendCharacterDeleteToClient();
//				}
//				else 
//				{
//					// error message!
//					if(!(g_pUserInformation->IsNetmarble)) // && g_pUserInformation->IsNetmarbleLogin))
//						g_msg_wrong_ssn->Start();
//					else
//						g_msg_wrong_delete->Start() ;  
//				}
//			}
//			break;
//
//		case DELETE_CANCEL:
//			Finish();
//			break;
//	}
}

//-----------------------------------------------------------------------------
// MouseControl
//
// 
//-----------------------------------------------------------------------------
bool C_VS_UI_CHAR_DELETE::MouseControl(UINT message, int _x, int _y)
{
	Window::MouseControl(message, _x, _y);
	m_pC_button_group->MouseControl(message, _x, _y);

	return true;
}

//-----------------------------------------------------------------------------
// KeyboardControl
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_CHAR_DELETE::KeyboardControl(UINT message, UINT key, long extra)
{
	if (message == WM_KEYDOWN)
		switch (key)
		{
			case VK_ESCAPE:
				Run(DELETE_CANCEL);
				return;

			case VK_RETURN:
				Run(DELETE_OK);
				return;
		}
	
	// digit only
	if(!(g_pUserInformation->IsNetmarble && g_pUserInformation->IsNetmarbleLogin))
	{
#if __CONTENTS(__CHAR_DELETE)
		Window::KeyboardControl(message, key, extra);
#else
		if (message == WM_CHAR && (!gC_ci->IsKorean() || gC_ci->IsKorean() && (key >= '0' && key <= '9')))
		{
			Window::KeyboardControl(message, key, extra);

			if( gC_ci->IsKorean() )
			{
				if (m_bl_ssn_ip_part1)
				{
					if (m_lev_ssn_part1.Size() == SSN_PART1_CHAR_COUNT)
					{
						m_bl_ssn_ip_part1 = false;
						m_lev_ssn_part2.Acquire();
					}
				}
			}
		}
#endif
	}
	else if(message == WM_CHAR && (g_pUserInformation->IsNetmarble && g_pUserInformation->IsNetmarbleLogin))
	{
		Window::KeyboardControl(message, key, extra);
	}	

	if (message == WM_KEYDOWN)
		if (key == VK_BACK)
		{
			if( gC_ci->IsKorean() )
			{
				if (!m_bl_ssn_ip_part1)
				{
					if (m_lev_ssn_part2.Size() == 0)
					{
						m_bl_ssn_ip_part1 = true;
						m_lev_ssn_part1.Acquire();
					}
				}
			}

			Window::KeyboardControl(message, key, extra);
		}
}




//-----------------------------------------------------------------------------
// RollDice
//
// ÁÖ»çÀ§¸¦ ´øÁ®¼­ point¸¦ Á¤ÇÑ´Ù.
//-----------------------------------------------------------------------------
void C_VS_UI_NEWCHAR::RollDice(bool load)
{
	switch(m_p_slot->Race)
	{
	case RACE_SLAYER:
		if(load == false)
		{
			switch(m_selected_job)
			{
			case 0:
			case 1:
				m_p_slot->STR_PURE = 20;
				m_p_slot->DEX_PURE = 5;
				m_p_slot->INT_PURE = 5;
				break;
			case 2:
				m_p_slot->STR_PURE = 5;
				m_p_slot->DEX_PURE = 20;
				m_p_slot->INT_PURE = 5;
				break;
			case 3:
			case 4:
				m_p_slot->STR_PURE = 5;
				m_p_slot->DEX_PURE = 5;
				m_p_slot->INT_PURE = 20;
				break;
			}
			
		}
		break;

	case RACE_VAMPIRE:
		{
			m_p_slot->STR_PURE = 20;
			m_p_slot->DEX_PURE = 20;
			m_p_slot->INT_PURE = 20;
		}
		break;
		
	case RACE_OUSTERS:
		{
			m_p_slot->STR_PURE = 10;
			m_p_slot->DEX_PURE = 10;
			m_p_slot->INT_PURE = 10;
			m_p_slot->bonus_point = 15;
		}
		break;
	}

	m_p_slot->DAM			= 1;
	m_p_slot->DAM2			= max(1, m_p_slot->STR_PURE/10);
	m_p_slot->DEFENSE		= m_p_slot->DEX_PURE;
	m_p_slot->PROTECTION	= m_p_slot->STR_PURE/15;
	m_p_slot->TOHIT			= m_p_slot->DEX_PURE;

	m_p_slot->HP = m_p_slot->STR_PURE*2;
	m_p_slot->MP = m_p_slot->INT_PURE*2;

	m_p_slot->HP_MAX = 20*2; // ÀÌ°É ... const int·Î ÇÏ´Ï±î SetEnergy()¿¡¼­ ÀÌ °ªÀÌ º¯Çß´Ù!
	m_p_slot->MP_MAX = 20*2;
}

//-----------------------------------------------------------------------------
// SendNewCharacterToClient
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_NEWCHAR::SendNewCharacterToClient()
{
	//
	// !¿ÜºÎ¿¡ sz_nameÀ» deleteÇÏ¸é ¾ÈµÈ´Ù.
	//
	static NEW_CHARACTER S_new_character; // ¹Ýµå½Ã staticÀ¸·Î..

//	DeleteNew(m_p_slot->sz_name);

	char *sz_temp;
	g_Convert_DBCS_Ascii2SingleByte(m_lev_name.GetString(), m_lev_name.Size(), sz_temp);

	m_p_slot->sz_name = sz_temp;
	DeleteNew(sz_temp);

	S_new_character.sz_name		= (char *)m_p_slot->sz_name.c_str();
	S_new_character.race		= m_p_slot->Race;
	S_new_character.bl_female	= m_p_slot->bl_female;
	S_new_character.STR			= m_p_slot->STR_PURE;
	S_new_character.DEX			= m_p_slot->DEX_PURE;
	S_new_character.INT			= m_p_slot->INT_PURE;
	S_new_character.slot		= m_selected_slot;
	S_new_character.skin_color = m_p_slot->skin_color;
	S_new_character.hair_color = m_p_slot->hair_color;
	S_new_character.coat_color = m_p_slot->coat_color;;
	S_new_character.trouser_color = m_p_slot->trouser_color;
	S_new_character.face	= m_p_slot->man_info.hair-M_HAIR1;
	S_new_character.race		= m_p_slot->Race;
	S_new_character.job			= m_selected_job;

	gpC_base->SendMessage(UI_NEW_CHARACTER, 0, 0, &S_new_character);
}

//-----------------------------------------------------------------------------
// _Timer_CharUpdate
//
// 
//-----------------------------------------------------------------------------
void _Timer_CharUpdate() // globals
{
		g_char_index++;
}

//-----------------------------------------------------------------------------
// Start
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_NEWCHAR::Start()
{
	PI_Processor::Start();
	g_pTopView->DeleteTitleEffect();

	m_bl_pushed_table = false;
	m_p_slot				= NULL;
	m_selected_slot	= 0;

	gpC_window_manager->AppearWindow(this);
	m_pC_button_group->Init();

	LoadDesc("create_window.txt", 30, 14, false);

	m_lev_name.Acquire();
	m_lev_name.EraseAll();

	//POINT	ptEffect;
	//ptEffect.x	= 	m_wEffect_Fire_Left1_X;
	//ptEffect.y	=	m_wEffect_Fire_Left1_Y;
	//g_pTopView->AddTitleEffect(&ptEffect, EFFECTSPRITETYPE_CHAR_MANAGER_LEFT_FIRE_1, 2, EFFECT_INDEX_FIRE_LEFT1);

	//ptEffect.x	= 	m_wEffect_Fire_Left2_X;
	//ptEffect.y	=	m_wEffect_Fire_Left2_Y;
	//g_pTopView->AddTitleEffect(&ptEffect, EFFECTSPRITETYPE_CHAR_MANAGER_LEFT_FIRE_2, 2, EFFECT_INDEX_FIRE_LEFT2);

	//ptEffect.x	= 	m_wEffect_Fire_Right1_X;
	//ptEffect.y	=	m_wEffect_Fire_Right1_Y;
	//g_pTopView->AddTitleEffect(&ptEffect, EFFECTSPRITETYPE_CHAR_MANAGER_RIGHT_FIRE_1, 2, EFFECT_INDEX_FIRE_RIGHT1);

	//ptEffect.x	= 	m_wEffect_Fire_Right2_X;
	//ptEffect.y	=	m_wEffect_Fire_Right2_Y;
	//g_pTopView->AddTitleEffect(&ptEffect, EFFECTSPRITETYPE_CHAR_MANAGER_RIGHT_FIRE_2, 2, EFFECT_INDEX_FIRE_RIGHT2);

	//ptEffect.x	= 	m_wEffect_Fire_Center_X;
	//ptEffect.y	=	m_wEffect_Fire_Center_Y;
	//g_pTopView->AddTitleEffect(&ptEffect, EFFECTSPRITETYPE_CHAR_MANAGER_CENTER_FIRE, 2, EFFECT_INDEX_FIRE_CENTER);
}

void C_VS_UI_NEWCHAR::Finish()
{
	//m_pC_char_appearance->Finish();

	PI_Processor::Finish();

	gpC_window_manager->DisappearWindow(this);

//	m_pC_ani_fin->Stop();
}

//-----------------------------------------------------------------------------
// Process
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_NEWCHAR::Process()
{
	m_pC_button_group->Process();
}

//-----------------------------------------------------------------------------
// C_VS_UI_NEWCHAR
//
// 
//-----------------------------------------------------------------------------
C_VS_UI_NEWCHAR::C_VS_UI_NEWCHAR()
{
	g_RegisterWindow(this);

	AttrKeyboardControl(true);

	bool bHighResolution = g_pUserInformation->iResolution_x > 800;
	
/*	if(g_pUserInformation->IsResolution1024)
	{
		m_common_spk.Open(SPK_COMMON);
//		m_title_spk.Open(SPK_TITLE_1024);
		m_image_spk.Open(SPK_CHAR_CREATE);
	}
	else
	{
		m_image_spk.Open(SPK_CHAR_CREATE800);
		m_common_spk.Open(SPK_COMMON);
	}  */
//	m_face_spk.Open(SPK_FACE_MAKE);

	//m_image_hays_spk.Open("data\\ui\\spk\\new\\charcreaterenewal\\00000.spk");
	//m_image_hays_spk1.Open("data\\ui\\spk\\new\\charcreaterenewal\\00016.spk");

	m_image_hays_spk.Open(SPK_CHAR_CREATE_NEW);
	m_image_spk.Open(SPK_CHAR_CREATE);
	m_common_spk.Open(SPK_COMMON);

	m_iCurBackPicID = BK_800_600;
	
#if	__CONTENTS(__USER_GRADE)
	m_pC_use_grade = new C_SPRITE_PACK(SPK_USE_GRADE);
#endif	//__USER_GRADE

//	Set(0, 0, g_pUserInformation->iResolution_x, g_pUserInformation->iResolution_y );

	m_pAnimationTimer = new CTickTimer;
	m_pAnimationTimer->StartTimer(50, true);
	m_aniArpha = 31;
	m_bAniArphaUp = false;

	m_show_skin = false;
	m_selected_job = 0;

	// set button
	m_pC_button_group = new ButtonGroup(this);

	const InterfaceInformation *pSkin = &g_pSkinManager->Get( SkinManager::NEW_CHAR );
	
	int convx = (g_pUserInformation->iResolution_x - 800) / 2;
	int convy = (g_pUserInformation->iResolution_y - 600) / 2;

	int skinnum = 0;

	m_chDirection	= 2;

	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_wPrevButton_X, m_wPrevButton_Y,	
													m_image_hays_spk.GetWidth(BTN_RED_NORMAL), m_image_hays_spk.GetHeight(BTN_RED_NORMAL), 
													BACK_ID, this, BTN_RED_NORMAL));

	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_wNextButton_X, m_wNextButton_Y,	
													m_image_hays_spk.GetWidth(BTN_GREEN_NORMAL), m_image_hays_spk.GetHeight(BTN_GREEN_NORMAL), 
													NEXT_ID, this, BTN_GREEN_NORMAL));


	
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_wCharLeftRotation_Button_X, m_wCharLeftRotation_Button_Y,	
													m_image_spk.GetWidth(CHAR_LEFT_RATOATION_BUTTON), m_image_spk.GetHeight(CHAR_LEFT_RATOATION_BUTTON), 
													CHAR_LEFT_LOTATION_ID, this, CHAR_LEFT_RATOATION_BUTTON));

	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_wCharRightRotation_Button_X, m_wCharRightRotation_Button_Y,	
													m_image_spk.GetWidth(CHAR_RIGHT_RATOATION_BUTTON), m_image_spk.GetHeight(CHAR_RIGHT_RATOATION_BUTTON), 
													CHAR_RIGHT_LOTATION_ID, this, CHAR_RIGHT_RATOATION_BUTTON));
	


	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_wSelect_Race_Slayer_Button_X, m_wSelect_Race_Slayer_Button_Y,	
													m_image_hays_spk.GetWidth(BUTTON_SLAYER_NORMAL), m_image_hays_spk.GetHeight(BUTTON_SLAYER_NORMAL), 
													SLAYER_ID, this, BUTTON_SLAYER_NORMAL));

	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_wSelect_Race_Vampire_Button_X, m_wSelect_Race_Vampire_Button_Y,	
													m_image_hays_spk.GetWidth(BUTTON_VAMPIRE_NORMAL), m_image_hays_spk.GetHeight(BUTTON_VAMPIRE_NORMAL), 
													VAMPIRE_ID, this, BUTTON_VAMPIRE_NORMAL));

	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_wSelect_Race_Ousters_Button_X, m_wSelect_Race_Ousters_Button_Y,	
													m_image_hays_spk.GetWidth(BUTTON_OUTER_NORMAL), m_image_hays_spk.GetHeight(BUTTON_OUTER_NORMAL), 
													OUSTERS_ID, this, BUTTON_OUTER_NORMAL));


	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_wNameCheck_Button_X, m_wNameCheck_Button_Y,	
													m_image_hays_spk.GetWidth(BUTTON_BLUE_NORMAL), m_image_hays_spk.GetHeight(BUTTON_BLUE_NORMAL), 
													CHECK_ID, this, BUTTON_BLUE_NORMAL));

	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_wNewCharBox_X+16, m_wNameCheck_Button_Y+145,	
													m_image_hays_spk.GetWidth(BTN_YELLOW_NORMAL), m_image_hays_spk.GetHeight(BTN_YELLOW_NORMAL), 
													SELECT_SKIN, this, BTN_YELLOW_NORMAL));

//#if __CONTENTS(__RACE_OUSTERS)
////	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(pSkin->GetPoint( skinnum ).x+convx,convy+pSkin->GetPoint( skinnum ).y,m_image_spk.GetWidth(OUSTERS_BUTTON)+20, m_image_spk.GetHeight(OUSTERS_BUTTON), OUSTERS_ID, this, OUSTERS_BUTTON));skinnum++;
//#else
//	skinnum++;
// #endif

	// LineEditorVisual setting...
	m_lev_name.SetPrintInfo(gpC_base->m_user_id_pi);
	m_lev_name.SetInputStringColor(RGB_WHITE);
	m_lev_name.SetPosition(m_wNewCharBox_X + 20,m_wNewCharBox_Y + 30);
	m_lev_name.SetByteLimit(11);//by viva
	Attach(&m_lev_name);

	m_slayer_man_ispk.LoadFromFileRunning(ISPK_SLAYER_MAN);
	m_slayer_woman_ispk.LoadFromFileRunning(ISPK_SLAYER_WOMAN);

	m_vampire_ispk.LoadFromFileRunning(ISPK_VAMPIRE);
	m_ousters_ispk.LoadFromFileRunning(ISPK_OUSTERS);

	//m_AdvancementSlayerIspk.LoadFromFileRunning( ISPK_ADVANCEMENT_SLAYER );
	m_AdvancementVampireManIspk.LoadFromFileRunning( ISPK_ADVANCEMENT_VAMPIRE_MAN );
	m_AdvancementVampireWomanIspk.LoadFromFileRunning( ISPK_ADVANCEMENT_VAMPIRE_WOMAN );
	m_AdvancementOustersIspk.LoadFromFileRunning( ISPK_ADVANCEMENT_OUSTERS );
	m_AdvancementSlayerManIspk.LoadFromFileRunning( ISPK_ADVANCEMENT_SLAYER_MAN );
	m_AdvancementSlayerWomanIspk.LoadFromFileRunning( ISPK_ADVANCEMENT_SLAYER_WOMAN );

	//if(access(CFPK_SLAYER, 0))	_Error(FILE_OPEN);
 	ivfstream file_man(CFPK_SLAYER_MAN, std::ios::binary);
	if(!file_man.is_open()) _Error(FILE_OPEN);
 	m_slayer_man_cfpk.LoadFromFile(file_man);
 	file_man.close();

	//if(access(CFPK_SLAYER, 0))	_Error(FILE_OPEN);
 	ivfstream file_woman(CFPK_SLAYER_WOMAN, std::ios::binary);
	if(!file_woman.is_open()) _Error(FILE_OPEN);
 	m_slayer_woman_cfpk.LoadFromFile(file_woman);
 	file_woman.close();

	//if(access(CFPK_VAMPIRE, 0))	_Error(FILE_OPEN);
	ivfstream file_vampire(CFPK_VAMPIRE, std::ios::binary);
	if(!file_vampire.is_open()) _Error(FILE_OPEN);
	m_vampire_cfpk.LoadFromFile(file_vampire);
	file_vampire.close();

	//if(access(CFPK_OUSTERS, 0))	_Error(FILE_OPEN);
	ivfstream file_ousters(CFPK_OUSTERS, std::ios::binary);
	if(!file_ousters.is_open()) _Error(FILE_OPEN);
	m_ousters_cfpk.LoadFromFile(file_ousters);
	file_ousters.close();
	
	//if(access(CFPK_ADVANCEMENT_OUSTERS, 0))	_Error(FILE_OPEN);
	ivfstream file_ac_ousters( CFPK_ADVANCEMENT_OUSTERS, std::ios::binary);
	if(!file_ac_ousters.is_open()) _Error(FILE_OPEN);
	m_AdvancementOustersCfpk.LoadFromFile( file_ac_ousters );
	file_ac_ousters.close();

	//if(access(CFPK_ADVANCEMENT_VAMPIRE_MAN, 0))	_Error(FILE_OPEN);
	ivfstream file_ac_vampire( CFPK_ADVANCEMENT_VAMPIRE_MAN, std::ios::binary);
	if(!file_ac_vampire.is_open()) _Error(FILE_OPEN);
	m_AdvancementVampireManCfpk.LoadFromFile( file_ac_vampire );
	file_ac_vampire.close();

	//if(access(CFPK_ADVANCEMENT_VAMPIRE_WOMAN, 0))	_Error(FILE_OPEN);
	ivfstream file_ac_vampire2( CFPK_ADVANCEMENT_VAMPIRE_WOMAN, std::ios::binary);
	if(!file_ac_vampire2.is_open()) _Error(FILE_OPEN);
	m_AdvancementVampireWomanCfpk.LoadFromFile( file_ac_vampire2 );
	file_ac_vampire2.close();

	//if(access(CFPK_ADVANCEMENT_SLAYER_MAN, 0))	_Error(FILE_OPEN);
	ivfstream file_ac_slayerman( CFPK_ADVANCEMENT_SLAYER_MAN, std::ios::binary);
	if(!file_ac_slayerman.is_open()) _Error(FILE_OPEN);
	m_AdvancementSlayerManCfpk.LoadFromFile( file_ac_slayerman );
	file_ac_slayerman.close();

	//if(access(CFPK_ADVANCEMENT_SLAYER_WOMAN, 0))	;
	ivfstream file_ac_slayerwoman( CFPK_ADVANCEMENT_SLAYER_WOMAN, std::ios::binary);
	if(!file_ac_slayerwoman.is_open()) _Error(FILE_OPEN);
	m_AdvancementSlayerWomanCfpk.LoadFromFile( file_ac_slayerwoman );
	file_ac_slayerwoman.close();

	srand((unsigned)time(NULL));

	m_iSave[0] = -1;
	m_focused_help = HELP_DEFAULT;

	m_pack_file.SetRAR(RPK_TITLE, RPK_PASSWORD);

	SetDesc(29, 160, RGB(160, 160, 160), gpC_base->m_chatting_pi);
//#endif	
	m_desc_y_distance = 16;

	m_wMale_OR_Femail_Select_Radio_Alpha	= 0;
	m_wFace_Alpha							= 0;
	m_btSelect_Face							= 0;
	m_btVirtureSelect_Face					= 0;

	m_wSave_Button_Alpha					= 0;				//
	m_wLoad_Button_Alpha					= 0;				//
	m_wReset_Button_Alpha					= 0;				//

	for(int i = 0; i < STET_MAX; i++)
	{
		m_wStet_Plus_Button_Alpha[i]	= 0;
		m_wStet_Minus_Button_Alpha[i]	= 0;
	}
	Init_TitleUIInterface_InfInfo();
}

//-----------------------------------------------------------------------------
// ~C_VS_UI_NEWCHAR
//
// 
//-----------------------------------------------------------------------------
C_VS_UI_NEWCHAR::~C_VS_UI_NEWCHAR()
{
	g_UnregisterWindow(this);
#if __CONTENTS(__USER_GRADE)
	DeleteNew(m_pC_use_grade);
#endif //__USER_GRADE
	DeleteNew(m_pC_button_group);
	DeleteNew(m_pAnimationTimer);
}

void C_VS_UI_NEWCHAR::UnacquireMouseFocus()
{
	m_pC_button_group->UnacquireMouseFocus();
}

//-----------------------------------------------------------------------------
// ChangeColor
//
// (x, y) À§Ä¡ÀÇ color table color·Î color¸¦ changeÇÑ´Ù.
// ¹Ù²åÀ¸¸é true¸¦ ¹ÝÈ¯ÇÑ´Ù.
//-----------------------------------------------------------------------------
bool C_VS_UI_NEWCHAR::ChangeColor(int _x, int _y)
{
	for (int j=0; j < COLOR_LIST_Y; j++)
	{
		for (int i=0; i < COLOR_LIST_X; i++)
		{
			if(m_p_slot->Race != RACE_OUSTERS)
			{
				if (_x >= m_wSkinColor_Start_X && _x < m_wSkinColor_Start_X + (i * COLOR_UNIT_X) + COLOR_UNIT_X&&
					_y >= m_wSkinColor_Start_Y && _y < m_wSkinColor_Start_Y + (j * COLOR_UNIT_Y) + COLOR_UNIT_Y)
				{
					m_skin_point.Set(i, j);
					m_p_slot->skin_color = m_skin_color_array[i][j];
					return true;
				}
			}
			if(m_p_slot->Race != RACE_VAMPIRE)
			{
				if (_x >= m_wHairColor_Start_X && _x < m_wHairColor_Start_X + (i * COLOR_UNIT_X) + COLOR_UNIT_X &&
					_y >= m_wHairColor_Start_Y && _y < m_wHairColor_Start_Y + (j * COLOR_UNIT_Y) + COLOR_UNIT_Y)
				{
					m_hair_point.Set(i, j);
					m_p_slot->hair_color = m_hair_color_array[i][j];
					return true;
				}
			}
		}
	}
	return false;
}



void	C_VS_UI_NEWCHAR::Init_TitleUIInterface_InfInfo()
{
	char arrstrAppName[255]		= {NULL,};
	char arrstrFileName[255]	= {NULL,};

	GetCurrentDirectory(_MAX_PATH, arrstrFileName);	//ÇöÀç ½ÇÇà ÁßÀÎ ÆÄÀÏÀÇ °æ·Î¸¦ ¾ò´Â´Ù.

	bool bHighResolution = g_pUserInformation->iResolution_x > 800;
	int ConvX = 0;	int ConvY = 0;
	
	if(bHighResolution)	// 1024*768, 1280*960, 1280*1024
	{
		if(g_pUserInformation->iResolution_x <=1024)
			strcpy(arrstrAppName,"CREATE_CHAR_1024_768");
		else
		{
			// 1280*720
			if(g_pUserInformation->iResolution_y < 960)
			{	
				strcpy(arrstrAppName,"CREATE_CHAR_1280_720");

// 				ConvX = (g_pUserInformation->iResolution_x - m_image_spk.GetWidth(WINDOW_1024_768)) / 2;	//128
// 				ConvY = (g_pUserInformation->iResolution_y - m_image_spk.GetHeight(WINDOW_1024_768)) / 2;	//-24
			}
			// 1280*960
			else if(g_pUserInformation->iResolution_y < 1024)
			{	
				strcpy(arrstrAppName,"CREATE_CHAR_1280_960");

// 				ConvX = (g_pUserInformation->iResolution_x - m_image_spk.GetWidth(WINDOW_1024_768)) / 2;	//128
// 				ConvY = (g_pUserInformation->iResolution_y - m_image_spk.GetHeight(WINDOW_1024_768)) / 2;	//96
			}
			// 1280*1024
			else
			{	
				strcpy(arrstrAppName,"CREATE_CHAR_1280_1024");

// 				ConvX = (g_pUserInformation->iResolution_x - m_image_spk.GetWidth(WINDOW_1024_768)) / 2;	//128
// 				ConvY = (g_pUserInformation->iResolution_y - m_image_spk.GetHeight(WINDOW_1024_768)) / 2;	//128
			}
		}
	}
	else
		strcpy(arrstrAppName,"CREATE_CHAR_800_600");

	if(g_pUserInformation->IsNetmarbleLogin)
	{
		if(bHighResolution)
			strcpy(arrstrAppName,"NET_CREATE_CHAR_1024_768");
		else
			strcpy(arrstrAppName,"NET_CREATE_CHAR_800_600");
	}

	strcat(arrstrFileName, FILE_INFO_TITLE_UI);

	m_wNewCharBox_X							= (WORD)GetPrivateProfileInt(arrstrAppName, "NEWCHAR_BOX_X", 0, arrstrFileName);
	m_wNewCharBox_Y							= (WORD)GetPrivateProfileInt(arrstrAppName, "NEWCHAR_BOX_Y", 0, arrstrFileName);

	m_wNameCheck_Button_X					= m_wNewCharBox_X + 181;
	m_wNameCheck_Button_Y					= m_wNewCharBox_Y + 25;

	m_wCharNameFocus_X						= m_wNewCharBox_X + 20;
	m_wCharNameFocus_Y						= m_wNewCharBox_Y + 30;

	m_wCharLeftRotation_Button_X			= m_wNewCharBox_X + 21;
	m_wCharLeftRotation_Button_Y			= m_wNewCharBox_Y + 101;

	m_wCharRightRotation_Button_X			= m_wNewCharBox_X + 95;
	m_wCharRightRotation_Button_Y			= m_wNewCharBox_Y + 101;

	m_wCharView_X							= m_wNewCharBox_X + 42;
	m_wCharView_Y							= m_wNewCharBox_Y + 130;

	m_ptFace_Radio[SELECT_LEFT_FACE].x		= m_wNewCharBox_X + 16;
	m_ptFace_Radio[SELECT_LEFT_FACE].y		= m_wNewCharBox_Y + 257-80;

	m_ptFace_Radio[SELECT_CENTER_FACE].x	= m_ptFace_Radio[SELECT_LEFT_FACE].x + 37;
	m_ptFace_Radio[SELECT_CENTER_FACE].y	= m_ptFace_Radio[SELECT_LEFT_FACE].y;

	m_ptFace_Radio[SELECT_RIGHT_FACE].x		= m_ptFace_Radio[SELECT_CENTER_FACE].x + 37;
	m_ptFace_Radio[SELECT_RIGHT_FACE].y		= m_ptFace_Radio[SELECT_CENTER_FACE].y;

	m_ptFace[SELECT_LEFT_FACE].x			= m_wNewCharBox_X+7;
	m_ptFace[SELECT_LEFT_FACE].y			= m_wNewCharBox_Y + 257-80;

	m_ptFace[SELECT_CENTER_FACE].x			= m_ptFace[SELECT_LEFT_FACE].x + 36;
	m_ptFace[SELECT_CENTER_FACE].y			= m_ptFace[SELECT_LEFT_FACE].y;

	m_ptFace[SELECT_RIGHT_FACE].x			= m_ptFace[SELECT_CENTER_FACE].x + 36;
	m_ptFace[SELECT_RIGHT_FACE].y			= m_ptFace[SELECT_CENTER_FACE].y;

	m_ptRaceSelect_Radio[RACE_SLAYER].x		= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_RACE_RRADIO_SLAYER_X", 0, arrstrFileName) + m_wNewCharBox_X;
	m_ptRaceSelect_Radio[RACE_SLAYER].y		= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_RACE_RRADIO_SLAYER_Y", 0, arrstrFileName) + m_wNewCharBox_Y;

	m_ptRaceSelect_Radio[RACE_VAMPIRE].x	= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_RACE_RRADIO_VAMPIRE_X", 0, arrstrFileName) + m_wNewCharBox_X;
	m_ptRaceSelect_Radio[RACE_VAMPIRE].y	= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_RACE_RRADIO_VAMPIRE_Y", 0, arrstrFileName) + m_wNewCharBox_Y;

	m_ptRaceSelect_Radio[RACE_OUSTERS].x	= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_RACE_RRADIO_OUSTERS_X", 0, arrstrFileName) + m_wNewCharBox_X;
	m_ptRaceSelect_Radio[RACE_OUSTERS].y	= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_RACE_RRADIO_OUSTERS_Y", 0, arrstrFileName) + m_wNewCharBox_Y;

	m_wHide_Ousters_Selection_Button_X		= (WORD)GetPrivateProfileInt(arrstrAppName, "HIDE_OUSTERS_SELECTION_BUTTON_X", 0, arrstrFileName)	+ m_wNewCharBox_X;
	m_wHide_Ousters_Selection_Button_Y		= (WORD)GetPrivateProfileInt(arrstrAppName, "HIDE_OUSTERS_SELECTION_BUTTON_Y", 0, arrstrFileName)	+ m_wNewCharBox_Y;
	m_wSelect_Race_Slayer_Button_X			= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_RACE_SLAYER_BUTTON_X", 0, arrstrFileName);
	m_wSelect_Race_Slayer_Button_Y			= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_RACE_SLAYER_BUTTON_Y", 0, arrstrFileName);

	m_wSelect_Race_Vampire_Button_X			= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_RACE_VAMPIRE_BUTTON_X", 0, arrstrFileName);
	m_wSelect_Race_Vampire_Button_Y			= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_RACE_VAMPIRE_BUTTON_Y", 0, arrstrFileName);

	m_wSelect_Race_Ousters_Button_X			= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_RACE_OUSTERS_BUTTON_X", 0, arrstrFileName);
	m_wSelect_Race_Ousters_Button_Y			= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_RACE_OUSTERS_BUTTON_Y", 0, arrstrFileName);

	m_wMale_OR_Female_Select_Box_X			= m_wNewCharBox_X + 16;
	m_wMale_OR_Female_Select_Box_Y			= m_wNewCharBox_Y + 175+66-40;

	//m_wMale_Select_Radio_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "MALE_SELECT_RADIO_X", 0, arrstrFileName)	+ m_wMale_OR_Female_Select_Box_X;
	//m_wMale_Select_Radio_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "MALE_SELECT_RADIO_Y", 0, arrstrFileName)	+ m_wMale_OR_Female_Select_Box_Y;
	m_wMale_Select_Radio_X			= m_wNewCharBox_X + 16+30;
	m_wMale_Select_Radio_Y			= m_wNewCharBox_Y + 175+66-40+6;

	m_wMale_Select_Button_X			= m_wNewCharBox_X + 16+30;
	m_wMale_Select_Button_Y			= m_wNewCharBox_Y + 175+66-40+6;

	//m_wFemale_Select_Radio_X				= (WORD)GetPrivateProfileInt(arrstrAppName, "FEMALE_SELECT_RADIO_X", 0, arrstrFileName)	+ m_wMale_OR_Female_Select_Box_X;
	//m_wFemale_Select_Radio_Y				= (WORD)GetPrivateProfileInt(arrstrAppName, "FEMALE_SELECT_RADIO_Y", 0, arrstrFileName)	+ m_wMale_OR_Female_Select_Box_Y;

	m_wFemale_Select_Radio_X			= m_wNewCharBox_X + 16+65;
	m_wFemale_Select_Radio_Y			= m_wNewCharBox_Y + 175+66-40+6;

	m_wFemale_Select_Button_X			= m_wNewCharBox_X + 16+65;
	m_wFemale_Select_Button_Y			= m_wNewCharBox_Y + 175+66-40+6;

	//m_wMale_Select_Button_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "MALE_SELECT_BUTTON_X", 0, arrstrFileName)	+ m_wMale_OR_Female_Select_Box_X;
	//m_wMale_Select_Button_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "MALE_SELECT_BUTTON_Y", 0, arrstrFileName)	+ m_wMale_OR_Female_Select_Box_Y;


	//m_wFemale_Select_Button_X				= (WORD)GetPrivateProfileInt(arrstrAppName, "FEMALE_SELECT_BUTTON_X", 0, arrstrFileName) + m_wMale_OR_Female_Select_Box_X;
	//m_wFemale_Select_Button_Y				= (WORD)GetPrivateProfileInt(arrstrAppName, "FEMALE_SELECT_BUTTON_Y", 0, arrstrFileName) + m_wMale_OR_Female_Select_Box_Y;


	m_wHairColor_BOX_X						= m_wNewCharBox_X + 276;
	m_wHairColor_BOX_Y						= m_wNewCharBox_Y + 22;

	m_wHairColor_Start_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "HAIR_COLOR_START_X", 0, arrstrFileName)	+ m_wHairColor_BOX_X;
	m_wHairColor_Start_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "HAIR_COLOR_START_Y", 0, arrstrFileName)	+ m_wHairColor_BOX_Y;

	m_wSkinColor_BOX_X						= m_wNewCharBox_X + 276;
	m_wSkinColor_BOX_Y						= m_wNewCharBox_Y + 22+46+26;

	m_wSkinColor_Start_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "SKIN_COLOR_START_X", 0, arrstrFileName)	+ m_wSkinColor_BOX_X;
	m_wSkinColor_Start_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "SKIN_COLOR_START_Y", 0, arrstrFileName)	+ m_wSkinColor_BOX_Y;

	m_wOpset_BOX_X							= m_wNewCharBox_X + 16+50;
	m_wOpset_BOX_Y							= m_wNewCharBox_Y + 235+23;

	m_wSave_Button_X						= (WORD)GetPrivateProfileInt(arrstrAppName, "SAVE_BUTTON_X", 0, arrstrFileName)	+ m_wOpset_BOX_X;
	m_wSave_Button_Y						= (WORD)GetPrivateProfileInt(arrstrAppName, "SAVE_BUTTON_Y", 0, arrstrFileName)	+ m_wOpset_BOX_Y;

	m_wLoad_Button_X						= (WORD)GetPrivateProfileInt(arrstrAppName, "LOAD_BUTTON_X", 0, arrstrFileName)	+ m_wOpset_BOX_X;
	m_wLoad_Button_Y						= (WORD)GetPrivateProfileInt(arrstrAppName, "LOAD_BUTTON_Y", 0, arrstrFileName)	+ m_wOpset_BOX_Y;

	m_wReset_Button_X						= (WORD)GetPrivateProfileInt(arrstrAppName, "RESET_BUTTON_X", 0, arrstrFileName)	+ m_wOpset_BOX_X;
	m_wReset_Button_Y						= (WORD)GetPrivateProfileInt(arrstrAppName, "RESET_BUTTON_Y", 0, arrstrFileName)	+ m_wOpset_BOX_Y;

	m_wSTR_Text_X							= m_wNewCharBox_X + 210;
	m_wSTR_Text_Y							= m_wNewCharBox_Y + 55;

	m_wDEX_Text_X							= m_wSTR_Text_X;
	m_wDEX_Text_Y							= m_wNewCharBox_Y + 75;

	m_wINT_Text_X							= m_wSTR_Text_X;
	m_wINT_Text_Y							= m_wNewCharBox_Y + 92;

	m_wHP_Text_X							= m_wSTR_Text_X;
	m_wHP_Text_Y							= m_wNewCharBox_Y + 112;

	m_wMP_Text_X							= m_wSTR_Text_X;
	m_wMP_Text_Y							= m_wNewCharBox_Y + 131;

	m_wDEFENSE_Text_X						= m_wSTR_Text_X;
	m_wDEFENSE_Text_Y						= m_wNewCharBox_Y + 149;

	m_wPROTECTION_Text_X					= m_wSTR_Text_X;
	m_wPROTECTION_Text_Y					= m_wNewCharBox_Y + 168;

	m_wTOHIT_Text_X							= m_wSTR_Text_X;
	m_wTOHIT_Text_Y							= m_wNewCharBox_Y + 187;

	m_wDAM_Text_X							= m_wSTR_Text_X;
	m_wDAM_Text_Y							= m_wNewCharBox_Y + 207;

	m_wStet_Box_X							= m_wNewCharBox_X + 155;
	m_wStet_Box_Y							= m_wNewCharBox_Y + 235;

	m_wBonus_Text_X							= (WORD)GetPrivateProfileInt(arrstrAppName, "BONUS_TEXT_X", 0, arrstrFileName) + m_wStet_Box_X;
	m_wBonus_Text_Y							= (WORD)GetPrivateProfileInt(arrstrAppName, "BONUS_TEXT_Y", 0, arrstrFileName) + m_wStet_Box_Y;

	m_ptStet_Plus[STET_STR].x				= m_wNewCharBox_X + 229;
	m_ptStet_Plus[STET_STR].y				= m_wNewCharBox_Y + 56;

	m_ptStet_Plus[STET_DEX].x				= m_ptStet_Plus[STET_STR].x;
	m_ptStet_Plus[STET_DEX].y				= m_wNewCharBox_Y + 74;

	m_ptStet_Plus[STET_INT].x				= m_ptStet_Plus[STET_STR].x;
	m_ptStet_Plus[STET_INT].y				= m_wNewCharBox_Y + 94;

	m_ptStet_Minus[STET_STR].x				= m_wNewCharBox_X + 243;
	m_ptStet_Minus[STET_STR].y				= m_wNewCharBox_Y + 56;

	m_ptStet_Minus[STET_DEX].x				= m_ptStet_Minus[STET_STR].x;
	m_ptStet_Minus[STET_DEX].y				= m_wNewCharBox_Y + 74;

	m_ptStet_Minus[STET_INT].x				= m_ptStet_Minus[STET_STR].x;
	m_ptStet_Minus[STET_INT].y				= m_wNewCharBox_Y + 94;

	m_wPrevButton_X							= (WORD)GetPrivateProfileInt(arrstrAppName, "PREV_BUTTON_X", 0, arrstrFileName);
	m_wPrevButton_Y							= (WORD)GetPrivateProfileInt(arrstrAppName, "PREV_BUTTON_Y", 0, arrstrFileName);

	m_wNextButton_X							=  m_wNewCharBox_X + 27;
	m_wNextButton_Y							=  m_wNewCharBox_Y + 429;

	m_wEffect_Fire_Left1_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_FIRE_LEFT1_X", 0, arrstrFileName);
	m_wEffect_Fire_Left1_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_FIRE_LEFT1_Y", 0, arrstrFileName);

	m_wEffect_Fire_Left2_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_FIRE_LEFT2_X", 0, arrstrFileName);
	m_wEffect_Fire_Left2_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_FIRE_LEFT2_Y", 0, arrstrFileName);

	m_wEffect_Fire_Right1_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_FIRE_RIGHT1_X", 0, arrstrFileName);
	m_wEffect_Fire_Right1_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_FIRE_RIGHT1_Y", 0, arrstrFileName);

	m_wEffect_Fire_Right2_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_FIRE_RIGHT2_X", 0, arrstrFileName);
	m_wEffect_Fire_Right2_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_FIRE_RIGHT2_Y", 0, arrstrFileName);

	m_wEffect_Fire_Center_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_FIRE_FIRE_CENTER_X", 0, arrstrFileName);
	m_wEffect_Fire_Center_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_FIRE_FIRE_CENTER_Y", 0, arrstrFileName);
	
	m_wChild_X								= (WORD)GetPrivateProfileInt(arrstrAppName, "CHILD_X", 0, arrstrFileName);
	m_wChild_Y								= (WORD)GetPrivateProfileInt(arrstrAppName, "CHILD_Y", 0, arrstrFileName);

	m_wAdult_X								= (WORD)GetPrivateProfileInt(arrstrAppName, "ADULT_X", 0, arrstrFileName);
	m_wAdult_Y								= (WORD)GetPrivateProfileInt(arrstrAppName, "ADULT_Y", 0, arrstrFileName);

	m_wViolence_X							= (WORD)GetPrivateProfileInt(arrstrAppName, "VIOLENCE_X", 0, arrstrFileName);
	m_wViolence_Y							= (WORD)GetPrivateProfileInt(arrstrAppName, "VIOLENCE_Y", 0, arrstrFileName);

	m_wFear_X								= (WORD)GetPrivateProfileInt(arrstrAppName, "FEAR_X", 0, arrstrFileName);
	m_wFear_Y								= (WORD)GetPrivateProfileInt(arrstrAppName, "FEAR_Y", 0, arrstrFileName);

	m_wTex_Bar_X							= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_BAR_X", 0, arrstrFileName);
	m_wTex_Bar_Y							= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_BAR_Y", 0, arrstrFileName);
	
	m_wAni_Mark_X							= (WORD)GetPrivateProfileInt(arrstrAppName, "ANI_MARK_X", 0, arrstrFileName);
	m_wAni_Mark_Y							= (WORD)GetPrivateProfileInt(arrstrAppName, "ANI_MARK_Y", 0, arrstrFileName);

	m_ptText_Line[LINE1].x					= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_LINE1_X", 0, arrstrFileName)	+ m_wTex_Bar_X;
	m_ptText_Line[LINE1].y					= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_LINE1_Y", 0, arrstrFileName)	+ m_wTex_Bar_Y;

	m_ptText_Line[LINE2].x					= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_LINE2_X", 0, arrstrFileName)	+ m_wTex_Bar_X;
	m_ptText_Line[LINE2].y					= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_LINE2_Y", 0, arrstrFileName)	+ m_wTex_Bar_Y;

	m_ptText_Line[LINE3].x					= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_LINE3_X", 0, arrstrFileName)	+ m_wTex_Bar_X;
	m_ptText_Line[LINE3].y					= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_LINE3_Y", 0, arrstrFileName)	+ m_wTex_Bar_Y;

	m_ptText_Line[LINE4].x					= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_LINE4_X", 0, arrstrFileName)	+ m_wTex_Bar_X;
	m_ptText_Line[LINE4].y					= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_LINE4_Y", 0, arrstrFileName)	+ m_wTex_Bar_Y;

	m_wPrimeum_Use_Day_Txt_X				= (WORD)GetPrivateProfileInt(arrstrAppName, "PRIMEUP_USE_DAY_TEXT_X", 0, arrstrFileName);
	m_wPrimeum_Use_Day_Txt_Y				= (WORD)GetPrivateProfileInt(arrstrAppName, "PRIMEUP_USE_DAY_TEXT_Y", 0, arrstrFileName);

	GetPrivateProfileString(arrstrAppName, "TEXT_LINE1", "", m_arrTextLine[LINE1], sizeof(m_arrTextLine[LINE1]), arrstrFileName);
	GetPrivateProfileString(arrstrAppName, "TEXT_LINE2", "", m_arrTextLine[LINE2], sizeof(m_arrTextLine[LINE2]), arrstrFileName);
	GetPrivateProfileString(arrstrAppName, "TEXT_LINE3", "", m_arrTextLine[LINE3], sizeof(m_arrTextLine[LINE3]), arrstrFileName);
	GetPrivateProfileString(arrstrAppName, "TEXT_LINE4", "", m_arrTextLine[LINE4], sizeof(m_arrTextLine[LINE4]), arrstrFileName);

	m_lev_name.SetPosition(m_wCharNameFocus_X,	m_wCharNameFocus_Y);
}


//-----------------------------------------------------------------------------
// GetPoint
//
// color array¿¡¼­ colorsetÀÇ point¸¦ ¹ÝÈ¯ÇÑ´Ù.
//-----------------------------------------------------------------------------
Point C_VS_UI_NEWCHAR::GetPoint(int colorset, bool bl_skin_color)
{
	int i, j;
	Point point;

	if (bl_skin_color)
	{
		for (j=0; j < COLOR_LIST_Y; j++)
			for (i=0; i < COLOR_LIST_X; i++)
				if (colorset == m_skin_color_array[i][j])
				{
					point.Set(i, j);
					return point;
				}
	}
	else
	{
		for (j=0; j < COLOR_LIST_Y; j++)
			for (i=0; i < COLOR_LIST_X; i++)
				if (colorset == m_hair_color_array[i][j])
				{
					point.Set(i, j);
					return point;
				}
	}

	assert(0);

	return point;
}

//-----------------------------------------------------------------------------
// GetColor
//
// color array¿¡¼­ (x, y)ÀÇ color setÀ¸·Î color¸¦ ±¸ÇØ¼­ ¹ÝÈ¯ÇÑ´Ù.
//-----------------------------------------------------------------------------
int C_VS_UI_NEWCHAR::GetColor(int _x, int _y, bool bl_skin_color)
{
	int colorset;
	if (bl_skin_color)
		colorset = m_skin_color_array[_x][_y];
	else
		colorset = m_hair_color_array[_x][_y];

	const int center_value = 10;

	return CIndexSprite::ColorSet[colorset][center_value];
}


void C_VS_UI_NEWCHAR::ShowButtonDescription(C_VS_UI_EVENT_BUTTON * p_button)
{

}

void C_VS_UI_NEWCHAR::ShowButtonName(C_VS_UI_EVENT_BUTTON *p_button)
{
	switch(p_button->GetID())
	{
	case SLAYER_ID:
		p_button->x	= m_wSelect_Race_Slayer_Button_X;
		p_button->y	= m_wSelect_Race_Slayer_Button_Y;
		g_PrintColorStr(p_button->x + 126, 	p_button->y + 33, "ÈË  Àà", gpC_base->m_haysNameBig, RGB_WHITE);
		break;
	case VAMPIRE_ID:
		p_button->x	= m_wSelect_Race_Vampire_Button_X;
		p_button->y	= m_wSelect_Race_Vampire_Button_Y;
		g_PrintColorStr(p_button->x + 126, 	p_button->y + 33, "ÎüÑª¹í", gpC_base->m_haysNameBig, RGB_WHITE);
		break;
	case OUSTERS_ID:
		p_button->x	= m_wSelect_Race_Ousters_Button_X;
		p_button->y	= m_wSelect_Race_Ousters_Button_Y;
		g_PrintColorStr(p_button->x + 126, 	p_button->y + 33, "Ä§  Áé", gpC_base->m_haysNameBig, RGB_WHITE);
		break;

	case BACK_ID:
		p_button->x	= m_wPrevButton_X;
		p_button->y	= m_wPrevButton_Y;
		g_PrintColorStr(p_button->x + 90, 	p_button->y + 9, "·µ   »Ø", gpC_base->m_title_menu_pi, RGB_WHITE);
		break;

	case NEXT_ID:
		p_button->x	= m_wNextButton_X;
		p_button->y	= m_wNextButton_Y;
		g_PrintColorStr(p_button->x + 85, 	p_button->y + 9, "´´  ½¨", gpC_base->m_title_menu_pi, RGB_WHITE);
		break;

	case CHECK_ID:
		p_button->x	= m_wNameCheck_Button_X;
		p_button->y	= m_wNameCheck_Button_Y;
		g_PrintColorStr(p_button->x + 13, 	p_button->y + 8, "¼ì²âÃû×Ö", gpC_base->m_title_menu_pi, RGB_WHITE);
		break;
	case SELECT_SKIN:
		p_button->x	= m_wNewCharBox_X+16;
		p_button->y	= m_wNameCheck_Button_Y+145;
		g_PrintColorStr(p_button->x + 24, 	p_button->y + 7, "Íâ±í±ä¸ü", gpC_base->m_title_menu_pi, RGB_WHITE);
		break;
	}
}

//-----------------------------------------------------------------------------
// ShowButtonWidget
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_NEWCHAR::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{
	switch(p_button->GetID())
	{
	case BACK_ID:
		p_button->x	= m_wPrevButton_X;
		p_button->y	= m_wPrevButton_Y;
		break;

	case NEXT_ID:
		p_button->x	= m_wNextButton_X;
		p_button->y	= m_wNextButton_Y;
		break;

	case CHECK_ID:
		p_button->x	= m_wNameCheck_Button_X;
		p_button->y	= m_wNameCheck_Button_Y;
		break;

	case SELECT_SKIN:
		p_button->x	= m_wNewCharBox_X+16;
		p_button->y	= m_wNameCheck_Button_Y+145;
		break;

	case CHAR_LEFT_LOTATION_ID:
		p_button->x	= m_wCharLeftRotation_Button_X;
		p_button->y	= m_wCharLeftRotation_Button_Y;
		break;

	case CHAR_RIGHT_LOTATION_ID:
		p_button->x	= m_wCharRightRotation_Button_X;
		p_button->y	= m_wCharRightRotation_Button_Y;
		break;

	case SLAYER_ID:
		if(p_button->GetFocusState())
		{
			if (p_button->GetPressState()) // push state
			{
				m_btRace_Select	= RACE_SLAYER;
			}
		}

		p_button->x	= m_wSelect_Race_Slayer_Button_X;
		p_button->y	= m_wSelect_Race_Slayer_Button_Y;

		m_image_hays_spk.BltLocked(m_wSelect_Race_Slayer_Button_X, m_wSelect_Race_Slayer_Button_Y, BUTTON_SLAYER_NORMAL);
		if(m_btRace_Select == RACE_SLAYER)
		{
			m_image_hays_spk.BltLocked(m_wSelect_Race_Slayer_Button_X, m_wSelect_Race_Slayer_Button_Y, BUTTON_SLAYER_PRESS);
		}
		break;

	case VAMPIRE_ID:
		if(p_button->GetFocusState())
		{
			if (p_button->GetPressState()) // push state
			{
				m_btRace_Select	= RACE_VAMPIRE;
			}
		}

		p_button->x	= m_wSelect_Race_Vampire_Button_X;
		p_button->y	= m_wSelect_Race_Vampire_Button_Y;

		m_image_hays_spk.BltLocked(m_wSelect_Race_Vampire_Button_X, m_wSelect_Race_Vampire_Button_Y, BUTTON_VAMPIRE_NORMAL);
		if(m_btRace_Select == RACE_VAMPIRE)
		{
			m_image_hays_spk.BltLocked(m_wSelect_Race_Vampire_Button_X, m_wSelect_Race_Vampire_Button_Y, BUTTON_VAMPIRE_PRESS);
		}
		break;
		
	case OUSTERS_ID:
		if(p_button->GetFocusState())
		{
			if (p_button->GetPressState()) // push state
			{
				m_btRace_Select	= RACE_OUSTERS;
			}
		}

		p_button->x	= m_wSelect_Race_Ousters_Button_X;
		p_button->y	= m_wSelect_Race_Ousters_Button_Y;

		m_image_hays_spk.BltLocked(m_wSelect_Race_Ousters_Button_X, m_wSelect_Race_Ousters_Button_Y, BUTTON_OUTER_NORMAL);
		if(m_btRace_Select == RACE_OUSTERS)
		{
			m_image_hays_spk.BltLocked(m_wSelect_Race_Ousters_Button_X, m_wSelect_Race_Ousters_Button_Y, BUTTON_OUTER_PRESS);
		}
		break;
	}

	if(!((p_button->GetID() == SLAYER_ID)	||	(p_button->GetID()	==	VAMPIRE_ID)	||	(p_button->GetID() == OUSTERS_ID)))
	{
		if ( p_button->GetID() == BACK_ID || p_button->GetID() == NEXT_ID )
			m_image_hays_spk.BltLocked(p_button->x, p_button->y, p_button->m_image_index);
		else if ( p_button->GetID() == CHECK_ID )
			m_image_hays_spk.BltLocked(p_button->x, p_button->y, p_button->m_image_index);
		else if ( p_button->GetID() == SELECT_SKIN )
			m_image_hays_spk.BltLocked(p_button->x, p_button->y, p_button->m_image_index);
		else
			m_image_spk.BltLocked(p_button->x, p_button->y, p_button->m_image_index);
	}
	if(p_button->GetFocusState())
	{
		if ( p_button->GetPressState() )
		{
			if(!((p_button->GetID() == SLAYER_ID)	||	(p_button->GetID()	==	VAMPIRE_ID)	||	(p_button->GetID() == OUSTERS_ID)))
			{
				if ( p_button->GetID() == BACK_ID || p_button->GetID() == NEXT_ID )
					m_image_hays_spk.BltLocked(p_button->x, p_button->y, p_button->m_image_index-1);
				else if ( p_button->GetID() == CHECK_ID )
					m_image_hays_spk.BltLocked(p_button->x, p_button->y, p_button->m_image_index-1);
				else if ( p_button->GetID() == SELECT_SKIN )
					m_image_hays_spk.BltLocked(p_button->x, p_button->y, p_button->m_image_index-1);
			}
		}
		else
		{
			if(!(p_button->GetID() == CHECK_ID))
			{
				if(p_button->m_alpha >= 31)
					p_button->m_alpha = 0;
			}

			if(!((p_button->GetID() == SLAYER_ID)	||	(p_button->GetID()	==	VAMPIRE_ID)	||	(p_button->GetID() == OUSTERS_ID)))
			{
				if ( p_button->GetID() == BACK_ID || p_button->GetID() == NEXT_ID)
					m_image_hays_spk.BltLockedAlpha(p_button->x, p_button->y, p_button->m_image_index-1, p_button->m_alpha);
				else if ( p_button->GetID() == CHECK_ID )
					m_image_hays_spk.BltLockedAlpha(p_button->x, p_button->y, p_button->m_image_index-1, p_button->m_alpha);
				else if ( p_button->GetID() == SELECT_SKIN )
					m_image_hays_spk.BltLockedAlpha(p_button->x, p_button->y, p_button->m_image_index-1, p_button->m_alpha);
				else
					m_image_spk.BltLockedAlpha(p_button->x, p_button->y, p_button->m_image_index-1, p_button->m_alpha);
			}
		}

	}
/*	if(p_button->GetID() == MALE_ID || p_button->GetID() == FEMALE_ID 
		|| p_button->GetID() == SLAYER_ID || p_button->GetID() == VAMPIRE_ID || p_button->GetID() == OUSTERS_ID )
	{
		if(p_button->GetFocusState())
		{
			if(m_p_slot->Race != RACE_OUSTERS)
				m_image_spk.BltLocked(x+p_button->x+20, y+p_button->y, p_button->m_image_index);
		}
	}
	else
	if(p_button->GetID() == BACK_ID || p_button->GetID() == NEXT_ID)
	{
		if(p_button->GetFocusState())
		{
			if (p_button->GetPressState()) // push state
				m_common_spk.BltLocked(x+p_button->x, y+p_button->y, p_button->m_image_index+1);
			else
			{
				m_common_spk.BltLocked(x+p_button->x, y+p_button->y, p_button->m_image_index);
				m_common_spk.BltLockedAlpha(x+p_button->x, y+p_button->y, p_button->m_image_index+2, p_button->m_alpha);
			}
			if(p_button->GetID() == BACK_ID)
				m_focused_help = HELP_BACK;
			else
				m_focused_help = HELP_NEXT;
		}
		else
			m_common_spk.BltLocked(x+p_button->x, y+p_button->y, p_button->m_image_index);
	}
	
	else
	{
		if( 
			(p_button->GetID() >= STR_PLUS_ID && p_button->GetID() <= INT_MINUS_ID && m_p_slot->Race !=  RACE_OUSTERS ) ||
			(p_button->GetID() == REROLL_ID && m_p_slot->Race != RACE_SLAYER )
		  )
			return;

		if(p_button->GetFocusState())
		{
			if( m_p_slot->Race == RACE_SLAYER || !(p_button->GetID() == LOAD_ID || p_button->GetID() == SAVE_ID || p_button->GetID() == REROLL_ID || p_button->GetID() == FACE_BACK_ID || p_button->GetID() == FACE_NEXT_ID))
			{
				if (p_button->GetPressState()) // push state
					m_image_spk.BltLocked(x+p_button->x, y+p_button->y, p_button->m_image_index+1);
				else
				{
					m_image_spk.BltLocked(x+p_button->x, y+p_button->y, p_button->m_image_index);
					m_image_spk.BltLockedAlpha(x+p_button->x, y+p_button->y, p_button->m_image_index+2, p_button->m_alpha);
				}
	
				switch(p_button->GetID())
				{
				case CHECK_ID:
					m_focused_help = HELP_CHECK;
					break;
					
				case LOAD_ID:
					m_focused_help = HELP_LOAD;
					break;
					
				case SAVE_ID:
					m_focused_help = HELP_SAVE;
					break;
					
				case REROLL_ID:
					m_focused_help = HELP_REROLL;
					break;
				}
			}// else 
		}

		else
		{
			if( m_p_slot->Race == RACE_SLAYER && (p_button->GetID() == LOAD_ID || p_button->GetID() == SAVE_ID || p_button->GetID() == REROLL_ID) )
			{
				m_image_spk.BltLocked(x+p_button->x, y+p_button->y, p_button->m_image_index);
				return;
			}

			if( 
				(
				m_p_slot->Race == RACE_SLAYER || 
				!(p_button->GetID() == LOAD_ID || 
				p_button->GetID() == SAVE_ID || 
				p_button->GetID() == REROLL_ID || 
				p_button->GetID() == FACE_BACK_ID || 
				p_button->GetID() == FACE_NEXT_ID)
				)

				&& (m_p_slot->Race == RACE_OUSTERS && p_button->GetID() >= STR_PLUS_ID && p_button->GetID() <= INT_MINUS_ID))
				m_image_spk.BltLocked(x+p_button->x, y+p_button->y, p_button->m_image_index);
		}
	}
*/
}

//-----------------------------------------------------------------------------
// WindowEventReceiver
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_NEWCHAR::WindowEventReceiver(id_t event)
{
}

//-----------------------------------------------------------------------------
// IsPixel
//
// 
//-----------------------------------------------------------------------------
bool C_VS_UI_NEWCHAR::IsPixel(int _x, int _y)
{
	return m_image_hays_spk.IsPixel(_x, _y, m_iCurBackPicID);
}

//-----------------------------------------------------------------------------
// SetCharacterToThisSlot
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_NEWCHAR::SetCharacterToThisSlot(int slot, S_SLOT * p_slot)
{ 
	assert(p_slot->bl_set == false);
	
	m_p_slot = p_slot; 
	m_selected_slot = slot;

	// default
	m_p_slot->bl_female = false;

#if __CONTENTS(__RACE_OUSTERS)
	m_btRace_Select	= rand()%3;
#else
	m_btRace_Select = rand()%2;
#endif // ÀÚµ¿À¸·Î Á¾Á·¼±ÅÃµÇ´Â ºÎºÐ.

	srand(GetTickCount());

	m_p_slot->man_info.coat = M_COAT1;
	switch(m_btRace_Select)
	{
	case RACE_SLAYER :
		m_p_slot->Race = RACE_SLAYER;
		m_p_slot->man_info.face = M_FACE1;
		m_p_slot->man_info.hair = M_HAIR1;
		break;
	case RACE_VAMPIRE:
		m_p_slot->Race = RACE_VAMPIRE;
		m_p_slot->man_info.face = M_FACE2;
		m_p_slot->man_info.hair = M_HAIR2;
		break;
	default :
		m_p_slot->Race = RACE_OUSTERS;
		m_p_slot->man_info.face = M_FACE3;
		m_p_slot->man_info.hair = M_HAIR3;
		break;
	}
	
	m_p_slot->man_info.helmet = M_NO_WEAR;
	m_p_slot->man_info.trouser = M_TROUSER1;
	m_p_slot->man_info.right = M_NO_WEAR;//M_BLADE;
	m_p_slot->man_info.left = M_NO_WEAR;//M_DRAGON_SHIELD;

	m_p_slot->left_color = 377;
	m_p_slot->right_color = 377;
	m_p_slot->helmet_color = 377;
	m_p_slot->trouser_color = 377;
	m_p_slot->coat_color = 377;

	if(m_p_slot->Race == RACE_OUSTERS)
		m_p_slot->skin_color = 377;

//#if __CONTENTS(__RACE_OUSTERS)		
	Run(SLAYER_ID + m_btRace_Select);
//#else	
//	Run(SLAYER_ID+rand()%2);
// #endif
}

//-----------------------------------------------------------------------------
// KeyboardControl
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_NEWCHAR::KeyboardControl(UINT message, UINT key, long extra)
{
	if (message == WM_KEYDOWN && key == VK_ESCAPE) // cancel!
	{
		Run(BACK_ID);
	}
	if (message == WM_CHAR)
	{
		if (isdigit(key) && m_lev_name.Size() == 0)
			return;

		char ignore_char[] = {'~', '`', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_',
									'+', '=', '\\', '|', '[', ']', '{', '}', ';', ':', '\"', '\'', ',', '<', '.', '>',
									'/', '?', ' '};

		for (int i=0; i<sizeof(ignore_char); i++)
			if ((char)key == ignore_char[i])
				return;
	}

	if(message == WM_KEYUP && key == VK_RETURN)
		Run(NEXT_ID);

	Window::KeyboardControl(message, key, extra);
}

//-----------------------------------------------------------------------------
//	Run
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_NEWCHAR::Run(id_t id)
{

	int i = 0;

	if( 
			(id >= STR_PLUS_ID && id <= INT_MINUS_ID && m_p_slot->Race !=  RACE_OUSTERS ) ||
			(id == REROLL_ID && m_p_slot->Race != RACE_SLAYER )
		  )
			return;

	switch (id)
	{
		case SLAYER_ID:
			m_p_slot->Race = RACE_SLAYER;
			m_p_slot->man_info.helmet = M_NO_WEAR;
			m_p_slot->man_info.right = M_NO_WEAR;
			m_p_slot->man_info.coat = M_COAT1;
			m_p_slot->man_info.trouser = M_TROUSER1;

			Run(MALE_ID+rand()%2);
			for(i = 0; i < rand()%5; i++)
				Run(FACE_NEXT_ID);
			m_skin_point.x = rand()%COLOR_LIST_X;
			m_skin_point.y = rand()%COLOR_LIST_Y;
			m_hair_point.x = rand()%COLOR_LIST_X;
			m_hair_point.y = rand()%COLOR_LIST_Y;
			m_p_slot->hair_color = m_hair_color_array[m_hair_point.x][m_hair_point.y];
			m_p_slot->skin_color = m_skin_color_array[m_skin_point.x][m_skin_point.y];
			RollDice();

			m_wFace_Alpha							= 0;
			m_btSelect_Face							= 0;
			m_btVirtureSelect_Face					= 0;
			break;

		case VAMPIRE_ID:
			m_p_slot->Race = RACE_VAMPIRE;
			m_p_slot->man_info.coat = (CHAR_MAN)1;
			Run(MALE_ID+rand()%2);
			m_skin_point.x = rand()%COLOR_LIST_X;
			m_skin_point.y = rand()%COLOR_LIST_Y;
			m_p_slot->skin_color = m_skin_color_array[m_skin_point.x][m_skin_point.y];
			RollDice();

			m_wFace_Alpha							= 0;
			m_btSelect_Face							= 0;
			m_btVirtureSelect_Face					= 0;
			break;

		case OUSTERS_ID:
			m_p_slot->Race = RACE_OUSTERS;
			m_p_slot->man_info.coat = (CHAR_MAN)1;
			m_p_slot->man_info.right = (CHAR_MAN)0;
			m_hair_point.x = rand()%COLOR_LIST_X;
			m_hair_point.y = rand()%COLOR_LIST_Y;
			m_p_slot->hair_color = m_hair_color_array[m_hair_point.x][m_hair_point.y];
			RollDice();

			m_wFace_Alpha							= 0;
			m_btSelect_Face							= 0;
			m_btVirtureSelect_Face					= 0;
			break;
			
		case MALE_ID:
			m_p_slot->bl_female = false;

			m_wFace_Alpha							= 0;
			m_btSelect_Face							= 0;
			m_btVirtureSelect_Face					= 0;	
			break;

		case FEMALE_ID:
			m_p_slot->bl_female = true;

			m_wFace_Alpha							= 0;
			m_btSelect_Face							= 0;
			m_btVirtureSelect_Face					= 0;
			break;

		case NEXT_ID:
			if (m_lev_name.Size() == 0)
			{
				g_msg_empty_name->Start();
			}
			else if(m_p_slot->Race == RACE_OUSTERS && m_p_slot->bonus_point != 0)
			{
				g_msg_left_bonus_point->Start();
			}
			else
			{
				SendNewCharacterToClient();
			}
			break;

		case BACK_ID:
			Finish();
			gC_vs_ui.StartCharacterManager(true);
			break;

		case FACE_BACK_ID:			
			if( m_p_slot->Race == RACE_SLAYER )
			{
				switch(m_p_slot->man_info.hair)
				{
				case M_HAIR1:
					m_p_slot->man_info.hair = M_HAIR3;
					m_p_slot->man_info.face = M_FACE3;
					break;
					
				case M_HAIR2:
					m_p_slot->man_info.hair = M_HAIR1;
					m_p_slot->man_info.face = M_FACE1;
					break;
					
				case M_HAIR3:
					m_p_slot->man_info.hair = M_HAIR2;
					m_p_slot->man_info.face = M_FACE2;
					break;
				}
			}
			break;

		case FACE_NEXT_ID:
			if( m_p_slot->Race == RACE_SLAYER )
			{
				switch(m_p_slot->man_info.hair)
				{
				case M_HAIR2:
					m_p_slot->man_info.hair = M_HAIR3;
					m_p_slot->man_info.face = M_FACE3;
					break;
					
				case M_HAIR3:
					m_p_slot->man_info.hair = M_HAIR1;
					m_p_slot->man_info.face = M_FACE1;
					break;
					
				case M_HAIR1:
					m_p_slot->man_info.hair = M_HAIR2;
					m_p_slot->man_info.face = M_FACE2;
					break;
				}
			}
			break;

		case SAVE_ID:
			if( m_p_slot->Race == RACE_SLAYER )
			{
				m_iSave[0] = m_p_slot->STR_PURE;
				m_iSave[1] = m_p_slot->DEX_PURE;
				m_iSave[2] = m_p_slot->INT_PURE;
			}
			break;
		case SELECT_BLAZE:
		case SELECT_SWORD:
		case SELECT_GUN:
		case SELECT_HEAL:
		case SELECT_ENCHANT:
			if( m_p_slot->Race == RACE_SLAYER )
			{
				m_selected_job = id-SELECT_BLAZE;
				RollDice();
			}
			break;

		case LOAD_ID:
			if( m_p_slot->Race == RACE_SLAYER )
				RollDice(true);
			break;

		case REROLL_ID:
			if( m_p_slot->Race == RACE_SLAYER )
				RollDice();
			break;

		case CHECK_ID:
			if (m_lev_name.Size() == 0)
			{
				g_msg_empty_name->Start();
			}
			else
			{
				char *sz_temp;
				g_Convert_DBCS_Ascii2SingleByte(m_lev_name.GetString(), m_lev_name.Size(), sz_temp);
				m_p_slot->sz_name = sz_temp;
				DeleteNew(sz_temp);
				gpC_base->SendMessage(UI_NEWCHARACTER_CHECK, 0, 0, (void *)m_p_slot->sz_name.c_str());
			}
			break;

		case STR_PLUS_ID:
			if(m_p_slot->bonus_point > 0)
			{
				m_p_slot->STR_PURE++;
				m_p_slot->bonus_point--;
			}
			break;

		case STR_MINUS_ID:
			if(m_p_slot->STR_PURE > 10)
			{
				m_p_slot->STR_PURE--;
				m_p_slot->bonus_point++;
			}
			break;

		case DEX_PLUS_ID:
			if(m_p_slot->bonus_point > 0)
			{
				m_p_slot->DEX_PURE++;
				m_p_slot->bonus_point--;
			}
			break;
			
		case DEX_MINUS_ID:
			if(m_p_slot->DEX_PURE > 10)
			{
				m_p_slot->DEX_PURE--;
				m_p_slot->bonus_point++;
			}
			break;
			
		case INT_PLUS_ID:
			if(m_p_slot->bonus_point > 0)
			{
				m_p_slot->INT_PURE++;
				m_p_slot->bonus_point--;
			}
			break;
			
		case INT_MINUS_ID:
			if(m_p_slot->INT_PURE > 10)
			{
				m_p_slot->INT_PURE--;
				m_p_slot->bonus_point++;
			}
			break;

		case CHAR_LEFT_LOTATION_ID:
			m_chDirection--;
			if(m_chDirection < 0)
				m_chDirection = 7;

			break;

		case CHAR_RIGHT_LOTATION_ID:
			m_chDirection++;
			if(m_chDirection > 7)
				m_chDirection = 0;

			break;
		case SELECT_SKIN:
			if(m_show_skin == false)
				m_show_skin = true;
			else if(m_show_skin == true)
				m_show_skin = false;
			 break;
	}
}





void	C_VS_UI_NEWCHAR::MouseSelectMale_OR_Female_RollOver(int _x, int _y)				//¼ºº° ¼±ÅÃ
{
	if(m_p_slot->Race == RACE_SLAYER || m_p_slot->Race == RACE_VAMPIRE)		//¼ºº° ¼±ÅÃ Á¶°Ç
	{
		if(((_x >= m_wMale_Select_Button_X) && (_x <= m_wMale_Select_Button_X + m_image_hays_spk.GetWidth(BTN_UNCHECK))) 
			&&
			((_y >= m_wMale_Select_Button_Y) && (_y <= m_wMale_Select_Button_Y + m_image_hays_spk.GetHeight(BTN_UNCHECK))))
		{
			m_btVirtureSelect_Male	= VIRTURE_SELECT_MALE;
		}
		else if(((_x >= m_wFemale_Select_Button_X) && (_x <= m_wFemale_Select_Button_X + m_image_hays_spk.GetWidth(BTN_UNCHECK))) 
				&&
				((_y >= m_wFemale_Select_Button_Y) && (_y <= m_wFemale_Select_Button_Y + m_image_hays_spk.GetHeight(BTN_UNCHECK))))
		{
			m_btVirtureSelect_Male	= VIRTURE_SELECT_FEMALE;
		}
		else
		{
			m_btVirtureSelect_Male	= VIRTURE_NO_SELECT;
		}
	}
}



void	C_VS_UI_NEWCHAR::MouseSelectFace_RollOver(int _x, int _y)							//¾ó±¼ ¼±ÅÃ
{
	if(m_p_slot->Race == RACE_SLAYER)		//¾ó±¼ ¼±ÅÃ Á¶°Ç
	{
		if(m_p_slot->bl_female	== false)
		{
			for(int i = 0; i < SELECT_FACE_MAX; i++)
			{
				if(((_x >= m_ptFace_Radio[i].x) && (_x <= m_ptFace_Radio[i].x + m_image_spk.GetWidth(CHAR_FACE_SLAYER_MALE_SELECT_1 + i))) 
					&&
					((_y >= m_ptFace_Radio[i].y) && (_y <= m_ptFace_Radio[i].y + m_image_spk.GetHeight(CHAR_FACE_SLAYER_MALE_SELECT_1 + i))))
					{
						m_btVirtureSelect_Face	= SELECT_LEFT_FACE + i;
					}
			}
		}
		else
		{
			for(int i = 0; i < SELECT_FACE_MAX; i++)
			{
				if(((_x >= m_ptFace_Radio[i].x) && (_x <= m_ptFace_Radio[i].x + m_image_spk.GetWidth(CHAR_FACE_SLAYER_FEMALE_SELECT_1 + i))) 
					&&
					((_y >= m_ptFace_Radio[i].y) && (_y <= m_ptFace_Radio[i].y + m_image_spk.GetHeight(CHAR_FACE_SLAYER_FEMALE_SELECT_1 + i))))
				{
					m_btVirtureSelect_Face	= SELECT_LEFT_FACE + i;
				}
			}
		}
	}
}




void	C_VS_UI_NEWCHAR::MouseSelectStet_RollOver(int _x, int _y)		//´É·ÂÄ¡
{
	if(m_p_slot->Race == RACE_SLAYER)		//´É·ÂÄ¡ ¼³Á¤
	{
		if(((_x >=m_wSave_Button_X) && (_x <= m_wSave_Button_X + m_image_spk.GetWidth(SAVE_BUTTON))) 
			&&
			((_y >= m_wSave_Button_Y) && (_y <= m_wSave_Button_Y + m_image_spk.GetHeight(SAVE_BUTTON))))
		{
			m_wSave_Button_Alpha++;
			if(m_wSave_Button_Alpha >= 31)
				m_wSave_Button_Alpha	= 31;
		}
		else
		{
			m_wSave_Button_Alpha = 0;
		}

		if(((_x >=m_wLoad_Button_X) && (_x <= m_wLoad_Button_X + m_image_spk.GetWidth(LOAD_BUTTON))) 
			&&
			((_y >= m_wLoad_Button_Y) && (_y <= m_wLoad_Button_Y + m_image_spk.GetHeight(LOAD_BUTTON))))
		{
			m_wLoad_Button_Alpha++;
			if(m_wLoad_Button_Alpha >= 31)
				m_wLoad_Button_Alpha	= 31;
		}
		else
		{
			m_wLoad_Button_Alpha = 0;
		}

		if(((_x >=m_wReset_Button_X) && (_x <= m_wReset_Button_X + m_image_spk.GetWidth(RESET_BUTTON))) 
			&&
			((_y >= m_wReset_Button_Y) && (_y <= m_wReset_Button_Y + m_image_spk.GetHeight(RESET_BUTTON))))
		{
			m_wReset_Button_Alpha++;
			if(m_wReset_Button_Alpha >= 31)
				m_wReset_Button_Alpha	= 31;
		}
		else
		{
			m_wReset_Button_Alpha = 0;
		}
	}

	if(m_p_slot->Race == RACE_OUSTERS)		//´É·ÂÄ¡ ¼³Á¤
	{
		for(int i = 0; i < STET_MAX; i++)
		{
			if(((_x >=m_ptStet_Plus[i].x) && (_x <= m_ptStet_Plus[i].x + m_image_hays_spk.GetWidth(BTN_ADD_NORMAL))) 
				&&
				((_y >= m_ptStet_Plus[i].y) && (_y <= m_ptStet_Plus[i].y + m_image_hays_spk.GetHeight(BTN_ADD_NORMAL))))
			{
				m_wStet_Plus_Button_Alpha[i]	+= 1;
				if(m_wStet_Plus_Button_Alpha[i] >= 31)
					m_wStet_Plus_Button_Alpha[i]	= 31;
			}
			else
			{
				m_wStet_Plus_Button_Alpha[i] = 0;
			}

			if(((_x >=m_ptStet_Minus[i].x) && (_x <= m_ptStet_Minus[i].x + m_image_hays_spk.GetWidth(BTN_DELETE_NORMAL))) 
				&&
				((_y >= m_ptStet_Minus[i].y) && (_y <= m_ptStet_Minus[i].y + m_image_hays_spk.GetHeight(BTN_DELETE_NORMAL))))
			{
				m_wStet_Minus_Button_Alpha[i]	+= 1;
				if(m_wStet_Minus_Button_Alpha[i] >= 31)
					m_wStet_Minus_Button_Alpha[i]	= 31;							
			}
			else
			{
				m_wStet_Minus_Button_Alpha[i] = 0;
			}
		}
	}
}



void	C_VS_UI_NEWCHAR::MouseSelectMale_OR_Female_Click(int _x, int _y)
{
	if(m_p_slot != NULL)
	{
		if(m_p_slot->Race == RACE_SLAYER || m_p_slot->Race == RACE_VAMPIRE)		// ¼ºº° ¼±ÅÃ Á¶°Ç
		{
			if(((_x >= m_wMale_Select_Button_X) && (_x <= m_wMale_Select_Button_X + m_image_hays_spk.GetWidth(BTN_CHECK))) 
				&&
				((_y >= m_wMale_Select_Button_Y) && (_y <= m_wMale_Select_Button_Y + m_image_hays_spk.GetHeight(BTN_CHECK))))
			{
				m_p_slot->bl_female = false;
			}
			else if(((_x >= m_wFemale_Select_Button_X) && (_x <= m_wFemale_Select_Button_X + m_image_hays_spk.GetWidth(BTN_CHECK))) 
				&&
				((_y >= m_wFemale_Select_Button_Y) && (_y <= m_wFemale_Select_Button_Y + m_image_hays_spk.GetHeight(BTN_CHECK))))
			{
				m_p_slot->bl_female = true;
			}
		}
	}
}

void	C_VS_UI_NEWCHAR::MouseSelectFace_Click(int _x, int _y)
{
	if(m_p_slot->Race == RACE_SLAYER)	//¾ó±¼ ¼±ÅÃ Á¶°Ç
	{
		if(m_p_slot->bl_female	== false)
		{
			for(int i = 0; i < SELECT_FACE_MAX; i++)
			{
				if(((_x >= m_ptFace_Radio[i].x) && (_x <= m_ptFace_Radio[i].x + m_image_spk.GetWidth(CHAR_FACE_SLAYER_MALE_SELECT_1 + i))) 
					&&
					((_y >= m_ptFace_Radio[i].y) && (_y <= m_ptFace_Radio[i].y + m_image_spk.GetHeight(CHAR_FACE_SLAYER_MALE_SELECT_1 + i))))
				{
					m_btSelect_Face	= SELECT_LEFT_FACE + i;

					switch(m_btSelect_Face)
					{
					case SELECT_LEFT_FACE:
						m_p_slot->man_info.hair = M_HAIR3;
						m_p_slot->man_info.face = M_HAIR3;
						break;

					case SELECT_CENTER_FACE:
						m_p_slot->man_info.hair = M_HAIR1;
						m_p_slot->man_info.face = M_HAIR1;
						break;
					
					case SELECT_RIGHT_FACE:
						m_p_slot->man_info.hair = M_HAIR2;
						m_p_slot->man_info.face = M_HAIR2;
						break;
					}
				}
			}
		}
		else
		{
			for(int i = 0; i < SELECT_FACE_MAX; i++)
			{
				if(((_x >= m_ptFace_Radio[i].x) && (_x <= m_ptFace_Radio[i].x + m_image_spk.GetWidth(CHAR_FACE_SLAYER_FEMALE_SELECT_1 + i))) 
					&&
					((_y >= m_ptFace_Radio[i].y) && (_y <= m_ptFace_Radio[i].y + m_image_spk.GetHeight(CHAR_FACE_SLAYER_FEMALE_SELECT_1 + i))))
				{
					m_btSelect_Face	= SELECT_LEFT_FACE + i;
					
					switch(m_btSelect_Face)
					{
						case SELECT_LEFT_FACE:
							m_p_slot->man_info.hair = M_HAIR3;
							m_p_slot->man_info.face = M_HAIR3;
							break;
	
						case SELECT_CENTER_FACE:
							m_p_slot->man_info.hair = M_HAIR1;
							m_p_slot->man_info.face = M_HAIR1;
							break;
			
						case SELECT_RIGHT_FACE:
							m_p_slot->man_info.hair = M_HAIR2;
							m_p_slot->man_info.face = M_HAIR2;
							break;
				
					}
				}
			}
		}
	}
}

void	C_VS_UI_NEWCHAR::MouseSelectStet_Click(int _x, int _y)
{
	if(m_p_slot->Race == RACE_SLAYER)		//´É·ÂÄ¡ ¼³Á¤
	{
		//if(((_x >=m_wSave_Button_X) && (_x <= m_wSave_Button_X + m_image_spk.GetWidth(SAVE_BUTTON))) 
		//	&&
		//	((_y >= m_wSave_Button_Y) && (_y <= m_wSave_Button_Y + m_image_spk.GetHeight(SAVE_BUTTON))))
		//{
		//	Run(SAVE_ID);
		//}

		//if(((_x >=m_wLoad_Button_X) && (_x <= m_wLoad_Button_X + m_image_spk.GetWidth(LOAD_BUTTON))) 
		//	&&
		//	((_y >= m_wLoad_Button_Y) && (_y <= m_wLoad_Button_Y + m_image_spk.GetHeight(LOAD_BUTTON))))
		//{
		//	Run(LOAD_ID);
		//}

		//if(((_x >=m_wReset_Button_X) && (_x <= m_wReset_Button_X + m_image_spk.GetWidth(RESET_BUTTON))) 
		//	&&
		//	((_y >= m_wReset_Button_Y) && (_y <= m_wReset_Button_Y + m_image_spk.GetHeight(RESET_BUTTON))))
		//{
		//	Run(REROLL_ID);
		//}
		for(int i=0;i<5;i++)
		{
			if(((_x >=m_wOpset_BOX_X+i*30) && (_x <= m_wOpset_BOX_X+i*30 + m_image_hays_spk.GetWidth(BTN_BLAZE_NORMAL))) 
				&&
				((_y >= m_wOpset_BOX_Y) && (_y <= m_wOpset_BOX_Y + m_image_spk.GetHeight(BTN_BLAZE_NORMAL))))
			{
				Run(SELECT_BLAZE+i);
			}
		}
	}

	if(m_p_slot->Race == RACE_OUSTERS)		//´É·ÂÄ¡ ¼³Á¤
	{
		for(int i = 0; i < STET_MAX; i++)
		{
			if(((_x >=m_ptStet_Plus[i].x) && (_x <= m_ptStet_Plus[i].x + m_image_hays_spk.GetWidth(BTN_ADD_NORMAL))) 
				&&
				((_y >= m_ptStet_Plus[i].y) && (_y <= m_ptStet_Plus[i].y + m_image_hays_spk.GetHeight(BTN_ADD_NORMAL))))
			{
				Run(STR_PLUS_ID + i);
			}

			if(((_x >=m_ptStet_Minus[i].x) && (_x <= m_ptStet_Minus[i].x + m_image_hays_spk.GetWidth(BTN_DELETE_NORMAL))) 
				&&
			((_y >= m_ptStet_Minus[i].y) && (_y <= m_ptStet_Minus[i].y + m_image_hays_spk.GetHeight(BTN_DELETE_NORMAL))))
			{
				Run(STR_MINUS_ID + i);
			}
		}
	}
}


//-----------------------------------------------------------------------------
// MouseControl
//
// 
//-----------------------------------------------------------------------------
bool C_VS_UI_NEWCHAR::MouseControl(UINT message, int _x, int _y)
{
	Window::MouseControl(message, _x, _y);

	m_pC_button_group->MouseControl(message, _x, _y);

	const RECT rect[HELP_MAX] =
	{
		{0, 0, 0, 0},			//default
		{0, 0, 0, 0},			//back
		{0, 0, 0, 0},			//next
		{337, 170, 418, 193},	//name
		{0, 0, 0, 0},			//check
		{346, 218, 409, 295},	//tribe
		{346, 310, 409, 360},	//gender
		{281, 385, 405, 416},	//haircolor
		{455, 385, 579, 416},	//skincolor
		{456, 219, 545, 485},	//face type
		{645, 219, 753, 242},		//str
		{645, 246, 753, 269},		//dex
		{645, 273, 753, 296},		//int
		{645, 300, 753, 323},		//hp
		{645, 327, 753, 350},		//mp
		{645, 354, 753, 377},		//defence
		{645, 381, 753, 404},		//protection
		{645, 408, 753, 431},		//tohit
		{645, 435, 753, 458},		//damage
		{0, 0, 0, 0},		//save
		{0, 0, 0, 0},		//load
		{0, 0, 0, 0},		//reroll
		{645, 173, 725, 196},		//bonus

	};

	// control color table
	switch (message)
	{
		case M_MOVING:
			m_focused_help = HELP_DEFAULT;
			{
				for(int i = 0; i < HELP_MAX; i++)
				{
					int gap_x = (g_pUserInformation->iResolution_x - 800) / 2;
					int gap_y = (g_pUserInformation->iResolution_y - 600) / 2;
					
					
					if(_x > rect[i].left+gap_x && _x < rect[i].right+gap_x && _y > rect[i].top+gap_y && _y < rect[i].bottom+gap_y)
					{
						m_focused_help = i;
						break;
					}
				}
			}
			if(m_focused_help == HELP_BONUS && m_p_slot->Race != RACE_OUSTERS)
				m_focused_help = HELP_DEFAULT;

			if (m_bl_pushed_table)
				ChangeColor(_x, _y);

			if(m_p_slot != NULL)
			{
				MouseSelectMale_OR_Female_RollOver(_x, _y);
				MouseSelectFace_RollOver(_x, _y);
				MouseSelectStet_RollOver(_x, _y);
			}
		
			break;

		case M_LEFTBUTTON_DOWN:
//		case M_LB_DOUBLECLICK:
/*#ifdef CONVERT_1024_768
			if (ChangeColor(_x-112, _y-84) == true)
#else*/
			if (ChangeColor(_x, _y) == true)
//#endif			
			{
				m_bl_pushed_table = true;
				return true;
			}

			if(m_p_slot != NULL)
			{
				MouseSelectMale_OR_Female_Click(_x, _y);
				MouseSelectFace_Click(_x, _y);
				MouseSelectStet_Click(_x, _y);
			}

			break;

		case M_LEFTBUTTON_UP:
			m_bl_pushed_table = false;
			break;
	}

	return true;
}

//-----------------------------------------------------------------------------
// ShowCharacter
//
// (x, y)¿¡ ³²/¿© Ä³¸¯ÅÍ ÇÏ³ª¸¦ Ãâ·ÂÇÑ´Ù. µû¶ó¼­ ¾î´À ÇÏ³ª´Â null·Î µÇ¾ß ÇÏ´Ù.
//
// »ìºÎºÐ : i1
// ¿ÊºÎºÐ : i2
//-----------------------------------------------------------------------------
void	C_VS_UI_NEWCHAR::ShowCharacter(int _x, int _y, S_SLOT * p_slot, int index, int enable, int dark)
{
	//
	// Ãâ·Â¼ø¼­
	//
	// ¹ÙÁö -> »óÀÇ -> ¸Ó¸®Ä«¶ô -> Åõ±¸ -> ¿À¸¥¼ÕÀåÂø -> ¿Þ¼ÕÀåÂø
	//
	if (gpC_base->m_p_DDSurface_back->Lock())
	{
		switch(p_slot->Race)
		{
		case RACE_OUSTERS:
			if( p_slot->m_AdvancementLevel > 0 )
				_ShowCharacterACOusters( _x, _y, p_slot, index, enable, dark );
			else
				_ShowCharacterOusters( _x, _y, p_slot, index, enable, dark );
			break;
			
		case RACE_VAMPIRE:
			if( p_slot->m_AdvancementLevel > 0 )
				_ShowCharacterACVampire( _x, _y, p_slot, index, enable, dark );
			else
				_ShowCharacterVampire( _x, _y, p_slot, index, enable, dark );
			break;
			
		case RACE_SLAYER:
			if( p_slot->m_AdvancementLevel > 0 )
				_ShowCharacterACSlayer( _x, _y, p_slot, index, enable, dark );
			else
				_ShowCharacterSlayer( _x, _y, p_slot, index, enable, dark );
			break;
		}
		gpC_base->m_p_DDSurface_back->Unlock();
	}
}

//-----------------------------------------------------------------------------
// DrawCover
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_NEWCHAR::DrawCover(int _x, int _y)
{
}



void	C_VS_UI_NEWCHAR::DrawCharFaceSelect()
{
	switch( m_p_slot->Race )
	{
		case RACE_SLAYER:
			if(m_p_slot->bl_female	== false)
			{
				m_image_spk.BltLocked(m_ptFace[SELECT_LEFT_FACE].x,		m_ptFace[SELECT_LEFT_FACE].y, CHAR_FACE_SLAYER_MALE_SELECT_1);
				m_image_spk.BltLocked(m_ptFace[SELECT_CENTER_FACE].x,	m_ptFace[SELECT_CENTER_FACE].y, CHAR_FACE_SLAYER_MALE_SELECT_2);
				m_image_spk.BltLocked(m_ptFace[SELECT_RIGHT_FACE].x,	m_ptFace[SELECT_RIGHT_FACE].y, CHAR_FACE_SLAYER_MALE_SELECT_3);
			}
			else
			{
				m_image_spk.BltLocked(m_ptFace[SELECT_LEFT_FACE].x,		m_ptFace[SELECT_LEFT_FACE].y, CHAR_FACE_SLAYER_FEMALE_SELECT_1);
				m_image_spk.BltLocked(m_ptFace[SELECT_CENTER_FACE].x,	m_ptFace[SELECT_CENTER_FACE].y, CHAR_FACE_SLAYER_FEMALE_SELECT_2);
				m_image_spk.BltLocked(m_ptFace[SELECT_RIGHT_FACE].x,	m_ptFace[SELECT_RIGHT_FACE].y, CHAR_FACE_SLAYER_FEMALE_SELECT_3);
			}

			m_image_spk.BltLocked(m_ptFace_Radio[m_btSelect_Face].x,	m_ptFace_Radio[m_btSelect_Face].y, RADIO_SELECT_BUTTON);
			m_image_spk.BltLockedAlpha(m_ptFace_Radio[m_btVirtureSelect_Face].x,	m_ptFace_Radio[m_btVirtureSelect_Face].y, 
										RADIO_SELECT_BUTTON, m_wFace_Alpha);

			switch(m_btVirtureSelect_Face)
			{
			case SELECT_LEFT_FACE:
				m_wFace_Alpha++;
					if(m_wFace_Alpha >= 31)
						m_wFace_Alpha	= 0;
				break;

			case SELECT_CENTER_FACE:
				m_wFace_Alpha++;
					if(m_wFace_Alpha >= 31)
						m_wFace_Alpha	= 0;
				break;
				
			case SELECT_RIGHT_FACE:
				m_wFace_Alpha++;
					if(m_wFace_Alpha >= 31)
						m_wFace_Alpha	= 0;
				break;
			default:
				m_wFace_Alpha	= 0;
				break;
			}

			break;

		case RACE_VAMPIRE:
			if(m_p_slot->bl_female	== false)
			{
				m_image_spk.BltLocked(m_ptFace[SELECT_LEFT_FACE].x,		m_ptFace[SELECT_LEFT_FACE].y, CHAR_FACE_VAMPIRE_MALE_SELECT);
				m_image_spk.BltLocked(m_ptFace_Radio[SELECT_LEFT_FACE].x,	m_ptFace_Radio[SELECT_LEFT_FACE].y, RADIO_SELECT_BUTTON);
			}
			else
			{
				m_image_spk.BltLocked(m_ptFace[SELECT_LEFT_FACE].x,		m_ptFace[SELECT_LEFT_FACE].y, CHAR_FACE_VAMPIRE_FEMALE_SELECT);
				m_image_spk.BltLocked(m_ptFace_Radio[SELECT_LEFT_FACE].x,	m_ptFace_Radio[SELECT_LEFT_FACE].y, RADIO_SELECT_BUTTON);
			}
			break;

		case RACE_OUSTERS:	//¾Æ¿ì½ºÅÍÁî´Â ¼ºº°ÀÌ ¾ø´Ù.
			m_image_spk.BltLocked(m_ptFace[SELECT_LEFT_FACE].x,		m_ptFace[SELECT_LEFT_FACE].y, CHAR_FACE_OUSTERS_SELECT);
			m_image_spk.BltLocked(m_ptFace_Radio[SELECT_LEFT_FACE].x,	m_ptFace_Radio[SELECT_LEFT_FACE].y, RADIO_SELECT_BUTTON);
			break;
	}

}




void	C_VS_UI_NEWCHAR::ChangeEffectPoint()
{
	POINT	ptEffect;
	ptEffect.x	= 	m_wEffect_Fire_Left1_X;
	ptEffect.y	=	m_wEffect_Fire_Left1_Y;
	g_pTopView->SetTitleEffectPos(&ptEffect, EFFECT_INDEX_FIRE_LEFT1);

	ptEffect.x	= 	m_wEffect_Fire_Left2_X;
	ptEffect.y	=	m_wEffect_Fire_Left2_Y;
	g_pTopView->SetTitleEffectPos(&ptEffect, EFFECT_INDEX_FIRE_LEFT2);

	ptEffect.x	= 	m_wEffect_Fire_Right1_X;
	ptEffect.y	=	m_wEffect_Fire_Right1_Y;
	g_pTopView->SetTitleEffectPos(&ptEffect, EFFECT_INDEX_FIRE_RIGHT1);

	ptEffect.x	= 	m_wEffect_Fire_Right2_X;
	ptEffect.y	=	m_wEffect_Fire_Right2_Y;
	g_pTopView->SetTitleEffectPos(&ptEffect, EFFECT_INDEX_FIRE_RIGHT2);

	ptEffect.x	= 	m_wEffect_Fire_Center_X;
	ptEffect.y	=	m_wEffect_Fire_Center_Y;
	g_pTopView->SetTitleEffectPos(&ptEffect, EFFECT_INDEX_FIRE_CENTER);
}





void	C_VS_UI_NEWCHAR::DrawSelect_Race()
{
//	m_image_spk.BltLocked(m_ptRaceSelect_Radio[m_btRace_Select].x, m_ptRaceSelect_Radio[m_btRace_Select].y, RADIO_SELECT_BUTTON);	//Á¾Á· ¼±ÅÃ ¹öÆ°
//
//#if !__CONTENTS(__RACE_OUSTERS)
//	m_image_spk.BltLocked(m_wHide_Ousters_Selection_Button_X, m_wHide_Ousters_Selection_Button_Y, HIDE_OUSTERS_SELECTION_BUTTON);
//#endif
//	switch(m_p_slot->Race)		// Á¾Á· ¼±ÅÃ ¹öÆ°
//	{
//	case RACE_SLAYER:
//		m_image_spk.BltLocked(m_wSelect_Race_Slayer_Button_X, m_wSelect_Race_Slayer_Button_Y,	SELECT_SLAYER_BUTTON);
//		break;
//	case RACE_VAMPIRE:
//		m_image_spk.BltLocked(m_wSelect_Race_Vampire_Button_X, m_wSelect_Race_Vampire_Button_Y,	SELECT_VAMPIRE_BUTTON);
//		break;
//	case RACE_OUSTERS:
//		m_image_spk.BltLocked(m_wSelect_Race_Ousters_Button_X, m_wSelect_Race_Ousters_Button_Y,	SELECT_OUSTERS_BUTTON);
//		break;
//	}
	m_image_hays_spk.BltLocked(m_wNewCharBox_X+280, m_wNewCharBox_Y, SKIN_WINDOW);
}





void	C_VS_UI_NEWCHAR::DrawSelect_Male_OR_Female()
{
	//m_image_spk.BltLocked(m_wMale_OR_Female_Select_Box_X, m_wMale_OR_Female_Select_Box_Y, MALE_OR_FEMALE_SELECT_BOX);	//¼ºº° ¼±ÅÃ ¹Ú½º
	if(m_p_slot->Race == RACE_SLAYER || m_p_slot->Race == RACE_VAMPIRE)	//¾Æ¿ì½ºÅÍÁî´Â ¼ºº°ÀÌ ¾ø´Ù.
	{
		m_image_hays_spk.BltLocked(m_wMale_OR_Female_Select_Box_X, m_wMale_OR_Female_Select_Box_Y, BK_MILE_FEMAL);
		if(m_p_slot->bl_female	== false)	//¼ºº° ¼±ÅÃ ¹öÆ°
		{
			m_image_hays_spk.BltLocked(m_wMale_Select_Button_X, m_wMale_Select_Button_Y, BTN_CHECK);
			m_image_hays_spk.BltLocked(m_wFemale_Select_Button_X, m_wFemale_Select_Button_Y, BTN_UNCHECK);
		}
		else
		{
			m_image_hays_spk.BltLocked(m_wFemale_Select_Button_X, m_wFemale_Select_Button_Y, BTN_CHECK);
			m_image_hays_spk.BltLocked(m_wMale_Select_Button_X, m_wMale_Select_Button_Y, BTN_UNCHECK);
		}

		//switch(m_btVirtureSelect_Male)		//¼ºº° ¼±ÅÃ ¹öÆ°(¸¶¿ì½º ·Ñ¿À¹ö »óÅÂ¿¡ µû¶ó ´Ù¸§)
		//{
		//case VIRTURE_SELECT_MALE:
		//	m_image_spk.BltLockedAlpha(m_wMale_Select_Radio_X, m_wMale_Select_Radio_Y, RADIO_SELECT_BUTTON, m_wMale_OR_Femail_Select_Radio_Alpha);

		//	m_wMale_OR_Femail_Select_Radio_Alpha++;
		//	if(m_wMale_OR_Femail_Select_Radio_Alpha >= 31)
		//		m_wMale_OR_Femail_Select_Radio_Alpha	= 0;
		//	break;

		//case VIRTURE_SELECT_FEMALE:
		//	m_image_spk.BltLockedAlpha(m_wFemale_Select_Radio_X, m_wFemale_Select_Radio_Y, RADIO_SELECT_BUTTON, m_wMale_OR_Femail_Select_Radio_Alpha);

		//	m_wMale_OR_Femail_Select_Radio_Alpha++;
		//	if(m_wMale_OR_Femail_Select_Radio_Alpha >= 31)
		//		m_wMale_OR_Femail_Select_Radio_Alpha	= 0;
		//	break;
		//		
		//default:
		//	m_wMale_OR_Femail_Select_Radio_Alpha	= 0;
		//	break;
		//}
	}
}




void	C_VS_UI_NEWCHAR::DrawSelect_Stet()
{
	switch(m_p_slot->Race)		// ¾Æ¿ì½ºÅÍÁî, ½½·¹ÀÌ¾î ´É·ÂÄ¡ ¼³Á¤ ÀÌ¹ÌÁö
	{
	case RACE_SLAYER:
		//m_image_spk.BltLocked(m_wOpset_BOX_X, m_wOpset_BOX_Y, OPSET_BOX);
		//m_image_spk.BltLocked(m_wSave_Button_X, m_wSave_Button_Y, SAVE_BUTTON);
		//m_image_spk.BltLocked(m_wLoad_Button_X, m_wLoad_Button_Y, LOAD_BUTTON);
		//m_image_spk.BltLocked(m_wReset_Button_X, m_wReset_Button_Y, RESET_BUTTON);			

		//m_image_spk.BltLockedAlpha(m_wSave_Button_X, m_wSave_Button_Y, SAVE_BUTTON_PUSHED, m_wSave_Button_Alpha);
		//m_image_spk.BltLockedAlpha(m_wLoad_Button_X, m_wLoad_Button_Y, LOAD_BUTTON_PUSHED, m_wLoad_Button_Alpha);
		//m_image_spk.BltLockedAlpha(m_wReset_Button_X, m_wReset_Button_Y, RESET_BUTTON_PUSHED, m_wReset_Button_Alpha);

		m_image_hays_spk.BltLocked(m_wOpset_BOX_X, m_wOpset_BOX_Y, BTN_BLAZE_NORMAL);
		m_image_hays_spk.BltLocked(m_wOpset_BOX_X+30, m_wOpset_BOX_Y, BTN_SWORD_NORMAL);
		m_image_hays_spk.BltLocked(m_wOpset_BOX_X+30*2, m_wOpset_BOX_Y, BTN_GUN_NORMAL);
		m_image_hays_spk.BltLocked(m_wOpset_BOX_X+30*3, m_wOpset_BOX_Y, BTN_HEAL_NORMAL);
		m_image_hays_spk.BltLocked(m_wOpset_BOX_X+30*4, m_wOpset_BOX_Y, BTN_ENCHANT_NORMAL);
		break;

	case RACE_OUSTERS:
		m_image_hays_spk.BltLocked(m_wStet_Box_X-30, m_wStet_Box_Y, BK_BLACK);
		for(int i = 0; i < STET_MAX; i++)
		{
			m_image_hays_spk.BltLocked(m_ptStet_Plus[i].x, m_ptStet_Plus[i].y, BTN_ADD_NORMAL);
			m_image_hays_spk.BltLockedAlpha(m_ptStet_Plus[i].x, m_ptStet_Plus[i].y, BTN_ADD_PRESS, m_wStet_Plus_Button_Alpha[i]);

			m_image_hays_spk.BltLocked(m_ptStet_Minus[i].x, m_ptStet_Minus[i].y, BTN_DELETE_NORMAL);
			m_image_hays_spk.BltLockedAlpha(m_ptStet_Minus[i].x, m_ptStet_Minus[i].y, BTN_DELETE_PRESS, m_wStet_Minus_Button_Alpha[i]);
		}
		break;
	}
}




void	C_VS_UI_NEWCHAR::DrawSelect_Hair_Skin_Color()
{
	//m_image_spk.BltLocked(m_wHairColor_BOX_X, m_wHairColor_BOX_Y, HAIR_COLOR_BOX);
	//m_image_spk.BltLocked(m_wSkinColor_BOX_X, m_wSkinColor_BOX_Y, SKIN_COLOR_BOX);

	int i, j;
	S_SURFACEINFO	surfaceinfo;
	SetSurfaceInfo(&surfaceinfo, gpC_base->m_p_DDSurface_back->GetDDSD());

	Rect color_unit_rect;

	color_unit_rect.WH(COLOR_UNIT_X, COLOR_UNIT_Y);

		// hair
	if(m_p_slot->Race != RACE_VAMPIRE)
	{
		for (j=0; j < COLOR_LIST_Y; j++)
		{
			for (i=0; i < COLOR_LIST_X; i++)
			{
				color_unit_rect.XY(COLOR_UNIT_X*i+m_wHairColor_Start_X, m_wHairColor_Start_Y+COLOR_UNIT_Y*j);
				FillRect(&surfaceinfo, &color_unit_rect, GetColor(i, j, false));
			}
		}	
				// show select mark
		color_unit_rect.XY(m_hair_point.x*COLOR_UNIT_X+m_wHairColor_Start_X, m_wHairColor_Start_Y+m_hair_point.y*COLOR_UNIT_Y);
		rectangle(&surfaceinfo, &color_unit_rect, ga_blink_color_table[g_blink_value]);
	}
	else
	{
		m_p_slot->hair_color = 377;
	}

	if(m_p_slot->Race != RACE_OUSTERS)
	{
			// body
		for (j=0; j < COLOR_LIST_Y; j++)
			for (i=0; i < COLOR_LIST_X; i++)
			{
				color_unit_rect.XY(COLOR_UNIT_X*i+m_wSkinColor_Start_X, m_wSkinColor_Start_Y+COLOR_UNIT_Y*j);
				FillRect(&surfaceinfo, &color_unit_rect, GetColor(i, j, true));
			}

			// show select mark
		color_unit_rect.XY(m_skin_point.x*COLOR_UNIT_X+m_wSkinColor_Start_X, m_wSkinColor_Start_Y+m_skin_point.y*COLOR_UNIT_Y);
		rectangle(&surfaceinfo, &color_unit_rect, ga_blink_color_table[g_blink_value]);
	}
	else
	{
		m_p_slot->skin_color = 377;
	}	
}



void C_VS_UI_NEWCHAR::DrawStetText()
{
	char str[255];
	sprintf(str, "Á¦Á¿£º");
	g_Print(m_wSTR_Text_X-30, m_wSTR_Text_Y, str, &gpC_base->m_value_pi);
	sprintf(str, "Ãô½Ý£º");
	g_Print(m_wSTR_Text_X-30, m_wDEX_Text_Y, str, &gpC_base->m_value_pi);
	sprintf(str, "ÖªÊ¶£º");
	g_Print(m_wSTR_Text_X-30, m_wINT_Text_Y, str, &gpC_base->m_value_pi);
	sprintf(str, "ÉúÃü£º");
	g_Print(m_wSTR_Text_X-30, m_wHP_Text_Y, str, &gpC_base->m_value_pi);
	sprintf(str, "Ä§Á¦£º");
	g_Print(m_wSTR_Text_X-30, m_wMP_Text_Y, str, &gpC_base->m_value_pi);
	sprintf(str, "»Ø±Ü£º");
	g_Print(m_wSTR_Text_X-30, m_wDEFENSE_Text_Y, str, &gpC_base->m_value_pi);
	sprintf(str, "·ÀÓù£º");
	g_Print(m_wSTR_Text_X-30, m_wPROTECTION_Text_Y, str, &gpC_base->m_value_pi);
	sprintf(str, "ÃüÖÐ£º");
	g_Print(m_wSTR_Text_X-30, m_wTOHIT_Text_Y, str, &gpC_base->m_value_pi);
	sprintf(str, "ÉËº¦£º");
	g_Print(m_wSTR_Text_X-30, m_wDAM_Text_Y, str, &gpC_base->m_value_pi);

	sprintf(str, "%d", m_p_slot->STR_PURE);
	g_Print(m_wSTR_Text_X, m_wSTR_Text_Y, str, &gpC_base->m_value_pi);
	sprintf(str, "%d", m_p_slot->DEX_PURE);
	g_Print(m_wDEX_Text_X, m_wDEX_Text_Y, str, &gpC_base->m_value_pi);
	sprintf(str, "%d", m_p_slot->INT_PURE);
	g_Print(m_wINT_Text_X, m_wINT_Text_Y, str, &gpC_base->m_value_pi);
	sprintf(str, "%d", m_p_slot->HP);
	g_Print(m_wHP_Text_X, m_wHP_Text_Y, str, &gpC_base->m_value_pi);
	sprintf(str, "%d", m_p_slot->MP);
	g_Print(m_wMP_Text_X, m_wMP_Text_Y, str, &gpC_base->m_value_pi);
	sprintf(str, "%d", m_p_slot->DEFENSE);
	g_Print(m_wDEFENSE_Text_X, m_wDEFENSE_Text_Y, str, &gpC_base->m_value_pi);
	sprintf(str, "%d", m_p_slot->PROTECTION);
	g_Print(m_wPROTECTION_Text_X, m_wPROTECTION_Text_Y, str, &gpC_base->m_value_pi);
	sprintf(str, "%d", m_p_slot->TOHIT);
	g_Print(m_wTOHIT_Text_X, m_wTOHIT_Text_Y, str, &gpC_base->m_value_pi);
	sprintf(str, "%d~%d", m_p_slot->DAM, m_p_slot->DAM2);
	g_Print(m_wDAM_Text_X, m_wDAM_Text_Y, str, &gpC_base->m_value_pi);
	if(m_p_slot->Race == RACE_OUSTERS)
	{
		sprintf(str, "Ê£ÓàÊôÐÔµã£º");
		g_Print(m_wDAM_Text_X+5, m_wBonus_Text_Y, str, &gpC_base->m_value_pi);

		sprintf(str, "%d", m_p_slot->bonus_point);
		g_Print(m_wBonus_Text_X+18, m_wBonus_Text_Y, str, &gpC_base->m_value_pi);
	}
	if(m_p_slot->Race == RACE_SLAYER)
	{
		  if(m_selected_job == 0)
		  {
			  sprintf(str,"µ±Ç°Ñ¡ÔñÖ°Òµ£ºµ¶ÊÖ");
			  g_Print(m_wOpset_BOX_X+125, m_wOpset_BOX_Y-18, str, &gpC_base->m_value_pi);
		  }
		  if(m_selected_job == 1)
		  {
			  sprintf(str,"µ±Ç°Ñ¡ÔñÖ°Òµ£º½£¿Í");
			  g_Print(m_wOpset_BOX_X+125, m_wOpset_BOX_Y-18, str, &gpC_base->m_value_pi);
		  }
		  if(m_selected_job == 2)
		  {
			  sprintf(str,"µ±Ç°Ñ¡ÔñÖ°Òµ£º¾üÈË");
			  g_Print(m_wOpset_BOX_X+125, m_wOpset_BOX_Y-18, str, &gpC_base->m_value_pi);
		  }
		  if(m_selected_job == 3)
		  {
			  sprintf(str,"µ±Ç°Ñ¡ÔñÖ°Òµ£ºÒ½Éú");
			  g_Print(m_wOpset_BOX_X+125, m_wOpset_BOX_Y-18, str, &gpC_base->m_value_pi);
		  }
		  if(m_selected_job == 4)
		  {
			  sprintf(str,"µ±Ç°Ñ¡ÔñÖ°Òµ£º×£¸£");
			  g_Print(m_wOpset_BOX_X+125, m_wOpset_BOX_Y-18, str, &gpC_base->m_value_pi);
		  }
		  sprintf(str,"µ¶ÊÖ");
		  g_Print(m_wOpset_BOX_X+30, m_wOpset_BOX_Y+30, str, &gpC_base->m_value_pi);
		  sprintf(str,"½£¿Í");
		  g_Print(m_wOpset_BOX_X+30*2, m_wOpset_BOX_Y+30, str, &gpC_base->m_value_pi);
		  sprintf(str,"¾üÈË");
		  g_Print(m_wOpset_BOX_X+30*3, m_wOpset_BOX_Y+30, str, &gpC_base->m_value_pi);
		  sprintf(str,"Ò½Éú");
		  g_Print(m_wOpset_BOX_X+30*4, m_wOpset_BOX_Y+30, str, &gpC_base->m_value_pi);
		  sprintf(str,"×£¸£");
		  g_Print(m_wOpset_BOX_X+30*5, m_wOpset_BOX_Y+30, str, &gpC_base->m_value_pi);
	}
	if(m_show_skin == true)
	{
		sprintf(str,"Í··¢ÑÕÉ«");
		g_Print(m_wHairColor_Start_X+90, m_wHairColor_Start_Y-20, str, &gpC_base->m_value_pi);
		sprintf(str,"Æ¤·ôÑÕÉ«");
		g_Print(m_wSkinColor_Start_X+90, m_wSkinColor_Start_Y-20, str, &gpC_base->m_value_pi);
	}
}



//-----------------------------------------------------------------------------
// Show
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_NEWCHAR::Show()
{

	if(m_p_slot	== NULL)
		return;

	Init_TitleUIInterface_InfInfo();
//	ChangeEffectPoint();

	gpC_base->m_p_DDSurface_back->FillSurface(0);

	int convx = (g_pUserInformation->iResolution_x - 800) / 2;
	int convy = (g_pUserInformation->iResolution_y - 600) / 2;
	bool bHighResolution = g_pUserInformation->iResolution_x > 800;
	

	//draw background
	if(gpC_base->m_p_DDSurface_back->Lock())
	{
		if(bHighResolution)
		{
			if( g_pUserInformation->iResolution_x <= 1024 )
			{
				m_image_hays_spk.BltLocked( (g_pUserInformation->iResolution_x - m_image_hays_spk.GetWidth(BK_1024_768)) / 2, 
				(g_pUserInformation->iResolution_y - m_image_hays_spk.GetHeight(BK_1024_768)) / 2, BK_1024_768);
				m_iCurBackPicID = BK_1024_768;
			}
			else
			{
				if( g_pUserInformation->iResolution_y < 960 )
				{
					m_image_hays_spk.BltLocked( (g_pUserInformation->iResolution_x - m_image_hays_spk.GetWidth(BK_1280_960)) / 2, 
					(g_pUserInformation->iResolution_y - m_image_hays_spk.GetHeight(BK_1280_960)) / 2, BK_1280_960);
					m_iCurBackPicID = BK_1280_960;
				}
				else
				{
					m_image_hays_spk.BltLocked( (g_pUserInformation->iResolution_x - m_image_hays_spk.GetWidth(BK_1280_1024)) / 2, 
					(g_pUserInformation->iResolution_y - m_image_hays_spk.GetHeight(BK_1280_1024)) / 2, BK_1280_1024);
					m_iCurBackPicID = BK_1280_1024;
				}
			}
		}
		else
		{
			m_image_hays_spk.BltLocked( (g_pUserInformation->iResolution_x - m_image_hays_spk.GetWidth(BK_800_600)) / 2, 
				(g_pUserInformation->iResolution_y - m_image_hays_spk.GetHeight(BK_800_600)) / 2, BK_800_600);
			m_iCurBackPicID = BK_800_600;
		}
		
		m_image_hays_spk.BltLocked(m_wNewCharBox_X, m_wNewCharBox_Y, BK_PANEL);

		m_image_hays_spk.BltLocked(0, 0, 30);

		gpC_base->m_p_DDSurface_back->Unlock();
	}
	
	//draw character
	ShowCharacter(m_wCharView_X, m_wCharView_Y, m_p_slot, g_char_index, false);

	if(gpC_base->m_p_DDSurface_back->Lock())
	{
		//DrawCharFaceSelect();
		if(m_show_skin == true)
		{
		  DrawSelect_Race();
		  DrawSelect_Hair_Skin_Color();
		}
		//DrawSelect_Race();
		DrawSelect_Male_OR_Female();
		
		DrawSelect_Stet();

		m_pC_button_group->Show();

		gpC_base->m_p_DDSurface_back->Unlock();
	}

	//g_pTopView->DrawTitleEffect(EFFECT_INDEX_FIRE_LEFT1);
	//g_pTopView->DrawTitleEffect(EFFECT_INDEX_FIRE_LEFT2);
	//g_pTopView->DrawTitleEffect(EFFECT_INDEX_FIRE_RIGHT1);
	//g_pTopView->DrawTitleEffect(EFFECT_INDEX_FIRE_RIGHT2);
	//g_pTopView->DrawTitleEffect(EFFECT_INDEX_FIRE_CENTER);

	g_FL2_GetDC();
	DrawStetText();

	m_pC_button_group->ShowButtonName();

	int iLine = 0;
//	for(int i = 0; i < LINE_MAX; i++)
//	{
////		g_PrintColorStr(m_ptText_Line[i].x, 	m_ptText_Line[i].y,
////						m_arrTextLine[i], gpC_base->m_title_menu_pi, RGB_WHITE);
//#if __CONTENTS(__RACE_OUSTERS)
//		if(i == 1)
//			continue;
//		g_PrintColorStr(m_ptText_Line[iLine].x,		m_ptText_Line[iLine].y,
//						(*g_pGameStringTable)[UI_TITLE_UI_RENEWAL_CREATECHAR_TEXT1 + i].GetString(), gpC_base->m_title_menu_pi, RGB_WHITE);
//		if(iLine < LINE_MAX - 1)
//			iLine++;
//#else
//		if(i == 0 || i == 4)
//			continue;
//		g_PrintColorStr(m_ptText_Line[iLine].x, 	m_ptText_Line[iLine].y,
//						(*g_pGameStringTable)[UI_TITLE_UI_RENEWAL_CREATECHAR_TEXT1 + i].GetString(), gpC_base->m_title_menu_pi, RGB_WHITE);
//		if(iLine < LINE_MAX - 2)
//			iLine++;
//#endif
//	}

	char szBuffer[256]	= {NULL,};

	if (g_LeftPremiumDays == 0xFFFE)
	{
		sprintf( szBuffer, (*g_pGameStringTable)[UI_STRING_MESSAGE_NOT_PREMIUM_USER].GetString() );
	}
	else if (g_LeftPremiumDays == 0xFFFC && g_PayType == 4 )
	{
		sprintf( szBuffer, (*g_pGameStringTable)[UI_STRING_MESSAGE_DEFERRED_PAYMENT_NOTICE].GetString() );
	}
	else if ( g_LeftPremiumDays > 0 && g_PayType == 1)
	{
		if(g_bFamily)
			sprintf( szBuffer, (*g_pGameStringTable)[UI_STRING_MESSAGE_LEFT_FAMILY_DAYS].GetString(), g_LeftPremiumDays );
		else
			sprintf( szBuffer, (*g_pGameStringTable)[UI_STRING_MESSAGE_LEFT_PREMIUM_DAYS].GetString(), g_LeftPremiumDays );
	}
	else if (g_LeftPremiumDays == 0 && g_PayType == 1)
	{
		if(g_bFamily)
			sprintf( szBuffer, (*g_pGameStringTable)[UI_STRING_MESSAGE_EXPIRE_FAMILY_TODAY].GetString() );	
		else
			sprintf( szBuffer, (*g_pGameStringTable)[UI_STRING_MESSAGE_EXPIRE_PREMIUM_SERVICE_TODAY].GetString() );	
	}
	else if ( g_LeftPremiumDays > 0 && g_PayType == 3)
	{
		sprintf( szBuffer, (*g_pGameStringTable)[UI_STRING_MESSAGE_LEFT_PREMIUM_PAYZONE_DAYS].GetString(), g_LeftPremiumDays );
	}
	else if (g_LeftPremiumDays == 0 && g_PayType == 3)
	{
		sprintf( szBuffer, (*g_pGameStringTable)[UI_STRING_MESSAGE_LEFT_PREMIUM_PAYZONE_DAYS].GetString() );	
	}

	int szBufferLen = g_GetStringWidth(szBuffer, gpC_base->m_desc_menu_pi.hfont)/2;

//	if( g_LeftPremiumDays != 0xFFFF )
//	{
//		if(g_pUserInformation->IsResolution1024)
//		{
//			g_PrintColorStr((1024 / 2) - szBufferLen, m_wPrimeum_Use_Day_Txt_Y, szBuffer, gpC_base->m_desc_menu_pi, RGB_WHITE );
//		}
//		else
//		{
//			g_PrintColorStr((800 / 2) - szBufferLen, m_wPrimeum_Use_Day_Txt_Y, szBuffer, gpC_base->m_desc_menu_pi, RGB_WHITE );
//		}
//	}

	Window::ShowWidget();
	g_FL2_ReleaseDC();

	SHOW_WINDOW_ATTR;
}



//-----------------------------------------------------------------------------
// NewCharacterCreateOk
//
// ÀÌ¹Ì slotÀÌ ¼³Á¤µÇ¾î ÀÖÀ¸¹Ç·Î, ¸¶Áö¸·À¸·Î bl_set = true¸¸ ÇØÁØ´Ù.
//-----------------------------------------------------------------------------
void C_VS_UI_CHAR_MANAGER::NewCharacterCreateOk()
{
	assert(m_slot[m_stSelect_Slot].bl_set == false);

	m_slot[m_stSelect_Slot].bl_set = true;
//	m_slot[m_select_heart_temp].bl_vampire = false;

	// init etc value
//	m_slot[m_select_heart_temp].CC = 0;
	m_slot[m_stSelect_Slot].FAME = 1234567890;
//	m_slot[m_select_heart_temp].NOTERITY = 0;
	m_slot[m_stSelect_Slot].level = 1;

	SelectSlot(m_stSelect_Slot);

	Start(true);
//	m_pC_newchar->Finish();

}

//-----------------------------------------------------------------------------
// NewCharacterCreateFailed
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_CHAR_MANAGER::NewCharacterCreateFailed(int error)
{
	g_msg_character_create_failed->Start();
}

//-----------------------------------------------------------------------------
// SetCharacter
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_CHAR_MANAGER::SetCharacter(int slot, S_SLOT &S_slot)
{
	if (slot >= 0 && slot < SLOT)
	{
		if (S_slot.sz_name.c_str() == NULL)
			_ErrorStr("Null Character name entered.");

		m_slot[slot] = S_slot;
		m_slot[slot].bl_set = true;
	
		m_slot[slot].sz_name = S_slot.sz_name;

		m_pC_button_group->Delete(m_pC_button_create_char[slot]);
		

		// by sigi
		if (S_slot.sz_guild_name.c_str()!=NULL)
		{
			m_slot[slot].sz_guild_name = S_slot.sz_guild_name;
		}

		if(m_stSelect_Slot == NOT_SELECTED)
			for (int i=0; i < SLOT; i++)
				if (SelectSlot(i))
					break;

		AddCharInfoString(slot);
	}
}

void	C_VS_UI_CHAR_MANAGER::PopupNetmarbleAgreementMessage()
{
	if( m_pC_NetmarbleAgreement != NULL)
	{
		m_pC_NetmarbleAgreement->Start();
	}
}

//-----------------------------------------------------------------------------
// ClearAllCharacter
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_CHAR_MANAGER::ClearAllCharacter()
{
	m_slot[SLOT_LEFT].bl_set = false;
	m_slot[SLOT_CENTER].bl_set = false;
	m_slot[SLOT_RIGHT].bl_set = false;
}

//-----------------------------------------------------------------------------
// DeleteCharacter
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_CHAR_MANAGER::DeleteCharacter(int slot)
{
	assert(m_slot[slot].bl_set == true);
	assert(m_slot[slot].sz_name.c_str() != NULL);

	m_slot[slot].bl_set = false;
	m_slot[slot].sz_name.clear();
	m_slot[slot].sz_name.resize(0);
//	DeleteNewArray(m_slot[slot].sz_name);

	DeleteNew(m_pC_char_delete);

	//20070628Ä³¸¯ÅÍ¸¦ Áö¿ì¸é ¸¸µé±â ¹öÆ°À» ¸¸µç´Ù.
	m_pC_button_group->Delete(m_pC_button_create_char[slot]);
	DeleteNew(m_pC_button_create_char[slot]);

	// search new character for selection
	m_stSelect_Slot = NOT_SELECTED;
	for (int i=0; i < SLOT; i++)
		if (SelectSlot(i))
			break;

	g_msg_char_delete_completed->Start();
//	g_msg_char_delete_completed->AttrKeyboardControl(true);
}

//-----------------------------------------------------------------------------
// Process
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_CHAR_MANAGER::Process()
{
	m_pC_button_group->Process();
}

//-----------------------------------------------------------------------------
// Start
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_CHAR_MANAGER::Start(bool back)
{
	PI_Processor::Start();
	m_pC_newchar->Finish();

	g_pTopView->DeleteTitleEffect();
	DeleteCharInfoString();

	if(!back)
	{
		m_slot[SLOT_LEFT].bl_set	= false;
		m_slot[SLOT_CENTER].bl_set = false;
		m_slot[SLOT_RIGHT].bl_set	= false;
		
		m_stSelect_Slot	= NOT_SELECTED;
	}
	gpC_window_manager->AppearWindow(this);
	m_pC_button_group->Init();

	gbl_wood_skin = false;
//	gbl_vampire_interface = false;

	g_eRaceInterface = RACE_SLAYER;

	// change skin data
	gpC_global_resource->FreeAssemble();
	gpC_global_resource->LoadAssemble();

	LoadDesc("character.txt", 30, 14, false);

	//POINT	ptEffect;
	//ptEffect.x	= 	m_wEffect_Fire_Left1_X;
	//ptEffect.y	=	m_wEffect_Fire_Left1_Y;
	//g_pTopView->AddTitleEffect(&ptEffect, EFFECTSPRITETYPE_CHAR_MANAGER_LEFT_FIRE_1, 2, EFFECT_INDEX_FIRE_LEFT1);

	//ptEffect.x	= 	m_wEffect_Fire_Left2_X;
	//ptEffect.y	=	m_wEffect_Fire_Left2_Y;
	//g_pTopView->AddTitleEffect(&ptEffect, EFFECTSPRITETYPE_CHAR_MANAGER_LEFT_FIRE_2, 2, EFFECT_INDEX_FIRE_LEFT2);

	//ptEffect.x	= 	m_wEffect_Fire_Right1_X;
	//ptEffect.y	=	m_wEffect_Fire_Right1_Y;
	//g_pTopView->AddTitleEffect(&ptEffect, EFFECTSPRITETYPE_CHAR_MANAGER_RIGHT_FIRE_1, 2, EFFECT_INDEX_FIRE_RIGHT1);

	//ptEffect.x	= 	m_wEffect_Fire_Right2_X;
	//ptEffect.y	=	m_wEffect_Fire_Right2_Y;
	//g_pTopView->AddTitleEffect(&ptEffect, EFFECTSPRITETYPE_CHAR_MANAGER_RIGHT_FIRE_2, 2, EFFECT_INDEX_FIRE_RIGHT2);

	//ptEffect.x	= 	m_wEffect_Fire_Center_X;
	//ptEffect.y	=	m_wEffect_Fire_Center_Y;
	//g_pTopView->AddTitleEffect(&ptEffect, EFFECTSPRITETYPE_CHAR_MANAGER_CENTER_FIRE, 2, EFFECT_INDEX_FIRE_CENTER);

	//for(int i = 0; i < SLOT; i++)
	//{
	//	g_pTopView->AddTitleEffect(&m_ptEffect_Char_Attach_UP[i], EFFECTSPRITETYPE_CHAR_MANAGER_CHAR_ATTACH_UP,			2, EFFECT_INDEX_CHAR_ATTACH_UP + (SLOT*i));
	//	g_pTopView->AddTitleEffect(&m_ptEffect_Char_Attach_DOWN[i], EFFECTSPRITETYPE_CHAR_MANAGER_CHAR_ATTACH_DOWN ,	2, EFFECT_INDEX_CHAR_ATTACH_DOWN + (SLOT*i));
	//	g_pTopView->AddTitleEffect(&m_ptEffect_Char_Select[i], EFFECTSPRITETYPE_CHAR_MANAGER_CHAR_SELECT,				2, EFFECT_INDEX_CHAR_SELECT + (SLOT*i));
	//}
	
	EMPTY_MOVE;
}

//-----------------------------------------------------------------------------
// Finish
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_CHAR_MANAGER::Finish()
{
	PI_Processor::Finish();

	gpC_window_manager->DisappearWindow(this);
}

/*-----------------------------------------------------------------------------
- C_VS_UI_CHAR_MANAGER
-
-----------------------------------------------------------------------------*/
C_VS_UI_CHAR_MANAGER::C_VS_UI_CHAR_MANAGER()
{
	g_RegisterWindow(this);

	AttrKeyboardControl(true);

	Init_TitleUIInterface_InfInfo();



	m_pC_newchar = new C_VS_UI_NEWCHAR;
//	m_pC_char_info = NULL;
	m_pC_char_delete = NULL;
	m_pC_biling = NULL;
	
	m_pC_button_create_char[SLOT_LEFT] = NULL;
	m_pC_button_create_char[SLOT_CENTER] = NULL;
	m_pC_button_create_char[SLOT_RIGHT] = NULL;

	m_pAnimationTimer = new CTickTimer;
	m_pAnimationTimer->StartTimer(50, true);
	m_aniArpha = 31;
	m_bAniArphaUp = false;


	//m_common_spk.Open(SPK_COMMON);
	//m_image_spk.Open(SPK_CHAR_MANAGER);
	
	bool bHighResolution = g_pUserInformation->iResolution_x > 800;
	/*
	if(g_pUserInformation->IsResolution1024)
	{
		m_common_spk.Open(SPK_COMMON);
		m_image_spk.Open(SPK_CHAR_MANAGER);
	}
	else
	{
		m_common_spk.Open(SPK_COMMON);
		m_image_spk.Open(SPK_CHAR_MANAGER800);
	}*/

	m_image_spk.Open(SPK_CHAR_MANAGER);


	m_image_hays_0.Open("data\\ui\\spk\\new\\charmanagerrenewal\\00000.spk");
	m_image_hays_1.Open("data\\ui\\spk\\new\\charmanagerrenewal\\00016.spk");
	m_image_hays_2.Open("data\\ui\\spk\\new\\charmanagerrenewal\\00032.spk");


	// ³Ý¸¶ºíÀÌ ¾Æ´Ñ°æ¿ì
	if(g_pUserInformation!=NULL)
	{
		if(!g_pUserInformation->bChinese)
		{
#if __CONTENTS(__USER_GRADE)
			 m_pC_use_grade = new C_SPRITE_PACK(SPK_USE_GRADE);
#endif //__USER_GRADE
		} else 
			m_pC_use_grade = NULL;

		if( true )//g_pUserInformation->IsNetmarble )
		{
			m_pC_NetmarbleAgreement = new C_VS_UI_NETMARBLE_AGREEMENT;
		}
		else m_pC_NetmarbleAgreement = NULL;
	} else
	{
		m_pC_NetmarbleAgreement = NULL;
		m_pC_use_grade = NULL;
	}


	m_pC_button_group = new ButtonGroup(this);

	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_wPrev_Button_X, m_wPrev_Button_Y, 
													m_image_hays_2.GetWidth(BUTTON_YELLOW_NORMAL), m_image_hays_2.GetHeight(BUTTON_YELLOW_NORMAL), 
													BACK_ID, this, BUTTON_YELLOW_NORMAL));

	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_wGameStart_Button_X, m_wGameStart_Button_Y,
													m_image_hays_2.GetWidth(BUTTON_GREEN_NORMAL), m_image_hays_2.GetHeight(BUTTON_GREEN_NORMAL), 
													NEXT_ID, this, BUTTON_GREEN_NORMAL));



	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_wCharCreate_Button_X, m_wCharCreate_Button_Y, 
													m_image_hays_2.GetWidth(BUTTON_BLUE_NORMAL), m_image_hays_2.GetHeight(BUTTON_BLUE_NORMAL), 
													CREATE_ID, this, BUTTON_BLUE_NORMAL));

	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_wCharDelete_Button_X, m_wCharDelete_Button_Y,
													m_image_hays_2.GetWidth(BUTTON_RED_NORMAL), m_image_hays_2.GetHeight(BUTTON_RED_NORMAL), 
													DELETE_ID, this, BUTTON_RED_NORMAL));




	m_w_CharHeight	= 60;
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_ptArrCharSelect_Button[SLOT_LEFT].x, m_ptArrCharSelect_Button[SLOT_LEFT].y, 
													m_image_hays_1.GetWidth(BUTTON_SELROLE_NORMAL), m_image_hays_1.GetHeight(BUTTON_SELROLE_NORMAL), 
													CHAR_SELECT_LEFT_ID, this, BUTTON_SELROLE_NORMAL));

	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_ptArrCharSelect_Button[SLOT_CENTER].x, m_ptArrCharSelect_Button[SLOT_CENTER].y, 
													m_image_hays_1.GetWidth(BUTTON_SELROLE_NORMAL), m_image_hays_1.GetHeight(BUTTON_SELROLE_NORMAL), 
													CHAR_SELECT_CENTER_ID, this, BUTTON_SELROLE_NORMAL));

	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_ptArrCharSelect_Button[SLOT_RIGHT].x, m_ptArrCharSelect_Button[SLOT_RIGHT].y, 
													m_image_hays_1.GetWidth(BUTTON_SELROLE_NORMAL), m_image_hays_1.GetHeight(BUTTON_SELROLE_NORMAL), 
													CHAR_SELECT_RIGHT_ID, this, BUTTON_SELROLE_NORMAL));

/*	for(int i = 0; i < 3; i++)
	{
		if(g_pUserInformation->IsResolution1024)
		{
			m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(x+g_heart_rect[i]+115-112, y+HEART_Y+19-84, m_image_spk.GetWidth(DELETE_BUTTON), m_image_spk.GetHeight(DELETE_BUTTON), DELETE_1_ID+i, this, DELETE_BUTTON));
			m_pC_button_create_char[i] = new C_VS_UI_EVENT_BUTTON(x+g_heart_rect[i]+14-112, y+HEART_Y+204-84, m_image_spk.GetWidth(CREATE_BUTTON), m_image_spk.GetHeight(CREATE_BUTTON), CREATE_1_ID+i, this, CREATE_BUTTON);
			m_pC_button_group->Add(m_pC_button_create_char[i]);
		}
		else
		{
			m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(x+g_heart_rect[i]+115, y+HEART_Y+19, m_image_spk.GetWidth(DELETE_BUTTON), m_image_spk.GetHeight(DELETE_BUTTON), DELETE_1_ID+i, this, DELETE_BUTTON));
			m_pC_button_create_char[i] = new C_VS_UI_EVENT_BUTTON(x+g_heart_rect[i]+14, y+HEART_Y+204, m_image_spk.GetWidth(CREATE_BUTTON), m_image_spk.GetHeight(CREATE_BUTTON), CREATE_1_ID+i, this, CREATE_BUTTON);
			m_pC_button_group->Add(m_pC_button_create_char[i]);
		}
	}
*/
	g_char_update_tid = gC_timer2.Add(ANI_MILLISEC, _Timer_CharUpdate);
	gC_timer2.Continue(g_char_update_tid);

	// ANI_FRAME = 11
	g_char_index = 0;

	m_pack_file.SetRAR(RPK_TITLE, RPK_PASSWORD);

	SetDesc(0, 0, RGB(255, 255, 255), gpC_base->m_chatting_pi);
	m_desc_y_distance = 16;
	m_wSlayerFindHighDomainLevel	= 0;

	m_focused_help = HELP_DEFAULT;

	m_iBackGroundPicID = -1;
}


void	C_VS_UI_CHAR_MANAGER::Init_TitleUIInterface_InfInfo()
{
	char arrstrAppName[255]		= {NULL,};
	char arrstrFileName[255]	= {NULL,};

	GetCurrentDirectory(_MAX_PATH, arrstrFileName);	//ÇöÀç ½ÇÇà ÁßÀÎ ÆÄÀÏÀÇ °æ·Î¸¦ ¾ò´Â´Ù.

	bool bHighResolution = g_pUserInformation->iResolution_x > 800;
	int ConvX = 0;	int ConvY = 0;
	
	if(bHighResolution)
	{
		if(g_pUserInformation->iResolution_x <= 1024)
			strcpy(arrstrAppName,"CHAR_MANAGER_1024_768");
		else
		{	
			// 1280*720
			if(g_pUserInformation->iResolution_y <= 960)
				strcpy(arrstrAppName,"CHAR_MANAGER_1280_960");
			else if ( g_pUserInformation->iResolution_y <= 1024 )
				strcpy(arrstrAppName,"CHAR_MANAGER_1280_1024");
		}
	}
	else
		strcpy(arrstrAppName,"CHAR_MANAGER_800_600");

	
	if(g_pUserInformation->IsNetmarbleLogin)
	{
		if(bHighResolution)
			strcpy(arrstrAppName,"NET_CHAR_MANAGER_1024_768");
		else
			strcpy(arrstrAppName,"NET_CHAR_MANAGER_800_600");
	}

	strcat(arrstrFileName, FILE_INFO_TITLE_UI);

	m_wChar_Info_Angle_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_INFO_ANGLE_X", 0, arrstrFileName);
	m_wChar_Info_Angle_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_INFO_ANGLE_Y", 0, arrstrFileName);

	m_wSlayerChar_Info_Angle_X				= (WORD)GetPrivateProfileInt(arrstrAppName, "SLAYER_CHAR_INFO_ANGLE_X", 0, arrstrFileName);
	m_wSlayerChar_Info_Angle_Y				= (WORD)GetPrivateProfileInt(arrstrAppName, "SLAYER_CHAR_INFO_ANGLE_Y", 0, arrstrFileName);



	m_ptArrChar_Pos[SLOT_LEFT].x			= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_LEFT_X", 0, arrstrFileName);
	m_ptArrChar_Pos[SLOT_LEFT].y			= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_LEFT_Y", 0, arrstrFileName);

	m_ptArrChar_Pos[SLOT_CENTER].x			= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_CENTER_X", 0, arrstrFileName);
	m_ptArrChar_Pos[SLOT_CENTER].y			= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_CENTER_Y", 0, arrstrFileName);

	m_ptArrChar_Pos[SLOT_RIGHT].x			= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_RIGHT_X", 0, arrstrFileName);
	m_ptArrChar_Pos[SLOT_RIGHT].y			= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_RIGHT_Y", 0, arrstrFileName);

	m_ptArrCharSelect_Button[SLOT_LEFT].x	= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_SELECT_LEFT_BUTTON_X", 0, arrstrFileName);
	m_ptArrCharSelect_Button[SLOT_LEFT].y	= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_SELECT_LEFT_BUTTON_Y", 0, arrstrFileName);

	m_ptArrCharSelect_Button[SLOT_CENTER].x	= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_SELECT_CENTER_BUTTON_X", 0, arrstrFileName);
	m_ptArrCharSelect_Button[SLOT_CENTER].y	= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_SELECT_CENTER_BUTTON_Y", 0, arrstrFileName);

	m_ptArrCharSelect_Button[SLOT_RIGHT].x	= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_SELECT_RIGHT_BUTTON_X", 0, arrstrFileName);
	m_ptArrCharSelect_Button[SLOT_RIGHT].y	= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_SELECT_RIGHT_BUTTON_Y", 0, arrstrFileName);

	m_wCharSelect_Button_Size_Width			= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_SELECT_BUTTON_WIDHT", 0, arrstrFileName);
	m_wCharSelect_Button_Size_Height		= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_SELECT_BUTTON_HEIGHT", 0, arrstrFileName);

	m_ptChar_Name_Bar[SLOT_LEFT].x			= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_NAME_BAR_LEFT_X", 0, arrstrFileName);
	m_ptChar_Name_Bar[SLOT_LEFT].y			= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_NAME_BAR_LEFT_Y", 0, arrstrFileName);

	m_ptChar_Name_Bar[SLOT_CENTER].x		= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_NAME_BAR_CENTER_X", 0, arrstrFileName);
	m_ptChar_Name_Bar[SLOT_CENTER].y		= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_NAME_BAR_CENTER_Y", 0, arrstrFileName);

	m_ptChar_Name_Bar[SLOT_RIGHT].x			= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_NAME_BAR_RIGHT_X", 0, arrstrFileName);
	m_ptChar_Name_Bar[SLOT_RIGHT].y			= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_NAME_BAR_RIGHT_Y", 0, arrstrFileName);

	m_ptChar_Name[SLOT_LEFT].x				= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_NAME_LEFT_X", 0, arrstrFileName)	+ m_ptChar_Name_Bar[SLOT_LEFT].x;
	m_ptChar_Name[SLOT_LEFT].y				= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_NAME_LEFT_Y", 0, arrstrFileName)	+ m_ptChar_Name_Bar[SLOT_LEFT].y;
	
	m_ptChar_Name[SLOT_CENTER].x			= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_NAME_CENTER_X", 0, arrstrFileName)+ m_ptChar_Name_Bar[SLOT_CENTER].x;
	m_ptChar_Name[SLOT_CENTER].y			= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_NAME_CENTER_Y", 0, arrstrFileName)+ m_ptChar_Name_Bar[SLOT_CENTER].y;

	m_ptChar_Name[SLOT_RIGHT].x				= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_NAME_RIGHT_X", 0, arrstrFileName)	+ m_ptChar_Name_Bar[SLOT_RIGHT].x;
	m_ptChar_Name[SLOT_RIGHT].y				= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_NAME_RIGHT_Y", 0, arrstrFileName)	+ m_ptChar_Name_Bar[SLOT_RIGHT].y;

	m_wChar_Name_Bar_Width					= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_NAME_BAR_WIDHT", 0, arrstrFileName);
	
	m_wPrev_Button_X						= (WORD)GetPrivateProfileInt(arrstrAppName, "PREVE_BUTTON_X", 0, arrstrFileName);
	m_wPrev_Button_Y						= (WORD)GetPrivateProfileInt(arrstrAppName, "PREVE_BUTTON_Y", 0, arrstrFileName);

	m_wGameStart_Button_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "GAME_START_BUTTON_X", 0, arrstrFileName);
	m_wGameStart_Button_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "GAME_START_BUTTON_Y", 0, arrstrFileName);

	m_wCharCreate_Button_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_CREATE_BUTTON_X", 0, arrstrFileName);
	m_wCharCreate_Button_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_CREATE_BUTTON_Y", 0, arrstrFileName);

	m_wCharDelete_Button_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_DELETE_BUTTON_X", 0, arrstrFileName);
	m_wCharDelete_Button_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_DELETE_BUTTON_Y", 0, arrstrFileName);


	m_wEffect_Fire_Left1_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_FIRE_LEFT1_X", 0, arrstrFileName);
	m_wEffect_Fire_Left1_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_FIRE_LEFT1_Y", 0, arrstrFileName);

	m_wEffect_Fire_Left2_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_FIRE_LEFT2_X", 0, arrstrFileName);
	m_wEffect_Fire_Left2_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_FIRE_LEFT2_Y", 0, arrstrFileName);

	m_wEffect_Fire_Right1_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_FIRE_RIGHT1_X", 0, arrstrFileName);
	m_wEffect_Fire_Right1_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_FIRE_RIGHT1_Y", 0, arrstrFileName);

	m_wEffect_Fire_Right2_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_FIRE_RIGHT2_X", 0, arrstrFileName);
	m_wEffect_Fire_Right2_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_FIRE_RIGHT2_Y", 0, arrstrFileName);

	m_wEffect_Fire_Center_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_FIRE_FIRE_CENTER_X", 0, arrstrFileName);
	m_wEffect_Fire_Center_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_FIRE_FIRE_CENTER_Y", 0, arrstrFileName);

	m_ptEffect_Char_Attach_UP[SLOT_LEFT].x		= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_CHAR_ATTACH_LEFT_UP_X", 0, arrstrFileName);
	m_ptEffect_Char_Attach_UP[SLOT_LEFT].y		= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_CHAR_ATTACH_LEFT_UP_Y", 0, arrstrFileName);

	m_ptEffect_Char_Attach_UP[SLOT_CENTER].x	= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_CHAR_ATTACH_CENTER_UP_X", 0, arrstrFileName);
	m_ptEffect_Char_Attach_UP[SLOT_CENTER].y	= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_CHAR_ATTACH_CENTER_UP_Y", 0, arrstrFileName);

	m_ptEffect_Char_Attach_UP[SLOT_RIGHT].x		= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_CHAR_ATTACH_RIGHT_UP_X", 0, arrstrFileName);
	m_ptEffect_Char_Attach_UP[SLOT_RIGHT].y		= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_CHAR_ATTACH_RIGHT_UP_Y", 0, arrstrFileName);

	m_ptEffect_Char_Attach_DOWN[SLOT_LEFT].x	= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_CHAR_ATTACH_LEFT_DOWN_X", 0, arrstrFileName);
	m_ptEffect_Char_Attach_DOWN[SLOT_LEFT].y	= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_CHAR_ATTACH_LEFT_DOWN_Y", 0, arrstrFileName);

	m_ptEffect_Char_Attach_DOWN[SLOT_CENTER].x	= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_CHAR_ATTACH_CENTER_DOWN_X", 0, arrstrFileName);
	m_ptEffect_Char_Attach_DOWN[SLOT_CENTER].y	= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_CHAR_ATTACH_CENTER_DOWN_Y", 0, arrstrFileName);

	m_ptEffect_Char_Attach_DOWN[SLOT_RIGHT].x	= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_CHAR_ATTACH_RIGHT_DOWN_X", 0, arrstrFileName);
	m_ptEffect_Char_Attach_DOWN[SLOT_RIGHT].y	= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_CHAR_ATTACH_RIGHT_DOWN_Y", 0, arrstrFileName);

	m_ptEffect_Char_Select[SLOT_LEFT].x			= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_CHAR_SELECT_LEFT_X", 0, arrstrFileName);
	m_ptEffect_Char_Select[SLOT_LEFT].y			= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_CHAR_SELECT_LEFT_Y", 0, arrstrFileName);

	m_ptEffect_Char_Select[SLOT_CENTER].x		= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_CHAR_SELECT_CENTER_X", 0, arrstrFileName);
	m_ptEffect_Char_Select[SLOT_CENTER].y		= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_CHAR_SELECT_CENTER_Y", 0, arrstrFileName);

	m_ptEffect_Char_Select[SLOT_RIGHT].x		= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_CHAR_SELECT_RIGHT_X", 0, arrstrFileName);
	m_ptEffect_Char_Select[SLOT_RIGHT].y		= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_CHAR_SELECT_RIGHT_Y", 0, arrstrFileName);

	m_wChild_X									= (WORD)GetPrivateProfileInt(arrstrAppName, "CHILD_X", 0, arrstrFileName);
	m_wChild_Y									= (WORD)GetPrivateProfileInt(arrstrAppName, "CHILD_Y", 0, arrstrFileName);

	m_wAdult_X									= (WORD)GetPrivateProfileInt(arrstrAppName, "ADULT_X", 0, arrstrFileName);
	m_wAdult_Y									= (WORD)GetPrivateProfileInt(arrstrAppName, "ADULT_Y", 0, arrstrFileName);

	m_wViolence_X								= (WORD)GetPrivateProfileInt(arrstrAppName, "VIOLENCE_X", 0, arrstrFileName);
	m_wViolence_Y								= (WORD)GetPrivateProfileInt(arrstrAppName, "VIOLENCE_Y", 0, arrstrFileName);

	m_wFear_X									= (WORD)GetPrivateProfileInt(arrstrAppName, "FEAR_X", 0, arrstrFileName);
	m_wFear_Y									= (WORD)GetPrivateProfileInt(arrstrAppName, "FEAR_Y", 0, arrstrFileName);

	m_wTex_Bar_X								= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_BAR_X", 0, arrstrFileName);
	m_wTex_Bar_Y								= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_BAR_Y", 0, arrstrFileName);
	
	m_wAni_Mark_X								= (WORD)GetPrivateProfileInt(arrstrAppName, "ANI_MARK_X", 0, arrstrFileName);
	m_wAni_Mark_Y								= (WORD)GetPrivateProfileInt(arrstrAppName, "ANI_MARK_Y", 0, arrstrFileName);

	m_ptText_Line[LINE1].x						= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_LINE1_X", 0, arrstrFileName)	+ m_wTex_Bar_X;
	m_ptText_Line[LINE1].y						= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_LINE1_Y", 0, arrstrFileName)	+ m_wTex_Bar_Y;

	m_ptText_Line[LINE2].x						= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_LINE2_X", 0, arrstrFileName)	+ m_wTex_Bar_X;
	m_ptText_Line[LINE2].y						= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_LINE2_Y", 0, arrstrFileName)	+ m_wTex_Bar_Y;

	m_ptText_Line[LINE3].x						= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_LINE3_X", 0, arrstrFileName)	+ m_wTex_Bar_X;
	m_ptText_Line[LINE3].y						= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_LINE3_Y", 0, arrstrFileName)	+ m_wTex_Bar_Y;

	m_wPrimeum_Use_Day_Txt_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "PRIMEUP_USE_DAY_TEXT_X", 0, arrstrFileName);
	m_wPrimeum_Use_Day_Txt_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "PRIMEUP_USE_DAY_TEXT_Y", 0, arrstrFileName);
	
	m_wWorningString_X							= (WORD)GetPrivateProfileInt(arrstrAppName, "WORNIN_STRING_X", 0, arrstrFileName);
	m_wWorningString_Y							= (WORD)GetPrivateProfileInt(arrstrAppName, "WORNIN_STRING_Y", 0, arrstrFileName);

	GetPrivateProfileString(arrstrAppName, "TEXT_LINE1", "", m_arrTextLine[LINE1], sizeof(m_arrTextLine[LINE1]), arrstrFileName);
	GetPrivateProfileString(arrstrAppName, "TEXT_LINE2", "", m_arrTextLine[LINE2], sizeof(m_arrTextLine[LINE2]), arrstrFileName);
	GetPrivateProfileString(arrstrAppName, "TEXT_LINE3", "", m_arrTextLine[LINE3], sizeof(m_arrTextLine[LINE3]), arrstrFileName);


	m_wPanel_X								= (WORD)GetPrivateProfileInt(arrstrAppName, "m_wPanel_X", 0, arrstrFileName);
	m_wPanel_Y								= (WORD)GetPrivateProfileInt(arrstrAppName, "m_wPanel_Y", 0, arrstrFileName);

	m_wListInfo_X							= (WORD)GetPrivateProfileInt(arrstrAppName, "m_wListInfo_X", 0, arrstrFileName);
	m_wListInfo_Y							= (WORD)GetPrivateProfileInt(arrstrAppName, "m_wListInfo_Y", 0, arrstrFileName);


	m_ptArrCharSelect_Button[SLOT_LEFT].x = m_wPanel_X + 24;
	m_ptArrCharSelect_Button[SLOT_LEFT].y = m_wPanel_Y + 84;

	m_ptArrCharSelect_Button[SLOT_CENTER].x = m_wPanel_X + 24;
	m_ptArrCharSelect_Button[SLOT_CENTER].y = m_ptArrCharSelect_Button[SLOT_LEFT].y + 80;

	m_ptArrCharSelect_Button[SLOT_RIGHT].x = m_wPanel_X + 24;
	m_ptArrCharSelect_Button[SLOT_RIGHT].y = m_ptArrCharSelect_Button[SLOT_CENTER].y + 80;

	m_wCharCreate_Button_X = m_wPanel_X + 46;
	m_wCharCreate_Button_Y = m_wPanel_Y + 491;

	m_wCharDelete_Button_X = m_wPanel_X + 191;
	m_wCharDelete_Button_Y = m_wPanel_Y + 491;


	m_wChar_Info_X							=  m_wListInfo_X;
	m_wChar_Info_Y							=  m_wListInfo_Y;

	m_wSlayerChar_Info_X					=  m_wListInfo_X;
	m_wSlayerChar_Info_Y					=  m_wListInfo_Y;

}




void	C_VS_UI_CHAR_MANAGER::AddCharInfoString(int iSlotIndex)
{
	S_CHAR_INFO_STRING	st_Char_Info_String;
	st_Char_Info_String.Release();

	char	str[255];
	char*	grade[20];

	st_Char_Info_String.strName		=	(*g_pGameStringTable)[UI_STRING_MESSAGE_CHAR_MANAGER_NAME].GetString();
	st_Char_Info_String.strName		+=	m_slot[iSlotIndex].sz_name.c_str();

//	int	iLevel[DOMAIN_LEVE_MAX];
//	iLevel[SWORD]	= m_slot[iSlotIndex].DOMAIN_SWORD;
//	iLevel[BLADE]	= m_slot[iSlotIndex].DOMAIN_BLADE;
//	iLevel[GUN]		= m_slot[iSlotIndex].DOMAIN_GUN;
//	iLevel[HEAL]	= m_slot[iSlotIndex].DOMAIN_HEAL;
//	iLevel[ENCHENT]	= m_slot[iSlotIndex].DOMAIN_ENCHANT;
//
//	m_wSlayerFindHighDomainLevel	= 0;
//	for(int i = 1; i < DOMAIN_LEVE_MAX; i++)
//	{
//		if(iLevel[i-1] < iLevel[i])
//		{
//			m_wSlayerFindHighDomainLevel++;
//		}
// 	}

	//bool bHighResolution = g_pUserInformation->iResolution_x > 800;

	//if(bHighResolution)
	//{
	//	if(g_pUserInformation->iResolution_x <= 1024) //1024  768
	//		m_iBackGroundPicID = m_slot[iSlotIndex].Race + SLAYER_1024_768;
	//	else 
	//	{
	//		if(g_pUserInformation->iResolution_y <= 960) //1280  960
	//			m_iBackGroundPicID = m_slot[iSlotIndex].Race + SLAYER_1280_960;
	//		else  //1280  1024
	//			m_iBackGroundPicID = m_slot[iSlotIndex].Race + SLAYER_1280_1024;
	//	}
	//}
	//else		// 800*600
	//{
	//	m_iBackGroundPicID = m_slot[iSlotIndex].Race;
	//}

	if(m_wSlayerFindHighDomainLevel == 0)
	{
		m_wSlayerFindHighDomainLevel	= rand() % DOMAIN_LEVE_MAX;
	}

	st_Char_Info_String.strLevel	=	(*g_pGameStringTable)[UI_STRING_MESSAGE_CHAR_MANAGER_LEVEL].GetString();
	wsprintf(str, "%d", m_slot[iSlotIndex].level);
	st_Char_Info_String.strLevel	+=	str;

	st_Char_Info_String.strStrength	=	(*g_pGameStringTable)[UI_STRING_MESSAGE_CHAR_MANAGER_STR_PURE].GetString();
	wsprintf(str, "%d", m_slot[iSlotIndex].STR_PURE);
	st_Char_Info_String.strStrength	+=	str;

	st_Char_Info_String.strDex	=	(*g_pGameStringTable)[UI_STRING_MESSAGE_CHAR_MANAGER_DEX_PURE].GetString();
	wsprintf(str, "%d", m_slot[iSlotIndex].DEX_PURE);
	st_Char_Info_String.strDex	+=	str;

	st_Char_Info_String.strInt	=	(*g_pGameStringTable)[UI_STRING_MESSAGE_CHAR_MANAGER_INT_PURE].GetString();
	wsprintf(str, "%d", m_slot[iSlotIndex].INT_PURE);
	st_Char_Info_String.strInt	+=	str;

	st_Char_Info_String.strSwordLevel	=	(*g_pGameStringTable)[UI_STRING_MESSAGE_CHAR_MANAGER_SWORD_LEVEL].GetString();
	wsprintf(str, "%d", m_slot[iSlotIndex].DOMAIN_SWORD);
	st_Char_Info_String.strSwordLevel	+=	str;

	st_Char_Info_String.strBladeLevel	=	(*g_pGameStringTable)[UI_STRING_MESSAGE_CHAR_MANAGER_BLADE_LEVEL].GetString();
	wsprintf(str, "%d", m_slot[iSlotIndex].DOMAIN_BLADE);
	st_Char_Info_String.strBladeLevel	+=	str;

	st_Char_Info_String.strGunLevel	=	(*g_pGameStringTable)[UI_STRING_MESSAGE_CHAR_MANAGER_GUN_LEVEL].GetString();
	wsprintf(str, "%d", m_slot[iSlotIndex].DOMAIN_GUN);
	st_Char_Info_String.strGunLevel	+=	str;

	st_Char_Info_String.strHealLevel	=	(*g_pGameStringTable)[UI_STRING_MESSAGE_CHAR_MANAGER_HEAL_LEVEL].GetString();
	wsprintf(str, "%d", m_slot[iSlotIndex].DOMAIN_HEAL);
	st_Char_Info_String.strHealLevel	+=	str;

	st_Char_Info_String.strEnchantLevel	=	(*g_pGameStringTable)[UI_STRING_MESSAGE_CHAR_MANAGER_ENCHANT_LEVEL].GetString();
	wsprintf(str, "%d", m_slot[iSlotIndex].DOMAIN_ENCHANT);
	st_Char_Info_String.strEnchantLevel	+=	str;

	st_Char_Info_String.strFame	=	(*g_pGameStringTable)[UI_STRING_MESSAGE_CHAR_MANAGER_FAME].GetString();
	wsprintf(str, "%d", m_slot[iSlotIndex].FAME);
	st_Char_Info_String.strFame	+=	str;

	const char* sgrade[20] = 
	{
		(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_PIVATE].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_SERENT].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_FEACEL].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_LITENA].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_KAINEL].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_GENEAL].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_FORE_GENEAL].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_MAJORIS_GENEAL].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_CLOEL_GENEAL].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_MARSHAL].GetString(),
		"ÀÇÖ®Á¦Á¿",
		"±ªÖ®Á¦Á¿",
		"ÐÜÖ®Á¦Á¿",
		"»¢Ö®Á¦Á¿",
		"ÐÅÑöÖ®Á¦",
		"Ô­Á¦Ö¸»Ó¹Ù",
		"ÒéÔ±",
		"´ó³¼",
		"Òé³¤",
		"×ÜÀí",
	};

	const char* vgrade[20] = 
	{
		(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_RITTER].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_REICHSRITTER].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_BARONET].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_PREYHER].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_GRAF].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_MARKGRAF].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_PFALZGRAF].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_FURST].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_HERZOG].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_LANDESHER].GetString(),
		"¶þµÈºî¾ô",
		"Ò»µÈºî¾ô",
		"ÁìÖ÷",
		"Ñ¡µÛºî",
		"¹«¾ô",
		"´ó¹«¾ô",
		"Ç×Íõ",
		"´¢¾ý",
		"Ñª»Ê",
		"¿­Èö",
	};

	switch(m_slot[iSlotIndex].Race)
	{
	case RACE_SLAYER:
		memcpy((char*)grade,	(const char*)sgrade, sizeof(sgrade));
	break;

	case RACE_VAMPIRE:
		memcpy((char*)grade,	(const char*)vgrade, sizeof(vgrade));
	break;
	}

	if(m_slot[iSlotIndex].GRADE>0&&m_slot[iSlotIndex].GRADE<=100)
	{
		if(m_slot[iSlotIndex].Race != RACE_OUSTERS)
		{
			st_Char_Info_String.strGrade	=	(*g_pGameStringTable)[UI_STRING_MESSAGE_CHAR_MANAGER_GRADE].GetString();
			wsprintf(str, "%s [%d]",grade[(m_slot[iSlotIndex].GRADE-1)/5],m_slot[iSlotIndex].GRADE);
			st_Char_Info_String.strGrade	+=	str;
		}
	}

	st_Char_Info_String.iSlotIndex	= iSlotIndex;

	std::vector<S_CHAR_INFO_STRING>::iterator it	= m_Char_Info_String.begin();
	bool	blPush	= true;

	for(int i = 0; i < m_Char_Info_String.size(); it++, i++)
	{
		if(it->iSlotIndex	== iSlotIndex)
			blPush	= false;
	}

	if(blPush)
		m_Char_Info_String.push_back(st_Char_Info_String);
}




void	C_VS_UI_CHAR_MANAGER::DeleteCharInfoString()
{
	std::vector<S_CHAR_INFO_STRING>::iterator it = m_Char_Info_String.begin();

	for(int i = 0; i < m_Char_Info_String.size(); it++, i++)
	{
		it->Release();
	}

	m_Char_Info_String.clear();
	m_Char_Info_String.resize(0);	
}
 


void	C_VS_UI_CHAR_MANAGER::DrawCharInfoString()
{
	COLORREF	colFontRgb	= RGB(255,255,255);
	std::vector<S_CHAR_INFO_STRING>::iterator it	= m_Char_Info_String.begin();

	int px	= m_wChar_Info_X;
	int py	= m_wChar_Info_Y;
	int iPureY	= 0;
		PrintInfo	serverFont = gpC_base->m_chatting_pi;
#if __CONTENTS(__JAPAN_UI)
		serverFont = gpC_base->m_small_pi;
#endif //__JAPAN_UI

	bool bHighResolution = g_pUserInformation->iResolution_x > 800;


	if ( m_stSelect_Slot != -1 && m_Char_Info_String.size() > m_stSelect_Slot )
	{
		g_PrintColorStr(px+21, py+12, m_Char_Info_String[m_stSelect_Slot].strName.c_str(),			serverFont, colFontRgb);

		//py += 16;
		//g_PrintColorStr(px, py, m_Char_Info_String[m_stSelect_Slot].strLevel.c_str(),			serverFont, colFontRgb);

		g_PrintColorStr(px+21, py+65, m_Char_Info_String[m_stSelect_Slot].strStrength.c_str(),		serverFont, colFontRgb);

		g_PrintColorStr(px+21, py+94, m_Char_Info_String[m_stSelect_Slot].strDex.c_str(),				serverFont, colFontRgb);

		g_PrintColorStr(px+21, py+123, m_Char_Info_String[m_stSelect_Slot].strInt.c_str(),				serverFont, colFontRgb);

		g_PrintColorStr(px+21, py+123+64, m_Char_Info_String[m_stSelect_Slot].strFame.c_str(),			serverFont, colFontRgb);

		g_PrintColorStr(px+21, py+123+64+30, m_Char_Info_String[m_stSelect_Slot].strGrade.c_str(),			serverFont, colFontRgb);
	}



/*
	for(int i = 0; i < m_Char_Info_String.size(); it++, i++)
	{
		if(it->iSlotIndex	== m_stSelect_Slot)
		{
			switch(m_slot[m_stSelect_Slot].Race)
			{
			case RACE_SLAYER:
				if(!bHighResolution)
				{
					px	= m_wSlayerChar_Info_X;
					py	= m_wSlayerChar_Info_Y;
				}

				g_PrintColorStr(px, py, it->strName.c_str(),			serverFont, colFontRgb);

				py += 16;
				g_PrintColorStr(px, py, it->strStrength.c_str(),		serverFont, colFontRgb);

				py += 16;
				g_PrintColorStr(px, py, it->strDex.c_str(),				serverFont, colFontRgb);
			
				py += 16;
				g_PrintColorStr(px, py, it->strInt.c_str(),				serverFont, colFontRgb);

				iPureY = py;

				//if(!bHighResolution)
				//{
				//	px += 130;
				//	py = m_wSlayerChar_Info_Y;
				//	g_PrintColorStr(px, py, it->strSwordLevel.c_str(),		serverFont, colFontRgb);

				//	py += 16;
				//	g_PrintColorStr(px, py, it->strBladeLevel.c_str(),		serverFont, colFontRgb);

				//	py += 16;
				//	g_PrintColorStr(px, py, it->strGunLevel.c_str(),		serverFont, colFontRgb);

				//	py += 16;
				//	g_PrintColorStr(px, py, it->strHealLevel.c_str(),		serverFont, colFontRgb);

				//	py += 16;
				//	g_PrintColorStr(px, py, it->strEnchantLevel.c_str(),	serverFont, colFontRgb);

				//	px	= m_wSlayerChar_Info_X;
				//}
				//else
				//{
				//	py += 16;
				//	g_PrintColorStr(px, py, it->strSwordLevel.c_str(),		serverFont, colFontRgb);

				//	py += 16;
				//	g_PrintColorStr(px, py, it->strBladeLevel.c_str(),		serverFont, colFontRgb);

				//	py += 16;
				//	g_PrintColorStr(px, py, it->strGunLevel.c_str(),		serverFont, colFontRgb);

				//	py += 16;
				//	g_PrintColorStr(px, py, it->strHealLevel.c_str(),		serverFont, colFontRgb);

				//	py += 16;
				//	g_PrintColorStr(px, py, it->strEnchantLevel.c_str(),	serverFont, colFontRgb);

				//	iPureY = py;
				//	px	= m_wChar_Info_X;
				//}
				py	= iPureY + 16;
				g_PrintColorStr(px, py, it->strFame.c_str(),			serverFont, colFontRgb);
				
				py += 16;
				g_PrintColorStr(px, py, it->strGrade.c_str(),			serverFont, colFontRgb);
				break;
				
			case RACE_VAMPIRE:
				g_PrintColorStr(px, py, it->strName.c_str(),			serverFont, colFontRgb);

				py += 16;
				g_PrintColorStr(px, py, it->strLevel.c_str(),			serverFont, colFontRgb);

				py += 16;
				g_PrintColorStr(px, py, it->strStrength.c_str(),		serverFont, colFontRgb);

				py += 16;
				g_PrintColorStr(px, py, it->strDex.c_str(),				serverFont, colFontRgb);
			
				py += 16;
				g_PrintColorStr(px, py, it->strInt.c_str(),				serverFont, colFontRgb);
				
				py += 16;
				g_PrintColorStr(px, py, it->strFame.c_str(),			serverFont, colFontRgb);
				
				py += 16;
				g_PrintColorStr(px, py, it->strGrade.c_str(),			serverFont, colFontRgb);
				break;

			case RACE_OUSTERS:
				g_PrintColorStr(px, py, it->strName.c_str(),			serverFont, colFontRgb);

				py += 16;
				g_PrintColorStr(px, py, it->strLevel.c_str(),			serverFont, colFontRgb);

				py += 16;
				g_PrintColorStr(px, py, it->strStrength.c_str(),		serverFont, colFontRgb);

				py += 16;
				g_PrintColorStr(px, py, it->strDex.c_str(),				serverFont, colFontRgb);
			
				py += 16;
				g_PrintColorStr(px, py, it->strInt.c_str(),				serverFont, colFontRgb);
				
				py += 16;
				g_PrintColorStr(px, py, it->strFame.c_str(),			serverFont, colFontRgb);
				break;
			}
		}
	}	
	*/
}


/*-----------------------------------------------------------------------------
- ~C_VS_UI_CHAR_MANAGER
-
-----------------------------------------------------------------------------*/
C_VS_UI_CHAR_MANAGER::~C_VS_UI_CHAR_MANAGER()
{
	g_UnregisterWindow(this);

	// !Window¸¦ ùÀú deleteÇØ¾ß ÇÑ´Ù.
	DeleteNew(m_pC_biling);
	DeleteNew(m_pC_char_delete);
	DeleteNew(m_pC_newchar);
#if	__CONTENTS(__USER_GRADE)
	DeleteNew(m_pC_use_grade);
#endif	//__USER_GRADE
	DeleteNew( m_pC_NetmarbleAgreement);
//	DeleteNew(m_pC_char_info);
	
	DeleteNew(m_pAnimationTimer);
	
	m_pC_button_group->Delete(m_pC_button_create_char[SLOT_LEFT]);
	m_pC_button_group->Delete(m_pC_button_create_char[SLOT_CENTER]);
	m_pC_button_group->Delete(m_pC_button_create_char[SLOT_RIGHT]);
	
	DeleteNew(m_pC_button_create_char[SLOT_LEFT]);
	DeleteNew(m_pC_button_create_char[SLOT_CENTER]);
	DeleteNew(m_pC_button_create_char[SLOT_RIGHT]);

	DeleteNew(m_pC_button_group);

	gC_timer2.Delete(g_char_update_tid);


}

//-----------------------------------------------------------------------------
// C_VS_UI_CHAR_MANAGER::CloseCharInfo
//
// 
//-----------------------------------------------------------------------------
//void C_VS_UI_CHAR_MANAGER::CloseCharInfo()
//{
//	if(m_pC_char_info != NULL)
//	{
//		DeleteNew(m_pC_char_info);
//		m_pC_char_info = NULL;
//	}
//
//	gbl_vampire_interface = false;
//
//	// change skin data
//	gpC_global_resource->FreeAssemble();
//	gpC_global_resource->LoadAssemble();
//}

//-----------------------------------------------------------------------------
// C_VS_UI_CHAR_MANAGER::SelectSlot
//
// selectµÇ¾úÀ¸¸é true¸¦ ¹ÝÈ¯ÇÑ´Ù.
//-----------------------------------------------------------------------------
bool C_VS_UI_CHAR_MANAGER::SelectSlot(int n)
{
	if (n >= 0 && n < SLOT)
	{
		if (m_slot[n].bl_set == true)
		{
			m_stSelect_Slot = n;
			g_char_index = 0;
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
// AcquireFirstSequence
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_CHAR_MANAGER::AcquireFirstSequence()
{
}

//-----------------------------------------------------------------------------
// UnacquireMouseFocus
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_CHAR_MANAGER::UnacquireMouseFocus()
{
	m_pC_button_group->UnacquireMouseFocus();
}

//-----------------------------------------------------------------------------
// WindowEventReceiver
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_CHAR_MANAGER::WindowEventReceiver(id_t event)
{
}

//-----------------------------------------------------------------------------
// IsPixel
//
// 
//-----------------------------------------------------------------------------
bool C_VS_UI_CHAR_MANAGER::IsPixel(int _x, int _y)
{
	return true;
//	return m_pC_back.IsPixel(SCR2WIN_X(_x), SCR2WIN_Y(_y));
}

//-----------------------------------------------------------------------------
// Run
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_CHAR_MANAGER::Run(id_t id)
{
	int i=-1;

	switch (id)
	{
		case CREATE_ID:
			//
			// ¼±ÅÃÇÑ Ä³¸¯ÅÍ Ä­ÀÌ ºñ¾î ÀÖÀ¸¸é ±× Ä­¿¡ Ä³¸¯ÅÍ¸¦ ¸¸µç´Ù.
			//
			{
				bool bSlotEmpty = false;
			// search empty slot
			if(m_stSelect_Slot < 0)
				{
				m_stSelect_Slot = 0;
					bSlotEmpty = true;
				}
				else
				{
					for (int i = SLOT_LEFT; i < SLOT; ++i)
					{
						if (m_slot[i].bl_set == false)
						{
							m_stSelect_Slot = i;
							bSlotEmpty = true;
							break;
						}
					}

				}
				if (!bSlotEmpty)
				{
					g_msg_all_slot_created->Start();
				}
				else if (m_slot[m_stSelect_Slot].bl_set == false)
			{
				m_select_heart_temp = 0;
				m_pC_newchar->Start();
				m_pC_newchar->SetCharacterToThisSlot(m_stSelect_Slot, &m_slot[m_stSelect_Slot]);
				m_pC_newchar->RollDice(); // Start()¿¡ ³ÖÀ¸¸é ¾ÈµÈ´Ù. - SetCharacterToThisSlot()¸¦ ±× µÚ¿¡ ÇÏ±â ¶§¹®.
				Finish();
				return;
			}

				//g_msg_all_slot_created->Start();
			}
			break;

		case NEXT_ID:
			// ¸ðµç slotÀÌ ºñ¾î ÀÖ´Â°¡?
			if (m_slot[SLOT_LEFT].bl_set == false &&
				 m_slot[SLOT_CENTER].bl_set == false &&
				 m_slot[SLOT_RIGHT].bl_set == false)
			{
				g_msg_all_slot_not_char->Start();
				break;
			}

			if (m_slot[m_stSelect_Slot].bl_set)
				gpC_base->SendMessage(UI_CONNECT, m_stSelect_Slot, 0);
			else
				g_msg_not_select_char->Start();
			break;

		case BACK_ID:
			//Finish();
			gpC_base->SendMessage(UI_CHARACTER_MANAGER_FINISHED); // Finish()¿¡ µÎÁö ¸»°Í.
			break;

		case DELETE_ID:
			//if (m_slot[m_stSelect_Slot].bl_set == true)
			//{
			//	DeleteNew(m_pC_char_delete);
			//	
			//	m_pC_char_delete = new C_VS_UI_CHAR_DELETE();
			//	m_pC_char_delete->Start();
			//	m_pC_char_delete->Slot(m_stSelect_Slot);
			//}
			break;
		case CANNOT_PLAY_ID :
			i=0;
		case CANNOT_PLAY_BY_ATTR_ID :
			if(i == -1)
				i=1;
			{
				DeleteNew(m_pC_biling);

				m_pC_biling = new C_VS_UI_GO_BILING_PAGE((C_VS_UI_GO_BILING_PAGE::BILING_MSG_LIST) i );
				m_pC_biling->Start();
			}
			break;
		case CHAR_SELECT_LEFT_ID:
			if(m_slot[SLOT_LEFT].bl_set == TRUE)
				AddCharInfoString(SLOT_LEFT);
			break;

		case CHAR_SELECT_CENTER_ID:
			if(m_slot[SLOT_CENTER].bl_set == TRUE)
				AddCharInfoString(SLOT_CENTER);
			break;

		case CHAR_SELECT_RIGHT_ID:
			if(m_slot[SLOT_RIGHT].bl_set == TRUE)
				AddCharInfoString(SLOT_RIGHT);
			break;

	}
}

/*-----------------------------------------------------------------------------
- MouseControl
-
-----------------------------------------------------------------------------*/
bool C_VS_UI_CHAR_MANAGER::MouseControl(UINT message, int _x, int _y)
{
	_x-=x;_y-=y;
	Window::MouseControl(message, _x, _y);

	bool re = m_pC_button_group->MouseControl(message, _x, _y);

	bool bHighResolution = g_pUserInformation->iResolution_x > 800;
	int ConvX = 0;	int ConvY = 0;
	
	switch (message)
	{
		case M_MOVING:
			m_focused_help = HELP_DEFAULT;
			{
				for(int i = 0; i < 3; i++)
				{
					if(_x > x+g_heart_rect[i]-ConvX && _x < x+g_heart_rect[i]-ConvX + m_image_spk.GetWidth() &&
						_y > y+HEART_Y-ConvY && _y < y+HEART_Y-ConvY + m_image_spk.GetHeight())
					{
						m_focused_help = HELP_MAX+i;
						break;
					}
				}
			}
			break;

		case M_LB_DOUBLECLICK:
//			if(re == true)
			{
				for(int i = 0; i < SLOT; i++)
				{
					if (((m_ptArrCharSelect_Button[i].x <= _x) 
						&& (m_ptArrCharSelect_Button[i].y - m_w_CharHeight <= _y))
						&& 
						((m_ptArrCharSelect_Button[i].x + m_image_spk.GetWidth(CHAR_SELECT_LEFT + i) >= _x)
						&& (m_ptArrCharSelect_Button[i].y + m_image_spk.GetHeight(CHAR_SELECT_LEFT + i) >= _y)))
					{
						if(m_slot[i].bl_set == true)
							Run(NEXT_ID);
						else
							Run(CREATE_ID);
					}
				}
			break;
			}

		case M_LEFTBUTTON_UP:
			break;

		case M_RIGHTBUTTON_UP:
//			Run(CHARINFO);
			break;

		case M_WHEEL_UP:
			break;

		case M_WHEEL_DOWN:
			break;

	}

	return true;
}

/*-----------------------------------------------------------------------------
- KeyboardControl
-
-----------------------------------------------------------------------------*/
void C_VS_UI_CHAR_MANAGER::KeyboardControl(UINT message, UINT key, long extra)
{
	switch(message)
	{
	case WM_KEYDOWN:
		switch(key)
		{
		case VK_ESCAPE:
			Run(BACK);
			break;

		case VK_RIGHT:
			if(!SelectSlot(m_stSelect_Slot+1))SelectSlot(m_stSelect_Slot+2);
			break;

		case VK_LEFT:
			if(!SelectSlot(m_stSelect_Slot-1))SelectSlot(m_stSelect_Slot-2);
			break;

		case VK_RETURN:
			Run(NEXT_ID);
			break;

		case VK_UP:
			break;

		case VK_DOWN:
			break;

		}
		break;
	}
}


void C_VS_UI_CHAR_MANAGER::ShowButtonDescription(C_VS_UI_EVENT_BUTTON * p_button)
{
	switch(p_button->GetID())
	{
	case BACK_ID:
		m_focused_help = HELP_BACK;
		break;
	case NEXT_ID:	
		m_focused_help = HELP_NEXT;
		break;
	case DELETE_ID:
		m_focused_help = HELP_X;
		break;
		
	case CREATE_ID:
		m_focused_help = HELP_CREATE;
		break;
	}
}

void C_VS_UI_CHAR_MANAGER::ShowButtonName(C_VS_UI_EVENT_BUTTON *p_button)
{
	switch(p_button->GetID())
	{
	case BACK_ID:
		p_button->x	= m_wPrev_Button_X;
		p_button->y	= m_wPrev_Button_Y;
		g_PrintColorStr(p_button->x + 29+13, 	p_button->y + 7, "ÉÏÒ»²½", gpC_base->m_title_menu_pi, RGB_WHITE);
		break;

	case NEXT_ID:
		p_button->x	= m_wGameStart_Button_X;
		p_button->y	= m_wGameStart_Button_Y;
		g_PrintColorStr(p_button->x + 29 + 30, 	p_button->y + 7, "ÏÂÒ»²½", gpC_base->m_title_menu_pi, RGB_WHITE);
		break;

	case DELETE_ID:
		p_button->x	= m_wCharDelete_Button_X;
		p_button->y	= m_wCharDelete_Button_Y;
		g_PrintColorStr(p_button->x + 38, 	p_button->y + 7, "É¾³ý½ÇÉ«", gpC_base->m_title_menu_pi, RGB_WHITE);
		break;

	case CREATE_ID:
		p_button->x	= m_wCharCreate_Button_X;
		p_button->y	= m_wCharCreate_Button_Y;
		g_PrintColorStr(p_button->x + 38, 	p_button->y + 7, "´´½¨½ÇÉ«", gpC_base->m_title_menu_pi, RGB_WHITE);
		break;
	}
}

//-----------------------------------------------------------------------------
// ShowButtonWidget
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_CHAR_MANAGER::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{
//	int index = p_button->m_image_index;

	int picID = 0;

	switch(p_button->GetID())
	{
	case BACK_ID:
		p_button->x	= m_wPrev_Button_X;
		p_button->y	= m_wPrev_Button_Y;
		m_image_hays_2.BltLocked(p_button->x, p_button->y, p_button->m_image_index);
		break;

	case NEXT_ID:
		p_button->x	= m_wGameStart_Button_X;
		p_button->y	= m_wGameStart_Button_Y;
		m_image_hays_2.BltLocked(p_button->x, p_button->y, p_button->m_image_index);
		break;

	case DELETE_ID:
		p_button->x	= m_wCharDelete_Button_X;
		p_button->y	= m_wCharDelete_Button_Y;
		m_image_hays_2.BltLocked(p_button->x, p_button->y, p_button->m_image_index);
		break;

	case CREATE_ID:
		p_button->x	= m_wCharCreate_Button_X;
		p_button->y	= m_wCharCreate_Button_Y;
		m_image_hays_2.BltLocked(p_button->x, p_button->y, p_button->m_image_index);
		break;



	case CHAR_SELECT_LEFT_ID:
		if(p_button->GetFocusState())
		{
			if (p_button->GetPressState()) // push state
			{
				m_stSelect_Slot	= SLOT_LEFT;
			}
		}

		picID = m_slot[SLOT_LEFT].Race + RACE_ICON_SLAYER_ACTIVE;

		m_image_hays_1.BltLocked(m_ptArrCharSelect_Button[SLOT_LEFT].x, m_ptArrCharSelect_Button[SLOT_LEFT].y, p_button->m_image_index);

		if ( m_slot[SLOT_LEFT].bl_set )
			m_image_hays_1.BltLocked(m_ptArrCharSelect_Button[SLOT_LEFT].x, m_ptArrCharSelect_Button[SLOT_LEFT].y, picID + 3);
		
		if(m_stSelect_Slot == SLOT_LEFT)
		{
			m_image_hays_1.BltLocked(m_ptArrCharSelect_Button[SLOT_LEFT].x, m_ptArrCharSelect_Button[SLOT_LEFT].y, p_button->m_image_index+1);

			if ( m_slot[SLOT_LEFT].bl_set )
				m_image_hays_1.BltLocked(m_ptArrCharSelect_Button[SLOT_LEFT].x, m_ptArrCharSelect_Button[SLOT_LEFT].y, picID);
			//else
			//{
			//	bool bHighResolution = g_pUserInformation->iResolution_x > 800;

			//	if(bHighResolution)
			//	{
			//		if(g_pUserInformation->iResolution_x <= 1024) //1024  768
			//			m_iBackGroundPicID = NONE_1024_768;
			//		else 
			//		{
			//			if(g_pUserInformation->iResolution_y <= 960) //1280  960
			//				m_iBackGroundPicID = NONE_1280_960;
			//			else  //1280  1024
			//				m_iBackGroundPicID = NONE_1280_1024;
			//		}
			//	}
			//	else		// 800*600
			//	{
			//		m_iBackGroundPicID = NONE_800_600;
			//	}
			//}
		}
		break;

	case CHAR_SELECT_CENTER_ID:
		if(p_button->GetFocusState())
		{
			if (p_button->GetPressState()) // push state
			{
				m_stSelect_Slot	= SLOT_CENTER;
			}
		}

		picID = m_slot[SLOT_CENTER].Race + RACE_ICON_SLAYER_ACTIVE;
		m_image_hays_1.BltLocked(m_ptArrCharSelect_Button[SLOT_CENTER].x, m_ptArrCharSelect_Button[SLOT_CENTER].y, p_button->m_image_index);

		if ( m_slot[SLOT_CENTER].bl_set )
			m_image_hays_1.BltLocked(m_ptArrCharSelect_Button[SLOT_CENTER].x, m_ptArrCharSelect_Button[SLOT_CENTER].y, picID + 3);

		if(m_stSelect_Slot == SLOT_CENTER)
		{
			m_image_hays_1.BltLocked(m_ptArrCharSelect_Button[SLOT_CENTER].x, m_ptArrCharSelect_Button[SLOT_CENTER].y, p_button->m_image_index+1);

			if ( m_slot[SLOT_CENTER].bl_set )
				m_image_hays_1.BltLocked(m_ptArrCharSelect_Button[SLOT_CENTER].x, m_ptArrCharSelect_Button[SLOT_CENTER].y, picID);
			//else
			//{
			//	bool bHighResolution = g_pUserInformation->iResolution_x > 800;

			//	if(bHighResolution)
			//	{
			//		if(g_pUserInformation->iResolution_x <= 1024) //1024  768
			//			m_iBackGroundPicID = NONE_1024_768;
			//		else 
			//		{
			//			if(g_pUserInformation->iResolution_y <= 960) //1280  960
			//				m_iBackGroundPicID = NONE_1280_960;
			//			else  //1280  1024
			//				m_iBackGroundPicID = NONE_1280_1024;
			//		}
			//	}
			//	else		// 800*600
			//	{
			//		m_iBackGroundPicID = NONE_800_600;
			//	}
			//}

		}
		break;

	case CHAR_SELECT_RIGHT_ID:
		if(p_button->GetFocusState())
		{
			if (p_button->GetPressState()) // push state
			{
				m_stSelect_Slot	= SLOT_RIGHT;
			}
		}

		picID = m_slot[SLOT_RIGHT].Race + RACE_ICON_SLAYER_ACTIVE;
		m_image_hays_1.BltLocked(m_ptArrCharSelect_Button[SLOT_RIGHT].x, m_ptArrCharSelect_Button[SLOT_RIGHT].y, p_button->m_image_index);

		if ( m_slot[SLOT_RIGHT].bl_set )
			m_image_hays_1.BltLocked(m_ptArrCharSelect_Button[SLOT_RIGHT].x, m_ptArrCharSelect_Button[SLOT_RIGHT].y, picID + 3);
		
		if(m_stSelect_Slot == SLOT_RIGHT)
		{
			m_image_hays_1.BltLocked(m_ptArrCharSelect_Button[SLOT_RIGHT].x, m_ptArrCharSelect_Button[SLOT_RIGHT].y, p_button->m_image_index+1);
			if ( m_slot[SLOT_RIGHT].bl_set )
				m_image_hays_1.BltLocked(m_ptArrCharSelect_Button[SLOT_RIGHT].x, m_ptArrCharSelect_Button[SLOT_RIGHT].y, picID);
			//else
			//{
			//	bool bHighResolution = g_pUserInformation->iResolution_x > 800;

			//	if(bHighResolution)
			//	{
			//		if(g_pUserInformation->iResolution_x <= 1024) //1024  768
			//			m_iBackGroundPicID = NONE_1024_768;
			//		else 
			//		{
			//			if(g_pUserInformation->iResolution_y <= 960) //1280  960
			//				m_iBackGroundPicID = NONE_1280_960;
			//			else  //1280  1024
			//				m_iBackGroundPicID = NONE_1280_1024;
			//		}
			//	}
			//	else		// 800*600
			//	{
			//		m_iBackGroundPicID = NONE_800_600;
			//	}
			//}
		}

		break;
	}

	if(p_button->GetFocusState())
	{
		if (p_button->GetPressState()) // push state
		{
			if(!((p_button->GetID()	== CHAR_SELECT_LEFT_ID) || (p_button->GetID()	== CHAR_SELECT_CENTER_ID) || (p_button->GetID()	== CHAR_SELECT_RIGHT_ID)))
				m_image_hays_2.BltLocked(p_button->x, p_button->y, p_button->m_image_index-1);
		}
		else
		{
			//¹öÆ°À» ¼­¼­È÷ È°¼ºÈ­ ½ÃÅ°±â À§ÇØ¼­ ±âº» ±×¸²À» »Ñ¸°´Ù ¿ÏÀü Åõ¸íÀÏ¶§ ¹öÆ°ÀÌ ¾ø¾îÁ® ¹ö¸²
			if(p_button->GetID()	== BACK_ID || p_button->GetID()	== NEXT_ID || p_button->GetID()	== DELETE_ID || p_button->GetID()	== CREATE_ID)
			{
				if(p_button->m_alpha >= 31)
					p_button->m_alpha = 0;	
				m_image_hays_2.BltLockedAlpha(p_button->x, p_button->y, p_button->m_image_index-1, p_button->m_alpha);
			}
		}
	}
}




void	C_VS_UI_CHAR_MANAGER::ChangeEffectPoint()
{
	POINT	ptEffect;
	ptEffect.x	= 	m_wEffect_Fire_Left1_X;
	ptEffect.y	=	m_wEffect_Fire_Left1_Y;
	g_pTopView->SetTitleEffectPos(&ptEffect, EFFECT_INDEX_FIRE_LEFT1);

	ptEffect.x	= 	m_wEffect_Fire_Left2_X;
	ptEffect.y	=	m_wEffect_Fire_Left2_Y;
	g_pTopView->SetTitleEffectPos(&ptEffect, EFFECT_INDEX_FIRE_LEFT2);

	ptEffect.x	= 	m_wEffect_Fire_Right1_X;
	ptEffect.y	=	m_wEffect_Fire_Right1_Y;
	g_pTopView->SetTitleEffectPos(&ptEffect, EFFECT_INDEX_FIRE_RIGHT1);

	ptEffect.x	= 	m_wEffect_Fire_Right2_X;
	ptEffect.y	=	m_wEffect_Fire_Right2_Y;
	g_pTopView->SetTitleEffectPos(&ptEffect, EFFECT_INDEX_FIRE_RIGHT2);

	ptEffect.x	= 	m_wEffect_Fire_Center_X;
	ptEffect.y	=	m_wEffect_Fire_Center_Y;
	g_pTopView->SetTitleEffectPos(&ptEffect, EFFECT_INDEX_FIRE_CENTER);

	for(int i = 0; i < SLOT; i++)
	{
		g_pTopView->SetTitleEffectPos(&m_ptEffect_Char_Attach_UP[i], EFFECT_INDEX_CHAR_ATTACH_UP + (SLOT*i));
		g_pTopView->SetTitleEffectPos(&m_ptEffect_Char_Attach_DOWN[i], EFFECT_INDEX_CHAR_ATTACH_DOWN + (SLOT*i));
		g_pTopView->SetTitleEffectPos(&m_ptEffect_Char_Select[i], EFFECT_INDEX_CHAR_SELECT + (SLOT*i));
	}
}



void	C_VS_UI_CHAR_MANAGER::Draw_Effect_Button_Char()
{
	g_pTopView->DrawTitleEffect(EFFECT_INDEX_FIRE_LEFT1);
	g_pTopView->DrawTitleEffect(EFFECT_INDEX_FIRE_LEFT2);
	g_pTopView->DrawTitleEffect(EFFECT_INDEX_FIRE_RIGHT1);
	g_pTopView->DrawTitleEffect(EFFECT_INDEX_FIRE_RIGHT2);
	g_pTopView->DrawTitleEffect(EFFECT_INDEX_FIRE_CENTER);
	
	if(gpC_base->m_p_DDSurface_back->Lock())
	{
		m_pC_button_group->Show();	   
		gpC_base->m_p_DDSurface_back->Unlock();
	}

	for (int i = 0; i < SLOT; i++)
	{
		if (m_slot[i].bl_set)
		{
			int index;
			index = g_char_index;
			g_CurrentFrame = index;

			if(i == m_stSelect_Slot)
			{
				g_pTopView->DrawTitleEffect(EFFECT_INDEX_CHAR_SELECT + (SLOT*i));
				g_pTopView->DrawTitleEffect(EFFECT_INDEX_CHAR_ATTACH_UP + (SLOT*i));
			}	

			m_pC_newchar->ShowCharacter(m_ptArrChar_Pos[i].x, m_ptArrChar_Pos[i].y, &m_slot[i], index, (m_stSelect_Slot==i)?1:0, !(m_stSelect_Slot==i));

			if(i == m_stSelect_Slot)
			{
				g_pTopView->DrawTitleEffect(EFFECT_INDEX_CHAR_ATTACH_DOWN + (SLOT*i));
			}
		}
	}
}



/*-----------------------------------------------------------------------------
- Show
-
-----------------------------------------------------------------------------*/
void C_VS_UI_CHAR_MANAGER::Show()
{

	bool bHighResolution = g_pUserInformation->iResolution_x > 800;



	//bool bHighResolution = g_pUserInformation->iResolution_x > 800;

	if ( m_stSelect_Slot == -1 )
	{
		if(bHighResolution)
		{
			if(g_pUserInformation->iResolution_x <= 1024) //1024  768
				m_iBackGroundPicID = NONE_1024_768;
			else 
			{
				if(g_pUserInformation->iResolution_y <= 960) //1280  960
					m_iBackGroundPicID = NONE_1280_960;
				else  //1280  1024
					m_iBackGroundPicID = NONE_1280_1024;
			}
		}
		else		// 800*600
		{
			m_iBackGroundPicID = NONE_800_600;
		}
	}
	else
	{
		if(bHighResolution)
		{
			if(g_pUserInformation->iResolution_x <= 1024) //1024  768
				m_iBackGroundPicID = m_slot[m_stSelect_Slot].Race + SLAYER_1024_768;
			else 
			{
				if(g_pUserInformation->iResolution_y <= 960) //1280  960
					m_iBackGroundPicID = m_slot[m_stSelect_Slot].Race + SLAYER_1280_960;
				else  //1280  1024
					m_iBackGroundPicID = m_slot[m_stSelect_Slot].Race + SLAYER_1280_1024;
			}
		}
		else		// 800*600
		{
			m_iBackGroundPicID = m_slot[m_stSelect_Slot].Race;
		}
	}




	
	m_pC_button_group->ShowDescription();
	Init_TitleUIInterface_InfInfo();

	gpC_base->m_p_DDSurface_back->FillSurface(0);
	if(gpC_base->m_p_DDSurface_back->Lock())
	{
		if(bHighResolution)
		{
			if(g_pUserInformation->iResolution_x <= 1024) //1024  768
			{
				if ( !m_slot[m_stSelect_Slot].bl_set )
					m_iBackGroundPicID = NONE_1024_768;

				m_image_hays_0.BltLocked( (g_pUserInformation->iResolution_x - m_image_hays_0.GetWidth(m_iBackGroundPicID)) / 2, 
					(g_pUserInformation->iResolution_y - m_image_hays_0.GetHeight(m_iBackGroundPicID)) / 2, m_iBackGroundPicID);
				
				//m_image_spk.BltLocked(m_wChar_Info_Angle_X, m_wChar_Info_Angle_Y, CAHR_INFO_ANGLE_1024_768); ½ÇÉ«ÐÅÏ¢Ãæ°å
			}
			
			else
			{
				if(g_pUserInformation->iResolution_y < 960)//1280  960
				{
					if ( !m_slot[m_stSelect_Slot].bl_set )
						m_iBackGroundPicID = NONE_1280_960;

					m_image_hays_0.BltLocked( (g_pUserInformation->iResolution_x - m_image_hays_0.GetWidth(m_iBackGroundPicID)) / 2, 
						(g_pUserInformation->iResolution_y - m_image_hays_0.GetHeight(m_iBackGroundPicID)) / 2, m_iBackGroundPicID);
					
				//	//m_image_hays_0.BltLocked(m_wChar_Info_Angle_X, m_wChar_Info_Angle_Y, CAHR_INFO_ANGLE_1024_768);  ½ÇÉ«ÐÅÏ¢Ãæ°å
				//}
				//else if(g_pUserInformation->iResolution_y < 1024)
				//{
				//	m_image_hays_0.BltLocked( (g_pUserInformation->iResolution_x - m_image_hays_0.GetWidth(WINDOW_1280_960)) / 2, 
				//		(g_pUserInformation->iResolution_y - m_image_spk.GetHeight(WINDOW_1280_960)) / 2, WINDOW_1280_960);
				//	
				//	//m_image_hays_0.BltLocked(m_wChar_Info_Angle_X, m_wChar_Info_Angle_Y, CAHR_INFO_ANGLE_1024_768); ½ÇÉ«ÐÅÏ¢Ãæ°å
				}
				else//1280  1024
				{
					if ( !m_slot[m_stSelect_Slot].bl_set )
						m_iBackGroundPicID = NONE_1280_1024;

					m_image_hays_0.BltLocked( (g_pUserInformation->iResolution_x - m_image_hays_0.GetWidth(m_iBackGroundPicID)) / 2, 
						(g_pUserInformation->iResolution_y - m_image_hays_0.GetHeight(m_iBackGroundPicID)) / 2, m_iBackGroundPicID);
					
					//m_image_hays_0.BltLocked(m_wChar_Info_Angle_X, m_wChar_Info_Angle_Y, CAHR_INFO_ANGLE_1024_768);  ½ÇÉ«ÐÅÏ¢Ãæ°å
				}
			}
		}
		else // 800  600
		{
			if ( !m_slot[m_stSelect_Slot].bl_set )
				m_iBackGroundPicID = NONE_800_600;

			m_image_hays_0.BltLocked( (g_pUserInformation->iResolution_x - m_image_hays_0.GetWidth(m_iBackGroundPicID)) / 2, 
				(g_pUserInformation->iResolution_y - m_image_hays_0.GetHeight(m_iBackGroundPicID)) / 2, m_iBackGroundPicID);


			//½ÇÉ«ÐÅÏ¢Ãæ°å
			//if(m_stSelect_Slot >= 0 && m_stSelect_Slot <= SLOT)
			//{
			//	if(m_slot[m_stSelect_Slot].Race	== RACE_SLAYER)
			//	{
			//		m_image_spk.BltLocked(m_wSlayerChar_Info_Angle_X, m_wSlayerChar_Info_Angle_Y, SLAYER_CHAR_INFO_ANGLE);
			//	}
			//	else
			//	{
			//		m_image_spk.BltLocked(m_wChar_Info_Angle_X, m_wChar_Info_Angle_Y, CAHR_INFO_ANGLE_800_600);			
			//	}
			//}
		}
		
//		ChangeEffectPoint();   show fire!!!!!!!!!!!!!!
//#if __CONTENTS(__USER_GRADE)
//#if __CONTENTS(!__IMI_INTERFACE)
//		if(!g_pUserInformation->GoreLevel)
//			m_pC_use_grade->BltLocked(m_wChild_X, m_wChild_Y, CHILD);
//		else
//#endif
//			m_pC_use_grade->BltLocked(m_wAdult_X, m_wAdult_Y, ADULT);
//		m_pC_use_grade->BltLocked(m_wViolence_X, m_wViolence_Y, VIOLENCE);
//		m_pC_use_grade->BltLocked(m_wFear_X, m_wFear_Y, FEAR);
//#endif // __USER_GRADE

		//m_image_spk.BltLocked(m_wTex_Bar_X, m_wTex_Bar_Y, TEXT_BAR);
		//m_image_spk.BltLocked(m_wAni_Mark_X, m_wAni_Mark_Y, ANI_MARK);

		gpC_base->m_p_DDSurface_back->Unlock();
	}


	COLORREF disable_color = RGB(100, 100, 100);

	int i;


	if(gpC_base->m_p_DDSurface_back->Lock())
	{
		//DrawPanel
		m_image_hays_1.BltLocked( m_wPanel_X, m_wPanel_Y, PANAL_NONE);
		m_image_hays_1.BltLockedAlpha( m_wPanel_X, m_wPanel_Y, PANAL_FILL, 20);

		//Draw infomation
		m_image_hays_1.BltLocked( m_wListInfo_X, m_wListInfo_Y, LIST_INFOMATION_NONE);
		m_image_hays_1.BltLockedAlpha( m_wListInfo_X, m_wListInfo_Y, LIST_INFOMATION_NORMAL, 20);

		//DrawButton
		m_pC_button_group->Show();	   
		//DrawLockButton
		m_image_hays_1.BltLocked( m_wPanel_X + 24, m_ptArrCharSelect_Button[SLOT_RIGHT].y + 80, BUTTON_SELROLE_ENABLE);
		m_image_hays_1.BltLocked( m_wPanel_X + 24, m_ptArrCharSelect_Button[SLOT_RIGHT].y + 160, BUTTON_SELROLE_ENABLE);

		gpC_base->m_p_DDSurface_back->Unlock();
	}

	//show select role button
	//Draw_Effect_Button_Char();

	//if(gpC_base->m_p_DDSurface_back->Lock())
	//{
	//	for (i = 0; i < SLOT; i++)
	//	{
	//		m_image_spk.BltLocked(m_ptChar_Name_Bar[i].x, m_ptChar_Name_Bar[i].y, CAHR_NAME_ANGLE);
	//	}
	//	gpC_base->m_p_DDSurface_back->Unlock();
	//}

	g_FL2_GetDC();
	for (i = 0; i < SLOT; i++)
	{
		if(m_slot[i].bl_set)
		{
			int iX = m_wPanel_X + 203;
			int iY = m_wPanel_Y + 119 + i*80;
			g_PrintColorStrShadow(iX, iY, m_slot[i].sz_name.c_str(), gpC_base->m_haysNameBig, RGB_WHITE, RGB_BLACK);

			iX = m_wPanel_X + 94;
			iY = m_wPanel_Y + 91 + i*80;

			char str[255];
			if(m_slot[i].m_AdvancementLevel<0)
			wsprintf(str, "µÈ¼¶£º%d", m_slot[i].level);
			else
			wsprintf(str, "×ªÖ°£º%d", m_slot[i].m_AdvancementLevel);
			g_PrintColorStrShadow(iX, iY, str, gpC_base->m_haysLevel, RGB_WHITE, RGB_BLACK);
		}
	}

	g_PrintColorStr(m_wPanel_X + 119, 	m_wPanel_Y + 28, "ÈËÎïÑ¡Ôñ", gpC_base->m_haysNameBig, RGB_WHITE);

	DrawCharInfoString();
//	for(i = 0; i < LINE_MAX; i++)
//	{
////		g_PrintColorStr(m_ptText_Line[i].x, 	m_ptText_Line[i].y,
////						m_arrTextLine[i], gpC_base->m_title_menu_pi, RGB_WHITE);
//
//		g_PrintColorStr(m_ptText_Line[i].x, 	m_ptText_Line[i].y,
//						(*g_pGameStringTable)[UI_TITLE_UI_RENEWAL_CHARMANAGER_TEXT1 + i].GetString(), gpC_base->m_title_menu_pi, RGB_WHITE);
//	}

	char szBuffer[256]	= {NULL,};

	if (g_LeftPremiumDays == 0xFFFE)
	{
		sprintf( szBuffer, (*g_pGameStringTable)[UI_STRING_MESSAGE_NOT_PREMIUM_USER].GetString() );
	}
	else if (g_LeftPremiumDays == 0xFFFC && g_PayType == 4 )
	{
		sprintf( szBuffer, (*g_pGameStringTable)[UI_STRING_MESSAGE_DEFERRED_PAYMENT_NOTICE].GetString() );
	}
	else if ( g_LeftPremiumDays > 0 && g_PayType == 1)
	{
		if(g_bFamily)
			sprintf( szBuffer, (*g_pGameStringTable)[UI_STRING_MESSAGE_LEFT_FAMILY_DAYS].GetString(), g_LeftPremiumDays );
		else
			sprintf( szBuffer, (*g_pGameStringTable)[UI_STRING_MESSAGE_LEFT_PREMIUM_DAYS].GetString(), g_LeftPremiumDays );
	}
	else if (g_LeftPremiumDays == 0 && g_PayType == 1)
	{
		if(g_bFamily)
			sprintf( szBuffer, (*g_pGameStringTable)[UI_STRING_MESSAGE_EXPIRE_FAMILY_TODAY].GetString() );	
		else
			sprintf( szBuffer, (*g_pGameStringTable)[UI_STRING_MESSAGE_EXPIRE_PREMIUM_SERVICE_TODAY].GetString() );	
	}
	else if ( g_LeftPremiumDays > 0 && g_PayType == 3)
	{
		sprintf( szBuffer, (*g_pGameStringTable)[UI_STRING_MESSAGE_LEFT_PREMIUM_PAYZONE_DAYS].GetString(), g_LeftPremiumDays );
	}
	else if (g_LeftPremiumDays == 0 && g_PayType == 3)
	{
		sprintf( szBuffer, (*g_pGameStringTable)[UI_STRING_MESSAGE_LEFT_PREMIUM_PAYZONE_DAYS].GetString() );	
	}

	int szBufferLen = g_GetStringWidth(szBuffer, gpC_base->m_desc_menu_pi.hfont)/2;

	m_pC_button_group->ShowButtonName();

//	if( g_LeftPremiumDays != 0xFFFF )
//	{
//		if(g_pUserInformation->IsResolution1024)
//		{
//			g_PrintColorStr((1024 / 2) - szBufferLen, m_wPrimeum_Use_Day_Txt_Y, szBuffer, gpC_base->m_desc_menu_pi, RGB_WHITE );
//		}
//		else
//		{
//			g_PrintColorStr((800 / 2) - szBufferLen, m_wPrimeum_Use_Day_Txt_Y, szBuffer, gpC_base->m_desc_menu_pi, RGB_WHITE );
//		}
//	}

	g_PrintColorStr(m_wWorningString_X, 	m_wWorningString_Y,
						(*g_pGameStringTable)[UI_STRING_MESSAGE_CHILDGUARD_DENYED_NOTUSE], gpC_base->m_title_menu_pi, RGB_WHITE);
	g_FL2_ReleaseDC();

	SHOW_WINDOW_ATTR;
}



/////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// Process
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_SERVER_SELECT::Process()
{
	m_pC_button_group->Process();
}

//-----------------------------------------------------------------------------
// Start
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_SERVER_SELECT::Start(bool bGroup)
{
	m_bl_group = bGroup;

	PI_Processor::Start();

	gpC_window_manager->AppearWindow(this);
	m_pC_button_group->Init();

	// change skin data
	gpC_global_resource->FreeAssemble();
	gpC_global_resource->LoadAssemble();

	m_pack_file.SetRAR(RPK_TITLE, RPK_PASSWORD);

	SetDesc(29, 160, RGB(160, 160, 160), gpC_base->m_chatting_pi);
	m_desc_y_distance = 16;

	m_scroll = 0;
	m_bl_scrolling = false;

	m_focused_help = HELP_DEFAULT;
	m_focus_server = -1;

	if(m_bl_group)
		LoadDesc("world.txt", 30, 14, false);
	else
		LoadDesc("server.txt", 30, 14, false);

	EMPTY_MOVE;

}

//-----------------------------------------------------------------------------
// Finish
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_SERVER_SELECT::Finish()
{
	PI_Processor::Finish();

	m_server_name_chenel.clear();
	m_server_id_chenel.clear();
	m_server_status_chenel.clear();

	gpC_window_manager->DisappearWindow(this);
}

/*-----------------------------------------------------------------------------
- C_VS_UI_SERVER_SELECT
-
-----------------------------------------------------------------------------*/
C_VS_UI_SERVER_SELECT::C_VS_UI_SERVER_SELECT()
{
	m_focus_server = -1;
	m_server_select = -1;
	m_scroll = 0;
	m_server_size	= 0;

	m_pAnimationTimer = new CTickTimer;
	m_pAnimationTimer->StartTimer(50, true);
	m_aniArpha = 31;
	m_bAniArphaUp = false;

	m_pserver_slayernum_barcount	= NULL;
	m_pserver_vampirenum_barcount	= NULL;
	m_pserver_ousters_barcount		= NULL;

	m_server_select_world			= 0;
	m_server_select_chenel			= 0;
	m_wSelect_Chenel_Index			= 0;
	m_blAccep_World_Chenenl			= true;

	m_server_select_world_prev		= -1;
	m_server_select_chenel_prev		= -1;

	m_iOldMousePoint_X				= 0;
	m_iOldMousePoint_Y				= 0;

	m_blKeybord_OR_Mouse_Input		= true;

	Init_TitleUIInterface_InfInfo();
#if	__CONTENTS(__USER_GRADE)
	m_pC_use_grade = new C_SPRITE_PACK(SPK_USE_GRADE);
#endif	//__USER_GRADE

	m_title_spk.Open(SPK_TITLE);
	m_title_hays_spk.Open(SPK_NEW_TITLE);

	bool bHighResolution = g_pUserInformation->iResolution_x > 800;
	int ConvX = 0;	int ConvY = 0;
	
	//¼­¹ö ¸®½ºÆ® Ãâ·ÂÀ§Ä¡
	m_server_x = 350+ConvX;
	m_server_y = 191+ConvY;


	g_RegisterWindow(this);

	AttrKeyboardControl(true);

	m_image_hays_spk.Open(SPK__NEW_SERVER_SELECT);
	m_image_spk.Open(SPK_SERVER_SELECT);
	
	Set(0, 0, g_pUserInformation->iResolution_x, g_pUserInformation->iResolution_y);
 	if(bHighResolution)
 	{
 		if(g_pUserInformation->iResolution_x <= 1024)
 			Set( (g_pUserInformation->iResolution_x - m_title_spk.GetWidth(1)) / 2, 
 			(g_pUserInformation->iResolution_y - m_title_spk.GetHeight(1)) / 2, 
 			m_title_spk.GetWidth(1), m_title_spk.GetHeight(1) );
 		else // if(g_pUserInformation->iResolution_x > 1024)
 		{
 			if(g_pUserInformation->iResolution_y < 960)
 				Set( (g_pUserInformation->iResolution_x - m_title_spk.GetWidth(2)) / 2, 
 				(g_pUserInformation->iResolution_y - m_title_spk.GetHeight(2)) / 2, 
 				m_title_spk.GetWidth(2), m_title_spk.GetHeight(2) );
 			else if(g_pUserInformation->iResolution_y < 1024)
 				Set( (g_pUserInformation->iResolution_x - m_title_spk.GetWidth(3)) / 2, 
 				(g_pUserInformation->iResolution_y - m_title_spk.GetHeight(3)) / 2, 
 				m_title_spk.GetWidth(3), m_title_spk.GetHeight(3) );
 			else
 				Set( (g_pUserInformation->iResolution_x - m_title_spk.GetWidth(4)) / 2, 
 				(g_pUserInformation->iResolution_y - m_title_spk.GetHeight(4)) / 2, 
 				m_title_spk.GetWidth(4), m_title_spk.GetHeight(4) );
 		}
 	}
	else
		Set( (g_pUserInformation->iResolution_x - m_title_spk.GetWidth(0)) / 2, 
 			(g_pUserInformation->iResolution_y - m_title_spk.GetHeight(0)) / 2, 
			m_title_spk.GetWidth(0), m_title_spk.GetHeight(0) );
	

	m_pC_button_group = new ButtonGroup(this);

	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_wPreve_Button_X, m_wPreve_Button_Y, 
							m_image_spk.GetWidth(PREV_SCREEN_BUTTON), m_image_spk.GetHeight(PREV_SCREEN_BUTTON), 
							BACK_ID, this, PREV_SCREEN_BUTTON));
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_wNext_Button_X, m_wNext_Button_Y, 
							m_image_spk.GetWidth(NEXT_SCREEN_BUTTON), m_image_spk.GetHeight(NEXT_SCREEN_BUTTON), 
							NEXT_ID, this, NEXT_SCREEN_BUTTON));

	m_blKeybord_OR_Mouse_Input	= false;

	m_focused_help = HELP_DEFAULT;
}




void	C_VS_UI_SERVER_SELECT::Init_TitleUIInterface_InfInfo()
{
	char arrstrAppName[255]		= {NULL,};
	char arrstrFileName[255]	= {NULL,};

	GetCurrentDirectory(_MAX_PATH, arrstrFileName);	//ÇöÀç ½ÇÇà ÁßÀÎ ÆÄÀÏÀÇ °æ·Î¸¦ ¾ò´Â´Ù.

	bool bHighResolution = g_pUserInformation->iResolution_x > 800;
	int ConvX = 0;	int ConvY = 0;
	
	if(bHighResolution)
	{
		if(g_pUserInformation->iResolution_x <=1024)
			strcpy(arrstrAppName,"SERVER_SELECT_1024_768");
		else
		{
			// 1280*720
			if(g_pUserInformation->iResolution_y < 960)
			{	
				strcpy(arrstrAppName,"SERVER_SELECT_1280_720");

// 				ConvX = (g_pUserInformation->iResolution_x - m_image_spk.GetWidth(WINDOW_1024_768)) / 2;	//128
// 				ConvY = (g_pUserInformation->iResolution_y - m_image_spk.GetHeight(WINDOW_1024_768)) / 2;	//-24
			}
			// 1280*960
			else if(g_pUserInformation->iResolution_y < 1024)
			{	
				strcpy(arrstrAppName,"SERVER_SELECT_1280_960");

// 				ConvX = (g_pUserInformation->iResolution_x - m_image_spk.GetWidth(WINDOW_1024_768)) / 2;	//128
// 				ConvY = (g_pUserInformation->iResolution_y - m_image_spk.GetHeight(WINDOW_1024_768)) / 2;	//96
			}
			// 1280*1024
			else
			{	
				strcpy(arrstrAppName,"SERVER_SELECT_1280_1024");

// 				ConvX = (g_pUserInformation->iResolution_x - m_image_spk.GetWidth(WINDOW_1024_768)) / 2;	//128
// 				ConvY = (g_pUserInformation->iResolution_y - m_image_spk.GetHeight(WINDOW_1024_768)) / 2;	//128
			}
		}	
	}
	else
		strcpy(arrstrAppName,"SERVER_SELECT_800_600");

	strcat(arrstrFileName, FILE_INFO_TITLE_UI);

	m_wWorld_List_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "WORLD_LIST_X", 0, arrstrFileName);
	m_wWorld_List_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "WORLD_LIST_Y", 0, arrstrFileName);

	m_wSelect_World_Bar_Interval_X	= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_WORLD_BAR_INTERVAL_X", 0, arrstrFileName);
	m_wSelect_World_Bar_Interval_Y	= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_WORLD_BAR_INTERVAL_Y", 0, arrstrFileName);

	m_wSelect_World_Bar_X			= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_WORLD_BAR_X", 0, arrstrFileName) + m_wWorld_List_X - 7;
	m_wSelect_World_Bar_Y			= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_WORLD_BAR_Y", 0, arrstrFileName) + m_wWorld_List_Y - 15;

	m_wSelect_World_Name_Font_X		= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_WORLD_NAME_FONT_X", 0, arrstrFileName) + m_wWorld_List_X - 7;
	m_wSelect_World_Name_Font_Y		= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_WORLD_NAME_FONT_Y", 0, arrstrFileName) + m_wWorld_List_Y - 15;

	m_wSelect_World_Status_Font_X	= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_WORLD_STATUS_FONT_X", 0, arrstrFileName) + m_wWorld_List_X - 7;
	m_wSelect_World_Status_Font_Y	= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_WORLD_STATUS_FONT_Y", 0, arrstrFileName) + m_wWorld_List_Y - 15;

	m_wWorld_List_Show_Max			= (WORD)GetPrivateProfileInt(arrstrAppName, "WORLD_LIST_SHOW_MAX", 0, arrstrFileName);

	m_wChenel_List_X				= (WORD)GetPrivateProfileInt(arrstrAppName, "CHENEL_LIST_X", 0, arrstrFileName);
	m_wChenel_List_Y				= (WORD)GetPrivateProfileInt(arrstrAppName, "CHENEL_LIST_Y", 0, arrstrFileName);

	m_wSelect_Chenel_Bar_Interval_X	= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_CHENEL_BAR_INTERVAL_X", 0, arrstrFileName);
	m_wSelect_Chenel_Bar_Interval_Y	= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_CHENEL_BAR_INTERVAL_Y", 0, arrstrFileName);

	m_wSelect_Chenel_Bar_Chenel_X	= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_CHENEL_BAR_CHENEL_X", 0, arrstrFileName) + m_wChenel_List_X - 5;
	m_wSelect_Chenel_Bar_Chenel_Y	= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_CHENEL_BAR_CHENEL_Y", 0, arrstrFileName) + m_wChenel_List_Y - 16;

	m_wSelect_Chenel_Bar_Status_X	= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_CHENEL_BAR_STATUS_X", 0, arrstrFileName) + m_wChenel_List_X - 5;
	m_wSelect_Chenel_Bar_Status_Y	= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_CHENEL_BAR_STATUS_Y", 0, arrstrFileName) + m_wChenel_List_Y - 16;

	m_wSelect_Chenel_Bar_RaceInfo_X	= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_CHENEL_BAR_RACEINFO_X", 0, arrstrFileName) + m_wChenel_List_X - 5;
	m_wSelect_Chenel_Bar_RaceInfo_Y	= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_CHENEL_BAR_RACEINFO_Y", 0, arrstrFileName) + m_wChenel_List_Y - 16;

	m_wSelect_Chenel_Name_Font_X	= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_CHENEL_NAME_FONT_X", 0, arrstrFileName) + m_wChenel_List_X - 5;
	m_wSelect_Chenel_Name_Font_Y	= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_CHENEL_NAME_FONT_Y", 0, arrstrFileName) + m_wChenel_List_Y - 16;

	m_wSelect_Chenel_Status_Font_X	= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_CHENEL_STATUS_FONT_X", 0, arrstrFileName) + m_wChenel_List_X - 5;
	m_wSelect_Chenel_Status_Font_Y	= (WORD)GetPrivateProfileInt(arrstrAppName, "SELECT_CHENEL_STATUS_FONT_Y", 0, arrstrFileName) + m_wChenel_List_Y - 16;

	m_wChenel_List_Show_Max			= (WORD)GetPrivateProfileInt(arrstrAppName, "CHENEL_LIST_SHOW_MAX", 0, arrstrFileName);

	m_wChar_Bar_Start_View_X		= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_BAR_START_VIEW_X", 0, arrstrFileName) + m_wChenel_List_X - 5;
	m_wChar_Bar_Start_View_Y		= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_BAR_START_VIEW_Y", 0, arrstrFileName) + m_wChenel_List_Y - 16;

	m_wChar_Bar_Interval_X			= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_BAR_INTERVAL_X", 0, arrstrFileName);
	m_wChar_Bar_Interval_Y			= (WORD)GetPrivateProfileInt(arrstrAppName, "CHAR_BAR_INTERVAL_Y", 0, arrstrFileName);

	m_wPreve_Button_X				= (WORD)GetPrivateProfileInt(arrstrAppName, "PREVE_BUTTON_X", 0, arrstrFileName);
	m_wPreve_Button_Y				= (WORD)GetPrivateProfileInt(arrstrAppName, "PREVE_BUTTON_Y", 0, arrstrFileName);

	m_wNext_Button_X				= (WORD)GetPrivateProfileInt(arrstrAppName, "NEXT_BUTTON_X", 0, arrstrFileName);
	m_wNext_Button_Y				= (WORD)GetPrivateProfileInt(arrstrAppName, "NEXT_BUTTON_Y", 0, arrstrFileName);

	m_wChild_X						= (WORD)GetPrivateProfileInt(arrstrAppName, "CHILD_X", 0, arrstrFileName);
	m_wChild_Y						= (WORD)GetPrivateProfileInt(arrstrAppName, "CHILD_Y", 0, arrstrFileName);

	m_wAdult_X						= (WORD)GetPrivateProfileInt(arrstrAppName, "ADULT_X", 0, arrstrFileName);
	m_wAdult_Y						= (WORD)GetPrivateProfileInt(arrstrAppName, "ADULT_Y", 0, arrstrFileName);

	m_wViolence_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "VIOLENCE_X", 0, arrstrFileName);
	m_wViolence_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "VIOLENCE_Y", 0, arrstrFileName);

	m_wFear_X						= (WORD)GetPrivateProfileInt(arrstrAppName, "FEAR_X", 0, arrstrFileName);
	m_wFear_Y						= (WORD)GetPrivateProfileInt(arrstrAppName, "FEAR_Y", 0, arrstrFileName);

	m_wTex_Bar_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_BAR_X", 0, arrstrFileName);
	m_wTex_Bar_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_BAR_Y", 0, arrstrFileName);

	m_wAni_Mark_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "ANI_MARK_X", 0, arrstrFileName);
	m_wAni_Mark_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "ANI_MARK_Y", 0, arrstrFileName);

	m_wView_Race_Info_Image_X		= (WORD)GetPrivateProfileInt(arrstrAppName, "VIEW_RACE_INFO_IMAGE_X", 0, arrstrFileName)	+ m_wChenel_List_X - 5;
	m_wView_Race_Info_Image_Y		= (WORD)GetPrivateProfileInt(arrstrAppName, "VIEW_RACE_INFO_IMAGE_Y", 0, arrstrFileName)	+ m_wChenel_List_Y - 16;

	m_ptText_Line[LINE1].x			= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_LINE1_X", 0, arrstrFileName)	+ m_wTex_Bar_X;
	m_ptText_Line[LINE1].y			= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_LINE1_Y", 0, arrstrFileName)	+ m_wTex_Bar_Y;

	m_ptText_Line[LINE2].x			= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_LINE2_X", 0, arrstrFileName)	+ m_wTex_Bar_X;
	m_ptText_Line[LINE2].y			= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_LINE2_Y", 0, arrstrFileName)	+ m_wTex_Bar_Y;

	m_wPrimeum_Use_Day_Txt_X		= (WORD)GetPrivateProfileInt(arrstrAppName, "PRIMEUP_USE_DAY_TEXT_X", 0, arrstrFileName);
	m_wPrimeum_Use_Day_Txt_Y		= (WORD)GetPrivateProfileInt(arrstrAppName, "PRIMEUP_USE_DAY_TEXT_Y", 0, arrstrFileName);
	
	GetPrivateProfileString(arrstrAppName, "TEXT_LINE1", "", m_arrTextLine[LINE1], sizeof(m_arrTextLine[LINE1]), arrstrFileName);
	GetPrivateProfileString(arrstrAppName, "TEXT_LINE2", "", m_arrTextLine[LINE2], sizeof(m_arrTextLine[LINE2]), arrstrFileName);
}



/*-----------------------------------------------------------------------------
- ~C_VS_UI_SERVER_SELECT
-
-----------------------------------------------------------------------------*/
C_VS_UI_SERVER_SELECT::~C_VS_UI_SERVER_SELECT()
{
	g_UnregisterWindow(this);

	// !Window¸¦ ùÀú deleteÇØ¾ß ÇÑ´Ù.
	DeleteNew(m_pAnimationTimer);
	DeleteNew(m_pC_button_group);
#if	__CONTENTS(__USER_GRADE)
	DeleteNew(m_pC_use_grade);
#endif	//__USER_GRADE

	if(m_pserver_slayernum_barcount != NULL)
	{
		delete[] m_pserver_slayernum_barcount;
		m_pserver_slayernum_barcount		= NULL;
	}

	if(m_pserver_vampirenum_barcount != NULL)
	{
		delete[] m_pserver_vampirenum_barcount;
		m_pserver_vampirenum_barcount		= NULL;
	}

	if(m_pserver_ousters_barcount != NULL)
	{
		delete[] m_pserver_ousters_barcount;
		m_pserver_ousters_barcount		= NULL;
	}
}



//-----------------------------------------------------------------------------
// SetSelectBar()
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_SERVER_SELECT::SelectBarPos()
{
#if __CONTENTS(__SERVER_SELECT_REVEWAL)

	bool bHighResolution = g_pUserInformation->iResolution_x > 800;
	int ConvX = 0;	int ConvY = 0;
	
	/*
	if(g_pUserInformation->IsResolution1024)
	{
		if(m_bl_group)
		{
			m_server_x = 350+MODE1024_X;//+112;
			m_server_y = 191+MODE1024_Y;//+84;
		}
		else
		{
			m_server_x = 350+MODE1024_X-13;
			m_server_y = 191+MODE1024_Y+7;
		}
	}
	else
	{
		if(m_bl_group)
		{
			m_server_x = 350;//+112;
			m_server_y = 191;//+84;
		}
		else
		{
			m_server_x = 337;//+112;
			m_server_y = 198;//+84;
		}
	}*/
	
	if(m_bl_group)
	{
		m_server_x = 350+ConvX;//+112;
		m_server_y = 191+ConvY;//+84;
	}
	else
	{
		m_server_x = 350+ConvX-13;
		m_server_y = 191+ConvY+7;
	}	
#endif //__SERVER_SELECT_REVEWAL
}


//-----------------------------------------------------------------------------
// AcquireFirstSequence
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_SERVER_SELECT::AcquireFirstSequence()
{
}

//-----------------------------------------------------------------------------
// UnacquireMouseFocus
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_SERVER_SELECT::UnacquireMouseFocus()
{
	m_pC_button_group->UnacquireMouseFocus();
}

//-----------------------------------------------------------------------------
// WindowEventReceiver
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_SERVER_SELECT::WindowEventReceiver(id_t event)
{
}

//-----------------------------------------------------------------------------
// IsPixel
//
// 
//-----------------------------------------------------------------------------
bool C_VS_UI_SERVER_SELECT::IsPixel(int _x, int _y)
{
//	return m_image_spk.IsPixel(SCR2WIN_X(_x), SCR2WIN_Y(_y));
	return true;
}

//-----------------------------------------------------------------------------
// Run
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_SERVER_SELECT::Run(id_t id)
{
	switch (id)
	{
	case BACK_ID:
		gpC_base->SendMessage(UI_CLOSE_SERVER_SELECT, true);

		if(m_pserver_slayernum_barcount != NULL)
		{
			delete[] m_pserver_slayernum_barcount;
			m_pserver_slayernum_barcount		= NULL;
		}	

		if(m_pserver_vampirenum_barcount != NULL)
		{
			delete[] m_pserver_vampirenum_barcount;
			m_pserver_vampirenum_barcount		= NULL;
		}

		if(m_pserver_ousters_barcount != NULL)
		{
			delete[] m_pserver_ousters_barcount;
			m_pserver_ousters_barcount		= NULL;
		}
			break;

	case NEXT_ID:
	{
		bool validIndex		= false;
		bool validWorld		= false;
		bool validServer	= false;

		if(m_blAccep_World_Chenenl)
		{
			validIndex	= m_server_select_world > -1 && m_server_select_world < (int)m_server_name_world.size();
			validWorld	= m_blAccep_World_Chenenl && m_server_status_world[m_server_select_world] != STATUS_CLOSED;
		}
		else
		{
			validIndex	= m_server_select_chenel > -1 && m_server_select_chenel < (int)m_server_name_chenel.size();
			validServer = !m_blAccep_World_Chenenl && m_server_status_chenel[m_server_select_chenel] != STATUS_VERY_BAD;
		}

		if(m_blAccep_World_Chenenl)
		{
			m_wSelect_World_Click_Index	= m_server_select_world;
			if( validIndex && (validServer || validWorld)) 
			{
				if( m_blAccep_World_Chenenl == 0
#if __CONTENTS(__USER_GRADE)
					&& g_pUserInformation->IsUnderFifthteen
					&& !m_server_nonpk_chenel.at(m_server_select_chenel)
#endif //__USER_GRADE
#if __CONTENTS(__CONECT_LIMITER)
					&& m_server_id_world[m_server_select_world]	< STATUS_VERY_BAD
#endif
					)
				{
					gC_vs_ui.RunAskCheckToEnterServerDialog(
							C_VS_UI_ASK_DIALOG::ASK_CHECK_TO_ENTER_SERVER,
							MAKEWORD(m_blAccep_World_Chenenl,m_server_id_world[m_server_select_world]) );
				}
				else
				{
					gpC_base->SendMessage(UI_CONNECT_SERVER, m_blAccep_World_Chenenl, m_server_id_world[m_server_select_world]);
				}
			}
		}
		else
		{
			if( validIndex && (validServer || validWorld)) 
			{
				if( m_blAccep_World_Chenenl == 0
#if __CONTENTS(__USER_GRADE)
					&& g_pUserInformation->IsUnderFifthteen
					&& !m_server_nonpk_chenel.at(m_server_select_chenel)
#endif //__USER_GRADE
#if __CONTENTS(__CONECT_LIMITER)
					&& m_server_status_chenel[m_server_select_chenel]	== STATUS_VERY_BAD
#endif
					)
				{
					gC_vs_ui.RunAskCheckToEnterServerDialog(
							C_VS_UI_ASK_DIALOG::ASK_CHECK_TO_ENTER_SERVER,
							MAKEWORD(m_bl_group,m_server_id_chenel[m_server_select_chenel]) );
				}
				else
				{
					gpC_base->SendMessage(UI_CONNECT_SERVER, m_bl_group, m_server_id_chenel[m_server_select_chenel]);
				}
			}
		}
	}
	break;

	case SCROLL_UP_ID:
		if(m_scroll > 0)
			m_scroll--;
		EMPTY_MOVE;
		break;

	case SCROLL_DOWN_ID:
		if(m_server_name_chenel.size() > 12 && m_scroll < m_server_name_chenel.size()-12)
			m_scroll++;
		EMPTY_MOVE;
		break;
	}
}

/*-----------------------------------------------------------------------------
- MouseControl
-
-----------------------------------------------------------------------------*/
bool C_VS_UI_SERVER_SELECT::MouseControl(UINT message, int _x, int _y)
{
//	_x-=x;_y-=y;
	Window::MouseControl(message, _x, _y);

	m_pC_button_group->MouseControl(message, _x, _y);

//	static char server_status_string[50];
	
	int	iWorldServerFocusHeight		= 0;
	int	iWorldServerFocusWidth		= 0;
	int	iWorldFocusIndex			= 0;

	int	iChenelServerFocusHeight	= 0;
	int	iChenelServerFocusWidth		= 0;
	int	iChenelFocusIndex			= 0;

	WORD	wWorld_Scop_Start_X	= 0;
	WORD	wWorld_Scop_Start_Y	= 0;
	WORD	wWorld_Scop_End_X	= 0;
	WORD	wWorld_Scop_End_Y	= 0;

	WORD	wChenel_Scop_Start_X	= 0;
	WORD	wChenel_Scop_Start_Y	= 0;
	WORD	wChenel_Scop_End_X	= 0;
	WORD	wChenel_Scop_End_Y	= 0;

	iWorldServerFocusWidth		= m_wSelect_World_Bar_Interval_X;
	iWorldServerFocusHeight		= m_wSelect_World_Bar_Interval_Y;

	iChenelServerFocusWidth		= m_wSelect_Chenel_Bar_Interval_X;
	iChenelServerFocusHeight	= m_wSelect_Chenel_Bar_Interval_Y;

	switch (message)
	{
		case M_MOVING:
			m_focused_help = HELP_DEFAULT;
			m_focus_server = -1;

			if((_x != m_iOldMousePoint_X || _y != m_iOldMousePoint_Y))
			{
				m_iOldMousePoint_X	= _x;
				m_iOldMousePoint_Y	= _y;

				if(m_blAccep_World_Chenenl == false)
					m_blKeybord_OR_Mouse_Input = false;
			}

			for(iWorldFocusIndex = 0; iWorldFocusIndex < m_server_name_world.size(); iWorldFocusIndex++)
			{
				wWorld_Scop_Start_X	= m_wSelect_World_Bar_X;
				wWorld_Scop_Start_Y	= m_wSelect_World_Bar_Y + (m_wSelect_World_Bar_Interval_Y * iWorldFocusIndex);

				wWorld_Scop_End_X	= m_wSelect_World_Bar_X + iWorldServerFocusWidth;
				wWorld_Scop_End_Y	= m_wSelect_World_Bar_Y + (m_wSelect_World_Bar_Interval_Y * iWorldFocusIndex) + iWorldServerFocusHeight;

				if(wWorld_Scop_Start_X	<= _x	&&	wWorld_Scop_End_X >= _x &&
					wWorld_Scop_Start_Y <= _y	&&	wWorld_Scop_End_Y >= _y
					&& m_blKeybord_OR_Mouse_Input == false)
				{
					m_focus_server			= iWorldFocusIndex;
					m_server_select_world	= iWorldFocusIndex;
					
//					m_bl_group				= true;
					m_blAccep_World_Chenenl	= TRUE;			
				}
			}

			for(iChenelFocusIndex = 0; iChenelFocusIndex < m_server_name_chenel.size(); iChenelFocusIndex++)
			{
				wChenel_Scop_Start_X	= m_wSelect_Chenel_Bar_Chenel_X;
				wChenel_Scop_Start_Y	= m_wSelect_Chenel_Bar_Chenel_Y + (m_wSelect_Chenel_Bar_Interval_Y * iChenelFocusIndex);

				wChenel_Scop_End_X		= m_wSelect_Chenel_Bar_Chenel_X + iChenelServerFocusWidth;
				wChenel_Scop_End_Y		= m_wSelect_Chenel_Bar_Chenel_Y + (m_wSelect_Chenel_Bar_Interval_Y * iChenelFocusIndex) + iChenelServerFocusHeight;

				if(wChenel_Scop_Start_X	<= _x	&&	wChenel_Scop_End_X >= _x &&
					wChenel_Scop_Start_Y <= _y	&&	wChenel_Scop_End_Y >= _y
					&& m_blKeybord_OR_Mouse_Input == false)
				{
					m_focus_server				= iChenelFocusIndex;
					m_server_select_chenel		= iChenelFocusIndex;

					m_blAccep_World_Chenenl				= FALSE;
				}
			}

			if(m_bl_scrolling)
			{
				if(m_server_name_chenel.size() > 12)
				{
					m_bl_scrolling = true;
					m_scroll = (m_server_name_chenel.size()-12)*(min(SCROLL_HEIGHT, max(0, (_y - SCROLL_Y))) + SCROLL_HEIGHT/(m_server_name_chenel.size()-12)/2)/SCROLL_HEIGHT;
				}
			}
			break;

		case M_LEFTBUTTON_DOWN:
			m_blKeybord_OR_Mouse_Input	= false;	//Å¬¸¯ÀÌ µÈ »êÅÂ¿¡¼­¸¸ ¸¶¿ì½º¿¡°Ô ¼±ÅÃ ÇÒ ¼ö ÀÖ´Â ±ÇÇÑÀ» ÁØ´Ù.

			if(m_focus_server != -1 
#if __CONTENTS(__CONECT_LIMITER)
				&& (m_server_status[m_server_select] < STATUS_VERY_BAD)
#endif
				)
			{
//				m_server_select = m_focus_server;
//				Run(NEXT_ID);

				if(m_blAccep_World_Chenenl && m_blKeybord_OR_Mouse_Input == false)
				{
					if(m_server_select_world_prev != m_server_select_world)
					{
						m_server_select_world_prev	=	m_server_select_world; 
		
//						if(m_server_status_world[m_server_select_world] == STATUS_OPENED)
//							gpC_base->SendMessage(UI_CONNECT_SERVER, true, m_server_id_world[m_server_select_world]);
					}
				}
				else
				{
//					if(m_server_status_chenel[m_server_select_chenel] == STATUS_OPENED)
//						gpC_base->SendMessage(UI_CONNECT_SERVER, false, m_server_id_chenel[m_server_select_chenel]);
				}
				Run(NEXT_ID);
			}
			break;

		case M_LEFTBUTTON_UP:
			m_bl_scrolling = false;
			break;

		case M_RIGHTBUTTON_DOWN:
			break;

		case M_RIGHTBUTTON_UP:
			break;

		case M_WHEEL_UP:
			Run(SCROLL_UP_ID);
			break;

		case M_WHEEL_DOWN:
			Run(SCROLL_DOWN_ID);
			break;
	}

	return true;
}

/*-----------------------------------------------------------------------------
- KeyboardControl
-
-----------------------------------------------------------------------------*/
void C_VS_UI_SERVER_SELECT::KeyboardControl(UINT message, UINT key, long extra)
{
	switch(message)
	{
	case WM_KEYDOWN:
		m_blKeybord_OR_Mouse_Input	= true;

		switch(key)
		{
		case VK_ESCAPE:
			Run(BACK_ID);
			break;

		case VK_RETURN:
#if __CONTENTS(__CONECT_LIMITER)
		if (m_server_status[m_server_select] < STATUS_VERY_BAD)
#endif
			{
				Run(NEXT_ID);
			}
			break;

		case VK_UP:
			if(m_blAccep_World_Chenenl)
			{
				if(m_server_select_world > 0)
					m_server_select_world--;
			}
			else
			{
				if(m_server_select_chenel > 0)
					m_server_select_chenel--;
			}

			break;

		case VK_DOWN:
			if(m_blAccep_World_Chenenl)
			{
				if(m_server_select_world < (int)m_server_name_world.size()-1)
					m_server_select_world++;
			}
			else
			{
				if(m_server_select_chenel < (int)m_server_name_chenel.size()-1)
					m_server_select_chenel++;
			}
			break;

		case VK_LEFT:
			m_blAccep_World_Chenenl	= TRUE;
			break;

		case VK_RIGHT:
			m_blAccep_World_Chenenl	= FALSE;
			break;
		}
		break;
	}
}


void C_VS_UI_SERVER_SELECT::ShowButtonName(C_VS_UI_EVENT_BUTTON *p_button)
{
	switch(p_button->GetID())
	{
	case BACK_ID:
		p_button->x	= m_wPreve_Button_X;
		p_button->y	= m_wPreve_Button_Y;
		m_focused_help = HELP_BACK;
		g_PrintColorStr(p_button->x + 29, 	p_button->y + 7, "ÉÏÒ»²½", gpC_base->m_title_menu_pi, RGB_WHITE);
		break;
	case NEXT_ID:
		p_button->x	= m_wNext_Button_X;
		p_button->y	= m_wNext_Button_Y;
		m_focused_help = HELP_NEXT;
		g_PrintColorStr(p_button->x + 29, 	p_button->y + 7, "ÏÂÒ»²½", gpC_base->m_title_menu_pi, RGB_WHITE);
		break;
	}
}

//-----------------------------------------------------------------------------
// ShowButtonWidget
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_SERVER_SELECT::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{
//	int index = p_button->m_image_index;
	
	switch(p_button->GetID())
	{
	case BACK_ID:
		p_button->x	= m_wPreve_Button_X;
		p_button->y	= m_wPreve_Button_Y;
		m_focused_help = HELP_BACK;
		break;
	case NEXT_ID:
		p_button->x	= m_wNext_Button_X;
		p_button->y	= m_wNext_Button_Y;
		m_focused_help = HELP_NEXT;
		break;
	}

	m_image_hays_spk.BltLocked(p_button->x, p_button->y, p_button->m_image_index);

	if(p_button->GetFocusState())
	{
		if(p_button->m_alpha >= 31)
			p_button->m_alpha = 0;	
	
		m_image_hays_spk.BltLockedAlpha(p_button->x, p_button->y, p_button->m_image_index-1, p_button->m_alpha);
	}



}

///////////////////////////////////////////////////////////////////////////////
// SetServerDefault
//
///////////////////////////////////////////////////////////////////////////////
void C_VS_UI_SERVER_SELECT::SetServerList(LPSTR *name, int *id, int *status, int size, int default_id, bool *nonpk, WORD *pwSlayer, WORD *pwVampire, WORD *pwOusters)
{
	m_server_name_chenel.clear();
	m_server_id_chenel.clear();
	m_server_status_chenel.clear();
	m_server_nonpk_chenel.clear();
	m_server_slayernum_chenel.clear();
	m_server_vampirenum_chenel.clear();
	m_server_oustersenum_chenel.clear();

	if(m_bl_group	== true)
	{
		m_server_name_world.clear();
		m_server_id_world.clear();
		m_server_status_world.clear();
		m_server_nonpk_world.clear();

		m_server_size	= size;			//Ã¤³ÎÀÇ °³¼ö

		for(int i = 0; i < size; i++)
		{
			m_server_name_world.push_back(name[i]);
			m_server_id_world.push_back(id[i]);
			m_server_status_world.push_back(status[i]);
			if(pwSlayer != NULL && pwSlayer != NULL && pwSlayer != NULL)
			{
				m_server_slayernum_chenel.push_back(pwSlayer[i]);
				m_server_vampirenum_chenel.push_back(pwVampire[i]);
				m_server_oustersenum_chenel.push_back(pwOusters[i]);
			}
			if(id[i] == default_id)
			{
				m_server_select_world = i;
				m_wSelect_World_Click_Index	= i;
				if(i >= 12)
					m_scroll = i - 12;
			}

			if(nonpk != NULL)
				m_server_nonpk_chenel.push_back(nonpk[i]);
		}
			m_blAccep_World_Chenenl	= TRUE;
	}
	else
	{
#if __CONTENTS(__15_PVP_INHIBITION)
		m_server_size	= size;			//Ã¤³ÎÀÇ °³¼ö
		int GoreLevelChenelNum = 0;
		int i;
		for(i = 0; i < size; i++)
		{
			if(nonpk == NULL)
			{
				for(int i = 0; i < 12; ++i)
					nonpk[i] = false;
			}
			if((g_pUserInformation->IsUnderFifthteen && nonpk[i])
				|| !g_pUserInformation->IsUnderFifthteen)
			{
				m_server_name_chenel.push_back(name[i]);
				m_server_id_chenel.push_back(id[i]);
				m_server_status_chenel.push_back(status[i]);
				if(pwSlayer != NULL && pwSlayer != NULL && pwSlayer != NULL)
				{
					m_server_slayernum_chenel.push_back(pwSlayer[i]);
					m_server_vampirenum_chenel.push_back(pwVampire[i]);
					m_server_oustersenum_chenel.push_back(pwOusters[i]);
				}
				if(id[i] == default_id)
				{
					m_server_select_chenel = i;
					if(i >= 12)
						m_scroll = i - 12;
				}
				m_server_nonpk_chenel.push_back(nonpk[i]);
				if(nonpk[i])
				{
					++GoreLevelChenelNum;
				}
			}
		}
		if((g_pUserInformation->IsUnderFifthteen && nonpk[i]))
		{
			m_server_size = GoreLevelChenelNum;
		}
		m_blAccep_World_Chenenl	= FALSE;
#else
		m_server_size	= size;			//Ã¤³ÎÀÇ °³¼ö
		for(int i = 0; i < size; i++)
		{
			m_server_name_chenel.push_back(name[i]);
			m_server_id_chenel.push_back(id[i]);
			m_server_status_chenel.push_back(status[i]);
			if(pwSlayer != NULL && pwSlayer != NULL && pwSlayer != NULL)
			{
				m_server_slayernum_chenel.push_back(pwSlayer[i]);
				m_server_vampirenum_chenel.push_back(pwVampire[i]);
				m_server_oustersenum_chenel.push_back(pwOusters[i]);
			}
			if(id[i] == default_id)
			{
				m_server_select_chenel = i;
				if(i >= 12)
					m_scroll = i - 12;
			}

			if(nonpk != NULL)
				m_server_nonpk_chenel.push_back(nonpk[i]);
		}
		m_blAccep_World_Chenenl	= FALSE;
#endif //__15_PVP_INHIBITION
	}
	CharBarCount();

	if(m_bl_group	== true)	//trueÀÏ ¶§°¡ ¿ùµå ¼±ÅÃ
	{
		if(m_server_id_world.size())
		{
			if(m_server_select_world < 0)
				m_server_select_world	= 0;

			gpC_base->SendMessage(UI_CONNECT_SERVER, true, m_server_id_world[m_server_select_world]); 
		}
	}
}

/*-----------------------------------------------------------------------------
- Show
-
-----------------------------------------------------------------------------*/
void C_VS_UI_SERVER_SELECT::Show()
{
	
	Init_TitleUIInterface_InfInfo();
	
	gpC_base->m_p_DDSurface_back->FillSurface(0);

	if(gpC_base->m_p_DDSurface_back->Lock())
	{
		GroupView();
		if(m_pAnimationTimer->IsTimeLimit())
		{
			if(m_bAniArphaUp)
			{
				++m_aniArpha;
				if(m_aniArpha == 31)
				{
					m_bAniArphaUp = false;
				}
			}
			else
			{
				--m_aniArpha;
				if(m_aniArpha == 1)
				{
					m_bAniArphaUp = true;
				}
			}
			
		}
		SelectBarPos();

//#if __CONTENTS(__USER_GRADE)
//#if __CONTENTS(!__IMI_INTERFACE)
//		if(!g_pUserInformation->GoreLevel)
//			m_pC_use_grade->BltLocked(m_wChild_X, m_wChild_Y, CHILD);
//		else
//#endif
//			m_pC_use_grade->BltLocked(m_wAdult_X, m_wAdult_Y, ADULT);
//		m_pC_use_grade->BltLocked(m_wViolence_X, m_wViolence_Y, VIOLENCE);
//		m_pC_use_grade->BltLocked(m_wFear_X, m_wFear_Y, FEAR);
//#endif // __USER_GRADE
		
		SelectBarView();
		CharBoxView();

		ChannelCharBarView();

		///m_image_hays_spk.BltLocked(m_wTex_Bar_X, m_wTex_Bar_Y, TEXT_BAR); //modify by hays 2013 / 3 / 21
		//m_image_spk.BltLocked(m_wAni_Mark_X, m_wAni_Mark_Y, ANI_MARK);
		//m_image_hays_spk.BltLocked(m_wView_Race_Info_Image_X, m_wView_Race_Info_Image_Y, VIEW_RACE_INFO); modify by hays 2013 / 3/ 21

		gpC_base->m_p_DDSurface_back->Unlock();
	}

	//¼­¹ö¸®½ºÆ® Ç¥½Ã
	g_FL2_GetDC();

	ServerNameView();
	ServerNameViewWorld();

//	g_PrintColorStr(m_ptText_Line[LINE1].x, 	m_ptText_Line[LINE1].y,
//					m_arrTextLine[LINE1], gpC_base->m_title_menu_pi, RGB_WHITE);
//	g_PrintColorStr(m_ptText_Line[LINE2].x, 	m_ptText_Line[LINE2].y,
//					m_arrTextLine[LINE2], gpC_base->m_title_menu_pi, RGB_WHITE);

	g_PrintColorStr(m_ptText_Line[LINE1].x, 	m_ptText_Line[LINE1].y,
					(*g_pGameStringTable)[UI_TITLE_UI_RENEWAL_SERVERSELECT_TEXT1], gpC_base->m_title_menu_pi, RGB_WHITE);
	g_PrintColorStr(m_ptText_Line[LINE2].x, 	m_ptText_Line[LINE2].y,
					(*g_pGameStringTable)[UI_TITLE_UI_RENEWAL_SERVERSELECT_TEXT2], gpC_base->m_title_menu_pi, RGB_WHITE);
	
	char szBuffer[256]	= {NULL,};

	if (g_LeftPremiumDays == 0xFFFE)
	{
		sprintf( szBuffer, (*g_pGameStringTable)[UI_STRING_MESSAGE_NOT_PREMIUM_USER].GetString() );
	}
	else if (g_LeftPremiumDays == 0xFFFC && g_PayType == 4 )
	{
		sprintf( szBuffer, (*g_pGameStringTable)[UI_STRING_MESSAGE_DEFERRED_PAYMENT_NOTICE].GetString() );
	}
	else if ( g_LeftPremiumDays > 0 && g_PayType == 1)
	{
		if(g_bFamily)
			sprintf( szBuffer, (*g_pGameStringTable)[UI_STRING_MESSAGE_LEFT_FAMILY_DAYS].GetString(), g_LeftPremiumDays );
		else
			sprintf( szBuffer, (*g_pGameStringTable)[UI_STRING_MESSAGE_LEFT_PREMIUM_DAYS].GetString(), g_LeftPremiumDays );
	}
	else if (g_LeftPremiumDays == 0 && g_PayType == 1)
	{
		if(g_bFamily)
			sprintf( szBuffer, (*g_pGameStringTable)[UI_STRING_MESSAGE_EXPIRE_FAMILY_TODAY].GetString() );	
		else
			sprintf( szBuffer, (*g_pGameStringTable)[UI_STRING_MESSAGE_EXPIRE_PREMIUM_SERVICE_TODAY].GetString() );	
	}
	else if ( g_LeftPremiumDays > 0 && g_PayType == 3)
	{
		sprintf( szBuffer, (*g_pGameStringTable)[UI_STRING_MESSAGE_LEFT_PREMIUM_PAYZONE_DAYS].GetString(), g_LeftPremiumDays );
	}
	else if (g_LeftPremiumDays == 0 && g_PayType == 3)
	{
		sprintf( szBuffer, (*g_pGameStringTable)[UI_STRING_MESSAGE_LEFT_PREMIUM_PAYZONE_DAYS].GetString() );	
	}

	int szBufferLen = g_GetStringWidth(szBuffer, gpC_base->m_desc_menu_pi.hfont)/2;

	m_pC_button_group->ShowButtonName();

//	if( g_LeftPremiumDays != 0xFFFF )
//	{
//		if(g_pUserInformation->IsResolution1024)
//		{
//			g_PrintColorStr((1024 / 2) - szBufferLen, m_wPrimeum_Use_Day_Txt_Y, szBuffer, gpC_base->m_desc_menu_pi, RGB_WHITE );
//		}
//		else
//		{
//			g_PrintColorStr((800 / 2) - szBufferLen, m_wPrimeum_Use_Day_Txt_Y, szBuffer, gpC_base->m_desc_menu_pi, RGB_WHITE );
//		}
//	}

	g_FL2_ReleaseDC();

//#ifdef CONVERT_1024_768
//	ShowDesc(112,84);
//#else
//	ShowDesc();
//#endif
	
	SHOW_WINDOW_ATTR;
}



/*-----------------------------------------------------------------------------
- GroupShow
-
-----------------------------------------------------------------------------*/
void C_VS_UI_SERVER_SELECT::GroupView()
{
	bool bHighResolution = g_pUserInformation->iResolution_x > 800;
	if(bHighResolution)
	{
		if(g_pUserInformation->iResolution_x <= 1024)
			m_title_hays_spk.BltLocked( (g_pUserInformation->iResolution_x - m_title_hays_spk.GetWidth(1)) / 2, 
			(g_pUserInformation->iResolution_y - m_title_hays_spk.GetHeight(1)) / 2,  1) ;
		else
		{
			if(g_pUserInformation->iResolution_y < 960)
			//	m_title_spk.BltLocked( (g_pUserInformation->iResolution_x - m_title_spk.GetWidth(2)) / 2, 
			//	(g_pUserInformation->iResolution_y - m_title_spk.GetHeight(2)) / 2 , 2) ;
			//else if(g_pUserInformation->iResolution_y < 1024)
				m_title_hays_spk.BltLocked( (g_pUserInformation->iResolution_x - m_title_hays_spk.GetWidth(2)) / 2, 
				(g_pUserInformation->iResolution_y - m_title_hays_spk.GetHeight(2)) / 2 , 2) ;
			else
				m_title_hays_spk.BltLocked( (g_pUserInformation->iResolution_x - m_title_hays_spk.GetWidth(3)) / 2, 
				(g_pUserInformation->iResolution_y - m_title_hays_spk.GetHeight(3)) / 2 , 3) ;
		}
	}
	else
		m_title_hays_spk.BltLocked( (g_pUserInformation->iResolution_x - m_title_hays_spk.GetWidth(0)) / 2, 
		(g_pUserInformation->iResolution_y - m_title_hays_spk.GetHeight(0)) / 2 , 0) ;
	
	m_image_hays_spk.BltLocked(m_wWorld_List_X, m_wWorld_List_Y, TITLE_WORLD);
	m_image_hays_spk.BltLocked(m_wChenel_List_X, m_wChenel_List_Y, TITLE_SERVER);
	m_pC_button_group->Show();
}


/*-----------------------------------------------------------------------------
- OutputServerName
-
-----------------------------------------------------------------------------*/
void C_VS_UI_SERVER_SELECT::ServerNameView()
{

	char server_status_string[30];
	memset((char*) server_status_string, NULL, sizeof(server_status_string));
	COLORREF statusColor = RGB_WHITE;

	if(m_server_status_chenel.size())
	{
		for(int i = 0; i < min(m_server_status_chenel.size(), 12); i++)
		{
			switch(m_server_status_chenel[i+m_scroll])
			{
			case STATUS_VERY_GOOD:
				strcpy(server_status_string, (*g_pGameStringTable)[UI_STRING_MESSAGE_SERVER_STATUS_VERY_GOOD].GetString());
				break;
			
			case STATUS_GOOD:
				strcpy(server_status_string,(*g_pGameStringTable)[UI_STRING_MESSAGE_SERVER_STATUS_GOOD].GetString());
				break;
				
			case STATUS_NORMAL:
				strcpy(server_status_string, (*g_pGameStringTable)[UI_STRING_MESSAGE_SERVER_STATUS_NORMAL].GetString());
				break;
				
			case STATUS_BAD:
				strcpy(server_status_string, (*g_pGameStringTable)[UI_STRING_MESSAGE_SERVER_STATUS_BAD].GetString());
				break;
				
			case STATUS_VERY_BAD:
				strcpy(server_status_string, (*g_pGameStringTable)[UI_STRING_MESSAGE_SERVER_STATUS_VERY_BAD].GetString());
				break;

			case STATUS_DOWN:
				statusColor = RGB_RED;
				strcpy(server_status_string, (*g_pGameStringTable)[UI_STRING_MESSAGE_SERVER_STATUS_CLOSE].GetString());
				break;
			}

			if(i+m_scroll == m_server_select_chenel && (m_blAccep_World_Chenenl == FALSE))
			{
				g_PrintColorStr(m_wSelect_Chenel_Name_Font_X, (m_wSelect_Chenel_Bar_Interval_Y * i) + m_wSelect_Chenel_Name_Font_Y,
								m_server_name_chenel[i+m_scroll].c_str(), gpC_base->m_title_menu_pi, RGB(255,255,0));
					
				g_PrintColorStr(m_wSelect_Chenel_Status_Font_X,	(m_wSelect_Chenel_Bar_Interval_Y * i) + m_wSelect_Chenel_Status_Font_Y,
								server_status_string, gpC_base->m_title_menu_pi, RGB(255,255,0));
			}
			else
			{
				g_PrintColorStr(m_wSelect_Chenel_Name_Font_X, (m_wSelect_Chenel_Bar_Interval_Y * i) + m_wSelect_Chenel_Name_Font_Y,
								m_server_name_chenel[i+m_scroll].c_str(), gpC_base->m_title_menu_pi, RGB_WHITE);
					
				g_PrintColorStr(m_wSelect_Chenel_Status_Font_X, (m_wSelect_Chenel_Bar_Interval_Y * i) + m_wSelect_Chenel_Status_Font_Y,
								server_status_string, gpC_base->m_title_menu_pi, RGB_WHITE);
			}
		}
	}
}


void C_VS_UI_SERVER_SELECT::ServerNameViewWorld()
{
	char server_status_string[30];
	memset((char*) server_status_string, NULL, sizeof(server_status_string));
	COLORREF statusColor = RGB_WHITE;

	for(int i = 0; i < min(m_server_name_world.size(), 12); i++)
	{
//		if(m_bl_group)
		{
			switch(m_server_status_world[i+m_scroll])
			{
			case STATUS_OPENED:
				strcpy(server_status_string,(*g_pGameStringTable)[UI_STRING_MESSAGE_SERVER_STATUS_OPEN].GetString());
				break;
	
			case STATUS_CLOSED:
				statusColor = RGB_RED;
				strcpy(server_status_string, (*g_pGameStringTable)[UI_STRING_MESSAGE_SERVER_STATUS_CLOSE].GetString());
				break;
			}
		}
		PrintInfo	serverFont = gpC_base->m_title_menu_pi;
#if __CONTENTS(__JAPAN_UI)
		serverFont = gpC_base->m_small_pi;
#endif //__JAPAN_UI
		g_PrintColorStr(m_wSelect_World_Name_Font_X,	m_wSelect_World_Name_Font_Y + (m_wSelect_World_Bar_Interval_Y * i), 
						m_server_name_world[i+m_scroll].c_str(),	serverFont, RGB_WHITE);
		g_PrintColorStr(m_wSelect_World_Status_Font_X,	m_wSelect_World_Status_Font_Y + (m_wSelect_World_Bar_Interval_Y * i), 
						server_status_string, serverFont, RGB_WHITE);

		if(i+m_scroll == m_wSelect_World_Click_Index)
		{
			g_PrintColorStr(m_wSelect_World_Name_Font_X,	m_wSelect_World_Name_Font_Y + (m_wSelect_World_Bar_Interval_Y * i), 
							m_server_name_world[i+m_scroll].c_str(),	serverFont, RGB(128,255,00));
			g_PrintColorStr(m_wSelect_World_Status_Font_X,	m_wSelect_World_Status_Font_Y + (m_wSelect_World_Bar_Interval_Y * i), 
							server_status_string, serverFont, RGB(128,255,00));
		}
		
		if(i+m_scroll == m_server_select_world && m_blAccep_World_Chenenl)
		{
			g_PrintColorStr(m_wSelect_World_Name_Font_X,	m_wSelect_World_Name_Font_Y + (m_wSelect_World_Bar_Interval_Y * i), 
							m_server_name_world[i+m_scroll].c_str(),	serverFont, RGB(255,255,00));
			g_PrintColorStr(m_wSelect_World_Status_Font_X,	m_wSelect_World_Status_Font_Y + (m_wSelect_World_Bar_Interval_Y * i), 
							server_status_string, serverFont, RGB(255,255,00));
		}
	}
}


/*-----------------------------------------------------------------------------
- SelectBarView
-
-----------------------------------------------------------------------------*/
void C_VS_UI_SERVER_SELECT::SelectBarView()
{
	if(m_server_status_world.size())
	{
		for(int i = 0; i < min(m_server_status_world.size(), 12); i++)
		{
			if(i+m_scroll == m_server_select_world && m_blAccep_World_Chenenl)
			{
				m_image_hays_spk.BltLocked(m_wSelect_World_Bar_X, 
										m_wSelect_World_Bar_Y + (m_wSelect_World_Bar_Interval_Y * i), WORLD_SELECT_BAR);
			}
		}
	}
	
	if(m_server_status_chenel.size())
	{
		for(int i = 0; i < min(m_server_status_chenel.size(), 12); i++)
		{
			if(i+m_scroll == m_server_select_chenel && (m_blAccep_World_Chenenl == FALSE))
			{
				m_image_hays_spk.BltLocked(m_wSelect_Chenel_Bar_Chenel_X, 
										m_wSelect_Chenel_Bar_Chenel_Y + (m_wSelect_Chenel_Bar_Interval_Y * i), CHENEL_SELECT_BAR_CHENEL);
				m_image_hays_spk.BltLocked(m_wSelect_Chenel_Bar_Status_X, 
										m_wSelect_Chenel_Bar_Status_Y + (m_wSelect_Chenel_Bar_Interval_Y * i), CHENEL_SELECT_BAR_STATUS);
				m_image_hays_spk.BltLocked(m_wSelect_Chenel_Bar_RaceInfo_X, 
										m_wSelect_Chenel_Bar_RaceInfo_Y + (m_wSelect_Chenel_Bar_Interval_Y * i), CHENEL_SELECT_BAR_RACEINFO);
			}
		}
	}
}


/*-----------------------------------------------------------------------------
- CharBoxView
-
-----------------------------------------------------------------------------*/
void C_VS_UI_SERVER_SELECT::CharBoxView()
{
#if __CONTENTS(__SERVER_SELECT_REVEWAL)
//	const int	iSlayerBoxPos_X		= 713;
//	const int	iSlayerBoxPos_Y		= 167;
//	const int	iVampiresBoxPos_X	= 713;
//	const int	iVampiresBoxPos_Y	= 187;
//	const int	iOustersBoxPos_X	= 713;
//	const int	iOustersBoxPos_Y	= 207;
//
//	if(g_pUserInformation->IsResolution1024)
//	{
//		if(!m_bl_group)
//		{
//			m_image_spk.BltLocked(iSlayerBoxPos_X + MODE1024_X, iSlayerBoxPos_Y + MODE1024_Y, SLAYER_BOX);
//			m_image_spk.BltLocked(iVampiresBoxPos_X + MODE1024_X, iVampiresBoxPos_Y + MODE1024_Y, VAMPIRES_BOX);
//			m_image_spk.BltLocked(iOustersBoxPos_X + MODE1024_X, iOustersBoxPos_Y + MODE1024_Y, OUSTERS_BOX);
//		}
//	}
//	else
//	{
//		if(!m_bl_group)
//		{
//			m_image_spk.BltLocked(iSlayerBoxPos_X, iSlayerBoxPos_Y, SLAYER_BOX);
//			m_image_spk.BltLocked(iVampiresBoxPos_X, iVampiresBoxPos_Y, VAMPIRES_BOX);
//			m_image_spk.BltLocked(iOustersBoxPos_X, iOustersBoxPos_Y, OUSTERS_BOX);
//		}
//	}
#endif //__SERVER_SELECT_REVEWAL
}


/*-----------------------------------------------------------------------------
- CharBarView
-
-----------------------------------------------------------------------------*/
void C_VS_UI_SERVER_SELECT::CharBarView(int iBarCount, int iCharConnectBar, int iChannel, int iCharBarLine)
{
	const int	iBarWidth				= m_image_hays_spk.GetWidth(iCharConnectBar);
	const int	iBarHeight				= m_image_hays_spk.GetHeight(iCharConnectBar);

	const int	iCharBarSpace_X			= 2;
	const int	iCharBarSpace_Y			= m_image_hays_spk.GetHeight(iCharConnectBar);

	int			iBarX					= 0;
	int			iBarY					= 0;
	int			iCharIndex				= iCharBarLine;

	if(!m_bl_group)
	{
		for(int i = 1; i <= iBarCount; i++)
		{
			iBarX	= m_wChar_Bar_Start_View_X + (m_wChar_Bar_Interval_X * i) + (iBarWidth * i);
			iBarY	= m_wChar_Bar_Start_View_Y + (m_wChar_Bar_Interval_Y * iCharBarLine) + (iBarHeight * iCharBarLine) + 
						(m_wSelect_Chenel_Bar_Interval_Y * iChannel);

			m_image_hays_spk.BltLocked(iBarX, iBarY, iCharConnectBar);
		}
	}
	if (g_pUserInformation->attrOperator.GetAttr(OPERATORTYPE_MACADDRESS))
	{
		int __n_slayer_num = (int)m_server_slayernum_chenel[iChannel];
		int __n_vampire_num = (int)m_server_vampirenum_chenel[iChannel];
		int __n_ousters_num = (int)m_server_oustersenum_chenel[iChannel];
		int __n_total_num = __n_slayer_num + __n_vampire_num + __n_ousters_num;
		char __sz_user_count[16] = {0};
		sprintf (__sz_user_count,"%d¸í",__n_total_num);
		int __n_string_width = g_GetStringWidth(__sz_user_count,gpC_base->m_user_id_pi.hfont);
		g_FL2_GetDC();
		g_PrintColorStr(m_wChar_Bar_Start_View_X+(87/2)-(__n_string_width/2),m_wChar_Bar_Start_View_Y+(iChannel*34)+5,__sz_user_count,gpC_base->m_user_id_pi,RGB_WHITE);	
		g_FL2_ReleaseDC();
	}
}



void	C_VS_UI_SERVER_SELECT::CharBarCount()
{
#if __CONTENTS(__SERVER_SELECT_REVEWAL)	
	m_server_slayernumtotal		= 0;
	m_server_vampirenumtotal	= 0;
	m_server_oustersnumtotal	= 0;

	if(m_server_slayernum_chenel.size() > 0)
	{
		if(m_pserver_slayernum_barcount==NULL)
			m_pserver_slayernum_barcount	= new WORD[m_server_slayernum_chenel.size()];
	}
	if(m_server_vampirenum_chenel.size() > 0)
	{
		if(m_pserver_vampirenum_barcount==NULL)
			m_pserver_vampirenum_barcount	= new WORD[m_server_vampirenum_chenel.size()];
	}
	if(m_server_oustersenum_chenel.size() > 0)
	{
		if(m_pserver_ousters_barcount==NULL)
			m_pserver_ousters_barcount		= new WORD[m_server_oustersenum_chenel.size()];
	}
	int i;
	for( i = 0; i < m_server_slayernum_chenel.size(); i++)
	{
		m_server_slayernumtotal				+= m_server_slayernum_chenel[i];
		m_pserver_slayernum_barcount[i]		= m_server_slayernum_chenel[i];
	}
	for(i = 0; i < m_server_vampirenum_chenel.size(); i++)
	{
		m_server_vampirenumtotal			+= m_server_vampirenum_chenel[i];
		m_pserver_vampirenum_barcount[i]	= m_server_vampirenum_chenel[i];
	}
	for(i = 0; i < m_server_oustersenum_chenel.size(); i++)
	{
		m_server_oustersnumtotal			+= m_server_oustersenum_chenel[i];
		m_pserver_ousters_barcount[i]		= m_server_oustersenum_chenel[i];
	}

	for(i = 0; i < m_server_slayernum_chenel.size(); i++)
	{
		m_pserver_slayernum_barcount[i] =	(WORD)(((float)m_server_slayernum_chenel[i] / (float)m_server_slayernumtotal)*10);
		if(m_pserver_slayernum_barcount[i] < 10)
		{
			m_pserver_slayernum_barcount[i] += 1;
		}
	}

	for(i = 0; i < m_server_vampirenum_chenel.size(); i++)
	{
		m_pserver_vampirenum_barcount[i] =	(WORD)(((float)m_server_vampirenum_chenel[i] / (float)m_server_vampirenumtotal)*10);
		if(m_pserver_vampirenum_barcount[i] < 10)
		{
			m_pserver_vampirenum_barcount[i] += 1;
		}
	}

	for(i = 0; i < m_server_oustersenum_chenel.size(); i++)
	{
		m_pserver_ousters_barcount[i] =		(WORD)(((float)m_server_oustersenum_chenel[i] / (float)m_server_oustersnumtotal)*10);
		if(m_pserver_ousters_barcount[i] < 10)
		{
			m_pserver_ousters_barcount[i] += 1;
		}
	}
#endif //__SERVER_SELECT_REVEWAL
}



void	C_VS_UI_SERVER_SELECT::ChannelCharBarView()
{
#if __CONTENTS(__SERVER_SELECT_REVEWAL)
	if(m_pserver_slayernum_barcount != NULL && m_pserver_vampirenum_barcount != NULL && m_pserver_ousters_barcount != NULL)
	{
		for(int i = 0; i < m_server_size; i++)
		{
			CharBarView(10, BLACK_BAR, i, 0);	//ºí·¢¹Ù´Â ¹«Á¶°Ç 10°³		
			CharBarView(10, BLACK_BAR, i, 1);	//ºí·¢¹Ù´Â ¹«Á¶°Ç 10°³		
			CharBarView(10, BLACK_BAR, i, 2);	//ºí·¢¹Ù´Â ¹«Á¶°Ç 10°³		
			CharBarView(m_pserver_slayernum_barcount[i], SLAYER_BAR, i, 0);	
			CharBarView(m_pserver_vampirenum_barcount[i], VAMPIRES_BAR, i, 1);	
			CharBarView(m_pserver_ousters_barcount[i], OUSTERS_BAR, i, 2);	
		}
	}
#endif //__SERVER_SELECT_REVEWAL
}



/*-----------------------------------------------------------------------------
- S_SLOT
-
-----------------------------------------------------------------------------*/
void S_SLOT::Init()
{
	bl_set			= false; // slotÀÌ ¼³Á¤µÇ¾ú´Â°¡?
	bl_female		= false;
	bl_drained		= false; //ÈíÇ÷µÈ »óÅÂÀÎ°¡?

	ZeroMemory(&man_info,	sizeof(MAN_INFO));
	
	helmet_color	= 0;
	trouser_color	= 0;
	coat_color		= 0;
	skin_color		= 0;
	hair_color		= 0;
	left_color		= 0;
	right_color		= 0;

	sz_name.clear();
	sz_guild_name.clear();
	
	alignment		= static_cast<ALIGNMENT>(0);
	alignment_num	= 0;
	level			= 0;
	STR_PURE		= 0;
	STR_CUR			= 0;
	STR_MAX			= 0;
	DEX_PURE		= 0;
	DEX_CUR			= 0;
	DEX_MAX			= 0;
	INT_PURE		= 0;
	INT_CUR			= 0;
	INT_MAXX		= 0;
	STR_EXP_REMAIN	= 0;
	DEX_EXP_REMAIN	= 0;
	INT_EXP_REMAIN	= 0;
	EXP_REMAIN		= 0;
	DAM				= 0;	// max
	DAM2			= 0;	// min
	SILVER_DAM		= 0;	// max
	SILVER_DAM2		= 0;	// min
	CHANGE_VAMPIRE	= 0;	// ¹ìÆÄÀÌ¾î·Î º¯ÇÏ´Â ³²Àº ½Ã°£ ºÐ
	DEFENSE			= 0;
	PROTECTION		= 0;
	TOHIT			= 0;
	HP				= 0;
	MP				= 0;
	HP_MAX			= 0;
	MP_MAX			= 0;
	SILVER_HP		= 0;
	
	DOMAIN_SWORD	= 0;
	DOMAIN_BLADE	= 0;
	DOMAIN_GUN		= 0;
	DOMAIN_HEAL		= 0;
	DOMAIN_ENCHANT	= 0;
	
	FAME			= 0;
	
	bonus_point		= 0; // vampire only
	skill_point		= 0; // ousters only
	
	AttackBloodBurstPoint	= 0;
	DefenseBloodBurstPoint	= 0;
	PartyBloodBurstPoint	= 0;
	MagicRemainSec			= 0; 
	MagicRemainTick			= 0; 
	
	STATUS.clear();
	
	GUILD_ID		= 0;
	GUILD_GRADE		= 0;
	
	WS				= 0;
	WeaponSpeed		= 0;
	GRADE			= 0;
	GRADE_EXP_REMAIN	= 0;
	
	Race			= RACE_SLAYER;
	
	ElementalFire	= 0;
	ElementalWater	= 0;
	ElementalEarth	= 0;
	ElementalWind	= 0;
	
	m_SMS_Charge	= 0;
	m_Powerjjang_Point	= 0;
	m_AdvancementLevel	= 0;	// ÀüÁ÷ ·¹º§ 

	SlayerAdvancedStr = 0;
	SlayerAdvancedDex = 0;
	SlayerAdvancedInt = 0;
#if __CONTENTS(__CONTRIBUTE_SYSTEM)
	ContributePoint = 0;
#endif //__CONTRIBUTE_SYSTEM
}



/*-----------------------------------------------------------------------------
- C_VS_UI_LOGIN
-
-----------------------------------------------------------------------------*/
C_VS_UI_LOGIN::C_VS_UI_LOGIN()
{
	g_RegisterWindow(this);

	AttrTopmost(true);
	AttrKeyboardControl(true);

	//by svi
	bool bHighResolution = g_pUserInformation->iResolution_x > 800;
	int ConvX = 0;	int ConvY = 0;
	
	if(bHighResolution)
	{
		m_pC_login_spk = new C_SPRITE_PACK(SPK_LOGIN_1024);

		if(g_pUserInformation->iResolution_x > 1024)
		{	
			// 1280*720
			if(g_pUserInformation->iResolution_y < 960)
			{	ConvX = 128;	ConvY = -24;	}
			// 1280*960
			else if(g_pUserInformation->iResolution_y < 1024)
			{	ConvX = 128;	ConvY = 96;		}
			// 1280*1024
			else
			{	ConvX = 128;	ConvY = 128;	}
		}
	}
	else	
		m_pC_login_spk = new C_SPRITE_PACK(SPK_LOGIN);
	
/*	if(g_pUserInformation->IsResolution1024)
		m_pC_login_spk = new C_SPRITE_PACK(SPK_LOGIN_1024);
	else	m_pC_login_spk = new C_SPRITE_PACK(SPK_LOGIN);  */
	

//	m_pC_login_menu_default.Open(SPK_LOGIN_MENU_DEFAULT);
	m_pC_login_menu.Open(SPK_LOGIN_MENU);

	Set(/*154, 180*/g_pUserInformation->iResolution_x/2 - m_pC_login_spk->GetWidth()/2, g_pUserInformation->iResolution_y/2 - m_pC_login_spk->GetHeight()/2, m_pC_login_spk->GetWidth(), m_pC_login_spk->GetHeight());
	
//#ifdef CONVERT_1024_768
	//Set(/*154, 180*/RESOLUTION_X/2 - m_pC_login_spk->GetWidth()/2, RESOLUTION_Y/2 - m_pC_login_spk->GetHeight()/2, m_pC_login_spk->GetWidth(), m_pC_login_spk->GetHeight());
//#else
	//Set(/*154, 180*/400 - m_pC_login_spk->GetWidth()/2, 300 - m_pC_login_spk->GetHeight()/2-57, m_pC_login_spk->GetWidth(), m_pC_login_spk->GetHeight());
//#endif
	

	m_pC_button_group = new ButtonGroup(this);

	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(118 + ConvX, 123 + ConvY, m_pC_login_menu.GetWidth(NEW_ID), m_pC_login_menu.GetHeight(NEW_ID), NEW_ID, this, PUSHED_NEW_ID, 1));
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(52 + ConvX, 123 + ConvY, m_pC_login_menu.GetWidth(OK), m_pC_login_menu.GetHeight(OK), OK, this, PUSHED_OK, 1));
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(156 + ConvX, 28 + ConvY, m_pC_login_menu.GetWidth(CANCEL), m_pC_login_menu.GetHeight(CANCEL), CANCEL, this, PUSHED_CANCEL, 1));


	// LineEditorVisual setting...
	m_lev_id.SetPosition(x+LOGIN_ID_X + ConvX, y+LOGIN_ID_Y + ConvY);
	
	//if(g_pUserInformation->IsNetmarble)
	if(g_pUserInformation->IsNetmarbleLogin)
		m_lev_id.SetByteLimit(12);
	else
		m_lev_id.SetByteLimit(12);

	m_lev_password.SetPosition(x+LOGIN_PASSWORD_X + ConvX, y+LOGIN_PASSWORD_Y + ConvY);
	m_lev_password.PasswordMode(true);

	//if(g_pUserInformation->IsNetmarble)
	if(g_pUserInformation->IsNetmarbleLogin)
		m_lev_password.SetByteLimit(12);
	else
		m_lev_password.SetByteLimit(10);

	Attach(&m_lev_id);
	Attach(&m_lev_password);

//	m_bFirst = true;
}

//-----------------------------------------------------------------------------
// ReadySend
//
// ºñ¾îÀÖÁö¾Ê°í ÀÔ·ÂÀÌ ´Ù µÇ¾úÀ¸¸é true¸¦ ¹ÝÈ¯ÇÏ°í ±×·¸Áö ¾ÊÀ¸¸é false¸¦ ¹ÝÈ¯ÇÑ´Ù.
//-----------------------------------------------------------------------------
bool C_VS_UI_LOGIN::ReadySend()
{
	if (m_lev_id.Size() > 0 && m_lev_password.Size() > 0)
		return true;
	
	return false;

	/*if (gC_font.GetStringBuffer()->str.length() == 0)
		return false;

	if (m_e_ip == ID)
	{
		if (m_string_line_PASSWORD.length() == 0)
			return false;
	}
	else
	{
		if (m_string_line_ID.length() == 0)
			return false;
	}

	return true;*/
}

/*-----------------------------------------------------------------------------
- ~C_VS_UI_LOGIN
-
-----------------------------------------------------------------------------*/
C_VS_UI_LOGIN::~C_VS_UI_LOGIN()
{
	g_UnregisterWindow(this);

	DeleteNew(m_pC_button_group);
	DeleteNew(m_pC_login_spk);
}

//-----------------------------------------------------------------------------
// AcquireFirstSequence
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_LOGIN::AcquireFirstSequence()
{
	
}

//-----------------------------------------------------------------------------
// ChangeFocus
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_LOGIN::ChangeFocus()
{
	if (m_lev_id.IsAcquire())
	{
		if(m_lev_id.Size() == 0)
			m_lev_id.AddString(m_lev_id_backup.c_str());
		m_lev_password.Acquire();
	}
	else
	{
		char * p_temp = NULL;
		g_Convert_DBCS_Ascii2SingleByte(m_lev_id.GetString(), m_lev_id.Size(), p_temp);
		if(p_temp == NULL)
		{
			m_lev_id_backup = "";
		}
		else
		{
			m_lev_id_backup = p_temp;
			DeleteNewArray(p_temp);
		}
		m_lev_id.Acquire();
		m_lev_id.EraseAll();
	}
}

void C_VS_UI_LOGIN::UnacquireMouseFocus()
{
	m_pC_button_group->UnacquireMouseFocus();
}

void C_VS_UI_LOGIN::ShowButtonDescription(C_VS_UI_EVENT_BUTTON * p_button)
{
}

void C_VS_UI_LOGIN::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{
	if (p_button->GetFocusState() && p_button->GetPressState())
	{
		m_pC_login_menu.BltLocked(x+p_button->x, y+p_button->y, p_button->m_image_index);
	}
	
//	m_pC_login_menu_default.Blt(p_button->x, y, p_button->GetID());

	else if (p_button->m_alpha)
		m_pC_login_menu.BltLockedAlpha(x+p_button->x, y+p_button->y, p_button->GetID(), p_button->m_alpha);
	
}

//-----------------------------------------------------------------------------
// WindowEventReceiver
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_LOGIN::WindowEventReceiver(id_t event)
{
}

//-----------------------------------------------------------------------------
// IsPixel
//
// 
//-----------------------------------------------------------------------------
bool C_VS_UI_LOGIN::IsPixel(int _x, int _y)
{
	return m_pC_login_spk->IsPixel(SCR2WIN_X(_x), SCR2WIN_Y(_y));
}

//-----------------------------------------------------------------------------
// Process
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_LOGIN::Process()
{
	m_pC_button_group->Process();
}

//-----------------------------------------------------------------------------
// Start
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_LOGIN::Start()
{
	PI_Processor::Start();

	AttrKeyboardControl(true);

	gpC_window_manager->AppearWindow(this);
	m_pC_button_group->Init();

	m_lev_id.Acquire();
	m_lev_id.EraseAll();
	m_lev_password.EraseAll();



	if(strlen(g_pUserOption->BackupID) > 0)
	{
		m_lev_id.AddString(g_pUserOption->BackupID);
		ChangeFocus();
	}
}

//-----------------------------------------------------------------------------
// Finish
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_LOGIN::Finish()
{
	PI_Processor::Finish();

	gpC_window_manager->DisappearWindow(this);
}

//-----------------------------------------------------------------------------
// Run
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_LOGIN::Run(id_t id)
{
	switch (id)
	{
		case OK:
			if (ReadySend() == true)
			{
				SendLoginToClient();
			}
			else
			{
				g_msg_wrong_id_password->Start();
			}
			break;

		case CANCEL:
			Finish();
			break;

		case NEW_ID:
			//g_msg_not_available_menu->Start();
			Finish();
			gpC_base->SendMessage(UI_RUN_NEWUSER_REGISTRATION);
			break;
	}
}

/*-----------------------------------------------------------------------------
- MouseControl
-
-----------------------------------------------------------------------------*/
bool C_VS_UI_LOGIN::MouseControl(UINT message, int _x, int _y)
{
	Window::MouseControl(message, _x, _y);
	_x-=x; _y-=y;

	m_pC_button_group->MouseControl(message, _x, _y);

	switch (message)
	{
		case M_LEFTBUTTON_DOWN:
		case M_LB_DOUBLECLICK:
			{
				Rect id_rt(LOGIN_ID_X, LOGIN_ID_Y, 130, 23);
				Rect pass_rt(LOGIN_PASSWORD_X, LOGIN_PASSWORD_Y, 130, 23);
				if (id_rt.IsInRect(_x, _y))
				{
					if (!m_lev_id.IsAcquire())
						ChangeFocus();
				}
				else if (pass_rt.IsInRect(_x, _y))
				{
					if (!m_lev_password.IsAcquire())
						ChangeFocus();
				}
			}
	}

	return true;
}

//-----------------------------------------------------------------------------
// NextFocus
//
// ID or Password µÑ Áß ¾î´À ÇÏ³ª°¡ ÀÔ·ÂÀÌ ÀüÇô ¾ø¾ú´Ù¸é, ´ÙÀ½ÀÇ ±×°÷À¸·Î ÀÌµ¿ÇÑ´Ù.
//
// `ºñ¾îÀÖ´Â °÷ÀÌ ¾øÀ¸¸é true¸¦ ¹ÝÈ¯ÇÑ´Ù.
//-----------------------------------------------------------------------------
/*
bool C_VS_UI_LOGIN::NextFocus()
{
	// gC_font ³»ºÎ¿¡¼­ tabÀº ¾Æ¹«°Íµµ ¾Æ´Ï´Ù.
	gC_font.ForceShowCursor();

	if (m_e_ip == ID)
	{
		m_e_ip = PASSWORD;
		
		m_string_line_ID.erase();
		m_string_line_ID = gC_font.GetStringBuffer()->str;

		gC_font.SetInputLine(m_string_line_PASSWORD.c_str());
	}
	else
	{
		m_e_ip = ID;

		m_string_line_PASSWORD.erase();
		m_string_line_PASSWORD = gC_font.GetStringBuffer()->str;

		gC_font.SetInputLine(m_string_line_ID.c_str());
	}

	// no empty? - ¸¶Áö¸·¿¡ °Ë»çÇÑ´Ù.
	if (m_string_line_ID.length() > 0 && m_string_line_PASSWORD.length() > 0)
		return true;

	return false;
}*/

//-----------------------------------------------------------------------------
// SendLoginToClient
//
// ID/Password¸¦ Client·Î º¸³½´Ù.
//-----------------------------------------------------------------------------
void C_VS_UI_LOGIN::SendLoginToClient()
{
	// copy from input line.
/*	if (m_e_ip == ID)
	{
		m_string_line_ID.erase();
		m_string_line_ID += gC_font.GetStringBuffer()->str;
	}
	else
	{
		m_string_line_PASSWORD.erase();
		m_string_line_PASSWORD += gC_font.GetStringBuffer()->str;
	}
*/
	//
	// ¹Ýµå½Ã staticÀ¸·Î ÇÏ°í member¸¦ login check°¡ ³¡³ª°í delete ÇØÁØ´Ù.
	//
	static LOGIN S_login; 
	//S_login.sz_id = (char *)m_string_line_ID.c_str();
	//S_login.sz_password = (char *)m_string_line_PASSWORD.c_str();
	g_Convert_DBCS_Ascii2SingleByte(m_lev_id.GetString(), m_lev_id.Size(), S_login.sz_id);
	g_Convert_DBCS_Ascii2SingleByte(m_lev_password.GetString(), m_lev_password.Size(), S_login.sz_password);
	strcpy(g_pUserOption->BackupID, S_login.sz_id);

	gpC_base->SendMessage(UI_LOGIN, 0, 0, &S_login);
}

/*-----------------------------------------------------------------------------
- KeyboardControl
- Log-In ID¿Í Password¸¦ ÀÔ·Â¹Þ´Â´Ù.
-----------------------------------------------------------------------------*/
void C_VS_UI_LOGIN::KeyboardControl(UINT message, UINT key, long extra)
{

	//bool focus_end = false;
	//if (message == WM_KEYDOWN && key == VK_RETURN)
	//	focus_end = NextFocus();

	//gpC_base->SelectFont(FONT_SLAYER);

	//if (key != VK_RETURN)
	//	gC_font.KeyInput(message, key, extra);

//	if(message == WM_CHAR && m_bFirst)
//	{
//		m_bFirst = false;
//		return;
//	}


	Window::KeyboardControl(message, key, extra);

	switch (message)
	{
		case WM_KEYDOWN:
			// 
			// input position º¯°æ.
			//
			if (key == VK_TAB)
			{
				//NextFocus();
				ChangeFocus();
			}
			else if (key == VK_ESCAPE) // cancel!
			{
				Finish();
			}
			else if (key == VK_RETURN) // ok
			{
				//if (focus_end) // ºñ¾î ÀÖ´Â °÷ÀÌ ¾øÀ¸¸é send!
				//{

				if (ReadySend() == true)
					SendLoginToClient();
				else
					//NextFocus();
					ChangeFocus();
				//}
			}
			break;
	}
}

extern HWND g_hWnd;
/*-----------------------------------------------------------------------------
- Show
-
-----------------------------------------------------------------------------*/
void C_VS_UI_LOGIN::Show()
{
//	if(m_lev_password.IsAcquire())
//	{
//		DWORD conversion, sentence;
//		ImmGetConversionStatus(ImmGetContext(g_hWnd), &conversion, &sentence);
//		if(conversion)
//		{
//			conversion = 0;
//			ImmSetConversionStatus(ImmGetContext(g_hWnd), conversion, sentence);
//		}
//	}

//	m_pC_login_spk->BltAlpha(x, y+20, SHADOW, 22);
	if(gpC_base->m_p_DDSurface_back->Lock())
	{
		m_pC_login_spk->BltLocked(x, y);		
		m_pC_button_group->Show();
		gpC_base->m_p_DDSurface_back->Unlock();
	}
/*
	// login ¹®ÀÚ¿­ Ãâ·Â.
	if (gpC_base->m_p_DDSurface_back->Lock())
	{
		S_SURFACEINFO	surfaceinfo;
		SetSurfaceInfo(&surfaceinfo, gpC_base->m_p_DDSurface_back->GetDDSD());

		gpC_base->SelectFont(FONT_SLAYER);

		// cursor´Â ÇöÀç ÀÔ·Â line¿¡¸¸ ÀÖ°Ô ÇØ¾ß ÇÑ´Ù.
		if (m_e_ip == ID)
			gC_font.Update(&surfaceinfo, x+LOGIN_ID_X, y+LOGIN_ID_Y, WHITE);
		else
			gC_font.PrintStringNoConvert(&surfaceinfo, m_string_line_ID.c_str(), x+LOGIN_ID_X, y+LOGIN_ID_Y, WHITE);

		gC_font.PasswordMode();
		if (m_e_ip == PASSWORD)
			gC_font.Update(&surfaceinfo, x+LOGIN_PASSWORD_X, y+LOGIN_PASSWORD_Y, WHITE);
		else
			gC_font.PrintStringNoConvert(&surfaceinfo, m_string_line_PASSWORD.c_str(), x+LOGIN_PASSWORD_X, y+LOGIN_PASSWORD_Y, WHITE);
		gC_font.NoPasswordMode();

		gpC_base->m_p_DDSurface_back->Unlock();
	}*/

	Window::ShowWidget();

	SHOW_WINDOW_ATTR;
}

//-----------------------------------------------------------------------------
// NewCharacterCreateOk
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_TITLE::NewCharacterCreateOk()
{
	m_pC_char_manager->NewCharacterCreateOk();
}

void	C_VS_UI_TITLE::PopupNetmarbleAgreementMessage()
{
	m_pC_char_manager->PopupNetmarbleAgreementMessage();
}

void ExecF_Use_AskCheckToEnterServer(C_VS_UI_DIALOG * p_this_dialog, id_t id)
{
	C_VS_UI_ASK_DIALOG *p_ask_dlg = static_cast<C_VS_UI_ASK_DIALOG *>( p_this_dialog );

	switch (id)
	{
	case DIALOG_EXECID_OK:
		{
			DWORD value		= p_ask_dlg->GetdwTemporayValue() ;
			BOOL group		= LOBYTE(value);
			int	servernum	= HIBYTE(value);
			gpC_base->SendMessage(UI_CONNECT_SERVER, group, servernum);

		}
		break;
	case DIALOG_EXECID_CANCEL:
	case DIALOG_EXECID_EXIT:
		{
			gpC_base->SendMessage(UI_NONPK_SERVER_USE);
		}
		break;
	}
	
//	gC_vs_ui.AcquireChatting();
}

void	C_VS_UI_TITLE::RunAskCheckToEnterServerDialog(int AskType ,  int value)
{
	if (m_pC_use_askCheckToEnterServer != NULL)
	{
		DeleteNew(m_pC_use_askCheckToEnterServer);
	}
	//ExecF_Use_AskItem 
	// center
	if(AskType >= C_VS_UI_ASK_DIALOG::MAX_ASK_DIALOG_TYPE)
		return;
	m_pC_use_askCheckToEnterServer = new C_VS_UI_ASK_DIALOG(
		-1, -1, 3, 1, ExecF_Use_AskCheckToEnterServer, DIALOG_CANCEL | DIALOG_OK, 
		(C_VS_UI_ASK_DIALOG::TYPE_ASK_DIALOG)AskType, value ) ; //0);	// by sigi
	
	assert(m_pC_use_askCheckToEnterServer != NULL);
	
	m_pC_use_askCheckToEnterServer->Start();
}

//-----------------------------------------------------------------------------
// StartCharacterManager
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_TITLE::StartCharacterManager(bool back)
{
	Finish();
	m_pC_server_select->Finish();

	m_pC_char_manager->Start(back);
}

//-----------------------------------------------------------------------------
// StartCharacterManager
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_TITLE::StartServerSelect(bool bGroup)
{
	Finish();

	m_pC_login->Finish();

	m_pC_char_manager->Finish();

	m_pC_server_select->Finish();

	m_pC_server_select->Start(bGroup);
}


//-----------------------------------------------------------------------------
// DeleteCharacter
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_TITLE::DeleteCharacter(int slot)
{
	m_pC_char_manager->DeleteCharacter(slot);
}

//-----------------------------------------------------------------------------
// ClearAllCharacter
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_TITLE::ClearAllCharacter()
{
	m_pC_char_manager->ClearAllCharacter();
}

void A(C_VS_UI_DIALOG * p, id_t id)
{
	int z = 0;
}



//-----------------------------------------------------------------------------
// C_VS_UI_TITLE
//
// 
//-----------------------------------------------------------------------------
C_VS_UI_TITLE::C_VS_UI_TITLE()
{
	g_RegisterWindow(this);
	
#ifndef _LIB
#endif
	
	AttrKeyboardControl(true);

	m_pC_char_manager = new C_VS_UI_CHAR_MANAGER;
	m_pC_server_select = new C_VS_UI_SERVER_SELECT;

	m_pC_login = new C_VS_UI_LOGIN;

	bool bHighResolution = g_pUserInformation->iResolution_x > 800;
	
/*	if(g_pUserInformation->IsResolution1024)
		m_title_spk.Open(SPK_TITLE_1024);
	else
		m_title_spk.Open(SPK_TITLE); */

	m_title_spk.Open(SPK_TITLE);

	//add by hays
	m_title_new_spk.Open(SPK_NEW_TITLE);

	m_title_menu_default.Open(SPK_TITLE_MENU_DEFAULT);


	if(bHighResolution)
	{
		if(g_pUserInformation->iResolution_x <= 1024)
			Set( (g_pUserInformation->iResolution_x - m_title_new_spk.GetWidth(1)) / 2, (g_pUserInformation->iResolution_y - m_title_new_spk.GetHeight(1)) / 2, m_title_new_spk.GetWidth(1), m_title_new_spk.GetHeight(1) );
		else // if(g_pUserInformation->iResolution_x > 1024)
		{
			if(g_pUserInformation->iResolution_y < 960)
				Set( (g_pUserInformation->iResolution_x - m_title_new_spk.GetWidth(2)) / 2, (g_pUserInformation->iResolution_y - m_title_new_spk.GetHeight(2)) / 2, m_title_new_spk.GetWidth(2), m_title_new_spk.GetHeight(2) );
			else if(g_pUserInformation->iResolution_y < 1024)
				Set( (g_pUserInformation->iResolution_x - m_title_new_spk.GetWidth(3)) / 2, (g_pUserInformation->iResolution_y - m_title_new_spk.GetHeight(3)) / 2, m_title_new_spk.GetWidth(3), m_title_new_spk.GetHeight(3) );
			else
				Set( (g_pUserInformation->iResolution_x - m_title_new_spk.GetWidth(4)) / 2, (g_pUserInformation->iResolution_y - m_title_new_spk.GetHeight(4)) / 2, m_title_new_spk.GetWidth(4), m_title_new_spk.GetHeight(4) );
		}
	}
	else
	{
		Set( (g_pUserInformation->iResolution_x - m_title_new_spk.GetWidth(0)) / 2, 
			(g_pUserInformation->iResolution_y - m_title_new_spk.GetHeight(0)) / 2, 
				m_title_new_spk.GetWidth(0), m_title_new_spk.GetHeight(0) );
	}
	

#if	__CONTENTS(__USER_GRADE)
	m_pC_use_grade = new C_SPRITE_PACK(SPK_USE_GRADE);
#endif	//__USER_GRADE
//	const InterfaceInformation *pSkin = &g_pSkinManager->Get( SkinManager::TITLE );
	m_pC_button_group = new ButtonGroup(this);

	int iStartRangeX = 0, iStartRangeY  = g_pUserInformation->iResolution_y - m_title_spk.GetHeight(1);

	int	offsetX = 0;
	
	if(bHighResolution)
	{
		offsetX = 86;
	}
	else
	{
		offsetX = 70;
	}

	m_wAni_Mark_X		= 0;
	m_wAni_Mark_Y		= 0;

	m_wButton_Layout_X	= 0;
	m_wButton_Layout_Y	= 0;

	m_wID_Edit_X		= 0;
	m_wID_Edit_Y		= 0;

	m_wPW_Edit_X		= 0;
	m_wPW_Edit_Y		= 0;

	m_wGame_Run_X		= 0;
	m_wGame_Run_Y		= 0;

	m_wID_Create_X		= 0;
	m_wID_Create_Y		= 0;

	m_wOption_X			= 0;
	m_wOption_Y			= 0;

	m_wGame_Creaters_X	= 0;
	m_wGame_Creaters_Y	= 0;

	m_wGame_Exit_X		= 0;
	m_wGame_Exit_Y		= 0;

	Init_TitleUIInterface_InfInfo();
		
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_wGame_Run_X,	m_wGame_Run_Y, 	m_title_menu_default.GetWidth(CONNECT_HILIGHT), 
														m_title_menu_default.GetHeight(CONNECT_HILIGHT), CONNECT, this,CONNECT_HILIGHT));
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_wID_Create_X,	m_wID_Create_Y, m_title_menu_default.GetWidth(NEWID_HILIGHT), 
														m_title_menu_default.GetHeight(NEWID_HILIGHT), NEWID, this,NEWID_HILIGHT));
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_wOption_X, m_wOption_Y, m_title_menu_default.GetWidth(OPTION_HILIGHT),
														m_title_menu_default.GetHeight(OPTION_HILIGHT), OPTION, this,OPTION_HILIGHT));
#if __CONTENTS(!__IMI_INTERFACE)
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_wGame_Creaters_X,	m_wGame_Creaters_Y, m_title_menu_default.GetWidth(CREDIT_HILIGHT), 
														m_title_menu_default.GetHeight(CREDIT_HILIGHT), CREDIT, this,CREDIT_HILIGHT));
#endif //__IMI_INTERFACE
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(m_wGame_Exit_X, m_wGame_Exit_Y, m_title_menu_default.GetWidth(EXIT_HILIGHT), 
														m_title_menu_default.GetHeight(EXIT_HILIGHT), EXIT, this,EXIT_HILIGHT));

	m_pC_credit = NULL;
	m_pC_dialog = NULL;

	m_dw_prev_tickcount = GetTickCount();
	m_dw_millisec = 30;
	m_credit_scroll = 0;
	m_pC_use_askCheckToEnterServer = NULL ; 

	m_iWarmingTextIndex = rand()%2;

	// LineEditorVisual setting...
	if(false == g_pUserInformation->IsAutoLogIn &&
	   false == g_pUserInformation->IsNetmarbleLogin)
	{
		m_lev_id.SetPosition(m_wID_Edit_X,	m_wID_Edit_Y);
		
		if(g_pUserInformation->IsNetmarbleLogin)
			m_lev_id.SetByteLimit(12);
		else
			m_lev_id.SetByteLimit(12);
		
		m_lev_password.SetPosition(m_wPW_Edit_X,	m_wPW_Edit_Y);
		m_lev_password.PasswordMode(true);
		
		if(g_pUserInformation->IsNetmarbleLogin)
			m_lev_password.SetByteLimit(12);
		else
			m_lev_password.SetByteLimit(10);

#if __CONTENTS(__IMI_INTERFACE)
		m_lev_id.SetAbsWidth(80);
		m_lev_id.SetByteLimit(20);
#endif //__IMI_INTERFACE
#if __CONTENTS(__ID_PASSWORD)||__CONTENTS(__JAPAN_UI)
		m_lev_id.SetAbsWidth(80);
		m_lev_id.SetByteLimit(30);
		m_lev_password.SetAbsWidth(80);
		m_lev_password.SetByteLimit(20);
#endif	//__ID_PASSWORD
		
		Attach(&m_lev_id);
		Attach(&m_lev_password);
	}

	m_pAnimationTimer = new CTickTimer;
	m_pAnimationTimer->StartTimer(50, true);
	m_aniArpha = 31;
	m_bAniArphaUp = false;
}

float getPcent(WORD wA, WORD wM)
{
	float fA = (float)wA;
	float fM = (float)wM;

	float fRes = fA / fM;

	return fRes;
}

WORD getPcentData(WORD wA, WORD wS, WORD wD)
{
	float fPcent = getPcent(wA, wS);

	WORD data = fPcent * (float)wD;

	return data;
}


void	C_VS_UI_TITLE::Init_TitleUIInterface_InfInfo()
{
	char arrstrAppName[255]		= {NULL,};
	char arrstrFileName[255]	= {NULL,};

	GetCurrentDirectory(_MAX_PATH, arrstrFileName);	//ÇöÀç ½ÇÇà ÁßÀÎ ÆÄÀÏÀÇ °æ·Î¸¦ ¾ò´Â´Ù.

	bool bHighResolution = g_pUserInformation->iResolution_x > 800;

	int ConvX = 0;	int ConvY = 0;
		
	//if(bHighResolution)
	//{
	//	if(g_pUserInformation->iResolution_x <=1024)
	//		strcpy(arrstrAppName,"LOGIN_1024_768");
	//	else
	//	{
	//		// 1280*720
	//		if(g_pUserInformation->iResolution_y < 960)
	//			strcpy(arrstrAppName,"LOGIN_1280_720");
	//		// 1280*960
	//		else if(g_pUserInformation->iResolution_y < 1024)
	//			strcpy(arrstrAppName,"LOGIN_1280_960");
	//		// 1280*1024
	//		else
	//			strcpy(arrstrAppName,"LOGIN_1280_1024");
	//	}	
	//}
	//else
	strcpy(arrstrAppName,"LOGIN_800_600");
	

//	if(g_pUserInformation->IsNetmarbleLogin)
//	{
//		if(bHighResolution)
//			strcpy(arrstrAppName,"NET_LOGIN_1024_768");
//		else
//			strcpy(arrstrAppName,"NET_LOGIN_800_600");
//	}
//#ifdef __DESIGNED_ITEMMANIA
//	if(bHighResolution)
//		strcpy(arrstrAppName,"IMI_LOGIN_1024_768");
//	else
//		strcpy(arrstrAppName,"IMI_LOGIN_800_600");
//#endif //__DESIGNED_ITEMMANIA
	strcat(arrstrFileName, FILE_INFO_TITLE_UI);

	m_wAni_Mark_X				= (WORD)GetPrivateProfileInt(arrstrAppName, "ANI_MARK_X", 0, arrstrFileName);
	m_wAni_Mark_Y				= (WORD)GetPrivateProfileInt(arrstrAppName, "ANI_MARK_Y", 0, arrstrFileName);

	m_wButton_Layout_X			= (WORD)GetPrivateProfileInt(arrstrAppName, "BUTTON_LAYOUT_X", 0, arrstrFileName);
	m_wButton_Layout_Y			= (WORD)GetPrivateProfileInt(arrstrAppName, "BUTTON_LAYOUT_Y", 0, arrstrFileName);

	float fPcentX = 0.5f;//(float)m_wButton_Layout_X / 800.0;
	float fPcentY = 0.488f;//(float)m_wButton_Layout_Y / 600.0;

	float fOffX = getPcent(m_title_new_spk.GetWidth(BUTTON_LAYOUT_BUTTON), g_pUserInformation->iResolution_x);
	float fOffY = getPcent(m_title_new_spk.GetHeight(BUTTON_LAYOUT_BUTTON), g_pUserInformation->iResolution_y);


	m_wButton_Layout_X = (float)g_pUserInformation->iResolution_x * (fPcentX - fOffX*0.5f) ;
	m_wButton_Layout_Y = (float)g_pUserInformation->iResolution_y * (fPcentY - fOffY*0.5f) ;
	

	m_wID_Edit_X				= (WORD)GetPrivateProfileInt(arrstrAppName, "ID_EDIT_X", 0, arrstrFileName) + m_wButton_Layout_X;
	m_wID_Edit_Y				= (WORD)GetPrivateProfileInt(arrstrAppName, "ID_EDIT_Y", 0, arrstrFileName) + m_wButton_Layout_Y;

	m_wPW_Edit_X				= (WORD)GetPrivateProfileInt(arrstrAppName, "PW_EDIT_X", 0, arrstrFileName) + m_wButton_Layout_X;
	m_wPW_Edit_Y				= (WORD)GetPrivateProfileInt(arrstrAppName, "PW_EDIT_Y", 0, arrstrFileName) + m_wButton_Layout_Y;

	m_wGame_Run_X				= (WORD)GetPrivateProfileInt(arrstrAppName, "GAME_RUN_X", 0, arrstrFileName) + m_wButton_Layout_X;
	m_wGame_Run_Y				= (WORD)GetPrivateProfileInt(arrstrAppName, "GAME_RUN_Y", 0, arrstrFileName) + m_wButton_Layout_Y;

	m_wID_Create_X				= (WORD)GetPrivateProfileInt(arrstrAppName, "ID_CREATE_X", 0, arrstrFileName);
	m_wID_Create_Y				= (WORD)GetPrivateProfileInt(arrstrAppName, "ID_CREATE_Y", 0, arrstrFileName);

	fPcentX = 0.286;
	fPcentY = 0.838;

	m_wID_Create_X = fPcentX * g_pUserInformation->iResolution_x;
	m_wID_Create_Y = fPcentY * g_pUserInformation->iResolution_y;


	m_wOption_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "OPTION_X", 0, arrstrFileName);
	m_wOption_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "OPTION_Y", 0, arrstrFileName);

	m_wOption_X = getPcentData(m_wOption_X, 800, g_pUserInformation->iResolution_x);
	m_wOption_Y = getPcentData(m_wOption_Y, 600, g_pUserInformation->iResolution_y);

	m_wGame_Creaters_X			= (WORD)GetPrivateProfileInt(arrstrAppName, "GAME_CREATERS_X", 0, arrstrFileName);
	m_wGame_Creaters_Y			= (WORD)GetPrivateProfileInt(arrstrAppName, "GAME_CREATERS_Y", 0, arrstrFileName);

	m_wGame_Creaters_X = getPcentData(m_wGame_Creaters_X, 800, g_pUserInformation->iResolution_x);
	m_wGame_Creaters_Y = getPcentData(m_wGame_Creaters_Y, 600, g_pUserInformation->iResolution_y);

	m_wGame_Exit_X				= (WORD)GetPrivateProfileInt(arrstrAppName, "GAME_EXIT_X", 0, arrstrFileName);
	m_wGame_Exit_Y				= (WORD)GetPrivateProfileInt(arrstrAppName, "GAME_EXIT_Y", 0, arrstrFileName);

	m_wGame_Exit_X = getPcentData(m_wGame_Exit_X, 800, g_pUserInformation->iResolution_x);
	m_wGame_Exit_Y = getPcentData(m_wGame_Exit_Y, 600, g_pUserInformation->iResolution_y);

	m_wEffect_Warter_Light_X	= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_WARTER_LIGHT_X", 0, arrstrFileName);
	m_wEffect_Warter_Light_Y	= (WORD)GetPrivateProfileInt(arrstrAppName, "EFFECT_WARTER_LIGHT_Y", 0, arrstrFileName);

	m_wText_Image_X				= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_IMAGE_X", 0, arrstrFileName);
	m_wText_Image_Y				= (WORD)GetPrivateProfileInt(arrstrAppName, "TEXT_IMAGE_Y", 0, arrstrFileName);

	m_wChild_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "CHILD_X", 0, arrstrFileName);
	m_wChild_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "CHILD_Y", 0, arrstrFileName);

	m_wAdult_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "ADULT_X", 0, arrstrFileName);
	m_wAdult_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "ADULT_Y", 0, arrstrFileName);

	m_wViolence_X				= (WORD)GetPrivateProfileInt(arrstrAppName, "VIOLENCE_X", 0, arrstrFileName);
	m_wViolence_Y				= (WORD)GetPrivateProfileInt(arrstrAppName, "VIOLENCE_Y", 0, arrstrFileName);

	m_wFear_X					= (WORD)GetPrivateProfileInt(arrstrAppName, "FEAR_X", 0, arrstrFileName);
	m_wFear_Y					= (WORD)GetPrivateProfileInt(arrstrAppName, "FEAR_Y", 0, arrstrFileName);

	m_wWorningString_X			= (WORD)GetPrivateProfileInt(arrstrAppName, "WORNIN_STRING_X", 0, arrstrFileName);
	m_wWorningString_Y			= (WORD)GetPrivateProfileInt(arrstrAppName, "WORNIN_STRING_Y", 0, arrstrFileName);

	
	fPcentX = 0.5;
	
	fOffX = getPcent(332, g_pUserInformation->iResolution_x);
	//fOffY = getPcent(510, g_pUserInformation->iResolution_y);

	m_wWorningString_X = (float)g_pUserInformation->iResolution_x * (fPcentX - fOffX*0.5f) ;
	//m_wWorningString_Y = (float)g_pUserInformation->iResolution_y * (fPcentY - fOffY*0.5f) ;


	//m_wWorningString_X = getPcentData(m_wWorningString_X, 800, g_pUserInformation->iResolution_x);
	m_wWorningString_Y = getPcentData(m_wWorningString_Y, 600, g_pUserInformation->iResolution_y);


	if(false == g_pUserInformation->IsAutoLogIn &&
	   false == g_pUserInformation->IsNetmarbleLogin)
	{
		m_lev_id.SetPosition(m_wID_Edit_X,	m_wID_Edit_Y);
		m_lev_password.SetPosition(m_wPW_Edit_X, m_wPW_Edit_Y);
	}
}



//-----------------------------------------------------------------------------
// ~C_VS_UI_TITLE
//
// 
//-----------------------------------------------------------------------------
C_VS_UI_TITLE::~C_VS_UI_TITLE()
{
	g_UnregisterWindow(this);
	
#ifndef _LIB
//	DeleteNew(m_pC_dialog);
#endif

	//
	// !¸ÕÀú child WindowµéÀ» deleteÇØ¾ß ÇÑ´Ù.
	//
	// ±×·¸°Ô ÇÏÁö ¾ÊÀ¸¸é child WindowÀÌ Á¦°ÅµÉ ¶§´Â ÀÌ¹Ì C_VS_UI_TITLE::IsPIxel()À»
	// ÇÒ ¼ö ¾ø´Â »óÅÂ(m_title_spk°¡ deleteµÈ ÀÌÈÄ)ÀÌ±â ¶§¹®ÀÌ´Ù.
	//
	DeleteNew(m_pC_login);
	DeleteNew(m_pC_char_manager);
	DeleteNew(m_pC_server_select);
	
//	DeleteNew(m_pC_newuser);
//	DeleteNew(m_pC_option);

	DeleteNew(m_pC_button_group);

	DeleteNew(m_pC_credit);
	DeleteNew(m_pC_dialog);
#if	__CONTENTS(__USER_GRADE)
	DeleteNew(m_pC_use_grade);
#endif	//__USER_GRADE	
	DeleteNew(m_pC_use_askCheckToEnterServer) ; 

	DeleteNew(m_pAnimationTimer);
}

//-----------------------------------------------------------------------------
// C_VS_UI_TITLE::CloseUserRegistrationWindow
//
// 
//-----------------------------------------------------------------------------
//void	C_VS_UI_TITLE::CloseUserRegistrationWindow()
//{
//	m_pC_newuser->Finish();
//}

//-----------------------------------------------------------------------------
// C_VS_UI_TITLE::RunNewUserRegistration
//
// 
//-----------------------------------------------------------------------------
//void	C_VS_UI_TITLE::RunNewUserRegistration()
//{
//	assert(m_pC_newuser != NULL);
//
//	m_pC_newuser->Start();
//}
/*
//-----------------------------------------------------------------------------
// RunTitleOption
//
// ±³È¯ÇÒ°Å³Ä°í ¹¯´Â´Ù.
//-----------------------------------------------------------------------------
void C_VS_UI_TITLE::RunOption()
{
	//gC_vs_ui.CloseTitle();

	if (m_pC_option!= NULL)
	{
		DeleteNew(m_pC_option);
	}

	// center
	m_pC_option = new C_VS_UI_OPTION;

	assert(m_pC_option != NULL);

//	gbl_title_option_running = true;

	m_pC_option->Start();	
}

//-----------------------------------------------------------------------------
// CloseTitleOption
//
// ÀÌ¹Ì finishµÈ »óÅÂÀÌ¸é ¾Æ¹«°Íµµ ÇÏÁö ¾Ê´Â´Ù.
//-----------------------------------------------------------------------------
void C_VS_UI_TITLE::CloseOption()
{
	if (!m_pC_option)
		return;

	DeleteNew(m_pC_option);
	
	//assert(m_pC_tribe_interface != NULL);
	//m_pC_tribe_interface->DoCommonActionAfterEventOccured();	

	//gbl_title_option_running = false;
	//gC_vs_ui.AcquireChatting();
}
*/
//-----------------------------------------------------------------------------
// C_VS_UI_TITLE::CloseCharInfo
//
// 
//-----------------------------------------------------------------------------
//void C_VS_UI_TITLE::CloseCharInfo()
//{
//	if (m_pC_char_manager)
//		m_pC_char_manager->CloseCharInfo();
//}


//-----------------------------------------------------------------------------
// AcquireFirstSequence
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_TITLE::AcquireFirstSequence()
{
}

//-----------------------------------------------------------------------------
// NewCharacterCreateFailed
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_TITLE::NewCharacterCreateFailed(int error)
{
	if (m_pC_char_manager)
		m_pC_char_manager->NewCharacterCreateFailed(error);
}

void C_VS_UI_TITLE::SetCharacter(int slot, S_SLOT &S_slot)
{
	if (m_pC_char_manager)
		m_pC_char_manager->SetCharacter(slot, S_slot);
}

void C_VS_UI_TITLE::UnacquireMouseFocus()
{
	m_pC_button_group->UnacquireMouseFocus();
}

void C_VS_UI_TITLE::AcquireMouseFocus()
{

}

void C_VS_UI_TITLE::RunCannotPlayMessage()
{
	if(m_pC_char_manager)
		m_pC_char_manager->Run(C_VS_UI_CHAR_MANAGER::CANNOT_PLAY_ID);	
}

void C_VS_UI_TITLE::RunCannotPlayByAttrMessage()
{
	if(m_pC_char_manager)
		m_pC_char_manager->Run(C_VS_UI_CHAR_MANAGER::CANNOT_PLAY_BY_ATTR_ID);	
}

//-----------------------------------------------------------------------------
// WindowEventReceiver
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_TITLE::WindowEventReceiver(id_t event)
{
}

//-----------------------------------------------------------------------------
// IsPixel
//
// 
//-----------------------------------------------------------------------------
bool C_VS_UI_TITLE::IsPixel(int _x, int _y)
{
	SPRITE_ID id = TITLE_BACK_GROUND_800_600;

	bool bHighResolution = g_pUserInformation->iResolution_x > 800;

	if ( bHighResolution )
	{
		if(g_pUserInformation->iResolution_x <= 1024)
			id = TITLE_BACK_GROUND_1024_768;
		else 
		{
			if(g_pUserInformation->iResolution_y <= 960)
				id = TITLE_BACK_GROUND_1280_960;
			else
			id = TITLE_BACK_GROUND_1280_1024;
		}
	}
	else
		id = TITLE_BACK_GROUND_800_600;



	return m_title_new_spk.IsPixel((_x), (_y), id);
}

//-----------------------------------------------------------------------------
// Process
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_TITLE::Process()
{
	m_pC_button_group->Process();
}

//-----------------------------------------------------------------------------
// Start
//
// TitleÀ» Àç½ÃÀÛÇÑ´Ù. ±×·¡¼­ Title ÇÏÀ§¸Þ´º¸¦ ¸ðµÎ Á¾·áÇØ¾ß ÇÑ´Ù.
//-----------------------------------------------------------------------------
void C_VS_UI_TITLE::Start()
{
	m_bl_credit = false;
	gbl_wood_skin = true;
//	gbl_vampire_interface = false;

	// change skin data
	gpC_global_resource->FreeAssemble();
	gpC_global_resource->LoadAssemble();

	PI_Processor::Start();

	g_pTopView->DeleteTitleEffect();

	m_pC_char_manager->Finish();
	m_pC_login->Finish();
	m_pC_server_select->Finish();
//	m_pC_newuser->Finish();

	AttrKeyboardControl(true);
	gpC_window_manager->AppearWindow(this);
	m_pC_button_group->Init();
	if(false == g_pUserInformation->IsAutoLogIn &&
	   false == g_pUserInformation->IsNetmarbleLogin)
	{
		m_lev_id.Acquire();
		m_lev_id.EraseAll();
		m_lev_password.EraseAll();
	
		
		if(strlen(g_pUserOption->BackupID) > 0)
		{
			m_lev_id.AddString(g_pUserOption->BackupID);
			ChangeFocus();
		}
	}

	g_descriptor_manager.Unset();

	g_eRaceInterface = RACE_SLAYER;

	POINT	ptEffect_Warter_Light;
	
	ptEffect_Warter_Light.x		= m_wEffect_Warter_Light_X;
	ptEffect_Warter_Light.y		= m_wEffect_Warter_Light_Y;

	bool bHighResolution = g_pUserInformation->iResolution_x > 800;
	
	//if(bHighResolution)
	//	g_pTopView->AddTitleEffect(&ptEffect_Warter_Light, EFFECTSPRITETYPE_LOGIN_WARTER_LIGHT, 8, EFFECT_INDEX_WARTER_LIGHT);
	//else
	//	g_pTopView->AddTitleEffect(&ptEffect_Warter_Light, EFFECTSPRITETYPE_LOGIN_WARTER_LIGHT_800_600, 4, EFFECT_INDEX_WARTER_LIGHT);

#ifndef _LIB
	//m_pC_dialog->Start();
#endif
}

//-----------------------------------------------------------------------------
// Finish
//
// Title/Login/Characters ... ¸ðµç Window°¡ µ¶¸³µÈ °ÍÀÌ¹Ç·Î ¾î´À ÇÏ³ª°¡ FinishµÇ¾î¼­
// ´Ù¸¥ °Íµµ FinishµÇ¸é ¾ÈµÈ´Ù.
//-----------------------------------------------------------------------------
void C_VS_UI_TITLE::Finish()
{
	PI_Processor::Finish();

	gpC_window_manager->DisappearWindow(this);
}

//-----------------------------------------------------------------------------
// ShowButtonWidget
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_TITLE::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{
	switch(p_button->GetID())
	{
	case CONNECT:
		p_button->x	= m_wGame_Run_X;
		p_button->y	= m_wGame_Run_Y;
	break;

	case NEWID:
		p_button->x	= m_wID_Create_X;
		p_button->y	= m_wID_Create_Y;
	break;

	case OPTION:
		p_button->x	= m_wOption_X;
		p_button->y	= m_wOption_Y;
	break;

	case CREDIT:
		p_button->x	= m_wGame_Creaters_X;
		p_button->y	= m_wGame_Creaters_Y;
	break;

	case EXIT:
		p_button->x	= m_wGame_Exit_X;
		p_button->y	= m_wGame_Exit_Y;
	break;
	}

	m_title_menu_default.BltLocked(p_button->x, p_button->y, (p_button->m_image_index)+1);

	if(p_button->GetPressState())
		m_title_menu_default.BltLocked(p_button->x, p_button->y, (p_button->m_image_index));
	else if (p_button->GetFocusState())
	{
		if(p_button->m_alpha >= 31)
			p_button->m_alpha = 0;

		m_title_menu_default.BltLockedAlpha(p_button->x, p_button->y, (p_button->m_image_index), p_button->m_alpha);
	}	
}

void C_VS_UI_TITLE::ShowButtonDescription(C_VS_UI_EVENT_BUTTON * p_button)
{
	const char* m_Title_button_string[5] = 
	{
		(*g_pGameStringTable)[UI_STRING_MESSAGE_TITLE_HOTKEY_CONNECT].GetString(),		//Connnect
		(*g_pGameStringTable)[UI_STRING_MESSAGE_TITLE_HOTKEY_OPTION].GetString(),		// Option
		(*g_pGameStringTable)[UI_STRING_MESSAGE_TITLE_HOTKEY_CREDIT].GetString(),		// Credit
		(*g_pGameStringTable)[UI_STRING_MESSAGE_TITLE_HOTKEY_EXIT].GetString(),			// Exit
		(*g_pGameStringTable)[UI_STRING_MESSAGE_TITLE_HOTKEY_NEWID].GetString(),		// NewID
	};
	int Title_buttonID = p_button->GetID();
	if(p_button->GetFocusState())
	{
		g_descriptor_manager.Set(DID_INFO, p_button->x, p_button->y+p_button->h+35, (void *)m_Title_button_string[Title_buttonID]);
	}
}



//-----------------------------------------------------------------------------
// Show
//
// [Âü°í] ¸¸¾à descriptor¸¦ Title¿¡¼­ »ç¿ëÇÏ·Á¸é, ±×°ÍÀÇ Show()¸¦ ¿©±â¼­ ½ÇÇàÇÑ´Ù.
//			 ÀÌ°ÍÀº Game class¿¡µµ ÀÖ´Ù. C_VS_UI::Show()¿¡´Ù ³õÀ¸¸é ¾ÈµÈ´Ù.
//-----------------------------------------------------------------------------
void C_VS_UI_TITLE::Show()
{
	
	Timer();

	Init_TitleUIInterface_InfInfo();

	bool bHighResolution = g_pUserInformation->iResolution_x > 800;
	
	if(bHighResolution)
	{
		gpC_base->m_p_DDSurface_back->FillSurface(0);
	}

	if(gpC_base->m_p_DDSurface_back->Lock())
	{
		if(bHighResolution)
		{
			if(g_pUserInformation->iResolution_x <= 1024)
				m_title_new_spk.BltLocked((g_pUserInformation->iResolution_x - m_title_new_spk.GetWidth(TITLE_BACK_GROUND_1024_768)) / 2, 
				(g_pUserInformation->iResolution_y - m_title_new_spk.GetHeight(TITLE_BACK_GROUND_1024_768)) / 2, TITLE_BACK_GROUND_1024_768);
			else 
			{
				if(g_pUserInformation->iResolution_y <= 960)
				//	m_title_new_spk.BltLocked((g_pUserInformation->iResolution_x - m_title_new_spk.GetWidth(TITLE_BACK_GROUND_1280_720)) / 2, 
				//	(g_pUserInformation->iResolution_y - m_title_spk.GetHeight(TITLE_BACK_GROUND_1280_720)) / 2, TITLE_BACK_GROUND_1280_720);
				//else if(g_pUserInformation->iResolution_y < 1024)
					m_title_new_spk.BltLocked((g_pUserInformation->iResolution_x - m_title_new_spk.GetWidth(TITLE_BACK_GROUND_1280_960)) / 2, 
					(g_pUserInformation->iResolution_y - m_title_new_spk.GetHeight(TITLE_BACK_GROUND_1280_960)) / 2, TITLE_BACK_GROUND_1280_960);
				else
					m_title_new_spk.BltLocked((g_pUserInformation->iResolution_x - m_title_new_spk.GetWidth(TITLE_BACK_GROUND_1280_1024)) / 2, 
					(g_pUserInformation->iResolution_y - m_title_new_spk.GetHeight(TITLE_BACK_GROUND_1280_1024)) / 2, TITLE_BACK_GROUND_1280_1024);
			}
		}
		else		// 800*600
		{
			m_title_new_spk.BltLocked((g_pUserInformation->iResolution_x - m_title_new_spk.GetWidth(TITLE_BACK_GROUND_800_600)) / 2, 
				(g_pUserInformation->iResolution_y - m_title_new_spk.GetHeight(TITLE_BACK_GROUND_800_600)) / 2, TITLE_BACK_GROUND_800_600);
		}

		gpC_base->m_p_DDSurface_back->Unlock();
	}

	
	
	POINT	ptEffect_Warter_Light;
	ptEffect_Warter_Light.x		= m_wEffect_Warter_Light_X;
	ptEffect_Warter_Light.y		= m_wEffect_Warter_Light_Y;
	g_pTopView->SetTitleEffectPos(&ptEffect_Warter_Light, EFFECT_INDEX_WARTER_LIGHT);
	g_pTopView->DrawTitleEffect(EFFECT_INDEX_WARTER_LIGHT);	

	

	if(gpC_base->m_p_DDSurface_back->Lock())
	{
		m_title_new_spk.BltLockedAlpha(m_wButton_Layout_X, m_wButton_Layout_Y, BUTTON_LAYOUT_BUTTON, 18);
		m_title_new_spk.BltLocked(m_wButton_Layout_X, m_wButton_Layout_Y, TEXT_IMAGE);
		//m_title_new_spk.BltLocked(m_wAni_Mark_X, m_wAni_Mark_Y, ANI_MARK_BUTTON);
		//m_title_new_spk.BltLocked(m_wButton_Layout_X, m_wButton_Layout_Y, TEXT_IMAGE);

//#if __CONTENTS(__USER_GRADE)
//#if __CONTENTS(!__IMI_INTERFACE)
//		m_pC_use_grade->BltLocked(m_wChild_X, m_wChild_Y, CHILD);
//#endif //__IMI_INTERFACE
//		m_pC_use_grade->BltLocked(m_wAdult_X, m_wAdult_Y, ADULT);
//		m_pC_use_grade->BltLocked(m_wViolence_X, m_wViolence_Y, VIOLENCE);
//		m_pC_use_grade->BltLocked(m_wFear_X, m_wFear_Y, FEAR);
//#endif // __USER_GRADE
		
		m_pC_button_group->Show();	
		gpC_base->m_p_DDSurface_back->Unlock();
	}

	g_PrintColorStrShadow(m_wButton_Layout_X + 30, m_wButton_Layout_Y + 21, "ÓÃ»§Ãû", gpC_base->m_user_id_pi, RGB_WHITE, RGB_BLACK);
	g_PrintColorStrShadow(m_wButton_Layout_X + 30, m_wButton_Layout_Y + 43, "ÃÜ  Âë", gpC_base->m_user_id_pi, RGB_WHITE, RGB_BLACK);
			
	if(false == g_pUserInformation->IsAutoLogIn &&   false == g_pUserInformation->IsNetmarbleLogin)
	{
		Window::ShowWidget();
	}

	m_pC_button_group->ShowDescription();
	
	if (m_bl_credit)
	{
		if(gpC_base->m_p_DDSurface_back->Lock())
		{
			assert(m_pC_credit != NULL);
				
			const int scroll_x = 0, scroll_y = 0;
			
			if(g_pUserInformation->iResolution_x > 800)
			{
				if(g_pUserInformation->iResolution_x <= 1024)
					m_pC_credit->BltLocked(g_pUserInformation->iResolution_x/2-m_pC_credit->GetWidth(BACKGROUND_1024_768)/2, 
					g_pUserInformation->iResolution_y/2-m_pC_credit->GetHeight(BACKGROUND_1024_768)/2, BACKGROUND_1024_768);
				else
				{
					if(g_pUserInformation->iResolution_y < 960)
						m_pC_credit->BltLocked(g_pUserInformation->iResolution_x/2-m_pC_credit->GetWidth(BACKGROUND_1280_720)/2, 
						g_pUserInformation->iResolution_y/2-m_pC_credit->GetHeight(BACKGROUND_1280_720)/2, BACKGROUND_1280_720);
					else if(g_pUserInformation->iResolution_y < 1024)
						m_pC_credit->BltLocked(g_pUserInformation->iResolution_x/2-m_pC_credit->GetWidth(BACKGROUND_1280_960)/2, 
						g_pUserInformation->iResolution_y/2-m_pC_credit->GetHeight(BACKGROUND_1280_960)/2, BACKGROUND_1280_960);
					else
						m_pC_credit->BltLocked(g_pUserInformation->iResolution_x/2-m_pC_credit->GetWidth(BACKGROUND_1280_1024)/2, 
						g_pUserInformation->iResolution_y/2-m_pC_credit->GetHeight(BACKGROUND_1280_1024)/2, BACKGROUND_1280_1024);
				}
			}
			else
				m_pC_credit->BltLocked(g_pUserInformation->iResolution_x/2-m_pC_credit->GetWidth(BACKGROUND_800_600)/2, 
				g_pUserInformation->iResolution_y/2-m_pC_credit->GetHeight(BACKGROUND_800_600)/2, BACKGROUND_800_600);

			int scroll = ( (m_credit_scroll < 0)? 0 : m_credit_scroll );
			int scroll2 = ( (m_credit_scroll < 0)? m_credit_scroll : m_credit_scroll );
			int scroll3 = ( (m_credit_scroll < 0)? g_pUserInformation->iResolution_y+m_credit_scroll : g_pUserInformation->iResolution_y );
				
			Rect rect(0, scroll, m_pC_credit->GetWidth(CREATORS_SCROLL), min(scroll3, m_pC_credit->GetHeight(CREATORS_SCROLL) - scroll));
			m_pC_credit->BltLockedClip(scroll_x, scroll_y-scroll2, rect, CREATORS_SCROLL);
				
			Rect rect2(0, 0, m_pC_credit->GetWidth(COPYRIGHT), min(scroll3 - (m_pC_credit->GetHeight(CREATORS_SCROLL) - scroll) -50, m_pC_credit->GetHeight(COPYRIGHT)));
			m_pC_credit->BltLockedClip(scroll_x +m_pC_credit->GetWidth(CREATORS_SCROLL)/2-m_pC_credit->GetWidth(COPYRIGHT)/2, 
				scroll_y + max((g_pUserInformation->iResolution_y-70)/2, (m_pC_credit->GetHeight(CREATORS_SCROLL) - scroll + 50) ), rect2, COPYRIGHT);

			gpC_base->m_p_DDSurface_back->Unlock();
		}
	}
	else
	{
	g_FL2_GetDC();

	g_PrintColorStr(m_wWorningString_X, m_wWorningString_Y, (*g_pGameStringTable)[STRING_MESSAGE_WARMING_LOGIN2].GetString(), gpC_base->m_user_id_pi, RGB_WHITE);

	g_FL2_ReleaseDC();
	}

	SHOW_WINDOW_ATTR;
}




//-----------------------------------------------------------------------------
// C_VS_UI_TITLE::Timer
//
//-----------------------------------------------------------------------------
bool	C_VS_UI_TITLE::Timer()
{
	if(m_dw_prev_tickcount+m_dw_millisec <= GetTickCount())
	{
		m_dw_prev_tickcount = GetTickCount();
		m_credit_scroll++;
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
// MouseControl
//
// 
//-----------------------------------------------------------------------------
bool C_VS_UI_TITLE::MouseControl(UINT message, int _x, int _y)
{
	if (m_bl_credit)
	{
		if (message == M_LEFTBUTTON_UP)
		{
			m_bl_credit = false;
			DeleteNew(m_pC_credit);
			EMPTY_MOVE;
		}

		return true;
	}

	Window::MouseControl(message, _x, _y);

	m_pC_button_group->MouseControl(message, _x, _y);

	int iStartRangeX = 0, iStartRangeY  = g_pUserInformation->iResolution_y - m_title_spk.GetHeight(1);
	int offsetX = 0;
	
	bool bHighResolution = g_pUserInformation->iResolution_x > 800;
	if(bHighResolution)	
	{
		offsetX = 86;
	}
	else
	{
		offsetX = 70;
	}
	switch (message)
	{
	case M_LEFTBUTTON_DOWN:
	case M_LB_DOUBLECLICK:
		{
			if(false == g_pUserInformation->IsAutoLogIn &&
		       false == g_pUserInformation->IsNetmarbleLogin)
			{
				Rect id_rt(m_wID_Edit_X,	m_wID_Edit_Y, 130, 23);
				Rect pass_rt(m_wPW_Edit_X,	m_wPW_Edit_Y, 130, 23);
				if (id_rt.IsInRect(_x, _y))
				{
					if (!m_lev_id.IsAcquire())
						ChangeFocus();
				}
				else if (pass_rt.IsInRect(_x, _y))
				{
					if (!m_lev_password.IsAcquire())
						ChangeFocus();
				}
			}
		}
	}

	return true; // no game, then 'true'
}

//-----------------------------------------------------------------------------
// KeyboardControl
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_TITLE::KeyboardControl(UINT message, UINT key, long extra)
{
	Window::KeyboardControl(message, key, extra);
	
	if (m_bl_credit)
	{
		if (message == WM_KEYDOWN)
			if (key == VK_ESCAPE)
			{
				m_bl_credit = false;
				DeleteNew(m_pC_credit);
				EMPTY_MOVE;
			}

		return;
	}

	switch (message)
	{
		case WM_KEYDOWN:
			// 
			// input position º¯°æ.
			//
			if (key == VK_TAB)
			{	
				if(false == g_pUserInformation->IsAutoLogIn &&
				   false == g_pUserInformation->IsNetmarbleLogin)
				{
					//NextFocus();
					ChangeFocus();
				}
			}
			else if (key == VK_ESCAPE) // cancel!
			{
				Run(EXIT);
//				Finish();
			}
			else if (key == VK_RETURN) // ok
			{
				//if (focus_end) // ºñ¾î ÀÖ´Â °÷ÀÌ ¾øÀ¸¸é send!
				//{
				if(false == g_pUserInformation->IsAutoLogIn &&
				   false == g_pUserInformation->IsNetmarbleLogin)
				{
					if (ReadySend() == true)
						SendLoginToClient();
					else
						//NextFocus();
						ChangeFocus();
					//}
				}
				else
				{
					gpC_base->SendMessage(UI_RUN_CONNECT);
				}
			}
			break;
	}

	// ¸¸¾à IME toggleµÇ¾î ÀÖÀ» °æ¿ì¸¦ ´ëºñÇÏ¿© scan code·Î ÇÑ´Ù.

/*	id_t id = INVALID_ID;
	if (message == WM_KEYDOWN) 
	{
		switch (SCAN_CODE(extra))
		{
			case SCANCODE_C: // 'C'onnect
				id = CONNECT;
				break;

//			case SCANCODE_T: // 'T'utorial
//				id = TUTORIAL;
//				break;

			case SCANCODE_O: // 'O'ption
				id = OPTION;
				break;

			case SCANCODE_R: // C'r'edit
				id = CREDIT;
				break;

			case SCANCODE_X: // E'x'it
				id = EXIT;
				break;
			case SCANCODE_N: // 'N'ewID
				id = NEWID;
				break;

			default:
				id = INVALID_ID;
		}
	}

	Run(id);*/
}

//-----------------------------------------------------------------------------
// Run
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_TITLE::Run(id_t id)
{
	switch (id)
	{
		case CONNECT:
			{
				// ³Ý¸¶ºí¿ë
	//			m_pC_login->Start();
				if(false == g_pUserInformation->IsAutoLogIn &&
				   false == g_pUserInformation->IsNetmarbleLogin)
				{
					if (ReadySend() == true)
					{
						SendLoginToClient();
					}
					else
					{
						g_msg_wrong_id_password->Start();
					}
				}
				else
				{
					gpC_base->SendMessage(UI_RUN_CONNECT);
				}
			}
			break;

//		case TUTORIAL:
//			g_msg_not_available_menu->Start();
//			break;

		case OPTION:
			{
				//g_msg_not_available_menu->Start();
				gC_vs_ui.RunOption(true);
			}
			break;

		case CREDIT:
			{
				//g_msg_not_available_menu->Start();
				DeleteNew(m_pC_credit);

				bool bHighResolution = g_pUserInformation->iResolution_x > 800;

// 				if(bHighResolution)
// 					m_pC_credit = new C_SPRITE_PACK(SPK_CREDIT_1024);
// 				else	m_pC_credit = new C_SPRITE_PACK(SPK_CREDIT);

				m_pC_credit = new C_SPRITE_PACK(SPK_CREDIT);

				m_bl_credit = true;
	
				//m_credit_scroll = -RESOLUTION_Y;
				m_credit_scroll = -g_pUserInformation->iResolution_y;
			}
			break;

		case EXIT:
			{
				DeleteNew(m_pC_dialog);
				m_pC_dialog = new C_VS_UI_DIALOG(-1, -1, 2, 0, ExecF_EXITQuestion, DIALOG_TITLE_OK|DIALOG_TITLE_CANCEL);
			
				char * pp_dmsg[1] = {(*g_pGameStringTable)[STRING_MESSAGE_EXIT_QUESTION].GetString(),};
				m_pC_dialog->SetMessage( pp_dmsg, 1, SMO_NOFIT , true );
				m_pC_dialog->Start();
				break;
			}
		case NEWID:
			{
				Finish();
				gpC_base->SendMessage(UI_RUN_NEWUSER_REGISTRATION);
			}
			break;

		default:
			break;
	}

	if(id != INVALID_ID)
	{
		g_descriptor_manager.Unset();
		m_pC_button_group->UnacquireMouseFocus();
	}
}

bool C_VS_UI_TITLE::ReadySend()
{
	if (m_lev_id.Size() > 0 && m_lev_password.Size() > 0)
		return true;
	
	return false;

}

void C_VS_UI_TITLE::ChangeFocus()
{
	if (m_lev_id.IsAcquire())
	{
		if(m_lev_id.Size() == 0)
			m_lev_id.AddString(m_lev_id_backup.c_str());
		m_lev_password.Acquire();
	}
	else
	{
		char * p_temp = NULL;
		g_Convert_DBCS_Ascii2SingleByte(m_lev_id.GetString(), m_lev_id.Size(), p_temp);
		if(p_temp == NULL)
		{
			m_lev_id_backup = "";
		}
		else
		{
			m_lev_id_backup = p_temp;
			DeleteNewArray(p_temp);
		}
		m_lev_id.Acquire();
		m_lev_id.EraseAll();
	}
}

void C_VS_UI_TITLE::SendLoginToClient()
{
	//
	// ¹Ýµå½Ã staticÀ¸·Î ÇÏ°í member¸¦ login check°¡ ³¡³ª°í delete ÇØÁØ´Ù.
	//
	static LOGIN S_login; 
	//S_login.sz_id = (char *)m_string_line_ID.c_str();
	//S_login.sz_password = (char *)m_string_line_PASSWORD.c_str();
	g_Convert_DBCS_Ascii2SingleByte(m_lev_id.GetString(), m_lev_id.Size(), S_login.sz_id);
	g_Convert_DBCS_Ascii2SingleByte(m_lev_password.GetString(), m_lev_password.Size(), S_login.sz_password);
	strcpy(g_pUserOption->BackupID, S_login.sz_id);

	gpC_base->SendMessage(UI_LOGIN, 0, 0, &S_login);
}



/*-----------------------------------------------------------------------------
- C_VS_UI_OPTION
-
-----------------------------------------------------------------------------*/
C_VS_UI_OPTION::C_VS_UI_OPTION(bool IsTitle)
{
	m_IsTitle = IsTitle;

	// CONTROL TAB
	if(g_pUserOption->UseEnterChat)
	{
		m_check[CHECK_NORMAL_CHAT] = CHECK_NOT;
		m_check[CHECK_ENTER_CHAT] = CHECK_CHECK;
	}
	else
	{
		m_check[CHECK_NORMAL_CHAT] = CHECK_CHECK;
		m_check[CHECK_ENTER_CHAT] = CHECK_NOT;
	}

	// ÇØ»óµµ ¼±ÅÃ RADIO ¹öÆ°
// 	if(IsTitle)
// 	{
// 		m_check[CHECK_RESOLUTION_1024x768]	= CHECK_TYPE(g_pUserOption->Resolution1024);
// 		m_check[CHECK_RESOLUTION_800x600]	= CHECK_TYPE(!m_check[CHECK_RESOLUTION_1024x768]);
// 	}
// 	else
// 	{
// 		m_check[CHECK_RESOLUTION_1024x768]	= (g_pUserOption->Resolution1024) ? CHECK_CHECK_DISABLE : CHECK_DISABLE;
// 		m_check[CHECK_RESOLUTION_800x600]	= (!g_pUserOption->Resolution1024) ? CHECK_CHECK_DISABLE : CHECK_DISABLE;;
// 	}


//	m_check[CHECK_MOUSE_SPEED] = g_pUserOption->UseMouseSpeed?CHECK_CHECK:CHECK_NOT;
	m_value_mouse_speed = g_pUserOption->MouseSpeedValue;

	if(gpC_Imm && gpC_Imm->IsDevice())
	{
		m_check[CHECK_IFEEL] = g_pUserOption->UseForceFeel?CHECK_CHECK:CHECK_NOT;
	}
	else	m_check[CHECK_IFEEL] = CHECK_DISABLE;

	// GRAPHIC TAB
	m_check[CHECK_ALPHA_HPBAR] = g_pUserOption->DrawTransHPBar?CHECK_CHECK:CHECK_NOT;
	m_check[CHECK_BLOOD_DROP] = g_pUserOption->BloodDrop?CHECK_CHECK:CHECK_NOT;

	if(g_pUserInformation->IsUnderFifthteen)
		m_check[CHECK_BLOOD_DROP] = CHECK_DISABLE; 
	
	m_check[CHECK_ALPHA_DEPTH] = CHECK_DISABLE;
	m_check[CHECK_DEFAULT_ALPHA] = g_pUserOption->DefaultAlpha?CHECK_CHECK:CHECK_NOT;
	if(CDirectDraw::IsSupportGammaControl())
	{
		m_check[CHECK_GAMMA] = g_pUserOption->UseGammaControl?CHECK_CHECK:CHECK_NOT;
		m_value_gamma = g_pUserOption->GammaValue;
	}
	else	m_check[CHECK_GAMMA] = CHECK_DISABLE;

	m_check[CHECK_CHATBOX] = g_pUserOption->DrawChatBoxOutline?CHECK_CHECK:CHECK_NOT;
	m_check[CHECK_FPS] = g_pUserOption->DrawFPS?CHECK_CHECK:CHECK_NOT;
	m_check[CHECK_AUTOHIDE_SMOOTH] = g_pUserOption->AutoHideSmoothScroll?CHECK_CHECK:CHECK_NOT;

	// SOUND TAB
//	m_check[CHECK_YELL] = g_pUserOption->PlayYellSound?CHECK_CHECK:CHECK_NOT;
	m_check[CHECK_SOUND] = g_pUserOption->PlaySound?CHECK_CHECK:CHECK_NOT;
	m_check[CHECK_MUSIC] = g_pUserOption->PlayMusic?CHECK_CHECK:CHECK_NOT;
	m_volume_sound = g_pUserOption->VolumeSound;
	m_volume_music = g_pUserOption->VolumeMusic;

//	if(g_pUserOption->PlaySound)
//	{
//		m_check[CHECK_YELL] = g_pUserOption->PlayYellSound?CHECK_CHECK:CHECK_NOT;
//	}
//	else m_check[CHECK_YELL] = CHECK_DISABLE;

	if(g_pUserOption->PlayMusic)
	{
		if(g_pUserOption->PlayWaveMusic)
		{
			m_check[CHECK_WAV] = CHECK_CHECK;
			m_check[CHECK_MIDI] = CHECK_NOT;
		}
		else
		{
			m_check[CHECK_WAV] = CHECK_NOT;
			m_check[CHECK_MIDI] = CHECK_CHECK;
		}
	}
	else
	{
		m_check[CHECK_WAV] = CHECK_DISABLE;
		m_check[CHECK_MIDI] = CHECK_DISABLE;
	}

	// GAME TAB
	m_check[CHECK_HELP] = g_pUserOption->ShowChoboHelp?CHECK_CHECK:CHECK_NOT;
	m_check[CHECK_FILTERING] = g_pUserOption->FilteringCurse?CHECK_CHECK:CHECK_NOT;
//	m_check[CHECK_CHANGE] = g_pUserOption->TribeChange?CHECK_CHECK:CHECK_NOT;
//	m_check[CHECK_PARTY_INVITE] = g_pUserOption->DenyPartyInvite?CHECK_CHECK:CHECK_NOT;
//	m_check[CHECK_PARTY_REQUEST] = g_pUserOption->DenyPartyRequest?CHECK_CHECK:CHECK_NOT;
	m_check[CHECK_PRELOAD_MONSTER] = g_pUserOption->IsPreLoadMonster?CHECK_CHECK:CHECK_NOT;		
	m_check[CHECK_CHAT_WHITE] = g_pUserOption->ChatWhite?CHECK_CHECK:CHECK_NOT;		
	
	m_check[CHECK_TEEN_VERSION] = g_pUserOption->UseTeenVersion?CHECK_CHECK:CHECK_NOT;
	m_check[CHECK_POPUPCHAT_BY_WHISPER] = g_pUserOption->PopupChatByWhisper?CHECK_CHECK:CHECK_NOT;		
//	m_check[CHECK_NOT_SEND_MY_INFO] = g_pUserOption->NotSendMyInfo ? CHECK_CHECK:CHECK_NOT;
	m_check[CHECK_DO_NOT_SHOW_WAR_MSG] = g_pUserOption->DoNotShowWarMsg ? CHECK_CHECK:CHECK_NOT;
	m_check[CHECK_DO_NOT_SHOW_LAIR_MSG] = g_pUserOption->DoNotShowLairMsg ? CHECK_CHECK:CHECK_NOT;
	m_check[CHECK_DO_NOT_SHOW_HOLY_LAND_MSG] = g_pUserOption->DoNotShowHolyLandMsg ? CHECK_CHECK:CHECK_NOT;

#if __CONTENTS(__GAMEOPTION_ITEMBAY_MESSAGEBOX)
	m_check[CHECK_DO_NOT_SHOW_ITEMBAY_MESSAGEBOX] = g_pUserOption->DoNotShowItemBayMessageBox ? CHECK_CHECK:CHECK_NOT;
#endif

#if __CONTENTS(__LANGUAGE_CHANGE)
	m_check[CHECK_SHOW_GAMEMONEY_WITH_HANGUL] = g_pUserOption->ShowGameMoneyWithHANGUL ? CHECK_CHECK:CHECK_NOT;
#endif	//__LANGUAGE_CHANGE
	m_check[CHECK_DO_NOT_SHOW_PERSNALSHOP_MSG] = g_pUserOption->DoNotShowPersnalShopMsg? CHECK_CHECK:CHECK_NOT;
#if __CONTENTS(__JAPAN_UI)
	m_check[CHECK_ONE_CLICK_ATTACK_OFF] = g_pUserOption->DoNotOneClickAttackOff? CHECK_CHECK:CHECK_NOT;
#endif //__JAPAN_UI
	m_pC_main_spk = NULL;
	m_pC_etc_spk = NULL;
	m_pC_scroll_bar = NULL;

	m_pC_dialog = NULL;

	m_i_selected_tab = TAB_CONTROL;

	if(false == m_IsTitle)
	{
		m_pC_scroll_bar = new C_VS_UI_SCROLL_BAR(3, Rect(370, 92, -1, 100));
		m_i_selected_tab = TAB_CONTROL;

		switch(g_eRaceInterface)
		{
		case RACE_SLAYER:
			m_vampire_plus_x = 0; m_vampire_plus_y = 0;
			m_pC_main_spk = new C_SPRITE_PACK(SPK_OPTION_SLAYER);
			break;

		case RACE_VAMPIRE:
			m_vampire_plus_x = 9; m_vampire_plus_y = 1;
			m_pC_main_spk = new C_SPRITE_PACK(SPK_OPTION_VAMPIRE);
			break;

		case RACE_OUSTERS:
			m_vampire_plus_x = 12; m_vampire_plus_y = 10;
			m_pC_main_spk = new C_SPRITE_PACK(SPK_OPTION_OUSTERS);
			break;
		}
		
		m_pC_etc_spk = new C_SPRITE_PACK(SPK_OPTION);
		//Set(RESOLUTION_X /2 - m_pC_main_spk->GetWidth()/2, RESOLUTION_Y /2 - m_pC_main_spk->GetHeight()/2, m_pC_main_spk->GetWidth(), m_pC_main_spk->GetHeight());
		Set(g_pUserInformation->iResolution_x /2 - m_pC_main_spk->GetWidth()/2, g_pUserInformation->iResolution_y /2 - m_pC_main_spk->GetHeight()/2, m_pC_main_spk->GetWidth(), m_pC_main_spk->GetHeight());
	}
	else
	{	
		m_vampire_plus_x = 0; m_vampire_plus_y = 0;

		bool bHighResolution = g_pUserInformation->iResolution_x > 800;

		if(bHighResolution)	m_pC_main_spk = new C_SPRITE_PACK(SPK_TITLE_OPTION_1024);
		else	m_pC_main_spk = new C_SPRITE_PACK(SPK_TITLE_OPTION);
		m_pC_scroll_bar = new C_VS_UI_SCROLL_BAR(0, Rect(378, 90, -1, 112), false, SPK_TITLE_OPTION_SCROLL, 2, 2, 2);
		
		//Set(RESOLUTION_X /2 - m_pC_main_spk->GetWidth()/2, RESOLUTION_Y /2 - m_pC_main_spk->GetHeight()/2 , m_pC_main_spk->GetWidth(), m_pC_main_spk->GetHeight());
		//ÀÌ¹ÌÁö Áß¾Ó¿¡ ¬ÃÆÁö¸¸ 1ÇÈ¼¿¾¿ ´ç°Ü¾ß ÇßÀ½
		
		Set(g_pUserInformation->iResolution_x /2 - m_pC_main_spk->GetWidth()/2 - 1, 
			g_pUserInformation->iResolution_y /2 - m_pC_main_spk->GetHeight()/2 - 1, 
			m_pC_main_spk->GetWidth(), m_pC_main_spk->GetHeight());
	}
	AttrTopmost(true);



	const InterfaceInformation* pSkin = &g_pSkinManager->Get( SkinManager::OPTION );
	m_pC_button_group = new ButtonGroup(this);

	// ÇÏ´Ü µðÆúÆ®µîµî ¹öÆ°
//	int default_button_x = 174, default_button_y = 282, load_button_x = 246, save_button_x = 303;
//	m_pC_button_group->Add( new C_VS_UI_EVENT_BUTTON(default_button_x, default_button_y, m_pC_etc_spk->GetWidth(DEFAULT_BUTTON_HILIGHTED), m_pC_etc_spk->GetHeight(DEFAULT_BUTTON_HILIGHTED), DEFAULT_ID, this, DEFAULT_BUTTON_HILIGHTED) );
//	m_pC_button_group->Add( new C_VS_UI_EVENT_BUTTON(load_button_x, default_button_y, m_pC_etc_spk->GetWidth(LOAD_BUTTON_HILIGHTED), m_pC_etc_spk->GetHeight(LOAD_BUTTON_HILIGHTED), LOAD_ID, this, LOAD_BUTTON_HILIGHTED) );
//	m_pC_button_group->Add( new C_VS_UI_EVENT_BUTTON(save_button_x, default_button_y, m_pC_etc_spk->GetWidth(SAVE_BUTTON_HILIGHTED), m_pC_etc_spk->GetHeight(SAVE_BUTTON_HILIGHTED), SAVE_ID, this, SAVE_BUTTON_HILIGHTED) );

	// close¹öÆ°
	//int close_button_x = pSkin->GetPoint(0).x, close_button_y = pSkin->GetPoint(0).y;
	int i = 0;
	
	if(false == m_IsTitle)
	{
		Tab_X[0] = pSkin->GetRect(0).left;
		Tab_X[1] = pSkin->GetRect(0).top;
		Tab_X[2] = pSkin->GetRect(0).right;
		Tab_X[3] = pSkin->GetRect(0).bottom;
		Tab_Y = 20;

		m_pC_button_group->Add( new C_VS_UI_EVENT_BUTTON(pSkin->GetPoint(0).x,pSkin->GetPoint(0).y, m_pC_etc_spk->GetWidth(BUTTON_CLOSE), m_pC_etc_spk->GetHeight(BUTTON_CLOSE), CLOSE_ID, this, BUTTON_CLOSE) );

		// tab¹öÆ°
		//int tab_control_x = 116, tab_y = 20, tab_graphic_x = 170, tab_sound_x = 224, tab_game_x = 278;
		m_pC_button_group->Add( new C_VS_UI_EVENT_BUTTON(pSkin->GetPoint(1).x, pSkin->GetPoint(1).y, m_pC_main_spk->GetWidth(TAB_CONTROL), m_pC_main_spk->GetHeight(TAB_CONTROL), CONTROL_ID, this, TAB_CONTROL) );
		m_pC_button_group->Add( new C_VS_UI_EVENT_BUTTON(pSkin->GetPoint(2).x, pSkin->GetPoint(2).y, m_pC_main_spk->GetWidth(TAB_GRAPHIC), m_pC_main_spk->GetHeight(TAB_GRAPHIC), GRAPHIC_ID, this, TAB_GRAPHIC) );
		m_pC_button_group->Add( new C_VS_UI_EVENT_BUTTON(pSkin->GetPoint(3).x, pSkin->GetPoint(3).y, m_pC_main_spk->GetWidth(TAB_SOUND), m_pC_main_spk->GetHeight(TAB_SOUND), SOUND_ID, this, TAB_SOUND) );
		m_pC_button_group->Add( new C_VS_UI_EVENT_BUTTON(pSkin->GetPoint(4).x, pSkin->GetPoint(4).y, m_pC_main_spk->GetWidth(TAB_GAME), m_pC_main_spk->GetHeight(TAB_GAME), GAME_ID, this, TAB_GAME) );

		m_check_x = pSkin->GetPoint(5).x, m_check_y = pSkin->GetPoint(5).y, m_check_gap = 20;
		
		// control_tab ¹öÆ°µé
	//	int list_button_x = 341, list_button_y = 54;
		m_pC_control_button_group = new ButtonGroup(this);
		m_pC_control_button_group->Add( new C_VS_UI_EVENT_BUTTON(m_check_x+10, m_check_y, m_pC_etc_spk->GetWidth(RADIO_BACK_DISABLE), m_pC_etc_spk->GetHeight(RADIO_BACK_DISABLE), CHECK_NORMAL_CHAT, this, RADIO_BACK_DISABLE) );
		m_pC_control_button_group->Add( new C_VS_UI_EVENT_BUTTON(m_check_x+120, m_check_y, m_pC_etc_spk->GetWidth(RADIO_BACK_DISABLE), m_pC_etc_spk->GetHeight(RADIO_BACK_DISABLE), CHECK_ENTER_CHAT, this, RADIO_BACK_DISABLE) );

		for(i = 0; i < CHECK_CONTROL_MAX; i++)
			m_pC_control_button_group->Add( new C_VS_UI_EVENT_BUTTON(m_check_x, m_check_y+m_check_gap*(8+i), m_pC_etc_spk->GetWidth(CHECK_BACK_DISABLE), m_pC_etc_spk->GetHeight(CHECK_BACK_DISABLE), CHECK_CONTROL_TAB+i+2, this, CHECK_BACK_DISABLE) );

	#if __CONTENTS(__080405_FIREST_UI_UPDATE)
		m_pC_control_button_group->Add( new C_VS_UI_EVENT_BUTTON(m_check_x,pSkin->GetPoint(6).y, m_pC_main_spk->GetWidth(RESET_OPTION), m_pC_main_spk->GetHeight(RESET_OPTION), RESET_ID, this, RESET_OPTION) );
	#endif //__080405_FIREST_UI_UPDATE

		// graphic_tab ¹öÆ°µé
		m_pC_graphic_button_group = new ButtonGroup(this);
		//m_pC_graphic_button_group->Add( new C_VS_UI_EVENT_BUTTON(m_check_x+10, m_check_y, m_pC_etc_spk->GetWidth(RADIO_BACK_DISABLE), m_pC_etc_spk->GetHeight(RADIO_BACK_DISABLE), CHECK_RESOLUTION_800x600, this, RADIO_BACK_DISABLE) );
		//m_pC_graphic_button_group->Add( new C_VS_UI_EVENT_BUTTON(m_check_x+120, m_check_y, m_pC_etc_spk->GetWidth(RADIO_BACK_DISABLE), m_pC_etc_spk->GetHeight(RADIO_BACK_DISABLE), CHECK_RESOLUTION_1024x768, this, RADIO_BACK_DISABLE) );
		for(i = 0; i < CHECK_GRAPHIC_MAX; i++)
			m_pC_graphic_button_group->Add( new C_VS_UI_EVENT_BUTTON(m_check_x, m_check_y+m_check_gap*(1+i), m_pC_etc_spk->GetWidth(CHECK_BACK_DISABLE), m_pC_etc_spk->GetHeight(CHECK_BACK_DISABLE), CHECK_GRAPHIC_TAB+i+2, this, CHECK_BACK_DISABLE) );
		
		// sound_tab ¹öÆ°µé
		m_pC_sound_button_group = new ButtonGroup(this);
		for(i = 0; i < CHECK_SOUND_MAX; i++)
			m_pC_sound_button_group->Add( new C_VS_UI_EVENT_BUTTON(m_check_x, m_check_y+m_check_gap*i, m_pC_etc_spk->GetWidth(CHECK_BACK_DISABLE), m_pC_etc_spk->GetHeight(CHECK_BACK_DISABLE), CHECK_SOUND_TAB+i, this, CHECK_BACK_DISABLE) );

		// game_tab ¹öÆ°µé
		m_pC_game_button_group = new ButtonGroup(this);
		for(i = 0; i < CHECK_GAME_MAX; i++)
			m_pC_game_button_group->Add( new C_VS_UI_EVENT_BUTTON(m_check_x, m_check_y+m_check_gap*i, m_pC_etc_spk->GetWidth(CHECK_BACK_DISABLE), m_pC_etc_spk->GetHeight(CHECK_BACK_DISABLE), CHECK_GAME_TAB+i, this, CHECK_BACK_DISABLE) );

		m_rt_value[1].Set(m_check_x+120, m_check_y+m_check_gap*(CHECK_GAMMA-CHECK_GRAPHIC_TAB-1) , m_pC_etc_spk->GetWidth(VOLUME_BAR), 15);
		m_rt_value[2].Set(m_check_x+120, m_check_y+m_check_gap*(CHECK_SOUND-CHECK_SOUND_TAB), m_pC_etc_spk->GetWidth(VOLUME_BAR), 15);
		m_rt_value[3].Set(m_check_x+120, m_check_y+m_check_gap*(CHECK_MUSIC-CHECK_SOUND_TAB), m_pC_etc_spk->GetWidth(VOLUME_BAR), 15);
		m_rt_value[4].Set(m_check_x+120, m_check_y+m_check_gap*(CHECK_ALPHA_DEPTH-CHECK_GRAPHIC_TAB-1), m_pC_etc_spk->GetWidth(VOLUME_BAR), 15);

	}
	else
	{
		for(int i = 0; i<4; i++)
			Tab_X[i] = 1 + (i*70);
		Tab_Y = 1;

		m_pC_button_group->Add( new C_VS_UI_EVENT_BUTTON(m_pC_main_spk->GetWidth() - 25, 
			m_pC_main_spk->GetHeight() - 25, 
			m_pC_main_spk->GetWidth(TITLE_BUTTON_EXIT_HILIGHT), 
			m_pC_main_spk->GetHeight(TITLE_BUTTON_EXIT_HILIGHT), 
			CLOSE_ID, this, TITLE_BUTTON_EXIT_HILIGHT) );		

		m_pC_button_group->Add( new C_VS_UI_EVENT_BUTTON(Tab_X[0], Tab_Y, m_pC_main_spk->GetWidth(TITLE_TAB_CONTROL_HILIGHT), m_pC_main_spk->GetHeight(TITLE_TAB_CONTROL_HILIGHT), CONTROL_ID, this, TITLE_TAB_CONTROL_HILIGHT) );
		m_pC_button_group->Add( new C_VS_UI_EVENT_BUTTON(Tab_X[1], Tab_Y, m_pC_main_spk->GetWidth(TITLE_TAB_GRAPHIC_HILIGHT), m_pC_main_spk->GetHeight(TITLE_TAB_GRAPHIC_HILIGHT), GRAPHIC_ID, this, TITLE_TAB_GRAPHIC_HILIGHT) );
		m_pC_button_group->Add( new C_VS_UI_EVENT_BUTTON(Tab_X[2], Tab_Y, m_pC_main_spk->GetWidth(TITLE_TAB_SOUND_HILIGHT), m_pC_main_spk->GetHeight(TITLE_TAB_SOUND_HILIGHT), SOUND_ID, this, TITLE_TAB_SOUND_HILIGHT) );
		m_pC_button_group->Add( new C_VS_UI_EVENT_BUTTON(Tab_X[3], Tab_Y, m_pC_main_spk->GetWidth(TITLE_TAB_GAME_HILIGHT), m_pC_main_spk->GetHeight(TITLE_TAB_GAME_HILIGHT), GAME_ID, this, TITLE_TAB_GAME_HILIGHT) );

		m_check_x = 20, m_check_y = 35 , m_check_gap = 20;

		
	// control_tab ¹öÆ°µé
	//	int list_button_x = 341, list_button_y = 54;
		m_pC_control_button_group = new ButtonGroup(this);
		m_pC_control_button_group->Add( new C_VS_UI_EVENT_BUTTON(m_check_x+10, m_check_y, m_pC_main_spk->GetWidth(TITLE_RADIO_BACK), m_pC_main_spk->GetHeight(TITLE_RADIO_BACK), CHECK_NORMAL_CHAT, this, TITLE_RADIO_BACK) );
		m_pC_control_button_group->Add( new C_VS_UI_EVENT_BUTTON(m_check_x+120, m_check_y, m_pC_main_spk->GetWidth(TITLE_RADIO_BACK), m_pC_main_spk->GetHeight(TITLE_RADIO_BACK), CHECK_ENTER_CHAT, this, TITLE_RADIO_BACK) );

		for(i = 0; i < CHECK_CONTROL_MAX; i++)
		{
			m_pC_control_button_group->Add( new C_VS_UI_EVENT_BUTTON(m_check_x - 10, m_check_y+m_check_gap*(8+i), m_pC_main_spk->GetWidth(TITLE_CHECK_BACK), m_pC_main_spk->GetHeight(TITLE_CHECK_BACK), CHECK_CONTROL_TAB+i+2, this, TITLE_CHECK_BACK) );
		}
			
		m_pC_control_button_group->Add( new C_VS_UI_EVENT_BUTTON( 
			w - m_pC_main_spk->GetWidth(TITLE_BUTTON_RESET_HILIGHT) - 40,
			h - m_pC_main_spk->GetHeight(TITLE_BUTTON_RESET_HILIGHT) - 20,
			m_pC_main_spk->GetWidth(TITLE_BUTTON_RESET_HILIGHT),
			m_pC_main_spk->GetHeight(TITLE_BUTTON_RESET_HILIGHT),
			KEY_DEFAULT_INIT, this, TITLE_BUTTON_RESET_HILIGHT) );

//#ifdef CONVERT_1024_768
//		m_pC_control_button_group->Add( new C_VS_UI_EVENT_BUTTON( 
//			w - m_pC_main_spk->GetWidth(TITLE_BUTTON_RESET_HILIGHT) - 60 ,
//			h - m_pC_main_spk->GetHeight(TITLE_BUTTON_RESET_HILIGHT) - 50 ,
//			m_pC_main_spk->GetWidth(TITLE_BUTTON_RESET_HILIGHT),
//			m_pC_main_spk->GetHeight(TITLE_BUTTON_RESET_HILIGHT),
//			KEY_DEFAULT_INIT, this, TITLE_BUTTON_RESET_HILIGHT) );
//#else
//		m_pC_control_button_group->Add( new C_VS_UI_EVENT_BUTTON(x+ 20 ,y + 133, m_pC_main_spk->GetWidth(TITLE_BUTTON_RESET_HILIGHT), m_pC_main_spk->GetHeight(TITLE_BUTTON_RESET_HILIGHT), KEY_DEFAULT_INIT, this, TITLE_BUTTON_RESET_HILIGHT) );
//#endif
		


		// graphic_tab ¹öÆ°µé
		m_pC_graphic_button_group = new ButtonGroup(this);
		m_pC_graphic_button_group->Add( new C_VS_UI_EVENT_BUTTON(m_check_x+10, m_check_y, m_pC_main_spk->GetWidth(TITLE_RADIO_BACK), m_pC_main_spk->GetHeight(TITLE_RADIO_BACK), CHECK_RESOLUTION_800x600, this, TITLE_RADIO_BACK) );
		m_pC_graphic_button_group->Add( new C_VS_UI_EVENT_BUTTON(m_check_x+120, m_check_y, m_pC_main_spk->GetWidth(TITLE_RADIO_BACK), m_pC_main_spk->GetHeight(TITLE_RADIO_BACK), CHECK_RESOLUTION_1024x768, this, TITLE_RADIO_BACK) );

		for(i = 0; i < CHECK_GRAPHIC_MAX; i++)
			m_pC_graphic_button_group->Add( new C_VS_UI_EVENT_BUTTON(m_check_x, m_check_y+m_check_gap*(1+i), m_pC_main_spk->GetWidth(TITLE_CHECK_BACK), m_pC_main_spk->GetHeight(TITLE_CHECK_BACK), CHECK_GRAPHIC_TAB+i+2, this, TITLE_CHECK_BACK) );
		// sound_tab ¹öÆ°µé
		m_pC_sound_button_group = new ButtonGroup(this);
		for(i = 0; i < CHECK_SOUND_MAX; i++)
			m_pC_sound_button_group->Add( new C_VS_UI_EVENT_BUTTON(m_check_x, m_check_y+m_check_gap*i, m_pC_main_spk->GetWidth(TITLE_CHECK_BACK), m_pC_main_spk->GetHeight(TITLE_CHECK_BACK), CHECK_SOUND_TAB+i, this, TITLE_CHECK_BACK) );
		// game_tab ¹öÆ°µé
		m_pC_game_button_group = new ButtonGroup(this);
		for(i = 0; i < CHECK_GAME_MAX; i++)
			m_pC_game_button_group->Add( new C_VS_UI_EVENT_BUTTON(m_check_x, m_check_y+m_check_gap*i, m_pC_main_spk->GetWidth(TITLE_CHECK_BACK), m_pC_main_spk->GetHeight(TITLE_CHECK_BACK), CHECK_GAME_TAB+i, this, TITLE_CHECK_BACK) );

		m_rt_value[1].Set(m_check_x+120, m_check_y+m_check_gap*(CHECK_GAMMA-CHECK_GRAPHIC_TAB-1) , m_pC_main_spk->GetWidth(TITLE_VOLUME_BAR), 15);
		m_rt_value[2].Set(m_check_x+120, m_check_y+m_check_gap*(CHECK_SOUND-CHECK_SOUND_TAB), m_pC_main_spk->GetWidth(TITLE_VOLUME_BAR), 15);
		m_rt_value[3].Set(m_check_x+120, m_check_y+m_check_gap*(CHECK_MUSIC-CHECK_SOUND_TAB), m_pC_main_spk->GetWidth(TITLE_VOLUME_BAR), 15);
		m_rt_value[4].Set(m_check_x+120, m_check_y+m_check_gap*(CHECK_ALPHA_DEPTH-CHECK_GRAPHIC_TAB-1), m_pC_main_spk->GetWidth(TITLE_VOLUME_BAR), 15);

	}

//	m_rt_value[0].Set(m_check_x+120, m_check_y+m_check_gap*(6+CHECK_MOUSE_SPEED-CHECK_CONTROL_TAB), m_pC_etc_spk->GetWidth(VOLUME_BAR), 15);

	g_RegisterWindow(this);

//	if(false == m_IsTitle)
//	{
//		DeleteNew(m_pC_main_spk);
//		m_pC_main_spk = NULL;
//		DeleteNew(m_pC_etc_spk);
//		m_pC_etc_spk = NULL;
//	}
}

/*-----------------------------------------------------------------------------
- ~C_VS_UI_OPTION
-
-----------------------------------------------------------------------------*/
C_VS_UI_OPTION::~C_VS_UI_OPTION()
{
	gpC_base->SendMessage(UI_CLOSE_OPTION);
	gC_vs_ui.UnSetAccelMode();
	
	g_UnregisterWindow(this);

	DeleteNew(m_pC_dialog);
	DeleteNew(m_pC_scroll_bar);
	DeleteNew(m_pC_button_group);
	DeleteNew(m_pC_control_button_group);
	DeleteNew(m_pC_graphic_button_group);
	DeleteNew(m_pC_sound_button_group);
	DeleteNew(m_pC_game_button_group);
	if(m_pC_main_spk)
	{
		DeleteNew(m_pC_main_spk);
		m_pC_main_spk = NULL;
		DeleteNew(m_pC_etc_spk);
		m_pC_etc_spk = NULL;
	}

}

//-----------------------------------------------------------------------------
// C_VS_UI_OPTION::ShowButtonWidget
//
// 
//-----------------------------------------------------------------------------
void	C_VS_UI_OPTION::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{
	
	//Ã¼Å©&¶óµð¿À ¹öÆ°µé
	if(false == m_IsTitle)
	{
		if(p_button->m_image_index == CHECK_BACK_DISABLE || p_button->m_image_index == RADIO_BACK_DISABLE)
		{
			if(m_check[p_button->GetID()] == CHECK_DISABLE || m_check[p_button->GetID()] == CHECK_CHECK_DISABLE)
			{
				m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+p_button->x, y+m_vampire_plus_y+p_button->y, p_button->m_image_index);
				if(m_check[p_button->GetID()] == CHECK_CHECK_DISABLE)
					m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+p_button->x+2, y+m_vampire_plus_y+p_button->y+2, p_button->m_image_index+2);
			}
			else
			{
				m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+p_button->x, y+m_vampire_plus_y+p_button->y, p_button->m_image_index+1);

				int radio_plus_x = 0, radio_plus_y = 0;
				if(p_button->m_image_index == RADIO_BACK_DISABLE)
				{
					radio_plus_x = 1; radio_plus_y = 1;
				}

				if(p_button->GetPressState())
					m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+radio_plus_x+p_button->x+2, y+m_vampire_plus_y+radio_plus_y+p_button->y+3, p_button->m_image_index+2);
				else if(m_check[p_button->GetID()] == CHECK_CHECK)
					m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+radio_plus_x+p_button->x+2, y+m_vampire_plus_y+radio_plus_y+p_button->y+2, p_button->m_image_index+2);
			}
		}
		//tab¹öÆ°µé
		else if(p_button->GetID() == CONTROL_ID || p_button->GetID() == GRAPHIC_ID || p_button->GetID() == SOUND_ID || p_button->GetID() == GAME_ID)
		{
			if(p_button->GetFocusState())
			{
				if(p_button->GetPressState())
				{
					m_pC_main_spk->BltLocked(x+m_vampire_plus_x+p_button->x, y+m_vampire_plus_y+p_button->y, p_button->m_image_index);
				}
				else
				{
					Rect rect(0, 0, p_button->w, p_button->h-1);
					m_pC_main_spk->BltLockedClip(x+m_vampire_plus_x+p_button->x, y+m_vampire_plus_y+p_button->y, rect, p_button->m_image_index);
				}
			}
		}
		//Close¹öÆ°
		else if(p_button->GetID() == CLOSE_ID)
		{
			if(p_button->GetFocusState())
			{
				if(p_button->GetPressState())
					m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+p_button->x, y+m_vampire_plus_y+p_button->y, p_button->m_image_index+3);
				else
					m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+p_button->x, y+m_vampire_plus_y+p_button->y, p_button->m_image_index+2);
			}
			else
			{
				if(p_button->GetPressState())
					m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+p_button->x, y+m_vampire_plus_y+p_button->y, p_button->m_image_index+1);
				else
					m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+p_button->x, y+m_vampire_plus_y+p_button->y, p_button->m_image_index);
			}

		}
	
	#if __CONTENTS(__080405_FIREST_UI_UPDATE)		
		else if(p_button->GetID() == RESET_ID)
		{
			if(p_button->GetFocusState())
			{
				if(p_button->GetPressState())
					m_pC_main_spk->BltLocked(x+m_vampire_plus_x+p_button->x, y+m_vampire_plus_y+p_button->y, RESET_OPTION_PUSHED);
				else
					m_pC_main_spk->BltLocked(x+m_vampire_plus_x+p_button->x, y+m_vampire_plus_y+p_button->y, RESET_OPTION_HILIGHTED);
			}
			else
				m_pC_main_spk->BltLocked(x+m_vampire_plus_x+p_button->x, y+m_vampire_plus_y+p_button->y, RESET_OPTION);

		}
	#endif //__080405_FIREST_UI_UPDATE
	
		//Hotkey List¹öÆ°
		else if(p_button->GetID() == LIST_ID)
		{
			if(p_button->GetFocusState())
			{
				if(p_button->GetPressState())
					m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+p_button->x, y+m_vampire_plus_y+p_button->y, p_button->m_image_index+3);
				else
					m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+p_button->x, y+m_vampire_plus_y+p_button->y, p_button->m_image_index+2);
			}
			else
			{
				if(p_button->GetPressState())
					m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+p_button->x, y+m_vampire_plus_y+p_button->y, p_button->m_image_index+1);
				else
					m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+p_button->x, y+m_vampire_plus_y+p_button->y, p_button->m_image_index);
			}

		}
		else
		if(p_button->GetFocusState())
		{
			if(p_button->GetPressState())
			{
				m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+p_button->x, y+m_vampire_plus_y+p_button->y, p_button->m_image_index+1);
			}
			else
				m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+p_button->x, y+m_vampire_plus_y+p_button->y, p_button->m_image_index);
		}
	}
	else
	{
		if(p_button->m_image_index == TITLE_CHECK_BACK || p_button->m_image_index == TITLE_RADIO_BACK)
		{
			if(m_check[p_button->GetID()] == CHECK_DISABLE || m_check[p_button->GetID()] == CHECK_CHECK_DISABLE)
			{
				m_pC_main_spk->BltLockedDarkness(x + p_button->x, y + p_button->y, p_button->m_image_index, 1);
			}
			else
			{
				int radio_plus_x = 0, radio_plus_y = 0;
				if(p_button->m_image_index == TITLE_RADIO_BACK)
				{
					radio_plus_x = 3; radio_plus_y = 3;
					m_pC_main_spk->BltLocked(x + p_button->x, y + p_button->y, p_button->m_image_index);
					if(m_check[p_button->GetID()] == CHECK_CHECK)
					m_pC_main_spk->BltLocked(x + p_button->x + radio_plus_x, y + p_button->y + radio_plus_y, p_button->m_image_index+1);
				}
				else
				{
					if(m_check[p_button->GetID()] == CHECK_CHECK)
						m_pC_main_spk->BltLocked(x + p_button->x + radio_plus_x, y + p_button->y + radio_plus_y, p_button->m_image_index+1);
					else
						m_pC_main_spk->BltLocked(x + p_button->x + radio_plus_x, y + p_button->y + radio_plus_y, p_button->m_image_index);
				}
//				int radio_plus_x = 0, radio_plus_y = 0;
//				if(p_button->m_image_index == RADIO_BACK_DISABLE)
//				{
//					if(m_check[p_button->GetID()] == CHECK_CHECK)
//					radio_plus_x = 1; radio_plus_y = 1;
//				}
//
//				if(p_button->GetPressState())
//					m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+radio_plus_x+p_button->x+2, y+m_vampire_plus_y+radio_plus_y+p_button->y+3, p_button->m_image_index+2);
//				else if(m_check[p_button->GetID()] == CHECK_CHECK)
//					m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+radio_plus_x+p_button->x+2, y+m_vampire_plus_y+radio_plus_y+p_button->y+2, p_button->m_image_index+2);
			}
		}
		//tab¹öÆ°µé
		else if(p_button->GetID() == CONTROL_ID || p_button->GetID() == GRAPHIC_ID || p_button->GetID() == SOUND_ID || p_button->GetID() == GAME_ID)
		{
			if(p_button->GetFocusState())
			{
				if(p_button->GetPressState())
				{
					m_pC_main_spk->BltLocked(x+p_button->x, y+p_button->y, p_button->m_image_index+4);
				}
				else
				{
					m_pC_main_spk->BltLocked(x+p_button->x, y+p_button->y, p_button->m_image_index);
				}
			}
		}
		//Close¹öÆ°
		else if(p_button->GetID() == CLOSE_ID)
		{
			if(p_button->GetFocusState())
			{
				if(p_button->GetPressState())
					m_pC_main_spk->BltLocked(x+p_button->x, y+p_button->y, TITLE_BUTTON_EXIT_PUSH);
				else
					m_pC_main_spk->BltLocked(x+p_button->x, y+p_button->y, TITLE_BUTTON_EXIT_HILIGHT);
			}
		}

		else if(p_button->GetID() == KEY_DEFAULT_INIT)
		{
			if(p_button->GetFocusState())
			{
				if(p_button->GetPressState())
					m_pC_main_spk->BltLocked(x+p_button->x, y+p_button->y, TITLE_BUTTON_RESET_PUSH);
				else
					m_pC_main_spk->BltLocked(x+p_button->x, y+p_button->y, TITLE_BUTTON_RESET_HILIGHT);
			}
			else
				m_pC_main_spk->BltLocked(x+p_button->x, y+p_button->y, TITLE_BUTTON_RESET);

		}	
		//Hotkey List¹öÆ°
		else if(p_button->GetID() == LIST_ID)
		{
			if(p_button->GetFocusState())
			{
				if(p_button->GetPressState())
					m_pC_main_spk->BltLocked(x+m_vampire_plus_x+p_button->x, y+m_vampire_plus_y+p_button->y, p_button->m_image_index+3);
				else
					m_pC_main_spk->BltLocked(x+m_vampire_plus_x+p_button->x, y+m_vampire_plus_y+p_button->y, p_button->m_image_index+2);
			}
			else
			{
				if(p_button->GetPressState())
					m_pC_main_spk->BltLocked(x+m_vampire_plus_x+p_button->x, y+m_vampire_plus_y+p_button->y, p_button->m_image_index+1);
				else
					m_pC_main_spk->BltLocked(x+m_vampire_plus_x+p_button->x, y+m_vampire_plus_y+p_button->y, p_button->m_image_index);
			}

		}
//		else
//		if(p_button->GetFocusState())
//		{
//			if(p_button->GetPressState())
//			{
//				m_pC_main_spk->BltLocked(x+m_vampire_plus_x+p_button->x, y+m_vampire_plus_y+p_button->y, p_button->m_image_index+1);
//			}
//			else
//				m_pC_main_spk->BltLocked(x+m_vampire_plus_x+p_button->x, y+m_vampire_plus_y+p_button->y, p_button->m_image_index);
//		}
	}
}

//-----------------------------------------------------------------------------
// Process
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_OPTION::Process()
{
	m_pC_button_group->Process();
	switch(m_i_selected_tab)
	{
	case TAB_CONTROL:
		m_pC_control_button_group->Process();
		break;

	case TAB_GRAPHIC:
		m_pC_graphic_button_group->Process();
		break;

	case TAB_SOUND:
		m_pC_sound_button_group->Process();
		break;

	case TAB_GAME:
		m_pC_game_button_group->Process();
		break;
	}
}

//-----------------------------------------------------------------------------
// Start
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_OPTION::Start()
{
	m_bLBPush = false;

	PI_Processor::Start();

	m_pC_button_group->Init();
	m_pC_control_button_group->Init();
	m_pC_graphic_button_group->Init();
	m_pC_sound_button_group->Init();
	m_pC_game_button_group->Init();

//	if(false == m_IsTitle)
//	{
//		if(m_pC_main_spk == NULL)
//		{
//			switch(g_eRaceInterface)
//			{
//			case RACE_SLAYER:
//				m_pC_main_spk = new C_SPRITE_PACK(SPK_OPTION_SLAYER);
//				break;
//
//			case RACE_VAMPIRE:
//				m_pC_main_spk = new C_SPRITE_PACK(SPK_OPTION_VAMPIRE);
//				break;
//
//			case RACE_OUSTERS:
//				m_pC_main_spk = new C_SPRITE_PACK(SPK_OPTION_OUSTERS);
//				break;
//			}
//			
//			m_pC_etc_spk = new C_SPRITE_PACK(SPK_OPTION);
//		}
//	}
	// ³Ý¸¶ºíÀÏ°æ¿ì¿¡´Â g_pUserInformation ÀÇ bNetmarbleGoreLevel ¸¦ »ç¿ëÇÏÀÚ.
	// false ÀÏ °æ¿ì°¡ teenversion.
	
	if(!gC_vs_ui.IsGameMode())
	{
		// ¸Þ´º¿¡¼­ ³Ý¸¶ºí Æ¾¹öÁ¯ÀÌ¸é °­Á¦ ¼³Á¤ÈÄ Disable ±×·¸Áö ¾ÊÀ¸¸é ¿É¼Ç¿¡ µû¸¥´Ù.
		if(!g_pUserInformation->bNetmarbleGoreLevel&&g_pUserInformation->IsNetmarble)
			m_check[CHECK_TEEN_VERSION] = CHECK_CHECK_DISABLE;			
		else
			m_check[CHECK_TEEN_VERSION] = g_pUserOption->UseTeenVersion?CHECK_CHECK:CHECK_NOT;
	} else		
	{
		// ³Ý¸¶ºí Æ¾¹öÁ¯ÀÌ¸é °­Á¦ ¼³Á¤. ±×·¸Áö ¾ÊÀ¸¸é ¿É¼Ç¿¡ µû¸¥´Ù.
		if(!g_pUserInformation->bNetmarbleGoreLevel&&g_pUserInformation->IsNetmarble)
		{
			// °×ÁßÀÌ¸é
			m_check[CHECK_TEEN_VERSION] = g_pUserInformation->bNetmarbleGoreLevel ? CHECK_DISABLE : CHECK_CHECK_DISABLE ;

		} else
		{
			if(g_pUserInformation->GoreLevel)
				m_check[CHECK_TEEN_VERSION] = g_pUserOption->UseTeenVersion?CHECK_CHECK_DISABLE:CHECK_DISABLE;
			else
				m_check[CHECK_TEEN_VERSION] = CHECK_CHECK_DISABLE;		
		}
	}



	if(g_bEnable3DHAL && !gC_vs_ui.IsGameMode())
	{
		m_check[CHECK_3D] = g_pUserOption->Use3DHAL?CHECK_CHECK:CHECK_NOT;
	}
	else
		m_check[CHECK_3D] = g_pUserOption->Use3DHAL?CHECK_CHECK_DISABLE:CHECK_DISABLE;


	m_pC_scroll_bar->SetPosMax(MAX_ACCELERATOR-14-7+1);
	m_focus_hotkey = -1;

	gpC_window_manager->AppearWindow(this);
}

void C_VS_UI_OPTION::Finish()
{
	if(m_pC_main_spk)
	{
		DeleteNew(m_pC_main_spk);
		m_pC_main_spk = NULL;
		DeleteNew(m_pC_etc_spk);
		m_pC_etc_spk = NULL;
	}
	PI_Processor::Finish();

	gpC_window_manager->DisappearWindow(this);
}

//-----------------------------------------------------------------------------
// Run
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_OPTION::Run(id_t id)
{
	switch (id)
	{
	case KEY_DEFAULT_INIT:	// Å¸ÀÌÆ² ¹öÆ° ÃÊ±âÈ­
		{
		#if __CONTENTS(__080405_FIREST_UI_UPDATE)
			// Ã¹È­¸é ¿É¼ÇÃ¢¿¡¼­ ¼³Á¤ÃÊ±âÈ­ ´ÙÀÌ¾ó·Î±× ¶ç¿ì±âÀü¿¡ ¿É¼ÇÃ¢ ¾Æ¹«°÷ÀÌ³ª Å¬¸¯ÇÑÈÄ ¼³Á¤ÃÊ±âÈ­Ã¢ ¶ç¿ì¸é
			// È®ÀÎ Ãë¼Ò ¹öÆ°ÀÌ È°¼º¾ÈµÇ´ø ¹ö±×¼öÁ¤
			ClearInputState();
		#endif //__080405_FIREST_UI_UPDATE

			DeleteNew(m_pC_dialog);
			m_pC_dialog = new C_VS_UI_DIALOG(-1, -1, 3, 0, ExecF_OptionResetButton, DIALOG_TITLE_OK|DIALOG_TITLE_CANCEL);
			
			char * pp_dmsg[1] = {
					(*g_pGameStringTable)[UI_STRING_MESSAGE_KEYSETTING_INIT].GetString(),
			};
			m_pC_dialog->SetMessage( pp_dmsg, 1, SMO_NOFIT , true );
			m_pC_dialog->Start();
		}
		break;

#if __CONTENTS(__080405_FIREST_UI_UPDATE)
	case RESET_ID:	// °ÔÀÓ³» ¹öÆ° ÃÊ±âÈ­
		{
			ClearInputState();

			DeleteNew(m_pC_dialog);
			m_pC_dialog = new C_VS_UI_DIALOG(-1, -1, 3, 0, ExecF_OptionResetButton, DIALOG_TITLE_OK|DIALOG_TITLE_CANCEL);
			
			char * pp_dmsg[1] = {
					(*g_pGameStringTable)[UI_STRING_MESSAGE_KEYSETTING_INIT].GetString(),
			};
			m_pC_dialog->SetMessage( pp_dmsg, 1, SMO_NOFIT , true );
			m_pC_dialog->Start();
		}
		break;
#endif //__080405_FIREST_UI_UPDATE

	//	case DEFAULT_ID:
//		gC_vs_ui.StartGame(false);
//		break;

//	case SAVE_ID:
//		{
//			char sz_filename[512];
//			wsprintf(sz_filename, "UserSet\\%s.set", g_char_slot_ingame.sz_name);
//			
//			ofstream file(sz_filename, ios::binary);
//			
//			if(file)
//			{
//				gpC_vs_ui_window_manager->SaveToFile(file);
//				file.close();
//			}
//		}
//		break;
//
//	case LOAD_ID:
//		{
//			// window_set file loading
//			char sz_filename[512];
//			wsprintf(sz_filename, "UserSet\\%s.set", g_char_slot_ingame.sz_name);
//			
//			ifstream file(sz_filename, ios::binary | ios::nocreate);
//			
//			if(file)
//			{
//				gpC_vs_ui_window_manager->LoadFromFile(file);
//				file.close();
//			}
//			gC_vs_ui.StartGame(true, false);
//		}
//		break;

	case CLOSE_ID:
		gpC_base->SendMessage(UI_CLOSE_OPTION);
		break;

	case CONTROL_ID:
		m_i_selected_tab = TAB_CONTROL;
		break;

	case GRAPHIC_ID:
		m_i_selected_tab = TAB_GRAPHIC;
		break;

	case SOUND_ID:
		m_i_selected_tab = TAB_SOUND;
		break;

	case GAME_ID:
		m_i_selected_tab = TAB_GAME;
		break;

	// CONTROL TAB
	case CHECK_NORMAL_CHAT:
	case CHECK_ENTER_CHAT:
		{
			g_pUserOption->UseEnterChat = (id == CHECK_ENTER_CHAT);
			m_check[CHECK_NORMAL_CHAT] = g_pUserOption->UseEnterChat?CHECK_NOT:CHECK_CHECK;
			m_check[CHECK_ENTER_CHAT] = g_pUserOption->UseEnterChat?CHECK_CHECK:CHECK_NOT;
		}
		break;

	case CHECK_RESOLUTION_800x600:
	case CHECK_RESOLUTION_1024x768:
		{
// 			if(m_IsTitle)
// 			{
// 				g_pUserOption->Resolution1024 = (id == CHECK_RESOLUTION_1024x768);
// 				m_check[CHECK_RESOLUTION_800x600]	= CHECK_TYPE(!g_pUserOption->Resolution1024);
// 				m_check[CHECK_RESOLUTION_1024x768]	= CHECK_TYPE(g_pUserOption->Resolution1024);
// 			}
		}
		break;

	case CHECK_IFEEL:
		if(m_check[CHECK_IFEEL] != CHECK_DISABLE)
		{
			m_check[CHECK_IFEEL] = (m_check[CHECK_IFEEL] == CHECK_CHECK)?CHECK_NOT:CHECK_CHECK;
			g_pUserOption->UseForceFeel = m_check[CHECK_IFEEL] == CHECK_CHECK;
			if(gpC_Imm && g_pUserOption->UseForceFeel)gpC_Imm->Enable();
			else if(gpC_Imm)gpC_Imm->Disable();
		}
		break;

//	case CHECK_MOUSE_SPEED:
//		if(m_check[CHECK_MOUSE_SPEED] != CHECK_DISABLE)
//		{
//			m_check[CHECK_MOUSE_SPEED] = (m_check[CHECK_MOUSE_SPEED] == CHECK_CHECK)?CHECK_NOT:CHECK_CHECK;
//			g_pUserOption->UseMouseSpeed = m_check[CHECK_MOUSE_SPEED] == CHECK_CHECK;
//		}
		break;

	// GRAPHIC TAB
	case CHECK_3D:
		if(m_check[CHECK_3D] != CHECK_DISABLE && m_check[CHECK_3D] != CHECK_CHECK_DISABLE)
		{
			m_check[CHECK_3D] = (m_check[CHECK_3D] == CHECK_CHECK)?CHECK_NOT:CHECK_CHECK;
			g_pUserOption->Use3DHAL = m_check[CHECK_3D] == CHECK_CHECK;
		}
		break;

	case CHECK_ALPHA_HPBAR:
		if(m_check[CHECK_ALPHA_HPBAR] != CHECK_DISABLE)
		{
			m_check[CHECK_ALPHA_HPBAR] = (m_check[CHECK_ALPHA_HPBAR] == CHECK_CHECK)?CHECK_NOT:CHECK_CHECK;
			g_pUserOption->DrawTransHPBar = m_check[CHECK_ALPHA_HPBAR] == CHECK_CHECK;
		}
		break;

	case CHECK_BLOOD_DROP:
		if(m_check[CHECK_BLOOD_DROP] != CHECK_DISABLE)
		{
			m_check[CHECK_BLOOD_DROP] = (m_check[CHECK_BLOOD_DROP] == CHECK_CHECK)?CHECK_NOT:CHECK_CHECK;
			g_pUserOption->BloodDrop = m_check[CHECK_BLOOD_DROP] == CHECK_CHECK;
		}
		break;

	case CHECK_AUTOHIDE_SMOOTH:
		if(m_check[CHECK_AUTOHIDE_SMOOTH] != CHECK_DISABLE)
		{
			m_check[CHECK_AUTOHIDE_SMOOTH] = (m_check[CHECK_AUTOHIDE_SMOOTH] == CHECK_CHECK)?CHECK_NOT:CHECK_CHECK;
			g_pUserOption->AutoHideSmoothScroll = m_check[CHECK_AUTOHIDE_SMOOTH] == CHECK_CHECK;
		}
		break;

	case CHECK_GAMMA:
		if(m_check[CHECK_GAMMA] != CHECK_DISABLE)
		{
			m_check[CHECK_GAMMA] = (m_check[CHECK_GAMMA] == CHECK_CHECK)?CHECK_NOT:CHECK_CHECK;
			g_pUserOption->UseGammaControl = m_check[CHECK_GAMMA] == CHECK_CHECK;
			if(g_pUserOption->UseGammaControl)CDirectDraw::SetGammaRamp(m_value_gamma);
			else if(CDirectDraw::IsSupportGammaControl())
				CDirectDraw::RestoreGammaRamp();
		}
		break;

	case CHECK_CHATBOX:
		if(m_check[CHECK_CHATBOX] != CHECK_DISABLE)
		{
			m_check[CHECK_CHATBOX] = (m_check[CHECK_CHATBOX] == CHECK_CHECK)?CHECK_NOT:CHECK_CHECK;
			g_pUserOption->DrawChatBoxOutline = m_check[CHECK_CHATBOX] == CHECK_CHECK;
		}
		break;

	case CHECK_FPS:
		if(m_check[CHECK_FPS] != CHECK_DISABLE)
		{
			m_check[CHECK_FPS] = (m_check[CHECK_FPS] == CHECK_CHECK)?CHECK_NOT:CHECK_CHECK;
			g_pUserOption->DrawFPS = m_check[CHECK_FPS] == CHECK_CHECK;
		}
		break;

	case CHECK_DEFAULT_ALPHA:
		if(m_check[CHECK_DEFAULT_ALPHA] != CHECK_DISABLE)
		{
			m_check[CHECK_DEFAULT_ALPHA] = (m_check[CHECK_DEFAULT_ALPHA] == CHECK_CHECK)?CHECK_NOT:CHECK_CHECK;
			g_pUserOption->DefaultAlpha = m_check[CHECK_DEFAULT_ALPHA] == CHECK_CHECK;
		}
		break;

	// SOUND TAB
//	case CHECK_YELL:
//		if(m_check[CHECK_YELL] != CHECK_DISABLE)
//		{
//			m_check[CHECK_YELL] = (m_check[CHECK_YELL] == CHECK_CHECK)?CHECK_NOT:CHECK_CHECK;
//			g_pUserOption->PlayYellSound = m_check[CHECK_YELL] == CHECK_CHECK;
//		}
//		break;

	case CHECK_SOUND://È¿°úÀ½
		Effect_Music_ONOFF(CHECK_SOUND);
	/*	if(m_check[CHECK_SOUND] != CHECK_DISABLE)
		{
			m_check[CHECK_SOUND] = (m_check[CHECK_SOUND] == CHECK_CHECK)?CHECK_NOT:CHECK_CHECK;
			g_pUserOption->PlaySound = m_check[CHECK_SOUND] == CHECK_CHECK;

//			if(g_pUserOption->PlaySound)m_check[CHECK_YELL] = g_pUserOption->PlayYellSound?CHECK_CHECK:CHECK_NOT;
//			else m_check[CHECK_YELL] = CHECK_DISABLE;

			gpC_base->SendMessage( UI_CHANGE_OPTION, CHECK_SOUND, m_check[CHECK_SOUND] == CHECK_CHECK );
		}*/
		break;

	case CHECK_MUSIC://¹è°æÀ½
		Background_Music_ONOFF(CHECK_MUSIC);
	/*	if(m_check[CHECK_MUSIC] != CHECK_DISABLE)
		{
			m_check[CHECK_MUSIC] = (m_check[CHECK_MUSIC] == CHECK_CHECK)?CHECK_NOT:CHECK_CHECK;
			g_pUserOption->PlayMusic = m_check[CHECK_MUSIC] == CHECK_CHECK;
			gpC_base->SendMessage( UI_CHANGE_OPTION, CHECK_MUSIC, m_check[CHECK_MUSIC] == CHECK_CHECK );

			if(g_pUserOption->PlayMusic)
			{
				m_check[CHECK_WAV] = g_pUserOption->PlayWaveMusic?CHECK_CHECK:CHECK_NOT;
				m_check[CHECK_MIDI] = g_pUserOption->PlayWaveMusic?CHECK_NOT:CHECK_CHECK;
			}
			else
			{
				m_check[CHECK_WAV] = CHECK_DISABLE;
				m_check[CHECK_MIDI] = CHECK_DISABLE;
			}
		}*/
		break;

	case CHECK_WAV:
	case CHECK_MIDI:
		if(m_check[CHECK_WAV] != CHECK_DISABLE)
		{
			g_pUserOption->PlayWaveMusic = id == CHECK_WAV;
			m_check[CHECK_WAV] = g_pUserOption->PlayWaveMusic?CHECK_CHECK:CHECK_NOT;
			m_check[CHECK_MIDI] = g_pUserOption->PlayWaveMusic?CHECK_NOT:CHECK_CHECK;
			gpC_base->SendMessage( UI_CHANGE_OPTION, CHECK_WAV, m_check[CHECK_WAV] == CHECK_CHECK );
		}
		break;

	// GAME TAB
	case CHECK_HELP:
		if(m_check[CHECK_HELP] != CHECK_DISABLE)
		{
			m_check[CHECK_HELP] = (m_check[CHECK_HELP] == CHECK_CHECK)?CHECK_NOT:CHECK_CHECK;
			g_pUserOption->ShowChoboHelp = m_check[CHECK_HELP] == CHECK_CHECK;
		}
		break;

	case CHECK_FILTERING:
		if(m_check[CHECK_FILTERING] != CHECK_DISABLE)
		{
			m_check[CHECK_FILTERING] = (m_check[CHECK_FILTERING] == CHECK_CHECK)?CHECK_NOT:CHECK_CHECK;
			g_pUserOption->FilteringCurse = m_check[CHECK_FILTERING] == CHECK_CHECK;
		}
		break;

//	case CHECK_CHANGE:
//		if(m_check[CHECK_CHANGE] != CHECK_DISABLE)
//		{
//			m_check[CHECK_CHANGE] = (m_check[CHECK_CHANGE] == CHECK_CHECK)?CHECK_NOT:CHECK_CHECK;
//			g_pUserOption->TribeChange = m_check[CHECK_CHANGE] == CHECK_CHECK;
//		}
//		break;
//
//	case CHECK_PARTY_INVITE:
//		if(m_check[CHECK_PARTY_INVITE] != CHECK_DISABLE)
//		{
//			m_check[CHECK_PARTY_INVITE] = (m_check[CHECK_PARTY_INVITE] == CHECK_CHECK)?CHECK_NOT:CHECK_CHECK;
//			g_pUserOption->DenyPartyInvite = m_check[CHECK_PARTY_INVITE] == CHECK_CHECK;
//		}
//		break;
//
//	case CHECK_PARTY_REQUEST:
//		if(m_check[CHECK_PARTY_REQUEST] != CHECK_DISABLE)
//		{
//			m_check[CHECK_PARTY_REQUEST] = (m_check[CHECK_PARTY_REQUEST] == CHECK_CHECK)?CHECK_NOT:CHECK_CHECK;
//			g_pUserOption->DenyPartyRequest = m_check[CHECK_PARTY_REQUEST] == CHECK_CHECK;
//		}
//		break;

	case CHECK_PRELOAD_MONSTER:
		if(m_check[CHECK_PRELOAD_MONSTER] != CHECK_DISABLE)
		{
			m_check[CHECK_PRELOAD_MONSTER] = (m_check[CHECK_PRELOAD_MONSTER] == CHECK_CHECK)?CHECK_NOT:CHECK_CHECK;
			g_pUserOption->IsPreLoadMonster = m_check[CHECK_PRELOAD_MONSTER] == CHECK_CHECK;
		}
		break;

	case CHECK_CHAT_WHITE:
		if(m_check[CHECK_CHAT_WHITE] != CHECK_DISABLE)
		{
			m_check[CHECK_CHAT_WHITE] = (m_check[CHECK_CHAT_WHITE] == CHECK_CHECK)?CHECK_NOT:CHECK_CHECK;
			g_pUserOption->ChatWhite = m_check[CHECK_CHAT_WHITE] == CHECK_CHECK;
		}
		break;
	case CHECK_TEEN_VERSION :
		if(m_check[CHECK_TEEN_VERSION] != CHECK_DISABLE&& m_check[CHECK_TEEN_VERSION] != CHECK_CHECK_DISABLE)
		{
			m_check[CHECK_TEEN_VERSION] = (m_check[CHECK_TEEN_VERSION] == CHECK_CHECK)?CHECK_NOT:CHECK_CHECK;
			g_pUserOption->UseTeenVersion = m_check[CHECK_TEEN_VERSION] == CHECK_CHECK;
		}
		break;
	case CHECK_POPUPCHAT_BY_WHISPER :
		if(m_check[CHECK_POPUPCHAT_BY_WHISPER] != CHECK_DISABLE)
		{
			m_check[CHECK_POPUPCHAT_BY_WHISPER] = (m_check[CHECK_POPUPCHAT_BY_WHISPER] == CHECK_CHECK)?CHECK_NOT:CHECK_CHECK;
			g_pUserOption->PopupChatByWhisper = m_check[CHECK_POPUPCHAT_BY_WHISPER] == CHECK_CHECK;
		}
		break;
	case CHECK_DO_NOT_SHOW_WAR_MSG :
		if(m_check[CHECK_DO_NOT_SHOW_WAR_MSG] != CHECK_DISABLE )
		{
			m_check[CHECK_DO_NOT_SHOW_WAR_MSG] = (m_check[CHECK_DO_NOT_SHOW_WAR_MSG] == CHECK_CHECK) ? CHECK_NOT:CHECK_CHECK;
			g_pUserOption->DoNotShowWarMsg = m_check[CHECK_DO_NOT_SHOW_WAR_MSG] == CHECK_CHECK;
		}
		break;
	case CHECK_DO_NOT_SHOW_LAIR_MSG :
		if(m_check[CHECK_DO_NOT_SHOW_LAIR_MSG] != CHECK_DISABLE )
		{
			m_check[CHECK_DO_NOT_SHOW_LAIR_MSG] = (m_check[CHECK_DO_NOT_SHOW_LAIR_MSG] == CHECK_CHECK) ? CHECK_NOT:CHECK_CHECK;
			g_pUserOption->DoNotShowLairMsg = m_check[CHECK_DO_NOT_SHOW_LAIR_MSG] == CHECK_CHECK;
		}
		break;
	case CHECK_DO_NOT_SHOW_HOLY_LAND_MSG :
		if(m_check[CHECK_DO_NOT_SHOW_HOLY_LAND_MSG] != CHECK_DISABLE )
		{
			m_check[CHECK_DO_NOT_SHOW_HOLY_LAND_MSG] = (m_check[CHECK_DO_NOT_SHOW_HOLY_LAND_MSG] == CHECK_CHECK) ? CHECK_NOT:CHECK_CHECK;
			g_pUserOption->DoNotShowHolyLandMsg = m_check[CHECK_DO_NOT_SHOW_HOLY_LAND_MSG] == CHECK_CHECK;
		}
		break;

#if __CONTENTS(__GAMEOPTION_ITEMBAY_MESSAGEBOX)
	case CHECK_DO_NOT_SHOW_ITEMBAY_MESSAGEBOX :
		if(m_check[CHECK_DO_NOT_SHOW_ITEMBAY_MESSAGEBOX] != CHECK_DISABLE )
		{
			m_check[CHECK_DO_NOT_SHOW_ITEMBAY_MESSAGEBOX] = (m_check[CHECK_DO_NOT_SHOW_ITEMBAY_MESSAGEBOX] == CHECK_CHECK) ? CHECK_NOT:CHECK_CHECK;
			g_pUserOption->DoNotShowItemBayMessageBox = m_check[CHECK_DO_NOT_SHOW_ITEMBAY_MESSAGEBOX] == CHECK_CHECK;
		}
		break;
#endif

#if __CONTENTS(__LANGUAGE_CHANGE)
	case CHECK_SHOW_GAMEMONEY_WITH_HANGUL:
		if(m_check[CHECK_SHOW_GAMEMONEY_WITH_HANGUL] != CHECK_DISABLE )
		{
			m_check[CHECK_SHOW_GAMEMONEY_WITH_HANGUL] = (m_check[CHECK_SHOW_GAMEMONEY_WITH_HANGUL] == CHECK_CHECK) ? CHECK_NOT:CHECK_CHECK;
			g_pUserOption->ShowGameMoneyWithHANGUL = m_check[CHECK_SHOW_GAMEMONEY_WITH_HANGUL] == CHECK_CHECK;
		}
		break;
#endif	//__LANGUAGE_CHANGE
	case CHECK_DO_NOT_SHOW_PERSNALSHOP_MSG:
		if(m_check[CHECK_DO_NOT_SHOW_PERSNALSHOP_MSG] != CHECK_DISABLE )
		{
			m_check[CHECK_DO_NOT_SHOW_PERSNALSHOP_MSG] = (m_check[CHECK_DO_NOT_SHOW_PERSNALSHOP_MSG] == CHECK_CHECK) ? CHECK_NOT:CHECK_CHECK;
			g_pUserOption->DoNotShowPersnalShopMsg = m_check[CHECK_DO_NOT_SHOW_PERSNALSHOP_MSG] == CHECK_CHECK;
		}
		break;
#if __CONTENTS(__JAPAN_UI)
	case CHECK_ONE_CLICK_ATTACK_OFF:
		if(m_check[CHECK_ONE_CLICK_ATTACK_OFF] != CHECK_DISABLE )
		{
			m_check[CHECK_ONE_CLICK_ATTACK_OFF] = (m_check[CHECK_ONE_CLICK_ATTACK_OFF] == CHECK_CHECK) ? CHECK_NOT:CHECK_CHECK;
			g_pUserOption->DoNotOneClickAttackOff = m_check[CHECK_ONE_CLICK_ATTACK_OFF] == CHECK_CHECK;
		}
		break;
#endif //__JAPAN_UI
//	case CHECK_NOT_SEND_MY_INFO :
//		if(m_check[CHECK_NOT_SEND_MY_INFO] != CHECK_DISABLE)
//		{
//			m_check[CHECK_NOT_SEND_MY_INFO] = (m_check[CHECK_NOT_SEND_MY_INFO] == CHECK_CHECK)? CHECK_NOT : CHECK_CHECK ;
//			g_pUserOption->NotSendMyInfo = m_check[CHECK_NOT_SEND_MY_INFO] == CHECK_CHECK;
//		}
//		break;
	}

}


void	C_VS_UI_OPTION::SetValue(int _x, enum VALUE_RECT rect_value)
{
	if(rect_value >= RECT_MAX)return;

	_x = min(m_rt_value[rect_value].x+m_rt_value[rect_value].w, max(m_rt_value[rect_value].x, _x));
	_x -= m_rt_value[rect_value].x;

	switch(rect_value)
	{
	case RECT_MOUSE_SPEED:
		m_value_mouse_speed = _x*MAX_MOUSE_SPEED/m_rt_value[rect_value].w;
		break;

	case RECT_GAMMA:
		m_value_gamma = MIN_GAMMA_VALUE+_x*MAX_GAMMA_VALUE/m_rt_value[rect_value].w;
		break;

	case RECT_SOUND:
		m_volume_sound = _x*MAX_SOUND_VOLUME/m_rt_value[rect_value].w;
		break;

	case RECT_MUSIC:
		m_volume_music = _x*MAX_MUSIC_VOLUME/m_rt_value[rect_value].w;
		break;

	case RECT_ALPHA:
		g_pUserOption->ALPHA_DEPTH = _x*MAX_ALPHA_DEPTH/m_rt_value[rect_value].w;
		break;
	}
}

/*-----------------------------------------------------------------------------
- MouseControl
-
-----------------------------------------------------------------------------*/
bool C_VS_UI_OPTION::MouseControl(UINT message, int _x, int _y)
{
	static VALUE_RECT value = RECT_MOUSE_SPEED;

	if(false == m_IsTitle)
		_x -=m_vampire_plus_x; _y-=m_vampire_plus_y;
	
	//Window::MouseControl(message, _x, _y);
	_x -=x; _y-=y;
	
	bool re = m_pC_button_group->MouseControl(message, _x, _y);

	switch(m_i_selected_tab)
	{
	case TAB_CONTROL:
		re &= m_pC_control_button_group->MouseControl(message, _x, _y);
		re &= m_pC_scroll_bar->MouseControl(message, _x, _y);
		break;

	case TAB_GRAPHIC:
		re &= m_pC_graphic_button_group->MouseControl(message, _x, _y);
		break;

	case TAB_SOUND:
		re &= m_pC_sound_button_group->MouseControl(message, _x, _y);
		break;

	case TAB_GAME:
		re &= m_pC_game_button_group->MouseControl(message, _x, _y);
		break;
	}

	switch (message)
	{
		case M_MOVING :
			{
				m_focus_hotkey = -1;
				const int accel_gap = 15;
				int TitleOffset_x = 0;
				int TitleOffset_y = 0;
				if(true == m_IsTitle)
				{
					TitleOffset_x = -115;
					TitleOffset_y = -20;
				}
				if(m_i_selected_tab == TAB_CONTROL && _x > 125 +TitleOffset_x && _x < 368+TitleOffset_x && _y > 100 + TitleOffset_y && _y < 102+accel_gap*7+TitleOffset_y)
				{
					m_focus_hotkey = (_y - 100 - TitleOffset_y)/accel_gap;
					if(m_focus_hotkey > 6)
					{
						m_focus_hotkey = -1;
						break;
					}
					m_focus_hotkey += m_pC_scroll_bar->GetScrollPos();
				}
			}
			if(m_bLBPush)
			{
				SetValue(_x, value);
			}
		break;

		case M_LEFTBUTTON_DOWN:
		case M_LB_DOUBLECLICK:
//			if(m_i_selected_tab == TAB_CONTROL && m_check[CHECK_MOUSE_SPEED] && m_rt_value[RECT_MOUSE_SPEED].IsInRect(_x, _y))
//			{
//				m_bLBPush = true;
//				value = RECT_MOUSE_SPEED;
//				SetValue(_x, value);
//			}
//			else 
			if(m_i_selected_tab == TAB_CONTROL && m_focus_hotkey != -1)
			{
				gC_vs_ui.SetAccelMode(ACCEL_NULL+14+m_focus_hotkey);
			}
			if(m_i_selected_tab == TAB_GRAPHIC && (m_check[CHECK_GAMMA] && m_rt_value[RECT_GAMMA].IsInRect(_x, _y) || m_check[CHECK_ALPHA_DEPTH] && m_rt_value[RECT_ALPHA].IsInRect(_x, _y)))
			{
				m_bLBPush = true;
				if(m_rt_value[RECT_GAMMA].IsInRect(_x, _y))
					value = RECT_GAMMA;
				else
					value = RECT_ALPHA;
				SetValue(_x, value);
			}
			else if(m_i_selected_tab == TAB_SOUND && (m_rt_value[RECT_SOUND].IsInRect(_x, _y) && m_check[CHECK_SOUND] || m_rt_value[RECT_MUSIC].IsInRect(_x, _y) && m_check[CHECK_MUSIC]))
			{
				m_bLBPush = true;
				if(m_rt_value[RECT_SOUND].IsInRect(_x, _y))
					value = RECT_SOUND;
				else
					value = RECT_MUSIC;
				SetValue(_x, value);
			}
			else

			if (gpC_mouse_pointer->GetPickUpItem() == false && re)
			{
				MoveReady();
				SetOrigin(_x, _y);
				break;
			}
			break;

		case M_LEFTBUTTON_UP:
			if(m_bLBPush)
			{
				m_bLBPush = false;
				switch(value)
				{
				case RECT_MOUSE_SPEED:
					gpC_base->SendMessage( UI_CHANGE_OPTION, CHECK_VALUE_MOUSE_SPEED, m_value_mouse_speed );
					break;

				case RECT_GAMMA:
					if(CDirectDraw::IsSupportGammaControl() && m_check[CHECK_GAMMA])
						CDirectDraw::SetGammaRamp(m_value_gamma);
					g_pUserOption->GammaValue = m_value_gamma;
					break;

				case RECT_SOUND:
					gpC_base->SendMessage( UI_CHANGE_OPTION, CHECK_VALUE_SOUND_VOLUME, m_volume_sound );
					break;

				case RECT_MUSIC:
					gpC_base->SendMessage( UI_CHANGE_OPTION, CHECK_VALUE_MUSIC_VOLUME, m_volume_music );
					break;

				case RECT_ALPHA:
					break;
				}
			}
		break;
		
		case M_WHEEL_UP:
			m_pC_scroll_bar->ScrollUp();
			EMPTY_MOVE;
			break;

		case M_WHEEL_DOWN:
			m_pC_scroll_bar->ScrollDown();
			EMPTY_MOVE;
			break;
	}


	return true;
}

/*-----------------------------------------------------------------------------
- KeyboardControl
-
-----------------------------------------------------------------------------*/
void C_VS_UI_OPTION::KeyboardControl(UINT message, UINT key, long extra)
{
	// ¸¸¾à IME toggleµÇ¾î ÀÖÀ» °æ¿ì¸¦ ´ëºñÇÏ¿© scan code·Î ÇÑ´Ù.

	if (message == WM_KEYDOWN)
	{	
//		if(gC_vs_ui.IsAccelMode() && key==VK_ESCAPE)
//			gC_vs_ui.UnSetAccelMode();
//		else
		if (!gC_vs_ui.IsAccelMode() && !gC_vs_ui.IsInputHotkey() && key==VK_ESCAPE)
		{
			gpC_base->SendMessage( UI_CLOSE_OPTION );
		}
	}
}

/*-----------------------------------------------------------------------------
- Show
-
-----------------------------------------------------------------------------*/
void C_VS_UI_OPTION::Show()
{
	static const char scancode_name[256][20] = 
	{
		"",						// 0x00
		"ESCAPE",				// 0x01
		"1",					// 0x02
		"2",					// 0x03
		"3",					// 0x04
		"4",					// 0x05
		"5",					// 0x06
		"6",					// 0x07
		"7",					// 0x08
		"8",					// 0x09
		"9",					// 0x0A
		"0",					// 0x0B
		"MINUS",				// 0x0C
		"EQUALS",				// 0x0D
		"BACK",					// 0x0E
		"TAB",					// 0x0F
		"Q",					// 0x10
		"W",					// 0x11
		"E",					// 0x12
		"R",					// 0x13
		"T",					// 0x14
		"Y",					// 0x15
		"U",					// 0x16
		"I",					// 0x17
		"O",					// 0x18
		"P",					// 0x19
		"LBRACKET",				// 0x1A
		"RBRACKET",				// 0x1B
		"RETURN",				// 0x1C
		"LCONTROL",				// 0x1D
		"A",					// 0x1E
		"S",					// 0x1F
		"D",					// 0x20
		"F",					// 0x21
		"G",					// 0x22
		"H",					// 0x23
		"J",					// 0x24
		"K",					// 0x25
		"L",					// 0x26
		":",					// 0x27
		"'",					// 0x28
		"~",					// 0x29
		"LSHIFT",				// 0x2A
		"BACKSLASH",			// 0x2B
		"Z",					// 0x2C
		"X",					// 0x2D
		"C",					// 0x2E
		"V",					// 0x2F
		"B",					// 0x30
		"N",					// 0x31
		"M",					// 0x32
		"COMMA",				// 0x33
		"PERIOD",				// 0x34
		"SLASH",				// 0x35
		"RSHIFT",				// 0x36
		"MULTIPLY",				// 0x37
		"LMENU",				// 0x38
		"SPACE",				// 0x39
		"CAPITAL",				// 0x3A
		"F1",					// 0x3B
		"F2",					// 0x3C
		"F3",					// 0x3D
		"F4",					// 0x3E
		"F5",					// 0x3F
		"F6",					// 0x40
		"F7",					// 0x41
		"F8",					// 0x42
		"F9",					// 0x43
		"F10",					// 0x44
		"NUMLOCK",				// 0x45
		"SCROLL",				// 0x46
		"NUMPAD7",				// 0x47
		"NUMPAD8",				// 0x48
		"NUMPAD9",				// 0x49
		"SUBTRACT",				// 0x4A
		"NUMPAD4",				// 0x4B
		"NUMPAD5",				// 0x4C
		"NUMPAD6",				// 0x4D
		"ADD",					// 0x4E
		"NUMPAD1",				// 0x4F
		"NUMPAD2",				// 0x50
		"NUMPAD3",				// 0x51
		"NUMPAD0",				// 0x52
		"DECIMAL",				// 0x53
		"",						// 0x54
		"",						// 0x55
		"",						// 0x56
		"F11",					// 0x57
		"F12",					// 0x58
		"",						// 0x59
		"",						// 0x5A
		"",						// 0x5B
		"",						// 0x5C
		"",						// 0x5D
		"",						// 0x5E
		"",						// 0x5F
		"",						// 0x60
		"",						// 0x61
		"",						// 0x62
		"",						// 0x63
		"F13",					// 0x64
		"F14",					// 0x65
		"F15",					// 0x66
		"",						// 0x67
		"",						// 0x68
		"",						// 0x69
		"",						// 0x6A
		"",						// 0x6B
		"",						// 0x6C
		"",						// 0x6D
		"",						// 0x6E
		"",						// 0x6F
		"KANA",					// 0x70
		"",						// 0x71
		"",						// 0x72
		"",						// 0x73
		"",						// 0x74
		"",						// 0x75
		"",						// 0x76
		"",						// 0x77
		"",						// 0x78
		"CONVERT",				// 0x79
		"",						// 0x7A
		"NOCONVERT",			// 0x7B
		"",						// 0x7C
		"YEN",					// 0x7D
		"",						// 0x7E
		"",						// 0x7F
		"",						// 0x80
		"",						// 0x81
		"",						// 0x82
		"",						// 0x83
		"",						// 0x84
		"",						// 0x85
		"",						// 0x86
		"",						// 0x87
		"",						// 0x88
		"",						// 0x89
		"",						// 0x8A
		"",						// 0x8B
		"",						// 0x8C
		"NUMPADEQUALS",			// 0x8D
		"",						// 0x8E
		"",						// 0x8F
		"CIRCUMFLEX",			// 0x90
		"AT",					// 0x91
		"COLON",				// 0x92
		"UNDERLINE",			// 0x93
		"KANJI",				// 0x94
		"STOP",					// 0x95
		"AX",					// 0x96
		"UNLABELED",			// 0x97
		"",						// 0x98
		"",						// 0x99
		"",						// 0x9A
		"",						// 0x9B
		"NUMPADENTER",			// 0x9C
		"RCONTROL",				// 0x9D
		"",						// 0x9E
		"",						// 0x9F
		"",						// 0xA0
		"",						// 0xA1
		"",						// 0xA2
		"",						// 0xA3
		"",						// 0xA4
		"",						// 0xA5
		"",						// 0xA6
		"",						// 0xA7
		"",						// 0xA8
		"",						// 0xA9
		"",						// 0xAA
		"",						// 0xAB
		"",						// 0xAC
		"",						// 0xAD
		"",						// 0xAE
		"",						// 0xAF
		"",						// 0xB0
		"",						// 0xB1
		"",						// 0xB2
		"NUMPADCOMMA",			// 0xB3
		"",						// 0xB4
		"DIVIDE",				// 0xB5
		"",						// 0xB6
		"SYSRQ",				// 0xB7
		"RMENU",				// 0xB8
		"",						// 0xB9
		"",						// 0xBA
		"",						// 0xBB
		"",						// 0xBC
		"",						// 0xBD
		"",						// 0xBE
		"",						// 0xBF
		"",						// 0xC0
		"",						// 0xC1
		"",						// 0xC2
		"",						// 0xC3
		"",						// 0xC4
		"PAUSE",				// 0xC5
		"",						// 0xC6
		"HOME",					// 0xC7
		"UP",					// 0xC8
		"PRIOR",				// 0xC9
		"",						// 0xCA
		"LEFT",					// 0xCB
		"",						// 0xCC
		"RIGHT",				// 0xCD
		"",						// 0xCE
		"END",					// 0xCF
		"DOWN",					// 0xD0
		"NEXT",					// 0xD1
		"INSERT",				// 0xD2
		"DELETE",				// 0xD3
		"",						// 0xD4
		"",						// 0xD5
		"",						// 0xD6
		"",						// 0xD7
		"",						// 0xD8
		"",						// 0xD9
		"",						// 0xDA
		"LWIN",					// 0xDB
		"RWIN",					// 0xDC
		"APPS",					// 0xDD
		"POWER",				// 0xDE
		"SLEEP",				// 0xDF
		"",						// 0xE0
		"",						// 0xE1
		"",						// 0xE2
		"",						// 0xE3
		"",						// 0xE4
		"",						// 0xE5
		"",						// 0xE6
		"",						// 0xE7
		"",						// 0xE8
		"",						// 0xE9
		"",						// 0xEA
		"",						// 0xEB
		"",						// 0xEC
		"",						// 0xED
		"",						// 0xEE
		"",						// 0xEF
		"",						// 0xF0
		"",						// 0xF1
		"",						// 0xF2
		"",						// 0xF3
		"",						// 0xF4
		"",						// 0xF5
		"",						// 0xF6
		"",						// 0xF7
		"",						// 0xF8
		"",						// 0xF9
		"",						// 0xFA
		"",						// 0xFB
		"",						// 0xFC
		"",						// 0xFD
		"",						// 0xFE
		"",						// 0xFF
	};

	const InterfaceInformation* pSkin = &g_pSkinManager->Get( SkinManager::OPTION );

	int i = 0;
//	int tab_x[4] = {pSkin->GetRect(0).left, pSkin->GetRect(0).top, pSkin->GetRect(0).right, pSkin->GetRect(0).bottom}, tab_y = 20;
	
	if(gpC_base->m_p_DDSurface_back->Lock())
	{
		m_pC_main_spk->BltLocked(x, y);
//		if(false == m_IsTitle)
//			m_pC_main_spk->BltLocked(x+tab_x[m_i_selected_tab-TAB_CONTROL]+m_vampire_plus_x, y+tab_y+m_vampire_plus_y, m_i_selected_tab);
//		else
			//m_pC_main_spk->BltLocked(x+Tab_X[m_i_selected_tab-TAB_CONTROL]+m_vampire_plus_x, y+Tab_Y+m_vampire_plus_y, m_i_selected_tab);
			m_pC_main_spk->BltLocked(x,y,0);
			if(m_IsTitle)
			{
				m_pC_main_spk->BltLocked(x + m_pC_main_spk->GetWidth() - 25, y + m_pC_main_spk->GetHeight() - 25, 
					TITLE_BUTTON_EXIT);
			}
		gpC_base->m_p_DDSurface_back->Unlock();
	}
	COLORREF strColor = RGB(0, 0, 0);
	if(m_IsTitle)
	{
		strColor = RGB(150, 150, 150);
	}
	
	switch(m_i_selected_tab)
	{
	case TAB_CONTROL:
		{
			int TitleOffset_x = 0;
			int TitleOffset_y = 0;
			if(m_IsTitle)
			{
				TitleOffset_x = -115;
				TitleOffset_y = -20;
			}
			const std::string check_string[CHECK_CONTROL_MAX] =
			{
//				"Mouse Speed",
				"Logitech IFeel Mouse Force Feedback",
			};

			if(gpC_base->m_p_DDSurface_back->Lock())
			{
				m_pC_main_spk->BltLocked(x+m_vampire_plus_x+125+TitleOffset_x, y+m_vampire_plus_y+80+TitleOffset_y, HOTKEY_WINDOW);
				m_pC_control_button_group->Show();
				gpC_base->m_p_DDSurface_back->Unlock();
			}
			
			g_FL2_GetDC();
//			g_PrintColorStr(x+m_vampire_plus_x+130, y+m_vampire_plus_y+56, "Input Style : ", gpC_base->m_user_id_pi, strColor);
			g_PrintColorStr(x+m_vampire_plus_x+m_check_x+30, y+m_vampire_plus_y+m_check_y, 
				(*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_MENU_NORMAL_CHATTING].GetString(), gpC_base->m_user_id_pi, strColor);
			
			g_PrintColorStr(x+m_vampire_plus_x+m_check_x+140, y+m_vampire_plus_y+m_check_y, 
				(*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_MENU_ENTER_CHATTING].GetString(), gpC_base->m_user_id_pi, strColor);

//			m_pC_etc_spk->Blt(x+m_vampire_plus_x+230, y+m_vampire_plus_y+53, HOTKEY_BACK);
//			m_pC_etc_spk->Blt(x+m_vampire_plus_x+230+m_pC_etc_spk->GetWidth(HOTKEY_BACK), y+m_vampire_plus_y+53, HOTKEY_BACK_RIGHT);
			
			for(i = 0; i < CHECK_CONTROL_MAX; i++)
			{
				if(m_IsTitle)
				{
					g_PrintColorStr(x+m_vampire_plus_x+m_check_x+5, y+m_vampire_plus_y+m_check_y+m_check_gap*(8+i), check_string[i].c_str(), gpC_base->m_user_id_pi, strColor);
				}
				else
				{
					g_PrintColorStr(x+m_vampire_plus_x+m_check_x+15, y+m_vampire_plus_y+m_check_y+m_check_gap*(8+i), check_string[i].c_str(), gpC_base->m_user_id_pi, strColor);
				}
			
			}
//			m_pC_etc_spk->Blt(x+m_vampire_plus_x+m_rt_value[RECT_MOUSE_SPEED].x, y+m_vampire_plus_y+m_rt_value[RECT_MOUSE_SPEED].y+5, VOLUME_BAR);
//			if(m_check[CHECK_MOUSE_SPEED])
//				m_pC_etc_spk->Blt(x+m_vampire_plus_x+m_rt_value[RECT_MOUSE_SPEED].x-m_pC_etc_spk->GetWidth(VOLUME_TAG)/2+m_value_mouse_speed*m_rt_value[RECT_MOUSE_SPEED].w/MAX_MOUSE_SPEED, y+m_vampire_plus_y+m_rt_value[RECT_MOUSE_SPEED].y, VOLUME_TAG);
			
			// Accelator
			const int accel_count = MAX_ACCELERATOR;
			const int accel_gap = 15;
			for(i = 0; i < min(accel_count, 7); i++)
			{
				const BYTE accel = ACCEL_NULL+i+14+m_pC_scroll_bar->GetScrollPos();
				const char *pAccelName = g_pKeyAccelerator->GetName(accel);
				g_PrintColorStr(x+m_vampire_plus_x+127+TitleOffset_x, y+m_vampire_plus_y+80+22+accel_gap*i+TitleOffset_y, pAccelName, gpC_base->m_chatting_pi, RGB_WHITE);
				WORD key = g_pKeyAccelerator->GetKey(accel);
				int px = 0;
				if(ACCEL_HAS_CONTROL(key))
					px = g_PrintColorStr(x+m_vampire_plus_x+127+100+px+TitleOffset_x, y+m_vampire_plus_y+80+22+accel_gap*i+TitleOffset_y, "Ctrl", gpC_base->m_chatting_pi, RGB_WHITE);
				if(ACCEL_HAS_ALT(key))
				{
					if(px != 0)
					{
						px = g_PrintColorStr(px, y+m_vampire_plus_y+80+22+accel_gap*i+TitleOffset_y, "+", gpC_base->m_chatting_pi, RGB_WHITE);
						px = g_PrintColorStr(px, y+m_vampire_plus_y+80+22+accel_gap*i+TitleOffset_y, "Alt", gpC_base->m_chatting_pi, RGB_WHITE);
					}
					else
						px = g_PrintColorStr(x+m_vampire_plus_x+127+100+TitleOffset_x, y+m_vampire_plus_y+80+22+accel_gap*i+TitleOffset_y, "Alt", gpC_base->m_chatting_pi, RGB_WHITE);
				}
				if(ACCEL_HAS_SHIFT(key))
				{
					if(px != 0)
					{
						px = g_PrintColorStr(px, y+m_vampire_plus_y+80+22+accel_gap*i+TitleOffset_y, "+", gpC_base->m_chatting_pi, RGB_WHITE);
						px = g_PrintColorStr(px, y+m_vampire_plus_y+80+22+accel_gap*i+TitleOffset_y, "Shift", gpC_base->m_chatting_pi, RGB_WHITE);
					}
					else
						px = g_PrintColorStr(x+m_vampire_plus_x+127+100+TitleOffset_x, y+m_vampire_plus_y+80+22+accel_gap*i+TitleOffset_y, "Shift", gpC_base->m_chatting_pi, RGB_WHITE);
				}
				if(px != 0)
				{
					px = g_PrintColorStr(px, y+m_vampire_plus_y+80+22+accel_gap*i+TitleOffset_y, "+", gpC_base->m_chatting_pi, RGB_WHITE);
					px = g_PrintColorStr(px, y+m_vampire_plus_y+80+22+accel_gap*i+TitleOffset_y, scancode_name[ACCEL_GET_KEY(key)], gpC_base->m_chatting_pi, RGB_WHITE);
				}
				else
					px = g_PrintColorStr(x+m_vampire_plus_x+127+100+TitleOffset_x, y+m_vampire_plus_y+80+22+accel_gap*i+TitleOffset_y, scancode_name[ACCEL_GET_KEY(key)], gpC_base->m_chatting_pi, RGB_WHITE);
							
				//				char sz_temp[20];
				//				wsprintf(sz_temp, "%d", m_focus_hotkey);
				//				g_PrintColorStr(x+m_vampire_plus_x+127+100, y+m_vampire_plus_y+80, sz_temp, gpC_base->m_chatting_pi, RGB_WHITE);
				
			}	
			g_FL2_ReleaseDC();
			if(false == m_IsTitle)
				m_pC_scroll_bar->Show(x+m_vampire_plus_x+TitleOffset_x, y+m_vampire_plus_y+TitleOffset_y);
			else
				m_pC_scroll_bar->Show3(x+m_vampire_plus_x+TitleOffset_x, y+m_vampire_plus_y+TitleOffset_y);
		}
		break;

	case TAB_GRAPHIC:
		{
			const char* check_string[CHECK_GRAPHIC_MAX] =
			{
				(*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_MENU_3D_ACCEL].GetString(),
				(*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_MENU_ALPHA_HPBAR].GetString(),
				(*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_MENU_SHED_BLOOD].GetString(),
				(*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_MENU_HIDE_SOFT].GetString(),
				(*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_MENU_GAME_BRIGHT].GetString(),
				(*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_MENU_CHATTING_TALK].GetString(),
				(*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_MENU_PUT_FPS].GetString(),
				(*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_MENU_WINDOW_ALPHA].GetString(),
				(*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_MENU_DENSITY_ALPHA].GetString(),
				(*g_pGameStringTable)[UI_STRING_MESSAGE_DO_NOT_SHOW_PERSNALSHOP_MSG].GetString(),				
				
			};
			
			g_FL2_GetDC();

			// ÇØ»óµµ
			//g_PrintColorStr(x+m_vampire_plus_x+m_check_x+30, y+m_vampire_plus_y+m_check_y, 
			//	(*g_pGameStringTable)[UI_STRING_MESSAGE_800x600].GetString(), gpC_base->m_user_id_pi, strColor);
			
			//g_PrintColorStr(x+m_vampire_plus_x+m_check_x+140, y+m_vampire_plus_y+m_check_y, 
			//	(*g_pGameStringTable)[UI_STRING_MESSAGE_1024x768].GetString(), gpC_base->m_user_id_pi, strColor);

			for(i = 0; i < CHECK_GRAPHIC_MAX; i++)
				g_PrintColorStr(x+m_vampire_plus_x+m_check_x+15, y+m_vampire_plus_y+m_check_y+m_check_gap*(1+i), check_string[i], gpC_base->m_user_id_pi, strColor);
			g_FL2_ReleaseDC();

			if(gpC_base->m_p_DDSurface_back->Lock())
			{
				if(false == m_IsTitle)
				{
					m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+m_rt_value[RECT_GAMMA].x, y+m_vampire_plus_y+m_rt_value[RECT_GAMMA].y+5, VOLUME_BAR);
					if(m_check[CHECK_GAMMA])
						m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+m_rt_value[RECT_GAMMA].x-m_pC_etc_spk->GetWidth(VOLUME_TAG)/2+(m_value_gamma-MIN_GAMMA_VALUE)*m_rt_value[RECT_GAMMA].w/MAX_GAMMA_VALUE, y+m_vampire_plus_y+m_rt_value[RECT_GAMMA].y, VOLUME_TAG);
					
					m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+m_rt_value[RECT_ALPHA].x, y+m_vampire_plus_y+m_rt_value[RECT_ALPHA].y+5, VOLUME_BAR);
					if(m_check[CHECK_ALPHA_DEPTH])
						m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+m_rt_value[RECT_ALPHA].x-m_pC_etc_spk->GetWidth(VOLUME_TAG)/2+(g_pUserOption->ALPHA_DEPTH)*m_rt_value[RECT_ALPHA].w/MAX_ALPHA_DEPTH, y+m_vampire_plus_y+m_rt_value[RECT_ALPHA].y, VOLUME_TAG);
				}
				else
				{
					m_pC_main_spk->BltLocked(x+m_vampire_plus_x+m_rt_value[RECT_GAMMA].x, y+m_vampire_plus_y+m_rt_value[RECT_GAMMA].y+5, TITLE_VOLUME_BAR);
					if(m_check[CHECK_GAMMA])
						m_pC_main_spk->BltLocked(x+m_vampire_plus_x+m_rt_value[RECT_GAMMA].x-m_pC_main_spk->GetWidth(TITLE_VOLUME_TAG)/2+(m_value_gamma-MIN_GAMMA_VALUE)*m_rt_value[RECT_GAMMA].w/MAX_GAMMA_VALUE, y+m_vampire_plus_y+m_rt_value[RECT_GAMMA].y, TITLE_VOLUME_TAG);
					
					m_pC_main_spk->BltLocked(x+m_vampire_plus_x+m_rt_value[RECT_ALPHA].x, y+m_vampire_plus_y+m_rt_value[RECT_ALPHA].y+5, TITLE_VOLUME_BAR);
					if(m_check[CHECK_ALPHA_DEPTH])
						m_pC_main_spk->BltLocked(x+m_vampire_plus_x+m_rt_value[RECT_ALPHA].x-m_pC_main_spk->GetWidth(TITLE_VOLUME_TAG)/2+(g_pUserOption->ALPHA_DEPTH)*m_rt_value[RECT_ALPHA].w/MAX_ALPHA_DEPTH, y+m_vampire_plus_y+m_rt_value[RECT_ALPHA].y, TITLE_VOLUME_TAG);
				}
				m_pC_graphic_button_group->Show();
				gpC_base->m_p_DDSurface_back->Unlock();
			}
		}
		break;

	case TAB_SOUND:
		{
			const char* check_string[CHECK_SOUND_MAX] =
			{
//				"±âÇÕ ¼Ò¸® µè±â",
				(*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_MENU_SOUND_VOLUME].GetString(),
				(*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_MENU_MUSIC_VOLUME].GetString(),
			};

			g_FL2_GetDC();
			for(i = 0; i < CHECK_SOUND_MAX; i++)
				g_PrintColorStr(x+m_vampire_plus_x+m_check_x+15, y+m_vampire_plus_y+m_check_y+m_check_gap*i, check_string[i], gpC_base->m_user_id_pi, strColor);
//			g_PrintColorStr(x+m_vampire_plus_x+m_check_x+80, y+m_vampire_plus_y+m_check_y+m_check_gap*i, "WAV", gpC_base->m_user_id_pi, strColor);
//			g_PrintColorStr(x+m_vampire_plus_x+m_check_x+140, y+m_vampire_plus_y+m_check_y+m_check_gap*i, "MIDI", gpC_base->m_user_id_pi, strColor);
			g_FL2_ReleaseDC();

			if(gpC_base->m_p_DDSurface_back->Lock())
			{
				if(false == m_IsTitle)
				{
					m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+m_rt_value[RECT_SOUND].x, y+m_vampire_plus_y+m_rt_value[RECT_SOUND].y+5, VOLUME_BAR);
					m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+m_rt_value[RECT_MUSIC].x, y+m_vampire_plus_y+m_rt_value[RECT_MUSIC].y+5, VOLUME_BAR);
					if(m_check[CHECK_SOUND])
						m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+m_rt_value[RECT_SOUND].x-m_pC_etc_spk->GetWidth(VOLUME_TAG)/2+m_volume_sound*m_rt_value[RECT_SOUND].w/MAX_SOUND_VOLUME, y+m_vampire_plus_y+m_rt_value[RECT_SOUND].y, VOLUME_TAG);
					if(m_check[CHECK_MUSIC])
						m_pC_etc_spk->BltLocked(x+m_vampire_plus_x+m_rt_value[RECT_MUSIC].x-m_pC_etc_spk->GetWidth(VOLUME_TAG)/2+m_volume_music*m_rt_value[RECT_MUSIC].w/MAX_MUSIC_VOLUME, y+m_vampire_plus_y+m_rt_value[RECT_MUSIC].y, VOLUME_TAG);
				}
				else
				{
					m_pC_main_spk->BltLocked(x+m_vampire_plus_x+m_rt_value[RECT_SOUND].x, y+m_vampire_plus_y+m_rt_value[RECT_SOUND].y+5, TITLE_VOLUME_BAR);
					m_pC_main_spk->BltLocked(x+m_vampire_plus_x+m_rt_value[RECT_MUSIC].x, y+m_vampire_plus_y+m_rt_value[RECT_MUSIC].y+5, TITLE_VOLUME_BAR);
					if(m_check[CHECK_SOUND])
						m_pC_main_spk->BltLocked(x+m_vampire_plus_x+m_rt_value[RECT_SOUND].x-m_pC_main_spk->GetWidth(TITLE_VOLUME_TAG)/2+m_volume_sound*m_rt_value[RECT_SOUND].w/MAX_SOUND_VOLUME, y+m_vampire_plus_y+m_rt_value[RECT_SOUND].y, TITLE_VOLUME_TAG);
					if(m_check[CHECK_MUSIC])
						m_pC_main_spk->BltLocked(x+m_vampire_plus_x+m_rt_value[RECT_MUSIC].x-m_pC_main_spk->GetWidth(TITLE_VOLUME_TAG)/2+m_volume_music*m_rt_value[RECT_MUSIC].w/MAX_MUSIC_VOLUME, y+m_vampire_plus_y+m_rt_value[RECT_MUSIC].y, TITLE_VOLUME_TAG);
				}
				m_pC_sound_button_group->Show();
				gpC_base->m_p_DDSurface_back->Unlock();			
			}			
		}
		break;

	case TAB_GAME:
		{
			const char* check_string[CHECK_GAME_MAX] =
			{
				(*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_MENU_SHOW_BASIC_HELP].GetString(),
				(*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_MENU_NO_LISTEN_BAD_TALK].GetString(),
				(*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_MENU_LOAD_ALL_IMAGE].GetString(),
				(*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_MENU_CHATTING_COLOR_WHITE].GetString(),
				(*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_MENU_RUN_TEEN_VERSION].GetString(),
				(*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_MENU_OPEN_WINDOW_WHEN_WHISPER].GetString(),
				(*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_DO_NOT_WAR_MSG].GetString(),
				(*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_DO_NOT_LAIR_MSG].GetString(),
				(*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_DO_NOT_HOLY_LAND_MSG].GetString(),
#if __CONTENTS(__JAPAN_UI)
				(*g_pGameStringTable)[UI_STRING_MESSAGE_ONE_CLICK_ATTACK_OFF].GetString(),
#endif //__JAPAN_UI
#if __CONTENTS(__LANGUAGE_CHANGE)
				(*g_pGameStringTable)[UI_STRING_MESSAGE_GAMEMONEY_WITH_HANGUL].GetString(),	
#endif	//__LANGUAGE
#if __CONTENTS(__GAMEOPTION_ITEMBAY_MESSAGEBOX)
				(*g_pGameStringTable)[UI_GAME_OPTION_ITEM_BAY_MESSAGE_BOX].GetString(),
#endif

//				(*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_NOT_SEND_MY_INFO].GetString(),
/*				"ÃÊº¸ÀÚ¿ë µµ¿ò¸» º¸±â",
				"³ª»Û¸» µèÁö ¾Ê±â",
//				"Á¾Á· º¯ÇÏ°Ô ÇÏ±â",
//				"ÆÄÆ¼ ÃÊ´ë °ÅºÎ",
//				"ÆÄÆ¼ °¡ÀÔ ½ÅÃ» °ÅºÎ",
				"¸ÊÀÌµ¿ÇÒ ¶§ ¸ó½ºÅÍ ÀÌ¹ÌÁö ºÒ·¯¿À±â",
				"Ã¤ÆÃ ¸ðµÎ Èò»öÀ¸·Î º¸±â",
				"Æ¾¹öÁ¯À¸·Î º¸±â",
				"±Ó¼Ó¸» ¿ÔÀ»¶§ Ã¤ÆÃÃ¢ ¶ç¿ì±â",*/
			};
			
			g_FL2_GetDC();
			for(i = 0; i < CHECK_GAME_MAX; i++)
				g_PrintColorStr(x+m_vampire_plus_x+m_check_x+15, y+m_vampire_plus_y+m_check_y+m_check_gap*i, check_string[i], gpC_base->m_user_id_pi, strColor);
			g_FL2_ReleaseDC();		
		}
		break;
	}
	
	if(gpC_base->m_p_DDSurface_back->Lock())
	{
		m_pC_button_group->Show();
		if(m_i_selected_tab==TAB_GAME)
			m_pC_game_button_group->Show();

//		if(true == m_IsTitle)
//			DrawTitleEffect();
		gpC_base->m_p_DDSurface_back->Unlock();
	}
	

	if(gC_vs_ui.IsAccelMode())
	{
		Rect rect;
		rect.w = 330;
		rect.h = 110;
		//rect.x = RESOLUTION_X/2-rect.w/2;
		//rect.y = RESOLUTION_Y/2-rect.h/2;

		rect.x = g_pUserInformation->iResolution_x/2-rect.w/2;
		rect.y = g_pUserInformation->iResolution_y/2-rect.h/2;
		
		if(m_IsTitle)
		{
			RECT mssageBox;
			
			mssageBox.left = rect.x;
			mssageBox.top = rect.y;
			mssageBox.right = rect.x + rect.w;
			mssageBox.bottom = rect.x + rect.h;
			
			gpC_base->m_p_DDSurface_back->DrawRect(&mssageBox, 0x3BCA);
			gpC_base->m_p_DDSurface_back->BltColorAlpha(&mssageBox, 0x2245, 5);
		}
		else
		{
			gpC_global_resource->DrawDialog(rect, g_pUserOption->DefaultAlpha != FALSE);
		}
		
		const BYTE accel = gC_vs_ui.GetAccelKey();
		const char *pAccelName = g_pKeyAccelerator->GetName(accel);
		int px = rect.x+30;
		int py = rect.y+30;
		
		g_FL2_GetDC();
		//px = g_PrintColorStr(px, py, (*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_MENU_ACCEL_NAME].GetString(), gpC_base->m_chatting_pi, RGB_WHITE);
		g_PrintColorStr(px, py, pAccelName, gpC_base->m_chatting_pi, RGB_WHITE);
		WORD key = g_pKeyAccelerator->GetKey(accel);
		px = rect.x+30+150;
		//px = g_PrintColorStr(px, py, (*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_MENU_ACCEL_KEY].GetString(), gpC_base->m_chatting_pi, RGB_WHITE);
		int old_px = px;
		if(ACCEL_HAS_CONTROL(key))
			px = g_PrintColorStr(px, py, "Ctrl", gpC_base->m_chatting_pi, RGB_WHITE);
		if(ACCEL_HAS_ALT(key))
		{
			if(px != old_px)
			{
				px = g_PrintColorStr(px, py, "+", gpC_base->m_chatting_pi, RGB_WHITE);
				px = g_PrintColorStr(px, py, "Alt", gpC_base->m_chatting_pi, RGB_WHITE);
			}
			else
				px = g_PrintColorStr(px, py, "Alt", gpC_base->m_chatting_pi, RGB_WHITE);
		}
		if(ACCEL_HAS_SHIFT(key))
		{
			if(px != old_px)
			{
				px = g_PrintColorStr(px, py, "+", gpC_base->m_chatting_pi, RGB_WHITE);
				px = g_PrintColorStr(px, py, "Shift", gpC_base->m_chatting_pi, RGB_WHITE);
			}
			else
				px = g_PrintColorStr(px, py, "Shift", gpC_base->m_chatting_pi, RGB_WHITE);
		}
		if(px != old_px)
		{
			px = g_PrintColorStr(px, py, "+", gpC_base->m_chatting_pi, RGB_WHITE);
			px = g_PrintColorStr(px, py, scancode_name[ACCEL_GET_KEY(key)], gpC_base->m_chatting_pi, RGB_WHITE);
		}
		else
			px = g_PrintColorStr(px, py, scancode_name[ACCEL_GET_KEY(key)], gpC_base->m_chatting_pi, RGB_WHITE);
	
		g_PrintColorStr(rect.x+30, rect.y+50, (*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_MENU_MSG1].GetString(), gpC_base->m_chatting_pi, RGB_WHITE);
		g_PrintColorStr(rect.x+30, rect.y+70,(*g_pGameStringTable)[UI_STRING_MESSAGE_OPTION_MENU_MSG2].GetString(), gpC_base->m_chatting_pi, RGB_WHITE);
		g_FL2_ReleaseDC();
	}
	SHOW_WINDOW_ATTR;
}

//-----------------------------------------------------------------------------
// AcquireFirstSequence
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_OPTION::AcquireFirstSequence()
{
}

//-----------------------------------------------------------------------------
// UnacquireMouseFocus
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_OPTION::UnacquireMouseFocus()
{
	m_pC_button_group->UnacquireMouseFocus();
	m_pC_control_button_group->UnacquireMouseFocus();
	m_pC_graphic_button_group->UnacquireMouseFocus();
	m_pC_sound_button_group->UnacquireMouseFocus();
	m_pC_game_button_group->UnacquireMouseFocus();
}

//-----------------------------------------------------------------------------
// WindowEventReceiver
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_OPTION::WindowEventReceiver(id_t event)
{
}

//-----------------------------------------------------------------------------
// IsPixel
//
// 
//-----------------------------------------------------------------------------
bool C_VS_UI_OPTION::IsPixel(int _x, int _y)
{
//	return m_image_spk.IsPixel(SCR2WIN_X(_x), SCR2WIN_Y(_y));
	if(m_pC_main_spk)
	{
		return m_pC_main_spk->IsPixel(_x-x, _y-y);
	}
	return false;
}

void C_VS_UI_OPTION::Background_Music_ONOFF( EXEC_CHECK_ID check_id )
{
	if(m_check[check_id] != CHECK_DISABLE)
	{
		m_check[check_id] = (m_check[check_id] == CHECK_CHECK)?CHECK_NOT:CHECK_CHECK;
		g_pUserOption->PlayMusic = m_check[check_id] == CHECK_CHECK;
		gpC_base->SendMessage( UI_CHANGE_OPTION, check_id, m_check[check_id] == CHECK_CHECK );
		
		if(g_pUserOption->PlayMusic)
		{
			m_check[CHECK_WAV] = g_pUserOption->PlayWaveMusic?CHECK_CHECK:CHECK_NOT;
			m_check[CHECK_MIDI] = g_pUserOption->PlayWaveMusic?CHECK_NOT:CHECK_CHECK;
		}
		else
		{
			m_check[CHECK_WAV] = CHECK_DISABLE;
			m_check[CHECK_MIDI] = CHECK_DISABLE;
		}
	}
}

void C_VS_UI_OPTION::Effect_Music_ONOFF( EXEC_CHECK_ID check_id )
{
	if(m_check[check_id] != CHECK_DISABLE)
	{
		m_check[check_id] = (m_check[check_id] == CHECK_CHECK)?CHECK_NOT:CHECK_CHECK;
		g_pUserOption->PlaySound = m_check[check_id] == CHECK_CHECK;
		
		//			if(g_pUserOption->PlaySound)m_check[CHECK_YELL] = g_pUserOption->PlayYellSound?CHECK_CHECK:CHECK_NOT;
		//			else m_check[CHECK_YELL] = CHECK_DISABLE;
		
		gpC_base->SendMessage( UI_CHANGE_OPTION, CHECK_SOUND, m_check[check_id] == CHECK_CHECK );
	}
}


//-----------------------------------------------------------------------------
// C_VS_UI_GO_BILING_PAGE
//
// 
//-----------------------------------------------------------------------------
C_VS_UI_GO_BILING_PAGE::C_VS_UI_GO_BILING_PAGE(BILING_MSG_LIST msg)
{
	g_RegisterWindow(this);

	AttrTopmost(true);
	AttrKeyboardControl(true);
	m_biling_mode = msg;

	// ³Ý¸¶ºí¿ë
	int w_w = 350;
	int w_h = 200;

	int cancel_offset_x, cancel_offset_y;
	int ok_offset_x, ok_offset_y;

	ok_offset_x = w_w - 150;
	ok_offset_y = w_h-60;
	cancel_offset_x = w_w - 75;
	cancel_offset_y = w_h-60;

	
	//Set(RESOLUTION_X/2-w_w/2, RESOLUTION_Y/2-w_h/2, w_w, w_h);
	Set(g_pUserInformation->iResolution_x/2-w_w/2, g_pUserInformation->iResolution_y/2-w_h/2, w_w, w_h);

	m_pC_button_group = new ButtonGroup(this);
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(x+ok_offset_x, y+ok_offset_y, gpC_global_resource->m_pC_assemble_box_button_spk->GetWidth(C_GLOBAL_RESOURCE::AB_BUTTON_OK), gpC_global_resource->m_pC_assemble_box_button_spk->GetHeight(C_GLOBAL_RESOURCE::AB_BUTTON_OK), BILING_OK, this, C_GLOBAL_RESOURCE::AB_BUTTON_OK));
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(x+cancel_offset_x, y+cancel_offset_y, gpC_global_resource->m_pC_assemble_box_button_spk->GetWidth(C_GLOBAL_RESOURCE::AB_BUTTON_OK), gpC_global_resource->m_pC_assemble_box_button_spk->GetHeight(C_GLOBAL_RESOURCE::AB_BUTTON_OK), BILING_CANCEL, this, C_GLOBAL_RESOURCE::AB_BUTTON_CANCEL));

}

//-----------------------------------------------------------------------------
// ~C_VS_UI_GO_BILING_PAGE
//
// 
//-----------------------------------------------------------------------------
C_VS_UI_GO_BILING_PAGE::~C_VS_UI_GO_BILING_PAGE()
{
	g_UnregisterWindow(this);

	DeleteNew(m_pC_button_group);
}

void	C_VS_UI_GO_BILING_PAGE::ShowButtonDescription(C_VS_UI_EVENT_BUTTON * p_button)
{
	static char * m_help_string[2] = {
		(*g_pGameStringTable)[UI_STRING_MESSAGE_GO_BILING_PAGE].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_CHAR_CANCEL].GetString()
	};

	g_descriptor_manager.Set(DID_INFO, p_button->x, p_button->y, (void *)m_help_string[p_button->GetID()],0,0);
}

//-----------------------------------------------------------------------------
// C_VS_UI_GO_BILING_PAGE::ShowButtonWidget
//
// 
//-----------------------------------------------------------------------------
void	C_VS_UI_GO_BILING_PAGE::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{	
	if (p_button->GetFocusState())	
	{
		if(p_button->GetPressState())
			gpC_global_resource->m_pC_assemble_box_button_spk->Blt(p_button->x, p_button->y, p_button->m_image_index+C_GLOBAL_RESOURCE::AB_BUTTON_PUSHED_OFFSET);
		else
			gpC_global_resource->m_pC_assemble_box_button_spk->Blt(p_button->x, p_button->y, p_button->m_image_index+C_GLOBAL_RESOURCE::AB_BUTTON_HILIGHTED_OFFSET);
	} else
		gpC_global_resource->m_pC_assemble_box_button_spk->Blt(p_button->x, p_button->y, p_button->m_image_index);

}

//-----------------------------------------------------------------------------
// WindowEventReceiver
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_GO_BILING_PAGE::WindowEventReceiver(id_t event)
{
}

//-----------------------------------------------------------------------------
// IsPixel
//
// 
//-----------------------------------------------------------------------------
bool C_VS_UI_GO_BILING_PAGE::IsPixel(int _x, int _y)
{
	return IsInRect(_x, _y);//m_pC_image_spk->IsPixel(SCR2WIN_X(_x), SCR2WIN_Y(_y));
}

//-----------------------------------------------------------------------------
// Start
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_GO_BILING_PAGE::Start()
{
	PI_Processor::Start();
	gpC_window_manager->AppearWindow(this);

	m_pC_button_group->Init();
}

void C_VS_UI_GO_BILING_PAGE::Finish()
{
	PI_Processor::Finish();

	gpC_window_manager->DisappearWindow(this);
}

//-----------------------------------------------------------------------------
// Process
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_GO_BILING_PAGE::Process()
{
	m_pC_button_group->Process();
}

//-----------------------------------------------------------------------------
// Show
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_GO_BILING_PAGE::Show()
{
	gpC_global_resource->DrawDialog(x, y, w, h, GetAttributes()->alpha);
	
	g_FL2_GetDC();
	std::string str;

	switch(m_biling_mode)
	{
	case CANNOT_PLAY_MSG :
		str = (*g_pGameStringTable)[STRING_MESSAGE_SELECT_PC_CANNOT_PLAY].GetString();
		str += "\n";
		str += (*g_pGameStringTable)[UI_STRING_MESSAGE_WILL_YOU_GO_BILING_PAGE].GetString();
		break;
	case CANNOT_PLAY_BY_ATTR_MSG :
		str = (*g_pGameStringTable)[STRING_MESSAGE_SELECT_PC_CANNOT_PLAY_BY_ATTR].GetString();
		str += "\n";
		str += (*g_pGameStringTable)[UI_STRING_MESSAGE_WILL_YOU_GO_BILING_PAGE].GetString();
		break;
	default :
		str = "";
	}
	
	int next=0;
	char sz_string[512];
	
	int print_x=30+x,vx;
	int py = 40+y;
	const int print_gap = 20;
	const int char_width = g_GetStringWidth("a", gpC_base->m_chatting_pi.hfont);
	
	vx = print_x;
	
	while(str.size() > next)
	{
		strcpy(sz_string, str.c_str()+next);
		
		char *sz_string2 = sz_string;
		
		while(*sz_string2 == ' ')		// ¾ÕÀÇ °ø¹éÁ¦°Å
		{
			sz_string2++;
			next++;
		}
		
		int cut_pos = (x+w-30 -vx)/char_width;
		
		if(!g_PossibleStringCut(sz_string2, cut_pos))
			cut_pos--;
		sz_string2[cut_pos] = NULL;
		
		char *return_char = NULL;
		if((return_char = strchr(sz_string2, '\n')) != NULL)	// return Ã³¸®
		{
			cut_pos = return_char - sz_string2+1;
			sz_string2[cut_pos-1] = NULL;
		}
		
		g_PrintColorStr(vx, py, sz_string2, gpC_base->m_chatting_pi, RGB_WHITE);
		next += cut_pos;
		vx = print_x;
		py += print_gap;
	}
	m_pC_button_group->ShowDescription();
	
	g_FL2_ReleaseDC();

	m_pC_button_group->Show();

	SHOW_WINDOW_ATTR;
}

//-----------------------------------------------------------------------------
// Run
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_GO_BILING_PAGE::Run(id_t id)
{
	switch (id)
	{
		case BILING_OK:			
			gpC_base->SendMessage(UI_GO_BILING_PAGE, TRUE);
			Finish();
			break;

		case BILING_CANCEL:
			Finish();
			break;
	}
}

//-----------------------------------------------------------------------------
// MouseControl
//
// 
//-----------------------------------------------------------------------------
bool C_VS_UI_GO_BILING_PAGE::MouseControl(UINT message, int _x, int _y)
{
	Window::MouseControl(message, _x, _y);
	m_pC_button_group->MouseControl(message, _x, _y);

	return true;
}

//-----------------------------------------------------------------------------
// KeyboardControl
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_GO_BILING_PAGE::KeyboardControl(UINT message, UINT key, long extra)
{
	if (message == WM_KEYDOWN)
	{
		switch (key)
		{
			case VK_ESCAPE:
				Run(BILING_CANCEL);
				return;

			case VK_RETURN:
				Run(BILING_OK);
				return;
		}
	}
}

//-----------------------------------------------------------------------------
// C_VS_UI_NETMARBLE_AGREEMENT
//
// 
//-----------------------------------------------------------------------------
C_VS_UI_NETMARBLE_AGREEMENT::C_VS_UI_NETMARBLE_AGREEMENT()
{
	g_RegisterWindow(this);

	AttrTopmost(true);
	AttrKeyboardControl(true);

	// ³Ý¸¶ºí¿ë
	int w_w = 400;
	int w_h = 300;

	int cancel_offset_x, cancel_offset_y;
	int ok_offset_x, ok_offset_y;

	ok_offset_x = w_w - 150;
	ok_offset_y = w_h-60;
	cancel_offset_x = w_w - 75;
	cancel_offset_y = w_h-60;

	m_pC_etc_spk = new C_SPRITE_PACK(SPK_OPTION);
	
	//Set(RESOLUTION_X/2-w_w/2, RESOLUTION_Y/2-w_h/2, w_w, w_h);
	Set(g_pUserInformation->iResolution_x/2-w_w/2, g_pUserInformation->iResolution_y/2-w_h/2, w_w, w_h);

	m_bCheck = false;

	int checkx = x + 135 ; // 326;
	int checky = y + 204 ; //356;

	m_pC_button_group = new ButtonGroup(this);
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(x+ok_offset_x, y+ok_offset_y, gpC_global_resource->m_pC_assemble_box_button_spk->GetWidth(C_GLOBAL_RESOURCE::AB_BUTTON_OK), gpC_global_resource->m_pC_assemble_box_button_spk->GetHeight(C_GLOBAL_RESOURCE::AB_BUTTON_OK), BUTTON_OK, this, C_GLOBAL_RESOURCE::AB_BUTTON_OK));
	m_pC_button_group->Add( new C_VS_UI_EVENT_BUTTON(checkx, checky, m_pC_etc_spk->GetWidth(CHECK_BACK_DISABLE), m_pC_etc_spk->GetHeight(CHECK_BACK_DISABLE), CHECK, this, CHECK_BACK_DISABLE));
}

//-----------------------------------------------------------------------------
// ~C_VS_UI_NETMARBLE_AGREEMENT
//
// 
//-----------------------------------------------------------------------------
C_VS_UI_NETMARBLE_AGREEMENT::~C_VS_UI_NETMARBLE_AGREEMENT()
{
	g_UnregisterWindow(this);

	DeleteNew(m_pC_button_group);
	DeleteNew(m_pC_etc_spk);
}

void	C_VS_UI_NETMARBLE_AGREEMENT::ShowButtonDescription(C_VS_UI_EVENT_BUTTON * p_button)
{
	static char * m_help_string = {
		(*g_pGameStringTable)[UI_STRING_MESSAGE_I_AGREE].GetString()
	};

	if( p_button->GetID() == CHECK )
		g_descriptor_manager.Set(DID_INFO, p_button->x, p_button->y, (void *)m_help_string,0,0);
}

//-----------------------------------------------------------------------------
// C_VS_UI_NETMARBLE_AGREEMENT::ShowButtonWidget
//
// 
//-----------------------------------------------------------------------------
void	C_VS_UI_NETMARBLE_AGREEMENT::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{	
	if( p_button->GetID() == CHECK )
	{
		m_pC_etc_spk->Blt(p_button->x,p_button->y, p_button->m_image_index);
		if( m_bCheck )
			m_pC_etc_spk->Blt(p_button->x+2, p_button->y+2, CHECK_FOCUS);
	}
	else
	{
		if (p_button->GetFocusState())	
		{
			if(p_button->GetPressState())
				gpC_global_resource->m_pC_assemble_box_button_spk->Blt(p_button->x, p_button->y, p_button->m_image_index+C_GLOBAL_RESOURCE::AB_BUTTON_PUSHED_OFFSET);
			else
				gpC_global_resource->m_pC_assemble_box_button_spk->Blt(p_button->x, p_button->y, p_button->m_image_index+C_GLOBAL_RESOURCE::AB_BUTTON_HILIGHTED_OFFSET);
		} else
			gpC_global_resource->m_pC_assemble_box_button_spk->Blt(p_button->x, p_button->y, p_button->m_image_index);
	}
}

//-----------------------------------------------------------------------------
// WindowEventReceiver
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_NETMARBLE_AGREEMENT::WindowEventReceiver(id_t event)
{
}

//-----------------------------------------------------------------------------
// IsPixel
//
// 
//-----------------------------------------------------------------------------
bool C_VS_UI_NETMARBLE_AGREEMENT::IsPixel(int _x, int _y)
{
	return IsInRect(_x, _y);//m_pC_image_spk->IsPixel(SCR2WIN_X(_x), SCR2WIN_Y(_y));
}

//-----------------------------------------------------------------------------
// Start
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_NETMARBLE_AGREEMENT::Start()
{
	PI_Processor::Start();
	gpC_window_manager->AppearWindow(this);

	m_pC_button_group->Init();
}

void C_VS_UI_NETMARBLE_AGREEMENT::Finish()
{
	PI_Processor::Finish();

	gpC_window_manager->DisappearWindow(this);
}

//-----------------------------------------------------------------------------
// Process
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_NETMARBLE_AGREEMENT::Process()
{
	m_pC_button_group->Process();
}

//-----------------------------------------------------------------------------
// Show
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_NETMARBLE_AGREEMENT::Show()
{
	gpC_global_resource->DrawDialog(x, y, w, h, GetAttributes()->alpha);
	
	g_FL2_GetDC();
	std::string str = (*g_pGameStringTable)[UI_STRING_MESSAGE_NETMARBLE_AGREEMENT].GetString();

	int next=0;
	char sz_string[512];
	
	int print_x=30+x,vx;
	int py = 40+y;
	const int print_gap = 20;
	const int char_width = g_GetStringWidth("a", gpC_base->m_chatting_pi.hfont);
	
	vx = print_x;
	
	while(str.size() > next)
	{
		strcpy(sz_string, str.c_str()+next);
		
		char *sz_string2 = sz_string;
		
		while(*sz_string2 == ' ')		// ¾ÕÀÇ °ø¹éÁ¦°Å
		{
			sz_string2++;
			next++;
		}
		
		int cut_pos = (x+w-30 -vx)/char_width;
		
		if(!g_PossibleStringCut(sz_string2, cut_pos))
			cut_pos--;
		sz_string2[cut_pos] = NULL;
		
		char *return_char = NULL;
		if((return_char = strchr(sz_string2, '\n')) != NULL)	// return Ã³¸®
		{
			cut_pos = return_char - sz_string2+1;
			sz_string2[cut_pos-1] = NULL;
		}
		
		g_PrintColorStr(vx, py, sz_string2, gpC_base->m_chatting_pi, RGB_WHITE);
		next += cut_pos;
		vx = print_x;
		py += print_gap;
	}
	
	//int checkx = x + 135 ; // 326;
	//int checky = y + 204 ; //356;

	g_PrintColorStr( x + 135 + 18, y + 205, (*g_pGameStringTable)[UI_STRING_MESSAGE_I_AGREE].GetString(),gpC_base->m_chatting_pi, RGB_WHITE);
	m_pC_button_group->ShowDescription();
	
	g_FL2_ReleaseDC();

	m_pC_button_group->Show();

	SHOW_WINDOW_ATTR;
}

//-----------------------------------------------------------------------------
// Run
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_NETMARBLE_AGREEMENT::Run(id_t id)
{
	switch( id )
	{
	case BUTTON_OK :		
		gpC_base->SendMessage(UI_NETMARBLE_AGREEMENT, m_bCheck );
		Finish();
		break;

	case CHECK :
		m_bCheck = !m_bCheck;
		break;
	}
}

//-----------------------------------------------------------------------------
// MouseControl
//
// 
//-----------------------------------------------------------------------------
bool C_VS_UI_NETMARBLE_AGREEMENT::MouseControl(UINT message, int _x, int _y)
{
	Window::MouseControl(message, _x, _y);
	m_pC_button_group->MouseControl(message, _x, _y);

	return true;
}

//-----------------------------------------------------------------------------
// KeyboardControl
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_NETMARBLE_AGREEMENT::KeyboardControl(UINT message, UINT key, long extra)
{
//	if (message == WM_KEYDOWN)
//	{
//		switch (key)
//		{
//			case VK_ESCAPE:
//				Run(BILING_CANCEL);
//				return;
//
//			case VK_RETURN:
//				Run(BILING_OK);
//				return;
//		}
//	}
}

#endif //__TITLE_UI_RENWEAL
