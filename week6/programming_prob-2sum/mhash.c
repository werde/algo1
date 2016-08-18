#include "mhash.h"

void insertInt(MHash *mh, long long int n)
{
    //find position in hash array
    int pos = mHashFunction(mh, n);

    //make Link out of int
    Link *l = malloc(sizeof(Link));
    l->key = n;
    l->prev = 0;
    l->next = 0;

    //insert Link
    if (mh->p[pos] == 0)
    {
        mh->p[pos] = l;
    } else
    {
        Link *tempLink;
        tempLink = mh->p[pos];

        while (tempLink->next != 0)
            tempLink = tempLink->next;

        tempLink->next = l;
        l->prev = tempLink;
    }
};

int searchInt(MHash *mh, long long int n)
{
    int result = 0;
    int pos = mHashFunction(mh, n);

    if (mh->p[pos] == 0)
        return 0;
    //printf("%ld", n);

    if (mh->p[pos] > 0)
    {
        Link *tempLink;
        tempLink = mh->p[pos];

        do
        {
            if (tempLink->key == n)
                result++;

            tempLink = tempLink->next;

        } while (tempLink != 0);
        return result;
    }

    return 0;
};

MHash* allocMHash(long long int sz)
{
    long long int i;
    MHash *mh = malloc(sizeof(MHash));

    mh->p = malloc(sizeof(Link*)*sz);
    mh->sz = sz;

    for (i = 0; i < mh->sz; i++)
    {
        mh->p[i] = 0;
    }

    return mh;
};

void deallocMHash(MHash *mh)
{
    free(mh->p);
    free(mh);
};

int mHashFunction(MHash *mh, long long int n)
{

    long long val;
    val = (n > 0) ? n%mh->sz : -1 * n%mh->sz;

    if (val > INT_MAX)
        exit(1);

    return (int) val;
};
