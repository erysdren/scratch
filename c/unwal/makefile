
CC ?= gcc

CFLAGS += -std=c99 -pedantic -Wall -Wextra

SOURCES = unwal.c

EXEC ?= unwal

all: clean $(EXEC)

clean:
	$(RM) $(EXEC)

$(EXEC): $(SOURCES)
	$(CC) -o $(EXEC) $(SOURCES) $(CFLAGS)
