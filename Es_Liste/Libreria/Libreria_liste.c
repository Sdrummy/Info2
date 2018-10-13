#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct list_element{
	int value;
	struct list_element *next;

}iteam;

typedef iteam* list;

list cons(list l, int e){
	list root = malloc(sizeof(iteam));
	root->value = e;
	root->next = l;
	return root;
}
list emptylist(void){
	return NULL;
}
bool empty(list l){
	return(l == NULL);
}
list tail(list l){
	return l->next;
}
int head(list l){
	return l->value;
}
list riempi(void){
	list root = emptylist();
	int check;
	printf("\nInserire valori, terminare con zero:\n");
	do{
		scanf("%d", &check);
		if (check == 0)
			break;
		root = cons(root, check);
	} while (check != 0);
	return root;
}
void show(list l){
	printf("[ ");
	while (!empty(l)){
		printf(" %d ", l->value);
		l = tail(l);
	}
	printf(" ]");
}
bool cerca(list l, int e){
	while (!empty(l)){
		if (l->value == e)
			return true;
		l = tail(l);
	}
	return false;
}