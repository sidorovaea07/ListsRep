#ifndef STACKSHEADER
#define STACKSHEADER

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
   
#define PRPRINT(x) printf("ProcessorVerify returned " #x"\n"); break;
#define STPRINT(x) printf("StackVerify returned " #x"\n");

#define WHITE "\033[0m"
#define GREY "\033[90m"
#define BLACKFONE "\033[40m"
#define RED "\033[91m"
#define BLUE "\033[36m"
#define YELLOW "\033[33m"
#define PURPLE "\033[35m"

#define DEBUG

#ifdef DEBUG
    #define PRP(x) printf(PURPLE #x " pointer: %p\n" WHITE, (x))
    #define PRD(x) printf(BLUE #x " = %d\n" WHITE, (x))
    #define PRU(x) printf(BLUE #x " = %lu\n" WHITE, (x))
    #define PRTF(x) printf(PURPLE "print to file returned %d\n" WHITE, (x))
#else
    #define PRP(x)
    #define PRD(x)
    #define PRU(x)
    #define PRTF(x)
                                      
#endif

typedef const int canary;
const int POISON = 0xdeadbee;
canary CANARY1 = 0xc0cca;
canary CANARY2 = 0x5055a;

#define SIZEOFMYLIST 5
#define OK 0

typedef struct elem_t
{
    size_t prev;
    size_t next;
    int value;
} elem_t;

typedef struct list_t
{
    elem_t *data;
    size_t size;
    size_t capacity;
    size_t free;
    int ERR;
} list_t;

int ListInit(list_t *lst, size_t capacity);
int ListVerify(list_t *lst);
int TxtGenerate(list_t *lst, const char* inputfile);
int PngGenerate(list_t *lst, const char* inputfile);
int ListDump(list_t *lst, const char* inputfile);

int ListDestroy(list_t *lst);
int ListInsert(list_t *lst, int in);

int ListReallocation(list_t *lst);

#endif
