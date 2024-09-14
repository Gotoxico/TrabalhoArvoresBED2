#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include  "ArvoreB.h"

//int t = 3;  // Grau mínimo da árvore B


int main(){
    srand(time(NULL));
   //Menu
    NOARVOREB* raiz = criarNoArvoreB(3, 1);
    raiz->NomeArquivo = "raiz.dat";
    int opcao;
    //inserir 4 chaves
    insercaoCLRS(1, &raiz);
    insercaoCLRS(2, &raiz);
    insercaoCLRS(3, &raiz);
    insercaoCLRS(4, &raiz);

    

    do{
        printf("1 - Criar diretorio\n");
        printf("2 - Listar arvores\n");
        printf("3 - Inserir chave\n");
        printf("4 - Remover chave\n");
        printf("5 - Buscar chave\n");
        printf("6 - Imprimir arvore\n");
        printf("7 - Sair\n");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                criarDiretorio();
                break;
            case 2:
                listarArvoresDiretorio();
                break;
            case 3:
                printf("Digite a chave a ser inserida: ");
                int chave;
                scanf("%d", &chave);
                printf("\n");
                insercaoCLRS(chave, &raiz);
                //imprimirArvoreB(raiz, 0);
                // printf("\n%s\n", raiz->NomeArquivo);
                // printf("%s\n%s\n", raiz->filhos[0], raiz->filhos[1]);
                NOARVOREB* filho = coletarArquivoBinario(raiz->filhos[1]);
                printf("%d\n", filho->n);
                for(int i = 0; i < filho->n; i++){
                    printf("%d\n", filho->chaves[i]);
                }
                break;
            case 4:
                printf("Digite a chave a ser removida: ");
                int chaveRemover;
                scanf("%d", &chaveRemover);
                //remocaoCLRS(chaveRemover, raiz->NomeArquivo);
                break;
            case 5:
                printf("Digite a chave a ser buscada: ");
                int chaveBusca;
                scanf("%d", &chaveBusca);
                buscarArvoreBBinariamente(chaveBusca, raiz->NomeArquivo);
                break;
            case 6:
                imprimirArvoreB(raiz, 0);
                break;
            case 7:
                break;
            default:
                printf("Opcao invalida\n");
                break;
        }
    }while(opcao != 7);
    return 0;

}