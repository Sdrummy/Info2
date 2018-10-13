#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
	char nome[20];
	float prezzo;
}element;
typedef struct node{
	element e;
	struct node*next;
}item;
typedef item* list;


bool empty(list l){
	return l == NULL;
}
bool isLess(element e1, element e2){
	return (strcmp(e1.nome, e2.nome) <0);
}
bool isEqual(element e1, element e2){
	return ((strcmp(e1.nome, e2.nome) == 0) && (e1.prezzo == e2.prezzo)) ? true : false;
}
list emptylist(void){
	return NULL;
}
element head(list l){
	return l->e;
}
list tail(list l){
	return l->next;
}
list cons(list l, element e){
	list root = malloc(sizeof(item));
	root->e = e;
	root->next = l;
	return root;
}
list insOrd(list l,element e){
	if (empty(l) || isLess(e, head(l)))
		return cons(l, e);
	return cons(insOrd(tail(l), e), head(l));
}
void show(list l){
	while (!empty(l)){
		printf("Nome: %s  Prezzo: %f\n", head(l).nome, head(l).prezzo);
		l = tail(l);
	}
}
list leggi(void){
	list root = emptylist();
	element e;
	FILE *f = fopen("magazzino1.txt", "rt");
	if (f == NULL)
		return root;
	while (!feof(f)){
		fscanf(f, "%s%f", e.nome, &e.prezzo);
		root = insOrd(root, e);
	}
	fclose(f);
	return root;
}
void visualizza_soglia(list l, float soglia){
	while (!empty(l)){
		if (head(l).prezzo>soglia)
			printf("Nome: %s  Prezzo: %f\n", head(l).nome, head(l).prezzo);
		l = tail(l);
	}
}
list delete(list l, element e){
	if (empty(l))
		return emptylist();
	if (isEqual(head(l), e))
		return tail(l);
	else
		return cons(delete(tail(l), e), head(l));
}
void visualizza_50(list l){
	element e1;
	list sup = l;
	while (!empty(l)){
		e1= head(l);
		sup = tail(l);
		while (!empty(sup)){
			if (head(sup).prezzo + e1.prezzo == 50){
				printf("Coppie di elementi che costano 50:\n%s costo: %f e %s costo: %f\n", e1.nome,e1.prezzo , head(sup).nome, head(sup).prezzo);
				l = delete(l, head(sup));
			}
			sup = tail(sup);
		}
		l = tail(l);
	}
}
int main(void){
	float sgl;
	list l = leggi();
	show(l);
/*	printf("Inserire soglia di visualizzazione: ");
	scanf("%f", &sgl);
	printf("Articoli che costano più di %f:\n", sgl);
	visualizza_soglia(l, sgl);*/
	visualizza_50(l);
}