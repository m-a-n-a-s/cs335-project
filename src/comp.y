%{
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <fcntl.h>
#include <list>
#include <stdarg.h>
#include <string>

using namespace std;

int scope;
int func_flag;

int symbol_count = 0;
int func_symb=0;
int blockSym=0;

int yylex(void);
void yyerror(char *s,...);

#include "semanticCheck.h"
#include "functions.h"
//#include "symbolTable.h"

extern int yylineno;
string file_name;
string func_type;
string func_name;
string funcArguments;
string currArguments;

string type_name="";
int structCounter=0;

int tempodd;
int tempeven;

%}

%union {
  int number;     /*value of integer*/
  char* str;
  struct node *ptr;     /*node pointer */
  number_types *num;
};
%nonassoc SR
%nonassoc CHAR CONST DOUBLE ENUM EXTERN FLOAT INT LONG REGISTER SHORT SIGNED STATIC STRUCT TYPEDEF UNION UNSIGNED VOID VOLATILE AUTO

%token <str> CHAR CONST CASE CONTINUE DEFAULT DO DOUBLE
%token <str> ELSE ENUM EXTERN FLOAT FOR IF INLINE INT LONG
%nonassoc IFX
%nonassoc ELSE
%token <str> REGISTER RESTRICT RETURN SHORT SIGNED STATIC STRUCT SWITCH TYPEDEF UNION
%token <str> UNSIGNED VOID VOLATILE WHILE ALIGNAS ALIGNOF ATOMIC BOOL COMPLEX
%token <str> GENERIC IMAGINARY NORETURN STATIC_ASSERT THREAD_LOCAL FUNC_NAME
%token <str> AUTO BREAK GOTO TYPEDEF_NAME IDENTIFIER ENUMERATION_CONSTANT
%token <num> CONSTANT
%token <str> STRING_LITERAL
%left <str> PTR_OP
%token <str> INC_OP DEC_OP
%token <str> LEFT_OP RIGHT_OP
%left <str> LE_OP GE_OP EQ_OP NE_OP
%left <str> AND_OP OR_OP
%right <str> MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%right <str> SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%right <str> XOR_ASSIGN OR_ASSIGN TYPE_NAME
%token <str> ELLIPSIS
%type <str> assignment_operator E1 E2 E3 E4 X1

%start translation_unit

%left <str> ',' '^' '|' ';' '{' '}' '[' ']' '(' ')' '+' '-' '%' '/' '*' '.' '>' '<' SIZEOF
%right <str> '&' '=' '!' '~' ':' '?'

%type <ptr> multiplicative_expression additive_expression cast_expression primary_expression expression assignment_expression postfix_expression unary_expression shift_expression relational_expression equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_or_expression logical_and_expression conditional_expression constant_expression
%type <ptr> type_name argument_expression_list initializer_list M3 M4 M5 M6 M7
%type <ptr> unary_operator
%type <ptr> declaration declaration_specifiers
%type <ptr> init_declarator_list storage_class_specifier type_specifier type_qualifier
%type <ptr> init_declarator declarator initializer struct_or_union_specifier enum_specifier struct_or_union struct_declaration_list
%type <ptr> struct_declaration specifier_qualifier_list struct_declarator_list struct_declarator enumerator_list enumerator pointer
%type <ptr> direct_declarator type_qualifier_list parameter_type_list identifier_list parameter_list parameter_declaration
%type <ptr> abstract_declarator direct_abstract_declarator labeled_statement compound_statement expression_statement declaration_list
%type <ptr> selection_statement iteration_statement jump_statement external_declaration translation_unit function_definition statement statement_list
%type <number> M N GOTO_emit

%%


primary_expression
	: IDENTIFIER			{$$ = term_symb($1);
							char *c=primary_expr($1);
							if(c){
								string tmp_str(c);
								$$->init_flag = lookup($1)->init_flag;
								$$->node_type = tmp_str;
								string key($1);
								$$->node_key = key;
								$$->expr_type = 3;
								// ****3AC****
								$$->place = pair<string,Entry*>(key,lookup(key));
                                $$->nextlist={};
								// ****3AC****
							}else{
								yyerror("Error : %s not declared",$1);
								string stmp("");
								$$->node_type=stmp;
							}
							}
	| CONSTANT				{$$ = term_symb($1->str);
							if($1->is_integer==1){
								long long val = $1->integer_value;
								char * a = constant($1->num_type);
								$$->init_flag=1;
								string tmp_str(a);
								$$->node_type=tmp_str;
								$$->integer_value = val;
								$$->real_value = -5;
								$$->expr_type=5;
							}else{
								long long val = (int) $1->real_value;
								
								char * a = constant($1->num_type);
								$$->init_flag =1;
								string tmp_str(a);
								$$->node_type=tmp_str;
								$$->integer_value = val;
								$$->expr_type=5;
							}
							// ****3AC****

							$$->place = pair<string,Entry*>($1->str,NULL);
                            $$->nextlist={};
							
							// ****3AC****

							//TO ADD SOME THING REMEBBER************************
							} 
	| STRING_LITERAL		{$$ = term_symb($1);
							string stmp("char *");
							$$->init_flag=1;
							$$->node_type=stmp;

							// ****3AC****

							$$->place = pair<string,Entry*>($1,NULL);
                            $$->nextlist={};

							// ****3AC****

							}
	| '(' expression ')'	{$$ = $2;}
	;

postfix_expression
: primary_expression			{$$ = $1;}

| postfix_expression '[' expression ']'	{$$ = non_term_symb("[ ]", NULL, $1, $3);
							if($1->init_flag==1 && $3->init_flag==1) $$->init_flag=1;
							char *s=postfix_expr($1->node_type,1);
							if(s&&is_Intgr($3->node_type)){
								string tmp_str(s);
								$$->node_type=tmp_str;

								//****3AC****

								$$->place = getTmpSym($$->node_type);
                                //qid opT  = pair<string,Entry*>("[]",NULL);
                                // int k = emit(opT, $1->place, $3->place, $$->place, -1);
                                $$->place.second->size = $3->place.second->offset;
                                $$->place.second->offset = $1->place.second->offset;
                                $$->place.second->init_flag = -5;
                                $$->nextlist = {};
                                //backPatch($3->truelist, k);
                                //backPatch($3->falselist, k);

								// **** 3AC ****

							}else if(!is_Intgr($3->node_type)){
								yyerror("Error : array index not a int");
							}else{
								yyerror("Error : array indexed with more indices than its dimension");
							}
							}																
															
| postfix_expression '(' ')'	{$$ = $1;
							$$->init_flag=1;
							char* s = postfix_expr($1->node_type, 2);
							if(s){
								string tmp_str(s);
								$$->node_type =tmp_str;
								if($1->expr_type==3){
									string funcArgs = func_args_list($1->node_key);

									//----------------------------3AC-------------------------------------------------//
                         			qid t = getTmpSym($$->node_type);
									int k=emit(pair<string, Entry*>("refParam", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), t, -1);
									int k1=emit(pair<string, Entry*>("CALL", NULL), $1->place, pair<string, Entry*>("1", NULL), t, -1);
									$$->nextlist ={};
									$$->place = t;
									//-------------------------3AC---------------------------------------//

									if(!(funcArgs=="")){//yyerror("Error : \'%s\' Invalid function call. Usage    \'%s %s\( %s \)\'",($1->node_key).c_str(),($$->node_type).c_str(),($1->node_key).c_str(),funcArgs.c_str());
										yyerror("Error : \'%s\' invalid function call.",($1->node_key).c_str());
									}
								}
							}else yyerror("Error : Invalid Function call");															
							currArguments="";
							}

