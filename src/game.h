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

#define MAX_THINGS	1024

typedef struct {
	uint32_t	ticks;
	uint32_t	rescue_ticks;
	
	thing_t		things[MAX_THINGS];
	size_t		thing_count;
	
	thing_id_t	dude_id;
	
	size_t		input_timeout;

} game_t;

extern game_t game;

void game_init(void);

thing_t *game_add_thing(thing_type_t type, thing_id_t *thing_id);

#endif
