//
//  timer.c
//  K2
//
//  Created by Justin Bowes on 2013-08-23.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "timer.h"

#include "k2_log.h"
#include <SDL2/SDL.h>

timer_t timer;

void timer_init(uint32_t *game_ticks, uint32_t run_interval, uint32_t pause_interval) {
	timer = (timer_t) {
		.sdl_tick_offset = SDL_GetTicks(),
		.run_interval = run_interval,
		.pause_interval = pause_interval,
		.game_ticks = game_ticks,
		.paused = false
	};
}

void timer_step(void) {
	uint32_t current_tick = SDL_GetTicks();
	uint32_t last_tick = *timer.game_ticks;
	
	if (timer.paused) {
		timer.sdl_tick_offset = current_tick - *timer.game_ticks;
		LOG_DEBUG("Timer paused, ticks = %u", *timer.game_ticks);
		SDL_Delay(timer.pause_interval);
	} else {
		*timer.game_ticks = current_tick - timer.sdl_tick_offset;
		uint32_t interval = timer.run_interval;
		if (last_tick + interval > current_tick) {
			uint32_t delay = current_tick - (last_tick + interval);
			LOG_DEBUG("Delaying %u ms", delay);
			SDL_Delay(delay);
		}
	}

}

void timer_run(void) {
	timer.paused = false;
}

void timer_pause(void) {
	timer.paused = true;
}