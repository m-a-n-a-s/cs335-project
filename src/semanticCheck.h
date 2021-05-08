#include "symbolTable.h"
using namespace std;


bool is_ptr(string type);
bool void_ptr(string type);
bool is_char(string type);
bool is_bool(string type);
bool int_flag (string type);
bool real_flag (string type);
unsigned long long get_size(string type);
string getstr_num_type(int num_type);
char* postfix_type1(string type);
char* postfix_type2(string type);
char* postfix_type3(string type);
char* unary_type(string op, string type);
int compatible(string first_type,string second_type);
int argument_type(string first_type, string second_type);
int additive_type(string first_type, string second_type);
int multiplicative_type1(string first_type, string second_type);
int multiplicative_type2(string first_type, string second_type);
int multiplicative_type3(string first_type, string second_type);
int relational_type(string first_type,string second_type);
int equality_type(string first_type,string second_type);
int conditional_type(string first_type,string second_type);
int bitwise_type(string first_type,string second_type);
int assignment_type1(string first_type, string second_type);
int assignment_type2(string first_type, string second_type);
int assignment_type3(string first_type, string second_type);
int assignment_type4(string first_type, string second_type);
int assignment_type5(string first_type, string second_type);
int assignment_type6(string first_type, string second_type);
int assignment_type7(string first_type, string second_type);


