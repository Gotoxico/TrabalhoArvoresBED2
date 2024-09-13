#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include "ArvoreB.h"
int t = 3;

//Funcao para gerar um nome de arquivo aleatorio
char* geradorNomeArquivo(){
   char nome[26];
   for(int i = 0; i < 26;i++){
        nome[i] = 'A' + i;
   }

    char *caminho = malloc(25 * sizeof(char)); 
    for(int i = 0; i < 20; i++){
        caminho[i] = nome[rand() % 26];
    }
    caminho[20] = '\0';
    strcat(caminho, ".dat");

    return caminho;
}

// Função para verificar se o arquivo raiz.dat existe no diretório
int verificarRaiz() {
    const char* caminho = "../Arvore";
    DIR *f = opendir(caminho);
    struct dirent* entrada;
    int arquivos = 0;
    if (f == NULL) {
        perror("Erro ao abrir diretorio");
        return 0;
    } else {
        while ((entrada = readdir(f)) != NULL) {
            arquivos++;
            if (strcmp(entrada->d_name, "raiz.dat") == 0) {
                closedir(f);
                return 1;
            }
        }
        closedir(f); // Fecha o diretório se "raiz.dat" não for encontrado
    }
    return 0;
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
void criarArquivoBinario(NOARVOREB *no, char *caminhoCompleto) {
    FILE *f = fopen(caminhoCompleto, "wb");
    if (f == NULL) {
        printf("Erro de criação do arquivo\n");
        return;
    }

    // Escreve o número de chaves e a folha
    fwrite(&no->n, sizeof(int), 1, f);
    fwrite(&no->folha, sizeof(int), 1, f);

    // Grava as chaves
    fwrite(no->chaves, sizeof(int), no->n, f);

    fwrite(no->NomeArquivo, sizeof(char), 25, f);
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

      
        criarArquivoBinario(raiz, caminhoCompleto);
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
    //printf("Nome: %s\n", nome);
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
                //fread(no->NomeArquivo, sizeof(char), 25, bf);
                no->NomeArquivo = nome;
                fclose(bf);
                closedir(f);
                return no;
            }
        }
    }
    closedir(f);
    free(no);
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

