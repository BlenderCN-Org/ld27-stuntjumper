//
//  timer_blit.h
//  K2
//
//  Created by Justin Bowes on 2013-08-25.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#ifndef K2_timer_blit_h
#define K2_timer_blit_h

void timer_blit_init(void);
void timer_blit(uint32_t ticks, int right, int y);
void timer_blit_destroy(void);

#endif