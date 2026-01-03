//////////////////////////////////////////////////////////////////////////////
/// @file iovfs_base.h
/// @author chyaya
/// @date 2007.06.26
//////////////////////////////////////////////////////////////////////////////
#pragma once

#include <WTypes.h>
#include "CNFS.h"

// Darkeden 특수화
//#define SPECIALIZE_DARKEDEN

#define VFS_VERSION		1	///< VirtualFileSystem 버전

class IFileIO;

//////////////////////////////////////////////////////////////////////////////
/// @struct VirtualFileHeader
/// @brief Virtual File Header
///
/// 가상 파일의 최상단에 붙게되는 파일 헤더
//////////////////////////////////////////////////////////////////////////////
struct VirtualFileHeader
{
	DWORD	FileSize;		///< 파일의 실제 크기
	BYTE	Version;		///< VFS Version (내가 이걸 왜 2번째에 넣었을까? - _-;;)
	BYTE	IsCompressed;	///< 압축이 되었는지 여부

	/// @brief 기본 생성자
	/// @sa Init()
	VirtualFileHeader()	{ Init(); }

	/// @brief 멤버 변수를 초기화 한다.
	void Init()
	{
		FileSize		= 0;
		Version			= VFS_VERSION;
		IsCompressed	= 0;
	}
};

/// struct VirtualFileHeader의 크기
/// sizeof()를 사용하면 4바이트 단위로 맞춰지기 때문에
/// 실제 크기를 따로 정의해준다.
#define VF_HEADER_SIZE		6


//////////////////////////////////////////////////////////////////////////////
/// @class VirtualFileSystem
/// @brief Virtual File System
///
/// 가상 파일 시스템을 관리하는 클래스
//////////////////////////////////////////////////////////////////////////////
class VirtualFileSystem
{
public:
	/// @brief 기본 생성자
	/// @sa Init()
	VirtualFileSystem();

	/// @brief start 생성자
	/// @param filename 파일 이름
	/// @param flags 오픈 모드
	/// @sa Start()
	/// @warning 클라이언트에서 사용할 때는 읽기 전용으로 하는 것이 좋다. (flags를 FS_READ)\n
	///          VFS에 데이터를 기록 중에 비정상 종료될 경우 파일의 무결성을 보장 할 수 없기 때문이다.
	VirtualFileSystem(LPCTSTR filename, int flags = FS_READ);

	/// @brief 파괴자
	~VirtualFileSystem();

	/// @brief 파일을 복사 할때 버퍼 크기
	enum { FILE_COPY_BUFFER_SIZE = 65536 };

public:
	/// @brief 멤버 변수를 초기화 한다.
	void		Init();

	/// @brief Virtual File System을 시작한다.
	/// @param filename 파일 이름
	/// @param flags 오픈 모드
	/// @return 성공 여부
	/// @warning 클라이언트에서 사용할 때는 읽기 전용으로 하는 것이 좋다. (flags를 FS_READ)\n
	///          VFS에 데이터를 기록 중에 비정상 종료될 경우 파일의 무결성을 보장 할 수 없기 때문이다.
	bool		Start(LPCTSTR filename, int flags = FS_READ);

	/// @brief Virtual File System 종료
	void		End();

	/// @brief VFS에 실제 파일을 복사한다.
	/// @param srcname 소스인 실제 파일의 경로
	/// @param compress 압축해서 카피할 것인지 여부
	/// @warning 현재(2007.06.26) 시점에서 압축을 하지 않은 경우를 테스트 못해봤다.
	///          압축을 하지 않고 사용하길 원한다면 반드시 테스트 후에 사용할 것.
	/// @sa AddFileRename()
	void		AddFile(LPCTSTR srcname, bool compress = false);

	/// @brief VFS에 실제 파일의 이름을 바꿔 복사한다.
	/// @param srcname 소스인 실제 파일의 경로
	/// @param destname 목표인 가상 파일의 경로
	/// @param compress 압축해서 카피할 것인지 여부
	/// @warning 현재(2007.06.26) 시점에서 압축을 하지 않은 경우를 테스트 못해봤다.
	///          압축을 하지 않고 사용하길 원한다면 반드시 테스트 후에 사용할 것.
	/// @sa AddFile()
	void		AddFileRename(LPCTSTR srcname, LPCTSTR destname, bool compress = false);

#ifdef SPECIALIZE_DARKEDEN
	/// @brief VFS에 실제 파일을 복사한다. (TypePackFile 특수화 버전)
	/// @param srcname 소스인 실제 파일의 경로
	/// @param compress 압축해서 카피할 것인지 여부
	/// @warning 현재(2007.06.26) 시점에서 사용하지 않음
	/// @sa AddTypePackFileRename(), AddFile(), AddFileRename()
	///
	/// TypePack의 각 Type크기만큼 나눠서 가상파일에 집어넣는 방법을 구상했으나
	/// 너무 파일이 많아지는 바람에 실패했다. - _-;;
	/// 사용하지 말것
	void		AddTypePackFile(LPCTSTR srcname, bool compress = false);

