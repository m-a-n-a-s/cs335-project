#include "semanticCheck.h"

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

bool is_bool(string type){
    bool ret_val;
    if(type == "bool"){
        ret_val = true;
    }
    else{
        ret_val = false;
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

unsigned long long get_size(string type){
    if (struct_size_map.find(type) != struct_size_map.end())    return struct_size_map[type];
    else if (type == "int") return sizeof(int);
    else if (type == "long int")    return sizeof(long int);
    else if (type == "long long int")   return sizeof(long long int);
    else if (type == "signed int")  return sizeof(signed int);
    else if (type == "signed long int") return sizeof(signed long int);
    else if (type == "signed long long")    return sizeof(signed long long);
    else if (type == "signed long long int")    return sizeof(signed long long int);
    else if (type == "unsigned int")    return sizeof(unsigned int);
    else if (type == "unsigned long int")   return sizeof(unsigned long int);
    else if (type == "unsigned long long")  return sizeof(unsigned long long);
    else if (type == "unsigned long long int")  return sizeof(unsigned long long int);
    else if (type == "short")   return sizeof(short);
    else if (type == "short int")   return sizeof(short int);
    else if (type == "signed short int")    return sizeof(signed short int);
    else if (type == "unsigned short int")  return sizeof(unsigned short int);
    else if (type == "float")   return sizeof(float);
    else if (type == "double")  return sizeof(double);
    else if (type == "long double") return sizeof(long double);
    // else if (type == "char")    return sizeof(char);
    else if (type == "char")    return 4;
    else return 8;
}

char* postfix_type1(string type){
    if(!is_ptr(type)){
        return NULL;
    }
    else{
        char* ret_val= new char();
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

    // -1 => Incompatible Error
    // 0 => Incompatible Warning
    // 1 => Compatible

    if(first_type == second_type)   return 1;
    else if(void_ptr(first_type) && is_ptr(second_type))    return 1;
    else if(void_ptr(second_type) && is_ptr(first_type))    return 1;
    else if(is_char(first_type) && int_flag(second_type))   return 1;
    else if(is_char(second_type) && int_flag(first_type))   return 1;
    else if(is_char(first_type) && real_flag(second_type))  return 1;
    else if(is_char(second_type) && real_flag(first_type))  return 1;
    else if(is_char(first_type) && is_char(second_type))    return 1;
    else if(int_flag(first_type) && int_flag(second_type))  return 1;
    else if(real_flag(first_type) && real_flag(second_type))    return 1;
    else if(int_flag(first_type) && real_flag(second_type)) return 1;
    else if(real_flag(first_type) && int_flag(second_type)) return 1;

    else if(is_ptr(first_type) && is_ptr(second_type))  return 0;
    else if(is_ptr(first_type) && int_flag(second_type))    return 0;
    else if(is_ptr(second_type) && int_flag(first_type))    return 0;
    
    else return -1;
}

int argument_type(string first_type, string second_type){
    // -1 => Error
    // 1 => OK
    
    bool void1 = false;
    bool void2 = false;

    if(first_type == "void") void1 = true;
    if(second_type == "void") void2 = true;
    
    if(!(void1 && void2)){
        return -1;
    }
    else{
        return 1;
    }
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
    else if(is_char(first_type) && is_char(second_type)) return 2;
    else    return -1;
}

// For a*b 
int multiplicative_type1(string first_type, string second_type){
    // -1 => Error
    // 0 => int
    // 1 => real

    if(int_flag(first_type) && int_flag(second_type))   return 0;
    else if(int_flag(first_type) && real_flag(second_type)) return 1;
    else if(real_flag(first_type) && int_flag(second_type)) return 1;
    else if(real_flag(first_type) && real_flag(second_type))    return 1;
    else return -1;
}

// For a/b
int multiplicative_type2(string first_type, string second_type){
    // -1 => Error
    // 0 => int
    // 1 => real

    if(int_flag(first_type) && int_flag(second_type))   return 0;
    else if(int_flag(first_type) && real_flag(second_type)) return 1;
    else if(real_flag(first_type) && int_flag(second_type)) return 1;
    else if(real_flag(first_type) && real_flag(second_type))    return 1;
    else return -1;
}

// For a%b
int multiplicative_type3(string first_type, string second_type){
    // -1 => Error
    // 0 => int

    if(int_flag(first_type) && int_flag(second_type))   return 0;
    else return -1;
}

int relational_type(string first_type,string second_type){
    
    // -1 => Error
    // 0 => Warning (ptr and int/char)
    // 1 => OK (int/real/char and int/real/char)
    if(first_type == second_type)   return 1;
    if(is_char(first_type) && int_flag(second_type))   return 1;
    else if(is_char(second_type) && int_flag(first_type))   return 1;
    else if(is_char(first_type) && real_flag(second_type))  return 1;
    else if(is_char(second_type) && real_flag(first_type))  return 1;
    else if(is_char(first_type) && is_char(second_type))    return 1;
    else if(int_flag(first_type) && int_flag(second_type))  return 1;
    else if(real_flag(first_type) && real_flag(second_type))    return 1;
    else if(int_flag(first_type) && real_flag(second_type)) return 1;
    else if(real_flag(first_type) && int_flag(second_type)) return 1;
    
    else if(is_ptr(first_type) && is_char(second_type))  return 0;
    else if(is_char(first_type) && is_ptr(second_type))  return 0;
    else if(is_ptr(first_type) && int_flag(second_type)) return 0;
    else if(int_flag(first_type) && is_ptr(second_type)) return 0;
    else if(is_ptr(first_type)&&is_ptr(second_type)) return 0;
    else return -1;
}

int bitwise_type(string first_type,string second_type){ // ^,&,|
    // -1 => Error
    // 0 => OK (bool and int type)
    // 1 => OK (bool and bool)

    if(is_bool(first_type) && int_flag(second_type))  return 0;
    else if(int_flag(first_type) && is_bool(second_type)) return 0;
    else if(int_flag(first_type) && int_flag(second_type))  return 0;

    else if(is_bool(first_type) && is_bool(second_type))  return 1;

    else return -1;
}

// Fot =
int assignment_type1(string first_type, string second_type){
    // -1 => Error
    // 0 => Warning
    // 1 => OK

    int valid = compatible(first_type,second_type);
    if(valid == 1) return 1;
    else if(valid == 0) return 0;
    else return -1;
}

// For +=/-=
int assignment_type2(string first_type, string second_type){
    // -1 => Error
    // 1 => OK

    int add_type = additive_type(first_type,second_type);
    if(add_type != 1)   return 1;
    else return -1;
}

// For *=
int assignment_type3(string first_type, string second_type){
    // -1 => Error
    // 1 => OK

    int mult_type = multiplicative_type1(first_type,second_type);
    if(mult_type != -1) return 1;
    else return -1;
}

// For /=
int assignment_type4(string first_type, string second_type){
    // -1 => Error
    // 1 => OK

    int mult_type = multiplicative_type2(first_type,second_type);
    if(mult_type != -1) return 1;
    else return -1;
}

// For %=
int assignment_type5(string first_type, string second_type){
    // -1 => Error
    // 1 => OK

    int mult_type = multiplicative_type3(first_type,second_type);
    if(mult_type != -1) return 1;
    else return -1;
}

// For >>=/<<=
int assignment_type6(string first_type, string second_type){
    // -1 => Error
    // 1 => OK

    if(int_flag(first_type) && int_flag(second_type))   return 1;
    else return -1;
}

// For &=/^=/|=
int assignment_type7(string first_type, string second_type){
    // -1 => Error
    // 1 => OK

    int bit_type = bitwise_type(first_type,second_type);
    if(bit_type != -1) return 1;
    else return -1;
}

