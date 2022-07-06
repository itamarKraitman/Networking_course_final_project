.PHONY: all run clean
CC = gcc
FLAGS= 
HEADERS = 
all: send recv

send: send_udp.o
	$(CC) $< -o send 

recv: recv_udp.o
	$(CC) $< -o recv
%.o: %.c 
	$(CC) -c $< -o $@

clean:
	rm -f *.o send recv