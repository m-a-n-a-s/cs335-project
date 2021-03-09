%token IDENTIFIER CONSTANT STRING_LITERAL SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%start translation_unit
%%

primary_expression
	: IDENTIFIER
	| CONSTANT
	| STRING_LITERAL
	| '(' expression ')'
	;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']'
	| postfix_expression '(' ')'
	| postfix_expression '(' argument_expression_list ')'
	| postfix_expression '.' IDENTIFIER
	| postfix_expression PTR_OP IDENTIFIER
	| postfix_expression INC_OP
	| postfix_expression DEC_OP
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
	;

unary_expression
	: postfix_expression
	| INC_OP unary_expression
	| DEC_OP unary_expression
	| unary_operator cast_expression
	| SIZEOF unary_expression
	| SIZEOF '(' type_name ')'
	;

unary_operator
	: '&'
	| '*'
	| '+'
	| '-'
	| '~'
	| '!'
	;

cast_expression
	: unary_expression
	| '(' type_name ')' cast_expression
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression
	| multiplicative_expression '/' cast_expression
	| multiplicative_expression '%' cast_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression
	| shift_expression RIGHT_OP additive_expression
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression
	| relational_expression '>' shift_expression
	| relational_expression LE_OP shift_expression
	| relational_expression GE_OP shift_expression
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression
	| equality_expression NE_OP relational_expression
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OP inclusive_or_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP logical_and_expression
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression
	;

assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
	;

assignment_operator
	: '='
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN
	;

expression
	: assignment_expression
	| expression ',' assignment_expression
	;

constant_expression
	: conditional_expression
	;

declaration
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';'
	;

declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers
	| type_specifier
	| type_specifier declaration_specifiers
	| type_qualifier
	| type_qualifier declaration_specifiers
	;

init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: declarator
	| declarator '=' initializer
	;

storage_class_specifier
	: TYPEDEF
	| EXTERN
	| STATIC
	| AUTO
	| REGISTER
	;

type_specifier
	: VOID
	| CHAR
	| SHORT
	| INT
	| LONG
	| FLOAT
	| DOUBLE
	| SIGNED
	| UNSIGNED
	| struct_or_union_specifier
	| enum_specifier
	| TYPE_NAME
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}'
	| struct_or_union '{' struct_declaration_list '}'
	| struct_or_union IDENTIFIER
	;

struct_or_union
	: STRUCT
	| UNION
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

struct_declarator_list
	: struct_declarator {$$ = $1;}
	| struct_declarator_list ',' struct_declarator {$$ = nonTerminal("struct_declarator_list",NULL, $1, $3);}
	;

struct_declarator
	: declarator {$$ = $1;}
	| ':' constant_expression {$$ = $2;}
	| declarator ':' constant_expression {$$ = nonTerminal("struct_declarator", NULL, $1, $3);}
	;

enum_specifier
	: ENUM '{' enumerator_list '}' {$$ = nonTerminal("enum_specifier", $1, NULL, $3);}
	| ENUM IDENTIFIER '{' enumerator_list '}' {$$ = nonTerminal3("enum_specifier", $1,$2, $4,NULL);}
	| ENUM IDENTIFIER {$$ = nonTerminal3("enum_specifier",$1, $2,NULL, NULL);}
	;

enumerator_list
	: enumerator {$$ = $1;}
	| enumerator_list ',' enumerator {$$ = nonTerminal("enumerator_list", NULL, $1,  $3);}
	;

enumerator
	: IDENTIFIER {$$ = $1;}
	| IDENTIFIER '=' constant_expression {$$ = nonTerminal("=",NULL, $1,  $3);}
	;

type_qualifier
	: CONST {$$ = terminal($1);}
	| VOLATILE {$$ = terminal($1);}
	;

declarator
	: pointer direct_declarator {$$ = nonTerminal("declarator", NULL, $1, $2);}
	| direct_declarator {$$ = $1;}
	;