	/// @brief VFS에 실제 파일의 이름을 바꿔 복사한다. (TypePackFile 특수화 버전)
	/// @param srcname 소스인 실제 파일의 경로
	/// @param destname 목표인 가상 파일의 경로
	/// @param compress 압축해서 카피할 것인지 여부
	/// @warning 현재(2007.06.26) 시점에서 사용하지 않음
	/// @sa AddTypePackFile(), AddFile(), AddFileRename()
	///
	/// TypePack의 각 Type크기만큼 나눠서 가상파일에 집어넣는 방법을 구상했으나
	/// 너무 파일이 많아지는 바람에 실패했다. - _-;;
	/// 사용하지 말것
	void		AddTypePackFileRename(LPCTSTR srcname, LPCTSTR destname, bool compress = false);
#endif // SPECIALIZE_DARKEDEN

	/// @brief VFS 안의 가상파일을 삭제한다.
	/// @param filename 삭제할 가상 파일 경로
	///
	/// filename으로 넘긴 경로와 일치하는 가상 파일이 없으면
	/// 아무 일도 일어나지 않는다.
	void		DeleteFile(LPCTSTR filename);

	/// @brief 읽을 수 있는 대상 파일이 있는지 검사
	/// @param filename 검사할 파일 경로
	/// @return 파일이 존재하면 true
	///
	/// 주의할 점은 이 함수를 가상 파일이 존재하는지 여부로 사용해서는 안된다는 사실이다.
	/// 이 함수는 실제로 데이터를 읽어들일 수 있는 파일이 있는지 검사하는 함수로
	/// 가상파일, 일반파일 중 하나의 파일만 존재 하더라도 true를 리턴한다.
	/// 참고로 우선 순위는 일반파일이 더 높다.
	/// 지금 생각해보니 함수이름을 잘못 정한것 같기도 하다. - _-;;
	bool		IsFileExist(LPCTSTR filename) const;

	/// @brief 읽을 수 있는 대상 파일의 크기 검사
	/// @param filename 검사할 파일 경로
	/// @return 파일의 크기 (BYTE단위)
	///
	/// 이 함수는 실제로 데이터를 읽어들일 수 있는 파일의 크기를 검사하는 함수로
	/// 가상파일만 존재하면 가상파일의 크기를, 일반 파일만 존재하면 일반 파일이 크기를,
	/// 둘다 존재하면 일반 파일의 크기를 얻는 함수다.
	/// 이 함수 역시 지금 생각해보니 함수이름을 잘못 정한것 같기도 하다. - _-;;
	int			GetFileSize(LPCTSTR filename);

	/// @brief 가상 파일을 일반 파일로 만들어 준다.
	/// @param srcname 소스인 가상 파일 경로
	/// @return 성공 여부
	/// @sa CreateTempFileRename()
	///
	/// CreateTempFileRename()과 같은 기능을 하는 함수지만
	/// make_temp_filepath()를 사용해서 자동으로 임시 파일 경로를 만들어 준다.
	
	bool		CreateTempFile(LPCTSTR srcname);

	/// @brief 가상 파일을 일반 파일로 만들어 준다.
	/// @param srcname 소스인 가상 파일 경로
	/// @param destname 대상인 일반 파일 경로
	/// @return 성공 여부
	/// @sa CreateTempFile()
	///
	/// 가상 파일을 일반 파일로 만들어 준다.
	/// 디렉토리를 지정할 경우 자동으로 생성함
	bool		CreateRealFile(LPCTSTR srcname, LPCTSTR destname);

	/// @brief NFS Wrapper 클래스의 포인터를 얻는다.
	/// @return CNFS 포인터
	CNFS*		GetNFS()	{ return &m_NFS;	}

protected:
	/// @brief 해당 디렉토리를 만들어 준다.
	/// @param szFullPath 디렉토리 경로나 파일 경로
	/// @return 성공 여부
	///
	/// 하위 경로를 포함한 풀 디렉토리를 생성해준다.
	bool		BuildFullPathDirectory(LPCTSTR szFullPath);
	
private:
	CNFS		m_NFS;	///< NFS Wrapper
};

typedef VirtualFileSystem	VFSYSTEM;
typedef VFSYSTEM*			LPVFSYSTEM;