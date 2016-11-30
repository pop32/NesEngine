/*
 * CPU.h
 *
 *  Created on: 2016/11/21
 *      Author: z1j7663
 */

#ifndef CCPU_H_
#define CCPU_H_

#include "NesEngine.h"
#include "CRegister.h"
#include "CCPUExecutor.h"

namespace NesEngine {

	class CCPUExecutor;

	class CCPU {
	public:
		CCPU(CMemory *cpMemory);
		virtual ~CCPU();

		void ExecCycle();
		void Reset();
		void AddCycle(int nCycle_) {
			nCycle += nCycle_;
		}
		void AddCycle() {
			nCycle++;
		}

	private:
		uint8_t byOpCode;
		int nCycle;

		CRegister m_Register;
		CMemory *m_pMemory;
		CCPUExecutor *m_pCCPUExecutor[256];

	};

} /* namespace NesEngine */

#endif /* CCPU_H_ */
