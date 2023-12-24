
# static variables
CC ?= gcc
RM ?= rm -f

# executable name
EXEC ?= dumpmaptiles

# objects
OBJECTS = dumpmaptiles.o

# clean and build execs
all: clean $(EXEC)

# remove objects and executable
clean:
	$(RM) $(OBJECTS) $(EXEC)

# build executable
$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

# generic c object rule
%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<
