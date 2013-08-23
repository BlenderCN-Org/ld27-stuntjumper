//
//  k2_error.c
//  K2
//
//  Created by Justin Bowes on 2013-08-22.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "k2_error.h"
#include "k2_l10n.h"
#include "app.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
static void show_abort_message(const char *message) {
	const char *title;
	if (! k2_l10n_get_success("error_title", &title)) title = app.name;
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title,
							 message, NULL);
}

void k2_abort(const char *error_fmt_key, ...) {
	va_list args;
	va_start(args, error_fmt_key);
	char message[1024] = {0};
	const char *val = kl(error_fmt_key);
	vsnprintf(message, 1024, val, args);
	va_end(args);
	show_abort_message(message);
	abort();
}
