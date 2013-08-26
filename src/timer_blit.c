//
//  timer_blit.c
//  K2
//
//  Created by Justin Bowes on 2013-08-25.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "timer_blit.h"
#include "app.h"
#include "sdl.h"
#include <string.h>
#include <stdio.h>
#include "k2_error.h"

static const char *glyphs = "0123456789.:";
static struct {
	sprite_t glyphs[20];
	struct {
		sprite_t *glyph;
		SDL_Rect dest;
	} character[15];
	float advance;
	size_t length;
} timer_text;

static const SDL_Color white = { 0xFF, 0xFF, 0xFF, 0xFF };

void timer_blit_init(void) {
	PHYSFS_File *pf = PHYSFS_openRead(FONT);
    if (! pf) k2_abort("err_init", FONT);
	SDL_RWops *file = PHYSFSRWOPS_makeRWops(pf);
	TTF_Font *font = TTF_OpenFontRW(file, true, 12);
	float widest = 0.f;
	for (size_t i = 0; i < strlen(glyphs); ++i) {
		char digit_buffer[2];
		snprintf(digit_buffer, 2, "%c", glyphs[i]);
		SDL_Surface *surf = TTF_RenderUTF8_Blended(font, digit_buffer, white);
		widest = fmaxf(widest, surf->w);
		util_sprite_from_surf(&timer_text.glyphs[i], 0, surf);
		SDL_FreeSurface(surf);
	}
	timer_text.advance = widest;
	TTF_CloseFont(font);
}

void timer_blit(uint32_t ticks, int right, int y) {
	float time = ticks / 60.f;
	
	char timer_str[11];
	uint32_t minutes = time / 60.f;
	uint32_t tensecs = time / 10 * 10;
	float frac = time - tensecs;
	snprintf(timer_str, 11, "%02u:%01u%.2f", minutes, tensecs / 10, frac);
	size_t len = strlen(timer_str);
	
	timer_text.length = 0;
	xvec2 pos = {{ right, y }};
	for (size_t i = 0; i < len; ++i) {
		ptrdiff_t glyph_index = strchr(glyphs, timer_str[len - i - 1]) - glyphs;
		sprite_t *glyph = &timer_text.glyphs[glyph_index];
		timer_text.character[timer_text.length].glyph = glyph;
		pos.x -= timer_text.advance;
		timer_text.character[timer_text.length].dest = (SDL_Rect) {
			pos.x,
			pos.y,
			glyph->src_rect[0].w,
			glyph->src_rect[0].h
		};
		++timer_text.length;
	}
	
	for (size_t i = 0; i < timer_text.length; ++i) {
		SDL_RenderCopy(display.renderer, timer_text.character[i].glyph->texture,
					   timer_text.character[i].glyph->src_rect, &timer_text.character[i].dest);
	}

}

void timer_blit_destroy(void) {
	for (size_t i = 0; i < strlen(glyphs); ++i) {
		SDL_DestroyTexture(timer_text.glyphs[i].texture);
	}
}