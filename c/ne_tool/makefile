
CC ?= gcc
RM ?= rm -f
EXEC ?= ne_tool
PKGCONFIG ?= pkg-config

ifeq ($(DEBUG), 1)
override CFLAGS += -g3
endif

ifeq ($(PARANOID), 1)
override CFLAGS += -fsanitize=address,undefined -Wall -Wextra -pedantic
override LDFLAGS += -fsanitize=address,undefined
endif

ifeq ($(RELEASE), 1)
override CFLAGS += -O3
override LDFLAGS += -O3
endif

OBJECTS = \
	main.o

all: $(EXEC)

clean:
	$(RM) $(OBJECTS) $(EXEC)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)
