//
//  app.c
//  K2
//
//  Created by Justin Bowes on 2013-08-23.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "app.h"

app_t app = {
	.name = "K2 test app",
	.exit = false
};

static bool quit_request(SDL_Event *event) {
	app.exit = true;
	SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
	return true;
}

void app_init(void) {
	config_init();
	display_init();
	event_init();
	window_init();
	audio_init();
	process_init();
	view_init();
	timer_init(&game.ticks, config.frame_interval, 10 * config.frame_interval);
	game_init();
	
	event_add_handler(NULL, quit_request, SDL_QUIT);
	
	audio_play_music("music/haunting torgo theme.mp3");
}

void app_destroy() {
//	config_destroy();
//	display_destroy();
//	event_destroy();
//	window_destroy();
	audio_destroy();
//	process_destroy();
//	view_destroy();
//	timer_destroy();
//	game_destroy();
}