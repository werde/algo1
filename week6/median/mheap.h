#ifndef MHEAP_H_INCLUDED
#define MHEAP_H_INCLUDED

/*  min heap*/

enum HeapType { MAX = 0, MIN = 1 }; // todo init heaps to be max or min heaps

typedef struct
{
    int *val;
    int sz;
} MHeap;

MHeap* allocMHeap(int sz);

void insertMin(MHeap *mh, int n);
void insertMax(MHeap *mh, int n);
void insertNum();   // todo general inserts

int extractMin(MHeap* mh);
int extractMax(MHeap* mh);

void swapInt(int *a, int *b);

#endif // MHEAP_H_INCLUDED
