
#include "client_PCH.h"

#if __CONTENTS(__GPS_ADD)

#include "VS_UI_GameCommon.h"
#include "VS_UI_GameCommon2.h"
#include "VS_UI_GlobalResource.h"
#include "VS_UI_filepath.h"
#include "VS_UI_Mouse_pointer.h"
//#include "VS_UI_Item.h"		
#include "VS_UI.h"
#include "VS_UI_GPS.h"

#include "MPriceManager.h"
#include "MCreatureTable.h"
#include "CDirectInput.h"
#include "MNPCTable.h"
#include "MParty.h"

#include "MGuildMarkManager.h"
#include "MGuildInfoMapper.h"
#include "ExperienceTable.h"
#include "UserOption.h"
#include "UserInformation.h"
#include "MItemOptionTable.h"
#include "MGameStringTable.H"
//#include "ex\DebugInfo.h"
#include "RankBonusDef.H"
#include "RankBonusTable.H"
#include "KeyAccelerator.h"

#include "MZoneTable.h"
#include "FameInfo.h"
#include "MMonsterKillQuestInfo.h"
#include "SystemAvailabilities.h"
#include "SkinManager.h"

#include <algorithm>
#include <time.h>
#include "../client/packet/types/WarTypes.h"

#include "MHelpDef.h"
#include "VS_UI_ExtraDialog.h"
#include "DebugInfo.h"
#include "MItemFinder.h"

#include "MPlayer.h"

#include "UIDialog.h"
#include "QuestDef.h"


#include <stdlib.h>

#include "UIMessageManager.h"
#include "MGpsTable.h"

#if __CONTENTS(__TITLE_UI_RENWEAL)
	#include "VS_UI_NewTitle.h"
#else	//__TITLE_UI_RENWEAL
	#include "VS_UI_Title.h"
#endif //__TITLE_UI_RENWEAL

extern	MGPS_INFO	*g_pGpsInfoTable;

#if __CONTENTS(__MOVE_ZONE)
//extern bool FileOpenBinary(const char* filename, ivfstream& file);
#endif //__MOVE_ZONE

//-----------------------------------------------------------------------------
// C_GPS_BOX
//
//-----------------------------------------------------------------------------
C_GPS_BOX::C_GPS_BOX()
{
	memset((S_GPS_BASE_INFO*)&m_Gps_Base_Info, NULL, sizeof(S_GPS_BASE_INFO));
}

C_GPS_BOX::~C_GPS_BOX()
{
	memset((S_GPS_BASE_INFO*)&m_Gps_Base_Info, NULL, sizeof(S_GPS_BASE_INFO));
}

void	C_GPS_BOX::SetBox(S_GPS_BASE_INFO Gps_Base_Info)
{
	m_Gps_Base_Info	= Gps_Base_Info;
}

void	C_GPS_BOX::BoxView()
{
	if(m_Gps_Base_Info.bHide)	//Box가 숨기기 상태이면 박스를 그리지 않고 함수를 빠져나간다.
		return;

	if(m_Gps_Base_Info.spk)
		m_Gps_Base_Info.spk->BltLocked(m_Gps_Base_Info.iX, m_Gps_Base_Info.iY, m_Gps_Base_Info.wSpkIndex);
}


//-----------------------------------------------------------------------------
// C_GPS_BUTTON
//
//-----------------------------------------------------------------------------

C_GPS_BUTTON::C_GPS_BUTTON()
{
	memset((S_GPS_BASE_INFO*)&m_Gps_Base_Info, NULL, sizeof(S_GPS_BASE_INFO));
}

C_GPS_BUTTON::~C_GPS_BUTTON()
{
	memset((S_GPS_BASE_INFO*)&m_Gps_Base_Info, NULL, sizeof(S_GPS_BASE_INFO));
}

void	C_GPS_BUTTON::SetButton(S_GPS_BASE_INFO Gps_Base_Info)
{
	m_Gps_Base_Info	= Gps_Base_Info;
}

void	C_GPS_BUTTON::ButtonView()
{
	if(m_Gps_Base_Info.bHide)
		return;

	if(m_Gps_Base_Info.spk)
		m_Gps_Base_Info.spk->BltLocked(m_Gps_Base_Info.iX, m_Gps_Base_Info.iY, m_Gps_Base_Info.wSpkIndex);
}

bool	C_GPS_BUTTON::ButtonClick(int iPos_X, int iPos_Y, bool bClick, int iSpkIndex1, int iSpkIndex2)
{
	if(iPos_X >= m_Gps_Base_Info.iX && iPos_X <= m_Gps_Base_Info.iX + m_Gps_Base_Info.iWidht &&
			iPos_Y >= m_Gps_Base_Info.iY && iPos_Y <= m_Gps_Base_Info.iY + m_Gps_Base_Info.iHeight)	//마우스 롤오버
	{
		m_Gps_Base_Info.wSpkIndex	= iSpkIndex2;	//마우스가 롤 오버일때는 iSpkIndex2로 바꿔준다.
		if(bClick)
		{
			return true;							//버튼이 클릭 되면 true를 리컨 한다.
		}
		return false;
	}
	m_Gps_Base_Info.wSpkIndex	= iSpkIndex1;		//평상시에는 iSpkIndex1로 설정 된다.
	return false;
}

//-----------------------------------------------------------------------------
// C_GPS_MAP
//
//-----------------------------------------------------------------------------
C_GPS_MAP::C_GPS_MAP()
{
	memset((S_GPS_BASE_INFO*)&m_Gps_Base_Info, NULL, sizeof(S_GPS_BASE_INFO));
	m_pIconSpk	= NULL;
	m_Gps_Party_Info.clear();
	m_Gps_Npc_Info.clear();
	m_Gps_Potal_Info.clear();
	m_ZoneInfo.clear();
	m_MonsterInfo.clear();
	m_Gps_Quest_Info.clear();
	m_Gps_Quest_Info_temp.clear();

	m_Gps_Party_Info.resize(0);
	m_Gps_Npc_Info.resize(0);
	m_Gps_Potal_Info.resize(0);
	m_ZoneInfo.resize(0);
	m_MonsterInfo.resize(0);
	m_Gps_Quest_Info.resize(0);
	m_Gps_Quest_Info_temp.resize(0);

	m_iUserNpcGameMap_X	= 0;
	m_iUserNpcGameMap_Y = 0;
	m_iSelectMapIndex	= 0;
	m_bInfoInit			= true;
	m_strTemp			= "";
	GpsZoneInfoInit();
	GpsNpcInfoInit();
	GpsPortalInfoInit();
	GpsMonsterInfoInit();
	SetGpsPartyInfo();
}

C_GPS_MAP::~C_GPS_MAP()
{
	memset((S_GPS_BASE_INFO*)&m_Gps_Base_Info, NULL, sizeof(S_GPS_BASE_INFO));
	m_pIconSpk	= NULL;
	m_Gps_Party_Info.clear();
	m_Gps_Npc_Info.clear();
	m_Gps_Potal_Info.clear();
	m_ZoneInfo.clear();
	m_MonsterInfo.clear();
	m_Gps_Quest_Info.clear();

	m_Gps_Party_Info.resize(0);
	m_Gps_Npc_Info.resize(0);
	m_Gps_Potal_Info.resize(0);
	m_ZoneInfo.resize(0);
	m_MonsterInfo.resize(0);
	m_Gps_Quest_Info.resize(0);

	m_iUserNpcGameMap_X	= 0;
	m_iUserNpcGameMap_Y = 0;
	m_iSelectMapIndex	= 0;
	m_bInfoInit			= true;

	GpsZoneInfoInit();
	GpsNpcInfoInit();
	GpsPortalInfoInit();
	GpsMonsterInfoInit();
	SetGpsPartyInfo();
}

void	C_GPS_MAP::GpsMonsterInfoInit()		//월드맵 상에서 클릭 되었을때에 보여질 몬스터 정보
{
	m_MonsterInfo.clear();
	m_MonsterInfo.resize(0);
	S_GPS_MONSTER_INFO	MonsterInfo;
	DWORD							dwSize					= g_pGpsInfoTable->GetTitleMonsterInfoSize();
	std::vector<SGPS_MONSTER_INFO>	SGps_TitleMonster_Info	= g_pGpsInfoTable->GetTitleMonsterInfo();

	for(DWORD i = 0; i < dwSize; i++)
	{
		MonsterInfo.Release();

		MonsterInfo.wZoneID			=	SGps_TitleMonster_Info[i].wZoneID;
		MonsterInfo.pchFieldName	=	SGps_TitleMonster_Info[i].strZoneName.GetString();
		MonsterInfo.wMonsterLv1		=	SGps_TitleMonster_Info[i].wMinMonsterLv;
		MonsterInfo.wMonsterLv2		=	SGps_TitleMonster_Info[i].wMaxMonsterLv;
		
		m_MonsterInfo.push_back(MonsterInfo);
	}
}

void	C_GPS_MAP::GpsZoneInfoInit()				
{
	m_ZoneInfo.clear();
	m_ZoneInfo.resize(0);

	S_GPS_ZONE_NAME_ID				ZoneNameID;
	DWORD							dwSize			= g_pGpsInfoTable->GetZoneInfoSize();
	std::vector<SGPS_ZONE_INFO>		SGps_Zone_Info	= g_pGpsInfoTable->GetZoneInfo();

	for(DWORD i = 0; i < dwSize; i++)
	{
		ZoneNameID.Release();
		
		ZoneNameID.pchName	= SGps_Zone_Info[i].strGpsTitle_ZoneName.GetString();
		ZoneNameID.wID		= SGps_Zone_Info[i].wZoneID;

		m_ZoneInfo.push_back(ZoneNameID);
	}
}

void	C_GPS_MAP::GpsNpcInfoInit()					//NPC 정보 위치와 ID는 실제 게임상에서와 동일 하다.
{
	m_Gps_Npc_Info.clear();
	m_Gps_Npc_Info.resize(0);

	S_GPS_NPC_INFO		Gps_Npc_Info;

	DWORD							dwSize			= g_pGpsInfoTable->GetNpcInfoSize();
	std::vector<SGPS_NPC_INFO>		SGps_Npc_Info	= g_pGpsInfoTable->GetNpcInfo();

	for(int i = 0; i < dwSize; i++)
	{
		Gps_Npc_Info.Release();

		Gps_Npc_Info.wPos_X									= SGps_Npc_Info[i].wPos_X;
		Gps_Npc_Info.wPos_Y									= SGps_Npc_Info[i].wPos_Y;
		Gps_Npc_Info.pchName								= SGps_Npc_Info[i].strNpcName.GetString();
		Gps_Npc_Info.chExplanation							= SGps_Npc_Info[i].strNpcExplanation.GetString();
		Gps_Npc_Info.wSpkIndex								= SGps_Npc_Info[i].wSpkIndex;
		Gps_Npc_Info.S_Gps_Game_Map_Info.wID				= SGps_Npc_Info[i].wZoneID;
		Gps_Npc_Info.S_Gps_Game_Map_Info.wMapSize_Width		= SGps_Npc_Info[i].wMapWidth;
		Gps_Npc_Info.S_Gps_Game_Map_Info.wMapSize_Height	= SGps_Npc_Info[i].wMapHeight;

		m_Gps_Npc_Info.push_back(Gps_Npc_Info);
	}
}



void	C_GPS_MAP::GpsPortalInfoInit()					//포탈 정보 실제 게임에서와 동일하다.
{
	m_Gps_Potal_Info.clear();
	m_Gps_Potal_Info.resize(0);
	S_GPS_POTAL_INFO				Gps_Potal_Info;

	DWORD								dwSize			= g_pGpsInfoTable->GetPotalInfoSize();
	std::vector<SGPS_POTAL_INFO>		SGps_Potal_Info	= g_pGpsInfoTable->GetPotalInfo();

	for(DWORD i = 0; i < dwSize; i++)
	{
		Gps_Potal_Info.Release();

		Gps_Potal_Info.wPos_X								= SGps_Potal_Info[i].wPos_X;
		Gps_Potal_Info.wPos_Y								= SGps_Potal_Info[i].wPos_Y;
		Gps_Potal_Info.chExplanation						= SGps_Potal_Info[i].strPotalName.GetString();
		Gps_Potal_Info.wSpkIndex							= SGps_Potal_Info[i].wSpkIndex;
		Gps_Potal_Info.S_Gps_Game_Map_Info.wID				= SGps_Potal_Info[i].wZoneID;
		Gps_Potal_Info.S_Gps_Game_Map_Info.wMapSize_Width	= SGps_Potal_Info[i].wMapWidth;
		Gps_Potal_Info.S_Gps_Game_Map_Info.wMapSize_Height	= SGps_Potal_Info[i].wMapHeight;

		m_Gps_Potal_Info.push_back(Gps_Potal_Info);
	}
}

void	C_GPS_MAP::SetGpsUserInfo(S_GPS_NPC_INFO Gps_Npc_Info)
{
	GameMapToGpsMapNpcPos(Gps_Npc_Info);
	m_Gps_User_Info = Gps_Npc_Info;
}

void	C_GPS_MAP::SetGpsPartyInfo()
{
	m_Gps_Party_Info.clear();
	m_Gps_Party_Info.resize(0);
	
	S_GPS_NPC_INFO Gps_Party_Info;
	if(g_pParty != NULL)
	{
		for(int i = 0; i < g_pParty->GetSize(); i++)
		{
			if(g_pParty->GetMemberInfo(i) != NULL)
			{
				Gps_Party_Info.wPos_X			= g_pParty->GetMemberInfo(i)->zoneX;
				Gps_Party_Info.wPos_Y			= g_pParty->GetMemberInfo(i)->zoneY;

//				Gps_Party_Info.chExplanation	= g_pParty->GetMemberInfo(i)->guildName.GetString();

				Gps_Party_Info.S_Gps_Game_Map_Info.wID	= g_pParty->GetMemberInfo(i)->zoneID;
				Gps_Party_Info.S_Gps_Game_Map_Info.wMapSize_Width	= 256;
				Gps_Party_Info.S_Gps_Game_Map_Info.wMapSize_Height	= 256;

				if(m_iZoneID == WORLDMAP_ID_PERONA_NW || m_iZoneID == WORLDMAP_ID_PERONA_NE || 
					m_iZoneID == WORLDMAP_ID_PERONA_SW || m_iZoneID == WORLDMAP_ID_PERONA_SE)
				{
					Gps_Party_Info.S_Gps_Game_Map_Info.wMapSize_Width = 128;
				}

				Gps_Party_Info.wSpkIndex = GPS_PARTY_PC_ICON;

				m_Gps_Party_Info.push_back(Gps_Party_Info);
				GameMapToGpsMapNpcPos(m_Gps_Party_Info[i]);
			}
		}
	}
}

