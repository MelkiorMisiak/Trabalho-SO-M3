#include "block.h"
#include "string.h"

int block_read(uint32_t block, void *buffer)
{
    if ((block * BLOCK_SIZE) >= DISK_SIZE) return -1;
    
    memcpy(buffer, &disk[block * BLOCK_SIZE], BLOCK_SIZE);
    return 0;
}

int block_write(uint32_t block, const void *buffer)
{
    if ((block * BLOCK_SIZE) >= DISK_SIZE) return -1;
    
    memcpy(&disk[block * BLOCK_SIZE], buffer, BLOCK_SIZE);
    return 0;
}
