#include "semanticCheck.h"

// string char* str){
//    int i;
//    string s = "";
//    for (i = 0; i < strlen(str); i++) {
//       s = s + str[i];
//    }
//    return s;
// }


string getstr_num_type(int num_type){
    string ret_val;
    switch(num_type){
        case 1: {
            ret_val.append("int");
            break;
        }
        case 2: {
            ret_val.append("long");
            break;
        }
        case 3: {
            ret_val.append("long long");
            break;
        }
        case 4: {
            ret_val.append("float");
            break;
        }
        case 5: {
            ret_val.append("double");
            break;
        }
        case 6:{
            ret_val.append("long double");
            break;
        }
        default: {
            ret_val.append("default");
            break;
        }
    }
    return ret_val;
}

bool int_flag(string type){
    bool ret_val;

    if(type=="int" || type=="short" || type=="short int" || type=="signed short" || type=="unsigned short" || type=="unsigned short int" || type=="signed short int" || 
        type=="long" || type=="long long" || type=="long int" || type=="long long int" || type=="unsigned int" || type=="unsigned long" || type=="unsigned long long" ||
        type=="unsigned long int" || type=="unsigned long long int" || type=="signed int" || type=="signed long" || type=="signed long long" || type=="signed long int" ||
        type=="signed long long int"){

       ret_val = true;         
    }

    else{
       ret_val = false;
    }

    return ret_val;
}

bool real_flag (string type){
   bool ret_val;
   
   if(type=="float"|| type=="double" || type=="long double" || type=="unsigned float" || type=="unsigned double"||
   type=="unsigned long double" || type=="signed float" || type=="signed double" || type=="signed long double"){

       ret_val = true;
   }
   
   else{
       ret_val = false;
   }

   return ret_val;
}

bool is_ptr(string type){
    bool ret_val;
    if(type[type.size()-1] == '*'){
        ret_val = true;
    }
    else{
        ret_val = false;
    }
    return ret_val;
}

bool void_ptr(string type){
    bool ret_val;
    if(type == "void*"){
        ret_val = true;
    }
    else{
        ret_val = false;
    }
    return ret_val;
}

bool is_char(string type){
    bool ret_val;
    if(type == "char"){
        ret_val = true;
    }
    else{
        ret_val = false;
    }
    return ret_val;
}

// char* primary_type(char* identifier1){
//     string identifier(identifier1);
//     Entry* n = lookup(identifier);
//     if(!n){
//         return NULL;
//     }
//     else{
//         char* s = new char();
//         strcpy(s, (n->type).c_str());
//         return s;
//     }	
// }

char* postfix_type1(string type){
    if(type[type.size()-1] != '*'){
        return NULL;
    }
    else{
        char* ret_val = new char();
        strcpy(ret_val, type.c_str());
        ret_val[type.size()-1]='\0';	
        return ret_val;
    }
}

char* postfix_type2(string type){
    string tmp = type.substr(0,5);
    if(tmp != "FUNC_"){
        return NULL;
    }
    else{
        char* ret_val = new char();
        strcpy(ret_val, type.c_str());
        ret_val += 5;
        return ret_val;
    }
}

char* postfix_type3(string type){
    if(int_flag(type) == false){
        return NULL;
    }
    else{
        char* ret_val = new char();
        strcpy(ret_val, type.c_str());
        return ret_val;
    }
}

// char* postfix_type(string type, int rule_no){
//     char* ret_val = new char();
//     strcpy(ret_val, type.c_str());

