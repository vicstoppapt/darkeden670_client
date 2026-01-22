/*-----------------------------------------------------------------------------

	VS_UI_Title.h

	VS User Interface Title.

	Title Object Components:
										Login
										New User
										Character Manager:
																	New character creation:
																							Appearance
																	Character info:
																							Character delete

	2000.8.9. KJTINC

-----------------------------------------------------------------------------*/

#ifndef __VS_UI_TITLE_H__
#define __VS_UI_TITLE_H__

#include "VS_UI_Base.h"
#include "VS_UI_Util.h"
#include "VS_UI_Widget.h"
#include "VS_UI_Dialog.h"
#include "VS_UI_DESC.h"
#include <vector>

#if __CONTENTS(__TITLE_UI_RENWEAL)

class CTickTimer;
class C_VS_UI_ASK_DIALOG ; 

enum MAIN_SPK_INDEX // C_VS_UI_NEWCHAR 에서도 사용하므로...
{
	MAIN,
	HEART_LEFT,
	HEART_CENTER,
	HEART_RIGHT,
	HEART_LEFT_HIGHLIGHT,
	HEART_CENTER_HIGHLIGHT,
	HEART_RIGHT_HIGHLIGHT,
	NAME_BOARD,
};

enum
{
	TOTAL_ENERGY_LINE = 109,
};

// character ani
enum
{
	ANI_MILLISEC = 100, 
};

// 3차의상까지의 스프라이트 팩 크기
#define ORIGIN3RD_COAT_SPRITEPACK_SIZE	50

//
// character 생성시 character part...
// CFPK 순서
//
enum CHAR_MAN
{
	M_SWORD,
	M_BLADE,

	M_SR,
	M_AR,
	M_SG,
	M_SMG,

	M_CROSS,
	M_MACE,

	M_SHIELD1,
	M_SHIELD2,

	M_HAIR1,
	M_HAIR2,
	M_HAIR3,

	M_MOTOR,

	M_HELMET1,
	M_HELMET2,
	M_HELMET3,

	M_COAT1,
	M_TROUSER1,

	M_COAT2,
	M_TROUSER2,

	M_COAT3,
	M_TROUSER3,

	M_COAT4,
	M_TROUSER4,
	
	M_FACE1,
	M_FACE2,
	M_FACE3,

	M_NO_WEAR,
};

struct MAN_INFO
{
	CHAR_MAN		face;
	CHAR_MAN		hair;
	CHAR_MAN		helmet;
	CHAR_MAN		coat;
	CHAR_MAN		trouser;
	CHAR_MAN		right; // 무기
	CHAR_MAN		left;  // 방어구
};

enum ALIGNMENT
{
	UI_EVIL_PLUS,
	UI_EVIL,
	UI_NEUTRAL,
	UI_GOOD,
	UI_GOOD_PLUS,
};

// character creation slot
struct S_SLOT
{
	S_SLOT() { m_AdvancementLevel = 0; }
	void Init();

	bool								bl_set; // slot이 설정되었는가?
//	bool								bl_vampire;
	bool								bl_female;
	bool								bl_drained; //흡혈된 상태인가?
	MAN_INFO							man_info;
	
	int									helmet_color;
	int									trouser_color;
	int									coat_color;
	int									skin_color;
	int									hair_color;
	int									left_color;
	int									right_color;

	std::string							sz_name;
	std::string							sz_guild_name;
	ALIGNMENT							alignment;
	int									alignment_num;
	int									level;		// vampire only
	int									STR_PURE;	// by larosel
	int									STR_CUR;	// by larosel
	int									STR_MAX;	// by larosel
	int									DEX_PURE;	// by larosel
	int									DEX_CUR;	// by larosel
	int									DEX_MAX;	// by larosel
	int									INT_PURE;	// by larosel
	int									INT_CUR;	// by larosel
	int									INT_MAXX;	// by larosel	//INT_MAX 는 못씀
	int									STR_EXP_REMAIN;
	int									DEX_EXP_REMAIN;
	int									INT_EXP_REMAIN;
	int									EXP_REMAIN;		// vampire only
	int									DAM;			// max
	int									DAM2;			// min
	int									SILVER_DAM;		//max
	int									SILVER_DAM2;	//min
	int									CHANGE_VAMPIRE;	// 뱀파이어로 변하는 남은 시간 분
//	int									AC;
	int									DEFENSE;	// by larosel
	int									PROTECTION;	// by larosel
	int									TOHIT;
	int									HP;
	int									MP;
	int									HP_MAX;
	int									MP_MAX;
	int									SILVER_HP;

	int									DOMAIN_SWORD;
	int									DOMAIN_BLADE;
	int									DOMAIN_GUN;
	int									DOMAIN_HEAL;
	int									DOMAIN_ENCHANT;

//	int									CC;
	int									FAME;		// slayer only
//	int									NOTERITY;
	int									bonus_point; // vampire only
	int									skill_point; // ousters only

	WORD								AttackBloodBurstPoint;
	WORD								DefenseBloodBurstPoint;
	WORD								PartyBloodBurstPoint;
	int									MagicRemainSec ; 
	DWORD								MagicRemainTick ; 

	WORD								SlayerAdvancedStr;
	WORD								SlayerAdvancedDex;
	WORD								SlayerAdvancedInt;

	int									luck;
	int									hpsteal;
	int									mpsteal;
	int									allres;
	int									vision;
	int									cri;

#if __CONTENTS(__CONTRIBUTE_SYSTEM)
	int									ContributePoint;
#endif //__CONTRIBUTE_SYSTEM

#if __CONTENTS(__JAPAN_REVERSE_DEVELOP || __EXPERT_PET_CHANGER)
	bool								bExpertPetUse;
#endif //__JAPAN_REVERSE_DEVELOP

	

	struct UI_EFFECTSTATUS_STRUCT
	{
		TYPE_ACTIONINFO actionInfo;
		DWORD			delay100msec;
	};

	typedef std::vector<UI_EFFECTSTATUS_STRUCT>			UI_EFFECTSTATUS_TYPE;
	UI_EFFECTSTATUS_TYPE				STATUS;	
	
	// Vampire일 경우 mp는 무시한다.
//	WORD									hp_cur_line;
//	WORD									mp_cur_line;	// slayer only
//	WORD									hp_percent;
//	WORD									mp_percent;		// slayer only

	WORD								GUILD_ID;
	BYTE								GUILD_GRADE;

	BYTE								WS;
	BYTE								WeaponSpeed;
	int									GRADE;
	int									GRADE_EXP_REMAIN;

	Race								Race;
	
	int									ElementalFire;
	int									ElementalWater;
	int									ElementalEarth;
	int									ElementalWind;
	
	int									m_SMS_Charge;
	int									m_Powerjjang_Point;
	int									m_AdvancementLevel;	// 전직 레벨 
//	BYTE								m_NickNameType;
//	std::string							m_NickName;
};	

//-----------------------------------------------------------------------------
// C_VS_UI_LOGIN
//
// 
//-----------------------------------------------------------------------------
class C_VS_UI_LOGIN : public Window, public Exec, public ButtonVisual
{
private:
	enum 
	{
		NEW_ID,
		OK,
		CANCEL,
		PUSHED_NEW_ID,
		PUSHED_OK,
		PUSHED_CANCEL,
	};

	//enum INPUT_POSITION // 입력 위치
	//{
	//	ID,
	//	PASSWORD,
	//};

	enum { SHADOW = 1 };

	C_SPRITE_PACK *				m_pC_login_spk;
//	C_SPRITE_PACK				m_pC_login_menu_default;
	C_SPRITE_PACK				m_pC_login_menu;

	ButtonGroup *				m_pC_button_group;

	//
	// string line buffer (ID / PASSWORD)
	//
	//STRING						m_string_line_ID;
	//STRING						m_string_line_PASSWORD;

	LineEditorVisual			m_lev_id;
	LineEditorVisual			m_lev_password;
	std::string					m_lev_id_backup;

	//INPUT_POSITION	m_e_ip; // input position

	void	SendLoginToClient();
	//bool	NextFocus();
	bool	ReadySend();
	void	ChangeFocus();

public:
	C_VS_UI_LOGIN();
	~C_VS_UI_LOGIN();

	void	AcquireDisappear() {}
	void	CancelPushState() { m_pC_button_group->CancelPushState(); }
	void	AcquireFirstSequence();
	void	UnacquireMouseFocus();
	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON * p_button);
	void	WindowEventReceiver(id_t event);
	bool	IsPixel(int _x, int _y);

	void	Run(id_t id);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);
	void	Show();
	void	Process();
	
	void	ExecuteObject();
	void	Start();
	void	Finish();
};
/*
//-----------------------------------------------------------------------------
// C_VS_UI_NEWUSER
//
// 
//-----------------------------------------------------------------------------
class C_VS_UI_NEWUSER : public Window, public Exec, public ButtonVisual
{
private:
	ButtonGroup *				m_pC_button_group;
	C_SPRITE_PACK *			m_pC_newuser_spk;

	enum EXEC_ID
	{
		ID_REPEAT_CHECK,
		FINISH,
		CANCEL,
		GENDER_MALE,
		GENDER_FEMALE,
		ANNOUNCE_MY_INFO,
	};

	enum ITEM_SEARCH_SEQUENCE
	{
		ISS_ID,
		ISS_PASSWORD,
		ISS_REPASSWORD,
		ISS_NAME,
		ISS_STATE,
		ISS_SSN,
		ISS_ADDRESS,
		ISS_WOO, // 우편번호
		ISS_PHONE,
		ISS_HOMEPAGE,
		ISS_EMAIL,

		ISS_COUNT,
	};

	static S_RECT						m_item_rect[ISS_COUNT];
	static ITEM_SEARCH_SEQUENCE	m_item_search_sequence[ISS_COUNT];

	enum NEWUSER_SPK_INDEX
	{
		NEWUSER_WINDOW,
		ID_REPEAT_CHECK_IMAGE,
		FINISH_IMAGE,
		CANCEL_IMAGE,
		CHECK_IMAGE,
	};

	// input item
	LineEditorVisual			m_lev_id;
	LineEditorVisual			m_lev_password;
	LineEditorVisual			m_lev_repassword;
	LineEditorVisual			m_lev_name;
	LineEditorVisual			m_lev_ssn_part1;
	LineEditorVisual			m_lev_ssn_part2;
	LineEditorVisual			m_lev_email;
	LineEditorVisual			m_lev_state;
	LineEditorVisual			m_lev_phone;
	LineEditorVisual			m_lev_woo;
	LineEditorVisual			m_lev_homepage;
	LineEditorVisual			m_lev_address;
	bool							m_bl_female;
	bool							m_bl_announce_my_info;

	int							m_current_focus;
	bool							m_bl_ssn_ip_part1; // input position

	void	SendNewUserInfoToClient();
	void	ChangeFocus(ITEM_SEARCH_SEQUENCE n);

public:
	C_VS_UI_NEWUSER();
	~C_VS_UI_NEWUSER();

	void	AcquireDisappear() {}
	void	CancelPushState() { m_pC_button_group->CancelPushState(); }
	void	WindowEventReceiver(id_t event);
	bool	IsPixel(int _x, int _y);
	void	UnacquireMouseFocus();

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button);
	void	Run(id_t id);
	void	Show();
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);
	void	Start();
	void	Finish();
	void	Process();
};
*/
//-----------------------------------------------------------------------------
// C_VS_UI_CHAR_DELETE
//
// 
//-----------------------------------------------------------------------------
class C_VS_UI_CHAR_DELETE : public Window, public Exec, public ButtonVisual
{
private:
	enum CHAR_DELETE_MENU
	{
		DELETE_OK,
		DELETE_CANCEL,
	};

//	enum IMAGE_SPK_INDEX
//	{
//		DELETE_WINDOW,
//	};

