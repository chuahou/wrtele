// SPDX-License-Identifier: ???
// Copyright (c) 2021 Chua Hou

#define _GNU_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <curl/curl.h>

#include "botapi.h"
#include "config.h"

bool tele_send_message(char *msg)
{
	CURL *curl;
	if ((curl = curl_easy_init())) {

		// Encode message to catch special characters.
		char *encoded_msg = curl_easy_escape(curl, msg, 0);

		// Create the URL.
		char *url;
		if (asprintf(&url,
				"https://api.telegram.org/bot%s/sendMessage?chat_id=%s&text=%s",
				TELE_API_KEY, TELE_TARGET_CHAT_ID, encoded_msg) < 0) return false;
		curl_free(encoded_msg);

		// Perform CURL request.
		curl_easy_setopt(curl, CURLOPT_URL, url);
		CURLcode res = curl_easy_perform(curl);
		curl_easy_cleanup(curl); free(url);
		return (res == CURLE_OK);
	}
	return false;
}
