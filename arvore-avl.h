#include <stdio.h>
#include <stdlib.h>

/* representação dos nós  de Árvore AVL */
typedef struct sNoAVL {
    int chave;
    int fb;
    struct sNoAvl* esq;
    struct sNoAvl* dir;
} TNoAVL;

void imprime(TNoAVL* no, int tab);
TNoAVL* rotacao_direita(TNoAVL* p);
TNoAVL* rotacao_esquerda(TNoAVL* p);
TNoAVL* rotacao_dupla_direita(TNoAVL* p);
TNoAVL* rotacao_dupla_esquerda(TNoAVL* p);
TNoAVL *insere(TNoAVL *p, int chave, int *flag);

