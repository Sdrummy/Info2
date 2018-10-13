#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
	int e;
	struct node *next, *previous;
}item;
typedef item* list;

bool empty(list l){
	return l == NULL;
}
list emptylist(void){
	return NULL;
}
list tail(list l){
	return l->next;
}
list prec(list l){
	return l->previous;
}
int head(list l){
	return l->e;
}
list cons(list l, int e){	//aggiungo in testa
	list root = malloc(sizeof(item));
	root->e = e;
	root->next = l;
	root->previous = emptylist();
	return root;
}
list insCoda(list ultimo, int e){ //aggiungo in coda (devo passare alla funzione l'ultimo nodo della lista originale)
	list nl = malloc(sizeof(item));
	nl->e = e;
	nl->previous = ultimo;
	if (!empty(ultimo))
		ultimo->next = nl;
	nl->next = emptylist();
	return nl; //ritorna la coda di una lista
}

void show_da_testa(list testa){
	putchar('[');
	while (!empty(testa)){
		printf(" %d ", head(testa));
		testa = tail(testa);
	}

	printf("]\n");
}

void show_da_coda(list coda){
	putchar('[');
	while (!empty(coda)){
		printf(" %d ", head(coda));
		coda = prec(coda);
	}
	printf("]\n");
}
list leggi(void){
	list root = emptylist();
	int e;
	do{
		printf("Inserire un elemento, terminare con 0: ");
		scanf("%d", &e);
		if (e == 0)
			break;
		root = insCoda(root, e);
	} while (true);
	//while (!empty(prec(root)))	
	//	root = prec(root);
	return root;
}
list re_wind(list fine){			//ritorno la lista per gestione fifo 
	while (!empty(prec(fine)))
		fine = prec(fine);
	return fine;
}
list coda(list l, int e){	//data una lista(la testa di una lista) aggiunge e in coda e ritorna la coda 
	list t = malloc(sizeof(item)),l1=emptylist();
	t->e = e;
	t->previous = emptylist(), t->next = emptylist();
	if (!empty(l)){
		//return t;
		while (!empty(l)){
			l1 = l;
			l = tail(l);
		}
		l1->next = t;
		t->previous = l1;
	}
	return t;
}
int main(void){
	list l = leggi();
	show_da_coda(l);
	l=re_wind(l);
	list c = coda(l, 21);
	show_da_coda(c);
	//show_da_testa(l);
	
}
