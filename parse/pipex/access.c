#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

/* 
access(2) checks whether a process has permission to access a file 
or directory. It takes two arguments: the path to the file or directory, 
and a mode representing the type of access being checked. 
The mode is specified using constants such as R_OK, W_OK, and X_OK, 
which represent read, write, and execute permissions, respectively.
 */
int	main()
{
	if (access("example.txt", R_OK) != -1)
		printf("have permission\n");
	else
		printf("don't have permission\n");
	return (0);
}