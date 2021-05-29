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
	char *addrs = malloc(strlen(env) + 1);
	memcpy(addrs, env, strlen(env) + 1);

	// Iterate through tokens.
	*len = 0;
	struct device *devices = NULL;
	char *mac = strtok(addrs, " ,;");
	while (mac != NULL) {
		struct device *new_devices = realloc(devices,
				sizeof(struct device) * ++*len);
		if (!new_devices) { free(devices); len = 0; return NULL; }
		devices = new_devices;
		strncpy(devices[*len - 1].mac, mac, 17);
		for (char *p = devices[*len - 1].mac; *p != '\0'; p++)
			*p = tolower(*p);
		devices[*len - 1].connected = false;
		mac = strtok(NULL, " ,;");
	}
	free(addrs);

	return devices;
}

char *config_list_command()
{
	return getenv("WRTELE_LIST_COMMAND");
}
