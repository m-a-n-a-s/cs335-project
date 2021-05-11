int main()
{
    int a[100];
    int n;
    int i;
    int t;
    int l;
    int h;
    print_string("Enter no. of elements\n");
    n=scanf();
    print_string("Enter elements\n");
    for(i=0;i<n;i=i+1){
        a[i]=scanf();
    }
    t=1;
    l=0;
    h=n-1;
    //print_int(h);
    while (h > l)
    {
        if ( a[l] != a[h])
        {
            t=0;
            break;
        }
        l=l+1;
        h=h-1;
    }
    if(t==0){
        print_string("NOT PALINDROME\n");
    }
    else{
        print_string("PALINDROME\n");
    }
    return 0;
}