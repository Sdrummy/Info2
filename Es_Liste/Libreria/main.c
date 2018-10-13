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
void show(list l){
	printf("[ ");
	while (!empty(l)){
		printf(" %d ", l->value);
		l = tail(l);
	}
	printf(" ]");
}

list ins_ord(int el, list l){
	list t,root=l,sup=emptylist();
	t = cons(l, el);
	if (empty(l))
		return t;

	while (!empty(l)){
		sup = l;
		l = tail(l);

	}
	sup->next = t;
	t->next = emptylist();
	return root;
}
int main(void){
	list r = emptylist();
	int el;
	do{
		printf("Inserire un valore,terminare con zero: ");
		scanf("%d", &el);
		if (el == 0)
			break;
		else
			r = ins_ord(el, r);

	} while (el != 0);
	show(r);
}