#include "client_PCH.h"
#include "VS_UI_Base.h"
#include "VS_UI_Util.h"
#include "VS_UI.h"
#include "VS_UI_GameCommon2.h"
#include "VS_UI_Friend_System.h"
#include "MPlayer.h"
#include "MZone.h"
#include "MGameStringTable.h"
#include "MGuildInfoMapper.h"


#if __CONTENTS(__FRIEND_ADDITION)
/*
	Ä³¸¯ÅÍ ÆË¾÷ ¸Þ´º
*/
C_VS_UI_CHARACTER_POPUP_MENU::C_VS_UI_CHARACTER_POPUP_MENU(int _x, int _y, TYPE_OBJECTID id)
: C_VS_UI_MENU(_x,_y)
{
	m_id = id;
}

C_VS_UI_CHARACTER_POPUP_MENU::~C_VS_UI_CHARACTER_POPUP_MENU()
{
	// ÀÌ¹ÌÁö°¡ ÀÖ´Ù¸é Á¤¸® ÇØÁØ´Ù.
	if (m_menu_spkimage != NULL)
	{
		DeleteNew(m_menu_spkimage);
	}
}

void C_VS_UI_CHARACTER_POPUP_MENU::Start()
{
	C_VS_UI_MENU::Start();
}

void C_VS_UI_CHARACTER_POPUP_MENU::Finish()
{
	C_VS_UI_MENU::Finish();
}

void C_VS_UI_CHARACTER_POPUP_MENU::Show()
{
	if (m_menu_spkimage == NULL) return;
	if (gpC_base->m_p_DDSurface_back->Lock())
	{
		// ¸Þ´º ¹ÙÅÁ ÀÌ¹ÌÁö
		m_menu_spkimage->BltLocked(x,y,SI_MAIN);

		// ¸¶¿ì½º ¿À¹ö Ä¿¼­
		if (m_current_command >= 0 && m_current_command < m_command_count)
			m_menu_spkimage->BltLocked(x+m_command_pos_x_gap,y+m_command_pos_y_gap+(m_menu_spkimage->GetHeight(SI_SELECT_BOX)*m_current_command),SI_SELECT_BOX+m_current_command);
		gpC_base->m_p_DDSurface_back->Unlock();
	}
}

bool C_VS_UI_CHARACTER_POPUP_MENU::LButtonDown(int cmd)
{
	if (cmd != CI_ADD_FRIEND)
	{
		if (m_v_main_command[cmd]->pExecFn != NULL)
			m_v_main_command[cmd]->pExecFn((void*)&m_id);
	}
	else
	{
		MCreature* pCreature = g_pZone->GetCreature(m_id);
	
		if (pCreature == NULL)
			return true;
		if (pCreature->CurPernalShop() == 1)
			return true;
		if (pCreature->IsNPC())
			return true;

		if (m_v_main_command[cmd]->pExecFn != NULL)
			m_v_main_command[cmd]->pExecFn((void*)pCreature->GetName());
	}
	gpC_base->SendMessage(UI_DESTROY,0,0,(void*)m_window_name.c_str());
	return true;
}

void C_VS_UI_CHARACTER_POPUP_MENU::SetSpkImage(C_SPRITE_PACK*& image, int command_count)
{ 
	m_menu_spkimage = image;
	m_command_count = command_count;
	w = m_menu_spkimage->GetWidth(SI_MAIN);
	h = m_menu_spkimage->GetHeight(SI_MAIN);

	// ¿©¹é °è»ê
	if (image->GetSize() > 1)
	{
		m_command_pos_x_gap = (m_menu_spkimage->GetWidth(SI_MAIN) - m_menu_spkimage->GetWidth(SI_SELECT_BOX)) / 2;
		m_command_pos_y_gap = (h - (m_menu_spkimage->GetHeight(SI_SELECT_BOX) * m_command_count)) / 2;
		m_select_box_height = m_menu_spkimage->GetHeight(SI_SELECT_BOX);
	}
}

void C_VS_UI_CHARACTER_POPUP_MENU::SetPosition(int _x, int _y, MENU_POSITION pos /*= MP_RIGHTBOTTOM*/)
{
	C_VS_UI_MENU::SetPosition(_x,_y,pos);
	m_menu_box.SetRect(x, y, x + m_menu_spkimage->GetWidth(SI_MAIN), y + m_menu_spkimage->GetHeight(SI_MAIN));
}

void C_VS_UI_CHARACTER_POPUP_MENU::AddCommand(const char* pszCommand, id_t id, void (*pExecFn)(void* void_ptr) /*= NULL*/, int style /* = MENU_COMMAND::CS_NONE */)
{
	C_VS_UI_MENU::AddCommand(pszCommand,id,pExecFn,style);

	m_menu_box.SetRect(x,y,x+m_menu_spkimage->GetWidth(SI_MAIN),y+m_menu_spkimage->GetHeight(SI_MAIN));
	Set(m_menu_box.left, m_menu_box.top, m_menu_box.right - m_menu_box.left, m_menu_box.bottom - m_menu_box.top);
}

void C_VS_UI_CHARACTER_POPUP_MENU::SetSubMenu(id_t id, C_VS_UI_MENU*& pSubMenu)
{
	C_VS_UI_MENU::SetSubMenu(id,pSubMenu);
}

/*
	Ä£±¸ ¸®½ºÆ® ºä UI Å¬·¡½º
*/
C_VS_UI_FRIEND_LISTVIEW::C_VS_UI_FRIEND_LISTVIEW(Window* pParent, int _x, int _y, int _w, int _h, DWORD styl, SELECT_TYPE type)
: C_VS_UI_LISTVIEW(pParent,_x,_y,_w,_h,styl,type)
{
	m_scroll_spkimage = NULL;
}

C_VS_UI_FRIEND_LISTVIEW::~C_VS_UI_FRIEND_LISTVIEW()
{

}

void C_VS_UI_FRIEND_LISTVIEW::Start()
{
	C_VS_UI_LISTVIEW::Start();
}

void C_VS_UI_FRIEND_LISTVIEW::Finish()
{
	C_VS_UI_LISTVIEW::Finish();
}

void C_VS_UI_FRIEND_LISTVIEW::Show()
{
	if (!Running()) return;

	C_VS_UI_LISTVIEW::Show();
}

void C_VS_UI_FRIEND_LISTVIEW::DrawScrollBar()
{
	// To do : ¸®½ºÆ® ºäÀÇ ½ºÅ©·ÑÀ» µå·ÎÀ× ÇÑ´Ù.

	if (gpC_base->m_p_DDSurface_back->Lock())
	{
		if (m_vertical_scroll)
		{// ½ºÅ©·Ñ ÀÌ¹ÌÁö
			m_scroll_spkimage->BltLocked(x+m_scroll_data.background_area.left,y+m_scroll_data.background_area.top,FCSI_SCROLL_BACKGROUND_FRONT);
			if (m_scroll_data.up_button_push)
				m_scroll_spkimage->BltLocked(x+m_scroll_data.up_button_area.left,y+m_scroll_data.up_button_area.top,FCSI_SCROLL_UP_BUTTON_PUSH);
			else
				m_scroll_spkimage->BltLocked(x+m_scroll_data.up_button_area.left,y+m_scroll_data.up_button_area.top,FCSI_SCROLL_UP_BUTTON_NORMAL);
			if (m_scroll_data.dw_button_push)
				m_scroll_spkimage->BltLocked(x+m_scroll_data.dw_button_area.left,y+m_scroll_data.dw_button_area.top,FCSI_SCROLL_DOWN_BUTTON_PUSH);
			else
				m_scroll_spkimage->BltLocked(x+m_scroll_data.dw_button_area.left,y+m_scroll_data.dw_button_area.top,FCSI_SCROLL_DOWN_BUTTON_NORMAL);
			m_scroll_spkimage->BltLocked(x+m_scroll_data.bar_button_area.left,y+m_scroll_data.bar_button_area.top,FCSI_SCROLL_BAR);
		}
		gpC_base->m_p_DDSurface_back->Unlock();	
	}
	return;
}

void C_VS_UI_FRIEND_LISTVIEW::Process()
{
	if (!Running()) return;

	C_VS_UI_LISTVIEW::Process();
}

bool C_VS_UI_FRIEND_LISTVIEW::IsPixel(int _x, int _y)
{ 
	if (!Running()) return false;

	if (m_scroll_data.background_area.PtInRect(CPoint(_x-x,_y-y)))
		return true;

	return IsInRect(_x, _y);
}
	

bool C_VS_UI_FRIEND_LISTVIEW::MouseControl(UINT message, int _x, int _y)
{
	if (!Running()) return false;

	C_VS_UI_LISTVIEW::MouseControl(message,_x,_y);

	return true;
}

void C_VS_UI_FRIEND_LISTVIEW::SetScrollSpkImage(C_SPRITE_PACK*& image)
{
	m_scroll_spkimage = image;
}

void C_VS_UI_FRIEND_LISTVIEW::GenerateVerticalScroll()
{
	// TODO : ¼¼·Î ½ºÅ©·ÑÀÇ ÃÊ±â À§Ä¡ ¹× Å©±â µîÀ» Á¤ÀÇ ÇÑ´Ù.

	int pos_x = w + 8;
	int pos_y = 0;
	int back_w = m_scroll_spkimage->GetWidth(FCSI_SCROLL_BACKGROUND_FRONT);
	int back_h = m_scroll_spkimage->GetHeight(FCSI_SCROLL_BACKGROUND_FRONT);
	{// ½ºÅ©·Ñ ¹è°æ
		m_scroll_data.background_area.SetRect(pos_x,pos_y,pos_x+back_w,pos_y+back_h);
	}

	int cm_button_w = m_scroll_spkimage->GetWidth(FCSI_SCROLL_UP_BUTTON_NORMAL);
	int cm_button_x = pos_x + ((back_w / 2) - (cm_button_w / 2));
	int ud_button_h = m_scroll_spkimage->GetHeight(FCSI_SCROLL_UP_BUTTON_NORMAL);
	int up_button_y = pos_y + 2;
	int dw_button_y = back_h - 2 - ud_button_h;
	{
		// »ó´Ü ¹öÆ°
		m_scroll_data.up_button_area.SetRect(cm_button_x,up_button_y,cm_button_x+cm_button_w,up_button_y+ud_button_h);
		// ÇÏ´Ü ¹öÆ°
		m_scroll_data.dw_button_area.SetRect(cm_button_x,dw_button_y,cm_button_x+cm_button_w,dw_button_y+ud_button_h);
	}

	int bar_button_y = up_button_y + ud_button_h + 1;
	int bar_button_h = m_scroll_spkimage->GetHeight(FCSI_SCROLL_BAR);
	{// ½ºÅ©·Ñ ¹Ù
		m_scroll_data.bar_button_size.cx = cm_button_w;
		m_scroll_data.bar_button_size.cy = bar_button_h;
		m_scroll_data.bar_button_area.SetRect(cm_button_x,bar_button_y,cm_button_x+cm_button_w,bar_button_y+bar_button_h);
	}
	
	m_scroll_data.bar_pos = 0;
	m_scroll_data.back_pos_y = bar_button_y;
	m_scroll_data.back_height = (dw_button_y - 1) - bar_button_y;
	m_scroll_data.old_time = 0;
}

void C_VS_UI_FRIEND_LISTVIEW::GenerateHorizonScorll()
{
	// TODO : °¡·Î ½ºÅ©·ÑÀÇ ÃÊ±â À§Ä¡ ¹× Å©±â µîÀ» Á¤ÀÇ ÇÑ´Ù.
}

void C_VS_UI_FRIEND_LISTVIEW::LdbclkItemProc(LTVITEM* item)
{
	if (GetItemNameBytSelect(0))
	{
		gpC_base->SendMessage(UI_FRIEND_INFO_DATA,0,0,(void*)GetItemNameBytSelect(0));
	}
}

/*
	Ä£±¸ ´ë±â ¸®½ºÆ® ºä UI Å¬·¡½º
*/
C_VS_UI_FRIEND_WAIT_LISTVIEW::C_VS_UI_FRIEND_WAIT_LISTVIEW(Window* pParent, int _x, int _y, int _w, int _h, DWORD styl, SELECT_TYPE type)
: C_VS_UI_LISTVIEW(pParent,_x,_y,_w,_h,styl,type)
{
	m_scroll_spkimage = NULL;
}

C_VS_UI_FRIEND_WAIT_LISTVIEW::~C_VS_UI_FRIEND_WAIT_LISTVIEW()
{

}

void C_VS_UI_FRIEND_WAIT_LISTVIEW::Start()
{
	C_VS_UI_LISTVIEW::Start();
}

void C_VS_UI_FRIEND_WAIT_LISTVIEW::Finish()
{
	C_VS_UI_LISTVIEW::Finish();
}

void C_VS_UI_FRIEND_WAIT_LISTVIEW::Show()
{
	if (!Running()) return;

	C_VS_UI_LISTVIEW::Show();
}

void C_VS_UI_FRIEND_WAIT_LISTVIEW::DrawScrollBar()
{
	// To do : ¸®½ºÆ® ºäÀÇ ½ºÅ©·ÑÀ» µå·ÎÀ× ÇÑ´Ù.

	if (gpC_base->m_p_DDSurface_back->Lock())
	{
		if (m_vertical_scroll)
		{// ½ºÅ©·Ñ ÀÌ¹ÌÁö
			m_scroll_spkimage->BltLocked(x+m_scroll_data.background_area.left,y+m_scroll_data.background_area.top,FCSI_SCROLL_BACKGROUND_FRONT);
			if (m_scroll_data.up_button_push)
				m_scroll_spkimage->BltLocked(x+m_scroll_data.up_button_area.left,y+m_scroll_data.up_button_area.top,FCSI_SCROLL_UP_BUTTON_PUSH);
			else
				m_scroll_spkimage->BltLocked(x+m_scroll_data.up_button_area.left,y+m_scroll_data.up_button_area.top,FCSI_SCROLL_UP_BUTTON_NORMAL);
			if (m_scroll_data.dw_button_push)
				m_scroll_spkimage->BltLocked(x+m_scroll_data.dw_button_area.left,y+m_scroll_data.dw_button_area.top,FCSI_SCROLL_DOWN_BUTTON_PUSH);
			else
				m_scroll_spkimage->BltLocked(x+m_scroll_data.dw_button_area.left,y+m_scroll_data.dw_button_area.top,FCSI_SCROLL_DOWN_BUTTON_NORMAL);
			m_scroll_spkimage->BltLocked(x+m_scroll_data.bar_button_area.left,y+m_scroll_data.bar_button_area.top,FCSI_SCROLL_BAR);
		}
		gpC_base->m_p_DDSurface_back->Unlock();	
	}
	return;
}

void C_VS_UI_FRIEND_WAIT_LISTVIEW::Process()
{
	if (!Running()) return;

	C_VS_UI_LISTVIEW::Process();
}

bool C_VS_UI_FRIEND_WAIT_LISTVIEW::IsPixel(int _x, int _y)
{ 
	if (!Running()) return false;

	if (m_scroll_data.background_area.PtInRect(CPoint(_x-x,_y-y)))
		return true;

	return IsInRect(_x, _y);
}
	

bool C_VS_UI_FRIEND_WAIT_LISTVIEW::MouseControl(UINT message, int _x, int _y)
{
	if (!Running()) return false;

	C_VS_UI_LISTVIEW::MouseControl(message,_x,_y);

	return true;
}

void C_VS_UI_FRIEND_WAIT_LISTVIEW::SetScrollSpkImage(C_SPRITE_PACK*& image)
{
	m_scroll_spkimage = image;
}