void	C_GPS_MAP::SetMap(S_GPS_BASE_INFO Gps_Base_Info, int iZoneID, C_SPRITE_PACK *IconSpk)
{
	m_Gps_Base_Info	= Gps_Base_Info;
	m_iZoneID		= iZoneID;
	m_pIconSpk		= IconSpk;

	static vector<S_GPS_NPC_INFO>		scGpsNpcInfo;
	static vector<S_GPS_NPC_INFO>		scGpsPartyInfo;
	static vector<S_GPS_POTAL_INFO>		scGpsPotalInfo;

	if(m_bInfoInit)											//Gps_map가 실행 되면 몬스터 정보, NPC 정보, 던전 정보등이 초기화 된다.
	{
		m_bInfoInit	= false;								//이 초기화된 값들은 월드맵 상의 정보일때 한번만 가지고 있어야 한다.

		scGpsNpcInfo		= m_Gps_Npc_Info;
		scGpsPartyInfo		= m_Gps_Party_Info;
		scGpsPotalInfo		= m_Gps_Potal_Info;
	}

	m_Gps_Npc_Info		= scGpsNpcInfo;						//gps가 드래그 되면 Icon의 위치들도 같이 변경 된다.
//	m_Gps_Party_Info	= scGpsPartyInfo;					//이럴 경우 게임상의 NPC 위치와 던전의 위치가 GPS상으로 바뀐다.
	m_Gps_Potal_Info	= scGpsPotalInfo;					//다시 게임상의 위치 정보로 설정해 주자.
#if __CONTENTS(__QUEST_RENEWAL)	// C_GPS_MAP::SetMap
	m_Gps_Quest_Info	= m_Gps_Quest_Info_temp;
#endif

	for(int i = 0; i < m_Gps_Npc_Info.size(); i++)
	{
		GameMapToGpsMapNpcPos(m_Gps_Npc_Info[i]);				//게임상의 NPC위치 정보를 GPS의 위치로 바꿔준다.
	}

	for(i = 0; i < m_Gps_Party_Info.size(); i++)
	{
//		GameMapToGpsMapNpcPos(m_Gps_Party_Info[i]);			//게임상의 파티위치 정보를 GPS의 위치로 바꿔준다.
	}

	for(i = 0; i < m_Gps_Potal_Info.size(); i++)
	{
		GameMapToGpsMapPotalPos(m_Gps_Potal_Info[i]);
	}

#if __CONTENTS(__QUEST_RENEWAL)	// C_GPS_MAP::SetMap	퀘스트 위치 설정
	for(i = 0; i < m_Gps_Quest_Info.size(); i++)
	{
		if(m_Gps_Quest_Info[i].bQuestShow)
		{
			GameMapToGpsMapQuestPos(m_Gps_Quest_Info[i]);
		}
	}
#endif	// __QUEST_RENEWAL
}

#if __CONTENTS(__QUEST_RENEWAL)
void	C_GPS_MAP::SetQuestInfo(vector<S_QUESTICON_INFO>	Gps_Quest_Info)
{
	m_Gps_Quest_Info.clear();
	m_Gps_Quest_Info.resize(0);

	m_Gps_Quest_Info	= Gps_Quest_Info;
}
#endif

#if __CONTENTS(__QUEST_RENEWAL)
void	C_GPS_MAP::ModifyQuestStatus(BYTE btStatus, DWORD dwQuestID)
{
	for(int i = 0; i < m_Gps_Quest_Info_temp.size(); i++)
	{
		if(m_Gps_Quest_Info_temp[i].wQuestID	== dwQuestID)
		{
			if(btStatus	== C_VS_UI_QUEST_LIST::CAN_REPLAY || btStatus	== C_VS_UI_QUEST_LIST::CANNOT || btStatus	== C_VS_UI_QUEST_LIST::CAN_ACCEPT)
			{
				m_Gps_Quest_Info_temp[i].wIndex	= QUEST_WAIT;
				if(m_Gps_Quest_Info.size() == m_Gps_Quest_Info_temp.size())
				{
					m_Gps_Quest_Info[i].wIndex		= QUEST_WAIT;
					m_Gps_Quest_Info[i].strQuestExplanation_GpsView			= m_Gps_Quest_Info_temp[i].strQuestExplanation_GpsView;
					m_Gps_Quest_Info[i].strQuestExplanation_WorldView		= m_Gps_Quest_Info_temp[i].strQuestExplanation_WorldView;
					std::string buffer = (*g_pGameStringTable)[UI_STRING_GQUEST_QUEST].GetString();
					buffer += (*g_pGameStringTable)[UI_STRING_GQUEST_STANDING_BRACKET].GetString();
					m_Gps_Quest_Info_temp[i].strQuestName_WorldView			= buffer;
				}
			}
			else if(btStatus	== C_VS_UI_QUEST_LIST::SUCCESS || btStatus	== C_VS_UI_QUEST_LIST::DOING)
			{
				m_Gps_Quest_Info_temp[i].wIndex	= QUEST_RUN;

				if(m_Gps_Quest_Info.size() == m_Gps_Quest_Info_temp.size())
				{
					m_Gps_Quest_Info[i].wIndex		= QUEST_RUN;
					m_Gps_Quest_Info[i].strQuestExplanation_GpsView			= m_Gps_Quest_Info_temp[i].strQuestExplanation_GpsView;
					m_Gps_Quest_Info[i].strQuestExplanation_WorldView		= m_Gps_Quest_Info_temp[i].strQuestExplanation_WorldView;
					std::string buffer = (*g_pGameStringTable)[UI_STRING_GQUEST_QUEST].GetString();
					buffer = (*g_pGameStringTable)[UI_STRING_GQUEST_DOING_BRACKET].GetString();
					m_Gps_Quest_Info_temp[i].strQuestName_WorldView			= buffer;
				}
			}
			else if(btStatus	== C_VS_UI_QUEST_LIST::COMPLETE || btStatus	== C_VS_UI_QUEST_LIST::FAIL)
			{
				if(m_Gps_Quest_Info.size() == m_Gps_Quest_Info_temp.size())
				{
					m_Gps_Quest_Info.erase(m_Gps_Quest_Info.begin()+i);
					m_Gps_Quest_Info_temp.erase(m_Gps_Quest_Info_temp.begin()+i);
				}
			}

			if(GetWorldMapZoneIDExistenceFind(m_Gps_Quest_Info[i].S_Gps_Game_Map_Info.wID))	//Zone ID가 월드맵 상의 필드가 아니면 보여주지 않는다.
			{
				m_Gps_Quest_Info[i].bQuestShow	= false;
			}
		}
	}
}
#endif

#if __CONTENTS(__QUEST_RENEWAL)
void	C_GPS_MAP::GpsQuestInfoDelete()
{
	m_Gps_Quest_Info.clear();
	m_Gps_Quest_Info.resize(0);

	m_Gps_Quest_Info_temp.clear();
	m_Gps_Quest_Info_temp.resize(0);
}
#endif

#if __CONTENTS(__QUEST_RENEWAL)
bool	C_GPS_MAP::GetWorldMapZoneIDExistenceFind(DWORD dwZoneID)	//Zone ID가 월드 맵과 다를 때 True를 넘겨 준다.
{
	bool	bResult	= true;	//Zone ID가 월드맵과 다르면 Ture

	switch(dwZoneID)
	{
	case WORLDMAP_ID_LIMBO_NW:
		bResult	= false;
		break;
	case WORLDMAP_ID_LIMBO_NE:
		bResult	= false;
		break;
	case WORLDMAP_ID_LIMBO_SW:
		bResult	= false;
		break;
	case WORLDMAP_ID_LIMBO_SE:
		bResult	= false;
		break;


	case WORLDMAP_ID_ESL_NW:
		bResult	= false;
		break;
	case WORLDMAP_ID_ESL_NE:
		bResult	= false;
		break;
	case WORLDMAP_ID_ESL_SW:
		bResult	= false;
		break;
	case WORLDMAP_ID_ESL_SE:
		bResult	= false;
		break;

	case WORLDMAP_ID_LODIN_NW:
		bResult	= false;
		break;
	case WORLDMAP_ID_LODIN_NE:
		bResult	= false;
		break;
	case WORLDMAP_ID_LODIN_SW:
		bResult	= false;
		break;
	case WORLDMAP_ID_LODIN_SE:
		bResult	= false;
		break;

	case WORLDMAP_ID_CASTALO_NE:
		bResult	= false;
		break;

	case WORLDMAP_ID_DROBETA_NW:
		bResult	= false;
		break;
	case WORLDMAP_ID_DROBETA_NE:
		bResult	= false;
		break;
	case WORLDMAP_ID_DROBETA_SW:
		bResult	= false;
		break;
	case WORLDMAP_ID_DROBETA_SE:
		bResult	= false;
		break;

	case WORLDMAP_ID_BRANCO_NW:
		bResult	= false;
		break;
	case WORLDMAP_ID_BRANCO_NE:
		bResult	= false;
		break;
	case WORLDMAP_ID_BRANCO_SW:
		bResult	= false;
		break;
	case WORLDMAP_ID_BRANCO_SE:
		bResult	= false;
		break;

	case WORLDMAP_ID_PERONA_NW:
		bResult	= false;
		break;
	case WORLDMAP_ID_PERONA_NE:
		bResult	= false;
		break;
	case WORLDMAP_ID_PERONA_SW:
		bResult	= false;
		break;
	case WORLDMAP_ID_PERONA_SE:
		bResult	= false;
		break;

	case WORLDMAP_ID_TIMOR_NW:
		bResult	= false;
		break;
	case WORLDMAP_ID_TIMOR_NE:
		bResult	= false;
		break;
	case WORLDMAP_ID_TIMOR_SW:
		bResult	= false;
		break;
	case WORLDMAP_ID_TIMOR_SE:
		bResult	= false;
		break;
	}
	return bResult;
}
#endif

#if __CONTENTS(__QUEST_RENEWAL)
vector<S_QUESTICON_INFO>	C_GPS_MAP::GetQuestInfo()
{
	return m_Gps_Quest_Info_temp;
}
#endif

void	C_GPS_MAP::MapView()										//GPS안에 맵을 보여준다.
{
	if(m_Gps_Base_Info.bHide)
		return;

	SetGpsPartyInfo();
	if(m_Gps_Base_Info.spk)
		m_Gps_Base_Info.spk->BltLocked(m_Gps_Base_Info.iX, m_Gps_Base_Info.iY, m_Gps_Base_Info.wSpkIndex);	
	IconView();	
}

void	C_GPS_MAP::ZoneNameTextView()
{
	int iText_X			= 0;
	int iText_Y			= 0;
	int iText_Back_X	= 0;
	int iText_Back_Y	= 0;
	const int	ciText_Back_Width	= 110;
	const int	ciText_Back_Height	= 19;
	const int	ciTextWidht			= 8;
	const int	ciTextHeight		= 8;

	for(int i = 0; i < m_ZoneInfo.size(); i++)
	{
		if(m_ZoneInfo[i].wID	== m_iZoneID)
		{
			iText_Back_X = m_Gps_Base_Info.iX;
			iText_Back_Y = m_Gps_Base_Info.iY - 23;

			iText_X	= iText_Back_X + (ciText_Back_Width / 2) - ((strlen(m_ZoneInfo[i].pchName.c_str()) * ciTextWidht) / 2);	//출력될 문자를 센터에 맞춰주는 부분
			iText_Y	= iText_Back_Y;
			g_PrintColorStr(iText_X + 1,  iText_Y + 1, m_ZoneInfo[i].pchName.c_str(), gpC_base->m_desc_menu_pi,  RGB(255,194,128));
			g_PrintColorStr(iText_X,  iText_Y, m_ZoneInfo[i].pchName.c_str(), gpC_base->m_desc_menu_pi,  RGB(128,194,255));
		}
	}
} 

void	C_GPS_MAP::UserPosTextView()						//사용자의 위치를 보여준다.
{
	int iText_X			= 0;
	int iText_Y			= 0;
	int iText_Back_X	= 0;
	int iText_Back_Y	= 0;
	const int	ciText_Back_Width	= 110;
	const int	ciText_Back_Height	= 19;
	const int	ciTextWidht			= 8;
	const int	ciTextHeight		= 8;

	char *pch_X	= "X: ";
	char *pch_Y	= "Y: ";

	char chItoA_X[5];
	char chItoA_Y[5];
	char chUserPos[30];

	memset((char*)chUserPos, NULL, sizeof(chUserPos));
	memset((char*)chUserPos, NULL, sizeof(chItoA_X));
	memset((char*)chUserPos, NULL, sizeof(chItoA_Y));

	if(m_Gps_User_Info.S_Gps_Game_Map_Info.wID	== m_iZoneID)
	{
		iText_Back_X = m_Gps_Base_Info.iX + 287;
		iText_Back_Y = m_Gps_Base_Info.iY + m_Gps_Base_Info.iHeight + 12;

		strcat(chUserPos, pch_X);
		itoa(m_iUserNpcGameMap_X, chItoA_X, 10);
		strcat(chUserPos, chItoA_X);

		strcat(chUserPos, "  ");

		strcat(chUserPos, pch_Y);
		itoa(m_iUserNpcGameMap_Y, chItoA_Y, 10);
		strcat(chUserPos, chItoA_Y);

		iText_X	= iText_Back_X + (ciText_Back_Width / 2) - ((strlen(chUserPos) * ciTextWidht) / 2);	//센터를 맞춰주는 부분
		iText_Y	= iText_Back_Y;
		
		g_PrintColorStr(iText_X + 1,  iText_Y + 1, chUserPos, gpC_base->m_desc_menu_pi,  RGB(255, 255, 255));
		g_PrintColorStr(iText_X,  iText_Y, chUserPos, gpC_base->m_desc_menu_pi,  RGB(255, 255, 255)); //그림자 효과
	}
}

