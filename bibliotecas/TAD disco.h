
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
   a->setores = novo_No(-1, -1);
   a->setores->prox = a->setores;
   a->setores->ant = a->setores;
   a->tam = 0;
   return a;
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


TipoRetorno disco_grava(Disco* d, char* arquivo){

}



#endif //DISCO_H
