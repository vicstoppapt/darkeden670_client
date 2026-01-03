//////////////////////////////////////////////////////////////////////
//
// Filename    : GCTradeAddItemHandler.cpp
// Written By  : 김성민
// Description :
//
//////////////////////////////////////////////////////////////////////

// include files
#include "Client_PCH.h"
#include "GCTradeAddItem.h"
#include "ClientDef.h"
#include "MTradeManager.h"
#include "MItem.h"

void GCTradeAddItemHandler::execute ( GCTradeAddItem * pPacket , Player * pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY
	
#ifdef __GAME_CLIENT__
#if __CONTENTS(__PCITEMINFO2)
	PCItemInfo* pPCItemInfo = pPacket->GetPCItemInfo();
#else //__PCITEMINFO2
	GCTradeAddItem* pPCItemInfo =  pPacket;
#endif //__PCITEMINFO2
	//------------------------------------------------------------------------
	// TradeManager가 생성되지 않은 경우 --> -_-;;
	//------------------------------------------------------------------------
	if (g_pTradeManager==NULL)
	{
		DEBUG_ADD( "[Error] TradeManager is NULL");
		
		return;
	}

	//------------------------------------------------------------------------
	// 추가되는 아이템 생성
	//------------------------------------------------------------------------
	MItem* pItem = MItem::NewItem( (ITEM_CLASS)pPCItemInfo->getItemClass() );

	pItem->SetID( pPCItemInfo->getObjectID() );
	
	pItem->SetItemType( pPCItemInfo->getItemType() );
	pItem->SetItemOptionList( pPCItemInfo->getOptionType() );
#if __CONTENTS(__PET_MIXINGFORGE)
	pItem->SetPetMixingOptionList(pPCItemInfo->getMixOptionType());
#endif //__PET_MIXINGFORGE
	pItem->SetCurrentDurability( pPCItemInfo->getDurability() );
	pItem->SetSilver( pPCItemInfo->getSilver() );	
	pItem->SetGrade( pPCItemInfo->getGrade() );	
	pItem->SetItemThirdOptionList(pPCItemInfo->getThirdOptionType() );
	pItem->SetItemThirdOptionType(pPCItemInfo->getThirdEnchantType());
#if __CONTENTS(__INTERNATIONAL_PREMIUM_SYSTEM)
	pItem->SetCashItem(pPCItemInfo->getCashItem());
#endif	
	//ObjectID_t getTargetObjectID() const throw() { return m_TargetObjectID; }

	//------------------------------------------------------------------------
	// 개수
	//------------------------------------------------------------------------
	// 총인 경우
	//------------------------------------------------------------------------
	if (pItem->IsGunItem())
	{
		MMagazine* pMagazine = (MMagazine*)MItem::NewItem( (ITEM_CLASS)ITEM_CLASS_MAGAZINE );

		// 의미 없음 - -;
		pMagazine->SetID( 0 );

		// 이거는 총에 맞춰서 해줘야된다.
		for (int j=0; j<(*g_pItemTable)[ITEM_CLASS_MAGAZINE].GetSize(); j++)			
		{
			pMagazine->SetItemType(	j );

			if (pMagazine->IsInsertToItem( pItem ))
			{
				break;
			}
		}

		// 의미 없음
		pMagazine->ClearItemOption();
	
		// 탄창 개수
		pMagazine->SetNumber( pPCItemInfo->getItemNum() );

		//------------------------------------
		// 탄창 설정
		//------------------------------------
		MGunItem* pGunItem = (MGunItem*)pItem;
		pGunItem->SetMagazine( pMagazine );
	}		
	//------------------------------------------------------------------------
	// 총이 아닌 경우
	//------------------------------------------------------------------------
	else
	{
		pItem->SetNumber( pPCItemInfo->getItemNum() );
	}

	pItem->SetEnchantLevel( pPCItemInfo->getEnchantLevel() );

	//------------------------------------------------------------------------
	//
	// Item에 다른 item들이 들어있는 경우
	//
	//------------------------------------------------------------------------
	if (pPCItemInfo->getListNum()!=0)
	{
		DEBUG_ADD_FORMAT("This Item has Sub item(s) : size=%d", pPCItemInfo->getListNum());
		
		//------------------------------------------
		// Belt인 경우
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
					// Sub Item의 정보를 설정한다.
					//------------------------------------------
					MItem* pSubItem = MItem::NewItem( (enum ITEM_CLASS)pSubItemInfo->getItemClass() );
					pSubItem->SetItemType( pSubItemInfo->getItemType() );
					//pItem->SetItemOption( pSubItemInfo->getOptionType() );

					pSubItem->SetID( pSubItemInfo->getObjectID() );		

					pSubItem->SetNumber( pSubItemInfo->getItemNum() );			

					//------------------------------------------
					// Belt의 정해진 slot에 item을 추가시킨다.
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
					// Sub Item의 정보를 설정한다.
					//------------------------------------------
					MItem* pSubItem = MItem::NewItem( (enum ITEM_CLASS)pSubItemInfo->getItemClass() );
					pSubItem->SetItemType( pSubItemInfo->getItemType() );
					//pItem->SetItemOption( pSubItemInfo->getOptionType() );
					
					pSubItem->SetID( pSubItemInfo->getObjectID() );		
					
					pSubItem->SetNumber( pSubItemInfo->getItemNum() );			
					
					//------------------------------------------
					// Belt의 정해진 slot에 item을 추가시킨다.
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

	
	int gridX = pPacket->getX();
	int gridY = pPacket->getY();

	//------------------------------------------------------------------------
	// other Inventory에 추가한다..
	// 추가 안되면.. 콩가루.. - -;
	//------------------------------------------------------------------------
	if (!g_pTradeManager->GetOtherInventory()->AddItem( pItem, gridX, gridY ))
	{
		DEBUG_ADD_FORMAT("[Error] Can't add item to OtherInventory:id=%d (%d, %d)", pItem->GetID(), gridX, gridY);
		
		delete pItem;
	}

	//-----------------------------------------------------------
	// 뭔가 바뀐다면... OK취소
	//-----------------------------------------------------------
	g_pTradeManager->RefuseOtherTrade();
	g_pTradeManager->RefuseMyTrade();

#endif

	__END_CATCH
}
