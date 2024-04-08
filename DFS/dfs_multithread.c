#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 50
#define NUM_THREADS 4

typedef struct {
    long graph[MAX][MAX];
    long edges;
} Graph;

Graph g1;
pthread_t threads[NUM_THREADS];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

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

void* dfs_aux_thread(void* arg) {
    long thread_id = (long)arg;
    int start = thread_id * (MAX / NUM_THREADS);
    int end = start + (MAX / NUM_THREADS);

    for (int i = start; i < end; i++) {
        pthread_mutex_lock(&mutex);
        printf("Node: %d -------- Thread: %ld\n", i, thread_id);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

void dfs(Graph g) {
    printf("DFS:\n");

    for (long i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, dfs_aux_thread, (void*)i);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
}

int main() {
    createGraph(&g1);
    printGraph(g1);
    clock_t start = clock();
    dfs(g1);
    clock_t end = clock();
    double execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nRunTime: %.6f seconds\n", execution_time);
    return 0;
}
