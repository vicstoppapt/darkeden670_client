
//-----------------------------------------------------------------------------
// PacketFunction.cpp
//-----------------------------------------------------------------------------
// Packet¿¡ °ü·ÃµÈ utilityÇÔ¼ö
//-----------------------------------------------------------------------------

#include "Client_PCH.h"
#include <WINDOWS.H>
#include < nb30.h >
#include < wsipx.h >
#include < wsnwlink.h >
#include "MGameDef.h"
#include "MTopView.h"
#include "ClientDef.h"
#include "MCreatureWear.h"
#include "MItem.h"
#include "MEffectGeneratorTable.h"
#include "ClientConfig.h"
#include "MitemOptionTable.h"
#include "AddonDef.h"
#include "MItem.h"
#include "MInventory.h"
#include "MSlayerGear.h"
#include "MVampireGear.h"
#include "MOustersGear.h"
#include "MMoneyManager.h"
#include "MGameStringTable.h"
#include "VS_UI_Mouse_pointer.h"
#include "VS_UI.h"
#include "UIDialog.h"
#include "ServerInformation.h"
#include "PacketFunction.h"
#include "UserInformation.h"
#include "MFakeCreature.h"
#include "MCreature.h"
#include "MSoundTable.h"
#include "MGuildMarkManager.h"
#include "MGuildInfoMapper.h"
#include "UIFunction.h"
#include "ServerInfo.h"
// packet
#include "packet/PetInfo.h"
#include "Packet/PCSlayerInfo3.h"
#include "Packet/PCOustersInfo3.h"
#include "Packet/PCVampireInfo3.h"
#include "ExperienceTable.h"

#include "Packet\GPackets\GCAddItemToZone.h"
#include "Packet\GPackets\GCAddMonster.h"
#include "Packet\PCSlayerInfo2.h"
#include "Packet\PCVampireInfo2.h"
#include "Packet\PCOustersInfo2.h"
#include "Packet\InventoryInfo.h"
#include "Packet\GearInfo.h"
#include "Packet\ExtraInfo.h"
#include "Packet/Cpackets/CGSay.h"
#include "Packet/cpackets/CGCrashReport.h"
#include "EffectInfo.h"
#include "MScreenEffectManager.h"
#include "TempInformation.h"
#include "Packet\ModifyInfo.h"
//#include "CrashReport.h"
//#include "MCrashReportManager.h"
//#include "MFileDef.h"
#include "Properties.h"

#include "CImm.h"

#include "DebugInfo.h"
#include "MEventManager.h"
#include "MCreature.h"
#include "MZone.h"
#include "MPlayer.h"
#include "VS_UI_GameCommon2.h"
#include "MEffectSpriteTypeTable.h"
#include "EffectSpriteTypeDef.h"

#include "Packet/cpackets/CGAuthKey.h"
#include "BloodBibleSignInfo.h"
#include "VS_UI_filepath.h"

#ifdef __NPROTECT__
#include "PacketFunction.h"

extern CNPGameLib npgl;
#endif

#define SAFE_DELETE(x)		{ if(x!=NULL) delete x; x=NULL; }



extern MScreenEffectManager*	g_pInventoryEffectManager;
extern DWORD	g_PreviousCreatureType;

extern bool FileOpenBinary(const char* filename, ivfstream& file);

extern BOOL g_bSetHotKey;

extern bool		g_bZoneLargeLoadImage;
extern bool		g_bZoneSmallLoadImage;
extern MZone*	g_pZoneLarge;
extern MZone*	g_pZoneSmall;
extern int		g_nZoneLarge;
extern int		g_nZoneSmall;
extern bool		g_bZonePlayerInLarge;
extern bool		g_bFullScreen;
int				g_DyeColorSet[48] = 
{400,359,312,267,222,174,130,86,381,342,297,252,207,159,115,70,369,327,283,237,193,145,101,57,
165,381,407,420,435,451,466,480,170,364,412,426,440,455,471,487,179,371,419,434,449,464,479,494};

// sourceÈ­ÀÏ ³¡¿¡ ÀÖ´Ù. header compile½Ã°£ ¾Æ±î¹ö¼­ ..- -;
void	CheckItemForSkillIcon(const MItem* pItem);

extern BYTE g_macAddress[6];

//-----------------------------------------------------------------------------
// Global Packet HairID
//-----------------------------------------------------------------------------
int g_PacketHairID[3] = 
{
	ADDONID_HAIR1,
	ADDONID_HAIR2,
	ADDONID_HAIR3
};

//-----------------------------------------------------------------------------
// Global Packet Item Table
//-----------------------------------------------------------------------------
MItem*		g_pPacketItemHelm[HELMET_MAX] = { NULL, };

MItem*		g_pPacketItemJacket[JACKET_MAX] = { NULL, };
MItem*		g_pPacketItemPants[PANTS_MAX] = { NULL, };
MItem*		g_pPacketItemWeapon[WEAPON_MAX] = { NULL, };
MItem*		g_pPacketItemShield[SHIELD_MAX] = { NULL, };
MItem*		g_pPacketItemMotorcycle[MOTORCYCLE_MAX] = { NULL, };
MItem*		g_pPacketItemShoulder[SHOULDER_MAX] = { NULL, };

MItem*		g_pPacketItemOustersCoat[OUSTERS_COAT_MAX] = { NULL, };
MItem*		g_pPacketItemOustersArm[OUSTERS_ARM_MAX] = { NULL, };

MItem*		g_pPacketItemVampireCoat[VAMPIRE_COAT_MAX] = { NULL, };
MItem*		g_pPacketItemVampireArm[VAMPIRE_ARM_MAX] = { NULL, };

#if __CONTENTS(__GEAR_SWAP_CHANGE)	//PacketFunction.cpp		GearInfo* g_pGearInfo	= NULL;
GearInfo* g_pGearInfo	= NULL;
#endif	// __GEAR_SWAP_CHANGE
//-----------------------------------------------------------------------------
// Init PacketItemTable
//-----------------------------------------------------------------------------
void
InitPacketItemTable()
{
	//------------------------------------------------------------
	// MVampireCoat
	//------------------------------------------------------------
	MVampireCoat* pVampireCoatBasic = new MVampireCoat;	 pVampireCoatBasic->SetItemType( 0 ); pVampireCoatBasic->ClearItemOption(); 
	MVampireCoat* pVampireCoat1 = new MVampireCoat;	 pVampireCoat1->SetItemType( 0 ); pVampireCoat1->ClearItemOption(); 
	MVampireCoat* pVampireCoat2 = new MVampireCoat;	 pVampireCoat2->SetItemType( 4 ); pVampireCoat2->ClearItemOption(); 
	MVampireCoat* pVampireCoat3 = new MVampireCoat;	 pVampireCoat3->SetItemType( 8 ); pVampireCoat3->ClearItemOption(); 
	MVampireCoat* pVampireCoat4 = new MVampireCoat;	 pVampireCoat4->SetItemType( 18 ); pVampireCoat4->ClearItemOption(); 
	MVampireCoat* pVampireCoat5 = new MVampireCoat;	 pVampireCoat5->SetItemType( 28 ); pVampireCoat5->ClearItemOption(); //by viva
	MVampireCoat* pVampireCoat6 = new MVampireCoat;	 pVampireCoat6->SetItemType( 30 ); pVampireCoat6->ClearItemOption(); 
	MVampireCoat* pVampireCoat7 = new MVampireCoat;	 pVampireCoat7->SetItemType( 32 ); pVampireCoat7->ClearItemOption(); 
	MVampireCoat* pVampireCoat8 = new MVampireCoat;	 pVampireCoat8->SetItemType( 40 ); pVampireCoat8->ClearItemOption(); //231   rallser
	
	g_pPacketItemVampireCoat[VAMPIRE_COAT_BASIC] = pVampireCoatBasic;
	g_pPacketItemVampireCoat[VAMPIRE_COAT1] = pVampireCoat1;
	g_pPacketItemVampireCoat[VAMPIRE_COAT2] = pVampireCoat2;
	g_pPacketItemVampireCoat[VAMPIRE_COAT3] = pVampireCoat3;
	g_pPacketItemVampireCoat[VAMPIRE_COAT4] = pVampireCoat4;
	g_pPacketItemVampireCoat[VAMPIRE_COAT5] = pVampireCoat5;//by viva
	g_pPacketItemVampireCoat[VAMPIRE_COAT6] = pVampireCoat6;
	g_pPacketItemVampireCoat[VAMPIRE_COAT7] = pVampireCoat7;//201 rallser
	g_pPacketItemVampireCoat[VAMPIRE_COAT8] = pVampireCoat8;//231 rallser

	//------------------------------------------------------------
	// MVampire Arm
	//------------------------------------------------------------
	MVampireWeapon* pVampireArm1 = new MVampireWeapon;	 pVampireArm1->SetItemType( 0 ); pVampireArm1->ClearItemOption(); 
	MVampireWeapon* pVampireArm2 = new MVampireWeapon;	 pVampireArm2->SetItemType( 26 ); pVampireArm2->ClearItemOption();//by viva 171
	MVampireWeapon* pVampireArm3 = new MVampireWeapon;	 pVampireArm3->SetItemType( 27 ); pVampireArm3->ClearItemOption();	//181
	MVampireWeapon* pVampireArm4 = new MVampireWeapon;	 pVampireArm4->SetItemType( 28 ); pVampireArm4->ClearItemOption();	//201 by rallser
	MVampireWeapon* pVampireArm5 = new MVampireWeapon;	 pVampireArm5->SetItemType( 32 ); pVampireArm5->ClearItemOption();	//231 by rallser


	g_pPacketItemVampireArm[VAMPIRE_ARM_NONE]	= NULL;
	g_pPacketItemVampireArm[VAMPIRE_ARM_WEAPON]	= pVampireArm1;
	g_pPacketItemVampireArm[VAMPIRE_ARM_WEAPON2] = pVampireArm2;
	g_pPacketItemVampireArm[VAMPIRE_ARM_WEAPON3] = pVampireArm3;
	g_pPacketItemVampireArm[VAMPIRE_ARM_WEAPON4] = pVampireArm4;
	g_pPacketItemVampireArm[VAMPIRE_ARM_WEAPON5] = pVampireArm5;


	//------------------------------------------------------------
	// MOustersCoat
	//------------------------------------------------------------
	MOustersCoat* pOustersCoatBasic = new MOustersCoat;	 pOustersCoatBasic->SetItemType( 0 ); pOustersCoatBasic->ClearItemOption(); 
	MOustersCoat* pOustersCoat1 = new MOustersCoat;	 pOustersCoat1->SetItemType( 0 ); pOustersCoat1->ClearItemOption(); 
	MOustersCoat* pOustersCoat2 = new MOustersCoat;	 pOustersCoat2->SetItemType( 3 ); pOustersCoat2->ClearItemOption(); 
	MOustersCoat* pOustersCoat3 = new MOustersCoat;	 pOustersCoat3->SetItemType( 6 ); pOustersCoat3->ClearItemOption(); 
	MOustersCoat* pOustersCoat4 = new MOustersCoat;	 pOustersCoat4->SetItemType( 11 ); pOustersCoat4->ClearItemOption(); 
	MOustersCoat* pOustersCoat5 = new MOustersCoat;	 pOustersCoat5->SetItemType( 16 ); pOustersCoat5->ClearItemOption(); //by viva
	MOustersCoat* pOustersCoat6 = new MOustersCoat;	 pOustersCoat6->SetItemType( 17 ); pOustersCoat6->ClearItemOption(); 
	MOustersCoat* pOustersCoat7 = new MOustersCoat;	 pOustersCoat7->SetItemType( 18 ); pOustersCoat7->ClearItemOption();//by ralllser201
	MOustersCoat* pOustersCoat8 = new MOustersCoat;	 pOustersCoat8->SetItemType( 22 ); pOustersCoat8->ClearItemOption();//by ralllser231
	
	g_pPacketItemOustersCoat[OUSTERS_COAT_BASIC] = pOustersCoatBasic;
	g_pPacketItemOustersCoat[OUSTERS_COAT1] = pOustersCoat1;
	g_pPacketItemOustersCoat[OUSTERS_COAT2] = pOustersCoat2;
	g_pPacketItemOustersCoat[OUSTERS_COAT3] = pOustersCoat3;
	g_pPacketItemOustersCoat[OUSTERS_COAT4] = pOustersCoat4;
	g_pPacketItemOustersCoat[OUSTERS_COAT5] = pOustersCoat5;	//by viva
	g_pPacketItemOustersCoat[OUSTERS_COAT6] = pOustersCoat6;
	g_pPacketItemOustersCoat[OUSTERS_COAT7] = pOustersCoat7; //by rallser201
	g_pPacketItemOustersCoat[OUSTERS_COAT8] = pOustersCoat8; //by rallser231
	
	//------------------------------------------------------------
	// MOustersArm
	//------------------------------------------------------------
	MOustersWristlet* pOustersArm1 = new MOustersWristlet;	 pOustersArm1->SetItemType( 0 ); pOustersArm1->ClearItemOption(); 
	MOustersChakram* pOustersArm2 = new MOustersChakram;	 pOustersArm2->SetItemType( 0 ); pOustersArm2->ClearItemOption(); 
	MOustersChakram* pOustersArm3 = new MOustersChakram;	 pOustersArm3->SetItemType( 21 ); pOustersArm3->ClearItemOption();	//by viva
	MOustersChakram* pOustersArm4 = new MOustersChakram;	 pOustersArm4->SetItemType( 22 ); pOustersArm4->ClearItemOption(); 
	MOustersChakram* pOustersArm5 = new MOustersChakram;	 pOustersArm5->SetItemType( 23 ); pOustersArm5->ClearItemOption(); //by rallser201
	MOustersChakram* pOustersArm6 = new MOustersChakram;	 pOustersArm6->SetItemType( 27 ); pOustersArm6->ClearItemOption(); //by rallser231

	g_pPacketItemOustersArm[OUSTERS_ARM_GAUNTLET] = pOustersArm1;
	g_pPacketItemOustersArm[OUSTERS_ARM_CHAKRAM] = pOustersArm2;
	g_pPacketItemOustersArm[OUSTERS_ARM_CHAKRAM_171] = pOustersArm3;
	g_pPacketItemOustersArm[OUSTERS_ARM_CHAKRAM_181] = pOustersArm4;
	g_pPacketItemOustersArm[OUSTERS_ARM_CHAKRAM_201] = pOustersArm5;//rallser201
	g_pPacketItemOustersArm[OUSTERS_ARM_CHAKRAM_231] = pOustersArm6;//rallser201

	//------------------------------------------------------------
	// HELM
	//------------------------------------------------------------
	MHelm* pHelm1 = new MHelm;	 pHelm1->SetItemType( 0 ); pHelm1->ClearItemOption(); 
	MHelm* pHelm2 = new MHelm;	 pHelm2->SetItemType( 3 ); pHelm2->ClearItemOption();
	MHelm* pHelm3 = new MHelm;	 pHelm3->SetItemType( 12 ); pHelm3->ClearItemOption();
	MHelm* pHelm4 = new MHelm;	 pHelm4->SetItemType( 16 ); pHelm4->ClearItemOption();//by viva
	MHelm* pHelm5 = new MHelm;	 pHelm5->SetItemType( 17 ); pHelm5->ClearItemOption();
	MHelm* pHelm6 = new MHelm;	 pHelm6->SetItemType( 18 ); pHelm6->ClearItemOption();//rallser201
	MHelm* pHelm7 = new MHelm;	 pHelm6->SetItemType( 21 ); pHelm7->ClearItemOption();//rallser231

	g_pPacketItemHelm[HELMET_NONE]	= NULL;
	g_pPacketItemHelm[HELMET1]		= pHelm1;
	g_pPacketItemHelm[HELMET2]		= pHelm2;
	g_pPacketItemHelm[HELMET3]		= pHelm3;
	g_pPacketItemHelm[HELMET4]		= pHelm4;	//by viva
	g_pPacketItemHelm[HELMET5]		= pHelm5;
	g_pPacketItemHelm[HELMET6]		= pHelm6;
	g_pPacketItemHelm[HELMET7]		= pHelm7;
	//------------------------------------------------------------
	// COAT
	//------------------------------------------------------------
	MCoat* pCoat1 = new MCoat;	pCoat1->SetItemType( 0 ); pCoat1->ClearItemOption();
	MCoat* pCoat2 = new MCoat;	pCoat2->SetItemType( 4 );	pCoat2->ClearItemOption();
	MCoat* pCoat3 = new MCoat;	pCoat3->SetItemType( 8 );	pCoat3->ClearItemOption();
	MCoat* pCoat4 = new MCoat;	pCoat4->SetItemType( 22 );	pCoat4->ClearItemOption();
	MCoat* pCoat5 = new MCoat;	pCoat5->SetItemType( 32 );	pCoat5->ClearItemOption();//by viva
	MCoat* pCoat6 = new MCoat;	pCoat6->SetItemType( 34 );	pCoat6->ClearItemOption();
	MCoat* pCoat7 = new MCoat;	pCoat7->SetItemType( 36 );	pCoat7->ClearItemOption();//rallser201
	MCoat* pCoat8 = new MCoat;	pCoat8->SetItemType( 44 );	pCoat8->ClearItemOption();//rallser201

	g_pPacketItemJacket[JACKET_BASIC]	= NULL;	// pCoat1
	g_pPacketItemJacket[JACKET1]		= pCoat1;
	g_pPacketItemJacket[JACKET2]		= pCoat2;
	g_pPacketItemJacket[JACKET3]		= pCoat3;
	g_pPacketItemJacket[JACKET4]		= pCoat4;
	g_pPacketItemJacket[JACKET5]		= pCoat5;	//by viva
	g_pPacketItemJacket[JACKET6]		= pCoat6;
	g_pPacketItemJacket[JACKET7]		= pCoat7;//by rallser201
	g_pPacketItemJacket[JACKET8]		= pCoat8;//by rallser201

	//------------------------------------------------------------
	// TROUSER
	//------------------------------------------------------------
	MTrouser* pTrouser1 = new MTrouser;		pTrouser1->SetItemType( 0 ); pTrouser1->ClearItemOption();
	MTrouser* pTrouser2 = new MTrouser;		pTrouser2->SetItemType( 4 ); pTrouser2->ClearItemOption();
	MTrouser* pTrouser3 = new MTrouser;		pTrouser3->SetItemType( 8 ); pTrouser3->ClearItemOption();
	MTrouser* pTrouser4 = new MTrouser;		pTrouser4->SetItemType( 22 ); pTrouser4->ClearItemOption();
	MTrouser* pTrouser5 = new MTrouser;		pTrouser5->SetItemType( 36 ); pTrouser5->ClearItemOption();
	MTrouser* pTrouser6 = new MTrouser;		pTrouser6->SetItemType( 42 ); pTrouser6->ClearItemOption();

	g_pPacketItemPants[PANTS_BASIC]		= NULL;//pTrouser1;
	g_pPacketItemPants[PANTS1]			= pTrouser1;
	g_pPacketItemPants[PANTS2]			= pTrouser2;
	g_pPacketItemPants[PANTS3]			= pTrouser3;
	g_pPacketItemPants[PANTS4]			= pTrouser4;
	g_pPacketItemPants[PANTS5]			= pTrouser5;//rallser201
	g_pPacketItemPants[PANTS6]			= pTrouser6;//rallser231

	//------------------------------------------------------------
	// WEAPON
	//------------------------------------------------------------
	MSword*	pSword = new MSword;	pSword->SetItemType( 0 );	pSword->ClearItemOption();
	MBlade*	pBlade = new MBlade;	pBlade->SetItemType( 0 );	pBlade->ClearItemOption();
	MGunAR*	pGunAR = new MGunAR;	pGunAR->SetItemType( 0 );	pGunAR->ClearItemOption();
	MGunTR*	pGunSR = new MGunTR;	pGunSR->SetItemType( 0 );	pGunSR->ClearItemOption();
	MGunSG*	pGunSG = new MGunSG;	pGunSG->SetItemType( 0 );	pGunSG->ClearItemOption();
	MGunSMG*pGunSMG = new MGunSMG;	pGunSMG->SetItemType( 0 );	pGunSMG->ClearItemOption();
	MCross*	pCross = new MCross;	pCross->SetItemType( 0 );	pCross->ClearItemOption();
	MMace*  pMace  = new MMace;     pMace->SetItemType( 0 );	pMace->ClearItemOption();

	MSword* pSword2 = new MSword;	pSword2->SetItemType( 21 ); pSword2->ClearItemOption();
	MBlade* pBlade2 = new MBlade;	pBlade2->SetItemType( 21 ); pBlade2->ClearItemOption();
	MGunAR* pGunAR2 = new MGunAR;	pGunAR2->SetItemType( 21 ); pGunAR2->ClearItemOption();
	MGunTR* pGunSR2 = new MGunTR;	pGunSR2->SetItemType( 21 ); pGunSR2->ClearItemOption();
	MCross* pCross2	= new MCross;	pCross2->SetItemType( 19 ); pCross2->ClearItemOption();
	MMace*	pMace2	= new MMace;	pMace2->SetItemType( 19 );	pMace2->ClearItemOption();

	/*MSword* pSword3 = new MSword;	pSword3->SetItemType( 23 ); pSword3->ClearItemOption();
	MBlade* pBlade3 = new MBlade;	pBlade3->SetItemType( 23 ); pBlade3->ClearItemOption();
	MGunAR* pGunAR3 = new MGunAR;	pGunAR3->SetItemType( 23 ); pGunAR3->ClearItemOption();
	MGunTR* pGunSR3 = new MGunTR;	pGunSR3->SetItemType( 23 ); pGunSR3->ClearItemOption();
	MCross* pCross3	= new MCross;	pCross3->SetItemType( 21 ); pCross3->ClearItemOption();
	MMace*	pMace3	= new MMace;	pMace3->SetItemType( 21 );	pMace3->ClearItemOption();*/

	g_pPacketItemWeapon[WEAPON_NONE]			= NULL;
	g_pPacketItemWeapon[WEAPON_SWORD]			= pSword;
	g_pPacketItemWeapon[WEAPON_BLADE]			= pBlade;
	//g_pPacketItemWeapon[WEAPON_SHIELD]			= NULL;
	//g_pPacketItemWeapon[WEAPON_SWORD_SHIELD]	= pSword;
	g_pPacketItemWeapon[WEAPON_AR]				= pGunAR;
	g_pPacketItemWeapon[WEAPON_SR]				= pGunSR;
	g_pPacketItemWeapon[WEAPON_SG]				= pGunSG;
	g_pPacketItemWeapon[WEAPON_SMG]				= pGunSMG;
	g_pPacketItemWeapon[WEAPON_CROSS]			= pCross;	
	g_pPacketItemWeapon[WEAPON_MACE]			= pMace;

	g_pPacketItemWeapon[WEAPON_SWORD_2]			= pSword2;
	g_pPacketItemWeapon[WEAPON_BLADE_2]			= pBlade2;
	g_pPacketItemWeapon[WEAPON_AR_2]			= pGunAR2;
	g_pPacketItemWeapon[WEAPON_SR_2]			= pGunSR2;
	g_pPacketItemWeapon[WEAPON_CROSS_2]			= pCross2;	
	g_pPacketItemWeapon[WEAPON_MACE_2]			= pMace2;

	/*g_pPacketItemWeapon[WEAPON_SWORD_3]			= pSword3;
	g_pPacketItemWeapon[WEAPON_BLADE_3]			= pBlade3;
	g_pPacketItemWeapon[WEAPON_AR_3]			= pGunAR3;
	g_pPacketItemWeapon[WEAPON_SR_3]			= pGunSR3;
	g_pPacketItemWeapon[WEAPON_CROSS_3]			= pCross3;	
	g_pPacketItemWeapon[WEAPON_MACE_3]			= pMace3;//rallser201*/
	//------------------------------------------------------------
	// SHIELD
	//------------------------------------------------------------
	MShield* pShield1 = new MShield; pShield1->SetItemType( 0 ); pShield1->ClearItemOption();
	MShield* pShield2 = new MShield; pShield2->SetItemType( 5 ); pShield2->ClearItemOption();
	MShield* pShield3 = new MShield; pShield3->SetItemType( 16 ); pShield3->ClearItemOption();	//by viva
	MShield* pShield4 = new MShield; pShield4->SetItemType( 17 ); pShield4->ClearItemOption();
	MShield* pShield5 = new MShield; pShield5->SetItemType( 18 ); pShield5->ClearItemOption();
	MShield* pShield6 = new MShield; pShield6->SetItemType( 21 ); pShield6->ClearItemOption();

	g_pPacketItemShield[SHIELD_NONE] = NULL;
	g_pPacketItemShield[SHIELD1] = pShield1;
	g_pPacketItemShield[SHIELD2] = pShield2;
	g_pPacketItemShield[SHIELD3] = pShield3;	//by viva
	g_pPacketItemShield[SHIELD4] = pShield4;
	g_pPacketItemShield[SHIELD5] = pShield5;
	g_pPacketItemShield[SHIELD6] = pShield6;   //231
	
	//------------------------------------------------------------
	// motorcycle
	//------------------------------------------------------------
	MMotorcycle* pMotor1 = new MMotorcycle;	pMotor1->SetItemType( 0 ); pMotor1->ClearItemOption();
	// 2004, 1, 5, sobeit modify start - type º¯°æ 1->6, 2->7 ·Î
	MMotorcycle* pMotor2 = new MMotorcycle;	pMotor2->SetItemType( 6 ); pMotor2->ClearItemOption();
	MMotorcycle* pMotor3 = new MMotorcycle;	pMotor3->SetItemType( 7 ); pMotor3->ClearItemOption();
	// 2004, 1, 5, sobeit modify end
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
	MMotorcycle* pMotor4 = new MMotorcycle;	pMotor4->SetItemType( 8 ); pMotor4->ClearItemOption();
#if __CONTENTS(__SECOND_TRANSFORTER)
	MMotorcycle* pMotor5 = new MMotorcycle;	pMotor5->SetItemType( 9 ); pMotor5->ClearItemOption();
	MMotorcycle* pMotor6 = new MMotorcycle;	pMotor6->SetItemType( 10 ); pMotor6->ClearItemOption();
	MMotorcycle* pMotor7 = new MMotorcycle;	pMotor7->SetItemType( 11 ); pMotor7->ClearItemOption();
#endif //__SECOND_TRANSFORTER
#else
	MMotorcycle* pMotor4 = NULL;
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
	

	g_pPacketItemMotorcycle[MOTORCYCLE_NONE]	= NULL;
	g_pPacketItemMotorcycle[MOTORCYCLE1]		= pMotor1;
	g_pPacketItemMotorcycle[MOTORCYCLE2]		= pMotor2;
	g_pPacketItemMotorcycle[MOTORCYCLE3]		= pMotor3;
	g_pPacketItemMotorcycle[MOTORCYCLE4]		= pMotor4;
#if __CONTENTS(__SECOND_TRANSFORTER)
	g_pPacketItemMotorcycle[MOTORCYCLE5]		= pMotor5;
	g_pPacketItemMotorcycle[MOTORCYCLE6]		= pMotor6;
	g_pPacketItemMotorcycle[MOTORCYCLE7]		= pMotor7;
#endif //__SECOND_TRANSFORTER
	//------------------------------------------------------------
	// shouler
	//------------------------------------------------------------
	
	//Start ÀÌÀ¯ Global º¯¼ö¿Í °°Àº ÀÌ¸§À» »ç¿ë ÇØ¼­ ¸Þ¸ð¸®°¡ »èÁ¦µÇÁö ¾ÊÀ½
	//MItem*		g_pPacketItemShoulder[SHOULDER_MAX] = { NULL, };
	//2005. 04.13 µÑ¸® End

	MShoulderArmor* pShoulder1 = new MShoulderArmor;	pShoulder1->SetItemType( 0 ); pShoulder1->ClearItemOption();
	g_pPacketItemShoulder[SHOULDER_NONE]	= NULL;
	g_pPacketItemShoulder[SHOULDER1]		= pShoulder1;
	
}

//-----------------------------------------------------------------------------
// Init PacketItemTable
//-----------------------------------------------------------------------------
void
ReleasePacketItemTable()
{
	int i;

	//------------------------------------------------------------
	// VAMPIRE_ARM
	//------------------------------------------------------------
	for (i=0; i<VAMPIRE_COAT_MAX; i++)
	{
		if (g_pPacketItemVampireCoat[i]!=NULL)
		{
			delete g_pPacketItemVampireCoat[i];
			g_pPacketItemVampireCoat[i] = NULL;
		}
	}


	//------------------------------------------------------------
	// VAMPIRE_ARM
	//------------------------------------------------------------
	for (i=0; i<VAMPIRE_ARM_MAX; i++)
	{
		if (g_pPacketItemVampireArm[i]!=NULL)
		{
			delete g_pPacketItemVampireArm[i];
			g_pPacketItemVampireArm[i] = NULL;
		}
	}

	//------------------------------------------------------------
	// OUSTERS_COAT
	//------------------------------------------------------------
	for (i=0; i<OUSTERS_COAT_MAX; i++)
	{
		if (g_pPacketItemOustersCoat[i]!=NULL)
		{
			delete g_pPacketItemOustersCoat[i];
			g_pPacketItemOustersCoat[i] = NULL;
		}
	}

	//------------------------------------------------------------
	// OUSTERS_ARM
	//------------------------------------------------------------
	for (i=0; i<OUSTERS_ARM_MAX; i++)
	{
		if (g_pPacketItemOustersArm[i]!=NULL)
		{
			delete g_pPacketItemOustersArm[i];
			g_pPacketItemOustersArm[i] = NULL;
		}
	}
	

	//------------------------------------------------------------
	// HELM
	//------------------------------------------------------------
	for (i=0; i<HELMET_MAX; i++)
	{
		if (i!=HELMET_NONE 
			&& g_pPacketItemHelm[i]!=NULL)
		{
			delete g_pPacketItemHelm[i];
		}
	}
	
	//------------------------------------------------------------
	// COAT
	//------------------------------------------------------------
	for (i=0; i<JACKET_MAX; i++)
	{
		if (i!=JACKET_BASIC 
			&& g_pPacketItemJacket[i]!=NULL)
		{
			delete g_pPacketItemJacket[i];
		}
	}	

	//------------------------------------------------------------
	// TROUSER
	//------------------------------------------------------------
	for (i=0; i<PANTS_MAX; i++)
	{
		if (i!=PANTS_BASIC
			&& g_pPacketItemPants[i]!=NULL)
		{
			delete g_pPacketItemPants[i];
		}
	}	

	//------------------------------------------------------------
	// WEAPON
	//------------------------------------------------------------
	for (i=0; i<WEAPON_MAX; i++)		
	{
		if (i!=WEAPON_NONE 
			&& g_pPacketItemWeapon[i]!=NULL)
		{
			delete g_pPacketItemWeapon[i];
		}
	}

	//------------------------------------------------------------
	// SHIELD
	//------------------------------------------------------------
	for (i=0; i<SHIELD_MAX; i++)
	{
		if (g_pPacketItemShield[i]!=NULL)
		{
			delete g_pPacketItemShield[i];
		}
	}
	
	//------------------------------------------------------------
	// motorcycle
	//------------------------------------------------------------
	for (i=0; i<MOTORCYCLE_MAX; i++)
	{
		if (i!=MOTORCYCLE_NONE
			&& g_pPacketItemMotorcycle[i]!=NULL)
		{
			delete g_pPacketItemMotorcycle[i];
		}
	}

	//------------------------------------------------------------
	// shoulder
	//------------------------------------------------------------
	for (i=0; i<SHOULDER_MAX; i++)
	{
		if (i!=SHOULDER_NONE
			&& g_pPacketItemShoulder[i]!=NULL)
		{
			delete g_pPacketItemShoulder[i];
		}
	}
}

//-----------------------------------------------------------------------------
// Get Mine ActionInfo
//-----------------------------------------------------------------------------
// Áö·Ú(item type)¶û °ü·ÃµÈ actioninfo¸¦ ¾Ë¾Æ³½´Ù.
// ¾øÀ¸¸é -1À» returnÇÑ´Ù.
//-----------------------------------------------------------------------------
int
GetMineActionInfo(int itemType)
{
	const int maxMine = 5;

	const int mineSkillID[maxMine] = {
		MINE_ANKLE_KILLER,
		MINE_POMZ,
		MINE_AP_C1,
		MINE_DIAMONDBACK,		
		MINE_SWIFT_EX
	};

	if (itemType>=0 && itemType<maxMine)
	{		
		return mineSkillID[itemType];
	}

	return -1;
}

//-----------------------------------------------------------------------------
// Get Bomb ActionInfo
//-----------------------------------------------------------------------------
// ÆøÅº(item type)¶û °ü·ÃµÈ actioninfo¸¦ ¾Ë¾Æ³½´Ù.
// ¾øÀ¸¸é -1À» returnÇÑ´Ù.
//-----------------------------------------------------------------------------
int
GetBombActionInfo(int itemType)
{
	const int maxBomb = 5;

	const int bombSkillID[maxBomb] = {
		BOMB_SPLINTER,
		BOMB_ACER,
		BOMB_BULLS,
		BOMB_STUN,
		BOMB_CROSSBOW,		
	};

	if (itemType>=0 && itemType<maxBomb)
	{		
		return bombSkillID[itemType];
	}

	return -1;
}

//-----------------------------------------------------------------------------
// Set Gore Level
//-----------------------------------------------------------------------------
void
SetGoreLevel(bool bGoreLevel)
{
	// Gore Level ÇÒ·Á¸é..
	// EffectGenerator¿¡¼­ effectSpriteTypeÀÌ EFFECTSPRITETYPE_NULLÀÎ 
	// °æ¿ì¸¦ Ã¼Å©ÇØ¾ß ÇÑ´Ù. 
	// MTopView¿¡¼­µµ Ãâ·ÂÇÒ¶§ NULLÃ¼Å©ÇØ¾ßÇÑ´Ù.
	bool bZoneRelease = false;

//	if (g_pUserInformation->GoreLevel)
	{
		//-------------------------------------------------------
		// Gore ---> not Gore
		//-------------------------------------------------------
		// effectµéÀ» ¹Ù²ãÁØ´Ù.
		//-------------------------------------------------------
		if (!bGoreLevel)
		{
			g_pActionInfoTable->SetChildMode();

			bZoneRelease = true;
		}
	}
//	else
	{
		//-------------------------------------------------------
		// not Gore --> Gore
		//-------------------------------------------------------
		// ´Ù½Ã loadingÇÏ¸é µÈ´Ù.
		//-------------------------------------------------------
		if (bGoreLevel)
		{
			//-----------------------------------
			// Load From File
			//-----------------------------------
			ivfstream actionInfoFile2(FILE_INFO_ACTION_FK, std::ios::binary);
		//	if (!FileOpenBinary(g_pFileDef->getProperty("FILE_INFO_ACTION").c_str(), actionInfoFile2))
		//		return;

			g_pActionInfoTable->LoadFromFile(actionInfoFile2);
			actionInfoFile2.close();

			bZoneRelease = true;
		}
	}

	if(bZoneRelease == true)
	{
		//------------------------------------------------------
		// Small Zone Á¦°Å
		//------------------------------------------------------
		if (g_pZoneSmall != NULL)
		{
			DEBUG_ADD("[ delete SmallZone ]");
			delete g_pZoneSmall;	
			g_pZoneSmall = NULL;
			g_nZoneSmall = ZONEID_NULL;	
			g_bZoneSmallLoadImage = false;
		}			
		
		//------------------------------------------------------
		// Large Zone Á¦°Å
		//------------------------------------------------------
		if (g_pZoneLarge != NULL)
		{
			DEBUG_ADD("[ delete LargeZone ]");
			delete g_pZoneLarge;	
			g_pZoneLarge = NULL;
			g_nZoneLarge = ZONEID_NULL;	
			g_bZoneLargeLoadImage = false;
		}
		
		g_pZone = NULL;
		
	}

	g_pUserInformation->GoreLevel = bGoreLevel;
}

//-----------------------------------------------------------------------------
// Get Direction To Position
//-----------------------------------------------------------------------------
BYTE		
GetDirectionToPosition(int originX, int originY, int destX, int destY)
{
	return MTopView::GetDirectionToPosition(originX, originY, destX, destY);
}

//-----------------------------------------------------------------------------
// Convert Alignment
//-----------------------------------------------------------------------------
int
ConvertAlignment(int alignment2)
{
	int alignment = alignment2;

	// À½¼öÀÎ °æ¿ì..
	if (alignment > 10000)
	{	
		alignment = - (short)(~alignment + 1);

		DEBUG_ADD_FORMAT("Modify AlignmentValue = %d --> %d", alignment2, alignment);
	}

	const int numAlignment = 5;
	int alignmentValue[numAlignment] =
	{
		-7501,		// evil+
		-2501,		// evil
		2500,		// neutral
		7500,		// good
		10000		// good+
	};

	for (int i=0; i<numAlignment; i++)
	{
		if (alignment <= alignmentValue[i])
		{
			return i;
		}
	}

	return 0;
}

//-----------------------------------------------------------------------------
// Convert Duration To Frame
//-----------------------------------------------------------------------------
DWORD
ConvertDurationToFrame(int duration)
{
	// ÃÊ´ç 16 Frame
	// 0.1ÃÊ´ç 1.6 Frame
	// 1 --> 0.1ÃÊ
	// 10 --> 1ÃÊ
	return duration * g_pClientConfig->FPS / 10;
}

//-----------------------------------------------------------------------------
// Convert Millisecond To Frame
//-----------------------------------------------------------------------------
DWORD
ConvertMillisecondToFrame(DWORD ms)
{
	// 1 ms = 1/1000
	// 1000 ms = 1
	// 1 ÃÊ = 16 frame
	return ms * g_pClientConfig->FPS / 1000;
}

//-----------------------------------------------------------------------------
// Convert Duration To Millisecond
//-----------------------------------------------------------------------------
DWORD
ConvertDurationToMillisecond(int duration)
{
	// 1 --> 0.1ÃÊ	
	// 1 --> 100
	return duration * 100;
}

//-----------------------------------------------------------------------------
// Set VampireCreatureType
//-----------------------------------------------------------------------------
// »ç¶÷(³², ¿©), ´Á´ë, ¹ÚÁã..
//-----------------------------------------------------------------------------
int
#if __CONTENTS(__SECOND_TRANSFORTER)
GetVampireCreatureType(int shape, bool bMale, int coatType, DWORD wingItemType)
#else
GetVampireCreatureType(int shape, bool bMale, int coatType)
#endif
{
	DEBUG_ADD_FORMAT("Shape=%d. Male=%d", shape, (int)bMale);
	
	int vampireCreatureType[] = {
		-1, -1,
		CREATURETYPE_VAMPIRE_MALE1,
		CREATURETYPE_VAMPIRE_FEMALE1,
		CREATURETYPE_VAMPIRE_MALE2,
		CREATURETYPE_VAMPIRE_FEMALE2,
		CREATURETYPE_VAMPIRE_MALE3,
		CREATURETYPE_VAMPIRE_FEMALE3,
		CREATURETYPE_VAMPIRE_MALE4,
		CREATURETYPE_VAMPIRE_FEMALE4,
	};

	//--------------------------------------------------
	// CreatureType ¼³Á¤
	//--------------------------------------------------
	switch ( shape )
	{
	case SHAPE_NORMAL :
		{
			int frameID = 0;

			if(bMale)
			{
				frameID = (*g_pItemTable)[ITEM_CLASS_VAMPIRE_COAT][coatType].AddonMaleFrameID;
			}
			else
			{
				frameID = (*g_pItemTable)[ITEM_CLASS_VAMPIRE_COAT][coatType].AddonFemaleFrameID;
			}
			
			return vampireCreatureType[frameID];
		}
		break;

	case SHAPE_BAT :
		return CREATURETYPE_BAT;

	case SHAPE_WOLF :
		return CREATURETYPE_WOLF;

	case SHAPE_WERWOLF :
		return CREATURETYPE_WER_WOLF;

	case SHAPE_VAMPIRE_GHOST :
		return CREATURETYPE_VAMPIRE_GHOST;
#if __CONTENTS(__FAST_TRANSFORTER)
	case SHAPE_FLITTERMOUSE :
		{
#if __CONTENTS(__SECOND_TRANSFORTER)
			if(wingItemType == 0)
				return CREATURETYPE_FLITTERMOUSE;
			else
			if(wingItemType == 1)
				return CREATURETYPE_SHAPE_OF_DEMON;
			else
			if(wingItemType == 2)
				return CREATURETYPE_NEDE;
			else
				if(wingItemType == 3)
					return CREATURETYPE_KLTL;
#else
			return CREATURETYPE_FLITTERMOUSE;
#endif 
		}
#endif //__FAST_TRANSFORTER
	} 

	return SHAPE_MAX;
}


//-----------------------------------------------------------------------------
// Set OustersCreatureType
//-----------------------------------------------------------------------------
// »ç¶÷(³², ¿©), ´Á´ë, ¹ÚÁã..
//-----------------------------------------------------------------------------
int
GetOustersCreatureType(int coatType)
{
	//--------------------------------------------------
	// CreatureType ¼³Á¤
	//--------------------------------------------------
	return CREATURETYPE_OUSTERS;
	//	return (*g_pItemTable)[ITEM_CLASS_VAMPIRE_COAT][coatType].AddonMaleFrameID;
}

//-----------------------------------------------------------------------------
// Set Addon To Slayer
//-----------------------------------------------------------------------------
// NPC º¹ÀåÀ» ÀÔÈù´Ù.
//-----------------------------------------------------------------------------
void
SetAddonToSlayer(MCreatureWear* pCreature, int npcID )
{
	//-------------------------------------------------------------
	// °ª Ã¼Å©
	//-------------------------------------------------------------
	if (npcID >= g_pCreatureTable->GetSize())
	{
		DEBUG_ADD_FORMAT("[Error] SetAddonToSlayerNPC: npcID exceed Max = %d/%d", npcID, g_pCreatureTable->GetSize());
		
		return;
	}

	//-------------------------------------------------------------
	// º¹ÀåÀ» ÇÏ³ªÇÏ³ª ÀÔÈù´Ù.
	//-------------------------------------------------------------
	ITEM_WEARINFO* pInfo = (*g_pCreatureTable)[npcID].pItemWearInfo;

	if (pInfo==NULL)
	{
		DEBUG_ADD_FORMAT("[Error] SetAddonToSlayerNPC: ItemWearInfo is NULL. cType=%d", npcID);
		
		return;
	}
	
	//----------------------------------------	
	// ¸Ó¸®
	//----------------------------------------	
	pCreature->SetAddonHair(g_PacketHairID[pInfo->hair], pInfo->hairColor);

	//----------------------------------------	
	// º¹Àå
	//----------------------------------------	
	MItem* pCoat		= g_pPacketItemJacket[pInfo->jacket];
	MItem* pTrouser		= g_pPacketItemPants[pInfo->pants];
	MItem* pHelm		= g_pPacketItemHelm[pInfo->helmet];
	MItem* pWeapon		= g_pPacketItemWeapon[pInfo->weapon];
	MItem* pShield		= g_pPacketItemShield[pInfo->shield];

#if __CONTENTS(__SECOND_TRANSFORTER)
	int motorcycleInfo = pInfo->motorcycle;
	
	if(motorcycleInfo==4)
		motorcycleInfo+=(pCreature->GetWingItemType()-8);
	if(motorcycleInfo>=MOTORCYCLE_MAX)
			motorcycleInfo=MOTORCYCLE_MAX-1;

	MItem* pMotorcycle	= g_pPacketItemMotorcycle[motorcycleInfo];
#else
	MItem* pMotorcycle	= g_pPacketItemMotorcycle[pInfo->motorcycle];
#endif //__SECOND_TRANSFORTER

	// »ö±òÁ¤º¸ ¼³Á¤...
	//pCoat->SetItemOptionList( getHelmetColor() );
	//
	//
	//

	pCreature->SetAddonItem( pCoat );
	pCreature->SetAddonItem( pTrouser );
	pCreature->SetAddonItem( pHelm );
	pCreature->SetAddonItem( pWeapon );
	pCreature->SetAddonItem( pShield );
	pCreature->SetAddonItem( pMotorcycle );
	

	/*
	// ¿Þ¼Õ¿£ ¹æÆÐ
	if (pInfo->getWeaponType()==WEAPON_SWORD_SHIELD || pInfo->getWeaponType()==WEAPON_SHIELD)
	{
		pCreature->SetAddonItem( pShield );

		if (pShield!=NULL)
		{
			pCreature->SetAddonColorSet1( ADDON_LEFTHAND, pInfo->getShieldColor() );
		}
	}
	*/

	//----------------------------------------	
	// »ö±ò ¼³Á¤
	//----------------------------------------	
	if (pCoat!=NULL)
	{
		pCreature->SetAddonColorSet2( ADDON_COAT, pInfo->jacketColor );
	}

	pCreature->SetAddonColorSet1( ADDON_COAT, pInfo->skinColor );
		

	if (pTrouser!=NULL)
	{	
		pCreature->SetAddonColorSet1( ADDON_TROUSER, pInfo->pantsColor );
	}
	
	pCreature->SetAddonColorSet2( ADDON_TROUSER, pInfo->skinColor );
		
	if (pHelm!=NULL)
	{	
		pCreature->SetAddonColorSet1( ADDON_HELM, pInfo->helmetColor );
	}

	if (pWeapon!=NULL)
	{	
		pCreature->SetAddonColorSet1( ADDON_RIGHTHAND, pInfo->weaponColor );	
	}

	if (pShield!=NULL)
	{	
		pCreature->SetAddonColorSet1( ADDON_LEFTHAND, pInfo->shieldColor );	
	}

	if (pMotorcycle!=NULL)
	{
		pCreature->SetAddonColorSet1( ADDON_MOTOR, pInfo->motorcycleColor );
	}

	//----------------------------------------	
	// °ø°Ý ¼Óµµ ¼³Á¤
	//----------------------------------------	
//	pCreature->SetStatus( MODIFY_ALIGNMENT, pInfo->getAlignment() );
//	pCreature->SetWeaponSpeed( pInfo->getAttackSpeed() );

	DEBUG_ADD("[SetAddonToSlayer] NPC Wear OK");
}

//-----------------------------------------------------------------------------
// Set Addon To Slayer
//-----------------------------------------------------------------------------
// ¸Ó¸®
//-----------------------------------------------------------------------------
void		
SetAddonToSlayer(MCreatureWear* pCreature, const PCSlayerInfo2* pInfo)
{		
	//--------------------------------------------------
	// ¸Ó¸® ¼³Á¤
	//--------------------------------------------------
	// slayer³² 
	pCreature->SetAddonHair(g_PacketHairID[(int)pInfo->getHairStyle()], pInfo->getHairColor());		

	if(pInfo->getAdvancementLevel() > 0) // ½ÂÁ÷ Ä³¸¯ÅÍ
	{
		pCreature->SetAddonColorSet1( ADDON_COAT, pInfo->getHairColor () );
		pCreature->SetAddonColorSet1( ADDON_TROUSER, pInfo->getSkinColor() );
	}
	else
	{
		pCreature->SetAddonColorSet1( ADDON_COAT, pInfo->getSkinColor() );
		pCreature->SetAddonColorSet2( ADDON_TROUSER, pInfo->getSkinColor() );
	}
}

//-----------------------------------------------------------------------------
// Set Addon To Slayer
//-----------------------------------------------------------------------------
// º¹Àå
//-----------------------------------------------------------------------------
void		
SetAddonToSlayer(MCreatureWear* pCreature, const PCSlayerInfo3* pInfo)
{	
	/*
	HairStyle getHairStyle () const throw () 
	HelmetType getHelmetType () const throw () 
	JacketType getJacketType () const throw () 
	PantsType getPantsType () const throw () 
	WeaponType getWeaponType () const throw ()
	MotorcycleType getMotorcycleType () const throw ()
	
	Color_t getHairColor () const throw () 
	Color_t getSkinColor () const throw () 
	Color_t getHelmetColor ( ColorType colorType = MAIN_COLOR ) const throw () 
	Color_t getJacketColor ( ColorType colorType = MAIN_COLOR ) const throw () 
	Color_t getPantsColor ( ColorType colorType = MAIN_COLOR ) const throw () 
	Color_t getWeaponColor ( ColorType colorType = MAIN_COLOR ) const throw () 
	Color_t getShieldColor ( ColorType colorType = MAIN_COLOR ) const throw () 
	Color_t getMotorcycleColor ( ColorType colorType = MAIN_COLOR ) const throw () 
	*/


	//----------------------------------------	
	//
	// option°ú color´Â µû·Î ÁöÁ¤ÇØ¾ß ÇÑ´Ù.
	//
	//----------------------------------------	
	//Color_t getHairColor () const throw () 
	//Color_t getSkinColor () const throw () 
	//Color_t getHelmetColor ( ColorType colorType = MAIN_COLOR ) const throw () 
	//Color_t getJacketColor ( ColorType colorType = MAIN_COLOR ) const throw () 
	//Color_t getPantsColor ( ColorType colorType = MAIN_COLOR ) const throw () 
	//Color_t getWeaponColor ( ColorType colorType = MAIN_COLOR ) const throw () 
	//Color_t getShieldColor ( ColorType colorType = MAIN_COLOR ) const throw () 
	//Color_t getMotorcycleColor ( ColorType colorType = MAIN_COLOR ) const throw () 

	//----------------------------------------	
	// ¸Ó¸®
	//----------------------------------------	
	pCreature->SetAddonHair(g_PacketHairID[pInfo->getHairStyle()], pInfo->getHairColor());		

	//----------------------------------------	
	// º¹Àå
	//----------------------------------------	
	//MItem* pCoat		= g_pPacketItemJacket[pInfo->getJacketType()];
	//MItem* pTrouser		= g_pPacketItemPants[pInfo->getPantsType()];
	//MItem* pHelm		= g_pPacketItemHelm[pInfo->getHelmetType()];

	MItem* pCoat		= g_pPacketItemJacket[pInfo->getYi()];
	MItem* pTrouser		= g_pPacketItemPants[pInfo->getKu()];
	MItem* pHelm		= g_pPacketItemHelm[pInfo->getTou()];
	MItem* pWeapon		= g_pPacketItemWeapon[pInfo->getWuqi()];
	MItem* pShield		= g_pPacketItemShield[pInfo->getDun()];
	MItem* pShoulder	= g_pPacketItemShoulder[pInfo->getJian()];

	//MItem* pWeapon		= g_pPacketItemWeapon[pInfo->getWeaponType()];
	//MItem* pShield		= g_pPacketItemShield[pInfo->getShieldType()];

#if __CONTENTS(__SECOND_TRANSFORTER)
	//int motorcycleInfo = pInfo->getMotorcycleType();
	int motorcycleInfo = pInfo->getMoto();
	
	if(motorcycleInfo==4)
		motorcycleInfo+=(pCreature->GetWingItemType()-8);
	if(motorcycleInfo>=MOTORCYCLE_MAX)
		motorcycleInfo=MOTORCYCLE_MAX-1;

	MItem* pMotorcycle	= g_pPacketItemMotorcycle[motorcycleInfo];
#else
	MItem* pMotorcycle	= g_pPacketItemMotorcycle[pInfo->getMoto()];
#endif //__SECOND_TRANSFORTER

	//MItem* pShoulder	= g_pPacketItemShoulder[pInfo->getShoulderType()];

	// »ö±òÁ¤º¸ ¼³Á¤...
	//pCoat->SetItemOptionList( getHelmetColor() );
	//
	//
	//

	pCreature->SetAddonItem( pCoat );
	pCreature->SetAddonItem( pTrouser );
	pCreature->SetAddonItem( pHelm );
	pCreature->SetAddonItem( pWeapon );
	pCreature->SetAddonItem( pShield );
	pCreature->SetAddonItem( pMotorcycle );

	pCreature->SetAddonItem( pShoulder );

	

	/*
	// ¿Þ¼Õ¿£ ¹æÆÐ
	if (pInfo->getWeaponType()==WEAPON_SWORD_SHIELD || pInfo->getWeaponType()==WEAPON_SHIELD)
	{
		pCreature->SetAddonItem( pShield );

		if (pShield!=NULL)
		{
			pCreature->SetAddonColorSet1( ADDON_LEFTHAND, pInfo->getShieldColor() );
		}
	}
	*/

	bool bAdvancementCharacter = pInfo->getAdvancementLevel() > 0;

	//----------------------------------------	
	// »ö±ò ¼³Á¤
	//----------------------------------------	
	if (pCoat!=NULL)
	{
		pCreature->SetAddonColorSet2( ADDON_COAT, pInfo->getJacketColor() );
	}

	if(bAdvancementCharacter) // ½ÂÁ÷ Ä³¸¯ÅÍ
	{
		pCreature->SetAddonColorSet1( ADDON_COAT, pInfo->getHairColor () );
	}
	else
	{
		pCreature->SetAddonColorSet1( ADDON_COAT, pInfo->getSkinColor() );
	}
//	pCreature->SetAddonColorSet1( ADDON_COAT, pInfo->getSkinColor() );
	

	if(bAdvancementCharacter) // ½ÂÁ÷ Ä³¸¯ÅÍ
	{
		if (pTrouser!=NULL)
			pCreature->SetAddonColorSet2( ADDON_TROUSER, pInfo->getPantsColor() );
	
		pCreature->SetAddonColorSet1( ADDON_TROUSER, pInfo->getSkinColor() );
	}
	else
	{
		if (pTrouser!=NULL)
			pCreature->SetAddonColorSet1( ADDON_TROUSER, pInfo->getPantsColor() );
	
		pCreature->SetAddonColorSet2( ADDON_TROUSER, pInfo->getSkinColor() );
	}
		
	if (pHelm!=NULL)
	{	
		pCreature->SetAddonColorSet1( ADDON_HELM, pInfo->getHelmetColor() );
		pCreature->SetAddonColorSet2( ADDON_HELM, pInfo->getHelmetColor() );
	}

	if (pWeapon!=NULL)
	{	
		pCreature->SetAddonColorSet1( ADDON_RIGHTHAND, pInfo->getWeaponColor() );	
		pCreature->SetAddonColorSet2( ADDON_RIGHTHAND, pInfo->getWeaponColor() );	
	}

	if (pShield!=NULL)
	{	
		pCreature->SetAddonColorSet1( ADDON_LEFTHAND, pInfo->getShieldColor() );	
		pCreature->SetAddonColorSet2( ADDON_LEFTHAND, pInfo->getShieldColor() );	
	}

	if (pMotorcycle!=NULL)
	{
		pCreature->SetAddonColorSet1( ADDON_MOTOR, pInfo->getMotorcycleColor() );
		pCreature->SetAddonColorSet2( ADDON_MOTOR, pInfo->getMotorcycleColor() );
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
		//¸¸ÀÏ, ½½·¹ÀÌ¾îÀÇ ½Å±ÔÀÌµ¿¼ö´ÜÀÌ¶ó¸é..... 
		//4¿ù 30ÀÏ Å×¼· / 5¿ù 7ÀÏ º»¼· ÆÐÄ¡±îÁö´Â ÀÓÀÇ·Î Color°ªÀ» 0À¸·Î ¼¼ÆÃÇÑ´Ù.
		//ÃßÈÄ, ½Å±ÔÀÌµ¿¼ö´Ü¿¡ ´ëÇÑ Color Enchant±â´ÉÀÌ Ãß°¡µÉ ¶§.. (ÇöÀç)½½·¹ÀÌ¾î ¹ÙÀÌÅ©¿¡ ´ëÇØ¼­ ColorÃ³¸®°¡ ¹ÌÈíÇÑ ºÎºÐÀ» º¸¿ÏÇÏ°í, ±× ¶§´Â ÀÌ ºÎºÐÀÇ Ã³¸®¸¦ »©µµ·Ï ÇÏ³®.
#if __CONTENTS(__FAST_TRANSFORTER)
		if (pMotorcycle->GetItemType () == 8 )
		{
			pCreature->SetAddonColorSet1( ADDON_MOTOR, 379 );
			pCreature->SetAddonColorSet2( ADDON_MOTOR, 379 );
		}
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
		if (pMotorcycle->GetItemType () == 9 )
		{
			pCreature->SetAddonColorSet1( ADDON_MOTOR, 379 );
			pCreature->SetAddonColorSet2( ADDON_MOTOR, 379 );
		}
		if (pMotorcycle->GetItemType () == 10 )
		{
			pCreature->SetAddonColorSet1( ADDON_MOTOR, 379 );
			pCreature->SetAddonColorSet2( ADDON_MOTOR, 379 );
		}
		if (pMotorcycle->GetItemType () == 11 )
		{
			pCreature->SetAddonColorSet1( ADDON_MOTOR, 379 );
			pCreature->SetAddonColorSet2( ADDON_MOTOR, 379 );
		}
#endif //__SECOND_TRANSFORTER
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
	}

	//----------------------------------------	
	// °ø°Ý ¼Óµµ ¼³Á¤
	//----------------------------------------	
	pCreature->SetWeaponSpeed( pInfo->getAttackSpeed() );
}

//-----------------------------------------------------------------------------
// Add Item To Zone
//-----------------------------------------------------------------------------
// bDroppingÀº ¹æ±Ý ¶³¾îÁö±â ½ÃÀÛÇÏ´Â°ÇÁö...(true)
// ¶³¾îÁ® ÀÖ´ø°ÇÁö(false)¸¦ °áÁ¤ÇÏ´Â °ÍÀÌ´Ù.
//
// »ý¼ºµÈ ItemÀ» returnÇÑ´Ù.
// ¹º°¡ ´Ù¸¥ ÀÛ¾÷À» ÇÏ±â À§ÇØ¼­.. -_-;
//-----------------------------------------------------------------------------
MItem*
AddItemToZone(GCAddItemToZone* pPacket, BOOL bDropping)
{
#if __CONTENTS(__PCITEMINFO)
	PCItemInfo* pPCItemInfo = pPacket->GetPCItemInfo();
#else //__PCITEMINFO
	GCAddItemToZone* pPCItemInfo =  pPacket;
#endif //__PCITEMINFO
	//------------------------------------------------
	// ItemÀ» °¡Áö°í ÀÖ´Ù°¡ ZoneÀ¸·Î ¶³¾î¶ß¸®´Â °æ¿ì
	//------------------------------------------------
	// ¶³¾î¶ß¸±·Á´Â item
	if (g_pPlayer->IsItemCheckBufferDropToZone())
	{
		//---------------------------------------------
		// ¶³¾î¶ß¸±·Á´Â item
		//---------------------------------------------
		MItem* pItem = g_pPlayer->GetItemCheckBuffer();
	
		if (pItem!=NULL)
		{
			//---------------------------------------------
			// °°Àº IDÀÎ °æ¿ì¸¸ ¶³¾î¶ß·Á¾ß ÇÑ´Ù....
			//---------------------------------------------
			if (pItem->GetID() == pPCItemInfo->getObjectID())
			{	
//				__BEGIN_HELP_EVENT
//					if (pItem->GetItemClass()==ITEM_CLASS_MONEY)
//					{
//						// [µµ¿ò¸»] µ· ¹ö¸± ¶§
////						ExecuteHelpEvent( HE_ITEM_DROP_MONEY );	
//					}
//				__END_HELP_EVENT
				

				DEBUG_ADD_FORMAT("[Try To Drop Item to Zone] ID=%d, xy=(%d, %d)", pPCItemInfo->getObjectID(), pPacket->getX(), pPacket->getY());
				
				//---------------------------------------------
				// item check buffer¸¦ ¾ø¾ÖÁØ´Ù.
				//---------------------------------------------
				g_pPlayer->ClearItemCheckBuffer();

				//---------------------------------------------
				// mouse cursor¿¡¼­ Á¦°Å
				//---------------------------------------------
				UI_DropItem();

				// ¶³¾î¶ß¸®´Â ÁÂÇ¥ ¼³Á¤
				pItem->SetPosition( pPacket->getX(), pPacket->getY() );

				// Zone¿¡ ItemÀ» Ãß°¡ÇÑ´Ù.
				if (!g_pZone->AddItem( pItem, bDropping ))
				{
					DEBUG_ADD_FORMAT("[Can't Drop Item] ID=%d, xy=(%d, %d)", pPCItemInfo->getObjectID(), pPacket->getX(), pPacket->getY());
					
					SAFE_DELETE( pItem );

					return NULL;
				}

				//------------------------------------------------------------------------
				// ±â¼ú ¾ÆÀÌÄÜ Àç¼³Á¤..
				//------------------------------------------------------------------------
				// ¼º¼ö, ÆøÅº
				//------------------------------------------------------------------------
				CheckItemForSkillIcon(pItem);

				DEBUG_ADD_FORMAT("[Drop Item to Zone OK] ID=%d, xy=(%d, %d)", pPCItemInfo->getObjectID(), pPacket->getX(), pPacket->getY());
				
				return pItem;
			}
		}
		else
		{
			DEBUG_ADD("[Can't Drop] Item CheckBuffer NULL");
			
			return NULL;
		}
	}

	//------------------------------------------------
	// ItemÀ» »ý¼ºÇØ¼­ Zone¿¡ Ãß°¡ÇÑ´Ù.
	//------------------------------------------------
	DEBUG_ADD("Create NEW Item");
	
	MItem* pItem;

	if ( pPCItemInfo->getItemClass() >= g_pItemTable->GetSize() ||
		(*g_pItemTable)[pPCItemInfo->getItemClass()].GetSize() <= pPCItemInfo->getItemType() )
	{
		SendBugReport("[PacketFunction::AddItemToZone,%d] %d,%d",__LINE__,pPCItemInfo->getItemClass(), pPCItemInfo->getItemType() );
		return NULL;
	}

	pItem = MItem::NewItem( (enum ITEM_CLASS)pPCItemInfo->getItemClass() );
	pItem->SetItemType( pPCItemInfo->getItemType() );
	pItem->SetItemOptionList( pPCItemInfo->getOptionType() );
	pItem->SetItemGTwoOptionList( pPCItemInfo->getGTwoOptionType() );
#if __CONTENTS(__PET_MIXINGFORGE)
	pItem->SetPetMixingOptionList(pPCItemInfo->getMixOptionType());
#endif //__PET_MIXINGFORGE
	pItem->SetID( pPCItemInfo->getObjectID() );		

	pItem->SetPosition( pPacket->getX(), pPacket->getY() );

	// °³¼ö ¼³Á¤
	pItem->SetNumber( 1 );

	// durability
	pItem->SetCurrentDurability( pPCItemInfo->getDurability() );
	pItem->SetSilver( pPCItemInfo->getSilver() );
	pItem->SetGrade( pPCItemInfo->getGrade() );
	pItem->SetEnchantLevel( pPCItemInfo->getEnchantLevel() );
#if __CONTENTS(__PCITEMINFO)
	pItem->SetItemThirdOptionList(pPCItemInfo->getThirdOptionType());
	pItem->SetItemThirdOptionType(pPCItemInfo->getThirdEnchantType());
#endif //__PCITEMINFO
	//-------------------------------------------------
	// ÀÌ¸§ ¼³Á¤ : µ·ÀÎ °æ¿ì ¾×¼ö Ç¥½Ã
	//-------------------------------------------------
	if (pItem->GetItemClass()==ITEM_CLASS_MONEY || pItem->GetItemClass()== ITEM_CLASS_CHECK_MONEY)
	{
		char str[128];

		int lowWord = pItem->GetCurrentDurability();
		int highWord = pItem->GetSilver();
		int money = (highWord << 16) | lowWord;
		
		sprintf(str, (*g_pGameStringTable)[STRING_DRAW_ITEM_NAME_MONEY].GetString(), pItem->GetName(), money);

		pItem->SetName( str );
	}


	//------------------------------------------
	// °³¼ö
	//------------------------------------------
	// ÃÑÀÎ °æ¿ì
	//------------------------------------------
	if (pItem->IsGunItem())
	{
		MMagazine* pMagazine = (MMagazine*)MItem::NewItem( (ITEM_CLASS)ITEM_CLASS_MAGAZINE );

		// ÀÇ¹Ì ¾øÀ½ - -;
		pMagazine->SetID( 0 );

		// ÀÌ°Å´Â ÃÑ¿¡ ¸ÂÃç¼­ ÇØÁà¾ßµÈ´Ù.
		for (int j=0; j<(*g_pItemTable)[ITEM_CLASS_MAGAZINE].GetSize(); j++)			
		{
			pMagazine->SetItemType(	j );

			if (pMagazine->IsInsertToItem( pItem ))
			{
				break;
			}
		}
		
		if(pPCItemInfo->getSilver())
			pMagazine->SetItemType( pMagazine->GetItemType()+8);
		// ¾î¿¹~ ÀºÅºÈ¯ ÇÏµåÄÚµù by ¾¦°«

		// ÀÇ¹Ì ¾øÀ½
		pMagazine->ClearItemOption();
	
		// ÅºÃ¢ °³¼ö
		pMagazine->SetNumber( pPCItemInfo->getItemNum() );

		//------------------------------------
		// ÅºÃ¢ ¼³Á¤
		//------------------------------------
		MGunItem* pGunItem = (MGunItem*)pItem;
		pGunItem->SetMagazine( pMagazine );
	}		
	//------------------------------------------
	// ÃÑÀÌ ¾Æ´Ñ °æ¿ì
	//------------------------------------------
	else
	{
		if (!pItem->IsChargeItem())
		{
			pItem->SetNumber( pPCItemInfo->getItemNum() );		
		}
	}

	//------------------------------------------
	//
	// Item¿¡ ´Ù¸¥ itemµéÀÌ µé¾îÀÖ´Â °æ¿ì
	//
	//------------------------------------------
	if (pPCItemInfo->getListNum()!=0)
	{
		DEBUG_ADD_FORMAT("This Item has Sub item(s) : size=%d", pPCItemInfo->getListNum());
		
		//------------------------------------------
		// BeltÀÎ °æ¿ì
		//------------------------------------------
		if (pItem->GetItemClass()==ITEM_CLASS_BELT)
		{
			MBelt* pBelt = (MBelt*)pItem;

			int size = pPCItemInfo->getListNum();
					
			for (int i=0; i<size; i++)
			{
				SubItemInfo * pSubItemInfo = pPCItemInfo->popFrontListElement();

				if (pSubItemInfo==NULL)
				{
					DEBUG_ADD("[Error] Sub Item is NULL");
				}
				else
				{
					//------------------------------------------
					// Sub ItemÀÇ Á¤º¸¸¦ ¼³Á¤ÇÑ´Ù.
					//------------------------------------------
					if ( pSubItemInfo->getItemClass() >= g_pItemTable->GetSize() ||
						(*g_pItemTable)[pSubItemInfo->getItemClass()].GetSize() <= pSubItemInfo->getItemType() )
					{
						SendBugReport("[PacketFunction::AddItemToZone,%d] %d,%d",__LINE__,pSubItemInfo->getItemClass(), pSubItemInfo->getItemType() );
						continue;
					}
					MItem* pSubItem = MItem::NewItem( (enum ITEM_CLASS)pSubItemInfo->getItemClass() );
					pSubItem->SetItemType( pSubItemInfo->getItemType() );
					//pItem->SetItemOption( pSubItemInfo->getOptionType() );

					pSubItem->SetID( pSubItemInfo->getObjectID() );		

					pSubItem->SetNumber( pSubItemInfo->getItemNum() );			

					//------------------------------------------
					// BeltÀÇ Á¤ÇØÁø slot¿¡ itemÀ» Ãß°¡½ÃÅ²´Ù.
					//------------------------------------------
					pBelt->AddItem( pSubItem, pSubItemInfo->getSlotID() );

					delete pSubItemInfo;
				}
			}
		}else if (pItem->GetItemClass()==ITEM_CLASS_OUSTERS_ARMSBAND)
		{
			MOustersArmsBand* pBelt = (MOustersArmsBand*)pItem;
			
			int size = pPCItemInfo->getListNum();
			
			for (int i=0; i<size; i++)
			{
				SubItemInfo * pSubItemInfo = pPCItemInfo->popFrontListElement();
				
				if (pSubItemInfo==NULL)
				{
					DEBUG_ADD("[Error] Sub Item is NULL");
				}
				else
				{
					//------------------------------------------
					// Sub ItemÀÇ Á¤º¸¸¦ ¼³Á¤ÇÑ´Ù.
					//------------------------------------------
					if ( pSubItemInfo->getItemClass() >= g_pItemTable->GetSize() ||
						(*g_pItemTable)[pSubItemInfo->getItemClass()].GetSize() <= pSubItemInfo->getItemType() )
					{
						SendBugReport("[PacketFunction::AddItemToZone,%d] %d,%d",__LINE__,pSubItemInfo->getItemClass(), pSubItemInfo->getItemType() );
						continue;
					}
					MItem* pSubItem = MItem::NewItem( (enum ITEM_CLASS)pSubItemInfo->getItemClass() );
					pSubItem->SetItemType( pSubItemInfo->getItemType() );
					//pItem->SetItemOption( pSubItemInfo->getOptionType() );
					
					pSubItem->SetID( pSubItemInfo->getObjectID() );		
					
					pSubItem->SetNumber( pSubItemInfo->getItemNum() );			
					
					//------------------------------------------
					// BeltÀÇ Á¤ÇØÁø slot¿¡ itemÀ» Ãß°¡½ÃÅ²´Ù.
					//------------------------------------------
					pBelt->AddItem( pSubItem, pSubItemInfo->getSlotID() );
					
					delete pSubItemInfo;
				}
			}
		}
		else
		{
			DEBUG_ADD_FORMAT("This Item can't have Sub item : class=%d", (int)pItem->GetItemClass());
		}
	}

	//------------------------------------------------	
	// Zone¿¡ Ãß°¡ÇÑ´Ù.
	//------------------------------------------------	
	if (!g_pZone->AddItem( pItem, bDropping ))
	{
		//------------------------------------------------	
		// Zone¿¡ Ãß°¡µÇÁö ¾ÊÀº °æ¿ì
		//------------------------------------------------	
		DEBUG_ADD_FORMAT("[Can't Add Item] ID=%d, xy=(%d, %d)", pPCItemInfo->getObjectID(), pPacket->getX(), pPacket->getY());
		
		// ÀÌÀü¿¡ ÀÖ´ø°É Á¦°ÅÇÑ´Ù.
		TYPE_OBJECTID oldID = g_pZone->GetItemID( pItem->GetX(), pItem->GetY() );

		//------------------------------------------------	
		// ±× ÀÚ¸®¿¡´Â ´Ù¸¥ ¾ÆÀÌÅÛÀÌ ÀÖ´Â °æ¿ì...
		//------------------------------------------------	
		if (oldID!=OBJECTID_NULL)
		{
			DEBUG_ADD_FORMAT("Exist Item ID = %d", oldID);
		
			//------------------------------------------------	
			// ´Ù¸¥ ¾ÆÀÌÅÛÀÎ °æ¿ì.. ±âÁ¸¿¡°É Á¦°ÅÇÑ´Ù.
			//------------------------------------------------	
			if (oldID!=pItem->GetID())
			{
				if (g_pZone->RemoveItem( oldID ))
				{
					DEBUG_ADD_FORMAT("Remove Old Item(id=%d) & Add", oldID);
					
					// ´Ù½Ã Ãß°¡ÇÑ´Ù.
					if (!g_pZone->AddItem( pItem, bDropping ))
					{
						DEBUG_ADD("[Can't Re-Add Item]");
						
						// memory Á¦°Å
						delete pItem;
					}		
				}
				else
				{
					DEBUG_ADD_FORMAT("[Can't Remove Old Item] id=%d", oldID);
					
					// memory Á¦°Å
					delete pItem;
				}		
			}
			//------------------------------------------------	
			// °°Àº itemÀÎ °æ¿ì..
			//------------------------------------------------	
			else
			{
				DEBUG_ADD_FORMAT("[Error] Already Exist Same Item");
				
				delete pItem;
			}
		}
		//------------------------------------------------	
		// ±× ÀÚ¸®¿¡ ¾ÆÀÌÅÛÀÌ ¾ø´Ù¸é...
		// ´Ù¸¥ ÀÚ¸®¿¡ °°Àº objectID¸¦ °¡Áø ¾ÆÀÌÅÛÀÌ ÀÖ´Ù´Â ÀÇ¹ÌÀÌ´Ù.
		//------------------------------------------------	
		else
		{
			if (g_pZone->RemoveItem( pPCItemInfo->getObjectID() ))
			{
				DEBUG_ADD_FORMAT("Remove Old Item(id=%d) & Add", pPCItemInfo->getObjectID());
				
				// ´Ù½Ã Ãß°¡ÇÑ´Ù.
				if (!g_pZone->AddItem( pItem, bDropping ))
				{
					DEBUG_ADD("[Can't Re-Add Item2]");
					
					// memory Á¦°Å
					delete pItem;
				}		
			}
			else
			{
				DEBUG_ADD_FORMAT("[Can't Remove Old Item2] id=%d", pPCItemInfo->getObjectID());
				
				// memory Á¦°Å
				delete pItem;
			}		
		}

		return NULL;
	}

	// [µµ¿ò¸»] ¾ÆÀÌÅÛ ¶³¾îÁú ¶§
//	__BEGIN_HELP_EVENT
//		ExecuteHelpEvent( HE_ITEM_APPEAR );	
//	__END_HELP_EVENT

	return pItem;
}

//-----------------------------------------------------------------------------
// SkillToSector
//-----------------------------------------------------------------------------
void
SkillToSector(TYPE_ACTIONINFO nActionInfo, TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY, int dir, DWORD delayFrame, MActionResult* pResult)
{
	POINT point = MTopView::MapToPixel(sX, sY);

	//------------------------------------------------------
	//
	//				¸ñÇ¥ »ý¼º
	//
	//------------------------------------------------------
	// »ç¿ëÀÚ°¡ ¾ø¾î¼­ .. -_-;;
	//------------------------------------------------------
	MEffectTarget* pEffectTarget = new MEffectTarget( (*g_pActionInfoTable)[nActionInfo].GetSize() );

	pEffectTarget->Set( point.x, point.y, 0, OBJECTID_NULL );

	pEffectTarget->SetDelayFrame( delayFrame );

	// °á°ú ¼³Á¤
	pEffectTarget->SetResult( pResult );




	int z = 0;
	//--------------------------------------------------------
	// °øÁß¿¡¼­ ½ÃÀÛÇÏ´Â °æ¿ì
	//--------------------------------------------------------
	if ((*g_pActionInfoTable)[nActionInfo].IsStartSky())
	{
		z	= (*g_pActionInfoTable)[nActionInfo].GetValue();
	}

	//--------------------------------------------------------
	//
	//                   Effect»ý¼º		
	//
	//--------------------------------------------------------
	g_pEffectGeneratorTable->Generate(
			point.x, point.y, z,				// ½ÃÀÛ À§Ä¡
			dir, 		// ¹æÇâ
			1,					// power
			nActionInfo,		//	ActionInfoTableÁ¾·ù,
			pEffectTarget		// ¸ñÇ¥ Á¤º¸
	);	
}

//-----------------------------------------------------------------------------
// Add Vampire Portal
//-----------------------------------------------------------------------------
void		
AddVampirePortal(
				int serverID,								// ÀÌÆåÆ®ÀÇ OID
				const char* ownerName,								// Æ÷Å» ÁÖÀÎ
				TYPE_SECTORPOSITION sX, TYPE_SECTORPOSITION sY,		// Æ÷Å»ÀÇ ÁÂÇ¥
				DWORD delayFrame,							// Æ÷Å»ÀÇ Áö¼Ó ½Ã°£
				
				// ¸ñÇ¥ Á¤º¸
				int zoneID,							// Æ÷Å»ÀÇ ¸ñÇ¥ Á¸ ID
				TYPE_SECTORPOSITION zoneX,			// Æ÷Å»ÀÇ ¸ñÇ¥ ÁÂÇ¥ x
				TYPE_SECTORPOSITION zoneY,			// Æ÷Å»ÀÇ ¸ñÇ¥ ÁÂÇ¥ y

				bool bStartFromMainNode )
{
	int nActionInfo = RESULT_MAGIC_BLOODY_TUNNEL;

	if ((*g_pActionInfoTable)[nActionInfo].GetSize()!=0)
	{
		//--------------------------------------------------------
		//
		//					Effect ¸ñÇ¥ ¼³Á¤
		//
		//--------------------------------------------------------
		MPortalEffectTarget* pEffectTarget = new MPortalEffectTarget( (*g_pActionInfoTable)[nActionInfo].GetSize() );

		pEffectTarget->Set( 0, 0, 0, OBJECTID_NULL );
		pEffectTarget->SetServerID( serverID );
		pEffectTarget->SetOwnerName( ownerName );
		pEffectTarget->SetPortal( zoneID, zoneX, zoneY );

		//--------------------------------------------------------
		// Áö¼Ó ½Ã°£ ¼³Á¤
		//--------------------------------------------------------
		pEffectTarget->SetDelayFrame( delayFrame );		

		//--------------------------------------------------------
		//
		//				Main Node¸¦ Ã£´Â´Ù.
		//
		//--------------------------------------------------------
		if (bStartFromMainNode)
		{
			if ((*g_pActionInfoTable)[ nActionInfo ].HasMainNode())
			{
				// main node°¡ ÀÖÀ¸¸é main nodeºÎÅÍ ½ÃÀÛÇÏ°Ô ÇÑ´Ù.
				for (int i=0; i<(*g_pActionInfoTable)[ nActionInfo ].GetMainNode(); i++)
				{
					pEffectTarget->NextPhase();
				}			
			}		
		}
		
		//--------------------------------------------------------
		//
		//					½ÃÀÛ À§Ä¡¸¦ °áÁ¤ÇÑ´Ù.
		//
		//--------------------------------------------------------
		POINT point;	
		int x,y,z, dir = DIRECTION_DOWN;

		point = MTopView::MapToPixel(sX, sY);
		x = point.x;
		y = point.y;
		z = 0;
	
		//--------------------------------------------------------
		//
		//                   Effect»ý¼º		
		//
		//--------------------------------------------------------
		g_pEffectGeneratorTable->Generate(
				x,y,z,				// ½ÃÀÛ À§Ä¡
				dir, 				// ¹æÇâ
				1,					// power
				nActionInfo,		//	ActionInfoTableÁ¾·ù,
				pEffectTarget		// ¸ñÇ¥ Á¤º¸
		);	
		

		DEBUG_ADD_FORMAT("[AddVampirePortal] ai=%d", nActionInfo);
	}
}

//-----------------------------------------------------------------------------
// Execute ActionInfo From MainNode
//-----------------------------------------------------------------------------
// MainNodeºÎÅÍ ±â¼úÀ» ½ÇÇàÇÑ´Ù.
//-----------------------------------------------------------------------------
void
ExecuteActionInfoFromMainNode(
			TYPE_ACTIONINFO nActionInfo,										// »ç¿ë ±â¼ú ¹øÈ£
		
			TYPE_SECTORPOSITION startX, TYPE_SECTORPOSITION startY, int startZ, // ±â¼ú »ç¿ëÇÏ´Â »ç¶÷(?) 
			int direction,														// »ç¿ë ¹æÇâ
			
			TYPE_OBJECTID targetID,												// ¸ñÇ¥¿¡ ´ëÇÑ Á¤º¸
			TYPE_SECTORPOSITION targetX, TYPE_SECTORPOSITION targetY, int targetZ, 
			
			DWORD delayFrame,													// ±â¼úÀÇ (³²Àº) Áö¼Ó ½Ã°£		
			
			MActionResult* pActionResult,										// °á°ú Á¤º¸

			bool bStartFromMainNode,											// MainNodeºÎÅÍ ½ÃÀÛÇÏ´Â°¡?

			int sX, int sY)		// ÁÂÇ¥ º¸Á¤
{

	if (nActionInfo==ACTIONINFO_NULL)
	{
		if (pActionResult!=NULL)
		{
			delete pActionResult;
		}
		return;
	}

	if( nActionInfo >= g_pActionInfoTable->GetSize() )
	{
		DEBUG_ADD_FORMAT("[ExecuteActionInfoFromMainNode] skill type error %d", nActionInfo );
		return;
	}

	if ((*g_pActionInfoTable)[nActionInfo].GetSize()!=0)
	{
		POINT point;	

		//--------------------------------------------------------
		// ¸ñÇ¥ À§Ä¡ PixelÁÂÇ¥
		//--------------------------------------------------------
		point = MTopView::MapToPixel(targetX, targetY);

		//--------------------------------------------------------
		//
		//					Effect ¸ñÇ¥ ¼³Á¤
		//
		//--------------------------------------------------------
		MEffectTarget* pEffectTarget = new MEffectTarget( (*g_pActionInfoTable)[nActionInfo].GetSize() );

		pEffectTarget->Set( point.x, point.y, targetZ, targetID );

		//--------------------------------------------------------
		// Áö¼Ó ½Ã°£ ¼³Á¤
		//--------------------------------------------------------
		pEffectTarget->SetDelayFrame( delayFrame );		

		// °á°ú ¼³Á¤ : °á°ú Ã³¸®´Â EffectGenerator¿¡ ¸Ã±ä´Ù.
		pEffectTarget->SetResult( pActionResult );

		//--------------------------------------------------------
		//
		//				Main Node¸¦ Ã£´Â´Ù.
		//
		//--------------------------------------------------------
		if (bStartFromMainNode)
		{
			if ((*g_pActionInfoTable)[ nActionInfo ].HasMainNode())
			{
				// main node°¡ ÀÖÀ¸¸é main nodeºÎÅÍ ½ÃÀÛÇÏ°Ô ÇÑ´Ù.
				for (int i=0; i<(*g_pActionInfoTable)[ nActionInfo ].GetMainNode(); i++)
				{
					pEffectTarget->NextPhase();
				}			
			}		
		}
		
		//--------------------------------------------------------
		//
		//					½ÃÀÛ À§Ä¡¸¦ °áÁ¤ÇÑ´Ù.
		//
		//--------------------------------------------------------
		int x,y,z, dir;

		//--------------------------------------------------------
		// User À§Ä¡¿¡¼­ ½ÃÀÛÇÏ´Â °æ¿ì
		//--------------------------------------------------------
		if ((*g_pActionInfoTable)[nActionInfo].IsStartUser())
		{
			point = MTopView::MapToPixel(startX, startY);

			x			= point.x + sX;
			y			= point.y + sY;
			z			= startZ;//+60;			
		}
		//--------------------------------------------------------
		// Target À§Ä¡¿¡¼­ ½ÃÀÛÇÏ´Â °æ¿ì
		//--------------------------------------------------------
		else if ((*g_pActionInfoTable)[nActionInfo].IsStartTarget())
		{
			x			= point.x + sX;
			y			= point.y + sY;
			z			= startZ;//+60;			
		}

		//--------------------------------------------------------
		// °øÁß¿¡¼­ ½ÃÀÛÇÏ´Â °æ¿ì
		//--------------------------------------------------------
		if ((*g_pActionInfoTable)[nActionInfo].IsStartSky())
		{
			z	= startZ + (*g_pActionInfoTable)[nActionInfo].GetValue();

			dir	= DIRECTION_DOWN;
		}
		//--------------------------------------------------------
		// Áö»ó¿¡¼­ ½ÃÀÛÇÏ´Â °æ¿ì
		//--------------------------------------------------------
		else
		{
			dir	= direction;
		}

		//--------------------------------------------------------
		//
		//                   Effect»ý¼º		
		//
		//--------------------------------------------------------
		g_pEffectGeneratorTable->Generate(
				x,y,z,				// ½ÃÀÛ À§Ä¡
				dir, 				// ¹æÇâ
				1,					// power
				nActionInfo,		//	ActionInfoTableÁ¾·ù,
				pEffectTarget		// ¸ñÇ¥ Á¤º¸
		);	
		

		DEBUG_ADD_FORMAT("[ExecuteActionInfoFromMainNode] ai=%d", nActionInfo);
	}
	else
	{
		//------------------------------------------------------------
		// °á°ú¸¦ Ã³¸®ÇØ¾ßÇÏ´Â ½ÃÁ¡ÀÎ°¡? - ´ç¿¬ÇÏ´Ù°í º»´Ù *_*;
		//------------------------------------------------------------				
		if (pActionResult != NULL)
		{					
			// °á°ú ½ÇÇà
			pActionResult->Execute();
					
			// ¸Þ¸ð¸® Á¦°Å
			delete pActionResult;		
		}				
	}
}

//-----------------------------------------------------------------------------
// Get Position  Map  To  Screen
//-----------------------------------------------------------------------------
// mapÁÂÇ¥ (sX,sY)¸¦ È­¸é »óÀÇ ÁÂÇ¥·Î ¹Ù²Û´Ù.
//-----------------------------------------------------------------------------
POINT			
ConvertPositionMapToScreen(int sX, int sY)
{
	POINT point = g_pTopView->MapToScreen(sX, sY);

	return point;
}



//-----------------------------------------------------------------------------
// Set Inventory Info
//-----------------------------------------------------------------------------
// PlayerÀÇ Inventory Á¤º¸¸¦ ¼³Á¤ÇÑ´Ù.
//-----------------------------------------------------------------------------
void
SetInventoryInfo(InventoryInfo* pInventoryInfo)
{
	DEBUG_ADD( "Set Inventory Info" );
	
	//--------------------------------------------------
	// Inventory ÃÊ±âÈ­
	//--------------------------------------------------	
	g_pInventory->Init(INVENTORY_WIDTH, INVENTORY_HEIGHT);
	
	if (pInventoryInfo!=NULL)
	{
		int itemNum = pInventoryInfo->getListNum();

		//--------------------------------------------------
		// Inventory¿¡ ¾ÆÀÌÅÛµéÀ» Ãß°¡ÇÑ´Ù.
		//--------------------------------------------------
		for (int i=0; i<itemNum; i++)
		{
			// ¿ÜºÎ¿¡¼­ Áö¿öÁà¾ß ÇÑ´Ù.
			InventorySlotInfo * pSlotInfo = pInventoryInfo->popFrontListElement();

			if( pSlotInfo == NULL )
				continue;

			if( pSlotInfo->getItemClass() >= g_pItemTable->GetSize() ||
				pSlotInfo->getItemType() >= (*g_pItemTable)[pSlotInfo->getItemClass()].GetSize() )
			{
				SendBugReport("[%s] %d,%d",__FILE__, pSlotInfo->getItemClass(), pSlotInfo->getItemType());
				delete pSlotInfo;
				continue;
			}

			//------------------------------------------------
			// ItemÀ» »ý¼ºÇØ¼­ Inventory¿¡ Ãß°¡ÇÑ´Ù.
			//------------------------------------------------
			MItem* pItem = MItem::NewItem( (ITEM_CLASS)pSlotInfo->getItemClass() );
			
			// object ID
			pItem->SetID( pSlotInfo->getObjectID() );

			// type / option
			pItem->SetItemType(	pSlotInfo->getItemType() );
			pItem->SetItemOptionList( pSlotInfo->getOptionType() );
			pItem->SetItemGTwoOptionList( pSlotInfo->getGTwoOptionType() );
			pItem->SetItemThirdOptionList( pSlotInfo->getThirdOptionType() );
			pItem->SetItemThirdOptionType(pSlotInfo->getThirdEnchantType());

#if __CONTENTS(__PET_MIXINGFORGE)
			if((ITEM_CLASS)pSlotInfo->getItemClass() == ITEM_CLASS_PET_ITEM)
				int a = pSlotInfo->getMixOptionTypeSize();
			pItem->SetPetMixingOptionList(pSlotInfo->getMixOptionType());
#endif //__PET_MIXINGFORGE

#if __CONTENTS(__PET_VISION_AMPLE)
			pItem->SetPet_RedBirdOptionNum(pSlotInfo->getAddedInfo1());
			pItem->SetPet_AmpulOptionNum(pSlotInfo->getAddedInfo2());
			pItem->SetPet_op3(pSlotInfo->getAddedInfo3());
#endif //__PET_VISION_AMPLE

#if __CONTENTS(__INTERNATIONAL_PREMIUM_SYSTEM)
			pItem->SetCashItem(pSlotInfo->getCashItem());
#endif
			// inventory¿¡¼­ÀÇ ÁÂÇ¥
			pItem->SetGridXY( pSlotInfo->getInvenX(), pSlotInfo->getInvenY() );

			//------------------------------------------
			// °³¼ö
			//------------------------------------------
			// ÃÑÀÎ °æ¿ì
			//------------------------------------------
			if (pItem->IsGunItem())
			{
				MMagazine* pMagazine = (MMagazine*)MItem::NewItem( (ITEM_CLASS)ITEM_CLASS_MAGAZINE );

				// ÀÇ¹Ì ¾øÀ½ - -;
				pMagazine->SetID( 0 );

				// ÀÌ°Å´Â ÃÑ¿¡ ¸ÂÃç¼­ ÇØÁà¾ßµÈ´Ù.
				for (int j=0; j<(*g_pItemTable)[ITEM_CLASS_MAGAZINE].GetSize(); j++)			
				{
					pMagazine->SetItemType(	j );

					if (pMagazine->IsInsertToItem( pItem ))
					{
						break;
					}
				}

				if(pSlotInfo->getSilver())
					pMagazine->SetItemType( pMagazine->GetItemType()+8);
				// ¾î¿¹~ ÀºÅºÈ¯ ÇÏµåÄÚµù by ¾¦°«

				// ÀÇ¹Ì ¾øÀ½
				pMagazine->ClearItemOption();
			
				// ÅºÃ¢ °³¼ö
				pMagazine->SetNumber( pSlotInfo->getItemNum() );

				//------------------------------------
				// ÅºÃ¢ ¼³Á¤
				//------------------------------------
				MGunItem* pGunItem = (MGunItem*)pItem;
				pGunItem->SetMagazine( pMagazine );
			}		
			//------------------------------------------
			// ÃÑÀÌ ¾Æ´Ñ °æ¿ì
			//------------------------------------------
			else
			{
				pItem->SetNumber( pSlotInfo->getItemNum() );
			}


			//------------------------------------------
			//
			// Item¿¡ ´Ù¸¥ itemµéÀÌ µé¾îÀÖ´Â °æ¿ì
			//
			//------------------------------------------
			if (pSlotInfo->getListNum()!=0)
			{
				DEBUG_ADD_FORMAT("This Item has Sub item(s) : size=%d", pSlotInfo->getListNum());
				
				//------------------------------------------
				// BeltÀÎ °æ¿ì
				//------------------------------------------
				if (pItem->GetItemClass()==ITEM_CLASS_BELT)
				{
					MBelt* pBelt = (MBelt*)pItem;

					int size = pSlotInfo->getListNum();
					
					for (int i=0; i<size; i++)
					{
						SubItemInfo * pSubItemInfo = pSlotInfo->popFrontListElement();

						if (pSubItemInfo==NULL)
						{
							DEBUG_ADD("[Error] Sub Item is NULL");
						}
						else
						{
							//------------------------------------------
							// Sub ItemÀÇ Á¤º¸¸¦ ¼³Á¤ÇÑ´Ù.
							//------------------------------------------
							if ( pSubItemInfo->getItemClass() >= g_pItemTable->GetSize() ||
								(*g_pItemTable)[pSubItemInfo->getItemClass()].GetSize() <= pSubItemInfo->getItemType() )
							{
								SendBugReport("[PacketFunction::SetInventoryInfo,%d] %d,%d",__LINE__,pSubItemInfo->getItemClass(), pSubItemInfo->getItemType() );
								return;
							}
							MItem* pSubItem = MItem::NewItem( (enum ITEM_CLASS)pSubItemInfo->getItemClass() );
							pSubItem->SetItemType( pSubItemInfo->getItemType() );
							//pItem->SetItemOption( pSubItemInfo->getOptionType() );

							pSubItem->SetID( pSubItemInfo->getObjectID() );		

							pSubItem->SetNumber( pSubItemInfo->getItemNum() );			

							//------------------------------------------
							// BeltÀÇ Á¤ÇØÁø slot¿¡ itemÀ» Ãß°¡½ÃÅ²´Ù.
							//------------------------------------------
							pBelt->AddItem( pSubItem, pSubItemInfo->getSlotID() );

							delete pSubItemInfo;
						}
					} 
				}
				else if (pItem->GetItemClass()==ITEM_CLASS_OUSTERS_ARMSBAND)
				{
					MOustersArmsBand* pBelt = (MOustersArmsBand*)pItem;
					
					int size = pSlotInfo->getListNum();
					
					for (int i=0; i<size; i++)
					{
						SubItemInfo * pSubItemInfo = pSlotInfo->popFrontListElement();
						
						if (pSubItemInfo==NULL)
						{
							DEBUG_ADD("[Error] Sub Item is NULL");
						}
						else
						{
							//------------------------------------------
							// Sub ItemÀÇ Á¤º¸¸¦ ¼³Á¤ÇÑ´Ù.
							//------------------------------------------
							if ( pSubItemInfo->getItemClass() >= g_pItemTable->GetSize() ||
								(*g_pItemTable)[pSubItemInfo->getItemClass()].GetSize() <= pSubItemInfo->getItemType() )
							{
								SendBugReport("[PacketFunction::SetInventoryInfo,%d] %d,%d",__LINE__,pSubItemInfo->getItemClass(), pSubItemInfo->getItemType() );
								return;
							}
							MItem* pSubItem = MItem::NewItem( (enum ITEM_CLASS)pSubItemInfo->getItemClass() );
							pSubItem->SetItemType( pSubItemInfo->getItemType() );
							//pItem->SetItemOption( pSubItemInfo->getOptionType() );
							
							pSubItem->SetID( pSubItemInfo->getObjectID() );		
							
							pSubItem->SetNumber( pSubItemInfo->getItemNum() );			
							
							//------------------------------------------
							// BeltÀÇ Á¤ÇØÁø slot¿¡ itemÀ» Ãß°¡½ÃÅ²´Ù.
							//------------------------------------------
							pBelt->AddItem( pSubItem, pSubItemInfo->getSlotID() );
							
							delete pSubItemInfo;
						}
					}
				}
				else
				{
					DEBUG_ADD_FORMAT("This Item can't have Sub item : class=%d", (int)pItem->GetItemClass());
				}
			}


			// main»ö±ò
			pItem->SetItemColorSet( pSlotInfo->getMainColor() );

			// ÇöÀç ³»±¸¼º
			pItem->SetCurrentDurability( pSlotInfo->getDurability() );
			pItem->SetSilver( pSlotInfo->getSilver() );
			pItem->SetGrade( pSlotInfo->getGrade() );
			pItem->SetEnchantLevel( pSlotInfo->getEnchantLevel() );

			//---------------------------------------------
			// itemÀ» inventory¿¡ ³Ö´Â´Ù.
			//---------------------------------------------
			if (g_pInventory->AddItem( pItem, pItem->GetGridX(), pItem->GetGridY() ))
			{				
			}	
			else
			{
				// itemÀ» inventory¿¡ Ãß°¡ÇÒ ¼ö ¾ø´Â °æ¿ì
				DEBUG_ADD_FORMAT("[Error] Can't Add Item to Inventory. id=%d, cl=%d, tp=%d, xy=(%d,%d)", 					
												(int)pItem->GetID(),
												(int)pItem->GetItemClass(),
												(int)pItem->GetItemType(),
												(int)pItem->GetGridX(),
												(int)pItem->GetGridY());
				
				delete pItem;
			}

			delete pSlotInfo;
		}
	}

	//---------------------------------------------------------
	// »ç¿ë °¡´É ¿©ºÎ Ã¼Å©
	//---------------------------------------------------------
	g_pInventory->CheckAffectStatusAll();

	//---------------------------------------------------------
	// inventory¿¡ ºÙÀº EffectÁ¦°Å
	//---------------------------------------------------------
	if (g_pInventoryEffectManager!=NULL)
	{
		g_pInventoryEffectManager->Release();
	}
}

//--------------------------------------------------------------------------------
// Gear Information
//--------------------------------------------------------------------------------
// PlayerÀÇ Gear¿¡ ´ëÇÑ info¸¦ ¼³Á¤ÇÑ´Ù.
// SetGearInfo()¸¦ ÇÏ±â Àü¿¡..
// g_pPlayer°¡ SlayerÀÎÁö VampireÀÎÁö°¡ °áÁ¤ÀÌ ³ª¾ß ÇÑ´Ù.
// ±×·¡¾ßÁö.. g_SlayerGearÀÎÁö.. g_VampireGearÀÎÁö¸¦ ¾Ë ¼ö°¡ ÀÖ´Ù.
//--------------------------------------------------------------------------------
#if __CONTENTS(__GEAR_SWAP_CHANGE) // SetGearInfo ¸öÃ¼
void SetGearInfo(GearInfo* pGearInfo, BloodBibleSignInfo* pBloodBibleInfo, DWORD dwGearID, bool bOtherGear)
#else
void SetGearInfo(GearInfo* pGearInfo, BloodBibleSignInfo* pBloodBibleInfo, bool bOtherGear)
#endif //__GEAR_SWAP_CHANGE
{
	DEBUG_ADD( "Set Gear Info" );

	bOtherGear = false;
	MPlayerGear *pGear = NULL;

	if ( !bOtherGear )
	{
		if(ACTION_STAND != g_pPlayer->GetAction())//	&&	ACTION_MOVE != g_pPlayer->GetAction())
		{
			g_pPlayer->SetAction(ACTION_STAND);
			//		return;
		}

#if __CONTENTS(__GEAR_SWAP_CHANGE) // ±³Ã¼°¡ µÇ¾úÀ½À» ¾Ë¸°´Ù.
		switch(g_pPlayer->GetRace())
		{
		case RACE_SLAYER:
			g_pSlayerGear->SetProcessingGearChange(true);
			break;

		case RACE_VAMPIRE:
			g_pVampireGear->SetProcessingGearChange(true);
			break;

		case RACE_OUSTERS:
			g_pOustersGear->SetProcessingGearChange(true);
			break;
		}

		DWORD	dwGearSize	= gC_vs_ui.GetGearSize();

		MItem* pItem	= NULL;

		for(int i = 0; i < dwGearSize; i++)
		{
			if(i	!= 0)	// ID 0ÀÌ ¸Ó¸® »ö ÀÎ°¡ º¸´Ù.
			{
				g_pPlayer->RemoveAddon(i);
				pItem	=	g_pPlayer->GetGearItemIndexFromAddonInfo(i);

				if(pItem)
				{
					g_pPlayer->SetAddonItem(pItem);		

					delete pItem;
					pItem	= NULL;
				}
			}
		}

#endif	// __GEAR_SWAP_CHANGE
	}


	if ( !bOtherGear )
	{
		switch(g_pPlayer->GetRace())
		{
		case RACE_SLAYER:
			g_pSlayerGear->Init();
			break;

		case RACE_VAMPIRE:
			g_pVampireGear->Init();
			break;

		case RACE_OUSTERS:
			g_pOustersGear->Init();
			break;
		}
	}
	//else
	//{
	//	switch(g_pPlayer->GetRace())
	//	{
	//	case RACE_SLAYER:
	//		g_pSlayerGearOther->SetIsOtherGear(true);
	//		g_pSlayerGearOther->Init();
	//		break;

	//	case RACE_VAMPIRE:
	//		g_pVampireGearOther->Init();
	//		g_pVampireGearOther->SetIsOtherGear(true);
	//		break;

	//	case RACE_OUSTERS:
	//		g_pOustersGearOther->Init();
	//		g_pOustersGearOther->SetIsOtherGear(true);
	//		break;
	//	}
	//}


	if (pGearInfo!=NULL)
	{
		int itemNum = pGearInfo->getListNum();
				
		bool bAdd;
		
		for (int i=0; i<itemNum; i++)
		{
			// ¿ÜºÎ¿¡¼­ Áö¿öÁà¾ß ÇÑ´Ù.
			GearSlotInfo * pSlotInfo = pGearInfo->popFrontListElement();

			if( pSlotInfo->getItemClass() >= g_pItemTable->GetSize() ||
				pSlotInfo->getItemType() >= (*g_pItemTable)[pSlotInfo->getItemClass()].GetSize() )
			{
				SendBugReport("[%s,%d] %d,%d",__FILE__, __LINE__,pSlotInfo->getItemClass(), pSlotInfo->getItemType());
				delete pSlotInfo;
				continue;
			}
					
			//------------------------------------------------
			// ItemÀ» »ý¼ºÇØ¼­ Gear¿¡ Ãß°¡ÇÑ´Ù.
			//------------------------------------------------
			MItem* pItem = MItem::NewItem( (ITEM_CLASS)pSlotInfo->getItemClass() );
		
			// object ID
			pItem->SetID( pSlotInfo->getObjectID() );

			// type / option
			pItem->SetItemType(	pSlotInfo->getItemType() );
			pItem->SetItemOptionList( pSlotInfo->getOptionType() );
			pItem->SetItemGTwoOptionList( pSlotInfo->getGTwoOptionType() );
			pItem->SetItemThirdOptionList( pSlotInfo->getThirdOptionType() );
			pItem->SetItemThirdOptionType(pSlotInfo->getThirdEnchantType());
#if __CONTENTS(__PET_MIXINGFORGE)
			pItem->SetPetMixingOptionList(pSlotInfo->getMixOptionType());
#endif //__PET_MIXINGFORGE
#if __CONTENTS(__INTERNATIONAL_PREMIUM_SYSTEM)
			pItem->SetCashItem(pSlotInfo->getCashItem());
#endif		
#if __CONTENTS(__GEAR_SWAP_CHANGE) // SetGearInfo	pItem->SetActive((pSlotInfo->getActiveSlot())	
			pItem->SetActive(pSlotInfo->getActiveSlot());
#endif		// __GEAR_SWAP_CHANGE

			
			//------------------------------------------
			// °³¼ö
			//------------------------------------------
			// ÃÑÀÎ °æ¿ì
			//------------------------------------------
			if (pItem->IsGunItem())
			{
				MMagazine* pMagazine = (MMagazine*)MItem::NewItem( (ITEM_CLASS)ITEM_CLASS_MAGAZINE );

				// ÀÇ¹Ì ¾øÀ½ - -;
				pMagazine->SetID( 0 );

				// ÀÌ°Å´Â ÃÑ¿¡ ¸ÂÃç¼­ ÇØÁà¾ßµÈ´Ù.
				for (int j=0; j<(*g_pItemTable)[ITEM_CLASS_MAGAZINE].GetSize(); j++)			
				{
					pMagazine->SetItemType(	j );

					if (pMagazine->IsInsertToItem( pItem ))
					{
						break;
					}
				}

				if(pSlotInfo->getSilver())
					pMagazine->SetItemType( pMagazine->GetItemType()+8);
				// ¾î¿¹~ ÀºÅºÈ¯ ÇÏµåÄÚµù by ¾¦°«

				// ÀÇ¹Ì ¾øÀ½
				pMagazine->ClearItemOption();
			
				// ÅºÃ¢ °³¼ö
				pMagazine->SetNumber( pSlotInfo->getItemNum() );

				//------------------------------------
				// ÅºÃ¢ ¼³Á¤
				//------------------------------------
				MGunItem* pGunItem = (MGunItem*)pItem;
				pGunItem->SetMagazine( pMagazine );
			}		
			//------------------------------------------
			// ÃÑÀÌ ¾Æ´Ñ °æ¿ì
			//------------------------------------------
			else
			{
				pItem->SetNumber( pSlotInfo->getItemNum() );
				pItem->SetSilver( pSlotInfo->getSilver() );
			}

			pItem->SetGrade( pSlotInfo->getGrade() );
			// gear¿¡¼­ÀÇ ÁÂÇ¥
			pItem->SetItemSlot( pSlotInfo->getSlotID() );

			// main»ö±ò
			pItem->SetItemColorSet( pSlotInfo->getMainColor() );

			// ÇöÀç ³»±¸¼º
			pItem->SetCurrentDurability( pSlotInfo->getDurability() );			
			pItem->SetEnchantLevel( pSlotInfo->getEnchantLevel() );		

			//------------------------------------------
			//
			// Item¿¡ ´Ù¸¥ itemµéÀÌ µé¾îÀÖ´Â °æ¿ì
			//
			//------------------------------------------
			if (pSlotInfo->getListNum()!=0)
			{
				DEBUG_ADD_FORMAT("This Item has Sub item(s) : size=%d", pSlotInfo->getListNum());
				
				//------------------------------------------
				// BeltÀÎ °æ¿ì
				//------------------------------------------
				if (pItem->GetItemClass()==ITEM_CLASS_BELT)
				{
					MBelt* pBelt = (MBelt*)pItem;

					int size = pSlotInfo->getListNum();
					
					for (int i=0; i<size; i++)
					{
						SubItemInfo * pSubItemInfo = pSlotInfo->popFrontListElement();

						if (pSubItemInfo==NULL)
						{
							DEBUG_ADD("[Error] Sub Item is NULL");
						}
						else
						{
							//------------------------------------------
							// Sub ItemÀÇ Á¤º¸¸¦ ¼³Á¤ÇÑ´Ù.
							//------------------------------------------
							if ( pSubItemInfo->getItemClass() >= g_pItemTable->GetSize() ||
								(*g_pItemTable)[pSubItemInfo->getItemClass()].GetSize() <= pSubItemInfo->getItemType() )
							{
								SendBugReport("[PacketFunction::SetGearInfo,%d] %d,%d",__LINE__,pSubItemInfo->getItemClass(), pSubItemInfo->getItemType() );
								return;
							}
							MItem* pSubItem = MItem::NewItem( (enum ITEM_CLASS)pSubItemInfo->getItemClass() );
							pSubItem->SetItemType( pSubItemInfo->getItemType() );
							//pItem->SetItemOption( pSubItemInfo->getOptionType() );

							pSubItem->SetID( pSubItemInfo->getObjectID() );		

							pSubItem->SetNumber( pSubItemInfo->getItemNum() );			

							//------------------------------------------
							// BeltÀÇ Á¤ÇØÁø slot¿¡ itemÀ» Ãß°¡½ÃÅ²´Ù.
							//------------------------------------------
							pBelt->AddItem( pSubItem, pSubItemInfo->getSlotID() );

							delete pSubItemInfo;
						}
					}
				}
				else if (pItem->GetItemClass()==ITEM_CLASS_OUSTERS_ARMSBAND)
				{
					MOustersArmsBand* pBelt = (MOustersArmsBand*)pItem;

					int size = pSlotInfo->getListNum();
					
					for (int i=0; i<size; i++)
					{
						SubItemInfo * pSubItemInfo = pSlotInfo->popFrontListElement();

						if (pSubItemInfo==NULL)
						{
							DEBUG_ADD("[Error] Sub Item is NULL");
						}
						else
						{
							//------------------------------------------
							// Sub ItemÀÇ Á¤º¸¸¦ ¼³Á¤ÇÑ´Ù.
							//------------------------------------------
							if ( pSubItemInfo->getItemClass() >= g_pItemTable->GetSize() ||
								(*g_pItemTable)[pSubItemInfo->getItemClass()].GetSize() <= pSubItemInfo->getItemType() )
							{
								SendBugReport("[PacketFunction::SetGearInfo,%d] %d,%d",__LINE__,pSubItemInfo->getItemClass(), pSubItemInfo->getItemType() );
								return;
							}
							MItem* pSubItem = MItem::NewItem( (enum ITEM_CLASS)pSubItemInfo->getItemClass() );
							pSubItem->SetItemType( pSubItemInfo->getItemType() );
							//pItem->SetItemOption( pSubItemInfo->getOptionType() );

							pSubItem->SetID( pSubItemInfo->getObjectID() );		

							pSubItem->SetNumber( pSubItemInfo->getItemNum() );			

							//------------------------------------------
							// BeltÀÇ Á¤ÇØÁø slot¿¡ itemÀ» Ãß°¡½ÃÅ²´Ù.
							//------------------------------------------
							pBelt->AddItem( pSubItem, pSubItemInfo->getSlotID() );

							delete pSubItemInfo;
						}
					}
				}
				else
				{
					DEBUG_ADD_FORMAT("This Item can't have Sub item : class=%d", (int)pItem->GetItemClass());
				}
			}

			//---------------------------------------------
			// itemÀ» gear¿¡ ³Ö´Â´Ù.
			//---------------------------------------------
			// slayer / vampire¿¡ µû¶ó¼­ gear°¡ ´Ù¸£´Ù.
			//---------------------------------------------
			if ( !bOtherGear )
			{
				switch(g_pPlayer->GetRace())
				{
				case RACE_SLAYER:
					bAdd = g_pSlayerGear->AddItem( pItem, (MSlayerGear::GEAR_SLAYER)pItem->GetItemSlot() );
					break;

				case RACE_VAMPIRE:
					bAdd = g_pVampireGear->AddItem( pItem, (MVampireGear::GEAR_VAMPIRE)pItem->GetItemSlot() );
					break;

				case RACE_OUSTERS:
					bAdd = g_pOustersGear->AddItem( pItem, (MOustersGear::GEAR_OUSTERS)pItem->GetItemSlot() );
					break;
				}
			}
			else
			{
				switch(g_pPlayer->GetRace())
				{
				case RACE_SLAYER:
					bAdd = g_pSlayerGearOther->AddItem( pItem, (MSlayerGear::GEAR_SLAYER)pItem->GetItemSlot() );
					break;

				case RACE_VAMPIRE:
					bAdd = g_pVampireGearOther->AddItem( pItem, (MVampireGear::GEAR_VAMPIRE)pItem->GetItemSlot() );
					break;

				case RACE_OUSTERS:
					bAdd = g_pOustersGearOther->AddItem( pItem, (MOustersGear::GEAR_OUSTERS)pItem->GetItemSlot() );
					break;
				}
			}

			if ( !bOtherGear )
			{
#if __CONTENTS(__GEAR_SWAP_CHANGE) // SetGearInfo Âø¿ë ÇÒ ¼ö ¾ø´Â ¾ÆÀÌÅÛÀº UnSetÇÑ´Ù.
				bool	bGetActive	= pGearInfo->GetActive();

				if(bGetActive == false || !pSlotInfo->getActiveSlot())
				{		
					pItem->UnSetAffectStatus();
				}
#endif	//	__GEAR_SWAP_CHANGE

				//---------------------------------------------
				// º¹Àå ¹Ù²Û´Ù.
				//---------------------------------------------
				g_pPlayer->SetAddonItem( pItem );

				//---------------------------------------------
				// Gear Ãß°¡ÇÒ ¼ö ¾ø´Â °æ¿ì
				//---------------------------------------------
				if (!bAdd)		
				{
					// itemÀ» Gear¿¡ Ãß°¡ÇÒ ¼ö ¾ø´Â °æ¿ì
					DEBUG_ADD_FORMAT("[Error] Can't Add Item to Gear. id=%d, cl=%d, tp=%d, slot=%d", 
						(int)pItem->GetID(),
						(int)pItem->GetItemClass(),
						(int)pItem->GetItemType(),
						(int)pItem->GetItemSlot());

					delete pItem;
				}

				delete pSlotInfo;
			}

			SetBloodBibleSlot(pBloodBibleInfo);
	}	

	if ( bOtherGear )
		return;

#if __CONTENTS(__GEAR_SWAP_CHANGE) // SetGearInfo ¼­¹ö¿¡¼­ ¹ÞÀº ÀåÂøÃ¢ÀÇ ID¸¦ ¼³Á¤ ÇÑ´Ù.
	switch(g_pPlayer->GetRace())
	{
	case RACE_SLAYER:
		g_pSlayerGear->SetActive(pGearInfo->GetActive());
		//		g_pSlayerGear->SetAccepGearID(dwGearID);
		g_pSlayerGear->SetAccepGearID(pGearInfo->GetGearSlotID());
		break;

	case RACE_VAMPIRE:
		g_pVampireGear->SetActive(pGearInfo->GetActive());
		//		g_pVampireGear->SetAccepGearID(dwGearID);
		g_pVampireGear->SetAccepGearID(pGearInfo->GetGearSlotID());
		break;

	case RACE_OUSTERS:
		g_pOustersGear->SetActive(pGearInfo->GetActive());
		//		g_pOustersGear->SetAccepGearID(dwGearID);
		g_pOustersGear->SetAccepGearID(pGearInfo->GetGearSlotID());
		break;
	}
#endif	//__GEAR_SWAP_CHANGE

	pGear = g_pPlayer->GetGear();

#if __CONTENTS(__GEAR_SWAP_CHANGE)// void SetGearInfo		pGear->CheckAffectStatusAllGear();
	pGear->CheckAffectStatusPickupItem();
#else
	pGear->CheckAffectStatusAll();
#endif // __GEAR_SWAP_CHANGE
	//----------------------------------------------------
	// Skill Ã¼Å©
	//----------------------------------------------------
	g_pSkillAvailable->SetAvailableSkills();

	//----------------------------------------------
	// ¼öÄ¡ °è»êÀ» ÇÑ´Ù.
	//----------------------------------------------
	g_pPlayer->CalculateStatus();

	//g_char_slot_ingame.CC		= g_pPlayer->GetCARRYWEIGHT();
	//g_char_slot_ingame.DAM		= g_pPlayer->GetDAM();
	//g_char_slot_ingame.AC		= g_pPlayer->GetAC();
	g_char_slot_ingame.TOHIT	= g_pPlayer->GetTOHIT();

#if __CONTENTS(__GEAR_SWAP_CHANGE) // ±³Ã¼°¡ ¿Ï·á µÇ¾úÀ½À» ¾Ë¸°´Ù.
	if ( !bOtherGear )
	{
		switch(g_pPlayer->GetRace())
		{
		case RACE_SLAYER:
			g_pSlayerGear->SetProcessingGearChange(false);
			break;

		case RACE_VAMPIRE:
			g_pVampireGear->SetProcessingGearChange(false);
			break;

		case RACE_OUSTERS:
			g_pOustersGear->SetProcessingGearChange(false);
			break;
		}
	}

#endif	// __GEAR_SWAP_CHANGE
			}



}
// 2004, 10, 21, sobeit add start - blood bible slot
void SetBloodBibleSlot(BloodBibleSignInfo* pBloodBibleInfo)
{
	if(NULL == pBloodBibleInfo)
		return;

	std::vector<WORD>	TempSignList = pBloodBibleInfo->getList();
	for(int i = 0; i< HOLYLAND_BONUS_MAX; i++)
		g_abHolyLandBonusSkills[i] = false;
	switch(g_pPlayer->GetRace())
	{
	case RACE_SLAYER:
		{
			for(int i = 0; i<g_pSlayerGear->GetBloodBibleOpenSlot() ; i++)
			{
				MItem* pItem = g_pSlayerGear->RemoveItem((MSlayerGear::GEAR_SLAYER)(MSlayerGear::GEAR_SLAYER_BLOOD_BIBLE1+i));
				SAFE_DELETE(pItem);
			}

			g_pSlayerGear->SetBloodBibleOpenSlot(pBloodBibleInfo->getOpenNum());

			for(i = 0; i<TempSignList.size() ; i++)
			{
				MItem* pItem = MItem::NewItem( ITEM_CLASS_BLOOD_BIBLE_SIGN );
				pItem->SetItemType(	TempSignList[i] );
				pItem->SetID(i);
				g_pSlayerGear->AddItem(pItem, (MSlayerGear::GEAR_SLAYER)(MSlayerGear::GEAR_SLAYER_BLOOD_BIBLE1+i));
				g_abHolyLandBonusSkills[(TempSignList[i]%12)] = true;
			}
		}
		break;

	case RACE_VAMPIRE:
		{
			for(int i = 0; i<g_pVampireGear->GetBloodBibleOpenSlot() ; i++)
			{
				MItem* pItem = g_pVampireGear->RemoveItem((MVampireGear::GEAR_VAMPIRE)(MVampireGear::GEAR_VAMPIRE_BLOOD_BIBLE1+i));
				SAFE_DELETE(pItem);
			}
			g_pVampireGear->SetBloodBibleOpenSlot(pBloodBibleInfo->getOpenNum());

			for(i = 0; i<TempSignList.size() ; i++)
			{
				MItem* pItem = MItem::NewItem( ITEM_CLASS_BLOOD_BIBLE_SIGN );
				pItem->SetItemType(	TempSignList[i] );
				pItem->SetID(i);
				g_pVampireGear->AddItem(pItem, (MVampireGear::GEAR_VAMPIRE)(MVampireGear::GEAR_VAMPIRE_BLOOD_BIBLE1+i));
				g_abHolyLandBonusSkills[(TempSignList[i]%12)] = true;
			}
		}
		break;

	case RACE_OUSTERS:
		{
			for(int i = 0; i<g_pOustersGear->GetBloodBibleOpenSlot() ; i++)
			{
				MItem* pItem = g_pOustersGear->RemoveItem((MOustersGear::GEAR_OUSTERS)(MOustersGear::GEAR_OUSTERS_BLOOD_BIBLE1+i));
				SAFE_DELETE(pItem);
			}
			g_pOustersGear->SetBloodBibleOpenSlot(pBloodBibleInfo->getOpenNum());

			for(i = 0; i<TempSignList.size() ; i++)
			{ 
				MItem* pItem = MItem::NewItem( ITEM_CLASS_BLOOD_BIBLE_SIGN );
				pItem->SetItemType(	TempSignList[i] );
				pItem->SetID(i);
				g_pOustersGear->AddItem(pItem, (MOustersGear::GEAR_OUSTERS)(MOustersGear::GEAR_OUSTERS_BLOOD_BIBLE1+i));
				g_abHolyLandBonusSkills[(TempSignList[i]%12)] = true;
			}
		}
		break;
	}

	

}
// 2004, 10, 21, sobeit add end - blood bible slot
//--------------------------------------------------------------------------------
// Extra Information
//--------------------------------------------------------------------------------
// mouse¿¡ µé°í ÀÖ´Â item¿¡ ´ëÇÑ Á¤º¸ ¼³Á¤
//--------------------------------------------------------------------------------
void
SetExtraInfo(ExtraInfo* pExtraInfo)
{
	DEBUG_ADD( "Set Extra Info" );
	
	//------------------------------------------------------
	// µé°í ÀÖ´Â itemÀ» ¾ø¾Ø´Ù.
	//------------------------------------------------------
	MItem* pCurrentItem = gpC_mouse_pointer->GetPickUpItem();

	if (pCurrentItem!=NULL)
	{
		delete pCurrentItem;
		UI_DropItem();
	}

	if (pExtraInfo!=NULL)
	{
		int itemNum = pExtraInfo->getListNum();

		//------------------------------------------------------
		// ´ç¿¬È÷ 1°³¹Û¿¡ ¾ø°ÚÁö¸¸.. - -;;
		//------------------------------------------------------
		for (int i=0; i<itemNum; i++)
		{
			ExtraSlotInfo * pSlotInfo = pExtraInfo->popFrontListElement();

			//------------------------------------------------
			// ItemÀ» »ý¼ºÇØ¼­ mouse¿¡ µé¸°´Ù.
			//------------------------------------------------
			if ( pSlotInfo->getItemClass() >= g_pItemTable->GetSize() ||
				(*g_pItemTable)[pSlotInfo->getItemClass()].GetSize() <= pSlotInfo->getItemType() )
			{
				SendBugReport("[PacketFunction::SetExtraInfo,%d] %d,%d",__LINE__,pSlotInfo->getItemClass(), pSlotInfo->getItemType() );
				return;
			}
			MItem* pItem = MItem::NewItem( (ITEM_CLASS)pSlotInfo->getItemClass() );
			
			// object ID
			pItem->SetID( pSlotInfo->getObjectID() );

			// type / option
			pItem->SetItemType(	pSlotInfo->getItemType() );
			pItem->SetItemOptionList( pSlotInfo->getOptionType() );
			pItem->SetItemGTwoOptionList( pSlotInfo->getGTwoOptionType() );
			pItem->SetItemThirdOptionList( pSlotInfo->getThirdOptionType() );
			pItem->SetItemThirdOptionType(pSlotInfo->getThirdEnchantType());
#if __CONTENTS(__PET_MIXINGFORGE)
			pItem->SetPetMixingOptionList(pSlotInfo->getMixOptionType());
#endif //__PET_MIXINGFORGE
#if __CONTENTS(__INTERNATIONAL_PREMIUM_SYSTEM)
			pItem->SetCashItem(pSlotInfo->getCashItem());
#endif
			//------------------------------------------
			// °³¼ö
			//------------------------------------------
			// ÃÑÀÎ °æ¿ì
			//------------------------------------------
			if (pItem->IsGunItem())
			{
				MMagazine* pMagazine = (MMagazine*)MItem::NewItem( (ITEM_CLASS)ITEM_CLASS_MAGAZINE );

				// ÀÇ¹Ì ¾øÀ½ - -;
				pMagazine->SetID( 0 );

				// ÀÌ°Å´Â ÃÑ¿¡ ¸ÂÃç¼­ ÇØÁà¾ßµÈ´Ù.
				for (int j=0; j<(*g_pItemTable)[ITEM_CLASS_MAGAZINE].GetSize(); j++)			
				{
					pMagazine->SetItemType(	j );

					if (pMagazine->IsInsertToItem( pItem ))
					{
						break;
					}
				}

				if(pSlotInfo->getSilver())
					pMagazine->SetItemType( pMagazine->GetItemType()+8);
				// ¾î¿¹~ ÀºÅºÈ¯ ÇÏµåÄÚµù by ¾¦°«
				
				// ÀÇ¹Ì ¾øÀ½
				pMagazine->ClearItemOption();
			
				// ÅºÃ¢ °³¼ö
				pMagazine->SetNumber( pSlotInfo->getItemNum() );

				//------------------------------------
				// ÅºÃ¢ ¼³Á¤
				//------------------------------------
				MGunItem* pGunItem = (MGunItem*)pItem;
				pGunItem->SetMagazine( pMagazine );
			}		
			//------------------------------------------
			// ÃÑÀÌ ¾Æ´Ñ °æ¿ì
			//------------------------------------------
			else
			{
				pItem->SetNumber( pSlotInfo->getItemNum() );
			}


			//------------------------------------------
			//
			// Item¿¡ ´Ù¸¥ itemµéÀÌ µé¾îÀÖ´Â °æ¿ì
			//
			//------------------------------------------
			if (pSlotInfo->getListNum()!=0)
			{
				DEBUG_ADD_FORMAT("This Item has Sub item(s) : size=%d", pSlotInfo->getListNum());
				
				//------------------------------------------
				// BeltÀÎ °æ¿ì
				//------------------------------------------
				if (pItem->GetItemClass()==ITEM_CLASS_BELT)
				{
					MBelt* pBelt = (MBelt*)pItem;

					int size = pSlotInfo->getListNum();
					
					for (int i=0; i<size; i++)
					{
						SubItemInfo * pSubItemInfo = pSlotInfo->popFrontListElement();

						if (pSubItemInfo==NULL)
						{
							DEBUG_ADD("[Error] Sub Item is NULL");
						}
						else
						{
							//------------------------------------------
							// Sub ItemÀÇ Á¤º¸¸¦ ¼³Á¤ÇÑ´Ù.
							//------------------------------------------
							if ( pSubItemInfo->getItemClass() >= g_pItemTable->GetSize() ||
								(*g_pItemTable)[pSubItemInfo->getItemClass()].GetSize() <= pSubItemInfo->getItemType() )
							{
								SendBugReport("[PacketFunction::SetExtraInfo,%d] %d,%d",__LINE__,pSubItemInfo->getItemClass(), pSubItemInfo->getItemType() );
								return;
							}
							MItem* pSubItem = MItem::NewItem( (enum ITEM_CLASS)pSubItemInfo->getItemClass() );
							pSubItem->SetItemType( pSubItemInfo->getItemType() );
							//pItem->SetItemOptionList( pSubItemInfo->getOptionType() );

							pSubItem->SetID( pSubItemInfo->getObjectID() );		

							pSubItem->SetNumber( pSubItemInfo->getItemNum() );			

							//------------------------------------------
							// BeltÀÇ Á¤ÇØÁø slot¿¡ itemÀ» Ãß°¡½ÃÅ²´Ù.
							//------------------------------------------
							pBelt->AddItem( pSubItem, pSubItemInfo->getSlotID() );

							delete pSubItemInfo;
						}
					}
				}
				else if (pItem->GetItemClass()==ITEM_CLASS_OUSTERS_ARMSBAND)
				{
					MOustersArmsBand* pBelt = (MOustersArmsBand*)pItem;
					
					int size = pSlotInfo->getListNum();
					
					for (int i=0; i<size; i++)
					{
						SubItemInfo * pSubItemInfo = pSlotInfo->popFrontListElement();
						
						if (pSubItemInfo==NULL)
						{
							DEBUG_ADD("[Error] Sub Item is NULL");
						}
						else
						{
							//------------------------------------------
							// Sub ItemÀÇ Á¤º¸¸¦ ¼³Á¤ÇÑ´Ù.
							//------------------------------------------
							if ( pSubItemInfo->getItemClass() >= g_pItemTable->GetSize() ||
								(*g_pItemTable)[pSubItemInfo->getItemClass()].GetSize() <= pSubItemInfo->getItemType() )
							{
								SendBugReport("[PacketFunction::SetExtraInfo,%d] %d,%d",__LINE__,pSubItemInfo->getItemClass(), pSubItemInfo->getItemType() );
								return;
							}

							MItem* pSubItem = MItem::NewItem( (enum ITEM_CLASS)pSubItemInfo->getItemClass() );
							pSubItem->SetItemType( pSubItemInfo->getItemType() );
							//pItem->SetItemOptionList( pSubItemInfo->getOptionType() );
							
							pSubItem->SetID( pSubItemInfo->getObjectID() );		
							
							pSubItem->SetNumber( pSubItemInfo->getItemNum() );			
							
							//------------------------------------------
							// BeltÀÇ Á¤ÇØÁø slot¿¡ itemÀ» Ãß°¡½ÃÅ²´Ù.
							//------------------------------------------
							pBelt->AddItem( pSubItem, pSubItemInfo->getSlotID() );
							
							delete pSubItemInfo;
						}
					}
				}
				else
				{
					DEBUG_ADD_FORMAT("This Item can't have Sub item : class=%d", (int)pItem->GetItemClass());
				}
			}


			// main»ö±ò
			pItem->SetItemColorSet( pSlotInfo->getMainColor() );

			// ÇöÀç ³»±¸¼º
			pItem->SetCurrentDurability( pSlotInfo->getDurability() );
			pItem->SetSilver( pSlotInfo->getSilver() );
			pItem->SetGrade( pSlotInfo->getGrade() );
			pItem->SetEnchantLevel( pSlotInfo->getEnchantLevel() );

			//------------------------------------------
			// ItemÀ» µç´Ù.
			//------------------------------------------
			UI_PickUpItem( pItem );

			delete pSlotInfo;
		}
	}

}

//--------------------------------------------------------------------------------
// Set EffectInfo
//--------------------------------------------------------------------------------
// Player¿¡°Ô ºÙ¾î ÀÖ´Â Effect¸¦ ¼³Á¤ÇØÁØ´Ù.
//
// delayedFrameÀº ..
// Ã³¸®(Æ¯È÷ loading)¸¦ ÇÑ´Ù°í client¿¡¼­ ¼Ò¿äµÈ ½Ã°£¸¸Å­À» 
// »©ÁÖ´Â °ÍÀÌ´Ù.
//--------------------------------------------------------------------------------
void
SetEffectInfo(MCreature* pCreature, EffectInfo* pEffectInfo, int delayedFrame)
{
	DEBUG_ADD_FORMAT( "Set Effect Info. id=%d", pCreature->GetID() );
	
	if (pEffectInfo!=NULL)
	{
		//--------------------------------------------------
		// °¢°¢ÀÇ Effect Status¸¦ ¼³Á¤ÇÑ´Ù.
		//--------------------------------------------------
		for (int i = 0; i < pEffectInfo->getListNum(); i++)
		{
			std::pair<WORD,DWORD>	Element		= pEffectInfo->popFrontListElement();
			EFFECTSTATUS			status		= (EFFECTSTATUS)Element.first;
			DWORD					duration	= Element.second;

//			if( status == EFFECTSTATUS_VIEW_HP )
//			{
//				int a = 0;
//			}
			//--------------------------------------------------
			// Á¾·ù¿¡ µû¶ó¼­..
			//--------------------------------------------------
			switch (status)
			{
				//--------------------------------------------------
				// ÈíÇ÷ ´çÇÑ°Å
				//--------------------------------------------------
				case EFFECTSTATUS_BLOOD_DRAIN :
					duration *= 10;
				break;
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
				case EFFECTSTATUS_SUMMON_SYLPH_GREEN :
				case EFFECTSTATUS_SUMMON_SYLPH_ORANGE :
				case EFFECTSTATUS_SUMMON_SYLPH_RED :
				case EFFECTSTATUS_SUMMON_SYLPH_YELLOW :
				case EFFECTSTATUS_SUMMON_SYLPH_WHITE :
				case EFFECTSTATUS_SUMMON_SYLPH_BROWN :
				case EFFECTSTATUS_SUMMON_SYLPH_LILAC :
				case EFFECTSTATUS_SUMMON_SYLPH_BLACK :
				case EFFECTSTATUS_SUMMON_SYLPH:
				case EFFECTSTATUS_SUMMON_WISP_RED:
				case EFFECTSTATUS_SUMMON_WISP_YELLOW:
				case EFFECTSTATUS_SUMMON_WISP_GREEN:
					{
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
						if(pCreature->GetWingType() == 2)
						{
#if __CONTENTS(__SECOND_TRANSFORTER)
							if(pCreature->GetWingItemType() == 0)
							{
#endif //__SECOND_TRANSFORTER
								status = EFFECTSTATUS_CLIENT_WING_SYLPH;
								pCreature->SetWingEffect1();
#if __CONTENTS(__SECOND_TRANSFORTER)
							}
							else if(pCreature->GetWingItemType() == 1)//Ä¦ÍÐ
							{
								status = EFFECTSTATUS_CLIENT_UNICORN;
								pCreature->SetWingEffect2();
							}
							else if(pCreature->GetWingItemType() == 2)//Ä§ÁéÐÂ×øÆï¸½¼Ó×´Ì¬
							{
								status = EFFECTSTATUS_OusterWings_New_1;
							//	pCreature->SetWingEffect3(0);
							}
							else if(pCreature->GetWingItemType() == 3)//Ä§ÁéÐÂ×øÆï¸½¼Ó×´Ì¬
							{
								status = EFFECTSTATUS_OusterWings_New_2;
							}
							//¶«¹æ ÄÚµå -- ¼­¹ö¿¡¼­ À®¾ÆÀÌÅÛÅ¸ÀÔÀÌ Á¤ÀÇµÇÁö ¾ÊÀº °ªÀÌ ¿Ã ¶§, °¡Àå Ã³À½ Ãß°¡µÈ ¼¼·¹°ïÀ¸·Î...
							else
							{
								status = EFFECTSTATUS_CLIENT_WING_SYLPH;
								pCreature->SetWingEffect1();
							}
							// - ¶«»§ ³¡.

#endif //__SECOND_TRANSFORTER
						}
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
					}
					break;
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
				//--------------------------------------------------
				// Coma»óÅÂ
				//--------------------------------------------------
				case EFFECTSTATUS_COMA :
					pCreature->SetCorpse();
				break;

				case EFFECTSTATUS_BACK_STAB_3 :
				case EFFECTSTATUS_ICE_OF_SOUL_STONE :
				case EFFECTSTATUS_TRAP_TRIGGERED :
				case EFFECTSTATUS_TRAPPED :
				case EFFECTSTATUS_GROUND_ELEMENTAL_CENTER:
				{
					TYPE_ACTIONINFO		ActionInfo = (*g_pEffectStatusTable)[ status ].ActionInfo;
					
					if( ActionInfo != ACTIONINFO_NULL )
					{						
						if( status == EFFECTSTATUS_TRAP_TRIGGERED || status == EFFECTSTATUS_TRAPPED )
							duration = ConvertDurationToFrame( duration );
						else
							duration = 18;					

						if( status == EFFECTSTATUS_ICE_OF_SOUL_STONE )
							duration = 19;
						if( status == EFFECTSTATUS_GROUND_ELEMENTAL_CENTER)
							duration = 0xFFFF;
						
						ExecuteActionInfoFromMainNode(
							ActionInfo,						
							pCreature->GetX(), pCreature->GetY(), 0,
							pCreature->GetDirection(),						
							pCreature->GetID(),
							pCreature->GetX(), pCreature->GetY(), 0,						
							duration,						
							NULL, status == EFFECTSTATUS_GROUND_ELEMENTAL_CENTER
							);
					}
				}
				break;
			}
			//ÀÌ°Í¸¸ ¿Ö ÀÎÆ®¿´À»±î...ÂÁ ¼öÁ¤ Å©¾Ñ
			DWORD				delayFrame	= ConvertDurationToFrame( duration );


			// loading½Ã°£À» »« delay frame
			delayFrame -= delayedFrame;

			// ½Ã°£ÀÌ ³²¾Æ ÀÖ´Â °æ¿ì¿¡¸¸...
			if (delayFrame > 0)
			{
				pCreature->AddEffectStatus( status, delayFrame );
			}
		}
	}
}

//--------------------------------------------------------------------------------
// Get FaceStyle
//--------------------------------------------------------------------------------
int 
UI_GetFaceStyle(int faceStyle)
{
	switch (faceStyle)
	{
	case HAIR_STYLE1 :
		return M_FACE1;
		break;
	case HAIR_STYLE2 :
		return M_FACE2;
		break;
	case HAIR_STYLE3 :
		return M_FACE3;
		break;
	}
	
	return 0;
}


//--------------------------------------------------------------------------------
// Set PCSlayerInfo
//--------------------------------------------------------------------------------
// Player¿¡°Ô slayer Á¤º¸¸¦ ¼³Á¤ÇÑ´Ù.
//--------------------------------------------------------------------------------
void
SetPCSlayerInfo(PCSlayerInfo2* pInfo)
{
	DEBUG_ADD( "Set Slayer Info" );
	
	g_pPlayer->SetID( pInfo->getObjectID() );
	g_pPlayer->SetSight( pInfo->getSight() );

	//--------------------------------------------------
	// Player ¸ö ¼³Á¤
	//--------------------------------------------------
	// slayer³² / ¿©

	if (pInfo->getCompetence()==0)
	{
		g_pPlayer->SetCompetence( 0 );
		g_pPlayer->SetCreatureType( CREATURETYPE_SLAYER_OPERATOR );
		g_pPlayer->SetMale( pInfo->getSex()==MALE );
	}
	else
	{
		g_pPlayer->SetCreatureType( (pInfo->getSex()==MALE)? CREATURETYPE_SLAYER_MALE : CREATURETYPE_SLAYER_FEMALE );
	}
	// ÇÇºÎ»ö
	g_pPlayer->SetBodyColor1( pInfo->getSkinColor() );
	g_pPlayer->SetMasterEffectType( pInfo->getMasterEffectColor() );

	// ¸Ó¸®			
	SetAddonToSlayer( g_pPlayer, pInfo );

	//--------------------------------------------------
	// ³» ±æµå ¼³Á¤
	//--------------------------------------------------
	int guildID = pInfo->getGuildID();

	g_pPlayer->SetGuildNumber( guildID );
	g_pPlayer->SetOriginServerNum( pInfo->getBorn() );

	if (pInfo!=NULL)
	{
		g_pUserInformation->GuildName = pInfo->getGuildName().c_str();
	}
	else
	{
		g_pUserInformation->GuildName.Release();
	}
	g_pUserInformation->GuildGrade = pInfo->getGuildMemberRank();

	//--------------------------------------------------
	// Á¤º¸Ã¢¿¡¼­ Ãâ·ÂÇÒ ¶§ ÇÊ¿äÇÑ Á¤º¸..
	//--------------------------------------------------
	g_char_slot_ingame.sz_name			= g_pUserInformation->CharacterID.GetString();
	if(g_pUserInformation->GuildName.GetString() == NULL)
		g_char_slot_ingame.sz_guild_name	= "";
	else
		g_char_slot_ingame.sz_guild_name	= g_pUserInformation->GuildName.GetString();

	g_char_slot_ingame.GUILD_ID			= guildID;
	g_char_slot_ingame.GUILD_GRADE		= g_pUserInformation->GuildGrade;

	g_char_slot_ingame.GRADE		= pInfo->getRank();
//	int accum = 0;
//	accum = g_pExperienceTable->GetRankInfo(g_char_slot_ingame.GRADE, g_pPlayer->GetRace()).AccumExp;
//	g_char_slot_ingame.GRADE_EXP_REMAIN = accum-pInfo->getRankExp();
	g_char_slot_ingame.GRADE_EXP_REMAIN = pInfo->getRankExp();

	g_char_slot_ingame.Race = RACE_SLAYER;
	g_char_slot_ingame.bl_female = !g_pPlayer->IsMale();

	g_char_slot_ingame.hair_color = pInfo->getHairColor();	
	g_char_slot_ingame.skin_color = pInfo->getSkinColor();

	g_char_slot_ingame.SlayerAdvancedStr = pInfo->getSlayerAdvancedStr();
	g_char_slot_ingame.SlayerAdvancedDex = pInfo->getSlayerAdvancedDex();
	g_char_slot_ingame.SlayerAdvancedInt = pInfo->getSlayerAdvancedInt();

#if __CONTENTS(__CONTRIBUTE_SYSTEM)
	g_char_slot_ingame.ContributePoint = pInfo->getContributePoint();
#endif //__CONTRIBUTE_SYSTEM

	g_pUserInformation->HairColor = pInfo->getHairColor();	
	g_pUserInformation->SkinColor = pInfo->getSkinColor();

	g_pGuildInfoMapper->SetGuildName( pInfo->getGuildID(), g_char_slot_ingame.sz_guild_name );

	//--------------------------------------------------
	// Effect Á¤º¸ Á¦°Å
	//--------------------------------------------------
	g_char_slot_ingame.STATUS.clear();
	
	// ¾ó±¼ ¼³Á¤
	g_char_slot_ingame.man_info.face = (CHAR_MAN)UI_GetFaceStyle(g_pUserInformation->FaceStyle);
	
	// 
	//g_pUserInformation->FaceStyle = pInfo->getHairStyle();
	
	// ±âº» º¹Àå
	/*
	MItem* pCoat = MItem::NewItem( ITEM_CLASS_COAT );
	MItem* pTrouser = MItem::NewItem( ITEM_CLASS_TROUSER );
	
	pCoat->SetItemType( 0 );				
	pTrouser->SetItemType( 0 );

	g_pPlayer->SetAddonItem( pCoat );	
	g_pPlayer->SetAddonItem( pTrouser);

	delete pCoat;
	delete pTrouser;
	*/


	//--------------------------------------------------
	// ÇöÀç »óÅÂ ¼³Á¤
	//--------------------------------------------------		
	HP_t maxHP	= pInfo->getHP( ATTR_MAX );
	HP_t HP		= pInfo->getHP( ATTR_CURRENT );
	MP_t maxMP	= pInfo->getMP( ATTR_MAX );
	MP_t MP		= pInfo->getMP( ATTR_CURRENT );
	int STR_CUR	= pInfo->getSTR( ATTR_CURRENT );
	int DEX_CUR	= pInfo->getDEX( ATTR_CURRENT );
	int INT_CUR	= pInfo->getINT( ATTR_CURRENT );
	int STR_MAX	= pInfo->getSTR( ATTR_MAX );
	int DEX_MAX	= pInfo->getDEX( ATTR_MAX );
	int INT_MAXX	= pInfo->getINT( ATTR_MAX );
	int STR_PURE	= pInfo->getSTR( ATTR_BASIC );
	int DEX_PURE	= pInfo->getDEX( ATTR_BASIC );
	int INT_PURE	= pInfo->getINT( ATTR_BASIC );
	int Fame	= pInfo->getFame();
	int STR_EXP_REMAIN	= pInfo->getSTRExp();
	int DEX_EXP_REMAIN	= pInfo->getDEXExp();
	int INT_EXP_REMAIN	= pInfo->getINTExp();
	//int Notority = pInfo->getNotoriety();

	//pInfo->getSkillDomainLevel( d );
	//pInfo->getSkillDomainExp( d );
	DEBUG_ADD( "Set Slayer Info : SetStatus" );

#if __CONTENTS(__ATTACK_SPEED)
	BYTE WeaponSpeed = pInfo->getAttackSpeed();
	g_pPlayer->SetStatus(MODIFY_ATTACK_SPEED, pInfo->getAttackSpeed());
	g_char_slot_ingame.WeaponSpeed = WeaponSpeed;
#endif //__ATTACK_SPEED	

	g_pPlayer->SetStatus( MODIFY_MAX_HP, maxHP);
	g_pPlayer->SetStatus( MODIFY_MAX_MP, maxMP);
	g_pPlayer->SetStatus( MODIFY_CURRENT_HP, HP);
	g_pPlayer->SetStatus( MODIFY_CURRENT_MP, MP);
	g_pPlayer->SetStatus( MODIFY_CURRENT_STR, STR_CUR);
	g_pPlayer->SetStatus( MODIFY_CURRENT_DEX, DEX_CUR);
	g_pPlayer->SetStatus( MODIFY_CURRENT_INT, INT_CUR);
	g_pPlayer->SetStatus( MODIFY_BASIC_STR, STR_PURE);
	g_pPlayer->SetStatus( MODIFY_BASIC_DEX, DEX_PURE);
	g_pPlayer->SetStatus( MODIFY_BASIC_INT, INT_PURE);
	g_pPlayer->SetStatus( MODIFY_MAX_STR, STR_MAX);
	g_pPlayer->SetStatus( MODIFY_MAX_DEX, DEX_MAX);
	g_pPlayer->SetStatus( MODIFY_MAX_INT, INT_MAXX);
	g_pPlayer->SetStatus( MODIFY_STR_EXP_REMAIN, STR_EXP_REMAIN);
	g_pPlayer->SetStatus( MODIFY_DEX_EXP_REMAIN, DEX_EXP_REMAIN);
	g_pPlayer->SetStatus( MODIFY_INT_EXP_REMAIN, INT_EXP_REMAIN);	
	g_pPlayer->SetStatus( MODIFY_FAME, Fame);
	g_pPlayer->SetStatus( MODIFY_ALIGNMENT, pInfo->getAlignment() );
	g_pPlayer->SetStatus( MODIFY_RANK, pInfo->getRank() );
	g_pPlayer->SetStatus( MODIFY_RANK_EXP_REMAIN, pInfo->getRankExp() );
	g_pPlayer->SetStatus( MODIFY_ADVANCEMENT_CLASS_LEVEL, pInfo->getAdvancementLevel() );

	
	// Sjheon 2005.08.02 Add
	g_pPlayer->SetStatus( MODIFY_ATTACK_BLOOD_BURST_POINT, pInfo->getAttackBloodBurstPoint() );
	g_pPlayer->SetStatus( MODIFY_DEFENSE_BLOOD_BURST_POINT, pInfo->getDefenseBloodBurstPoint() );
	g_pPlayer->SetStatus( MODIFY_PARTY_BLOOD_BURST_POINT, pInfo->getPartyBloodBurstPoint() );
	//UI_SetBloodBurstSetGage() ; 
	// Sjheon 2005.08.02 End

	//20070907 slayer ¸Á°¢ÀÇ ¼öÁ¤
	g_pPlayer->SetStatus(MODIFY_ADVANCED_SLAYERSTR, pInfo->getSlayerAdvancedStr());
	g_pPlayer->SetStatus(MODIFY_ADVANCED_SLAYERDEX, pInfo->getSlayerAdvancedDex());
	g_pPlayer->SetStatus(MODIFY_ADVANCED_SLAYERINT, pInfo->getSlayerAdvancedInt());

#if __CONTENTS(__CONTRIBUTE_SYSTEM)
	g_pPlayer->SetStatus(MODIFY_CONTRIBUTE_POINT, pInfo->getContributePoint());
#endif //__CONTRIBUTE_SYSTEM	

	// 2005, 1, 18, sobeit add start - ½ÂÁ÷ ½½·¹´Â º¸³Ê½º Æ÷ÀÎÆ®°¡ ÀÖ´Ù.
	int Bonus	= pInfo->getAttrBonus();
	g_pPlayer->SetStatus( MODIFY_BONUS_POINT, Bonus);
	// 2005, 1, 18, sobeit add end - ½ÂÁ÷ ½½·¹´Â º¸³Ê½º Æ÷ÀÎÆ®°¡ ÀÖ´Ù.

	g_pPlayer->SetStatus( MODIFY_ATTACK_SPEED,  pInfo->getAttackSpeed() );
	
	DEBUG_ADD( "Set Slayer Info: Set g_char_slot_ingame" );
	
	//--------------------------------------------------
	// UI¿¡ Á¤º¸ ¼³Á¤
	//--------------------------------------------------
	//UI_SetHP( HP, maxHP );
	//UI_SetMP( MP, maxMP );
	g_char_slot_ingame.level = 1;//g_pPlayer->GetVampExp();

	g_char_slot_ingame.alignment = (ALIGNMENT)ConvertAlignment(g_pPlayer->GetAlignment());

	g_char_slot_ingame.STR_CUR = STR_CUR;
	g_char_slot_ingame.DEX_CUR = DEX_CUR;
	g_char_slot_ingame.INT_CUR = INT_CUR;
	g_char_slot_ingame.STR_MAX = STR_MAX;
	g_char_slot_ingame.DEX_MAX = DEX_MAX;
	g_char_slot_ingame.INT_MAXX= INT_MAXX;
	g_char_slot_ingame.STR_PURE = STR_PURE;
	g_char_slot_ingame.DEX_PURE = DEX_PURE;
	g_char_slot_ingame.INT_PURE = INT_PURE;
	//g_char_slot_ingame.DAM =g_pPlayer->GetDAM();
	//g_char_slot_ingame.AC =g_pPlayer->GetAC();
	g_char_slot_ingame.TOHIT =g_pPlayer->GetTOHIT();
	g_char_slot_ingame.HP =g_pPlayer->GetHP();
	g_char_slot_ingame.MP =g_pPlayer->GetMP();
	g_char_slot_ingame.HP_MAX =g_pPlayer->GetMAX_HP();
	g_char_slot_ingame.MP_MAX =g_pPlayer->GetMAX_MP();
	//g_char_slot_ingame.CC =g_pPlayer->GetCARRYWEIGHT();
	g_char_slot_ingame.FAME =g_pPlayer->GetFAME();
//	g_char_slot_ingame.NOTERITY =g_pPlayer->GetNotoriety();

	g_char_slot_ingame.STR_EXP_REMAIN	= STR_EXP_REMAIN;
	g_char_slot_ingame.DEX_EXP_REMAIN	= DEX_EXP_REMAIN;
	g_char_slot_ingame.INT_EXP_REMAIN	= INT_EXP_REMAIN;

	if(pInfo->getAdvancementLevel() > 0)
		g_char_slot_ingame.EXP_REMAIN = pInfo->getAdvancementGoalExp();

	
	//--------------------------------------------------		
	// Domain Level ¼³Á¤
	//--------------------------------------------------
	DEBUG_ADD( "Set Slayer Info : Domain" );
	
	const int numDomains = 5;
	int domains[numDomains] = 
	{ 
		SKILLDOMAIN_BLADE,
		SKILLDOMAIN_SWORD,
		SKILLDOMAIN_GUN,
		SKILLDOMAIN_HEAL,
		SKILLDOMAIN_ENCHANT,			
	};

	for (int i=0; i<numDomains; i++)
	{
		int domain = domains[i];

		(*g_pSkillManager)[domain].SetDomainLevel( pInfo->getSkillDomainLevel( (SkillDomain)domain ) );
		(*g_pSkillManager)[domain].SetDomainExpRemain( pInfo->getSkillDomainExp( (SkillDomain)domain ) );
	}	
	
	DEBUG_ADD( "Set Slayer Info : Money" );
	

	//--------------------------------------------------		
	// µ· ¼³Á¤
	//--------------------------------------------------		
	g_pMoneyManager->SetMoney( pInfo->getGold() );
	g_pMoneyManager->SetDianJuan(pInfo->getDianJuan());
	g_pMoneyManager->SetJiFen(pInfo->getJiFen());

	//--------------------------------------------------
	//	PCS Number ÃÊ±âÈ­ 
	//--------------------------------------------------
//	g_pUserInformation->PCSNumber = pInfo->getPhoneNumber();
//	C_VS_UI_SLAYER_PDS::m_pcs_number = pInfo->getPhoneNumber();

	//--------------------------------------------------
	// Skill Hot key¼³Á¤
	//--------------------------------------------------
	if (!g_bSetHotKey)
	{		
		UI_SetHotKey( 0, pInfo->getHotKey( 0 ) );
		UI_SetHotKey( 1, pInfo->getHotKey( 1 ) );
		UI_SetHotKey( 2, pInfo->getHotKey( 2 ) );
		UI_SetHotKey( 3, pInfo->getHotKey( 3 ) );

		g_bSetHotKey = TRUE;
	}	

	DEBUG_ADD( "Set Slayer Info OK" );
}


//--------------------------------------------------------------------------------
// Set PCVampire Info
//--------------------------------------------------------------------------------
// Player¿¡°Ô vampire Á¤º¸¸¦ ¼³Á¤ÇÑ´Ù.
//--------------------------------------------------------------------------------
void		
SetPCVampireInfo(PCVampireInfo2* pInfo)
{
	DEBUG_ADD( "Set Vampire Info" );
	
	// ÀÓ½Ã·Î ¼³Á¤..
	//g_pPlayer->SetGuildNumber( 2 );

	g_pPlayer->SetID( pInfo->getObjectID() );
	g_pPlayer->SetSight( pInfo->getSight() );

	//--------------------------------------------------
	// Player ¸ö ¼³Á¤
	//--------------------------------------------------
	// ¹ÚÁã³ª ´Á´ë , °í½ºÆ® ·Î º¯½Å ÁßÀÎ °æ¿ì..
	if (g_PreviousCreatureType==CREATURETYPE_WOLF
		|| g_PreviousCreatureType==CREATURETYPE_BAT
		|| g_PreviousCreatureType==CREATURETYPE_VAMPIRE_GHOST
		|| g_PreviousCreatureType==CREATURETYPE_WER_WOLF
#if __CONTENTS(__FAST_TRANSFORTER)
		|| g_PreviousCreatureType==CREATURETYPE_FLITTERMOUSE
		|| g_PreviousCreatureType==CREATURETYPE_NEDE
		|| g_PreviousCreatureType==CREATURETYPE_KLTL
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
		|| g_PreviousCreatureType==CREATURETYPE_SHAPE_OF_DEMON
#endif //__SECOND_TRANSFORTER
		)
	{
		g_pPlayer->SetCreatureType( g_PreviousCreatureType );

		if( pInfo->getCompetence() == 0 )
			g_pPlayer->SetCompetence( 0 );
	}
	// Vampire³² : ¿©
	else
	{
		if (pInfo->getCompetence()==0)
		{
			g_pPlayer->SetCompetence( 0 );
			g_pPlayer->SetCreatureType( CREATURETYPE_VAMPIRE_OPERATOR );
			g_pPlayer->SetMale( pInfo->getSex()==MALE );
		}
		else
		{
			int creatureType = (pInfo->getSex()==MALE)? CREATURETYPE_VAMPIRE_MALE1 : CREATURETYPE_VAMPIRE_FEMALE1;
			g_pPlayer->SetCreatureType( creatureType );
		}
	}
	
	g_pPlayer->SetMale( pInfo->getSex()==MALE );

//	_MinTrace("sdfdsf:%d\n", pInfo->getSex() );

	// Áö»ó, °øÁß ÀÌµ¿ °áÁ¤
	if (g_pPlayer->GetCreatureType()==CREATURETYPE_BAT) // || g_pPlayer->GetCreatureType()==CREATURETYPE_VAMPIRE_GHOST)
	{
		g_pPlayer->SetFlyingCreature();		
	}
	else
	{
		g_pPlayer->SetGroundCreature();
	}

//	// ÇÇºÎ»ö
	g_pPlayer->SetBodyColor1( pInfo->getSkinColor() );
	g_pPlayer->SetMasterEffectType( pInfo->getMasterEffectColor() );

	g_pPlayer->SetMasterEffectType( pInfo->getMasterEffectColor() );

	if( g_pPlayer->GetCreatureType() == CREATURETYPE_WER_WOLF )
		g_pPlayer->SetBodyColor1( 377 );
//		g_pPlayer->SetBodyColor1( pInfo->getCoatColor() );

	// ¸Ó¸®»öÀ¸·Î ¹Ù²¼´Ù
//	g_pPlayer->SetBodyColor1( pInfo->getHairColor() );

	if( pInfo->getBatColor() != 0 )
		g_pPlayer->SetBatColor( pInfo->getBatColor() );
	else
		g_pPlayer->SetBatColor( 0xFFFF );
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
	g_pPlayer->SetWingType(pInfo->GetBatType());
#if __CONTENTS(__SECOND_TRANSFORTER)
	g_pPlayer->SetWingItemType(pInfo->getWingItemType());
#endif //__SECOND_TRANSFORTER
	if(pInfo->GetBatType() == 2)
	{
#if __CONTENTS(__SECOND_TRANSFORTER)
		if(pInfo->getWingItemType()==0)
		{
#endif //__SECOND_TRANSFORTER
			if(pInfo->GetWingColor1() != 0)
				g_pPlayer->SetWingColor( pInfo->GetWingColor1() );
			else
				g_pPlayer->SetWingColor( 403 );
			g_pPlayer->SetWingEffectColor(pInfo->GetWingColor2());
#if __CONTENTS(__SECOND_TRANSFORTER)
		}
		if(pInfo->getWingItemType()==1)
		{
			if(pInfo->GetWingColor1() != 0)
			g_pPlayer->SetWingColor( pInfo->GetWingColor1() );
			else
				g_pPlayer->SetWingColor( 403 );
			g_pPlayer->SetWingEffectColor(pInfo->GetWingColor2());
		}
#endif //__SECOND_TRANSFORTER
	}
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
	g_pPlayer->SetAdvanceBatColor(pInfo->getAdvanceBatColor());

	//--------------------------------------------------
	// [ TEST CODE ]
	//--------------------------------------------------
	// ¿Ê »ö±ò ¼³Á¤ÇÏ±â
	//--------------------------------------------------
//	g_pPlayer->SetBodyColor2( pInfo->getCoatColor() );
	///*
	if (g_pPlayer->IsMale())
	{
		g_pPlayer->SetBodyColor2( 377 );//91 );
	}
	else
	{
		g_pPlayer->SetBodyColor2( 377 );//38 );
	}
	//*/

//	g_pPlayer->SetAddonColorSet1( ADDON_COAT, pInfo->getSkinColor() );
//	g_pPlayer->SetAddonColorSet2( ADDON_COAT, pInfo->getSkinColor() );

	//--------------------------------------------------
	// ³» ±æµå ¼³Á¤
	//--------------------------------------------------
	int guildID = pInfo->getGuildID();

	g_pPlayer->SetGuildNumber( guildID );

	g_pPlayer->SetOriginServerNum( pInfo->getBorn() );

	if (pInfo!=NULL)
	{
		g_pUserInformation->GuildName = pInfo->getGuildName().c_str();
	}
	else
	{
		g_pUserInformation->GuildName.Release();
	}
	g_pUserInformation->GuildGrade = pInfo->getGuildMemberRank();

	g_pGuildInfoMapper->SetGuildName( pInfo->getGuildID(), g_char_slot_ingame.sz_guild_name );

	//--------------------------------------------------
	// Á¤º¸Ã¢¿¡¼­ Ãâ·ÂÇÒ ¶§ ÇÊ¿äÇÑ Á¤º¸..
	//--------------------------------------------------
	g_char_slot_ingame.sz_name			= g_pUserInformation->CharacterID.GetString();
	if(g_pUserInformation->GuildName.GetString() == NULL)
		g_char_slot_ingame.sz_guild_name	= "";
	else
		g_char_slot_ingame.sz_guild_name	= g_pUserInformation->GuildName.GetString();

	g_char_slot_ingame.GUILD_ID			= guildID;
	g_char_slot_ingame.GUILD_GRADE		= g_pUserInformation->GuildGrade;

	g_char_slot_ingame.GRADE		= pInfo->getRank();
//	int accum = 0;
//	accum = g_pExperienceTable->GetRankInfo(g_char_slot_ingame.GRADE, g_pPlayer->GetRace()).AccumExp;
//	g_char_slot_ingame.GRADE_EXP_REMAIN = accum-pInfo->getRankExp();
	g_char_slot_ingame.GRADE_EXP_REMAIN	= pInfo->getRankExp();

	g_char_slot_ingame.hair_color = pInfo->getBatColor();
	g_char_slot_ingame.skin_color = pInfo->getSkinColor();

#if __CONTENTS(__CONTRIBUTE_SYSTEM)
	g_char_slot_ingame.ContributePoint = pInfo->getContributePoint();
#endif //__CONTRIBUTE_SYSTEM

	g_pUserInformation->HairColor = pInfo->getBatColor();	
	g_pUserInformation->SkinColor = pInfo->getSkinColor();
	g_pUserInformation->BatColor  = pInfo->getBatColor();
	
	//--------------------------------------------------
	// Effect Á¤º¸ Á¦°Å
	//--------------------------------------------------
	g_char_slot_ingame.STATUS.clear();
	
	//g_pUserInformation->FaceStyle = pInfo->getHairStyle();

	// vampire default ¾ó±¼
	g_char_slot_ingame.man_info.face = M_FACE1;


	//--------------------------------------------------
	// ÇöÀç »óÅÂ ¼³Á¤
	//--------------------------------------------------
	HP_t maxHP	= pInfo->getHP( ATTR_MAX );
	HP_t HP		= pInfo->getHP( ATTR_CURRENT );
	int STR_CUR	= pInfo->getSTR( ATTR_CURRENT );
	int DEX_CUR	= pInfo->getDEX( ATTR_CURRENT );
	int INT_CUR	= pInfo->getINT( ATTR_CURRENT );
	int STR_MAX	= pInfo->getSTR( ATTR_MAX );
	int DEX_MAX	= pInfo->getDEX( ATTR_MAX );
	int INT_MAXX	= pInfo->getINT( ATTR_MAX );
	int STR_PURE	= pInfo->getSTR( ATTR_BASIC );
	int DEX_PURE	= pInfo->getDEX( ATTR_BASIC );
	int INT_PURE	= pInfo->getINT( ATTR_BASIC );
	//int STR_EXP	= pInfo->getSTRExp();
	//int DEX_EXP	= pInfo->getDEXExp();
	//int INT_EXP	= pInfo->getINTExp();
	int Exp		= pInfo->getExp();	
	int Bonus	= pInfo->getBonus();
	int Level	= pInfo->getLevel();	
	int Fame	= pInfo->getFame();
//	int Notority = pInfo->getNotoriety();

#if __CONTENTS(__ATTACK_SPEED)
	BYTE WeaponSpeed = pInfo->getAttackSpeed();
	g_pPlayer->SetStatus(MODIFY_ATTACK_SPEED, pInfo->getAttackSpeed());
	g_char_slot_ingame.WeaponSpeed = WeaponSpeed;
#endif //__ATTACK_SPEED

	g_pPlayer->SetStatus( MODIFY_MAX_HP, maxHP);
	g_pPlayer->SetStatus( MODIFY_CURRENT_HP, HP);
	g_pPlayer->SetStatus( MODIFY_CURRENT_STR, STR_CUR);
	g_pPlayer->SetStatus( MODIFY_CURRENT_DEX, DEX_CUR);
	g_pPlayer->SetStatus( MODIFY_CURRENT_INT, INT_CUR);
	g_pPlayer->SetStatus( MODIFY_BASIC_STR, STR_PURE);
	g_pPlayer->SetStatus( MODIFY_BASIC_DEX, DEX_PURE);
	g_pPlayer->SetStatus( MODIFY_BASIC_INT, INT_PURE);
	g_pPlayer->SetStatus( MODIFY_MAX_STR, STR_MAX);
	g_pPlayer->SetStatus( MODIFY_MAX_DEX, DEX_MAX);
	g_pPlayer->SetStatus( MODIFY_MAX_INT, INT_MAXX);
	g_pPlayer->SetStatus( MODIFY_BONUS_POINT, Bonus);
	g_pPlayer->SetStatus( MODIFY_LEVEL, Level);
	g_pPlayer->SetStatus( MODIFY_FAME, Fame);
//	g_pPlayer->SetStatus( MODIFY_NOTORIETY, Notority);
	g_pPlayer->SetStatus( MODIFY_VAMP_EXP_REMAIN, Exp);
	g_pPlayer->SetStatus( MODIFY_SILVER_DAMAGE, pInfo->getSilverDamage());	
	g_pPlayer->SetStatus( MODIFY_ALIGNMENT, pInfo->getAlignment() );
	g_pPlayer->SetStatus( MODIFY_RANK, pInfo->getRank() );
	g_pPlayer->SetStatus( MODIFY_RANK_EXP_REMAIN, pInfo->getRankExp() );
	g_pPlayer->SetStatus( MODIFY_ADVANCEMENT_CLASS_LEVEL, pInfo->getAdvancementLevel() );

	
	// Sjheon 2005.08.02 Add
	g_pPlayer->SetStatus( MODIFY_ATTACK_BLOOD_BURST_POINT, pInfo->getAttackBloodBurstPoint() );
	g_pPlayer->SetStatus( MODIFY_DEFENSE_BLOOD_BURST_POINT, pInfo->getDefenseBloodBurstPoint() );
	g_pPlayer->SetStatus( MODIFY_PARTY_BLOOD_BURST_POINT, pInfo->getPartyBloodBurstPoint() );
	// Sjheon 2005.08.02 End

	//g_pPlayer->SetStatus( MODIFY_STR_EXP, STR_EXP);
	//g_pPlayer->SetStatus( MODIFY_DEX_EXP, DEX_EXP);
	//g_pPlayer->SetStatus( MODIFY_INT_EXP, INT_EXP);	
	
	//--------------------------------------------------
	// ui¿¡ Ãâ·Â Á¤º¸ ¼³Á¤
	//--------------------------------------------------
	//g_char_slot_ingame.sz_name = g_pUserInformation->CharacterID.GetString();
	//g_char_slot_ingame.bl_vampire = g_pPlayer->IsVampire();
	//g_char_slot_ingame.bl_female = !g_pPlayer->IsMale();

	g_char_slot_ingame.level = g_pPlayer->GetLEVEL();
	g_char_slot_ingame.alignment = (ALIGNMENT)ConvertAlignment( g_pPlayer->GetAlignment() );

	g_char_slot_ingame.EXP_REMAIN	= pInfo->getExp();

	g_char_slot_ingame.STR_CUR = STR_CUR;
	g_char_slot_ingame.DEX_CUR = DEX_CUR;
	g_char_slot_ingame.INT_CUR = INT_CUR;
	g_char_slot_ingame.STR_MAX = STR_MAX;
	g_char_slot_ingame.DEX_MAX = DEX_MAX;
	g_char_slot_ingame.INT_MAXX = INT_MAXX;
	g_char_slot_ingame.STR_PURE = STR_PURE;
	g_char_slot_ingame.DEX_PURE = DEX_PURE;
	g_char_slot_ingame.INT_PURE = INT_PURE;
	//g_char_slot_ingame.DAM =g_pPlayer->GetDAM();
	//g_char_slot_ingame.AC =g_pPlayer->GetAC();
	g_char_slot_ingame.TOHIT =g_pPlayer->GetTOHIT();
	g_char_slot_ingame.HP =g_pPlayer->GetHP();
	g_char_slot_ingame.MP =g_pPlayer->GetMP();
	g_char_slot_ingame.HP_MAX =g_pPlayer->GetMAX_HP();
	g_char_slot_ingame.MP_MAX =g_pPlayer->GetMAX_MP();
	//g_char_slot_ingame.CC =g_pPlayer->GetCARRYWEIGHT();
	g_char_slot_ingame.FAME =g_pPlayer->GetFAME();
//	g_char_slot_ingame.NOTERITY =g_pPlayer->GetNotoriety();

	if(pInfo->getAdvancementLevel() > 0)
		g_char_slot_ingame.EXP_REMAIN = pInfo->getAdvancementGoalExp();

	//--------------------------------------------------
	// Domain Level ¼³Á¤
	//--------------------------------------------------
	/*
	const int numDomains = 1;
	int domains[numDomains] = 
	{ 
		SKILLDOMAIN_VAMPIRE
	};

	for (int i=0; i<numDomains; i++)
	{
		int domain = domains[i];

		(*g_pSkillManager)[domain].SetDomainLevel( pInfo->getSkillDomainLevel( SkillDomain)domain ) );
	}	
	*/

	//--------------------------------------------------
	// UI¿¡ Á¤º¸ ¼³Á¤
	//--------------------------------------------------
	//UI_SetHP( HP, maxHP );

	//--------------------------------------------------		
	// µ· ¼³Á¤
	//--------------------------------------------------		
	g_pMoneyManager->SetMoney( pInfo->getGold() );
	g_pMoneyManager->SetDianJuan(pInfo->getDianJuan());
	g_pMoneyManager->SetJiFen(pInfo->getJiFen());

	//--------------------------------------------------
	//	VampireGear ÃÊ±âÈ­
	//--------------------------------------------------			
	g_pVampireGear->Init();

	//--------------------------------------------------
	// Skill Hot key¼³Á¤
	//--------------------------------------------------
	if (!g_bSetHotKey)
	{		
		UI_SetHotKey( 0, pInfo->getHotKey( 0 ) );
		UI_SetHotKey( 1, pInfo->getHotKey( 1 ) );
		UI_SetHotKey( 2, pInfo->getHotKey( 2 ) );
		UI_SetHotKey( 3, pInfo->getHotKey( 3 ) );
		UI_SetHotKey( 4, pInfo->getHotKey( 4 ) );
		UI_SetHotKey( 5, pInfo->getHotKey( 5 ) );
		UI_SetHotKey( 6, pInfo->getHotKey( 6 ) );
		UI_SetHotKey( 7, pInfo->getHotKey( 7 ) );


		g_bSetHotKey = TRUE;		
	}

	DEBUG_ADD( "Set Vampire Info OK" );
}

//--------------------------------------------------------------------------------
// Set PCVampire Info
//--------------------------------------------------------------------------------
// Player¿¡°Ô vampire Á¤º¸¸¦ ¼³Á¤ÇÑ´Ù.
//--------------------------------------------------------------------------------
void		
SetPCOustersInfo(PCOustersInfo2* pInfo)
{
	DEBUG_ADD( "Set Ousters Info" );
	
	// ÀÓ½Ã·Î ¼³Á¤..
	//g_pPlayer->SetGuildNumber( 2 );

	g_pPlayer->SetID( pInfo->getObjectID() );
	g_pPlayer->SetSight( pInfo->getSight() );

	//--------------------------------------------------
	// Player ¸ö ¼³Á¤
	//--------------------------------------------------
	if (pInfo->getCompetence()==0)
	{
		g_pPlayer->SetCompetence( 0 );
		g_pPlayer->SetCreatureType( CREATURETYPE_OUSTERS_OPERATOR );
		g_pPlayer->SetMale( pInfo->getSex()==MALE );
	}
	else
	{
		int creatureType = CREATURETYPE_OUSTERS;
		g_pPlayer->SetCreatureType( creatureType );
	}
	
// 	g_pPlayer->SetMale( pInfo->getSex()==MALE );

	g_pPlayer->SetGroundCreature();

#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
	g_pPlayer->SetWingType(pInfo->getWingSylphType());
#if __CONTENTS(__SECOND_TRANSFORTER)
	g_pPlayer->SetWingItemType(pInfo->getWingItemType());
#endif //__SECOND_TRANSFORTER
	if(pInfo->getWingSylphType() == 2)
	{
#if __CONTENTS(__SECOND_TRANSFORTER)
		if(pInfo->getWingItemType()==0)
		{
#endif //__SECOND_TRANSFORTER
			if(pInfo->getWingBodyColor() != 0)
				g_pPlayer->SetWingColor( pInfo->getWingBodyColor() );
			else
				g_pPlayer->SetWingColor( 0xFFFF );
			g_pPlayer->SetWingEffectColor(pInfo->getWingEffectColor());
#if __CONTENTS(__SECOND_TRANSFORTER)
		}
		if(pInfo->getWingItemType()==1)
		{
			if(pInfo->getWingBodyColor() != 0)
				g_pPlayer->SetWingColor( pInfo->getWingBodyColor() );
			else
				g_pPlayer->SetWingColor( 0xFFFF );
			g_pPlayer->SetWingEffectColor(pInfo->getWingEffectColor());
		}
#endif //__SECOND_TRANSFORTER
	}
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
	// ¸Ó¸®»ö
	g_pPlayer->SetBodyColor1( pInfo->getHairColor() );
	g_pPlayer->SetMasterEffectType( pInfo->getMasterEffectColor() );

//	g_pPlayer->SetAddonColorSet1()

	//--------------------------------------------------
	// [ TEST CODE ]
	//--------------------------------------------------
	// ¿Ê »ö±ò ¼³Á¤ÇÏ±â
	//--------------------------------------------------
//	g_pPlayer->SetBodyColor2( pInfo->getCoatColor() );
	///*
//	if (g_pPlayer->IsMale())
//	{
//		g_pPlayer->SetBodyColor2( 377 );//91 );
//	}
//	else
//	{
//		g_pPlayer->SetBodyColor2( 377 );//38 );
//	}
	//*/

//	g_pPlayer->SetAddonColorSet1( ADDON_COAT, pInfo->getSkinColor() );
//	g_pPlayer->SetAddonColorSet2( ADDON_COAT, pInfo->getSkinColor() );


	//--------------------------------------------------
	// ³» ±æµå ¼³Á¤
	//--------------------------------------------------
	int guildID = pInfo->getGuildID();

	g_pPlayer->SetGuildNumber( guildID );
	g_pPlayer->SetOriginServerNum( pInfo->getBorn() );

	if (pInfo!=NULL)
	{
		g_pUserInformation->GuildName = pInfo->getGuildName().c_str();
	}
	else
	{
		g_pUserInformation->GuildName.Release();
	}
	g_pUserInformation->GuildGrade = pInfo->getGuildMemberRank();

	//--------------------------------------------------
	// Á¤º¸Ã¢¿¡¼­ Ãâ·ÂÇÒ ¶§ ÇÊ¿äÇÑ Á¤º¸..
	//--------------------------------------------------
	g_char_slot_ingame.sz_name			= g_pUserInformation->CharacterID.GetString();
	if(g_pUserInformation->GuildName.GetString() == NULL)
		g_char_slot_ingame.sz_guild_name	= "";
	else
		g_char_slot_ingame.sz_guild_name	= g_pUserInformation->GuildName.GetString();

	g_pGuildInfoMapper->SetGuildName( pInfo->getGuildID(), g_char_slot_ingame.sz_guild_name );

	g_char_slot_ingame.GUILD_ID			= guildID;
	g_char_slot_ingame.GUILD_GRADE		= g_pUserInformation->GuildGrade;

	g_char_slot_ingame.GRADE		= pInfo->getRank();
//	int accum = 0;
//	accum = g_pExperienceTable->GetRankInfo(g_char_slot_ingame.GRADE, g_pPlayer->GetRace()).AccumExp;
//	g_char_slot_ingame.GRADE_EXP_REMAIN = accum-pInfo->getRankExp();
	g_char_slot_ingame.GRADE_EXP_REMAIN	= pInfo->getRankExp();

	g_char_slot_ingame.hair_color = pInfo->getHairColor();
//	g_char_slot_ingame.skin_color = pInfo->getSkinColor();

#if __CONTENTS(__CONTRIBUTE_SYSTEM)
	g_char_slot_ingame.ContributePoint = pInfo->getContributePoint();
#endif //__CONTRIBUTE_SYSTEM

	g_pUserInformation->HairColor = pInfo->getHairColor();	
//	g_pUserInformation->SkinColor = pInfo->getSkinColor();
	
	//--------------------------------------------------
	// Effect Á¤º¸ Á¦°Å
	//--------------------------------------------------
	g_char_slot_ingame.STATUS.clear();
	
	//g_pUserInformation->FaceStyle = pInfo->getHairStyle();

	// vampire default ¾ó±¼
	g_char_slot_ingame.man_info.face = M_FACE1;


	//--------------------------------------------------
	// ÇöÀç »óÅÂ ¼³Á¤
	//--------------------------------------------------
	HP_t maxHP	= pInfo->getHP( ATTR_MAX );
	MP_t maxMP	= pInfo->getMP( ATTR_MAX );
	HP_t HP		= pInfo->getHP( ATTR_CURRENT );
	MP_t MP		= pInfo->getMP( ATTR_CURRENT );
	int STR_CUR	= pInfo->getSTR( ATTR_CURRENT );
	int DEX_CUR	= pInfo->getDEX( ATTR_CURRENT );
	int INT_CUR	= pInfo->getINT( ATTR_CURRENT );
	int STR_MAX	= pInfo->getSTR( ATTR_MAX );
	int DEX_MAX	= pInfo->getDEX( ATTR_MAX );
	int INT_MAXX	= pInfo->getINT( ATTR_MAX );
	int STR_PURE	= pInfo->getSTR( ATTR_BASIC );
	int DEX_PURE	= pInfo->getDEX( ATTR_BASIC );
	int INT_PURE	= pInfo->getINT( ATTR_BASIC );
	//int STR_EXP	= pInfo->getSTRExp();
	//int DEX_EXP	= pInfo->getDEXExp();
	//int INT_EXP	= pInfo->getINTExp();
	int Exp		= pInfo->getExp();	
	int Bonus	= pInfo->getBonus();
	int skillPoint	= pInfo->getSkillBonus();
	int Level	= pInfo->getLevel();	
	int Fame	= pInfo->getFame();
//	int Notority = pInfo->getNotoriety();

#if __CONTENTS(__ATTACK_SPEED)
	BYTE WeaponSpeed = pInfo->getAttackSpeed();
	g_pPlayer->SetStatus(MODIFY_ATTACK_SPEED, pInfo->getAttackSpeed());
	g_char_slot_ingame.WeaponSpeed = WeaponSpeed;
#endif //__ATTACK_SPEED

	g_pPlayer->SetStatus( MODIFY_MAX_HP, maxHP);
	g_pPlayer->SetStatus( MODIFY_MAX_MP, maxMP);
	g_pPlayer->SetStatus( MODIFY_CURRENT_HP, HP);
	g_pPlayer->SetStatus( MODIFY_CURRENT_MP, MP);
	g_pPlayer->SetStatus( MODIFY_CURRENT_STR, STR_CUR);
	g_pPlayer->SetStatus( MODIFY_CURRENT_DEX, DEX_CUR);
	g_pPlayer->SetStatus( MODIFY_CURRENT_INT, INT_CUR);
	g_pPlayer->SetStatus( MODIFY_BASIC_STR, STR_PURE);
	g_pPlayer->SetStatus( MODIFY_BASIC_DEX, DEX_PURE);
	g_pPlayer->SetStatus( MODIFY_BASIC_INT, INT_PURE);
	g_pPlayer->SetStatus( MODIFY_MAX_STR, STR_MAX);
	g_pPlayer->SetStatus( MODIFY_MAX_DEX, DEX_MAX);
	g_pPlayer->SetStatus( MODIFY_MAX_INT, INT_MAXX);
	g_pPlayer->SetStatus( MODIFY_BONUS_POINT, Bonus);
	g_pPlayer->SetStatus( MODIFY_SKILL_BONUS_POINT, skillPoint);
	g_pPlayer->SetStatus( MODIFY_LEVEL, Level);
	g_pPlayer->SetStatus( MODIFY_FAME, Fame);
//	g_pPlayer->SetStatus( MODIFY_NOTORIETY, Notority);
	g_pPlayer->SetStatus( MODIFY_VAMP_EXP_REMAIN, Exp);
	g_pPlayer->SetStatus( MODIFY_SILVER_DAMAGE, pInfo->getSilverDamage());	
	g_pPlayer->SetStatus( MODIFY_ALIGNMENT, pInfo->getAlignment() );
	g_pPlayer->SetStatus( MODIFY_RANK, pInfo->getRank() );
	g_pPlayer->SetStatus( MODIFY_RANK_EXP_REMAIN, pInfo->getRankExp() );
	g_pPlayer->SetStatus( MODIFY_ADVANCEMENT_CLASS_LEVEL, pInfo->getAdvancementLevel() );	

	
	// Sjheon 2005.08.02 Add
	g_pPlayer->SetStatus( MODIFY_ATTACK_BLOOD_BURST_POINT, pInfo->getAttackBloodBurstPoint() );
	g_pPlayer->SetStatus( MODIFY_DEFENSE_BLOOD_BURST_POINT, pInfo->getDefenseBloodBurstPoint() );
	g_pPlayer->SetStatus( MODIFY_PARTY_BLOOD_BURST_POINT, pInfo->getPartyBloodBurstPoint() );
	// Sjheon 2005.08.02 End
	

	//g_pPlayer->SetStatus( MODIFY_STR_EXP, STR_EXP);
	//g_pPlayer->SetStatus( MODIFY_DEX_EXP, DEX_EXP);
	//g_pPlayer->SetStatus( MODIFY_INT_EXP, INT_EXP);	
	
	//--------------------------------------------------
	// ui¿¡ Ãâ·Â Á¤º¸ ¼³Á¤
	//--------------------------------------------------
	//g_char_slot_ingame.sz_name = g_pUserInformation->CharacterID.GetString();
	//g_char_slot_ingame.bl_vampire = g_pPlayer->IsVampire();
	//g_char_slot_ingame.bl_female = !g_pPlayer->IsMale();

	g_char_slot_ingame.level = g_pPlayer->GetLEVEL();
	g_char_slot_ingame.alignment = (ALIGNMENT)ConvertAlignment( g_pPlayer->GetAlignment() );

	g_char_slot_ingame.EXP_REMAIN	= pInfo->getExp();

	g_char_slot_ingame.STR_CUR = STR_CUR;
	g_char_slot_ingame.DEX_CUR = DEX_CUR;
	g_char_slot_ingame.INT_CUR = INT_CUR;
	g_char_slot_ingame.STR_MAX = STR_MAX;
	g_char_slot_ingame.DEX_MAX = DEX_MAX;
	g_char_slot_ingame.INT_MAXX = INT_MAXX;
	g_char_slot_ingame.STR_PURE = STR_PURE;
	g_char_slot_ingame.DEX_PURE = DEX_PURE;
	g_char_slot_ingame.INT_PURE = INT_PURE;
	//g_char_slot_ingame.DAM =g_pPlayer->GetDAM();
	//g_char_slot_ingame.AC =g_pPlayer->GetAC();
	g_char_slot_ingame.TOHIT =g_pPlayer->GetTOHIT();
	g_char_slot_ingame.HP =g_pPlayer->GetHP();
	g_char_slot_ingame.MP =g_pPlayer->GetMP();
	g_char_slot_ingame.HP_MAX =g_pPlayer->GetMAX_HP();
	g_char_slot_ingame.MP_MAX =g_pPlayer->GetMAX_MP();
	//g_char_slot_ingame.CC =g_pPlayer->GetCARRYWEIGHT();
	g_char_slot_ingame.FAME =g_pPlayer->GetFAME();
//	g_char_slot_ingame.NOTERITY =g_pPlayer->GetNotoriety();

	if(pInfo->getAdvancementLevel() > 0)
		g_char_slot_ingame.EXP_REMAIN = pInfo->getAdvancementGoalExp();

	//--------------------------------------------------
	// Domain Level ¼³Á¤
	//--------------------------------------------------
	/*
	const int numDomains = 1;
	int domains[numDomains] = 
	{ 
		SKILLDOMAIN_VAMPIRE
	};

	for (int i=0; i<numDomains; i++)
	{
		int domain = domains[i];

		(*g_pSkillManager)[domain].SetDomainLevel( pInfo->getSkillDomainLevel( SkillDomain)domain ) );
	}	
	*/

	//--------------------------------------------------
	// UI¿¡ Á¤º¸ ¼³Á¤
	//--------------------------------------------------
	//UI_SetHP( HP, maxHP );

	//--------------------------------------------------		
	// µ· ¼³Á¤
	//--------------------------------------------------		
	g_pMoneyManager->SetMoney( pInfo->getGold() );
	g_pMoneyManager->SetDianJuan(pInfo->getDianJuan());
	g_pMoneyManager->SetJiFen(pInfo->getJiFen());

	//--------------------------------------------------
	//	OustersGear ÃÊ±âÈ­
	//--------------------------------------------------			
	g_pOustersGear->Init();

//	//--------------------------------------------------
//	// Skill Hot key¼³Á¤
//	//--------------------------------------------------
//	if (!g_bSetHotKey)
//	{		
//		UI_SetHotKey( 0, pInfo->getHotKey( 0 ) );
//		UI_SetHotKey( 1, pInfo->getHotKey( 1 ) );
//		UI_SetHotKey( 2, pInfo->getHotKey( 2 ) );
//		UI_SetHotKey( 3, pInfo->getHotKey( 3 ) );
//		UI_SetHotKey( 4, pInfo->getHotKey( 4 ) );
//		UI_SetHotKey( 5, pInfo->getHotKey( 5 ) );
//		UI_SetHotKey( 6, pInfo->getHotKey( 6 ) );
//		UI_SetHotKey( 7, pInfo->getHotKey( 7 ) );
//
//
//		g_bSetHotKey = TRUE;		
//	}

	DEBUG_ADD( "Set Ousters Info OK" );
}

//-----------------------------------------------------------------------------
// Popup Error Message
//-----------------------------------------------------------------------------
void
PopupErrorMessage(ErrorID errorID)
{
	switch (errorID)
	{
		case INVALID_ID_PASSWORD : 
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_INVALID_ID_PASSWORD].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
		break;

		case ALREADY_CONNECTED : 
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_ALREADY_CONNECTED].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
		break;

		case ALREADY_REGISTER_ID : 
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_ALREADY_REGISTER_ID].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
		break;

		case ALREADY_REGISTER_SSN : 
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_ALREADY_REGISTER_SSN].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
		break;

		case EMPTY_ID : 
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_EMPTY_ID].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
		break;

		case SMALL_ID_LENGTH : 
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_SMALL_ID_LENGTH].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
		break;

		case EMPTY_PASSWORD : 
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_EMPTY_PASSWORD].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
		break;

		case SMALL_PASSWORD_LENGTH : 
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_SMALL_PASSWORD_LENGTH].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
		break;

		case EMPTY_NAME : 
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_EMPTY_NAME].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
		break;

		case EMPTY_SSN : 
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_EMPTY_SSN].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
		break;

		case INVALID_SSN : 
			{	
				if(!g_pUserInformation->IsNetmarble)
					g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_INVALID_SSN].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
				else
					g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_INVALID_DELETE].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
			}			
		break;

		case NOT_FOUND_PLAYER :
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_NOT_FOUND_PLAYER].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
		break;

		case NOT_FOUND_ID :
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_NOT_FOUND_ID].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
		break;

		case NOT_ALLOW_ACCOUNT:
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_NOT_ALLOW_ACCOUNT].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
		break;

		case NOT_PAY_ACCOUNT:
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_NOT_PAY_ACCOUNT].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
		break;

		// 2004, 03, 26 sobeit add start
		case CANNOT_AUTHORIZE_BILLING:   // ºô¸µ Á¤º¸¸¦ Ã£À» ¼ö ¾ø½À´Ï´Ù.
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_CANNOT_AUTHORIZE_BILLING].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
		break;
		case CANNOT_CREATE_PC_BILLING:    // À¯·á »ç¿ëÀÚ°¡ ¾Æ´Ï¶ó¼­ Ä³¸¯ÅÍ¸¦ ¸ø ¸¸µì´Ï´Ù.
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_CANNOT_CREATE_PC_BILLING].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
		break;
		// 2004, 03, 26 sobeit add end
		
		// 2004, 7, 19 sobeit add start
		case KEY_EXPIRED:
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_KEY_EXPIRED].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
			break;
		case NOT_FOUND_KEY:
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_NOT_FOUND_KEY].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
			break;
		// 2004, 7, 19 sobeit add end
		case ETC_ERROR:
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_LOGIN_DENY].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
			break;
		case IP_DENYED:
			g_pUIDialog->PopupFreeMessageDlg("You can't play this. Play your country version, Please.", -1,-1,UI_DIALOG_TITLE_OK, true);
			break;
		case NOT_AVAILABLE:
			g_pUIDialog->PopupFreeMessageDlg( (*g_pGameStringTable)[UI_STRING_MESSAGE_NOT_AVAILABLE].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
			break;	

		case DELETE_PC_ERROR_GUILD_MASTER:
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[UI_STRING_MESSAGE_GUILDMASTER_NOTDELETE].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
			break;
		case NEED_USE_AGREEMENT:
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[UI_STRING_MESSAGE_NEED_USE_AGREEMENT].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
			break;
		//20071116 - ½ºÇÇµåÇÙ Æä³ÎÆ¼·Î ÀÎÇÑ ·Î±ä½ÇÆÐ.
		case SPEED_HACK_PENALTY_USER:
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[UI_STRING_MESSAGE_SPEED_HACK_PENALTY_USER].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
			break;
		//2008.08.25	- 
		case INSPECTING_SERVER:
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_INSPECTING_SERVER_ERROR].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
			break;
		case NO_ADULT:
			g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_NO_ADULT].GetString(), -1,-1,UI_DIALOG_TITLE_OK, true);
			break;
		default : //case ETC_ERROR : 
				g_pUIDialog->PopupFreeMessageDlg((*g_pGameStringTable)[STRING_ERROR_ETC_ERROR].GetString());
				
	}

}

//-----------------------------------------------------------------------------
// Set ServerGroupName
//-----------------------------------------------------------------------------
void
SetServerGroupName( const char* pName )
{
	g_pServerInformation->SetServerGroupName( pName );
}

//-----------------------------------------------------------------------------
// Set ServerGroupName
//-----------------------------------------------------------------------------
void
SetServerGroupStatus( int status )
{
	g_pServerInformation->SetServerGroupStatus( status );
}

//-----------------------------------------------------------------------------
// Set ServerName
//-----------------------------------------------------------------------------
void
SetServerName( const char* pName )
{
//	g_pServerInformation->SetServerName( pName );
}

//-----------------------------------------------------------------------------
// Use Item OK
//-----------------------------------------------------------------------------
// Potion»ç¿ë
//-----------------------------------------------------------------------------
bool
UseItemOK()
{
	//------------------------------------------------------------------
	//
	//				Item Check Buffer È®ÀÎ
	//
	//------------------------------------------------------------------	
	MItem* pItem = g_pPlayer->GetItemCheckBuffer();

	//----------------------------------------------------
	// Check Buffer¿¡ itemÀÌ ÀÖ´Â °æ¿ì
	//----------------------------------------------------
	if (pItem!=NULL)
	{
		PlaySound( pItem->GetUseSoundID() );

		//-------------------------------------------------
		// Force Feel
		//-------------------------------------------------
		if (g_pUserOption->UseForceFeel && gpC_Imm!=NULL && gpC_Imm->IsDevice()
			&& pItem->GetUseSoundID() < g_pSoundTable->GetSize())
		{
			DEBUG_ADD_FORMAT("ForceAction-UseItemOK(%d)", pItem->GetUseSoundID());
			gpC_Imm->ForceAction( pItem->GetUseSoundID() );
		}

		MPlayer::ITEM_CHECK_BUFFER status =	g_pPlayer->GetItemCheckBufferStatus();

		if( status == MPlayer::ITEM_CHECK_BUFFER_ITEM_TO_ITEM )
		{
			g_pPlayer->ClearItemCheckBuffer();
			if( g_pTempInformation->GetMode() == TempInformation::MODE_ITEM_CODE_SHEET )
			{
				char type = char(g_pTempInformation->Value1)+1;
				
				int invenX = HIWORD( g_pTempInformation->Value2);
				int invenY = LOWORD( g_pTempInformation->Value2);
				
				std::list<TYPE_ITEM_OPTION> OldItemOption = pItem->GetItemOptionList();
				
				int offset = invenY * 10 + invenX;
				if( offset >=0 && offset<60 &&OldItemOption.size()==30)
				{
					pItem->ClearItemOption();
					int cur_off=0;
					std::list<TYPE_ITEM_OPTION>::iterator itr = OldItemOption.begin();
					std::list<TYPE_ITEM_OPTION>::iterator enditr = OldItemOption.end();
					
					while( itr != enditr )
					{
						TYPE_ITEM_OPTION option = *itr;
						if(offset >= cur_off && offset < cur_off+2)
						{
							if( offset == cur_off )
								option = (type<<4)|(option&0xf);
							else
								option = ((option&0xf0))|(type&0xf);
						}
						pItem->AddItemOption( option );						
						cur_off+=2;
						++itr;
					}					
				}				
				UI_DropItem();
				if( g_pTempInformation->pValue != NULL )
				{
					MItem *pMouseItem = (MItem*)(g_pTempInformation->pValue);
					if( pMouseItem != NULL )
						delete pMouseItem;
				}
				g_pTempInformation->SetMode( TempInformation::MODE_NULL );								
				gC_vs_ui.RunQuestInventory(pItem);
				g_pTempInformation->pValue = NULL;
			}
		} else
		//----------------------------------------------------
		// Inventory¿¡¼­ »ç¿ë
		//----------------------------------------------------		
		if (status==MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY)			
		{			
			// Item Check Buffer¸¦ Áö¿î´Ù.
			DWORD SubInvetoryID = g_pPlayer->GetItemIDCheckBufferSubInventory();
			g_pPlayer->ClearItemCheckBuffer();

			//-------------------------------------------------
			// VampirePortalÀÎ °æ¿ì
			//-------------------------------------------------
			/*
			if (pItem->GetItemClass()==ITEM_CLASS_VAMPIRE_PORTAL_ITEM)
			{
				MVampirePortalItem* pPortalItem = (MVampirePortalItem*)pItem;

				if (!pPortalItem->IsMarked())
				{
					int zoneID = (g_bZonePlayerInLarge? g_nZoneLarge : g_nZoneSmall);
					int zoneX = g_pPlayer->GetServerX();
					int zoneY = g_pPlayer->GetServerY();
					pPortalItem->SetZone(zoneID, zoneX, zoneY);
				}
			}
			*/

			//-------------------------------------------------
			// »ç¿ëÇÏ´Â ¾ÆÀÌÅÛÀÎ °æ¿ì´Â ¼ýÀÚ¸¦ ÁÙÀÎ´Ù.
			//-------------------------------------------------
			if ((pItem->IsChargeItem() || pItem->IsPileItem())  && (pItem->GetItemClass() != ITEM_CLASS_VAMPIRE_PORTAL_ITEM))
			{
				pItem->SetNumber( max(0, pItem->GetNumber() - 1) );
			}

			if(pItem->GetItemClass() == ITEM_CLASS_DYE_POTION )
			{
				TYPE_ITEMTYPE	ItemType = pItem->GetItemType();
				// Çì¾î»öÀº ½½·¹ÀÌ¾î, ¾Æ¿ì½ºÅÍÁî¸¸
				if(ItemType >= 0 && ItemType <= 23 )
				{
					if(g_pPlayer->IsSlayer())
					{
						int color_set = g_DyeColorSet[ItemType];
						if(g_pPlayer->IsAdvancementClass())
							g_pPlayer->SetAddonColorSet1( ADDON_COAT, (WORD) color_set );
						else
							g_pPlayer->SetAddonHair( g_pPlayer->GetHairFrameID(), (WORD) color_set );
						g_pUserInformation->HairColor = color_set;
					}
					else if (g_pPlayer->IsOusters() )
					{
						int color_set = g_DyeColorSet[ItemType];
						g_pPlayer->SetBodyColor1( color_set );
						g_pUserInformation->HairColor = color_set;
					}
				} else
				if( ItemType >=24 && ItemType <= 47 )
				{
					int color_set = g_DyeColorSet[ItemType];
					if(g_pPlayer->IsSlayer())
					{
						g_pPlayer->SetAddonColorSet1(ADDON_COAT, color_set);
					}						
					else
						g_pPlayer->SetBodyColor1( color_set );
					g_pUserInformation->SkinColor = color_set;
				} else
				if( ItemType == 48 )
				{
					// ¼ºÀüÈ¯ ¾ÆÀÌÅÛÀÌ´Ù.
					if( !g_pPlayer->IsOusters() )
					{
						
						if( g_pPlayer->IsSlayer() )
						{
							const MCreatureWear::ADDON_INFO& addon= g_pPlayer->GetAddonInfo( ADDON_HAIR );
						
							g_pPlayer->SetCreatureType( (g_pPlayer->IsMale()==true)? CREATURETYPE_SLAYER_FEMALE: CREATURETYPE_SLAYER_MALE );
							g_pPlayer->SetMale( !g_pPlayer->IsMale() );

							g_pPlayer->SetAddonHair(g_PacketHairID[addon.FrameID], addon.ColorSet1);
						}
						else
						{
							int creatureType = (g_pPlayer->IsMale()==true)? CREATURETYPE_VAMPIRE_MALE1 : CREATURETYPE_VAMPIRE_FEMALE1;
							g_pPlayer->SetCreatureType( creatureType );
							g_pPlayer->SetMale( !g_pPlayer->IsMale() );
						
						}
							
						
						// °¡Áö°í ÀÖ´Â ¸ðµç ¾ÆÀÌÅÛ¿¡ ´ëÇØ¼­ Ã¼Å©ÇÑ´Ù.
						if( g_pPlayer->IsSlayer() )
							g_pSlayerGear->CheckAffectStatusAll();
						else if( g_pPlayer->IsVampire() )
							g_pVampireGear->CheckAffectStatusAll();
						
						g_pInventory->CheckAffectStatusAll();
						
						g_char_slot_ingame.bl_female = g_pPlayer->IsFemale();
						
					}
				}
				//¹ÚÁã ¸¶½ºÅÍ ÀÌÆåÆ® ÄÃ·¯ º¯°æ
				//23±×¸°, 2ºí·ç, 33·¹µå, 82¿»·Î, 380È­ÀÌÆ®, 50½ºÄ«ÀÌºí·ç, 151¶óÀÏ¶ô, 395ºí·¢, 0xFFFF±âº»
				else if( ItemType >= 49 && ItemType <= 57 )
				{
					WORD colorset_list[9] = {23, 2, 33, 82, 380, 50, 151, 395, 0xFFFF};
					int myColor = ItemType - 49;
					
					g_pPlayer->SetBatColor( colorset_list[myColor] );
					UI_PopupMessage( STRING_MESSAGE_SUCCESS_CHANGED_BAT_COLOR );
				}
				//°í½ºÆ® ¸¶½ºÅÍ ÀÌÆåÆ® ÄÃ·¯ º¯°æ by diesirace 20070308
				else if( ItemType >= 76 && ItemType <= 79 )
				{
					WORD colorset_list[9] = {36, 6, 0, 262};
					int myColor = ItemType - 76;
					
					g_pPlayer->SetAdvanceBatColor( colorset_list[myColor] );
					UI_PopupMessage( STRING_MESSAGE_SUCCESS_CHANGED_ADVANCE_BAT_COLOR );
				}
				else if( ItemType >= 58 && ItemType <= 61 )
				{
					if(ItemType == 61)
						g_pPlayer->ChangeMasterEffectType(0);
					else
						g_pPlayer->ChangeMasterEffectType(ItemType - 57);
					UI_PopupMessage( UI_STRING_MESSAGE_EFFECT_APPLY );
					//UI_PopupMessage( STRING_MESSAGE_SUCCESS_CHANGE );

				}
				else if( ItemType >= 62 && ItemType <= 63 )
				{
					// sjheon	2005.05.16
					if(ItemType == 63)
						g_pPlayer->ChangeMasterEffectType(0);
					else
						g_pPlayer->ChangeMasterEffectType(4);
					UI_PopupMessage( UI_STRING_MESSAGE_EFFECT_APPLY );
					// sjheon	2005.05.16
				}
				// nanomech 2006.05.24 Add
				else if( ItemType >= 68 && ItemType <= 75 )//8type color
				{
					//COLORREF color_table[8] = {RGB_RED,RGB_BLUE,RGB_GREEN,RGB_INDIGO,RGB_ORANGE,RGB_YELLOW,RGB_WHITE,RGB_GRAY};
					int myColor = ItemType - 68;

					g_pPlayer->SetPersnalShopColor( MCreature::s_PersnalShopColor[myColor] );
					//g_pPlayer->SetPersnalString(
				}
				// nanomech 2006.05.24 End
				else if(ItemType >= 65 && ItemType <= 67)
				{
					UI_PopupMessage( UI_STRING_MESSAGE_EFFECT_APPLY );
				}
			}
			else if(pItem->GetItemClass() == ITEM_CLASS_SUB_INVENTORY )
			{
				// sub inventory Ã³¸®´Â GCSubInventoryInfo¿¡¼­ ÇÑ´Ù.
				g_pPlayer->SetItemCheckBuffer( pItem, MPlayer::ITEM_CHECK_BUFFER_USE_FROM_INVENTORY);
			}
			// 2004, 6, 18 sobeit add start - naming pet used
//			if(pItem->GetItemClass() == ITEM_CLASS_EVENT_GIFT_BOX )
//			{
//				if(pItem->GetItemType() == 22)
//					gC_vs_ui.SetChangeableNickName(true);
//				else if(pItem->GetItemType() == 23)
//					gC_vs_ui.SetChangeablePetNickName(true);
//			}
			// 2004, 6, 18 sobeit add end - naming pet used
			//-------------------------------------------------
			// ¾ø¾îÁöÁö ¾Ê´Â °æ¿ì
			//-------------------------------------------------
			if (pItem->IsPileItem() && pItem->GetNumber()>0
				|| pItem->IsChargeItem() && pItem->GetNumber()>0
				|| pItem->GetItemClass()==ITEM_CLASS_SLAYER_PORTAL_ITEM
				|| pItem->GetItemClass()==ITEM_CLASS_OUSTERS_SUMMON_ITEM
				|| pItem->GetItemClass()==ITEM_CLASS_PET_ITEM
				|| pItem->GetItemClass()==ITEM_CLASS_SUB_INVENTORY
#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
				|| pItem->GetItemClass()==ITEM_CLASS_VAMPIREWING_ITEM
				|| pItem->GetItemClass()==ITEM_CLASS_OUSTERSWING_ITEM
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
				)
			{
			}
			//-------------------------------------------------
			// Á¦°ÅÇÏ´Â °æ¿ì
			//-------------------------------------------------
			else
			{
				if(SubInvetoryID != 0 && SubInvetoryID != OBJECTID_NULL)
				{
					MSubInventory* SubInventoryItem = (MSubInventory*)g_pInventory->GetItem(SubInvetoryID);
					if(NULL != SubInventoryItem)
					{
						SubInventoryItem->RemoveItem((TYPE_OBJECTID)pItem->GetID());
						// itemÁ¤º¸ Á¦°Å
						UI_RemoveDescriptor( (void*)pItem );

						// memory¿¡¼­ Á¦°Å
						delete pItem;		
					}
				}
				else
				{
					// inventory¿¡¼­ Á¦°Å
					g_pInventory->RemoveItem( (TYPE_OBJECTID)pItem->GetID() );

					// itemÁ¤º¸ Á¦°Å
					UI_RemoveDescriptor( (void*)pItem );

					// memory¿¡¼­ Á¦°Å
					delete pItem;			
				}
			}
		
		}
		//----------------------------------------------------
		// QuickSlot¿¡¼­ »ç¿ë
		//----------------------------------------------------
		else if (status==MPlayer::ITEM_CHECK_BUFFER_USE_FROM_QUICKSLOT)
		{	
			// Item Check Buffer¸¦ Áö¿î´Ù.
			g_pPlayer->ClearItemCheckBuffer();

			// 2004, 10, 5, sobeit add start - Äü½½·Ô¿¡¼­ ¿ÀÅä¹ÙÀÌÅ° »ç¿ë
			if(pItem->GetItemClass() == ITEM_CLASS_KEY)
			{
				// ÇÒ°Ô ¾ø³×..^^
			}
			// 2004, 10, 5, sobeit add start
			//-------------------------------------------------
			// °³¼ö Ã¼Å©¸¦ ÇØ¾ßÇÑ´Ù.
			//-------------------------------------------------
			else if (pItem->IsPileItem() && pItem->GetNumber()>1)
			{
				// ¾ÆÁ÷ °³¼ö°¡ ´õ ³²¾Æ ÀÖ´Â °æ¿ì,
				// °³¼ö¸¦ ÇÏ³ª ÁÙ¿©ÁØ´Ù.
				pItem->SetNumber( pItem->GetNumber() - 1 );
			}
			//-------------------------------------------------
			// ´Ù »ç¿ëÇÑ °æ¿ì --> Á¦°ÅÇÑ´Ù.
			//-------------------------------------------------
			else
			{
				// ¾ÆÀÌÅÛÀ» ´Ù »ç¿ëÇßÀ» °æ¿ì °°Àº ¾ÆÀÌÅÛÀÌ ÀÎº¥Åä¸®¿¡ ÀÖ´Ù¸é Äü½½·ÔÀ¸·Î ¿Å±ä´Ù.
				MItem* pNextItem	= g_pInventory->FindItem(pItem->GetItemClass(), pItem->GetItemType());
				BYTE nItemSlot		= pItem->GetItemSlot();

				// quickSlot¿¡¼­ Á¦°Å
				if( g_pPlayer->IsSlayer() )
				{
					g_pQuickSlot->RemoveItem( (BYTE)pItem->GetItemSlot() );

					if(pNextItem != NULL)
						gC_vs_ui.AutoMoveInventoryItemToQuickSlot(
							pNextItem->GetGridX(), pNextItem->GetGridY(), nItemSlot);	// Äü½½·ÔÀ¸·Î °í°í
				}
				else if (g_pPlayer->IsOusters() )
				{
					MOustersArmsBand* pQuickSlot = NULL;
					// ¾ÆÀÌÅÛÀÌ ÀÖ´Â ¾Ï½º¹êµå¸¦ °Ë»öÇÑ´Ù.
					
					if( g_pArmsBand1 != NULL && g_pArmsBand1->GetItemToModify( pItem->GetID() ) == pItem )
						pQuickSlot = g_pArmsBand1;
					if( g_pArmsBand2 != NULL && g_pArmsBand2->GetItemToModify( pItem->GetID() ) == pItem )
					{
						pQuickSlot = g_pArmsBand2;
						// by svi
						if (g_pArmsBand1 != NULL)
							nItemSlot += g_pArmsBand1->GetPocketNumber() ;  
					}

					if( pQuickSlot != NULL ) {
						pQuickSlot->RemoveItem( (BYTE)pItem->GetItemSlot() );
						
						if(pNextItem != NULL)
							gC_vs_ui.AutoMoveInventoryItemToQuickSlot(
								pNextItem->GetGridX(), pNextItem->GetGridY(), nItemSlot);	// Äü½½·ÔÀ¸·Î °í°í
					}
				}
				// itemÁ¤º¸ Á¦°Å
				UI_RemoveDescriptor( (void*)pItem );

				// memory¿¡¼­ Á¦°Å
				delete pItem;
			}

			//----------------------------------------------------
			// º§Æ® ¸ø ¾ø¾Öµµ·Ï ÇÑ°Å.. Ãë¼Ò
			//----------------------------------------------------
			UI_UnlockGear();
		}
		//----------------------------------------------------
		// ´Ù¸¥ »óÅÂ??
		//----------------------------------------------------
		else if( status == MPlayer::ITEM_CHECK_BUFFER_USE_FROM_GEAR)
		{
			g_pPlayer->ClearItemCheckBuffer();

			if( pItem->GetItemClass() == ITEM_CLASS_COUPLE_RING || 
				pItem->GetItemClass() == ITEM_CLASS_VAMPIRE_COUPLE_RING ||
				pItem->GetItemClass() == ITEM_CLASS_OUSTERS_HARMONIC_PENDENT

				)
			{
				// -_- Ä¿ÇÃ¸µ ,  °á¼ÓÀÇ ÆÒ´øÆ® ÀÌ¸é........ status...´Â »ç¿ë ¾ÈÇÔ.
				
				if( !g_pPlayer->IsWaitVerifyNULL() )
					return false;
				
				g_pPlayer->SetWaitVerify( MPlayer::WAIT_VERIFY_LOVE_CHAIN );
				g_pPlayer->AddEffectStatus( EFFECTSTATUS_LOVE_CHAIN , 100 );	
//				g_pSystemMessage->AddFormat((*g_pGameStringTable)[UI_STRING_MESSAGE_TRACE].GetString(), (*g_pGameStringTable)[STRING_MESSAGE_COUPLE].GetString());
				
				MEvent event;
				event.eventID = EVENTID_LOVECHAIN;
				event.eventDelay = 10000;
				event.eventFlag = EVENTFLAG_SHOW_DELAY_STRING;
				event.eventType = EVENTTYPE_ZONE;

				if(pItem->GetItemClass() == ITEM_CLASS_OUSTERS_HARMONIC_PENDENT)
				{
					event.m_StringsID.push_back(STRING_MESSAGE_OUSTERS_COUPLE_MOVE_START);
					event.m_StringsID.push_back(STRING_MESSAGE_MOVE_DELAY_SEC);
				}
				else
				{
					event.m_StringsID.push_back(STRING_MESSAGE_COUPLE_MOVE_START);
					event.m_StringsID.push_back(STRING_MESSAGE_MOVE_DELAY_SEC);
				}

				g_pEventManager->AddEvent(event);
			} 
		}
		// 2004, 9, 13, sobeit add start - Äù½ºÆ® ÀÎº¥ ¾ÆÀÌÅÛ »ç¿ë Çß´Ù
		else if(status == MPlayer::ITEM_CHECK_BUFFER_USE_FROM_GQUEST_INVENTORY)
		{
			g_pPlayer->ClearItemCheckBuffer();
			gC_vs_ui.DeleteQuestItem(pItem->GetItemSlot());
		}
		// 2004, 9, 13, sobeit add end - Äù½ºÆ® ÀÎº¥ ¾ÆÀÌÅÛ »ç¿ë Çß´Ù
		else
		{
			DEBUG_ADD_FORMAT("[Error] ItemCheck Buffer is not Use Status: status=%d", (int)status);

			return false;
		}

	}
	//----------------------------------------------------
	// itemÀÌ ¾ø´Â °æ¿ì.. - -;;
	//----------------------------------------------------
	else
	{
		DEBUG_ADD("[Error] No Item in CheckBuffer");
		
		return false;
	}

	return true;
}

//------------------------------------------------------------------
// Affect ModifyInfo ( MStatus*, ModifyInfo* )
//------------------------------------------------------------------
void
AffectModifyInfo(MStatus* pStatus, ModifyInfo* pInfo)
{
	//------------------------------------------------------------------
	// »óÅÂ°ªÀ» ¹Ù²Û´Ù.
	//------------------------------------------------------------------
	int i;

	SHORTDATA sData;
	LONGDATA lData;

	DEBUG_ADD("AMo");

	int shortNum = pInfo->getShortCount();
	int longNum = pInfo->getLongCount();

	for (i=0; i<shortNum; i++)
	{
		pInfo->popShortData( sData );
		
		pStatus->SetStatus( sData.type, sData.value );		
	}

	DEBUG_ADD("LD");
	
	for (i=0; i<longNum; i++)
	{
		pInfo->popLongData( lData );
		
		pStatus->SetStatus( lData.type, lData.value );		
	}

	DEBUG_ADD("AM_ok");
}

//------------------------------------------------------------------
// Packet CrossCounter
//------------------------------------------------------------------
// user --> target 
//------------------------------------------------------------------
void
SkillCrossCounter(MCreature* pUserCreature, MCreature* pTargetCreature, int skillID)
{
	//------------------------------------------------------------------
	// Ã¼Å© Ã¼Å©~
	//------------------------------------------------------------------
	if (pUserCreature==NULL || pTargetCreature==NULL)
	{
		DEBUG_ADD("[Error] CrossCounter. Creature NULL or Not WearCreature");
		
		return;
	}

	// [ TEST CODE ]
	// ÁøÇàÁßÀÎ EffectÀÌ¸é Result·Î Ãß°¡ÇØ¾ß ÇÑ´Ù.
	// Result¸¦ »ý¼ºÇÏ°í..
	// pUserCreature->>AddActionResult( ... )
		
	//------------------------------------------------------
	// Fake CreatureÀÇ ÁÂÇ¥ °è»ê
	//------------------------------------------------------
	int x = pTargetCreature->GetX();
	int y = pTargetCreature->GetY();
	
	// ¸Â´Â ¾Ö¿¡¼­ player¹æÇâÀ¸·Î ÇÑ Ä­..
	int sx = pUserCreature->GetX() - x;
	int sy = pUserCreature->GetY() - y;

	if (sx>0) sx=1; else if (sx<0) sx=-1; else sx=0;
	if (sy>0) sy=1; else if (sy<0) sy=-1; else sy=0;

	x += sx;
	y += sy;					

	//------------------------------------------------------
	// Fake Creature »ý¼º
	//------------------------------------------------------
	MFakeCreature* pFakeCreature = g_pZone->NewFakeCreature( pUserCreature, x, y );

	int dir = pFakeCreature->GetDirectionToPosition( pTargetCreature->GetX(), pTargetCreature->GetY() );
	pFakeCreature->SetDirection( dir );
	pFakeCreature->SetCurrentDirection( dir );

	pFakeCreature->SetAction( ACTION_ATTACK );		// ±×³É.. - -;;

	//------------------------------------------------------
	// ÀÜ»ó ÇÑ¹ø º¸¿©ÁÖ°í »ç¶óÁö°Ô ¼³Á¤
	//------------------------------------------------------
	pFakeCreature->SetFakeCreatureType( MFakeCreature::FAKE_CREATURE_FADE_ACTION );	

	//------------------------------------------------------
	// Fake Creature¸¦ Zone¿¡ Ãß°¡
	//------------------------------------------------------
	if (!g_pZone->AddFakeCreature( pFakeCreature ))
	{
		delete pFakeCreature;
	}

	//------------------------------------------------------
	// ±â¼ú »ç¿ë
	//------------------------------------------------------
	if (skillID==SKILL_ATTACK_MELEE)
	{	
		skillID = pUserCreature->GetBasicActionInfo();
	}

	if (skillID >= g_pActionInfoTable->GetMinResultActionInfo())
	{
		DEBUG_ADD_FORMAT("[Error] SkillType Error = %d", skillID);
		return;
	}

	MActionResult* pResult = new MActionResult;

	DWORD delayFrame = 0;//ConvertDurationToFrame( pPacket->getDuration() );

	pResult->Add( new MActionResultNodeActionInfo( 
								skillID, 
								pUserCreature->GetID(),
								pTargetCreature->GetID(),
								x,
								y,
								delayFrame ) );

	//------------------------------------------------------
	// EffectStatus°¡ ÀÖ´Ù¸é ºÙÀÎ´Ù.
	//------------------------------------------------------
	/*
	EFFECTSTATUS es = (*g_pActionInfoTable)[skillID].GetEffectStatus();
	
	if (es!=EFFECTSTATUS_NULL)
	{
		pResult->Add( new MActionResultNodeAddEffectStatus( pFakeCreature->GetID(),
																es, 
																delayFrame ) );
	}
	*/

	pFakeCreature->PacketSpecialActionToOther(
						skillID, 
						pTargetCreature->GetID(),
						pResult			// °á°ú
	);			
	
}

//------------------------------------------------------------------
// Skill ShadowDancing // [»õ±â¼ú]
//------------------------------------------------------------------
// user --> target 
//------------------------------------------------------------------
void
SkillShadowDancing(MCreature* pUserCreature, MCreature* pTargetCreature, int skillID)
{
	//------------------------------------------------------------------
	// Ã¼Å© Ã¼Å©~
	//------------------------------------------------------------------
	if (pUserCreature==NULL || pTargetCreature==NULL)
	{
		DEBUG_ADD("[Error] ShadowDancing. Creature NULL or Not WearCreature");
		
		return;
	}

	// [ TEST CODE ]
	// ÁøÇàÁßÀÎ EffectÀÌ¸é Result·Î Ãß°¡ÇØ¾ß ÇÑ´Ù.
	// Result¸¦ »ý¼ºÇÏ°í..
	// pUserCreature->>AddActionResult( ... )
		
	//------------------------------------------------------
	// Fake CreatureÀÇ ÁÂÇ¥ °è»ê
	//------------------------------------------------------
	int x = pTargetCreature->GetX();
	int y = pTargetCreature->GetY();
	
	// ¸Â´Â ¾Ö¿¡¼­ player¹æÇâÀ¸·Î ÇÑ Ä­..
	int sx = pUserCreature->GetX() - x;
	int sy = pUserCreature->GetY() - y;

	if (sx>0) sx=1; else if (sx<0) sx=-1; else sx=0;
	if (sy>0) sy=1; else if (sy<0) sy=-1; else sy=0;

	//------------------------------------------------------
	// Fake Creature »ý¼º
	//------------------------------------------------------
	POINT cxy[3] = 
	{
		{ sx, sy },
		{ sx, -sy },
		{ -sx, sy }
	};

	for (int i=0; i<3; i++)
	{	
		MFakeCreature* pFakeCreature = g_pZone->NewFakeCreature( pUserCreature, pUserCreature->GetX(), pUserCreature->GetY());

		int dir = pFakeCreature->GetDirectionToPosition( pTargetCreature->GetX(), pTargetCreature->GetY() );
		pFakeCreature->SetDirection( dir );
		pFakeCreature->SetCurrentDirection( dir );

		pFakeCreature->SetAction( ACTION_SLAYER_SWORD );		// ±×³É.. - -;;

		//------------------------------------------------------
		// ÀÜ»ó ÇÑ¹ø º¸¿©ÁÖ°í »ç¶óÁö°Ô ¼³Á¤
		//------------------------------------------------------
		pFakeCreature->SetFakeCreatureType( MFakeCreature::FAKE_CREATURE_FAST_MOVE_ACTION );

		//------------------------------------------------------
		// Fake Creature¸¦ Zone¿¡ Ãß°¡
		//------------------------------------------------------
		if (!g_pZone->AddFakeCreature( pFakeCreature ))
		{
			delete pFakeCreature;
		}

		//------------------------------------------------------
		// ±â¼ú »ç¿ë
		//------------------------------------------------------
		if (skillID==SKILL_ATTACK_MELEE)
		{	
			skillID = pUserCreature->GetBasicActionInfo();
		}

		if (skillID >= g_pActionInfoTable->GetMinResultActionInfo())
		{
			DEBUG_ADD_FORMAT("[Error] SkillType Error = %d", skillID);
			return;
		}


		pFakeCreature->SetFakeCreatureFastMoveAction(x+cxy[i].x, y+cxy[i].y, 
													skillID, 
													pTargetCreature->GetID());
	}

}

//-----------------------------------------------------------------------------
// Create ActionResultNode
//-----------------------------------------------------------------------------
// Creature¿¡ skillID¿¡ ºÙ´Â ActionResultNode¸¦ »ý¼ºÇÑ´Ù.
//-----------------------------------------------------------------------------
MActionResultNode*
CreateActionResultNode(MCreature* pCreature, int skillID, BYTE grade)
{
	//------------------------------------------------------
	//
	// skill¿¡ °á°ú°¡ ÀÖÀ¸¸é Àû¿ë ½ÃÅ²´Ù.
	//
	//------------------------------------------------------
	MActionResultNode* pActionResultNode = NULL;

	switch ((*g_pActionInfoTable)[skillID].GetActionResultID())
	{
		//------------------------------------------------------
		// Burrow
		//------------------------------------------------------
		case ACTIONRESULTNODE_CREATURE_BURROW :
			DEBUG_ADD("[ACTIONRESULTNODE_CREATURE_BURROW]");
			
			pActionResultNode = new MActionResultNodeCreatureBurrow(pCreature->GetID());
		break;

		//------------------------------------------------------
		// Invisible
		//------------------------------------------------------
		case ACTIONRESULTNODE_CREATURE_INVISIBLE :
			DEBUG_ADD("[ACTIONRESULTNODE_CREATURE_INVISIBLE]");
			
			pActionResultNode = new MActionResultNodeCreatureInvisible(pCreature->GetID());
		break;		

		//------------------------------------------------------
		// Visible
		//------------------------------------------------------
		case ACTIONRESULTNODE_CREATURE_VISIBLE :
			DEBUG_ADD("[ACTIONRESULTNODE_CREATURE_VISIBLE]");
			
			pActionResultNode = new MActionResultNodeCreatureVisible(pCreature->GetID());

			pCreature->RemoveEffectStatus( EFFECTSTATUS_INVISIBILITY );
			pCreature->RemoveEffectStatus( EFFECTSTATUS_SNIPPING_MODE );
			pCreature->RemoveEffectStatus( EFFECTSTATUS_SNIPPING_MODE_2 );
		break;

		//------------------------------------------------------
		// Snipping
		//------------------------------------------------------
		case ACTIONRESULTNODE_CREATURE_SNIPPING :			
			DEBUG_ADD("[ACTIONRESULTNODE_CREATURE_SNIPPING]");
			
			pActionResultNode = new MActionResultNodeCreatureSnipping(pCreature->GetID());						
		break;
		case ACTIONRESULTNODE_CREATURE_SNIPPING_2 :			
			DEBUG_ADD("[ACTIONRESULTNODE_CREATURE_SNIPPING_2]");

			pActionResultNode = new MActionResultNodeCreatureSnipping2(pCreature->GetID());						
			break;

		//------------------------------------------------------
		// Turning
		//------------------------------------------------------
		case ACTIONRESULTNODE_CREATURE_TURNING :			
			DEBUG_ADD("[ACTIONRESULTNODE_CREATURE_TURNING]");

			if( skillID == SKILL_TYPHOON )
			{
				if( grade == 1 )
					pActionResultNode = new MActionResultNodeCreatureTurning(pCreature->GetID(), 16);
			}
			else
				pActionResultNode = new MActionResultNodeCreatureTurning(pCreature->GetID(), 16);
		break;

		//------------------------------------------------------
		// Casket [»õ±â¼ú]
		//------------------------------------------------------
		case ACTIONRESULTNODE_SUMMON_CASKET :			
			DEBUG_ADD("[ACTIONRESULTNODE_SUMMON_CASKET]");
			
			pActionResultNode = new MActionResultNodeSummonCasket(pCreature->GetID(), 0);
		break;

		//------------------------------------------------------
		// FakeDie
		//------------------------------------------------------
		case ACTIONRESULTNODE_FAKE_DIE:
			DEBUG_ADD("[ACTIONRESULTNODE_FAKE_DIE]");
			
			pActionResultNode = new MActionResultNodeFakeDie(pCreature->GetID());
			pCreature->SetFakeDie();
		break;

		//------------------------------------------------------
		// EVENT
		//------------------------------------------------------
		case ACTIONRESULTNODE_EVENT:
			DEBUG_ADD("[ACTIONRESULTNODE_EVENT]");
			
			pActionResultNode = new MActionResultNodeEvent(skillID);
		break;

	}


	return pActionResultNode;
}

//-----------------------------------------------------------------------------
// Check Item For SkillIcon
//-----------------------------------------------------------------------------
// ÀÌ ºÎºÐÀº MItem¿¡ °¢ item¸¶´ÙÀÇ skill iconÀ» Ã¼Å©ÇÏ´Â
// virtual member functionÀ» ¸¸µé¾î¾ß ÇÑ´Ù.
// Áö±ÝÀº Çì´õ ÄÄÆÄÀÏ°ú ½Ã°£ °ü°è»ó ÀÌ·¸°Ô °£´Ù. - -; T_T;
//-----------------------------------------------------------------------------
void
CheckItemForSkillIcon(const MItem* pItem)
{
	ITEM_CLASS itemClass = pItem->GetItemClass();

	// Æ¯Á¤ item classÀÎ °æ¿ì´Â skill iconÀÌ ¹Ù²ï´Ù.
	if (g_pPlayer->IsSlayer()
		&& (itemClass==ITEM_CLASS_HOLYWATER
			|| itemClass==ITEM_CLASS_SLAYER_PORTAL_ITEM
			|| itemClass==ITEM_CLASS_BOMB
			|| itemClass==ITEM_CLASS_MINE
			|| itemClass==ITEM_CLASS_BOMB_MATERIAL)

		|| g_pPlayer->IsVampire()
		&& (itemClass==ITEM_CLASS_VAMPIRE_PORTAL_ITEM
			|| itemClass==ITEM_CLASS_VAMPIRE_ETC)
		)
	{
		g_pSkillAvailable->SetAvailableSkills();
	}	
}


void		SetFadeStart(char start, char end, char step, BYTE r, BYTE g, BYTE b,WORD delay, BYTE delayPostion)
{
	g_pTopView->SetFadeStart(start, end, step, r, g, b, delay, delayPostion);
}

void		SetFadeEnd()
{
	g_pTopView->SetFadeEnd();
}

//------------------------------------------------------------------
// Skill ShadowDancing // [»õ±â¼ú]
//------------------------------------------------------------------
// user --> target 
//------------------------------------------------------------------
void
SkillIllendue(MCreature* pUserCreature, MCreature* pTargetCreature, int skillID, int shape)
{
	//------------------------------------------------------------------
	// Ã¼Å© Ã¼Å©~
	//------------------------------------------------------------------
	if (pUserCreature==NULL || pTargetCreature==NULL)
	{
		DEBUG_ADD("[Error] ShadowDancing. Creature NULL or Not WearCreature");
		
		return;
	}

	// [ TEST CODE ]
	// ÁøÇàÁßÀÎ EffectÀÌ¸é Result·Î Ãß°¡ÇØ¾ß ÇÑ´Ù.
	// Result¸¦ »ý¼ºÇÏ°í..
	// pUserCreature->>AddActionResult( ... )
		
	//------------------------------------------------------
	// Fake CreatureÀÇ ÁÂÇ¥ °è»ê
	//------------------------------------------------------
	int x = pTargetCreature->GetX();
	int y = pTargetCreature->GetY();
	
	// ¸Â´Â ¾Ö¿¡¼­ player¹æÇâÀ¸·Î ÇÑ Ä­..
	int sx = pUserCreature->GetX() - x;
	int sy = pUserCreature->GetY() - y;

	if (sx>0) sx=1; else if (sx<0) sx=-1; else sx=0;
	if (sy>0) sy=1; else if (sy<0) sy=-1; else sy=0;

	//------------------------------------------------------
	// Fake Creature »ý¼º
	//------------------------------------------------------

	POINT Straight[4] = {
		{ -2, -2 },
		{ -2,  2 },
		{ 2,  -2 },
		{ 2,   2 },
	};

	POINT Diagonal[4] = {
		{ 0,  2 },
		{ 2,  0 },
		{ -2, 0 },
		{ 0, -2 },
	};

	POINT *Position;
	
	switch(shape) {
		case 0: // ÀÚµ¿
			Position = (pUserCreature->GetDirection() & 0x1) ? Diagonal : Straight;
			break;
		case 1: // ½ÊÀÚ¸ð¾ç(+)
			Position = Diagonal;
			break;
		case 2: // ¿¢½º¸ð¾ç(x)
			Position = Straight;
			break;
	}
	
	for (int i=0; i<4; i++)
	{	
		//MFakeCreature* pFakeCreature = NewFakeCreature( pUserCreature, pTargetCreature->GetX() + Position[i].x, pTargetCreature->GetY() + Position[i].y);
		MFakeCreature* pFakeCreature = g_pZone->NewFakeCreature( pUserCreature, pUserCreature->GetX() , pUserCreature->GetY() );

		int dir = pFakeCreature->GetDirectionToPosition( pTargetCreature->GetX(), pTargetCreature->GetY() );
		pFakeCreature->SetDirection( dir );
		pFakeCreature->SetCurrentDirection( dir );

		pFakeCreature->SetAction( ACTION_MAGIC );		// ±×³É.. - -;;

		//------------------------------------------------------
		// ÀÜ»ó ÇÑ¹ø º¸¿©ÁÖ°í »ç¶óÁö°Ô ¼³Á¤
		//------------------------------------------------------
		//pFakeCreature->SetFakeCreatureType( MFakeCreature::FAKE_CREATURE_BRIGHTNESS );						
		pFakeCreature->SetFakeCreatureType( MFakeCreature::FAKE_CREATURE_FAST_MOVE_ACTION );

		//------------------------------------------------------
		// Fake Creature¸¦ Zone¿¡ Ãß°¡
		//------------------------------------------------------
		if (!g_pZone->AddFakeCreature( pFakeCreature ))
		{
			delete pFakeCreature;
		}

		//------------------------------------------------------
		// ±â¼ú »ç¿ë
		//------------------------------------------------------
		if (skillID==SKILL_ATTACK_MELEE)
		{	
			skillID = pUserCreature->GetBasicActionInfo();
		}

		if (skillID >= g_pActionInfoTable->GetMinResultActionInfo())
		{
			DEBUG_ADD_FORMAT("[Error] SkillType Error = %d", skillID);
			return;
		}

//		MActionResult* pResult = new MActionResult;
		
		DWORD delayFrame = 0;//ConvertDurationToFrame( pPacket->getDuration() );
		
		pFakeCreature->SetFakeCreatureFastMoveAction(
			pTargetCreature->GetX() + Position[i].x, pTargetCreature->GetY() + Position[i].y,
			skillID, 
			pTargetCreature->GetID() );
		
//		pResult->Add( new MActionResultNodeActionInfo( 
//			skillID, 
//			pUserCreature->GetID(),
//			pTargetCreature->GetID(),
//			x,
//			y,
//			delayFrame ) );
//		
//		pFakeCreature->PacketSpecialActionToOther(
//			skillID, 
//			pTargetCreature->GetID(),
//			pResult			// °á°ú
//			);			
	}
}
void
SkillBatStorm1(MCreature* pUserCreature,MCreature* pTargetCreature,int targetX, int targetY,int skillID, int shape)
{
	//------------------------------------------------------------------
	// Ã¼Å© Ã¼Å©~
	//------------------------------------------------------------------
	if (pUserCreature==NULL)
	{
		DEBUG_ADD("[Error] ShadowDancing. Creature NULL or Not WearCreature");
		
		return;
	}
	 // POINT point;
    //  point = MTopView::MapToPixel(targetX, targetY);
	//------------------------------------------------------
	// Fake CreatureÀÇ ÁÂÇ¥ °è»ê
	//------------------------------------------------------
	int x =  targetX;
	int y = targetY;
	
	// ¸Â´Â ¾Ö¿¡¼­ player¹æÇâÀ¸·Î ÇÑ Ä­..
	int sx = pUserCreature->GetX() - x;
	int sy = pUserCreature->GetY() - y;

	if (sx>0) 
		sx=1; 
	else if (sx<0) 
		sx=-1; 
	else 
		sx=0;

	if (sy>0) 
		sy=1; 
	else if (sy<0) 
		sy=-1; 
	else 
		sy=0;

	//------------------------------------------------------
	// Fake Creature »ý¼º
	//------------------------------------------------------

	POINT Straight[4] = {
		{ -1, -1 },
		{ -1,  1 },
		{ 1,  -1 },
		{ 1,   1 },
	};

	POINT Diagonal[4] = {
		{ 0,  2 },
		{ 2,  0 },
		{ -2, 0 },
		{ 0, -2 },
	};

	POINT *Position;
	
	switch(shape) {
		case 0: // ÀÚµ¿
			Position = (pUserCreature->GetDirection() & 0x1) ? Diagonal : Straight;
			break;
		case 1: // ½ÊÀÚ¸ð¾ç(+)
			Position = Diagonal;
			break;
		case 2: // ¿¢½º¸ð¾ç(x)
			Position = Straight;
			break;
	}
	
	for (int i=0; i<4; i++)
	{	
	
		MFakeCreature* pFakeCreature = g_pZone->NewFakeCreature( pUserCreature, pUserCreature->GetX() , pUserCreature->GetY() );
		int dir ;
		if (pTargetCreature==NULL)
			dir =pFakeCreature->GetDirectionToPosition( targetX, targetY);
		else 
			dir = pFakeCreature->GetDirectionToPosition( pTargetCreature->GetX(), pTargetCreature->GetY());

		//pFakeCreature->SetDirection( 1 );
		//pFakeCreature->SetCurrentDirection( 1 );

		pFakeCreature->SetTraceX((unsigned short)targetX);
		pFakeCreature->SetTraceY((unsigned short)targetY);
		pFakeCreature->SetAction( ACTION_MAGIC );		// ±×³É.. - -;;

		//------------------------------------------------------
		// ÀÜ»ó ÇÑ¹ø º¸¿©ÁÖ°í »ç¶óÁö°Ô ¼³Á¤
		//------------------------------------------------------
							
		pFakeCreature->SetFakeCreatureType( MFakeCreature::FAKE_CREATURE_FAST_MOVE_ACTION );

		//------------------------------------------------------
		// Fake Creature¸¦ Zone¿¡ Ãß°¡
		//------------------------------------------------------
		if (!g_pZone->AddFakeCreature( pFakeCreature ))
		{
			delete pFakeCreature;
		}

		//------------------------------------------------------
		// ±â¼ú »ç¿ë
		//------------------------------------------------------
		if (skillID==SKILL_ATTACK_MELEE)
		{	
			skillID = pUserCreature->GetBasicActionInfo();
		}

		if (skillID >= g_pActionInfoTable->GetMinResultActionInfo())
		{
			DEBUG_ADD_FORMAT("[Error] SkillType Error = %d", skillID);
			return;
		}

		//MCreature* pTargetCreature = g_pZone->GetCreature( targetID );
		DWORD delayFrame = 0;
		
		pFakeCreature->SetFakeCreatureFastMoveAction(
			targetX + Position[i].x, targetY + Position[i].y,
			skillID, 
			pUserCreature->GetID() );
			
	}
}
void
SkillSPECTORINVERSE(MCreature* pUserCreature, MCreature* pTargetCreature, int skillID, int shape)
{
	//------------------------------------------------------------------
	// Ã¼Å© Ã¼Å©~
	//------------------------------------------------------------------
	if (pUserCreature==NULL || pTargetCreature==NULL)
	{
		DEBUG_ADD("[Error] ShadowDancing. Creature NULL or Not WearCreature");
		
		return;
	}

	// [ TEST CODE ]
	// ÁøÇàÁßÀÎ EffectÀÌ¸é Result·Î Ãß°¡ÇØ¾ß ÇÑ´Ù.
	// Result¸¦ »ý¼ºÇÏ°í..
	// pUserCreature->>AddActionResult( ... )
		
	//------------------------------------------------------
	// Fake CreatureÀÇ ÁÂÇ¥ °è»ê
	//------------------------------------------------------
	int x = pTargetCreature->GetX();
	int y = pTargetCreature->GetY();
	
	// ¸Â´Â ¾Ö¿¡¼­ player¹æÇâÀ¸·Î ÇÑ Ä­..
	int sx = pUserCreature->GetX() - x;
	int sy = pUserCreature->GetY() - y;

	if (sx>0) sx=1; else if (sx<0) sx=-1; else sx=0;
	if (sy>0) sy=1; else if (sy<0) sy=-1; else sy=0;

	//------------------------------------------------------
	// Fake Creature »ý¼º
	//------------------------------------------------------

	POINT Straight[6] = {
		{ -2, 2 },
		{ -2, 0 },
		{ -2, -2},
		{ 2,  2 },
		{ 2,  0 },
		{2, -2},
	};

	POINT Diagonal[6] = {
		{ -2, 2 },
		{ -2, 0 },
		{ -2, -2},
		{ 2,  2 },
		{ 2,  0 },
		{2, -2},
	};

	POINT *Position;
	
	switch(shape) {
		case 0: // ÀÚµ¿
			Position = (pUserCreature->GetDirection() & 0x1) ? Diagonal : Straight;
			break;
		case 1: // ½ÊÀÚ¸ð¾ç(+)
			Position = Diagonal;
			break;
		case 2: // ¿¢½º¸ð¾ç(x)
			Position = Straight;
			break;
	}
	
	for (int i=0; i<6; i++)
	{	
		//MFakeCreature* pFakeCreature = NewFakeCreature( pUserCreature, pTargetCreature->GetX() + Position[i].x, pTargetCreature->GetY() + Position[i].y);
		MFakeCreature* pFakeCreature = g_pZone->NewFakeCreature( pUserCreature, pUserCreature->GetX() , pUserCreature->GetY() );

		int dir = pFakeCreature->GetDirectionToPosition( pTargetCreature->GetX(), pTargetCreature->GetY() );
		pFakeCreature->SetDirection( dir );
		pFakeCreature->SetCurrentDirection( dir );

		pFakeCreature->SetAction( ACTION_MAGIC );		// ±×³É.. - -;;

		//------------------------------------------------------
		// ÀÜ»ó ÇÑ¹ø º¸¿©ÁÖ°í »ç¶óÁö°Ô ¼³Á¤
		//------------------------------------------------------
		//pFakeCreature->SetFakeCreatureType( MFakeCreature::FAKE_CREATURE_BRIGHTNESS );						
		pFakeCreature->SetFakeCreatureType( MFakeCreature::FAKE_CREATURE_FAST_MOVE_ACTION );

		//------------------------------------------------------
		// Fake Creature¸¦ Zone¿¡ Ãß°¡
		//------------------------------------------------------
		if (!g_pZone->AddFakeCreature( pFakeCreature ))
		{
			delete pFakeCreature;
		}

		//------------------------------------------------------
		// ±â¼ú »ç¿ë
		//------------------------------------------------------
		if (skillID==SKILL_ATTACK_MELEE)
		{	
			skillID = pUserCreature->GetBasicActionInfo();
		}

		if (skillID >= g_pActionInfoTable->GetMinResultActionInfo())
		{
			DEBUG_ADD_FORMAT("[Error] SkillType Error = %d", skillID);
			return;
		}

//		MActionResult* pResult = new MActionResult;
		
		DWORD delayFrame = 0;//ConvertDurationToFrame( pPacket->getDuration() );
		
		pFakeCreature->SetFakeCreatureFastMoveAction(
			pTargetCreature->GetX() + Position[i].x, pTargetCreature->GetY() + Position[i].y,
			skillID, 
			pTargetCreature->GetID() );
		
//		pResult->Add( new MActionResultNodeActionInfo( 
//			skillID, 
//			pUserCreature->GetID(),
//			pTargetCreature->GetID(),
//			x,
//			y,
//			delayFrame ) );
//		
//		pFakeCreature->PacketSpecialActionToOther(
//			skillID, 
//			pTargetCreature->GetID(),
//			pResult			// °á°ú
//			);			
	}
}
void		
SetAddonToOusters(MCreatureWear* pCreature, const PCOustersInfo2* pInfo)
{	
}

void		
SetAddonToOusters(MCreatureWear* pCreature, const PCOustersInfo3* pInfo)
{	
	MItem* pCoat		= g_pPacketItemOustersCoat[pInfo->getCoatType()];
	MItem* pArm			= g_pPacketItemOustersArm[pInfo->getArmType()];	
		
	pCreature->SetAddonItem( pCoat );
	pCreature->SetAddonItem( pArm );
	
	pCreature->SetAddonColorSet1( ADDON_COAT, pInfo->getHairColor() );
	pCreature->SetAddonColorSet2( ADDON_COAT, pInfo->getCoatColor() );
	pCreature->SetAddonColorSet1( ADDON_TROUSER, pInfo->getBootsColor() );
	pCreature->SetAddonColorSet2( ADDON_TROUSER, pInfo->getBootsColor() );
	pCreature->SetAddonColorSet1( ADDON_RIGHTHAND, pInfo->getArmColor() );
	pCreature->SetAddonColorSet2( ADDON_RIGHTHAND, pInfo->getArmColor() );
		
	pCreature->SetWeaponSpeed( pInfo->getAttackSpeed() );
}

void		
SetAddonToVampire(MCreatureWear* pCreature, const PCVampireInfo2* pInfo)
{
}

void		
SetAddonToVampire(MCreatureWear* pCreature, const PCVampireInfo3* pInfo)
{	
	MItem* pCoat		= g_pPacketItemVampireCoat[pInfo->getCoatType()];
	MItem* pArm			= g_pPacketItemVampireArm[pInfo->getArmType()];	
		
	pCreature->SetAddonItem( pCoat );
	pCreature->SetAddonItem( pArm );
	
	pCreature->SetBodyColor1(pInfo->getSkinColor());
	pCreature->SetBodyColor2(pInfo->getCoatColor());
	
	pCreature->SetAddonColorSet1( ADDON_COAT, pInfo->getSkinColor() );
	pCreature->SetAddonColorSet2( ADDON_COAT, pInfo->getCoatType() );

	pCreature->SetAddonColorSet1( ADDON_RIGHTHAND, pInfo->getArmColor() );
	pCreature->SetAddonColorSet2( ADDON_RIGHTHAND, pInfo->getArmColor() );
		
	pCreature->SetWeaponSpeed( pInfo->getAttackSpeed() );
}

void
SkillBlazeWalk(MCreature* pUserCreature, MCreature* pTargetCreature, int skillID, BYTE grade)
{
		//------------------------------------------------------------------
	// Ã¼Å© Ã¼Å©~
	//------------------------------------------------------------------
	if (pUserCreature==NULL || pTargetCreature==NULL)
	{
		DEBUG_ADD("[Error] ShadowDancing. Creature NULL or Not WearCreature");
		
		return;
	}

	// [ TEST CODE ]
	// ÁøÇàÁßÀÎ EffectÀÌ¸é Result·Î Ãß°¡ÇØ¾ß ÇÑ´Ù.
	// Result¸¦ »ý¼ºÇÏ°í..
	// pUserCreature->>AddActionResult( ... )
	
	POINT TargetList[3] = 
	{
		{ 1, 0 },
		{ -1, 0 },
		{ 0, 1 }
	};
		
	for (int i=0; i<=grade; i++)
	{			
		MFakeCreature* pFakeCreature = g_pZone->NewFakeCreature( pUserCreature, pUserCreature->GetX() , pUserCreature->GetY() );
		
//		int dir = pFakeCreature->GetDirectionToPosition( pTargetCreature->GetX(), pTargetCreature->GetY() );

		int dir;

		switch( i )
		{
		case 0 :
			dir = 0;
			break;
		case 1 :
			dir = 4;
			break;
		case 2 :
			dir = 6;
			break;
		}
		
		pFakeCreature->SetDirection( dir );
		pFakeCreature->SetCurrentDirection( dir );		
		pFakeCreature->SetAction( ACTION_STAND );
		
		pFakeCreature->SetFakeCreatureType( MFakeCreature::FAKE_CREATURE_FAST_MOVE_ACTION );
		
		//------------------------------------------------------
		// Fake Creature¸¦ Zone¿¡ Ãß°¡
		//------------------------------------------------------
		if (!g_pZone->AddFakeCreature( pFakeCreature ))
		{
			delete pFakeCreature;
		}
		
		//------------------------------------------------------
		// ±â¼ú »ç¿ë
		//------------------------------------------------------
		if (skillID==SKILL_ATTACK_MELEE)
		{	
			skillID = pUserCreature->GetBasicActionInfo();
		}
		
		if (skillID >= g_pActionInfoTable->GetMinResultActionInfo())
		{
			DEBUG_ADD_FORMAT("[Error] SkillType Error = %d", skillID);
			return;
		}
		
		pFakeCreature->SetFakeCreatureFastMoveAction(
			pTargetCreature->GetX()+TargetList[i].x, pTargetCreature->GetY() +TargetList[i].y,
			skillID, 
			pTargetCreature->GetID() );

		pFakeCreature->SetDelay( (i+1)*4 );
	}
}
void
SendBugReport(const char *bug, ...)
{	
	if( bug == NULL )
		return;

	
	va_list		vl;
	char Buffer[256];

	va_start(vl, bug);
	vsprintf(Buffer, bug, vl);    
    va_end(vl);
	

#ifdef __DEBUG_OUTPUT__
	DEBUG_ADD_FORMAT("[BUG_REPORT] %s",Buffer);
#endif
	
	int len = strlen(Buffer);

	if( len <= 1 )
		return;

	if( len >= 100 )
		Buffer[100] = '\0';

	std::string message;

	message = "*bug_report ";
	message += Buffer;

	CGSay _CGSay;

	_CGSay.setMessage( message );
	_CGSay.setColor( 0 );
	
	if( g_pSocket != NULL )
		g_pSocket->sendPacket( &_CGSay );
	
}

void
SetPetInfo(PetInfo* pPetInfo, TYPE_OBJECTID objectID)
{
	MCreature *pCreature = g_pZone->GetCreature(objectID);

	if(pCreature != NULL)
	{
		if(pPetInfo->getPetType() == PET_NONE)
		{
			if(pCreature->GetPetID() != OBJECTID_NULL)
			{
				MFakeCreature *pFakeCreature = (MFakeCreature *)g_pZone->GetFakeCreature(pCreature->GetPetID());

				if(pCreature != g_pPlayer)
				{
					if(gC_vs_ui.GetCurrentOtherInfoName() != NULL &&
						strcmp(pCreature->GetName(), gC_vs_ui.GetCurrentOtherInfoName()) == 0 )
					{
						gC_vs_ui.SetOtherPetInfo(NULL);
					}
				}

				if(pFakeCreature != NULL)
				{
					g_pZone->RemoveFakeCreature(pCreature->GetPetID());
					if(pCreature == g_pPlayer)	// ÀÚ±â ÆêÀÎ °æ¿ì
					{
						UI_RemoveEffectStatus(EFFECTSTATUS_CLIENT_MAGICAL_PET_CHANGER) ; 
#if __CONTENTS(__EXPERT_PET_CHANGER)
						UI_RemoveEffectStatus(EFFECTSTATUS_CLIENT_EXPERT_PET_CHANGER) ; 
#endif //__EXPERT_PET_CHANGER
					}
				}
				else
				{
					DEBUG_ADD("[GCPetInfoHandler] ÆêÀ» ¾ø¾Ù·Á°í º¸´Ï±î ÁÖÀÎ³ðÀº ÆêÀÌ ÀÖ´Âµ¥ ¸·»ó ÆêÀÌ ¾ø³× ±×·Á");
				}
			}
			else
			{
				DEBUG_ADD("[GCPetInfoHandler] ÆêÀ» ¾ø¾Ù·Á°í º¸´Ï±î ÁÖÀÎ³ðÀÌ ÆêÀÌ ¾ø³× ±×·Á");
			}
		}
		else
		{
			MPetItem *pItem = NULL;

			ObjectID_t itemID = pPetInfo->getPetItemObjectID();

			if(pCreature == g_pPlayer)		// ÀÚ±â ÆêÀÎ °æ¿ì
			{
				DWORD SubInvetoryID = g_pPlayer->GetItemIDCheckBufferSubInventory();
				if(SubInvetoryID != 0 && SubInvetoryID != OBJECTID_NULL)
				{
					MSubInventory* SubInventoryItem = (MSubInventory*)g_pInventory->GetItem(SubInvetoryID);
					if(NULL != SubInventoryItem)
					{
						pItem = dynamic_cast<MPetItem *>(SubInventoryItem->GetItemToModify(itemID));
					}
				}
				else
				{
					MItem* pSubInventory = NULL;
					pItem = dynamic_cast<MPetItem *>(g_pInventory->GetItemToModifyAll( itemID, pSubInventory ));

				//	pItem = dynamic_cast<MPetItem *>(g_pInventory->GetItemToModify(itemID));
				}
			}
			else
			{
				pItem = dynamic_cast<MPetItem *>(MItem::NewItem( ITEM_CLASS_PET_ITEM ));
				pItem->SetItemType( pPetInfo->getPetType() );
			}

			if(pItem != NULL)
			{
				MFakeCreature* pFakeCreature = NULL;

#if __CONTENTS(__PET_VISION_AMPLE)
				// isSummonInfo°¡ 1ÀÌ¸é ¼ÒÈ¯ÀÌÆåÆ® ¹× ¼ÒÈ¯ ¸Þ¼¼Áö »Ñ¸²
				// °í·Î isSummonInfo°¡ 2ÀÏ¶© Å©¸®ÃÄ´Â »ý¼ºµÇ°í, ¼ÒÈ¯¹× ¸Þ½ÃÁö°¡ ¾øÀ½
				bool bSummonEffect = pPetInfo->isSummonInfo()==1?true:false;
#endif //__PET_VISION_AMPLE

				bool bNewCreature = pPetInfo->isSummonInfo()>0?true:false;

				if(pCreature->GetPetID() != OBJECTID_NULL)
				{
					pFakeCreature = dynamic_cast<MFakeCreature *>(g_pZone->GetFakeCreature(pCreature->GetPetID()));
					
					if(pFakeCreature == NULL)
						return;

					if(pCreature == g_pPlayer)		// ÀÚ±â ÆêÀÎ °æ¿ì
					{
						MPetItem *pPetItem = pFakeCreature->GetPetItem();
						if(pPetItem != NULL)
						{
							if(pItem->GetID() == pFakeCreature->GetPetItem()->GetID())	// ¿ø·¡²² ¶Ç ³¯¶ó¿Â°æ¿ì
							{
								// »õ ÆêÀÌ ·¹º§ÀÌ 1³ôÀº°æ¿ì
								if(pPetInfo->getPetLevel() == pPetItem->GetNumber()+1)
								{
									int num1 = pPetInfo->getPetLevel() % 10;
									if (num1==2 || num1==4 || num1==5 || num1==9)
									{
										g_pGameMessage->AddFormat((*g_pGameStringTable)[STRING_MESSAGE_NEW_PET_LEVEL_1].GetString(), pPetItem->GetPetName().c_str(), pPetInfo->getPetLevel());
									}
									else
									{
										g_pGameMessage->AddFormat((*g_pGameStringTable)[STRING_MESSAGE_NEW_PET_LEVEL_2].GetString(), pPetItem->GetPetName().c_str(), pPetInfo->getPetLevel());
									}

									// ·¹º§ 10ÀÌ µÇ¼­ ¼Ó¼ºÀ» ºÎ¿©ÇÒ ¼ö ÀÖ´Ù
									if(pPetInfo->getPetLevel() == 10)
									{
										g_pGameMessage->Add((*g_pGameStringTable)[STRING_MESSAGE_PET_CAN_GET_ATTR].GetString());
									}
									else
									// ·¹º§ÀÌ 49°¡ µÇ¼­ ¿É¼ÇÀ» ºÙÀÏ ¼ö ÀÖ´Ù.
									if(pPetInfo->getPetLevel() == 49)
									{
										g_pGameMessage->AddFormat((*g_pGameStringTable)[STRING_MESSAGE_PET_CAN_GET_OPTION].GetString(), pPetItem->GetPetName().c_str());
									}

									// ¾ÆÁ÷ 2Â÷ ´É·ÂÀÌ ¾ø°í
									// °×ºí ÇÒ ¼ö ÀÖ´Â °æ¿ì
									if(!pPetInfo->canCutHead() && pPetInfo->canGamble())
									{
										g_pGameMessage->Add((*g_pGameStringTable)[UI_STRING_MESSAGE_CAN_ENCHANT_PET].GetString());
									}
								}
								// 2Â÷ °×ºí ¼º°ø
								if(pPetInfo->canCutHead() != false && pPetItem->IsCanCutHead() == false)
								{
									g_pGameMessage->AddFormat((*g_pGameStringTable)[STRING_MESSAGE_PET_GAMBLE_OK].GetString(), pPetItem->GetPetName().c_str());
									if(g_pUserOption->UseTeenVersion == TRUE)
									{
										g_pGameMessage->Add((*g_pGameStringTable)[STRING_MESSAGE_PET_GAMBLE_DESC_TEEN].GetString());
									}
									else
									{
										g_pGameMessage->Add((*g_pGameStringTable)[STRING_MESSAGE_PET_GAMBLE_DESC].GetString());
									}
									UI_UnlockItem();
									
								}
								// 3Â÷ °×ºí ¼º°ø
								else if(pPetInfo->canAttack() != false && pPetItem->IsCanAttack() == false)
								{
									g_pGameMessage->AddFormat((*g_pGameStringTable)[STRING_MESSAGE_PET_3RD_GAMBLE_OK].GetString(), pPetItem->GetPetName().c_str());
									UI_UnlockItem();
								}
								// °×ºí ½ÇÆÐ
								else if(pPetInfo->canGamble() == false && pPetItem->IsCanGamble() != false)
								{
									if(pPetInfo->canCutHead())
										g_pGameMessage->AddFormat((*g_pGameStringTable)[STRING_MESSAGE_PET_3RD_GAMBLE_FAIL].GetString(), pPetItem->GetPetName().c_str());
									else
										g_pGameMessage->AddFormat((*g_pGameStringTable)[STRING_MESSAGE_PET_GAMBLE_FAIL].GetString(), pPetItem->GetPetName().c_str());
									UI_UnlockItem();
								}
							}
						}

						pFakeCreature->SetCreatureType(pPetInfo->getPetCreatureType());
					}
				}
				else
#if __CONTENTS(__PET_VISION_AMPLE)
				if (bNewCreature)
#endif //__PET_VISION_AMPLE
				{
					POINT p = MFakeCreature::CaculatePetPosition(pCreature->GetX(), pCreature->GetY(), 2, 0, MCreature::CREATURE_FAKE_GROUND, pCreature->GetX(), pCreature->GetY());
					int dir = rand()%8;
					pFakeCreature = g_pZone->NewFakeCreature(pPetInfo->getPetCreatureType(), p.x, p.y, dir );


					//------------------------------------------------------
					// Fake Creature¸¦ Zone¿¡ Ãß°¡
					//------------------------------------------------------
					if (!g_pZone->AddFakeCreature( pFakeCreature ))
					{
						
						delete pFakeCreature;
						if(pCreature != g_pPlayer)		// ÀÚ±â ÆêÀÎ °æ¿ì
						{
							delete pItem;
						}
					}

					pFakeCreature->SetZone(g_pZone);
				}

#if __CONTENTS(__PET_VISION_AMPLE)
				if(pItem && !pFakeCreature)
				{
					if(pPetInfo->getPetAttrLevel() > 0)	// ¼Ó¼ºÀÌ ÀÖ´Â °æ¿ì´Â »ö Ç¥½Ã
					{
						//	2009.11.27 by neclipse
						//	ºí·çµå·Ó ¿§Áö¿Í »þÀÎÀÌ ³ª¿À¸é¼­ ÀÎÃ¾Æ® °¡´É ¹üÀ§°¡ º¯°æÀÌ µÇ¾ú´Ù.
						//	º¯°æÀÌ µÇ¸é¼­ ¹®Á¦Á¡Àº Æê ¾ÆÀÌÅÛÀÇ °æ¿ì ÀÎÃ¾Æ® °¡´É ¹üÀ§¿¡¼­ °¡Àå ¸¶Áö¸· ¿É¼ÇÀÇ »öÀ¸·Î º¸¿©ÁØ´Ù´Â °ÍÀÌ´Ù.
						//	ÇöÀç´Â ¹üÀ§°¡ º¯°æ µÇ¾úÀ¸¹Ç·Î »ö¸¶Àú º¯°æµÇ´Â »óÈ²..
						//	±âÁ¸°ú µ¿ÀÏÇÏ°Ô °¡±â À§ÇØ¼± ÀÌÀü¿¡ »ç¿ëÇß´ø »öÀ» »ç¿ëÇÏ´Â °ÍÀÌ´Ù.
						ITEMOPTION_TABLE::ITEMOPTION_PART optionPart = static_cast<ITEMOPTION_TABLE::ITEMOPTION_PART>(pPetInfo->getPetAttr());

						int size = g_pItemOptionTable->GetSize();

						for(int i = 1; i < size; i++)
						{
							ITEMOPTION_INFO &optionInfo = g_pItemOptionTable->Get(i);
							if(optionInfo.Part == optionPart && optionInfo.UpgradeOptionType == 0)
							{
								pItem->SetItemColorSet(optionInfo.ColorSet);
								break;
							}
						}
						//	by neclipse ´Ù¸¥ Á¶°ÇÀ¸·Î Àû¿ë
					}
					else
					{
						pItem->SetItemColorSet((*g_pItemOptionTable)[0].ColorSet);
					}
					pItem->SetCurrentDurability( pPetInfo->getPetHP() );
					pItem->SetEnchantLevel( pPetInfo->getPetAttr() );
					pItem->SetSilver( pPetInfo->getPetAttrLevel() );
					pItem->SetNumber( pPetInfo->getPetLevel() );
					pItem->SetPetFoodType( pPetInfo->getFoodType() );
#if __CONTENTS(__FUNCTION_PETFOOD)
					pItem->setFunctionPetfoodType(pPetInfo->getFunctionPetfoodType());
#endif //__FUNCTION_PETFOOD
					int accum = 0;
					accum = g_pExperienceTable->GetPetExp(pPetInfo->getPetLevel()).AccumExp;
					pItem->SetPetExpRemain(accum-pPetInfo->getPetExp());
//					pItem->SetPetExpRemain( pPetInfo->getPetExp() );
					pItem->SetPetCutHead( pPetInfo->canCutHead()?true:false );
					pItem->SetPetGamble( pPetInfo->canGamble()?true:false );
					pItem->SetPetAttack( pPetInfo->canAttack()?true:false );
					pItem->SetEnchantSkillType( pPetInfo->getEnchantSkillType() );
					
					pItem->ClearItemOption();
					if(pPetInfo->getPetOption() != NULL)
					{
						pItem->AddItemOption(pPetInfo->getPetOption());		// ·¹µå ¹öµå·Î ÀÎÃ¾Æ®ÇÑ ¿É¼Ç
#if __CONTENTS(__PET_VISION_AMPLE)
						pItem->SetPet_RedBirdOptionNum(pPetInfo->getPetOption());
#endif //__PET_VISION_AMPLE
					}

#if __CONTENTS(__PET_VISION_AMPLE)
					if(pPetInfo->getPetOption2() != NULL)
					{
						pItem->AddItemOption(pPetInfo->getPetOption2());	// ºñÁ¯¾ÚÇÃ·Î ÀÎÃ¾Æ®ÇÑ ¿É¼Ç
						pItem->SetPet_AmpulOptionNum(pPetInfo->getPetOption2());
					}
					if(pPetInfo->getPetOption3() != NULL)
					{
						pItem->AddItemOption(pPetInfo->getPetOption3());	// ºñÁ¯¾ÚÇÃ·Î ÀÎÃ¾Æ®ÇÑ ¿É¼Ç
						pItem->SetPet_op3(pPetInfo->getPetOption3());
					}
#endif //__PET_VISION_AMPLE
					
#if __CONTENTS(__NEW_PET_INCUBUS)
					// 081203 wlzzi - OptionTypeÃß°¡
					// 2008-12-09 - ij-ch
					// 12¿ù À¯·á¾ÆÀÌÅÛ(ÀÎÅ¥¹ö½º)ÀÌÈÄÀÇ ±âº»¿É¼ÇÀ¸·Î ºÙÀÏ ¿É¼Ç
					// Å¬¶óÀÌ¾ðÆ®ÀÇ UI»ó¿¡¼­´Â °°Àº list<TYPE_ITEM_OPTION>±¸Á¶¿¡ ¿É¼ÇÀ» ADD()½ÃÄÑÁÖÁö¸¸
					// ¼­¹ö»ó¿¡¼­´Â Æê ¿É¼Ç°ú ¾ÆÀÌÅÛ¿É¼ÇÀº ³ª´µ¾îÁ® ÀÖ´Ù.
					const std::list<TYPE_ITEM_OPTION> &optionList = pPetInfo->getOptionType();
					std::list<TYPE_ITEM_OPTION>::const_iterator itr= optionList.begin();
					
					for(; itr!=optionList.end() && *itr < g_pItemOptionTable->GetSize(); itr++)
					{
						pItem->AddItemOption(*itr);
					}
#endif //__NEW_PET_INCUBUS
#if __CONTENTS(__PET_MIXINGFORGE)
					pItem->SetPetMixingOptionList(pPetInfo->getMixOptionType());
#endif //__PET_MIXINGFORGE
				}
				else
#endif //__PET_VISION_AMPLE
				if(pFakeCreature)
				{
					pFakeCreature->SetCreatureType(pPetInfo->getPetCreatureType());

					if(pPetInfo->getPetAttrLevel() > 0)	// ¼Ó¼ºÀÌ ÀÖ´Â °æ¿ì´Â »ö Ç¥½Ã
					{
						//	2009.11.27 by neclipse
						//	ºí·çµå·Ó ¿§Áö¿Í »þÀÎÀÌ ³ª¿À¸é¼­ ÀÎÃ¾Æ® °¡´É ¹üÀ§°¡ º¯°æÀÌ µÇ¾ú´Ù.
						//	º¯°æÀÌ µÇ¸é¼­ ¹®Á¦Á¡Àº Æê ¾ÆÀÌÅÛÀÇ °æ¿ì ÀÎÃ¾Æ® °¡´É ¹üÀ§¿¡¼­ °¡Àå ¸¶Áö¸· ¿É¼ÇÀÇ »öÀ¸·Î º¸¿©ÁØ´Ù´Â °ÍÀÌ´Ù.
						//	ÇöÀç´Â ¹üÀ§°¡ º¯°æ µÇ¾úÀ¸¹Ç·Î »ö¸¶Àú º¯°æµÇ´Â »óÈ²..
						//	±âÁ¸°ú µ¿ÀÏÇÏ°Ô °¡±â À§ÇØ¼± ÀÌÀü¿¡ »ç¿ëÇß´ø »öÀ» »ç¿ëÇÏ´Â °ÍÀÌ´Ù.
						ITEMOPTION_TABLE::ITEMOPTION_PART optionPart = static_cast<ITEMOPTION_TABLE::ITEMOPTION_PART>(pPetInfo->getPetAttr());

						int size = g_pItemOptionTable->GetSize();

						for(int i = 1; i < size; i++)
						{
							ITEMOPTION_INFO &optionInfo = g_pItemOptionTable->Get(i);
							if(optionInfo.Part == optionPart && optionInfo.UpgradeOptionType == 0)
							{
								pFakeCreature->SetBodyColor1(optionInfo.ColorSet);
								pFakeCreature->SetBodyColor2(optionInfo.ColorSet);
								pItem->SetItemColorSet(optionInfo.ColorSet);
								
								break;
							}
						}
						//	by neclipse ´Ù¸¥ Á¶°ÇÀ¸·Î Àû¿ë
					}
					else
					{
						pFakeCreature->SetBodyColor1( 0) ; //(*g_pItemOptionTable)[0].ColorSet);
						pFakeCreature->SetBodyColor2( 0) ; //((*g_pItemOptionTable)[0].ColorSet);
						pItem->SetItemColorSet((*g_pItemOptionTable)[0].ColorSet);
					}

					pCreature->SetPetID( pFakeCreature->GetID() );

					pFakeCreature->SetOwnerID(pCreature->GetID());
					pFakeCreature->SetFakeCreatureType( MFakeCreature::FAKE_CREATURE_TRACE );

						if(pItem->GetItemType() >= 4)	// ÆêÀÌ ³¯¶ó ´Ù´Ò¶§ 4:¹ì2Â÷Æê, 5:¾Æ¿ì2Â÷Æê
						pFakeCreature->SetMoveType(MCreature::CREATURE_FAKE_FLYING);
					else
						pFakeCreature->SetMoveType(MCreature::CREATURE_FAKE_GROUND);

					// 2004, 6, 18 sobeit add start - add nick name
					pFakeCreature->SetNickName(NicknameInfo::NICK_CUSTOM , (char*)pPetInfo->getNickname().c_str());
					// 2004, 6, 18 sobeit add end - add nick name
					pFakeCreature->SetFakePosition( pCreature->GetX(), pCreature->GetY() );
					pFakeCreature->SetTraceID( objectID ); 
					pFakeCreature->SyncTurretDirection();
					
					// FakeCreature°¡ Á¤»óÀûÀ¸·Î Ãß°¡ µÇ¾ú´Ù
					pFakeCreature->SetPetItem(pItem);

					pItem->SetCurrentDurability( pPetInfo->getPetHP() );
					pItem->SetEnchantLevel( pPetInfo->getPetAttr() );
					pItem->SetSilver( pPetInfo->getPetAttrLevel() );
					pItem->SetNumber( pPetInfo->getPetLevel() );
					pItem->SetPetFoodType( pPetInfo->getFoodType() );
#if __CONTENTS(__FUNCTION_PETFOOD)
					pItem->setFunctionPetfoodType(pPetInfo->getFunctionPetfoodType());
#endif //__FUNCTION_PETFOOD
					int accum = 0;
					accum = g_pExperienceTable->GetPetExp(pPetInfo->getPetLevel()).AccumExp;
					pItem->SetPetExpRemain(accum-pPetInfo->getPetExp());
//					pItem->SetPetExpRemain( pPetInfo->getPetExp() );
					pItem->SetPetCutHead( pPetInfo->canCutHead()?true:false );
					pItem->SetPetGamble( pPetInfo->canGamble()?true:false );
					pItem->SetPetAttack( pPetInfo->canAttack()?true:false );
					pItem->SetEnchantSkillType( pPetInfo->getEnchantSkillType() );
					
					pItem->ClearItemOption();
					if(pPetInfo->getPetOption() != NULL)
					{
						pItem->AddItemOption(pPetInfo->getPetOption());		// ·¹µå ¹öµå·Î ÀÎÃ¾Æ®ÇÑ ¿É¼Ç
#if __CONTENTS(__PET_VISION_AMPLE)
						pItem->SetPet_RedBirdOptionNum(pPetInfo->getPetOption());
#endif //__PET_VISION_AMPLE
					}

#if __CONTENTS(__PET_VISION_AMPLE)
					if(pPetInfo->getPetOption2() != NULL)
					{
						pItem->AddItemOption(pPetInfo->getPetOption2());	// ºñÁ¯¾ÚÇÃ·Î ÀÎÃ¾Æ®ÇÑ ¿É¼Ç
						pItem->SetPet_AmpulOptionNum(pPetInfo->getPetOption2());
					}
					if(pPetInfo->getPetOption3() != NULL)
					{
						pItem->AddItemOption(pPetInfo->getPetOption3());	// ºñÁ¯¾ÚÇÃ·Î ÀÎÃ¾Æ®ÇÑ ¿É¼Ç
						pItem->SetPet_op3(pPetInfo->getPetOption3());
					}
#endif //__PET_VISION_AMPLE
					
#if __CONTENTS(__NEW_PET_INCUBUS)
					// 081203 wlzzi - OptionTypeÃß°¡
					// 2008-12-09 - ij-ch
					// 12¿ù À¯·á¾ÆÀÌÅÛ(ÀÎÅ¥¹ö½º)ÀÌÈÄÀÇ ±âº»¿É¼ÇÀ¸·Î ºÙÀÏ ¿É¼Ç
					// Å¬¶óÀÌ¾ðÆ®ÀÇ UI»ó¿¡¼­´Â °°Àº list<TYPE_ITEM_OPTION>±¸Á¶¿¡ ¿É¼ÇÀ» ADD()½ÃÄÑÁÖÁö¸¸
					// ¼­¹ö»ó¿¡¼­´Â Æê ¿É¼Ç°ú ¾ÆÀÌÅÛ¿É¼ÇÀº ³ª´µ¾îÁ® ÀÖ´Ù.
					const std::list<TYPE_ITEM_OPTION> &optionList = pPetInfo->getOptionType();
					std::list<TYPE_ITEM_OPTION>::const_iterator itr= optionList.begin();
					
					for(; itr!=optionList.end() && *itr < g_pItemOptionTable->GetSize(); itr++)
					{
						pItem->AddItemOption(*itr);
					}
#endif //__NEW_PET_INCUBUS
#if __CONTENTS(__PET_MIXINGFORGE)
					pItem->SetPetMixingOptionList(pPetInfo->getMixOptionType());
#endif //__PET_MIXINGFORGE

					pFakeCreature->SetName(pItem->GetPetName().c_str());
//20081007 petTypeº¯¼ö ¾Æ·¡ÂÊ¿¡ ÀÖ´ø°É À§¾Ö¼­µµ ¾²±â À§ÇØ¼­ ²ø¾î ¿Ã¸²
					PetType_t petType = pPetInfo->getPetType();
					
#if __CONTENTS(__PET_VISION_AMPLE)
					if(bSummonEffect)
#else
					if(bNewCreature)
#endif //__PET_VISION_AMPLE
					{
#if __CONTENTS(__2008_OCTOBER_MAKETITEM || __NEW_PET_INCUBUS)
						if (petType != 8 && petType >= 6 && petType <= 10
#if __CONTENTS(__NEW_PET_INCUBUS)
							|| petType == 11
#endif //__NEW_PET_INCUBUS
							|| petType == 12 || petType ==13 || petType ==14 || petType == 15 || petType == 16 || petType == 17 || petType == 18 || petType == 19 || petType == 20 || petType == 21 || petType == 22 || petType == 23 || petType == 24  || petType == 25 || petType == 26 //by rallser
							)
						g_pTopView->VampireComeFromPortalNonTurn( pFakeCreature );
						else
#endif //__2008_OCTOBER_MAKETITEM || __NEW_PET_INCUBUS
						g_pTopView->VampireComeFromPortal( pFakeCreature );

						if(pCreature == g_pPlayer)	// ÀÚ±â ÆêÀÎ °æ¿ì
						{
							g_pSystemMessage->AddFormat((*g_pGameStringTable)[STRING_MESSAGE_PET_SUMMON].GetString(), pItem->GetPetName().c_str());
							//if(pPetInfo->getMagicRemainSec() > 0 )
							//{ 
							//	UI_AddEffectStatus(EFFECTSTATUS_CLIENT_MAGICAL_PET_CHANGER , pPetInfo->getMagicRemainSec() << 4) ;   
							//}
						}
					}
					if( pCreature == g_pPlayer )
					{
						if( pPetInfo->getMagicRemainSec() > 0 )
						{ 
							UI_AddEffectStatus(EFFECTSTATUS_CLIENT_MAGICAL_PET_CHANGER , pPetInfo->getMagicRemainSec() << 4) ;   
						}
#if __CONTENTS(__EXPERT_PET_CHANGER)
						//2006.02.08 chyaya
						if( pPetInfo->getExpertPetChangerRemainSec() > 0 )
						{ 
							UI_AddEffectStatus(EFFECTSTATUS_CLIENT_EXPERT_PET_CHANGER , pPetInfo->getExpertPetChangerRemainSec() << 4) ;   
						}
#endif //__EXPERT_PET_CHANGER

					}


					//////////////////////////////////////////////////////////////////////////
					// Idle Action Ãß°¡
					if(petType == 6 || petType == 7 || petType == 8
#if __CONTENTS(__NEW_PET_FIRE_ELEMENTAL)
					|| petType == 9
#endif //__NEW_PET_FIRE_ELEMENTAL
#if __CONTENTS(__2008_OCTOBER_MAKETITEM)
					|| petType == 10
#endif //__2008_OCTOBER_MAKETITEM
#if __CONTENTS(__NEW_PET_INCUBUS)
					|| petType == 11
#endif //__NEW_PET_INCUBUS
#if __CONTENTS(__PET_MASHIMARO)
					|| petType == 12
#endif //__PET_MASHIMARO
#if __CONTENTS(__PET_CATS)
					|| petType == 13
					|| petType == 14
					|| petType == 15
					|| petType == 16
					|| petType == 17
					|| petType == 18
					|| petType == 19
					|| petType == 20
					|| petType == 21
					|| petType == 22
					|| petType == 23
					|| petType == 24
				    || petType == 25
					|| petType == 26
#endif //__PET_CATS


						)	// ·çÆë
					{
						pFakeCreature->AddIdleAction(ACTION_ATTACK);
						pFakeCreature->AddIdleAction(ACTION_DAMAGED);
					}

					//////////////////////////////////////////////////////////////////////////
					// Pet Effect Ãß°¡

					// ÀÏ´Ü ´Ù Áö¿î´Ù.
					pFakeCreature->ClearEffectStatus();

					int enchantSkillType = pPetInfo->getEnchantSkillType() - 1;

					if(enchantSkillType >= 0)
					{
						int petEffectOffset = EFFECTSTATUS_CLIENT_PET_EFFECT_WOLF_SHOCK_CAPSULE;

						switch(petType)
						{
						case 1: case 2: case 6: case 9: // ¿ïÇÁµ¶, ¿ï¹ö¸°, ·çÆë, ÆÄÀÌ¾î¿¤¸®¸àÅ»
							petEffectOffset = EFFECTSTATUS_CLIENT_PET_EFFECT_WOLF_SHOCK_CAPSULE; break;
						case 3: // ¼¾Å¸¿ì·Î(ÅÊÅ©)
							petEffectOffset = EFFECTSTATUS_CLIENT_PET_EFFECT_CENTAURO_SHOCK_CAPSULE; break;
						case 4: // ½ºÆ¼Áö(¹ÚÁã)
							petEffectOffset = EFFECTSTATUS_CLIENT_PET_EFFECT_STIRGE_SHOCK_CAPSULE; break;
						case 5: // ÇÈ½Ã
							petEffectOffset = EFFECTSTATUS_CLIENT_PET_EFFECT_PIXIE_SHOCK_CAPSULE; break;
					//	case 19:
                      //      petEffectOffset = EFFECTSTATUS_unknow759; break;
						}

						EFFECTSTATUS petEffect = static_cast<EFFECTSTATUS>( petEffectOffset + enchantSkillType );

						pFakeCreature->AddEffectStatus(petEffect, 0xFFFF);
					}
//20081002 ¶ÇÇÏ³ªÀÇ ÇÏµåÄÚµù? ¿©Æ° Æê¿¡ Å¬¶óÀÌ¾ðÆ® Àü¿ë EFFECTSTATUS¸¦ ºÙ¿©¼­ Æê¿¡ Áö¼ÓÇü ÀÌÆåÆ®¸¦ ºÙ¿©¼­ º¸¿©ÁØ´Ù.
//Å¸ÀÎµµ º¸¿©ÁÖ±â À§ÇØ¼­ ¿©±â¼­ ºÙ¿©Áà¾ß ÇÑ´Ù.
//ÀÌ·± Áö¼ÓÇü ÀÌÆåÆ® ºÙ´Â Ä³ÀÌ½º°¡ ´Ã¾î³ª¸é case¹®À¸·Î º¯°æ ÇØµµ ÁÁÀ»µí
#if __CONTENTS(__2008_OCTOBER_MAKETITEM)
					if(petType == 10)
					{
						pFakeCreature->AddEffectStatus(EFFECTSTATUS_CLIENT_SUCCUBUS_MAINTENANCE, 0xFFFF);
					}
					if(petType ==16 || petType ==17 || petType ==19 || petType ==20 || petType ==21 || petType ==22 || petType ==23) //³èÎï¹â»·
					{
                        MAttachEffect* pEffect = NULL;
					    pEffect = pFakeCreature->CreateAttachEffect( EFFECTSPRITETYPE_UPGRADED_DELLA_CATS_EFFECT_FRONT, 0xffff,0);//rallser22
					}
					if(petType == 18) //³èÎï¹â»·
					{
                        MAttachEffect* pEffect = NULL;
					    pEffect = pFakeCreature->CreateAttachEffect( EFFECTSPRITETYPE_unknow_2013, 0xffff,0);//rallser22
					}
				   if(petType == 25) //³èÎï¹â»·
					{
                        MAttachEffect* pEffect = NULL;
					    pEffect = pFakeCreature->CreateAttachEffect( EFFECTSPRITETYPE_unknow_2273, 0xffff,0);//2273rallser22   750ÂÌ¶Ü×ª 751À¶¶Ü×ª 752×Ï¶Ü×ª 753»ð·ï»Ë¶Ü×ª 754ÂÌÉ«¸«Í·¶Ü×ª-757 758-761ÄÑ¿´ 762ÂÌÉ«ÕÖ×Ó763À¶É«764×ÏÉ«765»ðºì
						//pFakeCreature->AddEffectStatus(EFFECTSTATUS_CLIENT_EXPERT_PET_CHANGER, 0xFFFF);
					}
					if(petType == 24) //³èÎï¹â»·
					{
						MAttachEffect* pEffect = NULL;
						pEffect = pFakeCreature->CreateAttachEffect( EFFECTSPRITETYPE_unknow_2174, 0xffff,0);//2273rallser22   750ÂÌ¶Ü×ª 751À¶¶Ü×ª 752×Ï¶Ü×ª 753»ð·ï»Ë¶Ü×ª 754ÂÌÉ«¸«Í·¶Ü×ª-757 758-761ÄÑ¿´ 762ÂÌÉ«ÕÖ×Ó763À¶É«764×ÏÉ«765»ðºì
						//pFakeCreature->AddEffectStatus(EFFECTSTATUS_CLIENT_EXPERT_PET_CHANGER, 0xFFFF);
					}
				 //		if(petType == 26) //³èÎï¹â»·
					//{
					//	int action = pFakeCreature->GetNextAction();
					//	
					//	char szBuf[128];
					//	if(action == 0)
					//	{
			  //          sprintf(szBuf, "%d",action);
			  //           g_pSystemMessage->Add( szBuf );
     //                   pFakeCreature->AddEffectStatus(EFFECTSTATUS_unknow766, 0xFFFF);
					//	}
					//	else if(action == 1)
					//	{
					//	  pFakeCreature->RemoveEffectStatus(EFFECTSTATUS_unknow766)	  ;
					//	   pFakeCreature->AddEffectStatus(EFFECTSTATUS_unknow767, 0xFFFF);
					//	}
					//}
#endif //__2008_OCTOBER_MAKETITEM
				}
			}
			else
			{
				DEBUG_ADD_FORMAT("Æê ºÙÀÏ·Á°í ¾ÆÀÌÅÛ Ã£¾Æº¸´Ï ¾ÆÀÌÅÛ(%d) ¾øÀ½", itemID);
			}
		}
	}
	else
	{
		DEBUG_ADD("[GCPetInfoHandler] ÆêÀ¸·Î ¸Õ°¡ ÇØº¼¶ó´Ï±î ÁÖÀÎ³ðÀÌ ¾ø³× ±×·Á");
		return;
	}

	MPetItem *pPetItem = NULL;
	PETINFO petInfo;
	if(pCreature != NULL && pCreature->GetPetID() != OBJECTID_NULL)
	{
		MFakeCreature *pFakeCreature = (MFakeCreature *)g_pZone->GetFakeCreature(pCreature->GetPetID());
		if(pFakeCreature != NULL)
		{
			pPetItem = pFakeCreature->GetPetItem();
			if(pPetItem != NULL)
			{
				petInfo.HP = pPetItem->GetCurrentDurability();
				petInfo.ATTR = pPetItem->GetEnchantLevel();
				petInfo.ATTR_VALUE = pPetItem->GetSilver();
				petInfo.LEVEL = pPetItem->GetNumber();
				petInfo.FOODTYPE = pPetItem->GetPetFoodType();
				petInfo.EXP_REMAIN = pPetItem->GetPetExpRemain();
				petInfo.CUT_HEAD = pPetItem->IsCanCutHead();
				petInfo.GAMBLE = pPetItem->IsCanGamble();

				if(pPetItem->GetItemOptionListCount() == 0)
#if __CONTENTS(!__NEW_PET_INCUBUS)
					petInfo.OPTION = -1;
				else
					petInfo.OPTION = pPetItem->GetItemOptionList().front();
#else
				{
					petInfo.OPTION_LIST.clear();
				}
				else
				{		
					const std::list<TYPE_ITEM_OPTION> &optionList = pPetItem->GetItemOptionList();
					std::list<TYPE_ITEM_OPTION>::const_iterator itr= optionList.begin();
					
					for(; itr!=optionList.end() && *itr < g_pItemOptionTable->GetSize(); itr++)
					{
						petInfo.OPTION_LIST.push_back( *itr );
					}
				}
#endif //__NEW_PET_INCUBUS
#if __CONTENTS(__PET_MIXINGFORGE)
				const std::list<TYPE_ITEM_OPTION> &petMixingOption = pPetItem->GetPetMixingOptionList();
				std::list<TYPE_ITEM_OPTION>::const_iterator itr = petMixingOption.begin();
				
				for(;itr != petMixingOption.end(); ++itr)
				{
					petInfo.MIXINGOPTION.push_back( *itr );
				}
#endif //__PET_MIXINGFORGE
				
				petInfo.ITEM_TYPE = pPetItem->GetItemType();
				petInfo.ITEM_ID = pPetItem->GetID();
				petInfo.NAME = pPetItem->GetPetName();
				petInfo.ATTACK = pPetItem->IsCanAttack();
				petInfo.ChangeAbleNickName = pFakeCreature->GetOwnerID() == g_pPlayer->GetID();
				petInfo.ENCHANTSKILLTYPE = pPetItem->GetEnchantSkillType();
				petInfo.NICK_NAME = pFakeCreature->GetNickName();
#if __CONTENTS(__FUNCTION_PETFOOD)
				petInfo.FUNCTION_PETFOODTYPE = pPetItem->getFunctionPetfoodType();
#endif //__FUNCTION_PETFOOD
			}
			
			//pFakeCreature->AddEffectStatus(EFFECTSTATUS_GRAND_MASTER_SLAYER_130, 0xFFFFFFFF);
		}
	}

	// ÀÚ±â ÆêÀÎ °æ¿ì
	if(pCreature == g_pPlayer)
	{
		if(pPetItem == NULL)
			gC_vs_ui.SetPetInfo(NULL);
		else
			gC_vs_ui.SetPetInfo(&petInfo);
		g_pPlayer->CalculateLightSight();
		g_pPlayer->CalculateStatus();
		
		g_pPlayer->SetPetDelay(GetTickCount());
	}
	else if(pCreature != NULL)
	{
		MFakeCreature *pFakeCreature = (MFakeCreature *)g_pZone->GetFakeCreature(pCreature->GetPetID());

		if(pFakeCreature != NULL)
		{
			if(gC_vs_ui.GetCurrentOtherInfoName() != NULL &&
				strcmp(pCreature->GetName(), gC_vs_ui.GetCurrentOtherInfoName()) == 0 )
			{
				if(pPetItem == NULL)
					gC_vs_ui.SetOtherPetInfo(NULL);
				else
					gC_vs_ui.SetOtherPetInfo(&petInfo);
			}
		}
	}

}

void	AddOustersElemental( MCreature *pOwnerCreature, int creatureType, int status )
{
	if(pOwnerCreature == NULL)
		return;
	
	if(pOwnerCreature->GetElementalID() != OBJECTID_NULL)
		return;

	POINT p = MFakeCreature::CaculatePetPosition(pOwnerCreature->GetX(), pOwnerCreature->GetY(), 2, 0, MCreature::CREATURE_FAKE_FLYING, pOwnerCreature->GetX(), pOwnerCreature->GetY());
	int dir = rand()%8;
	MFakeCreature *pFakeCreature = g_pZone->NewFakeCreature(creatureType, p.x, p.y, dir );

	//------------------------------------------------------
	// Fake Creature¸¦ Zone¿¡ Ãß°¡
	//------------------------------------------------------
	if (!g_pZone->AddFakeCreature( pFakeCreature ))
	{
		delete pFakeCreature;
	}

	pFakeCreature->SetZone(g_pZone);
	pOwnerCreature->SetElementalID( pFakeCreature->GetID() );
	pFakeCreature->SetOwnerID(pOwnerCreature->GetID());
	pFakeCreature->SetFakeCreatureType( MFakeCreature::FAKE_CREATURE_TRACE );
	pFakeCreature->SetMoveType(MCreature::CREATURE_FAKE_FLYING);
	pFakeCreature->SetFakePosition( pOwnerCreature->GetX(), pOwnerCreature->GetY() );
	pFakeCreature->SetTraceID( pOwnerCreature->GetID() ); 
	pFakeCreature->AddEffectStatus( (EFFECTSTATUS)status, 0xFFFF );
}

void	SendCrashReport()
{
// 	if( gC_ci->IsKorean() == true )
// 	{
// 		std::ifstream file(CRASH_LOG_FILENAME);
// 		file.seekg(0, std::ios::end);
// 		int nFileSize = file.tellg();
// 
// 		if(nFileSize > 4)
// 		{
// 			MCrashReportManager crm;
// 			crm.LoadFromFile(CRASH_LOG_FILENAME);
// 			int sizeCrashReport = crm.GetSize();
// 			for(int i = 0; i < sizeCrashReport; i++)
// 			{
// 				MCrashReport &cr = crm[i];
// 
// 				CGCrashReport _CGCrashReport;
// 				if(NULL != cr.GetAddress())			_CGCrashReport.setAddress(cr.GetAddress());
// 				if(NULL != cr.GetCallStack())		_CGCrashReport.setCallStack(cr.GetCallStack());
// 				if(NULL != cr.GetExecutableTime())	_CGCrashReport.setExecutableTime(cr.GetExecutableTime());
// 				if(NULL != cr.GetMessage())			_CGCrashReport.setMessage(cr.GetMessage());
// 				if(NULL != cr.GetOS())				_CGCrashReport.setOS(cr.GetOS());
// 				_CGCrashReport.setVersion(cr.GetVersion());
// 
// 				if( g_pSocket != NULL )
// 					g_pSocket->sendPacket( &_CGCrashReport );
// 			}
// 		}
// 		
// 		DeleteFile(OLD_CRASH_LOG_FILENAME);
// 		DeleteFile(CRASH_LOG_FILENAME);
// 	}
}

void	SetFlagTo( bool bTae )
{
	if( g_pTopView == NULL )
		return;

	if( bTae == true )
	{
		(*g_pItemTable)[ITEM_CLASS_EVENT_ITEM][27].SetFrameID( 856, 879,0 );
		(*g_pItemTable)[ITEM_CLASS_EVENT_ITEM][27].SetDropFrameID( 856 );
		
		(g_pTopView->m_EffectAlphaFPK)[EFFECTSPRITETYPE_FLAG_HEAD] = (g_pTopView->m_EffectAlphaFPK)[EFFECTSPRITETYPE_FLAG_HEAD_TAE];
		(g_pTopView->m_EffectAlphaFPK)[EFFECTSPRITETYPE_FLAG_GROUND] = (g_pTopView->m_EffectAlphaFPK)[EFFECTSPRITETYPE_FLAG_GROUND_TAE];

		(g_pTopView->m_EffectAlphaPPK)[EFFECTSPRITETYPE_FLAG_HEAD] = (g_pTopView->m_EffectAlphaPPK)[EFFECTSPRITETYPE_FLAG_HEAD_TAE];
		(g_pTopView->m_EffectAlphaPPK)[EFFECTSPRITETYPE_FLAG_GROUND] = (g_pTopView->m_EffectAlphaPPK)[EFFECTSPRITETYPE_FLAG_GROUND_TAE];
	}
	else
	{
		(*g_pItemTable)[ITEM_CLASS_EVENT_ITEM][27].SetFrameID( 750,764,0 );
		(*g_pItemTable)[ITEM_CLASS_EVENT_ITEM][27].SetDropFrameID( 750 );

		(g_pTopView->m_EffectAlphaFPK)[EFFECTSPRITETYPE_FLAG_HEAD] = (g_pTopView->m_EffectAlphaFPK)[EFFECTSPRITETYPE_FLAG_HEAD_ORIGINAL];
		(g_pTopView->m_EffectAlphaFPK)[EFFECTSPRITETYPE_FLAG_GROUND] = (g_pTopView->m_EffectAlphaFPK)[EFFECTSPRITETYPE_FLAG_GROUND_ORIGINAL];
		
		(g_pTopView->m_EffectAlphaPPK)[EFFECTSPRITETYPE_FLAG_HEAD] = (g_pTopView->m_EffectAlphaPPK)[EFFECTSPRITETYPE_FLAG_HEAD_ORIGINAL];
		(g_pTopView->m_EffectAlphaPPK)[EFFECTSPRITETYPE_FLAG_GROUND] = (g_pTopView->m_EffectAlphaPPK)[EFFECTSPRITETYPE_FLAG_GROUND_ORIGINAL];
	}
}

BOOL GetMacAddressFromNetBIOS(LPBYTE lpMacAddress)
{
    NCB ncb ;
    LANA_ENUM le ;
    
	int MacAddressSize = 6; // 6byte
	
    struct tagADAPTER
    {
        ADAPTER_STATUS adapt ;
        NAME_BUFFER    NameBuff[256] ;
    } adapter ;

	if(NULL == lpMacAddress)
		return FALSE;
//    ASSERT(lpMacAddress!=(LPBYTE)NULL) ;

    memset(&ncb,0x00,sizeof(NCB)) ;                  
    memset(&le,0x00,sizeof(LANA_ENUM)) ;             
    ncb.ncb_command = NCBENUM ;
    ncb.ncb_buffer = (UCHAR*)&le ;
    ncb.ncb_length = sizeof(LANA_ENUM) ;

    if(Netbios(&ncb)==NRC_GOODRET)
    {
        memset(&ncb,0x00,sizeof(NCB)) ;
        ncb.ncb_command = NCBRESET ;
//          ncb.ncb_callname[0] = 20 ;                   
        ncb.ncb_lana_num = le.lana[0] ;              

        if(Netbios(&ncb)==NRC_GOODRET)
        {
            memset(&ncb,0x00,sizeof(NCB)) ;
            memset(&ncb.ncb_callname,' ',NCBNAMSZ) ;
            ncb.ncb_callname[0] = '*' ;
//              ncb.ncb_callname[NCBNAMSZ-1] = NULL ;    
            ncb.ncb_command = NCBASTAT ;
            ncb.ncb_lana_num = le.lana[0] ;          
            ncb.ncb_buffer = (UCHAR*)&adapter ;
            ncb.ncb_length = sizeof(tagADAPTER) ;

            if(Netbios(&ncb)==NRC_GOODRET)
            {
                memcpy(lpMacAddress,&adapter.adapt.adapter_address,
                    MacAddressSize) ;
                return(TRUE) ;
            }
        }
    }
    return(FALSE) ;
}

BOOL GetMacAddressFromSock()
{
    int          iAdapters ;
    int          iOpt  = sizeof(iAdapters) ;
    int          iSize = sizeof(SOCKADDR_IPX) ;
    BOOL         bRet  = FALSE ;
    SOCKET       sock ;
    SOCKADDR_IPX adrIPX ;
    WSADATA      wsaData ;

	WORD wVersionRequested;
  
	wVersionRequested = MAKEWORD( 2, 0 );
//    #define WINSOCK_11 0x0101
//	char name[255];
//	PHOSTENT hostinfo;


    if(WSAStartup(wVersionRequested,&wsaData)==0)
    {
//		if( gethostname ( name, sizeof(name)) == 0)
//        {
//           if((hostinfo = gethostbyname(name)) != NULL)
//           {
//              g_IPAddress = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
//           }
//        }      
		sock=socket(AF_IPX,SOCK_DGRAM,NSPROTO_IPX);
        if(sock !=INVALID_SOCKET)
        {
			
            memset(&adrIPX,0x00,sizeof(SOCKADDR_IPX)) ;
            adrIPX.sa_family = AF_IPX ;

            if(bind(sock,(SOCKADDR*)&adrIPX,iSize)!=SOCKET_ERROR)
            {
                if(getsockopt(sock,NSPROTO_IPX,IPX_MAX_ADAPTER_NUM,
                    (char*)&iAdapters,&iOpt)!=SOCKET_ERROR)
                {
                    while(iAdapters)
                    {
                        IPX_ADDRESS_DATA ipxAdrData ;
                        memset( &ipxAdrData,0x00,
                            sizeof(IPX_ADDRESS_DATA)) ;
                        ipxAdrData.adapternum = --iAdapters ;
                        iOpt = sizeof(IPX_ADDRESS_DATA) ;
                        if(getsockopt(sock,NSPROTO_IPX,IPX_ADDRESS,
                            (char*)&ipxAdrData,&iOpt)!=SOCKET_ERROR)
                        {
                            if(ipxAdrData.status==TRUE && 
                                ipxAdrData.wan==FALSE)
                            {
                                memcpy(g_macAddress,
                                    &ipxAdrData.nodenum,
                                    6) ;
                                bRet = TRUE ;
                                break ;
                            }
                        }
                    }
                }
            }
            closesocket(sock) ;
        }

        WSACleanup() ;
    }
    return(bRet) ;
}

// 2004, 8, 26, sobeit add start - mac address Ã¼Å©ÇØ¼­ À©µµ ¸ðµå º¯°æ
std::string GetLocalIP()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	char name[255];
	PHOSTENT hostinfo;
	wVersionRequested = MAKEWORD( 2, 0 );
	std::string ip;	
	if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
	{
		if( gethostname ( name, sizeof(name)) == 0)
		{
			if((hostinfo = gethostbyname(name)) != NULL)
			{
				ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
			}
        }      
        WSACleanup( );
	} 
	return ip;
}

bool
CheckMacScreenMode()
{
	typedef std::map<std::string,std::string>			MACINFO_MAP;
	MACINFO_MAP MacInfo_Map;

	// ¹ÚÂùÈ£

	//////////////////////////////////////////////////////////////////////////////////////////
 	// ÇÁ·Î±×·¥ÆÀ
	
	// ¹ÚÁØ¿ë
	MacInfo_Map.insert(MACINFO_MAP::value_type("00-19-D1-63-7A-1C", "123.215.22.201"));
	// Áø±â¿µ
	MacInfo_Map.insert(MACINFO_MAP::value_type("00-1B-FC-E3-BC-7D", "123.215.22.241"));
	// ±è¼º¿ë
	MacInfo_Map.insert(MACINFO_MAP::value_type("00-1E-8C-BE-11-81", "123.215.22.202"));
	// ¹Úµ¿Áø
	MacInfo_Map.insert(MACINFO_MAP::value_type("00-E0-4C-77-19-E0", "123.215.22.204"));
	// ±è¿µÃ¤
	MacInfo_Map.insert(MACINFO_MAP::value_type("00-19-D1-59-9E-1C", "123.215.22.203"));
	// ¹ÚÂù¿ë
	MacInfo_Map.insert(MACINFO_MAP::value_type("02-FF-3F-C2-12-46", "123.215.22.148"));
	// ÀÌ±ÇÈ®
	MacInfo_Map.insert(MACINFO_MAP::value_type("00-1D-60-35-5E-4E", "123.215.22.200"));
	// ÃµÀÏÀç
	MacInfo_Map.insert(MACINFO_MAP::value_type("00-1E-8C-BE-14-E6", "123.215.22.186"));

	// ±èÁÖ¿¬
	
// 	//////////////////////////////////////////////////////////////////////////////////////////
// 	// ±âÈ¹ÆÀ
// 
// 	// ÃÖÀ±¼®
 	MacInfo_Map.insert(MACINFO_MAP::value_type("00-1B-FC-E3-BC-7F", "123.215.22.167"));
	// °­Á¾ÈÆ

// 
// 
// 	//////////////////////////////////////////////////////////////////////////////////////////
// 	// DB ÆÀ
// 	
// 	// ¹Ú¼º¿ø
 	MacInfo_Map.insert(MACINFO_MAP::value_type("00-16-E6-D8-53-53", "123.215.22.156"));
// 	
// 
// 	//////////////////////////////////////////////////////////////////////////////////////////
// 	// ±×·¡ÇÈÆÀ
// 
// 	// ÇÑ±¤½Ä
 	MacInfo_Map.insert(MACINFO_MAP::value_type("00-19-D1-63-8F-A0", "123.215.22.196"));
	// ÀÌÇöÁ¾
	// ÀÌÁØÈ£
// 	MacInfo_Map.insert(MACINFO_MAP::value_type("00-19-D1-64-16-96", "211.178.176.144"));

// 	//////////////////////////////////////////////////////////////////////////////////////////
// 	// °í°´Áö¿øÆÀ
// 	
 	// Á¤¿µÈ£	
 	MacInfo_Map.insert(MACINFO_MAP::value_type("00-1D-7D-CC-BB-91", "123.215.22.162"));
 	// Çãµµ¿í
 	MacInfo_Map.insert(MACINFO_MAP::value_type("00-19-D1-64-15-FD", "123.215.22.163"));
 	// ±è¸íÈ£
 	MacInfo_Map.insert(MACINFO_MAP::value_type("00-11-D8-DA-40-3D", "123.215.22.166"));
 	// È²¹Ì¶ó
 	MacInfo_Map.insert(MACINFO_MAP::value_type("00-1D-7D-E5-4C-C1", "123.215.22.164"));
	// ÇÑÁ¤¼ö
	MacInfo_Map.insert(MACINFO_MAP::value_type("00-1D-7D-A1-7F-7A", "123.215.22.208"));
	//ÀÌÀ±Á¤
	MacInfo_Map.insert(MACINFO_MAP::value_type("00-1D-7D-9D-36-28", "123.215.22.170"));
	//±èÁ¤ÇÐ
	MacInfo_Map.insert(MACINFO_MAP::value_type("00-1D-7D-A3-AC-A1", "123.215.22.182"));
	//¸íÈñ¾¾
	MacInfo_Map.insert(MACINFO_MAP::value_type("00-11-2F-25-9A-AF", "211.178.176.157"));
	//Á¤´Ù¿ò - ÀÏº»
	MacInfo_Map.insert(MACINFO_MAP::value_type("00-50-CE-30-AD-27", "211.178.176.156"));
	//À¯½Â¿¬
	MacInfo_Map.insert(MACINFO_MAP::value_type("00-1D-7D-A3-A8-A5", "123.215.22.226"));
	//Á¶Àå¿ë
	MacInfo_Map.insert(MACINFO_MAP::value_type("00-19-D1-ED-52-9D", "123.215.22.165"));
	//±èÇö¿ì
	//Çý½Å¾¾
	MacInfo_Map.insert(MACINFO_MAP::value_type("00-1D-7D-93-90-EC", "123.215.22.183"));


// 
// 
// 	//////////////////////////////////////////////////////////////////////////////////////////
// 	// ³×Æ®¿öÅ©ÆÀ
// 
// 
// 
// 	//////////////////////////////////////////////////////////////////////////////////////////
// 	// ÇØ¿Ü»ç¾÷ÆÀ
// 
// 
// 
// 	//////////////////////////////////////////////////////////////////////////////////////////
// 	// ¸¶ÄÉÆÃÆÀ
// 
// 
// 
// 	//////////////////////////////////////////////////////////////////////////////////////////
// 	// À¥¼­ºñ½ºÆÀ
// 
 	// ±è¿µÈ­
 	MacInfo_Map.insert(MACINFO_MAP::value_type("00-1B-FC-D5-10-E3", "123.215.22.210"));
 	// È²¼ºÇö
 	MacInfo_Map.insert(MACINFO_MAP::value_type("00-1D-7D-9B-59-B2", "123.215.22.187"));
	
// 
// 
// 	//////////////////////////////////////////////////////////////////////////////////////////
// 	// »ç¾÷ÆÀ
// 
// 	// ¹Ú¼º±¸
// 	MacInfo_Map.insert(MACINFO_MAP::value_type("00-11-2F-25-99-0C", "222.106.218.147"));
// 	// Àå½Â¿¬
 	MacInfo_Map.insert(MACINFO_MAP::value_type("00-0C-6E-60-79-A4", "211.178.176.157"));
	// ±èÇö±â
 	MacInfo_Map.insert(MACINFO_MAP::value_type("00-0E-A6-3C-A4-96", "123.215.22.140"));
	// ÀÌÁ¾Çü
 	MacInfo_Map.insert(MACINFO_MAP::value_type("00-1D-7D-D3-62-CE", "211.178.176.150"));

// 	//////////////////////////////////////////////////////////////////////////////////////////
// 	// ÇÃ·§ÆûÆÀ
//
	// ¿À³ª¿µ
	MacInfo_Map.insert(MACINFO_MAP::value_type("00-16-E6-D8-53-53", "123.215.22.153"));
	// ÀåÈ«¼ø
	MacInfo_Map.insert(MACINFO_MAP::value_type("0A-0A-0A-0A-16-16", "123.125.22.158"));

// 	//////////////////////////////////////////////////////////////////////////////////////////
// 	// ±×·¡ÇÈÆÀ
//
	// ÃÖÈ£Áø
	MacInfo_Map.insert(MACINFO_MAP::value_type("00-19-D1-E7-B9-2A", "123.215.22.193"));


//////////////////////////////////////////////////////////////////////////
// D2 ±âÈ¹ÆÀ

//	// ÁöÀ¯Á¤
	MacInfo_Map.insert(MACINFO_MAP::value_type("00-19-D1-59-B0-BC", "123.215.22.212"));

	
	char szMyMac[32];
	sprintf(szMyMac, "%02X-%02X-%02X-%02X-%02X-%02X", g_macAddress[0], g_macAddress[1], g_macAddress[2], g_macAddress[3], g_macAddress[4], g_macAddress[5]);

	MACINFO_MAP::const_iterator itr = MacInfo_Map.find(szMyMac); // ³» Mac Addresss°¡ ÀÖ³ª Ã£±â.
	
	if(itr != MacInfo_Map.end())
	{
		const std::string&	CheckIP		= itr->second;
		std::string			MyIPAddress = GetLocalIP();
		
		if(CheckIP == MyIPAddress)
			return true;
	}
	
	return false;
}
// 2004, 8, 26, sobeit add end - mac address Ã¼Å©ÇØ¼­ À©µµ ¸ðµå º¯°æ


// 2004, 04, 3 sobeit add start - Áúµå·¹ ¸Ê ÀÌÆåÆ® Ãß°¡ , »èÁ¦
// nEffect : 1 (À§ÂÊ ÀÌÆåÆ®), 2 (¾Æ·¡ÂÊ ÀÌÆåÆ®)
	// bAppearBossMonster : true( ¸Ê ·Îµù½Ã È¤Àº º¸½º¸÷ÀÌ Á×¾úÀ» ¶§) , false ( º¸½º¸÷ÀÌ ³ª¿À´Â ¼ø°£ ÀÌÆåÆ® )
void 
Add_GDR_Effect(int nEffect, bool bAppearBossMonster)
{
	if(1413 != g_pZone->GetID()) // Áúµå·¹ ÇÏµå only
		return;
	if(1 == nEffect) // À§ÂÊ ÀÌÆåÆ®
	{
		if(bAppearBossMonster) // º¸½º¸÷ÀÌ ³ª¿À´Â ¼ø°£ ÀÌÆåÆ®
		{
//			MEvent event;
//			event.eventID = EVENTID_CONTINUAL_GROUND_ATTACK;
//			event.eventType = EVENTTYPE_ZONE;
//			event.eventFlag = EVENTFLAG_SHAKE_SCREEN;
//			event.parameter2 = 30 << 16;
//			event.parameter3 = 5;
//			event.eventDelay = 4*1000;
//			g_pEventManager->AddEvent(event);

//			if (g_pUserOption->PlaySound)
//			{
//				PlaySound( SOUND_S_DIE, 
//					false,
//				g_pPlayer->GetX() + rand()%20-10, g_pPlayer->GetY() + rand()%20-10 );			
//
//			}
			g_pZone->RemoveTileEffect(136, 86,EFFECTSTATUS_BLACK_SMALL_SMOKE_1);
			g_pZone->RemoveTileEffect(136, 86-1,EFFECTSTATUS_BLACK_SMALL_SMOKE_2);
			g_pZone->RemoveTileEffect(136-1, 86-1,EFFECTSTATUS_BLACK_SMALL_SMOKE_3);
			g_pZone->RemoveTileEffect(136+1, 86-1,EFFECTSTATUS_BLACK_SMALL_SMOKE_1);
			g_pZone->RemoveTileEffect(136-1, 86,EFFECTSTATUS_BLACK_SMALL_SMOKE_2);
			g_pZone->RemoveTileEffect(136+1, 86,EFFECTSTATUS_BLACK_SMALL_SMOKE_3);
			g_pZone->RemoveTileEffect(136-1, 86+1,EFFECTSTATUS_BLACK_SMALL_SMOKE_1);
			g_pZone->RemoveTileEffect(136+1, 86+1,EFFECTSTATUS_BLACK_SMALL_SMOKE_2);
			g_pZone->RemoveTileEffect(136, 86+1,EFFECTSTATUS_BLACK_SMALL_SMOKE_3);
			
			g_pZone->RemoveTileEffect(137, 80,EFFECTSTATUS_BLACK_LARGE_SMOKE);
			g_pZone->RemoveTileEffect(143, 86,EFFECTSTATUS_BLACK_LARGE_SMOKE);
			g_pZone->RemoveTileEffect(136, 93,EFFECTSTATUS_BLACK_LARGE_SMOKE);
			g_pZone->RemoveTileEffect(130, 87,EFFECTSTATUS_BLACK_LARGE_SMOKE);

			ExecuteActionInfoFromMainNode(MAP_BLACK_HALL,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
					136, 86, 0, 0, NULL, false);								
			ExecuteActionInfoFromMainNode(MAP_ELECTRIC_POST,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
					137, 80, 0, 0, NULL, false);						
			ExecuteActionInfoFromMainNode(MAP_ELECTRIC_POST,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
					143, 86, 0, 0, NULL, false);						
			ExecuteActionInfoFromMainNode(MAP_ELECTRIC_POST,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
					136, 93, 0, 0, NULL, false);						
			ExecuteActionInfoFromMainNode(MAP_ELECTRIC_POST,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
					130, 87, 0, 0, NULL, false);	
		}
		else // ±âº» effect ( º¸½º¸÷ÀÌ Á×°Å³ª ¸Ê ·Îµù½Ã)
		{
			ExecuteActionInfoFromMainNode(MAP_BLACK_SMALL_SMOKE_1,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
				136, 86, 0, 0, NULL, false);								
			ExecuteActionInfoFromMainNode(MAP_BLACK_SMALL_SMOKE_2,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
				136, 86-1, 0, 0, NULL, false);								
			ExecuteActionInfoFromMainNode(MAP_BLACK_SMALL_SMOKE_3,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
				136-1, 86-1, 0, 0, NULL, false);								
			ExecuteActionInfoFromMainNode(MAP_BLACK_SMALL_SMOKE_1,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
				136+1, 86-1, 0, 0, NULL, false);								
			ExecuteActionInfoFromMainNode(MAP_BLACK_SMALL_SMOKE_2,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
				136-1, 86, 0, 0, NULL, false);								
			ExecuteActionInfoFromMainNode(MAP_BLACK_SMALL_SMOKE_3,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
				136+1, 86, 0, 0, NULL, false);								
			ExecuteActionInfoFromMainNode(MAP_BLACK_SMALL_SMOKE_1,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
				136-1, 86+1, 0, 0, NULL, false);								
			ExecuteActionInfoFromMainNode(MAP_BLACK_SMALL_SMOKE_2,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
				136+1, 86+1, 0, 0, NULL, false);								
			ExecuteActionInfoFromMainNode(MAP_BLACK_SMALL_SMOKE_3,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
				136, 86+1, 0, 0, NULL, false);			
			
			ExecuteActionInfoFromMainNode(MAP_BLACK_LARGE_SMOKE,0, 0, 0,g_pPlayer->GetDirection(),	0,	
				137, 80, 0, 0, NULL, false);								
			ExecuteActionInfoFromMainNode(MAP_BLACK_LARGE_SMOKE,0, 0, 0,g_pPlayer->GetDirection(),	0,	
				143, 86, 0, 0, NULL, false);						
			ExecuteActionInfoFromMainNode(MAP_BLACK_LARGE_SMOKE,0, 0, 0,g_pPlayer->GetDirection(),	0,	
				136, 93, 0, 0, NULL, false);						
			ExecuteActionInfoFromMainNode(MAP_BLACK_LARGE_SMOKE,0, 0, 0,g_pPlayer->GetDirection(),	0,	
				130, 87, 0, 0, NULL, false);	
		}
	}
	else if(2 == nEffect) // ¾Æ·¡ÂÊ ÀÌÆåÆ®
	{
		if(bAppearBossMonster) // º¸½º¸÷ÀÌ ³ª¿À´Â ¼ø°£ ÀÌÆåÆ®
		{
			g_pZone->RemoveTileEffect(83, 139,EFFECTSTATUS_BLACK_SMALL_SMOKE_1);
			g_pZone->RemoveTileEffect(83, 139-1,EFFECTSTATUS_BLACK_SMALL_SMOKE_2);
			g_pZone->RemoveTileEffect(83-1, 139-1,EFFECTSTATUS_BLACK_SMALL_SMOKE_3);
			g_pZone->RemoveTileEffect(83+1, 139-1,EFFECTSTATUS_BLACK_SMALL_SMOKE_1);
			g_pZone->RemoveTileEffect(83-1, 139,EFFECTSTATUS_BLACK_SMALL_SMOKE_2);
			g_pZone->RemoveTileEffect(83+1, 139,EFFECTSTATUS_BLACK_SMALL_SMOKE_3);
			g_pZone->RemoveTileEffect(83-1, 139+1,EFFECTSTATUS_BLACK_SMALL_SMOKE_1);
			g_pZone->RemoveTileEffect(83+1, 139+1,EFFECTSTATUS_BLACK_SMALL_SMOKE_2);
			g_pZone->RemoveTileEffect(83, 139+1,EFFECTSTATUS_BLACK_SMALL_SMOKE_3);
			
			g_pZone->RemoveTileEffect(83, 134,EFFECTSTATUS_BLACK_LARGE_SMOKE);
			g_pZone->RemoveTileEffect(89, 140,EFFECTSTATUS_BLACK_LARGE_SMOKE);
			g_pZone->RemoveTileEffect(82, 147,EFFECTSTATUS_BLACK_LARGE_SMOKE);
			g_pZone->RemoveTileEffect(76, 141,EFFECTSTATUS_BLACK_LARGE_SMOKE);

			ExecuteActionInfoFromMainNode(MAP_BLACK_HALL,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
					83, 139, 0, 0, NULL, false);								
			ExecuteActionInfoFromMainNode(MAP_ELECTRIC_POST,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
					83, 134, 0, 0, NULL, false);						
			ExecuteActionInfoFromMainNode(MAP_ELECTRIC_POST,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
					89, 140, 0, 0, NULL, false);						
			ExecuteActionInfoFromMainNode(MAP_ELECTRIC_POST,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
					82, 147, 0, 0, NULL, false);						
			ExecuteActionInfoFromMainNode(MAP_ELECTRIC_POST,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
					76, 141, 0, 0, NULL, false);	
		}
		else // ±âº» effect ( º¸½º¸÷ÀÌ Á×°Å³ª ¸Ê ·Îµù½Ã)
		{
			ExecuteActionInfoFromMainNode(MAP_BLACK_SMALL_SMOKE_1,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
				83, 139, 0, 0, NULL, false);								
			ExecuteActionInfoFromMainNode(MAP_BLACK_SMALL_SMOKE_2,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
				83, 139-1, 0, 0, NULL, false);								
			ExecuteActionInfoFromMainNode(MAP_BLACK_SMALL_SMOKE_3,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
				83-1, 139-1, 0, 0, NULL, false);								
			ExecuteActionInfoFromMainNode(MAP_BLACK_SMALL_SMOKE_1,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
				83+1, 139-1, 0, 0, NULL, false);								
			ExecuteActionInfoFromMainNode(MAP_BLACK_SMALL_SMOKE_2,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
				83-1, 139, 0, 0, NULL, false);								
			ExecuteActionInfoFromMainNode(MAP_BLACK_SMALL_SMOKE_3,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
				83+1, 139, 0, 0, NULL, false);								
			ExecuteActionInfoFromMainNode(MAP_BLACK_SMALL_SMOKE_1,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
				83-1, 139+1, 0, 0, NULL, false);								
			ExecuteActionInfoFromMainNode(MAP_BLACK_SMALL_SMOKE_2,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
				83+1, 139+1, 0, 0, NULL, false);								
			ExecuteActionInfoFromMainNode(MAP_BLACK_SMALL_SMOKE_3,0, 0, 0,g_pPlayer->GetDirection(),	g_pPlayer->GetID(),	
				83, 139+1, 0, 0, NULL, false);			
			
			ExecuteActionInfoFromMainNode(MAP_BLACK_LARGE_SMOKE,0, 0, 0,g_pPlayer->GetDirection(),	0,	
				83, 134, 0, 0, NULL, false);								
			ExecuteActionInfoFromMainNode(MAP_BLACK_LARGE_SMOKE,0, 0, 0,g_pPlayer->GetDirection(),	0,	
				89, 140, 0, 0, NULL, false);						
			ExecuteActionInfoFromMainNode(MAP_BLACK_LARGE_SMOKE,0, 0, 0,g_pPlayer->GetDirection(),	0,	
				82, 147, 0, 0, NULL, false);						
			ExecuteActionInfoFromMainNode(MAP_BLACK_LARGE_SMOKE,0, 0, 0,g_pPlayer->GetDirection(),	0,	
				76, 141, 0, 0, NULL, false);
		}
	}
}
// 2004, 04, 3 sobeit add end - Áúµå·¹ ¸Ê ÀÌÆåÆ® Ãß°¡

// 2004, 06, 26 sobeit add start - ÀÏ·çÀü½º ¿þÀÌ Æ÷Å»
void Add_GDR_Potal_Effect(int nMapID)
{
	if(nMapID == 1410) // ÀÏ·çÀü½º ¿þÀÌ 1
	{
		ExecuteActionInfoFromMainNode(MAP_GDR_LAIR_POTAL,0, 0, 0,0, 0,	
				73, 80, 0, 0, NULL, false);			
		ExecuteActionInfoFromMainNode(MAP_GDR_LAIR_POTAL,0, 0, 0,0, 0,	
				118, 69, 0, 0, NULL, false);			
	}
	else if(nMapID == 1411)
	{
		ExecuteActionInfoFromMainNode(MAP_GDR_LAIR_POTAL,0, 0, 0,0, 0,	
				125, 58, 0, 0, NULL, false);			
		ExecuteActionInfoFromMainNode(MAP_GDR_LAIR_POTAL,0, 0, 0,0, 0,	
				22, 85, 0, 0, NULL, false);			
		ExecuteActionInfoFromMainNode(MAP_GDR_LAIR_POTAL,0, 0, 0,0, 0,	
				9, 86, 0, 0, NULL, false);			
		ExecuteActionInfoFromMainNode(MAP_GDR_LAIR_POTAL,0, 0, 0,0, 0,	
				12, 102, 0, 0, NULL, false);			
	}
}

// 2004, 06, 26 sobeit add end - ÀÏ·çÀü½º ¿þÀÌ Æ÷Å»

// 2004, 08, 6 sobeit add start - °¢ Á¾Á·º° ¸ó½ºÅÍ Ãß°¡
void Add_Race_SlayerMonster(GCAddMonster * pPacket)
{
	MCreature* pCreature = g_pZone->GetCreature(pPacket->getObjectID());
	if(NULL == pCreature)
	{
		int CreatureType = pPacket->getMonsterType();

		MCreatureWear* pCreatureWear = new MCreatureWear;

		pCreatureWear->SetZone( g_pZone );

		pCreature = (MCreature*)pCreatureWear;

		if(CreatureType == 797)
			CreatureType = CREATURETYPE_SLAYER_FEMALE;
//		else
//			CreatureType = CREATURETYPE_SLAYER_MALE;
		pCreatureWear->SetCreatureType( CreatureType ); 
		pCreatureWear->SetGuildNumber( 1 );

		pCreatureWear->SetGroundCreature();
		pCreatureWear->SetID(pPacket->getObjectID());
		pCreatureWear->SetPosition( pPacket->getX(), pPacket->getY() );
		pCreatureWear->SetServerPosition( pPacket->getX(), pPacket->getY() );
		pCreatureWear->SetDirection( /*pPacket->getDir()*/2 );
		pCreatureWear->SetCurrentDirection( pPacket->getDir() );
		pCreatureWear->SetAction( ACTION_STAND );

		// ÇÇºÎ»ö
//			pCreatureWear->SetBodyColor1( si.getSkinColor() );
		pCreatureWear->SetStatus( MODIFY_MAX_HP, pPacket->getMaxHP() );
		pCreatureWear->SetStatus( MODIFY_CURRENT_HP,  pPacket->getCurrentHP() );
//			pCreatureWear->SetStatus( MODIFY_ALIGNMENT, si.getAlignment() );
//			pCreatureWear->SetStatus( MODIFY_RANK, si.getRank() );

		// ÀÌ¸§
		pCreatureWear->SetName( (*g_pCreatureTable)[pPacket->getMonsterType()].Name.GetString() );
		//pCreatureWear->SetName( pPacket->getMonsterName().c_str() );

		MItem* pCoat		= NULL;
		MItem* pTrouser		= NULL;
		MItem* pHelm		= NULL;
		MItem* pWeapon		= NULL;
		MItem* pShield		= NULL;
		MItem* pMotorcycle	= NULL;
		
		
		if(pPacket->getMonsterType() == 796 || pPacket->getMonsterType() == 797)
		{	
			pCoat		= g_pPacketItemJacket[JACKET_BASIC];
			pTrouser	= g_pPacketItemPants[PANTS_BASIC];
			pHelm		= g_pPacketItemHelm[HELMET_NONE];
			pWeapon		= g_pPacketItemWeapon[WEAPON_NONE];
			pShield		= g_pPacketItemShield[SHIELD_NONE];
			pMotorcycle	= g_pPacketItemMotorcycle[MOTORCYCLE_NONE];

			pCreatureWear->SetAddonColorSet1(ADDON_COAT, 393);
			pCreatureWear->SetAddonColorSet2(ADDON_COAT, 393);
			pCreatureWear->SetAddonColorSet1(ADDON_TROUSER, 393);
			pCreatureWear->SetAddonColorSet2(ADDON_TROUSER, 393);
		}
		else
		{
			//----------------------------------------	
			// º¹Àå - ¾Ï²¨³ª ÀÔÈ÷ÀÚ..-_-; ÃÑÀº sr
			//----------------------------------------	
			pCoat		= g_pPacketItemJacket[JACKET3];
			pTrouser		= g_pPacketItemPants[PANTS3];
			pHelm		= g_pPacketItemHelm[HELMET2];
			pWeapon		= g_pPacketItemWeapon[WEAPON_SR];
			pShield		= g_pPacketItemShield[SHIELD_NONE];
			pMotorcycle	= g_pPacketItemMotorcycle[MOTORCYCLE_NONE];
		}		
		pCreatureWear->SetAddonItem( pCoat );
		pCreatureWear->SetAddonItem( pTrouser );
		pCreatureWear->SetAddonItem( pHelm );
		pCreatureWear->SetAddonItem( pWeapon );
		pCreatureWear->SetAddonItem( pShield );
		pCreatureWear->SetAddonItem( pMotorcycle );


		if (!g_pZone->AddCreature( pCreatureWear ))
		{
			delete pCreatureWear;
			pCreatureWear = NULL;
			pCreature = NULL;
		}

		if(pPacket->getMonsterType() == 793)
		{
			pCreature->AddEffectStatus(EFFECTSTATUS_CAUSE_CRITICAL_WOUNDS, 0xffff);
			ExecuteActionInfoFromMainNode(RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS,pCreature->GetX(), pCreature->GetY(), 0,2,	pCreature->GetID(),	
					pCreature->GetX(), pCreature->GetY(), 0, 0xffff, NULL, false);			
		}
	}
	else
	{
		pCreature->SetGuildNumber( 1 );

		pCreature->SetGroundCreature();
		pCreature->SetPosition( pPacket->getX(), pPacket->getY() );
		pCreature->SetServerPosition( pPacket->getX(), pPacket->getY() );
		pCreature->SetDirection( pPacket->getDir() );
		pCreature->SetCurrentDirection( pPacket->getDir() );
		pCreature->SetAction( ACTION_STAND );

		// ÇÇºÎ»ö
//		pCreature->SetBodyColor1( si.getSkinColor() );

		pCreature->SetStatus( MODIFY_MAX_HP, pPacket->getMaxHP() );
		pCreature->SetStatus( MODIFY_CURRENT_HP,  pPacket->getCurrentHP() );
//			pCreature->SetStatus( MODIFY_ALIGNMENT, si.getAlignment() );
//			pCreature->SetStatus( MODIFY_RANK, si.getRank() );

		if(pPacket->getMonsterType() == 793)
		{
			pCreature->AddEffectStatus(EFFECTSTATUS_CAUSE_CRITICAL_WOUNDS, 0xffff);
			ExecuteActionInfoFromMainNode(RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS,pCreature->GetX(), pCreature->GetY(), 0,2,	pCreature->GetID(),	
					pCreature->GetX(), pCreature->GetY(), 0, 0xffff, NULL, false);			
		}
	}
}
void Add_Race_OustersMonster(GCAddMonster * pPacket)
{
	MCreature* pCreature = g_pZone->GetCreature(pPacket->getObjectID());
	if (pCreature==NULL)
	{
		int CreatureType = pPacket->getMonsterType();
		MCreatureWear* pCreatureWear = new MCreatureWear;

		pCreature = (MCreature*)pCreatureWear;

		pCreature->SetZone( g_pZone );

		pCreature->SetName( (*g_pCreatureTable)[pPacket->getMonsterType()].Name.GetString() );
		//pCreature->SetName( pPacket->getMonsterName().c_str() );

		//--------------------------------------------------
		// CreatureType ¼³Á¤
		//--------------------------------------------------
		//ItemType_t coatType = oi.getCoatType();

		pCreature->SetCreatureType( CreatureType );

		pCreature->SetID(pPacket->getObjectID());
		//pCreature->SetAction(ACTION_MOVE);
		pCreature->SetPosition( pPacket->getX(), pPacket->getY() );
		pCreature->SetServerPosition( pPacket->getX(), pPacket->getY() );
		
		pCreature->SetDirection( /*pPacket->getDir()*/2 );
		pCreature->SetCurrentDirection( pPacket->getDir() );
		pCreature->SetAction( ACTION_STAND );
		// »ö±ò
//			pCreature->SetBodyColor1( oi.getHairColor() );
//			pCreature->SetBodyColor2( oi.getCoatColor() );

		
		pCreature->SetStatus( MODIFY_MAX_HP, pPacket->getMaxHP() );
		pCreature->SetStatus( MODIFY_CURRENT_HP,  pPacket->getCurrentHP() );
//			pCreature->SetStatus( MODIFY_ALIGNMENT, oi.getAlignment() );
//			pCreature->SetStatus( MODIFY_RANK, oi.getRank() );
	
		pCreature->SetWeaponSpeed( 40 );

		pCreature->SetGuildNumber( 1 );

		if(CreatureType == 800)
		{
			MItem* pCoat		= g_pPacketItemOustersCoat[OUSTERS_COAT_BASIC];
			MItem* pArm			= g_pPacketItemOustersArm[OUSTERS_ARM_CHAKRAM];	

			pCreatureWear->SetAddonItem( pCoat );
			pCreatureWear->SetAddonItem( pArm );

			pCreatureWear->SetAddonColorSet1(ADDON_COAT, 393);
			pCreatureWear->SetAddonColorSet2(ADDON_COAT, 393);
			pCreatureWear->SetAddonColorSet1(ADDON_RIGHTHAND, 393);
			pCreatureWear->SetAddonColorSet2(ADDON_RIGHTHAND, 393);
			
			pCreature->SetBodyColor1( 393 );
			pCreature->SetBodyColor2( 393 );
			pCreature->SetFade();

		}
		
		if (!g_pZone->AddCreature( pCreature ))
		{
			delete pCreature;
			pCreature = NULL;
		}
		if(pPacket->getMonsterType() == 795)
		{
			pCreature->AddEffectStatus(EFFECTSTATUS_CAUSE_CRITICAL_WOUNDS, 0xffff);
			ExecuteActionInfoFromMainNode(RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS,pCreature->GetX(), pCreature->GetY(), 0,2,	pCreature->GetID(),	
					pCreature->GetX(), pCreature->GetY(), 0, 0xffff, NULL, false);			
		}
		
	}
	//--------------------------------------------------
	// ÀÌ¹Ì ÀÖ´Â CreatureÀÎ °æ¿ì
	//--------------------------------------------------
	else
	{
		//--------------------------------------------------
		// CreatureType ¼³Á¤
		//--------------------------------------------------
	//	ItemType_t coatType = oi.getCoatType();

	//	pCreature->SetCreatureType( CREATURETYPE_OUSTERS );

		// ÀÓ½Ã·Î
		pCreature->SetGuildNumber( 1 );
		
		//pCreature->SetAction(ACTION_MOVE);
		pCreature->SetPosition( pPacket->getX(), pPacket->getY() );
		pCreature->SetServerPosition( pPacket->getX(), pPacket->getY() );
		pCreature->SetDirection( /*pPacket->getDir()*/2 );
		pCreature->SetCurrentDirection( pPacket->getDir() );
		pCreature->SetAction( ACTION_STAND );

		// »ö±ò
//			pCreature->SetBodyColor1( oi.getHairColor() );
//			pCreature->SetBodyColor2( oi.getCoatColor() );


		//--------------------------------------------------
		// [ TEST CODE ]
		//--------------------------------------------------
		// ¿Ê »ö±ò ¼³Á¤ÇÏ±â
		//--------------------------------------------------
		/*
		if (pCreature->IsMale())
		{
			pCreature->SetBodyColor2( 91 );
		}
		else
		{
			pCreature->SetBodyColor2( 38 );
		}
		*/

		pCreature->SetStatus( MODIFY_MAX_HP, pPacket->getMaxHP() );
		pCreature->SetStatus( MODIFY_CURRENT_HP,  pPacket->getCurrentHP() );
//			pCreature->SetStatus( MODIFY_ALIGNMENT, oi.getAlignment() );
//			pCreature->SetStatus( MODIFY_RANK, oi.getRank() );

		pCreature->SetWeaponSpeed(40);

		if(pPacket->getMonsterType() == 795)
		{
			pCreature->AddEffectStatus(EFFECTSTATUS_CAUSE_CRITICAL_WOUNDS, 0xffff);
			ExecuteActionInfoFromMainNode(RESULT_MAGIC_CAUSE_CRITICAL_WOUNDS,pCreature->GetX(), pCreature->GetY(), 0,2,	pCreature->GetID(),	
					pCreature->GetX(), pCreature->GetY(), 0, 0xffff, NULL, false);			
		}
		
	}
}

// 2004, 8, 26, sobeit add start - nProtct ÀÎÁõ ÆÐÅ¶
void 
Send_nProtect_Auth(DWORD dwVal)
{
#if __CONTENTS(__NPROTECT)
	CGAuthKey _CGAuthKey;
	_CGAuthKey.setKey(dwVal);

	if( g_pSocket != NULL )
	{
		g_pSocket->sendPacket( &_CGAuthKey );
//		MessageBox(g_hWnd, "_CGAuthKeyº¸³¿", "Warning", MB_OK);
	}
#endif //__NPROTECT
}
// 2004, 8, 26, sobeit add end - nProtct ÀÎÁõ ÆÐÅ¶

POINT GetNextTileByDirection(int TileX, int TileY, byte Dir)
{
	POINT FinalTile;
	FinalTile.x = TileX; 
	FinalTile.y = TileY;
	switch (Dir)
	{
		case DIRECTION_LEFTDOWN		: FinalTile.x--;	FinalTile.y++;	break;
		case DIRECTION_RIGHTUP		: FinalTile.x++;	FinalTile.y--;	break;
		case DIRECTION_LEFTUP		: FinalTile.x--;	FinalTile.y--;	break;
		case DIRECTION_RIGHTDOWN	: FinalTile.x++;	FinalTile.y++;	break;
		case DIRECTION_LEFT			: FinalTile.x--;				break;
		case DIRECTION_DOWN			:			FinalTile.y++;	break;
		case DIRECTION_UP			:			FinalTile.y--;	break;
		case DIRECTION_RIGHT		: FinalTile.x++;				break;
	}

	return FinalTile;
}
// 2004, 11, 16, sobeit add start
void Add_RocketRuncher(MCreature* UserCreature, MCreature* TargetCreature)
{
	if(NULL == UserCreature || NULL == TargetCreature)
		return;
	int TempDir = MTopView::GetDirectionToPosition(UserCreature->GetX(), UserCreature->GetY(), TargetCreature->GetX(), TargetCreature->GetY());
	POINT _Tile = GetNextTileByDirection(UserCreature->GetX(), UserCreature->GetY(), TempDir);

	MFakeCreature *pFakeCreature = g_pZone->NewFakeCreature(CREATURETYPE_ROCKET_LUNCHER, _Tile.x, _Tile.y, UserCreature->GetDirection());
	int delayFrame = max(abs(TargetCreature->GetX()-_Tile.x), abs(TargetCreature->GetY()-_Tile.y)) * 250;

	if (!g_pZone->AddFakeCreature( pFakeCreature ))
	{
		delete pFakeCreature;
	}
	else
	{
		pFakeCreature->SetZone(g_pZone);
		pFakeCreature->SetFakeCreatureType(MFakeCreature::FAKE_CREATURE_ROCKET);
		pFakeCreature->SetMoveType(MCreature::CREATURE_FAKE_FLYING);
		pFakeCreature->AddEffectStatus( (EFFECTSTATUS)(EFFECTSTATUS_ROCKET_LUNCHER), 0xFFFF );
		pFakeCreature->SetTraceID(TargetCreature->GetID());
		pFakeCreature->SetTime(timeGetTime() + delayFrame); 
		pFakeCreature->SetGhost(0xff, 2);
	}
}
#if __CONTENTS(__SECOND_RARE_SKILL)
void Add_XRL_RocketRuncher(MCreature* UserCreature, MCreature* TargetCreature)
{
	if(NULL == UserCreature || NULL == TargetCreature)
		return;
	int TempDir = MTopView::GetDirectionToPosition(UserCreature->GetX(), UserCreature->GetY(), TargetCreature->GetX(), TargetCreature->GetY());
	POINT _Tile = GetNextTileByDirection(UserCreature->GetX(), UserCreature->GetY(), TempDir);

	MFakeCreature *pFakeCreature = g_pZone->NewFakeCreature(CREATURETYPE_XRL_ROCKET_LUNCHER, _Tile.x, _Tile.y, UserCreature->GetDirection());
	int delayFrame = max(abs(TargetCreature->GetX()-_Tile.x), abs(TargetCreature->GetY()-_Tile.y)) * 250;

	if (!g_pZone->AddFakeCreature( pFakeCreature ))
	{
		delete pFakeCreature;
	}
	else
	{
		pFakeCreature->SetZone(g_pZone);
		pFakeCreature->SetFakeCreatureType(MFakeCreature::FAKE_CREATURE_XRL_ROCKET);
		pFakeCreature->SetMoveType(MCreature::CREATURE_FAKE_FLYING);
		pFakeCreature->AddEffectStatus( (EFFECTSTATUS)(EFFECTSTATUS_XRL), 0xFFFF );
		pFakeCreature->SetTraceID(TargetCreature->GetID());
		pFakeCreature->SetTime(timeGetTime() + delayFrame); 
		pFakeCreature->SetGhost(0xff, 2);
	}
}
#endif //__SECOND_RARE_SKILL
// 2004, 11, 16, sobeit add end

// 2005, 1, 3, sobeit add start - wild wolf
void Add_Wild_Wolf(MCreature* UserCreature, MCreature* TargetCreature, bool IsEatCorpse)
{
	if(NULL == UserCreature || NULL == TargetCreature)
		return;
	int TempDir = MTopView::GetDirectionToPosition(UserCreature->GetX(), UserCreature->GetY(), TargetCreature->GetX(), TargetCreature->GetY());
	POINT StartTile = GetNextTileByDirection(UserCreature->GetX(), UserCreature->GetY(), TempDir);
//	POINT EndTile = GetNextTileByDirection(TargetCreature->GetX(), TargetCreature->GetY(), TempDir);
	
	UserCreature->SetDirection(TempDir);
//	int TempDir = MTopView::GetDirectionToPosition(g_pPlayer->GetX()+5, g_pPlayer->GetY()-5, g_pPlayer->GetX(), g_pPlayer->GetY());
//	POINT StartTile = GetNextTileByDirection(g_pPlayer->GetX()+5, g_pPlayer->GetY()-5, TempDir);
//	POINT EndTile = GetNextTileByDirection(g_pPlayer->GetX(), g_pPlayer->GetY(), TempDir);


	MFakeCreature *pFakeCreature = g_pZone->NewFakeCreature(CREATURETYPE_WILD_WOLF, StartTile.x, StartTile.y, TempDir);

	if (!g_pZone->AddFakeCreature( pFakeCreature ))
	{
		delete pFakeCreature;
	}
	else
	{
		pFakeCreature->SetZone(g_pZone);
		pFakeCreature->SetFakeCreatureType(MFakeCreature::FAKE_CREATURE_WILD_WOLF);
		pFakeCreature->SetMoveType(MCreature::CREATURE_FAKE_FLYING);
		pFakeCreature->SetTraceID(TargetCreature->GetID());
//		pFakeCreature->SetTraceID(g_pPlayer->GetID());
		pFakeCreature->SetIsEatCorpse(IsEatCorpse);
		
		pFakeCreature->SetTargetTile(TargetCreature->GetX(), TargetCreature->GetY());
	}
}
// 2005, 1, 3, sobeit add end

// 2005, 1, 6, sobeit add start - dragon tornado
void SetDragonTorando(int Type, DWORD ObjectID, int TileX, int TileY)
{
	if(g_pZone == NULL) return;
	MFakeCreature *pFakeCreature = (MFakeCreature*)(g_pZone->GetFakeCreature(ObjectID));
	if(pFakeCreature == NULL)
	{
		// ¾øÀ¸¸é »ý¼º
		int TempCreatureType = Type==EFFECTSTATUS_DRAGON_TORNADO? 788:789;
		pFakeCreature = g_pZone->NewFakeCreature(TempCreatureType, TileX, TileY, 0);
		pFakeCreature->SetID(ObjectID);
		if (!g_pZone->AddFakeCreature( pFakeCreature ))
		{
			delete pFakeCreature;
		}
		else
		{
			pFakeCreature->SetZone(g_pZone);
			pFakeCreature->SetFakeCreatureType(MFakeCreature::FAKE_CREATURE_DRAGON_TORNADO);
			pFakeCreature->SetMoveType(MCreature::CREATURE_FAKE_FLYING);
			pFakeCreature->AddEffectStatus((EFFECTSTATUS)Type, 0xffff);
			pFakeCreature->SetAction(ACTION_STAND);
		}
	}
	else
	{
		// ÁÂÇ¥°¡ Æ²¸®¸é ÀÌµ¿
		if(TileX != pFakeCreature->GetX() || TileY != pFakeCreature->GetY())
		{
			int TempDir = pFakeCreature->GetDirectionToPosition(TileX, TileY);
			pFakeCreature->SetFakeMoveOnce(TempDir);
		}
	}
}
// 2005, 1, 6, sobeit add end
void
SetSubInventoryInfo(MItem* pItem, InventoryInfo* pInventoryInfo)
{
	DEBUG_ADD( "Set SubInventory Info" );
	
	if(pInventoryInfo == NULL) return ;
	int itemNum = pInventoryInfo->getListNum();

	MSubInventory* pSubInventory = dynamic_cast<MSubInventory*>(pItem);

	if(!pSubInventory) return;

	int nSIWidth	= pSubInventory->GetWidth();
	int nSIHeight	= pSubInventory->GetHeight();

	for( int iy = 0; iy < nSIHeight; ++iy )
		for( int ix = 0; ix < nSIWidth; ++ix )
			pSubInventory->RemoveItem( ix, iy );

	//--------------------------------------------------
	// Inventory¿¡ ¾ÆÀÌÅÛµéÀ» Ãß°¡ÇÑ´Ù.
	//--------------------------------------------------
	for (int i=0; i<itemNum; i++)
	{
		// ¿ÜºÎ¿¡¼­ Áö¿öÁà¾ß ÇÑ´Ù.
		InventorySlotInfo * pSlotInfo = pInventoryInfo->popFrontListElement();

		if( pSlotInfo == NULL )
			continue;

		if( pSlotInfo->getItemClass() >= g_pItemTable->GetSize() ||
			pSlotInfo->getItemType() >= (*g_pItemTable)[pSlotInfo->getItemClass()].GetSize() )
		{
			SendBugReport("[%s] %d,%d",__FILE__, pSlotInfo->getItemClass(), pSlotInfo->getItemType());
			delete pSlotInfo;
			continue;
		}

		//------------------------------------------------
		// ItemÀ» »ý¼ºÇØ¼­ Inventory¿¡ Ãß°¡ÇÑ´Ù.
		//------------------------------------------------
		MItem* pItem = MItem::NewItem( (ITEM_CLASS)pSlotInfo->getItemClass() );
		
		// object ID
		pItem->SetID( pSlotInfo->getObjectID() );

		// type / option
		pItem->SetItemType(	pSlotInfo->getItemType() );
		pItem->SetItemOptionList( pSlotInfo->getOptionType() );
		pItem->SetItemGTwoOptionList( pSlotInfo->getGTwoOptionType() );
		pItem->SetItemThirdOptionList( pSlotInfo->getThirdOptionType() );
		pItem->SetItemThirdOptionType(pSlotInfo->getThirdEnchantType());
#if __CONTENTS(__PET_MIXINGFORGE)
		pItem->SetPetMixingOptionList(pSlotInfo->getMixOptionType());
#endif //__PET_MIXINGFORGE
#if __CONTENTS(__INTERNATIONAL_PREMIUM_SYSTEM)
		pItem->SetCashItem(pSlotInfo->getCashItem());
#endif
		// inventory¿¡¼­ÀÇ ÁÂÇ¥
		pItem->SetGridXY( pSlotInfo->getInvenX(), pSlotInfo->getInvenY() );

		//------------------------------------------
		// °³¼ö
		//------------------------------------------
		// ÃÑÀÎ °æ¿ì
		//------------------------------------------
		if (pItem->IsGunItem())
		{
			MMagazine* pMagazine = (MMagazine*)MItem::NewItem( (ITEM_CLASS)ITEM_CLASS_MAGAZINE );

			// ÀÇ¹Ì ¾øÀ½ - -;
			pMagazine->SetID( 0 );

			// ÀÌ°Å´Â ÃÑ¿¡ ¸ÂÃç¼­ ÇØÁà¾ßµÈ´Ù.
			for (int j=0; j<(*g_pItemTable)[ITEM_CLASS_MAGAZINE].GetSize(); j++)			
			{
				pMagazine->SetItemType(	j );

				if (pMagazine->IsInsertToItem( pItem ))
				{
					break;
				}
			}

			if(pSlotInfo->getSilver())
				pMagazine->SetItemType( pMagazine->GetItemType()+8);
			// ¾î¿¹~ ÀºÅºÈ¯ ÇÏµåÄÚµù by ¾¦°«

			// ÀÇ¹Ì ¾øÀ½
			pMagazine->ClearItemOption();
		
			// ÅºÃ¢ °³¼ö
			pMagazine->SetNumber( pSlotInfo->getItemNum() );

			//------------------------------------
			// ÅºÃ¢ ¼³Á¤
			//------------------------------------
			MGunItem* pGunItem = (MGunItem*)pItem;
			pGunItem->SetMagazine( pMagazine );
		}		
		//------------------------------------------
		// ÃÑÀÌ ¾Æ´Ñ °æ¿ì
		//------------------------------------------
		else
		{
			pItem->SetNumber( pSlotInfo->getItemNum() );
		}


		//------------------------------------------
		//
		// Item¿¡ ´Ù¸¥ itemµéÀÌ µé¾îÀÖ´Â °æ¿ì
		//
		//------------------------------------------
		if (pSlotInfo->getListNum()!=0)
		{
			DEBUG_ADD_FORMAT("This Item has Sub item(s) : size=%d", pSlotInfo->getListNum());
			
			//------------------------------------------
			// BeltÀÎ °æ¿ì
			//------------------------------------------
			if (pItem->GetItemClass()==ITEM_CLASS_BELT)
			{
				MBelt* pBelt = (MBelt*)pItem;

				int size = pSlotInfo->getListNum();
				
				for (int i=0; i<size; i++)
				{
					SubItemInfo * pSubItemInfo = pSlotInfo->popFrontListElement();

					if (pSubItemInfo==NULL)
					{
						DEBUG_ADD("[Error] Sub Item is NULL");
					}
					else
					{
						//------------------------------------------
						// Sub ItemÀÇ Á¤º¸¸¦ ¼³Á¤ÇÑ´Ù.
						//------------------------------------------
						if ( pSubItemInfo->getItemClass() >= g_pItemTable->GetSize() ||
							(*g_pItemTable)[pSubItemInfo->getItemClass()].GetSize() <= pSubItemInfo->getItemType() )
						{
							SendBugReport("[PacketFunction::SetInventoryInfo,%d] %d,%d",__LINE__,pSubItemInfo->getItemClass(), pSubItemInfo->getItemType() );
							return;
						}
						MItem* pSubItem = MItem::NewItem( (enum ITEM_CLASS)pSubItemInfo->getItemClass() );
						pSubItem->SetItemType( pSubItemInfo->getItemType() );
						//pItem->SetItemOption( pSubItemInfo->getOptionType() );

						pSubItem->SetID( pSubItemInfo->getObjectID() );		

						pSubItem->SetNumber( pSubItemInfo->getItemNum() );			

						//------------------------------------------
						// BeltÀÇ Á¤ÇØÁø slot¿¡ itemÀ» Ãß°¡½ÃÅ²´Ù.
						//------------------------------------------
						pBelt->AddItem( pSubItem, pSubItemInfo->getSlotID() );

						delete pSubItemInfo;
					}
				} 
			}
			else if (pItem->GetItemClass()==ITEM_CLASS_OUSTERS_ARMSBAND)
			{
				MOustersArmsBand* pBelt = (MOustersArmsBand*)pItem;
				
				int size = pSlotInfo->getListNum();
				
				for (int i=0; i<size; i++)
				{
					SubItemInfo * pSubItemInfo = pSlotInfo->popFrontListElement();
					
					if (pSubItemInfo==NULL)
					{
						DEBUG_ADD("[Error] Sub Item is NULL");
					}
					else
					{
						//------------------------------------------
						// Sub ItemÀÇ Á¤º¸¸¦ ¼³Á¤ÇÑ´Ù.
						//------------------------------------------
						if ( pSubItemInfo->getItemClass() >= g_pItemTable->GetSize() ||
							(*g_pItemTable)[pSubItemInfo->getItemClass()].GetSize() <= pSubItemInfo->getItemType() )
						{
							SendBugReport("[PacketFunction::SetInventoryInfo,%d] %d,%d",__LINE__,pSubItemInfo->getItemClass(), pSubItemInfo->getItemType() );
							return;
						}
						MItem* pSubItem = MItem::NewItem( (enum ITEM_CLASS)pSubItemInfo->getItemClass() );
						pSubItem->SetItemType( pSubItemInfo->getItemType() );
						//pItem->SetItemOption( pSubItemInfo->getOptionType() );
						
						pSubItem->SetID( pSubItemInfo->getObjectID() );		
						
						pSubItem->SetNumber( pSubItemInfo->getItemNum() );			
						
						//------------------------------------------
						// BeltÀÇ Á¤ÇØÁø slot¿¡ itemÀ» Ãß°¡½ÃÅ²´Ù.
						//------------------------------------------
						pBelt->AddItem( pSubItem, pSubItemInfo->getSlotID() );
						
						delete pSubItemInfo;
					}
				}
			}
			else
			{
				DEBUG_ADD_FORMAT("This Item can't have Sub item : class=%d", (int)pItem->GetItemClass());
			}
		}


		// main»ö±ò
		pItem->SetItemColorSet( pSlotInfo->getMainColor() );

		// ÇöÀç ³»±¸¼º
		pItem->SetCurrentDurability( pSlotInfo->getDurability() );
		pItem->SetSilver( pSlotInfo->getSilver() );
		pItem->SetGrade( pSlotInfo->getGrade() );
		pItem->SetEnchantLevel( pSlotInfo->getEnchantLevel() );

		g_pPlayer->CheckAffectStatus(pItem);
		
		//---------------------------------------------
		// itemÀ» inventory¿¡ ³Ö´Â´Ù.
		//---------------------------------------------
		if(false == UI_AddItemToSubInventory(
				pSubInventory->GetID(),
				pItem, pItem->GetGridX(), pItem->GetGridY()))
		{
			// itemÀ» inventory¿¡ Ãß°¡ÇÒ ¼ö ¾ø´Â °æ¿ì
			DEBUG_ADD_FORMAT("[Error] Can't Add Item to Inventory. id=%d, cl=%d, tp=%d, xy=(%d,%d)", 					
											(int)pItem->GetID(),
											(int)pItem->GetItemClass(),
											(int)pItem->GetItemType(),
											(int)pItem->GetGridX(),
											(int)pItem->GetGridY());
			
			delete pItem;
		}

		delete pSlotInfo;
	}

	//pSubInventory->CheckAffectStatusAll();
}



// 2007.10.02 chyaya add start - FakeCreature Storm
void Add_FakeCreature_Storm(MCreature* UserCreature, int CreatureType,
							int TargetX, int TargetY, int RangeW, int RangeH, float density)
{
	if(NULL == UserCreature)
		return;

	int TempDir = MTopView::GetDirectionToPosition(UserCreature->GetX(), UserCreature->GetY(), TargetX, TargetY);
	POINT StartTile = GetNextTileByDirection(UserCreature->GetX(), UserCreature->GetY(), TempDir);
//	POINT EndTile = GetNextTileByDirection(TargetCreature->GetX(), TargetCreature->GetY(), TempDir);
	
	UserCreature->SetDirection(TempDir);

	const int StormSize = RangeW * RangeH * density;

	for(int i = 0; i < StormSize; ++i)
	{
		MFakeCreature *pFakeCreature = g_pZone->NewFakeCreature(CreatureType, StartTile.x, StartTile.y, TempDir);

		if (!g_pZone->AddFakeCreature( pFakeCreature ))
		{
			delete pFakeCreature;
		}
		else
		{
			pFakeCreature->SetZone(g_pZone);
			pFakeCreature->SetFakeCreatureType(MFakeCreature::FAKE_CREATURE_RANDOM_MOVE);
			pFakeCreature->SetMoveType(MCreature::CREATURE_FAKE_FLYING);
			pFakeCreature->SetSkipShadow(false);
			
			pFakeCreature->SetTargetTile(TargetX, TargetY);
			pFakeCreature->SetFakePosition(TargetX, TargetY);
			pFakeCreature->SetFakeRange(RangeW, RangeH);
		}
	}
}
void Add_FakeCreature_Wild_Wolf_Strike(MCreature* UserCreature, MCreature* TargetCreature)	 //--221 ¹í×å ÈºÀÇ
{
	if(NULL == UserCreature || NULL == TargetCreature)
		return;
	int TempDir = MTopView::GetDirectionToPosition(UserCreature->GetX(), UserCreature->GetY(), TargetCreature->GetX(), TargetCreature->GetY());
	POINT StartTile = GetNextTileByDirection(UserCreature->GetX(), UserCreature->GetY(), TempDir);

	UserCreature->SetDirection(TempDir);

	MFakeCreature *pFakeCreature = g_pZone->NewFakeCreature(CREATURETYPE_DARK_WOLF, StartTile.x, StartTile.y, TempDir);

	if (!g_pZone->AddFakeCreature( pFakeCreature ))
	{
		delete pFakeCreature;
	}
	else
	{
		pFakeCreature->SetZone(g_pZone);
		pFakeCreature->SetFakeCreatureType(MFakeCreature::FAKE_CREATURE_WILD_WOLF);
		pFakeCreature->SetMoveType(MCreature::CREATURE_FAKE_FLYING);
		pFakeCreature->SetTraceID(TargetCreature->GetID());

		pFakeCreature->SetTargetTile(TargetCreature->GetX(), TargetCreature->GetY());
	}
}
// 2007.10.02 chyaya add end
#if __CONTENTS(__ONIBLA)
void
SkillGhostShadow(MCreature* pUserCreature, MCreature* pTargetCreature, int skillID, int shadowCount, int shape)
{
	//------------------------------------------------------------------
	// Ã¼Å© Ã¼Å©~
	//------------------------------------------------------------------
	if (pUserCreature==NULL || pTargetCreature==NULL)
	{
		DEBUG_ADD("[Error] ShadowDancing. Creature NULL or Not WearCreature");
		
		return;
	}

	// [ TEST CODE ]
	// ÁøÇàÁßÀÎ EffectÀÌ¸é Result·Î Ãß°¡ÇØ¾ß ÇÑ´Ù.
	// Result¸¦ »ý¼ºÇÏ°í..
	// pUserCreature->>AddActionResult( ... )
		
	//------------------------------------------------------
	// Fake CreatureÀÇ ÁÂÇ¥ °è»ê
	//------------------------------------------------------
	int x = pTargetCreature->GetX();
	int y = pTargetCreature->GetY();
	
	// ¸Â´Â ¾Ö¿¡¼­ player¹æÇâÀ¸·Î ÇÑ Ä­..
	int sx = pUserCreature->GetX() - x;
	int sy = pUserCreature->GetY() - y;

	if (sx>0) sx=1; else if (sx<0) sx=-1; else sx=0;
	if (sy>0) sy=1; else if (sy<0) sy=-1; else sy=0;

	//------------------------------------------------------
	// Fake Creature »ý¼º
	//------------------------------------------------------

	POINT Straight[4] = {
		{ -2, -2 },
		{ -2,  2 },
		{ 2,  -2 },
		{ 2,   2 },
	};

	POINT Diagonal[4] = {
		{ 0,  2 },
		{ 2,  0 },
		{ -2, 0 },
		{ 0, -2 },
	};

	POINT *Position;
	
	switch(shape) {
		case 0: // ÀÚµ¿
			Position = (pUserCreature->GetDirection() & 0x1) ? Diagonal : Straight;
			break;
		case 1: // ½ÊÀÚ¸ð¾ç(+)
			Position = Diagonal;
			break;
		case 2: // ¿¢½º¸ð¾ç(x)
			Position = Straight;
			break;
	}
	
	for (int i=0; i<shadowCount; i++)
	{	
		MFakeCreature* pFakeCreature = g_pZone->NewFakeCreature( pUserCreature, pUserCreature->GetX() , pUserCreature->GetY() );

		int dir = pFakeCreature->GetDirectionToPosition( pUserCreature->GetX(), pUserCreature->GetY() );
		pFakeCreature->SetDirection( dir );
		pFakeCreature->SetCurrentDirection( dir );

		pFakeCreature->SetAction( ACTION_MAGIC );		// ±×³É.. - -;;

		//------------------------------------------------------
		// ÀÜ»ó ÇÑ¹ø º¸¿©ÁÖ°í »ç¶óÁö°Ô ¼³Á¤
		//------------------------------------------------------
		pFakeCreature->SetFakeCreatureType( MFakeCreature::FAKE_CREATURE_FAST_MOVE_ACTION);

		//------------------------------------------------------
		// Fake Creature¸¦ Zone¿¡ Ãß°¡
		//------------------------------------------------------
		if (!g_pZone->AddFakeCreature( pFakeCreature ))
		{
			delete pFakeCreature;
		}

		//------------------------------------------------------
		// ±â¼ú »ç¿ë
		//------------------------------------------------------
		if (skillID==SKILL_ATTACK_MELEE)
		{	
			skillID = pUserCreature->GetBasicActionInfo();
		}

		if (skillID >= g_pActionInfoTable->GetMinResultActionInfo())
		{
			DEBUG_ADD_FORMAT("[Error] SkillType Error = %d", skillID);
			return;
		}

//		MActionResult* pResult = new MActionResult;
		
		DWORD delayFrame = 0;//ConvertDurationToFrame( pPacket->getDuration() );
		
		pFakeCreature->SetFakeCreatureFastMoveAction(
			pUserCreature->GetX() + Position[i].x, pUserCreature->GetY() + Position[i].y,
			skillID, 
			pTargetCreature->GetID() );
	}
	
}
#endif //__ONIBLA
