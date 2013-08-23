//
//  process_manager.h
//  K2
//
//  Created by Justin Bowes on 2013-08-23.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#ifndef K2_process_manager_h
#define K2_process_manager_h

#include <stdbool.h>

typedef void(process_func)(void);

void process_init(void);
void process_update(void);

void process_add(process_func *process);
bool process_remove(process_func *process);

#endif