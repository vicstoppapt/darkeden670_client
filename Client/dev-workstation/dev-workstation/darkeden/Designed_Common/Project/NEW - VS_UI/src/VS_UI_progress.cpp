#include "client_PCH.h"

#include "VS_UI_progress.h"
#include "VS_UI_filepath.h"
#include "VS_UI_description.h"
#include "UserInformation.h"
#include "VS_UI.h"
#include <time.h>

#include "MGameStringTable.H"
#include "VS_UI_GPS.H"

#define PROGRESS_MAX 25


//-----------------------------------------------------------------------------
// C_VS_UI_PROGRESS
//
// 
//-----------------------------------------------------------------------------
C_VS_UI_PROGRESS::C_VS_UI_PROGRESS()
{
	g_RegisterWindow(this);

	AttrTopmost(true);

	srand(time(0));

	m_pC_progress = NULL;
	m_pC_event_progress = NULL;
	m_pC_character = NULL;
	m_pC_ppl = NULL;
	m_pC_ci = NULL;

	// 넷마블은 게임내 광고 안함
//	if(g_pUserInformation->IsNetmarble ||
//	   g_pUserInformation->IsTestServer)
//	{
		InitEventProgress();

		/* 몬스터 로딩화면은 이제 그만~ chyaya
		if(rand() % 2)
		{
			InitEventProgress();
		}
		else
		{
			InitMonsterInfoProgress();
		}
		*/
//	}
//	else
//	{
//		if(rand() % 2)
//		{
//			InitPPLProgress();
//		}
//		else
//		{
//			InitEventProgress();

			/* 몬스터 로딩화면은 이제 그만~ chyaya
			if(rand() % 2)
			{
				InitEventProgress();
			}
			else
			{
				InitMonsterInfoProgress();
			}
			*/

//			m_pC_ci = new C_SPRITE_PACK(SPK_PROGRESS_CI);
//		}
//	}
	

	m_world_name = "";
	m_server_name = "";
	m_server_status = C_VS_UI_SERVER_SELECT::STATUS_DOWN;

#if __CONTENTS(__TIPOJYU_CASTLE)
	m_wZoneID		= 0;
#endif //  __TIPOJYU_CASTLE
}

//-----------------------------------------------------------------------------
// ~C_VS_UI_PROGRESS
//
// 
//-----------------------------------------------------------------------------
C_VS_UI_PROGRESS::~C_VS_UI_PROGRESS()
{
	g_UnregisterWindow(this);

	if(m_pC_event_progress != NULL)
		DeleteNew(m_pC_event_progress);

	if(m_pC_progress != NULL)
		DeleteNew(m_pC_progress);
	
	if(m_pC_character != NULL)
		DeleteNew(m_pC_character);

	if(m_pC_ci != NULL)
		DeleteNew(m_pC_ci);

	if(m_pC_ppl != NULL)
		DeleteNew(m_pC_ppl);

//	DeleteNewArray(m_p_bar_buf);
}

//-----------------------------------------------------------------------------
// C_VS_UI_PROGRESS::SetProgressStyle
//
// 
//-----------------------------------------------------------------------------
//void	C_VS_UI_PROGRESS::SetProgressStyle(PROGRESS_SPK_INDEX style)
//{
//	if (style >= BAR)
//	{
//		style = SLAYER_PROGRESS_1;
//	}

//	m_progress_back_image = style; 

	/*
	if (m_progress_back_image == VAMPIRE_PROGRESS)
	{
		int index = rand()%VAMPIRE_RAND_MAX;
		if (index > 0)
		{
			DeleteNew(m_pC_progress);
			m_pC_progress = new C_SPRITE_PACK(SPK_PROGRESS_VAMPIRE_RAND);

			m_progress_back_image = index-1;
		}
	}
	*/
//}

