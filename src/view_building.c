//
//  view_building.c
//  K2
//
//  Created by Justin Bowes on 2013-08-24.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "create_level.h"
#include "view_building.h"
#include "sprites.h"
#include "k2_log.h"
#include "timer_blit.h"

#define SUNSET_SPEED 0.01f

static sprite_t sky;
static float sunset;
static struct {
	xvec2 target;
	xvec2 current;
	xvec2 offset;
} camera;

static void activate(void) {
	memset(&camera, 0, sizeof(camera));
	camera.current.x = camera.target.x = REFERENCE_WIDTH / 2;
	camera.current.y = BUILDING_HEIGHT - REFERENCE_HEIGHT / 2;
	sky.texture = util_create_texture("sprite/sky.png", sky.src_rect);
	
	audio_music_play("music/bgm.ogg");
	
	sunset = 0.f;
}

static void deactivate(void) {
	SDL_DestroyTexture(sky.texture);
}

static void update_camera(void) {
	const xvec2 halfscreen = xvec2_set(REFERENCE_WIDTH / 2, REFERENCE_HEIGHT / 2);

	thing_t *dude = &game.things[game.dude_id];
	xvec2 *dudepos = &dude->position;
	camera.target.y = dudepos->y;
	
	if (camera.target.y == 0.f) {
		xvec2 drama_target = xvec2_set(camera.target.x, REFERENCE_HEIGHT * -0.28f);
		float drama_mix = 1.f - (fmaxf(dudepos->x + 16.f, 0.f) / 48.f);
		camera.target = xvec2_mix(camera.target, drama_target, drama_mix);
	}
	
	camera.target.y = fminf(BUILDING_HEIGHT + 16 - halfscreen.y, camera.target.y);
	
	float mix_rate = (dude->type < dude_dive ? 0.01 : 0.3);
	
	camera.current = xvec2_mix(camera.current, camera.target, mix_rate);
	camera.offset = xvec2_set(camera.current.x - halfscreen.x, camera.current.y - halfscreen.y);
	
	LOG_TRACE("Camera: %f %f (moving to %f %f) (offset %f %f)",
			  camera.current.x, camera.current.y,
			  camera.target.x, camera.target.y,
			  camera.offset.x, camera.offset.y);
}

static void update_sunset(void) {
	// if it's safe to move the sun...
	if (camera.target.y > 1000) {
		sunset = fminf(sunset + SUNSET_SPEED, sky.src_rect[0].h - REFERENCE_HEIGHT);
	}
}

static void update(void) {
	update_camera();
	update_sunset();
}

SDL_Rect target_rect(sprite_t *sprite, int x, int y, float offset_mult) {
	return (SDL_Rect) {
		x - offset_mult * camera.offset.x,
		y - offset_mult * camera.offset.y,
		sprite->src_rect[0].w,
		sprite->src_rect[0].h
	};
}

static void render(void) {
	SDL_Rect target = target_rect(&sky, -64, (REFERENCE_HEIGHT - BUILDING_HEIGHT / 4) - 128, 0.25f);
	target.y += sunset;
	SDL_RenderCopy(display.renderer, sky.texture, sky.src_rect, &target);
	for (size_t i = 0; i < MAX_THINGS; ++i) {
		thing_t *thing = &game.things[i];
		if (! thing->type) continue;
		sprite_t *sprite = sprite_thing_get(thing->type);
		target = target_rect(sprite, thing->position.x, thing->position.y, 1.f);
		
		if (thing->current_frame > sprite->frame_count) {
			LOG_WARN("%llu frame out of range!", (long long unsigned)i);
			thing->current_frame = 0;
		}
		
		SDL_RenderCopyEx(display.renderer, sprite->texture,
						 &sprite->src_rect[thing->current_frame], &target, thing->angle, NULL, 0);
	}
	
	if (camera.target.y > 0) {
		timer_blit(game.active_ticks, REFERENCE_WIDTH - 10, 10);
	}
	
}



view_t view_building = {
	activate,
	deactivate,
	update,
	render
};
