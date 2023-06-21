#include <stdio.h>
#define MAX 200

int emptyQueue(int Q[]) {
    return Q[0] == 0;
}

int fullQueue(int Q[]) {
    return Q[0] == Q[MAX + 1];
}

void enqueue(int Q[], int v) {
    Q[Q[MAX + 1]] = v;
    if(Q[0] == 0) Q[0] = 1;
    Q[MAX + 1] = (Q[MAX + 1] % MAX) + 1;
}

int dequeue(int Q[]) {
    int v = Q[Q[0]];
    Q[0] = (Q[0] % MAX) + 1;
    if(Q[0] == Q[MAX + 1]) {
        Q[0] = 0;
        Q[MAX + 1] = 1;
    }
    return v;
}

void reverse(int Q[]) {
    int val;
    if(!emptyQueue(Q)) {
        val = dequeue(Q);
        reverse(Q);
        enqueue(Q, val);
    }
}

void stampaQueue(int Q[]) {
    if(!emptyQueue(Q)) {
        int v = dequeue(Q);
        printf("%d ", v);
        stampaQueue(Q);
        enqueue(Q, v);
    }
}

void stampa(int Q[]) {
    stampaQueue(Q);
    puts("");
    reverse(Q);
}

void newQueue(int *q) {
    q[0] = 0;
    q[MAX+1] = 1;
}

static void moltiplica_queue(int Q[]){
    if (emptyQueue(Q)) return;
    int val[3];
    int c;
    for(c = 0; !emptyQueue(Q) && c < 3; c++){
        val[c] = dequeue(Q);
    }
    moltiplica_queue(Q);
    if (c == 3) enqueue(Q, val[0]*val[1]*val[2]);
    else for(; c > 0; c--) enqueue(Q, val[c-1]);
}

void moltiplica(int Q[]){
    moltiplica_queue(Q);
    reverse(Q);
}
int main() {
    int q[MAX+2];
    newQueue(q);
    enqueue(q, 4);
    enqueue(q, 5);
    enqueue(q, 6);
    enqueue(q, 7);
    enqueue(q, 3);
    stampa(q);
    stampa(q);

    return 0;
}
