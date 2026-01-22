//----------------------------------------------------------------------
// MSkillManager.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MSkillManager.h"
#include "MTypeDef.h"

#ifdef __GAME_CLIENT__
	#include "MPlayer.h"
	#include "MSlayerGear.h"
	#include "MInventory.h"
	#include "ServerInfo.h"
	#include "MHelpManager.h"
//	#include "MFileDef.h"
	#include "Properties.h"
	#include "MItemFinder.h"
	#include "UserInformation.h"
	#include "VS_UI.h"		// [새기술3]
	#include "MZone.h"		// 레어존에서 invisibility 못쓰게 할려고
#include "DebugInfo.h"

	extern MItem* UI_GetMouseItem();
	extern bool IsBombMaterial(const MItem* pItem);

	extern DWORD	g_CurrentTime;
#endif

#ifdef __GAME_CLIENT__
	bool	FileOpenBinary(const char* filename, ivfstream& file);

	// MItem.cpp에 있다.
	bool	IsBombMaterial(const MItem* pItem);

	bool	g_abHolyLandBonusSkills[HOLYLAND_BONUS_MAX] = { false, };
	bool	g_abSweeperBonusSkills[SWEEPER_BONUS_MAX] = { false, };

#endif

//----------------------------------------------------------------------
//
// Global
//
//----------------------------------------------------------------------
// SkillInfoTable
MSkillInfoTable	*					g_pSkillInfoTable = NULL;

// SkillManager
MSkillManager*						g_pSkillManager = NULL;

// SkillAvailable
MSkillSet*							g_pSkillAvailable = NULL;

// 
//----------------------------------------------------------------------
//
//							SKILLINFO_NODE
//
//----------------------------------------------------------------------
SKILLINFO_NODE::SKILLINFO_NODE()
{
	m_Level = 1;

	m_SpriteID = 0;

	m_MP = 0;	
	m_bPassive = false;
	m_bActive = false;
		
	m_ExpLevel = 0;			// 스킬 레벨
	m_SkillExp = 0;			// 스킬 경험치

	m_LearnLevel = 100;
	m_eSkillRace = RACE_SLAYER;

	m_DelayTime = 0;		// 기술 사용후 다시 사용가능한 delay
	m_AvailableTime = 0;	// 다시 사용 가능한 시간
		
	m_bEnable = false;	

	DomainType = 0;		// 그 기술이 어느 도메인에 속하는가.
	minDamage = 0;		// 최소 데미지 또는 효과치.
	maxDamage = 0;		// 최대 데미지 또는 효과치.
	minDelay = 0;		// 최소 사용 딜레이.
	maxDelay = 0;		// 최대 사용 딜레이.
	minCastTime = 0;	// 최소 캐스팅 타임.
	maxCastTime = 0;	// 최대 캐스팅 타임.		
	minDuration = 0;	// 최소 지속 시간
	maxDuration = 0;	// 최대 지속 시간
	minRange = 1;		// 최소 사정거리
	maxRange = 1;		// 최대 사정거리
	maxExp = 0;			// 그 기술의 100% 경험치. 1 회당 + 1 씩 올라감
	SkillPoint = 0;
	LevelUpPoint = 0;
	Fire= 0;
	Water= 0;
	Earth= 0;
	Wind= 0;
	Sum= 0;
	Wristlet= 0;
	Stone1= 0;
	Stone2= 0;
	Stone3= 0;
	Stone4= 0;
	ElementalDomain= 0;
	CanDelete = 0;

	m_bHideInSkillTree = false;
}

//----------------------------------------------------------------------
// Load From File ServerSkillInfo
//----------------------------------------------------------------------
void		
SKILLINFO_NODE::LoadFromFileServerSkillInfo(ivfstream& file)
{
	int ll;
	MString name;
	MString hname;
	int mp;
	
	file.read((char*)&ll, 4);
	file.read((char*)&DomainType, 4);
	name.LoadFromFile( file );
	hname.LoadFromFile( file );
	file.read((char*)&minDamage, 4);		// 최소 데미지 또는 효과치.
	file.read((char*)&maxDamage, 4);		// 최대 데미지 또는 효과치.
	file.read((char*)&minDelay, 4);			// 최소 사용 딜레이.
	file.read((char*)&maxDelay, 4);			// 최대 사용 딜레이.
	file.read((char*)&minDuration, 4);		// 최소 캐스팅 타임.
	file.read((char*)&maxDuration, 4);		// 최대 캐스팅 타임.
	file.read((char*)&mp, 4);					// 마나 소모량.(m_MP)
	file.read((char*)&minRange, 4);			// 최소 사정거리
	file.read((char*)&maxRange, 4);			// 최대 사정거리
	file.read((char*)&maxExp, 4);			// 그 기술의 100% 경험치. 1 회당 + 1 씩 올라감	
	
	if(DomainType == SKILLDOMAIN_OUSTERS)
	{
		file.read((char*)&SkillPoint,		sizeof(int));
		file.read((char*)&LevelUpPoint,		sizeof(int));
		int szSkill;
		file.read((char*)&szSkill,			sizeof(int));
		SkillTypeList.clear();
		for(int i = 0; i < szSkill; i++)
		{
			int skillType;
			file.read((char*)&skillType,		sizeof(int));
			SkillTypeList.push_back(skillType);
		}
		file.read((char*)&Fire,				sizeof(int));
		file.read((char*)&Water,			sizeof(int));
		file.read((char*)&Earth,			sizeof(int));
		file.read((char*)&Wind,				sizeof(int));
		file.read((char*)&Sum,				sizeof(int));
		file.read((char*)&Wristlet,			sizeof(int));
		file.read((char*)&Stone1,			sizeof(int));
		file.read((char*)&Stone2,			sizeof(int));
		file.read((char*)&Stone3,			sizeof(int));
		file.read((char*)&Stone4,			sizeof(int));
		file.read((char*)&ElementalDomain,	sizeof(int));
		file.read((char*)&CanDelete,		sizeof(BYTE));
	} else
	{
		ElementalDomain = -1;
	}
	if (name != "Empty Skill")
	{
		m_LearnLevel = ll;
		m_Name = name;
		m_HName = hname;
		m_MP = mp;
	}
}

//----------------------------------------------------------------------
// Add NextSkill
//----------------------------------------------------------------------
// 다음에 배울 수 있는 Skill들을 설정한다.
//----------------------------------------------------------------------
bool			
SKILLINFO_NODE::AddNextSkill(ACTIONINFO id)
{
	SKILLID_LIST::iterator iSkill = m_listNextSkill.begin();

	// sort해서 add한다.
	while (iSkill != m_listNextSkill.end())
	{
		// 이미 있으면 추가 불가
		if (*iSkill==id)
		{
			return false;
		}
		// 큰거 앞에..
		else if (*iSkill > id)
		{
			// 앞에 추가한다.
			m_listNextSkill.insert( iSkill, id );

			return true;
		}

		iSkill++;
	}

	m_listNextSkill.push_back( id );

	return true;
}

//----------------------------------------------------------------------
// Save To File
//----------------------------------------------------------------------
void		
SKILLINFO_NODE::SaveToFile(std::ofstream& file)
{

	m_Name.SaveToFile( file );							// 기술 이름
	m_HName.SaveToFile( file );
	file.write((const char*)&m_Level, 4);
	file.write((const char*)&m_X, 4);
	file.write((const char*)&m_Y, 4);					// 화면에서의 출력 시작 위치
	file.write((const char*)&m_SpriteID, SIZE_SPRITEID);	// 기술의 Icon Sprite
	file.write((const char*)&m_MP, 4);	// MP소비량
	file.write((const char*)&m_bPassive, 1);		// passive skill인가?
	file.write((const char*)&m_YMP, 4);	// MP소비량
	file.write((const char*)&m_ZMP, 4);	// MP소비량
	file.write((const char*)&m_bActive, 1);			// 항상 사용 가능한 skill인가?

	BYTE skillStep = m_SkillStep;
	file.write((const char*)&skillStep, 1);

	// id list 저장
	int idNum;
	SKILLID_LIST::const_iterator iSkillID;

	idNum = m_listNextSkill.size();
	file.write((const char*)&idNum, 4);
	iSkillID = m_listNextSkill.begin();

	while (iSkillID!=m_listNextSkill.end())
	{
		TYPE_ACTIONINFO id = *iSkillID;
		file.write((const char*)&id, SIZE_ACTIONINFO);
		iSkillID++;
	}

	// Delay Group 저장
	idNum = m_listDelayGroup.size();
	file.write((const char*)&idNum, 4);
	iSkillID = m_listDelayGroup.begin();

	while (iSkillID != m_listDelayGroup.end())
	{
		TYPE_ACTIONINFO id = *iSkillID;
		file.write((const char*)&id, SIZE_ACTIONINFO);
		iSkillID++;
	}

	m_Description.SaveToFile(file);

	file.write((const char*)&m_bHideInSkillTree, 1);	// 스킬 트리에서 숨겨야하는 스킬
}

//----------------------------------------------------------------------
// Load From File
//----------------------------------------------------------------------
int g_nskillnodeindex = 0;

void		
SKILLINFO_NODE::LoadFromFile(ivfstream& file)
{
	m_index = g_nskillnodeindex;
	g_nskillnodeindex++;
	m_Name.LoadFromFile( file );					// 기술 이름
	m_HName.LoadFromFile( file );
	file.read((char*)&m_Level, 4);
	file.read((char*)&m_X, 4);
	file.read((char*)&m_Y, 4);						// 화면에서의 출력 시작 위치
	file.read((char*)&m_SpriteID, SIZE_SPRITEID);	// 기술의 Icon Sprite
	file.read((char*)&m_MP, 4);		// MP소비량
	file.read((char*)&m_bPassive, 1);				// passive 스킬?
	file.read((char*)&m_YMP, 4);		// MP소비량
	file.read((char*)&m_ZMP, 4);		// MP소비량
	file.read((char*)&m_bActive, 1);				// 항상 사용 가능한 skill인가?

	BYTE skillStep;
	file.read((char*)&skillStep, 1);
	m_SkillStep = (SKILL_STEP)skillStep;
	// id list load
	int idNum;
	file.read((char*)&idNum, 4);

	m_listNextSkill.clear();
	int i;
	for (i = 0; i < idNum; i++)
	{
		TYPE_ACTIONINFO id;
		file.read((char*)&id, SIZE_ACTIONINFO);
		m_listNextSkill.push_back( (ACTIONINFO)id );
	}	

	// 배운 level
	m_ExpLevel = 0;

	// Delay Group
	file.read((char*)&idNum, 4);
	m_listDelayGroup.clear();
	for (i = 0; i < idNum; i++)
	{
		TYPE_ACTIONINFO id;
		file.read((char*)&id, SIZE_ACTIONINFO);
		m_listDelayGroup.push_back( (ACTIONINFO)id );
	}
	
	m_Description.LoadFromFile(file);

	file.read((char*)&m_bHideInSkillTree, 1);		// 스킬 트리에서 숨겨야하는 스킬
}	

//----------------------------------------------------------------------
// Set DelayTime ( delay )
//----------------------------------------------------------------------
// 기술 사용후 다시 사용할 수 있는 delay시간 설정
//----------------------------------------------------------------------
void
SKILLINFO_NODE::SetDelayTime(DWORD delay)		
{
	// 3초 이하 기술은 delay가 없는 걸로 표시한다.
	if (delay < 1800)
	{
		delay = 0;
	}			
				
	m_DelayTime = delay;	
}

//----------------------------------------------------------------------
// Is AvailableTime ?
//----------------------------------------------------------------------
// 지금 사용 가능한가?
//----------------------------------------------------------------------
bool
SKILLINFO_NODE::IsAvailableTime() const		
{
	#if defined(__GAME_CLIENT__)
		return g_CurrentTime >= m_AvailableTime;
	#else
		return true;
	#endif
}

//----------------------------------------------------------------------
// Get AvailableTimeLeft
//----------------------------------------------------------------------
// 남은 사용 가능 시간
//----------------------------------------------------------------------
DWORD				
SKILLINFO_NODE::GetAvailableTimeLeft() const
{
	#if defined(__GAME_CLIENT__)
		int timeGap = (int)m_AvailableTime - (int)g_CurrentTime;

		if (timeGap > 0)
		{
			return timeGap;
		}
	#endif

	return 0;
}

//----------------------------------------------------------------------
// Set AvailableTime
//----------------------------------------------------------------------
// 지금 바로 사용 가능하게 설정한다.
//----------------------------------------------------------------------
void
SKILLINFO_NODE::SetAvailableTime(int delay)
{
	// 깔끔하게 0으로.. - -;
	#ifdef __GAME_CLIENT__
	if(delay == 0)
	{
		m_CurrentDelayTime = 0;
		m_AvailableTime = 0;	//g_CurrentTime;
	}
	else
	{
		m_CurrentDelayTime = delay;
		m_AvailableTime = g_CurrentTime+delay;	//g_CurrentTime;
	}
	#endif
}

