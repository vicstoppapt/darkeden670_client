#include <windows.h>
#include <string>
#include <stdio.h>
#include "\crypto\crc.h"
#include "misc.h"

using namespace CryptoPP;

std::string GetHashCode(const char* filename)
{	
	byte *data;
	FILE *fp=fopen("e:\\darkedentest\\darkeden.exe","rb");
	fseek(fp,0,SEEK_END);
	unsigned int size = ftell(fp);
	fseek(fp,0,SEEK_SET);
	data = new byte[size];
	fread(data,1,size,fp);
	fclose(fp);
	CRC32 crc;	

	bool pass=true, fail;
	SecByteBlock digest(crc.DigestSize());

	unsigned j;
	
	crc.Update(data,size);
	crc.Final(digest);
	fail = memcmp(digest, &size, crc.DigestSize()) != 0;
	pass = pass && !fail;
	
	cout << (fail ? "FAILED   " : "passed   ");
	for (j=0; j<crc.DigestSize(); j++)
		cout << hex << (int)digest[j];
		//cout << setw(2) << setfill('0') << hex << (int)digest[j];
//	cout << "   \"" << (char *)testSet[i].input << '\"';
	cout  << endl;
	return "";
}