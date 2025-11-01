#include "Lists.h"

#define tail lst -> data[0].prev
#define head lst -> data[0].next
#define ifree lst -> free
#define SIZEOFMYLIST 10

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
    lst -> capacity = capacity;
    tail = 0;
    head = ifree = 1;
    lst -> data[0].value = CANARY1;
    for (size_t i = 1; i < capacity; i++) {
        lst -> data[i].prev = - 1;
        lst -> data[i].value = POISON;
        lst -> data[i].next = (int)i + 1;
    }
    return OK;
}

int TxtGenerate(list_t *lst, const char* inputfile)
{
    FILE* fp = fopen(inputfile, "w");
    fprintf(fp, "digraph {\n");
    fprintf(fp, "Free [shape = rect; color = blue; label = \"free = %d\"]\n", lst -> free);
    for (size_t i = 0; i < lst -> capacity; i++) {
        if (lst -> data[i].value == POISON) CREATE_FREEBLOCK
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
    PRD(system(str));
    return OK;
}

int ListDump(list_t *lst, const char* inputfile)
{
    TxtGenerate(lst, inputfile);
    PngGenerate(inputfile);
    return OK;
}

int ListInsert(list_t *lst, int in)
{
    int i = 0;
    for (i = 1; lst -> data[i].next != 0; i = lst -> data[i].next) {}
    int insert_to = lst -> data[i].next = ifree;
    lst -> data[insert_to].prev = tail;
    tail = ifree;
    ifree = lst -> data[insert_to].next;
    lst -> data[insert_to].value = in;
    lst -> data[insert_to].next = 0;
    PRINT("inserted\n");
    return insert_to;
}

int ListDelete(list_t *lst, int index)
{
    lst -> data[index].value = POISON;
    lst -> data[lst -> data[index].prev].next = lst -> data[index].next;
    lst -> data[lst -> data[index].next].prev = lst -> data[index].prev;
    lst -> data[index].prev = -1;
    lst -> data[index].next = ifree;
    ifree = ifree < index ? ifree : index;                              // ??  
    PRINT("deleted\n");
    return OK;
}

int ListProcess(list_t *lst)
{
    int x = 0;
    char w = '\0';
    printf(YELLOW "Type \"i\" and number to insert it or \"d\" and index to delete it.\n" WHITE);
    while (scanf("%c%d", &w, &x) == 2) {        
        if (w == 'i') {ListInsert(lst, x);}
        else if (w == 'd') {ListDelete(lst, x);}
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
// int ListReallocation(list_t *lst);
// int ListVerify(list_t *lst);