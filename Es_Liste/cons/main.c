#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct list_element{
	int val;
	struct list_element *next;
}iteam;

typedef iteam* list;


list cons(int e, list l){		//di fatto la lista viene stampata in ordine inverso rispetto all'immissione però ha senso perchè per definizione la funzione cons aggiunge l'elemento in testa
	list s;
	s = (list)malloc(sizeof(iteam));
	s->val = e;
	s->next = l;
	return s;
}

void visualizza(list l){
	printf("[");
	while (l != NULL){
		printf(" %d ", l->val);
		l = l->next;
	}
	printf("]");
}


bool ricerca(list l,int e){
	
	while (l != NULL){
		if (l->val == e)
			return true;
		l = l->next;
	}
	return false;
}

list sublist(int pos, list l){
	int i=0;
	while (l != NULL && i++ < pos)		//a seconda di come si interpreta il problema i diventa 1 o 0: se vale 0 vengono saltati i primi pos elementi, se vale 1 si inizia al pos-esimo elemento
		l = l->next;
	return l;
}
int main(void){
	int i = 0;

	list root = NULL;

	do{
		printf("Inserire valore");
		scanf("%d", &i);
		if (i == 0)
			break;
		root = cons(i, root);

	} while (i != 0);
	
	visualizza(root);
	//bool check = ricerca(root, 2);
	list ssub = sublist(2, root);
	visualizza(ssub);
	return 0;
}