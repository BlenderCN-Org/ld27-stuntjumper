//
//  k2_l10n.c
//  K2
//
//  Created by Justin Bowes on 2013-08-22.
//  Copyright (c) 2013 Informi Software Inc. All rights reserved.
//

#include "k2_l10n.h"
#include "k2_hash.h"
#include "k2_log.h"
#include <physfs/physfs.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

k2_l10n_t *last_used = NULL;

static void parse_l10n_section(cJSON *section) {
	cJSON *entry = section->child;
	while (entry) {
		last_used->keys[last_used->entries] = k2_hash_string(entry->string);
		strncat(last_used->values[last_used->entries], entry->valuestring, L10N_ENTRY_SIZE);
		++ last_used->entries;
		entry = entry->next;
	}
}

static void parse_l10n_file(const char *filename, const char *l10n) {
	PHYSFS_File *file = PHYSFS_openRead(filename);
	if (! file) {
		LOG_ERROR("Couldn't read %s", filename);
	}
	size_t length = PHYSFS_fileLength(file);
	char buf[length + 1];
	buf[length] = '\0';
	PHYSFS_readBytes(file, buf, length);
	
	cJSON *doc = cJSON_Parse(buf);
	if (! doc) {
		LOG_ERROR("%s not in expected format\n"
				  "%s", filename, cJSON_GetErrorPtr());
		return;
	}
	cJSON *common = cJSON_GetObjectItem(doc, "common");
	if (common) parse_l10n_section(common);
	
	cJSON *language = cJSON_GetObjectItem(doc, l10n);
	if (language) parse_l10n_section(language);
	
	if (common == NULL && language == NULL) {
		LOG_ERROR("%s not a localization file", filename);
	}
	
	cJSON_Delete(doc);
}

void k2_l10n_init(k2_l10n_t *self, const char *l10n) {
	last_used = self;
	memset(self, 0, sizeof(*self));
	
	char **localization_files = PHYSFS_enumerateFiles("l10n");
	for (char **i = localization_files; *i; ++i) {
		char pathname[PATH_MAX];
		snprintf(pathname, PATH_MAX, "l10n%s%s", PHYSFS_getDirSeparator(), *i);
		parse_l10n_file(pathname, l10n);
	}
	PHYSFS_freeList(localization_files);
}

static int k2_l10n_get_index(const char *key) {
	if (! last_used) {
		LOG_ERROR("No active localization!");
		return -1;
	}
	uint32_t keyval = k2_hash_string(key);
	for (size_t i = 0; i < L10N_MAX_ENTRIES; ++i) {
		if (last_used->keys[i] == keyval) return (int)i;
	}
	return -1;
}

bool k2_l10n_get_success(const char *key, const char **pval) {
	int index = k2_l10n_get_index(key);
	if (index == -1) return false;
	*pval = last_used->values[index];
	return true;
}

const char * k2_l10n_get(const char *key) {
	int index = k2_l10n_get_index(key);
	if (index == -1) return key;
	return last_used->values[index];
}

int k2_l10n_printf(char *buf, size_t size, const char *key, ...) {
	va_list list;
	va_start(list, key);
	int result = vsnprintf(buf, size, k2_l10n_get(key), list);
	va_end(list);
	return result;
}

