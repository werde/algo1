#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define INPUT_FILE "IntegerArray.txt"
#define INPUT_SIZE 100000

int readInput(FILE* f, int** pp);
void recursive(int* p, int size);
void merge(int* f, int* s, int size1, int size2);

unsigned long long int inversions = 0;

int main()
{
    FILE* f;
    f = fopen(INPUT_FILE, "r");

    int* p = 0;
    int size = 0;
    size = readInput(f, &p);

    recursive(p, size);
    /*
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%d\n", p[i]);
    }
    */

    printf("Number of inversions - %llu\n", inversions);
    return 0;
}

int readInput(FILE* f, int** pp)
{
    char buf[90];
    int bufInt, index = 0;

    int size = 0;
    while ( fgets(buf, sizeof(buf), f) != NULL )
    {
        //printf("%d\n", bufInt);
        size++;
    }

    *pp = malloc(sizeof(int)*size);
    printf("input size - %d\n", size);

    rewind(f);
    while ( fgets(buf, sizeof(buf), f) != NULL )
    {
        bufInt = atoi(buf);
        //printf("%d\n", bufInt);
        (*pp)[index] = bufInt;
        index++;
    }

    return size;
}

void recursive(int* p, int size)
{
    int offset1, offset2;

    if (size < 2)
        return;

    if (size%2 == 0)
    {
        offset2 = offset1 = size/2;
    } else
    {
        offset1 = size/2;
        offset2 = 1 + size/2;
    }

    //printf("offset %d %d %d \n", size, offset1, offset2);

    recursive(p, offset1);
    recursive(p + offset1, offset2);
    merge(p, p+offset1, offset1, offset2);
}

//pohoje na pravdu
void merge(int* f, int* s, int size1, int size2)
{
    int i = 0;
    int size = size1 + size2;
    int* a = f;
    int* b = s;
    int* merged = malloc((size)*sizeof(int));

    for (i = 0; i < size; i++)
    {
        if (*a < *b)
        {
            merged[i] = *a;
            a++;
        } else
        {
            inversions += (f + size1 - a);    /*  calculate inversions */

            merged[i] = *b;
            b++;
        }

        /* if at end of the first array */
        if (a >= f + size1)
        {
            memcpy(merged + i + 1, b, (s + size2 - b)*sizeof(int));
            break;
        }

        /* if at end of the second array */
        if (b >= s + size2)
        {
            memcpy(merged + i + 1, a, (f + size1 - a)*sizeof(int));
            break;
        }
    }

    /* cope merged array over existing */
    memcpy(f, merged, size*sizeof(int));
    free(merged);
}
