#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include "ArvoreB.h"
//int t = 3;

//Funcao para gerar um nome de arquivo aleatorio
char* geradorNomeArquivo(){
   char nome[26];
   for(int i = 0; i < 26;i++){
        nome[i] = 'A' + i;
   }

    char *caminho = (char*)malloc(25 * sizeof(char)); 
    for(int i = 0; i < 20; i++){
        caminho[i] = nome[rand() % 26];
    }
    caminho[20] = '\0';
    strcat(caminho, ".dat");

    return caminho;
}

// Função para verificar se o arquivo raiz.dat existe no diretorio
int verificarRaiz(char* nomeDiretorio) {
    char* caminho = (char*) malloc(256 * sizeof(char));
    snprintf(caminho, sizeof(caminho), "../Diretorios/%s", nomeDiretorio);
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
        closedir(f); // Fecha o diretorio se "raiz.dat" nao for encontrado
    }
    return 0;
}

// Funcao basica para criar no de arvore B
NOARVOREB* criarNoArvoreB(int t, int folha) {
    NOARVOREB* no = (NOARVOREB*) malloc(sizeof(NOARVOREB));
    no->n = 0;
    no->chaves = (int*) malloc((2*t - 1) * sizeof(int));
    no->filhos = (char**) malloc((2*t) * sizeof(char*));
    for (int i = 0; i < 2 * t; i++) {
        no->filhos[i] = (char*) malloc(25 * sizeof(char));  // ou o tamanho adequado
    }
    no->folha = folha;
    no->NomeArquivo = (char*) malloc(25 * sizeof(char));
    //strncpy(no->NomeArquivo, geradorNomeArquivo(), 25);
    strcpy(no->NomeArquivo , geradorNomeArquivo());
    no->t = t;
    
    return no;
}

//funcao para criar um arquivo binario
void criarArquivoBinario(NOARVOREB *no, char *caminhoCompleto) {
    FILE *f = fopen(caminhoCompleto, "wb");
    if (f == NULL) {
        printf("Erro de criacao do arquivo\n");
        return;
    }

    // Escreve o numero de chaves e a folha
    fwrite(&no->n, sizeof(int), 1, f);
    fwrite(&no->folha, sizeof(int), 1, f);

    // Grava as chaves
    fwrite(no->chaves, sizeof(int), no->n, f);

    fwrite(no->NomeArquivo, sizeof(char), strlen(no->NomeArquivo) + 1, f);  // Grava a string inteira, incluindo o terminador nulo

    // Aqui voce pode adicionar codigo para gravar os filhos, caso seja necesssario.
    printf("Nome: %s\n", no->NomeArquivo);
    printf("Folha: %d\n", no->n);
    printf("Chaves: ");
    for(int i = 0; i < no->n; i++){
        printf("%d ", no->chaves[i]);
    }

    fclose(f);
}

//funcao para criar um arquivo binario dentro de um diretorio no diretorio Arvore chamando a funcao criarArquivoBinario

void criarArquivoDiretorio(NOARVOREB *no, char *nome, char* nomeDiretorio) {
    NOARVOREB *raiz = no;
    char* caminho = (char*) malloc(256 * sizeof(char));
    snprintf(caminho, sizeof(caminho), "../Diretorios/%s", nomeDiretorio);
    DIR *f = opendir(caminho);
    
    if (f == NULL) {
        printf("Erro ao abrir diretorio\n");
        return;
    } else {
        // Cria o caminho completo para o arquivo
        char caminhoCompleto[250];
        snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s%s", caminho, nome);

        // Abre o arquivo binário para escrita
        FILE *file = fopen(caminhoCompleto, "wb");
        if (file == NULL) {
            printf("Erro de criacao do arquivo\n");
            closedir(f);
            return;
        }
        printf("Nome: %s\n",nome);
        for(int i = 0; i < no->n;i++){
            printf("%d, ", no->chaves[i]);
        }
        printf("\nFolha: %d\n", no->folha);
        if(no->folha == 0){
            printf("filhos: \n");
            for(int i = 0; i < no->n+1; i++){
                printf("%s\n", no->filhos[i]);
            }
        }
        printf("\n");
        // Escreve o numero de chaves e se o no e folha
        fwrite(&no->n, sizeof(int), 1, file);
        fwrite(&no->folha, sizeof(int), 1, file);

        // Grava as chaves
        fwrite(no->chaves, sizeof(int), no->n, file);

        // Grava o NomeArquivo (string), garantindo que seja armazenada corretamente
        fwrite(nome, sizeof(char), strlen(nome) + 1, file);  // Inclui o terminador nulo

        // Aqui você pode adicionar codigo para gravar os filhos, caso seja necessario.
        // Exemplo de gravação dos filhos (caso aplicavel):
        if (!no->folha) {
            for (int i = 0; i < no->n + 1; i++) {
                fwrite(no->filhos[i], sizeof(char), strlen(no->filhos[i]) + 1, file);
            }
            
            // fwrite(no->filhos, sizeof(char), (no->n + 1) * 25, file);
        }

        // Exibe informações no console (opcional)
        // printf("Nome: %s\n", no->NomeArquivo);
        // printf("Folha: %d\n", no->folha);
        // printf("Chaves: ");
        // for (int i = 0; i < no->n; i++) {
        //     printf("%d ", no->chaves[i]);
        // }
        // printf("\n");

        // Fecha o arquivo binário e o diretório
        fclose(file);
        closedir(f);
    }
}