	int							m_selected_slot;

//	C_SPRITE_PACK *			m_pC_image_spk;
	ButtonGroup *				m_pC_button_group;

	// 주민등록번호(SSN) string buffer.
	LineEditorVisual			m_lev_ssn_part1;
	LineEditorVisual			m_lev_ssn_part2;
	bool							m_bl_ssn_ip_part1; // input position

	void	SendCharacterDeleteToClient();

public:
	C_VS_UI_CHAR_DELETE();
	~C_VS_UI_CHAR_DELETE();

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON * p_button);
	void	UnacquireMouseFocus() { m_pC_button_group->UnacquireMouseFocus(); }
	void	CancelPushState() { m_pC_button_group->CancelPushState(); }
	void	AcquireDisappear() {}
	void	WindowEventReceiver(id_t event);
	bool	IsPixel(int _x, int _y);

	void	Start();
	void	Finish();
	void	Process();
	void	Show();
	void	Run(id_t id);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);
	void	Slot(int slot) { m_selected_slot = slot; }

	BYTE	m_btBox_RGB_R;
	BYTE	m_btBox_RGB_G;
	BYTE	m_btBox_RGB_B;
	BYTE	m_btBox_RGB_Alpha;

	BYTE	m_btLine_RGB_R;
	BYTE	m_btLine_RGB_G;
	BYTE	m_btLine_RGB_B;

	WORD	Get_RGB_16(BYTE btRGB_R, BYTE btRGB_G, BYTE btRGB_B);
	WORD	Get_RGBAlpha_16(BYTE btRGB_Alpha);

	void	Init_TitleUIInterface_InfInfo();
};

//-----------------------------------------------------------------------------
// C_VS_UI_CHAR_APPEARANCE
//
// Chacter 외모 변경 class.
//-----------------------------------------------------------------------------
/*
class C_VS_UI_CHAR_APPEARANCE : public Window, public Exec
{
private:
	enum FACE_SPK_INDEX
	{
		M_GUNNER,
		M_FIGHTER,
		M_PRIEST,
		W_GUNNER,
		W_FIGHTER,
		W_PRIEST,
	};

	enum APPEARANCE_MENU
	{
		APPERANCE_OK,
		APPERANCE_CANCEL,
		FACE1,
		FACE2,
		FACE3,
		COLORSET1,
		COLORSET2,
		MENU_COUNT,
	};

	enum 
	{ 
		// 0 ~ 35 (color set range)
		COLORSET_X = 9, 
		COLORSET_Y = 4,

		// appearance Window position
		APPEARANCE_X = 342,
		APPEARANCE_Y = 182,

		// color set offset
		COLORSET_OFFSET_X = 45,
		COLORSET_OFFSET_Y = 170,

		// color unit rect width, height
		COLOR_UNIT_W = 20,
		COLOR_UNIT_H = 20,
	};

	//
	// Color Window 관련
	//
	BYTE							m_b_hair_colorset; // 선택된 color set
	BYTE							m_b_skin_colorset; // 선택된 color set
	int							m_focused_x; // color 선택 focus
	int							m_focused_y;
	BYTE							m_b_colorset_array[COLORSET_Y][COLORSET_X];
	bool							m_bl_colorset1; // Appearance Window에서 colorset1이 선택되었는가?
	bool							m_bl_push_colorset;

	C_VS_UI_BUTTON *			m_pC_button[MENU_COUNT];
	C_SPRITE_PACK *			m_pC_appearance_spk;
	C_SPRITE_PACK *			m_pC_face_spk;

	S_SLOT *						m_p_slot;

public:
	C_VS_UI_CHAR_APPEARANCE();
	~C_VS_UI_CHAR_APPEARANCE();

	void	WindowEventReceiver(id_t event);
	bool	IsPixel(int _x, int _y);

	void	Show();
	void	Run(id_t id);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);
	void	Start();
	void	Finish();
	void	Process();
	void	SetSlotCharacter(S_SLOT * p_slot) { m_p_slot = p_slot; }
};*/



































//-----------------------------------------------------------------------------
// C_VS_UI_NEWCHAR
//
// 
//-----------------------------------------------------------------------------
class C_VS_UI_NEWCHAR : public Window, public Exec, public ButtonVisual, public C_VS_UI_DESC
{
private:
//	C_ANI_OBJECT *				m_pC_ao_fin;
//	C_ANIMATION *				m_pC_ani_fin;

	enum COMMON_SPK_ID
	{
		BACK,
		LEFT_ANIMATION_TITLE,
		RIGHT_ANIMATION_TITLE,
	};

	enum CREATE_SPK_ID
	{
		WINDOW_800_600,
		WINDOW_1024_768,
		WINDOW_1280_720,
		WINDOW_1280_960,
		WINDOW_1280_1024,
		TITLE,
		MALE_CHECK,
		MALE_CHECK_HILIGHTED,
		SLAYER_BUTTON,
		VAMPIRE_BUTTON,
		OUSTERS_BUTTON,
		FACE_BACK_BUTTON,
		FACE_BACK_BUTTON_PUSHED,
		FACE_BACK_BUTTON_HILIGHTED,
		FACE_NEXT_BUTTON,
		FACE_NEXT_BUTTON_PUSHED,
		FACE_NEXT_BUTTON_HILIGHTED,
		CHECK_BUTTON,
		CHECK_BUTTON_PUSHED,
		CHECK_BUTTON_HILIGHTED,
		REROLL_BUTTON,
		REROLL_BUTTON_PUSHED,
		REROLL_BUTTON_HILIGHTED,
		BONUS_LINE,
		PLUS_BUTTON,
		PLUS_BUTTON_PUSHED,
		PLUS_BUTTON_HILIGHTED,
		MINUS_BUTTON,
		MINUS_BUTTON_PUSHED,
		MINUS_BUTTON_HILIGHTED,
		ABILITY_DISPLAY_TOOL,
		HAIR_COLOR_SELECT,
		SKIN_COLOR_SELECT,
		SEX_DISPLAY_TOOL,
		INTERNATIONAL_TITLE,
	};

	enum EXEC_ID
	{
		BACK_ID,
		NEXT_ID,
		SLAYER_ID,
		VAMPIRE_ID,
		OUSTERS_ID,
		MALE_ID,
		FEMALE_ID,
		FACE_BACK_ID,
		FACE_NEXT_ID,
		CHECK_ID,
		SAVE_ID,
		LOAD_ID,
		REROLL_ID,
		STR_PLUS_ID,
		DEX_PLUS_ID,
		INT_PLUS_ID,
		STR_MINUS_ID,
		DEX_MINUS_ID,
		INT_MINUS_ID,

		CHAR_LEFT_LOTATION_ID,
		CHAR_RIGHT_LOTATION_ID,

		SELECT_SLAYER_ID,
		SELECT_VAMPIRE_ID,
		SELECT_OUSTERS_ID,

		SELECT_SKIN,
		SELECT_BLAZE,
		SELECT_SWORD,
		SELECT_GUN,
		SELECT_HEAL,
		SELECT_ENCHANT,

	};

	enum 
	{ 
		NAME_BOARD_X = 381,
		NAME_BOARD_Y = 174,

		// hair/skin 24 color
		COLOR_LIST_X = 8,
		COLOR_LIST_Y = 3,

		COLOR_UNIT_X = 15,
		COLOR_UNIT_Y = 9,

		TABLE_X = 283, // color table
		TABLE_X2 = 457,
		TABLE_Y = 419,
	}; 

	enum	EFFECT_INDEX
	{
		EFFECT_INDEX_FIRE_LEFT1,
		EFFECT_INDEX_FIRE_LEFT2,
		EFFECT_INDEX_FIRE_RIGHT1,
		EFFECT_INDEX_FIRE_RIGHT2,
		EFFECT_INDEX_FIRE_CENTER,
		EFFECT_INDEX_CHAR_ATTACH_UP,
		EFFECT_INDEX_CHAR_ATTACH_DOWN,
		EFFECT_INDEX_CHAR_SELECT,
	};

	enum FACE_SPK_INDEX
	{
		M_GUNNER,
		M_FIGHTER,
		M_PRIEST,
		W_GUNNER,
		W_FIGHTER,
		W_PRIEST,

		BLIGHT_FACE_OFFSET=0,
		GENDER_OFFSET=3,
	};

	CCreatureFramePack 		m_slayer_man_cfpk;
	CCreatureFramePack 		m_slayer_woman_cfpk;
	CCreatureFramePack 		m_vampire_cfpk;
	CCreatureFramePack 		m_ousters_cfpk;
	
	CCreatureFramePack		m_AdvancementSlayerManCfpk;
	CCreatureFramePack		m_AdvancementSlayerWomanCfpk;
	CCreatureFramePack		m_AdvancementVampireManCfpk;
	CCreatureFramePack		m_AdvancementVampireWomanCfpk;
	CCreatureFramePack		m_AdvancementOustersCfpk;
	
	CIndexSpritePack 			m_slayer_man_ispk;
	CIndexSpritePack 			m_slayer_woman_ispk;
	CIndexSpritePack 			m_vampire_ispk;
	CIndexSpritePack 			m_ousters_ispk;
	
	CIndexSpritePack			m_AdvancementSlayerManIspk;
	CIndexSpritePack			m_AdvancementSlayerWomanIspk;
	CIndexSpritePack			m_AdvancementVampireManIspk;
	CIndexSpritePack			m_AdvancementVampireWomanIspk;
	CIndexSpritePack			m_AdvancementOustersIspk;

