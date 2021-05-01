int main(){
    int true = 1, false = 0;
    while(printf("Hello World\n") && 0){}
    while(false && true){printf("Incorrect\n");}
    while(true || false){printf("Working\n"); break;}
    while(false || printf("Good\n")){break;}
}