#ifndef HEADERS_LISTS_H
#define HEADERS_LISTS_H

#include "MyLib.h"

#define tail lst->data[0].prev
#define head lst->data[0].next
#define ifree lst->free

typedef struct elem_t
{
    int prev;
    int next;
    int value;
} elem_t;

typedef struct list_t
{
    elem_t *data;
    size_t size;
    size_t capacity;
    int free;
    int err;
} list_t;

typedef struct files_t
{
    const char* input;
    char* output;
    const char* htmlfile;
} files_t;

#endif
