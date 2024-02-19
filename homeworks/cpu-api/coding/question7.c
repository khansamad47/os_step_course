/*
7. Write a program that creates a child process, and then in the child
closes standard output (STDOUT FILENO). What happens if the child
calls printf() to print some output after closing the descriptor?
Ans: doesn't print if you close it
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char* argv[])
{
	int pid_child = fork();
	if (pid_child < 0)
	{
		fprintf(stderr,"error: failed to fork\n");
		return 1;
	}
	if (pid_child > 0)
	{
		// parent
		printf("%d: will wait for child %d\n",getpid(), pid_child);
		int status = 0;
		waitpid(pid_child, &status, 0);
		printf("%d: wait is over. now exit\n",getpid());
	}
	else {
		// child
		printf("%d: i am child will close stdout and attempt to print\n", getpid());
		fclose(stdout);
		printf("%d: print after stdout has been closed\n", getpid());

	}
	return 0;
}

