#include "symbolTable.h"

map<string , symbol_table*> to_struct_table;
map<string , string> argsMap;
map<symbol_table *, symbol_table*> Parent;
map<symbol_table *, int> symTable_type;
map<string ,int> item_switch;
map<string , int> struct_size;
map<int, string> status_map;
int blk_num ;
int offset_gnum;
int offset_num;
long int blk_size[100];
long long offset_g[100];
long long offset_nxt[100];
int count_struct;
int structOffset;
int next_flag;

symbol_table *curr;
symbol_table global_table;
symbol_table *struct_table;
symbol_table *struct_table_temp;

void make_struct_table(){
   symbol_table* myStruct = new symbol_table;
   count_struct++;
   struct_table = myStruct;
   structOffset = 0;  
}

void paramTable(){
      offset_num++;
      offset_nxt[offset_num]=offset_g[offset_gnum];
      create_table(string("Next"),S_FUNC,string(""));
      next_flag=1;
}

bool insert_sym_struct(string k, string type, ull size, ull offset, int init_flag ){
           if((*struct_table).count(k)) return false;
           insert_symbol(*struct_table, k, type, size, -10, init_flag);
           structOffset += size;
           return true;
}


string struct_membr_type(string struct_name, string idT){
   struct_table_temp = to_struct_table[struct_name];
   Entry* aT = (*struct_table_temp)[idT];
   return aT->type;
}

bool struct_flag(string struct_name){
   if(to_struct_table.count(struct_name)) return true;
}

bool end_struct(string struct_name){
   if(to_struct_table.count(struct_name)) return false;
   to_struct_table.insert(pair<string, symbol_table*>(string("STRUCT_")+struct_name, struct_table)); 
   Parent.insert(pair<symbol_table*, symbol_table*>(struct_table, NULL));
   struct_size.insert(pair<string, int>(string("STRUCT_")+struct_name, structOffset));
   struct_name = "struct_" + struct_name + ".csv";
   print_tables(struct_table, struct_name);
   return true;
}


void itemSwitchMap(){
   status_map.insert(make_pair<int, string>(1,"integer_value"));
   status_map.insert(make_pair<int, string>(2,"fVal"));
   status_map.insert(make_pair<int, string>(3,"dVal"));
   status_map.insert(make_pair<int, string>(4,"sVal"));
   status_map.insert(make_pair<int, string>(5,"char_value"));
   status_map.insert(make_pair<int, string>(6,"bVal"));
   item_switch.insert(make_pair<string, int>("string", 1));
   item_switch.insert(make_pair<string, int>("int", 2));
   item_switch.insert(make_pair<string, int>("func", 3));
   item_switch.insert(make_pair<string, int>("Keyword", 1));
   item_switch.insert(make_pair<string, int>("Operator",1));
   item_switch.insert(make_pair<string, int>("IDENTIFIER", 1));
   item_switch.insert(make_pair<string, int>("ENUMERATION_CONSTANT", 1));
   item_switch.insert(make_pair<string, int>("TYPEDEF_NAME", 1));
}

void table_initialize(){
    for(blk_num=0;blk_num<100;blk_num++){
        blk_size[blk_num]=0;
    }
    offset_gnum=0;
    offset_g[offset_gnum]=0;
    offset_num=0;
    count_struct=0;
    blk_num=0;
    itemSwitchMap();
    Parent.insert(make_pair<symbol_table*, symbol_table*>(&global_table, NULL));
    symTable_type.insert(make_pair<symbol_table*, int>(&global_table, 1));
    curr = &global_table;
    next_flag = 0;
    addKeywords();
    argsMap.insert(pair<string,string>(string("printf"),string("char *,...")));
   //  argsMap.insert(pair<string,string>(string("prints"),string("char*")));
    argsMap.insert(pair<string,string>(string("scanf"),string("")));

}

int structLookup(string struct_name, string idStruct){
   if(to_struct_table.count(struct_name)!=1) return 1;
   else if((*to_struct_table[struct_name]).count(idStruct)!=1) return 2;
   return 0;

}

