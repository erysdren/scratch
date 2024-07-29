
EXEC ?= luna.exe
RM ?= rm -f
CC = i586-pc-msdosdjgpp-gcc
STRIP = i586-pc-msdosdjgpp-strip

override CFLAGS += -Wall -pedantic -Os -march=i486 -mtune=i486 -ffast-math \
	-funroll-loops -fomit-frame-pointer -fstrength-reduce -fforce-addr \
	-Ilua -Wno-strict-aliasing
override LDFLAGS += -Llua -llua -lm

OBJECTS = list.o luna.o main.o mem.o mouse.o palette.o rect.o ui.o util.o vid.o

all: clean $(EXEC)

clean:
	$(RM) $(OBJECTS) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)
	$(STRIP) $@

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
