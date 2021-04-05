%{
#include "functions.h"

#include <iostream>
#include <cstring>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdarg.h>
using namespace std;

int yylex(void);
void yyerror(char *s,...);
%}

%union {
  int number;     /*integer value*/
  char* str;
  struct node *ptr;     /*node pointer */
};

%token <str> CHAR CONST CASE CONTINUE DEFAULT DO DOUBLE
%token <str> ELSE ENUM EXTERN FLOAT FOR IF INLINE INT LONG
%nonassoc IFX
%nonassoc ELSE
%token <str> REGISTER RESTRICT RETURN SHORT SIGNED STATIC STRUCT SWITCH TYPEDEF UNION
%token <str> UNSIGNED VOID VOLATILE WHILE ALIGNAS ALIGNOF ATOMIC BOOL COMPLEX
%token <str> GENERIC IMAGINARY NORETURN STATIC_ASSERT THREAD_LOCAL FUNC_NAME
%token <str> AUTO BREAK GOTO TYPEDEF_NAME IDENTIFIER CONSTANT ENUMERATION_CONSTANT
%token <str> STRING_LITERAL
//%token <num> I_CONSTANT F_CONSTANT
%left <str> PTR_OP
%token <str> INC_OP DEC_OP
%token <str> LEFT_OP RIGHT_OP
%left <str> LE_OP GE_OP EQ_OP NE_OP
%left <str> AND_OP OR_OP
%right <str> MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%right <str> SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%right <str> XOR_ASSIGN OR_ASSIGN TYPE_NAME
%token <str> ELLIPSIS
%type <str> assignment_operator

%start translation_unit

%left <str> ',' '^' '|' ';' '{' '}' '[' ']' '(' ')' '+' '-' '%' '/' '*' '.' '>' '<' SIZEOF
%right <str> '&' '=' '!' '~' ':' '?'

%type <ptr> multiplicative_expression additive_expression cast_expression primary_expression expression assignment_expression postfix_expression unary_expression shift_expression relational_expression equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_or_expression logical_and_expression conditional_expression constant_expression
%type <ptr> type_name argument_expression_list initializer_list
%type <ptr> unary_operator
%type <ptr> declaration declaration_specifiers
%type <ptr> init_declarator_list storage_class_specifier type_specifier type_qualifier
%type <ptr> init_declarator declarator initializer struct_or_union_specifier enum_specifier struct_or_union struct_declaration_list
%type <ptr> struct_declaration specifier_qualifier_list struct_declarator_list struct_declarator enumerator_list enumerator pointer
%type <ptr> direct_declarator type_qualifier_list parameter_type_list identifier_list parameter_list parameter_declaration
%type <ptr> abstract_declarator direct_abstract_declarator labeled_statement compound_statement expression_statement declaration_list
%type <ptr> selection_statement iteration_statement jump_statement external_declaration translation_unit function_definition statement statement_list

%%

primary_expression
	: IDENTIFIER			{$$ = term_symb($1);
								char *a=primaryExpr($1);
								if(a){
									string as(a);
									$$->isInit=lookup($1)->is_init;
									$$->isInit = lookup($1)->is_init;
                                    $$->nodeType=as;
                                    string key($1);
                                    $$->exprType = 3;
                                    $$->nodeKey = key;
								}
								else{
									yyerror("Error : %s not declared",$1);
									$$->nodeType=string("");
								}
							}
	| CONSTANT				{$$ = term_symb($1);
								//TO ADD SOME THING REMEBBER************************
							} 
	| STRING_LITERAL		{$$ = term_symb($1);
								$$->nodeType=string("char*");
								$$->isInit=1;
							}
	| '(' expression ')'	{$$ = $2;}
	;

