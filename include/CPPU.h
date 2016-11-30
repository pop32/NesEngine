/*
 * PPU.h
 *
 *  Created on: 2016/11/21
 *      Author: z1j7663
 */

#ifndef CPPU_H_
#define CPPU_H_

#include "NesEngine.h"
#include "CVRAM.h"

namespace NesEngine {

	class CPPU {
	public:
		CPPU(CVRAM *pcVRAM);
		virtual ~CPPU();

	private:
		CVRAM* pm_VRAM;
	};

}

#endif /* CPPU_H_ */
