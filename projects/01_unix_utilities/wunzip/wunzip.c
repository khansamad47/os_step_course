#include <stdio.h>

int main (int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("wunzip: file1 [file2 ...]\n");
        return 1;
    }
    for (size_t i = 1; i != argc; ++i)
    {
        FILE* filePtr = fopen(argv[i],"rb");
        unsigned char buffer[5]; // 5 byte buffer
        while(fread(buffer, 5, 1, filePtr))
        {
            int count = *((int *)buffer);
            char character = buffer[4];
            for(size_t i = 0; i != count; ++i)
            {
                printf("%c", character);
            }
        }
        fclose(filePtr);
    }
    return 0;
}
