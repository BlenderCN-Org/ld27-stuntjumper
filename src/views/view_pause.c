//
//  view_pause.c
//  K2
//
//  Created by Justin Bowes on 2013-08-23.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "view_pause.h"

#include <SDL2_ttf/SDL_ttf.h>

#include "app.h"
#include "k2_log.h"

static SDL_Texture *message_texture;
static SDL_Rect message_rect;

static void activate(void) {
	message_texture = util_create_font_texture(kl("paused"), 24, 0, NULL);
}

static void deactivate(void) {
	SDL_DestroyTexture(message_texture);
}

static void update(void) {
	// update isn't called during pause
}

static void render(void) {
	if (! timer.paused) view_pop();

	view_render_parent();

	SDL_SetRenderDrawBlendMode(display.renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(display.renderer, 0, 0, 0, 0xD0);
	SDL_RenderFillRect(display.renderer, NULL);
	
	uint32_t timebase = timer.absolute_ticks >> 2;
	SDL_Color c = {
		timebase % 0xFF,
		(timebase + 86) % 0xFF,
		(timebase + 172) % 0xFF,
		0xFF
	};
	SDL_SetTextureColorMod(message_texture, c.r, c.g, c.g);
	util_center_texture_rect(message_texture, &message_rect);
	
	SDL_RenderCopy(display.renderer, message_texture, NULL, &message_rect);
}

view_t view_pause = {
	activate,
	deactivate,
	update,
	render
};