	enum E_SPK_ID_1
	{
		BK_800_600,
		BK_1024_768,
		BK_1280_960,
		BK_1280_1024,
		BK_PANEL,
		BUTTON_BLUE_PRESS,
		BUTTON_BLUE_NORMAL,
		BUTTON_ROTE_LEFT_PRESS,
		BUTTON_ROTE_LEFT_NORMAL,
		BUTTON_ROTE_RIGHT_PRESS,
		BUTTON_ROTE_RIGHT_NORMAL,
		BUTTON_SLAYER_NORMAL,
		BUTTON_SLAYER_PRESS,
		BUTTON_VAMPIRE_NORMAL,
		BUTTON_VAMPIRE_PRESS,
		BUTTON_OUTER_NORMAL,

		BUTTON_OUTER_PRESS,
		BK_MILE_FEMAL,
		BTN_CHECK,
		BTN_UNCHECK,
		BK_BLACK,
		BTN_ADD_PRESS,
		BTN_ADD_NORMAL,
		BTN_DELETE_PRESS,
		BTN_DELETE_NORMAL,
		BTN_RED_PRESS,
		BTN_RED_NORMAL,
		BTN_GREEN_PRESS,
		BTN_GREEN_NORMAL,
		IMAGE_DARKEDEN_ICON,
		IMAGE_DARKEDEN_ICON_A,
		SKIN_WINDOW,
		BTN_YELLOW_PRESS,
		BTN_YELLOW_NORMAL,

		BTN_BLAZE_NORMAL,
		BTN_SWORD_NORMAL,
		BTN_GUN_NORMAL,
		BTN_HEAL_NORMAL,
		BTN_ENCHANT_NORMAL,

		BTN_BLAZE_PRESS,
		BTN_SWORD_PRESS,
		BTN_GUN_PRESS,
		BTN_HEAL_PRESS,
		BTN_ENCHANT_PRESS,
		BTN_CHAR_1,
		BTN_CHAR_2,
		BTN_CHAR_3,
		BTN_CHAR_4,
		BTN_CHAR_1_1,
		BTN_CHAR_2_1,
		BTN_CHAR_3_1,
		BTN_CHAR_4_1,

	};

	//C_SPRITE_PACK				m_image_hays_spk1;
	C_SPRITE_PACK				m_image_hays_spk;
	int							m_iCurBackPicID;

	C_SPRITE_PACK				m_common_spk;
	C_SPRITE_PACK				m_image_spk;
	C_SPRITE_PACK				m_face_spk;
	C_SPRITE_PACK				m_title_spk;
	C_SPRITE_PACK*				m_pC_use_grade;

	enum E_NEW_CHARACTER_SPK_ID
	{
		BACK_GROUND_800_600,
		BACK_GROUND_1024_768,
		BACK_GROUND_1280_720,
		BACK_GROUND_1280_960,
		BACK_GROUND_1280_1024,
		NEW_CHAR_BOX,
		CHAR_NAME_CHECK_BUTTON_PUSHED,
		CHAR_NAME_CHECK_BUTTON,
		CHAR_LEFT_RATOATION_BUTTON_PUSHED,
		CHAR_LEFT_RATOATION_BUTTON,
		CHAR_RIGHT_RATOATION_BUTTON_PUSHED,
		CHAR_RIGHT_RATOATION_BUTTON,
		CHAR_FACE_SLAYER_MALE_SELECT_1,
		CHAR_FACE_SLAYER_MALE_SELECT_2,
		CHAR_FACE_SLAYER_MALE_SELECT_3,
		CHAR_FACE_SLAYER_FEMALE_SELECT_1,
		CHAR_FACE_SLAYER_FEMALE_SELECT_2,
		CHAR_FACE_SLAYER_FEMALE_SELECT_3,
		CHAR_FACE_VAMPIRE_MALE_SELECT,
		CHAR_FACE_VAMPIRE_FEMALE_SELECT,
		CHAR_FACE_OUSTERS_SELECT,
		SELECT_SLAYER_BUTTON,
		SELECT_VAMPIRE_BUTTON,
		SELECT_OUSTERS_BUTTON,
		MALE_OR_FEMALE_SELECT_BOX,
		MALE_BUTTON,
		FEMALE_BUTTON,
		HAIR_COLOR_BOX,
		SKIN_COLOR_BOX,
		OPSET_BOX,
		SAVE_BUTTON_PUSHED,
		SAVE_BUTTON,
		LOAD_BUTTON_PUSHED,
		LOAD_BUTTON,
		RESET_BUTTON_PUSHED,
		RESET_BUTTON,
		STET_BOX,
		STET_PLUS_BUTTON_PUSHED,
		STET_PLUS_BUTTON,
		STET_MINUS_BUTTON_PUSHED,
		STET_MINUS_BUTTON,
		RADIO_SELECT_BUTTON,
		PREV_BUTTON_PUSHED,
		PREV_BUTTON,
		NEXT_BUTTON_PUSHED,
		NEXT_BUTTON,
		TEXT_BAR,
		ANI_MARK,
		HIDE_OUSTERS_SELECTION_BUTTON,
	};


	enum E_SELECT_FACE
	{
		SELECT_LEFT_FACE,
		SELECT_CENTER_FACE,
		SELECT_RIGHT_FACE,
		SELECT_FACE_MAX
	};

	enum E_SELECT_MALE_OR_FEMALE	//성별 선택에서 마우스가 롤 오버된 상태일때 체크
	{
		VIRTURE_SELECT_MALE,
		VIRTURE_SELECT_FEMALE,
		VIRTURE_NO_SELECT,
	};

	enum E_STET
	{
		STET_STR,
		STET_DEX,
		STET_INT,
		STET_MAX
	};

	enum E_TEXT_LINE 
	{
		LINE1,
		LINE2,
		LINE3,
		LINE4,
		LINE5,
		LINE_MAX
	};

	enum USEGRADE
	{
		CHILD,			//12세
		//TEENAGER,
		ADULT,			//18세
		VIOLENCE,		//폭력성
		FEAR,			//공포
	};

	WORD						m_wNewCharBox_X;				//캐릭터 생성창 박스 위치
	WORD						m_wNewCharBox_Y;

	WORD						m_wNameCheck_Button_X;			//캐릭터 이름 중복 버튼의 위치
	WORD						m_wNameCheck_Button_Y;

	WORD						m_wCharNameFocus_X;				//이름 입력 포커스	위치
	WORD						m_wCharNameFocus_Y;

	WORD						m_wCharLeftRotation_Button_X;	//캐릭터 돌려보기 버튼 위치
	WORD						m_wCharLeftRotation_Button_Y;

	WORD						m_wCharRightRotation_Button_X;	//캐릭터 돌려보기 버튼 위치
	WORD						m_wCharRightRotation_Button_Y;

	POINT						m_ptFace_Radio[SELECT_FACE_MAX];	//얼굴 선택 라디오 버튼 위치
	POINT						m_ptFace[SELECT_FACE_MAX];			//얼굴 버튼 위치

	WORD						m_wCharView_X;					//캐릭터 보여줄 위치
	WORD						m_wCharView_Y;

	POINT						m_ptRaceSelect_Radio[RACE_MAX];	//캐릭터 선택 라디오 버튼 위치

	WORD						m_wSelect_Race_Slayer_Button_X;	//슬레이어 선택 버튼 위치
	WORD						m_wSelect_Race_Slayer_Button_Y;

	WORD						m_wSelect_Race_Vampire_Button_X;	//뱀파이어 선택 버튼 위치
	WORD						m_wSelect_Race_Vampire_Button_Y;

	WORD						m_wSelect_Race_Ousters_Button_X;	//아우스터즈 선택 버튼 위치
	WORD						m_wSelect_Race_Ousters_Button_Y;
	WORD						m_wHide_Ousters_Selection_Button_X;		//아우스터즈 선택 버튼 가리는 위치
	WORD						m_wHide_Ousters_Selection_Button_Y;

	WORD						m_wMale_OR_Female_Select_Box_X;		//성별 박스 위치
	WORD						m_wMale_OR_Female_Select_Box_Y;
	
	WORD						m_wMale_Select_Button_X;			//성별(남자) 버튼 위치
	WORD						m_wMale_Select_Button_Y;

	WORD						m_wFemale_Select_Button_X;			//성벌(여자) 버튼 위치
	WORD						m_wFemale_Select_Button_Y;

	WORD						m_wMale_Select_Radio_X;				//성별(남자) 선택 라디오 버튼 위치
	WORD						m_wMale_Select_Radio_Y;

	WORD						m_wFemale_Select_Radio_X;			//성별(여자) 선택 라디오 버튼 위치
	WORD						m_wFemale_Select_Radio_Y;

	WORD						m_wHairColor_BOX_X;					//머리 색상 박스 위치
	WORD						m_wHairColor_BOX_Y;

	WORD						m_wHairColor_Start_X;				//머리 색상 시작 위치
	WORD						m_wHairColor_Start_Y;

	WORD						m_wSkinColor_BOX_X;					//피부 색상 박스 위치
	WORD						m_wSkinColor_BOX_Y;

	WORD						m_wSkinColor_Start_X;				//피부 색상 시작 위치
	WORD						m_wSkinColor_Start_Y;

	WORD						m_wOpset_BOX_X;						//슬레이어 설정들의 박스 위치(저장, 불러오기, 다시 설정)
	WORD						m_wOpset_BOX_Y;

	WORD						m_wSave_Button_X;					//저장 버튼의 위치
	WORD						m_wSave_Button_Y;

	WORD						m_wLoad_Button_X;					//불러오기 버튼의 위치
	WORD						m_wLoad_Button_Y;

	WORD						m_wReset_Button_X;					//다시 설정 버튼의 위치
	WORD						m_wReset_Button_Y;

	WORD						m_wStet_Box_X;						//스텟 박스 위치
	WORD						m_wStet_Box_Y;

	POINT						m_ptStet_Plus[STET_MAX];			//스텟 플러스 버튼 위치
	POINT						m_ptStet_Minus[STET_MAX];			//스텟 플러스 버튼 위치

	WORD						m_wNextButton_X;					//확인(다음) 버튼의 위치
	WORD						m_wNextButton_Y;

	WORD						m_wPrevButton_X;					//이전(Back) 버튼의 위치
	WORD						m_wPrevButton_Y;

	WORD						m_wSTR_Text_X;
	WORD						m_wSTR_Text_Y;

	WORD						m_wDEX_Text_X;
	WORD						m_wDEX_Text_Y;

	WORD						m_wINT_Text_X;
	WORD						m_wINT_Text_Y;

