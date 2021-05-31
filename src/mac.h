// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Chua Hou
//
// Functions to get information about MAC addresses.

#ifndef __WRTELE_MAC_H_INCLUDED__
#define __WRTELE_MAC_H_INCLUDED__

#include <stdbool.h>
#include <stddef.h>

#define MAX_DEVICE_NAME_LEN 46 // 64 - 18

// Status of a MAC address and its last known status.
struct device {
	char mac[18];
	char name[MAX_DEVICE_NAME_LEN];
	bool connected;
};

// Updates the connection status of devices devs from the given list of MACs
// macs, and returns a list of changed devices. The list must be free()-ed. The
// length of the list of changed devices is written to changed_len, and the
// specified commands_len commands are run. The string macs is destructively
// modified.
struct device *check_status(struct device *devs, size_t devs_len,
		char *macs, size_t *changed_len);

// Returns a string of the output of given commands, which must be free()-ed.
// commands_len is the length of the commands array.
char *list_macs(char **commands, size_t commands_len);

#endif
