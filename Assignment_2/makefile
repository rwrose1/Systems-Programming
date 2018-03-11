CC = gcc
CFLAGS  = -g
OBJECTS = main.o archivingSize.o archiving.o archivingTwo.o other.o

archiver: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o archiver
%.o: %.c
	$(CC) $(CFLAGS) -c $<
