#include <stdlib.h>

size_t string_len(char *c){
	size_t ln;
	if (c[0] == 0)
		return 0;
	ln = 1 + string_len(c + 1);
	return ln;
}

int main(void){
	char *c = "que";
	size_t len = string_len(c);
	return 0;
}