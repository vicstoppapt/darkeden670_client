//----------------------------------------------------------------------
// MServerItemTable.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MCreatureTable.h"
#include "MServerCreatureTable.h"
#include <fstream>

//----------------------------------------------------------------------
//
// SERVER_CREATURETABLE_INFO
//
//----------------------------------------------------------------------
SERVER_CREATURETABLE_INFO::SERVER_CREATURETABLE_INFO()
{
}

SERVER_CREATURETABLE_INFO::~SERVER_CREATURETABLE_INFO()
{
}

//----------------------------------------------------------------------
// Save To File
//----------------------------------------------------------------------
void			
SERVER_CREATURETABLE_INFO::SaveToFile(std::ofstream& file)
{
	file.write((const char*)&Type, 4);
	file.write((const char*)&Level, 4);
}

//----------------------------------------------------------------------
// Load To File
//----------------------------------------------------------------------
void			
SERVER_CREATURETABLE_INFO::LoadFromFile(ivfstream& file)
{
	file.read((char*)&Type, 4);
	file.read((char*)&Level, 4);
}

//----------------------------------------------------------------------
//
// SERVER_CREATURECLASS_TABLE
//
//----------------------------------------------------------------------
SERVER_CREATURECLASS_TABLE::SERVER_CREATURECLASS_TABLE()
{
}

SERVER_CREATURECLASS_TABLE::~SERVER_CREATURECLASS_TABLE()
{
}


//----------------------------------------------------------------------
// Affect To ItemTable
//----------------------------------------------------------------------
// client의 item table에 필요한 정보를 저장시킨다.
//
// return값이 -1이면 제대로 된 경우이고
//				-2이면 itemClass의 개수가 틀린 경우
//				아니라면... 오류가 있는 itemClass의 ID이다.
//----------------------------------------------------------------------
int		
SERVER_CREATURECLASS_TABLE::AffectToCreatureTable( CREATURE_TABLE& creatureTable )
{
	//---------------------------------------------------
	// 전체class의 size 체크
	//---------------------------------------------------
	int clientClassSize = creatureTable.GetSize();
	int serverClassSize = GetSize();

	//---------------------------------------------------
	// 양쪽 size가 모두 같은 경우에 
	// 필요한 data들 설정한다.
	//---------------------------------------------------
	for(int cc = 0; cc < clientClassSize; cc++)
	{	
		CREATURETABLE_INFO&	clientInfo = creatureTable[cc];

		int findServerIdx = -1;

		for(int sc = 0; sc < serverClassSize; sc++)
		{
			SERVER_CREATURETABLE_INFO&	serverInfo = m_pTypeInfo[sc];

			if(cc == serverInfo.Type)
			{
				findServerIdx = sc;
				break;
			}
		}

		if(findServerIdx != -1)
		{
			clientInfo.Level = m_pTypeInfo[findServerIdx].Level;
		}
		else
		{
			clientInfo.Level = -1;
		}
	}

	return -1;
}