postfix_expression
	: primary_expression									{$$ = $1;}
	| postfix_expression '[' expression ']'					{$$ = non_term_symb("[ ]", NULL, $1, $3);
																if($1->isInit==1&&$3->isInit==1) $$->isInit=1;
																char *s=postfixExpr($1->nodeType,1);
																if(s&&isInt($3->nodeType)){
																	string as(s);
																	$$->nodeType=as;
																}
																else if(!isInt($3->nodeType)){
																	yyerror("Error : array index not a int");
																}
																else{
																	yyerror("Error : array indexed with more indeces than its dimension");
																}
															}
	| postfix_expression '(' ')'							{$$ = $1;
																$$->isInit=1;
																char* s = postfixExpr($1->nodeType, 2);
																if(s){
																	string as(s);
																	$$->nodeType =as;
																		if($1->exprType==3){
																			string funcArgs = funcArgList($1->nodeKey);
																			if(!(funcArgs==string(""))) {
																				yyerror(Error : \'%s\' function call requires arguments to be passed \n     \'%s %s\( %s \)\'",($1->nodeKey).c_str(),($$->nodeType).c_str(),($1->nodeKey).c_str(),funcArgs.c_str());
																			}
																		}
																}
																else {
																	yyerror("Error : Invalid Function call");
																}
																	currArguments=string("");

															}
															}
	| postfix_expression '(' argument_expression_list ')'	{$$ = non_term_symb("postfix_expression", NULL, $1, $3);
																if($3->isInit==1) $$->isInit=1;
																char* s = postfixExpr($1->nodeType, 3);
																if(s){
																	string as(s);
																	$$->nodeType =as;
																	if($1->exprType==3){
																		string funcArgs = funcArgList($1->nodeKey);
																		char* a =new char();
																		string temp1 = currArguments;
																		string temp2 = funcArgs;
																		string typeA,typeB;
																		string delim = string(",");
																		unsigned f1=1;
																		unsigned f2=1;
																		int argNo = 0;
																		while(f1!=-1 && f2!=-1){
																			f1 = temp1.find_first_of(delim);
																			f2 = temp2.find_first_of(delim);
																			argNo++;
																			if(f1==-1) typeA = temp1; else{ typeA = temp1.substr(0,f1); temp1 = temp1.substr(f1+1);}
																			if(f2==-1) typeB = temp2 ; else{ typeB = temp2.substr(0,f2); temp2 = temp2.substr(f2+1); }
																			if(typeB==string("...")) break;
																			a = validAssign(typeA,typeB);
																			if(a){
																				if(!strcmp(a,"warning")) { yyerror("Warning : Passing argumnet %d of \'%s\' from incompatible pointer type.\n Note : expected \'%s\' but argument is of type \'%s\'\n     \'%s %s\( %s \)\'",argNo,($1->nodeKey).c_str(),typeB.c_str(),typeA.c_str(),($$->nodeType).c_str(),($1->nodeKey).c_str(),funcArgs.c_str()); }
																			}
																			else{
																				yyerror("Error : Incompatible type for argument %d of \'%s\' .\n Note : expected \'%s\' but argument is of type \'%s\'\n     \'%s %s\( %s \)\'",argNo,($1->nodeKey).c_str(),typeB.c_str(),typeA.c_str(),($$->nodeType).c_str(),($1->nodeKey).c_str(),funcArgs.c_str());
																			}
																			if((f1!=-1)&&(f2!=-1)){
																				continue;
																			}else if(f2!=-1){
																				if(!(temp2==string("..."))) yyerror("Error : Too few arguments for the function \'%s\'\n    \'%s %s\( %s \)\'",($1->nodeKey).c_str(),($$->nodeType).c_str(),($1->nodeKey).c_str(),funcArgs.c_str());
																				break;
																			}else if(f1!=-1){
																				yyerror("Error : Too many arguments for the function \'%s\'\n    \'%s %s\( %s \)\'",($1->nodeKey).c_str(),($$->nodeType).c_str(),($1->nodeKey).c_str(),funcArgs.c_str());
																				break;
																			}else{ break; }
																		}
																			
																	}

																}
																else {
																	yyerror("Error : Invalid Function call");
																}
																	currArguments=string("");
															}
	| postfix_expression '.' IDENTIFIER						{$$ = non_term_symb(" . ", NULL, $1, term_symb($3));
																string as($3);
																int k = structLookup($1->nodeType, as);
																if(k==1) yyerror("Error : \'.\' is an invalid operator on \'%s\'", $1->nodeKey.c_str() );
																else if(k==2) yyerror("Error : \'%s\' is not a member of struct \'%s\'", $3,$1->nodeKey.c_str() );
																else $$->nodeType = structMemberType($1->nodeType, as);
																$$->nodeKey = $1->nodeKey+ string(".") + as;
															}
	| postfix_expression PTR_OP IDENTIFIER					{$$ = non_term_symb("->", NULL, $1, term_symb($3));
																string as($3);
																string as1 = ($1->nodeType).substr(0,($1->nodeType).length()-1);
																int k = structLookup(as1, as);
																cout<<k<<endl;
																if(k==1){ yyerror("Error : \'%s\' is an invalid operator on \'%s\'", $2, $1->nodeKey.c_str() );
																}
																else if(k==2){ yyerror("Error : \'%s\' is not a member of struct \'%s\'", $3,$1->nodeKey.c_str() );
																}
																else $$->nodeType = structMemberType(as1, as);
																$$->nodeKey = $1->nodeKey+ string("->") + as;
															}
	| postfix_expression INC_OP								{$$=  non_term_symb("++", NULL,$1, NULL);
																if($1->isInit==1) $$->isInit=1;
																char* s = postfixExpr($1->nodeType, 6);
																if(s){
																	string as(s);
																	$$->nodeType =as;
																	$$->iVal = $1->iVal +1;
																}
																else {
																	yyerror("Error : Increment not defined for this type");
																}
															}
	| postfix_expression DEC_OP								{$$=  non_term_symb("--", NULL,$1, NULL);
																if($1->isInit==1) $$->isInit =1;
																char* s = postfixExpr($1->nodeType, 7);
																if(s){
																	string as(s);
																	$$->nodeType =as;
																    $$->iVal = $1->iVal -1;
																}
																else {
																	yyerror("Error : Decrement not defined for this type");
																}
															}
	;

