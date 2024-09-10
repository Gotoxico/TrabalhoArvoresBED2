#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include "ArvoreB.h"

//int t = 3;  // Grau m�nimo da �rvore B


int main(){

    NOARVOREB * raiz = criarNoArvoreB(t, 1);
    
    //insere 
    insercaoCLRS(10, &raiz);
    insercaoCLRS(20, &raiz);
    insercaoCLRS(5, &raiz);
    insercaoCLRS(6, &raiz);
    insercaoCLRS(12, &raiz);

    imprimirArvoreB(raiz, 0);



    //inserir um
}