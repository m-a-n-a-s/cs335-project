#include "IR_3ac.h"
#include <fstream>
using namespace std;

long long pos = -1;
vector<quad> emit_list;

unordered_map<int, string> label_map;
unordered_map<string, int> goto_map;
unordered_map<string, vector<int>> backpatch_list;

ofstream IR_file;

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
    //cout<<new_instr.op.first<<" "<<new_instr.operand_1.first<<" "<<new_instr.operand_2.first<<"\n";
    return ++pos;
}

//get temporary variable
string newlabel_var(){
    static long temp_var_num = 0;
    temp_var_num++;
    return (string("@temp") + to_string(temp_var_num));
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

int assign_3ac(char* oprtr, string type, string operand_1_type, string operand_2_type, pair <string, Entry*> operand_1_place, pair <string, Entry*> operand_2_place){
    int ret_val;
    string oprtr_str = string(oprtr);

    if(oprtr_str == "=" || oprtr_str == "+=" || oprtr_str == "-=" || oprtr_str == "*=" || oprtr_str == "/="){            
        bool equate = false;
        bool same_type = true;
        bool oprtr_matched = false;
        
        pair <string, Entry*> t;
        pair <string, Entry*> t2;

        string tmp_oprtr1;
        string tmp_oprtr2;

        if (oprtr_str == "="){
            equate = true;
            t = operand_2_place;
        }
        else if (oprtr_str == "+=" || oprtr_str == "-=" || oprtr_str == "*=" || oprtr_str == "/=")  oprtr_matched = true;

        if(oprtr_matched){
            t = newlabel_sym(type);
            tmp_oprtr1.push_back(oprtr[0]);
            tmp_oprtr2 = tmp_oprtr1;
        }

        if (int_flag(operand_1_type)){
            if (int_flag(operand_2_type)){
                tmp_oprtr1.append("int");
                if(equate){
                    //do nothing
                }
                else{
                    ret_val = emit(pair<string, Entry *>(tmp_oprtr1, NULL), operand_1_place, operand_2_place, t, -1);
                }
            }
            else if (real_flag(operand_2_type)){
                same_type = false;
                t2 = newlabel_sym(type);
                ret_val = emit(pair<string, Entry *>("realtoint", NULL), operand_2_place, pair<string, Entry *>("", NULL), t2, -1);
                tmp_oprtr1.append("int");
                if(equate){
                    //do nothing
                }
                else{
                    ret_val=emit(pair<string, Entry *>(tmp_oprtr1,NULL), operand_1_place, t2, t, -1);
                }
            }
        }
        else if (real_flag(operand_1_type))
        {
            if (int_flag(operand_2_type))
            {
                t2 = newlabel_sym(type);
                ret_val = emit(pair<string, Entry *>("inttoreal", NULL), operand_2_place, pair<string, Entry *>("", NULL), t2, -1);
                tmp_oprtr1.append("real");
                if(equate){
                    //do nothing
                }
                else{
                    ret_val=emit(pair<string, Entry *>(tmp_oprtr1, NULL), operand_1_place, t2, t, -1);
                }
                same_type = false;
            }
            else if (real_flag(operand_2_type))
            {
                tmp_oprtr1.append("real");
                if(equate){
                    //do nothing
                }
                else{
                    ret_val = emit(pair<string, Entry *>(tmp_oprtr1, NULL), operand_1_place, operand_2_place, t, -1);
                }
            }
        }

        if (!same_type && equate){
            ret_val=emit(pair<string, Entry *>("=", NULL), t2, pair<string, Entry *>("", NULL), operand_1_place, -1);
        }
        else{
            ret_val = emit(pair<string, Entry *>("=", NULL), t, pair<string, Entry *>("", NULL), operand_1_place, -1);
        }
    }

    else{
        ret_val = 0;
        bool oprtr_matched = false;

        pair <string, Entry*> t = newlabel_sym(type);
        
        string tmp_oprtr1;
        string tmp_oprtr2;

        string oprtr_str = string(oprtr);

        if (oprtr_str == "%=" || oprtr_str == "^=" || oprtr_str == "|=" || oprtr_str == "&="){
            oprtr_matched = true;
        }

        if(oprtr_matched){
            tmp_oprtr1.push_back(oprtr[0]);
            tmp_oprtr2 = tmp_oprtr1;
        }

        else{
            if (oprtr_str == "<<="){
                tmp_oprtr1.append("LEFT_OP");
                tmp_oprtr2.append("<<");
            }

            else if(oprtr_str == ">>="){
                tmp_oprtr1.append("RIGHT_OP");
                tmp_oprtr2.append(">>");
            }
        }
        emit(pair<string, Entry *>(tmp_oprtr1, NULL), operand_1_place, operand_2_place, t, -1);
        ret_val=emit(pair<string, Entry *>("=", NULL), t, pair<string, Entry *>("", NULL), operand_1_place, -1);
    
    }

    return ret_val;
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
    IR_file.open("IRcode.txt");
	for(int i = 0; i < emit_list.size(); ++i)  {
		switch (-emit_list[i].line_no){
        case 1: {IR_file << setw(5) << "[" << i << "]" << ": " << setw(15) << emit_list[i].op.first << " " <<
                    setw(15) << emit_list[i].operand_1.first << " " <<
                    setw(15) << emit_list[i].operand_2.first << " " <<
                    setw(15) << emit_list[i].ans.first << '\n';
                break;}
        case 2: {IR_file  << endl << "[" << i << "]" << ": "<<
                    emit_list[i].op.first << endl << endl;
                break;}
        case 3: {IR_file  << endl << "[" << i << "]" << ": "<<
                    emit_list[i].op.first << endl << endl;
                break;}
        case 4: {IR_file << setw(5) << "[" << i << "]" << ": " << setw(15) << emit_list[i].op.first << " " <<
                    setw(15) << emit_list[i].operand_1.first << " " <<
                    setw(15) << emit_list[i].operand_2.first << " " <<
                    setw(15) << emit_list[i].ans.first << '\n';
                break;}
        case 7: {IR_file << setw(5) << "[" << i << "]" << ": " << setw(15) << emit_list[i].op.first << " " <<
                    setw(15) << emit_list[i].operand_1.first << " " <<
                    setw(15) << emit_list[i].operand_2.first << " " <<
                    setw(15) << emit_list[i].ans.first << '\n';
                break;}
        default:{int k = emit_list[i].line_no;
                while(emit_list[k].op.first == "GOTO" && emit_list[k].operand_1.first == ""){
                    k = emit_list[k].line_no;
                }
                if(label_map.find(k)== label_map.end()) label_map.insert(pair<int, string>(k, "Label"+to_string(k)));
                IR_file << setw(5) << "[" << i << "]" << ": " << setw(15) << emit_list[i].op.first << " " <<
                    setw(15) << emit_list[i].operand_1.first << " " <<
                    setw(15) << emit_list[i].operand_2.first << " " <<
                    setw(15) << k << "---" << '\n';
                emit_list[i].line_no = k;
                break;}
        }
	}
    IR_file.close();
	return;
}
