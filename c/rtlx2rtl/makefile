
CC ?= gcc
RM ?= rm -f

CFLAGS ?= -std=c99 -O3 -pedantic -Wall -Wextra
LDFLAGS ?=

EXEC ?= rtlx2rtl
SOURCES = rtlx2rtl.c

all: clean $(EXEC)

clean:
	$(RM) $(EXEC)

$(EXEC): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
