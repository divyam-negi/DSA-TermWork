#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent;
    int rank;
};

// Function prototypes
int find(struct Subset subsets[], int i);
void Union(struct Subset subsets[], int x, int y);
int compare(const void* a, const void* b);
void KruskalMST(struct Edge edges[], int V, int E);

// Find set of an element i (uses path compression technique)
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Union of two sets of x and y (uses union by rank)
void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Comparator function used by qsort to sort edges based on weight
int compare(const void* a, const void* b) {
    struct Edge* edge1 = (struct Edge*)a;
    struct Edge* edge2 = (struct Edge*)b;
    return edge1->weight - edge2->weight;
}

// Function to construct MST using Kruskal's algorithm
void KruskalMST(struct Edge edges[], int V, int E) {
    struct Edge result[V]; // Stores the resultant MST
    int e = 0; // Index variable used for result[]
    int i = 0; // Index variable used for sorted edges

    // Sort all the edges in non-decreasing order of their weight
    qsort(edges, E, sizeof(edges[0]), compare);

    // Allocate memory for creating V subsets
    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));

    // Initialize subsets
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Number of edges to be taken is V-1
    while (e < V - 1 && i < E) {
        // Pick the smallest edge
        struct Edge next_edge = edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge does not cause cycle, include it in the result
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    // Print the edges of MST along with their weights
    int total_weight = 0;
    printf("Edges of the Minimum Spanning Tree:\n");
    for (i = 0; i < e; ++i) {
        printf("%d -- %d    Weight: %d\n", result[i].src, result[i].dest, result[i].weight);
        total_weight += result[i].weight;
    }
    printf("Total Weight of the Minimum Spanning Tree: %d\n", total_weight);

    free(subsets);
}

// Driver program
int main() {
    int V, E;
    printf("Enter the number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    struct Edge edges[E];
    printf("Enter the source, destination, and weight for each edge:\n");
    for (int i = 0; i < E; ++i)
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);

    KruskalMST(edges, V, E);

    return 0;
}