//----------------------------------------------------------------------
// Set Next AvailableTime
//----------------------------------------------------------------------
// 다음 사용 가능한 시간을 결정한다.
//----------------------------------------------------------------------
void
SKILLINFO_NODE::SetNextAvailableTime()
{
	#ifdef __GAME_CLIENT__
		// 현재시간에서 delayTime후에는 사용 가능하다.
		m_CurrentDelayTime = m_DelayTime;
		m_AvailableTime = g_CurrentTime + m_DelayTime;
//		m_AvailableTime = g_CurrentTime + m_DelayTime<1800? 0 : m_DelayTime;
	#endif
}

//----------------------------------------------------------------------
// Set Enable
//----------------------------------------------------------------------
void				
SKILLINFO_NODE::SetEnable(bool enable)
{
	m_bEnable = enable;
}

//----------------------------------------------------------------------
// Set Disable
//----------------------------------------------------------------------
/*
void				
SKILLINFO_NODE::SetDisable()
{
	m_bEnable = false;
}
*/

//----------------------------------------------------------------------
//
//							MSkillSet
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Add Skill
//----------------------------------------------------------------------
bool			
MSkillSet::AddSkill(ACTIONINFO id, BYTE flag)
{
	SKILLID_MAP::iterator	iSkill;

	iSkill = find( id );
	
	//-----------------------------------------------
	// 아직 없는 Skill이면 추가	
	//-----------------------------------------------
	if (iSkill == end())
	{
		insert(SKILLID_MAP::value_type( id, SKILLID_NODE(id, flag) ));

		return true;
	}
	
	//-----------------------------------------------
	// 이미 있다면 flag만 바꾼다.
	//-----------------------------------------------
	SKILLID_NODE& node = (*iSkill).second;
	
	node.Flag = flag;

	return false;
}

//----------------------------------------------------------------------
// Remove Skill
//----------------------------------------------------------------------
// SkillID 제거
//----------------------------------------------------------------------
bool			
MSkillSet::RemoveSkill(ACTIONINFO id)
{
	SKILLID_MAP::iterator	iSkill;

	//--------------------------------------------------
	// ID가 id인 Skill를 찾는다.
	//--------------------------------------------------
	iSkill = find(id);
    
	//--------------------------------------------------
	// 그런 id를 가진 Skill이 없는 경우
	//--------------------------------------------------
	if (iSkill == end())
	{
		return false;
	}

	//--------------------------------------------------
	// 찾은 경우 --> 제거	
	//--------------------------------------------------
	// map에서 제거
	erase( iSkill );

	return true;
}

//----------------------------------------------------------------------
// Is Enable Skill?
//----------------------------------------------------------------------
// id의 skill이 사용 가능한가?
//----------------------------------------------------------------------
bool			
MSkillSet::IsEnableSkill(ACTIONINFO id) const
{
#ifdef __GAME_CLIENT__
	// 플레이어가 SILENCE 스킬이 걸려있는 경우 스킬을 사용할 수 없다.
	if(g_pPlayer->HasEffectStatus(EFFECTSTATUS_SILENCE) ) return false;

	// 피의 저주가 걸려있지 않으면 피의 향연을 쓸수 없다.
	if(id == SKILL_BLOODS_SYMPOSION_ATTACK &&
	   (!g_pPlayer->HasEffectStatus(EFFECTSTATUS_BLOOD_CURSE) ||
		!g_pPlayer->IsVampire())) return false;
#endif 

	SKILLID_MAP::const_iterator		iSkill;

	//--------------------------------------------------
	// ID가 id인 Skill를 찾는다.x
	//--------------------------------------------------
	iSkill = find(id);
    
	//--------------------------------------------------
	// 그런 id를 가진 Skill이 없는 경우
	//--------------------------------------------------
	if (iSkill == end())
	{
		return false;
	}

	//--------------------------------------------------
	// 찾은 경우 --> Is enable?
	//--------------------------------------------------
			
	return ((*iSkill).second).IsEnable()!=0;	
}

//----------------------------------------------------------------------
// Enable Skill
//----------------------------------------------------------------------
bool			
MSkillSet::EnableSkill(ACTIONINFO id)
{
	SKILLID_MAP::iterator	iSkill;

	//--------------------------------------------------
	// ID가 id인 Skill를 찾는다.
	//--------------------------------------------------
	iSkill = find(id);
    
	//--------------------------------------------------
	// 그런 id를 가진 Skill이 없는 경우
	//--------------------------------------------------
	if (iSkill == end())
	{
		return false;
	}

	//--------------------------------------------------
	// 찾은 경우 --> enable
	//--------------------------------------------------
	// map에서 제거
	((*iSkill).second).SetEnable();

	return true;
}

//----------------------------------------------------------------------
// Disable Skill 
//----------------------------------------------------------------------
bool			
MSkillSet::DisableSkill(ACTIONINFO id)	
{
	SKILLID_MAP::iterator	iSkill;

	//--------------------------------------------------
	// ID가 id인 Skill를 찾는다.
	//--------------------------------------------------
	iSkill = find(id);
    
	//--------------------------------------------------
	// 그런 id를 가진 Skill이 없는 경우
	//--------------------------------------------------
	if (iSkill == end())
	{
		return false;
	}

	//--------------------------------------------------
	// 찾은 경우 --> enable
	//--------------------------------------------------
	// map에서 제거
	((*iSkill).second).SetDisable();

	return true;
}

