//
//  view_building.c
//  K2
//
//  Created by Justin Bowes on 2013-08-24.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "view_building.h"
#include "sprites.h"

sprite_t sky;
sprite_t building_sheet;

static void activate(void) {
	sky.texture = util_create_texture("sprite/sky.png", sky.src_rect);
	building_sheet.texture = util_create_texture("sprite/building.png", building_sheet.src_rect);
}

static void deactivate(void) {
	
}

static void update(void) {
}

SDL_Rect target_rect(sprite_t *sprite, int x, int y) {
	return (SDL_Rect) { x, y, sprite->src_rect[0].w, sprite->src_rect[0].h };
}

static void render(void) {
	SDL_Rect target = target_rect(&sky, 0, 0);
	SDL_RenderCopy(display.renderer, sky.texture, sky.src_rect, &target);
	for (size_t i = 0; i < MAX_THINGS; ++i) {
		thing_t *thing = &game.things[i];
		if (! thing->type) continue;
		sprite_t *sprite = sprite_get(thing->type);
		target = target_rect(sprite, thing->position.x, thing->position.y);
		SDL_RenderCopy(display.renderer, sprite->texture, &sprite->src_rect[thing->current_frame], &target);
	}
}



view_t view_building = {
	activate,
	deactivate,
	update,
	render
};
