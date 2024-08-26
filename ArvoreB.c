#include <stdio.h>
#include <stdlib.h>
#include "ArvoreB.h"

NOARVOREB* criarNoArvoreB(int t, int folha){
    NOARVOREB* no = (NOARVOREB*) malloc(sizeof(NOARVOREB));
    no->n = 0;
    no->chaves = (int*) malloc(sizeof((2*t-1) * sizeof(int)));
    no->filhos = (char**) malloc(sizeof(2*t) * sizeof(char*));
    no->folha = folha;
    return no;
}

int buscarArvoreB(int chave, char** raiz){
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

int buscaBinariaNo(int chave, NOARVOREB* raiz, int limiteInferior, int limiteSuperior){
    if(limiteInferior > limiteSuperior){
        return -meio;
    }

    int meio = (limiteInferior+limiteSuperior)/2;
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

int buscarArvoreBBinariamente(int chave, char** raiz){
    NOARVOREB* r = raiz; //Descobrir modo para esse NOARVOREB receber o no armazenado no arquivo binario
    int i = buscaBinariaNo(chave, r, 0, r->n-1);
    if(i > 0){
        return i;
    }
    if(i == 0){
        NOARVOREB* rf = r->filhos[i];
    }
    else{
        NOARVOREB* rf = r->filhos[-i+1]
    }

    if(r->folha){
        return NULL;
    }
    else{
        return buscarArvoreBBinariamente(chave, rf);
    }
}

NOARVOREB* insercaoCLRS(int chave, char** raiz){
    NOARVORE* r = raiz; //Descobrir modo para esse NOARVOREB receber o no armazenado no arquivo binario
    if(r->n == 2*t-1){
        NOARVOREB* s = criarNoArvore(t, 0);
        s->filhos[1] = r;
        splitChildArvoreB(s, 1);
        insercaoNaoCheioArvoreB(chave, s);
    }
    else{
        insercaoNaoCheioArvoreB(chave, r);
    }
}

NOARVOREB* insercaoNaoCheioArvoreB(int chave, char** raiz){
    NOARVOREB* r = raiz; //Descobrir modo para esse NOARVOREB receber o no armazenado no arquivo binario
    int i = r->n;
    if(r->folha){
        while(i >= 1 && chave < r->chaves[i]){
            r->chaves[i+1] = r->chaves[i];
            i = i-1;
        }
        r->chaves[i+1] = chave;
        r->n = r->n+1;
    }
    else{
        while(i >= 1 && chave < r->chaves[i]){
            i = i-1;
        }
        i = i+1;
        NOARVOREB* rf = r->filhos[i];
        if(rf->n == 2*t-1){
            splitChildArvoreB(r, i);
            if(chave > r->chaves[i]){
                i = i+1;
            }
        }
        insercaoNaoCheioArvoreB(chave, r->filhos[i]);
    }
}

NOARVOREB* splitChildArvore(int chave, NOARVOREB* raiz){
    NOARVOREB* z = (NOARVOREB*) malloc(sizeof(NOARVOREB));
    z->chaves = (int*) malloc(sizeof((2*t-1) * sizeof(int)));
    z->filhos = (char**) malloc(sizeof(2*t) * sizeof(char*));
    NOARVOREB* y = raiz->filhos[chave];
    z->folha = y->folha;
    z->n = t-1;

    for(int j = 1; j < t; j++){
        z->chaves[j] = y->chaves[j+t];
    }
    if(y->folha == 0){
        for(int j = 1; j < t+1; j++){
            z->filhos[j] = y->filhos[j+t];
        }
    }
    y->n = t-1;

    for(int j = raiz->n+1; j > chave; j--){
        raiz->filhos[j+1] = raiz->filhos[j];
    }
    raiz->filhos[chave+1] = z;
    for(int j = raiz->n; j > chave-1; j--){
        raiz->chaves[j+1] = raiz->chaves[j];
    }
    raiz->chaves[chave] = y->chaves[t];
    raiz->n = raiz->n+1;
    //Escrever no y em arquivo binario
    //Escrever no z em arquivo binario
    //Escrever no x em arquivo binario
}

NOARVOREB* buscarPai(int chaveFilho, NOARVOREB* raiz){
    NOARVOREB* pai = raiz;
    while(pai->folha != 0){
        int i = buscaBinariaNo(chaveFilho, r, 0, r->n-1);
        if(i >= 0){
            return pai;
        }
        NOARVORE* rf = r->filhos[-i];
        else{
            return buscarPai(chaveFilho, rf);
        }
    }
}

NOARVOREB* remocaoCLRS(int chave, char** raiz){
    NOARVOREB* r = raiz; //Descobrir modo para esse NOARVOREB receber o no armazenado no arquivo binario
    int presenca = buscarArvoreB(chave, raiz);
    if(presenca == NULL){
        return NULL;
    }
    else{
        if(r->folha){
            if(r->n-1 >= t-1){
                int i = 0;
                while(i < r->n && chaves[i] > chave){
                    i++;
                }
                if(chaves[i] == chave){
                    for(int j = i; j<r->n; j++){
                        chaves[j] = chaves[j+1];
                    }
                }
            }
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
                        pai->filhos[i+11].n = pai->filhos[i+1] - 1;
                    }
                    else{
                        //Adicionar caso em que os irmaos possuem t-1
                    }
                }
            }
        }

        else{
            if(r->folhas == 0 && buscarBinariaNo(chave, r, 0, r->n-1) > 0){
                int i = presenca;
                if(r->filhos[i].n >= t){
                    r->chaves[i] = r->filhos[i].chaves[r->filhos[i].n];
                    r->filhos[i].n = (r->filhos[i].n)-1;
                }
                if(r->filhos[i+1].n >= t){
                    r->chaves[i] = r->filhos[i+1].chaves[0];
                    r->filhos[i+1].n = (r->filhos[i+1].n)-1;
                }
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