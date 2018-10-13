#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define N 3

typedef struct{
	int altezza;
	int peso;
	int limite;
} pacco;

typedef struct {
	int altezza;
	int pacco[N];
} torre;

bool verifica(torre *sol, pacco *p, int i, int fine){
	int j, somma = 0;
	for (j = 0; j<fine; j++)
		somma += p[sol->pacco[j]].peso;
	if (somma>p[i].limite)
		return false;
	return true;
}

void creatorre(int n, int s, torre *c, torre *b, pacco *pacchi,int *listauso){
	int i;
	if (s == n){
		if (c->altezza > b->altezza){
			for (i = 0; i < n; i++)
				b->pacco[i] = c->pacco[i];
			b->altezza = c->altezza;
		}
		return;
	}
	for (i = 0; i < n; i++){
		if (listauso[i] == 0){
			if (verifica(c,pacchi,i,s) == 1){
				c->pacco[s] = i;
				listauso[i] = 1;
				c->altezza += pacchi[i].altezza;
				creatorre(n, s + 1, c, b, pacchi, listauso);
				c->pacco[s] = -1;
				listauso[i] = 0;
				c->altezza -= pacchi[i].altezza;
			}
			else
				creatorre(n, n, c, b, pacchi, listauso);
		}
	}

}



int main(void){
	torre corrente, best;
	int n = N;
	pacco elencopacchi[N];
	int listauso[N];


	elencopacchi[0].peso = 10;
	elencopacchi[0].altezza = 20;
	elencopacchi[0].limite = 40;

	elencopacchi[1].peso = 10;
	elencopacchi[1].altezza = 10;
	elencopacchi[1].limite = 8;

	elencopacchi[2].peso = 9;
	elencopacchi[2].altezza = 3;
	elencopacchi[2].limite = 5;

	for (int i = 0; i < n; i++){
		corrente.pacco[i] = -1;
		best.pacco[i] = -1;
		listauso[i] = 0;
	}

	corrente.altezza = 0;
	best.altezza = 0;
	creatorre(n, 0, &corrente, &best, elencopacchi, listauso);
	if (best.altezza == 0)
		printf("Impossibile impilare i pacchi");
	else{
	printf("La pila più alta risulta %d, formata dai pacchi (dall'ultimo al primo) ", best.altezza);
	for (int i = 0;best.pacco[i]!=-1; i++)
		printf("%d", best.pacco[i]);
	}
	
	return 0;
}