void C_VS_UI_FRIEND_WAIT_LISTVIEW::GenerateVerticalScroll()
{
	// TODO : ¼¼·Î ½ºÅ©·ÑÀÇ ÃÊ±â À§Ä¡ ¹× Å©±â µîÀ» Á¤ÀÇ ÇÑ´Ù.

	int pos_x = w + 8;
	int pos_y = 0;
	int back_w = m_scroll_spkimage->GetWidth(FCSI_SCROLL_BACKGROUND_FRONT);
	int back_h = m_scroll_spkimage->GetHeight(FCSI_SCROLL_BACKGROUND_FRONT);
	{// ½ºÅ©·Ñ ¹è°æ
		m_scroll_data.background_area.SetRect(pos_x,pos_y,pos_x+back_w,pos_y+back_h);
	}

	int cm_button_w = m_scroll_spkimage->GetWidth(FCSI_SCROLL_UP_BUTTON_NORMAL);
	int cm_button_x = pos_x + ((back_w / 2) - (cm_button_w / 2));
	int ud_button_h = m_scroll_spkimage->GetHeight(FCSI_SCROLL_UP_BUTTON_NORMAL);
	int up_button_y = pos_y + 2;
	int dw_button_y = back_h - 2 - ud_button_h;
	{
		// »ó´Ü ¹öÆ°
		m_scroll_data.up_button_area.SetRect(cm_button_x,up_button_y,cm_button_x+cm_button_w,up_button_y+ud_button_h);
		// ÇÏ´Ü ¹öÆ°
		m_scroll_data.dw_button_area.SetRect(cm_button_x,dw_button_y,cm_button_x+cm_button_w,dw_button_y+ud_button_h);
	}

	int bar_button_y = up_button_y + ud_button_h + 1;
	int bar_button_h = m_scroll_spkimage->GetHeight(FCSI_SCROLL_BAR);
	{// ½ºÅ©·Ñ ¹Ù
		m_scroll_data.bar_button_size.cx = cm_button_w;
		m_scroll_data.bar_button_size.cy = bar_button_h;
		m_scroll_data.bar_button_area.SetRect(cm_button_x,bar_button_y,cm_button_x+cm_button_w,bar_button_y+bar_button_h);
	}
	
	m_scroll_data.bar_pos = 0;
	m_scroll_data.back_pos_y = bar_button_y;
	m_scroll_data.back_height = (dw_button_y - 1) - bar_button_y;
	m_scroll_data.old_time = 0;
}

void C_VS_UI_FRIEND_WAIT_LISTVIEW::GenerateHorizonScorll()
{
	// TODO : °¡·Î ½ºÅ©·ÑÀÇ ÃÊ±â À§Ä¡ ¹× Å©±â µîÀ» Á¤ÀÇ ÇÑ´Ù.
}

/*
	Ä£±¸ ½Ã½ºÅÛ UI Å¬·¡½º
*/
C_VS_UI_FRIEND_SYSTEM::C_VS_UI_FRIEND_SYSTEM()
{
	g_RegisterWindow(this);
	gpC_window_manager->AppearWindow(this);

	m_p_friend_common = new C_SPRITE_PACK(SPK_FRIEND_COMMON);
	m_p_friend_system = new C_SPRITE_PACK(SPK_FRIEND_SYSTEM);
	m_p_button_group = new ButtonGroup(this);

	w = m_p_friend_system->GetWidth(FSSI_BACKGROUND);
	h = m_p_friend_system->GetHeight(FSSI_BACKGROUND);
	x = (g_pUserInformation->iResolution_x/2)-(w/2);
	y = g_pUserInformation->iResolution_y/4;
	
	int button_w = m_p_friend_system->GetWidth(FSSI_PAPER_NORMAL);
	int button_h = m_p_friend_system->GetHeight(FSSI_PAPER_NORMAL);

	int left_button_x = ((w/2)/2)-(button_w/2);
	int center_button_x = (w/2)-(button_w/2);
	int right_button_x = ((w/2)+((w/2)/2))-(button_w/2);

	int top_button_y = static_cast<int>(static_cast<float>(h) * 0.15f);
	int bottom_button_y = static_cast<int>(static_cast<float>(h) * 0.9f);

	// ¼³¸í ¹öÆ°
	/*p_button_group->Add(new C_VS_UI_EVENT_BUTTON(w-37, 5,
			m_p_friend_common->GetWidth(FCSI_DESCRIPTION_BUTTON_NORMAL), m_p_friend_common->GetHeight(FCSI_DESCRIPTION_BUTTON_NORMAL),
			EIDESCRIPTION, this, FCSI_DESCRIPTION_BUTTON_NORMAL));*/
	// ´Ý±â ¹öÆ°
	m_p_button_group->Add(new C_VS_UI_EVENT_BUTTON(w-20, 5,
			m_p_friend_common->GetWidth(FCSI_CLOSE_BUTTON_NORMAL), m_p_friend_common->GetHeight(FCSI_CLOSE_BUTTON_NORMAL),
			EICLOSE, this, FCSI_CLOSE_BUTTON_NORMAL));
	// 09.07.02 - ÀÏ´Ü »ç¿ëÇÏÁö ¾Ê´Â ¹öÆ°Àº ¸¸µéÁöµµ ¾Êµµ·Ï ÇÑ´Ù.
	/*// ÂÊÁö ¹öÆ°
	m_p_button_group->Add(new C_VS_UI_EVENT_BUTTON(left_button_x, top_button_y,
			m_p_friend_system->GetWidth(FSSI_PAPER_NORMAL), m_p_friend_system->GetHeight(FSSI_PAPER_NORMAL),
			EIPAPER, this, FSSI_PAPER_NORMAL));
	// ¿ìÆí ¹öÆ°
	m_p_button_group->Add(new C_VS_UI_EVENT_BUTTON(center_button_x, top_button_y,
			m_p_friend_system->GetWidth(FSSI_MAIL_NORMAL), m_p_friend_system->GetHeight(FSSI_MAIL_NORMAL),
			EIMAIL, this, FSSI_MAIL_NORMAL));
	// ±âÅ¸±â´É ¹öÆ°
	m_p_button_group->Add(new C_VS_UI_EVENT_BUTTON(right_button_x, top_button_y,
			m_p_friend_system->GetWidth(FSSI_OTHER_FUNC_NORMAL), m_p_friend_system->GetHeight(FSSI_OTHER_FUNC_NORMAL),
			EIOTHERFUNC, this, FSSI_OTHER_FUNC_NORMAL));*/
	// Ä£±¸Ãß°¡ ¹öÆ°
	m_p_button_group->Add(new C_VS_UI_EVENT_BUTTON(left_button_x, bottom_button_y,
			m_p_friend_system->GetWidth(FSSI_FRIEND_ADD_NORMAL), m_p_friend_system->GetHeight(FSSI_FRIEND_ADD_NORMAL),
			EIFRIENDADD, this, FSSI_FRIEND_ADD_NORMAL));
	// Ä£±¸»èÁ¦ ¹öÆ°
	m_p_button_group->Add(new C_VS_UI_EVENT_BUTTON(right_button_x/*center_button_x*/, bottom_button_y,
			m_p_friend_system->GetWidth(FSSI_FRIEND_DEL_NORMAL), m_p_friend_system->GetHeight(FSSI_FRIEND_DEL_NORMAL),
			EIFRIENDDEL, this, FSSI_FRIEND_DEL_NORMAL));
	// ¿É¼Ç ¹öÆ°
	/*m_p_button_group->Add(new C_VS_UI_EVENT_BUTTON(right_button_x, bottom_button_y,
			m_p_friend_system->GetWidth(FSSI_OPTION_NORMAL), m_p_friend_system->GetHeight(FSSI_OPTION_NORMAL),
			EIOPTION, this, FSSI_OPTION_NORMAL));*/

	int list_view_x = 8;
	int list_view_y = static_cast<int>(static_cast<float>(h) * 0.18f);

	m_p_friend_list_view = new C_VS_UI_FRIEND_LISTVIEW(this,list_view_x,list_view_y,305,253,
			C_VS_UI_LISTVIEW::LSFOUTLINE|C_VS_UI_LISTVIEW::LSFFRAMELINE|C_VS_UI_LISTVIEW::LSFITEMSELECTBOX|C_VS_UI_LISTVIEW::LSFSORT);
	m_p_friend_list_view->InitColumnHeader(4,C_VS_UI_LISTVIEW::CHACENTER);
	#ifdef __DESIGNED_CHS
	m_p_friend_list_view->SetColumnHeader("ÐÕÃû",0,90);
	m_p_friend_list_view->SetColumnHeader("ËùÔÚµØÍ¼",1,150);
	m_p_friend_list_view->SetColumnHeader("×´Ì¬",2,65);
	m_p_friend_list_view->SetColumnHeader("ÏßÂ·",3,0);
	#else
	m_p_friend_list_view->SetColumnHeader("Name",0,90);
	m_p_friend_list_view->SetColumnHeader("Zone",1,150);
	m_p_friend_list_view->SetColumnHeader("Status",2,65);
	m_p_friend_list_view->SetColumnHeader("Channels",3,0);
	#endif
	m_p_friend_list_view->SetScrollSpkImage(m_p_friend_common);
}

C_VS_UI_FRIEND_SYSTEM::~C_VS_UI_FRIEND_SYSTEM()
{
	if (m_p_button_group != NULL)
		DeleteNew(m_p_button_group);
	if (m_p_friend_list_view != NULL)
		DeleteNew(m_p_friend_list_view);
	if (m_p_friend_common != NULL)
		DeleteNew(m_p_friend_common);
	if (m_p_friend_system != NULL)
		DeleteNew(m_p_friend_system);

	gpC_window_manager->DisappearWindow(this);
	g_UnregisterWindow(this);
}

void C_VS_UI_FRIEND_SYSTEM::Start()
{
	PI_Processor::Start();
	gpC_window_manager->FirstPriority(this);
	m_p_friend_list_view->Start();
	m_p_button_group->Init();

	int check_box_x = w - static_cast<int>(static_cast<float>(w) * 0.97f);
	int confirm_pos_y = static_cast<int>(static_cast<float>(h) * 0.84f);

	m_check_box_confirm.SetParent(this);
	m_check_box_confirm.SetPos(check_box_x,confirm_pos_y);
	m_check_box_confirm.Start();

	EMPTY_MOVE;
}

void C_VS_UI_FRIEND_SYSTEM::Finish()
{
	PI_Processor::Finish();
	m_p_friend_list_view->Finish();
	m_check_box_confirm.Finish();
}

void C_VS_UI_FRIEND_SYSTEM::Show()
{
	if (!Running()) return;
	if (gpC_base->m_p_DDSurface_back->Lock())
	{
		{// ¹è°æ
			m_p_friend_system->BltLocked(x,y,FSSI_BACKGROUND);
		}

		{// ¹®±¸
			int title_w = m_p_friend_system->GetWidth(FSSI_TITLE);
			int title_y = y + static_cast<int>(static_cast<float>(h) * 0.05f);
			m_p_friend_system->BltLocked((x+(w/2))-(title_w/2),title_y,FSSI_TITLE);
		}

		{// Å×µÎ¸®
			m_p_friend_common->BltLocked(x,y-m_p_friend_common->GetHeight(FCSI_TOP_OUTLINE),FCSI_TOP_OUTLINE);
			m_p_friend_common->BltLocked(x,y+m_p_friend_system->GetHeight(FSSI_BACKGROUND),FCSI_BOTTOM_OUTLINE);
			m_p_friend_common->BltLocked(x-m_p_friend_common->GetWidth(FCSI_LEFT_OUTLINE),y+30,FCSI_LEFT_OUTLINE);
			m_p_friend_common->BltLocked(x+m_p_friend_system->GetWidth(FSSI_BACKGROUND),y+30,FCSI_RIGHT_OUTLINE);
		}

		{// Å×µÎ¸® Àå½Ä
			int decoration_gap_w = 35;
			int decoration_gap_h = 37;
			int decoration_w = m_p_friend_common->GetWidth(FCSI_LEFTTOPOUTLINE_DECORATION);
			int decoration_h = m_p_friend_common->GetHeight(FCSI_LEFTTOPOUTLINE_DECORATION);

			m_p_friend_common->BltLocked(x-decoration_gap_w,y-decoration_gap_h,
									FCSI_LEFTTOPOUTLINE_DECORATION);
			m_p_friend_common->BltLocked(x+w-(decoration_w-decoration_gap_w),y-decoration_gap_h,
									FCSI_RIGHTTOPOUTLINE_DECORATION);
			m_p_friend_common->BltLocked(x-decoration_gap_w,y+h-(decoration_h-decoration_gap_h),
									FCSI_LEFTBOTTOMOUTLINE_DECORATION);
			m_p_friend_common->BltLocked(x+w-(decoration_w-decoration_gap_w),y+h-(decoration_h-decoration_gap_h),
									FCSI_RIGHTBOTTOMOUTLINE_DECORATION);
		}
		gpC_base->m_p_DDSurface_back->Unlock();
	}

	{// Á¤º¸Ã¢ ¿É¼Ç
		int str_pos_x = x + (w - static_cast<int>(static_cast<float>(w) * 0.91f));
		int confirm_pos_y = y + static_cast<int>(static_cast<float>(h) * 0.84f);

		g_FL2_GetDC();
		// Ä£±¸ Ãß°¡ È®ÀÎÃ¢ ÆË¾÷
	#ifdef __DESIGNED_CHS
		g_PrintColorStr(str_pos_x,confirm_pos_y,"¾Ü¾øÌí¼ÓºÃÓÑ",gpC_base->m_dialog_msg_pi,RGB_BLACK);
	#else
		g_PrintColorStr(str_pos_x,confirm_pos_y,"Reject friend joining",gpC_base->m_dialog_msg_pi,RGB_BLACK);
	#endif		
		g_FL2_ReleaseDC();

		m_check_box_confirm.Show();
	}

	m_p_friend_list_view->Show();
	m_p_button_group->Show();
}

void C_VS_UI_FRIEND_SYSTEM::Process()
{
	if (!Running()) return;

	m_check_box_confirm.Process();
	m_p_button_group->Process();
	m_p_friend_list_view->Process();

	if (m_check_box_confirm.GetCheck() != m_old_check_state_confirm)
	{
		m_old_check_state_confirm = m_check_box_confirm.GetCheck();
		//Sleep(50);
		SendOptionInfo();
	}
}

void C_VS_UI_FRIEND_SYSTEM::Run(id_t id)
{
	if (!Running()) return;

	switch (id)
	{
	case EIDESCRIPTION:
		break;
	case EICLOSE:
		Finish();
		break;
	case EIPAPER:
		break;
	case EIMAIL:
		break;
	case EIOTHERFUNC:
		break;
	case EIFRIENDADD:	// Ä£±¸ Ãß°¡
		{
			C_VS_UI_FRINEND_ADD_INPUT_PLAYER* pFriend = (C_VS_UI_FRINEND_ADD_INPUT_PLAYER*)gpC_window_manager->GetWindowbyName("FriendAddInput");
			if (pFriend)
			{
				if (pFriend->Running())
				{
					pFriend->Finish();
					DeleteNew(pFriend);
				}
				else
				{
					DeleteNew(pFriend);
				}
			}
			pFriend = new C_VS_UI_FRINEND_ADD_INPUT_PLAYER;
			pFriend->SetWindowName("FriendAddInput");
			pFriend->Start();
		}
		break;
	case EIFRIENDDEL:	// Ä£±¸ »èÁ¦
		{
			if (m_p_friend_list_view->GetSelectItemSize())
			{
				C_VS_UI_FRINEND_DEL* pFriend = (C_VS_UI_FRINEND_DEL*)gpC_window_manager->GetWindowbyName("FriendDelIsPlayer");
				if (pFriend)
				{
					if (pFriend->Running())
					{
						pFriend->Finish();
						DeleteNew(pFriend);
					}
					else
					{
						DeleteNew(pFriend);
					}
				}
				pFriend = new C_VS_UI_FRINEND_DEL(m_p_friend_list_view->GetItemNameBytSelect(0));
				pFriend->SetWindowName("FriendDelIsPlayer");
				pFriend->Start();
			}
			else
			{
				C_VS_UI_FRINEND_DEL_NOTSELECT* pFriend = (C_VS_UI_FRINEND_DEL_NOTSELECT*)gpC_window_manager->GetWindowbyName("FriendDelNotSelect");
				if (pFriend)
				{
					if (pFriend->Running())
					{
						pFriend->Finish();
						DeleteNew(pFriend);
					}
					else
					{
						DeleteNew(pFriend);
					}
				}
				pFriend = new C_VS_UI_FRINEND_DEL_NOTSELECT;
				pFriend->SetWindowName("FriendDelNotSelect");
				pFriend->Start();
			}
		}
		break;
	case EIOPTION:
		{
			C_VS_UI_FRIEND_SYSTEM_OPTION* pFriend = (C_VS_UI_FRIEND_SYSTEM_OPTION*)gpC_window_manager->GetWindowbyName("FriendOption");
			if (pFriend)
			{
				if (pFriend->Running())
				{
					pFriend->Finish();
					DeleteNew(pFriend);
				}
				else
				{
					DeleteNew(pFriend);
				}
			}
			pFriend = new C_VS_UI_FRIEND_SYSTEM_OPTION;
			pFriend->SetWindowName("FriendOption");
			pFriend->Start();
		}
		break;
	}
}

bool C_VS_UI_FRIEND_SYSTEM::MouseControl(UINT message, int _x, int _y)
{
	if (!Running()) return false;

	int or_x = _x, or_y = _y;
	Window::MouseControl(message,_x,_y);

	_x -= x; _y -= y;
	bool inButton = m_p_button_group->MouseControl(message, _x, _y);
	bool check_confirm = m_check_box_confirm.MouseControl(message,_x,_y);
	bool inList = m_p_friend_list_view->IsPixel(_x+x,_y+y);

	if (message == M_LEFTBUTTON_DOWN && inButton && !inList && check_confirm)
	{
		MoveReady();
		SetOrigin(_x,_y);
	}
	if (inButton)
		m_p_friend_list_view->MouseControl(message,or_x,or_y);

	return true;
}

