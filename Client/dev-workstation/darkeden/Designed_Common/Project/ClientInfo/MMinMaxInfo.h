//--------------------------------------------------------------------------------
// MMinMaxInfo.h
//--------------------------------------------------------------------------------

#ifndef __MMINMAXINFO_H__
#define __MMINMAXINFO_H__

#include "CTypeTable.h"
std::ifstream;
std::ofstream;

class MMinMaxInfo {
	public :
		MMinMaxInfo(int min=0, int max=0)
		{
			Set( min, max );
		}

		~MMinMaxInfo() {}

		void		Set(int min, int max)
		{
			Min	= min;
			Max	= max;
		}

		void		operator = (const MMinMaxInfo& info)
		{
			Set(info.Min, info.Max);
		}

		bool		operator == (const MMinMaxInfo& info)
		{
			return Min==info.Min && Max==info.Max;
		}

		bool		operator != (const MMinMaxInfo& info)
		{
			return Min!=info.Min || Max!=info.Max;
		}

		//------------------------------------------------------------
		// File I/O
		//------------------------------------------------------------
		void		SaveToFile(std::ofstream& file);
		void		LoadFromFile(ivfstream& file);

	public :
		int			Min;
		int			Max;

};

typedef CTypeTable<MMinMaxInfo>		MMinMaxInfoTable;

#endif
