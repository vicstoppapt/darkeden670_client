//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectAllSupplyItemHandler.cpp
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "Client_PCH.h"
#include "CGSelectAllSupplyItem.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "Zone.h"
	#include "PacketUtil.h"
	#include "ItemUtil.h"
	#include "Inventory.h"
	#include "StringPool.h"

	#include "ItemFactoryManager.h"
	#include "SupplyItemListManager.h"

	#include "Gpackets/GCCreateItem.h"
	#include "Gpackets/GCUpdateSupplyItemList.h"
	#include "Gpackets/GCSystemMessage.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSelectAllSupplyItemHandler::execute(CGSelectAllSupplyItem* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY//__BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);
	
	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);
	
	Creature* pCreature = pGamePlayer->getCreature();
	if ( pCreature == NULL )
	{
		return;
	}	
	
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	if ( pPC == NULL )
	{
		return;
	}
		
	Zone *pZone = pPC->getZone();
	if ( pZone == NULL )
	{
		return;
	}
	
	Inventory* pInventory = pPC->getInventory();
	if ( pInventory == NULL )
	{
		return;
	}
	
	SupplyItemListManager *pSupplyItemListManager;
	
	pSupplyItemListManager = pPC->getSupplyItemListManager();
	if ( pSupplyItemListManager == NULL )
	{
		return;
	}
	
	while( true )
	{
		Item *pItem = pSupplyItemListManager->PickupFrontItem();
		if ( pItem == NULL )
		{
			break;
		}
	
		(pZone->getObjectRegistry()).registerObject(pItem);
			
		// 인벤토리의 빈 곳을 찾는다.
		_TPOINT p;
		if (pInventory->getEmptySlot(pItem, p))
		{
			// 인벤토리에 추가한다.
			pInventory->addItem(p.x, p.y, pItem);
			pItem->create(pCreature->getName(), STORAGE_INVENTORY, 0, p.x, p.y);
	
			// ItemTrace 에 Log 를 남긴다
			if ( pItem != NULL )
			{
				remainTraceLog( pItem, "SupplyItem", pCreature->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
				remainTraceLogNew( pItem, pCreature->getName(), ITL_GET, ITLD_EVENTNPC, pZone->getZoneID() );
			}
	
			// 인벤토리에 아이템 생성 패킷을 보내준다.
			GCCreateItem gcCreateItem;
			makeGCCreateItem( &gcCreateItem, pItem, p.x, p.y );
			pGamePlayer->sendPacket(&gcCreateItem);
		}
		else
		{
			// 인벤토리에 빈자리가 없음
			
			StringStream buf;

			buf << g_pStringPool->getString( STRID_NOT_ENOUGH_INVENTORY_SPACE );
			
			GCSystemMessage	gcSystemMessage;
			gcSystemMessage.setMessage(buf.toString());
			
			pGamePlayer->sendPacket(&gcSystemMessage);	
	
			break;
		}
	}
	
	GCUpdateSupplyItemList gcUpdateSupplyItemList;
	makeGCUpdateSupplyItemList(&gcUpdateSupplyItemList, pPC);
	pGamePlayer->sendPacket( &gcUpdateSupplyItemList );
	
#endif /* __GAME_SERVER__ */

	__END_CATCH//__END_DEBUG_EX
}


