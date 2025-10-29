#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

typedef struct {
    char peca[10];
    int valor;
} Peca_game;

typedef struct {
    Peca_game pecas[MAX];
    int topo;
} Torre;

// Peças
Peca_game p[6] = {
    {"         ", 0},
    {"    o    ", 1},
    {"   ooo   ", 2},
    {"  ooooo  ", 3},
    {" ooooooo ", 4},
    {"ooooooooo", 5}
};

// Limpa buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausa() {
    printf("\nTecle enter para continuar...\n");
    getchar();
}

// Inicializa torres
void inicializarTorres(Torre *t1, Torre *t2, Torre *t3) {
    t1->topo = -1;
    t2->topo = -1;
    t3->topo = -1;
}

// Verifica se torre está vazia
int vazio(Torre *t) {
    return t->topo == -1;
}

// Inicia jogo com número de peças definido pela dificuldade
void start_game(Torre *t1, Torre *t2, Torre *t3, int dif) {
    int idx_peca = dif + 2; // número de peças = dif + 2
    for(int i = 0; i <= dif + 1; i++) {
        t1->pecas[i] = p[idx_peca - i];
        t1->topo++;
        t2->pecas[i] = p[0];
        t3->pecas[i] = p[0];
    }
}

// Exibe torres
void exibir(Torre *t1, Torre *t2, Torre *t3, int dif) {
    int idx = dif + 1;
    printf("\n[-----------]\t[-----------]\t[-----------]\n");
    for(int i = idx; i >= 0; i--) {
        printf("[ %s ]\t", t1->pecas[i].peca);
        printf("[ %s ]\t", t2->pecas[i].peca);
        printf("[ %s ]\n", t3->pecas[i].peca);
    }
    printf("[-----------]\t[-----------]\t[-----------]\n");       
    printf("[__TORRE 1__]\t[__TORRE 2__]\t[__TORRE 3__]\n\n");
}

// Move peça de uma torre para outra
void movimento(Torre *origem, Torre *destino) {
    if(vazio(origem)) {
        printf("Movimento inválido! Torre de origem vazia.\n");
        pausa();
        return;
    }

    if(!vazio(destino) && origem->pecas[origem->topo].valor > destino->pecas[destino->topo].valor) {
        printf("Movimento inválido! Não pode colocar peça maior sobre menor.\n");
        pausa();
        return;
    }

    destino->topo++;
    destino->pecas[destino->topo] = origem->pecas[origem->topo];
    origem->pecas[origem->topo] = p[0];
    origem->topo--;
}

// Checa vitória: todas as peças na torre 3
int checar_vitoria(Torre *t3, int dif) {
    if(t3->topo + 1 == dif + 2) {
        printf("\n* * * PARABENS! VOCE COMPLETOU O DESAFIO! * * *\n");
        return 1;
    }
    return 0;
}

int main() {
    char dif_level[3][30] = {"(1) - Facil","(2) - Normal","(3) - Dificil"};
    char dif_level2[3][30] = {"Facil","Normal","Dificil"};
    int dif = 1;
    int opcaoMenu = 0, torreOrigem = 0, torreDestino = 0;

    Torre t1, t2, t3;

    do {
        printf("\n=============== TORRE DE HANOI ===============\n");
        printf("(1) Jogar\n");
        printf("(2) Alterar dificuldade\n");
        printf("(0) Sair\n");
        printf("----------------------------------------------\n");
        printf("Nivel atual: %s\n", dif_level2[dif-1]);
        printf("==============================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcaoMenu);
        limparBufferEntrada();

        switch(opcaoMenu) {
            case 1:
                inicializarTorres(&t1, &t2, &t3);
                start_game(&t1, &t2, &t3, dif);
                int jogando = 1;
                int movimentos = 0;
                while(jogando) {
                    exibir(&t1, &t2, &t3, dif);
                    printf("Selecione a torre de origem (0 para sair): ");
                    scanf("%d", &torreOrigem);
                    limparBufferEntrada();
                    if(torreOrigem == 0) break;

                    printf("Selecione a torre de destino: ");
                    scanf("%d", &torreDestino);
                    limparBufferEntrada();

                    // Movimentos válidos
                    if(torreOrigem == 1 && torreDestino == 2) movimento(&t1, &t2);
                    else if(torreOrigem == 1 && torreDestino == 3) movimento(&t1, &t3);
                    else if(torreOrigem == 2 && torreDestino == 1) movimento(&t2, &t1);
                    else if(torreOrigem == 2 && torreDestino == 3) movimento(&t2, &t3);
                    else if(torreOrigem == 3 && torreDestino == 1) movimento(&t3, &t1);
                    else if(torreOrigem == 3 && torreDestino == 2) movimento(&t3, &t2);
                    else {
                        printf("Opcao invalida!\n");
                        pausa();
                        continue;
                    }

                    movimentos++;
                    if(checar_vitoria(&t3, dif)) {
                        exibir(&t1, &t2, &t3, dif);
                        printf("Total de movimentos: %d\n", movimentos);
                        pausa();
                        jogando = 0;
                    }
                }
                break;

            case 2:
                for(int i=0;i<3;i++) printf("%s\n", dif_level[i]);
                printf("Escolha uma opcao de dificuldade: ");
                scanf("%d", &dif);
                limparBufferEntrada();
                if(dif < 1 || dif > 3) dif = 1;
                printf("Dificuldade alterada para %s\n", dif_level2[dif-1]);
                pausa();
                break;

            case 0:
                printf("==============================================\n");
                printf("*** GAME OVER ***\n");
                printf("==============================================\n\n");
                break;

            default:
                printf("Opcao invalida!\n");
                pausa();
                break;
        }

    } while(opcaoMenu != 0);

    return 0;
}
