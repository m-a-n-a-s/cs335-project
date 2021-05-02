int main(){
    int a = 2, b = 3, c = 4, d = 5;
    if (a <= 2){
        if (b <= 3){
            if (c == 4 && d >= 5){
                prints("Working\n");
            }
            else prints("Incorrect\n");
        }
        else if (b > 6) prints("Incorrect\n");
    }
}