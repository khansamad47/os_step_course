/*
4. Write a program that calls fork() and then calls some form of
exec() to run the program /bin/ls. See if you can try all of the
variants of exec(), including (on Linux) execl(), execle(),
execlp(), execv(), execvp(), and execvpe(). Why do
you think there are so many variants of the same basic call?

execl -- full-path of binary, args as list
execlp -- binary will be searched in path, args as list

*/
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	if (fork() == 0) {
		printf("execl \n");
		int rc = execl("/usr/bin/ls","/usr/bin/ls",(char*) NULL);
		fprintf(stderr, "error: failed to execl with rc = %d\n", rc);
		return 0;
	}
	if (fork() == 0) {
		printf("execlp \n");
		int rc = execlp("ls","ls", (char*) NULL);
		fprintf(stderr, "error: failed to execlp with rc = %d\n", rc);
		return 0;
	}
	if (fork() == 0) {
		printf("execle \n");
		char* env [] = {"MESSAGE=SAMAD", NULL};
		int rc = execle("/usr/bin/echo","echo", "$MESSAGE", (char*) NULL, env);
		fprintf(stderr, "error: failed to execl with rc = %d\n", rc);
		return 0;
	}
	return 0;
}