Entry* add_entry(string type,ull size,ll offset,int init_flag){
    Entry* mynew = new Entry();
    mynew->type = type;
    mynew->size = size;
    mynew->offset = offset;
    mynew->init_flag = init_flag;
    return mynew;
}

string get_sym_type(string k){
    Entry* temp = lookup(k);
    if(temp){ string a = temp->type;return a;}
    else return string();
}

void insert_symbol(symbol_table& table,string k,string type,ull size,ll offset, int init_flag){
   blk_size[blk_num] = blk_size[blk_num] + size;
   if(offset==10){ table.insert (pair<string,Entry *>(k,add_entry(type,size,offset_nxt[offset_num],init_flag))); }
   else if(offset==-10){ table.insert (pair<string,Entry *>(k,add_entry(type,size,structOffset,init_flag))); }
   else { table.insert (pair<string,Entry *>(k,add_entry(type,size,offset_g[offset_gnum],init_flag))); }
   offset_g[offset_gnum] = offset_g[offset_gnum] + size;
   return;
}

void fprintStruct(Entry *a, FILE* file){
    fprintf(file, "%s,",a->type.c_str());
    switch(item_switch[a->type]){
        case 1:{
                 fprintf(file, " %lld,%lld,%d\n", a->size, a->offset,a->init_flag);
                 break;
               }
        case 2:{ 
                 fprintf(file, "%lld,%lld ,%d\n", a->size, a->offset,a->init_flag);
                 break;
                }
        case 3:{
                 fprintf(file, "%lld, %lld,%d\n", a->size, a->offset,a->init_flag); break;

               }
       default : {
                 fprintf(file, "%lld, %lld, %d\n", a->size, a->offset,a->init_flag);

               }

    }

}

void create_table(string name,int type,string func_type){
  string f ;
  if(func_type!="12345") f =string("FUNC_")+func_type; else f = string("Block");
  if(next_flag==1){ insert_symbol(*Parent[curr],name,f,0,10,1);
                  offset_num--;
                  (*Parent[curr]).erase(string("Next"));
       }
  else {
   blk_num++;
   symbol_table* myTable = new symbol_table;
    insert_symbol(*curr,name,f,0,0,1);
    offset_gnum++;
    offset_g[offset_gnum]=0;
    Parent.insert(pair<symbol_table*, symbol_table*>(myTable,curr));
    symTable_type.insert(pair<symbol_table*, int>(myTable,type));
    curr = myTable; }
    next_flag=0;
}

string func_args_list(string k){
      string a = argsMap[k];
      return a;
}

void update_table(string k){
    curr = Parent[curr];
    offset_gnum--;
    offset_g[offset_gnum] += offset_g[offset_gnum+1];
    update_table_size(k);
    blk_size[blk_num-1] = blk_size[blk_num]+blk_size[blk_num-1];
    blk_size[blk_num] = 0;
    blk_num--;
}

Entry* lookup(string a){
   symbol_table * tmp;
   tmp = curr;
   while (1){
      if ((*tmp).count(a)){
         return (*tmp)[a];
      }
      if(Parent[tmp]!=NULL) tmp= Parent[tmp];
      else break;
   }
   return NULL;
}
Entry* scopeLookup(string a){
   symbol_table * tmp;
   tmp = curr;
      if ((*tmp).count(a)){
         return (*tmp)[a];
      }
   return NULL;
}

