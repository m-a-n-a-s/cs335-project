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


char* constant(int type){
    switch(type){
        case 1: return "long";
        case 2: return "long long";
        case 3: return "float";
        case 4: return "double";
        case 5: return "long double";
        default: return "default";
    }
}

bool is_Intgr (string type){
   if(type==convert_to_string("int")) return true;
   else if(type==convert_to_string("short")) return true;
   else if(type==convert_to_string("short int")) return true;
   else if(type==convert_to_string("signed short")) return true;
   else if(type==convert_to_string("unsigned short")) return true;
   else if(type==convert_to_string("unsigned short int")) return true;
   else if(type==convert_to_string("signed short int")) return true;
   else if(type==convert_to_string("long")) return true;
   else if(type==convert_to_string("long long")) return true;
   else if(type==convert_to_string("long int")) return true;
   else if(type==convert_to_string("long long int")) return true;
   else if(type==convert_to_string("unsigned int")) return true;
   else if(type==convert_to_string("unsigned long")) return true;
   else if(type==convert_to_string("unsigned long long")) return true;
   else if(type==convert_to_string("unsigned long int")) return true;
   else if(type==convert_to_string("unsigned long long int")) return true;
   else if(type==convert_to_string("signed int")) return true;
   else if(type==convert_to_string("signed long")) return true;
   else if(type==convert_to_string("signed long long")) return true;
   else if(type==convert_to_string("signed long int")) return true;
   else if(type==convert_to_string("signed long long int")) return true;
   else return false;
}

bool is_SignedInt (string type){
   if(type==convert_to_string("int")) return true;
   else if(type==convert_to_string("short")) return true;
   else if(type==convert_to_string("short int")) return true;
   else if(type==convert_to_string("signed short")) return true;
   else if(type==convert_to_string("signed short int")) return true;
   else if(type==convert_to_string("long")) return true;
   else if(type==convert_to_string("long long")) return true;
   else if(type==convert_to_string("long int")) return true;
   else if(type==convert_to_string("long long int")) return true;
   else if(type==convert_to_string("signed int")) return true;
   else if(type==convert_to_string("signed long")) return true;
   else if(type==convert_to_string("signed long long")) return true;
   else if(type==convert_to_string("signed long int")) return true;
   else if(type==convert_to_string("signed long long int")) return true;
   else return false;
}

bool is_float (string type){
   if(type==convert_to_string("float")) return true;
   else if(type==convert_to_string("double")) return true;
   else if(type==convert_to_string("long double")) return true;
   else if(type==convert_to_string("unsigned float")) return true;
   else if(type==convert_to_string("unsigned double")) return true;
   else if(type==convert_to_string("unsigned long double")) return true;
   else if(type==convert_to_string("signed float")) return true;
   else if(type==convert_to_string("signed double")) return true;
   else if(type==convert_to_string("signed long double")) return true;
   return false;
}

bool is_SignedFloat (string type){
   if(type==convert_to_string("float")) return true;
   else if(type==convert_to_string("double")) return true;
   else if(type==convert_to_string("long double")) return true;
   else if(type==convert_to_string("signed float")) return true;
   else if(type==convert_to_string("signed double")) return true;
   else if(type==convert_to_string("signed long double")) return true;
   else return false;
}

char* primary_expr(char* identifier1){
    string identifier(identifier1);
    Entry* n = lookup(identifier);
    if(!n){
        return NULL;
    }
    else{
        char* s = new char();
        strcpy(s, (n->type).c_str());
        return s;
    }	
}
 
char* postfix_expr(string type, int Number){
    char* type_new = new char();
    strcpy(type_new, type.c_str());

    switch(Number){
        case 1: {if(type[type.size()-1]=='*'){
                    type_new[type.size()-1]='\0';	
                    return type_new;
                }
                else{
                    return NULL;
                }
                }
        case 2: {if(type[type.size()-1]=='*'){
                    type_new[type.size()-1]='\0';	
                    return type_new;
                }
                else{
                    return NULL;
                }
                }
        case 3: {string tmp = type.substr(0,5);
                if(tmp==convert_to_string("FUNC_")){
                    type_new += 5;
                    return type_new;
                }
                else 
                    return NULL;
                }
        case 6: {if(is_Intgr(type)){
                    return type_new;
                }
                else 
                    return NULL;
                }
        case 7: {if(is_Intgr(type)){
                    return type_new;
                }
                else 
                    return NULL;
                }
        case 8: return type_new;
        case 9: return type_new;

    }
}

