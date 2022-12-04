/* a simple echo server using UDP */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <sys/time.h>
#include <stdio_ext.h>
#include "udp_sock_proto.h" //header

#define SERVER_UDP_PORT	5000
#define MAXLEN	3




int main(int argc, char **argv)
{
int n, sd, client_len, port,i;
struct sockaddr_in server, client;
char buf[MAXLEN];

switch(argc) {
case 1:
	port = SERVER_UDP_PORT;
	break;
case 2:
	port = atoi(argv[1]);
	break;
default:
	fprintf(stderr, "Usage: %s [port]\n", argv[0]);
	exit(1);
}



/* Create a dgram socket */

if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
  fprintf(stderr, "Can't create a socket\n");
  exit(1);
}

/* Bind an address to the socket */

memset(&server, 0, sizeof(server));
server.sin_family = AF_INET;
server.sin_port = htons(port);
server.sin_addr.s_addr = htonl(INADDR_ANY);
//server.sin_addr.s_addr = inet_addr("127.0.0.1");
if(bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1) {
  fprintf(stderr, "Can't bind name to socket\n");
  exit(1);
}

/* Connect */

while(1) {

  client_len = sizeof(client);
  if ((n = recvfrom(sd, buf, MAXLEN, 0, (struct sockaddr *)&client, &client_len)) < 0) {
    fprintf(stderr, "Can't receive datagram\n");
    exit(1);
  }

if(n==3) //check valid ??
  {	
  
  	struct math_proto mp; struct math_proto mp_result;
  	math_proto_parse_pkt(&mp, buf); math_proto_print_debug(&mp);
  	math_proto_calculate(&mp, &mp_result); math_proto_print_debug(&mp_result);
   	math_proto_create_pkt(&mp_result, buf);
   	sendto(sd, buf, n, 0, (struct sockaddr *)&client, client_len); //send the data to client		
  }
  
  
  for(i=0;i<n;i++) { printf("%02x ", buf[i]); } printf("\n"); //print received data dump

printf("Received (%d bytes) from %s\n", n,(char *)inet_ntoa(client.sin_addr)); // print the data sent from client
  
  if (sendto(sd, buf, n, 0, (struct sockaddr *)&client, client_len) != n) {
    fprintf(stderr, "Can't send datagram\n");
    exit(1);
  }

  // Clear out the buffer
  memset(&buf, 0, MAXLEN);
}

close(sd);
return(0);
}



