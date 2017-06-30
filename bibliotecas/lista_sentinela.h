
// Danilo Sambugaro de Carlo
// RA 1857347
// Darlan Felipe Sousa Andrade
// RA 1857355

#ifndef LISTA_SENTINELA_H
#define LISTA_SENTINELA_H

#include <stdio.h>
#include <stdlib.h>

typedef unsigned long T;

typedef struct no{
    T ini;
    T fim;
    struct no* prox;
    struct no* ant;
}No;

typedef struct{
    No* sentinela;
    int tam;
}Lista;

Lista* lista_cria();
void lista_insere(Lista* l, T ini, T fim);
No* lista_remove(Lista* l, int posicao);
No* novo_No(T elem1, T elem2);
void posiciona_ponteiro(Lista *l, int posi, No* p);

No* novo_No(T elem1, T elem2){
    No* n = (No*) malloc(sizeof(No));
    n->ini = elem1;
    n->fim = elem2;
    n->prox = NULL;
    n->ant = NULL;
    return n;
}

void posiciona_ponteiro(Lista *l, int posi, No* p){
    if ((l->tam/2) >= posi) {
        p = l->sentinela->prox;
        for (int i = 0; i < posi; i++) {
            p = p->prox;
        }
    } else {
        p = l->sentinela->ant;
        for (int i = 0; i < ((l->tam) - (posi)); i++) {
            p = p->ant;
        }
    }
}

Lista* lista_cria(){
    Lista* l = (Lista*) malloc(sizeof(Lista));
    l->sentinela = novo_No(0, 0);
    l->sentinela->prox = l->sentinela;
    l->sentinela->ant = l->sentinela;
    l->tam = 0;
    return l;
}

void lista_insere(Lista* l, T ini, T fim){

    No* p = l->sentinela;
    No* novo = novo_No(ini, fim);
    novo->ant = p->ant;
    novo->prox = p;
    p->ant->prox = novo;
    p->ant = novo;
    (l->tam)++;

}

No* lista_remove(Lista* l, int posicao){

    No* p = l->sentinela;
    posiciona_ponteiro(l, posicao, p);
    p->prox->ant = p->ant;
    p->ant->prox = p->prox;
    (l->tam)--;
    return p;
}

#endif //LISTA_SENTINELA_H
