#ifndef STACKSHEADER
#define STACKSHEADER

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#define WHITE "\033[0m"
#define GREY "\033[90m"
#define BLACKFONE "\033[40m"
#define RED "\033[91m"
#define BLUE "\033[36m"
#define YELLOW "\033[33m"
#define PURPLE "\033[35m"

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
#define STRSIZE 100

#define DEBUG

#ifdef DEBUG
    #define PRINT(fmt, ...) printf(YELLOW fmt WHITE, ##__VA_ARGS__ )
    #define PRP(x) printf(PURPLE #x " pointer: %p\n" WHITE, (x))
    #define PRD(x) printf(BLUE #x " = %d\n" WHITE, (x))
    #define PRU(x) printf(BLUE #x " = %lu\n" WHITE, (x))
    #define PRTF(x) printf(PURPLE "print to file returned %d\n" WHITE, (x))
#else
    #define PRP(x)
    #define PRD(x)
    #define PRU(x)
    #define PRTF(x)
    #define PRINT(fmt, ...)                                
#endif

typedef const int canary;
const int POISON = 0xdeadbee;
canary CANARY1 = 0xc0cca;
canary CANARY2 = 0x5055a;

#define OK 0

typedef struct elem_t
{
    int prev;
    int next;
    int value;
} elem_t;

typedef struct list_t
{
    elem_t *data;
    size_t size;
    size_t capacity;
    int free;
    int ERR;
} list_t;

int ListInit(list_t *lst, size_t capacity);
int ListProcess(list_t *lst);
int CleanBuff();
// int ListVerify(list_t *lst);
int TxtGenerate(list_t *lst, const char* inputfile);
int PngGenerate(const char* inputfile);
int ListDump(list_t *lst, const char* inputfile);

int ListInsert(list_t *lst, int ind, int in);
int ListDelete(list_t *lst, int index);

int ListRealloc(list_t *lst);
int ListDestroy(list_t *lst);

#endif
