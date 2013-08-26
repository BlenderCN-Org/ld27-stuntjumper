//
//  k2_physfs.h
//  K2
//
//  Created by Justin Bowes on 2013-08-22.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#ifndef K2_k2_physfs_h
#define K2_k2_physfs_h

#include <stdbool.h>
#include "physfs.h"

int k2_physfs_set_sane_config(const char *appName, const char *archiveExt, bool archivesFirst);

#endif
