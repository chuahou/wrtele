// SPDX-License-Identifier: MIT
// Copyright (c) 2021 Chua Hou

#include <stdbool.h>
#include <stdio.h>

#include "botapi.h"
#include "config.h"

int main(int argc, char **argv)
{
	puts("wrtele");
	tele_send_message(argc > 1 ? argv[1] : "wrtele");

	return 0;
}
