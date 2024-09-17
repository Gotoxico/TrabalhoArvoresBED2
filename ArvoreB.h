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
NOARVOREB* criarNoArvoreB(int t, int folha);
void criarArquivoDiretorio(NOARVOREB *no, char* nomeArquivo);
void removerArquivoDiretorio(char *nome);
NOARVOREB* abrirArquivoDiretorio(char* nomeArquivo);
int procurarArquivoDiretorio(char *nome);
int buscarArvoreB(int chave, NOARVOREB* raiz);
int buscaBinariaNo(int chave, NOARVOREB* raiz, int limiteInferior, int limiteSuperior);
int buscarArvoreBBinariamente(int chave, NOARVOREB* raiz);
NOARVOREB* buscarPai(int chaveFilho, NOARVOREB* raiz);
void splitChildArvoreB(NOARVOREB* raiz, int i);
void insercaoNaoCheioArvoreB(int chave, NOARVOREB * raiz);
void insercaoCLRS(int chave, NOARVOREB ** raiz);
void removerArquivosDiretorio();
void listarArvores();
char * geradorArquivoRaiz(NOARVOREB* raiz);
NOARVOREB * leituraArquivoRaiz(char* nome);
int remocaoFolha(int chave, NOARVOREB* r);
int remocaoNoInterno(int chave, NOARVOREB** raiz);
int remocaoCaso3(int chave, NOARVOREB** raiz);
int buscarFilhoRemocao(int chave, NOARVOREB* raiz);
void remocaoCLRS(int chave, NOARVOREB** raiz);
void atualizarNomeArquivoRaiz(NOARVOREB* raiz, char* nomeArquivo);
void removerArvoreRaiz(char* nome);
void removerArvore(char* nome);
int diretorioVazio();
int buscarArquivo(char* nome);
#include "ArvoreB.c"
#endif
