#ifndef HEADERS_DUMP_H
#define HEADERS_DUMP_H

#include "Lists.h"

typedef struct files_t
{
    const char* input;
    char* output;
    const char* htmlfile;
} files_t;

int TxtGenerate(list_t *lst, files_t *files);
int PngGenerate(files_t *files);
int ListDump(list_t *lst, files_t *files);
int HtmlGenerate(list_t *lst, files_t *files);
int OutputName(files_t *files);
int CleanBuff();
int FilesInit(files_t *files, const char* input, char* output, const char* htmlfile);
#endif