direct_declarator
	: IDENTIFIER {$$=terminal($1);}
	| '(' declarator ')' {$$ = $2;}
	| direct_declarator '[' constant_expression ']' {$$ = nonTerminal("direct_declarator", NULL, $1, $3);}
	| direct_declarator '[' ']' {$$ = nonTerminalSquareB("direct_declarator", $1);}
	| direct_declarator '(' parameter_type_list ')' {$$ = nonTerminal("direct_declarator", NULL, $1, $3);}
	| direct_declarator '(' identifier_list ')' {$$ = nonTerminal("direct_declarator", NULL, $1, $3);
	| direct_declarator '(' ')' {$$ = nonTerminalRoundB("direct_declarator", $1);}
	;

pointer
	: '*' {$$=terminal("*");}
	| '*' type_qualifier_list {$$=nonTerminal("*",NULL,$2,NULL);}
	| '*' pointer {$$=nonTerminal("*",NULL,$2,NULL);}
	| '*' type_qualifier_list pointer {$$=nonTerminal("*",NULL,$2,$3);}
	;

type_qualifier_list
	: type_qualifier {$$=$1;}
	| type_qualifier_list type_qualifier {$$=nonTerminal("type_qualifier_list",NULL,$1,$2);}
	;


parameter_type_list
	: parameter_list {$$=$1;}
	| parameter_list ',' ELLIPSIS {$$=nonTerminal("parameter_list",NULL,$1,$3);}
	;

parameter_list
	: parameter_declaration
	| parameter_list ',' parameter_declaration
	;

parameter_declaration
	: declaration_specifiers declarator {$$=nonTerminal("parameter_declaration",NULL,$1,$2);}
	| declaration_specifiers abstract_declarator {$$=nonTerminal("parameter_declaration",NULL,$1,$2);}
	| declaration_specifiers {$$=$1;}
	;

identifier_list
	: IDENTIFIER {$$=terminal($1);}
	| identifier_list ',' IDENTIFIER {$$=nonTerminal("identifier_list",NULL,$1,temp);}
	;

type_name
	: specifier_qualifier_list {$$=$1;}
	| specifier_qualifier_list abstract_declarator {$$=nonTerminal("type_name",NULL,$1,$2);}
	;

abstract_declarator
	: pointer {$$=$1;}
	| direct_abstract_declarator {$$=$1;}
	| pointer direct_abstract_declarator {$$=nonTerminal("abstract_declarator",NULL,$1,$2);}
	;

direct_abstract_declarator
	: '(' abstract_declarator ')' {$$ = $2;}
	| '[' ']' {$$ = terminal("[ ]");}
	| '[' constant_expression ']' {$$ = $2;}
	| direct_abstract_declarator '[' ']' {$$ = nonTerminal("direct_abstract_declarator" , "[ ]", $1,NULL);}
	| direct_abstract_declarator '[' constant_expression ']' {$$ = nonTerminal("direct_abstract_declarator",NULL, $1, $3);}
	| '(' ')' {$$ = terminal("( )");}
	| '(' parameter_type_list ')' {$$ = $2;}
	| direct_abstract_declarator '(' ')' {$$ = nonTerminal("direct_abstract_declarator","( )", $1,NULL);}
	| direct_abstract_declarator '(' parameter_type_list ')' {$$ = nonTerminal("direct_abstract_declarator", NULL, $1, $3);}
	;

initializer
	: assignment_expression {$$ = $1;}
	| '{' initializer_list '}' {$$ = $2;}
	| '{' initializer_list ',' '}' {$$ = nonTerminal("initializer", $3, $2 ,NULL);}
	;

initializer_list
	: initializer {$$ = $1;}
	| initializer_list ',' initializer {$$ = nonTerminal("initializer_list", NULL, $1 ,$3);}
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
	: IDENTIFIER ':' statement {$$ = nonTerminal("labeled_statement", NULL, temp, $3);}
	| CASE constant_expression ':' statement {$$ = nonTerminal2("labeled_statement", temp, $1, $2);}
	| DEFAULT ':' statement {$$ = nonTerminal("labeled_statement", NULL, temp, $3);}
	;

compound_statement
	: '{' '}' {$$ = terminal("{ }");}
	| '{' statement_list '}' {$$ = $2;}
	| '{' declaration_list '}' {$$ = $2;}
	| '{' declaration_list statement_list '}'
	;

declaration_list
	: declaration {$$=$1;}
	| declaration_list declaration {$$ = nonTerminal("declaration_list", NULL, $1, $2);}
	;

statement_list
	: statement {$$ = $1;}
	| statement_list statement {$$ = nonTerminal("statement_list", NULL, $1, $2);}
	;

expression_statement
	: ';' {$$ = terminal(";");}
	| expression ';' {$$ = $1;}
	;

selection_statement
	: IF '(' expression ')' statement {$$ = nonTerminal2("IF (expr) stmt", NULL, $3, $5);}
	| IF '(' expression ')' statement ELSE statement {$$ = nonTerminal2("IF (expr) stmt ELSE stmt", $3, $5, $7);}
	| SWITCH '(' expression ')' statement {$$ = nonTerminal2("SWITCH (expr) stmt", NULL, $3, $5);}
	;

iteration_statement
	: WHILE '(' expression ')' statement {$$ = nonTerminal2("WHILE (expr) stmt", NULL, $3, $5);}
	| DO statement WHILE '(' expression ')' ';' {$$ = nonTerminal2("DO stmt WHILE (expr)", NULL, $2, $5);}
	| FOR '(' expression_statement expression_statement ')' statement {$$ = nonTerminal2("FOR (expr stmt expr stmt) stmt", $3, $4, $6);}
	| FOR '(' expression_statement expression_statement expression ')' statement {$$ = nonTerminalFiveChild("FOR (expr stmt expr stmt expr) stmt", NULL, $3, $4, $4, $7);}
	;

jump_statement
	: GOTO IDENTIFIER ';' {$$ = nonTerminal("jump_statement", NULL, temp, temp1);}
	| CONTINUE ';' {$$ = terminal("continue");}
	| BREAK ';' {$$ = terminal("break");}
	| RETURN ';' {$$ = terminal("return");}
	| RETURN expression ';' {$$ = nonTerminal("jump_statement", NULL, temp, $2);}
	;

translation_unit
	: external_declaration {$$ = $1;}
	| translation_unit external_declaration {$$ = nonTerminal("translation_unit", NULL, $1, $2);}
	;

external_declaration
	: function_definition {$$ = $1;}
	| declaration {$$ = $1;}
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement {$$ = nonTerminalFourChild("function_definition", $1, $2, $3, $4, NULL);}
	| declaration_specifiers declarator compound_statement {$$ = nonTerminal2("function_definition", $1, $2, $3);}
	| declarator declaration_list compound_statement
	| declarator compound_statement
	;

%%
#include <stdio.h>

extern char yytext[];
extern int column;

yyerror(s)
char *s;
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}