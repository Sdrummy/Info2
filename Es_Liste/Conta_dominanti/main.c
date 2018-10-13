#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
	int val;
	struct nodo *next;
}iteam;

typedef iteam* list;

list crea(void){
	int count = 0;
	list root, l;
	root = (list)malloc(sizeof(iteam));
	root->next = NULL;

	printf("Quanti elementi si vogliono inserire?: ");
	scanf("%d", &count);
	if (count == 0)
		return root;


	printf("Inserire il primo valore: ");
	scanf("%d", &root->val);
	l = (list)malloc(sizeof(iteam));
	root->next = l;


	for (int i = 1; i < count; i++){
		l->next = (list)malloc(sizeof(iteam));
		printf("Inserire il %d-esimo valore: ", i + 1);
		scanf("%d", &l->val);
		l = l->next;

	}
	l->next = NULL;
	return root;
}

int conta_dom(list l){
	int i,count,sup;
	for (i = 0,count=0; l->next != NULL; i++){
		sup = l->val;
		l = l->next;
		if (sup > l->val && l->next!=NULL)
			count++;
	}
	return count;
}
void visualizza(list l){

	printf("[");
	while (l->next != NULL){
		printf(" %d ", l->val);
		l = l->next;
	}
	printf("]");
}
int main(void){
	list root = crea();
	visualizza(root);
	int num_dom = conta_dom(root);
	return 0;
}
