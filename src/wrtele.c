// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Chua Hou

#define _GNU_SOURCE
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "botapi.h"
#include "config.h"
#include "mac.h"

int main(int argc, char **argv)
{
	// Get list of devices to watch.
	size_t macs_len;
	struct device *macs = config_mac_addrs(&macs_len);
	if (!macs || macs_len < 1) {
		errno = EINVAL;
		perror("Invalid MAC addresses to watch");
		return -1;
	}
	puts("Watching devices:");
	for (size_t i = 0; i < macs_len; i++) {
		struct device mac = macs[i];
		printf("%s %s\n", mac.mac, mac.name);
	}

	// Infinite loop to watch.
	unsigned int sleep_duration = config_sleep_duration();
	while (true) {
		size_t changed_len;
		struct device *changed = check_status(macs, macs_len, &changed_len);

		for (size_t i = 0; i < changed_len; i++) {
			if (changed[i].connected) {
				char *msg;
				if (asprintf(&msg, "Device %s connected.", changed[i].name) < 0) {
					perror("Failed to create message");
					return -1;
				}
				tele_send_message(config_tele_api_key(),
						config_tele_target_chat_id(), msg);
				puts(msg); free(msg);
			} else {
				char *msg;
				if (asprintf(&msg, "Device %s disconnected.", changed[i].name) < 0) {
					perror("Failed to create message");
					return -1;
				}
				tele_send_message(config_tele_api_key(),
						config_tele_target_chat_id(), msg);
				puts(msg); free(msg);
			}
		}
		free(changed);

		sleep(sleep_duration);
	}
}