argument_expression_list
	: assignment_expression									{$$ = $1;if($1->isInit==1)$$->isInit = 1; currArguments = $1->nodeType;}
	| argument_expression_list ',' assignment_expression	{$$ = non_term_symb($2,NULL,$1, $3);
																char* a =  argumentExpr($1->nodeType, $3->nodeType, 2);
																string as(a);
																$$->nodeType = as;
																if($1->isInit == 1 && $3->isInit==1) $$->isInit=1;
																currArguments = currArguments +string(",")+ $3->nodeType;
															}
	;

unary_expression
	: postfix_expression				{$$ = $1;}
	| INC_OP unary_expression			{$$ = non_term_symb("++", NULL, NULL, $2);
											if($2->isInit == 1 ) $$->isInit=1;
											char* s = postfixExpr($2->nodeType, 6);
											if(s){
												string as(s);
												$$->nodeType =as;
												$$->iVal = $2->iVal +1;
											}
											else {
												yyerror("Error : Increment not defined for this type");
											}
										}
	| DEC_OP unary_expression			{$$ = non_term_symb("--", NULL, NULL, $2);
											$$->iVal =$2->iVal -1;
											if($2->isInit == 1 ) $$->isInit=1;
											char* s = postfixExpr($2->nodeType, 7);
											if(s){
												string as(s);
												$$->nodeType =as;
											}
											else {
												yyerror("Error : Decrement not defined for this type");
	  										}			
										}
	| unary_operator cast_expression	{$$ = non_term_symb("unary_expression", NULL, $1, $2);
											$$->iVal = $2->iVal;
											if( $2->isInit==1) $$->isInit=1;
											char* a= unaryExpr($1->name, $2->nodeType, 1);
											if(a){
												string as(a);
												$$->nodeType= as;
											}
											else{
												yyerror("Error : Type inconsistent with operator %s", $1->name.c_str());
											}
										}
	| SIZEOF unary_expression			{$$ = non_term_symb($1, NULL, NULL, $2);$$->nodeType = string("int");$$->isInit=1;}
	| SIZEOF '(' type_name ')'			{$$ = non_term_symb($1, NULL, NULL, $3);$$->nodeType = string("int");$$->isInit=1;}
	;

unary_operator
	: '&'	{$$ = term_symb("&");}
	| '*'	{$$ = term_symb("*");}
	| '+'	{$$ = term_symb("+");}
	| '-'	{$$ = term_symb("-");}
	| '~'	{$$ = term_symb("~");}
	| '!'	{$$ = term_symb("!");}
	;

cast_expression
	: unary_expression					{$$ = $1;}
	| '(' type_name ')' cast_expression	{$$ = non_term_symb("cast_expression", NULL, $2, $4);
												$$->nodeType = $2->nodeType;
                        						if($4->isInit==1) $$->isInit=1;
										}
	;

