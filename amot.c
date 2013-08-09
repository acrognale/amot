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

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#include <curl/curl.h>

#include <libavformat/avformat.h>
#include <libavutil/dict.h>

#include "amot.h"
#include "posters.h"
#include "net.h"

void md_find_directories()
{
	DIR *parent_dir;
	DIR *sub_dir;
	struct dirent *ep;
	parent_dir = opendir("./");
	if (parent_dir != NULL) {
		while ((ep = readdir(parent_dir))) {
			if ((sub_dir = opendir(ep->d_name)) != NULL) {
				md_scan_media(sub_dir,ep);
				closedir(sub_dir);
			}
		}
		(void) closedir (parent_dir);
	}
	else
		perror("Couldn't open the directory");
}

const char *get_file_ext (const char *filename) 
{
	const char *dot = strrchr(filename,'.');
	if (!dot || dot == filename) 
		return "";
	return dot + 1;
}

void md_scan_media(DIR *target_dir, struct dirent *ep)
{
	while ((ep = readdir(target_dir))) {
		if (strcmp(get_file_ext(ep->d_name),SUPPORTED_FORMATS[0]) == 0) {
			md_check_file(ep->d_name);
		}
	}
}

int md_check_file(char *filename)
{
	AVFormatContext *fmt_ctx = NULL;
	AVDictionaryEntry *tag = NULL;
	int ret;
	
	av_register_all();
	if ((ret = avformat_open_input(&fmt_ctx, filename, NULL, NULL)))
		return ret;

	while ((tag = av_dict_get(fmt_ctx->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))) {
		printf("%s=%s\n", tag->key, tag->value);
		if (strcmp(tag->key,"title") == 0) {
			char *title = tag->value;
			md_clean_title(title);			
		}
	}
	return 0;
}

void md_clean_title(char *title)
{
	char JUNK[] = ".=[]-";
	char *WORDS[] = { "720p","x264","DVDRip","AC3","BDRip",
		"HANDJOB","DON","TBB","SiNNERS","LiNG","EbP","BRRIP", NULL};
	for (int i = 0; i < sizeof(JUNK); i++) {
		for (int e = 0; e < strlen(title); e++) {
			if (title[e] == JUNK[i])
				memmove(title+e, title+e+1, strlen(title)+e);
		}
	}
	puts(title);
	char *dst = title;
	while (*dst) {
		char **word = WORDS; 
		for (; *word; word++) {
			if (!strncmp(title, *word, strlen(*word))) {
				title += strlen(*word);
				break;
			}	
		}		
		if (!*word)
			*dst++ = *title++;
	}
	puts(dst);
	*dst = 0;
}

int main() 
{
	md_find_directories();
	md_get_movie_id("blah");
	return 0;
}