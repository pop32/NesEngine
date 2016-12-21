/*
 * PPU.cpp
 *
 *  Created on: 2016/11/21
 *      Author: kyon
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
