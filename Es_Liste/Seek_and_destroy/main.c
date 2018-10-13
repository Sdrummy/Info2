#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
	int e;
	struct node *next;
}item;
typedef item* list;

bool empty(list l){
	return l == NULL;
}
list emptylist(void){
	return NULL;
}
int head(list l){
	return l->e;
}
list tail(list l){
	return l->next;
}
list cons(list l, int e){
	list root = malloc(sizeof(item));
	root->e = e;
	root->next = l;
	return root;
}
void show(list l){
	printf("[");
	while (!empty(l)){
		printf(" %d ", head(l));
		l = tail(l);
	}
	printf("]\n");
}

list append(list l1, list l2){
	if (empty(l1))
		return l2;
	return cons(append(tail(l1), l2), head(l1));
}
list insord(list l, int e){
	list t = cons(emptylist(), e),l1=emptylist(),root=l;
	if (empty(l))
		return t;
	while (!empty(l)){
		l1 = l;
		l = tail(l);
	}
	l1->next = t;
	return root;
}
list seekAndDestroy(list l, int k){
	list root = l, t = l,c=emptylist(),supp=l;
	int n = k;

	if (head(l) == k)
		return tail(l);

	while (!empty(l)){
		supp = l;
		
		while (k>0 && !empty(l)){
			c = l;
			k -= head(l);
			l = tail(l);
		}
		if (k == 0){
		/*	if (l == tail(root))
				return l;*/
			t->next = c->next;		//GUARDA BENE: scrivere t=c->next o t=c NON FUNZIONA questo perchè nel nodo procedente a t l'indirizzo next sarà ancora l'indirizzo in memoria di t, quindi per 
			return root;		//attaccare 2 liste è necessario conoscere il nodo precedente a quello da eliminare in modo da poter modificare l'indirizzo next che non punti più al nodo che si vuole eliminare 
		}						//ma al primo nodo valido, nel mio caso c->next essendo c l'ultimo nodo della sotto-lista da eliminare	
			//break;
		else{
			if (empty(l))
				return root;
			if (k < 0){
				k = n;
				l = supp;
			}	
		}	
			t = l;
			l = tail(l);
	}
	return root;
/*	list i = emptylist();
	
	while (root!=t){
		i = insord(i, head(root));
		root = tail(root);
	}
	return append(i, c->next);*/
}
int main(void){
	list prova = emptylist();
	int e;
	do{
		printf("Inserire valori: ");
		scanf("%d", &e);
		if (e == 0)
			break;
		prova = cons(prova, e);
	} while (true);

	show(prova);
	list l = seekAndDestroy(prova, 5);
	show(l);
}