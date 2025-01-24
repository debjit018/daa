#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Queue {
    int *arr;
    int front, rear;
    int size;
};

struct Graph {
    int V;
    int **adjMatrix;
};

struct Queue* createQueue(int size);
void enqueue(struct Queue* queue, int value);
int dequeue(struct Queue* queue);
bool isQueueEmpty(struct Queue* queue);
void BFS(struct Graph* graph, int startVertex, bool *visited);
struct Graph* createGraph(int V);

int main() {
    int V, E, u, v;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    struct Graph* graph = createGraph(V);

    printf("Enter the number of edges: ");
    scanf("%d", &E);

    for (int i = 0; i < E; i++) {
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);
        graph->adjMatrix[u][v] = 1;
        graph->adjMatrix[v][u] = 1;  // For undirected graph
    }

    printf("BFS Traversal starting from vertex 0:\n");
    bool *visited = (bool*)calloc(V, sizeof(bool));
    BFS(graph, 0, visited);
    
    printf("\n");

    return 0;
}

struct Queue* createQueue(int size) {
    struct Queue* queue = (struct Queue*)calloc(1, sizeof(struct Queue));
    queue->arr = (int*)calloc(size, sizeof(int));
    queue->front = queue->rear = -1;
    queue->size = size;
    return queue;
}

void enqueue(struct Queue* queue, int value) {
    if (queue->rear == queue->size - 1) {
        printf("Queue is full\n");
        return;
    }
    if (queue->front == -1) {
        queue->front = 0;
    }
    queue->arr[++queue->rear] = value;
}

int dequeue(struct Queue* queue) {
    if (queue->front == -1) {
        printf("Queue is empty\n");
        return -1;
    }
    int item = queue->arr[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front++;
    }
    return item;
}

bool isQueueEmpty(struct Queue* queue) {
    return queue->front == -1;
}

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)calloc(1, sizeof(struct Graph));
    graph->V = V;
    graph->adjMatrix = (int**)calloc(V, sizeof(int*));
    for (int i = 0; i < V; i++) {
        graph->adjMatrix[i] = (int*)calloc(V, sizeof(int));
    }
    return graph;
}

void BFS(struct Graph* graph, int startVertex, bool *visited) {
    struct Queue* queue = createQueue(graph->V);
    visited[startVertex] = true;
    enqueue(queue, startVertex);

    while (!isQueueEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        for (int i = 0; i < graph->V; i++) {
            if (graph->adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                enqueue(queue, i);
            }
        }
    }
}
