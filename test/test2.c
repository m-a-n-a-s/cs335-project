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
    //n->val=9;
    //int *x;
    //n->next=x;
    int z=2*hello(6)+1000;
    //scanf("%d",&test_var);
    if(test_var < 2){
        //printf("Not Prime\n");
    }
    else{
	int i=0;
        int flag = 1;
        int max = 5;//(int) sqrt((double)test_var);
        for(i=2;i<=max; i++){
            if(test_var % i == 0){
                //printf("Not Prime\n");
                flag = 0;
                break;
            }
        }
        if(flag){
            //printf("Yes, it is Prime\n");
        }
    }
    printf("%d %d",test_var,z);
    return 0;
}
