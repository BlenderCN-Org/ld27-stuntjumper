//
//  window.c
//  K2
//
//  Created by Justin Bowes on 2013-08-23.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "window.h"
#include "app.h"

static event_handler_t unpause_handler = 0;

static bool on_unpause(SDL_Event *event) {
	timer.paused = false;
	event_remove_handler(&unpause_handler);
	return true;
}

static bool on_window(SDL_Event *event) {
	bool pause = false;
	switch (event->window.event) {
		case SDL_WINDOWEVENT_HIDDEN:
		case SDL_WINDOWEVENT_FOCUS_LOST:
		case SDL_WINDOWEVENT_LEAVE:
		case SDL_WINDOWEVENT_MINIMIZED:
			pause = true;
			break;
	}
	if (pause) {
		timer.paused = true;
		if (! unpause_handler) event_add_handler(&unpause_handler, on_unpause, SDL_MOUSEBUTTONUP | SDL_KEYUP);
		return true;
	}
	return false;
}

void window_init(void) {
	event_add_handler(NULL, on_window, SDL_WINDOWEVENT);
}