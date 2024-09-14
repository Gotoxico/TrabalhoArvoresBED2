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
    no->chaves = (int) malloc((2*t - 1) * sizeof(int));
    no->filhos = (char*) malloc((2*t) * sizeof(char*));
    for (int i = 0; i < 2 * t; i++) {
        no->filhos[i] = (char*) malloc(25 * sizeof(char));  // ou o tamanho adequado
    }
    no->folha = folha;
    no->NomeArquivo = (char*) malloc(25 * sizeof(char));
    //strncpy(no->NomeArquivo, geradorNomeArquivo(), 25);
    strcpy(no->NomeArquivo , geradorNomeArquivo());
    
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

    fwrite(no->NomeArquivo, sizeof(char), strlen(no->NomeArquivo) + 1, f);  // Grava a string inteira, incluindo o terminador nulo

    // Aqui você pode adicionar código para gravar os filhos, caso seja necessário.
    printf("Nome: %s\n", no->NomeArquivo);
    printf("Folha: %d\n", no->n);
    printf("Chaves: ");
    for(int i = 0; i < no->n; i++){
        printf("%d ", no->chaves[i]);
    }

    fclose(f);
}

//função para criar um arquivo binario dentro de um diretorio no diretorio Arvore chamando a funcao criarArquivoBinario

