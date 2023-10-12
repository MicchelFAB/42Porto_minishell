#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

/* 
dup2(2) helps you ‘replace’ open file descriptors. 
By default, FD 0, 1 and 2 are open and are set to stdin, 
stdout and stderr respectively. dup2(2) allows you to replace 
these with another FD, which you may obtain with open(2). 
This can be useful for redirecting output from one FD to another, 
like using printf(3) to print to a file instead of the terminal.
 */
int		main(void)
{
	int fd;

	fd = open("example.txt", O_WRONLY | O_CREAT, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	printf("this is printed in example.txt\n");
	return (0);
}