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

string nameStruct=""; // for struct name


int errorCount=0;

int scope;

int symbol_count = 0;
int func_symb=0;
int blockSym=0;

int func_decl_only=0; // to check whether it is just a func declaration


int yylex(void);
void yyerror(char *s,...);

//#include "semanticCheck.h"
//#include "functions.h"
//#include "symbolTable.h"
#include "assembly.h"

extern int yylineno;
string file_name;
string func_type;
string func_name;
string args_defined;
string args_called;

string type_name="";
int structCounter=0;

// int tempodd;
// int tempeven;

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
%type <str> assignment_operator str_mark1 str_mark2 str_mark3 str_mark4

%start translation_unit

%left <str> ',' '^' '|' ';' '{' '}' '[' ']' '(' ')' '+' '-' '%' '/' '*' '.' '>' '<' SIZEOF
%right <str> '&' '=' '!' '~' ':' '?'

%type <ptr> multiplicative_expression additive_expression cast_expression primary_expression expression assignment_expression postfix_expression unary_expression shift_expression relational_expression equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_or_expression logical_and_expression conditional_expression constant_expression
%type <ptr> type_name argument_expression_list initializer_list M1 M2 M3 M4 M5 M6 M7
%type <ptr> unary_operator
%type <ptr> declaration declaration_specifiers
%type <ptr> init_declarator_list storage_class_specifier type_specifier type_qualifier
%type <ptr> init_declarator declarator initializer struct_or_union_specifier enum_specifier struct_or_union struct_declaration_list
%type <ptr> struct_declaration specifier_qualifier_list struct_declarator_list struct_declarator enumerator_list enumerator pointer
%type <ptr> direct_declarator type_qualifier_list parameter_type_list identifier_list parameter_list parameter_declaration
%type <ptr> abstract_declarator direct_abstract_declarator labeled_statement compound_statement expression_statement declaration_list
%type <ptr> selection_statement iteration_statement jump_statement external_declaration translation_unit function_definition statement statement_list
%type <number> M N N1

%%


primary_expression
	: IDENTIFIER			{$$ = term_symb($1);
							string tmp_id = convert_to_string($1);
							Entry* tmp_entry = lookup(tmp_id);
							if(tmp_entry == NULL){
								yyerror("Error : %s not declared",$1);
								string typ = "";
								$$->node_type = typ;
							}
							else{
								$$->init_flag = tmp_entry->init_flag;
								$$->node_type = tmp_entry->type;
								$$->node_key = tmp_id;
								$$->expr_type = "identifier";
								$$->place.first = tmp_id;
								$$->place.second = tmp_entry;	
							}
						}
	| CONSTANT				{$$ = term_symb($1->str);
							
							if($1->is_integer==1){
								string tmp_str = getstr_num_type($1->num_type);
								$$->init_flag=1;
								$$->node_type=tmp_str;
								$$->integer_value = $1->integer_value;
								$$->expr_type = "constant";
							}
							else{
								string tmp_str = getstr_num_type($1->num_type);
								$$->init_flag =1;
								$$->node_type=tmp_str;
								$$->expr_type = "constant";
							}
							$$->place.first = $1->str;
							$$->place.second = NULL;
						} 
	| STRING_LITERAL		{$$ = term_symb($1);
							$$->init_flag=1;
							string tmp_str = "";
							tmp_str.append("char*");
							$$->node_type=tmp_str;
							$$->place.first = $1;
							$$->place.second = NULL;
						}
	| '(' expression ')'	{$$ = $2;}
	;

postfix_expression
: primary_expression			{$$ = $1;}

| postfix_expression '[' expression ']'	{$$ = non_term_symb("[ ]", NULL, $1, $3);
							
									if($1->init_flag==1 && $3->init_flag==1){
										$$->init_flag=1;
									}
							char* deref_type =postfix_type1($1->node_type);// returns type removing the last "*"
							
							if(deref_type && int_flag($3->node_type)){
								string tmp_str(deref_type);
								$$->node_type=tmp_str;
								$$->place = newlabel_sym($$->node_type);
									
								if(deref_type[0]=='S'){
									//means $1 is struct type
									string tmp(deref_type);
									$$->place.second->struct_size=struct_size_map[tmp];
									$$->place.second->is_struct=1;
									
								}

                                if($3->place.second!=NULL){
									//means index is not a const number
									$$->place.second->size = $3->place.second->offset;
                                										
									if($1->place.second->dim==0){
										$$->place.second->off=$3->place.second->offset;//loaction of i in a[i][j]
									}
									else{
										$$->place.second->off=$1->place.second->off; //loaction of i in a[i][j]
									}
									
									$$->place.second->col=$1->place.second->col;

									$$->place.second->offset = $1->place.second->offset;
									$$->place.second->is_array=1;
								}
								else{
									//means const number
									$$->place.second->size=stoi($3->place.first);
									if($1->place.second->dim==0){
										$$->place.second->off=stoi($3->place.first);// i in a[i][j]
									}
									else{
										$$->place.second->off=$1->place.second->off; // i in a[i][j]
									}
									$$->place.second->col=$1->place.second->col;

									$$->place.second->offset=$1->place.second->offset;
									$$->place.second->is_array=2;
								}
								$$->place.second->dim=$1->place.second->dim+1;
                                $$->place.second->init_flag = 1;

							}
							else if(!int_flag($3->node_type)){
								yyerror("Error : array index not a int");
							}
							else{
								yyerror("Error : array indexed with more indices than its dimension");
							}
							}																
															
| postfix_expression '(' ')'	{$$ = $1;
							if($1->init_flag){
								$$->init_flag=1;
							}
							char* type_func = postfix_type2($1->node_type);
							if(type_func ==  NULL){
								yyerror("Error : Invalid Function call");
							}
							else{
								string tmp_str(type_func);
								$$->node_type = tmp_str;
								string get_args = args_map[$1->node_key];// get arguments
								pair <string, Entry*> newlabel = newlabel_sym($$->node_type);
								emit(pair<string, Entry*>("return place", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), newlabel, -1);
								emit(pair<string, Entry*>("CALL", NULL), $1->place, pair<string, Entry*>("0", NULL), newlabel, -1);
								$$->place = newlabel;
								if(get_args.length()){
									yyerror("Error : \'%s\' Invalid function call. Too many arguments",($1->node_key).c_str());
								}
							}	
							args_called="";													
						}

