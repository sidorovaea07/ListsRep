#ifndef HEADERS_LISTS_H
#define HEADERS_LISTS_H

#include "MyLib.h"
#include "Dump.h"

#define OK 0
#define STRSIZE 100
#define SIZEOFMYLIST 1


#define tail lst->data[0].prev
#define head lst->data[0].next
#define ifree lst->free


const int POISON = 0xdeadbee;

typedef struct elem_t
{
    int prev;
    int next;
#ifdef DOUBLE_VALUES
    double value;
#else
    int value;
#endif
} elem_t;

typedef struct list_t
{
    elem_t *data;
    size_t size;
    size_t capacity;
    int free;
    int err;
} list_t;

#endif
