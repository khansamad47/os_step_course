/*
5. Now write a program that uses wait() to wait for the child process
to finish in the parent. What does wait() return? What happens if
you use wait() in the child?

Ans: wait returns the pid of the child waited on. If you use wait on a child the wait returns negative value;

*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    printf("%d: hello\n", getpid());
	int rc = fork();
	if ( rc < 0 )
	{
		fprintf(stderr, "error: failed to fork \n");
		return 1;
	}
	if (rc > 0)
	{
		// parent
		int status = 0;
		int pid = wait(&status);
		printf("%d: child %d has exited with status %d\n", getpid(), pid, status);
	}
	else {
		// child
		printf("%d: hello\n", getpid());
		int status = 0;
		int pid = wait(&status);
		printf("%d: called wait from child status = %d, pid = %d\n", getpid(), status, pid);
	}
	return 0;
}
