#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <util.h>
#include "index.h"

#define TAM_PAGINA 4096
#define MAX_CHAVES 204
#define ESPACO_LIVRE_NA_PAGINA (TAM_PAGINA - ((MAX_CHAVES*4) + (MAX_CHAVES*8) + ((MAX_CHAVES+1)*8) + 3))

struct registro_st{
    int chave;
    long rrn;
};

struct pagina_st{
    registro *registros;
    long *filhos;
    short numChaves;
    bool ehFolha;
};

struct chavePromovida_st{
    int chave;
    long rrn;
    long filhos[2];
};


//Aloca espaço para carregar página
//Lê dados da página do arquivo
pagina *lePaginaDoArquivo(FILE *fp){
    pagina *pagina = malloc(TAM_PAGINA);
    //TODO
}

/*Escreve a pagina num determinado rrn*/
Errors escrevePaginaNoArquivo(long rrn, pagina *page, FILE *fp){
    //Verifica se está tudo ok com os dados
    //Encontra local para escrita baseado no RRN
    //Escreve dados
    //Atualiza valor de espaço livre na página
    //Dica: você pode criar uma função que só lida com a escrita dos dados e chamar aqui
}

/*Pega pagina um determinado rrn*/
pagina *getPagina(long RRN, FILE *fp){
    //Recupera uma página baseado no RRN
    //Procura e carrega seus dados
}

/*Pega o rrn da raiz do header*/
long getHeaderArvore(FILE *fp){
    //Carrega o cabeçalho da árvore, que está no início do arquivo
}

/*Escreve o rrn da raiz no header*/
void escreveHeaderArvore(FILE *fp, long rootRRN){
    //Calcula espaço livre e escreve no cabeçalho da árvore, junto com o RRN do nó raíz
}

pagina *criaArvore(FILE *fp){
    //Aloca espaço pra raiz
    //Inicializa os valores
    //Escreve a raiz no cabeçalho
}

pagina *getRaizArvore(FILE *fp){
    //Verifica se a árvore já existe ou precisa criar uma nova
    //Se a árvore não existir, cria ela
    //Se existir, só pega o RRN da raiz no cabeçalho e carrega sua página
    //Pode ser adaptada pra inserção e busca sem precisar de 2 funções
}

chavePromovida *insereEmNode(pagina *page, chavePromovida *newKey, FILE *fp){
    //Procura local pra inserir nova chave na página
    //Se não couber, splitta ele
    //Escreve dados na página
}

/*Insere uma chave na pagina*/
pagina *buscaEInsere(pagina *page, chavePromovida *newKey){
    //Encontra a posição para inserir a chave
    //Se não existir espaço, precisa criar uma nova página (usem uma função para criar)
    //Salvar dados da nova chave na página
}

/*Se o tamanho da pagina for impar, retorna a maior parte*/
pagina *divideECriaNode(pagina **page){
    //Encontra a posição do meio das chaves
    //Cria espaço pra nova página
    //Copia metade das chaves pra página nova
    //Limpa elas do nó antigo
    //Atualiza os filhos de ambas as páginas
    //Atualiza o número de chaves de ambas
}

/*Extrai chave promovida da pagina*/
chavePromovida *extraiChavePromovida(pagina *page){
    //Aloca espaço pra chave
    //Tira ela da página
    //Atualiza dados da página (filho, número de chaves, etc)
}

/*Divide o node e escreve no arquivo*/
chavePromovida *_divide(pagina *page,FILE *fp, chavePromovida *newKey){
    //Divide a página, cria o novo nó (faça numa função auxiliar pois é complexo)
    //Extrai a chave promovida e atualiza os filhos da chave
    //Escreve a página nova e a que foi dividida (com suas atualizações) no arquivo
}


/*Usar caso a chave promovida chegue na raiz*/
pagina *criaNodeComChavePromovida(chavePromovida *promoKey){
    //Se promoção cria estrutura para nova raiz,
    //Aloca espaço para ela
    //Salva dados da chave promovida na nova raiz
    //atualiza os filhos deste novo nó/página
    //Pode reusar função que cria página nova e adicionar somente especificidades
}

Errors setNodeRaiz(pagina *page, FILE *fp){
    //Escreve página nova e atualiza o cabeçalho para conter ela como raiz
    //Deveria ser chamada junto com criação de novo nó quando promoção cria uma nova raiz
}

/*Insercao Recursiva*/
chavePromovida *_insereArvore(pagina *node, chavePromovida *key, FILE *fp){
    //Se nó a ser inserido a chave é folha, tenta inserir
    //Caso a inserção crie uma promoção, precisa retornar a chave promovida para a recursão
    //Se não for nó folha, procura qual sub-árvore seguir para inserir numa folha
    //Encontrar a posição correta e descer para filho à esquerda se a chave for menor
    //E descer à direita se for maior
    //Chamar a inserção recursiva pro filho escolhido
    //Se a inserção recursiva retornar uma chave promovida, precisa tentar inserir essa chave promovida no nó atual
    //Retornar chave promovida ou um valor NULL se não houve promoção
}

Errors insereArvore(registro *newRecord, pagina *root, FILE *fp){
    //Função mais abstrata de inserção
    //Prepara os dados da nova chave
    //Tenta inserir recursivamente
    //Se tiver chave promovida no final da recursão, é que existe nova raiz
    //Chama as funções pra criar nova raiz e atualizar o cabeçalho
}

/*Returns rrn if key exist else return -1*/
long buscaArvore(pagina *node, int key, FILE *fp){
    //Procura no nó atual se a chave existe
    //Se não existir, tenta procurar no filho adequado, recursivamente
    //Se encontrar a chave, retorna RRN dela
    //Se não encontrar (chegar num nó folha e não estiver lá), retorna -1
}