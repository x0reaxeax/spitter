#include "mem.h"
#include "cpu.h"

void *memcpy(void *dest, const void *src, size_t nbytes) {
    for (size_t i = 0; i < nbytes; i++) {
        *(byte *) (dest + i) = *(byte *) (src + i);
    }
    
    return dest;
}

void memset(void *dest, byte cb, size_t nbytes) {
    for (size_t i = 0; i < nbytes; i++) {
        *(byte *) (dest + i) = cb;
    }
}

bool check_ill(void *mem) {
    if (((byte*) mem)[0] == 0x0f && ((byte *) mem)[1] == 0x0b) {
        return true;
    }

    return false;
}

void *find_ill(void *mem, size_t maxsz) {
    for (size_t i = 0; i < maxsz; i++) {
        if (*(byte *) (mem + i) == I_NOP) {
            if (check_ill(mem + i + 1)) {
                return (mem + i);
            }
        }
    }
    
    return NULL;
}

int mem_set_rwx(void *mem, size_t len) {
    int ret = EXIT_SUCCESS;
    size_t offsz = ((uintptr_t) mem % 4096);
    uintptr_t addr = ((uintptr_t) mem) - offsz;

    __asm__ volatile (
        ".intel_syntax noprefix;"
        "push   10;"
        "pop    rax;"
        "mov    rdi, %[addr];"
        "mov    rsi, %[len];"
        "push   7;"
        "pop    rdx;"
        "syscall;"
        "mov %[out], eax;"
        ".att_syntax;"
        : [out] "=r" (ret)
        : [addr] "r" (addr), [len] "r" (offsz + len)
        : "rax", "rdi", "rsi", "rdx"
    );

    return ret;
}

int ASM_NAKED exit(int exitcode) {
    __asm__ volatile (
        ".intel_syntax noprefix;"
        "mov    eax, 60;"
        "syscall;"
        ".att_syntax;"
    );
}

void ASM_NAKED print(int fd, const char *buf, size_t slen) {
    __asm__ volatile (
        ".intel_syntax noprefix;"
        "push 1;"
        "pop rax;"
        "syscall;"
        "ret;"
        ".att_syntax;"
    );
}