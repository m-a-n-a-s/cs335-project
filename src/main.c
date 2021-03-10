#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *yyin;

int main(int argc, char * argv[]){
    if (argc < 4){
        printf("ERROR ::: USAGE: <Parser> <File Name> -o <Output File Name>");
        return -1;
    }
    yyin = fopen(argv[1], "r");
    FILE* graph_script = fopen(argv[3], "w");
    fprintf(graph_script, "digraph G {\n\tordering=out;\n");
    yyparse();
    fprintf(graph_script, "}\n");
    fclose(yyin);
    fclose(graph_script);
    return 0;
}