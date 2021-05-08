/* A program to test
whether the no. is prime or not */
int hello(int x){
    int y=x*2;
    return y;
}

struct node{
	int val;
	int *next;
};

int main(){
    int test_var=1+3*5/6;
    struct node *n;
    int z=2*hello(6)+1000;
    test_var = scanf();
    if(test_var < 2){
        print_string("Not Prime\n");
    }
    else{
	int i=0;
        int flag = 1;
        int max = 5;
        for(i=2;i<=max; i++){
            if(test_var % i == 0){
                print_string("Not Prime\n");
                flag = 0;
                break;
            }
        }
        if(flag){
            print_string("Yes, it is Prime\n");
        }
    }
    print_int(test_var);
    print_int(z);
    return 0;
}
