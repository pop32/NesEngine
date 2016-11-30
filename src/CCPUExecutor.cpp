/*
 * CCPUExecutor.cpp
 *
 *  Created on: 2016/11/24
 *      Author: z1j7663
 */

#include "CCPUExecutor.h"

namespace NesEngine {


CCPUExecutor::CCPUExecutor(uint8_t byOpCode_, CCPU *cpCPU, CRegister *cpRegister, CMemory *cpMemory) {
	m_pDecoder = new CDecoder(byOpCode_, cpCPU, cpRegister, cpMemory);
	m_pALU = new CALU(byOpCode_, cpCPU, cpRegister, cpMemory);
}

CCPUExecutor::~CCPUExecutor() {
	delete m_pDecoder;
	delete m_pALU;
}

void CCPUExecutor::Execute(void)
{
	m_pDecoder->FetchOperand();
	m_pALU->ExecuteOpcode();
}


} /* namespace NesEngine */
