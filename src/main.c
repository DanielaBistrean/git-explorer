#define _BSD_SOURCE

#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/types.h>
#include <time.h>

#include "fs/fs.h"

int
show_file_info(char *filename, struct stat file_info)
{
	printf("Filename: %s\n", filename);
	printf("Minor=%d\tMajor=%d\n", minor(file_info.st_dev), major(file_info.st_dev));
	printf("I-node: %ld\n", file_info.st_ino);

	switch (file_info.st_mode & S_IFMT)
	{
		case S_IFREG:
			printf("Type: regular\n");
			break;
		case S_IFDIR:
			printf("Type: directory\n");
			break;
		case S_IFCHR:
			printf("Type: character\n");
			break;
		case S_IFBLK:
			printf("Type: block\n");
			break;
		case S_IFIFO:
			printf("Type: FIFO or pipe\n");
			break;
		case S_IFSOCK:
			printf("Type: socket\n");
			break;
		case S_IFLNK:
			printf("Type: link\n");
			break;
	}

	printf("Permissions: 0%o\n", file_info.st_mode & 0x1ff);
	printf("Links to file: %ld\n", file_info.st_nlink);
	printf("Uid=%d gid=%d\n", file_info.st_uid, file_info.st_gid);

	if (S_ISCHR(file_info.st_mode) || S_ISBLK(file_info.st_mode))
		printf("rMinor=%d\trMajor=%d\n", minor(file_info.st_rdev), major(file_info.st_rdev));

	printf("Size=%ld bytes\n", file_info.st_size);
	printf("Block size:%ld\n", file_info.st_blksize);
	printf("Blocks:%ld\n", file_info.st_blocks);
	printf("Last access time:%s", ctime(&file_info.st_atime));
	printf("Last modification time:%s", ctime(&file_info.st_mtime));
	printf("Last status change:%s", ctime(&file_info.st_ctime));
	printf("\n");

	return 0;
}

void
show_dir_info(struct dir_info d_info)
{
	printf("Dir %s contains %d files:\n", d_info.pathname, d_info.num_nodes);
	struct file_node *current = d_info.first;

	while (current != NULL)
	{
		show_file_info(current->filename, current->f_info);
		current = current->next;
	}
}

int
main(int argc, char const *argv[])
{
	struct dir_info d_info;
	if (get_dir_info(argv[1], &d_info) == -1)
		fprintf(stderr, "Error could not read dir\n");

	show_dir_info(d_info);
	
	return 0;
}
