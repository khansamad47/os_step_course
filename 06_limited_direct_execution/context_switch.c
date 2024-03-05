#define _GNU_SOURCE
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>

int main(int argc, char* argv[])
{
    int pipe1[2]; // { child_read}
    int pipe2[2];
    pipe(pipe1);
    pipe(pipe2);
    struct timeval t0, t1;
    double total_time = 0;
    char buffer[1];
    int iterations = 100000;
    cpu_set_t mask;
    CPU_ZERO(&mask); // clear mask
    CPU_SET(0, &mask);
    sched_setaffinity(getpid(), sizeof(mask), &mask);
    int pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "Failed to fork");
        exit(1);
    }
    if (pid == 0)
    {
        sched_setaffinity(getpid(), sizeof(mask), &mask);
        // child process
        close(pipe1[0]); // Close pipe1 read end
        close(pipe2[1]); // Close pipe2 write end
        gettimeofday(&t0, NULL);
        for(size_t i = 0; i != iterations; ++i)
        {
            //printf("Child: Writing\n");
            write(pipe1[1], "C", 1);
            //printf("Child: Wrote\n");
            //printf("Child: Reading\n");
            read(pipe2[0], buffer, 1);
            //printf("Child: Got %s\n", buffer);
        }
        gettimeofday(&t1, NULL);
        long elapsed = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;
        total_time += (elapsed);
        total_time /= 2;
        printf("Time per syscall = %f\n", total_time/iterations);
        return 0;
    }
    // parent
    close(pipe1[1]); // Close pipe1 write end
    close(pipe2[0]); // Close pipe2 read end
    for(size_t i = 0; i != iterations; ++i)
    {
        //printf("Parent: Reading\n");
        read(pipe1[0], buffer, 1);
        //printf("Parent: Got %s\n", buffer);
        //printf("Parent: Writing\n");
        write(pipe2[1], "P", 1);
        //printf("Parent: Wrote\n");
    }
    return 0;
}
