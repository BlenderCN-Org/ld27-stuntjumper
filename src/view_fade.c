//
//  view_fade.c
//  K2
//
//  Created by Justin Bowes on 2013-08-25.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "view_fade.h"

#include <SDL2/SDL.h>

#include "app.h"
#include "k2_log.h"

#define FADE_DELTA 1.f / 60.f

static SDL_Color target;
static float alpha = 0.0f;
static float delta = FADE_DELTA;

static void activate(void) {
}

static void deactivate(void) {
}

static void update(void) {
	view_update_parent();
	alpha += delta;
	alpha = fminf(alpha, 1.f);
	alpha = fmaxf(alpha, 0.f);
}

static void render(void) {
	view_render_parent();
	uint8_t alpha_byte = (uint8_t)(0xFF * alpha);
	SDL_SetRenderDrawBlendMode(display.renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(display.renderer, target.r, target.g, target.b, alpha_byte);
	SDL_RenderFillRect(display.renderer, NULL);
	
	if (view_fade_done()) {
		view_pop();
	}
}

void view_fade_in(SDL_Color color) {
	alpha = 1.f;
	delta = -FADE_DELTA;
	target = color;
}

void view_fade_out(SDL_Color color) {
	alpha = 0.f;
	delta = FADE_DELTA;
	target = color;
}

bool view_fade_done(void) {
	if (delta > 0.f) {
		return (alpha >= 1.f);
	} else {
		return (alpha <= 0.f);
	}
}

view_t view_fade = {
	activate,
	deactivate,
	update,
	render
};