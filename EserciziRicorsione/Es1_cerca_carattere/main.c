#include <stdbool.h>

bool verifica_num(int *num, int val, int lung,int index){	//esempio con ricorsione (tipo tail), notare che serve un parametro in più rispetto alla versione iterativa 
	if (lung == index)
		return false;
	if (num[index] == val)
		return true;							
	return verifica_num(num, val, lung, ++index);
}


/*bool verifica_num(int *num, int val, int lung){
	for (int i = 0; i < lung; i++){
		if (num[i] == val)
			return true;
	}
	return false;
}*/


int main(void){
	int v[5] = { 1, 2, 34, 5, 6 };
	int n = 5;
	int da_cercare = 2;
	bool check = verifica_num(v, da_cercare, n,0);		
	return 0;
}