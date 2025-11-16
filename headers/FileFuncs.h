#ifndef HEADERS_FILEFUNCS_H
#define HEADERS_FILEFUNCS_H
#include <stdlib.h>

#include "Lists.h"

int TxtGenerate(list_t *lst, files_t *files);
int PngGenerate(files_t *files);
int ListDump(list_t *lst, files_t *files);
int HtmlGenerate(list_t *lst, files_t *files);
int OutputName(files_t *files);
int CleanBuff();

#endif