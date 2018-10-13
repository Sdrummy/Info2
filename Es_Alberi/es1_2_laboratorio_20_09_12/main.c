#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
	char nome[10];
	unsigned int len;
}element;
typedef struct node{
	element value;
	struct node *left, *right;
}item;

typedef item* tree;

tree emptytree(void){
	return NULL;
}
bool empy(tree t){
	return t == NULL;
}
tree constree(element el, tree l, tree r){
	tree t = malloc(sizeof(item));
	strcpy(t->value.nome, el.nome);
	t->value.len = strlen(el.nome);
	t->left = l;
	t->right = r;
	return t;
}
element root(tree t){
	return t->value;
}
tree left(tree t){
	return t->left;
}
tree right(tree t){
	return t->right;
}

bool isEqual(element e1, element e2){
	return (strcmp(e1.nome, e2.nome) == 0);
}
bool isLess(element e1, element e2){
	return (strcmp(e1.nome, e2.nome) < 0);
}
void show_cresc(tree t){
	if (!empy(t)){
		show_cresc(left(t));
		printf("%s\tLunghezza: %d\n", root(t).nome,root(t).len);
		show_cresc(right(t));
	}
}
void cerca_max(tree t,element *e){		//FUNZIONE che ritorna la parola più lunga 
	if (!empy(t)){
		if (e->len < root(t).len)
			*e = root(t);
		cerca_max(left(t), e);
		cerca_max(right(t), e);
	}

}
void show_dec(tree t){		//visualizza il bst in ordine decrescente 
	if (!empy(t)){
		show_dec(right(t));
		printf("%s\tLunghezza: %d\n", root(t).nome, root(t).len);
		show_dec(left(t));
		
		
	}
}
tree insOrd(tree t, element e){
	tree supp = t;
	
	
	if (empy(t))
		return constree(e,emptytree(),emptytree());
	while (!empy(t)){
		if (isLess(e, root(t))){			// se si inseriscono delle parole in un bst (a sinistra di root vengono in prima in ordine alfabetico) con una in order si visualizzano in ordine crescente 
			if (empy(left(t))){
				t->left = constree(e, emptytree(), emptytree());
				t = left(t);
			}
			t = left(t);

		}
		else{
			if (empy(right(t))){
				t->right = constree(e, emptytree(), emptytree());
				t = right(t);
			}
			t = right(t);
		}
	}
	return supp;
}

tree leggi_file(void){
	element e;
	tree t = emptytree();
	FILE *f = fopen("parole.txt", "rt");
	while (!feof(f)){
		fscanf(f, "%s", e.nome);
		t = insOrd(t, e);
	}
	fclose(f);
	return t;
}

int main(void){
	unsigned int max = 0;
	tree t = leggi_file();
	show_cresc(t);
	putchar('\n');
	show_dec(t);
	element e= {"ERRORE",0};
	cerca_max(t, &e);
	printf("\nParola con il maggior numero di caratteri: %s\tCaratteri: %d", e.nome, e.len);
}