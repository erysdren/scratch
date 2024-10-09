
RM ?= rm -f
PKGCONFIG ?= pkg-config

EXEC ?= test

OBJECTS = main.o

override CFLAGS += $(shell $(PKGCONFIG) sdl3 gl cglm --cflags)
override LDFLAGS += $(shell $(PKGCONFIG) sdl3 gl cglm --libs) -lm

all: clean $(EXEC)

clean:
	$(RM) $(OBJECTS) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)
