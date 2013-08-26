//
//  view.c
//  K2
//
//  Created by Justin Bowes on 2013-08-23.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "view.h"
#include <SDL2/SDL.h>
#include <string.h>
#include "app.h"
#include "k2_log.h"

#define VIEW_STACK_MAX	64

static void default_view_activate(void) {
	LOG_WARN("Default view was activated");
}

static void default_view_deactivate(void) {
}

static void default_view_update(void) {
}

static void default_view_render(void) {
	SDL_SetRenderDrawColor(display.renderer, game.ticks % 0xFF, (game.ticks + 86) % 0xFF, (game.ticks + 172) % 0xFF, 0xFF);
	SDL_RenderClear(display.renderer);
}

typedef struct {
	view_t views[VIEW_STACK_MAX];
	size_t current;
	size_t render_ptr;
} view_stack_t;

view_stack_t stack;

static view_t *current_view(void) {
	return &stack.views[stack.current];
}

static view_t *render_view(void) {
	return &stack.views[stack.render_ptr];
}

void view_init(void) {
	memset(&stack, 0, sizeof(stack));
	stack.views[0] = (view_t) {
		default_view_activate,
		default_view_deactivate,
		default_view_update,
		default_view_render
	};
}

void view_push(view_t *new_view) {
	++stack.current;
	stack.views[stack.current] = *new_view;
	current_view()->activate();
}

bool view_pop(void) {
	if (stack.current == 0) {
		return false;
	}
	
	current_view()->deactivate();
	--stack.current;
	return true;
}

void view_update(void) {
	stack.render_ptr = stack.current;
	current_view()->update();
}

void view_render(void) {
	stack.render_ptr = stack.current;
	current_view()->render();
	SDL_RenderPresent(display.renderer);
}

void view_update_parent(void) {
	if (stack.render_ptr == 0) {
		LOG_WARN("Can't update parent of last view");
		return;
	}
	
	--stack.render_ptr;
	render_view()->update();
}

void view_render_parent(void) {
	if (stack.render_ptr == 0) {
		LOG_WARN("Can't render parent of last view");
		return;
	}
	
	--stack.render_ptr;
	render_view()->render();
}