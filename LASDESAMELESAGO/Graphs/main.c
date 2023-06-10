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

void *addNode(Graph *g) {
    Edge **tmp = NULL;
    
    tmp = realloc(g->adj, (g->nv + 1) * sizeof(Edge *));
    if (tmp == NULL) handleError(0);

    g->adj = tmp;
    g->adj[g->nv] = NULL;
    g->nv += 1;
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

void removeEdge(Graph *graph, int src, int dest) {
    Edge *curr = graph->adj[src];
    Edge *prev = NULL;

    while (curr != NULL) {
        if (curr->key == dest) {
            if (prev == NULL) {
                graph->adj[src] = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void dfsRec(Graph *g, int i, int *aux) {
    Edge *e;
    aux[i] = 1;
    for (e = g->adj[i]; e; e = e->next)
        if (!aux[e->key]) {
            printf("%d,", e->key);
            dfsRec(g, e->key, aux);
        }
}

void dfs(Graph *g) {
    int i;
    int *aux = calloc(g->nv, sizeof(int));

    if (!aux) handleError(0);
    else {
        for (i = 0; i < g->nv; i++)
            if (!aux[i]) {
                printf("\n%d", i);
                dfsRec(g, i, aux);
            }
        free(aux);
    }
}

void removeNode(Graph *graph, int node) {
	int i;
    for (i = 0; i < graph->nv; i++) {
        removeEdge(graph, i, node);
    }

    Edge *curr = graph->adj[node];
    while (curr != NULL) {
        Edge *next = curr->next;
        free(curr);
        curr = next;
    }

    for (i = node + 1; i < graph->nv; i++) {
        graph->adj[i - 1] = graph->adj[i];
    }

    Edge **edge = realloc(graph->adj, (graph->nv - 1) * sizeof(Edge *));
    if (edge == NULL) handleError(0);
    graph->adj = edge;
    graph->nv -= 1;
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
    
    addNode(G1);
    puts("\nAggiungo un nodo");
    printGraph(G1);
    puts("\nRimuovo un nodo");
    removeNode(G1, 4);
    printGraph(G1);

    return 0;
}
