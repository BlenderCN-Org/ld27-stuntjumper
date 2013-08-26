//
//  k2_log.c
//  K2
//
//  Created by Justin Bowes on 2013-08-22.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "k2_log.h"
#include "k2_platform.h"
#include <stdbool.h>

#if (K2_LOG_LEVEL < K2_LOG_LEVEL_OFF)
char ___k2_log_output[K2_LOG_MAX];
#endif

#ifdef K2_PLATFORM_WINDOWS

// Clean-room reimpl of GNU-like basename for Windows
#define INCLUDES_DRIVE(path)	((((path)[0] >= 'a' && (path)[1] <= 'z') || ((path)[0] >= 'A' && (path)[0] <= 'Z')) && (path)[1] == ':')
#define DRIVE_LENGTH(path)		(INCLUDES_DRIVE(path) ? 2 : 0)
#define IS_SEPARATOR(chr)		((chr) == '/' || (chr) == '\\')

char *k2_basename(const char *name) {
	const char *after_last = name + DRIVE_LENGTH(name);
	bool is_all_slashes = true;
	const char *cp;

	for (cp = name; *cp != '\0'; cp++) {
		if (IS_SEPARATOR(*cp)) {
			after_last = cp + 1;
		} else {
			is_all_slashes = false;
		}
	}

	if (*after_last == '\0' && IS_SEPARATOR(*name) && is_all_slashes) {
		// What did you do?!
		--after_last; // Return final slash.
	}

	return (char *)after_last;
}

#endif