#include "mheap.h"

MHeap* allocMHeap(int sz)
{
    MHeap *mh ;
    mh = malloc(sizeof(MHeap));

    mh->val = malloc(sizeof(int)*sz);
    mh->sz = 0;

    return mh;
};

void insertMin(MHeap *mh, int n)
{
    if (mh->sz == 0)
    {
        mh->val[0] = n;
        mh->sz++;
        return;
    }

    mh->val[mh->sz] = n;

    int *targetPtr;
    int *parentPtr;
    targetPtr =  mh->val + mh->sz;
    parentPtr = mh->val + ((mh->sz + 1)/2 - 1);

    while ((*parentPtr > *targetPtr) && (parentPtr < targetPtr ) && (parentPtr >= mh->val))
    {
        swapInt(parentPtr, targetPtr);
        targetPtr = parentPtr;
        parentPtr = mh->val + ((targetPtr - mh->val + 1)/2 - 1);
    }

    mh->sz++;
};

void insertMax(MHeap *mh, int n)
{
    if (mh->sz == 0)
    {
        mh->val[0] = n;
        mh->sz++;
        return;
    }
    mh->val[mh->sz] = n;

    int *targetPtr;
    int *parentPtr;
    targetPtr =  mh->val + mh->sz;
    parentPtr = mh->val + ((mh->sz + 1)/2 - 1);

    while ((*parentPtr < *targetPtr) && (parentPtr < targetPtr ) && (parentPtr >= mh->val))
    {
        swapInt(parentPtr, targetPtr);
        targetPtr = parentPtr;
        parentPtr = mh->val + ((targetPtr - mh->val + 1)/2 - 1);
    }

    mh->sz++;
};

void insertNum()
{
       //todo general inserts
};

int extractMin(MHeap* mh)
{
    if (mh->sz < 1)
        return 0;

    int min = mh->val[0];

    mh->val[0] = mh->val[mh->sz-1];

    int *targetPtr;
    targetPtr = mh->val;
    int *childPtrLeft;
    childPtrLeft = mh->val + 1;
    int *childPtrRight;
    childPtrRight = mh->val + 2;

    while (((*targetPtr > *childPtrLeft) || (*targetPtr > *childPtrRight)) //it' less more than less or right child
           && (targetPtr < (mh->val + mh->sz)))   //can't pass array's last element
    {
        if ((*childPtrLeft < *childPtrRight) && (childPtrLeft < mh->val + mh->sz))
        {
            swapInt(targetPtr, childPtrLeft);
            targetPtr = childPtrLeft;
        }
        else if ((*childPtrLeft > *childPtrRight) && (childPtrRight < mh->val + mh->sz))
        {
            swapInt(targetPtr, childPtrRight);
            targetPtr = childPtrRight;
        }
        else
        {
            break;
        }
        int delta = targetPtr - mh->val + 1;
        childPtrLeft = mh->val + (delta*2 - 1);
        childPtrRight = mh->val + (delta*2);
    }

    mh->sz--;
    return min;
};

int extractMax(MHeap* mh)
{
    if (mh->sz < 1)
        return 0;

    int max = mh->val[0];

    mh->val[0] = mh->val[mh->sz-1];

    int *targetPtr;
    targetPtr = mh->val;
    int *childPtrLeft;
    childPtrLeft = mh->val + 1;
    int *childPtrRight;
    childPtrRight = mh->val + 2;

    while (((*targetPtr < *childPtrLeft) || (*targetPtr < *childPtrRight)) //it' less more than less or right child
           && (targetPtr < (mh->val + mh->sz)))   //can't pass array's last element
    {
        if ((*childPtrLeft > *childPtrRight) && (childPtrLeft < mh->val + mh->sz))
        {
            swapInt(targetPtr, childPtrLeft);
            targetPtr = childPtrLeft;
        }
        else if ((*childPtrLeft < *childPtrRight) && (childPtrRight < mh->val + mh->sz))
        {
            swapInt(targetPtr, childPtrRight);
            targetPtr = childPtrRight;
        }
        else
        {
            break;
        }
        int delta = targetPtr - mh->val + 1;
        childPtrLeft = mh->val + (delta*2 - 1);
        childPtrRight = mh->val + (delta*2);
    }

    mh->sz--;
    return max;
};

void swapInt(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void swapParent(MHeap* mh, int *ip)
{
    int index;
    int parentIndex;

    index = ip - mh->val;
    parentIndex = (index + 1)/2 - 1;

    if (parentIndex < 0)
        return;

    swapInt(mh->val + index, mh->val + parentIndex);
}
