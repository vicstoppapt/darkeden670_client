//---------------------------------------------------------------------------
// InitHelpManager.cpp
//---------------------------------------------------------------------------

#include "MHelpManager.h"
#include "MFileDef.h"
#include <fstream>
#include "packet/Properties.h"

//---------------------------------------------------------------------------
// Node생성
//---------------------------------------------------------------------------
#define LP_COMPARE(pt)				((MCompareHelpNode*)(pt))
#define LP_OUTPUT(pt)				((MOutputHelpNode*)(pt))
#define NEW_COMPARE(helpCompare)	new MCompareHelpNode( helpCompare )
#define NEW_OUTPUT					new MOutputHelpNode()

//---------------------------------------------------------------------------
// Node의 종류
//---------------------------------------------------------------------------
#define	NODE_ROOT					pHelpNode
#define NODE_T						LP_COMPARE(NODE_ROOT)->GetTrue()
#define NODE_F						LP_COMPARE(NODE_ROOT)->GetFalse()
#define NODE_TT						LP_COMPARE(NODE_T)->GetTrue()
#define NODE_TF						LP_COMPARE(NODE_T)->GetFalse()
#define NODE_FT						LP_COMPARE(NODE_F)->GetTrue()
#define NODE_FF						LP_COMPARE(NODE_F)->GetFalse()
#define NODE_TTT					LP_COMPARE(NODE_TT)->GetTrue()
#define NODE_TTF					LP_COMPARE(NODE_TT)->GetFalse()
#define NODE_TFT					LP_COMPARE(NODE_TF)->GetTrue()
#define NODE_TFF					LP_COMPARE(NODE_TF)->GetFalse()
#define NODE_FTT					LP_COMPARE(NODE_FT)->GetTrue()
#define NODE_FTF					LP_COMPARE(NODE_FT)->GetFalse()
#define NODE_FFT					LP_COMPARE(NODE_FF)->GetTrue()
#define NODE_FFF					LP_COMPARE(NODE_FF)->GetFalse()
#define NODE_TTTT					LP_COMPARE(NODE_TTT)->GetTrue()
#define NODE_TTTF					LP_COMPARE(NODE_TTT)->GetFalse()
#define NODE_TTFT					LP_COMPARE(NODE_TTF)->GetTrue()
#define NODE_TTFF					LP_COMPARE(NODE_TTF)->GetFalse()
#define NODE_TFTT					LP_COMPARE(NODE_TFT)->GetTrue()
#define NODE_TFTF					LP_COMPARE(NODE_TFT)->GetFalse()
#define NODE_TFFT					LP_COMPARE(NODE_TFF)->GetTrue()
#define NODE_TFFF					LP_COMPARE(NODE_TFF)->GetFalse()
#define NODE_FTTT					LP_COMPARE(NODE_FTT)->GetTrue()
#define NODE_FTTF					LP_COMPARE(NODE_FTT)->GetFalse()
#define NODE_FTFT					LP_COMPARE(NODE_FTF)->GetTrue()
#define NODE_FTFF					LP_COMPARE(NODE_FTF)->GetFalse()
#define NODE_FFTT					LP_COMPARE(NODE_FFT)->GetTrue()
#define NODE_FFTF					LP_COMPARE(NODE_FFT)->GetFalse()
#define NODE_FFFT					LP_COMPARE(NODE_FFF)->GetTrue()
#define NODE_FFFF					LP_COMPARE(NODE_FFF)->GetFalse()
#define NODE_TTTTT					LP_COMPARE(NODE_TTTT)->GetTrue()
#define NODE_TTTTF					LP_COMPARE(NODE_TTTT)->GetFalse()
#define NODE_TTTFT					LP_COMPARE(NODE_TTTF)->GetTrue()
#define NODE_TTTFF					LP_COMPARE(NODE_TTTF)->GetFalse()
#define NODE_TTFTT					LP_COMPARE(NODE_TTFT)->GetTrue()
#define NODE_TTFTF					LP_COMPARE(NODE_TTFT)->GetFalse()
#define NODE_TTFFT					LP_COMPARE(NODE_TTFF)->GetTrue()
#define NODE_TTFFF					LP_COMPARE(NODE_TTFF)->GetFalse()
#define NODE_TFTTT					LP_COMPARE(NODE_TFTT)->GetTrue()
#define NODE_TFTTF					LP_COMPARE(NODE_TFTT)->GetFalse()
#define NODE_TFTFT					LP_COMPARE(NODE_TFTF)->GetTrue()
#define NODE_TFTFF					LP_COMPARE(NODE_TFTF)->GetFalse()
#define NODE_TFFTT					LP_COMPARE(NODE_TFFT)->GetTrue()
#define NODE_TFFTF					LP_COMPARE(NODE_TFFT)->GetFalse()
#define NODE_TFFFT					LP_COMPARE(NODE_TFFF)->GetTrue()
#define NODE_TFFFF					LP_COMPARE(NODE_TFFF)->GetFalse()
#define NODE_FTTTT					LP_COMPARE(NODE_FTTT)->GetTrue()
#define NODE_FTTTF					LP_COMPARE(NODE_FTTT)->GetFalse()
#define NODE_FTTFT					LP_COMPARE(NODE_FTTF)->GetTrue()
#define NODE_FTTFF					LP_COMPARE(NODE_FTTF)->GetFalse()
#define NODE_FTFTT					LP_COMPARE(NODE_FTFT)->GetTrue()
#define NODE_FTFTF					LP_COMPARE(NODE_FTFT)->GetFalse()
#define NODE_FTFFT					LP_COMPARE(NODE_FTFF)->GetTrue()
#define NODE_FTFFF					LP_COMPARE(NODE_FTFF)->GetFalse()
#define NODE_FFTTT					LP_COMPARE(NODE_FFTT)->GetTrue()
#define NODE_FFTTF					LP_COMPARE(NODE_FFTT)->GetFalse()
#define NODE_FFTFT					LP_COMPARE(NODE_FFTF)->GetTrue()
#define NODE_FFTFF					LP_COMPARE(NODE_FFTF)->GetFalse()
#define NODE_FFFTT					LP_COMPARE(NODE_FFFT)->GetTrue()
#define NODE_FFFTF					LP_COMPARE(NODE_FFFT)->GetFalse()
#define NODE_FFFFT					LP_COMPARE(NODE_FFFF)->GetTrue()
#define NODE_FFFFF					LP_COMPARE(NODE_FFFF)->GetFalse()


