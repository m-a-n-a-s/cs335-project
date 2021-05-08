#include <iostream>
#include <unordered_map>
#include <map>
#include <cstring>
#include <string>

using namespace std;

enum symbol_tab_types{
	S_FILE,S_BLOCK,S_FUNC,S_PROTO
};


// entries of symbol table
typedef struct table_entry{
    unsigned long long size;
    long long offset;
    string type;
    int init_flag;
    int is_array; //1 means index is expression. 2 means it is const no.
} Entry;

typedef unordered_map<string,Entry *> symbol_table;


string convert_to_string(char *str);

extern map<string, symbol_table *> struct_table_map;
extern map<string , string> args_map;
extern map<symbol_table *, symbol_table*> Parent;
extern map<string, int> struct_size;

extern int blk_num;
extern long long blk_size[20];

extern int offset_arr_index;
extern long long offset_arr[20];
extern long long old_offset;
extern long long struct_offset;

extern bool E3_done;


extern symbol_table global_table;
extern symbol_table *curr;
extern symbol_table *struct_table;


unsigned long long get_size (char* id);
void fprintStruct(Entry *a, FILE *file);
void table_initialize();
void paramTable();
void update_init_flag(string k);
void create_table(string name,string func_type);
void insert_args(string a,string b);
void update_table(string k,int is_init);
void insert_symbol(symbol_table& table,string k,string type,unsigned long long size,long long offset,int init_flag);
void print_tables(symbol_table *a, string filename);
void print_func_args();
void update_table_size(string k);
void make_struct_table();
void itemSwitchMap();
Entry* lookup(string a);
Entry* scopeLookup(string a);
Entry* add_entry(string type, unsigned long long size, long long offset,int init_flag);
bool insert_sym_struct(string k, string type, unsigned long long size, unsigned long long offset, int init_flag );
void end_struct(string struct_name);
bool struct_flag(string struct_name);
string get_sym_type(string k);
string func_args_list(string k);
string struct_membr_type(string struct_name, string idT);
int structLookup(string struct_name, string idStruct);

void insert_symbol1(symbol_table &table, string key, string type, unsigned long long size, int init_flag);
void insert_symbol2(symbol_table &table, string key, string type, unsigned long long size, int init_flag);
void insert_symbol3(symbol_table &table, string key, string type, unsigned long long size, int init_flag);