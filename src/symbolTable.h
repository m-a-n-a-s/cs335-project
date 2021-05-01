#include <iostream>
#include <unordered_map>
#include <map>
#include <cstring>
#include <string>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

enum symbol_tab_types{
	S_FILE,S_BLOCK,S_FUNC,S_PROTO
};


// entries of symbol table
typedef struct table_entry{
    ull size;
    ll offset;
    string type;
    int init_flag;
    int is_array;
} Entry;

typedef unordered_map<string,Entry *> symbol_table;


string convert_to_string(char *str);

extern int blk_num;
extern int offset_gnum;
extern int next_flag;
extern long int blk_size[100];
extern long long offset_g[100];
extern map<string , string> argsMap;
extern map<string ,int> item_switch;
extern map<symbol_table *, int > symbol_tab_types;
extern map<symbol_table *, symbol_table*> Parent;
extern map<int, string> statusMap;

extern symbol_table global_table;
extern symbol_table *curr;

ull get_size (char* id);
void fprintStruct(Entry *a, FILE *file);
void table_initialize();
void addKeywords();
void paramTable();
void update_init_flag(string k);
void create_table(string name,int type,string func_type);
void insert_args(string a,string b);
void update_table(string k);
void insert_symbol(symbol_table& table,string k,string type,ull size,ll offset,int init_flag);
void print_tables(symbol_table *a, string filename);
void print_func_args();
void update_table_size(string k);
void make_struct_table();
void itemSwitchMap();
Entry* lookup(string a);
Entry* scopeLookup(string a);
Entry* add_entry(string type, ull size, ll offset,int init_flag);
bool insert_sym_struct(string k, string type, ull size, ull offset, int init_flag );
bool end_struct(string struct_name);
bool struct_flag(string struct_name);
string get_sym_type(string k);
string func_args_list(string k);
string struct_membr_type(string struct_name, string idT);
int structLookup(string struct_name, string idStruct);
