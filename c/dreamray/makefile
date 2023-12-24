
# static variables
CC ?= gcc
RM ?= rm -f
PKGCONFIG ?= pkg-config

# base cflags and ldflags
CFLAGS += $(shell $(PKGCONFIG) sdl2 SDL2_image --cflags) -Ofast
LDFLAGS += -lm $(shell $(PKGCONFIG) sdl2 SDL2_image --libs)

# executable name
EXEC ?= dreamray

# objects
OBJECTS = main.o ray.o

# clean and build execs
all: clean $(EXEC)

# remove objects and executable
clean:
	$(RM) $(OBJECTS) $(EXEC)

# build executable
$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

# generic c object rule
%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<
