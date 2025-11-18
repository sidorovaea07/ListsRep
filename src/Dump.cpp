#include "Dump.h"
#include <stdlib.h>

#define MAKEDIR(name) do {                                        \
    char* iterate = (char *)calloc(STRSIZE, sizeof(char));        \
    sprintf(iterate, "touch logs/%s", name);                      \
    system(iterate);                                              \
    free(iterate);                                                \
} while (0);

int FilesInit(files_t *files, const char* input, char* output, const char* htmlfile)
{
    MAKEDIR(input)
    MAKEDIR(output)
    MAKEDIR(htmlfile)    
    files->input = input;
    files->output = output;
    files->htmlfile = htmlfile;
    return OK;
}

int CleanBuff()
{
    while (getchar() != '\n');
    return OK;
}

int OutputName(files_t *files)
{
    CleanBuff();
    char name[STRSIZE / 10] = "";
    printf("Output file name: ");
    scanf("%9s", name);
    files->output = (char* )calloc(STRSIZE, sizeof(char));
    sprintf(files->output, "pictures/%s.png", name);
    PRP(files->output);
    PRINT("%s\n", files->output);
    return OK;
}

int TxtGenerate(list_t *lst, files_t *files)
{
    FILE* fp = fopen(files->input, "w");
    fprintf(fp, "digraph {\n");
    fprintf(fp, "rankdir = LR;\n");
    fprintf(fp, "inf [shape = rect; color = blue; label = \"head = %d\ntail = %d\nfree = %d\nsize = %lu\ncapacity = %lu\"]\n", head, tail, lst->free, lst->size, lst->capacity);
    for (size_t i = 0; i < lst->capacity; i++) {
        if (lst->data[i].value == POISON)
            fprintf(fp, "\t %lu [shape = Mrecord; style = filled; fillcolor = pink2; color = yellow; label = \"ind = %lu | prev = %d | value = %d | next = %d\"]\n", i, i, lst -> data[i].prev, lst -> data[i].value, lst -> data[i].next);
        else
            fprintf(fp, "\t %lu [shape = Mrecord; style = filled; fillcolor = pink2; color = blue; label = \"ind = %lu | prev = %d | value = %d | next = %d\"]\n", i, i, lst -> data[i].prev, lst -> data[i].value, lst -> data[i].next);
        
        if (lst -> data[i]. prev == -1) 
            fprintf(fp, "\t%lu->%d [color = yellow]\n", i, lst -> data[i].next);
        else if (i == (size_t)lst -> data[lst -> data[i].next].prev)
            fprintf(fp, "\t%lu->%d [dir = none; color = sienna4]\n", i, lst -> data[i].next);
        else {
            fprintf(fp, "\t%lu->%d [color = red]\n", i, lst -> data[i].prev);
            fprintf(fp, "\t%lu->%d [color = green]\n", i, lst -> data[i].next);
        }    
    }
    fprintf(fp, "}\n");
    fclose(fp);
    return 0;
}

int PngGenerate(files_t *files)
{
    char str[STRSIZE] = "";
    sprintf(str, "dot %s -T png -o %s", files->input, files->output);
    PRD(system(str));
    return OK;
}

int HtmlGenerate(list_t *lst, files_t *files)
{
    FILE *fp = fopen(files->htmlfile, "w");
    fprintf(fp, "<pre>\n" "<h3> LIST %p DUMP </h3>\n", lst);
    fprintf(fp, "head = %d\ntail = %d\nfree = %d\nsize = %lu\ncapacity = %lu\n\n", head, tail, lst->free, lst->size, lst->capacity);
    fprintf(fp, "<h4> prev:\tvalue:\t\tnext:\t </h4> \n");
    for (size_t i = 0; i < lst->capacity; i++) {
        fprintf(fp, "%d\t%10d\t%d\n", lst->data[i].prev, lst->data[i].value, lst->data[i].next);
    }
    fprintf(fp, "<h2> IMAGE: </h2> \n<img src = %s width = 500px> \n", files->output);
    fclose(fp);
    return OK;
}

int ListDump(list_t *lst, files_t *files)
{
    TxtGenerate(lst, files);
    OutputName(files);
    PngGenerate(files);
    HtmlGenerate(lst, files);
    return OK;
}