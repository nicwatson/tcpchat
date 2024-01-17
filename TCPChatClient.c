/*
FILE: TCPChatClient.c
Part of TCPChat by Nic Watson

Client-side initialization code.

Acknowledgements:
	Code adapted from http://cs.baylor.edu/~donahoo/practical/CSockets/
	which is the online resource for "TCP/IP Sockets in C: Practical
	Guide for Programmers" by Michael Donahoo and Kenneth Calvert.
	Used under GPL license v2+
*/

#include "TCPChat.h"

#define RCVBUFSIZE 160   /* Size of receive buffer */

/* Connect TCP chat client to the given server */
void startClient(char * handle, unsigned short servPort, char *servIP)
{
    int sock;						/* Socket descriptor */
    struct sockaddr_in servAddr;	/* Chat server address */

    /* Create a reliable, stream socket using TCP */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");

    /* Construct the server address structure */
    memset(&servAddr, 0, sizeof(servAddr));			/* Zero out structure */
    servAddr.sin_family = AF_INET;					/* Internet address family*/
    servAddr.sin_addr.s_addr = inet_addr(servIP);	/* Server IP address */
    servAddr.sin_port = htons(servPort);			/* Server port */

    /* Establish the connection to the echo server */
    if(connect(sock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
		DieWithError("connect() failed");

	chatProcess(sock, handle);
    exit(0);
}
