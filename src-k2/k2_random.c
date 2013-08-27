//
//  k2_random.c
//  K2
//
//  Created by Justin Bowes on 2013-08-24.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "k2_random.h"
#include <stdlib.h>

int k2_random_int(int min, int max_inclusive) {
	int range = max_inclusive - min + 1;
	int val = rand() % range;
	return val + min;
}