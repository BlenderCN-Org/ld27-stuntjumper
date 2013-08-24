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

void util_center_texture_rect(SDL_Texture *texture, SDL_Rect *rect_out);
SDL_Texture *util_create_texture(const char *file, SDL_Rect *rect_out);

#endif