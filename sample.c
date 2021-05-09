struct node{
    long a;
    int b;
};

// void foo(struct node *n1){
//     n1->a=7;
//     n1->b=8;
//     return;
// }
// void bar(struct node n1){
//     n1.a=9;
//     n1.b=10;
// }
int main(){
    struct node n;
    struct node *n1;
    int x,y;
    int *z;
    n1=&n;
    n1->a=2;
    n1->b=n.a+3*n1->a;
    x=n1->a;
    y=n1->b;
    print_int(x);
    print_string("\n");
    print_int(y);
    print_string("\n");
    //foo(&n);
    n.a=533;
    n.b=46;
    x=n.a;
    y=n1->b;
    print_int(x);
    print_string("\n");
    print_int(y);
    print_string("\n");
    z=&y;
    x=*z;
    print_int(x);
    
    return 0;
}