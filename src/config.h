// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Chua Hou
//
// Functions to access configuration.

#ifndef __WRTELE_CONFIG_H_INCLUDED__
#define __WRTELE_CONFIG_H_INCLUDED__

// Get Telegram API key. Simple wrapper around getenv.
char *config_tele_api_key();

// Get Telegram target chat ID. Simple wrapper around getenv.
char *config_tele_target_chat_id();

#endif
