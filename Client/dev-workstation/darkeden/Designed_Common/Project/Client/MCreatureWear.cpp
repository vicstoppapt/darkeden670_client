//----------------------------------------------------------------------
// MCreatureWear.cpp
//----------------------------------------------------------------------
#include "Client_PCH.h"
#include "MCreatureWear.h"
#include "MItem.h"
#include "AddonDef.h"
#include "SkillDef.h"
#include "DebugInfo.h"
#include "CIndexSprite.h"
#include "ClientConfig.h"
#include "MEffectGeneratorTable.h"
#include "MEffectSpriteTypeTable.h"
#include "EffectSpriteTypeDef.h"
#include "MItemOptionTable.h"
#include "PacketFunction.h"
#include "MinTR.H"
#include "MTopView.h"
#include "MPlayer.h"

int defaultSkinColor		= 410;					
int defaultCoatColor		= 377;//368;	
int defaultTrouserColor	= 377;//489;	


#define	ATTACHEFFECTCOLOR_NULL		0xFFFF

//----------------------------------------------------------------------
// static member
//----------------------------------------------------------------------
// CreatureÀÇ ÇöÀç ¹æÇâ¿¡ µû¶ó¼­...
// ¿ÊÀ» Ãâ·ÂÇØÁÖ´Â ¼ø¼­°¡ ´Ù¸¦ ¼ö ÀÖ´Ù.
// °¢ ¹æÇâº°·Î ¿Ê Ãâ·ÂÇØÁÖ´Â ¼ø¼­¸¦ Á¤ÇÏ´Â ºÎºÐÀÌ´Ù.
int			MCreatureWear::s_AddonOrder[DIRECTION_MAX][ADDON_MAX] = 
{
	{ ADDON_MOTOR, ADDON_TROUSER, ADDON_COAT, ADDON_HAIR, ADDON_HELM, ADDON_RIGHTHAND, ADDON_LEFTHAND },	// LEFT
	{ ADDON_MOTOR, ADDON_TROUSER, ADDON_COAT, ADDON_HAIR, ADDON_HELM, ADDON_RIGHTHAND, ADDON_LEFTHAND },	// LEFTDOWN
	{ ADDON_MOTOR, ADDON_TROUSER, ADDON_COAT, ADDON_HAIR, ADDON_HELM, ADDON_LEFTHAND, ADDON_RIGHTHAND },	// DOWN	
	{ ADDON_MOTOR, ADDON_TROUSER, ADDON_COAT, ADDON_HAIR, ADDON_HELM, ADDON_LEFTHAND, ADDON_RIGHTHAND },	// RIGHTDOWN	
	{ ADDON_MOTOR, ADDON_TROUSER, ADDON_COAT, ADDON_HAIR, ADDON_HELM, ADDON_LEFTHAND, ADDON_RIGHTHAND },	// RIGHT
	{ ADDON_MOTOR, ADDON_TROUSER, ADDON_COAT, ADDON_HAIR, ADDON_HELM, ADDON_LEFTHAND, ADDON_RIGHTHAND },	// RIGHTUP
	{ ADDON_MOTOR, ADDON_TROUSER, ADDON_COAT, ADDON_HAIR, ADDON_HELM, ADDON_RIGHTHAND, ADDON_LEFTHAND },	// UP
	{ ADDON_MOTOR, ADDON_TROUSER, ADDON_COAT, ADDON_HAIR, ADDON_HELM, ADDON_RIGHTHAND, ADDON_LEFTHAND }		// LEFTUP
};

int	MCreatureWear::s_ACAddonOrder[ DIRECTION_MAX ][ AC_ADDON_MAX ] =
{
	{ AC_ADDON_MOTOR, AC_ADDON_BODY, AC_ADDON_HELM, AC_ADDON_SHOULDER, AC_ADDON_RIGHTHAND, AC_ADDON_LEFTHAND },
	{ AC_ADDON_MOTOR, AC_ADDON_BODY, AC_ADDON_HELM, AC_ADDON_SHOULDER, AC_ADDON_RIGHTHAND, AC_ADDON_LEFTHAND },
	{ AC_ADDON_MOTOR, AC_ADDON_BODY, AC_ADDON_HELM, AC_ADDON_SHOULDER, AC_ADDON_LEFTHAND, AC_ADDON_RIGHTHAND },
	{ AC_ADDON_MOTOR, AC_ADDON_BODY, AC_ADDON_HELM, AC_ADDON_SHOULDER, AC_ADDON_LEFTHAND, AC_ADDON_RIGHTHAND },
	{ AC_ADDON_MOTOR, AC_ADDON_BODY, AC_ADDON_HELM, AC_ADDON_SHOULDER, AC_ADDON_LEFTHAND, AC_ADDON_RIGHTHAND },
	{ AC_ADDON_MOTOR, AC_ADDON_BODY, AC_ADDON_HELM, AC_ADDON_SHOULDER, AC_ADDON_LEFTHAND, AC_ADDON_RIGHTHAND },
	{ AC_ADDON_MOTOR, AC_ADDON_BODY, AC_ADDON_HELM, AC_ADDON_SHOULDER, AC_ADDON_RIGHTHAND, AC_ADDON_LEFTHAND },
	{ AC_ADDON_MOTOR, AC_ADDON_BODY, AC_ADDON_HELM, AC_ADDON_SHOULDER, AC_ADDON_RIGHTHAND, AC_ADDON_LEFTHAND },
};


//----------------------------------------------------------------------
//
//  constructor/destructor
//
//----------------------------------------------------------------------
MCreatureWear::MCreatureWear()
{
	for (int i=0; i<ADDON_MAX; i++)
	{
		ClearAddonInfo( i );
	}

	m_HairFrameID = ADDONID_HAIR1;
	m_HairColorSet = 0;

	m_ShoulderAddon.bAddon = FALSE;
	m_ShoulderAddon.FrameID	= FRAMEID_NULL;		// º¹Àå

	m_ShoulderAddon.ItemClass	= ITEM_CLASS_NULL;	// item class
	m_ShoulderAddon.ItemType	= ITEMTYPE_NULL;			// item type
	m_ShoulderAddon.ColorSet1	= 0;						// colorset1
	m_ShoulderAddon.ColorSet2	= 0;						// colorset2
	m_ShoulderAddon.bEffectColor = FALSE;					// effect color·Î º¸¿©Áö´Â ºÎÀ§ÀÎ°¡?
	m_ShoulderAddon.EffectColorSet	= 0;				// effectcolorset
}

MCreatureWear::~MCreatureWear()
{
}

//----------------------------------------------------------------------
//
//  member functions
//
//----------------------------------------------------------------------
//----------------------------------------------------------------------
// Clear AddonInfo
//----------------------------------------------------------------------
void			
MCreatureWear::ClearAddonInfo(int Addon)
{
	if(IsAdvancementClass() && Addon == ADDON_MAX)
	{
		ADDON_INFO& addon = m_ShoulderAddon;

		// ÃÊ±âÈ­
		addon.bAddon	= FALSE;			// Âø¿ëÇß³ª?	
		addon.FrameID	= FRAMEID_NULL;		// º¹Àå

		addon.ItemClass	= ITEM_CLASS_NULL;	// item class
		addon.ItemType	= ITEMTYPE_NULL;			// item type
		addon.ColorSet1	= 0;						// colorset1
		addon.ColorSet2	= 0;						// colorset2
		addon.bEffectColor = FALSE;					// effect color·Î º¸¿©Áö´Â ºÎÀ§ÀÎ°¡?
		addon.EffectColorSet	= 0;				// effectcolorset

	}
	else
	{
		ADDON_INFO& addon = m_Addon[Addon];

		// ÃÊ±âÈ­
		addon.bAddon	= FALSE;			// Âø¿ëÇß³ª?	
		addon.FrameID	= FRAMEID_NULL;		// º¹Àå

		addon.ItemClass	= ITEM_CLASS_NULL;	// item class
		addon.ItemType	= ITEMTYPE_NULL;			// item type
		addon.ColorSet1	= 0;						// colorset1
		addon.ColorSet2	= 0;						// colorset2
		addon.bEffectColor = FALSE;					// effect color·Î º¸¿©Áö´Â ºÎÀ§ÀÎ°¡?
		addon.EffectColorSet	= 0;				// effectcolorset
	}
}

//----------------------------------------------------------------------
// Set Same Wear
//----------------------------------------------------------------------
void				
MCreatureWear::SetSameWear(const MCreatureWear* pCreature)
{
	// º¹ÀåÀÇ Á¤º¸	
	for (int i=0; i<ADDON_MAX; i++)
	{
		m_Addon[i] = pCreature->m_Addon[i];
	}

	m_HairFrameID = pCreature->m_HairFrameID;
	m_HairColorSet = pCreature->m_HairColorSet;
}

//----------------------------------------------------------------------
// Set Addon ColorSet1
//----------------------------------------------------------------------
void			
MCreatureWear::SetAddonColorSet1(int Addon, WORD colorSet)	
{ 
	if (Addon >= ADDON_MAX)
	{
		return;
	}
	
	// 2004, 5, 4 sobeit add start - ´Ù¸¥ Ä³¸¯ÀÇ ¾Æ¿ì½ºÅÍÁî ºÎÃ÷´Â ¼¼ÆÃÇÏ´Â ÄÚµå°¡ ¾ø¾î¼­ °£´ÜÈ÷ Ãß°¡
	if(Addon == ADDON_TROUSER)
		m_Addon[Addon].bAddon = true;
	// 2004, 5, 4 sobeit add end

	if (colorSet < MAX_COLORSET || colorSet == UNIQUE_ITEM_COLOR || colorSet == QUEST_ITEM_COLOR)
	{	
		m_Addon[Addon].ColorSet1 = colorSet; 		
	}
	else
	{
		DEBUG_ADD_FORMAT("[Error] Exceed Maximum ColorSet. addon=%d, set=%d", Addon, colorSet);		
	}
}

//----------------------------------------------------------------------
// Set Addon ColorSet2
//----------------------------------------------------------------------
void			
MCreatureWear::SetAddonColorSet2(int Addon, WORD colorSet)	
{ 
	if (Addon >= ADDON_MAX)
	{
		return;
	}

	// 2004, 5, 4 sobeit add start - ´Ù¸¥ Ä³¸¯ÀÇ ¾Æ¿ì½ºÅÍÁî ºÎÃ÷´Â ¼¼ÆÃÇÏ´Â ÄÚµå°¡ ¾ø¾î¼­ °£´ÜÈ÷ Ãß°¡
	if(Addon == ADDON_TROUSER)
		m_Addon[Addon].bAddon = true;
	// 2004, 5, 4 sobeit add end
	
	if (colorSet < MAX_COLORSET || colorSet == UNIQUE_ITEM_COLOR || colorSet == QUEST_ITEM_COLOR)
	{	
		// ¿î¿µÀÚ´Â set1ÀÌ´Ù. T_T;;
		if (m_CreatureType==CREATURETYPE_SLAYER_OPERATOR
			&& Addon==ADDON_COAT)
		{
			m_ColorBody1 = m_ColorBody2 = colorSet;
		}
		
		m_Addon[Addon].ColorSet2 = colorSet; 		
	}
	else
	{
		DEBUG_ADD_FORMAT("[Error] Exceed Maximum ColorSet. addon=%d, set=%d", Addon, colorSet);
	}
}