void C_VS_UI_FRIEND_SYSTEM::KeyboardControl(UINT message, UINT key, long extra)
{
	if (!Running()) return;

	if (message == WM_KEYDOWN)
	{
		switch (key)
		{
		case VK_ESCAPE:
			//Finish();
			break;		
		}
	}	
}

bool C_VS_UI_FRIEND_SYSTEM::IsPixel(int _x,int _y)
{
	if (!Running()) return false;

	return IsInRect(_x, _y);
}

void C_VS_UI_FRIEND_SYSTEM::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{
	// ¼³¸í ¹öÆ° ¹× ´Ý±â ¹öÆ°
	if (p_button->GetID() == EIDESCRIPTION || p_button->GetID() == EICLOSE)
	{
		if (p_button->GetFocusState() && p_button->GetPressState())
			m_p_friend_common->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+1);
		else
			m_p_friend_common->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index);
	}
	// ±â´ÉÀÌ È°¼ºÈ­ µÇÁö ¾ÊÀº ¹öÆ°
	else if (p_button->GetID() == EIPAPER || p_button->GetID() == EIMAIL || p_button->GetID() == EIOTHERFUNC || p_button->GetID() == EIOPTION)
	{
		// ÇöÀç ÀÌ ½ÃÁ¡¿¡¼± ±×¸®Áö ¾Êµµ·Ï ÇÑ´Ù.(09.07.02)
		return;
		m_p_friend_system->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+2);
	}
	// ±â´ÉÀÌ È°¼ºÈ­ µÈ ¹öÆ°
	else
	{
		if (p_button->GetFocusState())
		{
			if (p_button->GetPressState())
				m_p_friend_system->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+2);
			else
				m_p_friend_system->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+1);
		}
		else
			m_p_friend_system->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index);
	}
}

void C_VS_UI_FRIEND_SYSTEM::ShowButtonDescription(C_VS_UI_EVENT_BUTTON *p_button)
{

}

void C_VS_UI_FRIEND_SYSTEM::SendOptionInfo()
{
	m_option_info.SetOptionToDenyAddRequest(m_check_box_confirm.GetCheck()^1);
	gpC_base->SendMessage(UI_FRIEND_SYSTEM_OPTION,0,0,(void*)&m_option_info);
}

/*
	Ä£±¸ Á¤º¸Ã¢ UI Å¬·¡½º
*/
C_VS_UI_FRIEND_INFO::C_VS_UI_FRIEND_INFO()
{
	g_RegisterWindow(this);

	m_p_friend_common = new C_SPRITE_PACK(SPK_FRIEND_COMMON);
	m_p_friend_info = new C_SPRITE_PACK(SPK_FRIEND_INFO);
	m_p_button_group = new ButtonGroup(this);
	
	w = m_p_friend_info->GetWidth(FISI_BACKGROUND);
	h = m_p_friend_info->GetHeight(FISI_BACKGROUND);
	x = (g_pUserInformation->iResolution_x/2)-(w/2);
	y = g_pUserInformation->iResolution_y/3;

	m_old_check_state_paper = false;
	m_old_check_state_my_info = false;

	int ok_button_x = w - static_cast<int>(static_cast<float>(w) * 0.32f);
	int button_y = static_cast<int>(static_cast<float>(h) * 0.88f);

	// ¼³¸í ¹öÆ°
	/*p_button_group->Add(new C_VS_UI_EVENT_BUTTON(w-37, 5,
			m_p_friend_common->GetWidth(FCSI_DESCRIPTION_BUTTON_NORMAL), m_p_friend_common->GetHeight(FCSI_DESCRIPTION_BUTTON_NORMAL),
			EIDESCRIPTION, this, FCSI_DESCRIPTION_BUTTON_NORMAL));*/
	// ´Ý±â ¹öÆ°
	m_p_button_group->Add(new C_VS_UI_EVENT_BUTTON(w-20, 5,
			m_p_friend_common->GetWidth(FCSI_CLOSE_BUTTON_NORMAL), m_p_friend_common->GetHeight(FCSI_CLOSE_BUTTON_NORMAL),
			EICLOSE, this, FCSI_CLOSE_BUTTON_NORMAL));
	// È®ÀÎ ¹öÆ°
	m_p_button_group->Add(new C_VS_UI_EVENT_BUTTON(ok_button_x, button_y,
			m_p_friend_info->GetWidth(FISI_OK_NORMAL), m_p_friend_info->GetHeight(FISI_OK_NORMAL),
			EIOK, this, FISI_OK_NORMAL));

	int editbox_x = w - static_cast<int>(static_cast<float>(w) * 0.96f);
	int editbox_y = static_cast<int>(static_cast<float>(h) * 0.66f);//0.575f); // Á¤º¸Ã¢ ¿É¼ÇÀÌ µé¾î °¬À»¶§ ÁÂÇ¥ Á¤º¸
	int editbox_w = static_cast<int>(static_cast<float>(w) * 0.92f);
	int editbox_h = static_cast<int>(static_cast<float>(h) * 0.18f);

	m_friend_edit_box.SetRect(editbox_x,editbox_y,editbox_x+editbox_w,editbox_y+editbox_h);

	// Ä£±¸ ÀÌ¸§ ÀÔ·ÂÃ¢
	m_friend_info_edit_box.SetPosition(editbox_x,editbox_y);
	m_friend_info_edit_box.SetPrintInfo(gpC_base->m_chatting_pi);
	m_friend_info_edit_box.SetByteLimit(100);
	m_friend_info_edit_box.SetInputStringColor(RGB_BRIGHT_GRAY);
	m_friend_info_edit_box.SetCursorColor(RGB_BLACK);
	m_friend_info_edit_box.SetDigitOnlyMode(false);
	m_friend_info_edit_box.SetEditorMode(17,3);
	m_friend_info_edit_box.SetAbsWidth(editbox_w-10);
#ifdef __DESIGNED_CHS
	m_friend_info_edit_box.AddString("µ¥»÷ºóÊäÈëºÃÓÑ±¸×¢.");
#else
	m_friend_info_edit_box.AddString("Please click to write a note.");
#endif	

	Attach(&m_friend_info_edit_box);

	m_print_info.hfont = CreateFont(12,0,0,0,FW_NORMAL,FALSE,FALSE,
									0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS ,DEFAULT_QUALITY,DEFAULT_PITCH|FF_ROMAN,
									"Help");
	m_print_info.text_color = gpC_base->m_dialog_msg_pi.text_color;
	m_print_info.text_align = gpC_base->m_dialog_msg_pi.text_align;
	m_print_info.bk_mode = gpC_base->m_dialog_msg_pi.bk_mode;
	m_print_info.back_color = gpC_base->m_dialog_msg_pi.back_color;
}

C_VS_UI_FRIEND_INFO::~C_VS_UI_FRIEND_INFO()
{
	

	if (m_p_button_group != NULL)
		DeleteNew(m_p_button_group);
	if (m_p_friend_common != NULL)
		DeleteNew(m_p_friend_common);
	if (m_p_friend_info != NULL)
		DeleteNew(m_p_friend_info);

	
	g_UnregisterWindow(this);
}

void C_VS_UI_FRIEND_INFO::Start()
{
	PI_Processor::Start();
	gpC_window_manager->AppearWindow(this);
	m_p_button_group->Init();

	int check_box_x = w - static_cast<int>(static_cast<float>(w) * 0.97f);
	int paper_pos_y = static_cast<int>(static_cast<float>(h) * 0.78f);
	int my_info_pos_y = static_cast<int>(static_cast<float>(h) * 0.835f);

	/*m_check_box_paper.SetParent(this);
	m_check_box_paper.SetPos(check_box_x,paper_pos_y);
	m_check_box_my_info.SetParent(this);
	m_check_box_my_info.SetPos(check_box_x,my_info_pos_y);
	m_check_box_paper.Start();
	m_check_box_my_info.Start();*/
	
	EMPTY_MOVE;
}

void C_VS_UI_FRIEND_INFO::Finish()
{
	PI_Processor::Finish();
	//by viva
	m_check_box_paper.Finish();
	m_check_box_my_info.Finish();

	gpC_window_manager->DisappearWindow(this);
}

