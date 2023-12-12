
CC ?= gcc
RM ?= rm -f
PKGCONFIG ?= pkg-config

TILE_EXEC ?= tile
EXECS = $(TILE_EXEC)

TILE_OBJECTS = tile.o brprogram.o
OBJECTS = $(TILE_OBJECTS)

override CFLAGS += $(shell $(PKGCONFIG) sdl2 brender --cflags)
override LDFLAGS += $(shell $(PKGCONFIG) sdl2 brender --libs) -lm

all: clean $(EXECS)

clean:
	$(RM) $(OBJECTS) $(EXECS)

$(TILE_EXEC): $(TILE_OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