//----------------------------------------------------------------------
// Set Avaliable Skills
//----------------------------------------------------------------------
// 현재 사용 가능한 모든 skill들을 찾아서 추가한다.
//
// - 현재 들고 있는 무기를 보고
//   SkillTree에서 적절한 domain을 모두 enable / 나머지는 disable
// - inventory에서 skill에 관련된 기술을 찾는다.
// - 기타.. skill ?
//----------------------------------------------------------------------
void
MSkillSet::SetAvailableSkills()
{
#ifdef __GAME_CLIENT__

	if (g_pPlayer==NULL 		
		|| g_pSkillManager==NULL
		|| g_pSkillManager->GetSize()==0		
		|| g_pSkillInfoTable==NULL
		|| g_pSkillInfoTable->GetSize()==0)
	{
		return;
	}

	//--------------------------------------------------
	// player의 현재 MP
	//--------------------------------------------------
	int playerMP;		
	BYTE flag;
	
	if (g_pPlayer->GetRace() != RACE_VAMPIRE)
	{
		playerMP = g_pPlayer->GetMP();	

		// EFFECTSTATUS_SACRIFICE 사용중이면 HP 1이 MP 2가 된다.
		if (g_pPlayer->HasEffectStatus(EFFECTSTATUS_SACRIFICE))
		{
			playerMP += (g_pPlayer->GetHP() << 1);
		}		
	}
	else
	{
		// vampire인 경우는 HP를 MP대신에 쓴다.
		playerMP = g_pPlayer->GetHP();	
	}

	// 모든 skill들을 지운다.
	clear();
	
	if( g_pZone != NULL && g_pZone->GetID() == 3001 )
		return;


	//-----------------------------------------------------
	//
	//					slayer인 경우
	//
	//-----------------------------------------------------
	switch(g_pPlayer->GetRace())
	{
		case RACE_SLAYER:
		{
			if (g_pSlayerGear==NULL
				|| g_pInventory==NULL)
			{
				return;
			}
			// 2004, 9, 16, sobeit add start - 인스톨 터렛일때 스킬 정보 갱신
			if(g_pPlayer->HasEffectStatus(EFFECTSTATUS_INSTALL_TURRET))
			{
				//insert(SKILLID_MAP::value_type( SKILL_CLINT_ADV2_HALCYON_MK1, SKILLID_NODE(SKILL_CLINT_ADV2_HALCYON_MK1, FLAG_SKILL_ENABLE) ));
				insert(SKILLID_MAP::value_type( MAGIC_UN_TRANSFORM, SKILLID_NODE(MAGIC_UN_TRANSFORM, FLAG_SKILL_ENABLE) ));
				if ((*g_pSkillInfoTable)[SKILL_TURRET_FIRE].GetMP() > playerMP)
					insert(SKILLID_MAP::value_type( SKILL_TURRET_FIRE, SKILLID_NODE(SKILL_TURRET_FIRE, 0) ));
				else
					insert(SKILLID_MAP::value_type( SKILL_TURRET_FIRE, SKILLID_NODE(SKILL_TURRET_FIRE, FLAG_SKILL_ENABLE) ));
				insert(SKILLID_MAP::value_type( SKILL_VIVID_MAGAZINE, SKILLID_NODE(SKILL_VIVID_MAGAZINE, FLAG_SKILL_ENABLE) ));
				return;
			}


            //Add By Hays 2013  3  10
			if(g_pPlayer->HasEffectStatus(EFFECTSTATUS_INSTALL_MK1))
			{
					bool bCheckNAPALNBULLET			= ((*g_pSkillManager)[SKILLDOMAIN_GUN].GetSkillStatus(SKILL_ADV2_HALCYON_MK1_NAPALN_BULLET)==MSkillDomain::SKILLSTATUS_LEARNED);
					bool bCheckNAPALNBULLET2			= ((*g_pSkillManager)[SKILLDOMAIN_GUN].GetSkillStatus(SKILL_CLIENT_ADV2_HALCYON_MK1)==MSkillDomain::SKILLSTATUS_LEARNED);

					insert(SKILLID_MAP::value_type( MAGIC_UN_TRANSFORM, SKILLID_NODE(MAGIC_UN_TRANSFORM, FLAG_SKILL_ENABLE) ));

					if ((*g_pSkillInfoTable)[SKILL_CLINT_ADV2_HALCYON_MK1].GetMP() > playerMP)
					insert(SKILLID_MAP::value_type( SKILL_CLINT_ADV2_HALCYON_MK1, SKILLID_NODE(SKILL_CLINT_ADV2_HALCYON_MK1, 0) ));

					if ((bCheckNAPALNBULLET == true) && (*g_pSkillInfoTable)[SKILL_ADV2_HALCYON_MK1_NAPALN_BULLET].GetMP() > playerMP)
					{
						insert(SKILLID_MAP::value_type( SKILL_ADV2_HALCYON_MK1_NAPALN_BULLET, SKILLID_NODE(SKILL_ADV2_HALCYON_MK1_NAPALN_BULLET, 0) ));
						if ((bCheckNAPALNBULLET2 == true) && (*g_pSkillInfoTable)[SKILL_CLIENT_ADV2_HALCYON_MK1].GetMP() > playerMP)
						{
							insert(SKILLID_MAP::value_type( SKILL_CLIENT_ADV2_HALCYON_MK1, SKILLID_NODE(SKILL_CLIENT_ADV2_HALCYON_MK1, 0) ));
						}
					}

					
				else
					insert(SKILLID_MAP::value_type( SKILL_CLINT_ADV2_HALCYON_MK1, SKILLID_NODE(SKILL_CLINT_ADV2_HALCYON_MK1, FLAG_SKILL_ENABLE) ));

					if ( bCheckNAPALNBULLET == true )
					{
					insert(SKILLID_MAP::value_type( SKILL_ADV2_HALCYON_MK1_NAPALN_BULLET, SKILLID_NODE(SKILL_ADV2_HALCYON_MK1_NAPALN_BULLET, FLAG_SKILL_ENABLE) ));
					}
					if ( bCheckNAPALNBULLET2 == true )
					{
						insert(SKILLID_MAP::value_type( SKILL_CLIENT_ADV2_HALCYON_MK1, SKILLID_NODE(SKILL_CLIENT_ADV2_HALCYON_MK1, FLAG_SKILL_ENABLE) ));
					}
				return;
			}
			// 2004, 9, 16, sobeit add end - 인스톨 터렛일때 스킬 정보 갱신
			//-----------------------------------------------------
			//
			// Domain에 따른 enable 체크..
			//
			//-----------------------------------------------------
			BYTE fDomain[MAX_SKILLDOMAIN];
			
			// 현재 들고 있는 item
			const MItem* pItem = (*g_pSlayerGear).GetItem( (MSlayerGear::GEAR_SLAYER)MSlayerGear::GEAR_SLAYER_RIGHTHAND );

			//-----------------------------------------------------
			// gun/sword/blade 만 체크하면 된다.
			//-----------------------------------------------------
			fDomain[SKILLDOMAIN_GUN]	= 0;
			fDomain[SKILLDOMAIN_BLADE]	= 0;
			fDomain[SKILLDOMAIN_SWORD]	= 0;

			if (pItem!=NULL && pItem->IsAffectStatus())
			{	
				//-----------------------------------------------------
				// 총이면.. 총만 enable
				//-----------------------------------------------------
				if (pItem->IsGunItem())
				{
					fDomain[SKILLDOMAIN_GUN]	= FLAG_SKILL_ENABLE;
				}
				//-----------------------------------------------------
				// sword이면 sword만 enable
				//-----------------------------------------------------
				else if (pItem->GetItemClass()==ITEM_CLASS_SWORD)
				{
					fDomain[SKILLDOMAIN_SWORD]	= FLAG_SKILL_ENABLE;
				}
				//-----------------------------------------------------
				// blade이면 blade만 enable
				//-----------------------------------------------------
				else if (pItem->GetItemClass()==ITEM_CLASS_BLADE)
				{
					fDomain[SKILLDOMAIN_BLADE]	= FLAG_SKILL_ENABLE;
				}
			}
			
			//-----------------------------------------------------
			//
			// SkillTree 검색
			//
			//-----------------------------------------------------
			//-----------------------------------------------------
			// Blade
			//-----------------------------------------------------
			MSkillDomain& bladeDomain = (*g_pSkillManager)[SKILLDOMAIN_BLADE];

			bladeDomain.SetBegin();		
			while (bladeDomain.IsNotEnd())
			{
				MSkillDomain::SKILLSTATUS	status	= bladeDomain.GetSkillStatus();

				// 배웠으면..
				if (status == MSkillDomain::SKILLSTATUS_LEARNED)
				{
					ACTIONINFO id = bladeDomain.GetSkillID();
		
					if ((*g_pSkillInfoTable)[id].GetMP() > playerMP)
					{
						flag = 0;
					}
					else
					{
						flag = fDomain[SKILLDOMAIN_BLADE];

						if ((*g_pSkillInfoTable)[id].IsActive())
						{
							flag |= FLAG_SKILL_ENABLE;
						}					
					}

					insert(SKILLID_MAP::value_type( id, SKILLID_NODE(id, flag) ));
				}

				// 다음
				bladeDomain.Next();
			}

			//-----------------------------------------------------
			// Sword
			//-----------------------------------------------------
			MSkillDomain& swordDomain = (*g_pSkillManager)[SKILLDOMAIN_SWORD];

			swordDomain.SetBegin();		
			while (swordDomain.IsNotEnd())
			{
				MSkillDomain::SKILLSTATUS	status	= swordDomain.GetSkillStatus();

				// 배웠으면..
				if (status == MSkillDomain::SKILLSTATUS_LEARNED)
				{
					ACTIONINFO	id = swordDomain.GetSkillID();
					int			iSilver	= 0;

					if(pItem)
						iSilver	= pItem->GetSilver();

					if ((*g_pSkillInfoTable)[id].GetMP() > playerMP)
					{
						flag = 0;
					}
				//	else if(iSilver == 0 && id == SKILL_SHINE_SWORD)
				//	{
				//		flag = 0;
				//	}
					else
					{
						flag = fDomain[SKILLDOMAIN_SWORD];

						if ((*g_pSkillInfoTable)[id].IsActive())
						{
							flag |= FLAG_SKILL_ENABLE;
						}					
					}

					insert(SKILLID_MAP::value_type( id, SKILLID_NODE(id, flag) ));
				}

				// 다음
				swordDomain.Next();
			}

			//-----------------------------------------------------
			// Gun
			//-----------------------------------------------------
			MSkillDomain& gunDomain = (*g_pSkillManager)[SKILLDOMAIN_GUN];

			gunDomain.SetBegin();		
			while (gunDomain.IsNotEnd())
			{
				MSkillDomain::SKILLSTATUS	status	= gunDomain.GetSkillStatus();
				
				// 배웠으면..
				if (status == MSkillDomain::SKILLSTATUS_LEARNED)
				{
					ACTIONINFO id = gunDomain.GetSkillID();

					if ((*g_pSkillInfoTable)[id].GetMP() > playerMP)
					{
						flag = 0;
					}
					else
					{
						flag = fDomain[SKILLDOMAIN_GUN];

						if ((*g_pSkillInfoTable)[id].IsActive())
						{
							flag |= FLAG_SKILL_ENABLE;
						}					
					}

					insert(SKILLID_MAP::value_type( id, SKILLID_NODE(id, flag) ));
				}

				// 다음
				gunDomain.Next();
			}

			//-----------------------------------------------------
			// Enchant - 그냥 모두 추가하면 된다.
			//-----------------------------------------------------
			MSkillDomain& enchantDomain = (*g_pSkillManager)[SKILLDOMAIN_ENCHANT];

			enchantDomain.SetBegin();		
			while (enchantDomain.IsNotEnd())
			{
				MSkillDomain::SKILLSTATUS	status	= enchantDomain.GetSkillStatus();

				// 배웠으면..
				if (status == MSkillDomain::SKILLSTATUS_LEARNED)
				{
					ACTIONINFO id = enchantDomain.GetSkillID();
					
					int iSilver = 0;
					if(pItem)
						iSilver	= pItem->GetSilver();


					if ((*g_pSkillInfoTable)[id].GetMP() > playerMP)
					{
						flag = 0;
					}
					//20090306 인챈트 스킬중에서도 은도금에 영향 받는 스킬은 체크를 하자
				//	else if(iSilver == 0 && id == SKILL_HEAVEN_GROUND)
				//	{
				//		flag = 0;
				//	}
					else
					{
						flag = FLAG_SKILL_ENABLE;
					}

					insert(SKILLID_MAP::value_type( id, SKILLID_NODE(id, flag) ));
				}

				// 다음
				enchantDomain.Next();
			}

			
			//-----------------------------------------------------
			// Heal - 그냥 모두 추가하면 된다.
			//-----------------------------------------------------
			MSkillDomain& healDomain = (*g_pSkillManager)[SKILLDOMAIN_HEAL];

			healDomain.SetBegin();		
			while (healDomain.IsNotEnd())
			{
				MSkillDomain::SKILLSTATUS	status	= healDomain.GetSkillStatus();

				// 배웠으면..
				if (status == MSkillDomain::SKILLSTATUS_LEARNED)
				{
					ACTIONINFO id = healDomain.GetSkillID();

					if ((*g_pSkillInfoTable)[id].GetMP() > playerMP)
					{
						flag = 0;
					}
					else
					{
						flag = FLAG_SKILL_ENABLE;
					}

					insert(SKILLID_MAP::value_type( id, SKILLID_NODE(id, flag) ));
				}

				// 다음
				healDomain.Next();
			}
			
	
			//-----------------------------------------------------
			//
			// Inventory 검색
			//
			//-----------------------------------------------------
			BOOL bCheckHolyWater	= TRUE;
			BOOL bCheckPortal		= TRUE;

			BOOL bCheckInstallMine = (gunDomain.GetSkillStatus(SKILL_INSTALL_MINE)==MSkillDomain::SKILLSTATUS_LEARNED);
			BOOL bCheckCreateMine = (gunDomain.GetSkillStatus(SKILL_MAKE_MINE)==MSkillDomain::SKILLSTATUS_LEARNED);
			BOOL bCheckCreateBomb = (gunDomain.GetSkillStatus(SKILL_MAKE_BOMB)==MSkillDomain::SKILLSTATUS_LEARNED);		
			
			BOOL bCheckBomb			= (gunDomain.GetSkillStatus(SKILL_THROW_BOMB)==MSkillDomain::SKILLSTATUS_LEARNED);
			BOOL bCheckBombOrMine   = bCheckBomb || bCheckInstallMine;
			BOOL bCheckBombOrMineMaterial   = bCheckCreateBomb || bCheckCreateMine;
			
			BOOL bHasBomb			= FALSE;
			BOOL bHasMine			= FALSE;
			BOOL bHasMineMaterial	= FALSE;
			BOOL bHasBombMaterial	= FALSE;

			g_pInventory->SetBegin();

			while (g_pInventory->IsNotEnd())
			{
				const MItem* pItem = g_pInventory->Get();

				ITEM_CLASS itemClass = pItem->GetItemClass();

				// 2005, 3, 2, sobeit add start - 서브 인벤도 뒤지자..-_-; 소스가 깝깝하네..ㅋ
				if(itemClass == ITEM_CLASS_SUB_INVENTORY)
				{
					MSubInventory* pSubItem = (MSubInventory*)pItem;
					pSubItem->SetBegin();
					while(pSubItem->IsNotEnd())
					{

						const MItem* pSubSbuItem = pSubItem->Get();
						if(NULL != pSubSbuItem && bCheckPortal && pSubSbuItem->GetItemClass() == ITEM_CLASS_SLAYER_PORTAL_ITEM)
						{
							flag = FLAG_SKILL_ENABLE;
							insert(SKILLID_MAP::value_type( SUMMON_HELICOPTER, SKILLID_NODE(SUMMON_HELICOPTER, flag)) );
							bCheckPortal = FALSE;
						}
						pSubItem->Next();
					}
				}

				// 2005, 3, 2, sobeit add end

				//-----------------------------------------------------
				// Portal
				//-----------------------------------------------------
				if (bCheckPortal && itemClass==ITEM_CLASS_SLAYER_PORTAL_ITEM)
				{				
					flag = FLAG_SKILL_ENABLE;
				
					insert(SKILLID_MAP::value_type( SUMMON_HELICOPTER, SKILLID_NODE(SUMMON_HELICOPTER, flag)) );

					bCheckPortal = FALSE;
				}
				//-----------------------------------------------------
				// HolyWater
				//-----------------------------------------------------			
				else if (bCheckHolyWater && itemClass==ITEM_CLASS_HOLYWATER)
				{
					if ((*g_pSkillInfoTable)[MAGIC_THROW_HOLY_WATER].GetMP() > playerMP)
					{
						flag = 0;
					}
					else
					{
						flag = FLAG_SKILL_ENABLE;
					}

					insert(SKILLID_MAP::value_type( MAGIC_THROW_HOLY_WATER, SKILLID_NODE(MAGIC_THROW_HOLY_WATER, flag)) );				

					// [도움말] 벨트의 아이템 사용
//					__BEGIN_HELP_EVENT
//						ExecuteHelpEvent( HE_ITEM_APPEAR_HOLY_WATER );	
//					__END_HELP_EVENT

					bCheckHolyWater = FALSE;
				}
				//-----------------------------------------------------
				// Bomb / Mine - 종류별로 따로 추가해야한다.
				//-----------------------------------------------------
				else if (bCheckBombOrMine
						&& (itemClass==ITEM_CLASS_BOMB
							|| itemClass==ITEM_CLASS_MINE))
				{
					if (itemClass==ITEM_CLASS_BOMB)
					{
						bHasBomb = TRUE;

						if (bCheckBomb)	flag = FLAG_SKILL_ENABLE;
									else flag = 0;
					}
					else
					{
						bHasMine = TRUE;

						if (bCheckInstallMine) flag = FLAG_SKILL_ENABLE;
										else flag = 0;					
					}

					int skillID = pItem->GetUseActionInfo();

					

					// 폭탄/지뢰 마다 사용 가능한 아이콘을 추가한다.
					if (find((ACTIONINFO)skillID)==end())
					{
						insert(SKILLID_MAP::value_type( (ACTIONINFO)skillID, SKILLID_NODE((ACTIONINFO)skillID, flag)) );
					}
				}
				//-----------------------------------------------------
				// 폭탄/지뢰 재료
				//-----------------------------------------------------
				else if (bCheckBombOrMineMaterial
							&& itemClass==ITEM_CLASS_BOMB_MATERIAL)
				{
					if (IsBombMaterial(pItem))
					{
						bHasBombMaterial = TRUE;
					}
					else
					{
						bHasMineMaterial = TRUE;
					}
				}
				
				// 다음
				g_pInventory->Next();
			}

			// mouse에 있는 아이템도 체크한다.
			MItem* pMouseItem = UI_GetMouseItem();

			if (pMouseItem!=NULL)
			{
				ITEM_CLASS	itemClass	= pMouseItem->GetItemClass();
				bool isBombMaterial = IsBombMaterial(pMouseItem);

				bHasBomb			= bHasBomb || itemClass==ITEM_CLASS_BOMB;
				bHasMine			= bHasMine || itemClass==ITEM_CLASS_MINE;

				bHasMineMaterial	= bHasMineMaterial || itemClass==ITEM_CLASS_BOMB_MATERIAL && !isBombMaterial;
				bHasBombMaterial	= bHasBombMaterial || itemClass==ITEM_CLASS_BOMB_MATERIAL && isBombMaterial;
			}

			// 지뢰 설치 기술을 배웠고 지뢰가 있다면 icon을 enable시킨다.
			if (bCheckInstallMine)
			{
				ACTIONINFO skillID = SKILL_INSTALL_MINE;
				flag = (IsEnableSkill(skillID) && bHasMine? FLAG_SKILL_ENABLE : 0);
				
				iterator iSkill = find( skillID );
				if (iSkill != end())
				{			
					iSkill->second.Flag = flag;
				}
				else
				{
					insert(SKILLID_MAP::value_type( skillID, SKILLID_NODE(skillID, flag)) );
				}
			}

			// 지뢰 생성 기술을 배웠고 지뢰 재료가 있다면 icon을 enable시킨다.
			if (bCheckCreateMine)
			{
				ACTIONINFO skillID = SKILL_MAKE_MINE;
				flag = (IsEnableSkill(skillID) && bHasMineMaterial? FLAG_SKILL_ENABLE : 0);
				
				iterator iSkill = find( skillID );
				if (iSkill != end())
				{			
					iSkill->second.Flag = flag;
				}
				else
				{
					insert(SKILLID_MAP::value_type( skillID, SKILLID_NODE(skillID, flag)) );
				}
			}

			// 폭탄 생성 기술을 배웠고 폭탄 재료가 있다면 icon을 enable시킨다.
			if (bCheckCreateBomb)
			{
				ACTIONINFO skillID = SKILL_MAKE_BOMB;
				flag = (IsEnableSkill(skillID) && bHasBombMaterial? FLAG_SKILL_ENABLE : 0);
				
				iterator iSkill = find( skillID );
				if (iSkill != end())
				{			
					iSkill->second.Flag = flag;
				}
				else
				{
					insert(SKILLID_MAP::value_type( skillID, SKILLID_NODE(skillID, flag)) );
				}
			}

			// 폭탄 던지기 기술을 배웠고 폭탄이 있다면 icon을 enable시킨다.
			if (bCheckBomb)
			{
				ACTIONINFO skillID = SKILL_THROW_BOMB;
				flag = (IsEnableSkill(skillID) && bHasBomb? FLAG_SKILL_ENABLE : 0);
				
				iterator iSkill = find( skillID );
				if (iSkill != end())
				{			
					iSkill->second.Flag = flag;
				}
				else
				{
					insert(SKILLID_MAP::value_type( skillID, SKILLID_NODE(skillID, flag)) );
				}
			}

			//-----------------------------------------------------
			// Restore 임의로 추가
			//-----------------------------------------------------
			if (g_pUserInformation->HasSkillRestore)
			{
				if ((*g_pSkillInfoTable)[MAGIC_RESTORE].GetMP() > playerMP)
				{
					flag = 0;
				}
				else
				{
					flag = FLAG_SKILL_ENABLE;
				}

				insert(SKILLID_MAP::value_type( MAGIC_RESTORE, SKILLID_NODE(MAGIC_RESTORE, flag) ));
			}


			//-----------------------------------------------------
			// 은도금이 필요한 스킬들
			//-----------------------------------------------------
		/*	if(pItem != NULL && !pItem->IsGunItem())
			{
				if(pItem->GetSilver() < 50)
				{
					for(int i = 0; i < 5; ++i) {
						ACTIONINFO localActionInfo = static_cast<ACTIONINFO>(SKILL_SHINE_SWORD + i);

						iterator iSkill = find( localActionInfo );
						if (iSkill != end())
							iSkill->second.Flag = false;
					}
				}
			}*/ // 2013-5-23  by rallser 팁귁瘻斂세콘矜狼뗬陵
		}
		break;

	//-----------------------------------------------------
	//
	//					vampire인 경우
	//
	//-----------------------------------------------------
	case RACE_VAMPIRE:
		{		
			//-----------------------------------------------------
			//
			// SkillTree 검색
			//
			//-----------------------------------------------------
			// [새기술3] 관 속에서는 기술 못 쓴다.
			if (g_pPlayer->IsInCasket())
			{
				flag = FLAG_SKILL_ENABLE;

				insert(SKILLID_MAP::value_type( MAGIC_OPEN_CASKET, SKILLID_NODE(MAGIC_OPEN_CASKET, flag) ));
				gC_vs_ui.SelectSkill( MAGIC_OPEN_CASKET );

				return;
			}
			
			// 뱀파이어인 경우만 쓸 수 있다. --> 박쥐나 늑대에서는 사용못한다.
			if (g_pPlayer->GetCreatureType()==CREATURETYPE_VAMPIRE_MALE1
				|| g_pPlayer->GetCreatureType()==CREATURETYPE_VAMPIRE_FEMALE1
				|| g_pPlayer->GetCreatureType()==CREATURETYPE_VAMPIRE_MALE2
				|| g_pPlayer->GetCreatureType()==CREATURETYPE_VAMPIRE_FEMALE2
				|| g_pPlayer->GetCreatureType()==CREATURETYPE_VAMPIRE_MALE3
				|| g_pPlayer->GetCreatureType()==CREATURETYPE_VAMPIRE_FEMALE3
				|| g_pPlayer->GetCreatureType()==CREATURETYPE_VAMPIRE_MALE4
				|| g_pPlayer->GetCreatureType()==CREATURETYPE_VAMPIRE_FEMALE4
				|| g_pPlayer->GetCreatureType()==CREATURETYPE_VAMPIRE_OPERATOR)
			{
				MSkillDomain& vampireDomain = (*g_pSkillManager)[SKILLDOMAIN_VAMPIRE];
				
				vampireDomain.SetBegin();		

				MItem* pSubInventory = NULL;
				while (vampireDomain.IsNotEnd())
				{
					MSkillDomain::SKILLSTATUS	status	= vampireDomain.GetSkillStatus();

					// 배웠으면..
					if (status == MSkillDomain::SKILLSTATUS_LEARNED)
					{
						ACTIONINFO id = vampireDomain.GetSkillID();

						// 레어존에서는 인비저빌리티 못쓰게 한다...하드하드
						if ((*g_pSkillInfoTable)[id].GetMP() > playerMP
							|| id == MAGIC_INVISIBILITY && (g_pZone->GetID() == 1104 || g_pZone->GetID() == 1106 || g_pZone->GetID() == 1114 || g_pZone->GetID() == 1115))
						{
							flag = 0;
						}
						else
						{
							flag = FLAG_SKILL_ENABLE;					
						}


						// Item 사용하는거 체크
						switch (id)
						{
							case MAGIC_BLOODY_MARK :
								if (NULL == ((MItemManager*)g_pInventory)->FindItemAll( MVampirePortalItemFinder( false ) , pSubInventory))
								{
									flag = 0;
								}							
							break;

							case MAGIC_BLOODY_TUNNEL :
								if (NULL == ((MItemManager*)g_pInventory)->FindItemAll( MVampirePortalItemFinder( true ) , pSubInventory ))
								{
									flag = 0;
								}
							break;

							case MAGIC_TRANSFORM_TO_WOLF :
								if (NULL == g_pInventory->FindItem( ITEM_CLASS_VAMPIRE_ETC, 0 ))
								{
									flag = 0;
								}							
							break;

							case MAGIC_TRANSFORM_TO_BAT :
								if (NULL == g_pInventory->FindItemAll( MItemClassTypeFinder(ITEM_CLASS_VAMPIRE_ETC , 1), pSubInventory )
#if __CONTENTS(__FAST_TRANSFORTER)
									&& NULL == g_pInventory->FindItemAll( MItemClassTypeFinder(ITEM_CLASS_VAMPIREWING_ITEM , 0), pSubInventory)
									&& NULL == g_pInventory->FindItemAll( MItemClassTypeFinder(ITEM_CLASS_VAMPIREWING_ITEM , 2), pSubInventory)
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
									&& NULL == g_pInventory->FindItemAll( MItemClassTypeFinder(ITEM_CLASS_VAMPIREWING_ITEM , 1), pSubInventory)
#endif //__SECOND_TRANSFORTER
									)

								{
									flag = 0;
								}							
							break;
							
							case SKILL_TRANSFORM_TO_WERWOLF :
								if(g_pInventory->FindItem( ITEM_CLASS_SKULL, 39) == NULL)
								{
									flag = 0;
								}
							break;

							case MAGIC_HOWL :
								flag=0;
							break;
							
						}

						insert(SKILLID_MAP::value_type( id, SKILLID_NODE(id, flag) ));
					}

					// 다음
					vampireDomain.Next();
				}
			}

			//-----------------------------------------------------
			//
			// Inventory 검색
			//
			//-----------------------------------------------------
			/*
			BOOL bCheckPortalMark = TRUE;
			BOOL bCheckPortalTunnel = TRUE;

			g_pInventory->SetBegin();

			while ((*g_pInventory).IsNotEnd())
			{
				const MItem* pItem = g_pInventory->Get();

				ITEM_CLASS itemClass = pItem->GetItemClass();

				//-----------------------------------------------------
				// Portal
				//-----------------------------------------------------
				if (itemClass==ITEM_CLASS_VAMPIRE_PORTAL_ITEM)
				{				
					flag = FLAG_SKILL_ENABLE;
				
					if (bCheckPortalMark && !pItem->IsMarked())
					{
						insert(SKILLID_MAP::value_type( MAGIC_BLOODY_MARK, SKILLID_NODE(MAGIC_BLOODY_MARK, flag)) );
						
						bCheckPortalMark = false;
					}

					if (bCheckPortalTunnel && pItem->IsMarked())
					{
						insert(SKILLID_MAP::value_type( MAGIC_BLOODY_TUNNEL, SKILLID_NODE(MAGIC_BLOODY_TUNNEL, flag)) );
						
						bCheckPortalTunnel = false;
					}				
				}

				// 다음
				g_pInventory->Next();
			}
			*/

			//-----------------------------------------------------
			//
			// 기본 Skill
			//
			//-----------------------------------------------------
			// 흡혈 --> 늑대나 박쥐는 흡혈 못한다.
			

			//-----------------------------------------------------
			// 불기둥 임의로 추가
			//-----------------------------------------------------
			if (g_pUserInformation->HasMagicGroundAttack)
			{
				if ((*g_pSkillInfoTable)[MAGIC_GROUND_ATTACK].GetMP() > playerMP)
				{
					flag = 0;
				}
				else
				{
					flag = FLAG_SKILL_ENABLE;
				}

				insert(SKILLID_MAP::value_type( MAGIC_GROUND_ATTACK, SKILLID_NODE(MAGIC_GROUND_ATTACK, flag) ));
			}
			
			SetAvailableVampireSkills();

			//-----------------------------------------------------
			// 블러디 스네이크 임의로 추가
			//-----------------------------------------------------
			if (g_pUserInformation->HasMagicBloodySnake)
			{
				if ((*g_pSkillInfoTable)[MAGIC_BLOODY_SNAKE].GetMP() > playerMP)
				{
					flag = 0;
				}
				else
				{
					flag = FLAG_SKILL_ENABLE;
				}

				insert(SKILLID_MAP::value_type( MAGIC_BLOODY_SNAKE, SKILLID_NODE(MAGIC_BLOODY_SNAKE, flag) ));
			}

			//-----------------------------------------------------
			// 블러디 워프 임의로 추가
			//-----------------------------------------------------
			if (g_pUserInformation->HasMagicBloodyWarp)
			{
				if ((*g_pSkillInfoTable)[MAGIC_BLOODY_WARP].GetMP() > playerMP)
				{
					flag = 0;
				}
				else
				{
					flag = FLAG_SKILL_ENABLE;
				}

				insert(SKILLID_MAP::value_type( MAGIC_BLOODY_WARP, SKILLID_NODE(MAGIC_BLOODY_WARP, flag) ));
			}
		}
		break;

	case RACE_OUSTERS:
		{		
			//-----------------------------------------------------
			//
			// SkillTree 검색
			//
			//-----------------------------------------------------
			{
				MSkillDomain& oustersDomain = (*g_pSkillManager)[SKILLDOMAIN_OUSTERS];
				
				oustersDomain.SetBegin();		
				while (oustersDomain.IsNotEnd())
				{
					MSkillDomain::SKILLSTATUS	status	= oustersDomain.GetSkillStatus();

					// 배웠으면..
					if (status == MSkillDomain::SKILLSTATUS_LEARNED)
					{
						ACTIONINFO id = oustersDomain.GetSkillID();

						SKILLINFO_NODE sInfo = (*g_pSkillInfoTable)[id];
						
						flag = 0;

						if (sInfo.GetMP() <= playerMP)
						{
							if(sInfo.IsActive())
							{
								flag = FLAG_SKILL_ENABLE;					
							}
							else
							{
								// 현재 들고 있는 item
								const MItem* pItem = (*g_pOustersGear).GetItem( (MOustersGear::GEAR_OUSTERS)MOustersGear::GEAR_OUSTERS_RIGHTHAND );
								
								if(sInfo.ElementalDomain == SKILLINFO_NODE::ELEMENTAL_DOMAIN_NO_DOMAIN ||
									sInfo.ElementalDomain == SKILLINFO_NODE::ELEMENTAL_DOMAIN_WIND ||
									sInfo.ElementalDomain == SKILLINFO_NODE::ELEMENTAL_DOMAIN_ETC ||
									sInfo.GetSkillStep() == SKILL_STEP_ETC)
								{
									flag = FLAG_SKILL_ENABLE;
								}
								else
								{
									if (pItem!=NULL && pItem->IsAffectStatus())
									{	
										const int itemClass = pItem->GetItemClass();
										
										if (itemClass == ITEM_CLASS_OUSTERS_CHAKRAM && sInfo.ElementalDomain == SKILLINFO_NODE::ELEMENTAL_DOMAIN_COMBAT || 
											itemClass == ITEM_CLASS_OUSTERS_WRISTLET &&
												(
													sInfo.ElementalDomain == SKILLINFO_NODE::ELEMENTAL_DOMAIN_FIRE && sInfo.Fire <= g_pPlayer->GetElementalFire() ||
													sInfo.ElementalDomain == SKILLINFO_NODE::ELEMENTAL_DOMAIN_WATER && sInfo.Water <= g_pPlayer->GetElementalWater() ||
													sInfo.ElementalDomain == SKILLINFO_NODE::ELEMENTAL_DOMAIN_EARTH && sInfo.Earth <= g_pPlayer->GetElementalEarth()
												)
											)
										{
											flag = FLAG_SKILL_ENABLE;
										}
									}
								}
							}
						}

						if( id == SKILL_SUMMON_SYLPH )
						{
							MItem* pSubInventory = NULL;
							if(NULL == ((MItemManager*)g_pInventory)->FindItemAll( MOustersSummonGemItemFinder(), pSubInventory )
#if __CONTENTS(__FAST_TRANSFORTER)
								&& NULL == g_pInventory->FindItemAll( MItemClassTypeFinder(ITEM_CLASS_OUSTERSWING_ITEM , 0), pSubInventory )
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
								&& NULL == g_pInventory->FindItemAll( MItemClassTypeFinder(ITEM_CLASS_OUSTERSWING_ITEM , 1), pSubInventory )
								&& NULL == g_pInventory->FindItemAll( MItemClassTypeFinder(ITEM_CLASS_OUSTERSWING_ITEM , 2), pSubInventory )
#endif //__SECOND_TRANSFORTER
								)
								flag = 0;
						}

						insert(SKILLID_MAP::value_type( id, SKILLID_NODE(id, flag) ));
					}

					// 다음
					oustersDomain.Next();
				}
			}

			//-----------------------------------------------------
			//
			// 기본 Skill
			//
			//-----------------------------------------------------
//			// 흡혈 --> 늑대나 박쥐는 흡혈 못한다.
//			if (g_pPlayer->GetCreatureType()!=CREATURETYPE_BAT
//				&& g_pPlayer->GetCreatureType()!=CREATURETYPE_WOLF)
//			{
//				if ((*g_pSkillInfoTable)[SKILL_BLOOD_DRAIN].GetMP() > playerMP)
//				{
//					flag = 0;
//				}
//				else
//				{
//					flag = FLAG_SKILL_ENABLE;
//				}
//				insert(SKILLID_MAP::value_type( SKILL_BLOOD_DRAIN, SKILLID_NODE(SKILL_BLOOD_DRAIN, flag) ));
//			}

		}
		break;
	}


	//-----------------------------------------------------
	// Etc - 그냥 모두 추가하면 된다.
	//-----------------------------------------------------
	MSkillDomain& etcDomain = (*g_pSkillManager)[SKILLDOMAIN_ETC];
	
	etcDomain.SetBegin();
	while (etcDomain.IsNotEnd())
	{
		MSkillDomain::SKILLSTATUS	status	= etcDomain.GetSkillStatus();
		
		// 배웠으면..
		if (status == MSkillDomain::SKILLSTATUS_LEARNED)
		{
			ACTIONINFO id = etcDomain.GetSkillID();
			
			if ((*g_pSkillInfoTable)[id].GetMP() > playerMP)
			{
				flag = 0;
			}
			else
			{
				flag = FLAG_SKILL_ENABLE;
			}
			
			erase(id);
			insert(SKILLID_MAP::value_type( id, SKILLID_NODE(id, flag) ));
		}
		
		// 다음
		etcDomain.Next();
	}

	
	//-----------------------------------------------------
	// 
	// 피의 성서 보너스 맘대로 추가-ㅅ-
	//
	//-----------------------------------------------------
	int i;
	for(i = 0; i < HOLYLAND_BONUS_MAX; i++)
	{
		if(g_abHolyLandBonusSkills[i] == true)
		{
			insert(SKILLID_MAP::value_type( (ACTIONINFO)(SKILL_HOLYLAND_BLOOD_BIBLE_ARMEGA+i), SKILLID_NODE((ACTIONINFO)(SKILL_HOLYLAND_BLOOD_BIBLE_ARMEGA+i), FLAG_SKILL_ENABLE) ));
		}
	}

	for(i = 0; i < SWEEPER_BONUS_MAX; i++)
	{
		if( g_abSweeperBonusSkills[i] == true )
		{
			insert( SKILLID_MAP::value_type( (ACTIONINFO)(SKILL_SWEEPER_BONUS_1 + i), SKILLID_NODE( (ACTIONINFO)(SKILL_SWEEPER_BONUS_1+i), FLAG_SKILL_ENABLE) ) );
		}
	}

	if (g_pPlayer->GetCreatureType()!=CREATURETYPE_BAT
		&& g_pPlayer->GetCreatureType()!=CREATURETYPE_VAMPIRE_GHOST
		&& g_pPlayer->GetCreatureType()!=CREATURETYPE_WOLF
#if __CONTENTS(__FAST_TRANSFORTER)
		&& g_pPlayer->GetCreatureType() != CREATURETYPE_FLITTERMOUSE
		&& g_pPlayer->GetCreatureType() != CREATURETYPE_NEDE
		&& g_pPlayer->GetCreatureType() != CREATURETYPE_KLTL
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
		&& g_pPlayer->GetCreatureType() != CREATURETYPE_SHAPE_OF_DEMON
#endif //__SECOND_TRANSFORTER

		)
	{
//워아이템을 가지고 있으면 커플체인은 사용할수 없다.
		MItem*	pWarItem = g_pInventory->FindItem(ITEM_CLASS_WAR_ITEM);
		if(pWarItem!=NULL)
		{
		}
		else
		{
			MPlayerGear* pGear;
			MItemClassFinder itemFinder( ITEM_CLASS_COUPLE_RING );
			
			switch(g_pPlayer->GetRace())
			{
			case RACE_SLAYER:
				pGear = g_pSlayerGear;							
				break;
				
			case RACE_VAMPIRE:
				pGear = g_pVampireGear;
				itemFinder.SetItemClass( ITEM_CLASS_VAMPIRE_COUPLE_RING);
				break;
				
			case RACE_OUSTERS:
				itemFinder.SetItemClass( ITEM_CLASS_OUSTERS_HARMONIC_PENDENT);
				pGear = g_pOustersGear;
				break;
			}
			
			MItem *pItem = pGear->FindItem( itemFinder );
			if(pItem != NULL)
			{
				insert(SKILLID_MAP::value_type( (ACTIONINFO)SKILL_LOVE_CHAIN, SKILLID_NODE((ACTIONINFO)(SKILL_LOVE_CHAIN), pItem->IsAffectStatus() ) ));
			}
		}
	}
	
//	insert(SKILLID_MAP::value_type( (ACTIONINFO)SKILL_MAGIC_ELUSION, SKILLID_NODE((ACTIONINFO)(SKILL_MAGIC_ELUSION),  FLAG_SKILL_ENABLE)) );

	
	//-----------------------------------------------------
	// 일자코흐 프롤로그 - 껍닥 벗기기
	// : 무두질용 칼이 있을 경우에만 무두질 스킬 추가
	//-----------------------------------------------------
	MItemClassTypeFinder findTanningKnife(ITEM_CLASS_COMMON_QUEST_ITEM, 3);
	MItem* pSubInventory;
	MItem* pTanningKnife = g_pInventory->FindItemAll(findTanningKnife, pSubInventory);

	if(pTanningKnife)
	{
		ACTIONINFO		id		= static_cast<ACTIONINFO>(SKILL_TANNING);
		SKILLID_NODE	node	= SKILLID_NODE(id, FLAG_SKILL_ENABLE);
		insert(SKILLID_MAP::value_type(id, node));
	}

	//-----------------------------------------------------
	// 시야 계산
	//-----------------------------------------------------
	g_pPlayer->CalculateLightSight();
	

	//CheckMP();

	// 스킬이 비었을때 호출되면 -_- 난리난다.
//	if( size() > 5 )
//		gC_vs_ui.ResetHotKey();
#endif
}

