#ifndef BLOCK_H
#define BLOCK_H 1

#include <stdint.h>

#define DISK_SIZE (1024 * 1024) // 1MB
#define BLOCK_SIZE 512

static uint8_t disk[DISK_SIZE];

int block_read(uint32_t block, void *buffer);
int block_write(uint32_t block, const void *buffer);

#endif
