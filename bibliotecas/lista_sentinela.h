
// Danilo Sambugaro de Carlo
// RA 1857347

#ifndef LISTA_SENTINELA_H
#define LISTA_SENTINELA_H

#include <stdio.h>
#include <stdlib.h>

typedef unsigned long T;

typedef struct no{
    T* ini;
    T* fim;
    struct no* prox;
    struct no* ant;
}No;

typedef struct{
    No* sentinela;
    int tam;
}Lista;


Lista* lista_cria();

void lista_insere(Lista* l, T elemento, int posicao);
No* lista_remove1(Lista* l, int posicao);

int lista_remove2(Lista* l, int posicao, T* endereco);
T* lista_remove_elemento(Lista* l, T elemento, int (*compara)(void*,void*));

T* lista_busca1(Lista* l, int posicao);
int lista_busca2(Lista* l, int posicao, T* endereco);
int lista_contem(Lista* l, T elemento, int (*compara)(void*,void*));
int lista_posicao(Lista* l, T elemento, int (*compara)(void*,void*));

int lista_tamanho(Lista* l);
void lista_imprime(Lista* l, int (*imprimeElemento)(void*));

No* novo_No(T elem1, T elem2);
void posiciona_ponteiro(Lista *l, int posi, No* p);

//FUNÇÕES IMPLEMENTADAS

No* novo_No(T elem1, T elem2){
    No* n = (No*) malloc(sizeof(No));
    n->ini = (T*) malloc(sizeof(T));
    n->fim = (T*) malloc(sizeof(T));
    *(n->ini) = elem1;
    *(n->fim) = elem2;
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

void lista_insere(Lista* l, T ini, T fim, int posicao){

    No* p = NULL;

    posiciona_ponteiro(l, (posicao-1), p);
    No* novo = novo_No(ini, fim);
    novo->prox = p->prox;
    novo->ant = p;
    p->prox->ant = novo;
    p->prox = novo;
}

No* lista_remove1(Lista* l, int posicao){

    No* p = NULL;
    posiciona_ponteiro(l, posicao, p);

    p->prox->ant = p->ant;
    p->ant->prox = p->prox;
    return p;
}

#endif //LISTA_SENTINELA_H
