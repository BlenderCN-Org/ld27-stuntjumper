//
//  display.c
//  K2
//
//  Created by Justin Bowes on 2013-08-23.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "display.h"
#include "app.h"
#include "k2_error.h"

display_t display;

void display_init(void) {
	uint32_t flags = 0, width = 0, height = 0;
	flags |= SDL_RENDERER_ACCELERATED;
	flags |= SDL_RENDERER_PRESENTVSYNC;
	if (config.fullscreen) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	} else {
		width = REFERENCE_WIDTH << 2;
		height = REFERENCE_HEIGHT << 2;
	}
	SDL_CreateWindowAndRenderer(width, height, flags, &display.window, &display.renderer);
	SDL_GetRendererInfo(display.renderer, &display.renderer_info);
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest"); // pixelate
	SDL_RenderSetLogicalSize(display.renderer, REFERENCE_WIDTH, REFERENCE_HEIGHT);
	
	if (! display.renderer_info.flags & SDL_RENDERER_ACCELERATED) k2_abort("err_accel");
	
	if (! display.renderer_info.flags & SDL_RENDERER_TARGETTEXTURE)	k2_abort("err_accel");
	
	SDL_SetRenderDrawColor(display.renderer, 0xFF, 0xFF, 0x0, 0xFF);
	SDL_RenderClear(display.renderer);
	SDL_RenderPresent(display.renderer);
}