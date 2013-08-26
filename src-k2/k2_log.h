//
//  k2_log.h
//  K2
//
//  Created by Justin Bowes on 2013-08-22.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//
// Logging code. Use as printf. LOG_DEBUG("My integer: %d", 6);
// Uses ANSI color formatting where it should work (i.e. linux).

#ifndef K2_k2_log_h
#define K2_k2_log_h

#include "k2_platform.h"

#include <stdio.h>

// ----------- logging ----------------------
#define K2_LOG_LEVEL_TRACE             0
#define K2_LOG_LEVEL_DEBUG             1
#define K2_LOG_LEVEL_INFO              2
#define K2_LOG_LEVEL_WARN              3
#define K2_LOG_LEVEL_ERROR             4

#define K2_LOG_LEVEL_OFF               999
#define K2_LOG_LEVEL_ALL               K2_LOG_LEVEL_TRACE

#ifdef DEBUG
#define K2_LOG_LEVEL					K2_LOG_LEVEL_DEBUG
#endif

#ifndef K2_LOG_LEVEL
#define K2_LOG_LEVEL                   K2_LOG_LEVEL_INFO
#endif

#define LOG_ANSI

#include <libgen.h>
#if defined(K2_PLATFORM_OSX) || defined(K2_PLATFORM_IOS) || defined(K2_PLATFORM_WINDOWS)
# undef LOG_ANSI
#endif

#if defined(K2_PLATFORM_UNIX) || defined(K2_PLATFORM_OSX) || defined(K2_PLATFORM_IOS)
# define K2_STDERR stderr
# define K2_STDOUT stdout
#endif

#if !defined(LOG_ANSI)
#define __func__ __FUNCTION__
#define K2_COLOR_txtblk ""
#define K2_COLOR_txtred ""
#define K2_COLOR_txtgrn ""
#define K2_COLOR_txtylw ""
#define K2_COLOR_txtblu ""
#define K2_COLOR_txtpur ""
#define K2_COLOR_txtcyn ""
#define K2_COLOR_txtwht ""
#define K2_COLOR_bldblk ""
#define K2_COLOR_bldred ""
#define K2_COLOR_bldgrn ""
#define K2_COLOR_bldylw ""
#define K2_COLOR_bldblu ""
#define K2_COLOR_bldpur ""
#define K2_COLOR_bldcyn ""
#define K2_COLOR_bldwht ""
#define K2_COLOR_undblk ""
#define K2_COLOR_undred ""
#define K2_COLOR_undgrn ""
#define K2_COLOR_undylw ""
#define K2_COLOR_undblu ""
#define K2_COLOR_undpur ""
#define K2_COLOR_undcyn ""
#define K2_COLOR_undwht ""
#define K2_COLOR_bakblk ""
#define K2_COLOR_bakred ""
#define K2_COLOR_bakgrn ""
#define K2_COLOR_bakylw ""
#define K2_COLOR_bakblu ""
#define K2_COLOR_bakpur ""
#define K2_COLOR_bakcyn ""
#define K2_COLOR_bakwht ""
#define K2_COLOR_txtrst ""