char* argument_expr(string first_type, string second_type, int Number){
    char* ret_str = "void";
    char* err_str = "error";

    switch(Number){
        case 1: {if(first_type==convert_to_string("void"))   return ret_str;
                else return err_str;}
        case 2: {if(first_type==convert_to_string("void") && second_type==convert_to_string("void"))   return ret_str;
                else return err_str;}
	}
}

char* shift_expr(string first_type,string second_type){
      char* ret_str = "True";
      if(is_Intgr(first_type) && is_Intgr(second_type))  return ret_str;
      else return NULL;
} 

char* unary_expr(string op, string type, int Number){
    char* ret_str = new char();
    if(Number==1){
	    if (op == convert_to_string("&")){
		    type = type + convert_to_string("*");
	    }
        else if (op == convert_to_string("*")){
            return postfix_expr(type, 1);
        }
	    else  if (op==convert_to_string("+")){
            if(is_float(type) || is_Intgr(type)|| type==convert_to_string("_Complex")|| type==convert_to_string("_Imaginary") ){;}
            else return NULL;
	    }
	    else if (op==convert_to_string("-")){
            if(is_float(type) || is_Intgr(type)|| type==convert_to_string("_Complex")|| type==convert_to_string("_Imaginary") ){;}
            else return NULL;
	    }
	    if(op == convert_to_string("~")){	
            if(is_Intgr(type)|| type =="bool") {;}
            else return NULL;
        }
        else if(op == convert_to_string("!")){	
            if(type =="bool") {;}
            else return NULL;
        }    
	    strcpy(ret_str, type.c_str());
    }
    return ret_str;
}

char* validAssign(string first_type,string second_type){
    char * ret_str = new char();
    if(is_Intgr(second_type) && (first_type[first_type.size()-1]=='*')){
        ret_str = "warning";
        return ret_str;
    }
    if(is_Intgr(first_type) && (second_type[second_type.size()-1]=='*')){
        ret_str = "warning";
        return ret_str;
    }
    if(first_type==convert_to_string("char"))  first_type=convert_to_string("long long");
    if(is_Intgr(first_type))   first_type=convert_to_string("long double");
    if(second_type==convert_to_string("char"))  second_type=convert_to_string("long long");
    if(is_Intgr(second_type))   second_type=convert_to_string("long double");
    
    if(is_float(first_type) && is_float(second_type)){ ret_str = "true";return ret_str; } 
    if(first_type==convert_to_string("void*") && (second_type[second_type.size()-1]=='*')){
        ret_str = "true";return ret_str;
    }
    if(second_type==convert_to_string("void*") && (first_type[first_type.size()-1]=='*')){
        ret_str = "true";return ret_str;
    }
    if(first_type==second_type){
        ret_str = "true";return ret_str;
    }
    if((second_type[second_type.size()-1]=='*') && (first_type[first_type.size()-1]=='*')){
        ret_str = "warning";return ret_str;
    }
    return NULL;
}

char* additive_expr(string first_type,string second_type,char op){
	char *ret_str = new char();
	if(is_Intgr(first_type)|| is_float(first_type)){
		if(is_Intgr(second_type)||is_float(second_type)){
			if(is_Intgr(first_type)&&is_Intgr(second_type)){ ret_str = "int"; }
			else { ret_str = "real"; }
			return ret_str;
		} 
	}
	else if(first_type==convert_to_string("char")&&is_Intgr(second_type)) {
		ret_str = "char";
        return ret_str;
	}
    else if(second_type==convert_to_string("char")&&is_Intgr(first_type)){
        ret_str = "char";
        return ret_str;
    }
    else if((first_type[first_type.size()-1]=='*')&&is_Intgr(second_type)){
        strcpy(ret_str, first_type.c_str());
        return ret_str; 
    }
    else if((second_type[second_type.size()-1]=='*')&&is_Intgr(first_type)){
        strcpy(ret_str, second_type.c_str());return ret_str;
    }        
	return NULL;
}


char* multilplicative_expr(string first_type, string second_type, char op){
    char* ret_str = new char();
    if(is_Intgr(first_type)|| is_float(first_type)){
	if(is_Intgr(second_type)||is_float(second_type)){
		if(op == '%'){
			if(is_Intgr(first_type)&&is_Intgr(second_type)){
			    ret_str = "int";
			    return ret_str;
			}
		}
		if(op == '*'|| op == '/'){
                     if(is_Intgr(first_type) && is_Intgr(second_type)){ ret_str = "int"; }
                     else { ret_str = "float"; }
                     return ret_str;
	        }
        }	
  }
  return NULL;
}

