//
//  util.h
//  K2
//
//  Created by Justin Bowes on 2013-08-23.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#ifndef K2_util_h
#define K2_util_h

#include <SDL2/SDL.h>
#include "k2_platform.h"
#include "sprites.h"

void util_center_texture_rect(SDL_Texture *texture, SDL_Rect *rect_out);
void util_sprite_from_surf(sprite_t *sprite, size_t index, SDL_Surface *surface);
SDL_Texture *util_create_texture(const char *file, SDL_Rect *rect_out);

K2_INLINE float util_frand(void) {
	return (float) rand() / (float) RAND_MAX;
}

#endif