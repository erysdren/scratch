
AS = ia16-elf-as
CC = ia16-elf-gcc
LD = ia16-elf-ld
NASM = nasm
RM = rm -f

CFLAGS = -O3 -march=i8088 -mtune=i8088 -Wno-overflow -nostdinc -nostdlib -ffreestanding -Isys16
LDFLAGS =

SYS16_OBJECTS = sys16/memory.o sys16/io.o sys16/video.o sys16/fix16.o sys16/file.o sys16/int86.o sys16/int86x.o
GAME_OBJECTS = game/main.o game/ray.o
GAME_EXEC = game.com

# default
all: clean $(GAME_EXEC)

# clean
clean:
	$(RM) $(SYS16_OBJECTS) $(GAME_OBJECTS) $(GAME_EXEC)

# game
$(GAME_EXEC): $(GAME_OBJECTS) $(SYS16_OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

# run in dosbox
run: $(GAME_EXEC)
	dosbox-x -conf dosbox-x.conf

# run in 86box
run-86box: $(GAME_EXEC)
	mcopy -o -i game.img $(GAME_EXEC) ::
	86Box ./86box.cfg

# gnu assembly objects
%.o: %.s
	$(AS) -c $(ASFLAGS) -o $@ $<

# nasm assembly objects
%.o: %.asm
	$(NASM) -f elf -o $@ $<

# c objects
%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<