void	C_GPS_MAP::IconView()					//Icon을 GPS 맵상에 보여준다.
{
	int		iSecFrameTemp	= (g_CurrentFrame%16) + 1;

	if(m_Gps_Base_Info.bHide)
		return;

	if(m_pIconSpk)
	{
		for(int i = 0; i < m_Gps_Npc_Info.size(); i++)		//월드맵 ZoneID에 해당하는 NPC정보를 GPS 맵상에 ICON으로 보여준다.
		{
			if(m_Gps_Npc_Info[i].S_Gps_Game_Map_Info.wID	== m_iZoneID)
				m_pIconSpk->BltLocked(m_Gps_Npc_Info[i].wPos_X, m_Gps_Npc_Info[i].wPos_Y, m_Gps_Npc_Info[i].wSpkIndex);
		}
		for(i = 0; i < m_Gps_Potal_Info.size(); i++)		//월드맵 ZoneID에 해당하는 NPC정보를 GPS 맵상에 ICON으로 보여준다.
		{
			if(m_Gps_Potal_Info[i].S_Gps_Game_Map_Info.wID	== m_iZoneID)
				m_pIconSpk->BltLocked(m_Gps_Potal_Info[i].wPos_X, m_Gps_Potal_Info[i].wPos_Y, m_Gps_Potal_Info[i].wSpkIndex);
		}
		for(i = 0; i < m_Gps_Party_Info.size(); i++)		//월드맵 Zone에 해당하는 파티원 정보를 GPS 맵상에 Icon으로 보여준다.
		{
			if(m_Gps_Party_Info[i].S_Gps_Game_Map_Info.wID	== m_iZoneID)
				m_pIconSpk->BltLocked(m_Gps_Party_Info[i].wPos_X, m_Gps_Party_Info[i].wPos_Y, m_Gps_Party_Info[i].wSpkIndex);
		}
#if __CONTENTS(__QUEST_RENEWAL)
		for(i = 0; i < m_Gps_Quest_Info.size(); i++)		//월드맵 Zone에 해당하는 퀘스트 정보를 GPS 맵상에 Icon으로 보여준다.
		{
			if(m_Gps_Quest_Info[i].bQuestShow	== false)
				continue;
			if(m_Gps_Quest_Info[i].S_Gps_Game_Map_Info.wID	== m_iZoneID)
				m_pIconSpk->BltLockedAlpha(m_Gps_Quest_Info[i].wPos_X, m_Gps_Quest_Info[i].wPos_Y, 
											m_Gps_Quest_Info[i].wIndex + GPS_QUEST_WAIT, iSecFrameTemp * 2);
		}
#endif	//__QUEST_RENEWAL
		if(m_Gps_User_Info.S_Gps_Game_Map_Info.wID	== m_iZoneID)	//사용자의 정보를 보여준다.
			m_pIconSpk->BltLocked(m_Gps_User_Info.wPos_X, m_Gps_User_Info.wPos_Y, m_Gps_User_Info.wSpkIndex);
	}
}

void	C_GPS_MAP::GameMapToGpsMapNpcPos(S_GPS_NPC_INFO &Gps_Npc_Info)	//미니맵과 GPS의 크기를 계산해서 NPC의 위치를 찾는다. 
{
	int		iGpsMapWidth		= 0;
	int		iGpsMapHeight		= 0;

	int		iGameMapScale_X		= 0;
	int		iGameMapScale_Y		= 0;

	int		iGameNpcPos_X		= 0;
	int		iGameNpcPos_Y		= 0;

	float	fGpsMapScale_X		= 0;
	float	fGpsMapScale_Y		= 0;

	int		iScale_X			= 0;
	int		iScale_Y			= 0;

	float	fScale_X			= 0;
	float	fScale_Y			= 0;

	if(m_Gps_User_Info.S_Gps_Game_Map_Info.wID	== m_iZoneID)	//게임 맵의 캐릭터 좌표를 구해준다.
	{
		m_iUserNpcGameMap_X	= Gps_Npc_Info.wPos_X;
		m_iUserNpcGameMap_Y = Gps_Npc_Info.wPos_Y;
	}

	iGpsMapWidth	= m_Gps_Base_Info.spk->GetWidth(m_Gps_Base_Info.wSpkIndex);
	iGpsMapHeight	= m_Gps_Base_Info.spk->GetHeight(m_Gps_Base_Info.wSpkIndex);

	fScale_X		= ((float)(iGpsMapWidth) / (float)(Gps_Npc_Info.S_Gps_Game_Map_Info.wMapSize_Width));
	fScale_Y		= ((float)(iGpsMapHeight) / (float)(Gps_Npc_Info.S_Gps_Game_Map_Info.wMapSize_Height));	

	iGameMapScale_X	= (float)fScale_X * (float)Gps_Npc_Info.wPos_X;
	iGameMapScale_Y	= (float)fScale_Y * (float)Gps_Npc_Info.wPos_Y;

	iGameNpcPos_X		= Gps_Npc_Info.wPos_X;
	iGameNpcPos_Y		= Gps_Npc_Info.wPos_Y;

	Gps_Npc_Info.wPos_X	= (int)iGameMapScale_X + m_Gps_Base_Info.iX;
	Gps_Npc_Info.wPos_Y	= (int)iGameMapScale_Y + m_Gps_Base_Info.iY;

	if(m_pIconSpk != NULL)
	{
		int iIconHeight	= m_pIconSpk->GetHeight(Gps_Npc_Info.wSpkIndex);
		int iIconWidth	= m_pIconSpk->GetWidth(Gps_Npc_Info.wSpkIndex);

		if(iGameNpcPos_X > 1)
			Gps_Npc_Info.wPos_X	= (int)iGameMapScale_X + m_Gps_Base_Info.iX - (m_pIconSpk->GetWidth(Gps_Npc_Info.wSpkIndex)/2);
		else
			Gps_Npc_Info.wPos_X	= m_Gps_Base_Info.iX;

		if(iGameNpcPos_Y > 1)
			Gps_Npc_Info.wPos_Y	= (int)iGameMapScale_Y + m_Gps_Base_Info.iY - (m_pIconSpk->GetHeight(Gps_Npc_Info.wSpkIndex)/2);
		else
			Gps_Npc_Info.wPos_Y	= m_Gps_Base_Info.iY;

		if(Gps_Npc_Info.wPos_X + iIconWidth > iGpsMapWidth + m_Gps_Base_Info.iX)
			Gps_Npc_Info.wPos_X	= (int)iGameMapScale_X + m_Gps_Base_Info.iX - m_pIconSpk->GetWidth(Gps_Npc_Info.wSpkIndex);
		if(Gps_Npc_Info.wPos_Y + iIconHeight > iGameMapScale_X + m_Gps_Base_Info.iX)
			Gps_Npc_Info.wPos_X	= (int)iGameMapScale_X + m_Gps_Base_Info.iX - m_pIconSpk->GetWidth(Gps_Npc_Info.wSpkIndex);
	}
}

void	C_GPS_MAP::GameMapToGpsMapPotalPos(S_GPS_POTAL_INFO &Gps_Potal_Info)	//게임상의 포탈 정보를 GPS맵의 위치로 바꿔준다.
{
	int		iGpsMapWidth		= 0;
	int		iGpsMapHeight		= 0;

	int		iGameMapScale_X		= 0;
	int		iGameMapScale_Y		= 0;

	float	fGpsMapScale_X		= 0;
	float	fGpsMapScale_Y		= 0;

	int		iScale_X			= 0;
	int		iScale_Y			= 0;

	int		iGameNpcPos_X		= 0;
	int		iGameNpcPos_Y		= 0;

	float	fScale_X			= 0;
	float	fScale_Y			= 0;

	iGpsMapWidth	= m_Gps_Base_Info.spk->GetWidth(m_Gps_Base_Info.wSpkIndex);
	iGpsMapHeight	= m_Gps_Base_Info.spk->GetHeight(m_Gps_Base_Info.wSpkIndex);

	fScale_X		= ((float)(iGpsMapWidth) / (float)(Gps_Potal_Info.S_Gps_Game_Map_Info.wMapSize_Width));
	fScale_Y		= ((float)(iGpsMapHeight) / (float)(Gps_Potal_Info.S_Gps_Game_Map_Info.wMapSize_Height));	

	iGameMapScale_X	= (float)fScale_X * (float)Gps_Potal_Info.wPos_X;
	iGameMapScale_Y	= (float)fScale_Y * (float)Gps_Potal_Info.wPos_Y;

	iGameNpcPos_X	= Gps_Potal_Info.wPos_X;
	iGameNpcPos_Y	= Gps_Potal_Info.wPos_Y;

	Gps_Potal_Info.wPos_X	= (int)iGameMapScale_X + m_Gps_Base_Info.iX;
	Gps_Potal_Info.wPos_Y	= (int)iGameMapScale_Y + m_Gps_Base_Info.iY;

	if(m_pIconSpk != NULL)
	{
		int iIconHeight	= m_pIconSpk->GetHeight(Gps_Potal_Info.wSpkIndex);
		int iIconWidth	= m_pIconSpk->GetWidth(Gps_Potal_Info.wSpkIndex);

		if(iGameNpcPos_X > 1)
			Gps_Potal_Info.wPos_X	= (int)iGameMapScale_X + m_Gps_Base_Info.iX - (m_pIconSpk->GetWidth(Gps_Potal_Info.wSpkIndex)/2);
		else
			Gps_Potal_Info.wPos_X	= m_Gps_Base_Info.iX;

		if(iGameNpcPos_Y> 1)
			Gps_Potal_Info.wPos_Y	= (int)iGameMapScale_Y + m_Gps_Base_Info.iY - (m_pIconSpk->GetHeight(Gps_Potal_Info.wSpkIndex)/2);
		else
			Gps_Potal_Info.wPos_Y	= m_Gps_Base_Info.iY;

		if(Gps_Potal_Info.wPos_X + iIconWidth > iGpsMapWidth + m_Gps_Base_Info.iX)
			Gps_Potal_Info.wPos_X	= iGpsMapWidth + m_Gps_Base_Info.iX - m_pIconSpk->GetWidth(Gps_Potal_Info.wSpkIndex);

		if(Gps_Potal_Info.wPos_Y + iIconHeight > iGpsMapHeight + m_Gps_Base_Info.iY)
			Gps_Potal_Info.wPos_Y	= iGpsMapHeight + m_Gps_Base_Info.iY - m_pIconSpk->GetHeight(Gps_Potal_Info.wSpkIndex);
	}
}


#if __CONTENTS(__QUEST_RENEWAL)	//GPS	GameMapToGpsMapQuestPos() 정의 부분	
void	C_GPS_MAP::GameMapToGpsMapQuestPos(S_QUESTICON_INFO &Gps_Quest_Info)	//월드맵과 GPS의 크기를 계산해서 Quest의 위치를 찾는다. 
{
	int		iGpsMapWidth		= 0;
	int		iGpsMapHeight		= 0;

	int		iGameMapScale_X		= 0;
	int		iGameMapScale_Y		= 0;

	float	fGpsMapScale_X		= 0;
	float	fGpsMapScale_Y		= 0;

	int		iScale_X			= 0;
	int		iScale_Y			= 0;

	int		iGameNpcPos_X		= 0;
	int		iGameNpcPos_Y		= 0;

	float	fScale_X			= 0;
	float	fScale_Y			= 0;

	iGpsMapWidth	= m_Gps_Base_Info.spk->GetWidth(m_Gps_Base_Info.wSpkIndex);
	iGpsMapHeight	= m_Gps_Base_Info.spk->GetHeight(m_Gps_Base_Info.wSpkIndex);

	fScale_X	= ((float)(iGpsMapWidth) / (float)(Gps_Quest_Info.S_Gps_Game_Map_Info.wMapSize_Width));
	fScale_Y	= ((float)(iGpsMapHeight) / (float)(Gps_Quest_Info.S_Gps_Game_Map_Info.wMapSize_Height));	

	iGameMapScale_X	= (float)fScale_X * (float)Gps_Quest_Info.wPos_X;
	iGameMapScale_Y	= (float)fScale_Y * (float)Gps_Quest_Info.wPos_Y;

	iGameNpcPos_X	= Gps_Quest_Info.wPos_X;
	iGameNpcPos_Y	= Gps_Quest_Info.wPos_Y;

	Gps_Quest_Info.wPos_X	= (int)iGameMapScale_X + m_Gps_Base_Info.iX;
	Gps_Quest_Info.wPos_Y	= (int)iGameMapScale_Y + m_Gps_Base_Info.iY;

	if(m_pIconSpk != NULL)
	{
		int iIconHeight	= m_pIconSpk->GetHeight(Gps_Quest_Info.wIndex + GPS_QUEST_WAIT);
		int iIconWidth	= m_pIconSpk->GetWidth(Gps_Quest_Info.wIndex + GPS_QUEST_WAIT);

		if(iGameNpcPos_X > 1)
			Gps_Quest_Info.wPos_X	= (int)iGameMapScale_X + m_Gps_Base_Info.iX - (m_pIconSpk->GetWidth(Gps_Quest_Info.wIndex + GPS_QUEST_WAIT)/2);
		else
			Gps_Quest_Info.wPos_X	= m_Gps_Base_Info.iX;

		if(iGameNpcPos_Y> 1)
			Gps_Quest_Info.wPos_Y	= (int)iGameMapScale_Y + m_Gps_Base_Info.iY - (m_pIconSpk->GetHeight(Gps_Quest_Info.wIndex + GPS_QUEST_WAIT)/2);
		else
			Gps_Quest_Info.wPos_Y	= m_Gps_Base_Info.iY;

		if(Gps_Quest_Info.wPos_X + iIconWidth > iGpsMapWidth + m_Gps_Base_Info.iX)
			Gps_Quest_Info.wPos_X	= iGpsMapWidth + m_Gps_Base_Info.iX - m_pIconSpk->GetWidth(Gps_Quest_Info.wIndex + GPS_QUEST_WAIT);

		if(Gps_Quest_Info.wPos_Y + iIconHeight > iGpsMapHeight + m_Gps_Base_Info.iY)
			Gps_Quest_Info.wPos_Y	= iGpsMapHeight + m_Gps_Base_Info.iY - m_pIconSpk->GetHeight(Gps_Quest_Info.wIndex + GPS_QUEST_WAIT);
	}
}
#endif	// GameMapToGpsMapQuestPos;


