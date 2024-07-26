
TARGET=scripter.app

CC=wcc
LD=wlink
CFLAGS=-ms
SYSTEM=dos

OBJECTS=main.o gem.o

.c.o:
	$(CC) $(CFLAGS) $*.c

$(TARGET): $(OBJECTS) wlink.rsp
	$(LD) @wlink.rsp

wlink.rsp: makefile
	echo name $(TARGET) >wlink.rsp
	echo system $(SYSTEM) >>wlink.rsp
	for %i in ($(OBJECTS)) do echo file %i >>wlink.rsp
