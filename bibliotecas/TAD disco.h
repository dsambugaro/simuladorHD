
// Danilo Sambugaro de Carlo
// RA 1857347
// Darlan Felipe Sousa Andrade
// RA 1857355

#ifndef DISCO_H
#define DISCO_H

#include "lista_sentinela.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//FUNÇÕES CABEÇALHO

//DISCO
Disco* disco_cria(char* nome, unsigned long tamanho);
TipoRetorno disco_grava(Disco* d, char* arquivo); //nome arquivo deve conter o caminho absoluto ou relativo do arquivo
TipoRetorno disco_remove(Disco* d, char* nome); //somente o nome do arquivo sem o caminho
TipoRetorno disco_recupera(Disco* d, char* nome, FILE* arquivoFisico);

//AUXILIARES
int insere_livre(Lista* l, No* n);

//ARQUIVO
void arquivo_remove(NoArquivo* a);
NoArquivo* busca_arquivo(Disco* d, char* nome);
void inserir_NoArquivo(NoArquivo* lista, char* arquivo, unsigned long arqTam);
unsigned long arquivo_tam(char* arquivo);
char* pega_nome_arquivo(char* arquivo);
NoArquivo* lista_arquivo();

//FUNÇÕES CORPO

//DISCO
Disco* disco_cria(char* nome, unsigned long tamanho){
    if (nome == NULL) {
        return NULL;
    }
    if (tamanho == 0) {
        return NULL;
    }
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
    unsigned long falta_gravar = tamanhoArquivo;
    Lista* setores = d->arquivos->ant->setores;
    No* livre = d->livres->sentinela->prox;

    while(falta_gravar) {
        qnt_gravado = fread((d->disco+(livre->ini)), 1, ((livre->fim)-(livre->ini)+1), arq);

        if (qnt_gravado == ((livre->fim) - (livre->ini))) {
            No* setorArq = lista_remove(d->livres, 0);
            setorArq->ant = setores->sentinela->ant;
            setorArq->prox = setores->sentinela;
            setores->sentinela->ant->prox = setorArq;
            setores->sentinela->ant = setorArq;
        } else {
            unsigned long novoIni = (livre->ini+qnt_gravado);
            lista_insere(setores, livre->ini, (novoIni-1));
            livre->ini = novoIni;
        }

        d->espacoLivre -= qnt_gravado;
        d->espacoOcupado += qnt_gravado;
        falta_gravar -= qnt_gravado;
    }

    d->qtdeArquivos++;
    fclose(arq);
    return SUCESSO;
}

TipoRetorno disco_remove(Disco* d, char* nome){

    NoArquivo* p = busca_arquivo(d, nome);

    if (p == NULL) {
        return ARQUIVO_INEXISTENTE;
    }

    No* setorArq = NULL;
    Lista* setores = d->livres;
    while ((p->setores->tam) < 0) {
        setorArq = lista_remove(p->setores, 0);
        insere_livre(setores, setorArq);
    }

    d->qtdeArquivos--;
    d->espacoLivre += p->tam;
    d->espacoOcupado -= p->tam;

    arquivo_remove(p);

    return SUCESSO;
}

TipoRetorno disco_recupera(Disco* d, char* nome, FILE* arquivoFisico){

    NoArquivo* p = busca_arquivo(d, nome);

    if (p == NULL) {
        return ARQUIVO_INEXISTENTE;
    }

    No* sentinela = p->setores->sentinela;
    No* setor = p->setores->sentinela->prox;

    while (setor != sentinela) {
        fwrite((d->disco+(setor->ini)), 1, (((setor->fim) - (setor->ini))+1), arquivoFisico);
        setor = setor->prox;
    }

    fclose(arquivoFisico);
    return SUCESSO;
}

//AUXILIARES
int insere_livre(Lista* l, No* n){
    if (l == NULL) {
        return 0;
    }
    if (n == NULL) {
        return 0;
    }

    No* p = l->sentinela->prox;
    for (int i = 0; i < (l->tam); i++) {
        if ((n->fim) == ((p->ini)-1)) {
            p->ini = n->ini;
            if ((p->ant->fim) == ((p->ini)-1)) {
              p->ant->fim = p->fim;
              p->prox->ant = p->ant;
              p->ant->prox = p->prox;
              free(p);
            }
            free(n);
            return 1;
        } else if ((n->ini) == ((p->fim)+1)) {
            p->fim = n->fim;
            free(n);
            return 1;
        } else {
            p = p->prox;
        }
    }

    p = l->sentinela;
    n->ant = p->ant;
    n->prox = p;
    p->ant->prox = n;
    p->ant = n;

    return 1;
}

// ARQUIVO
NoArquivo* lista_arquivo(){
   NoArquivo* a = (NoArquivo*) malloc(sizeof(NoArquivo));
   a->prox = a;
   a->ant = a;
   return a;
}

char* pega_nome_arquivo(char* arquivo){
    unsigned int tam = strlen(arquivo);
    char str[40];
    char* retorna_nome = (char*) calloc(40, sizeof(char));
    strcpy(str, arquivo);
    unsigned int i;
    unsigned int aux = 0;
    for (i = 0;  i < tam; i++){
        if (str[i] == '/') {
            aux = i;
        }
    }
    if (aux != 0) {
        aux++;
    }
    for (i = 0; i < (tam); i++) {
        retorna_nome[i] = str[aux+i];
    }
    return retorna_nome;
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

void inserir_NoArquivo(NoArquivo* lista, char* arquivo, unsigned long arqTam){

    NoArquivo* a = (NoArquivo*) malloc(sizeof(NoArquivo));
    char* nome = {pega_nome_arquivo(arquivo)};
    strcpy(a->nome, nome);
    a->tam = arqTam;
    a->setores = lista_cria();

    NoArquivo* p = lista;
    a->ant = p->ant;
    a->prox = p;
    p->ant = a;
    a->ant->prox = a;

}

NoArquivo* busca_arquivo(Disco* d, char* nome){
    NoArquivo* p = d->arquivos->prox;
    for (unsigned int i = 0; i < d->qtdeArquivos; i++) {
        if ((strcmp(p->nome, nome)) == 0) {
            return p;
        } else {
            p = p->prox;
        }
    }
    return NULL;
}

void arquivo_remove(NoArquivo* a){
    a->prox->ant = a->ant;
    a->ant->prox = a->prox;
    free(a);
}





#endif //DISCO_H
