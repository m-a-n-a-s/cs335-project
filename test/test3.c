/* A program to test
whether a string is a palindrome */

#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

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
    fgets(str, MAX_LENGTH, stdin);
    str[strlen(str)-1] = '\0';
    if(isPalindrome(str)){
        printf("Yes %s is Palindrome\n", str);
    }
    else{
        printf("%s is not Palindrome\n", str);
    }
}