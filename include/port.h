/*
 * port.h
 *
 *  Created on: 2016/11/21
 *      Author: z1j7663
 */

#ifndef PORT_H_
#define PORT_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#ifndef __LIBRETRO__
#include <memory.h>
#endif
#include <time.h>
#include <string.h>
#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif
#include <sys/types.h>

#ifdef __WIN32__
#define NOMINMAX
#include <windows.h>
#endif

#ifndef nesengine_types_defined
#define nesengine_types_defined
typedef unsigned char		bool8;
#ifdef HAVE_STDINT_H
#include <stdint.h>
typedef intptr_t				pint;
typedef int8_t					int8;
typedef uint8_t				uint8;
typedef int16_t				int16;
typedef uint16_t				uint16;
typedef int32_t				int32;
typedef uint32_t				uint32;
typedef int64_t				int64;
typedef uint64_t				uint64;
#else	// HAVE_STDINT_H
#ifdef __WIN32__
typedef intptr_t				pint;
typedef signed char			int8;
typedef unsigned char		uint8;
typedef signed short			int16;
typedef unsigned short		uint16;
typedef signed int     		int32;
typedef unsigned int			uint32;
typedef signed __int64		int64;
typedef unsigned __int64		uint64;
typedef int8					int8_t;
typedef uint8					uint8_t;
typedef int16					int16_t;
typedef uint16					uint16_t;
typedef int32					int32_t;
typedef uint32					uint32_t;
typedef int64					int64_t;
typedef uint64					uint64_t;
typedef int					socklen_t;
#else	// __WIN32__
typedef signed char			int8;
typedef unsigned char		uint8;
typedef signed short			int16;
typedef unsigned short		uint16;
typedef signed int			int32;
typedef unsigned int			uint32;
#ifdef __GNUC__
// long long is not part of ISO C++
__extension__
#endif
typedef long long				int64;
typedef unsigned long long	uint64;
#ifdef PTR_NOT_INT
typedef long					pint;
#else   // __PTR_NOT_INT
typedef int					pint;
#endif  // __PTR_NOT_INT
#endif	//  __WIN32__
#endif	// HAVE_STDINT_H
#endif	// nesengine_types_defined

#ifndef TRUE
#define TRUE	1
#endif
#ifndef FALSE
#define FALSE	0
#endif

#endif /* PORT_H_ */
