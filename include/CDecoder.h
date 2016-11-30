/*
 * CDecoder.h
 *
 *  Created on: 2016/11/25
 *      Author: z1j7663
 */

#ifndef CDECODER_H_
#define CDECODER_H_
#include "NesEngine.h"

#include "CRegister.h"
#include "CMemory.h"
#include "CCPU.h"

namespace NesEngine {

	class CCPU;

	class CDecoder {
	public:
		CDecoder(uint8_t byOpCode_, CCPU *cpCPU, CRegister *cpRegister, CMemory *cpMemory);
		virtual ~CDecoder();

		void FetchOperand(void);

	private:
		CCPU *m_pCPU;
		CRegister *m_pRegister;
		CMemory *m_pMemory;
		uint8_t byOpCode;

		void (CDecoder::*FetchExecutor)(void);
		void Immediate(void);
		void ZeroPage(void);
		void ZeroPageX(void);
		void Absolute(void);
		void AbsoluteX(void);
		void AbsoluteY(void);
		void Indirect(void);
		void IndirectX(void);
		void IndirectY(void);
		void Relative(void);
		void Implied(void);
		void Accumulator(void);
		void Undef(void);

	};

} /* namespace NesEngine */

#endif /* CDECODER_H_ */
