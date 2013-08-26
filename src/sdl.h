/* 
 * File:   sdl.h
 * Author: Justin
 *
 * Created on August 26, 2013, 12:55 AM
 */

#ifndef SDL_H
#define	SDL_H

#include "k2_platform.h"

#if defined(K2_PLATFORM_WINDOWS)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#elif defined(K2_PLATFORM_OSX)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#else
#error Unconfigured platform
#endif

#endif	/* SDL_H */

