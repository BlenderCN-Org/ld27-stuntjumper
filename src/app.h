//
//  app.h
//  K2
//
//  Created by Justin Bowes on 2013-08-22.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#ifndef K2_app_h
#define K2_app_h

#include "audio.h"
#include "config.h"
#include "core.h"
#include "display.h"
#include "event.h"
#include "game.h"
#include "keyboard.h"
#include "process.h"
#include "score.h"
#include "sprites.h"
#include "timer.h"
#include "timer_blit.h"
#include "view.h"
#include "window.h"

#include "util.h"
#include "physfsrwops.h"
#include "k2_l10n.h"

typedef struct {
	const char *name;
	bool exit;
} app_t;

extern app_t app;

void app_init(void);
void app_destroy(void);

#endif
