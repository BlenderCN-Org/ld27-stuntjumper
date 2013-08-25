//
//  core.c
//  K2
//
//  Created by Justin Bowes on 2013-08-23.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "core.h"

#include "app.h"
#include <stdint.h>

#define CORE_INTERVAL (1000/60)

void core_loop(void) {
	
	SDL_Event event;
	while (! app.exit) {
		while (SDL_PollEvent(&event)) {
			event_handle(&event);
		}
		
		if (! timer.paused) {
			process_update();			
			view_update();
		}
		view_render();
		
		timer_step();
	}
}