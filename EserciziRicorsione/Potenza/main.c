#include <stdlib.h>

int esp(int b, int e){
	if (e == 0)
		return 1;
	return b*esp(b, --e);
}

int main(void){
	int exp = 0;
	int base = 3;
	int esponenziale = esp(base, exp);
	return 0;
}