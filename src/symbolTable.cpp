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

map<string, symbol_table *> to_struct_table;
map<string, string> argsMap;
map<symbol_table *, symbol_table *> Parent;
map<symbol_table *, int> symTable_type;
map<string, int> item_switch;
map<string, int> struct_size;
map<int, string> status_map;
int blk_num;
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

void make_struct_table()
{
   symbol_table *myStruct = new symbol_table;
   count_struct++;
   struct_table = myStruct;
   structOffset = 0;
}

void paramTable()
{
   offset_num++;
   offset_nxt[offset_num] = offset_g[offset_gnum];
   create_table("Next", S_FUNC, "");
   next_flag = 1;
}

bool insert_sym_struct(string key, string type, ull size, ull offset, int init_flag)
{
   if ((*struct_table).find(key) != (*struct_table).end())
      return false;
   insert_symbol(*struct_table, key, type, size, -10, init_flag);
   structOffset += size;
   return true;
}

string struct_membr_type(string struct_name, string idT)
{
   struct_table_temp = to_struct_table[struct_name];
   Entry *aT = (*struct_table_temp)[idT];
   return aT->type;
}

bool struct_flag(string struct_name)
{
   if (to_struct_table.find(struct_name) != to_struct_table.end())
      return true;
}

bool end_struct(string struct_name)
{
   if (to_struct_table.find(struct_name) != to_struct_table.end())
      return false;
   to_struct_table.insert(pair<string, symbol_table *>("STRUCT_" + struct_name, struct_table));
   Parent.insert(pair<symbol_table *, symbol_table *>(struct_table, NULL));
   struct_size.insert(pair<string, int>("STRUCT_" + struct_name, structOffset));
   struct_name = "struct_" + struct_name + ".csv";
   print_tables(struct_table, struct_name);
   return true;
}

void table_initialize()
{
   for (blk_num = 0; blk_num < 100; blk_num++)
   {
      blk_size[blk_num] = 0;
   }
   offset_gnum = 0;
   offset_g[offset_gnum] = 0;
   offset_num = 0;
   count_struct = 0;
   blk_num = 0;
   //itemSwitchMap();
   Parent.insert(make_pair<symbol_table *, symbol_table *>(&global_table, NULL));
   symTable_type.insert(make_pair<symbol_table *, int>(&global_table, 1));
   curr = &global_table;
   next_flag = 0;
   //addKeywords();
   //insert_symbol(*curr,"printf","FUNC_void",8,0,1);
   //insert_symbol(*curr,"scanf","FUNC_int",8,0,1);
   //insert_symbol(*curr, "printf", "FUNC_void", 8, 0, 1); //
   insert_symbol(*curr, "scanf", "FUNC_int", 8, 0, 1);
   insert_symbol(*curr, "print_string", "FUNC_void", 8, 0, 1); //
   //insert_symbol(*curr, "strlen", "FUNC_int", 8, 0, 1);  //
   insert_symbol(*curr, "print_int", "FUNC_void", 8, 0, 1); //
   //insert_symbol(*curr, "readFile", "FUNC_int", 8, 0, 1);
   //insert_symbol(*curr, "writeFile", "FUNC_int", 8, 0, 1);

   //argsMap.insert(pair<string,string>("printf","char*,..."));
   //  argsMap.insert(pair<string,string>("prints","char*"));
   //argsMap.insert(pair<string,string>("scanf","char*,..."));
   argsMap.insert(pair<string, string>(string("print_int"), string("int")));
   //argsMap.insert(pair<string, string>(string("printf"), string("int")));
   argsMap.insert(pair<string, string>(string("print_string"), string("char*")));
   argsMap.insert(pair<string, string>(string("scanf"), string("")));
}

int structLookup(string struct_name, string idStruct)
{
   if (to_struct_table.count(struct_name) != 1)
      return 1;
   else if ((*to_struct_table[struct_name]).count(idStruct) != 1)
      return 2;
   return 0;
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

void insert_symbol(symbol_table &table, string key, string type, ull size, ll offset, int init_flag)
{
   blk_size[blk_num] = blk_size[blk_num] + size;
   if (offset == 10)
   {
      table.insert(pair<string, Entry *>(key, add_entry(type, size, offset_nxt[offset_num], init_flag)));
   }
   else if (offset == -10)
   {
      table.insert(pair<string, Entry *>(key, add_entry(type, size, structOffset, init_flag)));
   }
   else
   {
      table.insert(pair<string, Entry *>(key, add_entry(type, size, offset_g[offset_gnum], init_flag)));
   }
   offset_g[offset_gnum] = offset_g[offset_gnum] + size;
   return;
}

void fprintStruct(Entry *a, FILE *file)
{
   fprintf(file, "%s,%lld, %lld, %d\n", a->type.c_str(), a->size, a->offset, a->init_flag);
}

void create_table(string name, int type, string func_type)
{
   string f;
   //if(func_type!="12345") f =convert_to_string("FUNC_")+func_type; else f = convert_to_string("Block");
   f = convert_to_string("FUNC_") + func_type;
   if (next_flag == 1)
   {
      insert_symbol(*Parent[curr], name, f, 0, 10, 1);
      offset_num--;
      (*Parent[curr]).erase(convert_to_string("Next"));
   }
   else
   {
      blk_num++;
      symbol_table *myTable = new symbol_table;
      insert_symbol(*curr, name, f, 0, 0, 1);
      offset_gnum++;
      offset_g[offset_gnum] = 0;
      Parent.insert(pair<symbol_table *, symbol_table *>(myTable, curr));
      symTable_type.insert(pair<symbol_table *, int>(myTable, type));
      curr = myTable;
   }
   next_flag = 0;
}

string func_args_list(string key)
{
   string a = argsMap[key];
   return a;
}

void update_table(string key)
{
   curr = Parent[curr];
   offset_gnum--;
   offset_g[offset_gnum] += offset_g[offset_gnum + 1];
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
      if ((*tmp).find(a) != (*tmp).end())
      {
         return (*tmp)[a];
      }
      if (Parent[tmp] != NULL)
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
   argsMap.insert(pair<string, string>(a, b));
}

void print_func_args()
{
   FILE *file = fopen("FuncArguments.csv", "w");
   for (auto it : argsMap)
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