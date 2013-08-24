//
//  create_level.c
//  K2
//
//  Created by Justin Bowes on 2013-08-24.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "create_level.h"

#include "k2_log.h"

static thing_type_t random_building_piece(void) {
	return k2_random_int(building, building_tv);
}

static void create_satellite_dish(thing_id_t parent_id, thing_t *parent) {
	thing_t *child = game_add_thing(building_satellite, NULL);
	child->linked_thing = parent_id;
	child->breakable = true;
	child->attached = true;
	child->position = (xvec2) {{ parent->position.x + parent->size.x, parent->position.y }};
}

static void create_fire_escape(thing_id_t parent_id, thing_t *parent) {
	// assumes we're working upwards.
	thing_id_t escape_id;
	thing_t *escape = game_add_thing(fire_escape, &escape_id);
	escape->attached = true;
	escape->breakable = true;
	xvec2 position = {{ parent->position.x + parent->size.x, parent->position.y }};
	escape->position = position;
	
	LOG_DEBUG("Added fire escape at %f %f", position.x, position.y);
	
	thing_id_t blocking = -1;
	// set start position early
	position.y += escape->size.height;
	while (blocking == -1 && position.y < BUILDING_HEIGHT) {
		parent_id = escape_id;
		blocking = thing_at_position(position);
		if (blocking == -1 || thing_type(blocking) == fire_escape) {
			escape = game_add_thing(ladder, &escape_id);
			escape->linked_thing = parent_id;
			escape->attached = true;
			escape->breakable = true;
			escape->position = position;
			LOG_DEBUG("Added ladder at %f %f", position.x, position.y);
		}
		// adjust here so we can check if too low for the next
		position.y += escape->size.height;
	}
}

static void create_building(void) {
	
	SDL_Rect tile_rect = sprite_get(building)->src_rect[0];
	
	for (int y = BUILDING_HEIGHT - tile_rect.h; y > 0; y -= tile_rect.h) {
		thing_id_t thing_id;
		thing_t *piece = game_add_thing(random_building_piece(), &thing_id);
		piece->solid = true;
		piece->attached = true;
		piece->position = (xvec2){{ 0, y }};
		
		LOG_DEBUG("Added building at %f %f", piece->position.x, piece->position.y);

		switch (piece->type) {
			case building_tv:
				create_satellite_dish(thing_id, piece);
				break;
				
			case building_dark_escape:
				create_fire_escape(thing_id, piece);
				break;
				
			default:
				break;
		}
	}
	// Create a horizontal area at the top.
	for (int x = -REFERENCE_WIDTH; x < 0; x += tile_rect.w) {
		game_add_thing(building_fullwidth, NULL);
	}
}

void create_level(void) {
	create_building();
}