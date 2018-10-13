int div(int min, int mag,int q){		//esegue la divisione intera tra 2 numeri, se si vuole anche il resto sarebbe necessario passare una variabile da riempire come puntatore 

	if (q == 0){
	int sup = mag;		//questo if si fa solo alla prima chiamata quando q è ancora 0 per scambiare dividendo e divisore secondo la definizione di divisione intera (quante volte il divisore stà nel dividendo)
	if (min > mag){		
		mag = min;
		min = sup;
		}
	}
	if (mag < min)
		
		return q;
	
		
	return div(min, mag - min, ++q);
}

int main(void){
	int ris = div(70, 9,0);
	return 0;
}