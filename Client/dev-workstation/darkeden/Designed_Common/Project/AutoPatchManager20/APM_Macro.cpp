#pragma once

#include "stdAfx.h"
#include "APM_Macro.h"
#include <direct.h>
#include <io.h>
#include <cstring>


// ----------------------------------------------------------------------------
const char* TrimChange( char* sBuffer_, char chDes_, char chSrc_ )
{
	char	*pHead;
	char	ch;
	
	pHead = sBuffer_;

	if((int) strlen(sBuffer_) <= 0)
		return sBuffer_;

	for(unsigned int i = 0; i<strlen(sBuffer_); i++)
	{
		ch = *pHead;
		if (ch == chSrc_)
			*pHead = chDes_;

		pHead ++;
	}
	return sBuffer_;
}


// ----------------------------------------------------------------------------
//	Name: trimGetRunName()
//	Desc: 지정된 문자열에서 실행파일을 얻습니다 
//	Call: 예) c:\tmp\sample.exe -> "sample.exe"
// ----------------------------------------------------------------------------
const char* TrimGetRunName( const char* sBuffer_ )
{
	int		nStrLength;
	const char	*sPtrEnd;
	const char	*sPtr;
	const char	*sExt;
	char	ch;

	if ((nStrLength = (int)strlen(sBuffer_)) <= 0 )
		return NULL;

	sPtrEnd = sBuffer_+ (nStrLength-1);
	sPtr	= sPtrEnd;
	sExt	= NULL;

	while(nStrLength>0)
	{
		ch = *sPtr;

		if (ch=='/' || ch=='\\' || ch==':' )
			return sExt;

		sExt = sPtr;

		//
		sPtr --;
		nStrLength --;
	}

	// if (*sExt >= 0x20 && *sExt <= 0xFF)
	if (sExt != NULL)
		return sExt;

	return NULL;
}


// ----------------------------------------------------------------------------
//	Name: trimGetRunName()
//	Desc: 지정된 문자열에서 실행파일을 얻습니다 
//	Call: 예) "c:\tmp\sample.exe" -> "c:\tmp\"
// ----------------------------------------------------------------------------
const char* TrimGetRunPath( const char* sSrcFullPath_ ,char *sOutRunPath_ )
{
	int		nStrLength;
	bool	bIsPathFind;

	char	*sPtrEnd;
	char	*sPtr;
	char	ch;

	bIsPathFind = false;
	if ((nStrLength = (int)strlen(sSrcFullPath_ )) <= 0 )
		return NULL;

	strcpy(sOutRunPath_,sSrcFullPath_);

	sPtrEnd = sOutRunPath_+(nStrLength-1);
	sPtr	= sPtrEnd;

	while( nStrLength>0 )
	{
		ch = *sPtr;

		if (ch=='/' || ch=='\\' || ch==':' )
		{
			bIsPathFind = true;
			*sPtr = '\0';
			break;
		}
		//
		sPtr --;
		nStrLength --;
	}

	if (strlen(sOutRunPath_) <= 0 || bIsPathFind == false)
		return NULL;

	return sOutRunPath_;
}

// ----------------------------------------------------------------------------
//	Name: trimChange()
//	Desc: 지정된버퍼중 해당문자열을 전부 수정
//	
// ----------------------------------------------------------------------------
const char* TrimChange( char* sBuffer_, const char* src_ ,char *des_)
{
	char		sBufferDes[256+1];
	const char	*pBufsrc;
	char		*pBufdes;

	memset( sBufferDes, 0, sizeof(sBufferDes) );

	pBufsrc = sBuffer_;
	pBufdes = sBufferDes;

	if ( (int) strlen(sBuffer_) == 0 )
		return sBuffer_;

	int len;
	int	i;

	len = (int) strlen( sBuffer_ );
	i =0;
	while( i< len )
	{
		if (strncmp( pBufsrc,src_,strlen( src_)) == 0)
		{
			strncpy( pBufdes, des_,strlen(des_));
			pBufsrc+= strlen(src_);
			pBufdes+= strlen(des_);
			i+= (int)strlen(src_);
		}
		else{
			strncpy( pBufdes, pBufsrc,1);
			pBufdes ++;
			pBufsrc ++;
			i++;
		}
	}

	strncpy ( sBuffer_, sBufferDes, strlen(sBufferDes));
	sBuffer_ += strlen(sBufferDes);
	*sBuffer_ = '\0';

	return sBuffer_;
}

// d:\sample\sample
// d:/sample/sample
bool FullPathBuild( const char* sSrcFullPath_ )
{
	char spath[1024+1];
	const char	*ps;
	char		*pd;

	memset( spath, 0, sizeof(spath) );
	ps = sSrcFullPath_;
	pd = spath;

	int fullPathLength = (int)strlen(sSrcFullPath_);
	int i;	
	for (i = 0; i < fullPathLength; ++i)
	{
		char ch = *(ps);
		if ( ch == '\\' ||  ch == '/' )
		{
			if ( strlen( ps ) > 0 && *(ps-1) != ':')
			{
				::_mkdir( spath );
				if ( ::_access( spath, 6) == -1)
					return false;
				/*
				OutputDebugString(spath);
				OutputDebugString("\n");
				*/
			}
		}
		*(pd) = ch; 
		++pd;
		++ps;
	}

	return true;
}