| postfix_expression '(' argument_expression_list ')'	{$$ = non_term_symb("postfix_expression", NULL, $1, $3);
							if($3->init_flag==1&&$1->init_flag){
								$$->init_flag=1;
							}
							char* type_func = postfix_type2($1->node_type);
							if(type_func == NULL){
								yyerror("Error : Invalid Function call");
							}
							else {
								string tmp_str(type_func);
								$$->node_type = tmp_str;
								if($1->expr_type == "identifier"){
									string get_args = args_map[$1->node_key];// get arguments
									vector<string> vect_called;
									vector<string> vect_get;
									string delim = ",";
									int index_called = 1;
									int index_get = 1;
									
									while(index_called != -1){
										index_called  =  args_called.find_first_of(delim);
										string tmp = "";
										if(index_called  == -1){
											tmp = args_called;
										}
										else{
											tmp = args_called.substr(0,index_called); 
											args_called = args_called.substr(index_called+1);
										}
										vect_called.push_back(tmp);
									}

									while(index_get != -1){
										index_get  = get_args.find_first_of(delim);
										string tmp = "";
										if(index_get ==  -1){
											tmp = get_args;
										}
										else{
											tmp = get_args.substr(0,index_get);	
											get_args = get_args.substr(index_get +1);
										}
										vect_get.push_back(tmp);
									}

									int size1 = vect_called.size();
									int size2 = vect_get.size();

									if(vect_get[size2-1] == "..."){
										if(size2 - size1 > 1){
											yyerror("Error : Too few arguments for the function \'%s\'\n    \'%s %s\( %s \)\'",($1->node_key).c_str(),($$->node_type).c_str(),($1->node_key).c_str(),get_args.c_str());
										}
										else{
											for(int i=0;i<size2-1;i++){
												string arg_call = vect_called[i];
												string arg_get = vect_get[i];
												int valid = compatible(arg_call,arg_get);
												if(valid == 0){
													yyerror("Warning : Passing argument %d of \'%s\' from incompatible pointer type.\n Note : expected \'%s\' but argument is of type \'%s\'\n     \'%s %s\( %s \)\'",i+1,($1->node_key).c_str(),arg_get.c_str(),arg_call.c_str(),($$->node_type).c_str(),($1->node_key).c_str(),get_args.c_str());
												}
												else if(valid == -1){
													yyerror("Error : Incompatible argument type %d of \'%s\' .\n Expected \'%s\' but argument is of type \'%s\'\n     \'%s %s\( %s \)\'",i+1,($1->node_key).c_str(),arg_get.c_str(),arg_call.c_str(),($$->node_type).c_str(),($1->node_key).c_str(),get_args.c_str());
												}
											}
										}
									}

									else{
										if(size1 < size2){
											yyerror("Error : Too few arguments for the function \'%s\'\n    \'%s %s\( %s \)\'",($1->node_key).c_str(),($$->node_type).c_str(),($1->node_key).c_str(),get_args.c_str());
										}
										else if(size1 > size2){
											yyerror("Error : Too many arguments for the function \'%s\'\n    \'%s %s\( %s \)\'",($1->node_key).c_str(),($$->node_type).c_str(),($1->node_key).c_str(),get_args.c_str());
										}
										else{
											for(int i=0;i<size2;i++){
												string arg_call = vect_called[i];
												string arg_get = vect_get[i];
												int valid = compatible(arg_call,arg_get);
												if(valid == 0){
													yyerror("Warning : Passing argument %d of \'%s\' from incompatible pointer type.\n Note : expected \'%s\' but argument is of type \'%s\'\n     \'%s %s\( %s \)\'",i+1,($1->node_key).c_str(),arg_get.c_str(),arg_call.c_str(),($$->node_type).c_str(),($1->node_key).c_str(),get_args.c_str());
												}
												else if(valid == -1){
													yyerror("Error : Incompatible argument type %d of \'%s\' .\n Expected \'%s\' but argument is of type \'%s\'\n     \'%s %s\( %s \)\'",i+1,($1->node_key).c_str(),arg_get.c_str(),arg_call.c_str(),($$->node_type).c_str(),($1->node_key).c_str(),get_args.c_str());
												}
											}
										}
									}
									string size1_str = to_string(size1 + 1);
                  					pair <string, Entry*> newlabel = newlabel_sym($$->node_type);
                  					emit(pair<string, Entry*>("return place", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), newlabel, -1);
                  					emit(pair<string, Entry*>("CALL", NULL), $1->place, pair<string, Entry*>(size1_str, NULL), newlabel, -1);
                  					$$->place = newlabel;
								}
							}
								args_called="";
							}
	| postfix_expression '.' IDENTIFIER			{$$ = non_term_symb(" . ", NULL, $1, term_symb($3));
												if($1->init_flag){
													$$->init_flag=1;
												}
												string tmp_str($3);
												if(struct_table_map.find($1->node_type) == struct_table_map.end()){
													yyerror("Error : Invalid operator \'.\' on \'%s\'", $1->node_key.c_str() );
												}
												else if((*struct_table_map[$1->node_type]).find(tmp_str) == (*struct_table_map[$1->node_type]).end()){
													yyerror("Error : \'%s\' does not have member \'%s\'", $1->node_key.c_str() ,$3);
												}
												else{
													Entry* struct_entry = (*(struct_table_map[$1->node_type]))[tmp_str];
													string stmp = struct_entry->type;
													$$->node_type=stmp;
													$$->place = newlabel_sym($$->node_type);
													$$->place.second->size=struct_entry->offset;
													$$->place.second->offset=$1->place.second->offset;
													$$->place.second->is_struct=1;

													if($1->place.second->is_array>0){
														$$->place.second->is_struct_array=$1->place.second->is_array; 
														$$->place.second->off=$1->place.second->size; // load the i's val/offset in the expr a[i].val;
														$$->place.second->struct_size=$1->place.second->struct_size;
													}
												}

												string tmp_key = $1->node_key;
												tmp_key.append(".");
												tmp_key.append(tmp_str); 
												$$->node_key=tmp_key;
												
												
											}

	| postfix_expression PTR_OP IDENTIFIER		{$$ = non_term_symb("->", NULL, $1, term_symb($3));
												string tmp_str($3);
												if($1->init_flag){
													$$->init_flag=1;
												}
												char *deref_type = postfix_type1($1->node_type);
												if(deref_type==NULL){
													yyerror("Error :Invalid operator  \'%s\' on \'%s\'", $2, $1->node_key.c_str() );
												}
												else{
													string deref_str=convert_to_string(deref_type);
													if(struct_table_map.find(deref_str) == struct_table_map.end()){
														yyerror("Error : Invalid operator \'.\' on \'%s\'", $1->node_key.c_str() );
													}

													else if((*struct_table_map[deref_str]).find(tmp_str) == (*struct_table_map[deref_str]).end()){
														yyerror("Error : \'%s\' does not have member \'%s\'", $1->node_key.c_str() ,$3);
													}

													else{
														Entry* struct_entry = (*(struct_table_map[deref_str]))[tmp_str];
														string stmp = struct_entry->type;
														$$->node_type=stmp;
														$$->place = newlabel_sym($$->node_type);
														$$->place.second->size=struct_entry->offset;
														$$->place.second->offset=$1->place.second->offset;
														$$->place.second->is_struct=2;
													}

													string tmp_key = $1->node_key;
													tmp_key.append("->");
													tmp_key.append(tmp_str); 
													$$->node_key=tmp_key;
												}
											}

	| postfix_expression INC_OP					{$$=  non_term_symb("++", NULL,$1, NULL);
												if($1->init_flag==1){
													$$->init_flag=1;
												}
												if(int_flag($1->node_type) == false){
													yyerror("Error : \'%s\' not defined for this type",$2);
												}
												else{
													$$->node_type =$1->node_type;//tmp_str;
													$$->integer_value = $1->integer_value +1;
                  									string op = "S++";
													string op2 = "";
													set_place2($$,$1,op,op2);
												}
											}

	| postfix_expression DEC_OP					{$$=  non_term_symb("--", NULL,$1, NULL);
												if($1->init_flag==1){
													$$->init_flag =1;
												}
												if(int_flag($1->node_type) == false){
													yyerror("Error : \'%s\' not defined for this type",$2);
												}
												else{
													$$->node_type =$1->node_type;//tmp_str;
													$$->integer_value = $1->integer_value - 1;
                  									string op = "S--";
													string op2 = "";
													set_place2($$,$1,op,op2);
												}
											}
	;

argument_expression_list
	: assignment_expression									{$$ = $1;
															if($1->init_flag==1){
																$$->init_flag = 1;
															}
															args_called = $1->node_type;
                											if($$->place.second == NULL && $$->node_type == "char*"){
																//constant string
                											  	emit(pair<string, Entry*>("param", NULL), $$->place, pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), -4);
                											}
                											else emit(pair<string, Entry*>("param", NULL), $$->place, pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), -1);
														}
	| argument_expression_list ',' assignment_expression	{$$ = non_term_symb($2,NULL,$1, $3);
								if($1->init_flag == 1 && $3->init_flag==1){
									$$->init_flag=1;
								}
								args_called.append(",");
								args_called.append($3->node_type);
             					if($3->place.second == NULL && $3->node_type == "char*"){
             					     emit(pair<string, Entry*>("param", NULL), $3->place, pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), -4);
             					}
             					else emit(pair<string, Entry*>("param", NULL), $3->place, pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), -1);
								}
	;

