#include "semanticCheck.h"
#include "IR_3ac.h"

#include <fstream>
using namespace std;
using std::setw;

long long pos = -1;
vector<quad> emit_list;
map<int, string> label_map;
map<string, int> goto_map;
unordered_map<string, vector<int>> backpatch_list;

ofstream IRcodeFile;

//set the values inside struct
quad set_values_quad(pair <string, Entry*> operand_1, pair <string, Entry*> operand_2, pair <string, Entry*> op, pair <string, Entry*> ans, int line_no){  
    quad new_instr;
    new_instr.operand_1 = operand_1;
    new_instr.operand_2 = operand_2;
    new_instr.op = op;
    new_instr.ans = ans;
    new_instr.line_no = line_no;
    return new_instr;
}

//emit
int emit(pair <string, Entry*> op, pair <string, Entry*> operand_1, pair <string, Entry*> operand_2, pair <string, Entry*> ans, int line_no){
    quad new_instr = set_values_quad(operand_1, operand_2, op, ans, line_no);
    emit_list.push_back(new_instr);
    return ++pos;
}

//get temporary variable
string newlabel_var(){
    static long temp_var_num = 0;
    temp_var_num++;
    return (string("temp_") + to_string(temp_var_num));
}

//get temporary symbol
pair<string, Entry *> newlabel_sym(string type){
    string temp_var_str = newlabel_var();
    char* new_temp_str = new char[type.length() + 1];
    strcpy(new_temp_str, type.c_str()); 
    insert_symbol(*curr, temp_var_str, type, get_size(new_temp_str), 0, 1);
    pair<string, Entry *> new_temp_sym = pair <string, Entry* >(temp_var_str, lookup(temp_var_str));
    return new_temp_sym;
}

int assignmentExpression(char* o, string type, string type1, string type3, pair <string, Entry*> place1, pair <string, Entry*> place3){
    pair <string, Entry*> t = place3;
    pair <string, Entry*> t2;
    string o_new(o);
    string op;
    string op1;
    int a = 0;
    int b = 0;
    if (o_new == "=")
        a = 1;
    else if (o_new == "*=")
    {
        op = "*";
        op1 = "*";
        t = newlabel_sym(type);
    }
    else if (o_new == "/=")
    {
        op = "/";
        op1 = "/";
        t = newlabel_sym(type);
    }
    else if (o_new == "+=")
    {
        op = "+";
        op1 = "+";
        t = newlabel_sym(type);
    }
    else if (o_new == "-=")
    {
        op = "-";
        op1 = "-";
        t = newlabel_sym(type);
    }
    int k;

    if (is_Intgr(type1))
    {
        if (is_Intgr(type3))
        {
            op += "int";
            if (o_new != "=")
                k = emit(pair<string, Entry *>(op, lookup(op1)), place1, place3, t, -1);
        }
        else if (is_float(type3))
        {
            t2 = newlabel_sym(type);
            k = emit(pair<string, Entry *>("realtoint", NULL), place3, pair<string, Entry *>("", NULL), t2, -1);
            op += "int";
            if (o_new != "=")
                emit(pair<string, Entry *>(op, lookup(op1)), place1, t2, t, -1);
            b = 1;
        }
    }
    else if (is_float(type1))
    {
        if (is_Intgr(type3))
        {
            t2 = newlabel_sym(type);
            k = emit(pair<string, Entry *>("realtoint", NULL), place3, pair<string, Entry *>("", NULL), t2, -1);
            op += "int";
            if (o_new != "=")
                emit(pair<string, Entry *>(op, lookup(op1)), place1, t2, t, -1);
            b = 1;
        }
        else if (is_float(type3))
        {
            op += "real";
            if (o_new != "=")
                k = emit(pair<string, Entry *>(op, lookup(op1)), place1, place3, t, -1);
        }
    }

    if (!(a && b))
        k = emit(pair<string, Entry *>("=", lookup("=")), t, pair<string, Entry *>("", NULL), place1, -1);
    else
        emit(pair<string, Entry *>("=", lookup("=")), t2, pair<string, Entry *>("", NULL), place1, -1);

    return k;
}
void assignment2(char *o, string type, string type1, string type3, pair <string, Entry*> place1, pair <string, Entry*> place3)
{
    pair <string, Entry*> t = newlabel_sym(type);
    string o_new(o);
    string op;
    string op1;
    if (o_new == "%=")
        op = "%";
    else if (o_new == "^=")
        op = "^";
    else if (o_new == "|=")
        op = "|";
    else if (o_new == "&=")
        op = "&";
    op1 = op;
    if (o_new == "<<=")
    {
        op = "LEFT_OP";
        op1 = "<<";
    }
    if (o_new == ">>=")
    {
        op = "RIGHT_OP";
        op1 = ">>";
    }
    emit(pair<string, Entry *>(op, lookup(op1)), place1, place3, t, -1);
    emit(pair<string, Entry *>("=", lookup("=")), t, pair<string, Entry *>("", NULL), place1, -1);
}

//backpatch
void backPatch(vector<int> goto_list, int line_no){
    for (int i = 0; i < goto_list.size(); ++i){
        emit_list[goto_list[i]].line_no = line_no;
    }
    return;
}

//finding corresponding goto for backpatches
char *backPatchGoto(){
    for (auto it = backpatch_list.begin(); it != backpatch_list.end(); ++it){
        if (goto_map.find(it->first) == goto_map.end()){
            char *a;
            strcpy(a, it->first.c_str());
            return a;
        }
        else{
            backPatch(backpatch_list[it->first], goto_map[it->first]);
        }
    }
    return NULL;
}

// --- REMEMBER --- It will be used as it is in main.cpp and  removed from here

void show_in_file(){
    IRcodeFile.open("IRcode.txt");
	for(int i = 0; i < emit_list.size(); ++i)  {
		switch (-emit_list[i].line_no){
        case 1: {IRcodeFile << setw(5) << "[" << i << "]" << ": " << setw(15) << emit_list[i].op.first << " " <<
                    setw(15) << emit_list[i].operand_1.first << " " <<
                    setw(15) << emit_list[i].operand_2.first << " " <<
                    setw(15) << emit_list[i].ans.first << '\n';
                break;}
        case 2: {IRcodeFile  << endl << "[" << i << "]" << ": "<<
                    emit_list[i].op.first << endl << endl;
                break;}
        case 3: {IRcodeFile  << endl << "[" << i << "]" << ": "<<
                    emit_list[i].op.first << endl << endl;
                break;}
        case 4: {IRcodeFile << setw(5) << "[" << i << "]" << ": " << setw(15) << emit_list[i].op.first << " " <<
                    setw(15) << emit_list[i].operand_1.first << " " <<
                    setw(15) << emit_list[i].operand_2.first << " " <<
                    setw(15) << emit_list[i].ans.first << '\n';
                break;}
        default:{int k = emit_list[i].line_no;
                while(emit_list[k].op.first == "GOTO" && emit_list[k].operand_1.first == ""){
                    k = emit_list[k].line_no;
                }
                if(label_map.find(k)== label_map.end()) label_map.insert(pair<int, string>(k, "Label"+to_string(k)));
                IRcodeFile << setw(5) << "[" << i << "]" << ": " << setw(15) << emit_list[i].op.first << " " <<
                    setw(15) << emit_list[i].operand_1.first << " " <<
                    setw(15) << emit_list[i].operand_2.first << " " <<
                    setw(15) << k << "---" << '\n';
                emit_list[i].line_no = k;
                break;}
        }
	}
    IRcodeFile.close();
	return;
}
