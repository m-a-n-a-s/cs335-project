#include "semanticCheck.h"
#include "symbolTable.h"


// string convert_to_string(char* str){
//    int i;
//    string s = "";
//    for (i = 0; i < strlen(str); i++) {
//       s = s + str[i];
//    }
//    return s;
// }


char* constant(int num_type){
    if(num_type==1) return "int";
    if(num_type==2) return "long";
    if(num_type==3) return "long long";
    if(num_type==4) return "float";
    if(num_type==5) return "double";
    if(num_type==6) return "long double";
    return "default";
}

char* primary_expr(char* identifier1){
    string identifier(identifier1);
    Entry* n = lookup(identifier);
    if(n){
	char* s = new char();
	strcpy(s, (n->type).c_str());
	return s;
    }
    return NULL;	
}
 
char* postfix_expr(string type, int Number){
    char* type_new = new char();
    strcpy(type_new, type.c_str());
    if(Number==1){ // postfix_expression '[' expression ']' 
        if(type[type.size()-1]=='*'){
	    type_new[type.size()-1]='\0';	
	    return type_new;
	}
	else 
	    return NULL;
    }
    if (Number==2){ // postfix_expression '(' argument_expression_list ')'
	string tmp = type.substr(0,5);
	if(tmp==convert_to_string("FUNC_")){
	    type_new += 5;
	    return type_new;
	}
	else 
	    return NULL;
    }
    if (Number==3){
	string tmp = type.substr(0,5);
	if(tmp==convert_to_string("FUNC_")){
	    type_new += 5;
	    return type_new;
	}
	else 
	    return NULL;
    }
    if (Number==6 || Number==7){ // postfix_expression INC_OP/DEC_OP
	if(is_Intgr(type)){
	    return type_new;
	}
	else 
	    return NULL;
    }
    if (Number==8|| Number==9){
        return type_new;
    }
}

bool is_Intgr (string type){
   if(type==convert_to_string("int")) return true;
   if(type==convert_to_string("long")) return true;
   if(type==convert_to_string("long long")) return true;
   if(type==convert_to_string("long int")) return true;
   if(type==convert_to_string("long long int")) return true;
   if(type==convert_to_string("unsigned int")) return true;
   if(type==convert_to_string("unsigned long")) return true;
   if(type==convert_to_string("unsigned long long")) return true;
   if(type==convert_to_string("unsigned long int")) return true;
   if(type==convert_to_string("unsigned long long int")) return true;
   if(type==convert_to_string("signed int")) return true;
   if(type==convert_to_string("signed long")) return true;
   if(type==convert_to_string("signed long long")) return true;
   if(type==convert_to_string("signed long int")) return true;
   if(type==convert_to_string("signed long long int")) return true;
   if(type==convert_to_string("short")) return true;
   if(type==convert_to_string("short int")) return true;
   if(type==convert_to_string("signed short")) return true;
   if(type==convert_to_string("unsigned short")) return true;
   if(type==convert_to_string("unsigned short int")) return true;
   if(type==convert_to_string("signed short int")) return true;
   return false;
}

char* argument_expr(string type1, string type2, int Number){
    char* a = new char();
    a = "void";
    if(Number==1){ //assign_expression
	if(type1==convert_to_string("void"))
	     return a;
	else {
	    a = "error";
	    return a;
	}	
    }
    if(Number==2){
	if(type1==convert_to_string("void") && type2==convert_to_string("void"))
	     return a;
	else {
	    a = "error";
	    return a;
	}	
    }
}

bool is_SignedInt (string type){
   if(type==convert_to_string("int")) return true;
   if(type==convert_to_string("long")) return true;
   if(type==convert_to_string("long long")) return true;
   if(type==convert_to_string("long int")) return true;
   if(type==convert_to_string("long long int")) return true;
   if(type==convert_to_string("signed int")) return true;
   if(type==convert_to_string("signed long")) return true;
   if(type==convert_to_string("signed long long")) return true;
   if(type==convert_to_string("signed long int")) return true;
   if(type==convert_to_string("signed long long int")) return true;
   if(type==convert_to_string("short")) return true;
   if(type==convert_to_string("short int")) return true;
   if(type==convert_to_string("signed short")) return true;
   if(type==convert_to_string("signed short int")) return true;

   return false;
}


