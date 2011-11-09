// coding: utf-8
// ----------------------------------------------------------------------------
/* Copyright (c) 2009, Roboterclub Aachen e.V.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Roboterclub Aachen e.V. nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ROBOTERCLUB AACHEN E.V. ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ROBOTERCLUB AACHEN E.V. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */
// ----------------------------------------------------------------------------

#ifdef __DOXYGEN__

/**
 * \brief	Compiler description
 * \ingroup	platform
 */
#define	XPCC__COMPILER_STRING

/**
 * \brief	Possible compilers
 * \ingroup	platform
 */
//@{
#define	XPCC__COMPILER_GCC
#define	XPCC__COMPILER_MSVC
//@}

/**
 * \brief	Operating system description
 * \ingroup	platform
 */
#define	XPCC__OS_STRING

/**
 * \brief	Possible operating systems
 * \ingroup	platform
 */
//@{
#define	XPCC__OS_UNIX
#define	XPCC__OS_LINUX
#define	XPCC__OS_OSX
#define	XPCC__OS_WIN32
#define	XPCC__OS_WIN64
//@}

/**
 * \brief	CPU description
 * \ingroup	platform
 */
#define	XPCC__CPU_STRING

/**
 * \brief	Possible CPU definitions
 * \ingroup	platform
 */
//@{
#define	XPCC__CPU_AVR
#define	XPCC__CPU_ATXMEGA
#define	XPCC__CPU_ATMEGA
#define	XPCC__CPU_ATTINY

#define	XPCC__CPU_ARM
#define	XPCC__CPU_ARM7TDMI
#define	XPCC__CPU_CORTEX_M3

#define	XPCC__CPU_X86
#define	XPCC__CPU_X86_64
//@}

#else //!__DOXYGEN__

// ----------------------------------------------------------------------------
// Determine compilation environment

#if defined __GNUC__
#	define XPCC__COMPILER_STRING	"Gnu GCC"
#	define XPCC__COMPILER_GCC 1
#endif

#if defined _MSC_VER
#	define XPCC__COMPILER_STRING 	"Microsoft Visual C++"
#	define XPCC__COMPILER_MSVC 1
#endif

#if !defined XPCC__COMPILER_STRING
#	define XPCC__COMPILER_STRING 	"Unknown compiler"
#	warning	"Couldn't determine the used compiler! Please add it to <xpcc/architecture/detect.hpp>"
#endif

// ----------------------------------------------------------------------------
// Determine target operating system

#if defined linux || defined __linux__
#	define XPCC__OS_LINUX 1 
#	define XPCC__OS_STRING 			"Linux"
#endif

#if (defined __MWERKS__ && defined __powerc && !defined macintosh) || defined __APPLE_CC__ || defined macosx
#	define XPCC__OS_OSX 1
#	define XPCC__OS_STRING			"MacOS X"
#endif

#if defined __unix__
#	define XPCC__OS_UNIX 1 
#	if !defined XPCC__OS_STRING
#		define XPCC__OS_STRING 		"Unix-like(generic)"
#	endif
#endif

#if defined _WIN32 || defined WIN32 || defined __NT__ || defined __WIN32__
#	define XPCC__OS_WIN32 1
#	if defined _WIN64
#		define XPCC__OS_WIN64 1
#		define XPCC__OS_STRING		"Win64"
#	else
#		if !defined XPCC__OS_STRING
#			define XPCC__OS_STRING	"Win32"
#		endif
#	endif
#endif

// ----------------------------------------------------------------------------
// Determine 

#if defined __AVR__
#	define	XPCC__CPU_AVR 1
#	if defined __AVR_XMEGA__
#		define XPCC__CPU_ATXMEGA 1
#		define XPCC__CPU_STRING		"Atmel XMEGA"
#	else
		// see http://www.nongnu.org/avr-libc/user-manual/using__tools.html
#		if __AVR_ARCH__ == 2 || __AVR_ARCH__ == 25 || __AVR_ARCH__ == 1
#			define XPCC__CPU_ATTINY 1
#			define XPCC__CPU_STRING	"Atmel tinyAVR"
#		else
#			define XPCC__CPU_ATMEGA 1
#			define XPCC__CPU_STRING	"Atmel megaAVR"
#		endif
#	endif
#endif

#if defined __X86__ || defined __i386__ || defined i386 || defined _M_IX86 || defined __386__ || defined __x86_64__ || defined _M_X64
#	define XPCC__CPU_X86 1
#	if defined __x86_64__ || defined _M_X64
#		define XPCC__CPU_X86_64 1
#		define XPCC__CPU_STRING		"AMD x86-64"
#	else
#		define XPCC__CPU_STRING		"Intel 386+"
#	endif
#endif

#if defined __arm__
#	define XPCC__CPU_ARM 1
#	if defined __ARM_ARCH_4T__
#		define XPCC__CPU_ARM7TDMI 1
#		define XPCC__CPU_STRING		"ARM7TDMI"
#	elif defined __ARM_ARCH_7M__
#		define XPCC__CPU_CORTEX_M3 1
#		define XPCC__CPU_STRING		"Cortex M3"
#	endif
#endif

#if !defined XPCC__CPU_STRING
#	error "Couldn't determine target CPU!"
#	define XPCC__CPU_STRING 		"Unknown"
#endif

// windows lacks support for some macros c99 we need to provide here
#if defined XPCC__OS_WIN32
#	include "platform/x86/windows.hpp"
#endif

#endif	// !__DOXYGEN__
