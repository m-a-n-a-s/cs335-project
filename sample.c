struct node{
    long a;
    int b;
};

void foo(struct node *n1){
    n1->a=7;
    n1->b=8;
    return;
}
void bar(struct node n1){
    n1.a=9;
    n1.b=10;
}
int main(){
    struct node n;
    struct node *n1;
    
    int x,y;
    n1=&n;
    n1->a=2;
    n1->b=3;
    x=n1->a;
    y=n1->b;
    print_int(x);
    print_int(y);
    foo(&n);
    x=n1->a;
    y=n1->b;
    print_int(x);
    print_int(y);
    
    return 0;
}