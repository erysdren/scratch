
EXEC ?= vgashow
RM ?= rm -f
CC ?= gcc
PKGCONFIG ?= pkg-config

override CFLAGS += $(shell $(PKGCONFIG) sdl2 --cflags)
override LDFLAGS += $(shell $(PKGCONFIG) sdl2 --libs)

OBJECTS = vgashow.o

all: clean $(EXEC)

clean:
	$(RM) $(OBJECTS) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
