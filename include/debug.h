/*
 * debug.h
 *
 *  Created on: 2016/11/25
 *      Author: z1j7663
 */

#ifdef __DEBUG__
#define DebugPrint(...) {printf("%s(%d):", __func__, __LINE__); printf(__VA_ARGS__);}
#else
#define DebugPrint(...)
#endif