//----------------------------------------------------------------------
// New Item From AddonInfo
//----------------------------------------------------------------------
// Addon¹øÂ° Á¤º¸·Î ItemÀ» »ý¼ºÇÑ´Ù.
// ¿ÜºÎ¿¡¼­ deleteÇØÁà¾ß ÇÑ´Ù.
//----------------------------------------------------------------------
MItem*
MCreatureWear::NewItemFromAddonInfo(int Addon)
{
	if(IsAdvancementClass() && Addon == ADDON_MAX)
	{
		ADDON_INFO& addon = m_ShoulderAddon;

		//--------------------------------------------------
		// itemÀ» Âø¿ëÇÑ °æ¿ì
		//--------------------------------------------------
		if (!addon.bAddon || addon.ItemClass==ITEM_CLASS_NULL)
		{
			return NULL;
		}
		
		//--------------------------------------------------
		// itemÀÇ Á¤º¸¸¦ ¾Ë±âÀ§ÇØ¼­ »ý¼ºÇØ¼­ Á¦°ÅÇÑ´Ù.
		//--------------------------------------------------
		MItem* pItem = MItem::NewItem( addon.ItemClass );
		pItem->SetItemType( addon.ItemType );

		return pItem;
	}
	else
	{
		if (Addon >= ADDON_MAX)
		{
			return false;
		}

		ADDON_INFO& addon = m_Addon[Addon];

		//--------------------------------------------------
		// itemÀ» Âø¿ëÇÑ °æ¿ì
		//--------------------------------------------------
		if (!addon.bAddon || addon.ItemClass==ITEM_CLASS_NULL)
		{
			return NULL;
		}
		
		//--------------------------------------------------
		// itemÀÇ Á¤º¸¸¦ ¾Ë±âÀ§ÇØ¼­ »ý¼ºÇØ¼­ Á¦°ÅÇÑ´Ù.
		//--------------------------------------------------
		MItem* pItem = MItem::NewItem( addon.ItemClass );
		pItem->SetItemType( addon.ItemType );

		return pItem;
	}
	return NULL;
}

//----------------------------------------------------------------------
// Remove Addon
//----------------------------------------------------------------------
// AddonÀÇ À§Ä¡ÀÇ º¹ÀåÀ» ¾ø¾Ø´Ù.
//----------------------------------------------------------------------
bool		
MCreatureWear::RemoveAddon(int Addon)
{ 
	DEBUG_ADD("MCreatureWear::RemoveAddon");
	
	// shoulder
	if(IsAdvancementClass() && Addon == ADDON_MAX)
	{
		ADDON_INFO& addon = m_ShoulderAddon;

		//--------------------------------------------------
		// ÀåÂøÇÑ°Ô ÀÖÀ» °æ¿ì¿¡¸¸ ¹þ±ä´Ù. - -;
		//--------------------------------------------------
		if (addon.bAddon)
		{
			MItem* pItem = NewItemFromAddonInfo( Addon );
			
			if (pItem!=NULL)
			{
				//--------------------------------------------------
				// addon ItemÀ» º¹Àå¿¡¼­ Á¦°ÅÇÑ´Ù.
				//--------------------------------------------------
				bool bRemove = RemoveAddonItem( pItem );

				delete pItem;

				return bRemove;
			}

			//--------------------------------------------------
			// Á¤º¸ Á¦°Å..
			//--------------------------------------------------
			ClearAddonInfo( Addon );

			return true;
		}
	}
	else
	{

		if (Addon >= ADDON_MAX)
		{
			return false;
		}

		ADDON_INFO& addon = m_Addon[Addon];

		//--------------------------------------------------
		// ÀåÂøÇÑ°Ô ÀÖÀ» °æ¿ì¿¡¸¸ ¹þ±ä´Ù. - -;
		//--------------------------------------------------
		if (addon.bAddon)
		{
			MItem* pItem = NewItemFromAddonInfo( Addon );
			
			if (pItem!=NULL)
			{
				//--------------------------------------------------
				// addon ItemÀ» º¹Àå¿¡¼­ Á¦°ÅÇÑ´Ù.
				//--------------------------------------------------
				bool bRemove = RemoveAddonItem( pItem );

				delete pItem;
				pItem = NULL;

				return bRemove;
			}

			//--------------------------------------------------
			// Á¤º¸ Á¦°Å..
			//--------------------------------------------------
			ClearAddonInfo( Addon );

			return true;
		}
	}
	return false;
}

//---------------------------------------------------------------------------
// Set AddonItem
//---------------------------------------------------------------------------
// ¸Ó¸®Ä«¶ôÀ» ¼³Á¤ÇÑ´Ù.
//---------------------------------------------------------------------------
void			
MCreatureWear::SetAddonHair(TYPE_FRAMEID id, WORD cs1)
{
	ADDON_INFO& addon = m_Addon[ADDON_HAIR];

	// ÃÊ±âÈ­
	addon.bAddon	= TRUE;			// Âø¿ëÇß³ª?	
	addon.FrameID	= id;		// º¹Àå

	addon.ItemClass	= ITEM_CLASS_NULL;	// item class

	addon.ItemType	= ITEMTYPE_NULL;			// item type
	addon.ColorSet1	= cs1;						// colorset1
	addon.ColorSet2	= 0;						// colorset2
	addon.bEffectColor = FALSE;
	addon.EffectColorSet = 0;

	// ÀúÀåÇØ µÐ´Ù.
	m_HairFrameID = id;
	m_HairColorSet = cs1;
}

