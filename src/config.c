// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Chua Hou

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "mac.h"

char *config_tele_api_key()
{
	return getenv("WRTELE_TELE_API_KEY");
}

char *config_tele_target_chat_id()
{
	return getenv("WRTELE_TELE_TARGET_CHAT_ID");
}

struct device *config_mac_addrs(size_t *len)
{
	// Make copy so we can strtok.
	char *env = getenv("WRTELE_MAC_ADDRS");
	if (!env) return NULL;
	char *addrs = malloc(strlen(env) + 1);
	memcpy(addrs, env, strlen(env) + 1);

	// Iterate through tokens.
	*len = 0;
	struct device *devices = NULL;
	char *strtok_st;
	char *entry = strtok_r(addrs, ",;", &strtok_st);
	while (entry != NULL) {
		// Separate entry into MAC and device name. [mac]=[name]
		char *inner_strtok_st;
		char *mac = strtok_r(entry, "=", &inner_strtok_st);
		char *name = strtok_r(NULL, "=", &inner_strtok_st);
		if (!name) name = mac; // Use MAC as name if not provided.

		// Add new device.
		struct device *new_devices = realloc(devices,
				sizeof(struct device) * ++*len);
		if (!new_devices) { free(devices); len = 0; return NULL; }
		devices = new_devices;
		strncpy(devices[*len - 1].mac, mac, 17);
		strncpy(devices[*len - 1].name, name, MAX_DEVICE_NAME_LEN - 1);
		for (char *p = devices[*len - 1].mac; *p != '\0'; p++)
			*p = tolower(*p);
		devices[*len - 1].connected = false;

		// Advance to next token.
		entry = strtok_r(NULL, ",;", &strtok_st);
	}
	free(addrs);

	return devices;
}

char *config_list_command()
{
	return getenv("WRTELE_LIST_COMMAND");
}

unsigned int config_sleep_duration()
{
	char *env = getenv("WRTELE_SLEEP_DURATION");
	if (env) {
		long parse = strtol(env, NULL, 0);
		return parse <= 0L ? 1 : (unsigned int) parse;
	}
	else return 1;
}
