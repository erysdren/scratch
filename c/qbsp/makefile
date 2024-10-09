
EXEC ?= test
RM ?= rm -f
CC ?= gcc
PKGCONFIG ?= pkg-config

override CFLAGS += $(shell $(PKGCONFIG) --cflags sdl3)
override LDFLAGS += $(shell $(PKGCONFIG) --libs sdl3)

OBJECTS = test.o

all: clean $(EXEC)

clean:
	$(RM) $(OBJECTS) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
