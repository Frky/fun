
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mem.h"

#define N 500

#define MAX_BLOCK_SIZE   100

typedef struct syr_el {
    char *_block;
    size_t _s;
    char p;
    struct syr_el *_next;
} SYR_EL;

static int nb_malloc;

SYR_EL *add(SYR_EL *syr, char a, char b) {
    char c = a;
    SYR_EL *el = mem_alloc(sizeof(SYR_EL));
    nb_malloc++;
    int j = (rand() % MAX_BLOCK_SIZE) + 1;
    int k;
    el->_s = j;
    el->_block = mem_alloc(j * sizeof(char));
    nb_malloc++;
    for (k = 0; k < j; k++)
        el->_block[k] = rand() % 128;
    el->_next = syr;
    syr = el;
    c = c + b;
    return syr;
}

SYR_EL *del(SYR_EL *syr) {
    SYR_EL *el;
    el = syr;
    syr = syr->_next;
    mem_free(el->_block, el->_s);
    mem_free(el, sizeof(SYR_EL));
    return syr;
}

void mess_with_memory(void) {
    int i, j, k;
    int n = rand() % N + 1;
    n = 147;
    printf("n: %i\n", n);
    SYR_EL *syr = NULL;
    for (i = 0; i < n; i++) {
        syr = add(syr, 0, 0);
    }
    while (n > 1) {
        if (n % 2 == 0) {
            for (i = 0; i < n/2; i++) {
                syr = del(syr);
            }
            n = n/2;
        } else {
            for (i = 0; i < 2*n + 1; i++) {
                syr = add(syr, 0, 0);
            }
            n = 3*n + 1;
        }
    }
    mem_free(syr->_block, syr->_s);
    mem_free(syr, sizeof(SYR_EL));
    return;
}

int main(void) {

    printf("Size of int: %lu\n", sizeof(int));
    printf("Size of *int: %lu\n", sizeof(int *));
    mem_init();
    nb_malloc = 0;
    srand(time(NULL));
    int i;
    for (i = 0; i < 1; i++)
        mess_with_memory();
    printf("NB MALLOC: %i\n", nb_malloc);
    mem_destroy();

    return 0;

}
