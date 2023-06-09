#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct edge {
    int key;
    int weight;
    struct edge *next;
} Edge;

typedef struct graph {
    int nv;
    Edge **adj;
} Graph;

void handleError(int n) {
    if (n == 0) {
        printf("ERRORE: Memoria non allocata!");
        exit(-1);
    }
}
    
Graph *createGraph(int nv) {
    Graph *graph = NULL;

    graph = (Graph *) malloc(sizeof(Graph));
    if (graph == NULL) handleError(0);

    graph->adj = (Edge**) calloc(nv, sizeof(Edge *));
    if (graph->adj == NULL && nv > 0) handleError(0);

    graph->nv = nv;

    return graph;
}

Edge *createEdge(int k, int w) {
    Edge *e = NULL;

    e = (Edge *) malloc(sizeof(Edge));
    if (e == NULL) handleError(0);

    e->key = k;
    e->weight = w;
    e->next = NULL;

    return e;
}

void addEdge(Graph *g, int src, int dest, int weight) {
    Edge *e = createEdge(dest, weight);

    if (g->adj[src] == NULL)
        g->adj[src] = e;
    else {
        Edge *curr = g->adj[src];

        while (curr->next != NULL)
            curr = curr->next;

        curr->next = e;
    }
}

Graph *addNode(Graph *g) {
    Edge **tmp = NULL;
    tmp = realloc(g->adj, (g->nv + 1) * sizeof(Edge *));
    if (tmp == NULL) handleError(0);

    g->adj = tmp;
    g->adj[g->nv] = NULL;
    g->nv += 1;

    return g;
}


void printGraph(Graph *g) {
	int i;
    for (i = 0; i < g->nv; i++) {
        printf("Vertice %d: ", i);

        Edge *curr = g->adj[i];
        while (curr != NULL) {
            printf("%d(%d) -> ", curr->key, curr->weight);
            curr = curr->next;
        }
        puts("NULL");
    }
}

void insertRandomVertex(Graph *G1, int g) {
    srand(time(NULL));
    int j = 0;
    for(j; j < g; j++) {
        int s = rand() % G1->nv;
        int v = rand() % G1->nv;
        int w = rand() % 9;
        addEdge(G1, s, v, w);
    }
}

int main() {

    Graph *G1 = createGraph(5);
    
    insertRandomVertex(G1, 10);
    printGraph(G1);

    return 0;
}