void C_VS_UI_FRIEND_INFO::Show()
{
	if (!Running()) return;

	std::string str = "";
			
#ifdef __DESIGNED_CHS
	str = "»¹Ã»ÓÐ¼ÓÈë.";
#else
	str = "Haven't joined.";
#endif		

	if (gpC_base->m_p_DDSurface_back->Lock())
	{
		{// ¹è°æ
			m_p_friend_info->BltLocked(x,y,FISI_BACKGROUND);
		}

		{// ¹®±¸
			int title_w = m_p_friend_info->GetWidth(FISI_TITLE);
			int title_y = y + static_cast<int>(static_cast<float>(h) * 0.025f);
			m_p_friend_info->BltLocked((x+(w/2))-(title_w/2),title_y,FISI_TITLE);
		}

		{// Å×µÎ¸®
			m_p_friend_common->BltLocked(x,y-m_p_friend_common->GetHeight(FCSI_TOP_OUTLINE),FCSI_TOP_OUTLINE);
			m_p_friend_common->BltLocked(x,y+m_p_friend_info->GetHeight(FISI_BACKGROUND),FCSI_BOTTOM_OUTLINE);
			m_p_friend_common->BltLocked(x-m_p_friend_common->GetWidth(FCSI_LEFT_OUTLINE),y,FCSI_LEFT_OUTLINE);
			m_p_friend_common->BltLocked(x+m_p_friend_info->GetWidth(FISI_BACKGROUND),y,FCSI_RIGHT_OUTLINE);
		}

		{// Å×µÎ¸® Àå½Ä
			int decoration_gap_w = 35;
			int decoration_gap_h = 37;
			int decoration_w = m_p_friend_common->GetWidth(FCSI_LEFTTOPOUTLINE_DECORATION);
			int decoration_h = m_p_friend_common->GetHeight(FCSI_LEFTTOPOUTLINE_DECORATION);

			m_p_friend_common->BltLocked(x-decoration_gap_w,y-decoration_gap_h,
									FCSI_LEFTTOPOUTLINE_DECORATION);
			m_p_friend_common->BltLocked(x+w-(decoration_w-decoration_gap_w),y-decoration_gap_h,
									FCSI_RIGHTTOPOUTLINE_DECORATION);
			m_p_friend_common->BltLocked(x-decoration_gap_w,y+h-(decoration_h-decoration_gap_h),
									FCSI_LEFTBOTTOMOUTLINE_DECORATION);
			m_p_friend_common->BltLocked(x+w-(decoration_w-decoration_gap_w),y+h-(decoration_h-decoration_gap_h),
									FCSI_RIGHTBOTTOMOUTLINE_DECORATION);
		}

		gpC_base->m_p_DDSurface_back->Unlock();
	}

	// 3Àº µÎ²²°ª
	int info_line_y = y + static_cast<int>(static_cast<float>(h) * 0.63f);//0.555f); // Á¤º¸Ã¢ ¿É¼ÇÀÌ µé¾î °¬À»¶§ ÁÂÇ¥ Á¤º¸
	int edit_line_y = y + static_cast<int>(static_cast<float>(h) * 0.84f);
	for (int i = 0; i < 3; ++i)
	{// ±¸ºÐ¼±
		
		gpC_base->m_p_DDSurface_back->HLine(x,info_line_y+i,w,BLACK);
		//gpC_base->m_p_DDSurface_back->HLine(x,edit_line_y+i,w,BLACK);
	}

	{// Ä£±¸ Á¤º¸
		g_FL2_GetDC();

		int str_pos_x = x + (w - static_cast<int>(static_cast<float>(w) * 0.95f));
		int str_pos_y = y + static_cast<int>(static_cast<float>(h) * 0.135f);
#ifdef __DESIGNED_CHS
		// ÀÌ¸§
		g_PrintColorStr(str_pos_x,str_pos_y,"ÐÕÃû",m_print_info,RGB_BLACK);
		str_pos_y += 18;
		// °è±Þ
		g_PrintColorStr(str_pos_x,str_pos_y,"½×¼¶",m_print_info,RGB_BLACK);
		str_pos_y += 18;
		// ·¹º§
		g_PrintColorStr(str_pos_x,str_pos_y,"µÈ¼¶",m_print_info,RGB_BLACK);
		str_pos_y += 18; 
		// Ã¤³Î
		g_PrintColorStr(str_pos_x,str_pos_y,"ÏßÂ·",m_print_info,RGB_BLACK);
		str_pos_y += 18;
		// À§Ä¡
		g_PrintColorStr(str_pos_x,str_pos_y,"Î»ÖÃ",m_print_info,RGB_BLACK);
		str_pos_y += 18;

		// ÆÀ,Å¬·£,±æµå
		if (g_pPlayer && g_pPlayer->IsSlayer())
			g_PrintColorStr(str_pos_x,str_pos_y,"¹¤»á",m_print_info,RGB_BLACK);
		else if (g_pPlayer && g_pPlayer->IsVampire())
			g_PrintColorStr(str_pos_x,str_pos_y,"ÑªÃË",m_print_info,RGB_BLACK);
		else if (g_pPlayer && g_pPlayer->IsOusters())
			g_PrintColorStr(str_pos_x,str_pos_y,"¹¤»á",m_print_info,RGB_BLACK);
		str_pos_y += 18;
		// ¼ºÇâ
		g_PrintColorStr(str_pos_x,str_pos_y,"ÇãÏò",m_print_info,RGB_BLACK);
		str_pos_y += 18;
		// ±â¿©µµ
		g_PrintColorStr(str_pos_x,str_pos_y,"¹±Ï×Öµ",m_print_info,RGB_BLACK);
		
#else
		// ÀÌ¸§
		g_PrintColorStr(str_pos_x,str_pos_y,"Name",m_print_info,RGB_BLACK);
		str_pos_y += 18;
		// °è±Þ
		g_PrintColorStr(str_pos_x,str_pos_y,"Rank",m_print_info,RGB_BLACK);
		str_pos_y += 18;
		// ·¹º§
		g_PrintColorStr(str_pos_x,str_pos_y,"Level",m_print_info,RGB_BLACK);
		str_pos_y += 18; 
		// Ã¤³Î
		g_PrintColorStr(str_pos_x,str_pos_y,"Channels",m_print_info,RGB_BLACK);
		str_pos_y += 18;
		// À§Ä¡
		g_PrintColorStr(str_pos_x,str_pos_y,"Location",m_print_info,RGB_BLACK);
		str_pos_y += 18;

		// ÆÀ,Å¬·£,±æµå
		if (g_pPlayer && g_pPlayer->IsSlayer())
			g_PrintColorStr(str_pos_x,str_pos_y,"Team",m_print_info,RGB_BLACK);
		else if (g_pPlayer && g_pPlayer->IsVampire())
			g_PrintColorStr(str_pos_x,str_pos_y,"Clan",m_print_info,RGB_BLACK);
		else if (g_pPlayer && g_pPlayer->IsOusters())
			g_PrintColorStr(str_pos_x,str_pos_y,"Guilds",m_print_info,RGB_BLACK);
		str_pos_y += 18;
		// ¼ºÇâ
		g_PrintColorStr(str_pos_x,str_pos_y,"Fame",m_print_info,RGB_BLACK);
		str_pos_y += 18;
		// ±â¿©µµ
		g_PrintColorStr(str_pos_x,str_pos_y,"Contribution",m_print_info,RGB_BLACK);

#endif




		g_FL2_ReleaseDC();		

		int info_area_x = x + (w - static_cast<int>(static_cast<float>(w) * 0.75f));
		int info_area_y = y + static_cast<int>(static_cast<float>(h) * 0.13f);
		int info_area_w = static_cast<int>(static_cast<float>(w) * 0.70f);
		int info_area_h = 15;
		int info_view_box_count = 8;

		CRect box(info_area_x,info_area_y,info_area_x+info_area_w,info_area_y+info_area_h);
		for (int i = 0; i < info_view_box_count; ++i)
		{
			if (gpC_base->m_p_DDSurface_back->Lock())
			{// Á¤º¸ Ç¥½Ã ¿µ¿ª
				gpC_base->m_p_DDSurface_back->BltColorAlpha(box,BLACK,25);
				gpC_base->m_p_DDSurface_back->Unlock();

				gpC_base->m_p_DDSurface_back->DrawRect(box,DARKGRAY);
			}
			box.top += 18;
			box.bottom = box.top + 15;
		}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// À¯ÀúÀÇ ¼¼ºÎ Á¤º¸ÀÌ´Ù.

		g_FL2_GetDC();

		const static char* align_temp[5] = 
		{
			(*g_pGameStringTable)[UI_STRING_MESSAGE_ALIGN_VERY_BAD].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_ALIGN_BAD].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_ALIGN_NORMAL].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_ALIGN_GOOD].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_ALIGN_VERY_GOOD].GetString(),
		};

		switch(g_eRaceInterface)
		{
		case RACE_SLAYER:
			{
				const static char* grade[20] = 
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

				const static char *SlayerJob[5] = 
				{
					(*g_pGameStringTable)[UI_STRING_MESSAGE_ENG_DOMAIN_BLADE2].GetString(),
					(*g_pGameStringTable)[UI_STRING_MESSAGE_ENG_DOMAIN_SWORD2].GetString(),
					(*g_pGameStringTable)[UI_STRING_MESSAGE_ENG_DOMAIN_GUN2].GetString(),
					(*g_pGameStringTable)[UI_STRING_MESSAGE_ENG_DOMAIN_HEAL2].GetString(),
					(*g_pGameStringTable)[UI_STRING_MESSAGE_ENG_DOMAIN_ENCHANT2].GetString(),
				};

				int info_data_y = info_area_y;
				std::string info_str;
				// À¯Àú ÀÌ¸§
				g_PrintColorStr(info_area_x+3,info_data_y+2,m_user_name.c_str(),m_print_info,RGB_BRIGHT_GRAY);
				info_data_y += 18;

				// À¯Àú °è±Þ
				if (m_user_grade > 0 && m_user_grade <= 100/*GRADE_MARK_MAX*/)
				{
					info_str = grade[(m_user_grade-1)/5];
					g_PrintColorStr(info_area_x+3,info_data_y+2,info_str.c_str(),m_print_info,RGB_BRIGHT_GRAY);
				}
				info_data_y += 18;

				// À¯Àú ·¹º§
				char szLevel[16] = {0};
				sprintf(szLevel,"%d",m_user_level);
				if(m_user_domain >= 0 && m_user_domain < 5)
				{
					sprintf(szLevel,"%s %s %d",SlayerJob[m_user_domain],(*g_pGameStringTable)[UI_STRING_MESSAGE_DESC_CLASS2].GetString(),m_user_level);
					g_PrintColorStr(info_area_x+3,info_data_y+2,szLevel, gpC_base->m_chatting_pi, RGB_BRIGHT_GRAY);
				}
				info_data_y += 18;

				// À¯Àú°¡ À§Ä¡ÇÑ ¼­¹ö
				g_PrintColorStr(info_area_x+3,info_data_y+2,m_user_server.c_str(),m_print_info,RGB_BRIGHT_GRAY);
				info_data_y += 18;

				// À¯Àú À§Ä¡
				g_PrintColorStr(info_area_x+3,info_data_y+2,m_user_location.c_str(),m_print_info,RGB_BRIGHT_GRAY);
				info_data_y += 18;
				
				// À¯Àú ±æµå
				if (!m_user_society.empty())
					g_PrintColorStr(info_area_x+3,info_data_y+2,m_user_society.c_str(),m_print_info,RGB_BRIGHT_GRAY);
				else
					g_PrintColorStr(info_area_x+3,info_data_y+2, str.c_str()/*(*g_pGameStringTable)[UI_STRING_MESSAGE_NOT_JOIN_ANY_CLAN].GetString()*/, gpC_base->m_chatting_pi, RGB_WHITE);
				info_data_y += 18;

				// À¯Àú ¼ºÇâ
				if(m_user_alignment >= 0 && m_user_alignment < 5)
					g_PrintColorStr(info_area_x+3,info_data_y+2,align_temp[m_user_alignment], gpC_base->m_chatting_pi, RGB_BRIGHT_GRAY);	
				info_data_y += 18;

				// À¯Àú ±â¿©µµ
				char szContribute[128] = {0};
				int contributeGrade = countContributeGrade(m_user_contribute);	
				if (contributeGrade >= 0 || contributeGrade < 8)
				{
					wsprintf(szContribute,"%d/%d%s %s",m_user_contribute,contributeGrade,(*g_pGameStringTable)[UI_STRING_CONTRIBUTE_GRADE].GetString(),(*g_pGameStringTable)[UI_STRING_MESSAGE_SLAYER_CONTRIBUTENAME_7+(7-contributeGrade)].GetString());
					g_PrintColorStr(info_area_x+3,info_data_y+2,szContribute,m_print_info,RGB_BRIGHT_GRAY);
				}
				info_data_y += 18;
			}
			break;
		case RACE_VAMPIRE:
			{
				const static char* grade[20] = 
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

				int info_data_y = info_area_y;
				std::string info_str;
				// À¯Àú ÀÌ¸§
				g_PrintColorStr(info_area_x+3,info_data_y+2,m_user_name.c_str(),m_print_info,RGB_BRIGHT_GRAY);
				info_data_y += 18;

				// À¯Àú °è±Þ
				if (m_user_grade > 0 && m_user_grade <= 50/*GRADE_MARK_MAX*/)
				{
					info_str = grade[(m_user_grade-1)/5];
					g_PrintColorStr(info_area_x+3,info_data_y+2,info_str.c_str(),m_print_info,RGB_BRIGHT_GRAY);
				}
				info_data_y += 18;

				// À¯Àú ·¹º§
				char szLevel[16] = {0};
				sprintf(szLevel,"%d",m_user_level);
				if (m_user_adv_level == 0)
					g_PrintColorStr(info_area_x+3,info_data_y+2,szLevel,m_print_info,RGB_BRIGHT_GRAY);
				else
				{
					int LevelGrade = (m_user_adv_level-1)/10;
					int LevelUnits = (m_user_adv_level-1)%10;

					static char sz_buf [32];
					sprintf(szLevel,(*g_pGameStringTable)[UI_STRING_MESSAGE_ADVANTE_0+LevelGrade].GetString(),LevelUnits+1);

					g_PrintColorStr(info_area_x+3,info_data_y+2,szLevel,m_print_info,RGB_BRIGHT_GRAY);
				}
				info_data_y += 18;

				// À¯Àú°¡ À§Ä¡ÇÑ ¼­¹ö
				g_PrintColorStr(info_area_x+3,info_data_y+2,m_user_server.c_str(),m_print_info,RGB_BRIGHT_GRAY);
				info_data_y += 18;

				// À¯Àú À§Ä¡
				g_PrintColorStr(info_area_x+3,info_data_y+2,m_user_location.c_str(),m_print_info,RGB_BRIGHT_GRAY);
				info_data_y += 18;
				
				// À¯Àú ±æµå
				if (!m_user_society.empty())
					g_PrintColorStr(info_area_x+3,info_data_y+2,m_user_society.c_str(),m_print_info,RGB_BRIGHT_GRAY);
				else
					g_PrintColorStr(info_area_x+3,info_data_y+2, str.c_str(), gpC_base->m_chatting_pi, RGB_BRIGHT_GRAY);
				info_data_y += 18;

				// À¯Àú ¼ºÇâ
				if(m_user_alignment >= 0 && m_user_alignment < 5)
					g_PrintColorStr(info_area_x+3,info_data_y+2,align_temp[m_user_alignment], gpC_base->m_chatting_pi, RGB_BRIGHT_GRAY);	
				info_data_y += 18;

				// À¯Àú ±â¿©µµ
				char szContribute[128] = {0};
				int contributeGrade = countContributeGrade(m_user_contribute);	
				if (contributeGrade >= 0 || contributeGrade < 8)
				{
					wsprintf(szContribute,"%d/%d%s %s",m_user_contribute,contributeGrade,(*g_pGameStringTable)[UI_STRING_CONTRIBUTE_GRADE].GetString(),(*g_pGameStringTable)[UI_STRING_MESSAGE_VAMPIRE_CONTRIBUTENAME_7+(7-contributeGrade)].GetString());
					g_PrintColorStr(info_area_x+3,info_data_y+2,szContribute,m_print_info,RGB_BRIGHT_GRAY);
				}
				info_data_y += 18;
			}
			break;
		case RACE_OUSTERS:
			{
				const static char* grade[20] = 
				{
					(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_MALCHUT].GetString(),
					(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_YESOD].GetString(),
					(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_HOD].GetString(),
					(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_NETRETH].GetString(),
					(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_TIPHRETH].GetString(),
					(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_GEBURAH].GetString(),
					(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_CHESED].GetString(),
					(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_BINAH].GetString(),
					(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_CHOKMA].GetString(),
					(*g_pGameStringTable)[UI_STRING_MESSAGE_GRADE_KEATHER].GetString(),
					"Ã·ÌØÀ­",
					"¼Ó°ÙÁÐ",
					"À­ì³¶û",
					"¹þÃÀ¶û",
					"Ã×åÈÀÕ",
					"¿¨Âó¶û",
					"Èø»ù¶û",
					"¸¥»ù¶û",
					"À­Æõ¶û",
					"Ã·ËþÌØÂ¡",

				};
				
				int info_data_y = info_area_y;
				std::string info_str;
				// À¯Àú ÀÌ¸§
				g_PrintColorStr(info_area_x+3,info_data_y+2,m_user_name.c_str(),m_print_info,RGB_BRIGHT_GRAY);
				info_data_y += 18;

				// À¯Àú °è±Þ
				if (m_user_grade > 0 && m_user_grade <= 50/*GRADE_MARK_MAX*/)
				{
					info_str = grade[(m_user_grade-1)/5];
					g_PrintColorStr(info_area_x+3,info_data_y+2,info_str.c_str(),m_print_info,RGB_BRIGHT_GRAY);
				}
				info_data_y += 18;

				// À¯Àú ·¹º§
				char szLevel[16] = {0};
				sprintf(szLevel,"%d",m_user_level);
				if (m_user_adv_level == 0)
					g_PrintColorStr(info_area_x+3,info_data_y+2,szLevel,m_print_info,RGB_BRIGHT_GRAY);
				else
				{
					int LevelGrade = (m_user_adv_level-1)/10;
					int LevelUnits = (m_user_adv_level-1)%10;

					static char sz_buf [32];
					sprintf(szLevel,(*g_pGameStringTable)[UI_STRING_MESSAGE_ADVANTE_0+LevelGrade].GetString(),LevelUnits+1);

					g_PrintColorStr(info_area_x+3,info_data_y+2,szLevel,m_print_info,RGB_BRIGHT_GRAY);
				}
				info_data_y += 18;

				// À¯Àú°¡ À§Ä¡ÇÑ ¼­¹ö
				g_PrintColorStr(info_area_x+3,info_data_y+2,m_user_server.c_str(),m_print_info,RGB_BRIGHT_GRAY);
				info_data_y += 18;

				// À¯Àú À§Ä¡
				g_PrintColorStr(info_area_x+3,info_data_y+2,m_user_location.c_str(),m_print_info,RGB_BRIGHT_GRAY);
				info_data_y += 18;
				
				// À¯Àú ±æµå
				if (!m_user_society.empty())
					g_PrintColorStr(info_area_x+3,info_data_y+2,m_user_society.c_str(),m_print_info,RGB_BRIGHT_GRAY);
				else
					g_PrintColorStr(info_area_x+3,info_data_y+2, str.c_str(), gpC_base->m_chatting_pi, RGB_WHITE);
				info_data_y += 18;

				// À¯Àú ¼ºÇâ
				if(m_user_alignment >= 0 && m_user_alignment < 5)
					g_PrintColorStr(info_area_x+3,info_data_y+2,align_temp[m_user_alignment], gpC_base->m_chatting_pi, RGB_BRIGHT_GRAY);	
				info_data_y += 18;

				// À¯Àú ±â¿©µµ
				char szContribute[128] = {0};
				int contributeGrade = countContributeGrade(m_user_contribute);	
				if (contributeGrade >= 0 || contributeGrade < 8)
				{
					wsprintf(szContribute,"%d/%d%s %s",m_user_contribute,contributeGrade,(*g_pGameStringTable)[UI_STRING_CONTRIBUTE_GRADE].GetString(),(*g_pGameStringTable)[UI_STRING_MESSAGE_OUSTERS_CONTRIBUTENAME_7+(7-contributeGrade)].GetString());
					g_PrintColorStr(info_area_x+3,info_data_y+2,szContribute,m_print_info,RGB_BRIGHT_GRAY);
				}
				info_data_y += 18;
			}
		}

		g_FL2_ReleaseDC();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}

	if (gpC_base->m_p_DDSurface_back->Lock())
	{// ¸Þ¸ð ¿µ¿ª
		CRect box;
		box = m_friend_edit_box;
		box.left += x;
		box.right += x;
		box.top += y;
		box.bottom += y;

		// Ä£±¸ ÀÌ¸§ ÀÔ·ÂÃ¢
		gpC_base->m_p_DDSurface_back->BltColorAlpha(box,BLACK,25);
		gpC_base->m_p_DDSurface_back->Unlock();

		gpC_base->m_p_DDSurface_back->DrawRect(box,DARKGRAY);

		// Ä£±¸ ÀÌ¸§ ÀÔ·ÂÃ¢
		int editbox_x = box.left + 3;
		int editbox_y = box.top + 3;
		m_friend_info_edit_box.SetPosition(editbox_x,editbox_y);
		m_friend_info_edit_box.Show();
	}

	// Á¤º¸Ã¢ ¿É¼ÇÀÇ ±â´ÉÀ» ¿ÏÀüÈ÷ ²¨µÐ´Ù.
	// 09.07.02 - ÇöÀç ³íÀÇµÈ »çÇ×À¸·Î ¿©·¯°¡Áö ¹®Á¦Á¡ÀÌ ¸¹¾Æ Áö±ÝÀº »ç¿ëÇÏÁö ¾Êµµ·Ï ÇÑ´Ù.
	/*{// Á¤º¸Ã¢ ¿É¼Ç
		int str_pos_x = x + (w - static_cast<int>(static_cast<float>(w) * 0.89f));
		int paper_pos_y = y + static_cast<int>(static_cast<float>(h) * 0.78f);
		int my_info_pos_y = y + static_cast<int>(static_cast<float>(h) * 0.835f);

		m_check_box_paper.Show();
		m_check_box_my_info.Show();

		g_FL2_GetDC();

		// ÂÊÁö ¼³Á¤
		g_PrintColorStr(str_pos_x,paper_pos_y,"ÂÊÁö¸¦ ¹ÞÁö ¾Ê½À´Ï´Ù.",m_print_info,RGB_BLACK);
		// ³» Á¤º¸ º¸¿©ÁÖ±â ¼ö¶ô ¿©ºÎ
		g_PrintColorStr(str_pos_x,my_info_pos_y,"³» Á¤º¸¸¦ º¸¿©ÁÖÁö ¾Ê½À´Ï´Ù.",m_print_info,RGB_BLACK);

		g_FL2_ReleaseDC();
	}*/

	m_p_button_group->Show();
}

void C_VS_UI_FRIEND_INFO::Process()
{
	if (!Running()) return;

	// Á¤º¸Ã¢ ¿É¼ÇÀÇ ±â´ÉÀ» ¿ÏÀüÈ÷ ²¨µÐ´Ù.
	// 09.07.02 - ÇöÀç ³íÀÇµÈ »çÇ×À¸·Î ¿©·¯°¡Áö ¹®Á¦Á¡ÀÌ ¸¹¾Æ Áö±ÝÀº »ç¿ëÇÏÁö ¾Êµµ·Ï ÇÑ´Ù.
	/*m_check_box_paper.Process();
	m_check_box_my_info.Process();*/
	m_p_button_group->Process();
}

void C_VS_UI_FRIEND_INFO::Run(id_t id)
{
	switch (id)
	{
	case EIDESCRIPTION:		// Ä£±¸ Ãß°¡ È®ÀÎ ¹öÆ°
		break;
	case EICLOSE:			// Ä£±¸ Ãß°¡ Ãë¼Ò ¹öÆ°
		gpC_base->SendMessage(UI_DESTROY,0,0,(void*)m_window_name.c_str());
		break;
	case EIOK:				// Ä£±¸ Ãß°¡ Ãë¼Ò ¹öÆ°
		SendOptionInfo();
		break;
	}	
}

