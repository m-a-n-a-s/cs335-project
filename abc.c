/*int hello(int y){
	int x=5;
	return 2+hello(x);
}


int main(){
	int a[10];
	char c[2]={'a','b'};
	return 0;
}


*/
struct alpha{
	char c;
};
struct beta{
	struct alpha *m;
};
int func(){
    int y=2;
    struct node{
    	int a,b;
	};
	struct node x;
	return 1; 
}
int main()
{
    int x = func();
    int y=2;    
    if(x==1){
	//int z=3;
    }
    else{
	//int q=2;
    }
    return 0;
}
