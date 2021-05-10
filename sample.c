struct node
{
    int val;
    int b;
};

void foo(struct node *tmp){
    tmp->val=3333;
    tmp->b=4;
    return;
}
struct node foobar(int val){
    struct node x;
    x.val=val;
    x.b=val+1;
    return x;
}
struct node foobar1(struct node x){
    x.val=2324;
    x.b=50;
    return x;
}
int main()
{
    struct node a;
    //struct node arr[10];
    a.val=2;
    print_int(a.val);
    print_string("\n");
    foo(&a);
    print_int(a.val);
    print_string(" ");
    print_int(a.b);
    print_string("\n");
    a=foobar(500);
    print_int(a.val);
    print_int(a.b);
    print_string("\n");
    a=foobar1(a);
    print_int(a.val);
    print_int(a.b);
    print_string("\n");
    
    return 0;
}