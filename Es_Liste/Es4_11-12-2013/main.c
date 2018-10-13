#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
	char nome[30];
	unsigned int prezzo;
}element;

typedef struct list_element{
	element e;
	struct list_element *next;

}iteam;

typedef iteam* list;


list emptylist(void){
	return NULL;
}
bool empty(list l){
	return(l == NULL);
}
list tail(list l){
	return l->next;
}
element head(list l){
	return l->e;
}
list cons(list l, element e){
	list root = malloc(sizeof(iteam));
	root->e = e;
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
	printf("Il maggazzino contiene:\n");
	while (!empty(l)){
		printf("%s\tPrezzo: %d\n", head(l).nome, head(l).prezzo);
		l = tail(l);
	}
}
list leggi(void){
	list root = emptylist();
	element e;
	FILE *f = fopen("magazzino.txt", "rt");
	
	while (!feof(f)){
		fscanf(f,"%s", &e.nome);
		fscanf(f, "%d", &e.prezzo);
		
		root = cons(root, e);
	}
	fclose(f);
	return root;
}
list insOrd(list l, element e){
	list t=emptylist();
	if (empty(l))
		return cons(l, e);
	if (empty(l) || !isLess(head(l), e)){
		t = cons(l, e);
		return t;
	}
	return cons(insOrd(l, e), head(l));
	
}
void ordine(list l, unsigned int soglia){
	list root = emptylist();
	while (!empty(l)){
		if (head(l).prezzo > soglia)
			root = insOrd(root, head(l));
		l = tail(l);
	}
	show(root);
}
void prezzo(element *lista, int count, int costo_parziale, int *v, int pos, int n){	//una volta risolto il problema della rappresentazione della lista diventa un banale problema di backtracking
	int i;
	if (count == 2 && costo_parziale==50){
		for (i = 0; i < n; i++){
			if (v[i] == 1)
				printf("Articolo: %s\tPrezzo: %d",lista[i].nome,lista[i].prezzo);
			
		}
		return;
	}
	if (pos == n)
		return;

	count++;
	costo_parziale +=lista[pos].prezzo;
	v[pos] = 1;
	prezzo(lista, count, costo_parziale, v, pos + 1, n);
	count--;
	costo_parziale -= lista[pos].prezzo;
	v[pos] = 0;
	prezzo(lista, count, costo_parziale, v, pos + 1, n);
}
int main(void){
	int i;
	unsigned int soglia;
	list root = leggi();
	show(root);
	printf("\nInserire soglia di visualizzazione:\n");
	scanf("%d", &soglia);
	ordine(root, soglia);

	int v[4] = { 0, 0, 0, 0 };
	element *l = malloc(4 * sizeof(element)); // si poteva fare una funzione per calcolare la lunghezza della lista che so essere 4
	i = 0;
	while (!empty(root)){
		l[i] = head(root);
		i++;
		root = tail(root);
	}
	prezzo(l, 0, 0, v, 0, 4);
	return 0;
}