unary_expression
	: postfix_expression				{$$ = $1;}
	| INC_OP unary_expression			{$$ = non_term_symb("++", NULL, NULL, $2);
							if($2->init_flag == 1 ){
								$$->init_flag=1;
							}
							if(int_flag($2->node_type) == false){
								yyerror("Error : \'%s\' not defined for this type",$1);
							}
							else{
								string tmp_str($2->node_type);
								$$->node_type = tmp_str;
								$$->integer_value = $2->integer_value +1;
								string op = "++P";
								string op2 = "";
								set_place2($$,$2,op,op2);
							}
						}
	| DEC_OP unary_expression			{$$ = non_term_symb("--", NULL, NULL, $2);
							if($2->init_flag == 1 ){
								$$->init_flag=1;
							}
							if(int_flag($2->node_type) == false){
								yyerror("Error : \'%s\' not defined for this type",$1);
							}
							else{
								string tmp_str($2->node_type);
								$$->node_type = tmp_str;
								$$->integer_value = $2->integer_value +1;
                  				string op = "--P";
								string op2 = "";
								set_place2($$,$2,op,op2);
							}		
							}
	| unary_operator cast_expression	{$$ = non_term_symb("unary_expression", NULL, $1, $2);
						if( $2->init_flag==1){
							$$->init_flag=1;
						}
						$$->integer_value = $2->integer_value;
						char* un_type = unary_type($1->name, $2->node_type);
						if(un_type == NULL){
							yyerror("Error : Inconsistent type  with operator %s", $1->name.c_str());
						}
						else{
							string tmp_str(un_type);
							$$->node_type= tmp_str;
                  			pair <string, Entry*> newlabel = newlabel_sym($$->node_type);
                  			emit($1->place, $2->place, pair<string, Entry*>("", NULL), newlabel, -1);
                  			$$->place = newlabel;
						}
					}
	| SIZEOF unary_expression			{$$ = non_term_symb($1, NULL, NULL, $2);
										string tmp_str = "";
										tmp_str.append("int");
										$$->node_type = tmp_str;
										$$->init_flag=1;
                  						string op = "SIZEOF";
										string op2 = "";
										set_place2($$,$2,op,op2);
										}
	| SIZEOF '(' type_name ')'			{$$ = non_term_symb($1, NULL, NULL, $3);
										string tmp_str = "";
										tmp_str.append("int");
										$$->node_type = tmp_str;
										$$->init_flag=1;
                						string op = "SIZEOF";
										string op2 = "";
										set_place2($$,$3,op,op2);
										}
	;

unary_operator
	: '&'	{$$ = term_symb("unary&");
			$$->name="&";
			$$->place.first = "unary&";
			$$->place.second = NULL;
			}
	| '*'	{$$ = term_symb("*");
			$$->name="*";
			$$->place.first = "unary*";
			$$->place.second = NULL;
			}
	| '+'	{$$ = term_symb("+");
			$$->name="+";
			$$->place.first = "unary+";
			$$->place.second = NULL;
			}
	| '-'	{$$ = term_symb("-");
			$$->name="-";
			$$->place.first = "unary-";
			$$->place.second = NULL;
			}
	| '~'	{$$ = term_symb("~");
			$$->name="~";
			$$->place.first = "~";
			$$->place.second = NULL;
			}
	| '!'	{$$ = term_symb("!");
			$$->name="!";
			$$->place.first = "!";
			$$->place.second = NULL;
			}
	;

cast_expression
	: unary_expression					{$$ = $1;}
	| '(' type_name ')' cast_expression	{$$ = non_term_symb("cast_expression", NULL, $2, $4);
						$$->node_type = $2->node_type;
        				if($4->init_flag==1){
							$$->init_flag=1;
						}
						string op = $4->node_type;
						op.append("to");
						op.append($$->node_type);
						string op2 = ",";
						set_place2($$,$4,op,op2);
					}
	;

multiplicative_expression
	: cast_expression								{$$ = $1;}

	| multiplicative_expression '*' cast_expression{
			$$ = non_term_symb("*", NULL, $1, $3);
			if($1->init_flag==1 && $3->init_flag==1){
				$$->init_flag=1;
			}
			int mult_type = multiplicative_type1($1->node_type, $3->node_type);
			if(mult_type == -1){
				yyerror("Error : Incompatible type for \'*\'");
			}
			else{
				int k;
				if(mult_type == 0){
					$$->node_type = "int";
                  	string op = "*int";
					set_place($$,$1,op,$3);
				}
				else if (mult_type == 1){
					$$->node_type = "float";
                  	pair <string, Entry*> newlabel = newlabel_sym($$->node_type);

                  	if(int_flag($1->node_type)){
                  	      pair <string, Entry*> newlabel2 = newlabel_sym($$->node_type);
                  	      emit(pair<string, Entry*>("inttoreal",NULL),$1->place,pair<string, Entry*>("",NULL),newlabel2,-1);
                  	      k=emit(pair<string, Entry*>("*real", NULL), newlabel2, $3->place, newlabel, -1);
                  	}
                  	else if(int_flag($3->node_type)){
                  	      pair <string, Entry*> newlabel2 = newlabel_sym($$->node_type);
                  	      emit(pair<string, Entry*>("inttoreal",NULL),$3->place,pair<string, Entry*>("",NULL),newlabel2,-1);
                  	      k=emit(pair<string, Entry*>("*real", NULL), $1->place, newlabel2, newlabel, -1);
                  	}
                  	else {
                  	      k=emit(pair<string, Entry*>("*real", NULL), $1->place, $3->place, newlabel, -1);
                  	}
					
                  	$$->place = newlabel;
				}
			}
			
		}
	| multiplicative_expression '/' cast_expression	{$$ = non_term_symb("/", NULL, $1, $3);
														if($1->init_flag==1 && $3->init_flag==1){
															$$->init_flag=1;
														}
														if ($3->integer_value != 0)
															$$->integer_value = $1->integer_value/ $3->integer_value;
														int mult_type = multiplicative_type2($1->node_type, $3->node_type);
														if(mult_type == -1){
															yyerror("Error : Incompatible type for \'/\'");
														}
														else{
															int k;
															if(mult_type == 0){
																$$->node_type = "int";
                  												string op = "/int";
																set_place($$,$1,op,$3);
															}
															else if (mult_type == 1){
																$$->node_type = "float";
                  												pair <string, Entry*> newlabel = newlabel_sym($$->node_type);

                  												if(int_flag($1->node_type)){
                  												      pair <string, Entry*> newlabel2 = newlabel_sym($$->node_type);
                  												      emit(pair<string, Entry*>("inttoreal",NULL),$1->place,pair<string, Entry*>("",NULL),newlabel2,-1);
                  												      k=emit(pair<string, Entry*>("/real", NULL), newlabel2, $3->place, newlabel, -1);
                  												}
                  												else if(int_flag($3->node_type)){
                  												      pair <string, Entry*> newlabel2 = newlabel_sym($$->node_type);
                  												      emit(pair<string, Entry*>("inttoreal",NULL),$3->place,pair<string, Entry*>("",NULL),newlabel2,-1);
                  												      k=emit(pair<string, Entry*>("/real", NULL), $1->place, newlabel2, newlabel, -1);
                  												}
                  												else {
                  												      k=emit(pair<string, Entry*>("/real", NULL), $1->place, $3->place, newlabel, -1);
                  												}
                  												$$->place =newlabel;
															}
														}
													}

	| multiplicative_expression '%' cast_expression	{$$ = non_term_symb("%", NULL, $1, $3);
							if($1->init_flag==1 && $3->init_flag==1){
								$$->init_flag=1;
							}
							if($3->integer_value != 0) $$->integer_value = $1->integer_value % $3->integer_value;
							int mult_type = multiplicative_type3($1->node_type, $3->node_type);
							if(mult_type == -1){
								yyerror("Error : Incompatible type for \'%\'");
							}
							else{
								$$->node_type= "long long";
								//===========3AC======================//
                  				pair <string, Entry*> newlabel = newlabel_sym($$->node_type);
                  				int k =emit(pair<string, Entry*>("%", NULL), $1->place, $3->place, newlabel, -1);
                  				$$->nextlist={};
                  				$$->place = newlabel;

                  				//====================================//
							}

							}
	;