//Função para remover um arquivo binário de um diretório, dado o seu nome
void removerArquivoDiretorio(char *nome, char* nomeDiretorio){
    char* caminho = (char*) malloc(256 * sizeof(char));
    snprintf(caminho, sizeof(caminho), "../Diretorios/%s", nomeDiretorio);
    DIR *f = opendir(caminho);
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
                snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s%s", caminho, nome);
                remove(caminhoCompleto);
                closedir(f);
                return;
            }
        }
    }
}

//Funcao

//Função para coletar um arquivo binário de um diretório
/*NOARVOREB * coletarArquivoBinario(char *nome){
    
    //printf("Nome: %s\n", nome);
    DIR *f = opendir("../Diretorios/Arvore");
    NOARVOREB * no = criarNoArvoreB(t, 1);
    struct dirent* entrada;
    int arquivos = 0;
    
    if(f == NULL){
        printf("Erro de leitura\n");
        return NULL;
    }
    else{
        char caminhoCompleto[250];  
        sprintf(caminhoCompleto, "../Diretorios/Arvore/%s", nome);
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
                //no->chaves = (int *)malloc(no->n * sizeof(int));
                fread(no->chaves, sizeof(int), no->n, bf);
                fread(no->NomeArquivo, sizeof(char), 25, bf);
                if(!no->folha){ 
                    for(int i = 0; i < no->n+1; i++){
                        fread(no->filhos[i], sizeof(char), 25, bf);
                    }
                    // fread(no->filhos, sizeof(char), (no->n + 1) * 25, bf);
                }
                //no->NomeArquivo = malloc(25 * sizeof(char));
                //no->NomeArquivo = nome;
                fclose(bf);
                closedir(f);
                return no;
            }
        }
    }
    closedir(f);
    free(no);
    return NULL;
}*/

//Mesma funcao que coletarArquivoBinario, mas atualizada para abrir um diretorio dentro de Diretorios
NOARVOREB* abrirArquivoDiretorio(char* nomeArquivo, char *nomeDiretorio){
    char caminho[256];
    snprintf(caminho, sizeof(caminho), "../Diretorios/%s", nomeDiretorio);
    DIR *f = opendir(caminho);
    struct dirent* entrada;
    int arquivos = 0;

    if(f == NULL){
        printf("Erro de leitura\n");
        return NULL;
    }
    else{
        char caminhoCompleto[256];
        int folha, t;
        snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s/%s", caminho, nomeArquivo);
        while((entrada = readdir(f)) != NULL){
            arquivos++;
            if(strcmp(entrada->d_name, nomeArquivo) == 0){
                FILE *bf = fopen(caminhoCompleto, "rb");
                if(bf == NULL){
                    printf("Erro de leitura\n");
                    return NULL;
                }
                fread(&folha, sizeof(int), 1, bf);
                fread(&t, sizeof(int), 1, bf);
                NOARVOREB* no = criarNoArvoreB(t, folha);
                no->folha = folha;
                no->t = t;
                fread(&no->n, sizeof(int), 1, bf);
                fread(&no->folha, sizeof(int), 1, bf);
                //no->chaves = (int *)malloc(no->n * sizeof(int));
                fread(no->chaves, sizeof(int), no->n, bf);
                fread(no->NomeArquivo, sizeof(char), 25, bf);
                if(!no->folha){ 
                    for(int i = 0; i < no->n+1; i++){
                        fread(no->filhos[i], sizeof(char), 25, bf);
                    }
                    // fread(no->filhos, sizeof(char), (no->n + 1) * 25, bf);
                }
                //no->NomeArquivo = malloc(25 * sizeof(char));
                //no->NomeArquivo = nome;
                fclose(bf);
                closedir(f);
                return no;
            }
        }

    }
    closedir(f);
    return NULL;
}


