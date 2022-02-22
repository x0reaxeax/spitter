CC 	= gcc
OUT	= loader
HDR = cpu.h mem.h types.h
OBJ = op64.o
FLG = -nostdlib	\
		-fno-stack-protector \
		-ffreestanding
SRC = loader.c

all: loader

loader: $(OBJ)
	$(CC) $(FLG) $(SRC) -o $@ $^

%.o: %.c $(HDR)
	$(CC) $(FLG) -c -o $@ $<

clean:
	rm -f $(OBJ) $(OUT)