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

		// Create the URL.
		char *url;
		if (asprintf(&url, "https://api.telegram.org/bot%s/sendMessage",
				config_tele_api_key()) < 0) {
			perror("Failed to create request URL");
			curl_easy_cleanup(curl);
			return false;
		}

		// Encode message to catch special characters.
		char *encoded_msg = curl_easy_escape(curl, msg, 0);

		// Put fields in POST fields.
		char *postfields;
		if (asprintf(&postfields, "chat_id=%s&text=%s",
				config_tele_target_chat_id(), encoded_msg) < 0) {
			perror("Failed to create post fields");
			curl_easy_cleanup(curl);
			return false;
		}
		curl_free(encoded_msg);

		// Perform CURL request.
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfields);
		CURLcode res = curl_easy_perform(curl);
		curl_easy_cleanup(curl); free(url); free(postfields);
		if (res == CURLE_OK) {
			return true;
		} else {
			perror("CURL request error");
			return false;
		}
	}
	perror("Failed to create CURL object");
	return false;
}
