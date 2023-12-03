
CC = i586-pc-msdosdjgpp-gcc
LD = i586-pc-msdosdjgpp-ld
AS = i586-pc-msdosdjgpp-as
RM ?= rm -f
PYTHON ?= python3
CP ?= cp
MV ?= mv
TILED ?= tiled

CFLAGS += -Ofast -ffast-math -funroll-loops -fomit-frame-pointer

EXEC ?= build/ray.exe
OBJECTS = fix32.o hash.o pixelmap.o ray.o dos.o main.o utils.o math.o \
	console.o keyboard.o level.o cvar.o cmd.o wad.o timer.o cmdlib.o \
	cvarlib.o adlib.o imf.o actor.o game.o engine.o

all: clean $(EXEC)

clean:
	$(RM) $(OBJECTS) $(EXEC)

run: $(EXEC)
	dosbox-x -conf build/dosbox-x.conf

wads:
	$(PYTHON) tools/pxlgen assetsrc/*.png
	$(MV) assetsrc/*.pxl build/

levels:
	$(PYTHON) tools/lvlgen assetsrc/*.tmj
	$(MV) assetsrc/*.lvl build/

editor:
	$(TILED) assetsrc/game.tiled-project

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<
