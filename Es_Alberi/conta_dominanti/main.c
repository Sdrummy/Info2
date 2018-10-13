#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
	int val;
	struct node *left, *right;
}iteam;
typedef iteam* tree;

tree emptytree(void){
	return NULL;
}
bool empty(tree t){
	return t == NULL;
}
int root(tree t){
	if (empty(t))
		return 0;		//se il nodo è vuoto ritorno 0 invece di abort o altre cose perchè un nodo può avere 1 solo figlio 
	return t->val;
}
tree cons(int e, tree l, tree r){
	tree n = malloc(sizeof(iteam));
	n->val = e;
	n->right = r;
	n->left = l;
	return n;
}
tree left(tree t){
	return t->left;
}
tree right(tree t){
	return t->right;
}
void inorder(tree t){
	if (!empty(t)){
		inorder(left(t));
		printf("\t%d", root(t));
		inorder(right(t));
	}
}

tree insord(tree t, int e){
	tree r = t;
	if (empty(t))
		return cons(e, emptytree(), emptytree());
	while (!empty(t)){
		if (e <= root(t)){
				if (empty(left(t))){
					t->left = cons(e, emptytree(), emptytree());
					t = left(t);
				}
				t = left(t);	
		}
		else{
				if (empty(right(t))){
					t->right = cons(e, emptytree(), emptytree());
					t = right(t);
				}
			t = right(t);
		}
	}
	return r;
}
bool verifica_dominante(tree t){
	if (empty(t) || ( empty(left(t)) && empty(right(t))) )
		return false;
	if (root(t) > (root(left(t)) + root(right(t))))
		return true;
	return false;
}

void n_dom1(tree t, int *count){   //mia soluzione passando un parametro extra da usare come counter per i dominanti
	if (!empty(t)){
		if (verifica_dominante(t))
			(*count)++;
		n_dom1(left(t), count);
		n_dom1(right(t), count);
	}
}

int n_dom2(tree t){			//mia soluzione che non usa un parametro extra ma torna semplicemente un intero 
	
	if (empty(t))
		return 0;
	if (!empty(t) && verifica_dominante(t))
		return 1 + n_dom2(left(t)) + n_dom2(right(t));
	else
		return n_dom2(left(t)) + n_dom2(right(t));
	
}
void contaDominanti(tree t, int *num) {		//soluzione della puviani 
	if (!empty(t)) {
		int l = 0, r = 0;

		if (!empty(left(t)))
			l = root(left(t));

		if (!empty(right(t)))
			r = root(right(t));

		if (root(t) >= r + l && r + l>0) {
			(*num)++;
		}
		contaDominanti(left(t), num); contaDominanti(right(t), num);
	}
}
int main(void){
	tree t = emptytree(),l=emptytree();
	int e,count=0;
	FILE *f = fopen("sol.txt", "rt");
	while (fscanf(f, "%d", &e) > 0)
		t = insord(t, e);
	l = t;
	fclose(f);
	inorder(t);
//	count=n_dom(t);
	printf("\nCi sono %d dominanti usando la mia soluzione", count);
	count = 0;
	contaDominanti(t, &count);
	printf("\nCi sono %d dominanti usando la soluzione della Puviani", count);
}