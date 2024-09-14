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

// Fun��o para verificar se o arquivo raiz.dat existe no diret�rio
int verificarRaiz() {
    const char* caminho = "../Diretorios/Arvore";
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
        closedir(f); // Fecha o diret�rio se "raiz.dat" n�o for encontrado
    }
    return 0;
}

// Fun��o b�sica para criar um n� de �rvore B
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
        printf("Erro de cria��o do arquivo\n");
        return;
    }

    // Escreve o n�mero de chaves e a folha
    fwrite(&no->n, sizeof(int), 1, f);
    fwrite(&no->folha, sizeof(int), 1, f);

    // Grava as chaves
    fwrite(no->chaves, sizeof(int), no->n, f);

    fwrite(no->NomeArquivo, sizeof(char), strlen(no->NomeArquivo) + 1, f);  // Grava a string inteira, incluindo o terminador nulo

    // Aqui voc� pode adicionar c�digo para gravar os filhos, caso seja necess�rio.
    printf("Nome: %s\n", no->NomeArquivo);
    printf("Folha: %d\n", no->n);
    printf("Chaves: ");
    for(int i = 0; i < no->n; i++){
        printf("%d ", no->chaves[i]);
    }

    fclose(f);
}

//fun��o para criar um arquivo binario dentro de um diretorio no diretorio Arvore chamando a funcao criarArquivoBinario

void criarArquivoDiretorio(NOARVOREB *no, char *nome) {
    NOARVOREB *raiz = no;
    DIR *f = opendir("../Diretorios/Arvore");
    
    if (f == NULL) {
        printf("Erro ao abrir diret�rio\n");
        return;
    } else {
        // Cria o caminho completo para o arquivo
        char caminhoCompleto[250];
        snprintf(caminhoCompleto, sizeof(caminhoCompleto), "../Diretorios/Arvore/%s", nome);

        // Abre o arquivo bin�rio para escrita
        FILE *file = fopen(caminhoCompleto, "wb");
        if (file == NULL) {
            printf("Erro de cria��o do arquivo\n");
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
        // Escreve o n�mero de chaves e se o n� � folha
        fwrite(&no->n, sizeof(int), 1, file);
        fwrite(&no->folha, sizeof(int), 1, file);

        // Grava as chaves
        fwrite(no->chaves, sizeof(int), no->n, file);

        // Grava o NomeArquivo (string), garantindo que seja armazenada corretamente
        fwrite(nome, sizeof(char), strlen(nome) + 1, file);  // Inclui o terminador nulo

        // Aqui voc� pode adicionar c�digo para gravar os filhos, caso seja necess�rio.
        // Exemplo de grava��o dos filhos (caso aplic�vel):
        if (!no->folha) {
            // for (int i = 0; i < no->n + 1; i++) {
            //     fwrite(no->filhos[i], sizeof(char), strlen(no->filhos[i]) + 1, file);
            // 
            
            fwrite(no->filhos, sizeof(char), (no->n + 1) * 25, file);
        }

        // Exibe informa��es no console (opcional)
        // printf("Nome: %s\n", no->NomeArquivo);
        // printf("Folha: %d\n", no->folha);
        // printf("Chaves: ");
        // for (int i = 0; i < no->n; i++) {
        //     printf("%d ", no->chaves[i]);
        // }
        // printf("\n");

        // Fecha o arquivo bin�rio e o diret�rio
        fclose(file);
        closedir(f);
    }
}


//Fun��o para remover um arquivo bin�rio de um diret�rio, dado o seu nome
void removerArquivoDiretorio(char *nome){
    DIR *f = opendir("../Diretorios/Arvore");
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
                snprintf(caminhoCompleto, sizeof(caminhoCompleto), "../Diretorios/Arvore/%s", nome);
                remove(caminhoCompleto);
                closedir(f);
                return;
            }
        }
    }
}

