#ifndef LISTFUNCS
#define LISTFUNCS

#include "Lists.h"

int ListInit(list_t *lst, size_t capacity);
int ListProcess(list_t *lst);
// int ListVerify(list_t *lst);
int ListInsert(list_t *lst, int ind, int in);
int ListDelete(list_t *lst, int index);
int ListRealloc(list_t *lst);
int ListDestroy(list_t *lst);

#endif