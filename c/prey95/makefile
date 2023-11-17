
CC ?= gcc
RM ?= rm -f

SOURCES_BSP2PLY = bsp2ply.c bsp.c
SOURCES_WAD2PNG = wad2png.c wad.c mip.c

override LDFLAGS += -lm

all: clean bsp2ply wad2png

bsp2ply: $(SOURCES_BSP2PLY)
	$(CC) -o bsp2ply $(SOURCES_BSP2PLY) $(LDFLAGS) $(CFLAGS)

wad2png: $(SOURCES_WAD2PNG)
	$(CC) -o wad2png $(SOURCES_WAD2PNG) $(LDFLAGS) $(CFLAGS)

clean:
	$(RM) bsp2ply wad2png *.o *.exe