//Fun��o para coletar um arquivo bin�rio de um diret�rio
NOARVOREB * coletarArquivoBinario(char *nome){
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
    DIR *f = opendir("./Diretorios/Arvore");
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
                printf("    ");  // Indenta��o para mostrar a profundidade
            }
            printf("%d\n", no->chaves[i]);

            if (!no->folha) {
                NOARVOREB * filho = coletarArquivoBinario(no->filhos[i]);
                imprimirArvoreB(filho, nivel + 1);
            }
        }
    }
}



//fun��o para procurar um nome de arquivo em um diret�rio
int procurarArquivoDiretorio(char *nome){
    DIR *f = opendir("../Diretorios/Arvore");
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
int buscarArvoreB(int chave, char* raiz){
    NOARVOREB* r = coletarArquivoBinario(raiz); //Descobrir modo para esse NOARVOREB receber o no armazenado no arquivo binario
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
        return buscarArvoreB(chave, r->filhos[i]);
    }
}

// Fun��o de busca bin�ria em um n�
int buscaBinariaNo(int chave, NOARVOREB* raiz, int limiteInferior, int limiteSuperior) {
    if (limiteInferior > limiteSuperior) {
        return -(limiteInferior + 1);  // Retorna �ndice negativo se n�o encontrado
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

// Fun��o para buscar uma chave na �rvore B binariamente
int buscarArvoreBBinariamente(int chave, char* raiz) {
    NOARVOREB* r = coletarArquivoBinario(raiz);
    
    int i = buscaBinariaNo(chave, r, 0, r->n - 1);
    if (i >= 0) {
        return i;
    }

    if (r->folha) {
        return -1;  // N�o encontrado
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
    // Carrega o n� filho y a partir do arquivo bin�rio correspondente
    NOARVOREB* y = coletarArquivoBinario(raiz->filhos[i]);  
    // Cria um novo n� z, que vai receber as metades das chaves de y
    NOARVOREB* z = criarNoArvoreB(t, y->folha);  
    z->n = t - 1;

    // Copia as �ltimas t-1 chaves de y para z
    for (int j = 0; j < t - 1; j++) {
        z->chaves[j] = y->chaves[j + t];
    }

    // Se y n�o for folha, transfere os filhos correspondentes para z
    if (!y->folha) {
        for (int j = 0; j < t; j++) {
            strcpy(z->filhos[j], y->filhos[j + t]);
        }
    }

    // Atualiza o n�mero de chaves em y
    y->n = t - 1;

    // Move os filhos de raiz para dar espa�o para o novo filho z
    for (int j = raiz->n; j >= i + 1; j--) {
        strcpy(raiz->filhos[j + 1], raiz->filhos[j]);
    }

    // Insere o ponteiro para o novo n� z
    strcpy(raiz->filhos[i + 1], z->NomeArquivo);

    // Move as chaves de raiz para dar espa�o para a nova chave
    for (int j = raiz->n; j >= i; j--) {
        raiz->chaves[j + 1] = raiz->chaves[j];
    }

    // Insere a chave do meio de y em raiz
    raiz->chaves[i] = y->chaves[t - 1];
    raiz->n++;

    // Exibe os nomes dos n�s para fins de depura��o
    printf("Nome x: %s\n", raiz->NomeArquivo);
    printf("Nome y: %s\n", y->NomeArquivo);
    printf("Nome z: %s\n", z->NomeArquivo);

    // Se o nome do arquivo raiz n�o for "raiz.dat", faz algumas trocas de nomes
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
        //Leitura do filho no arquivo bin�rio
        NOARVOREB* filho = coletarArquivoBinario(raiz->filhos[i]);
        printf("Arquivo filho: %s\n", filho->NomeArquivo);
        // printf("%d\n%d\n", filho->n, chave);
        // printf("%s\n", filho->NomeArquivo);
        printf("insere no filho\n");
        insercaoNaoCheioArvoreB(chave, filho);
        //printf("Valor de N: %d\n", filho->n);
        if (filho->n == 2 * t - 1) {
            printf("SPLIT DO N� FOLHA\n");
            splitChildArvoreB(raiz, i);
        }
    }
}


/// Fun��o para inser��o usando o m�todo CLRS
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
    DIR *f = opendir("../Diretorios/Arvore");
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
                snprintf(caminhoCompleto, sizeof(caminhoCompleto), "../Diretorios/Arvore/%s", entrada->d_name);
                remove(caminhoCompleto);
            }
        }
    }
    closedir(f);
}

