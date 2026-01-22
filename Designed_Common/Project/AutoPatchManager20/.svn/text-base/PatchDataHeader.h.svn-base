#pragma once

struct PatchDataHeader
{
	PatchDataHeader()
		: UncompressSize(0)
		, CompressSize(0)
		, Incompressible(0) {}

	DWORD	UncompressSize;
	DWORD	CompressSize;
	BYTE	Incompressible;
};

#define PATCHDATAHEADER_SIZE 9