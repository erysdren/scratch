
CC = i586-pc-msdosdjgpp-gcc
LD = i586-pc-msdosdjgpp-ld
AS = i586-pc-msdosdjgpp-as
RM ?= rm -f

EXEC ?= ray.exe
OBJECTS = fix32.o hash.o pixelmap.o ray.o dos.o main.o utils.o math.o \
	console.o

all: clean $(EXEC)

clean:
	$(RM) $(OBJECTS) $(EXEC)

run: $(EXEC)
	dosbox-x -conf dosbox-x.conf

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<
