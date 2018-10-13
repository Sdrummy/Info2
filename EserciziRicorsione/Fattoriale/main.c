unsigned int fact(unsigned int n){
	if (n == 0)
		return 1;
	return n*fact(n - 1);
}


int main(void){
	unsigned int a = 4,b;
	b = fact(a);
	return 0;
}