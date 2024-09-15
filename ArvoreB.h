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

char* geradorNomeArquivo();
int verificarRaiz(char* nomeDiretorio);
NOARVOREB* criarNoArvoreB(int t, int folha);
void criarArquivoBinario(NOARVOREB *no, char *caminhoCompleto);
void criarArquivoDiretorio(NOARVOREB *no, char *nome, char* nomeDiretorio);
void removerArquivoDiretorio(char *nome, char* nomeDiretorio);
NOARVOREB* coletarArquivoBinario(char* nome);
NOARVOREB* abrirArquivoDiretorio(char *nomeDiretorio, char* nomeArquivo);
void listarArvoresDiretorio(char* nomeDiretorio);
char * criarDiretorio();
void imprimirArvoreB(NOARVOREB* no, int nivel, char* nomeDiretorio);
int procurarArquivoDiretorio(char *nome, char* nomeDiretorio);
int buscarArvoreB(int chave, char* raiz, char* nomeDiretorio);
int buscaBinariaNo(int chave, NOARVOREB* raiz, int limiteInferior, int limiteSuperior);
int buscarArvoreBBinariamente(int chave, char* raiz, char* nomeDiretorio);
NOARVOREB* buscarPai(int chaveFilho, NOARVOREB* raiz, char* nomeDiretorio);
void splitChildArvoreB(NOARVOREB* raiz, int i, char* nomeDiretorio);
void insercaoNaoCheioArvoreB(int chave, NOARVOREB * raiz, char* nomeDiretorio);
void insercaoCLRS(int chave, NOARVOREB ** raiz, char* nomeDiretorio);
void removerArquivosDiretorio(char* nomeDiretorio);
void listarDiretorioPai();
void listarDiretorios(char *nomeDiretorio);
int VerificarDiretorio(char *nomeDiretorio);
//NOARVOREB* remocaoCLRS(int chave, char* raiz);
//int remocaoCLRS(int chave, char* raiz);
//void splitChildArvore(int chave, NOARVOREB* raiz);
//void remocao(int chave, char* raiz);
//int remocaoCLRS2(int chave, NOARVOREB** raiz);
//void remocao2(int chave, NOARVOREB** raiz);
int remocaoFolha(int chave, NOARVOREB* r, char* nomeDiretorio);
int remocaoNoInterno(int chave, NOARVOREB** raiz, char* nomeDiretorio);
int remocaoCaso3(int chave, NOARVOREB** raiz, char* nomeDiretorio);
int buscarFilhoRemocao(int chave, NOARVOREB* raiz);
void remocaoCLRS(int chave, NOARVOREB** raiz, char* nomeDiretorio);

#include "ArvoreB.c"
#endif
