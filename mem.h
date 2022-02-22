#ifndef _SPITTER_MEM_H_
#define _SPITTER_MEM_H_

#include "types.h"

void *memcpy(void *dest, const void *src, size_t nbytes);
void memset(void *dest, byte cb, size_t nbytes);
int mem_set_rwx(void *mem, size_t len);

int ASM_NAKED exit(int exitcode);
void ASM_NAKED print(int fd, const char *buf, size_t slen);

#endif