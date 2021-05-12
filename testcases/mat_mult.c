int main()
{
    int a[2][2],b[2][2],c[2][2];
    int i,j,k;
    int tmp;
    print_string("Enter 4 elements for matrix a:\n");
    for(i=0;i<2;i=i+1){
        for(j=0;j<2;j=j+1){
            a[i][j]=scan_int();
        }
    }
    print_string("Enter 4 elements for matrix b:\n");
    for(i=0;i<2;i=i+1){
        for(j=0;j<2;j=j+1){
            b[i][j]=scan_int();
        }
    }
    for (i = 0; i < 2; i=i+1) {
        for (j = 0; j < 2; j=j+1) {
            c[i][j] = 0;
            for (k = 0; k < 2; k=k+1){
                tmp=c[i][j];
                c[i][j]=tmp+(a[i][k]*b[k][j]);
            }
        }
    }
    print_string("res of a X b is:\n");
    for(i=0;i<2;i=i+1){
        for(j=0;j<2;j=j+1){
            print_int(c[i][j]);
            print_string(" ");
        }
        print_string("\n");
    }
    return 0;
}