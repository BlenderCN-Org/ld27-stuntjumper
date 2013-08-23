//
//  audio.h
//  K2
//
//  Created by Justin Bowes on 2013-08-23.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#ifndef K2_audio_h
#define K2_audio_h

#include <SDL2_mixer/SDL_mixer.h>

typedef struct {
	Mix_Music *music;
	Mix_Music *next_music;
} audio_t;

extern audio_t audio;

void audio_init(void);
void audio_destroy(void);

void audio_play_music(const char *file);

#endif
