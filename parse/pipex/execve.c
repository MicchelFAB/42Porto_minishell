#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

/* 
execve(2) is a system call that allows you to execute another program 
from within your program. It replaces the current process image with a 
new process image, effectively running a new program. 
It takes three arguments: the path to the program to be executed, 
an array of command line arguments, and an array of environment variables.
**
In this code, the args array contains the command line arguments to be passed 
to the ls command. execve(2) is then called with the path to the 
ls command (/bin/ls), the args array, and NULL for the environment variables. 
This replaces the current process image with the ls command, 
and the output of ls -l will be printed to the terminal. 
The printf() statement after execve(2) will not be executed, 
as the process image has been replaced.
 */
int		main()
{
	char	*ag[3];

	ag[0] = "ls";
	ag[1] = "-l";
	ag[2] = NULL;
	execve("/bin/ls", ag, NULL);
	printf("This line will not be executed.\n");

	return (0);
}