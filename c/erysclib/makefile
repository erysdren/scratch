
CC ?= gcc
RM ?= rm -f

EXEC ?= test1

OBJECTS = test1.o erysdren_utils.o

all: clean $(EXEC)

clean:
	$(RM) $(OBJECTS) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<
