/* A program to test
whether the no. is prime or not */

int main(){
    int test_var;
    scanf("%d",&test_var);
    if(test_var < 2){
        printf("Not Prime\n");
    }
    else{
        int flag = 1;
        int max = (int) sqrt((double)test_var);
        for(int i=2;i<=max; i++){
            if(test_var % i == 0){
                printf("Not Prime\n");
                flag = 0;
                break;
            }
        }
        if(flag){
            printf("Yes, it is Prime\n");
        }
    }
    return 0;
}
