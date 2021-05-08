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
int next_flag;

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
   next_flag = 0;
   insert_symbol(*curr, "scanf", "FUNC_int", 8, 0, 1);
   insert_symbol(*curr, "print_string", "FUNC_void", 8, 0, 1);
   insert_symbol(*curr, "print_int", "FUNC_void", 8, 0, 1); 
}

int structLookup(string struct_name, string idStruct)
{
   if (struct_table_map.find(struct_name) == struct_table_map.end())
      return 1;
   else if ((*struct_table_map[struct_name]).count(idStruct) != 1)
      return 2;
   return 0;
}

void fprintStruct(Entry *a, FILE *file)
{
   fprintf(file, "%s,%lld, %lld, %d\n", a->type.c_str(), a->size, a->offset, a->init_flag);
}

void paramTable()
{
   old_offset = offset_arr[offset_arr_index];
   create_table("New Func", S_FUNC, "");
   next_flag = 1;
}

Entry *add_entry(string type, ull size, ll offset, int init_flag)
{
   Entry *mynew = new Entry();
   mynew->type = type;
   mynew->size = size;
   mynew->offset = offset;
   mynew->init_flag = init_flag;
   return mynew;
}

string get_sym_type(string key)
{
   Entry *temp = lookup(key);
   if (temp)
   {
      string a = temp->type;
      return a;
   }
   else
      return "";
}

void insert_symbol(symbol_table &table, string key, string type, ull size, ll offset_type, int init_flag)
{
   blk_size[blk_num] = blk_size[blk_num] + size;
   if (offset_type == 10)
   {
      table.insert(pair<string, Entry *>(key, add_entry(type, size,old_offset, init_flag)));
   }
   else if (offset_type == -10)
   {
      table.insert(pair<string, Entry *>(key, add_entry(type, size, struct_offset, init_flag)));
   }
   else
   {
      table.insert(pair<string, Entry *>(key, add_entry(type, size, offset_arr[offset_arr_index], init_flag)));
   }
   offset_arr[offset_arr_index] = offset_arr[offset_arr_index] + size;
   return;
}



void create_table(string name, int type, string func_type)
{
   string f;
   // if(func_type!="12345") f =convert_to_string("FUNC_")+func_type; else f = convert_to_string("Block");
   f = convert_to_string("FUNC_") + func_type;
   if (next_flag == 1)
   {
      insert_symbol(*Parent[curr], name, f, 0, 10, 1);
      old_offset = 0;
      // (*Parent[curr]).erase(convert_to_string("Next"));
   }
   else
   {
      blk_num++;
      symbol_table *myTable = new symbol_table;
      // insert_symbol(*curr, name, f, 0, 0, 1);
      offset_arr_index++;
      offset_arr[offset_arr_index] = 0;
      Parent.insert(pair<symbol_table *, symbol_table *>(myTable, curr));
      curr = myTable;
   }
   next_flag = 0;
}

string func_args_list(string key)
{
   string a = args_map[key];
   return a;
}

void update_table(string key)
{
   curr = Parent[curr];
   offset_arr_index--;
   offset_arr[offset_arr_index] += offset_arr[offset_arr_index + 1];
   update_table_size(key);
   blk_size[blk_num - 1] = blk_size[blk_num] + blk_size[blk_num - 1];
   blk_size[blk_num] = 0;
   blk_num--;
}

Entry *lookup(string a)
{
   symbol_table *tmp;
   tmp = curr;
   while (1)
   {
      if ((*tmp).find(a) != (*tmp).end()) // if present in curr
      {
         return (*tmp)[a];
      }
      if (Parent[tmp] != NULL) // goto parent symtable to check
         tmp = Parent[tmp];
      else
         break;
   }
   return NULL;
}
Entry *scopeLookup(string a)
{
   symbol_table *tmp;
   tmp = curr;
   if ((*tmp).find(a) != (*tmp).end())
   {
      return (*tmp)[a];
   }
   return NULL;
}

ull get_size(char *id)
{
   // integer
   string str = convert_to_string(id);
   if (struct_size.find(id) != struct_size.end())
      return struct_size[str];
   if (str == "int")
      return sizeof(int);
   if (str == "long int")
      return sizeof(long int);
   if (str == "long long")
      return sizeof(long long);
   if (str == "long long int")
      return sizeof(long long int);
   if (str == "signed int")
      return sizeof(signed int);
   if (str == "signed long int")
      return sizeof(signed long int);
   if (str == "signed long long")
      return sizeof(signed long long);
   if (str == "signed long long int")
      return sizeof(signed long long int);
   if (str == "unsigned int")
      return sizeof(unsigned int);
   if (str == "unsigned long int")
      return sizeof(unsigned long int);
   if (str == "unsigned long long")
      return sizeof(unsigned long long);
   if (str == "unsigned long long int")
      return sizeof(unsigned long long int);
   if (str == "short")
      return sizeof(short);
   if (str == "short int")
      return sizeof(short int);
   if (str == "signed short int")
      return sizeof(signed short int);
   if (str == "unsigned short int")
      return sizeof(unsigned short int);

   //float
   if (str == "float")
      return sizeof(float);
   if (str == "double")
      return sizeof(double);
   if (str == "long double")
      return sizeof(long double);

   //char
   if (str == "char")
      return sizeof(char);

   return 8;
}

void update_init_flag(string key)
{
   Entry *temp = lookup(key);
   if (temp)
   {
      temp->init_flag = 1;
   }
}
void update_table_size(string key)
{
   Entry *temp = lookup(key);
   if (temp)
   {
      temp->size = blk_size[blk_num];
   }
}

void insert_args(string a, string b)
{
   args_map.insert(pair<string, string>(a, b));
}

void print_func_args()
{
   FILE *file = fopen("FuncArguments.csv", "w");
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

   for (auto it : *a)
   {
      fprintf(file, "%s,", it.first.c_str());
      fprintStruct(it.second, file);
   }
   fclose(file);
}