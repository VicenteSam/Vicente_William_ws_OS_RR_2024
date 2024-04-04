#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

int main(){
    Grafo* gr = criar_Grafo(5, 5);

    inserirAresta (gr, 0, 1);
    inserirAresta (gr, 1, 3);
    inserirAresta (gr, 1, 2);
    inserirAresta (gr, 2, 4);
    inserirAresta (gr, 3, 0);
    inserirAresta (gr, 3, 4);
    inserirAresta (gr, 4, 1);

    imprimir_Grafo(gr);


    printf("\nBusca \n");
    int visitado[5];
    dfs_grafo(gr, 0, visitado);
    
    liberar_Grafo(gr);

    system("pause");
    return 0;
}