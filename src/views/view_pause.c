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

SDL_Color white = { 0xFF, 0xFF, 0xFF, 0xFF };

SDL_Texture *message_texture;
SDL_Rect message_rect;

static void activate(void) {
	PHYSFS_Version v;
	PHYSFS_getLinkedVersion(&v);
	PHYSFS_File *pf = PHYSFS_openRead("font/telegrama_render_osn.otf");
	SDL_RWops *file = PHYSFSRWOPS_makeRWops(pf);
	TTF_Font *font = TTF_OpenFontRW(file, true, 24);
	SDL_Surface *surf = TTF_RenderUTF8_Blended(font, kl("paused"), white);
	message_texture = SDL_CreateTextureFromSurface(display.renderer, surf);
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	SDL_RWclose(file);
}

static void deactivate(void) {
	SDL_DestroyTexture(message_texture);
}

static void update(void) {
	if (! timer.paused) view_pop();
	
	uint32_t timebase = timer.absolute_ticks >> 2;
	SDL_Color c = {
		timebase % 0xFF,
		(timebase + 86) % 0xFF,
		(timebase + 172) % 0xFF,
		0xFF
	};
	SDL_SetTextureColorMod(message_texture, c.r, c.g, c.g);
	util_center_texture_rect(message_texture, &message_rect);
}

static void render(void) {
	view_render_parent();
	SDL_RenderCopy(display.renderer, message_texture, NULL, &message_rect);
}

view_t view_pause = {
	activate,
	deactivate,
	update,
	render
};