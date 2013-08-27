//
//  _main.c
//  K2
//
//  Created by Justin Bowes on 2013-08-22.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include <physfs/physfs.h>
#include <cJSON/cJSON.h>
#include "sdl.h"

#include "k2_log.h"
#include "k2_physfs.h"
#include "k2_error.h"
#include "app.h"

static void quit(void) {
	LOG_INFO("Shutting down");
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
	
#if defined(K2_PLATFORM_WINDOWS)
    PHYSFS_init(NULL);
#else
	PHYSFS_init(argv[0]);
#endif
	if (! k2_physfs_set_sane_config(app.name, "zip", false))
		k2_abort("Couldn't initialize file system");	
	
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1)
                k2_abort("err_init", "SDL", SDL_GetError());
	if (TTF_Init() == -1) k2_abort("err_init", "TTF", SDL_GetError());
	if (IMG_Init(IMG_INIT_PNG) == -1) k2_abort("err_init", "IMG", SDL_GetError());
	
	app_init();

	core_loop();
	
	app_destroy();
}
