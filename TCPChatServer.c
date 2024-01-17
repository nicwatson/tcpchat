/*
FILE: TCPChatServer.c
Part of TCPChat by Nic Watson

Server-side initialization code. The server differs from the client in
that the server waits and listens for client connections.

Acknowledgements:
	Code adapted from http://cs.baylor.edu/~donahoo/practical/CSockets/
	which is the online resource for "TCP/IP Sockets in C: Practical
	Guide for Programmers" by Michael Donahoo and Kenneth Calvert.
	Used under GPL license v2+
*/

#include "TCPChat.h"

#define MAXPENDING 5    /* Maximum outstanding connection requests */
		
/* Start TCP chat server on given port, open to chat connections */
void startServer(char * handle, unsigned short servPort)
{
    int servSock;					/* Socket descriptor for server */
    int clntSock;					/* Socket descriptor for client */
    struct sockaddr_in servAddr;	/* Local address */
    struct sockaddr_in clntAddr;	/* Client address */
    unsigned int clntLen;			/* Length of client addr data structure */

    /* Create socket for incoming connections */
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");
      
    /* Construct local address structure */
    memset(&servAddr, 0, sizeof(servAddr));			/* Zero out structure */
    servAddr.sin_family = AF_INET;					/* Internet addr family */
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);	/* Any incoming interface */
    servAddr.sin_port = htons(servPort);		/* Local port */

    /* Bind to the local address */
    if (bind(servSock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
        DieWithError("bind() failed");

    /* Mark the socket so it will listen for incoming connections */
    if (listen(servSock, MAXPENDING) < 0)
        DieWithError("listen() failed");

    for (;;) /* Run forever */
    {
        /* Set the size of the in-out parameter */
        clntLen = sizeof(clntAddr);

        /* Wait for a client to connect */
        if ((clntSock = accept(servSock, (struct sockaddr *) &clntAddr, 
                               &clntLen)) < 0)
            DieWithError("accept() failed");

        /* clntSock is connected to a client! */

        printf("Handling client %s\n", inet_ntoa(clntAddr.sin_addr));

        chatProcess(clntSock, handle);
		/* If one chat exits, loop repeats & server can handle another client */
    }
    /* NOT REACHED */
}
