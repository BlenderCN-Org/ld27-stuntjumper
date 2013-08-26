//
//  view_score.c
//  K2
//
//  Created by Justin Bowes on 2013-08-25.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "view_score.h"
#include "view_title.h"
#include "score.h"
#include "app.h"
#include "timer_blit.h"

#define TXSMALL	8
#define TSMALL	10
#define TMED	12
#define	TLARGE	16

#define INPUT_INTERVAL 20

static uint32_t ticks_countup;

typedef struct {
	SDL_Texture *texture;
	SDL_Rect source_rect;
} text_splat;

static text_splat title_rotate[2], elapsed_time, achievements, achievements_none, achievements_more;
static text_splat ach_title[bp__last];
static text_splat ach_desc[bp__last];
static bool achieved_now[bp__last];

static size_t achievement_count;
static int achievement_index;
static uint32_t input_timeout;

#define ROTATE_INTERVAL 180
static size_t rotate_index;
static int32_t rotate_timeout;
static float brightness;


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

static void activate(void) {
	rotate_index = 0;
	rotate_timeout = ROTATE_INTERVAL;
	input_timeout = 0;
	ticks_countup = 0;
	create_text_splat(kl("game_over"), TLARGE, 0, &title_rotate[0]);
	create_text_splat(kl("press_esc"), TLARGE, 0, &title_rotate[1]);
	create_text_splat(kl("score_elapsed_time"), TSMALL, 0, &elapsed_time);
	create_text_splat(kl("score_achievements"), TMED, 0, &achievements);
	create_text_splat(kl("score_achievements_more"), TSMALL, 0, &achievements_more);
	create_text_splat(kl("score_achievements_none"), TSMALL, REFERENCE_WIDTH - 64, &achievements_none);
		
	achievement_count = 0;
	achievement_index = -1;
	for (size_t i = 0; i < bp__last; ++i) {
		if (game.score.bprops[i] && !score_lifetime.bprops[i]) {
			achieved_now[i] = true;
			++achievement_count;
			if (achievement_index == -1) achievement_index = (int) i;
			char key[64];
			snprintf(key, 64, "%s_title", score_bkeys[i]);
			create_text_splat(kl(key), TSMALL, REFERENCE_WIDTH - 48 - 4, &ach_title[i]);
			snprintf(key, 64, "%s_desc", score_bkeys[i]);
			create_text_splat(kl(key), TXSMALL, REFERENCE_WIDTH - 8, &ach_desc[i]);
		} else {
			achieved_now[i] = false;
		}
	}
	
	score_consolidate();
}

static void deactivate(void) {
	for (int i = 0; i < 2; ++i) SDL_DestroyTexture(title_rotate[i].texture);
	SDL_DestroyTexture(elapsed_time.texture);
	SDL_DestroyTexture(achievements.texture);
	SDL_DestroyTexture(achievements_none.texture);
}


static void update(void) {
	brightness = 1.f - fabsf((float)rotate_timeout - (ROTATE_INTERVAL / 2)) / ((float)ROTATE_INTERVAL / 2);
	rotate_timeout -= 1;
	if (rotate_timeout == 0) {
		rotate_index = (rotate_index + 1) % 2;
		rotate_timeout = ROTATE_INTERVAL;
	}

	if (ticks_countup < game.ended_at_ticks) ticks_countup += 10;
	if (ticks_countup > game.ended_at_ticks) ticks_countup = game.ended_at_ticks;
	
	if (input_timeout == 0) {
		if (keyboard_is_down(SDLK_LEFT) && achievement_count > 0) {
			if (achievement_index == ach_no_left_arrow) {
				deactivate();
				game.score.bprops[ach_no_no_left_arrow] = true;
				activate();
				ticks_countup = game.ended_at_ticks;
				achievement_index = ach_no_no_left_arrow;
				audio_play("sfx/ach.wav");
			} else {
				do {
					achievement_index = achievement_index - 1;
					if (achievement_index < 0) achievement_index = bp__last - 1;
				} while (! achieved_now[achievement_index]);
			}
			input_timeout = INPUT_INTERVAL;
		}
		
		if (keyboard_is_down(SDLK_RIGHT) && achievement_count > 0) {
			do {
				achievement_index = (achievement_index + 1) % bp__last;
			} while (! achieved_now[achievement_index]);
			input_timeout = INPUT_INTERVAL;
		}
	} else {
		--input_timeout;
	}
	
	if (keyboard_is_down(SDLK_ESCAPE)) {
		while (view_pop()) {}
		game_init();
	}
}


static void render(void) {
	SDL_SetTextureAlphaMod(title_rotate[rotate_index].texture, 0xFF * brightness);
	SDL_SetRenderDrawColor(display.renderer, 0x20, 0x20, 0x20, 0x20);
	SDL_RenderClear(display.renderer);
	SDL_SetRenderDrawBlendMode(display.renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(display.renderer, 0xFF, 0xFF, 0xFF, 0x20);

	draw_text_splat(&title_rotate[rotate_index], -1, 0);
	draw_sprite(panel_timer, 16, 28);
	timer_blit(ticks_countup, REFERENCE_WIDTH - 22, 32);
	draw_text_splat(&elapsed_time, -1, 56);
	
	SDL_RenderDrawLine(display.renderer, 0, 80, REFERENCE_WIDTH, 80);
	
	draw_text_splat(&achievements, -1, 81);
	
	if (achievement_index != -1) {
		draw_sprite(panel_achievement, 0, 106);
		draw_sprite(achievement_index, 9, 114);
		draw_text_splat(&ach_title[achievement_index], 48, 130 - (ach_title[achievement_index].source_rect.h / 2));
		draw_text_splat(&ach_desc[achievement_index], 4, 152);
	} else {
		draw_text_splat(&achievements_none, -1, 130);
	}
	
	SDL_RenderDrawLine(display.renderer, 0, 224, REFERENCE_WIDTH, 224);
	if (achievement_count > 1) {
		draw_text_splat(&achievements_more, -1, 232);
		draw_sprite(sui_arrow_left, 0, 226);
		draw_sprite(sui_arrow_right, REFERENCE_WIDTH - 32, 226);
	}
}

view_t view_score = {
	activate,
	deactivate,
	update,
	render
};