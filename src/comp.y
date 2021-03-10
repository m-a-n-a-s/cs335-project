%{
#include "functions.h"

int yylex(void);
void yyerror(char *s,...);
%}

%union {
  int number;     /*integer value*/
  char* str;
  struct node *ptr;     /*node pointer */
};

// %token IDENTIFIER CONSTANT STRING_LITERAL SIZEOF
// %token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
// %token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
// %token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
// %token XOR_ASSIGN OR_ASSIGN TYPE_NAME

// %token TYPEDEF EXTERN STATIC AUTO REGISTER
// %token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
// %token STRUCT UNION ENUM ELLIPSIS

// %token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

// %start translation_unit

%token <str> CHAR CONST CASE CONTINUE DEFAULT DO DOUBLE
%token <str> ELSE ENUM EXTERN FLOAT FOR IF INLINE INT LONG
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
	: IDENTIFIER			{$$ = terminal("IDENTIFIER");}
	| CONSTANT				{$$ = terminal("CONSTANT");}
	| STRING_LITERAL		{$$ = terminal("STRING_LITERAL");}
	| '(' expression ')'	{$$ = $2;}
	;

postfix_expression
	: primary_expression									{$$ = $1;}
	| postfix_expression '[' expression ']'					{$$ = nonTerminal("[ ]", NULL, $1, $3);}
	| postfix_expression '(' ')'							{$$ = $1;}
	| postfix_expression '(' argument_expression_list ')'	{$$ = nonTerminal("Postfix Expression", NULL, $1, $3);}
	| postfix_expression '.' IDENTIFIER						{$$ = nonTerminal(" . ", NULL, $1, terminal("IDENTIFIER"));}
	| postfix_expression PTR_OP IDENTIFIER					{$$ = nonTerminal("->", NULL, $1, terminal("IDENTIFIER"));}
	| postfix_expression INC_OP								{$$=  nonTerminal("++", NULL,$1, NULL);}
	| postfix_expression DEC_OP								{$$=  nonTerminal("--", NULL,$1, NULL);}
	;

argument_expression_list
	: assignment_expression									{$$ = $1;}
	| argument_expression_list ',' assignment_expression	{$$ = nonTerminal($2,NULL, $1, $3);}
	;

unary_expression
	: postfix_expression				{$$ = $1;}
	| INC_OP unary_expression			{$$ = nonTerminal("++", NULL, NULL, $2);}
	| DEC_OP unary_expression			{$$ = nonTerminal("--", NULL, NULL, $2);}
	| unary_operator cast_expression	{$$ = nonTerminal("Unary Expression", NULL, $1, $2);}
	| SIZEOF unary_expression			{$$ = nonTerminal($1, NULL, NULL, $2);}
	| SIZEOF '(' type_name ')'			{$$ = nonTerminal($1, NULL, NULL, $3);}
	;

unary_operator
	: '&'	{$$ = terminal("&");}
	| '*'	{$$ = terminal("*");}
	| '+'	{$$ = terminal("+");}
	| '-'	{$$ = terminal("-");}
	| '~'	{$$ = terminal("~");}
	| '!'	{$$ = terminal("!");}
	;

cast_expression
	: unary_expression					{$$ = $1;}
	| '(' type_name ')' cast_expression	{$$ = nonTerminal("Cast Expression", NULL, $2, $4);}
	;

multiplicative_expression
	: cast_expression								{$$ = $1;}
	| multiplicative_expression '*' cast_expression	{$$ = nonTerminal("*", NULL, $1, $3);}
	| multiplicative_expression '/' cast_expression	{$$ = nonTerminal("/", NULL, $1, $3);}
	| multiplicative_expression '%' cast_expression	{$$ = nonTerminal("%", NULL, $1, $3);}
	;

additive_expression
	: multiplicative_expression							{$$ = $1;}
	| additive_expression '+' multiplicative_expression	{$$ = nonTerminal("+", NULL, $1, $3);}
	| additive_expression '-' multiplicative_expression	{$$ = nonTerminal("-", NULL, $1, $3);}
	;

shift_expression
	: additive_expression							{$$ = $1;}
	| shift_expression LEFT_OP additive_expression	{$$ = nonTerminal2($2, $1, NULL, $3);}
	| shift_expression RIGHT_OP additive_expression	{$$ = nonTerminal2($2, $1, NULL, $3);}
	;

