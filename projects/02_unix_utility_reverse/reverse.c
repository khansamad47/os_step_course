#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct Node {
    char* data;
    struct Node* next;
};

typedef struct Node Node;

int main(int argc, char* argv[])
{
    // $ reverse [input [output]]
    if (argc > 3)
    {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }
    FILE * inputStream = stdin;
    FILE * outputStream = stdout;
    if (argc >= 2)
    {
        if ((inputStream = fopen(argv[1],"r")) == NULL)
        {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
    }
    if (argc == 3)
    {
        if (0 == strcmp(argv[1],argv[2]))
        {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }
        // Check if the two files refer to the same one
        struct stat file1;
        struct stat file2;
        if (0 == stat(argv[1], &file1) && 0 == stat(argv[2], &file2))
        {
            if (file1.st_ino == file2.st_ino)
            {
                fprintf(stderr, "reverse: input and output file must differ\n");
                exit(1);
            }
        }
        
        if((outputStream = fopen(argv[2],"w")) == NULL)
        {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
            exit(1);
        }
    }

    char * bufferPtr = NULL;
    size_t bufferSize = 0;
    Node* head = NULL;
    while (-1 != getline(&bufferPtr, &bufferSize, inputStream))
    {
        Node* temp = head;
        head = malloc(sizeof(Node));
        head->data = bufferPtr;
        head->next = temp;
        bufferPtr = NULL;
        bufferSize = 0;

    }
    if (bufferPtr != NULL)
    {
        free(bufferPtr);
    }
    Node* nodePtr = head;
    while (nodePtr != NULL)
    {
        fprintf(outputStream,"%s", nodePtr->data);
        Node* deleteMe = nodePtr;
        nodePtr = nodePtr->next;
        free(deleteMe->data);
        free(deleteMe);
    }

    // Closing file streams
    if (inputStream != stdin)
    {
        fclose(inputStream);
    }
    if (outputStream != stdout)
    {
        fclose(outputStream);
    }
    return 0;
}
