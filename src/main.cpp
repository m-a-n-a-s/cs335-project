#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *yyin;
FILE* ast;

 

int main(int argc, char * argv[]){
    if (argc < 4){
        printf("ERROR ::: USAGE: <Parser> <File Name> -o <Output File Name>\n");
        return -1;
    }
    yyin = fopen(argv[1], "r");
    ast = fopen(argv[3], "w");
    fprintf(ast, "digraph G {\n\tordering=out;\n");
    yyparse();
    fprintf(ast, "}\n");
    fclose(yyin);
    fclose(ast);
    return 0;
}
