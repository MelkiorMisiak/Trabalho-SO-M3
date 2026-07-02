#ifndef FS_H
#define FS_H 1

#include "block.h"

#include <stdint.h>

#define FAT_FREE 0x0000
#define FAT_EOF 0xFFFF

#define SIMPLEFAT_MAGIC 0x53464154
#define CLUSTER_SIZE 512
#define TOTAL_CLUSTERS 1024
#define TOTAL_BLOCKS DISK_SIZE/BLOCK_SIZE

#define NUM_CLUSTERS DISK_SIZE/CLUSTER_SIZE

#define MAX_NAME_SIZE 32

struct superblock_t {
	uint32_t magic;

	uint32_t total_blocks;

	uint32_t total_clusters;

	uint32_t cluster_size;
};

struct dir_entry_t {
	char name[MAX_NAME_SIZE];

	uint32_t size;

	uint16_t first_cluster;
};


extern uint16_t fat[NUM_CLUSTERS];
extern struct superblock_t superblock;

#define MAX_FILES 8
extern struct dir_entry_t directory[MAX_FILES];
static uint32_t directory_entries = 0;

int fs_init(void);
int cluster_alloc(void);

uint32_t clusters_used(uint16_t cluster);

int fs_create(const char *name);
int fs_open(const char *name);
int fs_write(int ft, const void *buffer, uint32_t size);
int fs_read(int fd, void *buffer, uint32_t size);
int fs_close(int fd);
int fs_delete(const char *name);

#endif
