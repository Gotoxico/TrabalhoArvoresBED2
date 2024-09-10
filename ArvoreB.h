#ifndef ARVOREB_H
#define ARVOREB_H

typedef struct noArvoreB{
    char *NomeArquivo;
    int n;
    int *chaves;
    NOARVOREB **filhos; 
    int folha;
    int t;
}NOARVOREB;

NOARVOREB* criarNoArvoreB(int t, int folha);
int buscarArvoreB(int chave, char** raiz);
int buscaBinariaNo(int chave, NOARVOREB* raiz, int limiteInferior, int limiteSuperior);
int buscarArvoreBBinariamente(int chave, char** raiz);
void insercaoCLRS(int chave, char** raiz);
 void insercaoNaoCheioArvoreB(int chave, char** raiz);
void splitChildArvore(int chave, NOARVOREB* raiz);
NOARVOREB* buscarPai(int chaveFilho, NOARVOREB* raiz);
NOARVOREB* remocaoCLRS(int chave, char** raiz);
char* geradorNomeArquivo();
void criarArquivoDiretorio();
void imprimirArvoreB(NOARVOREB* raiz, int nivel);

#include "ArvoreB.c"
#endif
