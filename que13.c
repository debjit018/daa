#include <stdio.h>
#include <stdlib.h>

struct Graph {
    int V;
    int **adjMatrix;
};

struct Graph* createGraph(int V);
void DFS(struct Graph* graph, int startVertex, int *visited);
void printGraph(struct Graph* graph);

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

    printf("DFS Traversal starting from vertex 0:\n");
    int *visited = (int*)calloc(V, sizeof(int));
    DFS(graph, 0, visited);
    
    printf("\n");

    return 0;
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

void DFS(struct Graph* graph, int startVertex, int *visited) {
    visited[startVertex] = 1;
    printf("%d ", startVertex);

    for (int i = 0; i < graph->V; i++) {
        if (graph->adjMatrix[startVertex][i] == 1 && !visited[i]) {
            DFS(graph, i, visited);
        }
    }
}

void printGraph(struct Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        for (int j = 0; j < graph->V; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}