bool C_VS_UI_FRIEND_INFO::MouseControl(UINT message, int _x, int _y)
{
	if (!Running()) return false;

				// Ã³À½ ¸Þ¸ð¸¦ ÀÔ·Â ÇÒ¶© ÆíÁýÃ¢ÀÇ ±âº» ³»¿ëÀ» ¾ø¾Ø´Ù.
	std::string str = "";
			
#ifdef __DESIGNED_CHS
	str = "µ¥»÷ºóÊäÈëºÃÓÑ±¸×¢.";
#else
	str = "Please click to write a note.";
#endif	

	Window::MouseControl(message,_x,_y);
	_x -= x; _y -= y;

	if (m_friend_edit_box.PtInRect(CPoint(_x,_y)))
	{
		if (message == M_LEFTBUTTON_DOWN)
		{
			char* memo = NULL;
			g_Convert_DBCS_Ascii2SingleByte(m_friend_info_edit_box.GetString(),m_friend_info_edit_box.Size(),memo);
			if (memo && str.compare(memo) == 0)
			{
				m_friend_info_edit_box.EraseAll();
			}
			m_friend_info_edit_box.Acquire();
		}
		return true;
	}
	else
	{
		if (message == M_LEFTBUTTON_DOWN)
		{
			if (m_friend_info_edit_box.Size() == 0)
			{
				// ÀÔ·ÂµÈ ¸Þ¸ð°¡ ¾ø´Ù¸é ±âº» ¸Þ¸ð·Î µÇµ¹¸°´Ù.
				m_friend_info_edit_box.AddString( str.c_str() );
			}
			m_friend_info_edit_box.Unacquire();
			gC_vs_ui.AcquireChatting();
		}
	}

	bool inButton = m_p_button_group->MouseControl(message, _x, _y);
	// Á¤º¸Ã¢ ¿É¼ÇÀÇ ±â´ÉÀ» ¿ÏÀüÈ÷ ²¨µÐ´Ù.
	// 09.07.02 - ÇöÀç ³íÀÇµÈ »çÇ×À¸·Î ¿©·¯°¡Áö ¹®Á¦Á¡ÀÌ ¸¹¾Æ Áö±ÝÀº »ç¿ëÇÏÁö ¾Êµµ·Ï ÇÑ´Ù.
	/*
	bool check_paper = m_check_box_paper.MouseControl(message,_x,_y);
	bool check_info = m_check_box_my_info.MouseControl(message,_x,_y);
	*/

	if (message == M_LEFTBUTTON_DOWN && inButton)// && check_paper && check_info)
	{
		MoveReady();
		SetOrigin(_x,_y);
	}

	return true;
}

void C_VS_UI_FRIEND_INFO::KeyboardControl(UINT message, UINT key, long extra)
{
	if (!Running()) return;

	if (message == WM_KEYDOWN)
	{
		switch (key)
		{
		case VK_ESCAPE:
			//gpC_base->SendMessage(UI_DESTROY,0,0,(void*)m_window_name.c_str());
			break;		
		}
	}
}

bool C_VS_UI_FRIEND_INFO::IsPixel(int _x,int _y)
{
	if (!Running()) return false;

	return IsInRect(_x, _y);
}

void C_VS_UI_FRIEND_INFO::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{
	// ¼³¸í ¹öÆ° ¹× ´Ý±â ¹öÆ°
	if (p_button->GetID() == EIDESCRIPTION || p_button->GetID() == EICLOSE)
	{
		if (p_button->GetFocusState() && p_button->GetPressState())
			m_p_friend_common->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+1);
		else
			m_p_friend_common->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index);
	}
	// ¼öÁ¤ ¹× ´Ý±â ¹öÆ°
	else
	{
		if (p_button->GetFocusState())
		{
			if (p_button->GetPressState())
				m_p_friend_info->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+2);
			else
				m_p_friend_info->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+1);
		}
		else
			m_p_friend_info->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index);
	}
}

void C_VS_UI_FRIEND_INFO::ShowButtonDescription(C_VS_UI_EVENT_BUTTON *p_button)
{

}

void C_VS_UI_FRIEND_INFO::SendOptionInfo()
{
	// Á¤º¸Ã¢ ¿É¼ÇÀÇ ±â´ÉÀ» ¿ÏÀüÈ÷ ²¨µÐ´Ù.
	// 09.07.02 - ÇöÀç ³íÀÇµÈ »çÇ×À¸·Î ¿©·¯°¡Áö ¹®Á¦Á¡ÀÌ ¸¹¾Æ Áö±ÝÀº »ç¿ëÇÏÁö ¾Êµµ·Ï ÇÑ´Ù.
	/*if (0)
	{
		m_option_info.SetOptionToRecvMesg(m_check_box_paper.GetCheck()^1);
		m_option_info.SetOptionToNotifyMyInfo(m_check_box_my_info.GetCheck()^1);
	}*/

	char* memo = NULL;
	g_Convert_DBCS_Ascii2SingleByte(m_friend_info_edit_box.GetString(),m_friend_info_edit_box.Size(),memo);
	if (memo)
	{
		m_user_memo = memo;
		m_info_data.m_user_name = m_user_name;
		m_info_data.m_option_info.SetMemo(m_user_memo);
	}

	gpC_base->SendMessage(UI_FRIEND_INFO_OPTION,0,0,(void*)&m_info_data);
	gpC_base->SendMessage(UI_DESTROY,0,0,(void*)m_window_name.c_str());
}

/*
	Ä£±¸ ´ë±âÃ¢ UI Å¬·¡½º
*/
C_VS_UI_FRIEND_WAIT::C_VS_UI_FRIEND_WAIT()
{
	g_RegisterWindow(this);
	gpC_window_manager->AppearWindow(this);

	m_p_friend_common = new C_SPRITE_PACK(SPK_FRIEND_COMMON);
	m_p_friend_wait = new C_SPRITE_PACK(SPK_FRIEND_WAIT);
	m_p_button_group = new ButtonGroup(this);

	w = m_p_friend_wait->GetWidth(FWSI_BACKGROUND);
	h = m_p_friend_wait->GetHeight(FWSI_BACKGROUND);
	x = (g_pUserInformation->iResolution_x/2)-(w/2);
	y = g_pUserInformation->iResolution_y/3;
	
	// ¼³¸í ¹öÆ°
	/*p_button_group->Add(new C_VS_UI_EVENT_BUTTON(w-37, 5,
			m_p_friend_common->GetWidth(FCSI_DESCRIPTION_BUTTON_NORMAL), m_p_friend_common->GetHeight(FCSI_DESCRIPTION_BUTTON_NORMAL),
			EIDESCRIPTION, this, FCSI_DESCRIPTION_BUTTON_NORMAL));*/
	// ´Ý±â ¹öÆ°
	m_p_button_group->Add(new C_VS_UI_EVENT_BUTTON(w-20, 5,
			m_p_friend_common->GetWidth(FCSI_CLOSE_BUTTON_NORMAL), m_p_friend_common->GetHeight(FCSI_CLOSE_BUTTON_NORMAL),
			EICLOSE, this, FCSI_CLOSE_BUTTON_NORMAL));

	int list_view_x = 8;
	int list_view_y = static_cast<int>(static_cast<float>(h) * 0.12f);

	// 10Àº º¸¿©Áö´Â ¸ñ·ÏÀÇ °³¼ö
	for (int i = 0; i < 10; ++i)
	{
		int button_y = list_view_y + (23 * (i + 1));

		// Ãß°¡ ¹öÆ°
		m_p_button_group->Add(new C_VS_UI_EVENT_BUTTON(list_view_x + 135, button_y + 3,
				m_p_friend_wait->GetWidth(FWSI_ADD_NORMAL), m_p_friend_wait->GetHeight(FWSI_ADD_NORMAL),
				EIADD+i, this, FWSI_ADD_NORMAL));
		// »èÁ¦ ¹öÆ°
		m_p_button_group->Add(new C_VS_UI_EVENT_BUTTON(list_view_x + 185, button_y + 3,
				m_p_friend_wait->GetWidth(FWSI_DEL_NORMAL), m_p_friend_wait->GetHeight(FWSI_DEL_NORMAL),
				EIDEL+i, this, FWSI_DEL_NORMAL));
	}

	m_friend_wait_list_view = new C_VS_UI_FRIEND_WAIT_LISTVIEW(this,list_view_x,list_view_y,234,253,
				C_VS_UI_LISTVIEW::LSFOUTLINE|C_VS_UI_LISTVIEW::LSFFRAMELINE);
	m_friend_wait_list_view->InitColumnHeader(3,C_VS_UI_LISTVIEW::CHACENTER);
#ifdef __DESIGNED_CHS
	m_friend_wait_list_view->SetColumnHeader("ÐÕÃû",0,134);
	m_friend_wait_list_view->SetColumnHeader("ÔÊÐí",1,50);
	m_friend_wait_list_view->SetColumnHeader("¾Ü¾ø",2,50);
#else
	m_friend_wait_list_view->SetColumnHeader("Name",0,134);
	m_friend_wait_list_view->SetColumnHeader("Allow",1,50);
	m_friend_wait_list_view->SetColumnHeader("Deny",2,50);
#endif	

	m_friend_wait_list_view->SetScrollSpkImage(m_p_friend_common);
}

C_VS_UI_FRIEND_WAIT::~C_VS_UI_FRIEND_WAIT()
{
	gpC_window_manager->DisappearWindow(this);
	g_UnregisterWindow(this);

	if (m_p_button_group != NULL)
		DeleteNew(m_p_button_group);
	if (m_friend_wait_list_view != NULL)
		DeleteNew(m_friend_wait_list_view);
	if (m_p_friend_common != NULL)
		DeleteNew(m_p_friend_common);
	if (m_p_friend_wait != NULL)
		DeleteNew(m_p_friend_wait);
}

void C_VS_UI_FRIEND_WAIT::Start()
{
	PI_Processor::Start();
	gpC_window_manager->FirstPriority(this);
	m_friend_wait_list_view->Start();
	m_p_button_group->Init();
}

void C_VS_UI_FRIEND_WAIT::Finish()
{
	PI_Processor::Finish();
	m_friend_wait_list_view->Finish();
}

void C_VS_UI_FRIEND_WAIT::Show()
{
	if (!Running()) return;
	
	if (gpC_base->m_p_DDSurface_back->Lock())
	{
		{// ¹è°æ
			m_p_friend_wait->BltLocked(x,y,FWSI_BACKGROUND);
		}

		{// ¹®±¸
			int title_w = m_p_friend_wait->GetWidth(FWSI_TITLE);
			int title_y = y + static_cast<int>(static_cast<float>(h) * 0.02f);
			m_p_friend_wait->BltLocked((x+(w/2))-(title_w/2),title_y,FWSI_TITLE);
		}

		{// Å×µÎ¸®
			m_p_friend_common->BltLocked(x,y-m_p_friend_common->GetHeight(FCSI_TOP_OUTLINE),FCSI_TOP_OUTLINE);
			m_p_friend_common->BltLocked(x,y+m_p_friend_wait->GetHeight(FWSI_BACKGROUND),FCSI_BOTTOM_OUTLINE);
			m_p_friend_common->BltLocked(x-m_p_friend_common->GetWidth(FCSI_LEFT_OUTLINE),y,FCSI_LEFT_OUTLINE);
			m_p_friend_common->BltLocked(x+m_p_friend_wait->GetWidth(FWSI_BACKGROUND),y,FCSI_RIGHT_OUTLINE);
		}

		{// Å×µÎ¸® Àå½Ä
			int decoration_gap_w = 35;
			int decoration_gap_h = 37;
			int decoration_w = m_p_friend_common->GetWidth(FCSI_LEFTTOPOUTLINE_DECORATION);
			int decoration_h = m_p_friend_common->GetHeight(FCSI_LEFTTOPOUTLINE_DECORATION);

			m_p_friend_common->BltLocked(x-decoration_gap_w,y-decoration_gap_h,
									FCSI_LEFTTOPOUTLINE_DECORATION);
			m_p_friend_common->BltLocked(x+w-(decoration_w-decoration_gap_w),y-decoration_gap_h,
									FCSI_RIGHTTOPOUTLINE_DECORATION);
			m_p_friend_common->BltLocked(x-decoration_gap_w,y+h-(decoration_h-decoration_gap_h),
									FCSI_LEFTBOTTOMOUTLINE_DECORATION);
			m_p_friend_common->BltLocked(x+w-(decoration_w-decoration_gap_w),y+h-(decoration_h-decoration_gap_h),
									FCSI_RIGHTBOTTOMOUTLINE_DECORATION);
		}

		gpC_base->m_p_DDSurface_back->Unlock();
	}

	m_friend_wait_list_view->Show();
	m_p_button_group->Show();
}

void C_VS_UI_FRIEND_WAIT::Process()
{
	if (!Running()) return;

	m_p_button_group->Process();
	m_friend_wait_list_view->Process();
}

void C_VS_UI_FRIEND_WAIT::Run(id_t id)
{
	if (!Running()) return;

	switch (id)
	{
	case EIDESCRIPTION:	// ¼³¸í ¹öÆ°
		return;
	case EICLOSE:		// ´Ý±â ¹öÆ°
		Finish();
		return;
	}

	if (id >= EIADD && id < EIDEL)
	{// Ãß°¡ ¹öÆ°
		// Ä£±¸ Ãß°¡·Î ÀÎÇÑ »ó´ë¹æ È®ÀÎ ¸Þ½ÃÁö
		int index = id - EIADD;
		if (index < 0 || index >= m_friend_wait_list_view->GetItemSize())
			return;
		m_str_player_name = m_friend_wait_list_view->GetItemNameByIndex(index,0);
		m_friend_wait_list_view->DeleteColumnItem(m_str_player_name.c_str());
		gpC_base->SendMessage(UI_FRIEND_RES_ADD,1,0,(void*)m_str_player_name.c_str());
	}
	else if (id >= EIDEL)
	{
		// Ä£±¸ Ãß°¡·Î ÀÎÇÑ »ó´ë¹æ È®ÀÎ ¸Þ½ÃÁö
		int index = id - EIDEL;
		if (index < 0 || index >= m_friend_wait_list_view->GetItemSize())
			return;
		m_str_player_name = m_friend_wait_list_view->GetItemNameByIndex(index,0);
		m_friend_wait_list_view->DeleteColumnItem(m_str_player_name.c_str());
		gpC_base->SendMessage(UI_FRIEND_RES_ADD,0,1,(void*)m_str_player_name.c_str());
	}
}

bool C_VS_UI_FRIEND_WAIT::MouseControl(UINT message, int _x, int _y)
{
	if (!Running()) return false;

	int or_x = _x, or_y = _y;
	Window::MouseControl(message,_x,_y);
	_x -= x; _y -= y;

	bool inButton = m_p_button_group->MouseControl(message, _x, _y);
	bool inList = m_friend_wait_list_view->IsPixel(_x+x,_y+y);

	if (message == M_LEFTBUTTON_DOWN && inButton && !inList)
	{
		MoveReady();
		SetOrigin(_x,_y);
	}
	m_friend_wait_list_view->MouseControl(message,or_x,or_y);

	return true;
}

void C_VS_UI_FRIEND_WAIT::KeyboardControl(UINT message, UINT key, long extra)
{
	if (!Running()) return;

	if (message == WM_KEYDOWN)
	{
		switch (key)
		{
		case VK_ESCAPE:
			//Finish();
			break;		
		}
	}
}

bool C_VS_UI_FRIEND_WAIT::IsPixel(int _x,int _y)
{
	if (!Running()) return false;

	return IsInRect(_x, _y);
}

void C_VS_UI_FRIEND_WAIT::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{
	if (p_button->GetID() != EIDESCRIPTION && p_button->GetID() != EICLOSE)
	{
		int all_size = m_friend_wait_list_view->GetItemSize();
		int button_index = all_size;
		if (p_button->GetID() < EIDEL)
			button_index = (p_button->GetID() - EIADD);
		else if (p_button->GetID() >= EIDEL)
			button_index = (p_button->GetID() - EIDEL);
		if (button_index < all_size)
		{
			if (p_button->GetFocusState())
			{
				if (p_button->GetPressState())
					m_p_friend_wait->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+2);
				else
					m_p_friend_wait->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+1);
			}
			else
				m_p_friend_wait->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index);
		}
	}
	else
	{
		if (p_button->GetFocusState() && p_button->GetPressState())
			m_p_friend_common->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+1);
		else
			m_p_friend_common->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index);
	}
}

void C_VS_UI_FRIEND_WAIT::ShowButtonDescription(C_VS_UI_EVENT_BUTTON *p_button)
{

}

