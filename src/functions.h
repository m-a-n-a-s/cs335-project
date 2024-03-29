#include <stdio.h>
#include <stdlib.h>
#include "IR_3ac.h"

using namespace std;

struct node{
  char* token;
  unsigned long id; // for ast id
  int init_flag;
  long long size;
  long long int integer_value;
  long double real_value;
  char char_value;
  string name;
  string node_key;
  string node_type;
  string expr_type;
  ///////////////////////////
  pair <string, Entry*> place;
  vector<int> truelist;
  vector<int> nextlist;
  vector<int> falselist;
  vector<int> breaklist;
  vector<int> continuelist;
  vector<int> caselist;
  
  int col;
  //vector<int> dim; //ith dimnesion columns size for mutidimensional array
  ///////////////////////////
  
};

enum ntype {
    N_INT , N_LONG , N_LONGLONG , N_FLOAT , N_DOUBLE, N_LONGDOUBLE
};

typedef struct{
   int num_type; /* int-1 , long-2 , long long-3 , float-4, double-5 , long double-6 */
   int unsigned_flag;
   char * str;
   long long int integer_value;
   long double real_value;

   int is_integer; // check wheteher integer or real
} number_types;


void make_truefalse_lists(struct node* node1);
void set_place(struct node* node0, struct node* node1, string op, struct node* node3);
void set_place2(struct node* node0, struct node* node1, string op1, string op2);
vector<int> merging(vector<int> &l1, vector<int> &l2);
unsigned long find_id();
struct node *term_symb(char *str);
struct node *non_term_symb(char* str, char *op, struct node *node1, struct node *node2);
struct node *non_term_symb_3(char *str,struct node* node1 ,struct node *node2, struct node *node3);
struct node *non_term_symb_4(char *str,struct node *node1,struct node *node2, struct node *node3, struct node *node4, char* op);
struct node *non_term_symb_5(char *str,struct node *node1,struct node *node2, struct node *node3, struct node *node4, struct node* node5);
struct node *non_term_symb_enum(char *str,char *op1,char *op2, struct node *node1,char *op3);
