#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef /*qualsiasi cosa*/ int element;

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
bool isEqual(element e1, element e2){	 //cambiano con il tipo di element 
	return e1 == e2;					
}
bool isMajor(element e1, element e2){// cambiano con il tipo di element 
	return e1 > e2; //tenere presente l'uguale
}
bool isLess(element e1, element e2){// cambiano con il tipo di element 
	return e1 < e2; //occhio all'uguale
}
void scambia(element *v1, element *v2){
	element tmp;
	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}
void moveDown(int *v, int pos, int hs){
	int u = pos;
	if (isLeaf(pos, hs))
		return;
	if ((isLess(v[left(pos)], v[right(pos)]) || isEqual(v[left(pos)], v[right(pos)])) && left(pos) <= hs) // qua o nell'altro caso, in generale almeno 1 dei due deve avere is equal
		u = left(pos);
	else{
		if (right(pos) > hs)
			u = left(pos);
	}
	if (isLess(v[right(pos)], v[left(pos)]) && right(pos) <= hs)
		u = right(pos);


	if (isLess(v[u], v[pos])){
		scambia(&v[u], &v[pos]);
		moveDown(v, u, hs);
	}
}
void heapify(element *v, int pos, int hs){
	if (pos <= hs){
		heapify(v, left(pos), hs);
		heapify(v, right(pos), hs);
		moveDown(v, pos, hs);
	}
}
void heap_sort(element *v, int pos, int hs){
	for (int i = hs; i >= 2; i--){
		scambia(&v[1], &v[i]);
		heapify(v, 1, i - 1);
	}
}
void moveUp(element *v, int pos, int hs){
	int u;
	if (pos == 1)		//is root
		return;
	if (isLess(v[pos], v[parent(pos)])){
		u = parent(pos);
		scambia(&v[pos], &v[u]);
		moveUp(v, u, hs);
	}

}
element cerca_max(element *v, int hs){
	int  i;
	element max = v[hs];
	i = parent(hs);
	for (int count = hs; count < parent(hs); count--){
		if (isLess(max,v[count]))
			max = v[count];
	}
	return max;
}
void printElement(element e){ //da modificare in base all'element 
	printf(" %d \n", e);
}
void show(element *v, int hs){
	for (int i = 1; i <= hs; i++)
		printElement(v[i]);
}