| postfix_expression '(' argument_expression_list ')'	{$$ = non_term_symb("postfix_expression", NULL, $1, $3);
							if($3->init_flag==1) $$->init_flag=1;
							char* s = postfix_expr($1->node_type, 3);
							if(s){
								string tmp_str(s);
								$$->node_type =tmp_str;
								if($1->expr_type==3){
									string funcArgs = func_args_list($1->node_key);
									char* a =new char();
									string temp1 = currArguments;
									string temp2 = funcArgs;
									string typeA,typeB;
									string delim = ",";
									unsigned f1=1;
									unsigned f2=1;
									int argNo = 0;
									while(f1!=-1 && f2!=-1){
										f1 = temp1.find_first_of(delim);
										f2 = temp2.find_first_of(delim);
										argNo++;
										if(f1==-1) typeA = temp1; else{ typeA = temp1.substr(0,f1); temp1 = temp1.substr(f1+1);}
										if(f2==-1) typeB = temp2 ; else{ typeB = temp2.substr(0,f2); temp2 = temp2.substr(f2+1); }
										if(typeB=="...") break;
										a = validAssign(typeA,typeB);
										if(a){
											if(!strcmp(a,"warning")) { yyerror("Warning : Passing argument %d of \'%s\' from incompatible pointer type.\n Note : expected \'%s\' but argument is of type \'%s\'\n     \'%s %s\( %s \)\'",argNo,($1->node_key).c_str(),typeB.c_str(),typeA.c_str(),($$->node_type).c_str(),($1->node_key).c_str(),funcArgs.c_str()); }
										}else{
											yyerror("Error : Incompatible argument type %d of \'%s\' .\n Expected \'%s\' but argument is of type \'%s\'\n     \'%s %s\( %s \)\'",argNo,($1->node_key).c_str(),typeB.c_str(),typeA.c_str(),($$->node_type).c_str(),($1->node_key).c_str(),funcArgs.c_str());
										}
										if((f1!=-1)&&(f2!=-1)){
											continue;
										}else if(f2!=-1){
											if(!(temp2=="...")) yyerror("Error : Too few arguments for the function \'%s\'\n    \'%s %s\( %s \)\'",($1->node_key).c_str(),($$->node_type).c_str(),($1->node_key).c_str(),funcArgs.c_str());
											break;
										}else if(f1!=-1){
											yyerror("Error : Too many arguments for the function \'%s\'\n    \'%s %s\( %s \)\'",($1->node_key).c_str(),($$->node_type).c_str(),($1->node_key).c_str(),funcArgs.c_str());
											break;
										}else{ break; }
									}
									//--------------------------3AC----------------------------------//
                       				unsigned fT=1;
                       				unsigned carg=1;
                  					while(fT!=-1){
                          				carg++;
                          				fT = currArguments.find_first_of(delim);
                          				if(fT==-1) typeA = currArguments; else{ typeA = currArguments.substr(0,fT); currArguments = currArguments.substr(fT+1);}
                  					}
                  					qid t = getTmpSym($$->node_type);
                  					emit(pair<string, Entry*>("refParam", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), t, -1);
                  					int k=emit(pair<string, Entry*>("CALL", NULL), $1->place, pair<string, Entry*>(to_string(carg), NULL), t, -1);
                  					$$->place = t;
                  					$$->nextlist ={};
                  					//----------------------------3AC-----------------------------------------//	
								}

							}
							else {
								yyerror("Error : Invalid Function call");
							}
								currArguments="";
							}
	| postfix_expression '.' IDENTIFIER			{$$ = non_term_symb(" . ", NULL, $1, term_symb($3));
												string tmp_str($3);
												int k = structLookup($1->node_type, tmp_str);
												

												switch(k){
													case 1: yyerror("Error : Invalid operator \'.\' on \'%s\'", $1->node_key.c_str() );break;
													case 2: yyerror("Error : \'%s\' does not have member \'%s\'", $1->node_key.c_str() ,$3);break;
													default: {string stmp=struct_membr_type($1->node_type, tmp_str);$$->node_type=stmp;}break;
												}

												string xtmp = $1->node_key+ "." + tmp_str; $$->node_key=xtmp;
												}

	| postfix_expression PTR_OP IDENTIFIER		{$$ = non_term_symb("->", NULL, $1, term_symb($3));
												string tmp_str($3);
												string as1 = ($1->node_type).substr(0,($1->node_type).length()-1);
												int k = structLookup(as1, tmp_str);
												

												switch(k){
													case 1: yyerror("Error :Invalid operator  \'%s\' on \'%s\'", $2, $1->node_key.c_str() );break;
													case 2: yyerror("Error : \'%s\' does not have member \'%s\'", $1->node_key.c_str() ,$3);break;
													default: {string stmp = struct_membr_type(as1, tmp_str);$$->node_type=stmp;}break;
												}

												string xtmp = $1->node_key+ "->" + tmp_str; $$->node_key=xtmp;
												}

	| postfix_expression INC_OP					{$$=  non_term_symb("++", NULL,$1, NULL);
												if($1->init_flag==1) $$->init_flag=1;
												char* s = postfix_expr($1->node_type, 6);
												if(s){
													string tmp_str(s);
													$$->node_type =tmp_str;
													$$->integer_value = $1->integer_value +1;

													//------------------3AC------------//
                  									qid t1 = getTmpSym($$->node_type);
                  									int k=  emit(pair<string, Entry*>("++S", lookup("++")), $1->place, pair<string, Entry*>("", NULL), t1, -1);
                  									$$->place = t1;
                  									$$->nextlist = {};
                  									//-----------------3AC-----------------//

												}else {
													yyerror("Error : \'%s\' not defined for this type",$2);
												}
												}

	| postfix_expression DEC_OP					{$$=  non_term_symb("--", NULL,$1, NULL);
												if($1->init_flag==1) $$->init_flag =1;
												char* s = postfix_expr($1->node_type, 7);
												if(s){
													string tmp_str(s);
													$$->node_type =tmp_str;
												    $$->integer_value = $1->integer_value -1;

													//-----------------3AC-------------//
                  									qid t1 = getTmpSym($$->node_type);
                  									int k=emit(pair<string, Entry*>("--S", lookup("--")), $1->place, pair<string, Entry*>("", NULL), t1, -1);
                  									$$->place = t1;
                  									$$->nextlist={};
                  									//--------------3AC-------------//
													  
												}else {
													yyerror("Error : \'%s\' not defined for this type",$2);
												}
												}
	;

argument_expression_list
	: assignment_expression									{$$ = $1;if($1->init_flag==1)$$->init_flag = 1; currArguments = $1->node_type;
															//----------------3AC------------//
                											if($$->place.second == NULL && $$->node_type == "char*"){
                											  int k=emit(pair<string, Entry*>("param", NULL), $$->place, pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), -4);
                											}
                											else int k=emit(pair<string, Entry*>("param", NULL), $$->place, pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), -1);
                											$$->nextlist={};
                											//---------------3AC------------//
															}
	| argument_expression_list ',' assignment_expression	{$$ = non_term_symb($2,NULL,$1, $3);
								char* a =  argument_expr($1->node_type, $3->node_type, 2);
								string tmp_str(a);
								$$->node_type = tmp_str;
								if($1->init_flag == 1 && $3->init_flag==1) $$->init_flag=1;
								currArguments = currArguments +","+ $3->node_type;
								//-------3AC-------------//
             					if($3->place.second == NULL && $3->node_type == "char*"){
             					     int k=emit(pair<string, Entry*>("param", NULL), $3->place, pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), -4);
             					}
             					else int k=emit(pair<string, Entry*>("param", NULL), $3->place, pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), -1);
             					$$->nextlist={};
             					//------3AC--------------//
								}
	;

unary_expression
	: postfix_expression				{$$ = $1;}
	| INC_OP unary_expression			{$$ = non_term_symb("++", NULL, NULL, $2);
							if($2->init_flag == 1 ) $$->init_flag=1;
							char* s = postfix_expr($2->node_type, 6);
							if(s){
								string tmp_str(s);
								$$->node_type =tmp_str;
								$$->integer_value = $2->integer_value +1;
								//===========3AC======================//
                  				qid t1 = getTmpSym($$->node_type);
                  				int k = emit(pair<string, Entry*>("++P", lookup("++")), $2->place, pair<string, Entry*>("", NULL), t1, -1);
                  				$$->place = t1;
                  				$$->nextlist = {};
              					//    $$->code =  $2->code + '\n' +\
                				//         $$->node_key + string("= ") + "INC_OP" + string(" ") + $2->node_key;
                  				//====================================//
							}
							else {
								yyerror("Error : \'%s\' not defined for this type",$1);
							}
							}
	| DEC_OP unary_expression			{$$ = non_term_symb("--", NULL, NULL, $2);
							$$->integer_value =$2->integer_value -1;
							if($2->init_flag == 1 ) $$->init_flag=1;
							char* s = postfix_expr($2->node_type, 7);
							if(s){
								string tmp_str(s);
								$$->node_type =tmp_str;
								//===========3AC======================//
                  				qid t1 = getTmpSym($$->node_type);
                  				int k = emit(pair<string, Entry*>("--P", lookup("--")), $2->place, pair<string, Entry*>("", NULL), t1, -1);
                  				$$->place = t1;
                  				$$->nextlist={};

                  				//====================================//
							}
							else {
								yyerror("Error : \'%s\' not defined for this type",$1);
							}			
							}
	| unary_operator cast_expression	{$$ = non_term_symb("unary_expression", NULL, $1, $2);
						$$->integer_value = $2->integer_value;
						if( $2->init_flag==1) $$->init_flag=1;
						char* a= unary_expr($1->name, $2->node_type, 1);
						if(a){
							string tmp_str(a);
							$$->node_type= tmp_str;
							//===========3AC======================//
                  			qid t1 = getTmpSym($$->node_type);
                  			int k = emit($1->place, $2->place, pair<string, Entry*>("", NULL), t1, -1);
                  			$$->place = t1;
                  			$$->nextlist={};

                  			//====================================//
						}
						else{
							yyerror("Error : Inconsistent type  with operator %s", $1->name.c_str());
						}
						}
	| SIZEOF unary_expression			{$$ = non_term_symb($1, NULL, NULL, $2);$$->node_type = "int";$$->init_flag=1;
										//===========3AC======================//
                  						qid t1 = getTmpSym($$->node_type);
                  						int k = emit(pair<string, Entry*>("SIZEOF", lookup("sizeof")), $2->place, pair<string, Entry*>("", NULL), t1, -1);
                  						$$->place = t1;
                  						$$->nextlist={};

                						//====================================//
										}
	| SIZEOF '(' type_name ')'			{$$ = non_term_symb($1, NULL, NULL, $3);$$->node_type = "int";$$->init_flag=1;
										//===========3AC======================//
                						  qid t1 = getTmpSym($$->node_type);
                						  int k = emit(pair<string, Entry*>("SIZEOF", lookup("sizeof")), $3->place, pair<string, Entry*>("", NULL), t1, -1);
                						  $$->place = t1;
                						  $$->nextlist={};

                						//====================================//
										}
	;

