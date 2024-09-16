#ifndef ARVOREB_H
#define ARVOREB_H

typedef struct noArvoreB{
    int folha;
    int t;
    char *NomeArquivo;
    int n;
    int *chaves;
    char **filhos; 
}NOARVOREB;

typedef struct raizArvoreB{
    char* NomeArquivo;
}RAIZARVOREB;

char* geradorNomeArquivo();
//int verificarRaiz(char* nomeDiretorio);
NOARVOREB* criarNoArvoreB(int t, int folha);
void criarArquivoDiretorio(NOARVOREB *no);
void removerArquivoDiretorio(char *nome);
//NOARVOREB* coletarArquivoBinario(char* nome);
NOARVOREB* abrirArquivoDiretorio(char* nomeArquivo);
//void listarArvoresDiretorio(char* nomeDiretorio);
//char * criarDiretorio();
void imprimirArvoreB(NOARVOREB* no, int nivel);
int procurarArquivoDiretorio(char *nome);
int buscarArvoreB(int chave, char* raiz);
int buscaBinariaNo(int chave, NOARVOREB* raiz, int limiteInferior, int limiteSuperior);
int buscarArvoreBBinariamente(int chave, char* raiz);
NOARVOREB* buscarPai(int chaveFilho, NOARVOREB* raiz);
void splitChildArvoreB(NOARVOREB* raiz, int i);
void insercaoNaoCheioArvoreB(int chave, NOARVOREB * raiz);
void insercaoCLRS(int chave, NOARVOREB ** raiz);
void removerArquivosDiretorio();
void listarArvores();
void geradorArquivoRaiz(NOARVOREB* raiz);
char* leituraArquivoRaiz(char* nome);
//NOARVOREB* remocaoCLRS(int chave, char* raiz);
//int remocaoCLRS(int chave, char* raiz);
//void splitChildArvore(int chave, NOARVOREB* raiz);
//void remocao(int chave, char* raiz);
//int remocaoCLRS2(int chave, NOARVOREB** raiz);
//void remocao2(int chave, NOARVOREB** raiz);
int remocaoFolha(int chave, NOARVOREB* r);
int remocaoNoInterno(int chave, NOARVOREB** raiz);
int remocaoCaso3(int chave, NOARVOREB** raiz);
int buscarFilhoRemocao(int chave, NOARVOREB* raiz);
void remocaoCLRS(int chave, NOARVOREB** raiz);

#include "ArvoreB.c"
#endif
