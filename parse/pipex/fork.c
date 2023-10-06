#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

/*
fork(2) is a system call that creates a new process by duplicating 
the calling process. The new process is known as the child process, 
while the original process is known as the parent process. 
After the fork, both processes execute the same code, but each has 
a separate memory space.
*/
int	main()
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		printf("This is the child process: pid = %d\n", getpid());
	else
		printf("This is the parent process: pid = %d\n", getpid());
	return (0);
}