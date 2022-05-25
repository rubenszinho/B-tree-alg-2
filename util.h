#ifndef UITL_H
#define UTIL_H

#define ARQ_NAME "registros"

#define bool int
#define TRUE 1
#define FALSE 0

#define Errors int // TODO: fazer retorno de erros funcionando

FILE *cria_arquivo_dados();
void elimina_nulls(char *buffer, int size);

#endif