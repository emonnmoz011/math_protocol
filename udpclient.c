/* a simple echo client using UDP */
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
#include "udp_sock_proto.h" // header


#define SERVER_UDP_PORT	5000
#define MAXLEN	3
#define DEFLEN	3

long delay(struct timeval t1, struct timeval t2); // calculating time delay

int main(int argc, char **argv)
{

int len;
int data_size = DEFLEN, port = SERVER_UDP_PORT;
int i, j, sd, server_len;
struct hostent *hp;
struct sockaddr_in server;
char *pname, *host, *bp, rbuf[MAXLEN], sbuf[MAXLEN];
struct timeval start, end;

pname = argv[0];
argc--;
argv++;

if (argc > 0 && (strcmp(*argv, "-s") == 0)) {
  if (--argc > 0 && (data_size = atoi(*++argv))) {
    argc--;
    argv++;
  }
  else {
    fprintf(stderr, "Usage: %s [-s data_size] host[port]\n", pname);
    exit(1);
  }
}

if (argc > 0) {
  host = *argv;
  if (--argc > 0) port = atoi(*++argv);
}
else {
  fprintf(stderr, "Usage: %s [-s data_size] host[port]\n", pname);
  exit(1);
}


/* Create a datagram socket */

if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
  fprintf(stderr, "Can't create a socket\n");
  exit(1);
}

/* Store server info */

bzero((char *)&server, sizeof(server));
server.sin_family = AF_INET;
server.sin_port = htons(port);
if ((hp = gethostbyname(host)) == NULL) {
  fprintf(stderr, "Can't get server address\n");
  exit(1);
}
bcopy(hp->h_addr, (char *)&server.sin_addr, hp->h_length);
if (data_size > MAXLEN) {
  fprintf(stderr, "Data is too big\n");
  exit(1);
}


gettimeofday(&start, NULL);

/* Transmit */
/* Scanning data to transmit. Only HEX values are accepted */
unsigned char n1,n2;
printf("Enter Two Hex values:");
scanf("%x%x",&n1,&n2); 


server_len = sizeof(server);

/* Defining Protocol */

{

struct math_proto mp;	
		
		mp.opr='+'; 
		mp.val1=n1;
		mp.val2=n2;
		math_proto_print_debug(&mp); // observing the debug
		math_proto_create_pkt(&mp, sbuf);
		
  		
  	if (sendto(sd, sbuf, data_size, 0, (struct sockaddr *)&server, server_len) == -1)  // checking if valid data is sent
  		{
  		fprintf(stderr, "sendto error\n");
  		exit(1);
  			}
  
    	
len = recvfrom(sd, rbuf, MAXLEN, 0, (struct sockaddr *)&server, &server_len); // receive data from server
    	
    	if (len < 0) 
    		{
  		fprintf(stderr, "recvfrom error\n"); // if there are no data, print an error
  		exit(1);
  			}
  			
printf("Received from server: %d bytes\n", len);
  		
	for(i=0;i<len;i++) 
		{ printf("%02x", rbuf[i]); } //print received data dump
		printf("\n"); 
    	
  
gettimeofday(&end, NULL);

printf("Round trip delay: %ld ms.\n", delay(start,end));



} //closing the structure

close(sd);

} //clsosing the main fuction
    	
    	
  

long delay (struct timeval t1, struct timeval t2)
{
  long d;
  d = (t2.tv_sec - t1.tv_sec) * 1000;
  d+- ((t2.tv_usec - t1.tv_usec + 500) / 1000);
  return(d);
}



