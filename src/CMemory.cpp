/*
 * Memory.cpp
 *
 *  Created on: 2016/11/21
 *      Author: z1j7663
 */

#include "CMemory.h"

namespace NesEngine {


CMemory::CMemory()
{
	memset(mem, 0, sizeof(mem));

}

CMemory::~CMemory()
{

}


void CMemory::LoadROM(char* file)
{
	FILE* fp;
	if ((fp = fopen(file, "rb")) == NULL) {
		return;
	}
	fread(mem + 0x8000, sizeof(char), 0x7FFF, fp);

	fclose(fp);
}

void CMemory::LoadFromMemory(uint8_t* mem_)
{
	memcpy(mem + 0x8000, mem_ + 0x10, 0x7FFF);
//	DebugPrint("mem 0x8000:%x\n", mem[0x8000]);
//	DebugPrint("mem 0x8001:%x\n", mem[0x8001]);
//	DebugPrint("mem 0x8002:%x\n", mem[0x8002]);
//
//	DebugPrint("mem 0xFFFD:%x\n", mem[0xFFFD]);
//	DebugPrint("mem 0xFFFC:%x\n", mem[0xFFFC]);
}

uint8_t CMemory::GetByte(uint16_t wAddr)
{
	return mem[wAddr];
}


uint16_t CMemory::GetWord(uint16_t wAddr)
{
	uint16_t ret = 0;
	ret = (mem[wAddr+1] << 8) + mem[wAddr];
	return ret;
}

void CMemory::SetByte(uint16_t wAddr, uint8_t byVal)
{
	mem[wAddr] = byVal;
}


} /* namespace NesEngine */
