#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct list_element{
	int value;
	struct list_element *next;

}iteam;

typedef iteam* list;

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
		root = cons(root, check);
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

bool cerca(list l, int e){
	while (!empty(l)){
		if (l->value == e)
			return true;
		l = tail(l);
	}
	return false;
}


list leggi_da_file(void){
	int sup;
	list root = emptylist();
	FILE *f = fopen("esiti.txt", "rt");
	while (!feof(f)){
		fscanf(f, "%d", &sup);
		root = cons(root, sup);

	}
	fclose(f);
	return root;
}
list rimuovi_doppie(list l){
	
	list root = emptylist();
	root = cons(root, head(l));
	l = tail(l);
	while (!empty(l)){
		if (!cerca(root,head(l)))
			root = cons(root, head(l));
		l = tail(l);
	}
	return root;
}

void visualizza_soglia(list l, int soglia){
	list root_inf = emptylist();
	list root_sup = emptylist();
	while (!empty(l)){
		if (head(l) >= soglia)
			root_sup = cons(root_sup, head(l));
		else
			root_inf = cons(root_inf, head(l));
		l = tail(l);
	}
	printf("I voti inferiori alla soglia inserita sono:\t");
	show(root_inf);
	printf("\nI voti superiori alla soglia inserita sono:\t");
	show(root_sup);
}
int main(void){
	
	int soglia;
	list root = leggi_da_file();
	show(root);
	printf("\nInserire una soglia per la visualizzazione dei voti");
	scanf("%d", &soglia);
	visualizza_soglia(root, soglia);
	return 0;
}