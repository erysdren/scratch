
EXEC?=moon
RM?=rm -f
CC?=gcc
PKGCONFIG?=pkg-config
PKGS?=sdl2

override CFLAGS += -g3 $(shell $(PKGCONFIG) --cflags $(PKGS))
override LDFLAGS += -g3 $(shell $(PKGCONFIG) --libs $(PKGS)) -lm

OBJECTS = main.o

all: clean $(EXEC)

clean:
	$(RM) $(OBJECTS) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)
