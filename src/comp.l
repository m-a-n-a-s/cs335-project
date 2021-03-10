%{
#include <stdio.h>
#include "y.tab.h"
void yyerror (char *s);
int yylex();
void count();
void print();
static int col=1;
char lexeme[2048]; 
char token[2048];
%}
%option yylineno

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*


%%

"/*"(.|\n)*"*/"		{/*a C comment*/}
"//"(.)*(\n)		{/*a C comment*/}

"auto"			{ count(); strcpy(lexeme,yytext); strcpy(token,"AUTO"); return AUTO; }
"break"			{ count(); strcpy(lexeme,yytext); strcpy(token,"BREAK"); return BREAK; }
"case"			{ count(); strcpy(lexeme,yytext); strcpy(token,"CASE"); return CASE; }
"char"			{ count(); strcpy(lexeme,yytext); strcpy(token,"CHAR"); return CHAR; }
"const"			{ count(); strcpy(lexeme,yytext); strcpy(token,"CONST"); return CONST; }
"continue"		{ count(); strcpy(lexeme,yytext); strcpy(token,"CONTINUE"); return CONTINUE; }
"default"		{ count(); strcpy(lexeme,yytext); strcpy(token,"DEFAULT"); return DEFAULT; }
"do"			{ count(); strcpy(lexeme,yytext); strcpy(token,"DO"); return DO; }
"double"		{ count(); strcpy(lexeme,yytext); strcpy(token,"DOUBLE"); return DOUBLE; }
"else"			{ count(); strcpy(lexeme,yytext); strcpy(token,"ELSE"); return ELSE; }
"enum"			{ count(); strcpy(lexeme,yytext); strcpy(token,"ENUM"); return ENUM; }
"extern"		{ count(); strcpy(lexeme,yytext); strcpy(token,"EXTERN"); return EXTERN; }
"float"			{ count(); strcpy(lexeme,yytext); strcpy(token,"FLOAT"); return FLOAT; }
"for"			{ count(); strcpy(lexeme,yytext); strcpy(token,"FOR"); return FOR; }
"goto"			{ count(); strcpy(lexeme,yytext); strcpy(token,"GOTO"); return GOTO; }
"if"			{ count(); strcpy(lexeme,yytext); strcpy(token,"IF"); return IF; }
"int"			{ count(); strcpy(lexeme,yytext); strcpy(token,"INT"); return INT; }
"long"			{ count(); strcpy(lexeme,yytext); strcpy(token,"LONG"); return LONG; }
"register"		{ count(); strcpy(lexeme,yytext); strcpy(token,"REGISTER"); return REGISTER; }
"return"		{ count(); strcpy(lexeme,yytext); strcpy(token,"RETURN"); return RETURN; }
"short"			{ count(); strcpy(lexeme,yytext); strcpy(token,"SHORT"); return SHORT; }
"signed"		{ count(); strcpy(lexeme,yytext); strcpy(token,"SIGNED"); return SIGNED; }
"sizeof"		{ count(); strcpy(lexeme,yytext); strcpy(token,"SIZEOF"); return SIZEOF; }
"static"		{ count(); strcpy(lexeme,yytext); strcpy(token,"STATIC"); return STATIC; }
"struct"		{ count(); strcpy(lexeme,yytext); strcpy(token,"STRUCT"); return STRUCT; }
"switch"		{ count(); strcpy(lexeme,yytext); strcpy(token,"SWITCH"); return SWITCH; }
"typedef"		{ count(); strcpy(lexeme,yytext); strcpy(token,"TYPEDEF"); return TYPEDEF; }
"union"			{ count(); strcpy(lexeme,yytext); strcpy(token,"UNION"); return UNION; }
"unsigned"		{ count(); strcpy(lexeme,yytext); strcpy(token,"UNSIGNED"); return UNSIGNED; }
"void"			{ count(); strcpy(lexeme,yytext); strcpy(token,"VOID"); return VOID; }
"volatile"		{ count(); strcpy(lexeme,yytext); strcpy(token,"VOLATILE"); return VOLATILE; }
"while"			{ count(); strcpy(lexeme,yytext); strcpy(token,"WHILE"); return WHILE; }

