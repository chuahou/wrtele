// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Chua Hou

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
		perror("Invalid MAC addresses to watch");
		return -1;
	}

	// Infinite loop to watch.
	unsigned int sleep_duration = config_sleep_duration();
	while (true) {
		size_t changed_len;
		struct device *changed = check_status(macs, macs_len, &changed_len);

		for (size_t i = 0; i < changed_len; i++) {
			if (changed[i].connected) {
				const int MSG_LEN = 36;
				char msg[MSG_LEN];
				snprintf(msg, MSG_LEN, "Device %s connected.", changed[i].mac);
				tele_send_message(msg); puts(msg);
			} else {
				const int MSG_LEN = 39;
				char msg[MSG_LEN];
				snprintf(msg, MSG_LEN, "Device %s disconnected.", changed[i].mac);
				tele_send_message(msg); puts(msg);
			}
		}

		sleep(sleep_duration);
	}
}