/*
	Ä£±¸ ½Ã½ºÅÛ ¿É¼ÇÃ¢ UI Å¬·¡½º
*/
C_VS_UI_FRIEND_SYSTEM_OPTION::C_VS_UI_FRIEND_SYSTEM_OPTION()
{
	g_RegisterWindow(this);
	
	m_friend_spk = new C_SPRITE_PACK(SPK_FRIEND_COMMON);
	m_p_button_group = new ButtonGroup(this);
	m_print_info = gpC_base->m_dialog_msg_pi;

	m_old_check_state_confirm = false;
	m_old_check_state_paper = false;
	m_old_check_state_my_info = false;

	w = m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX);
	h = m_friend_spk->GetHeight(FCSI_POPUP_MESSAGE_BOX);
	x = (g_pUserInformation->iResolution_x/2)-(w/2);
	y = g_pUserInformation->iResolution_y/3;

	int left_ok_button_x = (w/2)/2-(m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK)/4);
	int right_cancel_button_x = ((w/2)+((w/2)/2))-(m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK)-(m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK)/4));
	int left_ok_button_y = static_cast<int>(static_cast<float>(h)*0.6f);

	// È®ÀÎ ¹öÆ°
	m_p_button_group->Add(new C_VS_UI_EVENT_BUTTON(left_ok_button_x,left_ok_button_y,
			m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK),m_friend_spk->GetHeight(FCSI_POPUP_MESSAGE_BOX_OK),
			EIOK,this,FCSI_POPUP_MESSAGE_BOX_OK));
	// Ãë¼Ò ¹öÆ°
	m_p_button_group->Add(new C_VS_UI_EVENT_BUTTON(right_cancel_button_x,left_ok_button_y,
			m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_CANCEL),m_friend_spk->GetHeight(FCSI_POPUP_MESSAGE_BOX_CANCEL),
			EICANCEL,this,FCSI_POPUP_MESSAGE_BOX_CANCEL));
}

C_VS_UI_FRIEND_SYSTEM_OPTION::~C_VS_UI_FRIEND_SYSTEM_OPTION()
{
	g_UnregisterWindow(this);

	if (m_p_button_group != NULL)
		DeleteNew(m_p_button_group);
	if (m_friend_spk != NULL)
		DeleteNew(m_friend_spk);
}

void C_VS_UI_FRIEND_SYSTEM_OPTION::Start()
{
	PI_Processor::Start();
	gpC_window_manager->AppearWindow(this);
	m_p_button_group->Init();

	int check_box_x = w - static_cast<int>(static_cast<float>(w) * 0.84f);
	int confirm_pos_y = static_cast<int>(static_cast<float>(h) * 0.25f);
	int paper_pos_y = static_cast<int>(static_cast<float>(h) * 0.35f);
	int my_info_pos_y = static_cast<int>(static_cast<float>(h) * 0.45f);

	m_check_box_confirm.SetParent(this);
	m_check_box_confirm.SetPos(check_box_x,confirm_pos_y);
	m_check_box_paper.SetParent(this);
	m_check_box_paper.SetPos(check_box_x,paper_pos_y);
	m_check_box_my_info.SetParent(this);
	m_check_box_my_info.SetPos(check_box_x,my_info_pos_y);
	m_check_box_confirm.Start();
	m_check_box_paper.Start();
	m_check_box_my_info.Start();
}

void C_VS_UI_FRIEND_SYSTEM_OPTION::Finish()
{
	PI_Processor::Finish();
	gpC_window_manager->DisappearWindow(this);
	m_check_box_confirm.Finish();
	m_check_box_paper.Finish();
	m_check_box_my_info.Finish();
}

void C_VS_UI_FRIEND_SYSTEM_OPTION::Show()
{
	if (!Running()) return;
	
	if(gpC_base->m_p_DDSurface_back->Lock())
	{
		// ¸Þ½ÃÁö ¹Ú½º
		m_friend_spk->BltLocked(x,y,FCSI_POPUP_MESSAGE_BOX);
		gpC_base->m_p_DDSurface_back->Unlock();
	}

	{// Á¤º¸Ã¢ ¿É¼Ç
		int str_pos_x = x + (w - static_cast<int>(static_cast<float>(w) * 0.78f));
		int confirm_pos_y = y + static_cast<int>(static_cast<float>(h) * 0.25f);
		int paper_pos_y = y + static_cast<int>(static_cast<float>(h) * 0.35f);
		int my_info_pos_y = y + static_cast<int>(static_cast<float>(h) * 0.45f);

		g_FL2_GetDC();

#ifdef __DESIGNED_CHS
		// Ä£±¸ Ãß°¡ È®ÀÎÃ¢ ÆË¾÷
		g_PrintColorStr(str_pos_x,confirm_pos_y,"Pop-up the confirmation window of freind joining",m_print_info,RGB_BLACK);
		// ÂÊÁö ¼³Á¤
		g_PrintColorStr(str_pos_x,paper_pos_y,"Temporary close receiving message window",m_print_info,RGB_BLACK);
		// ³» Á¤º¸ º¸¿©ÁÖ±â ¼ö¶ô ¿©ºÎ
		g_PrintColorStr(str_pos_x,my_info_pos_y,"Temporary close sending message window",m_print_info,RGB_BLACK);
#else
		// Ä£±¸ Ãß°¡ È®ÀÎÃ¢ ÆË¾÷
		g_PrintColorStr(str_pos_x,confirm_pos_y,"Pop-up the confirmation window of freind joining",m_print_info,RGB_BLACK);
		// ÂÊÁö ¼³Á¤
		g_PrintColorStr(str_pos_x,paper_pos_y,"Temporary close receiving message window",m_print_info,RGB_BLACK);
		// ³» Á¤º¸ º¸¿©ÁÖ±â ¼ö¶ô ¿©ºÎ
		g_PrintColorStr(str_pos_x,my_info_pos_y,"Temporary close sending message window",m_print_info,RGB_BLACK);
#endif

		g_FL2_ReleaseDC();

		m_check_box_confirm.Show();
		m_check_box_paper.Show();
		m_check_box_my_info.Show();
	}
	m_p_button_group->Show();
}

void C_VS_UI_FRIEND_SYSTEM_OPTION::Process()
{
	if (!Running()) return;

	m_check_box_confirm.Process();
	m_check_box_paper.Process();
	m_check_box_my_info.Process();
	m_p_button_group->Process();
}

void C_VS_UI_FRIEND_SYSTEM_OPTION::Run(id_t id)
{
	if (!Running()) return;

	switch (id)
	{
	case EIOK:			// È®ÀÎ ¹öÆ°
		if (m_old_check_state_confirm != m_check_box_confirm.GetCheck() || m_old_check_state_paper != m_check_box_paper.GetCheck() || m_old_check_state_my_info != m_check_box_my_info.GetCheck())
		{
			C_VS_UI_FRINEND_OPTION_CONFIRM* pFriend = (C_VS_UI_FRINEND_OPTION_CONFIRM*)gpC_window_manager->GetWindowbyName("FriendOptionConfirm");
			if (pFriend)
			{
				if (pFriend->Running())
				{
					pFriend->Finish();
					DeleteNew(pFriend);
				}
				else
				{
					DeleteNew(pFriend);
				}
			}
			pFriend = new C_VS_UI_FRINEND_OPTION_CONFIRM;
			pFriend->SetParentWindowType(C_VS_UI_FRINEND_OPTION_CONFIRM::PT_SYSTEM_OPTION,this);
			pFriend->SetWindowName("FriendOptionConfirm");
			pFriend->Start();
		}
		return;
	case EICANCEL:		// Ãë¼Ò ¹öÆ°
		Finish();
		return;
	}
}

bool C_VS_UI_FRIEND_SYSTEM_OPTION::MouseControl(UINT message, int _x, int _y)
{
	if (!Running()) return false;

	Window::MouseControl(message,_x,_y);
	_x -= x; _y -= y;

	bool inButton = m_p_button_group->MouseControl(message, _x, _y);
	bool check_confirm = m_check_box_confirm.MouseControl(message,_x,_y);
	bool check_paper = m_check_box_paper.MouseControl(message,_x,_y);
	bool check_info = m_check_box_my_info.MouseControl(message,_x,_y);

	if (message == M_LEFTBUTTON_DOWN && inButton && check_confirm && check_paper && check_info)
	{
		MoveReady();
		SetOrigin(_x,_y);
	}

	return true;
}

void C_VS_UI_FRIEND_SYSTEM_OPTION::KeyboardControl(UINT message, UINT key, long extra)
{
	if (!Running()) return;

	if (message == WM_KEYDOWN)
	{
		switch (key)
		{
		case VK_RETURN:
			break;
		case VK_ESCAPE:
			//gpC_base->SendMessage(UI_DESTROY,0,0,(void*)m_window_name.c_str());
			break;		
		}
	}
}

bool C_VS_UI_FRIEND_SYSTEM_OPTION::IsPixel(int _x,int _y)
{
	if (!Running()) return false;

	return IsInRect(_x, _y);
}

void C_VS_UI_FRIEND_SYSTEM_OPTION::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{
	if (p_button->GetFocusState())
	{
		if (p_button->GetPressState())
			m_friend_spk->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+2);
		else
			m_friend_spk->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+1);
	}
	else
		m_friend_spk->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index);
}

void C_VS_UI_FRIEND_SYSTEM_OPTION::ShowButtonDescription(C_VS_UI_EVENT_BUTTON *p_button)
{

}

void C_VS_UI_FRIEND_SYSTEM_OPTION::SendOptionInfo()
{
	/*m_option_info.SetOptionToPopupWaitList(m_check_box_confirm.GetCheck());
	m_option_info.SetOptionToRecvMesg(m_check_box_paper.GetCheck()^1);
	m_option_info.SetOptionToNotifyMyInfo(m_check_box_my_info.GetCheck()^1);*/
	
	gpC_base->SendMessage(UI_FRIEND_SYSTEM_OPTION,0,0,(void*)&m_option_info);

	Finish();
}

/*
	Ä£±¸ Ãß°¡Ã¢ UI Å¬·¡½º - ÀÌ¸§À» Á÷Á¢ ÀÔ·Â
*/
C_VS_UI_FRINEND_ADD_INPUT_PLAYER::C_VS_UI_FRINEND_ADD_INPUT_PLAYER()
{
	g_RegisterWindow(this);
			
	m_friend_spk = new C_SPRITE_PACK(SPK_FRIEND_COMMON);
	m_pC_button_group = new ButtonGroup(this);
	m_print_info = gpC_base->m_dialog_msg_pi;

#ifdef __DESIGNED_CHS
	m_str_message = "ÇëÊäÈëºÃÓÑµÄÐÕÃû!";
#else
	m_str_message = "Please input character name of your friend!";
#endif

	w = m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX);
	h = m_friend_spk->GetHeight(FCSI_POPUP_MESSAGE_BOX);
	x = (g_pUserInformation->iResolution_x/2)-(w/2);
	y = g_pUserInformation->iResolution_y/3;

	int left_ok_button_x = (w/2)/2-(m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK)/4);
	int right_cancel_button_x = ((w/2)+((w/2)/2))-(m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK)-(m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK)/4));
	int left_ok_button_y = static_cast<int>(static_cast<float>(h)*0.6f);

	// È®ÀÎ ¹öÆ°
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(left_ok_button_x,left_ok_button_y,
			m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK),m_friend_spk->GetHeight(FCSI_POPUP_MESSAGE_BOX_OK),
			EIOK,this,FCSI_POPUP_MESSAGE_BOX_OK));
	// Ãë¼Ò ¹öÆ°
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(right_cancel_button_x,left_ok_button_y,
			m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_CANCEL),m_friend_spk->GetHeight(FCSI_POPUP_MESSAGE_BOX_CANCEL),
			EICANCEL,this,FCSI_POPUP_MESSAGE_BOX_CANCEL));

	int editbox_x = x + ((w/2)-64);
	int editbox_y = y + static_cast<int>(static_cast<float>(h)*0.46f) + 3;
	// Ä£±¸ ÀÌ¸§ ÀÔ·ÂÃ¢
	m_friend_edit_box.SetPosition(editbox_x,editbox_y);
	m_friend_edit_box.SetPrintInfo(gpC_base->m_chatting_pi);
	m_friend_edit_box.SetByteLimit(10);
	m_friend_edit_box.SetInputStringColor(RGB_BLACK);
	m_friend_edit_box.SetCursorColor(RGB_BLACK);
	m_friend_edit_box.SetDigitOnlyMode(false);
	m_friend_edit_box.SetAbsWidth(128);

	Attach(&m_friend_edit_box);
}

C_VS_UI_FRINEND_ADD_INPUT_PLAYER::~C_VS_UI_FRINEND_ADD_INPUT_PLAYER()
{
	g_UnregisterWindow(this);

	if (m_friend_spk)
		DeleteNew(m_friend_spk);
	DeleteNew(m_pC_button_group);
}

void C_VS_UI_FRINEND_ADD_INPUT_PLAYER::Start()
{
	PI_Processor::Start();
	gpC_window_manager->AppearWindow(this);
	m_friend_edit_box.Acquire();
	m_pC_button_group->Init();

	EMPTY_MOVE;
}

void C_VS_UI_FRINEND_ADD_INPUT_PLAYER::Finish()
{
	PI_Processor::Finish();
	gpC_window_manager->DisappearWindow(this);
	m_friend_edit_box.Unacquire();
	gC_vs_ui.AcquireChatting();
}

void C_VS_UI_FRINEND_ADD_INPUT_PLAYER::Show()
{
	if (!Running()) return;

	if(gpC_base->m_p_DDSurface_back->Lock())
	{
		// ¸Þ½ÃÁö ¹Ú½º
		m_friend_spk->BltLocked(x,y,FCSI_POPUP_MESSAGE_BOX);

		int editbox_x = x + ((w/2)-64) - 4;
		int editbox_y = y + static_cast<int>(static_cast<float>(h)*0.46f) - 3;

		CRect box(editbox_x,editbox_y,editbox_x+132,editbox_y+17);

		// Ä£±¸ ÀÌ¸§ ÀÔ·ÂÃ¢
		gpC_base->m_p_DDSurface_back->BltColorAlpha(box,WHITE,0);
		gpC_base->m_p_DDSurface_back->Unlock();

		gpC_base->m_p_DDSurface_back->DrawRect(box,BLACK);

		// Ä£±¸ ÀÌ¸§ ÀÔ·ÂÃ¢
		editbox_x += 4;
		editbox_y += 3;
		m_friend_edit_box.SetPosition(editbox_x,editbox_y);
		m_friend_edit_box.Show();
	}

	m_pC_button_group->Show();

	g_FL2_GetDC();
	{// ¸Þ½ÃÁö
		int message_x = x + static_cast<int>((w/2)/3.6f);
		int message_w = static_cast<int>(w*0.78f);
		int message_y = y + static_cast<int>(static_cast<float>(h)*0.25f);
		int message_h = 46;
		CRect TextBox(message_x,message_y,message_x+message_w,message_y+message_h);
		g_DrawText(TextBox,m_str_message.c_str(),&m_print_info);
	}
	g_FL2_ReleaseDC();
}

void C_VS_UI_FRINEND_ADD_INPUT_PLAYER::Process()
{
	if (!Running()) return;

	m_pC_button_group->Process();
}


void C_VS_UI_FRINEND_ADD_INPUT_PLAYER::Run(id_t id)
{
	switch (id)
	{
	case EIOK:		// Ä£±¸ Ãß°¡ È®ÀÎ ¹öÆ°
		if(m_friend_edit_box.Size())
		{
			char* szName;
			g_Convert_DBCS_Ascii2SingleByte(m_friend_edit_box.GetString(), m_friend_edit_box.Size(), szName);
			if(szName != NULL)
			{
				gpC_base->SendMessage(UI_FRIEND_ADD,0,0,(void*)szName);
			}
		}
		gpC_base->SendMessage(UI_DESTROY,0,0,(void*)m_window_name.c_str());
		break;
	case EICANCEL:	// Ä£±¸ Ãß°¡ Ãë¼Ò ¹öÆ°
		m_friend_edit_box.EraseAll();
		gpC_base->SendMessage(UI_DESTROY,0,0,(void*)m_window_name.c_str());
		break;
	}
}

bool C_VS_UI_FRINEND_ADD_INPUT_PLAYER::MouseControl(UINT message, int _x, int _y)
{
	if (!Running()) return false;

	Window::MouseControl(message,_x,_y);
	_x -= x; _y -= y;
	bool inButton = m_pC_button_group->MouseControl(message, _x, _y);

	if (message == M_LEFTBUTTON_DOWN && inButton)
	{
		MoveReady();
		SetOrigin(_x,_y);
	}
	return true;	
}

void C_VS_UI_FRINEND_ADD_INPUT_PLAYER::KeyboardControl(UINT message, UINT key, long extra)
{
	if (!Running()) return;

	if (message == WM_KEYDOWN)
	{
		switch (key)
		{
		case VK_RETURN:
			Run(EIOK);
			break;
		case VK_ESCAPE:
			//gpC_base->SendMessage(UI_DESTROY,0,0,(void*)m_window_name.c_str());
			break;		
		}
	}
}

