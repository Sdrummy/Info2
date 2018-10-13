#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct sito{
	char nome[30];
	unsigned int numero_accessi;
}element;

typedef struct list_element{
	element e;
	struct list_element *next;
}item;

typedef item* list;

list emptylist(void){
	return NULL;
}

bool empty(list l){
	return l == NULL;
}

list cons(list l, element e){
	list t=malloc(sizeof(item));
	t->e = e;
	t->next = l;
	return t;

}
list tail(list l){
	return l->next;
}
element head(list l){
	element ris;
	ris = l->e;
	return ris;
}

void show(list l){
	printf("Siti web:\n");
	while (!empty(l)){
		printf("Nome:\t%s", head(l).nome);
		printf("\tNumero di accessi: %d", head(l).numero_accessi);
		putchar('\n');
		l = tail(l);
	}

}



list ordina(list l,element e){//si suppone che la lista di partenza sia già ordinata
	list t=emptylist();
	list root;
	
	root= l;
	if (empty(l) || e.numero_accessi > head(l).numero_accessi){//se l è vuota oppure il numero di accessi di e è maggiore alla testa di l (che si suppone essere il massimo di l) allora e dovrà essere la testa di l
		t = cons(l, e);											//quindi una semplice cons 
		return t;
	}
	return cons(ordina(tail(l), e), head(l));//se invece e è minore della testa di l con questa scrittura non faccio altro che scorrere in profondità la lista tramite chiamate ricorsive fino a che e non sarà maggiore di un certo elemento di l
}											//o fino a che e non sarà l'ultimo elemento di l, dopodichè tornando indietro con le chiamate ricorsive aggiungerò i successivi nodi di l in testa ad e 


list leggi_da_file(void){
	list root = emptylist();
	element e;
	FILE *f = fopen("siti.txt", "rt");
	while (!feof(f)){
		fscanf(f, "%s", &e.nome);
		fscanf(f, "%d", &e.numero_accessi);
		root = ordina(root, e);

	}
	fclose(f);
	return root;
}


int main(void){
	char ins_nome[30]; //al più un sito può avere 30 char 
	list root = leggi_da_file();
	list root2 = root;
	show(root);
	
	printf("\nI tre migliori siti sono:\n");
	for (int i = 0; i < 3; i++){
		printf("In posizione numero %d  con %d visite:\t%s\n",i+1, head(root).numero_accessi, head(root).nome);
		root = tail(root);
	}

	printf("Inserire una stringa di ricerca: ");
	scanf("%s", ins_nome);
	unsigned int len = strlen(ins_nome);
	printf("\nSiti che contengono nella parte iniziale la stringa inserita: ");
	while (!empty(root2)){
		if (strncmp(ins_nome, head(root2).nome, len) == 0)
			printf("\n%s\tNumero visite: %d", head(root2).nome, head(root2).numero_accessi);
		root2 = tail(root2);
	}
	return 0;
}