	WORD						m_wHP_Text_X;
	WORD						m_wHP_Text_Y;

	WORD						m_wMP_Text_X;
	WORD						m_wMP_Text_Y;

	WORD						m_wDEFENSE_Text_X;	//회피율 텍스트 위치
	WORD						m_wDEFENSE_Text_Y;

	WORD						m_wPROTECTION_Text_X;	//방어율 텍스트 위치
	WORD						m_wPROTECTION_Text_Y;

	WORD						m_wTOHIT_Text_X;	//명중율 텍스트 위치
	WORD						m_wTOHIT_Text_Y;

	WORD						m_wDAM_Text_X;	//데미지 텍스트 위치
	WORD						m_wDAM_Text_Y;

	WORD						m_wBonus_Text_X;	//보너스 포인트 텍스트 위치
	WORD						m_wBonus_Text_Y;

	char						m_chDirection;						//방향 설정
	BYTE						m_btRace_Select;					//종족 선택

	BYTE						m_btVirtureSelect_Face;				//얼굴을 선택 한다. 마우스가 버튼을 가리키고 있을때
	BYTE						m_btSelect_Face;					//얼굴을 선택 한다.
	BYTE						m_btVirtureSelect_Male;				//여자, 남자 선택 (true = 남자) 마우스가 버튼을 가리키고 있을때
	WORD						m_wMale_OR_Femail_Select_Radio_Alpha;		//성별 선택 라디오 버튼의 알파 값
	WORD						m_wFace_Alpha;						//얼굴 선택 라디오 버튼의 알파 값

	WORD						m_wSave_Button_Alpha;				//
	WORD						m_wLoad_Button_Alpha;				//
	WORD						m_wReset_Button_Alpha;				//

	WORD						m_wStet_Plus_Button_Alpha[STET_MAX];
	WORD						m_wStet_Minus_Button_Alpha[STET_MAX];


	WORD						m_wEffect_Fire_Left1_X;				// 불 이펙트 위치
	WORD						m_wEffect_Fire_Left1_Y;

	WORD						m_wEffect_Fire_Left2_X;
	WORD						m_wEffect_Fire_Left2_Y;

	WORD						m_wEffect_Fire_Right1_X;
	WORD						m_wEffect_Fire_Right1_Y;

	WORD						m_wEffect_Fire_Right2_X;
	WORD						m_wEffect_Fire_Right2_Y;

	WORD						m_wEffect_Fire_Center_X;
	WORD						m_wEffect_Fire_Center_Y;

	WORD						m_wChild_X;
	WORD						m_wChild_Y;

	WORD						m_wAdult_X;
	WORD						m_wAdult_Y;

	WORD						m_wViolence_X;
	WORD						m_wViolence_Y;

	WORD						m_wFear_X;
	WORD						m_wFear_Y;

	WORD						m_wTex_Bar_X;
	WORD						m_wTex_Bar_Y;

	WORD						m_wAni_Mark_X;
	WORD						m_wAni_Mark_Y;

	POINT						m_ptText_Line[LINE_MAX];						//아래 하단에 보여질 텍스트 좌표의 위치
	char						m_arrTextLine[LINE_MAX][256];

	WORD						m_wPrimeum_Use_Day_Txt_X;
	WORD						m_wPrimeum_Use_Day_Txt_Y;

	enum HELP
	{
		HELP_DEFAULT,
		HELP_BACK,
		HELP_NEXT,
		HELP_NAME,
		HELP_CHECK,
		HELP_TRIBE,
		HELP_GENDER,
		HELP_HAIRCOLOR,
		HELP_SKINCOLOR,
		HELP_FACETYPE,
		HELP_STR,
		HELP_DEX,
		HELP_INT,
		HELP_HP,
		HELP_MP,
		HELP_DEFENCE,
		HELP_PROTECTION,
		HELP_TOHIT,
		HELP_DAMAGE,
		HELP_SAVE,
		HELP_LOAD,
		HELP_REROLL,
		HELP_BONUS,
		HELP_MAX,
	};
	int							m_focused_help;

//	bool							m_bl_skin_color_control;
	S_SLOT *						m_p_slot; // character manager의 slot중 하나를 가리킨다.
	int							m_selected_slot; // 선택된 slot: char manager에 있지만, 필요함.
	int							m_selected_job;

	ButtonGroup *				m_pC_button_group;
//	ButtonGroup *				m_pC_button_group_face;

	LineEditorVisual			m_lev_name;

	// for color change
	static int					m_hair_color_array[COLOR_LIST_X][COLOR_LIST_Y];
	static int					m_skin_color_array[COLOR_LIST_X][COLOR_LIST_Y];
	Point							m_hair_point;
	Point							m_skin_point;
	bool							m_bl_pushed_table;
	bool						m_show_skin;

	int							m_failed_code;

	int							m_iSave[3];

	CTickTimer *				m_pAnimationTimer;
	int							m_aniArpha;
	bool						m_bAniArphaUp;

	//
	// face 선택 list.
	// 현재 선택된 face가 맨 먼저 나오게 된다. 다른 것을 선택하면 다른 것이 먼저 나오고...
	//
	bool							m_face_change_temp;

	Point GetPoint(int colorset, bool bl_skin_color);
	int	GetColor(int _x, int _y, bool bl_skin_color);
	bool	ChangeColor(int _x, int _y);

	void	SendNewCharacterToClient();
//	void	ChangeFace();
	void	_ShowCharacterOusters( int _x, int _y, S_SLOT* p_slot, int index, int enable, int dark  );
	void	_ShowCharacterSlayer( int _x, int _y, S_SLOT* p_slot, int index, int enable, int dark );
	void	_ShowCharacterVampire( int _x, int _y, S_SLOT* p_slot, int index, int enable, int dark );

	void	_ShowCharacterACOusters( int _x, int _y, S_SLOT* p_slot, int index, int enable, int dark );
	void	_ShowCharacterACSlayer( int _x, int _y, S_SLOT* p_slot, int index, int enable, int dark );
	void	_ShowCharacterACVampire( int _x, int _y, S_SLOT* p_slot, int index, int enable, int dark );


	void	Init_TitleUIInterface_InfInfo();

public:
	C_VS_UI_NEWCHAR();
	~C_VS_UI_NEWCHAR();

//	void	UsedID(bool used);

	void	AcquireDisappear() {}
	void	CancelPushState() { m_pC_button_group->CancelPushState(); }
	void	WindowEventReceiver(id_t event);
	bool	IsPixel(int _x, int _y);
	void	UnacquireMouseFocus();

	void	ShowButtonName(C_VS_UI_EVENT_BUTTON *p_button);
	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON * p_button);
	void	DrawCover(int _x, int _y);
//	void	DrawHP(int _x, int _y, int line);
//	void	DrawMP(int _x, int _y, int line);
//	void	SetEnergy(int cur_val, int max_val, WORD &percent, WORD &line);
	void	Run(id_t id);
	void	ShowCharacter(int _x, int _y, S_SLOT * p_slot, int index, int enable, int dark=false);
	void	Show();
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);
	void	Start();
	void	Finish();
	void	Process();
	void	RollDice(bool load = false);
	void	SetError(int error) { m_failed_code = error; }
	void	SetCharacterToThisSlot(int slot, S_SLOT * p_slot);
//	void	SetBoardSpk(C_SPRITE_PACK * p_spk) { m_pC_board_spk = p_spk; }

	void	DrawCharFaceSelect();
	void	ChangeEffectPoint();

	void	DrawSelect_Race();
	void	DrawSelect_Male_OR_Female();
	void	DrawSelect_Stet();				//능력치
	void	DrawSelect_Hair_Skin_Color();	//색 선택
	void	DrawStetText();					//글자

	void	MouseSelectMale_OR_Female_RollOver(int _x, int _y);				//성별 선택
	void	MouseSelectFace_RollOver(int _x, int _y);						//얼굴 선택
	void	MouseSelectStet_RollOver(int _x, int _y);						//얼굴 선택

	void	MouseSelectMale_OR_Female_Click(int _x, int _y);				//성별 선택
	void	MouseSelectFace_Click(int _x, int _y);						//얼굴 선택
	void	MouseSelectStet_Click(int _x, int _y);						//얼굴 선택
};


class C_VS_UI_GO_BILING_PAGE;
class C_VS_UI_NETMARBLE_AGREEMENT;









//-----------------------------------------------------------------------------
// C_VS_UI_CHAR_MANAGER
//
// 
//-----------------------------------------------------------------------------
class C_VS_UI_CHAR_MANAGER : public Window, public Exec, public ButtonVisual, public C_VS_UI_DESC
{
private:
	enum SLOT_POSITION
	{ 
//		HEART_LEFT_X = 66, 
//		HEART_CENTER_X = 290, 
//		HEART_RIGHT_X = 530, 
//		HEART_Y = 120,

		SLOT_LEFT = 0,
		SLOT_CENTER,
		SLOT_RIGHT,
		SLOT,
	};

	enum COMMON_SPK_ID
	{
		BACK,
		BACK_BUTTON,
		BACK_BUTTON_PUSHED,
		BACK_BUTTON_HILIGHTED,
		NEXT_BUTTON,
		NEXT_BUTTON_PUSHED,
		NEXT_BUTTON_HILIGHTED,
		LEFT_ANIMATION_TITLE,
		RIGHT_ANIMATION_TITLE,
	};

	enum CHAR_MANAGER_SPK_ID
	{
		WINDOW_800_600,
		WINDOW_1024_768,
		WINDOW_1280_720,
		WINDOW_1280_960,
		WINDOW_1280_1024,
		CAHR_INFO_ANGLE_800_600,
		SLAYER_CHAR_INFO_ANGLE,
		CAHR_INFO_ANGLE_1024_768,
		CAHR_NAME_ANGLE,
		CREATE_BUTTON_PUSHED,
		CREATE_BUTTON,
		DELETE_BUTTON_PUSHED,
		DELETE_BUTTON,
		GAME_START_PUSHED,
		GAME_START,
		PREV_SCREEN_BUTTON_PUSHED,
		PREV_SCREEN_BUTTON,
		CHAR_SELECT_LEFT_PUSHED,
		CHAR_SELECT_LEFT,
		CHAR_SELECT_CENTER_PUSHED,
		CHAR_SELECT_CENTER,
		CHAR_SELECT_RIGHT_PUSHED,
		CHAR_SELECT_RIGHT,
		TEXT_BAR,
		ANI_MARK,
	};

	enum SPK_ID_0
	{
		SLAYER_800_600,
		VAMPIRE_800_600,
		OUSTERS_800_600,
		NONE_800_600,

		SLAYER_1024_768,
		VAMPIRE_1024_768,
		OUSTERS_1024_768,
		NONE_1024_768,