void C_VS_UI_FRINEND_ADD_INPUT_PLAYER::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{
	if (p_button->GetFocusState())
	{
		if (p_button->GetPressState())
			m_friend_spk->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+2);
		else
			m_friend_spk->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+1);
	}
	else
		m_friend_spk->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index);
}

void C_VS_UI_FRINEND_ADD_INPUT_PLAYER::ShowButtonDescription(C_VS_UI_EVENT_BUTTON *p_button)
{

}

/*
	Ä£±¸ Ãß°¡Ã¢ UI Å¬·¡½º - ÆË¾÷¿¡¼­ Á÷Á¢ Ä£±¸ Ãß°¡
*/
C_VS_UI_FRINEND_ADD_IS_PLAYER::C_VS_UI_FRINEND_ADD_IS_PLAYER(const char* player)
{
	g_RegisterWindow(this);
		
	m_friend_spk = new C_SPRITE_PACK(SPK_FRIEND_COMMON);
	m_pC_button_group = new ButtonGroup(this);
	m_print_info = gpC_base->m_dialog_msg_pi;

	m_str_player = player;
	
#ifdef __DESIGNED_CHS
	m_str_message = "ÄãÏëºÍ¸Ã½ÇÉ«³ÉÎªºÃÓÑ?";
#else
	m_str_message = "Do you want to make friends with this character?";
#endif	

	w = m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX);
	h = m_friend_spk->GetHeight(FCSI_POPUP_MESSAGE_BOX);
	x = (g_pUserInformation->iResolution_x/2)-(w/2);
	y = g_pUserInformation->iResolution_y/3;

	int left_ok_button_x = (w/2)/2-(m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK)/4);
	int right_cancel_button_x = ((w/2)+((w/2)/2))-(m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK)-(m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK)/4));
	int left_ok_button_y = static_cast<int>(static_cast<float>(h)*0.5f);

	// È®ÀÎ ¹öÆ°
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(left_ok_button_x,left_ok_button_y,
			m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK),m_friend_spk->GetHeight(FCSI_POPUP_MESSAGE_BOX_OK),
			EIOK,this,FCSI_POPUP_MESSAGE_BOX_OK));
	// Ãë¼Ò ¹öÆ°
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(right_cancel_button_x,left_ok_button_y,
			m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_CANCEL),m_friend_spk->GetHeight(FCSI_POPUP_MESSAGE_BOX_CANCEL),
			EICANCEL,this,FCSI_POPUP_MESSAGE_BOX_CANCEL));
}

C_VS_UI_FRINEND_ADD_IS_PLAYER::~C_VS_UI_FRINEND_ADD_IS_PLAYER()
{
	g_UnregisterWindow(this);

	if (m_friend_spk)
		DeleteNew(m_friend_spk);
	DeleteNew(m_pC_button_group);
}

void C_VS_UI_FRINEND_ADD_IS_PLAYER::Start()
{
	PI_Processor::Start();
	gpC_window_manager->AppearWindow(this);
	m_pC_button_group->Init();

	EMPTY_MOVE;
}

void C_VS_UI_FRINEND_ADD_IS_PLAYER::Finish()
{
	PI_Processor::Finish();
	gpC_window_manager->DisappearWindow(this);
}

void C_VS_UI_FRINEND_ADD_IS_PLAYER::Show()
{
	if (!Running()) return;

	if(gpC_base->m_p_DDSurface_back->Lock())
	{
		// ¸Þ½ÃÁö ¹Ú½º
		m_friend_spk->BltLocked(x,y,FCSI_POPUP_MESSAGE_BOX);
		gpC_base->m_p_DDSurface_back->Unlock();
	}

	m_pC_button_group->Show();

	g_FL2_GetDC();
	{// ¸Þ½ÃÁö
		int message_x = x + static_cast<int>((w/2)/3.6f);
		int message_w = static_cast<int>(w*0.78f);
		int message_y = y + static_cast<int>(static_cast<float>(h)*0.3f);
		int message_h = 46;
		CRect TextBox(message_x,message_y,message_x+message_w,message_y+message_h);
		g_DrawText(TextBox,m_str_message.c_str(),&m_print_info);
	}
	g_FL2_ReleaseDC();
}

void C_VS_UI_FRINEND_ADD_IS_PLAYER::Process()
{
	if (!Running()) return;

	m_pC_button_group->Process();	
}


void C_VS_UI_FRINEND_ADD_IS_PLAYER::Run(id_t id)
{
	switch (id)
	{
	case EIOK:		// Ä£±¸ Ãß°¡ È®ÀÎ ¹öÆ°
		if(!m_str_player.empty())
		{
			char* szName = new char[m_str_player.size()];
			sprintf(szName,"%s",m_str_player.c_str());
			gpC_base->SendMessage(UI_FRIEND_ADD,0,0,(void*)szName);
		}
		gpC_base->SendMessage(UI_DESTROY,0,0,(void*)m_window_name.c_str());
		break;
	case EICANCEL:	// Ä£±¸ Ãß°¡ Ãë¼Ò ¹öÆ°
		gpC_base->SendMessage(UI_DESTROY,0,0,(void*)m_window_name.c_str());
		break;
	}
}

bool C_VS_UI_FRINEND_ADD_IS_PLAYER::MouseControl(UINT message, int _x, int _y)
{
	if (!Running()) return false;

	Window::MouseControl(message,_x,_y);
	_x -= x; _y -= y;
	bool inButton = m_pC_button_group->MouseControl(message, _x, _y);

	if (message == M_LEFTBUTTON_DOWN && inButton)
	{
		MoveReady();
		SetOrigin(_x,_y);
	}
	return true;	
}

void C_VS_UI_FRINEND_ADD_IS_PLAYER::KeyboardControl(UINT message, UINT key, long extra)
{
	if (!Running()) return;

	if (message == WM_KEYDOWN)
	{
		switch (key)
		{
		case VK_RETURN:
			Run(EIOK);
			break;
		case VK_ESCAPE:
			//gpC_base->SendMessage(UI_DESTROY,0,0,(void*)m_window_name.c_str());
			break;		
		}
	}
}

void C_VS_UI_FRINEND_ADD_IS_PLAYER::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{
	if (p_button->GetFocusState())
	{
		if (p_button->GetPressState())
			m_friend_spk->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+2);
		else
			m_friend_spk->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+1);
	}
	else
		m_friend_spk->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index);
}

void C_VS_UI_FRINEND_ADD_IS_PLAYER::ShowButtonDescription(C_VS_UI_EVENT_BUTTON *p_button)
{

}

/*
	Ä£±¸ »èÁ¦Ã¢ UI Å¬·¡½º
*/
C_VS_UI_FRINEND_DEL::C_VS_UI_FRINEND_DEL(const char* player)
{
	g_RegisterWindow(this);
		
	m_del_player_name = player;

	m_friend_spk = new C_SPRITE_PACK(SPK_FRIEND_COMMON);
	m_pC_button_group = new ButtonGroup(this);

#ifdef __DESIGNED_CHS
	m_str_message = "°Ñ¸Ã½ÇÉ«´ÓºÃÓÑÁÐ±íÀïÃæÉ¾³ý?"; 
#else
	m_str_message = "Do you want to delete this character from friends list?"; 
#endif
	
	w = m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX);
	h = m_friend_spk->GetHeight(FCSI_POPUP_MESSAGE_BOX);
	x = (g_pUserInformation->iResolution_x/2)-(w/2);
	y = g_pUserInformation->iResolution_y/3;

	int left_ok_button_x = (w/2)/2-(m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK)/4);
	int right_cancel_button_x = ((w/2)+((w/2)/2))-(m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK)-(m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK)/4));
	int left_ok_button_y = static_cast<int>(static_cast<float>(h)*0.5f);

	// È®ÀÎ ¹öÆ°
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(left_ok_button_x,left_ok_button_y,
			m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK),m_friend_spk->GetHeight(FCSI_POPUP_MESSAGE_BOX_OK),
			EIOK,this,FCSI_POPUP_MESSAGE_BOX_OK));
	// Ãë¼Ó ¹öÆ°
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(right_cancel_button_x,left_ok_button_y,
			m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_CANCEL),m_friend_spk->GetHeight(FCSI_POPUP_MESSAGE_BOX_CANCEL),
			EICANCEL,this,FCSI_POPUP_MESSAGE_BOX_CANCEL));
}

C_VS_UI_FRINEND_DEL::~C_VS_UI_FRINEND_DEL()
{
	g_UnregisterWindow(this);

	if (m_friend_spk)
		DeleteNew(m_friend_spk);
	DeleteNew(m_pC_button_group);
}

void C_VS_UI_FRINEND_DEL::Start()
{
	PI_Processor::Start();
	gpC_window_manager->AppearWindow(this);
	m_pC_button_group->Init();

	EMPTY_MOVE;
}

void C_VS_UI_FRINEND_DEL::Finish()
{
	PI_Processor::Finish();
	gpC_window_manager->DisappearWindow(this);
}

void C_VS_UI_FRINEND_DEL::Show()
{
	if (!Running()) return;

	if(gpC_base->m_p_DDSurface_back->Lock())
	{
		// ¸Þ½ÃÁö ¹Ú½º
		m_friend_spk->BltLocked(x,y,FCSI_POPUP_MESSAGE_BOX);
		gpC_base->m_p_DDSurface_back->Unlock();
	}
	
	m_pC_button_group->Show();

	g_FL2_GetDC();
	{// ¸Þ½ÃÁö
		int message_x = x + static_cast<int>((w/2)/3.6f);
		int message_w = static_cast<int>(w*0.78f);
		int message_y = y + static_cast<int>(static_cast<float>(h)*0.3f);
		int message_h = 46;
		CRect TextBox(message_x,message_y,message_x+message_w,message_y+message_h);
		g_DrawText(TextBox,m_str_message.c_str(),&gpC_base->m_dialog_msg_pi);
	}
	g_FL2_ReleaseDC();
}

void C_VS_UI_FRINEND_DEL::Process()
{
	if (!Running()) return;
	
	m_pC_button_group->Process();	
}


void C_VS_UI_FRINEND_DEL::Run(id_t id)
{
	switch (id)
	{
	case EIOK:		// Ä£±¸ »èÁ¦ È®ÀÎ ¹öÆ°
		if(!m_del_player_name.empty())
		{
			char* szName = new char[m_del_player_name.size()];
			sprintf(szName,"%s",m_del_player_name.c_str());
			gpC_base->SendMessage(UI_FRIEND_DEL,0,0,(void*)szName);
		}
		gpC_base->SendMessage(UI_DESTROY,0,0,(void*)m_window_name.c_str());
		break;
	case EICANCEL:	// Ä£±¸ »èÁ¦ Ãë¼Ò ¹öÆ°
		gpC_base->SendMessage(UI_DESTROY,0,0,(void*)m_window_name.c_str());
		break;
	}
}

bool C_VS_UI_FRINEND_DEL::MouseControl(UINT message, int _x, int _y)
{
	if (!Running()) return false;

	Window::MouseControl(message,_x,_y);
	_x -= x; _y -= y;
	bool inButton = m_pC_button_group->MouseControl(message, _x, _y);

	if (message == M_LEFTBUTTON_DOWN && inButton)
	{
		MoveReady();
		SetOrigin(_x,_y);
	}
	return true;	
}

void C_VS_UI_FRINEND_DEL::KeyboardControl(UINT message, UINT key, long extra)
{
	if (!Running()) return;

	if (message == WM_KEYDOWN)
	{
		switch (key)
		{
		case VK_RETURN:
			Run(EIOK);
			break;
		case VK_ESCAPE:
			//gpC_base->SendMessage(UI_DESTROY,0,0,(void*)m_window_name.c_str());
			break;		
		}
	}
}

void C_VS_UI_FRINEND_DEL::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{
	if (p_button->GetFocusState())
	{
		if (p_button->GetPressState())
			m_friend_spk->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+2);
		else
			m_friend_spk->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+1);
	}
	else
		m_friend_spk->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index);
}

void C_VS_UI_FRINEND_DEL::ShowButtonDescription(C_VS_UI_EVENT_BUTTON *p_button)
{

}

/*
	¼±ÅÃµÈ Ä£±¸°¡ ¾ø´Â »óÅÂ¿¡¼­ÀÇ Ä£±¸ »èÁ¦Ã¢ UI Å¬·¡½º
*/
C_VS_UI_FRINEND_DEL_NOTSELECT::C_VS_UI_FRINEND_DEL_NOTSELECT()
{
	g_RegisterWindow(this);
		
	m_friend_spk = new C_SPRITE_PACK(SPK_FRIEND_COMMON);
	m_pC_button_group = new ButtonGroup(this);

#ifdef __DESIGNED_CHS
	m_str_message = "ÇëÑ¡ÔñÒªÉ¾³ýµÄ½ÇÉ«!"; 
#else
	m_str_message = "Please select character to delete!"; 
#endif
	
	w = m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX);
	h = m_friend_spk->GetHeight(FCSI_POPUP_MESSAGE_BOX);
	x = (g_pUserInformation->iResolution_x/2)-(w/2);
	y = g_pUserInformation->iResolution_y/3;

	int ok_button_x = (w/2)-(m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK)/2);
	int ok_button_y = static_cast<int>(static_cast<float>(h)*0.5f);

	// È®ÀÎ ¹öÆ°
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(ok_button_x,ok_button_y,
			m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK),m_friend_spk->GetHeight(FCSI_POPUP_MESSAGE_BOX_OK),
			EIOK,this,FCSI_POPUP_MESSAGE_BOX_OK));
}

C_VS_UI_FRINEND_DEL_NOTSELECT::~C_VS_UI_FRINEND_DEL_NOTSELECT()
{
	g_UnregisterWindow(this);

	if (m_friend_spk)
		DeleteNew(m_friend_spk);
	DeleteNew(m_pC_button_group);
}

void C_VS_UI_FRINEND_DEL_NOTSELECT::Start()
{
	PI_Processor::Start();
	gpC_window_manager->AppearWindow(this);
	m_pC_button_group->Init();

	EMPTY_MOVE;
}

void C_VS_UI_FRINEND_DEL_NOTSELECT::Finish()
{
	PI_Processor::Finish();
	gpC_window_manager->DisappearWindow(this);
}

void C_VS_UI_FRINEND_DEL_NOTSELECT::Show()
{
	if (!Running()) return;

	if(gpC_base->m_p_DDSurface_back->Lock())
	{
		// ¸Þ½ÃÁö ¹Ú½º
		m_friend_spk->BltLocked(x,y,FCSI_POPUP_MESSAGE_BOX);
		gpC_base->m_p_DDSurface_back->Unlock();
	}
	
	m_pC_button_group->Show();

	g_FL2_GetDC();
	{// ¸Þ½ÃÁö
		int message_x = x + static_cast<int>((w/2)/2.4f);
		int message_w = static_cast<int>(w*0.78f);
		int message_y = y + static_cast<int>(static_cast<float>(h)*0.32f);
		int message_h = 46;
		CRect TextBox(message_x,message_y,message_x+message_w,message_y+message_h);
		g_DrawText(TextBox,m_str_message.c_str(),&gpC_base->m_dialog_msg_pi);
	}
	g_FL2_ReleaseDC();
}

void C_VS_UI_FRINEND_DEL_NOTSELECT::Process()
{
	if (!Running()) return;
	
	m_pC_button_group->Process();	
}


void C_VS_UI_FRINEND_DEL_NOTSELECT::Run(id_t id)
{
	switch (id)
	{
	case EIOK:	// È®ÀÎ ¹öÆ°
		gpC_base->SendMessage(UI_DESTROY,0,0,(void*)m_window_name.c_str());
		break;
	}
}

bool C_VS_UI_FRINEND_DEL_NOTSELECT::MouseControl(UINT message, int _x, int _y)
{
	if (!Running()) return false;

	Window::MouseControl(message,_x,_y);
	_x -= x; _y -= y;
	bool inButton = m_pC_button_group->MouseControl(message, _x, _y);

	if (message == M_LEFTBUTTON_DOWN && inButton)
	{
		MoveReady();
		SetOrigin(_x,_y);
	}
	return true;	
}

void C_VS_UI_FRINEND_DEL_NOTSELECT::KeyboardControl(UINT message, UINT key, long extra)
{
	if (!Running()) return;

	if (message == WM_KEYDOWN)
	{
		switch (key)
		{
		case VK_RETURN:
			Run(EIOK);
			break;
		case VK_ESCAPE:
			//gpC_base->SendMessage(UI_DESTROY,0,0,(void*)m_window_name.c_str());
			break;		
		}
	}
}

void C_VS_UI_FRINEND_DEL_NOTSELECT::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{
	if (p_button->GetFocusState())
	{
		if (p_button->GetPressState())
			m_friend_spk->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+2);
		else
			m_friend_spk->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+1);
	}
	else
		m_friend_spk->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index);
}

