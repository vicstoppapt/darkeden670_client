//////////////////////////////////////////////////////////////////////////////
// Filename    : CGSMSSendHandler.cpp
// Written By  : reiot@ewestsoft.com , elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGSMSSend.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Assert.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGSMSSendHandler::execute (CGSMSSend* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);

#endif
	
	__END_DEBUG_EX __END_CATCH
}
