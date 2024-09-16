#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include  "ArvoreB.h"

//int t = 3;  // Grau mínimo da árvore B

//FEITO POR KAUAN DOS SANTOS LOCHE e RODRIGO ISAO GOTO


int main(){
    srand(time(NULL));
    
   //Menu
    NOARVOREB * raiz = criarNoArvoreB(t, 1);
    int opcaoDir, opcao;
   
    
  
    
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
                
            
                break;
            case 4:
                printf("Digite a chave a ser removida: ");
                int chaveRemover;
                scanf("%d", &chaveRemover);
                remocaoCLRS(chaveRemover, &raiz);
                break;
            case 5:
                printf("Digite a chave a ser buscada: ");
                int chaveBusca;
                scanf("%d", &chaveBusca);
                int i = buscarArvoreB(chaveBusca, raiz);
                if(i == 1){
                    printf("Chave encontrada\n");
                }
                else{
                    printf("Chave nao encontrada\n");
                }

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
}
