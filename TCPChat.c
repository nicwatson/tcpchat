/*
FILE: TCPChat.c (MAIN file)
Part of TCPChat by Nic Watson

----
Frontend for the TCP Chat program.  The same executable can be used to activate
the server or the client.  Arguments are given on the command line in the
following format:
	<Handle> <Server Port> [IP address]
	
	A chat handle and server port must be specified.  If an IP address is not
	specified, the program acts as chat server listening for connections on the
	given port.  If an IP address is specified, the program tries to connect to
	the given port on the given machine.  Once a server/client connection is
	established, client and server take turns exchanging chat messages.
	
	It is possible to exit the chat at any time by typing ".quit" - this will
	inform both parties that one of them terminated the chat.  In the client's
	case the program will exit, while in the server's case, the program will
	just go back to waiting for more connections.
	
Note:  the only way to terminate the server program (make it stop listening
	for connections) is to actually interrupt (e.g. CTRL-C) or kill it.  The
	".quit" command just terminates a chat session.

File listing:
	TCPChat.h
	DieWithError.c
	HandlePeer.c
	TCPChat.c
	TCPChatClient.c
	TCPChatServer.c

Compile with:
	gcc -ansi -Wall TCPChat.c TCPChatClient.c TCPChatServer.c HandlePeer.c
		DieWithError.c -o tcpchat

*/

#include "TCPChat.h"

int main(int argc, char * argv[])
{
	char handle[HANDLE_LEN+1];
	if (argc == 3)     /* Test for correct number of arguments */
    {
		strncpy(handle, argv[1], HANDLE_LEN);
		startServer(argv[1], atoi(argv[2]));			/* Server version */
	}
	else if(argc == 4)
	{
		strncpy(handle, argv[1], HANDLE_LEN);
		startClient(argv[1], atoi(argv[2]), argv[3]);	/* Client version */
	}
	else
	{
        fprintf(stderr, "Usage:  %s <Handle> <Server Port> [IP address]\n",
			argv[0]);
        exit(1);
    }
	return 0;
}