//-----------------------------------------------------------------------------
// InitMonsterInfoProgress
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_PROGRESS::InitMonsterInfoProgress()
{
	m_progress_type = TYPE_MONSTER_INFO;

	static bool Check[PROGRESS_MAX];
	static int	CheckNum = 0;
	int num, i;
	
	for(i = 0; i < PROGRESS_MAX; i++)
		Check[i] = false;
	
	CheckNum = PROGRESS_MAX;
	
	if(g_pUserInformation->GoreLevel == false)
	{
		// 틴버전 하드코딩
		Check[4] = true;
		Check[9] = true;
		Check[11] = true;
		Check[13] = true;
		Check[14] = true;
		Check[15] = true;
		Check[21] = true;
		Check[22] = true;
		Check[23] = true;
		
		CheckNum -= 9;
	}
	
	num = rand() % CheckNum;
	
	for(i = 0; i <= num; i++)
	{
		if(Check[i] == true)num++;
	}
	
	Check[num] = true;
	CheckNum--;
	
	
	m_pC_progress = new CSpritePack;

	bool bHighResolution = g_pUserInformation->iResolution_x > 800;	
	
	if(!bHighResolution)
		m_pC_progress->LoadFromFile(SPK_PROGRESS);
	else
		m_pC_progress->LoadFromFile(SPK_PROGRESS_1024);
	
	m_pC_character = new CSpritePack;
	
	m_pC_character->Init(2);
	m_pC_character->LoadFromFileData(0, num*2, SPK_PROGRESS_CHARACTER, SPKI_PROGRESS_CHARACTER);
	m_pC_character->LoadFromFileData(1, num*2+1, SPK_PROGRESS_CHARACTER, SPKI_PROGRESS_CHARACTER);
	
	m_pack_file.SetRAR(RPK_PROGRESS, RPK_PASSWORD);
	
	PrintInfo pi, title_pi;
	COLORREF color, title_color;
	
	title_pi = gpC_base->m_char_value_pi;
	title_color = RGB(178,140,121);
	pi = gpC_base->m_char_name_pi;
	color = RGB(200,200,200);
	
	static char *Monster[PROGRESS_MAX] =
	{
		(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_TNDEAD].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_ARKHAN].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_ESTROIDER].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_GOLEMER].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_DARKSCREAMER].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_DEADBODY].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_MODERAS].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_VANDALIZER].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_DIRTYSTRIDER].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_HELLWIZARD].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_TNSOUL].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_IRONTEETH].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_REDEYE].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_CRIMSONSLAUGTHER].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_HELLGUARDIAN].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_SOLDIER].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_RIPPER].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_BIGFANG].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_LORDCHAOS].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_CHAOSGUARDIAN].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_HOBBLE].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_CHAOSNIGHT].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_WIDOWS].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_KID].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_NAME_SHADOWWING].GetString(),
	};
	
	static char *MonsterFilename[PROGRESS_MAX] =
	{
		(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_TNDEAD].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_ARKHAN].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_ESTROIDER].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_GOLEMER].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_DARKSCREAMER].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_DEADBODY].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_MODERAS].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_VANDALIZER].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_DIRTYSTRIDER].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_HELLWIZARD].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_TNSOUL].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_IRONTEETH].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_REDEYE].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_CRIMSONSLAUGTHER].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_HELLGUARDIAN].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_SOLDIER].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_RIPPER].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_BIGFANG].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_LORDCHAOS].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_CHAOSGUARDIAN].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_HOBBLE].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_CHAOSNIGHT].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_WIDOWS].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_KID].GetString(),
			(*g_pGameStringTable)[UI_STRING_MESSAGE_MONSTER_ENAME_SHADOWWING].GetString(),
	};
	
	std::string filename = MonsterFilename[num];
	filename += ".txt";
	LoadDesc(filename.c_str(), 43, 50, false);

	int convx = (g_pUserInformation->iResolution_x - 800) / 2;
	int convy = (g_pUserInformation->iResolution_y - 600) / 2;
	
	SetDesc(convx + 400, convy + 150, color, pi);
	SetDescTitle(convx + 400, convy + 120, title_color, title_pi);
	SetDescTitle(Monster[num]);
	Set(g_pUserInformation->iResolution_x/2 - (*m_pC_progress)[BACK].GetWidth()/2 ,
		g_pUserInformation->iResolution_y/2 - (*m_pC_progress)[BACK].GetHeight()/2 ,
		(*m_pC_progress)[BACK].GetWidth(), (*m_pC_progress)[BACK].GetHeight());

}