additive_expression
	: multiplicative_expression							{$$ = $1;}
	| additive_expression '+' multiplicative_expression	{$$ = non_term_symb("+", NULL, $1, $3);
								if($1->init_flag==1 && $3->init_flag==1){
									$$->init_flag=1;
								}
								$$->integer_value = $1->integer_value + $3->integer_value;
								int add_type = additive_type($1->node_type,$3->node_type);
								string op_type;
								if(add_type == -1){
									yyerror("Error : Incompatible type for \'+\'");
								}
								else{
									if(add_type == 0){
										$$->node_type="int";
										op_type = "+int";
									}
									else if(add_type == 1){
										$$->node_type="float";
										op_type = "+real";
									}
									else if(add_type == 2){
										$$->node_type = "char";
										op_type = "+int";
									}
									else if(add_type == 3){
										//pointer types
										$$->node_type = $1->node_type;
										op_type = "+" + $1->node_type;
									}
									else if(add_type == 4){
										//pointer types
										$$->node_type = $3->node_type;
										op_type = "+" + $3->node_type;
									}
                   					pair <string, Entry*> newlabel = newlabel_sym($$->node_type);
                   					if(int_flag($1->node_type) && real_flag($3->node_type)){
                   					     pair <string, Entry*> newlabel2 = newlabel_sym($$->node_type);
                   					     emit(pair<string, Entry*>("inttoreal",NULL),$1->place,pair<string, Entry*>("",NULL),newlabel2,-1);
                   					     emit(pair<string, Entry*>(op_type, NULL), newlabel2, $3->place, newlabel, -1);
                   					}
                   					else if(int_flag($3->node_type) && real_flag($1->node_type)){
                   					     pair <string, Entry*> newlabel2 = newlabel_sym($$->node_type);
                   					     emit(pair<string, Entry*>("inttoreal",NULL),$3->place,pair<string, Entry*>("",NULL),newlabel2,-1);
                   					     emit(pair<string, Entry*>(op_type, NULL), $1->place, newlabel2, newlabel, -1);
                   					}
                   					else {
                   					     emit(pair<string, Entry*>(op_type, NULL), $1->place, $3->place, newlabel, -1);
                   					}
                   					$$->place = newlabel;
								}
								
							}

	| additive_expression '-' multiplicative_expression	{$$ = non_term_symb("-", NULL, $1, $3);
								if($1->init_flag==1 && $3->init_flag==1){
									$$->init_flag=1;
								}
								$$->integer_value = $1->integer_value - $3->integer_value;
								int add_type = additive_type($1->node_type,$3->node_type);
								string op_type;
								if(add_type == -1){
									yyerror("Error : Incompatible type for \'-\'");
								}
								else{ 
									if(add_type == 0){
										$$->node_type="long long";
										op_type = "-int";
									}
									else if(add_type == 1){
										$$->node_type="long double";
										op_type = "-real";
									}
									else if(add_type == 2){
										$$->node_type = "char";
										op_type = "-int";
									}
									else if(add_type == 3){
										$$->node_type = $1->node_type;
										op_type = "-" + $1->node_type;
									}
									else if(add_type == 4){
										$$->node_type = $3->node_type;
										op_type = "-" + $3->node_type;
									}
                   					pair <string, Entry*> newlabel = newlabel_sym($$->node_type);
                   					if(int_flag($1->node_type) && real_flag($3->node_type)){
                   					     pair <string, Entry*> newlabel2 = newlabel_sym($$->node_type);
                   					     emit(pair<string, Entry*>("inttoreal",NULL),$1->place,pair<string, Entry*>("",NULL),newlabel2,-1);
                   					     emit(pair<string, Entry*>(op_type, NULL), newlabel2, $3->place, newlabel, -1);
                   					}
                   					else if(int_flag($3->node_type) && real_flag($1->node_type)){
                   					     pair <string, Entry*> newlabel2 = newlabel_sym($$->node_type);
                   					     emit(pair<string, Entry*>("inttoreal",NULL),$3->place,pair<string, Entry*>("",NULL),newlabel2,-1);
                   					     emit(pair<string, Entry*>(op_type, NULL), $1->place, newlabel2, newlabel, -1);
                   					}
                   					else {
                   					     emit(pair<string, Entry*>(op_type, NULL), $1->place, $3->place, newlabel, -1);

                   					}
                   					$$->place = newlabel;
								}
								
								}
	;

shift_expression
	: additive_expression							{$$ = $1;}
	| shift_expression LEFT_OP additive_expression	{$$ = non_term_symb_3($2, $1, NULL, $3);
							if($1->init_flag==1 && $3->init_flag==1){
								$$->init_flag=1;
							}
							if(int_flag($1->node_type) && int_flag($3->node_type)){
								$$->node_type = $1->node_type;
                          		string op = "<<";
								set_place($$,$1,op,$3);
							}
							else yyerror("Error : Invalid operands to <<");
							}

	| shift_expression RIGHT_OP additive_expression	{$$ = non_term_symb_3($2, $1, NULL, $3);
														if($1->init_flag==1 && $3->init_flag==1){
															$$->init_flag=1;
														}
														if(int_flag($1->node_type) && int_flag($3->node_type)){
															$$->node_type = $1->node_type;
                                 							string op = ">>";
															set_place($$,$1,op,$3);
														}
														else	yyerror("Error : Invalid operands to >>");
													}
	;

relational_expression
	: shift_expression								{$$ = $1;}
	| relational_expression '<' shift_expression	{$$ = non_term_symb("<", NULL, $1, $3);
							if($1->init_flag==1 && $3->init_flag==1){
								$$->init_flag=1;
							}
							int rel_type = relational_type($1->node_type,$3->node_type);
							if(rel_type == -1){
								yyerror("Error : invalid operands to <");
							}
							else{ 
								if(rel_type != 1){
									yyerror("Warning : Invalid Comparison : pointer and Integer");
								}
								$$->node_type = "bool";
                           		string op = "<";
								set_place($$,$1,op,$3);
							}	
						}

	| relational_expression '>' shift_expression	{$$ = non_term_symb(">", NULL, $1, $3);
							if($1->init_flag==1 && $3->init_flag==1){
								$$->init_flag=1;
							}
							int rel_type = relational_type($1->node_type,$3->node_type);
							if(rel_type == -1){
								yyerror("Error : invalid operands to >");
							}
							else{ 
								if(rel_type != 1){
									yyerror("Warning : Invalid Comparison : pointer and Integer");
								}
								$$->node_type = "bool";
                           		string op = ">";
								set_place($$,$1,op,$3);
							}
						}

	| relational_expression LE_OP shift_expression	{$$ = non_term_symb($2, NULL, $1, $3);
							if($1->init_flag==1 && $3->init_flag==1){
								$$->init_flag=1;
							}
							int rel_type = relational_type($1->node_type,$3->node_type);
							if(rel_type == -1){
								yyerror("Error : invalid operands to <=");
							}
							else{ 
								if(rel_type != 1){
									yyerror("Warning : Invalid Comparison : pointer and Integer");
								}
								$$->node_type = "bool";
                           		string op = "LE_OP";
								set_place($$,$1,op,$3);
							}
						}

	| relational_expression GE_OP shift_expression	{$$ = non_term_symb($2, NULL, $1, $3);
							if($1->init_flag==1 && $3->init_flag==1){
								$$->init_flag=1;
							}
							int rel_type = relational_type($1->node_type,$3->node_type);
							if(rel_type == -1){
								yyerror("Error : invalid operands to >=");
							}
							else{ 
								if(rel_type != 1){
									yyerror("Warning : Invalid Comparison : pointer and Integer");
								}
								$$->node_type = "bool";
                           		string op = "GE_OP";
								set_place($$,$1,op,$3);
							}
						}
	;

equality_expression
  : relational_expression   {$$ = $1;}
  | equality_expression EQ_OP relational_expression {$$ = non_term_symb_3("==", $1, NULL, $3);
						    if($1->init_flag==1 && $3->init_flag==1){
								$$->init_flag=1;
							}
							int eq_type = relational_type($1->node_type,$3->node_type);
							if(eq_type == -1){
								yyerror("Error :Invalid operands to ==");
							}
							else{
								if(eq_type == 0){
							    	yyerror("Warning : Invalid Comparison : pointer and Integer");
							    }
							    $$->node_type = "bool";
                           		string op = "EQ_OP";
								set_place($$,$1,op,$3);
						    }
                        }

  | equality_expression NE_OP relational_expression {$$ = non_term_symb_3("!=", $1, NULL, $3);
						    if($1->init_flag==1 && $3->init_flag==1){
								$$->init_flag=1;
							}
							int eq_type = relational_type($1->node_type,$3->node_type);
							if(eq_type == -1){
								yyerror("Error :Invalid operands to ==");
							}
							else{
								if(eq_type == 0){
							    	yyerror("Warning : Invalid Comparison : pointer and Integer");
							    }
							    $$->node_type = "bool";
								string op = "NE_OP";
								set_place($$,$1,op,$3);
						    }
                        }
  ;

and_expression
  : equality_expression  { $$ = $1;}
  | and_expression '&' equality_expression  {
               	$$ = non_term_symb("&",NULL, $1, $3);
				if($1->init_flag==1 && $3->init_flag==1){
					$$->init_flag=1;
				}
				int bit_type = bitwise_type($1->node_type,$3->node_type);
               	if(bit_type == -1){
					yyerror("Error :Invalid operands to the &");
				}
				else{
					if(bit_type == 1){
						$$->node_type = "bool"; 
					}
					else{   
						$$->node_type = "int";
					}
                  	string op = "&";
					set_place($$,$1,op,$3);
               }
          }
  ;

