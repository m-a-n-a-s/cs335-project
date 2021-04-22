#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include <unordered_map>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

bool is_Intgr (string type);
bool is_float (string type);
bool is_SignedInt (string type);
bool is_SignedFloat (string type);
char* constant(int num_type);
char* primary_expr(char* identifier);
char* postfix_expr(string type, int Number);
char* argument_expr(string type1, string type2, int Number);
char* unary_expr(string op, string type, int Number);
char* validAssign(string type1,string type2);
char* additive_expr(string type1, string type2, char op);
char* multilplicative_expr(string type1, string type2, char op);
char* equality_expr(string type1,string type2);
char* relational_expr(string type1,string type2,char * op);
char* shift_expr(string type1,string type2);
char* bitwise_expr(string type1,string type2);
char* conditional_expr(string type1,string type2);
char* assign_expr(string type1,string type2,char* op);

