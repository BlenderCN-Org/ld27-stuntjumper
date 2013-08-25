//
//  processes.c
//  K2
//
//  Created by Justin Bowes on 2013-08-24.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "processes.h"
#include "create_level.h"
#include "app.h"
#include "k2_log.h"

#define GRAVITY		1.0f / 60.f
#define MAX_DOWN	1000.f / 60.f // roughly 8192 in 10 seconds

#define INPUT_INTERVAL		5
#define FRAME_INTERVAL		3
#define DUDE_DIVE_SPEED		0.3f
#define DUDE_WALK_SPEED		0.3f
#define DUDE_FALL_CONTROL	0.005f
#define VELOCITY_X_DAMPING	0.007f

#define RANDOM_ROTATION		0.5

#define COEFF_REST			0.3		// but not for dude

// --------------------------------------------------------------------------

void process_animate(void) {
	for (size_t i = 0; i < MAX_THINGS; ++i) {
		thing_t *tp = &game.things[i];
		if (! tp->type) continue;
		
		sprite_t *sprite = sprite_get(tp->type);
		if (sprite->frame_count == 0) continue;
		
		if (tp->animate_timeout > 0) {
			--tp->animate_timeout;
			continue;
		}
		
		tp->current_frame = (tp->current_frame + 1) % sprite->frame_count;
		
		tp->animate_timeout = FRAME_INTERVAL * sprite->rate;
	}
}

// --------------------------------------------------------------------------

void process_attached(void) {
	const float angles[] = { 260, 225, 190, 170, 135, 90 };
	
	for (size_t i = 0; i < MAX_THINGS; ++i) {
		thing_t *tp = &game.things[i];
		if (! tp->type) continue;
		if (! tp->attached_to) continue;
		
		thing_t *parent = &game.things[tp->attached_to];
		tp->position = xvec2_add(parent->position, tp->attach_offset);
		
		if (tp->attached_to == game.dude_id) {
			if (tp->wearing && parent->type == dude_fall) {
				tp->angle = angles[parent->current_frame];
				if (tp->type == tshirt) tp->angle += 180;
			}
		}
	}
}

// --------------------------------------------------------------------------

void process_collide(void) {
	thing_t *dp = &game.things[game.dude_id];
	xvec2 center = xvec2_add(dp->position, xvec2_all(16.f));
	thing_id_t touching = thing_at_position(center, 0);
	while (touching != -1) {
		
		thing_t *collide = &game.things[touching];
		
		if (collide->solid) {
			// easy linear bounceback
			dp->velocity.x += collide->size.x / (dp->position.x - collide->position.x);
			// That's it. scram
		} else if (collide->attached_to && collide->attached_to != game.dude_id) {
			if (collide->wearable) {
				// Delete and recreate, because it needs to go in front.
				thing_t *newcollide = game_add_thing(collide->type, NULL);
				*newcollide = *collide;
				newcollide->attached_to = game.dude_id;
				newcollide->wearing = true;
				newcollide->attach_offset = xvec2_all(0.f);
				
				if (newcollide->type == bra) {
					newcollide->position.y -= 10; // better fit
				}
				
				// bye bye old one
				collide->type = nothing;
				dp->velocity.y *= 0.5;
				
			} else if (collide->breakable) {
				if (collide->attached_to) {
					thing_t *parent = &game.things[collide->attached_to];
					parent->broken = true;
					if (parent->type == building_tv) {
						parent->type = building_tv_fritz;
						parent->current_frame = 1;
						parent->animate_timeout = 0;
					}
				}
				collide->attached_to = 0;
				dp->velocity.y *= 0.5;
				collide->velocity.x = 1.5 * dp->velocity.x;
				dp->velocity.x -= collide->velocity.x;
				collide->rotation = util_frand() * RANDOM_ROTATION - (RANDOM_ROTATION / 2.f);
			}
		}
		
		touching = thing_at_position(center, touching + 1);
	}
	
}

// --------------------------------------------------------------------------

static void process_dude_fall(thing_t *dt) {
	float move;
	if (dt->current_frame <= 2) {
		move = (3.0f - dt->current_frame) / 3.0f;
		dt->velocity.x -= DUDE_FALL_CONTROL * move;
	} else {
		move = (dt->current_frame - 3.0f) / 3.0f;
		dt->velocity.x += DUDE_FALL_CONTROL * move;
	}
}