ull get_size (char* id){
  // integer
  if(struct_size.count(id)) return struct_size[string(id)];
  if(!strcmp(id, "int")) return sizeof(int);
  if(!strcmp(id, "long int")) return sizeof(long int);
  if(!strcmp(id, "long long")) return sizeof(long long);
  if(!strcmp(id, "long long int")) return sizeof(long long int);
  if(!strcmp(id, "signed int")) return sizeof(signed int);
  if(!strcmp(id, "signed long int")) return sizeof(signed long int);
  if(!strcmp(id, "signed long long")) return sizeof(signed long long);
  if(!strcmp(id, "signed long long int")) return sizeof(signed long long int);
  if(!strcmp(id, "unsigned int")) return sizeof(unsigned int);
  if(!strcmp(id, "unsigned long int")) return sizeof(unsigned long int);
  if(!strcmp(id, "unsigned long long")) return sizeof(unsigned long long);
  if(!strcmp(id, "unsigned long long int")) return sizeof(unsigned long long int);
  if(!strcmp(id, "short")) return sizeof(short);
  if(!strcmp(id, "short int")) return sizeof(short int);
  if(!strcmp(id, "signed short int")) return sizeof(signed short int);
  if(!strcmp(id, "unsigned short int")) return sizeof(unsigned short int);


  //float
  if(!strcmp(id, "float")) return sizeof(float);
  if(!strcmp(id, "double")) return sizeof(double);
  if(!strcmp(id, "long double")) return sizeof(long double);

  //char
  if(!strcmp(id, "char")) return sizeof(char);

  return 8;

}

void update_init_flag(string k){
   Entry *temp = lookup(k);
   if(temp){
       temp->init_flag =1;
   }
}
void update_table_size(string k){
   Entry *temp = lookup(k);
   if(temp){
       temp->size = blk_size[blk_num];
   }
}

void insert_args(string a,string b){
     argsMap.insert(pair<string,string>(a,b));
}

