
CC ?= gcc
RM ?= rm -f
PKGCONFIG ?= pkg-config

TILE_EXEC ?= tile
BRROTT_EXEC ?= brrott
EXECS = $(TILE_EXEC) $(BRROTT_EXEC)

TILE_OBJECTS = tile.o brprogram.o
BRROTT_OBJECTS = brrott.o brprogram.o
OBJECTS = $(TILE_OBJECTS) $(BRROTT_OBJECTS)

override CFLAGS += $(shell $(PKGCONFIG) sdl2 brender --cflags)
override LDFLAGS += -lm $(shell $(PKGCONFIG) sdl2 brender --libs)

all: clean $(EXECS)

clean:
	$(RM) $(OBJECTS) $(EXECS)

$(TILE_EXEC): $(TILE_OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BRROTT_EXEC): $(BRROTT_OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
