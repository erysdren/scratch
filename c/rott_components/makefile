
CC ?= gcc
RM ?= rm -f

CFLAGS ?= -O3
LDFLAGS ?=

EXEC ?= rott_components
OBJECTS = mapset.o wad.o main.o

all: clean $(EXEC)

clean:
	$(RM) $(OBJECTS) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<
