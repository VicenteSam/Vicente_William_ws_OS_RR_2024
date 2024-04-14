#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 35

long graph[MAX][MAX];
long visited[MAX];

void createGraph() {
    srand(time(NULL));
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            if (i != j) {
                graph[i][j] = rand() % 2;
                graph[j][i] = graph[i][j];
            } else {
                graph[i][j] = 0;
            }
        }
    }
}

void printGraph() {
    printf("   ");
    for (int i = 0; i < MAX; i++)
        printf("%3d", i);
    printf("\n");
    for (int i = 0; i < MAX; i++) {
        printf("%3d", i);
        for (int j = 0; j < MAX; j++)
            printf("%3ld", graph[i][j]);
        printf("\n");
    }
}

void dfs_aux(int vertex) {                                                         //  graph explorer marking nodes as visited
    printf("%d ", vertex);
    visited[vertex] = 1;
        
    for (int j = 0; j < MAX; j++) {
        if (graph[vertex][j] == 1 && visited[j] == 0)
            dfs_aux(j);
    }
}

void dfs(int orig) {                                                               //  initializing initial point
    printf("DFS:\n");
    for (int j = 0; j < MAX; j++)
        visited[j] = 0;
    dfs_aux(orig);
}

int main() {
    createGraph();
    printGraph();
    clock_t start = clock();
    dfs(0);
    clock_t end = clock();
    double execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nRunTime: %.6f seconds\n", execution_time);
    return 0;
}