//Implementar funcao pra pesquisar arvores na pasta
void listarArvoresDiretorio(char* nomeDiretorio){
    char* caminho = (char*) malloc(256 * sizeof(char));
    snprintf(caminho, sizeof(caminho), "../Diretorios/%s", nomeDiretorio);

    DIR *f = opendir(caminho);
    struct dirent* entrada;
    int arquivos = 0, i = 1;

    if(f == NULL){
        printf("Erro de leitura\n");
        return;
    }

    else{
        while((entrada=readdir(f))!= NULL){
            arquivos++;
            NOARVOREB* raiz = abrirArquivoDiretorio(nomeDiretorio, entrada->d_name);
            if(raiz->folha == 0){
                printf("Arquivo %d: %s\n", i, entrada->d_name);
                i++;
            }
        }
    }
}

//Funcao para criar um diretorio dentro do diretorio Diretorios
char * criarDiretorio(){
    DIR *f = opendir("../Diretorios");
    char* nomeDiretorio = (char*)malloc(256 * sizeof(char));
    printf("Digite nome: \n");
    scanf("%255s", nomeDiretorio);

    char* caminhoCompleto = (char*)malloc(256*sizeof(char));
    snprintf(caminhoCompleto, sizeof(caminhoCompleto), "../Diretorios%s", nomeDiretorio);

    if(VerificarDiretorio(caminhoCompleto)){
        perror("Diretorio existente\n");
        return criarDiretorio();
    }
    
    if(mkdir(caminhoCompleto) == 0){
        printf("Diretorio criado\n");
        return caminhoCompleto;
    }
    else{
        perror("Criacao mal sucedida\n");
        free(nomeDiretorio);
        free(caminhoCompleto);
        return criarDiretorio();
    }
}

//Funcao para imprimir a arvore B
void imprimirArvoreB(NOARVOREB* no, int nivel, char* nomeDiretorio) {
    if (no != NULL) {
        int i;
        
        // Primeiro imprimir o lado direito (maiores)
        if (!no->folha) {
            NOARVOREB * filho = abrirArquivoDiretorio(no->filhos[no->n], nomeDiretorio);
            imprimirArvoreB(filho, nivel + 1, nomeDiretorio);
        }

        // Depois imprimir as chaves e os filhos da esquerda
        for (i = no->n - 1; i >= 0; i--) {
            for (int j = 0; j < nivel; j++) {
                printf("    ");  // Indentação para mostrar a profundidade
            }
            printf("%d\n", no->chaves[i]);

            if (!no->folha) {
                NOARVOREB * filho = abrirArquivoDiretorio(no->filhos[i], nomeDiretorio);
                imprimirArvoreB(filho, nivel + 1, nomeDiretorio);
            }
        }
    }
}