//---------------------------------------------------------------------------
// Set AddonItem
//---------------------------------------------------------------------------
// ÀåÂøÇØ¼­ ¸ð¾çÀÌ ¹Ù²î´Â item(AddonItem)ÀÎ °æ¿ì
// Creature¿¡ ÀåÂøÇÏ°í »óÅÂ¸¦ ¹Ù²Û´Ù.
//---------------------------------------------------------------------------
bool
MCreatureWear::SetAddonItem(MItem* pItem)
{
	DEBUG_ADD("MCreatureWear::SetAddonItem");
	
	if (pItem==NULL)
	{
		DEBUG_ADD("The Item is NULL");
		
		return false;
	}

	//-------------------------------------------------
	//
	// Á¤ÁöÇÑ »óÅÂÀÎ °æ¿ì¸¸ º¹ÀåÀ» ¹Ù²Ü ¼ö ÀÖ´Ù.
	//
	//-------------------------------------------------
	// player°¡ ¾Æ´Ñ °æ¿ì³ª..
	// ¿ÀÅä¹ÙÀÌ¸¦ Å¸´Â °æ¿ì´Â..
	// ±×³É Á¤ÁöÇÏ°Ô ÇØ ¹ö¸°´Ù. - -;
	if (GetClassType()!=MCreature::CLASS_PLAYER
		|| pItem->GetItemClass()==ITEM_CLASS_MOTORCYCLE)
	{
		SetAction( (m_MoveAction==ACTION_SLAYER_MOTOR_MOVE)? ACTION_SLAYER_MOTOR_STAND : ACTION_STAND );
	}

#if __CONTENTS(__GEAR_SWAP_CHANGE)	// MCreatureWear::SetAddonItem ÀåÂøÃ¢ ±³Ã¼ Á¶°Ç
	
	bool	bItemActive	= true;
/*	DWORD	dwGetGearID	= 0;
	switch(g_pPlayer->GetRace())
	{
	case RACE_SLAYER:
		dwGetGearID	= g_pSlayerGear->GetSendGearID();
		break;

	case RACE_VAMPIRE:
		dwGetGearID	= g_pVampireGear->GetSendGearID();
		break;
		
	case RACE_OUSTERS:
		dwGetGearID	= g_pOustersGear->GetSendGearID();
		break;
	}
*/

	if(pItem->IsQuestItem() || pItem->IsAffectStatus())
		bItemActive	= true;
	else
		bItemActive	= false;

	if ((m_Action==ACTION_STAND 
		|| m_Action	== ACTION_MOVE
		|| IsSlayer() && m_Action==ACTION_SLAYER_MOTOR_STAND
		|| IsOusters() && m_Action==ACTION_OUSTERS_FAST_MOVE_STAND
#if __CONTENTS(__FAST_TRANSFORTER)
		|| IsOusters() && m_Action==ACTION_OUSTERS_WING_STAND
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
		|| IsOusters() && m_Action==ACTION_OUSTERS_UNICORN_STAND
#endif //__SECOND_TRANSFORTER
		)
		&& bItemActive)
#else
	if (m_Action==ACTION_STAND 
		|| IsSlayer() && m_Action==ACTION_SLAYER_MOTOR_STAND
		|| IsOusters() && m_Action==ACTION_OUSTERS_FAST_MOVE_STAND 
#if __CONTENTS(__FAST_TRANSFORTER)
		|| IsOusters() && m_Action==ACTION_OUSTERS_WING_STAND
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
		|| IsOusters() && m_Action==ACTION_OUSTERS_UNICORN_STAND
#endif //__SECOND_TRANSFORTER
		)
#endif	//__GEAR_SWAP_CHANGE
	{
		//-------------------------------------------------
		// ÀåÂøÇØ¼­ ¸ð¾çÀÌ ¹Ù²î´Â ItemÀÎ °æ¿ì¿¡¸¸ Ã³¸®ÇÑ´Ù.
		//-------------------------------------------------

		if(pItem->IsAddonItem() && (pItem->IsAffectStatus() || 
			(pItem->GetItemClass() == ITEM_CLASS_COAT &&
			pItem->GetItemType() >=32 &&
			pItem->GetItemType() <=35)))	//by viva
		{
			TYPE_FRAMEID	fid;
			ADDON			Addon = pItem->GetAddonSlot();

			//-------------------------------------------------
			// º¹ÀåÀÌ ¹Ù²î´Â À§Ä¡°¡ ÀÖ´Â °æ¿ì
			//-------------------------------------------------
			if (pItem->GetAddonSlot()==ADDON_NULL)
			{	
				// 2005, 1, 19, sobeit add start - ½½·¹ÀÌ¾î ¼ñ´õ ¾Æ¸Ó Ã³¸®
				if(pItem->GetItemClass() == ITEM_CLASS_SHOULDER_ARMOR)
					{
					if (IsMale())
					{
						fid = pItem->GetAddonMaleFrameID();
					}			
					else //if (pCreature->IsFemale())
					{
						fid = pItem->GetAddonFemaleFrameID();			
					}
					m_ShoulderAddon.bAddon = TRUE;
					m_ShoulderAddon.FrameID	= fid;		// º¹Àå

					m_ShoulderAddon.ItemClass	= ITEM_CLASS_SHOULDER_ARMOR;	// item class
					m_ShoulderAddon.ItemType	= pItem->GetItemType();			// item type
					m_ShoulderAddon.ColorSet1	= pItem->GetItemOptionColorSet();	// option
					m_ShoulderAddon.ColorSet2	= pItem->GetItemOptionColorSet();//pItem->GetItemColorSet();			// null
					m_ShoulderAddon.bEffectColor = FALSE;
					m_ShoulderAddon.EffectColorSet = 0;
				}
				// 2005, 1, 19, sobeit add end
				else
					DEBUG_ADD_FORMAT("[Error] Item doesn't have Addon Slot. id=%d, class=%d, type=%d", 
														pItem->GetID(), (int)pItem->GetItemClass(), (int)pItem->GetItemType());
				
			}
			else
			{	
				//-------------------------------------------------
				//
				//			ÀåÂøÇÏ´Â À§Ä¡¿¡ µû¶ó¼­ Ã³¸®..
				//
				//-------------------------------------------------
				switch (Addon)
				{
					//-------------------------------------------------
					// ¿ÀÅä¹ÙÀÌ¸¦ ÀåÂøÇÑ °æ¿ì
					//-------------------------------------------------
					case ADDON_MOTOR :
						//------------------------------------------
						// ¿òÁ÷ÀÌ´Â ¹æ¹ý ¹Ù²Þ
						//------------------------------------------					
						SetMoveDevice( MCreature::MOVE_DEVICE_RIDE );
					break;

					//-------------------------------------------------
					// ÀåÂøÇÒ·Á´Â°Ô ¿Þ¼Õ¹«±â?ÀÎ °æ¿ì
					//-------------------------------------------------
					case ADDON_LEFTHAND :
					{
						// ¹æÆÐ¹Û¿¡ ¾ø´Ù. - -;
						// ÇÊ»ì ÇÏµåÄÚµù.. - -;;;;

						//-------------------------------------------------
						// ±âÁ¸¿¡ ÀÖ´ø ¿À¸¥¼Õ¹«±â°¡ ¾ç¼Õ¹«±âÀÌ¸é 
						// ¿À¸¥¼ÕAddonÀ» Á¦°ÅÇÑ´Ù.
						//-------------------------------------------------
						MItem* pOldItem = NewItemFromAddonInfo( ADDON_RIGHTHAND );

						// ¿À¸¥¼Õ itemÀÌ ÀÖ´Â °æ¿ì Á¦°ÅÇÑ´Ù.
						if (pOldItem!=NULL)
						{	
							if (pOldItem->IsGearSlotTwoHand())
							{
								RemoveAddon( ADDON_RIGHTHAND );
							}

							delete pOldItem;
						}
					}
					break;

					//-------------------------------------------------
					// ÀåÂøÇÒ·Á´Â°Ô ¿À¸¥¼Õ¹«±â?ÀÎ °æ¿ì
					//-------------------------------------------------
					case ADDON_RIGHTHAND :
					{
						// ¾ç¼Õ¹«±âÀÌ¸é ¿Þ¼ÕÀ» ¾ø¾Ø´Ù.
						if (pItem->IsGearSlotTwoHand())
						{
							RemoveAddon( ADDON_LEFTHAND );
						}				
					}	
					break;

					//-------------------------------------------------
					// ¸ðÀÚ
					//-------------------------------------------------
					// ¸ðÀÚÀÎ °æ¿ì´Â
					// ÂªÀº ¸Ó¸®Ä«¶ôÀÌ¶ó¸é ¾ø¾Ø´Ù.
					// ÂªÀº ¸Ó¸® : ¿©12, ³²12
					// ±×·¯³ª 1¹ø ¸ðÀÚ´Â Çìµå¼Â ÇüÅÂ±â ¶§¹®¿¡
					// ¸Ó¸®Ä«¶ôÀ» ¹Ýµå½Ã Ãâ·ÂÇØ¾ßÇÔ
					//-------------------------------------------------
					case ADDON_HELM :
						if(pItem->GetAddonMaleFrameID() != ADDONID_HELM1)
						{
							if(IsMale() && m_HairFrameID != ADDONID_HAIR3 ||
							   IsFemale() && m_HairFrameID != ADDONID_HAIR1)
							{
								if(!IsAdvancementClass())
									RemoveAddon( ADDON_HAIR );
							}
						}
						else
						{
							SetAddonHair(m_HairFrameID, m_HairColorSet);
						}
					break;

					//-------------------------------------------------
					// ¿î¿µÀÚÀÎ °æ¿ì.. ¿Ê ¹Ù²Ù¸é ¸ö »ö±ò ¹Ù²ï´Ù.
					//-------------------------------------------------
					case ADDON_COAT :
						if (m_CreatureType==CREATURETYPE_SLAYER_OPERATOR
							|| m_CreatureType==CREATURETYPE_VAMPIRE_OPERATOR
							|| m_CreatureType==CREATURETYPE_OUSTERS_OPERATOR)
						{
//							if(pItem->IsUniqueItem())
//								m_ColorBody1 = m_ColorBody2 = UNIQUE_ITEM_COLOR;
//							else
								m_ColorBody1 = m_ColorBody2 = pItem->GetItemOptionColorSet();
						}
					break;
				}
					
				//-------------------------------------------------
				//
				//			¼ºº°¿¡ µû¸¥ FrameID
				//
				//-------------------------------------------------	
				if (IsMale())
				{
					fid = pItem->GetAddonMaleFrameID();
				}			
				else //if (pCreature->IsFemale())
				{
					fid = pItem->GetAddonFemaleFrameID();			
				}
			
				//-------------------------------------------------	
				// SlayerÀÌ¸é¼­ fid°¡ ¾ø´Â °æ¿ì..
				//-------------------------------------------------					
				if (fid == FRAMEID_NULL && IsSlayer())
				{					
					DEBUG_ADD_FORMAT("[Error] Item doesn't have FrameID. id=%d, class=%d, type=%d", 
										pItem->GetID(), (int)pItem->GetItemClass(), (int)pItem->GetItemType());					
				}
				//-------------------------------------------------					
				// Á¤»óÀûÀÌ°Å³ª.. VampireÀÎ °æ¿ì
				//-------------------------------------------------					
				else
				{	
					// 2005, 1, 19, sobeit add start - ½½·¹ÀÌ¾î ¼ñ´õ ¾Æ¸Ó Ã³¸®
//					if(pItem->GetItemClass() == ITEM_CLASS_SHOULDER_ARMOR)
//					{
//						m_ShoulderAddon.bAddon = TRUE;
//						m_ShoulderAddon.FrameID	= fid;		// º¹Àå
//
//						m_ShoulderAddon.ItemClass	= ITEM_CLASS_SHOULDER_ARMOR;	// item class
//						m_ShoulderAddon.ItemType	= pItem->GetItemType();			// item type
//						m_ShoulderAddon.ColorSet1	= pItem->GetItemOptionColorSet();	// option
//						m_ShoulderAddon.ColorSet2	= pItem->GetItemOptionColorSet();//pItem->GetItemColorSet();			// null
//						m_ShoulderAddon.bEffectColor = FALSE;
//						m_ShoulderAddon.EffectColorSet = 0;
//					}
					// 2005, 1, 19, sobeit add end
//					else
					{
						//-------------------------------------------------
						// ÀåÂøÇÑ´Ù.
						//-------------------------------------------------
						ADDON_INFO& addon = m_Addon[Addon];

						// ÃÊ±âÈ­
						addon.bAddon	= TRUE;
						addon.FrameID	= fid;

						addon.ItemClass	= pItem->GetItemClass();
						addon.ItemType	= pItem->GetItemType();

						// ¹ìÆÄ ¿ÊÃß°¡
						if(pItem->GetItemClass() == ITEM_CLASS_VAMPIRE_COAT)
						{
							unsigned short nSpecialActionInfo = GetSpecialActionInfo();

							if(m_CreatureType != CREATURETYPE_VAMPIRE_OPERATOR)
							{
								//if (m_CreatureType != CREATURETYPE_WOLF && m_CreatureType != CREATURETYPE_BAT )
								if (m_CreatureType != CREATURETYPE_WOLF && m_CreatureType != CREATURETYPE_BAT  && m_CreatureType != CREATURETYPE_VAMPIRE_GHOST
#if __CONTENTS(__FAST_TRANSFORTER)
								&& m_CreatureType != CREATURETYPE_FLITTERMOUSE
								&& m_CreatureType != CREATURETYPE_NEDE
								&& m_CreatureType != CREATURETYPE_KLTL
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
								&& m_CreatureType != CREATURETYPE_SHAPE_OF_DEMON
#endif //__SECOND_TRANSFORTER
									)
								{
									if( m_CreatureType == CREATURETYPE_WER_WOLF )//±äÀÇºóÑÕÉ«
									{
										SetCreatureType( CREATURETYPE_WER_WOLF );//±äÀÇºóÑÕÉ«
									}
									/*
									else
									{
										if (IsMale())
										{
											SetCreatureType(pItem->GetAddonMaleFrameID());
										}			
										else //if (pCreature->IsFemale())
										{
											SetCreatureType(pItem->GetAddonFemaleFrameID());
										}
									}
									*/
								}
	
								addon.ColorSet1			= m_ColorBody1;//defaultSkinColor;	// ÇÇºÎ
								addon.ColorSet2			= defaultCoatColor;

								addon.bEffectColor		= FALSE;
								addon.EffectColorSet	= 0;

								if(pItem->IsUniqueItem())
									m_ColorBody2 = UNIQUE_ITEM_COLOR;
								else
									m_ColorBody2	= pItem->GetItemOptionColorSet();			// option

								if( m_CreatureType == CREATURETYPE_WER_WOLF )//±äÀÇºóÑÕÉ«
									m_ColorBody1 = m_ColorBody2;
									
							}
							else
							{
								m_ColorBody1 = m_ColorBody2 = pItem->GetItemOptionColorSet();
							}

							SetSpecialActionInfo(nSpecialActionInfo);
						}

						else 
						if (Addon==ADDON_COAT || Addon==ADDON_TROUSER)
						{
							{
								
								// 2005, 2, 18, sobeit modify end
								//						if(pItem->IsUniqueItem())
								//							addon.ColorSet2	= UNIQUE_ITEM_COLOR;			// option
								//						else

								if(Addon == ADDON_COAT)
								{
									// 2005, 2, 18, sobeit modify start - ½ÂÁ÷ ½½·¹ÀÌ¾î ADDON_COATÀÇ ColorSet1Àº ¸Ó¸® »ö±òÀÌ´Ù.
									if(!IsAdvancementClass())
										addon.ColorSet1	= m_ColorBody1;//defaultSkinColor;	// ÇÇºÎ
									else
									{
										ADDON_INFO& HairAddon = m_Addon[ADDON_HAIR];
										addon.ColorSet1	= HairAddon.ColorSet1;						// colorset1
									}

									addon.ColorSet2	= pItem->GetItemOptionColorSet();
								}
								else
								{
									addon.ColorSet1	= pItem->GetItemOptionColorSet();
								}

								
								addon.bEffectColor = FALSE;
								addon.EffectColorSet = 0;
								
								// »óÀÇÀÎ °æ¿ì¸¸ ¿ÊÀÌ ¹Ù²ï´Ù.
								//if (Addon==ADDON_COAT)
								{
									//-------------------------------------------------
									// Vampire¸¸ Àû¿ëµÈ´Ù.
									//-------------------------------------------------
									if (m_CreatureType==CREATURETYPE_VAMPIRE_OPERATOR)
									{
										//								if(pItem->IsUniqueItem())
										//									m_ColorBody1 = m_ColorBody2 = UNIQUE_ITEM_COLOR;
										//								else
										m_ColorBody1 = m_ColorBody2 = pItem->GetItemOptionColorSet();
									}
									else
									{
										//								if(pItem->IsUniqueItem())
										//									m_ColorBody2 = UNIQUE_ITEM_COLOR;
										//								else
										m_ColorBody2 = pItem->GetItemOptionColorSet();
									}
								}
							}
						}
						else
						{
	//						if(pItem->IsUniqueItem())
	//						{
	//							addon.ColorSet1	= UNIQUE_ITEM_COLOR;	// option
	//							addon.ColorSet2	= UNIQUE_ITEM_COLOR;//pItem->GetItemColorSet();			// null
	//						}
	//						else
							{
								addon.ColorSet1	= pItem->GetItemOptionColorSet();	// option
								addon.ColorSet2	= pItem->GetItemOptionColorSet();//pItem->GetItemColorSet();			// null

#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
								//¸¸ÀÏ, ½½·¹ÀÌ¾îÀÇ ½Å±ÔÀÌµ¿¼ö´ÜÀÌ¶ó¸é..... 
								//4¿ù 30ÀÏ Å×¼· / 5¿ù 7ÀÏ º»¼· ÆÐÄ¡±îÁö´Â ÀÓÀÇ·Î Color°ªÀ» 0À¸·Î ¼¼ÆÃÇÑ´Ù.
								//ÃßÈÄ, ½Å±ÔÀÌµ¿¼ö´Ü¿¡ ´ëÇÑ Color Enchant±â´ÉÀÌ Ãß°¡µÉ ¶§.. (ÇöÀç)½½·¹ÀÌ¾î ¹ÙÀÌÅ©¿¡ ´ëÇØ¼­ ColorÃ³¸®°¡ ¹ÌÈíÇÑ ºÎºÐÀ» º¸¿ÏÇÏ°í, ±× ¶§´Â ÀÌ ºÎºÐÀÇ Ã³¸®¸¦ »©µµ·Ï ÇÏ³®.
								if (pItem->GetItemClass() == ITEM_CLASS_MOTORCYCLE)
								{
#if __CONTENTS(__FAST_TRANSFORTER)
									if(pItem->GetItemType () == 8)
									{
										addon.ColorSet1	= (WORD)379;
										addon.ColorSet2	= (WORD)379;
									}
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
									else if(pItem->GetItemType () == 9)
									{
										addon.ColorSet1	= (WORD)379;
										addon.ColorSet2	= (WORD)379;
									}
#endif //__SECOND_TRANSFORTER
								}
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
							}
							addon.bEffectColor = FALSE;
							addon.EffectColorSet = 0;
						}					
					}
				}				
			}
		}			
		else
		{
			DEBUG_ADD_FORMAT("[Error] Item is Not Addon Item. id=%d, class=%d, type=%d", 
									pItem->GetID(), (int)pItem->GetItemClass(), (int)pItem->GetItemType());			
		}

		//-------------------------------------------------
		// ÀåÂøÇÑ ItemÀÌ 
		// ±âº»°ø°Ý¿ë ¾ÆÀÌÅÛÀÌ¶ó¸é...
		// ±âº»°ø°ÝActionInfo°¡ ¹Ù²î¾î¾ß ÇÑ´Ù.
		//-------------------------------------------------
		if (pItem->IsBasicWeapon() && pItem->IsAffectStatus())
		{
			TYPE_ACTIONINFO ai = pItem->GetUseActionInfo();

			//-------------------------------------------------
			// ¼³Á¤µÈ actionInfo°¡ ¾ø´Â °æ¿ì
			//-------------------------------------------------
			if (ai==ACTIONINFO_NULL)
			{
				// ±âº» ¸Ç¼Õ °ø°Ý µ¿ÀÛÀ¸·Î ÀüÈ¯ÇÑ´Ù.
				SetBasicActionInfo( SKILL_ATTACK_MELEE );
				
				DEBUG_ADD("[Empty ActionInfo]This Creature's basic attack is Melee");				
			}
			//-------------------------------------------------
			// ¼³Á¤µÈ actionInfo°¡ ÀÖ´Ù¸é..
			//-------------------------------------------------
			else
			{
				// ±âº» °ø°Ý µ¿ÀÛÀ¸·Î ¼³Á¤ÇÑ´Ù.
				SetBasicActionInfo( ai );
				
				DEBUG_ADD_FORMAT("[Set BasicActionInfo] %d", ai);
			}
		}

		//-------------------------------------------------
		// ¿À¸¥¼ÕÀÌ ºñ¾îÀÖÀ¸¸é..
		// °ø°ÝÀº ¸Ç¼ÕÀÌ¶ó°í º¸¸é µÈ´Ù..
		// ÇÏµå ÄÚµù.. - -;;
		//-------------------------------------------------
		if (!m_Addon[ADDON_RIGHTHAND].bAddon)
		{
			DEBUG_ADD("[Empty RightHand]This Creature's basic attack is Melee");
			
			// ±âº» ¸Ç¼Õ °ø°Ý µ¿ÀÛÀ¸·Î ÀüÈ¯ÇÑ´Ù.
			SetBasicActionInfo( SKILL_ATTACK_MELEE );			
		}

		return true;	
		
	}

	//-------------------------------------------------
	//
	// Á¤ÁöÇÑ »óÅÂ°¡ ¾Æ´Ñ °æ¿ì
	//
	//-------------------------------------------------
	DEBUG_ADD_FORMAT("[Error] Not STAND action. id=%d, action=%d", m_ID, m_Action);
	
	// ´ÙÀ½¿¡ Á¤ÁöÇÒ ¶§, º¹ÀåÀ» ¹Ù²Ùµµ·Ï ÇÑ´Ù..
	// ±×·¡¾ß µÇ´Âµ¥.. ±ÍÂú´Ù. - -;;

	return false;	
}

