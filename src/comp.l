%{
#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include "functions.h"
#include "y.tab.h"
void yyerror (char *s,...);

extern int errorCount;
extern string nameStruct;
int yylex();
void count();
void print();

void int_extract();
void real_extract(char *c);

static int col=1;
%}
%option yylineno

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*


%%

"/*"([^*]|\*+[^*/])*\*+"/"	{/*a C comment*/}
"//"(.)*(\n)			{/*a C comment*/}

"auto"			{ count(); yylval.str = strdup(yytext); return AUTO; }
"break"			{ count(); yylval.str = strdup(yytext); return BREAK; }
"case"			{ count(); yylval.str = strdup(yytext); return CASE; }
"char"			{ count(); yylval.str = strdup(yytext); return CHAR; }
"const"			{ count(); yylval.str = strdup(yytext); return CONST; }
"continue"		{ count(); yylval.str = strdup(yytext); return CONTINUE; }
"default"		{ count(); yylval.str = strdup(yytext); return DEFAULT; }
"do"			{ count(); yylval.str = strdup(yytext); return DO; }
"double"		{ count(); yylval.str = strdup(yytext); return DOUBLE; }
"else"			{ count(); yylval.str = strdup(yytext); return ELSE; }
"enum"			{ count(); yylval.str = strdup(yytext); return ENUM; }
"extern"		{ count(); yylval.str = strdup(yytext); return EXTERN; }
"float"			{ count(); yylval.str = strdup(yytext); return FLOAT; }
"for"			{ count(); yylval.str = strdup(yytext); return FOR; }
"goto"			{ count(); yylval.str = strdup(yytext); return GOTO; }
"if"			{ count(); yylval.str = strdup(yytext); return IF; }
"int"			{ count(); yylval.str = strdup(yytext); return INT; }
"long"			{ count(); yylval.str = strdup(yytext); return LONG; }
"register"		{ count(); yylval.str = strdup(yytext); return REGISTER; }
"return"		{ count(); yylval.str = strdup(yytext); return RETURN; }
"short"			{ count(); yylval.str = strdup(yytext); return SHORT; }
"signed"		{ count(); yylval.str = strdup(yytext); return SIGNED; }
"sizeof"		{ count(); yylval.str = strdup(yytext); return SIZEOF; }
"static"		{ count(); yylval.str = strdup(yytext); return STATIC; }
"struct"		{ count(); yylval.str = strdup(yytext); return STRUCT; }
"switch"		{ count(); yylval.str = strdup(yytext); return SWITCH; }
"typedef"		{ count(); yylval.str = strdup(yytext); return TYPEDEF; }
"union"			{ count(); yylval.str = strdup(yytext); return UNION; }
"unsigned"		{ count(); yylval.str = strdup(yytext); return UNSIGNED; }
"void"			{ count(); yylval.str = strdup(yytext); return VOID; }
"volatile"		{ count(); yylval.str = strdup(yytext); return VOLATILE; }
"while"			{ count(); yylval.str = strdup(yytext); return WHILE; }

{L}({L}|{D})*		{ count(); yylval.str = strdup(yytext);nameStruct=convert_to_string(yylval.str); return IDENTIFIER; }

0[xX]{H}+{IS}?		{sscanf(yytext+2,"%llx",&yylval.num->integer_value); count(); yylval.num->str = strdup(yytext); int_extract(); return CONSTANT; }
0{D}+{IS}?		{ sscanf(yytext,"%lld",&yylval.num->integer_value);count(); yylval.num->str = strdup(yytext); int_extract();return CONSTANT; }
{D}+{IS}?		{ sscanf(yytext,"%lld",&yylval.num->integer_value);count(); yylval.num->str = strdup(yytext); int_extract();return CONSTANT; }
L?'(\\.|[^\\'])+'	{ count(); yylval.num->str = strdup(yytext); int_extract();return CONSTANT; }

{D}+{E}{FS}?		{ count(); yylval.num->str = strdup(yytext); char *c=strdup(yytext); real_extract(c);return CONSTANT; }
{D}*"."{D}+({E})?{FS}?	{ count(); yylval.num->str = strdup(yytext);char *c=strdup(yytext); real_extract(c);return CONSTANT; }
{D}+"."{D}*({E})?{FS}?	{ count(); yylval.num->str = strdup(yytext); char *c=strdup(yytext); real_extract(c);return CONSTANT; }

L?\"(\\.|[^\\"])*\"	{ count(); yylval.str = strdup(yytext); return STRING_LITERAL; }

