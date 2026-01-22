//////////////////////////////////////////////////////////////////////////////
/// @file VFS_Macro.h
/// @author chyaya
/// @date 2007.06.26
//////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>
#include <cstring>


//////////////////////////////////////////////////////////////////////////////
/// @fn make_unique_path
///
/// 경로를 유니크하게 변환한다.
//////////////////////////////////////////////////////////////////////////////
inline void make_unique_path(char * s)
{
	char * d = s;
	char c;
	while(c = *s)
	{
		while((c == '/' || c == '\\') && c == s[1])
			c = *(++s);
		c = tolower(c);
		if(c == '\\') c = '/';
		*d = c;
		++s, ++d;
	}
	*d = '\0';
}


//////////////////////////////////////////////////////////////////////////////
/// @fn make_temp_filepath
///
/// 임시 경로를 생성한다.
//////////////////////////////////////////////////////////////////////////////
inline void make_temp_filepath(LPCTSTR path, LPTSTR tempPath)
{
	const char* tok = "\\/";

	strcpy(tempPath, "temp/$");

	char szPathCopy[MAX_PATH];
	strcpy(szPathCopy, path);

	char* pFilePath = strtok(szPathCopy, tok);
	//strcat(tempPath, strlwr(pFilePath));
	strcat(tempPath, pFilePath);

	while(pFilePath = strtok(NULL, tok))
	{
		strcat(tempPath, "$");
		//strcat(tempPath, strlwr(pFilePath));
		strcat(tempPath, pFilePath);
	}
}


//////////////////////////////////////////////////////////////////////////////
/// @struct compare_path_string
///
/// 두개의 string을 경로로 간주하고 비교
/// - std::map의 template 3번째 인자로 사용가능
/// - std::set의 template 2번째 인자로 사용가능
//////////////////////////////////////////////////////////////////////////////
struct compare_path_string
{
	bool operator()(const std::string& s1, const std::string& s2) const
	{
		const char * p1 = s1.c_str();
		const char * p2 = s2.c_str();

		char c1, c2;
		while((c1 = *p1) & (c2 = *p2))
		{
			while((c1 == '/' || c1 == '\\') && c1 == p1[1])
				c1 = *(++p1);
			while((c2 == '/' || c2 == '\\') && c2 == p2[1])
				c2 = *(++p2);

			c1 = tolower(c1);
			if(c1 == '\\') c1 = '/';

			c2 = tolower(c2);
			if(c2 == '\\') c2 = '/';

			if(c1 != c2) return c1 < c2;

			++p1;
			++p2;
		}

		if(!c1 && !c2)
			return false;
		else
			return c1 < c2;

	}
};



//////////////////////////////////////////////////////////////////////////////
/// @struct hash_func_path_string_stlport
///
/// 두개의 string을 경로로 간주하는 hash function
/// - hash_map(stlport)의 template 3번째 인자로 사용가능
//////////////////////////////////////////////////////////////////////////////
struct hash_func_path_string_stlport
{ 
	size_t operator()(const std::string& s) const
	{
		unsigned long hash = 5381;
		int c;
		const char* p = s.c_str();
        
		while (c = *p)
		{
			while((c == '/' || c == '\\') && c == p[1])
				c = *(++p);
			c = tolower(c);
			if(c == '\\') c = '/';
			hash = ((hash << 5) + hash) + c;
			++p;
		}
        
        return hash;
	};
};


//////////////////////////////////////////////////////////////////////////////
/// @struct equal_path_string
///
/// 두개의 string을 경로로 간주하고 같은 값인지 체크
/// - hash_map(stlport)의 template 4번째 인자로 사용가능
//////////////////////////////////////////////////////////////////////////////
struct equal_path_string
{
	bool operator()(const std::string& s1, const std::string& s2) const
	{
		const char * p1 = s1.c_str();
		const char * p2 = s2.c_str();

		char c1, c2;
		while((c1 = *p1) & (c2 = *p2))
		{
			while((c1 == '/' || c1 == '\\') && c1 == p1[1])
				c1 = *(++p1);
			while((c2 == '/' || c2 == '\\') && c2 == p2[1])
				c2 = *(++p2);

			c1 = tolower(c1);
			if(c1 == '\\') c1 = '/';
			c2 = tolower(c2);
			if(c2 == '\\') c2 = '/';

			if(c1 != c2) return false;

			++p1;
			++p2;
		}

		if(!c1 && !c2) return true;
		return false;
	}
};


//////////////////////////////////////////////////////////////////////////////
/// @fn equal_path_string
///
/// XOR 마스킹 함 해준다. -__-
//////////////////////////////////////////////////////////////////////////////
inline void encrypt_data(char *data, int size, int key)
{
////const char*	XOR_MASKING_VALUE	= "This's Korea";
	//const char* XOR_MASKING_VALUE = "chyaya";
	//const int	XOR_MASKING_SIZE	= 6;
	  const char*	XOR_MASKING_VALUE	= "zhegeshixiexuede";
	  const int	XOR_MASKING_SIZE	= 16;

	if(key < 0)	key = -key;

	if(size > XOR_MASKING_SIZE)
	{
		key %= (size - XOR_MASKING_SIZE);
		
		for(int i = 0; i < XOR_MASKING_SIZE; ++i, ++key)
			data[key] ^= XOR_MASKING_VALUE[i];
	}
}


//////////////////////////////////////////////////////////////////////////////
/// @fn decode_data
///
/// 암호 풀어준다. 별거 없심
//////////////////////////////////////////////////////////////////////////////
inline void decode_data(char *data, int size, int key)
{
	encrypt_data(data, size, key);
}


//////////////////////////////////////////////////////////////////////////////
/// @fn calc_compress_buffer_size
///
/// 압축 버퍼 만들때 약간 버퍼크기를 크게 해야한다.
//////////////////////////////////////////////////////////////////////////////
inline int calc_compress_buffer_size(int size)
{
	return size + (size >> 4) + 64 + 3;
}