#else
#define K2_COLOR_txtblk "\033[0;30m"
#define K2_COLOR_txtred "\033[0;31m"
#define K2_COLOR_txtgrn "\033[0;32m"
#define K2_COLOR_txtylw "\033[0;33m"
#define K2_COLOR_txtblu "\033[0;34m"
#define K2_COLOR_txtpur "\033[0;35m"
#define K2_COLOR_txtcyn "\033[0;36m"
#define K2_COLOR_txtwht "\033[0;37m"
#define K2_COLOR_bldblk "\033[1;30m"
#define K2_COLOR_bldred "\033[1;31m"
#define K2_COLOR_bldgrn "\033[1;32m"
#define K2_COLOR_bldylw "\033[1;33m"
#define K2_COLOR_bldblu "\033[1;34m"
#define K2_COLOR_bldpur "\033[1;35m"
#define K2_COLOR_bldcyn "\033[1;36m"
#define K2_COLOR_bldwht "\033[1;37m"
#define K2_COLOR_undblk "\033[4;30m"
#define K2_COLOR_undred "\033[4;31m"
#define K2_COLOR_undgrn "\033[4;32m"
#define K2_COLOR_undylw "\033[4;33m"
#define K2_COLOR_undblu "\033[4;34m"
#define K2_COLOR_undpur "\033[4;35m"
#define K2_COLOR_undcyn "\033[4;36m"
#define K2_COLOR_undwht "\033[4;37m"
#define K2_COLOR_bakblk "\033[40m"
#define K2_COLOR_bakred "\033[41m"
#define K2_COLOR_bakgrn "\033[42m"
#define K2_COLOR_bakylw "\033[43m"
#define K2_COLOR_bakblu "\033[44m"
#define K2_COLOR_bakpur "\033[45m"
#define K2_COLOR_bakcyn "\033[46m"
#define K2_COLOR_bakwht "\033[47m"
#define K2_COLOR_txtrst "\033[0m"
#define K2_STDERR stderr
#define K2_STDOUT stdout
#endif

#if (K2_LOG_LEVEL < K2_LOG_LEVEL_OFF)
#define K2_LOG_MAX 16384
extern char ___k2_log_output[K2_LOG_MAX];
#	ifdef K2_PLATFORM_WINDOWS
char *k2_basename(const char *name);
/* MinGW points to _iob which the IDEs don't like */
#		define k2_log(stream, color, level, file, func, line, ...) \
do { printf("[%s]\t %s %s:%d %s\n", level, k2_basename(file), func, line, (snprintf(___k2_log_output, K2_LOG_MAX, __VA_ARGS__), ___k2_log_output)); fflush(stdout); } while (0)
#	else
#		define k2_log(stream, color, level, file, func, line, ...) \
do { fprintf(stream, "[%s%s%s]\t %s %s:%d %s\n", color, level, K2_COLOR_txtrst, basename(file), func, line, (snprintf(___k2_log_output, K2_LOG_MAX, __VA_ARGS__), ___k2_log_output)); fflush(stream); } while (0)
#	endif
#else
#define k2_log(s, c, lv, f, fn, ln, ...)
#endif

#if (K2_LOG_LEVEL <= K2_LOG_LEVEL_TRACE)
#define LOG_TRACE(...)               k2_log(K2_STDOUT, K2_COLOR_txtrst K2_COLOR_txtwht, "trace", __FILE__, __func__, __LINE__, __VA_ARGS__)
#else
#define LOG_TRACE(...)
#endif

#if (K2_LOG_LEVEL <= K2_LOG_LEVEL_DEBUG)
#define LOG_DEBUG(...)               k2_log(K2_STDOUT, K2_COLOR_txtrst K2_COLOR_txtwht, "debug", __FILE__, __func__, __LINE__, __VA_ARGS__)
#else
#define LOG_DEBUG(...)
#endif

#if (K2_LOG_LEVEL <= K2_LOG_LEVEL_INFO)
#define LOG_INFO(...)                k2_log(K2_STDOUT, K2_COLOR_txtrst K2_COLOR_txtgrn, "info", __FILE__, __func__, __LINE__, __VA_ARGS__)
#else
#define LOG_INFO(...)
#endif

#if (K2_LOG_LEVEL <= K2_LOG_LEVEL_WARN)
#define LOG_WARN(...)                k2_log(K2_STDERR, K2_COLOR_txtrst K2_COLOR_bldylw, "warn", __FILE__, __func__, __LINE__, __VA_ARGS__)
#else
#define LOG_WARN(...)
#endif

#if (K2_LOG_LEVEL <= K2_LOG_LEVEL_ERROR)
#define LOG_ERROR(...)               k2_log(K2_STDERR, K2_COLOR_txtrst K2_COLOR_bakred K2_COLOR_bldylw, "error", __FILE__, __func__, __LINE__, __VA_ARGS__)
#else
#define LOG_ERROR(...)
#endif

#endif
