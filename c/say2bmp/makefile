
CC=clang
RM?=rm -f
PKGCONFIG?=pkg-config
PKGS?=sdl3

override CFLAGS+=-Wall -Wextra -pedantic -std=c23

override CFLAGS+=$(shell $(PKGCONFIG) --cflags $(PKGS))
override LDFLAGS+=$(shell $(PKGCONFIG) --libs $(PKGS)) -lm

OBJEXT?=.o
BINEXT?=

OBJ=say2bmp$(OBJEXT)

EXEC=say2bmp$(BINEXT)

all: clean $(EXEC)

clean:
	$(RM) $(OBJ) $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
