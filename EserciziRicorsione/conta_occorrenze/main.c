#include <stdlib.h>

int conta_occ(char *str, char dc,size_t index){
	int ris = 0;
	if (str[index] == 0)
		return 0;
	ris = conta_occ(str, dc, ++index);
	if (str[index - 1] == dc)
		ris++;
	return ris;
}


int main(void){
	char *c = "  ";
	char da_cercare = ' ';
	int c_occ = conta_occ(c, da_cercare,0);
	return 0;
}