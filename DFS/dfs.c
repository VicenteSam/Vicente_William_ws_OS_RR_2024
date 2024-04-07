#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 50

typedef struct {
    long graph[MAX][MAX];
    long edges;
} Graph;

long visited[MAX];

void createGraph(Graph *g) {
    srand(time(NULL));
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            if (i != j) {
                g->graph[i][j] = rand() % 2;
                g->graph[j][i] = g->graph[i][j];
            } else {
                g->graph[i][j] = 0;
            }
        }
    }
}

void printGraph(Graph g) {
    printf("   ");
    for (int i = 0; i < MAX; i++)
        printf("%3d", i);
    printf("\n");
    for (int i = 0; i < MAX; i++) {
        printf("%3d", i);
        for (int j = 0; j < MAX; j++)
            printf("%3ld", g.graph[i][j]);
        printf("\n");
    }
}

void dfs_aux(Graph g, int vertex) {
    printf("%d ", vertex);
    if (!visited[vertex])
        visited[vertex] = 1;
        
    for (int j = 0; j < MAX; j++) {
        if (g.graph[vertex][j] == 1 && visited[j] == 0)
            dfs_aux(g, j);
    }
}

void dfs(Graph g, int orig) {
    printf("DFS:\n");
    for (int j = 0; j < MAX; j++)
        visited[j] = 0;
    dfs_aux(g, orig);
}

int main() {
    Graph g1;
    createGraph(&g1);
    printGraph(g1);
    clock_t start = clock();
    dfs(g1, 0);
    clock_t end = clock();
    double execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nRunTime: %.6f seconds\n", execution_time);
    return 0;
}
