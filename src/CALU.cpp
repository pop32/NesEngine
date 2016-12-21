/*
 * CALU.cpp
 *
 *  Created on: 2016/11/22
 *      Author: kyon
 */

#include "CALU.h"

namespace NesEngine {

CALU::CALU(uint8_t byOpCode_, CCPU *cpCPU, CRegister *cpRegister, CMemory *cpMemory) {
	m_pCPU = cpCPU;
	m_pRegister = cpRegister;
	m_pMemory = cpMemory;
	byOpCode = byOpCode_;

	Executor = &CALU::UNDEF;
	switch (byOpCode_ & 0xF0) {

	case 0x00:
	case 0x10:
		switch (byOpCode_ & 0x0F) {
		case 0x06:
		case 0x0E:
			Executor = &CALU::ASL;
			break;
		case 0x01:
		case 0x05:
		case 0x09:
		case 0x0D:
			Executor = &CALU::ORA;
			break;
		default:
			switch (byOpCode_) {
			case 0x0A:
				Executor = &CALU::ASL;
				break;
			case 0x00:
				Executor = &CALU::BRK;
				break;
			case 0x08:
				Executor = &CALU::PHP;
				break;
			case 0x10:
				Executor = &CALU::BPL;
				break;
			case 0x18:
				Executor = &CALU::CLC;
				break;
			}
		}
		break;

	case 0x20:
	case 0x30:
		switch (byOpCode_ & 0x0F) {
		case 0x06:
		case 0x0E:
			Executor = &CALU::ROL;
			break;
		case 0x01:
		case 0x05:
		case 0x09:
		case 0x0D:
			Executor = &CALU::AND;
			break;
		default:
			switch (byOpCode_) {
			case 0x20:
				Executor = &CALU::JSR;
				break;
			case 0x24:
			case 0x2C:
				Executor = &CALU::BIT;
				break;
			case 0x28:
				Executor = &CALU::PLP;
				break;
			case 0x2A:
				Executor = &CALU::ROL;
				break;
			case 0x30:
				Executor = &CALU::BMI;
				break;
			case 0x38:
				Executor = &CALU::SEC;
				break;
			}
		}
		break;

	case 0x40:
	case 0x50:
		switch (byOpCode_ & 0x0F) {
		case 0x06:
		case 0x0E:
			Executor = &CALU::LSR;
			break;
		case 0x01:
		case 0x05:
		case 0x09:
		case 0x0D:
			Executor = &CALU::EOR;
			break;
		default:
			switch (byOpCode_) {
			case 0x4A:
				Executor = &CALU::LSR;
				break;
			case 0x40:
				Executor = &CALU::RTI;
				break;
			case 0x48:
				Executor = &CALU::PHA;
				break;
			case 0x4C:
				Executor = &CALU::JMP;
				break;
			case 0x50:
				Executor = &CALU::BVC;
				break;
			case 0x58:
				Executor = &CALU::CLI;
				break;
			}
			break;
		}
		break;

	case 0x60:
	case 0x70:
		switch (byOpCode_ & 0x0F) {
		case 0x06:
		case 0x0E:
			Executor = &CALU::ROL;
			break;
		case 0x01:
		case 0x05:
		case 0x09:
		case 0x0D:
			Executor = &CALU::ADC;
			break;
		default:
			switch (byOpCode_) {
			case 0x60:
				Executor = &CALU::RTS;
				break;
			case 0x68:
				Executor = &CALU::PLA;
				break;
			case 0x6A:
				Executor = &CALU::ROL;
				break;
			case 0x6C:
				Executor = &CALU::JMP;
				break;
			}
		}
		break;

	case 0x80:
	case 0x90:
		switch (byOpCode_ & 0x0F) {
		case 0x01:
		case 0x05:
		case 0x09:
		case 0x0D:
			Executor = &CALU::STA;
			break;
		case 0x06:
			Executor = &CALU::STX;
			break;
		case 0x04:
			Executor = &CALU::STY;
			break;
		default:
			switch (byOpCode_) {
			case 0x88:
				Executor = &CALU::DEY;
				break;
			case 0x8A:
				Executor = &CALU::TXA;
				break;
			case 0x8C:
				Executor = &CALU::STY;
				break;
			case 0x8E:
				Executor = &CALU::STX;
				break;
			case 0x98:
				Executor = &CALU::TYA;
				break;
			case 0x9A:
				Executor = &CALU::TXS;
				break;
			}
			break;
		}
		break;

	case 0xA0:
	case 0xB0:
		switch (byOpCode_ & 0x0F) {
		case 0x01:
		case 0x05:
		case 0x09:
		case 0x0D:
			Executor = &CALU::LDA;
			break;
		case 0x06:
		case 0x0E:
			Executor = &CALU::LDX;
			break;
		case 0x04:
		case 0x0C:
			Executor = &CALU::LDY;
			break;
		default:
			switch (byOpCode_) {
			case 0xA0:
				Executor = &CALU::LDY;
				break;
			case 0xA2:
				Executor = &CALU::LDX;
				break;
			case 0xA8:
				Executor = &CALU::TAY;
				break;
			case 0xAA:
				Executor = &CALU::TAX;
				break;
			case 0xB0:
				Executor = &CALU::BCS;
				break;
			case 0xB8:
				Executor = &CALU::CLV;
				break;
			case 0xBA:
				Executor = &CALU::TSX;
				break;
			}
			break;
		}
		break;

	case 0xC0:
	case 0xD0:
		switch (byOpCode_ & 0x0F) {
		case 0x01:
		case 0x05:
		case 0x09:
		case 0x0D:
			Executor = &CALU::CMP;
			break;
		case 0x06:
		case 0x0E:
			Executor = &CALU::DEC;
			break;
		default:
			switch (byOpCode_) {
			case 0xCA:
				Executor = &CALU::DEX;
				break;
			case 0xC8:
				Executor = &CALU::INY;
				break;
			case 0xD8:
				Executor = &CALU::INY;
				break;
			}
			break;
		}
		break;

	case 0xE0:
	case 0xF0:
		switch (byOpCode_ & 0x0F) {
		case 0x01:
		case 0x05:
		case 0x09:
		case 0x0D:
			Executor = &CALU::SBC;
			break;
		case 0x06:
		case 0x0E:
			Executor = &CALU::INC;
			break;
		default:
			switch (byOpCode_) {
			case 0xE0:
			case 0xE4:
			case 0xEC:
				Executor = &CALU::CPX;
				break;
			case 0xE8:
				Executor = &CALU::INX;
				break;
			case 0xEA:
				Executor = &CALU::NOP;
				break;
			case 0xF0:
				Executor = &CALU::BEQ;
				break;
			case 0xF8:
				Executor = &CALU::SED;
				break;
			}
			break;
		}
		break;
	}

}

CALU::~CALU() {

}

void CALU::ExecuteOpcode(void)
{
	(this->*Executor)();
}

void CALU::ADC(void)
{
	uint8_t prev = m_pRegister->A;
	uint8_t val = m_pRegister->OPERAND + m_pRegister->GetCarryFlg();
	m_pRegister->A = prev + val;
	m_pRegister->SetNZFlg(m_pRegister->A);
	m_pRegister->SetCarryFlgAdd(prev, val, m_pRegister->A);
	m_pRegister->SetOverFlowFlg(prev, val, m_pRegister->A);
}

void CALU::SBC(void)
{
	uint8_t prev = m_pRegister->A;
	uint8_t val = m_pRegister->OPERAND + m_pRegister->GetNotCarryFlg();
	m_pRegister->A = m_pRegister->A - val;
	m_pRegister->SetNZFlg(m_pRegister->A);
	m_pRegister->SetCarryFlgSub(prev, m_pRegister->A);
	m_pRegister->SetOverFlowFlg(prev, val, m_pRegister->A);
}

void CALU::AND(void)
{
	m_pRegister->A &= m_pRegister->OPERAND;
}

void CALU::ORA(void)
{
	m_pRegister->A |= m_pRegister->OPERAND;
}

void CALU::EOR(void)
{
	m_pRegister->A ^= m_pRegister->OPERAND;
}

void CALU::ASL(void)
{
	m_pRegister->A <<= 1;
	m_pRegister->SetNZFlg(m_pRegister->A);
	m_pRegister->SetCarryFlg(m_pRegister->A & 0x80);
}

void CALU::LSR(void)
{
	m_pRegister->A >>= 1;
	m_pRegister->SetNZFlg(m_pRegister->A);
	m_pRegister->SetCarryFlg(m_pRegister->A & 0x01);
}

void CALU::ROL(void)
{
	m_pRegister->A <<= 1;
	m_pRegister->A |= ((m_pRegister->A & 0xFE) | m_pRegister->GetCarryFlg());
	m_pRegister->SetNZFlg(m_pRegister->A);
	m_pRegister->SetCarryFlg(m_pRegister->A & 0x80);
}

void CALU::ROR(void)
{
	m_pRegister->A >>= 1;
	m_pRegister->A |= ((m_pRegister->A & 0xEF) | (m_pRegister->GetCarryFlg() << 8));
	m_pRegister->SetNZFlg(m_pRegister->A);
	m_pRegister->SetCarryFlg(m_pRegister->A & 0x80);
}

void CALU::BCC(void)
{
	if (!m_pRegister->IsCarryFlg()) {
		m_pRegister->SetPC(m_pRegister->OPERAND);
	}
}

void CALU::BCS(void)
{
	if (m_pRegister->IsCarryFlg()) {
		m_pRegister->SetPC(m_pRegister->OPERAND);
	}
}

void CALU::BEQ(void)
{
	if (m_pRegister->IsZeroFlg()) {
		m_pRegister->SetPC(m_pRegister->OPERAND);
	}
}

void CALU::BNE(void)
{
	if (!m_pRegister->IsZeroFlg()) {
		m_pRegister->SetPC(m_pRegister->OPERAND);
	}
}

void CALU::BVC(void)
{
	if (!m_pRegister->IsOverFlowFlg()) {
		m_pRegister->SetPC(m_pRegister->OPERAND);
	}
}

void CALU::BVS(void)
{
	if (m_pRegister->IsOverFlowFlg()) {
		m_pRegister->SetPC(m_pRegister->OPERAND);
	}
}

void CALU::BPL(void)
{
	if (!m_pRegister->IsNegativeFlg()) {
		m_pRegister->SetPC(m_pRegister->OPERAND);
	}
}

void CALU::BMI(void)
{
	if (m_pRegister->IsNegativeFlg()) {
		m_pRegister->SetPC(m_pRegister->OPERAND);
	}
}

void CALU::BIT(void)
{
	int8_t result = m_pRegister->A & m_pRegister->OPERAND;
	m_pRegister->SetNZFlg(result);
	m_pRegister->SetCarryFlg( ((result & 0x40) == 0x10) );
}

void CALU::JMP(void)
{
	m_pRegister->SetPC(m_pRegister->OPERAND);
}

void CALU::JSR(void)
{

}

void CALU::RTS(void)
{

}

void CALU::BRK(void)
{

}

void CALU::RTI(void)
{

}

void CALU::CMP(void)
{

}

void CALU::CPX(void)
{

}

void CALU::CPY(void)
{

}

void CALU::INC(void)
{
	m_pRegister->A++;
	m_pRegister->SetNZFlg(m_pRegister->A);
}

void CALU::DEC(void)
{
	m_pRegister->A--;
	m_pRegister->SetNZFlg(m_pRegister->A);
}

void CALU::INX(void)
{
	m_pRegister->X++;
	m_pRegister->SetNZFlg(m_pRegister->X);
}

void CALU::DEX(void)
{
	m_pRegister->X--;
	m_pRegister->SetNZFlg(m_pRegister->X);
}

void CALU::INY(void)
{
	m_pRegister->Y++;
	m_pRegister->SetNZFlg(m_pRegister->Y);
}

void CALU::DEY(void)
{
	m_pRegister->Y--;
	m_pRegister->SetNZFlg(m_pRegister->Y);
}

void CALU::CLC(void)
{
	m_pRegister->SetCarryFlg();
}

void CALU::SEC(void)
{
	m_pRegister->ClearCarryFlg();
}

void CALU::CLI(void)
{

}

void CALU::SEI(void)
{

}

void CALU::CLD(void)
{

}

void CALU::SED(void)
{

}

void CALU::CLV(void)
{

}

void CALU::LDA(void)
{
	m_pRegister->A = (uint8_t)m_pRegister->OPERAND;
	m_pRegister->SetNZFlg(m_pRegister->A);
}

void CALU::LDX(void)
{
	m_pRegister->X = (uint8_t)m_pRegister->OPERAND;
	m_pRegister->SetNZFlg(m_pRegister->X);
}

void CALU::LDY(void)
{
	m_pRegister->Y = (uint8_t)m_pRegister->OPERAND;
	m_pRegister->SetNZFlg(m_pRegister->Y);
}

void CALU::STA(void)
{
	m_pMemory->SetByte(m_pRegister->OPERAND, m_pRegister->A);
}

void CALU::STX(void)
{
	m_pMemory->SetByte(m_pRegister->OPERAND, m_pRegister->X);
}

void CALU::STY(void)
{
	m_pMemory->SetByte(m_pRegister->OPERAND, m_pRegister->Y);
}

void CALU::TAX(void)
{
	m_pRegister->X = m_pRegister->A;
}

void CALU::TXA(void)
{
	m_pRegister->A = m_pRegister->X;

}

void CALU::TAY(void)
{
	m_pRegister->Y = m_pRegister->A;

}

void CALU::TYA(void)
{
	m_pRegister->A = m_pRegister->Y;

}

void CALU::TXS(void)
{
	m_pRegister->S = m_pRegister->X;

}

void CALU::TSX(void)
{
	m_pRegister->X = m_pRegister->S;

}

void CALU::PHA(void)
{

}

void CALU::PLA(void)
{

}

void CALU::PHP(void)
{

}

void CALU::PLP(void)
{

}

void CALU::NOP(void)
{

}

void CALU::UNDEF(void)
{

}


} /* namespace NesEngine */
