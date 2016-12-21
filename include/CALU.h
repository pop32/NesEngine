/*
 * CALU.h
 *
 *  Created on: 2016/11/22
 *      Author: kyon
 */

#ifndef CALU_H_
#define CALU_H_

#include "NesEngine.h"
#include "CRegister.h"
#include "CMemory.h"
#include "CCPU.h"


namespace NesEngine {

	class CCPU;

	class CALU {
	public:
		CALU(uint8_t byOpCode_, CCPU *cpCPU, CRegister *cpRegister, CMemory *cpMemory);
		virtual ~CALU();

		void ExecuteOpcode(void);

	private:
		CCPU *m_pCPU;
		CRegister *m_pRegister;
		CMemory *m_pMemory;

		uint8_t byOpCode;

		void (CALU::*Executor)(void);

		void ADC(void);
		void SBC(void);
		void AND(void);
		void ORA(void);
		void EOR(void);
		void ASL(void);
		void LSR(void);
		void ROL(void);
		void ROR(void);
		void BCC(void);
		void BCS(void);
		void BEQ(void);
		void BNE(void);
		void BVC(void);
		void BVS(void);
		void BPL(void);
		void BMI(void);
		void BIT(void);
		void JMP(void);
		void JSR(void);
		void RTS(void);
		void BRK(void);
		void RTI(void);
		void CMP(void);
		void CPX(void);
		void CPY(void);
		void INC(void);
		void DEC(void);
		void INX(void);
		void DEX(void);
		void INY(void);
		void DEY(void);
		void CLC(void);
		void SEC(void);
		void CLI(void);
		void SEI(void);
		void CLD(void);
		void SED(void);
		void CLV(void);
		void LDA(void);
		void LDX(void);
		void LDY(void);
		void STA(void);
		void STX(void);
		void STY(void);
		void TAX(void);
		void TXA(void);
		void TAY(void);
		void TYA(void);
		void TXS(void);
		void TSX(void);
		void PHA(void);
		void PLA(void);
		void PHP(void);
		void PLP(void);
		void NOP(void);
		void UNDEF(void);
	};

} /* namespace NesEngine */

#endif /* CALU_H_ */
