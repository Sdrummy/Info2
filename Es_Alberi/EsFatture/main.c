#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
	int codart;
	char descrizione[50];
	char tipologia[50];
}articolo;

typedef struct {
	int codfat;
	char data[11];
	char tipopagamento[20];
	int iva;
	char piva[16];
}fattura;

typedef struct{
	int codfat;
	int nriga;
	int codart;
	int quantità;
	float prezzouni;
}rigaFattura;


typedef struct node{
	rigaFattura r;
	struct node* next;
}item;
typedef item* list;

typedef struct nodeArt{
	articolo a;
	struct nodeArt *left, *right;
}itemArt;
typedef itemArt* treeA;


typedef struct nodeFt{
	fattura f;
	list righe;
	struct nodeFt *left, *right;
}itemFt;
typedef itemFt* treeF;

/*
*
*			PRIMITIVE ARTICOLI
*
*
*/


bool emptyA(treeA t){
	return t == NULL;
}
treeA emptytreeart(void){
	return NULL;
}
treeA leftA(treeA t){
	return t->left;
}
treeA rightA(treeA t){
	return t->right;
}
articolo rootA(treeA t){
	return t->a;
}
treeA constreeA(treeA l, treeA r, articolo art){
	treeA t = malloc(sizeof(itemArt));
	t->left = l;
	t->right = r;
	t->a = art;
	return t;
}
bool isLessA(articolo a1, articolo a2){
	return a1.codart < a1.codart;
}
treeA insOrdArt(treeA l, articolo a){
	treeA t = constreeA(emptytreeart(), emptytreeart(), a), ris = l;
	if (emptyA(l))
		return t;
	while (!emptyA(l)){
		if (isLessA(a, rootA(l))){
			if (emptyA(leftA(l))){
				l->left = t;
				l = leftA(l);
			}
			l = leftA(l);
		}
		else{
			if (emptyA(rightA(l))){
				l->right = t;
				l = rightA(l);
			}
			l = rightA(l);
		}
	}
	return ris;
}
treeA leggiart(void){
	treeA ris = emptytreeart();
	articolo sup;
	FILE *f = fopen("articoli.dat", "rb");
	if (f == NULL)
		return ris;
	while (fread(&sup, sizeof(articolo), 1, f) > 0)
		ris = insOrdArt(ris, sup);

	fclose(f);
	return ris;
}

void showArticoli(treeA l){
	if (!emptyA(l)){
		printf("Codice articolo: %d\nDescrizione: %s\nTipologia: %s\n", rootA(l).codart, rootA(l).descrizione, rootA(l).tipologia);
		showArticoli(leftA(l));
		showArticoli(rightA(l));
	}
}




/*
*
*
*
*		PRIMITIVE FATTURE
*
*
*/

bool emptyF(treeF t){
	return t == NULL;
}
treeF emptytreef(void){
	return NULL;
}
treeF leftF(treeF t){
	return t->left;
}
treeF rightF(treeF t){
	return t->right;
}
fattura rootF(treeF t){
	return t->f;
}
treeF constreeF(treeF l, treeF r, fattura ft){
	treeF t = malloc(sizeof(itemFt));
	t->left = l;
	t->right = r;
	t->f = ft;
	return t;
}
bool islessF(fattura f1, fattura f2){
	return (strcmp(f1.piva, f2.piva) < 0);
}

treeF insOrdFt(treeF l, fattura a){
	treeF t = constreeF(emptytreef(), emptytreef(), a), ris = l;
	if (emptyF(l))
		return t;
	while (!emptyF(l)){
		if (islessF(a, rootF(l))){
			if (emptyF(leftF(l))){
				l->left = t;
				l = leftF(l);
			}
			l = leftF(l);
		}
		else{
			if (emptyF(rightF(l))){
				l->right = t;
				l = rightF(l);
			}
			l = rightF(l);
		}
	}
	return ris;
}
void nullaFatture(treeF t){
	if (!emptyF(t)){
		t->righe = NULL;
		nullaFatture(leftF(t));
		nullaFatture(rightF(t));
	}
}
treeF leggiFatture(void){
	fattura sup;
	treeF ris = emptytreef();
	FILE *f = fopen("fatture.dat", "rb");
	if (f == NULL)
		return emptytreef();
	while (fread(&sup, sizeof(fattura), 1, f) > 0)
		
		ris = insOrdFt(ris, sup);
	
		
	fclose(f);
	nullaFatture(ris);
	return ris;
}

/*
*
*
*	PRIMITIVE LISTA RIGHE
*
*
*/


bool empty(list l){
	return l == NULL;
}
list emptylist(void){
	return NULL;
}
list tail(list l){
	return l->next;
}
rigaFattura head(list l){
	return l->r;
}
list cons(list l, rigaFattura a){
	list r = malloc(sizeof(item));
	r->r = a;
	r->next = l;
	return r;
}
bool isls(rigaFattura r1, rigaFattura r2){
	return r1.nriga < r2.nriga;
}
/*list insOrd(list l, rigaFattura r){		//ulteriore versione dell'inserimento ordinato per liste
	list l1 = emptylist(), rt = l, t = cons(l, r);
	if (empty(l) || isls(r, head(l)))
		return t;
	//return cons(insOrd(tail(l), r), head(l));
	while (!empty(l) && !isls(r, head(l))){
		l1 = l;
		l = tail(l);
	}
	l1->next = cons(l, r);
	t->next = emptylist();
	return rt;
}*/
list insOrd(list l, rigaFattura r){
	list t = cons(l, r);
	if (empty(l) || isls(r, head(l)))
		return t;
	return cons(insOrd(tail(l), r), head(l));
}