void C_VS_UI_FRINEND_DEL_NOTSELECT::ShowButtonDescription(C_VS_UI_EVENT_BUTTON *p_button)
{

}

/*
	Ä£±¸Ãß°¡ È®ÀÎÃ¢ UI Å¬·¡½º
*/
C_VS_UI_FRINEND_CONFIRM::C_VS_UI_FRINEND_CONFIRM(const char* player, const char* message)
{
	g_RegisterWindow(this);
		
	m_str_player_name = player;
	m_str_message = message;
	
	m_friend_spk = new C_SPRITE_PACK(SPK_FRIEND_COMMON);
	m_pC_button_group = new ButtonGroup(this);

	w = m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX);
	h = m_friend_spk->GetHeight(FCSI_POPUP_MESSAGE_BOX);
	x = (g_pUserInformation->iResolution_x/2)-(w/2);
	y = g_pUserInformation->iResolution_y/3;

	int left_ok_button_x = (w/2)/2-(m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK)/4);
	int right_cancel_button_x = ((w/2)+((w/2)/2))-(m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK)-(m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK)/4));
	int left_ok_button_y = static_cast<int>(static_cast<float>(h)*0.6f);

	// È®ÀÎ ¹öÆ° 
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(left_ok_button_x,left_ok_button_y,
			m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK),m_friend_spk->GetHeight(FCSI_POPUP_MESSAGE_BOX_OK),
			EIOK,this,FCSI_POPUP_MESSAGE_BOX_OK));
	// Ãë¼Ò ¹öÆ°
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(right_cancel_button_x,left_ok_button_y,
			m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_CANCEL),m_friend_spk->GetHeight(FCSI_POPUP_MESSAGE_BOX_CANCEL),
			EICANCEL,this,FCSI_POPUP_MESSAGE_BOX_CANCEL));
}

C_VS_UI_FRINEND_CONFIRM::~C_VS_UI_FRINEND_CONFIRM()
{
	g_UnregisterWindow(this);

	if (m_friend_spk)
		DeleteNew(m_friend_spk);
	DeleteNew(m_pC_button_group);
}

void C_VS_UI_FRINEND_CONFIRM::Start()
{
	PI_Processor::Start();
	gpC_window_manager->AppearWindow(this);
	m_pC_button_group->Init();

	EMPTY_MOVE;
}

void C_VS_UI_FRINEND_CONFIRM::Finish()
{
	PI_Processor::Finish();
	gpC_window_manager->DisappearWindow(this);
}

void C_VS_UI_FRINEND_CONFIRM::Show()
{
	if (!Running()) return;

	if(gpC_base->m_p_DDSurface_back->Lock())
	{
		// ¸Þ½ÃÁö ¹Ú½º
		m_friend_spk->BltLocked(x,y,FCSI_POPUP_MESSAGE_BOX);
		gpC_base->m_p_DDSurface_back->Unlock();
	}

	m_pC_button_group->Show();

	g_FL2_GetDC();
	{// ¸Þ½ÃÁö
		int message_x = x + static_cast<int>((w/2)/3.6f);
		int message_w = static_cast<int>(w*0.78f);
		int message_y = y + static_cast<int>(static_cast<float>(h)*0.3f);
		int message_h = 46;
		CRect TextBox(message_x,message_y,message_x+message_w,message_y+message_h);
		g_DrawText(TextBox,m_str_message.c_str(),&gpC_base->m_dialog_msg_pi);
	}
	g_FL2_ReleaseDC();
}

void C_VS_UI_FRINEND_CONFIRM::Process()
{
	if (!Running()) return;

	m_pC_button_group->Process();	
}

void C_VS_UI_FRINEND_CONFIRM::Run(id_t id)
{
	if (!Running()) return;

	switch (id)
	{
	case EIOK:		// Ä£±¸ Ãß°¡ È®ÀÎ ¹öÆ°
		gpC_base->SendMessage(UI_FRIEND_RES_ADD,1,0,(void*)m_str_player_name.c_str());
		gpC_base->SendMessage(UI_DESTROY,0,0,(void*)m_window_name.c_str());
		break;
	case EICANCEL:	// Ä£±¸ Ãß°¡ Ãë¼Ò ¹öÆ°
		gpC_base->SendMessage(UI_FRIEND_RES_ADD,0,1,(void*)m_str_player_name.c_str());
		gpC_base->SendMessage(UI_DESTROY,0,0,(void*)m_window_name.c_str());
		break;
	}
}

bool C_VS_UI_FRINEND_CONFIRM::MouseControl(UINT message, int _x, int _y)
{
	if (!Running()) return false;

	Window::MouseControl(message,_x,_y);
	_x -= x; _y -= y;
	bool inButton = m_pC_button_group->MouseControl(message, _x, _y);

	if (message == M_LEFTBUTTON_DOWN && inButton)
	{
		MoveReady();
		SetOrigin(_x,_y);
	}
	return true;	
}

void C_VS_UI_FRINEND_CONFIRM::KeyboardControl(UINT message, UINT key, long extra)
{
	if (!Running()) return;

	if (message == WM_KEYDOWN)
	{
		switch (key)
		{
		case VK_RETURN:
			Run(EIOK);
			break;
		case VK_ESCAPE:
			//gpC_base->SendMessage(UI_DESTROY,0,0,(void*)m_window_name.c_str());
			break;		
		}
	}
}

void C_VS_UI_FRINEND_CONFIRM::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{
	if (p_button->GetFocusState())
	{
		if (p_button->GetPressState())
			m_friend_spk->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+2);
		else
			m_friend_spk->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+1);
	}
	else
		m_friend_spk->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index);
}

void C_VS_UI_FRINEND_CONFIRM::ShowButtonDescription(C_VS_UI_EVENT_BUTTON *p_button)
{

}

/*
	¿É¼Ç È®ÀÎÃ¢ UI Å¬·¡½º
*/
C_VS_UI_FRINEND_OPTION_CONFIRM::C_VS_UI_FRINEND_OPTION_CONFIRM()
{
	g_RegisterWindow(this);

#ifdef __DESIGNED_CHS
	m_str_message = "ÄÚÈÝÒÑ¾­·¢Éú¸Ä±ä,Òª±£´æÂð?";
#else
	m_str_message = "content have been changed ,want to save?";
#endif		
	
	m_friend_spk = new C_SPRITE_PACK(SPK_FRIEND_COMMON);
	m_pC_button_group = new ButtonGroup(this);

	w = m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX);
	h = m_friend_spk->GetHeight(FCSI_POPUP_MESSAGE_BOX);
	x = (g_pUserInformation->iResolution_x/2)-(w/2);
	y = g_pUserInformation->iResolution_y/3;

	m_option_type = PT_SYSTEM_OPTION;

	int left_ok_button_x = (w/2)/2-(m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK)/4);
	int right_cancel_button_x = ((w/2)+((w/2)/2))-(m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK)-(m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK)/4));
	int left_ok_button_y = static_cast<int>(static_cast<float>(h)*0.6f);

	// È®ÀÎ ¹öÆ° 
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(left_ok_button_x,left_ok_button_y,
			m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK),m_friend_spk->GetHeight(FCSI_POPUP_MESSAGE_BOX_OK),
			EIOK,this,FCSI_POPUP_MESSAGE_BOX_OK));
	// Ãë¼Ò ¹öÆ°
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(right_cancel_button_x,left_ok_button_y,
			m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_CANCEL),m_friend_spk->GetHeight(FCSI_POPUP_MESSAGE_BOX_CANCEL),
			EICANCEL,this,FCSI_POPUP_MESSAGE_BOX_CANCEL));
}

C_VS_UI_FRINEND_OPTION_CONFIRM::~C_VS_UI_FRINEND_OPTION_CONFIRM()
{
	g_UnregisterWindow(this);

	if (m_friend_spk)
		DeleteNew(m_friend_spk);
	DeleteNew(m_pC_button_group);
}

void C_VS_UI_FRINEND_OPTION_CONFIRM::Start()
{
	PI_Processor::Start();
	gpC_window_manager->AppearWindow(this);
	m_pC_button_group->Init();

	EMPTY_MOVE;
}

void C_VS_UI_FRINEND_OPTION_CONFIRM::Finish()
{
	PI_Processor::Finish();
	gpC_window_manager->DisappearWindow(this);
}

void C_VS_UI_FRINEND_OPTION_CONFIRM::Show()
{
	if (!Running()) return;

	if(gpC_base->m_p_DDSurface_back->Lock())
	{
		// ¸Þ½ÃÁö ¹Ú½º
		m_friend_spk->BltLocked(x,y,FCSI_POPUP_MESSAGE_BOX);
		gpC_base->m_p_DDSurface_back->Unlock();
	}

	m_pC_button_group->Show();

	g_FL2_GetDC();
	{// ¸Þ½ÃÁö
		int message_x = x + static_cast<int>((w/2)/3.6f);
		int message_w = static_cast<int>(w*0.78f);
		int message_y = y + static_cast<int>(static_cast<float>(h)*0.3f);
		int message_h = 46;
		CRect TextBox(message_x,message_y,message_x+message_w,message_y+message_h);
		g_DrawText(TextBox,m_str_message.c_str(),&gpC_base->m_dialog_msg_pi);
	}
	g_FL2_ReleaseDC();
}

void C_VS_UI_FRINEND_OPTION_CONFIRM::Process()
{
	if (!Running()) return;

	m_pC_button_group->Process();	
}

void C_VS_UI_FRINEND_OPTION_CONFIRM::Run(id_t id)
{
	if (!Running()) return;

	switch (id)
	{
	case EIOK:		// ¿É¼Ç ¼³Á¤ È®ÀÎ ¹öÆ°
		// ÀÌ°÷¿¡¼­ ¹Ù²ï°Å¿¡ ´ëÇÑ ÆÐÅ¶À» º¸³½´Ù.
		if (m_option_type == PT_SYSTEM_OPTION)
		{
			((C_VS_UI_FRIEND_SYSTEM_OPTION*)m_parent)->SendOptionInfo();
		}
		else if (m_option_type == PT_INFO_OPTION)
		{
			((C_VS_UI_FRIEND_INFO*)m_parent)->SendOptionInfo();
		}
		gpC_base->SendMessage(UI_DESTROY,0,0,(void*)m_window_name.c_str());
		break;
	case EICANCEL:	// ¿É¼Ç Ãë¼Ò ¹öÆ°
		gpC_base->SendMessage(UI_DESTROY,0,0,(void*)m_window_name.c_str());
		break;
	}
}

bool C_VS_UI_FRINEND_OPTION_CONFIRM::MouseControl(UINT message, int _x, int _y)
{
	if (!Running()) return false;

	Window::MouseControl(message,_x,_y);
	_x -= x; _y -= y;
	bool inButton = m_pC_button_group->MouseControl(message, _x, _y);

	if (message == M_LEFTBUTTON_DOWN && inButton)
	{
		MoveReady();
		SetOrigin(_x,_y);
	}
	return true;	
}

void C_VS_UI_FRINEND_OPTION_CONFIRM::KeyboardControl(UINT message, UINT key, long extra)
{
	if (!Running()) return;

	if (message == WM_KEYDOWN)
	{
		switch (key)
		{
		case VK_RETURN:
			Run(EIOK);
			break;
		case VK_ESCAPE:
			//gpC_base->SendMessage(UI_DESTROY,0,0,(void*)m_window_name.c_str());
			break;		
		}
	}
}

void C_VS_UI_FRINEND_OPTION_CONFIRM::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{
	if (p_button->GetFocusState())
	{
		if (p_button->GetPressState())
			m_friend_spk->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+2);
		else
			m_friend_spk->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+1);
	}
	else
		m_friend_spk->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index);
}

void C_VS_UI_FRINEND_OPTION_CONFIRM::ShowButtonDescription(C_VS_UI_EVENT_BUTTON *p_button)
{

}

/*
	ÆÐÅ¶ Å×½ºÆ®¿ë ¸Þ½ÃÁö
*/
C_VS_UI_FRINEND_MESSAGE_BOX::C_VS_UI_FRINEND_MESSAGE_BOX(const char* message)
{
	g_RegisterWindow(this);
		
	m_friend_spk = new C_SPRITE_PACK(SPK_FRIEND_COMMON);
	m_pC_button_group = new ButtonGroup(this);

	m_str_message = message; 
	
	w = m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX);
	h = m_friend_spk->GetHeight(FCSI_POPUP_MESSAGE_BOX);
	x = (g_pUserInformation->iResolution_x/2)-(w/2);
	y = g_pUserInformation->iResolution_y/3;

	int ok_button_x = (w/2)-(m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK)/2);
	int ok_button_y = static_cast<int>(static_cast<float>(h)*0.5f);

	// È®ÀÎ ¹öÆ°
	m_pC_button_group->Add(new C_VS_UI_EVENT_BUTTON(ok_button_x,ok_button_y,
			m_friend_spk->GetWidth(FCSI_POPUP_MESSAGE_BOX_OK),m_friend_spk->GetHeight(FCSI_POPUP_MESSAGE_BOX_OK),
			EIOK,this,FCSI_POPUP_MESSAGE_BOX_OK));
}

C_VS_UI_FRINEND_MESSAGE_BOX::~C_VS_UI_FRINEND_MESSAGE_BOX()
{
	g_UnregisterWindow(this);

	if (m_friend_spk)
		DeleteNew(m_friend_spk);
	if (m_pC_button_group)
		DeleteNew(m_pC_button_group);
}

void C_VS_UI_FRINEND_MESSAGE_BOX::Start()
{
	PI_Processor::Start();
	gpC_window_manager->AppearWindow(this);
	m_pC_button_group->Init();

	EMPTY_MOVE;
}

void C_VS_UI_FRINEND_MESSAGE_BOX::Finish()
{
	PI_Processor::Finish();
	gpC_window_manager->DisappearWindow(this);
}

void C_VS_UI_FRINEND_MESSAGE_BOX::Show()
{
	if (!Running()) return;

	if(gpC_base->m_p_DDSurface_back->Lock())
	{
		// ¸Þ½ÃÁö ¹Ú½º
		m_friend_spk->BltLocked(x,y,FCSI_POPUP_MESSAGE_BOX);
		gpC_base->m_p_DDSurface_back->Unlock();
	}
	
	m_pC_button_group->Show();

	g_FL2_GetDC();
	{// ¸Þ½ÃÁö
		int message_x = x + static_cast<int>((w/2)/3.6f);
		int message_w = static_cast<int>(w*0.78f);
		int message_y = y + static_cast<int>(static_cast<float>(h)*0.32f);
		int message_h = 46;
		CRect TextBox(message_x,message_y,message_x+message_w,message_y+message_h);
		g_DrawText(TextBox,m_str_message.c_str(),&gpC_base->m_dialog_msg_pi);
	}
	g_FL2_ReleaseDC();
}

void C_VS_UI_FRINEND_MESSAGE_BOX::Process()
{
	if (!Running()) return;
	
	m_pC_button_group->Process();	
}


void C_VS_UI_FRINEND_MESSAGE_BOX::Run(id_t id)
{
	switch (id)
	{
	case EIOK:	// È®ÀÎ ¹öÆ°
		gpC_base->SendMessage(UI_DESTROY,0,0,(void*)m_window_name.c_str());
		break;
	}
}

bool C_VS_UI_FRINEND_MESSAGE_BOX::MouseControl(UINT message, int _x, int _y)
{
	if (!Running()) return false;

	Window::MouseControl(message,_x,_y);
	_x -= x; _y -= y;
	bool inButton = m_pC_button_group->MouseControl(message, _x, _y);

	if (message == M_LEFTBUTTON_DOWN && inButton)
	{
		MoveReady();
		SetOrigin(_x,_y);
	}
	return true;	
}

void C_VS_UI_FRINEND_MESSAGE_BOX::KeyboardControl(UINT message, UINT key, long extra)
{
	if (!Running()) return;

	if (message == WM_KEYDOWN)
	{
		switch (key)
		{
		case VK_RETURN:
			Run(EIOK);
			break;
		case VK_ESCAPE:
			//gpC_base->SendMessage(UI_DESTROY,0,0,(void*)m_window_name.c_str());
			break;		
		}
	}
}

void C_VS_UI_FRINEND_MESSAGE_BOX::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{
	if (p_button->GetFocusState())
	{
		if (p_button->GetPressState())
			m_friend_spk->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+2);
		else
			m_friend_spk->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index+1);
	}
	else
		m_friend_spk->Blt(x+p_button->x,y+p_button->y,p_button->m_image_index);
}

void C_VS_UI_FRINEND_MESSAGE_BOX::ShowButtonDescription(C_VS_UI_EVENT_BUTTON *p_button)
{

}

#endif //__FRIEND_ADDITION