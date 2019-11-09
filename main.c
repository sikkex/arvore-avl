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



int main() {
    printf("Hello, World!\n");
    return 0;
}