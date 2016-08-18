/*
    Answer is 427
    execution time : 2243.410 s
    TODO: use sorted array
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "mhash.h"

#define INPUT_FILE "algo1-programming_prob-2sum.txt"
#define TEST_FILE "test.txt"
#define TEST 1

#define LOWER_T -10000
#define UPPER_T 10000

#define HASH_SIZE_FACTOR 1  //Hash array size = size of input times HASH_SIZE_FACTOR

MHash *readInput(long long int **arrp, int *arrSz);
int twoSum(MHash *mh, long long int *arr, int t, int arrSz);

int main()
{
    int i;
    MHash *mh;
    long long int* arr = 0;
    int arrSz = 0;

    mh = readInput(&arr, &arrSz);

    int t_num = 0;
    for (i = LOWER_T; i <= UPPER_T; i++)
    {
        t_num += twoSum(mh, arr, i, arrSz);
    }

    //Print out hash array
    /*
    for (i = 0; i < mh->sz; i++)
    {
        if (mh->p[i] > 0)
        {
            printf("Hash position : %d \n", i);

            Link *tempLink;
            tempLink = mh->p[i];

            do
            {
                printf("\t value %ld\n", tempLink->key);

                tempLink = tempLink->next;
            } while (tempLink != 0);
        }
    }
    */

    printf("[!] Answer is   %d\n", t_num);

    deallocMHash(mh);

    return 0;
}

int twoSum(MHash *mh, long long int *arr, int t, int arrSz)
{
    if (t%100 == 0)
        printf("Looking up %d \n", t);

    int i;
    int result = 0;
    long long int s; //value searching for

    for (i = 0; i < arrSz; i++)
    {
        long long int curVal = arr[i];
        s = t - curVal;
        //printf("%d   %ld  %ld\n", t, curVal, s);
        if (curVal != s)
        {
            result += searchInt(mh, s);
        }

        if (result > 0) //only need to find a pair once
            break;
    }

    if (result > 0)
    {
        //printf("found %d %d %d\n", t, arr[i], s);
        return 1;
    }

    return 0;
};

MHash *readInput(long long int **arrp, int *arrSz)
{
    FILE *f;
    MHash *mh;
#if TEST
    f = fopen(TEST_FILE, "r");
#else
    f = fopen(INPUT_FILE, "r");
#endif // TEST

    //init hash size
    char buffer[200];
    int size = 0;
    while (fgets(buffer, sizeof(buffer), f))
        size++;
    printf("[!] Size of input - %d\n", size);

    *arrSz = size;
    mh = allocMHash(size*HASH_SIZE_FACTOR);
    *arrp = malloc(sizeof(long long int)*size);

    rewind(f);

    //fill with values
    long long int val;
    int i;
    i = 0;
    while (fgets(buffer, sizeof(buffer), f))
    {
        val = atoll(buffer);
        (*arrp)[i] = val;
        insertInt(mh, val);

        i++;
    }

    fclose(f);
    return mh;
}
