#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "operacoes.h"
#include "util.h"

// Recebe uma string como argumento para armazenar a (index_ésima + 1) palavra
// no endereco "parseado"
unsigned short int parsear_string(char *parseado, char *string, unsigned short int index)
{
    if (string == NULL || parseado == NULL)
    {
        return 0;
    }


    char buffer[TAM_STRING];
    strcpy(buffer, "0");

    unsigned short int commas_found = 0;
    unsigned short int string_index = 0;
    unsigned short int string_size = strlen(string);

    // Percorrendo a string a ser parseada até chegarmos à parte que nos interessa.
    // Por exemplo, se queremos apenas o curso, que viria com index == 3, teríamos de
    // percorrer na string até encontrar a 3° virgula.
    for (; commas_found < index && string_index < string_size; string_index++)
    {
        if (string[string_index] == ',' || string[string_index] == ';' ||
            string[string_index] == '|')
        {
            commas_found++;
        }
    }

    unsigned short int i = 0;
    for (i = 0;
         string[string_index] != ',' && string[string_index] != ';' &&
         string[string_index] != '|' && string_index < string_size;
         i++, string_index++)
    {
        parseado[i] = string[string_index];
    }
    parseado[i] = '\0';

    // Casos especiais: A parte procurada da string é a operação. Porém, a separação da operação para o
    // num_usp é um espaço, e não uma vírgula, mesmo sendo campos diferentes.
    if (index == 0)
    {
        // A operação tem 6 letras, entao colocaremos no espaço 6 do vetor, um string_terminator.
        parseado[TAM_OPERACAO] = '\0';
    }
    if (index == 5)
    {
        string_index = TAM_OPERACAO + 1; // 1 se refere ao espaço. Exemplo: INSERT 12345678, Anything.
        // O indice em que o num_usp começa é o indice 7 (oitavo campo do vetor)
        for (i = 0;
             i < string_size && string_index < string_size && string[string_index] != ',' &&
             string[string_index] != ';' && string[string_index] != '|';
             i++, string_index++)
        {
            parseado[i] = string[string_index];
        }
        parseado[i] = '\0';
    }

    return 1;
}

// Recebe o ponteiro para o arquivo (na posicao exata em que o registro deve ser escrito)
// e uma string csv como argumento. Armazena as informacoes contidas na string_csv no formato
// aluno_st no arquivo binário especificado, de forma a ser lida posteriormente pelas demais
// funcoes do programa. Retorna 1 em sucesso, 0 caso contrário.
unsigned short int write_string_data(FILE *p_arq, char *string_csv)
{
    if (string_csv == NULL || p_arq == NULL)
    {
        return 0;
    }

    char *buffer = (char *) malloc(TAM_STRING*sizeof(char));
    int num_usp = 0;

    assert(parsear_string(buffer, string_csv, CSV_USPNUMBER) != 0);
    num_usp = atoi(buffer);

    char *nome = (char *) malloc(TAM_STRING*sizeof(char));
    assert(parsear_string(nome, string_csv, CSV_NAME) != 0);

    char *sobrenome = (char *) malloc(TAM_STRING*sizeof(char));
    assert(parsear_string(sobrenome, string_csv, CSV_SOBRENOME) != 0);

    char *curso = (char *) malloc(TAM_STRING*sizeof(char));
    assert(parsear_string(curso, string_csv, CSV_CURSO) != 0);

    float nota = 0;
    assert(parsear_string(buffer, string_csv, CSV_NOTA) != 0);
    nota = atof(buffer);

    fwrite(&num_usp, sizeof(int), 1, p_arq);
    fwrite(nome, TAM_STRING, 1, p_arq);
    fwrite(sobrenome, TAM_STRING, 1, p_arq);
    fwrite(curso, TAM_STRING, 1, p_arq);
    fwrite(&nota, sizeof(float), 1, p_arq);

    free(curso);
    free(nome);
    free(sobrenome);
    free(buffer);

    return 1;
}

// Lê um registro, se o arquivo nao tiver acabado, e o armazena em aluno. Retorna 1 em sucesso
// e 0 caso contrário.
unsigned short int ler_registro(aluno_st *aluno, FILE *p_arq)
{
    int error = fread(&aluno -> num_usp, sizeof(int), 1, p_arq);
    if (!error) return 0;

    error = fread(&aluno -> nome, sizeof(char), TAM_STRING, p_arq);
    if (!error) return 0;

    error = fread(&aluno -> sobrenome, sizeof(char), TAM_STRING, p_arq);
    if (!error) return 0;

    error = fread(&aluno -> curso, sizeof(char), TAM_STRING, p_arq);
    if (!error) return 0;

    error = fread(&aluno -> nota, sizeof(float), 1, p_arq);
    if (!error) return 0;

    return 1;
}

long getRRNinFile(FILE *p_arq)
{
    fseek(p_arq, 0, SEEK_END);
    long rrn = ftell(p_arq) / TAM_REGISTRO;
    return rrn;
}