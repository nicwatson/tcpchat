/*
FILE: HandlePeer.c
Part of TCPChat by Nic Watson

Contains functions used by chat server or chat client for the actual exchange of
messages.  One function fits all, in that chatProcess() is run by both the
server and the client (at this point there is no practical difference between
the two).  In the code, the system on the other end (whether it is actually the
server or client in real life) is referred to simply as "peer".
*/

#include "TCPChat.h"

/* Required for fcntl */
#define _GNU_SOURCE

/* Used to get a message from input and send it to the peer, and attempt to
    receive messages sent by peer.  Returns the length of the message received
    from peer.  This return value serves no real purpose except insofar as it is
	not zero or -1.  Returns -1 only if the local machine or the peer gave 
	".quit" command.  Returns 0 if no message was received from peer.
	Does not return at all if there is a fatal read(), send() or recv() error.  
	Req'd parameters:
		clntSocket - the socket used for chat
		handle - local machine's handle
		peerHandle - peer's handle */
int chatSend(int clntSocket, char * handle, char * peerHandle)
{
	char msgBuffer[MSGBUFSIZE+1];                  /* Message buffer */
	int msgSize;                                   /* Message size counter */

	/* Message sending */	
    msgSize = read(0, msgBuffer, MSGBUFSIZE);  /* Read from stdin */
	if(msgSize != -1)       /* Error, or just no input given */
	{
        if(errno != EAGAIN) /* True if there was a genuine fatal error */
        {
            DieWithError("read() failed");
        }
        if(send(clntSocket, msgBuffer, msgSize, 0) < 0) /* Send msg to peer */
        {
            DieWithError("send() failed");
        }
        msgBuffer[msgSize - 1] = '\0';      /* 0-terminated for strcmp's sake */
        if(strcmp(msgBuffer, ".quit") == 0)     /* Connection dropped by self */
        {
            printf("\n* You have dropped the connection with %s.", peerHandle);
            return -1;
        }
        printf("%s: ", handle);                        /* Reprint prompt */
        fflush(stdout);
    }
    
    /* Message receiving */
    msgSize = recv(clntSocket, msgBuffer, MSGBUFSIZE, 0);   /* recv from peer */
    if(msgSize != -1)           /* Error, or just nothing to receive */
    {
        if(errno != EAGAIN)     /* True if there was a genuine fatal error */
        {
            DieWithError("recv() failed");
        }
        msgBuffer[msgSize-1] = '\0';                    /* null-terminate msg */
        printf("\n%s: %s", peerHandle, msgBuffer);
        if(strcmp(msgBuffer, ".quit") == 0) /* Connection dropped by peer */
        {
            printf("\n* %s dropped the connection.", peerHandle);
            return -1;
        }
        printf("\n%s: ", handle);                       /* re-print prompt */
        fflush(stdout);
    }
    if(msgSize == -1)
    {
		return 0;	/* No msg received from peer (like EAGAIN - not an error) */
	}
    return msgSize;	/* Message receieved from peer. */
}

/* Handles message exchange loop.
	Req'd parameters:
		clntSocket - the socket used for chat
		handle - handle used by user on local machine */
void chatProcess(int clntSocket, char * handle)
{
	char peerHandle[HANDLE_LEN+1];				/* Stores peer's handle */
	fcntl(0, F_SETFL, O_NDELAY);				/* Set stdin to non-blocking */
	
	/* Exchange handles */ 
	if(send(clntSocket, handle, HANDLE_LEN+1, 0) < -1)
		DieWithError("send() handle failed");
	if(recv(clntSocket, peerHandle, HANDLE_LEN+1, 0) < 0)
    	DieWithError("recv() handle failed");

	fcntl(clntSocket, F_SETFL, O_NONBLOCK);		/* Set socket to non-blocking */
	
	printf("\n%s: ", handle);					/* Print prompt (own handle) */
	/* Need to fflush() to make sure the printed prompt is sent to the screen
	before anything else happens - otherwise prompts won't appear correctly */
	fflush(stdout);   
	
	int cntl;				/* Status control variable */
	do						/* Message exchange loop */
	{
        cntl = chatSend(clntSocket, handle, peerHandle);
	}while(cntl >= 0);		/* Loop will exit if someone has ".quit" */
    close(clntSocket);		/* Close client socket */
	printf("\n");
	/* Return to calling program (either server or client) */
}
