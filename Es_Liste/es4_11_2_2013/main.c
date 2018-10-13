#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h.>

typedef struct{
	char nome[20];
	float prezzo;
}element;
typedef struct node{
	element value;
	struct node *next;
}iteam;

typedef iteam* list;

bool empty(list t){
	return t == NULL;
}
list emptylist(void){
	return NULL;
}
element head(list l){
	return l->value;
}
list next(list t){
	return t->next;
}
list cons(list l, element e){
	list root = malloc(sizeof(iteam));
	root->value = e;
	root->next = l;
	return root;
}
bool isEqual(element e1, element e2){
	return (strcmp(e1.nome, e2.nome) == 0);
}
bool isLess(element e1, element e2){
	return (strcmp(e1.nome, e2.nome) < 0);
}
void show(list l){
	printf("Articoli:\n");
	while (!empty(l)){
		printf("Nome: %s\tPrezzo: %f\n", head(l).nome, head(l).prezzo);
		l = next(l);
	}
}
list leggi_file(void){
	element e;
	list root = emptylist();
	FILE *f = fopen("magazzino.txt", "rt");
	if (f == NULL)
		return root;
	while (!feof(f)){
		fscanf(f, "%s", e.nome);
		fscanf(f, "%f", &e.prezzo);
		root = cons(root, e);
	}
	fclose(f);
	return root;
}
list insOrd(list l, element e){
	list root=emptylist();
	if (empty(l) || isLess(e, head(l))){
		root = cons(l, e);
		return root;
	}

	return cons(insOrd(next(l), e), head(l));
}
list show_soglia(list l, float soglia){
	list root = emptylist();
	while (!empty(l)){
		if (head(l).prezzo > soglia)
			root = insOrd(root, head(l));
		l = next(l);
	}
	return root;
}

void visualizza_50(list l, int count,element *sol,float sommaparziale){

	if (count == 2 || empty(l)){
		if (sommaparziale==50)
			printf("Articoli da 50 euro: %s costo %f e %s costo %f\n", sol[0].nome, sol[0].prezzo, sol[1].nome, sol[1].prezzo);
		return;
	}

		count++;
		sommaparziale += head(l).prezzo;
		sol[count-1] = head(l);
		visualizza_50(next(l), count, sol, sommaparziale);
		count--;
		sommaparziale -= head(l).prezzo;
		visualizza_50(next(l), count, sol, sommaparziale);
}
int main(void){
	float soglia;
	element a[2];
	list root = leggi_file();
	show(root);
	printf("Inserire una soglia di visualizzazione: ");
	scanf("%f", &soglia);
	list sl = show_soglia(root, soglia);
	show(sl);
	visualizza_50(root,0,a,0);
}