bool is_float (string type){
   if(type==convert_to_string("float")) return true;
   if(type==convert_to_string("double")) return true;
   if(type==convert_to_string("long double")) return true;
   if(type==convert_to_string("unsigned float")) return true;
   if(type==convert_to_string("unsigned double")) return true;
   if(type==convert_to_string("unsigned long double")) return true;
   if(type==convert_to_string("signed float")) return true;
   if(type==convert_to_string("signed double")) return true;
   if(type==convert_to_string("signed long double")) return true;

   return false;
}

bool is_SignedFloat (string type){
   if(type==convert_to_string("float")) return true;
   if(type==convert_to_string("double")) return true;
   if(type==convert_to_string("long double")) return true;
   if(type==convert_to_string("signed float")) return true;
   if(type==convert_to_string("signed double")) return true;
   if(type==convert_to_string("signed long double")) return true;

   return false;
}

char* shift_expr(string type1,string type2){
      char *a =new char();
      a = "True";
      if(is_Intgr(type1)&&is_Intgr(type2))
          return a;
      else return NULL;
} 

char* unary_expr(string op, string type, int Number){
    char* a= new char();
    //cout<<"hello "<<op<<"\n";
    if(Number==1){ //unary_operator cast_expression
	    if (op==convert_to_string("&")){
		    type = type+ convert_to_string("*");
	    }
            if (op==convert_to_string("*")){
                 return postfix_expr(type, 1);
	     }
	    if (op==convert_to_string("+")){
		if(is_float(type) || is_Intgr(type)){;}
		else return NULL;
	     }
	    if (op==convert_to_string("-")){
		if(is_float(type) || is_Intgr(type)){;}
		else return NULL;
	     }
	    if	(op == convert_to_string("~")){	
		if(is_Intgr(type)|| type =="bool") {;}
		else return NULL;
            }
            if	(op == convert_to_string("!")){	
		if(type =="bool") {;}
		else return NULL;
            }    
	    strcpy(a, type.c_str());
    }
    return a;
}

char* validAssign(string type1,string type2){
    char * a =new char();
   if(is_Intgr(type2) && (type1[type1.size()-1]=='*')){
      a="warning";return a;
   }
   if(is_Intgr(type1) && (type2[type2.size()-1]=='*')){
      a="warning";return a;
   }
    if(type1==convert_to_string("char"))  type1=convert_to_string("long long");
    if(is_Intgr(type1))   type1=convert_to_string("long double");
    if(type2==convert_to_string("char"))  type2=convert_to_string("long long");
    if(is_Intgr(type2))   type2=convert_to_string("long double");
    
   if(is_float(type1) && is_float(type2)){ a = "true";return a; } 
   if(type1==convert_to_string("void*") && (type2[type2.size()-1]=='*')){
      a="true";return a;
   }
   if(type2==convert_to_string("void*") && (type1[type1.size()-1]=='*')){
      a="true";return a;
   }
   if(type1==type2){
     a="true";return a;
   }
   if((type2[type2.size()-1]=='*') && (type1[type1.size()-1]=='*')){
      a="warning";return a;
   }
   return NULL;
}

char* additive_expr(string type1,string type2,char op){
	char *a = new char();
	if(is_Intgr(type1)|| is_float(type1)){
		if(is_Intgr(type2)||is_float(type2)){
			if(is_Intgr(type1)&&is_Intgr(type2)){ a="int"; }
			else { a="real"; }
			return a;
		} 
	}
	else if(type1==convert_to_string("char")&&is_Intgr(type2)) {
		a="char";return a;
	}
        else if(type2==convert_to_string("char")&&is_Intgr(type1)){
               a="char";return a;
        }
        else if((type1[type1.size()-1]=='*')&&is_Intgr(type2)){
            strcpy(a,type1.c_str());
          return a; 
        }
        else if((type2[type2.size()-1]=='*')&&is_Intgr(type1)){
            strcpy(a,type2.c_str());return a;
        }        
	return NULL;
}


