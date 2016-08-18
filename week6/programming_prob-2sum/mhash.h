/*
    Hashing realized using chaining


*/

#ifndef MHASH_H_INCLUDED
#define MHASH_H_INCLUDED

#include <stdlib.h>
#include <memory.h>
#include <limits.h>

#include "Link.h"

typedef struct
{
    Link **p;
    long long int sz;
} MHash;

void insertInt(MHash *mh, long long int n);
int searchInt(MHash *mh, long long int n);

MHash* allocMHash(long long int sz);
void deallocMHash(MHash *mh);

int mHashFunction(MHash *mh, long long int n);

#endif // MHASH_H_INCLUDED