//     switch(rule_no){
//         case 1: {if(type[type.size()-1]=='*'){
//                     ret_val[type.size()-1]='\0';	
//                     return ret_val;
//                 }
//                 else{
//                     return NULL;
//                 }
//                 }
//         case 2: {string tmp = type.substr(0,5);
//                 if(tmp=="FUNC_"){
//                     ret_val += 5;
//                     return ret_val;
//                 }
//                 else 
//                     return NULL;
//                 }
//         case 3: {string tmp = type.substr(0,5);
//                 if(tmp=="FUNC_"){
//                     ret_val += 5;
//                     return ret_val;
//                 }
//                 else 
//                     return NULL;
//                 }
//         case 6: {if(int_flag(type)){
//                     return ret_val;
//                 }
//                 else 
//                     return NULL;
//                 }
//         case 7: {if(int_flag(type)){
//                     return ret_val;
//                 }
//                 else 
//                     return NULL;
//                 }
//         case 8: return ret_val;
//         case 9: return ret_val;

//     }
// }

char* argument_type(string first_type, string second_type){
    bool void1 = false;
    bool void2 = false;

    if(first_type == "void") void1 = true;
    if(second_type == "void") void2 = true;
    
    if(!(void1 && void2)){
        return "error";
    }
    else{
        return "void";
    }
    // char* ret_str = "void";
    // char* err_str = "error";

    // switch(rule_no){
    //     case 1: {if(first_type=="void")   return ret_str;
    //             else return err_str;}
    //     case 2: {if(first_type=="void" && second_type=="void")   return ret_str;
    //             else return err_str;}
	// }
}

// char* shift_type(string first_type,string second_type){
//       char* ret_str = "True";
//       if(int_flag(first_type) && int_flag(second_type))  return ret_str;
//       else return NULL;
// } 

char* unary_type(string op, string type){
    if (op == "*") return postfix_type1(type);
    else  if ((op=="-"||op=="+") && (real_flag(type) == false) && (int_flag(type) == false))   return NULL;
    else if(op == "~" && (int_flag(type) == false) && (type != "bool"))  return NULL;
    else if(op == "!" && type != "bool")    return NULL; 
    else if (op == "&")  type = type + "*";
    char* ret_val = new char();
    strcpy(ret_val, type.c_str());
    return ret_val;
}

int compatible(string first_type,string second_type){

    // 1 => Compatible
    // 0 => Incompatible Warning
    // -1 => Incompatible Error

    if(first_type == second_type)   return 1;
    else if(void_ptr(first_type) && is_ptr(second_type))    return 1;
    else if(void_ptr(second_type) && is_ptr(first_type))    return 1;
    else if(first_type == "char" && second_type == "long long") return 1;
    else if(second_type == "char" && first_type == "long long") return 1;
    else if(int_flag(first_type) && second_type == "long double")   return 1;
    else if(int_flag(second_type) && first_type == "long double")   return 1;
    else if(int_flag(first_type) && int_flag(second_type))  return 1;
    else if(real_flag(first_type) && real_flag(second_type))    return 1;
    else if(int_flag(first_type) && real_flag(second_type)) return 1;
    else if(real_flag(first_type) && int_flag(second_type)) return 1;

    else if(is_ptr(first_type) && is_ptr(second_type))  return 0;
    else if(is_ptr(first_type) && int_flag(second_type))    return 0;
    else if(is_ptr(second_type) && int_flag(first_type))    return 0;
    
    else return -1;
}

int additive_type(string first_type,string second_type){
	
    //-1 => Error
    // 0 => int
    // 1 => real
    // 2 => char
    // 3 => ptr1
    // 4 => ptr2
    
    if(is_ptr(first_type) && int_flag(second_type)) return 3;
    else if(int_flag(first_type) && is_ptr(second_type)) return 4;
    else if(int_flag(first_type) && int_flag(second_type))   return 0;
    else if(int_flag(first_type) && real_flag(second_type)) return 1;
    else if(real_flag(first_type) && int_flag(second_type)) return 1;
    else if(real_flag(first_type) && real_flag(second_type))    return 1;
    else if(is_char(first_type) && int_flag(second_type))   return 2;
    else if(int_flag(first_type) && is_char(second_type))   return 2;
    else    return -1;
}


