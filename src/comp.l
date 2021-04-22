%{
#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include "functions.h"
#include "y.tab.h"
void yyerror (char *s,...);

int yylex();
void count();
void print();

void int_extract();
void real_extract();

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

"auto"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"AUTO"); return AUTO; }
"break"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"BREAK"); return BREAK; }
"case"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"CASE"); return CASE; }
"char"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"CHAR"); return CHAR; }
"const"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"CONST"); return CONST; }
"continue"		{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"CONTINUE"); return CONTINUE; }
"default"		{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"DEFAULT"); return DEFAULT; }
"do"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"DO"); return DO; }
"double"		{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"DOUBLE"); return DOUBLE; }
"else"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"ELSE"); return ELSE; }
"enum"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"ENUM"); return ENUM; }
"extern"		{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"EXTERN"); return EXTERN; }
"float"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"FLOAT"); return FLOAT; }
"for"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"FOR"); return FOR; }
"goto"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"GOTO"); return GOTO; }
"if"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"IF"); return IF; }
"int"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"INT"); return INT; }
"long"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"LONG"); return LONG; }
"register"		{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"REGISTER"); return REGISTER; }
"return"		{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"RETURN"); return RETURN; }
"short"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"SHORT"); return SHORT; }
"signed"		{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"SIGNED"); return SIGNED; }
"sizeof"		{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"SIZEOF"); return SIZEOF; }
"static"		{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"STATIC"); return STATIC; }
"struct"		{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"STRUCT"); return STRUCT; }
"switch"		{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"SWITCH"); return SWITCH; }
"typedef"		{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"TYPEDEF"); return TYPEDEF; }
"union"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"UNION"); return UNION; }
"unsigned"		{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"UNSIGNED"); return UNSIGNED; }
"void"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"VOID"); return VOID; }
"volatile"		{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"VOLATILE"); return VOLATILE; }
"while"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"WHILE"); return WHILE; }

{L}({L}|{D})*		{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"IDENTIFIER"); return IDENTIFIER; }

0[xX]{H}+{IS}?		{sscanf(yytext+2,"%llx",&yylval.num->integer_value); count(); yylval.num->str = strdup(yytext); strcpy(lexeme,yytext);strcpy(token,"CONSTANT");int_extract(); return CONSTANT; }
0{D}+{IS}?		{ sscanf(yytext,"%lld",&yylval.num->integer_value);count(); yylval.num->str = strdup(yytext); strcpy(lexeme,yytext);strcpy(token,"CONSTANT"); int_extract();return CONSTANT; }
{D}+{IS}?		{ sscanf(yytext,"%lld",&yylval.num->integer_value);count(); yylval.num->str = strdup(yytext); strcpy(lexeme,yytext);strcpy(token,"CONSTANT"); int_extract();return CONSTANT; }
L?'(\\.|[^\\'])+'	{ count(); yylval.num->str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"CONSTANT");int_extract();return CONSTANT; }

{D}+{E}{FS}?		{sscanf(yytext,"%Lf",&yylval.num->real_value); count(); yylval.num->str = strdup(yytext); strcpy(lexeme,yytext);strcpy(token,"CONSTANT"); real_extract();return CONSTANT; }
{D}*"."{D}+({E})?{FS}?	{ sscanf(yytext,"%Lf",&yylval.num->real_value);count(); yylval.num->str = strdup(yytext); strcpy(lexeme,yytext);strcpy(token,"CONSTANT"); real_extract();return CONSTANT; }
{D}+"."{D}*({E})?{FS}?	{ sscanf(yytext,"%Lf",&yylval.num->real_value);count(); yylval.num->str = strdup(yytext); strcpy(lexeme,yytext);strcpy(token,"CONSTANT"); real_extract();return CONSTANT; }

L?\"(\\.|[^\\"])*\"	{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"STRING_LITERAL"); return STRING_LITERAL; }

