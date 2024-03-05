#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    int handle = open("test.txt", O_CREAT ,"r");
    int iterations = 1000000;
    struct timeval t0, t1;
    double total_time = 0;
    gettimeofday(&t0, NULL);
    for (int i = 0; i < iterations; ++i)
    {
        read(handle, NULL,0);
        
    }
    gettimeofday(&t1, NULL);
    long elapsed = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;
    total_time += (elapsed);
    printf("Time per syscall = %f \n", (float) total_time /iterations);
    return 0;
}
