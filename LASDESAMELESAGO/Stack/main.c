#include <stdio.h>
#define MAX 200

void push(int S[], int v) {
	S[++S[0]] = v;
}

int pop(int S[]) {
	S[0]--;
	return S[S[0]+1];
}

int empty_stack(int S[]) {
	return S[0] == 0;
}

int full_stack(int S[]) {
	return S[0] == MAX;
}

void new_stack(int S[]) {
	int n, v;
	
	printf("Quanti elementi inserire nello stack?\n");
	scanf("%d", &n);
	
	int i;
	for(i = 0; i < n; i++) {
		printf("Inserire il %d valore: ", i+1);
		scanf("%d", &v);
		push(S, v);
	}
}

void print_stack(int S[]) {
	int v;
	if(!empty_stack(S)) {
		v = pop(S);
		printf("%d ", v);
		print_stack(S);
		push(S, v);
	}
}

void remove_from_stack(int S[], int v) {
	if(!empty_stack(S)) {
		int el = pop(S);
		remove_from_stack(S, v);
		if(el != v)
			push(S, el);
	}
}

int main(int argc, char *argv[]) {
	int stack[MAX+1] = {0};
	int v;
	
	new_stack(stack);
	print_stack(stack);
	
	printf("Elemento da eliminare: ");
	scanf("%d", &v);
	
	remove_from_stack(stack, v);
	print_stack(stack);
	return 0;
}
