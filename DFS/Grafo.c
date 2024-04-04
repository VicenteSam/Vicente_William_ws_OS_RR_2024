#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

struct grafo{
  int num_vertices;
  int grau_max;
  int** arestas;
  int* grau;
};

Grafo *criar_Grafo (int num_vertices, int grau_max){
  Grafo *gr;
  gr = (Grafo*) malloc(sizeof(struct grafo));
  if (gr != NULL){
    int i;
    gr->num_vertices = num_vertices;
    gr->grau_max = grau_max;
    gr->grau=(int*)calloc(num_vertices, sizeof(int));
    gr->arestas=(int**)malloc(num_vertices*sizeof(int*));
    for (i = 0; i < num_vertices; i++)
      gr->arestas[i]=(int*)malloc(grau_max*sizeof(int));
  }
  return gr;
}

void liberar_Grafo(Grafo* gr) {
  if(gr != NULL){
    int i;
    for (i = 0; i < gr->num_vertices; i++)
      free(gr->arestas[i]);
    free(gr->arestas);
    free(gr->grau);
    free(gr);
  }
}

int inserirAresta(Grafo* gr, int orig, int dest){
  if(gr == NULL)
    return 0;
  if(orig < 0 || orig >= gr->num_vertices)
    return 0;
  if(dest < 0 || dest >= gr->num_vertices)
    return 0;
  
  gr->arestas[orig][gr->grau[orig]] = dest;
  gr->grau[orig]++;
  
  return 1;
}

void imprimir_Grafo(Grafo *gr){
    if(gr == NULL)
        return;

    int i, j;
    for(i=0; i < gr->num_vertices; i++){
        printf("%d: ", i);
        for(j=0; j < gr->grau[i]; j++){
            printf("%d, ", gr->arestas[i][j]);
      }
      printf("\n");
    }
}

void dfs(Grafo *gr, int raiz, int *visitado, int cont){
  int i;
  visitado[raiz] = cont;
  for (i = 0; i < gr->grau[raiz]; i++){
    if(!visitado[gr->arestas[raiz][i]])
      dfs(gr, gr->arestas[raiz][i], visitado, cont+1);
  }
}

void dfs_grafo(Grafo *gr, int raiz, int *visitado){
    int i, cont = 1;
    for (i = 0; i < gr->num_vertices; i++)
      visitado[i] = 0;
    dfs(gr, raiz, visitado, cont);

    for(i=0; i < gr->num_vertices; i++)
        printf("%d -> %d\n",i,visitado[i]);
}

