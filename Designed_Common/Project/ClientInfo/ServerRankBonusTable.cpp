//---------------------------------------------------------------------------------
// ServerRankBonusTable.cpp
//---------------------------------------------------------------------------------
#include "RankBonusTable.h"
#include "ServerRankBonusTable.h"
#include <fstream>

//---------------------------------------------------------------------------------
//
//					StatusInfo
//
//---------------------------------------------------------------------------------
void				
ServerRankBonusInfo::LoadFromFile(ivfstream& file)
{
	file.read((char*)&m_type, 4);
	m_Name.LoadFromFile(file);
	file.read((char*)&m_level, 4);
	file.read((char*)&m_race, 4);
	file.read((char*)&m_point, 4);
}

#include "stdio.h"
//				-1이면 정상
//				-2이면 itemClass의 개수가 틀린 경우
int
ServerRankBonusTable::AffectToClient(RankBonusTable &rankBonusTable)
{
	int count = GetSize();

	if(count != rankBonusTable.GetSize())
		return -1;

	FILE *fp;
	fp = fopen("RankBonus.txt", "wt");

	fprintf(fp, "RankBonusTable::RankBonusTable()\n{\n");
	fprintf(fp, "	Init(36);\n\n");
	fprintf(fp, "/////////////////////////////////////////////\n");
	fprintf(fp, "// Slayer Rank Bonus Skill\n");
	fprintf(fp, "/////////////////////////////////////////////\n\n");
	
	bool bVampire = false;
	for(int i = 0; i < count; i++)
	{
		rankBonusTable[i].SetType(Get(i).GetType());
		rankBonusTable[i].SetName(Get(i).GetName());
		rankBonusTable[i].SetLevel(Get(i).GetLevel());
		rankBonusTable[i].SetRace((Race)Get(i).GetRace());
		rankBonusTable[i].SetPoint(Get(i).GetPoint());

		if(bVampire == false && rankBonusTable[i].IsVampireSkill())
		{
			fprintf(fp, "\n/////////////////////////////////////////////\n");
			fprintf(fp, "// Vampire Rank Bonus Skill\n");
			fprintf(fp, "/////////////////////////////////////////////\n\n");
			bVampire = true;
		}

		fprintf(fp, "	// %d %s Level : %d race : %s\n	Get(%d).SetSkillIconID(%d);\n\n", rankBonusTable[i].GetType(), rankBonusTable[i].GetName(), rankBonusTable[i].GetLevel(), rankBonusTable[i].IsVampireSkill()?"Vampire":"Slayer", i, rankBonusTable[i].GetSkillIconID());
	}

	fprintf(fp, "}\n");

	fclose(fp);
	
	return -2;
}
