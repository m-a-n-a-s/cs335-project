int main(){
    int a = 5, b = 6;
    int c =  - a - b;
    int d = c/-2;
    int e = d * -1;
    int f = d - e;
    print_int(d);
    print_int(e);
    print_int(c);
    print_int(f);
    print_string("\n");
    if (c == 1) print_string("Incorrect\n");
    else if (c == -11) print_string("Correct\n");
    if(f==10) print_string("All correct");
    return 0;
}
