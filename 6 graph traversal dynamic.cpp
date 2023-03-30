#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

int visited[MAX_VERTICES];

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node** adjLists;
};

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->vertex = dest;
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

void dfs(struct Graph* graph, int vertex) {
    visited[vertex] = 1;
    printf("%d ", vertex);
    struct Node* adjList = graph->adjLists[vertex];
    while (adjList != NULL) {
        int connectedVertex = adjList->vertex;
        if (!visited[connectedVertex]) {
            dfs(graph, connectedVertex);
        }
        adjList = adjList->next;
    }
}

void bfs(struct Graph* graph, int startVertex) {
    visited[startVertex] = 1;
    int queue[MAX_VERTICES];
    int front = -1;
    int rear = -1;
    queue[++rear] = startVertex;

    while (front != rear) {
        int currentVertex = queue[++front];
        printf("%d ", currentVertex);

        struct Node* adjList = graph->adjLists[currentVertex];

        while (adjList != NULL) {
            int connectedVertex = adjList->vertex;

            if (!visited[connectedVertex]) {
                visited[connectedVertex] = 1;
                queue[++rear] = connectedVertex;
            }
            adjList = adjList->next;
        }
    }
}

int main() {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    printf("Enter the number of vertices: ");
    scanf("%d", &graph->numVertices);

    graph->adjLists = (struct Node*) malloc(graph->numVertices sizeof(struct Node*));

    int i;
    for (i = 0; i < graph->numVertices; i++) {
        graph->adjLists[i] = NULL;
    }

    int choice = 0;
    int src, dest;
   do {
        printf("\n1. Add edge\n");
        printf("2. BFS traversal\n");
        printf("3. DFS traversal\n");
        printf("4. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter source and destination vertex: ");
                scanf("%d %d", &src, &dest);
                addEdge(graph, src, dest);
                break;
            case 2:
                for (i = 0; i < graph->numVertices; i++) {
                    visited[i] = 0;
                }
                printf("Enter starting vertex: ");
                scanf("%d", &src);
                bfs(graph, src);
                break;
            case 3:
                for (i = 0; i < graph->numVertices; i++) {
                    visited[i] = 0;
                }
                printf("Enter starting vertex: ");
                scanf("%d", &src);
                dfs(graph, src);
                break;
            case 4:
                printf("thank you");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }while(choice!=4);

    return 0;
}