"..."			{ count(); yylval.str = strdup(yytext); return ELLIPSIS; }
">>="			{ count(); yylval.str = strdup(yytext); return RIGHT_ASSIGN; }
"<<="			{ count(); yylval.str = strdup(yytext); return LEFT_ASSIGN; }
"+="			{ count(); yylval.str = strdup(yytext); return ADD_ASSIGN; }
"-="			{ count(); yylval.str = strdup(yytext); return SUB_ASSIGN; }
"*="			{ count(); yylval.str = strdup(yytext); return MUL_ASSIGN; }
"/="			{ count(); yylval.str = strdup(yytext); return DIV_ASSIGN; }
"%="			{ count(); yylval.str = strdup(yytext); return MOD_ASSIGN; }
"&="			{ count(); yylval.str = strdup(yytext); return AND_ASSIGN; }
"^="			{ count(); yylval.str = strdup(yytext); return XOR_ASSIGN; }
"|="			{ count(); yylval.str = strdup(yytext); return OR_ASSIGN; }
">>"			{ count(); yylval.str = strdup(yytext); return RIGHT_OP; }
"<<"			{ count(); yylval.str = strdup(yytext); return LEFT_OP; }
"++"			{ count(); yylval.str = strdup(yytext); return INC_OP; }
"--"			{ count(); yylval.str = strdup(yytext); return DEC_OP; }
"->"			{ count(); yylval.str = strdup(yytext); return PTR_OP; }
"&&"			{ count(); yylval.str = strdup(yytext); return AND_OP; }
"||"			{ count(); yylval.str = strdup(yytext); return OR_OP; }
"<="			{ count(); yylval.str = strdup(yytext); return LE_OP; }
">="			{ count(); yylval.str = strdup(yytext); return GE_OP; }
"=="			{ count(); yylval.str = strdup(yytext); return EQ_OP; }
"!="			{ count(); yylval.str = strdup(yytext); return NE_OP; }
";"			{ count(); yylval.str = strdup(yytext); return ';'; }
("{"|"<%")		{ count(); yylval.str = strdup(yytext); return '{'; }
("}"|"%>")		{ count(); yylval.str = strdup(yytext); return '}'; }
","			{ count(); yylval.str = strdup(yytext); return ','; }
":"			{ count(); yylval.str = strdup(yytext); return ':'; }
"="			{ count(); yylval.str = strdup(yytext); return '='; }
"("			{ count(); yylval.str = strdup(yytext); return '('; }
")"			{ count(); yylval.str = strdup(yytext); return ')'; }
("["|"<:")		{ count(); yylval.str = strdup(yytext); return '['; }
("]"|":>")		{ count(); yylval.str = strdup(yytext); return ']'; }
"."			{ count(); yylval.str = strdup(yytext); return '.'; }
"&"			{ count(); yylval.str = strdup(yytext); return '&'; }
"!"			{ count(); yylval.str = strdup(yytext); return '!'; }
"~"			{ count(); yylval.str = strdup(yytext); return '~'; }
"-"			{ count(); yylval.str = strdup(yytext); return '-'; }
"+"			{ count(); yylval.str = strdup(yytext); return '+'; }
"*"			{ count(); yylval.str = strdup(yytext); return '*'; }
"/"			{ count(); yylval.str = strdup(yytext); return '/'; }
"%"			{ count(); yylval.str = strdup(yytext); return '%'; }
"<"			{ count(); yylval.str = strdup(yytext); return '<'; }
">"			{ count(); yylval.str = strdup(yytext); return '>'; }
"^"			{ count(); yylval.str = strdup(yytext); return '^'; }
"|"			{ count(); yylval.str = strdup(yytext); return '|'; }
"?"			{ count(); yylval.str = strdup(yytext); return '?'; }

[ \t\v\n\f]		{ count(); }
.			{ yyerror("Invalid Character Found");/* ignore bad characters */ }




%%

int yywrap(void){
	return 1;
}

void int_extract(){
   yylval.num->is_integer = 1;
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
void real_extract(char *c){
   int n=yyleng-1;
   string str=convert_to_string(c);
   yylval.num->real_value=stof(str);
   yylval.num->str=strdup(c);
   yylval.num->is_integer=0;
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
void yyerror(char *s,...){
	va_list args;
  	char buffer[1024];
        
        if(s[0]=='E'){
                errorCount++;
        }

        va_start(args,s);
	vsnprintf(buffer,1023,s,args);
	va_end(args);

	fprintf(stderr,"Line:%d Col:%d:: %s\n",yylineno,col,buffer);
	
        if(errorCount>=20){
                fprintf(stderr,"Too many errors. EXITTING BYE\n");
                exit(1);
        }
        //printf("Line:%d Col:%d %s\n",yylineno,col,s);
	// exit(1);
}


