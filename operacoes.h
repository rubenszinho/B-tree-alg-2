/* 
    Header de operações que serão utilizadas para operar os registros.
*/

#ifndef OPERACOES_H
#define OPERACOES_H

typedef struct aluno aluno_st;

// Recebe uma string como argumento para armazenar a (index_ésima + 1) palavra
// no endereco "parseado". Utiliza-se das macros definidas em util.h.
// Como por exemplo, ao receber CSV_CURSO como "index", retorna em "parseado"
// o curso do registro. Ao receber CSV_NOTA, retorna a nota em "parseado".
unsigned short int parsear_string(char *parseado, char *string, unsigned short int index);

// Lê um registro, se o arquivo nao tiver acabado, e o armazena em aluno. Retorna 1 em sucesso
// e 0 caso contrário.
unsigned short int ler_registro(aluno_st *aluno, FILE *p_arq);

// Recebe o ponteiro para o arquivo acabei de de(na posicao exata em que o registro deve ser escrito)
// e uma string csv como argumento. Armazena as informacoes contidas na string_csv no formato
// aluno_st no arquivo binário especificado, de forma a ser lida posteriormente pelas demais
// funcoes do programa. Retorna 1 em sucesso, 0 caso contrário.
unsigned short int write_string_data(FILE *p_arq, char *string_csv);

// retorna o proximo rrn disponivel (fim do arquivo) no arquivo de registros
long getRRNinFile(FILE *p_arq);

#endif