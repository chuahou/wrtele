// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Chua Hou

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mac.h"

struct device *check_status(struct device *devs, size_t devs_len,
		char *macs, size_t *changed_len)
{
	*changed_len = 0;
	if (!macs) return NULL;

	// Make everything lowercase.
	for (char *p = macs; *p != '\0'; p++) *p = tolower(*p);

	// Array of changed devices.
	struct device *changed = malloc(sizeof(struct device) * devs_len);
	if (!changed) return NULL;

	// Iterate through devices.
	for (size_t i = 0; i < devs_len; i++) {
		if (strstr(macs, devs[i].mac) != NULL) {
			if (!devs[i].connected) {
				devs[i].connected = true;
				changed[(*changed_len)++] = devs[i];
			}
		} else if (devs[i].connected) {
			devs[i].connected = false;
			changed[(*changed_len)++] = devs[i];
		}
	}
	return changed;
}

char *list_macs(char **commands, size_t commands_len)
{
	// Iterate over commands.
	char *output = NULL; size_t output_len = 0;
	for (size_t i = 0; i < commands_len; i++) {
		char *command = commands[i];
		FILE *p = popen(command, "r");
		if (!p) return NULL;

		// Copy output into output variable.
		const size_t BUF_SIZE = 128;
		char buf[BUF_SIZE];
		while (fgets(buf, BUF_SIZE, p)) {
			size_t read_len = strlen(buf);
			char *new_output = realloc(output, output_len + read_len + 1);
			if (!new_output) {
				free(output); pclose(p); return NULL;
			}
			output = new_output;

			memcpy(&output[output_len], buf, read_len + 1); // +1 for '\0'
			output_len += read_len;
		}

		pclose(p);
	}

	return output;
}
