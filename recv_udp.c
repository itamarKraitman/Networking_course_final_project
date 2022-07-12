#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>


void printsin(struct sockaddr_in *s, char *str1, char *str2) {
  printf("%s:\n", str1);
  printf("%s: ", str2);
  char str3[30];
  strcpy(str3, (char*)inet_ntoa((struct in_addr)s->sin_addr));
  printf("ip= %s, port= %d", str3, s->sin_port);
  printf("\n");
}


int main(int argc, char *argv[])
{/*variable to store the descriptor number which will be returns from the socket method
  variable to store the integer that is returned fro the recive call
  and variable to store the size of "from" */
  int socket_fd, cc, fsize; 
  struct sockaddr_in  s_in, from; // variable of type structure describing an Internet socket address
  struct { char head; u_long  body; char tail;} msg; // defines the structure of the message that will be received
  // struct {int number;} msg;
/*creating the socket, domain is IPv4 Internet protocols, type is SOCK_DGRAM to support datagrams, protocol is 0 to make the socket serves a particular socket type*/
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);

  bzero((char *) &s_in, sizeof(s_in));  /* They say you must do this, you can also do this with memset*/

  s_in.sin_family = (short)AF_INET; // // the address family for the transport address is set to AF_INET
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD, contains an IPv4 address, converts it to host byte order */
  s_in.sin_port = htons((u_short)0x3333); // transport protocol port number, converts it to network byte order

  printsin( &s_in, "RECV_UDP", "Local socket is:"); 
  fflush(stdout); // make the program to print the content immediately to the terminal

  bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in)); // assigns the address to the socket

  for(;;) {
    fsize = sizeof(from); // takes the size of "form" to send it as parameter of address length to recvfrom function 
    cc = recvfrom(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&from,&fsize); //The recvfrom() call are used to receive messages from a socket.
    printsin( &from, "recv_udp: ", "Packet from:");
    printf("Got data ::%c%ld%c\n",msg.head,(long) ntohl(msg.body),msg.tail); // prints the message
    // printf("Got Data: %d", msg.number);
    fflush(stdout);
  }
  
  return 0;
}

