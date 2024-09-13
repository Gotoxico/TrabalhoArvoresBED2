#ifndef ARVOREB_H
#define ARVOREB_H

typedef struct noArvoreB{
    char *NomeArquivo;
    int n;
    int *chaves;
    char **filhos; 
    int folha;
<<<<<<< Updated upstream
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
char geradorNomeArquivo();
void criarArquivoDiretorio();
void imprimirArvoreB(NOARVOREB* raiz, int nivel);
=======
   // int t;
}NOARVOREB;

char* geradorNomeArquivo();
NOARVOREB* criarNoArvoreB(int t, int folha);
void criarArquivoBinario(NOARVOREB * no, char* nome);
void criarArquivoDiretorio(NOARVOREB* no, char * nome);
void removerArquivoDiretorio(char * nome);
NOARVOREB* coletarArquivoBinario(char* nome);
void listarArvoresDiretorio();
char * criarDiretorio();
void imprimirArvoreB(NOARVOREB* raiz, int nivel);
int procurarArquivoDiretorio(char *nome);
int buscarArvoreB(int chave, char* raiz);
int buscaBinariaNo(int chave, NOARVOREB* raiz, int limiteInferior, int limiteSuperior);
int buscarArvoreBBinariamente(int chave, char* raiz);
NOARVOREB* buscarPai(int chaveFilho, NOARVOREB* raiz);
void splitChildArvoreB(NOARVOREB* raiz, int i);
void insercaoNaoCheioArvoreB(int chave, NOARVOREB * raiz);
void insercaoCLRS(int chave, NOARVOREB ** raiz);
//NOARVOREB* remocaoCLRS(int chave, char* raiz);
//void splitChildArvore(int chave, NOARVOREB* raiz);
>>>>>>> Stashed changes

#include "ArvoreB.c"
#endif
