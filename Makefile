CC  = gcc
OUT = loader
HDR = cpu.h mem.h types.h
OBJ = op64.o
FLG = -nostdlib	\
        -fno-stack-protector \
        -ffreestanding
SRC = loader.c
LOUT= libl0ader.a
LOBJ= l0ader.o

all: loader

.PHONY: library

library: SLIB+=-D LOADER_LIB -fPIC -shared

library: $(OBJ)
	$(CC) $(SLIB) $(FLG) -c $(SRC) -o l0ader.o
	ar sr $(LOUT) $(OBJ) $(LOBJ)

loader: $(OBJ)
	$(CC) $(FLG) $(SRC) -o $@ $^

%.o: %.c $(HDR)
	$(CC) $(SLIB) $(FLG) -c -o $@ $<

.PHONY: clean

clean:
	rm -f $(OBJ) $(LOBJ) $(OUT) $(LOUT)
