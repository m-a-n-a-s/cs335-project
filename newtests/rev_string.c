void rev(char *c,int n){
    int l=0;
    int h=n-1;
    char t;
    while(l<h){
        t=c[l];
        c[l]=c[h];
        c[h]=t;
        l=l+1;
        h=h-1;
    }
    return;
}
int main()
{
    char a[10];
    int n;
    int i;
    //n=3;
    print_string("Enter no. of elements\n");
    n=scanf();
    print_string("Enter elements\n");
    for(i=0;i<n;i=i+1){
        a[i]=scan_char();
    }
    rev(&a[0],n);
    for(i=0;i<n;i=i+1){
        print_char(a[i]);
    }
    return 0;
}