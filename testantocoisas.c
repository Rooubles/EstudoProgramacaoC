#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define MAX 5

typedef struct 
{
    int peca[MAX];
    int topo;
} Torre;

//-------

void inicializarTorres(Torre *t1, Torre *t2, Torre *t3) {
    t1->topo = -1;
    t2->topo = -1;
    t3->topo = -1;
}

void start_game(Torre *t1, Torre *t2, Torre *t3, int *d) {
    int dif = *d + 2;
    int peca = dif;
    printf( "\nPEÇA %d , DIF %d\n", peca, dif); 
    for(int i = 0 ; i < dif ; i++) {
        t1->peca[i] = peca;
        t2->peca[i] = 0;
        t3->peca[i] = 0;
        t1->topo++;
        peca--;
    }
}

void exibir (Torre *t1, Torre *t2, Torre *t3, int *d) {
    int dif = *d + 2;
    int idx = dif-1;
    printf("\n");
    for(int i = 0 ; i < dif ; i++) {
        printf("[     %d     ]\t", t1->peca[idx]);
        printf("[     %d     ]\t", t2->peca[idx]);
        printf("[     %d     ]\n", t3->peca[idx]);
        idx--;
    }
    printf("[  TORRE A  ]\t");
    printf("[  TORRE B  ]\t");
    printf("[  TORRE C  ]\n");
}

int main() {
    char dif_level[3][30] = {"(1) - Facil","(2) - Normal"," (3) - Dificil"};
    int dif = 1;
    Torre t1;
    Torre t2;
    Torre t3;

    inicializarTorres(&t1, &t2, &t3);
    start_game(&t1, &t2, &t3, &dif);
    exibir(&t1, &t2, &t3, &dif);

    printf("\n\ntopo: %d\n\n", t1.peca[t1.topo]);




    return 0;
}

