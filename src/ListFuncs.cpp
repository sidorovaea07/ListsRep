#include "ListFuncs.h"
#include "Dump.h"
#include <stdlib.h>

int ListInit(list_t *lst, size_t capacity)
{
    lst->data = (elem_t* ) calloc(capacity + 1, sizeof (elem_t));
    lst->capacity = capacity + 1;
    lst->size = 0;
    tail = head = 0;
    lst->data[0].value = CANARY1;
    ifree = 1;
    
    if (lst->capacity - 1 > 1) {
        for (size_t i = 1; i < lst->capacity; i++) {
            lst->data[i].prev = -1;
            lst->data[i].value = POISON;
            lst->data[i].next = (int)i + 1;
        }    
        lst->data[lst->capacity - 1].next = 0;
    }
    return OK;
}

int ListInsert(list_t *lst, int ind, int in)
{
    if (ind >= (int)lst->capacity || ind < 0 || lst->data[ind].prev == -1) {
        printf("You can't insert after this index!\n"); 
        return OK;
    }
    lst->size++;
    if (ifree == (int)lst->capacity) {
        ListRealloc(lst);
    }
    int currnext = lst->data[ind].next;
    int currnextfree = lst->data[ifree].next;
    int into = ifree;
    PRD(ifree); PRU(lst->capacity);
    
    if (ind == 0) {
        head = into;
    }
    if (ind == tail) {
        tail = into;
    }
    
    lst->data[ind].next = into;
    lst->data[currnext].prev = into;
    
    lst->data[into].prev = (int)ind;
    lst->data[into].value = in;
    lst->data[into].next = currnext;

    PRD(ifree);
    PRD(currnextfree);

    if (currnextfree == 0) {
        ifree = ListRealloc(lst);
    }
    else {
        ifree = currnextfree;
    }

    PRINT("inserted\n");
    return into;
}

int ListRealloc(list_t *lst)
{
    size_t currcapacity = lst->capacity;
    PRD(lst->data[lst->capacity - 1].value);
    PRU(lst->capacity);
    PRU(lst->size);
    
    (lst->capacity) *= 2;
    PRU(lst->capacity);
    lst->data = (elem_t* ) realloc(lst->data, (lst->capacity) * sizeof(elem_t));
    if (!lst->data) {
        PRINT("WRONG REALLOC\n");
    }
    for (size_t i = currcapacity; i < lst->capacity; i++) {
        lst->data[i].prev = - 1;
        lst->data[i].value = POISON;
        lst->data[i].next = (int)i + 1;
    }
    lst->data[lst->capacity - 1].next = 0;

    return (int)currcapacity;
}

int ListDelete(list_t *lst, int index)
{
    if (index >= (int)lst->capacity || lst->data[index].value == POISON || index == 0) {
        printf("You can't delete this index!\n"); 
        return OK;
    }
    lst->data[index].value = POISON;
    lst->data[lst->data[index].prev].next = lst->data[index].next;
    lst->data[lst->data[index].next].prev = lst->data[index].prev;
    lst->data[index].prev = -1;
    lst->data[index].next = ifree;

    ifree = index;
    lst->size--;
    
    PRINT("deleted\n");
    return OK;
}

int ListProcess(list_t *lst, files_t* files)
{
    int v = 0; char w = '\0'; int d = 0;
    printf(YELLOW "Type:\n\t\"i\", index and number to insert it\n\t\"d\" and index to delete it\n\t\"q\" to quit\n\t\"p\" to print.\n" WHITE);
    while (w = getchar()) {    
        CleanBuff();
        switch (w) {
            case 'i':
                scanf("%d%d", &d, &v);
                ListInsert(lst, d, v);
                break;
            case 'd':
                scanf("%d", &d);  
                ListDelete(lst, d);
                break;
            case 'p':
                PRINT("let's print\n");
                ListDump(lst, files);
                break;
            case 'q':
                break;
            default: 
                printf("Try again.\n");
                break;
        }
        CleanBuff();
    }
    return OK;
}

int ListDestroy(list_t *lst)
{
    free(lst->data);
    return 0;
}