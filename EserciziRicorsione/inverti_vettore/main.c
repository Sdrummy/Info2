void scambia(int *v, int size,int posi,int posf){
	if (posi >= posf)
		return;
	scambia(v, size, ++posi, --posf);
	int sup = v[posf+1];
	v[posf+1] = v[posi-1];
	v[posi-1] = sup;
}

int main(void){
	int v[] = { 1, 2, 3, 4, 5, 6,7,8,21 };
	int sz = 9;
	scambia(v, sz,0,sz-1);
	return 0;
}