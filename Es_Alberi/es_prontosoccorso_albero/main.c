#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
	char nome[20];
	char c_f[17];
	char referto[100];
	char codiceAccesso;
} persona;

typedef struct node{
	persona e;
	struct node*left, *right;
}item;
typedef item* tree;

tree emptytree(void){
	return NULL;
}
bool empty(tree t){
	return t == NULL;
}
persona root(tree t){
	return t->e;
}
tree left(tree t){
	return t->left;
}
tree right(tree t){
	return t->right;
}
tree cons(tree l, tree r, persona e){
	tree t = malloc(sizeof (item));
	t->left = l;
	t->right = r;
	t->e = e;
	return t;
}
bool isLess(persona p1, persona p2){
	return p1.codiceAccesso < p2.codiceAccesso;
}
tree insOrd(tree t, persona el){
	tree l = cons(emptytree(), emptytree(), el),rt=t;
	if (empty(t))
		return l;
	while (!empty(t)){
		if (!isLess(root(t), el)){
			if (empty(left(t))){
				t->left = l;
				t = left(t);
			}
			t = left(t);
		
			}
		else{
			if (empty(right(t))){
				t->right = l;
				t = right(t);
			}
			t = right(t);
		}
	}
	return rt;
}
persona aggiungi_ricoverato(void){
	persona sup;
	fflush(stdin);
	printf("Inserire Nome e Cognome (zero-terminare): ");
	scanf("%[^0]", sup.nome);
	fflush(stdin);
	printf("Inserire codice fiscale CF del paziente: ");
	scanf("%s", sup.c_f);
	fflush(stdin);
	printf("Inserire referto (terminare inserimento con -1): ");
	scanf("%[^-1]", sup.referto);
	fflush(stdin);
	printf("Inserire codice identificativo (0,1,2,3,4): ");
	scanf("%c", &sup.codiceAccesso);
	//fflush(stdin);
	/*printf("Orario di entrata (xx:xx): ");
	scanf("%s", sup.ora_ingresso);
	fflush(stdin);*/
	/*v[*pos] = sup;
	(*pos)++;*/
	return sup;
}
void show_maxPrio(tree t){
	while (!empty(right(t))){
		t = right(t);
	}
	printf("\nProssimo paziente da visitare:\n");
	printf("Nome: %s\nReferto: %s\n", root(t).nome, root(t).referto);
	printf("Codice di accesso: %c\n", root(t).codiceAccesso);
}
int main(void){
	persona p;
	tree l = emptytree();
	int c;
	do{
		printf("Benvenuto al pronto soccorso, scegliere operazione da eseguire:\n.1 Ricovera paziente\n.2 Visualizza il prossimo paziente\n");
		scanf("%d", &c);
		switch (c){
		case 1:
			p = aggiungi_ricoverato();
			l = insOrd(l, p);
			break;
		case 2:
			show_maxPrio(l);
			break;
		default:
			
			break;
		}
	} while (c != 0);
	return 0;
}