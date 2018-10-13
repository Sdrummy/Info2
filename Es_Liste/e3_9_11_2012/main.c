#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



typedef struct nodeI{
	char interesse[20];
	struct nodeI* next;
}itemI;
typedef itemI* list_interest;

typedef struct {
	char nome[20];
	list_interest inter;
}element;

typedef struct node{
	 element e;
	struct node *next;
}item;
typedef item* list;



/*
*
*
*
*		primitive per list interessi
*
*
*/

bool emptyI(list_interest l){
	return l == NULL;
}
list_interest emptylistI(void){
	return NULL;
}
list_interest tailI(list_interest l){
	return l->next;
}
char *headI(list_interest l){
	return l->interesse;
}
list_interest consI(list_interest l, char *e){
	list_interest root = malloc(sizeof(itemI));
	strcpy(root->interesse, e);
	root->next = l;
	return root;
}
/*
*
*
*			primitive per list 	
*
*
*
*/

bool empty(list l){
	return l == NULL;
}
list emptylist(void){
	return NULL;
}
list tail(list l){
	return l->next;
}
element head(list l){
	return l->e;
}
list cons(list l, element e){
	list root = malloc(sizeof(item));
	root->e = e;
	root->next = l;
	return root;
}

list_interest leggiInteressi(FILE *f){
	char sup[20];
	list_interest root = emptylistI();
	while (fscanf(f, "%[^,\n]", sup) > 0){
		root = consI(root, sup);
		fscanf(f, "%*[ ,]");
	}
	fgetc(f);
	return root;
}
list leggi(void){
	element e;
	list root = emptylist();
	FILE *f = fopen("utente.txt", "rt");
	if (f == NULL)
		return root;
	while (!feof(f)){
		if (fscanf(f, "%[^:]", e.nome) <= 0)
			break;
		fscanf(f, "%*2c");
		e.inter = leggiInteressi(f);
		root = cons(root, e);
	}
	fclose(f);
	return root;
}

void show_interessi(list_interest li){
	while (!emptyI(li)){
		printf(" %s ", headI(li));
		li = tailI(li);
	}
	
}
void show(list l){
	while (!empty(l)){
		printf("Nome: %s\n", head(l).nome);
		printf("Ineressi:");
		show_interessi(head(l).inter);
		printf("\n\n");
		l = tail(l);
	}
}
int count_int(list_interest li){
	int count = 0;
	while (!emptyI(li)){
		count++;
		li = tailI(li);
	}
	return count;
}
void interessi_max(list l){
	int max = 0,sup;
	char nome_maxint[20];
	while (!empty(l)){
		sup = count_int(head(l).inter);
		if (sup > max){
			max = sup;
			strcpy(nome_maxint, head(l).nome);
		}
		l = tail(l);
	}
	if (max == 0)
		fprintf(stderr, "NON SONO PRESENTI UTENTI NELLA LISTA\n");
	else
		printf("L'utente con il maggior numero di interessi si chiama %s e ne ha ben %d", nome_maxint, max);
}

bool isEqual(char *stringa1, char *stringa2){
	return (strcmp(stringa1, stringa2) == 0);
}
bool almeno2(list_interest l1, list_interest l2){
	list_interest sup = emptylistI();
	int count = 0;
	while (!emptyI(l1)){
		sup = l2;
		while (!emptyI(l2)){
			if (isEqual(headI(l1), headI(l2)))
				count++;
			l2 = tailI(l2);
		}
		l2 = sup;
		l1 = tailI(l1);
	}
	if (count >= 2)
		return true;
	return false;
}
void search(element e, list rest){
	while (!empty(rest)){
		if (almeno2(e.inter, head(rest).inter) && !isEqual(e.nome,head(rest).nome))
			printf("%s %s\n", e.nome, head(rest).nome);
		rest = tail(rest);
	}

}

list delete(list l1, element e){		
	if (empty(l1))
		return emptylist();
	else{
		if (isEqual(head(l1).nome, e.nome))
			return tail(l1);
		else
			return cons(delete(tail(l1),e),head(l1));
	}
}
void interessi_2comuni(list l){
	list root = l;
	while (!empty(l)){
		search(head(l), root);
		root = delete(root, head(l)); //dopo aver cercato se l'elemento testa di l ha almeno 2 interessi in comune con tutti gli elementi della coda di l1 CANCELLO da root l'elemento testa di l poichè 
		l = tail(l);					//l'ho già controllato su qualsiasi altro elemento di root, lasciarlo vorrebbe dire avere situazioni tipo: luca-paolo paolo-luca 
	}
	
}
int main(void){
	
	list root = leggi();
	show(root);
	interessi_max(root);
	printf("\nUtenti con almeno due interessi in comune:\n");
	interessi_2comuni(root);
}