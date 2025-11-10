#ifndef LISTS
#define LISTS

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#define OK 0
#define STRSIZE 100
#define SIZEOFMYLIST 1
typedef const int canary;
const int POISON = 0xdeadbee;
canary CANARY1 = 0xc0cca;

#define WHITE "\033[0m"
#define GREY "\033[90m"
#define BLACKFONE "\033[40m"
#define RED "\033[91m"
#define BLUE "\033[36m"
#define YELLOW "\033[33m"
#define PURPLE "\033[35m"

#define DEBUG

#ifdef DEBUG
    #define PRINT(fmt, ...) printf(YELLOW fmt WHITE, ##__VA_ARGS__ )
    #define PRP(x) printf(PURPLE #x " pointer: %p\n" WHITE, (x))
    #define PRD(x) printf(BLUE #x " = %d\n" WHITE, (x))
    #define PRU(x) printf(BLUE #x " = %lu\n" WHITE, (x))
    #define PRTF(x) printf(PURPLE "print to file returned %d\n" WHITE, (x))
    #define FINISH PRINT(PURPLE"finish\n"WHITE);
#else
    #define PRP(x)
    #define PRD(x)
    #define PRU(x)
    #define PRTF(x)
    #define PRINT(fmt, ...)
    #define FINISH                                
#endif

#define tail lst -> data[0].prev
#define head lst -> data[0].next
#define ifree lst -> free

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

int CleanBuff();

#endif
