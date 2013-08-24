//
//  sprites.h
//  K2
//
//  Created by Justin Bowes on 2013-08-24.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#ifndef K2_sprites_h
#define K2_sprites_h

#include "thing.h"

#define MAX_FRAMES 8

typedef struct sprite {
	SDL_Texture *texture;
	
	size_t frame_count;
	SDL_Rect src_rect[MAX_FRAMES];
} sprite_t;


void sprites_init(void);
void sprites_destroy(void);

sprite_t *sprite_get(thing_type_t thing_type);

#endif