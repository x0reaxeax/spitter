#ifndef _SPITTER_CPU_H_
#define _SPITTER_CPU_H_

#define I_NOP       0x90
#define I_TRAP      0xcc
#define I_RET       0xc3

#define I_POP_RBP   0x5d

#define ASM_BYTES(byte, quant)          \
    do { __asm__ volatile (             \
        ".rept %c0; .byte %c1; .endr;"  \
        :: "i" (quant), "i" (byte)      \
    ); } while(0);

#define ASM_BYTE(byte)                  \
    ASM_BYTES(byte, 1)

#define ASM_NOP(quant)                  \
    ASM_BYTES(I_NOP, quant)


#define ASM_TRAP                        \
    do { __asm__ volatile ("int3"); } while (0);


bool check_ill(void *mem);
void *find_ill(void *mem, size_t maxsz);

#endif