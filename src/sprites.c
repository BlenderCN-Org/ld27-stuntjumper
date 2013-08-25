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
	sprites[id].rate = 4;
}

static void set_dude_sprites(SDL_Texture *texture) {
	set_sprite(dude, texture, 1, TILE(7, 4, 1, 1));

	sprites[dude_walk].texture = texture;
	sprites[dude_fall].texture = texture;
	sprites[dude_dive].texture = texture;

	sprites[dude_walk].frame_count = 7;
	sprites[dude_walk].rate = 2;
	for (int i = 0; i < 7; ++i) {
		sprites[dude_walk].src_rect[i] = TILE(i, 4, 1, 1);
	}
	sprites[dude_dive].frame_count = 6;
	sprites[dude_dive].rate = 2;
	
	sprites[dude_fall].frame_count = 6;
	sprites[dude_fall].rate = SIZE_T_MAX;
	for (int i = 0; i < 6; ++i) {
		sprites[dude_dive].src_rect[i] = TILE(i, 5, 1, 1);
		sprites[dude_fall].src_rect[i] = TILE(i, 6, 1, 1);
	}
}

void sprites_init(void) {
	memset(sprites, 0, thing__last * sizeof(sprite_t));
	
	building_sheet.texture = util_create_texture("sprite/sprites.png", &building_sheet.src_rect[0]);
	
	SDL_Texture *sheet = building_sheet.texture;
	
	set_sprite(gull, sheet, 4, TILE(5, 0, 1, 1), TILE(5, 1, 1, 1), TILE(5, 2, 1, 1), TILE(5, 3, 1, 1));
	set_sprite(cat, sheet, 2, TILE(2, 2, 1, 1), TILE(2, 3, 1, 1));
	set_sprite(tshirt, sheet, 1, TILE(3, 2, 1, 1));
	set_sprite(jeans, sheet, 1, TILE(4, 2, 1, 1));
	set_sprite(bra, sheet, 1, TILE(3, 3, 1, 1));
	set_sprite(dress, sheet, 1, TILE(4, 3, 1, 1));
	set_sprite(fire_escape, sheet, 1, TILE(1, 1, 1, 1));
	set_sprite(ladder, sheet, 1, TILE(1, 2, 1, 1));
	set_sprite(awning, sheet, 1, TILE(2, 1, 2, 1));
	set_sprite(clothesline, sheet, 1, TILE(2, 0, 3, 1));
	set_sprite(building, sheet, 1, TILE(0, 0, 1, 1));
	set_sprite(building_curtain, sheet, 1, TILE(1, 0, 1, 1));
	set_sprite(building_dark_escape, sheet, 1, TILE(0, 1, 1, 1));
	set_sprite(building_bright, sheet, 1, TILE(0, 2, 1, 1));
	set_sprite(building_venetian, sheet, 1, TILE(0, 3, 1, 1));
	set_sprite(building_fullwidth, sheet, 1, TILE(1, 3, 1, 1));
	set_sprite(building_tv, sheet, 3, TILE(6, 0, 1, 1), TILE(6, 1, 1, 1), TILE(6, 2, 1, 1));
	set_sprite(building_tv_fritz, sheet, 2, TILE(6, 3, 1, 1), TILE(7, 3, 1, 1));
	sprites[building_tv_fritz].rate = 20;
	set_sprite(building_satellite, sheet, 1, TILE(7, 0, 1, 1));
	
	set_sprite(gibs, sheet, 1, TILE(4, 7, 2, 1));
	set_sprite(ground, sheet, 1, TILE(0, 7, 4, 1));
	
	set_dude_sprites(sheet);
	
}

void sprites_destroy(void) {
	SDL_DestroyTexture(building_sheet.texture);
}

sprite_t *sprite_get(thing_type_t thing_type) {
	return &sprites[thing_type];
}