		SLAYER_1280_960,
		VAMPIRE_1280_960,
		OUSTERS_1280_960,
		NONE_1280_960,

		SLAYER_1280_1024,
		VAMPIRE_1280_1024,
		OUSTERS_1280_1024,
		NONE_1280_1024,
	};

	enum SPK_ID_1
	{
		PANAL_FILL,
		PANAL_NONE,
		RACE_ICON_SLAYER_ACTIVE,
		RACE_ICON_VAMPIRE_ACTIVE,
		RACE_ICON_OUSTERS_ACTIVE,
		RACE_ICON_SLAYER_DEACTIVE,
		RACE_ICON_VAMPIRE_DEACTIVE,
		RACE_ICON_OUSTERS_DEACTIVE,
		BUTTON_SELROLE_NORMAL,
		BUTTON_SELROLE_DOWN,
		BUTTON_SELROLE_ENABLE,
		LIST_INFOMATION_NORMAL,
		LIST_INFOMATION_NONE,
		ICON_blade,
		ICON_Sword,
		ICON_Gun,

	};

	enum SPK_ID_2
	{
		ICON_Heal,
		ICON_Enchant,
		ICON_Fire,
		ICON_Water,
		ICON_Earth,
		BUTTON_BLUE_PRESS,
		BUTTON_BLUE_NORMAL,
		BUTTON_RED_PRESS,
		BUTTON_RED_NORMAL,
		BUTTON_YELLOW_PRESS,
		BUTTON_YELLOW_NORMAL,
		BUTTON_GREEN_PRESS,
		BUTTON_GREEN_NORMAL,
	};

public :

	enum EXEC_ID
	{
		BACK_ID,
		NEXT_ID,
		DELETE_ID,
		CREATE_ID,


		CANNOT_PLAY_ID,
		CANNOT_PLAY_BY_ATTR_ID,

		CHAR_SELECT_LEFT_ID,
		CHAR_SELECT_CENTER_ID,
		CHAR_SELECT_RIGHT_ID,
	};
private :
	enum USEGRADE
	{
		CHILD,
		//TEENAGER,
		ADULT,
		VIOLENCE,
		FEAR,
	};

	enum	EFFECT_INDEX
	{
		EFFECT_INDEX_FIRE_LEFT1,
		EFFECT_INDEX_FIRE_LEFT2,
		EFFECT_INDEX_FIRE_RIGHT1,
		EFFECT_INDEX_FIRE_RIGHT2,
		EFFECT_INDEX_FIRE_CENTER,
		EFFECT_INDEX_CHAR_ATTACH_UP,
		EFFECT_INDEX_CHAR_ATTACH_DOWN,
		EFFECT_INDEX_CHAR_SELECT,
	};

	enum E_TEXT_LINE 
	{
		LINE1,
		LINE2,
		LINE3,
		LINE_MAX
	};

	enum E_SLAYER_DOMAIN_LEVEL
	{
		SWORD,
		BLADE,
		GUN,
		HEAL,
		ENCHENT,
		DOMAIN_LEVE_MAX
	};

	C_VS_UI_CHAR_DELETE *	m_pC_char_delete;
	C_VS_UI_GO_BILING_PAGE *	m_pC_biling;
	C_VS_UI_NETMARBLE_AGREEMENT* m_pC_NetmarbleAgreement;

	C_VS_UI_EVENT_BUTTON*		m_pC_button_create_char[SLOT];

	C_SPRITE_PACK				m_image_hays_0;
	C_SPRITE_PACK				m_image_hays_1;
	C_SPRITE_PACK				m_image_hays_2;

	C_SPRITE_PACK				m_common_spk;
	C_SPRITE_PACK				m_image_spk;
	C_SPRITE_PACK*				m_pC_use_grade;
	C_SPRITE_PACK				m_title_spk;

	ButtonGroup *				m_pC_button_group;

	C_VS_UI_NEWCHAR *			m_pC_newchar;
//	C_VS_UI_CHAR_INFO * 		m_pC_char_info;

	S_SLOT						m_slot[SLOT];
	int							m_select_heart_temp;
	int							m_iBackGroundPicID;

	CTickTimer *				m_pAnimationTimer;
	int							m_aniArpha;
	bool						m_bAniArphaUp;

	WORD						m_wChar_Info_Angle_X;
	WORD						m_wChar_Info_Angle_Y;

	WORD						m_wSlayerChar_Info_Angle_X;
	WORD						m_wSlayerChar_Info_Angle_Y;

	WORD						m_wChar_Info_X;
	WORD						m_wChar_Info_Y;

	WORD						m_wSlayerChar_Info_X;
	WORD						m_wSlayerChar_Info_Y;

	POINT						m_ptArrChar_Pos[SLOT];
	POINT						m_ptArrCharSelect_Button[SLOT];

	WORD						m_wCharSelect_Button_Size_Width;
	WORD						m_wCharSelect_Button_Size_Height;

	Point						m_ptChar_Name_Bar[SLOT];
	Point						m_ptChar_Name[SLOT];
	WORD						m_wChar_Name_Bar_Width;

	WORD						m_wPrev_Button_X;
	WORD						m_wPrev_Button_Y;

	WORD						m_wGameStart_Button_X;
	WORD						m_wGameStart_Button_Y;

	WORD						m_wCharCreate_Button_X;
	WORD						m_wCharCreate_Button_Y;

	WORD						m_wCharDelete_Button_X;
	WORD						m_wCharDelete_Button_Y;

	WORD						m_wEffect_Fire_Left1_X;
	WORD						m_wEffect_Fire_Left1_Y;

	WORD						m_wEffect_Fire_Left2_X;
	WORD						m_wEffect_Fire_Left2_Y;

	WORD						m_wEffect_Fire_Right1_X;
	WORD						m_wEffect_Fire_Right1_Y;

	WORD						m_wEffect_Fire_Right2_X;
	WORD						m_wEffect_Fire_Right2_Y;

	WORD						m_wEffect_Fire_Center_X;
	WORD						m_wEffect_Fire_Center_Y;

	POINT						m_ptEffect_Char_Attach_UP[SLOT];
	POINT						m_ptEffect_Char_Attach_DOWN[SLOT];
	POINT						m_ptEffect_Char_Select[SLOT];

	short						m_stSelect_Slot;

	WORD						m_wChild_X;
	WORD						m_wChild_Y;

	WORD						m_wPanel_X;
	WORD						m_wPanel_Y;

	WORD						m_wListInfo_X;
	WORD						m_wListInfo_Y;

	WORD						m_wAdult_X;
	WORD						m_wAdult_Y;

	WORD						m_wViolence_X;
	WORD						m_wViolence_Y;

	WORD						m_wFear_X;
	WORD						m_wFear_Y;

	WORD						m_wTex_Bar_X;
	WORD						m_wTex_Bar_Y;

	WORD						m_wAni_Mark_X;
	WORD						m_wAni_Mark_Y;

	POINT						m_ptText_Line[LINE_MAX];						//아래 하단에 보여질 텍스트 좌표의 위치
	char						m_arrTextLine[LINE_MAX][256];

	WORD						m_wSlayerFindHighDomainLevel;					//슬레이어의 도메인 레벨중 가장 높은것을 찾을 변수
	WORD						m_w_CharHeight;									//캐릭터도 클릭이 될 수 있도록 변수 추가

	WORD						m_wPrimeum_Use_Day_Txt_X;
	WORD						m_wPrimeum_Use_Day_Txt_Y;

	WORD						m_wWorningString_X;
	WORD						m_wWorningString_Y;


	struct S_CHAR_INFO_STRING
	{
		std::string	strName;
		std::string	strStrength;
		std::string	strDex;
		std::string	strInt;
		std::string	strLevel;

		std::string	strSwordLevel;
		std::string	strBladeLevel;
		std::string	strGunLevel;
		std::string	strHealLevel;
		std::string	strEnchantLevel;

		std::string	strFame;
		std::string	strGrade;

		int			iSlotIndex;

		void	Release()
		{
			strName.clear();
			strStrength.clear();
			strDex.clear();
			strInt.clear();
			strLevel.clear();
			strFame.clear();
			strGrade.clear();

			strSwordLevel.clear();
			strBladeLevel.clear();
			strGunLevel.clear();
			strHealLevel.clear();
			strEnchantLevel.clear();



			strName.resize(0);
			strStrength.resize(0);
			strDex.resize(0);
			strInt.resize(0);
			strLevel.resize(0);
			strFame.resize(0);
			strGrade.resize(0);

			strSwordLevel.resize(0);
			strBladeLevel.resize(0);
			strGunLevel.resize(0);
			strHealLevel.resize(0);
			strEnchantLevel.resize(0);
			iSlotIndex	= -1;
		}
	};

	std::vector<S_CHAR_INFO_STRING>	m_Char_Info_String;
	enum HELP
	{
		HELP_DEFAULT,
		HELP_BACK,
		HELP_NEXT,
		HELP_X,
		HELP_CREATE,
		HELP_MAX,
	};
	int							m_focused_help;

public:
	C_VS_UI_CHAR_MANAGER();
	~C_VS_UI_CHAR_MANAGER();

	bool	SelectSlot(int n);
//	void	UsedID(bool used)	{ if(m_pC_newchar)m_pC_newchar->UsedID(used); }
//	void	CloseCharInfo();
	void	AcquireDisappear() {}
	void	CancelPushState() { m_pC_button_group->CancelPushState(); }
	void	AcquireFirstSequence();
	void	UnacquireMouseFocus();
	void	WindowEventReceiver(id_t event);
	bool	IsPixel(int _x, int _y);

	void	ShowButtonName(C_VS_UI_EVENT_BUTTON *p_button);
	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON * p_button);
	void	Run(id_t id);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);
	void	Show();
	void	Process();
	void	Start(bool back = false);
	void	Finish();
	void	NewCharacterCreateOk();
	void	NewCharacterCreateFailed(int error);
	void	SetCharacter(int slot, S_SLOT &S_slot);
	void	DeleteCharacter(int slot);
	void	ClearAllCharacter();

	void	PopupNetmarbleAgreementMessage();
	void	Init_TitleUIInterface_InfInfo();

	void	AddCharInfoString(int iSlotIndex);
	void	DeleteCharInfoString();
	void	DrawCharInfoString();

	void	ChangeEffectPoint();					//이팩트 좌표바꾼다.
	void	Draw_Effect_Button_Char();					//이팩트 좌표바꾼다.
};



