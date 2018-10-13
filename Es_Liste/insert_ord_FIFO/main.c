#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct list_element{
	int value;
	struct list_element *next;

}iteam;

typedef iteam* list;

list ins_ord(list l, int e);

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
		root = ins_ord(root, check);
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

list ins_ord(list l, int e){
	list l1 = emptylist();
	list root=l,t=emptylist();

	t = cons(t, e);
	if (empty(l))
		return t;

	while (!empty(l)){
		l1 = l;
		l = tail(l);
	}
	l1->next = t;

	return root;

}

void dealloca(list l){	/*Importante funzione per la deallocazione della memoria, si sfrutta una shallow copy (viene di fatto copiato l'indirizzo in memoria in un altra variabile che poi può essere deallocata producendo lo stesso effetto che si avrebbe con free di l stesso) */
	list temp;

	while (!empty(l)){
		temp = l;
		l = tail(l);
		free(temp);
	}
	
}

int main(void){
	list root = riempi();
	show(root);
	dealloca(root);
}