#include "fs.h"
#include "string.h"
#include "uart.h"
#include <stdint.h>

uint16_t fat[NUM_CLUSTERS];
struct superblock_t superblock;
struct dir_entry_t directory[MAX_FILES];

int fs_init(void)
{
	superblock.magic = SIMPLEFAT_MAGIC;
	superblock.cluster_size = CLUSTER_SIZE;
	superblock.total_clusters = TOTAL_CLUSTERS;
	superblock.total_blocks = TOTAL_BLOCKS; 

	for(uint32_t i = 0; i < NUM_CLUSTERS; i++) {
		fat[i] = FAT_FREE;
	}

	for(uint32_t i = 0; i < MAX_FILES; i++) {
		directory[i].first_cluster = 0x0000;
		directory[i].name[0] = '\0';
		directory[i].size = 0;
	}
    directory_entries = 0;

	return 0;
}

int cluster_alloc(void)
{
	for(uint32_t i = 0; i < NUM_CLUSTERS; i++) {
		if(fat[i] == FAT_FREE)
			return i;
	}
	return -1;
}

uint32_t clusters_used(uint16_t cluster)
{
	uint32_t used = 0;
	if(fat[cluster] == FAT_FREE || fat[cluster] == FAT_EOF)
		return 0;
	
    uint16_t current = fat[cluster];
	while(current != FAT_EOF) {
		used++;
		current = fat[current];
	}
	return used;
}

int fs_create(const char *name)
{
	if (directory_entries >= MAX_FILES)
		return -1;

	for(uint32_t i = 0; i < MAX_FILES; i++) {
		if(directory[i].name[0] != '\0' && !strcmp(name, directory[i].name))
			return -1; 
	}

	int cluster = cluster_alloc();
	if(cluster == -1)
		return -1; 

	for(uint32_t i = 0; i < MAX_FILES; i++) {
		if(directory[i].name[0] == '\0') {
			    strcpy(directory[i].name, name);
			    directory[i].name[MAX_NAME_SIZE - 1] = '\0';
			    directory[i].first_cluster = cluster;
			    directory[i].size = 0;
			    
			    fat[cluster] = FAT_EOF;
			    directory_entries++;
			    return 0;
		}
	}
	return -1;
}

int fs_open(const char *name)
{
	for(uint32_t i = 0; i < MAX_FILES; i++) {
		if(directory[i].name[0] != '\0' && !strcmp(name, directory[i].name)) {
			return i; // Return file descriptor (index)
		}
	}
	return -1;
}

int fs_write(int fd, const void *buffer, uint32_t size)
{
    	if(fd < 0 || fd >= MAX_FILES || directory[fd].name[0] == '\0') 
        	return -1;

    	const uint8_t *data = (const uint8_t *)buffer;
    	uint32_t bytes_written = 0;
    	uint16_t current_cluster = directory[fd].first_cluster;

    	while (bytes_written < size) {
        	uint32_t chunk = size - bytes_written;
        	if (chunk > CLUSTER_SIZE) 
            		chunk = CLUSTER_SIZE;

        	uint8_t block_buf[CLUSTER_SIZE] = {0};
        	memcpy(block_buf, data + bytes_written, chunk);
        
        	block_write(current_cluster, block_buf);
        	bytes_written += chunk;

        	if (bytes_written < size) {
            		if (fat[current_cluster] == FAT_EOF) {
                	int next = cluster_alloc();
                	if (next == -1) break; // Disk full
                
                	fat[current_cluster] = next;
                	fat[next] = FAT_EOF;
            		}
            	current_cluster = fat[current_cluster];
        	}
    	}

    	if (bytes_written > directory[fd].size) {
        	directory[fd].size = bytes_written;
    	}

    	return bytes_written;
}

int fs_read(int fd, void *buffer, uint32_t size)
{
    	if(fd < 0 || fd >= MAX_FILES || directory[fd].name[0] == '\0') 
        	return -1;

    	uint8_t *dest = (uint8_t *)buffer;
    	uint32_t bytes_read = 0;
    	uint16_t current_cluster = directory[fd].first_cluster;

    	if (size > directory[fd].size) {
        	size = directory[fd].size;
    	}

    	while (bytes_read < size && current_cluster != FAT_EOF) {
        	uint32_t chunk = size - bytes_read;
        	if (chunk > CLUSTER_SIZE) 
            		chunk = CLUSTER_SIZE;

        	uint8_t block_buf[CLUSTER_SIZE];
        	block_read(current_cluster, block_buf);

        	memcpy(dest + bytes_read, block_buf, chunk);
        	bytes_read += chunk;

        	current_cluster = fat[current_cluster];
    	}
    	return bytes_read;
}

int fs_close(int fd)
{
	return 0;
}

int fs_delete(const char *name)
{
    	int fd = fs_open(name);
    	if(fd == -1) return -1;

    	uint16_t current = directory[fd].first_cluster;
    	while(current != FAT_EOF) {
        	uint16_t next = fat[current];
        	fat[current] = FAT_FREE;
        	current = next;
    	}

    	directory[fd].name[0] = '\0';
    	directory[fd].first_cluster = 0;
    	directory[fd].size = 0;
    
    	if(directory_entries > 0) {
        	directory_entries--;
    	}

	return 0;
}
