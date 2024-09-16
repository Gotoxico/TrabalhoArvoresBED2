#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include  "ArvoreB.h"

//int t = 3;  // Grau mínimo da árvore B

int main(){
    srand(time(NULL));
    int opcao1 = 0, opcao2 = 0, chave, t, conferidor;
    char* nomeArvore = (char*) malloc(256 * sizeof(char));
    char* nomeArquivo = (char*) malloc(25 * sizeof(char));
    NOARVOREB* raiz, *aux;

    do{
        printf("=============================================\n");
        printf("Digite uma opcao: \n1 - Abrir arvore existente\n2 - Criar nova arvore\n3 - Sair\n");
        scanf("%d", &opcao1);
        printf("=============================================\n");
        system("cls");
        switch(opcao1){
            case 1:
                listarArvores();
                printf("\n\nDigite o nome da arvore: ");
                scanf("%s", nomeArvore);
                aux = leituraArquivoRaiz(nomeArvore);
                t = aux->t;
                if(strcpy(nomeArquivo,aux->NomeArquivo) != NULL){
                    strcpy(nomeArquivo, aux->NomeArquivo);
                    printf("%s", nomeArvore);
                    raiz = abrirArquivoDiretorio(nomeArquivo);
                }
                else{
                    break;
                }
                do{
                    system("cls");
                    printf("\n=============================================\n");
                    printf("Digite uma opcao para arvore: \n1 - Inserir chave\n2 - Remover chave\n3 - Buscar chave\n4 - Imprimir arvore\n5 - Sair\n");
                    scanf("%d", &opcao2);
                    printf("\n=============================================\n");
                     switch(opcao2){
                        case 1:
                            printf("Digite chave: \n");
                            scanf("%d", &chave);
                            conferidor = buscarArvoreB(chave, raiz);
                            if(conferidor == 1){
                                printf("\nChave ja existe\n");
                                break;
                            }
                            insercaoCLRS(chave, &raiz);
                            printf("%s", nomeArvore);
                            atualizarNomeArquivoRaiz(raiz, nomeArvore);
                            printf("\nChave inserida\n");
                            system("pause");

                            break;

                        case 2:
                            printf("Digite chave: \n");
                            scanf("%d", &chave);
                            remocaoCLRS(chave, &raiz);
                            atualizarNomeArquivoRaiz(raiz, nomeArvore);
                            //system("pause");
                            break;

                        case 3:
                            printf("Digite chave: \n");
                            scanf("%d", &chave);
                            conferidor = buscarArvoreB(chave, raiz);
                            if(conferidor == 1){
                                printf("\nChave encontrada\n");
                            }
                            else{
                                printf("\nChave nao encontrada\n");
                            }
                            system("pause");
                            break;

                        case 4:
                            imprimirArvoreB(raiz, 0);
                            system("pause");
                            break;

                        default:
                            
                            break;
                    }
                }while(opcao2 != 5);
                break;

            case 2:
                 printf("Digite t da nova arvore: ");
                scanf("%d", &t);
                raiz = criarNoArvoreB(t, 1);
                printf("Digite a primeira chave: \n");
                scanf("%d", &chave);
                insercaoCLRS(chave, &raiz);
                nomeArvore = geradorArquivoRaiz(raiz);
                do{
                    system("cls");
                    printf("=============================================\n");
                    printf("Digite uma opcao para arvore: \n1 - Inserir chave\n2 - Remover chave\n3 - Buscar chave\n4 - Imprimir arvore\n5 - Sair\n");
                    scanf("%d", &opcao2);
                    printf("\n=============================================\n");
                
                    switch(opcao2){
                        case 1:
                            printf("Digite chave: \n");
                            scanf("%d", &chave);
                            conferidor = buscarArvoreB(chave, raiz);
                            if(conferidor == 1){
                                printf("\nChave ja existe\n");
                                break;
                            }
                            insercaoCLRS(chave, &raiz);
                            atualizarNomeArquivoRaiz(raiz, nomeArvore);
                            printf("\nChave inserida\n");
                            system("pause");

                            break;

                        case 2:
                            printf("Digite chave: \n");
                            scanf("%d", &chave);
                            remocaoCLRS(chave, &raiz);
                            atualizarNomeArquivoRaiz(raiz, nomeArvore);
                            break;

                        case 3:
                            printf("Digite chave: \n");
                            scanf("%d", &chave);
                            conferidor = buscarArvoreB(chave, raiz->NomeArquivo);
                            if(conferidor == 1){
                                printf("\nChave encontrada\n");
                            }
                            else{
                                printf("\nChave nao encontrada\n");
                            }
                            system("pause");
                            break;

                        case 4:
                            imprimirArvoreB(raiz, 0);
                            system("pause");
                            break;

                        default:
                            break;
                    }
                }while(opcao2 != 5);
                break;


            default:
                break;
        }
        
    }while(opcao1 != 3);
}
