#include <stdio.h>
#include <stdlib.h>

typedef struct arvore
{
        char info;
        struct arvore *esq;
        struct arvore *dir;
} Arvore;

Arvore *cria_arv_vazia(void)
{
        return NULL;
}

Arvore *arv_constroi(char c, Arvore *e, Arvore *d)
{
        Arvore *a = (Arvore *)malloc(sizeof(Arvore));
        a->info = c;
        a->esq = e;
        a->dir = d;
        return a;
}

int verifica_arv_vazia(Arvore *a)
{
        return (a == NULL);
}

int arv_bin_check(Arvore *a)
{
        if (a != NULL && a->dir != NULL && a->esq != NULL)
        {
                printf("%c > %c = %d\n", a->info, a->esq->info, a->info > a->esq->info);
                printf("%c < %c = %d\n", a->info, a->dir->info, a->info < a->dir->info);
        }
        return a == NULL
                   ? 1
                   : ((a->esq == NULL || a->info > a->esq->info) && (a->dir == NULL || a->info < a->dir->info) && arv_bin_check(a->esq) && arv_bin_check(a->dir));
}

Arvore *arv_libera(Arvore *a)
{
        if (!verifica_arv_vazia(a))
        {
                arv_libera(a->esq);
                arv_libera(a->dir);
                free(a);
        }
        return NULL;
}

int arv_pertence(Arvore *a, char c)
{
        return a != NULL && (a->info == c || arv_pertence(a->dir, c) || arv_pertence(a->esq, c));
}

void arv_imprime(Arvore *a)
{
        if (a == NULL)
                return;
        arv_imprime(a->esq);
        printf("%c \n", a->info);
        arv_imprime(a->dir);
}

int eh_espelho(Arvore *arv_a, Arvore *arv_b)
{
        return (arv_a == NULL && arv_b == NULL) || ((arv_a != NULL && arv_b != NULL) && (arv_a->info == arv_b->info && eh_espelho(arv_a->esq, arv_b->dir) && eh_espelho(arv_a->dir, arv_b->esq)));
}

Arvore *cria_espelho(Arvore *arv_a)
{
        return arv_a == NULL
                   ? cria_arv_vazia()
                   : arv_constroi(arv_a->info, cria_espelho(arv_a->dir), cria_espelho(arv_a->esq));
}

int main(int argc, char *argv[])
{
        Arvore *a = arv_constroi(
            'a',
            arv_constroi(
                'b',
                cria_arv_vazia(),
                arv_constroi(
                    'd',
                    cria_arv_vazia(),
                    cria_arv_vazia())),
            arv_constroi(
                'c',
                arv_constroi(
                    'e',
                    cria_arv_vazia(),
                    cria_arv_vazia()),
                arv_constroi(
                    'f',
                    cria_arv_vazia(),
                    cria_arv_vazia())));

        Arvore *b = arv_constroi(
            'a',
            arv_constroi(
                'c',
                arv_constroi(
                    'f',
                    cria_arv_vazia(),
                    cria_arv_vazia()),
                arv_constroi(
                    'e',
                    cria_arv_vazia(),
                    cria_arv_vazia())),
            arv_constroi(
                'b',
                arv_constroi(
                    'd',
                    cria_arv_vazia(),
                    cria_arv_vazia()),
                cria_arv_vazia()));

        Arvore *c = arv_constroi(
            'a',
            arv_constroi(
                'c',
                arv_constroi(
                    'f',
                    cria_arv_vazia(),
                    cria_arv_vazia()),
                arv_constroi(
                    'e',
                    cria_arv_vazia(),
                    cria_arv_vazia())),
            arv_constroi(
                'b',
                arv_constroi(
                    'd',
                    cria_arv_vazia(),
                    cria_arv_vazia()),
                arv_constroi(
                    'g',
                    cria_arv_vazia(),
                    cria_arv_vazia())));

        Arvore *d = arv_constroi(
            'd',
            arv_constroi(
                'b',
                arv_constroi(
                    'a',
                    cria_arv_vazia(),
                    cria_arv_vazia()),
                arv_constroi(
                    'c',
                    cria_arv_vazia(),
                    cria_arv_vazia())),
            arv_constroi(
                'f',
                arv_constroi(
                    'e',
                    cria_arv_vazia(),
                    cria_arv_vazia()),
                arv_constroi(
                    'g',
                    cria_arv_vazia(),
                    cria_arv_vazia())));

        Arvore *a_esp = cria_espelho(a);

        printf("A:\n");
        arv_imprime(a);
        printf("\n");
        printf("A é binária: %d\n", arv_bin_check(a));

        printf("A_esp:\n");
        arv_imprime(a_esp);
        printf("\n");
        printf("A_esp é binária: %d\n", arv_bin_check(a_esp));

        printf("A_esp é espelho de a: %d\n", eh_espelho(a, a_esp));

        printf("D:\n");
        arv_imprime(d);
        printf("\n");
        printf("D é binária: %d\n", arv_bin_check(d));

        arv_libera(a);
        arv_libera(b);
        arv_libera(c);
        arv_libera(d);
        arv_libera(a_esp);
        return 0;
}
