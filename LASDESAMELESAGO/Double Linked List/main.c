#include <stdio.h>
#include <stdlib.h>

typedef struct N {
    int i;
    struct N *prev;
    struct N *next;
}Node;

void handleErrors(int i) {
    if(i == 0) {
        printf("Memoria non allocata!!");
        exit(-1);
    }
}

Node *createNode(int i) {
    Node *tmp = NULL;

    tmp = (Node*)malloc(sizeof(Node));
    if(tmp == NULL) handleErrors(0);

    tmp->i = i;
    tmp->prev = NULL;
    tmp->next = NULL;

    return tmp;
}

Node *addNode(Node *head, int i) {
    Node *tmp = createNode(i);

    if(head != NULL) {
        tmp->next = head;
        head->prev = tmp;
    }
    return tmp;
}

Node *removeNode(Node *head, int i) {
    if(head == NULL) return head;

    head->next = removeNode(head->next, i);

    if(head->i == i) {
        Node *tmp = head->next;
        if(tmp != NULL)
            tmp->prev = head->prev;
        free(head);
        return tmp;
    }
    return head;
}

void printList(Node *head) {
    if(head != NULL) {
        printf("%d ", head->i);
        printList(head->next);
    }
}

void freeList(Node *head) {
    if(head != NULL) {
        Node *tmp = head->next;
        free(head);
        freeList(tmp);
    }
}

Node *removeNeg(Node *L1, Node **L2) {
    if(L1 == NULL) return NULL;

    L1->next = removeNeg(L1->next, L2);

    if(L1->i < 0) {
        Node *tmp = L1->next;
        if(tmp != NULL) tmp->prev = L1->prev;
        *L2 = addNode(*L2, L1->i);
        free(L1);
        return tmp;
    }
    return L1;
}

Node *removePos(Node **L1, Node *L2) {
    if(L2 == NULL) return NULL;

    L2->next = removePos(L1, L2->next);

    if(L2->i > 0) {
        Node *tmp = L2->next;
        if(tmp != NULL) tmp->prev = L2->prev;
        *L1 = addNode(*L1, L2->i);
        free(L2);
        return tmp;
    }
    return L2;
}

void removeNegPos(Node **L1, Node **L2) {
    *L2 = removePos(L1, *L2);
    *L1 = removeNeg(*L1, L2);
}

Node *fillList(Node *head) {
    int numero, nodo, i;
    printf("Quanti valori inserire nella lista?: ");
    scanf("%d", &numero);
    for(i = 0; i < numero; i++) {
        printf("%d: Inserire il valore: ", i+1);
        scanf("%d", &nodo);
        head = addNode(head, nodo);
    }
    return head;
}

int main() {

    Node *h = NULL;
    Node *g = NULL;

    h = fillList(h);

    g = fillList(g);

    puts("\nLa lista 1: ");
    printList(h);

    puts("\nLa lista 2: ");
    printList(g);

    puts("\nLa nuova lista");
    removeNegPos(&h, &g);

    printList(h);
    puts("");
    printList(g);
    puts("");
    freeList(h);
    freeList(g);
    system("PAUSE");

}
/* possibile input
7
1
4
-7
3
8
-34
3
5
-2
3
6
-5
12
*/