char* relational_expr(string first_type,string second_type,char * op){
     char *ret_str = new char();
     if(is_Intgr(first_type) || is_float(first_type) || (first_type==convert_to_string("char"))){
        if(is_Intgr(second_type)||is_float(second_type)||(second_type==convert_to_string("char"))){
            ret_str = "bool";return ret_str;
        }  
        else if(second_type[second_type.size()-1]=='*'){
            if(is_Intgr(first_type)||(first_type==convert_to_string("char"))){ 
                ret_str = "Bool"; 
                return ret_str; 
            }
            else return NULL;
        }
     }
     if(first_type[first_type.size()-1]=='*'){
        if(is_Intgr(second_type)||(second_type==convert_to_string("char"))){ 
            ret_str = "Bool"; 
            return ret_str; 
        }
        else return NULL;
    }
    return NULL;
}

char* assign_expr(string first_type,string second_type,char* op){
    char *ret_str = new char();
    if(!strcmp(op,"=")){
        ret_str = validAssign(first_type,second_type);
        if(ret_str) return ret_str;
        else return NULL;
    }
    else if((!strcmp(op,"*="))||(!strcmp(op,"/="))||(!strcmp(op,"%="))){
        ret_str = multilplicative_expr(first_type,second_type,op[0]);
        if(ret_str){ ret_str = "true"; return ret_str; }
    }
    else if((!strcmp(op,"+="))||(!strcmp(op,"-="))){
        ret_str = additive_expr(first_type,second_type,op[0]);
        if(ret_str){ ret_str = "true"; return ret_str;}
    }
    else if((!strcmp(op,">>="))||(!strcmp(op,"<<="))){
        ret_str = shift_expr(first_type,second_type);
        if(ret_str){ ret_str = "true"; return ret_str;}
    }
    else if((!strcmp(op,"&="))||(!strcmp(op,"^="))||(!strcmp(op,"|="))){
        ret_str = bitwise_expr(first_type,second_type);
        if(ret_str){ ret_str = "true"; return ret_str;}
    }
    return NULL;
}

char * equality_expr(string first_type,string second_type){
       char *ret_str = new char();
       if(is_Intgr(first_type)||is_float(first_type)||(first_type=="char")){
             if(is_Intgr(second_type)||is_float(second_type)||(second_type=="char")){
                ret_str = "True";
                return ret_str;
             }
       }
       else if(first_type[first_type.size()-1]=='*' && is_Intgr(second_type)){
           ret_str = "true";
           return ret_str;
       }
       else if(second_type[second_type.size()-1]=='*' && is_Intgr(first_type)){
           ret_str = "true";
           return ret_str;
       }
       else if(!strcmp(first_type.c_str(),second_type.c_str())){
            ret_str = "True";
            return ret_str;
       }
   return NULL;
}

char* conditional_expr(string first_type,string second_type){
    char* ret_str = new char();
    if(first_type==convert_to_string("char")){
        first_type = convert_to_string("long long");
    }
    if(is_Intgr(first_type)){
        first_type = convert_to_string("long double");
    }
    if(second_type==convert_to_string("char")){
        second_type = convert_to_string("long long");
    }
    if(is_Intgr(second_type)){
        second_type = convert_to_string("long double");
    }
    if(is_float(first_type) && is_float(second_type)){ 
    ret_str = "long double";
    return ret_str; 
    }
    if( first_type == second_type ){
        strcpy(ret_str, first_type.c_str()); return ret_str;
    }
    if((first_type[first_type.size()-1]=='*') && second_type[second_type.size()-1]=='*'){
        ret_str = "void*"; return ret_str;
    }
    return NULL;
}

char* bitwise_expr(string first_type,string second_type){ // ^,&,|
      char * ret_str = new char();
      if((first_type==convert_to_string("bool"))&&(second_type==convert_to_string("bool"))){
          ret_str = "true";
          return ret_str;
      }
      if(is_Intgr(first_type) || first_type==convert_to_string("bool")){
            if(is_Intgr(second_type) || second_type==convert_to_string("bool")){
                ret_str = "True"; 
                return ret_str;
            }               
      } 
      return NULL;
}

