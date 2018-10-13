#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
	char Nome[20];
	char CF[17];
	char Referto[100];
	char CodiceAccesso;
} Persona;

typedef Persona element;

int left(int pos){
	return 2 * pos;
}
int right(int pos){
	return 2 * pos + 1;
}
int parent(int pos){
	return pos / 2;
}

bool isless(element e1, element e2){
	return e1.CodiceAccesso < e2.CodiceAccesso;
}

bool isleaf(int pos, int hs){
	if (left(pos) > hs && right(pos) > hs)
		return true;
	return false;
}
void scambia(element *v1, element *v2){
	element tmp;
	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}
void moveDown(element *v, int pos, int hs){
	int u = pos;
	if (isleaf(pos,hs))
		return;
	if (isless(v[left(pos)], v[right(pos)]) && left(pos) <= hs)
		u = left(pos);
	
	if (right(pos) > hs && left(pos)<=hs)
			u = left(pos);
		
	if (isless(v[right(pos)], v[left(pos)]) && right(pos) <= hs)
		u = right(pos);
	
	
	if (isless(v[u], v[pos])){
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
void moveUp(element *v, int pos, int hs){
	int u;
	if (pos==1)		//is root
		return;
	if (isless(v[pos], v[parent(pos)])){
		u = parent(pos);
		scambia(&v[pos], &v[u]);
		moveUp(v, u, hs);
	}
		
}
void printElement(element e){
	printf("Nome: %s\nCodice Fiscale: %s\nReferto: %s\nCodice d'accesso: %c\n\n", e.Nome, e.CF, e.Referto, e.CodiceAccesso);
}
void show(element *v, int hs){
	for (int i = 1; i <= hs; i++)
		printElement(v[i]);
}
void add(element *vet,element e, int *hs){
	(*hs)++;
	vet = realloc(vet, (*hs + 1)*sizeof(element));
	vet[*hs] = e;
	moveUp(vet, *hs, *hs);
}
element cerca_max(element *v, int hs){
	int  i;
	element max=v[hs];
	i = parent(hs);
	for (int count = hs; count < parent(hs); count--){
		if (v[count].CodiceAccesso>max.CodiceAccesso)
			max = v[count];
	}
	return max;
}

int main(void){
	int c,hs;
	element sup;
	element *v = malloc(sizeof(element)); // heap vuoto 
	hs = 0;

	do{
		printf("Scegliere un' azione:\n.1 Aggiungi paziente\n.2 Visualizza paziente con priorità più bassa\n.3 Visualizza paziente con priorità più alta\n.4 Elimina paziente con priorità più alta\n");
		scanf("%d", &c);
		switch (c){
		case 1:
			printf("Inserire paziente: (nome,cf,referto,codice acc)");
			scanf("%s %s %s %c", &sup.Nome, &sup.CF, &sup.Referto, &sup.CodiceAccesso);
			add(v, sup, &hs);
			break;
		case 2:
			printf("Paziente con priorità più bassa:\n");
			printElement(v[1]);
			break;
		case 3:
			sup = cerca_max(v, hs);
			printf("Prossimo con priorità massima:\n");
			printElement(sup);
			break;
		case 4:
			printElement(v[hs]);
			v = realloc(v, --hs*sizeof(element));
			printElement(v[hs]);
			break;
		default:
			c = 0;
			break;
		}


	} while (c != 0);

	free(v);
	return 0;
}
