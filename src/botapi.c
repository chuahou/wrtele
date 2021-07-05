// SPDX-License-Identifier: ???
// Copyright (c) 2021 Chua Hou

#define _GNU_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <curl/curl.h>

#include "botapi.h"

bool tele_send_message(char *key, char *chat_id, char *msg)
{
	bool ret = false;

	// Initialize CURL object.
	CURL *curl;
	if (!(curl = curl_easy_init())) {
		fputs("Failed to create CURL object", stderr);
		goto err_curl_easy_init;
	}

	// Create the URL.
	char *url;
	if (asprintf(&url,
				"https://api.telegram.org/bot%s/sendMessage", key) < 0) {
		fputs("Failed to create request URL", stderr);
		goto err_asprintf_url;
	}

	// Encode message to catch special characters.
	char *encoded_msg = curl_easy_escape(curl, msg, 0);
	if (!encoded_msg) {
		fputs("Failed to encode message", stderr);
		goto err_curl_easy_escape;
	}

	// Put fields in POST fields.
	char *postfields;
	if (asprintf(&postfields,
				"chat_id=%s&text=%s", chat_id, encoded_msg) < 0) {
		fputs("Failed to create post fields", stderr);
		goto err_asprintf_postfields;
	}

	// Perform CURL request.
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfields);
	CURLcode res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
		fputs("CURL request error", stderr);
		goto err_curlcode;
	} else ret = true;

err_curlcode:
	free(postfields);
err_asprintf_postfields:
	curl_free(encoded_msg);
err_curl_easy_escape:
	free(url);
err_asprintf_url:
	curl_easy_cleanup(curl);
err_curl_easy_init:
	return ret;
}
