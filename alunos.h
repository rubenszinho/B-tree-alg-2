#ifndef ALUNOS_H
#define ALUNOS_H

#include "index.h"

#define NAME_SIZE 20
#define COURSE_SIZE 40
#define STRUCT_SIZE (sizeof(int) + 2*NAME_SIZE + COURSE_SIZE + sizeof(float))
#define REGISTER_SIZE (STRUCT_SIZE + 6)
#define SEPARATORS ",.;\n"

typedef struct aluno_st aluno;

aluno *criar_aluno(char linha[STRUCT_SIZE]);
void inserir_aluno(aluno *aluno, FILE *arq);
aluno *le_aluno(FILE *arq, int rrn);
aluno *busca_aluno(FILE *arq, int nUsp);
void deleta_aluno(FILE *arq, int chave);
void imprimir_aluno(aluno *aluno);


#endif