#if __CONTENTS(__QUEST_RENEWAL)
	bool	C_GPS_MAP::GetIconRollOverExplanationView(int iPox_X, int iPox_Y, bool bButtonClcik)	
		//마우스가 Icon에 롤 오버되면 Icon에 해당 하는 정보를 보여준다.
#else
	bool	C_GPS_MAP::GetIconRollOverExplanationView(int iPox_X, int iPox_Y)	
	//마우스가 Icon에 롤 오버되면 Icon에 해당 하는 정보를 보여준다.
#endif
{
	bool bResult	= false;	// 아이콘의 클릭된 상태값 (현재는 퀘스트 아이콘이 클릭 된 상태만 알려준다.)

	for(int i = 0; i < m_Gps_Potal_Info.size(); i++)
	{
		if(m_Gps_Potal_Info[i].S_Gps_Game_Map_Info.wID	== m_iZoneID)
		{
			if(iPox_X >= m_Gps_Potal_Info[i].wPos_X && 
				iPox_X <= m_pIconSpk->GetWidth(m_Gps_Potal_Info[i].wSpkIndex) + m_Gps_Potal_Info[i].wPos_X &&
				iPox_Y >= m_Gps_Potal_Info[i].wPos_Y &&
				iPox_Y <= m_pIconSpk->GetHeight(m_Gps_Potal_Info[i].wSpkIndex) + m_Gps_Potal_Info[i].wPos_Y)
			{
				g_descriptor_manager.Set(DID_INFO, gpC_mouse_pointer->GetPointerX(), gpC_mouse_pointer->GetPointerY(), const_cast<char *>(m_Gps_Potal_Info[i].chExplanation.c_str()) );
			}
		}
	}

	for(i = 0; i < m_Gps_Npc_Info.size(); i++)
	{
		if(m_Gps_Npc_Info[i].S_Gps_Game_Map_Info.wID	== m_iZoneID)
		{
			if(iPox_X >= m_Gps_Npc_Info[i].wPos_X && 
				iPox_X <= m_pIconSpk->GetWidth(m_Gps_Npc_Info[i].wSpkIndex) + m_Gps_Npc_Info[i].wPos_X &&
				iPox_Y >= m_Gps_Npc_Info[i].wPos_Y && 
				iPox_Y <= m_pIconSpk->GetHeight(m_Gps_Npc_Info[i].wSpkIndex) + m_Gps_Npc_Info[i].wPos_Y)
			{
				m_Npc_string.sz_main_str	= const_cast<char *>(m_Gps_Npc_Info[i].pchName.c_str());
				m_Npc_string.sz_main_str2	= NULL;
				m_Npc_string.sz_sub_str		= const_cast<char *>(m_Gps_Npc_Info[i].chExplanation.c_str());

//				m_Npc_string.sz_main_str	= NULL;	// 모두 널이면 실행시 메모리 오류가 난다.
//				m_Npc_string.sz_main_str2	= NULL;	// 헬프 스트링이 전역 적이지 못하면 메모리 오류가 난다.
//				m_Npc_string.sz_sub_str		= NULL; // 다른 사람의 소스를 보면 멤버 변수나 혹은 static로 글로벌로 선언이 되어 있을 것이다.
													// 왜 에러가 나는지는 모르겠다.
													// m_Npc_string 이 변수를 지역으로 선언하면 메모리 오류가 난다.
				g_descriptor_manager.Set(DID_HELP, gpC_mouse_pointer->GetPointerX(), gpC_mouse_pointer->GetPointerY(), &m_Npc_string);
			}
		}
	}

	for(i = 0; i < m_Gps_Party_Info.size(); i++)
	{
		if(m_Gps_Party_Info[i].S_Gps_Game_Map_Info.wID	== m_iZoneID)
		{
			if(iPox_X >= m_Gps_Party_Info[i].wPos_X && 
				iPox_X <= m_pIconSpk->GetWidth(m_Gps_Npc_Info[i].wSpkIndex) + m_Gps_Party_Info[i].wPos_X &&
				iPox_Y >= m_Gps_Party_Info[i].wPos_Y && 
				iPox_Y <= m_pIconSpk->GetHeight(m_Gps_Npc_Info[i].wSpkIndex) + m_Gps_Party_Info[i].wPos_Y)
			{
				char	chIToA[5];
//				m_Gps_Party_Info[i].pchName.clear();
//				m_Gps_Party_Info[i].pchName.resize(0);

				memset((char*)m_chXY, NULL, sizeof(m_chXY));
				memset((char*)chIToA, NULL, sizeof(chIToA));

				strcat(m_chXY,"X:");
				itoa(m_Gps_Party_Info[i].wPos_X, chIToA, 10);
				strcat(m_chXY,chIToA);

				strcat(m_chXY,",  ");
				strcat(m_chXY,"Y:");

				memset((char*)chIToA, NULL, sizeof(chIToA));
				itoa(m_Gps_Party_Info[i].wPos_Y, chIToA, 10);
				strcat(m_chXY,chIToA);

				m_Npc_string.sz_main_str	= g_pParty->GetMemberInfo(i)->Name.GetString();
				m_Npc_string.sz_main_str2	= NULL;
				m_Npc_string.sz_sub_str		= m_chXY;

//				m_Gps_Party_Info[i].pchName.insert(0, m_chXY);
//				m_Npc_string.sz_sub_str		= const_cast<char *>(m_Gps_Party_Info[i].pchName.c_str());

//				m_Npc_string.sz_main_str	= NULL;	// 모두 널이면 실행시 메모리 오류가 난다.
//				m_Npc_string.sz_main_str2	= NULL;	// 헬프 스트링이 전역 적이지 못하면 메모리 오류가 난다.
//				m_Npc_string.sz_sub_str		= NULL; // 다른 사람의 소스를 보면 멤버 변수나 혹은 static로 글로벌로 선언이 되어 있을 것이다.
													// 왜 에러가 나는지는 모르겠다.
													// m_Npc_string 이 변수를 지역으로 선언하면 메모리 오류가 난다.
				g_descriptor_manager.Set(DID_HELP, gpC_mouse_pointer->GetPointerX(), gpC_mouse_pointer->GetPointerY(), &m_Npc_string);
			}
		}
	}

#if __CONTENTS(__QUEST_RENEWAL)	
	for(i = 0; i < m_Gps_Quest_Info.size(); i++)
	{
		if(m_Gps_Quest_Info[i].bQuestShow	== false)
			continue;

		if(m_Gps_Quest_Info[i].S_Gps_Game_Map_Info.wID	== m_iZoneID)
		{
			if(iPox_X >= m_Gps_Quest_Info[i].wPos_X && 
				iPox_X <= m_pIconSpk->GetWidth(m_Gps_Quest_Info[i].wIndex + GPS_QUEST_WAIT) + m_Gps_Quest_Info[i].wPos_X &&
				iPox_Y >= m_Gps_Quest_Info[i].wPos_Y && 
				iPox_Y <= m_pIconSpk->GetHeight(m_Gps_Quest_Info[i].wIndex + GPS_QUEST_WAIT) + m_Gps_Quest_Info[i].wPos_Y)
			{
				m_strTemp	= m_Gps_Quest_Info[i].strQuestExplanation_GpsView;
				if(m_Gps_Quest_Info[i].wIndex == QUEST_RUN)
				{
					std::string buffer = (*g_pGameStringTable)[UI_STRING_GQUEST_DOING_BRACKET].GetString();
					m_strTemp	+= " ";
					m_strTemp	+= buffer;
				}
				else
				{
					std::string buffer = (*g_pGameStringTable)[UI_STRING_GQUEST_STANDING_BRACKET].GetString();
					m_strTemp	+= " ";
					m_strTemp	+= buffer;
				}


				m_Npc_string.sz_main_str	= const_cast<char *>(m_Gps_Quest_Info[i].strQuestName_GpsView.c_str());
				m_Npc_string.sz_main_str2	= NULL;
				m_Npc_string.sz_sub_str		= const_cast<char *>(m_strTemp.c_str());

				g_descriptor_manager.Set(DID_HELP, gpC_mouse_pointer->GetPointerX(), gpC_mouse_pointer->GetPointerY(), &m_Npc_string);
				if(bButtonClcik)
					bResult	= true;
			}
		}
	}
#endif	// __QUEST_RENEWAL

	return bResult;
}

#if __CONTENTS(__MOVE_ZONE)
bool	C_GPS_MAP::SetMoveZone(int iPox_X, int iPox_Y)
{
	// 2008.11.7 ij-ch
	RECT _rcBoundCheck = {0,};
	POINT _ptBoundCheck = {0,};

	SetRect(&_rcBoundCheck,m_Gps_Base_Info.iX,m_Gps_Base_Info.iY,m_Gps_Base_Info.iX+m_Gps_Base_Info.iWidht,m_Gps_Base_Info.iY+m_Gps_Base_Info.iHeight);
	_ptBoundCheck.x = iPox_X;
	_ptBoundCheck.y = iPox_Y;

	if(PtInRect(&_rcBoundCheck,_ptBoundCheck))
	{
		MZone* pZone = new MZone;
		ZONETABLE_INFO *pZoneInfo = g_pZoneTable->Get(m_iZoneID);
		MString mapFileName = pZoneInfo->Filename;
	
		/*
		// 정확한 Zone 가로 세로 (속도가 느리다)
		ivfstream file;
		if(!FileOpenBinary(mapFileName.GetString(), file))
		{
			return FALSE;
		}
	
		if(!pZone->LoadFromFile(file))
		{
			return FALSE;
		}
				
		file.close();

		int _zw = pZone->GetWidth();
		int _zh = pZone->GetHeight();
				
		pZone->Release();
		delete pZone;
		pZone = NULL;
		*/

		// Gps "◀" PotalInfo에 존재하는 Zone 가로 세로(속도가 빠르다)
		int _zw = m_Gps_Potal_Info[0].S_Gps_Game_Map_Info.wMapSize_Width;
		int _zh = m_Gps_Potal_Info[0].S_Gps_Game_Map_Info.wMapSize_Height;
	
		int _i_w = m_Gps_Base_Info.iWidht;
		int _i_h = m_Gps_Base_Info.iHeight;

		int _ml_x = _ptBoundCheck.x-_rcBoundCheck.left;
		int _ml_y = _ptBoundCheck.y-_rcBoundCheck.top;

		int _mov_x = (_zw*_ml_x)/_i_w;
		int _mov_y = (_zh*_ml_y)/_i_h;
		
		gpC_mouse_pointer->SetMoveZoneInfo(m_iZoneID,_mov_x,_mov_y,30,iPox_X,iPox_Y);

		return TRUE;
	}
	
	return FALSE;
}
#endif //__MOVE_ZONE

S_GPS_MONSTER_INFO	C_GPS_MAP::GetMonsterInfo()			//월드맵에서 클릭된 ZoneID에 해당하는 몬스터 정보를 넘겨준다.
{
	S_GPS_MONSTER_INFO MonsterInfo;
	MonsterInfo.wZoneID			= 0;
//	MonsterInfo.pchFieldName	= NULL;
	MonsterInfo.wMonsterLv1		= 0;
	MonsterInfo.wMonsterLv2		= 0;

	for(int i = 0; i < m_MonsterInfo.size(); i++)
	{
		if(m_iZoneID == m_MonsterInfo[i].wZoneID)
		{
			MonsterInfo.pchFieldName	= m_MonsterInfo[i].pchFieldName;
			MonsterInfo.wZoneID			= m_MonsterInfo[i].wZoneID;
			MonsterInfo.wMonsterLv1		= m_MonsterInfo[i].wMonsterLv1;
			MonsterInfo.wMonsterLv2		= m_MonsterInfo[i].wMonsterLv2;
		}
	}
	return MonsterInfo;
}

