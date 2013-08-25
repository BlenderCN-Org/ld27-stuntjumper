//
//  event.c
//  K2
//
//  Created by Justin Bowes on 2013-08-23.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "event.h"

#include "k2_log.h"
#include <string.h>

#define MAX_HANDLERS 256
typedef struct {
	uint32_t	type;
	event_func	*func;
} event_handler_record_t;

typedef struct {
	event_handler_record_t records[MAX_HANDLERS];
	size_t handler_count;
} event_handlers_t;

event_handlers_t handlers;

void event_init(void) {
	memset(&handlers, 0, sizeof(handlers));
}

void event_add_handler(event_handler_t *handler, event_func func, uint32_t event_type) {
	event_handler_record_t *rec = &handlers.records[handlers.handler_count];
	rec->func = func;
	rec->type = event_type;
	event_handler_t result = (event_handler_t)handlers.handler_count;
	handlers.handler_count = (handlers.handler_count + 1) % MAX_HANDLERS;
	
	if (handler) *handler = result;
}

bool event_remove_handler(event_handler_t *handler) {
	bool result = !! handlers.records[*handler].func;
	handlers.records[*handler].func = NULL;
	if (result) *handler = 0;
	return result;
}

void event_handle(SDL_Event *event) {
	bool handled = false;
	for (size_t i = 0; i < MAX_HANDLERS; ++i) {
		if (handlers.records[i].func) {
			if (handlers.records[i].type == event->type) {
				if (handlers.records[i].func(event)) {
					return;
				} else {
					handled = true;
				}
			}
		}
	}
	if (! handled) LOG_DEBUG("No handler for %X", event->type);
}