multiplicative_expression
	: cast_expression								{$$ = $1;}
	| multiplicative_expression '*' cast_expression	{$$ = non_term_symb("*", NULL, $1, $3);
														char* a=multilplicativeExpr($1->nodeType, $3->nodeType, '*');
														if(a){
															int k;
															if(strcmp(a,"int")==0){
																//$$=nonTerminal("*int",NULL,$1,$3);
																$$->nodeType = string("long long");
															}
															else if (strcmp(a, "float")==0){
																//$$=nonTerminal("*float",NULL,$1,$3);
																$$->nodeType = string("long double");
																
															}
														}
														else{
															//$$=nonTerminal("*",NULL,$1,$3);
															yyerror("Error : Incompatible type for * operator");
														}
														if($1->isInit==1 && $3->isInit==1) $$->isInit=1;
														}
													}
	| multiplicative_expression '/' cast_expression	{$$ = non_term_symb("/", NULL, $1, $3);
														if ($3->iVal != 0)
														$$->iVal = $1->iVal/ $3->iVal;
														char* a=multilplicativeExpr($1->nodeType, $3->nodeType, '/');
														if(a){int k;
															if(!strcmp(a,"int")){
																//$$=nonTerminal("/int",NULL,$1,$3);
																$$->nodeType = string("long long");
															
															}
															else if (!strcmp(a,"float")){
																//$$=nonTerminal("/float",NULL,$1,$3);
																$$->nodeType = string("long double");
															
															}
														}
														else{
															//$$=nonTerminal("/",NULL,$1,$3);
															yyerror("Error : Incompatible type for / operator");
														}
														if($1->isInit==1 && $3->isInit==1) $$->isInit=1;
													}
	| multiplicative_expression '%' cast_expression	{$$ = non_term_symb("%", NULL, $1, $3);
														if($3->iVal != 0) $$->iVal = $1->iVal % $3->iVal;
														char* a=multilplicativeExpr($1->nodeType, $3->nodeType, '/');
														if(!strcmp(a,"int")){
															$$->nodeType= string("long long");
																
														}
														else {
															yyerror("Error : Incompatible type for % operator");
														}
														if($1->isInit==1 && $3->isInit==1) $$->isInit=1;
														
													}
	;

additive_expression
	: multiplicative_expression							{$$ = $1;}
	| additive_expression '+' multiplicative_expression	{$$ = non_term_symb("+", NULL, $1, $3);
															$$->iVal = $1->iVal + $3->iVal;
															char *a = additiveExpr($1->nodeType,$3->nodeType,'+');
															char *q=new char();
															string p;
															if(a){
																string as(a);
																p = string("+")+as;
																strcpy(q,p.c_str());
															}
															else q = "+";
															//$$=nonTerminal(q,NULL,$1,$3);
															if(a){ 
																string as(a);
																if(!strcmp(a,"int")) $$->nodeType=string("long long");
																else if(!strcmp(a,"real")) $$->nodeType=string("long double");
																else $$->nodeType=as; // for imaginary and complex returns
											
															}
															else {
																yyerror("Error : Incompatible type for + operator");
															}
															if($1->isInit==1 && $3->isInit==1) $$->isInit=1;
														}
	| additive_expression '-' multiplicative_expression	{$$ = non_term_symb("-", NULL, $1, $3);
															$$->iVal = $1->iVal - $3->iVal;
															char *a = additiveExpr($1->nodeType,$3->nodeType,'-');
															char *q = new char();
															string p;
															if(a){ string as(a);
																p =string("-")+as;
																strcpy(q,p.c_str());
															}
															//$$=nonTerminal(q,NULL,$1,$3);
															if(a){ 
																string as(a);
																if(!strcmp(a,"int")) $$->nodeType=string("long long");
																else if(!strcmp(a,"real")) $$->nodeType=string("long double");
																else $$->nodeType=as;   // for imaginary and complex returns
																
															}
															else {
																yyerror("Error : Incompatible type for - operator");
															}
															if($1->isInit==1 && $3->isInit==1) $$->isInit=1;
														}
	;

shift_expression
	: additive_expression							{$$ = $1;}
	| shift_expression LEFT_OP additive_expression	{$$ = non_term_symb_2($2, $1, NULL, $3);
														char* a = shiftExpr($1->nodeType,$3->nodeType);                        
														if(a){
                            								$$->nodeType = $1->nodeType;
	
														}
														else{
															yyerror("Error : Invalid operands to binary <<");
														}
														if($1->isInit==1 && $3->isInit==1) $$->isInit=1;
																						

													}
	| shift_expression RIGHT_OP additive_expression	{$$ = non_term_symb_2($2, $1, NULL, $3);
														$$ = nonTerminal2(">>", $1, NULL, $3);
														char* a = shiftExpr($1->nodeType,$3->nodeType);
														if(a){
															$$->nodeType = $1->nodeType;
															
														}
														else{
															yyerror("Error : Invalid operands to binary >>");
														}

														if($1->isInit==1 && $3->isInit==1) $$->isInit=1;
													}
	;

