
#ifndef DISCO_H
#define DISCO_H

#include "lista_sentinela.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nosetor{
    unsigned long inicio;
    unsigned long fim;
    struct nosetor* prox;
    struct nosetor* ant;
}NoSetor;

typedef struct noarquivo{
    char nome[40];
    unsigned long tam;
    Lista* setores;
    struct noarquivo* prox;
    struct noarquivo* ant;
}NoArquivo;

typedef struct{
    char nome[40];
    void* disco;
    Lista* livres;
    NoArquivo* arquivos;
    unsigned long tamDisco;
    unsigned long espacoLivre;
    unsigned long espacoOcupado;
    unsigned long qtdeArquivos;
}Disco;

typedef enum{
    SUCESSO = 0,
    ESPACO_INSUFICIENTE,
    ARQUIVO_INEXISTENTE
}TipoRetorno;

Disco* disco_cria(char* nome, unsigned long tamanho);
TipoRetorno disco_grava(Disco* d, char* arquivo); //nome arquivo deve conter o caminho absoluto ou relativo do arquivo
TipoRetorno disco_remove(Disco* d, char* nome); //somente o nome do arquivo sem o caminho
TipoRetorno disco_recupera(Disco* d, char* nome, FILE* arquivoFisico);

//Funções

NoArquivo* lista_arquivo(){
   NoArquivo* a = (NoArquivo*) malloc(sizeof(NoArquivo));
   a->prox = a;
   a->ant = a;
   return a;
}


void inserir_NoArquivo(NoArquivo* lista, char* arquivo, unsigned long arqTam){

    NoArquivo* a = (NoArquivo*) malloc(sizeof(NoArquivo));
    strcpy(a->nome, arquivo);
    a->tam = arqTam;
    a->setores = lista_cria();

    NoArquivo* p = lista;
    a->ant = p->ant;
    a->prox = p;
    p->ant = a;
    a->ant->prox = a;
}

Disco* disco_cria(char* nome, unsigned long tamanho){
    Disco* d = (Disco*) malloc(sizeof(Disco));
    strcpy(d->nome, nome);
    d->disco = (void*) malloc(tamanho);
    d->livres = lista_cria();
    lista_insere(d->livres, 0, tamanho);
    d->tamDisco = tamanho;
    d->espacoLivre = tamanho;
    d->espacoOcupado = 0;
    d->qtdeArquivos = 0;
    d->arquivos = lista_arquivo();
    return d;
}

unsigned long arquivo_tam(char* arquivo){
    FILE* arq =  fopen(arquivo, "rb");

    if (arq == NULL) {
        return ARQUIVO_INEXISTENTE;
    }

    fseek(arq, 0, SEEK_END);
    unsigned long tamanho = ftell(arq);
    fclose(arq);
    return tamanho;
}

TipoRetorno disco_grava(Disco* d, char* arquivo){
    unsigned long tamanhoArquivo = arquivo_tam(arquivo);

    if (tamanhoArquivo > d->espacoLivre) {
        return ESPACO_INSUFICIENTE;
    }

    inserir_NoArquivo(d->arquivos, arquivo, tamanhoArquivo);

    FILE* arq = fopen(arquivo, "rb");

    if (arq == NULL) {
        return ARQUIVO_INEXISTENTE;
    }

    unsigned long qnt_gravado = 0;
    int grava = 1;
    unsigned long falta_gravar = tamanhoArquivo;
    Lista* setores = d->arquivos->ant->setores;
    No* livre = d->livres->sentinela->prox;

    while(grava) {
        qnt_gravado = fread(d->disco+(livre->ini), 1, ((livre->fim)-(livre->ini)+1), arq);

        if (qnt_gravado == ((livre->fim) - (livre->ini))) {
            No* setorArq = lista_remove(d->livres, 0);
            setorArq->ant = setores->sentinela->ant;
            setorArq->prox = setores->sentinela;
            setores->sentinela->ant->prox = setorArq;
            setores->sentinela->ant = setorArq;
        } else {
            No* setorArq = novo_No();
            unsigned long novoIni = (livre->ini+qnt_gravado);
            lista_insere(setores, livre->ini, (novoIni-1));
            livre->ini = novoIni;
        }

        d->espacoLivre -= qnt_gravado;
        d->espacoOcupado += qnt_gravado;

        falta_gravar -= qnt_gravado;
        if (falta_gravar == 0) {
            grava = 0;
        }
    }
}



#endif //DISCO_H
