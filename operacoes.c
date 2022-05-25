#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alunos.h"
#include "util.h"

#define OP_SIZE 10

void inicia_operacoes(){
    FILE *arq = cria_arquivo_dados();
    cria_arquivo_index();

    char operacao[OP_SIZE] = "";
    char buffer[STRUCT_SIZE];

    while(strcmp(operacao, "exit") != 0){
        scanf("%s", operacao);
        getchar();
        fgets(buffer, STRUCT_SIZE, stdin);

        // Inserir novo aluno no arquivo
        if(strcmp(operacao, "insert") == 0){
            aluno *novoAluno = criar_aluno(buffer);
            inserir_aluno(novoAluno, arq);
        // Busca aluno com determinado numero Usp
        }else if(strcmp(operacao, "search") == 0){
            int chave = atoi(buffer);
            aluno *alunoLido = busca_aluno(arq, chave);
            if(alunoLido != NULL){
                imprimir_aluno(alunoLido);
                free(alunoLido);
            }else{
                printf("Registro nao encontrado!\n");
            }
        }

        fflush(arq);
    }
    fclose(arq);
}