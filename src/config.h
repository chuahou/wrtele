// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Chua Hou
//
// Functions to access configuration.

#ifndef __WRTELE_CONFIG_H_INCLUDED__
#define __WRTELE_CONFIG_H_INCLUDED__

#include "mac.h"

// Get Telegram API key. Simple wrapper around getenv.
char *config_tele_api_key();

// Get Telegram target chat ID. Simple wrapper around getenv.
char *config_tele_target_chat_id();

// MAC addresses to watch, separated by any of " ,;", in all lowercase. Length
// of array returned in len.
struct device *config_mac_addrs(size_t *len);

// Command(s) to execute to list MAC addresses, separated by ';'.
char *config_list_command();

#endif
