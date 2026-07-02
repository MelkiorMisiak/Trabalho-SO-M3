#ifndef FS_H
#define FS_H 1

#include <stdint.h>

#define SIMPLEFAT_MAGIC 0x53464154

#define FAT_FREE 0x0000
#define FAT_EOF 0xFFFF

struct superblock_t {
	uint32_t magic;

	uint32_t total_blocks;

	uint32_t total_clusters;

	uint32_t cluster_size;
};

struct dir_entry_t {
	char name[32];

	uint32_t size;

	uint16_t first_cluster;
};

int fs_init(void);
int cluster_alloc(void);

int fs_create(const char *name);
int fs_open(const char *name);
int fs_write(int ft, const void *buffer, uint32_t size);
int fs_read(int fd, void *buffer, uint32_t size);
int fs_close(int fd);
int fs_delete(const char *name);

#endif
