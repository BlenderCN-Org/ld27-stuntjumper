//
//  keyboard.c
//  K2
//
//  Created by Justin Bowes on 2013-08-24.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "keyboard.h"
#include "app.h"

static bool keys[SDL_NUM_SCANCODES];
event_handler_t keydown_listener, keyup_listener;

static bool on_keydown(SDL_Event *event) {
	SDL_Keycode kc = event->key.keysym.sym & (SDL_NUM_SCANCODES - 1);
	keys[kc] = true;
	return false; // keep processing keys
}

static bool on_keyup(SDL_Event *event) {
	SDL_Keycode kc = event->key.keysym.sym & (SDL_NUM_SCANCODES - 1);
	keys[kc] = false;
	return false; // allow other listeners to process this key
}

void keyboard_init(void) {
	memset(keys, 0, sizeof(bool) * SDL_NUM_SCANCODES);
	event_add_handler(&keydown_listener, on_keydown, SDL_KEYDOWN);
	event_add_handler(&keyup_listener, on_keyup, SDL_KEYUP);
}

void keyboard_destroy(void) {
	event_remove_handler(&keydown_listener);
	event_remove_handler(&keyup_listener);
}

bool keyboard_is_down(SDL_Keycode kc) {
	kc = kc & (SDL_NUM_SCANCODES - 1);
	return keys[kc];
}
