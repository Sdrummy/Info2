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
list insOrd(list l, int e){
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
list append(list l1, list l2){
	if (empty(l1))
		return l2;
	return cons(append(tail(l1), l2), head(l1));
}
void show(list l){
	printf("[");
	while (!empty(l)){
		printf(" %d ", head(l));
		l = tail(l);
	}
	printf("]\n");
}
list seek_and_destroy(list l, int k, int h){		//elimino i primi h elementi con somma uguale a k
	list root = l,t=emptylist(),c=emptylist(),sup=l;
	int n = k;
	while (!empty(l)){
		sup = l;
		t = l;
		for (int i = 0; i < h && !empty(l); i++){
			k -= head(l);
			c = l;
			l = tail(l);
		}
		if (empty(l))
			return root;
		if (k == 0)
			break;
		else{
			l = sup;
			l = tail(l);
			k = n;
		}
	}
	list i = emptylist();
	while (root != t){
		i = insOrd(i, head(root));
		root = tail(root);
	}
	return append(i, c->next);
}
list leggi(void){
	list l = emptylist();
	int e;
	do{
		printf("Inserire: ");
		scanf("%d", &e);
		if (e == 0)
			break;
		l = cons(l, e);
	} while (true);
	return l;
}

int main(void){
	list p = leggi();
	show(p);
	list nuova_p = seek_and_destroy(p, 5, 3);
	show(nuova_p);
}