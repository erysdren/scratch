
EXEC ?= vga2png
RM ?= rm -f
CC ?= gcc
BIN2O ?= bin2o

OBJECTS = vga2png.o

all: clean $(EXEC)

clean:
	$(RM) $(OBJECTS) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
