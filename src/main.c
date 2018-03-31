#define _BSD_SOURCE

#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <time.h>

int
show_file_info(const char *file_name)
{
	struct stat file_info;

	if (stat(file_name, &file_info) == -1)
	{
		fprintf(stderr, "Error(%d): %s\n", errno, strerror(errno));
		return -1;
	}

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

	return 0;
}

int
main(int argc, char const *argv[])
{
	show_file_info(argv[1]);
	
	return 0;
}
