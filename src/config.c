// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Chua Hou

#include <stdlib.h>

#include "config.h"

char *config_tele_api_key()
{
	return getenv("WRTELE_TELE_API_KEY");
}

char *config_tele_target_chat_id()
{
	return getenv("WRTELE_TELE_TARGET_CHAT_ID");
}
