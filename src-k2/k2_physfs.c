//
//  k2_physfs_init.c
//  K2
//
//  Created by Justin Bowes on 2013-08-22.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "k2_physfs.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <physfs/physfs.h>

#include "k2_log.h"
#include "k2_platform.h"

#if defined(K2_PLATFORM_APPLE)
#	include <strings.h>
#	define strnicmp(a, b, n) strncasecmp(a, b, n)
#elif defined(K2_PLATFORM_WINDOWS)
#	define strnicmp _strnicmp
#endif

/* Split out to avoid stack allocation in a loop. */
static void add_config_path(const char *i, const size_t l, const char *dirsep,
                              bool archives_first)
{
    const char *d = PHYSFS_getRealDir(i);
    const size_t allocsize = strlen(d) + strlen(dirsep) + l + 1;
    char *str = (char *) malloc(allocsize);
    if (str != NULL)
    {
        sprintf(str, "%s%s%s", d, dirsep, i);
		LOG_DEBUG("Mounting %s", str);
		PHYSFS_mount(str, NULL, !archives_first);
        free(str);
    } /* if */
} /* setSaneCfgAddPath */

#define BAIL_IF_MACRO(c, RC, k) { if (c) return RC; }

int k2_physfs_set_sane_config(const char *app_name,
                         const char *archive_extension,
                         bool archives_first)
{
	const char *organization = "Informi Labs";
	
    const char *basedir = PHYSFS_getBaseDir();
    const char *prefdir = PHYSFS_getPrefDir(organization, app_name);
    const char *dirsep = PHYSFS_getDirSeparator();

    if (!PHYSFS_setWriteDir(prefdir))
    {
		LOG_ERROR("Can't set write dir");
		return 0;
    } /* if */
	
    /* Put write dir first in search path... */
    PHYSFS_mount(prefdir, NULL, 0);
	
	char resource_path[PATH_MAX];
#if defined (K2_PLATFORM_APPLE)
	snprintf(resource_path, PATH_MAX, "%s%s", basedir,
			 "Contents/Resources/resources-pkg");
#else
	snprintf(resource_path, PATH_MAX, "%s%s", basedir,
			 "resources-pkg");	
#endif
	PHYSFS_mount(resource_path, NULL, 1);
	
	/* Put base path on search path... */
    PHYSFS_mount(basedir, NULL, 1);
	
	
	/* Root out archives, and add them to search path... */
    if (archive_extension != NULL)
    {
        char **rc = PHYSFS_enumerateFiles("/");
        char **i;
        size_t extlen = strlen(archive_extension);
        char *ext;
		
        for (i = rc; *i != NULL; i++)
        {
            size_t l = strlen(*i);
            if ((l > extlen) && ((*i)[l - extlen - 1] == '.'))
            {
                ext = (*i) + (l - extlen);
                if (strnicmp(ext, archive_extension, strlen(ext)) == 0)
                    add_config_path(*i, l, dirsep, archives_first);
            } /* if */
        } /* for */
		
        PHYSFS_freeList(rc);
    } /* if */
	
    return(1);
} /* PHYSFS_setSaneConfig */