//-----------------------------------------------------------------------------
// InitMonsterInfoProgress
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_PROGRESS::InitEventProgress()
{
	m_progress_type = TYPE_EVENT;

	m_Draw_Num = 0;
	int iEventStartID = 0 ; int iEventCount = 0; 

// 	if(bHighResolution)
// 		m_pC_event_progress = new C_SPRITE_PACK(SPK_PROGRESS_EVENT_1024);
// 	else
// 		m_pC_event_progress = new C_SPRITE_PACK(SPK_PROGRESS_EVENT);
// 
// 	do{
// 		m_Draw_Num = (rand() % (m_pC_event_progress->GetSize() - 4)) / 2; // -4는 티포쥬 로딩 이미지 개수.
// 	}while(m_Draw_Num == EVENT_REVENGE_OF_THE_MASTERS ||
// 			m_Draw_Num == EVENT_REVENGE_OF_THE_MASTERS_2);		// 피 나오는거 그냥 빼기로 했다.

	m_pC_event_progress = new C_SPRITE_PACK(SPK_PROGRESS_EVENT);

	do 
	{
		m_Draw_Num = (rand() % (EVENT_MAXX*2 - 4));	// 총 로딩 이미지 개수 - 티포쥬 로딩 이미지 개수.
	} while(m_Draw_Num % 2 == 1);

	bool bHighResolution = g_pUserInformation->iResolution_x > 800;

	if(bHighResolution)
	{
		if(g_pUserInformation->iResolution_x <= 1024)
			m_Draw_Num = m_Draw_Num + EVENT_MAXX*2*RESOLUTION_1024_768;
		else // if(g_pUserInformation->iResolution_x > 1024)
		{
			if(g_pUserInformation->iResolution_y < 960)
				m_Draw_Num = m_Draw_Num + EVENT_MAXX*2*RESOLUTION_1280_720;
			else if(g_pUserInformation->iResolution_y < 1024)
				m_Draw_Num = m_Draw_Num + EVENT_MAXX*2*RESOLUTION_1280_960;
			else
				m_Draw_Num = m_Draw_Num + EVENT_MAXX*2*RESOLUTION_1280_1024;
		}
	}

// 	//while(	!g_pUserInformation->GoreLevel   && 
// 	//		( m_Event_Num == 1 || m_Event_Num == 2 ) ); // 틴버전을 사용하는데 피가 나오면 다시 뽑는다.
	
	Set(0, 0, m_pC_event_progress->GetWidth(), m_pC_event_progress->GetHeight());
}

#if __CONTENTS(__TIPOJYU_CASTLE)
void	C_VS_UI_PROGRESS::SetZoneID(WORD wZoneID)
{
	m_wZoneID = wZoneID;

	bool bHighResolution = g_pUserInformation->iResolution_x > 800;
	
	switch(m_wZoneID)
	{
	case 1801:	case 1803:
		{
			m_Draw_Num	= PROGREES_LIFE_IMAGE;
			
			if(bHighResolution)
			{
				if(g_pUserInformation->iResolution_x <= 1024)
					m_Draw_Num = m_Draw_Num + EVENT_MAXX*2*RESOLUTION_1024_768;
				else // if(g_pUserInformation->iResolution_x > 1024)
				{
					if(g_pUserInformation->iResolution_y < 960)
						m_Draw_Num = m_Draw_Num + EVENT_MAXX*2*RESOLUTION_1280_720;
					else if(g_pUserInformation->iResolution_y < 1024)
						m_Draw_Num = m_Draw_Num + EVENT_MAXX*2*RESOLUTION_1280_960;
					else
						m_Draw_Num = m_Draw_Num + EVENT_MAXX*2*RESOLUTION_1280_1024;
				}
			}
			break;
		}
		
	
	case 1802:	case 1804:
		{
			m_Draw_Num	= PROGREES_HADES_IMAGE;

			if(bHighResolution)
			{
				if(g_pUserInformation->iResolution_x <= 1024)
					m_Draw_Num = m_Draw_Num + EVENT_MAXX*2*RESOLUTION_1024_768;
				else // if(g_pUserInformation->iResolution_x > 1024)
				{
					if(g_pUserInformation->iResolution_y < 960)
						m_Draw_Num = m_Draw_Num + EVENT_MAXX*2*RESOLUTION_1280_720;
					else if(g_pUserInformation->iResolution_y < 1024)
						m_Draw_Num = m_Draw_Num + EVENT_MAXX*2*RESOLUTION_1280_960;
					else
						m_Draw_Num = m_Draw_Num + EVENT_MAXX*2*RESOLUTION_1280_1024;
				}
			}
			break;
		}
	}
}