unary_operator
	: '&'	{$$ = term_symb("&");$$->name="&";}
	| '*'	{$$ = term_symb("*");$$->name="*";}
	| '+'	{$$ = term_symb("+");$$->name="+";}
	| '-'	{$$ = term_symb("-");$$->name="-";}
	| '~'	{$$ = term_symb("~");$$->name="~";}
	| '!'	{$$ = term_symb("!");$$->name="!";}
	;

cast_expression
	: unary_expression					{$$ = $1;}
	| '(' type_name ')' cast_expression	{$$ = non_term_symb("cast_expression", NULL, $2, $4);
						$$->node_type = $2->node_type;
        				if($4->init_flag==1) $$->init_flag=1;
						//=============3AC====================//
                        qid t1 = getTmpSym($$->node_type);
                        string t = $4->node_type+ "to" + $$->node_type ;
                        int k = emit(pair<string, Entry*>(t, NULL), $4->place, pair<string, Entry*>(",", NULL), t1, -1);
                        $$->nextlist={};
                        $$->place = t1;

                        //====================================//
						}
	;

multiplicative_expression
	: cast_expression								{$$ = $1;}

	| multiplicative_expression '*' cast_expression{
			$$ = non_term_symb("*", NULL, $1, $3);
			char* a=multilplicative_expr($1->node_type, $3->node_type, '*');
			if(a){
				int k;
				if(strcmp(a,"int")==0){
					//$$=non_term_symb("*int",NULL,$1,$3);
					$$->node_type = "long long";
					//---------------3AC----------------//
                  	qid t1 = getTmpSym($$->node_type);
                  	k=emit(pair<string, Entry*>("*int", lookup("*")), $1->place, $3->place, t1, -1);
                  	$$->place = t1;
                  	$$->nextlist={};
                	//--------------3AC--------------------//
				}
				else if (strcmp(a, "float")==0){
					//$$=non_term_symb("*float",NULL,$1,$3);
					$$->node_type = "long double";
					//-------------3AC---------------------//
                  	qid t1 = getTmpSym($$->node_type);

                  	if(is_Intgr($1->node_type)){
                  	      qid t2 = getTmpSym($$->node_type);
                  	      emit(pair<string, Entry*>("inttoreal",NULL),$1->place,pair<string, Entry*>("",NULL),t2,-1);
                  	      k=emit(pair<string, Entry*>("*real", lookup("*")), t2, $3->place, t1, -1);
                  	}
                  	else if(is_Intgr($3->node_type)){
                  	      qid t2 = getTmpSym($$->node_type);
                  	      emit(pair<string, Entry*>("inttoreal",NULL),$3->place,pair<string, Entry*>("",NULL),t2,-1);
                  	      k=emit(pair<string, Entry*>("*real", lookup("*")), $1->place, t2, t1, -1);
                  	}
                  	else {

                  	      k=emit(pair<string, Entry*>("*real", lookup("*")), $1->place, $3->place, t1, -1);
                  	}
                  	$$->place = t1;
                  	$$->nextlist={};
                	//------------3AC-----------------------------//
				}
			}
			else{
				//$$=non_term_symb("*",NULL,$1,$3);
				yyerror("Error : Incompatible type for \'*\'");
			}
			if($1->init_flag==1 && $3->init_flag==1) $$->init_flag=1;
		}
	| multiplicative_expression '/' cast_expression	{$$ = non_term_symb("/", NULL, $1, $3);
														if ($3->integer_value != 0)
															$$->integer_value = $1->integer_value/ $3->integer_value;
														char* a=multilplicative_expr($1->node_type, $3->node_type, '/');
														if(a){int k;
															if(!strcmp(a,"int")){
																//$$=non_term_symb("/int",NULL,$1,$3);
																$$->node_type = "long long";
																//---------------3AC----------------------//
                  												qid t1 = getTmpSym($$->node_type);
                  												k = emit(pair<string, Entry*>("/int", lookup("/")), $1->place, $3->place, t1, -1);
                  												$$->place = t1;
                  												$$->nextlist= {};
                  												//--------------3AC------------------------//
															}
															else if (!strcmp(a,"float")){
																//$$=non_term_symb("/float",NULL,$1,$3);
																$$->node_type = "long double";
																//-------------3AC---------------------//
                  												qid t1 = getTmpSym($$->node_type);

                  												if(is_Intgr($1->node_type)){
                  												      qid t2 = getTmpSym($$->node_type);
                  												      emit(pair<string, Entry*>("inttoreal",NULL),$1->place,pair<string, Entry*>("",NULL),t2,-1);
                  												      k=emit(pair<string, Entry*>("/real", lookup("/")), t2, $3->place, t1, -1);
                  												}
                  												else if(is_Intgr($3->node_type)){
                  												      qid t2 = getTmpSym($$->node_type);
                  												      emit(pair<string, Entry*>("inttoreal",NULL),$3->place,pair<string, Entry*>("",NULL),t2,-1);
                  												      k=emit(pair<string, Entry*>("/real", lookup("/")), $1->place, t2, t1, -1);
                  												}
                  												else {
                  												      k=emit(pair<string, Entry*>("/real", lookup("/")), $1->place, $3->place, t1, -1);
                  												}
                  												$$->place =t1;
                  												$$->nextlist={};
                  												//-------------------------------------------//
															}
														}
														else{
															//$$=non_term_symb("/",NULL,$1,$3);
															yyerror("Error : Incompatible type for \'/\'");
														}
														if($1->init_flag==1 && $3->init_flag==1) $$->init_flag=1;
													}

	| multiplicative_expression '%' cast_expression	{$$ = non_term_symb("%", NULL, $1, $3);
							if($3->integer_value != 0) $$->integer_value = $1->integer_value % $3->integer_value;
							char* a=multilplicative_expr($1->node_type, $3->node_type, '/');
							if(!strcmp(a,"int")){
								$$->node_type= "long long";
								//===========3AC======================//
                  				qid t1 = getTmpSym($$->node_type);
                  				int k =emit(pair<string, Entry*>("%", lookup("%")), $1->place, $3->place, t1, -1);
                  				$$->nextlist={};
                  				$$->place = t1;

                  				//====================================//
							}
							else yyerror("Error : Incompatible type for \'%\'");
							if($1->init_flag==1 && $3->init_flag==1) $$->init_flag=1;

							}
	;

additive_expression
	: multiplicative_expression							{$$ = $1;}
	| additive_expression '+' multiplicative_expression	{$$ = non_term_symb("+", NULL, $1, $3);
								$$->integer_value = $1->integer_value + $3->integer_value;
								char *a = additive_expr($1->node_type,$3->node_type,'+');
								const char *q=new char();
								string p;
								if(a){
									string tmp_str(a);
									p = "+"+tmp_str;
									q = p.c_str();
								}
								else q = "+";
								//$$=non_term_symb(q,NULL,$1,$3);
								if(a){ 
									string tmp_str(a);
									if(!strcmp(a,"int")) $$->node_type="long long";
									else if(!strcmp(a,"real")) $$->node_type="long double";
									else $$->node_type=tmp_str; // for imaginary and complex returns
									//===========3AC======================//
                   					qid t1 = getTmpSym($$->node_type);
                   					if(is_Intgr($1->node_type) && is_float($3->node_type)){
                   					     qid t2 = getTmpSym($$->node_type);
                   					     emit(pair<string, Entry*>("inttoreal",NULL),$1->place,pair<string, Entry*>("",NULL),t2,-1);
                   					     emit(pair<string, Entry*>(p, lookup("+")), t2, $3->place, t1, -1);
                   					}
                   					else if(is_Intgr($3->node_type) && is_float($1->node_type)){
                   					     qid t2 = getTmpSym($$->node_type);
                   					     emit(pair<string, Entry*>("inttoreal",NULL),$3->place,pair<string, Entry*>("",NULL),t2,-1);
                   					     emit(pair<string, Entry*>(p, lookup("+")), $1->place, t2, t1, -1);
                   					}
                   					else {
                   					     emit(pair<string, Entry*>(p, lookup("+")), $1->place, $3->place, t1, -1);
                   					}
                   					$$->place = t1;
                  					$$->nextlist = {};
                  					//====================================//
								}
								else {
									yyerror("Error : Incompatible type for \'+\'");
								}
								if($1->init_flag==1 && $3->init_flag==1) $$->init_flag=1;
								}

	| additive_expression '-' multiplicative_expression	{$$ = non_term_symb("-", NULL, $1, $3);
								$$->integer_value = $1->integer_value - $3->integer_value;
								char *a = additive_expr($1->node_type,$3->node_type,'-');
								char *q = new char();
								string p;
								if(a){ string tmp_str(a);
									p ="-"+tmp_str;
									strcpy(q,p.c_str());
								}
								//$$=non_term_symb(q,NULL,$1,$3);
								if(a){ 
									string tmp_str(a);
									if(!strcmp(a,"int")) $$->node_type="long long";
									else if(!strcmp(a,"real")) $$->node_type="long double";
									else $$->node_type=tmp_str;   // for imaginary and complex returns
									//===========3AC======================//
                   					qid t1 = getTmpSym($$->node_type);
                   					if(is_Intgr($1->node_type) && is_float($3->node_type)){
                   					     qid t2 = getTmpSym($$->node_type);
                   					     emit(pair<string, Entry*>("inttoreal",NULL),$1->place,pair<string, Entry*>("",NULL),t2,-1);
                   					     emit(pair<string, Entry*>(p, lookup("-")), t2, $3->place, t1, -1);
                   					}
                   					else if(is_Intgr($3->node_type) && is_float($1->node_type)){
                   					     qid t2 = getTmpSym($$->node_type);
                   					     emit(pair<string, Entry*>("inttoreal",NULL),$3->place,pair<string, Entry*>("",NULL),t2,-1);
                   					     emit(pair<string, Entry*>(p, lookup("-")), $1->place, t2, t1, -1);
                   					}
                   					else {
                   					     emit(pair<string, Entry*>(p, lookup("-")), $1->place, $3->place, t1, -1);
                   					}
                   					$$->place = t1;
                   					$$->nextlist = {};
                  					//====================================//
								}
								else {
									yyerror("Error : Incompatible type for \'-\'");
								}
								if($1->init_flag==1 && $3->init_flag==1) $$->init_flag=1;
								}
	;