void	C_GPS_MAP::SetSelectMapIndex(int iZoneID)		//
{
	switch(iZoneID)
	{
	case WORLDMAP_ID_LIMBO_NW:
		m_iSelectMapIndex	= WORLDMAP_SELECT_LIMBO_NW;
	break;
	case WORLDMAP_ID_LIMBO_NE:
		m_iSelectMapIndex	= WORLDMAP_SELECT_LIMBO_NE;
	break;
	case WORLDMAP_ID_LIMBO_SW:
		m_iSelectMapIndex	= WORLDMAP_SELECT_LIMBO_SW;
	break;
	case WORLDMAP_ID_LIMBO_SE:
		m_iSelectMapIndex	= WORLDMAP_SELECT_LIMBO_SE;
	break;


	case WORLDMAP_ID_ESL_NW:
		m_iSelectMapIndex	= WORLDMAP_SELECT_ESL_NW;
	break;
	case WORLDMAP_ID_ESL_NE:
		m_iSelectMapIndex	= WORLDMAP_SELECT_ESL_NE;
	break;
	case WORLDMAP_ID_ESL_SW:
		m_iSelectMapIndex	= WORLDMAP_SELECT_ESL_SW;
	break;
	case WORLDMAP_ID_ESL_SE:
		m_iSelectMapIndex	= WORLDMAP_SELECT_ESL_SE;
	break;

	case WORLDMAP_ID_LODIN_NW:
		m_iSelectMapIndex	= WORLDMAP_SELECT_LODIN_NW;
	break;
	case WORLDMAP_ID_LODIN_NE:
		m_iSelectMapIndex	= WORLDMAP_SELECT_LODIN_NE;
	break;
	case WORLDMAP_ID_LODIN_SW:
		m_iSelectMapIndex	= WORLDMAP_SELECT_LODIN_SW;
	break;
	case WORLDMAP_ID_LODIN_SE:
		m_iSelectMapIndex	= WORLDMAP_SELECT_LODIN_SE;
	break;

	case WORLDMAP_ID_CASTALO_NE:
		m_iSelectMapIndex	= WORLDMAP_SELECT_CASTALO_NE;
	break;

	case WORLDMAP_ID_DROBETA_NW:
		m_iSelectMapIndex	= WORLDMAP_SELECT_DROBETA_NW;
	break;
	case WORLDMAP_ID_DROBETA_NE:
		m_iSelectMapIndex	= WORLDMAP_SELECT_DROBETA_NE;
	break;
	case WORLDMAP_ID_DROBETA_SW:
		m_iSelectMapIndex	= WORLDMAP_SELECT_DROBETA_SW;
	break;
	case WORLDMAP_ID_DROBETA_SE:
		m_iSelectMapIndex	= WORLDMAP_SELECT_DROBETA_SE;
	break;

	case WORLDMAP_ID_BRANCO_NW:
		m_iSelectMapIndex	= WORLDMAP_SELECT_BRANCO_NW;
	break;
	case WORLDMAP_ID_BRANCO_NE:
		m_iSelectMapIndex	= WORLDMAP_SELECT_BRANCO_NE;
	break;
	case WORLDMAP_ID_BRANCO_SW:
		m_iSelectMapIndex	= WORLDMAP_SELECT_BRANCO_SW;
	break;
	case WORLDMAP_ID_BRANCO_SE:
		m_iSelectMapIndex	= WORLDMAP_SELECT_BRANCO_SE;
	break;

	case WORLDMAP_ID_PERONA_NW:
		m_iSelectMapIndex	= WORLDMAP_SELECT_PERONA_NW;
	break;
	case WORLDMAP_ID_PERONA_NE:
		m_iSelectMapIndex	= WORLDMAP_SELECT_PERONA_NE;
	break;
	case WORLDMAP_ID_PERONA_SW:
		m_iSelectMapIndex	= WORLDMAP_SELECT_PERONA_SW;
	break;
	case WORLDMAP_ID_PERONA_SE:
		m_iSelectMapIndex	= WORLDMAP_SELECT_PERONA_SE;
	break;

	case WORLDMAP_ID_TIMOR_NW:
		m_iSelectMapIndex	= WORLDMAP_SELECT_TIMOR_NW;
	break;
	case WORLDMAP_ID_TIMOR_NE:
		m_iSelectMapIndex	= WORLDMAP_SELECT_TIMOR_NE;
	break;
	case WORLDMAP_ID_TIMOR_SW:
		m_iSelectMapIndex	= WORLDMAP_SELECT_TIMOR_SW;
	break;
	case WORLDMAP_ID_TIMOR_SE:
		m_iSelectMapIndex	= WORLDMAP_SELECT_TIMOR_SE;
	break;
	}
}


int	C_GPS_MAP::GetSelectMapIndex()
{
	return m_iSelectMapIndex;
}

#if __CONTENTS(__QUEST_RENEWAL)	//GPS	AddQuestInfo();	정의 부분
void	C_GPS_MAP::AddQuestInfo(S_QUESTICON_INFO QuestInfo)
{
	m_Gps_Quest_Info_temp.clear();
	m_Gps_Quest_Info_temp.resize(0);

	if(QuestInfo.S_Gps_Game_Map_Info.wID	== WORLDMAP_ID_PERONA_SW || QuestInfo.S_Gps_Game_Map_Info.wID	== WORLDMAP_ID_PERONA_SE
		|| QuestInfo.S_Gps_Game_Map_Info.wID	== WORLDMAP_ID_PERONA_NW || QuestInfo.S_Gps_Game_Map_Info.wID	== WORLDMAP_ID_PERONA_NE)
	{
		QuestInfo.S_Gps_Game_Map_Info.wMapSize_Height	= 256;
		QuestInfo.S_Gps_Game_Map_Info.wMapSize_Width	= 128;
	}
	else
	{	
		QuestInfo.S_Gps_Game_Map_Info.wMapSize_Height	= 256;
		QuestInfo.S_Gps_Game_Map_Info.wMapSize_Width	= 256;
	}

	if(QuestInfo.btStatus	== C_VS_UI_QUEST_LIST::CAN_REPLAY || QuestInfo.btStatus	== C_VS_UI_QUEST_LIST::CAN_ACCEPT 
		|| QuestInfo.btStatus	== C_VS_UI_QUEST_LIST::CANNOT)
	{
		std::string buffer = (*g_pGameStringTable)[UI_STRING_GQUEST_QUEST].GetString();
		buffer += (*g_pGameStringTable)[UI_STRING_GQUEST_STANDING_BRACKET].GetString();
		QuestInfo.strQuestName_WorldView		= buffer;
		QuestInfo.wIndex	+= QUEST_WAIT;
	}
	else if(QuestInfo.btStatus	== C_VS_UI_QUEST_LIST::SUCCESS || QuestInfo.btStatus	== C_VS_UI_QUEST_LIST::DOING)
	{
		std::string buffer = (*g_pGameStringTable)[UI_STRING_GQUEST_QUEST].GetString();
		buffer = (*g_pGameStringTable)[UI_STRING_GQUEST_DOING_BRACKET].GetString();
		QuestInfo.strQuestName_WorldView		= buffer;
		QuestInfo.wIndex	+= QUEST_RUN;
	}
	else if(QuestInfo.btStatus	== C_VS_UI_QUEST_LIST::COMPLETE || QuestInfo.btStatus	== C_VS_UI_QUEST_LIST::FAIL)
	{
		QuestInfo.bQuestShow	= false;
	}

	if(GetWorldMapZoneIDExistenceFind(QuestInfo.S_Gps_Game_Map_Info.wID))	//Zone ID가 월드맵 상의 필드가 아니면 보여주지 않는다.
	{
		QuestInfo.bQuestShow	= false;
	}

	m_Gps_Quest_Info.push_back(QuestInfo);
	m_Gps_Quest_Info_temp	= m_Gps_Quest_Info;
}
#endif	//__QUEST_RENEWAL


//-----------------------------------------------------------------------------
// C_GPS_SCROLL
//
//-----------------------------------------------------------------------------
C_GPS_SCROLL::C_GPS_SCROLL()
{
	memset((S_GPS_BASE_INFO*)&m_Track_Info, NULL, sizeof(S_GPS_BASE_INFO));
	memset((S_GPS_BASE_INFO*)&m_UpButton_Info, NULL, sizeof(S_GPS_BASE_INFO));
	memset((S_GPS_BASE_INFO*)&m_DownButton_Info, NULL, sizeof(S_GPS_BASE_INFO));
	memset((S_GPS_BASE_INFO*)&m_Bar_Info, NULL, sizeof(S_GPS_BASE_INFO));
	m_iRange			= 0;
	m_iTrackCount		= 0;
	m_fTrackBarMoveSize	= 0;
	m_fTrackBartmp_Y	= 0;

	m_bUpButtonShow		= false;
	m_bDownButtonShow	= false;
}

C_GPS_SCROLL::~C_GPS_SCROLL()
{
	memset((S_GPS_BASE_INFO*)&m_Track_Info, NULL, sizeof(S_GPS_BASE_INFO));
	memset((S_GPS_BASE_INFO*)&m_UpButton_Info, NULL, sizeof(S_GPS_BASE_INFO));
	memset((S_GPS_BASE_INFO*)&m_DownButton_Info, NULL, sizeof(S_GPS_BASE_INFO));
	memset((S_GPS_BASE_INFO*)&m_Bar_Info, NULL, sizeof(S_GPS_BASE_INFO));
	m_iRange			= 0;
	m_iTrackCount		= 0;
	m_fTrackBarMoveSize	= 0;
	m_fTrackBartmp_Y	= 0;

	m_bUpButtonShow		= false;
	m_bDownButtonShow	= false;
}

void	C_GPS_SCROLL::ScrollView()
{
	if(m_Track_Info.bHide)
		return;

	if(m_Track_Info.spk)
		m_Track_Info.spk->BltLocked(m_Track_Info.iX, m_Track_Info.iY, m_Track_Info.wSpkIndex);
	
	if(m_bUpButtonShow)
	{
		if(m_UpButton_Info.spk)
			m_UpButton_Info.spk->BltLocked(m_UpButton_Info.iX, m_UpButton_Info.iY, m_UpButton_Info.wSpkIndex);
	}

	if(m_bDownButtonShow)
	{
		if(m_DownButton_Info.spk)
			m_DownButton_Info.spk->BltLocked(m_DownButton_Info.iX, m_DownButton_Info.iY, m_DownButton_Info.wSpkIndex);
	}

	if(m_Bar_Info.spk)
		m_Bar_Info.spk->BltLocked(m_Bar_Info.iX, m_Bar_Info.iY, m_Bar_Info.wSpkIndex);
}

void	C_GPS_SCROLL::SetScroll(S_GPS_BASE_INFO Track_Info, S_GPS_BASE_INFO UpButton_Info, S_GPS_BASE_INFO DownButton_Info,
								S_GPS_BASE_INFO Bar_Info, int iRange)
{
	m_Track_Info		= Track_Info; 
	m_UpButton_Info		= UpButton_Info;
	m_DownButton_Info	= DownButton_Info;

//	if(m_iTrackCount)
	m_Bar_Info			= Bar_Info;
	m_Bar_Info.iY		= Bar_Info.iY + (int)m_fTrackBartmp_Y;	//m_fTrackBartmp_Y움직여진 트랙 바의 위치

	m_iRange			= iRange;	//움직일수 있는 트랙바의 범위
}

void	C_GPS_SCROLL::ScrollUpButton()
{
	m_iTrackCount--;
	if(m_iTrackCount < 0)
	{
		m_iTrackCount = 0;
		return;
	}

	m_fTrackBarMoveSize	= (float)(float)(m_Track_Info.iHeight - m_Bar_Info.iHeight) / (float)m_iRange;	//소수점을 가지고 있으면 스크롤 바의 움직임이 조금더
	//정확해 진다.
	m_fTrackBartmp_Y	-= m_fTrackBarMoveSize;	

	if(m_Bar_Info.iY < m_UpButton_Info.iY + m_UpButton_Info.iHeight)
	{
		m_fTrackBartmp_Y	= 0;
	}
}

void	C_GPS_SCROLL::ScrollDownButton()
{
	m_iTrackCount++;
	if(m_iTrackCount > m_iRange)
	{
		m_iTrackCount = m_iRange;
		return;
	}

	m_fTrackBarMoveSize	= (float)(float)(m_Track_Info.iHeight - m_Bar_Info.iHeight) / (float)m_iRange;
	m_fTrackBartmp_Y	+= m_fTrackBarMoveSize;

	if(m_Bar_Info.iY + m_Bar_Info.iHeight > m_DownButton_Info.iY)
	{
		m_fTrackBartmp_Y	= m_Track_Info.iHeight - m_Bar_Info.iHeight;
	}
}

void	C_GPS_SCROLL::TrackBarMove()
{
}

bool	C_GPS_SCROLL::GetScrollUpButtonRollOver(int iPos_X, int iPos_Y, bool bClick, bool bWheel)			//스크롤 업 버튼에 마우스가 올려지거나 클릭 되면 실행
{
	if(iPos_X > m_UpButton_Info.iX && iPos_X < m_UpButton_Info.iX + m_UpButton_Info.iWidht &&
		iPos_Y > m_UpButton_Info.iY && iPos_Y < m_UpButton_Info.iY + m_UpButton_Info.iHeight && bClick)		//스크롤 업 버튼이 클릭 되었다.
	{
		UpButtonShow(false);
		ScrollUpButton();
		return true;
	}
	else if(iPos_X > m_UpButton_Info.iX && iPos_X < m_UpButton_Info.iX + m_UpButton_Info.iWidht &&			//스크롤 업 버튼에 마우스 롤 오버 상태
		iPos_Y > m_UpButton_Info.iY && iPos_Y < m_UpButton_Info.iY + m_UpButton_Info.iHeight)
	{
		UpButtonShow(true);
	}
	else if(bWheel)																							//휠 업
	{
		UpButtonShow(false);
		ScrollUpButton();
		return true;
	}
	else																									//어떤 조건도 만족 하지 않을 때
	{
		UpButtonShow(false);
	}
	return false;
}

bool	C_GPS_SCROLL::GetScrollDownButtonRollOver(int iPos_X, int iPos_Y, bool bClick, bool bWheel)			//GetScrollUpButtonRollOver함수와 동일(단, 아래를 지향 한다.)
{
	if(iPos_X > m_DownButton_Info.iX && iPos_X < m_DownButton_Info.iX + m_DownButton_Info.iWidht &&
		iPos_Y > m_DownButton_Info.iY && iPos_Y < m_DownButton_Info.iY + m_DownButton_Info.iHeight && bClick)
	{
		ScrollDownButton();
		DownButtonShow(false);
		return true;
	}
	else if(iPos_X > m_DownButton_Info.iX && iPos_X < m_DownButton_Info.iX + m_DownButton_Info.iWidht &&
		iPos_Y > m_DownButton_Info.iY && iPos_Y < m_DownButton_Info.iY + m_DownButton_Info.iHeight)
	{
		DownButtonShow(true);
	}
	else if(bWheel)
	{
		DownButtonShow(false);
		ScrollDownButton();
		return true;
	}
	else
	{
		DownButtonShow(false);
	}

	return false;
}