exclusive_or_expression
  : and_expression   { $$ = $1;}
  | exclusive_or_expression '^' and_expression  {
           			$$ = non_term_symb("^", NULL, $1, $3);
					if($1->init_flag==1 && $3->init_flag==1){
						$$->init_flag=1;
					}
				   	int bit_type = bitwise_type($1->node_type,$3->node_type);
					if(bit_type == -1){
						yyerror("Error : Invalid operands to the ^");
					}
					else{
						if(bit_type == 1){
							$$->node_type = "bool"; 
						}
						else{   
							$$->node_type = "int";
						}
						string op = "^";
						set_place($$,$1,op,$3);
               		}
        		}
  ;

inclusive_or_expression
	: exclusive_or_expression								{$$ = $1;}
	| inclusive_or_expression '|' exclusive_or_expression	{$$ = non_term_symb("|", NULL, $1, $3);
								if($1->init_flag==1 && $3->init_flag==1){
									$$->init_flag=1;
								}
								int bit_type = bitwise_type($1->node_type,$3->node_type);
								if(bit_type == -1){
									yyerror("Error :Invalid operands to the |");
								}
								else{
									if(bit_type == 1){
										$$->node_type = "bool"; 
									}
									else{   
										$$->node_type = "int";
									}
                           			string op = "|";
									set_place($$,$1,op,$3);
								}
							}
	;

M1
  : logical_and_expression AND_OP {
                        make_truefalse_lists($1); // if already not processed then no truelist/falselist present
                        $$ = $1;
  }
  ;

M
 : %empty {
           $$ = emit_list.size();
 }
 ;
   
logical_and_expression
	: inclusive_or_expression								{$$ = $1;}
	| M1 M inclusive_or_expression	{$$ = non_term_symb_3("&&", $1, NULL, $3);
								if($1->init_flag==1 && $3->init_flag==1){
									$$->init_flag=1;
								}
								$$->node_type == "bool";
                            	make_truefalse_lists($3);
                           		backPatch($1->truelist,$2);
                           		$$->truelist = $3->truelist;
                           		$$->falselist=merging($1->falselist,$3->falselist);
								}
	;

M2
  : logical_or_expression OR_OP {
                        make_truefalse_lists($1);
                        $$ = $1;
  }
  ;

logical_or_expression
	: logical_and_expression								{$$ = $1;}
	| M2 M logical_and_expression	{$$ = non_term_symb_3("||", $1, NULL, $3);
								if($1->init_flag==1 && $3->init_flag==1){
									$$->init_flag=1;
								}
								$$->node_type == "bool";
                         		make_truefalse_lists($3);
                         		backPatch($1->falselist, $2);
                         		$$->falselist = $3->falselist;
								$$->truelist= merging($1->truelist, $3->truelist);
							}
	;

M3
  : logical_or_expression '?' {
                        make_truefalse_lists($1);
                        $$ = $1;
  }
  ;

N
 : %empty {
                emit(pair<string, Entry*>("=", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), -1);
                $$ = emit(pair<string, Entry*>("GOTO", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), 0);
 }
 ;

conditional_expression
	: logical_or_expression												{$$ = $1;}
	| M3 M expression ':' N conditional_expression {$$ = non_term_symb_3("logical_expr ? expr : conditional_expr", $1, $3, $6);
										if($1->init_flag==1 && $3->init_flag==1 && $6->init_flag==1){
											$$->init_flag=1;
										}
										int cond_type = relational_type($3->node_type,$6->node_type);
										if(cond_type == -1){
											yyerror("Error :Type Mismatch in ternary statement");
										}
										else{
											if(cond_type==0){
												yyerror("Warning : Type Mismatch in ternary statement");
											}
											$$->node_type = "int";
                    						pair <string, Entry*> newlabel = newlabel_sym($$->node_type);
                    						emit(pair<string, Entry*>("=", NULL), $6->place, pair<string, Entry*>("", NULL), newlabel, -1);
                    						backPatch($1->truelist , $2);
                    						backPatch($1->falselist , $5+1);
											emit_list[$5-1].operand_1 = $3->place;
											emit_list[$5-1].ans = newlabel;
                    						$$->nextlist = $3->nextlist;
                    						$$->nextlist.push_back($5);
                    						$$->place = newlabel;
										}																		
									}
	;

