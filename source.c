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
  int socket_fd; 
  struct sockaddr_in  dest; 
  struct hostent *hostptr; 
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0); 
  bzero((char *) &dest, sizeof(dest)); 
  hostptr = gethostbyname(argv[1]);  
  dest.sin_family = (short) AF_INET; 
  bcopy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);
  dest.sin_port = htons((u_short)0x3333);
  int msg = 0;
  while(true) {
    msg++;
    sendto(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&dest,
                  sizeof(dest));
    sleep(1);
  }
  return 0;