//-----------------------------------------------------------------------------
// C_VS_UI_SERVER_SELECT
//
// 
//-----------------------------------------------------------------------------
class C_VS_UI_SERVER_SELECT : public Window, public Exec, public ButtonVisual, public C_VS_UI_DESC
{
public:
	enum SERVER_STATUS
	{
		STATUS_VERY_GOOD,
		STATUS_GOOD,
		STATUS_NORMAL,
		STATUS_BAD,
		STATUS_VERY_BAD,
		STATUS_DOWN,
	};

	enum GROUP_STATUS
	{
		STATUS_OPENED,
		STATUS_CLOSED,
	};


private:
	enum COMMON_SPK_ID
	{
		BACK,
		BACK_BUTTON,
		BACK_BUTTON_PUSHED,
		BACK_BUTTON_HILIGHTED,
		NEXT_BUTTON,
		NEXT_BUTTON_PUSHED,
		NEXT_BUTTON_HILIGHTED,
		LEFT_ANIMATION_TITLE,
		RIGHT_ANIMATION_TITLE,
	};

	enum SERVER_SELECT_SPK_ID
	{
		TITLE_WORLD,
		TITLE_SERVER,
		PREV_SCREEN_BUTTON_SELECT,
		PREV_SCREEN_BUTTON,
		NEXT_SCREEN_BUTTON_SELECT,
		NEXT_SCREEN_BUTTON,
		SLAYER_BAR,
		VAMPIRES_BAR,
		OUSTERS_BAR,
		BLACK_BAR,
		WORLD_SELECT_BAR,
		CHENEL_SELECT_BAR_CHENEL,
		CHENEL_SELECT_BAR_STATUS,
		CHENEL_SELECT_BAR_RACEINFO,
		TEXT_BAR,
		ANI_MARK,
		VIEW_RACE_INFO,
	};

	enum EXEC_ID
	{
		BACK_ID,
		NEXT_ID,
		SCROLL_UP_ID,
		SCROLL_DOWN_ID,
	};

	enum USEGRADE
	{
		CHILD,
		//TEENAGER,
		ADULT,
		VIOLENCE,
		FEAR,
	};	

	bool m_bl_group;

	unsigned int				m_scroll;
	bool						m_bl_scrolling;

	enum
	{
		SCROLL_X = 670,
		SCROLL_Y = 220,
		SCROLL_WIDTH = 20,
		SCROLL_HEIGHT = 185,

		MODE1024_X	= 112,
		MODE1024_Y	= 84,
	};

	enum E_TEXT_LINE 
	{
		LINE1,
		LINE2,
		LINE_MAX
	};

	//Add By Hays
	C_SPRITE_PACK				m_image_hays_spk;
	C_SPRITE_PACK				m_title_hays_spk;

	C_SPRITE_PACK				m_common_spk;
	C_SPRITE_PACK				m_image_spk;
	C_SPRITE_PACK				m_title_spk;
	C_SPRITE_PACK*				m_pC_use_grade;

	ButtonGroup *				m_pC_button_group;

	std::vector<std::string>	m_server_name;
	std::vector<int>			m_server_id;
	std::vector<int>			m_server_status;
	std::vector<bool>			m_server_nonpk;
	std::vector<WORD>			m_server_slayernum;
	std::vector<WORD>			m_server_vampirenum;
	std::vector<WORD>			m_server_oustersenum;

	std::vector<std::string>	m_server_name_chenel;
	std::vector<int>			m_server_id_chenel;
	std::vector<int>			m_server_status_chenel;
	std::vector<bool>			m_server_nonpk_chenel;
	std::vector<WORD>			m_server_slayernum_chenel;
	std::vector<WORD>			m_server_vampirenum_chenel;
	std::vector<WORD>			m_server_oustersenum_chenel;

	std::vector<std::string>	m_server_name_world;
	std::vector<int>			m_server_id_world;
	std::vector<int>			m_server_status_world;
	std::vector<bool>			m_server_nonpk_world;

	WORD						m_wListLayout_X;
	WORD						m_wListLayout_Y;

	WORD						m_wWorld_List_X;
	WORD						m_wWorld_List_Y;

	WORD						m_wChenel_List_X;
	WORD						m_wChenel_List_Y;

	WORD						m_wSelect_World_Click_Index;
	WORD						m_wSelect_Chenel_Index;

	WORD						m_wSelect_World_Bar_X;
	WORD						m_wSelect_World_Bar_Y;

	WORD						m_wSelect_Chenel_Bar_Chenel_X;
	WORD						m_wSelect_Chenel_Bar_Chenel_Y;

	WORD						m_wSelect_Chenel_Bar_Status_X;
	WORD						m_wSelect_Chenel_Bar_Status_Y;

	WORD						m_wSelect_Chenel_Bar_RaceInfo_X;
	WORD						m_wSelect_Chenel_Bar_RaceInfo_Y;

	WORD						m_wSelect_World_Bar_Interval_X;
	WORD						m_wSelect_World_Bar_Interval_Y;

	WORD						m_wSelect_Chenel_Bar_Interval_X;
	WORD						m_wSelect_Chenel_Bar_Interval_Y;

	WORD						m_wSelect_World_Name_Font_X;
	WORD						m_wSelect_World_Name_Font_Y;

	WORD						m_wSelect_Chenel_Name_Font_X;
	WORD						m_wSelect_Chenel_Name_Font_Y;

	WORD						m_wSelect_World_Status_Font_X;
	WORD						m_wSelect_World_Status_Font_Y;

	WORD						m_wSelect_Chenel_Status_Font_X;
	WORD						m_wSelect_Chenel_Status_Font_Y;

	WORD						m_wWorld_List_Show_Max;
	WORD						m_wChenel_List_Show_Max;

	int							m_server_select_world;
	int							m_server_select_chenel;

	WORD						m_wChar_Bar_Start_View_X;
	WORD						m_wChar_Bar_Start_View_Y;

	WORD						m_wChar_Bar_Interval_X;
	WORD						m_wChar_Bar_Interval_Y;

	BOOL						m_blAccep_World_Chenenl;				//월드로 받을건지 체널로 받을건지 확인 한다. true면 월드 false면 채널

	int							m_server_select_world_prev;
	int							m_server_select_chenel_prev;

	WORD						m_server_slayernumtotal;
	WORD						m_server_vampirenumtotal;
	WORD						m_server_oustersnumtotal;

	WORD						*m_pserver_slayernum_barcount;
	WORD						*m_pserver_vampirenum_barcount;
	WORD						*m_pserver_ousters_barcount;

	WORD						m_wPreve_Button_X;
	WORD						m_wPreve_Button_Y;

	WORD						m_wNext_Button_X;
	WORD						m_wNext_Button_Y;

	WORD						m_wChild_X;
	WORD						m_wChild_Y;

	WORD						m_wAdult_X;
	WORD						m_wAdult_Y;

	WORD						m_wViolence_X;
	WORD						m_wViolence_Y;

	WORD						m_wFear_X;
	WORD						m_wFear_Y;

	WORD						m_wTex_Bar_X;
	WORD						m_wTex_Bar_Y;

	WORD						m_wAni_Mark_X;
	WORD						m_wAni_Mark_Y;

	WORD						m_wView_Race_Info_Image_X;						//종족 정보 이미지 위치
	WORD						m_wView_Race_Info_Image_Y;

	POINT						m_ptText_Line[LINE_MAX];						//아래 하단에 보여질 텍스트 좌표의 위치

	int							m_focus_server;
	int							m_server_select;

	int							m_server_size;

	int							m_server_x;
	int							m_server_y;

	CTickTimer *				m_pAnimationTimer;
	int							m_aniArpha;
	bool						m_bAniArphaUp;

	bool						m_blKeybord_OR_Mouse_Input;			//키보드 입력 상태인지 마우스 입력 상태인지 확인 (true이면 키보드 입력 상태)

	char						m_arrTextLine[LINE_MAX][256];

	int							m_iOldMousePoint_X;
	int							m_iOldMousePoint_Y;

	WORD						m_wPrimeum_Use_Day_Txt_X;
	WORD						m_wPrimeum_Use_Day_Txt_Y;
	enum HELP
	{
		HELP_DEFAULT,
		HELP_BACK,
		HELP_NEXT,
		HELP_MAX,
	};
	int							m_focused_help;
public:
	C_VS_UI_SERVER_SELECT();
	~C_VS_UI_SERVER_SELECT();

	void	AcquireDisappear() {}
	void	CancelPushState() { m_pC_button_group->CancelPushState(); }
	void	AcquireFirstSequence();
	void	UnacquireMouseFocus();
	void	WindowEventReceiver(id_t event);
	bool	IsPixel(int _x, int _y);

	void	ShowButtonName(C_VS_UI_EVENT_BUTTON *p_button);
	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button);
	void	Run(id_t id);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);
	void	Show();
	void	Process();
	void	Start(bool bGroup);
	void	Finish();

#if __CONTENTS(__SERVER_SELECT_REVEWAL)
	void	SetServerList(LPSTR *name, int *id, int *status, int size, int default_id, bool *nonpk, WORD *pwSlayer, WORD *pwVampire, WORD *pwOusters);
#else
	void	SetServerList(LPSTR *name, int *id, int *status, int size, int default_id, bool *nonpk);
#endif	//__SERVER_SELECT_REVEWAL

private:
	void	SelectBarPos();
	void	SelectBarView();
	void	GroupView();
	void	ServerNameView();
	void	ServerNameViewWorld();
	
	void	CharBoxView();
	void	CharBarView(int iBarCount = 0, int iCharConnectBar = SLAYER_BAR, int iChannel	= 0, int iCharBarLine = 0);
	void	CharBarCount();
	void	ChannelCharBarView();

	void	Init_TitleUIInterface_InfInfo();
};


//-----------------------------------------------------------------------------
// class C_VS_UI_OPTION
//
//-----------------------------------------------------------------------------
class C_VS_UI_OPTION : public Window, public Exec, public ButtonVisual, public C_VS_UI_DESC
{
public :

	enum EXEC_ID
	{
		DEFAULT_ID = 0xffff0000,
		SAVE_ID,
		LOAD_ID,
		CLOSE_ID,

		CONTROL_ID,
		GRAPHIC_ID,
		SOUND_ID,
		GAME_ID,

		//CONTROL TAB
		LIST_ID,
	#if __CONTENTS(__080405_FIREST_UI_UPDATE)
		RESET_ID,
	#endif //__080405_FIREST_UI_UPDATE
	};

	enum EXEC_CHECK_ID
	{
		//CONTROL
		CHECK_CONTROL_TAB,
		CHECK_NORMAL_CHAT = CHECK_CONTROL_TAB,	//옵션만
		CHECK_ENTER_CHAT,						//옵션만
//		CHECK_MOUSE_SPEED,						//메세지??
		CHECK_IFEEL,							//UI처리
		KEY_DEFAULT_INIT,