char * criarDiretorio(){
    char* nomeDiretorio = malloc(256 * sizeof(char));
    printf("Digite nome: \n");
    scanf("%255s", nomeDiretorio);
   
    if(_mkdir(nomeDiretorio) == 0){
        printf("Diretorio criado\n");
        return NULL;
    }
    else{
        perror("Criacao mal sucedida\n");
        return criarDiretorio();
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
            imprimirArvoreB(filho, nivel + 1);
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
int buscarArvoreB(int chave, char * raiz){
    NOARVOREB * r = coletarArquivoBinario(raiz); //Descobrir modo para esse NOARVOREB receber o no armazenado no arquivo binario
    int i = 0;
    while(i <= r->n && chave > r->chaves[i]){
        i = i+1;
    }
    if(i <= r->n && chave == r->chaves[i]){
        return i;
    }
    if(r->folha){
        return -1;
    }
    else{
        return buscarArvoreB(chave, r->filhos[i]);
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
int buscarArvoreBBinariamente(int chave, char* raiz) {
    NOARVOREB* r = coletarArquivoBinario(raiz);
    
    int i = buscaBinariaNo(chave, r, 0, r->n - 1);
    if (i >= 0) {
        return i;
    }

    if (r->folha) {
        return -1;  // Não encontrado
    }

    char* proximoFilho = r->filhos[-i - 1];
    return buscarArvoreBBinariamente(chave, proximoFilho);
}

//Funcao para buscar o pai de um no 
NOARVOREB* buscarPai(int chaveFilho, NOARVOREB* raiz){
    NOARVOREB* pai = raiz;
    while(pai->folha != 0){
        int i = -(buscaBinariaNo(chaveFilho, pai, 0, pai->n-1));
        NOARVOREB* filho = coletarArquivoBinario(pai->filhos[i]);
        if(i <= 0 && filho->folha){
            return pai;
        }
        else{
            NOARVOREB* rf = coletarArquivoBinario( pai->filhos[i]);
            buscarPai(chaveFilho, rf);
        }
    }
}

// Função para fazer o split de um nó filho
void splitChildArvoreB(NOARVOREB* raiz, int i) {
    // printf("Split\n");
    NOARVOREB* y;
    y = coletarArquivoBinario(raiz->filhos[i]);  
    printf("]\n");
    NOARVOREB* z = criarNoArvoreB(t, y->folha);
    // printf("Split\n");
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
    // printf("X[%d] = [", raiz->n);
    // for(int j=0; j < raiz->n; j++){
    //     printf("%d, ", raiz->chaves[j]);
    // }
    // printf("Y[%d] = [", y->n);
    // for(int j=0; j < y->n; j++){
    //     printf("%d, ", y->chaves[j]);
    // }
    // printf("]\n");
    // printf("Z[%d] = [", z->n);
    // for(int j=0; j < z->n; j++){
    //     printf("%d, ", z->chaves[j]);
    // }
   char * nome = y->NomeArquivo;
   y->NomeArquivo = raiz->NomeArquivo;
    raiz->NomeArquivo = nome;
    raiz->filhos[i] = y->NomeArquivo;
    raiz->filhos[i+1] = z->NomeArquivo;
    
    criarArquivoDiretorio(y, y->NomeArquivo);
    criarArquivoDiretorio(z, raiz->filhos[i+1]);
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
        printf("%s\n", raiz->NomeArquivo);
        criarArquivoDiretorio(raiz, raiz->NomeArquivo);
        printf("Insercao\n");
        for(int j = 0; j < raiz->n; j++){
            printf("%d\n", raiz->chaves[j]);
        }
-       printf("\n");
    } else {
        while (i >= 0 && chave < raiz->chaves[i]) {
            i--;
        }
        i++;
        //Leitura do filho no arquivo binário
        NOARVOREB* filho = coletarArquivoBinario(raiz->filhos[i]);
       // printf("%s\n", filho->NomeArquivo);
        // printf("%d\n%d\n", filho->n, chave);
        insercaoNaoCheioArvoreB(chave, filho);
        if (filho->n == 2 * t - 1) {
            printf("Split\n");
             splitChildArvoreB(raiz, i);
         }
    }
}


/// Função para inserção usando o método CLRS
void insercaoCLRS(int chave, NOARVOREB ** raiz) {
   NOARVOREB* r = *raiz;
    insercaoNaoCheioArvoreB(chave, r);
    if (r->n == (2 * t - 1)) {
        printf("Split\n");
        NOARVOREB* s = criarNoArvoreB(t, 0);
        s->filhos[0] = r->NomeArquivo;
        //insercaoNaoCheioArvoreB(chave, r);
        splitChildArvoreB(s, 0);
        
        // char * nome = s->NomeArquivo;
        // s->NomeArquivo = r->NomeArquivo;
        // r->NomeArquivo = nome;
        //s->filhos[0] = nome;
        printf("%s\n%s\n", r->NomeArquivo, s->NomeArquivo);
        *raiz = s;
    }        
}

/*
Funcao para remover CLRS
NOARVOREB* remocaoCLRS(int chave, char* raiz){
    NOARVOREB* r = coletarArquivoBinario(raiz); //Descobrir modo para esse NOARVOREB receber o no armazenado no arquivo binario
    int presenca = buscarArvoreB(chave, raiz);
    //Se a chave nao estiver presente na arvore, retornar null
    if(presenca == -1){
        return -1;
    }
    else{
        if(r->folha){
            //Se for folha e quando remover, a propriedade de elementos t-1 se manter
            if(r->n-1 >= t-1){
                int i = 0;
                while(i < r->n && r->chaves[i] > chave){
                    i++;
                }
                if(r->chaves[i] == chave){
                    for(int j = i; j<r->n; j++){
                        r->chaves[j] = r->chaves[j+1];
                    }
                }
            }
            //Se a propriedade nao se manter, pegar o mais a direita do irmao da esquerda ou o mais a esquerda do irmao da direita e unir, ou entao se os dois possuem t-1, agrupar
            else{
                NOARVOREB* pai = buscarPai(chave, r);
                int i = buscaBinariaNo(chave, r, 0, r->n-1);
                if(coletarArquivoBinario(pai->filhos[i-1])->n > t-1){
                    ;
                    coletarArquivoBinario(pai->filhos[i])->chaves[(coletarArquivoBinario(pai->filhos[i])->n)+1] = coletarArquivoBinario(pai->filhos[i-1])->chaves[coletarArquivoBinario(pai->filhos[i])->n];
                    coletarArquivoBinario(pai->filhos[i])->n = coletarArquivoBinario(pai->filhos[i])->n + 1;
                    coletarArquivoBinario(pai->filhos[i-1])->n = coletarArquivoBinario(pai->filhos[i])->n - 1;
                }
                else{
                    
                    if(coletarArquivoBinario(pai->filhos[i+1])->n > t-1){
                        coletarArquivoBinario(pai->filhos[i])->chaves[(coletarArquivoBinario(pai->filhos[i])->n)+1] = coletarArquivoBinario(pai->filhos[i+1])->chaves[(coletarArquivoBinario(pai->filhos[i])->n)];
                        coletarArquivoBinario(pai->filhos[i])->n = coletarArquivoBinario(pai->filhos[i])->n + 1;
                        coletarArquivoBinario(pai->filhos[i+1])->n = coletarArquivoBinario(pai->filhos[i+1])->n - 1;
                    }
                    else{
                        //Adicionar caso em que os irmaos possuem t-1
                    }
                }
            }
        }

        else{
            //Se a chave estiver em um no interno
            if(r->folha == 0 && buscarBinariaNo(chave, r, 0, r->n-1) > 0){
                int i = presenca;
                
                //Se o filho da esquerda for ficar com mais que t-1, roubar uma chave dele
                if(coletarArquivoBinario(r->filhos[i])->n >= t){
                    r->chaves[i] = coletarArquivoBinario(r->filhos[i])->chaves[coletarArquivoBinario(r->filhos[i])->n];
                    coletarArquivoBinario(r->filhos[i])->n = (coletarArquivoBinario(r->filhos[i])->n)-1;
                }
                //Se o filho da direita for ficar com mais que t-1, roubar uma chave dele
                coletarArquivoBinario(r->filhos[i+1])->n;
                if(coletarArquivoBinario(r->filhos[i+1])->n >= t){
                    r->chaves[i] = coletarArquivoBinario(r->filhos[i+1])->chaves[0];
                    coletarArquivoBinario(r->filhos[i+1])->n = (coletarArquivoBinario(r->filhos[i+1])->n)-1;
                }
                //Criar um no com merge como filho de r
                
                else{
                    int folha = coletarArquivoBinario(r->filhos[i])->folha;
                    NOARVOREB* merge = criarNoArvoreB(t, folha);

                    //Filho esquerdo
                    for(int a = 0; a < coletarArquivoBinario(r->filhos[i])->n; a++){
                        merge->chaves[a] = coletarArquivoBinario(r->filhos[i])->chaves[a];
                        merge->n = merge->n + 1;
                    }
                    
                    //Filho direito
                    for(int a = (merge->n), j = 0; a < coletarArquivoBinario(r->filhos[i+1])->n; a++, j++){
                        merge->chaves[a] = coletarArquivoBinario(r->filhos[i+1])->chaves[j];
                        merge->n = merge->n + 1;
                    }
                    
                    //Arrumando os indexes da raiz, o apontamento de filho e a quantidade de chaves
                    for(int j = i; j < (r->n) - 1; j++){
                        r->chaves[j] = r->chaves[j+1];
                    }

                    r->filhos[i] = merge;
                    r->n = (r->n) - 1;
                }
            }
            
            else{
                //Implementar casos 3 (quando chave nao esta em um no, mas ele e interno)
            }

        }

    }

}

*/
