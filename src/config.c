//
//  config.c
//  K2
//
//  Created by Justin Bowes on 2013-08-22.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "config.h"
#include "k2_l10n.h"

#include <string.h>

config_t config;
k2_l10n_t l10n;

void config_init(void) {
	memset(&config, 0, sizeof(config));
	
	strncat(config.language, "en", 8);
	config.frame_interval = 1000 / 60;

	k2_l10n_init(&l10n, config.language);
}
