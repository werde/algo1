#include <stdio.h>
#include <stdlib.h>

#include "mheap.h"

#define INPUT_FILE "median.txt"
#define TEST_FILE "test.txt"
#define TEST 0

void readInput(int **arrp, int *szp);
long long int median(MHeap* mhmin, MHeap* mhmax, int* values, int sz);

int main()
{
    int i;
    int *arr;
    int size;

    readInput(&arr, &size);
    printf("[!] Size of input - %d\n", size);

    //heaps init
    MHeap *mhmin;
    MHeap *mhmax;
    mhmin = allocMHeap(size);
    mhmax = allocMHeap(size);

    long long int med;
    med = median(mhmin, mhmax, arr, size);

    printf("[!] result - %lld\n", med);

    return 0;
}

long long int median(MHeap* mhmin, MHeap* mhmax, int* values, int sz)
{

    int i, cur;
    long long int result = 0;

    insertMax(mhmax, values[0]);  //init
    result += values[0]; //very first median

    for (i = 1; i < sz; i++)
    {
        cur = values[i];

        //insert current value
        if (cur < mhmax->val[0])
        {
            insertMax(mhmax, cur);
        }
        else
        {
            insertMin(mhmin, cur);
        }

        //balance heaps
        if (mhmax->sz > mhmin->sz + 1)
        {
            int temp = extractMax(mhmax);
            insertMin(mhmin, temp);
        };
        if(mhmin->sz > mhmax->sz + 1)
        {
            int temp = extractMin(mhmin);
            insertMax(mhmax, temp);
        };

        //calcualate sum
        if (mhmax->sz == mhmin->sz)
        {
            result += mhmax->val[0];
        }
        else if (mhmax->sz > mhmin->sz)
        {
            result += mhmax->val[0];
        }
        else if (mhmax->sz < mhmin->sz)
        {
            result += mhmin->val[0];
        }
    }

    return result;
};

void readInput(int **arrp, int *szp)
{
    FILE *f;
#if TEST
    f = fopen(TEST_FILE, "r");
#else
    f = fopen(INPUT_FILE, "r");
#endif // TEST

    char buffer[256];
    int size = 0;
    while (fgets(buffer, sizeof(buffer), f))
        size++;

    *arrp = malloc(sizeof(int)*size);
    *szp = size;

    rewind(f);

    int i = 0;
    while (fgets(buffer, sizeof(buffer), f))
    {
        (*arrp)[i] = atoi(buffer);
        i++;
    }
};
