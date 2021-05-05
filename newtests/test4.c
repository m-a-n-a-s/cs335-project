int main(){
    int true = 1, false = 0;
    while(print_string("Hello World\n") && 0){}
    while(false && true){print_string("Incorrect\n");}
    while(true || false){print_string("Working\n"); break;}
    while(false || print_string("Good\n")){break;}
    return 0;
}