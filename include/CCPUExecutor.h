/*
 * CCPUExecutor.h
 *
 *  Created on: 2016/11/24
 *      Author: z1j7663
 */

#ifndef CCPUEXECUTOR_H_
#define CCPUEXECUTOR_H_

#include "CRegister.h"
#include "CMemory.h"
#include "CCPU.h"
#include "CALU.h"
#include "CDecoder.h"

namespace NesEngine {

	class CCPU;
	class CDecoder;
	class CALU;

	class CCPUExecutor {
	public:
		CCPUExecutor(uint8_t byOpCode_, CCPU *cpCPU, CRegister *cpRegister, CMemory *cpMemory);
		virtual ~CCPUExecutor();

		void Execute(void);
	private:
		CDecoder *m_pDecoder;
		CALU *m_pALU;
	};

} /* namespace NesEngine */

#endif /* CCPUEXECUTOR_H_ */
