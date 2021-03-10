#include "functions.h"

extern FILE *ast;

#define ul unsigned long

ul find_id() {
  static ul id = 0;
  return ++id;
}
// WORKING !!

struct node *square(char *str, struct node *node1) {
  struct node* head = (struct node*) malloc(sizeof(struct node));
  ul size1 = strlen(str);
  head->token = (char*)malloc(size1 + 1);
  strcpy(head->token, str);
  head->id = find_id();
  head->token[size1] = '\0';
  fprintf(ast, "\t%lu [label=\"%s\"];\n", head->id,head->token );
  ul brac_id = find_id();
  fprintf(ast, "\t%lu [label=\"[ ]\"];\n", brac_id );
  if(node1) fprintf(ast, "\t%lu -> %lu;\n", head->id, node1->id);
  fprintf(ast, "\t%lu -> %lu;\n", head->id, brac_id);
  return head;
  // return NULL;
}

struct node *parentheses(char *str, struct node *node1) {
  struct node* head = (struct node*) malloc(sizeof(struct node));
  ul size1 = strlen(str);
  head->token = (char*)malloc(size1 + 1);
  strcpy(head->token, str);
  head->id = find_id();
  head->token[size1] = '\0';
  fprintf(ast, "\t%lu [label=\"%s\"];\n", head->id,head->token );
  ul brac_id = find_id();
  fprintf(ast, "\t%lu [label=\"( )\"];\n", brac_id );
  if(node1) fprintf(ast, "\t%lu -> %lu;\n", head->id, node1->id);
  fprintf(ast, "\t%lu -> %lu;\n", head->id, brac_id);
  return head;
  // return NULL;
}

struct node *term_symb(char *str) {
  struct node* head = (struct node*) malloc(sizeof(struct node));
  // puts(str);
  ul size1 = strlen(str);
  head->token = (char*)malloc(2*size1 + 1);
  strcpy(head->token, str);
  head->id = find_id();
  char temp_str[2*strlen(head->token)];
  ul j = 0;
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
    
  if(str[0] == '"'){
        strncpy(head->token, (head->token + 1), strlen(head->token)-2);
        head->token[strlen(head->token)-2] = '\0';
        fprintf(ast, "\t%lu [label=\"\\\"%s\\\"\"];\n", head->id,head->token);
    }else{
        fprintf(ast, "\t%lu [label=\"%s\"];\n", head->id,head->token);
    }
  return head;
  // return NULL;
}

