#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>

int left(int i){
	return i * 2;
}
int right(int i){
	return i * 2 + 1;
}
int parent(int i){
	return i / 2;
}
/*bool isLeaf(int pos, int hs){
	if (left(pos) > hs && right(pos) > hs)
		return true;
	return false;
}*/
bool isLeaf(int pos, int hs){
	return (left(pos) > hs && right(pos) > hs) ? true : false;
}
bool isLess(int e1, int e2){
	return e1 < e2;
}
bool isEqual(int e1, int e2){	 //cambiano con il tipo di element 
	return e1 == e2;
}
void scambia(int *n1, int *n2)
{
	int temp;

	temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}
void moveDown(int *v, int pos, int hs){
	int u = pos;
	if (isLeaf(pos, hs))
		return;
	if (isLess(v[left(pos)], v[right(pos)]) && left(pos) <= hs)
		u = left(pos);

	if (right(pos) > hs && left(pos) <= hs)
		u = left(pos);

	if (isLess(v[right(pos)], v[left(pos)]) && right(pos) <= hs)
		u = right(pos);


	if (isLess(v[u], v[pos])){
		scambia(&v[u], &v[pos]);
		moveDown(v, u, hs);
	}
}
/*void moveDown(int *v, int hs, int pos){
	int u = pos;

	if (isLeaf(pos, hs))
		return;
	

	if (v[left(pos)] >= v[right(pos)] && left(pos) <= hs)
		u = left(pos);
	else{
		if (right(pos) > hs)			// i due else sono necessari quando si chiama la funzione su un vettore con un nodo che ha solo il figlio sinistro: in tal caso u è automaticamente 
			u = left(pos);				//il figlio sinistro poichè il figlio destro non esiste (o è già stato ordinato e quindi è per forza maggiore del sinistro (ordine crescente)però  non verifica l' and )
	}
	
	if (v[right(pos)] >= v[left(pos)] && right(pos) <= hs)
		u = right(pos);
	else{
		if (left(pos) > hs)
			u = right(pos);		//tecnicamente questo controllo sul right è inutile poichè una coda heap non può avere solo figlio destro e non sinistro
	}
	
	if (v[u] > v[pos] && u != pos){
		scambia(&v[u], &v[pos]);
		moveDown(v, hs, u);
	}
}*/

void heapify(int *v, int pos, int hs){
	if (pos<=hs){
		heapify(v, left(pos), hs);
		heapify(v, right(pos), hs);
		moveDown(v, pos, hs);
	}
}

void show(int *a,int heap_dim){
	int i;
	printf("[");
	for (i = 1; i <= heap_dim; i++)
		printf(" %d ", a[i]);
	printf("]\n");
}
void heapsort(int *A, int dim) {
	int i;

	

	for (i = dim; i >= 2; i--) {
		scambia(&A[1], &A[i]);
		
		heapify(A, 1, i - 1);
		//moveDown(A, i-1,  1);
	}
	return;
}

int main(void){
	int i=1;
	int vet[14] = { -1,12, 13, 231, 4, 12, 345, 3, 21, 5754, 1, 234, 11 ,6};

	heapify(vet, 1, 13);
	
	heapsort(vet, 13);
	show(vet, 13);
}
