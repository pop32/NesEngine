/*
 * CPU.cpp
 *
 *  Created on: 2016/11/21
 *      Author: z1j7663
 */

#include "CCPU.h"

namespace NesEngine {

CCPU::CCPU(CMemory *cpMemory)
{
	m_pMemory = cpMemory;
	byOpCode  = 0;
	nCycle    = 0;
	for (int i=0; i < 256; i++) {
		m_pCCPUExecutor[i] = new CCPUExecutor(i, this, &m_Register, cpMemory);
	}

}

CCPU::~CCPU()
{
	for (int i=0; i < 256; i++) {
		delete m_pCCPUExecutor[i];
	}

}

void CCPU::ExecCycle()
{
	byOpCode = m_pMemory->GetByte(m_Register.GetPC());
	m_Register.AddPC();
	AddCycle();
	m_pCCPUExecutor[byOpCode]->Execute();
}

/*
 * リセット
 */
void CCPU::Reset()
{
	m_Register.X = 0;
	m_Register.Y = 0;
	m_Register.A = 0;
	m_Register.SetPC(m_pMemory->GetWord(0xFFFC));

}


} /* namespace NesEngine */
