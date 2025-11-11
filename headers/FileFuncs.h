#ifndef FILEFUNCS
#define FILEFUNCS

#include "Lists.h"

#define CREATE_FREEBLOCK                                                                                                                                                \
        fprintf(fp, "\t %lu [shape = Mrecord; style = filled; fillcolor = pink2; color = yellow; label = \"{ind = %lu | prev = %d | value = %d | next = %d}\"]\n",  \
        i, i, lst -> data[i].prev, lst -> data[i].value, lst -> data[i].next);

#define CREATE_BLOCK                                                                                                                                                \
        fprintf(fp, "\t %lu [shape = Mrecord; style = filled; fillcolor = pink2; color = blue; label = \"{ind = %lu | prev = %d | value = %d | next = %d}\"]\n",  \
        i, i, lst -> data[i].prev, lst -> data[i].value, lst -> data[i].next);

#define CREATE_ARROW                                                                                        \
        if (lst -> data[i]. prev == -1) fprintf(fp, "\t%lu->%d [color = yellow]\n", i, lst -> data[i].next); \
        else if (i == (size_t)lst -> data[lst -> data[i].next].prev)                                         \
            fprintf(fp, "\t%lu->%d [dir = none; color = sienna4]\n", i, lst -> data[i].next);               \
        else {                                                                                              \
            fprintf(fp, "\t%lu->%d [color = red]\n", i, lst -> data[i].prev);                              \
            fprintf(fp, "\t%lu->%d [color = green]\n", i, lst -> data[i].next);                            \
        }

int TxtGenerate(list_t *lst, const char* inputfile);
int PngGenerate(const char* inputfile, const char* outputfile);
int ListDump(list_t *lst, const char* inputfile, const char* htmlfile);
int HtmlGenerate(const char* pngfile, const char* output, list_t *lst);
int OutputName();

#endif