void			
MSkillSet::SetAvailableVampireSkills()
{
#ifdef __GAME_CLIENT__
	MSkillDomain& vampireDomain = (*g_pSkillManager)[SKILLDOMAIN_VAMPIRE];
	TYPE_CREATURETYPE PlayerCreatureType = g_pPlayer->GetCreatureType();

	int playerMP;		
	BYTE flag;
	
	if (g_pPlayer->GetRace() != RACE_VAMPIRE)
	{
		playerMP = g_pPlayer->GetMP();	

		// EFFECTSTATUS_SACRIFICE 사용중이면 HP 1이 MP 2가 된다.
		if (g_pPlayer->HasEffectStatus(EFFECTSTATUS_SACRIFICE))
		{
			playerMP += (g_pPlayer->GetHP() << 1);
		}		
	}
	else
	{
		// vampire인 경우는 HP를 MP대신에 쓴다.
		playerMP = g_pPlayer->GetHP();	
	}

	if (PlayerCreatureType!=CREATURETYPE_BAT
		&& PlayerCreatureType!=CREATURETYPE_VAMPIRE_GHOST
		&& PlayerCreatureType!=CREATURETYPE_WOLF
		&& PlayerCreatureType!=CREATURETYPE_WER_WOLF//긴의빈세콘
		&& PlayerCreatureType!=CREATURETYPE_INSTALL_TURRET
		&& PlayerCreatureType!=CREATURETYPE_INSTALL_MK1
#if __CONTENTS(__FAST_TRANSFORTER)
		&& PlayerCreatureType != CREATURETYPE_FLITTERMOUSE
		&& PlayerCreatureType != CREATURETYPE_NEDE
		&& PlayerCreatureType != CREATURETYPE_KLTL
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
		&& PlayerCreatureType != CREATURETYPE_SHAPE_OF_DEMON
#endif //__SECOND_TRANSFORTER
		)
	{
		if ((*g_pSkillInfoTable)[SKILL_BLOOD_DRAIN].GetMP() > playerMP)
		{
			flag = 0;
		}
		else
		{
			flag = FLAG_SKILL_ENABLE;
		}
		insert(SKILLID_MAP::value_type( SKILL_BLOOD_DRAIN, SKILLID_NODE(SKILL_BLOOD_DRAIN, flag) ));
	}
	
	//-----------------------------------------------------
	// 
	// invisible인가?
	//
	//-----------------------------------------------------
	if (g_pPlayer->IsInvisible())
	{
		flag = FLAG_SKILL_ENABLE;
		
		insert(SKILLID_MAP::value_type( MAGIC_UN_INVISIBILITY, SKILLID_NODE(MAGIC_UN_INVISIBILITY, flag) ));
	}
		
	switch( PlayerCreatureType )
	{
	case CREATURETYPE_WOLF :
		{
			if ((*g_pSkillInfoTable)[MAGIC_EAT_CORPSE].GetMP() > playerMP)
			{
				flag = 0;
			}
			else
			{
				flag = FLAG_SKILL_ENABLE;
			}
			insert(SKILLID_MAP::value_type( MAGIC_EAT_CORPSE, SKILLID_NODE(MAGIC_EAT_CORPSE, flag) ));
			
			// 짖기 - -;
			if( vampireDomain.GetSkillStatus( MAGIC_HOWL ) == MSkillDomain::SKILLSTATUS_LEARNED )
			{
				if( (*g_pSkillInfoTable)[MAGIC_HOWL].GetMP() > playerMP)				
				{
					flag = 0;
				}
				else
				{
					flag = FLAG_SKILL_ENABLE;
				}
				insert(SKILLID_MAP::value_type( MAGIC_HOWL, SKILLID_NODE(MAGIC_HOWL, flag) ));
			}
		}
		break;
	case CREATURETYPE_WER_WOLF ://긴의빈豚冀賈痰돨세콘
		{
			if( (*g_pSkillInfoTable)[SKILL_BITE_OF_DEATH].GetMP() > playerMP )
			{
				flag  = 0;
			}
			else
			{
				flag = FLAG_SKILL_ENABLE;
			}

			insert(SKILLID_MAP::value_type( SKILL_BITE_OF_DEATH, SKILLID_NODE(SKILL_BITE_OF_DEATH, flag) ));

			if( vampireDomain.GetSkillStatus( MAGIC_RAPID_GLIDING ) == MSkillDomain::SKILLSTATUS_LEARNED )
			{
				if( (*g_pSkillInfoTable)[MAGIC_RAPID_GLIDING].GetMP() > playerMP )
				{
					flag  = 0;
				}
				else
				{
					flag = FLAG_SKILL_ENABLE;
				}
				insert(SKILLID_MAP::value_type( MAGIC_RAPID_GLIDING, SKILLID_NODE(MAGIC_RAPID_GLIDING, flag) ));
			}

			if( vampireDomain.GetSkillStatus( SKILL_VIOLENT_PHANTOM ) == MSkillDomain::SKILLSTATUS_LEARNED )
			{
				if( (*g_pSkillInfoTable)[SKILL_VIOLENT_PHANTOM].GetMP() > playerMP )
				{
					flag  = 0;
				}
				else
				{
					flag = FLAG_SKILL_ENABLE;
				}
				insert(SKILLID_MAP::value_type( SKILL_VIOLENT_PHANTOM, SKILLID_NODE(SKILL_VIOLENT_PHANTOM, flag) ));
			}

	/*		if( vampireDomain.GetSkillStatus( SKILL_LETHAL_CLAW ) == MSkillDomain::SKILLSTATUS_LEARNED )//藤속161屢綾瞳낚의榴檄苟，by rallser
			{
				if( (*g_pSkillInfoTable)[SKILL_LETHAL_CLAW].GetMP() > playerMP )
				{
					flag  = 0;
				}
				else
				{
					flag = FLAG_SKILL_ENABLE;
				}
				insert(SKILLID_MAP::value_type( SKILL_LETHAL_CLAW, SKILLID_NODE(SKILL_LETHAL_CLAW, flag) ));
			}*/			 //MAGIC_BLOODY_ZENITH
			if( vampireDomain.GetSkillStatus( MAGIC_BLOODY_ZENITH ) == MSkillDomain::SKILLSTATUS_LEARNED )//藤속161屢綾瞳낚의榴檄苟，by rallser
			{
				if( (*g_pSkillInfoTable)[SKILL_LETHAL_CLAW].GetMP() > playerMP )
				{
					flag  = 0;
				}
				else
				{
					flag = FLAG_SKILL_ENABLE;
				}
				insert(SKILLID_MAP::value_type( MAGIC_BLOODY_ZENITH, SKILLID_NODE(MAGIC_BLOODY_ZENITH, flag) ));
			}
			if( vampireDomain.GetSkillStatus( MAGIC_DARKNESS ) == MSkillDomain::SKILLSTATUS_LEARNED )//藤속161屢綾瞳낚의榴檄苟，by rallser
			{
				if( (*g_pSkillInfoTable)[MAGIC_DARKNESS].GetMP() > playerMP )
				{
					flag  = 0;
				}
				else
				{
					flag = FLAG_SKILL_ENABLE;
				}
				insert(SKILLID_MAP::value_type( MAGIC_DARKNESS, SKILLID_NODE(MAGIC_DARKNESS, flag) ));
			}
			if( vampireDomain.GetSkillStatus( SKILL_WILD_WOLF ) == MSkillDomain::SKILLSTATUS_LEARNED )
			{
				if( (*g_pSkillInfoTable)[SKILL_WILD_WOLF].GetMP() > playerMP )
				{
					flag  = 0;
				}
				else
				{
					flag = FLAG_SKILL_ENABLE;
				}
				insert(SKILLID_MAP::value_type( SKILL_WILD_WOLF, SKILLID_NODE(SKILL_WILD_WOLF, flag) ));
			}			
		}
		break;
	}
		
	//-----------------------------------------------------
	// 
	// 변신 중인가?
	//
	//-----------------------------------------------------
	if (PlayerCreatureType!=CREATURETYPE_VAMPIRE_MALE1
		&& PlayerCreatureType!=CREATURETYPE_VAMPIRE_FEMALE1
		&& PlayerCreatureType!=CREATURETYPE_VAMPIRE_MALE2
		&& PlayerCreatureType!=CREATURETYPE_VAMPIRE_FEMALE2
		&& PlayerCreatureType!=CREATURETYPE_VAMPIRE_MALE3
		&& PlayerCreatureType!=CREATURETYPE_VAMPIRE_FEMALE3
		&& PlayerCreatureType!=CREATURETYPE_VAMPIRE_MALE4
		&& PlayerCreatureType!=CREATURETYPE_VAMPIRE_FEMALE4
		&& PlayerCreatureType!=CREATURETYPE_VAMPIRE_OPERATOR)
	{			
		flag = FLAG_SKILL_ENABLE;
		
		insert(SKILLID_MAP::value_type( MAGIC_UN_TRANSFORM, SKILLID_NODE(MAGIC_UN_TRANSFORM, flag) ));
	}	
#endif
}

