// Danilo Sambugaro de Carlo
// RA 1857347
// Darlan Felipe Sousa Andrade
// RA 1857355


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibliotecas/TAD disco.h"

int main(int argc, char const *argv[]) {
    unsigned long tam = 10000000;
    char nome[40] = {"Unidade 1"};
    char arquivo[40] = {"photo.jpg"};
    char destino[40] = {"arquivo_recuperado.jpg"};
    TipoRetorno verifica;

    system("clear");

    printf("\n\n");

    printf("Iniciando programa! Bem vindo (^.^)");

    printf("\n\n");

    printf("Criando disco...\n");
    Disco* unidade_1 = disco_cria(nome, tam);
    if (unidade_1) {
        printf("...Disco criado!\n");
    } else {
        printf("\nErro ao criar disco!\n");
        exit(1);
    }

    printf("\n\n");

    printf("Gravando arquivo...\n");
    verifica = disco_grava(unidade_1, arquivo);
    if (verifica == ESPACO_INSUFICIENTE) {
        printf("Espaço Insuficiente!\n");
        exit(1);
    } else if (verifica == ARQUIVO_INEXISTENTE) {
        printf("Arquivo Inexistente!\n");
        exit(1);
    } else if (verifica == SUCESSO) {
        printf("...arquivo gravado!\n");
    }

    printf("\n\n");

    printf("Acessando arquivo...\n");
    FILE* arquivo_recuperado = fopen(destino, "wb");
    if (arquivo_recuperado == NULL) {
        printf("Erro ao abrir arquivo destino!\n");
        exit(1);
    } else {
        printf("...Arquivo acessado!\n");
    }

    printf("\n\n");

    printf("Recuperando arquivo...\n");
    verifica = disco_recupera(unidade_1, arquivo, arquivo_recuperado);
    if (verifica == ESPACO_INSUFICIENTE) {
        printf("Espaço Insuficiente!\n");
        exit(1);
    } else if (verifica == ARQUIVO_INEXISTENTE) {
        printf("Arquivo Inexistente!\n");
        exit(1);
    } else if (verifica == SUCESSO) {
        printf("...Arquivo recuperado!\n");
    }

    printf("\n\n");

    printf("Removando arquivo...\n");
    verifica = disco_remove(unidade_1, arquivo);
    if (verifica == ARQUIVO_INEXISTENTE) {
        printf("Arquivo Inexistente!\n");
        exit(1);
    } else if (verifica == SUCESSO) {
        printf("...Arquivo removido!\n");
    }

    printf("\n\n");

    printf("Encerrando programa! Até a próxima (>.<)");

    printf("\n\n");
    return 0;
}
