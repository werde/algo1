#include "heap.h"

void swapInt(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int getParentIndex(int index)
{
    if (index % 2)
        return (index/2 - 1);

    return (index/2);
}

Heap* heap_Alloc(int *array, int size)
{
    int i;
    Heap* h;

    h = malloc(sizeof(Heap));

    h->hPtr = malloc(sizeof(int)*size);

    for (i = 0; i < size; i++)
    {
        heap_Insert(h, array[i]);
    }

    return h;
};

void heap_Insert(Heap *heap, int val)
{
    int index = heap->sz;

    heap->hPtr[index] = val;
    (heap->sz)++;

    int temp = getParentIndex(index);
    while ((heap->hPtr[temp] > heap->hPtr[index]) && (index > 0))
    {
        swapInt(heap->hPtr+temp, heap->hPtr+index);
        index = temp;
        temp = getParentIndex(index);
    }
};

void heap_ExtractMin()
{

};
