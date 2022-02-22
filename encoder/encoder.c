#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define XOR_KEY 0x539

int main(int argc, const char *argv[]) {
    
    if (argc < 2) {
        fprintf(stderr, "usage: %s { \"SHELLCODE\" }\n", argv[0]);
        return 1;
    }

    size_t slen = strlen(argv[1]);

    /* identifier magic */
    unsigned char identifier[] = { 0x90, 0x0f, 0x0b };   

    printf("unsigned char exec[] = { ");
    for (size_t i = 0; i < (slen - 1); i+=2) {
        unsigned char hexbyte = 0;
        unsigned char ascii_byte[2] = { 0 };
        memcpy(ascii_byte, &argv[1][i], 2);

        hexbyte = strtol(ascii_byte, NULL, 16);

        printf("0x%02x, ", (unsigned char) (hexbyte ^ XOR_KEY));
    }

    for (size_t i = 0; i < sizeof(identifier); i++) {
        char *fmt = (i == (sizeof(identifier) - 1)) ? " };\n" : ", ";
        printf("0x%02x%s", (unsigned char) (identifier[i] ^ XOR_KEY), fmt);
    }
    
    return 0;
}