//funcao para list diretorio sem parametros
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


//Funcao para remover CLRS
int remocaoCLRS(int chave, char* raiz){
    NOARVOREB* r = coletarArquivoBinario(raiz); //Descobrir modo para esse NOARVOREB receber o no armazenado no arquivo binario
    printf("Inicio da remocao\n");

    //Se a chave nao estiver presente na arvore, retornar null
    //Caso 1
    printf("Caso 1\n");
    if(r->folha){
        printf("Folha\n");
        //Se for folha e quando remover, a propriedade de elementos t-1 se manter
        if(r->n >= t-1){
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
            return 1;
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
        printf("caso 2\n");
        //Se a chave estiver em um no interno
        if(r->folha == 0 && buscaBinariaNo(chave, r, 0, r->n-1) > 0){
            int i = buscaBinariaNo(chave, r, 0, r->n-1);
            
            //Se o filho da esquerda for ficar com mais que t-1, roubar uma chave dele
            NOARVOREB* esquerda = coletarArquivoBinario(r->filhos[i]);
            if(esquerda->n >= t){
                r->chaves[i] = esquerda->chaves[(esquerda->n) - 1];
                esquerda->n = (esquerda->n) - 1;
                criarArquivoDiretorio(esquerda, esquerda->NomeArquivo);
                free(esquerda);
                return 1;
            }

            //Se o filho da direita for ficar com mais que t-1, roubar uma chave dele
            NOARVOREB* direita = coletarArquivoBinario(r->filhos[i+1]);
            if(direita->n >= t){
                r->chaves[i] = direita->chaves[0];
                direita->n = (direita->n) - 1;
                for(int j = 0; j < direita->n; j++){
                    direita->chaves[j] = direita->chaves[j+1];
                }
                criarArquivoDiretorio(direita, direita->NomeArquivo);
                free(direita);
                return 1;
            }
        
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
                    
                strcpy(r->filhos[i], merge->NomeArquivo);
                r->n = (r->n) - 1;

                criarArquivoDiretorio(r, r->NomeArquivo);
                criarArquivoDiretorio(merge, esquerda->NomeArquivo);

                free(esquerda);
                free(direita);
                free(merge);
                return 1;
            }
        }
        
        else{
            //Implementar casos 3 (quando chave nao esta em um no, mas ele e interno)
            int i = -buscaBinariaNo(chave, r, 0, r->n-1);

            //Caso for remover do filho da esquerda
            NOARVOREB* esquerda = coletarArquivoBinario(r->filhos[i]);
            NOARVOREB* direita = coletarArquivoBinario(r->filhos[i+1]);
            if(esquerda->n == (r->t) - 1){
                if(direita->n >= r->t){
                    

                    esquerda->chaves[esquerda->n] = r->chaves[i];
                    r->chaves[i] = direita->chaves[0];
                    for(int j = 0; j < direita->n - 1; j++){
                        direita->chaves[j] = direita->chaves[j+1];
                    }
                    criarArquivoDiretorio(esquerda, esquerda->NomeArquivo);
                    criarArquivoDiretorio(direita, direita->NomeArquivo);

                    free(esquerda);
                    free(direita);
                    return 1;
                }
                else{

                    //Caso for remover do filho da direita
                    if(esquerda->n >= r->t){
                        NOARVOREB* esquerda = coletarArquivoBinario(r->filhos[i-1]);
                        NOARVOREB* direita = coletarArquivoBinario(r->filhos[i]);

                        direita->chaves[0] = r->chaves[i];
                        r->chaves[i] = esquerda->chaves[esquerda->n - 1];
                        criarArquivoDiretorio(esquerda, esquerda->NomeArquivo);
                        criarArquivoDiretorio(direita, direita->NomeArquivo);

                        free(esquerda);
                        free(direita);
                        return 1;
                    }
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
                        criarArquivoDiretorio(esquerda, esquerda->NomeArquivo);

                        free(esquerda);
                        free(direita);
                        return 1;
                    }
                }
            }
        }
    }
}

