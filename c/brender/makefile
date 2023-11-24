
CC ?= gcc
RM ?= rm -f
PKGCONFIG ?= pkg-config

TILE_EXEC ?= tile
BSP_EXEC ?= bsp
EXECS = $(TILE_EXEC) $(BSP_EXEC)

TILE_OBJECTS = tile.o brprogram.o
BSP_OBJECTS = bsp.o brprogram.o
OBJECTS = $(TILE_OBJECTS) $(BSP_OBJECTS)

override CFLAGS += $(shell $(PKGCONFIG) sdl2 brender --cflags)
override LDFLAGS += -lm $(shell $(PKGCONFIG) sdl2 brender --libs)

all: clean $(EXECS)

clean:
	$(RM) $(OBJECTS) $(EXECS)

$(TILE_EXEC): $(TILE_OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BSP_EXEC): $(BSP_OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
