// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Chua Hou

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "mac.h"

struct device *check_status(struct device *devs, size_t devs_len)
{
	char *macs = list_macs();
	if (!macs) return NULL;

	// Make everything lowercase.
	for (char *p = macs; *p != '\0'; p++) *p = tolower(*p);

	// Array of changed devices.
	struct device *changed = malloc(sizeof(struct device) * devs_len);
	size_t changed_len = 0;

	// Iterate through devices.
	for (size_t i = 0; i < devs_len; i++) {
		if (strstr(macs, devs[i].mac) != NULL && !devs[i].connected) {
			devs[i].connected = true;
			changed[changed_len++] = devs[i];
		} else if (devs[i].connected) {
			devs[i].connected = false;
			changed[changed_len++] = devs[i];
		}
	}
	free(macs);

	return changed;
}

char *list_macs()
{
	// Create mutable copy of commands config string since we use destructive
	// calls to strtok.
	char *commands;
	char *commands_env = config_list_command();
	if (!commands_env) return NULL;
	size_t len = strlen(commands_env);
	if ((commands = malloc(len + 1))) {
		memcpy(commands, commands_env, len + 1);

		// Iterate over commands.
		char *command = strtok(commands, ";");
		char *output = NULL; size_t output_len = 0;
		while (command != NULL) {
			FILE *p = popen(command, "r");
			if (!p) { free(commands); return NULL; }

			// Copy output into output variable.
			const size_t BUF_SIZE = 128;
			char buf[BUF_SIZE];
			while (fgets(buf, BUF_SIZE, p)) {
				size_t read_len = strlen(buf);
				char *new_output = realloc(output, output_len + read_len);
				if (!new_output) {
					free(output); free(commands); pclose(p); return NULL;
				}
				output = new_output;

				memcpy(&output[output_len], buf, read_len + 1); // +1 for '\0'
				output_len += read_len;
			}

			pclose(p);

			// Next command.
			command = strtok(NULL, ";");
		}
		free(commands);

		return output;

	} else {
		return NULL;
	}
}
