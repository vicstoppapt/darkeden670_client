////////////////////////////////////////////////////////////////////////////////
//	created:	2004/12/22
//	file base:	client_pch.h
// 
////////////////////////////////////////////////////////////////////////////////

#pragma once

#pragma warning(disable:4290)
#pragma warning(disable:4018)
#pragma warning(disable:4244)
#pragma warning(disable:4018)
#pragma warning(disable:4786)
#pragma warning(disable:4103)
#pragma warning(disable:4049)

#pragma warning(error: 4067)

#pragma warning(push)

#include <string>
#include <vector>
#include <map>
#include <list>
#include <deque>
#include <bitset>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <cassert>
#include <assert.h>
#ifdef _MSC_VER
#undef assert
#ifndef NDEBUG
#include <cstdlib>
#define assert(expr) ((expr) ? (void)0 : (void)(::abort(), 0))
#else
#define assert(expr) ((void)0)
#endif
#endif
#include <MMSystem.h>
#include <Digitalv.h>
#include <DDraw.h>
#include <cstdio>
#include <cstdarg>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <locale.h>
#include <mbstring.h>
#include <mbctype.h>
// Definir tipos básicos que SystemTypes.h define, sem incluir SystemTypes.h
// (que inclui Windows.h novamente e causa conflito com common_sdk)
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
#include "AtlTypes/atltypes.h"
#include "ContentsFilter.h"
#pragma warning(pop)

using std::string;
using std::vector;
using std::map;
using std::list;
using std::deque;
using std::bitset;


