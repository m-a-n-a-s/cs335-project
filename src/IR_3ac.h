#include "symbolTable.h"

// #include <iostream>
// #include <string>
// #include <cstring>
// #include <vector>
// #include <map>
// #include <iomanip>
#include <bits/stdc++.h>
using namespace std;

typedef struct quadruple{
  pair <string, Entry*> operand_1;
  pair <string, Entry*> operand_2;
  pair <string, Entry*> op;
  pair <string, Entry*> ans;
  int line_no;
} quad;

extern vector <quad> emit_list;
extern unordered_map<string, vector<int>> backpatch_list;
extern map<string, int> goto_map;
extern map<int , string> label_map;

quad set_values_quad(pair <string, Entry*> operand_1, pair <string, Entry*> operand_2, pair <string, Entry*> op, pair <string, Entry*> ans, int line_no);
int emit (pair <string, Entry*> operand_1, pair <string, Entry*> operand_2, pair <string, Entry*> op, pair <string, Entry*>  ans, int line_no);
string newlabel_var();
pair<string, Entry*> newlabel_sym(string type);
int assignmentExpression(char *op, string type, string type1, string type3, pair <string, Entry*> place1, pair <string, Entry*> place3);
void assignment2(char *op, string type, string type1, string type3, pair <string, Entry*> place1, pair <string, Entry*> place3);
void backPatch(vector<int> goto_list, int line_no);
char* backPatchGoto();
void show_in_file();
