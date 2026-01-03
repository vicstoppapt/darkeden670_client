/*-----------------------------------------------------------------------------

	VS_UI_progress.h

	Progress class.

	2000.6.8. KJTINC

-----------------------------------------------------------------------------*/

#ifndef __VS_UI_PROGRESS_H__
#define __VS_UI_PROGRESS_H__

#include "VS_UI_Base.h"
#include "VS_UI_util.h"
#include "VS_UI_extradialog.h"	//VS_UI_DESC를 불러오면 extradialog가 에러난다 왜그럴까-_-a
/*
enum PROGRESS_SPK_INDEX
{
	TUTORIAL_HELIPORT,
	DUNGEON_EXIT,
	SLAYER_PROGRESS_1,
	SLAYER_PROGRESS_2,	
	VAMPIRE_PROGRESS_1,
	VAMPIRE_PROGRESS_2,
	VAMPIRE_PROGRESS_3,
	BAR,
};
*/

//----------------------------------------------------------------------------
// Class Progress
//----------------------------------------------------------------------------
class C_VS_UI_PROGRESS : public Window, public C_VS_UI_DESC
{
private:
//	enum 
//	{ 
//		TOTAL_BAR_LINE = 413,//248, 
//		BAR_GAP_X = 192, //49,//44,
//		BAR_GAP_Y = 557, //558,//144,
//		BAR_COLORKEY = 0xFF,

		//VAMPIRE_RAND_MAX = 6, // progress_vampire_rand.spk + original vampire back image
//	};

	enum PROGRESS_RESOLUTION
	{
		RESOLUTION_800_600,
		RESOLUTION_1024_768,
		RESOLUTION_1280_720,
		RESOLUTION_1280_960,
		RESOLUTION_1280_1024,
	};

	enum PROGRESS_TYPE
	{
		TYPE_MONSTER_INFO,
		TYPE_EVENT,	
		TYPE_PPL,
		TYPE_MAX
	};

	enum PROGRESS_MONSTER_INFO
	{
		BACK,
		CHAR_NAME_ALPHA,
		CHAR_NAME_BACK,
		PROGRESS_BAR,
		PROGRESS_ICON,
	};

	enum PROGRESS_EVENT
	{
		EVENT_OUSTERS,
		EVENT_REVENGE_OF_THE_MASTERS,
		EVENT_REVENGE_OF_THE_MASTERS_2,
		EVENT_SLAYER_2005,
		EVENT_VAMPIRE_2005,
		EVENT_OUSTERS_2005,
		EVENT_MAXX = 8,//modify by hays
	};

	enum PROGRESS_PPL
	{
		PPL_IVY_CLUB,
	};

	enum PROGRESS_CI
	{
		CI_DARKEDEN,
		CI_IVY_CLUB,
		CI_MAX
	};

#if __CONTENTS(__TIPOJYU_CASTLE)
	enum PROGRESS_EVENT_TIPOJYU
	{
		PROGREES_LIFE_IMAGE		= 6,			//현세 이미지	(이미지를 그리는 부분에서 *2해준다.) 그러므로 인덱스의 반값
		PROGREES_HADES_IMAGE	= 7,			//과거 이미지
	};

	WORD				m_wZoneID;
#endif // __TIPOJYU_CASTLE
	
	int					m_progress_type;

	C_SPRITE_PACK *		m_pC_event_progress;
	C_SPRITE_PACK *		m_pC_ppl;
	C_SPRITE_PACK *		m_pC_ci;

	CSpritePack *		m_pC_progress;
	CSpritePack	*		m_pC_character;

	WORD				m_percent;
	int					m_Draw_Num;

	std::string			m_world_name;
	std::string			m_server_name;
	int					m_server_status;

public:
	C_VS_UI_PROGRESS();
	~C_VS_UI_PROGRESS();

	void	InitMonsterInfoProgress();
	void	InitEventProgress();
	void	InitPPLProgress();

	void	WindowEventReceiver(id_t event);
	bool	IsPixel(int _x, int _y);

	void	Start();
	void	Finish();
	void	Show();
	void	SetProgress(WORD cur_val, WORD max_val);
	void	AcquireDisappear() {}

#if __CONTENTS(__TIPOJYU_CASTLE)
	void	SetZoneID(WORD wZoneID);
	WORD	GetZoneID() { return m_wZoneID;}
	BOOL	LoadingSleep();
#endif // __TIPOJYU_CASTLE
	void	SetServerName(const char *world_name, const char *server_name, int status)
	{
		if(world_name)
			m_world_name = world_name;
		else
			m_world_name = "";
		
		if(server_name)
			m_server_name = server_name;
		else 
			m_server_name = "";
		
		m_server_status = status; 
	}

	const char*	GetServerName() { return m_server_name.c_str(); }
	const char*	GetWorldName() { return m_world_name.c_str(); }
	int GetServerStatus() { return m_server_status; }

	//
	// !gC_vs_ui.StartProgress() 후에 설정한다.
	//
//	void	SetProgressStyle(PROGRESS_SPK_INDEX style);
};

#endif