//----------------------------------------------------------------------
// Check MP
//----------------------------------------------------------------------
// 선택된 skill들의 MP를 보고
// 사용가능한지 아닌지를 체크한다.
//----------------------------------------------------------------------
void
MSkillSet::CheckMP()
{
#ifdef __GAME_CLIENT__
	
	// mp 체크할때.. 현재 장비중인 무기도 체크해야되는데
	// 일단은.. 이케 간다. T_T;
	SetAvailableSkills(); 

	/*
	if (g_pPlayer==NULL)
	{
		return;
	}

	//--------------------------------------------------
	// player의 현재 MP
	//--------------------------------------------------
	int playerMP;
	
	if (g_pPlayer->IsSlayer())
	{
		playerMP = g_pPlayer->GetMP();	
	}
	else
	{
		// vampire인 경우는 HP를 MP대신에 쓴다.
		playerMP = g_pPlayer->GetHP();	
	}

	SKILLID_MAP::iterator iID = begin();
	
	//--------------------------------------------------
	// 모든 skill들에 대해서 mp 체크
	//--------------------------------------------------
	while (iID != end())
	{
		ACTIONINFO		id = (*iID).first;
		SKILLID_NODE&	node = (*iID).second;	

		//--------------------------------------------------
		// MP사용량이 현재MP보다 큰 경우.. --> 사용 불가
		//--------------------------------------------------
		if ((*g_pSkillInfoTable)[id].GetMP() > playerMP)
		{
			node.SetDisable();
		}
		//--------------------------------------------------
		// 아니면, 사용 가능하게 표시
		//--------------------------------------------------
		else
		{
			node.SetEnable();
		}

		iID++;
	}
	*/
#endif
}

