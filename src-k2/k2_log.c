//
//  k2_log.c
//  K2
//
//  Created by Justin Bowes on 2013-08-22.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "k2_log.h"

#if (K2_LOG_LEVEL < K2_LOG_LEVEL_OFF)
char ___k2_log_output[K2_LOG_MAX];
#endif