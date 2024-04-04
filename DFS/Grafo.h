typedef struct grafo Grafo;

Grafo *criar_Grafo (int num_vertices, int grau_max);
void liberar_Grafo(Grafo* gr);
int inserirAresta(Grafo* gr, int orig, int dest);
void imprimir_Grafo(Grafo *gr);
void dfs(Grafo *gr, int raiz, int *visitado, int cont);
void dfs_grafo(Grafo *gr, int raiz, int *visitado);
