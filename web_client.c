
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

char* get_ip_by_hostname(char* hostname) {
  struct addrinfo* res;
  // char* hostname;
  char* hostaddr;
  struct sockaddr_in* saddr;
  
  // if host name is already an ip address
  if (isdigit(hostname[0]))
  {
    return hostname;
  }

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

int main(int argc, char* argv[]) {
if (argc != 2) { // if an host name is not supplied from command line
    perror("no hostname supplied\n");
    exit(1);
  }

  int sock; 
  struct sockaddr_in cli_name; 
  int count, n;
  int value;
  char* url = argv[1];
  // char hostname[100];
  // char* ip_address = get_ip_by_hostname(hostname);
  char ip_address[100];
  int port = 0;
  char page[100];
  char sendline[4096];
  char recvline[4096];
  int sendbytes;
  // char* ip_address = get_ip_by_hostname(hostname);
  sscanf(url, "http://%99[^:]:%99d/%99[^\n]", ip_address, &port, page);

  printf("Client is alive and establishing socket connection.\n");
  
  /*creating the socket, domain is IPv4 Internet protocols, type is SOCK_STREAM and protocol is 0*/
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) // if an error was raised when creating the socket
    { perror ("Error opening channel");
      close(sock);
      exit(1);
    }
  // printf("%s", ip_address);
  bzero(&cli_name, sizeof(cli_name)); // erasing the memory from cli_name 
  /*init the attributes of cli_name*/
  cli_name.sin_family = AF_INET; 
  cli_name.sin_addr.s_addr = inet_addr(ip_address); // IPv4 numbers-and-dots notation into binary data in network byte order
  cli_name.sin_port = htons((int) port);

  /*if error was raised when trying to connect to the address, explain what was the problem and close the program, otherwise, connect the socket to the address*/
  if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0)
    { perror ("Error establishing communications");
      close(sock);
      exit(1);
    }
    
  // sprintf(sendline, "GET %s HTTP/1.0\n HOST: %s\r\n\r\n", url, hostname);
  sprintf(sendline, "GET %s HTTP/1.0\r\n\r\n", url);
  sendbytes = strlen(sendline);

  if (write(sock, sendline, sendbytes) != sendbytes) {
    close(sock);
    exit(1);
  }

  memset(recvline, 0, __SIZE_MAX__);
  while((n = read(sock, recvline, __SIZE_MAX__)))  {
    printf("%s", recvline);
  }
  if (n < 0) {
    close(sock);
    exit(1);
  }
  printf("Exiting now.\n");

  close(sock); 
  exit(0); 
  

}


