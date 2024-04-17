#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"

#define MAX 10
#define NUM_THREADS 4

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

bool visited[MAX] = {false};
pthread_t threads[NUM_THREADS];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void print_graph() {
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
        pthread_mutex_lock(&mutex);
        if (!visited[i]) {
            push(stack, i);
            visited[i] = true;
        }
        pthread_mutex_unlock(&mutex);

        while (!stackIsEmpty(stack)) {
            int node = pop(stack);
            printf("Thread %ld is visiting node: %d\n", thread_id, node);
            for (int j = 0; j < MAX; j++) {
                if (graph[node][j] != 0 && !visited[j]) {
                    pthread_mutex_lock(&mutex);
                    if (!visited[j]) {
                        push(stack, j);
                        visited[j] = true;
                    }
                    pthread_mutex_unlock(&mutex);
                }
            }
        }
    }
    
    destroyStack(&stack);
}


int main() {
    print_graph();
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

    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);
    
    return 0;
}
