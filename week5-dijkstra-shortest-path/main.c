#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

#define TEST 01
#define TEST_INPUT_FILE "test.txt"
#define INPUT_FILE "dijkstraData.txt"

void readInput();

int main()
{
    readInput();

    printf("Hello world!\n");
    return 0;
}

void readInput()
{
    FILE *f;
#if TEST
    f = fopen(TEST_INPUT_FILE, "r");
#else
    f = fopen(INPUT_FILE, "r");
#endif // TEST

    char buffer[200];
    int size = 0;
    while (fgets(buffer, sizeof(buffer), f))
    {
        printf("%s\n", buffer);
        size++;
    }
    printf("[!] Number of vertices - %d\n", size);
    rewind(f);

    while (fgets(buffer, sizeof(buffer), f))
    {
        char *start;
        int node, n, ln, chRead;

        start = buffer;
        sscanf(buffer, "%d%n", &node, &chRead);
        start += chRead;
        while (sscanf(start, "%d,%d%n", &n, &ln, &chRead) > 0)
        {
            printf ("edge %d %d of length %d\n", node, n , ln);
            start += chRead;
        }
    }
}
