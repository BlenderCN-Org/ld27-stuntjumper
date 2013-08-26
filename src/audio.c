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
#define CHANNELS	MIX_CHANNELS
#define CHUNK		1024

#define MIX_FADE	1000 // ms

typedef struct {
	Mix_Music *music;
	Mix_Music *next_music;
	
	Mix_Chunk *current_chunks[CHANNELS];
} audio_t;

static audio_t audio;

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
	if (audio.music) Mix_FreeMusic(audio.music); 
	play_music();
}

static void channel_finished(int channel) {
	Mix_FreeChunk(audio.current_chunks[channel]);
	audio.current_chunks[channel] = NULL;
}

void audio_init(void) {
	memset(&audio, 0, sizeof(audio));
	if (Mix_Init(MIX_INIT_MOD | MIX_INIT_OGG | MIX_INIT_MP3) == -1) k2_abort("err_init", "Mix");
	if (Mix_OpenAudio(RATE, FORMAT, MIX_DEFAULT_CHANNELS, CHUNK) == -1) k2_abort("err_audio");
	Mix_HookMusicFinished(music_finished);
	Mix_ChannelFinished(channel_finished);
}

void audio_destroy(void) {
	// Don't play this;
	if (audio.next_music) Mix_FreeMusic(audio.next_music);
	
	Mix_CloseAudio();
	while (Mix_Init(0)) {
		Mix_Quit();
	}
}

void audio_music_play(const char *file) {
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

void audio_music_fade(void) {
	if (audio.music) {
		Mix_FadeOutMusic(MIX_FADE);
	}
}

void audio_play(const char *file) {
	Mix_Chunk *chunk = Mix_LoadWAV_RW(PHYSFSRWOPS_openRead(file), true);
	size_t channel = Mix_PlayChannel(-1, chunk, 0);
	audio.current_chunks[channel] = chunk;
}

void audio_music_pause(void) {
	Mix_PauseMusic();
}

void audio_music_resume(void) {
	Mix_ResumeMusic();
}