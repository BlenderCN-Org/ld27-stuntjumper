//
//  process_manager.c
//  K2
//
//  Created by Justin Bowes on 2013-08-23.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "process.h"

#include <string.h>
#include <stdint.h>

#define MAX_PROCESSES 256

typedef struct {
	process_func *process[MAX_PROCESSES];
	size_t last_process;
} process_manager_t;

static process_manager_t processes;

void process_init(void) {
	memset(&processes, 0, sizeof(processes));
}

void process_update(void) {
	for (size_t i = 0; i < MAX_PROCESSES; ++i) {
		if (processes.process[i]) {
			processes.process[i]();
		}
	}
}

void process_add(process_func *process) {
	processes.process[processes.last_process + 1] = process;
	processes.last_process = (processes.last_process + 1) % MAX_PROCESSES;
}

bool process_remove(process_func *process) {
	for (size_t i = 0; i < MAX_PROCESSES; ++i) {
		if (processes.process[i] == process) {
			processes.process[i] = NULL;
			return true;
		}
	}
	return false;
}