assignment_expression
	: conditional_expression										{$$ = $1;}
	| unary_expression assignment_operator assignment_expression	{$$ = non_term_symb_3($2, $1, NULL, $3);
									string tmp_str = convert_to_string($2);
									int assign_type;
									if(tmp_str == "="){
										assign_type = assignment_type1($1->node_type, $3->node_type);										
									}
									else if(tmp_str == "+=" || tmp_str == "-="){
										assign_type = assignment_type2($1->node_type, $3->node_type);
									}
									else if(tmp_str == "*="){
										assign_type = assignment_type3($1->node_type, $3->node_type);
									}
									else if(tmp_str == "/="){
										assign_type = assignment_type4($1->node_type, $3->node_type);
									}
									else if(tmp_str == "%="){
										assign_type = assignment_type5($1->node_type, $3->node_type);
									}
									else if(tmp_str == ">>=" || tmp_str == "<<="){
										assign_type = assignment_type6($1->node_type, $3->node_type);
									}
									else if(tmp_str == "&=" || tmp_str == "^=" || tmp_str == "|="){
										assign_type = assignment_type7($1->node_type, $3->node_type);
									}
									if(assign_type == -1){
										yyerror("Error : Incompatible types when assigning type \'%s\' to \'%s\' ",($1->node_type).c_str(),($3->node_type).c_str());
									}
									else{
										$$->node_type = $1->node_type;
										if(assign_type == 0){
											yyerror("Warning : Incompatible pointer type assignment");
										}
                      					int k = assign_3ac($2, $$->node_type,$1->node_type, $3->node_type, $1->place, $3->place);
										$$->place = $1->place;
										backPatch($3->nextlist, k); //for ternary operator like expression
									}
									if($1->expr_type == "identifier"){ 
										if($3->init_flag==1){
											if(lookup($1->node_key) != NULL){
												Entry* tmp_entry = lookup($1->node_key);
												tmp_entry->init_flag = 1;
											}
										}
									 }
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
	| expression ',' M assignment_expression	{$$ = non_term_symb("expression ','", NULL, $1, $4);
                    						backPatch($1->nextlist,$3);
                    						$$->nextlist = $4->nextlist;
											}
	;

constant_expression
	: conditional_expression	{$$ = $1;}
	;

declaration
	: declaration_specifiers ';' {$$=$1;
								type_name="";
								}
	| declaration_specifiers init_declarator_list ';'	{$$ = non_term_symb("declaration", NULL, $1, $2);
                                                        type_name="";
														$$->nextlist = $2->nextlist;
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
												$$ = non_term_symb("init_declarator_list", NULL, $1, $4);
                                                 backPatch($1->nextlist, $3); //for ternary op like expression 
                                                 $$->nextlist = $4->nextlist;
												}
	;

init_declarator
	: declarator{
		$$ = $1;
		if($1->expr_type == "declarator"){
        	if((*curr).find($1->node_key) == (*curr).end()){
				insert_symbol1(*curr,$1->node_key,$1->node_type,$1->size,0);
				$$->place.first = $1->node_key;
				$$->place.second = lookup($1->node_key);
				$$->place.second->col=$1->col;
        	}
			else{  
				yyerror("Error : \'%s\' already declared",($1->node_key).c_str());
			}
        }
	}
	| declarator '=' M initializer	{	
		$$ = non_term_symb("=", NULL, $1, $4);
		if($1->expr_type == "declarator"||$1->expr_type == "arr_decl"){ 
        	if((*curr).find($1->node_key) == (*curr).end()){
				insert_symbol1(*curr,$1->node_key,$1->node_type,$1->size,1);
                int valid = compatible($1->node_type, $4->node_type);
				if(valid == -1){
					yyerror("Error : Invalid assignment of \'%s\' to \'%s\' ",$1->node_type.c_str(),$4->node_type.c_str());
				}
            	else{
                    if(valid == 0){ yyerror("Warning : Invalid assignment of \'%s\' to \'%s\' ",$1->node_type.c_str(),$4->node_type.c_str()); }
                    $1->place.first=$1->node_key;
					$1->place.second=lookup($1->node_key);
		            int k=assign_3ac("=", $1->node_type,$1->node_type, $4->node_type, $1->place, $4->place);
                    $$->place = $1->place;					
					backPatch($1->nextlist, $3); //for ternary op
                    $$->nextlist = $4->nextlist;					
                }
                $$->place.first = $1->node_key;
				$$->place.second = lookup($1->node_key);
            }
            else{ 
				yyerror("Error : \'%s\' already declared",($1->node_key).c_str());
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
	: VOID							{
									$$ = term_symb($1);
									string tmp_str($1);
									if(type_name.length()){
										type_name.append(" ");
									}
                   					type_name.append(tmp_str);
									}
	| CHAR							{$$ = term_symb($1);
									string tmp_str($1);
									if(type_name.length()){
										type_name.append(" ");
									}
                   					type_name.append(tmp_str);
									}
	| SHORT							{$$ = term_symb($1);
									string tmp_str($1);
									if(type_name.length()){
										type_name.append(" ");
									}
                   					type_name.append(tmp_str);
									}
	| INT							{$$ = term_symb($1);
									string tmp_str($1);
									if(type_name.length()){
										type_name.append(" ");
									}
                   					type_name.append(tmp_str);
									}
	| LONG							{$$ = term_symb($1);
									string tmp_str($1);
									if(type_name.length()){
										type_name.append(" ");
									}
                   					type_name.append(tmp_str);
									}
	| FLOAT							{$$ = term_symb($1);
									string tmp_str($1);
									if(type_name.length()){
										type_name.append(" ");
									}
                   					type_name.append(tmp_str);
									}
	| DOUBLE						{$$ = term_symb($1);
									string tmp_str($1);
									if(type_name.length()){
										type_name.append(" ");
									}
                   					type_name.append(tmp_str);
									}
	| SIGNED						{$$ = term_symb($1);
									string tmp_str($1);
									if(type_name.length()){
										type_name.append(" ");
									}
                   					type_name.append(tmp_str);
									}
	| UNSIGNED						{$$ = term_symb($1);
									string tmp_str($1);
									if(type_name.length()){
										type_name.append(" ");
									}
                   					type_name.append(tmp_str);
									}
	| struct_or_union_specifier		{$$ = $1;
									if(type_name.length()){
										type_name.append(" ");
									}
                   					type_name.append($$->node_type);
									}
	| enum_specifier				{$$ = $1; 
									yyerror("Error : Enum specifier not allowed");
									}
	| TYPE_NAME						{}
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER str_mark3 '{' struct_declaration_list '}'	{
									$$ = non_term_symb("struct_or_union_specifier", $2, $1, $5);
									string tmp_str($2); 
									Parent.insert(pair<symbol_table *, symbol_table *>(struct_table, NULL));
									struct_size_map.insert({("STRUCT_" + tmp_str), struct_size}); //create structSize variable 
									string stmp= "STRUCT_"+tmp_str; 
									$$->node_type=stmp;
									tmp_str = "struct_" + tmp_str + ".csv";
									print_tables(struct_table, tmp_str); 
									}

	| struct_or_union str_mark3 '{' struct_declaration_list '}'				{$$ = non_term_symb("struct_or_union_specifier", NULL, $1, $4);
																			yyerror("Error : Anonymous struct not allowed\n");
																		}	

	| struct_or_union IDENTIFIER									{$$ = non_term_symb("struct_or_union_specifier", $2, $1, NULL);
													string tmp_str($2);
													string tmp_str2("STRUCT_");
													tmp_str2.append(tmp_str);
													if(struct_table_map.find(tmp_str2) == struct_table_map.end()){
														yyerror("Error : struct \'%s\' is not defined",$2);
													} 
													else{
														$$->node_type = tmp_str2;
													}
												}
	;

str_mark3
  : %empty {
	  		string tmp=nameStruct;
	  	    const char *c=new char();
			c=tmp.c_str();
			symbol_table *new_struct_table = new symbol_table();
   			struct_table = new_struct_table;
   			struct_offset = 0; 
			struct_size = 0;
		    if (struct_table_map.find("STRUCT_"+tmp) == struct_table_map.end())
				struct_table_map.insert(pair<string, symbol_table *>("STRUCT_" + tmp, struct_table));
			else{
				yyerror("Error : struct \'%s\' is already defined\n", c);
			}
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
				if((*struct_table).find($1->node_key) != (*struct_table).end()){
					yyerror(" : \'%s\' is already declared in the same struct", $1->node_key.c_str());
				}
				else{
					insert_symbol3(*struct_table, $1->node_key, $1->node_type, $1->size, 0);
					if($1->node_type == "char")	struct_offset += 4;
					else	struct_offset += $1->size;
					struct_size += $1->size;
				}
	}
	| ':' constant_expression {$$ = $2;}
	| declarator ':' constant_expression {$$ = non_term_symb("struct_declarator", NULL, $1, $3);
										yyerror("Error : Bitfields not allowed");
										}
	;

enum_specifier
	: ENUM '{' enumerator_list '}' {$$ = non_term_symb("enum_specifier", $1, NULL, $3);}
	| ENUM IDENTIFIER '{' enumerator_list '}' {$$ = non_term_symb_enum("enum_specifier", $1,$2, $4,NULL);}
	| ENUM IDENTIFIER {$$ = non_term_symb_enum("enum_specifier",$1, $2,NULL, NULL);}
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
								string tmp_str=$2->node_type;
								tmp_str.append($1->node_type);
								$$->node_type=tmp_str;
								$$->node_key = $2->node_key;
								$$->expr_type=$2->expr_type;
								if($2->expr_type == "func_decl"){    //for functions
									func_name = $2->node_key; 
									func_type = tmp_str;
								}
								$$->size = get_size($$->node_type);
								$$->place.first = $$->node_key;
								$$->place.second = NULL; // not inserted yet
								}
	| direct_declarator {$$ = $1;
						string tmp_str = $1->node_type;
						if($1->expr_type == "func_decl"){  // for functions
							func_name = $1->node_key; 
							func_type = tmp_str;
						}
						$$->place.first = $$->node_key;
						$$->place.second = NULL; // not inserted yet
						}
	;

direct_declarator
	: IDENTIFIER {$$=term_symb($1);
				$$->expr_type="declarator";
				string tmp_str($1);
				$$->node_key=tmp_str;
				if(type_name=="spec_less_func"){ // specifier less function
					yyerror("Warning :return type of \'%s\' defaults to int",$1);
					type_name="int";
					$$->node_type=type_name;
				}
				else $$->node_type=type_name;
				$$->size = get_size(type_name); // used while inserting in symbol table
				$$->place.first = $$->node_key;
				$$->place.second = NULL; // getting inserted in init_declarator
				}
	| '(' declarator ')' {$$ = $2;}
	| direct_declarator '[' constant_expression ']' {$$ = non_term_symb("direct_declarator", NULL, $1, $3);
														
														if(!int_flag($3->node_type)){
															yyerror("Error : array index not an integer");
														}
														else{
															if($1->expr_type == "declarator"){ 
																	$$->expr_type = "declarator";
																	$$->node_key=$1->node_key;
																	string stmp=$1->node_type+"*";
																	$$->node_type=stmp;
															}
															else if($1->expr_type == "arr_decl"){
																yyerror("Error :array size missing in \'%s\' ",$1->node_key.c_str());
															}
															if($3->integer_value){
																$$->size = $1->size * $3->integer_value; 
																$$->col=$3->integer_value;
															}
															else { 
																char* a = new char();
																strcpy(a,($$->node_type).c_str());
																$$->size = get_size(a); 
															}
															$$->place.first = $$->node_key;
															$$->place.second = NULL;
														}
													}
	| direct_declarator '[' ']'    {$$ = non_term_symb("direct_declarator", "[ ]", $1, NULL);
						yyerror("Error : Variable size array not allowed");
					}

	| direct_declarator '(' str_mark2 parameter_type_list ')'  {$$ = non_term_symb("direct_declarator", NULL, $1, $4);
							if($1->expr_type == "declarator"){ 
								$$->node_key=$1->node_key;
								$$->expr_type = "func_decl"; // for function declaration
								$$->node_type=$1->node_type;
								args_map.insert({$1->node_key,args_defined});
								args_defined="";								
							}
							$$->place.first = $$->node_key;
							$$->place.second = NULL;
							string begin_emit =  "func ";
							begin_emit.append($$->node_key);
							begin_emit.append(" begin :");
							emit(pair<string , Entry*>(begin_emit, NULL), pair<string , Entry*>("", NULL),pair<string , Entry*>("", NULL),pair<string , Entry*>("", NULL),-2);
							}

	| direct_declarator '(' str_mark2 identifier_list ')' 	{$$ = non_term_symb("direct_declarator", NULL, $1, $4);
							yyerror("Error : type specifier for parameter missing");
							}

	| direct_declarator '(' str_mark2 ')' 			{$$ = non_term_symb("direct_declarator", "( )", $1, NULL);
							if($1->expr_type == "declarator"){
								$$->node_key=$1->node_key;
								args_map.insert({$1->node_key,""});
								$$->expr_type = "func_decl";
								args_defined = "";
							}
							$$->node_type=$1->node_type;
							$$->size=get_size($$->node_type);
							$$->place.first = $$->node_key;
							$$->place.second = NULL;
                        	string begin_emit =  "func ";
							begin_emit.append($$->node_key);
							begin_emit.append(" begin :");
                        	emit(pair<string , Entry*>(begin_emit, NULL), pair<string , Entry*>("", NULL),pair<string , Entry*>("", NULL),pair<string , Entry*>("", NULL),-2);
							}
	;
str_mark2
   :%empty                  { type_name ="";
                           	old_offset = offset_arr[offset_arr_index];
   							create_table("New Func", "");
							str_mark2_done = true;
							args_defined = "";
							}
    ;
pointer
	: '*' {$$=term_symb("*");
			$$->node_type="*";
			}
	| '*' type_qualifier_list {$$=non_term_symb("*",NULL,$2,NULL);
							$$->node_type="*";
							}
	| '*' pointer {$$=non_term_symb("*",NULL,$2,NULL);
				string tmp_str="*";
				tmp_str.append($2->node_type);
				$$->node_type=tmp_str;
				}
	| '*' type_qualifier_list pointer {$$=non_term_symb("*",NULL,$2,$3);
									string tmp_str="*";
									tmp_str.append($3->node_type);
									$$->node_type=tmp_str;
									}
	;

type_qualifier_list
	: type_qualifier {$$=$1;}
	| type_qualifier_list type_qualifier {$$=non_term_symb("type_qualifier_list",NULL,$1,$2);}
	;


parameter_type_list
	: parameter_list {$$=$1;}
	| parameter_list ',' ELLIPSIS {	args_defined = args_defined+",...";
					$$=non_term_symb("parameter_type_list",NULL,$1,term_symb("ELLIPSIS"));
					}
	;

parameter_list
	: parameter_declaration {$$=$1;}
	| parameter_list ',' parameter_declaration {$$=non_term_symb("parameter_list",NULL,$1,$3);}
	;

parameter_declaration
	: declaration_specifiers declarator {
			$$=non_term_symb("parameter_declaration",NULL,$1,$2);
			type_name="";
			if((*curr).find($2->node_key) == (*curr).end()){ 
				insert_symbol1(*curr,$2->node_key,$2->node_type,$2->size,1);
			}
			else {  
				yyerror("Error : %s is already declared",$2->node_key.c_str());
			}
			if(args_defined != "") args_defined= args_defined+","+($2->node_type);
			else args_defined=($2->node_type);
	}
	| declaration_specifiers abstract_declarator {
												$$=non_term_symb("parameter_declaration",NULL,$1,$2);
												yyerror("Error :abstract declaration not allowed");
												type_name="";
												}
	| declaration_specifiers {$$=$1;
							type_name="";
							yyerror("Error :abstract declaration not allowed");
							}
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
	| '{' initializer_list '}' {yyerror("Error : Direct declaration not allowed");
								$$ = $2;
								string tmp_str = $2->node_type+"*"; 
								$$->node_type = tmp_str;
								}
	| '{' initializer_list ',' '}' {
									$$ = non_term_symb("initializer", $3, $2 ,NULL);
									string tmp_str= $2->node_type+"*"; 
									$$->node_type=tmp_str; 
									$$->expr_type =$2->expr_type;
                                    $$->place = $2->place;
                                    $$->nextlist = $2->nextlist;
								}
	;

initializer_list
	: initializer {$$ = $1;$$->expr_type = "declarator";}
	| initializer_list ',' M initializer {
          $$ = non_term_symb("initializer_list", NULL, $1 ,$4);
          $$->node_type = $1->node_type;
           	int valid = compatible($1->node_type,$4->node_type);
			if(valid == -1){
				yyerror("Error : Incompatible types when initializing type \'%s\' to \'%s\' ",($1->node_type).c_str(),($4->node_type).c_str());
			}
            else if(valid == 0){
                yyerror("Warning : Incompatible pointer type assignment");
            }
            backPatch($1->nextlist, $3); //ternary op
            $$->nextlist = $4->nextlist;
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
                                 pair <string, Entry*> t = newlabel_sym("bool");
                                 int emit_ind1 = emit(pair<string, Entry*>("EQ_OP", NULL),pair<string, Entry*>("", NULL), $2->place, t, -1);
                                 $$->caselist.push_back(emit_ind1); // for adding operand_1
								 int emit_ind2 = emit(pair<string, Entry*>("GOTO", NULL),pair<string, Entry*>("IF", NULL), t, pair<string, Entry*>("", NULL ),0);
                                 $$->truelist.push_back(emit_ind2);
								 int emit_ind3 = emit(pair<string, Entry*>("GOTO", NULL),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),0);
                                 $$->falselist.push_back(emit_ind3);


   }
  ;

labeled_statement
	: IDENTIFIER ':' M statement {
		$$ = non_term_symb("labeled_statement", NULL, term_symb($1), $4);
				yyerror("Error : Expected a constant number inside switch-case");
	}
	| M5 M statement {
		$$ = non_term_symb_3("labeled_statement", term_symb("CASE"), $1, $3);
        backPatch($1->truelist, $2);
		$$->nextlist=merging($3->nextlist, $1->falselist);
        $$->breaklist = $3->breaklist;
        $$->caselist = $1->caselist;
        $$->continuelist=$3->continuelist;
	}
	| DEFAULT ':' statement {
		$$ = non_term_symb("labeled_statement", NULL, term_symb("DEFAULT"), $3);
        $$->breaklist= $3->breaklist;
        $$->nextlist = $3->nextlist;
        $$->continuelist=$3->continuelist;
	}
	;

compound_statement
	: '{' '}' {$$ = term_symb("{ }");func_decl_only=1;}
	| '{' statement_list '}'  { $$ = $2;}
	| '{' declaration_list '}'  { $$ = $2;}
	| '{' declaration_list M statement_list '}' {$$ = non_term_symb("compound_statement",NULL, $2,$4);
														backPatch($2->nextlist, $3);
														$$->nextlist = $4->nextlist;
												}
	;

declaration_list
	: declaration {$$=$1;}
	| declaration_list M declaration {$$ = non_term_symb("declaration_list", NULL, $1, $3);
                                         backPatch($1->nextlist, $2);
                                         $$->nextlist = $3->nextlist;
									  }
	;

statement_list
	: statement {$$ = $1;}
	| statement_list M statement {$$ = non_term_symb("statement_list", NULL, $1, $3);
                                         backPatch($1->nextlist, $2);
                                         $$->nextlist = $3->nextlist;
										 $$->caselist=merging($1->caselist, $3->caselist);
                                         $$->continuelist=merging($1->continuelist, $3->continuelist);
										 $$->breaklist=merging($1->breaklist, $3->breaklist);
									  }
	;

expression_statement
	: ';' {$$ = term_symb(";");}
	| expression ';' {$$ = $1;}
	;

M4
  :  IF '(' expression ')' {
                        make_truefalse_lists($3);
                        $$ = $3;
  }
  ;

N1
   : %empty {

                           $$ = emit(pair<string, Entry*>("GOTO", NULL),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),0);
   }
   ;

selection_statement
	: M4 M statement ELSE N1 M statement {
		$$ = non_term_symb_3("IF (expr) stmt ELSE stmt", $1, $3, $7);
        backPatch($1->truelist, $2);
        backPatch($1->falselist, $6);
        $3->nextlist.push_back($5);
		$$->nextlist=merging($3->nextlist, $7->nextlist);
		$$->breaklist =merging($3->breaklist, $7->breaklist);
		$$->continuelist=merging($3->continuelist, $7->continuelist);
	}
	| M4 M statement %prec IFX {
		$$ = non_term_symb_3("IF (expr) stmt", NULL, $1, $3);
        backPatch($1->truelist, $2);
		$$->nextlist=merging($3->nextlist, $1->falselist);
        $$->continuelist = $3->continuelist;
        $$->breaklist = $3->breaklist;
	}
	| SWITCH '(' expression ')' statement{
		$$ = non_term_symb_3("SWITCH (expr) stmt", NULL, $3, $5);
		int i = 0;
		while(i < $5->caselist.size()){
			emit_list[$5->caselist[i]].operand_1 = $3->place;
			i++;
		}
		$$->nextlist=merging($5->nextlist, $5->breaklist);
        $$->continuelist= $5->continuelist;
	}
	;

M6
  :   expression  {
						make_truefalse_lists($1);
                        $$ = $1;
  }
  ;


M7
  :   expression_statement  {
						make_truefalse_lists($1);
                        $$ = $1;
  }
  ;

iteration_statement
	: WHILE '(' M M6 ')' M statement {
		$$ = non_term_symb_3("WHILE (expr) stmt", NULL, $4, $7);
		int emit_ind = emit(pair<string, Entry*>("GOTO", NULL),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),$3);
        backPatch($4->truelist, $6);
        backPatch($7->continuelist, $3);
        backPatch($7->nextlist, $3);
		$$->nextlist=merging($4->falselist, $7->breaklist);
	}
	| DO M statement  WHILE '(' M M6 ')' ';'{
		$$ = non_term_symb_3("DO stmt WHILE (expr)", NULL, $3, $7);
        backPatch($7->truelist, $2);
        backPatch($3->continuelist, $6);
        backPatch($3->nextlist, $6);
		$$->nextlist = merging($7->falselist, $3->breaklist);
	}
	| FOR '(' expression_statement M M7 ')' M statement {
		$$ = non_term_symb_3("FOR (expr_stmt expr_stmt) stmt", $3, $5, $8);
		int emit_ind = emit(pair<string, Entry*>("GOTO", NULL),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),$4);
        backPatch($3->nextlist, $4);//for ternary op
        backPatch($5->truelist, $7);
		$$->nextlist=merging($5->falselist, $8->breaklist);
        backPatch($8->nextlist, $4 );
		backPatch($8->nextlist,$4);
	}
	| FOR '(' expression_statement M M7 M expression N1 ')' M statement{
		$$ = non_term_symb_5("FOR (expr_stmt expr_stmt expr) stmt", NULL, $3, $5, $7, $11);
		int emit_ind = emit(pair<string, Entry*>("GOTO", NULL),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),$6);
        backPatch($3->nextlist, $4);
        backPatch($5->truelist, $10);
		$$->nextlist=merging($5->falselist, $11->breaklist);
        backPatch($11->nextlist, $6 );
		backPatch($11->continuelist,$6);
        $7->nextlist.push_back($8);
        backPatch($7->nextlist, $4);
	}
	;

