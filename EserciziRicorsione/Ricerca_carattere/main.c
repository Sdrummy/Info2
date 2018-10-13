#include <stdbool.h>

bool cerca_ch(char *str, char chr){			//devo verificare se il carattere chr è o no presente in str
	bool t;
	if (str[0] == 0)
		return false;
	if (str[0] == chr)
		return true;
	
	t=cerca_ch(str + 1, chr);
	return t;
}

int main(void){
	char *c = "o peppino di maiorca sbatti sta porta";
	bool check = cerca_ch(c, 'd');
	return 0;
}