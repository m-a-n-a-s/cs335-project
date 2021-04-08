// A function which swaps the values of two variables
void swap1(long long int var1, long long int var2){
    long long int temp = var1;
    var1 = var2;
    var2 = temp;
    return;
}

// A function which swaps the values referenced by two pointers
void swap2(long long int* a, long long int *b){
    long long int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

int hello(int x){
    int y=x*2;
    return y;
}

struct node{
	int val;
	int *next;
};


int main(){
    long long int var1 = 2;
    long long int var2 = 3;
int test_var=1+3*5/6;
 struct node *n;
//n->val=9;
    //int *x;
    //n->next=x;
    int z=2*hello(6)+1000;
    printf("Initially var1 = %lld and var2 = %lld\n",var1,var2);
    swap1(var1, var2);
    printf("After value swap, var1 = %lld and var2 = %lld\n",var1,var2);
    swap2(&var1, &var2);
    printf("After pointer swap var1 = %lld and var2 = %lld\n",var1,var2);
  
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
