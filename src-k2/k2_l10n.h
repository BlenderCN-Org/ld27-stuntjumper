//
//  k2_l10n.h
//  K2
//
//  Created by Justin Bowes on 2013-08-22.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#ifndef K2_k2_l10n_h
#define K2_k2_l10n_h

#include <cJSON/cJSON.h>
#include <stdint.h>
#include <stdbool.h>

#define L10N_MAX_ENTRIES	256
#define L10N_ENTRY_SIZE		1024

typedef struct {
	uint32_t	keys[L10N_MAX_ENTRIES];
	char		values[L10N_MAX_ENTRIES][L10N_ENTRY_SIZE];
	size_t		entries;
} k2_l10n_t;

void k2_l10n_init(k2_l10n_t *self, const char *l10n);
bool k2_l10n_get_success(const char *key, const char **pval);
const char * k2_l10n_get(const char *key);
int k2_l10n_printf(char *buf, size_t size, const char *key, ...);

#define kl(k)					k2_l10n_get(k)
#define kexist(k)				k2_l10n_get_success(k, 0);
#define klprintf(buf, bsize, k)	k2_l10n_printf(buf, bsize, k)

#endif