BOOL	C_VS_UI_PROGRESS::LoadingSleep()
{
	switch(m_wZoneID)
	{
		case 1801:
		case 1803:
		case 1802:
		case 1804:
			return TRUE;
		default:
			return FALSE;
	}
}

#endif // __TIPOJYU_CASTLE

//-----------------------------------------------------------------------------
// InitPPLProgress
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_PROGRESS::InitPPLProgress()
{
	m_progress_type = TYPE_PPL;

	bool bHighResolution = g_pUserInformation->iResolution_x > 800;
	
	if(bHighResolution)
		m_pC_ppl = new C_SPRITE_PACK(SPK_PROGRESS_PPL_1024);
	else
		m_pC_ppl = new C_SPRITE_PACK(SPK_PROGRESS_PPL);
	
	m_Draw_Num = rand() % (m_pC_ppl->GetSize() / 2);

	Set(0, 0, m_pC_ppl->GetWidth(), m_pC_ppl->GetHeight());
}


//-----------------------------------------------------------------------------
// IsPixel
//
// 
//-----------------------------------------------------------------------------
bool C_VS_UI_PROGRESS::IsPixel(int _x, int _y)
{
//	return m_pC_progress->IsPixel(SCR2WIN_X(_x), SCR2WIN_Y(_y), SLAYER_PROGRESS_1);
	return true;//(*m_pC_progress)[BACK].IsColorPixel(SCR2WIN_X(_x), SCR2WIN_Y(_y));
}

//-----------------------------------------------------------------------------
// WindowEventReceiver
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_PROGRESS::WindowEventReceiver(id_t event)
{

}

//-----------------------------------------------------------------------------
// Start
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_PROGRESS::Start()
{
	PI_Processor::Start();

	gpC_window_manager->AppearWindow(this);

	m_world_name = "";
	m_server_name = "";
	m_server_status = C_VS_UI_SERVER_SELECT::STATUS_DOWN;


//	m_cur_line = 0;
	m_percent = 0;
//	m_progress_back_image = SLAYER_PROGRESS_1;

	g_descriptor_manager.Unset();
}

//-----------------------------------------------------------------------------
// Finish
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_PROGRESS::Finish()
{
	PI_Processor::Finish();

	gpC_window_manager->DisappearWindow(this);
}

//-----------------------------------------------------------------------------
// SetProgress
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_PROGRESS::SetProgress(WORD cur_val, WORD max_val)
{
	if (max_val == 0 || cur_val > max_val)
		return;

	if (max_val > 0)
	{
		float f = cur_val / (float)max_val;

		m_percent = (WORD)(f*100);

//		f = (m_percent / 100.) * TOTAL_BAR_LINE;

//		WORD n = f;
//		float t = n;
//		float r = f - t;
//		if (r > 0.)
//			n += 1; // 반올림.
//
//		if (m_percent < 100 && n >= TOTAL_BAR_LINE)
//			n = TOTAL_BAR_LINE - 1;
//
//		m_cur_line = n;
	}
}

