#include "functions.h"

extern FILE *digraph;

int find_id() {
  static int nodeId = 0;
  nodeId += 1;
  return nodeId;
}
// WORKING !!
struct node *non_term_symb(char *str,char *op, struct node *l, struct node *r) {
  struct node *n = (struct node*) malloc(sizeof(struct node));
  int size1 = strlen(str);
  n->name = (char*)malloc(size1 + 1);
  strcpy(n->name, str);
  n->id = find_id();
  int op_id = find_id();
  if(op){
    fprintf(digraph, "\t%lu [label=\"%s\"];\n", op_id, op);
  }
  n->name[size1] = '\0';
  fprintf(digraph, "\t%lu [label=\"%s\"];\n", n->id, n->name);
  if(l) fprintf(digraph, "\t%lu -> %lu;\n", n->id, l->id);
  if(op) fprintf(digraph, "\t%lu -> %lu;\n", n->id, op_id);
  if(r)fprintf(digraph, "\t%lu -> %lu;\n", n->id, r->id);
  //printf("non_term_symb Working\n");
  return n;
  // return NULL;
}
struct node *non_term_symb_1(char *str,char *op1, struct node *l,char *op2) {
  struct node *n = (struct node*) malloc(sizeof(struct node));
  int size1 = strlen(str);
  n->name = (char*)malloc(size1 + 1);
  strcpy(n->name, str);
  n->id = find_id();
  int op1_id = find_id();
  int op2_id = find_id();
  if(op1){

    fprintf(digraph, "\t%lu [label=\"%s\"];\n", op1_id, op1);
  }
  if(op2){

    fprintf(digraph, "\t%lu [label=\"%s\"];\n", op2_id, op2);
  }
  n->name[size1] = '\0';
  fprintf(digraph, "\t%lu [label=\"%s\"];\n", n->id, n->name);
  if(op1) fprintf(digraph, "\t%lu -> %lu;\n", n->id, op1_id);
  if(l)fprintf(digraph, "\t%lu -> %lu;\n", n->id, l->id);
  if(op2) fprintf(digraph, "\t%lu -> %lu;\n", n->id, op2_id);
  return n;
  // return NULL;
}
struct node *non_term_symb_3(char *str,char *op1,char *op3, struct node *l,char *op2) {
  struct node *n = (struct node*) malloc(sizeof(struct node));
  int size1 = strlen(str);
  n->name = (char*)malloc(size1 + 1);
  strcpy(n->name, str);
  n->id = find_id();
  int op1_id = find_id();
  int op3_id = find_id();
  int op2_id = find_id();
  if(op1){

    fprintf(digraph, "\t%lu [label=\"%s\"];\n", op1_id, op1);
  }
  if(op3){

    fprintf(digraph, "\t%lu [label=\"%s\"];\n", op3_id, op3);
  }

  if(op2){

    fprintf(digraph, "\t%lu [label=\"%s\"];\n", op2_id, op2);
  }
  n->name[size1] = '\0';
  fprintf(digraph, "\t%lu [label=\"%s\"];\n", n->id, n->name);
  if(op1) fprintf(digraph, "\t%lu -> %lu;\n", n->id, op1_id);
  if(op3) fprintf(digraph, "\t%lu -> %lu;\n", n->id, op3_id);
  if(l)fprintf(digraph, "\t%lu -> %lu;\n", n->id, l->id);
  if(op2) fprintf(digraph, "\t%lu -> %lu;\n", n->id, op2_id);
  return n;
  // return NULL;
}
struct node *non_term_symb_2(char *str,struct node *l,struct node *m, struct node *r) {
  struct node *n = (struct node*) malloc(sizeof(struct node));
  int size1 = strlen(str);
  n->name = (char*)malloc(size1 + 1);
  strcpy(n->name, str);
  n->id = find_id();
  n->name[size1] = '\0';
  fprintf(digraph, "\t%lu [label=\"%s\"];\n", n->id, n->name);
  if(l) fprintf(digraph, "\t%lu -> %lu;\n", n->id, l->id);
  if(m) fprintf(digraph, "\t%lu -> %lu;\n", n->id, m->id);
  if(r)fprintf(digraph, "\t%lu -> %lu;\n", n->id, r->id);
  return n;
  // return NULL;
}