{L}({L}|{D})*		{ count(); strcpy(lexeme,yytext); strcpy(token,"IDENTIFIER"); return IDENTIFIER; }
0[xX]{H}+{IS}?		{ count(); strcpy(lexeme,yytext);strcpy(token,"CONSTANT"); return CONSTANT; }
0{D}+{IS}?		{ count(); strcpy(lexeme,yytext);strcpy(token,"CONSTANT"); return CONSTANT; }
{D}+{IS}?		{ count(); strcpy(lexeme,yytext);strcpy(token,"CONSTANT"); return CONSTANT; }
L?'(\\.|[^\\'])+'	{ count(); strcpy(lexeme,yytext); strcpy(token,"CONSTANT");return CONSTANT; }

{D}+{E}{FS}?		{ count(); strcpy(lexeme,yytext);strcpy(token,"CONSTANT"); return CONSTANT; }
{D}*"."{D}+({E})?{FS}?	{ count(); strcpy(lexeme,yytext);strcpy(token,"CONSTANT"); return CONSTANT; }
{D}+"."{D}*({E})?{FS}?	{ count(); strcpy(lexeme,yytext);strcpy(token,"CONSTANT"); return CONSTANT; }

L?\"(\\.|[^\\"])*\"	{ count(); strcpy(lexeme,yytext); strcpy(token,"STRING_LITERAL"); return STRING_LITERAL; }