"..."			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"ELLIPSIS"); return ELLIPSIS; }
">>="			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"RIGHT_ASSIGN"); return RIGHT_ASSIGN; }
"<<="			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"LEFT_ASSIGN"); return LEFT_ASSIGN; }
"+="			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"ADD_ASSIGN"); return ADD_ASSIGN; }
"-="			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"SUB_ASSIGN"); return SUB_ASSIGN; }
"*="			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"MUL_ASSIGN"); return MUL_ASSIGN; }
"/="			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"DIV_ASSIGN"); return DIV_ASSIGN; }
"%="			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"MOD_ASSIGN"); return MOD_ASSIGN; }
"&="			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"AND_ASSIGN"); return AND_ASSIGN; }
"^="			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"XOR_ASSIGN"); return XOR_ASSIGN; }
"|="			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"OR_ASSIGN"); return OR_ASSIGN; }
">>"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"RIGHT_OP"); return RIGHT_OP; }
"<<"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"LEFT_OP"); return LEFT_OP; }
"++"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"INC_OP"); return INC_OP; }
"--"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"DEC_OP"); return DEC_OP; }
"->"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"PTR_OP"); return PTR_OP; }
"&&"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"AND_OP"); return AND_OP; }
"||"			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"OR_OP"); return OR_OP; }
"<="			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"LE_OP"); return LE_OP; }
">="			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"GE_OP"); return GE_OP; }
"=="			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"EQ_OP"); return EQ_OP; }
"!="			{ count(); yylval.str = strdup(yytext); strcpy(lexeme,yytext); strcpy(token,"NE_OP"); return NE_OP; }
";"				{ count(); yylval.str = strdup(yytext); strcpy(lexeme,";"); strcpy(token,";"); return ';'; }
("{"|"<%")		{ count(); yylval.str = strdup(yytext); strcpy(lexeme,"{"); strcpy(token,"{"); return '{'; }
("}"|"%>")		{ count(); yylval.str = strdup(yytext); strcpy(lexeme,"}"); strcpy(token,"}"); return '}'; }
","				{ count(); yylval.str = strdup(yytext); strcpy(lexeme,","); strcpy(token,","); return ','; }
":"				{ count(); yylval.str = strdup(yytext); strcpy(lexeme,":"); strcpy(token,":"); return ':'; }
"="				{ count(); yylval.str = strdup(yytext); strcpy(lexeme,"="); strcpy(token,"="); return '='; }
"("				{ count(); yylval.str = strdup(yytext); strcpy(lexeme,"("); strcpy(token,"("); return '('; }
")"				{ count(); yylval.str = strdup(yytext); strcpy(lexeme,")"); strcpy(token,")"); return ')'; }
("["|"<:")		{ count(); yylval.str = strdup(yytext); strcpy(lexeme,"["); strcpy(token,"["); return '['; }
("]"|":>")		{ count(); yylval.str = strdup(yytext); strcpy(lexeme,"]"); strcpy(token,"]"); return ']'; }
"."				{ count(); yylval.str = strdup(yytext); strcpy(lexeme,"."); strcpy(token,"."); return '.'; }
"&"				{ count(); yylval.str = strdup(yytext); strcpy(lexeme,"&"); strcpy(token,"&"); return '&'; }
"!"				{ count(); yylval.str = strdup(yytext); strcpy(lexeme,"!"); strcpy(token,"!"); return '!'; }
"~"				{ count(); yylval.str = strdup(yytext); strcpy(lexeme,"~"); strcpy(token,"~"); return '~'; }
"-"				{ count(); yylval.str = strdup(yytext); strcpy(lexeme,"-"); strcpy(token,"-"); return '-'; }
"+"				{ count(); yylval.str = strdup(yytext); strcpy(lexeme,"+"); strcpy(token,"+"); return '+'; }
"*"				{ count(); yylval.str = strdup(yytext); strcpy(lexeme,"*"); strcpy(token,"*"); return '*'; }
"/"				{ count(); yylval.str = strdup(yytext); strcpy(lexeme,"/"); strcpy(token,"/"); return '/'; }
"%"				{ count(); yylval.str = strdup(yytext); strcpy(lexeme,"%"); strcpy(token,"%"); return '%'; }
"<"				{ count(); yylval.str = strdup(yytext); strcpy(lexeme,"<"); strcpy(token,"<"); return '<'; }
">"				{ count(); yylval.str = strdup(yytext); strcpy(lexeme,">"); strcpy(token,">"); return '>'; }
"^"				{ count(); yylval.str = strdup(yytext); strcpy(lexeme,"^"); strcpy(token,"^"); return '^'; }
"|"				{ count(); yylval.str = strdup(yytext); strcpy(lexeme,"|"); strcpy(token,"|"); return '|'; }
"?"				{ count(); yylval.str = strdup(yytext); strcpy(lexeme,"?"); strcpy(token,"?"); return '?'; }

[ \t\v\n\f]		{ count(); }
.			{ yyerror("Invalid Character Found");/* ignore bad characters */ }




%%

int yywrap(void){
	return 1;
}

void int_extract(){
   yylval.num->is_integer = 1;
   //cout<<"int vlaue:"<<yylval.num->integer_value<<yylval.num->str<<"\n";
   yylval.num->num_type = yylval.num->unsigned_flag=1;
   for(int i=yyleng-1;;i--){
       if(yytext[i]=='u'||yytext[i]=='U')
                yylval.num->unsigned_flag = 1;
       else if (yytext[i]=='l'||yytext[i] == 'L')
                yylval.num->num_type++;
       else
             break;

   }


}
void real_extract(){
   int n=yyleng-1;
   yylval.num->is_integer=0;
   //cout<<yylval.num->str<<"\n";
   //cout<<"rael vlaue:"<<yylval.num->real_value<<" "<<yylval.num->str<<"\n";
    if(yytext[n]=='f'||yytext[n]=='F')
            yylval.num->num_type = N_FLOAT;
    else if (yytext[n]=='l'||yytext[n] == 'L')
            yylval.num->num_type = N_LONGDOUBLE;
    else
            yylval.num->num_type =N_DOUBLE;

}
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

    printf("%-20s %-20s %-10d %-10d\n", token, lexeme, yylineno, column_no);
}
*/
void yyerror(char *s,...){
	va_list args;
  	char buffer[1024];

	va_start(args,s);
	vsnprintf(buffer,1023,s,args);
	va_end(args);

	fprintf(stderr,"Line:%d Col:%d:: %s\n",yylineno,col,buffer);
	//printf("Line:%d Col:%d %s\n",yylineno,col,s);
	// exit(1);
}
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

