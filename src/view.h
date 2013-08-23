//
//  view.h
//  K2
//
//  Created by Justin Bowes on 2013-08-22.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#ifndef K2_view_h
#define K2_view_h

typedef void (view_activate)(void);
typedef void (view_deactivate)(void);
typedef void (view_update)(double interval);
typedef void (view_render)(void);

typedef struct {
	view_activate	*activate;
	view_deactivate *deactivate;
	view_update		*update;
	view_render		*render;
} view_t;

extern view_t view;

void view_init(void);

#endif
