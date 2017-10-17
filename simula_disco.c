#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibliotecas/TAD disco.h"
asdasdasdasd

int menuOpcoes(Disco* d);
void insere_disco();
void insere_arquivo(Disco* d);
void remove_arquivo(Disco* d);
void recupera_arquivo(Disco* d);

void insere_disco(Disco* novo){
    setbuf(stdin, NULL);
    system("clear");

    char nome[40];
    unsigned long tam;

    printf("\n\n");

    printf("Defina o nome para o Disco (Max. 40 caracteres): \n");
    scanf("%[^\n]s", nome);
    setbuf(stdin, NULL);

    printf("\n");

    printf("Defina o tamanho do disco (em bytes): \n");
    scanf("%ld", &tam);
    setbuf(stdin, NULL);

    system("clear");

    printf("\n\n");

    printf("Criando disco...\n");
  	novo = disco_cria(nome, tam);
    if (novo) {
        printf("...Disco criado!\n");
    } else {
        printf("\nErro ao criar disco!\n");
        exit(1);
    }

    menuOpcoes(novo);
}

void insere_arquivo(Disco* d){
  char caminho[500];
  TipoRetorno verifica;

  printf("\n\n");

  printf("Defina o caminho do arquivo: \n");
  scanf("%s", caminho);
  setbuf(stdin, NULL);

  system("clear");

  printf("\n\n");

  printf("Gravando arquivo...\n");
  verifica = disco_grava(d, caminho);
  if (verifica == ESPACO_INSUFICIENTE) {
      printf("Espaço Insuficiente!\n");
  } else if (verifica == ARQUIVO_INEXISTENTE) {
      printf("Arquivo Inexistente!\n");
  } else if (verifica == SUCESSO) {
      printf("...arquivo gravado!\n");
  }

  printf("\n\n");
  menuOpcoes(d);
}

void remove_arquivo(Disco* d){
  char nome[500];
  TipoRetorno verifica;

  printf("\n\n");

  printf("Insira o nome do arquivo: \n");
  scanf("%s", nome);
  setbuf(stdin, NULL);

  system("clear");

  printf("\n\n");

  printf("Removendo arquivo...\n");
  verifica = disco_remove(d, nome);
  if (verifica == ARQUIVO_INEXISTENTE) {
      printf("Arquivo Inexistente!\n");
  } else if (verifica == SUCESSO) {
      printf("...Arquivo removido!\n");
  }

  printf("\n\n");
  menuOpcoes(d);
}

void recupera_arquivo(Disco* d){
  char nome[500];
  char destino[500];
  TipoRetorno verifica;

  printf("\n\n");

  printf("Insira o nome do arquivo: \n");
  scanf("%s", nome);
  setbuf(stdin, NULL);

  printf("Insira o destino do arquivo: \n");
  scanf("%s", destino);
  setbuf(stdin, NULL);

  system("clear");

  printf("\n\n");

  printf("Acessando destino...\n");
  FILE* arquivo_recuperado = fopen(destino, "wb");
  if (arquivo_recuperado == NULL) {
      printf("Erro ao abrir arquivo destino!\n");
      return;
  } else {
      printf("...Destino acessado!\n");
  }

  printf("\n\n");

  printf("Recuperando arquivo...\n");
  verifica = disco_recupera(d, nome, arquivo_recuperado);
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
  menuOpcoes(d);
}

int menuOpcoes(Disco* d){
	int opcao;
	printf(" _______________________________________________\n");
	printf("|\t\t\t\t\t\t|\n");
	printf("|\t\tBem vindo ao Disk!\t\t|\n");
	printf("|\t\t\t\t\t\t|\n");
	printf("|\t\tO que deseja fazer? \t\t|\n");
	printf("|  1-Inserir Arquivo\t2-Remover Arquivo\t|\n");
	printf("|  3-Recuperar Arquivo\t4-Sair\t\t\t|\n");
	printf("|_______________________________________________|\n\n");
	do{
		printf("Informe a Opção: ");
		scanf("%d", &opcao);
		switch (opcao) {
				case 1: system("clear"); insere_arquivo(d); return opcao; break;
				case 2: system("clear"); remove_arquivo(d); return opcao; break;
				case 3: system("clear"); recupera_arquivo(d); return opcao; break;
				case 4: printf("\n\n"); printf("Encerrando programa! Até a próxima (>.<)"); printf("\n\n"); exit(0); return opcao; break;
				default: system("clear"); printf("\nPor favor, selecione uma opção válida\n"); menuOpcoes(0);  break;
		}

	} while(opcao != 1 || opcao != 2 || opcao != 3 || opcao != 4);

	return opcao;
}

int main(int argc, char const *argv[]) {
    system("clear");
    printf("\n\n");
    printf("Iniciando programa! Bem vindo (^.^)");
    printf("\n\n");
		Disco* disk = 0;
		insere_disco(disk);
    return 0;
}
