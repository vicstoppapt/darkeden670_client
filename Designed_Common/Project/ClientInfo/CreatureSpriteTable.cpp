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
#include "packet/Properties.h"
#include "MMinMaxInfo.h"

#include "MItem.h"

#include "Packet\types\PacketItemDef.h"
#include "MathTable.h"

//#ifdef OUTPUT_DEBUG
	#define SAVE_TO_FILE
//#endif

#define		FILE_INFO_SERVER_RANK_BONUS	"Data\\ServerRankBonus.inf"
#define		FILE_INFO_SERVER_ITEM		"Data\\ServerItemInfo.inf"
#define		FILE_INFO_SERVER_NPC		"Data\\ServerNPC.inf"

#define		FILE_INFO_CHAT_CURSE		"Data\\yok.txt"
#define		FILE_INFO_CHAT_CURSE_2		"Data\\yok2.txt"// 캐릭터 이름에서만 필터링 될 것들

#define		FILE_INFO_CHAT_CURSE_NET		"Data\\yok_net.txt"
#define		FILE_INFO_CHAT_CURSE_NET_2		"Data\\yok2_net.txt"

#define		COLOR_CHIEF_MAGE			44
#define		COLOR_CHIEF_FIGHT			120
#define		COLOR_CHIEF_MAGE_FIGHT		485

#define		SCOPE_BLOCK

HRESULT InitFail(LPCTSTR szError,...);
bool 
FileOpenBinary(const char* filename, ivfstream& file);
//---------------------------------------------------------------------------
// Open File
//---------------------------------------------------------------------------
bool 
FileCheck(const char* filename);