relational_expression
	: shift_expression								{$$ = $1;}
	| relational_expression '<' shift_expression	{$$ = non_term_symb("<", NULL, $1, $3);
														char* a=relationalExpr($1->nodeType,$3->nodeType,"<");
														if(a) { 
															if(!strcmp(a,"bool")) $$->nodeType = string("bool");
															else if(!strcmp(a,"Bool")){
																$$->nodeType = string("bool");
																yyerror("Warning : comparison between pointer and integer");
															}
															
															else {
																yyerror("Error : invalid operands to binary <");
															}
															if($1->isInit==1 && $3->isInit==3) $$->isInit=1;
													}
	| relational_expression '>' shift_expression	{$$ = non_term_symb(">", NULL, $1, $3);
														char* a=relationalExpr($1->nodeType,$3->nodeType,">");
														if(a){ 
															if(!strcmp(a,"bool")) $$->nodeType = string("bool");
															else if(!strcmp(a,"Bool")){
																$$->nodeType = string("bool");
																yyerror("Warning : comparison between pointer and integer");
															}
														}else {
															yyerror("Error : invalid operands to binary >");
														}
														if($1->isInit==1 && $3->isInit==3) $$->isInit=1;
													}
	| relational_expression LE_OP shift_expression	{$$ = non_term_symb($2, NULL, $1, $3);
														char* a=relationalExpr($1->nodeType,$3->nodeType,"<=");
														if(a){
															if(!strcmp(a,"bool")) $$->nodeType = string("bool");
															else if(!strcmp(a,"Bool")){
																$$->nodeType = string("bool");
																yyerror("Warning : comparison between pointer and integer");
															}
															
														}else {
															yyerror("Error : invalid operands to binary <=");
														}
														if($1->isInit==1 && $3->isInit==3) $$->isInit=1;
													}
	| relational_expression GE_OP shift_expression	{$$ = non_term_symb($2, NULL, $1, $3);
														char* a=relationalExpr($1->nodeType,$3->nodeType,">=");
														if(a){  
															if(!strcmp(a,"bool")) $$->nodeType = string("bool");
															else if(!strcmp(a,"Bool")){
																$$->nodeType = string("bool");
																yyerror("Warning : comparison between pointer and integer");
															}	
														}else {
															yyerror("Error : invalid operands to binary >=");
														}
														if($1->isInit==1 && $3->isInit==3) $$->isInit=1;
													}
	;

equality_expression
  : relational_expression   {$$ = $1;}
  | equality_expression EQ_OP relational_expression {
                                                    $$ = non_term_symb_2("==", $1, NULL, $3);
                    char* a = equalityExpr($1->nodeType,$3->nodeType);
                    if(a){ if(!strcmp(a,"true")){
                            yyerror("Warning: Comparision between pointer and Integer");
                            }
                            $$->nodeType = "bool";
                    }
                   else{ yyerror("Error:Invalid operands to binary =="); }
                 if($1->isInit==1 && $3->isInit==3) $$->isInit=1;
                                                  }
  | equality_expression NE_OP relational_expression {
                      $$ = non_term_symb_2("!=", $1, NULL, $3);
                      char* a = equalityExpr($1->nodeType,$3->nodeType);
                    if(a){   if(!strcmp(a,"true")){
                            yyerror("Warning: Comparision between pointer and Integer");
                            }
                            $$->nodeType = "bool";
                    }
                   else{ yyerror("Error:Invalid operands to binary !="); }
                 if($1->isInit==1 && $3->isInit==3) $$->isInit=1;
                                                  }
  ;

and_expression
  : equality_expression  { $$ = $1;}
  | and_expression '&' equality_expression  {
               $$ = non_term_symb("&",NULL, $1, $3);
               char* a = bitwiseExpr($1->nodeType,$3->nodeType);
               if(a){
                  if(!strcmp(a,"true")) { $$->nodeType = string("bool"); }
                  else{   $$->nodeType = string("long long");}
               }
               else {
                 yyerror("Error:Invalid operands to the binary &");
               }
                 if($1->isInit==1 && $3->isInit==3) $$->isInit=1;
          }
  ;

exclusive_or_expression
  : and_expression   { $$ = $1;}
  | exclusive_or_expression '^' and_expression  {
           $$ = non_term_symb("^", NULL, $1, $3);
               char* a = bitwiseExpr($1->nodeType,$3->nodeType);
               if(a){
                  if(!strcmp(a,"true")) { $$->nodeType = string("bool"); }
                  else{   $$->nodeType = string("long long");}
               }
               else {
                 yyerror("Error:Invalid operands to the binary ^");
               }
                 if($1->isInit==1 && $3->isInit==3) $$->isInit=1;

        }
  ;

inclusive_or_expression
	: exclusive_or_expression								{$$ = $1;}
	| inclusive_or_expression '|' exclusive_or_expression	{$$ = non_term_symb("|", NULL, $1, $3);}
	;

logical_and_expression
	: inclusive_or_expression								{$$ = $1;}
	| logical_and_expression AND_OP inclusive_or_expression	{$$ = non_term_symb_2($2, $1, NULL, $3);}
	;

logical_or_expression
	: logical_and_expression								{$$ = $1;}
	| logical_or_expression OR_OP logical_and_expression	{$$ = non_term_symb_2($2, $1, NULL, $3);}
	;

conditional_expression
	: logical_or_expression												{$$ = $1;}
	| logical_or_expression '?' expression ':' conditional_expression	{$$ = non_term_symb_2("logical_expr ? expr : conditional_expr", $1, $3, $5);}
	;

assignment_expression
	: conditional_expression										{$$ = $1;}
	| unary_expression assignment_operator assignment_expression	{$$ = non_term_symb_2($2, $1, NULL, $3);}
	;

assignment_operator
	: '='			{$$ = "=";}
	| MUL_ASSIGN	{$$ = "*=";}
	| DIV_ASSIGN	{$$ = "/=";}
	| MOD_ASSIGN	{$$ = "%=";}
	| ADD_ASSIGN	{$$ = "+=";}
	| SUB_ASSIGN	{$$ = "-=";}
	| LEFT_ASSIGN	{$$ = "<<=";}
	| RIGHT_ASSIGN	{$$ = ">>=";}
	| AND_ASSIGN	{$$ = "&=";}
	| XOR_ASSIGN	{$$ = "^=";}
	| OR_ASSIGN		{$$ = "|=";}
	;

expression
	: assignment_expression					{$$ = $1;}
	| expression ',' assignment_expression	{$$ = non_term_symb("expression ','", NULL, $1, $3);}
	;

constant_expression
	: conditional_expression	{$$ = $1;}
	;

declaration
	: declaration_specifiers ';' {$$=$1;}
	| declaration_specifiers init_declarator_list ';'	{$$ = non_term_symb("declaration", NULL, $1, $2);}
	;

declaration_specifiers
	: storage_class_specifier							{$$ = $1;}
	| storage_class_specifier declaration_specifiers	{$$ = non_term_symb("declaration_specifiers", NULL, $1, $2);}
	| type_specifier									{$$ = $1;}		
	| type_specifier declaration_specifiers				{$$ = non_term_symb("declaration_specifiers", NULL, $1, $2);}
	| type_qualifier									{$$ = $1;}
	| type_qualifier declaration_specifiers				{$$ = non_term_symb("declaration_specifiers", NULL, $1, $2);}
	;

init_declarator_list
	: init_declarator							{$$ = $1;}
	| init_declarator_list ',' init_declarator	{$$ = non_term_symb("init_declaration_list", NULL, $1, $3);}
	;

init_declarator
	: declarator					{$$ = $1;}
	| declarator '=' initializer	{$$ = non_term_symb("=", NULL, $1, $3);}
	;

storage_class_specifier
	: TYPEDEF	{$$=term_symb($1);}
	| EXTERN	{$$=term_symb($1);}
	| STATIC	{$$=term_symb($1);}
	| AUTO		{$$=term_symb($1);}
	| REGISTER	{$$=term_symb($1);}
	;

type_specifier
	: VOID							{$$ = term_symb($1);}
	| CHAR							{$$ = term_symb($1);}
	| SHORT							{$$ = term_symb($1);}
	| INT							{$$ = term_symb($1);}
	| LONG							{$$ = term_symb($1);}
	| FLOAT							{$$ = term_symb($1);}
	| DOUBLE						{$$ = term_symb($1);}
	| SIGNED						{$$ = term_symb($1);}
	| UNSIGNED						{$$ = term_symb($1);}
	| struct_or_union_specifier		{$$ = $1;}
	| enum_specifier				{$$ = $1;}
	| TYPE_NAME						{$$ = term_symb($1);}
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}'	{$$ = non_term_symb("struct_or_union_specifier", $2, $1, $4);}
	| struct_or_union '{' struct_declaration_list '}'				{$$ = non_term_symb("struct_or_union_specifier", NULL, $1, $3);}
	| struct_or_union IDENTIFIER									{$$ = non_term_symb("struct_or_union_specifier", $2, $1, NULL);}
	;

