#include<stdio.h>
#include <stdlib.h>
#include<string.h>

struct node{
  char* name;
  int id;
};

int find_id();
struct node *non_term_symb(char *str,char *op, struct node *l, struct node *r);
struct node *non_term_symb_1(char *str,char *op1, struct node *l,char *op2);
struct node *non_term_symb_3(char *str,char *op1,char *op3, struct node *l,char *op2);
struct node *term_symb(char *str);
struct node *non_term_symb_2(char *str,struct node *l,struct node *m, struct node *r);
struct node *non_term_symb_4(char *str,struct node *a1,struct node *a2, struct node *a3, struct node*a4,char* op);
struct node *non_term_symb_5(char *str,struct node *a1,struct node *a2, struct node *a3, struct node*a4,struct node *a5);
struct node *parentheses(char *str, struct node *a);
struct node *square(char *str, struct node *a);