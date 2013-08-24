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

#define MAX_THINGS	4096

typedef struct {
	uint32_t	ticks;
	
	thing_t		things[MAX_THINGS];
	size_t		thing_count;
} game_t;

extern game_t game;

void game_init(void);

thing_t *game_add_thing(thing_type_t type, thing_id_t *thing_id);

#endif
