#include "symbolTable.h"

string convert_to_string(char *str)
{
   int i;
   string s = "";
   for (i = 0; i < strlen(str); i++)
   {
      s = s + str[i];
   }
   return s;
}

map<string, symbol_table *> struct_table_map; // maps structs with their symbol tables
map<string, string> args_map; // maps function with its arguments
map<symbol_table *, symbol_table *> Parent; // to access parent symbol table
map<string, int> struct_size; // maps structs with their sizes

int blk_num;
long long blk_size[20];

int offset_arr_index; 
long long offset_arr[20];
long long old_offset; // to store the previous value of offset
long long struct_offset;
bool E3_done;

symbol_table global_table; // global symbol table
symbol_table *curr; // current symbol table
symbol_table *struct_table; // struct symbol table

// initialize symbol table - called in main
void table_initialize(){
   offset_arr_index = 0;
   offset_arr[offset_arr_index] = 0;
   old_offset = 0;
   for (blk_num = 0; blk_num < 20; blk_num++){
      blk_size[blk_num] = 0;
   }
   blk_num = 0;
   Parent.insert(make_pair<symbol_table *, symbol_table *>(&global_table, NULL));
   curr = &global_table;
   E3_done = false;
   insert_symbol1(*curr, "scanf", "FUNC_int", 8, 1);
   insert_symbol1(*curr, "print_string", "FUNC_void", 8, 1);
   insert_symbol1(*curr, "print_int", "FUNC_void", 8, 1); 
}

void insert_symbol1(symbol_table &table, string key, string type, unsigned long long size, int init_flag){
   Entry* tmp_entry = new Entry();
   tmp_entry->type = type;
   tmp_entry->size = size;
   tmp_entry->offset = offset_arr[offset_arr_index];
   tmp_entry->init_flag = init_flag;
   table.insert({key, tmp_entry});

   blk_size[blk_num] = blk_size[blk_num] + size;
   offset_arr[offset_arr_index] = offset_arr[offset_arr_index] + size;
   
   return;
}

void insert_symbol2(symbol_table &table, string key, string type, unsigned long long size, int init_flag){
   Entry* tmp_entry = new Entry();
   tmp_entry->type = type;
   tmp_entry->size = size;
   tmp_entry->offset = old_offset;
   tmp_entry->init_flag = init_flag;
   table.insert({key, tmp_entry});

   blk_size[blk_num] = blk_size[blk_num] + size;
   offset_arr[offset_arr_index] = offset_arr[offset_arr_index] + size;
   
   return;
}

void insert_symbol3(symbol_table &table, string key, string type, unsigned long long size, int init_flag){
   Entry* tmp_entry = new Entry();
   tmp_entry->type = type;
   tmp_entry->size = size;
   tmp_entry->offset = struct_offset;
   tmp_entry->init_flag = init_flag;
   table.insert({key, tmp_entry});

   blk_size[blk_num] = blk_size[blk_num] + size;
   offset_arr[offset_arr_index] = offset_arr[offset_arr_index] + size;
   
   return;
}

void create_table(string name, string func_type){
   string type = convert_to_string("FUNC_") + func_type;
   if (E3_done){
      insert_symbol2(*Parent[curr], name, type, 0, 1);
      old_offset = 0;
      E3_done = false;
   }
   else{
      symbol_table *new_table = new symbol_table;
      Parent.insert({new_table, curr});
      curr = new_table;
      blk_num++;
      offset_arr_index++;
      offset_arr[offset_arr_index] = 0;
   }
   return;
}

void update_table(string key,int is_init){
   long long temp = blk_size[blk_num];
   blk_size[blk_num] = 0;
   blk_num--;
   if(lookup(key) != NULL){
      Entry* key_entry = lookup(key);
      key_entry->size = temp;
   }
   blk_size[blk_num] += temp;
   curr = Parent[curr];
   (*curr)[key]->init_flag=is_init;
   offset_arr_index--;
   offset_arr[offset_arr_index] += offset_arr[offset_arr_index + 1];
}

Entry* lookup(string key){
   symbol_table* fixed;
   fixed = curr;
   Entry* ret_val = new Entry();
   while(curr != NULL){
      if ((*curr).find(key) != (*curr).end()){
         ret_val = (*curr)[key];
         break;
      }
      curr = Parent[curr];
   }

   if(curr == NULL){
      curr = fixed;
      return NULL;
   }
   curr = fixed;
   return ret_val;
}

void print_func_args(){
   FILE *file = fopen("FuncArgs.csv", "w");
   for (auto it : args_map)
   {
      fprintf(file, "%s,", it.first.c_str());
      fprintf(file, "%s\n", it.second.c_str());
   }
   fclose(file);
}

void print_tables(symbol_table *a, string filename)
{
   FILE *file = fopen(filename.c_str(), "w");
   fprintf(file, "Key,Type,Size,Offset,is_Initialized\n");

   for (auto it : *a){
      fprintf(file, "%s,", it.first.c_str());
      fprintf(file, "%s,%lld, %lld, %d\n", it.second->type.c_str(), it.second->size, it.second->offset, it.second->init_flag);
   }
   fclose(file);
}