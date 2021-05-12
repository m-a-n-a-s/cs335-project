struct node
{
    int val;
    struct node *next;
};
int main()
{
    struct node a[5];
    struct node *tmp;
    int i;
    int x;
    int t = 0;
    for (i = 0; i < 4; i = i + 1)
    {
        a[i].next = &a[i + 1];
    }
    print_string("enter 5 values:\n");
    for (i = 0; i < 5; i = i + 1)
    {
        a[i].val = scan_int();
    }

    print_string("enter value to find:\n");
    x=scan_int();

    tmp=&a[0];
    i=0;
    while(i<5){
        if(x==tmp->val){
            t=1;
            break;
        }
        else{
            tmp=tmp->next;
        }
        //print_int(tmp->val);
        //tmp=tmp->next;
        i=i+1;
    }
    if(t==1){
        print_string("FOUND\n");
    }
    else{
        print_string("NOT FOUND\n");
    }

    return 0;
}