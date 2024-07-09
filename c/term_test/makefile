
EXEC ?= term_test
RM ?= rm -f
CC ?= gcc

override CFLAGS += -g3 -fsanitize=address
override LDFLAGS += -g3 -fsanitize=address

OBJECTS = main.o term.o

all: clean $(EXEC)

clean:
	$(RM) $(OBJECTS) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
