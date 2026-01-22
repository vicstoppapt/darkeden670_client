//----------------------------------------------------------------------
// MServerItemTable.h
//----------------------------------------------------------------------

#ifndef __SERVER_CREATURETABLE_H__
#define __SERVER_CREATURETABLE_H__

#pragma warning(disable:4786)

#include "MString.h"
#include "CTypeTable.h"
#include <list>

class SERVER_CREATURETABLE_INFO {
	public :
		SERVER_CREATURETABLE_INFO();
		~SERVER_CREATURETABLE_INFO();

		void	SaveToFile(std::ofstream& file);
		void	LoadFromFile(ivfstream& file);

	public :
		int		Type;
		int		Level;
};

typedef CTypeTable<SERVER_CREATURETABLE_INFO> SERVER_CREATURETYPE_TABLE;


//----------------------------------------------------------------------
// MServerItemTableInfo
//----------------------------------------------------------------------
class SERVER_CREATURECLASS_TABLE : public SERVER_CREATURETYPE_TABLE {
	public :
		SERVER_CREATURECLASS_TABLE();
		~SERVER_CREATURECLASS_TABLE();

		int		AffectToCreatureTable( CREATURE_TABLE& creatureTable );
};



#endif	// __SERVER_CREATURETABLE_H__

