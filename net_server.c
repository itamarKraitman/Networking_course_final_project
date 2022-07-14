#include <sys/types.h>
#include <unistd.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>     
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

#define PORT 1337
#define SIM_LENGTH 10

int main(void)
{ 
  int sock; 
  int connect_sock; 
  struct sockaddr_in serv_name; 
  size_t len; 
  int count;
  /*creating the socket, domain is IPv4 Internet protocols, type is SOCK_STREAM and protocol is 0*/
  sock = socket(AF_INET, SOCK_STREAM, 0);
  /*erasing the data from the memory where serv_name is, number of bytes as the size of serv_name*/
  bzero(&serv_name, sizeof(serv_name)); 
  // init attributes of serv_name 
  serv_name.sin_family = AF_INET; // the address family for the transport address is set to AF_INET                                  
  serv_name.sin_port = htons(PORT); // converts the host address to network address

  bind(sock, (struct sockaddr *)&serv_name, sizeof(serv_name)); // assigns the address to the socket
          
  listen(sock, 1); // waiting for incoming connection request to come
  len = sizeof(serv_name);
  
  connect_sock = accept(sock, (struct sockaddr *)&serv_name, &len); // accepting the connection request on the line

  for (count = 1; count <= SIM_LENGTH; count++)
    { write(connect_sock, &count, 4); // writes the content of count to the terminal of the client
      printf("Server has written %d to socket.\n", count);
    }

  close(connect_sock); 
  close(sock);

}
