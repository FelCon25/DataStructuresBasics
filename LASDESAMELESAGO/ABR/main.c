#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct T {
    int i;
    struct T *left;
    struct T *right;
}Node;

//create ABR node
Node *createNode(int i) {
    Node *tmp = NULL;

    tmp = (Node*)malloc(sizeof(Node));
    if(tmp == NULL) exit(-1);

    tmp->i = i;
    tmp->left = NULL;
    tmp->right = NULL;

    return tmp;
}

//add Node in an ABR
Node *addNode(Node *root, int i) {
    if(root == NULL) return createNode(i);
    else if(i < root->i) root->left = addNode(root->left, i);
    else root->right = addNode(root->right, i);
    return root;
}

//print the BST in order
void printTree(Node *root) {
    if(root != NULL) {
        printTree(root->left);
        printf("%d ", root->i);
        printTree(root->right);
    }
}

//free the whole tree
void freeBST(Node *root) {
    if(root != NULL) {
        freeBST(root->left);
        freeBST(root->right);
        free(root);
    }
}

//search the leftest element from a node
Node *searchMin(Node *root) {
    if (root == NULL)
        return root;

    if (root->left == NULL)
        return root;
    return searchMin(root->left);
}

//remove Node from BST
Node *removeNode(Node *root, int i) {
    if(root == NULL) return root;

    if(i < root->i) root->left = removeNode(root->left, i);
    else if(i > root->i) root->right = removeNode(root->right, i);

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
        else {
            Node *tmp = searchMin(root->right);
            root->i = tmp->i;
            root->right = removeNode(root->right, tmp->i);
        }
    }
    return root;
}

int findMax(Node *root) {
    if(root == NULL) return INT_MIN;

    int maxLeft = findMax(root->left);
    int maxRight = findMax(root->right);

    int v = INT_MIN;
    if(maxLeft > maxRight) v = maxLeft;
    else v = maxRight;

    if(v < root->i) v = root->i;

    return v;
}


int findMin(Node *root) {
    if(root == NULL) return INT_MAX;

    int minLeft = findMin(root->left);
    int minRight = findMin(root->right);

    int v = INT_MAX;
    if(minLeft < minRight) v = minLeft;
    else v = minRight;

    if(v > root->i) v = root->i;

    return v;
}

int findMinOfK(Node *root, int k) {
    if(root == NULL) return -1;
    if(root->i == k) return findMin(root);
    else if(k < root->i) findMinOfK(root->left, k);
    else findMinOfK(root->right, k);
}

int isBST(Node *root) {
    if(root == NULL) return 1;

    if(root->left != NULL && findMax(root->left) > root->i)
        return 0;
    if(root->right != NULL && findMin(root->right) < root->i)
        return 0;

    if(!isBST(root->left) || !isBST(root->right))
        return 0;

    return 1;
}

Node *merge(Node *T1, Node *T2) {
    Node *T3 = NULL;
    if(T1 == NULL) return T2;
    if(T2 == NULL) return T1;

    T3 = createNode(T1->i + T2->i);

    T3->left = merge(T1->left, T2->left);
    T3->right = merge(T1->right, T2->right);

    return T3;
}


int areIdentical(Node *T1, Node *T2) {
    if(T1 == NULL && T2 == NULL) return 1;

    if(T1 == NULL || T2 == NULL) return 0;

    if(T1->i != T2->i) return 0;

    return (T1->i == T2->i
            && areIdentical(T1->left, T2->left)
            && areIdentical(T2->right, T2->right));
}

//check if T2 is a subtree of T1
int isSubtree(Node *T1, Node *T2) {
    if(T2 == NULL) return 1;

    if(T1 == NULL) return 0;

    if(areIdentical(T1, T2)) return 1;

    return isSubtree(T1->left, T2) || isSubtree(T1->right, T2);
}

int checkABR(Node *root) {
    if(root == NULL) return 1;

    if()
}


int main() {
    Node *h = NULL;

    h = addNode(h, 50);
    h = addNode(h, 30);
    h = addNode(h, 70);
    h = addNode(h, 20);
    h = addNode(h, 40);
    h = addNode(h, 60);
    h = addNode(h, 23);
    h = addNode(h, 160);
    h = addNode(h, 88);

    Node *t = NULL;

    t = addNode(t, 60);
    t = addNode(t, 70);
    t = addNode(t, 23);
    t = addNode(t, 88);

    puts("\nTree:");
    printTree(h);
    puts("\nTree 2:");
    printTree(t);
    printf("\nT2 is subtree of T: %d", isSubtree(h, t));
    int i = 160;
    printf("\nRemove %d:\n", i);
    h = removeNode(h, i);
    printTree(h);
    printf("\nmin dal sottalbero %d: %d \n", 30, findMinOfK(h, 30));
    free(h);
}