//---------------------------------------------------------------------------
// Remove AddonItem
//---------------------------------------------------------------------------
// AddonItemÀ» ÀåÂøÇØÁ¦ ÇÑ´Ù.
//---------------------------------------------------------------------------
bool
MCreatureWear::RemoveAddonItem( MItem* pItem )
{
	DEBUG_ADD("MCreatureWear::RemoveAddonItem");
	
	if (pItem==NULL)
	{
		DEBUG_ADD("The Item is NULL");
		
		return false;
	}

	//-------------------------------------------------
	//
	// Á¤ÁöÇÑ »óÅÂÀÎ °æ¿ì¸¸ º¹ÀåÀ» ¹Ù²Ü ¼ö ÀÖ´Ù.
	//
	//-------------------------------------------------
	// player°¡ ¾Æ´Ñ °æ¿ì³ª..
	// ¿ÀÅä¹ÙÀÌ¸¦ Å¸´Â °æ¿ì´Â..
	// ±×³É Á¤ÁöÇÏ°Ô ÇØ ¹ö¸°´Ù. - -;
	if (GetClassType()!=MCreature::CLASS_PLAYER
		|| pItem->GetItemClass()==ITEM_CLASS_MOTORCYCLE)
	{
		SetAction( (m_MoveAction==ACTION_SLAYER_MOTOR_MOVE)? ACTION_SLAYER_MOTOR_STAND : ACTION_STAND );
	}

#if __CONTENTS(__GEAR_SWAP_CHANGE)	//MCreatureWear::RemoveAddonItem ÀåÂøÃ¢ ÇØÁ¦ Á¶°Ç
	if (m_Action==ACTION_STAND
		|| m_Action==ACTION_MOVE
		|| IsSlayer() && m_Action==ACTION_SLAYER_MOTOR_STAND
		|| IsOusters() && m_Action==ACTION_OUSTERS_FAST_MOVE_STAND
#if __CONTENTS(__FAST_TRANSFORTER)
		|| IsOusters() && m_Action==ACTION_OUSTERS_WING_STAND
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
		|| IsOusters() && m_Action==ACTION_OUSTERS_UNICORN_STAND
#endif //__SECOND_TRANSFORTER
		)
#else
	if (m_Action==ACTION_STAND
		|| IsSlayer() && m_Action==ACTION_SLAYER_MOTOR_STAND
		|| IsOusters() && m_Action==ACTION_OUSTERS_FAST_MOVE_STAND 
#if __CONTENTS(__FAST_TRANSFORTER)
		|| IsOusters() && m_Action==ACTION_OUSTERS_WING_STAND
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
		|| IsOusters() && m_Action==ACTION_OUSTERS_UNICORN_STAND
#endif //__SECOND_TRANSFORTER
		)
#endif	// __GEAR_SWAP_CHANGE

	{
		// ¹ìÆÄ ¿ÊÃß°¡
		if(pItem->GetItemClass() == ITEM_CLASS_VAMPIRE_COAT)
		{
			if(m_CreatureType != CREATURETYPE_VAMPIRE_OPERATOR)
			{
				//if (m_CreatureType != CREATURETYPE_WOLF && m_CreatureType != CREATURETYPE_BAT )
				if (m_CreatureType != CREATURETYPE_WOLF && m_CreatureType != CREATURETYPE_BAT && m_CreatureType != CREATURETYPE_VAMPIRE_GHOST
#if __CONTENTS(__FAST_TRANSFORTER)
								&& m_CreatureType != CREATURETYPE_FLITTERMOUSE
								&& m_CreatureType != CREATURETYPE_NEDE
								&& m_CreatureType != CREATURETYPE_KLTL
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
								&& m_CreatureType != CREATURETYPE_SHAPE_OF_DEMON
#endif //__SECOND_TRANSFORTER
					)
				{
					if( m_CreatureType == CREATURETYPE_WER_WOLF )//±äÀÇºóÑÕÉ«
					{
						SetCreatureType( CREATURETYPE_WER_WOLF );
						m_ColorBody1 = defaultCoatColor;
					}
					/*
					else
					{
						if (IsMale())	// ¾Æ¾¾ ÇÏµå ÄÚµù ÇÏ¸é ¾È´ë´Âµ¥-¤µ-
						{
							SetCreatureType(2);
						}			
						else //if (pCreature->IsFemale())
						{
							SetCreatureType(3);
						}
					}
					*/
				}
				//						addon.ColorSet1	= m_ColorBody1;//defaultSkinColor;	// ÇÇºÎ

				m_ColorBody2	= defaultCoatColor;
			}
			else
			{
				m_ColorBody1	= m_ColorBody2	= defaultCoatColor;
			}
		}

		//-------------------------------------------------
		// Âø¿ëÇØ¼­ ¸ð¾çÀÌ ¹Ù²î´Â ItemÀÎ°¡?
		//-------------------------------------------------
		// --> ÀåÂø ºÎÀ§¸¦ ¾Ë¾Æ³»¼­ 
		//    ±× ºÎÀ§ÀÇ AddonÀ» ¾ø¾Ö¾ß ÇÑ´Ù.
		//-------------------------------------------------
//		else
		if (pItem->IsAddonItem())
		{						
			enum ADDON add = pItem->GetAddonSlot();

			//-------------------------------------------------
			// ÀåÂø ºÎÀ§ÀÇ AddonÀ» ¾ø¾Ø´Ù.
			//-------------------------------------------------
			if (add == ADDON_NULL)
			{
				// 2005, 1, 19, sobeit add start - ½½·¹ÀÌ¾î ¼ñ´õ ¾Æ¸Ó Ã³¸®
				if(pItem->GetItemClass() == ITEM_CLASS_SHOULDER_ARMOR)
				{
					m_ShoulderAddon.bAddon = FALSE;
					m_ShoulderAddon.FrameID	= FRAMEID_NULL;		// º¹Àå

					m_ShoulderAddon.ItemClass	= ITEM_CLASS_NULL;	// item class
					m_ShoulderAddon.ItemType	= ITEMTYPE_NULL;			// item type
					m_ShoulderAddon.ColorSet1	= 0;						// colorset1
					m_ShoulderAddon.ColorSet2	= 0;						// colorset2
					m_ShoulderAddon.bEffectColor = FALSE;					// effect color·Î º¸¿©Áö´Â ºÎÀ§ÀÎ°¡?
					m_ShoulderAddon.EffectColorSet	= 0;				// effectcolorset
				}
				// 2005, 1, 19, sobeit add end
				else
				DEBUG_ADD_FORMAT("[Error] Item doesn't have Addon Slot. id=%d, class=%d, type=%d", 
													pItem->GetID(), (int)pItem->GetItemClass(), (int)pItem->GetItemType());				
			}
			else
			{
				//--------------------------------------------------
				// Á¤º¸¸¦ Á¦°Å ÇÑ´Ù.
				//--------------------------------------------------
				ClearAddonInfo( add );

				//-------------------------------------------------
				//
				//			ÀåÂøÇÏ´Â ºÎÀ§¿¡ µû¶ó¼­
				//
				//-------------------------------------------------	
				switch (add)
				{
					//-------------------------------------------------
					// »óÀÇ : ¸Ç¸öÀÏ °æ¿ì¿¡´Â ±âº»¸öÀ¸·Î..
					//-------------------------------------------------
					case ADDON_COAT :
					{
						//MItem* pItem = MItem::NewItem( ITEM_CLASS_TROUSER );
						//pItem->SetItemType( 0 );

						//SetAddonItem( pItem );	

						//delete pItem;
						//-------------------------------------------------
						// ÀåÂøÇÑ´Ù.
						//-------------------------------------------------						
						ADDON_INFO& addon = m_Addon[ADDON_COAT];

						// ÃÊ±âÈ­
						addon.bAddon	= TRUE;

						if(GetRace() == RACE_OUSTERS)
						{
							addon.FrameID = 1;
							addon.ColorSet1 = defaultCoatColor;

							addon.ItemClass	= ITEM_CLASS_OUSTERS_COAT;
						}
						else if(GetRace() == RACE_VAMPIRE)
						{	
							//SetCreatureType(IsMale() ? 2 : 3);

							addon.FrameID	= IsMale() ? 2 : 3;
							addon.ColorSet1 = m_ColorBody1;

							addon.ItemClass	= ITEM_CLASS_VAMPIRE_COAT;
						}
						else
						{
							//addon.FrameID	= IsMale()? ADDONID_COAT0_MALE : ADDONID_COAT0_FEMALE;
							addon.FrameID	= ADDONID_COAT1;

							// 2005, 2, 18, sobeit modify start - ½ÂÁ÷ ½½·¹ÀÌ¾î ADDON_COATÀÇ ColorSet1Àº ¸Ó¸® »ö±òÀÌ´Ù.
							if(!IsAdvancementClass())
								addon.ColorSet1	= m_ColorBody1;//defaultSkinColor;	// ÇÇºÎ
							else
							{
								ADDON_INFO& HairAddon = m_Addon[ADDON_HAIR];
								addon.ColorSet1	= HairAddon.ColorSet1;						// colorset1
							}
							// 2005, 2, 18, sobeit modify end

							addon.ItemClass	= ITEM_CLASS_COAT;
						}

						addon.ItemType	= 0;
						addon.ColorSet2	= defaultCoatColor;
						addon.bEffectColor = FALSE;
						addon.EffectColorSet = 0;
						
						//-------------------------------------------------	
						// Vampire¸¸ Àû¿ëµÈ´Ù.
						// ¿î¿µÀÚµµ Àû¿ëµÇ°ÚÁö..
						//-------------------------------------------------													
						if (m_CreatureType==CREATURETYPE_VAMPIRE_OPERATOR
							|| m_CreatureType==CREATURETYPE_SLAYER_OPERATOR
							|| m_CreatureType==CREATURETYPE_OUSTERS_OPERATOR
							)
						{
							m_ColorBody1 = m_ColorBody2 = defaultSkinColor;	
						}
						else
						{
							m_ColorBody2 = defaultCoatColor;
						}
						
					}
					break;

					//-------------------------------------------------
					// ÇÏÀÇ : ¸Ç¸öÀÏ °æ¿ì¿¡´Â ±âº»¸öÀ¸·Î..
					//-------------------------------------------------
					case ADDON_TROUSER :
					{
						//MItem* pItem = MItem::NewItem( ITEM_CLASS_TROUSER );
						//pItem->SetItemType( 0 );

						//SetAddonItem( pItem );

						//delete pItem;
						//-------------------------------------------------
						// ÀåÂøÇÑ´Ù.
						//-------------------------------------------------
						ADDON_INFO& addon = m_Addon[ADDON_TROUSER];

						// ÃÊ±âÈ­
						addon.bAddon	= TRUE;
						//addon.FrameID	= IsMale()? ADDONID_TROUSER0_MALE : ADDONID_TROUSER0_FEMALE;
						addon.FrameID	= ADDONID_TROUSER1;

						addon.ItemClass	= ITEM_CLASS_TROUSER;
						addon.ItemType	= 0;
						addon.ColorSet1	= defaultTrouserColor;
						addon.ColorSet2	= m_ColorBody1;//defaultSkinColor;	// ±âº» ÇÇºÎ»ö
						addon.bEffectColor = FALSE;
						addon.EffectColorSet = 0;
					}
					break;

					//-------------------------------------------------
					// ¿À¸¥¼ÕÀº ¹«±â..ÀÌ¹Ç·Î..
					//-------------------------------------------------				
					case ADDON_RIGHTHAND :
						// ±âº» ¸Ç¼Õ °ø°Ý µ¿ÀÛÀ¸·Î ÀüÈ¯ÇÑ´Ù.
						SetBasicActionInfo( SKILL_ATTACK_MELEE );

						// Æ¯Á¤ ¹«±â¿¡¸¸ °É¸®´Â Effect
						switch (pItem->GetItemClass())
						{
							//-------------------------------------------------	
							// µµ
							//-------------------------------------------------	
							case ITEM_CLASS_BLADE :
								if (HasEffectStatus(EFFECTSTATUS_BERSERKER))
								{
									RemoveEffectStatus(EFFECTSTATUS_BERSERKER);
								}
							break;

							//-------------------------------------------------	
							// ½ÊÀÚ°¡
							//-------------------------------------------------	
							case ITEM_CLASS_CROSS :
							case ITEM_CLASS_MACE :
								if (HasEffectStatus(EFFECTSTATUS_HYPNOSIS))
								{
									RemoveEffectStatus(EFFECTSTATUS_HYPNOSIS);
								}
							break;
						}
					break;

					//-------------------------------------------------
					// ¿ÀÅä¹ÙÀÌ ÀåÂø ÇØÁ¦
					//-------------------------------------------------
					case ADDON_MOTOR :
						//------------------------------------------
						// ¿òÁ÷ÀÌ´Â ¹æ¹ý ¹Ù²Þ
						//------------------------------------------					
						SetMoveDevice( MCreature::MOVE_DEVICE_WALK );
					break;

					//-------------------------------------------------
					// ¸ðÀÚ
					//-------------------------------------------------
					// ¸ðÀÚ¸¦ Á¦°ÅÇÑ °æ¿ì´Â 
					// ¸Ó¸®Ä«¶ôÀ» ´Ù½Ã ºÙ¿©ÁØ´Ù.
					//-------------------------------------------------
					case ADDON_HELM :
						SetAddonHair( m_HairFrameID, m_HairColorSet );
					break;
				}
				
			}

			return true;
		}

		// addon itemÀÌ ¾Æ´Ñ °æ¿ì
		return true;
	}

	//-------------------------------------------------
	//
	// Á¤ÁöÇÑ »óÅÂ°¡ ¾Æ´Ñ °æ¿ì
	//
	//-------------------------------------------------
	DEBUG_ADD_FORMAT("[Error] Not STAND action. id=%d, action=%d", m_ID, m_Action);
	
	// ´ÙÀ½¿¡ Á¤ÁöÇÒ ¶§, º¹ÀåÀ» ¹Ù²Ùµµ·Ï ÇÑ´Ù..
	// ±×·¡¾ß µÇ´Âµ¥.. ±ÍÂú´Ù. - -;;


	return false;
}