int		C_GPS_SCROLL::GetScrollCount()	
{
	return m_iTrackCount;					//아래 방향으로 몇칸 내려 갔는지 알고 있는 변수
}


void	C_GPS_SCROLL::UpButtonShow(bool bShow)
{
	m_bUpButtonShow		= bShow;
}

void	C_GPS_SCROLL::DownButtonShow(bool bShow)
{
	m_bDownButtonShow	= bShow;
}

//-----------------------------------------------------------------------------
// C_LIST
//
//-----------------------------------------------------------------------------
C_GPS_LIST::C_GPS_LIST()
{
	m_iLinePos_X			= LINEPOS_X;
	m_iLinePos_Y			= LINEPOS_Y;
	m_iListHeight			= LISTHEIGHT;
	m_iItemCount			= 0;
	m_iItemViewStartIndex	= 0;
	m_iListFocus			= -1;
	m_iListSelectFocus		= -1;
	m_bfirst				= true;
	m_bMouseClick			= false;

	m_ItemName.clear();
	m_ListItem.clear();
	m_ItemName.resize(0);
	m_ListItem.resize(0);

	memset((S_GPS_BASE_INFO*)&m_Gps_Base_Info, NULL, sizeof(m_Gps_Base_Info));
	memset((S_LIST_ITEM_POS*)m_Lip, NULL, sizeof(m_Lip));
	SetListItem();
}

C_GPS_LIST::~C_GPS_LIST()
{
	m_iLinePos_X			= LINEPOS_X;
	m_iLinePos_Y			= LINEPOS_Y;
	m_iListHeight			= LISTHEIGHT;
	m_iItemCount			= 0;
	m_iItemViewStartIndex	= 0;
	m_iListFocus			= -1;
	m_iListSelectFocus		= -1;
	m_ItemName.clear();
	m_ListItem.clear();

	m_bfirst				= true;
	m_bMouseClick			= false;

	m_ItemName.resize(0);
	m_ListItem.resize(0);
	memset((S_GPS_BASE_INFO*)&m_Gps_Base_Info, NULL, sizeof(m_Gps_Base_Info));
	memset((S_LIST_ITEM_POS*)m_Lip, NULL, sizeof(m_Lip));
}

void	C_GPS_LIST::ListView()
{
}

int		C_GPS_LIST::GetZoneID()
{
	if(m_ListItem.size() > 0)
		return m_iZoneID	= m_ListItem[m_iListSelectFocus].wZoneID;
	return 0;
}

void	C_GPS_LIST::SetList(S_GPS_BASE_INFO Gps_Base_Info)
{
	m_Gps_Base_Info	= Gps_Base_Info;

	m_iLinePos_X	= m_Gps_Base_Info.iX + LINEPOS_X;
	m_iLinePos_Y	= m_Gps_Base_Info.iY + LINEPOS_Y;

	S_GPS_BASE_INFO Track_Info;
	S_GPS_BASE_INFO UpButton_Info;		//지금은 트랙 하나를 사용하고 있다. UP버튼이미지를 받고 다시 진행 해야함.
	S_GPS_BASE_INFO DownButton_Info;
	S_GPS_BASE_INFO Bar_Info;
	int				iScrollRange	= 0;

	memset((S_LIST_ITEM_POS*)m_Lip, NULL, sizeof(m_Lip));
	for(UINT i = 0; i < LISTITEMVIEWCOUNT; i++)
	{
		m_Lip[i].iItemPos_X		= m_iLinePos_X + 10;
		m_Lip[i].iItemPos_Y		= m_iLinePos_Y + 3;
		m_Lip[i].iListHeight	= LISTHEIGHT;
		m_Lip[i].iListWidht		= LISTWIDHT;

		if(i > 0)
			m_Lip[i].iItemPos_Y		= m_Lip[i-1].iItemPos_Y + LISTHEIGHT + 1;
	}

	UpButton_Info				= m_Gps_Base_Info;
	UpButton_Info.wSpkIndex		= GPS_SCROLLUP_BUTTON;
	UpButton_Info.iX			= m_Gps_Base_Info.iX + LINEPOS_X + LISTWIDHT + 19;	//4리스트 라인선의 넓이
	UpButton_Info.iY			= m_Gps_Base_Info.iY + LINEPOS_Y;
	UpButton_Info.iWidht		= UpButton_Info.spk->GetWidth(GPS_SCROLLUP_BUTTON);
	UpButton_Info.iHeight		= UpButton_Info.spk->GetHeight(GPS_SCROLLUP_BUTTON);

	Track_Info					= UpButton_Info;
	Track_Info.wSpkIndex		= GPS_SCROLLTRACK;
	Track_Info.iWidht			= Track_Info.spk->GetWidth(GPS_SCROLLTRACK);
	Track_Info.iHeight			= Track_Info.spk->GetHeight(GPS_SCROLLTRACK) - (UpButton_Info.iHeight * 2); // 다운버튼이랑 업 버튼은 같다.

	DownButton_Info				= Track_Info;
	DownButton_Info.wSpkIndex	= GPS_SCROLLDOWN_BUTTON;
	DownButton_Info.iY			= Track_Info.iY + Track_Info.iHeight + UpButton_Info.iHeight;
	DownButton_Info.iWidht		= DownButton_Info.spk->GetWidth(GPS_SCROLLDOWN_BUTTON);
	DownButton_Info.iHeight		= DownButton_Info.spk->GetHeight(GPS_SCROLLDOWN_BUTTON);

	Bar_Info					= UpButton_Info;
	Bar_Info.wSpkIndex			= GPS_SCROLLTOMB_BUTTON;
	Bar_Info.iX					= UpButton_Info.iX + 1;			//1리스트은 라인선의 넓이
	Bar_Info.iY					= UpButton_Info.iY + UpButton_Info.spk->GetHeight(GPS_SCROLLUP_BUTTON) + 1;

	iScrollRange	= m_iItemCount - LISTITEMVIEWCOUNT;	//총 아이템 목록의 개수 - 보여지는 리스트의 개수 (예를 들어 항목의 개수가 10이라면 항목이 보여지는 개수
														//는 6개 즉 스크롤 에서 카운트 될수 있는 범위는 4가 된다.

	Track_Info.iHeight			= Track_Info.spk->GetHeight(GPS_SCROLLTRACK) - UpButton_Info.iHeight - DownButton_Info.spk->GetHeight(GPS_SCROLLDOWN_BUTTON);
	SetScroll(Track_Info, UpButton_Info, DownButton_Info, Bar_Info, iScrollRange);
}

S_GPS_MONSTER_INFO	C_GPS_LIST::GetSelectListItem()
{
	return m_SelectListItem;
}


void	C_GPS_LIST::ItemTextView()
{
	if(m_Gps_Base_Info.bHide)
		return;
	
	m_iItemViewStartIndex	= GetScrollCount();
	for(int i = 0; i < m_iItemCount - m_iItemViewStartIndex; i++)
	{
		if(i < LISTITEMVIEWCOUNT)
		{
			if(m_iListFocus == i + m_iItemViewStartIndex)
			{
				g_PrintColorStr(m_Lip[i].iItemPos_X, m_Lip[i].iItemPos_Y, 
									m_ListItem[m_iItemViewStartIndex + i].pchFieldName.c_str(), gpC_base->m_chatting_pi,  RGB(255,128,0));
				if(m_ListItem[m_iItemViewStartIndex + i].pchMonsterLv.size())
					g_PrintColorStr(m_Lip[i].iItemPos_X + 215, m_Lip[i].iItemPos_Y, 
										m_ListItem[m_iItemViewStartIndex + i].pchMonsterLv.c_str(), gpC_base->m_chatting_pi,  RGB(255,128,0));
			}
			else
			{
				g_PrintColorStr(m_Lip[i].iItemPos_X, m_Lip[i].iItemPos_Y, 
									m_ListItem[m_iItemViewStartIndex + i].pchFieldName.c_str(), gpC_base->m_chatting_pi,  RGB(255,255,255));
				if(m_ListItem[m_iItemViewStartIndex + i].pchMonsterLv.size())
					g_PrintColorStr(m_Lip[i].iItemPos_X + 215, m_Lip[i].iItemPos_Y, 
										m_ListItem[m_iItemViewStartIndex + i].pchMonsterLv.c_str(), gpC_base->m_chatting_pi,  RGB(255,255,255));
				//gpC_base->m_chatting_pi 폰트의 자간과 폰트 사이즈 등  폰트 정보를 가지고 있는듯 
			}
		}
	}
}

int		C_GPS_LIST::GetItemCount()
{
	return m_iItemCount;
}

bool	C_GPS_LIST::ItemClick(int iPos_X, int iPos_Y, bool bMouseClick)	//아이템이 클릭 되었는지 확인 한다.
{
	m_iItemViewStartIndex	= GetScrollCount();
	m_bMouseClick			= bMouseClick;
//	static char *pchExplanation[5];

	for(int i = 0; i < m_iItemCount - m_iItemViewStartIndex; i++)			//아이템 항목의 개수 - 보여주어야 할 인덱스 만큼 확인 한다.
	{
		if(i < LISTITEMVIEWCOUNT)											//항목은 6개만 보여준다.
		{
			if(iPos_X >= m_Lip[i].iItemPos_X && iPos_X <= m_Lip[i].iItemPos_X + LISTWIDHT &&
				iPos_Y >= m_Lip[i].iItemPos_Y && iPos_Y <= m_Lip[i].iItemPos_Y + LISTHEIGHT)	//현재 인덱스가 롤오버 상태인 경우
			{
				const int ArraySize = 20;
				static char CharArray[ArraySize][256];
				static char *CharPtrArray[ArraySize];
				
				for(int j = 0; j < ArraySize; ++j)
				{
					memset(CharArray[j], 0, 256);
					strcpy(CharArray[j], m_ListItem[m_iItemViewStartIndex + i].pchExplanation[j].c_str());
					CharPtrArray[j] = CharArray[j];
				}
				
				m_iListFocus = i + m_iItemViewStartIndex;

//				g_descriptor_manager.Set(DID_STRINGS,iPos_X,iPos_Y, (void*)pchExplanation, 2);


				if(m_ListItem[m_iItemViewStartIndex + i].wExplanationCount > 0)
					g_descriptor_manager.Set(DID_STRINGS,iPos_X,iPos_Y, CharPtrArray,
												m_ListItem[m_iItemViewStartIndex + i].wExplanationCount);

				if(m_bMouseClick)
				{
					m_SelectListItem.wMonsterLv1	= m_ListItem[m_iItemViewStartIndex + i].wMonsterLv1;
					m_SelectListItem.wMonsterLv2	= m_ListItem[m_iItemViewStartIndex + i].wMonsterLv2;
					m_SelectListItem.wZoneID		= m_ListItem[m_iItemViewStartIndex + i].wZoneID;
					m_SelectListItem.pchFieldName	= m_ListItem[m_iItemViewStartIndex + i].pchFieldName;
					m_SelectListItem.pchMonsterLv	= m_ListItem[m_iItemViewStartIndex + i].pchMonsterLv;

					m_iListSelectFocus				= m_iListFocus;
					return true;
				}
			}
		}
	}
	return false;
}

void	C_GPS_LIST::SetListItem()				//몬스터의 정보를 설정 한다.
{
	S_GPS_MONSTER_INFO ListItemInfo;
	m_ListItem.clear();
	m_ListItem.resize(0);

	DWORD								dwSize					= g_pGpsInfoTable->GetListMonsterInfoSize();
	std::vector<SGPS_MONSTER_INFO>		SGps_ListMonster_Info	= g_pGpsInfoTable->GetListMonsterInfo();

	for(DWORD i = 0; i < dwSize; i++)
	{
		ListItemInfo.Release();

		ListItemInfo.wZoneID			= SGps_ListMonster_Info[i].wZoneID;
		ListItemInfo.pchFieldName		= SGps_ListMonster_Info[i].strZoneName.GetString();
		//clear(),resize(0) 시에 초기화 되기때문에 없을때 굳이 넣어줄필요가 없다. 넣으주면 0사이즈의 스트링이 = 오퍼레이터를 통해 0 랭스를 구하려다 튕 해버린다.
		if(SGps_ListMonster_Info[i].strMonsterLv.GetLength() != 0)
			ListItemInfo.pchMonsterLv		= SGps_ListMonster_Info[i].strMonsterLv.GetString();

		for(DWORD j = 0; j < SGps_ListMonster_Info[i].wExplanationCount; j++)
		{
			ListItemInfo.wExplanationCount	= SGps_ListMonster_Info[i].wExplanationCount;
			ListItemInfo.pchExplanation[j]	= SGps_ListMonster_Info[i].strExplanation[j].GetString();
		}

		ListItemInfo.wMonsterLv1		= SGps_ListMonster_Info[i].wMinMonsterLv;
		ListItemInfo.wMonsterLv2		= SGps_ListMonster_Info[i].wMaxMonsterLv;

		m_ListItem.push_back(ListItemInfo);
	}
	m_iItemCount	= m_ListItem.size();
}

//-----------------------------------------------------------------------------
// C_LISTMANAGER
//
//-----------------------------------------------------------------------------
C_LISTMANAGER::C_LISTMANAGER()
{
	m_bListShow	= true;
	memset((S_GPS_BASE_INFO*)&m_Gps_ListViewButton_Info, NULL, sizeof(S_GPS_BASE_INFO));
	memset((S_GPS_BASE_INFO*)&m_Gps_Base_Info, NULL, sizeof(S_GPS_BASE_INFO));
}

C_LISTMANAGER::~C_LISTMANAGER()
{
	m_bListShow	= true;
}