shift_expression
	: additive_expression							{$$ = $1;}
	| shift_expression LEFT_OP additive_expression	{$$ = non_term_symb_2($2, $1, NULL, $3);
							char* a = shift_expr($1->node_type,$3->node_type);                        
							if(a){
								$$->node_type = $1->node_type;
								//===========3AC======================//
                          		qid t1 = getTmpSym($$->node_type);
                          		int k = emit(pair<string, Entry*>("LEFT_OP", lookup("<<")), $1->place, $3->place, t1, -1);
                          		$$->place = t1;
                          		$$->nextlist={};
                        		//====================================//
							}
							else yyerror("Error : Invalid operands to <<");
							if($1->init_flag==1 && $3->init_flag==1) $$->init_flag=1;
							}

	| shift_expression RIGHT_OP additive_expression	{$$ = non_term_symb_2($2, $1, NULL, $3);
														//$$ = non_term_symb_2(">>", $1, NULL, $3);
														char* a = shift_expr($1->node_type,$3->node_type);
														if(a){
															$$->node_type = $1->node_type;
															//===========3AC======================//
                                 							qid t1 = getTmpSym($$->node_type);
                                 							int k = emit(pair<string, Entry*>("RIGHT_OP", lookup(">>")), $1->place, $3->place, t1, -1);
                                 							$$->place = t1;
                                 							$$->nextlist={};
                                							//====================================//	
														}
														else{yyerror("Error : Invalid operands to >>");}

														if($1->init_flag==1 && $3->init_flag==1) $$->init_flag=1;
													}
	;

relational_expression
	: shift_expression								{$$ = $1;}
	| relational_expression '<' shift_expression	{$$ = non_term_symb("<", NULL, $1, $3);
							char* a = relational_expr($1->node_type,$3->node_type,"<");
							if(a) { 
								if(!strcmp(a,"bool")) $$->node_type = "bool";
								else if(!strcmp(a,"bool_warning")){
									$$->node_type = "bool";
									yyerror("Warning : Invalid Comparison : pointer and Integer");
								}
								//===========3AC======================//
                        		qid t1 = getTmpSym($$->node_type);
                        		int k =  emit(pair<string, Entry*>("<", lookup("<")), $1->place, $3->place, t1, -1);
                        		$$->place = t1;
                        		$$->nextlist={};
                       			//====================================//
							}	
							else {
								yyerror("Error : invalid operands to <");
							}
							if($1->init_flag==1 && $3->init_flag==1) $$->init_flag=1;
							}

	| relational_expression '>' shift_expression	{$$ = non_term_symb(">", NULL, $1, $3);
							char* a=relational_expr($1->node_type,$3->node_type,">");
							if(a){ 
								if(!strcmp(a,"bool")) $$->node_type = "bool";
								else if(!strcmp(a,"bool_warning")){
									$$->node_type = "bool";
									yyerror("Warning : Invalid Comparison : pointer and Integer");
								}
								//===========3AC======================//
                           		qid t1 = getTmpSym($$->node_type);
                           		int k = emit(pair<string, Entry*>(">", lookup(">")), $1->place, $3->place, t1, -1);
                           		$$->place = t1;
                           		$$->nextlist = {};
                       			//====================================//
							}else {
								yyerror("Error : invalid operands to >");
							}
							if($1->init_flag==1 && $3->init_flag==1) $$->init_flag=1;
							}

	| relational_expression LE_OP shift_expression	{$$ = non_term_symb($2, NULL, $1, $3);
							char* a=relational_expr($1->node_type,$3->node_type,"<=");
							if(a){
								if(!strcmp(a,"bool")) $$->node_type = "bool";
								else if(!strcmp(a,"bool_warning")){
									$$->node_type = "bool";
									yyerror("Warning : Invalid Comparison : pointer and Integer");
								}
								//===========3AC======================//
                          	 	qid t1 = getTmpSym($$->node_type);
                          		int k= emit(pair<string, Entry*>("LE_OP", lookup("<=")), $1->place, $3->place, t1, -1);
                           		$$->place = t1;
                           		$$->nextlist = {};
                       			//====================================//
							}else {
								yyerror("Error : invalid operands to <=");
							}
							if($1->init_flag==1 && $3->init_flag==1) $$->init_flag=1;
							}

	| relational_expression GE_OP shift_expression	{$$ = non_term_symb($2, NULL, $1, $3);
							char* a=relational_expr($1->node_type,$3->node_type,">=");
							if(a){  
								if(!strcmp(a,"bool")) $$->node_type = "bool";
								else if(!strcmp(a,"bool_warning")){
									$$->node_type = "bool";
									yyerror("Warning : Invalid Comparison : pointer and Integer");
								}
								//===========3AC======================//
                           		qid t1 = getTmpSym($$->node_type);
                           		int k = emit(pair<string, Entry*>("GE_OP", lookup(">=")), $1->place, $3->place, t1, -1);
                           		$$->place = t1;
                           		$$->nextlist ={};
                       			//====================================//	
							}else {
								yyerror("Error : invalid operands to >=");
							}
							if($1->init_flag==1 && $3->init_flag==1) $$->init_flag=1;
							}
	;

equality_expression
  : relational_expression   {$$ = $1;}
  | equality_expression EQ_OP relational_expression {$$ = non_term_symb_2("==", $1, NULL, $3);
						    char* a = equality_expr($1->node_type,$3->node_type);
						    if(a){ if(!strcmp(a,"true")){
							    yyerror("Warning : Invalid Comparison : pointer and Integer");
							    }
							    $$->node_type = "bool";
								//===========3AC======================//
                           		qid t1 = getTmpSym($$->node_type);
                           		int k = emit(pair<string, Entry*>("EQ_OP", lookup("\=\=")), $1->place, $3->place, t1, -1);
                           		$$->place = t1;
                           		$$->nextlist = {};
                       			//====================================//
						    }
						   else{ yyerror("Error :Invalid operands to =="); }
						   if($1->init_flag==1 && $3->init_flag==1) $$->init_flag=1;
                                                   }

  | equality_expression NE_OP relational_expression {$$ = non_term_symb_2("!=", $1, NULL, $3);
						    char* a = equality_expr($1->node_type,$3->node_type);
						    if(a){   if(!strcmp(a,"true")){
							    yyerror("Warning : Invalid Comparison : pointer and Integer");
							    }
							    $$->node_type = "bool";
								//===========3AC======================//
                           		qid t1 = getTmpSym($$->node_type);
                           		int k = emit(pair<string, Entry*>("NE_OP", lookup("!=")), $1->place, $3->place, t1, -1);
                           		$$->place = t1;
                           		$$->nextlist ={};
                       			//====================================//
						    }
						   else{ yyerror("Error :Invalid operands to !="); }
						   if($1->init_flag==1 && $3->init_flag==1) $$->init_flag=1;
                                                   }
  ;

and_expression
  : equality_expression  { $$ = $1;}
  | and_expression '&' equality_expression  {
               $$ = non_term_symb("&",NULL, $1, $3);
               char* a = bitwise_expr($1->node_type,$3->node_type);
               if(a){
                  if(!strcmp(a,"true")) { $$->node_type = "bool"; }
                  else{  $$->node_type = "long long"; }
				  //===========3AC======================//
                  qid t1 = getTmpSym($$->node_type);
                  int k= emit(pair<string, Entry*>("&", lookup("&")), $1->place, $3->place, t1, -1);
                  $$->place = t1;
                  $$->nextlist={};
                  //====================================//	
				  
               }
               else {
                 yyerror("Error :Invalid operands to the &");
               }
                 if($1->init_flag==1 && $3->init_flag==1) $$->init_flag=1;
          }
  ;

exclusive_or_expression
  : and_expression   { $$ = $1;}
  | exclusive_or_expression '^' and_expression  {
           $$ = non_term_symb("^", NULL, $1, $3);
               char* a = bitwise_expr($1->node_type,$3->node_type);
               if(a){
                  if(!strcmp(a,"true")) { $$->node_type = "bool"; }
                  else{   $$->node_type = "long long";}
				  //===========3AC======================//
                  qid t1 = getTmpSym($$->node_type);
                  int k = emit(pair<string, Entry*>("^", lookup("^")), $1->place, $3->place, t1, -1);
                  $$->place = t1;
                  $$->nextlist={};
                  //====================================//
               }
               else {
                 yyerror("Error :Invalid operands to the ^");
               }
                 if($1->init_flag==1 && $3->init_flag==1) $$->init_flag=1;

        }
  ;