void remocao(int chave, char* raiz){
    NOARVOREB* r= coletarArquivoBinario(raiz);

    if(!buscarArvoreB(chave, raiz)){
        return;
    }

    int i = buscaBinariaNo(chave, r, 0, (r->n) - 1);
    i = -i;
    if(!remocaoCLRS(chave, raiz)){
        remocaoCLRS(chave, r->filhos[i]);
    }
}

int remocaoCLRS2(int chave, NOARVOREB** raiz){
    //NOARVOREB* r = coletarArquivoBinario(&raiz); // Coletando o n� armazenado no arquivo bin�rio
    NOARVOREB* r = *raiz;

    // Caso 1: A chave est� em uma folha
    if (r->folha) {
        printf("Caso 1\n");
        int i = 0;
        while (i < r->n && r->chaves[i] < chave) {
            i++;
        }

        // Se a chave foi encontrada, remov�-la
        if (i < r->n && r->chaves[i] == chave) {
            for (int j = i; j < r->n - 1; j++) {
                r->chaves[j] = r->chaves[j + 1]; // Movendo chaves
            }
            r->n--; // Atualizando o n�mero de chaves

            // Atualizando o n� no arquivo bin�rio
            criarArquivoDiretorio(r, r->NomeArquivo);
            free(r);
            return 1;
        }
        // Se a chave n�o foi encontrada, retornar erro
        free(r);
        return 0;
    }

    // Caso 2: A chave est� em um n� interno
    int i = buscaBinariaNo(chave, r, 0, r->n - 1); // Busca bin�ria para encontrar a posi��o da chave
    if (i >= 0) {
        // Se o filho � esquerda tem pelo menos t chaves, substitu�mos pela maior chave do sub�rvore esquerda
        NOARVOREB* esquerda = coletarArquivoBinario(r->filhos[i]);
        if (esquerda->n >= t) {
            printf("Caso 2a\n");
            int maior = esquerda->chaves[esquerda->n - 1]; // Maior chave � esquerda
            
            remocaoCLRS2(maior, &esquerda); // Remover o maior
            r->chaves[i] = maior; // Substituir a chave na raiz
            printf("Raiz chaves[i]: %d\n", r->chaves[i]);
            (*raiz) = r;
            criarArquivoDiretorio(r, r->NomeArquivo); // Atualizar
            criarArquivoDiretorio(esquerda, esquerda->NomeArquivo); // Atualizar filho
            free(esquerda);
            free(r);
            printf("Raiz chaves[i]: %d\n", r->chaves[i]);
            return 1;
        }

        // Se o filho � direita tem pelo menos t chaves, substitu�mos pela menor chave do sub�rvore direita
        NOARVOREB* direita = coletarArquivoBinario(r->filhos[i + 1]);
        if (direita->n >= t) {
            printf("Caso 2b\n");
            int menor = direita->chaves[0]; // Menor chave � direita
            remocaoCLRS2(menor, &direita); // Remover o menor
            r->chaves[i] = menor; // Substituir a chave na raiz
            printf("Raiz chaves[i]: %d\n", r->chaves[i]);
            (*raiz) = r;
            criarArquivoDiretorio(r, r->NomeArquivo); // Atualizar
            criarArquivoDiretorio(direita, direita->NomeArquivo); // Atualizar filho
            free(direita);
            free(r);
            printf("Raiz chaves[i]: %d\n", (*raiz)->chaves[i]);
            return 1;
        }

        // Caso 2c: Se ambos os filhos t�m t-1 chaves, fazemos merge
        else {
            // Unir os filhos esquerda e direita
            printf("Caso 2c\n");
            esquerda->chaves[esquerda->n] = r->chaves[i]; // Mover chave da raiz para o filho esquerdo
            for (int j = 0; j < direita->n; j++) {
                esquerda->chaves[esquerda->n + 1 + j] = direita->chaves[j]; // Copiar chaves do filho direito
            }
            esquerda->n += direita->n + 1; // Atualizar n�mero de chaves
            r->n--; // Reduzir o n�mero de chaves na raiz

            // Atualizar o arquivo
            criarArquivoDiretorio(esquerda, esquerda->NomeArquivo);
            criarArquivoDiretorio(r, r->NomeArquivo);
            free(direita);

            // Recurs�o para remover do n� esquerdo ap�s a fus�o
            return remocaoCLRS2(chave, &esquerda);
        }
    }

    // Caso 3: Se a chave n�o est� em um n� interno, descer recursivamente
    i = -i - 1; // Ajustar o �ndice para filho apropriado
    NOARVOREB* filho = coletarArquivoBinario(r->filhos[i]);

    // Caso 3a: Se o filho tem apenas t-1 chaves, fazemos o balanceamento
    if (filho->n == r->t - 1) {
        NOARVOREB* irmaoEsquerdo = (i > 0) ? coletarArquivoBinario(r->filhos[i - 1]) : NULL;
        NOARVOREB* irmaoDireito = (i < r->n) ? coletarArquivoBinario(r->filhos[i + 1]) : NULL;

        // Emprestar do irm�o esquerdo
        if (irmaoEsquerdo && irmaoEsquerdo->n >= r->t) {
            printf("Caso 3a\n");
            for (int j = filho->n; j > 0; j--) {
                filho->chaves[j] = filho->chaves[j - 1];
            }
            filho->chaves[0] = r->chaves[i - 1]; // Pegar chave da raiz
            r->chaves[i - 1] = irmaoEsquerdo->chaves[irmaoEsquerdo->n - 1]; // Atualizar raiz
            filho->n++;
            irmaoEsquerdo->n--;

            criarArquivoDiretorio(irmaoEsquerdo, irmaoEsquerdo->NomeArquivo);
            criarArquivoDiretorio(filho, filho->NomeArquivo);
        }
        // Emprestar do irm�o direito
        else if (irmaoDireito && irmaoDireito->n >= r->t) {
            printf("Caso 3a\n");
            filho->chaves[filho->n] = r->chaves[i]; // Pegar chave da raiz
            r->chaves[i] = irmaoDireito->chaves[0]; // Atualizar raiz
            for (int j = 0; j < irmaoDireito->n - 1; j++) {
                irmaoDireito->chaves[j] = irmaoDireito->chaves[j + 1]; // Mover chaves no irm�o direito
            }
            filho->n++;
            irmaoDireito->n--;

            criarArquivoDiretorio(irmaoDireito, irmaoDireito->NomeArquivo);
            criarArquivoDiretorio(filho, filho->NomeArquivo);
        }
        // Fazer merge com o irm�o direito se n�o puder emprestar
        else if (irmaoDireito) {
            printf("Caso 3b\n");
            filho->chaves[filho->n] = r->chaves[i]; // Mover chave da raiz para o filho
            for (int j = 0; j < irmaoDireito->n; j++) {
                filho->chaves[filho->n + 1 + j] = irmaoDireito->chaves[j]; // Copiar chaves do irm�o direito
            }
            filho->n += irmaoDireito->n + 1;
            r->n--;

            criarArquivoDiretorio(filho, filho->NomeArquivo);
            criarArquivoDiretorio(r, r->NomeArquivo);
            free(irmaoDireito);
        }
    }

    free(filho);
    free(r);

    return remocaoCLRS2(chave, &filho);
}

void remocao2(int chave, NOARVOREB** raiz){
    char* nome = (char*) malloc(25*sizeof(char));
    strcpy(nome, (*raiz)->NomeArquivo);

    if (!buscarArvoreB(chave, nome)) {
        return;
    }

    remocaoCLRS2(chave, raiz); // Chamada para a fun��o de remo��o
    free(raiz);
}

