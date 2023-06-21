#include <stdio.h>
#include <limits.h>
#define MAX 200

int isEmpty(int s[]) {
    return s[0] == 0;
}

int isFull(int s[]) {
    return s[0] == MAX;
}

void push(int s[], int v) {
    s[0]++;
    s[s[0]] = v;
}

int pop(int s[]) {
    s[0]--;
    return s[s[0] + 1];
}

void printStack(int s[]) {
    if(!isEmpty(s)) {
        int v = pop(s);
        printf("%d | ", v);
        printStack(s);
        push(s, v);
    }
}

void removeEl(int s[], int v) {
    if(!isEmpty(s)) {
        int t = pop(s);
        removeEl(s, v);
        if(t != v) push(s, t);
    }
}

int sumStack(int *S){
    if(!isEmpty(S)) {
        int v = pop(S);
        int s = v + sumStack(S);
        push(S, v);
        return s;
    }
    else return 0;
}

int searchMin(int *s) {
    if(!isEmpty(s)) {
        int v = pop(s);
        int b = searchMin(s);
        push(s, v);
        if(v < b) return v;
        else return b;
    }
    else return INT_MAX;
}

int main() {
    int s[MAX + 1] = {0};
    push(s,  3);
    push(s,  5);
    push(s,  6);
    push(s,  1);
    push(s,  7);
    push(s,  8);
    push(s,  9);
    printStack(s);

    printf("Somma %d", sumStack(s));
    printf("\nIl min %d", searchMin(s));

}

