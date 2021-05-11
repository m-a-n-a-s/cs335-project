#include <iostream>
#include <unordered_map>
#include <map>
#include <cstring>
#include <string>
#include <vector>
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
    int is_struct; // 1 means struct. Used in codegen
    
    int col;//for mult dim
    int dim;//for mult dim
    int off;//for mult dim

    int struct_size;
    int is_struct_array;
    //vector<int> dim; //ith dim col size
    //vector<int> off; //offset of the ith index
} Entry;

typedef unordered_map<string,Entry *> symbol_table;

string convert_to_string(char *str);

extern map<string, symbol_table *> struct_table_map;
extern map<string , string> args_map;
extern map<symbol_table *, symbol_table*> Parent;
extern map<string, int> struct_size_map;

extern int blk_num;
extern long long blk_size[20];

extern int offset_arr_index;
extern long long offset_arr[20];
extern long long old_offset;
extern long long struct_offset;
extern long long struct_size;

extern bool str_mark2_done;


extern symbol_table global_table;
extern symbol_table *curr;
extern symbol_table *struct_table;

void table_initialize();
void insert_symbol1(symbol_table &table, string key, string type, unsigned long long size, int init_flag);
void insert_symbol2(symbol_table &table, string key, string type, unsigned long long size, int init_flag);
void insert_symbol3(symbol_table &table, string key, string type, unsigned long long size, int init_flag);
void create_table(string name,string func_type);
void update_table(string key,int is_init);
Entry* lookup(string key);
void print_tables(symbol_table *tab, string filename);
