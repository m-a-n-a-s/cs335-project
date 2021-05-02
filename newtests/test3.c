int fib(int n){
    if (n <= 1) return 1;
    return fib(n-1) + fib(n-2);
}

int main(){
    int n, a = 1, b = 1, c, d, i;
    //n=scanf();
    n=3;
    d = fib(n);
    for(i = 2; i <= n; i++){
        c = a + b;
        a = b;
        b = c;
    }
    if (n < 2 && d == 1) prints("Correct\n");
    else if (n >= 2 && d == c) prints("Correct\n");
    else prints("Incorrect\n"); 
    return 0;
}