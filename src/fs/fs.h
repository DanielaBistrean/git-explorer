#ifndef GEXP_FS_FS_H
#define GEXP_FS_FS_H

#include <sys/stat.h>

struct file_node
{
	struct stat f_info;
	struct file_node *next;
	char filename[];
};

struct dir_info
{
	struct file_node *first;
	unsigned int num_nodes;
	char pathname[];
};

extern int get_dir_info(const char *pathname, struct dir_info *info);

#endif