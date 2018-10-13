#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_element{
	unsigned char numero_interessi;
	char nome[20];
	char cognome[20];
	struct list_element *next;
}node;

struct persona{
	unsigned char numero_int;
	char nome[20];
	char cognome[20];
};

typedef node* list;

list leggi(void){
	list root=NULL, l;
	char interessi[20];
	char c=0;
	FILE *f = fopen("utenti.txt", "rt");
	if (f == NULL)
		return root;
	root = (list)malloc(sizeof(node));
	root->numero_interessi = 0;
	fscanf(f, "%s", &root->nome);
	fscanf(f, "%[^:]", &root->cognome);
	fscanf(f, "%c", &c);
	while (c != '\n' && !feof(f)){
		fscanf(f, "%[^,\n]", &interessi);
		root->numero_interessi++;
		fscanf(f, "%c", &c);
		if (c == '\n')
			break;

	}
	l = (list)malloc(sizeof(node));
	root->next = l;

	while (!feof(f)){
	fscanf(f,"%s", &l->nome);
	fscanf(f," %[^:]", &l->cognome);
	l->numero_interessi = 0;
	
	fscanf(f, "%c", &c);
	while (c != '\n' && !feof(f)){
	fscanf(f, "%[^,\n]", &interessi);
	l->numero_interessi++;
	
	fscanf(f, "%c", &c);
	if (c == '\n')
		break;
	
	}
	l->next = (list)malloc(sizeof(node));
	l = l->next;
	}
	l->next = NULL;
	fclose(f);
	return root;
}

unsigned char n_interessi_max(list l){
	struct persona *max=malloc(sizeof(struct persona));
	max->numero_int = 0;
	if (l->next == NULL){
		printf("L'unica persona nella lista si chiama: %s %s con %d interessi", l->nome, l->cognome, l->numero_interessi);
		return l->numero_interessi;
	}
		
	while (l->next != NULL){
		if (l->numero_interessi > max->numero_int){
			max->numero_int = l->numero_interessi;
			strcpy(max->nome, l->nome);
			strcpy(max->cognome, l->cognome);

		}
		l = l->next;
	}
	printf("La persona con il maggior numero di interessi si chiama: %s %s con %d interessi", max->nome, max->cognome, max->numero_int);
	return max->numero_int;
	
}
void stampa_n(list l, unsigned int n_int){
	while (l->next != NULL){
		if (l->numero_interessi == n_int)
			printf("Nome e Cognome: %s %s\n", l->nome, l->cognome);
		l = l->next;
	}
}
int main(void){
	list l=leggi();
	unsigned char interessimax=n_interessi_max(l);
	for (int i = 0; i <= interessimax; i++){
		printf("\nPersone con %d interessi:\n", i);
		stampa_n(l, i);
	}
	return 0;
}