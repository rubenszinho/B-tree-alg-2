#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "index.h"
#include "operacoes.h"
#include "util.h"

int main(void)
{
    char nome_arq[] = "registros.bin";
    char nome_arq_arvore[] = "chaves.bin";
    cria_arquivo_dados(nome_arq);
    cria_arquivo_dados(nome_arq_arvore);

    FILE *ponteiro_arvore_arq = fopen(nome_arq_arvore, "r+");
    btPage *raiz = pegaOuCriaRaiz(ponteiro_arvore_arq);

    // Etapa de leitura da stdin e escrita dos dados lidos no arquivo binário.
    while (1)
    {
        // lendo da stdin e interrompendo laço quando encontrado o fim da entrada (EOF)
        char *str = (char *) malloc(TAM_INPUT*sizeof(char));
        // silenciando warning do valgrind de jmp com essa variavel nao inicializada
        void *eof = fgets(str, TAM_INPUT, stdin);
        if (eof == NULL)
        {
            free(str);
            break;
        }
        sanitizar_string(str);
        if (strcmp(str, "exit") == 0)
        {
            free(str);
            break;
        }

        char *operacao = (char *) malloc(TAM_STRING*sizeof(char));
        unsigned short int success = parsear_string(operacao, str, CSV_OP);
        if (!success)
        {
            printf("Erro no parseamento da operacao %s\n", str);
        }

        sscanf(str, "%s", operacao);


        if (strcmp(operacao, "insert") == 0)
        {
            int success = 0;

            char buffer[200];
            success = parsear_string(buffer, str, CSV_USPNUMBER);
            if (!success)
                printf("Algo deu errado no parseamento para pegar o numUSP na insercao\n");

            int found = buscaArvore(raiz, atoi(buffer), ponteiro_arvore_arq);

            if (found == -1)
            {
                FILE *p_arq = fopen(nome_arq, "r+");

                long rrn = getRRNinFile(p_arq);
                fseek(p_arq, rrn * TAM_REGISTRO, SEEK_SET);
                write_string_data(p_arq, str);

                fclose(p_arq);

                record new_record;
                new_record.key = atoi(buffer);
                new_record.recordRRN = rrn;
                insercaoArvore(&new_record, &raiz, ponteiro_arvore_arq);

            }
            else
            {
                printf("O Registro ja existe!\n");
            }
        }
        else if (strcmp(operacao, "search") == 0)
        {
            char buffer[TAM_STRING];
            parsear_string(buffer, str, CSV_OPINFO);
            unsigned short int chave_de_busca = atoi(buffer);

            int register_rrn = buscaArvore(raiz, chave_de_busca, ponteiro_arvore_arq);
            if (register_rrn == -1)
            {
                printf("Registro nao encontrado!\n");
            }
            else
            {
                FILE *p_arq = fopen(nome_arq, "r+");

                fseek(p_arq, register_rrn * TAM_REGISTRO, SEEK_SET);
                aluno_st aluno;
                ler_registro(&aluno, p_arq);
                imprimir_aluno(&aluno);

                fclose(p_arq);
            }
        }
        else if (strcmp(operacao, "update") == 0)
        {
            char buffer[TAM_STRING];
            parsear_string(buffer, str, CSV_USPNUMBER);
            unsigned short int chave_de_busca = atoi(buffer);

            int register_rrn = buscaArvore(raiz, chave_de_busca, ponteiro_arvore_arq);
            if (register_rrn == -1)
            {
                printf("Registro nao encontrado!\n");
            }
            else
            {
                FILE *p_arq = fopen(nome_arq, "r+");

                fseek(p_arq, register_rrn * TAM_REGISTRO, SEEK_SET);
                write_string_data(p_arq, str);

                fclose(p_arq);
            }
        }
        else
        {
            printf("Houve um erro na operacao: %s\n", operacao);
        }

        free(operacao);
        free(str);
    }

    libera_node(raiz);
    fclose(ponteiro_arvore_arq);

    return 0;
}