struct node *non_term_symb_4(char *str,struct node *a1,struct node *a2, struct node *a3, struct node*a4, char* op) {
  struct node *n = (struct node*) malloc(sizeof(struct node));
  int size1 = strlen(str);
  n->name = (char*)malloc(size1 + 1);
  strcpy(n->name, str);
  n->id = find_id();
  int op_id = find_id();
  if(op){
    fprintf(digraph,"\t%lu [label=\"%s\"];\n",op_id,op);
  }
  n->name[size1] = '\0';
  fprintf(digraph, "\t%lu [label=\"%s\"];\n", n->id, n->name);
  if(a1) fprintf(digraph, "\t%lu -> %lu;\n", n->id, a1->id);
  if(a2) fprintf(digraph, "\t%lu -> %lu;\n", n->id, a2->id);
  if(a3)fprintf(digraph, "\t%lu -> %lu;\n", n->id, a3->id);
  if(a4) fprintf(digraph,"\t%lu -> %lu;\n",n->id,a4->id);
  if(op) fprintf(digraph,"\t%lu -> %lu;\n",n->id,op_id);
  return n;
  // return NULL;
}

struct node *non_term_symb_5(char *str,struct node *a1,struct node *a2, struct node *a3, struct node*a4, struct node* a5) {
  struct node *n = (struct node*) malloc(sizeof(struct node));
  int size1 = strlen(str);
  n->name = (char*)malloc(size1 + 1);
  strcpy(n->name, str);
  n->id = find_id();
  n->name[size1] = '\0';
  fprintf(digraph, "\t%lu [label=\"%s\"];\n", n->id, n->name);
  if(a1) fprintf(digraph, "\t%lu -> %lu;\n", n->id, a1->id);
  if(a2) fprintf(digraph, "\t%lu -> %lu;\n", n->id, a2->id);
  if(a3)fprintf(digraph, "\t%lu -> %lu;\n", n->id, a3->id);
  if(a4) fprintf(digraph,"\t%lu -> %lu;\n",n->id,a4->id);
  if(a5) fprintf(digraph,"\t%lu -> %lu;\n",n->id,a5->id);
  return n;
  // return NULL;
}

struct node *term_symb(char *str) {
  struct node *n = (struct node*) malloc(sizeof(struct node));
  // puts(str);
  int size1 = strlen(str);
  n->name = (char*)malloc(2*size1 + 1);
  strcpy(n->name, str);
  n->id = find_id();
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
    
  if(str[0] == '"'){
        strncpy(n->name, (n->name + 1), strlen(n->name)-2);
        n->name[strlen(n->name)-2] = '\0';
        fprintf(digraph, "\t%lu [label=\"\\\"%s\\\"\"];\n", n->id,n->name);
    }else{
        fprintf(digraph, "\t%lu [label=\"%s\"];\n", n->id,n->name);
    }
  return n;
  // return NULL;
}

struct node *parentheses(char *str, struct node *a) {
  struct node *n = (struct node*) malloc(sizeof(struct node));
  int size1 = strlen(str);
  n->name = (char*)malloc(size1 + 1);
  strcpy(n->name, str);
  n->id = find_id();
  n->name[size1] = '\0';
  fprintf(digraph, "\t%lu [label=\"%s\"];\n", n->id,n->name );
  int newBracketId = find_id();
  fprintf(digraph, "\t%lu [label=\"( )\"];\n", newBracketId );
  if(a) fprintf(digraph, "\t%lu -> %lu;\n", n->id, a->id);
  fprintf(digraph, "\t%lu -> %lu;\n", n->id, newBracketId);
  return n;
  return NULL;
}
struct node *square(char *str, struct node *a) {
  struct node *n = (struct node*) malloc(sizeof(struct node));
  int size1 = strlen(str);
  n->name = (char*)malloc(size1 + 1);
  strcpy(n->name, str);
  n->id = find_id();
  n->name[size1] = '\0';
  fprintf(digraph, "\t%lu [label=\"%s\"];\n", n->id,n->name );
  int newBracketId = find_id();
  fprintf(digraph, "\t%lu [label=\"[ ]\"];\n", newBracketId );
  if(a) fprintf(digraph, "\t%lu -> %lu;\n", n->id, a->id);
  fprintf(digraph, "\t%lu -> %lu;\n", n->id, newBracketId);
  return n;
  return NULL;
}