struct_or_union
	: STRUCT	{$$ = term_symb($1);}
	| UNION		{$$ = term_symb($1);}
	;

struct_declaration_list
	: struct_declaration							{$$ = $1;}
	| struct_declaration_list struct_declaration	{$$ = non_term_symb("struct_declaration_list", NULL, $1, $2);}
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'	{$$ = non_term_symb("struct_declaration", NULL, $1, $2);}
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list	{$$ = non_term_symb("specifier_qualifier_list", NULL, $1, $2);}
	| type_specifier							{$$ = $1;}
	| type_qualifier specifier_qualifier_list	{$$ = non_term_symb("specifier_qualifier_list", NULL, $1, $2);}
	| type_qualifier							{$$ = $1;}
	;

struct_declarator_list
	: struct_declarator {$$ = $1;}
	| struct_declarator_list ',' struct_declarator {$$ = non_term_symb("struct_declarator_list",NULL, $1, $3);}
	;

struct_declarator
	: declarator {$$ = $1;}
	| ':' constant_expression {$$ = $2;}
	| declarator ':' constant_expression {$$ = non_term_symb("struct_declarator", NULL, $1, $3);}
	;

enum_specifier
	: ENUM '{' enumerator_list '}' {$$ = non_term_symb("enum_specifier", $1, NULL, $3);}
	| ENUM IDENTIFIER '{' enumerator_list '}' {$$ = non_term_symb_3("enum_specifier", $1,$2, $4,NULL);}
	| ENUM IDENTIFIER {$$ = non_term_symb_3("enum_specifier",$1, $2,NULL, NULL);}
	;

