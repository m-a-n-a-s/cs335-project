#include "functions.h"

extern FILE *digraph;

int getNodeId() {
  static int nodeId = 0;
  nodeId += 1;
  return nodeId;
}

void graphInitialization() {
  fprintf(digraph, "digraph G {\n");
  fprintf(digraph, "\tordering=out;\n");
}

void graphEnd() {
  fprintf(digraph, "}\n");
}

struct node *nonTerminal(char *str,char *op, struct node *l, struct node *r) {
  struct node *n = (struct node*) malloc(sizeof(struct node));
  n->name = str;
  n->id = getNodeId();
  int op_id = getNodeId();
  char *op_str = op;
  if(op){

    fprintf(digraph, "\t%lu [label=\"%s\"];\n", op_id, op_str);
  }
  n->name[strlen(n->name)] = '\0';
  fprintf(digraph, "\t%lu [label=\"%s\"];\n", n->id, n->name);
  if(l) fprintf(digraph, "\t%lu -> %lu;\n", n->id, l->id);
  if(op) fprintf(digraph, "\t%lu -> %lu;\n", n->id, op_id);
  if(r)fprintf(digraph, "\t%lu -> %lu;\n", n->id, r->id);
  return n;
}
struct node *nonTerminal1(char *str,char *op1, struct node *l,char *op2) {
  struct node *n = (struct node*) malloc(sizeof(struct node));
  n->name = str;
  n->id = getNodeId();
  int op1_id = getNodeId();
  char *op1_str = op1;
  int op2_id = getNodeId();
  char *op2_str = op2;
  if(op1){

    fprintf(digraph, "\t%lu [label=\"%s\"];\n", op1_id, op1_str);
  }
  if(op2){

    fprintf(digraph, "\t%lu [label=\"%s\"];\n", op2_id, op2_str);
  }
  n->name[strlen(n->name)] = '\0';
  fprintf(digraph, "\t%lu [label=\"%s\"];\n", n->id, n->name);
  if(op1) fprintf(digraph, "\t%lu -> %lu;\n", n->id, op1_id);
  if(l)fprintf(digraph, "\t%lu -> %lu;\n", n->id, l->id);
  if(op2) fprintf(digraph, "\t%lu -> %lu;\n", n->id, op2_id);
  return n;
}
struct node *nonTerminal3(char *str,char *op1,char *op3, struct node *l,char *op2) {
  struct node *n = (struct node*) malloc(sizeof(struct node));
  n->name = str;
  n->id = getNodeId();
  int op1_id = getNodeId();
  char *op1_str = op1;
  int op3_id = getNodeId();
  char *op3_str = op3;
  int op2_id = getNodeId();
  char *op2_str = op2;
  if(op1){

    fprintf(digraph, "\t%lu [label=\"%s\"];\n", op1_id, op1_str);
  }
  if(op3){

    fprintf(digraph, "\t%lu [label=\"%s\"];\n", op3_id, op3_str);
  }

  if(op2){

    fprintf(digraph, "\t%lu [label=\"%s\"];\n", op2_id, op2_str);
  }
  n->name[strlen(n->name)] = '\0';
  fprintf(digraph, "\t%lu [label=\"%s\"];\n", n->id, n->name);
  if(op1) fprintf(digraph, "\t%lu -> %lu;\n", n->id, op1_id);
  if(op3) fprintf(digraph, "\t%lu -> %lu;\n", n->id, op3_id);
  if(l)fprintf(digraph, "\t%lu -> %lu;\n", n->id, l->id);
  if(op2) fprintf(digraph, "\t%lu -> %lu;\n", n->id, op2_id);
  return n;
}
struct node *nonTerminal2(char *str,struct node *l,struct node *m, struct node *r) {
  struct node *n = (struct node*) malloc(sizeof(struct node));
  n->name = str;
  n->id = getNodeId();
  n->name[strlen(n->name)] = '\0';
  fprintf(digraph, "\t%lu [label=\"%s\"];\n", n->id, n->name);
  if(l) fprintf(digraph, "\t%lu -> %lu;\n", n->id, l->id);
  if(m) fprintf(digraph, "\t%lu -> %lu;\n", n->id, m->id);
  if(r)fprintf(digraph, "\t%lu -> %lu;\n", n->id, r->id);
  return n;
}

