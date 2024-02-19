/*
1. Write a program that calls fork(). Before calling fork(), have the
main process access a variable (e.g., x) and set its value to something (e.g., 100). What value is the variable in the child process?
What happens to the variable when both the child and parent change
the value of x?

Ans: 
*/

#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int x = 99;
	int rc = fork();
	if (rc < 0)
	{
		fprintf(stderr, "error: failed to fork\n");
		return 1;
	}
	if (rc == 0)
	{
		// This is the child process
		fprintf( stdout, "I am pid %d\n", getpid());
		fprintf( stdout, "value of x is %d\n", x);
		x = 123;
		fprintf( stdout, "value of x changed to  %d\n", x);
	}
	else 
	{
		fprintf( stdout, "I am pid %d\n", getpid());
		fprintf( stdout, "value of x is %d\n", x);
		x = 456;
		fprintf( stdout, "value of x changed to  %d\n", x);
	}
	return 0;
}
