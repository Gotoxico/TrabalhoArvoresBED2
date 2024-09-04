#include <stdio.h>
#include <stdlib.h>

typedef struct NOARVOREB {
    int *chaves;
    char **filhos;
    int n;
    int folha;
} NOARVOREB;

int t;  // Grau m�nimo da �rvore B

// Fun��o b�sica para criar um n� de �rvore B
NOARVOREB* criarNoArvoreB(int t, int folha) {
    NOARVOREB* no = (NOARVOREB*) malloc(sizeof(NOARVOREB));
    no->n = 0;
    no->chaves = (int*) malloc(sizeof((2*t-1) * sizeof(int)));
    no->filhos = (char**) malloc(sizeof(2*t) * sizeof(char*));
    no->folha = folha;
    return no;
}

// Fun��o de impress�o da �rvore B
void imprimirArvoreB(NOARVOREB* no, int nivel) {
    if (no != NULL) {
        int i;
        for (i = 0; i < no->n; i++) {
            if (!no->folha) {
                imprimirArvoreB(no->filhos[i], nivel + 1);
            }
            for (int j = 0; j < nivel; j++) {
                printf("    ");  // Indenta��o para mostrar a profundidade
            }
            printf("%d\n", no->chaves[i]);
        }
        if (!no->folha) {
            imprimirArvoreB(no->filhos[i], nivel + 1);
        }
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
int buscarArvoreBBinariamente(int chave, NOARVOREB* raiz) {
    int i = buscaBinariaNo(chave, raiz, 0, raiz->n - 1);
    if (i >= 0) {
        return i;
    }

    if (raiz->folha) {
        return -1;  // N�o encontrado
    }

    char* proximoFilho = raiz->filhos[-i - 1];
    return buscarArvoreBBinariamente(chave, proximoFilho);
}

// Fun��o para fazer o split de um n� filho
void splitChildArvoreB(NOARVOREB* raiz, int i) {
    NOARVOREB* y = raiz->filhos[i];
    NOARVOREB* z = criarNoArvoreB(t, y->folha);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++) {
        z->chaves[j] = y->chaves[j + t];
    }

    if (!y->folha) {
        for (int j = 0; j < t; j++) {
            z->filhos[j] = y->filhos[j + t];
        }
    }

    y->n = t - 1;

    for (int j = raiz->n; j >= i + 1; j--) {
        raiz->filhos[j + 1] = raiz->filhos[j];
    }

    raiz->filhos[i + 1] = z;

    for (int j = raiz->n; j >= i; j--) {
        raiz->chaves[j + 1] = raiz->chaves[j];
    }

    raiz->chaves[i] = y->chaves[t - 1];
    raiz->n++;
}


//Funcao para dividir chaves e filhos entre filhos y e z de raiz
NOARVOREB* splitChildArvore(int chave, NOARVOREB* raiz){
    NOARVOREB* z = (NOARVOREB*) malloc(sizeof(NOARVOREB));
    z->chaves = (int*) malloc(sizeof((2*t-1) * sizeof(int)));
    z->filhos = (char**) malloc(sizeof(2*t) * sizeof(char*));
    NOARVOREB* y = raiz->filhos[chave];
    z->folha = y->folha;
    z->n = t-1;

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
// Fun��o para inserir em um n� n�o cheio
void insercaoNaoCheioArvoreB(int chave, NOARVOREB* raiz) {
    int i = raiz->n - 1;

    if (raiz->folha) {
        while (i >= 0 && chave < raiz->chaves[i]) {
            raiz->chaves[i + 1] = raiz->chaves[i];
            i--;
        }
        raiz->chaves[i + 1] = chave;
        raiz->n++;
    } else {
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

// Fun��o para inser��o usando o m�todo CLRS
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



// Fun��o main para testar a �rvore B, criar menu
int main() {
    t = 3;  // Grau m�nimo da �rvore B

    NOARVOREB* raiz = criarNoArvoreB(t, 1);  // Cria a raiz da �rvore B
    int opcao, chave;

    do {
        printf("\n\nMenu de op��es:\n");
        printf("1 - Inserir chave\n");
        printf("2 - Buscar chave\n");
        printf("3 - Imprimir �rvore\n");
        printf("4 - Sair\n");
        printf("Digite a op��o desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a chave a ser inserida: ");
                scanf("%d", &chave);
                insercaoCLRS(chave, &raiz);
                imprimirArvoreB(raiz, 0);
                break;
            case 2:
                printf("Digite a chave a ser buscada: ");
                scanf("%d", &chave);
                if (buscarArvoreBBinariamente(chave, raiz) >= 0) {
                    printf("Chave encontrada!\n");
                } else {
                    printf("Chave n�o encontrada!\n");
                }
                break;
            case 3:
                imprimirArvoreB(raiz, 0);
                break;
            case 4:
                break;
            default:
                printf("Op��o inv�lida!\n");
        }
    } while (opcao != 4);

    return 0;
}

