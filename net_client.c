
#include <sys/types.h>
#include <unistd.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>    
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define SIM_LENGTH 10 
// #define IP_ADDRESS "127.0.1.1" -- put in comment to take the cmd input instead
#define PORT 1337 

char* nsLookup(char* hostname) {
  struct addrinfo* res;
  // char* hostname;
  char* hostaddr;
  struct sockaddr_in* saddr;
  
  // takes the host name which was supplied from the command line and stores it
  // creates the addrinfo and check if it has been created successfully
  if (0 != getaddrinfo(hostname, NULL, NULL, &res)) {
    fprintf(stderr, "Error in resolving hostname %s\n", hostname);
    exit(1);
  }
  // stores the host name and it's corresponding IP address, and prints them to the terminal 
  // saddr = (struct sockaddr_in*)res->ai_addr;
  hostaddr = inet_ntoa(saddr->sin_addr);
  return hostaddr;
}


int main(int argc, char* argv[])
{ 
  if (argc != 2) { // if an host name is not supplied from command line
    perror("no hostname supplied\n");
    exit(1);
  }
  
  int sock; 
  struct sockaddr_in cli_name; 
  int count;
  int value; 

  printf("Client is alive and establishing socket connection.\n");
  
  /*creating the socket, domain is IPv4 Internet protocols, type is SOCK_STREAM and protocol is 0*/
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) // if an error was raised when creating the socket
    { perror ("Error opening channel");
      close(sock);
      exit(1);
    }
  char* ip_address = nsLookup(argv[1]);
  // printf("%s", ip_address);
  bzero(&cli_name, sizeof(cli_name)); // erasing the memory from cli_name 
  /*init the attributes of cli_name*/
  cli_name.sin_family = AF_INET; 
  cli_name.sin_addr.s_addr = inet_addr(ip_address); // IPv4 numbers-and-dots notation into binary data in network byte order
  cli_name.sin_port = htons(PORT);

  /*if error was raised when trying to connect to the address, explain what was the problem and close the program, otherwise, connect the socket to the address*/
  if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0)
    { perror ("Error establishing communications");
      close(sock);
      exit(1);
    }

  /*reading the values that it receives from the server and prints them to the terminal*/
  printf("Address for %s is %s.\n", argv[1], ip_address);

  for (count = 1; count <= SIM_LENGTH; count++)
    { read(sock, &value, 4);
      printf("Client has received %d from socket.\n", value);
    }

  printf("Exiting now.\n");

  close(sock); 
  exit(0); 

} 