//---------------------------------------------------------------------------
// Set Creature Type
//---------------------------------------------------------------------------
// ±âº» º¹ÀåÀ» ÀÔÈù´Ù.
//---------------------------------------------------------------------------
void
MCreatureWear::SetCreatureType(TYPE_CREATURETYPE type)
{
	//-------------------------------------------------
	// type¼³Á¤
	//-------------------------------------------------
	MCreature::SetCreatureType( type );

	//-------------------------------------------------
	// ´Ù ¹þ±ä´Ù.
	//-------------------------------------------------
	for (int i=0; i<ADDON_MAX; i++)
	{
		ClearAddonInfo( i );
	}

	if(IsVampire())
	{
		//-------------------------------------------------
		// »óÀÇ : ¸Ç¸öÀÏ °æ¿ì¿¡´Â ±âº»¸öÀ¸·Î..
		//-------------------------------------------------
		ADDON_INFO& addon = m_Addon[ADDON_COAT];

		// ÃÊ±âÈ­
		addon.bAddon	= TRUE;

		// ¿ÊÀÌ ¾ø´Ù¸é Vampire 1Â÷ÀÇ»óÀ¸·Î ¼¼ÆÃ
		if(type == FRAMEID_NULL)
		{
			addon.FrameID	= IsMale()? 2 : 3;
		}
		else
		{
			addon.FrameID	= type;
		}
		
		addon.ItemClass	= ITEM_CLASS_VAMPIRE_COAT;
		addon.ItemType	= 0;
		addon.ColorSet1	= m_ColorBody1;//defaultSkinColor;	// ±âº» ÇÇºÎ»ö
		addon.ColorSet2	= defaultCoatColor;	
		addon.bEffectColor = FALSE;
		addon.EffectColorSet = 0;
	}
	else
	if(IsOusters())
	{
		//-------------------------------------------------
		// »óÀÇ : ¸Ç¸öÀÏ °æ¿ì¿¡´Â ±âº»¸öÀ¸·Î..
		//-------------------------------------------------
		ADDON_INFO& addon = m_Addon[ADDON_COAT];
		
		// ÃÊ±âÈ­
		addon.bAddon	= TRUE;
		addon.FrameID	= 1;
		//		addon.FrameID	= IsMale()? ADDONID_COAT0_MALE : ADDONID_COAT0_FEMALE;
		
		addon.ItemClass	= ITEM_CLASS_OUSTERS_COAT;
		addon.ItemType	= 0;
		addon.ColorSet1	= m_ColorBody1;//defaultSkinColor;	// ±âº» ÇÇºÎ»ö
		addon.ColorSet2	= defaultCoatColor;	
		addon.bEffectColor = FALSE;
		addon.EffectColorSet = 0;
	}
	else
	{
		//-------------------------------------------------
		// »óÀÇ : ¸Ç¸öÀÏ °æ¿ì¿¡´Â ±âº»¸öÀ¸·Î..
		//-------------------------------------------------
		ADDON_INFO& addon = m_Addon[ADDON_COAT];

		// ÃÊ±âÈ­
		addon.bAddon	= TRUE;
		//addon.FrameID	= IsMale()? ADDONID_COAT0_MALE : ADDONID_COAT0_FEMALE;
		addon.FrameID	= ADDONID_COAT1;
		
		addon.ItemClass	= ITEM_CLASS_COAT;
		addon.ItemType	= 0;
		addon.ColorSet1	= m_ColorBody1;//defaultSkinColor;	// ±âº» ÇÇºÎ»ö
		addon.ColorSet2	= defaultCoatColor;	
		addon.bEffectColor = FALSE;
		addon.EffectColorSet = 0;
		
		//-------------------------------------------------
		// ÇÏÀÇ : ¸Ç¸öÀÏ °æ¿ì¿¡´Â ±âº»¸öÀ¸·Î..
		//-------------------------------------------------
		ADDON_INFO& addon2 = m_Addon[ADDON_TROUSER];
		
		// ÃÊ±âÈ­
		addon2.bAddon	= TRUE;
		//addon2.FrameID	= IsMale()? ADDONID_TROUSER0_MALE : ADDONID_TROUSER0_FEMALE;
		addon2.FrameID	= ADDONID_TROUSER1;
		
		addon2.ItemClass	= ITEM_CLASS_TROUSER;
		addon2.ItemType	= 0;
		addon2.ColorSet1	= defaultTrouserColor;
		addon2.ColorSet2	= m_ColorBody1;//defaultSkinColor;	// ±âº» ÇÇºÎ»ö
		addon2.bEffectColor = FALSE;
		addon2.EffectColorSet = 0;
	}
}

