
# compile tools
CC = i586-pc-msdosdjgpp-gcc
LD = i586-pc-msdosdjgpp-ld
AS = i586-pc-msdosdjgpp-as

# file commands
CP ?= cp
MV ?= mv
RM ?= rm -f

# misc
PYTHON ?= python3
DOSBOX ?= dosbox-x

# base cflags
CFLAGS += -Ofast -ffast-math -funroll-loops -fomit-frame-pointer

# executable name
EXEC ?= build/ray.exe

# objects
OBJECTS = fix32.o hash.o pixelmap.o ray.o dos.o main.o utils.o math.o \
	console.o keyboard.o level.o cvar.o cmd.o wad.o timer.o cmdlib.o \
	cvarlib.o adlib.o imf.o actor.o game.o engine.o

# clean and build execs
all: clean $(EXEC)

# remove objects and executable
clean:
	$(RM) $(OBJECTS) $(EXEC)

# run engine in dosbox
run: $(EXEC)
	$(DOSBOX) -conf build/dosbox-x.conf

# build pixelmaps
pixelmaps:
	$(PYTHON) tools/pxlgen assetsrc/*.png
	$(MV) assetsrc/*.pxl build/

# build levels
levels:
	$(PYTHON) tools/lvlgen assetsrc/*.tmj
	$(MV) assetsrc/*.lvl build/

# build assets
assets: pixelmaps levels

# build executable
$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

# generic c object rule
%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<