//----------------------------------------------------------------------
//
//							MSkillDomain
//
//----------------------------------------------------------------------

//----------------------------------------------------------------------
//
// constructor / destructor
//
//----------------------------------------------------------------------
MSkillDomain::MSkillDomain()
{
	m_bNewSkill			= false;

	m_MaxLevel			= 0;
	m_MaxLearnedLevel	= -1;
	m_pLearnedSkillID	= NULL;
	m_DomainLevel		= 0;
	m_DomainExpRemain	= 0;

	m_DomainExpTable.Init( 151 );
}

MSkillDomain::~MSkillDomain()
{
	if (m_pLearnedSkillID!=NULL)
	{
		delete [] m_pLearnedSkillID;
	}


	//---------------------------------------------------------
	// Skill Step map 지우기
	//---------------------------------------------------------
	SKILL_STEP_MAP::iterator iList = m_mapSkillStep.begin();

	while (iList != m_mapSkillStep.end())
	{
		SKILL_STEP_LIST* pList = iList->second;

		if (pList != NULL)
		{
			delete pList;
		}
		
		iList ++;
	}

	m_mapSkillStep.clear();
}

//----------------------------------------------------------------------
//
// member functions
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Set Max Level
//----------------------------------------------------------------------
// domain의 최고 level 기술
//----------------------------------------------------------------------
void		
MSkillDomain::SetMaxLevel()
{
	if (m_pLearnedSkillID!=NULL)
	{
		delete [] m_pLearnedSkillID;
	}

	m_pLearnedSkillID = new ACTIONINFO [m_MaxLevel+1];	// 0부터 시작한다.
	m_MaxLearnedLevel = -1;

	for (int i=0; i<=m_MaxLevel; i++)
	{
		m_pLearnedSkillID[i] = MAX_ACTIONINFO;//ACTIONINFO_NULL;
	}
}

//----------------------------------------------------------------------
// Clear
//----------------------------------------------------------------------
void			
MSkillDomain::Clear()
{ 
//	SKILLID_MAP::iterator	iSkill = m_mapSkillID.begin();
//	SKILLID_MAP::iterator	endItr = m_mapSkillID.end();
//
//	while (iSkill!=endItr)
//	{		
//		//-----------------------------------------------
//		// 현재 사용 가능한 Skill에서 제거한다.
//		//-----------------------------------------------
//		(*g_pSkillAvailable).RemoveSkill( (*iSkill).first );
//
//		iSkill++;
//	}
//
//	m_iterator = NULL; 
//	m_mapSkillID.clear();

	ClearSkillList();

	//-----------------------------------------------
	// 배운 level 제거
	//-----------------------------------------------
	if (m_pLearnedSkillID!=NULL)
	{
		delete [] m_pLearnedSkillID;
		
		m_MaxLevel = 0;
		m_MaxLearnedLevel = -1;	
		m_pLearnedSkillID = NULL;
	}
}

void			
MSkillDomain::ClearSkillList()
{ 
	SKILLID_MAP::iterator	iSkill = m_mapSkillID.begin();
	SKILLID_MAP::iterator	endItr = m_mapSkillID.end();

	while (iSkill!=endItr)
	{		
		//-----------------------------------------------
		// 현재 사용 가능한 Skill에서 제거한다.
		//-----------------------------------------------
		(*g_pSkillAvailable).RemoveSkill( (*iSkill).first );

		iSkill++;
	}

	m_iterator = m_mapSkillID.end(); 
	m_mapSkillID.clear();

	if(m_pLearnedSkillID != NULL)
	{
		delete [] m_pLearnedSkillID;
		m_pLearnedSkillID = NULL;
	}
}

//----------------------------------------------------------------------
// AddSkill
//----------------------------------------------------------------------
// id와 그의 하위에 있는 것들을 모두 추가한다.
// 단 id의 skill의 level은 0이어야 한다.
//----------------------------------------------------------------------
bool			
MSkillDomain::SetRootSkill(ACTIONINFO id, bool reset)
{
	//--------------------------------------------------
	// 다 지운다.
	//--------------------------------------------------
	//Clear();
	if(reset)
		m_DomainLevel		= 0;

	//--------------------------------------------------
	// level이 0인 skill이어야 한다.
	//--------------------------------------------------
//	if ((*g_pSkillInfoTable)[id].GetLevel()==0)
	{
		int oldMaxLevel = m_MaxLevel;

		if( reset )
			m_MaxLevel = 0;
		bool bOK = AddSkill( id );		
		
		if (oldMaxLevel > m_MaxLevel && reset)
		{
			m_MaxLevel = oldMaxLevel;
		}

		//--------------------------------------------------
		// 제대로 추가된 경우
		//--------------------------------------------------
		if (bOK)
		{
			//--------------------------------------------------
			// domain의 skill level을 설정해준다.
			//--------------------------------------------------
			SetMaxLevel();
		}
	}

	return false;
}

