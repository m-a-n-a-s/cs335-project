#include <fstream>
#include "IR_3ac.h"
#include "semanticCheck.h"
using namespace std;
using std::setw;

map<int , string> Labels;
ofstream IRcodeFile;
long long Index = -1;
map<string, int> gotoIndex;
unordered_map<string, vector<int>> gotoIndexPatchList;

vector <quad> emit_list;

//get temporary variable
string newlabel_var(){
  static long temp_var_num = 0;
  temp_var_num++;
  return (string("temp_") + to_string(temp_var_num));
}

//get temporary symbol
pair<string, Entry*> newlabel_sym(string type){
    string temp_var_str = newlabel_var();
    insert_symbol(*curr, temp_var_str, type, get_size(&type[0]),0, 1);
    pair <string, Entry*> new_temp_sym = pair <string, Entry* >(temp, lookup(temp));
    return new_temp_sym;
}

void set_values_quad(quad* new_instr, qid id1, qid id2, qid op, qid res, int stmtNum){
    new_instr->id1 = id1;
    new_instr->id2 = id2;
    new_instr->op = op;
    new_instr->res = res;
    new_instr->stmtNum = stmtNum;
    return;
}

//emit
int emit(qid op, qid id1, qid id2, qid res, int stmtNum){
  quad* new_instr;
  emit_list.push_back(new_instr);
  return ++Index;
}

//backpatch
void backPatch(vector<int> li, int p){
  for(int i=0; i<li.size(); ++i){
    emit_list[li[i]].stmtNum = p;
}
return;
}

int assignmentExpression(char *o, string type, string type1, string type3, qid place1, qid place3){
	qid t = place3;
    qid t2;
    string o_new(o);
	string op;
	string op1;
    int a=0;
    int b=0;
    if(o_new == "=") a=1;
	else if(o_new == "*="){
		op = "*";
        op1 = "*";
		t = newlabel_sym(type);
	}else if(o_new == "/="){
		op = "/";
        op1 = "/";
		t = newlabel_sym(type);
	}else if(o_new == "+="){
		op = "+";
        op1 = "+";
		t = newlabel_sym(type);
	}else if(o_new == "-="){
		op = "-";
        op1 = "-";
		t = newlabel_sym(type);
	}
    int k;

    if(is_Intgr(type1)){
        if(is_Intgr(type3)){
            op += "int";
	        if(o_new != "=") k= emit(pair<string, Entry*>(op, lookup(op1)), place1, place3, t, -1);
        }else if(is_float(type3)){
            t2 = newlabel_sym(type);
		    k = emit(pair<string, Entry*>("realtoint",NULL),place3,pair<string, Entry*>("",NULL),t2,-1);
		    op += "int";
		    if(o_new != "=") emit(pair<string, Entry*>(op, lookup(op1)), place1, t2, t, -1);
            b=1;
        }
    }else if(is_float(type1)){
        if(is_Intgr(type3)){
            t2 = newlabel_sym(type);
            k = emit(pair<string, Entry*>("realtoint",NULL),place3,pair<string, Entry*>("",NULL),t2,-1);
            op += "int";
            if(o_new != "=") emit(pair<string, Entry*>(op, lookup(op1)), place1, t2, t, -1);
            b=1;
        }else if(is_float(type3)){
            op += "real";
		    if(o_new != "=") k=emit(pair<string, Entry*>(op, lookup(op1)), place1, place3, t, -1);
        }
    }

    if(!(a &&b )) k= emit(pair<string, Entry*>("=", lookup("=")),  t, pair<string, Entry*>("", NULL), place1, -1);
	else emit(pair<string, Entry*>("=", lookup("=")),  t2, pair<string, Entry*>("", NULL), place1, -1);

    return k;

}
void assignment2(char *o, string type, string type1, string type3, qid place1, qid place3){
	qid t = newlabel_sym(type);
    string o_new(o);
	string op;
	string op1;
    if(o_new == "%=") op = "%";
    else if(o_new == "^=") op = "^";
    else if(o_new == "|=") op = "|";
    else if(o_new == "&=") op = "&";
    op1 = op;
    if(o_new == "<<="){ op="LEFT_OP"; op1="<<"; }
    if(o_new == ">>="){ op="RIGHT_OP"; op1=">>"; }
    emit(pair<string, Entry*>(op, lookup(op1)), place1, place3, t, -1);
    emit(pair<string, Entry*>("=", lookup("=")),  t, pair<string, Entry*>("", NULL), place1, -1);
}

// List of goto___'s
//if(!gotoIndexStorage($1, $3)){yyerror("ERROR:\'%s\' is already defined", $1);}
bool gotoIndexStorage (string id, int loc){
  if(gotoIndex.find(id) == gotoIndex.end()){
    //not found
    gotoIndex.insert(pair<string, int>(id, loc));
    return true;
  }
  return false;
}

//List of backpatch to resolve goto___'s
void gotoIndexPatchListStorage (string id, int loc){
    gotoIndexPatchList[id].push_back(loc);
}

//finding corresponding goto for backpatches
char* backPatchGoto(){
  for (auto it =gotoIndexPatchList.begin(); it!=gotoIndexPatchList.end(); ++it){
    if(gotoIndex.find(it->first)==gotoIndex.end()){
        char *a;
        strcpy(a, it->first.c_str());
        return a;
    }
    else {
        backPatch(gotoIndexPatchList[it->first] , gotoIndex[it->first]);
    }
 }
    return NULL;
}

void show_in_file(){
    IRcodeFile.open("IRcode.txt");
	for(int i = 0; i < emit_list.size(); ++i)  {
		switch (-emit_list[i].stmtNum){
        case 1: {IRcodeFile << setw(5) << "[" << i << "]" << ": " << setw(15) << emit_list[i].op.first << " " <<
                    setw(15) << emit_list[i].id1.first << " " <<
                    setw(15) << emit_list[i].id2.first << " " <<
                    setw(15) << emit_list[i].res.first << '\n';}
                break;
        case 2: {IRcodeFile  << endl << "[" << i << "]" << ": "<<
                    emit_list[i].op.first << endl << endl;}
                    break;
        case 3: {IRcodeFile  << endl << "[" << i << "]" << ": "<<
                    emit_list[i].op.first << endl << endl;}
                break;
        case 4: {IRcodeFile << setw(5) << "[" << i << "]" << ": " << setw(15) << emit_list[i].op.first << " " <<
                    setw(15) << emit_list[i].id1.first << " " <<
                    setw(15) << emit_list[i].id2.first << " " <<
                    setw(15) << emit_list[i].res.first << '\n';}
        default: {while(emit_list[k].op.first == "GOTO" && emit_list[k].id1.first == ""){
                        k = emit_list[k].stmtNum;
                    }
                    if(Labels.find(k)== Labels.end()) Labels.insert(pair<int, string>(k, "Label"+to_string(k)));
                    IRcodeFile << setw(5) << "[" << i << "]" << ": " << setw(15) << emit_list[i].op.first << " " <<
                        setw(15) << emit_list[i].id1.first << " " <<
                        setw(15) << emit_list[i].id2.first << " " <<
                        setw(15) << k << "---" << '\n';
                    emit_list[i].stmtNum = k;}
                    break; 
        }
	}
    IRcodeFile.close();
	return;
}