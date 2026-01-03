#pragma warning(disable:4786)
#include <fstream>
#include <list>
#include <vector>
#include <windows.h>

struct PORTAL_FLAG
{
	int zone_id, x, y, portal_x, portal_y;
};

struct PRESET_INFO
{
	int zone_id[4], map_x[4], map_y[4], map_w[4], map_h[4];
};

BOOL InitOustersPortal()
{
	int zoneNum = 0;
	typedef std::list<PORTAL_FLAG> PORTAL_LIST;
	typedef std::vector<PORTAL_LIST> PORTAL_VECTOR;
	PORTAL_LIST		portalList;
	PORTAL_VECTOR		portalVector;
	PORTAL_FLAG portal;

	std::ifstream hornInfoFile("data\\gnomehorn.inf", std::ios::binary);
	hornInfoFile.read((char *)&zoneNum, sizeof(int));
	for(int i = 0; i < zoneNum; i++)
	{
		hornInfoFile.read((char *)&portal.zone_id, sizeof(int));
		hornInfoFile.read((char *)&portal.portal_x, sizeof(int));
		hornInfoFile.read((char *)&portal.portal_y, sizeof(int));
		
		portalList.push_back(portal);
	}

	portal.zone_id = 9999;
	portal.portal_x = 0;
	portal.portal_y = 0;
	
	hornInfoFile.read((char *)&portal.zone_id, sizeof(int));
	hornInfoFile.read((char *)&portal.portal_x, sizeof(int));
	hornInfoFile.read((char *)&portal.portal_y, sizeof(int));
	portalList.push_back(portal);
	

	hornInfoFile.close();

	int map_w = 256, map_h = 256;
	int group_num = 0;
	PORTAL_LIST mapList;

	std::list<PRESET_INFO> presetList;

	PRESET_INFO presetInfo;

	presetInfo.map_x[0] = 100;
	presetInfo.map_y[0] = 0;
	presetInfo.map_w[0] = 256;
	presetInfo.map_h[0] = 256;
	presetInfo.map_x[1] = 0;
	presetInfo.map_y[1] = 0;
	presetInfo.map_w[1] = 256;
	presetInfo.map_h[1] = 256;
	presetInfo.map_x[2] = 100;
	presetInfo.map_y[2] = 50;
	presetInfo.map_w[2] = 256;
	presetInfo.map_h[2] = 256;
	presetInfo.map_x[3] = 0;
	presetInfo.map_y[3] = 50;
	presetInfo.map_w[3] = 256;
	presetInfo.map_h[3] = 256;

	// Limbo
	presetInfo.zone_id[0] = 21;
	presetInfo.zone_id[1] = 22;
	presetInfo.zone_id[2] = 23;
	presetInfo.zone_id[3] = 24;
	presetList.push_back(presetInfo);

	// Eslanian
	presetInfo.zone_id[0] = 11;
	presetInfo.zone_id[1] = 12;
	presetInfo.zone_id[2] = 13;
	presetInfo.zone_id[3] = 14;
	presetList.push_back(presetInfo);
	
	// Drobeta
	presetInfo.zone_id[0] = 31;
	presetInfo.zone_id[1] = 32;
	presetInfo.zone_id[2] = 33;
	presetInfo.zone_id[3] = 34;
	presetList.push_back(presetInfo);
	
	// Rodin
	presetInfo.zone_id[0] = 41;
	presetInfo.zone_id[1] = 42;
	presetInfo.zone_id[2] = 43;
	presetInfo.zone_id[3] = 44;
	presetList.push_back(presetInfo);
	
	// Perona
	presetInfo.zone_id[0] = 61;
	presetInfo.map_x[0] = 50;
	presetInfo.zone_id[1] = 62;
	presetInfo.zone_id[2] = 63;
	presetInfo.map_x[2] = 50;
	presetInfo.zone_id[3] = 64;
	presetList.push_back(presetInfo);
	
	// TIMORE
	presetInfo.zone_id[0] = 51;
	presetInfo.map_x[0] = 100;
	presetInfo.zone_id[1] = 52;
	presetInfo.zone_id[2] = 53;
	presetInfo.map_x[2] = 100;
	presetInfo.zone_id[3] = 54;
	presetList.push_back(presetInfo);

	// 브랑코 
	presetInfo.zone_id[0] = 91;
	presetInfo.map_x[0] = 100;
	presetInfo.zone_id[1] = 92;
	presetInfo.zone_id[2] = 93;
	presetInfo.map_x[2] = 100;
	presetInfo.zone_id[3] = 94;
	presetList.push_back(presetInfo);


	// 카스탈로
	presetInfo.zone_id[0] = 81;
	presetInfo.zone_id[1] = -1;
	presetInfo.zone_id[2] = -1;
	presetInfo.zone_id[3] = -1;
	presetList.push_back(presetInfo);
	
	// d1
	presetInfo.zone_id[0] = 1102;
	presetInfo.map_w[0] = 128;
	presetInfo.map_h[0] = 128;
	presetInfo.zone_id[1] = 1004;
	presetInfo.map_w[1] = 128;
	presetInfo.map_h[1] = 128;
	presetInfo.zone_id[2] = 1123;
	presetInfo.map_w[2] = 128;
	presetInfo.map_h[2] = 128;
	presetInfo.zone_id[3] = 1105;
	presetInfo.map_w[3] = 256;
	presetInfo.map_h[3] = 256;
	presetList.push_back(presetInfo);
	
	// d2
	presetInfo.zone_id[0] = 9999;
	presetInfo.map_w[0] = 128;
	presetInfo.map_h[0] = 128;
	presetInfo.zone_id[1] = 1001;
	presetInfo.map_w[1] = 256;
	presetInfo.map_h[1] = 256;
	presetInfo.zone_id[2] = -1;
	presetInfo.map_w[2] = 128;
	presetInfo.map_h[2] = 128;
	presetInfo.zone_id[3] = 1002;
	presetInfo.map_w[3] = 128;
	presetInfo.map_h[3] = 128;
	presetList.push_back(presetInfo);
	
	// d3
	presetInfo.zone_id[0] = 1112;
	presetInfo.map_w[0] = 100;
	presetInfo.map_h[0] = 100;
	presetInfo.zone_id[1] = 1008;
	presetInfo.map_w[1] = 256;
	presetInfo.map_h[1] = 256;
	presetInfo.zone_id[2] = 1013;
	presetInfo.map_w[2] = 128;
	presetInfo.map_h[2] = 128;
	presetInfo.zone_id[3] = 1011;
	presetInfo.map_w[3] = 128;
	presetInfo.map_h[3] = 128;
	presetList.push_back(presetInfo);
	
	// d4
	presetInfo.zone_id[0] = 1124;
	presetInfo.map_w[0] = 128;
	presetInfo.map_h[0] = 128;
	presetInfo.zone_id[1] = 1126;
	presetInfo.map_w[1] = 128;
	presetInfo.map_h[1] = 128;

	presetInfo.zone_id[2] = -1;
	presetInfo.zone_id[3] = -1;
	//presetInfo.zone_id[2] = 1121;
	//presetInfo.map_w[2] = 128;
	//presetInfo.map_h[2] = 128;
	

	//presetInfo.zone_id[3] = 1125;
	//presetInfo.map_w[3] = 128;
	//presetInfo.map_h[3] = 128;

	presetList.push_back(presetInfo);

	// 아우스터즈 마을, 던전
	presetInfo.zone_id[0] = 1322;
	presetInfo.map_w[0] = 128;
	presetInfo.map_h[0] = 128;
	presetInfo.zone_id[1] = 1311;
	presetInfo.map_w[1] = 128;
	presetInfo.map_h[1] = 128;
	presetInfo.zone_id[2] = 1324;
	presetInfo.map_w[2] = 128;
	presetInfo.map_h[2] = 128;
	presetInfo.zone_id[3] = 1323;
	presetInfo.map_w[3] = 128;
	presetInfo.map_h[3] = 128;
	presetList.push_back(presetInfo);
	
	std::list<PRESET_INFO>::iterator itr = presetList.begin();
	std::list<PRESET_INFO>::iterator endItr = presetList.end();

	int aaa,bbb;
	while(itr != endItr)
	{
		PORTAL_LIST::iterator itr2;
		PORTAL_LIST::iterator endItr2 = portalList.end();

		for(int i = 0; i < 4; i++)
		{
			itr2 = portalList.begin();
			while(itr2 != endItr2)
			{
				aaa = itr->zone_id[i];
				bbb = itr2->zone_id;

				if(itr->zone_id[i] == itr2->zone_id)
				{
					portal.zone_id = itr2->zone_id;
					portal.portal_x = itr2->portal_x;
					portal.portal_y = itr2->portal_y;
					
					if(itr2->zone_id != 9999) // by Csm 포탈이 있는경우 -- 하드한 코딩 (죄표마추기 힘들어서 ㅠㅠ)
					{
						portal.x = itr->map_x[i]+portal.portal_x*100/itr->map_w[i];
						portal.y = itr->map_y[i]+portal.portal_y*50/itr->map_h[i];
					}
									
					if(itr2->zone_id == 1001) 
							portal.x +=100;

					mapList.push_back(portal);
				}
				itr2++;
			}
		}

		portalVector.push_back(mapList);
		mapList.clear();

		itr++;
	}

	zoneNum = portalVector.size();

	std::ofstream hornFile("data\\info\\horn.inf", std::ios::binary);
	hornFile.write((const char *)&zoneNum, sizeof(int));

	PORTAL_VECTOR::iterator mapItr = portalVector.begin();
	PORTAL_VECTOR::iterator mapEndItr = portalVector.end();

	while(mapItr != mapEndItr)
	{
		PORTAL_LIST ptList = *mapItr;

		PORTAL_LIST::iterator listItr = ptList.begin();
		PORTAL_LIST::iterator listEndItr = ptList.end();

		zoneNum = ptList.size();
		hornFile.write((const char *)&zoneNum, sizeof(int));

		while(listItr != listEndItr)
		{
			portal = *listItr;

			hornFile.write((const char *)&portal.zone_id, sizeof(int));
			hornFile.write((const char *)&portal.x, sizeof(int));
			hornFile.write((const char *)&portal.y, sizeof(int));
			hornFile.write((const char *)&portal.portal_x, sizeof(int));
			hornFile.write((const char *)&portal.portal_y, sizeof(int));

			listItr++;
		}

		mapItr++;
	}

	hornFile.close();

	return TRUE;
}
