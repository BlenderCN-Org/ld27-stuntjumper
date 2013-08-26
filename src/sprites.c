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
sprite_t score_sheet;

#define TILE_SIZE 32
#define T32(x, y, w, h) ((SDL_Rect) { TILE_SIZE * x, TILE_SIZE * y, TILE_SIZE * w, TILE_SIZE * h })

sprite_t thing_sprites[thing__last];
sprite_t score_sprites[score_sprite__last];

static void set_sprite(sprite_t *sheet, int id, SDL_Texture *texture, size_t count, ...) {
	va_list args;
	va_start(args, count);
	for (size_t i = 0; i < count; ++i) {
		sheet[id].src_rect[i] = va_arg(args, SDL_Rect);
	}
	sheet[id].frame_count = count;
	sheet[id].texture = texture;
	sheet[id].rate = 4;
}

static void set_dude_sprites(SDL_Texture *texture) {
	set_sprite(thing_sprites, dude_stand, texture, 1, T32(7, 4, 1, 1));

	thing_sprites[dude_walk].texture = texture;
	thing_sprites[dude_fall].texture = texture;
	thing_sprites[dude_dive].texture = texture;

	thing_sprites[dude_walk].frame_count = 7;
	thing_sprites[dude_walk].rate = 2;
	for (int i = 0; i < 7; ++i) {
		thing_sprites[dude_walk].src_rect[i] = T32(i, 4, 1, 1);
	}
	thing_sprites[dude_dive].frame_count = 6;
	thing_sprites[dude_dive].rate = 2;
	
	thing_sprites[dude_fall].frame_count = 6;
	thing_sprites[dude_fall].rate = SIZE_T_MAX;
	for (int i = 0; i < 6; ++i) {
		thing_sprites[dude_dive].src_rect[i] = T32(i, 5, 1, 1);
		thing_sprites[dude_fall].src_rect[i] = T32(i, 6, 1, 1);
	}
}

static void init_thing_sprites(void) {
	building_sheet.texture = util_create_texture("sprite/sprites.png", &building_sheet.src_rect[0]);
	
	SDL_Texture *sheet = building_sheet.texture;
	
	set_sprite(thing_sprites, gull, sheet, 4, T32(5, 0, 1, 1), T32(5, 1, 1, 1), T32(5, 2, 1, 1), T32(5, 3, 1, 1));
	set_sprite(thing_sprites, cat, sheet, 2, T32(2, 2, 1, 1), T32(2, 3, 1, 1));
	set_sprite(thing_sprites, tshirt, sheet, 1, T32(3, 2, 1, 1));
	set_sprite(thing_sprites, jeans, sheet, 1, T32(4, 2, 1, 1));
	set_sprite(thing_sprites, bra, sheet, 1, T32(3, 3, 1, 1));
	set_sprite(thing_sprites, dress, sheet, 1, T32(4, 3, 1, 1));
	set_sprite(thing_sprites, fire_escape, sheet, 1, T32(1, 1, 1, 1));
	set_sprite(thing_sprites, ladder, sheet, 1, T32(1, 2, 1, 1));
	set_sprite(thing_sprites, awning, sheet, 1, T32(2, 1, 2, 1));
	set_sprite(thing_sprites, clothesline, sheet, 1, T32(2, 0, 3, 1));
	set_sprite(thing_sprites, building, sheet, 1, T32(0, 0, 1, 1));
	set_sprite(thing_sprites, building_curtain, sheet, 1, T32(1, 0, 1, 1));
	set_sprite(thing_sprites, building_dark_escape, sheet, 1, T32(0, 1, 1, 1));
	set_sprite(thing_sprites, building_bright, sheet, 1, T32(0, 2, 1, 1));
	set_sprite(thing_sprites, building_venetian, sheet, 1, T32(0, 3, 1, 1));
	set_sprite(thing_sprites, building_fullwidth, sheet, 1, T32(1, 3, 1, 1));
	set_sprite(thing_sprites, building_tv, sheet, 3, T32(6, 0, 1, 1), T32(6, 1, 1, 1), T32(6, 2, 1, 1));
	set_sprite(thing_sprites, building_tv_fritz, sheet, 2, T32(6, 3, 1, 1), T32(7, 3, 1, 1));
	thing_sprites[building_tv_fritz].rate = 1;
	set_sprite(thing_sprites, building_tv_wtf, sheet, 1, T32(7, 2, 1, 1));
	set_sprite(thing_sprites, building_satellite, sheet, 1, T32(7, 0, 1, 1));
	
	set_sprite(thing_sprites, building_window_backlight, sheet, 1, T32(7, 5, 1, 1));
	set_sprite(thing_sprites, building_window_fg, sheet, 1, T32(7, 6, 1, 1));
	
	set_sprite(thing_sprites, gibs, sheet, 1, T32(4, 7, 2, 1));
	set_sprite(thing_sprites, ground, sheet, 1, T32(0, 7, 4, 1));
	
	set_dude_sprites(sheet);
}

