#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include  "ArvoreB.h"

//int t = 3;  // Grau m�nimo da �rvore B


int main(){
    srand(time(NULL));
    removerArquivosDiretorio();
    
   //Menu
    printf("oi\n");
    NOARVOREB * raiz = criarNoArvoreB(3, 1);
    strcpy(raiz->NomeArquivo, "raiz.dat");
    int opcao;
    //inserir 19 chaves
    insercaoCLRS(1, &raiz);
    insercaoCLRS(2, &raiz);
    insercaoCLRS(3, &raiz);
    insercaoCLRS(4, &raiz);
    insercaoCLRS(5, &raiz);
    insercaoCLRS(6, &raiz);
    insercaoCLRS(7, &raiz);
    insercaoCLRS(8, &raiz);
    insercaoCLRS(9, &raiz);
    insercaoCLRS(10, &raiz);
    insercaoCLRS(11, &raiz);
    insercaoCLRS(12, &raiz);
    insercaoCLRS(13, &raiz);
    insercaoCLRS(14, &raiz);
    insercaoCLRS(15, &raiz);
    insercaoCLRS(16, &raiz);
    // insercaoCLRS(17, &raiz);
    // insercaoCLRS(18, &raiz);
    // insercaoCLRS(19, &raiz);


    

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
                printf("%s\n", raiz->NomeArquivo);
                for(int i = 0; i < raiz->n+1; i++){
                    printf("%s\n", raiz->filhos[i]);
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