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
#include "score.h"

#define MAX_FRAMES 8

typedef struct sprite {
	SDL_Texture *texture;
	
	size_t frame_count;
	size_t rate;
	SDL_Rect src_rect[MAX_FRAMES];
} sprite_t;


void sprites_init(void);
void sprites_destroy(void);

sprite_t *sprite_thing_get(thing_type_t thing_type);
sprite_t *sprite_score_get(score_sprites_t score_sprite);

#endif