//---------------------------------------------------------------------------
// Node설정
//---------------------------------------------------------------------------
#define	SET_TRUE_COMPARE(helpCompare)		SetTrue( NEW_COMPARE( helpCompare ) )
#define	SET_FALSE_COMPARE(helpCompare)		SetFalse( NEW_COMPARE( helpCompare ) )
#define	SET_TRUE_OUTPUT						SetTrue( NEW_OUTPUT )
#define	SET_FALSE_OUTPUT					SetFalse( NEW_OUTPUT )
#define ADD_OUTPUT(helpOutput)				push_back( helpOutput )



//---------------------------------------------------------------------------
// Init HelpManager
//---------------------------------------------------------------------------
BOOL
InitHelpManager()
{
//	if (g_pHelpManager==NULL)
//	{
//		g_pHelpManager = new MHelpManager;
//	}
//
//	g_pHelpManager->Release();
//
//	g_pHelpManager->Init( MAX_HELP_EVENT );
//
//	MHelpNode* NODE_ROOT = NULL;
//
//
//	//------------------------------------------------------------------
//	// HE_TIME_PASSED,					// 시간이 지날 때 -_-;
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_COMPARE( HC_PLAYER_IN_SHOP );
//		// shop에 있는 경우
//		LP_COMPARE(NODE_ROOT)->SET_TRUE_OUTPUT;
//			LP_OUTPUT(NODE_T)->ADD_OUTPUT( HO_CLICK_ITEM_TO_BUY );
//			LP_OUTPUT(NODE_T)->ADD_OUTPUT( HO_CLICK_BAR_TO_CHANGE_ITEM_TYPE );	// normal/special
//			LP_OUTPUT(NODE_T)->ADD_OUTPUT( HO_NORMAL_ITEM_IS_BASIC_ITEM );
//			LP_OUTPUT(NODE_T)->ADD_OUTPUT( HO_SPECIAL_ITEM_IS_GOOD );
//			LP_OUTPUT(NODE_T)->ADD_OUTPUT( HO_YOU_CANNOT_USE_RED_ITEM );
//
//		// repair하는 경우
//		LP_COMPARE(NODE_ROOT)->SET_FALSE_COMPARE( HC_PLAYER_IN_REPAIR );
//			LP_COMPARE(NODE_F)->SET_TRUE_OUTPUT;
//				LP_OUTPUT(NODE_FT)->ADD_OUTPUT( HO_CLICK_ITEM_TO_REPAIR );
//				LP_OUTPUT(NODE_FT)->ADD_OUTPUT( HO_REPAIR_COST_IS_UP_TO_DURABILITY );
//
//			// 보관하는 경우
//			LP_COMPARE(NODE_F)->SET_FALSE_COMPARE( HC_PLAYER_IN_STORAGE );
//				LP_COMPARE(NODE_FF)->SET_TRUE_OUTPUT;
//					LP_OUTPUT(NODE_FFT)->ADD_OUTPUT( HO_CLICK_ITEM_TO_REPAIR );
//					LP_OUTPUT(NODE_FFT)->ADD_OUTPUT( HO_REPAIR_COST_IS_UP_TO_DURABILITY );
//
//				// 교환중인 경우
//				LP_COMPARE(NODE_FF)->SET_FALSE_COMPARE( HC_PLAYER_IN_TRADE );
//					LP_COMPARE(NODE_FFF)->SET_TRUE_OUTPUT;
//						LP_OUTPUT(NODE_FFFT)->ADD_OUTPUT( HO_RIGHTCLICK_ITEM_TO_ADD_TRADE );
//						LP_OUTPUT(NODE_FFFT)->ADD_OUTPUT( HO_RIGHTCLICK_ITEM_TO_SHOW );
//						LP_OUTPUT(NODE_FFFT)->ADD_OUTPUT( HO_ONLY_HIGH_LIGHTED_ITEM_WILL_TRADE );						
//						LP_OUTPUT(NODE_FFFT)->ADD_OUTPUT( HO_MONEY_AND_HIGH_LIGHTED_ITEM_AND_OTHER_INVENTORY_ITEM_WILL_TRADE );
//
//					// 정상적인 게임 중인 경우
//					LP_COMPARE(NODE_FFF)->SET_FALSE_COMPARE( HC_PLAYER_IN_NORMAL_GAME_MODE );
//						LP_COMPARE(NODE_FFFF)->SET_TRUE_OUTPUT;
//							LP_OUTPUT(NODE_FFFFT)->ADD_OUTPUT( HO_CTRL_H_TO_BASIC_HELP );														
//							LP_OUTPUT(NODE_FFFFT)->ADD_OUTPUT( HO_CLICK_PRESS_TO_AUTO_ACTION );
//							
//
//	(*g_pHelpManager)[HE_TIME_PASSED] = NODE_ROOT;					// 시간이 지날 때 -_-;
//
//
//	//------------------------------------------------------------------
//	// HE_CREATURE_APPEAR_MONSTER		// 몹이 나타날때
//	//------------------------------------------------------------------
//	// player가 slayer라면 경고 메세지.. -_-;
//	NODE_ROOT = NEW_COMPARE( HC_PLAYER_IS_SLAYER );
//		LP_COMPARE(NODE_ROOT)->SET_TRUE_OUTPUT;
//			LP_OUTPUT(NODE_T)->ADD_OUTPUT( HO_CLICK_MONSTER_TO_ATTACK );
//			LP_OUTPUT(NODE_T)->ADD_OUTPUT( HO_CLICK_PRESS_TO_AUTO_ACTION );
//
//	(*g_pHelpManager)[HE_CREATURE_APPEAR_MONSTER] = NODE_ROOT;		// 몹이 나타날때
//	
//
//	//------------------------------------------------------------------
//	// HE_CREATURE_APPEAR_NPC			// NPC 나타날때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_CLICK_NPC_TO_TRADE );
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_NPC_OUTLINE_COLOR_IS_GREEN );
//
//	(*g_pHelpManager)[HE_CREATURE_APPEAR_NPC] = NODE_ROOT;		// NPC 나타날때
//
//
//	//------------------------------------------------------------------
//	// HE_CREATURE_APPEAR_VAMPIRE		// Vampire 나타날때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_COMPARE( HC_PLAYER_IS_SLAYER );
//		LP_COMPARE(NODE_ROOT)->SET_TRUE_OUTPUT;
//			LP_OUTPUT(NODE_T)->ADD_OUTPUT( HO_VAMPIRE_IS_DANGEROUS );
//			LP_OUTPUT(NODE_T)->ADD_OUTPUT( HO_VAMPIRE_IS_OTHER_PLAYER );
//
//	(*g_pHelpManager)[HE_CREATURE_APPEAR_VAMPIRE] = NODE_ROOT;		// Vampire 나타날때
//
//
//	//------------------------------------------------------------------
//	// HE_CREATURE_APPEAR_SLAYER		// Slayer가 나타날때	
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_COMPARE( HC_PLAYER_IS_VAMPIRE );
//		LP_COMPARE(NODE_ROOT)->SET_TRUE_OUTPUT;
//			LP_OUTPUT(NODE_T)->ADD_OUTPUT( HO_ATTACK_SLAYER_TO_DRAIN );
//			
//	(*g_pHelpManager)[HE_CREATURE_APPEAR_SLAYER] = NODE_ROOT;		// Slayer가 나타날때	
//	
//
//	//------------------------------------------------------------------
//	// HE_SKILL_CAN_LEARN_SWORD		// 검 Skill을 배울 수 있을 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_WHERE_CAN_LEARN_SWORD_SKILL );
//
//	(*g_pHelpManager)[HE_SKILL_CAN_LEARN_SWORD] = NODE_ROOT;		// 검 Skill을 배울 수 있을 때
//
//
//	//------------------------------------------------------------------
//	// HE_SKILL_CAN_LEARN_BLADE		// 도 Skill을 배울 수 있을 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_WHERE_CAN_LEARN_BLADE_SKILL );
//	
//	(*g_pHelpManager)[HE_SKILL_CAN_LEARN_BLADE] = NODE_ROOT;		// 도 Skill을 배울 수 있을 때
//
//	//------------------------------------------------------------------
//	// HE_SKILL_CAN_LEARN_GUN		// 총 Skill을 배울 수 있을 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_WHERE_CAN_LEARN_GUN_SKILL );
//
//	(*g_pHelpManager)[HE_SKILL_CAN_LEARN_GUN] = NODE_ROOT;		// 총 Skill을 배울 수 있을 때
//
//
//	//------------------------------------------------------------------
//	// HE_SKILL_CAN_LEARN_HEAL		// 힐 Skill을 배울 수 있을 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_WHERE_CAN_LEARN_HEAL_SKILL );
//	
//	(*g_pHelpManager)[HE_SKILL_CAN_LEARN_HEAL] = NODE_ROOT;		// 힐 Skill을 배울 수 있을 때
//
//
//	//------------------------------------------------------------------
//	// HE_SKILL_CAN_LEARN_ENCHANT		// 인챈트 Skill을 배울 수 있을 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_WHERE_CAN_LEARN_ENCHANT_SKILL );
//	
//	(*g_pHelpManager)[HE_SKILL_CAN_LEARN_ENCHANT] = NODE_ROOT;		// 인챈트 Skill을 배울 수 있을 때
//
//
//	//------------------------------------------------------------------
//	// HE_SKILL_CAN_LEARN_VAMPIRE		// 뱀파이어 SKill을 배울 수 있을 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_WHERE_CAN_LEARN_VAMPIRE_SKILL );
//	
//	(*g_pHelpManager)[HE_SKILL_CAN_LEARN_VAMPIRE] = NODE_ROOT;		// 뱀파이어 SKill을 배울 수 있을 때
//
//
//	//------------------------------------------------------------------
//	// HE_SKILL_LEARNED				// Skill을 배웠을 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_COMPARE( HC_NO_SKILL_SELECTED );
//		LP_COMPARE(NODE_ROOT)->SET_TRUE_OUTPUT;
//			LP_OUTPUT(NODE_T)->ADD_OUTPUT( HO_HOW_TO_USE_SKILL );
//
//	(*g_pHelpManager)[HE_SKILL_LEARNED] = NODE_ROOT;		// Skill을 배웠을 때
//
//
//	//------------------------------------------------------------------
//	// HE_SKILL_ICON_CHANGE			// 기술 아이콘 바뀔 때	
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_COMPARE( HC_NO_SKILL_FUNCTION_KEY_DEFINED );
//		LP_COMPARE(NODE_ROOT)->SET_TRUE_OUTPUT;
//			LP_OUTPUT(NODE_T)->ADD_OUTPUT( HO_USE_FUNCTION_KEY_TO_SELECT_SKILL );		
//			
//	(*g_pHelpManager)[HE_SKILL_ICON_CHANGE] = NODE_ROOT;		// 기술 아이콘 바뀔 때	
//
//
//	//------------------------------------------------------------------
//	// HE_EFFECT_BLOOD_DRAIN			// 흡혈 당했을 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_COMPARE( HC_NO_SKILL_FUNCTION_KEY_DEFINED );
//		LP_COMPARE(NODE_ROOT)->SET_TRUE_OUTPUT;
//			LP_OUTPUT(NODE_T)->ADD_OUTPUT( HO_HOW_TO_CURE_BLOOD_DRAIN );
//			LP_OUTPUT(NODE_T)->ADD_OUTPUT( HO_YOU_MORPH_TO_VAMPIRE_IN_12_HOURS );
//
//	(*g_pHelpManager)[HE_EFFECT_BLOOD_DRAIN] = NODE_ROOT;		// 흡혈 당했을 때
//
//
//	//------------------------------------------------------------------
//	// HE_EFFECT_GREEN_POISON			// Green Poison걸렸을 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_EFFECT_GREEN_POISON );
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_HOW_TO_CURE_GREEN_POISON );
//
//	(*g_pHelpManager)[HE_EFFECT_GREEN_POISON] = NODE_ROOT;		// Green Poison걸렸을 때
//
//
//	//------------------------------------------------------------------
//	// HE_EFFECT_YELLOW_POISON		// Yellow Poison걸렸을 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_EFFECT_YELLOW_POISON );
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_HOW_TO_CURE_YELLOW_POISON );
//
//	(*g_pHelpManager)[HE_EFFECT_YELLOW_POISON] = NODE_ROOT;		// Yellow Poison걸렸을 때
//
//
//	//------------------------------------------------------------------
//	// HE_EFFECT_PURPLE_WALL			// Purple Wall걸렸을 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_EFFECT_PURPLE_WALL );
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_HOW_TO_CURE_PURPLE_WALL );
//
//	(*g_pHelpManager)[HE_EFFECT_PURPLE_WALL] = NODE_ROOT;		// Purple Wall걸렸을 때
//
//
//	//------------------------------------------------------------------
//	// HE_EFFECT_BLESS				// Bless걸렸을 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_EFFECT_BLESS );
//
//	(*g_pHelpManager)[HE_EFFECT_BLESS] = NODE_ROOT;		// Bless걸렸을 때
//
//
//	//------------------------------------------------------------------
//	// HE_EFFECT_STRIKING				// Striking걸렸을 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_EFFECT_STRIKING );
//
//	(*g_pHelpManager)[HE_EFFECT_STRIKING] = NODE_ROOT;		// Striking걸렸을 때
//
//
//	//------------------------------------------------------------------
//	// HE_EFFECT_BURROW				// Burrow하고 나서
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_EFFECT_BURROW );
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_HOW_TO_UNBURROW );
//
//	(*g_pHelpManager)[HE_EFFECT_BURROW] = NODE_ROOT;		// Burrow하고 나서
//
//
//	//------------------------------------------------------------------
//	// HE_STATUS_HP_LOW				// HP가 낮을 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_COMPARE( HC_HAS_HEAL_POTION_IN_BELT );
//		LP_COMPARE(NODE_ROOT)->SET_TRUE_OUTPUT;
//			LP_OUTPUT(NODE_T)->ADD_OUTPUT( HO_USE_HP_POTION_IN_BELT );
//		
//		LP_COMPARE(NODE_ROOT)->SET_FALSE_COMPARE( HC_HAS_HEAL_POTION_IN_INVENTORY );
//			LP_COMPARE(NODE_F)->SET_TRUE_OUTPUT;
//				LP_OUTPUT(NODE_FT)->ADD_OUTPUT( HO_USE_HP_POTION_IN_INVENTORY );
//
//			LP_COMPARE(NODE_F)->SET_FALSE_OUTPUT;
//				LP_OUTPUT(NODE_FF)->ADD_OUTPUT( HO_HOW_TO_GET_HEAL_POTION );
//				LP_OUTPUT(NODE_FF)->ADD_OUTPUT( HO_HEAL_POTION_CAN_HEAL );
//				LP_OUTPUT(NODE_FF)->ADD_OUTPUT( HO_YOU_WILL_DIE_WHEN_HP_ZERO );
//
//	(*g_pHelpManager)[HE_STATUS_HP_LOW] = NODE_ROOT;		// HP가 낮을 때
//
//
//	//------------------------------------------------------------------
//	// HE_STATUS_MP_LOW				// MP가 낮을 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_COMPARE( HC_HAS_MANA_POTION_IN_BELT );
//		LP_COMPARE(NODE_ROOT)->SET_TRUE_OUTPUT;
//			LP_OUTPUT(NODE_T)->ADD_OUTPUT( HO_USE_MANA_POTION_IN_BELT );
//		
//		LP_COMPARE(NODE_ROOT)->SET_FALSE_COMPARE( HC_HAS_MANA_POTION_IN_INVENTORY );
//			LP_COMPARE(NODE_F)->SET_TRUE_OUTPUT;
//				LP_OUTPUT(NODE_FT)->ADD_OUTPUT( HO_USE_MANA_POTION_IN_INVENTORY );
//
//			LP_COMPARE(NODE_F)->SET_FALSE_OUTPUT;
//				LP_OUTPUT(NODE_FF)->ADD_OUTPUT( HO_HOW_TO_GET_MANA_POTION );
//				LP_OUTPUT(NODE_FF)->ADD_OUTPUT( HO_MANA_POTION_CAN_FILL_MANA );
//				LP_OUTPUT(NODE_FF)->ADD_OUTPUT( HO_YOU_CANT_USE_SKILL_LACK_OF_MANA );
//
//	(*g_pHelpManager)[HE_STATUS_MP_LOW] = NODE_ROOT;		// MP가 낮을 때
//
//
//	//------------------------------------------------------------------
//	// HE_STATUS_BONUS_POINT			// 보너스 point생겼을때		
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_COMPARE( HC_RECEIVE_FIRST_BONUS_POINT );
//		LP_COMPARE(NODE_ROOT)->SET_TRUE_OUTPUT;
//			LP_OUTPUT(NODE_T)->ADD_OUTPUT( HO_CLICK_TO_PLUS_STATUS );
//
//	(*g_pHelpManager)[HE_STATUS_BONUS_POINT] = NODE_ROOT;		// 보너스 point생겼을때		
//
//
//	//------------------------------------------------------------------
//	// HE_TRADE_REQUESTED				// 교환신청 받을 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_OK_TO_ACCEPT_TRADE );
//
//	(*g_pHelpManager)[HE_TRADE_REQUESTED] = NODE_ROOT;		// 교환신청 받을 때
//
//
//	//------------------------------------------------------------------
//	// HE_TRADE_REQUEST				// 교환신청 하고 나서
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_CANCEL_TO_CANCEL_TRADE );
//
//	(*g_pHelpManager)[HE_TRADE_REQUEST] = NODE_ROOT;		// 교환신청 하고 나서
//
//
//	//------------------------------------------------------------------
//	// HE_TRADE_ITEM_ADD				// 교환중에 아이템 추가
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_RECLICK_ITEM_TO_REMOVE_TRADE );
//
//	(*g_pHelpManager)[HE_TRADE_ITEM_ADD] = NODE_ROOT;		// 교환중에 아이템 추가
//
//
//	//------------------------------------------------------------------
//	// HE_TRADE_ITEM_REMOVE			// 교환중에 아이템 제거	
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_ONLY_HIGH_LIGHTED_ITEM_WILL_TRADE );
//
//	(*g_pHelpManager)[HE_TRADE_ITEM_REMOVE] = NODE_ROOT;		// 교환중에 아이템 제거	
//
//
//	//------------------------------------------------------------------
//	// HE_CHAT_WHISPERED				// 귓속말 왔을 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_COMPARE( HC_DIDNOT_WHISPER_YET );
//		LP_COMPARE(NODE_ROOT)->SET_TRUE_OUTPUT;
//			LP_OUTPUT(NODE_T)->ADD_OUTPUT( HO_HOW_TO_WHISPER );
//			LP_OUTPUT(NODE_T)->ADD_OUTPUT( HO_HOW_TO_REJECT_CHAT );
//			LP_OUTPUT(NODE_T)->ADD_OUTPUT( HO_SLASH_TO_QUICK_WHISPER );
//
//	(*g_pHelpManager)[HE_CHAT_WHISPERED] = NODE_ROOT;		// 귓속말 왔을 때
//
//
//	//------------------------------------------------------------------
//	// HE_CHAT_WHISPER				// 귓속말 할 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_SLASH_TO_QUICK_WHISPER );
//
//	(*g_pHelpManager)[HE_CHAT_WHISPER] = NODE_ROOT;		// 귓속말 할 때
//
//
//	//------------------------------------------------------------------
//	// HE_CHAT_SHOUTED				// 외치기 왔을 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_HOW_TO_SHOUT );
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_HOW_TO_REJECT_CHAT );
//		
//	(*g_pHelpManager)[HE_CHAT_SHOUTED] = NODE_ROOT;		// 외치기 왔을 때
//
//
//	//------------------------------------------------------------------
//	// HE_CHAT_SHOUT					// 외치기 할 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_TIME_RESTRICT_SHOUT );
//
//	(*g_pHelpManager)[HE_CHAT_SHOUT] = NODE_ROOT;		// 외치기 할 때
//
//
//	//------------------------------------------------------------------
//	// HE_CHAT_REJECT					// 대화거부
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_HOW_TO_ACCEPT_CHAT_ALL );
//
//	(*g_pHelpManager)[HE_CHAT_REJECT] = NODE_ROOT;			// 대화거부
//
//
//	//------------------------------------------------------------------
//	// HE_CHAT_REJECT_USER					// 외치기 할 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_HOW_TO_ACCEPT_CHAT );
//
//	(*g_pHelpManager)[HE_CHAT_REJECT_USER] = NODE_ROOT;	// 대화거부 한 명
//
//	
//	//------------------------------------------------------------------
//	// HE_ITEM_APPEAR					// 근처에 아이템이 나타났을때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_COMPARE( HC_ITEM_PICKED_UP );
//		// 아이템 주운적이 있다면
//		LP_COMPARE(NODE_ROOT)->SET_TRUE_COMPARE( HC_USED_ALT_FOR_ITEM );
//			// ALT를 사용한 적이 없는 경우
//			LP_COMPARE(NODE_T)->SET_FALSE_OUTPUT;
//				LP_OUTPUT(NODE_TF)->ADD_OUTPUT( HO_ALT_TO_PICKUP_ITEM );
//
//		// 아이템 주운적이 없다면
//		LP_COMPARE(NODE_ROOT)->SET_FALSE_COMPARE( HC_USED_ALT_FOR_ITEM );
//			// ALT를 사용한 적이 있다면
//			LP_COMPARE(NODE_F)->SET_TRUE_OUTPUT;
//				LP_OUTPUT(NODE_FT)->ADD_OUTPUT( HO_CLICK_TO_PICKUP );
//
//			// ALT를 사용한적이 없다면
//			LP_COMPARE(NODE_F)->SET_FALSE_OUTPUT;
//				LP_OUTPUT(NODE_FF)->ADD_OUTPUT( HO_ALT_TO_PICKUP_ITEM );
//
//	(*g_pHelpManager)[HE_ITEM_APPEAR] = NODE_ROOT;		// 근처에 아이템이 나타났을때
//
//
//	//------------------------------------------------------------------
//	// HE_ITEM_PICKUP					// 아이템을 주웠을 때	
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_COMPARE( HC_USED_ALT_FOR_ITEM );
//		LP_COMPARE(NODE_ROOT)->SET_FALSE_OUTPUT;
//			LP_OUTPUT(NODE_F)->ADD_OUTPUT( HO_ALT_TO_PICKUP_ITEM );
//
//	(*g_pHelpManager)[HE_ITEM_PICKUP] = NODE_ROOT;		// 아이템을 주웠을 때	
//
//
//	//------------------------------------------------------------------
//	// HE_ITEM_USE_BELT_ITEM			// 벨트 아이템 사용할 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_COMPARE( HC_USED_FUNCTION_KEY_FOR_QUICKITEM );
//		LP_COMPARE(NODE_ROOT)->SET_FALSE_OUTPUT;
//			LP_OUTPUT(NODE_F)->ADD_OUTPUT( HO_USE_FUNCTION_KEY_FOR_QUICKITEM );
//
//	(*g_pHelpManager)[HE_ITEM_USE_BELT_ITEM] = NODE_ROOT;		// 벨트 아이템 사용할 때
//
//
//	//------------------------------------------------------------------
//	// HE_ITEM_USE_MAGAZINE			// 탄창 사용할 때		
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_RELOAD_TIME_IS_LONG );
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_BETTER_TO_LEARN_FAST_RELOAD_SKILL );
//
//	(*g_pHelpManager)[HE_ITEM_USE_MAGAZINE] = NODE_ROOT;		// 탄창 사용할 때		
//
//
//	//------------------------------------------------------------------
//	// HE_ITEM_APPEAR_HOLY_WATER		// 성수 생겼을 때		
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_YOU_CAN_THROW_HOLY_WATER_WITH_SKILL_SELECT );
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_HOLY_WATER_DAMAGE_DECIDED_WHEN_CREATE );
//
//	(*g_pHelpManager)[HE_ITEM_APPEAR_HOLY_WATER] = NODE_ROOT;		// 성수 생겼을 때		
//
//
//	//------------------------------------------------------------------
//	// HE_ITEM_EMPTY_BULLET			// 총알 다 썼을 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_USE_MAGAZINE_IN_INVENTORY_TO_RELOAD );	
//		
//	(*g_pHelpManager)[HE_ITEM_EMPTY_BULLET] = NODE_ROOT;		// 총알 다 썼을 때
//
//	//------------------------------------------------------------------
//	// HE_ITEM_DIFFERENT_BULLET_TYPE		// 다른 총알을 썼을 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_EACH_GUN_NEED_OWN_MAGAZINE );
//
//	(*g_pHelpManager)[HE_ITEM_DIFFERENT_BULLET_TYPE] = NODE_ROOT;	// 다른 총알을 썼을 때
//
//	//------------------------------------------------------------------
//	// HE_ITEM_DURABILITY_LOW			// 아이템 내구도가 낮을 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_ITEM_CAN_BE_BROKEN );
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_YOU_MUST_REPAIR_ITEM_BEFORE_BROKEN );
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_WHERE_TO_REPAIR );
//
//	(*g_pHelpManager)[HE_ITEM_DURABILITY_LOW] = NODE_ROOT;		// 아이템 내구도가 낮을 때
//
//
//	//------------------------------------------------------------------
//	// HE_ITEM_BROKEN					// 아이템이 부서질 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_BROKEN_ITEM_CANNOT_BE_RESTORE );
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_YOU_MUST_REPAIR_ITEM_BEFORE_BROKEN );
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_WHERE_TO_REPAIR );
//
//	(*g_pHelpManager)[HE_ITEM_BROKEN] = NODE_ROOT;		// 아이템이 부서질 때
//
//
//	//------------------------------------------------------------------
//	// HE_ITEM_BUY_MOTORCYCLE			// 오토바이 사고 나서
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_KEEP_MOTORCYCLE_KEY );
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_LEFTCLICK_TO_MOTORCYCLE_TO_RIDE );
//
//	(*g_pHelpManager)[HE_ITEM_BUY_MOTORCYCLE] = NODE_ROOT;		// 오토바이 사고 나서
//
//
//	//------------------------------------------------------------------
//	// HE_ITEM_RIDE_MOTORCYCLE		// 오토바이 탈 때	
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_YOU_CANNOT_ANY_ACTION_WHEN_RIDE_MOTORCYCLE );
//
//	(*g_pHelpManager)[HE_ITEM_RIDE_MOTORCYCLE] = NODE_ROOT;		// 오토바이 탈 때	
//
//
//	//------------------------------------------------------------------
//	// HE_ITEM_WEAR_BELT				// 벨트 착용할 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_BELT_TOGGLE_KEY );
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_ONLY_POTION_AND_MAGAZINE_CAN_STOCK_IN_BELT );
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_MOVE_ITEM_TO_BELT );
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_USE_FUNCTION_KEY_FOR_QUICKITEM );
//
//	(*g_pHelpManager)[HE_ITEM_WEAR_BELT] = NODE_ROOT;		// 벨트 착용할 때
//
//
//	//------------------------------------------------------------------
//	// HE_ITEM_WEAR_GUN				// 총 착용할 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_COMPARE( HC_EMPTY_BULLET );
//		LP_COMPARE(NODE_ROOT)->SET_TRUE_OUTPUT;
//			LP_OUTPUT(NODE_T)->ADD_OUTPUT( HO_NEED_RELOAD_TO_USE_GUN );
//			LP_OUTPUT(NODE_T)->ADD_OUTPUT( HO_USE_MAGAZINE_IN_INVENTORY_TO_RELOAD );
//
//		LP_COMPARE(NODE_ROOT)->SET_FALSE_OUTPUT;
//			LP_OUTPUT(NODE_F)->ADD_OUTPUT( HO_EACH_GUN_NEED_OWN_MAGAZINE );			
//			LP_OUTPUT(NODE_F)->ADD_OUTPUT( HO_USE_GUN_TO_INCREASE_GUN_SKILL );
//		
//	(*g_pHelpManager)[HE_ITEM_WEAR_GUN] = NODE_ROOT;		// 총 착용할 때
//
//
//	//------------------------------------------------------------------
//	// HE_ITEM_WEAR_SWORD				// 검 착용할 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_YOU_CAN_USE_SHIELD_WITH_SWORD );
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_USE_SWORD_TO_INCREASE_SWORD_SKILL );
//
//	(*g_pHelpManager)[HE_ITEM_WEAR_SWORD] = NODE_ROOT;		// 검 착용할 때
//
//
//	//------------------------------------------------------------------
//	// HE_ITEM_WEAR_BLADE				// 도 착용할 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_YOU_CANNOT_USE_SHIELD_WITH_BLADE );
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_USE_BLADE_TO_INCREASE_BLADE_SKILL );
//
//	(*g_pHelpManager)[HE_ITEM_WEAR_BLADE] = NODE_ROOT;		// 도 착용할 때	
//
//
//	//------------------------------------------------------------------
//	// HE_ITEM_WEAR_CROSS				// 십자가 착용할 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_YOU_CANNOT_USE_SHIELD_WITH_CROSS );
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_USE_CROSS_TO_INCREASE_HEAL_SKILL );
//
//	(*g_pHelpManager)[HE_ITEM_WEAR_CROSS] = NODE_ROOT;		// 십자가 착용할 때
//
//
//	//------------------------------------------------------------------
//	// HE_ITEM_WEAR_MACE				// mace 착용할 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_YOU_CANNOT_USE_SHIELD_WITH_MACE );
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_USE_MACE_TO_INCREASE_ENCHANT_SKILL );
//
//	(*g_pHelpManager)[HE_ITEM_WEAR_CROSS] = NODE_ROOT;		// mace 착용할 때
//
//
//	//------------------------------------------------------------------
//	// HE_ITEM_PICKUP_MONEY			// 돈 주웠을 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_INVENTORY_MONEY_WILL_AUTO_INCREASE_ );
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_YOU_CAN_DROP_MONEY_WITH_ICON_IN_INVENTORY );
//		
//	(*g_pHelpManager)[HE_ITEM_PICKUP_MONEY] = NODE_ROOT;		// 돈 주웠을 때
//
//
//	//------------------------------------------------------------------
//	// HE_ITEM_DROP_MONEY				// 돈 버렸을 때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_THERE_IS_MONEY );	// -_-;
//
//	(*g_pHelpManager)[HE_ITEM_DROP_MONEY] = NODE_ROOT;		// 돈 버렸을 때
//
//
//	//------------------------------------------------------------------
//	// HE_ITEM_APPEAR_CORPSE			// 시체가 생겼을 때	
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_LEFTCLICK_TO_CORPSE_TO_LOOT );
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_THERE_IS_SOME_ITEMS_IN_CORPSE );
//
//	(*g_pHelpManager)[HE_ITEM_APPEAR_CORPSE] = NODE_ROOT;		// 시체가 생겼을 때	
//
//	//------------------------------------------------------------------
//	// HE_PRESSED_ALT			// ALT눌렀을때
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_ALT_TO_PICKUP_ITEM );
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_ALT_TO_TRADE );
//
//	(*g_pHelpManager)[HE_PRESSED_ALT] = NODE_ROOT;		// ALT눌렀을때
//
//	//------------------------------------------------------------------
//	// HE_PRESSED_FUNCTION_KEY_FOR_QUICKITEM			// quickitem단축키로 사용
//	//------------------------------------------------------------------
//	NODE_ROOT = NEW_OUTPUT;
//		LP_OUTPUT(NODE_ROOT)->ADD_OUTPUT( HO_CTRL_TILDE_TO_QUICKSLOT );
//		
//	(*g_pHelpManager)[HE_PRESSED_FUNCTION_KEY_FOR_QUICKITEM] = NODE_ROOT;		// quickitem 단축키로 사용
//	
//
//	
//
//	//------------------------------------------------------------------
//	//
//	// Save To File
//	//
//	//------------------------------------------------------------------
//	std::ofstream file(g_pFileDef->getProperty("FILE_INFO_SMART_HELP").c_str(), ios::binary);
//	
//	g_pHelpManager->SaveToFile( file );
//
//	file.close();


	return TRUE;
}