		//GRAPHIC
		CHECK_GRAPHIC_TAB,
//		CHECK_3D = CHECK_GRAPHIC_TAB,			//옵션만
		CHECK_RESOLUTION_800x600 = CHECK_GRAPHIC_TAB,	//해상도 800x600
		CHECK_RESOLUTION_1024x768,						//해상도 1024x768
		CHECK_3D,								//옵션만
		CHECK_ALPHA_HPBAR,						//옵션만
		CHECK_BLOOD_DROP,						//옵션만
		CHECK_AUTOHIDE_SMOOTH,					//옵션만
		CHECK_GAMMA,							//UI처리
		CHECK_CHATBOX,							//옵션만
		CHECK_FPS,								//옵션만
		CHECK_DEFAULT_ALPHA,					//옵션만 ? 혹시 다른 처리도-.-
		CHECK_ALPHA_DEPTH,						//옵션만
		CHECK_DO_NOT_SHOW_PERSNALSHOP_MSG,		// 개인상점 스트링 안보기

		//SOUND
		CHECK_SOUND_TAB,
//		CHECK_YELL = CHECK_SOUND_TAB,			//옵션만
		CHECK_SOUND = CHECK_SOUND_TAB,							//메세지
		CHECK_MUSIC,							//메세지
		CHECK_WAV,								//메세지
		CHECK_MIDI,								//메세지

		//GAME
		CHECK_GAME_TAB,
		CHECK_HELP = CHECK_GAME_TAB,			//옵션만
		CHECK_FILTERING,						//옵션만
		CHECK_PRELOAD_MONSTER,
		CHECK_CHAT_WHITE,						//옵션만
		CHECK_TEEN_VERSION,
		CHECK_POPUPCHAT_BY_WHISPER,
		CHECK_DO_NOT_SHOW_WAR_MSG,				// 전쟁 메시지 보지 않기
		CHECK_DO_NOT_SHOW_LAIR_MSG,				// 레어마스터 메시지 보지 않기
		CHECK_DO_NOT_SHOW_HOLY_LAND_MSG,		// 아담의 성지 메시지 보지 않기

#if __CONTENTS(__JAPAN_UI)
		CHECK_ONE_CLICK_ATTACK_OFF,				//원클릭 일본 역개발
#endif //__JAPAN_UI
#if __CONTENTS(__LANGUAGE_CHANGE)
		CHECK_SHOW_GAMEMONEY_WITH_HANGUL,		// 게임머니 한글 병행 표시
#endif	//__LAVGUAGE_CHANGE
		//CHECK_SHOW_RESOLUTION1024,				// 게임 해상도 // 0 : 800*600  1 : 1024*768

#if __CONTENTS(__GAMEOPTION_ITEMBAY_MESSAGEBOX)
		CHECK_DO_NOT_SHOW_ITEMBAY_MESSAGEBOX,
#endif

//		CHECK_NOT_SEND_MY_INFO,			// 아직.
//		CHECK_CHANGE,							//옵션만
//		CHECK_PARTY_INVITE,						//옵션만
//		CHECK_PARTY_REQUEST,					//옵션만


		//VALUE
		CHECK_VALUE_MOUSE_SPEED,
		CHECK_VALUE_GAMMA,
		CHECK_VALUE_SOUND_VOLUME,
		CHECK_VALUE_MUSIC_VOLUME,

		CHECK_MAX,

		CHECK_CONTROL_MAX = 1,
		CHECK_GRAPHIC_MAX = 10,
		CHECK_SOUND_MAX = 2,

#if __CONTENTS(__GAMEOPTION_ITEMBAY_MESSAGEBOX)
		CHECK_GAME_MAX_SUM_VALUE = 1,
#else
		CHECK_GAME_MAX_SUM_VALUE = 0,
#endif

#if	__CONTENTS(__LANGUAGE_CHANGE) && __CONTENTS(__JAPAN_UI)
		CHECK_GAME_MAX = 11 + CHECK_GAME_MAX_SUM_VALUE,
#elif __CONTENTS(__LANGUAGE_CHANGE) || __CONTENTS(__JAPAN_UI)
		CHECK_GAME_MAX = 10 + CHECK_GAME_MAX_SUM_VALUE,
#else
		CHECK_GAME_MAX = 9 + CHECK_GAME_MAX_SUM_VALUE,
#endif	//__LANGUAGE_CHANGE
	};

	enum MAIN_SPK
	{
		MAIN_WINDOW,
		HOTKEY_WINDOW,

		TAB_CONTROL,
		TAB_GRAPHIC,
		TAB_SOUND,
		TAB_GAME,

	#if __CONTENTS(__080405_FIREST_UI_UPDATE)
		RESET_OPTION,
		RESET_OPTION_HILIGHTED,
		RESET_OPTION_PUSHED,
	#endif //__080405_FIREST_UI_UPDATE
	};

	enum ETC_SPK
	{
		VOLUME_BAR,
		VOLUME_TAG,
		DEFAULT_BUTTON_HILIGHTED,
		DEFAULT_BUTTONHILIGHTED_PUSHED,
		LOAD_BUTTON_HILIGHTED,
		LOAD_BUTTON_HILIGHTED_PUSHED,
		SAVE_BUTTON_HILIGHTED,
		SAVE_BUTTON_HILIGHTED_PUSHED,
		RADIO_BACK_DISABLE,
		RADIO_BACK_ENABLE,
		RADIO_FOCUS,
		CHECK_BACK_DISABLE,
		CHECK_BACK_ENABLE,
		CHECK_FOCUS,
		BUTTON_CLOSE_BACK,
		BUTTON_CLOSE,
		BUTTON_CLOSE_PUSHED,
		BUTTON_CLOSE_HILIGHTED,
		BUTTON_CLOSE_HILIGHTED_PUSHED,
		BUTTON_HELP_BACK,
		BUTTON_HELP,
		BUTTON_HELP_PUSHED,
		BUTTON_HELP_HILIGHTED,
		BUTTON_HELP_HILIGHTED_PUSHED,

	};

	enum CHECK_TYPE
	{
		CHECK_NOT,
		CHECK_CHECK,
		CHECK_CHECK_DISABLE = 0xFFFE,
		CHECK_DISABLE = 0xFFFF,
	};

	enum VALUE_RECT
	{
		RECT_MOUSE_SPEED,
		RECT_GAMMA,
		RECT_SOUND,
		RECT_MUSIC,
		RECT_ALPHA,

		RECT_MAX
	};

	enum TITLE_SPK
	{
		TITLE_MAIN_WINDOW,
		TITLE_HOTKEY_WINDOW,

		TITLE_TAB_CONTROL_HILIGHT,
		TITLE_TAB_GRAPHIC_HILIGHT,
		TITLE_TAB_SOUND_HILIGHT,
		TITLE_TAB_GAME_HILIGHT,

		TITLE_TAB_CONTROL_PUSH,
		TITLE_TAB_GRAPHIC_PUSH,
		TITLE_TAB_SOUND_PUSH,
		TITLE_TAB_GAME_PUSH,

		TITLE_VOLUME_BAR,
		TITLE_VOLUME_TAG,

		TITLE_RADIO_BACK,
		TITLE_RADIO_FOCUS,

		TITLE_CHECK_BACK,
		TITLE_CHECK_FOCUS,

		TITLE_BUTTON_EXIT_HILIGHT,
		TITLE_BUTTON_EXIT_PUSH,

		TITLE_BUTTON_RESET,
		TITLE_BUTTON_RESET_HILIGHT,
		TITLE_BUTTON_RESET_PUSH,

		TITLE_BUTTON_EXIT,
	};
private:

	C_VS_UI_DIALOG	*			m_pC_dialog;
	C_VS_UI_SCROLL_BAR			*m_pC_scroll_bar;
	bool						m_bLBPush;

	int							m_focus_hotkey;

	CHECK_TYPE					m_check[CHECK_MAX];

	C_SPRITE_PACK	*			m_pC_main_spk;
	C_SPRITE_PACK	*			m_pC_etc_spk;

	ButtonGroup *				m_pC_button_group;
	ButtonGroup *				m_pC_control_button_group;
	ButtonGroup *				m_pC_graphic_button_group;
	ButtonGroup *				m_pC_sound_button_group;
	ButtonGroup *				m_pC_game_button_group;

	Rect						m_rt_value[RECT_MAX];
	int							m_value_mouse_speed, m_value_gamma, m_volume_sound, m_volume_music;

	int							m_check_x, m_check_y, m_check_gap;
	int							m_i_selected_tab;
	int							m_vampire_plus_x, m_vampire_plus_y;

	void						SetValue(int _x, enum VALUE_RECT rect_value);

	bool						m_IsTitle;
	int							Tab_X[4];
	int							Tab_Y;
public:
	C_VS_UI_OPTION(bool IsTitle = false);
	~C_VS_UI_OPTION();

	void	AcquireDisappear() {}
	void	CancelPushState() 
	{
		m_pC_button_group->CancelPushState();
		m_pC_control_button_group->CancelPushState();
		m_pC_graphic_button_group->CancelPushState();
		m_pC_sound_button_group->CancelPushState();
		m_pC_game_button_group->CancelPushState();
		m_pC_scroll_bar->CancelPushState();
	}

	void	AcquireFirstSequence();
	void	UnacquireMouseFocus();
	void	WindowEventReceiver(id_t event);
	bool	IsPixel(int _x, int _y);

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button);
	void	Run(id_t id);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);
	void	Show();
	void	Process();
	void	Start();
	void	Finish();
	void	Background_Music_ONOFF( EXEC_CHECK_ID check_id);
	void	Effect_Music_ONOFF(EXEC_CHECK_ID check_id);

	//20071214 - Option Check Funtion
	void	SetOptionCheck (EXEC_CHECK_ID opt, CHECK_TYPE check) { if (opt >=0 && opt<CHECK_MAX) m_check[opt] = check; }

};


//-----------------------------------------------------------------------------
// C_VS_UI_TITLE
//
// 
//-----------------------------------------------------------------------------
class C_VS_UI_TITLE : public Window, public Exec, public ButtonVisual
{
private:
	//---------------------------------------
	// Components
	//---------------------------------------
	C_VS_UI_LOGIN *				m_pC_login;
//	C_VS_UI_NEWUSER *			m_pC_newuser;
	C_VS_UI_CHAR_MANAGER *		m_pC_char_manager;
	C_VS_UI_SERVER_SELECT *		m_pC_server_select;
	
	LineEditorVisual			m_lev_id;
	LineEditorVisual			m_lev_password;
	std::string					m_lev_id_backup;
	

