// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Chua Hou
//
// Bot API helper functions.

#ifndef __BOTAPI_H_INCLUDE__
#define __BOTAPI_H_INCLUDE__

#include <stdbool.h>

// Uses Telegram Bot API to send a message to the target user. Requires bot API
// key and target chat ID.
// Returns true on success.
bool tele_send_message(char *key, char *chat_id, char *msg);

#endif
