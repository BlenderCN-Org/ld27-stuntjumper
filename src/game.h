//
//  game.h
//  K2
//
//  Created by Justin Bowes on 2013-08-22.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#ifndef K2_game_h
#define K2_game_h

#include <stdint.h>
#include "thing.h"
#include "score.h"

#define MAX_THINGS	1024

typedef struct {
	uint32_t	ticks;
	uint32_t	active_ticks;
	
	bool		over;
	uint32_t	ended_at_ticks;
	
	thing_t		things[MAX_THINGS];
	size_t		thing_count;
	
	uint32_t	trigger_count[thing__last];
	uint32_t	gen_count[thing__last];
	
	thing_id_t	dude_id;
	
	size_t		input_timeout;
	
	score_t		score;

} game_t;

extern game_t game;

void game_init(void);
void game_start(void);

thing_t *game_add_thing(thing_type_t type, thing_id_t *thing_id);

#endif
