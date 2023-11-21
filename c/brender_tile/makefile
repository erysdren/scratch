
CC ?= gcc
RM ?= rm -f
PKGCONFIG ?= pkg-config

EXEC ?= brender_tile
OBJECTS = main.o brprogram.o

override CFLAGS += $(shell $(PKGCONFIG) sdl2 brender --cflags)
override LDFLAGS += -lm $(shell $(PKGCONFIG) sdl2 brender --libs)

all: clean $(EXEC)

clean:
	$(RM) $(OBJECTS) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
