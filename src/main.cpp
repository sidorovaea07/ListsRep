#include "../headers/ListFuncs.h"
#include "../headers/FileFuncs.h"

int main()
{  
    list_t lst1;
    files_t files1 = {"graph.txt", "", "my.html"};
    ListInit(&lst1, 0);
    ListProcess(&lst1);
    ListDump(&lst1, &files1);
    ListDestroy(&lst1);
    FINISH
    return 0;
}