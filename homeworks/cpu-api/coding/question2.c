/*
2. Write a program that opens a file (with the open() system call)
and then calls fork() to create a new process. Can both the child
and parent access the file descriptor returned by open()? What
happens when they are writing to the file concurrently, i.e., at the
same time?

Ans: Seems like it works fine, there is no crash atleast. However some times 
lines are half written by the parent and then the child starts to write.
*/

#include <stdio.h>
#include <unistd.h>

int main (int argc, char* argv[])
{
	FILE* outputFile = fopen("question2.out","w");
	int rc = fork();
	if (rc < 0)
	{
		fprintf(stderr, "failed to fork process\n");
		return 1;
	}
	if (rc == 0)
	{
		fprintf(stdout, "I am child process %d\n", getpid());
		for (int i = 0; i != 1000; ++i)
		{
			fprintf(outputFile, "I am the child: writing i = %d\n", i);
		}
	}
	else {
		fprintf(stdout, "I am parent process %d\n", getpid());
		for (int i = 0; i != 1000; ++i)
		{
			fprintf(outputFile, "I am the parent: writing i = %d\n", i);
		}
	}
	fclose(outputFile);
	return 0;
}

