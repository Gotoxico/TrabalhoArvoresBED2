#ifndef ARVOREB_H
#define ARVOREB_H

typedef struct noArvoreB{
    int n;
    int *chaves;
    char **filhos;
    int folha;
}NOARVOREB;

NOARVOREB* criarNoArvoreB(int t, int folha);
int buscarArvoreB(int chave, char** raiz);
int buscaBinariaNo(int chave, NOARVOREB* raiz, int limiteInferior, int limiteSuperior);
int buscarArvoreBBinariamente(int chave, char** raiz);
NOARVOREB* insercaoCLRS(int chave, NOARVOREB* raiz);
NOARVOREB* insercaoNaoCheioArvoreB(int chave, char** raiz);
NOARVOREB* splitChildArvore(int chave, NOARVOREB* raiz);
NOARVOREB* buscarPai(int chaveFilho, NOARVOREB* raiz);
NOARVOREB* remocaoCLRS(int chave, char** raiz);
char* geradorNomeArquivo();
void criarArquivoDiretorio();

#include "ArvoreB.c"
#endif
