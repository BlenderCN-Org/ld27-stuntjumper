//
//  view.h
//  K2
//
//  Created by Justin Bowes on 2013-08-22.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#ifndef K2_view_h
#define K2_view_h

typedef void (view_activate_func)(void);
typedef void (view_deactivate_func)(void);
typedef void (view_update_func)(void);
typedef void (view_render_func)(void);

typedef struct {
	view_activate_func		*activate;
	view_deactivate_func	*deactivate;
	view_update_func		*update;
	view_render_func		*render;
} view_t;

void view_init(void);
void view_set(view_t *view);
void view_update(void);
void view_render(void);

#endif
