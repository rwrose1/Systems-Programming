CC = gcc
CFLAGS  = -g
OBJECTS = flightRecorder.o

flightRecorder: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o flightRecorder
%.o: %.c
	$(CC) $(CFLAGS) -c $<
