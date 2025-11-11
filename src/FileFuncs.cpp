#include "../headers/FileFuncs.h"
char out[STRSIZE] = "";

int CleanBuff()
{
    while (getchar() != '\n');
    return OK;
}

int OutputName()
{
    CleanBuff();
    char name[STRSIZE / 10] = "";
    printf("Output file name: ");
    scanf("%9s", name);
    sprintf(out, "pictures/%s.png", name);
    PRP(out);
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

int PngGenerate(const char* inputfile, const char* outputfile)
{
    char str[STRSIZE] = "";
    sprintf(str, "dot %s -T png -o %s", inputfile, outputfile);
    PRINT("%s\n", str);
    system(str);
    return OK;
}

int HtmlGenerate(const char* pngfile, const char* output, list_t *lst)
{
    FILE *fp = fopen(output, "w");
    fprintf(fp, "<pre>\n" "<h3> LIST %p DUMP </h3>\n", lst);
    fprintf(fp, "head = %d\ntail = %d\nfree = %d\nsize = %lu\ncapacity = %lu\n\n", head, tail, lst -> free, lst -> size, lst -> capacity);
    fprintf(fp, "<h4> prev:\tvalue:\t\tnext:\t </h4> \n");
    for (size_t i = 0; i < lst -> capacity; i++) {
        fprintf(fp, "%d\t%10d\t%d\n", lst -> data[i].prev, lst -> data[i].value, lst -> data[i].next);
    }
    fprintf(fp, "<h2> IMAGE: </h2> \n<img src = %s width = 500px> \n", pngfile);
    fclose(fp);
    return OK;
}

int ListDump(list_t *lst, const char* inputfile, const char* htmlfile)
{
    TxtGenerate(lst, inputfile);
    OutputName();
    PngGenerate(inputfile, out);
    HtmlGenerate(out, htmlfile, lst);
    return OK;
}