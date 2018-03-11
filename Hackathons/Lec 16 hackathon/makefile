CC = gcc
CFLAGS  = -g
OBJECTS = main.o

flight: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o flight
%.o: %.c
	$(CC) $(CFLAGS) -c $<
