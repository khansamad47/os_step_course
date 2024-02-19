
/*
6. Write a slight modification of the previous program, this time using waitpid() instead of wait(). When would waitpid() be
useful?
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
		int pid = waitpid(rc, &status, 0);
		printf("%d: child %d has exited with status %d\n", getpid(), pid, status);
	}
	else {
		// child
		printf("%d: hello\n", getpid());
	}
	return 0;
}
