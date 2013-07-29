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

#include <curl/curl.h>
#include <jsmn.h>

#include "net.h"

#define POSTER_API_PATTERN "http://api.themoviedb.org/3/%s/images" // {id}
#define API_KEY "key"


// TODO: (1) implement a version that doesn't need `int pos` and fork jsmn
// 		 (2) also need to implement a search for values and keys
char get_json_key(jsmntok_t *tokens, const char *json_request, int pos) 
{
	jsmntok_t key = tokens[pos];
	unsigned int length = key.end - key.start;
	char key_string[length + 1];
	memcpy(key_string, &json_request[key.start], length);
	key_string[length] = '\0';
	printf("Key: %s\n", key_string);

	return key_string;
}

char get_json_value(jsmntok_t *tokens, const char *json_request, int pos)
{	
	jsmntok_t key = tokens[pos];
	unsigned int length = key.size;
	char value_string[length + 1];
	memcpy(value_string, &json_request[key.start], length);
	value_string[length] = '\0';
	printf("Value: %s\n", value_string);

	return value_string;
}

void md_get_poster(int id) 
{

}

void md_get_movie_id(char *title)
{
	int r;
	jsmn_parser p;
	jsmntok_t tok[10];
	
	const char *json_request;
	sprintf(json_request, "\"api_key\" : %s", API_KEY);

	jsmn_init(&p);
	r = jsmn_parse(&p, json_request, tok, 10);

	get_json_key(tok, json_request, 0);
	get_json_value(tok, json_request, 0);
}