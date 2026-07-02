#ifndef FS_H
#define FS_H 1

#include <stdint.h>

int fs_init(void);
int cluster_alloc(void);

int fs_create(const char *name);
int fs_open(const char *name);
int fs_write(int ft, const void *buffer, uint32_t size);
int fs_read(int fd, void *buffer, uint32_t size);
int fs_close(int fd);
int fs_delete(const char *name);

#endif
