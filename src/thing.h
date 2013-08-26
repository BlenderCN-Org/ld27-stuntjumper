//
//  thing.h
//  K2
//
//  Created by Justin Bowes on 2013-08-23.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#ifndef K2_thing_h
#define K2_thing_h

#include "k2_ivec2.h"
#include "k2_vec2.h"
#include <stddef.h>

typedef enum {
	
	nothing			= 0,
	
	dude_stand			= 0x0001,
	dude_walk		= 0x0002,
	dude_dive		= 0x0003,
	dude_fall		= 0x0004,
	
	gull			= 0x0100,
	cat				= 0x0101,
	
	tshirt			= 0x0200,
	jeans			= 0x0202,
	bra				= 0x0203,
	dress			= 0x0204,
	
	fire_escape		= 0x0300,
	ladder			= 0x0301,

	awning			= 0x0400,
	
	clothesline		= 0x0500,
	
	building		= 0x0600,
	building_curtain,
	building_dark_escape,
	building_bright,
	building_venetian,
	building_tv,
	building_tv_fritz,
	building_tv_wtf,
	building_satellite,
	building_fullwidth,
	
	building_window_fg,
	building_window_backlight,
	
	ground			= 0x06FF,

	gibs			= 0x07FE,
	catchers		= 0x07FF,
	thing__last		= 0x0800
	
} thing_type_t;

typedef int32_t thing_id_t;

typedef struct {
	
	thing_type_t	type;
	
	size_t			current_frame;
	size_t			animate_timeout;
	
	size_t			action_timeout;
	
	xvec2			position;
	xvec2			velocity;
	xvec2			size;

	// never moves. causes deflect collisions
	bool			solid;

	thing_id_t		attached_to;
	xvec2			attach_offset;
	
	// causes downward acceleration UNLESS
	// solid or attached
	bool			gravitated;

	float			angle;
	float			rotation;
	
	bool			breakable;
	bool			broken;
	
	bool			wearing;
	bool			wearable;
	
} thing_t;

thing_id_t thing_at_position(xvec2 position, thing_id_t search_start);
thing_type_t thing_type(thing_id_t tid);

#endif
