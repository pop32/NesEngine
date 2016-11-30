/*
 * CNesEngine.h
 *
 *  Created on: 2016/11/22
 *      Author: z1j7663
 */

#ifndef CNESENGINE_H_
#define CNESENGINE_H_

#include "NesEngine.h"
#include "CMemory.h"
#include "CVRAM.h"
#include "CCPU.h"
#include "CPPU.h"

namespace NesEngine {

	class CNesEngine {
	public:
		CNesEngine();
		virtual ~CNesEngine();

		void ExecuteCPU(void);
		void LoadROM(char* file);
		void LoadFromMemory(uint8_t* mem_);

	private:
		CMemory m_Memory;
		CVRAM m_VRAM;
		CCPU m_CPU;
		CPPU m_PPU;
	};

}

#endif /* CNESENGINE_H_ */