enumerator_list
	: enumerator {$$ = $1;}
	| enumerator_list ',' enumerator {$$ = non_term_symb("enumerator_list", NULL, $1,  $3);}
	;

enumerator
	: IDENTIFIER {$$ = term_symb($1);}
	| IDENTIFIER '=' constant_expression {$$ = non_term_symb("=",NULL, term_symb($1), $3);}
	;

type_qualifier
	: CONST {$$ = term_symb($1);}
	| VOLATILE {$$ = term_symb($1);}
	;

declarator
	: pointer direct_declarator {$$ = non_term_symb("declarator", NULL, $1, $2);}
	| direct_declarator {$$ = $1;}
	;

direct_declarator
	: IDENTIFIER {$$=term_symb($1);}
	| '(' declarator ')' {$$ = $2;}
	| direct_declarator '[' constant_expression ']' {$$ = non_term_symb("direct_declarator", NULL, $1, $3);}
	| direct_declarator '[' ']' {$$ = square("direct_declarator", $1);}
	| direct_declarator '(' parameter_type_list ')' {$$ = non_term_symb("direct_declarator", NULL, $1, $3);}
	| direct_declarator '(' identifier_list ')' {$$ = non_term_symb("direct_declarator", NULL, $1, $3);}
	| direct_declarator '(' ')' {$$ = parentheses("direct_declarator", $1);}
	;

pointer
	: '*' {$$=term_symb("*");}
	| '*' type_qualifier_list {$$=non_term_symb("*",NULL,$2,NULL);}
	| '*' pointer {$$=non_term_symb("*",NULL,$2,NULL);}
	| '*' type_qualifier_list pointer {$$=non_term_symb("*",NULL,$2,$3);}
	;

type_qualifier_list
	: type_qualifier {$$=$1;}
	| type_qualifier_list type_qualifier {$$=non_term_symb("type_qualifier_list",NULL,$1,$2);}
	;


parameter_type_list
	: parameter_list {$$=$1;}
	| parameter_list ',' ELLIPSIS {$$=non_term_symb("parameter_type_list",NULL,$1,term_symb("ELLIPSIS"));}
	;

parameter_list
	: parameter_declaration {$$=$1;}
	| parameter_list ',' parameter_declaration {$$=non_term_symb("parameter_list",NULL,$1,$3);}
	;

parameter_declaration
	: declaration_specifiers declarator {$$=non_term_symb("parameter_declaration",NULL,$1,$2);}
	| declaration_specifiers abstract_declarator {$$=non_term_symb("parameter_declaration",NULL,$1,$2);}
	| declaration_specifiers {$$=$1;}
	;

identifier_list
	: IDENTIFIER {$$=term_symb($1);}
	| identifier_list ',' IDENTIFIER {$$=non_term_symb("identifier_list",NULL,$1,term_symb($3));}
	;

type_name
	: specifier_qualifier_list {$$=$1;}
	| specifier_qualifier_list abstract_declarator {$$=non_term_symb("type_name",NULL,$1,$2);}
	;

abstract_declarator
	: pointer {$$=$1;}
	| direct_abstract_declarator {$$=$1;}
	| pointer direct_abstract_declarator {$$=non_term_symb("abstract_declarator",NULL,$1,$2);}
	;

