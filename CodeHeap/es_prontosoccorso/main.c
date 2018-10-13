#define _CRT_SECURE_NO_WARNINGS
#define MAX_RECOVERIES 100
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
	char nome[20];
	char c_f[20];
	char referto[100];
	char codiceAccesso;
	char ora_ingresso[6];
}persona;



bool empty(int pos, int heap_size){
	return pos > heap_size;
}
int parent(int pos){
	return pos / 2;
}
int left(int pos){
	return 2 * pos;
}
int right(int pos){
	return 2 * pos + 1;
}
persona nextUp(persona *v){
	return v[1];
}
int convert_time(char *ora){
	int time;
	time = ((ora[0] - '0') * 10 + (ora[1] - '0')) * 60;
	time += (ora[3] - '0') * 10 + (ora[4] - '0');
	return time;
}
void moveDown(persona *v, int heap_size, int pos){
	int u;
	persona sup;
	if (empty(pos, heap_size))
		return;
	if (v[right(pos)].codiceAccesso > v[left(pos)].codiceAccesso || ( (v[right(pos)].codiceAccesso == v[left(pos)].codiceAccesso) && convert_time(v[right(pos)].ora_ingresso) > convert_time(v[left(pos)].ora_ingresso)))
		u = right(pos);
	else
		u = left(pos);
	if (v[u].codiceAccesso > v[pos].codiceAccesso || ( (v[u].codiceAccesso == v[pos].codiceAccesso) && convert_time(v[u].ora_ingresso) > convert_time(v[pos].ora_ingresso))){
		sup = v[u];
		v[u] = v[pos];
		v[pos] = sup;
		moveDown(v, heap_size, u);
	}
}
void heapify(persona *v, int hs, int pos){
	if (!empty(pos, hs)){
		heapify(v, hs, left(pos));
		heapify(v, hs, right(pos));
		moveDown(v, hs, pos);
	}
}
void aggiungi(persona *v,int *pos){
	persona sup;
	fflush(stdin);
	printf("Inserire Nome e Cognome (zero-terminare): ");
	scanf("%[^0]", sup.nome);
	fflush(stdin);
	printf("Inserire codice fiscale CF del paziente: ");
	scanf("%s", sup.c_f);
	fflush(stdin);
	printf("Inserire referto (terminare inserimento con -1): ");
	scanf("%[^-1]", sup.referto);
	fflush(stdin);
	printf("Inserire codice identificativo (B,V,G,R,N): ");
	scanf("%c", &sup.codiceAccesso);
	fflush(stdin);
	printf("Orario di entrata (xx:xx): ");
	scanf("%s", sup.ora_ingresso);
	fflush(stdin);
	v[*pos] = sup;
	(*pos)++;
	
}

void visualizza_next(persona *v,int pos){
	printf("\nProssimo paziente da visitare:\n");
	printf("Nome: %s\nReferto: %s\n", v[pos].nome, v[pos].referto);
	printf("Codice di accesso: %c\tOrario di ingresso: %s (in minuti %d)\n", v[pos].codiceAccesso, v[pos].ora_ingresso, convert_time(v[pos].ora_ingresso));
}
int main(void){
	int pos = 1,check;
	persona ricoverati[MAX_RECOVERIES];
	
	
	do{
		printf("\t\t\tBenvenuti al pronto soccorso di stocazzo:\n 1 Per schedare paziente\n 2 Per visualizzare il prossimo paziente in coda\n");
		scanf("%d", &check);
		switch (check){
		case 1:
			aggiungi(ricoverati, &pos);
			break;
		case 2:
			visualizza_next(ricoverati, pos-1);
			break;
		default:
			printf("Inserire un comando valido");
			break;
		}
		heapify(ricoverati, pos, 1);
	} while (pos < MAX_RECOVERIES);
}