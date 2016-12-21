/*
 * VRAM.h
 *
 *  Created on: 2016/11/21
 *      Author: kyon
 */

#ifndef CVRAM_H_
#define CVRAM_H_

#include "NesEngine.h"

#define NESE_MAX_VRAM_SIZE 0xFFFF

namespace NesEngine {

	class CVRAM {
	public:
		CVRAM();
		virtual ~CVRAM();

	private:
		uint8_t mem[NESE_MAX_VRAM_SIZE];
	};

}

#endif /* CVRAM_H_ */
