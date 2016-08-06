#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

typedef struct
{
    int* hPtr;
    int sz;
} Heap;

Heap* heap_Alloc(int *array, int size);
void heap_Insert();
void heap_ExtractMin();




#endif // HEAP_H_INCLUDED
