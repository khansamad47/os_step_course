/*
3. Write another program using fork(). The child process should
print “hello”; the parent process should print “goodbye”. You should
try to ensure that the child process always prints first; can you do
this without calling wait() in the parent?
Ans: I can call sleep
*/

#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int rc = fork();
	if ( rc < 0 )
	{
		fprintf(stderr, "error: failed to fork \n");
		return 1;
	}
	if (rc > 0)
	{
		// parent
		//sleep(1);
		printf("goodbye\n");
	}
	else {
		// child
		printf("hello\n");
	}
	return 0;
}
