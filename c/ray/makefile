
CC ?= gcc
RM ?= rm -f

EXEC ?= ray
OBJECTS = main.o map.o cJSON.o

all: $(EXEC)

clean:
	$(RM) $(OBJECTS) $(EXEC)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)
