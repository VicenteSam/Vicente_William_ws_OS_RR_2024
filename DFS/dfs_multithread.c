#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MAX 10
#define NUM_THREAD 4

typedef struct {
    long graph[MAX][MAX];
    long visited[MAX];
    long start_vertex;
} Graph;

typedef struct {
    Graph *g;
    int thread_id;
} ThreadArgs;

pthread_t threads[NUM_THREAD];
pthread_mutex_t mutex;


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

void dfs(Graph *g, int vertex) {
    printf("Visiting vertex %d from thread %02ld\n", vertex, pthread_self());
    visited[vertex] = 1;
        
        
    for (int j = 0; j < MAX; j++) {
        pthread_mutex_unlock(&mutex);
        if (g->graph[vertex][j] == 1 && visited[j] == 0)
            dfs(g, j);
        pthread_mutex_lock(&mutex);
    }

    pthread_mutex_unlock(&mutex);
}

void *dfs_thread(void *args) {
    ThreadArgs *t_args = (ThreadArgs *)args;
    Graph *g = t_args->g;
    int thread_id = t_args->thread_id;

    for (int i = thread_id; i < MAX; i += NUM_THREAD) {
        pthread_mutex_lock(&mutex);
        if (!g->visited[i]) {
            dfs(g, i);
        }
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}


int main() {
    Graph g1;
    createGraph(&g1);
    printGraph(g1);

    pthread_mutex_init(&mutex, NULL);
    ThreadArgs args[NUM_THREAD];
    for (int i = 0; i < NUM_THREAD; i++) {
        args[i].g = &g1;
        args[i].thread_id = i;
        pthread_create(&threads[i], NULL, dfs_thread, (void *)&args[i]);
    }

    for (int i = 0; i < NUM_THREAD; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}
