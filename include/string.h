#ifndef STRING_H
#define STRING_H 1

#include <stdint.h>

#ifndef NULL
#define NULL ((void*)0)
#endif

void *memcpy(void *dest, const void *src, uint64_t n);
void *memset(void *s, int c, uint64_t n);

int strcmp(const char *a, const char *b);
char *strcpy(char *dest, const char *src);
uint64_t strlen(const char *s);

#endif
