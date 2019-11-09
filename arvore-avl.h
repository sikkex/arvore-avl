#include <stdio.h>
#include <stdlib.h>

/* representação dos nós  de Árvore AVL */
typedef struct sNoAVL {
    int chave;
    int fb;
    struct sNoAVL* esq;
    struct sNoAVL* dir;
} TNoAVL;

void imprime(TNoAVL* no, int tab);
TNoAVL* rotacao_direita(TNoAVL* p);
TNoAVL* rotacao_esquerda(TNoAVL* p);
TNoAVL* rotacao_dupla_direita(TNoAVL* p);
TNoAVL* rotacao_dupla_esquerda(TNoAVL* p);
TNoAVL *insere(TNoAVL *p, int chave, int *flag);
TNoAVL *remover(TNoAVL *p, int chave, int *flag);
TNoAVL* caso1 (TNoAVL* p);
TNoAVL* caso2 (TNoAVL* p);

