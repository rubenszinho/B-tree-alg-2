#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "alunos.h"

struct aluno_st{
    int nUsp;
    char nome[NAME_SIZE];
    char sobrenome[NAME_SIZE];
    char curso[COURSE_SIZE];
    float nota;
};

// Recebe uma string com os dados do aluno e coloca eles numa struct de tipo aluno
aluno *criar_aluno(char linha[STRUCT_SIZE]){
    aluno *novoAluno = malloc(sizeof(aluno));
    memset(novoAluno, 0, sizeof(aluno));

    char *tok;

    tok = strtok(linha, SEPARATORS);
    novoAluno->nUsp = atoi(tok);
    tok = strtok(NULL, SEPARATORS);
    strcpy(novoAluno->nome, tok);
    tok = strtok(NULL, SEPARATORS);
    strcpy(novoAluno->sobrenome, tok);  
    tok = strtok(NULL, SEPARATORS);
    strcpy(novoAluno->curso, tok);
    tok = strtok(NULL, SEPARATORS);
    novoAluno->nota = atof(tok);

    return novoAluno;
}

// Escreve o aluno no arquivo de registros e salva seu indice no arquivo index
void inserir_aluno(aluno *aluno, FILE *arq){
    int rrn = ftell(arq);
    char separator = ',';

    if(insere_index(aluno->nUsp, rrn)){
        fprintf(arq, "%d", aluno->nUsp);
        fprintf(arq, "%c", separator);
        fwrite(aluno->nome, sizeof(char), NAME_SIZE, arq);
        fprintf(arq, "%c", separator);
        fwrite(aluno->sobrenome, sizeof(char), NAME_SIZE, arq);
        fprintf(arq, "%c", separator);
        fwrite(aluno->curso, sizeof(char), COURSE_SIZE, arq);
        fprintf(arq, "%c", separator);
        fprintf(arq, "%f", aluno->nota);
        fprintf(arq, "%c", separator);
    }else{
        printf("O Registro ja existe!\n");
    }
    free(aluno);
}

// Le um aluno do arquivo localizado no RRN (offset) dado
aluno *le_aluno(FILE *arq, int rrn){
    char buffer[REGISTER_SIZE];
    fseek(arq, rrn, SEEK_SET);

    fread(&buffer, sizeof(char), (REGISTER_SIZE), arq);
    elimina_nulls(buffer, (REGISTER_SIZE));

    return criar_aluno(buffer);
}

// Busca um aluno no arquivo index com determinada chave (nUsp)
aluno *busca_aluno(FILE *arq, int chave){
    int rrn = busca_index(chave);
    if(rrn != NAO_ENCONTRADO){
        aluno *alunoLido = le_aluno(arq, rrn);
        return alunoLido;
    }
    return NULL;
}

void imprimir_aluno(aluno *aluno){
    printf("-------------------------------\n");
    printf("USP number: %d\n", aluno->nUsp);
    printf("Name: %s\n", aluno->nome);
    printf("Surname: %s\n", aluno->sobrenome);
    printf("Course: %s\n", aluno->curso);
    printf("Test grade: %.2f\n", aluno->nota);
    printf("-------------------------------\n");
}