direct_abstract_declarator
	: '(' abstract_declarator ')' {$$ = $2;}
	| '[' ']' {$$ = term_symb("[ ]");}
	| '[' constant_expression ']' {$$ = $2;}
	| direct_abstract_declarator '[' ']' {$$ = non_term_symb("direct_abstract_declarator" , "[ ]", $1,NULL);}
	| direct_abstract_declarator '[' constant_expression ']' {$$ = non_term_symb("direct_abstract_declarator",NULL, $1, $3);}
	| '(' ')' {$$ = term_symb("( )");}
	| '(' parameter_type_list ')' {$$ = $2;}
	| direct_abstract_declarator '(' ')' {$$ = non_term_symb("direct_abstract_declarator","( )", $1,NULL);}
	| direct_abstract_declarator '(' parameter_type_list ')' {$$ = non_term_symb("direct_abstract_declarator", NULL, $1, $3);}
	;

initializer
	: assignment_expression {$$ = $1;}
	| '{' initializer_list '}' {$$ = $2;}
	| '{' initializer_list ',' '}' {$$ = non_term_symb("initializer", $3, $2 ,NULL);}
	;

initializer_list
	: initializer {$$ = $1;}
	| initializer_list ',' initializer {$$ = non_term_symb("initializer_list", NULL, $1 ,$3);}
	;

statement
	: labeled_statement {$$ = $1;}
	| compound_statement {$$ = $1;}
	| expression_statement {$$ = $1;}
	| selection_statement {$$ = $1;}
	| iteration_statement {$$ = $1;}
	| jump_statement {$$ = $1;}
	;

labeled_statement
	: IDENTIFIER ':' statement {$$ = non_term_symb("labeled_statement", NULL, term_symb($1), $3);}
	| CASE constant_expression ':' statement {$$ = non_term_symb_2("labeled_statement", term_symb("CASE"), $2, $4);}
	| DEFAULT ':' statement {$$ = non_term_symb("labeled_statement", NULL, term_symb("DEFAULT"), $3);}
	;

compound_statement
	: '{' '}' {$$ = term_symb("{ }");}
	| '{' statement_list '}' {$$ = $2;}
	| '{' declaration_list '}' {$$ = $2;}
	| '{' declaration_list statement_list '}' {$$ = non_term_symb("compound_statement",NULL, $2,$3);}
	;

declaration_list
	: declaration {$$=$1;}
	| declaration_list declaration {$$ = non_term_symb("declaration_list", NULL, $1, $2);}
	;

statement_list
	: statement {$$ = $1;}
	| statement_list statement {$$ = non_term_symb("statement_list", NULL, $1, $2);}
	;

expression_statement
	: ';' {$$ = term_symb(";");}
	| expression ';' {$$ = $1;}
	;

selection_statement
	: IF '(' expression ')' statement %prec IFX {$$ = non_term_symb_2("IF (expr) stmt", NULL, $3, $5);}
	| IF '(' expression ')' statement ELSE statement {$$ = non_term_symb_2("IF (expr) stmt ELSE stmt", $3, $5, $7);}
	| SWITCH '(' expression ')' statement {$$ = non_term_symb_2("SWITCH (expr) stmt", NULL, $3, $5);}
	;

iteration_statement
	: WHILE '(' expression ')' statement {$$ = non_term_symb_2("WHILE (expr) stmt", NULL, $3, $5);}
	| DO statement WHILE '(' expression ')' ';' {$$ = non_term_symb_2("DO stmt WHILE (expr)", NULL, $2, $5);}
	| FOR '(' expression_statement expression_statement ')' statement {$$ = non_term_symb_2("FOR (expr stmt expr stmt) stmt", $3, $4, $6);}
	| FOR '(' expression_statement expression_statement expression ')' statement {$$ = non_term_symb_5("FOR (expr stmt expr stmt expr) stmt", NULL, $3, $4, $5, $7);}
	;

jump_statement
	: GOTO IDENTIFIER ';' {$$ = non_term_symb("jump_statement", NULL, term_symb("GOTO"), term_symb($2));}
	| CONTINUE ';' {$$ = term_symb("continue");}
	| BREAK ';' {$$ = term_symb("break");}
	| RETURN ';' {$$ = term_symb("return");}
	| RETURN expression ';' {$$ = non_term_symb("jump_statement", NULL, term_symb("return"), $2);}
	;

translation_unit
	: external_declaration {$$ = $1;}
	| translation_unit external_declaration {$$ = non_term_symb("translation_unit", NULL, $1, $2);}
	;

external_declaration
	: function_definition {$$ = $1;}
	| declaration {$$ = $1;}
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement {$$ = non_term_symb_4("function_definition", $1, $2, $3, $4, NULL);}
	| declaration_specifiers declarator compound_statement {$$ = non_term_symb_2("function_definition", $1, $2, $3);}
	| declarator declaration_list compound_statement {$$ = non_term_symb_2("function_definition",$1,$2,$3);}
	| declarator compound_statement {$$ = non_term_symb_2("function_definition", $1,NULL,$2);}
	;

%%