//----------------------------------------------------------------------
// Remove EffectStatus
//----------------------------------------------------------------------
// Æ¯Á¤ÇÑ EffectSpriteTypeÀ» Á¦°ÅÇÑ´Ù.
//----------------------------------------------------------------------
bool
MCreatureWear::RemoveEffectStatus(EFFECTSTATUS status)
{
	DEBUG_ADD_FORMAT("[RemoveEffectStatus] id=%d, status=%d", m_ID, (int)status);
	
	if (status>=g_pEffectStatusTable->GetSize())
	{
		DEBUG_ADD_FORMAT("[Error]EffectStatus exceed Max : %d", (int)status);
		
		return false;
	}

	if (!m_bEffectStatus[status])
	{
		return false;
	}

	m_bEffectStatus[status] = false;

	bool bUseEffectSprite = (*g_pEffectStatusTable)[status].bUseEffectSprite;

	TYPE_EFFECTSPRITETYPE type = (*g_pEffectStatusTable)[status].EffectSpriteType;
	//------------------------------------------------------------
	// effectStatus¿¡ µû¶ó¼­.
	//------------------------------------------------------------
	switch (status)
	{
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
			SetMoveDevice(MOVE_DEVICE_WALK);
			if(IsAdvancementClass())
			{
				type = Wisp_Sylph_Loopcolor_Kind(status);
				ExecuteActionInfoFromMainNode(MCreature::Wisp_Endcolor_Kind(status),GetX(), GetY(), 0,GetDirection(),	GetID(),	
					GetX(), GetY(), 0, 8, NULL, false);
			}
		break;
#if __CONTENTS(__FAST_TRANSFORTER)
		case EFFECTSTATUS_CLIENT_WING_SYLPH :
			{
				type = Seragon_Color_Kind(status);
				SetMoveDevice(MOVE_DEVICE_WALK);
			}
			break;
#endif //__FAST_TRANSFORTER
#if __CONTENTS(__SECOND_TRANSFORTER)
		case EFFECTSTATUS_CLIENT_UNICORN:
			{
				type = Unicorn_Color_Kind(status);
				SetMoveDevice(MOVE_DEVICE_WALK);
			}
			break;
		case EFFECTSTATUS_OusterWings_New_1:
			{
				RemoveAttachEffect(EFFECTSPRITETYPE_unknow_2326);
				RemoveAttachEffect(EFFECTSPRITETYPE_unknow_2327);
				SetMoveDevice(MOVE_DEVICE_WALK);//Ä§ÁéÐÂ×øÆï
			}
		case EFFECTSTATUS_OusterWings_New_2:
			{
				RemoveAttachEffect(EFFECTSPRITETYPE_unknow_2697);
				RemoveAttachEffect(EFFECTSPRITETYPE_unknow_2698);
				SetMoveDevice(MOVE_DEVICE_WALK);//Ä§ÁéÐÂ×øÆï
			}
#endif //__SECOND_TRANSFORTER

		case EFFECTSTATUS_BIKE_CRASH:
			SetMoveDevice(MOVE_DEVICE_WALK);
			break;
		//------------------------------------------------------------
		// ¸¶ºñ Ç®¸± ¶§
		//------------------------------------------------------------
		case EFFECTSTATUS_GUN_SHOT_GUIDANCE_AIM :
		case EFFECTSTATUS_SATELLITE_BOMB_AIM :
			if (m_bAlive)
			{
				SetStop();
				StopGunShotGuidance();
	#ifdef OUTPUT_DEBUG					
			DEBUG_ADD_FORMAT("[GSG] Stop");
	#endif
			}
		break;

		//------------------------------------------------------------
		// ¸¶ºñ Ç®¸± ¶§
		//------------------------------------------------------------
		case EFFECTSTATUS_CAUSE_CRITICAL_WOUNDS :
		case EFFECTSTATUS_EXPLOSION_WATER :
			if (m_bAlive)
			{
				SetStop();
				StopCauseCriticalWounds();
	#ifdef OUTPUT_DEBUG					
			DEBUG_ADD_FORMAT("[CCW] Stop");
	#endif
			}
		break;

		case EFFECTSTATUS_CURSE_PARALYSIS :
			if (m_bAlive)
			{
				SetStop();
				Remove_Curse_Paralsis_Effect();
			}
		break;

		//------------------------------------------------------------
		// EFFECTSTATUS_SUMMON_CASKET [»õ±â¼ú]
		//------------------------------------------------------------
		case EFFECTSTATUS_CASKET :
			// ¹Ù·Î invisible·Î ¸¸µç´Ù.
			RemoveCasket();
		break;

		//------------------------------------------------------------
		// invisible Á¦°Å
		//------------------------------------------------------------
		case EFFECTSTATUS_INVISIBILITY :
		case EFFECTSTATUS_SNIPPING_MODE :
		case EFFECTSTATUS_SNIPPING_MODE_2 :
			// invisibleÀ» Á¦°ÅÇÑ´Ù.
			SetVisible();
		break;

		//------------------------------------------------------------
		// EFFECTSTATUS_COMA
		//------------------------------------------------------------
		case EFFECTSTATUS_COMA :
			SetAlive();
			if(IsVampire())
			{
				ExecuteActionInfoFromMainNode(
							BLOOD_RESURRECT,										// »ç¿ë ±â¼ú ¹øÈ£
						
							m_X, m_Y, 0,
							(int)m_Direction,														// »ç¿ë ¹æÇâ
							
							m_ID,												// ¸ñÇ¥¿¡ ´ëÇÑ Á¤º¸
							m_X, m_Y, 0,
							
							2*16, //5*16, 
							
							NULL,
							
							false,
							
							(int)m_sX, (int)m_sY);	
			}

		case EFFECTSTATUS_GHOST:
			if (!(*g_pCreatureTable)[m_CreatureType].bFlyingCreature)	// ¹ÚÁãÀÎ °æ¿ì
				SetGroundCreature();
			break;
		break;
		case EFFECTSTATUS_GLACIER:	
			MCreature::RemoveGlacierEffect();
			break;

		case EFFECTSTATUS_INSTALL_TURRET:
			SetAction( ACTION_STAND );
			SetInstallTurretCount(0);
			SetInstallTurretDirect(2);
			SetDirection( 2 );
			SetCurrentDirection( 2 );
			break;
		case EFFECTSTATUS_GRAND_MASTER_SLAYER:
		case EFFECTSTATUS_GRAND_MASTER_VAMPIRE:
		case EFFECTSTATUS_GRAND_MASTER_OUSTERS:
		case EFFECTSTATUS_GRAND_MASTER_SLAYER_130:
		case EFFECTSTATUS_GRAND_MASTER_SLAYER_150:
		case EFFECTSTATUS_GRAND_MASTER_VAMPIRE_130:
		case EFFECTSTATUS_GRAND_MASTER_VAMPIRE_150:
		case EFFECTSTATUS_GRAND_MASTER_OUSTERS_130:
		case EFFECTSTATUS_GRAND_MASTER_OUSTERS_150:
			{
				type = GetMasterEffectType(status);
			}
			break;
		case EFFECTSTATUS_HYDRO_CONVERGENCE:
			type = EFFECTSPRITETYPE_HYDRO_CONVERGENCE_PILLAR_OF_WATER_REPEAT;
			break;	
		case EFFECTSTATUS_BLIND:
			if(g_pTopView != NULL && GetID() == g_pPlayer->GetID())
			{
				g_pTopView->SetFadeStart(1, 31, 1, 255,255,255);
				g_pTopView->SetBlindEffect(false);
			}
			break;
#if __CONTENTS(__20091116_ADD_RARE_SKILL)
			// 2009.11.19 by neclipse
			// ¾Æ¿ì½ºÅÍÁîÀÇ ÁúÇ³ÀÇ º£¸®¾î ·¹¾î½ºÅ³Àº
			// ÀÌµ¿½Ã »ç¶óÁöµµ·Ï Ã³¸®ÇÑ´Ù.
		case EFFECTSTATUS_SQUALLY_BARRIER1:
			RemoveAttachEffect(EFFECTSPRITETYPE_OUSTERS_SQUALLY_BARRIER_1_RARE_SKILL_BACK);
			RemoveAttachEffect(EFFECTSPRITETYPE_OUSTERS_SQUALLY_BARRIER_1_RARE_SKILL_FRONT);
			break;
		case EFFECTSTATUS_SQUALLY_BARRIER2:
			RemoveAttachEffect(EFFECTSPRITETYPE_OUSTERS_SQUALLY_BARRIER_2_RARE_SKILL_BACK);
			RemoveAttachEffect(EFFECTSPRITETYPE_OUSTERS_SQUALLY_BARRIER_2_RARE_SKILL_FRONT);
			break;
#endif //__20091116_ADD_RARE_SKILL

	}

	//------------------------------------------------------------
	//
	//			EffectSprite·Î Ç¥ÇöÇÏ´Â °æ¿ì
	//
	//------------------------------------------------------------
	if (bUseEffectSprite)
	{
		//TYPE_EFFECTSPRITETYPE type = (*g_pEffectStatusTable)[status].EffectSpriteType;
		TYPE_EFFECTSPRITETYPE type2 = EFFECTSPRITETYPE_NULL;

		if(type == EFFECTSPRITETYPE_FAST_MOVE_STOP)
			type2 = EFFECTSPRITETYPE_FAST_MOVE_FLY;

		if(type == EFFECTSPRITETYPE_HYDRO_CONVERGENCE_PILLAR_OF_WATER_REPEAT)
			type2 = EFFECTSPRITETYPE_HYDRO_CONVERGENCE_WATER_GROUND_REPEAT;

		_MinTrace("remove effectsprite\n");

		//-------------------------------------------------------
		// Creature¿¡ ºÙ¾î ÀÖ´Â EffectÁß¿¡¼­
		// EffectSpriteTypeÀÌ typeÀÎ °ÍÀ» Á¦°ÅÇÑ´Ù.
		//-------------------------------------------------------
		if (type < g_pEffectSpriteTypeTable->GetSize())
		{
			if (IsFemale()
				&& (*g_pEffectSpriteTypeTable)[type].FemaleEffectSpriteType!=EFFECTSPRITETYPE_NULL)
			{
				type = (*g_pEffectSpriteTypeTable)[type].FemaleEffectSpriteType;
			}
			

			if (m_bAttachEffect[type])
			{
				//-------------------------------------------------------
				// ¸ö¿¡ ºÙÀº °æ¿ì
				//-------------------------------------------------------			
				ATTACHEFFECT_LIST::iterator iEffect = m_listEffect.begin();

				bool re = false;

				while (iEffect != m_listEffect.end())
				{
					MAttachEffect* pEffect = *iEffect;
					
					//-------------------------------------------------------
					// °°Àº typeÀ» Ã£´Â´Ù.
					//-------------------------------------------------------
					if (pEffect->IsEffectSprite() 
						&& (pEffect->GetEffectSpriteType() == type ||
						type2 != EFFECTSPRITETYPE_NULL && pEffect->GetEffectSpriteType() == type2 ) )
					{						
						// ¸Þ¸ð¸® Á¦°Å
						delete pEffect;
						pEffect = NULL;
						
						ATTACHEFFECT_LIST::iterator dEffect = iEffect;
						iEffect--;

						// list¿¡¼­ Á¦°Å
						m_listEffect.erase( dEffect );

						m_bAttachEffect[type] = false;
						
						re = true;
					}					
					
					iEffect++;
				}

				if(re)
					return true;

				//-------------------------------------------------------
				// ¹Ù´Ú¿¡ ºÙÀº °æ¿ì
				//-------------------------------------------------------
				iEffect = m_listGroundEffect.begin();

				while (iEffect != m_listGroundEffect.end())
				{
					MAttachEffect* pEffect = *iEffect;
					
					//-------------------------------------------------------
					// °°Àº typeÀ» Ã£´Â´Ù.
					//-------------------------------------------------------
					if (pEffect->IsEffectSprite() && 
						( pEffect->GetEffectSpriteType() == type || type2 != EFFECTSPRITETYPE_NULL && 
						type2 == pEffect->GetEffectSpriteType()) )
					{
						// ¸Þ¸ð¸® Á¦°Å
						delete pEffect;

						// list¿¡¼­ Á¦°Å
						m_listGroundEffect.erase( iEffect );

						m_bAttachEffect[type] = false;
				
						return true;
					} 
					iEffect++;
				}
			}
		}
	}
	//------------------------------------------------------------
	//
	//			EffectColor·Î Ç¥ÇöÇÏ´Â °æ¿ì
	//
	//------------------------------------------------------------
	else
	{
		WORD colorSet = (*g_pEffectStatusTable)[status].EffectColor;

		//-------------------------------------------------------
		// Creature¿¡ ºÙ¾î ÀÖ´Â EffectÁß¿¡¼­
		// EffectColor°¡ colorÀÎ °ÍÀ» Á¦°ÅÇÑ´Ù.
		//-------------------------------------------------------
		ATTACHEFFECT_LIST::iterator iEffect = m_listEffect.begin();

		while (iEffect != m_listEffect.end())
		{
			MAttachEffect* pEffect = *iEffect;
			
			//-------------------------------------------------------
			// °°Àº typeÀ» Ã£´Â´Ù.
			//-------------------------------------------------------
			if (pEffect->IsEffectColor() && pEffect->GetEffectColor() == colorSet)
			{
				ADDON	part = pEffect->GetEffectColorPart();

				//------------------------------------------------------------
				// Æ¯Á¤ÇÑ ºÎÀ§¸¸ »ö±òÀÌ ¹Ù²î´Â °æ¿ìµµ ÀÖ´Ù.
				//------------------------------------------------------------
				if (part < ADDON_MAX)
				{
					m_Addon[part].bEffectColor = FALSE;
				}
				//------------------------------------------------------------
				// ¸ðµç ºÎÀ§¸¦ ¿ø·¡´ë·Î...
				//------------------------------------------------------------
				else
				{
					for (int p=0; p<ADDON_MAX; p++)
					{
						m_Addon[p].bEffectColor = FALSE;
					}
				}

				// ¸Þ¸ð¸® Á¦°Å
				delete pEffect;

				// list¿¡¼­ Á¦°Å
				m_listEffect.erase( iEffect );

				return true;
			}
			
			iEffect++;
		}		
	}
	
	return false;
}

