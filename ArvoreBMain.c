#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include  "ArvoreB.h"

//int t = 3;  // Grau mínimo da árvore B

int main(){
    srand(time(NULL));
    int opcao1 = 0, opcao2 = 0, chave, t;
    char* nomeDiretorio = (char*) malloc(256 * sizeof(char));
    char* nomeArquivo = (char*) malloc(256 * sizeof(char));
    NOARVOREB* raiz;

    do{
        printf("Digite uma opcao: \n1 - Abrir arvore existente\n2 - Criar nova arvore\n3 - Sair\n");
        scanf("%d", &opcao1);
        switch(opcao1){
            case 1:
                listarDiretorioPai();
                printf("Digite o nome do diretorio: ");
                scanf("%s", nomeDiretorio);
                listarDiretorios(nomeDiretorio);
                if(!VerificarDiretorio(nomeDiretorio)){
                    printf("Diretorio nao existe\n");
                    break;
                }
                printf("Digite o nome do arquivo: ");
                scanf("%s", nomeArquivo);
                if(abrirArquivoDiretorio(nomeArquivo, nomeDiretorio)){
                    raiz = abrirArquivoDiretorio(nomeArquivo, nomeDiretorio);
                }
                else{
                    break;
                }
                raiz = abrirArquivoDiretorio(nomeArquivo, nomeDiretorio);
                do{
                    printf("Digite uma opcao para arvore: \n1 - Inserir chave\n2 - Remover chave\n3 - Buscar chave\n4 - Imprimir arvore\n5 - Sair\n");
                    scanf("%d", &opcao2);
                    switch(opcao2){
                        case 1:
                            printf("Digite chave: \n");
                            scanf("%d", &chave);
                            insercaoCLRS(chave, &raiz, nomeDiretorio);
                            break;

                        case 2:
                            printf("Digite chave: \n");
                            scanf("%d", &chave);
                            remocaoCLRS(chave, raiz, nomeDiretorio);
                            break;

                        case 3:
                            printf("Digite chave: \n");
                            scanf("%d", &chave);
                            buscarArvoreB(chave, raiz->NomeArquivo, nomeDiretorio);
                            break;

                        case 4:
                            imprimirArvoreB(raiz, 0, nomeDiretorio);
                            break;

                        default:
                            printf("Opcao invalida\n");
                            break;
                    }
                }while(opcao2 != 5);

            case 2:
                criarDiretorio();
                printf("Digite t nova arvore: ");
                scanf("%d", &t);
                NOARVOREB* raiz = criarNoArvoreB(t, 1);
                break;

            default:
                printf("Opcao invalida\n");
                break;
        }
        
    }while(opcao1 != 3);
}

/*
int main(){
    srand(time(NULL));
    removerArquivosDiretorio();
    
   //Menu
    printf("oi\n");
    NOARVOREB * raiz = criarNoArvoreB(t, 1);
    //strcpy(raiz->NomeArquivo, "raiz.dat");
    int opcaoDir, opcao;
    // inserir 300 chaves 
    for (int i = 0; i < 20; i++) {
        insercaoCLRS(i, &raiz);
    }
    insercaoCLRS(-1, &raiz);
    insercaoCLRS(-2, &raiz);
    insercaoCLRS(-3, &raiz);





    // printf("%s\n", raiz->NomeArquivo);
    // for(int i = 0; i < raiz->n+1; i++){
    //     printf("%s\n", raiz->filhos[i]);
    // }
    // printf("\n");
    // insercaoCLRS(16, &raiz);
    // insercaoCLRS(17, &raiz);
    // insercaoCLRS(18, &raiz);
    // insercaoCLRS(19, &raiz);

    char * nomeDiretorio = (char*) malloc(256 * sizeof(char));
    
    // do{
    //     //menu com opções de abrir arvore existente ou criar nova ou sair
    //     printf("1 - Abrir arvore existente\n");
    //     printf("2 - Criar nova arvore\n");
    //     printf("3 - Sair\n");
    //     scanf("%d", &opcaoDir);

    //     switch(opcaoDir){
    //         case 1:
    //             listarDiretorioPai();
    //             printf("\nDigite o nome do diretorio: ");
    //             scanf("%s", nomeDiretorio);
    //             listarDiretorios(nomeDiretorio);
    //             if(VerificarDiretorio(nomeDiretorio)){
    //                 printf("\nDiretorio nao existe\n");
    //                 break;
    //             }
    //             else{
    //                 abrirArquivoDiretorio(nomeDiretorio);
    //             }
                
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
                            remocaoCLRS(chaveRemover, &raiz);
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
/*
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
*/
