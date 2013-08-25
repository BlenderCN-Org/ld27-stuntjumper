//
//  game.c
//  K2
//
//  Created by Justin Bowes on 2013-08-23.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "game.h"
#include "app.h"
#include "create_level.h"
#include "view_building.h"
#include "sprites.h"
#include "processes.h"

game_t game;

void game_init(void) {
	memset(&game, 0, sizeof(game));
	game.thing_count = 1; // skip 0 so we have a no-id
	
	create_level();
	process_add(process_animate);
	process_add(process_attached);
	process_add(process_dude);
	process_add(process_gravity);
	process_add(process_collide);
	process_add(process_momentum);
	process_add(process_input);
	
	view_push(&view_building);
	
}

thing_t *game_add_thing(thing_type_t type, thing_id_t *thing_id) {
	
	if (thing_id) *thing_id = (thing_id_t) game.thing_count;
	
	thing_t *thing = &game.things[game.thing_count++];
	thing->type = type;
	SDL_Rect src_rect = sprite_get(thing->type)->src_rect[0];
	thing->size = (xvec2) {{ src_rect.w, src_rect.h }};
	return thing;
}

