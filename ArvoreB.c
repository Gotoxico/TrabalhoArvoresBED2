#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "ArvoreB.h"
int t = 3;
//Funcao basica pra criar um no
NOARVOREB* criarNoArvoreB(int t, int folha){
    NOARVOREB* no = (NOARVOREB*) malloc(sizeof(NOARVOREB));
    no->n = 0;
    no->chaves = (int*) malloc(sizeof((2*t-1) * sizeof(int)));
    no->filhos = (char**) malloc(sizeof(2*t) * sizeof(char*));
    no->folha = folha;
    return no;
}

//Buscar presenca de um no na arvore e retornar a posicao em relacao ao vetor de chaves do no
int buscarArvoreB(int chave,  char  * raiz){
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

//Funcao para buscar binariamente uma chave dentro de um no e retornar posicao negativa em relacao ao vetor de nos se a chave nao estiver, e posicao positiva se estiver
int buscaBinariaNo(int chave, NOARVOREB* raiz, int limiteInferior, int limiteSuperior){
    int meio = (limiteInferior+limiteSuperior)/2;
    if(limiteInferior > limiteSuperior){
        return -meio;
    }

    if(raiz->chaves[meio] == chave){
        return meio;
    }
    if(raiz->chaves[meio] > chave){
        buscaBinariaNo(chave, raiz, limiteInferior, meio - 1);
    }
    else{
        buscaBinariaNo(chave, raiz, meio + 1, limiteSuperior);
    }
}

//Funcao para buscar binariamente uma chave numa arvore
int buscarArvoreBBinariamente(int chave, NOARVOREB* raiz) {
    int i = buscaBinariaNo(chave, raiz, 0, raiz->n - 1);
    //Descobrir modo para esse NOARVOREB receber o no armazenado no arquivo binario
    if (i >= 0) {
        return i;
    }

    if (raiz->folha) {
        return -1;  // Não encontrado
    }

    char* proximoFilho = raiz->filhos[-i - 1];
    return buscarArvoreBBinariamente(chave, proximoFilho);
}

//Funcao para dividir chaves e filhos entre filhos y e z de raiz
NOARVOREB* splitChildArvore(int chave, NOARVOREB* raiz){
   NOARVOREB* y = raiz->filhos[chave];
    NOARVOREB* z = criarNoArvoreB(t, y->folha);
    z->n = t - 1;

    //Copia chaves de y para z
    for(int j = 1; j < t; j++){
        z->chaves[j] = y->chaves[j+t];
    }

    //Se y for no interno, copia filhos de y para z
    if(y->folha == 0){
        for(int j = 1; j < t+1; j++){
            z->filhos[j] = y->filhos[j+t];
        }
    }
    //Modifica quantidade de chaves em y
    y->n = t-1;

    //Move os apontadores para a direita ate a chave
    for(int j = raiz->n+1; j > chave; j--){
        raiz->filhos[j+1] = raiz->filhos[j];
    }
    //Aponta z como um dos filhos de raiz
    raiz->filhos[chave+1] = z;

    //Move as chaves para a direita ate a chave - 1
    for(int j = raiz->n; j > chave-1; j--){
        raiz->chaves[j+1] = raiz->chaves[j];
    }
    raiz->chaves[chave] = y->chaves[t];
    raiz->n = raiz->n+1;
    //Escrever no y em arquivo binario
    //Escrever no z em arquivo binario
    //Escrever no raiz em arquivo binario
}

//Funcao para inserir por metodo CLRS que utiliza as funcoes splitChildArvoreB e insercaoNaoCheioArvoreB
// Função para inserção usando o método CLRS
void insercaoCLRS(int chave, NOARVOREB** raiz) {
    NOARVOREB* r = *raiz;
    if (r->n == 2 * t - 2) {
        NOARVOREB* s = criarNoArvoreB(t, 0);
        s->filhos[0] = r;
        insercaoNaoCheioArvoreB(chave, r);
        splitChildArvoreB(s, 0);
        *raiz = s;
    } else {
        insercaoNaoCheioArvoreB(chave, r);
    }
}


//Funcao para inserir em um no nao cheio
void insercaoNaoCheioArvoreB(int chave, NOARVOREB* raiz) {
    int i = raiz->n - 1;

    if (raiz->folha) {
        while (i >= 0 && chave < raiz->chaves[i]) {
            raiz->chaves[i + 1] = raiz->chaves[i];
            i--;
        }
        raiz->chaves[i + 1] = chave;
        raiz->n++;
    } 
    //Se for no interno, encontrar um filho
    else {
        while (i >= 0 && chave < raiz->chaves[i]) {
            i--;
        }
        i++;
        NOARVOREB* filho = raiz->filhos[i];
        insercaoNaoCheioArvoreB(chave, raiz->filhos[i]);
        if (filho->n == 2 * t - 1) {
            splitChildArvoreB(raiz, i);
        }
    }
}


/*//Funcao para buscar o pai de um no 
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
}*/

//Funcao para remover CLRS
NOARVOREB* remocaoCLRS(int chave, char** raiz){
    NOARVOREB* r = raiz; //Descobrir modo para esse NOARVOREB receber o no armazenado no arquivo binario
    int presenca = buscarArvoreB(chave, raiz);
    //Se a chave nao estiver presente na arvore, retornar null
    if(presenca == NULL){
        return NULL;
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
                if(pai->filhos[i-1].n > t-1){
                    pai->filhos[i].chaves[(pai->filhos[i].n)+1] = pai->filhos[i-1].chaves[(pai->filhos[i].n)];
                    pai->filhos[i].n = pai->filhos[i].n + 1;
                    pai->filhos[i-1].n = pai->filhos[i-1] - 1;
                }
                else{
                    if(pai->filhos[i+1].n > t-1){
                        pai->filhos[i].chaves[(pai->filhos[i].n)+1] = pai->filhos[i+1].chaves[(pai->filhos[i].n)];
                        pai->filhos[i].n = pai->filhos[i].n + 1;
                        pai->filhos[i+1].n = pai->filhos[i+1].n - 1;
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
                if(r->filhos[i].n >= t){
                    r->chaves[i] = r->filhos[i].chaves[r->filhos[i].n];
                    r->filhos[i].n = (r->filhos[i].n)-1;
                }
                //Se o filho da direita for ficar com mais que t-1, roubar uma chave dele
                if(r->filhos[i+1].n >= t){
                    r->chaves[i] = r->filhos[i+1].chaves[0];
                    r->filhos[i+1].n = (r->filhos[i+1].n)-1;
                }
                //Criar um no com merge como filho de r
                else{
                    int folha = r->filhos[i].folha;
                    NOARVOREB* merge = criarNoArvoreB(t, folha);
                    for(int i = 0; i < r->filhos[i].n; i++){
                        merge[i] = r->filhos[i];
                        merge->n = merge->n + 1;
                    }
                    for(int i = (merge->n)+1, j = 0; i < r->filhos[i+1].n, j < r->filhos[i+1].n; i++, j++){
                        merge[i] = r->filhos[j];
                        merge->n = merge->n + 1;
                    }
                    
                    for(int j = i; j <= (r->n) - i - 1; j++){
                        r->chaves[j] = r->chaves[j+1];
                    }
                    r->filhos[i] = merge;
                }
            }
            
            else{
                //Implementar casos 3 (quando chave nao esta em um no, mas ele e interno)
            }

        }

    }

}

char* geradorNomeArquivo(){
    char letras[26];
    for(int i = 0; i < 26; i++){
        letras[i] = 'a' + i;
    }
    // Aloca memória para o nome do arquivo (20 letras + ".dat" + '\0')
    char *caminho = malloc(25 * sizeof(char)); 
    
    // Gera as 20 letras aleatórias
    for(int i = 0; i < 20; i++){
        int letra = rand() % 26;
        caminho[i] = letras[letra];
    }

    // Adiciona a extensão ".dat"
    strcpy(caminho + 20, ".dat");

    return caminho;
}

char** criarArquivoBinario(char nome){
    FILE* f = fopen(nome, "wb");
    if(f == NULL){
        printf("Erro de criacao\n");
        return;
    }

    return nome;
}

void criarArquivoDiretorio(){
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
                criarArquivoDiretorio();
            }
        }
        criarArquivoBinario(nome);
    }
}

void coletarArquivoBinario(char nome){
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
                FILE *bf = fopen(nome, "rb");
                
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
                imprimirArvoreB(no->filhos[i], nivel + 1);
            }
            for (int j = 0; j < nivel; j++) {
                printf("    ");  // Indentação para mostrar a profundidade
            }
            printf("%d\n", no->chaves[i]);
        }
        if (!no->folha) {
            imprimirArvoreB(no->filhos[i], nivel + 1);
        }
    }
}

//Implementar funcao pra pesquisar arvores na pasta
