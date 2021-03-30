#include<stdio.h>
#include <stdlib.h>
#include<string.h>

struct node{
  char* token;
  unsigned long id;
};

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
