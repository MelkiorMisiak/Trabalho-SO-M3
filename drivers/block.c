#include "block.h"

int block_read(uint32_t block, void *buffer)
{
	uint8_t *value = buffer;
	*value = disk[block];
}

int block_write(uint32_t block, const void *buffer)
{
	const uint8_t *value = buffer;
	disk[block] = *value;
}

