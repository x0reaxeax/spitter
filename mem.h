#ifndef _SPITTER_MEM_H_
#define _SPITTER_MEM_H_

#include "types.h"

void *loader_memcpy(void *dest, const void *src, size_t nbytes);
void loader_memset(void *dest, byte cb, size_t nbytes);
int mem_set_rwx(void *mem, size_t len);

void ASM_NAKED loader_exit(int exitcode);
void ASM_NAKED loader_print(int fd, const char *buf, size_t slen);

int loader_exec(byte *input_feed, size_t size);

#endif