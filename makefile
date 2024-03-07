CC=g++
CFLAGS=-Wall -g
all: p_serial
p_serial:
	$(CC) $(CFLAGS) -o p_serial pserial.cpp
clean:
	rm -rf *.o *.exe
