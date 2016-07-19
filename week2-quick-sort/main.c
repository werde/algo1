#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

#define INPUT_FILE "QuickSort.txt"
#define INPUT_TEST_FILE "test.txt"
#define FIRST_ELEM_PIVOT 1
#define LAST_ELEM_PIVOT 2
#define MEDIAN_ELEM_PIVOT 3
#define TEST 1

int comparisonsFirstElement = 0;
int comparisonsFinalElement = 0;
int comparisonsMedianOfThree = 0;

int readInput(FILE* f, int** pp);
void swap(int* a, int* b);
int* median(int *fp, int *sp, int *tp);
void partition(int* array, const int size, int pivotMode);

int main()
{
    int size = 0;
    int *p, *p1, *p2, *p3;

    FILE* f;

#if TEST
    f = fopen(INPUT_TEST_FILE, "r");
#else
    f = fopen(INPUT_FILE, "r");
#endif
    size = readInput(f, &p);
    printf("[!] Input size - %d \n", size);

    p1 = malloc(sizeof(int)*size);
    p2 = malloc(sizeof(int)*size);
    p3 = malloc(sizeof(int)*size);

    memcpy(p1, p, sizeof(int)*size);
    memcpy(p2, p, sizeof(int)*size);
    memcpy(p3, p, sizeof(int)*size);

    partition(p1, size, FIRST_ELEM_PIVOT);
    partition(p2, size, LAST_ELEM_PIVOT);
    partition(p3, size, MEDIAN_ELEM_PIVOT);

    printf("\n");

    printf("first - %d; final - %d; median - %d;\n", comparisonsFirstElement, comparisonsFinalElement, comparisonsMedianOfThree);

    return 0;
}


void swap(int* a, int* b)
{
    int temp = 0;
    temp = *b;
    *b = *a;
    *a = temp;
}

int* median(int *fp, int *sp, int *tp)
{
    int f = *fp;
    int s = *sp;
    int t = *tp;

    if ((( f < s ) && ( f > t )) || (( f > s ) && (f < t )))    //median first
        return fp;
    if ((( s < f ) && ( s > t )) || (( s > f ) && ( s < t )))   //median second
        return sp;
    if ((( t > f ) && ( t < s )) || (( t < f ) && ( t > s )))   //median third
        return tp;

    if (f == s)
        return fp;

    if (f == t)
        return fp;

        return sp;
}

/* Pivot is always first element (array[0], *array) */
void partition(int* array, const int size, int pivotMode)
{
    if (size < 2)
        return;

    int i, j;
    int *pivot;
    pivot = 0;

    /* Pivot */
    if (pivotMode == FIRST_ELEM_PIVOT)
    {
        comparisonsFirstElement += size - 1;
        pivot = array;
    }
    if (pivotMode == LAST_ELEM_PIVOT)
    {
        comparisonsFinalElement += size - 1;
        pivot = array + size - 1;
    }
    if (pivotMode == MEDIAN_ELEM_PIVOT)
    {
        comparisonsMedianOfThree += size - 1;

        int offset = 0;
        if (size%2 == 0)
        {
            offset = size/2 - 1;
        } else
        {
            offset = size/2;
        }

        //printf("f %d s %d t %d \n", *array, *(array + offset), *(array + size - 1));
        pivot = median(array, array + offset, array + size - 1);
        //printf("median %d \n", *pivot);
    }

    if (pivot == 0)
    {
        printf("0 pivot");
        return;
    }

    swap(pivot, array); // swap first elements with given pivot

    /* Partition */
    i = j = 1;
    while ( j < size  )
    {
        if ( array[j] < array[0])   // first elem pivot
        {
            swap(array + j, array + i);
            i++;
        } else
        {
            /* Do nothing */
        }
        j++;
    }
    swap(array, array + i - 1);

    partition(array, i - 1, pivotMode);
    partition(array + i, size - i, pivotMode);
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