//----------------------------------------------------------------------
// AddSkill
//----------------------------------------------------------------------
// id와 그의 하위에 있는 것들을 모두 추가한다.
//----------------------------------------------------------------------
bool
MSkillDomain::AddSkill(ACTIONINFO id)
{
	SKILLID_MAP::iterator	iSkill;

	if(SKILL_ABERRATION == id)
		int a= 0;

	iSkill = m_mapSkillID.begin();

	while( iSkill != m_mapSkillID.end() )
	{
		if( iSkill->first == id )
		{
			break;
		}
		iSkill++;
	}
	int skillLevel = (*g_pSkillInfoTable)[id].GetLevel();

	//--------------------------------------------------
	// domain 최고 skill level을 찾는다.
	//--------------------------------------------------
	if (m_MaxLevel < skillLevel)
	{
		m_MaxLevel = skillLevel;
	}

	//-----------------------------------------------
	// 아직 없는 Skill이면 추가	
	//-----------------------------------------------
	if (iSkill == m_mapSkillID.end() )
	{		
		//-----------------------------------------------
		// root level이면 다음에 배울 수 있는 걸로 체크한다.
		//-----------------------------------------------
		if(id == SKILL_ABERRATION)
			int a =0 ;
		if (skillLevel==0)
		{
			m_mapSkillID.insert(SKILLID_MAP::value_type( id, SKILLSTATUS_NEXT ));
		}
		else
		{
			m_mapSkillID.insert(SKILLID_MAP::value_type( id, SKILLSTATUS_OTHER ));
		}	
		
		//-----------------------------------------------
		// 이 skill의 SkillStep에 관한 정보를 설정한다.
		//-----------------------------------------------

		SKILL_STEP skillStep = (*g_pSkillInfoTable)[id].GetSkillStep();
		if(skillStep == SKILL_STEP_ETC && id == SKILL_SOUL_CHAIN)
		{
#ifdef __GAME_CLIENT__ 
			if(this == &(*g_pSkillManager)[SKILL_DOMAIN_VAMPIRE])
				AddSkillStep(SKILL_STEP_VAMPIRE_INNATE, id);
			else if( this == &(*g_pSkillManager)[SKILL_DOMAIN_OUSTERS])
				AddSkillStep(SKILL_STEP_OUSTERS_ETC, id);
			else
				AddSkillStep(SKILL_STEP_APPRENTICE, id);
#endif
		}
		else
		{
			AddSkillStep(skillStep, id);
		}

		//--------------------------------------------------
		// 다음에 배울 수 있는 것들을 찾아서 추가한다.
		//--------------------------------------------------
		const SKILLINFO_NODE::SKILLID_LIST& listNextSkill = (*g_pSkillInfoTable)[id].GetNextSkillList();

		SKILLINFO_NODE::SKILLID_LIST::const_iterator iNextSkill = listNextSkill.begin();

		while (iNextSkill != listNextSkill.end())
		{
			//--------------------------------------------------
			// ID가 *iNextSkil인 Skill를 찾는다.
			//--------------------------------------------------
			iSkill = m_mapSkillID.find( *iNextSkill );

			//--------------------------------------------------
			// 아직 없는 경우에 추가한다.
			//--------------------------------------------------
			if (iSkill == m_mapSkillID.end())
			{
				AddSkill( *iNextSkill );
			}

			iNextSkill++;
		}

		return true;
	}

	//-----------------------------------------------
	// 이미 있는 Skill이면 false
	//-----------------------------------------------
	return false;
}


//----------------------------------------------------------------------
// Set SkillStatus
//----------------------------------------------------------------------
// skill의 상태를 변경한다.
//----------------------------------------------------------------------
/*
bool		
MSkillDomain::SetSkillStatus(ACTIONINFO id, SKILLSTATUS status)
{
	SKILLID_MAP::iterator	iSkill;

	iSkill = m_mapSkillID.find( id );
	
	//-----------------------------------------------
	// domain에 있는 Skill이면..
	//-----------------------------------------------
	if (iSkill != m_mapSkillID.end())
	{
		m_mapSkillID.insert(SKILLID_MAP::value_type( id, status ));

		switch (status)
		{
			case SKILLSTATUS_LEARNED :		// 배웠다.
				//-----------------------------------------------
				// 현재 사용 가능한 Skill에 추가한다.
				//-----------------------------------------------
				//(*g_pSkillAvailable).AddSkill( id );
				LearnSkill(id);
			break;

			case SKILLSTATUS_NEXT :				// 다음에 배울 수 있다.
			case SKILLSTATUS_OTHER :			// 아직은 배울 수 없다
				//-----------------------------------------------
				// 현재 사용 가능한 Skill에서 제거한다.
				//-----------------------------------------------
				(*g_pSkillAvailable).RemoveSkill( id );
			break;
		}

		return true;
	}

	//-----------------------------------------------
	// 이미 있는 Skill이면 false
	//-----------------------------------------------
	return false;
}
*/

//----------------------------------------------------------------------
// Get SkillStatus
//----------------------------------------------------------------------
// id의 상태는?
//----------------------------------------------------------------------
MSkillDomain::SKILLSTATUS		
MSkillDomain::GetSkillStatus(ACTIONINFO id) const
{
	SKILLID_MAP::const_iterator	iSkill;

	//--------------------------------------------------
	// ID가 id인 Skill를 찾는다.
	//--------------------------------------------------
	iSkill = m_mapSkillID.find(id);

	//--------------------------------------------------
	// 없을 경우 NULL을 return한다.
	//--------------------------------------------------
	if (iSkill == m_mapSkillID.end()) 
	{
		return SKILLSTATUS_NULL;
	}

	//--------------------------------------------------
	// 있으면 그 Skill를 return한다.
	//--------------------------------------------------
	return (*iSkill).second;
}

//----------------------------------------------------------------------
// Remove Skill
//----------------------------------------------------------------------
// mapSkill에서 제거하고 Skill의 pointer를 넘겨준다.
//----------------------------------------------------------------------
/*
bool
MSkillDomain::RemoveSkill(ACTIONINFO id)
{
	SKILLID_MAP::iterator	iSkill;

	//--------------------------------------------------
	// ID가 id인 Skill를 찾는다.
	//--------------------------------------------------
	iSkill = m_mapSkillID.find(id);
    
	//--------------------------------------------------
	// 그런 id를 가진 Skill이 없는 경우
	//--------------------------------------------------
	if (iSkill == m_mapSkillID.end())
	{
		return false;
	}

	//--------------------------------------------------
	// 찾은 경우 --> 제거	
	//--------------------------------------------------
	// map에서 제거
	m_mapSkillID.erase( iSkill );

	return true;
}
*/

//----------------------------------------------------------------------
// Add NextSkill
//----------------------------------------------------------------------
// 다음에 배울 수 있는 기술들을 체크한다.
//----------------------------------------------------------------------
void
MSkillDomain::AddNextSkill(ACTIONINFO id)
{
	const SKILLINFO_NODE::SKILLID_LIST& listNextSkill = (*g_pSkillInfoTable)[id].GetNextSkillList();

	SKILLINFO_NODE::SKILLID_LIST::const_iterator iNextSkill = listNextSkill.begin();

	while (iNextSkill != listNextSkill.end())
	{
		//--------------------------------------------------
		// ID가 *iNextSkil인 Skill를 찾는다.
		//--------------------------------------------------
		SKILLID_MAP::iterator iSkill = m_mapSkillID.find( *iNextSkill );

		//--------------------------------------------------
		// 있으면 그 Skill의 값을 바꾼다.
		//--------------------------------------------------
		// 물론, 현재 domain에 속해있는 경우에만 가능하고
		// 아직 배우지 않은 것일 경우에만 NEXT로 설정한다.
		//--------------------------------------------------
		if (iSkill != m_mapSkillID.end())
		{
			if ((*iSkill).second==SKILLSTATUS_OTHER)
			{						
				(*iSkill).second = SKILLSTATUS_NEXT;
			}
		}

		iNextSkill++;
	}
}
void
MSkillDomain::AddNextSkillForce(ACTIONINFO id)
{
	if (id==MAX_ACTIONINFO)
	{
		return;
	}
	bool HasChildSkill = false;

//	const SKILLINFO_NODE::SKILLID_LIST& listNextSkill = (*g_pSkillInfoTable)[id].GetNextSkillList();
//
//	SKILLINFO_NODE::SKILLID_LIST::const_iterator iNextSkill = listNextSkill.begin();
//
//	while (iNextSkill != listNextSkill.end())
//	{
//		//--------------------------------------------------
//		// ID가 *iNextSkil인 Skill를 찾는다.
//		//--------------------------------------------------
//		SKILLID_MAP::iterator iSkill = m_mapSkillID.find( *iNextSkill );
//
//		//--------------------------------------------------
//		// 있으면 그 Skill의 값을 바꾼다.
//		//--------------------------------------------------
//		// 물론, 현재 domain에 속해있는 경우에만 가능하고
//		// 아직 배우지 않은 것일 경우에만 NEXT로 설정한다.
//		//--------------------------------------------------
//		if (iSkill != m_mapSkillID.end())
//		{
//			if ((*iSkill).second==SKILLSTATUS_LEARNED)
//			{		
//				HasChildSkill = true; // 자기 밑에 딸린 스킬중에 배운스킬이 없어야 한다.
//			}
//		}
//
//		iNextSkill++;
//	}
	if(!HasChildSkill && (*g_pSkillInfoTable)[id].CanDelete)// 자기밑에 딸린 스킬이 없고 삭제 가능한 스킬이면
	{
		SKILLID_MAP::iterator	iSkill = m_mapSkillID.find( id );
		if (iSkill != m_mapSkillID.end())
		{
			if ((*iSkill).second==SKILLSTATUS_LEARNED)
			{						
				(*iSkill).second = SKILLSTATUS_NEXT;
			//	RemoveNextSkill(id);
			}

		}
	}
}

//----------------------------------------------------------------------
// Remove NextSkill
//----------------------------------------------------------------------
// 다음에 배울 수 있게 표시된 기술들을 제거한다.
//----------------------------------------------------------------------
void
MSkillDomain::RemoveNextSkill(ACTIONINFO id)
{
	if (id==MAX_ACTIONINFO)
	{
		return;
	}

	SKILLID_MAP::iterator iPreviousSkill = m_mapSkillID.find( id );

	// 바로 전에 배웠던 기술의 ID		
	ACTIONINFO previousID = (*iPreviousSkill).first;

	//--------------------------------------------------
	//
	// 다음에 배울 수 있는 것들을 찾아서 설정한다.
	//
	//--------------------------------------------------
	const SKILLINFO_NODE::SKILLID_LIST& listNextSkill = (*g_pSkillInfoTable)[previousID].GetNextSkillList();

	SKILLINFO_NODE::SKILLID_LIST::const_iterator iNextSkill = listNextSkill.begin();

	while (iNextSkill != listNextSkill.end())
	{
		//--------------------------------------------------
		// ID가 *iNextSkil인 Skill를 찾는다.
		//--------------------------------------------------
		SKILLID_MAP::iterator	iSkill = m_mapSkillID.find( *iNextSkill );

		//--------------------------------------------------
		// 있으면 그 Skill의 값을 바꾼다.
		//--------------------------------------------------
		// 물론, 현재 domain에 속해있는 경우에만 가능하고
		// NEXT이면 OTHER로 바꾼다.
		//--------------------------------------------------
		if (iSkill != m_mapSkillID.end())
		{
			if ((*iSkill).second==SKILLSTATUS_NEXT)
			{						
				(*iSkill).second = SKILLSTATUS_OTHER;
			}
		}

		iNextSkill++;
	}
}

//----------------------------------------------------------------------
// Learn Skill
//----------------------------------------------------------------------
// id의 skill을 Learn상태로 바꾼다.
// 다음에 배울 수 있는 skill들을 Next상태로 바꾼다.
//
// 같은 level의 기술은 하나밖에 배울 수 없다.
// 그렇게 되면, 현재 배울 수 있는 기술은 최고의 level인 기술이다. (m_MaxLevel)
//----------------------------------------------------------------------
bool
MSkillDomain::LearnSkill(ACTIONINFO id)
{
	//--------------------------------------------------
	// 새로운 기술을 배울 수 없으면..
	//--------------------------------------------------
	if (!m_bNewSkill)
	{
		return false;
	}


	//--------------------------------------------------
	// 이번에 배울 수 있는 level의 기술이 아니면 return
	//--------------------------------------------------
	if ((*g_pSkillInfoTable)[id].GetLevel()!=m_MaxLearnedLevel+1)
	{
	//	return false;
	}

	SKILLID_MAP::iterator	iSkill;

	//--------------------------------------------------
	// ID가 id인 Skill를 찾는다.
	//--------------------------------------------------
	iSkill = m_mapSkillID.find(id);

	//--------------------------------------------------
	// 없을 경우 NULL을 return한다.
	//--------------------------------------------------
	if (iSkill == m_mapSkillID.end()) 
	{
		return false;
	}

	//--------------------------------------------------
	// 이미 배운 것이면 return false
	//--------------------------------------------------
	if ((*iSkill).second==SKILLSTATUS_LEARNED)
	{
		return false;
	}

	
	//-----------------------------------------------
	// 현재 사용 가능한 Skill에 추가한다.
	//-----------------------------------------------
	(*g_pSkillAvailable).AddSkill( id );

	//-----------------------------------------------
	// 배운 기술 level 체크
	//-----------------------------------------------
	int skillLevel = (*g_pSkillInfoTable)[id].GetLevel();

	// 현재 level에서 배운 기술 설정
	m_pLearnedSkillID[skillLevel] = id;

	if (skillLevel > m_MaxLearnedLevel)
	{
		m_MaxLearnedLevel = skillLevel;

		//--------------------------------------------------
		//
		// 현재에 배울 수 있게 표시된 것들을 모두 없애준다.
		//
		//--------------------------------------------------
		// 바로 전 level의 하위 level
		//--------------------------------------------------
		//if (m_MaxLearnedLevel > 0)
		//{	
			///RemoveNextSkill( m_pLearnedSkillID[m_MaxLearnedLevel-1] );
		//}

		//--------------------------------------------------
		// 배울 수 있다고 표시된거 모두 제거
		//--------------------------------------------------
		SKILLID_MAP::iterator iSkill2 = m_mapSkillID.begin();

		while (iSkill2 != m_mapSkillID.end())
		{
			if ((*iSkill2).second==SKILLSTATUS_NEXT)
			{						
				(*iSkill2).second = SKILLSTATUS_OTHER;
			}

			iSkill2++;
		}

		//--------------------------------------------------
		// 배웠다고 체크한다.
		//--------------------------------------------------
		(*iSkill).second = SKILLSTATUS_LEARNED;	

		//--------------------------------------------------
		//
		// 다음에 배울 수 있는 것들을 찾아서 설정한다.
		//
		//--------------------------------------------------
		AddNextSkill( id );
	}	
	else
	{
		//--------------------------------------------------
		// 배웠다고 체크한다.
		//--------------------------------------------------
		(*iSkill).second = SKILLSTATUS_LEARNED;	
	}

	m_bNewSkill = false;

	return true;
}

