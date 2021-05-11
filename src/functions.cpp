#include "functions.h"
#include <bits/stdc++.h>

extern FILE *ast;

#define ul unsigned long

void make_truefalse_lists(struct node* node1){
  // if already not processed then no truelist/falselist present
  if(node1->truelist.empty()){
      int emit_ind1 = emit(pair<string, Entry*>("GOTO", NULL),pair<string, Entry*>("IF", NULL), node1->place, pair<string, Entry*>("", NULL ),0);
      int emit_ind2 = emit(pair<string, Entry*>("GOTO", NULL),pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL), pair<string, Entry*>("", NULL ),0);
      node1->truelist.push_back(emit_ind1);
      node1->falselist.push_back(emit_ind2);
  }
  return;
}

void set_place(struct node* node0, struct node* node1, string op, struct node* node3){
  pair <string, Entry*> newlabel = newlabel_sym(node0->node_type);
  emit(pair<string, Entry*>(op, NULL), node1->place, node3->place, newlabel, -1);
  node0->place = newlabel;
  return;
}

void set_place2(struct node* node0, struct node* node1, string op1, string op2){
  pair <string, Entry*> newlabel = newlabel_sym(node0->node_type);
  emit(pair<string, Entry*>(op1, NULL), node1->place, pair<string, Entry*>(op2, NULL), newlabel, -1);
  node0->place = newlabel;
}

ul find_id() {
  static ul id = 0;
  return ++id;
}
// WORKING !!

vector<int> merging(vector<int> &l1, vector<int> &l2){
  vector<int> arr(l1.size() + l2.size());
  merge(l1.begin(), l1.end(), l2.begin(), l2.end(), arr.begin());
  return arr;
}

//for terminal symbols in ast
struct node *term_symb(char *str) {
  struct node* head = new node();
  ul size1 = strlen(str);
  head->token = (char*)malloc(2*size1 + 1);
  strcpy(head->token, str);
  head->id = find_id();
  char temp_str[2*strlen(head->token)];
  ul j = 0;
  // To remove '\n' from the terminal symbol. To make \n as \\n 
  for(ul i=0; i < strlen(head->token); i++){
      if(head->token[i]=='\\'){
        temp_str[j] = '\\';
        j++;
      }
      temp_str[j] = head->token[i];
      j++;
  }
  temp_str[j] = '\0';
  strcpy(head->token, temp_str);
    
  if(str[0] == '"'){ //for strings like "hello"
        strncpy(head->token, (head->token + 1), strlen(head->token)-2);
        head->token[strlen(head->token)-2] = '\0';
        fprintf(ast, "\t%lu [label=\"\\\"%s\\\"\"];\n", head->id,head->token); // to print strings like "hello" in ast node label ="\"hello\""
    }else{
        fprintf(ast, "\t%lu [label=\"%s\"];\n", head->id,head->token);
    }
  return head;
}

struct node *non_term_symb(char* str, char *op, struct node *node1, struct node *node2) {
  struct node *head = new node();
  ul size1 = strlen(str);
  head->token = (char*)malloc(size1 + 1);
  strcpy(head->token, str);
  head->id = find_id();
  ul op_id = find_id();
  if(op) fprintf(ast, "\t%lu [label=\"%s\"];\n", op_id, op);
  head->token[size1] = '\0';
  fprintf(ast, "\t%lu [label=\"%s\"];\n", head->id, head->token);
  if(node1) fprintf(ast, "\t%lu -> %lu;\n", head->id, node1->id);
  if(op) fprintf(ast, "\t%lu -> %lu;\n", head->id, op_id);
  if(node2)fprintf(ast, "\t%lu -> %lu;\n", head->id, node2->id);
  return head;
}

struct node *non_term_symb_3(char *str,struct node* node1 ,struct node *node2, struct node *node3) {
  struct node* head = new node();
  ul size1 = strlen(str);
  head->token = (char*)malloc(size1 + 1);
  strcpy(head->token, str);
  head->id = find_id();
  head->token[size1] = '\0';
  fprintf(ast, "\t%lu [label=\"%s\"];\n", head->id, head->token);
  if(node1) fprintf(ast, "\t%lu -> %lu;\n", head->id, node1->id);
  if(node2) fprintf(ast, "\t%lu -> %lu;\n", head->id, node2->id);
  if(node3)fprintf(ast, "\t%lu -> %lu;\n", head->id, node3->id);
  return head;
}

struct node *non_term_symb_4(char *str,struct node *node1,struct node *node2, struct node *node3, struct node *node4, char* op) {
  struct node* head = new node();
  ul size1 = strlen(str);
  head->token = (char*)malloc(size1 + 1);
  strcpy(head->token, str);
  head->id = find_id();
  ul op_id = find_id();
  if(op)  fprintf(ast,"\t%lu [label=\"%s\"];\n",op_id,op);
  head->token[size1] = '\0';
  fprintf(ast, "\t%lu [label=\"%s\"];\n", head->id, head->token);
  if(node1) fprintf(ast, "\t%lu -> %lu;\n", head->id, node1->id);
  if(node2) fprintf(ast, "\t%lu -> %lu;\n", head->id, node2->id);
  if(node3)fprintf(ast, "\t%lu -> %lu;\n", head->id, node3->id);
  if (node4) fprintf(ast,"\t%lu -> %lu;\n",head->id ,node4->id);
  if(op) fprintf(ast,"\t%lu -> %lu;\n",head->id,op_id);
  return head;
}

struct node *non_term_symb_5(char *str,struct node *node1,struct node *node2, struct node *node3, struct node *node4, struct node* node5) {
  struct node* head = new node();
  ul size1 = strlen(str);
  head->token = (char*)malloc(size1 + 1);
  strcpy(head->token, str);
  head->id = find_id();
  head->token[size1] = '\0';
  fprintf(ast, "\t%lu [label=\"%s\"];\n", head->id, head->token);
  if(node1) fprintf(ast, "\t%lu -> %lu;\n", head->id, node1->id);
  if(node2) fprintf(ast, "\t%lu -> %lu;\n", head->id, node2->id);
  if(node3)fprintf(ast, "\t%lu -> %lu;\n", head->id, node3->id);
  if (node4) fprintf(ast,"\t%lu -> %lu;\n",head->id ,node4->id);
  if(node5) fprintf(ast,"\t%lu -> %lu;\n",head->id,node5->id);
  return head;
}

struct node *non_term_symb_enum(char *str,char *op1,char *op2, struct node *node1,char *op3) {
  struct node *head = new node();
  ul size1 = strlen(str);
  head->token = (char*)malloc(size1 + 1);
  strcpy(head->token, str);
  head->id = find_id();
  ul op1_id = find_id();
  ul op2_id = find_id();
  ul op3_id = find_id();
  if(op1) fprintf(ast, "\t%lu [label=\"%s\"];\n", op1_id, op1);
  if(op3) fprintf(ast, "\t%lu [label=\"%s\"];\n", op2_id, op2);
  if(op2) fprintf(ast, "\t%lu [label=\"%s\"];\n", op3_id, op3);
  head->token[size1] = '\0';
  fprintf(ast, "\t%lu [label=\"%s\"];\n", head->id, head->token);
  if(op1) fprintf(ast, "\t%lu -> %lu;\n", head->id, op1_id);
  if(op2) fprintf(ast, "\t%lu -> %lu;\n", head->id, op2_id);
  if(node1)fprintf(ast, "\t%lu -> %lu;\n", head->id, node1->id);
  if(op3) fprintf(ast, "\t%lu -> %lu;\n", head->id, op3_id);
  return head;
}








