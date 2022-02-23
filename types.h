#ifndef _SPITTER_TYPES_H_
#define _SPITTER_TYPES_H_

#if !defined(NULL) || !defined(_STDIO_H)
#define NULL                ((void *) 0)
#endif

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS        0
#define EXIT_FAILURE        1
#endif

#define ASM_NAKED           __attribute__ ((__naked__))

#if !defined(_STDINT_H) && !defined(_STDLIB_H)
typedef signed char         int8_t;
typedef unsigned char       uint8_t;

typedef signed short        int16_t;
typedef unsigned short      uint16_t;

typedef signed int          int32_t;
typedef unsigned int        uint32_t;

typedef signed long long    int64_t;
typedef unsigned long long  uint64_t;

typedef uint64_t            uintptr_t;
#endif

#if !defined(_STDIO_H) || !defined(_STDINT_H)
typedef unsigned long       size_t;
#endif

typedef unsigned char       byte;
typedef _Bool               bool;

enum {
    false = 0,
    true = 1
};

#endif