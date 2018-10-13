#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node{
	int value;
	struct node *left, *right;
}iteam;

typedef iteam* tree;

tree cons(int e, tree l, tree r){
	tree root = malloc(sizeof(iteam));
	root->value = e;
	root->left = l;
	root->right = r;
	return root;
}
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
	return t->left;
}
tree right(tree t){
	return t->right;
}

void preorder(tree t){
	if(!empty(t)){
		printf(" %d", root(t));	//show root
		preorder(left(t));
		preorder(right(t));
	}
}
void postorder(tree t){
	if (!empty(t)){
		postorder(left(t));
		postorder(right(t));
		printf(" %d", root(t));		//show root
	}
}
void inorder(tree t){
	if (!empty(t)){
		inorder(left(t));
		printf(" %d", root(t));	//show root
		inorder(right(t));
	}
}

tree insOrd(int el, tree t){
	tree l = t;
	
	if (empty(t))		//se t è un albero vuoto si ritorna la cons 
		return cons(el, emptytree(), emptytree()) ;

	while (!empty(t)){	//scorro t fino a che non è vuoto,nota: voglio aggiungere e come foglia
		if (el <= root(t)){//se l'elemento è minore (o uguale) alla radice mi sposto nel sottoalbero di sinistra
			if (empty(left(t))){
				t->left = cons(el, emptytree(), emptytree());	//come detto voglio aggiungere l'elemento come una foglia quindi scorro il sottoalbero di sinistra filo ad arrivare a null
				t = left(t);	//faccio left di t in modo da avere insieme al successivo left il valore albero vuoto ed uscire dal ciclo while
			}
			t = left(t);	

			}
		else{	//stessa cosa se e risulta maggiore della radice: vado ad inserirlo nel sottoalbero destro sempre come foglia 
			if (empty(right(t))){
				t->right = cons(el, emptytree(), emptytree());
				t = right(t);
			}
			t = right(t);
		}
	}
	return l;	//ritorno l che è un puntatore alla radice di t
}

tree delete(tree l, int e){
	tree padre_con_figlio_sinistro_da_eleminare = emptytree();
	tree padre_con_figlio_destro_da_eleminare = emptytree();
	tree t = l;
	tree next = emptytree();

	while (!empty(l) && root(l) != e){
		if (e <= root(l)){
			padre_con_figlio_sinistro_da_eleminare = l;
			padre_con_figlio_destro_da_eleminare = emptytree();	//uscito dal while conosco il puntatore al nodo da elminare e il padre che ha come figlio destro o sinistro tale nodo 
			l = left(l);
		}
		
		else{

			padre_con_figlio_sinistro_da_eleminare = emptytree();
			padre_con_figlio_destro_da_eleminare = l;
			l = right(l);
		}
		
	}



	if (!empty(l)){	//devo tenere presente che l'elemento potrebbe non essere presente (dal while sopra si esce o quando si trova l'elemento o quando si arriva all'albero vuoto)

		if (empty(left(l)) && empty(right(l))){			//CASO 1: il nodo da eliminare è una foglia
			if (t == l)
				return emptytree();
			next = emptytree();


		}
		else{
			if (!empty(left(l)) && empty(right(l))){
				if (t == l)									//CASO 2: il nodo ha un figlio, o destro o sinistro non lo so a priori quindi mi serve un ulteriore else
					return left(l);
				next = left(l);

			}
			else{
				if (empty(left(l)) && !empty(right(l))){
					if (t == l)
						return right(l);
					next = right(l);
				}

				else{		//CASO 3: il nodo ha 2 figli
					padre_con_figlio_destro_da_eleminare = l;
					padre_con_figlio_sinistro_da_eleminare = emptytree();
					next = right(l);
					if (!empty(next)){
						while (!empty(left(next))){
							padre_con_figlio_destro_da_eleminare = emptytree();
							padre_con_figlio_sinistro_da_eleminare = next;	//arrivo al successore
							next = left(next);
						}

						l->value = root(next);//il valore del nodo da eliminare è il valore di next(successore)
						if (!empty(right(next)))
							next = right(next);		//questo blocco di controllo serve perchè il successore potrebbe avere figli nel sottoalbero destro
						else
							next = emptytree();
					}

				}
			}

		}
		if (!empty(padre_con_figlio_destro_da_eleminare))	//nel caso 3 l'eliminazione avviene: capio nel nodo che devo elminare il valore del successore, dopo se il successore aveva figlio destro (sinistro è impossibile) elimino tale successore
			padre_con_figlio_destro_da_eleminare->right = next;	//impostando il valore del nodo successivo del padre a next cioè o il figlio destro del successore o null 
		else
			padre_con_figlio_sinistro_da_eleminare->left = next;
	}
	else
		printf("Elemento %d non presente sulla lista\n", e);
	return t;
}

int main(void){
	int e;
	tree r = emptytree();
	do{
		printf("Inserire elementi, terminare con zero: ");
		scanf("%d", &e);
		if (e == 0)
			break;
		r = insOrd(e, r);
	} while (true);

	preorder(r);
	putchar('\n');
	postorder(r);
	putchar('\n');
	inorder(r);
	putchar('\n');
	r = delete(r, 333);
	preorder(r);
}