static void process_dude_walk(thing_t *dt) {
	dt->position.x += DUDE_WALK_SPEED;
	if (dt->position.x > 16 + rand() % 8) {
		dt->type = dude_dive;
		dt->current_frame = 0;
		dt->velocity.x = util_frand() * DUDE_DIVE_SPEED + DUDE_DIVE_SPEED;
		dt->velocity.y = 0.2;
		dt->gravitated = true;
	}
}

static void process_dude_dive(thing_t *dt) {
	if (dt->current_frame == 0 && dt->position.y > 5.0) {
		// we've fallen somewhat but the current frame is 0, we've looped.
		dt->type = dude_fall;
		dt->current_frame = 5; // dive blends into this frame.
		dt->animate_timeout = SIZE_T_MAX;
	}
}

void process_dude(void) {
	thing_t *dt = &game.things[game.dude_id];
	switch (dt->type) {
		case dude:
			// cmon hero
			// cmon
			// cmon hero
			audio_pause_music();
			break;
			
		case dude_walk:
			// YEAH!
			audio_resume_music();
			process_dude_walk(dt);
			break;
			
		case dude_dive:
			process_dude_dive(dt);
			break;
			
		case dude_fall:
			process_dude_fall(dt);
			break;
			
		default:
			break;
	}
	
	if (dt->type >= dude_dive) {
		++game.rescue_ticks;
	}
}

// --------------------------------------------------------------------------

void process_gravity(void) {
	for (size_t i = 0; i < MAX_THINGS; ++i) {
		if (! game.things[i].type) continue;
		
		if (game.things[i].solid) continue;
		if (game.things[i].attached_to) continue;
		
		if (! game.things[i].gravitated) continue;
		
		game.things[i].velocity.y += GRAVITY;
		if (game.things[i].velocity.y > MAX_DOWN) game.things[i].velocity.y = MAX_DOWN;
	}
}

// --------------------------------------------------------------------------


static void handle_dude_left(thing_t *dt) {
	if (dt->type != dude_fall) return;
	
	if (dt->current_frame > 0) --dt->current_frame;
	game.input_timeout = INPUT_INTERVAL;
}

static void handle_dude_right(thing_t *dt) {
	switch (dt->type) {
		case dude:
			dt->type = dude_walk;
			break;
		case dude_walk:
			break;
		case dude_dive:
			return;
		case dude_fall:
			//frames are (left)0,1,2,3,4,5(right)
			if (dt->current_frame < 5) ++dt->current_frame;
			break;
		default:
			return;
	}
	game.input_timeout = INPUT_INTERVAL;
}

void process_input(void) {
	thing_t *dt = &game.things[game.dude_id];
	if (game.input_timeout) {
		--game.input_timeout;
		return;
	}
	
	if (keyboard_is_down(SDLK_LEFT)) handle_dude_left(dt);
	if (keyboard_is_down(SDLK_RIGHT)) handle_dude_right(dt);
	
	if (dt->type == dude_walk && ! game.input_timeout) {
		// no keys down and dude_walk becomes dude.
		dt->type = dude;
		dt->current_frame = 0;
	}
}

// --------------------------------------------------------------------------


void process_momentum(void) {
	for (size_t i = 0; i < MAX_THINGS; ++i) {
		thing_t *tp = &game.things[i];
		if (! tp->type) continue;
		
		if (tp->attached_to) continue;
		if (tp->solid) continue;
		if (tp->type <= dude_walk) continue;

		tp->position = xvec2_add(tp->position, tp->velocity);
		LOG_DEBUG("position: %f", tp->position.y);
		
		tp->velocity.x *= (1.f - VELOCITY_X_DAMPING);
		tp->angle += tp->rotation;
		
		if (tp->position.x > REFERENCE_WIDTH) {
			tp->position.x = REFERENCE_WIDTH - (tp->position.x - REFERENCE_WIDTH);
			tp->velocity.x = -fabsf(tp->velocity.x);
		}
		if (tp->position.x < 0) {
			tp->position.x = -tp->position.x;
			tp->velocity.x = fabsf(tp->velocity.x);
		}
		
		if (tp->position.y > BUILDING_HEIGHT) {
			if (tp->type == dude_fall) {
				tp->position = xvec2_set(tp->position.x - 16, BUILDING_HEIGHT - 8);
				tp->velocity = xvec2_all(0.f);
				tp->type = gibs;
				tp->current_frame = 0;
				tp->gravitated = false;
				tp->solid = true;
			} else {
				tp->position.y = BUILDING_HEIGHT - (tp->position.y - BUILDING_HEIGHT);
				tp->velocity.y = -COEFF_REST * tp->velocity.y;
				if (tp->velocity.y < 0.1) {
					tp->rotation = 0;
				}
			}
		}
	}
}

