#include <stdlib.h>
#include <stdbool.h>

struct matrix{
	size_t rows, cols;
	double *data;
};

bool sim(struct matrix *m, size_t n){
	size_t r = m->cols;

	if (n == 1)
		return true;

	for (size_t i = 0; i < m->cols - 1; i++){
		if (m->data[(n-1)*r+i] != m->data[(i + 1)*(r)-(r-n+1)])		//algoritmo per scorrere le righe e cercare la simmetria 
			return false;
	}

	return sim(m, --n);


	
}


int main(void){
	struct matrix *cosa = malloc(sizeof(struct matrix));
	cosa->cols = cosa->rows = 5;
	cosa->data = malloc(25*sizeof(double));
	double v[]= { 1, 2,3,4,5,2,1,7,8,9,3,7,1,10,11,4,8,10,1,5,5,9,11,5,1 };
	for (size_t r = 0; r < 25; r++)
		cosa->data[r] = v[r];
	bool check = sim(cosa,5);
	return 0;
}