char* multilplicative_type(string first_type, string second_type, char op){
    char* ret_str = new char();
    if(int_flag(first_type)|| real_flag(first_type)){
	if(int_flag(second_type)||real_flag(second_type)){
		if(op == '%'){
			if(int_flag(first_type)&&int_flag(second_type)){
			    ret_str = "int";
			    return ret_str;
			}
		}
		if(op == '*'|| op == '/'){
                     if(int_flag(first_type) && int_flag(second_type)){ ret_str = "int"; }
                     else { ret_str = "float"; }
                     return ret_str;
	        }
        }	
  }
  return NULL;
}

char* relational_type(string first_type,string second_type,char * op){
     char *ret_str = new char();
     if(int_flag(first_type) || real_flag(first_type) || (first_type=="char")){
        if(int_flag(second_type)||real_flag(second_type)||(second_type=="char")){
            ret_str = "bool";return ret_str;
        }  
        else if(second_type[second_type.size()-1]=='*'){
            if(int_flag(first_type)||(first_type=="char")){ 
                ret_str = "bool_warning"; 
                return ret_str; 
            }
            else return NULL;
        }
     }
     if(first_type[first_type.size()-1]=='*'){
        if(int_flag(second_type)||(second_type=="char")){ 
            ret_str = "bool_warning"; 
            return ret_str; 
        }
        else return NULL;
    }
    return NULL;
}

char* assign_type(string first_type,string second_type,char* op){
    char *ret_str = new char();
    if(!strcmp(op,"=")){
        int valid = compatible(first_type,second_type);
        if(valid == 1) return "true";
        else if(valid == 0) return "warning";
        else return NULL;
    }
    else if((!strcmp(op,"*="))||(!strcmp(op,"/="))||(!strcmp(op,"%="))){
        ret_str = multilplicative_type(first_type,second_type,op[0]);
        if(ret_str){ ret_str = "true"; return ret_str; }
    }
    else if((!strcmp(op,"+="))||(!strcmp(op,"-="))){
        int add_type = additive_type(first_type,second_type);
        if(add_type != -1){ ret_str = "true"; return ret_str;}
    }
    else if((!strcmp(op,">>="))||(!strcmp(op,"<<="))){
        if(int_flag(first_type) && int_flag(second_type)){ ret_str = "true"; return ret_str;}
    }
    else if((!strcmp(op,"&="))||(!strcmp(op,"^="))||(!strcmp(op,"|="))){
        ret_str = bitwise_type(first_type,second_type);
        if(ret_str){ ret_str = "true"; return ret_str;}
    }
    return NULL;
}

char * equality_type(string first_type,string second_type){
       char *ret_str = new char();
       if(int_flag(first_type)||real_flag(first_type)||(first_type=="char")){
             if(int_flag(second_type)||real_flag(second_type)||(second_type=="char")){
                ret_str = "True";
                return ret_str;
             }
       }
       else if(first_type[first_type.size()-1]=='*' && int_flag(second_type)){
           ret_str = "true";
           return ret_str;
       }
       else if(second_type[second_type.size()-1]=='*' && int_flag(first_type)){
           ret_str = "true";
           return ret_str;
       }
       else if(!strcmp(first_type.c_str(),second_type.c_str())){
            ret_str = "True";
            return ret_str;
       }
   return NULL;
}

char* conditional_type(string first_type,string second_type){
    char* ret_str = new char();
    if(first_type=="char"){
        first_type = "long long";
    }
    if(int_flag(first_type)){
        first_type = "long double";
    }
    if(second_type=="char"){
        second_type = "long long";
    }
    if(int_flag(second_type)){
        second_type = "long double";
    }
    if(real_flag(first_type) && real_flag(second_type)){ 
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

char* bitwise_type(string first_type,string second_type){ // ^,&,|
      char * ret_str = new char();
      if((first_type=="bool")&&(second_type=="bool")){
          ret_str = "true";
          return ret_str;
      }
      if(int_flag(first_type) || first_type=="bool"){
            if(int_flag(second_type) || second_type=="bool"){
                ret_str = "True"; 
                return ret_str;
            }               
      } 
      return NULL;
}

