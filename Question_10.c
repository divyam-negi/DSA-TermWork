#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node** adjLists;
};

// Function prototypes
struct Node* createNode(int);
struct Graph* createGraph(int);
void addEdge(struct Graph*, int, int);
void DFS(struct Graph*, int);
void displayGraph(struct Graph*);

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with 'numVertices' vertices
struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;

    graph->adjLists = (struct Node**)malloc(numVertices * sizeof(struct Node*));

    for (int i = 0; i < numVertices; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Uncomment the following lines for undirected graph
    /*
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
    */
}

// Recursive function for DFS traversal
void DFSUtil(struct Graph* graph, int vertex, int visited[]) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    struct Node* adjList = graph->adjLists[vertex];
    while (adjList != NULL) {
        int connectedVertex = adjList->data;
        if (!visited[connectedVertex])
            DFSUtil(graph, connectedVertex, visited);
        adjList = adjList->next;
    }
}

// Function to perform DFS traversal of the graph
void DFS(struct Graph* graph, int startVertex) {
    int* visited = (int*)calloc(graph->numVertices, sizeof(int));

    printf("DFS Traversal starting from vertex %d: ", startVertex);
    DFSUtil(graph, startVertex, visited);
    printf("\n");

    free(visited);
}

// Function to display the adjacency list representation of the graph
void displayGraph(struct Graph* graph) {
    printf("Adjacency List Representation of the Graph:\n");
    for (int i = 0; i < graph->numVertices; i++) {
        struct Node* temp = graph->adjLists[i];
        printf("Vertex %d: ", i);
        while (temp != NULL) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    int choice, numVertices, src, dest, startVertex;
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &numVertices);

    struct Graph* graph = createGraph(numVertices);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Edge\n");
        printf("2. Perform DFS Traversal\n");
        printf("3. Display Adjacency List\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter source and destination vertices for the edge: ");
                scanf("%d %d", &src, &dest);
                addEdge(graph, src, dest);
                break;
            case 2:
                printf("Enter the start vertex for DFS traversal: ");
                scanf("%d", &startVertex);
                DFS(graph, startVertex);
                break;
            case 3:
                displayGraph(graph);
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}

