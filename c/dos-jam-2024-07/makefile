
EXEC ?= luna.exe
RM ?= rm -f
CC = i586-pc-msdosdjgpp-gcc
STRIP = i586-pc-msdosdjgpp-strip

override CFLAGS += -Wall -pedantic -march=i486 -mtune=i486 -ffast-math -funroll-loops -fomit-frame-pointer -Ilua
override LDFLAGS += -Llua -llua -lm

OBJECTS = main.o mem.o mouse.o palette.o ui.o util.o vid.o

all: clean $(EXEC)

clean:
	$(RM) $(OBJECTS) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)
	$(STRIP) $@

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
