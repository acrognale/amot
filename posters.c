/*
The MIT License (MIT)

Copyright (c) 2013 Anthony Crognale

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <jsmn.h>

#include "net.h"

#define POSTER_API_PATTERN "http://api.themoviedb.org/3/%s/images" // {id}
#define API_KEY "key"

char *json_token_tostr(char *json, jsmntok_t *tok)
{   
	json[tok->end] = '\0';
    return json + tok->start;
}

jsmntok_t *search_json(char *json, jsmntok_t *tok, char *query) 
{
	jsmntok_t **tokens = &tok;
	for (; *tokens; tokens++) {
		if (strcmp(json_token_tostr(json, *tokens), query))
			return *tokens;
	}

	return NULL;
}

void md_get_poster(int id) 
{

}

void md_get_movie_id(char *title)
{
	int r;
	jsmn_parser p;
	jsmntok_t tok[10];
	
	char json_request[256];
	snprintf(json_request, sizeof(json_request), "\"api_key\" : %s, \"test_key\" : test ", API_KEY);

	jsmn_init(&p);
	r = jsmn_parse(&p, json_request, tok, 10);

	jsmntok_t *search_result;
	search_result = search_json(json_request, tok, "key");
	char *result_string = json_token_tostr(json_request, search_result);
	printf("%s\n", result_string);
}