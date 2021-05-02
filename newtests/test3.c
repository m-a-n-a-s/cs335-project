int fib(int n){
    if (n <= 1) return 1;
    return fib(n-1) + fib(n-2);
}

int main(){
    int n, a = 1, b = 1, c, d, i;
    n=scanf();
    //n=3;
    //d=3;
    d = fib(n);
    for(i = 2; i <= n; i=i+1){
        c = a + b;
        a = b;
        b = c;
    }
    //print_int(c);
    if (n < 2 && d == 1) print_string("Correct\n");
    else if (n >= 2 && d == c) print_string("Correct\n");
    else print_string("Incorrect\n"); 
    return 0;
}