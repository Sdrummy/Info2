#define _CRT_SECURE_NO_WARNINGS
#define MAX 50
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
	char nome[20];
	float prezzo;
}element;
int left(int pos){
	return 2 * pos;
}
int right(int pos){
	return 2 * pos + 1;
}
int parent(int pos){
	return pos / 2;
}
bool isLeaf(int pos, int hs){
	return (left(pos) > hs && right(pos) > hs) ? true : false;
}
typedef struct node{
	element e;
	struct node *next;
}item;
//typedef item* list;

/*bool empty(list l){
	return l == NULL;
}*/
bool isEqualPrice(element e1, element e2){
	return e1.prezzo == e2.prezzo;
}
bool isEqualName(element e1, element e2){
	return (strcmp(e1.nome, e2.nome) == 0);
}
bool isLess(element e1, element e2){
	return e1.prezzo < e2.prezzo;
}
void scambia(element *v1, element *v2){
	element tmp;
	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}
bool isEqual(element e1, element e2){
	return e1.prezzo == e2.prezzo;
}
bool omonimi(element e1, element e2){
	return (strcmp(e1.nome, e2.nome) == 0);
}
/*list emptylist(void){
	return NULL;
}
list tail(list l){
	return l->next;
}
element head(list l){
	return l->e;
}
list cons(list l, element e){
	list root = malloc(sizeof(item));
	root->e = e;
	root->next = l;
	return root;
}
void scrivi(void){
	element sup;
	int c;
	FILE *f = fopen("acquisti.dat", "wb");
	do{
		printf("Nome: ");
		scanf("%s", sup.nome);
		printf("Prezzo: ");
		scanf("%f", &sup.prezzo);
		fwrite(&sup, sizeof(item), 1, f);
		printf("Continuare? ");
		scanf("%d", &c);
	} while (c != 0);
	fclose(f);
}
list leggi(void){
	element e;
	list root = emptylist();
	FILE *f = fopen("acquisti.dat", "rb");
	if (f == NULL)
		return root;
	while (fread(&e, sizeof(item), 1, f) > 0)
		root = cons(root, e);
	fclose(f);
	return root;
}
void show(list l){
	while (!empty(l)){
		printf("Nome prodotto: %s  Costo: %f\n", head(l).nome, head(l).prezzo);
		l = tail(l);
	}
}
list crea_list(element e, list l){
	list s = emptylist();
	while (!empty(l)){
		if (isEqualPrice(e, head(l)))
			s = cons(s, head(l));
		l = tail(l);
	}
	return s;
}
void stampa_max_el(list l){
	element max;
	int max_val = 0, cur = 0;
	list sup = l;
	if (empty(tail(l))){
		printf("Con il prezzo %f compare un solo articolo: %s", head(l).prezzo, head(l).nome);
		return;
	}
	while (!empty(l)){
		sup = tail(l);
		while (!empty(sup)){
			if (isEqualName(head(l), head(sup)))
				cur++;
			sup = tail(sup);
		}
		if (cur > max_val){
			max = head(l);
			max_val = cur;
		}
		l = tail(l);
	}
	printf("L'elemento maggiormente acquistato per %f risulta: %s che compare %d volte\n", max.prezzo, max.nome, max_val);
	
}

list new_no_head(list l, element e){	//funzione che a partire da una lista ne costruisce un'altra formata da tutti e soli gli elementi della prima lista con prezzo diverso da e
	list sup = emptylist();
	while (!empty(l)){					
		if (!isEqualPrice(e, head(l)))
			sup = cons(sup, head(l));
		l = tail(l);
	}
	return sup;
}
void cerca(list l){
	list root = emptylist();
	while (!empty(l)){

		root = crea_list(head(l), l);	
		stampa_max_el(root);
		l = new_no_head(l, head(l));//non posso usare la delete poichè dentro ad l gli elementi con costo uguale ad head(l) potrebbero essere più di uno (generalmente lo saranno) non contigui o non in prima posizione
	}
}*/
void scrivi(void){
	element sup;
	int c;
	FILE *f = fopen("acquisti.dat", "wb");
	do{
		printf("Nome: ");
		scanf("%s", sup.nome);
		printf("Prezzo: ");
		scanf("%f", &sup.prezzo);
		fwrite(&sup, sizeof(element), 1, f);
		printf("Continuare? ");
		scanf("%d", &c);
	} while (c != 0);
	fclose(f);
}
/*void moveDown(element *v, int pos, int hs){
	int u = pos;
	if (isLeaf(pos, hs))
		return;
	if ( (isLess(v[left(pos)], v[right(pos)]) || isEqual(v[left(pos)],v[right(pos)])) && right(pos) <= hs)
		u = right(pos);
	else{
		if (isLess(v[right(pos)], v[left(pos)]) && left(pos) <= hs)
			u = left(pos);
		else{
			if (right(pos) > hs)
				u = left(pos);
		}
	}
	if (isLess(v[pos], v[u])){
		scambia(&v[u], &v[pos]);
		moveDown(v, u, hs);
	}
}*/
void moveDown(element *v, int pos, int hs){
	int u = pos, l = left(pos), r = right(pos);
	if (l > hs && r > hs)
		return;
	if ( (v[l].prezzo > v[pos].prezzo) && l <= hs)
		u = l;
	else{
	if ((v[r].prezzo > v[pos].prezzo) && r <= hs)
			u = r;
	}
	if (u != pos){
		scambia(&v[u], &v[pos]);
		moveDown(v,u, pos);
	}
}
void heapify(element *v, int pos, int hs){
	if (pos <= hs){
		heapify(v, left(pos), hs);
		heapify(v, right(pos), hs);
		moveDown(v, pos, hs);
	}
}
void show(element *v, int hs){
	for (int i = 1; i <= hs; i++)
		printf("Nome: %s Costo: %f\n", v[i].nome, v[i].prezzo);
	
}
void leggi(element *v, int max, int *hs){
	int i = 1;
	element sup;
	FILE *f = fopen("acquisti.dat", "rb");
	if (f == NULL){
		*hs = 0;
		return;
	}
	while (i<MAX && fread(&sup, sizeof(element), 1, f)>0){
		v[i] = sup;
		i++;
	}
	fclose(f);
	*hs = i - 1;
	
}
void max_rep(element *v, int hs){
	int max = 1, i = 1, cur = 1; //almeno 1 volta ci sono, se si tiene 0 di fatto non dice quanti articoli ci sono a quel prezzo con lo stesso nome ma quanti articoli hanno quel prezzo -1
	element m,c;
	while (i < hs){

		while (v[i].prezzo == v[i + 1].prezzo && i < hs){
			if (omonimi(v[i], v[i + 1])){
				cur++;
				c = v[i];
				i++;
			}
			else{
				i++;
				if (cur>max){
					max = cur;
					m = c;
					cur = 0;
				}
			}
		}
			
			if (cur>max){	//		questo controllo è necessario farlo anche fuori dal primo while poichè nel caso in cui il blocco di omonimi coincida con la fine dell'heap (gli omonimi allo stesso prezzo vanno da v[x] a v[hs])
				max = cur;	//uscirei dal 1* while a causa del controllo i<hs però uscendo dentro a cur avrei il massimo ma dentro max non c'è nulla poichè il controllo vincolato all'else non viene svolto
				m = c;
				cur = 1;
			}
			if (max != 1)
				printf("Con il prezzo %f l'articolo che compare più volte è: %s %d volte\n", m.prezzo, m.nome, max);
			max = 1;
			cur = 1;
		i++;
	}
}
void heapsort(element *v, int hs){
	int i = hs;
	for (; i >= 1; i--){
		scambia(&v[1], &v[i]);
		heapify(v, 1, i - 1);
	}
}
int main(void){
	element v[MAX];
	int hs;
	
	//scrivi(); //per creare acquisti.dat
	//list l = leggi();
	leggi(v, MAX, &hs);

	heapify(v, 1, hs);
	show(v, hs);
	heapsort(v, hs);
	show(v, hs);
	max_rep(v, hs);
	
	//cerca(l);
}