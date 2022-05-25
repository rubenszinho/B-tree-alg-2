#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

FILE *cria_arquivo_dados(){
    FILE *arq = fopen(ARQ_NAME, "w+");

    return arq;
}

// Remove os characteres nulos do meio de um buffer
void elimina_nulls(char *buffer, int tamanho){
    char string[tamanho];
    int j = 0;
    for(int i = 0; i < tamanho; i++){
        if(buffer[i] != '\0'){
            string[j] = buffer[i];
            j++;
        }
    }
    string[j] = '\0';
    strncpy(buffer, string, strlen(string));
}