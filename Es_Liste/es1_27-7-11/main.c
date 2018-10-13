#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
	int numero_concatenamenti;
	int value;
	char str[50];
}element;
typedef struct list_element{
	element e;
	struct list_element *next;
}item;

typedef item* list;

list emptylist(void){
	return NULL;
}

bool empty(list l){
	return l == NULL;
}

element head(list l){
	return l->e;
}

list tail(list l){
	return l->next;
}

list cons(list l, element e){
	list t = malloc(sizeof(item));
	t->e = e;
	t->next = l;
	return t;
}
bool isEqual(element a, element b){
	if (strcmp(a.str, b.str)==0 && a.value == b.value)
		return true;
	return false;
}
void show(list l){
	printf("Cose strane:\n");
	while (!empty(l)){
		if (head(l).value == -1){
				l = tail(l);
				continue;
		}
			
		printf("Nome:\t%s\t", head(l).str);
		printf("Numero: %d", head(l).value);
		putchar('\n');
		l = tail(l);
	}

}

list leggi( int check){
	element e;
	list root = emptylist();
	FILE *f;
	switch (check){
	case 1:
		f = fopen("lista1.txt", "rt");
		break;
	case 2:
		f = fopen("lista2.txt", "rt");
		break;
	default:
		return NULL;
		
	}
	while (!feof(f)){
		fscanf(f,"%d", &e.value);
		fscanf(f, "%s", &e.str);
		root = cons(root, e);
	}
	fclose(f);
	return root;
}
bool ctrl(int value, list l){
	while (!empty(l)){
		if (head(l).value == value)
			return true;
		l = tail(l);
	}
	return false;
}
void cat(element *a, list b){
	a->numero_concatenamenti = 0;
	while (!empty(b)){
		if (a->value == head(b).value){
			strcat(a->str, head(b).str);
			a->numero_concatenamenti++;
		}
			
		b = tail(b);
	}
}
list join(list A, list B){
	list root = A;
	while (!empty(A)){
		if (ctrl(head(A).value, B))
			cat(&A->e, B);


		else
			A->e.value = -1;
		A = tail(A);
	}
	return root;
}
void visualizza_max(list l){
	element tmp;
	tmp = head(l);
	l = tail(l);
	while (!empty(l)){
		if (head(l).numero_concatenamenti > tmp.numero_concatenamenti)
			tmp = head(l);
		l = tail(l);
	}
	printf("\nL'elemento ottenuto con il maggior numero di concatenamenti ne ha %d:\t%s\tNumero: %d", tmp.numero_concatenamenti, tmp.str, tmp.value);
}
int main(void){
	list root = leggi(1);
	show(root);
	list root2 = leggi(2);
	show(root2);
	list final = join(root, root2);
	show(final);
	visualizza_max(final);
}