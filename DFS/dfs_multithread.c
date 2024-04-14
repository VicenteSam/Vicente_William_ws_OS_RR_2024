#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 35
#define NUM_THREADS 4

long graph[MAX][MAX];
long visited[MAX];
pthread_t threads[NUM_THREADS];

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

void* dfs_aux_thread(void* arg) {                                               // threads routine where each thread has a node range
    long thread_id = (long)arg;
    int nodes_per_thread = MAX / NUM_THREADS;
    int start = thread_id * nodes_per_thread;
    int end = (thread_id + 1) * nodes_per_thread;

    if (thread_id == NUM_THREADS - 1) {
        end = MAX;
    }

    for (int i = start; i < end; i++) {
        printf("Node: %02d -------- Thread: %ld\n", i, thread_id);
    }

    pthread_exit(NULL);
}

int main() {
    createGraph();
    printGraph();
    clock_t start = clock();

    printf("DFS:\n");
    for (long i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, dfs_aux_thread, (void*)i);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    clock_t end = clock();
    double execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nRunTime: %.6f seconds\n", execution_time);

    return 0;
}
