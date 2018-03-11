CC = gcc
CFLAGS = -g
OBJECTS = main.o index.o browse.o other.o

indexer: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o indexer
%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean:
	-rm $(OBJECTS) indexer