relational_expression
	: shift_expression								{$$ = $1;}
	| relational_expression '<' shift_expression	{$$ = nonTerminal("<", NULL, $1, $3);}
	| relational_expression '>' shift_expression	{$$ = nonTerminal(">", NULL, $1, $3);}
	| relational_expression LE_OP shift_expression	{$$ = nonTerminal($2, NULL, $1, $3);}
	| relational_expression GE_OP shift_expression	{$$ = nonTerminal($2, NULL, $1, $3);}
	;

equality_expression
	: relational_expression								{$$ = $1;}
	| equality_expression EQ_OP relational_expression	{$$ = nonTerminal2($2, $1, NULL, $3);}
	| equality_expression NE_OP relational_expression	{$$ = nonTerminal2($2, $1, NULL, $3);}
	;

and_expression
	: equality_expression						{$$ = $1;}
	| and_expression '&' equality_expression	{$$ = nonTerminal("&", NULL, $1, $3);}
	;

exclusive_or_expression
	: and_expression								{$$ = $1;}
	| exclusive_or_expression '^' and_expression	{$$ = nonTerminal("^", NULL, $1, $3);}
	;

inclusive_or_expression
	: exclusive_or_expression								{$$ = $1;}
	| inclusive_or_expression '|' exclusive_or_expression	{$$ = nonTerminal("|", NULL, $1, $3);}
	;

logical_and_expression
	: inclusive_or_expression								{$$ = $1;}
	| logical_and_expression AND_OP inclusive_or_expression	{$$ = nonTerminal2($2, $1, NULL, $3);}
	;

logical_or_expression
	: logical_and_expression								{$$ = $1;}
	| logical_or_expression OR_OP logical_and_expression	{$$ = nonTerminal2($2, $1, NULL, $3);}
	;

conditional_expression
	: logical_or_expression												{$$ = $1;}
	| logical_or_expression '?' expression ':' conditional_expression	{$$ = nonTerminal2("? (Ternary Operator)", $1, $3, $5);}
	;

assignment_expression
	: conditional_expression										{$$ = $1;}
	| unary_expression assignment_operator assignment_expression	{$$ = nonTerminal2($2, $1, NULL, $3);}
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
	| expression ',' assignment_expression	{$$ = nonTerminal("Expression ','", NULL, $1, $3);}
	;

constant_expression
	: conditional_expression	{$$ = $1;}
	;

declaration
	: declaration_specifiers ';' {$$=$1;}
	| declaration_specifiers init_declarator_list ';'	{$$ = nonTerminal("declaration", NULL, $1, $2);}
	;

declaration_specifiers
	: storage_class_specifier							{$$ = $1;}
	| storage_class_specifier declaration_specifiers	{$$ = nonTerminal("declaration_specifiers", NULL, $1, $2);}
	| type_specifier									{$$ = $1;}		
	| type_specifier declaration_specifiers				{$$ = nonTerminal("declaration_specifiers", NULL, $1, $2);}
	| type_qualifier									{$$ = $1;}
	| type_qualifier declaration_specifiers				{$$ = nonTerminal("declaration_specifiers", NULL, $1, $2);}
	;

init_declarator_list
	: init_declarator							{$$ = $1;}
	| init_declarator_list ',' init_declarator	{$$ = nonTerminal("init_declaration_list", NULL, $1, $3);}
	;

init_declarator
	: declarator					{$$ = $1;}
	| declarator '=' initializer	{$$ = nonTerminal("=", NULL, $1, $3);}
	;

storage_class_specifier
	: TYPEDEF	{$$=terminal("TYPEDEF");}
	| EXTERN	{$$=terminal("EXTERN");}
	| STATIC	{$$=terminal("STATIC");}
	| AUTO		{$$=terminal("AUTO");}
	| REGISTER	{$$=terminal("REGISTER");}
	;

type_specifier
	: VOID							{$$ = terminal("VOID");}
	| CHAR							{$$ = terminal("CHAR");}
	| SHORT							{$$ = terminal("SHORT");}
	| INT							{$$ = terminal("INT");}
	| LONG							{$$ = terminal("LONG");}
	| FLOAT							{$$ = terminal("FLOAT");}
	| DOUBLE						{$$ = terminal("DOUBLE");}
	| SIGNED						{$$ = terminal("SIGNED");}
	| UNSIGNED						{$$ = terminal("UNSIGNED");}
	| struct_or_union_specifier		{$$ = $1;}
	| enum_specifier				{$$ = $1;}
	| TYPE_NAME						{$$ = terminal("TYPE_NAME");}
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}'	{$$ = nonTerminal("struct_or_union_specifier", $2, $1, $4);}
	| struct_or_union '{' struct_declaration_list '}'				{$$ = nonTerminal("struct_or_union_specifier", NULL, $1, $3);}
	| struct_or_union IDENTIFIER									{$$ = nonTerminal("struct_or_union_specifier", $2, $1, NULL);}
	;

