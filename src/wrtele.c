// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Chua Hou

#define _GNU_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "botapi.h"
#include "config.h"
#include "mac.h"

// Parses the string of commands in commands_str and separates them, writing the
// number of commands into len and returning an array of pointers. The pointers
// each point to starting characters in commands_str.
char **parse_commands(char *commands_str, size_t *len);

int main(int argc, char **argv)
{
	// Get list of devices to watch.
	size_t devs_len;
	struct device *devs = config_mac_addrs(&devs_len);
	if (!devs || devs_len < 1) {
		fputs("Invalid MAC addresses to watch", stderr);
		return -1;
	}
	puts("Watching devices:");
	for (size_t i = 0; i < devs_len; i++) {
		struct device mac = devs[i];
		printf("%s %s\n", mac.mac, mac.name);
	}

	// Get list of commands.
	char *config_commands_str = config_list_command();
	size_t commands_str_len = strlen(config_commands_str);
	char *commands_str = malloc(commands_str_len + 1);
	memcpy(commands_str, config_commands_str, commands_str_len);
	commands_str[commands_str_len] = '\0'; // Make mutable copy.
	size_t commands_len;
	char **commands = parse_commands(commands_str, &commands_len);
	if (!commands || commands_len < 1) {
		fputs("Failed to parse commands", stderr);
		return -1;
	}
	puts("Using commands:");
	for (size_t i = 0; i < commands_len; i++)
		puts(commands[i]);

	// Infinite loop to watch.
	unsigned int sleep_duration = config_sleep_duration();
	while (true) {
		size_t changed_len;
		char *macs = list_macs(commands, commands_len);
		struct device *changed = check_status(devs, devs_len, macs, &changed_len);
		free(macs);

		for (size_t i = 0; i < changed_len; i++) {
			char *msg;
			if (changed[i].connected) {
				if (asprintf(&msg, "Device %s connected.", changed[i].name) < 0) {
					fputs("Failed to create message", stderr);
					return -1;
				}
			} else {
				if (asprintf(&msg, "Device %s disconnected.", changed[i].name) < 0) {
					fputs("Failed to create message", stderr);
					return -1;
				}
			}
			tele_send_message(config_tele_api_key(),
					config_tele_target_chat_id(), msg);
			puts(msg); free(msg);
		}
		free(changed);

		sleep(sleep_duration);
	}

	// Only reachable on errors.
	free(devs); free(commands); free(commands_str); return -1;
}

char **parse_commands(char *commands_str, size_t *len)
{
	const char *SEPS = ";"; // Must be of length 1.
	*len = 1;
	for (char *p = commands_str; *p != '\0'; p++)
		if (*p == SEPS[0]) ++*len;
	char **commands = malloc(sizeof(char *) * *len);
	if (!commands) { *len = 0; return NULL; }

	// commands's elements point to appropriate start points within the
	// commands_str string. strtok() replaces separators with '\0'.
	commands[0] = strtok(commands_str, SEPS);
	for (size_t i = 1; i < *len; i++) commands[i] = strtok(NULL, SEPS);

	return commands;
}