void criarArquivoDiretorio(NOARVOREB *no, char *nome) {
    NOARVOREB *raiz = no;
    DIR *f = opendir("../Arvore");
    
    if (f == NULL) {
        printf("Erro ao abrir diretório\n");
        return;
    } else {
        // Cria o caminho completo para o arquivo
        char caminhoCompleto[250];
        snprintf(caminhoCompleto, sizeof(caminhoCompleto), "../Arvore/%s", nome);

        // Abre o arquivo binário para escrita
        FILE *file = fopen(caminhoCompleto, "wb");
        if (file == NULL) {
            printf("Erro de criação do arquivo\n");
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
        // Escreve o número de chaves e se o nó é folha
        fwrite(&no->n, sizeof(int), 1, file);
        fwrite(&no->folha, sizeof(int), 1, file);

        // Grava as chaves
        fwrite(no->chaves, sizeof(int), no->n, file);

        // Grava o NomeArquivo (string), garantindo que seja armazenada corretamente
        fwrite(nome, sizeof(char), strlen(nome) + 1, file);  // Inclui o terminador nulo

        // Aqui você pode adicionar código para gravar os filhos, caso seja necessário.
        // Exemplo de gravação dos filhos (caso aplicável):
        if (!no->folha) {
            // for (int i = 0; i < no->n + 1; i++) {
            //     fwrite(no->filhos[i], sizeof(char), strlen(no->filhos[i]) + 1, file);
            // 
            
            fwrite(no->filhos, sizeof(char), (no->n + 1) * 25, file);
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
                //no->chaves = (int *)malloc(no->n * sizeof(int));
                fread(no->chaves, sizeof(int), no->n, bf);
                fread(no->NomeArquivo, sizeof(char), 25, bf);
                if(!no->folha){ 
                    fread(no->filhos, sizeof(char), (no->n + 1) * 25, bf);
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

void imprimirArvoreB(NOARVOREB* no, int nivel) {
    if (no != NULL) {
        int i;
        
        // Primeiro imprimir o lado direito (maiores)
        if (!no->folha) {
            NOARVOREB * filho = coletarArquivoBinario(no->filhos[no->n]);
            imprimirArvoreB(filho, nivel + 1);
        }

        // Depois imprimir as chaves e os filhos da esquerda
        for (i = no->n - 1; i >= 0; i--) {
            for (int j = 0; j < nivel; j++) {
                printf("    ");  // Indentação para mostrar a profundidade
            }
            printf("%d\n", no->chaves[i]);

            if (!no->folha) {
                NOARVOREB * filho = coletarArquivoBinario(no->filhos[i]);
                imprimirArvoreB(filho, nivel + 1);
            }
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
int buscarArvoreB(int chave, char** raiz){
    NOARVOREB* r = coletarArquivoBinario(raiz); //Descobrir modo para esse NOARVOREB receber o no armazenado no arquivo binario
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

void splitChildArvoreB(NOARVOREB* raiz, int i) {
    // Carrega o nó filho y a partir do arquivo binário correspondente
    NOARVOREB* y = coletarArquivoBinario(raiz->filhos[i]);  
    // Cria um novo nó z, que vai receber as metades das chaves de y
    NOARVOREB* z = criarNoArvoreB(t, y->folha);  
    z->n = t - 1;

    // Copia as últimas t-1 chaves de y para z
    for (int j = 0; j < t - 1; j++) {
        z->chaves[j] = y->chaves[j + t];
    }

    // Se y não for folha, transfere os filhos correspondentes para z
    if (!y->folha) {
        for (int j = 0; j < t; j++) {
            strcpy(z->filhos[j], y->filhos[j + t]);
        }
    }

    // Atualiza o número de chaves em y
    y->n = t - 1;

    // Move os filhos de raiz para dar espaço para o novo filho z
    for (int j = raiz->n; j >= i + 1; j--) {
        strcpy(raiz->filhos[j + 1],raiz->filhos[j]);
    }

    // Insere o ponteiro para o novo nó z
    strcpy(raiz->filhos[i + 1], z->NomeArquivo);

    // Move as chaves de raiz para dar espaço para a nova chave
    for (int j = raiz->n; j >= i; j--) {
        raiz->chaves[j + 1] = raiz->chaves[j];
    }

    // Insere a chave do meio de y em raiz
    raiz->chaves[i] = y->chaves[t - 1];
    raiz->n++;

    // Exibe os nomes dos nós para fins de depuração
    printf("Nome x: %s\n", raiz->NomeArquivo);
    printf("Nome y: %s\n", y->NomeArquivo);
    printf("Nome z: %s\n", z->NomeArquivo);

    // Se o nome do arquivo raiz não for "raiz.dat", faz algumas trocas de nomes
    //     printf("Aqui\n");
    //     strcpy(raiz->filhos[i], raiz->NomeArquivo);
    //     strcpy(raiz->NomeArquivo, y->NomeArquivo);
    //     criarArquivoDiretorio(y, raiz->filhos[i]);
    //     criarArquivoDiretorio(z, z->NomeArquivo);
    //     criarArquivoDiretorio(raiz, raiz->NomeArquivo);

    // } else {
        // Se for a raiz, grava os arquivos correspondentes
        //strcpy(raiz->filhos[i], y->NomeArquivo);
        printf("\nCRIACAO DO DIRETORIO Y\n");
        criarArquivoDiretorio(y, y->NomeArquivo);
        printf("\nCRIACAO DO DIRETORIO Z\n");
        criarArquivoDiretorio(z, z->NomeArquivo);
        printf("\nCRIACAO DO DIRETORIO RAIZ\n");
        criarArquivoDiretorio(raiz, raiz->NomeArquivo);
        printf("\n");
        
}


void insercaoNaoCheioArvoreB(int chave, NOARVOREB * raiz) {

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
      
        criarArquivoDiretorio(raiz, raiz->NomeArquivo);
//         printf("Insercao\n");
// -       printf("\n");
    } else {
        printf("\nINSERCAO NAO FOLHA\n"); 
        while (i >= 0 && chave < raiz->chaves[i]) {
            i--;
        }
        i++;
        //Leitura do filho no arquivo binário
        NOARVOREB* filho = coletarArquivoBinario(raiz->filhos[i]);
        printf("Arquivo filho: %s\n", filho->NomeArquivo);
        // printf("%d\n%d\n", filho->n, chave);
        // printf("%s\n", filho->NomeArquivo);
        printf("insere no filho\n");
        insercaoNaoCheioArvoreB(chave, filho);
        //printf("Valor de N: %d\n", filho->n);
        if (filho->n == 2 * t - 1) {
            printf("SPLIT DO NÓ FOLHA\n");
            splitChildArvoreB(raiz, i);
        }
    }
}


/// Função para inserção usando o método CLRS
void insercaoCLRS(int chave, NOARVOREB ** raiz) {
    
   NOARVOREB* r = *raiz;
   printf("\n===========================================");
   printf("\nINICIO DA INSERCAO A PARTIR DA RAIZ\n");
    insercaoNaoCheioArvoreB(chave, r);
    if (r->n == (2 * t - 1)) {
        printf("\nSPLIT DA RAIZ CHEIA\n");
        NOARVOREB* s = criarNoArvoreB(t, 0);
        strcpy(s->filhos[0], r->NomeArquivo);
        //insercaoNaoCheioArvoreB(chave, r);
        splitChildArvoreB(s, 0);

        *raiz = s;

    } 
    printf("\n===========================================\n");
}

//funcao para remover todos os arquivos de um diretorio
void removerArquivosDiretorio(){
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
            if(strcmp(entrada->d_name, ".") != 0 && strcmp(entrada->d_name, "..") != 0){
                char caminhoCompleto[250];
                snprintf(caminhoCompleto, sizeof(caminhoCompleto), "../Arvore/%s", entrada->d_name);
                remove(caminhoCompleto);
            }
        }
    }
    closedir(f);
}


//Funcao para remover CLRS
void remocaoCLRS(int chave, char** raiz){
    NOARVOREB* r = coletarArquivoBinario(raiz); //Descobrir modo para esse NOARVOREB receber o no armazenado no arquivo binario
    int presenca = buscarArvoreB(chave, raiz);
    //Se a chave nao estiver presente na arvore, retornar null
    if(presenca == -1){
        return;
    }
    else{
        //Caso 1
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
                criarArquivoDiretorio(r, r->NomeArquivo);
                return;
            }
            //Se a propriedade nao se manter, pegar o mais a direita do irmao da esquerda ou o mais a esquerda do irmao da direita e unir, ou entao se os dois possuem t-1, agrupar
            /*else{
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
            }*/
        }

        //Casos 2a, 2b e 2c
        else{
            //Se a chave estiver em um no interno
            if(r->folha == 0 && buscaBinariaNo(chave, r, 0, r->n-1) > 0){
                int i = buscaBinariaNo(chave, r, 0, r->n-1);
                
                //Se o filho da esquerda for ficar com mais que t-1, roubar uma chave dele
                NOARVOREB* esquerda = coletarArquivoBinario(r->filhos[i]);
                if(esquerda->n >= t){
                    r->chaves[i] = esquerda->chaves[(esquerda->n) - 1];
                    esquerda->n = (esquerda->n) - 1;
                }
                criarArquivoDiretorio(esquerda, esquerda->NomeArquivo);
                free(esquerda);

                //Se o filho da direita for ficar com mais que t-1, roubar uma chave dele
                NOARVOREB* direita = coletarArquivoBinario(r->filhos[i+1]);
                if(direita->n >= t){
                    r->chaves[i] = direita->chaves[0];
                    direita->n = (direita->n) - 1;
                    for(int j = 0; j < direita->n; j++){
                        direita->chaves[j] = direita->chaves[j+1];
                    }
                }
                criarArquivoDiretorio(direita, direita->NomeArquivo);
                free(direita);

                //Criar um no com merge como filho de r
                else{
                    NOARVOREB* esquerda = coletarArquivoBinario(r->filhos[i]);
                    int folha = esquerda->folha;
                    int t = esquerda->t;
                    NOARVOREB* merge = criarNoArvoreB(t, folha);

                    //Filho esquerdo
                    for(int a = 0; a < esquerda->n; a++){
                        merge->chaves[a] = esquerda->chaves[a];
                        merge->n = merge->n + 1;
                    }
                    
                    //Filho direito
                    NOARVOREB* direita = coletarArquivoBinario(r->filhos[i+1]);
                    for(int a = (merge->n), j = 0; a < direita->n; a++, j++){
                        merge->chaves[a] = direita->chaves[j];
                        merge->n = merge->n + 1;
                    }
                    
                    //Arrumando os indexes da raiz, o apontamento de filho e a quantidade de chaves
                    for(int j = i; j < (r->n) - 1; j++){
                        r->chaves[j] = r->chaves[j+1];
                    }
                        
                    strcpy(r->filhos[i], merge->nomeArquivo);
                    r->n = (r->n) - 1;

                    criarArquivoDiretorio(r, r->NomeArquivo);
                    criarArquivoDiretorio(merge, merge->nomeArquivo);

                    free(esquerda);
                    free(direita);
                    free(merge);
                }
            }
            
            else{
                //Implementar casos 3 (quando chave nao esta em um no, mas ele e interno)
                int i = -buscaBinariaNo(chave, r, 0, r->n-1);
                NOARVOREB* esquerda = coletarArquivoBinario(r->filhos[i]);
                NOARVOREB* direita = coletarArquivoBinario(r->filhos[i+1]);

                //Caso for remover do filho da esquerda
                if(esquerda->n == (r->t) - 1){
                    if(direita->n >= r->t)){
                        esquerda->chaves[esquerda->n] = r->chaves[i];
                        r->chaves[i] = direita->chaves[0];
                        for(int j = 0; j < direita->n - 1; j++){
                            direita->chaves[j] = direita->chaves[j+1];
                        }
                    }

                    criarArquivoDiretorio(esquerda, esquerda->nomeArquivo);
                    criarArquivoDiretorio(direita, direita->nomeArquivo);

                    free(esquerda);
                    free(direita);
                    
                    else{
                        NOARVOREB* esquerda = coletarArquivoBinario(r->filhos[i-1]);
                        NOARVOREB* direita = coletarArquivoBinario(r->filhos[i]);

                        //Caso for remover do filho da direita
                        if(esquerda->n >= r->t){
                            direita->chaves[0] = r->chaves[i];
                            r->chaves[i] = esquerda->chaves[esquerda->n - 1];
                        }

                        criarArquivoDiretorio(esquerda, esquerda->nomeArquivo);
                        criarArquivoDiretorio(direita, direita->nomeArquivo);

                        free(esquerda);
                        free(direita);

                        else{
                            //Caso 3b, juntando o no filho[i] com o irmao da esquerda e utilizando uma chave da raiz como mediana
                            NOARVOREB* esquerda = coletarArquivoBinario(r->filhos[i-1]);
                            NOARVOREB* direita = coletarArquivoBinario(r->filhos[i]);
                            int j = esquerda->n;
                            esquerda->chaves[j] = r->chaves[i];
                            r->n = r->n - 1;
                            for(int a = j + 1, b = 0; b < direita->n; a++, b++){
                                esquerda->chaves[a] = direita->chaves[b]; 
                            }

                            criarArquivoDiretorio(r, r->NomeArquivo);
                            criarArquivoDiretorio(esquerda, esquerda->nomeArquivo);

                            free(esquerda);
                            free(direita);
                        }
                    }
                }
            }
        }
        remocaoCLRS(chave, r->filhos[i]);
    }
}

//Funcao para gerar nome aleatoriamente
char* geradorNomeArquivo(){
    char letras[26];
    for(int i = 0; i < 26; i++){
        letras[i] = 'a' + i;
    }

    char *caminho[24] = ".dat";
    for(int i = 0; i < 20; i++){
        memmove(*caminho + 1, *caminho, strlen(*caminho) + 1);
        int letra = rand() % 26;
        *caminho[0] = letras[letra];
    }

    return *caminho;
}

//Funcao para criar arquivo binario
char** criarArquivoBinario(char nome){
    FILE* f = fopen(nome, "wb");
    if(f == NULL){
        printf("Erro de criacao\n");
        return;
    }

    fclose(f);
    return nome;
}

//Funcao para criar o arquivo no diretorio
void criarArquivoDiretorio(NOARVOREB* no){
    DIR *f = opendir("../Arvore");
    struct dirent* entrada;
    int arquivos = 0;
    if(f == NULL){
        printf("Erro ao abrir diretorio\n");
        return;
    }

    else{
        char nome[24] = strcpy(geradorNomeArquivo(), nome);
        while(entrada=readdir(f)){
            arquivos++;
            if(strcmp(entrada->d_name, nome) == 0){
                closedir(f);
                criarArquivoDiretorio(&no);
                return;
            }
        }
        criarArquivoBinario(nome);
        FILE* bf = fopen(nome, "wb");

        fwrite(&no->n, sizeof(int), 1, bf);
        fwrite(&no->chaves, sizeof(int), (2 * no->t - 1), bf);
        for(int i = 0; i < (2 * no->t); i++){
            fwrite(no->filhos[i], sizeof(char), 24, bf);
        }
        fwrite(&no->folha, sizeof(int), 1, bf);
        fwrite(&no->t, sizeof(int), 1, bf);

        fclose(bf);
    }
}

//Funcao para ler um arquivo binario e criar no baseado em suas informacoes, no entanto de tras pra frente do arquivo binario
NOARVOREB* coletarArquivoBinario(char** nome){
    DIR *f = opendir("./Arvore");
    struct dirent* entrada;
    int arquivos = 0;
    
    if(f == NULL){
        printf("Erro de leitura\n");
        return;
    }

    else{
        while(entrada=readdir(f)){
            arquivos++;
            if(strcmp(entrada->d_name, nome) == 0){
                int t, folha;
                FILE *bf = fopen(nome, "rb");
                if(bf == NULL){
                    printf("Erro ao abrir arquivo\n");
                    return;
                }

                fseek(bf, -sizeof(int), SEEK_END);
                fread(&t, sizeof(int), 1, bf);
                fseek(bf, -sizeof(int), SEEK_CUR);
                fread(&folha, sizeof(int), 1, bf);
                NOARVOREB* raiz = criarNoArvoreB(t, folha);

                for(int i = 0; i < 2 * t; i++){
                    fseek(bf, -(24 * sizeof(char*)), SEEK_CUR);
                    fread(&raiz->filhos[i], sizeof(char*), 24, bf);
                }
                
                fseek(bf, - (2*t - 1) * sizeof(int), SEEK_CUR);
                fread(&raiz->chaves, sizeof(int), (2 * t - 1), bf);
                
                
                fseek(bf, -sizeof(int), SEEK_CUR);
                fread(&raiz->n, sizeof(int), 1, bf);

                return raiz;

                fclose(bf);
            }
        }
        closedir(f);
    }
}


// Funï¿½ï¿½o de impressï¿½o da ï¿½rvore B
void imprimirArvoreB(NOARVOREB* no, int nivel) {
    if (no != NULL) {
        int i;
        for (i = 0; i < no->n; i++) {
            if (!no->folha) {
                imprimirArvoreB(no->filhos[i], nivel + 1);
            }
            for (int j = 0; j < nivel; j++) {
                printf("    ");  // Indentaï¿½ï¿½o para mostrar a profundidade
            }
            printf("%d\n", no->chaves[i]);
        }
        if (!no->folha) {
            imprimirArvoreB(no->filhos[i], nivel + 1);
        }
    }
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
        while(entrada=readdir(f)){
            arquivos++;
            NOARVOREB* raiz = coletarArquivoBinario(entrada->d_name);
            if(raiz->folha == 0){
                printf("Arquivo %d: %s\n", i, entrada->d_name);
                i++;
            }
        }
    }
}

void criarDiretorio(){
    const char* nomeDiretorio;
    printf("Digite nome: \n");
    scanf("%s", &nomeDiretorio);
    if(_mkdir(nomeDiretorio == 0)){
        printf("Diretorio criado\n");
        return;
    }
    else{
        perror("Criacao mal sucedida\n");
        return criarDiretorio();
    }
}
