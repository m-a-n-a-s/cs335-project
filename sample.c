struct node
{
    int val;
    struct node *next;
};
int main()
{
    int x;
    struct node a[5];
    struct node *tmp;
    int i;
    int t=0;
    for(i=0;i<4;i=i+1){
        a[i].next=&a[i+1];
    }
    //print_string("enter 5 values:\n");
    for(i=0;i<5;i=i+1){
        a[i].val=i;
    }
    a[4].next=&a[1];
    // tmp=a[0].next;
    // print_int(tmp->val);
    //print_string("enter value to find:\n");
    //x=scanf();
    i=0;
    x=2;
    tmp=a[4].next;
    x=tmp->val;
    print_int(x);
    // tmp=a[1].next;
    // print_int(tmp->val);
    // tmp=tmp->next;
    // print_int(tmp->val);
    // tmp=tmp->next;
    // print_int(tmp->val);
    // while(i<5){
    //     // if(x==tmp->val){
    //     //     t=1;
    //     // }
    //     // else{
    //     //     tmp=tmp->next;
    //     // }
    //     print_int(tmp->val);
    //     tmp=tmp->next;
    //     i=i+1;
    // }
    // if(x==1){
    //     print_string("FOUND\n");
    // }
    // else{
    //     print_string("NOT FOUND\n");
    // }

    return 0;
}