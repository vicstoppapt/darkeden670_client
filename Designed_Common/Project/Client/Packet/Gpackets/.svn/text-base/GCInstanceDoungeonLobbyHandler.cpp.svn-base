//////////////////////////////////////////////////////////////////////
//
// Filename    : GCInstanceDoungeonLobbyHandler.cpp
// Written By  : rappi76
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCInstanceDoungeonLobby.h"
#include "ClientDef.h"
#include "TalkBox.h"
#include "UIDialog.h"
#include "MNPCScriptTable.h"
#include "TempInformation.h"
#include "SystemAvailabilities.h"

#include "VS_UI_INDOUN_NPC_DIALOG.h"
#include "VS_UI.h"

//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
#if __CONTENTS(__TIPOJYU_CASTLE)
extern C_VS_UI		gC_vs_ui;

void GCInstanceDoungeonLobbyHandler::execute ( GCInstanceDoungeonLobby * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__
	//cout << pPacket->toString() << endl;

	if (g_pPlayer==NULL
		|| g_pZone==NULL
		|| g_pNPCScriptTable==NULL
		|| g_pUIDialog==NULL
		|| g_pPCTalkBox==NULL)
	{
		DEBUG_ADD("[Error] Some Object is NULL");
		return;
	}


//	if (g_pPlayer->GetWaitVerify()==MPlayer::WAIT_VERIFY_NPC_ASK)
	{
		g_pPlayer->SetWaitVerifyNULL();
		
		// NPC
		MCreature* pCreature = g_pZone->GetCreature( pPacket->getObjectID() );

		if (pCreature!=NULL || pPacket->getNPCID() >= 634 && pPacket->getNPCID() <= 806) //637 )
		{		
			unsigned int CreatureType;

			if(pPacket->getNPCID() >= 634 && pPacket->getNPCID() <= 806) //637 )
			{
				CreatureType = pPacket->getNPCID();
			} else
			{
				CreatureType= pCreature->GetCreatureType();
			}

			S_INDOUN_DLG_INFO Indoun_Npc_Dlg_Info;

			InstanceDoungeonInfo	*pDoungeon		= NULL;
			int contentSize = pPacket->getButtonSize();
			
			Indoun_Npc_Dlg_Info.Realese();
			string str;
			for (int i = 0;		i < contentSize;	i++)
			{
				pDoungeon		= pPacket->getDoungeonInfo(i);
				Indoun_Npc_Dlg_Info.mapButtonNameList.push_back(pDoungeon->getDoungeonName());

				str	= pDoungeon->getDoungeonName();
			}

			Indoun_Npc_Dlg_Info.strDlgTitleName		= pPacket->getDoungeonTitle();
			Indoun_Npc_Dlg_Info.strNpcName			= pCreature->GetName();
			Indoun_Npc_Dlg_Info.wButtonSize			= contentSize;
			Indoun_Npc_Dlg_Info.wObjectID			= pPacket->getObjectID();
			Indoun_Npc_Dlg_Info.wNpcID				= CreatureType;
			Indoun_Npc_Dlg_Info.strDesc				= pPacket->getDoungeonDesc();

#if __CONTENTS(__TIPOJYU_CASTLE)
			gC_vs_ui.RunIndounNpcDlg(Indoun_Npc_Dlg_Info, ENTRANCE_DLG);
#endif // __TIPOJYU_CASTLE
			//---------------------------------------------------
			// g_PCTalkBox에 추가하면 된다.
			//---------------------------------------------------
			// 기존에 있던것 제거
			g_pPCTalkBox->Release();

			DEBUG_ADD("TalkBoxRel");

		}
						
	}
//	else
	{
//		DEBUG_ADD("[Error] WaitVerifyMode is Not WAIT_VERIFY_NPC_ASK");
	}

#endif

	__END_CATCH
}

#endif //__TIPOJYU_CASTLE