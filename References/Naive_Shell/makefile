CC = gcc
CFLAGS = -g
OBJECTS = main.o

shell: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o shell
%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean:
	-rm $(OBJECTS) shell
