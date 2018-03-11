CC = gcc
CFLAGS = -g
OBJECTS = sample.o file1.o

sample: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o sample
%.o: %.c
	$(CC) $(CFLAGS) -c $<
