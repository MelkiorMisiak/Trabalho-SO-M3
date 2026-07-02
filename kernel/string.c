#include "string.h"
#include <stdint.h>

void *memset(void *s, int c, uint64_t n) 
{
	uint8_t *p = s;
	while (n--)
		*p++ = c;
	return s;
}

void *memcpy(void *dest, const void *src, uint64_t n) {
    uint8_t *d = (uint8_t *)dest;
    const char *s = (const char *)src;

    for (uint64_t i = 0; i < n; i++) {
        d[i] = s[i];
    }

    return dest;
}


uint64_t strlen(const char *s)
{
	uint64_t len = 0;
	while(*s != '\0') {
		len++;
		s++;
	}
	return len;
}

int strcmp(const char *a, const char *b)
{
	uint64_t a_size = strlen(a);
	uint64_t b_size = strlen(b);

	if(a_size != b_size)
		return 1;

	for(uint64_t i = 0; i < a_size; i++)
	{
		if(a[i] != b[i])
			return 1;
	}
	return 0;
}

char *strcpy(char *dest, const char *src)
{
	for (uint32_t i = 0; i <= strlen(src); i++)
		dest[i] = src[i];

	return dest;
}


