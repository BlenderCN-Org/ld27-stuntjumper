//
//  view_fade.h
//  K2
//
//  Created by Justin Bowes on 2013-08-25.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#ifndef K2_view_fade_h
#define K2_view_fade_h

#include "view.h"

extern view_t view_fade;

void view_fade_in(SDL_Color color);
void view_fade_out(SDL_Color color);
bool view_fade_done(void);

#endif