void	C_LISTMANAGER::ListManagerView(bool bSurfaceLock)
{
	if(m_bListShow != true)
		return;
	if(bSurfaceLock)
	{
		BoxView();
		ListView();
		ScrollView();
	}
	else
	{
		ItemTextView();
	}
}

void	C_LISTMANAGER::SetListManager(S_GPS_BASE_INFO Gps_Base_Info)
{
	m_Gps_Base_Info	= Gps_Base_Info;

	S_GPS_BASE_INFO	Box_Base_Info;
	S_GPS_BASE_INFO	List_Base_Info;

	Box_Base_Info				= m_Gps_Base_Info;
	Box_Base_Info.wSpkIndex		= GPS_LISTBOX;

	List_Base_Info				= Box_Base_Info;
	List_Base_Info.wSpkIndex	= GPS_LISTBOX;
	List_Base_Info.iY			+= 0;

	SetBox(Box_Base_Info);
	SetList(List_Base_Info);
}

void	C_LISTMANAGER::SetListShow(bool bListShow)
{
	m_bListShow	= bListShow;
}


bool	C_LISTMANAGER::GetListShow()
{
	return m_bListShow;
}

//-----------------------------------------------------------------------------
// C_GPSMANAGER
//
//-----------------------------------------------------------------------------
C_GPSMANAGER::C_GPSMANAGER()
{
	memset((S_GPS_BASE_INFO*)&m_Gps_Base_Info, NULL, sizeof(S_GPS_BASE_INFO));
	memset((char*)m_chMonster, NULL, sizeof(m_chMonster));
	memset((char*)m_chMonsterLv, NULL, sizeof(m_chMonsterLv));
	bMonsterLvView	= false;
}

C_GPSMANAGER::~C_GPSMANAGER()
{
	memset((S_GPS_BASE_INFO*)&m_Gps_Base_Info, NULL, sizeof(S_GPS_BASE_INFO));
	memset((char*)m_chMonster, NULL, sizeof(m_chMonster));
	memset((char*)m_chMonsterLv, NULL, sizeof(m_chMonsterLv));
	bMonsterLvView	= false;
}

void	C_GPSMANAGER::GPSManagerView(bool bSurfaceLock)
{
	if(m_Gps_Base_Info.bHide)
		return;
	
	if(bSurfaceLock)
	{
		BoxView();
		MapView();
		m_Gps_Close_Button.ButtonView();
		m_Gps_ListView_Button.ButtonView();
	}
	else
	{
		ZoneNameTextView();
		UserPosTextView();
		MonsterLvView();
	}
}

void	C_GPSMANAGER::SetGPSManager(S_GPS_BASE_INFO Box_Base_Info, C_SPRITE_PACK *mapspk, int iMapIndex, int iZoneID)
{
	S_GPS_BASE_INFO	Map_Base_Info;
	S_GPS_BASE_INFO	Close_Button_Base_Info;
	S_GPS_BASE_INFO	ListView_Button_Base_Info;

	m_Gps_Base_Info			= Box_Base_Info;

	Map_Base_Info			= Box_Base_Info;
	Close_Button_Base_Info	= Box_Base_Info;

	Map_Base_Info.iX		+= 9;
	Map_Base_Info.iY		+= 34;
	Map_Base_Info.iWidht	= mapspk->GetWidth(iMapIndex);
	Map_Base_Info.iHeight	= mapspk->GetHeight(iMapIndex);
	Map_Base_Info.spk		= mapspk;

	Box_Base_Info.wSpkIndex	= GPS_MAPBOX;
	Map_Base_Info.wSpkIndex	= iMapIndex;
	
	Close_Button_Base_Info				=	Box_Base_Info;
	Close_Button_Base_Info.iHeight		=	Close_Button_Base_Info.spk->GetHeight(GPS_CLOSEBUTTON1);
	Close_Button_Base_Info.iWidht		=	Close_Button_Base_Info.spk->GetWidth(GPS_CLOSEBUTTON1);
	Close_Button_Base_Info.iX			+=	475;
	Close_Button_Base_Info.iY			+=	Box_Base_Info.iHeight - 21;
	Close_Button_Base_Info.wSpkIndex	= GPS_CLOSEBUTTON1;

	ListView_Button_Base_Info			= Box_Base_Info;
	ListView_Button_Base_Info.iHeight	= ListView_Button_Base_Info.spk->GetHeight(GPS_DUNGEONVIEW_BUTTON1);
	ListView_Button_Base_Info.iWidht	= ListView_Button_Base_Info.spk->GetWidth(GPS_DUNGEONVIEW_BUTTON1);
	ListView_Button_Base_Info.iX		+= 38;
	ListView_Button_Base_Info.iY		= Map_Base_Info.iY + Map_Base_Info.iHeight + 7;
	ListView_Button_Base_Info.wSpkIndex	= GPS_DUNGEONVIEW_BUTTON1;

	SetBox(Box_Base_Info);
	SetMap(Map_Base_Info, iZoneID, Box_Base_Info.spk);
	m_Gps_Close_Button.SetButton(Close_Button_Base_Info);
	m_Gps_ListView_Button.SetButton(ListView_Button_Base_Info);
}

void	C_GPSMANAGER::SetMonsterLv(int iMinLv, int iMaxLv)
{
	MonsterLvUint(iMinLv, iMaxLv);
}

void	C_GPSMANAGER::SetMonsterLv(string strMonsterLv)
{
	memset((char*)m_chMonster, NULL, sizeof(m_chMonster));
	strcat(m_chMonster, strMonsterLv.c_str());
}

void	C_GPSMANAGER::MonsterLvUint(int iMinLv, int iMaxLv)			//몬스터 레벨을 단위별로 구한다.
{
	char chLv[10];

	if(iMinLv == 0 || iMaxLv == 0)
	{
		bMonsterLvView	= false;
		return;
	}
	bMonsterLvView	= true;

	memset((char*)m_chMonster, NULL, sizeof(m_chMonster));
	memset((char*)m_chMonsterLv, NULL, sizeof(m_chMonsterLv));
	memset((char*)chLv, NULL, sizeof(chLv));

#if __DESIGNED_KOREA
	strcat(m_chMonster, "Monster Level:  ");
#else
	strcat(m_chMonster, "Monster Level:  ");
#endif	// __DESIGNED_KOREA
	itoa(iMinLv, chLv, 10);
	strcat(m_chMonsterLv, chLv);
	itoa(iMaxLv, chLv, 10);
	strcat(m_chMonsterLv, " ~ ");
	strcat(m_chMonsterLv, chLv);

	strcat(m_chMonster, m_chMonsterLv);
}

void	C_GPSMANAGER::MonsterLvView()
{
	int iText_X	= 0;
	int iText_Y	= 0;

	iText_X	= m_Gps_Base_Info.iX + 210;
	iText_Y	= m_Gps_Base_Info.iY + 12;

	g_PrintColorStr(iText_X,  iText_Y, m_chMonster, gpC_base->m_desc_menu_pi,  RGB(255,128,0));
}


//-----------------------------------------------------------------------------
// C_VS_UI_GPS
//
//-----------------------------------------------------------------------------
C_VS_UI_GPS::C_VS_UI_GPS()
{
	g_RegisterWindow(this);
	
	m_C_GpsManager;
	m_C_ListManager;
	
	// TIMER
	m_dw_gps_prev_tickcount = GetTickCount();
	m_dw_gps_millisec = 100;

	m_mouse_move	= false;
	m_iGpsMapIndex	= 0;
	
	memset((S_GPS_BASE_INFO*)&m_GPS_Base_Info, NULL, sizeof(S_GPS_BASE_INFO));

	m_p_gps_surface = new CSpriteSurface;
	
	m_p_gps_surface->InitOffsurface(200, 100, DDSCAPS_SYSTEMMEMORY);
	m_p_gps_surface->SetTransparency(0xffff);

	switch( g_eRaceInterface )
	{
	case RACE_SLAYER:
		m_GPS_Base_Info.spk = new C_SPRITE_PACK(SPK_GPS_SLAYER);
		break;

	case RACE_VAMPIRE:
		m_GPS_Base_Info.spk = new C_SPRITE_PACK(SPK_GPS_VAMPIRE);
		break;

	case RACE_OUSTERS:
		m_GPS_Base_Info.spk = new C_SPRITE_PACK(SPK_GPS_OUSTERS);
		break;
	}	
	m_pmapspk				= new C_SPRITE_PACK(SPK_GPSMAP);

	m_mouse_move_x			= 200;
	m_mouse_move_y			= 100;
	m_mouse_move_back_x		= 0;
	m_mouse_move_back_y		= 0;
	m_mouse_down_x			= 0;
	m_mouse_down_y			= 0;
	m_mouse_up_x			= 0;
	m_mouse_up_y			= 0;

	SetObjectPos();

	m_iZoneID				= 0;
	m_bGpsShow	= false;
	m_bGpsMove	= false;
	m_bStartGps	= false;

#ifndef _LIB

#endif
	
}

//-----------------------------------------------------------------------------
// ~C_VS_UI_MINIMAP
//
// 
//-----------------------------------------------------------------------------
C_VS_UI_GPS::~C_VS_UI_GPS()
{
	gpC_vs_ui_window_manager->SetAlpha(C_VS_UI_WINDOW_MANAGER::MINIMAP, GetAttributes()->alpha);
	gpC_vs_ui_window_manager->SetAutoHide(C_VS_UI_WINDOW_MANAGER::MINIMAP, GetAttributes()->autohide);
	gpC_vs_ui_window_manager->SetRect(C_VS_UI_WINDOW_MANAGER::MINIMAP, Rect(x, y, w, h));
	
	g_UnregisterWindow(this);
	
	if(m_p_gps_surface != NULL)
	{
		DeleteNew(m_p_gps_surface);
		m_p_gps_surface = NULL;
	}
	
	if(m_GPS_Base_Info.spk != NULL)
	{
		DeleteNew(m_GPS_Base_Info.spk);
		m_GPS_Base_Info.spk = NULL;
	}

	if(m_pmapspk != NULL)
	{
		delete m_pmapspk;
		m_pmapspk = NULL;
	}

	memset((S_GPS_BASE_INFO*)&m_GPS_Base_Info, NULL, sizeof(S_GPS_BASE_INFO));


//	DeleteNew(m_pC_button_group);

	m_bGpsMove	= false;
	m_bGpsShow	= false;
}

//-----------------------------------------------------------------------------
// C_VS_UI_GPS::ShowButtonWidget
//
// 
//-----------------------------------------------------------------------------
void	C_VS_UI_GPS::ShowButtonDescription(C_VS_UI_EVENT_BUTTON * p_button)
{
/*
	// 2006.08.22 sjheon
	if( m_bgpsDisableZone )
		return ; 

	const static char* m_minimap_button_string[4] = 
	{
		(*g_pGameStringTable)[UI_STRING_MESSAGE_SHOW_ALPHA_WINDOW].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_AUTO_HIDE_ON].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_SHOW_NO_ALPHA_WINDOW].GetString(),
		(*g_pGameStringTable)[UI_STRING_MESSAGE_AUTO_HIDE_OFF].GetString(),
	};
	
	if(GetAttributes()->alpha && p_button->GetID() == ALPHA_ID)
		g_descriptor_manager.Set(DID_INFO, p_button->x+x, p_button->y+y, (void *)m_minimap_button_string[2],0,0);
	if(GetAttributes()->autohide && p_button->GetID() == PUSHPIN_ID)
		g_descriptor_manager.Set(DID_INFO, p_button->x+x, p_button->y+y, (void *)m_minimap_button_string[3],0,0);
	else
		g_descriptor_manager.Set(DID_INFO, p_button->x+x, p_button->y+y, (void *)m_minimap_button_string[p_button->GetID()],0,0);
*/
}

//-----------------------------------------------------------------------------
// C_VS_UI_GPS::ShowButtonWidget
//
// 
//-----------------------------------------------------------------------------
void	C_VS_UI_GPS::ShowButtonWidget(C_VS_UI_EVENT_BUTTON * p_button)
{	
	// 2006.08.22 sjheon

}
//-----------------------------------------------------------------------------
// WindowEventReceiver
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_GPS::WindowEventReceiver(id_t event)
{
	// 2006.08.22 sjheon
	switch(event)
	{
	case EVENT_WINDOW_MOVE: 
	break;
	}
}

