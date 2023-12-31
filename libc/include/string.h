#ifndef SPECTRAOS_STRING_H_
#define SPECTRAOS_STRING_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
char* strrev(char* str, int len);

#ifdef __cplusplus
}
#endif

#endif