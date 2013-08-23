//
//  timer.h
//  K2
//
//  Created by Justin Bowes on 2013-08-23.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#ifndef K2_timer_h
#define K2_timer_h

#include <stdint.h>
#include <stdbool.h>

typedef struct {
	uint32_t sdl_tick_offset;
	uint32_t run_interval;
	uint32_t pause_interval;
	uint32_t *game_ticks;
	bool paused;
} timer_t;

extern timer_t timer;

void timer_init(uint32_t *game_ticks, uint32_t run_interval, uint32_t pause_interval);
void timer_step(void);
void timer_run(void);
void timer_pause(void);

#endif