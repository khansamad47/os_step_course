#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        return 0;

    }
    for (int i = 1; i != argc; ++i)
    {
        FILE* filePtr = fopen(argv[i], "r");
        if (filePtr == NULL)
        {
            printf("wcat: cannot open file\n");
            return 1;
        }
        char buffer[80];
        memset(buffer, 0x0, 80);
        while(fgets(buffer, 80, filePtr))
        {
            printf("%s",buffer);
        }
        fclose(filePtr);
    }
    return 0;
}