inclusive_or_expression
	: exclusive_or_expression								{$$ = $1;}
	| inclusive_or_expression '|' exclusive_or_expression	{$$ = non_term_symb("|", NULL, $1, $3);
								char* a = bitwise_expr($1->node_type,$3->node_type);
								if(a){
									if(!strcmp(a,"true")) { $$->node_type = "bool"; }
									else{   $$->node_type = "long long";}
									//===========3AC======================//
                           			qid t1 = getTmpSym($$->node_type);
                           			int k =  emit(pair<string, Entry*>("|", lookup("|")), $1->place, $3->place, t1, -1);
                           			$$->place = t1;
                           			$$->nextlist={};
                       				//====================================//
						
								}
								else {
									yyerror("Error :Invalid operands to the |");
								}
									if($1->init_flag==1 && $3->init_flag==1) $$->init_flag=1;
							
								}
	;

//M1
//  : logical_and_expression AND_OP {
//                        if($1->truelist.begin()==$1->truelist.end()){
//                            int k = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("IF", lookup("if")), $1->place, pair<string, Entry*>("", NULL ),0);
//                            int k1 = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),0);
//                            $1->truelist.push_back(k);
//                            $1->falselist.push_back(k1);
//
//                        }
//                        $$ = $1;
//  }
//  ;

M
 : %empty {
           $$ = getNextIndex();
 }
 ;
   
logical_and_expression
	: inclusive_or_expression								{$$ = $1;}
	| logical_and_expression AND_OP M inclusive_or_expression	{$$ = non_term_symb_2($2, $1, NULL, $4);
								$$->node_type == "bool";
								//===========3AC======================//
								if($1->truelist.begin()==$1->truelist.end()){
								int k = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("IF", lookup("if")), $1->place, pair<string, Entry*>("", NULL ),0);
								int k1 = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),0);
								$1->truelist.push_back(k);
								$1->falselist.push_back(k1);
								}

                            	if($4->truelist.begin()==$4->truelist.end()){
                                	int k2 = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("IF", lookup("if")), $4->place, pair<string, Entry*>("", NULL ),0);
                                	int k3 = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),0);
                                	$4->truelist.push_back(k2);
                                	$4->falselist.push_back(k3);
                        		}
                           		backPatch($1->truelist,$3);
                           		$$->truelist = $4->truelist;
                           		//$1->falselist.merge($4->falselist);
								   merging($1->falselist, $4->falselist);
                           		$$->falselist = $1->falselist;
                           		$$->nextlist ={};
                       			//====================================//
								if($1->init_flag==1 && $4->init_flag==1) $$->init_flag=1;
								}
	;

//M2
//  : logical_or_expression OR_OP {
//                        if($1->truelist.begin()==$1->truelist.end()){
//                            int k = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("IF", lookup("if")), $1->place, pair<string, Entry*>("", NULL ),0);
//                            int k1 = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),0);
//                            $1->truelist.push_back(k);
//                            $1->falselist.push_back(k1);
//
//                        }
//                        $$ = $1;
//  }
//  ;

logical_or_expression
	: logical_and_expression								{$$ = $1;}
	| logical_or_expression OR_OP M logical_and_expression	{$$ = non_term_symb_2($2, $1, NULL, $4);
								//$$ = non_term_symb_2("||", $1,NULL, $3);
								if($1->init_flag==1 && $4->init_flag==1) $$->init_flag=1;
								$$->node_type == "bool";
								//===========3AC======================//
								if($1->truelist.begin()==$1->truelist.end()){
									int k = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("IF", lookup("if")), $1->place, pair<string, Entry*>("", NULL ),0);
									int k1 = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),0);
									$1->truelist.push_back(k);
									$1->falselist.push_back(k1);
								}
                         		if($4->truelist.begin()==$4->truelist.end()){
                                	int k2 = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("IF", lookup("if")), $4->place, pair<string, Entry*>("", NULL ),0);
                                	int k3 = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),0);
                                	$4->truelist.push_back(k2);
                                	$4->falselist.push_back(k3);
                        		}
                         		backPatch($1->falselist, $3);
                         		$$->falselist = $4->falselist;
                         		//$1->truelist.merge($4->truelist);
								 merging($1->truelist, $4->truelist);
                         		$$->truelist = $1->truelist;
                         		$$->nextlist = {};
                        		//====================================//
								}
	;

M3
  : logical_or_expression '?' {
                        if($1->truelist.begin()==$1->truelist.end()){
                            int k = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("IF", lookup("if")), $1->place, pair<string, Entry*>("", NULL ),0);
                            int k1 = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),0);
                            $1->truelist.push_back(k);
                            $1->falselist.push_back(k1);

                        }
                        $$ = $1;
  }
  ;

N
 : %empty {
                emit(pair<string, Entry*>("=", lookup("=")), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), -1);
                $$ = emit(pair<string, Entry*>("GOTO", lookup("goto")), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), 0);
 }
 ;

conditional_expression
	: logical_or_expression												{$$ = $1;}
	| M3 M expression ':' N conditional_expression	{$$ = non_term_symb_2("logical_expr ? expr : conditional_expr", $1, $3, $6);
										$$->real_value = -11;
										char* a = conditional_expr($3->node_type,$6->node_type);
										if(a){
											string tmp_str(a);
											$$->node_type = "int";
											//--------------------3AC--------------------------//
                    						qid t = getTmpSym($$->node_type);
                    						emit(pair<string, Entry*>("=", lookup("=")), $6->place, pair<string, Entry*>("", NULL), t, -1);
                    						int k = emit(pair<string, Entry*>("GOTO", lookup("goto")), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), 0);
                    						backPatch($1->truelist , $2);
                    						backPatch($1->falselist , $5+1);
                    						setId1($5-1 , $3->place);
                    						setResult($5-1 , t);
                    						$$->nextlist = $3->nextlist;
                    						$$->nextlist.push_back($5);
                    						$$->nextlist.push_back(k);
                    						$$->place = t;
                 							//--------------------------------------------------//
										}
										else{

											yyerror("Error :Type Error in ternary statement");
										}
										if($1->init_flag==1 && $3->init_flag==1 && $6->init_flag==1) $$->init_flag=1;																		
										}
	;

