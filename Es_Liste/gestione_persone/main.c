#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
	char nome[30];
	char cognome[30];
}element;

typedef struct list_element{
	element value;
	struct list_element *next;
}iteam;

typedef iteam* list;



bool isEqual(element e1, element e2){
	if (strcmp(e1.nome, e2.nome) == 0 && strcmp(e1.cognome, e2.cognome) == 0)
		return true;
	return false;
}
bool isLess(element e1, element e2){
	if (strcmp(e1.cognome, e2.cognome) < 0 || (strcmp(e1.cognome, e2.cognome) == 0 && strcmp(e1.nome, e2.nome) < 0))
		return true;

	return false;
}

element copy(element e){
	element e1;
	e1 = e;
	return e1;
}

element getElement(void){
	element e;
	printf("Cognome: ");
	scanf("%s", &e.cognome);
	printf("Nome: ");
	scanf("%s", &e.nome);
	return e;
}

void printelement(element e){
	printf("Cognome: %s Nome: %s\n", e.cognome, e.nome);
}

list emptylist(void){
	return NULL;
}

bool empty(list l){
	return (l == NULL);
}

element head(list l){
	if (empty(l))
		abort();
	return l->value;
}

list tail(list l){
	if (empty(l))
		abort();
	return l->next;
}

list cons(element e, list l){
	list t = malloc(sizeof(iteam));
	t->value = copy(e);
	t->next = l;
	return t;

}

void showlist(list l){
	printf("Elenco persone:\n");
	while (!empty(l)){
		printelement(head(l));
		l = tail(l);
	}
	putchar('\n');
}

list insord(element e, list l){

	list t;
	if (empty(l) || !isLess(head(l), e)){

	t = cons(e, l);
	return t;
	}		
	return cons(head(l), insord(e, tail(l)));

}

int contaOmonimi(list l){
	int count = 0;
	while (!empty(tail(l))){
		if (isEqual(head(l), head(tail(l))))
			count++;
		l = tail(l);
	}
	return count;
}
list leggi(void){
	list l = emptylist();
	element e;
	FILE *f = fopen("persone.txt", "rt");
	while (!feof(f)){
		fscanf(f, "%s %s", e.nome, e.cognome);
		l = insord(e, l);
	}
	fclose(f);
	return l;
}
/*void omonimi(list l){
	//int n = 1;
	int n;
	element e;
	while (!empty(l)){
		n = 1;
		e = head(l);
		while (!empty(tail(l)) && isEqual(e, head(tail(l)))){
			n++;
			l = tail(l);
		}
		if (n != 1)
			printf("Ci sono %d %s %s\n", n, e.nome, e.cognome);
		//n = 1;
		l = tail(l);
	}
}*/
/*void omonimi(list l){
	int n = 0;
	element e;
	while (!empty(l)){
		e = head(l);
		if (!empty(tail(l)) && isEqual(e, head(tail(l)))){
			n++;
			l = tail(l);
			while (!empty(l) && isEqual(e, head(l)))
				l = tail(l);
		}
		else
			l = tail(l);
	}
	printf("Ci sono %d omonimi\n", n);
}*/

int main(void){
	list root = leggi();
	showlist(root);

	omonimi(root);
	return 0;
}