//
//  display.h
//  K2
//
//  Created by Justin Bowes on 2013-08-23.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#ifndef K2_display_h
#define K2_display_h

#include <SDL2/SDL.h>

#define REFERENCE_WIDTH		128
#define REFERENCE_HEIGHT	256

typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_RendererInfo renderer_info;
} display_t;

extern display_t display;

void display_init(void);

#endif
