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
    //Faz rotação de p para direita e retorna ponteiro para a nova raiz da subárvore afetada
    TNoAVL* u;
    u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    p->fb = 0;
    p = u;
    return p;
}

TNoAVL* rotacao_esquerda(TNoAVL* p)
{
    //Faz rotação de p para esquerda e retorna ponteiro para a nova raiz da subárvore afetada
    TNoAVL* u;
    u = p->dir;
    p->dir = u->esq;
    u->esq = p;
    p->fb = 0;
    p = u;
    return p;
}

TNoAVL* rotacao_dupla_direita(TNoAVL* p)
{
    //rotação esquerda-direta
    //Faz rotação de p->esq para esquerda, e de p para direita, e retorna ponteiro para nova raiz da subárvore afetada
    TNoAVL *u, *v;
    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;

    /* Atualizar FB de u  e p em função do FB de v - a nova raiz */
    if (v->fb == -1) {      /* antes: u->fb = 1 e p->fb = -2 */
        u->fb = 0;
        p->fb = 1;
    } else if (v->fb == 1) {
        p->fb = 0;
        u->fb = -1;
    } else {                /* v->fb = 0 */
        p->fb = 0;
        u->fb = 0;
    }
    p = v;
    return p;
}

TNoAVL* rotacao_dupla_esquerda(TNoAVL* p)
{
    //rotação direita-esquerda
    //Faz rotação de p->dir para direita, e de p para esquerda, e retorna ponteiro para nova raiz da subárvore afetada
    TNoAVL *z, *v;
    z = p->dir;
    v = z->esq;
    z->esq = v->dir;
    v->dir = z;
    p->dir = v->esq;
    v->esq = p;

    /*atualizar FB de z e p em função de FB de v – a nova raiz*/
    if(v->fb == 1) {
        p->fb = -1;
        z->fb = 0;
    } else if (v->fb == -1){
        p->fb = 0;
        z->fb = 1;
    } else {        //v->fb = 0
        p->fb = 0;
        z->fb = 0;
    }
    p = v;
    return p;
}

TNoAVL* caso1 (TNoAVL* p)
{
    // Chave foi inserida à esquerda de p e causou fb = -2.
    TNoAVL* u;

    u = p->esq;
    if (u->fb == -1) {      // Caso sinais iguais e negativos: rotação à direita.
        printf("\nFazendo rotação para à direita em %d", p->chave);
        p = rotacao_direita(p);
    } else {                // Caso de sinais trocados: rotação dupla u + p.
        printf("\nFazendo rotação dupla à direita em %d", p->chave);
        p = rotacao_dupla_direita(p);
    }
    p->fb = 0;
    return p;
}

TNoAVL* caso2 (TNoAVL* p)
{
    // Chave foi inserida à direita de p e causou fb = 2.
    TNoAVL* u;

    u = p->dir;
    if (u->fb == 1) {       // Caso sinais iguais e positivos: rotação à esquerda.
        printf("\nFazendo rotação para à esquerda em %d", p->chave);
        p = rotacao_esquerda(p);
    } else {                // Caso de sinais trocados: rotação dupla u + p.
        printf("\nFazendo rotação dupla à esquerda em %d", p->chave);
        p = rotacao_esquerda(p);
    }
    p->fb = 0;
    return p;
}


TNoAVL *insere(TNoAVL *p, int chave, int *flag)
{
    /* Insere no em uma árvore AVL, onde p representa a raiz da árvore,
    chave, a chave a ser inserida e flag é um booleano que indica se é necessário propagar operação de cálculo de fb */
    if (p == NULL) {
        p = (TNoAVL*) malloc(sizeof(TNoAVL));
        p->chave = chave;
        p->esq = NULL;
        p->dir = NULL;
        p->fb = 0;
        *flag = 1;
        printf("\nInseriu %d", p->chave);
    } else if (chave < p->chave) {          /* recurção à esquerda */
        p->esq = insere(p->esq, chave, flag);
        if (*flag) {                        /* inseriu: verificar balanceamento */
            switch (p->fb) {
                case -1:                   /* fb(p) = -2 */
                    p = caso1(p);
                    *flag = 0;              /* não propaga mais */
                    break;
                case 0:
                    p->fb = -1;             /* ficou maior à esquerda */
                    break;
                case 1:
                    p->fb = 0;              /* balanceou com a insersão */
                    *flag = 0;              /* não propagou mais */
                    break;
            }
        }
    } else if (chave > p->chave) {          /* recursão à direita */
        p->dir = insere(p->dir, chave, flag);
        if (*flag) {                        /* inseriu: verificar balanceamento */
            switch (p->fb) {
                case 1:                     /* fb(p) = 2 */
                    p = caso2(p);
                    *flag = 0;
                    break;
                case 0:
                    p->fb = 1;              /* ficou maior à direita */
                    break;
                case -1:
                    p->fb = 0;              /* balanceou com a insersão */
                    *flag = 0;              /* não propagou mais */
                    break;
            }
        }
    }
    // else if (chave == p->chave) ==> nada à fazer!
    return p;
}


int main() {
    TNoAVL *raiz;
    raiz = NULL;
    int ok;
    //arvore do exercício de inserção feito em aula
    raiz = insere(raiz, 50, &ok);
    raiz = insere(raiz, 40, &ok);
    raiz = insere(raiz, 30, &ok);
    raiz = insere(raiz, 45, &ok);
    raiz = insere(raiz, 47, &ok);
    raiz = insere(raiz, 55, &ok);
    raiz = insere(raiz, 56, &ok);
    raiz = insere(raiz, 1, &ok);
    raiz = insere(raiz, 2, &ok);
    raiz = insere(raiz, 3, &ok);
    raiz = insere(raiz, 49, &ok);
    raiz = insere(raiz, 60, &ok);
    raiz = insere(raiz, 10, &ok);
    printf("\n");
    imprime(raiz, 0);
}