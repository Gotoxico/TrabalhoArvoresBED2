#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "ArvoreB.h"
int t = 3;

//Funcao para gerar um nome de arquivo aleatorio
char* geradorNomeArquivo(){
    srand(time(NULL));
   char nome[26];
   for(int i = 0; i < 26;i++){
        nome[i] = 'A' + i;
   }

    char *caminho = malloc(25 * sizeof(char)); 
    ".dat";
    for(int i = 0; i < 20; i++){
        caminho[i] = nome[rand() % 26];
    }
    caminho[20] = '\0';
    strcat(caminho, ".dat");

    return caminho;
}

// Função básica para criar um nó de Árvore B
NOARVOREB* criarNoArvoreB(int t, int folha) {
    NOARVOREB* no = (NOARVOREB*) malloc(sizeof(NOARVOREB));
    no->n = 0;
    no->chaves = (int*) malloc((2*t - 1) * sizeof(int));
    no->filhos = (char**) malloc(2 * t * sizeof(char*));
    no->folha = folha;
    no->NomeArquivo = geradorNomeArquivo();
    
    return no;
}

//funcao para criar um arquivo binario
void criarArquivoBinario(NOARVOREB *no, char *nome) {
    FILE *f = fopen(nome, "wb");
    if (f == NULL) {
        printf("Erro de criação do arquivo\n");
        return;
    }

    // Escreve o número de chaves e a folha
    fwrite(&no->n, sizeof(int), 1, f);
    fwrite(&no->folha, sizeof(int), 1, f);

    // Grava as chaves
    fwrite(no->chaves, sizeof(int), no->n, f);

    // Aqui você pode adicionar código para gravar os filhos, caso seja necessário.

    fclose(f);
}

//função para criar um arquivo binario dentro de um diretorio
void criarArquivoDiretorio(NOARVOREB * no, char *nome){
    NOARVOREB *raiz = no;
    DIR *f = opendir("../Arvore");
    struct dirent* entrada;
    int arquivos = 0;
    if(f == NULL){
        printf("Erro ao abrir diretorio\n");
        return;
    }

    else{
        char caminhoCompleto[250];
        snprintf(caminhoCompleto, sizeof(caminhoCompleto), "../Arvore/%s", nome);

        //nome = strcpy(nome, geradorNomeArquivo());
        while ((entrada = readdir(f)) != NULL) {
            arquivos++;
            
        }
        criarArquivoBinario(raiz, caminhoCompleto);
        free(nome);
        closedir(f);
    }
}

//Função para remover um arquivo binário de um diretório, dado o seu nome
void removerArquivoDiretorio(char *nome){
    DIR *f = opendir("../Arvore");
    struct dirent* entrada;
    int arquivos = 0;
    if(f == NULL){
        printf("Erro ao abrir diretorio\n");
        return;
    }

    else{
        while ((entrada = readdir(f)) != NULL) {
            arquivos++;
            if(strcmp(entrada->d_name, nome) == 0){
                char caminhoCompleto[250];
                snprintf(caminhoCompleto, sizeof(caminhoCompleto), "../Arvore/%s", nome);
                remove(caminhoCompleto);
                closedir(f);
                return;
            }
        }
    }
}

//Função para coletar um arquivo binário de um diretório
NOARVOREB * coletarArquivoBinario(char *nome){
    DIR *f = opendir("../Arvore");
    NOARVOREB * no = criarNoArvoreB(t, 1);
    struct dirent* entrada;
    int arquivos = 0;
    
    if(f == NULL){
        printf("Erro de leitura\n");
        return NULL;
    }
    else{
        char caminhoCompleto[250];  
        sprintf(caminhoCompleto, "../Arvore/%s", nome);
        while ((entrada = readdir(f)) != NULL) {
            arquivos++;
            if(strcmp(entrada->d_name, nome) == 0){
                FILE *bf = fopen(caminhoCompleto, "rb");
                if(bf == NULL){
                    printf("Erro de leitura\n");
                    return NULL;
                }
                fread(&no->n, sizeof(int), 1, bf);
                fread(&no->folha, sizeof(int), 1, bf);
                no->chaves = (int *)malloc(no->n * sizeof(int));
                fread(no->chaves, sizeof(int), no->n, bf);
                no->NomeArquivo = nome;
                fclose(bf);
                closedir(f);
                return no;
            }
        }
    }
    return NULL;
}


//Implementar funcao pra pesquisar arvores na pasta
void listarArvoresDiretorio(){
    DIR *f = opendir("./Arvore");
    struct dirent* entrada;
    int arquivos = 0, i = 1;

    if(f == NULL){
        printf("Erro de leitura\n");
        return;
    }

    else{
        while((entrada=readdir(f))!= NULL){
            arquivos++;
            NOARVOREB* raiz = coletarArquivoBinario(entrada->d_name);
            if(raiz->folha == 0){
                printf("Arquivo %d: %s\n", i, entrada->d_name);
                i++;
            }
        }
    }
}

// Função de impressão da Árvore B
void imprimirArvoreB(NOARVOREB* no, int nivel) {
    if (no != NULL) {
        int i;
        for (i = 0; i < no->n; i++) {
            if (!no->folha) {
                NOARVOREB * filho = coletarArquivoBinario(no->filhos[i]);
                imprimirArvoreB(filho, nivel + 1);
            }
            for (int j = 0; j < nivel; j++) {
                printf("    ");  // Indentação para mostrar a profundidade
            }
            printf("%d\n", no->chaves[i]);
        }
        if (!no->folha) {
            NOARVOREB * filho = coletarArquivoBinario(no->filhos[i]);
            imprimirArvoreB(no->filhos[i], nivel + 1);
        }
    }
}


