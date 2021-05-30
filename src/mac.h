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

// Updates the connection status of devices devs, and returns a list of changed
// devices. The list must be free()-ed.
struct device *check_status(struct device *devs, size_t num_devs, size_t *changed_len);

// Returns a string of the output of config_list_command()'s commands, which
// must be free()-ed.
char *list_macs();

#endif
