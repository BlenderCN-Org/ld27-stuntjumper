//
//  audio.c
//  K2
//
//  Created by Justin Bowes on 2013-08-23.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "audio.h"
#include "physfsrwops.h"
#include "k2_error.h"
#include "k2_log.h"

#define RATE		MIX_DEFAULT_FREQUENCY
#define FORMAT		MIX_DEFAULT_FORMAT
#define CHANNELS	MIX_DEFAULT_CHANNELS
#define CHUNK		1024

#define MIX_FADE	1000 // ms

audio_t audio;

static void play_music(void) {
	audio.music = audio.next_music;
	audio.next_music = NULL;
	if (audio.music) {
		Mix_PlayMusic(audio.music, -1);
	} else {
		LOG_INFO("No music to play");
	}
}

static void music_finished(void) {
	Mix_HaltMusic();
	play_music();
}

void audio_init(void) {
	memset(&audio, 0, sizeof(audio));
	if (Mix_Init(MIX_INIT_MOD | MIX_INIT_OGG | MIX_INIT_MP3) == -1) k2_abort("err_init", "Mix");
	if (Mix_OpenAudio(RATE, FORMAT, CHANNELS, CHUNK) == -1) k2_abort("err_audio");
	Mix_HookMusicFinished(music_finished);
}

void audio_destroy(void) {
	// Don't play this;
	if (audio.next_music) Mix_FreeMusic(audio.next_music);
	
	Mix_CloseAudio();
	while (Mix_Init(0)) {
		Mix_Quit();
	}
}

void audio_play_music(const char *file) {
	Mix_Music *next = Mix_LoadMUS_RW(PHYSFSRWOPS_openRead(file), true);
	if (! next) {
		LOG_ERROR("Music not loaded: %s", file);
	}
	
	if (audio.next_music) {
		// cancel transition.
		Mix_FreeMusic(audio.next_music);
	}
	
	audio.next_music = next;
	if (audio.music) {
		Mix_FadeOutMusic(MIX_FADE);
	} else {
		play_music();
	}
}