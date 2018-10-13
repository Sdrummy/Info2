#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
	char nome[20];
	int interessi;
}element;

typedef struct node{
	element e;
	struct node* next;
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
list cons(list l, element e){
	list root = malloc(sizeof(item));
	root->e = e;
	root->next = l;
	return root;
}
element head(list l){
	return l->e;
}
int conta(FILE *f){
	int count = 0,c;

	while (1){
		fscanf(f, "%*[^,\n]");
		c = fgetc(f);
		count++;

		if (c ==EOF || c=='\n')
			break;	
	}
	return count;
}
list leggi(void){
	element sup;
	list root = emptylist();
	FILE *f = fopen("utenti.txt", "rt");
	if (f == NULL)
		return root;
	while (!feof(f)){
		fscanf(f, "%[^:]", sup.nome);
		sup.interessi = conta(f);
		root = cons(root, sup);
	}
	fclose(f);
	return root;
}
void show(list l){
	while (!empty(l)){
		printf("Nome: %s  Numero di interessi: %d\n", head(l).nome, head(l).interessi);
		l = tail(l);
	}

}
int max_interessi(list l){
	element max = head(l);
	
	l = tail(l);
	while (!empty(l)){
		if (head(l).interessi > max.interessi)
			max = head(l);
		l = tail(l);
	}
	printf("\nL'utente con il maggior numero di interessi si chiama: %s con  %d interessi\n", max.nome, max.interessi);
	return max.interessi;
}
void visualizza_numero_int(list l, int ni){
	while (!empty(l)){
		if (head(l).interessi == ni)
			printf("Nome: %s\n", head(l).nome);
		l = tail(l);
	}
}
bool search_int(list l, int n_int){
	int p = 0;
	while (!empty(l)){
		if (head(l).interessi == n_int)
			p++;
		l = tail(l);
	}
	if (p >= 2)
		return true;
	return false;
}
int main(void){
	list l = leggi();
	show(l);
	int max = max_interessi(l);
	for (int i = 0; i <= max; i++){
		if (search_int(l, i)){
			printf("Persone con %d interessi:\n", i);
			visualizza_numero_int(l, i);
		}
		else
			printf("Non ci sono persone con lo stesso numero (%d) di interessi\n", i);
	}
}