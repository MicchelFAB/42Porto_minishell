#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


/*
pipe(8) creates a unidirectional data channel that can be 
used for interprocess communication. The data written to 
one end of the pipe can be read from the other end of the pipe. 
Pipes are often used in combination with fork(2) to create a 
communication channel between parent and child processes.
*/

/*
In this code, pipe(8) is used to create a pipe, and fork(2) 
is used to create a child process. The child process writes 
the string "Hello, parent!" to the write end of the pipe 
using write(2), and then exits. The parent process reads the 
string from the read end of the pipe using read(2), 
and then prints it to the terminal using printf(3). 
The pipe is then closed in both processes using close(2).
*/
int		main()
{
	int		fd[2];
	pid_t	pid;
	char	buffer[13];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		close(fd[0]); //close the read end of the pipe
		write(fd[1], "hello parent", 13);
		close(fd[1]); //close the write end of the pipe
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]); //close the write end of the pipe
		read(fd[0], buffer, 13);
		close(fd[0]); // close the read end of the pipe
		printf("Message from the child: '%s'\n", buffer);
		exit(EXIT_SUCCESS);
	}
}
