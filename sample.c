int main(){
    int a[2][2];
    int i,j,tmp;
    for(i=0;i<2;i=i+1){
        for(j=0;j<2;j=j+1){
            tmp=scanf();
            a[i][j]=tmp;
        }
    }
    for(i=0;i<2;i=i+1){
        for(j=0;j<2;j=j+1){
            print_int(a[i][j]);
            print_string(" ");
        }
        print_string("\n");
    }

    return 0;
}