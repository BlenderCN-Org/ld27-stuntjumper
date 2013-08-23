//
//  _main.c
//  K2
//
//  Created by Justin Bowes on 2013-08-22.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <physfs/physfs.h>
#include <cJSON/cJSON.h>

#include "k2_log.h"
#include "k2_physfs.h"
#include "k2_error.h"
#include "app.h"

static void quit(void) {
	LOG_INFO("Shutting down");
	audio_destroy();
	while (IMG_Init(0)) {
		IMG_Quit();
	}
	if (TTF_WasInit()) TTF_Quit();
	if (SDL_WasInit(0)) SDL_Quit();
}

int main(int argc, char *argv[])
{
	display.window = NULL;
	atexit(quit);
	
	PHYSFS_init(argv[0]);
	if (! k2_physfs_set_sane_config(app_name, "zip", false))
		k2_abort("Couldn't initialize file system");	
	
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1)
		k2_abort("err_init", "SDL");
	if (TTF_Init() == -1) k2_abort("err_init", "TTF");
	if (IMG_Init(IMG_INIT_PNG) == -1) k2_abort("err_init", "IMG");
	
	config_init();
	display_init();
	audio_init();
	view_init();
	game_init();
	
	audio_play_music("music/minutewaltz.mp3");
	while (1) {
		
	}
}
