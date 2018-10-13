#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct list_element{
	int val;
	struct list_element *next;
}node;

typedef node* list;

list crea(void){
	int count = 0;
	list root, l;
	root = (list)malloc(sizeof(node));
	root->next = NULL;

	printf("Quanti elementi si vogliono inserire?: ");
	scanf("%d", &count);
	if (count == 0)
		return root;


	printf("Inserire il primo valore: ");
	scanf("%d", &root->val);
	l = (list)malloc(sizeof(node));
	root->next = l;


	for (int i = 1; i < count; i++){
		l->next = (list)malloc(sizeof(node));
		printf("Inserire il %d-esimo valore: ", i + 1);
		scanf("%d", &l->val);
		l = l->next;

	}
	l->next = NULL;
	return root;
}

list crea_nofissa(void){
	list root, l;
	int check = 1;
	root = (list)malloc(sizeof(node));
	root->next = NULL;

		printf("Inserire un valore ");
		scanf("%d", &root->val);

		if (root->val == 0){
			root->next = NULL;
			return root;
		}
		
	l = (list)malloc(sizeof(node));
	root->next = l;
	while (1){
		printf("Inserire un valore ");
		scanf("%d", &check);

		if (check == 0){
			l->next = NULL;
			return root;
		}

		l->val = check;
		l->next = (list)malloc(sizeof(node));
		l = l->next;
		
	}
	l->next = NULL;
	return root;
}
void visualizza(list l){

	printf("[");
	while (l->next != NULL){
		printf(" %d ", l->val);
		l = l->next;
	}
	printf("]");
}

int cerca_max(list l){
	int max = 0;
	while (l->next != NULL){
		if (l->val > max)
			max = l->val;
		l = l->next;
	}
	printf("\nIl massimo della lista risulta: %d", max);
	return max;
}

list sommaliste(list a, list b){
	list root, l;
	root = (list)malloc(sizeof(node));
	root->val = a->val + b->val;
	l = (list)malloc(sizeof(node));
	root->next = l;
	a = a->next;
	b = b->next;
	while (a->next != NULL && b->next != NULL){
		
		l->val = a->val + b->val;
		l->next = (list)malloc(sizeof(node));
		l = l->next;
		a = a->next;
		b = b->next;
	}
	l->next = NULL;
	return root;
}

int main(void){
	list l = crea_nofissa();
	list s = crea_nofissa();
	visualizza(l);
	visualizza(s);
	
	list sum = sommaliste(l, s);
	visualizza(sum);
	
	return 0;

}