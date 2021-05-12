struct node
{
    int val;
};

void foo(struct node *tmp){
    tmp->val=3333;
    return;
}
struct node foobar(int val){
    struct node x;
    x.val=val;
    return x;
}
struct node foobar1(struct node x){
    x.val=2324;
    return x;
}
int main()
{
    struct node a;
    a.val=2;
    print_int(a.val);
    print_string("\n");
    foo(&a);
    print_int(a.val);
    print_string("\n");
    a=foobar(500);
    print_int(a.val);
    print_string("\n");
    a=foobar1(a);
    print_int(a.val);
    print_string("\n");
    
    return 0;
}