jump_statement
	: GOTO IDENTIFIER ';' {$$ = non_term_symb("jump_statement", NULL, term_symb("GOTO"), term_symb($2));
						yyerror("Error : Unconditional Jumps not allowed");
	}
	| CONTINUE ';' {
		$$ = term_symb("continue");
        int emit_ind = emit(pair<string, Entry*>("GOTO", NULL),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),0);
        $$->continuelist.push_back(emit_ind);
	}
	| BREAK ';' {
		$$ = term_symb("break");
        int emit_ind = emit(pair<string, Entry*>("GOTO", NULL),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),0);
        $$->breaklist.push_back(emit_ind);
	}
	| RETURN ';' {
		$$ = term_symb("return");
		emit(pair<string, Entry*>("RETURN", NULL),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),-1);
	}
	| RETURN expression ';' {
		$$ = non_term_symb("jump_statement", NULL, term_symb("return"), $2);
		emit(pair<string, Entry*>("RETURN", NULL), $2->place, pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),-1);
		$$->nextlist=$2->nextlist;
	}
	;

translation_unit
	: external_declaration {$$ = $1;}
	| translation_unit M external_declaration {
		$$ = non_term_symb("translation_unit", NULL, $1, $3);       
		backPatch($1->nextlist, $2);
        $$->nextlist = $3->nextlist;	
	}
	;

