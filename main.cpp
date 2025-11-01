#include "Lists.h"
#define CREATE_BLOCK                                                                                                                                                \
        fprintf(fp, "\t %lu [shape = Mrecord; style = filled; fillcolor = pink2; color = blue; label = \"{ind = %lu | next = %lu | value = %d | prev = %lu}\"]\n",  \
        i, i, lst -> data[i].next, lst -> data[i].value, lst -> data[i].prev);

#define CREATE_ARROW                                                                                        \
        if (lst -> data[i].next == lst -> data[lst -> data[i].next].prev)                                   \
            fprintf(fp, "\t%lu->%lu [dir = none; color = sienna4]\n", i, lst -> data[i].next);              \
        else {                                                                                              \
            fprintf(fp, "\t%lu->%lu [color = red]\n", lst -> data[i].prev, i);                              \
            fprintf(fp, "\t%lu->%lu [color = green]\n", i, lst -> data[i].next);                            \
        }
#define STRSIZE 100

int main()
{  
    list_t lst1;
    int x = 0;
    ListInit(&lst1, SIZEOFMYLIST);
    // while (scanf("%d", &x) == 1)
    //     ListInsert(&lst1, x);
    ListDump(&lst1, "graph.txt");
    ListDestroy(&lst1);
    printf(PURPLE"finish\n"WHITE);
    return 0;
}

int ListInit(list_t *lst, size_t capacity)
{
    lst -> data = (elem_t* ) calloc(capacity + 1, sizeof (elem_t));
    lst -> capacity = capacity;
    lst -> free = 1;
    lst -> data[0].prev = 0;
    lst -> data[0].value = CANARY1;
    lst -> data[0].next = 0;
    for (size_t i = 1; i < capacity;) {
        lst -> data[i].prev = 0;
        lst -> data[i].value = POISON;
        lst -> data[i].next = ++i;
    }
    return OK;
}

int TxtGenerate(list_t *lst, const char* inputfile)
{
    FILE* fp = fopen(inputfile, "w");
    fprintf(fp, "digraph {\n");
    for (size_t i = 0; i < lst -> capacity; i++) {
        CREATE_BLOCK;
        CREATE_ARROW;
    }
    fprintf(fp, "}\n");
    fclose(fp);
    return 0;
}

int PngGenerate(list_t *lst, const char* inputfile)
{
    char str[STRSIZE] = "";
    char outputfile[STRSIZE / 10] = "";
    printf("Output file name: ");
    scanf("%9s", outputfile);
    sprintf(str, "dot %s -T png -o pictures/%s.png", inputfile, outputfile);
    puts(str);
    PRD(system(str));
    return OK;
}

int ListDump(list_t *lst, const char* inputfile)
{
    TxtGenerate(lst, inputfile);
    PngGenerate(lst, inputfile);
    return OK;
}

int ListInsert(list_t *lst, int in)
{
    size_t free = lst -> free;
    lst -> data[free].value = in;
    lst -> free = lst -> data[free].next;    
    lst -> data[free].next = 0;

    return 0;
}

int ListDestroy(list_t *lst)
{
    free(lst -> data);
    return 0;
}
// int ListReallocation(list_t *lst);
// int ListVerify(list_t *lst);