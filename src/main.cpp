#include "../headers/ListFuncs.h"
#include "../headers/FileFuncs.h"
extern char out[STRSIZE];

int main()
{  
    list_t lst1;
    ListInit(&lst1, SIZEOFMYLIST);
    ListProcess(&lst1);
    ListDump(&lst1, "graph.txt", "my.html");
    ListDestroy(&lst1);
    FINISH
    return 0;
}