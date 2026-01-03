//---------------------------------------------------------------------------------
// RankBonusTable.h
//---------------------------------------------------------------------------------
// 이미 화일이 존재하고.. 거기서 읽어온다고 가정했기 때문에.. 
// save함수는 없당..
//---------------------------------------------------------------------------------

#ifndef __SERVERRANKBONUSTABLE_H__
#define __SERVERRANKBONUSTABLE_H__

#include "CTypeTable.h"
#include "MString.h"
std::ifstream;
class RankBonusTable;

//---------------------------------------------------------------------------------
// RankBonus Info
//---------------------------------------------------------------------------------
class ServerRankBonusInfo {
	public :
		const int	GetType() const			{ return m_type; }
		const char *GetName() const			{ return m_Name.GetString(); }
		const int	GetLevel() const		{ return m_level; }
		const int	GetPoint() const		{ return m_point; }
		const bool	IsSlayerSkill() const	{ return (m_race == 0); }
		const bool	IsVampireSkill() const	{ return (m_race == 1); }
		const int	GetRace() const			{ return m_race; }


	public :
		void				LoadFromFile(ivfstream& file);		

	private:
		int m_type;
		MString m_Name;
		int m_level;
		int m_race;	// 0 : Slayer  1 : Vampire 2 : Ousters
		int m_point;
		
};

//---------------------------------------------------------------------------------
// RankBonus Table
//---------------------------------------------------------------------------------
class ServerRankBonusTable:public CTypeTable<ServerRankBonusInfo>
{
public:
	int AffectToClient(RankBonusTable &rankBonusTable);
};

#endif