//----------------------------------------------------------------------
// Update Effect
//----------------------------------------------------------------------
// Creature¿¡ ºÙÀº ¸ðµç EffectÀÇ FrameÀ» ¹Ù²ãÁÖ°í..
// ³¡³ª´Â°Ô ÀÖÀ¸¸é list¿Í memory¿¡¼­ »èÁ¦ÇÑ´Ù.
//----------------------------------------------------------------------
void		
MCreatureWear::UpdateAttachEffect()
{
	ATTACHEFFECT_LIST::iterator iEffect = m_listEffect.begin();
	ATTACHEFFECT_LIST::iterator iEffectTemp;

	// ¹à±â´Â 0
	//m_MaxEffectLight = 0;

	//---------------------------------------------------------------------
	// Ä³¸¯ÅÍ »ö±ò ¹Ù²Ù´Â »ö..
	//---------------------------------------------------------------------
	// NULL°ªÀÌ´ç.. ¿ÜºÎ¿¡¼­ Ã¼Å©ÇØ¾ßÇÔ..
	m_AttachEffectColor = m_ChangeColorSet;	//ATTACHEFFECTCOLOR_NULL;
	int bShowColor = (HasEffectStatus(EFFECTSTATUS_CURSE_PARALYSIS) || HasEffectStatus(EFFECTSTATUS_FREEZE)
						|| g_CurrentFrame % g_pClientConfig->FRAME_DRAW_ORIGINAL_SPRITE);	// ¸î frame¸¶´Ù ÇÑ¹ø¾¿Àº ¿ø·¡ »ö±òÀ» º¸¿©ÁØ´Ù.

	int bShowColorPart = (g_CurrentFrame & 0x00000004);	// 4 frame¾¿ ¹ø°¥¾Æ°¡¸ç »ö Ãâ·Â
	int numColors = 0;
	BOOL bChangeColor = FALSE;

	BOOL	bAddonColorPart[ADDON_MAX] = { FALSE, };
	WORD	addonColor[ADDON_MAX] = { m_ChangeColorSet, };

	//---------------------------------------------------------------------
	// ¸ðµç Effect¸¦ UpdateÇÑ´Ù.
	//---------------------------------------------------------------------
	while (iEffect != m_listEffect.end())
	{
		MAttachEffect*	pEffect = *iEffect;
		bool			bErase = false;
		
		int x		= pEffect->GetX();
		int y		= pEffect->GetY();
		int light = pEffect->GetLight();		

		//---------------------------------------------------------------------
		// Update
		//---------------------------------------------------------------------
		// message : find path
		//#ifdef	OUTPUT_DEBUG
			//sprintf(g_pDebugMessage->GetCurrent(), "Before UpdateEffect : Type=%d", pEffect->GetFrameID());	
			//g_pDebugMessage->Next();
		//#endif

		if( pEffect->GetEffectSpriteType() == EFFECTSPRITETYPE_FAST_MOVE_FLY ||
			pEffect->GetEffectSpriteType() == EFFECTSPRITETYPE_FAST_MOVE_STOP //||
//			(
//			pEffect->GetEffectSpriteType() == EFFECTSPRITETYPE_SUMMON_SYLPH_GREEN_FLY &&
//			pEffect->GetEffectSpriteType() == EFFECTSPRITETYPE_SUMMON_SYLPH_BLACK_STOP
//			)
			)
		{		
			BLT_TYPE		bltType = (*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_FAST_MOVE_STOP].BltType;
			TYPE_EFFECTSPRITETYPE		EffectSpriteType = pEffect->GetEffectSpriteType();
			bool			bNewSummonSylphEffect = false;
			bool			bNewSummonSylphEffectStop = false;
			
			if( EffectSpriteType >= EFFECTSPRITETYPE_SUMMON_SYLPH_GREEN_FLY &&
				EffectSpriteType <= EFFECTSPRITETYPE_SUMMON_SYLPH_BLACK_STOP )
			{
				bNewSummonSylphEffect = true;

				if( (EffectSpriteType - EFFECTSPRITETYPE_SUMMON_SYLPH_GREEN_FLY) & 0x1 )
					bNewSummonSylphEffectStop = true;
			}
			
			if( GetAction() == ACTION_OUSTERS_FAST_MOVE_STAND && (
				EffectSpriteType != EFFECTSPRITETYPE_FAST_MOVE_STOP ||
				( bNewSummonSylphEffect && !bNewSummonSylphEffectStop )
				)
			  )
			{
				TYPE_FRAMEID	frameID	= (*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_FAST_MOVE_STOP].FrameID;
				
				if( bNewSummonSylphEffect )
					frameID = (*g_pEffectSpriteTypeTable)[ EffectSpriteType + 1 ].FrameID;

				int maxFrame = g_pTopView->GetMaxEffectFrame(bltType, frameID);			
			
				pEffect->SetEffectSprite( EFFECTSPRITETYPE_FAST_MOVE_STOP );
				if( bNewSummonSylphEffect )
					pEffect->SetEffectSprite( EffectSpriteType + 1 );
				pEffect->SetFrameID( frameID, maxFrame );
			}
			else
			if( GetAction() == ACTION_OUSTERS_FAST_MOVE_MOVE && 
				( pEffect->GetEffectSpriteType() != EFFECTSPRITETYPE_FAST_MOVE_FLY ||
				( bNewSummonSylphEffect && bNewSummonSylphEffectStop )
			  ) )
			{
				TYPE_FRAMEID	frameID	= (*g_pEffectSpriteTypeTable)[EFFECTSPRITETYPE_FAST_MOVE_FLY].FrameID;
				if( bNewSummonSylphEffect )
					frameID = (*g_pEffectSpriteTypeTable)[ EffectSpriteType - 1 ].FrameID;

				int maxFrame = g_pTopView->GetMaxEffectFrame(bltType, frameID);			

				pEffect->SetEffectSprite( EFFECTSPRITETYPE_FAST_MOVE_FLY );

				if( bNewSummonSylphEffect )
					pEffect->SetEffectSprite( EffectSpriteType - 1 );
				pEffect->SetFrameID( frameID, maxFrame );
			}
		} 
		else if( pEffect->GetEffectSpriteType() >= EFFECTSPRITETYPE_NEW_LAR_SLASH_MALE_FAST &&
				 pEffect->GetEffectSpriteType() <= EFFECTSPRITETYPE_NEW_LAR_SLASH_FEMALE_SLOW )
		{
			if(!(  GetAction() == ACTION_SLAYER_SWORD_2 || GetAction() == ACTION_SLAYER_SWORD_2_SLOW || GetAction() == ACTION_SLAYER_SWORD_2_FAST ) 
				&& m_RepeatCount <= 0 )
			{
				pEffect->SetCount(0);
			}
		}
		else if(		
					(pEffect->GetEffectSpriteType() >= EFFECTSPRITETYPE_REGEN_TOWER_THROW_LIGHT_START &&
					pEffect->GetEffectSpriteType() <= EFFECTSPRITETYPE_REGEN_TOWER_THROW_LIGHT_END &&
					!HasEffectStatus( EFFECTSTATUS_TRYING ) 
					)
			)
		{
			bErase = true;			
		}

		if (bErase == false && pEffect->Update())
		{
			// -_- Èí¿µÀº ¹æÇâ ¾È¹Ù²Û´Ù..
			if( pEffect->GetEffectSpriteType() != EFFECTSPRITETYPE_ABSORB_SOUL )
				pEffect->SetDirection( m_CurrentDirection );
			// ÃÖ°í ¹à±â¸¦ °¡Áø EffectÀÇ ¹à±â¸¦ ÀúÀåÇÑ´Ù.
//			if (m_MaxEffectLight < pEffect->GetLight())
//			{
//				m_MaxEffectLight = pEffect->GetLight();
//			}

			// À§Ä¡ ¼³Á¤
			pEffect->SetPosition(m_X, m_Y);

			//---------------------------------------------------------------------
			// À§Ä¡°¡ ¹Ù²î¾ú°Å³ª
			// ºûÀÇ Å©±â(½Ã¾ß)°¡ ¹Ù²ï °æ¿ì
			//---------------------------------------------------------------------
			if (x!=pEffect->GetX() || y!=pEffect->GetY()
				|| light != pEffect->GetLight())
			{				
				// ½Ã¾ß ¹Ù²Ù±â
//				g_pZone->UnSetLight(x, y, light);
//				g_pZone->SetLight(pEffect->GetX(), pEffect->GetY(), pEffect->GetLight());

				/*
				// UnSetLightSight
				#ifdef	OUTPUT_DEBUG
					sprintf(g_pDebugMessage->GetCurrent(), "UnSetLightSight : Type=%d, Light=%d, (%d, %d)", pEffect->GetFrameID(), light, x,y);	
					g_pDebugMessage->Next();
				#endif

				// SetLightSight
				#ifdef	OUTPUT_DEBUG
					sprintf(g_pDebugMessage->GetCurrent(), "SetLightSight : Type=%d, Light=%d, (%d, %d)", pEffect->GetFrameID(), pEffect->GetLight(), pEffect->GetX(), pEffect->GetY());	
					g_pDebugMessage->Next();
				#endif
				*/
			}

			//---------------------------------------------------------------------
			// Ä³¸¯ÅÍ »ö±ò ¹Ù²Ù´Â EffectÀÌ¸é
			// ÇÏ³ª¸¦ ¼±ÅÃÇØ¾ß ÇÑ´Ù.
			//---------------------------------------------------------------------
			if (pEffect->IsEffectColor())
			{
				ADDON	part = pEffect->GetEffectColorPart();

				//--------------------------------------------------------
				// ºÎºÐÀûÀ¸·Î »ö±ò ¹Ù²î´Â effect
				//--------------------------------------------------------
				if (part < ADDON_MAX)
				{
					if (bShowColorPart)
					{
						bAddonColorPart[part] = TRUE;
						addonColor[part] = pEffect->GetEffectColor();

						bChangeColor = TRUE;
					}
				}
				//--------------------------------------------------------
				// ÀüÃ¼ »ö±ò ¹Ù²î´Â effect
				//--------------------------------------------------------
				else if (bShowColor)
				{
					numColors++;
					//if (m_AttachEffectColor == ATTACHEFFECTCOLOR_NULL || rand()%numColors==0)
					if (m_AttachEffectColor == m_ChangeColorSet || rand()%numColors==0)
					{
						m_AttachEffectColor = pEffect->GetEffectColor();

						bChangeColor = TRUE;
					}
				}				
			}

			//-----------------------------------------------
			//
			// ÀÌ Effect°¡ ³¡³ª±â Àü¿¡ LinkCount¿¡ ÀÇÇØ¼­
			// ´ÙÀ½ ¿¬°áµÇ´Â Effect°¡ ÀÖÀ¸¸é »ý¼ºÇØ¾ß ÇÑ´Ù.
			//
			// ÇöÀçFrameÀÌ EndLinkFrameÀ» ³Ñ¾î°£ °æ¿ì
			//
			//-----------------------------------------------
			if (g_CurrentFrame >= pEffect->GetEndLinkFrame()
				&& pEffect->GetLinkSize() != 0)
			{
				// GenerateNext¿¡¼­ 
				// pEffectÀÇ EffectTargetÀ» NULL·Î ¸¸µé¾îÁÖ±â ¶§¹®¿¡
				// ¿©±â¼­ Áö¿ï ÇÊ¿ä ¾ø´Ù.
				g_pEffectGeneratorTable->GenerateNext( pEffect );

				// pEffect´Â ¿©ÀüÈ÷ Á¸ÀçÇØ¾ß ÇÏ¹Ç·Î Áö¿ì¸é ¾ÈµÈ´Ù.
			}

			// Á¦´ë·Î µÈ °æ¿ì
			iEffect++;
		}
		//---------------------------------------------------------------------
		// ½Ã°£ÀÌ ´Ù µÅ¼­ ³¡³ª´Â °æ¿ì
		//---------------------------------------------------------------------
		else
		{
			bool bUseEffectSprite = pEffect->IsEffectSprite();

			// flagÁ¦°Å
			if (bUseEffectSprite)
			{
				m_bAttachEffect[pEffect->GetEffectSpriteType()] = false;	// flagÁ¦°Å
			}

			//m_bEffectStatus[pEffect->GetActionInfo()] = false;

			ADDON	part = pEffect->GetEffectColorPart();

			//------------------------------------------------------------
			// Æ¯Á¤ÇÑ ºÎÀ§¸¸ »ö±òÀÌ ¹Ù²î´Â °æ¿ìµµ ÀÖ´Ù.
			//------------------------------------------------------------
			if (part < ADDON_MAX)
			{
				m_Addon[part].bEffectColor = FALSE;
			}
			//------------------------------------------------------------
			// ¿ø·¡´ë·Î ¸ðµÎ µ¹¸°´Ù.
			//------------------------------------------------------------
			else
			{
				for (int p=0; p<ADDON_MAX; p++)
				{
					m_Addon[p].bEffectColor = FALSE;
				}
			}
		
			//---------------------------------------------------------------------
			//
			// ´ÙÀ½ ¿¬°áµÇ´Â Effect°¡ ÀÖÀ¸¸é »ý¼ºÇØ¾ß ÇÑ´Ù.
			//
			//---------------------------------------------------------------------
			if (pEffect->GetLinkSize() != 0)
			{				
				g_pEffectGeneratorTable->GenerateNext( pEffect );
			}

			// ºû³ª´Â Effect¸é ½Ã¾ß¸¦ »ç¶óÁö°Ô ÇØ¾ßÇÑ´Ù.
			//if (pEffect->GetBltType()==BLT_EFFECT)
			{
				//m_nAlphaEffect --;

				// ¸ðµç ºû³ª´ÂEffect°¡ »ç¶óÁ³À¸¸é ½Ã¾ß¸¦ Á¦°Å½ÃÅ²´Ù.
				//if (m_nAlphaEffect==0)
				{
//					g_pZone->UnSetLight(x, y, light);

					// UnSet LightSight
					/*
					#ifdef	OUTPUT_DEBUG
						sprintf(g_pDebugMessage->GetCurrent(), "RemoveEffect : Type=%d, Light=%d, (%d, %d)", pEffect->GetFrameID(), light, x,y);	
						g_pDebugMessage->Next();
					#endif
					*/
				}
			}

			DEBUG_ADD_FORMAT("[DeleteAttachEffect] id=%d, esType=%d", m_ID, pEffect->GetEffectSpriteType());
			
			// memory»èÁ¦, list»èÁ¦						
			delete pEffect;						// memoryÁ¦°Å
			
			DEBUG_ADD("[DeleteAttachEffect] OK");

			// list¿¡¼­ »èÁ¦ÇÏ±â À§ÇØ¼­.. ÀÓ½Ã·Î ÀúÀå
			iEffectTemp = iEffect;

			iEffect++;
			m_listEffect.erase( iEffectTemp );	// list¿¡¼­ Á¦°Å
		}		
	}

	//---------------------------------------------------------------------
	// ¸ö¿¡ ºÙ´Â effect
	//---------------------------------------------------------------------
	// ¸ðµç Effect¸¦ UpdateÇÑ´Ù.
	//---------------------------------------------------------------------
	iEffect = m_listGroundEffect.begin();
	
	while (iEffect != m_listGroundEffect.end())
	{
		MAttachEffect*	pEffect = *iEffect;
		
		int x		= pEffect->GetX();
		int y		= pEffect->GetY();
		int light = pEffect->GetLight();		

		//---------------------------------------------------------------------
		// Update
		//---------------------------------------------------------------------
		// message : find path
		//#ifdef	OUTPUT_DEBUG
			//sprintf(g_pDebugMessage->GetCurrent(), "Before UpdateEffect : Type=%d", pEffect->GetFrameID());	
			//g_pDebugMessage->Next();
		//#endif

		if (pEffect->Update())
		{
			// ÃÖ°í ¹à±â¸¦ °¡Áø EffectÀÇ ¹à±â¸¦ ÀúÀåÇÑ´Ù.
//			if (m_MaxEffectLight < pEffect->GetLight())
//			{
//				m_MaxEffectLight = pEffect->GetLight();
//			}

			// À§Ä¡ ¼³Á¤
			pEffect->SetPosition(m_X, m_Y);

			//---------------------------------------------------------------------
			// À§Ä¡°¡ ¹Ù²î¾ú°Å³ª
			// ºûÀÇ Å©±â(½Ã¾ß)°¡ ¹Ù²ï °æ¿ì
			//---------------------------------------------------------------------
			if (x!=pEffect->GetX() || y!=pEffect->GetY()
				|| light != pEffect->GetLight())
			{				
				// ½Ã¾ß ¹Ù²Ù±â
//				g_pZone->UnSetLight(x, y, light);
//				g_pZone->SetLight(pEffect->GetX(), pEffect->GetY(), pEffect->GetLight());

				/*
				// UnSetLightSight
				#ifdef	OUTPUT_DEBUG
					sprintf(g_pDebugMessage->GetCurrent(), "UnSetLightSight : Type=%d, Light=%d, (%d, %d)", pEffect->GetFrameID(), light, x,y);	
					g_pDebugMessage->Next();
				#endif

				// SetLightSight
				#ifdef	OUTPUT_DEBUG
					sprintf(g_pDebugMessage->GetCurrent(), "SetLightSight : Type=%d, Light=%d, (%d, %d)", pEffect->GetFrameID(), pEffect->GetLight(), pEffect->GetX(), pEffect->GetY());	
					g_pDebugMessage->Next();
				#endif
				*/
			}

			//-----------------------------------------------
			//
			// ÀÌ Effect°¡ ³¡³ª±â Àü¿¡ LinkCount¿¡ ÀÇÇØ¼­
			// ´ÙÀ½ ¿¬°áµÇ´Â Effect°¡ ÀÖÀ¸¸é »ý¼ºÇØ¾ß ÇÑ´Ù.
			//
			// ÇöÀçFrameÀÌ EndLinkFrameÀ» ³Ñ¾î°£ °æ¿ì
			//
			//-----------------------------------------------
			if (g_CurrentFrame >= pEffect->GetEndLinkFrame()
				&& pEffect->GetLinkSize() != 0)
			{
				// GenerateNext¿¡¼­ 
				// pEffectÀÇ EffectTargetÀ» NULL·Î ¸¸µé¾îÁÖ±â ¶§¹®¿¡
				// ¿©±â¼­ Áö¿ï ÇÊ¿ä ¾ø´Ù.
				g_pEffectGeneratorTable->GenerateNext( pEffect );

				// pEffect´Â ¿©ÀüÈ÷ Á¸ÀçÇØ¾ß ÇÏ¹Ç·Î Áö¿ì¸é ¾ÈµÈ´Ù.
			}

			// Á¦´ë·Î µÈ °æ¿ì
			iEffect++;
		}
		//---------------------------------------------------------------------
		// ½Ã°£ÀÌ ´Ù µÅ¼­ ³¡³ª´Â °æ¿ì
		//---------------------------------------------------------------------
		else
		{
			bool bUseEffectSprite = pEffect->IsEffectSprite();

			// flagÁ¦°Å
			if (bUseEffectSprite)
			{
				m_bAttachEffect[pEffect->GetEffectSpriteType()] = false;	// flagÁ¦°Å
			}

			//---------------------------------------------------------------------
			//
			// ´ÙÀ½ ¿¬°áµÇ´Â Effect°¡ ÀÖÀ¸¸é »ý¼ºÇØ¾ß ÇÑ´Ù.
			//
			//---------------------------------------------------------------------
			if (pEffect->GetLinkSize() != 0)
			{				
				g_pEffectGeneratorTable->GenerateNext( pEffect );
			}

			// ºû³ª´Â Effect¸é ½Ã¾ß¸¦ »ç¶óÁö°Ô ÇØ¾ßÇÑ´Ù.
			//if (pEffect->GetBltType()==BLT_EFFECT)
			{
				//m_nAlphaEffect --;

				// ¸ðµç ºû³ª´ÂEffect°¡ »ç¶óÁ³À¸¸é ½Ã¾ß¸¦ Á¦°Å½ÃÅ²´Ù.
				//if (m_nAlphaEffect==0)
				{
//					g_pZone->UnSetLight(x, y, light);

					// UnSet LightSight
					/*
					#ifdef	OUTPUT_DEBUG
						sprintf(g_pDebugMessage->GetCurrent(), "RemoveEffect : Type=%d, Light=%d, (%d, %d)", pEffect->GetFrameID(), light, x,y);	
						g_pDebugMessage->Next();
					#endif
					*/
				}
			}

			DEBUG_ADD_FORMAT("[DeleteAttachEffect] id=%d, esType=%d", m_ID, pEffect->GetEffectSpriteType());
			

			// memory»èÁ¦, list»èÁ¦						
			delete pEffect;						// memoryÁ¦°Å
			
			
			DEBUG_ADD("[DeleteAttachEffect] OK");
			

			// list¿¡¼­ »èÁ¦ÇÏ±â À§ÇØ¼­.. ÀÓ½Ã·Î ÀúÀå
			iEffectTemp = iEffect;

			iEffect++;
			m_listGroundEffect.erase( iEffectTemp );	// list¿¡¼­ Á¦°Å
		}		
	}

	//---------------------------------------------------------------------
	// »ö±ò ¹Ù²î´Â °Å º¸¿©ÁÖ´Â ½ÃÁ¡ÀÌ¸é..
	//---------------------------------------------------------------------
	if (bChangeColor)
	{
		//---------------------------------------------------------------------
		// ÀüÃ¼ »ö±ò ¹Ù²î´Â Effect°¡ ¾ø´Â °æ¿ì
		//---------------------------------------------------------------------	
		if (m_AttachEffectColor == m_ChangeColorSet)//ATTACHEFFECTCOLOR_NULL)
		{
			for (int p=0; p<ADDON_MAX; p++)
			{
				if (bAddonColorPart[p])
				{
					// ±× ºÎºÐ¸¸ ¹Ù²î´Â »ö±ò·Î..
					m_Addon[p].bEffectColor		= TRUE;
					m_Addon[p].EffectColorSet	= addonColor[p];
				}		
				else
				{
					// ¿ø·¡ »ö±ò·Î..
					m_Addon[p].bEffectColor		= FALSE;
				}
			}
		}
		//---------------------------------------------------------------------
		// ÀüÃ¼ »ö±ò ¹Ù²î´Â Effect°¡ ÀÖ´Â °æ¿ì
		//---------------------------------------------------------------------
		else
		{
			for (int p=0; p<ADDON_MAX; p++)
			{
				m_Addon[p].bEffectColor		= TRUE;

				if (bAddonColorPart[p])
				{
					// ±× ºÎºÐ¸¸ ¹Ù²î´Â »ö±ò·Î..			
					m_Addon[p].EffectColorSet	= addonColor[p];
				}		
				else
				{
					// ÀüÃ¼ ¹Ù²î´Â »ö±ò·Î..				
					m_Addon[p].EffectColorSet	= m_AttachEffectColor;
				}
			}
		}
	}
	//---------------------------------------------------------------------
	// »ö±ò ¹Ù²î´Â°Å ¾È º¸¿©ÁÖ´Â ½ÃÁ¡...
	//---------------------------------------------------------------------
	else
	{
		for (int p=0; p<ADDON_MAX; p++)
		{
			m_Addon[p].bEffectColor		= FALSE;
		}
	}
}

