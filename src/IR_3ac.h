#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <iomanip>
#include "symbolTable.h"
using namespace std;

typedef pair <string, Entry*> qid;

typedef struct quadruple{
  qid id1;
  qid id2;
  qid op;
  qid res;
  int stmtNum;
} quad;

extern vector <quad> emit_list;
extern map<int , string> Labels;

string newlabel_var();
pair<string, Entry*> newlabel_sym(string type);
void set_values_quad(quad* new_instr, qid id1, qid id2, qid op, qid res, int stmtNum);
int emit (qid id1, qid id2, qid op, qid  res, int stmtNum);
void backPatch(vector<int> li, int i);
void show_in_file();
int assignmentExpression(char *op, string type, string type1, string type3, qid place1, qid place3);
void assignment2(char *op, string type, string type1, string type3, qid place1, qid place3);
bool gotoIndexStorage (string id, int loc);
void gotoIndexPatchListStorage (string id, int loc);
char* backPatchGoto();
