#include <stdio.h>
#include <stdbool.h>

void writeToOutput(int counter, int character)
{
    fwrite(&counter,  4, 1, stdout);
    fwrite((unsigned char*)&character,1, 1, stdout);
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("wzip: file1 [file2 ...]\n");
        return 1;
    }
    bool prevIsValid = false;
    int buffer;
    int prev;
    int counter = 1;
    for (size_t i = 1; i != argc; ++i)
    {
        FILE* filePtr = fopen(argv[i],"r");
        while ((buffer = fgetc(filePtr)) != EOF)
        {
            if (prevIsValid)
            {
                if (buffer == prev)
                {
                    counter++;
                }
                else {
                    writeToOutput(counter, prev);
                    counter = 1;
                }
            }
            prev = buffer; // Last line
            prevIsValid = true;
        }
        fclose(filePtr);
    }
    if (prevIsValid)
    {
        writeToOutput(counter, prev);
    }
    return 0;
}
