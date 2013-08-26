//
//  util.c
//  K2
//
//  Created by Justin Bowes on 2013-08-23.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "physfsrwops.h"
#include "display.h"
#include "util.h"
#include "k2_ivec2.h"
#include "k2_error.h"

void util_center_texture_rect(SDL_Texture *texture, SDL_Rect *rect) {
	SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h);
	rect->x = (REFERENCE_WIDTH - rect->w) >> 1;
	rect->y = (REFERENCE_HEIGHT - rect->h) >> 1;
}

void util_sprite_from_surf(sprite_t *sprite, size_t index, SDL_Surface *surface) {
	sprite->src_rect[index] = (SDL_Rect) { 0, 0, surface->w, surface->h };
	sprite->texture = SDL_CreateTextureFromSurface(display.renderer, surface);
}

SDL_Texture *util_create_texture(const char *file, SDL_Rect *rect_out) {
    SDL_RWops *ops = PHYSFSRWOPS_openRead(file);
	SDL_Surface *surface = IMG_Load_RW(ops, true);
	if (! surface) k2_abort("err_texture", SDL_GetError());
	*rect_out = (SDL_Rect) { 0, 0, surface->w, surface->h };
	SDL_Texture *texture = SDL_CreateTextureFromSurface(display.renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

static const SDL_Color white = { 0xFF, 0xFF, 0xFF, 0xFF };

SDL_Texture *util_create_font_texture(const char *message, int point_size, uint32_t wrap_at, SDL_Rect *rect_out) {
	PHYSFS_File *pf = PHYSFS_openRead(FONT);
	SDL_RWops *file = PHYSFSRWOPS_makeRWops(pf);
	TTF_Font *font = TTF_OpenFontRW(file, true, point_size);
	SDL_Surface *surf = (wrap_at > 0 ?
						 TTF_RenderUTF8_Blended_Wrapped(font, message, white, wrap_at) :
						 TTF_RenderUTF8_Blended(font, message, white));
	SDL_Texture *message_texture = SDL_CreateTextureFromSurface(display.renderer, surf);
	
	if (rect_out) {
		*rect_out = (SDL_Rect) { 0, 0, surf->w, surf->h };
	}
	
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	SDL_RWclose(file);
	return message_texture;
}