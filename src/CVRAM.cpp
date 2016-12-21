/*
 * VRAM.cpp
 *
 *  Created on: 2016/11/21
 *      Author: kyon
 */

#include "CVRAM.h"

namespace NesEngine {


CVRAM::CVRAM()
{
	memset(mem, 0, sizeof(mem));
}

CVRAM::~CVRAM()
{
	// TODO Auto-generated destructor stub
}

} /* namespace NesEngine */
