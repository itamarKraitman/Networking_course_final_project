.PHONY: all run clean
CC = gcc
FLAGS= 
HEADERS = 
all: send recv client server lookup

send: send_udp.o
	$(CC) $< -o send 

recv: recv_udp.o
	$(CC) $< -o recv

client: net_client.o
	$(CC) $< -o client

server: net_server.o
	$(CC) $< -o server

lookup: nslookup.o
	$(CC) $< -o lookup
%.o: %.c 
	$(CC) -c $< -o $@

clean:
	rm -f *.o send recv client server lookup