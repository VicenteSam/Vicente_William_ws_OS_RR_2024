#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10

long graph[MAX][MAX] = {
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 1, 1, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 1, 1},
    {0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 1, 1, 0}
};
long visited[MAX];
int cont = 0;

void printGraph() {
    printf("   ");
    for (int i = 0; i < MAX; i++)
        printf("%3d", i + 1);
    printf("\n");
    for (int i = 0; i < MAX; i++) {
        printf("%3d", i + 1);
        for (int j = 0; j < MAX; j++)
            printf("%3ld", graph[i][j]);
        printf("\n");
    }
    printf("\nDFS:\n");
}

void dfs_aux(int vertex) {
    printf("-> %d ", vertex + 1);
    visited[vertex] = ++cont;
        
    for (int j = 0; j < MAX; j++) {
        if (graph[vertex][j] == 1 && visited[j] == 0)
            dfs_aux(j);
    }
}

void dfs(int orig) {
    cont = 0;
    
    for (int j = 0; j < MAX; j++)
        visited[j] = 0;
    dfs_aux(orig);
    printf("\n");
    for(int j = 0; j < MAX; j++)
        printf("| %ld |", visited[j]);
}

int main() {
    printGraph();
    clock_t start = clock();
    dfs(0);
    clock_t end = clock();
    double execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nRunTime: %.6f seconds\n", execution_time);
    return 0;
}
