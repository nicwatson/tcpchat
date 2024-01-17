# TCPChat

A program implementing a simple, two-way text chat protocol in ANSI C, using POSIX system calls. Originally written as a homework assignment in an Operating Systems and Networking course.

## Compiling

Compile with: `	gcc -ansi -Wall TCPChat.c TCPChatClient.c TCPChatServer.c HandlePeer.c DieWithError.c -o tcpchat`

## Usage

- Launch two separate shells on a Linux machine, or on two separate, network-connected Linux machines.
- One shell will be the server. Use the command: `tcpchat HANDLE SERVER_PORT` to start a server listening on `SERVER_PORT`, using the chat handle `HANDLE`.
- The other shell will be the client. Use the command: `tcpchat HANDLE SERVER_PORT IP_ADDRESS` to connect to a server listening on `SERVER_PORT` at the given `IP_ADDRESS`. The `HANDLE` here is the chat handle that the client-side will use.
- You can now type messages in either shell, and they will be forwarded (with handle attached) to the other shell.
- The client can disconnect with the `.quit` command. The server will continue to listen for new connections until the process is terminated (e.g. `CTRL-C`).

## Acknowledgments

Portions of the code, as noted with inline comments, are adapted from Michael Donahoo and Kenneth Calvert's _TCP/IP Sockets in C: Practical Guide for Programmers_, via [their webpage](http://cs.baylor.edu/~donahoo/practical/CSockets/).

Donahoo and Calvert's code is licensed for re-use under GPL v2, with the provision that derivative works may be distributed under GPL v2 or any later GPL version.