external_declaration
	: function_definition {type_name="";$$ = $1; }
	| declaration {type_name="";$$ = $1;}
	;

function_definition

	: declaration_specifiers declarator str_mark1 declaration_list compound_statement
         {   $$ = non_term_symb_4("function_definition", $1, $2, $4, $5, NULL);   
			 $$->nextlist=$5->nextlist;
			 	type_name="";
                string tmp_str($3);
				tmp_str.append(".csv");
                print_tables(curr,tmp_str);
                symbol_count=0;
				tmp_str.pop_back();
				tmp_str.pop_back();
				tmp_str.pop_back();
				tmp_str.pop_back();
               	update_table(tmp_str,!func_decl_only);
			  	func_decl_only=0;
                
				string end_emit =  "func end";
				emit(pair<string , Entry*>(end_emit, NULL), pair<string , Entry*>("", NULL),pair<string , Entry*>("", NULL),pair<string , Entry*>("", NULL),-3);
         }
	| declaration_specifiers declarator str_mark1 compound_statement  {
			$$ = non_term_symb_3("function_definition", $1, $2, $4);
			$$->nextlist=$4->nextlist;
				
             	type_name="";
                string tmp_str($3);
				tmp_str.append(".csv");
                print_tables(curr,tmp_str);
                symbol_count=0;
				tmp_str.pop_back();
				tmp_str.pop_back();
				tmp_str.pop_back();
				tmp_str.pop_back();
               	update_table(tmp_str,!func_decl_only);
			  	func_decl_only=0;
              
				string end_emit =  "func end";
				emit(pair<string , Entry*>(end_emit, NULL), pair<string , Entry*>("", NULL),pair<string , Entry*>("", NULL),pair<string , Entry*>("", NULL),-3);
            
			}
	| str_mark4 declarator str_mark1 declaration_list compound_statement { $$ = non_term_symb_3("function_definition",$2,$4,$5);
															$$->nextlist=$5->nextlist;
															type_name="";
															string tmp_str($3);
															tmp_str.append(".csv");
															print_tables(curr,tmp_str);
															symbol_count=0;
															tmp_str.pop_back();
															tmp_str.pop_back();
															tmp_str.pop_back();
															tmp_str.pop_back();
															update_table(tmp_str,!func_decl_only);
															func_decl_only=0;
														
															string end_emit =  "func end";
															emit(pair<string , Entry*>(end_emit, NULL), pair<string , Entry*>("", NULL),pair<string , Entry*>("", NULL),pair<string , Entry*>("", NULL),-3);

															
													}
	| str_mark4 declarator str_mark1 compound_statement { $$ = non_term_symb_3("function_definition", $2,NULL,$4);
											$$->nextlist=$4->nextlist;
											type_name="";
											string tmp_str($3);
											tmp_str.append(".csv");
											print_tables(curr,tmp_str);
											symbol_count=0;
											tmp_str.pop_back();
											tmp_str.pop_back();
											tmp_str.pop_back();
											tmp_str.pop_back();
											update_table(tmp_str,!func_decl_only);
											func_decl_only=0;
										
											string end_emit =  "func end";
											emit(pair<string , Entry*>(end_emit, NULL), pair<string , Entry*>("", NULL),pair<string , Entry*>("", NULL),pair<string , Entry*>("", NULL),-3);
											
						
									}
	;

str_mark1
    : %empty                 { 			type_name="";
                                         func_symb++;
                                         file_name = func_name;
                                         if((*Parent[curr]).find(func_name)!=(*Parent[curr]).end()){											
											if((*Parent[curr])[func_name]->init_flag) yyerror("Error : function \"%s\" already declared",func_name.c_str());
										 }
										 
										 create_table(file_name,func_type);
                                         char* f_name= new char();
                                         strcpy(f_name,file_name.c_str());
                                         $$ = f_name;
       }
    ;

str_mark4 : %empty {
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
	args_called = "";
	table_initialize();
	
	args_map.insert(pair<string, string>(string("print_int"), string("int")));
   	args_map.insert(pair<string, string>(string("print_string"), string("char*")));
   	args_map.insert(pair<string, string>(string("scanf"), string("")));
	args_map.insert(pair<string, string>(string("scan_char"), string("")));
	args_map.insert(pair<string, string>(string("print_char"), string("char")));
    yyin = fopen(argv[1], "r");
    ast = fopen(argv[3], "w");
    fprintf(ast, "digraph G {\n\tordering=out;\n");
	
    yyparse();
    fprintf(ast, "}\n");
    fclose(yyin);
    fclose(ast);
	// if(errorCount!=0){
	// 	return 0;
	// }
	file_name = "global_table.csv";
  	print_tables(curr,file_name);
  	// print_func_args();
	show_in_file();

	initialize_reg();
	generate_asm();
	string asm_name=convert_to_string(argv[1]);
	print_asm("code.c");

    return 0;
}

