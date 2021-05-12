#include "semanticCheck.h"

#include <vector>
#include <iomanip>

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
extern unordered_map<string, int> goto_map;
extern unordered_map<int , string> label_map;

quad set_values_quad(pair <string, Entry*> operand_1, pair <string, Entry*> operand_2, pair <string, Entry*> op, pair <string, Entry*> ans, int line_no);
int emit (pair <string, Entry*> operand_1, pair <string, Entry*> operand_2, pair <string, Entry*> op, pair <string, Entry*>  ans, int line_no);
string newlabel_var();
pair<string, Entry*> newlabel_sym(string type);
int assign_3ac(char *op, string type, string operand_1_type, string operand_2_type, pair <string, Entry*> operand_1_place, pair <string, Entry*> operand_2_place);
void backPatch(vector<int> goto_list, int line_no);
void show_in_file();
