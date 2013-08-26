//
//  create_level.c
//  K2
//
//  Created by Justin Bowes on 2013-08-24.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "create_level.h"

#include "k2_log.h"

#define FIRE_ESCAPE_PROB	0.02f
#define CLOTHESLINE_PROB	0.08f
#define SATELLITE_PROB		0.02f

static thing_type_t random_building_piece(void) {
	thing_type_t result = k2_random_int(building, building_venetian);
	if (util_frand() < SATELLITE_PROB) result = building_tv;
	return result;
}

static void create_satellite_dish(thing_id_t parent_id, thing_t *parent) {
	thing_t *child = game_add_thing(building_satellite, NULL);
	child->attached_to = parent_id;
	child->breakable = true;
	child->gravitated = true;
	child->position = (xvec2) {{ parent->position.x + parent->size.x, parent->position.y }};
	child->attach_offset = xvec2_set(parent->size.x, 0);
}

static void create_fire_escape(thing_id_t parent_id, thing_t *parent) {
	// assumes we're working upwards.
	thing_id_t escape_id;
	thing_t *escape = game_add_thing(fire_escape, &escape_id);
	escape->attached_to = parent_id;
	escape->breakable = true;
	escape->gravitated = true;
	xvec2 position = {{ parent->position.x + parent->size.x, parent->position.y }};
	escape->position = position;
	escape->attach_offset = xvec2_set(parent->size.x, 0);
	
	LOG_DEBUG("Added fire escape at %f %f", position.x, position.y);
	
	thing_id_t blocking = -1;
	// set start position early
	position.y += escape->size.height;
	// don't let the fire escape come down to ground level...that's not right
	while (blocking == -1 && position.y < BUILDING_HEIGHT - escape->size.height) {
		parent_id = escape_id;
		blocking = thing_at_position(position, 0);
		if (blocking == -1 || thing_type(blocking) == fire_escape) {
			float last_height = escape->size.height;
			escape = game_add_thing(ladder, &escape_id);
			escape->attached_to = parent_id;
			escape->breakable = true;
			escape->gravitated = true;
			escape->position = position;
			escape->attach_offset = xvec2_set(0.f, last_height);
			LOG_DEBUG("Added ladder at %f %f", position.x, position.y);
		}
		// adjust here so we can check if too low for the next
		position.y += escape->size.height;
	}
}

static void create_clothesline(thing_id_t parent_id, thing_t *parent) {
	thing_id_t ctid;
	thing_t *clothesthing = game_add_thing(clothesline, &ctid);
	clothesthing->position = xvec2_add(parent->position, xvec2_set(parent->size.x, 0.f));
	clothesthing->attached_to = parent_id;
	clothesthing->attach_offset = xvec2_set(parent->size.width, 0);
	
	// Add something to the line
	const thing_type_t select[] = {
		cat,
		tshirt,
		jeans,
		bra,
		dress,
		nothing,
		nothing
	};
	const size_t elements = sizeof(select) / sizeof(thing_type_t);
	int pick = rand() % elements;
	if (! select[pick]) return;
	
	thing_t *online = game_add_thing(select[pick], NULL);
	online->position = xvec2_add(clothesthing->position,
								 xvec2_set((clothesthing->size.width - online->size.width) / 2, 0.f));
	online->attach_offset = xvec2_set((clothesthing->size.width - online->size.width) / 2, 0.f);
	online->attached_to = ctid;
	online->gravitated = true;
	if (online->type >= tshirt && online->type <= dress) {
		online->wearable = true;
	} else {
		online->breakable = true;
	}
}

static void create_building(void) {
	
	SDL_Rect tile_rect = sprite_thing_get(building)->src_rect[0];
	
	for (int y = BUILDING_HEIGHT - tile_rect.h; y > 0; y -= tile_rect.h) {
		thing_id_t thing_id;
		thing_t *piece = game_add_thing(random_building_piece(), &thing_id);
		piece->solid = true;
		piece->position = (xvec2){{ 0, y }};
		
		LOG_DEBUG("Added building at %f %f", piece->position.x, piece->position.y);

		if (piece->type == building_tv) {
			create_satellite_dish(thing_id, piece);
		} else if (util_frand() < FIRE_ESCAPE_PROB) {
			create_fire_escape(thing_id, piece);
		} else if (util_frand() < CLOTHESLINE_PROB) {
			create_clothesline(thing_id, piece);
		}
		
	}
	// Create a horizontal area at the top.
	for (int x = -REFERENCE_WIDTH; x < 0; x += tile_rect.w) {
		thing_t *thing = game_add_thing(building_fullwidth, NULL);
		thing->position.y = thing->size.height;
		thing->solid = true;
	}
	// Add ground at the bottom
	thing_t *gt = game_add_thing(ground, NULL);
	gt->position = xvec2_set(0.f, BUILDING_HEIGHT);
	gt->solid = true;
}

static void create_dude(void) {
	thing_t *dt = game_add_thing(dude_stand, &game.dude_id);
	dt->position = xvec2_set(-16, 0);
}

void create_level(void) {
	create_building();
	create_dude();
}