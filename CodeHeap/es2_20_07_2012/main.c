#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
	char nome[20];
	float cost;
}processo;

int left(int pos){
	return 2 * pos;
}
int right(int pos){
	return 2 * pos + 1;
}
int parent(int pos){
	return pos / 2;
}
bool isempty(int pos, int heap_size){
	return (pos > heap_size);
}
void move_down(processo *v, int pos, int hs){
	int u;
	processo sup;
	if (isempty(pos, hs))
		return;
	if (v[right(pos)].cost > v[left(pos)].cost)
		u = right(pos);
	else
		u = left(pos);

	if (v[pos].cost < v[u].cost){
		sup = v[pos];
		v[pos] = v[u];
		v[u] = sup;
		move_down(v, u, hs);
	}
	
}
void heapify(processo *v, int pos, int hs){
	if (!isempty(pos, hs)){
		heapify(v, left(pos), hs);
		heapify(v, right(pos), hs);
		move_down(v, pos, hs);
	}
}
int leggi(processo *v){	//ritorna la dimensione del vettore
	processo sup;
	int i = 1,check,check2;
	FILE *f = fopen("processi.dat", "rb");
	if (f == NULL)
		return 0;
	while (!feof(f)){
		check=fscanf(f, "%s", &sup.nome);
		check2=fscanf(f, "%f", &sup.cost);
		if (check == EOF || check2 == EOF)
			break;
		else{
			v[i] = sup;
			i++;
		}

	}
	fclose(f);
	return i-1;
}
void show(processo *v, int heap_size){
	int i = 1;
	printf("Processi da eseguire:\n");
	while (!isempty(i, heap_size)){
		printf("Nome: %s\tCosto: %f\n", v[i].nome, v[i].cost);
		i++;
	}
	putchar('\n');
}
void visualizza_elemento(processo *v, int el){
	printf("Prossimo elemento: %s\tCosto: %f\n", v[el].nome, v[el].cost);
}
void delete_next(processo *v, int *heap_size, int da_el){
	v[da_el] = v[*heap_size];
	(*heap_size)--;
	heapify(v, 1, *heap_size);
//	show(v, *heap_size);
}
int main(void){
	int c,i=1;
	processo v[50];
	int hs = leggi(v);
	show(v, hs);
	heapify(v, 1, hs);
	show(v, hs);
	//delete_next(v, &hs, 3);
	do{
		printf("Scegliere un comando:\n 1 Per visualizzare il prossimo elemento in coda\n 2 Per rimuovere il prossimo elemento dalla coda\n");
		scanf("%d", &c);
		switch (c){
		case 1:
			visualizza_elemento(v, i);
			i++;
			break;
		case 2:
			delete_next(v, &hs, i);
			i++;
			break;
		default:
			break;
		}
	} while (c != 0 && i <= hs);
	return 0;
}