char* multilplicative_expr(string type1, string type2, char op){
    char* a = new char();
    if(is_Intgr(type1)|| is_float(type1)){
	if(is_Intgr(type2)||is_float(type2)){
		if(op == '%'){
			if(is_Intgr(type1)&&is_Intgr(type2)){
			    a = "int";
			    return a;
			}
		}
		if(op == '*'|| op == '/'){
                     if(is_Intgr(type1) && is_Intgr(type2)){ a="int"; }
                     else { a="float"; }
                     return a;
	        }
        }	
  }
  return NULL;
}

char* relational_expr(string type1,string type2,char * op){
     char *a = new char();
     if(is_Intgr(type1)||is_float(type1)||(type1==convert_to_string("char"))){
         if(is_Intgr(type2)||is_float(type2)||(type2==convert_to_string("char")))
         {
             a="bool";return a;
         }  
         else if(type2[type2.size()-1]=='*')
         {
             if(is_Intgr(type1)||(type1==convert_to_string("char"))){ a = "Bool"; 
                        return a; }
             else return NULL;
         }
     }
     if(type1[type1.size()-1]=='*')
       {
             if(is_Intgr(type2)||(type2==convert_to_string("char"))){ a = "Bool"; 
                  return a; }
             else return NULL;

       }
       return NULL;
}
char * equality_expr(string type1,string type2){
       char *a = new char();
       if(is_Intgr(type1)||is_float(type1)||(type1=="char")){
             if(is_Intgr(type2)||is_float(type2)||(type2=="char")){
             a="True";return a;
             }
       }
       else if(type1[type1.size()-1]=='*' && is_Intgr(type2)){
           a="true";return a;
       }
       else if(type2[type2.size()-1]=='*' && is_Intgr(type1)){
           a="true";return a;
       }
       else if(!strcmp(type1.c_str(),type2.c_str())){
            a = "True";return a;
       }
   return NULL;
}

char* conditional_expr(string type1,string type2){
     char* a = new char();
     if(type1==convert_to_string("char")) type1 = convert_to_string("long long");
     if(is_Intgr(type1))          type1 = convert_to_string("long double");
     if(type2==convert_to_string("char")) type2 = convert_to_string("long long");
     if(is_Intgr(type2))          type2 = convert_to_string("long double");
     if(is_float(type1) && is_float(type2)){ a="long double";
                                          return a; }
     if( type1 == type2 ){
          strcpy(a,type1.c_str()); return a;
     }
     if((type1[type1.size()-1]=='*') && type2[type2.size()-1]=='*'){
         a = "void*"; return a;
     }
     
   return NULL;
}

char* bitwise_expr(string type1,string type2){ // ^,&,|
      char * a = new char();
      if((type1==convert_to_string("bool"))&&(type2==convert_to_string("bool"))){
          a="true";return a;
      }
      if(is_Intgr(type1) || type1==convert_to_string("bool")){
            if(is_Intgr(type2) || type2==convert_to_string("bool")){
                a="True"; return a;
            }               
      } 
      return NULL;
}

char* assign_expr(string type1,string type2,char* op){
    char *a = new char();
    if(!strcmp(op,"=")){
        a = validAssign(type1,type2);
        if(a) return a;
        else return NULL;
    }
    else if((!strcmp(op,"*="))||(!strcmp(op,"/="))||(!strcmp(op,"%="))){
        a = multilplicative_expr(type1,type2,op[0]);
        if(a){ a="true"; return a; }
    }
    else if((!strcmp(op,"+="))||(!strcmp(op,"-="))){
        a = additive_expr(type1,type2,op[0]);
        if(a){ a="true"; return a;}
    }
    else if((!strcmp(op,">>="))||(!strcmp(op,"<<="))){
        a = shift_expr(type1,type2);
        if(a){ a="true"; return a;}
    }
    else if((!strcmp(op,"&="))||(!strcmp(op,"^="))||(!strcmp(op,"|="))){
        a = bitwise_expr(type1,type2);
        if(a){ a="true"; return a;}
    }
    return NULL;
}