//----------------------------------------------------------------------
// UnLearn Skill
//----------------------------------------------------------------------
// id의 skill을 안 배운 상태로 바꾼다.
//
// 제거된 것들 중에서 최고 level의 기술의
// 다음에 배울 수 있는 skill들을 Next상태로 바꾼다.
//
//----------------------------------------------------------------------
bool
MSkillDomain::UnLearnSkill(ACTIONINFO id)
{
	//--------------------------------------------------
	// 현재 최고 level의 기술만 제거할 수 있다.
	//--------------------------------------------------
	if ((*g_pSkillInfoTable)[id].GetLevel()!=m_MaxLearnedLevel)
	{
		return false;
	}

	SKILLID_MAP::iterator	iSkill;

	//--------------------------------------------------
	// ID가 id인 Skill를 찾는다.
	//--------------------------------------------------
	iSkill = m_mapSkillID.find(id);

	//--------------------------------------------------
	// 없을 경우 NULL을 return한다.
	//--------------------------------------------------
	if (iSkill == m_mapSkillID.end()) 
	{
		return false;
	}

	//--------------------------------------------------
	//
	// Skill의 값을 UnLearned로 바꾼다.
	//
	//--------------------------------------------------
	// 배운 것이면 아니면 return false
	if ((*iSkill).second!=SKILLSTATUS_LEARNED)
	{
		return false;
	}
	
	//--------------------------------------------------
	// 제거할려는 기술의 다음 기술들을 
	// 못 배우는 걸로 체 크한다.
	//--------------------------------------------------
	RemoveNextSkill( m_pLearnedSkillID[m_MaxLearnedLevel] );

	//--------------------------------------------------
	// 기술 level 없애주기
	//--------------------------------------------------
	m_pLearnedSkillID[m_MaxLearnedLevel] = MAX_ACTIONINFO;//ACTIONINFO_NULL;
	m_MaxLearnedLevel--;
	

	(*iSkill).second = SKILLSTATUS_OTHER;	// 실제로는 NEXTSKILL이지만..머..

	//-----------------------------------------------
	// 현재 사용 가능한 Skill에서 제거한다.
	//-----------------------------------------------
	(*g_pSkillAvailable).RemoveSkill( id );
	
	//--------------------------------------------------
	//
	// 다음에 배울 수 있는 것들을 찾아서 설정한다.
	//
	//--------------------------------------------------
	if (m_MaxLearnedLevel>=0)
	{
		AddNextSkill( m_pLearnedSkillID[m_MaxLearnedLevel] );
	}


	return true;
}


//----------------------------------------------------------------------
// Is Exist SkillStep
//----------------------------------------------------------------------
BOOL
MSkillDomain::IsExistSkillStep(SKILL_STEP ss) const
{
	SKILL_STEP_MAP::const_iterator iList = m_mapSkillStep.find( ss );

	if (iList == m_mapSkillStep.end())
	{
		return FALSE;
	}

	return TRUE;
}

//----------------------------------------------------------------------
// Get SkillStep List
//----------------------------------------------------------------------
const MSkillDomain::SKILL_STEP_LIST*	
MSkillDomain::GetSkillStepList(SKILL_STEP ss) const
{
	SKILL_STEP_MAP::const_iterator iList = m_mapSkillStep.find( ss );

	if (iList == m_mapSkillStep.end())
	{
		return NULL;
	}

	return iList->second;
}

//----------------------------------------------------------------------
// Add SkillStep List
//----------------------------------------------------------------------
void
MSkillDomain::AddSkillStep(SKILL_STEP ss, ACTIONINFO ai)
{
	SKILL_STEP_LIST* pList;
	SKILL_STEP_MAP::const_iterator iList = m_mapSkillStep.find( ss );

	if (iList == m_mapSkillStep.end())
	{
		// 없으면 new해서 추가한다.
		pList = new SKILL_STEP_LIST;
	}
	else
	{
		pList = iList->second;
	}

	// list에 ai추가
	SKILL_STEP_LIST list = *pList;
	bool bExist = false;
	for(int i=0;i<list.size();i++)
	{
		if( list[i] == ai )
		{			
			bExist = true;
			break;
		}
	}
	
	if(bExist == false)
//		pList->push_back( ai );	
	{
		
		if( pList->empty() )
		{
			pList->push_back( ai );
		} else
		{
			bool	bAdded = false;
			SKILL_STEP_LIST::iterator itr = pList->begin();
			SKILL_STEP_LIST::iterator endItr = pList->end();	
			int		LearnLevel = (*g_pSkillInfoTable)[ai].GetLearnLevel();
			while( itr != endItr )
			{
				int currentPositionLevel = (*g_pSkillInfoTable)[*itr].GetLearnLevel();
				
				if( currentPositionLevel > LearnLevel )
				{
					pList->insert( itr, ai );
					bAdded = true;
					break;
				}
				
				itr++;
			}
			if(bAdded == false )
			{
				pList->push_back( ai );
			}
		}
	}

	// (다시) 설정한다.
	m_mapSkillStep[ss] = pList;
}

//----------------------------------------------------------------------
// Save To File
//----------------------------------------------------------------------
// Skill ID를 File에 저장한다.
//----------------------------------------------------------------------
void		
MSkillDomain::SaveToFile(std::ofstream& file)
{
	SKILLID_MAP::iterator	iSkill = m_mapSkillID.begin();

	// size저장
	int size = m_mapSkillID.size();
	file.write((const char*)&size, 4);

	// 각 id저장
	while (iSkill != m_mapSkillID.end())
	{
		WORD id = (*iSkill).first;
		BYTE status = (*iSkill).second;

		file.write((const char*)&id, 2);
		file.write((const char*)&status, 1);

		iSkill++;
	}    
}

//----------------------------------------------------------------------
// Load From File
//----------------------------------------------------------------------
// Skill ID를 File에서 읽어온다.
//----------------------------------------------------------------------
void		
MSkillDomain::LoadFromFile(ivfstream& file)
{
	Clear();
	//m_mapSkillID.clear();
	
	// size읽어오기
	int size;
	file.read((char*)&size, 4);

	// 읽어와서 저장
	WORD id;
	BYTE status;
	for (int i=0; i<size; i++)
	{		
		file.read((char*)&id, 2);
		file.read((char*)&status, 1);

		m_mapSkillID.insert(SKILLID_MAP::value_type( 
										(enum ACTIONINFO)id, 
										(enum SKILLSTATUS)status ));
	} 
}

//----------------------------------------------------------------------
// LoadFromFileServerDomainInfo
//----------------------------------------------------------------------
void		
MSkillDomain::LoadFromFileServerDomainInfo(ivfstream& file)
{	
	int level;

	file.read((char*)&level, 4);

	// level에 맞춰서 loading..
	m_DomainExpTable[level].LoadFromFile( file );	
}

bool		
MSkillDomain::IsAvailableDeleteSkill(ACTIONINFO id)
{	
	const SKILLINFO_NODE::SKILLID_LIST& listNextSkill = (*g_pSkillInfoTable)[id].GetNextSkillList();

	SKILLINFO_NODE::SKILLID_LIST::const_iterator iNextSkill = listNextSkill.begin();

	while (iNextSkill != listNextSkill.end())
	{
		//--------------------------------------------------
		// ID가 *iNextSkil인 Skill를 찾는다.
		//--------------------------------------------------
		int TempSkillID = *iNextSkill;
		if(false == (*g_pSkillInfoTable)[*iNextSkill].CanDelete)
			return false;
		SKILLID_MAP::iterator iSkill = m_mapSkillID.find( *iNextSkill );

		if (iSkill != m_mapSkillID.end())
		{
			if ((*iSkill).second==SKILLSTATUS_LEARNED)
			{						
				return false;
			}
		}

		iNextSkill++;
	}
	return true;
}

//----------------------------------------------------------------------
// Get ExpInfo
//----------------------------------------------------------------------
const ExpInfo&	
MSkillDomain::GetExpInfo(int level) const
{
	return m_DomainExpTable[level];
}

//----------------------------------------------------------------------
//
// MSkillManager
//
//----------------------------------------------------------------------
MSkillManager::MSkillManager()
{
}

MSkillManager::~MSkillManager()
{
}

//----------------------------------------------------------------------
// Init
//----------------------------------------------------------------------
void
MSkillManager::Init()
{
	//--------------------------------------------------
	//
	// Skill Tree 초기화
	//
	//--------------------------------------------------
	CTypeTable<MSkillDomain>::Init( MAX_SKILLDOMAIN );
	//--------------------------------------------------
	// 기본 기술로부터 skill tree를 초기화한다.
	//--------------------------------------------------

	m_pTypeInfo[SKILLDOMAIN_BLADE].SetRootSkill( SKILL_SINGLE_BLOW );
	m_pTypeInfo[SKILLDOMAIN_SWORD].SetRootSkill( SKILL_DOUBLE_IMPACT );
	m_pTypeInfo[SKILLDOMAIN_GUN].SetRootSkill( SKILL_FAST_RELOAD );
	m_pTypeInfo[SKILLDOMAIN_ENCHANT].SetRootSkill( MAGIC_CREATE_HOLY_WATER );
	m_pTypeInfo[SKILLDOMAIN_HEAL].SetRootSkill( MAGIC_CURE_LIGHT_WOUNDS );
	m_pTypeInfo[SKILLDOMAIN_VAMPIRE].SetRootSkill( MAGIC_HIDE );
	m_pTypeInfo[SKILLDOMAIN_OUSTERS].SetRootSkill( SKILL_FLOURISH );
	m_pTypeInfo[SKILLDOMAIN_ETC].SetRootSkill( SKILL_SOUL_CHAIN );


	#ifdef __GAME_CLIENT__
		//------------------------------------------------
		// Server 정보를 loading한다.
		//------------------------------------------------
		ivfstream serverDomainInfoFile(g_pFileDef->getProperty("FILE_INFO_SKILL_DOMAIN_EXP").c_str(), std::ios_base::binary);
		if (!serverDomainInfoFile.is_open())
			return;

		LoadFromFileServerDomainInfo( serverDomainInfoFile );
		serverDomainInfoFile.close();
	#endif
}

void
MSkillManager::InitSkillList()
{
	for(int i = SKILLDOMAIN_BLADE; i < MAX_SKILLDOMAIN; i++ )
		m_pTypeInfo[i].ClearSkillList();

	m_pTypeInfo[SKILLDOMAIN_BLADE].SetRootSkill( SKILL_SINGLE_BLOW , false);
	m_pTypeInfo[SKILLDOMAIN_SWORD].SetRootSkill( SKILL_DOUBLE_IMPACT , false);
	m_pTypeInfo[SKILLDOMAIN_GUN].SetRootSkill( SKILL_FAST_RELOAD , false);
	m_pTypeInfo[SKILLDOMAIN_ENCHANT].SetRootSkill( MAGIC_CREATE_HOLY_WATER , false);
	m_pTypeInfo[SKILLDOMAIN_HEAL].SetRootSkill( MAGIC_CURE_LIGHT_WOUNDS , false);
	m_pTypeInfo[SKILLDOMAIN_VAMPIRE].SetRootSkill( MAGIC_HIDE , false);
	m_pTypeInfo[SKILLDOMAIN_OUSTERS].SetRootSkill( SKILL_FLOURISH , false);
	m_pTypeInfo[SKILLDOMAIN_ETC].SetRootSkill( SKILL_SOUL_CHAIN , false);
}



//----------------------------------------------------------------------
// LoadFromFileServerSkillInfo
//----------------------------------------------------------------------
void		
MSkillManager::LoadFromFileServerDomainInfo(ivfstream& file)
{
	int num, domain;

	file.read((char*)&num, 4);

	// 개수만큼..
	for (int i=0; i<num; i++)
	{		
		file.read((char*)&domain, 4);

		// domain에 맞춰서 loading한다.
		m_pTypeInfo[domain].LoadFromFileServerDomainInfo( file );
	}
}

