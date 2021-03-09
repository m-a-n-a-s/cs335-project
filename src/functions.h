#include<stdio.h>
#include <stdlib.h>
#include<string.h>

struct node{
  char* name;
  int id;
};

int getNodeId();
void graphInitialization();
void graphEnd();
struct node *nonTerminal(char *str,char *op, struct node *l, struct node *r);
struct node *nonTerminal1(char *str,char *op1, struct node *l,char *op2);
struct node *nonTerminal3(char *str,char *op1,char *op3, struct node *l,char *op2);
struct node *terminal(char *str);
struct node *nonTerminal2(char *str,struct node *l,struct node *m, struct node *r);
struct node *nonTerminalFourChild(char *str,struct node *a1,struct node *a2, struct node *a3, struct node*a4,char* op);
struct node *nonTerminalFiveChild(char *str,struct node *a1,struct node *a2, struct node *a3, struct node*a4,struct node *a5);
struct node *nonTerminalRoundB(char *str, struct node *a);
struct node *nonTerminalSquareB(char *str, struct node *a);
struct node *nonTerminalCurlyB(char *str, struct node *a);