	//add by hays
	C_SPRITE_PACK				m_title_new_spk;

	C_SPRITE_PACK				m_title_spk;
	C_SPRITE_PACK				m_title_menu_default;
	C_SPRITE_PACK				m_title_menu_select;
	C_SPRITE_PACK *				m_pC_credit;
	C_SPRITE_PACK 				m_pC_title_ani;
//	C_SPRITE_PACK				m_pC_symbol_ani;
	C_SPRITE_PACK *				m_pC_use_grade;
	CTickTimer *				m_pAnimationTimer;
	int							m_aniArpha;
	bool						m_bAniArphaUp;


	C_VS_UI_DIALOG *			m_pC_dialog;
	

	enum TITLE_MENU
	{ 
		CONNECT = 0,
//		TUTORIAL,
		OPTION,
//		INTRO,
		CREDIT,
		EXIT,
		NEWID,

		INVALID_ID,
	};

	enum TITLE_SPK
	{ 
		CONNECT_HILIGHT = 0,
		CONNECT_PUST,
		OPTION_HILIGHT,
		OPTION_PUSH,
		CREDIT_HILIGHT,
		CREDIT_PUSH,
		EXIT_HILIGHT,
		EXIT_PUSH,
		NEWID_HILIGHT,
		NEWID_PUSH,
	};


	enum USEGRADE
	{
		CHILD,
		//TEENAGER,
		ADULT,
		VIOLENCE,
		FEAR,
	};

	enum	INTERFACE_XY
	{
		TITLE_BACK_GROUND_800_600,
		TITLE_BACK_GROUND_1024_768,
		//TITLE_BACK_GROUND_1280_720,
		TITLE_BACK_GROUND_1280_960,
		TITLE_BACK_GROUND_1280_1024,
		BUTTON_LAYOUT_BUTTON,
		TEXT_IMAGE,
		ANI_MARK_BUTTON,
	};

	enum	EFFECT_INDEX
	{
		EFFECT_INDEX_WARTER_LIGHT,
	};
	enum	CREDIT_SPK_ID
	{
		BACKGROUND_800_600,
		BACKGROUND_1024_768,
		BACKGROUND_1280_720,
		BACKGROUND_1280_960,
		BACKGROUND_1280_1024,
		CREATORS_SCROLL,
		COPYRIGHT,

	};


	C_VS_UI_ASK_DIALOG*			m_pC_use_askCheckToEnterServer ; 
	ButtonGroup *				m_pC_button_group;
	bool						m_bl_credit;
	DWORD						m_dw_prev_tickcount;
	DWORD						m_dw_millisec;
	int							m_credit_scroll;
	int							m_iWarmingTextIndex;
	
	bool	Timer();
	bool	ReadySend();
	void	ChangeFocus();
	void	SendLoginToClient();

public:
	C_VS_UI_TITLE();
	~C_VS_UI_TITLE();

	// 넷마블용
	void	RunConnect()			{ if(m_pC_login) m_pC_login->Start(); }

	void	RunCannotPlayMessage();
	void	RunCannotPlayByAttrMessage();

	void	SelectCharacter(int n)	{ if(m_pC_char_manager)m_pC_char_manager->SelectSlot(n); }
//	void	UsedID(bool used)	{ if(m_pC_char_manager)m_pC_char_manager->UsedID(used); }

#if __CONTENTS(__SERVER_SELECT_REVEWAL)
	void	SetServerList(LPSTR *name, int *id, int *status, int size, int default_id, bool *nonpk = NULL, 
							WORD *pwSlayer = NULL, WORD *pwVampire = NULL, WORD *pwOusters = NULL)	{
		if(m_pC_server_select)m_pC_server_select->SetServerList(name, id, status, size, default_id, nonpk, pwSlayer, pwVampire, pwOusters);
	}

#else
	void	SetServerList(LPSTR *name, int *id, int *status, int size, int default_id, bool *nonpk = NULL)	{
		if(m_pC_server_select)m_pC_server_select->SetServerList(name, id, status, size, default_id, nonpk);
	}
#endif	//__SERVER_SELECT_REVEWAL

//	void	CloseUserRegistrationWindow();
//	void	RunNewUserRegistration();
//	void	CloseCharInfo();
	void	CancelPushState() { m_pC_button_group->CancelPushState(); }
	void	WindowEventReceiver(id_t event);
	bool	IsPixel(int _x, int _y);
	void	AcquireMouseFocus();
	void	UnacquireMouseFocus();
	void	AcquireFirstSequence();
	void	AcquireDisappear() {}

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button);
	void	Run(id_t id);
	void	Show();
	void	Process();
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);
	void	Start();
	void	Finish();
	void	StartCharacterManager(bool back = false);
	void	StartServerSelect(bool bGroup);
	void	SetCharacter(int slot, S_SLOT &S_slot);
	void	ClearAllCharacter();
	void	NewCharacterCreateOk();
	void	NewCharacterCreateFailed(int error);
	void	DeleteCharacter(int slot);
	void	PopupNetmarbleAgreementMessage();
	
	void	RunAskCheckToEnterServerDialog(int AskType ,  int value) ; 
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON * p_button);

	void	Init_TitleUIInterface_InfInfo();	
	//.inf에서 타이틀 UI의 정보를 설정 한다. (UI 설정을 바로 확인 할 수 있도록.)

private:

	WORD	m_wAni_Mark_X;
	WORD	m_wAni_Mark_Y;

	WORD	m_wButton_Layout_X;
	WORD	m_wButton_Layout_Y;

	WORD	m_wID_Edit_X;
	WORD	m_wID_Edit_Y;

	WORD	m_wPW_Edit_X;
	WORD	m_wPW_Edit_Y;

	WORD	m_wGame_Run_X;
	WORD	m_wGame_Run_Y;

	WORD	m_wID_Create_X;
	WORD	m_wID_Create_Y;

	WORD	m_wOption_X;
	WORD	m_wOption_Y;

	WORD	m_wGame_Creaters_X;
	WORD	m_wGame_Creaters_Y;

	WORD	m_wGame_Exit_X;
	WORD	m_wGame_Exit_Y;

	WORD	m_wEffect_Warter_Light_X;
	WORD	m_wEffect_Warter_Light_Y;

	WORD	m_wText_Image_X;
	WORD	m_wText_Image_Y;

	WORD	m_wChild_X;
	WORD	m_wChild_Y;

	WORD	m_wAdult_X;
	WORD	m_wAdult_Y;

	WORD	m_wViolence_X;
	WORD	m_wViolence_Y;

	WORD	m_wFear_X;
	WORD	m_wFear_Y;

	WORD	m_wWorningString_X;
	WORD	m_wWorningString_Y;
	//
	// gamemenu option
//	void	RunOption();
//	void	CloseOption();
//	bool	IsRunningOption(){ return (m_pC_option != NULL); }	// by larosel
};

//-----------------------------------------------------------------------------
// C_VS_UI_CHAR_DELETE
//
// 
//-----------------------------------------------------------------------------
class C_VS_UI_GO_BILING_PAGE : public Window, public Exec, public ButtonVisual
{
public :
	enum BILING_MSG_LIST 
	{
		CANNOT_PLAY_MSG = 0,
		CANNOT_PLAY_BY_ATTR_MSG,

		BILING_MSG_MAX,
		BILING_MSG_NULL,
	};
private:
	enum BILING_MENU
	{
		BILING_OK,
		BILING_CANCEL,
	};
	
	ButtonGroup *				m_pC_button_group;
	BILING_MSG_LIST				m_biling_mode;

public:
	C_VS_UI_GO_BILING_PAGE(BILING_MSG_LIST msg);
	~C_VS_UI_GO_BILING_PAGE();

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON * p_button);
	void	UnacquireMouseFocus() { m_pC_button_group->UnacquireMouseFocus(); }
	void	CancelPushState() { m_pC_button_group->CancelPushState(); }
	void	AcquireDisappear() {}
	void	WindowEventReceiver(id_t event);
	bool	IsPixel(int _x, int _y);

	void	Start();
	void	Finish();
	void	Process();
	void	Show();
	void	Run(id_t id);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);	
};


//-----------------------------------------------------------------------------
// C_VS_UI_CHAR_DELETE
//
// 
//-----------------------------------------------------------------------------
class C_VS_UI_NETMARBLE_AGREEMENT : public Window, public Exec, public ButtonVisual
{
private :
	ButtonGroup *				m_pC_button_group;

	enum BUTTON_ID
	{
		BUTTON_OK,
		CHECK,
	};

	enum ETC_SPK
	{
		VOLUME_BAR,
		VOLUME_TAG,
		DEFAULT_BUTTON_HILIGHTED,
		DEFAULT_BUTTONHILIGHTED_PUSHED,
		LOAD_BUTTON_HILIGHTED,
		LOAD_BUTTON_HILIGHTED_PUSHED,
		SAVE_BUTTON_HILIGHTED,
		SAVE_BUTTON_HILIGHTED_PUSHED,
		RADIO_BACK_DISABLE,
		RADIO_BACK_ENABLE,
		RADIO_FOCUS,
		CHECK_BACK_DISABLE,
		CHECK_BACK_ENABLE,
		CHECK_FOCUS,
		BUTTON_CLOSE_BACK,
		BUTTON_CLOSE,
		BUTTON_CLOSE_PUSHED,
		BUTTON_CLOSE_HILIGHTED,
		BUTTON_CLOSE_HILIGHTED_PUSHED,
		BUTTON_HELP_BACK,
		BUTTON_HELP,
		BUTTON_HELP_PUSHED,
		BUTTON_HELP_HILIGHTED,
		BUTTON_HELP_HILIGHTED_PUSHED,

	};
	C_SPRITE_PACK	*			m_pC_etc_spk;
	bool	m_bCheck;

public:
	C_VS_UI_NETMARBLE_AGREEMENT();
	~C_VS_UI_NETMARBLE_AGREEMENT();

	void	ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button);
	void	ShowButtonDescription(C_VS_UI_EVENT_BUTTON * p_button);
	void	UnacquireMouseFocus() { m_pC_button_group->UnacquireMouseFocus(); }
	void	CancelPushState() { m_pC_button_group->CancelPushState(); }
	void	AcquireDisappear() {}
	void	WindowEventReceiver(id_t event);
	bool	IsPixel(int _x, int _y);

	void	Start();
	void	Finish();
	void	Process();
	void	Show();
	void	Run(id_t id);
	bool	MouseControl(UINT message, int _x, int _y);
	void	KeyboardControl(UINT message, UINT key, long extra);	
};


#endif //__TITLE_UI_RENWEAL

#endif
