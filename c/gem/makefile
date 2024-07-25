
EXEC ?= hello.exe
RM ?= rm -f
CC = i586-pc-msdosdjgpp-gcc

override CFLAGS += -Wall -Wextra -pedantic
override LDFLAGS +=

OBJECTS = main.o gem.o

all: clean $(EXEC)

clean:
	$(RM) $(OBJECTS) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