assignment_expression
	: conditional_expression										{$$ = $1;}
	| unary_expression assignment_operator assignment_expression	{$$ = non_term_symb_2($2, $1, NULL, $3);
									char* a = assign_expr($1->node_type,$3->node_type,$2);
									if(a){
											if(!strcmp(a,"true")){ $$->node_type = $1->node_type;
											}
											if(!strcmp(a,"warning")){ $$->node_type = $1->node_type;
												yyerror("Warning : Incompatible pointer type assignment");
											}
										//-------------3AC------------------------------------//
                      					int k;
		     							if(!strcmp($2,"=") || !strcmp($2,"+=") || !strcmp($2,"-=") || !strcmp($2,"*=") || !strcmp($2,"/=")) k= assignmentExpression($2, $$->node_type,$1->node_type, $3->node_type, $1->place, $3->place)	;
		     							else assignment2($2, $$->node_type,$1->node_type, $3->node_type, $1->place, $3->place);
                       					$$->place = $1->place;
										backPatch($3->nextlist, k);
                       					//-------------------------------------------------------//		
									}
									else{ yyerror("Error : Incompatible types when assigning type \'%s\' to \'%s\' ",($1->node_type).c_str(),($3->node_type).c_str()); }
									if($1->expr_type==3){ if($3->init_flag==1) update_init_flag($1->node_key); }
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
	| expression ',' M assignment_expression	{$$ = non_term_symb("expression ','", NULL, $1, $4);$$->node_type = "void";
											//--------------3AC--------------------//
                    						backPatch($1->nextlist,$3);
                    						$$->nextlist = $4->nextlist;
                 							//-------------------------------------//
											}
	;

constant_expression
	: conditional_expression	{$$ = $1;}
	;

declaration
	: declaration_specifiers ';' {type_name="";$$=$1;}
	| declaration_specifiers init_declarator_list ';'	{type_name="";$$ = non_term_symb("declaration", NULL, $1, $2);
														//----------------3AC-----------------------//
                                                        $$->nextlist = $2->nextlist;
                                                      	//-----------------------------------------//	
														}
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
	| init_declarator_list ',' M init_declarator	{
												$$ = non_term_symb("init_declaration_list", NULL, $1, $4);
												//-----------3AC------------------//
                                                 backPatch($1->nextlist, $3);
                                                 $$->nextlist = $4->nextlist;
                                               //--------------------------------//
												}
	;

init_declarator
	: declarator{
		$$ = $1;
		if($1->expr_type==1){ 
			const char *t=new char();
			t = ($1->node_type).c_str();
        	const char *key =new char();
			key = ($1->node_key).c_str();
        	if(scopeLookup($1->node_key)){
                yyerror("Error : \'%s\' already declared",key);
        	}else if($1->node_type=="void"){
        	    yyerror("Error : void declaration \'%s\'",key);
        	}else {  
				insert_symbol(*curr,key,t,$1->size,0,0);

			}
        }
	}
	| declarator '=' M initializer	{
		
		$$ = non_term_symb("=", NULL, $1, $4);
		if($1->expr_type==1||$1->expr_type==15){ 
			const char *t=new char();
			t = ($1->node_type).c_str();
            const char *key =new char();
			key = ($1->node_key).c_str();
        if(scopeLookup($1->node_key)){
			yyerror("Error : \'%s\' already declared",key);
            }else if($1->node_type=="void"){
                 yyerror("Error : void declaration \'%s\'",key);
            }
            else { 
				if($$->expr_type==15) { 
					insert_symbol(*curr,key,t,($4->expr_type*$1->integer_value),0,1); 
				}
                insert_symbol(*curr,key,t,$1->size,0,1);
				//----------------- 3AC ------------------------//
                char *a = validAssign($1->node_type, $4->node_type);
            	if(a){
                    if(strcmp(a,"true")){ yyerror("Warning: Invalid assignment of \'%s\' to \'%s\' ",$1->node_type.c_str(),$4->node_type.c_str()); }
                    $1->place = pair<string, Entry*>($1->node_key, lookup($1->node_key));
		            assignmentExpression("=", $1->node_type,$1->node_type, $4->node_type, $1->place, $4->place);
                    $$->place = $1->place;
                    backPatch($1->nextlist, $3);
                    $$->nextlist = $4->nextlist;
                }
                else { yyerror("Error: Invalid assignment of \'%s\' to \'%s\' ",$1->node_type.c_str(),$4->node_type.c_str());}
                $$->place = pair<string, Entry*>($1->node_key, lookup($1->node_key));

                //-----------------------------------------------//
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
	: VOID							{if(type_name==""){string stmp($1); type_name = stmp;}
                   					else {string stmp($1);type_name = type_name+" "+stmp;}
									$$ = term_symb($1);}
	| CHAR							{if(type_name==""){string stmp($1); type_name = stmp;}
                   					else {string stmp($1);type_name = type_name+" "+stmp;}
									$$ = term_symb($1);}
	| SHORT							{if(type_name==""){string stmp($1); type_name = stmp;}
                   					else {string stmp($1);type_name = type_name+" "+stmp;}
									$$ = term_symb($1);}
	| INT							{if(type_name==""){string stmp($1); type_name = stmp;}
                   					else {string stmp($1);type_name = type_name+" "+stmp;}
									$$ = term_symb($1);}
	| LONG							{if(type_name==""){string stmp($1); type_name = stmp;}
                   					else {string stmp($1);type_name = type_name+" "+stmp;}
									$$ = term_symb($1);}
	| FLOAT							{if(type_name==""){string stmp($1); type_name = stmp;}
                   					else {string stmp($1);type_name = type_name+" "+stmp;}
									$$ = term_symb($1);}
	| DOUBLE						{if(type_name==""){string stmp($1); type_name = stmp;}
                   					else {string stmp($1);type_name = type_name+" "+stmp;}
									$$ = term_symb($1);}
	| SIGNED						{if(type_name==""){string stmp($1); type_name = stmp;}
                   					else {string stmp($1);type_name = type_name+" "+stmp;}
									$$ = term_symb($1);}
	| UNSIGNED						{if(type_name==""){string stmp($1); type_name = stmp;}
                   					else {string stmp($1);type_name = type_name+" "+stmp;}
									$$ = term_symb($1);}
	| struct_or_union_specifier		{if(type_name=="")type_name = $$->node_type;
                   					else type_name = type_name+" "+$$->node_type;
									$$ = $1;}
	| enum_specifier				{$$ = $1; yyerror("Implemention Error : Enum specifier not implemented. Sorry!!");}
	| TYPE_NAME						{if(type_name==""){string stmp($1); type_name = stmp;}
                   					else {string stmp($1);type_name = type_name+" "+stmp;}
									$$ = term_symb($1);}
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER E4 '{' struct_declaration_list '}'	{string tmp_str($2);
									$$ = non_term_symb("struct_or_union_specifier", $2, $1, $5);
									if(end_struct(tmp_str)){
									string stmp= "STRUCT_"+tmp_str; $$->node_type=stmp;}
									else yyerror("Error : struct \'%s\' is already defined\n", $2);
									}

	| struct_or_union E4 '{' struct_declaration_list '}'				{$$ = non_term_symb("struct_or_union_specifier", NULL, $1, $4);
											structCounter++;
											string tmp_str = to_string(structCounter);
											if(end_struct(tmp_str)){
											string stmp= "STRUCT_"+tmp_str; $$->node_type=stmp;}
											else yyerror("Error : struct \'%s\' is already defined\n", $2);
											}

	| struct_or_union IDENTIFIER									{$$ = non_term_symb("struct_or_union_specifier", $2, $1, NULL);
													string tmp_str($2);
													tmp_str = "STRUCT_" + tmp_str;
													if(struct_flag(tmp_str)) $$->node_type = tmp_str;
													else yyerror("Error : struct \'%s\' is not defined",$2);
													}
	;

E4
  : %empty {
           make_struct_table();
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
	: specifier_qualifier_list struct_declarator_list ';'	{$$ = non_term_symb("struct_declaration", NULL, $1, $2);type_name = "";}
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
				if(!insert_sym_struct($1->node_key, $1->node_type, $1->size, 0, 0)) yyerror(" : \'%s\' is already declared in the same struct", $1->node_key.c_str());}
	| ':' constant_expression {$$ = $2;}
	| declarator ':' constant_expression {$$ = non_term_symb("struct_declarator", NULL, $1, $3);
										if(!insert_sym_struct($1->node_key, $1->node_type, $1->size, 0, 1)) yyerror("Error : \'%s\' redeclared in the struct", $1->node_key.c_str());}
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
								
								if($2->expr_type==1){string stmp=$2->node_type+$1->node_type;$$->node_type=stmp;
									$$->node_key = $2->node_key;
									$$->expr_type=1;}
								if($2->expr_type==2){ func_name = $2->node_key; func_type = $2->node_type; }
								char* a = new char();
								strcpy(a,($$->node_type).c_str());
								$$->size = get_size(a);
								//------------------3AC---------------------------------//
                        		$$->place = pair<string, Entry*>($$->node_key, NULL);
                        		//-------------------------------------------------------//
								}
	| direct_declarator {$$ = $1;
						if($1->expr_type==2){ func_name=$1->node_key; 
							func_type = $1->node_type;
						}
						//------------------3AC---------------------------------//
                        $$->place = pair<string, Entry*>($$->node_key, NULL);
                        //-------------------------------------------------------//
						}
	;

direct_declarator
	: IDENTIFIER {$$=term_symb($1);
				//cout<<$1<<endl;
				$$->expr_type=1;string stmp($1);$$->node_key=stmp;
				if(type_name=="spec_less_func"){
					yyerror("Warning :return type of \'%s\' defaults to int",$1);
					type_name="int";
					$$->node_type=type_name;
				}
				else $$->node_type=type_name;
				char* a =new char();
                strcpy(a,type_name.c_str());
				$$->size = get_size(a);
				//------------------3AC---------------------------------//
                $$->place = pair<string, Entry*>($$->node_key, NULL);
                //-------------------------------------------------------//
				}
	| '(' declarator ')' {$$ = $2;
						if($2->expr_type==1){ 
							$$->expr_type=1;
                            $$->node_key=$2->node_key;
							//------------------3AC---------------------------------//
                            $$->place = pair<string, Entry*>($$->node_key, NULL);
                            //-------------------------------------------------------//
                            $$->node_type=$2->node_type;
						}
						}
	| direct_declarator '[' constant_expression ']' {$$ = non_term_symb("direct_declarator", NULL, $1, $3);
														//cout<<"hello\n";
														 if($1->expr_type==1){ $$->expr_type=1;
																$$->node_key=$1->node_key;
																string stmp=$1->node_type+"*";
																$$->node_type=stmp;
														}
														if($3->integer_value){ $$->size = $1->size * $3->integer_value; }
														else { char* a = new char();
																strcpy(a,($$->node_type).c_str());
																$$->size = get_size(a); 
															}

													}
										//DOUBTFULL}
	| direct_declarator '[' ']'    {$$ = square("direct_declarator", $1);
				     	if($1->expr_type==1){ $$->expr_type=1;
                                     	$$->node_key=$1->node_key;
                                     	string stmp=$1->node_type+"*";$$->node_type=stmp;}
					char* a = new char();
					strcpy(a,($$->node_type).c_str());
					$$->size = get_size(a);
					strcpy(a,($1->node_type).c_str());
					$$->expr_type=15;
					$$->integer_value=get_size(a);
					//------------------3AC---------------------------------//
                	$$->place = pair<string, Entry*>($$->node_key, NULL);
                    //-------------------------------------------------------//
					}

	| direct_declarator '(' E3 parameter_type_list ')' M {$$ = non_term_symb("direct_declarator", NULL, $1, $4);
							if($1->expr_type==1){ 
								$$->node_key=$1->node_key;
								$$->expr_type=2;
								$$->node_type=$1->node_type;
								insert_args($1->node_key,funcArguments);
								funcArguments="";
								char* a = new char();
								strcpy(a,($$->node_type).c_str());
								$$->size = get_size(a);
							}
							//------------------3AC---------------------------------//
                        	$$->place = pair<string, Entry*>($$->node_key, NULL);
                        	backPatch($4->nextlist, $6);
                        	if( !(($$->node_key == "odd" && tempodd == 0) || ($$->node_key == "even" && tempeven == 0)) ){string em =  "func " + $$->node_key+ " begin:";
                        	emit(pair<string , Entry*>(em, NULL), pair<string , Entry*>("", NULL),pair<string , Entry*>("", NULL),pair<string , Entry*>("", NULL),-2);}
                        	if($$->node_key == "odd" ){
                        	   tempodd = 1;
                        	}
                        	if($$->node_key == "even" ){
                        	   tempeven = 1;
                        	}
                        	//-------------------------------------------------------//
							}

	| direct_declarator '(' E3 identifier_list ')' 	{$$ = non_term_symb("direct_declarator", NULL, $1, $4);
							char* a = new char();
							$$->size = get_size(a);
							//------------------3AC---------------------------------//
                        	$$->place = pair<string, Entry*>($$->node_key, NULL);
                        	string em =  "func " + $$->node_key+ " begin:";
                        	emit(pair<string , Entry*>(em, NULL), pair<string , Entry*>("", NULL),pair<string , Entry*>("", NULL),pair<string , Entry*>("", NULL),-2);
                        	//-------------------------------------------------------//
							}

	| direct_declarator '(' E3 ')' 			{$$ = parentheses("direct_declarator", $1);
							if($1->expr_type==1){
								$$->node_key=$1->node_key;
								insert_args($1->node_key,"");
								$$->expr_type=2;
								funcArguments = "";
							}
							$$->node_type=$1->node_type;
							const char* a = new char();
							a = ($$->node_type).c_str();
							//------------------3AC---------------------------------//
                        	$$->place = pair<string, Entry*>($$->node_key, NULL);
                        	string em =  "func " + $$->node_key+ " begin:";
                        	emit(pair<string , Entry*>(em, NULL), pair<string , Entry*>("", NULL),pair<string , Entry*>("", NULL),pair<string , Entry*>("", NULL),-2);
                        	//-------------------------------------------------------//
							}
	;
E3
   :%empty                  {   type_name ="";
                          funcArguments = "";
                           paramTable();  }
    ;
pointer
	: '*' {$$=term_symb("*");$$->node_type="*";}
	| '*' type_qualifier_list {$$=non_term_symb("*",NULL,$2,NULL);$$->node_type="*";}
	| '*' pointer {$$=non_term_symb("*",NULL,$2,NULL);string stmp="*"+$2->node_type;$$->node_type=stmp;}
	| '*' type_qualifier_list pointer {$$=non_term_symb("*",NULL,$2,$3);string stmp="*"+$3->node_type;$$->node_type=stmp;}
	;

type_qualifier_list
	: type_qualifier {$$=$1;}
	| type_qualifier_list type_qualifier {$$=non_term_symb("type_qualifier_list",NULL,$1,$2);}
	;


parameter_type_list
	: parameter_list {$$=$1;}
	| parameter_list ',' ELLIPSIS {	funcArguments = funcArguments+",...";
					$$=non_term_symb("parameter_type_list",NULL,$1,term_symb("ELLIPSIS"));
					}
	;

parameter_list
	: parameter_declaration {$$=$1;}
	| parameter_list ',' M parameter_declaration {
												$$=non_term_symb("parameter_list",NULL,$1,$4);
												//----------------3AC--------------//
                                                backPatch($1->nextlist,$3);
                                                $$->nextlist=$4->nextlist;
                                                //---------------------------------//
												}
	;

parameter_declaration
	: declaration_specifiers declarator {type_name="";
			
          //paramTable();
         if($2->expr_type==1){
			 		 const char *t=new char();
					 t = ($2->node_type).c_str();
                     const char *key =new char();
					 key = ($2->node_key).c_str();
                  if(scopeLookup($2->node_key)){ yyerror("Error : %s is already declared",key);}
                   else {  insert_symbol(*curr,key,t,$2->size,0,1);}
                if(funcArguments=="")funcArguments=($2->node_type);
               else funcArguments= funcArguments+","+($2->node_type);
                     }
        $$=non_term_symb("parameter_declaration",NULL,$1,$2);}
	| declaration_specifiers abstract_declarator {$$=non_term_symb("parameter_declaration",NULL,$1,$2);type_name="";}
	| declaration_specifiers {$$=$1;type_name="";}
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
	| '{' initializer_list '}' {$$ = $2; string stmp= $2->node_type+"*"; $$->node_type=stmp;}
	| '{' initializer_list ',' '}' {
									$$ = non_term_symb("initializer", $3, $2 ,NULL);
									string stmp= $2->node_type+"*"; $$->node_type=stmp; $$->expr_type =$2->expr_type;
									//--------------3AC--------------------//
                                    $$->place = $2->place;
                                    $$->nextlist = $2->nextlist;
                                    //-------------------------------------//
								}
	;

initializer_list
	: initializer {$$ = $1;$$->expr_type=1;}
	| initializer_list ',' M initializer {
          $$ = non_term_symb("initializer_list", NULL, $1 ,$4);
          $$->node_type = $1->node_type;
           char* a =validAssign($1->node_type,$4->node_type);
            if(a){
                if(!strcmp(a,"true")){ ; }
                if(!strcmp(a,"warning")){ ;
                     yyerror("Warning : Incompatible pointer type assignment");
                     }
                 }
            else{ yyerror("Error : Incompatible types when initializing type \'%s\' to \'%s\' ",($1->node_type).c_str(),($4->node_type).c_str()); }
           $$->expr_type = $1->expr_type+1;
		   //--------------3AC--------------------//
            backPatch($1->nextlist, $3);
            $$->nextlist = $4->nextlist;
            //-------------------------------------//
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

M5
  : CASE constant_expression ':' {
                                  $$=$2;
                                //-----------3AC--------------------//
                                 qid t = getTmpSym("bool");
                                 int k = emit(pair<string, Entry*>("EQ_OP", lookup("\=\=")),pair<string, Entry*>("", NULL), $2->place, t, -1);
                                 int k1 = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("IF", lookup("if")), t, pair<string, Entry*>("", NULL ),0);
                                 int k2 = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),0);
                                 $$->caselist.push_back(k);
                                 $$->truelist.push_back(k1);
                                 $$->falselist.push_back(k2);
                               //-----------------------------------//


   }
  ;

labeled_statement
	: IDENTIFIER ':' M statement {
		$$ = non_term_symb("labeled_statement", NULL, term_symb($1), $4);
		//===========3AC======================//
        if(!gotoIndexStorage($1, $3)){
            yyerror("ERROR:\'%s\' is already defined", $1);
        }
		$$->nextlist = $4->nextlist;
        $$->caselist = $4->caselist;
        $$->continuelist = $4->continuelist;
        $$->breaklist = $4->breaklist;
        //=====================================//
	}
	| M5 M statement {
		$$ = non_term_symb_2("labeled_statement", term_symb("CASE"), $1, $3);
		//-----------3AC--------------------//
        backPatch($1->truelist, $2);
        //$3->nextlist.merge($1->falselist);
		merging($3->nextlist, $1->falselist);
        $$->breaklist = $3->breaklist;
        $$->nextlist = $3->nextlist;
        $$->caselist = $1->caselist;
        $$->continuelist=$3->continuelist;
        //-----------------------------------//
	}
	| DEFAULT ':' statement {
		$$ = non_term_symb("labeled_statement", NULL, term_symb("DEFAULT"), $3);
		//---------3AC-----------------------//
        $$->breaklist= $3->breaklist;
        $$->nextlist = $3->nextlist;
        $$->continuelist=$3->continuelist;
        //----------------------------------//
	}
	;

compound_statement
	: '{' '}' {func_flag=0;$$ = term_symb("{ }");}
	| E1  statement_list '}'  {if(blockSym){ string s($1);
                                    s=s+".csv";
                                    string u($1);
                                    //print_tables(curr,s);
                                    //update_table(u); blockSym--;
									
                                 } $$ = $2;
                               }
	| E1  declaration_list '}'  {if(blockSym){ string s($1);
                                    s=s+".csv";
                                    string u($1);
                                    //print_tables(curr,s);
                                    //update_table(u); blockSym--;
									
                                 } $$ = $2;
                               }
	| '{' declaration_list statement_list '}' {$$ = non_term_symb("compound_statement",NULL, $2,$3);}
	;

E1
    :  '{'  %prec SR      { if(func_flag==0) {symbol_count++;
                        file_name = /*string("symTableFunc")+to_string(func_symb)*/func_name+"Block"+to_string(symbol_count);
                        //scope=S_BLOCK;
                        //create_table(file_name,scope,string("12345"));
                        char * y=new char();
                        strcpy(y,file_name.c_str());
                        $$ = y;
                        //blockSym++;
                        }
                       func_flag=0;
              }

    ;

declaration_list
	: declaration {$$=$1;}
	| declaration_list M declaration {$$ = non_term_symb("declaration_list", NULL, $1, $3);
									//---------------3AC--------------------//
                                         backPatch($1->nextlist, $2);
                                         $$->nextlist = $3->nextlist;

										 //DECLARATION LIST IN TWO PLACES.
                                      //----------------------------------------//
									  }
	;

statement_list
	: statement {$$ = $1;}
	| statement_list M statement {$$ = non_term_symb("statement_list", NULL, $1, $3);
								//---------------3AC--------------------//
                                         backPatch($1->nextlist, $2);
                                         $$->nextlist = $3->nextlist;
                                         //$1->caselist.merge($3->caselist);
										 merging($1->caselist, $3->caselist);
                                         $$->caselist = $1->caselist;
                                         //$1->continuelist.merge($3->continuelist);
										 merging($1->continuelist, $3->continuelist);
                                         //$1->breaklist.merge($3->breaklist);
										 merging($1->breaklist, $3->breaklist);
                                         $$->continuelist = $1->continuelist;
                                         $$->breaklist = $1->breaklist;
                                      //----------------------------------------//
									  }
	;

expression_statement
	: ';' {$$ = term_symb(";");}
	| expression ';' {$$ = $1;}
	;

M4
  :  IF '(' expression ')' {
                        if($3->truelist.begin()==$3->truelist.end()){
                            int k = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("IF", lookup("if")), $3->place, pair<string, Entry*>("", NULL ),0);
                            int k1 = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),0);
                            $3->truelist.push_back(k);
                            $3->falselist.push_back(k1);

                        }
                        $$ = $3;
  }
  ;

