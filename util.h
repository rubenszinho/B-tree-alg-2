/* 
    Header de utilidades com as macros e funções genéricas que serão utilizadas na Árvore B e nas demais operações.
*/

#ifndef UITL_H
#define UTIL_H

#define TAM_STRING 30
#define TAM_OPERACAO 6
#define VIRGULAS 4

// macros que usaremos para definir qual parte da string csv será lida.
// Se enviarmos 0 como argumento, pegaremos o que está antes da primeira virgula.
// Se enviarmos 1 como argumento, pegaremos o que está após a primeira virgula.
// Se enviarmos 2 como argumento, pegaremos o que está após a 2 vírgula, e assim por diante.
#define CSV_OP 0        // operacao
#define CSV_NAME 1      // nome
#define CSV_SOBRENOME 2 // sobrenome
#define CSV_CURSO 3     // curso
#define CSV_NOTA 4      // nota
#define CSV_USPNUMBER 5 // contra-intuitiva a definição da macro, mas necessária.
#define CSV_OPINFO 5    // quando a operacao vem com algum dado, como por exemplo a busca (search "key")
// esse dado é obtido com a parser por meio da macro 5, ja que ocupa a mesma posicao
// do num usp na insercao

#define TAM_REGISTRO 98       // int + 3 * 30 + float
#define TAM_RRN 4               // tamanho de um inteiro.

#define TAM_INPUT TAM_OPERACAO + 1 + 16 + (3 * TAM_STRING) + VIRGULAS + 1
// palavra da op + espaco + int + float + 3 campos + virgulas + \0

struct aluno
{
    int num_usp;
    char nome[TAM_STRING], sobrenome[TAM_STRING], curso[TAM_STRING];
    float nota;
};

typedef struct aluno aluno_st;

// funcao que retira o \n de uma string, caso haja algum
void sanitizar_string(char *str);

// Função que cria um arquivo nome_arq. Se ele já existir, limpa todos os seus dados.
// Usada no início do programa para que as próximas aberturas possam ser feitas com o modo
// de abertura "r"
void cria_arquivo_dados(char *nome_arq);

// Imprime o registro de um estudante no formato especificado pelo trabalho
void imprimir_aluno(aluno_st *aluno);

#endif