"..."			{ count(); strcpy(lexeme,yytext); strcpy(token,"ELLIPSIS"); return ELLIPSIS; }
">>="			{ count(); strcpy(lexeme,yytext); strcpy(token,"RIGHT_ASSIGN"); return RIGHT_ASSIGN; }
"<<="			{ count(); strcpy(lexeme,yytext); strcpy(token,"LEFT_ASSIGN"); return LEFT_ASSIGN; }
"+="			{ count(); strcpy(lexeme,yytext); strcpy(token,"ADD_ASSIGN"); return ADD_ASSIGN; }
"-="			{ count(); strcpy(lexeme,yytext); strcpy(token,"SUB_ASSIGN"); return SUB_ASSIGN; }
"*="			{ count(); strcpy(lexeme,yytext); strcpy(token,"MUL_ASSIGN"); return MUL_ASSIGN; }
"/="			{ count(); strcpy(lexeme,yytext); strcpy(token,"DIV_ASSIGN"); return DIV_ASSIGN; }
"%="			{ count(); strcpy(lexeme,yytext); strcpy(token,"MOD_ASSIGN"); return MOD_ASSIGN; }
"&="			{ count(); strcpy(lexeme,yytext); strcpy(token,"AND_ASSIGN"); return AND_ASSIGN; }
"^="			{ count(); strcpy(lexeme,yytext); strcpy(token,"XOR_ASSIGN"); return XOR_ASSIGN; }
"|="			{ count(); strcpy(lexeme,yytext); strcpy(token,"OR_ASSIGN"); return OR_ASSIGN; }
">>"			{ count(); strcpy(lexeme,yytext); strcpy(token,"RIGHT_OP"); return RIGHT_OP; }
"<<"			{ count(); strcpy(lexeme,yytext); strcpy(token,"LEFT_OP"); return LEFT_OP; }
"++"			{ count(); strcpy(lexeme,yytext); strcpy(token,"INC_OP"); return INC_OP; }
"--"			{ count(); strcpy(lexeme,yytext); strcpy(token,"DEC_OP"); return DEC_OP; }
"->"			{ count(); strcpy(lexeme,yytext); strcpy(token,"PTR_OP"); return PTR_OP; }
"&&"			{ count(); strcpy(lexeme,yytext); strcpy(token,"AND_OP"); return AND_OP; }
"||"			{ count(); strcpy(lexeme,yytext); strcpy(token,"OR_OP"); return OR_OP; }
"<="			{ count(); strcpy(lexeme,yytext); strcpy(token,"LE_OP"); return LE_OP; }
">="			{ count(); strcpy(lexeme,yytext); strcpy(token,"GE_OP"); return GE_OP; }
"=="			{ count(); strcpy(lexeme,yytext); strcpy(token,"EQ_OP"); return EQ_OP; }
"!="			{ count(); strcpy(lexeme,yytext); strcpy(token,"NE_OP"); return NE_OP; }
";"				{ count(); strcpy(lexeme,";"); strcpy(token,";"); return ';'; }
("{"|"<%")		{ count(); strcpy(lexeme,"{"); strcpy(token,"{"); return '{'; }
("}"|"%>")		{ count(); strcpy(lexeme,"}"); strcpy(token,"}"); return '}'; }
","				{ count(); strcpy(lexeme,","); strcpy(token,","); return ','; }
":"				{ count(); strcpy(lexeme,":"); strcpy(token,":"); return ':'; }
"="				{ count(); strcpy(lexeme,"="); strcpy(token,"="); return '='; }
"("				{ count(); strcpy(lexeme,"("); strcpy(token,"("); return '('; }
")"				{ count(); strcpy(lexeme,")"); strcpy(token,")"); return ')'; }
("["|"<:")		{ count(); strcpy(lexeme,"["); strcpy(token,"["); return '['; }
("]"|":>")		{ count(); strcpy(lexeme,"]"); strcpy(token,"]"); return ']'; }
"."				{ count(); strcpy(lexeme,"."); strcpy(token,"."); return '.'; }
"&"				{ count(); strcpy(lexeme,"&"); strcpy(token,"&"); return '&'; }
"!"				{ count(); strcpy(lexeme,"!"); strcpy(token,"!"); return '!'; }
"~"				{ count(); strcpy(lexeme,"~"); strcpy(token,"~"); return '~'; }
"-"				{ count(); strcpy(lexeme,"-"); strcpy(token,"-"); return '-'; }
"+"				{ count(); strcpy(lexeme,"+"); strcpy(token,"+"); return '+'; }
"*"				{ count(); strcpy(lexeme,"*"); strcpy(token,"*"); return '*'; }
"/"				{ count(); strcpy(lexeme,"/"); strcpy(token,"/"); return '/'; }
"%"				{ count(); strcpy(lexeme,"%"); strcpy(token,"%"); return '%'; }
"<"				{ count(); strcpy(lexeme,"<"); strcpy(token,"<"); return '<'; }
">"				{ count(); strcpy(lexeme,">"); strcpy(token,">"); return '>'; }
"^"				{ count(); strcpy(lexeme,"^"); strcpy(token,"^"); return '^'; }
"|"				{ count(); strcpy(lexeme,"|"); strcpy(token,"|"); return '|'; }
"?"				{ count(); strcpy(lexeme,"?"); strcpy(token,"?"); return '?'; }

[ \t\v\n\f]		{ count(); }
.			{ yyerror("Invalid Character Found");/* ignore bad characters */ }




%%

void count(){

	for (int i = 0; yytext[i] != '\0'; i++){
		if (yytext[i] == '\n')
			col = 1;
		else if (yytext[i] == '\t')
			col += 4 - (col % 4);
		else
			col++;
    }
}
/*
void print(char *token, char * lexeme, int column_no){
    //to print the entries of table
    //first argument is token, 2nd is the lexeme

//     printf("%-20s %-20s %-10d %-10d\n", token, lexeme, yylineno, column_no);
// }

// void yyerror(char *s){
// 	printf("Line:%d Col:%d ERROR: %s\n",yylineno,col,s);
// 	exit(1);
// }

void yyerror(char *s){
	printf("Line:%d Col:%d ERROR: %s\n",yylineno,col,s);
	exit(1);
}
*/
// int main(int argc, char *argv[]){
// 	if(argc!=2){
//         printf("Please specify an existing filename\n");	
// 		return 1;
// 	}
//     yyin = fopen(argv[1], "r");
//     printf("%-20s %-20s %-10s %-10s\n", "Token", "Lexeme", "Line#", "Column#");
// 	int val = 0;
//     while( (val = yylex()) > 0){
// 		print(token, lexeme, col-strlen(lexeme));
//     }
// 	fclose(yyin);
// 	return 0;
// }