static void init_score_sprites(void) {
	score_sheet.texture = util_create_texture("sprite/score.png", &score_sheet.src_rect[0]);
	SDL_Texture *sheet = score_sheet.texture;
	set_sprite(score_sprites, panel_timer, sheet, 1,			T32(0, 0, 3, 1.5f));
	set_sprite(score_sprites, panel_achievement, sheet, 1,		T32(0, 1.5f, 4, 1.5f));
	
	set_sprite(score_sprites, ach_every_cat, sheet, 1,			T32(0, 3, 1, 1));
	set_sprite(score_sprites, ach_no_cat, sheet, 1,				T32(1, 3, 1, 1));
	set_sprite(score_sprites, ach_every_satellite, sheet, 1,	T32(2, 3, 1, 1));
	set_sprite(score_sprites, ach_no_satellite, sheet, 1,		T32(3, 3, 1, 1));
	set_sprite(score_sprites, ach_every_dress, sheet, 1,		T32(4, 3, 1, 1));
	set_sprite(score_sprites, ach_every_bra, sheet, 1,			T32(5, 3, 1, 1));
	set_sprite(score_sprites, ach_every_jeans, sheet, 1,		T32(6, 3, 1, 1));
	set_sprite(score_sprites, ach_every_tshirt, sheet, 1,		T32(7, 3, 1, 1));
	set_sprite(score_sprites, ach_every_clothes, sheet, 1,		T32(0, 4, 1, 1));
	set_sprite(score_sprites, ach_every_fire_escape, sheet, 1,	T32(1, 4, 1, 1));
	set_sprite(score_sprites, ach_no_fire_escape, sheet, 1,		T32(2, 4, 1, 1));
	set_sprite(score_sprites, ach_first_run, sheet, 1,			T32(3, 4, 1, 1));
	set_sprite(score_sprites, ach_no_left_arrow, sheet, 1,		T32(4, 4, 1, 1));
	set_sprite(score_sprites, ach_no_no_left_arrow, sheet, 1,	T32(7, 2, 1, 1));
	set_sprite(score_sprites, ach_everything_broken, sheet, 1,	T32(5, 4, 1, 1));
	set_sprite(score_sprites, ach_nothing_broken, sheet, 1,		T32(6, 4, 1, 1));
	set_sprite(score_sprites, ach_replay, sheet, 1,				T32(7, 4, 1, 1));
	set_sprite(score_sprites, ach_rounds_5, sheet, 1,			T32(0, 5, 1, 1));
	set_sprite(score_sprites, ach_rounds_10, sheet, 1,			T32(1, 5, 1, 1));
	set_sprite(score_sprites, ach_rounds_25, sheet, 1,			T32(2, 5, 1, 1));
	set_sprite(score_sprites, ach_rounds_100, sheet, 1,			T32(3, 5, 1, 1));
	set_sprite(score_sprites, ach_rounds_500, sheet, 1,			T32(4, 5, 1, 1));
	set_sprite(score_sprites, ach_rounds_1000, sheet, 1,		T32(5, 5, 1, 1));
	set_sprite(score_sprites, sui_arrow_left, sheet, 1,			T32(6, 5, 1, 1));
	set_sprite(score_sprites, sui_arrow_right, sheet, 1,		T32(7, 5, 1, 1));
}

void sprites_init(void) {
	memset(thing_sprites, 0, thing__last * sizeof(sprite_t));
	init_thing_sprites();
	init_score_sprites();
}

void sprites_destroy(void) {
	SDL_DestroyTexture(building_sheet.texture);
	SDL_DestroyTexture(score_sheet.texture);
}

sprite_t *sprite_thing_get(thing_type_t thing_type) {
	return &thing_sprites[thing_type];
}

sprite_t *sprite_score_get(score_sprites_t sid) {
	return &score_sprites[sid];
}