//função para procurar um nome de arquivo em um diretório
int procurarArquivoDiretorio(char *nome){
    DIR *f = opendir("../Arvore");
    struct dirent* entrada;
    int arquivos = 0;
    if(f == NULL){
        printf("Erro ao abrir diretorio\n");
        return 0;
    }

    else{
        while ((entrada = readdir(f)) != NULL) {
            arquivos++;
            if(strcmp(entrada->d_name, nome) == 0){
                closedir(f);
                return 1;
            }
        }
    }
    return 0;
}

//Buscar presenca de um no na arvore e retornar a posicao em relacao ao vetor de chaves do no
int buscarArvoreB(int chave, NOARVOREB * raiz){
    NOARVOREB* r = raiz; //Descobrir modo para esse NOARVOREB receber o no armazenado no arquivo binario
    int i = 0;
    while(i <= r->n && chave > r->chaves[i]){
        i = i+1;
    }
    if(i <= r->n && chave == r->chaves[i]){
        return i;
    }
    if(r->folha){
        return NULL;
    }
    else{
        return buscarArvoreB(chave, raiz->filhos[i]);
    }
}

// Função de busca binária em um nó
int buscaBinariaNo(int chave, NOARVOREB* raiz, int limiteInferior, int limiteSuperior) {
    if (limiteInferior > limiteSuperior) {
        return -(limiteInferior + 1);  // Retorna índice negativo se não encontrado
    }

    int meio = (limiteInferior + limiteSuperior) / 2;
    if (raiz->chaves[meio] == chave) {
        return meio;
    }

    if (raiz->chaves[meio] > chave) {
        return buscaBinariaNo(chave, raiz, limiteInferior, meio - 1);
    } else {
        return buscaBinariaNo(chave, raiz, meio + 1, limiteSuperior);
    }
}

// Função para buscar uma chave na árvore B binariamente
int buscarArvoreBBinariamente(int chave, NOARVOREB* raiz) {
    int i = buscaBinariaNo(chave, raiz, 0, raiz->n - 1);
    if (i >= 0) {
        return i;
    }

    if (raiz->folha) {
        return -1;  // Não encontrado
    }

    char* proximoFilho = raiz->filhos[-i - 1];
    return buscarArvoreBBinariamente(chave, proximoFilho);
}

// Função para fazer o split de um nó filho
void splitChildArvoreB(NOARVOREB* raiz, int i) {
    NOARVOREB* y = criarNoArvoreB(t, 0);
    y = coletarArquivoBinario(raiz->filhos[i]);  
    NOARVOREB* z = criarNoArvoreB(t, y->folha);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++) {
        z->chaves[j] = y->chaves[j + t];
    }

    if (!y->folha) {
        for (int j = 0; j < t; j++) {
            z->filhos[j] = y->filhos[j + t];
        }
    }
    y->n = t - 1;

    for (int j = raiz->n+1; j >= i; j--) {
        raiz->filhos[j + 1] = raiz->filhos[j];
    }

    raiz->filhos[i + 1] = z->NomeArquivo;

    for (int j = raiz->n; j >= i-1; j--) {
        raiz->chaves[j + 1] = raiz->chaves[j];
    }
    raiz->chaves[i] = y->chaves[t - 1];
    raiz->n++;
    criarArquivoDiretorio(y, y->NomeArquivo);
    criarArquivoDiretorio(z, z->NomeArquivo);
    criarArquivoDiretorio(raiz, raiz->NomeArquivo);
}

void insercaoNaoCheioArvoreB(int chave, NOARVOREB * raiz) {

    int i = raiz->n;
    if (raiz->folha) {
        while (i >= 0 && chave < raiz->chaves[i]) {
            raiz->chaves[i + 1] = raiz->chaves[i];
            i--;
        }
        raiz->chaves[i + 1] = chave;
        raiz->n++;
        criarArquivoDiretorio(raiz, raiz->NomeArquivo);

    } else {
        while (i >= 0 && chave < raiz->chaves[i]) {
            i--;
        }
        i++;
        //Leitura do filho no arquivo binário
        NOARVOREB* filho = coletarArquivoBinario(raiz->filhos[i]);
        insercaoNaoCheioArvoreB(chave, filho);
        if (filho->n == 2 * t - 1) {
            splitChildArvoreB(raiz, i);
        }
    }
}


/// Função para inserção usando o método CLRS
void insercaoCLRS(int chave, NOARVOREB ** raiz) {
   NOARVOREB* r = *raiz;
    insercaoNaoCheioArvoreB(chave, r);
    if (r->n == (2 * t - 1)) {
        NOARVOREB* s = criarNoArvoreB(t, 0);
        s->filhos[0] = s->NomeArquivo;
        insercaoNaoCheioArvoreB(chave, r);
        splitChildArvoreB(s, 0);
        s->NomeArquivo = r->NomeArquivo;
        *raiz = s;
    }        
}

//Funcao para buscar o pai de um no 
NOARVOREB* buscarPai(int chaveFilho, NOARVOREB* raiz){
    NOARVOREB* pai = raiz;
    while(pai->folha != 0){
        int i = buscaBinariaNo(chaveFilho, pai, 0, pai->n-1);
        if(i <= 0 && pai->filhos[-i].folha){
            return pai;
        }
        else{
            NOARVOREB* rf = pai->filhos[-i];
            buscarPai(chaveFilho, rf);
        }
    }
}


