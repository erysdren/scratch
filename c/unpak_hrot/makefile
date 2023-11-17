
CC ?= gcc

CFLAGS += -std=c99 -pedantic -Wall -Wextra

SOURCES = main.c

EXEC ?= unpak_hrot

all: clean $(EXEC)

clean:
	$(RM) $(EXEC)

$(EXEC): $(SOURCES)
	$(CC) -o $(EXEC) $(SOURCES) $(CFLAGS)
