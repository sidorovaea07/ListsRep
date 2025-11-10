#include "../headers/ListFuncs.h"
#include "../headers/FileFuncs.h"
extern char out[STRSIZE];

int main()
{  
    list_t lst1;
    ListInit(&lst1, SIZEOFMYLIST);
    ListProcess(&lst1);
    ListDump(&lst1, "graph.txt");
    HtmlGenerate(out, "my.html", &lst1);
    ListDestroy(&lst1);
    FINISH
    return 0;
}