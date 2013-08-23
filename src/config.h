//
//  config.h
//  K2
//
//  Created by Justin Bowes on 2013-08-22.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#ifndef K2_config_h
#define K2_config_h

#include <stdbool.h>
#include <stdint.h>

typedef struct {
	char		language[8];
	uint32_t	frame_interval;
	bool		fullscreen;
} config_t;

extern config_t config;

void config_init(void);

#endif
