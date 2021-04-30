#include "symbolTable.h"
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

string getstr_num_type(int num_type);
bool int_flag (string type);
bool real_flag (string type);
bool is_ptr(string type);
bool void_ptr(string type);
bool is_char(string type);
//char* primary_type(char* identifier);
// char* postfix_type(string type, int rule_no);
char* postfix_type1(string type);
char* postfix_type2(string type);
char* postfix_type3(string type);
char* argument_type(string first_type, string second_type);
char* unary_type(string op, string type);
int compatible(string first_type,string second_type);
int additive_type(string first_type, string second_type);
char* multilplicative_type(string first_type, string second_type, char op);
char* equality_type(string first_type,string second_type);
char* relational_type(string first_type,string second_type,char * op);
// char* shift_type(string first_type,string second_type);
char* bitwise_type(string first_type,string second_type);
char* conditional_type(string first_type,string second_type);
char* assign_type(string first_type,string second_type,char* op);

