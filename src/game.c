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

game_t game;

void game_init(void) {
	memset(&game, 0, sizeof(game));
	create_level();
	
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

