#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct list_element{
	int value;
	struct list_element *next;
}iteam;

typedef iteam* list;

void show(list l){
	printf("[ ");
	while (l->next != NULL){
		printf(" %d ", l->value);
		l = l->next;
	}
	printf(" ]\n");
}
bool cerca(list l, int e){
	while (l->next != NULL){
		if (l->value == e)
			return true;
		l = l->next;
	}
	return false;
}

list riempi(void){
	int val;
	list root = malloc(sizeof(iteam));
	list l;
	printf("Inserire valori terminare con 0:\n");
	scanf("%d", &val);
	if (val == 0)
		return NULL;
	root->value = val;
	l = (list)malloc(sizeof(iteam));
	root->next = l;

	while (val != 0){
		scanf("%d", &val);
		if (val == 0)
			break;

		l->value = val;
		l->next = (list)malloc(sizeof(iteam));
		l = l->next;
	}
	l->next = NULL;
	return root;

}
list rimuovi_doppie(list l){
	list root, g;
	int sup;
	root = (list)malloc(sizeof(iteam));
	root->value = l->value;
	sup = root->value;
	l = l->next;
	g = (list)malloc(sizeof(iteam));
	root->next = g;
	while (l->next != NULL){

		while (l->value == sup && l->next != NULL)
			l = l->next;
		if (l->next == NULL)
			break;
		g->value = l->value;
		sup = g->value;
		g->next = (list)malloc(sizeof(iteam));
		g = g->next;
		l = l->next;
	}
	g->next = NULL;
	return root;
}

list cerca_uguali_no_ripetuti(list l1, list l2){
	list root, g;
	root = (list)malloc(sizeof(iteam));

	while ( !cerca(l1, l2->value) && l2->next!=NULL)
		l2 = l2->next;
		
	
	if ( l2==NULL)
		return NULL;

	root->value = l2->value;
	g = (list)malloc(sizeof(iteam));
	root->next = g;
	
	l2 = l2->next;

	while (l2->next!=NULL){
		if (cerca(l1, l2->value)){
			g->value = l2->value;
			g->next = (list)malloc(sizeof(iteam));
			g = g->next;
		}
		
		l2 = l2->next;
	}
	g->next = NULL;
	root = rimuovi_doppie(root);
	return root;
}
int main(void){
	list root1 = riempi();
	show(root1);
	list root2 = riempi();
	show(root2);
	list root = cerca_uguali_no_ripetuti(root1, root2);
	show(root);
}