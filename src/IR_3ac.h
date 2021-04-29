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
extern unordered_map<string, vector<int>> gotoIndexPatchList;
extern map<string, int> gotoIndex;

string newlabel_var();
pair<string, Entry*> newlabel_sym(string type);
quad set_values_quad(qid id1, qid id2, qid op, qid res, int stmtNum);
int emit (qid id1, qid id2, qid op, qid  res, int stmtNum);
void backPatch(vector<int> li, int i);
void show_in_file();
// void display(quad q, int p);
// int getNextIndex();
// void setResult(int a, qid p);
// void setId1(int a, qid p);
// void setListId1(vector<int> li, qid p);
int assignmentExpression(char *op, string type, string type1, string type3, qid place1, qid place3);
void assignment2(char *op, string type, string type1, string type3, qid place1, qid place3);
// bool gotoIndexStorage (string id, int loc);
// void gotoIndexPatchListStorage (string id, int loc);
char* backPatchGoto();
