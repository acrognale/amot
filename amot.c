#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#include "amot.h"

void md_find_directories()
{
	DIR *parent_dir;
	DIR *sub_dir;
	struct dirent *ep;
	parent_dir = opendir("./");
	if (parent_dir != NULL)
	{
		while ((ep = readdir(parent_dir)))
		{
			if ((sub_dir = opendir(ep->d_name)) != NULL)
			{
				puts(ep->d_name);
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
	while ((ep = readdir(target_dir)))
	{
		if (strcmp(get_file_ext(ep->d_name),SUPPORTED_FORMATS[0]))
		{
			md_check_file(ep->d_name);
		}
	}
}

void md_check_file(struct dirent *ep)
{

}

int main() 
{
	md_find_directories();
	return 0;
}