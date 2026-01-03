//////////////////////////////////////////////////////////////////////////////
/// @file vfstream.cpp
/// @author chyaya
/// @date 2007.06.26
//////////////////////////////////////////////////////////////////////////////

#include "VFS_Precompile.h"
#include "VFS_Macro.h"

#include "vfstream.h"

#include "NormalFileIO.h"
#include "VirtualFileIO.h"

#ifdef _DEBUG
#define PACKAGEFILE_INLINE
#include "vfstream.inl"
#endif

VFSYSTEM iovfs_base::s_VFSystem;


void iovfs_base::open(LPCTSTR szName, int nMode)
{
	if(!szName) 
		return;



	BOOL bVirtualFile = nMode & iovs_ex::virtualfile;
	
	if(!bVirtualFile && nMode & std::ios_base::in)
		bVirtualFile = access(szName, 0);

	std::string strName = szName;

	 if ( strName.find(".inf") != -1 ) //如果是NIF文件	ASPK的时候注释掉
	 {
		 bVirtualFile = 1; //从包里读
		for (int i=0; i<EXCEPT_FILE_MAX; i++)
		{
			if ( strName.find( m_strExceptList[i].c_str() ) != -1 ) //找到了
				bVirtualFile = 0; //从外面文件夹里读
		}
	 }


	if(bVirtualFile)
	{	
		// VF绰 措家巩磊甫 啊府扁 锭巩俊 Unique茄 Path肺 父甸绢霖促.
		char szUniquePath[MAX_PATH];
		strcpy(szUniquePath, szName);
		make_unique_path(szUniquePath);

		m_pFileIO = new VirtualFileIO(&s_VFSystem);
		m_pFileIO->open(szUniquePath, nMode);
	}
	else
	{
		// 老馆 颇老篮 犬厘 可记阑 荤侩且 荐 绝促.
		nMode &= 0x0FFFFFFF;

		m_pFileIO = new NormalFileIO;
		m_pFileIO->open(szName, nMode);
	}

	if(!m_pFileIO->is_open())
		close();
}


void iovfs_base::close()
{
	if(m_pFileIO) m_pFileIO->close();
	Destory();
}


void iovfs_base::start_vfs(LPCTSTR filename, int flags)
{
	s_VFSystem.Start(filename, flags);
}


void iovfs_base::end_vfs()
{
	s_VFSystem.End();
}


bool iovfs_base::is_virtualfile() const
{
	return dynamic_cast<VirtualFileIO*>(m_pFileIO) != NULL;
}
