//
//  sprites.c
//  K2
//
//  Created by Justin Bowes on 2013-08-24.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "sprites.h"
#include "util.h"

#include <stdarg.h>

sprite_t building_sheet;

#define TILE_SIZE 32
#define TILE(x, y, w, h) ((SDL_Rect) { TILE_SIZE * x, TILE_SIZE * y, TILE_SIZE * w, TILE_SIZE * h })

sprite_t sprites[thing__last];

static void set_sprite(int id, SDL_Texture *texture, size_t count, ...) {
	va_list args;
	va_start(args, count);
	for (size_t i = 0; i < count; ++i) {
		sprites[id].src_rect[i] = va_arg(args, SDL_Rect);
	}
	sprites[id].frame_count = count;
	sprites[id].texture = texture;
}

void sprites_init(void) {
	memset(sprites, 0, thing__last * sizeof(sprite_t));
	
	building_sheet.texture = util_create_texture("sprite/building.png", &building_sheet.src_rect[0]);
	
	SDL_Texture *build = building_sheet.texture;
	
	set_sprite(gull, build, 4, TILE(5, 0, 1, 1), TILE(5, 1, 1, 1), TILE(5, 2, 1, 1), TILE(5, 3, 1, 1));
	set_sprite(cat, build, 2, TILE(2, 2, 1, 1), TILE(2, 3, 1, 1));
	set_sprite(tshirt, build, 1, TILE(3, 2, 1, 1));
	set_sprite(jeans, build, 1, TILE(4, 2, 1, 1));
	set_sprite(bra, build, 1, TILE(3, 3, 1, 1));
	set_sprite(dress, build, 1, TILE(4, 3, 1, 1));
	set_sprite(fire_escape, build, 1, TILE(1, 1, 1, 1));
	set_sprite(ladder, build, 1, TILE(1, 2, 1, 1));
	set_sprite(awning, build, 1, TILE(2, 1, 2, 1));
	set_sprite(clothesline, build, 1, TILE(2, 0, 3, 1));
	set_sprite(building, build, 1, TILE(0, 0, 1, 1));
	set_sprite(building_curtain, build, 1, TILE(1, 0, 1, 1));
	set_sprite(building_dark_escape, build, 1, TILE(0, 1, 1, 1));
	set_sprite(building_bright, build, 1, TILE(0, 2, 1, 1));
	set_sprite(building_venetian, build, 1, TILE(0, 3, 1, 1));
	set_sprite(building_fullwidth, build, 1, TILE(1, 3, 1, 1));
	set_sprite(building_tv, build, 3, TILE(6, 0, 1, 1), TILE(6, 1, 1, 1), TILE(6, 2, 1, 1));
	set_sprite(building_tv_fritz, build, 2, TILE(6, 3, 1, 1), TILE(7, 3, 1, 1));
	set_sprite(building_satellite, build, 1, TILE(7, 0, 1, 1));
	
}

void sprites_destroy(void) {
	SDL_DestroyTexture(building_sheet.texture);
}

sprite_t *sprite_get(thing_type_t thing_type) {
	return &sprites[thing_type];
}