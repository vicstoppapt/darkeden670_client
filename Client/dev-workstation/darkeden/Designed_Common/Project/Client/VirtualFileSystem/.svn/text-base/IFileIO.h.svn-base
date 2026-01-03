//////////////////////////////////////////////////////////////////////
//
// Filename    : FileIO.h
// Written By  : chyaya@darkeden.com
// Description : Header Of IFileIO Class
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include <wtypes.h>
#include <ios>

// 추가 옵션: VirtualFileIO인 경우에만 동작한다.
namespace iovs_ex
{
	enum {
		virtualfile = 0x10000000,
		compress	= 0x20000000,
	};
}

//////////////////////////////////////////////////////////////////////
//
// class IFileIO
//
// : 일반 파일과 패키지 파일의 인터페이스를 통일하기 위한 클래스
//
//////////////////////////////////////////////////////////// chyaya //
class IFileIO
{
public:
	virtual ~IFileIO()	{}

	virtual void		open(LPCTSTR szName, int nMode) = 0;
	virtual void		close() = 0;

	virtual bool		is_open() const = 0;

	virtual void		read(char* buf, int len) = 0;
	
	virtual int			gcount() const = 0;

	virtual void		seekg(long off, int dir = std::ios_base::beg) = 0;
	virtual int			tellg() = 0;

	virtual void		write(const char* src, int len) = 0;

// 	virtual void		seekp(long off, int dir = std::ios_base::beg) = 0;
// 	virtual int			tellp() = 0;

	virtual bool		eof() const = 0;
	
	virtual void		get(char& ch) = 0;
	virtual void*		getline(char* psch, int nCount, char delim = '\n') = 0;
};
