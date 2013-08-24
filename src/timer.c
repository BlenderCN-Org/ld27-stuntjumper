//
//  timer.c
//  K2
//
//  Created by Justin Bowes on 2013-08-23.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "timer.h"
#include "views/view_pause.h"

#include "k2_log.h"
#include <SDL2/SDL.h>

timer_t timer;

void timer_init(uint32_t *game_ticks, uint32_t run_interval, uint32_t pause_interval) {
	timer = (timer_t) {
		.absolute_ticks = SDL_GetTicks(),
		.sdl_tick_offset = 0,
		.run_interval = run_interval,
		.pause_interval = pause_interval,
		.game_ticks = game_ticks,
		.paused = false
	};
	timer.sdl_tick_offset = timer.absolute_ticks;
}

void timer_step(void) {
	timer.absolute_ticks = SDL_GetTicks();
	uint32_t last_tick = *timer.game_ticks;
	
	if (timer.paused) {
		timer.sdl_tick_offset = timer.absolute_ticks - *timer.game_ticks;
		LOG_DEBUG("Timer paused, ticks = %u", *timer.game_ticks);
		SDL_Delay(timer.pause_interval);
	} else {
		*timer.game_ticks = timer.absolute_ticks - timer.sdl_tick_offset;
		uint32_t interval = timer.run_interval;
		if (last_tick + interval > timer.absolute_ticks) {
			uint32_t delay = timer.absolute_ticks - (last_tick + interval);
			LOG_DEBUG("Delaying %u ms", delay);
			SDL_Delay(delay);
		}
	}

}

void timer_run(void) {
	timer.paused = false;
	// pause will pop itself
}

void timer_pause(void) {
	timer.paused = true;
	view_push(&view_pause);
}