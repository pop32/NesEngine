/*
 * CDecoder.cpp
 *
 *  Created on: 2016/11/25
 *      Author: kyon
 */

#include "CDecoder.h"

namespace NesEngine {

CDecoder::CDecoder(uint8_t byOpCode_, CCPU *cpCPU, CRegister *cpRegister, CMemory *cpMemory) {
	m_pCPU = cpCPU;
	m_pRegister = cpRegister;
	m_pMemory = cpMemory;
	byOpCode = byOpCode_;

	FetchExecutor = &CDecoder::Undef;
	switch (byOpCode_ & 0x0F) {
	case 0x00:
		switch (byOpCode_ & 0xF0) {
		case 0x20:
			FetchExecutor = &CDecoder::Absolute;
			break;
		case 0x60:
			FetchExecutor = &CDecoder::Implied;
			break;
		case 0xA0:
		case 0xC0:
		case 0xE0:
			FetchExecutor = &CDecoder::Immediate;
			break;
		default:
			FetchExecutor = &CDecoder::Relative;
			break;
		}
		break;

	case 0x01:
		switch (byOpCode_ & 0x10) {
		case 0x00:
			FetchExecutor = &CDecoder::IndirectX;
			break;
		case 0x10:
			FetchExecutor = &CDecoder::IndirectY;
			break;
		}
		break;

	case 0x04:
	case 0x05:
	case 0x06:
		switch (byOpCode_ & 0x10) {
		case 0x10:
			FetchExecutor = &CDecoder::ZeroPageX;
			break;
		case 0x00:
			FetchExecutor = &CDecoder::ZeroPage;
			break;
		}
		break;

	case 0x08:
		FetchExecutor = &CDecoder::Implied;
		break;

	case 0x09:
		switch (byOpCode_ & 0x10) {
		case 0x10:
			FetchExecutor = &CDecoder::AbsoluteY;
			break;
		case 0x00:
			FetchExecutor = &CDecoder::Immediate;
			break;
		}
		break;

	case 0x0A:
		switch (byOpCode_ & 0xF0) {
		case 0x00:
		case 0x20:
		case 0x40:
		case 0x60:
			FetchExecutor = &CDecoder::Accumulator;
			break;
		default:
			FetchExecutor = &CDecoder::Implied;
			break;
		}
		break;

	case 0x0C:
		switch (byOpCode_ & 0x10) {
		case 0x60:
			FetchExecutor = &CDecoder::Indirect;
			break;
		default:
			FetchExecutor = &CDecoder::Absolute;
			break;
		}
		break;

	case 0x0D:
		switch (byOpCode_ & 0x10) {
		case 0x10:
			FetchExecutor = &CDecoder::AbsoluteX;
			break;
		case 0x00:
			FetchExecutor = &CDecoder::Absolute;
			break;
		}
		break;

	case 0x0E:
		switch (byOpCode_ & 0x10) {
		case 0x00:
			FetchExecutor = &CDecoder::Absolute;
			break;
		case 0x10:
			FetchExecutor = &CDecoder::AbsoluteX;
			break;
		}
		break;

	}
}

CDecoder::~CDecoder() {

}

void CDecoder::FetchOperand(void) {
	(this->*FetchExecutor)();
}

void CDecoder::Immediate(void)
{
	m_pRegister->OPERAND = m_pMemory->GetByte(m_pRegister->GetPC());
	m_pRegister->AddPC();
}

void CDecoder::ZeroPage(void)
{
	m_pRegister->OPERAND = m_pMemory->GetByte(m_pRegister->GetPC());
	m_pRegister->AddPC();
}

void CDecoder::ZeroPageX(void)
{
	m_pRegister->OPERAND = m_pMemory->GetByte(m_pRegister->GetPC())
									+ m_pRegister->X;
	m_pRegister->AddPC();

}

void CDecoder::Absolute(void)
{
	m_pRegister->OPERAND = m_pMemory->GetWord(m_pRegister->GetPC());
	m_pRegister->AddPC(2);
}

void CDecoder::AbsoluteX(void)
{
	m_pRegister->OPERAND = m_pMemory->GetWord(m_pRegister->GetPC())
									+ m_pRegister->X;
	m_pRegister->AddPC(2);
}

void CDecoder::AbsoluteY(void)
{
	m_pRegister->OPERAND = m_pMemory->GetWord(m_pRegister->GetPC())
									+ m_pRegister->Y;
	m_pRegister->AddPC(2);
}

void CDecoder::Indirect(void)
{
	uint16_t addr;
	uint8_t lo_addr, hi_addr;
	addr = m_pMemory->GetByte(m_pRegister->GetPC());
	lo_addr = m_pMemory->GetByte(addr);
	hi_addr = m_pMemory->GetByte(addr + 1);
	m_pRegister->OPERAND = (hi_addr << 8) + lo_addr;
	m_pRegister->AddPC();

}

void CDecoder::IndirectX(void)
{
	uint16_t addr;
	uint8_t lo_addr, hi_addr;
	addr = m_pMemory->GetByte(m_pRegister->GetPC());
	lo_addr = m_pMemory->GetByte(addr + m_pRegister->X);
	hi_addr = m_pMemory->GetByte(addr + m_pRegister->X + 1);
	m_pRegister->OPERAND = (hi_addr << 8) + lo_addr;
	m_pRegister->AddPC();

}

void CDecoder::IndirectY(void)
{
	uint16_t addr;
	uint8_t lo_addr, hi_addr;
	addr = m_pMemory->GetByte(m_pRegister->GetPC());
	lo_addr = m_pMemory->GetByte(addr);
	hi_addr = m_pMemory->GetByte(addr + 1);
	m_pRegister->OPERAND = (hi_addr << 8) + lo_addr + m_pRegister->Y;
	m_pRegister->AddPC();

}

void CDecoder::Relative(void)
{
	int8_t val = m_pMemory->GetByte(m_pRegister->GetPC());
	m_pRegister->AddPC();
	m_pRegister->OPERAND = m_pRegister->GetPC() + val;
}

void CDecoder::Implied(void)
{
}

void CDecoder::Accumulator(void)
{
	m_pRegister->OPERAND = m_pRegister->A;
	m_pRegister->AddPC();
}

void CDecoder::Undef(void)
{

}



} /* namespace NesEngine */
