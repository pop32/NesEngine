/*
 * Memory.h
 *
 *  Created on: 2016/11/21
 *      Author: z1j7663
 */

#ifndef CMEMORY_H_
#define CMEMORY_H_

#include "NesEngine.h"

#define NESE_MAX_ROM_SIZE 0xFFFF

namespace NesEngine {

	class CMemory {
	public:
		CMemory();
		virtual ~CMemory();

		void LoadROM(char* file);
		void LoadFromMemory(uint8_t* mem_);
		uint8_t GetByte(uint16_t wAddr);
		uint16_t GetWord(uint16_t wAddr);
		void SetByte(uint16_t wAddr, uint8_t byVal);

	private:
		uint8_t mem[NESE_MAX_ROM_SIZE];
	};

}

#endif /* CMEMORY_H_ */
