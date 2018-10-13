#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
	char nome[20];
	float prezzo;
}element;

typedef struct list_element{
	element articolo;
	struct list_element *next;
}node;

typedef node* list;

bool isless(element e1, element e2){
	if (strcmp(e1.nome, e2.nome) < 0)
		return true;
	return false;
}
bool isequal(element e1, element e2){
	return (strcmp(e1.nome, e2.nome) == 0);
}

list getelement(FILE *f, list l){
	element e1;
	fscanf(f, "%s", &e1.nome);
	fscanf(f, "%f", &e1.prezzo);
	l->articolo = e1;
	return l;
}
void stampaelement(element e){
	printf("Nome: %s\tPrezzo: %f", e.nome, e.prezzo);
}
list riempi(void){
	FILE *f = fopen("magazzino.txt", "rt");
	list root, l;
	root = (list)malloc(sizeof(node));
	root = getelement(f, root);
	l = (list)malloc(sizeof(node));
	root->next = l;

	while (!feof(f)){
		l = getelement(f, l);
		l->next = (list)malloc(sizeof(node));
		l = l->next;
	}
	l->next=NULL;
	fclose(f);
	return root;
}

void showlist(list l){
	printf("Elementi:\n");
	while (l->next !=NULL){
		stampaelement(l->articolo);
		putchar('\n');
		l = l->next;
	}
}


int main(void){
	int prezzo_soglia;
	list root = riempi();
	showlist(root);
	printf("Inserire un prezzo di soglia: ");
	scanf("%d", &prezzo_soglia);

	return 0;
}