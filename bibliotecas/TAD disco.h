
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
    No* setores;
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


void inserir_arquivo(NoArquivo* lista, char* arquivo, unsigned long arqTam){

    NoArquivo* a = (NoArquivo*) malloc(sizeof(NoArquivo));
    strcpy(a->nome, arquivo);
    a->tam = arqTam;
    a->setores = novo_No(0, 0);
    a->setores->prox = a->setores;
    a->setores->ant = a->setores;

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
    lista_insere(d->livres, 0, tamanho, 0);
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

    inserir_arquivo(d->arquivos, arquivo, tamanhoArquivo);

    FILE* arq = fopen(arquivo, "rb");
    No* livre = d->livres->sentinela->prox;

    





}



#endif //DISCO_H