struct node *non_term_symb(char* str, char *root, struct node *left, struct node *right) {
  struct node *head = (struct node*) malloc(sizeof(struct node));
  ul size1 = strlen(str);
  head->token = (char*)malloc(size1 + 1);
  strcpy(head->token, str);
  head->id = find_id();
  ul root_id = find_id();
  if(root) fprintf(ast, "\t%lu [label=\"%s\"];\n", root_id, root);
  head->token[size1] = '\0';
  fprintf(ast, "\t%lu [label=\"%s\"];\n", head->id, head->token);
  if(left) fprintf(ast, "\t%lu -> %lu;\n", head->id, left->id);
  if(root) fprintf(ast, "\t%lu -> %lu;\n", head->id, root_id);
  if(right)fprintf(ast, "\t%lu -> %lu;\n", head->id, right->id);
  //printf("non_term_symb Working\n");
  return head;
  // return NULL;
}
struct node *non_term_symb_1(char *str,char *root1, struct node *left ,char *root2) {
  struct node *head = (struct node*) malloc(sizeof(struct node));
  ul size1 = strlen(str);
  head->token = (char*)malloc(size1 + 1);
  strcpy(head->token, str);
  head->id = find_id();
  ul root1_id = find_id();
  ul root2_id = find_id();
  if(root1) fprintf(ast, "\t%lu [label=\"%s\"];\n", root1_id, root1);
  if(root2) fprintf(ast, "\t%lu [label=\"%s\"];\n", root2_id, root2);
  head->token[size1] = '\0';
  fprintf(ast, "\t%lu [label=\"%s\"];\n", head->id, head->token);
  if(root1) fprintf(ast, "\t%lu -> %lu;\n", head->id, root1_id);
  if(left)fprintf(ast, "\t%lu -> %lu;\n", head->id, left->id);
  if(root2) fprintf(ast, "\t%lu -> %lu;\n", head->id, root2_id);
  return head;
  // return NULL;
}
struct node *non_term_symb_3(char *str,char *root1,char *root3, struct node *left,char *root2) {
  struct node *head = (struct node*) malloc(sizeof(struct node));
  ul size1 = strlen(str);
  head->token = (char*)malloc(size1 + 1);
  strcpy(head->token, str);
  head->id = find_id();
  ul root1_id = find_id();
  ul root3_id = find_id();
  ul root2_id = find_id();
  if(root1) fprintf(ast, "\t%lu [label=\"%s\"];\n", root1_id, root1);
  if(root3) fprintf(ast, "\t%lu [label=\"%s\"];\n", root3_id, root3);
  if(root2) fprintf(ast, "\t%lu [label=\"%s\"];\n", root2_id, root2);
  head->token[size1] = '\0';
  fprintf(ast, "\t%lu [label=\"%s\"];\n", head->id, head->token);
  if(root1) fprintf(ast, "\t%lu -> %lu;\n", head->id, root1_id);
  if(root3) fprintf(ast, "\t%lu -> %lu;\n", head->id, root3_id);
  if(left)fprintf(ast, "\t%lu -> %lu;\n", head->id, left->id);
  if(root2) fprintf(ast, "\t%lu -> %lu;\n", head->id, root2_id);
  return head;
  // return NULL;
}
struct node *non_term_symb_2(char *str,struct node *left ,struct node *mid, struct node *right) {
  struct node* head = (struct node*) malloc(sizeof(struct node));
  ul size1 = strlen(str);
  head->token = (char*)malloc(size1 + 1);
  strcpy(head->token, str);
  head->id = find_id();
  head->token[size1] = '\0';
  fprintf(ast, "\t%lu [label=\"%s\"];\n", head->id, head->token);
  if(left) fprintf(ast, "\t%lu -> %lu;\n", head->id, left->id);
  if(mid) fprintf(ast, "\t%lu -> %lu;\n", head->id, mid->id);
  if(right)fprintf(ast, "\t%lu -> %lu;\n", head->id, right->id);
  return head;
  // return NULL;
}

struct node *non_term_symb_4(char *str,struct node *node1,struct node *node2, struct node *node3, struct node *node4, char* root) {
  struct node* head = (struct node*) malloc(sizeof(struct node));
  ul size1 = strlen(str);
  head->token = (char*)malloc(size1 + 1);
  strcpy(head->token, str);
  head->id = find_id();
  ul root_id = find_id();
  if(root)  fprintf(ast,"\t%lu [label=\"%s\"];\n",root_id,root);
  head->token[size1] = '\0';
  fprintf(ast, "\t%lu [label=\"%s\"];\n", head->id, head->token);
  if(node1) fprintf(ast, "\t%lu -> %lu;\n", head->id, node1->id);
  if(node2) fprintf(ast, "\t%lu -> %lu;\n", head->id, node2->id);
  if(node3)fprintf(ast, "\t%lu -> %lu;\n", head->id, node3->id);
  if (node4) fprintf(ast,"\t%lu -> %lu;\n",head->id ,node4->id);
  if(root) fprintf(ast,"\t%lu -> %lu;\n",head->id,root_id);
  return head;
  // return NULL;
}

struct node *non_term_symb_5(char *str,struct node *node1,struct node *node2, struct node *node3, struct node *node4, struct node* node5) {
  struct node* head = (struct node*) malloc(sizeof(struct node));
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
  // return NULL;
}

