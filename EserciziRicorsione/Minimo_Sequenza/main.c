


int indice_valore_minimo(int *v, int dim)
{
	int res;
	if (dim == 1)
		return 0;			//caso base, se la dimensione è 1 l'indice dell'elemento più piccolo sarà 0 per forza perchè sarà presente solo quell'elemento

	res = indice_valore_minimo(v, dim - 1);		//per ricorsione procedo a ritroso fino alla dimensione 1 di fatto ottenendo come primo valore di res il valore 0  
	if (v[res] < v[dim - 1])
		return res;		//quello che poi viene fatto è in pratica un controllo tra l'elemento in posizione ris e l'elemento subito successivo, se si considera dall'inizio si avrà come primo confronto v[0] con v[1] 
			//questo perchè prima verranno aperti tutti i record poi secondo la modalità LIFO verranno chiusi partendo dal fondo mantenendo sempre in vita il valore minimo risultante dal confronto 
	return dim - 1;
}


int main(void){
	int s[] = { 10, 60, 3,1 ,23,2344,777};
	int idx = 7;
	int c = indice_valore_minimo(s, idx);
	return 0;
}