void print_func_args(){
     FILE* file = fopen("FuncArguments.csv","w");
     for(auto it:argsMap){
        fprintf(file,"%s,",it.first.c_str());
        fprintf(file,"%s\n",it.second.c_str());
     }
     fclose(file);
}
void print_tables(symbol_table* a, string filename) {
  FILE* file = fopen(filename.c_str(), "w");
  fprintf( file,"Key,Type,Size,Offset,is_Initialized\n");


  for(auto it: *a ){
    fprintf( file,"%s,", it.first.c_str());
    fprintStruct(it.second, file);
  }
  fclose(file);
}
void addKeywords(){

//-------------------inserting keywords-------------------------------------------
//   { string *keyword = new string(); *keyword = "AUTO"; insert_symbol(*curr,"auto","Keyword",8,0,1); } // auto keyword
//   { string *keyword = new string(); *keyword = "BREAK"; insert_symbol(*curr,"break","Keyword",8,0,1); } // break keyword
//   { string *keyword = new string(); *keyword = "CASE"; insert_symbol(*curr,"case","Keyword",8,0,1); } // case keyword
//   { string *keyword = new string(); *keyword = "CHAR"; insert_symbol(*curr,"char","Keyword",8,0,1); } // char keyword
//   { string *keyword = new string(); *keyword = "CONST"; insert_symbol(*curr,"const","Keyword",8,0,1); } // const keyword
//   { string *keyword = new string(); *keyword = "CONTINUE"; insert_symbol(*curr,"continue","Keyword",8,0,1); } // CONTINUE keyword
//   { string *keyword = new string(); *keyword = "DEFAULT"; insert_symbol(*curr,"default","Keyword",8,0,1); } // default keyword
//   { string *keyword = new string(); *keyword = "DO"; insert_symbol(*curr,"do","Keyword",8,0,1); } // do keyword
//   { string *keyword = new string(); *keyword = "DOUBLE"; insert_symbol(*curr,"double","Keyword",8,0,1); } // double keyword
//   { string *keyword = new string(); *keyword = "ELSE"; insert_symbol(*curr,"else","Keyword",8,0,1); } // else keyword
//   { string *keyword = new string(); *keyword = "ENUM"; insert_symbol(*curr,"enum","Keyword",8,0,1); } // enum keyword
//   { string *keyword = new string(); *keyword = "EXTERN"; insert_symbol(*curr,"extern","Keyword",8,0,1); } // extern keyword
//   { string *keyword = new string(); *keyword = "FLOAT"; insert_symbol(*curr,"float","Keyword",8,0,1); } // float keyword
//   { string *keyword = new string(); *keyword = "FOR"; insert_symbol(*curr,"for","Keyword",8,0,1); } // for keyword
//   { string *keyword = new string(); *keyword = "GOTO"; insert_symbol(*curr,"goto","Keyword",8,0,1); } // goto keyword
//   { string *keyword = new string(); *keyword = "IF"; insert_symbol(*curr,"if","Keyword",8,0,1); } // if keyword
//   { string *keyword = new string(); *keyword = "INLINE"; insert_symbol(*curr,"inline","Keyword",8,0,1); } // inline keyword
//   { string *keyword = new string(); *keyword = "INT"; insert_symbol(*curr,"int","Keyword",8,0,1); } // int keyword
//   { string *keyword = new string(); *keyword = "LONG"; insert_symbol(*curr,"long","Keyword",8,0,1); } // long keyword
//   { string *keyword = new string(); *keyword = "REGISTER"; insert_symbol(*curr,"register","Keyword",8,0,1); } // register keyword
//   {string *keyword = new string();  *keyword = "RESTRICT"; insert_symbol(*curr,"restrict","Keyword",8,0,1); } // restrict keyword
//   {string *keyword = new string();  *keyword = "RETURN"; insert_symbol(*curr,"return","Keyword",8,0,1); } // return keyword
//   {string *keyword = new string();  *keyword = "SHORT"; insert_symbol(*curr,"short","Keyword",8,0,1); } // short keyword
//   {string *keyword = new string();  *keyword = "SIGNED"; insert_symbol(*curr,"signed","Keyword",8,0,1); } // signed keyword
//   {string *keyword = new string();  *keyword = "SIZEOF"; insert_symbol(*curr,"sizeof","Keyword",8,0,1); } // sizeof keyword
//   {string *keyword = new string();  *keyword = "STATIC"; insert_symbol(*curr,"static","Keyword",8,0,1); } // static keyword
//   {string *keyword = new string();  *keyword = "STRUCT"; insert_symbol(*curr,"struct","Keyword",8,0,1); } // struct keyword
//   {string *keyword = new string();  *keyword = "SWITCH"; insert_symbol(*curr,"switch","Keyword",8,0,1); } // switch keyword
//   {string *keyword = new string();  *keyword = "TYPEDEF"; insert_symbol(*curr,"typedef","Keyword",8,0,1); } // typedef keyword
//   {string *keyword = new string();  *keyword = "UNION"; insert_symbol(*curr,"union","Keyword",8,0,1); } // union keyword
//   {string *keyword = new string();  *keyword = "UNSIGNED"; insert_symbol(*curr,"unsigned","Keyword",8,0,1); } // unsigned keyword
//   {string *keyword = new string();  *keyword = "VOID"; insert_symbol(*curr,"void","Keyword",8,0,1); } // void keyword
//   {string *keyword = new string();  *keyword = "VOLATILE"; insert_symbol(*curr,"volatile","Keyword",8,0,1); } // volatile keyword
//   {string *keyword = new string();  *keyword = "WHILE"; insert_symbol(*curr,"while","Keyword",8,0,1); } // while keyword
//   {string *keyword = new string();  *keyword = "ALIGNAS"; insert_symbol(*curr,"_Alignas","Keyword",8,0,1); } // _Alignas keyword
//   {string *keyword = new string();  *keyword = "ALIGNOF"; insert_symbol(*curr,"_Alignof","Keyword",8,0,1); } // _Alignof keyword
//   {string *keyword = new string();  *keyword = "ATOMIC"; insert_symbol(*curr,"_Atomic","Keyword",8,0,1); } // _Atomic keyword
//   {string *keyword = new string();  *keyword = "BOOL"; insert_symbol(*curr,"_Bool","Keyword",8,0,1); } // _Bool keyword
//   {string *keyword = new string();  *keyword = "COMPLEX"; insert_symbol(*curr,"_Complex","Keyword",8,0,1); } // _Complex keyword
//   {string *keyword = new string();  *keyword = "GENERIC"; insert_symbol(*curr,"_Generic","Keyword",8,0,1); } // _Generic keyword
//   {string *keyword = new string();  *keyword = "IMAGINARY"; insert_symbol(*curr,"_Imaginary","Keyword",8,0,1); } // _Imaginary keyword
//   {string *keyword = new string();  *keyword = "NORETURN"; insert_symbol(*curr,"_Noreturn","Keyword",8,0,1); } // _Noreturn keyword
//   {string *keyword = new string();  *keyword = "STATIC_ASSERT"; insert_symbol(*curr,"_Static_assert","Keyword",8,0,1); } // _Static_assert keyword
//   {string *keyword = new string();  *keyword = "THREAD_LOCAL"; insert_symbol(*curr,"_Thread_local","Keyword",8,0,1); } // _Thread_local keyword
//   {string *keyword = new string();  *keyword = "FUNC_NAME"; insert_symbol(*curr,"__func__","Keyword",8,0,1); } // __func__ keyword

// //-----------------------------inserting operators---------------------------------------------------

//   {string *oper = new string();  *oper = "ELLIPSIS"; insert_symbol(*curr,"...","Operator",8,0,1); } // ... operator
//   {string *oper = new string();  *oper = "RIGHT_ASSIGN"; insert_symbol(*curr,">>==","Operator",8,0,1); } // >>== operator
//   {string *oper = new string();  *oper = "LEFT_ASSIGN"; insert_symbol(*curr,"<<==","Operator",8,0,1); } // <<== operator
//   {string *oper = new string();  *oper = "ADD_ASSIGN"; insert_symbol(*curr,"+=","Operator",8,0,1); } // += operator
//   {string *oper = new string();  *oper = "SUB_ASSIGN"; insert_symbol(*curr,"-=","Operator",8,0,1); } // -= operator
//   {string *oper = new string();  *oper = "MUL_ASSIGN"; insert_symbol(*curr,"*=","Operator",8,0,1); } // *= operator
//   {string *oper = new string();  *oper = "DIV_ASSIGN"; insert_symbol(*curr,"/=","Operator",8,0,1); } // /= operator
//   {string *oper = new string();  *oper = "MOD_ASSIGN"; insert_symbol(*curr,"%=","Operator",8,0,1); } // %= operator
//   {string *oper = new string();  *oper = "AND_ASSIGN"; insert_symbol(*curr,"&=","Operator",8,0,1); } // &= operator
//   {string *oper = new string();  *oper = "XOR_ASSIGN"; insert_symbol(*curr,"^=","Operator",8,0,1); } // ^= operator
//   {string *oper = new string();  *oper = "OR_ASSIGN"; insert_symbol(*curr,"|=","Operator",8,0,1); } // |= operator
//   {string *oper = new string();  *oper = "RIGHT_OP"; insert_symbol(*curr,">>","Operator",8,0,1); } // >> operator
//   {string *oper = new string();  *oper = "LEFT_OP"; insert_symbol(*curr,"<<","Operator",8,0,1); } // << operator
//   {string *oper = new string();  *oper = "INC_OP"; insert_symbol(*curr,"++","Operator",8,0,1); } // ++ operator
//   {string *oper = new string();  *oper = "DEC_OP"; insert_symbol(*curr,"--","Operator",8,0,1); } // -- operator
//   {string *oper = new string();  *oper = "PTR_OP"; insert_symbol(*curr,"->","Operator",8,0,1); } // -> operator
//   {string *oper = new string();  *oper = "AND_OP"; insert_symbol(*curr,"&&","Operator",8,0,1); } // && operator
//   {string *oper = new string();  *oper = "OR_OP"; insert_symbol(*curr,"||","Operator",8,0,1); } // || operator
//   {string *oper = new string();  *oper = "LE_OP"; insert_symbol(*curr,"<=","Operator",8,0,1); } // <= operator
//   {string *oper = new string();  *oper = "GE_OP"; insert_symbol(*curr,">=","Operator",8,0,1); } // >= operator
//   {string *oper = new string();  *oper = "EQ_OP"; insert_symbol(*curr,"==","Operator",8,0,1); } // == operator
//   {string *oper = new string();  *oper = "NE_OP"; insert_symbol(*curr,"!=","Operator",8,0,1); } // != operator
//   {string *oper = new string();  *oper = ";"; insert_symbol(*curr,";","Operator",8,0,1); } // ; operator
//   {string *oper = new string();  *oper = "{"; insert_symbol(*curr,"{","Operator",8,0,1); } // { operator
//   {string *oper = new string();  *oper = "{"; insert_symbol(*curr,"<%","Operator",8,0,1); } // <% operator
//   {string *oper = new string();  *oper = "}"; insert_symbol(*curr,"}","Operator",8,0,1); } // } operator
//   {string *oper = new string();  *oper = "}"; insert_symbol(*curr,"%>","Operator",8,0,1); } // %> operator
//   {string *oper = new string();  *oper = ","; insert_symbol(*curr,",","Operator",8,0,1); } // , operator
//   {string *oper = new string();  *oper = ":"; insert_symbol(*curr,":","Operator",8,0,1); } // : operator
//   {string *oper = new string();  *oper = "="; insert_symbol(*curr,"=","Operator",8,0,1); } // = operator
//   {string *oper = new string();  *oper = "("; insert_symbol(*curr,"(","Operator",8,0,1); } // ( operator
//   {string *oper = new string();  *oper = ")"; insert_symbol(*curr,")","Operator",8,0,1); } // ) operator
//   {string *oper = new string();  *oper = "["; insert_symbol(*curr,"[","Operator",8,0,1); } // [ operator
//   {string *oper = new string();  *oper = "["; insert_symbol(*curr,"<:","Operator",8,0,1); } // <: operator
//   {string *oper = new string();  *oper = "]"; insert_symbol(*curr,":>","Operator",8,0,1); } // :> operator
//   {string *oper = new string();  *oper = "]"; insert_symbol(*curr,"]","Operator",8,0,1); } // ] operator
//   {string *oper = new string();  *oper = "."; insert_symbol(*curr,".","Operator",8,0,1); } // . operator
//   {string *oper = new string();  *oper = "&"; insert_symbol(*curr,"&","Operator",8,0,1); } // & operator
//   {string *oper = new string();  *oper = "!"; insert_symbol(*curr,"!","Operator",8,0,1); } // ! operator
//   {string *oper = new string();  *oper = "~"; insert_symbol(*curr,"~","Operator",8,0,1); } // ~ operator
//   {string *oper = new string();  *oper = "-"; insert_symbol(*curr,"-","Operator",8,0,1); } // - operator
//   {string *oper = new string();  *oper = "+"; insert_symbol(*curr,"+","Operator",8,0,1); } // + operator
//   {string *oper = new string();  *oper = "*"; insert_symbol(*curr,"*","Operator",8,0,1); } // * operator
//   {string *oper = new string();  *oper = "/"; insert_symbol(*curr,"/","Operator",8,0,1); } // / operator
//   {string *oper = new string();  *oper = "%"; insert_symbol(*curr,"%","Operator",8,0,1); } // % operator
//   {string *oper = new string();  *oper = "<"; insert_symbol(*curr,"<","Operator",8,0,1); } // < operator
//   {string *oper = new string();  *oper = ">"; insert_symbol(*curr,">","Operator",8,0,1); } // > operator
//   {string *oper = new string();  *oper = "^"; insert_symbol(*curr,"^","Operator",8,0,1); } // ^ operator
//   {string *oper = new string();  *oper = "|"; insert_symbol(*curr,"|","Operator",8,0,1); } // | operator
//   {string *oper = new string();  *oper = "?"; insert_symbol(*curr,"?","Operator",8,0,1); } // ? operator

//////////////// printf, scanf defined to run the code /////////
  insert_symbol(*curr,"printf","FUNC_void",8,0,1);
  insert_symbol(*curr,"scanf","FUNC_int",8,0,1);

}