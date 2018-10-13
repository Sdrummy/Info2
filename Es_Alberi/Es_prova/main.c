#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tree_element{
	int value;
	struct tree_element *right, *left;
}node;

typedef node* tree;

bool empty(tree t){
	return t == NULL;
}

tree emptytree(void){
	return NULL;
}

int root(tree t){
	return t->value;
}

tree left(tree t){
	if (empty(t))
		return NULL;
	return t->left;
}
tree right(tree t){
	if (empty(t))
		return NULL;
	return t->right;
}
tree cons(int el,tree l,tree r){
	tree root = malloc(sizeof(node));
	root->value = el;
	root->left = l;
	root->right = r;
	return root;
}
void preOrder(tree t){
	if(!empty(t)){
		printf("\t%d", root(t));
		preOrder(left(t));
		preOrder(right(t));
	}
}
void postOrder(tree t){
	if(!empty(t)){
		postOrder(left(t));
		postOrder(right(t));
		printf("\t%d", root(t));
	}
}
void inOrder(tree t){
	if (!empty(t)){
		inOrder(left(t));
		printf("\t%d", root(t));
		inOrder(right(t));
	}
}

tree creatree(void){
	int e;
	printf("Inserire valore, terminare con zero: ");
	scanf("%d", &e);
	if (e == 0)
		return emptytree();
	else
	{
		tree l = creatree();
		tree r = creatree();
		return cons(e, l, r);
	}
}
int main(void){
	tree root = creatree();
	postOrder(root);
	putchar('\n');
	preOrder(root);

	putchar('\n');
	inOrder(root);
}