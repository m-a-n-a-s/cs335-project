int max(int x, int y){
    if(x>y){
        return x;
    }
    else{
        return y;
    }
}

int main(){
    int a = 2, b = 3, i = 0, j = 1;
    for (; i <= max(a, b); i=i+1){
        j *= (j+1);
    }
    print_int(j);
    return 0;
}