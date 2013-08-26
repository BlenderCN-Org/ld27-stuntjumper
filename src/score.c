//
//  score.c
//  K2
//
//  Created by Justin Bowes on 2013-08-25.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "score.h"
#include "app.h"
#include "k2_log.h"
#include "k2_error.h"

#define SCORE_VERSION 1

score_t score_lifetime;

const char *score_bkeys[] = {
	"score_every_cat",
	"score_no_cat",
	
	"score_every_satellite",
	"score_no_satellite",
	
	"score_every_dress",
	"score_every_bra",
	"score_every_jeans",
	"score_every_tshirt",
	
	"score_every_clothes",
	
	"score_every_fire_escape",
	"score_no_fire_escape",
	
	"score_first_run",
	
	"score_no_left_arrow",
	"score_no_no_left_arrow",
	
	"score_everything_broken",
	"score_nothing_broken",
	
	"score_replay",
	
	"score_rounds_5",
	"score_rounds_10",
	"score_rounds_25",
	"score_rounds_100",
	"score_rounds_250",
	"score_rounds_1000"
};

const char *score_uikeys[] = {
	"score_fastest_run",
	"score_slowest_run",
	"score_rounds_played"
};

void score_init(void) {
	score_lifetime.version = 0;
	PHYSFS_File *file = PHYSFS_openRead("score.dat");
	if (file) {
		score_t loaded;
		PHYSFS_readBytes(file, &loaded, sizeof(loaded));
		PHYSFS_close(file);
		
		if (loaded.version == SCORE_VERSION) {
			score_lifetime = loaded;
			game.score.bprops[replay] = true;
		} else {
			LOG_WARN("Score version mismatch forces reset: got %uc", loaded.version);
		}
	}
	
	if (! score_lifetime.version) {
		score_init_instance(&score_lifetime);
	}
	
	// verify we can save
	score_save();
}

void score_init_instance(score_t *score) {
	memset(&score_lifetime, 0, sizeof(score_lifetime));
	score->version = SCORE_VERSION;
	score->uiprops[fastest_run] = UINT32_MAX;
}

void score_consolidate(void) {
	
	// bools we can batch
	for (size_t i = 0; i < bp__last; ++i) {
		score_lifetime.bprops[i] = score_lifetime.bprops[i] || game.score.bprops[i];
	}
	
	
	score_lifetime.uiprops[rounds_played] += game.score.uiprops[rounds_played];
	if (game.score.uiprops[fastest_run] < score_lifetime.uiprops[fastest_run]) {
		score_lifetime.uiprops[fastest_run] = game.score.uiprops[fastest_run];
	}
	if (game.score.uiprops[slowest_run] > score_lifetime.uiprops[slowest_run]) {
		score_lifetime.uiprops[slowest_run] = game.score.uiprops[slowest_run];
	}
	
	score_save();
}

void score_save(void) {
	PHYSFS_File *file = PHYSFS_openWrite("score.dat");
	if (! file) {
		k2_abort("err_write_save");
	}
	PHYSFS_writeBytes(file, &score_lifetime, sizeof(score_lifetime));
}