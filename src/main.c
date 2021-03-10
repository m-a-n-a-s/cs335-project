#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *yyin;
FILE* digraph;

int main(int argc, char * argv[]){
    if (argc < 4){
        printf("ERROR ::: USAGE: <Parser> <File Name> -o <Output File Name>\n");
        return -1;
    }
    yyin = fopen(argv[1], "r");
    digraph = fopen(argv[3], "w");
    fprintf(digraph, "digraph G {\n\tordering=out;\n");
    yyparse();
    fprintf(digraph, "}\n");
    fclose(digraph);
    //yyparse();
    fclose(yyin);
    return 0;
}