void inserisciRighe(treeF t, rigaFattura r){
	if (!emptyF(t)){
		if (r.codfat == rootF(t).codfat)
			t->righe = insOrd(t->righe, r);
		inserisciRighe(leftF(t), r);
		inserisciRighe(rightF(t), r);

	}

}
treeF leggiRighe(treeF t){
	rigaFattura sup;
	FILE *f = fopen("righefattura.dat", "rb");

	while (fread(&sup, sizeof(rigaFattura), 1, f) > 0)
		inserisciRighe(t, sup);

	fclose(f);
	return t;
}
void show_articoli_codice(treeA art, int codart){
	if (!emptyA(art)){
		if (rootA(art).codart == codart)
			printf("Descrizione articolo: %s\n\nTipologia: %s\n\n", rootA(art).descrizione, rootA(art).tipologia);
		show_articoli_codice(leftA(art), codart);
		show_articoli_codice(rightA(art), codart);
	}
}
void visualizzaRigheFatture(list l,treeA articoli){
	while (!empty(l)){
		printf("Codice articolo: %d\nNumero articoli acquistati: %d\nPrezzo unitario: %f\n", head(l).codart, head(l).quantità, head(l).prezzouni);
		show_articoli_codice(articoli, head(l).codart);
		l = tail(l);
	}
	putchar('\n');
}

void visualizzaFatture(treeF t,treeA art){
	if (!emptyF(t)){
		printf("Fattura: %d\nData: %s\nTipo di pagamento: %s\nIva imposta: %d\nPartita iva: %s\n", rootF(t).codfat, rootF(t).data, rootF(t).tipopagamento, rootF(t).iva, rootF(t).piva);
		printf("\nArticoli acquistati/venduti:\n\n");
		visualizzaRigheFatture(t->righe,art);
		visualizzaFatture(leftF(t),art);
		visualizzaFatture(rightF(t),art);
	}
}
void show_con_iva(treeF t,treeA art, char *partiva){
	if (!emptyF(t)){

		if (strcmp(rootF(t).piva, partiva) == 0){
			printf("Fattura: %d\nData: %s\nTipo di pagamento: %s\nIva imposta: %d\nPartita iva: %s\n", rootF(t).codfat, rootF(t).data, rootF(t).tipopagamento, rootF(t).iva, rootF(t).piva);
			printf("\nArticoli acquistati/venduti:\n\n");
			visualizzaRigheFatture(t->righe,art);
		}
		
		
		show_con_iva(leftF(t),art,partiva);
		show_con_iva(rightF(t),art, partiva);
	}
}

void scriviArticoli(void){
	articolo sup;
	int check;
	FILE *f = fopen("articoli.dat","wb");
	do{
		
		printf("Inserire codice articolo: ");
		scanf("%d", &sup.codart);
		fflush(stdin);


		printf("Inserire una descrizione dell'articolo: ");
		scanf("%[^\n]", sup.descrizione);
		fflush(stdin);

		printf("Inserire tipologia di articolo in questione: ");
		scanf("%[^\n]", sup.tipologia);
		
		printf("Continuare? ");
		scanf("%d", &check);
		fwrite(&sup, sizeof(articolo), 1, f);
	} while (check != 0);
	fclose(f);

}

void scriviFatture(void){
	fattura sup;
	int c;
	FILE *f = fopen("fatture.bin", "wb");
	do{

		printf("Inserire codice fattura: ");
		scanf("%d", &sup.codfat);
		fflush(stdin);

		printf("Inserire data riportata sulla fattura: ");
		scanf("%[^\n]", sup.data);
		fflush(stdin);

		printf("Inserire tipologia di pagamento: ");
		scanf("%[^\n]", sup.tipopagamento);
		fflush(stdin);

		printf("Inserire percentuale iva: ");
		scanf("%d", &sup.iva);

		printf("Inserire partita iva: ");
		scanf("%s", sup.piva);

		printf("Continuare? ");
		scanf("%d", &c);

		fwrite(&sup, sizeof(fattura), 1, f);
	} while (c != 0);
	fclose(f);
}

void scriviRigheFatture(void){
	rigaFattura sup;
	int c;
	FILE *f = fopen("righefatture.dat", "wb");
	printf("Inserire le righe relative ad ogni fattura:\n");
	do{
		printf("Inserire codice fattura: ");
		scanf("%d", &sup.codfat);
		printf("Inserire il numero della riga in questione nella fattura: ");
		scanf("%d", &sup.nriga);
		printf("Inserire codice articolo: ");
		scanf("%d", &sup.codart);
		printf("Inserire prezzo unitario: ");
		scanf("%f", &sup.prezzouni);
		printf("Inserire numero di articoli acquistati: ");
		scanf("%d", &sup.quantità);

		printf("Continuare? ");
		scanf("%d", &c);
		fwrite(&sup, sizeof(rigaFattura), 1, f);
	} while (c != 0);
	fclose(f);
}


int main(void){
	char partita_iva[16];
	//scriviRigheFatture();
	//scriviArticoli();
	treeA prova = leggiart();
	printf("Articoli presenti:\n\n\n");
	showArticoli(prova);
	//scriviFatture();
	treeF ft = leggiFatture();
	//nullaFatture(ft);
	treeF fatture_finali = leggiRighe(ft);
	printf("\nFatture registrate:\n\n\n");
	visualizzaFatture(fatture_finali,prova);
	printf("\nInserire una partita iva: ");
	scanf("%s", partita_iva);
	printf("\n\nFatture trovate con la seguente partita iva (%s):\n\n", partita_iva);
	show_con_iva(fatture_finali,prova, partita_iva);
}