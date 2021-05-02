int main(){
    int true = 1, false = 0;
    while(prints("Hello World\n") && 0){}
    while(false && true){prints("Incorrect\n");}
    while(true || false){prints("Working\n"); break;}
    while(false || prints("Good\n")){break;}
}