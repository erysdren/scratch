
CC = gcc

EXEC = lev_tool

SOURCES = main.c kaitaistruct.c lev_quake.c pic.c stb_image_write.c

all: clean $(EXEC)

clean:
	rm -f $(EXEC)

$(EXEC):
	$(CC) -o $(EXEC) $(SOURCES) $(CFLAGS) $(LDFLAGS)
