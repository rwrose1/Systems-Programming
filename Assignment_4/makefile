CC = gcc
CFLAGS = -g
OBJECTS = main.o BST.o hash.o hashFunction.o other.o

firstpass: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o firstpass
%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean:
	-rm $(OBJECTS) firstpass
