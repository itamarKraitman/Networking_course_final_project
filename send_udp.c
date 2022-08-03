#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int socket_fd; // init variable to store the descriptor number which will be returns from the socket method
  struct sockaddr_in  dest; // variable of type structure describing an Internet socket address
  struct hostent *hostptr; // variable of type description of data base entry for a single host
  struct { char head; u_long body; char tail; } msgbuf; // defining the structure of the body of the message
/*creating the socket, domain is IPv4 Internet protocols, type is SOCK_DGRAM to support datagrams, protocol is 0 to make the socket serves a particular socket type*/
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0); 
  bzero((char *) &dest, sizeof(dest)); /* They say you must do this, you can also do this with memset*/
  hostptr = gethostbyname(argv[1]); // creates an hostnet for the host name that is given rom the command line 
  dest.sin_family = (short) AF_INET; // the address family for the transport address is set to AF_INET
  bcopy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length); // copy the host address to the dest sin_addr with length of the host pointer
  dest.sin_port = htons((u_short)0x3333); // converts the address to network address
  // builds the message
  msgbuf.head = '<';
  msgbuf.body = htonl(getpid()); /* IMPORTANT! converts the process ID into host byte order */
  msgbuf.tail = '>';

  sendto(socket_fd,&msgbuf,sizeof(msgbuf),0,(struct sockaddr *)&dest,
                  sizeof(dest)); // sends the message to another socket

  return 0; 
}
