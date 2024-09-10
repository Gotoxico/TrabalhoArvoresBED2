#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

typedef struct NOARVOREB {
    int n;
    int folha;
    int *chaves;
    char **filhos;
} NOARVOREB;

int t = 3;  //Grau mínimo da árvore B

// Função básica para criar um nó de Árvore B
NOARVOREB* criarNoArvoreB(int t, int folha) {
    NOARVOREB* no = (NOARVOREB*) malloc(sizeof(NOARVOREB));
    no->n = 0;
    no->chaves = (int*) malloc((2*t - 1) * sizeof(int));
    no->filhos = (char**) malloc(2 * t * sizeof(char*));
    no->folha = folha;
    return no;
}
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
            if(strcmp(entrada->d_name, nome) == 0){
                closedir(f);
                criarArquivoDiretorio(no, nome);
                return;
            }
        }
        criarArquivoBinario(raiz, caminhoCompleto);
        //printf("Aqui");
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

NOARVOREB * coletarArquivoBinario(char *nome){
    DIR *f = opendir("../Arvore");
    NOARVOREB *no = (NOARVOREB*) malloc(sizeof(NOARVOREB));
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

// Função para dividir um nó filho cheio
void splitChildArvoreB(NOARVOREB *pai, int i) {
    NOARVOREB *y = coletarArquivoBinario(pai->filhos[i]);
    NOARVOREB *z = criarNoArvoreB(t,y->folha);
    z->n = t - 1;

    // Transfere as últimas t-1 chaves de y para z
    for (int j = 0; j < t - 1; j++) {
        z->chaves[j] = y->chaves[j + t];
    }

    // Se y não for folha, transfere os filhos
    if (!y->folha) {
        for (int j = 0; j < t; j++) {
            z->filhos[j] = y->filhos[j + t];
        }
    }

    y->n = t - 1;

    // Insere z como filho de pai
    for (int j = pai->n; j >= i + 1; j--) {
        pai->filhos[j + 1] = pai->filhos[j];
    }
    pai->filhos[i + 1] = geradorNomeArquivo();

    // Move as chaves de pai
    for (int j = pai->n - 1; j >= i; j--) {
        pai->chaves[j + 1] = pai->chaves[j];
    }
    pai->chaves[i] = y->chaves[t - 1];
    pai->n++;

    // Atualiza os arquivos binários
    criarArquivoDiretorio(y, pai->filhos[i]);
    criarArquivoDiretorio(z, pai->filhos[i + 1]);
    criarArquivoDiretorio(pai, geradorNomeArquivo());
}

// Função para inserção em um nó que não está cheio
void insercaoNaoCheioArvoreB(NOARVOREB *no, int chave, char *nome) {
    int i = no->n - 1;

    if (no->folha) {
        // Insere a chave no nó folha
        while (i >= 0 && chave < no->chaves[i]) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        no->n++;
        criarArquivoDiretorio(no, nome);
    } else {
        // Encontra o filho adequado para descer
        while (i >= 0 && chave < no->chaves[i]) {
            i--;
        }
        i++;
        NOARVOREB *filho = coletarArquivoBinario(no->filhos[i]);

        // Se o filho estiver cheio, divide o nó
        if (filho->n == 2 * t - 1) {
            splitChildArvoreB(no, i);
            if (chave > no->chaves[i]) {
                i++;
            }
        }

        // Insere no filho adequado
        insercaoNaoCheioArvoreB(filho, chave, no->filhos[i]);
    }
}

// Função para inserção geral na árvore B
void insercaoCLRS(int chave, char *nome) {
    NOARVOREB *raiz = coletarArquivoBinario(nome);

        insercaoNaoCheioArvoreB(raiz, chave, nome);
    if (raiz->n == 2 * t - 1) {
        // Se a raiz está cheia, cria uma nova raiz
        NOARVOREB *s = criarNoArvoreB(t,0);  // Novo nó raiz
        s->filhos[0] = nome;
        splitChildArvoreB(s, 0);
        char *novoNome = geradorNomeArquivo();
        criarArquivoDiretorio(s, novoNome);
        criarArquivoDiretorio(raiz, nome);
        insercaoNaoCheioArvoreB(s, chave, novoNome);
    } else {
    }
}

// Função principal para testar a inserção na árvore B
int main() {
    // Gerar nome para o arquivo
    char* nome = geradorNomeArquivo();
    printf("Arquivo gerado: %s\n", nome);

    // Criar a raiz da árvore B
    NOARVOREB* raiz = criarNoArvoreB(t,1);  // Raiz inicialmente é folha
    criarArquivoDiretorio(raiz, nome);      // Salvar a raiz no arquivo

    // // Inserir chaves
    insercaoCLRS(10, nome);
    insercaoCLRS(20, nome);
    insercaoCLRS(5, nome);
    insercaoCLRS(6, nome);
    insercaoCLRS(12, nome);
    raiz = coletarArquivoBinario(nome);
    imprimirArvoreB(raiz, 0);  // Imprimir a árvore B
    // raiz = coletarArquivoBinario(nome);
    // for(int i = 0; i < raiz->n; i++){
    //     printf("%d\n", raiz->chaves[i]);
    // }

}