struct_or_union
	: STRUCT	{$$ = terminal("STRUCT");}
	| UNION		{$$ = terminal("UNION");}
	;

struct_declaration_list
	: struct_declaration							{$$ = $1;}
	| struct_declaration_list struct_declaration	{$$ = nonTerminal("struct_declaration_list", NULL, $1, $2);}
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'	{$$ = nonTerminal("struct_declaration", NULL, $1, $2);}
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list	{$$ = nonTerminal("specifier_qualifier_list", NULL, $1, $2);}
	| type_specifier							{$$ = $1;}
	| type_qualifier specifier_qualifier_list	{$$ = nonTerminal("specifier_qualifier_list", NULL, $1, $2);}
	| type_qualifier							{$$ = $1;}
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
	: IDENTIFIER {$$ = terminal("IDENTIFIER");}
	| IDENTIFIER '=' constant_expression {$$ = nonTerminal("=",NULL, terminal("IDENTIFIER"), $3);}
	;

type_qualifier
	: CONST {$$ = terminal("CONST");}
	| VOLATILE {$$ = terminal("VOLATILE");}
	;

declarator
	: pointer direct_declarator {$$ = nonTerminal("declarator", NULL, $1, $2);}
	| direct_declarator {$$ = $1;}
	;

direct_declarator
	: IDENTIFIER {$$=terminal("IDENTIFIER");}
	| '(' declarator ')' {$$ = $2;}
	| direct_declarator '[' constant_expression ']' {$$ = nonTerminal("direct_declarator", NULL, $1, $3);}
	| direct_declarator '[' ']' {$$ = nonTerminalSquareB("direct_declarator", $1);}
	| direct_declarator '(' parameter_type_list ')' {$$ = nonTerminal("direct_declarator", NULL, $1, $3);}
	| direct_declarator '(' identifier_list ')' {$$ = nonTerminal("direct_declarator", NULL, $1, $3);}
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
	| parameter_list ',' ELLIPSIS {$$=nonTerminal("parameter_type_list",NULL,$1,terminal("ELLIPSIS"));}
	;

parameter_list
	: parameter_declaration {$$=$1;}
	| parameter_list ',' parameter_declaration {$$=nonTerminal("parameter_list",NULL,$1,$3);}
	;

parameter_declaration
	: declaration_specifiers declarator {$$=nonTerminal("parameter_declaration",NULL,$1,$2);}
	| declaration_specifiers abstract_declarator {$$=nonTerminal("parameter_declaration",NULL,$1,$2);}
	| declaration_specifiers {$$=$1;}
	;

identifier_list
	: IDENTIFIER {$$=terminal("IDENTIFIER");}
	| identifier_list ',' IDENTIFIER {$$=nonTerminal("identifier_list",NULL,$1,terminal("IDENTIFIER"));}
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
	: IDENTIFIER ':' statement {$$ = nonTerminal("labeled_statement", NULL, terminal("IDENTIFIER"), $3);}
	| CASE constant_expression ':' statement {$$ = nonTerminal2("labeled_statement", terminal("CASE"), $2, $4);}
	| DEFAULT ':' statement {$$ = nonTerminal("labeled_statement", NULL, terminal("DEFAULT"), $3);}
	;

compound_statement
	: '{' '}' {$$ = terminal("{ }");}
	| '{' statement_list '}' {$$ = $2;}
	| '{' declaration_list '}' {$$ = $2;}
	| '{' declaration_list statement_list '}' {$$ = nonTerminal("compound_statement",NULL, $2,$3);}
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
	| FOR '(' expression_statement expression_statement expression ')' statement {$$ = nonTerminalFiveChild("FOR (expr stmt expr stmt expr) stmt", NULL, $3, $4, $5, $7);}
	;

jump_statement
	: GOTO IDENTIFIER ';' {$$ = nonTerminal("jump_statement", NULL, terminal("GOTO"), terminal("IDENTIFIER"));}
	| CONTINUE ';' {$$ = terminal("continue");}
	| BREAK ';' {$$ = terminal("break");}
	| RETURN ';' {$$ = terminal("return");}
	| RETURN expression ';' {$$ = nonTerminal("jump_statement", NULL, terminal("return"), $2);}
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
	| declarator declaration_list compound_statement {$$ = nonTerminal2("function_definition",$1,$2,$3);}
	| declarator compound_statement {$$ = nonTerminal2("function_definition", $1,NULL,$2);}
	;

%%