/*
8. Write a program that creates two children, and connects the standard output of one to the standard input of the other, using the
pipe() system call.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void writer_process(int pipe_in)
{
	printf("writer process start\n");
	char message[] = "This is a message from the writer";
	int rc = write(pipe_in, message, strlen(message));
	if (rc < 0)
	{
		fprintf(stderr, "Failed to write to pipe rc = %d \n", rc);
	}
}
void reader_process(int pipe_out)
{
	printf("reader process start\n");
	char buffer[5];
	int bytes_read = 0;
	while ((bytes_read = read(pipe_out, &buffer,5)))
	{
		write(STDOUT_FILENO, buffer, bytes_read);
	}
	write(STDOUT_FILENO, "\n", 1);
}

int main(int argc, char* argv[])
{
	int fd_pipe[2];
	if (pipe(fd_pipe))
	{
		perror("Failed to open pipe");
		return 1;
	}
	printf("Opened pipe %d %d\n", fd_pipe[0], fd_pipe[1]);

	int child_pid = fork();
	if (child_pid < 0)
	{
		fprintf(stderr, "Failed to fork\n");
		exit(1);
	}
	if (child_pid == 0)
	{
		writer_process(fd_pipe[1]);	
		return 0;
	}
	int status;
	wait(&status);
	child_pid = fork();
	if (child_pid < 0)
	{
		fprintf(stderr, "Failed to fork\n");
		exit(1);
	}
	if (child_pid == 0)
	{
		reader_process(fd_pipe[0]);	
		return 0;
	}
	return 0;
}
