//
//  score.h
//  K2
//
//  Created by Justin Bowes on 2013-08-25.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#ifndef K2_score_h
#define K2_score_h

typedef enum {
	ach_every_cat,
	ach_no_cat,
	
	ach_every_satellite,
	ach_no_satellite,
	
	ach_every_dress,
	ach_every_bra,
	ach_every_jeans,
	ach_every_tshirt,
	ach_every_clothes,
	
	ach_every_fire_escape,
	ach_no_fire_escape,
	
	ach_first_run,
	
	ach_no_left_arrow,
	ach_no_no_left_arrow,	
	
	ach_everything_broken,
	ach_nothing_broken,
	
	ach_replay,
	
	ach_rounds_5,
	ach_rounds_10,
	ach_rounds_25,
	ach_rounds_100,
	ach_rounds_500,
	ach_rounds_1000,
	
	panel_timer,
	panel_achievement,

	sui_arrow_left,
	sui_arrow_right,
	
	score_sprite__last
} score_sprites_t;

enum {
	every_cat,
	no_cat,
	
	every_satellite,
	no_satellite,
	
	every_dress,
	every_bra,
	every_jeans,
	every_tshirt,
	
	every_clothes,
	
	every_fire_escape,
	no_fire_escape,
	
	first_run,
	
	no_left_arrow,
	no_no_left_arrow,
	
	everything_broken,
	nothing_broken,
	
	replay,
	
	rounds_5,
	rounds_10,
	rounds_25,
	rounds_100,
	rounds_250,
	rounds_1000,
	
	bp__last
} score_bprops;

extern const char *score_bkeys[];

enum {
	fastest_run,
	slowest_run,
	rounds_played,
	
	uip__last
} score_uiprops;

extern const char *score_uikeys[];

typedef struct {
	uint8_t		version;
	
	bool		bprops[bp__last];
	uint32_t	uiprops[uip__last];
	
} score_t;

extern score_t score_lifetime;

void score_init(void);
void score_init_instance(score_t *score);
void score_consolidate(void);
void score_save(void);

#endif