//função para procurar um nome de arquivo em um diretório
int procurarArquivoDiretorio(char *nome, char* nomeDiretorio){
    char* caminho = (char*) malloc(256 * sizeof(char));
    snprintf(caminho, sizeof(caminho), "../Diretorios/%s", nomeDiretorio);

    DIR *f = opendir(caminho);
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
int buscarArvoreB(int chave, char* raiz, char* nomeDiretorio){
    NOARVOREB* r = abrirArquivoDiretorio(raiz, nomeDiretorio); 
    printf("Inicio da busca\n");
    int i = 0;
    while(i <= r->n-1 && chave > r->chaves[i]){
        i = i+1;
    }
    if(i <= r->n-1 && chave == r->chaves[i]){
        return 1;
    }
    if(r->folha){
        return -1;
    }
    else{
        return buscarArvoreB(chave, r->filhos[i], nomeDiretorio);
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
int buscarArvoreBBinariamente(int chave, char* raiz, char* nomeDiretorio) {
    NOARVOREB* r = abrirArquivoDiretorio(raiz, nomeDiretorio);
    
    int i = buscaBinariaNo(chave, r, 0, r->n - 1);
    if (i >= 0) {
        return i;
    }

    if (r->folha) {
        return -1;  // Não encontrado
    }

    char* proximoFilho = r->filhos[-i - 1];
    return buscarArvoreBBinariamente(chave, proximoFilho, nomeDiretorio);
}

//Funcao para buscar o pai de um no 
NOARVOREB* buscarPai(int chaveFilho, NOARVOREB* raiz, char* nomeDiretorio){
    NOARVOREB* pai = raiz;
    while(pai->folha != 0){
        int i = -(buscaBinariaNo(chaveFilho, pai, 0, pai->n-1));
        NOARVOREB* filho = abrirArquivoDiretorio(pai->filhos[i], nomeDiretorio);
        if(i <= 0 && filho->folha){
            return pai;
        }
        else{
            NOARVOREB* rf = abrirArquivoDiretorio( pai->filhos[i], nomeDiretorio);
            buscarPai(chaveFilho, rf, nomeDiretorio);
        }
    }
    return NULL;
}

void splitChildArvoreB(NOARVOREB* raiz, int i, char* nomeDiretorio) {
    // Carrega o nó filho y a partir do arquivo binário correspondente
    NOARVOREB* y = abrirArquivoDiretorio(raiz->filhos[i], nomeDiretorio);  
    // Cria um novo nó z, que vai receber as metades das chaves de y
    NOARVOREB* z = criarNoArvoreB(raiz->t, y->folha);  
    z->n = raiz->t - 1;

    // Copia as últimas t-1 chaves de y para z
    for (int j = 0; j < raiz->t - 1; j++) {
        z->chaves[j] = y->chaves[j + raiz->t];
    }

    // Se y não for folha, transfere os filhos correspondentes para z
    if (!y->folha) {
        for (int j = 0; j < raiz->t; j++) {
            strcpy(z->filhos[j], y->filhos[j + raiz->t]);
        }
    }

    // Atualiza o número de chaves em y
    y->n = raiz->t - 1;

    // Move os filhos de raiz para dar espaço para o novo filho z
    for (int j = raiz->n; j >= i + 1; j--) {
        strcpy(raiz->filhos[j + 1], raiz->filhos[j]);
    }

    // Insere o ponteiro para o novo nó z
    strcpy(raiz->filhos[i + 1], z->NomeArquivo);

    // Move as chaves de raiz para dar espaço para a nova chave
    for (int j = raiz->n; j >= i; j--) {
        raiz->chaves[j + 1] = raiz->chaves[j];
    }

    // Insere a chave do meio de y em raiz
    raiz->chaves[i] = y->chaves[raiz->t - 1];
    raiz->n++;

    // Exibe os nomes dos nós para fins de depuração
    printf("Nome x: %s\n", raiz->NomeArquivo);
    printf("Nome y: %s\n", y->NomeArquivo);
    printf("Nome z: %s\n", z->NomeArquivo);

    

        // Se for a raiz, grava os arquivos correspondentes
        //strcpy(raiz->filhos[i], y->NomeArquivo);
        printf("\nCRIACAO DO DIRETORIO Y\n");
        criarArquivoDiretorio(y, y->NomeArquivo, nomeDiretorio);
        printf("\nCRIACAO DO DIRETORIO Z\n");
        criarArquivoDiretorio(z, z->NomeArquivo, nomeDiretorio);
        printf("\nCRIACAO DO DIRETORIO RAIZ\n");
        criarArquivoDiretorio(raiz, raiz->NomeArquivo, nomeDiretorio);
        printf("\n");
    
    
        
}

//Funcao para inserir em no nao cheio
void insercaoNaoCheioArvoreB(int chave, NOARVOREB * raiz, char* nomeDiretorio) {

    int i = raiz->n-1;
    if (raiz->folha) {
        printf("\nINSERCAO NA FOLHA\n");
        while (i >= 0 && chave < raiz->chaves[i]) {
            raiz->chaves[i + 1] = raiz->chaves[i];
            i--;
        }


       // printf("%d\n", chave);
        raiz->chaves[i + 1] = chave;
        raiz->n++;
      
        criarArquivoDiretorio(raiz, raiz->NomeArquivo, nomeDiretorio);
//         printf("Insercao\n");
//         printf("\n");
    } else {
        printf("\nINSERCAO NAO FOLHA\n"); 
        while (i >= 0 && chave < raiz->chaves[i]) {
            i--;
        }
        i++;
        //Leitura do filho no arquivo binário
        printf("Arquivo filho: %s\n", raiz->filhos[i]);
        NOARVOREB* filho = abrirArquivoDiretorio(raiz->filhos[i], nomeDiretorio);
        printf("Arquivo filho: %s\n", filho->NomeArquivo);
        // printf("%d\n%d\n", filho->n, chave);
        // printf("%s\n", filho->NomeArquivo);
        printf("insere no filho\n");
        insercaoNaoCheioArvoreB(chave, filho, nomeDiretorio);
        //printf("Valor de N: %d\n", filho->n);
        if (filho->n == 2 * (raiz->t) - 1) {
            printf("SPLIT DO NÓ FOLHA\n");
            splitChildArvoreB(raiz, i, nomeDiretorio);
        }
    }
}

// Função para inserção usando o método CLRS
void insercaoCLRS(int chave, NOARVOREB ** raiz, char* nomeDiretorio) {
    
   NOARVOREB* r = *raiz;
   printf("\n===========================================");
   printf("\nINICIO DA INSERCAO A PARTIR DA RAIZ\n");
    insercaoNaoCheioArvoreB(chave, r, nomeDiretorio);
    if (r->n == (2 * r->t - 1)) {
        //strcmp(r->NomeArquivo, geradorNomeArquivo());
        printf("\nSPLIT DA RAIZ CHEIA\n");
        NOARVOREB* s = criarNoArvoreB(r->t, 0);
        //strcpy(s->NomeArquivo, "raiz.dat");
        strcpy(s->filhos[0], r->NomeArquivo);
        //insercaoNaoCheioArvoreB(chave, r);
        splitChildArvoreB(s, 0, nomeDiretorio);

        *raiz = s;

    } 
    printf("\n===========================================\n");
}

//funcao para remover todos os arquivos de um diretorio
void removerArquivosDiretorio(char* nomeDiretorio){
    char* caminho = (char*) malloc(256 * sizeof(char));
    snprintf(caminho, sizeof(caminho), "../Diretorios/%s", nomeDiretorio);
    DIR *f = opendir(caminho);
    struct dirent* entrada;
    int arquivos = 0;
    if(f == NULL){
        printf("Erro ao abrir diretorio\n");
        return;
    }

    else{
        while ((entrada = readdir(f)) != NULL) {
            arquivos++;
            if(strcmp(entrada->d_name, ".") != 0 && strcmp(entrada->d_name, "..") != 0){
                char caminhoCompleto[250];
                snprintf(caminhoCompleto, sizeof(caminhoCompleto), "%s%s", caminho, entrada->d_name);
                remove(caminhoCompleto);
            }
        }
    }
    closedir(f);
}

//funcao para listar diretorio sem parametros
void listarDiretorioPai(){
    DIR *f = opendir("../Diretorios");
    struct dirent* entrada;
    int arquivos = 0;
    if(f == NULL){
        printf("Erro ao abrir diretorio\n");
        return;
    }

    else{
        while ((entrada = readdir(f)) != NULL) {
            arquivos++;
            if(strcmp(entrada->d_name, ".") != 0 && strcmp(entrada->d_name, "..") != 0){
                printf("%s\n", entrada->d_name);
            }
        }
    }
    closedir(f);
}

//funcao para listar diretorios 
void listarDiretorios(char *nomeDiretorio){
    char caminho[256];
    snprintf(caminho, sizeof(caminho), "../Diretorios/%s", nomeDiretorio);
    DIR *f = opendir(caminho);
    struct dirent* entrada;
    int arquivos = 0;
    if(f == NULL){
        printf("Erro ao abrir diretorio\n");
        return;
    }

    else{
        while ((entrada = readdir(f)) != NULL) {
            arquivos++;
            if(strcmp(entrada->d_name, ".") != 0 && strcmp(entrada->d_name, "..") != 0){
                printf("%s\n", entrada->d_name);
            }
        }
    }
    closedir(f);
}

//Funcao para verificar se um diretorio existe
int VerificarDiretorio(char *nomeDiretorio){
    char caminho[256];
    snprintf(caminho, sizeof(caminho), "../Diretorios/%s", nomeDiretorio);
    DIR *f = opendir(caminho);
    if(f == NULL){
        return 0;
    }
    else{
        return 1;
    }
}

// // Função de busca binária em um nó
// int buscaBinariaNo(int chave, NOARVOREB* raiz, int limiteInferior, int limiteSuperior) {
//     if (limiteInferior > limiteSuperior) {
//         printf("Chave não encontrada\n");
//         return -(limiteInferior + 1);  // Retorna índice negativo se não encontrado
//     }
//     printf("Recebendo meio\n");
//     int meio = (limiteInferior + limiteSuperior) / 2;
//     if (raiz->chaves[meio] == chave) {
//         printf("Chave encontrada\n");
//         return meio;  // Chave encontrada
//     }

//     if (raiz->chaves[meio] > chave) {
//         printf("Busca à esquerda\n");
//         return buscaBinariaNo(chave, raiz, limiteInferior, meio - 1);
//     } else {
//         printf("Busca à direita\n");
//         return buscaBinariaNo(chave, raiz, meio + 1, limiteSuperior);
//     }
// }

// Função para remover de nó folha
int remocaoFolha(int chave, NOARVOREB* r, char* nomeDiretorio){
    //Caso 1: A chave está em uma folha
    printf("Remoção em folha\n");
    if (r->folha) {
        int i = 0;
        while (i < r->n && r->chaves[i] < chave) {
            i++;
        }
      
        // Se a chave foi encontrada, removê-la
        if (i < r->n && r->chaves[i] == chave) {
            printf("Chave encontrada\n");
            for (int j = i; j < r->n - 1; j++) {
                r->chaves[j] = r->chaves[j + 1];
            }
            r->n--; // Atualizando o número de chaves
           
            printf("Valores:\n\n");
            for(int j = 0; j < r->n; j++){
                printf("%d\n", r->chaves[j]);
            }
            printf("\n");
            printf("Criando arquivo\n");
            // Atualizando o nó no arquivo binário
            criarArquivoDiretorio(r, r->NomeArquivo, nomeDiretorio);
            return 1;  // Sucesso
        }
        // Se a chave não foi encontrada
        return 0;
    }
    return 0;
}

//função de buscar para retornar em qual dos filhos do raiz deve ser feita a remoção
int buscarFilhoRemocao(int chave, NOARVOREB* raiz){
    int i = 0;
    while(i < raiz->n && chave > raiz->chaves[i]){
        i++;
    }
    return i;
}


// Função para tratar remoção de caso 3 (filho com t-1 chaves)
int remocaoCaso3(int chave, NOARVOREB** raiz, char* nomeDiretorio){
    NOARVOREB* r = *raiz;
    int i = buscaBinariaNo(chave, r, 0, r->n - 1); // Busca binária para encontrar a posição da chave

    // Se a chave não está no nó, ajustar índice para o filho correto
    if (i < 0) {
        i = -i - 1;  // Corrigindo índice para o filho correto
    } else {
        // Chave foi encontrada no nó raiz (tratar remoção em nós internos posteriormente)
        return 0;
    }
    printf("Valor de i: %d\n", i);
    NOARVOREB* filho = abrirArquivoDiretorio(r->filhos[i], nomeDiretorio);
    

    // Caso 3a: Se o filho tem t-1 chaves, faz balanceamento
    if (filho->n == (filho->t - 1) ) {
        printf("\nENTRANDO NO CASO 3\n");
        NOARVOREB* irmaoEsquerdo = (i > 0) ? abrirArquivoDiretorio(r->filhos[i - 1], nomeDiretorio) : NULL;
        printf("Recebeu irmao esquerdo\n");
        if(irmaoEsquerdo){
            imprimirArvoreB(irmaoEsquerdo, 0,  nomeDiretorio);
        }
        NOARVOREB* irmaoDireito = (i < r->n) ? abrirArquivoDiretorio(r->filhos[i+1], nomeDiretorio) : NULL;
        printf("Recebeu irmao direito\n");
        if(irmaoDireito){
            imprimirArvoreB(irmaoDireito, 0, nomeDiretorio);
        }

        // Emprestar do irmão esquerdo
        if (irmaoEsquerdo && irmaoEsquerdo->n >= r->t) {
            printf("Caso 3a: Empréstimo do irmão esquerdo\n");
            for (int j = filho->n; j > 0; j--) {
                filho->chaves[j] = filho->chaves[j - 1];
            }
            for(int j = filho->n + 1; j > 0; j--){
                strcpy(filho->filhos[j], filho->filhos[j-1]);
            }
            strcpy(filho->filhos[0], irmaoEsquerdo->filhos[irmaoEsquerdo->n]);
            filho->chaves[0] = r->chaves[i - 1];  // Pega chave da raiz
            r->chaves[i - 1] = irmaoEsquerdo->chaves[irmaoEsquerdo->n - 1];  // Atualiza raiz
            filho->n++;
            irmaoEsquerdo->n--;

            criarArquivoDiretorio(irmaoEsquerdo, irmaoEsquerdo->NomeArquivo, nomeDiretorio);
            criarArquivoDiretorio(filho, filho->NomeArquivo, nomeDiretorio);
            return 1;
        }
        // Emprestar do irmão direito
        else if (irmaoDireito && irmaoDireito->n >= r->t) {
            printf("Caso 3a: Empréstimo do irmão direito\n");
            filho->chaves[filho->n] = r->chaves[i];  // Pega chave da raiz
            r->chaves[i] = irmaoDireito->chaves[0];  // Atualiza raiz
            strcpy(filho->filhos[filho->n + 1], irmaoDireito->filhos[0]);  // Atualiza filhos
            for (int j = 0; j < irmaoDireito->n - 1; j++) {
                irmaoDireito->chaves[j] = irmaoDireito->chaves[j + 1];  // Mover chaves no irmão direito  // Mover filhos no irmão direito
            }
            for(int j = 0; j < irmaoDireito->n; j++){
                strcpy(irmaoDireito->filhos[j], irmaoDireito->filhos[j+1]);
            }
            filho->n++;
            irmaoDireito->n--;
            remocaoCLRS(chave, &filho, nomeDiretorio);  // Chamar recursivamente para remover a chave

            criarArquivoDiretorio(irmaoDireito, irmaoDireito->NomeArquivo, nomeDiretorio);
            criarArquivoDiretorio(filho, filho->NomeArquivo, nomeDiretorio);
            return 1;
        }
        // Merge com o irmão direito
        else if (irmaoDireito) {
            printf("Caso 3b: Merge com o irmão direito\n");
            filho->chaves[filho->n] = r->chaves[i];  // Mover chave da raiz para o filho
            for (int j = 0; j < irmaoDireito->n; j++) {
                filho->chaves[filho->n + 1 + j] = irmaoDireito->chaves[j];  // Copiar chaves do irmão direito
            }
            for(int j = 0; j < irmaoDireito->n + 1; j++){
                strcpy(filho->filhos[filho->n + 1 + j], irmaoDireito->filhos[j]);
            }
            filho->n += irmaoDireito->n + 1;
            r->n--;  // Atualiza número de chaves na raiz
            
            printf("\n=========================\nImpriimir filho\n");
            imprimirArvoreB(filho, 0, nomeDiretorio);
            //remocaoCLRS(chave, &filho);  // Chamar recursivamente para remover a chave
            *raiz = filho;

            criarArquivoDiretorio(filho, filho->NomeArquivo, nomeDiretorio);
            //criarArquivoDiretorio(r, r->NomeArquivo);
            free(irmaoDireito);  // Libera o nó do irmão direito
            return 1;
        
        }
        else{
            printf("Caso 3b: Merge com o irmão esquerdo\n");
            irmaoEsquerdo->chaves[irmaoEsquerdo->n] = r->chaves[i - 1];  // Mover chave da raiz para o irmão esquerdo
            for (int j = 0; j < filho->n; j++) {
                irmaoEsquerdo->chaves[irmaoEsquerdo->n + 1 + j] = filho->chaves[j];  // Copiar chaves do filho
            }
            for(int j = 0; j < filho->n + 1; j++){
                strcpy(irmaoEsquerdo->filhos[irmaoEsquerdo->n + 1 + j], filho->filhos[j]);
            }
            irmaoEsquerdo->n += filho->n + 1;
            r->n--;  // Atualiza número de chaves na raiz
            remocaoCLRS(chave, &irmaoEsquerdo, nomeDiretorio);  // Chamar recursivamente para remover a chave
            *raiz = irmaoEsquerdo;
            
            //remocaoCLRS(chave, &irmaoEsquerdo);  // Chamar recursivamente para remover a chave
            criarArquivoDiretorio(irmaoEsquerdo, irmaoEsquerdo->NomeArquivo, nomeDiretorio);
            free(filho);  // Libera o nó do filho
            return 1;
        }
    }
    return 0;
}

int remocaoNoInterno(int chave, NOARVOREB** raiz, char* nomeDiretorio){
    NOARVOREB* r = *raiz;
    printf("\nINICIO DA REMOCAO NO INTERNO\n");
    // Caso 2: A chave está em um nó interno
    int i = buscaBinariaNo(chave, r, 0, r->n - 1); // Busca binária para encontrar a posição da chave
    printf("Valor de i: %d\n", i);
    printf("Valor de n: %d\n\n", r->n);
    if (i < 0) {
        return 0;
    }
    if(r->n >= r->t){
        NOARVOREB* esquerda = abrirArquivoDiretorio(r->filhos[i], nomeDiretorio);
        printf("i>0\n");
        // Se o filho à esquerda tem pelo menos t chaves, substituímos pela maior chave da subárvore esquerda
        if (esquerda->n >= esquerda->t) {
            printf("Caso 2a\n");
            int maior = esquerda->chaves[(esquerda->n) - 1]; // Maior chave à esquerda
            //remocaoCLRS(maior, &esquerda); // Remover o maior
            esquerda->n--;
            r->chaves[i] = maior; // Substituir a chave na raiz
            printf("Raiz chaves[i]: %d\n", r->chaves[i]);
            //(*raiz) = r;
            criarArquivoDiretorio(r, r->NomeArquivo, nomeDiretorio); // Atualizar
            criarArquivoDiretorio(esquerda, esquerda->NomeArquivo, nomeDiretorio); // Atualizar filho
            free(esquerda);
            free(r);
            printf("Raiz chaves[i]: %d\n", r->chaves[i]);
            return 1;
        }

        // Se o filho à direita tem pelo menos t chaves, substituímos pela menor chave da subárvore direita
        NOARVOREB* direita = abrirArquivoDiretorio(r->filhos[i + 1], nomeDiretorio);
        if (direita->n >= r->t) {
            printf("Caso 2b\n");
            int menor = direita->chaves[0]; // Menor chave à direita
            //Remover o menor
            for(int j = 0; j < (direita->n) - 1; j++){
                direita->chaves[j] = direita->chaves[j+1];
            }
            direita->n--;
            //remocaoCLRS(menor, &direita); // Remover o menor
            r->chaves[i] = menor; // Substituir a chave na raiz
            printf("Raiz chaves[i]: %d\n", r->chaves[i]);
            //(*raiz) = r;
            criarArquivoDiretorio(r, r->NomeArquivo, nomeDiretorio); // Atualizar
            criarArquivoDiretorio(direita, direita->NomeArquivo, nomeDiretorio); // Atualizar filho
            free(direita);
            free(r);
            //printf("Raiz chaves[i]: %d\n", raiz->chaves[i]);
            return 1;
        }

        // Caso 2c: Se ambos os filhos têm t-1 chaves, fazemos merge
        else {
            // Unir os filhos esquerda e direita
            printf("Caso 2c\n");
            esquerda->chaves[esquerda->n] = r->chaves[i]; // Mover chave da raiz para o filho esquerdo
            for (int j = 0; j < direita->n; j++) {
                esquerda->chaves[esquerda->n + 1 + j] = direita->chaves[j]; // Copiar chaves do filho direito
            }
            esquerda->n += (direita->n + 1); // Atualizar número de chaves
            int k = 0;
            while(k < r->n && r->chaves[k] < chave){
                k++;
            }
            printf("AQUIII\n");
            for(int j = r->n-1; j>k; j--){
                r->chaves[j-1] = r->chaves[j];
                // strcpy(r->filhos[j], r->filhos[j+1]);
                printf("%d: %d\n",j, r->chaves[j]);
            }

            for(int j = i+1; j < r->n; j++){
                strcpy(r->filhos[j], r->filhos[j+1]);
            }
            r->n--; // Reduzir o número de chaves na raiz
            

            // Atualizar o arquivo
            criarArquivoDiretorio(esquerda, esquerda->NomeArquivo, nomeDiretorio);
            criarArquivoDiretorio(r, r->NomeArquivo, nomeDiretorio);
            free(direita);
            

            // Recursão para remover do nó esquerdo após a fusão
            remocaoCLRS(chave, &esquerda, nomeDiretorio);
            return 1;
        }
    }
    return 0;
}

// Função principal de remoção
void remocaoCLRS(int chave, NOARVOREB** raiz, char* nomeDiretorio){
    printf("\nInicio da remocao\n");
    printf("Folha: %d\n", (*raiz)->folha);
    for(int i = 0; i < (*raiz)->n; i++){
        printf("%d ", (*raiz)->chaves[i]);
    }
    printf("\n============\n");
    if ((*raiz)->folha) {
        NOARVOREB* r = *raiz;
        printf("\nRemocao Folha\n");
        remocaoFolha(chave, r, nomeDiretorio);  // Tratar a remoção de folhas
        return;
    } else {
        printf("\nRemocao No Interno\n");
        int a = remocaoNoInterno(chave, raiz, nomeDiretorio);  // Tratar a remoção de nós internos
        printf("Valor de a: %d\n", a);
        if (a) {
            return;
        }

        printf("Remocao caso 3\n");
        int b = remocaoCaso3(chave, &raiz, nomeDiretorio);
        printf("Valor de b: %d\n", b);
        if (b) {
            return;
        }

        // Busca binária e remoção recursiva em filhos
        int c = buscaBinariaNo(chave, (*raiz), 0, (*raiz)->n - 1);
        if (c < 0) {
            c = -c-1;
        }
        printf("Valor de c: %d\n", c);
        NOARVOREB * r = raiz;
        NOARVOREB* filho = abrirArquivoDiretorio(r->filhos[c], nomeDiretorio);
        printf("Arquivo filho: %s\n", filho->NomeArquivo);
        remocaoCLRS(chave, filho, nomeDiretorio);  // Chamada recursiva para o filho
    }
}

