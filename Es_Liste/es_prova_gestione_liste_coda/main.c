#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node{
	int e;
	struct node *next, *previous;
}item;
typedef item* list;

typedef struct{
	list head, tail;
}tcoda;
typedef tcoda* coda;

bool empty(list l){
	return l == NULL;
}
bool emptyque(coda c){
	return c == NULL;
}
list emptylist(void){
	return NULL;
}
coda emptycoda(void){
	return NULL;
}
int testa(list l){
	return l->e;
}
list next(list l){
	return l->next;
}
list prev(list l){
	return l->previous;
}
list cons(list l, int e){
	list root = malloc(sizeof(item));
	root->e = e;
	root->next = l;
	root->previous = emptylist();
	l->previous = root;
	return root;
}

coda costruisci(coda c, int e){	//aggiungo e in fondo alla coda cioè al posto dell'ultimo tail di c
	list l = malloc(sizeof(item));
	l->e = e;
	l->next = emptylist();
	l->previous = emptylist();
	if (emptyque(c)){
		coda nuova = malloc(sizeof(tcoda));
		nuova->head = l;
		nuova->tail = l;
		return nuova;
	}
	l->previous = c->tail;		//il precedente dell'ultimo elemento  della coda dovrà essere l'attuale ultimo elemento in coda
	c->tail->next = l;	//il successivo della coda dovrà essere l attuale 
	c->tail = l; //l'ultimo elemento della coda dovrà essere l poi null, la mia nuova tail è l, altrimenti avrei che tail non punta più alla coda cioè all'ultimo elemento della lista
	return c;
}

void show_coda(coda c){
	while (!empty(c->head)){
		printf(" %d ", c->head->e);
		c->head = c->head->next;
	}

}
coda leggi(void){
	int e;
	coda c = emptycoda();
	do{
		printf("Inserire valori, terminare con 0: ");
		scanf("%d", &e);
		if (e == 0)
			break;
		c = costruisci(c, e);
	} while (true);
	return c;
}
int main(void){
	coda prova = leggi();
	show_coda(prova);
}