//-----------------------------------------------------------------------------
// DrawBar (Based on Vampire Energy interface)
//
//
//-----------------------------------------------------------------------------
/*
void C_VS_UI_PROGRESS::DrawBar()
{
	if (m_cur_line < 1 || m_cur_line > TOTAL_BAR_LINE)
		return;

	if (gpC_base->m_p_DDSurface_back->Lock())
	{
		S_SURFACEINFO	src_surface, dest_surface;
		S_RECT			src_rect, dest_rect;
		SetSurfaceInfo(&dest_surface, gpC_base->m_p_DDSurface_back->GetDDSD());
		SetSurfaceInfo(src_surface, m_p_bar_buf, m_bar_width, m_bar_height);
		SetRect(src_rect, 0, 0, m_cur_line, m_bar_height);
		SetRect(dest_rect, x+BAR_GAP_X, y+BAR_GAP_Y, m_cur_line, m_bar_height);

		CkBltz(&dest_surface, &src_surface, &dest_rect, &src_rect, BAR_COLORKEY);

		gpC_base->m_p_DDSurface_back->Unlock();
	}
}
*/

//-----------------------------------------------------------------------------
// Show
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_PROGRESS::Show()
{
#if __CONTENTS(__MOVE_ZONE)
	if(gpC_mouse_pointer->IsMoveZoneEffect())
	{
		string namecc  = "존이동 중입니다.";
		
		for(int i=-1; i<=1; i++)
		for(int j=-1; j<=1; j++)
		{
			g_PrintColorStr(g_pUserInformation->iResolution_x / 2 - g_GetStringWidth(namecc.c_str(), gpC_base->m_dialog_menu_pi.hfont)/2+i,
			(int)(g_pUserInformation->iResolution_y * 0.70f)+j, namecc.c_str(), gpC_base->m_desc_menu_pi, RGB(165,0,0));
		}
		
		g_PrintColorStr(g_pUserInformation->iResolution_x / 2 - g_GetStringWidth(namecc.c_str(), gpC_base->m_dialog_menu_pi.hfont)/2,
			(int)(g_pUserInformation->iResolution_y * 0.70f), namecc.c_str(), gpC_base->m_desc_menu_pi, RGB(0,0,0));

		return;
	}
#endif //__MOVE_ZONE

	gpC_base->m_p_DDSurface_back->FillSurface(0);
	
	POINT p = {0, 0};
	

	if(gpC_base->m_p_DDSurface_back->Lock())
	{
		if(m_progress_type == TYPE_PPL)
		{
			Rect rect;

			m_pC_ppl->BltLocked(0, 0, (m_Draw_Num*2));

			rect.Set(0, m_pC_ppl->GetHeight(m_Draw_Num)*(100-m_percent)/100,
				m_pC_ppl->GetWidth(m_Draw_Num), m_pC_ppl->GetHeight(m_Draw_Num)*(m_percent)/100);

			m_pC_ppl->BltLockedClip(0, 0, rect, (m_Draw_Num*2)+1);
		}
		else
		{
			if(m_progress_type == TYPE_EVENT)
			{
				Rect rect;

				m_pC_event_progress->BltLocked(0, 0, m_Draw_Num);
				
				rect.Set(0, m_pC_event_progress->GetHeight(m_Draw_Num)*(100-m_percent)/100,
					m_pC_event_progress->GetWidth(m_Draw_Num), m_pC_event_progress->GetHeight(m_Draw_Num)*(m_percent)/100);
				
				m_pC_event_progress->BltLockedClip(0, 0, rect, m_Draw_Num+1);
				
//				Sleep(500); // 스핵 테스트를 위해 잠시 열어논 코드 배포 할때는 반드시 처리 안되게 해야 하는 코드 이다. 2008.09.09 - shootkj
				
#if __CONTENTS(__TIPOJYU_CASTLE)
				if(LoadingSleep())
					Sleep(250);
#endif
			}
			else
			{
				int convx = (g_pUserInformation->iResolution_x - 800) / 2;
				int convy = (g_pUserInformation->iResolution_y - 600) / 2;

				//BACK찍기
				gpC_base->m_p_DDSurface_back->BltSprite(&p, &(*m_pC_progress)[BACK]);

				p.x = convx + 200 - (*m_pC_character)[0].GetWidth()/2;
				p.y = convy + 300 - (*m_pC_character)[0].GetHeight()/2;
			
				//캐릭터 찍기
				gpC_base->m_p_DDSurface_back->s_Value1 = m_percent*32/100; 	// 0이면 완전 gray, 32이면 원래색깔
				
				gpC_base->m_p_DDSurface_back->SetEffect( CSpriteSurface::EFFECT_GRAY_SCALE );//EFFECT_NET);//
				
				
				Rect rect;
				RECT rt;
				S_SURFACEINFO surface_info;
				SetSurfaceInfo(&surface_info, gpC_base->m_p_DDSurface_back->GetDDSD());
				
				rect.Set(0, 0, (*m_pC_character)[0].GetWidth(), (*m_pC_character)[0].GetHeight()*(100-m_percent)/100);
				rt.left = max(-p.x, rect.x);
				rt.top = max(-p.y, rect.y);

				rt.right = min(rect.x+rect.w, g_pUserInformation->iResolution_x-p.x);
				rt.bottom = min(rect.y+rect.h, g_pUserInformation->iResolution_y-p.y);
				
				if(rt.left < rt.right && rt.top < rt.bottom)
				{
					WORD * p_dest = (WORD *)surface_info.p_surface+p.x+rt.left;
					p_dest = (WORD *)((BYTE *)p_dest+(p.y+rt.top)*surface_info.pitch);
					
					(*m_pC_character)[0].BltEffectClipHeight(p_dest, surface_info.pitch, &rt);
				}
				
				SetRect((RECT *)&rect, 0, (*m_pC_character)[0].GetHeight()*(100-m_percent)/100, (*m_pC_character)[0].GetWidth(), (*m_pC_character)[0].GetHeight() - (*m_pC_character)[0].GetHeight()*(100-m_percent)/100);
				rt.left = max(-p.x, rect.x);
				rt.top = max(-p.y, rect.y);

				rt.right = min(rect.x+rect.w, g_pUserInformation->iResolution_x-p.x);
				rt.bottom = min(rect.y+rect.h, g_pUserInformation->iResolution_y-p.y);
								
				if(rt.left < rt.right && rt.top < rt.bottom)
				{
					
					WORD * p_dest = (WORD *)surface_info.p_surface+p.x+rt.left;
					p_dest = (WORD *)((BYTE *)p_dest+(p.y+rt.top)*surface_info.pitch);
					
					(*m_pC_character)[0].BltClipHeight(p_dest, surface_info.pitch, &rt);
				}

				p.x = convx + 200 - (*m_pC_progress)[PROGRESS_BAR].GetWidth()/2;
				p.y += (*m_pC_character)[0].GetHeight()*(100-m_percent)/100-(*m_pC_progress)[PROGRESS_BAR].GetHeight()/2;
				
				
				gpC_base->m_p_DDSurface_back->SetEffect( CSpriteSurface::EFFECT_SCREEN );
				gpC_base->m_p_DDSurface_back->BltSpriteEffect(&p, &(*m_pC_progress)[PROGRESS_BAR]);
				
				p.x = g_pUserInformation->iResolution_x - (*m_pC_progress)[CHAR_NAME_BACK].GetWidth()-10;
				p.y = g_pUserInformation->iResolution_y - (*m_pC_progress)[CHAR_NAME_BACK].GetHeight()-45;
				
				//캐릭터이름찍기(하단큰거)
				
				gpC_base->m_p_DDSurface_back->SetEffect( CSpriteSurface::EFFECT_GRAY_SCALE_VARIOUS );
				gpC_base->m_p_DDSurface_back->BltSpriteEffect(&p, &(*m_pC_progress)[CHAR_NAME_BACK]);
				
				p.x = g_pUserInformation->iResolution_x - (*m_pC_progress)[CHAR_NAME_BACK].GetWidth()/2 -(*m_pC_character)[1].GetWidth()/2-10;
				p.y = g_pUserInformation->iResolution_y - (*m_pC_progress)[CHAR_NAME_BACK].GetHeight()/2 -(*m_pC_character)[1].GetHeight()/2-25;
				
				gpC_base->m_p_DDSurface_back->BltSprite(&p, &(*m_pC_character)[1]);
			}

			// 본섭인 경우 PPL 회사 CI를 출력한다.
			if(m_pC_ci)
			{
				const int ci_gap	= 15;
				const int ci_y		= h - m_pC_ci->GetHeight() - ci_gap;

				m_pC_ci->BltLocked(ci_gap, ci_y, CI_IVY_CLUB);
				m_pC_ci->BltLocked(w - m_pC_ci->GetWidth(CI_DARKEDEN) - ci_gap, ci_y, CI_DARKEDEN);
			}
		}
	
		gpC_base->m_p_DDSurface_back->Unlock();
	}

	//현재 서버이름 표시
	COLORREF focus_color;
	focus_color = RGB_BLACK;
	if(m_pC_event_progress != NULL)
		focus_color = RGB_WHITE;
	
	std::string name = GetWorldName();
	name += " - ";
	name += GetServerName();
	name += " (";

	
	switch(GetServerStatus())
	{
	case C_VS_UI_SERVER_SELECT::STATUS_VERY_GOOD:
		name +=(*g_pGameStringTable)[UI_STRING_MESSAGE_SERVER_STATUS_VERY_GOOD].GetString();
		break;
		
	case C_VS_UI_SERVER_SELECT::STATUS_GOOD:
		name +=(*g_pGameStringTable)[UI_STRING_MESSAGE_SERVER_STATUS_GOOD].GetString();
		break;
		
	case C_VS_UI_SERVER_SELECT::STATUS_NORMAL:
		name +=(*g_pGameStringTable)[UI_STRING_MESSAGE_SERVER_STATUS_NORMAL].GetString();
		break;
		
	case C_VS_UI_SERVER_SELECT::STATUS_BAD:
		name +=(*g_pGameStringTable)[UI_STRING_MESSAGE_SERVER_STATUS_BAD].GetString();
		break;
		
	case C_VS_UI_SERVER_SELECT::STATUS_VERY_BAD:
		name += (*g_pGameStringTable)[UI_STRING_MESSAGE_SERVER_STATUS_VERY_BAD].GetString();
		break;
		
	case C_VS_UI_SERVER_SELECT::STATUS_DOWN:
		name += (*g_pGameStringTable)[UI_STRING_MESSAGE_SERVER_STATUS_DOWN].GetString();
		break;
	}
	name += ")";
	
	g_PrintColorStr(g_pUserInformation->iResolution_x / 2 - g_GetStringWidth(name.c_str(), gpC_base->m_dialog_menu_pi.hfont)/2,
		(int)(g_pUserInformation->iResolution_y * 0.95f), name.c_str(), gpC_base->m_desc_menu_pi, focus_color);//by larosel

	if(m_progress_type == TYPE_MONSTER_INFO)
	{
		ShowDesc(x, y);
		p.x = m_desc_title_x + g_GetStringWidth(m_desc_title.c_str())/2 - (*m_pC_progress)[CHAR_NAME_ALPHA].GetWidth()/2;

		//캐릭터 이름위에 알파
		if(gpC_base->m_p_DDSurface_back->Lock())
		{
			p.y = m_desc_title_y-4;
			gpC_base->m_p_DDSurface_back->SetEffect( CSpriteSurface::EFFECT_SCREEN );
			gpC_base->m_p_DDSurface_back->BltSpriteEffect(&p, &(*m_pC_progress)[CHAR_NAME_ALPHA]);
			
			gpC_base->m_p_DDSurface_back->Unlock();
		}
	}

//	DrawBar();

	// percent 출력
#ifndef _LIB
//	char str[5];
//	sprintf(str, "%d%%", m_percent);
//	g_Print(380, 500, str);
#endif

}
