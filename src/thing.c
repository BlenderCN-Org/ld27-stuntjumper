//
//  thing.c
//  K2
//
//  Created by Justin Bowes on 2013-08-24.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "thing.h"
#include "game.h"

thing_id_t thing_at_position(xvec2 position) {
	for (size_t i = 0; i < thing__last; ++i) {
		thing_t *t = &game.things[i];
		if (! t->type) continue;
		
		// This assumes no rotation.
		if (t->position.x > position.x) continue;
		if (t->position.y > position.y) continue;
		if (t->position.x + t->size.x <= position.x) continue;
		if (t->position.y + t->size.y <= position.y) continue;
		
		return (thing_id_t)i;
	}
	return -1;
}

thing_type_t thing_type(thing_id_t tid) {
	return game.things[tid].type;
}