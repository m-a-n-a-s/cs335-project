/* A program to test
the swap functions */

#include <stdio.h>

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

int main(){
    long long int var1 = 2;
    long long int var2 = 3;
    printf("Initially var1 = %lld and var2 = %lld\n",var1,var2);
    swap1(var1, var2);
    printf("After value swap, var1 = %lld and var2 = %lld\n",var1,var2);
    swap2(&var1, &var2);
    printf("After pointer swap var1 = %lld and var2 = %lld\n",var1,var2);
    return 0;
}