int func(int a, int b){
	return a;
}

int f1(int a, int b, ...){
	return a;
}



int main()
{
    int n = 2;
    int x = func(2,3);
    int y = f1(2,3,4,5);
    int z = f1(2,3);
    int p = f1(2);

    for(n=0;n<2;n=n+1){
	print_int(n);
	}	

    return 0;
}
