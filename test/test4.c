/* A program to find 
the factorial of a number */

int factorial(int n){ 
    return (n == 1 || n == 0) ? 1 : n * factorial(n - 1); 
} 
  
int main() { 
    int var;
    scanf("%d",&var); 
    printf("Factorial of %d is %d\n", var, factorial(var)); 
    return 0; 
} 
