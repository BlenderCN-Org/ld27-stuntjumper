//
//  audio.h
//  K2
//
//  Created by Justin Bowes on 2013-08-23.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#ifndef K2_audio_h
#define K2_audio_h

#include "sdl.h"

void audio_init(void);
void audio_destroy(void);

void audio_music_play(const char *file);
void audio_play(const char *file);

void audio_music_pause(void);
void audio_music_resume(void);
void audio_music_fade(void);

#endif
