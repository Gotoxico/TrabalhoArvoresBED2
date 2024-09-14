#ifndef ARVOREB_H
#define ARVOREB_H

typedef struct noArvoreB{
    char *NomeArquivo;
    int n;
    int *chaves;
    char **filhos; 
    int folha;
    int t;
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
void removerArquivosDiretorio();
void listarDiretorios(char *nomeDiretorio);
void listarDiretorioPai();
int VerificarDiretorio(char *nomeDiretorio);
//NOARVOREB* remocaoCLRS(int chave, char* raiz);
int remocaoCLRS(int chave, char* raiz);
//void splitChildArvore(int chave, NOARVOREB* raiz);
void remocao(int chave, char* raiz);
int remocaoCLRS2(int chave, NOARVOREB** raiz);

#include "ArvoreB.c"
#endif
