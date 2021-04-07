#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

struct node{
  char* token;
  unsigned long id;

  long long size;
  long long int iVal;
  long double rVal;
  char cVal;
  int isInit;
  int exprType;
  string name;
  string nodeType;
  string nodeKey;
};

enum ntype {
    N_INT , N_LONG , N_LONGLONG , N_FLOAT , N_DOUBLE, N_LONGDOUBLE
};
typedef struct{
   int nType; /* 0 int , 1 long , 2 long long ,3 float,4 : double , 5:long double */
   int is_unsigned;
   char * str;
   long long int iVal;
   long double rVal;
} numb;
typedef struct{
   long long int iVal;
   long double rVal;
   char *str;
   char cVal;
   int exprType;
   node * nPtr;
} exprNode;




unsigned long find_id();

struct node *square(char *str, struct node *node);
struct node *parentheses(char *str, struct node *node);
struct node *term_symb(char *str);
struct node *non_term_symb(char *str,char *root, struct node *left, struct node *right);
struct node *non_term_symb_1(char *str,char *root1, struct node *left,char *root2);
struct node *non_term_symb_2(char *str,struct node *left,struct node *m, struct node *right);
struct node *non_term_symb_3(char *str,char *root1,char *root3, struct node *left,char *root2);
struct node *non_term_symb_4(char *str,struct node *node1,struct node *node2, struct node *node3, struct node*node4,char* root);
struct node *non_term_symb_5(char *str,struct node *node1,struct node *node2, struct node *node3, struct node*node4,struct node *node5);

// struct node *square(char *str, struct node *node){return NULL;}
// struct node *parentheses(char *str, struct node *node){return NULL;}
// struct node *term_symb(char *str){return NULL;}
// struct node *non_term_symb(char *str,char *root, struct node *left, struct node *right){return NULL;}
// struct node *non_term_symb_1(char *str,char *root1, struct node *left,char *root2){return NULL;}
// struct node *non_term_symb_2(char *str,struct node *left,struct node *m, struct node *right){return NULL;}
// struct node *non_term_symb_3(char *str,char *root1,char *root3, struct node *left,char *root2){return NULL;}
// struct node *non_term_symb_4(char *str,struct node *node1,struct node *node2, struct node *node3, struct node*node4,char* root){return NULL;}
// struct node *non_term_symb_5(char *str,struct node *node1,struct node *node2, struct node *node3, struct node*node4,struct node *node5){return NULL;}
