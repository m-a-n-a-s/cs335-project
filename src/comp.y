%{
// #include "functions.h"
#include <iostream>
// #include <cstring>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdarg.h>
#include <string>
using namespace std;


int scope;
int symNumber = 0;
int funcSym=0;
int isFunc;
int blockSym=0;
int yylex(void);
void yyerror(char *s,...);

#include "typecheck.h"
#include "functions.h"
#include "symTable.h"

string typeName="";
extern int yylineno;
string symFileName;
string funcName;
string funcType;
int structCounter=0;
string funcArguments;
string currArguments;

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
%type <str> assignment_operator E1 E2 E3 E5

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

// In struct_or_union '{' struct_declaration_list '}' check the last error line which I have commented. 
// Please add the rules of direct_declarator '[' constant_expression ']'


primary_expression
	: IDENTIFIER			{$$ = term_symb($1);
					char *a=primaryExpr($1);
					if(a){
						string as(a);
						$$->isInit = lookup($1)->is_init;
			                        $$->nodeType = as;
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
: primary_expression			{$$ = $1;}

| postfix_expression '[' expression ']'	{$$ = non_term_symb("[ ]", NULL, $1, $3);
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
															
| postfix_expression '(' ')'	{$$ = $1;
					$$->isInit=1;
				char* s = postfixExpr($1->nodeType, 2);
				if(s){
					string as(s);
					$$->nodeType =as;
					if($1->exprType==3){
						string funcArgs = funcArgList($1->nodeKey);
						if(!(funcArgs==string(""))) {
							yyerror("Error : \'%s\' function call requires arguments to be passed \n     \'%s %s\( %s \)\'",($1->nodeKey).c_str(),($$->nodeType).c_str(),($1->nodeKey).c_str(),funcArgs.c_str());
						}
					}
				}
				else{
					yyerror("Error : Invalid Function call");
				}																
				currArguments=string("");
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

	| postfix_expression PTR_OP IDENTIFIER					        {$$ = non_term_symb("->", NULL, $1, term_symb($3));
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

	| multiplicative_expression '*' cast_expression{
			$$ = non_term_symb("*", NULL, $1, $3);
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
														//$$ = nonTerminal2(">>", $1, NULL, $3);
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
							}	
							else {
								yyerror("Error : invalid operands to binary <");
							}
							if($1->isInit==1 && $3->isInit==1) $$->isInit=1;
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
							if($1->isInit==1 && $3->isInit==1) $$->isInit=1;
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
							if($1->isInit==1 && $3->isInit==1) $$->isInit=1;
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
							if($1->isInit==1 && $3->isInit==1) $$->isInit=1;
							}
	;

equality_expression
  : relational_expression   {$$ = $1;}
  | equality_expression EQ_OP relational_expression {$$ = non_term_symb_2("==", $1, NULL, $3);
						    char* a = equalityExpr($1->nodeType,$3->nodeType);
						    if(a){ if(!strcmp(a,"true")){
							    yyerror("Warning : Comparision between pointer and Integer");
							    }
							    $$->nodeType = "bool";
						    }
						   else{ yyerror("Error :Invalid operands to binary =="); }
						   if($1->isInit==1 && $3->isInit==1) $$->isInit=1;
                                                   }

  | equality_expression NE_OP relational_expression {$$ = non_term_symb_2("!=", $1, NULL, $3);
						    char* a = equalityExpr($1->nodeType,$3->nodeType);
						    if(a){   if(!strcmp(a,"true")){
							    yyerror("Warning : Comparision between pointer and Integer");
							    }
							    $$->nodeType = "bool";
						    }
						   else{ yyerror("Error :Invalid operands to binary !="); }
						   if($1->isInit==1 && $3->isInit==1) $$->isInit=1;
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
                 yyerror("Error :Invalid operands to the binary &");
               }
                 if($1->isInit==1 && $3->isInit==1) $$->isInit=1;
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
                 yyerror("Error :Invalid operands to the binary ^");
               }
                 if($1->isInit==1 && $3->isInit==1) $$->isInit=1;

        }
  ;

inclusive_or_expression
	: exclusive_or_expression								{$$ = $1;}
	| inclusive_or_expression '|' exclusive_or_expression	{$$ = non_term_symb("|", NULL, $1, $3);
								char* a = bitwiseExpr($1->nodeType,$3->nodeType);
								if(a){
									if(!strcmp(a,"true")) { $$->nodeType = string("bool"); }
									else{   $$->nodeType = string("long long");}
						
								}
								else {
									yyerror("Error :Invalid operands to the binary |");
								}
									if($1->isInit==1 && $3->isInit==1) $$->isInit=1;
							
								}
	;


   
logical_and_expression
	: inclusive_or_expression								{$$ = $1;}
	| logical_and_expression AND_OP inclusive_or_expression	{$$ = non_term_symb_2($2, $1, NULL, $3);
								$$->nodeType == string("bool");
								if($1->isInit==1 && $3->isInit==1) $$->isInit=1;
								}
	;

logical_or_expression
	: logical_and_expression								{$$ = $1;}
	| logical_or_expression OR_OP logical_and_expression	{$$ = non_term_symb_2($2, $1, NULL, $3);
								//$$ = nonTerminal2("||", $1,NULL, $3);
								if($1->isInit==1 && $3->isInit==1) $$->isInit=1;
								$$->nodeType == string("bool");
								}
	;

conditional_expression
	: logical_or_expression												{$$ = $1;}
	| logical_or_expression '?' expression ':' conditional_expression	{$$ = non_term_symb_2("logical_expr ? expr : conditional_expr", $1, $3, $5);
										$$->rVal = -11;
										char* a = conditionalExpr($3->nodeType,$5->nodeType);
										if(a){
											string as(a);
											$$->nodeType = string("int");
										}
										else{

											yyerror("Error :Type mismatch in conditional expression");
										}
										if($1->isInit==1 && $3->isInit==1 && $5->isInit==1) $$->isInit=1;																		
										}
	;

assignment_expression
	: conditional_expression										{$$ = $1;}
	| unary_expression assignment_operator assignment_expression	{$$ = non_term_symb_2($2, $1, NULL, $3);
									char* a = assignmentExpr($1->nodeType,$3->nodeType,$2);
									if(a){
											if(!strcmp(a,"true")){ $$->nodeType = $1->nodeType;
											}
											if(!strcmp(a,"warning")){ $$->nodeType = $1->nodeType;
												yyerror("Warning : Assignment with incompatible pointer type");
												}
											
											}
										else{ yyerror("Error : Incompatible types when assigning type \'%s\' to \'%s\' ",($1->nodeType).c_str(),($3->nodeType).c_str()); }
									if($1->exprType==3){ if($3->isInit==1) update_isInit($1->nodeKey); }
									}
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
	| expression ',' assignment_expression	{$$ = non_term_symb("expression ','", NULL, $1, $3);$$->nodeType = string("void");}
	;

constant_expression
	: conditional_expression	{$$ = $1;}
	;

declaration
	: declaration_specifiers ';' {typeName=string("");$$=$1;}
	| declaration_specifiers init_declarator_list ';'	{typeName=string("");$$ = non_term_symb("declaration", NULL, $1, $2);}
	;

declaration_specifiers
	: storage_class_specifier							{$$ = $1;}
	| storage_class_specifier declaration_specifiers	{$$ = non_term_symb("declaration_specifiers", NULL, $1, $2);}
	| type_specifier									{printf("In declaration_specifiers\n"); $$ = $1;}		
	| type_specifier declaration_specifiers				{$$ = non_term_symb("declaration_specifiers", NULL, $1, $2);}
	| type_qualifier									{$$ = $1;}
	| type_qualifier declaration_specifiers				{$$ = non_term_symb("declaration_specifiers", NULL, $1, $2);}
	;

init_declarator_list
	: init_declarator							{$$ = $1;}
	| init_declarator_list ',' init_declarator	{$$ = non_term_symb("init_declaration_list", NULL, $1, $3);}
	;

init_declarator
	: declarator{
		$$ = $1;
		if($1->exprType==1){ 
			char *t=new char();
        	strcpy(t,($1->nodeType).c_str());
        	char *key =new char();
        	strcpy(key,($1->nodeKey).c_str());
        	if(scopeLookup($1->nodeKey)){
                yyerror("Error : redeclaration of \'%s\'",key);
        	}else if($1->nodeType==string("void")){
        	    yyerror("Error : Variable or field \'%s\' declared void",key);
        	}else {  
				insertSymbol(*curr,key,t,$1->size,0,0);
			}
            //$$->place = pair<string, sEntry*>($1->nodeKey, lookup($1->nodeKey));
        }
	}
	| declarator '=' initializer	{
		$$ = non_term_symb("=", NULL, $1, $3);
		if($1->exprType==1||$1->exprType==15){ 
			char *t=new char();
            strcpy(t,($1->nodeType).c_str());
            char *key =new char();
            strcpy(key,($1->nodeKey).c_str());
        if(scopeLookup($1->nodeKey)){
			yyerror("Error : Redeclaration of \'%s\'",key);
            }else if($1->nodeType==string("void")){
                 yyerror("Error : Variable or field \'%s\' declared void",key);
            }
            else { 
				if($$->exprType==15) { 
					insertSymbol(*curr,key,t,($3->exprType*$1->iVal),0,1); 
				}
                insertSymbol(*curr,key,t,$1->size,0,1);
            }
        }
	}
	;

storage_class_specifier
	: TYPEDEF	{$$=term_symb($1);}
	| EXTERN	{$$=term_symb($1);}
	| STATIC	{$$=term_symb($1);}
	| AUTO		{$$=term_symb($1);}
	| REGISTER	{$$=term_symb($1);}
	;

type_specifier
	: VOID							{if(typeName==string(""))typeName = string($1);
                   					else typeName = typeName+string(" ")+string($1);
									$$ = term_symb($1);}
	| CHAR							{if(typeName==string(""))typeName = string($1);
                   					else typeName = typeName+string(" ")+string($1);
									$$ = term_symb($1);}
	| SHORT							{if(typeName==string(""))typeName = string($1);
                   					else typeName = typeName+string(" ")+string($1);
									$$ = term_symb($1);}
	| INT							{printf("Hello in type specifier\n"); if(typeName==string(""))typeName = string($1);
                   					else typeName = typeName+string(" ")+string($1);
									$$ = term_symb($1);}
	| LONG							{if(typeName==string(""))typeName = string($1);
                   					else typeName = typeName+string(" ")+string($1);
									$$ = term_symb($1);}
	| FLOAT							{if(typeName==string(""))typeName = string($1);
                   					else typeName = typeName+string(" ")+string($1);
									$$ = term_symb($1);}
	| DOUBLE						{if(typeName==string(""))typeName = string($1);
                   					else typeName = typeName+string(" ")+string($1);
									$$ = term_symb($1);}
	| SIGNED						{if(typeName==string(""))typeName = string($1);
                   					else typeName = typeName+string(" ")+string($1);
									$$ = term_symb($1);}
	| UNSIGNED						{if(typeName==string(""))typeName = string($1);
                   					else typeName = typeName+string(" ")+string($1);
									$$ = term_symb($1);}
	| struct_or_union_specifier		{if(typeName==string(""))typeName = $$->nodeType;
                   					else typeName = typeName+string(" ")+$$->nodeType;
									$$ = $1;}
	| enum_specifier				{$$ = $1; yyerror("Error : not implemented Enum specifier");}
	| TYPE_NAME						{if(typeName==string(""))typeName = string($1);
                   					else typeName = typeName+string(" ")+string($1);
									$$ = term_symb($1);}
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER E5 '{' struct_declaration_list '}'	{string as($2);
									$$ = non_term_symb("struct_or_union_specifier", $2, $1, $5);
									if(endStructTable(as)){
									$$->nodeType = string("STRUCT_")+as; }
									else yyerror("Error : struct \'%s\' is already defined\n", $2);
									}

	| struct_or_union E5 '{' struct_declaration_list '}'				{$$ = non_term_symb("struct_or_union_specifier", NULL, $1, $4);
											structCounter++;
											string as = to_string(structCounter);
											if(endStructTable(as)){
											$$->nodeType = string("STRUCT_")+as; }
											else yyerror("Error : struct \'%s\' is already defined\n", $2);
											}

	| struct_or_union IDENTIFIER									{$$ = non_term_symb("struct_or_union_specifier", $2, $1, NULL);
													string as($2);
													as = "STRUCT_" + as;
													if(isStruct(as)) $$->nodeType = as;
													else yyerror("Error : No struct \'%s\' is defined",$2);
													}
	;

E5
  : %empty {
           makeStructTable();
  };

struct_or_union
	: STRUCT	{$$ = term_symb($1);}
	| UNION		{$$ = term_symb($1);}
	;

struct_declaration_list
	: struct_declaration							{$$ = $1;}
	| struct_declaration_list struct_declaration	{$$ = non_term_symb("struct_declaration_list", NULL, $1, $2);}
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'	{$$ = non_term_symb("struct_declaration", NULL, $1, $2);typeName = string("");}
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
	: declarator {$$ = $1;
				if(!insertStructSymbol($1->nodeKey, $1->nodeType, $1->size, 0, 0)) yyerror(" : \'%s\' is already declared in the same struct", $1->nodeKey.c_str());}
	| ':' constant_expression {$$ = $2;}
	| declarator ':' constant_expression {$$ = non_term_symb("struct_declarator", NULL, $1, $3);
										if(!insertStructSymbol($1->nodeKey, $1->nodeType, $1->size, 0, 1)) yyerror("Error : \'%s\' is already declared in the same struct", $1->nodeKey.c_str());}
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
	: pointer direct_declarator {$$ = non_term_symb("declarator", NULL, $1, $2);
								if($2->exprType==1){$$->nodeType=$2->nodeType+$1->nodeType;
									$$->nodeKey = $2->nodeKey;
									$$->exprType=1;}
								if($2->exprType==2){ funcName = $2->nodeKey; funcType = $2->nodeType; }
								char* a = new char();
								strcpy(a,($$->nodeType).c_str());$$->size = getSize(a);}
	| direct_declarator {$$ = $1;
						if($1->exprType==2){ funcName=$1->nodeKey; funcType = $1->nodeType;}}
	;

direct_declarator
	: IDENTIFIER {printf("1\n");$$=term_symb($1);printf("2 %s\n",$1);
				$$->exprType=1;printf("3\n");/* $$->nodeKey=string($1)*/;string s($1);$$->nodeKey=s;printf("4\n");cout<<$$->nodeKey<<endl;
				$$->nodeType=typeName;printf("5%s\n",$$->nodeType);
				char* a =new char();printf("6\n");
                strcpy(a,typeName.c_str());printf("7\n");
				$$->size = getSize(a);printf("8\n");}
	| '(' declarator ')' {$$ = $2;
						if($2->exprType==1){ $$->exprType=1;
                                          $$->nodeKey=$2->nodeKey;
                                          $$->nodeType=$2->nodeType;}
						}
	| direct_declarator '[' constant_expression ']' {$$ = non_term_symb("direct_declarator", NULL, $1, $3);}
										//DOUBTFULL}
	| direct_declarator '[' ']'    {$$ = square("direct_declarator", $1);
				     	if($1->exprType==1){ $$->exprType=1;
                                     	$$->nodeKey=$1->nodeKey;
                                     	$$->nodeType=$1->nodeType+string("*");}
					char* a = new char();
					strcpy(a,($$->nodeType).c_str());
					$$->size = getSize(a);
					strcpy(a,($1->nodeType).c_str());
					$$->exprType=15;
					$$->iVal=getSize(a);
					}

	| direct_declarator '(' E3 parameter_type_list ')' {$$ = non_term_symb("direct_declarator", NULL, $1, $4);
							if($1->exprType==1){ $$->nodeKey=$1->nodeKey;
							$$->exprType=2;
							$$->nodeType=$1->nodeType;
							insertFuncArguments($1->nodeKey,funcArguments);
							funcArguments=string("");
							char* a = new char();
							strcpy(a,($$->nodeType).c_str());
							$$->size = getSize(a);
							}
							}

	| direct_declarator '(' E3 identifier_list ')' 	{$$ = non_term_symb("direct_declarator", NULL, $1, $4);
							char* a = new char();
							strcpy(a,($$->nodeType).c_str());
							$$->size = getSize(a);
							}

	| direct_declarator '(' E3 ')' 			{$$ = parentheses("direct_declarator", $1);
							if($1->exprType==1){
								$$->nodeKey=$1->nodeKey;
								insertFuncArguments($1->nodeKey,string(""));
								$$->exprType=2;
								funcArguments = string("");
							}
							$$->nodeType=$1->nodeType;
							char* a = new char();
							strcpy(a,($$->nodeType).c_str());
							$$->size = getSize(a);
							printf("Hello\n");
							}
	;
E3
   :%empty                  {   typeName =string("");
                          funcArguments = string("");
                           paramTable();  }
    ;
pointer
	: '*' {$$=term_symb("*");$$->nodeType=string("*");}
	| '*' type_qualifier_list {$$=non_term_symb("*",NULL,$2,NULL);$$->nodeType=string("*");}
	| '*' pointer {$$=non_term_symb("*",NULL,$2,NULL);$$->nodeType=string("*")+$2->nodeType;}
	| '*' type_qualifier_list pointer {$$=non_term_symb("*",NULL,$2,$3);$$->nodeType=string("*")+$3->nodeType;}
	;

type_qualifier_list
	: type_qualifier {$$=$1;}
	| type_qualifier_list type_qualifier {$$=non_term_symb("type_qualifier_list",NULL,$1,$2);}
	;


parameter_type_list
	: parameter_list {$$=$1;}
	| parameter_list ',' ELLIPSIS {	funcArguments = funcArguments+string(",...");
					$$=non_term_symb("parameter_type_list",NULL,$1,term_symb("ELLIPSIS"));
					}
	;

parameter_list
	: parameter_declaration {$$=$1;}
	| parameter_list ',' parameter_declaration {$$=non_term_symb("parameter_list",NULL,$1,$3);}
	;

parameter_declaration
	: declaration_specifiers declarator {typeName=string("");

          //paramTable();
         if($2->exprType==1){ char *t=new char();
                     strcpy(t,($2->nodeType).c_str());
                     char *key =new char();
                     strcpy(key,($2->nodeKey).c_str());
                  if(scopeLookup($2->nodeKey)){ yyerror("Error : redeclaration of %s",key);}
                   else {  insertSymbol(*curr,key,t,$2->size,0,1);}
                if(funcArguments==string(""))funcArguments=($2->nodeType);
               else funcArguments= funcArguments+string(",")+($2->nodeType);
                     }
        $$=non_term_symb("parameter_declaration",NULL,$1,$2);}
	| declaration_specifiers abstract_declarator {$$=non_term_symb("parameter_declaration",NULL,$1,$2);typeName=string("");}
	| declaration_specifiers {$$=$1;typeName=string("");}
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
	| '{' initializer_list '}' {$$ = $2; $$->nodeType = $2->nodeType+string("*");}
	| '{' initializer_list ',' '}' {$$ = non_term_symb("initializer", $3, $2 ,NULL);
									$$->nodeType = $2->nodeType+string("*"); $$->exprType =$2->exprType;
								}
	;

initializer_list
	: initializer {$$ = $1;$$->exprType=1;}
	| initializer_list ',' initializer {
          $$ = non_term_symb("initializer_list", NULL, $1 ,$3);
          $$->nodeType = $1->nodeType;
           char* a =validAssign($1->nodeType,$3->nodeType);
               if(a){
                    if(!strcmp(a,"true")){ ; }
                    if(!strcmp(a,"warning")){ ;
                         yyerror("Warning : Assignment with incompatible pointer type");
                         }
                     }
                else{ yyerror("Error : Incompatible types when initializing type \'%s\' to \'%s\' ",($1->nodeType).c_str(),($3->nodeType).c_str()); }
           $$->exprType = $1->exprType+1;
        }
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
	: '{' '}' {isFunc=0;$$ = term_symb("{ }");}
	| E1  statement_list '}'  {if(blockSym){ string s($1);
                                    s=s+string(".csv");
                                    string u($1);
                                    //printSymTables(curr,s);
                                    //updateSymTable(u); blockSym--;
									
                                 } $$ = $2;
                               }
	| E1  declaration_list '}'  {if(blockSym){ string s($1);
                                    s=s+string(".csv");
                                    string u($1);
                                    //printSymTables(curr,s);
                                    //updateSymTable(u); blockSym--;
									
                                 } $$ = $2;
                               }
	| '{' declaration_list statement_list '}' {$$ = non_term_symb("compound_statement",NULL, $2,$3);}
	;

E1
    :  '{'       { if(isFunc==0) {symNumber++;
                        symFileName = /*string("symTableFunc")+to_string(funcSym)*/funcName+string("Block")+to_string(symNumber);
                        //scope=S_BLOCK;
                        //makeSymTable(symFileName,scope,string("12345"));
                        char * y=new char();
                        strcpy(y,symFileName.c_str());
                        $$ = y;
                        //blockSym++;
                        }
                       isFunc=0;
              }

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
	: IF '(' expression ')' statement ELSE statement {$$ = non_term_symb_2("IF (expr) stmt ELSE stmt", $3, $5, $7);}
	| IF '(' expression ')' statement %prec IFX {$$ = non_term_symb_2("IF (expr) stmt", NULL, $3, $5);}
	| SWITCH '(' expression ')' statement{$$ = non_term_symb_2("SWITCH (expr) stmt", NULL, $3, $5);}
	;

iteration_statement
	: WHILE '(' expression ')' statement {$$ = non_term_symb_2("WHILE (expr) stmt", NULL, $3, $5);}
	| DO statement  WHILE '(' expression ')' ';'{$$ = non_term_symb_2("DO stmt WHILE (expr)", NULL, $2, $5);}
	| FOR '(' expression_statement expression_statement ')' statement {$$ = non_term_symb_2("FOR (expr_stmt expr_stmt) stmt", $3, $4, $6);}
	| FOR '(' expression_statement expression_statement expression ')'statement {$$ = non_term_symb_5("FOR (expr_stmt expr_stmt expr) stmt", NULL, $3, $4, $5, $7);}
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
	: function_definition {typeName=string("");$$ = $1;}
	| declaration {typeName=string("");$$ = $1;}
	;

function_definition

	: declaration_specifiers declarator E2 declaration_list compound_statement
         {      typeName=string("");
                string s($3);
                string u = s+string(".csv");
                printSymTables(curr,u);
                symNumber=0;
               updateSymTable(s);
                $$ = non_term_symb_4("function_definition", $1, $2, $4, $5, NULL);
         }
	| declaration_specifiers declarator E2 compound_statement  {
              typeName=string("");
              string s($3);string u =s+string(".csv");
              printSymTables(curr,u);
              symNumber=0;
              updateSymTable(s);
              $$ = non_term_symb_2("function_definition", $1, $2, $4);
            }
	| declarator declaration_list compound_statement { $$ = non_term_symb_2("function_definition",$1,$2,$3);
														//DOUBTFULL
													}
	| declarator compound_statement { $$ = non_term_symb_2("function_definition", $1,NULL,$2);
									//DOUBTFULL
									}
	;

E2
    : %empty                 { typeName=string("");scope = S_FUNC;
                                         isFunc = 1;
                                         funcSym++;
                                         symFileName = funcName;//string("symTableFunc")+to_string(funcSym);
                                         makeSymTable(symFileName,scope,funcType);
                                         char* y= new char();
                                         strcpy(y,symFileName.c_str());
                                         $$ = y;
       }
    ;

%%


extern FILE *yyin;
FILE* ast;



int main(int argc, char * argv[]){
    if (argc < 4){
        printf("ERROR ::: USAGE: <Parser> <File Name> -o <Output File Name>\n");
        return -1;
    }
	printf("Hello in main\n");
	funcName = string("GST");
	currArguments = string("");
	stInitialize();
	
    yyin = fopen(argv[1], "r");
    ast = fopen(argv[3], "w");
    fprintf(ast, "digraph G {\n\tordering=out;\n");
	printf("before yyparse\n");
    yyparse();
    fprintf(ast, "}\n");
    fclose(yyin);
    fclose(ast);

	symFileName = "GST.csv";
  	printSymTables(curr,symFileName);
  	printFuncArguments();
    return 0;
}
