/*
 * PPU.cpp
 *
 *  Created on: 2016/11/21
 *      Author: z1j7663
 */

#include "CPPU.h"

namespace NesEngine {


CPPU::CPPU(CVRAM *pcVRAM)
{
	pm_VRAM = pcVRAM;

}

CPPU::~CPPU()
{

}

} /* namespace NesEngine */
