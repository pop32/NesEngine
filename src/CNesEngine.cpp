/*
 * CNesEngine.cpp
 *
 *  Created on: 2016/11/22
 *      Author: z1j7663
 */

#include "CNesEngine.h"

namespace NesEngine {


CNesEngine::CNesEngine() : m_CPU(&m_Memory),m_PPU(&m_VRAM)  {
	// TODO 自動生成されたコンストラクター・スタブ

}

CNesEngine::~CNesEngine() {
	// TODO Auto-generated destructor stub
}

void CNesEngine::ExecuteCPU(void)
{
	m_CPU.ExecCycle();
}

void CNesEngine::LoadROM(char* file)
{
	m_Memory.LoadROM(file);
}

void CNesEngine::LoadFromMemory(uint8_t* mem_)
{
	m_Memory.LoadFromMemory(mem_);
	m_CPU.Reset();
}


} /* namespace NesEngine */
