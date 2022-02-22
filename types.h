#ifndef _SPITTER_TYPES_H_
#define _SPITTER_TYPES_H_

#define NULL                ((void *) 0)
#define EXIT_SUCCESS        0
#define EXIT_FAILURE        1

#define ASM_NAKED           __attribute__ ((__naked__))

typedef signed char         int8_t;
typedef unsigned char       uint8_t;

typedef signed short        int16_t;
typedef unsigned short      uint16_t;

typedef signed int          int32_t;
typedef unsigned int        uint32_t;

typedef signed long long    int64_t;
typedef unsigned long long  uint64_t;

typedef uint8_t             byte;
typedef uint64_t            size_t;
typedef uint64_t            uintptr_t;

typedef _Bool               bool;

enum {
    false = 0,
    true = 1
};

#endif