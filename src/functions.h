#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "IR_3ac.h"

using namespace std;

struct node{
  char* token;
  unsigned long id;
  int init_flag;
  int expr_type;
  long long size;
  long long int integer_value;
  long double real_value;
  char char_value;
  string name;
  string node_key;
  string node_type;
  ///////////////////////////
  qid place;
  vector<int> truelist;
  vector<int> nextlist;
  vector<int> falselist;
  vector<int> breaklist;
  vector<int> continuelist;
  vector<int> caselist;
  ///////////////////////////
};

enum ntype {
    N_INT , N_LONG , N_LONGLONG , N_FLOAT , N_DOUBLE, N_LONGDOUBLE
};

typedef struct{
   int num_type; /* int-0 , long-1 , long long-2 , float-3, double-4 , long double-5 */
   int unsigned_flag;
   char * str;
   long long int integer_value;
   long double real_value;

   int is_integer; // check wheteher integer or real
} number_types;


typedef struct{
   long long int integer_value;
   long double real_value;
   char *str;
   char char_value;
   int expr_type;
   node * nPtr;
} expr_node;



unsigned long find_id();
void merging(vector<int> l1, vector<int>l2);
struct node *square(char *str, struct node *node);
struct node *parentheses(char *str, struct node *node);
struct node *term_symb(char *str);
struct node *non_term_symb(char *str,char *root, struct node *left, struct node *right);
struct node *non_term_symb_1(char *str,char *root1, struct node *left,char *root2);
struct node *non_term_symb_2(char *str,struct node *left,struct node *m, struct node *right);
struct node *non_term_symb_3(char *str,char *root1,char *root3, struct node *left,char *root2);
struct node *non_term_symb_4(char *str,struct node *node1,struct node *node2, struct node *node3, struct node*node4,char* root);
struct node *non_term_symb_5(char *str,struct node *node1,struct node *node2, struct node *node3, struct node*node4,struct node *node5);
