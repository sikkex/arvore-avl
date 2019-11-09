#include "arvore-avl.h"

void imprime(TNoAVL* no, int tab)
{
    for(int i = 0; i < tab; i++) {
        printf("-");
    }
    if (no != NULL) {
        printf("%d (fb == %d)\n", no->chave, no->fb);
        imprime(no->esq, tab + 2);
        printf("\n");
        imprime(no->dir, tab + 2);
    } else printf("vazio");
}

TNoAVL* rotacao_direita(TNoAVL* p)
{
    TNoAVL* ptu;
    ptu = p->esq;
    p->esq = ptu->dir;
    ptu->dir = p;
    p = ptu;
    return p;
}

TNoAVL* rotacao_esquerda(TNoAVL* p)
{
    TNoAVL* ptu;
    ptu = p->dir;
    p->dir = ptu->esq;
    ptu->esq = p;
    p = ptu;
    return p;
}

TNoAVL* rotacao_dupla_direita(TNoAVL* p)
{
    rotacao_esquerda(p->esq);
    rotacao_direita(p);
    return p;
}

TNoAVL* rotacao_dupla_esquerda(TNoAVL* p)
{
    rotacao_direita(p->dir);
    rotacao_esquerda(p);
    return p;
}

int main() {
    printf("Hello, World!\n");
    return 0;
}