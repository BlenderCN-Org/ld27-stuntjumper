//
//  event.h
//  K2
//
//  Created by Justin Bowes on 2013-08-23.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#ifndef K2_event_h
#define K2_event_h

#include <stddef.h>
#include <stdint.h>
#include <SDL2/SDL.h>

typedef bool(event_func)(SDL_Event *event);

typedef uint32_t event_handler_t;

void event_init(void);

void event_add_handler(event_handler_t *handler, event_func func, uint32_t event_mask);
bool event_remove_handler(event_handler_t *handler);

void event_handle(SDL_Event *event);

#endif