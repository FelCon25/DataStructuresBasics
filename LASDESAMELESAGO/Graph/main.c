#include <stdio.h>
#include <stdlib.h>

typedef struct E {
	int key;
	int w;
	struct E *next;
}Edge;

typedef struct G {
	int nv;
	Edge **adj;
}Graph;

Graph *createGraph(int nv) {
	Graph *g = NULL;

	g = (Graph*)malloc(sizeof(Graph));
	if(g == NULL) exit(-1);

	g->adj = (Edge**)calloc(nv, sizeof(Edge*));
	if(g->adj == NULL) exit(-1);

	g->nv = nv;

	return g;
}

Edge *createEdge(int key, int w) {
	Edge *e = NULL;

	e = (Edge*)malloc(sizeof(Edge));
	if(e == NULL) exit(-1);

	e->key = key;
	e->w = w;
	e->next = NULL;

	return e;
}

void addEdge(Graph *g, int src, int dest, int w) {
	Edge *e = createEdge(dest, w);

	if(g->adj[src] == NULL) g->adj[src] = e;
	else {
		Edge *curr = g->adj[src];
		while(curr->next != NULL)
			curr = curr->next;
		curr->next = e;
	}
}

void printGraph(Graph *g) {
	int i;
	for(i = 0; i < g->nv; i++) {

		Edge *curr = g->adj[i];
		printf("Vertex %d: ", i);
		while(curr != NULL) {
			printf("%d(%d) -> ", curr->key, curr->w);
			curr = curr->next;
		}
		puts("NULL;");
	}
}

void freeGraph(Graph *g) {
	int i;
	for(i = 0; i < g->nv; i++) {
		Edge *curr = g->adj[i];
		while(curr != NULL) {
			Edge *tmp = curr->next;
			free(curr);
			curr = tmp;
		}
	}
	free(g->adj);
	free(g);
}

Graph *fillGraph() {
	int nv, na, i, src, dest, weight;
	Graph *g = NULL;
	printf("Inserire il numero di nodi del grafo: ");
	scanf("%d", &nv);
	g = createGraph(nv);

	printf("Inserire il numero di archi: ");
	scanf("%d", &na);


	for(i = 0; i < na; i++) {
		printf("%d: Inserire l'arco (fonte, destinazione, peso): ", i+1);
		scanf("%d %d %d", &src, &dest, &weight);
		addEdge(g, src, dest, weight);
	}

	return g;
}

void removeEdge(Graph*g, int src, int dest) {
	Edge *prev = NULL;
	Edge *curr = g->adj[src];

	while(curr != NULL) {
		if(curr->key == dest) {
			if(prev == NULL) g->adj[src] = curr->next;
			else prev->next = curr->next;
			free(curr);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}

void removeNode(Graph *g, int src) {
	int i;
	for(i = 0; i < g->nv; i++)
		removeEdge(g, i, src);

	Edge *curr = g->adj[src];
	while(curr != NULL) {
		Edge *tmp = curr->next;
		free(curr);
		curr = tmp;
	}
    g->adj[src] = NULL;

	for(i = 0; i < g->nv; i++) {
		curr = g->adj[i];
		while(curr != NULL) {
			if(curr->key > src) curr->key--;
			curr = curr->next;
		}
	}

	for(i = src + 1; i < g->nv; i++)
		g->adj[i - 1] = g->adj[i];

	Edge **e = NULL;
	e = (Edge**)realloc(g->adj, (g->nv-1)*sizeof(Edge*));
	if(e == NULL) exit(-1);

	g->adj = e;
	g->nv--;
}

int inDegree(Graph *g, int src) {
    int i = 0;
    int in = 0;
    for(; i < g->nv; i++) {
        Edge *curr = g->adj[src];
        while(curr != NULL) {
            if(curr->key == src) in++;
            curr = curr->next;
        }
    }
    return in;
}

int outDegree(Graph *g, int src) {
    int out = 0;
    Edge *curr = g->adj[src];

    while(curr != NULL) {
        out++;
        curr = curr->next;
    }
    return out;
}

//funzione per rimuovere tutti gli archi con peso pari
//e tutti i nodi con grado uscente dispari
void removeOddEven(Graph *g) {
    int i;

    for(i = 0; i < g->nv; i++) {
        Edge *curr = g->adj[i];
        Edge *prev = NULL;
        while(curr != NULL) {
            if(curr->w % 2 == 0) {
                if(prev == NULL) {
                    g->adj[i] = curr->next;
                    free(curr);
                    curr = g->adj[i];
                }
                else{
                    prev->next = curr->next;
                    free(curr);
                    curr = prev->next;
                }
            }
            else{
                prev = curr;
                curr = curr->next;
            }
        }
    }
    for(i = 0; i < g->nv; i++) {
        if(outDegree(g, i) % 2 != 0) {
            removeNode(g, i);
            i--;
        }
    }
}

int main(int argc, char *argv[]) {
	Graph *g = NULL;
	g = fillGraph();
	puts("Il grafo:");
	printGraph(g);

    puts("Rimuovo i pari: ");
    removeOddEven(g);
    printGraph(g);

	puts("Rimuovo il nodo 1");
	removeNode(g, 1);
	printGraph(g);
	freeGraph(g);
}

/* possibile input:
5
12
0 1 5
0 3 6
0 6 2
1 4 5
1 0 6
1 2 2
3 4 5
3 1 6
3 2 2
4 3 5
4 0 6
4 1 2
*/