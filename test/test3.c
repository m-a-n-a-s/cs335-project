/* A program to test
whether a string is a palindrome */
int MAX_LENGTH=100;
// A function to check palindrome string
int isPalindrome(char str[]){
    int i = 0;
    int j = strlen(str) - 1;
    
    while(i < j){
        if(str[i] != str[j]){
            return 0;
        }
        i++;
        j--;
    }
    return 1;
}

int main(){
    char str[MAX_LENGTH];
    char buf1[10]="";
    char buf2[10]=" ";
    char buf3[10]={'a','b'};
    fgets(str, MAX_LENGTH, stdin);
    str[strlen(str)-1] = '\0';
    if(isPalindrome(str)){
        printf("Yes %s is Palindrome\n", str);
    }
    else{
        printf("%s is not Palindrome\n", str);
    }
}
