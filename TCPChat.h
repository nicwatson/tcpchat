/* 
FILE: TCPChat.h
Part of TCPChat by Nic Watson
 
*/

#ifndef TCPCHAT_H
#define TCPCHAT_H

#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <errno.h>
#include <fcntl.h>		/* for fcntl() */

/* Maximum length of chat handle */
#define HANDLE_LEN 31
/* Maximum length of chat message */
#define MSGBUFSIZE 160

/* Error handling function */
void DieWithError(char *errorMessage);
/* Start chat server program */
void startServer(char *handle, unsigned short servPort);
/* Starts chat client program */
void startClient(char *handle, unsigned short servPort, char * servIP);
/* TCP chat handler function */
void chatProcess(int clntSocket, char *handle);

#endif