struct node *nonTerminalFourChild(char *str,struct node *a1,struct node *a2, struct node *a3, struct node*a4, char* op) {
  struct node *n = (struct node*) malloc(sizeof(struct node));
  n->name = str;
  n->id = getNodeId();
  int op_id = getNodeId();
  char *op_str = op;
  if(op){
    fprintf(digraph,"\t%lu [label=\"%s\"];\n",op_id,op_str);
  }
  n->name[strlen(n->name)] = '\0';
  fprintf(digraph, "\t%lu [label=\"%s\"];\n", n->id, n->name);
  if(a1) fprintf(digraph, "\t%lu -> %lu;\n", n->id, a1->id);
  if(a2) fprintf(digraph, "\t%lu -> %lu;\n", n->id, a2->id);
  if(a3)fprintf(digraph, "\t%lu -> %lu;\n", n->id, a3->id);
  if(a4) fprintf(digraph,"\t%lu -> %lu;\n",n->id,a4->id);
  if(op) fprintf(digraph,"\t%lu -> %lu;\n",n->id,op_id);
  return n;
}

struct node *nonTerminalFiveChild(char *str,struct node *a1,struct node *a2, struct node *a3, struct node*a4, struct node* a5) {
  struct node *n = (struct node*) malloc(sizeof(struct node));
  n->name = str;
  n->id = getNodeId();
  n->name[strlen(n->name)] = '\0';
  fprintf(digraph, "\t%lu [label=\"%s\"];\n", n->id, n->name);
  if(a1) fprintf(digraph, "\t%lu -> %lu;\n", n->id, a1->id);
  if(a2) fprintf(digraph, "\t%lu -> %lu;\n", n->id, a2->id);
  if(a3)fprintf(digraph, "\t%lu -> %lu;\n", n->id, a3->id);
  if(a4) fprintf(digraph,"\t%lu -> %lu;\n",n->id,a4->id);
  if(a5) fprintf(digraph,"\t%lu -> %lu;\n",n->id,a5->id);
  return n;
}

struct node *terminal(char *str) {
  struct node *n = (struct node*) malloc(sizeof(struct node));
  n->name=str;
  n->id = getNodeId();
  // checking '\n' character
  // the loop run til len because the last character is ""
    char t[2*strlen(n->name)];
    int j = 0;
    for(int i=0; i < strlen(n->name); ++i){
        if(n->name[i]=='\\'){
        char tmp = '\\';
        t[j] = tmp;
        j++;
        }
        t[j] = n->name[i];
        j++;
    }
    t[j] = '\0';
    strcpy(n->name, t);

  // printing sting token
  if(str[0] == '"'){
        strncpy(n->name, (n->name + 1), strlen(n->name)-2);
        n->name[strlen(n->name)-2] = '\0';
        fprintf(digraph, "\t%lu [label=\"\\\"%s\\\"\"];\n", n->id,n->name);
    }else{
        fprintf(digraph, "\t%lu [label=\"%s\"];\n", n->id,n->name);
    }
  return n;
}

struct node *nonTerminalRoundB(char *str, struct node *a) {
  struct node *n = (struct node*) malloc(sizeof(struct node));
  n->name=str;
  n->id = getNodeId();
  n->name[strlen(n->name)] = '\0';
  fprintf(digraph, "\t%lu [label=\"%s\"];\n", n->id,n->name );
  int newBracketId = getNodeId();
  fprintf(digraph, "\t%lu [label=\"( )\"];\n", newBracketId );
  if(a) fprintf(digraph, "\t%lu -> %lu;\n", n->id, a->id);
  fprintf(digraph, "\t%lu -> %lu;\n", n->id, newBracketId);
  return n;
}
struct node *nonTerminalSquareB(char *str, struct node *a) {
  struct node *n = (struct node*) malloc(sizeof(struct node));
  n->name=str;
  n->id = getNodeId();
  n->name[strlen(n->name)] = '\0';
  fprintf(digraph, "\t%lu [label=\"%s\"];\n", n->id,n->name );
  int newBracketId = getNodeId();
  fprintf(digraph, "\t%lu [label=\"[ ]\"];\n", newBracketId );
  if(a) fprintf(digraph, "\t%lu -> %lu;\n", n->id, a->id);
  fprintf(digraph, "\t%lu -> %lu;\n", n->id, newBracketId);
  return n;
}

// struct node *nonTerminalCurlyB(char *str, struct node *a) {
//   struct node *n = (struct node*) malloc(sizeof(struct node));
//   n->name=str;
//   n->id = getNodeId();
//   fprintf(digraph, "\t%lu [label=\"%s\"];\n", n->id,n->name );
//   int newBracketId = getNodeId();
//   fprintf(digraph, "\t%lu [label=\"{ }\"];\n", newBracketId );
//   if(a) fprintf(digraph, "\t%lu -> %lu;\n", n->id, a->id);
//   fprintf(digraph, "\t%lu -> %lu;\n", n->id, newBracketId);
//   return n;
// }