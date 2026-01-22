//---------------------------------------------------------------------------
// GameInitInfo.cpp
//---------------------------------------------------------------------------
// Information Table에 대한 초기화를 한다.
//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Include files
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include <fstream>
#include <mmsystem.h>

// def
#include "MTypeDef.h"
#include "MFileDef.h"
#include "AddonDef.h"
#include "SoundDef.h"
#include "EffectSpriteTypeDef.h"

// table
#include "ClientConfig.h"
#include "UserOption.h"
#include "MSoundTable.h"
#include "MMusicTable.h"
#include "MZoneTable.h"
#include "MItemTable.h"
#include "MItemOptionTable.h"
#include "MInteractionObjectTable.h"
#include "CFileIndexTable.h"
#include "MCreatureTable.h"
#include "MCreatureSpriteTable.h"
#include "CFramePack.h"
#include "MShopTemplateTable.h"
#include "MNPCTable.h"
#include "MEffectSpriteTypeTable.h"
#include "MEffectStatusTable.h"
#include "MActionInfoTable.h"
#include "MGameStringTable.h"
#include "MServerItemTable.h"
#include "MSkillManager.h"
#include "MEffectGeneratorDef.h"
#include "MusicDef.h"
#include "MChatManager.h"
#include "MLevelNameTable.h"
#include "AppendPatchInfo.h"
#include "AddonDef.h"
#include "RankBonusTable.h"
#include "ServerRankBonusTable.h"

#include "MMinMaxInfo.h"

#include "MItem.h"

#include "Packet\types\PacketItemDef.h"
#include "MathTable.h"

class EventGiftInfo
{
public :
	EventGiftInfo() { m_bActive = 1; m_Step = 1; m_Name = "";}
	~EventGiftInfo(){}

	void LoadFromFile(ivfstream &file)
	{
		file.read((char*)&m_ID, sizeof(DWORD));
		file.read((char*)&m_bActive, sizeof(char) );
		file.read((char*)&m_Step, sizeof( int ) );
		m_Name.LoadFromFile( file );
	}
	void SaveToFile(std::ofstream &file)
	{
		file.write((const char*)&m_ID, sizeof(DWORD ));
		file.write((const char*)&m_bActive, sizeof(char) );
		file.write((const char*)&m_Step, sizeof( int ) );
		m_Name.SaveToFile( file );
	}


public :
	DWORD	m_ID;
	char	m_bActive;
	int		m_Step;
	MString	m_Name;
};

typedef CTypeTable<EventGiftInfo> CEventGiftInfo;

void MakeEventInfo()
{
	return;
	CEventGiftInfo *Event = new CEventGiftInfo;	

	int index=0;
	DWORD id = 0;
	Event->Init(21);

	
	(*Event)[index].m_ID = id++;
	(*Event)[index].m_Step = 1;
	(*Event)[index].m_bActive = 1;
	(*Event)[index++].m_Name = "아사달쇼핑 상품권 1만원권";
	
	(*Event)[index].m_ID = id++;
	(*Event)[index].m_Step = 1;
	(*Event)[index].m_bActive = 1;
	(*Event)[index++].m_Name = "다크에덴 펜던트";
	
	(*Event)[index].m_ID = id++;
	(*Event)[index].m_Step = 1;
	(*Event)[index].m_bActive = 1;
	(*Event)[index++].m_Name = "다크에덴 티셔츠";
	
	(*Event)[index].m_ID = id++;
	(*Event)[index].m_Step = 1;
	(*Event)[index].m_bActive = 1;
	(*Event)[index++].m_Name = "다크에덴 이용권";
	
	(*Event)[index].m_ID = id++;
	(*Event)[index].m_Step = 2;
	(*Event)[index].m_bActive = 1;
	(*Event)[index++].m_Name = "인라인 스케이트";
	
	(*Event)[index].m_ID = id++;
	(*Event)[index].m_Step = 2;
	(*Event)[index].m_bActive = 1;
	(*Event)[index++].m_Name = "보이스펜";
	
	(*Event)[index].m_ID = id++;
	(*Event)[index].m_Step = 2;
	(*Event)[index].m_bActive = 1;
	(*Event)[index++].m_Name = "MP3 플래이어";
	
	(*Event)[index].m_ID = id++;
	(*Event)[index].m_Step = 2;
	(*Event)[index].m_bActive = 1;
	(*Event)[index++].m_Name = "5.1채널 스피커";
	
	(*Event)[index].m_ID = id++;
	(*Event)[index].m_Step = 2;
	(*Event)[index].m_bActive = 1;
	(*Event)[index++].m_Name = "아사달쇼핑 상품권 10만원권";
	
	(*Event)[index].m_ID = id++;
	(*Event)[index].m_Step = 3;
	(*Event)[index].m_bActive = 1;
	(*Event)[index++].m_Name = "명품시계";
	
	(*Event)[index].m_ID = id++;
	(*Event)[index].m_Step = 3;
	(*Event)[index].m_bActive = 1;
	(*Event)[index++].m_Name = "DVD/오디오 콤보";
	
	(*Event)[index].m_ID = id++;
	(*Event)[index].m_Step = 3;
	(*Event)[index].m_bActive = 1;
	(*Event)[index++].m_Name = "캠코더";
	
	(*Event)[index].m_ID = id++;
	(*Event)[index].m_Step = 3;
	(*Event)[index].m_bActive = 1;
	(*Event)[index++].m_Name = "디지털 카메라";
	
	(*Event)[index].m_ID = id++;
	(*Event)[index].m_Step = 3;
	(*Event)[index].m_bActive = 1;
	(*Event)[index++].m_Name = "아사달쇼핑 상품권 50만원권";
	
	(*Event)[index].m_ID = id++;
	(*Event)[index].m_Step = 4;
	(*Event)[index].m_bActive = 1;
	(*Event)[index++].m_Name = "홈시어터일체형";
	
	(*Event)[index].m_ID = id++;
	(*Event)[index].m_Step = 4;
	(*Event)[index].m_bActive = 1;
	(*Event)[index++].m_Name = "냉장고";
	
	(*Event)[index].m_ID = id++;
	(*Event)[index].m_Step = 4;
	(*Event)[index].m_bActive = 1;
	(*Event)[index++].m_Name = "완전평면 TV";
	
	(*Event)[index].m_ID = id++;
	(*Event)[index].m_Step = 4;
	(*Event)[index].m_bActive = 1;
	(*Event)[index++].m_Name = "TFT-LCD 모니터 18인치";
	
	(*Event)[index].m_ID = id++;
	(*Event)[index].m_Step = 4;
	(*Event)[index].m_bActive = 1;
	(*Event)[index++].m_Name = "컴퓨터";
	
	(*Event)[index].m_ID = id++;
	(*Event)[index].m_Step = 5;
	(*Event)[index].m_bActive = 1;
	(*Event)[index++].m_Name = "디지털 TV";
	
	(*Event)[index].m_ID = id++;
	(*Event)[index].m_Step = 5;
	(*Event)[index].m_bActive = 1;
	(*Event)[index++].m_Name = "다크에덴 이용권";

	std::ofstream EventGift("C:\\EventQuest.inf", std::ios::binary);
	Event->SaveToFile( EventGift );
	EventGift.close();

	delete Event;
}
