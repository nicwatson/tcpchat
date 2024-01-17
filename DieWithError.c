/*
FILE: DieWithError.c
Part of TCPChat by Nic Watson

This file is originally from
	http://cs.baylor.edu/~donahoo/practical/CSockets/
which is the online resource for
	"TCP/IP Sockets in C: Practical Guide for Programmers"
	by Michael Donahoo and Kenneth Calvert.

Used under GPL license - see LICENSE.md

*/

#include <stdio.h>  /* for perror() */
#include <stdlib.h> /* for exit() */

/* Print error message and kill program */
void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}
