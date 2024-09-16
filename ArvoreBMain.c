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
    char* nomeArvore = (char*) malloc(256 * sizeof(char));
    char* nomeArquivo = (char*) malloc(25 * sizeof(char));
    NOARVOREB* raiz;

    do{
        printf("Digite uma opcao: \n1 - Abrir arvore existente\n2 - Criar nova arvore\n3 - Sair\n");
        scanf("%d", &opcao1);
        switch(opcao1){
            case 1:
                listarArvores();
                printf("Digite o nome da arvore: ");
                scanf("%s", nomeArvore);
                if(strcpy(nomeArquivo, leituraArquivoRaiz(nomeArvore)) != NULL){
                    strcpy(nomeArquivo, leituraArquivoRaiz(nomeArvore));
                    printf("Chegou\n");
                    printf("%s", nomeArquivo);
                    raiz = abrirArquivoDiretorio(nomeArquivo);
                }
                else{
                    break;
                }
                do{
                    printf("Digite uma opcao para arvore: \n1 - Inserir chave\n2 - Remover chave\n3 - Buscar chave\n4 - Imprimir arvore\n5 - Sair\n");
                    scanf("%d", &opcao2);
                    switch(opcao2){
                        case 1:
                            printf("Digite chave: \n");
                            scanf("%d", &chave);
                            insercaoCLRS(chave, &raiz);
                            break;

                        case 2:
                            printf("Digite chave: \n");
                            scanf("%d", &chave);
                            remocaoCLRS(chave, &raiz);
                            break;

                        case 3:
                            printf("Digite chave: \n");
                            scanf("%d", &chave);
                            buscarArvoreB(chave, raiz->NomeArquivo);
                            break;

                        case 4:
                            imprimirArvoreB(raiz, 0);
                            break;

                        default:
                            printf("Opcao invalida\n");
                            break;
                    }
                }while(opcao2 != 5);
                break;

            case 2:
                printf("Digite t da nova arvore: ");
                scanf("%d", &t);
                raiz = criarNoArvoreB(t, 1);
                geradorArquivoRaiz(raiz);
                printf("Digite chave: \n");
                scanf("%d", &chave);
                insercaoCLRS(chave, &raiz);
                do{
                    printf("Digite uma opcao para arvore: \n1 - Inserir chave\n2 - Remover chave\n3 - Buscar chave\n4 - Imprimir arvore\n5 - Sair\n");
                    scanf("%d", &opcao2);
                    switch(opcao2){
                        case 1:
                            printf("Digite chave: \n");
                            scanf("%d", &chave);
                            insercaoCLRS(chave, &raiz);
                            break;

                        case 2:
                            printf("Digite chave: \n");
                            scanf("%d", &chave);
                            remocaoCLRS(chave, &raiz);
                            break;

                        case 3:
                            printf("Digite chave: \n");
                            scanf("%d", &chave);
                            buscarArvoreB(chave, raiz->NomeArquivo);
                            break;

                        case 4:
                            imprimirArvoreB(raiz, 0);
                            break;

                        default:
                            printf("Opcao invalida\n");
                            break;
                    }
                }while(opcao2 != 5);
                break;


            default:
                printf("Opcao invalida\n");
                break;
        }
        
    }while(opcao1 != 3);
}