GOTO_emit
   : %empty {

                           $$ = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),0);
   }
   ;

selection_statement
	: M4 M statement GOTO_emit ELSE M statement {
		$$ = non_term_symb_2("IF (expr) stmt ELSE stmt", $1, $3, $7);
		//----------3AC---------------------//
        backPatch($1->truelist, $2);
        backPatch($1->falselist, $6);
        $3->nextlist.push_back($4);
        //$3->nextlist.merge($7->nextlist);
		merging($3->nextlist, $7->nextlist);
        $$->nextlist=$3->nextlist;
        //$3->breaklist.merge($7->breaklist);
		merging($3->breaklist, $7->breaklist);
        $$->breaklist = $3->breaklist;
        //$3->continuelist.merge($7->continuelist);
		merging($3->continuelist, $7->continuelist);
        $$->continuelist = $3->continuelist;
        //-----------------------------------//
	}
	| M4 M statement %prec IFX {
		$$ = non_term_symb_2("IF (expr) stmt", NULL, $1, $3);
		//---------------3AC-------------------//
        backPatch($1->truelist, $2);
        //$3->nextlist.merge($1->falselist);
		merging($3->nextlist, $1->falselist);
        $$->nextlist= $3->nextlist;
        $$->continuelist = $3->continuelist;
        $$->breaklist = $3->breaklist;
        //------------------------------------//
	}
	| SWITCH '(' expression ')' statement{
		$$ = non_term_symb_2("SWITCH (expr) stmt", NULL, $3, $5);
		//--------------3AC---------------------------//
        setListId1($5->caselist, $3->place);
        //$5->nextlist.merge($5->breaklist);
		merging($5->nextlist, $5->breaklist);
        $$->nextlist= $5->nextlist;
        $$->continuelist= $5->continuelist;
        //---------------------------------------------//
	}
	;

