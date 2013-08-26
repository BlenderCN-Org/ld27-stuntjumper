//
//  view_title.c
//  K2
//
//  Created by Justin Bowes on 2013-08-25.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "view_title.h"
#include "view_building.h"
#include "k2_log.h"

// paste from view_score YEAH I DID
typedef struct {
	SDL_Texture *texture;
	SDL_Rect source_rect;
} text_splat;

static text_splat title_1;
static text_splat title_2;
static text_splat rotator[3];
static size_t rotate_index;
static float brightness;

#define INPUT_SUPPRESS 90
static int input_timeout;

#define ROTATE_INTERVAL 180
static int32_t rotate_timeout;

static event_handler_t any_key_handler;

static sprite_t *backlight;
static sprite_t *foreground;
static sprite_t *bottom;

#define ACTION_INTERVAL 120
#define DUDE_WALK_SPEED 0.125
#define ANIMATE_RATE 10
static thing_t dude;
static bool walking;
static uint32_t action_interval;
static float position;

static bool on_any_key(SDL_Event *event) {
	if (input_timeout) return false;
	
	game_start();
	return true;
}

static void create_text_splat(const char *message, int size, uint32_t wrap_at, text_splat *splat) {
	splat->texture = util_create_font_texture(message, size, wrap_at, &splat->source_rect);
}

static void draw_text_splat(text_splat *splat, int x, int y) {
	if (x == -1) x = (REFERENCE_WIDTH - splat->source_rect.w) / 2;
	
	SDL_Rect dest = { x, y, splat->source_rect.w, splat->source_rect.h };
	SDL_RenderCopy(display.renderer, splat->texture, &splat->source_rect, &dest);
}

static void draw_sprite(score_sprites_t sprite_id, int x, int y) {
	sprite_t *sprite = sprite_score_get(sprite_id);
	SDL_Rect dest = { x, y, sprite->src_rect[0].w, sprite->src_rect[0].h };
	SDL_RenderCopy(display.renderer, sprite->texture, &sprite->src_rect[0], &dest);
}


void activate(void) {
	create_text_splat(kl("title_1"), 18, 0, &title_1);
	create_text_splat(kl("title_2"), 24, 0, &title_2);
	create_text_splat(kl("byline"), 8, 0, &rotator[0]);
	create_text_splat(kl("ludum"), 8, 0, &rotator[1]);
	create_text_splat(kl("any_key"), 8, 0, &rotator[2]);
	rotate_index = 0;
	rotate_timeout = ROTATE_INTERVAL;
	event_add_handler(&any_key_handler, on_any_key, SDL_KEYUP);
	input_timeout = INPUT_SUPPRESS;
	
	backlight = sprite_thing_get(building_window_backlight);
	foreground = sprite_thing_get(building_window_fg);
	bottom = sprite_thing_get(building_fullwidth);
	dude.type = dude_stand;
	walking = false;
	action_interval = 0;
	position = -24;
}

void deactivate(void) {
	SDL_DestroyTexture(title_1.texture);
	SDL_DestroyTexture(title_2.texture);
	for (int i = 0; i < 3; ++i) SDL_DestroyTexture(rotator[i].texture);
	event_remove_handler(&any_key_handler);
}

void update(void) {
	if (input_timeout > 0) input_timeout -= 1;
	brightness = 1.f - fabsf((float)rotate_timeout - (ROTATE_INTERVAL / 2)) / ((float)ROTATE_INTERVAL / 2);
	rotate_timeout -= 1;
	if (rotate_timeout == 0) {
		rotate_index = (rotate_index + 1) % 3;
		rotate_timeout = ROTATE_INTERVAL;
	}

	++dude.animate_timeout;
	sprite_t *sprite = sprite_thing_get(dude.type);
	if (sprite->rate && dude.animate_timeout > sprite->rate * ANIMATE_RATE) {
		dude.current_frame = (dude.current_frame + 1) % sprite->frame_count;
		dude.animate_timeout = 0;
	}
	if (action_interval == 0) {
		action_interval = rand() % ACTION_INTERVAL;
		walking = !walking;
		dude.type = walking ? dude_walk : dude_stand;
		dude.current_frame = 0;
	}
	if (walking) {
		position += DUDE_WALK_SPEED;
		LOG_DEBUG("pos %f", position);
	}
	--action_interval;
	
}

void render(void) {
	SDL_SetRenderDrawColor(display.renderer, 0x20, 0x20, 0x20, 0xFF);
	SDL_RenderClear(display.renderer);
	draw_text_splat(&title_1, -1, 25);
	draw_text_splat(&title_2, -1, 35);
	
	SDL_SetTextureAlphaMod(rotator[rotate_index].texture, 0xFF * brightness);
	draw_text_splat(&rotator[rotate_index], -1, REFERENCE_HEIGHT - 24);
	
	SDL_SetRenderDrawBlendMode(display.renderer, SDL_BLENDMODE_BLEND);
	for (int x = 0; x < REFERENCE_WIDTH; x += 32) {
		SDL_Rect dest_rect = { x, 128, 32, 32 };
		SDL_RenderCopy(display.renderer, backlight->texture, &backlight->src_rect[0], &dest_rect);
	}
	sprite_t *dude_sprite = sprite_thing_get(dude.type);
	SDL_Rect dest_rect = {
		position,
		144,
		dude_sprite->src_rect[dude.current_frame].w,
		dude_sprite->src_rect[dude.current_frame].h
	};
	SDL_RenderCopy(display.renderer, dude_sprite->texture, &dude_sprite->src_rect[dude.current_frame], &dest_rect);
	for (int x = 0; x < REFERENCE_WIDTH; x += 32) {
		SDL_Rect fore_rect = { x, 128, 32, 32 };
		SDL_Rect bott_rect = { x, 160, 32, 32 };
		SDL_RenderCopy(display.renderer, foreground->texture, &foreground->src_rect[0], &fore_rect);
		SDL_RenderCopy(display.renderer, bottom->texture, &bottom->src_rect[0], &bott_rect);
	}
}

view_t view_title = {
	activate,
	deactivate,
	update,
	render
};