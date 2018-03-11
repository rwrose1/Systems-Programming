CC = gcc
CFLAGS  = -g
OBJECTS = main.o functionsOther.o functionsOne.o functionsTwo.o

mylogger: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o mylogger
%.o: %.c
	$(CC) $(CFLAGS) -c $<
