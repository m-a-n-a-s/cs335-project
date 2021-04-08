/* A program to find 
the factorial of a number */

int factorial(int n){ 
    return (n == 1 || n == 0) ? 1 : n * factorial(n - 1); 
} 
  
int main() { 
    int var=5; // Factorial of the number var would be stored in a variable called fact
    int fact=factorial(var);    
	printf("Factorial of %d is %d\n", var, fact); 
    return 0; 
} 
