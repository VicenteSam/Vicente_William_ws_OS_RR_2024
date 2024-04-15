#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>
#include "stack.h"

#define MAX 20
#define NUM_THREADS 4

long graph[MAX][MAX];
bool visited[MAX] = {false};
pthread_t threads[NUM_THREADS];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

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

void* dfs(void* arg) {
    long thread_id = (long)arg;
    Stack* stack = createStack();

    int start = thread_id * (MAX / NUM_THREADS);
    int end = (thread_id + 1) * (MAX / NUM_THREADS);
    if (thread_id == NUM_THREADS - 1) {
        end = MAX;
    }

    for (int i = start; i < end; i++) {
        if (!visited[i]) {
            push(stack, i);
            while (!stackIsEmpty(stack)) {
                int node = pop(stack);
                if (!visited[node]) {
                    visited[node] = true;
                    printf("Thread %ld is visiting node: %d\n", thread_id, node);
                    for (int j = 0; j < MAX; j++) {
                        if (graph[node][j] && !visited[j]) {
                            push(stack, j);
                        }
                    }
                }
            }
        }
    }

    destroyStack(&stack);
    pthread_exit(NULL);
}

int main() {
    createGraph();
    printGraph();
    clock_t start = clock();

    printf("DFS:\n");
    for (long i = 0; i < NUM_THREADS; ++i) {
        if (pthread_create(&threads[i], NULL, dfs, (void*)i) != 0){
            printf("Failed to create thread");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_join(threads[i], NULL) != 0){
            return 2;
        }
    }

    clock_t end = clock();
    double execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nRunTime: %.6f seconds\n", execution_time);

    return 0;
}
