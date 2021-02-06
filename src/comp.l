%{
#include <stdio.h>
void yyerror (char *s);
int yylex();
%}
%%

%%
void yyerror(char *s){
	printf("ERROR: %s\n",s);
	exit(1);
}

int main(int argc, char *argv[]){
	if(argc!=2){
        printf("Please specify an existing filename\n");	
		return 1;
	}
    yyin = fopen(argv[1], "r");
    
	fclose(yyin)
	return 0;
}
