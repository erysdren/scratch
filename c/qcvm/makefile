
EXEC ?= test
RM ?= rm -f
CC ?= gcc
PKGCONFIG ?= pkg-config

override CFLAGS += -std=c89 -pedantic -Wextra -Wall -Werror
override LDFLAGS +=

OBJECTS = main.o qcvm.o

all: clean $(EXEC)

clean:
	$(RM) $(OBJECTS) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
