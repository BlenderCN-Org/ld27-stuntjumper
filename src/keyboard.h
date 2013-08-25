//
//  keyboard.h
//  K2
//
//  Created by Justin Bowes on 2013-08-24.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#ifndef K2_keyboard_h
#define K2_keyboard_h

#include <SDL2/SDL.h>
#include <stdbool.h>

void keyboard_init(void);
void keyboard_destroy(void);

bool keyboard_is_down(SDL_Keycode kc);

#endif