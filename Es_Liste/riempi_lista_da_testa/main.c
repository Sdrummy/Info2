#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct list_element{
	float val;
	struct list_element *next;
}node;

typedef node* list;


list leggi(void){
	float sup = 0;
	list root, l;
	
	printf("Inserire il primo valore: ");
	scanf("%f", &sup);
	if (sup < 0){
		root = NULL;
		return root;
	}
	root = (list)malloc(sizeof(node));
	root->val = sup;
	l = (list)malloc(sizeof(node));
	root->next = l;
	while (1){
		printf("Inserire un valore: ");
		scanf("%f", &sup);
		if (sup < 0){
			l->next = NULL;
			return root;
		}
		l->val = sup;
		l->next = (list)malloc(sizeof(node));
		l = l->next;
	}
	l->next = NULL;
	return root;
}

void visualizza(list l){
	printf("[");
	while (l->next!= NULL){
		printf(" %f ", l->val);
		l = l->next;
	}
	printf("]");
	
}

bool verifica_ab(list l,float a,float b){
	if (a > b || a, b < 0)
		return false;
	while (l->next != NULL){
		if (l->val < a || (l->val + (l->next)->val )>= b)
			return false;
		l = l->next;
	}
	return true;
}
int main(void){
	float a, b;
	list root = leggi();
	visualizza(root);
	printf("\nInserire due valori A e B di controllo: ");
	scanf("%f%f", &a, &b);
	bool verifica_parametri = verifica_ab(root, a, b);

	switch (verifica_parametri){
	case 1:
		printf("La verifica ha avuto esito POSITIVO");
		break;
	default:
		printf("La verifica ha avuto esito NEGATIVO");
		break;
	}
	
	return 0;
}