//-----------------------------------------------------------------------------
// IsPixel
//
// 
//-----------------------------------------------------------------------------
bool C_VS_UI_GPS::IsPixel(int _x, int _y)
{
	bool re;
	if(!m_GpsManager_Base_Info.bHide)
	{
		if(m_C_ListManager.GetListShow())
		{
			if(m_bGpsMove	== true)
			{
				if(_x >= m_GpsManager_Base_Info.iX - MOUSE_MOVE_POS && _x <= (m_GpsManager_Base_Info.iX+m_GpsManager_Base_Info.iWidht + MOUSE_MOVE_POS) &&
					_y >= m_GpsManager_Base_Info.iY - MOUSE_MOVE_POS && _y <= (m_GpsManager_Base_Info.iY+m_GpsManager_Base_Info.iHeight + MOUSE_MOVE_POS)||
					_x >= m_ListManager_Base_Info.iX - MOUSE_MOVE_POS  && _x <= (m_ListManager_Base_Info.iX+m_ListManager_Base_Info.iWidht + MOUSE_MOVE_POS) &&
					_y >= m_ListManager_Base_Info.iY - MOUSE_MOVE_POS  && _y <= (m_ListManager_Base_Info.iY+m_ListManager_Base_Info.iHeight + MOUSE_MOVE_POS))
				{
					re = true;
				}
				else
				{	
					re = false;
				}
			}
			else
			{
				if(_x >= m_GpsManager_Base_Info.iX && _x <= (m_GpsManager_Base_Info.iX+m_GpsManager_Base_Info.iWidht) &&
					_y >= m_GpsManager_Base_Info.iY && _y <= (m_GpsManager_Base_Info.iY+m_GpsManager_Base_Info.iHeight)||
					_x >= m_ListManager_Base_Info.iX && _x <= (m_ListManager_Base_Info.iX+m_ListManager_Base_Info.iWidht) &&
					_y >= m_ListManager_Base_Info.iY && _y <= (m_ListManager_Base_Info.iY+m_ListManager_Base_Info.iHeight))
				{
					re = true;
				}
				else
				{	
					re = false;
				}
			}
		}
		else
		{
			if(m_bGpsMove	== true)
			{
				if(_x >= m_GpsManager_Base_Info.iX  - MOUSE_MOVE_POS && _x <= (m_GpsManager_Base_Info.iX+m_GpsManager_Base_Info.iWidht + MOUSE_MOVE_POS) &&
					_y >= m_GpsManager_Base_Info.iY  - MOUSE_MOVE_POS && _y <= (m_GpsManager_Base_Info.iY+m_GpsManager_Base_Info.iHeight + MOUSE_MOVE_POS))
					re	= true;
				else
					re	= false;
			}
			else
			{
				if(_x >= m_GpsManager_Base_Info.iX && _x <= (m_GpsManager_Base_Info.iX+m_GpsManager_Base_Info.iWidht) &&
					_y >= m_GpsManager_Base_Info.iY && _y <= (m_GpsManager_Base_Info.iY+m_GpsManager_Base_Info.iHeight))
//				_x >= m_IconManager_Base_Info.iX && _x <= (m_IconManager_Base_Info.iX+m_IconManager_Base_Info.iWidht) &&
//				_y >= m_IconManager_Base_Info.iY && _y <= (m_IconManager_Base_Info.iY+m_IconManager_Base_Info.iHeight))
					re = true;
				else
					re = false;
			}

		}
	}
	else
	{
		re = false;
	}
	return re;
}

//-----------------------------------------------------------------------------
// Run
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_GPS::Run(id_t id)
{

}

//-----------------------------------------------------------------------------
// MouseControl
//
// 
//-----------------------------------------------------------------------------
bool C_VS_UI_GPS::MouseControl(UINT message, int _x, int _y)
{
	if(m_bgpsDisableZone) 
		return false ; 

	Window::MouseControl(message, _x, _y);
//	_x-=x; _y-=y;
	
	bool re = false;
	
	switch(message)
	{
	case M_MOVING:
		if(m_bGpsMove == true)	// GPS드래그
		{
			int gps_x = m_mouse_move_x;
			int gps_y = m_mouse_move_y;

			m_mouse_move_x	= gps_x + (_x - m_mouse_move_back_x);
			m_mouse_move_y	= gps_y + (_y - m_mouse_move_back_y);

			SetObjectPos();
		}
		m_mouse_move_back_x	= _x;
		m_mouse_move_back_y	= _y;
	
		if(_x >= m_ListManager_Base_Info.iX && _x <= (m_ListManager_Base_Info.iX+m_ListManager_Base_Info.iWidht) &&
			_y >= m_ListManager_Base_Info.iY && _y <= (m_ListManager_Base_Info.iY+m_ListManager_Base_Info.iHeight))	//리스트 클릭(롤오버상태)
			m_C_ListManager.ItemClick(_x, _y, false);

		m_C_GpsManager.GetIconRollOverExplanationView(_x, _y);	//GPS에서 Icon에 롤 오버 됐을때 설명을 보여준다.
		m_C_GpsManager.m_Gps_Close_Button.ButtonClick(_x, _y, false, GPS_CLOSEBUTTON1, GPS_CLOSEBUTTON2);
		m_C_GpsManager.m_Gps_ListView_Button.ButtonClick(_x, _y, false, GPS_DUNGEONVIEW_BUTTON1, GPS_DUNGEONVIEW_BUTTON2);
		m_C_ListManager.GetScrollUpButtonRollOver(_x, _y, false, false);
		m_C_ListManager.GetScrollDownButtonRollOver(_x, _y, false, false);		
		
		break;
	
	case M_LEFTBUTTON_DOWN:
		if(!m_GpsManager_Base_Info.bHide)
		{
			if(_x >= m_GpsManager_Base_Info.iX && _x <= (m_GpsManager_Base_Info.iX+m_GpsManager_Base_Info.iWidht) &&
				_y >= m_GpsManager_Base_Info.iY && _y <= (m_GpsManager_Base_Info.iY+m_GpsManager_Base_Info.iHeight))
			{
				m_bGpsMove = true;
				m_mouse_down_x	= _x;
				m_mouse_down_y	= _y;
			}
			else
			{
				m_bGpsMove = false;
			}
		}


		if(m_C_GpsManager.m_Gps_ListView_Button.ButtonClick(_x, _y, true, GPS_DUNGEONVIEW_BUTTON1, GPS_DUNGEONVIEW_BUTTON2))
			m_C_ListManager.SetListShow(!m_C_ListManager.GetListShow());
		
		if(m_C_ListManager.ItemClick(_x, _y, true))
		{
			int iMinLv	= 0;
			int iMaxLv	= 0;
			string	strMonsterLv;

			m_iZoneID			= m_C_ListManager.GetZoneID();
			m_C_GpsManager.SetSelectMapIndex(m_iZoneID);
			m_iGpsMapIndex		= m_C_GpsManager.GetSelectMapIndex();

			m_SelectListItem	= m_C_ListManager.GetSelectListItem();
			iMinLv				= m_SelectListItem.wMonsterLv1;
			iMaxLv				= m_SelectListItem.wMonsterLv2;
			strMonsterLv		= m_SelectListItem.pchMonsterLv;

			m_C_GpsManager.SetMonsterLv(iMinLv, iMaxLv);

			if(iMinLv == 0 || iMaxLv == 0)
				m_C_GpsManager.SetMonsterLv(strMonsterLv);
			m_C_GpsManager.SetGPSManager(m_GpsManager_Base_Info, m_pmapspk, m_iGpsMapIndex, m_iZoneID);
		}
		if(m_C_ListManager.GetScrollUpButtonRollOver(_x, _y, true, false))
		{
			SetObjectPos();
		}
		if(m_C_ListManager.GetScrollDownButtonRollOver(_x, _y, true, false))
		{
			SetObjectPos();
		}
	
		if(m_C_GpsManager.m_Gps_Close_Button.ButtonClick(_x, _y, true, GPS_CLOSEBUTTON1, GPS_CLOSEBUTTON2))
		{
			m_bGpsMove = false;
			NonActive();
		}

#if __CONTENTS(__MOVE_ZONE)
		if(gpC_mouse_pointer->IsMoveZoneEffect())
		{
			// 개발자용 "맵 이동하는 기능" - 2008.11.7 ij-ch
			m_C_GpsManager.SetMoveZone(_x, _y);
			MouseControl(M_LEFTBUTTON_UP,_x,_y); // 창 이동 못하게
		} else
#endif // __MOVE_ZONE
#if __CONTENTS(__QUEST_RENEWAL)	
		if(m_C_GpsManager.GetIconRollOverExplanationView(_x, _y, true))	//아이콘이 클릭된 상태면(퀘스트가 클릭된 상태면 퀘스트 리스트를 실행)
		{
			gC_vs_ui.HotKey_Quest();
		}
#endif // __QUEST_RENEWAL

		break;
	case M_WHEEL_UP:
		m_C_ListManager.GetScrollUpButtonRollOver(_x, _y, false, true);
		SetObjectPos();
		break;
	case M_WHEEL_DOWN:
		m_C_ListManager.GetScrollDownButtonRollOver(_x, _y, false, true);
		SetObjectPos();
		break;
	case M_LB_DOUBLECLICK:
		// 반투명 상태에서 맵 클릭하면 이동되게
/*		if (gpC_mouse_pointer->GetPickUpItem() == false && re)
		{
			MoveReady();
			SetOrigin(_x, _y);
			break;
		}
*/		break;
		
	case M_LEFTBUTTON_UP:
		m_mouse_up_x	= _x;
		m_mouse_up_y	= _y;
		m_mouse_move	= false;
		m_bGpsMove		= false;
		break;
	}
	re	= m_bGpsMove;
	return re;
}

//-----------------------------------------------------------------------------
// MouseControlExtra
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_GPS::MouseControlExtra(UINT message, int _x, int _y)
{
	// 2006.08.22 sjheon
	if(m_bgpsDisableZone)
		return ; 

	_x-=x; _y-=y;

	switch(message)
	{
	case M_MOVING:
		// 미니맵 위에 마우스가 있다.

		break;
	}
}

//-----------------------------------------------------------------------------
// C_VS_UI_GPS
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_GPS::KeyboardControl(UINT message, UINT key, long extra)
{
	if (message == WM_KEYDOWN && key == VK_ESCAPE)
	{
		NonActive();
	}
}

//-----------------------------------------------------------------------------
// Show
//
// 
//-----------------------------------------------------------------------------
void C_VS_UI_GPS::Show()
{
	bool bSurfaceLock	= false;
	if(gpC_base->m_p_DDSurface_back->Lock())
	{
//		gpC_base->m_p_DDSurface_back->BltHalf() &map_point, m_p_gps_surface, &rt);
		bSurfaceLock	= true;
		m_C_GpsManager.GPSManagerView(true);
		m_C_ListManager.ListManagerView(true);
		gpC_base->m_p_DDSurface_back->Unlock();
	}
	bSurfaceLock	= false;
	
	g_FL2_GetDC();
	m_C_GpsManager.GPSManagerView(false);
	m_C_ListManager.ListManagerView(false);
	g_FL2_ReleaseDC();
}

//-----------------------------------------------------------------------------
// Timer
//
//-----------------------------------------------------------------------------
bool C_VS_UI_GPS::TimerGPS()
{
	if(m_dw_gps_prev_tickcount+m_dw_gps_millisec <= GetTickCount())
	{
		m_dw_gps_prev_tickcount = GetTickCount();
		return true;
	}
	
	return false;
}


void C_VS_UI_GPS::Start()
{
	if(m_bStartGps)
		return;

	m_GpsManager_Base_Info.bHide	= true;
	m_IconManager_Base_Info.bHide	= true;
	m_ListManager_Base_Info.bHide	= true;
	m_bStartGps						= true;

	m_C_GpsManager.SetGPSManager(m_GpsManager_Base_Info, m_pmapspk, m_iGpsMapIndex, m_iZoneID);
	m_C_ListManager.SetListManager(m_ListManager_Base_Info);
	
	PI_Processor::Start();
	AttrTopmost(true);
	AttrPin(true);

//	m_pC_button_group->Init();

	WindowEventReceiver(EVENT_WINDOW_MOVE);
	
	gpC_window_manager->AppearWindow(this);
}


void	C_VS_UI_GPS::SetZone(int zone_id)
{
	zone_id;
}

void	C_VS_UI_GPS::DesableZone(bool bZone)
{
	m_bgpsDisableZone	= bZone;
}


void	C_VS_UI_GPS::SetObjectPos()
{
	if(m_GPS_Base_Info.spk != NULL)
	{
		m_GPS_Base_Info.iX			= m_mouse_move_x;
		m_GPS_Base_Info.iY			= m_mouse_move_y;

		m_GpsManager_Base_Info				= m_GPS_Base_Info;
		m_GpsManager_Base_Info.iX			= m_mouse_move_x;
		m_GpsManager_Base_Info.iY			= m_mouse_move_y;
		m_GpsManager_Base_Info.iHeight		= m_GpsManager_Base_Info.spk->GetHeight(GPS_MAPBOX);
		m_GpsManager_Base_Info.iWidht		= m_GpsManager_Base_Info.spk->GetWidth(GPS_MAPBOX);
		m_C_GpsManager.SetGPSManager(m_GpsManager_Base_Info, m_pmapspk, m_iGpsMapIndex, m_iZoneID);	// GPSMAP타이틀의 값을 설정

		m_ListManager_Base_Info				= m_GpsManager_Base_Info;
		m_ListManager_Base_Info.iY			+= m_GpsManager_Base_Info.iHeight - 4;					//라인을 하나로 보이기 위해
		m_ListManager_Base_Info.iHeight		= m_ListManager_Base_Info.spk->GetHeight(GPS_LISTBOX);
		m_ListManager_Base_Info.iWidht		= m_ListManager_Base_Info.spk->GetWidth(GPS_LISTBOX);
		m_C_ListManager.SetListManager(m_ListManager_Base_Info);
	}
}


void	C_VS_UI_GPS::NonActive()
{
	AttrTopmost(false);
	AttrPin(false);
	m_bGpsShow						= false;
	m_GpsManager_Base_Info.bHide	= true;
	m_IconManager_Base_Info.bHide	= true;
	m_ListManager_Base_Info.bHide	= true;
	m_C_GpsManager.SetGPSManager(m_GpsManager_Base_Info, m_pmapspk, m_iGpsMapIndex, m_iZoneID);
	m_C_ListManager.SetListManager(m_ListManager_Base_Info);
//	Finish();
}

void	C_VS_UI_GPS::Active(int iMapIndex, int iMapID)
{
	AttrTopmost(true);
	AttrPin(true);
	m_bGpsShow							= true;
	m_GpsManager_Base_Info.bHide		= false;
	m_IconManager_Base_Info.bHide		= false;
	m_ListManager_Base_Info.bHide		= false;
	m_iGpsMapIndex						= iMapIndex;
	m_iZoneID							= iMapID;
	m_C_GpsManager.SetGPSManager(m_GpsManager_Base_Info, m_pmapspk, iMapIndex, m_iZoneID);
	m_C_ListManager.SetListManager(m_ListManager_Base_Info);	
}

bool	C_VS_UI_GPS::GetGpsShow()
{
	return m_bGpsShow;
}

void 	C_VS_UI_GPS::GpsInfoReView()
{
	m_C_GpsManager.SetGPSManager(m_GpsManager_Base_Info, m_pmapspk, m_iGpsMapIndex, m_iZoneID);
	m_C_ListManager.SetListManager(m_ListManager_Base_Info);
}
#endif	// __GPS_ADD
