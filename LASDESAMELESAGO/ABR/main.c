#include <stdio.h>
#include <stdlib.h>

typedef struct T {
	int i;
	struct T *left;
	struct T *right;
}Node;

void handleErrors(int i) {
	if(i == 0) {
		printf("Memoria non allocata!");
		exit(-1);
	}
}

Node *createNode(int i) {
	Node *tmp = NULL;
	
	tmp = malloc(sizeof(Node));
	if(tmp == NULL) handleErrors(0);
	
	tmp->i = i;
	tmp->left = NULL;
	tmp->right = NULL;
}

Node *insertNode(Node *root, int i) {
	if(root == NULL) return createNode(i);
	
	if(root->i >= i) root->left = insertNode(root->left, i);
	else if(root->i < i) root->right = insertNode(root->right, i);
	
	return root;
}

void preorder(Node *root) {
	if(root != NULL){
		preorder(root->left);
		printf("%d ", root->i);
		preorder(root->right);
	}
}

int searchValue(Node *root, int i) {
	if(root == NULL) return 0;
	else if(root->i > i) searchValue(root->left, i);
	else if(root->i < i) searchValue(root->right, i);
	else if(root->i == i) return 1;
}

Node *searchMin(Node *root) {
	if(root != NULL) {
		if(root->left != NULL) searchMin(root->left);
		else return root;
	}
}

Node *removeNode(Node *root, int i) {
	if(root == NULL) return root;
	
	if(i < root->i)
		root->left = removeNode(root->left, i);
	else if(i > root->i)
		root->right = removeNode(root->right, i);
	else {
		if(root->left == NULL) {
			Node *tmp = root->right;
			free(root);
			return tmp;
		}
		else if(root->right == NULL) {
			Node *tmp = root->left;
			free(root);
			return tmp;
		}
		
		Node *tmp = searchMin(tmp->right);
		root->i = tmp->i;
		root->right = removeNode(root->right, tmp->i);
	}
	
	return root;
}

int main(int argc, char *argv[]) {
	Node *r = NULL;
	
	r = insertNode(r, 10);
	r = insertNode(r, 210);
	r = insertNode(r, 310);
	r = insertNode(r, 410);
	r = insertNode(r, 160);
	r = insertNode(r, 120);
	r = insertNode(r, 4);
	r = insertNode(r, 140);
	r = insertNode(r, 180);
	
	preorder(r);
	
	r = removeNode(r, 140);
	printf("\n");
	preorder(r);
}
