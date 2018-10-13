#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
	char nome_sito[30];
	unsigned int numero_accessi;
}element;
typedef struct node{
	element val;
	struct node*left, *right;
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
	t->val = el;
	t->left = l;
	t->right = r;
	return t;
}
element root(tree t){
	return t->val;
}
tree left(tree t){
	return t->left;
}
tree right(tree t){
	return t->right;
}

bool isEqual(element e1, element e2){
	return (e1.numero_accessi==e2.numero_accessi);
}
bool isLess(element e1, element e2){
	return (e1.numero_accessi<e2.numero_accessi);
}
void inOrder(tree t){
	if (!empy(t)){
		inOrder(left(t));
		printf("%s\tNumero di accessi: %d\n", root(t).nome_sito, root(t).numero_accessi);
		inOrder(right(t));
	}
}
void preOrder(tree t){
	if (!empy(t)){
		printf("%s\tNumero di accessi: %d\n", root(t).nome_sito, root(t).numero_accessi);
		preOrder(left(t));
		preOrder(right(t));
	}

}
void show_dec(tree t){
	if (!empy(t)){
		show_dec(right(t));
		printf("%s\tNumero di accessi: %d\n", root(t).nome_sito, root(t).numero_accessi);
		show_dec(left(t));
		
	}
}
void string_matching(tree t,char *str,unsigned int len){
	if (!empy(t)){
		string_matching(right(t),str,len);
		if (strncmp(root(t).nome_sito, str, len) == 0)
			printf("%s\tNumero di accessi: %d\n", root(t).nome_sito, root(t).numero_accessi);
		
		
		string_matching(left(t),str,len);

	}
}
tree insord(tree t, element e){
	tree l = t;
	if (empy(t))
		return constree(e, emptytree(), emptytree());

	while (!empy(t)){
		if (isLess(e, root(t))){		
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
	return l;
}

tree leggi_file(void){
	element e;
	tree r = emptytree();
	FILE *f = fopen("siti.txt", "rt");
	if (f == NULL)
		return emptytree();
	while (!feof(f)){
		fscanf(f, "%s", e.nome_sito);
		fscanf(f, "%d", &e.numero_accessi);
		r = insord(r, e);
	}
	fclose(f);
	return r;
}
int main(void){
	char ins_nome[30];
	tree prova = leggi_file();
	show_dec(prova);//visualizzo i siti in ordine decrescente di popolarità
	printf("\nInserire una stringa di ricerca: ");
	scanf("%s",ins_nome);
	unsigned int len = strlen(ins_nome);
	string_matching(prova, ins_nome, len);
}