BOOL	InitCreatureSpriteTable()
{
	//---------------------------------------------------------------------
	//
	//    CreatureSpriteTable에 대한 정보 설정
	//
	//---------------------------------------------------------------------	
#ifdef SAVE_TO_FILE
	ivfstream creatureIndexFile(g_pFileDef->getProperty("FILE_ISPRITEINDEX_CREATURE").c_str(), std::ios::binary);
	ivfstream creatureShadowIndexFile(g_pFileDef->getProperty("FILE_SSPRITEINDEX_CREATURE").c_str(), std::ios::binary);
	ivfstream mmiFile("Data\\Creature.mmi", std::ios::binary);
	ivfstream mmiFile2("Data\\CreatureShadow.mmi", std::ios::binary);

	ivfstream creatureIndexFileSecond(g_pFileDef->getProperty("FILE_ISPRITEINDEX_CREATURE2").c_str(), std::ios::binary);
	ivfstream creatureShadowIndexFileSecond(g_pFileDef->getProperty("FILE_SSPRITEINDEX_CREATURE2").c_str(), std::ios::binary);
	ivfstream mmiFileSecond("Data\\Creature2.mmi", std::ios::binary);
	ivfstream mmiFileSecond2("Data\\CreatureShadow2.mmi", std::ios::binary);

	CFileIndexTable	indexTable;
	CFileIndexTable	indexTableShadow;
	
	CFileIndexTable	indexTableSecond;
	CFileIndexTable	indexTableShadowSecond;

	MMinMaxInfoTable	mmiTable;
	MMinMaxInfoTable	mmiTable2;	// 그림자 체크용

	MMinMaxInfoTable	mmiTableSecond;
	MMinMaxInfoTable	mmiTableSecond2;	// 그림자 체크용

	
	indexTable.LoadFromFile(creatureIndexFile);// Creature IndexSprite IndexFile
	indexTableShadow.LoadFromFile(creatureShadowIndexFile);	// Creature ShadowSprite IndexFile

	indexTableSecond.LoadFromFile(creatureIndexFileSecond);// Creature IndexSprite IndexFile2
	indexTableShadowSecond.LoadFromFile(creatureShadowIndexFileSecond);	// Creature ShadowSprite IndexFile2

	// Creature IndexSprite Min/Max Info
	mmiTable.LoadFromFile(mmiFile);
	mmiTable2.LoadFromFile(mmiFile2);
	
	// Creature2 IndexSprite Min/Max Info
	mmiTableSecond.LoadFromFile(mmiFileSecond);
	mmiTableSecond2.LoadFromFile(mmiFileSecond2);

	creatureIndexFile.close();
	creatureShadowIndexFile.close();
	creatureIndexFileSecond.close();
	creatureShadowIndexFileSecond.close();
	mmiFile.close();
	mmiFile2.close();
	mmiFileSecond.close();
	mmiFileSecond2.close();

	if (mmiTable.GetSize()!=mmiTable2.GetSize())
	{
		InitFail("Wrong MMI Table Size: %d != %d", mmiTable.GetSize(), mmiTable2.GetSize());

		return FALSE;
	}

	for (int m=0; m<mmiTable.GetSize(); m++)
	{
		if (mmiTable[m]!=mmiTable2[m])
		{
			//InitFail("Wrong MMI Size: [%d] (%d ~ %d) != (%d ~ %d)", m, mmiTable[m].Min, mmiTable[m].Max, mmiTable2[m].Min, mmiTable2[m].Max);

			//return FALSE;
		}
	}
	for (int m2=0; m2<mmiTableSecond.GetSize(); m2++)
	{
		if (mmiTableSecond[m2]!=mmiTableSecond2[m2])
		{
		}
	}

	/*
	// 2 = slayers : 기존의 ID랑 맞추기 위해서..
	int maxCreatures = 2 + 71;
	int maxCreatureSprites = maxCreatures * ACTION_MAX_VAMPIRE;

	g_pCreatureSpriteTable->Init( maxCreatureSprites );

	int min1, min2, max1, max2;
	long fp1, fp2;
			
	for (int CreatureIndex=0; CreatureIndex<maxCreatures; CreatureIndex++)
	{
		for (int a=0; a<ACTION_MAX_VAMPIRE; a++)
		{
			int i = CreatureIndex*ACTION_MAX_VAMPIRE + a;
			
			if (CreatureIndex >= 2)
			{
				int im = (CreatureIndex-2)*ACTION_MAX_VAMPIRE + a;

				min1 = mmiTable[im].Min;
				max1 = mmiTable[im].Max;
				min2 = mmiTable2[im].Min;
				max2 = mmiTable2[im].Max;
				fp1 = indexTable[min1];
				fp2 = indexTableShadow[min2];
			}
			else
			{
				min1 = max1 = min2 = max2 = SPRITEID_NULL;
				fp1 = fp2 = 0;
			}

			(*g_pCreatureSpriteTable)[i].FrameID				= CreatureIndex;
			(*g_pCreatureSpriteTable)[i].FirstSpriteID			= min1;
			(*g_pCreatureSpriteTable)[i].LastSpriteID			= max1;
			(*g_pCreatureSpriteTable)[i].FirstShadowSpriteID	= min2;
			(*g_pCreatureSpriteTable)[i].LastShadowSpriteID		= max2;
			(*g_pCreatureSpriteTable)[i].SpriteFilePosition		= fp1;
			(*g_pCreatureSpriteTable)[i].SpriteShadowFilePosition	= fp2;
		}
	}
	*/
	(*g_pCreatureSpriteTable).Init( 304
//#if __CONTENTS(__MENEGROTH)
//		+11
//#endif
//#if __CONTENTS(__SECOND_RARE_SKILL)
//		+1
//#endif //__SECOND_RARE_SKILL
//#if __CONTENTS(__FAST_TRANSFORTER)
//		+1
//#endif //__FAST_TRANSFORTER
//#if __CONTENTS(__SECOND_TRANSFORTER)
//		+1
//#endif //__SECOND_TRANSFORTER
//#if __CONTENTS(__TIPOJYU_CASTLE)	//티포쥬 몬스터 추가
//		+9
//#endif // __TIPOJYU_CASTLE
//#if __CONTENTS(__NEW_PET_FIRE_ELEMENTAL)
//		+1
//#endif //__NEW_PET_FIRE_ELEMENTAL
//#if __CONTENTS(__NEW_PET_INCUBUS)
//		+1
//#endif //__NEW_PET_INCUBUS
		);

	int index = 0;
	int mmiIndex = 0;
	//---------------------------------------------------------------------
	// [0]Slayer 남
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID					= FRAMEID_NULL;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID			= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition			= 0;//indexTable[(*g_pCreatureSpriteTable)[0].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType				= FLAG_CREATURESPRITE_PLAYER_SLAYER;
	index++;

	//---------------------------------------------------------------------
	// [1]Slayer 여
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID					= FRAMEID_NULL;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID			= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition			= 0;
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType				= FLAG_CREATURESPRITE_PLAYER_SLAYER;
	index++;

	//---------------------------------------------------------------------
	// [2]PC Vamp남 1차 의상
	//---------------------------------------------------------------------
	/*
	(*g_pCreatureSpriteTable)[index].FrameID			= 0;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	*/
	(*g_pCreatureSpriteTable)[index].FrameID					= 2;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID			= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition			= 0;
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType				= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [3]PC Vamp여 1차 의상
	//---------------------------------------------------------------------
	/*
	(*g_pCreatureSpriteTable)[index].FrameID			= 1;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	*/
	(*g_pCreatureSpriteTable)[index].FrameID					= 3;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID			= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition			= 0;
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType				= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	index++;
	mmiIndex++;
	
	//---------------------------------------------------------------------
	// [4]솔져
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 2;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;
	
	//---------------------------------------------------------------------
	// [5]데드바디
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 3;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;
	
	//---------------------------------------------------------------------
	// [6]키드
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 4;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [7]터닝소울
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 5;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [8]터닝데드
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 6;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [9]캡틴
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 7;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [10]드레이크
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 8;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [11]스파르탄
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 9;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [12]싱
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 10;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [13]여와 
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 11;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [14]쟌
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 12;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [15]쟈크
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 13;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [16]카이저
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 14;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [17]카인
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 15;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [18]칼
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 16;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [19]케빈
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 17;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [20]크리스
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 18;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [21]크리스틴
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 19;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [22]크라이프
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 20;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [23]한
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 21;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [24]한니발
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 22;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [25]타냐
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 23;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [26]데이비드
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 24;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [27]블러드 워록
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 25;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [28]그루버
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 26;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [29]그리픈
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 27;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [30]발레리
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 28;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [31]산드라
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 29;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [32]살라맨더
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 30;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [33]소냐
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 31;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [34]요시하라
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 32;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [35]요한
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 33;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [36]크로우
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 34;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [37]브리콜라카스
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 35;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [38]카파티니
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 36;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [39]스미스
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 37;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [40]골레머
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 38;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [41]더티스트라이더
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 39;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [42]알칸
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 40;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [43]레드아이
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 41;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [44]스마이로비치
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 42;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [45]잭
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 43;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [46]하스브로
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 44;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;
	
	//---------------------------------------------------------------------
	// [47]카오스 가디언
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 45;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [48]호블
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 46;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;	

	
	//---------------------------------------------------------------------
	// [49]니콜라이
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 47;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [50]라흐마노프
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 48;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;


	//---------------------------------------------------------------------
	// [51]리차드슨
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 49;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [52]샤모르
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 50;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [53]스토야노프
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 51;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	
	//---------------------------------------------------------------------
	// [54]예브게니
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 52;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [55]코난
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 53;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [56]프레드릭
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 54;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [57]섀도우윙
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 55;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [58]박쥐
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 56;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_PLAYER_VAMPIRE | FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [59]늑대
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 57;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_PLAYER_VAMPIRE | FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [60]뮤턴트
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 58;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [61]위도우즈
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 59;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [62]에스트로이더
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 60;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [63]에르체바토리
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 61;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [64]모데라스
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 62;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [65]쎄쓰
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 63;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [66]카콘
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 64;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [67]반델라이져
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 65;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [68]빅팽
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 66;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [69]아이언티쓰
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 67;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [70]다크스크리머
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 68;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [71]카오스나이트
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 69;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [72]크림슨슬로터
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 70;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [73]로드다크니스
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 71;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [74]리퍼
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 72;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [75]헬가디언
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 73;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [76]헬위자드
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 74;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [77]연변늑대
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 75;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [78]연변산타
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 76;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [79]에르체바토리 - 동작 있는거
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 77;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [80]아그네
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 78;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [81]아이만
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 79;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [82]카임
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 80;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [83]프리야
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 81;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [84]블라드 테페즈
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 82;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [85]운영자
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 83;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_PLAYER_ALL;
	index++;
	mmiIndex++;
	
	//---------------------------------------------------------------------
	// [86]슬레이어 성물보관대
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 84;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [87]뱀파이어 성물보관대
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 85;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;

	
	//---------------------------------------------------------------------
	// [88]다크가디언
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 86;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [89]로드카오스
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 87;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [90]카오스그리드
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 88;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [91]헬핀드
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 89;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [92]darkhaze
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 90;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;
	
	//---------------------------------------------------------------------
	// [93]그리피스
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 91;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [94]로빈벡스터
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 92;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [95]머피
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 93;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [96]카르멘버만
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 94;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [97]바토리2
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 95;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [98]바토리
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 96;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [99]테페즈
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 97;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [100]테페즈 관
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 98;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [101]던 울프아크
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 99;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [102]멈 린몬
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 100;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [103]샤먼 오프
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 101;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [104]크리스마스 트리
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 102;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [105]다크베리트
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 103;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [106]리치젤
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 104;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [107]마운트크래그
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 105;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [108]자이언트오스
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 106;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [109]PC Vamp남 2차 의상
	//---------------------------------------------------------------------
	/*
	(*g_pCreatureSpriteTable)[index].FrameID			= 107;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	*/
	(*g_pCreatureSpriteTable)[index].FrameID					= 4;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID			= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition			= 0;
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType				= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [110]PC Vamp남 무기
	//---------------------------------------------------------------------
	/*
	(*g_pCreatureSpriteTable)[index].FrameID			= 108;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	*/
	(*g_pCreatureSpriteTable)[index].FrameID					= 10;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID			= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition			= 0;
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType				= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [111]PC Vamp여 2차 의상
	//---------------------------------------------------------------------
	/*
	(*g_pCreatureSpriteTable)[index].FrameID			= 109;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	*/
	(*g_pCreatureSpriteTable)[index].FrameID					= 5;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID			= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition			= 0;
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType				= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	index++;
	mmiIndex++;
	
	//---------------------------------------------------------------------
	// [112]PC Vamp여 무기
	//---------------------------------------------------------------------
	/*
	(*g_pCreatureSpriteTable)[index].FrameID			= 110;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	*/
	(*g_pCreatureSpriteTable)[index].FrameID					= 11;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID			= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition			= 0;
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType				= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [113] 마리
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 111;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [114] 몰록
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 112;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [115] 베아트릭스
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 113;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [116] 아일린플로렌스
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 114;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [117] 아미
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 115;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [118] 알렌카를레스
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 116;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [119] 주디스엠마
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 117;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [120] 프레드릭헤드
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 118;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;
	

	//---------------------------------------------------------------------
	// [121] 파비안 시모네 주니어
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 119;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	
	//---------------------------------------------------------------------
	// [122] 브렌다 조아킴
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 120;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	
	//---------------------------------------------------------------------
	// [123] 수호성단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 121;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [124] 성지성단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 122;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [125] 옥타부스의 흑표범 
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 123;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [126] 셉티무스의 붉은 소
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 124;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [127] 테르티우스의 용
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 125;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;

	
	//---------------------------------------------------------------------
	// [128] 쿠아르투스 성의 불사조
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 126;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [129]PC Vamp남 3차 의상
	//---------------------------------------------------------------------
	/*
	(*g_pCreatureSpriteTable)[index].FrameID			= 127;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	*/
	(*g_pCreatureSpriteTable)[index].FrameID					= 6;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID			= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition			= 0;
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType				= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [130]PC Vamp여 3차 의상
	//---------------------------------------------------------------------
	/*
	(*g_pCreatureSpriteTable)[index].FrameID			= 128;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	*/
	(*g_pCreatureSpriteTable)[index].FrameID					= 7;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID			= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition			= 0;
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType				= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [131]PC Vamp남 - 뱀파이어 실험체
	//---------------------------------------------------------------------
	/*
	(*g_pCreatureSpriteTable)[index].FrameID			= 129;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	*/
	(*g_pCreatureSpriteTable)[index].FrameID					= 4;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID			= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition			= 0;
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType				= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [132] 딤가고일
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 130;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [133] 볼바메두사
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 131;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [134] 에쉬발록
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 132;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [135] 커피숍여주인
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 133;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [136] 양아치
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 134;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [137] 생선가게 주인
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 135;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [138] 할머니
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 136;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [139] 아마타
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 137;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_OUSTERS;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [140] 리파티
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 138;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [141] 게시판
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 139;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [142]Ousters
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= FRAMEID_NULL;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= 0;//indexTable[(*g_pCreatureSpriteTable)[0].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_PLAYER_OUSTERS;
	index++;
//	mmiIndex++;
	
	//---------------------------------------------------------------------
	// [143]라비니아
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 140;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_OUSTERS;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [144]리파티
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 141;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_OUSTERS;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [145]마네스코
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 142;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_OUSTERS;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [146]시오람
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 143;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_OUSTERS;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [147]아마타
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 144;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_OUSTERS;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [148]호라
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 145;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_OUSTERS;
	index++;
	mmiIndex++;
	
	//---------------------------------------------------------------------
	// [149]대지정령의뿔
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 146;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_OUSTERS;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [150]오레
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 147;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [151]깃발받침
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 148;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;
	
	//---------------------------------------------------------------------
	// [152]깃발받침
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 149;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [153]레벨별 전쟁 스위퍼 보관대
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 150;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [154] 리젠 타워 
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 151;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [155] 아우스터즈 NPC 정지
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 152;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_OUSTERS;
	index++;
	mmiIndex++;
	
	//---------------------------------------------------------------------
	// [156] 아우스터즈 NPC 마법
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 153;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_OUSTERS;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [157] 리프리
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 154;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_OUSTERS;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [158] 엘루니아
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 155;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_OUSTERS;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [159] 이그니엄
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 156;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_OUSTERS;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [160] 나이샤스
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 157;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_OUSTERS;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [161] 니트리샤
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 158;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_OUSTERS;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [162] 로와
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 159;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_OUSTERS;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [163] 공통펫 몬스터
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 160;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [164] 공통펫 1,2단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 161;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [165] 공통펫 3단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 162;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [166] 공통펫 4단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 163;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [167] 공통펫 5단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 164;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [168] 공통펫 6단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 165;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [169] 페키지펫 1,2단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 166;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [170] 페키지펫 3단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 167;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [171] 페키지펫 4단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 168;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [172] 페키지펫 5단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 169;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [173] 페키지펫 6단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 170;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [174] 대지정령
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 171;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [175] 정령
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= FRAMEID_NULL;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= 0;//indexTable[(*g_pCreatureSpriteTable)[0].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;

	//---------------------------------------------------------------------
	// [176] 슬레펫 1,2단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 172;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	
	
	//---------------------------------------------------------------------
	// [177] 슬레펫 3단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 173;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [178] 슬레펫 4단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 174;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	
	
	//---------------------------------------------------------------------
	// [179] 슬레펫 5단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 175;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	
	
	//---------------------------------------------------------------------
	// [180] 슬레펫 6단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 176;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	
	
	//---------------------------------------------------------------------
	// [181] 뱀파이어 펫 1,2단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 177;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [182] 뱀파이어 펫 3단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 178;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [183] 뱀파이어 펫 4단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 179;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [184] 뱀파이어 펫 5단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 180;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [185] 뱀파이어 펫 6단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 181;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [186] 아우스터스 펫 1,2단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 182;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [187] 아우스터스 펫 3단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 183;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [188] 아우스터스 펫 4단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 184;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [189] 아우스터스 펫 5단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 185;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	


	//---------------------------------------------------------------------
	// [190] 아우스터스 펫 6단
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 186;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	
	// 2004, 6, 5 sobeit add start
	//---------------------------------------------------------------------
	// [191] 716 질드레 유령 1
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= FRAMEID_NULL;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= 0;//indexTable[(*g_pCreatureSpriteTable)[0].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++; 
	// 2004, 6, 5 sobeit add end
	//---------------------------------------------------------------------
	// [192] 블런트트래그
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 187;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	
	//---------------------------------------------------------------------
	// [193] 뮤턴트엣져
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 188;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	
	//---------------------------------------------------------------------
	// [194] 본가디언
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 189;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	
	//---------------------------------------------------------------------
	// [195] 질드레 얼음 석상
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 190;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	
	//---------------------------------------------------------------------
	// [196] 성문1
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 191;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	
	//---------------------------------------------------------------------
	// [197] 성문2
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 192;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	
	//---------------------------------------------------------------------
	// [198] 성문3
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 193;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	
	//---------------------------------------------------------------------
	// [199] 성문4
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 194;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	
	
	//---------------------------------------------------------------------
	// [200] 질드레
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 195;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [201] 체크 포인트1
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 196;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [202] 체크 포인트2
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 197;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [203] 수정 질드레
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 198;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [204] 질드레
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 199;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [205] 다크베리트디펜더
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 200;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [206] 길드타워
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 201;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [207] Pleasure Station
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 202;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [208] Land mine
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 203;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [209] Craymore
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 204;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [210] Auto turret
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 205;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [211] Install Turret
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 206;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [212] Craymore - 수정
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 207;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [213] 드럼통
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 208;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [214] 삼각대a타입
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 209;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [215] 삼각대b타입
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 210;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [216] 삼각대c타입
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 211;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [217] 장애물a타입
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 212;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [218] 장애물b타입
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 213;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	
	
	//---------------------------------------------------------------------
	// [219] 서먼고어그랜드
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 214;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [220] 아이르 리피언 몸 
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 215;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [221] 아이르 리피언 몸 
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 216;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [222] 아이르 리피언 몸 
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 217;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

		//---------------------------------------------------------------------
	// [223] 아이르 리피언 몸 
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 218;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

		//---------------------------------------------------------------------
	// [224] 아이르 리피언 몸 
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 219;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

		//---------------------------------------------------------------------
	// [225] 아이르 리피언 몸 
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 220;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [226] 아이르 리피언 몸 
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 221;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [227] 인스톨 터렛 수정
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 222;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [228] 그레이트러피언1차
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 223;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [229] 그레이트러피언2차
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 224;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	
	
	//---------------------------------------------------------------------
	// [230] 플라즈마로켓런쳐
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 225;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	
	
	//---------------------------------------------------------------------
	// [231] 플라즈마로켓런쳐 수정
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 226;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	
	
	//---------------------------------------------------------------------
	// [232] 폭탄병
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 227;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [233] 박격포병
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 228;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [234] 반란군1
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 229;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [235] 반란군2
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 230;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [236] 반란군3
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 231;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [237] 반란군4
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 232;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [238] 레이저
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 233;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	
	
	//---------------------------------------------------------------------
	// [239] 뚱땡이
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 234;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [240] 터그렉(골룸)
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 235;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [241] 로이카다브루(철퇴인간)
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 236;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [242] 시아메스(쌍둥이)
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 237;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [243] 룽가테스타(신체변이)
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 238;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [244] 소총병
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 239;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [245] 자동소총병
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 240;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [246] 장교
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 241;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	
	
	//---------------------------------------------------------------------
	// [247] 이성의 봉인
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 242;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	
	
	//---------------------------------------------------------------------
	// [248] 펠트베벨 몸   SJHEON	2005.04.19 ADD
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 243;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	


	//---------------------------------------------------------------------
	// [249] 라클 (Rakel)	SJHEON	2005.04.19 ADD
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 244;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [250] 펠트베벨 발칸   SJHEON	2005.04.19 ADD
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 245;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	


	//---------------------------------------------------------------------
	// [251] 펠트베벨 토우 SJHEON	2005.04.19 ADD
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 246;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;

	
	//---------------------------------------------------------------------
	// [252] PC Vamp남 4차 의상
	//---------------------------------------------------------------------
	/*
	(*g_pCreatureSpriteTable)[index].FrameID			= 247;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	*/
	(*g_pCreatureSpriteTable)[index].FrameID					= 8;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID			= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition			= 0;
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType				= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [253] PC Vamp여 4차 의상
	//---------------------------------------------------------------------
	/*
	(*g_pCreatureSpriteTable)[index].FrameID			= 248;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	*/
	(*g_pCreatureSpriteTable)[index].FrameID					= 9;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastSpriteID				= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID			= SPRITEID_NULL;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition			= 0;
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= 0;
	(*g_pCreatureSpriteTable)[index].CreatureType				= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	index++;
	mmiIndex++;
	

	//---------------------------------------------------------------------
	// [254]미클리스
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 249;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;
	
	//---------------------------------------------------------------------
	// [255]미클리스소환몹
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 250;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [256]overpiger소환몹1
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 251;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;
	
	//---------------------------------------------------------------------
	// [257]overpiger소환몹2
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 252;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;
	
	//---------------------------------------------------------------------
	// [258]overpiger소환몹3
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 253;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;
	

	//---------------------------------------------------------------------
	// [259]고스트
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 254;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	index++;
	mmiIndex++;
	

	//---------------------------------------------------------------------
	// [260]터프한 눈사람
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 255;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [261]헬가든 수정구
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 256;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_ALL;
	index++;
	mmiIndex++;
	
	//---------------------------------------------------------------------
	// [262] 괴도 루펭
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 257;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [263] 밀리터리 베어 (071113)
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 258;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [264] 가고일 (071113)
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 259;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;	


	//---------------------------------------------------------------------
	// [265]케르베로스
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 260;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [266]맨티코아트
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 261;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [267]보글트_H
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 262;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [268]보글트_B
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 263;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [269]매서커
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 264;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [270]플럼피 보어
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 265;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;
	
	//---------------------------------------------------------------------
	// [271]슬레이어 입장NPC
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 266;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_SLAYER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [272]뱀파이어 입장NPC
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 267;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [273]아우스터즈 입장NPC
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 268;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_OUSTERS;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [274]카브라캄의 제단NPC
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 269;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_ALL;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [275]카브라캄 (Boss)
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 270;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;



	//---------------------------------------------------------------------
	// [276]xrl
	//---------------------------------------------------------------------

	(*g_pCreatureSpriteTable)[index].FrameID			= 271;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;	

	//---------------------------------------------------------------------
	// [277] 뱀파 고속 이동수단 (정식 명칭 없음)
	//---------------------------------------------------------------------

	(*g_pCreatureSpriteTable)[index].FrameID			= 272;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
//	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_PLAYER_VAMPIRE | FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;
	
	//---------------------------------------------------------------------
	// [278] 티포주 성 1층 문지기
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 273;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [279] 티포주 성 1층 근위대
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 274;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [280] 티포주 성 1층 근위대 대장
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 275;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [281] 티포주 성 2층 귀족 뱀파(여)
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 276;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [282] 티포주 성 2층 귀족 뱀파(남)
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 277;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [283] 티포주 성 2층 귀족 뱀파 대장 (남)
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 278;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [284] 티포주 성 경비병
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 279;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [285] 티포주 성 워버데스
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 280;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [286] 티포주 성 NPC
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 281;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_ALL;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [287] 뱀파 고속 이동수단 (쉐이프 오브 데몬)
	//---------------------------------------------------------------------

	(*g_pCreatureSpriteTable)[index].FrameID			= 282;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID	= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
//	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_PLAYER_VAMPIRE;
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_PLAYER_VAMPIRE | FLAG_CREATURESPRITE_MONSTER_VAMPIRE;
	index++;
	mmiIndex++;

	//---------------------------------------------------------------------
	// [288] 신규마켓 아이템(파이어 엘레멘탈)
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 283;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID	= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;


	//---------------------------------------------------------------------
	// [289]스켈레토리
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 284;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC_ALL;
	index++;
	mmiIndex++;
	
	//---------------------------------------------------------------------
	// [290]서큐버스
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 285;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;

//#if __CONTENTS(__NEW_PET_INCUBUS)
	//---------------------------------------------------------------------
	// [291]인큐버스
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 286;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTable[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTable[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTable2[mmiIndex].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTable2[mmiIndex].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTable[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndex++;
//#endif //__NEW_PET_INCUBUS

//#if __CONTENTS(__ONIBLA)
	int mmiIndexSecond = 0;
	//---------------------------------------------------------------------
	// [292]블렉아스트랄
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 287;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTableSecond[mmiIndexSecond].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTableSecond[mmiIndexSecond].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTableSecond2[mmiIndexSecond].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTableSecond2[mmiIndexSecond].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTableSecond[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadowSecond[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndexSecond++;
	//---------------------------------------------------------------------
	// [293] 빅토어
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 288;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTableSecond[mmiIndexSecond].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTableSecond[mmiIndexSecond].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTableSecond2[mmiIndexSecond].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTableSecond2[mmiIndexSecond].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTableSecond[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadowSecond[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndexSecond++;
	//---------------------------------------------------------------------
	// [294]아고니 차일드
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 289;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTableSecond[mmiIndexSecond].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTableSecond[mmiIndexSecond].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTableSecond2[mmiIndexSecond].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTableSecond2[mmiIndexSecond].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTableSecond[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadowSecond[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndexSecond++;
	//---------------------------------------------------------------------
	// [295]아고니 하운드
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 290;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTableSecond[mmiIndexSecond].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTableSecond[mmiIndexSecond].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTableSecond2[mmiIndexSecond].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTableSecond2[mmiIndexSecond].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTableSecond[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadowSecond[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndexSecond++;
	//---------------------------------------------------------------------
	// [296]화이트 아스트랄
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 291;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTableSecond[mmiIndexSecond].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTableSecond[mmiIndexSecond].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTableSecond2[mmiIndexSecond].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTableSecond2[mmiIndexSecond].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTableSecond[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadowSecond[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndexSecond++;

	//---------------------------------------------------------------------
	// [297]빌라인 레이디
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 292;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTableSecond[mmiIndexSecond].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTableSecond[mmiIndexSecond].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTableSecond2[mmiIndexSecond].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTableSecond2[mmiIndexSecond].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTableSecond[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadowSecond[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndexSecond++;

	//---------------------------------------------------------------------
	// [298]오니 스패니얼
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 293;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTableSecond[mmiIndexSecond].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTableSecond[mmiIndexSecond].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTableSecond2[mmiIndexSecond].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTableSecond2[mmiIndexSecond].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTableSecond[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadowSecond[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_MONSTER;
	index++;
	mmiIndexSecond++;

//#endif //__ONIBLA
//#if __CONTENTS(__PET_MASHIMARO)
	//---------------------------------------------------------------------
	// [299]마시마로
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 294;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTableSecond[mmiIndexSecond].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTableSecond[mmiIndexSecond].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTableSecond2[mmiIndexSecond].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTableSecond2[mmiIndexSecond].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTableSecond[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadowSecond[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndexSecond++;
//#endif //__PET_MASHIMARO

//#ifdef __CONTENTS(__PET_CATS)
	//---------------------------------------------------------------------
	// [300]태비 캣
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 295;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTableSecond[mmiIndexSecond].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTableSecond[mmiIndexSecond].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTableSecond2[mmiIndexSecond].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTableSecond2[mmiIndexSecond].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTableSecond[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadowSecond[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndexSecond++;
	//---------------------------------------------------------------------
	// [301]웰시 캣
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 296;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTableSecond[mmiIndexSecond].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTableSecond[mmiIndexSecond].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTableSecond2[mmiIndexSecond].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTableSecond2[mmiIndexSecond].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTableSecond[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadowSecond[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndexSecond++;
	//---------------------------------------------------------------------
	// [302]샤밍 캣
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 297;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTableSecond[mmiIndexSecond].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTableSecond[mmiIndexSecond].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTableSecond2[mmiIndexSecond].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTableSecond2[mmiIndexSecond].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTableSecond[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadowSecond[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndexSecond++;

//#endif //__PET_CATS

//#if __CONTENTS(__MOONLIGHT_FESTIVAL_EVENT)
	//---------------------------------------------------------------------
	// [303]달빛 여신
	//---------------------------------------------------------------------
	(*g_pCreatureSpriteTable)[index].FrameID			= 298;
	(*g_pCreatureSpriteTable)[index].FirstSpriteID		= mmiTableSecond[mmiIndexSecond].Min;
	(*g_pCreatureSpriteTable)[index].LastSpriteID		= mmiTableSecond[mmiIndexSecond].Max;
	(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID		= mmiTableSecond2[mmiIndexSecond].Min;
	(*g_pCreatureSpriteTable)[index].LastShadowSpriteID		= mmiTableSecond2[mmiIndexSecond].Max;
	(*g_pCreatureSpriteTable)[index].SpriteFilePosition	= indexTableSecond[(*g_pCreatureSpriteTable)[index].FirstSpriteID];	
	(*g_pCreatureSpriteTable)[index].SpriteShadowFilePosition	= indexTableShadowSecond[(*g_pCreatureSpriteTable)[index].FirstShadowSpriteID];
	(*g_pCreatureSpriteTable)[index].CreatureType		= FLAG_CREATURESPRITE_NPC;
	index++;
	mmiIndexSecond++;
//#endif //__MOONLIGHT_FESTIVAL_EVENT

	//------------------------------------------------
	// Save
	//------------------------------------------------
	std::ofstream creatureSpriteTable(g_pFileDef->getProperty("FILE_INFO_CREATURESPRITE").c_str(), std::ios::binary);
	(*g_pCreatureSpriteTable).SaveToFile(creatureSpriteTable);
	creatureSpriteTable.close();
#endif //SAVE_TO_FILE

	//------------------------------------------------
	// Load
	//------------------------------------------------
	ivfstream creatureSpriteTable2;//(FILE_INFO_CREATURE, ios::binary);
	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_INFO_CREATURESPRITE").c_str(), creatureSpriteTable2))
		return FALSE;
	(*g_pCreatureSpriteTable).LoadFromFile(creatureSpriteTable2);
	creatureSpriteTable2.close();
	
	//---------------------------------------------------------------------
	//
	//    CreatureSpriteTable에 대한 정보 설정
	//
	//---------------------------------------------------------------------	
#ifdef SAVE_TO_FILE
//	std::ifstream creatureActionMmiFile("Data\\creatureAction.mmi", ios::binary);
//	std::ifstream creatureActionMmiFile2("Data\\creatureActionShadow.mmi", ios::binary);
//	MMinMaxInfoTable	creatureActionMmiTable;
//	MMinMaxInfoTable	creatureActionMmiTable2;	// 그림자 체크용
//
//	// Creature IndexSprite Min/Max Info
//	creatureActionMmiTable.LoadFromFile(creatureActionMmiFile);
//	creatureActionMmiTable2.LoadFromFile(creatureActionMmiFile2);
//
//	creatureActionMmiFile.close();
//	creatureActionMmiFile2.close();
//
//	if (creatureActionMmiTable.GetSize()!=creatureActionMmiTable2.GetSize())
//	{
//		InitFail("Wrong creatureActionMMI Table Size: %d != %d", creatureActionMmiTable.GetSize(), creatureActionMmiTable2.GetSize());
//
//		return FALSE;
//	}
//
//	for (m=0; m<creatureActionMmiTable.GetSize(); m++)
//	{
//		if (creatureActionMmiTable[m]!=creatureActionMmiTable2[m])
//		{
//			//InitFail("Wrong MMI Size: [%d] (%d ~ %d) != (%d ~ %d)", m, mmiTable[m].Min, mmiTable[m].Max, mmiTable2[m].Min, mmiTable2[m].Max);
//
//			//return FALSE;
//		}
//	}
//
//	int maxCreatures = g_pCreatureSpriteTable->GetSize()-2;	// 2 for slayers
//	int maxCreatureActionSprites = maxCreatures * ACTION_MAX_VAMPIRE;
//
//	g_pCreatureActionSpriteTable->Init( maxCreatureActionSprites );
//
//	for (int creatureActionIndex=0; creatureActionIndex<maxCreatures; creatureActionIndex++)
//	{
//		for (int a=0; a<ACTION_MAX_VAMPIRE; a++)
//		{
//			int i = creatureActionIndex*ACTION_MAX_VAMPIRE + a;
//
//			(*g_pCreatureActionSpriteTable)[i].FrameID				= creatureActionIndex;
//			(*g_pCreatureActionSpriteTable)[i].FirstSpriteID		= creatureActionMmiTable[i].Min;
//			(*g_pCreatureActionSpriteTable)[i].LastSpriteID			= creatureActionMmiTable[i].Max;
//			(*g_pCreatureActionSpriteTable)[i].FirstShadowSpriteID	= creatureActionMmiTable2[i].Min;
//			(*g_pCreatureActionSpriteTable)[i].LastShadowSpriteID	= creatureActionMmiTable2[i].Max;
//			(*g_pCreatureActionSpriteTable)[i].SpriteFilePosition	= indexTable[(*g_pCreatureActionSpriteTable)[i].FirstSpriteID];
//			(*g_pCreatureActionSpriteTable)[i].SpriteShadowFilePosition	= indexTableShadow[(*g_pCreatureActionSpriteTable)[i].FirstShadowSpriteID];
//		}
//	}
//
//
//	//------------------------------------------------
//	// Save
//	//------------------------------------------------
//	std::ofstream creatureActionSpriteTable(FILE_INFO_CREATUREACTIONSPRITE, ios::binary);
//	g_pCreatureActionSpriteTable->SaveToFile(creatureActionSpriteTable);
//	creatureActionSpriteTable.close();
#endif

//	//------------------------------------------------
//	// Load
//	//------------------------------------------------
//	std::ifstream creatureActionSpriteTable2;//(FILE_INFO_CREATURE, ios::binary);
//	if (!FileOpenBinary(FILE_INFO_CREATUREACTIONSPRITE, creatureActionSpriteTable2))
//		return FALSE;
//	g_pCreatureActionSpriteTable->LoadFromFile(creatureActionSpriteTable2);
//	creatureActionSpriteTable2.close();

	return TRUE;
}
