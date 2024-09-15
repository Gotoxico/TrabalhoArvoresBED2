#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include  "ArvoreB.h"

//int t = 3;  // Grau mínimo da árvore B


int main(){
    srand(time(NULL));
    removerArquivosDiretorio();
    
   //Menu
    printf("oi\n");
    NOARVOREB * raiz = criarNoArvoreB(3, 1);
    //strcpy(raiz->NomeArquivo, "raiz.dat");
    int opcaoDir, opcao;
    //inserir 25 chaves
    insercaoCLRS(1, &raiz);
    insercaoCLRS(2, &raiz);
    insercaoCLRS(3, &raiz);
    insercaoCLRS(4, &raiz);
    insercaoCLRS(5, &raiz);
    insercaoCLRS(6, &raiz);
    insercaoCLRS(7, &raiz);
    // insercaoCLRS(8, &raiz);
    // insercaoCLRS(9, &raiz);
    // insercaoCLRS(10, &raiz);
    // insercaoCLRS(11, &raiz);
    // insercaoCLRS(12, &raiz);
    // insercaoCLRS(13, &raiz);
    // insercaoCLRS(14, &raiz);
    // insercaoCLRS(15, &raiz);
    // insercaoCLRS(16, &raiz);
    // insercaoCLRS(17, &raiz);
    // insercaoCLRS(18, &raiz);
    // insercaoCLRS(19, &raiz);
    // insercaoCLRS(20, &raiz);
    // insercaoCLRS(21, &raiz);
    // insercaoCLRS(22, &raiz);
    // insercaoCLRS(23, &raiz);
   // insercaoCLRS(24, &raiz);
   // insercaoCLRS(25, &raiz);



    printf("%s\n", raiz->NomeArquivo);
    for(int i = 0; i < raiz->n+1; i++){
        printf("%s\n", raiz->filhos[i]);
    }
    printf("\n");
    // insercaoCLRS(16, &raiz);
    // insercaoCLRS(17, &raiz);
    // insercaoCLRS(18, &raiz);
    // insercaoCLRS(19, &raiz);

    char * nomeDiretorio = malloc(256 * sizeof(char));
    
    do{
        //menu com opções de abrir arvore existente ou criar nova ou sair
        printf("1 - Abrir arvore existente\n");
        printf("2 - Criar nova arvore\n");
        printf("3 - Sair\n");
        scanf("%d", &opcaoDir);

        switch(opcaoDir){
            case 1:
                listarDiretorioPai();
                printf("\nDigite o nome do diretorio: ");
                scanf("%s", nomeDiretorio);
                listarDiretorios(nomeDiretorio);
                if(VerificarDiretorio(nomeDiretorio)){
                    printf("\nDiretorio nao existe\n");
                    break;
                }
                else{
                    abrirArquivoDiretorio(nomeDiretorio);
                }
                /*
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
                            remocaoCLRS(chaveRemover, raiz->NomeArquivo);
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
        }
*/
                break;
            case 2:
                //criarArquivoDiretorio(raiz, raiz->NomeArquivo);
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
                remocaoCLRS(chaveRemover, raiz);
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
    } while(opcaoDir != 3);
        return 0;

}