#include "fs.h"

#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int
get_dir_info(const char *pathname, struct dir_info *info)
{
	DIR *dir;
	struct dirent *d_info;
	unsigned int count = 0;
	struct file_node *first = NULL, *current = NULL;

	if ((dir = opendir(pathname)) == NULL)
		return -1;

	while ((d_info = readdir(dir)) != NULL)
	{
		char f_name[256];
		struct file_node *f_node = (struct file_node *) malloc(sizeof(struct file_node) + strlen(d_info->d_name));
		
		sprintf(f_name, "%s/%s", pathname, d_info->d_name);
		if (stat(f_name, &(f_node->f_info)) == -1)
		{
			free(f_node);
			continue;
		}
		
		strcpy(f_node->filename, d_info->d_name);

		if (current == NULL)
		{
			first = f_node;
		}
		else
		{
			current->next = f_node;
		}


		count++;
		current = f_node;
	}

	info->num_nodes = count;
	strcpy(info->pathname, pathname);
	info->first = first;

	return 0;
}
