#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

// Funcao que retira o \n de uma string, caso haja algum, e tambem as aspas
// para que possamos utilizar com as mesmas funcoes dos exercicios de indice primario
void sanitizar_string(char *str)
{
    if (str == NULL)
    {
        return;
    }
    int tam = 0;
    tam = strlen(str);

    if (!tam)
    {
        return;
    }

    for (int i = 0; i < tam; i++)
    {
        if (str[i] == '\n')
        {
            str[i] = '\0';
            break;
        }
    }

    for (int i = 0; i < tam; i++)
    {
        if (str[i] == 34) // 34 == codigo das aspas em ASCII...
        {
            for (int k = i; k < tam; k++)
            {
                str[k] = str[k + 1];
            }
            tam--;
            i--;
        }
    }
}

// Função que cria um arquivo nome_arq. Se ele já existir, limpa todos os seus dados.
// Usada no início do programa para que as próximas aberturas possam ser feitas com o modo
// de abertura "r"
void cria_arquivo_dados(char *nome_arq)
{
    if (nome_arq == NULL)
    {
        return;
    }

    FILE *file = fopen(nome_arq, "w");
    if (file == NULL)
    {
        return;
    }
    fclose(file);
}

void imprimir_aluno(aluno_st *aluno)
{
    printf("-------------------------------\n");
    printf("nUSP: %d\n", aluno -> num_usp);
    printf("Nome: %s\n", aluno -> nome);
    printf("Sobrenome: %s\n", aluno -> sobrenome);
    printf("Curso: %s\n", aluno -> curso);
    printf("Nota: %.2f\n", aluno -> nota);
    printf("-------------------------------\n");
}