#include <stdio.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("wzip: file1 [file2 ...]\n");
        return 1;
    }
    for (size_t i = 1; i != argc; ++i)
    {
        FILE* filePtr = fopen(argv[i],"r");
        int buffer = fgetc(filePtr);
        int character = buffer;
        int counter = 0;
        while (EOF != buffer)
        {
            if (buffer == character)
            {
                counter++;
            }
            else {
                fwrite(&counter,  4, 1, stdout);
                fwrite(&character,1, 1, stdout);
                character = buffer;
                counter = 1;
            }
            buffer = fgetc(filePtr);
        }
        fclose(filePtr);
    }
    return 0;
}