const MCreatureWear::ADDON_INFO&	MCreatureWear::GetACAddonInfo(int Addon) const
{ 
	switch( Addon )
	{
	case AC_ADDON_BODY :
		return m_Addon[ ADDON_COAT ];
		
	case AC_ADDON_HELM :
		return m_Addon[ ADDON_HELM ];

	case AC_ADDON_LEFTHAND :
		return m_Addon[ ADDON_LEFTHAND ];

	case AC_ADDON_RIGHTHAND :
		return m_Addon[ ADDON_RIGHTHAND ];

	case AC_ADDON_MOTOR :
		return m_Addon[ ADDON_MOTOR ];
	}

	return m_ShoulderAddon;
}

#if __CONTENTS(__FAST_TRANSFORTER||__SECOND_TRANSFORTER)
//½½·¹ÀÌ¾î¸¸ .. ¿ÀÅä¹ÙÀÌ Å¾½Â½Ã.. Addon¿¡ µî·ÏµÈ´Ù. µû¶ó¼­, ÀÌ ÇÔ¼ö´Â ½½·¹ÀÌ¾îÀÏ °æ¿ì¿¡¸¸ À¯È¿ÇÏ´Ù.
bool	MCreatureWear::IsRide_Fast_Transforter()
{
	ADDON_INFO& addon = m_Addon[ADDON_MOTOR];
	if (addon.bAddon && (addon.ItemType == 8	//½Å±Ô ÀÌµ¿¼ö´ÜÀÌ Ãß°¡µÇ¸é..¿©±â¿¡ ItemType¿¡ ÇÏµåÄÚµùÀ» ...
#if __CONTENTS(__SECOND_TRANSFORTER)
		|| addon.ItemType == 9
				|| addon.ItemType == 10
						|| addon.ItemType == 11
#endif //__SECOND_TRANSFORTER
		))
		return true;
	
	return false;
}
#endif //__FAST_TRANSFORTER||__SECOND_TRANSFORTER
