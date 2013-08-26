//
//  k2_platform.h
//  K2
//
//  Created by Justin Bowes on 2013-08-22.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#ifndef K2_k2_platform_h
#define K2_k2_platform_h

#define K2_INLINE static inline

#ifdef _WIN64
#	define K2_PLATFORM_WINDOWS
#	define K2_WORDSIZE 64
#	define K2_ENDIAN_LITTLE
#elif _WIN32
#	define K2_PLATFORM_WINDOWS
#	define K2_WORDSIZE
#	define K2_ENDIAN_LITTLE
#elif __APPLE__
#	define K2_PLATFORM_APPLE
#	define K2_PLATFORM_BSD
#	define K2_PLATFORM_POSIX
#	include "TargetConditionals.h"
#	if TARGET_IPHONE_SIMULATOR
#		define K2_PLATFORM_IOS
#		define K2_WORDSIZE 32
#		define K2_ENDIAN_LITTLE
#	elif TARGET_OS_IPHONE
#		define K2_PLATFORM_IOS
#		define K2_WORDSIZE 32
#		define K2_ENDIAN_BIG
#	elif TARGET_OS_MAC
#		include <limits.h>
#		define K2_PLATFORM_OSX
#		define K2_WORDSIZE __WORDSIZE
#		define K2_ENDIAN_LITTLE
#	else
#		error "Unidentified APPLE platform"
#	endif
#elif __linux
#	define K2_PLATFORM_POSIX
#	define K2_PLATFORM_LINUX
#elif __unix 
#	define K2_PLATFORM_POSIX
#	define K2_PLATFORM_UNIX
#elif __posix
#	define K2_PLATFORM_POSIX
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef K2_PLATFORM_WINDOWS
#   include <limits.h>
#   ifndef SIZE_T_MAX
#       define SIZE_T_MAX SIZE_MAX
#   endif
#endif

#endif