M6
  :   expression  {
                        if($1->truelist.begin()==$1->truelist.end()){
                            int k = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("IF", lookup("if")), $1->place, pair<string, Entry*>("", NULL ),0);
                            int k1 = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),0);
                            $1->truelist.push_back(k);
                            $1->falselist.push_back(k1);

                        }
                        $$ = $1;
  }
  ;


M7
  :   expression_statement  {
                        if($1->truelist.begin()==$1->truelist.end()){
                            int k = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("IF", lookup("if")), $1->place, pair<string, Entry*>("", NULL ),0);
                            int k1 = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),0);
                            $1->truelist.push_back(k);
                            $1->falselist.push_back(k1);

                        }
                        $$ = $1;
  }
  ;

iteration_statement
	: WHILE '(' M M6 ')' M statement GOTO_emit {
		$$ = non_term_symb_2("WHILE (expr) stmt", NULL, $4, $7);
		//-----------3AC------------------//
        backPatch($4->truelist, $6);
        $7->continuelist.push_back($8);
        backPatch($7->continuelist, $3);
        backPatch($7->nextlist, $3);
        $$->nextlist = $4->falselist;
        //$$->nextlist.merge($7->breaklist);
		merging($$->nextlist, $7->breaklist);
        //--------------------------------//
	}
	| DO M statement  WHILE '(' M M6 ')' ';'{
		$$ = non_term_symb_2("DO stmt WHILE (expr)", NULL, $3, $7);
		//--------3AC-------------------------//
        backPatch($7->truelist, $2);
        backPatch($3->continuelist, $6);
        backPatch($3->nextlist, $6);
        //$7->falselist.merge($3->breaklist);
		merging($7->falselist, $3->breaklist);
        $$->nextlist = $7->falselist;
        //-----------------------------------//
	}
	| FOR '(' expression_statement M M7 ')' M statement GOTO_emit {
		$$ = non_term_symb_2("FOR (expr_stmt expr_stmt) stmt", $3, $5, $8);
		//-------------3AC-------------------//
        backPatch($3->nextlist, $4);
        backPatch($5->truelist, $7);
        //$5->falselist.merge($8->breaklist);
		merging($5->falselist, $8->breaklist);
        $$->nextlist = $5->falselist;
        //$8->nextlist.merge($8->continuelist);
		merging($8->nextlist, $8->continuelist);
        $8->nextlist.push_back($9);
        backPatch($8->nextlist, $4 );
        //------------------------------------//
	}
	| FOR '(' expression_statement M M7 M expression GOTO_emit ')' M statement GOTO_emit {
		$$ = non_term_symb_5("FOR (expr_stmt expr_stmt expr) stmt", NULL, $3, $5, $7, $11);
		//-------------3AC-------------------//
        backPatch($3->nextlist, $4);
        backPatch($5->truelist, $10);
        //$5->falselist.merge($11->breaklist);
		merging($5->falselist, $11->breaklist);
        $$->nextlist = $5->falselist;
        //$11->nextlist.merge($11->continuelist);
		merging($11->nextlist, $11->continuelist);
        $11->nextlist.push_back($12);
        backPatch($11->nextlist, $6 );
        $7->nextlist.push_back($8);
        backPatch($7->nextlist, $4);
        //------------------------------------//
	}
	;

jump_statement
	: GOTO IDENTIFIER ';' {$$ = non_term_symb("jump_statement", NULL, term_symb("GOTO"), term_symb($2));
	//-----------3AC---------------------//
    int k = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),0);
    gotoIndexPatchListStorage($2, k);
	//-----------------------------------//
	}
	| CONTINUE ';' {
		$$ = term_symb("continue");
		//-----------3AC---------------------//
        int k = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),0);
        $$->continuelist.push_back(k);
        //-----------------------------------//
	}
	| BREAK ';' {
		$$ = term_symb("break");
		//-----------3AC---------------------//
        int k = emit(pair<string, Entry*>("GOTO", lookup("goto")),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),0);
        $$->breaklist.push_back(k);
        //-----------------------------------//
	}
	| RETURN ';' {
		$$ = term_symb("return");
		//------------3AC----------------//
		emit(pair<string, Entry*>("RETURN", lookup("return")),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),-1);
        //------------------------------//
	}
	| RETURN expression ';' {
		$$ = non_term_symb("jump_statement", NULL, term_symb("return"), $2);
		//------------3AC----------------//
		emit(pair<string, Entry*>("RETURN", lookup("return")), $2->place, pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),-1);
        //------------------------------//
	}
	;

translation_unit
	: external_declaration {$$ = $1;}
	| translation_unit M external_declaration {
		$$ = non_term_symb("translation_unit", NULL, $1, $3);
		//----------3Ac----------------//
        backPatch($1->nextlist, $2);
        $$->nextlist = $3->nextlist;
        //------------------------------//
	}
	;

external_declaration
	: function_definition {type_name="";$$ = $1;}
	| declaration {type_name="";$$ = $1;}
	;

function_definition

	: declaration_specifiers declarator E2 declaration_list compound_statement
         {      type_name="";
                string s($3);
                string u = s+".csv";
                print_tables(curr,u);
                symbol_count=0;
               update_table(s);
                $$ = non_term_symb_4("function_definition", $1, $2, $4, $5, NULL);
				//--------------------3AC--------------------------------//
                if($5->real_value != -5){ string em =  "func end";
                emit(pair<string , Entry*>(em, NULL), pair<string , Entry*>("", NULL),pair<string , Entry*>("", NULL),pair<string , Entry*>("", NULL),-3);}
                //------------------------------------------------------//
         }
	| declaration_specifiers declarator E2 compound_statement  {
              type_name="";
              string s($3);string u =s+".csv";
              print_tables(curr,u);
              symbol_count=0;
              update_table(s);
              $$ = non_term_symb_2("function_definition", $1, $2, $4);
			  //--------------------3AC--------------------------------//
              if($4->real_value != -5){string em =  "func end";
              emit(pair<string , Entry*>(em, NULL), pair<string , Entry*>("", NULL),pair<string , Entry*>("", NULL),pair<string , Entry*>("", NULL),-3); }
              //------------------------------------------------------//
            }
	| X1 declarator E2 declaration_list compound_statement { $$ = non_term_symb_2("function_definition",$2,$4,$5);
															type_name="";
															string s($3);string u =s+".csv";
															print_tables(curr,u);
															symbol_count=0;
															update_table(s);
															//DOUBTFULL
													}
	| X1 declarator E2 compound_statement { $$ = non_term_symb_2("function_definition", $2,NULL,$4);
											type_name="";
											string s($3);string u =s+".csv";
											print_tables(curr,u);
											symbol_count=0;
											update_table(s);
															
									        //DOUBTFULL
									}
	;

E2
    : %empty                 { type_name="";scope = S_FUNC;
                                         func_flag = 1;
                                         func_symb++;
                                         file_name = func_name;//string("symTableFunc")+to_string(func_symb);
                                         create_table(file_name,scope,func_type);
                                         char* y= new char();
                                         strcpy(y,file_name.c_str());
                                         $$ = y;
       }
    ;

X1 : %empty {
		type_name="spec_less_func";
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
	
	func_name ="global_table";
	currArguments = "";
	table_initialize();
	
    yyin = fopen(argv[1], "r");
    ast = fopen(argv[3], "w");
    fprintf(ast, "digraph G {\n\tordering=out;\n");
	
    yyparse();
    fprintf(ast, "}\n");
    fclose(yyin);
    fclose(ast);

	file_name = "global_table.csv";
  	print_tables(curr,file_name);
  	print_func_args();
    return 0;
}

