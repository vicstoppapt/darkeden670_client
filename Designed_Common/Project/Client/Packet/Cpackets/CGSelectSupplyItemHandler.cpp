//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSelectSupplyItemHandler.cpp
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "Client_PCH.h"
#include "CGSelectSupplyItem.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "Zone.h"
	#include "PacketUtil.h"
	#include "Inventory.h"

	#include "ItemFactoryManager.h"

	#include "Gpackets/GCCreateItem.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSelectSupplyItemHandler::execute(CGSelectSupplyItem* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY// __BEGIN_DEBUG_EX

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
	
	Item::ItemClass itemClass;
	ItemType_t itemType;
	
	if ( pPacket->getSelectID() == 1 )
	{
		itemClass = (Item::ItemClass)97;
		itemType = 0;
		
		list<OptionType_t> nullList;
		Item* pItem = CREATE_ITEM(itemClass, itemType, nullList);

		(pZone->getObjectRegistry()).registerObject(pItem);
		
		// 인벤토리의 빈 곳을 찾는다.
		_TPOINT p;
		if (pInventory->getEmptySlot(pItem, p))
		{
			// 인벤토리에 추가한다.
			pInventory->addItem(p.x, p.y, pItem);
			pItem->create(pCreature->getName(), STORAGE_INVENTORY, 0, p.x, p.y);

//			// ItemTrace 에 Log 를 남긴다
//			if ( pItem != NULL && pItem->isTraceItem() )
//			{
//				remainTraceLog( pItem, "MenegrothDoungeon", pCreature->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
//				remainTraceLogNew( pItem, pCreature->getName(), ITL_GET, ITLD_EVENTNPC, m_pZone->getZoneID() );
//			}

			// 인벤토리에 아이템 생성 패킷을 보내준다.
			GCCreateItem gcCreateItem;
			makeGCCreateItem( &gcCreateItem, pItem, p.x, p.y );
			pCreature->getPlayer()->sendPacket(&gcCreateItem);
		}

				
				
	}
	else if ( pPacket->getSelectID() == 2 )
	{
		
	}
	else
	{
		
	}
	
#endif /* __GAME_SERVER__ */

	__END_CATCH// __END_DEBUG_EX
}


