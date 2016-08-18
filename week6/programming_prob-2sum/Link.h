#ifndef LINK_H_INCLUDED
#define LINK_H_INCLUDED

typedef struct Link Link;

struct Link
{
    long long int key;
    Link *prev;
    Link *next;
};

#endif // LINK_H_INCLUDED
