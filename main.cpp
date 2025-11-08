#include "Lists.h"

#define tail lst -> data[0].prev
#define head lst -> data[0].next
#define ifree lst -> free
#define SIZEOFMYLIST 1

int main()
{  
    list_t lst1;
    ListInit(&lst1, SIZEOFMYLIST);
    ListProcess(&lst1);
    ListDump(&lst1, "graph.txt");
    ListDestroy(&lst1);
    PRINT(PURPLE"finish\n"WHITE);
    return 0;
}

int ListInit(list_t *lst, size_t capacity)
{
    lst -> data = (elem_t* ) calloc(capacity + 1, sizeof (elem_t));
    lst -> capacity = capacity + 1;
    lst -> size = 0;
    tail = head = 0;
    lst -> data[0].value = CANARY1;
    ifree = 1;
    for (size_t i = 1; i < lst -> capacity; i++) {
        lst -> data[i].prev = -1;
        lst -> data[i].value = POISON;
        lst -> data[i].next = (int)i + 1;
    }
    lst -> data[lst -> capacity - 1].next = 0;
    return OK;
}

int TxtGenerate(list_t *lst, const char* inputfile)
{
    FILE* fp = fopen(inputfile, "w");
    fprintf(fp, "digraph {\n");
    fprintf(fp, "inf [shape = rect; color = blue; label = \"head = %d\ntail = %d\nfree = %d\nsize = %lu\ncapacity = %lu\"]\n", head, tail, lst -> free, lst -> size, lst -> capacity);
    for (size_t i = 0; i < lst -> capacity; i++) {
        if (lst -> data[i].value == POISON) {CREATE_FREEBLOCK; CREATE_ARROW}
        else {CREATE_BLOCK; CREATE_ARROW}
    }
    fprintf(fp, "}\n");
    fclose(fp);
    return 0;
}

int PngGenerate(const char* inputfile)
{
    CleanBuff();
    char str[STRSIZE] = "";
    char outputfile[STRSIZE / 10] = "";
    printf("Output file name: ");
    scanf("%9s", outputfile);
    sprintf(str, "dot %s -T png -o pictures/%s.png", inputfile, outputfile);
    PRINT("%s\n", str);
    system(str);
    return OK;
}

int ListDump(list_t *lst, const char* inputfile)
{
    TxtGenerate(lst, inputfile);
    PngGenerate(inputfile);
    return OK;
}

int ListInsert(list_t *lst, int ind, int in)
{
    lst -> size++;
    int currnext = lst -> data[ind].next;
    int currnextfree = lst -> data[ifree].next;
    
    int into = ifree;

    if (ind == 0) {head = into;}
    if (ind == tail) {tail = into;}
    
    lst -> data[ind].next = into;
    lst -> data[currnext].prev = into;
    
    lst -> data[into].prev = (int)ind;
    lst -> data[into].value = in;
    lst -> data[into].next = currnext;

    PRD(ifree);
    PRD(currnextfree); 
    if (currnextfree == 0) {ifree = ListRealloc(lst);}
    else {ifree = currnextfree;}

    PRINT("inserted\n");
    return into;
}

int ListRealloc(list_t *lst)
{
    size_t currcapacity = lst -> capacity;
    PRD(lst -> data[lst -> capacity - 1].value);
    PRU(lst -> capacity);
    PRU(lst -> size);
    
    (lst -> capacity) *= 2;
    PRU(lst -> capacity);
    lst -> data = (elem_t* ) realloc(lst -> data, (lst -> capacity) * sizeof(elem_t));
    if (!lst -> data) {PRINT("WRONG REALLOC\n");}
    for (size_t i = currcapacity; i < lst -> capacity; i++) {
        lst -> data[i].prev = - 1;
        lst -> data[i].value = POISON;
        lst -> data[i].next = (int)i + 1;
    }
    lst -> data[lst -> capacity - 1].next = 0;

    return (int)currcapacity;
}

int ListDelete(list_t *lst, int index)
{
    lst -> data[index].value = POISON;
    lst -> data[lst -> data[index].prev].next = lst -> data[index].next;
    lst -> data[lst -> data[index].next].prev = lst -> data[index].prev;
    lst -> data[index].prev = -1;
    lst -> data[index].next = ifree;
    ifree = ifree < index ? ifree : index;                              // ??  
    lst -> size--;
    PRINT("deleted\n");
    return OK;
}

int ListProcess(list_t *lst)
{
    int v = 0;  //value
    char w = '\0';  //wish
    int d = 0;  //dest
    printf(YELLOW "Type \"i\", index and number to insert it or \"d\" and index to delete it.\n" WHITE);
    while (scanf("%c%d%d", &w, &d, &v) == 3) {        
        if (w == 'i') {ListInsert(lst, d, v);}
        else if (w == 'd') {ListDelete(lst, d);}
        else if (w == 'q') {break;}
        else printf("Try again.\n");
        CleanBuff();
    }
    return OK;
}

int ListDestroy(list_t *lst)
{
    free(lst -> data);
    return 0;
}

int CleanBuff()
{
    while (getchar() != '\n');
    return OK;
}
