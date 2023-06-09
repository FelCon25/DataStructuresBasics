#include <stdio.h>
#include <stdlib.h>

typedef struct N {
	int i;
	struct N *next;
}Node;

void handleErrors(int i) {
	if(i == 0) {
		printf("Memoria non allocata");
		exit(-1);
	}
}

Node *createNode(int i) {
	Node *tmp = NULL;
	
	tmp = malloc(sizeof(Node));
	if(tmp == NULL) handleErrors(i);
	
	tmp->i = i;
	tmp->next = NULL;
	
	return tmp;
}

Node *insertNode(Node *head, int i) {
	if(head == NULL) return createNode(i);
	head->next = insertNode(head->next, i);
	return head;
}

Node *removeNode(Node *head, int i) {
	if(head == NULL) return head;
	head->next = removeNode(head->next, i);
	if(head->i == i) {
		Node *tmp = head->next;
		free(head);
		head = tmp;
	}
	return head;
}

void stampList(Node *head) {
	while(head != NULL) {
		printf("%d -> ", head->i);
		head = head->next;
	}
	puts("NULL");
}

void freeList(Node *head) {
	if(head != NULL) {
		Node *tmp = head->next;
		free(head);
		freeList(tmp);
	}	
}


int main(int argc, char *argv[]) {
	Node *h = NULL;
	h = insertNode(h, 5);
	h = insertNode(h, 15);
	h = insertNode(h, 25);
	h = insertNode(h, 35);
	h = insertNode(h, 45);
	h = insertNode(h, 55);
	stampList(h);
	h = removeNode(h, 35);
	stampList(h);
	freeList(h);
}
